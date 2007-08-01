package org.opensim.view;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.modeling.SimmFileWriter;
import org.opensim.view.actions.OpenSimToSIMMOptionsJPanel;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 * A Class represnting the Action of exporting an OpenSim model to SIMM's jnt format.
 * The exported model is the "Current" model in the GUI as indicated by the explorer window.
 */
public final class FileExportSIMMJntAction extends CallableSystemAction {
    
    class ExportDlgListener implements ActionListener, PropertyChangeListener
    {
        DialogDescriptor dlgOfInterest;
        ExportDlgListener(DialogDescriptor aDialog)
        {
            super();
            dlgOfInterest=aDialog;
            dlgOfInterest.addPropertyChangeListener(this);
        }

        public void actionPerformed(ActionEvent e) {
            dlgOfInterest.setValid(!dlgOfInterest.isValid());
        }

        public void propertyChange(PropertyChangeEvent evt) {
            String name=evt.getPropertyName();
            int i=0;
        }
    }
    public void performAction() {
        // TODO implement action body
        Model mdl = OpenSimDB.getInstance().getCurrentModel();
        if (mdl != null){
            OpenSimToSIMMOptionsJPanel exportPanel = new OpenSimToSIMMOptionsJPanel();
            DialogDescriptor dlg = new DialogDescriptor(exportPanel, "Export SIMM Model");
            dlg.setValid(false);
            dlg.setButtonListener(new ExportDlgListener(dlg));
            DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
            Object userInput = dlg.getValue();
            if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
                String jntfileName = exportPanel.getJointFilename();
                if (jntfileName==null)
                    return;
                // Make sure we have the right extension.
                if (!jntfileName.endsWith(".jnt"))
                    jntfileName = jntfileName+".jnt";
                SimmFileWriter modelWriter=new SimmFileWriter(mdl);
                modelWriter.writeJointFile(jntfileName);

                // Now the muscles
                String mslfileName = exportPanel.getMslFilename();
                if (mslfileName==null || mslfileName.equalsIgnoreCase(""))
                    return;
                // Make sure we have the right extension.
                if (!mslfileName.endsWith(".msl"))
                    mslfileName = mslfileName+".msl";
                modelWriter.writeMuscleFile(mslfileName);
                StatusDisplayer.getDefault().setStatusText("Exported SIMM jnt & muscle files for model "+
                        mdl.getName()+".");
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
