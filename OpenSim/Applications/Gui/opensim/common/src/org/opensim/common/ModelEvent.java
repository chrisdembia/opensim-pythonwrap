/*
 * ModelEvent.java
 *
 * Created on June 16, 2006, 8:59 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.common;

import java.util.EventObject;
import org.opensim.modeling.SimmModel;

/**
 *
 * @author adminxp
 */
public class ModelEvent extends EventObject {
    
    public enum Operation{Open, Close, Save, ObjectOperation};
    
    Operation op= Operation.Open;
    /**
     * Creates a new instance of ModelEvent
     */
    public ModelEvent(SimmModel source, Operation op) {
        super(source);
        this.op = op;
    }
    
    public SimmModel getModel()
    {
        return (SimmModel) source;
    }
    
    public ModelEvent.Operation getOperation()
    {
        return op;
    }
    
}
