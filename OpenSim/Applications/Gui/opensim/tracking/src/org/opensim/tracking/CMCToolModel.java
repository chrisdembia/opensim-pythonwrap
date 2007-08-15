package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.Cancellable;
import org.opensim.modeling.CMCTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Kinematics;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;

public class CMCToolModel extends AbstractToolModelWithExternalLoads {
   //========================================================================
   // CMCToolWorker
   //========================================================================
   class CMCToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      private Kinematics kinematicsAnalysis = null; // For creating a storage we'll use as a motion
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      CMCToolWorker() throws IOException {
         updateTool();

         // Make no motion be currently selected (so model doesn't have extraneous ground forces/experimental markers from
         // another motion show up on it)
         MotionsDB.getInstance().clearCurrent();

         // CMC needs to remember the original actuator set, since it is replaced in updateModelActuatorsAndContactForces
         cmcTool().setOriginalActuatorSet(getOriginalModel().getActuatorSet());

         // Re-initialize our copy of the model
         Model model = getOriginalModel().clone();
         model.setInputFileName("");

         // Update actuator set and contact force set based on settings in the tool, then call setup() and setModel()
         // setModel() will call addAnalysisSetToModel
         tool.updateModelActuatorsAndContactForces(model, "");
         model.setup();
         tool.setModel(model);

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
         animationCallback = new JavaMotionDisplayerCallback(getModel(), getOriginalModel(), null, progressHandle);
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(1);
         animationCallback.startProgressUsingTime(ti,tf);

         // Do this manouver (there's gotta be a nicer way) to create the object so that C++ owns it and not Java (since 
         // removeIntegCallback in finished() will cause the C++-side callback to be deleted, and if Java owned this object
         // it would then later try to delete it yet again)
         interruptingCallback = InterruptingIntegCallback.safeDownCast((new InterruptingIntegCallback()).copy());
         getModel().addIntegCallback(interruptingCallback);

         // Kinematics analysis -- so that we can extract the resulting motion
         kinematicsAnalysis = Kinematics.safeDownCast((new Kinematics()).copy());
         kinematicsAnalysis.setRecordAccelerations(false);
         kinematicsAnalysis.setInDegrees(false);
         kinematicsAnalysis.setPrintResultFiles(false);
         getModel().addAnalysis(kinematicsAnalysis);

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

         // Add adjusted RRA model if we're in that mode
         if(processResults) {
            // Remove previous motion
            if(motion!=null) {
               if(reducedResidualsModel!=null) MotionsDB.getInstance().closeMotion(reducedResidualsModel, motion, false);
               else MotionsDB.getInstance().closeMotion(getOriginalModel(), motion, false);
               motion = null;
            }

            motion = new Storage(kinematicsAnalysis.getPositionStorage());
            motion.resampleLinear(0.001); // so that we don't get a crazy oversampled storage

            if(getAdjustModelToReduceResidualsEnabled()) {
               Model newReducedResidualsModel = null;
               try {
                  newReducedResidualsModel = new Model(getOutputModelFileName());
                  newReducedResidualsModel.setup();
               } catch (IOException ex) {
                  newReducedResidualsModel = null;
               }
               OpenSimDB.getInstance().replaceModel(reducedResidualsModel, newReducedResidualsModel);
               reducedResidualsModel = newReducedResidualsModel;
               MotionsDB.getInstance().addMotion(reducedResidualsModel, motion);
            } else {
               if(reducedResidualsModel!=null) {
                  OpenSimDB.getInstance().removeModel(reducedResidualsModel);
                  reducedResidualsModel = null;
               }
               MotionsDB.getInstance().addMotion(getOriginalModel(), motion);
            }
         }

         // Remove the kinematics analysis before printing results, so its results won't be written to disk
         getModel().removeAnalysis(kinematicsAnalysis);

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
   private CMCToolWorker worker = null;
   //========================================================================
   // END CMCToolWorker
   //========================================================================

   private boolean constraintsEnabled = false;
   private Model reducedResidualsModel = null;
   private Storage motion = null;

   public CMCToolModel(Model model) throws IOException {
      super(model);

      setTool(new CMCTool());

      // By default, set prefix of output to be subject name
      cmcTool().setName(model.getName());

      setDefaultResultsDirectory(model);

      updateFromTool();
   }

   CMCTool cmcTool() { return (CMCTool)tool; }

   //------------------------------------------------------------------------
   // Get/set
   //------------------------------------------------------------------------

   public String getDesiredKinematicsFileName() { return cmcTool().getDesiredKinematicsFileName(); }
   public void setDesiredKinematicsFileName(String fileName) {
      if(!getDesiredKinematicsFileName().equals(fileName)) {
         cmcTool().setDesiredKinematicsFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getDesiredKinematicsValid() { return (new File(getDesiredKinematicsFileName()).exists()); }

   public String getTaskSetFileName() { return cmcTool().getTaskSetFileName(); }
   public void setTaskSetFileName(String fileName) {
      if(!getTaskSetFileName().equals(fileName)) {
         cmcTool().setTaskSetFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getTaskSetValid() { return (new File(getTaskSetFileName()).exists()); }

   public String getConstraintsFileName() { return cmcTool().getConstraintsFileName(); }
   public void setConstraintsFileName(String fileName) {
      if(!getConstraintsFileName().equals(fileName)) {
         cmcTool().setConstraintsFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getConstraintsValid() { return !getConstraintsEnabled() || (new File(getConstraintsFileName()).exists()); }

   public boolean getConstraintsEnabled() { return constraintsEnabled; }
   public void setConstraintsEnabled(boolean enabled) {
      if(getConstraintsEnabled() != enabled) {
         constraintsEnabled = enabled;
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public double getLowpassCutoffFrequency() { return cmcTool().getLowpassCutoffFrequency(); }
   public void setLowpassCutoffFrequency(double frequency) {
      if(getLowpassCutoffFrequency() != frequency) {
         cmcTool().setLowpassCutoffFrequency(frequency);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public boolean getFilterKinematics() { return getLowpassCutoffFrequency() > 0; }
   public void setFilterKinematics(boolean filterKinematics) {
      if(getFilterKinematics() != filterKinematics) {
         if(filterKinematics) cmcTool().setLowpassCutoffFrequency(6);
         else cmcTool().setLowpassCutoffFrequency(-1);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   // RRA settings
   //
   public String getOutputModelFileName() { return cmcTool().getOutputModelFileName(); }
   public void setOutputModelFileName(String fileName) {
      if(!getOutputModelFileName().equals(fileName)) {
         cmcTool().setOutputModelFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public boolean getAdjustModelToReduceResidualsEnabled() { return cmcTool().getAdjustCOMToReduceResiduals(); }
   public void setAdjustModelToReduceResidualsEnabled(boolean enabled) {
      if(getAdjustModelToReduceResidualsEnabled() != enabled) {
         cmcTool().setAdjustCOMToReduceResiduals(enabled);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getAdjustedCOMBody() { return cmcTool().getAdjustedCOMBody(); }
   public void setAdjustedCOMBody(String fileName) {
      if(!getAdjustedCOMBody().equals(fileName)) {
         cmcTool().setAdjustedCOMBody(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getAdjustedCOMBodyValid() {
      return getOriginalModel().getDynamicsEngine().getBodySet().getIndex(getAdjustedCOMBody())>=0;
   }

   private boolean isRRAValid() {
      return !getAdjustModelToReduceResidualsEnabled() || (!FileUtils.effectivelyNull(getOutputModelFileName()) && getAdjustedCOMBodyValid());
   }

   //------------------------------------------------------------------------
   // External loads get/set (don't need to call setModified since AbstractToolModel does that)
   //------------------------------------------------------------------------
   public String getExternalLoadsFileName() { return cmcTool().getExternalLoadsFileName(); }
   protected void setExternalLoadsFileNameInternal(String fileName) { cmcTool().setExternalLoadsFileName(fileName); }

   public String getExternalLoadsModelKinematicsFileName() { return cmcTool().getExternalLoadsModelKinematicsFileName(); }
   protected void setExternalLoadsModelKinematicsFileNameInternal(String fileName) { cmcTool().setExternalLoadsModelKinematicsFileName(fileName); }

   public String getExternalLoadsBody1() { return cmcTool().getExternalLoadsBody1(); }
   protected void setExternalLoadsBody1Internal(String name) { cmcTool().setExternalLoadsBody1(name); }

   public String getExternalLoadsBody2() { return cmcTool().getExternalLoadsBody2(); }
   protected void setExternalLoadsBody2Internal(String name) { cmcTool().setExternalLoadsBody2(name); }

   public double getLowpassCutoffFrequencyForLoadKinematics() { return cmcTool().getLowpassCutoffFrequencyForLoadKinematics(); }
   protected void setLowpassCutoffFrequencyForLoadKinematicsInternal(double cutoffFrequency) { cmcTool().setLowpassCutoffFrequencyForLoadKinematics(cutoffFrequency); }

   // TODO: implement
   public double[] getAvailableTimeRange() { return null; }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   public void execute() {
      if(isModified() && worker==null) {
         try {
            worker = new CMCToolWorker();
         } catch (IOException ex) {
            setExecuting(false);
            ErrorDialog.displayIOExceptionDialog("CMC Tool Error", "Tool initialization failed.", ex);
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
      if(reducedResidualsModel!=null) {
         OpenSimDB.getInstance().removeModel(reducedResidualsModel);
         reducedResidualsModel = null;
      }
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public boolean isValid() {
      return super.isValid() && getDesiredKinematicsValid() && getTaskSetValid() && getConstraintsValid() && isRRAValid();
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   protected void updateFromTool() {
      super.updateFromTool();

      constraintsEnabled = !FileUtils.effectivelyNull(getConstraintsFileName());
   }

   protected void updateTool() {
      super.updateTool();

      if(!constraintsEnabled) cmcTool().setConstraintsFileName("");

      setModified(AbstractToolModel.Operation.AllDataChanged);
   }

   protected void relativeToAbsolutePaths(String parentFileName) {
      super.relativeToAbsolutePaths(parentFileName);

      String parentDir = (new File(parentFileName)).getParent();

      cmcTool().setDesiredKinematicsFileName(FileUtils.makePathAbsolute(cmcTool().getDesiredKinematicsFileName(), parentDir));
      cmcTool().setConstraintsFileName(FileUtils.makePathAbsolute(cmcTool().getConstraintsFileName(), parentDir));
      cmcTool().setTaskSetFileName(FileUtils.makePathAbsolute(cmcTool().getTaskSetFileName(), parentDir));
      cmcTool().setRRAControlsFileName(FileUtils.makePathAbsolute(cmcTool().getRRAControlsFileName(), parentDir));
      cmcTool().setOutputModelFileName(FileUtils.makePathAbsolute(cmcTool().getOutputModelFileName(), parentDir));

      cmcTool().setExternalLoadsFileName(FileUtils.makePathAbsolute(cmcTool().getExternalLoadsFileName(), parentDir));
      cmcTool().setExternalLoadsModelKinematicsFileName(FileUtils.makePathAbsolute(cmcTool().getExternalLoadsModelKinematicsFileName(), parentDir));
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      CMCTool newCMCTool = null;
      try {
         // TODO: pass it our model instead
         newCMCTool = new CMCTool(fileName, false);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }

      setTool(newCMCTool);
      relativeToAbsolutePaths(fileName);
      updateFromTool();
      setModified(AbstractToolModel.Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      updateTool();
      cmcTool().print(fileName);
      return true;
   }
}

