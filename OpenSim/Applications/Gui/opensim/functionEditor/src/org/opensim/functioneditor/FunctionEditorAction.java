package org.opensim.functioneditor;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows FunctionEditor component.
 */
public class FunctionEditorAction extends AbstractAction {
    
    public FunctionEditorAction() {
        super(NbBundle.getMessage(FunctionEditorAction.class, "CTL_FunctionEditorAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(FunctionEditorTopComponent.ICON_PATH, true)));
    }
    
    public void actionPerformed(ActionEvent evt) {
        TopComponent win = FunctionEditorTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
    
}
