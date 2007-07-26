package org.opensim.view.editors;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.OpenSimObject;
import org.opensim.utils.FileUtils;

public final class ObjectPropertiesEditor extends CallableSystemAction {
    
    public void performAction() {
      String fileName = FileUtils.getInstance().browseForFilename(".osim,.xml", "OpenSim model or XML file");
      if(fileName!=null) {
         OpenSimObject obj = OpenSimObject.makeObjectFromFile(fileName);
         if (obj != null){
            boolean confirm = new ObjectEditDialogMaker(obj, true).process();
            if (confirm) obj.print(fileName);
         } else {
            DialogDisplayer.getDefault().notify(
               new NotifyDescriptor.Message("Could not construct an object from the specified file."));
         }
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
