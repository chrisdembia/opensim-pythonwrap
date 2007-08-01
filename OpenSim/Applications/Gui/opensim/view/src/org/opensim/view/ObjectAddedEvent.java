/*
 * ObjectAddedEvent.java
 *
 * Created on July 18, 2007, 1:28 PM
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
public class ObjectAddedEvent extends OpenSimEvent {

   /**
    * Creates a new instance of ObjectAddedEvent
    */
   public ObjectAddedEvent(Object source, Model theModel, Vector<OpenSimObject> theObjects) {
        super(source, theModel, theObjects);
   }
}
