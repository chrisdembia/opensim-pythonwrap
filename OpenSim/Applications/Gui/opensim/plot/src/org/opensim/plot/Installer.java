package org.opensim.plot;

import org.openide.modules.ModuleInstall;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
    public void restored() {
        // By default, do nothing.
        // Put your startup code here.
        int i=0;
    }
    
}
