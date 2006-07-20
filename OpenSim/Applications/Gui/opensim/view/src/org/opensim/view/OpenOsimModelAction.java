package org.opensim.view;

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.util.Collection;
import javax.swing.JFileChooser;
import javax.swing.SwingUtilities;
import org.openide.util.HelpCtx;
import org.openide.util.Lookup;
import org.openide.util.LookupEvent;
import org.openide.util.LookupListener;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.common.OpenSimDB;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmModel;
import org.opensim.view.base.SerializationHelper;

public final class OpenOsimModelAction extends CallableSystemAction {
    
    protected String fileName;
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
         Lookup.Template tpl = new Lookup.Template (OpenSimObject.class);
        Lookup.Result res = Utilities.actionsGlobalContext().lookup (tpl);
        res.addLookupListener (new LookupListener() {
           public void resultChanged (LookupEvent evt) {
             Collection c = ((Lookup.Result) evt.getSource()).allInstances();
             //do something with the collection of 0 or more instances - the collection has changed
             System.out.println("Collection size="+c.size());
           }
        });
        
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

    public void loadModel(final String fileName) {
           // Make the model
        SimmModel aModel = new SimmModel(fileName);
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
}
