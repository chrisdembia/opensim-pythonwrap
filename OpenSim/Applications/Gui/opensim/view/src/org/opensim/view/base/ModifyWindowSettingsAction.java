package org.opensim.view.base;

import java.awt.Color;
import java.util.prefs.Preferences;
import javax.swing.JColorChooser;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.TheApp;
import org.opensim.view.OpenSimCanvas;
import org.opensim.view.pub.ViewDB;

public final class ModifyWindowSettingsAction extends CallableSystemAction {
        
    public void performAction() {
        // TODO implement action body
        JColorChooser backgroundColorChooser = new JColorChooser();
        OpenSimCanvas dCanvas = ViewDB.getInstance().getCurrenWindow().getCanvas();
        Color newColor = backgroundColorChooser.showDialog(dCanvas, "Select new background color", dCanvas.getBackground());
        if (newColor != null){
             float[] colorComponents = newColor.getRGBComponents(null);
             dCanvas.GetRenderer().SetBackground(colorComponents[0], colorComponents[1], colorComponents[2]);
             String defaultBackgroundColor=String.valueOf(colorComponents[0])+", "+
                     String.valueOf(colorComponents[1])+", "+
                     String.valueOf(colorComponents[2]);
            Preferences.userNodeForPackage(TheApp.class).put("BackgroundPref", defaultBackgroundColor);

             dCanvas.repaint();
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(ModifyWindowSettingsAction.class, "CTL_ModifyWindowSettingsAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
}
