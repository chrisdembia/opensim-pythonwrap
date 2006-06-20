package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows StdOutPanel component.
 */
public class StdOutPanelAction extends AbstractAction {
    
    public StdOutPanelAction() {
        super(NbBundle.getMessage(StdOutPanelAction.class, "CTL_StdOutPanelAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(StdOutPanelTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = StdOutPanelTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
