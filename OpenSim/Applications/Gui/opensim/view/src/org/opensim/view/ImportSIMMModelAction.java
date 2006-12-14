package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ImportSIMMModelAction extends CallableSystemAction {
    
    public void performAction() {
        // Browse for SIMM model
        
    }
    
    public String getName() {
        return NbBundle.getMessage(ImportSIMMModelAction.class, "CTL_ImportSIMMModelAction");
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
