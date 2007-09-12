package org.opensim.utils;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import org.openide.modules.ModuleInstall;
import org.openide.windows.WindowManager;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
    public void restored() {
        // By default, do nothing.
        // Put your startup code here.
        super.restored();
        SwingUtilities.invokeLater(new Runnable() {

         public void run() {
            TheApp.setAppFrame((JFrame)WindowManager.getDefault().getMainWindow());
         }
      });
    }
    
}
