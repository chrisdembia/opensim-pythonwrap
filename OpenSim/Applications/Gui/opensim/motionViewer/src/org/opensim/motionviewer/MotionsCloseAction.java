package org.opensim.motionviewer;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Storage;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.motionviewer.OneMotionNode;

public final class MotionsCloseAction extends CallableSystemAction {
   
   public void performAction() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      for(int i=0; i<selected.length; i++) {
         if(selected[i] instanceof OneMotionNode) { // Should be the case anyway (otherwise this action would not be enabled), but doesn't hurt to double check
            OneMotionNode node = (OneMotionNode)selected[i];
            MotionsDB.getInstance().closeMotion(node.getModel(), (Storage)node.getOpenSimObject(), true);
         }
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(MotionsCloseAction.class, "CTL_MotionsCloseAction");
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
   
   public boolean isEnabled() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      for(int i=0; i<selected.length; i++) if(!(selected[i] instanceof OneMotionNode)) return false; // one of the nodes is not a OneMotionNode
      return true;
   }
}
