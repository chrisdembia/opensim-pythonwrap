package org.opensim.view.actions;

import java.util.prefs.BackingStoreException;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class EditPreferencesAction extends CallableSystemAction {
   
   public void performAction() {
      EditPreferencesJPanel prefsPanel;
      try {
         prefsPanel = new EditPreferencesJPanel();
         DialogDescriptor prefsDialog = new DialogDescriptor(prefsPanel, "Preferences");
         setEnabled(false);
         DialogDisplayer.getDefault().createDialog(prefsDialog).setVisible(true);
         setEnabled(true);
        Object userInput = prefsDialog.getValue();
        if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0)
           prefsPanel.apply();        
        return ;
      } catch (BackingStoreException ex) {
         ex.printStackTrace();
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(EditPreferencesAction.class, "CTL_EditPreferencesAction");
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
