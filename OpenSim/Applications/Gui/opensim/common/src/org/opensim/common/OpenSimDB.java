/*
 * OpenSimDB.java
 *
 * Created on June 15, 2006, 2:58 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.common;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Observable;
import org.opensim.modeling.SimmModel;

/**
 *
 * @author adminxp
 */
final public class OpenSimDB extends Observable {
    
    static OpenSimDB instance;
    
    static HashMap<String, SimmModel> modelsLookupTable = new HashMap<String, SimmModel>();
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
    
    public static void addModel(SimmModel aModel) {
        modelsLookupTable.put(aModel.getName(), aModel);
    }
  
    public void addModel(String filename) {
        SimmModel aModel = new SimmModel(filename);
        aModel.setup();
        addModel(aModel);
        setChanged();
        newModelEvent evnt = new newModelEvent(aModel);
        notifyObservers(evnt);
    }

    public static SimmModel getModel(String modelName)
    {
        return modelsLookupTable.get(modelName);
    }
    
    public static Collection<SimmModel> getAllModels()
    {
        return modelsLookupTable.values();
    }
}
