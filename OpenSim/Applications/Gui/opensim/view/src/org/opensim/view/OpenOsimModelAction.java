package org.opensim.view;

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.net.URL;
import javax.swing.SwingUtilities;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmModel;
import org.opensim.utils.FileUtils;
import org.opensim.view.base.SerializationHelper;

public final class OpenOsimModelAction extends CallableSystemAction {
    
    protected String fileName;
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
/*       String defaultDir="";
       defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
       final JFileChooser dlog = new JFileChooser(defaultDir);
        
        dlog.setFileFilter(FileUtils.getFileFilter());
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            fileName = dlog.getSelectedFile().getAbsolutePath();
            Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
        }
*/
        String fileName = FileUtils.browseForFilename(".xml,.osim", "Model file to open");
        if (fileName != null){
            try {
                loadModel(fileName);
            } catch (IOException ex) {
                ex.printStackTrace();
                
            }
            
            try {
                writeExternal(SerializationHelper.getLogStream());
            } catch (IOException ex) {
                ex.printStackTrace();
            }            
        }
    }

     /**
     * A wrapper around loadModel that handles a SimmModel rather than a filename
     */
    public boolean loadModel(final SimmModel aModel) throws IOException {
        boolean retValue = false;
        aModel.setup();
        boolean isOk = aModel.builtOK();
        if (!isOk){
             BottomPanelTopComponent.findInstance().showErrorMessage("Failed to construct model from file "+fileName+"\n");
            return retValue;            
        }
        // Make the window
        final ModelWindowVTKTopComponent modelWindow = new ModelWindowVTKTopComponent(aModel);
        SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                modelWindow.open();
                OpenSimDB.getInstance().addObserver(modelWindow);
                OpenSimDB.getInstance().addModel(aModel);
                ViewDB.getInstance().addModelWindowMap(aModel, modelWindow);
                // Log message to Log window. 
                BottomPanelTopComponent.findInstance().showLogMessage("Model has been created from file "+fileName+"\n");
                modelWindow.requestActive();
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
        final SimmModel aModel = new SimmModel(fileName);
        if (aModel == null){
             BottomPanelTopComponent.findInstance().showErrorMessage("Failed to construct model from file "+fileName+"\n");
            return retValue;
        }
        return loadModel(aModel);
    }
    
    public String getName() {
        return NbBundle.getMessage(OpenOsimModelAction.class, "CTL_OpenOsimModel");
    }
    
    protected String iconResource() {
        return null;
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(OpenOsimModelAction.class);
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
       SerializationHelper.getCommandEncoder().writeObject(this);
       SerializationHelper.getCommandEncoder().flush();
    }

    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        
    }

}
