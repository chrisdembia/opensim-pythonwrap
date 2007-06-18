package org.opensim.logger;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows Logger component.
 */
public class LoggerAction extends AbstractAction {
   
   public LoggerAction() {
      super(NbBundle.getMessage(LoggerAction.class, "CTL_LoggerAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(LoggerTopComponent.ICON_PATH, true)));
   }
   
   public void actionPerformed(ActionEvent evt) {
      TopComponent win = LoggerTopComponent.findInstance();
      win.open();
      win.requestActive();
   }
   
}
