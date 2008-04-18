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
package org.opensim.view.editors;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.io.Serializable;
import java.util.Observable;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Observer;
import java.util.Vector;
import org.openide.ErrorManager;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.openide.windows.TopComponent;
import org.openide.windows.WindowManager;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.AbstractDynamicsEngine;
import org.opensim.modeling.Model;
import org.opensim.modeling.AbstractWrapObject;
import org.opensim.modeling.ArrayPtrsPropertyGroup;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.MuscleWrap;
import org.opensim.modeling.PropertyGroup;
import org.opensim.modeling.MusclePointSet;
import org.opensim.modeling.MuscleViaPoint;
import org.opensim.modeling.WrapEllipsoid;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Function;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Property;
import org.opensim.modeling.PropertySet;
import org.opensim.modeling.SetMuscleWrap;
import org.opensim.modeling.ArrayMusclePoint;
import org.opensim.modeling.SetWrapObject;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.Constant;
import org.opensim.modeling.MovingMusclePoint;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.Units;
import org.opensim.modeling.VisibleProperties.DisplayPreference;
import org.opensim.view.ClearSelectedObjectsEvent;
import org.opensim.view.DragObjectsEvent;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.ModelEvent;
import org.opensim.view.NameChangedEvent;
import org.opensim.view.ObjectSelectedEvent;
import org.opensim.view.ObjectSetCurrentEvent;
import org.opensim.view.ObjectsChangedEvent;
import org.opensim.view.ObjectsDeletedEvent;
import org.opensim.view.OpenSimEvent;
import org.opensim.view.SingleModelGuiElements;
import org.opensim.view.SingleModelVisuals;
import org.opensim.view.nodes.OneActuatorNode;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;
import org.opensim.view.SelectedObject;
import org.opensim.view.functionEditor.FunctionEditorTopComponent;
import org.opensim.view.functionEditor.FunctionEditorTopComponent.FunctionEditorOptions;

/**
 * Top component which displays the Muscle Editor window.
 *
 * TODO: fix potential memory leak -- savedAct is a C++-side copy of the actuator.  This is necessary
 * for the case where we end up calling replaceActuator(currentAct, savedAct), but if we don't end up
 * doing this we end up leaking memory since this C++-side copy won't be used or deleted.
 */
final public class MuscleEditorTopComponent extends TopComponent implements Observer {
   
   private static MuscleEditorTopComponent instance;
   private Model currentModel = null;
   private AbstractActuator currentAct = null; // the actuator that is currently shown in the Muscle Editor window
   private static final String[] wrapMethodNames = {"hybrid", "midpoint", "axial"};
   private static final String[] musclePointTypeNames = {"fixed", "via", "moving"};
   private static final String[] musclePointClassNames = {"MusclePoint", "MuscleViaPoint", "MovingMusclePoint"};
   private javax.swing.JScrollPane AttachmentsTab = null;
   private javax.swing.JScrollPane WrapTab = null;
   private javax.swing.JScrollPane CurrentPathTab = null;
   private String selectedTabName = null;
   private javax.swing.JCheckBox attachmentSelectBox[] = null; // array of checkboxes for selecting attachment points
   private String[] wrapObjectNames = null;
   private Hashtable<AbstractActuator, Boolean> pendingChanges = new Hashtable<AbstractActuator, Boolean>();
   private Hashtable<AbstractActuator, AbstractActuator> savedActs = new Hashtable<AbstractActuator, AbstractActuator>();

   private NumberFormat doublePropFormat = NumberFormat.getInstance();
   private NumberFormat intPropFormat = NumberFormat.getInstance();
   private NumberFormat positionFormat = NumberFormat.getInstance();
   private NumberFormat angleFormat = NumberFormat.getInstance();
   
   /** path to the icon used by the component and its open action */
//    static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
   
   private static final String PREFERRED_ID = "MuscleEditorTopComponent";
   
   private MuscleEditorTopComponent() {
      doublePropFormat.setMinimumFractionDigits(6);
      intPropFormat.setMinimumFractionDigits(0);
      positionFormat.setMinimumFractionDigits(5);
      angleFormat.setMinimumFractionDigits(2);

      initComponents();
      setName(NbBundle.getMessage(MuscleEditorTopComponent.class, "CTL_MuscleEditorTopComponent"));
      setToolTipText(NbBundle.getMessage(MuscleEditorTopComponent.class, "HINT_MuscleEditorTopComponent"));
//        setIcon(Utilities.loadImage(ICON_PATH, true));
      ViewDB.getInstance().addObserver(this);
      OpenSimDB.getInstance().addObserver(this);
      setupComponent(null);
   }

   private void backupAllActuators() {
      // Delete any existing actuator backups, and clear the savedActs hash table.
      Iterator<AbstractActuator> actIter = savedActs.values().iterator();
      while(actIter.hasNext())
         AbstractActuator.deleteActuator(actIter.next());
      savedActs.clear();

      pendingChanges.clear();

      // Make a backup of each actuator in the current model and add it to the savedActs hash table.
      if (currentModel != null) {
         ActuatorSet actuators = currentModel.getActuatorSet();
         for (int i=0; i<actuators.getSize(); i++) {
            AbstractActuator savedAct = AbstractActuator.safeDownCast(actuators.get(i).copy());
            savedActs.put(actuators.get(i), savedAct);
            pendingChanges.put(actuators.get(i), false);
         }
      }
   }

   private void updateBackupRestoreButtons() {
      if (currentAct != null) {
         boolean state = pendingChanges.get(currentAct);
         if (RestoreButton.isEnabled() != state)
            RestoreButton.setEnabled(state);
         if (BackupButton.isEnabled() != state)
            BackupButton.setEnabled(state);
      }

      boolean anyPendingChanges = false;
      Enumeration<AbstractActuator> acts = pendingChanges.keys();
      while(acts.hasMoreElements()) {
         AbstractActuator next = acts.nextElement();
         if (pendingChanges.get(next) == true) {
            anyPendingChanges = true;
            break;
         }
      }
      if (RestoreAllButton.isEnabled() != anyPendingChanges)
         RestoreAllButton.setEnabled(anyPendingChanges);
      if (BackupAllButton.isEnabled() != anyPendingChanges)
         BackupAllButton.setEnabled(anyPendingChanges);
   }

   private void setPendingChanges(boolean state, AbstractActuator act, boolean update) {
      pendingChanges.put(act, state);

      if (update)
         updateBackupRestoreButtons();

      // Mark the model as dirty as well.
      if (state == true && currentModel != null) {
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
         guiElem.setUnsavedChangesFlag(true);
      }
   }
   
   private void setAllPendingChanges(boolean state) {
      boolean needsRepainting = false;
      Enumeration<AbstractActuator> acts = pendingChanges.keys();
      while(acts.hasMoreElements()) {
         AbstractActuator next = acts.nextElement();
         pendingChanges.put(next, state);
      }

      updateBackupRestoreButtons();

      // Mark the model as dirty as well.
      if (state == true && currentModel != null) {
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
         guiElem.setUnsavedChangesFlag(true);
      }

      //if (repaint)
         //ViewDB.getInstance().repaintAll();
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        MuscleEditorScrollPane = new javax.swing.JScrollPane();
        MuscleEditorPanel = new javax.swing.JPanel();
        BackupButton = new javax.swing.JButton();
        BackupAllButton = new javax.swing.JButton();
        RestoreButton = new javax.swing.JButton();
        RestoreAllButton = new javax.swing.JButton();
        MuscleNameTextField = new javax.swing.JTextField();
        ParametersTabbedPanel = new javax.swing.JTabbedPane();
        MuscleNameLabel = new javax.swing.JLabel();
        MuscleTypeLabel = new javax.swing.JLabel();
        ModelNameLabel = new javax.swing.JLabel();
        MuscleSelectLabel = new javax.swing.JLabel();
        MuscleComboBox = new javax.swing.JComboBox();

        MuscleEditorScrollPane.setBorder(null);
        MuscleEditorPanel.setMinimumSize(new java.awt.Dimension(5, 5));
        MuscleEditorPanel.setPreferredSize(new java.awt.Dimension(5, 5));
        org.openide.awt.Mnemonics.setLocalizedText(BackupButton, "Backup current");
        BackupButton.setToolTipText("Make a backup copy of the current actuator. Click \"Restore current\" or \"Restore all\" to return to these values.");
        BackupButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BackupButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(BackupAllButton, "Backup all");
        BackupAllButton.setToolTipText("Make backup copies of all actuators in the current model. Click \"Restore all\" or \"Restore current\" to return to these values.");
        BackupAllButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BackupAllButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(RestoreButton, "Restore current");
        RestoreButton.setToolTipText("Restore the current actuator to the backup copy made when \"Backup\" or \"Backup all\" was pressed (or when the model was first loaded).");
        RestoreButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                RestoreButtonActionPerformed(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(RestoreAllButton, "Restore all");
        RestoreAllButton.setToolTipText("Restore all actuators to their backup copies made when \"Backup\" or \"Backup all\" was pressed (or when the model was first loaded).");
        RestoreAllButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                RestoreAllButtonActionPerformed(evt);
            }
        });

        MuscleNameTextField.setText("<actuator name>");
        MuscleNameTextField.setToolTipText("The name of this actuator");
        MuscleNameTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                MuscleNameTextFieldActionPerformed(evt);
            }
        });
        MuscleNameTextField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                MuscleNameTextFieldFocusLost(evt);
            }
        });

        org.openide.awt.Mnemonics.setLocalizedText(MuscleNameLabel, "Name");

        MuscleTypeLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        org.openide.awt.Mnemonics.setLocalizedText(MuscleTypeLabel, "Type: <class>");
        MuscleTypeLabel.setToolTipText("The type of this actuator");

        org.openide.awt.Mnemonics.setLocalizedText(ModelNameLabel, "Model: <name> ");
        ModelNameLabel.setToolTipText("The name of the current model");

        org.openide.awt.Mnemonics.setLocalizedText(MuscleSelectLabel, "Muscle");

        MuscleComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "<a muscle>", "Item 2", "Item 3", "Item 4" }));
        MuscleComboBox.setToolTipText("Select the actuator to edit");
        MuscleComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                MuscleComboBoxActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout MuscleEditorPanelLayout = new org.jdesktop.layout.GroupLayout(MuscleEditorPanel);
        MuscleEditorPanel.setLayout(MuscleEditorPanelLayout);
        MuscleEditorPanelLayout.setHorizontalGroup(
            MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(MuscleEditorPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(MuscleEditorPanelLayout.createSequentialGroup()
                        .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(ParametersTabbedPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 570, Short.MAX_VALUE)
                            .add(ModelNameLabel)
                            .add(MuscleEditorPanelLayout.createSequentialGroup()
                                .add(MuscleSelectLabel)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(MuscleComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 147, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .add(14, 14, 14)
                                .add(MuscleNameLabel)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(MuscleNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 147, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .add(15, 15, 15)
                                .add(MuscleTypeLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 157, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))
                        .addContainerGap())
                    .add(MuscleEditorPanelLayout.createSequentialGroup()
                        .add(10, 10, 10)
                        .add(RestoreButton)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(RestoreAllButton)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 111, Short.MAX_VALUE)
                        .add(BackupButton)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(BackupAllButton)
                        .add(27, 27, 27))))
        );
        MuscleEditorPanelLayout.setVerticalGroup(
            MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(MuscleEditorPanelLayout.createSequentialGroup()
                .addContainerGap()
                .add(ModelNameLabel)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(MuscleSelectLabel)
                    .add(MuscleComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(MuscleNameLabel)
                    .add(MuscleNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(MuscleTypeLabel))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(ParametersTabbedPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 246, Short.MAX_VALUE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(RestoreButton)
                    .add(RestoreAllButton)
                    .add(BackupAllButton)
                    .add(BackupButton))
                .addContainerGap())
        );
        MuscleEditorScrollPane.setViewportView(MuscleEditorPanel);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(MuscleEditorScrollPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 594, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(MuscleEditorScrollPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 358, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    private void BackupAllButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BackupAllButtonActionPerformed
       backupActuators();
    }//GEN-LAST:event_BackupAllButtonActionPerformed

    private void RestoreAllButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_RestoreAllButtonActionPerformed
       restoreActuators();
    }//GEN-LAST:event_RestoreAllButtonActionPerformed

   private void MuscleComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MuscleComboBoxActionPerformed
      if (currentModel == null)
         return;
      String nameOfNewAct = MuscleComboBox.getSelectedItem().toString();
      AbstractActuator newAct = currentModel.getActuatorSet().get(nameOfNewAct);
      if (newAct != null && AbstractActuator.getCPtr(newAct) != AbstractActuator.getCPtr(currentAct)) {
         currentAct = newAct;
         updateBackupRestoreButtons();
         setupComponent(currentAct);
      }
   }//GEN-LAST:event_MuscleComboBoxActionPerformed
   
   private boolean validName(String actName)
   {
      if (currentModel != null && currentAct != null) {
         if (actName.length() < 1) {
            MuscleNameTextField.setText(currentAct.getName());
            return false;
         }
         AbstractActuator existingAct = currentModel.getActuatorSet().get(actName);
         if (existingAct != null && AbstractActuator.getCPtr(existingAct) != AbstractActuator.getCPtr(currentAct)) {
            MuscleNameTextField.setText(currentAct.getName());
            Object[] options = {"OK"};
            String message = "The name \"" + actName + "\" is already being used. Please choose a different actuator name";
            int answer = JOptionPane.showOptionDialog(this,
                         message,
                         "Muscle Editor",
                         JOptionPane.OK_OPTION,
                         JOptionPane.WARNING_MESSAGE,
                         null,
                         options,
                         options[0]);
            return false;
         } else {
            return true;
         }
      }

      return false;
   }

   private void MuscleNameTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_MuscleNameTextFieldFocusLost
      if (!evt.isTemporary())
          MuscleNameEntered();
   }//GEN-LAST:event_MuscleNameTextFieldFocusLost

   private void MuscleNameTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MuscleNameTextFieldActionPerformed
      MuscleNameEntered();
   }//GEN-LAST:event_MuscleNameTextFieldActionPerformed

   private void MuscleNameEntered() {
      if (currentAct == null || currentAct.getName().equals(MuscleNameTextField.getText()) == true)
         return;
      if (validName(MuscleNameTextField.getText()) == false)
         return;
      currentAct.setName(MuscleNameTextField.getText());
      // Let the event handler update the muscle editor, because muscle names
      // could also be changed from outside the editor.
      NameChangedEvent evnt = new NameChangedEvent(currentAct);
      OpenSimDB.getInstance().setChanged();
      OpenSimDB.getInstance().notifyObservers(evnt);

      // If the actuator is an AbstractMuscle, then when it is renamed
      // all of its attachment points will be renamed as well. You need
      // to generate events for all of these name changes, because
      // attachment point names can be displayed in the function editor,
      // text bar (during selection), etc.
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      if (asm != null) {
         // Set the name again, this time using AbstractMuscle's custom method
         asm.setName(MuscleNameTextField.getText());
         MusclePointSet musclePoints = asm.getAttachmentSet();
         for (int i=0; i<musclePoints.getSize(); i++) {
            NameChangedEvent evt = new NameChangedEvent(musclePoints.get(i));
            OpenSimDB.getInstance().setChanged();
            OpenSimDB.getInstance().notifyObservers(evt);
         }
      }
   }

   // Called from update(), this function handles name changes to any actuator in
   // the current model. It assumes that the actuator's name has already been
   // changed, so only the muscle editor needs to be updated.
   private void updateActuatorName(AbstractActuator act) {
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
      String [] actNames = guiElem.getActuatorNames(true);
      MuscleComboBox.setModel(new javax.swing.DefaultComboBoxModel(actNames));
      if (currentAct != null) {
         MuscleComboBox.setSelectedIndex(findElement(actNames, currentAct.getName()));
         if (currentAct.equals(act))
            MuscleNameTextField.setText(currentAct.getName());
      }
      setPendingChanges(true, act, true);
   }

   private void RestoreButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_RestoreButtonActionPerformed
      restoreActuator();
   }//GEN-LAST:event_RestoreButtonActionPerformed
   
   private void BackupButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BackupButtonActionPerformed
      backupActuator();
   }//GEN-LAST:event_BackupButtonActionPerformed
   
   private void backupActuator() {
      //act.setName(MuscleNameTextField.getText());
      setPendingChanges(false, currentAct, true);
      //OpenSimDB.getInstance().setChanged();
      //NameChangedEvent evnt = new NameChangedEvent(act);
      //OpenSimDB.getInstance().notifyObservers(evnt);
      AbstractActuator savedAct = AbstractActuator.safeDownCast(currentAct.copy());
      //savedAct.setName(currentAct.getName()); // TODO: what about other properties of parent classes?
      savedActs.put(currentAct, savedAct);
   }

   private void backupActuators() {
      // Should never be null, but just in case...
       if (currentModel == null)
          return;

      // Loop through the actuator set, backing up only the ones that have been modified.
      ActuatorSet actSet = currentModel.getActuatorSet();
      for (int i=0; i<actSet.getSize(); i++) {
         AbstractActuator act = actSet.get(i);
         if (pendingChanges.get(act)) {
             AbstractActuator savedAct = savedActs.get(act);
             // Copy the elements of the saved actuator into the [regular] actuator.
             savedAct.copy(act);
         }
      }

      setAllPendingChanges(false);
   }

   /** restoreActuator
    *  Because the type of the actuator may have changed, you have to remove the current
    *  one (act) and replace it with the saved one (savedAct).
    */
   private void restoreActuatorReplace() {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      
      // Save the display preference of the old muscle.
      DisplayPreference dp = currentAct.getDisplayer().getVisibleProperties().getDisplayPreference();

      // Fire an event to announce the actuator switch. TODO: this code should
      // really fire an ObjectsReplacedEvent. And ViewDB should pick up this
      // event and remove the actuator geometry, rather than having the muscle editor
      // do it here.
      Vector<OpenSimObject> objs = new Vector<OpenSimObject>(2);
      objs.add(asm);
      ObjectsDeletedEvent evnt = new ObjectsDeletedEvent(this, model, objs);
      OpenSimDB.getInstance().setChanged();
      OpenSimDB.getInstance().notifyObservers(evnt);

      vis.removeActuatorGeometry(currentAct);
      AbstractActuator savedAct = savedActs.get(currentAct);
      // Remove the current actuator from the pendingChanges and savedActs hash tables.
      pendingChanges.remove(currentAct);
      savedActs.remove(currentAct);
      // Replace the actuator with the saved one.
      model.getActuatorSet().replaceActuator(currentAct, savedAct);
      currentAct = savedAct; // currentAct now points to the actuator in the model's actuator set.
      // Make a new backup copy of the actuator.
      savedAct = AbstractActuator.safeDownCast(currentAct.copy());
      // Put the new current actuator in the pendingChanges and savedActs hash tables.
      pendingChanges.put(currentAct, true); // old state must have been true for restore to be called
      savedActs.put(currentAct, savedAct);
      // Set the display preference of the new muscle to the same as the old.
      currentAct.getDisplayer().getVisibleProperties().setDisplayPreference(dp);
      vis.addActuatorGeometry(currentAct, true);

      // Once the proper ObjectsReplacedEvent is implemented, this NameChangedEvent
      // should no longer be needed.
      NameChangedEvent ev = new NameChangedEvent(currentAct);
      OpenSimDB.getInstance().setChanged();
      OpenSimDB.getInstance().notifyObservers(ev);

      setPendingChanges(false, currentAct, false);
      setupComponent(currentAct);
      ViewDB.getInstance().repaintAll();
   }

   /* The version of restoreActuator above replaces the actuator in the
    * model's actuator set, because the type may have been changed (so
    * the actuator to restore to is an entirely different object). This
    * causes problems in the GUI because other components like the
    * navigator do not yet handle replace-objects events. Also, with
    * the muscle-type combo box commented out for 1.0, the actuator
    * object cannot change between a backup/restore, so the function below
    * was created to do a simple copy-in-place when restore is pressed.
    * This version sends out only a name-changed event because the
    * other GUI components do not yet handle property-change events.
    */
   private void restoreActuator() {
      // Should never be null, but just in case...
       if (currentAct == null || currentModel ==  null)
          return;
      AbstractActuator savedAct = savedActs.get(currentAct);
      if (savedAct == null)
         return;

      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(currentModel);

      // Deselect all attachment points on the muscle being restored.
      AbstractMuscle currentMuscle = AbstractMuscle.safeDownCast(currentAct);
      if (currentMuscle != null)
         ViewDB.getInstance().removeObjectsBelongingToMuscleFromSelection(currentMuscle);

      // Make sure the Function Editor isn't still operating on one of this muscle's functions.
      FunctionEditorTopComponent win = FunctionEditorTopComponent.findInstance();
      win.closeObject(currentAct);

      // If the name has changed, fire an event.
      if (currentAct.getName().equals(savedAct.getName()) == false) {
         NameChangedEvent ev = new NameChangedEvent(currentAct);
         OpenSimDB.getInstance().setChanged();
         OpenSimDB.getInstance().notifyObservers(ev);
      }

      // Copy the elements of the saved actuator into the current actuator.
      currentAct.copy(savedAct);
      vis.updateActuatorGeometry(currentAct, true);

      setPendingChanges(false, currentAct, false);
      setupComponent(currentAct);
      ViewDB.getInstance().repaintAll();
   }

   private void restoreActuators() {
      // Should never be null, but just in case...
       if (currentModel == null)
          return;

      boolean updateEditor = false;
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(currentModel);

      // Deselect all attachment points.
      ViewDB.getInstance().removeObjectsBelongingToModelFromSelection(currentModel);

      // Make a note if the current actuator needs to be restored, so you can call
      // setupComponent() later.
      if (pendingChanges.get(currentAct))
          updateEditor = true;

      // Loop through the actuator set, restoring only the ones that have been modified.
      ActuatorSet actSet = currentModel.getActuatorSet();
      for (int i=0; i<actSet.getSize(); i++) {
          AbstractActuator act = actSet.get(i);
          if (pendingChanges.get(act)) {
              AbstractActuator savedAct = savedActs.get(act);
              // If the name has changed, fire an event.
              if (act.getName().equals(savedAct.getName()) == false) {
                 NameChangedEvent ev = new NameChangedEvent(act);
                 OpenSimDB.getInstance().setChanged();
                 OpenSimDB.getInstance().notifyObservers(ev);
              }
              // Make sure the Function Editor isn't still operating on one of this muscle's functions.
              FunctionEditorTopComponent win = FunctionEditorTopComponent.findInstance();
              win.closeObject(act);

              // Copy the elements of the saved actuator into the [regular] actuator.
              act.copy(savedAct);
              vis.updateActuatorGeometry(act, true);
          }
      }

      setAllPendingChanges(false);
      if (updateEditor)
         setupComponent(currentAct);
      ViewDB.getInstance().repaintAll();
   }

   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton BackupAllButton;
   private javax.swing.JButton BackupButton;
   private javax.swing.JLabel ModelNameLabel;
   private javax.swing.JComboBox MuscleComboBox;
   private javax.swing.JPanel MuscleEditorPanel;
   private javax.swing.JScrollPane MuscleEditorScrollPane;
   private javax.swing.JLabel MuscleNameLabel;
   private javax.swing.JTextField MuscleNameTextField;
   private javax.swing.JLabel MuscleSelectLabel;
   private javax.swing.JLabel MuscleTypeLabel;
   private javax.swing.JTabbedPane ParametersTabbedPanel;
   private javax.swing.JButton RestoreAllButton;
   private javax.swing.JButton RestoreButton;
   // End of variables declaration//GEN-END:variables
   
   /**
    * Gets default instance. Do not use directly: reserved for *.settings files only,
    * i.e. deserialization routines; otherwise you could get a non-deserialized instance.
    * To obtain the singleton instance, use {@link findInstance}.
    */
   public static synchronized MuscleEditorTopComponent getDefault() {
      if (instance == null) {
         instance = new MuscleEditorTopComponent();
      }
      return instance;
   }
   
   /**
    * Obtain the MuscleEditorTopComponent instance. Never call {@link #getDefault} directly!
    */
   public static synchronized MuscleEditorTopComponent findInstance() {
      TopComponent win = WindowManager.getDefault().findTopComponent(PREFERRED_ID);
      if (win == null) {
         ErrorManager.getDefault().log(ErrorManager.WARNING, "Cannot find MuscleEditor component. It will not be located properly in the window system.");
         return getDefault();
      }
      if (win instanceof MuscleEditorTopComponent) {
         return (MuscleEditorTopComponent)win;
      }
      ErrorManager.getDefault().log(ErrorManager.WARNING, "There seem to be multiple components with the '" + PREFERRED_ID + "' ID. That is a potential source of errors and unexpected behavior.");
      return getDefault();
   }
   
   public int getPersistenceType() {
      return TopComponent.PERSISTENCE_ALWAYS;
   }
   
   public void AttachmentPointEntered(javax.swing.JTextField field, int attachmentNum, int coordNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      double newValue, oldValue = musclePoints.get(attachmentNum).getAttachmentCoord(coordNum);
      try {
         newValue = positionFormat.parse(field.getText()).doubleValue();
      } catch (ParseException ex) {
         Toolkit.getDefaultToolkit().beep();
         field.setText(positionFormat.format(oldValue));
         return;
      }
      // format the number and write it back into the text field
      field.setText(positionFormat.format(newValue));
      // update the model if the number has changed
      if (oldValue != newValue) {
         musclePoints.get(attachmentNum).setAttachment(coordNum, newValue);
         setPendingChanges(true, currentAct, true);
         // tell the ViewDB to redraw the model
         Model model = asm.getModel();
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }
   
   public void AttachmentBodyChosen(javax.swing.JComboBox bodyComboBox, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      AbstractBody oldBody = musclePoints.get(attachmentNum).getBody();
      Model model = asm.getModel();
      BodySet bodies = model.getDynamicsEngine().getBodySet();
      AbstractBody newBody = bodies.get(bodyComboBox.getSelectedIndex());
      if (AbstractBody.getCPtr(newBody) != AbstractBody.getCPtr(oldBody)) {
         musclePoints.get(attachmentNum).setBody(newBody, true);
         setPendingChanges(true, currentAct, true);
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }
   
   public void AttachmentSelected(javax.swing.JCheckBox attachmentSelBox, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MusclePoint point = musclePoints.get(attachmentNum);
      ViewDB.getInstance().toggleAddSelectedObject(point);
   }
   
   public void ViaCoordinateChosen(javax.swing.JComboBox coordComboBox, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(attachmentNum));
      AbstractCoordinate oldCoord = via.getCoordinate();
      Model model = asm.getModel();
      CoordinateSet coords = model.getDynamicsEngine().getCoordinateSet();
      AbstractCoordinate newCoord = coords.get(coordComboBox.getSelectedIndex());
      if (AbstractCoordinate.getCPtr(newCoord) != AbstractCoordinate.getCPtr(oldCoord)) {
         via.setCoordinate(newCoord);
         // make sure the range min and range max are valid for this new coordinate
         double rangeMin = via.getRange().getitem(0);
         double rangeMax = via.getRange().getitem(1);
         boolean needsUpdating = false;
         if (rangeMin > newCoord.getRangeMax() || rangeMax < newCoord.getRangeMin()) {
            // If there is no overlap between the old range and the new range, use new range
            via.setRangeMin(newCoord.getRangeMin());
            via.setRangeMax(newCoord.getRangeMax());
            needsUpdating = true;
         } else {
            // It's OK if the range from the old coordinate is bigger than
            // the range of the new. Don't trim it down to size. JPL 08/08/07
            // Adjust the min and max to fit in the new range
            //if (rangeMin < newCoord.getRangeMin()) {
            //   via.setRangeMin(newCoord.getRangeMin());
            //   needsUpdating = true;
            //}
            //if (rangeMax > newCoord.getRangeMax()) {
            //   via.setRangeMax(newCoord.getRangeMax());
            //   needsUpdating = true;
            //}
         }
         setPendingChanges(true, currentAct, true);
         if (needsUpdating) {
            updateAttachmentPanel(asm);
         }
         ParametersTabbedPanel.setSelectedComponent(AttachmentsTab);
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }

   public void MovingMusclePointCoordinateChosen(javax.swing.JComboBox coordComboBox, int attachmentNum, int xyz) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MovingMusclePoint mmp = MovingMusclePoint.safeDownCast(musclePoints.get(attachmentNum));
      if (mmp == null || coordComboBox.getSelectedIndex() < 0)
         return;
      AbstractCoordinate oldCoord = null;
      if (xyz == 0)
         oldCoord = mmp.getXCoordinate();
      else if (xyz == 1)
         oldCoord = mmp.getYCoordinate();
      else if (xyz == 2)
         oldCoord = mmp.getZCoordinate();
      Model model = asm.getModel();
      CoordinateSet coords = model.getDynamicsEngine().getCoordinateSet();
      AbstractCoordinate newCoord = coords.get(coordComboBox.getSelectedIndex());
      if (AbstractCoordinate.getCPtr(newCoord) != AbstractCoordinate.getCPtr(oldCoord)) {
         if (xyz == 0)
            mmp.setXCoordinate(newCoord);
         else if (xyz == 1)
            mmp.setYCoordinate(newCoord);
         else if (xyz == 2)
            mmp.setZCoordinate(newCoord);
         setPendingChanges(true, currentAct, true);
         ParametersTabbedPanel.setSelectedComponent(AttachmentsTab);
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }

   public void MusclePointTypeChosen(javax.swing.JComboBox musclePointTypeComboBox, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePoint mp = asm.getAttachmentSet().get(attachmentNum);
      MuscleViaPoint via = MuscleViaPoint.safeDownCast(mp);
      MovingMusclePoint mmp = MovingMusclePoint.safeDownCast(mp);

      int oldType = 0;
      if (via != null)
         oldType = 1;
      else if (mmp != null)
         oldType = 2;
      int newType = musclePointTypeComboBox.getSelectedIndex();
      if (newType != oldType) {
         MusclePoint newPoint = MusclePoint.makeMusclePointOfType(mp, musclePointClassNames[newType]);
         boolean result = asm.getAttachmentSet().replaceMusclePoint(mp, newPoint);
         if (result == false) {
            // Reset the combo box state without triggering an event
            musclePointTypeComboBox.setEnabled(false);
            musclePointTypeComboBox.setSelectedIndex(oldType);
            musclePointTypeComboBox.setEnabled(true);
            Object[] options = {"OK"};
            int answer = JOptionPane.showOptionDialog(this,
               "A muscle must contain at least 2 attachment points that are not via points.",
               "Muscle Editor",
               JOptionPane.OK_OPTION,
               JOptionPane.WARNING_MESSAGE,
               null,
               options,
               options[0]);
            MusclePoint.deleteMusclePoint(newPoint);
            return;
         }
         setPendingChanges(true, currentAct, true);
         ParametersTabbedPanel.setSelectedComponent(AttachmentsTab);
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(currentModel);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the panels
         updateAttachmentPanel(asm);
         updateCurrentPathPanel(asm);
      }
   }

   public void RangeMinEntered(javax.swing.JTextField field, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(attachmentNum));

      // Conversions between radians and degrees
      double conversion = 180.0/Math.PI;
      NumberFormat nf = angleFormat;
      AbstractCoordinate coordinate = via.getCoordinate();
      if (coordinate != null && coordinate.getMotionType() == AbstractDof.DofType.Translational) {
         conversion = 1.0;
         nf = positionFormat;
      }

      double newValue, oldValue = via.getRange().getitem(0)*conversion;
      double biggestAllowed = via.getRange().getitem(1)*conversion;
      try {
         newValue = nf.parse(field.getText()).doubleValue();
      } catch (ParseException ex) {
         Toolkit.getDefaultToolkit().beep();
         newValue = Double.MAX_VALUE; // to force the field to update itself with the old value
      }

      if (newValue > biggestAllowed) {
         // user entered min that is greater than max, ignore it
         field.setText(nf.format(oldValue));
      } else {
         // format the number and write it back into the text field
         field.setText(nf.format(newValue));
         // update the model if the number has changed
         if (newValue != oldValue) {
            via.setRangeMin(newValue/conversion);
            setPendingChanges(true, currentAct, true);
            // tell the ViewDB to redraw the model
            Model model = asm.getModel();
            SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
            vis.updateActuatorGeometry(asm, true);
            ViewDB.getInstance().repaintAll();
            // update the current path panel
            updateCurrentPathPanel(asm);
         }
      }
   }
   
   public void RangeMaxEntered(javax.swing.JTextField field, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(attachmentNum));

      // Conversions between radians and degrees
      double conversion = 180.0/Math.PI;
      NumberFormat nf = angleFormat;
      AbstractCoordinate coordinate = via.getCoordinate();
      if (coordinate != null && coordinate.getMotionType() == AbstractDof.DofType.Translational) {
         conversion = 1.0;
         nf = positionFormat;
      }

      double newValue, oldValue = via.getRange().getitem(1)*conversion;
      double smallestAllowed = via.getRange().getitem(0)*conversion;
      try {
         newValue = nf.parse(field.getText()).doubleValue();
      } catch (ParseException ex) {
         Toolkit.getDefaultToolkit().beep();
         newValue = -Double.MAX_VALUE; // to force the field to update itself with the old value
      }

      if (newValue < smallestAllowed) {
         // user entered max that is less than min, ignore it
         field.setText(nf.format(oldValue));
      } else {
         // format the number and write it back into the text field
         field.setText(nf.format(newValue));
         // update the model if the number has changed
         if (newValue != oldValue) {
            via.setRangeMax(newValue/conversion);
            setPendingChanges(true, currentAct, true);
            // tell the ViewDB to redraw the model
            Model model = asm.getModel();
            SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
            vis.updateActuatorGeometry(asm, true);
            ViewDB.getInstance().repaintAll();
            // update the current path panel
            updateCurrentPathPanel(asm);
         }
      }
   }
   
   public void setWrapStartRange(javax.swing.JComboBox wrapStartComboBox, int wrapNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MuscleWrap mw = asm.getWrapSet().get(wrapNum);
      int oldStartPt = mw.getStartPoint();
      int newStartPt = wrapStartComboBox.getSelectedIndex();
      if (newStartPt < 1)
         newStartPt = -1;
      if (newStartPt != oldStartPt) {
         mw.setStartPoint(newStartPt);
         setPendingChanges(true, currentAct, true);
         Model model = asm.getModel();
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }
   
   public void setWrapEndRange(javax.swing.JComboBox wrapEndComboBox, int wrapNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MuscleWrap mw = asm.getWrapSet().get(wrapNum);
      int oldEndPt = mw.getEndPoint();
      int newEndPt = wrapEndComboBox.getSelectedIndex();
      if (newEndPt == wrapEndComboBox.getItemCount()-1)
         newEndPt = -1;
      else
         newEndPt++;
      if (newEndPt != oldEndPt) {
         mw.setEndPoint(newEndPt);
         setPendingChanges(true, currentAct, true);
         Model model = asm.getModel();
         // tell the ViewDB to redraw the model
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
         // update the current path panel
         updateCurrentPathPanel(asm);
      }
   }
   
   public void addMuscleWrap(int menuChoice) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      AbstractWrapObject awo = asm.getModel().getDynamicsEngine().getWrapObject(wrapObjectNames[menuChoice]);
      asm.addMuscleWrap(awo);
      setPendingChanges(true, currentAct, true);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void moveUpMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.moveUpMuscleWrap(num);
      setPendingChanges(true, currentAct, true);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void moveDownMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.moveDownMuscleWrap(num);
      setPendingChanges(true, currentAct, true);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void deleteMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.deleteMuscleWrap(num);
      setPendingChanges(true, currentAct, true);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void setWrapMethod(javax.swing.JComboBox wrapMethodComboBox, int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MuscleWrap mw = asm.getWrapSet().get(num);
      int methodInt = wrapMethodComboBox.getSelectedIndex();
      //TODO: there must be a better way to relate selected index to WrapMethod enum
      if (methodInt == 0)
         mw.setMethod(MuscleWrap.WrapMethod.hybrid);
      else if (methodInt == 1)
         mw.setMethod(MuscleWrap.WrapMethod.midpoint);
      else if (methodInt == 2)
         mw.setMethod(MuscleWrap.WrapMethod.axial);
      setPendingChanges(true, currentAct, true);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   private void MuscleTypeComboBoxActionPerformed(javax.swing.JComboBox muscleTypeComboBox) {
      //Property.PropertyType newType = (Property.PropertyType)muscleTypeComboBox.getSelectedIndex();
      int newType = muscleTypeComboBox.getSelectedIndex();
      Model model = currentAct.getModel();
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);
      String newTypeName = guiElem.getActuatorClassNames()[newType];
      String oldTypeName = currentAct.getType();
      if (newTypeName.equals(oldTypeName) == false) {
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         // Store the display preference of the muscle before it is deleted.
         DisplayPreference dp = currentAct.getDisplayer().getVisibleProperties().getDisplayPreference();
         vis.removeActuatorGeometry(currentAct);
         boolean oldState = pendingChanges.get(currentAct);
         pendingChanges.remove(currentAct);
         currentAct = model.getActuatorSet().changeActuatorType(currentAct, newTypeName);
         pendingChanges.put(currentAct, oldState);
         // Set the display preference of the new muscle to the same as the old.
         currentAct.getDisplayer().getVisibleProperties().setDisplayPreference(dp);
         setPendingChanges(true, currentAct, true);
         setupComponent(currentAct);
         // tell the ViewDB to redraw the model
         vis.addActuatorGeometry(currentAct, true);
         ViewDB.getInstance().repaintAll();
      }
   }
   
   public void DoublePropertyEntered(javax.swing.JTextField field, int propertyNum) {
      Property prop = null;
      try {
         prop = currentAct.getPropertySet().get(propertyNum);
      } catch (IOException ex) {
         ex.printStackTrace();
      }
      if (prop != null) {
         double newValue, oldValue = prop.getValueDbl();
         try {
            newValue = doublePropFormat.parse(field.getText()).doubleValue();
         } catch (ParseException ex) {
            Toolkit.getDefaultToolkit().beep();
            field.setText(doublePropFormat.format(oldValue));
            return;
         }
         // format the number and write it back into the text field
         field.setText(doublePropFormat.format(newValue));

         if (newValue != oldValue) {
            prop.setValue(newValue);
            setPendingChanges(true, currentAct, true);
            // TODO generate an event for this??
         }
      }
   }

   public void IntPropertyEntered(javax.swing.JTextField field, int propertyNum) {
      Property prop = null;
      try {
         prop = currentAct.getPropertySet().get(propertyNum);
      } catch (IOException ex) {
         ex.printStackTrace();
      }
      if (prop != null) {
         int newValue, oldValue = prop.getValueInt();
         try {
            newValue = intPropFormat.parse(field.getText()).intValue();
         } catch (ParseException ex) {
            Toolkit.getDefaultToolkit().beep();
            field.setText(intPropFormat.format(oldValue));
            return;
         }
         // write the value back into the text field (for consistent formatting)
         field.setText(intPropFormat.format(newValue));

         if (newValue != oldValue) {
            prop.setValue(newValue);
            setPendingChanges(true, currentAct, true);
            // TODO generate an event for this??
         }
      }
   }

   public void EditPropertyFunction(javax.swing.JButton button, int propertyNum) {
      Property prop = null;
      try {
         prop = currentAct.getPropertySet().get(propertyNum);
      } catch (IOException ex) {
         ex.printStackTrace();
      }
      if (prop != null) {
         OpenSimObject obj = prop.getValueObjPtr();
         Function func = Function.safeDownCast(obj);
         FunctionEditorTopComponent win = FunctionEditorTopComponent.findInstance();
         win.addChangeListener(new MusclePropertyFunctionEventListener());
         FunctionEditorOptions options = new FunctionEditorOptions();
         options.title = prop.getName();
         options.XUnits = new Units(Units.UnitType.simmMeters);
         options.XDisplayUnits = options.XUnits;
         options.YUnits = new Units(Units.UnitType.simmNewtons);
         options.YDisplayUnits = options.YUnits;
         options.XLabel = "norm length";
         options.YLabel = "norm force";
         win.open(currentModel, currentAct, null, func, options);
      }
   }

   public void EditMusclePointFunction(javax.swing.JButton button, int attachmentNum, int xyz) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      if (asm != null) {
         MovingMusclePoint mmp = MovingMusclePoint.safeDownCast(asm.getAttachmentSet().get(attachmentNum));
         if (mmp != null) {
            Function function = null;
            AbstractCoordinate coordinate = null;
            FunctionEditorOptions options = new FunctionEditorOptions();
            if (xyz == 0) {
               function = mmp.getXFunction();
               coordinate = mmp.getXCoordinate();
               options.title = "X offset";
            } else if (xyz == 1) {
               function = mmp.getYFunction();
               coordinate = mmp.getYCoordinate();
               options.title = "Y offset";
            } else if (xyz == 2) {
               function = mmp.getZFunction();
               coordinate = mmp.getZCoordinate();
               options.title = "Z offset";
            }
            if (coordinate != null) {
               if (coordinate.getMotionType() == AbstractDof.DofType.Rotational) {
                  options.XUnits = new Units(Units.UnitType.simmRadians);
                  options.XDisplayUnits = new Units(Units.UnitType.simmDegrees);
               } else {
                  options.XUnits = new Units(Units.UnitType.simmMeters);
                  options.XDisplayUnits = options.XUnits;
               }
               options.XLabel = coordinate.getName() + " (deg)";
            }
            options.YUnits = new Units(Units.UnitType.simmMeters);
            options.YDisplayUnits = options.YUnits;
            FunctionEditorTopComponent win = FunctionEditorTopComponent.findInstance();
            win.addChangeListener(new MusclePointFunctionEventListener());
            options.YLabel = options.YDisplayUnits.getLabel();
            Vector<OpenSimObject> objects = new Vector<OpenSimObject>(1);
            objects.add(currentAct);
            win.open(currentModel, mmp, objects, function, options);
         }
      }
   }

   public void addAttachmentPerformed(int menuChoice) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      int index = menuChoice;
      if (index > musclePoints.getSize() - 1)
         index = musclePoints.getSize() - 1;

      // ideally we'd like to just deselect the point we're deleting but the muscle displayer doesn't
      // deal well with maintaining the right glyph colors when the attachment set changes.
      // TODO: send some event that the muscle displayer can listen for and know to deselect the point
      // and make sure the rest of the points maintain correct selection status
      ViewDB.getInstance().removeObjectsBelongingToMuscleFromSelection(AbstractMuscle.safeDownCast(currentAct));

      MusclePoint closestPoint = musclePoints.get(index);
      asm.addAttachmentPoint(menuChoice, closestPoint.getBody());
      setPendingChanges(true, currentAct, false);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void deleteAttachmentPerformed(int menuChoice) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      // ideally we'd like to just deselect the point we're deleting but the muscle displayer doesn't
      // deal well with maintaining the right glyph colors when the attachment set changes.
      // TODO: send some event that the muscle displayer can listen for and know to deselect the point
      // and make sure the rest of the points maintain correct selection status
      ViewDB.getInstance().removeObjectsBelongingToMuscleFromSelection(AbstractMuscle.safeDownCast(currentAct));
      // The point may not be deleted, but save a reference to it so that if it is deleted
      // you can fire an ObjectsDeletedEvent later.
      MusclePoint mp = asm.getAttachmentSet().get(menuChoice);
      boolean result = asm.deleteAttachmentPoint(menuChoice);
      if (result == false) {
         Object[] options = {"OK"};
         int answer = JOptionPane.showOptionDialog(this,
                 "A muscle must contain at least 2 attachment points that are not via points.",
                 "Muscle Editor",
                 JOptionPane.OK_OPTION,
                 JOptionPane.WARNING_MESSAGE,
                 null,
                 options,
                 options[0]);
      } else {
         setPendingChanges(true, currentAct, false);
         setupComponent(currentAct);
         Model model = asm.getModel();
         // Fire an ObjectsDeletedEvent.
         Vector<OpenSimObject> objs = new Vector<OpenSimObject>(1);
         objs.add(mp);
         ObjectsDeletedEvent evnt = new ObjectsDeletedEvent(this, model, objs);
         OpenSimDB.getInstance().setChanged();
         OpenSimDB.getInstance().notifyObservers(evnt);
         // Update the display.
         SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
         vis.updateActuatorGeometry(asm, true);
         ViewDB.getInstance().repaintAll();
      }
   }
   
   public void componentOpened() {
      /*
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      OneActuatorNode muscleNode = (OneActuatorNode) selected[0];
      act = (AbstractActuator)muscleNode.getOpensimObject();
      savedAct = AbstractActuator.safeDownCast(act.copy());
      AttachmentsTab = null;
      WrapTab = null;
      CurrentPathTab = null;
      selectedTabName = null;
      setupComponent(act);
       **/
   }
   
   public void setupCurrentPathPanel(AbstractMuscle asm) {
      if (CurrentPathTab != null)
         ParametersTabbedPanel.remove(CurrentPathTab);
      CurrentPathTab = new javax.swing.JScrollPane();
      CurrentPathTab.setName("Current Path");
      ParametersTabbedPanel.insertTab("Current Path", null, CurrentPathTab, "Current path of the muscle", ParametersTabbedPanel.getTabCount());

      updateCurrentPathPanel(asm);
   }

   private void updateCurrentPathPanel(AbstractMuscle asm) {
      //CurrentPathTab.removeAll();
      javax.swing.JPanel CurrentPathPanel = new javax.swing.JPanel();
      CurrentPathPanel.setLayout(null);
      //CurrentPathPanel.setBackground(new java.awt.Color(200, 200, 255));
      CurrentPathTab.setViewportView(CurrentPathPanel);

      // Put the points in the current path in the CurrentPath tab
      ArrayMusclePoint asmp = asm.getCurrentPath();
      int X = 30;
      int Y = 40;
      
      // Set up the muscle-independent labels
      javax.swing.JLabel currentPathXLabel = new javax.swing.JLabel();
      currentPathXLabel.setText("X");
      currentPathXLabel.setBounds(X + 35, Y - 30, 8, 16);
      javax.swing.JLabel currentPathYLabel = new javax.swing.JLabel();
      currentPathYLabel.setText("Y");
      currentPathYLabel.setBounds(X + 95, Y - 30, 8, 16);
      javax.swing.JLabel currentPathZLabel = new javax.swing.JLabel();
      currentPathZLabel.setText("Z");
      currentPathZLabel.setBounds(X + 155, Y - 30, 8, 16);
      javax.swing.JLabel currentPathBodyLabel = new javax.swing.JLabel();
      currentPathBodyLabel.setText("Body");
      currentPathBodyLabel.setBounds(X + 210, Y - 30, 30, 16);
      javax.swing.JLabel currentPathSelLabel = new javax.swing.JLabel();
      currentPathSelLabel.setText("Type");
      currentPathSelLabel.setBounds(X + 290, Y - 30, 30, 16);
      CurrentPathPanel.add(currentPathXLabel);
      CurrentPathPanel.add(currentPathYLabel);
      CurrentPathPanel.add(currentPathZLabel);
      CurrentPathPanel.add(currentPathBodyLabel);
      CurrentPathPanel.add(currentPathSelLabel);
      
      for (int i = 0; i < asmp.getSize(); i++) {
         javax.swing.JLabel indexLabel = new javax.swing.JLabel();
         javax.swing.JLabel xField = new javax.swing.JLabel();
         xField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel yField = new javax.swing.JLabel();
         yField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel zField = new javax.swing.JLabel();
         zField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel bodyLabel = new javax.swing.JLabel();
         javax.swing.JLabel typeLabel = new javax.swing.JLabel();
         indexLabel.setText(intPropFormat.format(i+1) + ".");
         xField.setText(positionFormat.format(asmp.get(i).getAttachmentCoord(0)));
         yField.setText(positionFormat.format(asmp.get(i).getAttachmentCoord(1)));
         zField.setText(positionFormat.format(asmp.get(i).getAttachmentCoord(2)));
         bodyLabel.setText(asmp.get(i).getBodyName());
         if (asmp.get(i).getWrapObject() != null)
            typeLabel.setText("wrap" + " (" + asmp.get(i).getWrapObject().getName() + ")");
         else if (MuscleViaPoint.safeDownCast(asmp.get(i)) != null)
            typeLabel.setText("via");
         else if (MovingMusclePoint.safeDownCast(asmp.get(i)) != null)
            typeLabel.setText("moving");
         else
            typeLabel.setText("fixed");

         int height = Y + i * 22;
         int width = 60;
         indexLabel.setBounds(X - 20, height, 20, 21);
         xField.setBounds(X, height, width, 21);
         yField.setBounds(X + width + 1, height, width, 21);
         zField.setBounds(X + 2*width + 2, height, width, 21);
         bodyLabel.setBounds(X + 3*width + 10, height, 90, 21);
         typeLabel.setBounds(X + 3*width + 110, height, 120, 21);
         CurrentPathPanel.add(indexLabel);
         CurrentPathPanel.add(xField);
         CurrentPathPanel.add(yField);
         CurrentPathPanel.add(zField);
         CurrentPathPanel.add(bodyLabel);
         CurrentPathPanel.add(typeLabel);
      }
      Dimension d = new Dimension(400, Y + asmp.getSize() * 22);
      CurrentPathPanel.setPreferredSize(d);
   }
   
   public void setupWrapPanel(AbstractMuscle asm) {
      if (WrapTab != null)
         ParametersTabbedPanel.remove(WrapTab);
      javax.swing.JScrollPane WrapTab = new javax.swing.JScrollPane();
      javax.swing.JPanel WrapPanel = new javax.swing.JPanel();
      WrapPanel.setLayout(null);
      //WrapPanel.setBackground(new java.awt.Color(200, 200, 255));
      WrapTab.setViewportView(WrapPanel);
      WrapTab.setName("Wrapping");
      ParametersTabbedPanel.insertTab("Wrapping", null, WrapTab, "Wrapping parameters", ParametersTabbedPanel.getTabCount());
      
      // Set up the Wrap Panel
      int i, j, k, wCount = 0;
      int numAttachments = asm.getAttachmentSet().getSize();
      int X = 80;
      int Y = 40;
      BodySet bodies = asm.getModel().getDynamicsEngine().getBodySet();
      
      SetMuscleWrap smw = asm.getWrapSet();
      String[] startPointNames = new String[numAttachments + 1];
      startPointNames[0] = new String("first");
      String[] endPointNames = new String[numAttachments + 1];
      endPointNames[numAttachments] = new String("last");
      for (i = 0; i < numAttachments; i++) {
         startPointNames[i+1] = String.valueOf(i+1);
         endPointNames[i] = String.valueOf(i+1);
      }
      
      // Count the number of wrap objects not currently assigned to this muscle.
      int numWrapObjects = 0;
      for (i = 0; i < bodies.getSize(); i++) {
         numWrapObjects += bodies.get(i).getWrapObjectSet().getSize();
      }
      numWrapObjects -= smw.getSize();
      
      // Create an array of names of all of the model's wrap objects
      // that are not currently assigned to this muscle. These will be
      // used to make a comboBox that appears when the user clicks the
      // "add" button.
      wrapObjectNames = new String[numWrapObjects];
      for (i = 0; i < bodies.getSize(); i++) {
         SetWrapObject wrapObjects = bodies.get(i).getWrapObjectSet();
         for (j = 0; j < wrapObjects.getSize(); j++) {
            for (k = 0; k < smw.getSize(); k++) {
               if (AbstractWrapObject.getCPtr(wrapObjects.get(j)) == AbstractWrapObject.getCPtr(smw.get(k).getWrapObject()))
                  break;
            }
            if (k == smw.getSize())
               wrapObjectNames[wCount++] = new String(wrapObjects.get(j).getName());
         }
      }
      
      // Set up the muscle-independent labels
      javax.swing.JLabel wrapObjectLabel = new javax.swing.JLabel();
      wrapObjectLabel.setText("Object");
      wrapObjectLabel.setBounds(X + 30, 10, 50, 16);
      WrapPanel.add(wrapObjectLabel);
      javax.swing.JLabel wrapMethodLabel = new javax.swing.JLabel();
      wrapMethodLabel.setText("Method");
      wrapMethodLabel.setBounds(X + 150, 10, 50, 16);
      WrapPanel.add(wrapMethodLabel);
      javax.swing.JLabel wrapStartLabel = new javax.swing.JLabel();
      wrapStartLabel.setText("Start Pt");
      wrapStartLabel.setBounds(X + 223, 10, 80, 16);
      WrapPanel.add(wrapStartLabel);
      javax.swing.JLabel wrapEndLabel = new javax.swing.JLabel();
      wrapEndLabel.setText("End Pt");
      wrapEndLabel.setBounds(X + 285, 10, 80, 16);
      WrapPanel.add(wrapEndLabel);
      //javax.swing.JLabel editLabel = new javax.swing.JLabel();
      //editLabel.setText("Edit");
      //editLabel.setBounds(X + 355, 10, 40, 16);
      //WrapPanel.add(editLabel);
      
      for (i = 0; i < smw.getSize(); i++) {
         final int num = i;
         boolean isEllipsoid = false;
         AbstractWrapObject awo = smw.get(i).getWrapObject();
         WrapEllipsoid we = WrapEllipsoid.safeDownCast(awo);
         if (we != null)
            isEllipsoid = true;
         javax.swing.JLabel indexLabel = new javax.swing.JLabel();
         javax.swing.JComboBox methodComboBox = new javax.swing.JComboBox();
         if (isEllipsoid == false)
            methodComboBox.setEnabled(false);
         javax.swing.JComboBox startComboBox = new javax.swing.JComboBox();
         javax.swing.JComboBox endComboBox = new javax.swing.JComboBox();
         indexLabel.setText(intPropFormat.format(i+1) + ". " + awo.getName());
         if (isEllipsoid == true) {
            methodComboBox.setModel(new javax.swing.DefaultComboBoxModel(wrapMethodNames));
            methodComboBox.setSelectedIndex(findElement(wrapMethodNames, smw.get(i).getMethodName()));
            methodComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  setWrapMethod(((javax.swing.JComboBox)evt.getSource()), num);
               }
            });
         }
         
         startComboBox.setModel(new javax.swing.DefaultComboBoxModel(startPointNames));
         int start = smw.get(i).getStartPoint();
         if (start < 0)
            startComboBox.setSelectedIndex(0);
         else
            startComboBox.setSelectedIndex(findElement(startPointNames, String.valueOf(start)));
         startComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               setWrapStartRange(((javax.swing.JComboBox)evt.getSource()), num);
            }
         });
         
         endComboBox.setModel(new javax.swing.DefaultComboBoxModel(endPointNames));
         int end = smw.get(i).getEndPoint();
         if (end < 0)
            endComboBox.setSelectedIndex(endComboBox.getItemCount()-1);
         else
            endComboBox.setSelectedIndex(findElement(endPointNames, String.valueOf(end)));
         endComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               setWrapEndRange(((javax.swing.JComboBox)evt.getSource()), num);
            }
         });
         
         indexLabel.setBounds(X - 20, Y + i * 22, 200, 21);
         methodComboBox.setBounds(X + 130, Y + i * 22, 80, 21);
         startComboBox.setBounds(X + 220, Y + i * 22, 50, 21);
         endComboBox.setBounds(X + 280, Y + i * 22, 50, 21);
         WrapPanel.add(indexLabel);
         WrapPanel.add(methodComboBox);
         WrapPanel.add(startComboBox);
         WrapPanel.add(endComboBox);
         
         javax.swing.JButton upButton = new javax.swing.JButton();
         upButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/upArrow.png")));
         upButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/upArrow_selected.png")));
         upButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/upArrow_rollover.png")));
         upButton.setToolTipText("Move this wrap object up in the order");
         upButton.setBorder(null);
         upButton.setBorderPainted(false);
         upButton.setContentAreaFilled(false);
         upButton.setMargin(new java.awt.Insets(1, 1, 1, 1));
         upButton.setBounds(X - 75, Y + 3 + i * 22, 15, 15);
         if (i > 0)
            upButton.setEnabled(true);
         else
            upButton.setEnabled(false);
         upButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               moveUpMuscleWrap(num);
            }
         });
         WrapPanel.add(upButton);
         
         javax.swing.JButton downButton = new javax.swing.JButton();
         downButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/downArrow.png")));
         downButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/downArrow_selected.png")));
         downButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/downArrow_rollover.png")));
         downButton.setToolTipText("Move this wrap object down in the order");
         downButton.setBorder(null);
         downButton.setBorderPainted(false);
         downButton.setContentAreaFilled(false);
         downButton.setMargin(new java.awt.Insets(1, 1, 1, 1));
         downButton.setBounds(X - 58, Y + 3 + i * 22, 15, 15);
         if (smw.getSize() > 1 && i < smw.getSize() - 1)
            downButton.setEnabled(true);
         else
            downButton.setEnabled(false);
         downButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               moveDownMuscleWrap(num);
            }
         });
         WrapPanel.add(downButton);
         
         //C:\\SimTK\\OpenSim\\Applications\\Gui\\opensim\\view\\src\\org\\opensim\\view\\editors\\
         javax.swing.JButton deleteButton = new javax.swing.JButton();
         deleteButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/delete.png")));
         deleteButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/delete_selected.png")));
         deleteButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/delete_rollover.png")));
         deleteButton.setToolTipText("Delete this wrap object from this muscle");
         deleteButton.setBorder(null);
         deleteButton.setBorderPainted(false);
         deleteButton.setContentAreaFilled(false);
         deleteButton.setBounds(X - 38, Y + 3 + i * 22, 15, 15);
         deleteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               deleteMuscleWrap(num);
            }
         });
         WrapPanel.add(deleteButton);
      }
      
      // The add menu
      final javax.swing.JPopupMenu addMenu = new javax.swing.JPopupMenu();
      for (i = 0; i < numWrapObjects; i++) {
         javax.swing.JMenuItem menuItem = new JMenuItem(wrapObjectNames[i]);
         final int index = i;
         menuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               addMuscleWrap(index);
            }
         });
         addMenu.add(menuItem);
      }
      
      // Add the "add" line
      javax.swing.JButton upButton = new javax.swing.JButton();
      upButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/upArrow.png")));
      upButton.setBorder(null);
      upButton.setBorderPainted(false);
      upButton.setContentAreaFilled(false);
      upButton.setMargin(new java.awt.Insets(1, 1, 1, 1));
      upButton.setBounds(X - 75, Y + 3 + smw.getSize() * 22, 15, 15);
      upButton.setEnabled(false);
      WrapPanel.add(upButton);
      
      javax.swing.JButton downButton = new javax.swing.JButton();
      downButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/downArrow.png")));
      downButton.setBorder(null);
      downButton.setBorderPainted(false);
      downButton.setContentAreaFilled(false);
      downButton.setMargin(new java.awt.Insets(1, 1, 1, 1));
      downButton.setBounds(X - 58, Y + 3 + smw.getSize() * 22, 15, 15);
      downButton.setEnabled(false);
      WrapPanel.add(downButton);
      
      javax.swing.JButton addButton = new javax.swing.JButton();
      addButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/add.png")));
      addButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/add_selected.png")));
      addButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/add_rollover.png")));
      addButton.setBorder(null);
      addButton.setBorderPainted(false);
      addButton.setContentAreaFilled(false);
      addButton.setToolTipText("Add an existing wrap object to this muscle");
      addButton.setBounds(X - 38, Y + 3 + smw.getSize() * 22, 15, 15);
      WrapPanel.add(addButton);
      
      javax.swing.JLabel indexLabel = new javax.swing.JLabel();
      indexLabel.setText(intPropFormat.format(smw.getSize()+1) + ". existing wrap object");
      indexLabel.setEnabled(false);
      indexLabel.setBounds(X - 20, Y + smw.getSize() * 22, 200, 21);
      WrapPanel.add(indexLabel);
      
      javax.swing.JComboBox methodComboBox = new javax.swing.JComboBox();
      methodComboBox.setEnabled(false);
      methodComboBox.setBounds(X + 130, Y + smw.getSize() * 22, 80, 21);
      WrapPanel.add(methodComboBox);
      
      javax.swing.JComboBox startComboBox = new javax.swing.JComboBox();
      javax.swing.JComboBox endComboBox = new javax.swing.JComboBox();
      startComboBox.setEnabled(false);
      endComboBox.setEnabled(false);
      startComboBox.setBounds(X + 220, Y + smw.getSize() * 22, 50, 21);
      endComboBox.setBounds(X + 280, Y + smw.getSize() * 22, 50, 21);
      WrapPanel.add(startComboBox);
      WrapPanel.add(endComboBox);
      
      class PopupListener extends MouseAdapter {
         public void mousePressed(MouseEvent e) {
            //maybeShowPopup(e);
            addMenu.show(e.getComponent(),
                    e.getX(), e.getY());
         }
         
         public void mouseReleased(MouseEvent e) {
            maybeShowPopup(e);
         }
         
         private void maybeShowPopup(MouseEvent e) {
            if (e.isPopupTrigger()) {
               addMenu.show(e.getComponent(),
                       e.getX(), e.getY());
            }
         }
      }
      
      MouseListener popupListener = new PopupListener();
      addButton.addMouseListener(popupListener);
      
      Dimension d = new Dimension(350, Y + 20 + smw.getSize() * 22);
      WrapPanel.setPreferredSize(d);
   }
   
   public void setupAttachmentPanel(AbstractMuscle asm) {
      if (AttachmentsTab != null)
         ParametersTabbedPanel.remove(AttachmentsTab);
      AttachmentsTab = new javax.swing.JScrollPane();
      AttachmentsTab.setName("Attachments");
      ParametersTabbedPanel.insertTab("Attachments", null, AttachmentsTab, "Attachment points", 0);

      updateAttachmentPanel(asm);
   }

   private void updateAttachmentPanel(AbstractMuscle asm) {
      javax.swing.JPanel AttachmentsPanel = new javax.swing.JPanel();
      AttachmentsPanel.setLayout(null);
      //AttachmentsPanel.setBackground(new java.awt.Color(200, 200, 255));
      AttachmentsTab.setViewportView(AttachmentsPanel);
      
      // Put the attachment points in the attachments tab
      MusclePointSet musclePoints = asm.getAttachmentSet();
      int aCount = 0;
      int X = 30;
      int Y = 40;
      
      // Set up the muscle-independent labels
      boolean anyViaPoints = false;
      javax.swing.JLabel attachmentSelLabel = new javax.swing.JLabel();
      attachmentSelLabel.setText("Sel");
      attachmentSelLabel.setBounds(X + 3, Y - 30, 25, 16);
      javax.swing.JLabel attachmentTypeLabel = new javax.swing.JLabel();
      attachmentTypeLabel.setText("Type");
      attachmentTypeLabel.setBounds(X + 45, Y - 30, 40, 16);
      javax.swing.JLabel attachmentXLabel = new javax.swing.JLabel();
      attachmentXLabel.setText("X");
      attachmentXLabel.setBounds(X + 160, Y - 30, 8, 16);
      javax.swing.JLabel attachmentYLabel = new javax.swing.JLabel();
      attachmentYLabel.setText("Y");
      attachmentYLabel.setBounds(X + 295, Y - 30, 8, 16);
      javax.swing.JLabel attachmentZLabel = new javax.swing.JLabel();
      attachmentZLabel.setText("Z");
      attachmentZLabel.setBounds(X + 430, Y - 30, 8, 16);
      javax.swing.JLabel attachmentBodyLabel = new javax.swing.JLabel();
      attachmentBodyLabel.setText("Body");
      attachmentBodyLabel.setBounds(X + 532, Y - 30, 30, 16);
      javax.swing.JLabel coordLabel = new javax.swing.JLabel();
      coordLabel.setText("Coordinate");
      coordLabel.setBounds(X + 640, Y - 30, 90, 16);
      javax.swing.JLabel rangeMinLabel = new javax.swing.JLabel();
      rangeMinLabel.setText("Min");
      rangeMinLabel.setBounds(X + 765, Y - 30, 60, 16);
      javax.swing.JLabel rangeMaxLabel = new javax.swing.JLabel();
      rangeMaxLabel.setText("Max");
      rangeMaxLabel.setBounds(X + 830, Y - 30, 60, 16);
      AttachmentsPanel.add(attachmentSelLabel);
      AttachmentsPanel.add(attachmentTypeLabel);
      AttachmentsPanel.add(attachmentXLabel);
      AttachmentsPanel.add(attachmentYLabel);
      AttachmentsPanel.add(attachmentZLabel);
      AttachmentsPanel.add(attachmentBodyLabel);

      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(asm.getModel());
      String[] bodyNames = guiElem.getBodyNames();
      String[] coordinateNames = guiElem.getCoordinateNames();
      int numGuiLines = 0; // after for loop, will = numPoints + numMovingMusclePoints

      attachmentSelectBox = new javax.swing.JCheckBox[musclePoints.getSize()];
      
      for (int i = 0; i < musclePoints.getSize(); i++, numGuiLines++) {
         MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(i));
         MovingMusclePoint mmp = MovingMusclePoint.safeDownCast(musclePoints.get(i));

         int height = Y + numGuiLines * 25;
         int width = 135;
         int x = X;
         int y = Y;
         final int num = i;

         // The number label for the point
         javax.swing.JLabel indexLabel = null;
         indexLabel = new javax.swing.JLabel();
         indexLabel.setText(intPropFormat.format(num+1) + ".");
         indexLabel.setBounds(X - 20, height, 20, 21);
         AttachmentsPanel.add(indexLabel);

         // The checkbox for selecting/unselecting the point for editing
         attachmentSelectBox[i] = new javax.swing.JCheckBox();
         attachmentSelectBox[i].setBounds(x, height, 21, 21);
         attachmentSelectBox[i].setToolTipText("Click to select/unselect this attachment point");
         attachmentSelectBox[i].addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentSelected(((javax.swing.JCheckBox)evt.getSource()), num);
            }
         });
         AttachmentsPanel.add(attachmentSelectBox[i]);
         if (mmp != null)
            attachmentSelectBox[i].setEnabled(false);
         x += 30;

         // The combo box specifying the type of the point
         javax.swing.JComboBox pointTypeComboBox = new javax.swing.JComboBox();
         pointTypeComboBox.setModel(new javax.swing.DefaultComboBoxModel(musclePointTypeNames));
         pointTypeComboBox.setBounds(x, height, 65, 21);
         pointTypeComboBox.setToolTipText("The type of this attachment point");
         pointTypeComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               MusclePointTypeChosen(((javax.swing.JComboBox)evt.getSource()), num);
            }
         });
         int typeIndex = 0;
         if (via != null)
            typeIndex = 1;
         else if (mmp != null)
            typeIndex = 2;
         pointTypeComboBox.setSelectedIndex(typeIndex);
         AttachmentsPanel.add(pointTypeComboBox);
         x += 70;

         // The X coordinate of the point
         if (mmp == null) {
            javax.swing.JTextField xField = new javax.swing.JTextField();
            xField.setHorizontalAlignment(SwingConstants.TRAILING);
            xField.setBounds(x, height, width - 5, 21);
            xField.setText(positionFormat.format(musclePoints.get(i).getAttachmentCoord(0)));
            xField.setToolTipText("X coordinate of the attachment point");
            xField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 0);
               }
            });
            xField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  if (!evt.isTemporary())
                     AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 0);
               }
            });
            AttachmentsPanel.add(xField);
         } else {
            numGuiLines++;
            javax.swing.JButton editXButton = new javax.swing.JButton();
            editXButton.setBounds(x, height, width - 5, 21);
            editXButton.setText("Edit");
            editXButton.setEnabled(true);
            editXButton.setToolTipText("Edit the function controlling this X coordinate");
            editXButton.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  EditMusclePointFunction(((javax.swing.JButton)evt.getSource()), num, 0);
               }
            });
            AttachmentsPanel.add(editXButton);
            // Combo box for changing the coordinate. If the function is a Constant,
            // disable the combo box.
            javax.swing.JComboBox XCoordComboBox = new javax.swing.JComboBox();
            XCoordComboBox.setModel(new javax.swing.DefaultComboBoxModel(coordinateNames));
            XCoordComboBox.setBounds(x, height + 22, width - 5, 21);
            XCoordComboBox.setToolTipText("The coordinate that controls the X offset for this attachment point");
            XCoordComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  MovingMusclePointCoordinateChosen(((javax.swing.JComboBox)evt.getSource()), num, 0);
               }
            });
            Function Xfunction = mmp.getXFunction();
            if (Xfunction != null && Xfunction instanceof Constant) {
               XCoordComboBox.setEnabled(false);
            } else {
               XCoordComboBox.setSelectedIndex(findElement(coordinateNames, mmp.getXCoordinateName()));
            }
            AttachmentsPanel.add(XCoordComboBox);
         }
         x += width;

         // The Y coordinate of the point
         if (mmp == null) {
            javax.swing.JTextField yField = new javax.swing.JTextField();
            yField.setHorizontalAlignment(SwingConstants.TRAILING);
            yField.setBounds(x, height, width - 5, 21);
            yField.setText(positionFormat.format(musclePoints.get(i).getAttachmentCoord(1)));
            yField.setToolTipText("Y coordinate of the attachment point");
            yField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 1);
               }
            });
            yField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  if (!evt.isTemporary())
                     AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 1);
               }
            });
            AttachmentsPanel.add(yField);
         } else {
            javax.swing.JButton editYButton = new javax.swing.JButton();
            editYButton.setBounds(x, height, width - 5, 21);
            editYButton.setText("Edit");
            editYButton.setEnabled(true);
            editYButton.setToolTipText("Edit the function controlling this Y coordinate");
            editYButton.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  EditMusclePointFunction(((javax.swing.JButton)evt.getSource()), num, 1);
               }
            });
            AttachmentsPanel.add(editYButton);
            // Combo box for changing the coordinate. If the function is a Constant,
            // disable the combo box.
            javax.swing.JComboBox YCoordComboBox = new javax.swing.JComboBox();
            YCoordComboBox.setModel(new javax.swing.DefaultComboBoxModel(coordinateNames));
            YCoordComboBox.setBounds(x, height + 22, width - 5, 21);
            YCoordComboBox.setToolTipText("The coordinate that controls the Y offset for this attachment point");
            YCoordComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  MovingMusclePointCoordinateChosen(((javax.swing.JComboBox)evt.getSource()), num, 1);
               }
            });
            Function Yfunction = mmp.getYFunction();
            if (Yfunction != null && Yfunction instanceof Constant) {
               YCoordComboBox.setEnabled(false);
            } else {
               YCoordComboBox.setSelectedIndex(findElement(coordinateNames, mmp.getYCoordinateName()));
            }
            AttachmentsPanel.add(YCoordComboBox);
         }
         x += width;

         // The Z coordinate of the point
         if (mmp == null) {
            javax.swing.JTextField zField = new javax.swing.JTextField();
            zField.setHorizontalAlignment(SwingConstants.TRAILING);
            zField.setBounds(x, height, width - 5, 21);
            zField.setText(positionFormat.format(musclePoints.get(i).getAttachmentCoord(2)));
            zField.setToolTipText("Z coordinate of the attachment point");
            zField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 2);
               }
            });
            zField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  if (!evt.isTemporary())
                     AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 2);
               }
            });
            AttachmentsPanel.add(zField);
         } else {
            javax.swing.JButton editZButton = new javax.swing.JButton();
            editZButton.setBounds(x, height, width - 5, 21);
            editZButton.setText("Edit");
            editZButton.setEnabled(true);
            editZButton.setToolTipText("Edit the function controlling this Z coordinate");
            editZButton.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  EditMusclePointFunction(((javax.swing.JButton)evt.getSource()), num, 2);
               }
            });
            AttachmentsPanel.add(editZButton);
            // Combo box for changing the coordinate. If the function is a Constant,
            // disable the combo box.
            javax.swing.JComboBox ZCoordComboBox = new javax.swing.JComboBox();
            ZCoordComboBox.setModel(new javax.swing.DefaultComboBoxModel(coordinateNames));
            ZCoordComboBox.setBounds(x, height + 22, width - 5, 21);
            ZCoordComboBox.setToolTipText("The coordinate that controls the Z offset for this attachment point");
            ZCoordComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  MovingMusclePointCoordinateChosen(((javax.swing.JComboBox)evt.getSource()), num, 2);
               }
            });
            Function Zfunction = mmp.getZFunction();
            if (Zfunction != null && Zfunction instanceof Constant) {
               ZCoordComboBox.setEnabled(false);
            } else {
               ZCoordComboBox.setSelectedIndex(findElement(coordinateNames, mmp.getZCoordinateName()));
            }
            AttachmentsPanel.add(ZCoordComboBox);
         }
         x += width;

         // The combo box containing the body the point is attached to
         javax.swing.JComboBox comboBox = new javax.swing.JComboBox();
         comboBox.setModel(new javax.swing.DefaultComboBoxModel(bodyNames));
         comboBox.setSelectedIndex(findElement(bodyNames, musclePoints.get(i).getBodyName()));
         comboBox.setBounds(x, height, 90, 21);
         comboBox.setToolTipText("Body the attachment point is fixed to");
         comboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentBodyChosen(((javax.swing.JComboBox)evt.getSource()), num);
            }
         });
         AttachmentsPanel.add(comboBox);
         x += 100;
         
         // GUI items for via points (coord combo box, min range field, max range field)
         if (via != null) {
            anyViaPoints = true;
            double conversion = 1.0;
            NumberFormat nf =  angleFormat;
            AbstractCoordinate coordinate = via.getCoordinate();
            if (coordinate != null) {
               if (coordinate.getMotionType() == AbstractDof.DofType.Rotational) {
                  conversion = 180.0/Math.PI;
                  nf = angleFormat;
               } else {
                  nf = positionFormat;
               }
            }

            // The combo box containing the coordinate for the via point
            javax.swing.JComboBox coordComboBox = new javax.swing.JComboBox();
            coordComboBox.setModel(new javax.swing.DefaultComboBoxModel(coordinateNames));
            coordComboBox.setSelectedIndex(findElement(coordinateNames, via.getCoordinateName()));
            coordComboBox.setBounds(x, height, 130, 21);
            coordComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  ViaCoordinateChosen(((javax.swing.JComboBox)evt.getSource()), num);
               }
            });
            AttachmentsPanel.add(coordComboBox);
            x += 140;

            // The min range of the coordinate range
            javax.swing.JTextField rangeMinField = new javax.swing.JTextField();
            rangeMinField.setText(nf.format(via.getRange().getitem(0)*conversion));
            rangeMinField.setBounds(x, height, 60, 21);
            rangeMinField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  RangeMinEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            rangeMinField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  if (!evt.isTemporary())
                     RangeMinEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            AttachmentsPanel.add(rangeMinField);
            x += 65;

            // The max range of the coordinate range
            javax.swing.JTextField rangeMaxField = new javax.swing.JTextField();
            rangeMaxField.setText(nf.format(via.getRange().getitem(1)*conversion));
            rangeMaxField.setBounds(x, height, 60, 21);
            rangeMaxField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  RangeMaxEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            rangeMaxField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  if (!evt.isTemporary())
                     RangeMaxEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            AttachmentsPanel.add(rangeMaxField);
         }
      }
      
      // The add menu
      final javax.swing.JPopupMenu addMenu = new javax.swing.JPopupMenu();
      javax.swing.JMenuItem firstMenuItem = new JMenuItem("before 1");
      firstMenuItem.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            addAttachmentPerformed(0);
         }
      });
      addMenu.add(firstMenuItem);
      for (int i = 0; i < musclePoints.getSize() - 1; i++) {
         javax.swing.JMenuItem menuItem = new JMenuItem("between "+String.valueOf(i+1)+" and "+String.valueOf(i+2));
         final int index = i + 1;
         menuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               addAttachmentPerformed(index);
            }
         });
         addMenu.add(menuItem);
      }
      javax.swing.JMenuItem lastMenuItem = new JMenuItem("after "+String.valueOf(musclePoints.getSize()));
      final int index = musclePoints.getSize();
      lastMenuItem.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            addAttachmentPerformed(index);
         }
      });
      addMenu.add(lastMenuItem);
      
      // Add the "add" button
      javax.swing.JButton addButton = new javax.swing.JButton();
      addButton.setText("Add");
      addButton.setToolTipText("Add an attachment point");
      addButton.setBounds(X + 100, Y + 20 + numGuiLines * 25, 70, 21);
      AttachmentsPanel.add(addButton);
      
      class PopupListener extends MouseAdapter {
         public void mousePressed(MouseEvent e) {
            //maybeShowPopup(e);
            addMenu.show(e.getComponent(),
                    e.getX(), e.getY());
         }
         
         public void mouseReleased(MouseEvent e) {
            maybeShowPopup(e);
         }
         
         private void maybeShowPopup(MouseEvent e) {
            if (e.isPopupTrigger()) {
               addMenu.show(e.getComponent(),
                       e.getX(), e.getY());
            }
         }
      }
      
      MouseListener popupListener = new PopupListener();
      addButton.addMouseListener(popupListener);
      
      // the "delete" menu
      final javax.swing.JPopupMenu deleteMenu = new javax.swing.JPopupMenu();
      for (int i = 0; i < musclePoints.getSize(); i++) {
         javax.swing.JMenuItem menuItem = new JMenuItem(String.valueOf(i+1));
         final int deleteIndex = i;
         menuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               deleteAttachmentPerformed(deleteIndex);
            }
         });
         deleteMenu.add(menuItem);
      }
      
      // Add the "delete" button
      javax.swing.JButton deleteButton = new javax.swing.JButton();
      deleteButton.setText("Delete");
      deleteButton.setToolTipText("Delete an attachment point");
      deleteButton.setBounds(X + 200, Y + 20 + numGuiLines * 25, 70, 21);
      AttachmentsPanel.add(deleteButton);
      
      class PopupListenerDelete extends MouseAdapter {
         public void mousePressed(MouseEvent e) {
            //maybeShowPopup(e);
            deleteMenu.show(e.getComponent(),
                    e.getX(), e.getY());
         }
         
         public void mouseReleased(MouseEvent e) {
            maybeShowPopup(e);
         }
         
         private void maybeShowPopup(MouseEvent e) {
            if (e.isPopupTrigger()) {
               deleteMenu.show(e.getComponent(),
                       e.getX(), e.getY());
            }
         }
      }
      
      MouseListener popupListenerDelete = new PopupListenerDelete();
      deleteButton.addMouseListener(popupListenerDelete);
      
      Dimension d = new Dimension(640, Y + 45 + numGuiLines * 22);
      if (anyViaPoints) {
         d.width = 920;
         AttachmentsPanel.add(coordLabel);
         AttachmentsPanel.add(rangeMinLabel);
         AttachmentsPanel.add(rangeMaxLabel);
      }
      AttachmentsPanel.setPreferredSize(d);
      
      // Update the checked/unchecked state of the selected checkboxes
      ArrayList<SelectedObject> selectedObjects = ViewDB.getInstance().getSelectedObjects();
      for (int i = 0; i < selectedObjects.size(); i++)
         updateAttachmentSelections(selectedObjects.get(i), true);
   }
   
   public void setupComponent(AbstractActuator newAct) {
      // Remove all previous GUI components and their panels.
      // If the type of actuator changed since the last time
      // the panels were set up, there could be different
      // numbers and types of components and panels.
      // But before they are removed, store the name of the
      // currently selected tab (if any) so that you can try
      // to restore this selection (e.g., after the "restore"
      // button is pressed.
      // Since MuscleComboBox was added to the GUI, the muscle
      // editor now always has a current actuator (as long as there
      // is a current model). So if 'act' is passed in as null,
      // make the model's first actuator the current one.

      //currentModel = OpenSimDB.getInstance().getCurrentModel();
      SingleModelGuiElements guiElem = null;
      if (currentModel != null && newAct == null && currentModel.getActuatorSet().getSize() > 0)
         newAct = currentModel.getActuatorSet().get(0);

      // Save the currently selected GUI tab.
      if (currentAct != null) {
         Component comp = ParametersTabbedPanel.getSelectedComponent();
         if (comp != null)
            selectedTabName = comp.getName();
         else
            selectedTabName = null;
      }
      ParametersTabbedPanel.removeAll();
      AttachmentsTab = null;
      WrapTab = null;
      CurrentPathTab = null;

      // Set the current actuator to the newly selected one (should only be null
      // if the model is null or if the model has no actuators).
      currentAct = newAct;

      if (currentModel != null) {
         guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
         ModelNameLabel.setText("Model: " + currentModel.getName());
         if (currentModel.getActuatorSet().getSize() > 0) {
            MuscleComboBox.setEnabled(true);
            MuscleComboBox.setModel(new javax.swing.DefaultComboBoxModel(guiElem.getActuatorNames(true)));
         } else {
            MuscleComboBox.setEnabled(false);
         }
      } else {
         ModelNameLabel.setText("Model: No models");
         MuscleNameTextField.setText("");
         MuscleNameTextField.setEnabled(false);
         MuscleTypeLabel.setText("");
         //MuscleTypeComboBox.setEnabled(false);
         MuscleComboBox.setEnabled(false);
         BackupButton.setEnabled(false);
         RestoreButton.setEnabled(false);
         BackupAllButton.setEnabled(false);
         RestoreAllButton.setEnabled(false);
         return;
      }
      
      if (currentAct == null) {
         MuscleTypeLabel.setText("");
         MuscleNameTextField.setText("");
         MuscleNameTextField.setEnabled(false);
         //MuscleTypeComboBox.setEnabled(false);
         BackupButton.setEnabled(false);
         RestoreButton.setEnabled(false);
         BackupAllButton.setEnabled(false);
         RestoreAllButton.setEnabled(false);
         return;
      } else {
         MuscleTypeLabel.setText("Type: " + currentAct.getType());
         MuscleNameTextField.setEnabled(true);
         //MuscleTypeComboBox.setEnabled(true);
         BackupButton.setEnabled(true);
         BackupAllButton.setEnabled(true);
         MuscleComboBox.setSelectedIndex(findElement(guiElem.getActuatorNames(true), currentAct.getName()));
      }
      
      //MuscleTypeComboBox.setModel(new javax.swing.DefaultComboBoxModel(guiElem.getActuatorClassNames()));
      //MuscleTypeComboBox.setSelectedIndex(findElement(guiElem.getActuatorClassNames(), act.getType()));
      //MuscleTypeComboBox.addActionListener(new java.awt.event.ActionListener() {
      //   public void actionPerformed(java.awt.event.ActionEvent evt) {
      //      MuscleTypeComboBoxActionPerformed(MuscleTypeComboBox);
      //   }
      //});
      
      // Add the attachment panel first so it will always have index=0
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      if (asm != null)
         setupAttachmentPanel(asm);
      
      int i, j;
      MuscleNameTextField.setText(currentAct.getName());
      PropertySet ps = currentAct.getPropertySet();
      
      // Create the panels to hold the properties.
      ArrayPtrsPropertyGroup groups = ps.getGroups();
      int numGroups = groups.getSize();
      javax.swing.JScrollPane propTab[] = new javax.swing.JScrollPane[numGroups + 1];
      javax.swing.JPanel propPanel[] = new javax.swing.JPanel[numGroups + 1];
      int tabPropertyCount[] = new int[numGroups + 1];
      for (i = 0; i < numGroups; i++) {
         PropertyGroup pg = groups.get(i);
         propTab[i] = new javax.swing.JScrollPane();
         propPanel[i] = new javax.swing.JPanel();
         propPanel[i].setLayout(null);
         //propPanel[i].setBackground(new java.awt.Color(200, 200, 255));
         propTab[i].setViewportView(propPanel[i]);
         propTab[i].setName(pg.getName());
         ParametersTabbedPanel.addTab(pg.getName(), null, propTab[i], pg.getName());
         tabPropertyCount[i] = 0;
      }
      // Create the "other" panel to hold properties that are not in a group.
      propTab[numGroups] = new javax.swing.JScrollPane();
      propPanel[numGroups] = new javax.swing.JPanel();
      propPanel[numGroups].setLayout(null);
      //propPanel[numGroups].setBackground(new java.awt.Color(200, 200, 255));
      propTab[numGroups].setViewportView(propPanel[numGroups]);
      propTab[numGroups].setName("Other");
      ParametersTabbedPanel.addTab("Other", null, propTab[numGroups], "other parameters");
      tabPropertyCount[numGroups] = 0;

      // Loop through the properties, adding each one to the appropriate panel.
      for (i = 0; i < ps.getSize(); i++) {
         Property p;
         try {
            p = ps.get(i);
            final int num = i;
            int groupNum = ps.getGroupIndexContaining(p);
            if (groupNum < 0)
               groupNum = numGroups; // this is the index of the "other" panel
            if (p.getType() == org.opensim.modeling.Property.PropertyType.Dbl ||
                    p.getType() == org.opensim.modeling.Property.PropertyType.Int) {
               javax.swing.JLabel propLabel = new javax.swing.JLabel();
               propLabel.setText(p.getName());
               propLabel.setHorizontalAlignment(SwingConstants.RIGHT);
               propLabel.setBounds(20, 22 + tabPropertyCount[groupNum] * 22, 180, 16);
               propLabel.setToolTipText(p.getComment());
               javax.swing.JTextField propField = new javax.swing.JTextField();
               propField.setBounds(210, 20 + tabPropertyCount[groupNum] * 22, 120, 21);
               propField.setHorizontalAlignment(SwingConstants.TRAILING);
               if (p.getType() == org.opensim.modeling.Property.PropertyType.Dbl)
                  propField.setText(doublePropFormat.format(p.getValueDbl()));
               else
                  propField.setText(p.toString());
               propField.setToolTipText(p.getComment());
               propPanel[groupNum].add(propLabel);
               propPanel[groupNum].add(propField);
               tabPropertyCount[groupNum]++;
               if (p.getType() == org.opensim.modeling.Property.PropertyType.Dbl) {
                  propField.addActionListener(new java.awt.event.ActionListener() {
                     public void actionPerformed(java.awt.event.ActionEvent evt) {
                        DoublePropertyEntered(((javax.swing.JTextField)evt.getSource()), num);
                     }
                  });
                  propField.addFocusListener(new java.awt.event.FocusAdapter() {
                     public void focusLost(java.awt.event.FocusEvent evt) {
                        if (!evt.isTemporary())
                           DoublePropertyEntered(((javax.swing.JTextField)evt.getSource()), num);
                     }
                  });
               } else if (p.getType() == org.opensim.modeling.Property.PropertyType.Int) {
                  propField.addActionListener(new java.awt.event.ActionListener() {
                     public void actionPerformed(java.awt.event.ActionEvent evt) {
                        IntPropertyEntered(((javax.swing.JTextField)evt.getSource()), num);
                     }
                  });
                  propField.addFocusListener(new java.awt.event.FocusAdapter() {
                     public void focusLost(java.awt.event.FocusEvent evt) {
                        if (!evt.isTemporary())
                           IntPropertyEntered(((javax.swing.JTextField)evt.getSource()), num);
                     }
                  });
               }
            } else if (p.getType() == org.opensim.modeling.Property.PropertyType.ObjPtr) {
               OpenSimObject obj = p.getValueObjPtr();
               Function func = Function.safeDownCast(obj);
               if (func != null) {
                  javax.swing.JLabel propLabel = new javax.swing.JLabel();
                  propLabel.setText(p.getName());
                  propLabel.setHorizontalAlignment(SwingConstants.RIGHT);
                  propLabel.setBounds(20, 22 + tabPropertyCount[groupNum] * 22, 200, 16);
                  propLabel.setToolTipText(p.getComment());
                  javax.swing.JButton propButton = new javax.swing.JButton();
                  propButton.setBounds(230, 20 + tabPropertyCount[groupNum] * 22, 65, 21);
                  propButton.setText("Edit");
                  propButton.setEnabled(true);
                  propButton.setToolTipText("Edit the function controlling this property");
                  propButton.addActionListener(new java.awt.event.ActionListener() {
                     public void actionPerformed(java.awt.event.ActionEvent evt) {
                        EditPropertyFunction(((javax.swing.JButton)evt.getSource()), num);
                     }
                  });
                  propPanel[groupNum].add(propLabel);
                  propPanel[groupNum].add(propButton);
                  tabPropertyCount[groupNum]++;
               }
            }
         } catch (IOException ex) {
            ex.printStackTrace();
         }
      }
      
      // Set the preferred sizes of the property tabs.
      // If any of them have no properties, remove them
      // from the window.
      for (i = 0; i <= numGroups; i++) {
         if (tabPropertyCount[i] == 0) {
            ParametersTabbedPanel.remove(propTab[i]);
         } else {
            Dimension d = new Dimension(350, 30 + tabPropertyCount[i] * 22);
            propPanel[i].setPreferredSize(d);
         }
      }
      
      // Add the wrap and current panels last
      if (asm != null) {
         setupWrapPanel(asm);
         setupCurrentPathPanel(asm);
      }
      
      // Enable/disable the backup and restore buttons
      updateBackupRestoreButtons();
      
      // Set the selected tab in the ParametersTabbedPanel to the
      // one whose name matches selectedTabName.
      Component[] components = ParametersTabbedPanel.getComponents();
      if (selectedTabName == null) {
         ParametersTabbedPanel.setSelectedComponent(components[0]);
      } else {
         for (i = 0; i < components.length; i++) {
            if (components[i].getName().equals(selectedTabName)) {
               ParametersTabbedPanel.setSelectedComponent(components[i]);
               break;
            }
         }
      }
      
      //Dimension windowSize = MuscleEditorScrollPane.getParent().getSize();
      Dimension d = new Dimension(565, 358);
      MuscleEditorPanel.setPreferredSize(d);
      
      this.revalidate();
      this.repaint();
   }
   
   public void componentClosed() {
      // TODO add custom code on component closing
   }
   
   /** replaces this in object stream */
   public Object writeReplace() {
      return new ResolvableHelper();
   }
   
   protected String preferredID() {
      return PREFERRED_ID;
   }
   
   private int findElement(String[] nameList, String name) {
      int i;
      for (i = 0; i < nameList.length; i++)
         if (nameList[i].equals(name))
            return i;
      return -1;
   }
   
   public void open() {
      AbstractActuator newAct = null;
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if (selected.length > 0 && selected[0] instanceof OneActuatorNode) {
         OneActuatorNode muscleNode = (OneActuatorNode) selected[0];
         newAct = AbstractActuator.safeDownCast(muscleNode.getOpenSimObject());
         if (newAct != null && AbstractActuator.getCPtr(newAct) != AbstractActuator.getCPtr(currentAct)) {
            Model newModel = newAct.getModel();
            if (Model.getCPtr(newModel) != Model.getCPtr(currentModel)) {
               Object[] options = {"OK"};
               int answer = JOptionPane.showOptionDialog(this,
                       "You can only edit muscles that are in the current model.",
                       "Muscle Editor",
                       JOptionPane.DEFAULT_OPTION,
                       JOptionPane.WARNING_MESSAGE,
                       null,
                       options,
                       options[0]);
            } else {
               currentAct = newAct;
               AttachmentsTab = null;
               WrapTab = null;
               CurrentPathTab = null;
               selectedTabName = null;
               setPendingChanges(false, currentAct, false);
               setupComponent(currentAct);
            }
         }
      } else {
         setAllPendingChanges(false);
         setupComponent(null);
      }
      super.open();
      this.requestActive();
   }

   private boolean needToHandleEvent(Observable o, Object arg) {
      if (o instanceof ViewDB) {
         // We only care about ViewDB events if there is a current actuator
         // and the event's model is the muscle editor's current model (unless
         // it's a DragObjectsEvent).
         if (arg instanceof DragObjectsEvent)
            return true;
         if (currentAct == null)
            return false;
         if (arg instanceof OpenSimEvent) {
            OpenSimEvent ev = (OpenSimEvent)arg;
            if (Model.getCPtr(ev.getModel()) != Model.getCPtr(currentModel))
               return false;
         }
         return true;
      } else if (o instanceof OpenSimDB) {
         if (arg instanceof ModelEvent) {
            final ModelEvent evt = (ModelEvent)arg;
            if (evt.getOperation() == ModelEvent.Operation.SetCurrent ||
                    (evt.getOperation() == ModelEvent.Operation.Close &&
                    OpenSimDB.getInstance().getCurrentModel() == null)) {
               return true;
            }
            return false;
         } else if (arg instanceof ObjectSetCurrentEvent) {
            ObjectSetCurrentEvent evt = (ObjectSetCurrentEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            // If any of the event objects is a model not equal to the current model, this means there is a new
            // current model, so we need to handle the event.
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof Model) {
                  if (currentModel == null || !currentModel.equals(objs.get(i))) {
                     return true;
                  }
               }
            }
            return false;
         } else if (arg instanceof ObjectsChangedEvent) {
            if (currentAct == null)
               return false;
            ObjectsChangedEvent evt = (ObjectsChangedEvent)arg;
            if (Model.getCPtr(evt.getModel()) == Model.getCPtr(currentModel))
               return true;
            return false;
         } else if (arg instanceof NameChangedEvent) {
            NameChangedEvent evt = (NameChangedEvent)arg;
            if (evt.getObject() instanceof Model) {
               if (currentModel != null && currentModel.equals(evt.getObject()))
                  return true;
            } else if (evt.getObject() instanceof AbstractActuator) {
               AbstractActuator act = (AbstractActuator)evt.getObject();
               if (currentModel != null && currentModel.equals(act.getModel()))
                  return true;
            }
            return false;
         }
      }
      return true;
   }

   public void update(Observable o, Object arg) {
      if (needToHandleEvent(o, arg) == false)
         return;
      if (o instanceof ViewDB) {
         if (arg instanceof ObjectSelectedEvent) {
            ObjectSelectedEvent ev = (ObjectSelectedEvent)arg;
            updateAttachmentSelections(ev.getSelectedObject(), ev.getState());
         } else if (arg instanceof ClearSelectedObjectsEvent) {
            if (currentAct != null) {
               AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
               if (asm != null) {
                  MusclePointSet musclePoints = asm.getAttachmentSet();
                  for (int i = 0; i < musclePoints.getSize(); i++) {
                     attachmentSelectBox[i].setSelected(false);
                  }
                  this.repaint();
               }
            }
         } else if (arg instanceof DragObjectsEvent) {
            dragMusclePoints((DragObjectsEvent)arg);
         }
      } else if (o instanceof OpenSimDB) {
         // if current model is being switched due to open/close or change current then
         // update tool window
         if (arg instanceof ModelEvent) {
            final ModelEvent evt = (ModelEvent)arg;
            if (evt.getOperation() == ModelEvent.Operation.Close && OpenSimDB.getInstance().getCurrentModel() == null) {
               currentModel = null;
               currentAct = null;
               backupAllActuators();
               setAllPendingChanges(false);
               setupComponent(null);
            }
            // Do we need to handle close separately or should we be called with SetCurrent of null model?
         } else if (arg instanceof ObjectSetCurrentEvent) {
            ObjectSetCurrentEvent evt = (ObjectSetCurrentEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            // If any of the event objects is a model not equal to the current model, this means there is a new
            // current model. So clear out the panel.
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof Model) {
                  if (currentModel == null || !currentModel.equals(objs.get(i))) {
                     currentModel = (Model)objs.get(i);
                     currentAct = null;
                     backupAllActuators();
                     setAllPendingChanges(false);
                     setupComponent(null);
                     break;
                  }
               }
            }
         } else if (arg instanceof ObjectsChangedEvent) {
            ObjectsChangedEvent evt = (ObjectsChangedEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            // If any of the event objects is a coordinate, update the muscle path.
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof AbstractCoordinate) {
                  if (currentAct != null) {
                     AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
                     if (asm != null)
                        updateCurrentPathPanel(asm);
                  }
                  break;
               }
            }
         } else if (arg instanceof NameChangedEvent) {
            NameChangedEvent ev = (NameChangedEvent)arg;
            if (ev.getObject() instanceof Model) {
               if (currentModel != null && currentModel.equals(ev.getObject())) {
                  ModelNameLabel.setText("Model: " + currentModel.getName());
               }
            } else if (ev.getObject() instanceof AbstractActuator) {
               AbstractActuator act = (AbstractActuator)ev.getObject();
               if (currentModel != null && currentModel.equals(act.getModel()))
                  updateActuatorName(act);
            }
         }
      }
   }
   
   private void updateAttachmentSelections(SelectedObject selectedObject, boolean state) {
      if (currentAct != null) {
         OpenSimObject obj = selectedObject.getOpenSimObject();
         AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
         if (asm != null) {
            MusclePointSet musclePoints = asm.getAttachmentSet();
            for (int i = 0; i < musclePoints.getSize(); i++) {
               if (OpenSimObject.getCPtr(obj) == MusclePoint.getCPtr(musclePoints.get(i))) {
                  attachmentSelectBox[i].setSelected(state);
                  this.repaint();
                  break;
               }
            }
         }
      }
   }
   
   private void dragMusclePoints(DragObjectsEvent ev) {
      ArrayList<SelectedObject> selectedObjects = ViewDB.getInstance().getSelectedObjects();
      AbstractMuscle m = null;
      AbstractMuscle currentMuscle = AbstractMuscle.safeDownCast(currentAct);
      boolean currentMuscleMoved = false;
      for (int i = 0; i < selectedObjects.size(); i++) {
         OpenSimObject obj = selectedObjects.get(i).getOpenSimObject();
         MusclePoint mp = MusclePoint.safeDownCast(obj);
         if (mp != null) {
            AbstractDynamicsEngine engine = mp.getMuscle().getModel().getDynamicsEngine();
            AbstractBody body = mp.getBody();
            AbstractBody ground = engine.getGroundBody();
            double dragVectorBody[] = new double[3];
            engine.transform(ground, ev.getDragVector(), body, dragVectorBody);
            //System.out.println("drag: " + ev.getDragVector()[0] + " " + ev.getDragVector()[1] + " " + ev.getDragVector()[2]);
            mp.setAttachment(0, mp.getAttachmentCoord(0) + dragVectorBody[0]);
            mp.setAttachment(1, mp.getAttachmentCoord(1) + dragVectorBody[1]);
            mp.setAttachment(2, mp.getAttachmentCoord(2) + dragVectorBody[2]);
            m = mp.getMuscle();
            if (m != null)
               setPendingChanges(true, (AbstractActuator)m, false);
            // Check to see if the muscle editor's current muscle was moved, so you can update the window later.
            if (m != null && AbstractMuscle.getCPtr(m) == AbstractMuscle.getCPtr(currentMuscle)) {
               currentMuscleMoved = true;
            }
            // Update the geometry of the muscle.
            SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(m.getModel());
            vis.updateActuatorGeometry(m, true);
         }
      }
      // If m is not null, then at least one selected object is a muscle point
      // (that was just dragged). So redraw the model.
      if (m != null) {
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
         guiElem.setUnsavedChangesFlag(true);
         // If the current muscle moved, update the necessary panels.
         if (currentMuscleMoved) {
            updateAttachmentPanel(currentMuscle);
            updateCurrentPathPanel(currentMuscle);
         }
         updateBackupRestoreButtons();
         ViewDB.getInstance().renderAll();
      }
   }

   /* This function is called by the MusclePointFunctionEventListener when a moving muscle
    * point's X, Y, or Z function has been changed.
    */
   public void movingPointMoved(Model model, AbstractMuscle muscle, MovingMusclePoint point) {
      setPendingChanges(true, muscle, true);
      // tell the ViewDB to redraw the model
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(muscle, true);
      ViewDB.getInstance().repaintAll();
      // update the current path panel
      updateCurrentPathPanel(muscle);
   }

   /* This function is called by the MusclePropertyFunctionEventListener when a muscle
    * property that's a function has been changed.
    */
   public void propertyFunctionChanged(Model model, AbstractActuator act) {
      setPendingChanges(true, act, true);
   }

   final static class ResolvableHelper implements Serializable {
      private static final long serialVersionUID = 1L;
      public Object readResolve() {
         return MuscleEditorTopComponent.getDefault();
      }
   }
   
}
