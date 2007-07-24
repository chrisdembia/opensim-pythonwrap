package org.opensim.tracking.tools;

import java.io.IOException;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.tracking.BaseToolPanel;
import org.opensim.tracking.ForwardToolPanel;
import org.opensim.utils.ErrorDialog;
import org.opensim.view.pub.OpenSimDB;

public final class ForwardToolAction extends CallableSystemAction {
   
   public void performAction() {
      try {
         final ForwardToolPanel panel = new ForwardToolPanel();
         BaseToolPanel.openToolDialog(panel, "Forward Tool");
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Unexpected error","Unexpected error while initializing forward tool",ex);
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(ForwardToolAction.class, "CTL_ForwardToolAction");
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
      return true;
      //return OpenSimDB.getInstance().getCurrentModel()!=null;
   }
}
