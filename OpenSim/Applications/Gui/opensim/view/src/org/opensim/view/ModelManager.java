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
import org.openide.nodes.AbstractNode;
import org.opensim.modeling.AbstractModel;

/**
 *
 * @author ken
 */
public final class ModelManager implements ExplorerManager.Provider {
    
    private static ModelManager _instance = null;
    
    private final ExplorerManager _manager = new ExplorerManager();
    
    private ArrayList<AbstractModel> _models = new ArrayList<AbstractModel>();
    
    /** Get the single instance of the ModelManger */
    public static synchronized ModelManager getDefault() {
        if (_instance == null)
            _instance = new ModelManager();
        return _instance;
    }
    
    /** Creates a new instance of ModelManager */
    public ModelManager() {
    }
    
    public ArrayList<AbstractModel> getModels() { // TODO: make this const
        return _models;
    }
    
    public void addModel(AbstractModel m) {
        _models.add(m);
    }

    public ExplorerManager getExplorerManager() {
        return _manager;
    }
    
} // class ModelManager
