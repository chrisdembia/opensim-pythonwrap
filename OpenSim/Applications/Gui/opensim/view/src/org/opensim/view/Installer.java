package org.opensim.view;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.openide.modules.ModuleInstall;
import org.openide.util.NbBundle;
import vtk.vtkFileOutputWindow;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
    public void restored() {
        try {
             // Put your startup code here.
            UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (UnsupportedLookAndFeelException ex) {
            ex.printStackTrace();
        }
        // Disable the number in the application title that shows after OpenSim
        System.setProperty ("netbeans.buildnumber", 
                NbBundle.getMessage(Installer.class, "CTL_OpenSimVersion")); 
        ViewDB.updateCommandsVisibility();
        // Disable vtk output window
        // This code should be moved to the module installer to be done once per session
        /**
         * @todo open explorer window, Restore default directory and Bones directories, ..
         */
        super.restored();

    }
    
}
