package org.opensim.tracking;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import org.opensim.modeling.SimmIKParams;
import org.opensim.modeling.SimmIKTrialParams;

public final class IKVisualPanel extends workflowVisualPanelBase {
    
    int numTrials;
    SimmIKTrialParams[] availableTrials=null;
    static boolean initialized=false;   // Tooltips and other GUI elements need to be set only once
    /**
     * Creates new form IKVisualPanel
     */
    public IKVisualPanel() {
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 
    }
    
    public String getName() {
        return "Inverse Kinematics";
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jModelSpecPanel = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jModelNameTextField = new javax.swing.JTextField();
        jModelBrowseButton = new javax.swing.JButton();
        jModelAddonForIKPanel = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        jMarkersFileTextField = new javax.swing.JTextField();
        jMarkersBrowseButton = new javax.swing.JButton();
        jMarkersEditButton = new javax.swing.JButton();
        jLabel3 = new javax.swing.JLabel();
        jCoordinateSetTextField = new javax.swing.JTextField();
        jButton4 = new javax.swing.JButton();
        jTrialSelectionPanel = new javax.swing.JPanel();
        jLabel4 = new javax.swing.JLabel();
        jTrialFileTextField = new javax.swing.JTextField();
        jBrowse4TRCButton5 = new javax.swing.JButton();
        jLabel6 = new javax.swing.JLabel();
        jFromTextField = new javax.swing.JTextField();
        jLabel7 = new javax.swing.JLabel();
        jToTextField = new javax.swing.JTextField();
        jLabel8 = new javax.swing.JLabel();
        jKinematicSmoothingTextField = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        jGroundReactionSmoothingTextField = new javax.swing.JTextField();
        jLabel11 = new javax.swing.JLabel();
        jTrialSelectComboBox = new javax.swing.JComboBox();
        jOutputPanel = new javax.swing.JPanel();
        jLabel10 = new javax.swing.JLabel();
        jOutputMotionTextField = new javax.swing.JTextField();
        jButton7 = new javax.swing.JButton();
        jIncludeMarkersInOutputCheckBox = new javax.swing.JCheckBox();
        jIncludeUserDataCheckBox = new javax.swing.JCheckBox();
        jScrollPane1 = new javax.swing.JScrollPane();
        jMessageTextArea = new javax.swing.JTextArea();

        jModelSpecPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Model specification"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel1, "Model file");

        org.openide.awt.Mnemonics.setLocalizedText(jModelBrowseButton, "Browse...");

        org.jdesktop.layout.GroupLayout jModelSpecPanelLayout = new org.jdesktop.layout.GroupLayout(jModelSpecPanel);
        jModelSpecPanel.setLayout(jModelSpecPanelLayout);
        jModelSpecPanelLayout.setHorizontalGroup(
            jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelSpecPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(jLabel1)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 150, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelBrowseButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 29, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(42, Short.MAX_VALUE))
        );
        jModelSpecPanelLayout.setVerticalGroup(
            jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                .add(jLabel1)
                .add(jModelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .add(jModelBrowseButton))
        );

        jModelAddonForIKPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Model adjustments for IK"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "Markers");

        org.openide.awt.Mnemonics.setLocalizedText(jMarkersBrowseButton, "Browse...");

        org.openide.awt.Mnemonics.setLocalizedText(jMarkersEditButton, "Edit...");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel3, "Coordinates");

        org.openide.awt.Mnemonics.setLocalizedText(jButton4, "Browse...");

        org.jdesktop.layout.GroupLayout jModelAddonForIKPanelLayout = new org.jdesktop.layout.GroupLayout(jModelAddonForIKPanel);
        jModelAddonForIKPanel.setLayout(jModelAddonForIKPanelLayout);
        jModelAddonForIKPanelLayout.setHorizontalGroup(
            jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelAddonForIKPanelLayout.createSequentialGroup()
                .add(jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jLabel3)
                    .add(jLabel2))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                    .add(jCoordinateSetTextField)
                    .add(jMarkersFileTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                    .add(jButton4, 0, 0, Short.MAX_VALUE)
                    .add(jMarkersBrowseButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, Short.MAX_VALUE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jMarkersEditButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
        );
        jModelAddonForIKPanelLayout.setVerticalGroup(
            jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelAddonForIKPanelLayout.createSequentialGroup()
                .add(jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel2)
                    .add(jMarkersFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jMarkersBrowseButton)
                    .add(jMarkersEditButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelAddonForIKPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel3)
                    .add(jCoordinateSetTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jButton4)))
        );

        jTrialSelectionPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Trials to solve"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel4, "Trial file");

        org.openide.awt.Mnemonics.setLocalizedText(jBrowse4TRCButton5, "Browse...");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel6, "use time from");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel7, "to");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel8, "Kinematic Smoothing Factor");

        jKinematicSmoothingTextField.setEnabled(false);

        org.openide.awt.Mnemonics.setLocalizedText(jLabel9, "Ground Reaction Smoothing ");

        jGroundReactionSmoothingTextField.setEnabled(false);

        org.openide.awt.Mnemonics.setLocalizedText(jLabel11, "Select trial");

        jTrialSelectComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTrialSelectComboBoxActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jTrialSelectionPanelLayout = new org.jdesktop.layout.GroupLayout(jTrialSelectionPanel);
        jTrialSelectionPanel.setLayout(jTrialSelectionPanelLayout);
        jTrialSelectionPanelLayout.setHorizontalGroup(
            jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jTrialSelectionPanelLayout.createSequentialGroup()
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jTrialSelectionPanelLayout.createSequentialGroup()
                        .add(24, 24, 24)
                        .add(jLabel6)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jFromTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 31, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel7)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jToTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 40, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jTrialSelectionPanelLayout.createSequentialGroup()
                        .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(jLabel11)
                            .add(jLabel4))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(jTrialFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 148, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                            .add(jTrialSelectComboBox, 0, 148, Short.MAX_VALUE))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jBrowse4TRCButton5, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                .add(71, 71, 71))
            .add(jTrialSelectionPanelLayout.createSequentialGroup()
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jLabel8)
                    .add(jLabel9))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                    .add(jGroundReactionSmoothingTextField, 0, 0, Short.MAX_VALUE)
                    .add(jKinematicSmoothingTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 38, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );
        jTrialSelectionPanelLayout.setVerticalGroup(
            jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jTrialSelectionPanelLayout.createSequentialGroup()
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel11)
                    .add(jTrialSelectComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel4)
                    .add(jBrowse4TRCButton5)
                    .add(jTrialFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(5, 5, 5)
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel6)
                    .add(jLabel7)
                    .add(jToTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jFromTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel8)
                    .add(jKinematicSmoothingTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(4, 4, 4)
                .add(jTrialSelectionPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel9)
                    .add(jGroundReactionSmoothingTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(29, 29, 29))
        );

        jOutputPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Output files"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel10, "Motion file");

        org.openide.awt.Mnemonics.setLocalizedText(jButton7, "Browse...");

        org.openide.awt.Mnemonics.setLocalizedText(jIncludeMarkersInOutputCheckBox, "include markers");
        jIncludeMarkersInOutputCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jIncludeMarkersInOutputCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jIncludeUserDataCheckBox, "include other data from motion file ");
        jIncludeUserDataCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jIncludeUserDataCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.jdesktop.layout.GroupLayout jOutputPanelLayout = new org.jdesktop.layout.GroupLayout(jOutputPanel);
        jOutputPanel.setLayout(jOutputPanelLayout);
        jOutputPanelLayout.setHorizontalGroup(
            jOutputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jOutputPanelLayout.createSequentialGroup()
                .add(jOutputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jOutputPanelLayout.createSequentialGroup()
                        .add(jLabel10)
                        .add(12, 12, 12)
                        .add(jOutputMotionTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 136, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jButton7, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 31, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jOutputPanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .add(jIncludeMarkersInOutputCheckBox))
                    .add(jOutputPanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .add(jIncludeUserDataCheckBox)))
                .addContainerGap(52, Short.MAX_VALUE))
        );
        jOutputPanelLayout.setVerticalGroup(
            jOutputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jOutputPanelLayout.createSequentialGroup()
                .add(jOutputPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel10)
                    .add(jOutputMotionTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jButton7))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jIncludeMarkersInOutputCheckBox)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .add(jIncludeUserDataCheckBox)
                .add(65, 65, 65))
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
            .add(layout.createSequentialGroup()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jOutputPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jTrialSelectionPanel, 0, 302, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jModelSpecPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jModelAddonForIKPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jScrollPane1))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(jModelSpecPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelAddonForIKPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jTrialSelectionPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 158, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jOutputPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 94, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 66, Short.MAX_VALUE)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jTrialSelectComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTrialSelectComboBoxActionPerformed
// TODO add your handling code here:
        JComboBox trialSelect = (JComboBox)evt.getSource();
        makeTrialCurrent((SimmIKTrialParams) trialSelect.getSelectedItem());
    }//GEN-LAST:event_jTrialSelectComboBoxActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBrowse4TRCButton5;
    private javax.swing.JButton jButton4;
    private javax.swing.JButton jButton7;
    private javax.swing.JTextField jCoordinateSetTextField;
    private javax.swing.JTextField jFromTextField;
    private javax.swing.JTextField jGroundReactionSmoothingTextField;
    private javax.swing.JCheckBox jIncludeMarkersInOutputCheckBox;
    private javax.swing.JCheckBox jIncludeUserDataCheckBox;
    private javax.swing.JTextField jKinematicSmoothingTextField;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JButton jMarkersBrowseButton;
    private javax.swing.JButton jMarkersEditButton;
    private javax.swing.JTextField jMarkersFileTextField;
    private javax.swing.JTextArea jMessageTextArea;
    private javax.swing.JPanel jModelAddonForIKPanel;
    private javax.swing.JButton jModelBrowseButton;
    private javax.swing.JTextField jModelNameTextField;
    private javax.swing.JPanel jModelSpecPanel;
    private javax.swing.JTextField jOutputMotionTextField;
    private javax.swing.JPanel jOutputPanel;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField jToTextField;
    private javax.swing.JTextField jTrialFileTextField;
    private javax.swing.JComboBox jTrialSelectComboBox;
    private javax.swing.JPanel jTrialSelectionPanel;
    // End of variables declaration//GEN-END:variables
    void updateWorkflow(WorkflowDescriptor descriptor) {
    }

    void updatePanel(WorkflowDescriptor aDescriptor) {
        initialize(aDescriptor);
        SimmIKParams params = aDescriptor.getSubject().getIKParams();
        
        String modelFile = params.getModelFileName();
        if (modelFile.equalsIgnoreCase("Unassigned") || modelFile.equals("")){
            // Assume output of previous step
            modelFile = aDescriptor.getSubject().getMarkerPlacementParams().getOutputModelFileName();
        }
        jModelNameTextField.setText(modelFile); 
        numTrials = params.getNumIKTrials();
        if (availableTrials==null){ // First time around in this panel
            availableTrials = new SimmIKTrialParams[numTrials];
            for(int i=0; i < numTrials; i++){
                availableTrials[i] = params.getTrialParams(i);
            }
            if (jTrialSelectComboBox.getModel().getSize()==0){
                for(int i=0; i < numTrials; i++){
                    jTrialSelectComboBox.setModel(new DefaultComboBoxModel(availableTrials));
                }                
            }
       }
        // IF no trials are availble, we're in trouble
        if (numTrials==0){
           jTrialSelectComboBox.setEnabled(false);
           showMessage("No trials are available");
        }
        else
            // Get data for first trial and populate the dialog.
            makeTrialCurrent(availableTrials[0]);
    }
    /**
     * Mark one of the trials as current and update the GUI accordingly
     */
    private void makeTrialCurrent(SimmIKTrialParams simmIKTrialParams) {
        String trialName = simmIKTrialParams.getName();
        jTrialFileTextField.setText(simmIKTrialParams.getMarkerDataFilename());  //.trc
        jFromTextField.setText(String.valueOf(simmIKTrialParams.getStartTime()));
        jToTextField.setText(String.valueOf(simmIKTrialParams.getEndTime()));
        jOutputMotionTextField.setText(simmIKTrialParams.getOutputMotionFilename());
        jOutputMotionTextField.setToolTipText(simmIKTrialParams.getPropertySet().get("output_motion_file").getComment());
        jKinematicSmoothingTextField.setToolTipText(simmIKTrialParams.getPropertySet().get("kinematics_smoothing").getComment());
        jGroundReactionSmoothingTextField.setToolTipText(simmIKTrialParams.getPropertySet().get("ground_reaction_smoothing").getComment());
        jIncludeMarkersInOutputCheckBox.setSelected(simmIKTrialParams.getIncludeMarkers());
    }

    private void initialize(WorkflowDescriptor aDescriptor) {
        if (!initialized){
            SimmIKParams params = aDescriptor.getSubject().getIKParams();
            jModelNameTextField.setToolTipText(params.getPropertySet().get("model_file").getComment());
            jMarkersFileTextField.setToolTipText(params.getPropertySet().get("MarkerSet").getComment());
            jCoordinateSetTextField.setToolTipText(params.getPropertySet().get("CoordinateSet").getComment());
            initialized = true;
        }
    }
    /**
     * @returns trial selected by the user 
     */
    public SimmIKTrialParams getSelectedTrial()
    {
        return ((SimmIKTrialParams)jTrialSelectComboBox.getSelectedItem());
    }

    private void showMessage(String message) {
        jMessageTextArea.setText(message);    
    }
}

