/*
 * ModelManager.java
 *
 * Created on May 5, 2006, 1:17 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;


import java.util.ArrayList;
import org.openide.explorer.ExplorerManager;
import org.opensim.modeling.SimmModel;

/**
 *
 * @author ken
 */
public class ModelManager implements ExplorerManager.Provider {
    
    private static ModelManager _instance = null;
    
    private final ExplorerManager _manager = new ExplorerManager();
    
    private ArrayList<SimmModel> _models = new ArrayList<SimmModel>();
    
    /** Get the single instance of the ModelManger */
    public static synchronized ModelManager getDefault() {
        if (_instance == null)
            _instance = new ModelManager();
        return _instance;
    }
    
    /** Creates a new instance of ModelManager */
    public ModelManager() {
    }
    
    public ArrayList<SimmModel> getModels() { // TODO: make this const
        return _models;
    }
    
    public void addModel(SimmModel m) {
        _models.add(m);
    }

    public ExplorerManager getExplorerManager() {
        return _manager;
    }
    
} // class ModelManager
