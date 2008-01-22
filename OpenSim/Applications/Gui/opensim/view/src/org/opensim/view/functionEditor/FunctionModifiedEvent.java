/*
 * FunctionModifiedEvent.java
 *
 * Created on January 10, 2008, 4:51 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import java.util.EventObject;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;

/**
 * A change event that encapsulates information about a change to a function.
 */
public class FunctionModifiedEvent extends FunctionEvent {

   public FunctionModifiedEvent(Model model, OpenSimObject object, Function function) {
      super(model, object, function);
   }
}
