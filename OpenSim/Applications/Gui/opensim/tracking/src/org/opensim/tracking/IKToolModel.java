/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
import org.opensim.view.motions.MotionsDB;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;
import org.opensim.view.motions.JavaMotionDisplayerCallback;

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
      private Model modelCopy = null;
     
      IKToolWorker() throws Exception {
         updateIKTool();

         // Operate on a copy of the model -- this way if users play with parameters in the GUI it won't affect the model we're actually computing on
         modelCopy = new Model(getOriginalModel()); //For now create from 
         modelCopy.setInputFileName("");
         modelCopy.setup();
         ikTool.setModel(modelCopy);

         // We assume we're working with trial 0.  No support for dealing with other trials in the trial set right now.
         if (!ikTool.initializeTrial(0))
            throw new Exception("Inverse kinematics tool initialization failed -- check messages window for more details.");

         // Make no motion be currently selected (so model doesn't have extraneous ground forces/experimental markers from
         // another motion show up on it)
         MotionsDB.getInstance().clearCurrent();

         // Initialize progress bar, given we know the number of frames to process
         IKTrial trial = ikTool.getIKTrialSet().get(0);
         int startFrame = trial.getStartFrame();
         int endFrame = trial.getEndFrame();
         progressHandle = ProgressHandleFactory.createHandle("Executing inverse kinematics...",
                              new Cancellable() {
                                 public boolean cancel() {
                                    interrupt(true);
                                    return true;
                                 }
                              });

         // Animation callback will update the display during IK solve
         animationCallback = new JavaMotionDisplayerCallback(modelCopy, getOriginalModel(), ikTool.getIKTrialSet().get(0).getOutputStorage(), progressHandle);
         animationCallback.setModelForDisplaySetConfiguration(false);
         modelCopy.addIntegCallback(animationCallback);
         animationCallback.setStepInterval(1);
         animationCallback.startProgressUsingSteps(1, endFrame-startFrame+1);
         animationCallback.setOptimizerAlgorithm(ikTool.getIKTrialSet().get(0).getOptimizerAlgorithm());

         // Do this manouver (there's gotta be a nicer way) to create the object so that C++ owns it and not Java (since 
         // removeIntegCallback in finished() will cause the C++-side callback to be deleted, and if Java owned this object
         // it would then later try to delete it yet again)
         interruptingCallback = InterruptingIntegCallback.safeDownCast((new InterruptingIntegCallback()).copy());
         modelCopy.addIntegCallback(interruptingCallback);

         setExecuting(true);
      }

      public void interrupt(boolean promptToKeepPartialResult) {
         this.promptToKeepPartialResult = promptToKeepPartialResult;
         if(interruptingCallback!=null) interruptingCallback.interrupt();
      }

      public Object construct() {
         result = ikTool.solveTrial(0);

         return this;
      }

      public void finished() {
         progressHandle.finish();

         // Clean up motion displayer (this is necessary!)
         animationCallback.cleanupMotionDisplayer();

         modelCopy.removeIntegCallback(animationCallback);
         modelCopy.removeIntegCallback(interruptingCallback);
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

         modelCopy = null;
         worker = null;
      }
   }
   private IKToolWorker worker = null;
   //========================================================================
   // END IKToolWorker
   //========================================================================

   enum Operation { AllDataChanged, IKTrialNameChanged, IKTaskSetChanged, ExecutionStateChanged };

   private IKTool ikTool = null;
   private Model originalModel = null;
   private boolean modifiedSinceLastExecute = true;
   private IKCommonModel ikCommonModel;
   private Storage motion = null;
   private boolean executing = false;
   private String trialName = "ik trial";
   private boolean cleanupAfterExecuting = false;  // Keep track if cleaning up needs to be done on execution finish vs. dialog close

   public IKToolModel(Model originalModel) throws IOException {
      // Store original model
      this.originalModel = originalModel;

      // Create IK tool
      ikTool = new IKTool();
      addTrialIfNecessary();

      ikCommonModel = new IKCommonModel(originalModel);
      ikCommonModel.addObserver(this);
   }

   public Model getOriginalModel() { return originalModel; }
   public IKTool getIKTool() { return ikTool; }
   public IKCommonModel getIKCommonModel() { return ikCommonModel; }

   private void addTrialIfNecessary() {
      if(ikTool.getIKTrialSet().getSize()==0) {
         ikTool.getIKTrialSet().append(IKTrial.safeDownCast(new IKTrial().copy()));
      }
   }
   
   //------------------------------------------------------------------------
   // IK trial name
   //------------------------------------------------------------------------
   public String getTrialName() {
      return trialName;
   }
   public void setTrialName(String trialName) {
      if(!this.trialName.equals(trialName)) {
         this.trialName = trialName;
         setModified(Operation.IKTrialNameChanged);
      }
   }

   //------------------------------------------------------------------------
   // Setting the motion in the model
   //------------------------------------------------------------------------
   private void updateMotion(Storage newMotion) {
      if(motion!=null) {
         MotionsDB.getInstance().closeMotion(getOriginalModel(), motion, false, false);
      }
      motion = newMotion;
      if(motion!=null) {
         MotionsDB.getInstance().addMotion(getOriginalModel(), motion);
         //MotionControlJPanel.getInstance().setUserTime(motion.getLastTime());
         MotionsDB.getInstance().setMotionModified(motion, true);
      }
   }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   private void updateIKTool() {
      ikCommonModel.toIKTool(ikTool);
      ikTool.setPrintResultFiles(false);
      if(ikTool.getIKTrialSet().getSize()>0) ikTool.getIKTrialSet().get(0).setName(trialName);
   }

   public void execute() {
      if(isModified() && worker==null) {
         try {
            worker = new IKToolWorker();
            worker.start();
         } catch (Exception ex) {
            DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message(ex.getMessage(), NotifyDescriptor.ERROR_MESSAGE));
            worker = null;
         }
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
   // Handle updates in the IK Task Set
   //------------------------------------------------------------------------

   public void update(Observable observable, Object obj) {
      if(observable==ikCommonModel) setModified(Operation.IKTaskSetChanged);
   }

   //------------------------------------------------------------------------
   // Execution status
   //------------------------------------------------------------------------

   private void setExecuting(boolean executing) {
      if(this.executing != executing) {
         this.executing = executing;
         setChanged();
         notifyObservers(Operation.ExecutionStateChanged);
      }
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

   private void AbsoluteToRelativePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();
      for(int i=0; i<ikTool.getIKTrialSet().getSize(); i++) {
         IKTrial trial = ikTool.getIKTrialSet().get(i);
         trial.setMarkerDataFileName(FileUtils.makePathRelative(trial.getMarkerDataFileName(),parentDir));
         trial.setCoordinateFileName(FileUtils.makePathRelative(trial.getCoordinateFileName(),parentDir));
      }
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      IKTool newIKTool = null;
      try {
         newIKTool = new IKTool(fileName, false);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }
      ikTool = newIKTool;
      addTrialIfNecessary();
      relativeToAbsolutePaths(fileName);

      ikCommonModel.fromIKTool(ikTool);

      if(ikTool.getIKTrialSet().getSize()>0) trialName = ikTool.getIKTrialSet().get(0).getName();

      setModified(Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      XMLExternalFileChooserHelper helper = new XMLExternalFileChooserHelper(fileName);
      helper.addObject(ikTool.getIKTaskSet(), "IK Task Set");
      if(!helper.promptUser()) return false;
      updateIKTool();
      AbsoluteToRelativePaths(fileName);
      ikTool.print(fileName);
      relativeToAbsolutePaths(fileName);
      return true;
   }
   
   void cleanup() {
      if (isExecuting()){
         cleanupAfterExecuting = true;
      }
      else{
         ikCommonModel.deleteObservers();
         ikCommonModel=null;
         ikTool = null;
         System.gc();
      }
   }
}
