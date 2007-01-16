package org.opensim.view;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.pub.ViewDB;

public final class ModelDisplayShowAction extends CallableSystemAction {
    
    static String commandName = NbBundle.getMessage(ModelDisplayShowAction.class, "CTL_ModelDisplayShowAction");

    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
        return !ViewDB.getInstance().getDisplayStatus(modelNode.getModel());
    }

    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
        ViewDB.getInstance().toggleModelDisplay(modelNode.getModel());
    }
    
    public String getName() {
        return commandName;
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
