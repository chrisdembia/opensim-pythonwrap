package org.opensim.view;

import java.util.Vector;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;

public final class ObjectDisplayOpacityAction extends CallableSystemAction {
   
   public void performAction() {
      Vector<OpenSimObject> objects = new Vector<OpenSimObject>();
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      for(int i=0; i<selected.length; i++) {
         if(selected[i] instanceof OpenSimObjectNode)
            addLeafObjects((OpenSimObjectNode)selected[i], objects);
      }
      ObjectDisplayOpacityPanel.showDialog(objects);
   }

   public void addLeafObjects(OpenSimObjectNode node, Vector<OpenSimObject> objects) {
      Children ch = node.getChildren();
      if(ch.getNodesCount()>0) {
         for(Node childNode : ch.getNodes()) {
            if(childNode instanceof OpenSimObjectNode)
               addLeafObjects((OpenSimObjectNode)childNode, objects);
         }
      } else objects.add(node.getOpenSimObject());
   }
   
   public String getName() {
      return NbBundle.getMessage(ObjectDisplayOpacityAction.class, "CTL_ObjectDisplayOpacityAction");
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

   // Make it available only if selected objects have representation and belong to same model
    public boolean isEnabled() {
       // The "hide" option is enabled unless every selected node is hidden.
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        boolean isColorable=true;
        for(int i=0; i<selected.length && isColorable; i++){
            isColorable = (selected[i] instanceof OpenSimObjectNode);
            if (isColorable){
                OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
                isColorable=objectNode.getValidDisplayOptions().contains(displayOption.Colorable);
            }
        }
        return isColorable;
    }
}
