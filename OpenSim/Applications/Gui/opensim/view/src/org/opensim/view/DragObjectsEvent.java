/*
 * DragObjectsEvent.java
 *
 * Created on April 12, 2007, 11:30 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.EventObject;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class DragObjectsEvent extends EventObject {

   private double dragVector[] = null; 
    /** Creates a new instance of DragObjectsEvent
     *  dragVector is the vector in the world frame that the
     * objects should be dragged along.
     */
    public DragObjectsEvent(OpenSimObject source, double dragVector[]) {
       super(source);
       this.dragVector = new double[3];
       this.dragVector[0] = dragVector[0];
       this.dragVector[1] = dragVector[1];
       this.dragVector[2] = dragVector[2];
    }

    public OpenSimObject getObject()
    {
        return (OpenSimObject) source;
    }

    public String getName()
    {
        return ((OpenSimObject) source).getName();
    }

    public double[] getDragVector()
    {
        return dragVector;
    }

}
