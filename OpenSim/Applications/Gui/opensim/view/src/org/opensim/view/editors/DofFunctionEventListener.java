/*
 * DofFunctionEventListener.java
 *
 * Created on January 10, 2008, 2:16 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.editors;

import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.SingleModelGuiElements;
import org.opensim.view.functionEditor.FunctionEvent;
import org.opensim.view.functionEditor.FunctionEventListener;
import org.opensim.view.functionEditor.FunctionModifiedEvent;
import org.opensim.view.functionEditor.FunctionReplacedEvent;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Peter Loan
 */
public class DofFunctionEventListener implements FunctionEventListener {

   /**
    * Creates a new instance of DofFunctionEventListener
    */
   public DofFunctionEventListener() {
   }

   public void handleFunctionEvent(FunctionEvent event) {
      OpenSimObject object = event.getObject();
      AbstractDof dof = AbstractDof.safeDownCast(object);

      if (dof != null) {
         Model model = OpenSimDB.getInstance().getCurrentModel();
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);

         if (event instanceof FunctionReplacedEvent) {
            FunctionReplacedEvent fre = (FunctionReplacedEvent) event;
            Function oldFunction = fre.getFunction();
            Function newFunction = fre.getReplacementFunction();
            if (Function.getCPtr(oldFunction) != Function.getCPtr(newFunction)) {
               dof.setFunction(newFunction);
               ViewDB.getInstance().updateModelDisplayNoRepaint(model);
               ViewDB.getInstance().renderAll();
               guiElem.setUnsavedChangesFlag(true);
            }
         } else if (event instanceof FunctionModifiedEvent) {
            dof.getJoint().invalidate();
            ViewDB.getInstance().updateModelDisplayNoRepaint(model);
            ViewDB.getInstance().renderAll();
            guiElem.setUnsavedChangesFlag(true);
         }
      }
   }
}
