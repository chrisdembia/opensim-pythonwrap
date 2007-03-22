package org.opensim.motionviewer;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Vector;
import javax.swing.DefaultBoundedRangeModel;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import org.opensim.modeling.Model;
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

public class MasterMotionModel extends DefaultBoundedRangeModel{

   // Info specific to a motion/model combination is pushed down to the displayer object.
   List<MotionDisplayer> displayers=new ArrayList<MotionDisplayer>(10);  
   private boolean wrapMotion=false;
   int currentMotion = 0; // Master slider switches between motions finding local frame numbers 
   int currentFrame = 0;   // in currentMotion
   //double      startTime, endTime;
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
            Model dModel = disp.getModel();
            ViewDB.getInstance().getModelVisuals(dModel).updateModelDisplay(dModel);
            ViewDB.getInstance().repaintAll();
         }
         });
        
       //System.out.println("motion, frame"+currentMotion+", "+currentFrame);
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
      setValue(currentSuperFrame);
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
      setValue(currentSuperFrame);
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
         while( i< (superMotion.size()-1) && superMotion.get(i).getFrameTime()<userTime){
            i++;
         }
         currentSuperFrame=i;
     }
      setValue(currentSuperFrame);
   }

   public boolean isWrapMotion() {
      return wrapMotion;
   }

   public void setWrapMotion(boolean wrapMotion) {
      this.wrapMotion = wrapMotion;
   }

   void add(Model abstractModel, SimmMotionData simmMotionData) {
      
      if (displayers.size() != 0){
           // unload previously loaded motion of the same model
          for(int i=0; i<displayers.size(); i++)
           displayers.get(i).cleanupDisplay();
          //startTime=1000.0;
          //endTime=0.0;
          displayers.clear();
       }
       clear();
       displayers.add(new MotionDisplayer(simmMotionData, abstractModel));
       buildSuperMotion(abstractModel, simmMotionData, 0);
       updateBounds();
   }
   
   void addMerge(Model abstractModel, SimmMotionData simmMotionData) {
      int nextMotionNumber = displayers.size();
        displayers.add(new MotionDisplayer(simmMotionData, abstractModel));
       /*if (simmMotionData.getRangeMin() <startTime)
          startTime = simmMotionData.getRangeMin();
       if (simmMotionData.getRangeMax() >endTime)
          endTime = simmMotionData.getRangeMax();*/
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
     currentSuperFrame=0;
   }

   private void buildSuperMotion(Model model, SimmMotionData mot, int idx) {
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
         updateBounds();
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
            j++;
         }
         mergedMotion.add(newFrame);
         //System.out.println("Add frame "+i+" from motion "+idx+" at time"+time);
      }
       while (j < superMotion.size()-1){
            mergedMotion.add(superMotion.get(j));
            j++;
      }
      superMotion = mergedMotion;
      updateBounds();
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
      if (superMotion.size()>0)
         return superMotion.get(0).getFrameTime();
      else
         return 0.0;
   }
   double getEndTime()
   {
      if (superMotion.size()>0)
         return superMotion.get(superMotion.size()-1).getFrameTime();
      else
         return 0.0;
   }

   /**
    * Make labels for slider at 0, 25, 50, 75, 100% of time labeled with time
    **/
   Hashtable makeLabels() {
      // Go thru stored frames in superMotion and create 5 entries
      Hashtable labels = new Hashtable(5);
      int numFrames =  superMotion.size();
      if (numFrames <5){
         for(int i=0; i<5; i++){
            MotionFrame c = superMotion.get(i);
            String label = Double.toString(c.getFrameTime());
            if (label.length()>5) label=label.substring(0, 5);
            labels.put(new Integer(25*i), new JLabel(label));
         }
      }
      else {
         for(int i=0; i<5; i++){
            MotionFrame c = superMotion.get((numFrames-1)*i/4);
            String label = Double.toString(c.getFrameTime());
            if (label.length()>5) label=label.substring(0, 5);
            labels.put((numFrames-1)*i/4, new JLabel(label));
         }
      }
      return labels;
   }
   /**
    * Apply a frame based on the user moving the slider
    */
   void setFrameNumber(int userSelectedFrame) {
      setValue(userSelectedFrame);  // update Range model
      applySuperFrame(userSelectedFrame); // update display
   }

   private void applySuperFrame(int superFrame) {
      if (superFrame != currentSuperFrame){
         currentSuperFrame = superFrame;
         MotionFrame c = superMotion.get(currentSuperFrame);
         currentFrame = c.getFrameNumber();
         currentMotion = c.getMotionNumber();
         applyFrame(currentFrame);  
      }
   }

   private void updateBounds() {
      setRangeProperties(currentSuperFrame, 0, 0, superMotion.size()-1, false);
   }
}