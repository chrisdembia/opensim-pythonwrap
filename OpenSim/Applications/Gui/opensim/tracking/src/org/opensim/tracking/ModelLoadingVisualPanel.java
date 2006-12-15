/*
 * ModelLoadingVisualPanel.java
 *
 * Created on September 17, 2006, 8:37 PM
 */

package org.opensim.tracking;

import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;
import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import org.opensim.modeling.SimmSubject;
import org.opensim.modeling.SimmGenericModelMaker;
import org.openide.windows.WindowManager;
import org.openide.util.NbBundle;
import org.opensim.modeling.MarkerSet;
import org.opensim.utils.FileUtils;
import org.opensim.utils.TheApp;

/**
 *
 * @author  adminxp
 */
public class ModelLoadingVisualPanel extends workflowVisualPanelBase {
    
    boolean ownModel;
    boolean ownMarkers;
    String fullModelFileName;
    WorkflowDescriptor aDescriptor; // Cache the descriptor so that we can update it

    /**
     * Creates new form ModelLoadingVisualPanel
     */
    public ModelLoadingVisualPanel(workflowWizardPanelBase basePanel) {
        super(basePanel);
        initComponents();
    }
    
    /**
     * return visible name of the Panel
     * use trailing "*" to indicate executed tasks
     */
    public String getName() {
        String baseName = NbBundle.getMessage(ModelLoadingVisualPanel.class, "CTL_LoadGenericModel");
        return baseName;
    }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        buttonGroup1 = new javax.swing.ButtonGroup();
        buttonGroup2 = new javax.swing.ButtonGroup();
        jSubjectFilePanel2 = new javax.swing.JPanel();
        jLabel9 = new javax.swing.JLabel();
        jSubjectFileTextField2 = new javax.swing.JTextField();
        jAgeLabel2 = new javax.swing.JLabel();
        jAgeTextField2 = new javax.swing.JTextField();
        jWeightLabel2 = new javax.swing.JLabel();
        jWeightTextField2 = new javax.swing.JTextField();
        jHeightLabel2 = new javax.swing.JLabel();
        jHeightTextField2 = new javax.swing.JTextField();
        jGenderLabel2 = new javax.swing.JLabel();
        jGenderTextField2 = new javax.swing.JTextField();
        jGetSubjectFileButton3 = new javax.swing.JButton();
        jPanel5 = new javax.swing.JPanel();
        jModelDefaultRadioButton2 = new javax.swing.JRadioButton();
        jModelOwnRadioButton2 = new javax.swing.JRadioButton();
        jBrowseForModelButton2 = new javax.swing.JButton();
        jModelNameTextField2 = new javax.swing.JTextField();
        jPanel6 = new javax.swing.JPanel();
        jDefaultMarkersRadioButton2 = new javax.swing.JRadioButton();
        jOwnMarkersRadioButton2 = new javax.swing.JRadioButton();
        jOwnMarkersTextField2 = new javax.swing.JTextField();
        jMarkersNameButton2 = new javax.swing.JButton();
        jScrollPane3 = new javax.swing.JScrollPane();
        jMessageTextArea2 = new javax.swing.JTextArea();

        jSubjectFilePanel2.setBorder(javax.swing.BorderFactory.createTitledBorder("Scale setup file"));
        jLabel9.setText("Setup file");

        jSubjectFileTextField2.setToolTipText("Prepared workflow file");
        jSubjectFileTextField2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jSubjectFileTextField2ActionPerformed(evt);
            }
        });

        jAgeLabel2.setText("Age");

        jAgeTextField2.setEditable(false);

        jWeightLabel2.setText("Weight");

        jWeightTextField2.setEditable(false);

        jHeightLabel2.setText("Height");

        jHeightTextField2.setEditable(false);

        jGenderLabel2.setText("Gender");

        jGenderTextField2.setEditable(false);

        jGetSubjectFileButton3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/FolderOpen.gif")));
        jGetSubjectFileButton3.setToolTipText("Browse...");
        jGetSubjectFileButton3.setAutoscrolls(true);
        jGetSubjectFileButton3.setBorderPainted(false);
        jGetSubjectFileButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jGetSubjectFileButton3ActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jSubjectFilePanel2Layout = new org.jdesktop.layout.GroupLayout(jSubjectFilePanel2);
        jSubjectFilePanel2.setLayout(jSubjectFilePanel2Layout);
        jSubjectFilePanel2Layout.setHorizontalGroup(
            jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSubjectFilePanel2Layout.createSequentialGroup()
                .addContainerGap()
                .add(jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jSubjectFilePanel2Layout.createSequentialGroup()
                        .add(jLabel9)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jSubjectFileTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 231, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jGetSubjectFileButton3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jSubjectFilePanel2Layout.createSequentialGroup()
                        .add(jAgeLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jAgeTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 41, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jWeightLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jWeightTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 33, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jHeightLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jHeightTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 44, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jGenderLabel2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jGenderTextField2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 74, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jSubjectFilePanel2Layout.setVerticalGroup(
            jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSubjectFilePanel2Layout.createSequentialGroup()
                .add(15, 15, 15)
                .add(jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, jSubjectFilePanel2Layout.createSequentialGroup()
                        .add(jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                            .add(jGetSubjectFileButton3)
                            .add(jSubjectFileTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 17, Short.MAX_VALUE)
                        .add(jSubjectFilePanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                            .add(jAgeLabel2)
                            .add(jWeightLabel2)
                            .add(jWeightTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                            .add(jHeightLabel2)
                            .add(jHeightTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                            .add(jGenderLabel2)
                            .add(jAgeTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                            .add(jGenderTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                    .add(jSubjectFilePanel2Layout.createSequentialGroup()
                        .add(jLabel9)
                        .add(39, 39, 39))))
        );

        jPanel5.setBorder(javax.swing.BorderFactory.createTitledBorder("Model selection"));
        buttonGroup1.add(jModelDefaultRadioButton2);
        jModelDefaultRadioButton2.setSelected(true);
        jModelDefaultRadioButton2.setText("Use default model");
        jModelDefaultRadioButton2.setToolTipText("Use model from subject file (if specified) or the default model");
        jModelDefaultRadioButton2.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelDefaultRadioButton2.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jModelDefaultRadioButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jModelDefaultRadioButton2ActionPerformed(evt);
            }
        });

        buttonGroup1.add(jModelOwnRadioButton2);
        jModelOwnRadioButton2.setText("Use own model");
        jModelOwnRadioButton2.setToolTipText("Provide your own generic model");
        jModelOwnRadioButton2.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jModelOwnRadioButton2.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jModelOwnRadioButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jModelOwnRadioButton2ActionPerformed(evt);
            }
        });

        jBrowseForModelButton2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/FolderOpen.gif")));
        jBrowseForModelButton2.setToolTipText("Browse...");
        jBrowseForModelButton2.setBorderPainted(false);
        jBrowseForModelButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBrowseForModelButton2ActionPerformed(evt);
            }
        });

        jModelNameTextField2.setEditable(false);
        jModelNameTextField2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jModelNameTextField2ActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jPanel5Layout = new org.jdesktop.layout.GroupLayout(jPanel5);
        jPanel5.setLayout(jPanel5Layout);
        jPanel5Layout.setHorizontalGroup(
            jPanel5Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel5Layout.createSequentialGroup()
                .add(jPanel5Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jPanel5Layout.createSequentialGroup()
                        .add(jModelOwnRadioButton2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jModelNameTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 193, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jBrowseForModelButton2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jModelDefaultRadioButton2))
                .addContainerGap(33, Short.MAX_VALUE))
        );
        jPanel5Layout.setVerticalGroup(
            jPanel5Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(org.jdesktop.layout.GroupLayout.TRAILING, jPanel5Layout.createSequentialGroup()
                .addContainerGap()
                .add(jModelDefaultRadioButton2)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .add(jPanel5Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jModelOwnRadioButton2)
                    .add(jModelNameTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jBrowseForModelButton2)))
        );

        jPanel6.setBorder(javax.swing.BorderFactory.createTitledBorder("Marker selection "));
        buttonGroup2.add(jDefaultMarkersRadioButton2);
        jDefaultMarkersRadioButton2.setSelected(true);
        jDefaultMarkersRadioButton2.setText("Use default markers");
        jDefaultMarkersRadioButton2.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jDefaultMarkersRadioButton2.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jDefaultMarkersRadioButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDefaultMarkersRadioButton2ActionPerformed(evt);
            }
        });

        buttonGroup2.add(jOwnMarkersRadioButton2);
        jOwnMarkersRadioButton2.setText("Use own markers");
        jOwnMarkersRadioButton2.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jOwnMarkersRadioButton2.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jOwnMarkersRadioButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jOwnMarkersRadioButton2ActionPerformed(evt);
            }
        });

        jOwnMarkersTextField2.setEditable(false);
        jOwnMarkersTextField2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jOwnMarkersTextField2ActionPerformed(evt);
            }
        });

        jMarkersNameButton2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/swingui/FolderOpen.gif")));
        jMarkersNameButton2.setToolTipText("Browse...");
        jMarkersNameButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMarkersNameButton2ActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jPanel6Layout = new org.jdesktop.layout.GroupLayout(jPanel6);
        jPanel6.setLayout(jPanel6Layout);
        jPanel6Layout.setHorizontalGroup(
            jPanel6Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel6Layout.createSequentialGroup()
                .add(jPanel6Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jPanel6Layout.createSequentialGroup()
                        .add(jOwnMarkersRadioButton2)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jOwnMarkersTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 186, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jMarkersNameButton2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jDefaultMarkersRadioButton2))
                .addContainerGap(30, Short.MAX_VALUE))
        );
        jPanel6Layout.setVerticalGroup(
            jPanel6Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel6Layout.createSequentialGroup()
                .add(jDefaultMarkersRadioButton2)
                .add(14, 14, 14)
                .add(jPanel6Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jOwnMarkersRadioButton2)
                    .add(jMarkersNameButton2)
                    .add(jOwnMarkersTextField2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jScrollPane3.setBorder(null);
        jScrollPane3.setForeground(new java.awt.Color(204, 0, 51));
        jScrollPane3.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        jScrollPane3.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
        jScrollPane3.setEnabled(false);
        jScrollPane3.setFocusable(false);
        jMessageTextArea2.setBackground(new java.awt.Color(236, 233, 216));
        jMessageTextArea2.setColumns(20);
        jMessageTextArea2.setEditable(false);
        jMessageTextArea2.setForeground(new java.awt.Color(204, 0, 51));
        jMessageTextArea2.setRows(5);
        jMessageTextArea2.setBorder(null);
        jMessageTextArea2.setFocusable(false);
        jMessageTextArea2.setOpaque(false);
        jScrollPane3.setViewportView(jMessageTextArea2);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSubjectFilePanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(jPanel5, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(jPanel6, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(org.jdesktop.layout.GroupLayout.TRAILING, jScrollPane3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 375, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(jSubjectFilePanel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel5, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel6, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jScrollPane3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 80, Short.MAX_VALUE)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jOwnMarkersTextField2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jOwnMarkersTextField2ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jOwnMarkersTextField2ActionPerformed

    private void jModelNameTextField2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jModelNameTextField2ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jModelNameTextField2ActionPerformed

    private void jMarkersNameButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMarkersNameButton2ActionPerformed
        useOwnMarkers();
// TODO add your handling code here:
    }//GEN-LAST:event_jMarkersNameButton2ActionPerformed

    private void jOwnMarkersRadioButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jOwnMarkersRadioButton2ActionPerformed
        useOwnMarkers();
// TODO add your handling code here:
    }//GEN-LAST:event_jOwnMarkersRadioButton2ActionPerformed

    private void jDefaultMarkersRadioButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDefaultMarkersRadioButton2ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jDefaultMarkersRadioButton2ActionPerformed

    private void jBrowseForModelButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBrowseForModelButton2ActionPerformed
// TODO add your handling code here:
        useOwnModel();
    }//GEN-LAST:event_jBrowseForModelButton2ActionPerformed

    private void jModelOwnRadioButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jModelOwnRadioButton2ActionPerformed
       useOwnModel();
// TODO add your handling code here:
    }//GEN-LAST:event_jModelOwnRadioButton2ActionPerformed

    private void jModelDefaultRadioButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jModelDefaultRadioButton2ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jModelDefaultRadioButton2ActionPerformed

    private void jGetSubjectFileButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jGetSubjectFileButton3ActionPerformed
       String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        
        dlog.setDialogTitle(NbBundle.getMessage(ModelLoadingVisualPanel.class, "CTL_OpenSubjectFileDlgTitle"));
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Select setup file for model selection and scaling"));
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jSubjectFileTextField2.setText(dlog.getSelectedFile().getAbsolutePath());
            aDescriptor.setSubjectFile(dlog.getSelectedFile().getAbsolutePath());
            Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
            updatePanel(aDescriptor);
        }
        repaint();  // Refresh display after any new dialog is braught down
 // TODO add your handling code here:
        
    }//GEN-LAST:event_jGetSubjectFileButton3ActionPerformed

    private void jSubjectFileTextField2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jSubjectFileTextField2ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jSubjectFileTextField2ActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.ButtonGroup buttonGroup2;
    private javax.swing.JLabel jAgeLabel2;
    private javax.swing.JTextField jAgeTextField2;
    private javax.swing.JButton jBrowseForModelButton2;
    private javax.swing.JRadioButton jDefaultMarkersRadioButton2;
    private javax.swing.JLabel jGenderLabel2;
    private javax.swing.JTextField jGenderTextField2;
    private javax.swing.JButton jGetSubjectFileButton3;
    private javax.swing.JLabel jHeightLabel2;
    private javax.swing.JTextField jHeightTextField2;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JButton jMarkersNameButton2;
    private javax.swing.JTextArea jMessageTextArea2;
    private javax.swing.JRadioButton jModelDefaultRadioButton2;
    private javax.swing.JTextField jModelNameTextField2;
    private javax.swing.JRadioButton jModelOwnRadioButton2;
    private javax.swing.JRadioButton jOwnMarkersRadioButton2;
    private javax.swing.JTextField jOwnMarkersTextField2;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JPanel jSubjectFilePanel2;
    private javax.swing.JTextField jSubjectFileTextField2;
    private javax.swing.JLabel jWeightLabel2;
    private javax.swing.JTextField jWeightTextField2;
    // End of variables declaration//GEN-END:variables
    private void jModelDefaultRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                         
// TODO add your handling code here:
        // Reset fields to default model ones
        setSubjectInfo(null);
        
    }                                                        

    private void jMarkersNameButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                   
// TODO add your handling code here:
       useOwnMarkers();
    }                                                  

    private void jOwnMarkersRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                       
// TODO add your handling code here:
        useOwnMarkers();
    }                                                      

    private void jBrowseForModelButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                      
// TODO add your handling code here:
        useOwnModel();

    }                                                     

    private void jModelOwnRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                     
// TODO add your handling code here:
        useOwnModel();
    }                                                    

    private void jDefaultMarkersRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                           
// TODO add your handling code here:
    }                                                          

    private void jSubjectFileTextFieldActionPerformed(java.awt.event.ActionEvent evt) {                                                      
// TODO add your handling code here:
    }                                                     
    
   /**
    * Handle user switching to use his own model either by browsing or using the dario button
    * @returns true on success
    */
    private boolean  useOwnModel() {
        
        boolean selectModel = false;
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(".xml, .osim", "load OpenSim model file"));
       
        String modelFile=null;

        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            modelFile= dlog.getSelectedFile().getAbsolutePath();
            setModelFile(modelFile);
            Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());

        }
        
        setGuiCanAdvance(checkValidForm());
        return selectModel;
   }
   /**
    * One common place to set Model file (either from Browse... or from the radio button)
    */
    private void setModelFile(String modelFile) {
        if (modelFile!= null){
            jModelOwnRadioButton2.setSelected(true);
            /**
            String parentPath = new File(modelFile).getParent();
            if (parentPath != null){
                jModelNameTextField2.setText(modelFile.substring(parentPath.length()+1));
                aDescriptor.getSubject().setPathToSubject(parentPath+File.separator);
            }
            else
             **/
                jModelNameTextField2.setText(modelFile);
            // Update GUI accordingly
            ownModel = true;
        }
        else {
            jModelDefaultRadioButton2.setSelected(true);
            ownModel = false;
        }

    }
    // Repeat for markers
    private boolean  useOwnMarkers() {

        boolean selectMarkers = false;
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Select markers file"));

        String markersFile=null;
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            markersFile= dlog.getSelectedFile().getAbsolutePath();
            selectMarkers = true;
             Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
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
            jOwnMarkersRadioButton2.setSelected(true);
            String parentPath = new File(markersFile).getParent();
            if (parentPath != null)
                jOwnMarkersTextField2.setText(markersFile.substring(parentPath.length()+1));
            else
                 jOwnMarkersTextField2.setText(markersFile);
       }
        else
            jDefaultMarkersRadioButton2.setSelected(true);
    }

    private void setSubjectInfo(SimmSubject subject) {
        if (subject!= null){
            /* Restructure
            Property massProp = subject.getPropertySet().get("mass");
            boolean def = massProp.getUseDefault();
            if (subject.getMass()!=subject.getDefaultMass()){
                jWeightTextField2.setText(String.valueOf(subject.getSubjectMass()));
                jHeightTextField2.setText(String.valueOf(subject.getSubjectHeight()));
                jAgeTextField2.setText(String.valueOf(subject.getSubjectAge()));
            }
             **/
            this.firePropertyChange("Model_Defined", false, true);
        }
        else {
            jWeightTextField2.setText("");
            jHeightTextField2.setText("");
            jAgeTextField2.setText("");
            jModelNameTextField2.setText("");
        }
    }

    public boolean hasModel()
    {
        return (!(jModelNameTextField2.getText().equalsIgnoreCase("*.xml") || 
                jModelNameTextField2.getText().equals("")));
    }
        
    private void jGetSubjectFileButtonActionPerformed(ActionEvent evt) {
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        
        dlog.setDialogTitle(NbBundle.getMessage(ModelLoadingVisualPanel.class, "CTL_OpenSubjectFileDlgTitle"));
        dlog.setFileFilter(FileUtils.getFileFilter(".xml", "Select setup file for scaling_ik"));
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            jSubjectFileTextField2.setText(dlog.getSelectedFile().getAbsolutePath());
            aDescriptor.setSubjectFile(dlog.getSelectedFile().getAbsolutePath());
            Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
            updatePanel(aDescriptor);
        }
        repaint();  // Refresh display after any new dialog is braught down
    }
    
    public void appendMessage(String message)
    {
        jMessageTextArea2.append(message);
        invalidate();
        repaint();
    }

    /**
     * updatePanel updates the fields in the GUI based on the WorkflowDescriptor object
     */
    void updatePanel(WorkflowDescriptor aDescriptor) {
        this.aDescriptor = aDescriptor;
        SimmGenericModelMaker modelMaker = aDescriptor.getSubject().getGenericModelMaker();
         try {
        jModelNameTextField2.setToolTipText(modelMaker.getPropertySet().get("file_name").getComment());
            jOwnMarkersTextField2.setToolTipText(modelMaker.getPropertySet().get("MarkerSet").getComment());
        } catch (IOException ex) {
             TheApp.exitApp("Internal Error:Property does not exist in SimmGenericModelMaker");
         }
        if (aDescriptor.getUseOwnModel()){
            jModelOwnRadioButton2.setSelected(true);
            setModelFile(modelMaker.getModelFileName());
            setSubjectInfo(aDescriptor.dSubject);
        }
        else {
            jModelDefaultRadioButton2.setSelected(true);
            setSubjectInfo(null);
         }
        
        /* Restructure
        SimmMarkerSet markerSetObject = modelMaker.getMarkerSet();
        if (markerSetObject != null && markerSetObject.getInlined()==false){
            jOwnMarkersTextField2.setText(markerSetObject.getOffLineFileName());
            jOwnMarkersRadioButton2.setSelected(true);
        }
        if (aDescriptor.getUseOwnMarkers()){
            jOwnMarkersRadioButton2.setSelected(true);
        }
        else {
            jDefaultMarkersRadioButton2.setSelected(true);
        }**/
        setGuiCanAdvance(checkValidForm());
        
   }
    
    void updateWorkflow(WorkflowDescriptor descriptor){
        SimmGenericModelMaker params = descriptor.getSubject().getGenericModelMaker();
        if(!jModelNameTextField2.getText().equals("")){
            params.setModelFileName(jModelNameTextField2.getText());
            setModelFile(jModelNameTextField2.getText());
        }
        // We'll do the same for Markers when MarkerSet is exposed properly (bug 209)
        /*
        if(!jOwnMarkersTextField2.getText().equals("")){
            MarkerSet markerSet = new MarkerSet(jOwnMarkersTextField2.getText());
            descriptor.getModel().getDynamicsEngine().updateMarkerSet(markerSet);
       }*/
       
    };

    protected boolean checkValidForm() {

        return(!jModelNameTextField2.getText().equalsIgnoreCase(""));
    }

   public void checkConsistentPanel() {
      //Restructure
   }

 }
