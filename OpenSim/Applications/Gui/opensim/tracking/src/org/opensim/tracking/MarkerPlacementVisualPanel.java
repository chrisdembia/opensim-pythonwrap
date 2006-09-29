package org.opensim.tracking;

import javax.swing.JFileChooser;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.swingui.ValidateUserInput;
import org.opensim.utils.FileUtils;

public final class MarkerPlacementVisualPanel extends workflowVisualPanelBase {
    
    /**
     * Creates new form MarkerPlacementVisualPanel
     */
    public MarkerPlacementVisualPanel(workflowWizardPanelBase basePanel) {
        super(basePanel);
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 
    }
    
    public String getName() {
        return "Place markers based on trial";
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jSolveStaticPosePanel = new javax.swing.JPanel();
        jStaticTrialTextField = new javax.swing.JTextField();
        jBrowse4TrcButton = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jStaticFromTextField = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        jStaticToTextField = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jCoordinatesFileTextField = new javax.swing.JTextField();
        jMarkersFileTextField = new javax.swing.JTextField();
        jInitCoordinatesFileButton = new javax.swing.JButton();
        jAdditionalMarkersFileButton = new javax.swing.JButton();
        jOutputFilesPanel = new javax.swing.JPanel();
        jOutputMarkersFileNameTextField = new javax.swing.JTextField();
        jSimmJntCheckBox = new javax.swing.JCheckBox();
        iSaveMarkersCheckBox = new javax.swing.JCheckBox();
        jSaveMotionCheckBox = new javax.swing.JCheckBox();
        jOutputMotionTextField = new javax.swing.JTextField();
        jOutputJntTextField = new javax.swing.JTextField();
        jSaveOsimCheckBox = new javax.swing.JCheckBox();
        jOsimFilenameTextField = new javax.swing.JTextField();
        jBrowseOsimButton = new javax.swing.JButton();
        jBrowseMarkersButton = new javax.swing.JButton();
        jBrowseMotionButton = new javax.swing.JButton();
        jBrowseJntButton = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        jMessageTextArea = new javax.swing.JTextArea();

        jSolveStaticPosePanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Static pose"));

        org.openide.awt.Mnemonics.setLocalizedText(jBrowse4TrcButton, "Browse...");
        jBrowse4TrcButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowse4TrcButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jLabel1, "Static trial file");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "use time from");

        jStaticFromTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jStaticFromTextFieldActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jLabel3, "to");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel4, "Coordinates file");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel5, "Markers file");

        org.openide.awt.Mnemonics.setLocalizedText(jInitCoordinatesFileButton, "Browse...");
        jInitCoordinatesFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jInitCoordinatesFileButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jAdditionalMarkersFileButton, "Browse...");
        jAdditionalMarkersFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jAdditionalMarkersFileButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jSolveStaticPosePanelLayout = new org.jdesktop.layout.GroupLayout(jSolveStaticPosePanel);
        jSolveStaticPosePanel.setLayout(jSolveStaticPosePanelLayout);
        jSolveStaticPosePanelLayout.setHorizontalGroup(
            jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSolveStaticPosePanelLayout.createSequentialGroup()
                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jSolveStaticPosePanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .add(jLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jStaticFromTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 52, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel3)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jStaticToTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 46, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jSolveStaticPosePanelLayout.createSequentialGroup()
                        .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jSolveStaticPosePanelLayout.createSequentialGroup()
                                .add(jLabel1)
                                .add(13, 13, 13)
                                .add(jStaticTrialTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 147, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jSolveStaticPosePanelLayout.createSequentialGroup()
                                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                                    .add(jLabel4)
                                    .add(jLabel5))
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                                    .add(jMarkersFileTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 146, Short.MAX_VALUE)
                                    .add(jCoordinatesFileTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 146, Short.MAX_VALUE))))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                            .add(jAdditionalMarkersFileButton, 0, 0, Short.MAX_VALUE)
                            .add(jInitCoordinatesFileButton, 0, 0, Short.MAX_VALUE)
                            .add(jBrowse4TrcButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 35, Short.MAX_VALUE))))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jSolveStaticPosePanelLayout.setVerticalGroup(
            jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSolveStaticPosePanelLayout.createSequentialGroup()
                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel1)
                    .add(jStaticTrialTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowse4TrcButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel2)
                    .add(jLabel3)
                    .add(jStaticToTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jStaticFromTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(15, 15, 15)
                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel4)
                    .add(jCoordinatesFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jInitCoordinatesFileButton))
                .add(14, 14, 14)
                .add(jSolveStaticPosePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel5)
                    .add(jMarkersFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jAdditionalMarkersFileButton)))
        );

        jOutputFilesPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Output files"));

        org.openide.awt.Mnemonics.setLocalizedText(jSimmJntCheckBox, "SIMM .jnt");
        jSimmJntCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jSimmJntCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(iSaveMarkersCheckBox, "Markers");
        iSaveMarkersCheckBox.setActionCommand("Markers.xml");
        iSaveMarkersCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        iSaveMarkersCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jSaveMotionCheckBox, "Save.mot");
        jSaveMotionCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jSaveMotionCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jSaveOsimCheckBox, "OpenSim");
        jSaveOsimCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jSaveOsimCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseOsimButton, "jButton1");
        jBrowseOsimButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseOsimButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseMarkersButton, "jButton4");
        jBrowseMarkersButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseMarkersButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseMotionButton, "jButton6");
        jBrowseMotionButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseMotionButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseJntButton, "jButton7");
        jBrowseJntButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseJntButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jOutputFilesPanelLayout = new org.jdesktop.layout.GroupLayout(jOutputFilesPanel);
        jOutputFilesPanel.setLayout(jOutputFilesPanelLayout);
        jOutputFilesPanelLayout.setHorizontalGroup(
            jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jOutputFilesPanelLayout.createSequentialGroup()
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jSaveMotionCheckBox)
                    .add(jSimmJntCheckBox)
                    .add(iSaveMarkersCheckBox)
                    .add(jSaveOsimCheckBox))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                    .add(jOutputJntTextField)
                    .add(jOutputMotionTextField)
                    .add(jOutputMarkersFileNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 140, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, jOutputFilesPanelLayout.createSequentialGroup()
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jOsimFilenameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 156, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                    .add(jBrowseJntButton, 0, 0, Short.MAX_VALUE)
                    .add(jBrowseMotionButton, 0, 0, Short.MAX_VALUE)
                    .add(jBrowseMarkersButton, 0, 0, Short.MAX_VALUE)
                    .add(jBrowseOsimButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 29, Short.MAX_VALUE))
                .add(55, 55, 55))
        );
        jOutputFilesPanelLayout.setVerticalGroup(
            jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jOutputFilesPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jSaveOsimCheckBox)
                    .add(jOsimFilenameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowseOsimButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOutputMarkersFileNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(iSaveMarkersCheckBox)
                    .add(jBrowseMarkersButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOutputMotionTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jSaveMotionCheckBox)
                    .add(jBrowseMotionButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOutputJntTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jSimmJntCheckBox)
                    .add(jBrowseJntButton))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jScrollPane1.setBorder(null);
        jScrollPane1.setForeground(new java.awt.Color(204, 0, 51));
        jScrollPane1.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        jScrollPane1.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
        jScrollPane1.setEnabled(false);
        jScrollPane1.setFocusable(false);
        jMessageTextArea.setBackground(new java.awt.Color(224, 223, 227));
        jMessageTextArea.setColumns(20);
        jMessageTextArea.setEditable(false);
        jMessageTextArea.setForeground(new java.awt.Color(204, 0, 51));
        jMessageTextArea.setRows(5);
        jMessageTextArea.setBorder(null);
        jMessageTextArea.setFocusable(false);
        jMessageTextArea.setOpaque(false);
        jScrollPane1.setViewportView(jMessageTextArea);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSolveStaticPosePanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(jOutputFilesPanel, 0, 292, Short.MAX_VALUE)
            .add(org.jdesktop.layout.GroupLayout.TRAILING, jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 292, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jSolveStaticPosePanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputFilesPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 92, Short.MAX_VALUE)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jBrowseJntButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseJntButtonActionPerformed
      final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".jnt", "Output SIMM jnt file"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jOutputJntTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowseJntButtonActionPerformed

    private void jBrowseMotionButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseMotionButtonActionPerformed
      final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".mot", "Output Motion file"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jOutputMotionTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowseMotionButtonActionPerformed

    private void jBrowseMarkersButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseMarkersButtonActionPerformed
       final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Output Markers"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jOutputMarkersFileNameTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowseMarkersButtonActionPerformed

    private void jBrowseOsimButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseOsimButtonActionPerformed
       final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".xml, .osim", "Output OpenSim model"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jOsimFilenameTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowseOsimButtonActionPerformed

    private void jStaticFromTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jStaticFromTextFieldActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jStaticFromTextFieldActionPerformed

    private void jAdditionalMarkersFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAdditionalMarkersFileButtonActionPerformed
       final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Additional markers for static pose solution"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jMarkersFileTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jAdditionalMarkersFileButtonActionPerformed

    private void jInitCoordinatesFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jInitCoordinatesFileButtonActionPerformed
       final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".mot", "Motion file to initialize static pose solution"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jCoordinatesFileTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
// TODO add your handling code here:
    }//GEN-LAST:event_jInitCoordinatesFileButtonActionPerformed

    private void jBrowse4TrcButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowse4TrcButtonActionPerformed
// TODO add your handling code here:
       final JFileChooser dlog = new JFileChooser("");
       dlog.setFileFilter(FileUtils.getFileFilter(".trc", "Static trial file"));

       if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jStaticTrialTextField.setText(dlog.getSelectedFile().getAbsolutePath());
       }
        
    }//GEN-LAST:event_jBrowse4TrcButtonActionPerformed

    void updatePanel(WorkflowDescriptor aDescriptor) {
        SimmMarkerPlacementParams params = aDescriptor.getSubject().getMarkerPlacementParams();
        jStaticTrialTextField.setText(params.getStaticPoseFilename());  //trc file of static trial
        jStaticTrialTextField.setToolTipText(params.getPropertySet().get("marker_trial").getComment());
        jCoordinatesFileTextField.setToolTipText(params.getPropertySet().get("SimmCoordinateSet").getComment());
        jMarkersFileTextField.setToolTipText(params.getPropertySet().get("SimmMarkerSet").getComment());
        jOutputJntTextField.setToolTipText(params.getPropertySet().get("output_joint_file").getComment());
        jOsimFilenameTextField.setToolTipText(params.getPropertySet().get("output_model_file").getComment());
        jOutputMarkersFileNameTextField.setToolTipText(params.getPropertySet().get("output_marker_file").getComment());
        jOutputMotionTextField.setToolTipText(params.getPropertySet().get("output_motion_file").getComment());
        ArrayDouble timeRange = params.getTimeRange();
        if (timeRange.getSize()==2){
            jStaticFromTextField.setText(String.valueOf(timeRange.getitem(0)));  // from time in trc
            jStaticToTextField.setText(String.valueOf(timeRange.getitem(1)));  // to time in trc
        }
        if (!params.getCoordinateFileName().equalsIgnoreCase("Unassigned")){
            jCoordinatesFileTextField.setText(params.getCoordinateFileName());  // Coordinate file to init Single frame IK
            jCoordinatesFileTextField.setToolTipText(params.getPropertySet().get("coordinate_trial").getComment());
        }
        jMarkersFileTextField.setText("");      // Extra markers

        // We need to make a name for output files (at least the xml file) for
        // our own sake so that we can open it later.
        String subjectPath = aDescriptor.dSubject.getPathToSubject();
        
        if (!params.getOutputModelFileName().equalsIgnoreCase("Unassigned")){
            jOsimFilenameTextField.setText(params.getOutputModelFileName());
            jSaveOsimCheckBox.setSelected(true);
        }
        else{
            // Make up a default name
            jOsimFilenameTextField.setText(aDescriptor.dSubject.getPathToSubject()+
                                            FileUtils.addSuffix(params.getOutputModelFileName(),"MP")+".osim");
        }
        // Joint file .jnt
        if (!params.getOutputJointFileName().equalsIgnoreCase("Unassigned")){
            jOutputJntTextField.setText(params.getOutputJointFileName());
            jSimmJntCheckBox.setSelected(true);
        }
        else{
            // Make up a default name
            jOutputJntTextField.setText(aDescriptor.dSubject.getPathToSubject()+
                                            FileUtils.addSuffix(params.getOutputJointFileName(),"MP")+".jnt");
        }
        // New markers
        if (!params.getOutputMarkerFileName().equalsIgnoreCase("Unassigned")){
            jOutputMarkersFileNameTextField.setText(params.getOutputMarkerFileName());
            iSaveMarkersCheckBox.setSelected(true);
        }
        else{
            // Make up a default name
            jOutputMarkersFileNameTextField.setText(aDescriptor.dSubject.getPathToSubject()+
                                            FileUtils.addSuffix(params.getOutputMarkerFileName(),"MP")+".xml");
        }
        // Motion file
        if (!params.getOutputMotionFileName().equalsIgnoreCase("Unassigned")){
            jOutputMotionTextField.setText(params.getOutputMotionFileName());
            jSaveMotionCheckBox.setSelected(true);
        }
        else{
            // Make up a default name
            jOutputMotionTextField.setText(aDescriptor.dSubject.getPathToSubject()+
                                            FileUtils.addSuffix(params.getOutputMotionFileName(),"MP")+".osim");
        }
       
    }

    void updateWorkflow(WorkflowDescriptor descriptor) {
        SimmMarkerPlacementParams params = descriptor.getSubject().getMarkerPlacementParams();
        params.setStaticPoseFilename(jStaticTrialTextField.getText());
        ArrayDouble timeRange = new ArrayDouble(2);
        timeRange.setitem(0, Double.parseDouble(jStaticFromTextField.getText()));
        timeRange.setitem(1, Double.parseDouble(jStaticToTextField.getText()));
        //params.setTimeRange(timeRange);
        //if (jCoordinatesFileTextField.getText()!="")
        //  params.setCoordinateFile(jCoordinatesFileTextField.getText());

        
    }
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JCheckBox iSaveMarkersCheckBox;
    private javax.swing.JButton jAdditionalMarkersFileButton;
    private javax.swing.JButton jBrowse4TrcButton;
    private javax.swing.JButton jBrowseJntButton;
    private javax.swing.JButton jBrowseMarkersButton;
    private javax.swing.JButton jBrowseMotionButton;
    private javax.swing.JButton jBrowseOsimButton;
    private javax.swing.JTextField jCoordinatesFileTextField;
    private javax.swing.JButton jInitCoordinatesFileButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JTextField jMarkersFileTextField;
    private javax.swing.JTextArea jMessageTextArea;
    private javax.swing.JTextField jOsimFilenameTextField;
    private javax.swing.JPanel jOutputFilesPanel;
    private javax.swing.JTextField jOutputJntTextField;
    private javax.swing.JTextField jOutputMarkersFileNameTextField;
    private javax.swing.JTextField jOutputMotionTextField;
    private javax.swing.JCheckBox jSaveMotionCheckBox;
    private javax.swing.JCheckBox jSaveOsimCheckBox;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JCheckBox jSimmJntCheckBox;
    private javax.swing.JPanel jSolveStaticPosePanel;
    private javax.swing.JTextField jStaticFromTextField;
    private javax.swing.JTextField jStaticToTextField;
    private javax.swing.JTextField jStaticTrialTextField;
    // End of variables declaration//GEN-END:variables
    public void appendMessage(String message)
    {
        jMessageTextArea.append(message);
        repaint();
    }
    
}

