package org.opensim.view;

import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.pub.ViewDB;

public final class ObjectDisplayHideAction extends CallableSystemAction {

   private Model getModel(OpenSimObject object) {
      AbstractActuator act = AbstractActuator.safeDownCast(object);
      if (act != null)
         return act.getModel();
      AbstractBody body = AbstractBody.safeDownCast(object);
      if (body != null)
         return body.getDynamicsEngine().getModel();
      return null;
   }
    public boolean isEnabled() {
       // The "hide" option is enabled unless every selected node is hidden.
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        for(int i=0; i < selected.length; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            if (objectNode.getChildren().getNodesCount()>0)
                return true;
            int displayStatus = ViewDB.getInstance().getDisplayStatus(objectNode.getOpensimObject());
            if (displayStatus == 1 || displayStatus == 2)
               return true;
        }
        return false;
    }

   public void performAction() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      for(int i=0; i < selected.length; i++){
         OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            applyOperationToNode(objectNode);
      }
      ViewDB.getInstance().repaintAll();
   }

    private void applyOperationToNode(final OpenSimObjectNode objectNode) {
        OpenSimObject obj = objectNode.getOpensimObject();
        Children ch = objectNode.getChildren();
        if (ch.getNodesCount()>0){
            // apply action recursively
            Node[] childNodes=ch.getNodes();
            for(int child=0; child < childNodes.length ; child++){
               OpenSimObjectNode childNode = (OpenSimObjectNode) childNodes[child];
               applyOperationToNode(childNode);
            }
        }
        ViewDB.getInstance().toggleObjectsDisplay(obj, false);
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
