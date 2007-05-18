package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.pub.OpenSimDB;

public final class MyUndoAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        OpenSimDB.getInstance().undo();
    }
    
    public String getName() {
        return NbBundle.getMessage(MyUndoAction.class, "CTL_UndoAction");
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

    public boolean isEnabled() {
        boolean retValue;
        
        retValue = OpenSimDB.getInstance().canUndo();
        return retValue;
    }

    
}
