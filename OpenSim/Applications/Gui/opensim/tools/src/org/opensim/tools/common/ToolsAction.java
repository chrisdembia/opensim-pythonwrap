package org.opensim.tools.common;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows Tools component.
 */
public class ToolsAction extends AbstractAction {
    
    public ToolsAction() {
        super(NbBundle.getMessage(ToolsAction.class, "CTL_ToolsAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(ToolsTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = ToolsTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
