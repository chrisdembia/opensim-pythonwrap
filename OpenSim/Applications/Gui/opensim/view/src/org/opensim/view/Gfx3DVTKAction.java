package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows Gfx3DVTK component.
 */
public class Gfx3DVTKAction extends AbstractAction {
    
    public Gfx3DVTKAction() {
        super(NbBundle.getMessage(Gfx3DVTKAction.class, "CTL_Gfx3DVTKAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(Gfx3DVTKTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = Gfx3DVTKTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
