package org.opensim.view.actions;

import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.ModelSettingsSerializer;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class FileCloseAction extends CallableSystemAction {
 
   public static void closeModel(Model model) {
      if(model==null) return;
      // Confirm closing
      // TODO: check for unsaved changes to model before closing...
      // Write settings to persistent storage
      ModelSettingsSerializer ser = ViewDB.getInstance().getModelSavedSettings(model);
      if (ser.confirmAndWrite()==NotifyDescriptor.CANCEL_OPTION)
         return;

      OpenSimDB.getInstance().removeModel(model);
   }

   public void performAction() {
      closeModel(OpenSimDB.getInstance().getCurrentModel());      
   }
   
   public String getName() {
      return NbBundle.getMessage(FileCloseAction.class, "CTL_FileCloseAction");
   }
   
   protected void initialize() {
      super.initialize();
      // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
      putValue("noIconInMenu", Boolean.TRUE);
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
