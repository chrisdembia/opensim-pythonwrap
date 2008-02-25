/*
 * MusclePropertyFunctionEventListener.java
 *
 * Created on January 10, 2008, 4:51 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.editors;

import org.opensim.view.functionEditor.FunctionEvent;
import org.opensim.view.functionEditor.FunctionEventListener;
import org.opensim.view.functionEditor.FunctionModifiedEvent;
import org.opensim.view.functionEditor.FunctionReplacedEvent;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.Function;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class MusclePropertyFunctionEventListener implements FunctionEventListener {
   
   /** Creates a new instance of MusclePropertyFunctionEventListener */
   public MusclePropertyFunctionEventListener() {
   }

   public void handleFunctionEvent(FunctionEvent event) {
      OpenSimObject object = event.getObject();

      AbstractActuator act = AbstractActuator.safeDownCast(object);
      if (act != null) {
         if (event instanceof FunctionReplacedEvent) {
            FunctionReplacedEvent fre = (FunctionReplacedEvent) event;
            Function oldFunction = fre.getFunction();
            Function newFunction = fre.getReplacementFunction();
            if (Function.getCPtr(oldFunction) != Function.getCPtr(newFunction)) {
               act.replacePropertyFunction(oldFunction, newFunction);
               MuscleEditorTopComponent.findInstance().propertyFunctionChanged(event.getModel(), act);
            }
         } else if (event instanceof FunctionModifiedEvent) {
            MuscleEditorTopComponent.findInstance().propertyFunctionChanged(event.getModel(), act);
         }
      }
   }
}