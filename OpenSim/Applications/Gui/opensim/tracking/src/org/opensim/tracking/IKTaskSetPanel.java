/*
 * IKMarkerTaskPanel.java
 *
 * Created on July 4, 2007, 1:39 PM
 */

package org.opensim.tracking;

import java.awt.Component;
import java.io.File;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;

/**
 *
 * @author  erang
 */
public class IKTaskSetPanel extends javax.swing.JPanel implements ListSelectionListener, TableModelListener {
   private final static int enabledColumnWidth = 60;

   IKCommonModel ikCommonModel;

   IKTasksTableModel ikMarkerTasksTableModel;
   IKTasksTableModel ikCoordinateTasksTableModel;

   JTable activeTable = null; // the one which was the source of the last selection event (the one whose data is displayed in the panel's fields)
   
   /** Creates new form IKCoordinateTaskPanel */
   public IKTaskSetPanel(IKCommonModel ikCommonModel) {
      this.ikCommonModel = ikCommonModel;

      ikMarkerTasksTableModel = new IKTasksTableModel(ikCommonModel.getIKMarkerTasksModel(), "Marker");
      ikCoordinateTasksTableModel = new IKTasksTableModel(ikCommonModel.getIKCoordinateTasksModel(), "Coordinate");

      initComponents();

      ikMarkerTasksTable.setModel(ikMarkerTasksTableModel);
      ikCoordinateTasksTable.setModel(ikCoordinateTasksTableModel);

      for(JTable table : new JTable[]{ikMarkerTasksTable, ikCoordinateTasksTable}) {
         table.getSelectionModel().addListSelectionListener(this);
         table.getModel().addTableModelListener(this);

         table.setDefaultRenderer(IKTasksNameCell.class, new IKTasksNameCellRenderer());
         table.setDefaultRenderer(IKTasksValueCell.class, new IKTasksValueCellRenderer());
         table.setDefaultRenderer(IKTasksWeightCell.class, new IKTasksWeightCellRenderer());

         table.getColumnModel().getColumn(0).setPreferredWidth(enabledColumnWidth);
         table.getColumnModel().getColumn(0).setMinWidth(enabledColumnWidth);
         table.getColumnModel().getColumn(0).setMaxWidth(enabledColumnWidth);
      }

      updatePanel();
   }

   private IKTasksTableModel activeTableModel() { return activeTable!=null ? (IKTasksTableModel)activeTable.getModel() : null; }
   private IKTasksModel activeModel() { return activeTableModel()!=null ? activeTableModel().getIKTasksModel() : null; }

   //------------------------------------------------------------------------
   // Table data and selection handlers
   //------------------------------------------------------------------------
   public void tableChanged(TableModelEvent evt) {
      updatePanel();
   }

   public void valueChanged(ListSelectionEvent event) {
      if(event.getValueIsAdjusting()) return;

      // Update activeTable
      JTable otherTable = null;
      if(event.getSource()==ikMarkerTasksTable.getSelectionModel()) { activeTable = ikMarkerTasksTable; otherTable = ikCoordinateTasksTable; }
      else if(event.getSource()==ikCoordinateTasksTable.getSelectionModel()) { activeTable = ikCoordinateTasksTable; otherTable = ikMarkerTasksTable; }
      // Make sure only one table is selected at a time
      if(otherTable.getSelectedRowCount()>0) {
         otherTable.getSelectionModel().removeListSelectionListener(this);
         otherTable.getSelectionModel().clearSelection();
         otherTable.getSelectionModel().addListSelectionListener(this);
      }

      // TODO: if pending changes, might want to apply them to old selection
      updatePanel();
   }

   public void updatePanel() {
      updateSelectionCheckBoxes();
      updateValueComponents();
      updateWeightTextField();
   }

   private void updateSelectionCheckBoxes() {
      enableSelectedCheckBox.setSelected(false);
      disableSelectedCheckBox.setSelected(false);
      enableSelectedCheckBox.setEnabled(false);
      disableSelectedCheckBox.setEnabled(false);
      if(activeTable!=null && activeTable.getSelectedRowCount()>0) {
         boolean sameEnabled = activeTableModel().isSameEnabled(activeTable.getSelectedRows());
         if(sameEnabled) {
            if(activeModel().getEnabled(activeTable.getSelectedRows()[0])) { // all are enabled
               enableSelectedCheckBox.setSelected(true);
               disableSelectedCheckBox.setEnabled(true);
            } else {
               disableSelectedCheckBox.setSelected(true);
               enableSelectedCheckBox.setEnabled(true);
            }
         } else {
            enableSelectedCheckBox.setEnabled(true);
            disableSelectedCheckBox.setEnabled(true);
         }
      }
   }

   private void updateWeightTextField() {
      weightTextField.setText("");
      if(activeTable!=null && activeTable.getSelectedRowCount() > 0) {
         boolean sameWeight = activeTableModel().isSameWeight(activeTable.getSelectedRows());
         if(sameWeight) {
            if(activeModel().isLocked(activeTable.getSelectedRows()[0])) {
               weightTextField.setText(IKTasksTableModel.LockedStr); // and keep disabled
               weightTextField.setEnabled(false);
            } else {
               weightTextField.setText(((Double)activeModel().getWeight(activeTable.getSelectedRows()[0])).toString());
               weightTextField.setEnabled(true);
            }
         } else {
            weightTextField.setEnabled(true);
         }
      } else {
         weightTextField.setEnabled(false);
      }
   }

   private void updateValueComponents() {
      if(activeTable==null || activeTable.getSelectedRowCount()==0) {
         fromFileTextField.setText("");
         defaultValueTextField.setText("");
         manualValueTextField.setText("");
         buttonGroup1.setSelected(noValueRadioButton.getModel(),true);
         for(Component comp : new Component[]{fromFileRadioButton, defaultValueRadioButton, manualValueRadioButton, fromFileTextField, defaultValueTextField, manualValueTextField})
            comp.setEnabled(false);
      } else {
         boolean sameValueType = activeTableModel().isSameValueType(activeTable.getSelectedRows());
         boolean sameDefaultValue = activeTableModel().isSameDefaultValue(activeTable.getSelectedRows());
         boolean sameManualValue = activeTableModel().isSameManualValue(activeTable.getSelectedRows());

         Component enabledTextField = null;
         if(sameValueType) {
            switch(activeModel().getValueType(activeTable.getSelectedRows()[0])) {
               case FromFile:
                  buttonGroup1.setSelected(fromFileRadioButton.getModel(),true); 
                  enabledTextField = fromFileTextField;
                  break;
               case DefaultValue: 
                  buttonGroup1.setSelected(defaultValueRadioButton.getModel(),true); 
                  enabledTextField = defaultValueTextField;
                  break;
               case ManualValue: 
                  buttonGroup1.setSelected(manualValueRadioButton.getModel(),true); 
                  enabledTextField = manualValueTextField;
                  break;
            }
         } else {
            buttonGroup1.setSelected(noValueRadioButton.getModel(),true);
         }
         for(Component comp : new Component[]{fromFileTextField, defaultValueTextField, manualValueTextField})
            comp.setEnabled(comp==enabledTextField);

         // TODO: update as file changes and depending on which table
         String fileName = (activeTable==ikMarkerTasksTable) ? ikCommonModel.getMarkerDataFileName() : ikCommonModel.getCoordinateDataFileName();
         fromFileTextField.setText((new File(fileName)).getName());

         if(activeTable==ikCoordinateTasksTable) {
            fromFileRadioButton.setEnabled(true);
            defaultValueRadioButton.setEnabled(true);
            manualValueRadioButton.setEnabled(true);

            if(sameDefaultValue) defaultValueTextField.setText(((Double)activeModel().getDefaultValue(activeTable.getSelectedRows()[0])).toString());
            else defaultValueTextField.setText("Different");
            if(sameManualValue) manualValueTextField.setText(((Double)activeModel().getManualValue(activeTable.getSelectedRows()[0])).toString());
            else manualValueTextField.setText("");
         } else {
            fromFileRadioButton.setEnabled(true);
            defaultValueRadioButton.setEnabled(false);
            manualValueRadioButton.setEnabled(false);

            defaultValueTextField.setText("");
            manualValueTextField.setText("");
         }
      }
   }

   //////////////////////////////////////////////////////////////////////////
   // GUI stuff
   //////////////////////////////////////////////////////////////////////////
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      buttonGroup1 = new javax.swing.ButtonGroup();
      noValueRadioButton = new javax.swing.JRadioButton();
      jLabel1 = new javax.swing.JLabel();
      weightTextField = new javax.swing.JTextField();
      enableSelectedCheckBox = new javax.swing.JCheckBox();
      disableSelectedCheckBox = new javax.swing.JCheckBox();
      jLabel2 = new javax.swing.JLabel();
      fromFileRadioButton = new javax.swing.JRadioButton();
      defaultValueRadioButton = new javax.swing.JRadioButton();
      manualValueRadioButton = new javax.swing.JRadioButton();
      fromFileTextField = new javax.swing.JTextField();
      defaultValueTextField = new javax.swing.JTextField();
      manualValueTextField = new javax.swing.JTextField();
      jScrollPane2 = new javax.swing.JScrollPane();
      ikCoordinateTasksTable = new javax.swing.JTable();
      jScrollPane1 = new javax.swing.JScrollPane();
      ikMarkerTasksTable = new javax.swing.JTable();

      buttonGroup1.add(noValueRadioButton);
      noValueRadioButton.setText("jRadioButton1");
      noValueRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      noValueRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      jLabel1.setText("Weight");

      weightTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      weightTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            weightTextFieldActionPerformed(evt);
         }
      });
      weightTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            weightTextFieldFocusLost(evt);
         }
      });

      enableSelectedCheckBox.setText("Enable all selected");
      enableSelectedCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      enableSelectedCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      enableSelectedCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            enableSelectedCheckBoxActionPerformed(evt);
         }
      });

      disableSelectedCheckBox.setText("Disable all selected");
      disableSelectedCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      disableSelectedCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      disableSelectedCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            disableSelectedCheckBoxActionPerformed(evt);
         }
      });

      jLabel2.setText("Value");

      buttonGroup1.add(fromFileRadioButton);
      fromFileRadioButton.setText("From file");
      fromFileRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      fromFileRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      fromFileRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            fromFileRadioButtonActionPerformed(evt);
         }
      });

      buttonGroup1.add(defaultValueRadioButton);
      defaultValueRadioButton.setText("Default value");
      defaultValueRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      defaultValueRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      defaultValueRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            defaultValueRadioButtonActionPerformed(evt);
         }
      });

      buttonGroup1.add(manualValueRadioButton);
      manualValueRadioButton.setText("Manual value");
      manualValueRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      manualValueRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      manualValueRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            manualValueRadioButtonActionPerformed(evt);
         }
      });

      fromFileTextField.setEditable(false);
      fromFileTextField.setText("jTextField1");

      defaultValueTextField.setEditable(false);
      defaultValueTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      defaultValueTextField.setText("jTextField2");

      manualValueTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      manualValueTextField.setText("jTextField3");
      manualValueTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            manualValueTextFieldActionPerformed(evt);
         }
      });
      manualValueTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            manualValueTextFieldFocusLost(evt);
         }
      });

      jScrollPane2.setViewportView(ikCoordinateTasksTable);

      ikMarkerTasksTable.setModel(new javax.swing.table.DefaultTableModel(
         new Object [][] {
            {null, null, null, null},
            {null, null, null, null},
            {null, null, null, null},
            {null, null, null, null}
         },
         new String [] {
            "Title 1", "Title 2", "Title 3", "Title 4"
         }
      ));
      jScrollPane1.setViewportView(ikMarkerTasksTable);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 652, Short.MAX_VALUE)
               .add(layout.createSequentialGroup()
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(layout.createSequentialGroup()
                        .add(enableSelectedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 105, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(70, 70, 70)
                        .add(jLabel2))
                     .add(disableSelectedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 107, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(defaultValueRadioButton)
                     .add(manualValueRadioButton)
                     .add(fromFileRadioButton))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, fromFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 115, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(defaultValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(manualValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 102, Short.MAX_VALUE)
                  .add(jLabel1)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(weightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 105, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
               .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 652, Short.MAX_VALUE))
            .addContainerGap())
      );

      layout.linkSize(new java.awt.Component[] {defaultValueTextField, fromFileTextField, manualValueTextField}, org.jdesktop.layout.GroupLayout.HORIZONTAL);

      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, layout.createSequentialGroup()
            .addContainerGap()
            .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 247, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 244, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                  .add(weightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(jLabel1))
               .add(layout.createSequentialGroup()
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(fromFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(fromFileRadioButton)
                     .add(jLabel2)
                     .add(enableSelectedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 15, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(defaultValueRadioButton)
                     .add(defaultValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(disableSelectedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 15, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(manualValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(manualValueRadioButton))))
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   // We don't want to process a focus event if the focus is lost due to clicking on one of the tables because then the
   // selected rows of that table would be different from the row we would like to apply the change to (the old selected rows list)
   private boolean safeToProcessFocusEvent(java.awt.event.FocusEvent evt) {
      return !evt.isTemporary() && evt.getOppositeComponent()!=ikMarkerTasksTable && evt.getOppositeComponent()!=ikCoordinateTasksTable;
   }

   private void manualValueRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_manualValueRadioButtonActionPerformed
      activeTableModel().setValueType(activeTable.getSelectedRows(), IKTasksModel.ValueType.ManualValue);
   }//GEN-LAST:event_manualValueRadioButtonActionPerformed

   private void defaultValueRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_defaultValueRadioButtonActionPerformed
      activeTableModel().setValueType(activeTable.getSelectedRows(), IKTasksModel.ValueType.DefaultValue);
   }//GEN-LAST:event_defaultValueRadioButtonActionPerformed

   private void fromFileRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_fromFileRadioButtonActionPerformed
      activeTableModel().setValueType(activeTable.getSelectedRows(), IKTasksModel.ValueType.FromFile);
   }//GEN-LAST:event_fromFileRadioButtonActionPerformed

   private void setManualValueFromTextField() {
      try {
         double value = Double.valueOf(manualValueTextField.getText());
         activeTableModel().setManualValue(activeTable.getSelectedRows(), value);
      } catch (NumberFormatException ex) {
      }
   }

   private void manualValueTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_manualValueTextFieldFocusLost
      if(safeToProcessFocusEvent(evt)) setManualValueFromTextField();
   }//GEN-LAST:event_manualValueTextFieldFocusLost

   private void manualValueTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_manualValueTextFieldActionPerformed
      setManualValueFromTextField();
   }//GEN-LAST:event_manualValueTextFieldActionPerformed

   private void setWeightFromTextField() {
      try {
         double weight = Double.valueOf(weightTextField.getText());
         activeTableModel().setWeight(activeTable.getSelectedRows(), weight);
      } catch (NumberFormatException ex) {
      }
   }

   private void weightTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_weightTextFieldFocusLost
      if(safeToProcessFocusEvent(evt)) setWeightFromTextField();
   }//GEN-LAST:event_weightTextFieldFocusLost

   private void weightTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_weightTextFieldActionPerformed
      setWeightFromTextField();
   }//GEN-LAST:event_weightTextFieldActionPerformed

   private void disableSelectedCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_disableSelectedCheckBoxActionPerformed
      activeTableModel().setEnabled(activeTable.getSelectedRows(), false);
   }//GEN-LAST:event_disableSelectedCheckBoxActionPerformed

   private void enableSelectedCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_enableSelectedCheckBoxActionPerformed
      activeTableModel().setEnabled(activeTable.getSelectedRows(), true);
   }//GEN-LAST:event_enableSelectedCheckBoxActionPerformed
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.ButtonGroup buttonGroup1;
   private javax.swing.JRadioButton defaultValueRadioButton;
   private javax.swing.JTextField defaultValueTextField;
   private javax.swing.JCheckBox disableSelectedCheckBox;
   private javax.swing.JCheckBox enableSelectedCheckBox;
   private javax.swing.JRadioButton fromFileRadioButton;
   private javax.swing.JTextField fromFileTextField;
   private javax.swing.JTable ikCoordinateTasksTable;
   private javax.swing.JTable ikMarkerTasksTable;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel2;
   private javax.swing.JScrollPane jScrollPane1;
   private javax.swing.JScrollPane jScrollPane2;
   private javax.swing.JRadioButton manualValueRadioButton;
   private javax.swing.JTextField manualValueTextField;
   private javax.swing.JRadioButton noValueRadioButton;
   private javax.swing.JTextField weightTextField;
   // End of variables declaration//GEN-END:variables
}
