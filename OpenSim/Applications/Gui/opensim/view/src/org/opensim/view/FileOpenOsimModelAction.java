package org.opensim.view;

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.logger.OpenSimLogger;
import org.opensim.modeling.Model;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;

public class FileOpenOsimModelAction extends CallableSystemAction {
    
    protected String fileName;
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
        String fileName = FileUtils.getInstance().browseForFilename(FileUtils.OpenSimModelFileFilter);
        if (fileName != null){
            ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Loading model file "+fileName+"...");
            try {
                progressHandle.start();
                loadModel(fileName);
                progressHandle.finish();
                StatusDisplayer.getDefault().setStatusText("");
            } catch (IOException ex) {
                progressHandle.finish();
                ErrorDialog.displayIOExceptionDialog("OpenSim Model Loading Error",
                  "Could not construct a model from "+fileName+".\nConsider using File/import instead.\n",
                  ex);
            }    
        }
    }

     /**
     * A wrapper around loadModel that handles a Model rather than a filename
     * setup was invoked already on the model
     */
    public boolean loadModel(final Model aModel) throws IOException {
        boolean retValue = false;
        boolean isOk = aModel.builtOK();
        if (!isOk){
            OpenSimLogger.logMessage("Failed to construct model from file "+fileName+"\n", OpenSimLogger.ERROR);
            return retValue;            
        }
        if (OpenSimDB.getInstance().hasModel(aModel)){   // If model is already loaded, complain and return.
            OpenSimLogger.logMessage("Model is already loaded\n", OpenSimLogger.ERROR);
            return retValue;            
           
        }
        // Make the window
        SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                OpenSimDB.getInstance().addModel(aModel);
            }});
        retValue = true;
        return retValue;        
    }
    /**
     * This is the function that does the real work of loading a model file into the GUI
     * @param fileName is the absolute path to the file to be used.
     * @returns true on success else failure
     */
      public boolean loadModel(final String fileName) throws IOException {
         return loadModel(fileName, false);
         
     }
     public boolean loadModel(final String fileName, boolean loadInForground) throws IOException {
        boolean retValue = false;
        Model aModel=null;
        aModel= new Model(fileName);
        if (aModel == null){
             OpenSimLogger.logMessage("Failed to construct model from file "+fileName+"\n", OpenSimLogger.ERROR);
            return retValue;
        }
        aModel.setup();
        return loadModel(aModel);
    }
    
    public String getName() {
        return NbBundle.getMessage(FileOpenOsimModelAction.class, "CTL_OpenOsimModel");
    }
    
    protected String iconResource() {
        return null;
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(FileOpenOsimModelAction.class);
    }
    
    protected boolean asynchronous() {
        return true;
    }
    /**
     * Bean pattern to support serialization
     */
    public String getFileName()
    {
        return fileName;
    }
    
    public void setFileName(String filename)
    {
        fileName=filename;
    }
    
    public void writeExternal(ObjectOutput out) throws IOException {
       //SerializationHelper.getCommandEncoder().writeObject(this);
       //SerializationHelper.getCommandEncoder().flush();
    }

    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        
    }

}
