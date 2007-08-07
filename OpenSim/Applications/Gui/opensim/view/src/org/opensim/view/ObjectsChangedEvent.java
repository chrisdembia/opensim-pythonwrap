/*
 * ObjectsChangedEvent.java
 *
 * Created on August 7, 2007, 9:02 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.Vector;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class ObjectsChangedEvent extends OpenSimEvent {
   
   /** Creates a new instance of ObjectsChangedEvent */
   public ObjectsChangedEvent(Object source, Model theModel, Vector<OpenSimObject> theObjects) {
        super(source, theModel, theObjects);
   }
   
}
