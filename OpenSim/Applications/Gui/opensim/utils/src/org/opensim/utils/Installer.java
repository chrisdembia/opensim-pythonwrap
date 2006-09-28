package org.opensim.utils;

import org.openide.modules.ModuleInstall;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
    public void restored() {
        // By default, do nothing.
        // Put your startup code here.
        System.out.println("Installing modeling utils");
        super.restored();
    }
    
}
