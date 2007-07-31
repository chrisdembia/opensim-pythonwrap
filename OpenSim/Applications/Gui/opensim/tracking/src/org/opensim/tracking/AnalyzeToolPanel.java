/*
 * AnalyzeToolPanel.java
 *
 * Created on July 24, 2007, 7:37 PM
 */

package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JPanel;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.MotionsDB;

/**
 *
 * @author  erang
 */
public class AnalyzeToolPanel extends BaseToolPanel implements Observer {
  
   private boolean inverseDynamicsMode = false;
   AnalyzeToolModel toolModel = null;
   ActuatorsAndExternalLoadsPanel actuatorsAndExternalLoadsPanel = null;
   AnalysisSetPanel analysisSetPanel = null;
   private boolean internalTrigger = false;

   /** Creates new form AnalyzeToolPanel */
   public AnalyzeToolPanel(Model model, boolean inverseDynamicsMode) throws IOException {
      this.inverseDynamicsMode = inverseDynamicsMode;

      toolModel = new AnalyzeToolModel(model, inverseDynamicsMode);

      initComponents();

      // File chooser settings
      outputDirectory.setIncludeOpenButton(true);
      outputDirectory.setDirectoriesOnly(true);

      String keyword = inverseDynamicsMode ? "inverse dynamics" : "analysis";
      statesFileName.setExtensionsAndDescription(".sto", "States data for "+keyword);
      coordinatesFileName.setExtensionsAndDescription(".mot,.sto", "Motion data for "+keyword);
      speedsFileName.setExtensionsAndDescription(".mot,.sto", "Speeds data for "+keyword);

      if(inverseDynamicsMode) setSettingsFileDescription("Inverse dynamics tool settings files");
      else setSettingsFileDescription("Analyze tool settings file");

      if(inverseDynamicsMode) {
         actuatorsAndExternalLoadsPanel = new ActuatorsAndExternalLoadsPanel(toolModel, toolModel.getOriginalModel(), false);
         jTabbedPane1.addTab("External Loads", actuatorsAndExternalLoadsPanel);
      } else {
         actuatorsAndExternalLoadsPanel = new ActuatorsAndExternalLoadsPanel(toolModel, toolModel.getOriginalModel(), true);
         jTabbedPane1.addTab("Actuators and External Loads", actuatorsAndExternalLoadsPanel);
      }

      if(!inverseDynamicsMode) {
         analysisSetPanel = new AnalysisSetPanel(toolModel);
         jTabbedPane1.addTab("Analyses", analysisSetPanel);
      }

      // Disable some things if we're just doing inverse dynamics
      if(inverseDynamicsMode) {
         jLabel3.setVisible(false);
         activeAnalyses.setVisible(false);
         editAnalysesButton.setVisible(false);

         // Change border
         jPanel3.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Time"));
      }

      updateStaticFields();
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

   public void updateStaticFields() {
      modelName.setText(toolModel.getOriginalModel().getName());
   }

   public void updateFromModel() {
      internalTrigger = true;

      // Start off with everything enabled
      setEnabled(mainSettingsPanel, true);

      //if(!toolModel.needPseudoStates()) pseudoStatesFileName.setEnabled(false);
      
      // Input
      if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.Motion) buttonGroup1.setSelected(motionRadioButton.getModel(),true);
      else if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.States) buttonGroup1.setSelected(statesRadioButton.getModel(),true);
      else if(toolModel.getInputSource()==AnalyzeToolModel.InputSource.Coordinates) buttonGroup1.setSelected(coordinatesRadioButton.getModel(),true);
      else buttonGroup1.setSelected(unspecifiedRadioButton.getModel(),true);

      // Motion selections
      ArrayList<Storage> motions = MotionsDB.getInstance().getModelMotions(toolModel.getOriginalModel());
      motionsComboBox.removeAllItems();
      if(motions!=null) for(int i=0; i<motions.size(); i++) motionsComboBox.addItem(motions.get(i).getName());

      if(motions==null || motions.size()==0) motionRadioButton.setEnabled(false);
      else if(toolModel.getInputMotion()==null) motionsComboBox.setSelectedIndex(-1);
      else motionsComboBox.setSelectedIndex(motions.indexOf(toolModel.getInputMotion()));

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
      if(!filterCoordinatesCheckBox.isSelected()) {
         cutoffFrequency.setText("");
         cutoffFrequency.setEnabled(false);
      } else {
         cutoffFrequency.setText(((Double)toolModel.getLowpassCutoffFrequency()).toString());
      }

      // Speeds
      speedsCheckBox.setSelected(toolModel.getLoadSpeeds());
      if(!speedsCheckBox.isSelected()) speedsFileName.setEnabled(false);
      speedsFileName.setFileName(toolModel.getSpeedsFileName(),false);

      // Analysis set summary
      String str = "";
      for(int i=0; i<toolModel.getAnalysisSet().getSize(); i++)
         str += (i>0 ? ", " : "") + toolModel.getAnalysisSet().get(i).getType();
      activeAnalyses.setText(str);

      // Time
      initialTime.setText(((Double)toolModel.getInitialTime()).toString());
      finalTime.setText(((Double)toolModel.getFinalTime()).toString());

      // Output
      outputName.setText(toolModel.getOutputPrefix());
      outputDirectory.setFileName(toolModel.getResultsDirectory(),false);
      outputPrecision.setText(((Integer)toolModel.getOutputPrecision()).toString());

      // Actuators & external loads
      actuatorsAndExternalLoadsPanel.updatePanel();

      updateDialogButtons();

      internalTrigger = false;
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
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      buttonGroup1 = new javax.swing.ButtonGroup();
      unspecifiedRadioButton = new javax.swing.JRadioButton();
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
      outputDirectory = new org.opensim.swingui.FileTextFieldAndChooser();
      jLabel6 = new javax.swing.JLabel();
      outputName = new javax.swing.JTextField();
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

      buttonGroup1.add(unspecifiedRadioButton);
      unspecifiedRadioButton.setText("jRadioButton1");
      unspecifiedRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      unspecifiedRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Input"));
      buttonGroup1.add(motionRadioButton);
      motionRadioButton.setText("Loaded motion");
      motionRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      motionRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      motionRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            inputSourceRadioButtonActionPerformed(evt);
         }
      });

      motionsComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
      motionsComboBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            motionsComboBoxActionPerformed(evt);
         }
      });

      buttonGroup1.add(statesRadioButton);
      statesRadioButton.setText("States file");
      statesRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      statesRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      statesRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            inputSourceRadioButtonActionPerformed(evt);
         }
      });

      buttonGroup1.add(coordinatesRadioButton);
      coordinatesRadioButton.setText("Motion file");
      coordinatesRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      coordinatesRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
      coordinatesRadioButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            inputSourceRadioButtonActionPerformed(evt);
         }
      });

      statesFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            statesFileNameStateChanged(evt);
         }
      });

      coordinatesFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            coordinatesFileNameStateChanged(evt);
         }
      });

      speedsCheckBox.setText("Speeds file");
      speedsCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      speedsCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      speedsCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            speedsCheckBoxActionPerformed(evt);
         }
      });

      speedsFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            speedsFileNameStateChanged(evt);
         }
      });

      filterCoordinatesCheckBox.setText("Filter coordinates");
      filterCoordinatesCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      filterCoordinatesCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      filterCoordinatesCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            filterCoordinatesCheckBoxActionPerformed(evt);
         }
      });

      cutoffFrequency.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      cutoffFrequency.setText("jTextField1");
      cutoffFrequency.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            cutoffFrequencyActionPerformed(evt);
         }
      });
      cutoffFrequency.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            cutoffFrequencyFocusLost(evt);
         }
      });

      jLabel1.setText("Hz");

      org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
      jPanel2.setLayout(jPanel2Layout);
      jPanel2Layout.setHorizontalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel2Layout.createSequentialGroup()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel2Layout.createSequentialGroup()
                  .addContainerGap()
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(coordinatesRadioButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 112, Short.MAX_VALUE)
                     .add(statesRadioButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 112, Short.MAX_VALUE)
                     .add(motionRadioButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 112, Short.MAX_VALUE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(motionsComboBox, 0, 299, Short.MAX_VALUE)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, coordinatesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 299, Short.MAX_VALUE)
                     .add(statesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED))
               .add(jPanel2Layout.createSequentialGroup()
                  .add(114, 114, 114)
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(filterCoordinatesCheckBox)
                     .add(speedsCheckBox))
                  .add(6, 6, 6)
                  .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(jPanel2Layout.createSequentialGroup()
                        .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 186, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel1)
                        .add(14, 14, 14))
                     .add(jPanel2Layout.createSequentialGroup()
                        .add(speedsFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 206, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))))
            .add(33, 33, 33))
      );
      jPanel2Layout.setVerticalGroup(
         jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel2Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(motionRadioButton)
               .add(motionsComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(statesRadioButton)
               .add(statesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(coordinatesRadioButton)
               .add(coordinatesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(filterCoordinatesCheckBox)
               .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel1))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(speedsCheckBox)
               .add(speedsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .add(51, 51, 51))
      );

      jPanel4.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Output"));
      jLabel10.setText("Precision");

      outputPrecision.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      outputPrecision.setText("jTextField1");
      outputPrecision.setMinimumSize(new java.awt.Dimension(40, 20));
      outputPrecision.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            outputPrecisionActionPerformed(evt);
         }
      });
      outputPrecision.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            outputPrecisionFocusLost(evt);
         }
      });

      jLabel11.setText("Directory");

      outputDirectory.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            outputDirectoryStateChanged(evt);
         }
      });

      jLabel6.setText("Prefix");

      outputName.setText("jTextField1");
      outputName.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            outputNameActionPerformed(evt);
         }
      });
      outputName.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            outputNameFocusLost(evt);
         }
      });

      org.jdesktop.layout.GroupLayout jPanel4Layout = new org.jdesktop.layout.GroupLayout(jPanel4);
      jPanel4.setLayout(jPanel4Layout);
      jPanel4Layout.setHorizontalGroup(
         jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel4Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                  .add(jLabel6)
                  .add(jLabel11))
               .add(jLabel10))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(outputName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 402, Short.MAX_VALUE)
               .add(outputDirectory, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 402, Short.MAX_VALUE))
            .addContainerGap())
      );
      jPanel4Layout.setVerticalGroup(
         jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel4Layout.createSequentialGroup()
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel6)
               .add(outputName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel11)
               .add(outputDirectory, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel10)
               .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      jPanel3.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Analyze"));
      jLabel4.setText("Initial time");

      initialTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      initialTime.setText("jTextField2");
      initialTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            initialTimeActionPerformed(evt);
         }
      });
      initialTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            initialTimeFocusLost(evt);
         }
      });

      jLabel5.setText("Final time");

      finalTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      finalTime.setText("jTextField1");
      finalTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            finalTimeActionPerformed(evt);
         }
      });
      finalTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            finalTimeFocusLost(evt);
         }
      });

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
                  .add(jLabel3))
               .add(jPanel3Layout.createSequentialGroup()
                  .add(36, 36, 36)
                  .add(jLabel4)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel3Layout.createSequentialGroup()
                  .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(47, 47, 47)
                  .add(jLabel5)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(finalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
               .add(jPanel3Layout.createSequentialGroup()
                  .add(activeAnalyses, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 314, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(editAnalysesButton)))
            .addContainerGap())
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
               .add(jLabel4)
               .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
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
            .add(modelName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 419, Short.MAX_VALUE)
            .addContainerGap())
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
            .add(mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(jPanel1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(jPanel3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(jPanel4, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .add(12, 12, 12))
      );
      mainSettingsPanelLayout.setVerticalGroup(
         mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(mainSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 167, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPanel4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );
      jTabbedPane1.addTab("Main Settings", mainSettingsPanel);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 509, Short.MAX_VALUE)
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 493, Short.MAX_VALUE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   //------------------------------------------------------------------------
   // Input settings
   //------------------------------------------------------------------------

   private void inputSourceRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_inputSourceRadioButtonActionPerformed
      if(motionRadioButton.isSelected()) toolModel.setInputSource(AnalyzeToolModel.InputSource.Motion);
      else if(statesRadioButton.isSelected()) toolModel.setInputSource(AnalyzeToolModel.InputSource.States);
      else if(coordinatesRadioButton.isSelected()) toolModel.setInputSource(AnalyzeToolModel.InputSource.Coordinates);
      else toolModel.setInputSource(AnalyzeToolModel.InputSource.Unspecified);
   }//GEN-LAST:event_inputSourceRadioButtonActionPerformed

   private void motionsComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_motionsComboBoxActionPerformed
      if(internalTrigger) return;
      int index = motionsComboBox.getSelectedIndex();
      ArrayList<Storage> motions = MotionsDB.getInstance().getModelMotions(toolModel.getOriginalModel());
      if(motions!=null && 0<=index && index<motions.size()) toolModel.setInputMotion(motions.get(index));
      else toolModel.setInputMotion(null);
   }//GEN-LAST:event_motionsComboBoxActionPerformed

   private void coordinatesFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_coordinatesFileNameStateChanged
      toolModel.setCoordinatesFileName(coordinatesFileName.getFileName());
   }//GEN-LAST:event_coordinatesFileNameStateChanged

   private void statesFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_statesFileNameStateChanged
      toolModel.setStatesFileName(statesFileName.getFileName());
   }//GEN-LAST:event_statesFileNameStateChanged

   private void speedsCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_speedsCheckBoxActionPerformed
      toolModel.setLoadSpeeds(speedsCheckBox.isSelected());
   }//GEN-LAST:event_speedsCheckBoxActionPerformed

   private void speedsFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_speedsFileNameStateChanged
      toolModel.setSpeedsFileName(speedsFileName.getFileName());
   }//GEN-LAST:event_speedsFileNameStateChanged

   private void filterCoordinatesCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_filterCoordinatesCheckBoxActionPerformed
      toolModel.setFilterCoordinates(filterCoordinatesCheckBox.isSelected());
   }//GEN-LAST:event_filterCoordinatesCheckBoxActionPerformed

   private void cutoffFrequencyFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_cutoffFrequencyFocusLost
      if(!evt.isTemporary()) cutoffFrequencyActionPerformed(null);
   }//GEN-LAST:event_cutoffFrequencyFocusLost

   private void cutoffFrequencyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cutoffFrequencyActionPerformed
      try {
         toolModel.setLowpassCutoffFrequency(Double.valueOf(cutoffFrequency.getText()));
      } finally {
         cutoffFrequency.setText(((Double)toolModel.getLowpassCutoffFrequency()).toString());
      }
   }//GEN-LAST:event_cutoffFrequencyActionPerformed

   //------------------------------------------------------------------------
   // Analyze section
   //------------------------------------------------------------------------

   private void editAnalysesButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editAnalysesButtonActionPerformed
      jTabbedPane1.setSelectedComponent(analysisSetPanel);
   }//GEN-LAST:event_editAnalysesButtonActionPerformed

   private void initialTimeFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_initialTimeFocusLost
      if(!evt.isTemporary()) initialTimeActionPerformed(null);
   }//GEN-LAST:event_initialTimeFocusLost

   private void initialTimeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_initialTimeActionPerformed
      try {
         toolModel.setInitialTime(Double.valueOf(initialTime.getText()));
      } finally {
         initialTime.setText(((Double)toolModel.getInitialTime()).toString());
      }
   }//GEN-LAST:event_initialTimeActionPerformed

   private void finalTimeFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_finalTimeFocusLost
      if(!evt.isTemporary()) finalTimeActionPerformed(null);
   }//GEN-LAST:event_finalTimeFocusLost

   private void finalTimeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_finalTimeActionPerformed
      try {
         toolModel.setFinalTime(Double.valueOf(finalTime.getText()));
      } finally {
         finalTime.setText(((Double)toolModel.getFinalTime()).toString());
      }
   }//GEN-LAST:event_finalTimeActionPerformed

   //------------------------------------------------------------------------
   // Output settings
   //------------------------------------------------------------------------

   private void outputDirectoryStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_outputDirectoryStateChanged
      toolModel.setResultsDirectory(outputDirectory.getFileName());
   }//GEN-LAST:event_outputDirectoryStateChanged

   private void outputPrecisionFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_outputPrecisionFocusLost
      if(!evt.isTemporary()) outputPrecisionActionPerformed(null);
   }//GEN-LAST:event_outputPrecisionFocusLost

   private void outputPrecisionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_outputPrecisionActionPerformed
      try {
         toolModel.setOutputPrecision(Integer.valueOf(outputPrecision.getText()));
      } finally {
         outputPrecision.setText(((Integer)toolModel.getOutputPrecision()).toString());
      }
   }//GEN-LAST:event_outputPrecisionActionPerformed

   private void outputNameFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_outputNameFocusLost
      if(!evt.isTemporary()) outputNameActionPerformed(null);
   }//GEN-LAST:event_outputNameFocusLost

   private void outputNameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_outputNameActionPerformed
      toolModel.setOutputPrefix(outputName.getText());
   }//GEN-LAST:event_outputNameActionPerformed

   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JTextField activeAnalyses;
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
   private javax.swing.JLabel jLabel6;
   private javax.swing.JPanel jPanel1;
   private javax.swing.JPanel jPanel2;
   private javax.swing.JPanel jPanel3;
   private javax.swing.JPanel jPanel4;
   private javax.swing.JTabbedPane jTabbedPane1;
   private javax.swing.JPanel mainSettingsPanel;
   private javax.swing.JTextField modelName;
   private javax.swing.JRadioButton motionRadioButton;
   private javax.swing.JComboBox motionsComboBox;
   private org.opensim.swingui.FileTextFieldAndChooser outputDirectory;
   private javax.swing.JTextField outputName;
   private javax.swing.JTextField outputPrecision;
   private javax.swing.JCheckBox speedsCheckBox;
   private org.opensim.swingui.FileTextFieldAndChooser speedsFileName;
   private org.opensim.swingui.FileTextFieldAndChooser statesFileName;
   private javax.swing.JRadioButton statesRadioButton;
   private javax.swing.JRadioButton unspecifiedRadioButton;
   // End of variables declaration//GEN-END:variables
   
}
