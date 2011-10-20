/*
 * CoordinateSliderWithBox.java
 *
 * Created on May 15, 2007, 10:16 AM
 *
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

package org.opensim.coordinateviewer;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Vector;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JCheckBox;
import javax.swing.JFormattedTextField;
import javax.swing.JSlider;
import javax.swing.KeyStroke;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.text.NumberFormatter;
import org.openide.util.Utilities;
import org.opensim.modeling.Coordinate;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimContext;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ObjectsChangedEvent;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author  Ayman & Jeff
 * The real value of the slider is maintained in the "value" property of the jFormattedTextField
 * everything else is just a view (text, slider).
 */
public class CoordinateSliderWithBox extends javax.swing.JPanel implements ChangeListener,
        PropertyChangeListener{
   
   private double min, max, step;
   private double conversion=1.0;
   int numTicks=0;
   NumberFormat numberFormat;
   NumberFormatter formatter;
   private boolean rotational;
   private Coordinate coord;
   private OpenSimContext openSimContext;
   private Model model;
   private static double ROUNDOFF=1E-5;  // work around for roundoff converting Strings to/from doubles
   private static String LABELS_FORMAT="###.###";          // Number of digits to show after floating point in bounds
   // Should make images static or use reference rather than create a new instance per slider.
   static ImageIcon unclampedIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/unclamped.png"));
   static ImageIcon unclamped_rolloverIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/unclamped_rollover.png"));
   static ImageIcon clamped_rolloverIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/clamped_rollover.png"));
   static ImageIcon clampedIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/clamped.png"));
   static ImageIcon unlockedIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/unlocked.png"));
   static ImageIcon unlocked_rolloverIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/unlocked_rollover.png"));
   static ImageIcon locked_rolloverIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/locked_rollover.png"));
   static ImageIcon lockedIcon=new ImageIcon(Utilities.loadImage("org/opensim/coordinateviewer/images/locked.png"));
   
  
   public CoordinateSliderWithBox(Coordinate coord) {
      this.coord = coord;
      this.model = coord.getModel();
      openSimContext = OpenSimDB.getInstance().getContext(model);
      setRotational(coord.getMotionType()==Coordinate.MotionType.Rotational);
      this.min=coord.getRangeMin()*conversion;
      this.max=coord.getRangeMax()*conversion;
      min=roundBoundIfNeeded(min);
      max=roundBoundIfNeeded(max);
      
//      if (isRotational()){ // Make the step one degree
//         step=1.0;
//      }
//      else
//         this.step = (max-min)/100;

      step = 0.001; // Make the step one thousandths of a unit
      numTicks = (int)((max - min)/step)+1;
      numberFormat = NumberFormat.getNumberInstance();
      numberFormat.setMinimumFractionDigits(3);
      formatter = new NumberFormatter(numberFormat);
      setTextfieldBounds(true);
      initComponents();
      
      jFormattedTextField.getInputMap().put(KeyStroke.getKeyStroke(
              KeyEvent.VK_ENTER, 0),
              "check");
      Action callback = new handleReturnAction();
      jFormattedTextField.getActionMap().put("check", callback);
      jXSlider.setMinimum(0);
      jXSlider.setMaximum(numTicks-1);
      
      
      createBoundsLabels(jXSlider, min, max, 0, numTicks-1);
      jCoordinateNameLabel.setText(coord.getName());
      boolean clamped = openSimContext.getClamped(coord);
      jClampedCheckBox.setSelected(clamped);
      boolean locked = openSimContext.getLocked(coord);
      jLockedCheckBox.setSelected(locked);
      if (!clamped | locked){
         jMinimumLabel.setEnabled(false);
         jMaximumLabel.setEnabled(false);
      }
      jXSlider.setEnabled(!locked);
      jFormattedTextField.setEnabled(!locked);
//       jXSlider.setToolTipText("["+Math.round(min)+", "+Math.round(max)+"]");
      jXSlider.addChangeListener(this);
      jFormattedTextField.addPropertyChangeListener("value", this);
      jFormattedTextField.addFocusListener((FocusListener)callback);
      
      updateValue();
   }
   
   private void setTextfieldBounds(boolean trueFalse) {
      if (trueFalse){
         formatter.setMinimum(new Double(min));
         formatter.setMaximum(new Double(max));
      } else {
         formatter.setMinimum(new Double(-1e30));
         formatter.setMaximum(new Double(1e30));
         
      }
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jXSlider = new javax.swing.JSlider();
      jFormattedTextField = new JFormattedTextField(formatter);
      jClampedCheckBox = new javax.swing.JCheckBox();
      jLockedCheckBox = new javax.swing.JCheckBox();
      jCoordinateNameLabel = new javax.swing.JLabel();
      jMinimumLabel = new javax.swing.JLabel();
      jMaximumLabel = new javax.swing.JLabel();

      setAlignmentY(0.0F);
      jXSlider.setMajorTickSpacing(20);
      jXSlider.setMinorTickSpacing(10);
      jXSlider.setToolTipText("Seek");
      jXSlider.setAlignmentX(0.0F);
      jXSlider.setMinimumSize(new java.awt.Dimension(50, 25));
      jXSlider.setPreferredSize(new java.awt.Dimension(50, 25));

      jFormattedTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
      jFormattedTextField.setText("-123.456");
      jFormattedTextField.setToolTipText("Current value");
      jFormattedTextField.setFont(new java.awt.Font("Tahoma", 0, 11));
      jFormattedTextField.setMinimumSize(new java.awt.Dimension(55, 19));
      jFormattedTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jFormattedTextFieldActionPerformed(evt);
         }
      });

      jClampedCheckBox.setToolTipText("Toggle clamp to bounds");
      jClampedCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      jClampedCheckBox.setIcon(unclampedIcon);
      jClampedCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      jClampedCheckBox.setMaximumSize(new java.awt.Dimension(20, 20));
      jClampedCheckBox.setMinimumSize(new java.awt.Dimension(20, 20));
      jClampedCheckBox.setPreferredSize(new java.awt.Dimension(20, 20));
      jClampedCheckBox.setRolloverIcon(unclamped_rolloverIcon);
      jClampedCheckBox.setRolloverSelectedIcon(unclamped_rolloverIcon);
      jClampedCheckBox.setSelectedIcon(clampedIcon);
      jClampedCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jClampedCheckBoxActionPerformed(evt);
         }
      });

      jLockedCheckBox.setToolTipText("Toggle lock value");
      jLockedCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      jLockedCheckBox.setIcon(unlockedIcon);
      jLockedCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      jLockedCheckBox.setMaximumSize(new java.awt.Dimension(20, 20));
      jLockedCheckBox.setMinimumSize(new java.awt.Dimension(20, 20));
      jLockedCheckBox.setPreferredSize(new java.awt.Dimension(20, 20));
      jLockedCheckBox.setRolloverIcon(unlocked_rolloverIcon);
      jLockedCheckBox.setRolloverSelectedIcon(locked_rolloverIcon);
      jLockedCheckBox.setSelectedIcon(lockedIcon);
      jLockedCheckBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            jLockedCheckBoxActionPerformed(evt);
         }
      });

      jCoordinateNameLabel.setHorizontalAlignment(javax.swing.SwingConstants.TRAILING);
      jCoordinateNameLabel.setText("coordinate");
      jCoordinateNameLabel.setToolTipText("Name");
      jCoordinateNameLabel.setAlignmentX(1.0F);
      jCoordinateNameLabel.setMaximumSize(new java.awt.Dimension(100, 14));
      jCoordinateNameLabel.setMinimumSize(new java.awt.Dimension(100, 14));
      jCoordinateNameLabel.setPreferredSize(new java.awt.Dimension(100, 14));

      jMinimumLabel.setHorizontalAlignment(javax.swing.SwingConstants.TRAILING);
      jMinimumLabel.setText("-123");
      jMinimumLabel.setToolTipText("Lower bound");
      jMinimumLabel.setFocusable(false);
      jMinimumLabel.setIconTextGap(0);
      jMinimumLabel.setMaximumSize(new java.awt.Dimension(30, 25));
      jMinimumLabel.setMinimumSize(new java.awt.Dimension(30, 25));
      jMinimumLabel.setPreferredSize(new java.awt.Dimension(30, 25));

      jMaximumLabel.setText("123");
      jMaximumLabel.setToolTipText("Upper bound");
      jMaximumLabel.setFocusable(false);
      jMaximumLabel.setHorizontalTextPosition(javax.swing.SwingConstants.LEADING);
      jMaximumLabel.setIconTextGap(0);
      jMaximumLabel.setMaximumSize(new java.awt.Dimension(25, 25));
      jMaximumLabel.setMinimumSize(new java.awt.Dimension(25, 25));
      jMaximumLabel.setPreferredSize(new java.awt.Dimension(25, 25));

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jCoordinateNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 100, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jFormattedTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 55, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(0, 0, 0)
            .add(jLockedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 20, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(0, 0, 0)
            .add(jClampedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 20, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jMinimumLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jXSlider, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(jMaximumLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
            .add(jCoordinateNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(jMaximumLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(jFormattedTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(jLockedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(jClampedCheckBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .add(jMinimumLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
         .add(jXSlider, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
      );
   }// </editor-fold>//GEN-END:initComponents
    
   private void jClampedCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jClampedCheckBoxActionPerformed
      boolean newValue = ((JCheckBox)(evt.getSource())).isSelected();
      openSimContext.setClamped(coord, newValue);
      setTextfieldBounds(newValue);
      if (jLockedCheckBox.isSelected()) {
         // do nothing
      } else {
         jMinimumLabel.setEnabled(newValue);
         jMaximumLabel.setEnabled(newValue);
      }
      if (openSimContext.getClamped(coord)){
         if (openSimContext.getValue(coord)>coord.getRangeMax()){
            setTheValue(coord.getRangeMax()*conversion, true, true, true, true);
         } else if (openSimContext.getValue(coord)<coord.getRangeMin()){
            setTheValue(coord.getRangeMin()*conversion, true, true, true, true);
         }
      }
// TODO add your handling code here:
   }//GEN-LAST:event_jClampedCheckBoxActionPerformed
   
   private void jLockedCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jLockedCheckBoxActionPerformed
// TODO add your handling code here:
      boolean newValue = ((JCheckBox)(evt.getSource())).isSelected();
      openSimContext.setLocked(coord, newValue);
      // locked -> unClamped, update the GUI accordingly
      jClampedCheckBox.setSelected(openSimContext.getClamped(coord));
      jXSlider.setEnabled(!newValue);
      jFormattedTextField.setEnabled(!newValue);
      if (jClampedCheckBox.isSelected()) {
         jMinimumLabel.setEnabled(!newValue);
         jMaximumLabel.setEnabled(!newValue);
      }
   }//GEN-LAST:event_jLockedCheckBoxActionPerformed
   
   private void jFormattedTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jFormattedTextFieldActionPerformed
// TODO add your handling code here:
   }//GEN-LAST:event_jFormattedTextFieldActionPerformed
   
   
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JCheckBox jClampedCheckBox;
   private javax.swing.JLabel jCoordinateNameLabel;
   private javax.swing.JFormattedTextField jFormattedTextField;
   private javax.swing.JCheckBox jLockedCheckBox;
   private javax.swing.JLabel jMaximumLabel;
   private javax.swing.JLabel jMinimumLabel;
   private javax.swing.JSlider jXSlider;
   // End of variables declaration//GEN-END:variables
    /**
     * Set current value. May not correspond to a tickmark.
     * ONE SINGLE PLACE TO SET THE VALUE
     * During initialization, we don't want to update display of the whole model for every single slider.
     * but do it once after all the sliders were initialized.
     */
    void setTheValue(double theValue, boolean setText, boolean setSlider, boolean setCoordinate, boolean updateDisplay) {
       // Remove change listeners before calling setValue to avoid extraneous events
       if(setText) {
          jFormattedTextField.removePropertyChangeListener("value", this);
          jFormattedTextField.setValue(new Double(theValue));
          jFormattedTextField.addPropertyChangeListener("value", this);
       }
       if(setSlider) {
          jXSlider.removeChangeListener(this);
          jXSlider.setValue((int)((theValue-min)/step));
          jXSlider.addChangeListener(this);
       }
       if(setCoordinate) {
          openSimContext.setValue(coord, theValue/conversion);
          if (updateDisplay) {
             // Use renderAll rather than repaintAll for greater responsiveness in 3d viewer
             //ViewDB.getInstance().updateModelDisplay(OpenSimDB.getInstance().getCurrentModel());
             ViewDB.getInstance().updateModelDisplayNoRepaint(OpenSimDB.getInstance().getCurrentModel());
             ViewDB.getInstance().renderAll();
             Vector<OpenSimObject> objs = new Vector<OpenSimObject>(1);
             objs.add(coord);
             //SimbodyEngine eng = coord.getDynamicsEngine();
             ObjectsChangedEvent evnt = new ObjectsChangedEvent(this, model, objs);
             OpenSimDB.getInstance().setChanged();
             OpenSimDB.getInstance().notifyObservers(evnt);
          }
       }
    }
    
    public double getTheValue() {
       return ((Double)jFormattedTextField.getValue()).doubleValue();
    }
    
    /**
     * Update the value of the slider and textbox from the coordinate's current value without triggering any extraneous events or affecting display
     * Called from CoordinateSliderWithBox in response to model coordinates changing.
     */
    public void updateValue() {
       double theValue=openSimContext.getValue(coord) * conversion;
       setTheValue(theValue, true, true, false, false);
    }
    
    /**
     * Slider change
     */
    public void stateChanged(ChangeEvent e) {
       JSlider source = (JSlider) e.getSource();
       if (source != jXSlider) return;
       double theValue = jXSlider.getValue()*step+min;
       setTheValue(theValue, true, false, true, (source.getValueIsAdjusting()));
    }
    /**
     * Text field change
     */
    public void propertyChange(PropertyChangeEvent evt) {
       if ("value".equals(evt.getPropertyName())) {
          Number value = (Number)evt.getNewValue();
          Number valueOld = (Number)evt.getOldValue();
          if (value != null && valueOld!=value) {
             setTheValue(value.doubleValue(), false, true, true, true);
          }
       }
    }
    
    private void createBoundsLabels(JSlider jXSlider, double min, double max, int minint, int maxint) {
       double rounded = Math.round(min);
       if (Math.abs(min-rounded)<ROUNDOFF) min=rounded;
       // Limit display to 2 significant digit
       DecimalFormat formatter = new DecimalFormat(LABELS_FORMAT);
       String myString = formatter.format(min);
       jMinimumLabel.setText(myString);
       //JLabel startLabel = new JLabel(myString);
       rounded = Math.round(max);
       if (Math.abs(max-rounded)<ROUNDOFF) max=rounded;
       myString = formatter.format(max);
       //JLabel endLabel = new JLabel(myString);
       jMaximumLabel.setText(myString);
       //Hashtable<Integer,JLabel> labels = new Hashtable<Integer,JLabel>(2);
       //labels.put(minint, startLabel);
       //labels.put(maxint, endLabel);
       //jXSlider.setLabelTable(labels);
    }
    
    class handleReturnAction extends AbstractAction implements FocusListener {
       public void actionPerformed(ActionEvent e) {
          Number oldValue = (Number)jFormattedTextField.getValue();
          if (!jFormattedTextField.isEditValid()) { //The text is invalid.
             Toolkit.getDefaultToolkit().beep();
             String text = jFormattedTextField.getText();
             // Try to parse the text into a double as it could be out of range, in this case truncate
             try {
                double valueFromTextField = numberFormat.parse(text).doubleValue();
                if (openSimContext.getClamped(coord)){
                   if (valueFromTextField >max){
                      jFormattedTextField.setText(numberFormat.format(max));
                      jFormattedTextField.commitEdit();
                   } else {
                      jFormattedTextField.setText(numberFormat.format(min));
                      jFormattedTextField.commitEdit();
                   }
                } else
                   throw new UnsupportedOperationException();
             } catch (ParseException ex){
                jFormattedTextField.setText(numberFormat.format(oldValue));
             }
          } else try {                    //The text is valid,
             jFormattedTextField.commitEdit();     //so use it.
          } catch (java.text.ParseException exc) {
             jFormattedTextField.setText(numberFormat.format(oldValue));
          }
       }

       public void focusLost(java.awt.event.FocusEvent evt) {
          // The formatted text field already takes care of handling the
          // new value when focus is lost, as long as the new value is valid.
          // So here all we need to do is handle the case of an invalid
          // value so that the behavior is the same as in actionPerformed().
          Number oldValue = (Number)jFormattedTextField.getValue();
          if (!jFormattedTextField.isEditValid()) { //The text is invalid.
             Toolkit.getDefaultToolkit().beep();
             String text = jFormattedTextField.getText();
             // Try to parse the text into a double as it could be out of range, in this case truncate
             try {
                double valueFromTextField = numberFormat.parse(text).doubleValue();
                if (openSimContext.getClamped(coord)){
                   if (valueFromTextField >max){
                      jFormattedTextField.setText(numberFormat.format(max));
                      jFormattedTextField.commitEdit();
                   } else {
                      jFormattedTextField.setText(numberFormat.format(min));
                      jFormattedTextField.commitEdit();
                   }
                } else
                   throw new UnsupportedOperationException();
             } catch (ParseException ex){
                jFormattedTextField.setText(numberFormat.format(oldValue));
             }
          }
       }

       public void focusGained(java.awt.event.FocusEvent evt) {
       }
    }
    
    public boolean isRotational() {
       return rotational;
    }
    
    public void setRotational(boolean rotational) {
       this.rotational = rotational;
       if (rotational)
          conversion=180.0/Math.PI;
    }
    
    /**
     * Due to round off in converting back and forth between ints and floats we need to make sure sliders
     * and text boxes end up with proper int bounds if warranted
     *
     * This doesn't work now because of tight tolerances setting coordinate values
     */
    private double roundBoundIfNeeded(double bound) {
       double absBound = Math.abs(bound);
       double roundAbsBound= Math.round(absBound);
       if (Math.abs(absBound-roundAbsBound)<ROUNDOFF){
          return (bound>=0)?roundAbsBound:-roundAbsBound;
       } else
          return bound;
    }
     
}
