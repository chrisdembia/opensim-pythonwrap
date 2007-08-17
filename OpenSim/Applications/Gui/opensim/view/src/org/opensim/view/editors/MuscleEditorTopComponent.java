package org.opensim.view.editors;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.io.Serializable;
import java.text.DecimalFormat;
import java.util.Observable;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Observer;
import java.util.Vector;
import org.openide.ErrorManager;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.openide.windows.Mode;
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
import org.opensim.modeling.MusclePoint;
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

/**
 * Top component which displays the Muscle Editor window.
 */
final public class MuscleEditorTopComponent extends TopComponent implements Observer {
   
   private static MuscleEditorTopComponent instance;
   private Model currentModel = null;
   private AbstractActuator currentAct = null; // the actuator that is currently shown in the Muscle Editor window
   private AbstractActuator savedAct = null; // the state that gets restored when "reset" is pressed
   private boolean pendingChanges = false;
   private static final String[] wrapMethodNames = {"hybrid", "midpoint", "axial"};
   private javax.swing.JScrollPane AttachmentsTab = null;
   private javax.swing.JScrollPane WrapTab = null;
   private javax.swing.JScrollPane CurrentPathTab = null;
   private String selectedTabName = null;
   private javax.swing.JCheckBox attachmentSelectBox[] = null; // array of checkboxes for selecting attachment points
   private String[] wrapObjectNames = null;

   private NumberFormat doublePropFormat = new DecimalFormat("0.000000");
   private NumberFormat positionFormat = new DecimalFormat("0.00000");
   private NumberFormat angleFormat = new DecimalFormat("0.00");
   
   /** path to the icon used by the component and its open action */
//    static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
   
   private static final String PREFERRED_ID = "MuscleEditorTopComponent";
   private static String s_mode="leftSlidingSide";
   
   private MuscleEditorTopComponent() {
      initComponents();
      setName(NbBundle.getMessage(MuscleEditorTopComponent.class, "CTL_MuscleEditorTopComponent"));
      setToolTipText(NbBundle.getMessage(MuscleEditorTopComponent.class, "HINT_MuscleEditorTopComponent"));
//        setIcon(Utilities.loadImage(ICON_PATH, true));
      ViewDB.getInstance().addObserver(this);
      OpenSimDB.getInstance().addObserver(this);
      //Runtime.getRuntime().addShutdownHook(new ShutDownThread());
   }
   
   private void setPendingChanges(boolean state, boolean repaint) {
      pendingChanges = state;
      if (ResetButton.isEnabled() != state) {
         ResetButton.setEnabled(state);
         if (repaint == true)
            ViewDB.getInstance().repaintAll();
      }
      // Mark the model as dirty as well.
      if (state == true && currentModel != null) {
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
         guiElem.setUnsavedChangesFlag(true);
      }
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
      ApplyButton = new javax.swing.JButton();
      ResetButton = new javax.swing.JButton();
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
      org.openide.awt.Mnemonics.setLocalizedText(ApplyButton, "Set");
      ApplyButton.setToolTipText("Make a backup copy of this actuator. Click \"Reset\" to return to these values.");
      ApplyButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            ApplyButtonActionPerformed(evt);
         }
      });

      ApplyButton.getAccessibleContext().setAccessibleDescription("save all changes to this muscle");

      org.openide.awt.Mnemonics.setLocalizedText(ResetButton, "Reset");
      ResetButton.setToolTipText("Reset this actuator to the backup copy made when \"Set\" was pressed.");
      ResetButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            ResetButtonActionPerformed(evt);
         }
      });

      ResetButton.getAccessibleContext().setAccessibleDescription("reset this muscle to its previously saved version");

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
            .add(118, 118, 118)
            .add(ResetButton)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 201, Short.MAX_VALUE)
            .add(ApplyButton)
            .add(159, 159, 159))
         .add(MuscleEditorPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(ParametersTabbedPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 570, Short.MAX_VALUE)
               .add(ModelNameLabel)
               .add(MuscleEditorPanelLayout.createSequentialGroup()
                  .add(MuscleSelectLabel)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(MuscleComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 128, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(34, 34, 34)
                  .add(MuscleNameLabel)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(MuscleNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 125, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(23, 23, 23)
                  .add(MuscleTypeLabel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 178, Short.MAX_VALUE)))
            .addContainerGap())
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
               .add(MuscleNameTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(MuscleNameLabel)
               .add(MuscleTypeLabel))
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(ParametersTabbedPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 246, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(MuscleEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(ResetButton)
               .add(ApplyButton))
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

   private void MuscleComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MuscleComboBoxActionPerformed
      if (currentModel == null)
         return;
      String nameOfNewAct = MuscleComboBox.getSelectedItem().toString();
      AbstractActuator newAct = currentModel.getActuatorSet().get(nameOfNewAct);
      if (newAct != null && AbstractActuator.getCPtr(newAct) != AbstractActuator.getCPtr(currentAct)) {
         currentAct = newAct;
         savedAct = AbstractActuator.safeDownCast(currentAct.copy());
         setPendingChanges(false, false);
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
      if (currentAct == null || currentAct.getName().equals(MuscleNameTextField.getText()) == true)
         return;
      if (validName(MuscleNameTextField.getText()) == false)
         return;
      currentAct.setName(MuscleNameTextField.getText());
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
      String [] actNames = guiElem.getActuatorNames(true);
      MuscleComboBox.setModel(new javax.swing.DefaultComboBoxModel(actNames));
      MuscleComboBox.setSelectedIndex(findElement(actNames, currentAct.getName()));
      setPendingChanges(true, false);
      OpenSimDB.getInstance().setChanged();
      NameChangedEvent evnt = new NameChangedEvent(currentAct);
      OpenSimDB.getInstance().notifyObservers(evnt);
   }//GEN-LAST:event_MuscleNameTextFieldFocusLost

   private void MuscleNameTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MuscleNameTextFieldActionPerformed
      if (currentAct == null || currentAct.getName().equals(MuscleNameTextField.getText()) == true)
         return;
      if (validName(MuscleNameTextField.getText()) == false)
         return;
      currentAct.setName(MuscleNameTextField.getText());
      SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
      String [] actNames = guiElem.getActuatorNames(true);
      MuscleComboBox.setModel(new javax.swing.DefaultComboBoxModel(actNames));
      MuscleComboBox.setSelectedIndex(findElement(actNames, currentAct.getName()));
      setPendingChanges(true, false);
      OpenSimDB.getInstance().setChanged();
      NameChangedEvent evnt = new NameChangedEvent(currentAct);
      OpenSimDB.getInstance().notifyObservers(evnt);
   }//GEN-LAST:event_MuscleNameTextFieldActionPerformed
   
   private void ResetButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ResetButtonActionPerformed
      resetActuator();
   }//GEN-LAST:event_ResetButtonActionPerformed
   
   private void ApplyButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ApplyButtonActionPerformed
      saveActuator();
   }//GEN-LAST:event_ApplyButtonActionPerformed
   
   private void saveActuator() {
      //act.setName(MuscleNameTextField.getText());
      setPendingChanges(false, false);
      //OpenSimDB.getInstance().setChanged();
      //NameChangedEvent evnt = new NameChangedEvent(act);
      //OpenSimDB.getInstance().notifyObservers(evnt);
      savedAct = AbstractActuator.safeDownCast(currentAct.copy());
      savedAct.setName(currentAct.getName()); // TODO: what about other properties of parent classes?
   }
   
   /** resetActuator
    *  Because the type of the actuator may have changed, you have to remove the current
    *  one (act) and replace it with the saved one (savedAct).
    */
   private void resetActuatorReplace() {
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
      model.getActuatorSet().replaceActuator(currentAct, savedAct);
      currentAct = savedAct; // act now points to the actuator in the model's actuator set.
      savedAct = AbstractActuator.safeDownCast(currentAct.copy()); // Make a new backup copy of the actuator.
      // Set the display preference of the new muscle to the same as the old.
      currentAct.getDisplayer().getVisibleProperties().setDisplayPreference(dp);
      vis.addActuatorGeometry(currentAct, true);

      // Once the proper ObjectsReplacedEvent is implemented, this NameChangedEvent
      // should no longer be needed.
      NameChangedEvent ev = new NameChangedEvent(currentAct);
      OpenSimDB.getInstance().setChanged();
      OpenSimDB.getInstance().notifyObservers(ev);

      setPendingChanges(false, false);
      setupComponent(currentAct);
      ViewDB.getInstance().repaintAll();
   }

   /* The version of resetActuator above replaces the actuator in the
    * model's actuator set, because the type may have been changed (so
    * the actuator to reset to is an entirely different object). This
    * causes problems in the GUI because other components like the
    * navigator do not yet handle replace-objects events. Also, with
    * the muscle-type combo box commented out for 1.0, the actuator
    * object cannot change between a set/reset, so the function below
    * was created to do a simple copy-in-place when reset is pressed.
    * This version sends out only a name-changed event because the
    * other GUI components do not yet handle property-change events.
    */
   private void resetActuator() {
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(currentModel);

      // If the name has changed, fire an event.
      if (currentAct.getName().equals(savedAct.getName()) == false) {
         NameChangedEvent ev = new NameChangedEvent(currentAct);
         OpenSimDB.getInstance().setChanged();
         OpenSimDB.getInstance().notifyObservers(ev);
      }

      // Copy the elements of the saved actuator into the current actuator.
      currentAct.copy(savedAct);
      vis.updateActuatorGeometry(currentAct, true);

      setPendingChanges(false, false);
      setupComponent(currentAct);
      ViewDB.getInstance().repaintAll();
   }
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton ApplyButton;
   private javax.swing.JLabel ModelNameLabel;
   private javax.swing.JComboBox MuscleComboBox;
   private javax.swing.JPanel MuscleEditorPanel;
   private javax.swing.JScrollPane MuscleEditorScrollPane;
   private javax.swing.JLabel MuscleNameLabel;
   private javax.swing.JTextField MuscleNameTextField;
   private javax.swing.JLabel MuscleSelectLabel;
   private javax.swing.JLabel MuscleTypeLabel;
   private javax.swing.JTabbedPane ParametersTabbedPanel;
   private javax.swing.JButton ResetButton;
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
      double newValue, oldValue = musclePoints.get(attachmentNum).getAttachment().getitem(coordNum);
      try {
         newValue = Double.parseDouble(field.getText());
      } catch (NumberFormatException ex) {
         newValue = oldValue;
         oldValue = Double.MAX_VALUE; // to force the field to update itself with the old value
      }
      // format the number and write it back into the text field
      field.setText(positionFormat.format(newValue));
      // update the model if the number has changed
      if (oldValue != newValue) {
         musclePoints.get(attachmentNum).setAttachment(coordNum, newValue);
         setPendingChanges(true, false);
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
         setPendingChanges(true, false);
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
         if (needsUpdating) {
            setPendingChanges(true, false);
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
   
   public void RangeMinEntered(javax.swing.JTextField field, int attachmentNum) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(attachmentNum));

      // Conversions between radians and degrees
      double conversion = 1.0;
      NumberFormat nf = null;
      if (via.getCoordinate().getMotionType() == AbstractDof.DofType.Rotational) {
         conversion = 180.0/Math.PI;
         nf = angleFormat;
      } else {
         nf = positionFormat;
      }

      double newValue, oldValue = via.getRange().getitem(0)*conversion;
      double biggestAllowed = via.getRange().getitem(1)*conversion;
      try {
         newValue = Double.parseDouble(field.getText());
      } catch (NumberFormatException ex) {
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
            setPendingChanges(true, false);
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
      double conversion = 1.0;
      NumberFormat nf = null;
      if (via.getCoordinate().getMotionType() == AbstractDof.DofType.Rotational) {
         conversion = 180.0/Math.PI;
         nf = angleFormat;
      } else {
         nf = positionFormat;
      }

      double newValue, oldValue = via.getRange().getitem(1)*conversion;
      double smallestAllowed = via.getRange().getitem(0)*conversion;
      try {
         newValue = Double.parseDouble(field.getText());
      } catch (NumberFormatException ex) {
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
            setPendingChanges(true, false);
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
         setPendingChanges(true, false);
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
         setPendingChanges(true, false);
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
      setPendingChanges(true, false);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void moveUpMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.moveUpMuscleWrap(num);
      setPendingChanges(true, false);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void moveDownMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.moveDownMuscleWrap(num);
      setPendingChanges(true, false);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void deleteMuscleWrap(int num) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      asm.deleteMuscleWrap(num);
      setPendingChanges(true, false);
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
      setPendingChanges(true, false);
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
         currentAct = model.getActuatorSet().changeActuatorType(currentAct, newTypeName);
         // Set the display preference of the new muscle to the same as the old.
         currentAct.getDisplayer().getVisibleProperties().setDisplayPreference(dp);
         setPendingChanges(true, false);
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
            newValue = Double.parseDouble(field.getText());
         } catch (NumberFormatException ex) {
            newValue = oldValue;
            oldValue = Double.MAX_VALUE; // to force the field to update itself with the old value
         }
         // format the number and write it back into the text field
         field.setText(doublePropFormat.format(newValue));

         if (newValue != oldValue) {
            prop.setValue(newValue);
            setPendingChanges(true, false);
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
            newValue = Integer.parseInt(field.getText());
         } catch (NumberFormatException ex) {
            newValue = oldValue;
            oldValue = Integer.MAX_VALUE; // to force the field to update itself with the old value
         }
         // write the value back into the text field (for consistent formatting)
         field.setText(Integer.toString(newValue));

         if (newValue != oldValue) {
            prop.setValue(newValue);
            setPendingChanges(true, false);
            // TODO generate an event for this??
         }
      }
   }
   
   public void addAttachmentPerformed(int menuChoice) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      MusclePointSet musclePoints = asm.getAttachmentSet();
      int index = menuChoice;
      if (index > musclePoints.getSize() - 1)
         index = musclePoints.getSize() - 1;
      MusclePoint closestPoint = musclePoints.get(index);
      asm.addAttachmentPoint(menuChoice, closestPoint.getBody());
      setPendingChanges(true, false);
      setupComponent(currentAct);
      Model model = asm.getModel();
      SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
      vis.updateActuatorGeometry(asm, true);
      ViewDB.getInstance().repaintAll();
   }
   
   public void deleteAttachmentPerformed(int menuChoice) {
      AbstractMuscle asm = AbstractMuscle.safeDownCast(currentAct);
      boolean result = asm.deleteAttachmentPoint(menuChoice);
      if (result == false) {
         Object[] options = {"OK"};
         int answer = JOptionPane.showOptionDialog(this,
                 "A muscle must contain at least 2 fixed attachment points.",
                 "Muscle Editor",
                 JOptionPane.OK_OPTION,
                 JOptionPane.WARNING_MESSAGE,
                 null,
                 options,
                 options[0]);
      } else {
         setPendingChanges(true, false);
         setupComponent(currentAct);
         Model model = asm.getModel();
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
      currentPathXLabel.setBounds(X + 20, Y - 30, 8, 16);
      javax.swing.JLabel currentPathYLabel = new javax.swing.JLabel();
      currentPathYLabel.setText("Y");
      currentPathYLabel.setBounds(X + 80, Y - 30, 8, 16);
      javax.swing.JLabel currentPathZLabel = new javax.swing.JLabel();
      currentPathZLabel.setText("Z");
      currentPathZLabel.setBounds(X + 140, Y - 30, 8, 16);
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
         boolean isWrapPoint = false;
         if (asmp.get(i).getWrapObject() != null)
            isWrapPoint = true;
         javax.swing.JLabel indexLabel = new javax.swing.JLabel();
         javax.swing.JLabel xField = new javax.swing.JLabel();
         xField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel yField = new javax.swing.JLabel();
         yField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel zField = new javax.swing.JLabel();
         zField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JLabel bodyLabel = new javax.swing.JLabel();
         javax.swing.JLabel typeLabel = new javax.swing.JLabel();
         indexLabel.setText(String.valueOf(i+1) + ".");
         xField.setText(positionFormat.format(asmp.get(i).getAttachment().getitem(0)));
         yField.setText(positionFormat.format(asmp.get(i).getAttachment().getitem(1)));
         zField.setText(positionFormat.format(asmp.get(i).getAttachment().getitem(2)));
         bodyLabel.setText(asmp.get(i).getBodyName());
         if (isWrapPoint)
            typeLabel.setText("wrap" + " (" + asmp.get(i).getWrapObject().getName() + ")");
         else {
            if (MuscleViaPoint.safeDownCast(asmp.get(i)) == null)
               typeLabel.setText("fixed");
            else
               typeLabel.setText("via");
         }
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
      wrapObjectLabel.setBounds(X + 40, 10, 50, 16);
      WrapPanel.add(wrapObjectLabel);
      javax.swing.JLabel wrapMethodLabel = new javax.swing.JLabel();
      wrapMethodLabel.setText("Method");
      wrapMethodLabel.setBounds(X + 140, 10, 50, 16);
      WrapPanel.add(wrapMethodLabel);
      javax.swing.JLabel wrapStartLabel = new javax.swing.JLabel();
      wrapStartLabel.setText("Start Pt");
      wrapStartLabel.setBounds(X + 225, 10, 80, 16);
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
         indexLabel.setText(String.valueOf(i+1) + ". " + awo.getName());
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
      indexLabel.setText(String.valueOf(smw.getSize()+1) + ". existing wrap object");
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
      int i, aCount = 0;
      int X = 30;
      int Y = 40;
      
      // Set up the muscle-independent labels
      boolean anyViaPoints = false;
      javax.swing.JLabel attachmentXLabel = new javax.swing.JLabel();
      attachmentXLabel.setText("X");
      attachmentXLabel.setBounds(X + 20, Y - 30, 8, 16);
      javax.swing.JLabel attachmentYLabel = new javax.swing.JLabel();
      attachmentYLabel.setText("Y");
      attachmentYLabel.setBounds(X + 80, Y - 30, 8, 16);
      javax.swing.JLabel attachmentZLabel = new javax.swing.JLabel();
      attachmentZLabel.setText("Z");
      attachmentZLabel.setBounds(X + 140, Y - 30, 8, 16);
      javax.swing.JLabel attachmentBodyLabel = new javax.swing.JLabel();
      attachmentBodyLabel.setText("Body");
      attachmentBodyLabel.setBounds(X + 210, Y - 30, 30, 16);
      javax.swing.JLabel attachmentSelLabel = new javax.swing.JLabel();
      attachmentSelLabel.setText("Sel");
      attachmentSelLabel.setBounds(X + 290, Y - 30, 25, 16);
      javax.swing.JLabel coordLabel = new javax.swing.JLabel();
      coordLabel.setText("Coordinate");
      coordLabel.setBounds(X + 350, Y - 30, 90, 16);
      javax.swing.JLabel rangeMinLabel = new javax.swing.JLabel();
      rangeMinLabel.setText("Min");
      rangeMinLabel.setBounds(X + 480, Y - 30, 60, 16);
      javax.swing.JLabel rangeMaxLabel = new javax.swing.JLabel();
      rangeMaxLabel.setText("Max");
      rangeMaxLabel.setBounds(X + 542, Y - 30, 60, 16);
      AttachmentsPanel.add(attachmentXLabel);
      AttachmentsPanel.add(attachmentYLabel);
      AttachmentsPanel.add(attachmentZLabel);
      AttachmentsPanel.add(attachmentBodyLabel);
      AttachmentsPanel.add(attachmentSelLabel);
      
      attachmentSelectBox = new javax.swing.JCheckBox[musclePoints.getSize()];
      
      for (i = 0; i < musclePoints.getSize(); i++) {
         MuscleViaPoint via = MuscleViaPoint.safeDownCast(musclePoints.get(i));
         javax.swing.JLabel indexLabel = null;
         indexLabel = new javax.swing.JLabel();
         indexLabel.setText(String.valueOf(aCount+1) + ".");
         
         javax.swing.JTextField xField = new javax.swing.JTextField();
         xField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JTextField yField = new javax.swing.JTextField();
         yField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JTextField zField = new javax.swing.JTextField();
         zField.setHorizontalAlignment(SwingConstants.TRAILING);
         javax.swing.JComboBox comboBox = new javax.swing.JComboBox();
         attachmentSelectBox[i] = new javax.swing.JCheckBox();
         javax.swing.JComboBox coordComboBox = null;
         javax.swing.JTextField rangeMinField = null;
         javax.swing.JTextField rangeMaxField = null;
         if (via != null) {
            anyViaPoints = true;
            coordComboBox = new javax.swing.JComboBox();
            rangeMinField = new javax.swing.JTextField();
            rangeMaxField = new javax.swing.JTextField();
         }
         
         int height = Y + i * 22;
         int width = 60;
         
         final int num = i;
         
         SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(asm.getModel());
         String[] bodyNames = guiElem.getBodyNames();
         comboBox.setModel(new javax.swing.DefaultComboBoxModel(bodyNames));
         comboBox.setSelectedIndex(findElement(bodyNames, musclePoints.get(i).getBodyName()));
         if (via != null) {
            String[] coordinateNames = guiElem.getCoordinateNames();
            coordComboBox.setModel(new javax.swing.DefaultComboBoxModel(coordinateNames));
            coordComboBox.setSelectedIndex(findElement(coordinateNames, via.getCoordinateName()));
            double conversion = 1.0;
            NumberFormat nf =  null;
            if (via.getCoordinate().getMotionType() == AbstractDof.DofType.Rotational) {
               conversion = 180.0/Math.PI;
               nf = angleFormat;
            } else {
               nf = positionFormat;
            }
            rangeMinField.setText(nf.format(via.getRange().getitem(0)*conversion));
            rangeMaxField.setText(nf.format(via.getRange().getitem(1)*conversion));
            coordComboBox.setBounds(X + 3*width + 140, height, 130, 21);
            rangeMinField.setBounds(X + 3*width + 280, height, 60, 21);
            rangeMaxField.setBounds(X + 3*width + 345, height, 60, 21);
            coordComboBox.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  ViaCoordinateChosen(((javax.swing.JComboBox)evt.getSource()), num);
               }
            });
            rangeMinField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  RangeMinEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            rangeMinField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  RangeMinEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            rangeMaxField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  RangeMaxEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
            rangeMaxField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  RangeMaxEntered(((javax.swing.JTextField)evt.getSource()), num);
               }
            });
         }
         
         indexLabel.setBounds(X - 20, height, 20, 21);
         xField.setBounds(X, height, width, 21);
         yField.setBounds(X + width + 1, height, width, 21);
         zField.setBounds(X + 2*width + 2, height, width, 21);
         comboBox.setBounds(X + 3*width + 10, height, 90, 21);
         attachmentSelectBox[i].setBounds(X + 3*width + 110, height, 21, 21);
         xField.setText(positionFormat.format(musclePoints.get(i).getAttachment().getitem(0)));
         xField.setToolTipText("X coordinate of the attachment point");
         yField.setText(positionFormat.format(musclePoints.get(i).getAttachment().getitem(1)));
         yField.setToolTipText("Y coordinate of the attachment point");
         zField.setText(positionFormat.format(musclePoints.get(i).getAttachment().getitem(2)));
         zField.setToolTipText("Z coordinate of the attachment point");
         comboBox.setToolTipText("Body the attachment point is fixed to");
         attachmentSelectBox[i].setToolTipText("Click to select/unselect this attachment point");
         AttachmentsPanel.add(indexLabel);
         aCount++;
         
         xField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 0);
            }
         });
         xField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 0);
            }
         });
         yField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 1);
            }
         });
         yField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 1);
            }
         });
         zField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 2);
            }
         });
         zField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
               AttachmentPointEntered(((javax.swing.JTextField)evt.getSource()), num, 2);
            }
         });
         comboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentBodyChosen(((javax.swing.JComboBox)evt.getSource()), num);
            }
         });
         attachmentSelectBox[i].addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
               AttachmentSelected(((javax.swing.JCheckBox)evt.getSource()), num);
            }
         });
         AttachmentsPanel.add(xField);
         AttachmentsPanel.add(yField);
         AttachmentsPanel.add(zField);
         AttachmentsPanel.add(comboBox);
         AttachmentsPanel.add(attachmentSelectBox[i]);
         if (via != null) {
            AttachmentsPanel.add(coordComboBox);
            AttachmentsPanel.add(rangeMinField);
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
      for (i = 0; i < musclePoints.getSize() - 1; i++) {
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
      addButton.setBounds(X + 100, Y + 20 + musclePoints.getSize() * 22, 70, 21);
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
      for (i = 0; i < musclePoints.getSize(); i++) {
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
      deleteButton.setBounds(X + 200, Y + 20 + musclePoints.getSize() * 22, 70, 21);
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
      
      Dimension d = new Dimension(350, Y + 45 + musclePoints.getSize() * 22);
      if (anyViaPoints) {
         d.width = 630;
         AttachmentsPanel.add(coordLabel);
         AttachmentsPanel.add(rangeMinLabel);
         AttachmentsPanel.add(rangeMaxLabel);
      }
      AttachmentsPanel.setPreferredSize(d);
      
      // Update the checked/unchecked state of the selected checkboxes
      ArrayList<SelectedObject> selectedObjects = ViewDB.getInstance().getSelectedObjects();
      for (i = 0; i < selectedObjects.size(); i++)
         updateAttachmentSelections(selectedObjects.get(i), true);
   }
   
   public void setupComponent(AbstractActuator newAct) {
      // Remove all previous GUI components and their panels.
      // If the type of actuator changed since the last time
      // the panels were set up, there could be different
      // numbers and types of components and panels.
      // But before they are removed, store the name of the
      // currently selected tab (if any) so that you can try
      // to restore this selection (e.g., after the "reset"
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
         ApplyButton.setEnabled(false);
         ResetButton.setEnabled(false);
         return;
      }
      
      if (currentAct == null) {
         MuscleTypeLabel.setText("");
         MuscleNameTextField.setText("");
         MuscleNameTextField.setEnabled(false);
         //MuscleTypeComboBox.setEnabled(false);
         ApplyButton.setEnabled(false);
         ResetButton.setEnabled(false);
         return;
      } else {
         MuscleTypeLabel.setText("Type: " + currentAct.getType());
         MuscleNameTextField.setEnabled(true);
         //MuscleTypeComboBox.setEnabled(true);
         ApplyButton.setEnabled(true);
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
               final int num = i;
               if (p.getType() == org.opensim.modeling.Property.PropertyType.Dbl) {
                  propField.addActionListener(new java.awt.event.ActionListener() {
                     public void actionPerformed(java.awt.event.ActionEvent evt) {
                        DoublePropertyEntered(((javax.swing.JTextField)evt.getSource()), num);
                     }
                  });
                  propField.addFocusListener(new java.awt.event.FocusAdapter() {
                     public void focusLost(java.awt.event.FocusEvent evt) {
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
                  propButton.setBounds(230, 20 + tabPropertyCount[groupNum] * 22, 160, 21);
                  propButton.setText("Edit: coming soon.");
                  propButton.setEnabled(false);
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
      
      // Gray out the reset button if there are no pending changes
      ResetButton.setEnabled(pendingChanges);
      
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
      Dimension d = new Dimension(495, 358);
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
      Mode mode=WindowManager.getDefault().findMode(s_mode);
      //boolean docked = mode.dockInto(this);
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
               savedAct = AbstractActuator.safeDownCast(currentAct.copy());
               AttachmentsTab = null;
               WrapTab = null;
               CurrentPathTab = null;
               selectedTabName = null;
               setPendingChanges(false, false);
               setupComponent(currentAct);
            }
         }
      } else {
         setPendingChanges(false, false);
         setupComponent(null);
      }
      super.open();
      this.requestActive();
   }
/* Old version which prompted to save/reset any changes to current muscle
   public void open() {
      Mode mode=WindowManager.getDefault().findMode(s_mode);
      //boolean docked = mode.dockInto(this);
      AbstractActuator newAct = null;
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if (selected.length > 0) {
         OneActuatorNode muscleNode = (OneActuatorNode) selected[0];
         newAct = AbstractActuator.safeDownCast(muscleNode.getOpenSimObject());
         if (newAct != null && newAct != act) {
            boolean switchMuscles = false;
            if (pendingChanges == false) {
               switchMuscles = true;
            } else {
               Object[] options = {"Yes", "No", "Cancel"};
               int answer = JOptionPane.showOptionDialog(this,
                  "Do you want to save the changes you made to " + act.getName() + "?",
                  "Muscle Editor",
                  JOptionPane.YES_NO_CANCEL_OPTION,
                  JOptionPane.WARNING_MESSAGE,
                  null,
                  options,
                  options[2]);
               if (answer == 0) {
                  saveActuator();
                  switchMuscles = true;
               } else if (answer == 1) {
                  resetActuator();
                  switchMuscles = true;
               } else if (answer == 2) {
                  switchMuscles = false;
               }
            }
            if (switchMuscles == true) {
               act = newAct;
               savedAct = AbstractActuator.safeDownCast(act.copy());
               AttachmentsTab = null;
               WrapTab = null;
               CurrentPathTab = null;
               selectedTabName = null;
               setupComponent(act);
            }
         }
      } else {
         setupComponent(null);
      }
      super.open();
      this.requestActive();
   }
 */

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
            // If any of the event objects is a model, this means there is a new
            // current model, so we need to handle the event.
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof Model) {
                  return true;
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
               setPendingChanges(false, false);
               setupComponent(null);
            }
            // Do we need to handle close separately or should we be called with SetCurrent of null model?
         } else if (arg instanceof ObjectSetCurrentEvent) {
            ObjectSetCurrentEvent evt = (ObjectSetCurrentEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            // If any of the event objects is a model, this means there is a new
            // current model. So update the panel.
            // Kluge: Handle model name change separately!
            if ((objs.size()==1) && (objs.get(0) instanceof Model)){
               if (currentModel != null && currentModel.equals(objs.get(0))){
                  // Safe change just a name change probably. Don't do anything 
                  ModelNameLabel.setText("Model: " + currentModel.getName());
                  return;
               }
            }
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof Model) {
                  currentModel = (Model)objs.get(i);
                  setPendingChanges(false, false);
                  setupComponent(null);
                  break;
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
            mp.setAttachment(0, mp.getAttachment().getitem(0) + dragVectorBody[0]);
            mp.setAttachment(1, mp.getAttachment().getitem(1) + dragVectorBody[1]);
            mp.setAttachment(2, mp.getAttachment().getitem(2) + dragVectorBody[2]);
            m = mp.getMuscle();
            // Check to see if the muscle editor's current muscle was moved.
            if (AbstractMuscle.getCPtr(m) == AbstractMuscle.getCPtr(currentMuscle))
               currentMuscleMoved = true;
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
            setPendingChanges(true, false);
         }
         ViewDB.getInstance().repaintAll();
      }
   }
   
   final static class ResolvableHelper implements Serializable {
      private static final long serialVersionUID = 1L;
      public Object readResolve() {
         return MuscleEditorTopComponent.getDefault();
      }
   }
   
}
