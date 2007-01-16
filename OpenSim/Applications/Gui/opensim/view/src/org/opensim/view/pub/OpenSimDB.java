/*
 * OpenSimDB.java
 *
 * Created on June 15, 2006, 2:58 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.pub;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Observable;
import org.openide.awt.StatusDisplayer;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.*;

/**
 *
 * @author adminxp
 */
final public class OpenSimDB extends Observable {
    
    static OpenSimDB instance;
    
    static ArrayList<AbstractModel>  models = new ArrayList<AbstractModel>();
    static AbstractModel currentModel=null;
    // Map model to an ArrayList of Motions linked with it
    static Hashtable<AbstractModel, ArrayList<SimmMotionData>> mapModels2Motions = 
            new Hashtable<AbstractModel, ArrayList<SimmMotionData>>(4);
    //static SimmMotionData currentMotion=null;
    
    /** Creates a new instance of OpenSimDB */
    private OpenSimDB() {
    }
    
    public static synchronized OpenSimDB getInstance() {
        if (instance == null) {
             instance = new OpenSimDB();
             
        }
        return instance;
    }
    
    public void addModel(AbstractModel aModel) {
        models.add(aModel);
        // Mark model as current
        // Don't use setCurrent to avoid multiple events
        currentModel=aModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aModel, ModelEvent.Operation.Open);
        notifyObservers(evnt);
    }

    public static AbstractModel getModel(String modelName)
    {
        for(int i=0; i<models.size(); i++){
            if (models.get(i).getName().equals(modelName))
                return models.get(i);
        }
        return null;
    }
    
    public static Object[] getAllModels()
    {
        return (Object[]) models.toArray();
    }
    
    public void removeModel(AbstractModel model)
    {
        models.remove(model);
        if (models.size()>0)
           setCurrentModel(models.get(0));
        else
           currentModel=null;
        
        setChanged();
        ModelEvent evnt = new ModelEvent(model, ModelEvent.Operation.Close);
        notifyObservers(evnt);
    }
    /**
     * Number of models currently loaded.
     */
    public int getNumModels() {
        return models.size();
    }
    /**
     * For now this just fires an event to make sure the GUI indicates what's the current Model but
     * the database itself does not keep track of which one in the models is Current.
     */
    public void setCurrentModel(AbstractModel aCurrentModel) {
        currentModel = aCurrentModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aCurrentModel, ModelEvent.Operation.SetCurrent);
        notifyObservers(evnt);
        StatusDisplayer.getDefault().setStatusText("Current model:"+aCurrentModel.getName());
    }
    /**
     * Get current model (as indicated by bold name in the explorer view)
     * if none then the function returns null
     *
     * It's an error condition if this function returns null while the explorer view is nonempty
     **/
   public AbstractModel getCurrentModel() {
      return currentModel;
   }
   /**
    * hasModel checks if the passed in model is already loaded.
    **/
   public boolean hasModel(AbstractModel aModel) {
     for(int i=0; i<models.size(); i++){
         if (models.get(i).equals(aModel))
             return true;
     }
      return false;
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
      SimmMotionData newMotion = new SimmMotionData(fileName);
      boolean associated = false;
      while(!associated){
         AbstractModel modelForMotion = selectModel(currentModel);
         if (modelForMotion == null){ // user cancelled
            break;
         }
         // user selected a model, try to associate it
         if(canAssociateMotionToModel(newMotion, modelForMotion)){
            ArrayList<SimmMotionData> currentMotions = mapModels2Motions.get(modelForMotion);
            setCurrentModel(modelForMotion);
            if (currentMotions==null){
               currentMotions = new ArrayList<SimmMotionData>(3);
               mapModels2Motions.put(modelForMotion, currentMotions);
            }
            currentMotions.add(newMotion);
            associated = true;
            //setCurrentMotion(newMotion);
         }
         else  // Show error that motion couldn't be associated and repeat'
            ;
      }
   }

   private static AbstractModel selectModel(AbstractModel currentModel) {
      return currentModel;
   }
   /**
    * Criteria for associating motionto a model:
    * At least one genccord or marker (_tx?) in motion file/SimmMotionData
    */
   private static boolean canAssociateMotionToModel(SimmMotionData newMotion, AbstractModel modelForMotion) {
      ArrayStr coordinateNames = new ArrayStr();
      modelForMotion.getDynamicsEngine().getCoordinateSet().getNames(coordinateNames);
      int numCoordinates = coordinateNames.getSize();
      int numUsedColumns = 0;    // Keep track of how many columns correspond to Coords or Markers
      for(int i=0; i<numCoordinates; i++){
         if (newMotion.getColumnIndex(coordinateNames.getitem(i))!=-1)
            numUsedColumns++;
      }
      ArrayStr markerNames = new ArrayStr();
      modelForMotion.getDynamicsEngine().getMarkerSet().getNames(markerNames);
      for(int i=0; i<markerNames.getSize(); i++){
         if ((newMotion.getColumnIndex(markerNames.getitem(i)+"_tx")!=-1) ||
                 (newMotion.getColumnIndex(markerNames.getitem(i)+"_Tx")!=-1) ||
                 (newMotion.getColumnIndex(markerNames.getitem(i)+"_TX")!=-1))
            numUsedColumns++;
      }
     
      return numUsedColumns>=1;   // At least one column makes sense
   }


}
