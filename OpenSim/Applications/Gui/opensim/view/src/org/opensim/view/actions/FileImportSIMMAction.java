package org.opensim.view.actions;

import java.io.File;
import java.io.IOException;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.logger.OpenSimLogger;
import org.opensim.view.base.ExecOpenSimProcess;
import org.opensim.view.FileOpenOsimModelAction;

public final class FileImportSIMMAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        SimmToOpenSimOptionsJPanel importPanel = new SimmToOpenSimOptionsJPanel();
        DialogDescriptor dlg = new DialogDescriptor(importPanel, "Import Options");
        DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
        Object userInput = dlg.getValue();
        if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
            String jntfileName = importPanel.getJointFilename();
            if (jntfileName==null)
                return;
            String mslfileName = importPanel.getMslFilename();
            String engineString = importPanel.getDynamicsEngine();
            String anglesString = importPanel.getAngleConvention();
            String command="simmToOpenSim -j \""+jntfileName+"\"";
            
            if (mslfileName!=null)
                command += " -m \""+mslfileName+"\"";
            if (engineString.compareToIgnoreCase("Simbody")==0)
                command += " -e Simbody ";
            // simmToOpenSim is assumed in the Path, similar to other dlls we depend on.
            File f = new File(jntfileName);
            File jntFileDir = f.getParentFile();
            String tempFilename=null;
            try {
                File tmpFile = File.createTempFile("SimmToOpenSim", ".osim", jntFileDir);
                tempFilename= tmpFile.getAbsolutePath();
            } catch (IOException ex) {
                DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Message("Could not create a temporary file to perform model conversion. Check permissions."));
                return;
            }
            
            command+=" -x \""+tempFilename+"\"";
            OpenSimLogger.logMessage("Executing ["+command+"]", 0);
            boolean success = ExecOpenSimProcess.execute(command, new String[]{""}, jntFileDir );
            if (success){
                try {
                    // Display original model
                    ((FileOpenOsimModelAction) FileOpenOsimModelAction.findObject(
                            Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(tempFilename);
                } catch (ClassNotFoundException ex) {
                    ex.printStackTrace();
                } catch (IOException ex) {
                    DialogDisplayer.getDefault().notify(
                            new NotifyDescriptor.Message("Model could not be located. Please file a bug!"));
                };
            }
        }
    }
    public String getName() {
        return NbBundle.getMessage(FileImportSIMMAction.class, "CTL_FileImportSIMMAction");
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
