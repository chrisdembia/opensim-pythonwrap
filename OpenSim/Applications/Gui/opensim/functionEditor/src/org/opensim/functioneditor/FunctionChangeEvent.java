/*
 * FunctionChangeEvent.java
 *
 * Created on November 16, 2007, 3:02 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.functioneditor;

import java.util.EventObject;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;

/**
 * A change event that encapsulates information about a change to a chart.
 */
public class FunctionChangeEvent extends EventObject {
   
   private Model model;
   private OpenSimObject object;
   private Function oldFunction;
   private Function newFunction;

   public FunctionChangeEvent(Model model, OpenSimObject object, Function oldFunction, Function newFunction) {
      super(oldFunction);
      this.model = model;
      this.object = object;
      this.oldFunction = oldFunction;
      this.newFunction = newFunction;
   }
   
   public Model getModel() {
      return this.model;
   }
   
   public OpenSimObject getObject() {
      return this.object;
   }
   
   public Function getOldFunction() {
      return this.oldFunction;
   }
   
   public Function getNewFunction() {
      return this.newFunction;
   }
}
