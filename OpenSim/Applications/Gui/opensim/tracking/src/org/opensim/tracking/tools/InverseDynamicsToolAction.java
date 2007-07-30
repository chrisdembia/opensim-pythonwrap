package org.opensim.tracking.tools;

import java.io.IOException;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.tracking.AnalyzeToolPanel;
import org.opensim.tracking.BaseToolPanel;
import org.opensim.utils.ErrorDialog;
import org.opensim.view.pub.OpenSimDB;

public final class InverseDynamicsToolAction extends CallableSystemAction {
   
   public void performAction() {
      Model model = OpenSimDB.getInstance().getCurrentModel();
      if(model==null) return;

      try {
         final AnalyzeToolPanel panel = new AnalyzeToolPanel(model, true);
         BaseToolPanel.openToolDialog(panel, "Inverse Dynamics Tool");
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Unexpected error","Unexpected error while initializing inverse dynamics tool",ex);
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(InverseDynamicsToolAction.class, "CTL_InverseDynamicsToolAction");
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
