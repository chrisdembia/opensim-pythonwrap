/*
 * NameChangedEvent.java
 *
 * Created on February 14, 2007, 11:50 AM
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
public class NameChangedEvent extends EventObject {

    /** Creates a new instance of NameChangedEvent */
    public NameChangedEvent(OpenSimObject source) {
        super(source);
    }

    public OpenSimObject getObject()
    {
        return (OpenSimObject) source;
    }

    public String getName()
    {
        return ((OpenSimObject) source).getName();
    }

}
