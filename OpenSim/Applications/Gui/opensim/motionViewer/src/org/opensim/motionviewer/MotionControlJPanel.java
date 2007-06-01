/*
 * MotionControlJPanel.java
 *
 * Created on January 12, 2007, 11:28 AM
 */

package org.opensim.motionviewer;

import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.opensim.modeling.Storage;
import org.opensim.motionviewer.MotionEvent.Operation;

/**
 *
 * @author  Ayman
 * The panel for motion playback in main toolbar.
 * The panel will observer MotionsDB so that it can respond to changes in current model, events ...
 */
public class MotionControlJPanel extends javax.swing.JPanel 
        implements ChangeListener,  // For motion slider
                   Observer {       // For MotionsDB
   
   Timer               animationTimer=null;
   long                animationSpeed=100L;
   SpinnerModel        smodel = new SpinnerNumberModel(100, 10, 500, 10);
   boolean     motionLoaded=false;
   MasterMotionModel   masterMotion;
   
   /**
    * Creates new form MotionControlJPanel
    */
   public MotionControlJPanel() {
      masterMotion = new MasterMotionModel();   // initialize the object backing the GUI.
      initComponents();
      jMotionSlider.setModel(masterMotion);
      jMotionSlider.getModel().addChangeListener(this);  // Listen to changes in model due to other actions
      jMotionSlider.addChangeListener(this);             // listen to changes in the slider itself.
      MotionsDB.getInstance().addObserver(this);
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jReverseButton = new javax.swing.JButton();
      jStopButton = new javax.swing.JButton();
      jPlayButton = new javax.swing.JButton();
      jMotionSlider = new javax.swing.JSlider();
      jLabel2 = new javax.swing.JLabel();
      jTimeTextField = new javax.swing.JTextField();
      jSpeedSpinner = new javax.swing.JSpinner();
      jLabel1 = new javax.swing.JLabel();
      jButton1 = new javax.swing.JButton();
      jButton2 = new javax.swing.JButton();
      jMotionNameLabel = new javax.swing.JLabel();
      jLabel4 = new javax.swing.JLabel();
      jWrapToggleButton = new javax.swing.JToggleButton();

      setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
      jReverseButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse.gif")));
      jReverseButton.setPreferredSize(new java.awt.Dimension(50, 25));
      jReverseButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jPlayReverseButtonActionPerformed(evt);
         }
      });

      jStopButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/stop.gif")));
      jStopButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jStopButtonActionPerformed(evt);
         }
      });

      jPlayButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play.gif")));
      jPlayButton.setMaximumSize(new java.awt.Dimension(25, 25));
      jPlayButton.setMinimumSize(new java.awt.Dimension(25, 25));
      jPlayButton.setPreferredSize(new java.awt.Dimension(25, 25));
      jPlayButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jPlayButtonActionPerformed(evt);
         }
      });

      jMotionSlider.setMajorTickSpacing(50);
      jMotionSlider.setMinorTickSpacing(5);
      jMotionSlider.setPaintLabels(true);
      jMotionSlider.setPaintTicks(true);
      jMotionSlider.setPaintTrack(false);
      jMotionSlider.setExtent(100);

      jLabel2.setFont(new java.awt.Font("Tahoma", 1, 11));
      jLabel2.setText("Motion:");

      jTimeTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jTimeTextFieldActionPerformed(evt);
         }
      });
      jTimeTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
         public void propertyChange(java.beans.PropertyChangeEvent evt) {
            jTimeTextFieldPropertyChange(evt);
         }
      });
      jTimeTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            jTimeTextFieldFocusLost(evt);
         }
      });

      jSpeedSpinner.setModel(smodel);
      jSpeedSpinner.setToolTipText("animation speed ");

      jLabel1.setFont(new java.awt.Font("Tahoma", 1, 11));
      jLabel1.setText("rate:");

      jButton1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step.gif")));
      jButton1.setMaximumSize(new java.awt.Dimension(50, 25));
      jButton1.setMinimumSize(new java.awt.Dimension(50, 25));
      jButton1.setPreferredSize(new java.awt.Dimension(50, 25));
      jButton1.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jAdvanceButtonActionPerformed(evt);
         }
      });

      jButton2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep.gif")));
      jButton2.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jBackButtonActionPerformed(evt);
         }
      });

      jLabel4.setFont(new java.awt.Font("Tahoma", 1, 11));
      jLabel4.setText("time");

      jWrapToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap.gif")));
      jWrapToggleButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jWrapToggleButtonActionPerformed(evt);
         }
      });

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel2)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jMotionNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 104, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel4)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 52, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jMotionSlider, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 202, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jPlayButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jStopButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jReverseButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jButton2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jButton1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jWrapToggleButton)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jLabel1)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 37, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap()
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false)
               .add(jMotionSlider, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 36, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(jPlayButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jStopButton)
                     .add(jReverseButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jButton2)
                     .add(jButton1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                     .add(jWrapToggleButton)
                     .add(jLabel1)
                     .add(jSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                  .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                     .add(jLabel2)
                     .add(jLabel4)
                     .add(jMotionNameLabel)
                     .add(jTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))))
            .addContainerGap())
      );
   }// </editor-fold>//GEN-END:initComponents

   private void jTimeTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_jTimeTextFieldPropertyChange
   // Listen to "value" changes
      handleUserTimeChange();
// TODO add your handling code here:
   }//GEN-LAST:event_jTimeTextFieldPropertyChange
   
   private void jTimeTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jTimeTextFieldFocusLost
// TODO add your handling code here:
      handleUserTimeChange();
   }//GEN-LAST:event_jTimeTextFieldFocusLost
   
   private void jTimeTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTimeTextFieldActionPerformed
      handleUserTimeChange();
// TODO add your handling code here:
   }//GEN-LAST:event_jTimeTextFieldActionPerformed
   
   private void jBackButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBackButtonActionPerformed
      if (isMotionLoaded()){
         masterMotion.back();
          jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
      }
   }//GEN-LAST:event_jBackButtonActionPerformed
   
   private void jPlayReverseButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlayReverseButtonActionPerformed
      if (animationTimer!=null){
         animationTimer.cancel();
         animationTimer=null;
      }
      if (isMotionLoaded() && animationTimer==null){
         animationTimer = new Timer();
         final Timer fTimer = animationTimer;
         animationTimer.scheduleAtFixedRate(new TimerTask() {
            public void run() {
               masterMotion.back();
               jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
              // Kill self if done and wrapMotion is off
                if (masterMotion.finished(-1)){
                   fTimer.cancel();
                   animationTimer=null;
                }
            }
         }, ((Integer)smodel.getValue()).longValue(), ((Integer)smodel.getValue()).longValue());
      }
      
   }//GEN-LAST:event_jPlayReverseButtonActionPerformed
   
    private void jStopButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jStopButtonActionPerformed
       if (isMotionLoaded() && animationTimer != null){
          animationTimer.cancel();
          animationTimer = null;
       }
    }//GEN-LAST:event_jStopButtonActionPerformed
    
    private void jWrapToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jWrapToggleButtonActionPerformed
       
       masterMotion.setWrapMotion(!masterMotion.isWrapMotion());
    }//GEN-LAST:event_jWrapToggleButtonActionPerformed
    
    private void jAdvanceButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAdvanceButtonActionPerformed
       if (isMotionLoaded()){
          masterMotion.advance();
          jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
        }
    }//GEN-LAST:event_jAdvanceButtonActionPerformed
    
    private void jPlayButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlayButtonActionPerformed
      if (animationTimer!=null){
         animationTimer.cancel();
         animationTimer=null;
      }
       if (isMotionLoaded() && animationTimer==null){
          animationTimer = new Timer();
          final Timer fTimer = animationTimer;
          if (masterMotion.finished(1)){
              // reset motion if at end already
              masterMotion.setFrameNumber(0);
          }
          animationTimer.scheduleAtFixedRate(new TimerTask() {
             public void run() {
                masterMotion.advance();
                jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
                // Kill self if done and wrapMotion is off
                if (masterMotion.finished(1)){
                   fTimer.cancel();
                   animationTimer=null;
                }
             }
          }, ((Integer)smodel.getValue()).longValue(), ((Integer)smodel.getValue()).longValue());
       }
    }//GEN-LAST:event_jPlayButtonActionPerformed
    
    
    public void stateChanged(ChangeEvent e) {
       // Get frame number from slider (if not adjusting) and set model to it
       if (isMotionLoaded()){
          if (e.getSource().equals(jMotionSlider.getModel())){ // move slider as a side effect of changes in model
            //javax.swing.JSlider slider= (javax.swing.JSlider)e.getSource();
            if (jMotionSlider.getModel().getValueIsAdjusting())
                return;
             int gValue = jMotionSlider.getModel().getValue();
             jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
             jMotionSlider.setValue(gValue);
          }
          else if (e.getSource().equals(jMotionSlider)){ // move slider
            //javax.swing.JSlider slider= (javax.swing.JSlider)e.getSource();
            /*if (jMotionSlider.getValueIsAdjusting())
                return;*/
             int gValue = jMotionSlider.getValue();
             masterMotion.setFrameNumber(gValue);
             jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
          }
          
       }
    }
    
    public boolean isMotionLoaded() {
       return motionLoaded;
    }
    
    private void handleUserTimeChange() {
       if (isMotionLoaded()){
          //get frame corresponding to enetered time
          double userTime = 0.0;
          try {
             userTime = Double.valueOf(jTimeTextField.getText());
          }catch (NumberFormatException e){
             userTime = 0.0;
          }
          masterMotion.setTime(userTime);
          jTimeTextField.setText(String.valueOf(masterMotion.getCurrentTime()));
       }
    }

   /**
    * update the panel to reflect current motion's name, range, ...etc.
    */
   private void updatePanelDisplay() {
      if (masterMotion==null || masterMotion.getNumMotions()==0){
         jMotionNameLabel.setText("");
         jTimeTextField.setText("");
         Hashtable labels = jMotionSlider.createStandardLabels(25);
         jMotionSlider.setLabelTable(labels);        
      }
      else {
         if (masterMotion.getNumMotions()>=1){
            jMotionNameLabel.setText(masterMotion.getDisplayName());
            jTimeTextField.setText(String.valueOf(masterMotion.getStartTime()));
             Hashtable labels = masterMotion.makeLabels();
            jMotionSlider.setLabelTable(labels);
         }
      }
   }
   
   // Observable is MotionsDB
   public void update(Observable o, Object arg) {
      // Recover motion info, update toolbar accordingly
      if (o instanceof MotionsDB){
         MotionsDB mdb = (MotionsDB)o;
         if (!(arg instanceof MotionEvent)) // time should be ignored here
             return;
         MotionEvent evt = (MotionEvent)arg;
         if (evt.getOperation() == Operation.Open || evt.getOperation() == Operation.SetCurrent){
            // new motion is loaded or is set current. Update panel display
            motionLoaded = true;   // enable buttons as needed
            masterMotion.add(evt.getModel(), evt.getMotion());
            updatePanelDisplay();
         }
         else if (evt.getOperation() == Operation.Clear){
            motionLoaded = false;
            masterMotion.clear();
            updatePanelDisplay();
         }
         else if (evt.getOperation() == Operation.AddSyncMotion)
         {
            motionLoaded = true;
            masterMotion.addMerge(evt.getModel(), evt.getMotion());
            updatePanelDisplay();
         }
      }
   }
   
 
    
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton jButton1;
   private javax.swing.JButton jButton2;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JLabel jLabel2;
   private javax.swing.JLabel jLabel4;
   private javax.swing.JLabel jMotionNameLabel;
   private javax.swing.JSlider jMotionSlider;
   private javax.swing.JButton jPlayButton;
   private javax.swing.JButton jReverseButton;
   private javax.swing.JSpinner jSpeedSpinner;
   private javax.swing.JButton jStopButton;
   private javax.swing.JTextField jTimeTextField;
   private javax.swing.JToggleButton jWrapToggleButton;
   // End of variables declaration//GEN-END:variables

}
