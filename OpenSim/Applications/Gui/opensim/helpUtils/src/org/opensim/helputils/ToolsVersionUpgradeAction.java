package org.opensim.helputils;

import java.io.IOException;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Storage;

public final class ToolsVersionUpgradeAction extends CallableSystemAction {
    
    public void performAction() {
        ToolsVersionUpgradeJPanel upgradePanel = new ToolsVersionUpgradeJPanel();
        DialogDescriptor dlg = new DialogDescriptor(upgradePanel, "Version Update File");
        //dlg.setValid(false);
        DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
        Object userInput = dlg.getValue();
        
        if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
            String input = upgradePanel.getInputFileName();
            String output = upgradePanel.getOutputFileName();
            if (input!=null && output !=null){
                if (upgradePanel.getExtension().equalsIgnoreCase(".osim")){
                    try {
                        Model mdl = new Model(input);
                        mdl.initSystem();
                        boolean saveDefaults = OpenSimObject.getSerializeAllDefaults();
                        OpenSimObject.setSerializeAllDefaults(upgradePanel.isWriteDefaults());
                        mdl.copy().print(output);
                        OpenSimObject.setSerializeAllDefaults(saveDefaults);
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
               else if (upgradePanel.getExtension().equalsIgnoreCase(".xml")){
                    OpenSimObject obj = OpenSimObject.makeObjectFromFile(input);
                    boolean saveDefaults = OpenSimObject.getSerializeAllDefaults();
                    OpenSimObject.setSerializeAllDefaults(upgradePanel.isWriteDefaults());
                    obj.copy().print(output);
                    OpenSimObject.setSerializeAllDefaults(saveDefaults);
                }
                else if (upgradePanel.getExtension().equalsIgnoreCase(".sto")){
                    try {
                        Storage sto = new Storage(input);
                        sto.setInDegrees(upgradePanel.isMarkInDegrees());
                        sto.print(output);
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
            }
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(ToolsVersionUpgradeAction.class, "CTL_ToolsVersionUpgradeAction");
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
