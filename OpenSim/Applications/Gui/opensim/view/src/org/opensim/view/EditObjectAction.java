package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows EditObject component.
 */
public class EditObjectAction extends AbstractAction {
    
    public EditObjectAction() {
        super(NbBundle.getMessage(EditObjectAction.class, "CTL_EditObjectAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(EditObjectTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = EditObjectTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
