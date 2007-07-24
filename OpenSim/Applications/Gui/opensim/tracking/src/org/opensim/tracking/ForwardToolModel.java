package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.Cancellable;
import org.opensim.modeling.ForwardTool;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.swingui.SwingWorker;
import org.opensim.tracking.IKToolModel.IKToolWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

public class ForwardToolModel extends AbstractToolModel {
   //========================================================================
   // ForwardToolWorker
   //========================================================================
   class ForwardToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      ForwardToolWorker() {
         updateTool();

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

         // Animation callback will update the display during forward
         animationCallback = new JavaMotionDisplayerCallback(getModel(), null, progressHandle);
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(100);
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
         /*result = */tool.run();

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
   private ForwardToolWorker worker = null;
   //========================================================================
   // END ForwardToolWorker
   //========================================================================
   
   public ForwardToolModel() {
      setTool(new ForwardTool());
   }

   ForwardTool forwardTool() { return (ForwardTool)tool; }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public String getControlsFileName() { return forwardTool().getControlsFileName(); }
   public String getInitialStatesFileName() { return forwardTool().getInitialStatesFileName(); }

   // External loads
   public String getExternalLoadsFileName() { return forwardTool().getExternalLoadsFileName(); }
   public String getExternalLoadsModelKinematicsFileName() { return forwardTool().getExternalLoadsModelKinematicsFileName(); }
   public String getExternalLoadsBody1() { return forwardTool().getExternalLoadsBody1(); }
   public String getExternalLoadsBody2() { return forwardTool().getExternalLoadsBody2(); }
   public double getLowpassCutoffFrequencyForLoadKinematics() { return forwardTool().getLowpassCutoffFrequencyForLoadKinematics(); }

   // Integrator settings
   public boolean getUseSpecifiedDt() { return forwardTool().getUseSpecifiedDt(); }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   public void execute() {
      if(isModified() && worker==null) {
         worker = new ForwardToolWorker();
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
      return forwardTool().getModel()!=null;
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   protected void updateFromTool() {

   }

   protected void updateTool() {
      super.updateTool();
   }

   protected void relativeToAbsolutePaths(String parentFileName) {
      super.relativeToAbsolutePaths(parentFileName);

      String parentDir = (new File(parentFileName)).getParent();
      forwardTool().setModelFilename(FileUtils.makePathAbsolute(forwardTool().getModelFilename(), parentDir));
      forwardTool().setControlsFileName(FileUtils.makePathAbsolute(forwardTool().getControlsFileName(), parentDir));
      forwardTool().setInitialStatesFileName(FileUtils.makePathAbsolute(forwardTool().getInitialStatesFileName(), parentDir));
      forwardTool().setExternalLoadsFileName(FileUtils.makePathAbsolute(forwardTool().getExternalLoadsFileName(), parentDir));
      forwardTool().setExternalLoadsModelKinematicsFileName(FileUtils.makePathAbsolute(forwardTool().getExternalLoadsModelKinematicsFileName(), parentDir));
      forwardTool().setResultsDir(FileUtils.makePathAbsolute(forwardTool().getResultsDir(), parentDir));
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      ForwardTool newForwardTool = null;
      try {
         // TODO: pass it our model instead
         newForwardTool = new ForwardTool(fileName);
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
      // TODO: implement
      return false;
   }
}
