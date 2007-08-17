package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.awt.StatusDisplayer;
import org.openide.util.Cancellable;
import org.opensim.modeling.ForwardTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Kinematics;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

public class ForwardToolModel extends AbstractToolModelWithExternalLoads {
   //========================================================================
   // ForwardToolWorker
   //========================================================================
   class ForwardToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      private Kinematics kinematicsAnalysis = null; // For creating a storage we'll use as a motion
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      ForwardToolWorker() throws IOException {
         updateTool();

         // Make no motion be currently selected (so model doesn't have extraneous ground forces/experimental markers from
         // another motion show up on it)
         MotionsDB.getInstance().clearCurrent();

         // Re-initialize our copy of the model
         Model model = new Model(getOriginalModel());
         model.setInputFileName("");

         // Update actuator set and contact force set based on settings in the tool, then call setup() and setModel()
         // setModel() will call addAnalysisSetToModel
         tool.updateModelActuatorsAndContactForces(model, "");
         model.setup();
         tool.setModel(model);

         // don't add the model... we'll run forward on the new model but will actually apply the resulting motions to the current model
         setModel(model);

         // set model in our tool
         // add analysis set to model
         // TODO: eventually we'll want to have the kinematics analysis store the motion for us...

         // Initialize progress bar, given we know the number of frames to process
         double ti = getInitialTime();
         double tf = getFinalTime();
         progressHandle = ProgressHandleFactory.createHandle("Executing forward integration...",
                              new Cancellable() {
                                 public boolean cancel() {
                                    interrupt(false);
                                    return true;
                                 }
                              });

         // Animation callback will update the display *of the original model* during forward
         animationCallback = new JavaMotionDisplayerCallback(getModel(), getOriginalModel(), null, progressHandle);
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(1);
         animationCallback.setMinRenderTimeInterval(0.1); // to avoid rendering really frequently which can slow down our execution
         animationCallback.setRenderMuscleActivations(true);
         animationCallback.startProgressUsingTime(ti,tf);

         // Do this manouver (there's gotta be a nicer way) to create the object so that C++ owns it and not Java (since 
         // removeIntegCallback in finished() will cause the C++-side callback to be deleted, and if Java owned this object
         // it would then later try to delete it yet again)
         interruptingCallback = InterruptingIntegCallback.safeDownCast((new InterruptingIntegCallback()).copy());
         getModel().addIntegCallback(interruptingCallback);

         // Kinematics analysis -- so that we can extract the resulting motion
         // NO LONGER NEEDED SINCE WE JUST GET THE STATES FROM THE INTEGRAND
         //kinematicsAnalysis = Kinematics.safeDownCast((new Kinematics()).copy());
         //kinematicsAnalysis.setRecordAccelerations(false);
         //kinematicsAnalysis.setInDegrees(false);
         //kinematicsAnalysis.setPrintResultFiles(false);
         //getModel().addAnalysis(kinematicsAnalysis);

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
         if(!result && promptToKeepPartialResult) {
            Object answer = DialogDisplayer.getDefault().notify(new NotifyDescriptor.Confirmation("Forward integration did not complete.  Keep partial result?",NotifyDescriptor.YES_NO_OPTION));
            if(answer==NotifyDescriptor.YES_OPTION) processResults = true;
         }

         // Clean up motion displayer (this is necessary!)
         // Do it before adding/removing motions in MotionsDB since here we disable muscle activation rendering, 
         // but we want added motions to be able to enable that
         animationCallback.cleanupMotionDisplayer();

         if(processResults) {
            Storage motion = null;
            if(forwardTool().getStateStorage()!=null) {
               motion = new Storage(forwardTool().getStateStorage());
               motion.resampleLinear(0.001);
            }
            updateMotion(motion); // replaces current motion
         }

         //getModel().removeAnalysis(kinematicsAnalysis);

         // TODO: move this to a worker thread so as to not freeze the GUI if writing takes a while?
         if(processResults) {
            forwardTool().printResults();
         }

         progressHandle.finish();

         getModel().removeIntegCallback(animationCallback);
         getModel().removeIntegCallback(interruptingCallback);
         interruptingCallback = null;

         if(result) resetModified();

         setExecuting(false);

         worker = null;
      }
   }
   private ForwardToolWorker worker = null;
   //========================================================================
   // END ForwardToolWorker
   //========================================================================

   private Storage motion = null;

   public ForwardToolModel(Model model) throws IOException {
      super(model);

      // Check that the model has a real dynamics engine
      if(model.getDynamicsEngine().getType().equals("SimmKinematicsEngine"))
         throw new IOException("Forward dynamics tool requires a model with SdfastEngine or SimbodyEngine; SimmKinematicsEngine does not support dynamics.");

      setTool(new ForwardTool());

      // By default, set prefix of output to be subject name
      forwardTool().setName(model.getName());

      setDefaultResultsDirectory(model);
   }

   ForwardTool forwardTool() { return (ForwardTool)tool; }

   //------------------------------------------------------------------------
   // Setting the motion in the model
   //------------------------------------------------------------------------
   private void updateMotion(Storage newMotion) {
      if(motion!=null) {
         MotionsDB.getInstance().closeMotion(getOriginalModel(), motion, false);
      }
      motion = newMotion;
      if(motion!=null) {
         MotionsDB.getInstance().addMotion(getOriginalModel(), motion);
      }
   }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public String getControlsFileName() { return forwardTool().getControlsFileName(); }
   public void setControlsFileName(String fileName) {
      if(!getControlsFileName().equals(fileName)) {
         forwardTool().setControlsFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getControlsValid() { return (new File(getControlsFileName()).exists()); }

   public String getInitialStatesFileName() { return forwardTool().getStatesFileName(); }
   public void setInitialStatesFileName(String fileName) {
      if(!getInitialStatesFileName().equals(fileName)) {
         forwardTool().setStatesFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getInitialStatesValid() { return (new File(getInitialStatesFileName()).exists()); }

   // TODO: implement
   public double[] getAvailableTimeRange() { return null; }

   //------------------------------------------------------------------------
   // Integrator settings (continued from AbstractToolModel
   //------------------------------------------------------------------------
   public boolean getUseSpecifiedDt() { return forwardTool().getUseSpecifiedDt(); }
   public void setUseSpecifiedDt(boolean useSpecifiedDt) {
      if(getUseSpecifiedDt() != useSpecifiedDt) {
         forwardTool().setUseSpecifiedDt(useSpecifiedDt);
         setModified(AbstractToolModel.Operation.IntegratorSettingsChanged);
      }
   }

   //------------------------------------------------------------------------
   // External loads get/set (don't need to call setModified since AbstractToolModel does that)
   //------------------------------------------------------------------------
   public String getExternalLoadsFileName() { return forwardTool().getExternalLoadsFileName(); }
   protected void setExternalLoadsFileNameInternal(String fileName) { forwardTool().setExternalLoadsFileName(fileName); }

   public String getExternalLoadsModelKinematicsFileName() { return forwardTool().getExternalLoadsModelKinematicsFileName(); }
   protected void setExternalLoadsModelKinematicsFileNameInternal(String fileName) { forwardTool().setExternalLoadsModelKinematicsFileName(fileName); }

   public String getExternalLoadsBody1() { return forwardTool().getExternalLoadsBody1(); }
   protected void setExternalLoadsBody1Internal(String name) { forwardTool().setExternalLoadsBody1(name); }

   public String getExternalLoadsBody2() { return forwardTool().getExternalLoadsBody2(); }
   protected void setExternalLoadsBody2Internal(String name) { forwardTool().setExternalLoadsBody2(name); }

   public double getLowpassCutoffFrequencyForLoadKinematics() { return forwardTool().getLowpassCutoffFrequencyForLoadKinematics(); }
   protected void setLowpassCutoffFrequencyForLoadKinematicsInternal(double cutoffFrequency) { forwardTool().setLowpassCutoffFrequencyForLoadKinematics(cutoffFrequency); }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   public void execute() {
      if(isModified() && worker==null) {
         try {
            worker = new ForwardToolWorker();
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
      updateMotion(null);
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public boolean isValid() {
      return super.isValid() && getInitialStatesValid() && getControlsValid();
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   protected void updateFromTool() {
      super.updateFromTool();
   }

   protected void updateTool() {
      super.updateTool();
      forwardTool().setPrintResultFiles(false); // we'll manually write them out
   }

   protected void relativeToAbsolutePaths(String parentFileName) {
      super.relativeToAbsolutePaths(parentFileName);

      String parentDir = (new File(parentFileName)).getParent();

      forwardTool().setModelFilename(FileUtils.makePathAbsolute(forwardTool().getModelFilename(), parentDir));
      forwardTool().setControlsFileName(FileUtils.makePathAbsolute(forwardTool().getControlsFileName(), parentDir));
      forwardTool().setStatesFileName(FileUtils.makePathAbsolute(forwardTool().getStatesFileName(), parentDir));

      forwardTool().setExternalLoadsFileName(FileUtils.makePathAbsolute(forwardTool().getExternalLoadsFileName(), parentDir));
      forwardTool().setExternalLoadsModelKinematicsFileName(FileUtils.makePathAbsolute(forwardTool().getExternalLoadsModelKinematicsFileName(), parentDir));
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      ForwardTool newForwardTool = null;
      try {
         // TODO: pass it our model instead
         newForwardTool = new ForwardTool(fileName, false);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }

      setTool(newForwardTool);
      relativeToAbsolutePaths(fileName);
      updateFromTool();
      setModified(AbstractToolModel.Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      updateTool();
      forwardTool().print(fileName);
      return true;
   }
}
