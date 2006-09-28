package org.opensim.plot;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import ptolemy.plot.demo.PlotLiveDemo;

public final class PlotAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        Runnable doActions = new Runnable() {
                public void run() {
                    try {
                        OpenSimLivePlotDialog plotDialog = 
                                new OpenSimLivePlotDialog();

                        plotDialog.pack();
                        plotDialog.setVisible(true);
                    } catch (Exception ex) {
                        System.err.println(ex.toString());
                        ex.printStackTrace();
                    }
                }
            };

        try {
            SwingUtilities.invokeLater(doActions);
        } catch (Exception ex) {
            System.err.println(ex.toString());
            ex.printStackTrace();
        }

    }
    
    public String getName() {
        return NbBundle.getMessage(PlotAction.class, "CTL_PlotAction");
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
