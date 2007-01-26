package org.opensim.motionviewer;

import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import javax.swing.DefaultBoundedRangeModel;
import javax.swing.SwingUtilities;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.SimmMotionData;
import org.opensim.motionviewer.MotionDisplayer;
import org.opensim.motionviewer.MotionEvent;
import org.opensim.motionviewer.MotionEvent.Operation;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.view.pub.ViewDB;

// End of variables declaration                   


class MasterMotionModel{

   int currentFrame = 0;
   SimmMotionData simmMotionData;
   private DefaultBoundedRangeModel sliderModel = new DefaultBoundedRangeModel();
   MotionDisplayer displayer=null;  // null indicates no motion
   private boolean wrapMotion=false;
   
   MasterMotionModel() {
   }
   
   public void applyFrame(int currentFrame) {
      // Apply frame from file then update model display!
      this.currentFrame=currentFrame;
      displayer.applyFrameToModel(currentFrame, simmMotionData);
      SwingUtilities.invokeLater(new Runnable(){
         public void run(){
            ViewDB.getInstance().getModelVisuals(displayer.getModel()).updateModelDisplay(displayer.getModel());
            ViewDB.getInstance().repaintAll();
         }
         });
      getSliderModel().setValue(currentFrame);
   }
   
   public void back() {
     if (currentFrame>=1)
         currentFrame= currentFrame-1;
      else
         currentFrame= (wrapMotion) ? simmMotionData.getNumberOfFrames()-1 : currentFrame;
      applyFrame(currentFrame);
   }
   
   public void advance() {
      if (currentFrame<=simmMotionData.getNumberOfFrames()-2)
         currentFrame= currentFrame+1;
      else
         currentFrame= (wrapMotion) ? 0 : currentFrame;
      applyFrame(currentFrame);
   }
   
   
   public void setTime(double userTime) {
      currentFrame=simmMotionData.getFrameNumberForTime(userTime);
      applyFrame(currentFrame);
   }

   public int getStartFrame() {
      return 0;
   }

   public int getLastFrame() {
      return simmMotionData.getNumberOfFrames()-1;
   }

   public boolean isWrapMotion() {
      return wrapMotion;
   }

   public void setWrapMotion(boolean wrapMotion) {
      this.wrapMotion = wrapMotion;
   }

   public DefaultBoundedRangeModel getSliderModel() {
      return sliderModel;
   }

   void add(AbstractModel abstractModel, SimmMotionData simmMotionData) {
       if (displayer != null){
           // unload previously loaded motion of the same model
           displayer.cleanupDisplay();
       }
       displayer = new MotionDisplayer(simmMotionData, abstractModel);
       this.simmMotionData=simmMotionData;
   }

   boolean finished(int direction) {
      if (currentFrame==simmMotionData.getNumberOfFrames()-1 && direction==1 ||
              currentFrame==0 && direction==-1)
         return !wrapMotion;
      else
         return false;
   }

   public double getCurrentTime() {
      return simmMotionData.getValue("time", currentFrame);
   }
   
}