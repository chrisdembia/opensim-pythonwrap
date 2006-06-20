package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows ModelWindowVTK component.
 */
public class ModelWindowVTKAction extends AbstractAction {
    
    public ModelWindowVTKAction() {
        super(NbBundle.getMessage(ModelWindowVTKAction.class, "CTL_ModelWindowVTKAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(ModelWindowVTKTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = ModelWindowVTKTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
