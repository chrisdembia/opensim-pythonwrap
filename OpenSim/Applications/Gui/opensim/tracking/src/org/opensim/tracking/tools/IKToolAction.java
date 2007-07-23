package org.opensim.tracking.tools;

import java.awt.Dialog;
import java.io.IOException;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.tracking.IKToolPanel;
import org.opensim.utils.ErrorDialog;
import org.opensim.view.pub.OpenSimDB;

public final class IKToolAction extends CallableSystemAction {
   
   public void performAction() {
      Model model = OpenSimDB.getInstance().getCurrentModel();
      if(model==null) return;

      try {
         final IKToolPanel panel = new IKToolPanel(model);
         DialogDescriptor dlg = new DialogDescriptor(panel, "Inverse Kinematics Tool", false, panel);
         dlg.setOptions(panel.getDialogOptions());
         Dialog awtDialog = DialogDisplayer.getDefault().createDialog(dlg);
         panel.setOwner(awtDialog);
         awtDialog.setVisible(true);      
         awtDialog.requestFocus();
      } catch (IOException ex) {
         // IKToolPanel may have failed to initialize... 
         ErrorDialog.displayIOExceptionDialog("Unexpected error","Unexpected error while initializing inverse kinematics tool",ex);
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(IKToolAction.class, "CTL_IKToolAction");
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
