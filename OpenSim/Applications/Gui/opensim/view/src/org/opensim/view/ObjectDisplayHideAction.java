package org.opensim.view;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.OpenSimObjectNode;

public final class ObjectDisplayHideAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        boolean anyHidden = false;
        for(int i=0; i < selected.length && !anyHidden; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            anyHidden = anyHidden || !ViewDB.getInstance().getDisplayStatus(objectNode.getOpensimObject());
        }
        return !anyHidden;
    }

    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        for(int i=0; i < selected.length; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            ViewDB.getInstance().toggleObjectDisplay(objectNode.getOpensimObject());
        }        
    }
    
    public String getName() {
        return NbBundle.getMessage(ModelDisplayHideAction.class, "CTL_ModelDisplayHideAction");
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
