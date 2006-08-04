package org.opensim.view.base;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public class ToggleAxesAction extends CallableSystemAction {
    
    private OpenSimBaseCanvas dCanvas;
    public ToggleAxesAction(OpenSimBaseCanvas aCanvas)
    {
        dCanvas = aCanvas;
    }
    
    public void performAction() {
        // TODO implement action body
        if (dCanvas.getAxesDisplayed()){
            dCanvas.displayAxes(false);
            dCanvas.Render();
        }
        else{
            dCanvas.displayAxes(true);
            dCanvas.Render();
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(ToggleAxesAction.class, "CTL_ToggleAxesAction");
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
