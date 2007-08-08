package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.Cancellable;
import org.opensim.modeling.Analysis;
import org.opensim.modeling.AnalyzeTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.modeling.InverseDynamics;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

public class AnalyzeToolModel extends AbstractToolModelWithExternalLoads {
   //========================================================================
   // AnalyzeToolWorker
   //========================================================================
   class AnalyzeToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      AnalyzeToolWorker() throws IOException {
         updateTool();

         // Re-initialize our copy of the model
         Model model = getOriginalModel().clone();
         model.setInputFileName("");

         // Update actuator set and contact force set based on settings in the tool, then call setup() and setModel()
         // setModel() will call addAnalysisSetToModel
         tool.updateModelActuatorsAndContactForces(model, "");
         model.setup();
         tool.setModel(model);

         if(getInputSource()==InputSource.Motion && getInputMotion()!=null)
            getTool().setStatesFromMotion(getInputMotion(),false); // false == motion is in radians
         else
            getTool().loadStatesFromFile();
         getTool().loadControlsFromFile();
         getTool().loadPseudoStatesFromFile();

         // We don't need to add model to the 3D view... just using it to dump analyses result files
         setModel(model);

         // Initialize progress bar, given we know the number of frames to process
         double ti = getInitialTime();
         double tf = getFinalTime();
         progressHandle = ProgressHandleFactory.createHandle("Executing analyses...",
                              new Cancellable() {
                                 public boolean cancel() {
                                    interrupt(false);
                                    return true;
                                 }
                              });

         // Animation callback will update the display during forward
         animationCallback = new JavaMotionDisplayerCallback(getModel(), getOriginalModel(), null, progressHandle);
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(1);
         animationCallback.startProgressUsingTime(ti,tf);

         // Do this manouver (there's gotta be a nicer way) to create the object so that C++ owns it and not Java (since 
         // removeIntegCallback in finished() will cause the C++-side callback to be deleted, and if Java owned this object
         // it would then later try to delete it yet again)
         interruptingCallback = InterruptingIntegCallback.safeDownCast((new InterruptingIntegCallback()).copy());
         getModel().addIntegCallback(interruptingCallback);

         setExecuting(true);
      }

      public void interrupt(boolean promptToKeepPartialResult) {
         this.promptToKeepPartialResult = promptToKeepPartialResult;
         if(interruptingCallback!=null) interruptingCallback.interrupt();
      }

      public Object construct() {
         result = tool.run();

         return this;
      }

      public void finished() {
         boolean processResults = result;
         if(!result) { // TODO: prompt to keep partial results?
            DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Tool execution canceled by user.  Output files not written."));
         }

         progressHandle.finish();

         // Clean up motion displayer (this is necessary!)
         animationCallback.cleanupMotionDisplayer();

         getModel().removeIntegCallback(animationCallback);
         getModel().removeIntegCallback(interruptingCallback);
         interruptingCallback = null;

         if(result) resetModified();

         setExecuting(false);

         worker = null;
      }
   }
   private AnalyzeToolWorker worker = null;
   //========================================================================
   // END AnalyzeToolWorker
   //========================================================================
   
   private boolean inverseDynamicsMode = false;

   enum InputSource { Motion, States, Coordinates, Unspecified };
   private InputSource inputSource = InputSource.Unspecified;
   private Storage inputMotion = null;
   private boolean loadSpeeds = false;
   private boolean controlsEnabled = false;
   private String toolName;

   public AnalyzeToolModel(Model model, boolean inverseDynamicsMode) throws IOException {
      super(model);

      this.inverseDynamicsMode = inverseDynamicsMode;
      if(inverseDynamicsMode) toolName = "Inverse Dynamics Tool";
      else toolName = "Analyze Tool";

      // In inverse dynamisc mode, we know for sure we'll need a real dynamics engine, so check this up front
      if(inverseDynamicsMode && model.getDynamicsEngine().getType().equals("SimmKinematicsEngine"))
         throw new IOException("Inverse dynamics tool requires a model with SdfastEngine or SimbodyEngine; SimmKinematicsEngine does not support dynamics.");

      setTool(new AnalyzeTool());

      // By default, set prefix of output to be subject name
      getTool().setName(model.getName());

      setDefaultResultsDirectory(model);

      adjustToolForInverseDynamicsMode();
      updateFromTool();

      determineDefaultInputSource();
   }

   AnalyzeTool getTool() { return (AnalyzeTool)tool; }

   //------------------------------------------------------------------------
   // Utilities for inverse dynamics specific analyze tool
   //------------------------------------------------------------------------

   protected void adjustToolForInverseDynamicsMode() {
      if(!inverseDynamicsMode) return;
      // Since we're not using the model's actuator set, clear the actuator set related fields
      getTool().setReplaceActuatorSet(true);
      getTool().getActuatorSetFiles().setSize(0);
      // Check if have non-inverse dynamics analyses, or multiple inverse dynamics analyses
      boolean foundOtherAnalysis = false;
      boolean advancedSettings = false;
      int numInverseDynamicsAnalyses = 0;
      InverseDynamics inverseDynamicsAnalysis = null;
      for(int i=getTool().getAnalysisSet().getSize()-1; i>=0; i--) {
         Analysis analysis = getTool().getAnalysisSet().get(i);
         System.out.println("PROCESSING ANALYSIS "+analysis.getType()+","+analysis.getName());
         if(InverseDynamics.safeDownCast(analysis)==null) {
            foundOtherAnalysis = true;
            getTool().getAnalysisSet().remove(i);
         }
         else { 
            numInverseDynamicsAnalyses++;
            if(numInverseDynamicsAnalyses==1) {
               inverseDynamicsAnalysis = InverseDynamics.safeDownCast(analysis);
               if(inverseDynamicsAnalysis.getUseModelActuatorSet() || !inverseDynamicsAnalysis.getOn()) 
                  advancedSettings = true;
            } else {
               getTool().getAnalysisSet().remove(i);
            }
         }
      }
      if(inverseDynamicsAnalysis==null) {
         inverseDynamicsAnalysis = InverseDynamics.safeDownCast(new InverseDynamics().copy()); // C++-side copy
         getTool().getAnalysisSet().append(inverseDynamicsAnalysis);
      }
      inverseDynamicsAnalysis.setOn(true);
      inverseDynamicsAnalysis.setUseModelActuatorSet(false);

      if(foundOtherAnalysis || advancedSettings || numInverseDynamicsAnalyses>1) {
         String message = "";
         if(foundOtherAnalysis) message = "Settings file contained analyses other than inverse dynamics.  The inverse dynamics tool will ignore these.\n";
         if(numInverseDynamicsAnalyses>1) message += "More than one inverse dynamics analysis found.  Extras will be ignored.\n";
         if(advancedSettings) message += "Settings file contained an inverse dynamics analysis with advanced settings which will be ignored by the inverse dynamics tool.\n";
         message += "Please use the analyze tool if you wish to handle different analysis types and advanced analysis settings.\n";
         DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message(message, NotifyDescriptor.WARNING_MESSAGE));
      }
   }

   //------------------------------------------------------------------------
   // Default input source
   //------------------------------------------------------------------------

   protected void determineDefaultInputSource() {
      inputSource = InputSource.Unspecified;
      MotionsDB mdb = MotionsDB.getInstance();
      ArrayList<Storage> motions = mdb.getModelMotions(getOriginalModel());
      if(motions!=null && motions.size()>0) {
         // First check if one of the current motions is of this model
         for(int i=0; i<mdb.getNumCurrentMotions(); i++)
            if(mdb.getCurrentMotion(i).model==getOriginalModel()) {
               inputMotion = mdb.getCurrentMotion(i).motion;
               inputSource = InputSource.Motion;
               return;
            }
         // If not, then pick the first of this model's motions
         inputMotion = motions.get(0);
         inputSource = InputSource.Motion;
      }
   }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public InputSource getInputSource() { return inputSource; }
   public void setInputSource(InputSource inputSource) { 
      if(this.inputSource != inputSource) {
         this.inputSource = inputSource;
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public Storage getInputMotion() { return inputMotion; }
   public void setInputMotion(Storage inputMotion) { 
      if(this.inputMotion != inputMotion) {
         this.inputMotion = inputMotion;
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getControlsFileName() { return getTool().getControlsFileName(); }
   void setControlsFileName(String speedsFileName) {
      if(!getControlsFileName().equals(speedsFileName)) {
         getTool().setControlsFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getControlsValid() { return !getControlsEnabled() || (new File(getControlsFileName()).exists()); }
   public boolean getControlsEnabled() { return controlsEnabled; }
   public void setControlsEnabled(boolean enabled) {
      if(controlsEnabled != enabled) {
         controlsEnabled = enabled;
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getStatesFileName() { return getTool().getStatesFileName(); }
   void setStatesFileName(String speedsFileName) {
      if(!getStatesFileName().equals(speedsFileName)) {
         getTool().setStatesFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getStatesValid() { return (new File(getStatesFileName()).exists()); }

   public boolean needPseudoStates() { return getOriginalModel().getNumPseudoStates()>0; }

   public String getPseudoStatesFileName() { return getTool().getPseudoStatesFileName(); }
   void setPseudoStatesFileName(String speedsFileName) {
      if(!getPseudoStatesFileName().equals(speedsFileName)) {
         getTool().setPseudoStatesFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getCoordinatesFileName() { return getTool().getCoordinatesFileName(); }
   void setCoordinatesFileName(String coordinatesFileName) {
      if(!getCoordinatesFileName().equals(coordinatesFileName)) {
         getTool().setCoordinatesFileName(coordinatesFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getCoordinatesValid() { return (new File(getCoordinatesFileName()).exists()); }

   public String getSpeedsFileName() { return getTool().getSpeedsFileName(); }
   void setSpeedsFileName(String speedsFileName) {
      if(!getSpeedsFileName().equals(speedsFileName)) {
         getTool().setSpeedsFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getSpeedsValid() { return !getLoadSpeeds() || (new File(getSpeedsFileName()).exists()); }
   public boolean getLoadSpeeds() { return loadSpeeds; }
   public void setLoadSpeeds(boolean loadSpeeds) { 
      if(this.loadSpeeds != loadSpeeds) {
         this.loadSpeeds = loadSpeeds;
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public double getLowpassCutoffFrequency() { return getTool().getLowpassCutoffFrequency(); }
   public void setLowpassCutoffFrequency(double frequency) {
      if(getLowpassCutoffFrequency() != frequency) {
         getTool().setLowpassCutoffFrequency(frequency);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public boolean getFilterCoordinates() { return getLowpassCutoffFrequency() > 0; }
   public void setFilterCoordinates(boolean filterCoordinates) {
      if(getFilterCoordinates() != filterCoordinates) {
         if(filterCoordinates) getTool().setLowpassCutoffFrequency(6);
         else getTool().setLowpassCutoffFrequency(-1);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   // TODO: implement
   public double[] getAvailableTimeRange() { 
      double range[] = null;
      if(getInputSource()==InputSource.Motion && getInputMotion()!=null) 
         range = new double[]{getInputMotion().getFirstTime(), getInputMotion().getLastTime()};
      return range;
   }

   //------------------------------------------------------------------------
   // External loads get/set (don't need to call setModified since AbstractToolModel does that)
   //------------------------------------------------------------------------
   public String getExternalLoadsFileName() { return getTool().getExternalLoadsFileName(); }
   protected void setExternalLoadsFileNameInternal(String fileName) { getTool().setExternalLoadsFileName(fileName); }

   public String getExternalLoadsModelKinematicsFileName() { return getTool().getExternalLoadsModelKinematicsFileName(); }
   protected void setExternalLoadsModelKinematicsFileNameInternal(String fileName) { getTool().setExternalLoadsModelKinematicsFileName(fileName); }

   public String getExternalLoadsBody1() { return getTool().getExternalLoadsBody1(); }
   protected void setExternalLoadsBody1Internal(String name) { getTool().setExternalLoadsBody1(name); }

   public String getExternalLoadsBody2() { return getTool().getExternalLoadsBody2(); }
   protected void setExternalLoadsBody2Internal(String name) { getTool().setExternalLoadsBody2(name); }

   public double getLowpassCutoffFrequencyForLoadKinematics() { return getTool().getLowpassCutoffFrequencyForLoadKinematics(); }
   protected void setLowpassCutoffFrequencyForLoadKinematicsInternal(double cutoffFrequency) { getTool().setLowpassCutoffFrequencyForLoadKinematics(cutoffFrequency); }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   public void execute() {
      if(isModified() && worker==null) {
         try {
            worker = new AnalyzeToolWorker();
         } catch (IOException ex) {
            setExecuting(false);
            ErrorDialog.displayIOExceptionDialog(toolName+" Error", "Tool initialization failed.", ex);
            return;
         }
         worker.start();
      }
   }

   // TODO: may need to use locks and such to ensure that worker doesn't get set to null (by IKToolWorker.finished()) in between worker!=null check and worker.interrupt()
   // But I think both will typically run on the swing thread so probably safe
   public void interrupt(boolean promptToKeepPartialResult) {
      if(worker!=null) worker.interrupt(promptToKeepPartialResult);
   }

   public void cancel() {
      interrupt(false);
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   private boolean isValidInput() {
      return (getInputSource()==InputSource.Motion && getInputMotion()!=null) ||
             (getInputSource()==InputSource.States && getStatesValid()) ||
             (getInputSource()==InputSource.Coordinates && getCoordinatesValid()); // TODO check SpeedsValid once we re-enable speeds
   }

   public boolean isValid() {
      return super.isValid() && isValidInput() && getControlsValid();
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   protected void updateFromTool() {
      super.updateFromTool();

      if(!FileUtils.effectivelyNull(getStatesFileName())) inputSource = InputSource.States;
      else if(!FileUtils.effectivelyNull(getCoordinatesFileName())) inputSource = InputSource.Coordinates;
      else inputSource = InputSource.Unspecified;

      loadSpeeds = (inputSource == InputSource.Coordinates && !FileUtils.effectivelyNull(getSpeedsFileName()));

      controlsEnabled = !FileUtils.effectivelyNull(getControlsFileName());
   }

   protected void updateTool() {
      super.updateTool();

      // The C++ code determines whether we're using states or coordinates as input based on whether the file names are nonempty
      if(inputSource != InputSource.Coordinates) {
         getTool().setCoordinatesFileName("");
      } 
      if(inputSource != InputSource.Coordinates || !getLoadSpeeds()) {
         getTool().setSpeedsFileName("");
      }
      if(inputSource != InputSource.States) {
         getTool().setStatesFileName("");
      }

      setModified(AbstractToolModel.Operation.AllDataChanged);
   }

   protected void relativeToAbsolutePaths(String parentFileName) {
      super.relativeToAbsolutePaths(parentFileName);

      String parentDir = (new File(parentFileName)).getParent();

      getTool().setControlsFileName(FileUtils.makePathAbsolute(getTool().getControlsFileName(), parentDir));
      getTool().setStatesFileName(FileUtils.makePathAbsolute(getTool().getStatesFileName(), parentDir));
      getTool().setPseudoStatesFileName(FileUtils.makePathAbsolute(getTool().getPseudoStatesFileName(), parentDir));
      getTool().setCoordinatesFileName(FileUtils.makePathAbsolute(getTool().getCoordinatesFileName(), parentDir));
      getTool().setSpeedsFileName(FileUtils.makePathAbsolute(getTool().getSpeedsFileName(), parentDir));

      getTool().setExternalLoadsFileName(FileUtils.makePathAbsolute(getTool().getExternalLoadsFileName(), parentDir));
      getTool().setExternalLoadsModelKinematicsFileName(FileUtils.makePathAbsolute(getTool().getExternalLoadsModelKinematicsFileName(), parentDir));
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      AnalyzeTool newAnalyzeTool = null;
      try {
         // TODO: pass it our model instead
         newAnalyzeTool = new AnalyzeTool(fileName, false);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }

      setTool(newAnalyzeTool);
      relativeToAbsolutePaths(fileName);
      adjustToolForInverseDynamicsMode();
      updateFromTool();
      setModified(AbstractToolModel.Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      updateTool();
      getTool().print(fileName);
      return true;
   }
}

