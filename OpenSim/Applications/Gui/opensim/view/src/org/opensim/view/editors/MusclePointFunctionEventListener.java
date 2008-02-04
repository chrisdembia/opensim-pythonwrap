/*
 * MusclePointFunctionEventListener.java
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
import org.opensim.modeling.MovingMusclePoint;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class MusclePointFunctionEventListener implements FunctionEventListener {
   
   /** Creates a new instance of MusclePointFunctionEventListener */
   public MusclePointFunctionEventListener() {
   }

   public void handleFunctionEvent(FunctionEvent event) {
      OpenSimObject object = event.getObject();

      MovingMusclePoint mmp = MovingMusclePoint.safeDownCast(object);
      if (mmp != null) {
         if (event instanceof FunctionReplacedEvent) {
            FunctionReplacedEvent fre = (FunctionReplacedEvent) event;
            Function oldFunction = fre.getFunction();
            Function newFunction = fre.getReplacementFunction();
            if (Function.getCPtr(oldFunction) != Function.getCPtr(newFunction)) {
               if (Function.getCPtr(oldFunction) == Function.getCPtr(mmp.getXFunction()))
                  mmp.setXFunction(newFunction);
               else if (Function.getCPtr(oldFunction) == Function.getCPtr(mmp.getYFunction()))
                  mmp.setYFunction(newFunction);
               else if (Function.getCPtr(oldFunction) == Function.getCPtr(mmp.getZFunction()))
                  mmp.setZFunction(newFunction);
               MuscleEditorTopComponent.findInstance().movingPointMoved(event.getModel(), mmp.getMuscle(), mmp);
            }
         } else if (event instanceof FunctionModifiedEvent) {
            FunctionModifiedEvent fme = (FunctionModifiedEvent) event;
            Function function = fme.getFunction();
            if (Function.getCPtr(function) == Function.getCPtr(mmp.getXFunction()))
               mmp.setXFunction(function);
            else if (Function.getCPtr(function) == Function.getCPtr(mmp.getYFunction()))
               mmp.setYFunction(function);
            else if (Function.getCPtr(function) == Function.getCPtr(mmp.getZFunction()))
               mmp.setZFunction(function);
            MuscleEditorTopComponent.findInstance().movingPointMoved(event.getModel(), mmp.getMuscle(), mmp);
         }
      }
   }
}
