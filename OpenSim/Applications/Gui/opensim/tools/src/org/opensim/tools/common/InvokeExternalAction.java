package org.opensim.tools.common;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class InvokeExternalAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Show a panel with command line, environment variables, directory browser.
    }
    
    public String getName() {
        return NbBundle.getMessage(InvokeExternalAction.class, "CTL_InvokeExternalAction");
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
