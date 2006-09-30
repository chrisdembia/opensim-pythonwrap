package org.opensim.view;

import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmModel;
import org.opensim.utils.FileUtils;
import org.opensim.utils.TheApp;


public final class ExportSIMMJntAction extends CallableSystemAction {
    
    ModelWindowVTKTopComponent active;

    public void performAction() {
        // TODO implement action body
        active = ViewDB.getInstance().getCurrentModelWindow();
        if (active != null){
             String defaultDir="";
            defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
            final JFileChooser dlog = new JFileChooser(defaultDir);
            dlog.setFileFilter(FileUtils.getFileFilter(".jnt", "SIMM .jnt file"));

            SimmModel mdl = active.getModel();
            StatusDisplayer.getDefault().setStatusText("Exporting SIMM jnts of "+mdl.getName()+"to file.");
            mdl.writeSIMMJointFile("save.jnt");
            StatusDisplayer.getDefault().setStatusText("");
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(ExportSIMMJntAction.class, "CTL_ExportSIMMJntAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        setEnabled(false);
        ViewDB.registerModelCommand(this);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
