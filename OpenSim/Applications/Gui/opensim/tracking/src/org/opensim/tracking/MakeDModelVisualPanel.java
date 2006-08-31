package org.opensim.tracking;

import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import org.openide.windows.WindowManager;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.utils.FileUtils;

public final class MakeDModelVisualPanel extends workflowVisualPanelBase {
    
    /**
     * Creates new form MakeDModelVisualPanel
     */
    public MakeDModelVisualPanel() {
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 
    }
    
    public String getName() {
        return "Generate dynamic model";
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
        jModelTextField = new javax.swing.JTextField();
        jBrowse4ModelButton = new javax.swing.JButton();
        jCreateParamsCheckBox = new javax.swing.JCheckBox();
        jLabel2 = new javax.swing.JLabel();
        jDynamicsDirTextField = new javax.swing.JTextField();
        jBrowseForDynamicsDirButton = new javax.swing.JButton();
        jMessageTextArea = new javax.swing.JTextArea();

        jModelSpecPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Model Specification"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel1, "Model file");

        jModelTextField.setText("*.xml");

        org.openide.awt.Mnemonics.setLocalizedText(jBrowse4ModelButton, "...");
        jBrowse4ModelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowse4ModelButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jCreateParamsCheckBox, "Create params.txt file in same directory");
        jCreateParamsCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jCreateParamsCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "Directory for dynamics files:");

        jDynamicsDirTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDynamicsDirTextFieldActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jBrowseForDynamicsDirButton, "...");
        jBrowseForDynamicsDirButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseForDynamicsDirButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jModelSpecPanelLayout = new org.jdesktop.layout.GroupLayout(jModelSpecPanel);
        jModelSpecPanel.setLayout(jModelSpecPanelLayout);
        jModelSpecPanelLayout.setHorizontalGroup(
            jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelSpecPanelLayout.createSequentialGroup()
                .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jCreateParamsCheckBox)
                    .add(jLabel2)
                    .add(jModelSpecPanelLayout.createSequentialGroup()
                        .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                            .add(jModelSpecPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .add(jDynamicsDirTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 186, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jModelSpecPanelLayout.createSequentialGroup()
                                .add(jLabel1)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jModelTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 185, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
                            .add(jBrowseForDynamicsDirButton, 0, 0, Short.MAX_VALUE)
                            .add(jBrowse4ModelButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 38, Short.MAX_VALUE))))
                .addContainerGap(55, Short.MAX_VALUE))
        );
        jModelSpecPanelLayout.setVerticalGroup(
            jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelSpecPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel1)
                    .add(jModelTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowse4ModelButton))
                .add(20, 20, 20)
                .add(jLabel2)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jModelSpecPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jDynamicsDirTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowseForDynamicsDirButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .add(jCreateParamsCheckBox))
        );

        jMessageTextArea.setBackground(new java.awt.Color(224, 223, 227));
        jMessageTextArea.setColumns(20);
        jMessageTextArea.setEditable(false);
        jMessageTextArea.setFont(new java.awt.Font("Courier", 0, 12));
        jMessageTextArea.setForeground(new java.awt.Color(204, 0, 51));
        jMessageTextArea.setRows(5);
        jMessageTextArea.setText("Create a shared lib. to represent the dynamics \nof your model (.dll on Windows, .so on linux). \nUsing SD/Fast, C Compiler and the files created \nby OpenSim (model.h, model.sd, sdfor.c).\nPlace the generated shared library in your path.");
        jMessageTextArea.setWrapStyleWord(true);
        jMessageTextArea.setBorder(null);
        jMessageTextArea.setFocusable(false);
        jMessageTextArea.setOpaque(false);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelSpecPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(layout.createSequentialGroup()
                .add(jMessageTextArea, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 339, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jModelSpecPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jMessageTextArea, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 163, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jDynamicsDirTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDynamicsDirTextFieldActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jDynamicsDirTextFieldActionPerformed

    private void jBrowseForDynamicsDirButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseForDynamicsDirButtonActionPerformed
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(this.getClass()).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jDynamicsDirTextField.setText(dlog.getSelectedFile().getAbsolutePath());
            Preferences.userNodeForPackage(this.getClass()).put("WorkDirectory", dlog.getSelectedFile().getParent());
        }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowseForDynamicsDirButtonActionPerformed

    private void jBrowse4ModelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowse4ModelButtonActionPerformed
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(this.getClass()).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Model to write dynamics for"));
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jModelTextField.setText(dlog.getSelectedFile().getAbsolutePath());
            Preferences.userNodeForPackage(this.getClass()).put("WorkDirectory", dlog.getSelectedFile().getParent());
        }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowse4ModelButtonActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBrowse4ModelButton;
    private javax.swing.JButton jBrowseForDynamicsDirButton;
    private javax.swing.JCheckBox jCreateParamsCheckBox;
    private javax.swing.JTextField jDynamicsDirTextField;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JTextArea jMessageTextArea;
    private javax.swing.JPanel jModelSpecPanel;
    private javax.swing.JTextField jModelTextField;
    // End of variables declaration//GEN-END:variables
    void updateWorkflow(WorkflowDescriptor descriptor) {
    }

    void updatePanel(WorkflowDescriptor aDescriptor) {
        // file is the output file from MarkerPlacement by default
        SimmMarkerPlacementParams params = aDescriptor.getSubject().getMarkerPlacementParams();
        jModelTextField.setText(aDescriptor.getSubject().getPathToSubject()+params.getOutputModelFileName());
        jDynamicsDirTextField.setText(aDescriptor.getSubject().getPathToSubject());
    }

    public void appendMessage(String message) {
        jMessageTextArea.append(message);
        repaint();
    }
    /**
     * Query the form for the data we need to perform SaveDynamics
     */
    public String getModelFilename()
    {
        return jModelTextField.getText();
    }
    
    public String getDynamicsDirectory()
    {
        return jDynamicsDirTextField.getText();
    }
    public boolean getWriteParamsFlag()
    {
        return jCreateParamsCheckBox.isSelected();
    }
}

