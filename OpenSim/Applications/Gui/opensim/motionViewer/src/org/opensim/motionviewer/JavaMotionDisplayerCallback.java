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

package org.opensim.motionviewer;

import java.lang.reflect.InvocationTargetException;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.opensim.modeling.*;
import org.opensim.view.SingleModelVisuals;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman Habib
 */
public class JavaMotionDisplayerCallback extends SimtkAnimationCallback{
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
   String optimizerAlgorithm = null;

   /** Creates a new instance of JavaMotionDisplayerCallback */
   public JavaMotionDisplayerCallback(Model aModel, Model aModelForDisplay, Storage storage, ProgressHandle progressHandle) {
      super(aModel, aModelForDisplay);
      if(storage!=null) {
         this.storage = storage;
         motionDisplayer = new MotionDisplayer(storage, getModelForDisplay());
      }
      this.progressHandle = progressHandle;
   }
   public JavaMotionDisplayerCallback(Model aModel, Storage storage, ProgressHandle progressHandle) {
      this(aModel, aModel, storage, progressHandle);
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
      if(progressHandle!=null) progressHandle.start(endStep-startStep+1);
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
                  if(motionDisplayer!=null && storage.getSize()>0) motionDisplayer.applyFrameToModel(storage.getSize()-1);            
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
   
   public void processStep(int step) {
      if(!getOn()) return;
      if(progressHandle!=null) {
         int progressStep = progressUsingTime ? (int)((getCurrentTime()-startTime)*progressTimeResolution) : step-startStep+1;
         if(progressStep > lastProgressStep) { // make sure we only advance progress (else an exception is thrown)
            progressHandle.progress(progressStep);
            lastProgressStep = progressStep;
         }
      }
      currentSimTime = getCurrentTime();   
      if(proceed(step) && currentSimTime>minSimTime) {
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
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT, SWIGTYPE_p_void aClientData) {
      int retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP, aDYDT, aClientData);
      processStep(aStep);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT) {
      int retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP, aDYDT);
      processStep(aStep);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP) {
      int retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP);
      processStep(aStep);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
      int retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY);
      processStep(aStep);
      return retValue;
   }
   public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
      int retValue = super.begin(aStep, aDT, aT, aX, aY);
      return retValue;
   }

   public void cleanupMotionDisplayer() {
      setRenderMuscleActivations(false);
      if(motionDisplayer!=null) motionDisplayer.cleanupDisplay();
      ViewDB.getInstance().repaintAll();
   }

   protected void finalize() {
      super.finalize();
   }
}
