package org.opensim.plotter;

import javax.swing.JFrame;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ToolsPlotAction extends CallableSystemAction {
   
   public void performAction() {
      //JFrame f = new JPlotterFrame("Plotter Frame");
      //f.setVisible(true);
      
      DialogDescriptor dlg = new DialogDescriptor(new JPlotterPanel(),"Plotter Dialog");
      DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
   }
   
   public String getName() {
      return NbBundle.getMessage(ToolsPlotAction.class, "CTL_ToolsPlotAction");
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
