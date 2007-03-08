package org.opensim.view;

import java.util.prefs.Preferences;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.openide.modules.ModuleInstall;
import org.openide.util.NbBundle;
import org.opensim.utils.TheApp;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

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
        // Force creation of Model-database OpenSimDB 
        // and a View-database ViewDB
        // and register View as Observer of Model
        OpenSimDB.getInstance().addObserver(ViewDB.getInstance());
        ViewDB.updateCommandsVisibility();
        /**
         * @todo open explorer window, Restore default directory and Bones directories, ..
         */
        restorePrefs();
        super.restored();

    }
    
    private void restorePrefs()
    {
         String AAFRamesDefaultStr = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_AAFrames");        
         String saved=Preferences.userNodeForPackage(TheApp.class).get("AntiAliasingFrames", AAFRamesDefaultStr);
         Preferences.userNodeForPackage(TheApp.class).put("AntiAliasingFrames", saved);
         
         String defaultOffsetDirection = NbBundle.getMessage(ViewDB.class,"CTL_DisplayOffsetDir");
         saved=Preferences.userNodeForPackage(TheApp.class).get("DisplayOffsetDir", defaultOffsetDirection);
         Preferences.userNodeForPackage(TheApp.class).put("DisplayOffsetDir", saved);
         
         String defaultGeometryPath = NbBundle.getMessage(OpenSimBaseCanvas.class,"CTL_GeometryPath");
         saved=Preferences.userNodeForPackage(TheApp.class).get("GeometryPath", defaultGeometryPath);
         Preferences.userNodeForPackage(TheApp.class).put("GeometryPath", saved);

         String defaultBgColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_BackgroundColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("BackgroundColor", defaultBgColor);
         Preferences.userNodeForPackage(TheApp.class).put("BackgroundColor", saved);
         
         String defaultMuscleColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_MuscleColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("MuscleColor", defaultMuscleColor);
         Preferences.userNodeForPackage(TheApp.class).put("MuscleColor", saved);

         String defaultMarkerColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_MarkerColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("MarkerColor", defaultMarkerColor);
         Preferences.userNodeForPackage(TheApp.class).put("MarkerColor", saved);

         String defaultMusclePointColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_MusclePointColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("MusclePointColor", defaultMusclePointColor);
         Preferences.userNodeForPackage(TheApp.class).put("MusclePointColor", saved);

         String defaultWrapObjectColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_WrapObjectColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("WrapObjectColor", defaultWrapObjectColor);
         Preferences.userNodeForPackage(TheApp.class).put("WrapObjectColor", saved);

         String showWrapObjects = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_ShowWrapObjects");
         saved = Preferences.userNodeForPackage(TheApp.class).get("ShowWrapObjects", showWrapObjects);
         Preferences.userNodeForPackage(TheApp.class).put("ShowWrapObjects", saved);
    }
}
