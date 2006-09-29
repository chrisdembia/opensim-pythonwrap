package org.opensim.tracking;

import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import org.openide.windows.WindowManager;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.FileUtils;
import com.realisticDynamics.InvestigationRRA;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.opensim.utils.TheApp;
import org.opensim.view.editors.ObjectEditDialogMaker;

public final class ReduceResidualsVisualPanel extends workflowVisualPanelBase {
    
    /**
     * Creates new form ReduceResidualsVisualPanel
     */
    public ReduceResidualsVisualPanel(workflowWizardPanelBase basePanel) {
        super(basePanel);
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 
    }
    
    public String getName() {
        return "Reduce residuals";
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jRRAParamsPanel = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        jRRAPass1SetupFileTextField = new javax.swing.JTextField();
        jBrowse4RRA1SetupButton = new javax.swing.JButton();
        jEditRRA1SetupButton = new javax.swing.JButton();
        jRunRRAPass1Button = new javax.swing.JButton();
        jRRAParamsPanel1 = new javax.swing.JPanel();
        jLabel3 = new javax.swing.JLabel();
        jRRAPass2SetupFileTextField = new javax.swing.JTextField();
        jBrowse4RRA2SetupButton = new javax.swing.JButton();
        jEditRRA2SetupButton = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        jTextField4 = new javax.swing.JTextField();
        jButton6 = new javax.swing.JButton();
        jRunPass2Button = new javax.swing.JButton();

        jRRAParamsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Pass 1, Compute Residuals"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "Pass 1 settings file:");

        org.openide.awt.Mnemonics.setLocalizedText(jBrowse4RRA1SetupButton, "Browse...");
        jBrowse4RRA1SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowse4RRA1SetupButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jEditRRA1SetupButton, "jButton4");
        jEditRRA1SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jEditRRA1SetupButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jRunRRAPass1Button, "Run Pass 1");
        jRunRRAPass1Button.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRunRRAPass1ButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jRRAParamsPanelLayout = new org.jdesktop.layout.GroupLayout(jRRAParamsPanel);
        jRRAParamsPanel.setLayout(jRRAParamsPanelLayout);
        jRRAParamsPanelLayout.setHorizontalGroup(
            jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanelLayout.createSequentialGroup()
                .add(jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jRRAParamsPanelLayout.createSequentialGroup()
                        .add(jLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jRRAPass1SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 159, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jBrowse4RRA1SetupButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 31, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jEditRRA1SetupButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 38, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jRRAParamsPanelLayout.createSequentialGroup()
                        .add(123, 123, 123)
                        .add(jRunRRAPass1Button)))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jRRAParamsPanelLayout.setVerticalGroup(
            jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanelLayout.createSequentialGroup()
                .add(jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jBrowse4RRA1SetupButton)
                    .add(jLabel2)
                    .add(jRRAPass1SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jEditRRA1SetupButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 17, Short.MAX_VALUE)
                .add(jRunRRAPass1Button))
        );

        jRRAParamsPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder("Pass 2, alter motion to reduce residuals"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel3, "Pass 2 settings file:");

        org.openide.awt.Mnemonics.setLocalizedText(jBrowse4RRA2SetupButton, "jButton3");
        jBrowse4RRA2SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowse4RRA2SetupButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jEditRRA2SetupButton, "jButton5");
        jEditRRA2SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jEditRRA2SetupButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jLabel4, "Output Motion file: ");

        org.openide.awt.Mnemonics.setLocalizedText(jButton6, "jButton6");

        org.jdesktop.layout.GroupLayout jRRAParamsPanel1Layout = new org.jdesktop.layout.GroupLayout(jRRAParamsPanel1);
        jRRAParamsPanel1.setLayout(jRRAParamsPanel1Layout);
        jRRAParamsPanel1Layout.setHorizontalGroup(
            jRRAParamsPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanel1Layout.createSequentialGroup()
                .add(jRRAParamsPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jRRAParamsPanel1Layout.createSequentialGroup()
                        .add(jLabel3)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jRRAPass2SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 155, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jBrowse4RRA2SetupButton, 0, 0, Short.MAX_VALUE))
                    .add(jRRAParamsPanel1Layout.createSequentialGroup()
                        .add(jLabel4)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jTextField4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 155, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jButton6, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 35, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jEditRRA2SetupButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 38, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        jRRAParamsPanel1Layout.setVerticalGroup(
            jRRAParamsPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .add(jRRAParamsPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel3)
                    .add(jRRAPass2SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowse4RRA2SetupButton)
                    .add(jEditRRA2SetupButton))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jRRAParamsPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel4)
                    .add(jTextField4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jButton6))
                .addContainerGap(22, Short.MAX_VALUE))
        );

        org.openide.awt.Mnemonics.setLocalizedText(jRunPass2Button, "Run Pass 2");
        jRunPass2Button.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRunPass2ButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jRRAParamsPanel1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, jRRAParamsPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(layout.createSequentialGroup()
                        .add(137, 137, 137)
                        .add(jRunPass2Button)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jRRAParamsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .add(15, 15, 15)
                .add(jRRAParamsPanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jRunPass2Button)
                .addContainerGap(76, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jRunPass2ButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRunPass2ButtonActionPerformed
        final InvestigationRRA rra = new InvestigationRRA(jRRAPass2SetupFileTextField.getText());
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Solving RRA pass 2 ");
        progressHandle.start();

        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                progressHandle.progress((int)rra.getModel().getTime()*100);
                rra.run();
                return this;
            };
            public void finished() {
               progressHandle.finish();
            };
         };
        worker.start();
        appendMessage("Finished running step 2 of RRA");
// TODO add your handling code here:
    }//GEN-LAST:event_jRunPass2ButtonActionPerformed

    private void jEditRRA1SetupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jEditRRA1SetupButtonActionPerformed
          String setupFilename = jRRAPass1SetupFileTextField.getText();
          InvestigationRRA rra = new InvestigationRRA(setupFilename);
          new ObjectEditDialogMaker(rra, true).process();
          rra.print(setupFilename);
// TODO add your handling code here:
    }//GEN-LAST:event_jEditRRA1SetupButtonActionPerformed

    private void jEditRRA2SetupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jEditRRA2SetupButtonActionPerformed
          String setupFilename = jRRAPass2SetupFileTextField.getText();
          InvestigationRRA rra = new InvestigationRRA(setupFilename);
          new ObjectEditDialogMaker(rra, true).process();
          rra.print(setupFilename);
// TODO add your handling code here:
    }//GEN-LAST:event_jEditRRA2SetupButtonActionPerformed

    private void jRunRRAPass1ButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRunRRAPass1ButtonActionPerformed
// TODO add your handling code here:
        final InvestigationRRA rra = new InvestigationRRA(jRRAPass1SetupFileTextField.getText());
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Solving RRA pass 1 ");
        progressHandle.start();

        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                progressHandle.progress((int)rra.getModel().getTime()*100);
                rra.run();
                return this;
            };
            public void finished() {
               progressHandle.finish();
            };
         };
        worker.start();
        appendMessage("Finished running step 1 of RRA");;
    }//GEN-LAST:event_jRunRRAPass1ButtonActionPerformed

    private void jBrowse4RRA2SetupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowse4RRA2SetupButtonActionPerformed
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "RRA Pass2 settings file"));
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
           String setupFilename = dlog.getSelectedFile().getAbsolutePath();
            jRRAPass2SetupFileTextField.setText(setupFilename);
         }
// TODO add your handling code here:
    }//GEN-LAST:event_jBrowse4RRA2SetupButtonActionPerformed

    private void jBrowse4RRA1SetupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowse4RRA1SetupButtonActionPerformed
// TODO add your handling code here:
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "RRA Pass1 settings file"));
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            String setupFilename = dlog.getSelectedFile().getAbsolutePath();
            jRRAPass1SetupFileTextField.setText(setupFilename);
        }
    }//GEN-LAST:event_jBrowse4RRA1SetupButtonActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBrowse4RRA1SetupButton;
    private javax.swing.JButton jBrowse4RRA2SetupButton;
    private javax.swing.JButton jButton6;
    private javax.swing.JButton jEditRRA1SetupButton;
    private javax.swing.JButton jEditRRA2SetupButton;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JPanel jRRAParamsPanel;
    private javax.swing.JPanel jRRAParamsPanel1;
    private javax.swing.JTextField jRRAPass1SetupFileTextField;
    private javax.swing.JTextField jRRAPass2SetupFileTextField;
    private javax.swing.JButton jRunPass2Button;
    private javax.swing.JButton jRunRRAPass1Button;
    private javax.swing.JTextField jTextField4;
    // End of variables declaration//GEN-END:variables
    void updateWorkflow(WorkflowDescriptor descriptor) {
        descriptor.setSetupRRA_pass1Filename(jRRAPass1SetupFileTextField.getText());
        descriptor.setSetupRRA_pass2Filename(jRRAPass2SetupFileTextField.getText());
        
    }

    void updatePanel(WorkflowDescriptor aDescriptor) {
        jRRAPass1SetupFileTextField.setText(aDescriptor.getSetupRRA_pass1Filename());
        jRRAPass2SetupFileTextField.setText(aDescriptor.getSetupRRA_pass2Filename());
    }

    public void appendMessage(String message) {
        
    }
    
}

