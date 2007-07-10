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
import java.util.Observable;
import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.Model;
import org.opensim.view.*;

/**
 *
 * @author adminxp
 */
final public class OpenSimDB extends Observable {
    
    static OpenSimDB instance;
    
    static ArrayList<Model>  models = new ArrayList<Model>();
    static Model currentModel=null;
    ///static UndoManager undoMgr=new UndoManager();
    
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
        setupGroups(aModel);
        models.add(aModel);
        // Mark model as current
        // Don't use setCurrent to avoid multiple events
        //currentModel=aModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aModel, ModelEvent.Operation.Open);
        notifyObservers(evnt);
        setCurrentModel(aModel);
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
    /**
     * Number of models currently loaded.
     */
    public int getNumModels() {
        return models.size();
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

    public void saveModel(Model model, String fileName) {
      model.print(fileName);
      model.setInputFileName(fileName); // update the source filename of the model
      setChanged();
      ModelEvent evnt = new ModelEvent(model, ModelEvent.Operation.Save);
      notifyObservers(evnt);
   } 

    /**
     * For now this just fires an event to make sure the GUI indicates what's the current Model but
     * the database itself does not keep track of which one in the models is Current.
     */
    public void setCurrentModel(final Model aCurrentModel) {
        setCurrentModel(aCurrentModel, true);
    }
    public void setCurrentModel(final Model aCurrentModel, boolean logEdit) {
        final Model saveCurrentModel=currentModel;
        currentModel = aCurrentModel;
        setChanged();
        ModelEvent evnt = new ModelEvent(aCurrentModel, ModelEvent.Operation.SetCurrent);
        notifyObservers(evnt);
        if (logEdit){
            ExplorerTopComponent.getDefault().getUndoRedoManager().addEdit(new AbstractUndoableEdit() {
                public void undo() throws CannotUndoException {
                    super.undo();
                    setCurrentModel(saveCurrentModel, false);
                }

                public void redo() throws CannotRedoException {
                    super.redo();
                    setCurrentModel(aCurrentModel, false);
                }

                public boolean canUndo() {
                    boolean retValue= super.canUndo();
                    return true;
                }

                public boolean canRedo() {
                    boolean retValue = super.canRedo();
                    return true;
                }
           });
        //StatusDisplayer.getDefault().setStatusText("Current model:"+aCurrentModel.getName());
    }
    }
    
    public synchronized void undo()
    {
        ExplorerTopComponent.getDefault().getUndoRedoManager().undo();
    }
    public synchronized boolean canUndo()
    {
        return ExplorerTopComponent.getDefault().getUndoRedoManager().canUndo();
    }
    public synchronized void redo()
    {
        ExplorerTopComponent.getDefault().getUndoRedoManager().redo();
    }
    public synchronized boolean canRedo()
    {
        return ExplorerTopComponent.getDefault().getUndoRedoManager().canRedo();
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

   private void setupGroups(Model aModel) {
      // Create default groups
      ActuatorSet acts = aModel.getActuatorSet();
      // Until we decide how best to handle the "all" group,
      // don't add one here.
      //int numGroups = acts.getNumGroups();
      //if (acts.getGroup("all")==null){
         //acts.addGroup("all");
         //for(int i=0; i<acts.getSize(); i++){
            //acts.addObjectToGroup("all", acts.get(i).getName());
         //}
      //}
      CoordinateSet coords = aModel.getDynamicsEngine().getCoordinateSet();
      //numGroups = coords.getNumGroups();
      if (coords.getGroup("all")==null){
         coords.addGroup("all");
         for(int i=0; i<coords.getSize(); i++){
            coords.addObjectToGroup("all", coords.get(i).getName());
         }
      }
   }


}
