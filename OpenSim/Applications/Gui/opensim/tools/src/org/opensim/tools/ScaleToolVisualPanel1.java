package org.opensim.tools;

import javax.swing.JPanel;
import org.opensim.modeling.SimmScalingParams;

public final class ScaleToolVisualPanel1 extends JPanel {
    
    /** Creates new form ScaleToolVisualPanel1 */
    public ScaleToolVisualPanel1() {
        initComponents();
    }
    
    public String getName() {
        return "Scale model ...";
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        commonScalePanel1 = new org.opensim.tools.CommonScalePanel();

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(commonScalePanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(commonScalePanel1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private org.opensim.tools.CommonScalePanel commonScalePanel1;
    // End of variables declaration//GEN-END:variables
 
    // Update display based on workflow changes
    void updateGUI(SimmScalingParams params) {
       commonScalePanel1.readFrom(params);
    }
    
    // Update Object based on GUI Choices
    void updateObject(SimmScalingParams params)
    {
        commonScalePanel1.writeTo(params);
    }
}

