/*
 * IKToolPanel.java
 *
 * Created on July 16, 2007, 5:17 PM
 */

package org.opensim.tracking;

import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDescriptor;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.Model;
import org.opensim.utils.FileUtils;

public class IKToolPanel extends javax.swing.JPanel implements ActionListener, Observer {
   private IKToolModel ikToolModel = null;

   private FileFilter settingsFilter = FileUtils.getFileFilter(".xml", "IK tool settings file");

   private JButton settingsButton = new JButton("Settings >");
   private JButton previewButton = new JButton("Preview");
   private JButton okButton = new JButton("OK");

   private Dialog ownerDialog = null;

   class LoadSettingsAction extends AbstractAction {
      public LoadSettingsAction() { super("Load Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilename(settingsFilter);
         if(fileName!=null) ikToolModel.loadSettings(fileName);
      }
   }

   class SaveSettingsAction extends AbstractAction {
      public SaveSettingsAction() { super("Save Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilenameToSave(settingsFilter, true, null);
         if(fileName!=null) ikToolModel.saveSettings(fileName);
      }
   }
   
   /** Creates new form IKToolPanel */
   public IKToolPanel(Model model) throws IOException {
      if(model==null) throw new IOException("IKToolPanel got null model");

      ikToolModel = new IKToolModel(model);
      //ikToolModel.loadSettings("C:\\eran\\dev\\simbios\\opensim\\Trunk\\OpenSim\\Examples\\Gait2354\\subject01_Setup_IK.xml");

      initComponents();

      //---------------------------------------------------------------------
      // Settings menu
      //---------------------------------------------------------------------
      settingsButton.addMouseListener(new MouseAdapter() {
         public void mousePressed(MouseEvent evt) {
            JPopupMenu popup = new JPopupMenu();
            popup.add(new JMenuItem(new LoadSettingsAction()));
            popup.add(new JMenuItem(new SaveSettingsAction()));
            popup.show(evt.getComponent(),evt.getX(),evt.getY());
      }});

      jTabbedPane.addTab("IK Tasks", new IKTaskSetPanel(ikToolModel.getIKCommonModel()));

      markerFileName.setExtensionsAndDescription(".trc", "IK trial marker data");
      coordinateFileName.setExtensionsAndDescription(".mot", "Coordinates of IK trial");
  
      updateModelDataFromModel();
      updateFromModel();

      ikToolModel.addObserver(this);
   }

   public void update(Observable observable, Object obj) {
      System.out.println("UPDATE");
      if(observable == ikToolModel && obj == IKToolModel.Operation.ExecutionStateChanged) {
         // Just need to update the buttons
         updateDialogButtons();
      } else {
         updateFromModel();
      }
   }

   public void updateModelDataFromModel() {
      // Fill in model data -- only needs to be done once in beginning
      Model model = ikToolModel.getModel();
      modelNameTextField.setText(model.getName());
      modelNameTextField.setCaretPosition(0);
      MarkerSet markerSet = model.getDynamicsEngine().getMarkerSet();
      int numMarkers = markerSet.getSize();
      if(numMarkers > 0) markerSetInfoTextField.setText(((Integer)numMarkers).toString()+" markers");
      else markerSetInfoTextField.setText("No markers");
   }

   public void updateFromModel() {
      System.out.println("updateFromModel");
   
      // IK trial name
      trialNameTextField.setText(ikToolModel.getTrialName());

      // Static trial marker data
      markerFileName.setFileName(ikToolModel.getIKCommonModel().getMarkerDataFileName(),false);
      markerFileName.setFileIsValid(ikToolModel.getIKCommonModel().getMarkerDataValid());
      markerDataInfoPanel.update(ikToolModel.getIKCommonModel().getMarkerData());

      // Coordinate data
      coordinateFileName.setFileName(ikToolModel.getIKCommonModel().getCoordinateDataFileName(),false);
      coordinateFileName.setFileIsValid(ikToolModel.getIKCommonModel().getCoordinateDataValid());

      // Time range
      double[] timeRange = ikToolModel.getIKCommonModel().getTimeRange();
      startTime.setText(((Double)timeRange[0]).toString());
      endTime.setText(((Double)timeRange[1]).toString());

      //---------------------------------------------------------------------
      // Dialog buttons
      //---------------------------------------------------------------------
      updateDialogButtons();

      System.out.println("updateFromModel FINISHED");
   }


   //------------------------------------------------------------------------
   // Dialog Operations
   //------------------------------------------------------------------------
   public Object[] getDialogOptions() {
      return new Object[]{settingsButton, previewButton, okButton, DialogDescriptor.CANCEL_OPTION};
   }

   public void setOwner(Dialog dialog) { ownerDialog = dialog; }

   public void updateDialogButtons() {
      previewButton.setEnabled(!ikToolModel.isExecuting() && ikToolModel.isModified() && ikToolModel.isValid());
      okButton.setEnabled(!ikToolModel.isExecuting() && ikToolModel.isValid());
   }

   public void actionPerformed(ActionEvent evt) {
      System.out.println("DIALOG ACTION "+evt);
      if(evt.getActionCommand().equals("Cancel")) {
         ikToolModel.cancel();
         // the owner dialog will automatically handle disposing of the dialog in response to Cancel, since this is a standard option (CANCEL_OPTION)
      } else if(evt.getActionCommand().equals("OK")) {
         ikToolModel.execute();
         ownerDialog.dispose();
      } else if(evt.getActionCommand().equals("Preview")) {
         ikToolModel.execute();
      }
      updateDialogButtons();
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jTabbedPane = new javax.swing.JTabbedPane();
      jPanel1 = new javax.swing.JPanel();
      markerPlacerPanel = new javax.swing.JPanel();
      jLabel8 = new javax.swing.JLabel();
      endTime = new javax.swing.JTextField();
      jLabel9 = new javax.swing.JLabel();
      startTime = new javax.swing.JTextField();
      jLabel12 = new javax.swing.JLabel();
      markerFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      markerDataInfoPanel = new org.opensim.tracking.MarkerDataInfoPanel();
      coordinateFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      jLabel17 = new javax.swing.JLabel();
      trialNameTextField = new javax.swing.JTextField();
      jLabel1 = new javax.swing.JLabel();
      genericModelDataPanel = new javax.swing.JPanel();
      jLabel13 = new javax.swing.JLabel();
      modelNameTextField = new javax.swing.JTextField();
      jLabel16 = new javax.swing.JLabel();
      markerSetInfoTextField = new javax.swing.JTextField();

      markerPlacerPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "IK Trial"));
      jLabel8.setText("Time range");

      endTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      endTime.setMinimumSize(new java.awt.Dimension(1, 20));
      endTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            timeRangeActionPerformed(evt);
         }
      });
      endTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            timeRangeFocusLost(evt);
         }
      });

      jLabel9.setText("and");

      startTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      startTime.setMinimumSize(new java.awt.Dimension(1, 20));
      startTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            timeRangeActionPerformed(evt);
         }
      });
      startTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            timeRangeFocusLost(evt);
         }
      });

      jLabel12.setText("Trial file (.trc)");

      markerFileName.setMinimumSize(new java.awt.Dimension(3, 20));
      markerFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            markerFileNameStateChanged(evt);
         }
      });

      coordinateFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            coordinateFileNameStateChanged(evt);
         }
      });

      jLabel17.setText("Coordinates file");

      trialNameTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            trialNameTextFieldActionPerformed(evt);
         }
      });
      trialNameTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            trialNameTextFieldFocusLost(evt);
         }
      });

      jLabel1.setText("Trial name");

      org.jdesktop.layout.GroupLayout markerPlacerPanelLayout = new org.jdesktop.layout.GroupLayout(markerPlacerPanel);
      markerPlacerPanel.setLayout(markerPlacerPanelLayout);
      markerPlacerPanelLayout.setHorizontalGroup(
         markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, markerPlacerPanelLayout.createSequentialGroup()
            .add(60, 60, 60)
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel17)
               .add(jLabel12)
               .add(jLabel8)
               .add(jLabel1))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(trialNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 322, Short.MAX_VALUE)
               .add(markerFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 322, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, markerPlacerPanelLayout.createSequentialGroup()
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(org.jdesktop.layout.GroupLayout.LEADING, coordinateFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 322, Short.MAX_VALUE)
                     .add(markerPlacerPanelLayout.createSequentialGroup()
                        .add(startTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel9)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(endTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))
            .add(16, 16, 16)
            .add(markerDataInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
      markerPlacerPanelLayout.setVerticalGroup(
         markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(markerPlacerPanelLayout.createSequentialGroup()
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(markerDataInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(trialNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel1))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(markerFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel12))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(startTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel9)
                     .add(endTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel8))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(coordinateFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel17))))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      genericModelDataPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Current Model"));
      jLabel13.setText("Name");

      modelNameTextField.setEditable(false);
      modelNameTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      jLabel16.setText("Marker set");

      markerSetInfoTextField.setEditable(false);
      markerSetInfoTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      org.jdesktop.layout.GroupLayout genericModelDataPanelLayout = new org.jdesktop.layout.GroupLayout(genericModelDataPanel);
      genericModelDataPanel.setLayout(genericModelDataPanelLayout);
      genericModelDataPanelLayout.setHorizontalGroup(
         genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(genericModelDataPanelLayout.createSequentialGroup()
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(genericModelDataPanelLayout.createSequentialGroup()
                  .add(34, 34, 34)
                  .add(jLabel13))
               .add(genericModelDataPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(jLabel16)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(modelNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 235, Short.MAX_VALUE)
               .add(markerSetInfoTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 235, Short.MAX_VALUE))
            .addContainerGap())
      );
      genericModelDataPanelLayout.setVerticalGroup(
         genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(genericModelDataPanelLayout.createSequentialGroup()
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel13)
               .add(modelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(markerSetInfoTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel16))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout jPanel1Layout = new org.jdesktop.layout.GroupLayout(jPanel1);
      jPanel1.setLayout(jPanel1Layout);
      jPanel1Layout.setHorizontalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel1Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, markerPlacerPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(genericModelDataPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap())
      );
      jPanel1Layout.setVerticalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel1Layout.createSequentialGroup()
            .addContainerGap()
            .add(genericModelDataPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(markerPlacerPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(134, Short.MAX_VALUE))
      );
      jTabbedPane.addTab("IK Tool Settings", jPanel1);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(jTabbedPane)
            .addContainerGap())
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(jTabbedPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 397, Short.MAX_VALUE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   private void trialNameTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_trialNameTextFieldFocusLost
      if(!evt.isTemporary()) ikToolModel.setTrialName(trialNameTextField.getText());
   }//GEN-LAST:event_trialNameTextFieldFocusLost

   private void trialNameTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_trialNameTextFieldActionPerformed
      ikToolModel.setTrialName(trialNameTextField.getText());
   }//GEN-LAST:event_trialNameTextFieldActionPerformed

   private void markerFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_markerFileNameStateChanged
      boolean result = ikToolModel.getIKCommonModel().setMarkerDataFileName(markerFileName.getFileName());
      markerFileName.setFileIsValid(result);
   }//GEN-LAST:event_markerFileNameStateChanged

   private void coordinateFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_coordinateFileNameStateChanged
      boolean result = ikToolModel.getIKCommonModel().setCoordinateDataFileName(coordinateFileName.getFileName());
      coordinateFileName.setFileIsValid(result);
   }//GEN-LAST:event_coordinateFileNameStateChanged

   private void timeRangeFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_timeRangeFocusLost
      if(!evt.isTemporary()) timeRangeActionPerformed(null);
   }//GEN-LAST:event_timeRangeFocusLost

   private void timeRangeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_timeRangeActionPerformed
      try {
         double[] range = new double[]{Double.valueOf(startTime.getText()), Double.valueOf(endTime.getText())};
         ikToolModel.getIKCommonModel().setTimeRange(range);
      } catch (Exception ex) {
      }
      // May have clamped, get actual values
      double[] range = ikToolModel.getIKCommonModel().getTimeRange();
      startTime.setText(((Double)range[0]).toString());
      endTime.setText(((Double)range[1]).toString());
   }//GEN-LAST:event_timeRangeActionPerformed
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private org.opensim.swingui.FileTextFieldAndChooser coordinateFileName;
   private javax.swing.JTextField endTime;
   private javax.swing.JPanel genericModelDataPanel;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel12;
   private javax.swing.JLabel jLabel13;
   private javax.swing.JLabel jLabel16;
   private javax.swing.JLabel jLabel17;
   private javax.swing.JLabel jLabel8;
   private javax.swing.JLabel jLabel9;
   private javax.swing.JPanel jPanel1;
   private javax.swing.JTabbedPane jTabbedPane;
   private org.opensim.tracking.MarkerDataInfoPanel markerDataInfoPanel;
   private org.opensim.swingui.FileTextFieldAndChooser markerFileName;
   private javax.swing.JPanel markerPlacerPanel;
   private javax.swing.JTextField markerSetInfoTextField;
   private javax.swing.JTextField modelNameTextField;
   private javax.swing.JTextField startTime;
   private javax.swing.JTextField trialNameTextField;
   // End of variables declaration//GEN-END:variables
   
}
