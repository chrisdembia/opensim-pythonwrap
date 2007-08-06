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
import org.opensim.modeling.CMCTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.modeling.InverseDynamics;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

public class CMCToolModel extends AbstractToolModelWithExternalLoads {
   //========================================================================
   // CMCToolWorker
   //========================================================================
   class CMCToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      CMCToolWorker() throws IOException {
         updateTool();

         // CMC needs to remember the original actuator set, since it is replaced in updateModelActuatorsAndContactForces
         getTool().setOriginalActuatorSet(getOriginalModel().getActuatorSet());

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
   private CMCToolWorker worker = null;
   //========================================================================
   // END CMCToolWorker
   //========================================================================

   private boolean constraintsEnabled = false;

   public CMCToolModel(Model model) throws IOException {
      super(model);

      setTool(new CMCTool());

      // By default, set prefix of output to be subject name
      getTool().setName(model.getName());

      setDefaultResultsDirectory(model);

      updateFromTool();
   }

   CMCTool getTool() { return (CMCTool)tool; }

   //------------------------------------------------------------------------
   // Get/set
   //------------------------------------------------------------------------

   public String getDesiredKinematicsFileName() { return getTool().getDesiredKinematicsFileName(); }
   public void setDesiredKinematicsFileName(String fileName) {
      if(!getDesiredKinematicsFileName().equals(fileName)) {
         getTool().setDesiredKinematicsFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getDesiredKinematicsValid() { return (new File(getDesiredKinematicsFileName()).exists()); }

   public String getTaskSetFileName() { return getTool().getTaskSetFileName(); }
   public void setTaskSetFileName(String fileName) {
      if(!getTaskSetFileName().equals(fileName)) {
         getTool().setTaskSetFileName(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }
   public boolean getTaskSetValid() { return (new File(getTaskSetFileName()).exists()); }

   public String getConstraintsFileName() { return getTool().getConstraintsFileName(); }
   public void setConstraintsFileName(String fileName) {
      if(!getConstraintsFileName().equals(fileName)) {
         getTool().setConstraintsFileName(fileName);
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

   public String getOutputModelFileName() { return getTool().getOutputModelFileName(); }
   public void setOutputModelFileName(String fileName) {
      if(!getOutputModelFileName().equals(fileName)) {
         getTool().setOutputModelFileName(fileName);
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

   public boolean getFilterKinematics() { return getLowpassCutoffFrequency() > 0; }
   public void setFilterKinematics(boolean filterKinematics) {
      if(getFilterKinematics() != filterKinematics) {
         if(filterKinematics) getTool().setLowpassCutoffFrequency(6);
         else getTool().setLowpassCutoffFrequency(-1);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   // RRA settings
   //
   public boolean getResidualReductionEnabled() { return getTool().getAdjustCOMToReduceResiduals(); }
   public void setResidualReductionEnabled(boolean enabled) {
      if(getResidualReductionEnabled() != enabled) {
         getTool().setAdjustCOMToReduceResiduals(enabled);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
   }

   public String getAdjustedCOMBody() { return getTool().getAdjustedCOMBody(); }
   public void setAdjustedCOMBody(String fileName) {
      if(!getAdjustedCOMBody().equals(fileName)) {
         getTool().setAdjustedCOMBody(fileName);
         setModified(AbstractToolModel.Operation.InputDataChanged);
      }
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

   // TODO: implement
   public boolean getAvailableTimeRangeValid() { return false; }
   public double getAvailableInitialTime() { return -1 ;}
   public double getAvailableFinalTime() { return -1; }

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
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public boolean isValid() {
      return super.isValid() && getDesiredKinematicsValid() && getTaskSetValid() && getConstraintsValid();
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

      if(!constraintsEnabled) getTool().setConstraintsFileName("");

      setModified(AbstractToolModel.Operation.AllDataChanged);
   }

   protected void relativeToAbsolutePaths(String parentFileName) {
      super.relativeToAbsolutePaths(parentFileName);

      String parentDir = (new File(parentFileName)).getParent();

      getTool().setDesiredKinematicsFileName(FileUtils.makePathAbsolute(getTool().getDesiredKinematicsFileName(), parentDir));
      getTool().setConstraintsFileName(FileUtils.makePathAbsolute(getTool().getConstraintsFileName(), parentDir));
      getTool().setTaskSetFileName(FileUtils.makePathAbsolute(getTool().getTaskSetFileName(), parentDir));
      getTool().setRRAControlsFileName(FileUtils.makePathAbsolute(getTool().getRRAControlsFileName(), parentDir));
      getTool().setOutputModelFileName(FileUtils.makePathAbsolute(getTool().getOutputModelFileName(), parentDir));

      getTool().setExternalLoadsFileName(FileUtils.makePathAbsolute(getTool().getExternalLoadsFileName(), parentDir));
      getTool().setExternalLoadsModelKinematicsFileName(FileUtils.makePathAbsolute(getTool().getExternalLoadsModelKinematicsFileName(), parentDir));
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
      getTool().print(fileName);
      return true;
   }
}

