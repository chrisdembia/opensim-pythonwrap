/*
 * JavaMotionDisplayerCallback.java
 *
 * Created on April 4, 2007, 8:35 AM
 *
 * Copyright (c)  2006, Stanford University and Ayman Habib. All rights reserved.
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

package org.opensim.view.motions;

import java.lang.reflect.InvocationTargetException;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.opensim.modeling.*;
import org.opensim.view.SingleModelVisuals;
import org.opensim.view.motions.MotionDisplayer;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman Habib
 */
public class JavaMotionDisplayerCallback extends AnalysisWrapper {
   Storage storage = null;
   MotionDisplayer motionDisplayer = null;
   ProgressHandle progressHandle = null;

   boolean progressUsingTime = true;
   double startTime = 0.;
   double endTime = 1.;
   static final double progressTimeResolution = 1e2;
   int startStep = 0;
   int endStep = 1;
   int lastProgressStep = -1;
   double lastRenderTime = -1e10;
   double minRenderTimeInterval = -1;
   double startIKTime = getCurrentRealTime();
   double stopIKTime = 0;
   double startDisplayTime = 0;
   double stopDisplayTime = 0;
   double minSimTime = -1;
   double currentSimTime = 0;
   String optimizerAlgorithm = "";
   OpenSimContext context = null;
   OpenSimContext simulationContext = null; // Corresponding to actual model being run
   Model modelForDisplay=null;
   boolean ownsStorage=false;
   int numStates=0;
   ArrayStr stateLabels=null;
   private double[] statesBuffer;
   
   // Creates a new instance of JavaMotionDisplayerCallback 
   public JavaMotionDisplayerCallback(Model aModel, Storage aStorage, ProgressHandle progressHandle) {
      super(aModel);
      modelForDisplay=aModel;
      context = OpenSimDB.getInstance().getContext(aModel);
      if(storage!=null) {
         this.storage = aStorage;
      }
      else 
            createResultStorage();
      
      motionDisplayer = new MotionDisplayer(storage, getModelForDisplay());
      this.progressHandle = progressHandle;
   }

    private void createResultStorage() {
        storage = new Storage();
        storage.setName("Results");
        stateLabels = new ArrayStr();
        getModelForDisplay().getStateNames(stateLabels);
        stateLabels.insert(0, "time");
        storage.setColumnLabels(stateLabels);
        numStates = getModelForDisplay().getNumStates();
        statesBuffer = new double[numStates];
        ownsStorage=true;
    }
   
   public JavaMotionDisplayerCallback(Model aModel, Model aModelForDisplay, Storage aStorage, ProgressHandle progressHandle) {
      super(aModel);
      modelForDisplay=aModelForDisplay;
      context = OpenSimDB.getInstance().getContext(aModelForDisplay);
      if(aStorage!=null) {
         this.storage = aStorage;
      }
      else
          createResultStorage();
      motionDisplayer = new MotionDisplayer(storage, getModelForDisplay());
      this.progressHandle = progressHandle;
   }

   // In seconds
   public void setMinRenderTimeInterval(double interval) { minRenderTimeInterval = interval; }

   public void setRenderMuscleActivations(boolean render) {
      if(getModelForDisplayCompatibleStates()) {
        SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(getModelForDisplay());
        if(vis!=null) vis.setRenderMuscleActivations(render);
      }
   }

   public void startProgressUsingTime(double startTime, double endTime) {
      progressUsingTime = true;
      this.startTime = startTime;
      this.endTime = endTime;
      if(progressHandle!=null) progressHandle.start((int)((endTime-startTime)*progressTimeResolution));
   }

   public void startProgressUsingSteps(int startStep, int endStep) {
      progressUsingTime = false;
      this.startStep = startStep;
      this.endStep = endStep;
      //OpenSim20 if(progressHandle!=null) progressHandle.start(endStep-startStep+1);
   }
   
   public void setOptimizerAlgorithm(String aOptimizerAlgorithm) {
       optimizerAlgorithm = IO.Uppercase(aOptimizerAlgorithm);
   }

   private double getCurrentRealTime() {
      return 1e-9*System.nanoTime();
   }

   public void updateDisplaySynchronously() {
      try {
         SwingUtilities.invokeAndWait(new Runnable(){
            public void run() {
               double currentRealTime = getCurrentRealTime();
               if(minRenderTimeInterval<=0 || currentRealTime-lastRenderTime>minRenderTimeInterval) {
                  if(motionDisplayer!=null && storage.getSize()>0) 
                      motionDisplayer.applyFrameToModel(storage.getSize()-1);            
                  ViewDB.getInstance().updateModelDisplay(getModelForDisplay());  // Faster? than the next few indented lines
                    //ViewDB.getInstance().updateModelDisplayNoRepaint(getModelForDisplay());
                    ////ViewDB.getInstance().renderAll(); // Render now (if want to do it later, use repaintAll()) -- may slow things down too much
                    //ViewDB.getInstance().repaintAll();
                  lastRenderTime = currentRealTime; 
                  //System.out.println("REPAINTED");
               }
              }});                      
      } 
      catch (InterruptedException ex) {
         ex.printStackTrace();
      } catch (InvocationTargetException ex) {
         ex.printStackTrace();
      }
   }
   
   public void processStep(SWIGTYPE_p_SimTK__State s) {
      if(!getOn()) return;
      super.step(s, 0);
      if(progressHandle!=null) {
         int progressStep = (int)((getSimulationTime()-startTime)*progressTimeResolution);
         if(progressStep > lastProgressStep) { // make sure we only advance progress (else an exception is thrown)
            progressHandle.progress(progressStep);
            lastProgressStep = progressStep;
         }
      }
      currentSimTime = getSimulationTime();   
      if (ownsStorage) {    // Callback is the one accumulating results //ASSERTS downlstream 0327
          // Need to make sure nextResult is not Freed by gc
          StateVector nextResult = new StateVector();
          super.getStates(statesBuffer);
          System.out.println("Simulation time="+currentSimTime+" state[0]="+statesBuffer[0]);
          nextResult.setStates(currentSimTime, numStates, statesBuffer);
          storage.append(nextResult);
      }
      if(true) {
          stopIKTime = getCurrentRealTime(); // Stop timing of ik computations
          startDisplayTime = getCurrentRealTime(); // Start timing of display update
          updateDisplaySynchronously();
          stopDisplayTime = getCurrentRealTime();  // Stop timing of display update
          if(optimizerAlgorithm != null && optimizerAlgorithm.equals("JACOBIAN")) {
              minSimTime = currentSimTime+(stopDisplayTime-startDisplayTime)+(stopIKTime-startIKTime);  // Set minimum simulation time for next display update 
          }
          //System.out.println("minSimTime = "+currentSimTime+" + "+(stopDisplayTime-startDisplayTime)+" + "+(stopIKTime-startIKTime)+" = "+minSimTime);
          //System.out.println(optimizerAlgorithm);
          startIKTime = getCurrentRealTime(); // Start timing of ik computations
      }
   }
   
   public void cleanupMotionDisplayer() {
      setRenderMuscleActivations(false);
      if(motionDisplayer!=null) motionDisplayer.cleanupDisplay();
      ViewDB.getInstance().repaintAll();
   }

   protected void finalize() {
      super.finalize();
   }
   
    public void setStepInterval(int i) {
        //throw new UnsupportedOperationException("Not yet implemented");
    }

    private Model getModelForDisplay() {
        return modelForDisplay;//get_model();
    }

    private boolean getModelForDisplayCompatibleStates() {
        return false;
    }

    public int step(SWIGTYPE_p_SimTK__State s) {
        int retValue;
        retValue = super.step(s, 0);
        processStep(s);
        return retValue;
    }

    public int begin(SWIGTYPE_p_SimTK__State s) {
        int retValue=0;
        
        //retValue = super.begin(s);
        return retValue;
    }

    private double getCurrentTime() {
        return context.getTime();
    }

    public Storage getStateStorage() {
        return storage;
    }
    
    
}
