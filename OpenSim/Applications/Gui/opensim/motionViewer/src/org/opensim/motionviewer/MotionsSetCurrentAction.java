package org.opensim.motionviewer;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Storage;
import org.opensim.view.ExplorerTopComponent;

public final class MotionsSetCurrentAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        return (selected.length==1);
    }
    
    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        OneMotionNode node = (OneMotionNode)selected[0];
        MotionsDB.getInstance().setCurrent(node.getModel(), (Storage)node.getOpensimObject());
    }
    
    public String getName() {
        return NbBundle.getMessage(MotionsSetCurrentAction.class, "CTL_MotionsSetCurrentAction");
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
