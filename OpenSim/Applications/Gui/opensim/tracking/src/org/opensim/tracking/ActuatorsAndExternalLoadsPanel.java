/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * ActuatorsAndExternalLoadsPanel.java
 *
 * Created on July 23, 2007, 7:32 PM
 */

package org.opensim.tracking;

import java.awt.Color;
import java.awt.Component;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Vector;
import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JPanel;
import org.jdesktop.layout.GroupLayout;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Model;
import org.opensim.swingui.ComponentTitledBorder;
import org.opensim.swingui.MultiFileSelectorPanel;
import org.opensim.utils.FileUtils;

/**
 *
 * @author  erang
 */
public class ActuatorsAndExternalLoadsPanel extends javax.swing.JPanel {
  
   private JCheckBox externalLoadsPanelCheckBox = new JCheckBox(new EnableExternalLoadsAction());
   class EnableExternalLoadsAction extends AbstractAction {
      public EnableExternalLoadsAction() { super("External Loads"); }
      public void actionPerformed(ActionEvent evt) { toolModel.setExternalLoadsEnabled(((JCheckBox)evt.getSource()).isSelected()); }
   }

   AbstractToolModelWithExternalLoads toolModel;
   Model model;
   boolean internalTrigger = false;
   private NumberFormat numFormat = NumberFormat.getInstance();

   /** Creates new form ActuatorsAndExternalLoadsPanel */
   public ActuatorsAndExternalLoadsPanel(AbstractToolModelWithExternalLoads toolModel, Model model, boolean includeActuatorsPanel) {
      this.toolModel = toolModel;
      this.model = model;

      if (numFormat instanceof DecimalFormat) {
        ((DecimalFormat) numFormat).applyPattern("#,##0.#########");
      }

      initComponents();
      bindPropertiesToComponents();
      
      if(!includeActuatorsPanel) actuatorsPanel.setVisible(false);

      externalLoadsFileName.setExtensionsAndDescription(".mot,.sto", "External loads data");
      externalLoadsModelKinematicsFileName.setExtensionsAndDescription(".mot,.sto", "Model kinematics for external loads"); 

      // Add checkbox titled borders to external loads panel
      externalLoadsPanelCheckBox.setForeground(new Color(0,70,213));
      externalLoadsPanel.setBorder(new ComponentTitledBorder(externalLoadsPanelCheckBox, externalLoadsPanel, BorderFactory.createEtchedBorder()));

      // Re-layout panels after we've removed various parts...
      ((GroupLayout)this.getLayout()).layoutContainer(this);
      
      // Default to Append rather than replace AcuatorSet
      toolModel.setReplaceForceSet(false);
      updatePanel();
   }

   private void bindPropertiesToComponents() {
      ToolCommon.bindProperty(toolModel.getTool(), "force_set_files", actuatorSetFiles);
      ToolCommon.bindProperty(toolModel.getTool(), "external_loads_file", externalLoadsFileName);
      ToolCommon.bindProperty(toolModel.getTool(), "external_loads_body1", externalLoadsBody1);
      ToolCommon.bindProperty(toolModel.getTool(), "external_loads_body2", externalLoadsBody2);
      ToolCommon.bindProperty(toolModel.getTool(), "external_loads_model_kinematics_file", externalLoadsModelKinematicsFileName);
      ToolCommon.bindProperty(toolModel.getTool(), "lowpass_cutoff_frequency_for_load_kinematics", cutoffFrequency);
   }

   private void setEnabled(JPanel panel, boolean enabled) {
      for(Component comp : panel.getComponents()) {
         comp.setEnabled(enabled);
         if(comp instanceof JPanel) setEnabled((JPanel)comp, enabled);
      }
   }

   public void updatePanel() {
      internalTrigger = true;

      setEnabled(actuatorsPanel, true);
      setEnabled(externalLoadsPanel, true);

      //---------------------------------------------------------------------
      // Actuators
      //---------------------------------------------------------------------
      buttonGroup1.setSelected(toolModel.getReplaceForceSet() ? 
                               replaceActuatorSetRadioButton.getModel() : 
                               appendActuatorSetRadioButton.getModel(), true);

      String str = "";
      for(int i=0; i<toolModel.getForceSetFiles().getSize(); i++)
         str += (i>0?", ":"") + toolModel.getForceSetFiles().getitem(i);
      actuatorSetFiles.setText(str);

      //---------------------------------------------------------------------
      // External loads
      //---------------------------------------------------------------------

      externalLoadsPanelCheckBox.setSelected(toolModel.getExternalLoadsEnabled());
      if(!toolModel.getExternalLoadsEnabled()) setEnabled(externalLoadsPanel, false);

      // Update combo boxes with body names
      for(JComboBox comboBox : new JComboBox[]{externalLoadsBody1, externalLoadsBody2}) {
         comboBox.removeAllItems();
         if(model==null) continue;
         BodySet bodySet = model.getBodySet();
         if(bodySet==null) continue;
         for(int i=0; i<bodySet.getSize(); i++) comboBox.addItem(bodySet.get(i).getName());
         String selectedBody = (comboBox==externalLoadsBody1) ? toolModel.getExternalLoadsBody1() : toolModel.getExternalLoadsBody2();
         int index = bodySet.getIndex(selectedBody);
         comboBox.setSelectedIndex(index);
      }

      externalLoadsFileName.setFileName(toolModel.getExternalLoadsFileName(),false);
      externalLoadsModelKinematicsFileName.setFileName(toolModel.getExternalLoadsModelKinematicsFileName(),false);
      if(!toolModel.getFilterLoadKinematics()) {
         filterModelKinematics.setSelected(false);
         cutoffFrequency.setText("");
         cutoffFrequency.setEnabled(false);
      } else {
         filterModelKinematics.setSelected(true);
         cutoffFrequency.setText(numFormat.format(toolModel.getLowpassCutoffFrequencyForLoadKinematics()));
      }

      internalTrigger = false;
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        buttonGroup1 = new javax.swing.ButtonGroup();
        externalLoadsPanel = new javax.swing.JPanel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        filterModelKinematics = new javax.swing.JCheckBox();
        externalLoadsBody1 = new javax.swing.JComboBox();
        jLabel5 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        externalLoadsBody2 = new javax.swing.JComboBox();
        externalLoadsFileName = new org.opensim.swingui.FileTextFieldAndChooser();
        externalLoadsModelKinematicsFileName = new org.opensim.swingui.FileTextFieldAndChooser();
        cutoffFrequency = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        actuatorsPanel = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        actuatorSetFiles = new javax.swing.JTextField();
        appendActuatorSetRadioButton = new javax.swing.JRadioButton();
        replaceActuatorSetRadioButton = new javax.swing.JRadioButton();
        editActuatorSetFiles = new javax.swing.JButton();

        externalLoadsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "External Loads"));
        jLabel3.setText("External loads");

        jLabel4.setText("Kinematics for external loads");

        jLabel6.setText("Applied to bodies:");

        filterModelKinematics.setText("Filter kinematics");
        filterModelKinematics.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        filterModelKinematics.setMargin(new java.awt.Insets(0, 0, 0, 0));
        filterModelKinematics.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                filterModelKinematicsActionPerformed(evt);
            }
        });

        externalLoadsBody1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        externalLoadsBody1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                externalLoadsBody1ActionPerformed(evt);
            }
        });

        jLabel5.setText("Body1");

        jLabel7.setText("Body2");

        externalLoadsBody2.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        externalLoadsBody2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                externalLoadsBody2ActionPerformed(evt);
            }
        });

        externalLoadsFileName.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                externalLoadsFileNameStateChanged(evt);
            }
        });

        externalLoadsModelKinematicsFileName.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                externalLoadsModelKinematicsFileNameStateChanged(evt);
            }
        });

        cutoffFrequency.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
        cutoffFrequency.setText("jTextField3");
        cutoffFrequency.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cutoffFrequencyActionPerformed(evt);
            }
        });
        cutoffFrequency.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                cutoffFrequencyFocusLost(evt);
            }
        });

        jLabel9.setText("Hz");

        org.jdesktop.layout.GroupLayout externalLoadsPanelLayout = new org.jdesktop.layout.GroupLayout(externalLoadsPanel);
        externalLoadsPanel.setLayout(externalLoadsPanelLayout);
        externalLoadsPanelLayout.setHorizontalGroup(
            externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(externalLoadsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                    .add(filterModelKinematics)
                    .add(jLabel4)
                    .add(jLabel6)
                    .add(jLabel3))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(externalLoadsFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 288, Short.MAX_VALUE)
                    .add(externalLoadsModelKinematicsFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 288, Short.MAX_VALUE)
                    .add(externalLoadsPanelLayout.createSequentialGroup()
                        .add(10, 10, 10)
                        .add(jLabel5)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(externalLoadsBody1, 0, 103, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel7)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(externalLoadsBody2, 0, 103, Short.MAX_VALUE))
                    .add(externalLoadsPanelLayout.createSequentialGroup()
                        .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 139, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jLabel9)))
                .addContainerGap())
        );
        externalLoadsPanelLayout.setVerticalGroup(
            externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(externalLoadsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                    .add(jLabel3)
                    .add(externalLoadsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(12, 12, 12)
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel6)
                    .add(jLabel5)
                    .add(externalLoadsBody1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabel7)
                    .add(externalLoadsBody2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                    .add(jLabel4)
                    .add(externalLoadsModelKinematicsFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(13, 13, 13)
                .add(externalLoadsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(filterModelKinematics)
                    .add(cutoffFrequency, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabel9))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        actuatorsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "Actuators"));
        jLabel1.setText("Additional actuator set files");

        actuatorSetFiles.setEditable(false);
        actuatorSetFiles.setText("jTextField2");

        buttonGroup1.add(appendActuatorSetRadioButton);
        appendActuatorSetRadioButton.setSelected(true);
        appendActuatorSetRadioButton.setText("Append to model's actuator set");
        appendActuatorSetRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        appendActuatorSetRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        appendActuatorSetRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                appendActuatorSetRadioButtonActionPerformed(evt);
            }
        });

        buttonGroup1.add(replaceActuatorSetRadioButton);
        replaceActuatorSetRadioButton.setText("Replace model's actuator set");
        replaceActuatorSetRadioButton.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        replaceActuatorSetRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        replaceActuatorSetRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                replaceActuatorSetRadioButtonActionPerformed(evt);
            }
        });

        editActuatorSetFiles.setText("Edit...");
        editActuatorSetFiles.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editActuatorSetFilesActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout actuatorsPanelLayout = new org.jdesktop.layout.GroupLayout(actuatorsPanel);
        actuatorsPanel.setLayout(actuatorsPanelLayout);
        actuatorsPanelLayout.setHorizontalGroup(
            actuatorsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(actuatorsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(actuatorsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(actuatorsPanelLayout.createSequentialGroup()
                        .add(jLabel1)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(actuatorSetFiles, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 228, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(editActuatorSetFiles))
                    .add(appendActuatorSetRadioButton)
                    .add(replaceActuatorSetRadioButton))
                .addContainerGap())
        );
        actuatorsPanelLayout.setVerticalGroup(
            actuatorsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(actuatorsPanelLayout.createSequentialGroup()
                .add(actuatorsPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jLabel1)
                    .add(editActuatorSetFiles)
                    .add(actuatorSetFiles, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(appendActuatorSetRadioButton)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(replaceActuatorSetRadioButton)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, actuatorsPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, externalLoadsPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(actuatorsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(externalLoadsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

   private void replaceActuatorSetRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_replaceActuatorSetRadioButtonActionPerformed
      toolModel.setReplaceForceSet(true);
   }//GEN-LAST:event_replaceActuatorSetRadioButtonActionPerformed

   private void appendActuatorSetRadioButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_appendActuatorSetRadioButtonActionPerformed
      toolModel.setReplaceForceSet(false);
   }//GEN-LAST:event_appendActuatorSetRadioButtonActionPerformed

   //------------------------------------------------------------------------
   // Vector<String> <-> ArrayStr conversion utilities
   //------------------------------------------------------------------------
   // TODO: add these to java-wrapped ArrayStr class
   private static Vector<String> toVector(ArrayStr array) {
      Vector<String> vector = new Vector<String>(array.getSize());
      for(int i=0; i<array.getSize(); i++) vector.add(array.getitem(i));
      return vector;
   }
   
   private static ArrayStr toArrayStr(Vector<String> vector) {
      ArrayStr array = new ArrayStr();
      array.setSize(vector.size());
      for(int i=0; i<vector.size(); i++) array.set(i, vector.get(i));
      return array;
   }

   private void editActuatorSetFilesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editActuatorSetFilesActionPerformed
      Vector<String> actuatorSetFiles = toolModel.getForceSetFiles().toVector();
      Vector<String> result = MultiFileSelectorPanel.showDialog(actuatorSetFiles, FileUtils.getFileFilter(".xml", "Actuator set file"));
      if(result!=null) toolModel.setForceSetFiles(ArrayStr.fromVector(result));
   }//GEN-LAST:event_editActuatorSetFilesActionPerformed

   private void externalLoadsFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_externalLoadsFileNameStateChanged
      toolModel.setExternalLoadsFileName(externalLoadsFileName.getFileName());
   }//GEN-LAST:event_externalLoadsFileNameStateChanged

   private void externalLoadsBody1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_externalLoadsBody1ActionPerformed
      if(!internalTrigger) {
         if(externalLoadsBody1.getSelectedItem()==null) toolModel.setExternalLoadsBody1("");
         else toolModel.setExternalLoadsBody1((String)externalLoadsBody1.getSelectedItem());
      }
   }//GEN-LAST:event_externalLoadsBody1ActionPerformed

   private void externalLoadsBody2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_externalLoadsBody2ActionPerformed
      if(!internalTrigger) {
         if(externalLoadsBody2.getSelectedItem()==null) toolModel.setExternalLoadsBody2("");
         else toolModel.setExternalLoadsBody2((String)externalLoadsBody2.getSelectedItem());
      }
   }//GEN-LAST:event_externalLoadsBody2ActionPerformed

   private void externalLoadsModelKinematicsFileNameStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_externalLoadsModelKinematicsFileNameStateChanged
      toolModel.setExternalLoadsModelKinematicsFileName(externalLoadsModelKinematicsFileName.getFileName());
   }//GEN-LAST:event_externalLoadsModelKinematicsFileNameStateChanged
   
   private void filterModelKinematicsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_filterModelKinematicsActionPerformed
      toolModel.setFilterLoadKinematics(filterModelKinematics.isSelected());
   }//GEN-LAST:event_filterModelKinematicsActionPerformed

   private void cutoffFrequencyFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_cutoffFrequencyFocusLost
      if(!evt.isTemporary()) cutoffFrequencyActionPerformed(null);
   }//GEN-LAST:event_cutoffFrequencyFocusLost

   private void cutoffFrequencyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cutoffFrequencyActionPerformed
      try {
         toolModel.setLowpassCutoffFrequencyForLoadKinematics(numFormat.parse(cutoffFrequency.getText()).doubleValue());
      } catch (ParseException ex) {
         Toolkit.getDefaultToolkit().beep();
         cutoffFrequency.setText(numFormat.format(toolModel.getLowpassCutoffFrequencyForLoadKinematics()));
      }
   }//GEN-LAST:event_cutoffFrequencyActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField actuatorSetFiles;
    private javax.swing.JPanel actuatorsPanel;
    private javax.swing.JRadioButton appendActuatorSetRadioButton;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JTextField cutoffFrequency;
    private javax.swing.JButton editActuatorSetFiles;
    private javax.swing.JComboBox externalLoadsBody1;
    private javax.swing.JComboBox externalLoadsBody2;
    private org.opensim.swingui.FileTextFieldAndChooser externalLoadsFileName;
    private org.opensim.swingui.FileTextFieldAndChooser externalLoadsModelKinematicsFileName;
    private javax.swing.JPanel externalLoadsPanel;
    private javax.swing.JCheckBox filterModelKinematics;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JRadioButton replaceActuatorSetRadioButton;
    // End of variables declaration//GEN-END:variables
   
}
