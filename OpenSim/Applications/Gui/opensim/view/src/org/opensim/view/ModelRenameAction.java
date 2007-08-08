package org.opensim.view;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.nodes.ConcreteModelNode;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.pub.OpenSimDB;

public final class ModelRenameAction extends CallableSystemAction {
   
   public boolean isEnabled() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      return selected.length==1;
   }
   
   public void performAction() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if (selected.length == 1){
         OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[0];
         NotifyDescriptor.InputLine dlg =
                 new NotifyDescriptor.InputLine("Current Name: "+objectNode.getOpenSimObject().getName(), "Rename Object");
         if(DialogDisplayer.getDefault().notify(dlg)==NotifyDescriptor.OK_OPTION){
            String newName = dlg.getInputText();
            objectNode.getOpenSimObject().setName(newName);
            objectNode.setName(newName);  // Force navigartor window update
            // The following is specific to renaming a model since
            // other windows may display currentModel's name
            // A more generic scheme using events should be used.
            Model dModel = ((ConcreteModelNode)objectNode).getModel();
            if (dModel==OpenSimDB.getInstance().getCurrentModel())
               OpenSimDB.getInstance().setCurrentModel(dModel);   // Need to do this so that model dropdown updates
         }
         
      } else { // Should never happen
         DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Rename of multiple objects is not supported."));
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(ModelRenameAction.class, "CTL_ObjectRenameAction");
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
