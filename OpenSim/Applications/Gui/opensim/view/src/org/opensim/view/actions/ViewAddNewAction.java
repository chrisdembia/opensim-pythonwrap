package org.opensim.view.actions;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.pub.ViewDB;

public final class ViewAddNewAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Get current view window from ViewDB and create a new one 
        ViewDB.getInstance().addViewWindow();
    }
    
    public String getName() {
        return NbBundle.getMessage(ViewAddNewAction.class, "CTL_ViewAddNewAction");
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
