/*
 * SimmToOpenSimOptionsJPanel.java
 *
 * Created on July 21, 2007, 9:37 AM
 */

package org.opensim.view.actions;

/**
 *
 * @author  Ayman
 */
public class SimmToOpenSimOptionsJPanel extends javax.swing.JPanel {
    String[] DynamicsEngineNames = new String[]{    // internal names corresponding to names exposed in gui
        "SimmKinematicsEngine",
        "Simbody",
        "SDFast"
    };
    /** Creates new form SimmToOpenSimOptionsJPanel */
    public SimmToOpenSimOptionsJPanel() {
        initComponents();
        jntfileTextFieldAndChooser.setExtensionsAndDescription(".jnt", "SIMM joint file");
        mslfileTextFieldAndChooser.setExtensionsAndDescription(".msl", "SIMM muscle file");
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        angleUnitsButtonGroup = new javax.swing.ButtonGroup();
        buttonGroup1 = new javax.swing.ButtonGroup();
        jntfileTextFieldAndChooser = new org.opensim.swingui.FileTextFieldAndChooser();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        mslfileTextFieldAndChooser = new org.opensim.swingui.FileTextFieldAndChooser();
        jLabel4 = new javax.swing.JLabel();
        jEngineComboBox = new javax.swing.JComboBox();
        jRadioButtonDegrees = new javax.swing.JRadioButton();
        jLabel5 = new javax.swing.JLabel();
        jRadioButtonRadians = new javax.swing.JRadioButton();

        setBorder(javax.swing.BorderFactory.createTitledBorder("Import options"));
        jntfileTextFieldAndChooser.setToolTipText("location of .jnt file");

        jLabel1.setText("Joint file");

        jLabel2.setText("Muscle file");

        mslfileTextFieldAndChooser.setToolTipText("location of .msl file (optional and can be specified in jnt file header)");

        jLabel4.setText("Dynamics Engine for OpenSim Model:");

        jEngineComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "SIMM kinematics engine", "Simbody engine", "SDFast engine" }));

        jRadioButtonDegrees.setText("Degrees");
        jRadioButtonDegrees.setToolTipText("SIMM model is assumed in degrees");
        jRadioButtonDegrees.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jRadioButtonDegrees.setMargin(new java.awt.Insets(0, 0, 0, 0));

        jLabel5.setText("Angles in");

        jRadioButtonRadians.setSelected(true);
        jRadioButtonRadians.setText("Radians");
        jRadioButtonRadians.setToolTipText("Angles in SIMM model are assumed in radians");
        jRadioButtonRadians.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        jRadioButtonRadians.setMargin(new java.awt.Insets(0, 0, 0, 0));

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(layout.createSequentialGroup()
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(jLabel1)
                            .add(jLabel2)
                            .add(jLabel5))
                        .add(31, 31, 31)
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(org.jdesktop.layout.GroupLayout.TRAILING, jntfileTextFieldAndChooser, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 248, Short.MAX_VALUE)
                            .add(layout.createSequentialGroup()
                                .add(jRadioButtonDegrees)
                                .add(36, 36, 36)
                                .add(jRadioButtonRadians)
                                .addContainerGap())
                            .add(mslfileTextFieldAndChooser, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 248, Short.MAX_VALUE)))
                    .add(layout.createSequentialGroup()
                        .add(jLabel4)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jEngineComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jntfileTextFieldAndChooser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabel1))
                .add(10, 10, 10)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jLabel2)
                    .add(mslfileTextFieldAndChooser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(11, 11, 11)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel5)
                    .add(jRadioButtonDegrees)
                    .add(jRadioButtonRadians))
                .add(31, 31, 31)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel4, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 18, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jEngineComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.ButtonGroup angleUnitsButtonGroup;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JComboBox jEngineComboBox;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JRadioButton jRadioButtonDegrees;
    private javax.swing.JRadioButton jRadioButtonRadians;
    private org.opensim.swingui.FileTextFieldAndChooser jntfileTextFieldAndChooser;
    private org.opensim.swingui.FileTextFieldAndChooser mslfileTextFieldAndChooser;
    // End of variables declaration//GEN-END:variables
    String getJointFilename()
    {
        if (jntfileTextFieldAndChooser.getFileIsValid())
            return jntfileTextFieldAndChooser.getFileName();
        return null;
    }
    String getMslFilename()
    {
        if (mslfileTextFieldAndChooser.getFileIsValid())
            return mslfileTextFieldAndChooser.getFileName();
        return null;        
    }
    String getDynamicsEngine()
    {
        return DynamicsEngineNames[jEngineComboBox.getSelectedIndex()];
    }
    String getAngleConvention()
    {
        if (jRadioButtonDegrees.isSelected())
            return "Degrees";
        return "Radians";
    }
}
