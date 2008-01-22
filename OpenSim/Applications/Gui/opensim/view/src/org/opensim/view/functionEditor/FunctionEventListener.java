/*
 * FunctionEventListener.java
 *
 * Created on November 16, 2007, 3:10 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import java.util.EventListener;

/**
 * The interface that must be supported by classes that wish to receive 
 * notification of function change events.
 *
 */
public interface FunctionEventListener extends EventListener {

   /**
    * Receives notification of a modification to a function.
    *
    * @param event  the event.
    */
   public void handleFunctionEvent(FunctionEvent event);

}
