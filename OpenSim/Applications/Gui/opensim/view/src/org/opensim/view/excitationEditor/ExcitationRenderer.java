/*
 * ExcitationRenderer.java
 *
 * Created on October 25, 2007, 10:52 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import java.util.ArrayList;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.Function;
import org.opensim.view.functionEditor.FunctionRenderer;

/**
 *
 * @author Ayman Habib 
 */
public class ExcitationRenderer extends FunctionRenderer
 {

   private ControlLinear control;
   
   /**
     * Creates a ExcitationRenderer for a single function.
     */
   public ExcitationRenderer(ControlLinear theControl, Function dFunction) {
      super(dFunction);
      control=theControl;
   }

    public ControlLinear getControl() {
        return control;
    }

     
}
