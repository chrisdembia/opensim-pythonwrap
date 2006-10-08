package org.opensim.view;

import java.io.IOException;
import java.net.URL;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.TheApp;

public final class LoadGaitModelAction extends CallableSystemAction {
    
    public void performAction() {
    }
    
    public String getName() {
        return NbBundle.getMessage(LoadGaitModelAction.class, "CTL_LoadGaitModelAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(LoadGaitModelAction.class);
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
