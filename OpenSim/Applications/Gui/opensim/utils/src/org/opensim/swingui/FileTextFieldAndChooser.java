package org.opensim.swingui;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.JCheckBox;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.opensim.utils.FileUtils;

public class FileTextFieldAndChooser extends javax.swing.JPanel implements ActionListener {

   private static Color validBackground = Color.white;
   private static Color invalidBackground = new Color(255,102,102);

   private String extensions = null;
   private String description = null;

   private String lastFileName; // keep track of previous value to avoid firing change events when name stays the same
   private boolean fileIsValid = true;
   private boolean treatUnassignedAsEmptyString = true;
   private boolean treatEmptyStringAsValid = false;
   private boolean checkIfFileExists = true;

   private JCheckBox checkBox = null; // Optional associated check box which enables/disables the text field

   public FileTextFieldAndChooser() {
      initComponents();
      lastFileName = fileNameTextField.getText();
   }

   public FileTextFieldAndChooser(String extensions, String description) {
      initComponents();
      lastFileName = fileNameTextField.getText();
      setExtensionsAndDescription(extensions,description);
   }

   public void setCheckIfFileExists(boolean check) {
      checkIfFileExists = check;
   }

   public void setExtensionsAndDescription(String extensions, String description) {
      this.extensions = extensions;
      this.description = description;
   }

   public String getFileName() {
      return fileNameTextField.getText();
   }

   public void setFileName(String name, boolean triggerEvent) {
      if(name==null || (name.equals("Unassigned") && treatUnassignedAsEmptyString)) name = "";
      if(!name.equals(lastFileName)) {
         lastFileName = name;
         fileNameTextField.setText(name);
         if(checkIfFileExists) setFileIsValid((new File(name)).exists());
         else setFileIsValid(true);
         if(triggerEvent) fireStateChanged();
      }
   }

   public void setFileName(String name) {
      setFileName(name, true);
   }

   public boolean getFileIsValid() {
      return fileIsValid;
   }

   public void setFileIsValid(boolean valid) {
      fileIsValid = valid;
      updateTextFieldColor();
   }

   public void setEnabled(boolean enabled) {
      super.setEnabled(enabled);
      for(Component comp : getComponents()) comp.setEnabled(enabled);
      updateTextFieldColor();
   }

   public void setTreatEmptyStringAsValid(boolean asValid) {
      treatEmptyStringAsValid = asValid;
   }

   //------------------------------------------------------------------------
   // Associated check box
   //------------------------------------------------------------------------

   public void setAssociatedCheckBox(JCheckBox checkBox) {
      if(this.checkBox!=null) this.checkBox.removeActionListener(this);
      this.checkBox = checkBox;
      if(this.checkBox!=null) this.checkBox.addActionListener(this);
      setEnabled(this.checkBox.isSelected());
   }

   public void actionPerformed(ActionEvent evt) {
      if(evt.getSource()==checkBox && isEnabled() != checkBox.isSelected()) {
         setEnabled(checkBox.isSelected());
         fireStateChanged();
      }
   }

   //------------------------------------------------------------------------
   // ChangeListener code taken from AbstractButton.java
   //------------------------------------------------------------------------

   protected transient ChangeEvent changeEvent;
   public void addChangeListener(ChangeListener l) {
      listenerList.add(ChangeListener.class, l);
   }
   public void removeChangeListener(ChangeListener l) {
      listenerList.remove(ChangeListener.class, l);
   }
   public ChangeListener[] getChangeListeners() {
      return (ChangeListener[])(listenerList.getListeners(ChangeListener.class));
   }
   protected void fireStateChanged() {
      // Guaranteed to return a non-null array
      Object[] listeners = listenerList.getListenerList();
      // Process the listeners last to first, notifying
      // those that are interested in this event
      for (int i = listeners.length-2; i>=0; i-=2) {
         if (listeners[i]==ChangeListener.class) {
            // Lazily create the event:
            if (changeEvent == null)
               changeEvent = new ChangeEvent(this);
            ((ChangeListener)listeners[i+1]).stateChanged(changeEvent);
         }          
      }
   }   

   //------------------------------------------------------------------------
   // Utilities
   //------------------------------------------------------------------------

   private void updateTextFieldColor() {
      if(isEnabled() && (!fileIsValid || (!treatEmptyStringAsValid && fileNameTextField.getText().equals(""))))
         fileNameTextField.setBackground(invalidBackground);
      else fileNameTextField.setBackground(validBackground); 
   }

   //------------------------------------------------------------------------
   // Event handling for the text field / button
   //------------------------------------------------------------------------

   private void fileNameTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_fileNameTextFieldFocusLost
      if(!evt.isTemporary()) setFileName(fileNameTextField.getText());
   }//GEN-LAST:event_fileNameTextFieldFocusLost

   private void browseButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_browseButtonActionPerformed
      String result = FileUtils.getInstance().browseForFilename(extensions, description);
      if(result != null) setFileName(result);
   }//GEN-LAST:event_browseButtonActionPerformed

   private void fileNameTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_fileNameTextFieldActionPerformed
      setFileName(fileNameTextField.getText());
   }//GEN-LAST:event_fileNameTextFieldActionPerformed
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      fileNameTextField = new javax.swing.JTextField();
      browseButton = new javax.swing.JButton();

      setLayout(new javax.swing.BoxLayout(this, javax.swing.BoxLayout.X_AXIS));

      fileNameTextField.setMaximumSize(new java.awt.Dimension(2147483647, 19));
      fileNameTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            fileNameTextFieldActionPerformed(evt);
         }
      });
      fileNameTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            fileNameTextFieldFocusLost(evt);
         }
      });

      add(fileNameTextField);

      browseButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("FolderOpen.gif")));
      browseButton.setMaximumSize(new java.awt.Dimension(30, 19));
      browseButton.setMinimumSize(new java.awt.Dimension(30, 19));
      browseButton.setPreferredSize(new java.awt.Dimension(30, 19));
      browseButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            browseButtonActionPerformed(evt);
         }
      });

      add(browseButton);

   }// </editor-fold>//GEN-END:initComponents
   
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton browseButton;
   private javax.swing.JTextField fileNameTextField;
   // End of variables declaration//GEN-END:variables
   
}
