package org.opensim.view.actions;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
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
        DialogDescriptor dlg = new DialogDescriptor(importPanel, "Import SIMM Model");
        //dlg.setValid(false);
        DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
        Object userInput = dlg.getValue();
        
        if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
            String jntfileName = importPanel.getJointFilename();
            if (jntfileName==null || jntfileName.equalsIgnoreCase("") ){
                DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("No valid .jnt file have been specified. Import aborted."));
                return;
            }
            String mslfileName = importPanel.getMslFilename();
            String engineString = importPanel.getDynamicsEngine();
            String command="simmToOpenSim -j \""+jntfileName+"\"";
            
            if (mslfileName!=null && !mslfileName.equalsIgnoreCase(""))
                command += " -m \""+mslfileName+"\"";
            if (engineString.compareToIgnoreCase("Simbody")==0)
                command += " -e Simbody ";
            // simmToOpenSim is assumed in the Path, similar to other dlls we depend on.
            File f = new File(jntfileName);
            File jntFileDir = f.getParentFile();
            String osimfilename = importPanel.getOsimFilename();
            if (osimfilename==null || osimfilename.length()==0){
               DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("No valid OpeSim file have been specified. Import aborted."));
               return;
            }
            String fullOsimFilename = jntFileDir.getAbsolutePath()+File.separator+osimfilename;
            File testExists = new File(fullOsimFilename);
            if (testExists.exists()){
               Object userAnswer = DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Confirmation("File "+fullOsimFilename+" already exists, do you want to overwrite?.",NotifyDescriptor.YES_NO_OPTION));
               if(userAnswer==NotifyDescriptor.NO_OPTION) return;
            }
           
            command+=" -x \""+importPanel.getOsimFilename()+"\"";
            if (importPanel.getUseSeparateMarkersFile() && 
                    importPanel.getMarkersFileName()!=null &&
                    !importPanel.getMarkersFileName().equalsIgnoreCase("")){
               //-ms markerset_out
               command+=" -ms \""+importPanel.getMarkersFileName()+"\"";
            }
            OpenSimLogger.logMessage("Executing ["+command+"]", 0);
            boolean success = ExecOpenSimProcess.execute(command, new String[]{""}, jntFileDir );
            // if file was not generated warn and point to message area
            testExists = new File(fullOsimFilename);
            if (!testExists.exists()){
               DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Message("Importing model failed, please check Message window for details."));
               success=false;
            }
            
            if (success){
                try {
                    // Display original model
                    ((FileOpenOsimModelAction) FileOpenOsimModelAction.findObject(
                            Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(fullOsimFilename);
                } catch (ClassNotFoundException ex) {
                    ex.printStackTrace();
                } catch (IOException ex) {
                    DialogDisplayer.getDefault().notify(
                            new NotifyDescriptor.Message("Error opening converted model file "+fullOsimFilename));
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
