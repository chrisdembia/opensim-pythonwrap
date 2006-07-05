package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class LoadDemoModelAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        new OpenOsimModelAction().loadModel("C:/Downloads/MODEL/dynamic.xml");
    }
    
    public String getName() {
        return NbBundle.getMessage(LoadDemoModelAction.class, "CTL_LoadDemoModelAction");
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
