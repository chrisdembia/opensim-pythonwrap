/*
 * ScaleToolPanel.java
 *
 * Created on July 3, 2007, 4:51 PM
 */

package org.opensim.tracking;

import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.utils.FileUtils;

public abstract class BaseToolPanel extends JPanel implements ActionListener {
  
   private FileFilter settingsFilter = null;

   protected JButton settingsButton = new JButton("Settings >");
   protected JButton applyButton = new JButton("Run");
   protected JButton okButton = new JButton("Close");
   protected Dialog ownerDialog = null;

   //------------------------------------------------------------------------
   // Load/Save Settings Actions
   //------------------------------------------------------------------------
   class LoadSettingsAction extends AbstractAction {
      public LoadSettingsAction() { super("Load Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilename(settingsFilter);
         if(fileName!=null) loadSettings(fileName);
      }
   }
   class SaveSettingsAction extends AbstractAction {
      public SaveSettingsAction() { super("Save Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilenameToSave(settingsFilter, true, null);
         if(fileName!=null) saveSettings(fileName);
      }
   }

   public BaseToolPanel() {
      settingsButton.addMouseListener(new MouseAdapter() {
         public void mousePressed(MouseEvent evt) {
            JPopupMenu popup = new JPopupMenu();
            popup.add(new JMenuItem(new LoadSettingsAction()));
            popup.add(new JMenuItem(new SaveSettingsAction()));
            popup.show(evt.getComponent(),evt.getX(),evt.getY());
      }});

      setSettingsFileDescription("Settings file");
   }

   public void setSettingsFileDescription(String description) {
      settingsFilter = FileUtils.getFileFilter(".xml", description);
   }

   //------------------------------------------------------------------------
   // Override in derived classes
   //------------------------------------------------------------------------
   public void loadSettings(String fileName) {}
   public void saveSettings(String fileName) {}
   public void pressedCancel() {}
   public void pressedClose() {}
   public void pressedApply() {}

   //------------------------------------------------------------------------
   // Dialog Operations
   //------------------------------------------------------------------------
   public Object[] getDialogOptions() {
      return new Object[]{settingsButton, applyButton, okButton, DialogDescriptor.CANCEL_OPTION};
   }

   public void setOwner(Dialog dialog) { ownerDialog = dialog; }

   public void updateApplyButton(boolean applyEnabled) {
      applyButton.setEnabled(applyEnabled);
   }

   public void actionPerformed(ActionEvent evt) {
      if(evt.getActionCommand().equals("Cancel")) {
         pressedCancel();
         // the owner dialog will automatically handle disposing of the dialog in response to Cancel, since this is a standard option (CANCEL_OPTION)
      } else if(evt.getSource() == okButton) {
         pressedClose();
         ownerDialog.dispose();
      } else if(evt.getSource() == applyButton) {
         pressedApply();
      }
   }

   //------------------------------------------------------------------------
   // Helper function to create dialog
   //------------------------------------------------------------------------
   public static void openToolDialog(BaseToolPanel panel, String name) {
      DialogDescriptor dlg = new DialogDescriptor(panel, name, false, panel);
      dlg.setOptions(panel.getDialogOptions());
      Dialog dialog = DialogDisplayer.getDefault().createDialog(dlg);
      panel.setOwner(dialog);
      dialog.setVisible(true);      
      dialog.requestFocus();
   }
}
