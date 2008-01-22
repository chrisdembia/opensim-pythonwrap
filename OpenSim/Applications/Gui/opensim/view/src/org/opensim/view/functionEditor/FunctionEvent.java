/*
 * FunctionEvent.java
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
public class FunctionEvent extends EventObject {
   
   private Model model;
   private OpenSimObject object;
   private Function function;

   public FunctionEvent(Model model, OpenSimObject object, Function function) {
      super(function);
      this.model = model;
      this.object = object;
      this.function = function;
   }
   
   public Model getModel() {
      return this.model;
   }
   
   public OpenSimObject getObject() {
      return this.object;
   }
   
   public Function getFunction() {
      return this.function;
   }
}
