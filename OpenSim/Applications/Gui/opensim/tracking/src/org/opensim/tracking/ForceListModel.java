/*
 * ForceListModel.java
 *
 * Created on January 28, 2010, 3:59 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.tracking;

import javax.swing.DefaultListModel;
import org.opensim.modeling.Force;
import org.opensim.modeling.ForceSet;

/**
 *
 * @author ayman
 */
public class ForceListModel extends DefaultListModel {
    ForceSet  fSet;
    /** Creates a new instance of ForceListModel */
    public ForceListModel(ForceSet fSet) {
        super();
        this.fSet = fSet;
        initModel();
    }

    private void initModel() {
        clear();
        for (int i=0; i<fSet.getSize(); i++){
            Force f= fSet.get(i);
            add(i, f);
        }
    }
    
}
