/*
 * ScaleToolPanel.java
 *
 * Created on July 3, 2007, 4:51 PM
 */

package org.opensim.tracking;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.Model;
import org.opensim.swingui.ComponentTitledBorder;
import org.opensim.utils.FileUtils;

public class ScaleToolPanel extends javax.swing.JPanel implements ActionListener, Observer {
  
   private ScaleToolModel scaleToolModel = null;

   private FileFilter settingsFilter = FileUtils.getFileFilter(".xml", "Scale tool settings file");

   private JButton settingsButton = new JButton("Settings >");
   private JButton previewButton = new JButton("Preview");
   private JButton okButton = new JButton("OK");
   private JCheckBox modelScalerPanelCheckBox = new JCheckBox(new EnableModelScalerAction());
   private JCheckBox markerPlacerPanelCheckBox = new JCheckBox(new EnableMarkerPlacerAction());

   private Dialog ownerDialog = null;
   private MeasurementSetPanel measurementSetPanel;
   private Dialog measurementSetDialog;

   class EnableModelScalerAction extends AbstractAction {
      public EnableModelScalerAction() { super("Scale Model"); }
      public void actionPerformed(ActionEvent evt) { scaleToolModel.setModelScalerEnabled(((JCheckBox)evt.getSource()).isSelected()); }
   }

   class EnableMarkerPlacerAction extends AbstractAction {
      public EnableMarkerPlacerAction() { super("Adjust Model Markers"); }
      public void actionPerformed(ActionEvent evt) { 
         scaleToolModel.setMarkerPlacerEnabled(((JCheckBox)evt.getSource()).isSelected()); 
      }
   }

   class LoadSettingsAction extends AbstractAction {
      public LoadSettingsAction() { super("Load Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilename(settingsFilter);
         if(fileName!=null) scaleToolModel.loadSettings(fileName);
      }
   }

   class SaveSettingsAction extends AbstractAction {
      public SaveSettingsAction() { super("Save Settings..."); }
      public void actionPerformed(ActionEvent evt) {
         String fileName = FileUtils.getInstance().browseForFilenameToSave(settingsFilter, true, null);
         if(fileName!=null) scaleToolModel.saveSettings(fileName);
      }
   }

   /** Creates new form ScaleToolPanel */
   public ScaleToolPanel(Model model) throws IOException {
      if(model==null) {
         model = new Model("C:\\gait2354.osim");
         model.setup();
      }

      scaleToolModel = new ScaleToolModel(model);
      scaleToolModel.loadSettings("C:\\eran\\dev\\simbios\\opensim\\Trunk\\OpenSim\\Examples\\Gait2354\\subject01_Setup_Scale.xml");

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

      //---------------------------------------------------------------------
      // Measurement set editor dialog
      //---------------------------------------------------------------------
      measurementSetPanel = new MeasurementSetPanel(scaleToolModel);
      DialogDescriptor dlg = new DialogDescriptor(measurementSetPanel, "Measurement Set");
      dlg.setModal(false);
      dlg.setOptions(new Object[]{DialogDescriptor.OK_OPTION});
      measurementSetDialog = DialogDisplayer.getDefault().createDialog(dlg);

      jTabbedPane.addTab("Scale Factors", new ScaleFactorsPanel(scaleToolModel, measurementSetDialog));
      jTabbedPane.addTab("IK Tasks", new IKTaskSetPanel(scaleToolModel.getIKCommonModel()));      
      
      markerSetFileName.setExtensionsAndDescription(".xml", "MarkerSet XML file");
      measurementTrialFileName.setExtensionsAndDescription(".trc", "Measurement trial marker data");
      staticTrialFileName.setExtensionsAndDescription(".trc", "Static trial marker data");
      coordinateFileName.setExtensionsAndDescription(".mot", "Coordinates of static trial");

      // Add checkbox titled borders to model scaler and marker placer panels
      // TODO: ComponentTitledBorder example called setFocusPainted(false) on the checkboxes... do we need to do that?
      modelScalerPanelCheckBox.setForeground(new Color(0,70,213));
      markerPlacerPanelCheckBox.setForeground(new Color(0,70,213));
      modelScalerPanel.setBorder(new ComponentTitledBorder(modelScalerPanelCheckBox, modelScalerPanel, BorderFactory.createEtchedBorder()));
      markerPlacerPanel.setBorder(new ComponentTitledBorder(markerPlacerPanelCheckBox, markerPlacerPanel, BorderFactory.createEtchedBorder()));

      updateUnscaledModelDataFromModel();
      updateFromModel();

      scaleToolModel.addObserver(this);
   }

   public void update(Observable observable, Object obj) {
      System.out.println("UPDATE");
      updateFromModel();
   }

   public void updateUnscaledModelDataFromModel() {
      // Fill in unscaled model data -- only needs to be done once in beginning
      Model unscaledModel = scaleToolModel.getUnscaledModel();
      unscaledModelNameTextField.setText(unscaledModel.getName());
      unscaledModelNameTextField.setCaretPosition(0);
      unscaledModelMassTextField.setText(((Double)scaleToolModel.getModelMass(unscaledModel)).toString());
      unscaledModelMassTextField.setScrollOffset(0);
      // Assumes user has not had a chance to modify the marker set of the unscaled model yet...
      MarkerSet markerSet = unscaledModel.getDynamicsEngine().getMarkerSet();
      int numMarkers = markerSet.getSize();
      if(numMarkers > 0) unscaledMarkerSetInfoTextField.setText(((Integer)numMarkers).toString()+" markers");
      else unscaledMarkerSetInfoTextField.setText("No markers");
   }

   public void updateFromModel() {
      System.out.println("updateFromModel");

      //---------------------------------------------------------------------
      // Subject data
      //---------------------------------------------------------------------
      // Model name, mass
      modelNameTextField.setText(scaleToolModel.getName());
      modelMassTextField.setText(((Double)scaleToolModel.getMass()).toString());

      // Marker set
      Model unscaledModel = scaleToolModel.getUnscaledModel();
      MarkerSet markerSet = unscaledModel.getDynamicsEngine().getMarkerSet();
      int numMarkers = markerSet.getSize();
      if(numMarkers > 0) markerSetInfoTextField.setText(((Integer)numMarkers).toString()+" markers");
      else markerSetInfoTextField.setText("No markers!");
      if(scaleToolModel.getUseExtraMarkerSet()) {
         loadMarkerSetCheckBox.setSelected(true);
         markerSetFileName.setEnabled(true);
         markerSetFileName.setFileName(scaleToolModel.getExtraMarkerSetFileName(),false);
         markerSetFileName.setFileIsValid(scaleToolModel.getExtraMarkerSetValid());
      } else {
         loadMarkerSetCheckBox.setSelected(false);
         markerSetFileName.setEnabled(false);
      }

      //---------------------------------------------------------------------
      // Model scaler
      //---------------------------------------------------------------------
      // Model scaler enabled
      boolean enabled = scaleToolModel.getModelScalerEnabled();
      modelScalerPanelCheckBox.setSelected(enabled);
      for(Component comp : modelScalerPanel.getComponents()) comp.setEnabled(enabled);

      // Measurement trial file and time range
      if(scaleToolModel.getMeasurementTrialFileName() != null) {
         //measurementTrialFileName.setEnabled(true);
         measurementTrialFileName.setFileName(scaleToolModel.getMeasurementTrialFileName(),false);
         measurementTrialFileName.setFileIsValid(scaleToolModel.getMeasurementTrialValid());
      } else {
         measurementTrialFileName.setFileName("",false);
      }
      measurementTrialInfoPanel.update(scaleToolModel.getMeasurementTrial());
      double[] timeRange = scaleToolModel.getMeasurementTrialTimeRange();
      measurementTrialStartTime.setText(((Double)timeRange[0]).toString());
      measurementTrialEndTime.setText(((Double)timeRange[1]).toString());
      if(enabled) {
         measurementTrialStartTime.setEnabled(scaleToolModel.getMeasurementTrialValid());
         measurementTrialEndTime.setEnabled(scaleToolModel.getMeasurementTrialValid());
      }

      //---------------------------------------------------------------------
      // Marker placer
      //---------------------------------------------------------------------
      enabled = scaleToolModel.getMarkerPlacerEnabled();
      markerPlacerPanelCheckBox.setSelected(enabled);
      for(Component comp : markerPlacerPanel.getComponents()) comp.setEnabled(enabled);

      // Static trial marker data
      staticTrialFileName.setFileName(scaleToolModel.getIKCommonModel().getMarkerDataFileName(),false);
      staticTrialFileName.setFileIsValid(scaleToolModel.getIKCommonModel().getMarkerDataValid());
      staticTrialInfoPanel.update(scaleToolModel.getIKCommonModel().getMarkerData());

      // Coordinate data
      coordinateFileName.setFileName(scaleToolModel.getIKCommonModel().getCoordinateDataFileName(),false);
      coordinateFileName.setFileIsValid(scaleToolModel.getIKCommonModel().getCoordinateDataValid());

      // Time range
      timeRange = scaleToolModel.getIKCommonModel().getTimeRange();
      staticTrialStartTime.setText(((Double)timeRange[0]).toString());
      staticTrialEndTime.setText(((Double)timeRange[1]).toString());
      if(enabled) updateStaticTrialFieldsEnabled();

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
      previewButton.setEnabled(scaleToolModel.isModified() && scaleToolModel.isValid());
      okButton.setEnabled(scaleToolModel.isValid());
   }

   public void actionPerformed(ActionEvent evt) {
      System.out.println("DIALOG ACTION "+evt);
      if(evt.getActionCommand().equals("Cancel")) {
         scaleToolModel.cancel();
         measurementSetDialog.dispose(); 
         // the owner dialog will automatically handle disposing of the dialog in response to Cancel, since this is a standard option (CANCEL_OPTION)
      } else if(evt.getActionCommand().equals("OK")) {
         scaleToolModel.execute();
         ownerDialog.dispose();
         measurementSetDialog.dispose(); 
      } else if(evt.getActionCommand().equals("Preview")) {
         scaleToolModel.execute();
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
      staticTrialEndTime = new javax.swing.JTextField();
      jLabel9 = new javax.swing.JLabel();
      staticTrialStartTime = new javax.swing.JTextField();
      jLabel10 = new javax.swing.JLabel();
      copyMeasurementTrialToStaticTrial = new javax.swing.JCheckBox();
      jLabel12 = new javax.swing.JLabel();
      staticTrialFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      staticTrialInfoPanel = new org.opensim.tracking.MarkerDataInfoPanel();
      coordinateFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      jLabel17 = new javax.swing.JLabel();
      modelScalerPanel = new javax.swing.JPanel();
      jLabel3 = new javax.swing.JLabel();
      jLabel5 = new javax.swing.JLabel();
      measurementTrialStartTime = new javax.swing.JTextField();
      jLabel6 = new javax.swing.JLabel();
      measurementTrialEndTime = new javax.swing.JTextField();
      preserveMassDistributionCheckBox = new javax.swing.JCheckBox();
      jLabel11 = new javax.swing.JLabel();
      measurementTrialFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      measurementTrialInfoPanel = new org.opensim.tracking.MarkerDataInfoPanel();
      subjectDataPanel = new javax.swing.JPanel();
      jLabel4 = new javax.swing.JLabel();
      jLabel2 = new javax.swing.JLabel();
      jLabel1 = new javax.swing.JLabel();
      modelNameTextField = new javax.swing.JTextField();
      loadMarkerSetCheckBox = new javax.swing.JCheckBox();
      jLabel7 = new javax.swing.JLabel();
      markerSetInfoTextField = new javax.swing.JTextField();
      modelMassTextField = new javax.swing.JTextField();
      markerSetFileName = new org.opensim.swingui.FileTextFieldAndChooser();
      genericModelDataPanel = new javax.swing.JPanel();
      jLabel13 = new javax.swing.JLabel();
      unscaledModelNameTextField = new javax.swing.JTextField();
      unscaledModelMassTextField = new javax.swing.JTextField();
      jLabel14 = new javax.swing.JLabel();
      jLabel15 = new javax.swing.JLabel();
      jLabel16 = new javax.swing.JLabel();
      unscaledMarkerSetInfoTextField = new javax.swing.JTextField();

      markerPlacerPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Marker Placement Settings"));
      jLabel8.setText("Average markers between times");

      staticTrialEndTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      staticTrialEndTime.setMinimumSize(new java.awt.Dimension(1, 20));
      staticTrialEndTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            staticTrialTimeRangeActionPerformed(evt);
         }
      });
      staticTrialEndTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            staticTrialTimeRangeFocusLost(evt);
         }
      });

      jLabel9.setText("and");

      staticTrialStartTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      staticTrialStartTime.setMinimumSize(new java.awt.Dimension(1, 20));
      staticTrialStartTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            staticTrialTimeRangeActionPerformed(evt);
         }
      });
      staticTrialStartTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            staticTrialTimeRangeFocusLost(evt);
         }
      });

      jLabel10.setFont(new java.awt.Font("Tahoma", 1, 11));
      jLabel10.setText("Static pose trial:");

      copyMeasurementTrialToStaticTrial.setText("Same as measurement-based scaling trial above");
      copyMeasurementTrialToStaticTrial.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      copyMeasurementTrialToStaticTrial.setMargin(new java.awt.Insets(0, 0, 0, 0));
      copyMeasurementTrialToStaticTrial.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            copyMeasurementTrialToStaticTrialActionPerformed(evt);
         }
      });

      jLabel12.setText("Trial file (.trc)");

      staticTrialFileName.setMinimumSize(new java.awt.Dimension(3, 20));
      staticTrialFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            staticTrialFileNameStateChanged(evt);
         }
      });

      coordinateFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            coordinateFileNameStateChanged(evt);
         }
      });

      jLabel17.setText("Coordinates file");

      org.jdesktop.layout.GroupLayout markerPlacerPanelLayout = new org.jdesktop.layout.GroupLayout(markerPlacerPanel);
      markerPlacerPanel.setLayout(markerPlacerPanelLayout);
      markerPlacerPanelLayout.setHorizontalGroup(
         markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(markerPlacerPanelLayout.createSequentialGroup()
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .add(69, 69, 69)
                  .add(jLabel10))
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .add(90, 90, 90)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(jLabel17)
                     .add(jLabel12)))
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(jLabel8)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(copyMeasurementTrialToStaticTrial)
               .add(staticTrialFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 317, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.TRAILING, markerPlacerPanelLayout.createSequentialGroup()
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(org.jdesktop.layout.GroupLayout.LEADING, coordinateFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 307, Short.MAX_VALUE)
                     .add(markerPlacerPanelLayout.createSequentialGroup()
                        .add(staticTrialStartTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel9)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(staticTrialEndTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))
            .add(16, 16, 16)
            .add(staticTrialInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
      );
      markerPlacerPanelLayout.setVerticalGroup(
         markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(markerPlacerPanelLayout.createSequentialGroup()
            .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(jLabel10)
                     .add(copyMeasurementTrialToStaticTrial))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(staticTrialFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel12))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(staticTrialStartTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel9)
                     .add(staticTrialEndTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel8))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(markerPlacerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(coordinateFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jLabel17)))
               .add(markerPlacerPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(staticTrialInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
            .addContainerGap(30, Short.MAX_VALUE))
      );

      modelScalerPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Scale Settings"));
      jLabel3.setText("Trial file (.trc)");

      jLabel5.setText("Average measurements between times");

      measurementTrialStartTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      measurementTrialStartTime.setMinimumSize(new java.awt.Dimension(1, 20));
      measurementTrialStartTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            measurementSetTimeRangeActionPerformed(evt);
         }
      });
      measurementTrialStartTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            measurementSetTimeRangeFocusLost(evt);
         }
      });

      jLabel6.setText("and");

      measurementTrialEndTime.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      measurementTrialEndTime.setMinimumSize(new java.awt.Dimension(1, 20));
      measurementTrialEndTime.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            measurementSetTimeRangeActionPerformed(evt);
         }
      });
      measurementTrialEndTime.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            measurementSetTimeRangeFocusLost(evt);
         }
      });

      preserveMassDistributionCheckBox.setText("Preserve mass distribution");
      preserveMassDistributionCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      preserveMassDistributionCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      preserveMassDistributionCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            preserveMassDistributionCheckBoxActionPerformed(evt);
         }
      });

      jLabel11.setFont(new java.awt.Font("Tahoma", 1, 11));
      jLabel11.setText("Measurement-based scaling:");

      measurementTrialFileName.setMinimumSize(new java.awt.Dimension(3, 20));
      measurementTrialFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            measurementTrialFileNameStateChanged(evt);
         }
      });

      org.jdesktop.layout.GroupLayout modelScalerPanelLayout = new org.jdesktop.layout.GroupLayout(modelScalerPanel);
      modelScalerPanel.setLayout(modelScalerPanelLayout);
      modelScalerPanelLayout.setHorizontalGroup(
         modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(modelScalerPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(preserveMassDistributionCheckBox)
               .add(modelScalerPanelLayout.createSequentialGroup()
                  .add(24, 24, 24)
                  .add(modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel3)
                     .add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel11))
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(measurementTrialFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 285, Short.MAX_VALUE))
               .add(modelScalerPanelLayout.createSequentialGroup()
                  .add(jLabel5)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(measurementTrialStartTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 125, Short.MAX_VALUE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jLabel6)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(measurementTrialEndTime, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 134, Short.MAX_VALUE)))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(measurementTrialInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
      );
      modelScalerPanelLayout.setVerticalGroup(
         modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(modelScalerPanelLayout.createSequentialGroup()
            .add(modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(modelScalerPanelLayout.createSequentialGroup()
                  .add(preserveMassDistributionCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 15, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jLabel11)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(jLabel3))
               .add(measurementTrialFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(modelScalerPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel5)
               .add(measurementTrialStartTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(jLabel6)
               .add(measurementTrialEndTime, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap())
         .add(org.jdesktop.layout.GroupLayout.TRAILING, modelScalerPanelLayout.createSequentialGroup()
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(measurementTrialInfoPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );

      subjectDataPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Subject Data"));
      jLabel4.setText("Model name");

      jLabel2.setText("Weight");

      jLabel1.setText("kg");

      modelNameTextField.setMinimumSize(new java.awt.Dimension(3, 20));
      modelNameTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            modelNameTextFieldActionPerformed(evt);
         }
      });
      modelNameTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            modelNameTextFieldFocusLost(evt);
         }
      });

      loadMarkerSetCheckBox.setText("Add markers from file");
      loadMarkerSetCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      loadMarkerSetCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      loadMarkerSetCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            loadMarkerSetCheckBoxActionPerformed(evt);
         }
      });

      jLabel7.setText("Resulting marker set");

      markerSetInfoTextField.setEditable(false);
      markerSetInfoTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      modelMassTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      modelMassTextField.setMinimumSize(new java.awt.Dimension(3, 20));
      modelMassTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            modelMassTextFieldActionPerformed(evt);
         }
      });
      modelMassTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            modelMassTextFieldFocusLost(evt);
         }
      });

      markerSetFileName.setMinimumSize(new java.awt.Dimension(3, 20));
      markerSetFileName.addChangeListener(new javax.swing.event.ChangeListener() {
         public void stateChanged(javax.swing.event.ChangeEvent evt) {
            markerSetFileNameStateChanged(evt);
         }
      });

      org.jdesktop.layout.GroupLayout subjectDataPanelLayout = new org.jdesktop.layout.GroupLayout(subjectDataPanel);
      subjectDataPanel.setLayout(subjectDataPanelLayout);
      subjectDataPanelLayout.setHorizontalGroup(
         subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(subjectDataPanelLayout.createSequentialGroup()
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(subjectDataPanelLayout.createSequentialGroup()
                  .add(72, 72, 72)
                  .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                     .add(jLabel2)
                     .add(jLabel4)))
               .add(subjectDataPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(subjectDataPanelLayout.createSequentialGroup()
                        .add(17, 17, 17)
                        .add(jLabel7))
                     .add(loadMarkerSetCheckBox))))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(markerSetFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 227, Short.MAX_VALUE)
               .add(modelNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 227, Short.MAX_VALUE)
               .add(modelMassTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 227, Short.MAX_VALUE)
               .add(markerSetInfoTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 227, Short.MAX_VALUE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel1))
      );
      subjectDataPanelLayout.setVerticalGroup(
         subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(subjectDataPanelLayout.createSequentialGroup()
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel4)
               .add(modelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel2)
               .add(jLabel1)
               .add(modelMassTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(loadMarkerSetCheckBox)
               .add(markerSetFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(subjectDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel7, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 17, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(markerSetInfoTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap())
      );

      genericModelDataPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Generic Model Data"));
      jLabel13.setText("Model name");

      unscaledModelNameTextField.setEditable(false);
      unscaledModelNameTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      unscaledModelMassTextField.setEditable(false);
      unscaledModelMassTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      unscaledModelMassTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      jLabel14.setText("Weight");

      jLabel15.setText("kg");

      jLabel16.setText("Marker set");

      unscaledMarkerSetInfoTextField.setEditable(false);
      unscaledMarkerSetInfoTextField.setMinimumSize(new java.awt.Dimension(3, 20));

      org.jdesktop.layout.GroupLayout genericModelDataPanelLayout = new org.jdesktop.layout.GroupLayout(genericModelDataPanel);
      genericModelDataPanel.setLayout(genericModelDataPanelLayout);
      genericModelDataPanelLayout.setHorizontalGroup(
         genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(genericModelDataPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(jLabel13)
               .add(jLabel14)
               .add(jLabel16))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(unscaledMarkerSetInfoTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 193, Short.MAX_VALUE)
               .add(unscaledModelNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 193, Short.MAX_VALUE)
               .add(unscaledModelMassTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 193, Short.MAX_VALUE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel15))
      );
      genericModelDataPanelLayout.setVerticalGroup(
         genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(genericModelDataPanelLayout.createSequentialGroup()
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel13)
               .add(unscaledModelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel14)
               .add(jLabel15)
               .add(unscaledModelMassTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(genericModelDataPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel16)
               .add(unscaledMarkerSetInfoTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(37, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout jPanel1Layout = new org.jdesktop.layout.GroupLayout(jPanel1);
      jPanel1.setLayout(jPanel1Layout);
      jPanel1Layout.setHorizontalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel1Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
               .add(org.jdesktop.layout.GroupLayout.LEADING, markerPlacerPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 684, Short.MAX_VALUE)
               .add(org.jdesktop.layout.GroupLayout.LEADING, modelScalerPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(jPanel1Layout.createSequentialGroup()
                  .add(subjectDataPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(genericModelDataPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
            .addContainerGap())
      );
      jPanel1Layout.setVerticalGroup(
         jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jPanel1Layout.createSequentialGroup()
            .addContainerGap()
            .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(subjectDataPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
               .add(genericModelDataPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(modelScalerPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 118, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(markerPlacerPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
      jTabbedPane.addTab("Scale Tool Settings", jPanel1);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(jTabbedPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 709, Short.MAX_VALUE)
            .addContainerGap())
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(jTabbedPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 464, Short.MAX_VALUE)
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   //------------------------------------------------------------------------
   // Subject data
   //------------------------------------------------------------------------
   private void modelNameTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_modelNameTextFieldFocusLost
      if(!evt.isTemporary()) modelNameTextFieldActionPerformed(null);
   }//GEN-LAST:event_modelNameTextFieldFocusLost

   private void modelNameTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modelNameTextFieldActionPerformed
      scaleToolModel.setName(modelNameTextField.getText());
   }//GEN-LAST:event_modelNameTextFieldActionPerformed
   
   private void modelMassTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_modelMassTextFieldFocusLost
      if(!evt.isTemporary()) modelMassTextFieldActionPerformed(null);
   }//GEN-LAST:event_modelMassTextFieldFocusLost

   private void modelMassTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modelMassTextFieldActionPerformed
      try {
         double value = Double.valueOf(modelMassTextField.getText());
         scaleToolModel.setMass(value);
      } catch (Exception ex) {
         modelMassTextField.setText(((Double)scaleToolModel.getMass()).toString());
      }
   }//GEN-LAST:event_modelMassTextFieldActionPerformed

   private void loadMarkerSetCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_loadMarkerSetCheckBoxActionPerformed
      boolean enabled = ((JCheckBox)evt.getSource()).isSelected();
      markerSetFileName.setEnabled(enabled);
      scaleToolModel.setUseExtraMarkerSet(enabled);
      markerSetFileName.setFileIsValid(scaleToolModel.getExtraMarkerSetValid());
      //boolean result;
      //if(enabled) result = scaleToolModel.setExtraMarkerSetFileName(markerSetFileName.getFileName());
      //else result = scaleToolModel.setExtraMarkerSetFileName(null);
      //markerSetFileName.setFileIsValid(result);
   }//GEN-LAST:event_loadMarkerSetCheckBoxActionPerformed

   private void markerSetFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_markerSetFileNameStateChanged
      boolean result = scaleToolModel.setExtraMarkerSetFileName(markerSetFileName.getFileName());
      markerSetFileName.setFileIsValid(result);
   }//GEN-LAST:event_markerSetFileNameStateChanged

   //------------------------------------------------------------------------
   // ModelScaler data
   //------------------------------------------------------------------------

   private void preserveMassDistributionCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_preserveMassDistributionCheckBoxActionPerformed
      scaleToolModel.setPreserveMassDistribution(((JCheckBox)evt.getSource()).isSelected());
   }//GEN-LAST:event_preserveMassDistributionCheckBoxActionPerformed

   private void measurementTrialFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_measurementTrialFileNameStateChanged
      System.out.println("Setting file name");
      boolean result = scaleToolModel.setMeasurementTrialFileName(measurementTrialFileName.getFileName());
      measurementTrialFileName.setFileIsValid(result);
      copyMeasurementTrialToStaticTrial();
   }//GEN-LAST:event_measurementTrialFileNameStateChanged

   private void measurementSetTimeRangeFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_measurementSetTimeRangeFocusLost
      if(!evt.isTemporary()) measurementSetTimeRangeActionPerformed(null);
   }//GEN-LAST:event_measurementSetTimeRangeFocusLost

   private void measurementSetTimeRangeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_measurementSetTimeRangeActionPerformed
      try {
         double[] range = new double[]{Double.valueOf(measurementTrialStartTime.getText()),
                                       Double.valueOf(measurementTrialEndTime.getText())};
         scaleToolModel.setMeasurementTrialTimeRange(range);
      } catch (Exception ex) {
      }
      // May have clamped, get actual values
      double[] range = scaleToolModel.getMeasurementTrialTimeRange();
      measurementTrialStartTime.setText(((Double)range[0]).toString());
      measurementTrialEndTime.setText(((Double)range[1]).toString());
      copyMeasurementTrialToStaticTrial();
   }//GEN-LAST:event_measurementSetTimeRangeActionPerformed
   
   //------------------------------------------------------------------------
   // MarkerPlacer data
   //------------------------------------------------------------------------

   private void copyMeasurementTrialToStaticTrial() {
      if(copyMeasurementTrialToStaticTrial.isSelected()) {
         staticTrialFileName.setFileName(measurementTrialFileName.getFileName());
         staticTrialStartTime.setText(measurementTrialStartTime.getText());
         staticTrialEndTime.setText(measurementTrialEndTime.getText());
         //staticTrialFileNameStateChanged(null);
         staticTrialTimeRangeActionPerformed(null);
      }
   }
   
   private void updateStaticTrialFieldsEnabled() {
      boolean copying = copyMeasurementTrialToStaticTrial.isSelected();
      boolean validTrial = scaleToolModel.getIKCommonModel().getMarkerDataValid();
      staticTrialFileName.setEnabled(!copying);
      staticTrialStartTime.setEnabled(!copying && validTrial);
      staticTrialEndTime.setEnabled(!copying && validTrial);
   }

   private void copyMeasurementTrialToStaticTrialActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_copyMeasurementTrialToStaticTrialActionPerformed
      copyMeasurementTrialToStaticTrial();
      updateStaticTrialFieldsEnabled();
   }//GEN-LAST:event_copyMeasurementTrialToStaticTrialActionPerformed

   private void staticTrialFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_staticTrialFileNameStateChanged
      boolean result = scaleToolModel.getIKCommonModel().setMarkerDataFileName(staticTrialFileName.getFileName());
      staticTrialFileName.setFileIsValid(result);
   }//GEN-LAST:event_staticTrialFileNameStateChanged

   private void coordinateFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_coordinateFileNameStateChanged
      boolean result = scaleToolModel.getIKCommonModel().setCoordinateDataFileName(coordinateFileName.getFileName());
      coordinateFileName.setFileIsValid(result);
   }//GEN-LAST:event_coordinateFileNameStateChanged
   
   private void staticTrialTimeRangeFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_staticTrialTimeRangeFocusLost
      if(!evt.isTemporary()) staticTrialTimeRangeActionPerformed(null);
   }//GEN-LAST:event_staticTrialTimeRangeFocusLost

   private void staticTrialTimeRangeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_staticTrialTimeRangeActionPerformed
      try {
         double[] range = new double[]{Double.valueOf(staticTrialStartTime.getText()), Double.valueOf(staticTrialEndTime.getText())};
         scaleToolModel.getIKCommonModel().setTimeRange(range);
      } catch (Exception ex) {
      }
      // May have clamped, get actual values
      double[] range = scaleToolModel.getIKCommonModel().getTimeRange();
      staticTrialStartTime.setText(((Double)range[0]).toString());
      staticTrialEndTime.setText(((Double)range[1]).toString());
   }//GEN-LAST:event_staticTrialTimeRangeActionPerformed

   //------------------------------------------------------------------------
   // Local variables
   //------------------------------------------------------------------------

   // Variables declaration - do not modify//GEN-BEGIN:variables
   private org.opensim.swingui.FileTextFieldAndChooser coordinateFileName;
   private javax.swing.JCheckBox copyMeasurementTrialToStaticTrial;
   private javax.swing.JPanel genericModelDataPanel;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel10;
   private javax.swing.JLabel jLabel11;
   private javax.swing.JLabel jLabel12;
   private javax.swing.JLabel jLabel13;
   private javax.swing.JLabel jLabel14;
   private javax.swing.JLabel jLabel15;
   private javax.swing.JLabel jLabel16;
   private javax.swing.JLabel jLabel17;
   private javax.swing.JLabel jLabel2;
   private javax.swing.JLabel jLabel3;
   private javax.swing.JLabel jLabel4;
   private javax.swing.JLabel jLabel5;
   private javax.swing.JLabel jLabel6;
   private javax.swing.JLabel jLabel7;
   private javax.swing.JLabel jLabel8;
   private javax.swing.JLabel jLabel9;
   private javax.swing.JPanel jPanel1;
   private javax.swing.JTabbedPane jTabbedPane;
   private javax.swing.JCheckBox loadMarkerSetCheckBox;
   private javax.swing.JPanel markerPlacerPanel;
   private org.opensim.swingui.FileTextFieldAndChooser markerSetFileName;
   private javax.swing.JTextField markerSetInfoTextField;
   private javax.swing.JTextField measurementTrialEndTime;
   private org.opensim.swingui.FileTextFieldAndChooser measurementTrialFileName;
   private org.opensim.tracking.MarkerDataInfoPanel measurementTrialInfoPanel;
   private javax.swing.JTextField measurementTrialStartTime;
   private javax.swing.JTextField modelMassTextField;
   private javax.swing.JTextField modelNameTextField;
   private javax.swing.JPanel modelScalerPanel;
   private javax.swing.JCheckBox preserveMassDistributionCheckBox;
   private javax.swing.JTextField staticTrialEndTime;
   private org.opensim.swingui.FileTextFieldAndChooser staticTrialFileName;
   private org.opensim.tracking.MarkerDataInfoPanel staticTrialInfoPanel;
   private javax.swing.JTextField staticTrialStartTime;
   private javax.swing.JPanel subjectDataPanel;
   private javax.swing.JTextField unscaledMarkerSetInfoTextField;
   private javax.swing.JTextField unscaledModelMassTextField;
   private javax.swing.JTextField unscaledModelNameTextField;
   // End of variables declaration//GEN-END:variables
   
}
