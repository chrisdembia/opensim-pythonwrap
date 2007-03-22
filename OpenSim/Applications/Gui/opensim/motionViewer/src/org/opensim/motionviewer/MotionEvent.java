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
import org.opensim.modeling.SimmMotionData;

/**
 *
 * @author Ayman Habib
 */
public class MotionEvent extends EventObject {
    
    public enum Operation{Open, Close, SetCurrent, Clear, AddSyncMotion};
    SimmMotionData  motion;
    
    Operation op= Operation.Open;
    /**
     * Creates a new instance of MotionEvent
     */
    public MotionEvent(Model source, SimmMotionData motion, Operation op) {
        super(source);
        this.motion = motion;
        this.op = op;
    }
        
    public Model getModel()
    {
        return (Model) source;
    }
    
    public SimmMotionData getMotion()
    {
        return motion;
    }
    
    public MotionEvent.Operation getOperation()
    {
        return op;
    }
    
}
