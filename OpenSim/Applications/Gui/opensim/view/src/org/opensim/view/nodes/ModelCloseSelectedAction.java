package org.opensim.view.nodes;

import org.openide.NotifyDescriptor;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.ModelSettingsSerializer;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class ModelCloseSelectedAction extends CallableSystemAction {
   
    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // Action shouldn't be available otherwise'
        ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
        Model mdl = modelNode.getModel();
        // Confirm closing
        // Write settings to persistent storage
        ModelSettingsSerializer ser = ViewDB.getInstance().getModelSavedSettings(mdl);
        if (ser.confirmAndWrite()==NotifyDescriptor.CANCEL_OPTION)
            return;

        OpenSimDB.getInstance().removeModel(mdl);
    }
   
   public String getName() {
      return NbBundle.getMessage(ModelCloseSelectedAction.class, "CTL_ModelCloseSelectedAction");
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
