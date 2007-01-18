package org.opensim.view.editors;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows MuscleEditor component.
 */
public class MuscleEditorAction extends AbstractAction {
    
    public MuscleEditorAction() {
        super(NbBundle.getMessage(MuscleEditorAction.class, "CTL_MuscleEditorAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(MuscleEditorTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = MuscleEditorTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
