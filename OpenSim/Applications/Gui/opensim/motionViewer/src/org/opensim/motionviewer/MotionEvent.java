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
    
    public enum Operation{Open, Close, SetCurrent, Clear, AddSyncMotion};
    Model model;
    Storage motion;
    boolean lastInASeries = false; // for a series of AddSyncMotion, indicates that this is the last motion in the selected group 
                                   // (so display can update after this event is handled)
    
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

    public void setLastInASeries(boolean lastInASeries) { this.lastInASeries = lastInASeries; }
    public boolean getLastInASeries() { return lastInASeries; }
    
}
