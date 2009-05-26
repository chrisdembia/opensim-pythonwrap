/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.opensim.view;

import java.beans.XMLDecoder;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.prefs.Preferences;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.openide.modules.ModuleInstall;
import org.openide.util.NbBundle;
import org.opensim.utils.TheApp;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.OpenSimDBDescriptor;
import org.opensim.view.pub.PluginsDB;
import org.opensim.view.pub.ViewDB;
import org.opensim.view.editors.MuscleEditorTopComponent;
import org.opensim.view.markerEditor.MarkerEditorTopComponent;
import javax.swing.JPopupMenu;
import org.opensim.modeling.opensimModelJNI;
import org.opensim.utils.ApplicationState;
import org.opensim.view.actions.ApplicationExit;
import org.opensim.view.pub.ViewDBDescriptor;

/**
 * Manages a module's lifecycle. Remember that an installer is optional and
 * often not needed at all.
 */
public class Installer extends ModuleInstall {
    
   // Enable popups to display on top of heavy weight component/canvas
   static {
      JPopupMenu.setDefaultLightWeightPopupEnabled(false);
      javax.swing.ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);
      javax.swing.ToolTipManager.sharedInstance().setDismissDelay(600000); // keep tooltips up for a minute!
   }

   // This function is called when File...Exit is chosen.
   public boolean closing() {
      return ApplicationExit.confirmExit();
   }

    public void restored() {
        super.restored();
        System.setProperty ("netbeans.buildnumber", "1.9"); // Should get that from JNI but sometimes doesn't work'
        try {
             // Put your startup code here.
            UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
            UIManager.put("SliderUI", "org.opensim.view.OpenSimSliderUI");
            SwingUtilities.invokeLater(new Runnable(){
            public void run() {
               // This line is important because it forces the muscle editor to initialize at the start
               // which is necessary to allow moving muscle points even if the muscle editor top component is not shown
               // Note that this may cause a warning exception "Cannot find MuscleEditor component" to be shown... just ignore it.
               // Same goes for the MarkerEditor.
               MuscleEditorTopComponent.findInstance();
               MarkerEditorTopComponent.findInstance();
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
        // Force creation of Model-database OpenSimDB 
        // and a View-database ViewDB
        // and register View as Observer of Model
        OpenSimDB.getInstance().addObserver(ViewDB.getInstance());
        /**
         * @todo open explorer window, Restore default directory and Bones directories, ..
         */
        restorePrefs();
        /** Restore from file */

        try {
            XMLDecoder decoder = new XMLDecoder(new BufferedInputStream(
                new FileInputStream("AppState.xml")));
            ApplicationState readState= (ApplicationState)decoder.readObject();
            PluginsDB.getInstance().loadPlugins();
            OpenSimDB.getInstance().rebuild((OpenSimDBDescriptor) readState.getObject("OpenSimDB"));
            ViewDB.getInstance().rebuild((ViewDBDescriptor) readState.getObject("ViewDB"));
            decoder.close();
        } catch (FileNotFoundException ex) {
            // First time, no file yet
           ApplicationState as = ApplicationState.getInstance();
           as.addObject("OpenSimDB", new OpenSimDBDescriptor(OpenSimDB.getInstance()));
           //as.addObject("OpenSimDB", OpenSimDB.getInstance());
           as.addObject("ViewDB", new ViewDBDescriptor(ViewDB.getInstance()));
            //ex.printStackTrace();
           as.addObject("PluginsDB", PluginsDB.getInstance());
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    /**
     * restorePrefs is primarily used for the first time around where there are no pref values
     * stored in the backing file/registry. It sets values in the backing store based on the resource/Bundle files
     * built nito the application */
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
         saved=Preferences.userNodeForPackage(TheApp.class).get("Geometry Path", defaultGeometryPath);
         Preferences.userNodeForPackage(TheApp.class).put("Geometry Path", saved);

         String defaultBgColor = NbBundle.getMessage(OpenSimBaseCanvas.class, "CTL_BackgroundColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("BackgroundColor", defaultBgColor);
         Preferences.userNodeForPackage(TheApp.class).put("BackgroundColor", saved);

         String muscleRadius = NbBundle.getMessage(ViewDB.class, "CTL_MuscleRadius");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("Muscle Display Radius", muscleRadius);
         Preferences.userNodeForPackage(TheApp.class).put("Muscle Display Radius", saved);

         String markerRadius = NbBundle.getMessage(ViewDB.class, "CTL_MarkerRadius");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("Marker Display Radius", markerRadius);
         Preferences.userNodeForPackage(TheApp.class).put("Marker Display Radius", saved);

         String markerColor = NbBundle.getMessage(ViewDB.class, "CTL_MarkersColorRGB");        
         saved = Preferences.userNodeForPackage(TheApp.class).get("Markers Color", markerColor);
         Preferences.userNodeForPackage(TheApp.class).put("Markers Color", saved);
    }
}
