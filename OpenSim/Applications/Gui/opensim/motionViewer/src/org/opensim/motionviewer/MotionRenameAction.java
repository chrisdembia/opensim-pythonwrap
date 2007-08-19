package org.opensim.motionviewer;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.pub.OpenSimDB;

public final class MotionRenameAction extends CallableSystemAction {
   
    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        OneMotionNode objectNode = (OneMotionNode)selected[0];
        NotifyDescriptor.InputLine dlg =
                new NotifyDescriptor.InputLine("Current Name: "+objectNode.getOpenSimObject().getName(), "Rename Object");
        if(DialogDisplayer.getDefault().notify(dlg)==NotifyDescriptor.OK_OPTION){
            String newName = dlg.getInputText();
            if (OpenSimDB.getInstance().validateName(newName, true)){
                objectNode.getOpenSimObject().setName(newName);
                objectNode.setName(newName);  // Force navigartor window update
                MotionsDB.getInstance().renameMotion(objectNode.getOpenSimObject(), newName);
            }
            else
                 DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Provided name "+newName+" is not valid"));                
        }
        
    }
    
   public String getName() {
      return NbBundle.getMessage(MotionRenameAction.class, "CTL_MotionRenameAction");
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
      return (selected.length==1);
   }
   
}
