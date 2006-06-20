/*
 * newModelEvent.java
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
public class newModelEvent extends EventObject {
    
    /**
     * Creates a new instance of newModelEvent
     */
    public newModelEvent(SimmModel source) {
        super(source);
    }
    
    public SimmModel getModel()
    {
        return (SimmModel) source;
    }
    
}
