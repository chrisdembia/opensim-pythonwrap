package org.opensim.view;

import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.nodes.OpenSimObjectSetNode;
import org.opensim.view.pub.ViewDB;

public final class ObjectDisplayShowOnlyAction extends CallableSystemAction {
   
   public boolean isEnabled() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if (selected.length==0) return false;
      Object  parent = selected[0].getParentNode();
      boolean sameParent=true;
      for(int i=0; i < selected.length && sameParent; i++){
          sameParent = (selected[i].getParentNode().equals(parent));
      }
      return sameParent;
   }
   
   public void performAction() {
      // TODO implement action body
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      // The general scenario is to hide parent then show node and children
      // one exception is if the parent node is a model since hiding it in this case
      // makes it impossible to show selected node. This sitution is handled by overriding the behavior
      // in appropriate nodes.
      for(int i=0; i < selected.length; i++){
         if (!(selected[i] instanceof OpenSimObjectNode))
                continue;
         
         OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
         Object  parent = objectNode.getParentNode();
         if (parent instanceof OpenSimObjectNode){
            OpenSimObjectNode parentNode = (OpenSimObjectNode) parent;
            // For Actuators we want to go up to the ActuatorSet node rather than the group node
            // A cleaner solution would be to make nodes hold pointer to which node would
            // show only be relative to.
            while (!(parentNode instanceof OpenSimObjectSetNode) && 
                    !(parentNode instanceof ConcreteModelNode))
                parentNode = (OpenSimObjectNode) (parentNode.getParentNode());
            
            if (parentNode instanceof OpenSimObjectSetNode){
                OpenSimObjectSetNode setNode=(OpenSimObjectSetNode) parentNode;
                Children children=setNode.getChildren();
                Node[] childNodes = children.getNodes();
                for(int j=0; j<childNodes.length; j++){
                    OpenSimObjectNode n = (OpenSimObjectNode) childNodes[j];
                    ViewDB.getInstance().toggleObjectsDisplay(n.getOpenSimObject(), false);                    
                }
            }
            else
                ViewDB.getInstance().toggleObjectsDisplay(parentNode.getOpenSimObject(), false);
         }
      }
      for(int i=0; i < selected.length; i++){
         if (!(selected[i] instanceof OpenSimObjectNode))
                continue;
         OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
         ViewDB.getInstance().toggleObjectDisplay(objectNode.getOpenSimObject(), true);
      }
      ViewDB.getInstance().repaintAll();
   }
   
   public String getName() {
      return NbBundle.getMessage(ObjectDisplayShowOnlyAction.class, "CTL_ObjectDisplayShowOnlyAction");
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
