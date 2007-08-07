/*
 *
 * MotionsDB
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
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

import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;
import javax.swing.SwingUtilities;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.awt.StatusDisplayer;
import org.openide.nodes.Node;
import org.opensim.modeling.Model;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Storage;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.ModelEvent;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.pub.*;

/**
 *
 * @author Ayman
 */
public class MotionsDB extends Observable // Observed by other entities in motionviewer
        implements Observer {   // Observer OpenSimDB to sync. up when models are deleted
   
   public static class ModelMotionPair {
      public Model model;
      public Storage motion;
      public ModelMotionPair(Model model, Storage motion) { this.model = model; this.motion = motion; }
   }

   static MotionsDB instance;

   // Map model to an ArrayList of Motions linked with it
   Hashtable<Model, ArrayList<Storage>> mapModels2Motions =
           new Hashtable<Model, ArrayList<Storage>>(4);

   // More than one motion may be current if synchronizing motion
   Vector<ModelMotionPair> currentMotions = new Vector<ModelMotionPair>();
   
   /** Creates a new instance of MotionsDB */
   private MotionsDB() {
       OpenSimDB.getInstance().addObserver(this);
       addObserver(this); // Listen to our own events (used to update the explorer)
   }
   
   public static synchronized MotionsDB getInstance() {
      if (instance == null) {
         instance = new MotionsDB();
         
      }
      return instance;
   }

   /**
    * Load a motion file, and associate it with a model.
    * We try to associate the motion with current model first if something doesn't look
    * right (e.g. no coordinates or markers match, warn and ask user either to select another model
    * or abort loading.
    * A side effect of changing the model associated with a loaded motion is that the new model becomes
    * current.
    */
   public void loadMotionFile(String fileName) {
      Storage storage = null;
      try {
         storage = new Storage(fileName);
      } catch (IOException ex) {
         ex.printStackTrace();
         DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Could not read motion file "+fileName));
         return;
      }
      final Storage newMotion = storage;
      boolean associated = false;
      while(!associated){
         Model modelForMotion = OpenSimDB.getInstance().selectModel(OpenSimDB.getInstance().getCurrentModel());
         if (modelForMotion == null){ // user cancelled
            break;
         }
         // user selected a model, try to associate it
         if(MotionsDB.getInstance().motionAssociationPossible(modelForMotion, newMotion)){
            addMotion(modelForMotion, newMotion, true);
            StatusDisplayer.getDefault().setStatusText("Associated motion: "+newMotion.getName()+" to model: "+modelForMotion.getName());
            associated = true;
         } else { // Show error that motion couldn't be associated and repeat'
            DialogDisplayer.getDefault().notify( 
                    new NotifyDescriptor.Message("Could not associate motion to current model."));
            break;
         }
      }
   }
   
   /**
     * Criteria for associating motionto a model:
     * At least one genccord or marker (_tx?) in motion file/Storage
     */
   boolean motionAssociationPossible(Model modelForMotion, Storage newMotion) {
      ArrayStr coordinateNames = new ArrayStr();
      modelForMotion.getDynamicsEngine().getCoordinateSet().getNames(coordinateNames);
      int numCoordinates = coordinateNames.getSize();
      int numUsedColumns = 0;    // Keep track of how many columns correspond to Coords or Markers
      for(int i=0; i<numCoordinates; i++){
         if (newMotion.getStateIndex(coordinateNames.getitem(i))!=-1)
            numUsedColumns++;
      }
      ArrayStr markerNames = new ArrayStr();
      modelForMotion.getDynamicsEngine().getMarkerSet().getNames(markerNames);
      for(int i=0; i<markerNames.getSize(); i++){
         if ((newMotion.getStateIndex(markerNames.getitem(i)+"_tx")!=-1) ||
                 (newMotion.getStateIndex(markerNames.getitem(i)+"_Tx")!=-1) ||
                 (newMotion.getStateIndex(markerNames.getitem(i)+"_TX")!=-1))
            numUsedColumns++;
      }
     
      return (numUsedColumns>=1);  // At least one column makes sense
   }

   public void addMotion(Model model, Storage motion, boolean convertAngles) {
      if(convertAngles) model.getDynamicsEngine().convertDegreesToRadians(motion);

      // Add to mapModels2Motion
      ArrayList<Storage> motions = mapModels2Motions.get(model);
      if(motions==null) { // First motion for model
         motions = new ArrayList<Storage>(4);
         mapModels2Motions.put(model, motions);
      }
      motions.add(motion);

      MotionEvent evt = new MotionEvent(this, model, motion, MotionEvent.Operation.Open);
      setChanged();
      notifyObservers(evt);

      setCurrent(model, motion); // Also make it current (a separate event is sent out)
   }

   public void addMotion(Model model, Storage motion) {
      addMotion(model, motion, false);
   }

   public void clearCurrent() {
      clearCurrentMotions();
      MotionEvent evt = new MotionEvent(this, MotionEvent.Operation.CurrentMotionsChanged);
      setChanged();
      notifyObservers(evt);
   }

   public void setCurrent(Model model, Storage motion) {
      setCurrentMotion(new ModelMotionPair(model, motion));
      MotionEvent evt = new MotionEvent(this, MotionEvent.Operation.CurrentMotionsChanged);
      setChanged();
      notifyObservers(evt);
   }

   public void setCurrent(Vector<ModelMotionPair> motions) {
      setCurrentMotions(motions);
      MotionEvent evt = new MotionEvent(this, MotionEvent.Operation.CurrentMotionsChanged);
      setChanged();
      notifyObservers(evt);
   }

   public void closeMotion(Model model, Storage simmMotionData) {
      ArrayList<Storage> motions = mapModels2Motions.get(model);
      if(motions!=null) { // Shouldn't be null, but just in case...
         motions.remove(simmMotionData);
      }

      boolean removed = removeFromCurrentMotions(new ModelMotionPair(model, simmMotionData));

      MotionEvent evt = new MotionEvent(this, model, simmMotionData, MotionEvent.Operation.Close);
      setChanged();
      notifyObservers(evt);

      if(removed) {
         evt = new MotionEvent(this, MotionEvent.Operation.CurrentMotionsChanged);
         setChanged();
         notifyObservers(evt);
      }
   }

   public void update(Observable o, Object arg) {
      if (o instanceof OpenSimDB && arg instanceof ModelEvent){
         ModelEvent evnt = (ModelEvent) arg;
         if (evnt.getOperation()==ModelEvent.Operation.Close){
            Model model = evnt.getModel();
            // Send motion close events for all motions associated with this model
            ArrayList<Storage> motionsForModel = mapModels2Motions.get(evnt.getModel());
            if(motionsForModel != null) {
               for(int i=0; i<motionsForModel.size(); i++){
                  ModelMotionPair pair = new ModelMotionPair(model, motionsForModel.get(i));
                  removeFromCurrentMotions(pair);
                  closeMotion(model, motionsForModel.get(i));
               }
            }
         }
      } else if (o instanceof MotionsDB && arg instanceof MotionEvent) {
         final MotionEvent evnt = (MotionEvent) arg;
         SwingUtilities.invokeLater(new Runnable(){
            public void run() {  // Update tree display on event thread
               switch(evnt.getOperation()) {
                  case Open:
                  {
                     Node modelNode = ExplorerTopComponent.findInstance().getModelNode(evnt.getModel());
                     MotionsNode motionsNode = (MotionsNode) modelNode.getChildren().findChild("Motions");
                     if(motionsNode==null) {
                        motionsNode = new MotionsNode();
                        getInstance().addObserver(motionsNode);
                        modelNode.getChildren().add(new Node[]{motionsNode});
                     }
                     Node newMotionNode = new OneMotionNode(evnt.getMotion());
                     motionsNode.getChildren().add(new Node[]{newMotionNode});
                     break;
                  }
                  case Close:
                  {
                     try { // destroy() may throw IOException
                        Node motionNode = getMotionNode(evnt.getModel(), evnt.getMotion());
                        Node motionsNode = null;
                        if(motionNode!=null) {
                           motionsNode = motionNode.getParentNode();
                           motionNode.destroy();
                        }
                        // Delete the "Motions" container node if no more motions left
                        if(motionsNode!=null && motionsNode.getChildren().getNodesCount()==0 && motionsNode.getName().equals("Motions"))
                           motionsNode.destroy();
                     } catch (IOException ex) {
                        ex.printStackTrace();
                     }
                     break;
                  }
               }
            }
         });
      }
   }

    void reportTimeChange(double newTime) {
        MotionTimeChangeEvent evt = new MotionTimeChangeEvent(instance,newTime);
        setChanged();
        instance.notifyObservers(evt);
    }
   
    public ArrayList<Storage> getModelMotions(Model aModel)
    {
       return mapModels2Motions.get(aModel);
    }

   // Get the motion node from the explorer
   public OneMotionNode getMotionNode(final Model model, final Storage motion) {
      ConcreteModelNode modelNode = ExplorerTopComponent.findInstance().getModelNode(model);
      if(modelNode!=null) {
         Node motionsNode = modelNode.getChildren().findChild("Motions");
         if(motionsNode!=null) {
            Node[] children = motionsNode.getChildren().getNodes();
            for(Node child : motionsNode.getChildren().getNodes())
               if((child instanceof OneMotionNode) && ((OneMotionNode)child).getMotion() == motion)
                  return (OneMotionNode)child;
         }
      }
      return null;
   }

   //------------------------------------------------------------------------
   // Utilities for currentMotions
   //------------------------------------------------------------------------
   // TODO: add an equals() method to ModelMotionPair so that we can use more standard Vector routines
   // in place of these... but then I think we'll have to implement hashCode() and other such base functions.
   private void clearCurrentMotions() { currentMotions.setSize(0); }
   private void addToCurrentMotions(ModelMotionPair pair) { currentMotions.add(pair); }
   private void setCurrentMotion(ModelMotionPair pair) {
      currentMotions.setSize(1);
      currentMotions.set(0, pair);
   }
   private void setCurrentMotions(Vector<ModelMotionPair> motions) {
      currentMotions = motions; // TODO: hopefully it's safe to just use = here
   }
   private boolean removeFromCurrentMotions(ModelMotionPair pair) {
      for(int i=0; i<currentMotions.size(); i++) {
         if(currentMotions.get(i).model == pair.model && currentMotions.get(i).motion == pair.motion) {
            currentMotions.remove(i);
            return true;
         }
      }
      return false;
   }

   public int getNumCurrentMotions() { return currentMotions.size(); }
   public ModelMotionPair getCurrentMotion(int i) { return currentMotions.get(i); }

   boolean isModelMotionPairCurrent(ModelMotionPair pair) {
      for(int i=0; i<currentMotions.size(); i++) {
         if(currentMotions.get(i).model == pair.model && currentMotions.get(i).motion == pair.motion) 
            return true;
      }
      return false;
   }
}
