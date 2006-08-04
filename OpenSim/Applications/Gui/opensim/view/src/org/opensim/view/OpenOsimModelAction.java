package org.opensim.view;

import java.awt.Component;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.SwingUtilities;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.Presenter;
import org.opensim.common.OpenSimDB;
import org.opensim.modeling.SimmModel;
import org.opensim.view.base.SerializationHelper;

public final class OpenOsimModelAction extends CallableSystemAction implements Presenter.Toolbar {
    
    protected String fileName;
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
         
       final JFileChooser dlog = new JFileChooser();
        
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            fileName = dlog.getSelectedFile().getAbsolutePath();
            loadModel(fileName);
            BottomPanelTopComponent.showLogMessage("Model has been created from file "+dlog.getSelectedFile().getAbsolutePath()+"\n");
            try {
                writeExternal(SerializationHelper.getLogStream());
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }

    }

    /**
     * This is the function that does the real work of loading a model file into the GUI
     * @param fileName is the absolute path to the file to be used.
     * @returns true on success else failure
     */
    public boolean loadModel(final String fileName) {
        boolean retValue = false;   
        // Make the model
        SimmModel aModel = new SimmModel(fileName);
        if (aModel == null)
            return retValue;
        
        aModel.setup();
        // Make the window
        final ModelWindowVTKTopComponent modelWindow = new ModelWindowVTKTopComponent(aModel);
        SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                modelWindow.open();
           }});
        
        OpenSimDB.getInstance().addObserver(modelWindow);
        OpenSimDB.getInstance().addModel(aModel);
        
        retValue = true;
        return retValue;
    }
    
   public void loadModel(SimmModel aModel) {
        aModel.setup();
        // Make the window
        final ModelWindowVTKTopComponent modelWindow = new ModelWindowVTKTopComponent(aModel);
        SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                modelWindow.open();
           }});
        
        OpenSimDB.getInstance().addObserver(modelWindow);
        OpenSimDB.getInstance().addModel(aModel);
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

    public Component getToolbarPresenter() {
        Component retValue;
        
        retValue = new JButton(this);
        return retValue;
    }
    
}
