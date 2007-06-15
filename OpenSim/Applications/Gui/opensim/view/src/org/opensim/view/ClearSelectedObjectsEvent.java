/*
 * ClearSelectedObjectsEvent.java
 *
 * Created on April 3, 2007, 03:40 PM
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
public class ClearSelectedObjectsEvent extends EventObject {

    /** Creates a new instance of ClearSelectedObjectsEvent
     *  state indicates whether the object was selected (true)
     *  or unselected (false).
     */
    public ClearSelectedObjectsEvent(Object source) {
       super(source);
    }

}
