package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.Cancellable;
import org.opensim.modeling.IKTool;
import org.opensim.modeling.IKTrial;
import org.opensim.modeling.InterruptingIntegCallback;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.JavaMotionDisplayerCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

//==================================================================
// IKToolModel
//==================================================================
// Only deals with a single (the first) IKTrial in the IKTrialSet of IKTool
public class IKToolModel extends Observable implements Observer {
   //========================================================================
   // IKToolWorker
   //========================================================================
   class IKToolWorker extends SwingWorker {
      private ProgressHandle progressHandle = null;
      private JavaMotionDisplayerCallback animationCallback = null;
      private InterruptingIntegCallback interruptingCallback = null;
      boolean result = false;
      boolean promptToKeepPartialResult = true;
     
      IKToolWorker() {
         updateIKTool();

         // We assume we're working with trial 0.  No support for dealing with other trials in the trial set right now.
         ikTool.initializeTrial(0);

         // Make no motion be currently selected (so model doesn't have extraneous ground forces/experimental markers from
         // another motion show up on it)
         MotionsDB.getInstance().flushMotions();

         // Animation callback will update the display during IK solve
         animationCallback = new JavaMotionDisplayerCallback(getModel(), ikTool.getIKTrialSet().get(0).getOutputStorage());
         getModel().addIntegCallback(animationCallback);
         animationCallback.setStepInterval(1);

         // Do this manouver (there's gotta be a nicer way) to create the object so that C++ owns it and not Java (since 
         // removeIntegCallback in finished() will cause the C++-side callback to be deleted, and if Java owned this object
         // it would then later try to delete it yet again)
         interruptingCallback = InterruptingIntegCallback.safeDownCast((new InterruptingIntegCallback()).copy());
         getModel().addIntegCallback(interruptingCallback);

         progressHandle = ProgressHandleFactory.createHandle("Executing inverse kinematics...",
                              new Cancellable() {
                                 public boolean cancel() {
                                    interrupt(true);
                                    return true;
                                 }
                              });
         progressHandle.start();

         setExecuting(true);
      }

      public void interrupt(boolean promptToKeepPartialResult) {
         this.promptToKeepPartialResult = promptToKeepPartialResult;
         if(interruptingCallback!=null) interruptingCallback.interrupt();
      }

      public Object construct() {
         result = ikTool.solveTrial(0);

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

         IKTrial trial = ikTool.getIKTrialSet().get(0);

         boolean addMotion = true;
         if(!result) {
            boolean havePartialResult = trial.getOutputStorage()!=null && trial.getOutputStorage().getSize()>0;
            if(havePartialResult && promptToKeepPartialResult) {
               Object answer = DialogDisplayer.getDefault().notify(new NotifyDescriptor.Confirmation("Inverse kinematics did not complete.  Keep partial result?",NotifyDescriptor.YES_NO_OPTION));
               if(answer==NotifyDescriptor.NO_OPTION) addMotion = false;
            } else {
               addMotion = false;
            }
         }

         if(addMotion) {
            Storage motion = new Storage(trial.getOutputStorage()); // Java-side copy
            updateMotion(motion);
         }

         setExecuting(false);

         worker = null;
      }
   }
   private IKToolWorker worker = null;
   //========================================================================
   // END IKToolWorker
   //========================================================================

   enum Operation { AllDataChanged, IKTaskSetChanged, ExecutionStateChanged };

   private IKTool ikTool = null;
   private Model model = null;
   private boolean modifiedSinceLastExecute = true;
   private IKCommonModel ikCommonModel;
   private Storage motion = null;
   private boolean executing = false;

   public IKToolModel(Model originalModel) throws IOException {
      // Store original model
      this.model = originalModel;

      // Create IK tool
      ikTool = new IKTool();
      ikTool.setModel(model);

      ikCommonModel = new IKCommonModel(model);
      ikCommonModel.addObserver(this);
   }

   public Model getModel() { return model; }
   public IKTool getIKTool() { return ikTool; }
   public IKCommonModel getIKCommonModel() { return ikCommonModel; }
   
   //------------------------------------------------------------------------
   // Setting the motion in the model
   //------------------------------------------------------------------------
   private void updateMotion(Storage newMotion) {
      if(motion!=null) {
         MotionsDB.getInstance().closeMotion(getModel(), motion);
      }
      motion = newMotion;
      if(motion!=null) {
         MotionsDB.getInstance().addMotion(getModel(), motion);
      }
   }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   private void updateIKTool() {
      ikCommonModel.toIKTool(ikTool);
      ikTool.setPrintResultFiles(false);
   }

   public void execute() {
      if(isModified() && worker==null) {
         worker = new IKToolWorker();
         worker.start();
      }
   }

   // TODO: may need to use locks and such to ensure that worker doesn't get set to null (by IKToolWorker.finished()) in between worker!=null check and worker.interrupt()
   // But I think both will typically run on the swing thread so probably safe
   public void interrupt(boolean promptToKeepPartialResult) {
      if(worker!=null) worker.interrupt(promptToKeepPartialResult);
   }

   public void cancel() {
      System.out.println("IKToolModel.cancel");
      interrupt(false);
      updateMotion(null);
   }

   //------------------------------------------------------------------------
   // Handle updates in the IK Task Set
   //------------------------------------------------------------------------

   public void update(Observable observable, Object obj) {
      if(observable==ikCommonModel) setModified(Operation.IKTaskSetChanged);
   }

   //------------------------------------------------------------------------
   // Execution status
   //------------------------------------------------------------------------

   private void setExecuting(boolean executing) {
      this.executing = executing;
      setChanged();
      notifyObservers(Operation.ExecutionStateChanged);
   }
   public boolean isExecuting() {
      return executing;
   }

   //------------------------------------------------------------------------
   // Modified flag
   //------------------------------------------------------------------------

   private void setModified(Operation change) {
      modifiedSinceLastExecute = true;
      setChanged(); // need to call this before calling notifyObservers
      notifyObservers(change);
   }
   private void resetModified() {
      modifiedSinceLastExecute = false;
   }
   public boolean isModified() {
      return modifiedSinceLastExecute;
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public boolean isValid() {
      return ikCommonModel.isValid();
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------
   
   private void relativeToAbsolutePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();
      for(int i=0; i<ikTool.getIKTrialSet().getSize(); i++) {
         IKTrial trial = ikTool.getIKTrialSet().get(i);
         trial.setMarkerDataFileName(FileUtils.makePathAbsolute(trial.getMarkerDataFileName(),parentDir));
         trial.setCoordinateFileName(FileUtils.makePathAbsolute(trial.getCoordinateFileName(),parentDir));
      }
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      IKTool newIKTool = null;
      try {
         newIKTool = new IKTool(fileName, model);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }
      ikTool = newIKTool;
      relativeToAbsolutePaths(fileName);

      // keep internal data in sync
      modifiedSinceLastExecute = true;

      ikCommonModel.fromIKTool(ikTool);

      setModified(Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      updateIKTool();
      ikTool.print(fileName);
      return true;
   }
}
