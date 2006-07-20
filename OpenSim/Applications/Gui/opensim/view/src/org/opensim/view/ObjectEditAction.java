package org.opensim.view;

import javax.swing.JFrame;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.OpenSimObject;

public final class ObjectEditAction extends CallableSystemAction {
    OpenSimObject objectToEdit;
    OpenSimCanvas canvas;
    
    public ObjectEditAction(OpenSimObject objectToEdit, OpenSimCanvas canvas)
    {
        this.objectToEdit = objectToEdit;
        this.canvas = canvas;
    }
    public void performAction() {
        // TODO implement action body
        //new ObjectEditorJDialog(new JFrame(), true).setVisible(true);
    }
    
    public String getName() {
        return NbBundle.getMessage(ObjectEditAction.class, "CTL_ObjectEditAction");
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
