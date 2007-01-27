package org.opensim.motionviewer;

import java.util.Vector;
import javax.swing.DefaultBoundedRangeModel;
import javax.swing.SwingUtilities;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.pub.ViewDB;

// End of variables declaration                   


class MasterMotionModel{

   int currentMotion=0; // Master slider switches between motions finding local frame numbers 
   // Info specific to a motion/model combination is pushed down to the displayer object.
   private DefaultBoundedRangeModel sliderModel = new DefaultBoundedRangeModel();
   Vector<MotionDisplayer> displayers=new Vector<MotionDisplayer>(10);  
   private boolean wrapMotion=false;
   int currentFrame = 0;
   
   MasterMotionModel() {
   }
   
   public void applyFrame(int currentFrame) {
      // Apply frame from file then update model display!
      this.currentFrame=currentFrame;
      displayers.get(currentMotion).applyFrameToModel(currentFrame);
      SwingUtilities.invokeLater(new Runnable(){
         public void run(){
            AbstractModel dModel = displayers.get(currentMotion).getModel();
            ViewDB.getInstance().getModelVisuals(dModel).updateModelDisplay(dModel);
            ViewDB.getInstance().repaintAll();
         }
         });
      getSliderModel().setValue(currentFrame);
      if (displayers.size()>1){
         int numMotions = displayers.size();
         currentMotion++;
         if (currentMotion==numMotions)
            currentMotion=0;
      }
   }
   
   public void back() {
     if (currentFrame>=1)
         currentFrame= currentFrame-1;
      else
         currentFrame= (wrapMotion) ? displayers.get(currentMotion).getSimmMotionData().getNumberOfFrames()-1 : currentFrame;
      applyFrame(currentFrame);
   }
   
   public void advance() {
      if (currentFrame<=displayers.get(currentMotion).getSimmMotionData().getNumberOfFrames()-2)
         currentFrame= currentFrame+1;
      else
         currentFrame= (wrapMotion) ? 0 : currentFrame;
      applyFrame(currentFrame);
   }
   
   
   public void setTime(double userTime) {
      currentFrame=displayers.get(currentMotion).getSimmMotionData().getFrameNumberForTime(userTime);
      applyFrame(currentFrame);
   }

   public int getStartFrame() {
      return 0;
   }

   public int getLastFrame() {
      return displayers.get(currentMotion).getSimmMotionData().getNumberOfFrames()-1;
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
       if (displayers.size() != 0){
           // unload previously loaded motion of the same model
          for(int i=0; i<displayers.size(); i++)
           displayers.get(i).cleanupDisplay();
       }
       displayers.clear();
       displayers.add(0, new MotionDisplayer(simmMotionData, abstractModel));
   }

   void add(AbstractModel abstractModel, SimmMotionData simmMotionData, boolean merge) {
       displayers.add( new MotionDisplayer(simmMotionData, abstractModel));
   }

   boolean finished(int direction) {
      if (currentFrame==displayers.get(currentMotion).getSimmMotionData().getNumberOfFrames()-1 && direction==1 ||
              currentFrame==0 && direction==-1)
         return !wrapMotion;
      else
         return false;
   }

   public double getCurrentTime() {
      return displayers.get(currentMotion).getSimmMotionData().getValue("time", currentFrame);
   }

   void clear() {
       if (displayers.size()!=0){
           // unload previously loaded motion of the same model
          for(int i=0; i<displayers.size(); i++)
           displayers.get(i).cleanupDisplay();
       }
      sliderModel = new DefaultBoundedRangeModel();
   }
   
}