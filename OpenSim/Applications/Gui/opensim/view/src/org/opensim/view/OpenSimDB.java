/*
 * OpenSimDB.java
 *
 * Created on June 15, 2006, 2:58 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.ArrayList;
import java.util.Observable;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmMarkerSet;
import org.opensim.modeling.SimmModel;
import org.opensim.view.ModelEvent;

/**
 *
 * @author adminxp
 */
final public class OpenSimDB extends Observable {
    
    static OpenSimDB instance;
    
    static ArrayList<SimmModel>  models = new ArrayList<SimmModel>();
    /** 
    /** Creates a new instance of OpenSimDB */
    private OpenSimDB() {
    }
    
    public static synchronized OpenSimDB getInstance() {
        if (instance == null) {
             instance = new OpenSimDB();
        }
        return instance;
    }
    
    public void addModel(SimmModel aModel) {
        models.add(aModel);
        setChanged();
        ModelEvent evnt = new ModelEvent(aModel, ModelEvent.Operation.Open);
        notifyObservers(evnt);
    }

    public static SimmModel getModel(String modelName)
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
    
    public void removeModel(SimmModel model)
    {
        models.remove(model);
        setChanged();
        ModelEvent evnt = new ModelEvent(model, ModelEvent.Operation.Close);
        notifyObservers(evnt);
    }
    /**
     * Add a markerSet to the simmModel.
     * This operation modifies the model and triggers update of the visuals
     */
    void addMarkerSet(SimmMarkerSet markerSet, SimmModel simmModel) {
        simmModel.updateMarkers(markerSet);
        // Needed to update display properties of markers
        for(int i=0; i < markerSet.getSize(); i++){
            markerSet.get(i).setup(simmModel.getSimmKinematicsEngine());
        }
        setChanged();
        ModelEvent evnt = new ModelEvent(simmModel, ModelEvent.Operation.UpdateDisplay);
        notifyObservers(evnt);
   }

}
