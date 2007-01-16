package org.opensim.motionviewer;

import java.awt.Component;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ShowMotionSliderAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
   }
   
   public String getName() {
      return NbBundle.getMessage(ShowMotionSliderAction.class, "CTL_ShowMotionSliderAction");
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

   public Component getToolbarPresenter() {
      return new MotionSliderJPanel();
   }
   
}
