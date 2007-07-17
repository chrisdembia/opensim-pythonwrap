package org.opensim.motionviewer;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.motionviewer.OneMotionNode;

public final class MotionsSaveAsAction extends CallableSystemAction {
   
   public void performAction() {
      System.out.println("Save as");
      // TODO implement action body
   }
   
   public String getName() {
      return NbBundle.getMessage(MotionsSaveAsAction.class, "CTL_MotionsSaveAsAction");
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
      return (selected.length==1 && (selected[0] instanceof OneMotionNode));
   }
}
