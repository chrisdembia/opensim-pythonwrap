/*
 * JavaMotionDisplayerCallback.java
 *
 * Created on April 4, 2007, 8:35 AM
 *
 * Copyright (c) 2006, Stanford University and Ayman Habib. All rights reserved.
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

package org.opensim.motionviewer;

import java.lang.reflect.InvocationTargetException;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.opensim.modeling.*;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman Habib
 */
public class JavaMotionDisplayerCallback extends SimtkAnimationCallback{
   Storage storage = null;
   MotionDisplayer motionDisplayer = null;
   ProgressHandle progressHandle = null;
   int stepsProcessed = 0;

   /** Creates a new instance of JavaMotionDisplayerCallback */
   public JavaMotionDisplayerCallback(Model aModel, Storage storage, ProgressHandle progressHandle) {
      super(aModel);
      if(storage!=null) {
         this.storage = storage;
         motionDisplayer = new MotionDisplayer(storage, aModel);
      }
      this.progressHandle = progressHandle;
   }

   public void updateDisplaySynchronously() {
      try {
         SwingUtilities.invokeAndWait(new Runnable(){
            public void run() {
               ViewDB.getInstance().updateModelDisplay(getModel());
               if(motionDisplayer!=null) {
                  if(storage.getSize()>0) motionDisplayer.applyFrameToModel(storage.getSize()-1);
               }
            }});
      } catch (InterruptedException ex) {
         ex.printStackTrace();
      } catch (InvocationTargetException ex) {
         ex.printStackTrace();
      }
   }

   public void processStep(int step) {
      if(progressHandle!=null) progressHandle.progress(++stepsProcessed);
      if(proceed(step)) updateDisplaySynchronously();
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
      if(motionDisplayer!=null) motionDisplayer.cleanupDisplay();
   }

   protected void finalize() {
      super.finalize();
   }
}
