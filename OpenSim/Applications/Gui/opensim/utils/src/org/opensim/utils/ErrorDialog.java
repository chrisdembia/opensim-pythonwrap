package org.opensim.utils;

import java.awt.Dialog;
import java.io.IOException;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;

public class ErrorDialog {

   public static void displayIOExceptionDialog(String title, String message, IOException ex) {
      ErrorPanel panel = new ErrorPanel();
      panel.setText(message, ex.getMessage());
      DialogDescriptor dlg = new DialogDescriptor(panel, title);
      dlg.setOptions(new Object[]{DialogDescriptor.OK_OPTION});
      Dialog dialog = DialogDisplayer.getDefault().createDialog(dlg);
      dialog.setVisible(true);
   }
}
