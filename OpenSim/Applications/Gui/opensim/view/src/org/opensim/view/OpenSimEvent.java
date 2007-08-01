/*
 * OpenSimEvent.java
 *
 * Created on July 18, 2007, 1:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.EventObject;
import java.util.Vector;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class OpenSimEvent extends EventObject {
   /* 'objects' holds the vector of objects that this event is for. */
   private Vector<OpenSimObject> objects;
   /* 'model' is the model that owns the objects, but can be null
    * if the objects are not from a model or from multiple models.
    */
   private Model model;

   /** Creates a new instance of OpenSimEvent */
   public OpenSimEvent(Object source, Model theModel, Vector<OpenSimObject> theObjects) {
      super(source);
      model = theModel;
      if (theObjects != null && theObjects.size() > 0) {
         objects = new Vector<OpenSimObject>(theObjects.size());
         objects.addAll(theObjects);
      }
   }

   public Model getModel() {
       return model;
   }

   public Vector<OpenSimObject> getObjects() {
      return objects;
   }
}
