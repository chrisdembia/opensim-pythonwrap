package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

/**
 * A Class representing the action of replicating a graphics window. 
 * Only the geometry is replicated. Cameras, background color are not.
 *
 * @todo this class should be final per netBeans 
 */
public class ViewReplicateAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Get current view window from ViewDB and create a new one 
        ViewDB.getInstance().addViewWindow();
    }
    
    public String getName() {
        return NbBundle.getMessage(ViewReplicateAction.class, "CTL_ReplicateViewAction");
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
