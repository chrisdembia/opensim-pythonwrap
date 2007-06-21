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

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
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
import org.opensim.view.pub.*;

/**
 *
 * @author Ayman
 */
public class MotionsDB extends Observable // Observed by other entities in motionviewer
        implements Observer {   // Observer OpenSimDB to sync. up when models are deleted
   
   static MotionsDB instance;
   // Map model to an ArrayList of Motions linked with it
   static Hashtable<Model, ArrayList<Storage>> mapModels2Motions =
           new Hashtable<Model, ArrayList<Storage>>(4);
   
   /** Creates a new instance of MotionsDB */
   private MotionsDB() {
       OpenSimDB.getInstance().addObserver(this);
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
      Storage storage;
      final Storage newMotion = new Storage(fileName);
      String name = newMotion.getName();
      boolean associated = false;
      while(!associated){
         Model modelForMotion = OpenSimDB.getInstance().selectModel(OpenSimDB.getInstance().getCurrentModel());
         if (modelForMotion == null){ // user cancelled
            break;
         }
         // user selected a model, try to associate it
         if(MotionsDB.getInstance().AssociateMotionToModel(newMotion, modelForMotion)){
            associated = true;
            final Model dModel = modelForMotion;
            SwingUtilities.invokeLater(new Runnable(){
               public void run() {  // Update tree display on event thread
                  ExplorerTopComponent tree = ExplorerTopComponent.findInstance();
                  Node modelNode = tree.getModelNode(dModel);
                  Node[] nds = modelNode.getChildren().getNodes();
                  Node motionsNode = modelNode.getChildren().findChild("Motions");
                  if (motionsNode==null){ // Create Motions node if not created yet.
                     // "Motions"
                     motionsNode = new MotionsNode();
                     modelNode.getChildren().add(new Node[]{motionsNode});
                  }
                  Node newMotionNode = new OneMotionNode(newMotion);
                  motionsNode.getChildren().add(new Node[]{newMotionNode});
               }
            });
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
   boolean AssociateMotionToModel(Storage newMotion, Model modelForMotion) {
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
      
      boolean associationPossible=(numUsedColumns>=1); // At least one column makes sense
      if (associationPossible){
         if(mapModels2Motions.get(modelForMotion)==null){  // First motion for model
            mapModels2Motions.put(modelForMotion, new  ArrayList<Storage>(4));
         }
         ArrayList<Storage> motions= mapModels2Motions.get(modelForMotion);
         modelForMotion.getDynamicsEngine().convertDegreesToRadians(newMotion);
         motions.add(newMotion);
         MotionEvent evt = new MotionEvent(this, modelForMotion, newMotion, MotionEvent.Operation.Open);
         setChanged();
         //int c = this.countObservers();
         notifyObservers(evt);
         StatusDisplayer.getDefault().setStatusText("Associated motion: "+newMotion.getName()+" to model:"+modelForMotion.getName());
      }
      return associationPossible;
   }

    void setCurrent(Model model, Storage motion) {
         MotionEvent evt = new MotionEvent(this, model, motion, MotionEvent.Operation.SetCurrent);
         setChanged();
         notifyObservers(evt);
    }

   void flushMotions() {
         MotionEvent evt = new MotionEvent(this, null, null, MotionEvent.Operation.Clear);
         setChanged();
         notifyObservers(evt);
   }

   void addSyncMotion(Model model, Storage simmMotionData, boolean lastInASeries) {
         MotionEvent evt = new MotionEvent(this, model, simmMotionData, MotionEvent.Operation.AddSyncMotion);
         evt.setLastInASeries(lastInASeries);
         setChanged();
         notifyObservers(evt);
   }

   void closeMotion(Model model, Storage simmMotionData) {
         MotionEvent evt = new MotionEvent(this, model, simmMotionData, MotionEvent.Operation.Close);
         setChanged();
         notifyObservers(evt);
   }


    public void update(Observable o, Object arg) {
        if (o instanceof OpenSimDB && arg instanceof ModelEvent){
             ModelEvent evnt = (ModelEvent) arg;
             if (evnt.getOperation()==ModelEvent.Operation.Close){
               Model model = evnt.getModel();
               // Send motion close events for all motions associated with this model
               ArrayList<Storage> motionsForModel = mapModels2Motions.get(evnt.getModel());
               if(motionsForModel != null) {
                  for(int i=0; i<motionsForModel.size(); i++)
                     closeMotion(model, motionsForModel.get(i));
               }
            }
        }
    }

    void reportTimeChange(double newTime) {
        MotionTimeChangeEvent evt = new MotionTimeChangeEvent(instance,newTime);
        setChanged();
        instance.notifyObservers(evt);
    }
   
}
