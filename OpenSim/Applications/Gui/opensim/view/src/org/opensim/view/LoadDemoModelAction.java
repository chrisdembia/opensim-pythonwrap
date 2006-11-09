package org.opensim.view;

import java.awt.Component;
import java.io.IOException;
import javax.swing.JButton;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class LoadDemoModelAction extends CallableSystemAction {
    
    public void performAction() {
        try {
            // TODO better layout for models, bones, use relative path
            ((OpenOsimModelAction) OpenOsimModelAction.findObject(Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel("./resources/models/demoModel/dynamic.xml");
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            DialogDisplayer.getDefault().notify(
                    new NotifyDescriptor.Message("Model could not be located. Please file a bug!"));
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(LoadDemoModelAction.class, "CTL_LoadDemoModelAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(LoadDemoModelAction.class);
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
