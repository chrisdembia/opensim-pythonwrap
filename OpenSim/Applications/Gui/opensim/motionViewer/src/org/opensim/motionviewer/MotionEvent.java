/*
 * MotionEvent.java
 *
 * Created on June 16, 2006, 8:59 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.motionviewer;

import java.util.EventObject;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman Habib
 */
public class MotionEvent extends EventObject {
    
    public enum Operation{Open, Close, CurrentMotionsChanged};
    Model model;
    Storage motion;
    Operation op= Operation.Open;
    /**
     * Creates a new instance of MotionEvent
     */
    public MotionEvent(Object source, Model model, Storage motion, Operation op) {
        super(source);
        this.model = model;
        this.motion = motion;
        this.op = op;
    }
    public MotionEvent(Object source, Operation op) {
        super(source);
        this.model = null;
        this.motion = null;
        this.op = op;
    }
        
    public Model getModel()
    {
        return model;
    }
    
    public Storage getMotion()
    {
        return motion;
    }
    
    public MotionEvent.Operation getOperation()
    {
        return op;
    }
}
