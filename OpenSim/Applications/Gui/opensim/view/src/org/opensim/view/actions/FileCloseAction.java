package org.opensim.view.actions;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.FileSaveModelAction;
import org.opensim.view.ModelSettingsSerializer;
import org.opensim.view.SingleModelGuiElements;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class FileCloseAction extends CallableSystemAction {
   static boolean noGFX=false;

/* Close the model. If it's locked, tell the user and abort. If it's
 * modified, ask the user to save the changes, with the option to cancel
 * the close. If the model is not closed, return false.
 */
public static boolean closeModel(Model model) {
   if(model==null) return true;


   SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);
   
   // Do not allow the model to be closed if it is locked.
   if (guiElem.isLocked()) {
      NotifyDescriptor dlg = new NotifyDescriptor.Message(model.getName() + " is currently in use by " +
              guiElem.getLockOwner() + " and cannot be closed.", NotifyDescriptor.INFORMATION_MESSAGE);
      DialogDisplayer.getDefault().notify(dlg);
      return false;
   }
   
   // Confirm closing
   if (guiElem.getUnsavedChangesFlag()) {
      if (saveAndConfirmClose(model) == false)
         return false;
   }
   
   // Write settings to persistent storage
   ModelSettingsSerializer ser = ViewDB.getInstance().getModelSavedSettings(model);
   if (ser.confirmAndWrite(model)==NotifyDescriptor.CANCEL_OPTION)
      return false;

   OpenSimDB.getInstance().removeModel(model);
   
   return true;
}

   private static boolean saveAndConfirmClose(Model model)
   {
      NotifyDescriptor dlg = new NotifyDescriptor.Confirmation("Do you want to save the changes to " + model.getName() + "?", "Save model?");
      Object userSelection = DialogDisplayer.getDefault().notify(dlg);
      if (((Integer)userSelection).intValue() == ((Integer)NotifyDescriptor.OK_OPTION).intValue()) {
         return FileSaveModelAction.saveOrSaveAsModel(model);
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
