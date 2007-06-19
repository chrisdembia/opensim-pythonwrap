package org.opensim.logger;

import org.openide.modules.ModuleInstall;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {

   static JavaLogCallback logCallback=null;   
   
   public void restored() {
      super.restored();
      if(logCallback == null) {
         System.out.println("Initializing logger callback");
         logCallback = new JavaLogCallback();
         logCallback.addToLogManager();
      }
   }
   
   public void close() {
      if(logCallback != null) {
         logCallback.removeFromLogManager();
         logCallback=null;
      }
      super.close();
      
   }
}
