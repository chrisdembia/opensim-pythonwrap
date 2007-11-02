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
import java.util.Vector;
import java.util.regex.Pattern;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.Model;
import org.opensim.modeling.opensimModelJNI;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.*;
import vtk.vtkMatrix4x4;

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
        model.cleanup();
        if (models.size()>0){
             if (model==currentModel)
                setCurrentModel(models.get(0));
        }
        else
           currentModel=null;
        
        setChanged();
        ModelEvent evnt = new ModelEvent(model, ModelEvent.Operation.Close);
        notifyObservers(evnt);
        
        model.cleanup();    // Cleanup after removal 
        System.gc();
    }

   // removes old model and adds new model, but also transfers over some display properties
   // currently used by scale tool, which can't re-scale in place so it creates a new model to replace the old one
   public void replaceModel(Model oldModel, Model newModel) {
      vtkMatrix4x4 offset=null;
      double opacity=1;
      if(oldModel!=null) {
         SingleModelVisuals rep = ViewDB.getInstance().getModelVisuals(oldModel);
         if(rep!=null) {
            offset = ViewDB.getInstance().getModelVisualsTransform(rep); // TODO: do we need to make a copy??
            opacity = rep.getOpacity();
         }
         removeModel(oldModel);
      }
      if(newModel!=null) {
         addModel(newModel);
         SingleModelVisuals rep = ViewDB.getInstance().getModelVisuals(newModel);
         if(offset!=null) {
            ViewDB.getInstance().setModelVisualsTransform(rep, offset);
            ViewDB.getInstance().setObjectOpacity(newModel, opacity);
         }
      }
   }

    public void saveModel(Model model, String fileName) {
      model.print(fileName);
      model.setInputFileName(fileName); // update the source filename of the model
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);
      if(guiElem!=null) guiElem.setUnsavedChangesFlag(false);
      setChanged();
      ModelEvent evnt = new ModelEvent(model, ModelEvent.Operation.Save);
      notifyObservers(evnt);
   } 

    public void setCurrentModel(final Model aCurrentModel) {
        setCurrentModel(aCurrentModel, true);
    }

    /**
     * Set the current model to the new one and fire an event for the change.
     */
    public void setCurrentModel(Model aCurrentModel, boolean logEdit) {
        currentModel = aCurrentModel;
        Vector<OpenSimObject> objs = new Vector<OpenSimObject>(1);
        objs.add(aCurrentModel);
        ObjectSetCurrentEvent evnt = new ObjectSetCurrentEvent(this, aCurrentModel, objs);
        setChanged();
        //ModelEvent evnt = new ModelEvent(aCurrentModel, ModelEvent.Operation.SetCurrent);
        notifyObservers(evnt);
        objs.clear();
        /*
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
    }*/
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
   /**
    * Common place to validate new object names to make sure
    * They start with a an alphanumeric
    * contain any combinaton of letters, numbers, _, ., - but no special chars.
    */
   static public boolean validateName(String proposedName, boolean allowSpace)
   {
      Pattern p;
      if (allowSpace)
          p = Pattern.compile("[A-Z][A-Z0-9_. -]*", Pattern.CASE_INSENSITIVE);
      else
           p = Pattern.compile("[A-Z][A-Z0-9_.-]*", Pattern.CASE_INSENSITIVE);
         
        return (p.matcher(proposedName).matches());

   }
}
