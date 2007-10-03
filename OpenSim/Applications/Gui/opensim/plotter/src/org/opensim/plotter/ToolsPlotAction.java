package org.opensim.plotter;

import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.WindowConstants;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.utils.DialogUtils;
import org.opensim.utils.TheApp;
import org.opensim.view.pub.OpenSimDB;

public final class ToolsPlotAction extends CallableSystemAction {
   
   public void performAction() {
      final JPlotterPanel plotterPanel = new JPlotterPanel();
      
      JFrame f= DialogUtils.createFrameForPanel(plotterPanel, "Plotter");
      plotterPanel.setFrame(f);
      f.setVisible(true);

      f.addWindowListener(new WindowAdapter(){
         public void windowOpened(WindowEvent e) {
            MotionsDB.getInstance().addObserver(plotterPanel);
            OpenSimDB.getInstance().addObserver(plotterPanel);   // Make sure current model does not change under us
         }

         public void windowClosing(WindowEvent e) {
            MotionsDB.getInstance().deleteObserver(plotterPanel);
            OpenSimDB.getInstance().deleteObserver(plotterPanel); 
         }

         public void windowClosed(WindowEvent e) {
            MotionsDB.getInstance().deleteObserver(plotterPanel);
            OpenSimDB.getInstance().deleteObserver(plotterPanel); 
         }

    });
      
   }

   
   public String getName() {
      return NbBundle.getMessage(ToolsPlotAction.class, "CTL_ToolsPlotAction");
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
