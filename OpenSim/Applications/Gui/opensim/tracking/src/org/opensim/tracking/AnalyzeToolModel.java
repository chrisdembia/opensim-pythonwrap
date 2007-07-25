package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.Cancellable;
import org.opensim.modeling.AnalyzeTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Model;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
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

   enum InputSource { Motion, States, Coordinates };
   private InputSource inputSource = InputSource.Motion;
   private boolean loadSpeeds = false;

   public AnalyzeToolModel(Model model) throws IOException {
      super(null);

      this.originalModel = model;

      setTool(new AnalyzeTool());
   }

   AnalyzeTool getTool() { return (AnalyzeTool)tool; }
   Model getOriginalModel() { return originalModel; }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public InputSource getInputSource() { return inputSource; }
   public void setInputSource(InputSource inputSource) { this.inputSource = inputSource; }

   public boolean getLoadSpeeds() { return loadSpeeds; }
   public void setLoadSpeeds(boolean loadSpeeds) { this.loadSpeeds = loadSpeeds; }

   public String getControlsFileName() { return getTool().getControlsFileName(); }
   public String getStatesFileName() { return getTool().getStatesFileName(); }
   public String getPseudoStatesFileName() { return getTool().getPseudoStatesFileName(); }
   public String getCoordinatesFileName() { return getTool().getCoordinatesFileName(); }
   public String getSpeedsFileName() { return getTool().getSpeedsFileName(); }
   public double getLowpassCutoffFrequency() { return getTool().getLowpassCutoffFrequency(); }
   public boolean getFilterCoordinates() { return getLowpassCutoffFrequency() > 0; }

   // External loads
   public String getExternalLoadsFileName() { return getTool().getExternalLoadsFileName(); }
   public String getExternalLoadsModelKinematicsFileName() { return getTool().getExternalLoadsModelKinematicsFileName(); }
   public String getExternalLoadsBody1() { return getTool().getExternalLoadsBody1(); }
   public String getExternalLoadsBody2() { return getTool().getExternalLoadsBody2(); }
   public double getLowpassCutoffFrequencyForLoadKinematics() { return getTool().getLowpassCutoffFrequencyForLoadKinematics(); }
   public boolean getFilterLoadKinematics() { return getLowpassCutoffFrequencyForLoadKinematics() > 0; }

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
      return true;
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   protected void updateFromTool() {
      if(!FileUtils.effectivelyNull(getStatesFileName())) inputSource = InputSource.States;
      else if(!FileUtils.effectivelyNull(getCoordinatesFileName())) inputSource = InputSource.Coordinates;
      else inputSource = InputSource.Motion;

      loadSpeeds = (inputSource == InputSource.Coordinates && !FileUtils.effectivelyNull(getSpeedsFileName()));
   }

   protected void updateTool() {
      super.updateTool();
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
      updateFromTool();
      setModified(AbstractToolModel.Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      // TODO: implement
      return false;
   }
}

