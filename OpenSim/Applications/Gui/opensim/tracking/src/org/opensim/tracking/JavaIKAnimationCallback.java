/*
 * JavaIKAnimationCallback.java
 *
 * Created on April 25, 2007, 5:48 PM
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

package org.opensim.tracking;

import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.IKTool;
import org.opensim.modeling.Model;
import org.opensim.modeling.SWIGTYPE_p_double;
import org.opensim.modeling.SWIGTYPE_p_void;
import org.opensim.modeling.Storage;
import org.opensim.plotter.JPlotterPanel;
import org.opensim.plotter.PlotCurve;
import org.opensim.plotter.PlotterException;
import org.opensim.view.JavaAnimationCallback;

/**
 *
 * @author Ayman Habib. Callback specialized for handling IK primarily to
 * display IK Errors in a plot.
 *
 * @Todo All methods should be moved down to JavaAnimationCallback except for 
 * processStep, setupPlotter.
 */
public class JavaIKAnimationCallback extends JavaAnimationCallback{
    
    IKTool ik;
    JPlotterPanel plotter;
    PlotCurve cv=null;
    Storage s;
    int timeIndex=-1;
    int errorsIndexInStorage=-1;
    String MAX_ERROR="MaxMarkerError";    
    ArrayDouble errors = new ArrayDouble(100);
    boolean firstTime=true;
    
    /** Creates a new instance of JavaIKAnimationCallback */
    public JavaIKAnimationCallback(Model model) {
        super(model);
    }
    
  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT, SWIGTYPE_p_void aClientData) {
      int retValue;
      retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP, aDYDT, aClientData);
      processStep(aT);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT) {
      int retValue;
      retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP, aDYDT);
       processStep(aT);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP) {
      int retValue;
      retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY, aYP);
       processStep(aT);
      return retValue;
   }
   
   public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
       int retValue;
       
       retValue = super.step(aXPrev, aYPrev, aYPPrev, aStep, aDT, aT, aX, aY);
       processStep(aT);
       return retValue;
    }

   private void processStep(final double aT) {
      // begin should have been called first but actully it is not!
      if (cv==null && firstTime){
          firstTime=false;
          setupPlotter();
      }
      // update Plotter if it's up'
      timeIndex = s.findIndex(aT);
      if (timeIndex>=0){
          double errSquared = s.getStateVector(timeIndex).getData().getitem(errorsIndexInStorage);
          if (cv != null)
              cv.addDataPoint((double)aT, errSquared);
      }
   }

    public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
        int retValue;
        
        retValue = super.begin(aStep, aDT, aT, aX, aY);
        setupPlotter();

        return retValue;
    }

    private void setupPlotter() {
        // Launch plotter 
       /*
        s = ik.getIKTrialSet().get(0).getOutputStorage();
        errorsIndexInStorage = s.getStateIndex(MAX_ERROR);
        // Create plotter dialog and display s, column for markerError
        try {
            plotter = new JPlotterPanel();
            cv = plotter.showOneCurveAgainstTime(getModel(), s, "IK errors", MAX_ERROR);
            DialogDescriptor dlg = new DialogDescriptor(plotter,"Plotter Dialog");
            dlg.setModal(false);
            DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
        } catch (PlotterException ex) { // This should never happen
            ex.printStackTrace();
        }
        **/
    }

    protected void finalize() {
        super.finalize();
    }

    void setTool(IKTool ik) {
        this.ik = ik;
    }
    
}
