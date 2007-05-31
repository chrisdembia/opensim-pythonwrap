package org.opensim.view;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.pub.ViewDB;

public class ObjectDisplayChangeRepAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // If any selected object is hidden (or any selected group is mixed), return false.
        for(int i=0; i < selected.length; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            int displayStatus = ViewDB.getInstance().getDisplayStatus(objectNode.getOpensimObject());
            if (displayStatus == 0 || displayStatus == 2)
               return false;
        }
        return true;
    }

    public void performAction() {
       // unimplemneted by design
      throw new UnsupportedOperationException("Method should never be called!");
    }
    /**
     * A variation of performAction that takes the desired representation and applies it to the model
     */
     public void performAction(int newRep, int newShading) {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        for(int i=0; i < selected.length; i++){
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            ViewDB.getInstance().setObjectRepresentation(objectNode.getOpensimObject(), newRep, newShading);
         }        
    }
  
    public String getName() {
        return "unused";
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
