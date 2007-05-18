package org.opensim.coordinateviewer;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows CoordinateViewer component.
 */
public class CoordinateViewerAction extends AbstractAction {
   
   public CoordinateViewerAction() {
      super(NbBundle.getMessage(CoordinateViewerAction.class, "CTL_CoordinateViewerAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(CoordinateViewerTopComponent.ICON_PATH, true)));
   }
   
   public void actionPerformed(ActionEvent evt) {
      TopComponent win = CoordinateViewerTopComponent.findInstance();
      win.open();
      win.requestActive();
   }
   
}
