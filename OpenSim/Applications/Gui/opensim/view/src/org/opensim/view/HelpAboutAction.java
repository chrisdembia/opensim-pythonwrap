package org.opensim.view;

import javax.swing.JButton;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class HelpAboutAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
      HelpAboutJPanel helpPanel = new HelpAboutJPanel();
      DialogDescriptor helpDlgDescriptor = new DialogDescriptor(helpPanel, "About", true, null);
      helpDlgDescriptor.setOptions(new Object[]{new JButton("Close")});     
      DialogDisplayer.getDefault().createDialog(helpDlgDescriptor).setVisible(true);
   }
   
   public String getName() {
      return NbBundle.getMessage(HelpAboutAction.class, "CTL_HelpAboutAction");
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
