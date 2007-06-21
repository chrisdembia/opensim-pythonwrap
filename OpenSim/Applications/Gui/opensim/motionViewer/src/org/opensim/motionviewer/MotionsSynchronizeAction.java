package org.opensim.motionviewer;

import java.util.Hashtable;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.view.ExplorerTopComponent;

public final class MotionsSynchronizeAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        Hashtable <MotionsNode,Boolean> usedMotionNodes = new Hashtable<MotionsNode,Boolean>(selected.length);
        for(int i=0; i<selected.length; i++) {
           if(!(selected[i] instanceof OneMotionNode)) return false; // one of the nodes is not a OneMotionNode
           MotionsNode parent = (MotionsNode)selected[i].getParentNode();
           if(usedMotionNodes.containsKey(parent)) return false; // trying to pick multiple motions for the same model
           usedMotionNodes.put(parent, true);
        }
        return (selected.length>1);
    }
    /**
     * Action works by flushing all motions and then adding selected motions one at a time
     */
    public void performAction() {
        // TODO implement action body
       Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
       for(int i=0; i<selected.length; i++){
            OneMotionNode node =((OneMotionNode)selected[i]);
            Model model = node.getModel();
            if (i==0){
                MotionsDB.getInstance().flushMotions(model);
            }
            MotionsDB.getInstance().addSyncMotion(model, (Storage) node.getOpensimObject());
       }
    }
    
    public String getName() {
        return NbBundle.getMessage(MotionsSynchronizeAction.class, "CTL_MotionsSynchronizeAction");
    }
    
    protected String iconResource() {
        return "org/opensim/view/camera.gif";
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
