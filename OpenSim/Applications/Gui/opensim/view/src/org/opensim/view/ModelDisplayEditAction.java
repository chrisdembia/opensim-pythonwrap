package org.opensim.view;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.pub.ViewDB;

public final class ModelDisplayEditAction extends CallableSystemAction {
    
    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // Action shouldn't be available otherwise'
        ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
        ViewDB.getInstance().adjustModelDisplayOffset(modelNode.getModel());
    }
    
    public String getName() {
        return NbBundle.getMessage(ModelDisplayEditAction.class, "CTL_ModelDisplayEditAction");
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
