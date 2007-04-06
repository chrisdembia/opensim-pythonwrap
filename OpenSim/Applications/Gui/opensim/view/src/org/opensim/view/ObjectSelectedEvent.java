/*
 * ObjectSelectedEvent.java
 *
 * Created on April 1, 2007, 09:20 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.EventObject;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class ObjectSelectedEvent extends EventObject {

   private boolean selected = false;
    /** Creates a new instance of ObjectSelectedEvent
     *  state indicates whether the object was selected (true)
     *  or unselected (false).
     */
    public ObjectSelectedEvent(OpenSimObject source, boolean state) {
       super(source);
       selected = state;
    }

    public OpenSimObject getObject()
    {
        return (OpenSimObject) source;
    }

    public String getName()
    {
        return ((OpenSimObject) source).getName();
    }

    public boolean getState()
    {
        return selected;
    }

}
