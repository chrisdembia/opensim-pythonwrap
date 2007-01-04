package org.opensim.view;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.OpenSimObjectNode;

public final class ObjectDisplayShowAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // Enable show only if all nodes are hidden and vice versa
        boolean allHidden = true;
        for(int i=0; i < selected.length && allHidden; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            allHidden = allHidden && !ViewDB.getInstance().getDisplayStatus(objectNode.getOpensimObject());
        }
        return allHidden;
    }

    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        for(int i=0; i < selected.length; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            ViewDB.getInstance().toggleObjectDisplay(objectNode.getOpensimObject());
        }        
    }
    
    public String getName() {
        return NbBundle.getMessage(ModelDisplayHideAction.class, "CTL_ModelDisplayShowAction");
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
