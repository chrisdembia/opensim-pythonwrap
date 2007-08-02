package org.opensim.view;

import java.awt.Frame;
import java.util.prefs.Preferences;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.openide.modules.ModuleInstall;
import org.openide.util.NbBundle;
import org.opensim.utils.TheApp;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;
import org.opensim.view.editors.MuscleEditorTopComponent;
import javax.swing.JPopupMenu;
import org.openide.windows.WindowManager;
import org.opensim.modeling.opensimModelJNI;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
   // Enable opoups to display on top of heavy weight component/canvas
   static {
      JPopupMenu.setDefaultLightWeightPopupEnabled(false);
      javax.swing.ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);
   }
    public void restored() {
        super.restored();
        try {
             // Put your startup code here.
            UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
            UIManager.put("SliderUI", "org.opensim.view.OpenSimSliderUI");
            
            SwingUtilities.invokeLater(new Runnable(){
            public void run() {
               Frame f = WindowManager.getDefault ().getMainWindow ();
               f.setSize (800, 400);
               f.setResizable (true);
               MuscleEditorTopComponent.findInstance();
            }});
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
        System.setProperty ("netbeans.buildnumber", opensimModelJNI.GetVersion());
        // Force creation of Model-database OpenSimDB 
        // and a View-database ViewDB
        // and register View as Observer of Model
        OpenSimDB.getInstance().addObserver(ViewDB.getInstance());
        ViewDB.updateCommandsVisibility();
        /**
         * @todo open explorer window, Restore default directory and Bones directories, ..
         */
        restorePrefs();

    }
    
    private void restorePrefs()
    {
         String AAFRamesDefaultStr = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_AAFrames");        
         String saved=Preferences.userNodeForPackage(TheApp.class).get("AntiAliasingFrames", AAFRamesDefaultStr);
         Preferences.userNodeForPackage(TheApp.class).put("AntiAliasingFrames", saved);
         
         String defaultOffsetDirection = NbBundle.getMessage(ViewDB.class,"CTL_DisplayOffsetDir");
         saved=Preferences.userNodeForPackage(TheApp.class).get("DisplayOffsetDir", defaultOffsetDirection);
         Preferences.userNodeForPackage(TheApp.class).put("DisplayOffsetDir", saved);
         
         String nonCurrentModelOpacityStr = NbBundle.getMessage(ViewDB.class,"CTL_NonCurrentModelOpacity");
         saved = Preferences.userNodeForPackage(TheApp.class).get("NonCurrentModelOpacity", nonCurrentModelOpacityStr);
         Preferences.userNodeForPackage(TheApp.class).put("NonCurrentModelOpacity", saved);

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
