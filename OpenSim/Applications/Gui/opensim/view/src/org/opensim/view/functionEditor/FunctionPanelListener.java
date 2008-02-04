/*
 * FunctionPanelListener.java
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
public interface FunctionPanelListener extends EventListener {

   /**
    * Receives notification of a modification to a function.
    *
    * @param event  the event.
    */
   public void clearSelectedNodes();
   public void toggleSelectedNode(int series, int node);
   public void replaceSelectedNode(int series, int node);
   public void addNode(int series, double x, double y);
   public void deleteNode(int series, int node);
   public void duplicateNode(int series, int node);
   public void dragSelectedNodes(int series, int node, double dragVector[]);

}
