package org.opensim.swingui;


import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.BrowserLauncher;

public final class FileBug extends CallableSystemAction {
    
    public void performAction() {
        BrowserLauncher.openURL("https://simtk.org/tracker/?func=add&atid=322&group_id=91");
    }
    
    public String getName() {
        return NbBundle.getMessage(FileBug.class, "CTL_FileBug");
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
