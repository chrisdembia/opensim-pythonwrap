package org.opensim.motionviewer;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.openide.windows.TopComponent;

public final class ViewMotionsAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
      TopComponent tc = MotionViewerTopComponent.findInstance();
      tc.open();
      tc.requestActive();
      
   }
   
   public String getName() {
      return NbBundle.getMessage(ViewMotionsAction.class, "CTL_ViewMotionsAction");
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
