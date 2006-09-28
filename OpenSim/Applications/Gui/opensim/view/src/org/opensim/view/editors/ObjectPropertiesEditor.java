package org.opensim.view.editors;

import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.OpenSimObject;
import org.opensim.utils.TheApp;

public final class ObjectPropertiesEditor extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        // Browse for file, create object and open it for editing
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        
            if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
                String fileName = dlog.getSelectedFile().getAbsolutePath();
                Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
                OpenSimObject obj = OpenSimObject.makeObjectFromFile(fileName);
               if (obj != null){
                    boolean confirm = new ObjectEditDialogMaker(obj, true).process();
                    if (confirm)
                        obj.print(fileName);
                }
                else
                    DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Message("Could not construct an object from the specified file.\n"));
            }

    }
    
    public String getName() {
        return NbBundle.getMessage(ObjectPropertiesEditor.class, "CTL_ObjectPropertiesEditor");
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
