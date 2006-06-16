package org.opensim.view;

import javax.swing.JFileChooser;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.common.OpenSimDB;

public final class OpenOsimModelAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
        final JFileChooser dlog = new JFileChooser();
        
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            OpenSimDB.getInstance().addModel(dlog.getSelectedFile().getAbsolutePath());
        }

    }
    
    public String getName() {
        return NbBundle.getMessage(OpenOsimModelAction.class, "CTL_OpenOsimModel");
    }
    
    protected String iconResource() {
        return "org/opensim/view/integrator.gif";
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
