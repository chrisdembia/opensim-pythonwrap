package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.Cancellable;
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
import org.opensim.view.pub.OpenSimDB;

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
         getTool().loadControlsStatesPseudoStatesExternalLoadsFromFiles();

         OpenSimDB.getInstance().replaceModel(getModel(), model);
         setModel(model);

         // TODO: eventually we'll want to have the kinematics analysis store the motion for us...

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
         animationCallback = new JavaMotionDisplayerCallback(getModel(), null, progressHandle);
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(10);
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

         // Update one last time (TODO: is this necessary?)
         animationCallback.updateDisplaySynchronously();

         return this;
      }

      public void finished() {
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
   
   private Model originalModel = null;
   private boolean inverseDynamicsMode = false;

   enum InputSource { Motion, States, Coordinates, Unspecified };
   private InputSource inputSource = InputSource.Unspecified;
   private Storage inputMotion = null;
   private boolean loadSpeeds = false;

   public AnalyzeToolModel(Model model, boolean inverseDynamicsMode) throws IOException {
      super(null);

      this.originalModel = model;
      this.inverseDynamicsMode = inverseDynamicsMode;

      setTool(new AnalyzeTool());

      // By default, set prefix of output to be subject name
      getTool().setName(model.getName());

      // In inverse dynamics mode, initialize with an inverse dynamics analysis
      if(inverseDynamicsMode) {
         InverseDynamics inverseDynamicsAnalysis = InverseDynamics.safeDownCast(new InverseDynamics().copy()); // C++-side copy
         inverseDynamicsAnalysis.setUseModelActuatorSet(false);
         getTool().getAnalysisSet().append(inverseDynamicsAnalysis);
      }

      updateFromTool();

      determineDefaultInputSource();
   }

   AnalyzeTool getTool() { return (AnalyzeTool)tool; }
   Model getOriginalModel() { return originalModel; }

   //------------------------------------------------------------------------
   // Default input source
   //------------------------------------------------------------------------

   protected void determineDefaultInputSource() {
      inputSource = InputSource.Unspecified;
      ArrayList<Storage> motions = MotionsDB.getInstance().getModelMotions(getOriginalModel());
      if(motions!=null && motions.size()>0) {
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

   public boolean getLoadSpeeds() { return loadSpeeds; }
   public void setLoadSpeeds(boolean loadSpeeds) { 
      if(this.loadSpeeds != loadSpeeds) {
         this.loadSpeeds = loadSpeeds;
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

   public String getStatesFileName() { return getTool().getStatesFileName(); }
   void setStatesFileName(String speedsFileName) {
      if(!getStatesFileName().equals(speedsFileName)) {
         getTool().setStatesFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public boolean needPseudoStates() { return getOriginalModel().getNumPseudoStates()>0; }

   public String getPseudoStatesFileName() { return getTool().getPseudoStatesFileName(); }
   void setPseudoStatesFileName(String speedsFileName) {
      if(!getPseudoStatesFileName().equals(speedsFileName)) {
         getTool().setPseudoStatesFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getCoordinatesFileName() { return getTool().getCoordinatesFileName(); }
   void setCoordinatesFileName(String speedsFileName) {
      if(!getCoordinatesFileName().equals(speedsFileName)) {
         getTool().setCoordinatesFileName(speedsFileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getSpeedsFileName() { return getTool().getSpeedsFileName(); }
   void setSpeedsFileName(String speedsFileName) {
      if(!getSpeedsFileName().equals(speedsFileName)) {
         getTool().setSpeedsFileName(speedsFileName);
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

   //------------------------------------------------------------------------
   // External loads get/set
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
      if(getModel()!=null) {
         OpenSimDB.getInstance().removeModel(getModel());
      }
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public boolean isValid() {
      return getInputSource()!=InputSource.Unspecified;
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

      // TODO: if in inverse dynamics mode and the file we read in does not appear to be an analysis with an inverse dynamics analysis, print error/warning

      setTool(newAnalyzeTool);
      relativeToAbsolutePaths(fileName);
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

