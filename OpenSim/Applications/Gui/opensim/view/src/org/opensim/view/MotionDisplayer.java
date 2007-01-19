/*
 * MotionDisplayer.java
 *
 * Created on January 19, 2007, 9:06 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.Hashtable;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.SimmMotionData;

/**
 *
 * @author Ayman. This class is used to preprocess motion files (SimmMotionData or similar) so taht
 * 1. Maping column indices to markers, gcs, ... is done only once.
 * 2. If additional objects need to be created for force or other markers they are maintained here.
 * 3. This isolates the display code from the specifics of SimmMotionData so that OpenSim proper creatures can be used.
 */
public class MotionDisplayer {
    
    Hashtable<String, Integer> mapCoordinatesToIndices=new Hashtable<String, Integer>(40);
    private AbstractModel   model;
    
    /** Creates a new instance of MotionDisplayer */
    public MotionDisplayer(SimmMotionData motionData, AbstractModel model) {
        this.model = model;
        CoordinateSet coords = model.getDynamicsEngine().getCoordinateSet();
        for(int i=0; i<coords.getSize(); i++){
                mapCoordinatesToIndices.put(coords.get(i).getName(), 
                        new Integer(motionData.getColumnIndex(coords.get(i).getName())));
        }
    }
    public int getIndexInStorage(String gcName)
    {
        return mapCoordinatesToIndices.get(gcName).intValue();
    }

    public AbstractModel getModel() {
        return model;
    }
}
