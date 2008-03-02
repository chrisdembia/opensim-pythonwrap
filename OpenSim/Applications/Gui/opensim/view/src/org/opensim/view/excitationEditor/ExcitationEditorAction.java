package org.opensim.view.excitationEditor;

import java.awt.Dialog;
import javax.swing.JButton;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ExcitationEditorAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
       //DialogDescriptor dd = new DialogDescriptor(new ExcitationEditorJPanel(), "Excitation Editor");
       //dd.setOptions(new Object[]{new JButton("Close")});
       //dd.setModal(false);
       //Dialog dlg = DialogDisplayer.getDefault().createDialog(dd);
       //dlg.setVisible(true);
        new ExcitationEditorJFrame().setVisible(true);
    }
    
    public String getName() {
        return NbBundle.getMessage(ExcitationEditorAction.class, "CTL_ExcitationEditorAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
