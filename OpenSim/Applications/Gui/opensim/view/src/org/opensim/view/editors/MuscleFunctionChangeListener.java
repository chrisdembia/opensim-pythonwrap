/*
 * MuscleFunctionChangeListener.java
 *
 * Created on November 16, 2007, 3:16 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.editors;

import org.opensim.functioneditor.FunctionChangeEvent;
import org.opensim.functioneditor.FunctionChangeListener;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.Function;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class MuscleFunctionChangeListener implements FunctionChangeListener {
   
   /** Creates a new instance of MuscleFunctionChangeListener */
   public MuscleFunctionChangeListener() {
   }

   public void functionChanged(FunctionChangeEvent event) {
      OpenSimObject object = event.getObject();

      AbstractActuator act = AbstractActuator.safeDownCast(object);
      if (act != null) {
         Function oldFunction = event.getOldFunction();
         Function newFunction = event.getNewFunction();
         if (Function.getCPtr(oldFunction) != Function.getCPtr(newFunction)) {
            act.replaceFunction(oldFunction, newFunction);
         }
      }
      // if oldfunc != newfunc:
      //    actuator act = object;
      //    act.replaceFunctionProperty(old, new);
   }
}
