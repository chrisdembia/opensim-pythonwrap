package org.opensim.view.nodes;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.pub.ViewDB;

public final class IsolateCurrentModelAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      // Action shouldn't be available otherwise'
      ConcreteModelNode modelNode = (ConcreteModelNode) selected[0];
      Model mdl = modelNode.getModel();
      ViewDB.getInstance().isolateModel(mdl);
   }
  
   public String getName() {
      return NbBundle.getMessage(IsolateCurrentModelAction.class, "CTL_IsolateCurrentModelAction");
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
