package org.opensim.plotter;

import java.awt.Dialog;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.view.pub.OpenSimDB;

public final class ToolsPlotAction extends CallableSystemAction {
   
   public void performAction() {
      //JFrame f = new JPlotterFrame("Plotter Frame");
      //f.setVisible(true);
      final JPlotterPanel plotterPanel = new JPlotterPanel();
      DialogDescriptor dlg = new DialogDescriptor(plotterPanel,"Plotter Dialog");
      dlg.setModal(false);
      dlg.setClosingOptions(null);
      dlg.setOptions(new Object[]{DialogDescriptor.CLOSED_OPTION});
      
      Dialog awtDialog =DialogDisplayer.getDefault().createDialog(dlg);
      awtDialog.addWindowListener(new WindowAdapter(){
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
      awtDialog.setVisible(true);
      
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
