package org.opensim.motionviewer;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Vector;
import javax.swing.DefaultBoundedRangeModel;
import javax.swing.SwingUtilities;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.pub.ViewDB;

// End of variables declaration                   

class MotionFrame{
   private int motionNumber;
   private int frameNumber;
   private double frameTime;

   public MotionFrame(int motionNumber, int frameNumber, double frameTime)
   {
      this.motionNumber=motionNumber;
      this.frameNumber=frameNumber;
      this.frameTime=frameTime;
   }
   public int getMotionNumber() {
      return motionNumber;
   }
   public int getFrameNumber() {
      return frameNumber;
   }
   public double getFrameTime() {
      return frameTime;
   }   
}

public class MasterMotionModel{

   // Info specific to a motion/model combination is pushed down to the displayer object.
   private DefaultBoundedRangeModel sliderModel = new DefaultBoundedRangeModel();
   List<MotionDisplayer> displayers=new ArrayList<MotionDisplayer>(10);  
   private boolean wrapMotion=false;
   int currentMotion = 0; // Master slider switches between motions finding local frame numbers 
   int currentFrame = 0;   // in currentMotion
   double      startTime, endTime;
   // superMotion is the merged motion of multiple motions if many are displayed, otherwise
   // it's just a single motion.
   int         currentSuperFrame=0;       // index of current frame, motion in superMotion
   Vector<MotionFrame>   superMotion = new Vector<MotionFrame>(100); // One merged motion to work with
   
   MasterMotionModel() {
   }
   
   private void applyFrame(int currentFrame) {
      // Apply frame from file then update model display!
      final MotionDisplayer disp = displayers.get(currentMotion);
      disp.applyFrameToModel(currentFrame);
      SwingUtilities.invokeLater(new Runnable(){
         public void run(){
            AbstractModel dModel = disp.getModel();
            ViewDB.getInstance().getModelVisuals(dModel).updateModelDisplay(dModel);
            ViewDB.getInstance().repaintAll();
         }
         });
        
       System.out.println("motion, frame"+currentMotion+", "+currentFrame);
      //?getSliderModel().setValue(currentFrame);
   }
   
    public void back() {
       if (currentSuperFrame>=1){
          currentSuperFrame = currentSuperFrame-1;
          MotionFrame c = superMotion.get(currentSuperFrame);
          currentFrame = c.getFrameNumber();
          currentMotion = c.getMotionNumber();
       }
      else{
         currentSuperFrame= (wrapMotion) ? superMotion.size()-1 : currentSuperFrame;
          MotionFrame c = superMotion.get(currentSuperFrame);
          currentFrame = c.getFrameNumber();
          currentMotion = c.getMotionNumber();
     }
      applyFrame(currentFrame);
   }
   
   public void advance() {
      if (currentSuperFrame<=superMotion.size()-2){
         currentSuperFrame= currentSuperFrame+1;
          MotionFrame c = superMotion.get(currentSuperFrame);
          currentFrame = c.getFrameNumber();
          currentMotion = c.getMotionNumber();
      }
      else{
         currentSuperFrame= (wrapMotion) ? 0 : currentSuperFrame;
          MotionFrame c = superMotion.get(currentSuperFrame);
          currentFrame = c.getFrameNumber();
          currentMotion = c.getMotionNumber();
      }
      applyFrame(currentFrame);
   }
   
   
   public void setTime(double userTime) {
      // Find time for all motions and set it
      for(int i=0; i<displayers.size(); i++){
         MotionDisplayer md = displayers.get(i);
         currentFrame=md.getSimmMotionData().getFrameNumberForTime(userTime);
         currentMotion=i;
         applyFrame(currentFrame);
     }
     // Find superFrame
     if (userTime<superMotion.get(0).getFrameTime())
        currentSuperFrame=0;
     else if (userTime > superMotion.get(superMotion.size()-1).getFrameTime())
        currentSuperFrame=superMotion.size()-1;
     else { // search
         int i=0;
         while( i< superMotion.get(superMotion.size()-1).getFrameTime()){
            i++;
         }
         currentSuperFrame=i;
     }
   }

   public int getStartFrame() {
      return 0;
   }

   public int getLastFrame() {
      return superMotion.size()-1;
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
          startTime=1000.0;
          endTime=0.0;
          displayers.clear();
       }
       clear();
       displayers.add(new MotionDisplayer(simmMotionData, abstractModel));
       buildSuperMotion(abstractModel, simmMotionData, 0);
   }
   
   void addMerge(AbstractModel abstractModel, SimmMotionData simmMotionData) {
      int nextMotionNumber = displayers.size();
        displayers.add(new MotionDisplayer(simmMotionData, abstractModel));
       if (simmMotionData.getRangeMin() <startTime)
          startTime = simmMotionData.getRangeMin();
       if (simmMotionData.getRangeMax() >endTime)
          endTime = simmMotionData.getRangeMax();
       // updateBounds.
       buildSuperMotion(abstractModel, simmMotionData, displayers.size()-1);
   }

   public boolean finished(int direction) {
      if (currentSuperFrame==superMotion.size()-1 && direction==1 ||
              currentFrame==0 && direction==-1)
         return !wrapMotion;
      else
         return false;
   }

   public double getCurrentTime() {
      MotionFrame c = superMotion.get(currentSuperFrame);

      return c.getFrameTime();
   }

   void clear() {
     // unload previously loaded motion of the same model
     for(int i=0; i<displayers.size(); i++)
        displayers.get(i).cleanupDisplay();
     displayers.clear();
     superMotion.clear();  
     sliderModel = new DefaultBoundedRangeModel();
   }

   private void buildSuperMotion(AbstractModel model, SimmMotionData mot, int idx) {
      // need <time, frame number, motion number>.
      // Create a vector of motion frames and merge it with 
      int numFrames = mot.getNumberOfFrames();
      // Merge lists (superMotion, newFrames);
      if (superMotion.size()==0){   // Nothing to merge
         for(int i=0; i< numFrames; i++){
            double time = mot.getValue("time", i);
            MotionFrame newFrame = new MotionFrame(idx, i, time);
            // insert frame at position j and continue
            superMotion.add(newFrame);
         }
         return;
      }
      Vector<MotionFrame>   mergedMotion=new Vector<MotionFrame>(numFrames+superMotion.size());
      // Merge m,otions into one
      int j=0;
      for(int i=0; i< numFrames; i++){
         double time = mot.getValue("time", i);
         MotionFrame newFrame = new MotionFrame(idx, i, time);
         while(superMotion.get(j).getFrameTime()<time && j<superMotion.size()-1){
            mergedMotion.add(superMotion.get(j));
            System.out.println("Add frame "+
                    superMotion.get(j).getFrameNumber()+" from motion "+
                    superMotion.get(j).getMotionNumber()+" at time"+
                    superMotion.get(j).getFrameTime());
            j++;
         }
         mergedMotion.add(newFrame);
         //System.out.println("Add frame "+i+" from motion "+idx+" at time"+time);
      }
       while (j < superMotion.size()-1){
            mergedMotion.add(superMotion.get(j));
            System.out.println("Add frame "+
                    superMotion.get(j).getFrameNumber()+" from motion "+
                    superMotion.get(j).getMotionNumber()+" at time"+
                    superMotion.get(j).getFrameTime());
            j++;
      }
      superMotion = mergedMotion;
   }
   /**
    * How many motions currently playing/ready to play
    */
   int getNumMotions() {
      return displayers.size();
   }

   String getDisplayName() {
      if (getNumMotions()==0)
         return "None";
      if (getNumMotions()==1)
         return displayers.get(0).getSimmMotionData().getName();
      else 
         return "Multiple";
   }

   double getStartTime()
   {
      return startTime;
   }
   double getEndTime()
   {
      return endTime;
   }
}