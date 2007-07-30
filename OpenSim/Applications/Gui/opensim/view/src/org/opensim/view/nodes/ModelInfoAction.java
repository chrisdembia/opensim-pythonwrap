package org.opensim.view.nodes;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.TheApp;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.pub.ViewDB;
import org.opensim.modeling.Model;


public final class ModelInfoAction extends CallableSystemAction {
    
    public void performAction() {
        ModelInfoDialog dlg=new ModelInfoDialog(TheApp.getAppFrame(), true);
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // Action shouldn't be available otherwise'
        ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
        Model mdl = modelNode.getModel();
        dlg.setModelName(mdl.getName());
        dlg.setModelFile(mdl.getInputFileName());
        dlg.setAuthors(
                "Model developed by..");
        dlg.setReferences("Reference:IEEE TBME, vol. vv, pp. 1-2, 2000.");
        dlg.setVisible(true);
    }
    
    public String getName() {
        return NbBundle.getMessage(ModelInfoAction.class, "CTL_ModelInfoAction");
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
