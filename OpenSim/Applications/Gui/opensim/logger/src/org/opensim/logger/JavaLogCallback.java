package org.opensim.logger;

import org.opensim.modeling.*;
import javax.swing.SwingUtilities;

public class JavaLogCallback extends SimtkLogCallback {
   public void log(final String str) {
      SwingUtilities.invokeLater(new Runnable(){
         public void run() {
            LoggerTopComponent.findInstance().log(str);
         }});
   }

   protected void finalize()
   {
      removeFromLogManager();
      super.finalize();
   }
}
