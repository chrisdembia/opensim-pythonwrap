package org.opensim.view;

import java.io.File;
import javax.swing.JButton;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.modeling.OpenSimObject;
import org.opensim.swingui.FileTextFieldAndChooser;
import org.opensim.view.editors.ObjectEditDialogMaker;

public class FileTextFieldAndChooserWithEdit extends FileTextFieldAndChooser {

   JButton editButton = new JButton();

   public FileTextFieldAndChooserWithEdit() {
      editButton = new javax.swing.JButton();
      editButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/editor.gif")));
      editButton.setMaximumSize(new java.awt.Dimension(30, 19));
      editButton.setMinimumSize(new java.awt.Dimension(30, 19));
      editButton.setPreferredSize(new java.awt.Dimension(30, 19));
      editButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            editButtonActionPerformed(evt);
         }
      });

      add(editButton);
   }

   public void setFileName(String name, boolean triggerEvent) {
      super.setFileName(name, triggerEvent);
      boolean exists = (new File(name)).exists();
      editButton.setEnabled(isEnabled() && exists);
   }

   private void editButtonActionPerformed(java.awt.event.ActionEvent evt) {
      String originalFileName = getFileName();
      if(ObjectEditDialogMaker.editFile(originalFileName)) {
         // We want our tools to reload the data... if we just fire another state change notice most of them won't do anything
         // because they'll see that the filename hasn't changed... but we can force them to re-update with the following hack:
         setFileName("");
         setFileName(originalFileName);
      }
   }
}
