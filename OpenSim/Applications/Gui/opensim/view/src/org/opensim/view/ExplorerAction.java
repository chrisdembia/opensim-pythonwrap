package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows Explorer component.
 */
public class ExplorerAction extends AbstractAction {
    
    public ExplorerAction() {
        super(NbBundle.getMessage(ExplorerAction.class, "CTL_ExplorerAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(ExplorerTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = ExplorerTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
