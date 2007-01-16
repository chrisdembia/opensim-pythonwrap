package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.pub.ViewDB;

public final class SelectObjectAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
      ViewDB.getInstance().setPicking(true);
   }
   
   public String getName() {
      return NbBundle.getMessage(SelectObjectAction.class, "CTL_SelectObjectAction");
   }
   
   protected String iconResource() {
      return "org/opensim/view/pick.GIF";
   }
   
   public HelpCtx getHelpCtx() {
      return HelpCtx.DEFAULT_HELP;
   }
   
   protected boolean asynchronous() {
      return false;
   }
   
}
