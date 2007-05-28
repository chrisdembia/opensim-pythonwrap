/*
 * GroupsJPanel.java
 *
 * Created on May 20, 2007, 10:13 PM
 */

package org.opensim.view;

import javax.swing.DefaultListModel;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.ObjectGroup;
import javax.swing.border.TitledBorder;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author  Ayman Habib
 */
public class GroupEditorPanel extends javax.swing.JPanel 
                              implements ListSelectionListener,
                                         DocumentListener
{
    
    private CoordinateSet dSet;
    private DefaultListModel availaleGroups = new DefaultListModel();
    private DefaultListModel allSetMemebers = new DefaultListModel();
    private DefaultListModel currentSetMembers = new DefaultListModel();
    private ObjectGroup currentGroup;
    ListSelectionModel listSelectionModel;   // For the list of groups
    private static String NEW_GROUP="New Group";
    private CoordinateSet saveSet;
    
    /** Creates new form GroupsJPanel */
    public GroupEditorPanel(CoordinateSet aSet) {     
        dSet = aSet;
        saveSet = aSet;
        initComponents();
        populateLists();
        listSelectionModel = jAllGroupsList.getSelectionModel();
        listSelectionModel.addListSelectionListener(this);
        jFormattedGroupNameTextField.getDocument().addDocumentListener(this);
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jPanel3 = new javax.swing.JPanel();
      jScrollPane3 = new javax.swing.JScrollPane();
      jAllGroupsList = new javax.swing.JList();
      jDeleteButton = new javax.swing.JButton();
      jNewButton = new javax.swing.JButton();
      jSeparator1 = new javax.swing.JSeparator();
      jPanel2 = new javax.swing.JPanel();
      jScrollPane1 = new javax.swing.JScrollPane();
      jFromList = new javax.swing.JList();
      jScrollPane2 = new javax.swing.JScrollPane();
      jToList = new javax.swing.JList();
      jRemoveItemsButton = new javax.swing.JButton();
      jAddItemsButton = new javax.swing.JButton();
      jLabel1 = new javax.swing.JLabel();
      jFormattedGroupNameTextField = new javax.swing.JFormattedTextField();

      jScrollPane3.setBorder(javax.swing.BorderFactory.createTitledBorder("Coordinate Groups"));
      jAllGroupsList.setModel(new javax.swing.AbstractListModel() {
         String[] strings = { "All", "Group 1", "Group 2", "Group 3", "Group 4", "Group 5" };
         public int getSize() { return strings.length; }
         public Object getElementAt(int i) { return strings[i]; }
      });
      jAllGroupsList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
      jAllGroupsList.setToolTipText("List of available groups");
      jScrollPane3.setViewportView(jAllGroupsList);

      jDeleteButton.setText("Delete Group");
      jDeleteButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jDeleteButtonActionPerformed(evt);
         }
      });

      jNewButton.setText("Add Group");
      jNewButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jNewButtonActionPerformed(evt);
         }
      });

      jPanel2.setBorder(javax.swing.BorderFactory.createEtchedBorder());
      jScrollPane1.setBorder(javax.swing.BorderFactory.createTitledBorder("Available"));
      jFromList.setModel(new javax.swing.AbstractListModel() {
         String[] strings = { "Coordinate 1", "Coordinate 2", "Coordinate 3", "Coordinate 4", "Coordinate 5", "Coordinate 6" };
         public int getSize() { return strings.length; }
         public Object getElementAt(int i) { return strings[i]; }
      });
      jScrollPane1.setViewportView(jFromList);

      jScrollPane2.setBorder(javax.swing.BorderFactory.createTitledBorder("Group Members"));
      jToList.setModel(new javax.swing.AbstractListModel() {
         String[] strings = { "Coordinate 1", "Coordinate 5", "Coordinate 6", "Coordinate 9" };
         public int getSize() { return strings.length; }
         public Object getElementAt(int i) { return strings[i]; }
      });
      jScrollPane2.setViewportView(jToList);

      jRemoveItemsButton.setText("<<");
      jRemoveItemsButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jRemoveItemsButtonActionPerformed(evt);
         }
      });

      jAddItemsButton.setText(">>");
      jAddItemsButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jAddItemsButtonActionPerformed(evt);
         }
      });

      jLabel1.setText("Group Name:");

      jFormattedGroupNameTextField.setEnabled(false);

      org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
      jPanel2.setLayout(jPanel2Layout);
      jPanel2Layout.setHorizontalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel2Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel2Layout.createSequentialGroup()
                  .add(jScrollPane1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 115, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(jAddItemsButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 49, Short.MAX_VALUE)
                     .add(jRemoveItemsButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
               .add(jPanel2Layout.createSequentialGroup()
                  .add(jLabel1)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jFormattedGroupNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 103, Short.MAX_VALUE)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 116, Short.MAX_VALUE)
            .addContainerGap())
      );
      jPanel2Layout.setVerticalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel2Layout.createSequentialGroup()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jFormattedGroupNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel1))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jPanel2Layout.createSequentialGroup()
                  .add(21, 21, 21)
                  .add(jAddItemsButton)
                  .add(14, 14, 14)
                  .add(jRemoveItemsButton)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 33, Short.MAX_VALUE))
               .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 114, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.LEADING, jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 114, Short.MAX_VALUE))
            .addContainerGap())
      );

      org.jdesktop.layout.GroupLayout jPanel3Layout = new org.jdesktop.layout.GroupLayout(jPanel3);
      jPanel3.setLayout(jPanel3Layout);
      jPanel3Layout.setHorizontalGroup(
         jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel3Layout.createSequentialGroup()
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jSeparator1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 326, Short.MAX_VALUE)
               .add(jScrollPane3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 326, Short.MAX_VALUE)
               .add(jPanel3Layout.createSequentialGroup()
                  .add(57, 57, 57)
                  .add(jNewButton)
                  .add(32, 32, 32)
                  .add(jDeleteButton))
               .add(jPanel3Layout.createSequentialGroup()
                  .addContainerGap()
                  .add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
            .addContainerGap())
      );
      jPanel3Layout.setVerticalGroup(
         jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel3Layout.createSequentialGroup()
            .add(jScrollPane3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 123, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jNewButton)
               .add(jDeleteButton))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jSeparator1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addContainerGap())
      );

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jPanel3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   private void jRemoveItemsButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRemoveItemsButtonActionPerformed
      ListSelectionModel lsm = jToList.getSelectionModel();
      if (lsm.isSelectionEmpty())
         return;
      // Multiple interval selection. Loop thru them
 
      int minIndex=lsm.getMinSelectionIndex();
      int maxIndex=lsm.getMaxSelectionIndex();
      for(int i=minIndex; i<=maxIndex; i++){
         if (lsm.isSelectedIndex(i)){
            String objName=(String) jToList.getModel().getElementAt(i);
            if (currentGroup.contains(objName))
               currentGroup.remove(dSet.get(objName));
         }
      }
      updateCurrentGroup();
// TODO add your handling code here:
   }//GEN-LAST:event_jRemoveItemsButtonActionPerformed

   private void jDeleteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDeleteButtonActionPerformed
      //jAllGroupsList.r
      ListSelectionModel lsm = jAllGroupsList.getSelectionModel();
      if (lsm.isSelectionEmpty())
         return;
      int minIndex=lsm.getMinSelectionIndex();
      int maxIndex=lsm.getMaxSelectionIndex();
      //remove listeners temporarily
      lsm.removeListSelectionListener(this);
      for(int i=minIndex; i<=maxIndex; i++){
         if (lsm.isSelectedIndex(i)){
            Object obj=jAllGroupsList.getModel().getElementAt(i);
            if (obj instanceof ObjectGroup){
               ObjectGroup groupToDelete = (ObjectGroup) obj;
               // Find an alternate group and make it current
               if (jAllGroupsList.getModel().getSize()==1){
                  throw new UnsupportedOperationException("Not yet implemented");
               }
               else {
                  currentGroup=(ObjectGroup) jAllGroupsList.getModel().getElementAt(0);
                  dSet.removeGroup(groupToDelete.getName());
               }
               
            }
         }
      }
      updateGroupsList();
      // Restore listeners
      lsm.addListSelectionListener(this);

   }//GEN-LAST:event_jDeleteButtonActionPerformed

   private void jNewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jNewButtonActionPerformed
// TODO add your handling code here:
      dSet.addGroup(NEW_GROUP);
      updateGroupsList();
      currentGroup = dSet.getGroup(NEW_GROUP);
      updateCurrentGroup();   
   }//GEN-LAST:event_jNewButtonActionPerformed

   private void jAddItemsButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAddItemsButtonActionPerformed
// TODO add your handling code here:
      // Get selected items from allSetMemebers and add them to currentSetMembers
      ListSelectionModel lsm = jFromList.getSelectionModel();
      if (lsm.isSelectionEmpty())
         return;
      // Multiple interval selection. Loop thru them
 
      int minIndex=lsm.getMinSelectionIndex();
      int maxIndex=lsm.getMaxSelectionIndex();
      for(int i=minIndex; i<=maxIndex; i++){
         if (lsm.isSelectedIndex(i)){
            String objName=(String) jFromList.getModel().getElementAt(i);
            if (!currentGroup.contains(objName))
               currentGroup.add(dSet.get(objName));
         }
      }
      updateCurrentGroup();
   }//GEN-LAST:event_jAddItemsButtonActionPerformed
   /**
    * Populate Top list (of all groups) and bottom left (all available)
    * The lower right list of current members is populated by updateCurrentGroup
    */
    private void populateLists() {
       // Existing groups
       updateGroupsList();
       for(int i=0; i<dSet.getSize(); i++)
         allSetMemebers.add(i, dSet.get(i).getName());
       jFromList.setModel(allSetMemebers);
       
       //if any groups are defined we'll edit the first one by default
       if(availaleGroups.getSize()>=1){
          currentGroup = (ObjectGroup)availaleGroups.firstElement();
       }
       updateCurrentGroup();
        
    }
    // Populate list of current Group members 
   private void updateCurrentGroup() {
      // Get group members and populate the "to" list"
      ArrayPtrsObj members =currentGroup.getMembers();
      currentSetMembers.removeAllElements();
      for(int i=0; i<members.getSize(); i++)
         currentSetMembers.addElement(members.get(i).getName());
      jToList.setModel(currentSetMembers);
      jFormattedGroupNameTextField.setText(currentGroup.getName());
      //((TitledBorder)jScrollPane2.getBorder()).setTitle(currentGroup.getName()+" members");
      
   }
   // Handler for list of groups selection change
   public void valueChanged(ListSelectionEvent e) {
      if (e.getValueIsAdjusting())  
         return;
      ListSelectionModel lsm = (ListSelectionModel)e.getSource();
      if (lsm.isSelectionEmpty())
         return;
      if (lsm.equals(jAllGroupsList.getSelectionModel())){
         // Due to SINGLE_SELECTION mode we'll break on first match
         int minIndex=lsm.getMinSelectionIndex();
         int maxIndex=lsm.getMaxSelectionIndex();
         for(int i=minIndex; i<=maxIndex; i++){
            if (lsm.isSelectedIndex(i)){
               Object obj=jAllGroupsList.getModel().getElementAt(i);
               if (obj instanceof ObjectGroup){
                  currentGroup = (ObjectGroup) obj;
                  updateCurrentGroup();
               }
            }
         }
      }
   }

   private void updateGroupsList() {
       jAllGroupsList.removeAll();
       ArrayStr groups = new ArrayStr();
       dSet.getGroupNames(groups);
       for(int i=0; i<groups.getSize(); i++){
         availaleGroups.add(i, dSet.getGroup(groups.getitem(i)));  
       }
       jAllGroupsList.setModel(availaleGroups);
   }

   public void cancel() {
      // Copy back original set from saved one
      //dSet.copy(saveSet);
   }

   public void insertUpdate(DocumentEvent e) {
        handleGroupRename();
   }

   public void removeUpdate(DocumentEvent e) {
        handleGroupRename();
   }

   public void changedUpdate(DocumentEvent e) {
        handleGroupRename();
   }

   private void handleGroupRename() {
      String newName = (String)jFormattedGroupNameTextField.getText();
          //currentGroup.renameTo(newName);
      int i=0;
   }

    
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton jAddItemsButton;
   private javax.swing.JList jAllGroupsList;
   private javax.swing.JButton jDeleteButton;
   private javax.swing.JFormattedTextField jFormattedGroupNameTextField;
   private javax.swing.JList jFromList;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JButton jNewButton;
   private javax.swing.JPanel jPanel2;
   private javax.swing.JPanel jPanel3;
   private javax.swing.JButton jRemoveItemsButton;
   private javax.swing.JScrollPane jScrollPane1;
   private javax.swing.JScrollPane jScrollPane2;
   private javax.swing.JScrollPane jScrollPane3;
   private javax.swing.JSeparator jSeparator1;
   private javax.swing.JList jToList;
   // End of variables declaration//GEN-END:variables
    

}
