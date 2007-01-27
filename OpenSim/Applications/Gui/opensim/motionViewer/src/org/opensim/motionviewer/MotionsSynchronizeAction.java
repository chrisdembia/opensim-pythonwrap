package org.opensim.motionviewer;

import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.ExplorerTopComponent;

public final class MotionsSynchronizeAction extends CallableSystemAction {
    
    public boolean isEnabled() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
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
            AbstractModel model = node.getModel();
            if (i==0)
                MotionsDB.getInstance().flushMotions(model);
            MotionsDB.getInstance().addSyncMotion(model, (SimmMotionData) node.getOpensimObject());
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
