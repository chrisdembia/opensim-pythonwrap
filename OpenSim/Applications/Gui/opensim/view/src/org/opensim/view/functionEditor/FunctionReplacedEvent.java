/*
 * FunctionReplacedEvent.java
 *
 * Created on January 10, 2008, 4:51 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;

/**
 * A change event that encapsulates information about a function being replaced.
 */
public class FunctionReplacedEvent extends FunctionEvent {

   private Function replacementFunction;

   public FunctionReplacedEvent(Model model, OpenSimObject object, Function oldFunction, Function newFunction) {
      super(model, object, oldFunction);
      this.replacementFunction = newFunction;
   }
   
   public Function getReplacementFunction() {
      return this.replacementFunction;
   }
}
