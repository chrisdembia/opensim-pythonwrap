package org.opensim.view.base;

import java.awt.Color;
import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JColorChooser;
import javax.swing.JMenuItem;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public class ModifyWindowSettingsAction extends CallableSystemAction {
    
    OpenSimBaseCanvas dCanvas;
    
    public ModifyWindowSettingsAction(OpenSimBaseCanvas aCanvas)
    {
        super();
        dCanvas = aCanvas;
    }
    
    public void performAction() {
        // TODO implement action body
        JColorChooser backgroundColorChooser = new JColorChooser();
        Color newColor = backgroundColorChooser.showDialog(dCanvas, "Select new background color", dCanvas.getBackground());
        if (newColor != null){
             float[] colorComponents = newColor.getRGBComponents(null);
             dCanvas.GetRenderer().SetBackground(colorComponents[0], colorComponents[1], colorComponents[2]);
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
