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
import org.opensim.view.SelectedObject;

/**
 *
 * @author Peter Loan
 */
public class ObjectSelectedEvent extends EventObject {

   private SelectedObject selectedObject;
   private boolean selected = false;

    /** Creates a new instance of ObjectSelectedEvent
     *  state indicates whether the object was selected (true)
     *  or unselected (false).
     */
    public ObjectSelectedEvent(Object source, SelectedObject object, boolean state) {
       super(source);
       selectedObject = object;
       selected = state;
    }

    public SelectedObject getSelectedObject()
    {
        return (SelectedObject) selectedObject;
    }

    public String getName()
    {
        return getSelectedObject().getOpenSimObject().getName();
    }

    public boolean getState()
    {
        return selected;
    }

}
