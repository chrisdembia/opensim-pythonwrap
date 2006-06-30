package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.OpenSimObject;

public final class ModifyObjectVisibilityAction extends CallableSystemAction {
    
    OpenSimObject object;
    OpenSimCanvas canvas;
    
    public ModifyObjectVisibilityAction(OpenSimObject object, OpenSimCanvas canvas)
    {
        this.object = object;
        this.canvas = canvas;
    }
    
    public void performAction() {
        // TODO implement action body
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new VisibilityJDialog(new javax.swing.JFrame(), canvas, object).setVisible(true);
            }
        });
     }
    
    public String getName() {
        return NbBundle.getMessage(ModifyObjectVisibilityAction.class, "CTL_ModifyObjectVisibilityAction");
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
