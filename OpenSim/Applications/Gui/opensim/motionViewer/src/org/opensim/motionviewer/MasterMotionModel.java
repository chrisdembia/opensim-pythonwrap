package org.opensim.motionviewer;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import javax.swing.SwingUtilities;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.EventListenerList;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.view.pub.ViewDB;

// End of variables declaration                   

public class MasterMotionModel {

   // Info specific to a motion/model combination is pushed down to the displayer object.
   List<MotionDisplayer> displayers=new ArrayList<MotionDisplayer>(10);  
   private boolean wrapMotion=false;

   double currentTime=0; // this is the primary indicator of the current position
   Vector<Double> superMotionTimes = new Vector<Double>(100);

   private int cachedIndexClosestToCurrentTime=0;

   // -----------------------------------------------------------------------
   // Change listener stuff taken from DefaultColorSelectionModel.java
   // -----------------------------------------------------------------------
   protected transient ChangeEvent changeEvent = null;
   protected EventListenerList listenerList = new EventListenerList();
   public void addChangeListener(ChangeListener l) { listenerList.add(ChangeListener.class, l); }
   public void removeChangeListener(ChangeListener l) { listenerList.remove(ChangeListener.class, l); }
   protected void fireStateChanged()
   {
      Object[] listeners = listenerList.getListenerList();
      for (int i = listeners.length - 2; i >= 0; i -=2 ) {
         if (listeners[i] == ChangeListener.class) {
            if (changeEvent == null) {
               changeEvent = new ChangeEvent(this);
            }
            ((ChangeListener)listeners[i+1]).stateChanged(changeEvent);
         }
      }
   }
   // -----------------------------------------------------------------------

   MasterMotionModel() {
   }

   private void applyTime() 
   {
      if(displayers.size() == 0) return;

      for(int i=0; i<displayers.size(); i++) {
         displayers.get(i).applyTimeToModel(getCurrentTime());
      }

      // If in event dispatch thrread then execute synchronously
      if (SwingUtilities.isEventDispatchThread()){
         for(int i=0; i<displayers.size(); i++) {
            MotionDisplayer disp = displayers.get(i);
            Model dModel = disp.getModel();
            ViewDB.getInstance().updateModelDisplayNoRepaint(dModel);
         }
         //ViewDB.getInstance().repaintAll();
         ViewDB.getInstance().renderAll();
         MotionsDB motionsDB = MotionsDB.getInstance();
         motionsDB.reportTimeChange(getCurrentTime());
      }
      else {
         try {
            SwingUtilities.invokeAndWait(new Runnable(){
               public void run(){
                  for(int i=0; i<displayers.size(); i++) {
                     MotionDisplayer disp = displayers.get(i);
                     Model dModel = disp.getModel();
                     ViewDB.getInstance().updateModelDisplayNoRepaint(dModel);
                  }
                  ViewDB.getInstance().repaintAll();
                  MotionsDB motionsDB = MotionsDB.getInstance();
                  motionsDB.reportTimeChange(getCurrentTime());
               }
               });
         } catch (InvocationTargetException ex) {
            ex.printStackTrace();
         } catch (InterruptedException ex) {
            ex.printStackTrace();
         }
      }
   }

   private int getIndexClosestToCurrentTime()
   {
      int idx=cachedIndexClosestToCurrentTime; // shorter name for local variable...
      if(idx < 0 || idx >= superMotionTimes.size()) idx=0;
      if(currentTime >= superMotionTimes.get(idx).doubleValue()) {
         // search to the right
         int i=idx;
         while(i<superMotionTimes.size()-1 && currentTime>=superMotionTimes.get(i+1).doubleValue()) i++;
         if(i<superMotionTimes.size()-1) { 
            double left=superMotionTimes.get(i).doubleValue(), right=superMotionTimes.get(i+1).doubleValue();
            idx=(right-currentTime<currentTime-left)?i+1:i;
         } else idx=i;
      } else {
         // search to the left
         int i=idx;
         while(i>0 && currentTime<=superMotionTimes.get(i-1).doubleValue()) i--;
         if(i>0) {
            double left=superMotionTimes.get(i-1).doubleValue(), right=superMotionTimes.get(i).doubleValue();
            idx=(right-currentTime<currentTime-left)?i:i-1;
         } else idx=i;
      }
      cachedIndexClosestToCurrentTime=idx;
      return idx;
   }

   public boolean isWrapMotion() {
      return wrapMotion;
   }

   public void setWrapMotion(boolean wrapMotion) {
      this.wrapMotion = wrapMotion;
   }

   public boolean finished(int direction) {
      //int index = getIndexClosestToCurrentTime();
      //if (index==superMotionTimes.size()-1 && direction==1 || index==0 && direction==-1)
      if (currentTime==getEndTime() && direction==1 || currentTime==getStartTime() && direction==-1)
         return !wrapMotion;
      else
         return false;
   }

   public double getCurrentTime() {
      return currentTime;
   }

   // -----------------------------------------------------------------------
   // Utilities for building the super motion
   // -----------------------------------------------------------------------
   void add(Model abstractModel, Storage simmMotionData) {
      displayers.add(new MotionDisplayer(simmMotionData, abstractModel));
      buildSuperMotion(abstractModel, simmMotionData);
   }
   void add(MotionsDB.ModelMotionPair pair) {
      add(pair.model, pair.motion);
   }

   void clear() {
     // unload previously loaded motion of the same model
     for(int i=0; i<displayers.size(); i++)
        displayers.get(i).cleanupDisplay();
     displayers.clear();
     superMotionTimes.clear();  
     setTime(0);
     ViewDB.getInstance().repaintAll();
   }

   // TODO: get rid of third argument
   private void buildSuperMotion(Model model, Storage mot) {
      // Merge vector of valid times with times from passed in storage
      int numFrames = mot.getSize();
      Vector<Double> mergedTimes=new Vector<Double>(numFrames+superMotionTimes.size());
      int j=0;
      for(int i=0; i<numFrames; i++){
         double time = mot.getStateVector(i).getTime();
         while(j<superMotionTimes.size() && superMotionTimes.get(j).doubleValue()<=time) {
            mergedTimes.add(superMotionTimes.get(j));
            j++;
         }
         // avoid duplicate time values
         // TODO: use some threshold?
         if(mergedTimes.size()==0 || mergedTimes.lastElement().doubleValue()!=time) mergedTimes.add(time);
      }
      for(; j<superMotionTimes.size(); j++) 
         mergedTimes.add(superMotionTimes.get(j));
      superMotionTimes = mergedTimes;
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

   // -----------------------------------------------------------------------
   // Time range
   // -----------------------------------------------------------------------
   double getStartTime()
   {
      return superMotionTimes.size()>0 ? superMotionTimes.firstElement() : 0.0;
   }

   double getEndTime()
   {
      return superMotionTimes.size()>0 ? superMotionTimes.lastElement() : 0.0;
   }

   double clampedTime(double time)
   {
      return (time < getStartTime()) ? getStartTime() : (time > getEndTime()) ? getEndTime() : time;
   }

   // -----------------------------------------------------------------------
   // Main interface functions (for modifying time)
   // -----------------------------------------------------------------------
   public void back() {
      if (superMotionTimes.size() == 0) return;
      int index = getIndexClosestToCurrentTime();
      if (index > 0){
         index--;
      }
      else{
         index = (wrapMotion) ? superMotionTimes.size()-1 : index;
      }
      setTime(superMotionTimes.get(index));
   }
   
   public void advance() {
      if (superMotionTimes.size() == 0) return;
      int index = getIndexClosestToCurrentTime();
      if (index<superMotionTimes.size()-1){
         index++;
      }
      else{
         index = (wrapMotion) ? 0 : index;
      }
      setTime(superMotionTimes.get(index));
   }
  
   public void setTime(double userTime) {
      currentTime = clampedTime(userTime);
      applyTime();
      fireStateChanged();
   }

   public void advanceTime(double dt) {
      double time = getCurrentTime()+dt;
      if(wrapMotion) {
         double range=getEndTime()-getStartTime();
         if(range > 0) { // it may be that range==0 in case this is a single-frame motion
            while(time > getEndTime()) time-=range;
            while(time < getStartTime()) time+=range;
         }
      }
      setTime(time);
   }
}
