/*
 * FunctionChangeListener.java
 *
 * Created on November 16, 2007, 3:10 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.functioneditor;

import java.util.EventListener;

/**
 * The interface that must be supported by classes that wish to receive 
 * notification of function change events.
 *
 */
public interface FunctionChangeListener extends EventListener {

   /**
    * Receives notification of a function change event.
    *
    * @param event  the event.
    */
   public void functionChanged(FunctionChangeEvent event);

}
