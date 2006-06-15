package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows BottomPanel component.
 */
public class BottomPanelAction extends AbstractAction {
    
    public BottomPanelAction() {
        super(NbBundle.getMessage(BottomPanelAction.class, "CTL_BottomPanelAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(BottomPanelTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = BottomPanelTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
