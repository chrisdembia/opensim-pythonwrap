/*
 * AnalyzeAndForwardToolPanel.java
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
import org.jdesktop.layout.GroupLayout;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.MotionsDB;

/**
 *
 * @author  erang
 */
public class AnalyzeAndForwardToolPanel extends BaseToolPanel implements Observer {

   public enum Mode { ForwardDynamics, InverseDynamics, Analyze };
   private Mode mode;
   String modeName;
  
   AbstractToolModelWithExternalLoads toolModel = null;
   ActuatorsAndExternalLoadsPanel actuatorsAndExternalLoadsPanel = null;
   AnalysisSetPanel analysisSetPanel = null;

   private boolean internalTrigger = false;

   /** Creates new form AnalyzeAndForwardToolPanel */
   public AnalyzeAndForwardToolPanel(Model model, Mode mode) throws IOException {
      this.mode = mode;

      switch(mode) {
         case ForwardDynamics: modeName = "forward dynamics tool"; toolModel = new ForwardToolModel(model); break;
         case InverseDynamics: modeName = "inverse dynamics tool"; toolModel = new AnalyzeToolModel(model, true); break;
         case Analyze: modeName = "analyze tool"; toolModel = new AnalyzeToolModel(model, false); break;
      }

      initComponents();

      // File chooser settings
      outputDirectory.setIncludeOpenButton(true);
      outputDirectory.setDirectoriesOnly(true);

      setSettingsFileDescription("Settings file for "+modeName);

      if(mode==Mode.InverseDynamics || mode==Mode.Analyze) {
         forwardInputPanel.setVisible(false);
         if(mode==Mode.InverseDynamics) activeAnalysesPanel.setVisible(false);
         // Set file filters for analyze tool / inverse dynamics tool inputs
         statesFileName.setExtensionsAndDescription(".sto", "States data for "+modeName);
         coordinatesFileName.setExtensionsAndDescription(".mot,.sto", "Motion data for "+modeName);
         speedsFileName.setExtensionsAndDescription(".mot,.sto", "Speeds data for "+modeName);
      } else {
         analyzeInputPanel.setVisible(false);
         activeAnalysesPanel.setVisible(false);
         // Set file filters for forward tool inputs
         controlsFileName.setExtensionsAndDescription(".xml", "Controls input data for forward dynamics tool");
         initialStatesFileName.setExtensionsAndDescription(".sto", "States data for forward dynamics tool");
      }

      // Actuators & External Loads tab
      actuatorsAndExternalLoadsPanel = new ActuatorsAndExternalLoadsPanel(toolModel, toolModel.getOriginalModel(), mode!=Mode.InverseDynamics);
      jTabbedPane1.addTab((mode==Mode.InverseDynamics) ? "External Loads" : "Actuators and External Loads", actuatorsAndExternalLoadsPanel);

      // Analysis Set tab
      if(mode==Mode.Analyze) {
         analysisSetPanel = new AnalysisSetPanel(toolModel);
         jTabbedPane1.addTab("Analyses", analysisSetPanel);
      }

      // Integrator settings for forward dynamics
      if(mode==Mode.ForwardDynamics) {
         jTabbedPane1.addTab("Integrator Settings", advancedSettingsPanel);
      }

      // Re-layout panels after we've removed various parts...
      ((GroupLayout)mainSettingsPanel.getLayout()).layoutContainer(mainSettingsPanel);

      updateStaticFields();
      updateFromModel();

      toolModel.addObserver(this);
   }

   private AnalyzeToolModel analyzeToolModel() { return (AnalyzeToolModel)toolModel; }
   private ForwardToolModel forwardToolModel() { return (ForwardToolModel)toolModel; } 

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
      setEnabled(advancedSettingsPanel, true);

      if(mode==Mode.InverseDynamics || mode==Mode.Analyze) 
         updateAnalyzeToolSpecificFields(analyzeToolModel());
      else
         updateForwardToolSpecificFields(forwardToolModel());

      // Analysis set summary
      String str = "";
      for(int i=0; i<toolModel.getAnalysisSet().getSize(); i++)
         str += (i>0 ? ", " : "") + toolModel.getAnalysisSet().get(i).getType();
      activeAnalyses.setText(str);

      // Time
      if(toolModel.getAvailableTimeRangeValid()) {
         availableInitialTime.setText(((Double)toolModel.getAvailableInitialTime()).toString());
         availableFinalTime.setText(((Double)toolModel.getAvailableFinalTime()).toString());
      } else {
         availableInitialTime.setText("");
         availableFinalTime.setText("");
      }
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

   //---------------------------------------------------------------------
   // Fields for analyze tool / inverse dynamics tool
   //---------------------------------------------------------------------
   public void updateAnalyzeToolSpecificFields(AnalyzeToolModel toolModel) {
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
   }

   //---------------------------------------------------------------------
   // Fields for forward dynamics tool
   //---------------------------------------------------------------------
   public void updateForwardToolSpecificFields(ForwardToolModel toolModel) {
      controlsFileName.setFileName(toolModel.getControlsFileName(),false);
      initialStatesFileName.setFileName(toolModel.getInitialStatesFileName(),false);

      // Integrator settings
      useSpecifiedDt.setSelected(toolModel.getUseSpecifiedDt());
      maximumNumberOfSteps.setText(((Integer)toolModel.getMaximumNumberOfSteps()).toString());
      maxDT.setText(((Double)toolModel.getMaxDT()).toString());
      errorTolerance.setText(((Double)toolModel.getErrorTolerance()).toString());
      fineTolerance.setText(((Double)toolModel.getFineTolerance()).toString());
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
      advancedSettingsPanel = new javax.swing.JPanel();
      integratorSettingsPanel = new javax.swing.JPanel();
      jLabel13 = new javax.swing.JLabel();
      jLabel14 = new javax.swing.JLabel();
      jLabel15 = new javax.swing.JLabel();
      useSpecifiedDt = new javax.swing.JCheckBox();
      jLabel16 = new javax.swing.JLabel();
      maximumNumberOfSteps = new javax.swing.JTextField();
      jLabel17 = new javax.swing.JLabel();
      maxDT = new javax.swing.JTextField();
      errorTolerance = new javax.swing.JTextField();
      jLabel18 = new javax.swing.JLabel();
      fineTolerance = new javax.swing.JTextField();
      buttonGroup1 = new javax.swing.ButtonGroup();
      unspecifiedRadioButton = new javax.swing.JRadioButton();
      jTabbedPane1 = new javax.swing.JTabbedPane();
      mainSettingsPanel = new javax.swing.JPanel();
      analyzeInputPanel = new javax.swing.JPanel();
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
      outputPanel = new javax.swing.JPanel();
      jLabel10 = new javax.swing.JLabel();
      outputPrecision = new javax.swing.JTextField();
      jLabel11 = new javax.swing.JLabel();
      outputDirectory = new org.opensim.swingui.FileTextFieldAndChooser();
      jLabel6 = new javax.swing.JLabel();
      outputName = new javax.swing.JTextField();
      timePanel = new javax.swing.JPanel();
      jLabel4 = new javax.swing.JLabel();
      initialTime = new javax.swing.JTextField();
      jLabel5 = new javax.swing.JLabel();
      finalTime = new javax.swing.JTextField();
      jLabel7 = new javax.swing.JLabel();
      availableInitialTime = new javax.swing.JTextField();
      availableFinalTime = new javax.swing.JTextField();
      jLabel8 = new javax.swing.JLabel();
      modelInfoPanel = new javax.swing.JPanel();
      jLabel2 = new javax.swing.JLabel();
      modelName = new javax.swing.JTextField();
      activeAnalysesPanel = new javax.swing.JPanel();
      jLabel3 = new javax.swing.JLabel();
      activeAnalyses = new javax.swing.JTextField();
      editAnalysesButton = new javax.swing.JButton();
      forwardInputPanel = new javax.swing.JPanel();
      jLabel9 = new javax.swing.JLabel();
      controlsFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      jLabel12 = new javax.swing.JLabel();
      initialStatesFileName = new org.opensim.swingui.FileTextFieldAndChooser();

      integratorSettingsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Integrator Settings"));
      jLabel13.setText("Integrator steps:");

      jLabel14.setText("Integrator tolerances:");

      jLabel15.setText("Error tolerance");

      useSpecifiedDt.setText("Use time steps from states file");
      useSpecifiedDt.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      useSpecifiedDt.setMargin(new java.awt.Insets(0, 0, 0, 0));
      useSpecifiedDt.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            useSpecifiedDtActionPerformed(evt);
         }
      });

      jLabel16.setText("Maximum number");

      maximumNumberOfSteps.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      maximumNumberOfSteps.setText("jTextField5");
      maximumNumberOfSteps.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            maximumNumberOfStepsActionPerformed(evt);
         }
      });
      maximumNumberOfSteps.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            maximumNumberOfStepsFocusLost(evt);
         }
      });

      jLabel17.setText("Maximum  size");

      maxDT.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      maxDT.setText("jTextField6");
      maxDT.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            maxDTActionPerformed(evt);
         }
      });
      maxDT.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            maxDTFocusLost(evt);
         }
      });

      errorTolerance.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      errorTolerance.setText("jTextField7");
      errorTolerance.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            errorToleranceActionPerformed(evt);
         }
      });
      errorTolerance.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            errorToleranceFocusLost(evt);
         }
      });

      jLabel18.setText("Fine tolerance");

      fineTolerance.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      fineTolerance.setText("jTextField8");
      fineTolerance.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            fineToleranceActionPerformed(evt);
         }
      });
      fineTolerance.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            fineToleranceFocusLost(evt);
         }
      });

      org.jdesktop.layout.GroupLayout integratorSettingsPanelLayout = new org.jdesktop.layout.GroupLayout(integratorSettingsPanel);
      integratorSettingsPanel.setLayout(integratorSettingsPanelLayout);
      integratorSettingsPanelLayout.setHorizontalGroup(
         integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(integratorSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(useSpecifiedDt)
               .add(integratorSettingsPanelLayout.createSequentialGroup()
                  .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel13)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel14))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel15)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel16))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(errorTolerance, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 104, Short.MAX_VALUE)
                     .add(maximumNumberOfSteps, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 104, Short.MAX_VALUE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel18)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel17))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(maxDT, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 104, Short.MAX_VALUE)
                     .add(fineTolerance, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 104, Short.MAX_VALUE))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))
            .add(0, 0, 0))
      );
      integratorSettingsPanelLayout.setVerticalGroup(
         integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(integratorSettingsPanelLayout.createSequentialGroup()
            .add(useSpecifiedDt)
            .add(5, 5, 5)
            .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel13)
               .add(jLabel17)
               .add(maxDT, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel16)
               .add(maximumNumberOfSteps, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(integratorSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel14)
               .add(jLabel18)
               .add(fineTolerance, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel15)
               .add(errorTolerance, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout advancedSettingsPanelLayout = new org.jdesktop.layout.GroupLayout(advancedSettingsPanel);
      advancedSettingsPanel.setLayout(advancedSettingsPanelLayout);
      advancedSettingsPanelLayout.setHorizontalGroup(
         advancedSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(advancedSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(integratorSettingsPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addContainerGap())
      );
      advancedSettingsPanelLayout.setVerticalGroup(
         advancedSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(advancedSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(integratorSettingsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );
      buttonGroup1.add(unspecifiedRadioButton);
      unspecifiedRadioButton.setText("jRadioButton1");
      unspecifiedRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      unspecifiedRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

      analyzeInputPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Input"));
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

      org.jdesktop.layout.GroupLayout analyzeInputPanelLayout = new org.jdesktop.layout.GroupLayout(analyzeInputPanel);
      analyzeInputPanel.setLayout(analyzeInputPanelLayout);
      analyzeInputPanelLayout.setHorizontalGroup(
         analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(analyzeInputPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(motionRadioButton)
               .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
                  .add(org.jdesktop.layout.GroupLayout.LEADING, statesRadioButton, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                  .add(org.jdesktop.layout.GroupLayout.LEADING, coordinatesRadioButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 89, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, statesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 363, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, motionsComboBox, 0, 363, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, coordinatesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 363, Short.MAX_VALUE)
               .add(analyzeInputPanelLayout.createSequentialGroup()
                  .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(filterCoordinatesCheckBox)
                     .add(speedsCheckBox))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(analyzeInputPanelLayout.createSequentialGroup()
                        .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 256, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED))
                     .add(speedsFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 256, Short.MAX_VALUE))))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel1)
            .addContainerGap())
      );

      analyzeInputPanelLayout.linkSize(new java.awt.Component[] {filterCoordinatesCheckBox, speedsCheckBox}, org.jdesktop.layout.GroupLayout.HORIZONTAL);

      analyzeInputPanelLayout.setVerticalGroup(
         analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(analyzeInputPanelLayout.createSequentialGroup()
            .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
               .add(analyzeInputPanelLayout.createSequentialGroup()
                  .add(5, 5, 5)
                  .add(motionRadioButton)
                  .add(11, 11, 11)
                  .add(statesRadioButton)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                  .add(coordinatesRadioButton))
               .add(analyzeInputPanelLayout.createSequentialGroup()
                  .add(motionsComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(statesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(coordinatesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(filterCoordinatesCheckBox)
               .add(jLabel1)
               .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(analyzeInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(speedsCheckBox)
               .add(speedsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      outputPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Output"));
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

      org.jdesktop.layout.GroupLayout outputPanelLayout = new org.jdesktop.layout.GroupLayout(outputPanel);
      outputPanel.setLayout(outputPanelLayout);
      outputPanelLayout.setHorizontalGroup(
         outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(outputPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                  .add(jLabel6)
                  .add(jLabel11))
               .add(jLabel10))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(outputName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 426, Short.MAX_VALUE)
               .add(outputDirectory, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 426, Short.MAX_VALUE))
            .addContainerGap())
      );
      outputPanelLayout.setVerticalGroup(
         outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(outputPanelLayout.createSequentialGroup()
            .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel6)
               .add(outputName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel11)
               .add(outputDirectory, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(outputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel10)
               .add(outputPrecision, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      timePanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Time"));
      jLabel4.setText("Time range to process");

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

      jLabel5.setText("to");

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

      jLabel7.setText("Available time range from input data");

      availableInitialTime.setEditable(false);
      availableInitialTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      availableInitialTime.setText("jTextField1");

      availableFinalTime.setEditable(false);
      availableFinalTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      availableFinalTime.setText("jTextField2");

      jLabel8.setText("to");

      org.jdesktop.layout.GroupLayout timePanelLayout = new org.jdesktop.layout.GroupLayout(timePanel);
      timePanel.setLayout(timePanelLayout);
      timePanelLayout.setHorizontalGroup(
         timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(timePanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel4)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel7))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(timePanelLayout.createSequentialGroup()
                  .add(availableInitialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jLabel8)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(availableFinalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
               .add(timePanelLayout.createSequentialGroup()
                  .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jLabel5)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(finalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 64, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
            .addContainerGap(160, Short.MAX_VALUE))
      );

      timePanelLayout.linkSize(new java.awt.Component[] {availableFinalTime, availableInitialTime, finalTime, initialTime}, org.jdesktop.layout.GroupLayout.HORIZONTAL);

      timePanelLayout.setVerticalGroup(
         timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(timePanelLayout.createSequentialGroup()
            .add(timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel7)
               .add(availableInitialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel8)
               .add(availableFinalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(timePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel4)
               .add(initialTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel5)
               .add(finalTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      modelInfoPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Current Model"));
      jLabel2.setText("Name");

      modelName.setEditable(false);
      modelName.setText("jTextField1");

      org.jdesktop.layout.GroupLayout modelInfoPanelLayout = new org.jdesktop.layout.GroupLayout(modelInfoPanel);
      modelInfoPanel.setLayout(modelInfoPanelLayout);
      modelInfoPanelLayout.setHorizontalGroup(
         modelInfoPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(modelInfoPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel2)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(modelName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 443, Short.MAX_VALUE)
            .addContainerGap())
      );
      modelInfoPanelLayout.setVerticalGroup(
         modelInfoPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(modelInfoPanelLayout.createSequentialGroup()
            .add(6, 6, 6)
            .add(modelInfoPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel2)
               .add(modelName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      activeAnalysesPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Analysis Set"));
      jLabel3.setText("Active analyses");

      activeAnalyses.setEditable(false);
      activeAnalyses.setText("jTextField2");

      editAnalysesButton.setText("Edit");
      editAnalysesButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            editAnalysesButtonActionPerformed(evt);
         }
      });

      org.jdesktop.layout.GroupLayout activeAnalysesPanelLayout = new org.jdesktop.layout.GroupLayout(activeAnalysesPanel);
      activeAnalysesPanel.setLayout(activeAnalysesPanelLayout);
      activeAnalysesPanelLayout.setHorizontalGroup(
         activeAnalysesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(activeAnalysesPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel3)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(activeAnalyses, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 348, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(editAnalysesButton))
      );
      activeAnalysesPanelLayout.setVerticalGroup(
         activeAnalysesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(activeAnalysesPanelLayout.createSequentialGroup()
            .add(activeAnalysesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel3)
               .add(editAnalysesButton)
               .add(activeAnalyses, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      forwardInputPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Input"));
      jLabel9.setText("Controls");

      controlsFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            controlsFileNameStateChanged(evt);
         }
      });

      jLabel12.setText("Initial states");

      initialStatesFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            initialStatesFileNameStateChanged(evt);
         }
      });

      org.jdesktop.layout.GroupLayout forwardInputPanelLayout = new org.jdesktop.layout.GroupLayout(forwardInputPanel);
      forwardInputPanel.setLayout(forwardInputPanelLayout);
      forwardInputPanelLayout.setHorizontalGroup(
         forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(forwardInputPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(forwardInputPanelLayout.createSequentialGroup()
                  .add(19, 19, 19)
                  .add(jLabel9))
               .add(jLabel12))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(controlsFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 411, Short.MAX_VALUE)
               .add(initialStatesFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 411, Short.MAX_VALUE))
            .addContainerGap())
      );
      forwardInputPanelLayout.setVerticalGroup(
         forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(forwardInputPanelLayout.createSequentialGroup()
            .add(forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel9)
               .add(controlsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(forwardInputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel12)
               .add(initialStatesFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout mainSettingsPanelLayout = new org.jdesktop.layout.GroupLayout(mainSettingsPanel);
      mainSettingsPanel.setLayout(mainSettingsPanelLayout);
      mainSettingsPanelLayout.setHorizontalGroup(
         mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(mainSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(analyzeInputPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(modelInfoPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(forwardInputPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, timePanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, activeAnalysesPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, outputPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addContainerGap())
      );
      mainSettingsPanelLayout.setVerticalGroup(
         mainSettingsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(mainSettingsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(modelInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(analyzeInputPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(forwardInputPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(timePanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(activeAnalysesPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(outputPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
      jTabbedPane1.addTab("Main Settings", mainSettingsPanel);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 531, Short.MAX_VALUE)
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jTabbedPane1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );
   }// </editor-fold>//GEN-END:initComponents

   //------------------------------------------------------------------------
   // Forward tool input settings
   //------------------------------------------------------------------------

   private void initialStatesFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_initialStatesFileNameStateChanged
      forwardToolModel().setInitialStatesFileName(initialStatesFileName.getFileName());
   }//GEN-LAST:event_initialStatesFileNameStateChanged

   private void controlsFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_controlsFileNameStateChanged
      forwardToolModel().setControlsFileName(controlsFileName.getFileName());
   }//GEN-LAST:event_controlsFileNameStateChanged

   //------------------------------------------------------------------------
   // Integrator settings (forward tool)
   //------------------------------------------------------------------------

   private void fineToleranceFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_fineToleranceFocusLost
      if(!evt.isTemporary()) fineToleranceActionPerformed(null);
   }//GEN-LAST:event_fineToleranceFocusLost

   private void fineToleranceActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_fineToleranceActionPerformed
      try {
         toolModel.setFineTolerance(Double.valueOf(fineTolerance.getText()));
      } finally {
         fineTolerance.setText(((Double)toolModel.getFineTolerance()).toString());
      }
   }//GEN-LAST:event_fineToleranceActionPerformed

   private void maxDTFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_maxDTFocusLost
      if(!evt.isTemporary()) maxDTActionPerformed(null);
   }//GEN-LAST:event_maxDTFocusLost

   private void maxDTActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_maxDTActionPerformed
      try {
         toolModel.setMaxDT(Double.valueOf(maxDT.getText()));
      } finally {
         maxDT.setText(((Double)toolModel.getMaxDT()).toString());
      }
   }//GEN-LAST:event_maxDTActionPerformed

   private void errorToleranceFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_errorToleranceFocusLost
      if(!evt.isTemporary()) errorToleranceActionPerformed(null);
   }//GEN-LAST:event_errorToleranceFocusLost

   private void errorToleranceActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_errorToleranceActionPerformed
      try {
         toolModel.setErrorTolerance(Double.valueOf(errorTolerance.getText()));
      } finally {
         errorTolerance.setText(((Double)toolModel.getErrorTolerance()).toString());
      }
   }//GEN-LAST:event_errorToleranceActionPerformed

   private void maximumNumberOfStepsFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_maximumNumberOfStepsFocusLost
      if(!evt.isTemporary()) maximumNumberOfStepsActionPerformed(null);
   }//GEN-LAST:event_maximumNumberOfStepsFocusLost

   private void maximumNumberOfStepsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_maximumNumberOfStepsActionPerformed
      try {
         toolModel.setMaximumNumberOfSteps(Integer.valueOf(maximumNumberOfSteps.getText()));
      } finally {
         maximumNumberOfSteps.setText(((Integer)toolModel.getMaximumNumberOfSteps()).toString());
      }
   }//GEN-LAST:event_maximumNumberOfStepsActionPerformed

   private void useSpecifiedDtActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_useSpecifiedDtActionPerformed
      forwardToolModel().setUseSpecifiedDt(useSpecifiedDt.isSelected());
   }//GEN-LAST:event_useSpecifiedDtActionPerformed

   //------------------------------------------------------------------------
   // Analyze tool input settings
   //------------------------------------------------------------------------

   private void inputSourceRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_inputSourceRadioButtonActionPerformed
      if(motionRadioButton.isSelected()) analyzeToolModel().setInputSource(AnalyzeToolModel.InputSource.Motion);
      else if(statesRadioButton.isSelected()) analyzeToolModel().setInputSource(AnalyzeToolModel.InputSource.States);
      else if(coordinatesRadioButton.isSelected()) analyzeToolModel().setInputSource(AnalyzeToolModel.InputSource.Coordinates);
      else analyzeToolModel().setInputSource(AnalyzeToolModel.InputSource.Unspecified);
   }//GEN-LAST:event_inputSourceRadioButtonActionPerformed

   private void motionsComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_motionsComboBoxActionPerformed
      if(internalTrigger) return;
      int index = motionsComboBox.getSelectedIndex();
      ArrayList<Storage> motions = MotionsDB.getInstance().getModelMotions(toolModel.getOriginalModel());
      if(motions!=null && 0<=index && index<motions.size()) analyzeToolModel().setInputMotion(motions.get(index));
      else analyzeToolModel().setInputMotion(null);
   }//GEN-LAST:event_motionsComboBoxActionPerformed

   private void coordinatesFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_coordinatesFileNameStateChanged
      analyzeToolModel().setCoordinatesFileName(coordinatesFileName.getFileName());
   }//GEN-LAST:event_coordinatesFileNameStateChanged

   private void statesFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_statesFileNameStateChanged
      analyzeToolModel().setStatesFileName(statesFileName.getFileName());
   }//GEN-LAST:event_statesFileNameStateChanged

   private void speedsCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_speedsCheckBoxActionPerformed
      analyzeToolModel().setLoadSpeeds(speedsCheckBox.isSelected());
   }//GEN-LAST:event_speedsCheckBoxActionPerformed

   private void speedsFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_speedsFileNameStateChanged
      analyzeToolModel().setSpeedsFileName(speedsFileName.getFileName());
   }//GEN-LAST:event_speedsFileNameStateChanged

   private void filterCoordinatesCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_filterCoordinatesCheckBoxActionPerformed
      analyzeToolModel().setFilterCoordinates(filterCoordinatesCheckBox.isSelected());
   }//GEN-LAST:event_filterCoordinatesCheckBoxActionPerformed

   private void cutoffFrequencyFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_cutoffFrequencyFocusLost
      if(!evt.isTemporary()) cutoffFrequencyActionPerformed(null);
   }//GEN-LAST:event_cutoffFrequencyFocusLost

   private void cutoffFrequencyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cutoffFrequencyActionPerformed
      try {
         analyzeToolModel().setLowpassCutoffFrequency(Double.valueOf(cutoffFrequency.getText()));
      } finally {
         cutoffFrequency.setText(((Double)analyzeToolModel().getLowpassCutoffFrequency()).toString());
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
   private javax.swing.JPanel activeAnalysesPanel;
   private javax.swing.JPanel advancedSettingsPanel;
   private javax.swing.JPanel analyzeInputPanel;
   private javax.swing.JTextField availableFinalTime;
   private javax.swing.JTextField availableInitialTime;
   private javax.swing.ButtonGroup buttonGroup1;
   private org.opensim.swingui.FileTextFieldAndChooser controlsFileName;
   private org.opensim.swingui.FileTextFieldAndChooser coordinatesFileName;
   private javax.swing.JRadioButton coordinatesRadioButton;
   private javax.swing.JTextField cutoffFrequency;
   private javax.swing.JButton editAnalysesButton;
   private javax.swing.JTextField errorTolerance;
   private javax.swing.JCheckBox filterCoordinatesCheckBox;
   private javax.swing.JTextField finalTime;
   private javax.swing.JTextField fineTolerance;
   private javax.swing.JPanel forwardInputPanel;
   private org.opensim.swingui.FileTextFieldAndChooser initialStatesFileName;
   private javax.swing.JTextField initialTime;
   private javax.swing.JPanel integratorSettingsPanel;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel10;
   private javax.swing.JLabel jLabel11;
   private javax.swing.JLabel jLabel12;
   private javax.swing.JLabel jLabel13;
   private javax.swing.JLabel jLabel14;
   private javax.swing.JLabel jLabel15;
   private javax.swing.JLabel jLabel16;
   private javax.swing.JLabel jLabel17;
   private javax.swing.JLabel jLabel18;
   private javax.swing.JLabel jLabel2;
   private javax.swing.JLabel jLabel3;
   private javax.swing.JLabel jLabel4;
   private javax.swing.JLabel jLabel5;
   private javax.swing.JLabel jLabel6;
   private javax.swing.JLabel jLabel7;
   private javax.swing.JLabel jLabel8;
   private javax.swing.JLabel jLabel9;
   private javax.swing.JTabbedPane jTabbedPane1;
   private javax.swing.JPanel mainSettingsPanel;
   private javax.swing.JTextField maxDT;
   private javax.swing.JTextField maximumNumberOfSteps;
   private javax.swing.JPanel modelInfoPanel;
   private javax.swing.JTextField modelName;
   private javax.swing.JRadioButton motionRadioButton;
   private javax.swing.JComboBox motionsComboBox;
   private org.opensim.swingui.FileTextFieldAndChooser outputDirectory;
   private javax.swing.JTextField outputName;
   private javax.swing.JPanel outputPanel;
   private javax.swing.JTextField outputPrecision;
   private javax.swing.JCheckBox speedsCheckBox;
   private org.opensim.swingui.FileTextFieldAndChooser speedsFileName;
   private org.opensim.swingui.FileTextFieldAndChooser statesFileName;
   private javax.swing.JRadioButton statesRadioButton;
   private javax.swing.JPanel timePanel;
   private javax.swing.JRadioButton unspecifiedRadioButton;
   private javax.swing.JCheckBox useSpecifiedDt;
   // End of variables declaration//GEN-END:variables
   
}
