package org.opensim.view.actions;

import java.io.File;
import java.io.IOException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractDynamicsEngine;
import org.opensim.modeling.Model;
import org.opensim.modeling.SimmKinematicsEngine;
import org.opensim.utils.FileUtils;
import org.opensim.view.FileOpenOsimModelAction;

public final class FileImportSimmKEModelAction extends CallableSystemAction {
   
   public void performAction() {
        // Browse for model file
        String inputFileName = FileUtils.getInstance().browseForFilename(FileUtils.OpenSimModelFileFilter);
        if (inputFileName != null){
            ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Loading model file "+inputFileName+"...");
            progressHandle.start();
             if (inputFileName.length()==0){
                DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("No valid OpenSim file has been specified. Import aborted."));
                return;
             }
             String outputFileName = "migrated.osim";
             File f = new File(inputFileName);
             File fileDir = f.getParentFile();
             String fullOutputFilename = fileDir.getAbsolutePath()+File.separator+outputFileName;
             File testExists = new File(fullOutputFilename);
             if (testExists.exists()){
                Object userAnswer = DialogDisplayer.getDefault().notify(
                     new NotifyDescriptor.Confirmation("File "+fullOutputFilename+" already exists, do you want to overwrite?.",NotifyDescriptor.YES_NO_OPTION));
                if(userAnswer==NotifyDescriptor.NO_OPTION) return;
             }

             Model simmKEModel = null;
             try {
                simmKEModel = new Model(inputFileName);
		simmKEModel.setup();

                AbstractDynamicsEngine oldEngine = simmKEModel.getDynamicsEngine();
                SimmKinematicsEngine simmKE = SimmKinematicsEngine.safeDownCast(oldEngine);
                if (simmKE != null) {
                   AbstractDynamicsEngine newEngine = org.opensim.modeling.opensimModel.makeSimbodyEngine(simmKEModel, simmKE);
                   simmKEModel.replaceEngine(newEngine);
                   Model copy = Model.safeDownCast(simmKEModel.copy());
                   copy.print(fullOutputFilename);
                } else {
                   DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Model in "+inputFileName+" does not use a SimmKinematicsEngine."));
                   progressHandle.finish();
                   StatusDisplayer.getDefault().setStatusText("");
                   return;
                }
             } catch (IOException ex) {
                DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Error opening model file "+inputFileName));
                progressHandle.finish();
                StatusDisplayer.getDefault().setStatusText("");
                return;
             }
             // if file was not generated warn and point to message area
             boolean success = true;
             testExists = new File(fullOutputFilename);
             if (!testExists.exists()){
                 DialogDisplayer.getDefault().notify(
                     new NotifyDescriptor.Message("Importing model failed, please check Message window for details."));
                 success=false;
             }

             if (success){
                 try {
                     // Display original model
                     ((FileOpenOsimModelAction) FileOpenOsimModelAction.findObject(
                         Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(fullOutputFilename);
                 } catch (ClassNotFoundException ex) {
                     ex.printStackTrace();
                 } catch (IOException ex) {
                     DialogDisplayer.getDefault().notify(
                         new NotifyDescriptor.Message("Error opening migrated model file "+fullOutputFilename));
                 };
             }
             progressHandle.finish();
             StatusDisplayer.getDefault().setStatusText("");
        }
   }
   
   public String getName() {
      return NbBundle.getMessage(FileImportSimmKEModelAction.class, "CTL_FileImportSimmKEModelAction");
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
