/*
 * ObjectSetCurrentEvent.java
 *
 * Created on July 30, 2007, 3:46 PM
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
 * @author Peter
 */
public class ObjectSetCurrentEvent extends OpenSimEvent {
   
   /** Creates a new instance of ObjectSetCurrentEvent */
   public ObjectSetCurrentEvent(Object source, Model theModel, Vector<OpenSimObject> theObjects) {
        super(source, theModel, theObjects);
   }
   
}
