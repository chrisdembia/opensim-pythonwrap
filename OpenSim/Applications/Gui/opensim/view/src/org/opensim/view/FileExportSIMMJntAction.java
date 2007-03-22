package org.opensim.view;

import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.modeling.SimmFileWriter;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 * A Class represnting the Action of exporting an OpenSim model to SIMM's jnt format.
 * The exported model is the "Current" model in the GUI as indicated by the explorer window.
 */
public final class FileExportSIMMJntAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        Model mdl = OpenSimDB.getInstance().getCurrentModel();
        if (mdl != null){
            
            String jntFileName = FileUtils.getInstance().browseForFilename(".jnt", "SIMM .jnt file", false);
            if (jntFileName!=null){
                // Make sure we have the right extension.
                if (!jntFileName.endsWith(".jnt"))
                    jntFileName = jntFileName+".jnt";
                // Create a SimmFileWriter for the model and invoke its writeJointFile
                new SimmFileWriter(mdl).writeJointFile(jntFileName);
                StatusDisplayer.getDefault().setStatusText("Exported SIMM jnt file for model "+
                        mdl.getName()+" to file "+jntFileName+".");
            }
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(FileExportSIMMJntAction.class, "CTL_ExportSIMMJntAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        setEnabled(false);
        ViewDB.getInstance().registerModelCommand(this);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }

    public boolean isEnabled() {
       return OpenSimDB.getInstance().getCurrentModel()!=null;
   }

}
