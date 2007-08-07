/*
 * ObjectsDeletedEvent.java
 *
 * Created on August 7, 2007, 3:31 PM
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
public class ObjectsDeletedEvent extends OpenSimEvent {

   /**
    * Creates a new instance of ObjectsDeletedEvent
    */
   public ObjectsDeletedEvent(Object source, Model theModel, Vector<OpenSimObject> theObjects) {
        super(source, theModel, theObjects);
   }
}