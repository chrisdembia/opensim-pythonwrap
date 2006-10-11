package org.opensim.tracking;

import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import org.openide.windows.WindowManager;
import org.opensim.swingui.SwingWorker;
import org.opensim.utils.FileUtils;
import com.realisticDynamics.InvestigationRRA;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.awt.StatusDisplayer;
import org.opensim.modeling.Analysis;
import org.opensim.modeling.Model;
import org.opensim.utils.TheApp;
import org.opensim.view.editors.ObjectEditDialogMaker;

public final class ReduceResidualsVisualPanelPass1 extends workflowVisualPanelBase {
    
    /**
     * Creates new form ReduceResidualsVisualPanel
     */
    public ReduceResidualsVisualPanelPass1(workflowWizardPanelBase basePanel) {
        super(basePanel);
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 
    }
    
    public String getName() {
        return "Compute residuals";
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

        jRRAParamsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Pass 1, compute residuals"));
        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "Pass 1 settings file:");

        jBrowse4RRA1SetupButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/FolderOpen.gif")));
        jBrowse4RRA1SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowse4RRA1SetupButtonActionPerformed(evt);
            }
        });

        jEditRRA1SetupButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/editor.gif")));
        jEditRRA1SetupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jEditRRA1SetupButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jRRAParamsPanelLayout = new org.jdesktop.layout.GroupLayout(jRRAParamsPanel);
        jRRAParamsPanel.setLayout(jRRAParamsPanelLayout);
        jRRAParamsPanelLayout.setHorizontalGroup(
            jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanelLayout.createSequentialGroup()
                .add(jLabel2)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jRRAPass1SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 186, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jBrowse4RRA1SetupButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .add(6, 6, 6)
                .add(jEditRRA1SetupButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
        );
        jRRAParamsPanelLayout.setVerticalGroup(
            jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jRRAParamsPanelLayout.createSequentialGroup()
                .add(jRRAParamsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel2)
                    .add(jRRAPass1SetupFileTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowse4RRA1SetupButton)
                    .add(jEditRRA1SetupButton))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jRRAParamsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jRRAParamsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(262, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jEditRRA1SetupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jEditRRA1SetupButtonActionPerformed
          String setupFilename = jRRAPass1SetupFileTextField.getText();
          InvestigationRRA rra = new InvestigationRRA(setupFilename);
          new ObjectEditDialogMaker(rra, true).process();
          rra.print(setupFilename);
// TODO add your handling code here:
    }//GEN-LAST:event_jEditRRA1SetupButtonActionPerformed

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
    private javax.swing.JButton jEditRRA1SetupButton;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JPanel jRRAParamsPanel;
    private javax.swing.JTextField jRRAPass1SetupFileTextField;
    // End of variables declaration//GEN-END:variables
    void updateWorkflow(WorkflowDescriptor descriptor) {
        descriptor.setSetupRRA_pass1Filename(jRRAPass1SetupFileTextField.getText());
        
    }

    void updatePanel(WorkflowDescriptor aDescriptor) {
        jRRAPass1SetupFileTextField.setText(aDescriptor.getSetupRRA_pass1Filename());
    }

    public void appendMessage(String message) {
        
    }    
}

