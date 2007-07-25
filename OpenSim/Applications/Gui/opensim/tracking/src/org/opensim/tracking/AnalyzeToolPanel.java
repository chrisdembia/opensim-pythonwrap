/*
 * AnalyzeToolPanel.java
 *
 * Created on July 24, 2007, 7:37 PM
 */

package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JPanel;
import org.opensim.modeling.Model;

/**
 *
 * @author  erang
 */
public class AnalyzeToolPanel extends BaseToolPanel implements Observer {
   
   AnalyzeToolModel toolModel = null;
   ActuatorsAndExternalLoadsPanel actuatorsAndExternalLoadsPanel = null;

   /** Creates new form AnalyzeToolPanel */
   public AnalyzeToolPanel(Model model) throws IOException {
      toolModel = new AnalyzeToolModel(model);

      initComponents();

      resultsDirectory.setIncludeOpenButton(true);

      actuatorsAndExternalLoadsPanel = new ActuatorsAndExternalLoadsPanel();
      jTabbedPane1.addTab("Actuators and External Loads", actuatorsAndExternalLoadsPanel);

      setSettingsFileDescription("Analyze tool settings file");
      updateFromModel();
      toolModel.addObserver(this);
   }

   public void update(Observable observable, Object obj) {
      if(observable == toolModel && obj == AbstractToolModel.Operation.ExecutionStateChanged)
         updateDialogButtons();
      else
         updateFromModel(); 
   }

   private void setEnabled(JPanel panel, boolean enabled) {
      for(Component comp : panel.getComponents()) {
         comp.setEnabled(enabled);
         if(comp instanceof JPanel) setEnabled((JPanel)comp, enabled);
      }
   }

   public void updateFromModel() {
      // Start off with everything enabled
      setEnabled(mainSettingsPanel, true);
      setEnabled(analysesPanel, true);

      modelName.setText(toolModel.getOriginalModel().getName());
      
      // Input
      if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.Motion) buttonGroup1.setSelected(motionRadioButton.getModel(),true);
      else if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.States) buttonGroup1.setSelected(statesRadioButton.getModel(),true);
      else if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.Coordinates) buttonGroup1.setSelected(coordinatesRadioButton.getModel(),true);

      if(!buttonGroup1.isSelected(motionRadioButton.getModel())) motionsComboBox.setEnabled(false);
      if(!buttonGroup1.isSelected(statesRadioButton.getModel())) statesFileName.setEnabled(false);
      if(!buttonGroup1.isSelected(coordinatesRadioButton.getModel())) {
         coordinatesFileName.setEnabled(false);
         filterCoordinatesCheckBox.setEnabled(false);
         cutoffFrequency.setEnabled(false);
         speedsCheckBox.setEnabled(false);
         speedsFileName.setEnabled(false);
      }

      statesFileName.setFileName(toolModel.getStatesFileName(),false);
      coordinatesFileName.setFileName(toolModel.getCoordinatesFileName(),false);

      // Filter
      filterCoordinatesCheckBox.setSelected(toolModel.getFilterCoordinates());
      if(!filterCoordinatesCheckBox.isSelected()) cutoffFrequency.setEnabled(false);
      cutoffFrequency.setText(((Double)toolModel.getLowpassCutoffFrequency()).toString());

      // Speeds
      speedsCheckBox.setSelected(toolModel.getLoadSpeeds());
      if(!speedsCheckBox.isSelected()) speedsFileName.setEnabled(false);
      speedsFileName.setFileName(toolModel.getSpeedsFileName(),false);

      // Analysis set summary
      String str = "";
      for(int i=0; i<toolModel.getAnalysisSet().getSize(); i++)
         str += (i>0 ? ", " : "") + toolModel.getAnalysisSet().get(i).getType();

      // Time
      initialTime.setText(((Double)toolModel.getInitialTime()).toString());
      finalTime.setText(((Double)toolModel.getFinalTime()).toString());

      // Output
      outputPrecision.setText(((Integer)toolModel.getOutputPrecision()).toString());
      resultsDirectory.setFileName(toolModel.getResultsDirectory(),false);

      // Actuators & external loads
      actuatorsAndExternalLoadsPanel.updatePanel(toolModel, toolModel.getOriginalModel());
   }

   public void updateDialogButtons() {
      updateApplyButton(!toolModel.isExecuting() && toolModel.isModified() && toolModel.isValid());
   }

   //------------------------------------------------------------------------
   // Overrides from BaseToolPanel
   //------------------------------------------------------------------------

   public void loadSettings(String fileName) { toolModel.loadSettings(fileName); }
   public void saveSettings(String fileName) { toolModel.saveSettings(fileName); }

   public void pressedCancel() {
      toolModel.cancel();
   }

   public void pressedClose() {
   }

   public void pressedApply() {
      toolModel.execute();
      updateDialogButtons();
   }

   //------------------------------------------------------------------------
   // Utility to initialize the analyze tool dialog to process inverse dynamics
   //------------------------------------------------------------------------
   public static AnalyzeToolPanel createInverseDynamicsPanel(Model model) throws IOException {
      return new AnalyzeToolPanel(model);
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      buttonGroup1 = new javax.swing.ButtonGroup();
      jTabbedPane1 = new javax.swing.JTabbedPane();
      mainSettingsPanel = new javax.swing.JPanel();
      jPanel2 = new javax.swing.JPanel();
      motionRadioButton = new javax.swing.JRadioButton();
      motionsComboBox = new javax.swing.JComboBox();
      statesRadioButton = new javax.swing.JRadioButton();
      coordinatesRadioButton = new javax.swing.JRadioButton();
      statesFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      coordinatesFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      speedsCheckBox = new javax.swing.JCheckBox();
      speedsFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      filterCoordinatesCheckBox = new javax.swing.JCheckBox();
      cutoffFrequency = new javax.swing.JTextField();
      jLabel1 = new javax.swing.JLabel();
      jPanel4 = new javax.swing.JPanel();
      jLabel10 = new javax.swing.JLabel();
      outputPrecision = new javax.swing.JTextField();
      jLabel11 = new javax.swing.JLabel();
      resultsDirectory = new org.opensim.swingui.FileTextFieldAndChooser();
      jPanel3 = new javax.swing.JPanel();
      jLabel4 = new javax.swing.JLabel();
      initialTime = new javax.swing.JTextField();
      jLabel5 = new javax.swing.JLabel();
      finalTime = new javax.swing.JTextField();
      jLabel3 = new javax.swing.JLabel();
      activeAnalyses = new javax.swing.JTextField();
      editAnalysesButton = new javax.swing.JButton();
      jPanel1 = new javax.swing.JPanel();
      jLabel2 = new javax.swing.JLabel();
      modelName = new javax.swing.JTextField();
      analysesPanel = new javax.swing.JPanel();

      jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Input"));
      buttonGroup1.add(motionRadioButton);
      motionRadioButton.setText("Motion");
      motionRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      motionRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      motionsComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));

      buttonGroup1.add(statesRadioButton);
      statesRadioButton.setText("States file");
      statesRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      statesRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      buttonGroup1.add(coordinatesRadioButton);
      coordinatesRadioButton.setText("Coordinates file");
      coordinatesRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      coordinatesRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      speedsCheckBox.setText("Speeds file");
      speedsCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      speedsCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

      filterCoordinatesCheckBox.setText("Filter coordinates");
      filterCoordinatesCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      filterCoordinatesCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

      cutoffFrequency.setText("jTextField1");

      jLabel1.setText("Hz");

      org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
      jPanel2.setLayout(jPanel2Layout);
      jPanel2Layout.setHorizontalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel2Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(motionRadioButton)
               .add(statesRadioButton)
               .add(coordinatesRadioButton))
            .add(11, 11, 11)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                  .add(coordinatesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 226, Short.MAX_VALUE)
                  .add(statesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                  .add(motionsComboBox, 0, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
               .add(jPanel2Layout.createSequentialGroup()
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(filterCoordinatesCheckBox)
                     .add(speedsCheckBox))
                  .add(6, 6, 6)
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(jPanel2Layout.createSequentialGroup()
                        .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 186, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel1))
                     .add(speedsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 216, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))))
            .addContainerGap(147, Short.MAX_VALUE))
      );
      jPanel2Layout.setVerticalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel2Layout.createSequentialGroup()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, motionsComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, motionRadioButton))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, statesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, statesRadioButton))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, coordinatesRadioButton)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, coordinatesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(filterCoordinatesCheckBox)
               .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel1))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(speedsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(speedsCheckBox))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      jPanel4.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Output"));
      jLabel10.setText("Output precision");

      outputPrecision.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      outputPrecision.setText("jTextField1");
      outputPrecision.setMinimumSize(new java.awt.Dimension(40, 20));

      jLabel11.setText("Results directory");

      org.jdesktop.layout.GroupLayout jPanel4Layout = new org.jdesktop.layout.GroupLayout(jPanel4);
      jPanel4.setLayout(jPanel4Layout);
      jPanel4Layout.setHorizontalGroup(
         jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel4Layout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel11)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(resultsDirectory, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 343, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel10)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(0, 0, 0))
      );
      jPanel4Layout.setVerticalGroup(
         jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel4Layout.createSequentialGroup()
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                  .add(jLabel10)
                  .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
               .add(resultsDirectory, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel11))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      jPanel3.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Analyze"));
      jLabel4.setText("Initial time");

      initialTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      initialTime.setText("jTextField2");

      jLabel5.setText("Final time");

      finalTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      finalTime.setText("jTextField1");

      jLabel3.setText("Active analyses");

      activeAnalyses.setEditable(false);
      activeAnalyses.setText("jTextField2");

      editAnalysesButton.setText("Edit");
      editAnalysesButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            editAnalysesButtonActionPerformed(evt);
         }
      });

      org.jdesktop.layout.GroupLayout jPanel3Layout = new org.jdesktop.layout.GroupLayout(jPanel3);
      jPanel3.setLayout(jPanel3Layout);
      jPanel3Layout.setHorizontalGroup(
         jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel3Layout.createSequentialGroup()
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel3Layout.createSequentialGroup()
                  .addContainerGap()
                  .add(jLabel3)
                  .add(7, 7, 7)
                  .add(activeAnalyses, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 387, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(6, 6, 6)
                  .add(editAnalysesButton))
               .add(jPanel3Layout.createSequentialGroup()
                  .add(36, 36, 36)
                  .add(jLabel4)
                  .add(9, 9, 9)
                  .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(36, 36, 36)
                  .add(jLabel5)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(finalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
            .addContainerGap(48, Short.MAX_VALUE))
      );
      jPanel3Layout.setVerticalGroup(
         jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel3Layout.createSequentialGroup()
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel3)
               .add(activeAnalyses, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(editAnalysesButton))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 20, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel4)
               .add(finalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel5))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Current Model"));
      jLabel2.setText("Name");

      modelName.setEditable(false);
      modelName.setText("jTextField1");

      org.jdesktop.layout.GroupLayout jPanel1Layout = new org.jdesktop.layout.GroupLayout(jPanel1);
      jPanel1.setLayout(jPanel1Layout);
      jPanel1Layout.setHorizontalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel1Layout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel2)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(modelName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 293, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(250, Short.MAX_VALUE))
      );
      jPanel1Layout.setVerticalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel1Layout.createSequentialGroup()
            .add(6, 6, 6)
            .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel2)
               .add(modelName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout mainSettingsPanelLayout = new org.jdesktop.layout.GroupLayout(mainSettingsPanel);
      mainSettingsPanel.setLayout(mainSettingsPanelLayout);
      mainSettingsPanelLayout.setHorizontalGroup(
         mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(mainSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel4, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addContainerGap())
      );
      mainSettingsPanelLayout.setVerticalGroup(
         mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(mainSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(18, Short.MAX_VALUE))
      );
      jTabbedPane1.addTab("Main Settings", mainSettingsPanel);

      org.jdesktop.layout.GroupLayout analysesPanelLayout = new org.jdesktop.layout.GroupLayout(analysesPanel);
      analysesPanel.setLayout(analysesPanelLayout);
      analysesPanelLayout.setHorizontalGroup(
         analysesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(0, 616, Short.MAX_VALUE)
      );
      analysesPanelLayout.setVerticalGroup(
         analysesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(0, 414, Short.MAX_VALUE)
      );
      jTabbedPane1.addTab("Analyses", analysesPanel);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 621, Short.MAX_VALUE)
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 442, Short.MAX_VALUE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   private void editAnalysesButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editAnalysesButtonActionPerformed
      jTabbedPane1.setSelectedIndex(1);
   }//GEN-LAST:event_editAnalysesButtonActionPerformed
   
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JTextField activeAnalyses;
   private javax.swing.JPanel analysesPanel;
   private javax.swing.ButtonGroup buttonGroup1;
   private org.opensim.swingui.FileTextFieldAndChooser coordinatesFileName;
   private javax.swing.JRadioButton coordinatesRadioButton;
   private javax.swing.JTextField cutoffFrequency;
   private javax.swing.JButton editAnalysesButton;
   private javax.swing.JCheckBox filterCoordinatesCheckBox;
   private javax.swing.JTextField finalTime;
   private javax.swing.JTextField initialTime;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel10;
   private javax.swing.JLabel jLabel11;
   private javax.swing.JLabel jLabel2;
   private javax.swing.JLabel jLabel3;
   private javax.swing.JLabel jLabel4;
   private javax.swing.JLabel jLabel5;
   private javax.swing.JPanel jPanel1;
   private javax.swing.JPanel jPanel2;
   private javax.swing.JPanel jPanel3;
   private javax.swing.JPanel jPanel4;
   private javax.swing.JTabbedPane jTabbedPane1;
   private javax.swing.JPanel mainSettingsPanel;
   private javax.swing.JTextField modelName;
   private javax.swing.JRadioButton motionRadioButton;
   private javax.swing.JComboBox motionsComboBox;
   private javax.swing.JTextField outputPrecision;
   private org.opensim.swingui.FileTextFieldAndChooser resultsDirectory;
   private javax.swing.JCheckBox speedsCheckBox;
   private org.opensim.swingui.FileTextFieldAndChooser speedsFileName;
   private org.opensim.swingui.FileTextFieldAndChooser statesFileName;
   private javax.swing.JRadioButton statesRadioButton;
   // End of variables declaration//GEN-END:variables
   
}
