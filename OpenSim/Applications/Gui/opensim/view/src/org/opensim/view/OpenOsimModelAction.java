package org.opensim.view;

import javax.swing.JFileChooser;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.common.OpenSimDB;
import org.opensim.modeling.SimmModel;

public final class OpenOsimModelAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
        final JFileChooser dlog = new JFileChooser();
        
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            // Make the model
            SimmModel aModel = new SimmModel(dlog.getSelectedFile().getAbsolutePath());
            aModel.setup();
            // Make the window
            ModelWindowVTKTopComponent modelWindow = new ModelWindowVTKTopComponent(aModel);
            modelWindow.open();
            OpenSimDB.getInstance().addObserver(modelWindow);
            OpenSimDB.getInstance().addModel(aModel);
            //BottomPanelTopComponent.findInstance().showLogMessage("Model has been created from file "+dlog.getSelectedFile().getAbsolutePath()+"\n");
        }

    }
    
    public String getName() {
        return NbBundle.getMessage(OpenOsimModelAction.class, "CTL_OpenOsimModel");
    }
    
    protected String iconResource() {
        return null;
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
