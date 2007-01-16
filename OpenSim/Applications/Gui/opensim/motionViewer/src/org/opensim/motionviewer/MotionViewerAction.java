package org.opensim.motionviewer;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows MotionViewer component.
 */
public class MotionViewerAction extends AbstractAction {
   
   public MotionViewerAction() {
      super(NbBundle.getMessage(MotionViewerAction.class, "CTL_MotionViewerAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(MotionViewerTopComponent.ICON_PATH, true)));
   }
   
   public void actionPerformed(ActionEvent evt) {
      TopComponent win = MotionViewerTopComponent.findInstance();
      win.open();
      win.requestActive();
   }
   
}
