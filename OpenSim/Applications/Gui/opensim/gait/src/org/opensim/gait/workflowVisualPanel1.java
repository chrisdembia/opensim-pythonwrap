package org.opensim.gait;

import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import org.openide.util.NbBundle;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmSubject;

public final class workflowVisualPanel1 extends JPanel {

    boolean ownModel;
    boolean ownMarkers;
    /** Creates new form workflowVisualPanel1 */
    public workflowVisualPanel1() {
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 

    }
    
    public String getName() {
        return NbBundle.getMessage(workflowVisualPanel1.class, "CTL_LoadGenericModel");
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        modelButtonGroup = new javax.swing.ButtonGroup();
        markerButtonGroup = new javax.swing.ButtonGroup();
        jSubjectFilePanel = new javax.swing.JPanel();
        jLabel7 = new javax.swing.JLabel();
        jSubjectFileTextField = new javax.swing.JTextField();
        jGetSubjectFileButton = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        jModelDefaultRadioButton = new javax.swing.JRadioButton();
        jModelOwnRadioButton = new javax.swing.JRadioButton();
        jBrowseForModelButton = new javax.swing.JButton();
        jModelNameTextField = new javax.swing.JTextField();
        jAgeTextField = new javax.swing.JTextField();
        jAgeLabel = new javax.swing.JLabel();
        jWeightLabel = new javax.swing.JLabel();
        jWeightTextField = new javax.swing.JTextField();
        jHeightLabel = new javax.swing.JLabel();
        jHeightTextField = new javax.swing.JTextField();
        jGenderLabel = new javax.swing.JLabel();
        jGenderTextField = new javax.swing.JTextField();
        jPanel2 = new javax.swing.JPanel();
        jDefaultMarkersRadioButton = new javax.swing.JRadioButton();
        jOwnMarkersRadioButton = new javax.swing.JRadioButton();
        jOwnMarkersTextField = new javax.swing.JTextField();
        jMarkersNameButton = new javax.swing.JButton();
        jMarkersEditButton = new javax.swing.JButton();

        modelButtonGroup.add(jModelDefaultRadioButton);
        modelButtonGroup.add(jModelOwnRadioButton);

        jSubjectFilePanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Workflow Customization [Optional]"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel7, "Subject file");

        jSubjectFileTextField.setText("*.xml");
        jSubjectFileTextField.setToolTipText("Hello Paul");
        jSubjectFileTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jSubjectFileTextFieldActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jGetSubjectFileButton, "Browse...");
        jGetSubjectFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jGetSubjectFileButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jSubjectFilePanelLayout = new org.jdesktop.layout.GroupLayout(jSubjectFilePanel);
        jSubjectFilePanel.setLayout(jSubjectFilePanelLayout);
        jSubjectFilePanelLayout.setHorizontalGroup(
            jSubjectFilePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSubjectFilePanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(jLabel7)
                .add(35, 35, 35)
                .add(jSubjectFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 164, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jGetSubjectFileButton)
                .addContainerGap(66, Short.MAX_VALUE))
        );
        jSubjectFilePanelLayout.setVerticalGroup(
            jSubjectFilePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSubjectFilePanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(jSubjectFilePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel7)
                    .add(jSubjectFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jGetSubjectFileButton))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder("Model Selection"));
        modelButtonGroup.add(jModelDefaultRadioButton);
        jModelDefaultRadioButton.setSelected(true);
        org.openide.awt.Mnemonics.setLocalizedText(jModelDefaultRadioButton, "Use default model");
        jModelDefaultRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelDefaultRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

        modelButtonGroup.add(jModelOwnRadioButton);
        org.openide.awt.Mnemonics.setLocalizedText(jModelOwnRadioButton, "Use own model");
        jModelOwnRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelOwnRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jModelOwnRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jModelOwnRadioButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseForModelButton, "Browse...");
        jBrowseForModelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseForModelButtonActionPerformed(evt);
            }
        });

        jModelNameTextField.setEditable(false);

        jAgeTextField.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jAgeLabel, "Age");

        org.openide.awt.Mnemonics.setLocalizedText(jWeightLabel, "Weight");

        jWeightTextField.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jHeightLabel, "Height");

        jHeightTextField.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jGenderLabel, "Gender");

        jGenderTextField.setEditable(false);

        org.jdesktop.layout.GroupLayout jPanel1Layout = new org.jdesktop.layout.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jPanel1Layout.createSequentialGroup()
                        .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(jModelDefaultRadioButton)
                            .add(jPanel1Layout.createSequentialGroup()
                                .add(jModelOwnRadioButton)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jModelNameTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 129, Short.MAX_VALUE)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jBrowseForModelButton)))
                        .addContainerGap(94, Short.MAX_VALUE))
                    .add(jPanel1Layout.createSequentialGroup()
                        .add(jAgeLabel)
                        .add(17, 17, 17)
                        .add(jAgeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 47, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jWeightLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jWeightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 46, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jHeightLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jHeightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 44, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(12, 12, 12)
                        .add(jGenderLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jGenderTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 48, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .add(jModelDefaultRadioButton)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jModelOwnRadioButton)
                    .add(jBrowseForModelButton)
                    .add(jModelNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 14, Short.MAX_VALUE)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jAgeLabel)
                    .add(jAgeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jWeightLabel)
                    .add(jHeightLabel)
                    .add(jHeightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jWeightTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jGenderLabel)
                    .add(jGenderTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder("Marker Selection"));
        markerButtonGroup.add(jDefaultMarkersRadioButton);
        jDefaultMarkersRadioButton.setSelected(true);
        org.openide.awt.Mnemonics.setLocalizedText(jDefaultMarkersRadioButton, "use default markers");
        jDefaultMarkersRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jDefaultMarkersRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jDefaultMarkersRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDefaultMarkersRadioButtonActionPerformed(evt);
            }
        });

        markerButtonGroup.add(jOwnMarkersRadioButton);
        org.openide.awt.Mnemonics.setLocalizedText(jOwnMarkersRadioButton, "use own markers");
        jOwnMarkersRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jOwnMarkersRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jOwnMarkersRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jOwnMarkersRadioButtonActionPerformed(evt);
            }
        });

        jOwnMarkersTextField.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jMarkersNameButton, "Browse...");
        jMarkersNameButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMarkersNameButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jMarkersEditButton, "Edit...");

        org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jDefaultMarkersRadioButton)
                    .add(jPanel2Layout.createSequentialGroup()
                        .add(jOwnMarkersRadioButton)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jOwnMarkersTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 118, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jMarkersNameButton)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jMarkersEditButton)))
                .addContainerGap(26, Short.MAX_VALUE))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel2Layout.createSequentialGroup()
                .add(jDefaultMarkersRadioButton)
                .add(14, 14, 14)
                .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOwnMarkersRadioButton)
                    .add(jOwnMarkersTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jMarkersNameButton)
                    .add(jMarkersEditButton))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jSubjectFilePanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(jSubjectFilePanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jMarkersNameButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMarkersNameButtonActionPerformed
// TODO add your handling code here:
       useOwnMarkers();
    }//GEN-LAST:event_jMarkersNameButtonActionPerformed

    private void jOwnMarkersRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jOwnMarkersRadioButtonActionPerformed
// TODO add your handling code here:
        useOwnMarkers();
    }//GEN-LAST:event_jOwnMarkersRadioButtonActionPerformed

    private void jBrowseForModelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseForModelButtonActionPerformed
// TODO add your handling code here:
        useOwnModel();

    }//GEN-LAST:event_jBrowseForModelButtonActionPerformed

    private void jModelOwnRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jModelOwnRadioButtonActionPerformed
// TODO add your handling code here:
        useOwnModel();
    }//GEN-LAST:event_jModelOwnRadioButtonActionPerformed

    private void jDefaultMarkersRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDefaultMarkersRadioButtonActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jDefaultMarkersRadioButtonActionPerformed

    private void jGetSubjectFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jGetSubjectFileButtonActionPerformed
        final JFileChooser dlog = new JFileChooser();
        
        dlog.setDialogTitle(NbBundle.getMessage(workflowVisualPanel1.class, "CTL_OpenSubjectFileDlgTitle"));
        dlog.setFileFilter(new XMLFileFilter());
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jSubjectFileTextField.setText(dlog.getSelectedFile().getAbsolutePath());
            // Create a subject instance. This should be moves to the non-GUI counterpart class.
            SimmSubject subject = new SimmSubject(dlog.getSelectedFile().getAbsolutePath());
            setModelFile(subject.getGenericModelParams().getModelFileName());
            setSubjectInfo(subject);
            
            // @ToDo This may need to be changed once the "Default" really exists.
            jModelOwnRadioButton.setSelected(true);
        }
        //else
        //subject = new SimmSubject();
    }//GEN-LAST:event_jGetSubjectFileButtonActionPerformed

    private void jSubjectFileTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jSubjectFileTextFieldActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jSubjectFileTextFieldActionPerformed
    

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jAgeLabel;
    private javax.swing.JTextField jAgeTextField;
    private javax.swing.JButton jBrowseForModelButton;
    private javax.swing.JRadioButton jDefaultMarkersRadioButton;
    private javax.swing.JLabel jGenderLabel;
    private javax.swing.JTextField jGenderTextField;
    private javax.swing.JButton jGetSubjectFileButton;
    private javax.swing.JLabel jHeightLabel;
    private javax.swing.JTextField jHeightTextField;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JButton jMarkersEditButton;
    private javax.swing.JButton jMarkersNameButton;
    private javax.swing.JRadioButton jModelDefaultRadioButton;
    private javax.swing.JTextField jModelNameTextField;
    private javax.swing.JRadioButton jModelOwnRadioButton;
    private javax.swing.JRadioButton jOwnMarkersRadioButton;
    private javax.swing.JTextField jOwnMarkersTextField;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jSubjectFilePanel;
    private javax.swing.JTextField jSubjectFileTextField;
    private javax.swing.JLabel jWeightLabel;
    private javax.swing.JTextField jWeightTextField;
    private javax.swing.ButtonGroup markerButtonGroup;
    private javax.swing.ButtonGroup modelButtonGroup;
    // End of variables declaration//GEN-END:variables
        
    class XMLFileFilter extends javax.swing.filechooser.FileFilter {
        public boolean accept(File f) {
            return f.isDirectory() || f.getName().toLowerCase().endsWith(".xml");
        }

        public String getDescription() {
            return ".xml files";
        }
    }    
    /**
     * updatePanel updates the fields in the GUI based on the WorkflowDescriptor object
     */
    public void updatePanel(WorkflowDescriptor aDescriptor)
    {   
        jModelOwnRadioButton.setSelected(aDescriptor.getUseOwnModel());
        jOwnMarkersRadioButton.setSelected(aDescriptor.getUseOwnMarkers());
        SimmModel aModel = aDescriptor.getModel();
   }
    
   /**
    * Handle user switching to use his own model either by browsing or using the dario button
    * @returns true on success
    */
    private boolean  useOwnModel() {
        
        boolean selectModel = false;
        final JFileChooser dlog = new JFileChooser();
        
        String modelFile=null;
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            modelFile= dlog.getSelectedFile().getAbsolutePath();
            selectModel = true;
        }
        setModelFile(modelFile);
        
        return selectModel;
   }
   /**
    * One common place to set Model file (either from Browse... or from the radio button)
    */
    private void setModelFile(String modelFile) {
        if (modelFile!= null){
            jModelOwnRadioButton.setSelected(true);
            String parentPath = new File(modelFile).getParent();
            if (parentPath != null)
                jModelNameTextField.setText(modelFile.substring(parentPath.length()+1));
            else
                jModelNameTextField.setText(modelFile);
            // Update GUI accordingly
            ownModel = true;
        }
        else {
            jModelDefaultRadioButton.setSelected(true);
            ownModel = false;
        }

    }
    // Repeat for markers
    private boolean  useOwnMarkers() {

        boolean selectMarkers = false;
        final JFileChooser dlog = new JFileChooser();

        String markersFile=null;
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            markersFile= dlog.getSelectedFile().getAbsolutePath();
            selectMarkers = true;
        }
        setMarkersFile(markersFile);

        return selectMarkers;
   }
   /**
    * setMarkersFile is the one common place where markersFile is set 
    * (either from Browse... or from the radio button)
    */
    private void setMarkersFile(String markersFile) {
        if (markersFile!= null){
            jOwnMarkersRadioButton.setSelected(true);
            String parentPath = new File(markersFile).getParent();
            if (parentPath != null)
                jOwnMarkersTextField.setText(markersFile.substring(parentPath.length()+1));
            else
                 jOwnMarkersTextField.setText(markersFile);
       }
        else
            jDefaultMarkersRadioButton.setSelected(true);
    }

    private void setSubjectInfo(SimmSubject subject) {
        if (subject!= null){
            jWeightTextField.setText(String.valueOf(subject.getSubjectMass()));
            jHeightTextField.setText(String.valueOf(subject.getSubjectHeight()));
            jAgeTextField.setText(String.valueOf(subject.getSubjectAge()));
        }
        else {
            jWeightTextField.setText("");
            jHeightTextField.setText("");
            jAgeTextField.setText("");
        }
    }

    public boolean hasModel()
    {
        return (ownModel || jModelNameTextField.getText()!= "");
    }
    
    public String getModel()
    {
        return jModelNameTextField.getText();
    }
}

