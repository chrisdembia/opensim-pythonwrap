/*
 * MultiFileSelectorPanel.java
 *
 * Created on July 27, 2007, 4:10 PM
 */

package org.opensim.swingui;

import java.util.Vector;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;

/**
 *
 * @author  erang
 */
public class MultiFileSelectorPanel extends javax.swing.JPanel {
 
   Vector<String> fileNames;
   int currentSelectedIndex = -1;
   DefaultListModel listModel = new DefaultListModel();

   /** Creates new form MultiFileSelectorPanel */
   public MultiFileSelectorPanel(Vector<String> initialFileNames, FileFilter fileFilter) {
      this.fileNames = initialFileNames;

      initComponents();

      fileName.setFileFilter(fileFilter);

      fileList.setModel(listModel);
      for(int i=0; i<fileNames.size(); i++) listModel.addElement(fileNames.get(i));

      fileList.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
         public void valueChanged(ListSelectionEvent event) {
            if(event.getValueIsAdjusting()) return;
            listSelectionChanged();
         }
      });

      updatePanel();
   }

   public Vector<String> getFileNames() { return fileNames; }

   private void listSelectionChanged() {
      currentSelectedIndex = fileList.getSelectedIndex();
      updatePanel();
   }

   private void updatePanel() {
      if(currentSelectedIndex>=0) {
         fileName.setEnabled(true);
         fileName.setFileName(fileNames.get(currentSelectedIndex),false);
         deleteButton.setEnabled(true);
      } else {
         fileName.setEnabled(false);
         fileName.setFileName("",false);
         deleteButton.setEnabled(false);
      }
   }

   //------------------------------------------------------------------------
   // showDialog helper
   //------------------------------------------------------------------------
   static public Vector<String> showDialog(Vector<String> initialFileNames, FileFilter fileFilter) {
      // TODO: add file validator callback (FileTextFieldAndChooser needs this)
      MultiFileSelectorPanel panel = new MultiFileSelectorPanel(initialFileNames, fileFilter);
      DialogDescriptor dlg = new DialogDescriptor(panel, "Edit File List");
      Object answer = DialogDisplayer.getDefault().notify(dlg);
      if(answer==NotifyDescriptor.OK_OPTION) return panel.getFileNames();
      else return null;
   }

   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jScrollPane1 = new javax.swing.JScrollPane();
      fileList = new javax.swing.JList();
      fileName = new org.opensim.swingui.FileTextFieldAndChooser();
      addButton = new javax.swing.JButton();
      deleteButton = new javax.swing.JButton();

      fileList.setModel(new javax.swing.AbstractListModel() {
         String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
         public int getSize() { return strings.length; }
         public Object getElementAt(int i) { return strings[i]; }
      });
      fileList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
      jScrollPane1.setViewportView(fileList);

      fileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            fileNameStateChanged(evt);
         }
      });

      addButton.setText("Add");
      addButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            addButtonActionPerformed(evt);
         }
      });

      deleteButton.setText("Delete");
      deleteButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            deleteButtonActionPerformed(evt);
         }
      });

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(layout.createSequentialGroup()
                  .add(addButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 63, Short.MAX_VALUE)
                  .add(327, 327, 327))
               .add(layout.createSequentialGroup()
                  .add(deleteButton)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, fileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 311, Short.MAX_VALUE)
                     .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 311, Short.MAX_VALUE))
                  .addContainerGap())))
      );

      layout.linkSize(new java.awt.Component[] {addButton, deleteButton}, org.jdesktop.layout.GroupLayout.HORIZONTAL);

      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(layout.createSequentialGroup()
                  .add(addButton)
                  .add(0, 0, 0)
                  .add(deleteButton))
               .add(jScrollPane1))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(fileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   private void fileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_fileNameStateChanged
      if(currentSelectedIndex>=0) {
         fileNames.set(currentSelectedIndex, fileName.getFileName());
         listModel.set(currentSelectedIndex, fileName.getFileName());
      }
   }//GEN-LAST:event_fileNameStateChanged

   private void deleteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_deleteButtonActionPerformed
      if(currentSelectedIndex>=0) {
         fileNames.remove(currentSelectedIndex);
         listModel.remove(currentSelectedIndex);
      }
   }//GEN-LAST:event_deleteButtonActionPerformed

   private void addButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addButtonActionPerformed
      fileNames.add("Unassigned");
      listModel.addElement("Unassigned");
      fileList.setSelectedIndex(fileNames.size()-1);
   }//GEN-LAST:event_addButtonActionPerformed
   
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton addButton;
   private javax.swing.JButton deleteButton;
   private javax.swing.JList fileList;
   private org.opensim.swingui.FileTextFieldAndChooser fileName;
   private javax.swing.JScrollPane jScrollPane1;
   // End of variables declaration//GEN-END:variables
   
}
