package org.opensim.view.actions;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.FileSaveAsModelAction;
import org.opensim.view.ModelSettingsSerializer;
import org.opensim.view.SingleModelGuiElements;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class FileCloseAction extends CallableSystemAction {
 
   public static void closeModel(Model model) {
      if(model==null) return;

      // Confirm closing
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);
      if (guiElem.getUnsavedChangesFlag()) {
         if (saveAndConfirmClose(model) == false)
            return;
      }

      // TODO: check for unsaved changes to model before closing...
      // Write settings to persistent storage
      ModelSettingsSerializer ser = ViewDB.getInstance().getModelSavedSettings(model);
      if (ser.confirmAndWrite()==NotifyDescriptor.CANCEL_OPTION)
         return;

      OpenSimDB.getInstance().removeModel(model);
   }

   private static boolean saveAndConfirmClose(Model model)
   {
      NotifyDescriptor dlg = new NotifyDescriptor.Confirmation("Do you want to save the changes to " + model.getName() + "?", "OpenSim");
      Object userSelection = DialogDisplayer.getDefault().notify(dlg);
      if (((Integer)userSelection).intValue() == ((Integer)NotifyDescriptor.OK_OPTION).intValue()) {
          if (!model.getInputFileName().equals(""))
             FileSaveAsModelAction.saveModel(model, model.getInputFileName());
          else
             (new FileSaveAsModelAction()).performAction();
          return true;
      } else if (((Integer)userSelection).intValue() == ((Integer)NotifyDescriptor.NO_OPTION).intValue()) {
         return true;
      } else {
         return false;
      }
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
