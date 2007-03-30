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
import org.opensim.modeling.Model;
import org.opensim.modeling.ArrayStr;
import org.opensim.view.*;

/**
 *
 * @author adminxp
 */
final public class OpenSimDB extends Observable {
    
    static OpenSimDB instance;
    
    static ArrayList<Model>  models = new ArrayList<Model>();
    static Model currentModel=null;
    
    /** Creates a new instance of OpenSimDB */
    private OpenSimDB() {
    }
    
    // The setChanged() protected method must overridden to make it public
    public synchronized void setChanged() {
        super.setChanged();
    }
    
    public static synchronized OpenSimDB getInstance() {
        if (instance == null) {
             instance = new OpenSimDB();
             
        }
        return instance;
    }
    
    public void addModel(Model aModel) {
        models.add(aModel);
        // Mark model as current
        // Don't use setCurrent to avoid multiple events
        currentModel=aModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aModel, ModelEvent.Operation.Open);
        notifyObservers(evnt);
    }

    public static Model getModel(String modelName)
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
    
    public void removeModel(Model model)
    {
        models.remove(model);
        if (models.size()>0){
             if (model==currentModel)
                setCurrentModel(models.get(0));
        }
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
    public void setCurrentModel(Model aCurrentModel) {
        currentModel = aCurrentModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aCurrentModel, ModelEvent.Operation.SetCurrent);
        notifyObservers(evnt);
        //StatusDisplayer.getDefault().setStatusText("Current model:"+aCurrentModel.getName());
    }
    /**
     * Get current model (as indicated by bold name in the explorer view)
     * if none then the function returns null
     *
     * It's an error condition if this function returns null while the explorer view is nonempty
     **/
   public Model getCurrentModel() {
      return currentModel;
   }
   /**
    * hasModel checks if the passed in model is already loaded.
    **/
   public boolean hasModel(Model aModel) {
     for(int i=0; i<models.size(); i++){
         if (models.get(i).equals(aModel))
             return true;
     }
      return false;
   }

   public static Model selectModel(Model currentModel) {
      return currentModel;
   }


}
