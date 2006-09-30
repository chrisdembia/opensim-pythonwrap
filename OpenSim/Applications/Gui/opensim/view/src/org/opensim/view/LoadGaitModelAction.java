package org.opensim.view;

import java.io.IOException;
import java.net.URL;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.TheApp;

public final class LoadGaitModelAction extends CallableSystemAction {
    
    public void performAction() {
        try {
                // TODO better layout for models, bones, use relative path
            URL modelURL = this.getClass().getResource("resources/gait2392_gillette.osim");
                ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.OpenOsimModelAction"))).
                        loadModel(modelURL);
        } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
        } catch (IOException ex) {
            DialogDisplayer.getDefault().notify(
                    new NotifyDescriptor.Message("Model could not be located. Please file a bug!"));
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(LoadGaitModelAction.class, "CTL_LoadGaitModelAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(LoadGaitModelAction.class);
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
