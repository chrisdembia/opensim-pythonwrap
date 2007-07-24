package org.opensim.tracking.tools;

import java.io.IOException;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.tracking.BaseToolPanel;
import org.opensim.tracking.ScaleToolPanel;
import org.opensim.utils.ErrorDialog;
import org.opensim.view.pub.OpenSimDB;

public final class ScaleToolAction extends CallableSystemAction {
        
   public void performAction() {
      Model model = OpenSimDB.getInstance().getCurrentModel();
      if(model==null) return;

      try {
         final ScaleToolPanel panel = new ScaleToolPanel(model);
         BaseToolPanel.openToolDialog(panel, "Scale Tool");
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Unexpected error","Unexpected error while initializing scale tool",ex);
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(ScaleToolAction.class, "CTL_ScaleToolAction");
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
