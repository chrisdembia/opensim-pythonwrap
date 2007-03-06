package org.opensim.view.actions;

import java.io.File;
import java.io.IOException;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.base.ExecOpenSimProcess;
import org.opensim.utils.FileUtils;
import org.opensim.view.FileOpenOsimModelAction;

public final class FileImportSIMMAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
       String jntFileName = FileUtils.getInstance().browseForFilename(".jnt", "SIMM .jnt file", true);
        if (jntFileName!=null){
            // Make sure we have the right extension.
            if (!jntFileName.endsWith(".jnt"))
                jntFileName = jntFileName+".jnt";
            File f = new File(jntFileName);
            File jntFileDir = f.getParentFile();
            String tempFilename=null;
            try {
                File tmpFile = File.createTempFile("Simm2OpenSim", ".osim", jntFileDir);
                tempFilename= tmpFile.getAbsolutePath();
            } catch (IOException ex) {
                DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Message("Could not create a temporary file to perform model conversion. Check permissions."));
                return;
            }
            // simmToOpenSim is assumed in the Path, similar to other dlls we depend on.
            String command="simmToOpenSim -j "+jntFileName+" -x "+tempFilename;
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
