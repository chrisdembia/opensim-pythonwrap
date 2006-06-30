package org.opensim.gait;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import javax.help.CSH;
import javax.help.HelpBroker;
import javax.help.HelpSet;
import javax.help.HelpSetException;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import org.opensim.modeling.SimmSubject;

public final class workflowVisualPanel1 extends JPanel {
    
    /** Creates new form workflowVisualPanel1 */
    public workflowVisualPanel1() {
        initComponents();
        putClientProperty("WizardPanel_helpURL",this.getClass().getResource("help/html/SubjectSpecificWorkflow.htm")); 


/*        URL url;
            url = this.getClass().getResource("help/help.hs");

            HelpSet hs;
            try {
                hs = new HelpSet(null, url);
                HelpBroker hb = hs.createHelpBroker();

                jButton3.addActionListener(new CSH.DisplayHelpFromSource(hb));
           } catch (HelpSetException ex) {
                ex.printStackTrace();
           }
*/
    }
    
    public String getName() {
        return "Load generic model";
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
        jButton1 = new javax.swing.JButton();
        jTextField1 = new javax.swing.JTextField();
        jTextField2 = new javax.swing.JTextField();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jTextField3 = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        jTextField6 = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        jTextField4 = new javax.swing.JTextField();
        jPanel2 = new javax.swing.JPanel();
        jDefaultMarkersRadioButton = new javax.swing.JRadioButton();
        jOwnMarkersRadioButton = new javax.swing.JRadioButton();
        jTextField5 = new javax.swing.JTextField();
        jButton2 = new javax.swing.JButton();
        jButton3 = new javax.swing.JButton();

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
        org.openide.awt.Mnemonics.setLocalizedText(jModelDefaultRadioButton, "Use default model");
        jModelDefaultRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelDefaultRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jModelOwnRadioButton, "Use own model");
        jModelOwnRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelOwnRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jButton1, "Browse...");

        jTextField2.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jLabel2, "Age");

        org.openide.awt.Mnemonics.setLocalizedText(jLabel3, "Weight");

        jTextField3.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jLabel5, "Height");

        jTextField6.setEditable(false);

        org.openide.awt.Mnemonics.setLocalizedText(jLabel4, "Gender");

        jTextField4.setEditable(false);

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
                                .add(jTextField1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 129, Short.MAX_VALUE)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jButton1)))
                        .addContainerGap(94, Short.MAX_VALUE))
                    .add(jPanel1Layout.createSequentialGroup()
                        .add(jLabel2)
                        .add(17, 17, 17)
                        .add(jTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 47, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel3)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jTextField3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 31, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(19, 19, 19)
                        .add(jLabel5)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jTextField6, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 44, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(24, 24, 24)
                        .add(jLabel4)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jTextField4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 48, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(38, Short.MAX_VALUE))))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .add(jModelDefaultRadioButton)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jModelOwnRadioButton)
                    .add(jButton1)
                    .add(jTextField1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 14, Short.MAX_VALUE)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel2)
                    .add(jTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabel3)
                    .add(jLabel5)
                    .add(jTextField3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jTextField6, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabel4)
                    .add(jTextField4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder("Marker Selection"));
        org.openide.awt.Mnemonics.setLocalizedText(jDefaultMarkersRadioButton, "use default markers");
        jDefaultMarkersRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jDefaultMarkersRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jDefaultMarkersRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDefaultMarkersRadioButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(jOwnMarkersRadioButton, "use own markers");
        jOwnMarkersRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jOwnMarkersRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.openide.awt.Mnemonics.setLocalizedText(jButton2, "Browse...");

        org.openide.awt.Mnemonics.setLocalizedText(jButton3, "Edit...");

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
                        .add(jTextField5, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 118, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jButton2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jButton3)))
                .addContainerGap(26, Short.MAX_VALUE))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel2Layout.createSequentialGroup()
                .add(jDefaultMarkersRadioButton)
                .add(14, 14, 14)
                .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOwnMarkersRadioButton)
                    .add(jTextField5, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jButton2)
                    .add(jButton3))
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

    private void jDefaultMarkersRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDefaultMarkersRadioButtonActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jDefaultMarkersRadioButtonActionPerformed

    private void jGetSubjectFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jGetSubjectFileButtonActionPerformed
        final JFileChooser dlog = new JFileChooser();
        
        dlog.setDialogTitle("Subject file to initialize workflow");
        dlog.setFileFilter(new XMLFileFilter());
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jSubjectFileTextField.setText(dlog.getSelectedFile().getAbsolutePath());
            // Create a subject instance
            SimmSubject subject = new SimmSubject(dlog.getSelectedFile().getAbsolutePath());
            
        }
        //else
        //subject = new SimmSubject();
    }//GEN-LAST:event_jGetSubjectFileButtonActionPerformed

    private void jSubjectFileTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jSubjectFileTextFieldActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jSubjectFileTextFieldActionPerformed
    

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JButton jButton3;
    private javax.swing.JRadioButton jDefaultMarkersRadioButton;
    private javax.swing.JButton jGetSubjectFileButton;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JRadioButton jModelDefaultRadioButton;
    private javax.swing.JRadioButton jModelOwnRadioButton;
    private javax.swing.JRadioButton jOwnMarkersRadioButton;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jSubjectFilePanel;
    private javax.swing.JTextField jSubjectFileTextField;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JTextField jTextField2;
    private javax.swing.JTextField jTextField3;
    private javax.swing.JTextField jTextField4;
    private javax.swing.JTextField jTextField5;
    private javax.swing.JTextField jTextField6;
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

}

