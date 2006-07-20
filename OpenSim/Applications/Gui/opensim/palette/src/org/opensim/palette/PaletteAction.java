package org.opensim.palette;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows Palette component.
 */
public class PaletteAction extends AbstractAction {
    
    public PaletteAction() {
        super(NbBundle.getMessage(PaletteAction.class, "CTL_PaletteAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(PaletteTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = PaletteTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
