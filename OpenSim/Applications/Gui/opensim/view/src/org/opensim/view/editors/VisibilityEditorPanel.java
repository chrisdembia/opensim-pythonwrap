/*
 *
 * VisibilityEditorPanel
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view.editors;

import java.awt.Color;
import java.util.Collection;
import javax.swing.JColorChooser;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.OpenSimCanvas;
import vtk.vtkProperty;

/**
 *
 * @author Ayman
 */
public class VisibilityEditorPanel extends AbstractEditorPanel implements ChangeListener {
    OpenSimObject   object;
    OpenSimCanvas   canvas;
    vtkProperty     saveProperty;
    
    /** Creates new form VisibilityJDialog */
    public VisibilityEditorPanel( OpenSimObject object, OpenSimCanvas canvas) {
        this.object = object;
        this.canvas = canvas;
        initComponents();
        saveProperty = new vtkProperty();
        canvas.getObjectProperties(object, saveProperty);
        OpacitySlider.setValue((int)(saveProperty.GetOpacity()*100));
        OpacitySlider.addChangeListener(this);
    }
 
    private void jChooseColorBtnActionPerformed(java.awt.event.ActionEvent evt) {                                                
// TODO add your handling code here:
        JColorChooser objectColorChooser = new JColorChooser();
        Color newColor = objectColorChooser.showDialog(canvas, "Select new background color", canvas.getBackground());
        if (newColor != null){
             float[] colorComponents = newColor.getRGBComponents(null);
             double[] dColorComponents = new double[]{colorComponents[0], colorComponents[1], colorComponents[2]};
             canvas.setObjectColor(object, dColorComponents);
             canvas.repaint();
        }
    }                                               

    public void stateChanged(ChangeEvent e) {
        // Handle change in opacity slider
        int newOpacity = ((javax.swing.JSlider)e.getSource()).getValue();
        canvas.setObjectOpacity(object, (double)newOpacity/100.0);
        canvas.repaint();
    }

    private void initComponents() {
        
        setBorder(javax.swing.BorderFactory.createTitledBorder("Visibility Editor"));
        ObjectNameLabel = new javax.swing.JLabel();
        ObjectNameText = new javax.swing.JTextField();
        OpacityLabel = new javax.swing.JLabel();
        OpacitySlider = new javax.swing.JSlider();
        ColorLabel = new javax.swing.JLabel();
        jChooseColorBtn = new javax.swing.JButton();

        getAccessibleContext().setAccessibleParent(null);
        ObjectNameLabel.setText("Object Name:");

        ObjectNameText.setEditable(false);
        ObjectNameText.setText(object.getName());

        OpacityLabel.setText("Opacity:");

        ColorLabel.setText("Color:");

        jChooseColorBtn.setText("Choose...");
        jChooseColorBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jChooseColorBtnActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                        .add(OpacityLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(OpacitySlider, 0, 0, Short.MAX_VALUE))
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                        .add(ObjectNameLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(ObjectNameText, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 88, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))
                .add(1, 1, 1)
                .add(ColorLabel)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jChooseColorBtn)
                .add(36, 36, 36))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(ObjectNameLabel)
                    .add(ObjectNameText, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(OpacitySlider, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                        .add(OpacityLabel)
                        .add(ColorLabel)
                        .add(jChooseColorBtn)))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }

    public void confirmEdit() {
        // do nothing.
    }

    public void cancelEdit() {
        // restore vtk property 
        canvas.setObjectProperties(object, saveProperty);
        canvas.repaint();
    }
                   
    private javax.swing.JButton CancelBtn;
    private javax.swing.JLabel ColorLabel;
    private javax.swing.JLabel ObjectNameLabel;
    private javax.swing.JTextField ObjectNameText;
    private javax.swing.JButton OkBtn;
    private javax.swing.JLabel OpacityLabel;
    private javax.swing.JSlider OpacitySlider;
    private javax.swing.JButton jChooseColorBtn;
               
}
