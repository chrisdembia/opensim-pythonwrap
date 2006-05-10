package simtkView;


import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import vtk.*;
import simtkui.guiUtilities.*;
import javax.swing.event.*;
import java.util.*;

public class SimtkVisibilityControlDlg extends SimtkJDialog implements ChangeListener {
  JPanel jControlPanel = new JPanel();
  JSlider OpacitySlider = new JSlider();
  JLabel OpacityLabel = new JLabel();
  JButton CancelButton = new JButton();
  JButton CloseButton = new JButton();
  JButton ColorButton = new JButton();
  JPanel jVisibilityControlPanel = new JPanel();
  TitledBorder titledBorder1;
  BorderLayout borderLayout1 = new BorderLayout();
  Vector actors;
  vtkActor representativeActor;
  vtkPanel window;
  /** Support/model for opacity slider */
  BoundedRangeModel opacitySlider = new DefaultBoundedRangeModel();
  Border border1;
  double saveOpacity;
  Color saveColor;
  FlowLayout flowLayout1 = new FlowLayout();
  FlowLayout flowLayout2 = new FlowLayout();

  public SimtkVisibilityControlDlg(Vector objActors, vtkPanel window) {

    actors = objActors;
    this.window = window;
    representativeActor = ((SimtkVisRep) actors.get(0)).getGeomActor();
    saveOpacity = representativeActor.GetProperty().GetOpacity();
    double[] dColorComponents;
    dColorComponents = representativeActor.GetProperty().GetColor();
    saveColor = new Color( (float) dColorComponents[0],
                            (float) dColorComponents[1],
                            (float) dColorComponents[2]);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

  }
  private void jbInit() throws Exception {
    border1 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    ColorButton.addActionListener(new SimtkVisibilityControlDlg_ColorButton_actionAdapter(this));
    OpacitySlider.setPaintTicks(true);
    OpacitySlider.setLayout(flowLayout1);
    CancelButton.addActionListener(new SimtkVisibilityControlDlg_CancelButton_actionAdapter(this));
    CloseButton.addActionListener(new SimtkVisibilityControlDlg_CloseButton_actionAdapter(this));
    CloseButton.setToolTipText("");
    CloseButton.setActionCommand("Close");
    jControlPanel.add(CloseButton, null);
    jControlPanel.add(CancelButton, null);
    this.setDefaultCloseOperation(HIDE_ON_CLOSE);
    this.setEnabled(true);
    this.setForeground(Color.black);
    this.setTitle("Visibilty Control");
    this.getContentPane().setLayout(borderLayout1);
    this.getContentPane().add(jControlPanel, BorderLayout.SOUTH);
    jVisibilityControlPanel.add(OpacityLabel, null);
    jVisibilityControlPanel.add(OpacitySlider, null);
    jVisibilityControlPanel.add(ColorButton, null);
    titledBorder1 = new TitledBorder(BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151)),"Visibility Control");
    OpacitySlider.setMajorTickSpacing(0);
    OpacitySlider.setMaximum(100);
    OpacitySlider.setMinimum(0);
    OpacitySlider.setMinorTickSpacing(0);
    OpacitySlider.setPaintTrack(true);
    OpacitySlider.setMaximumSize(new Dimension(80, 19));
    OpacitySlider.setMinimumSize(new Dimension(80, 19));
    OpacitySlider.setPreferredSize(new Dimension(70, 19));
    OpacityLabel.setToolTipText("");
    OpacityLabel.setText("Opacity:");
    CancelButton.setText("Cancel");
    CloseButton.setText("Close");
    ColorButton.setToolTipText("");
    ColorButton.setActionCommand("Surface Color ");
    ColorButton.setText("Surface Color...");
    jVisibilityControlPanel.setBorder(border1);
    jVisibilityControlPanel.setLayout(flowLayout2);
    this.getContentPane().add(jVisibilityControlPanel,  BorderLayout.CENTER);
    double opacityValue = representativeActor.GetProperty().GetOpacity();
    opacitySlider.setValue((int)(opacityValue*100));
    OpacitySlider.getModel().addChangeListener(this);
  }

  void ColorButton_actionPerformed(ActionEvent e) {
    Color newColor = JColorChooser.showDialog(this, "Object Color",
                                              saveColor);
    if (newColor == null) // user cancelled
      return;
    float[] colorComponents = newColor.getRGBComponents(null);
    double[] dColorComponents = new double[3];
   for (int i=0; i <3; i++)
     dColorComponents[i] = colorComponents[i];
   for(int i=0; i < actors.size(); i++){
      ((SimtkVisRep) actors.get(i)).setColor(dColorComponents);
    }
  }

  /**
   * stateChanged
   *
   * @param e ChangeEvent
   */
  public void stateChanged(ChangeEvent e) {
    // Opacity slider
    BoundedRangeModel theSlider = (BoundedRangeModel) e.getSource();
    if (theSlider.getValueIsAdjusting())
      return;
    int newOpacity = theSlider.getValue();
    for(int i=0; i < actors.size(); i++){
       ((SimtkVisRep) actors.get(i)).setOpacity((double)newOpacity/100.0);
     }
    window.Render();
  }

  void CancelButton_actionPerformed(ActionEvent e) {
    float colorComponents[];
    colorComponents = saveColor.getRGBColorComponents(null);
    double[] dColorComponents = new double[3];
    for (int i=0; i <3; i++)
      dColorComponents[i] = colorComponents[i];

    for(int i=0; i < actors.size(); i++){
      ((SimtkVisRep) actors.get(i)).setOpacity(saveOpacity);
      ((SimtkVisRep) actors.get(i)).setColor(dColorComponents);
    }
    window.Render();

  }

  void CloseButton_actionPerformed(ActionEvent e) {
    this.dispose();
  }



}

class SimtkVisibilityControlDlg_ColorButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkVisibilityControlDlg adaptee;

  SimtkVisibilityControlDlg_ColorButton_actionAdapter(SimtkVisibilityControlDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ColorButton_actionPerformed(e);
  }
}

class SimtkVisibilityControlDlg_CancelButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkVisibilityControlDlg adaptee;

  SimtkVisibilityControlDlg_CancelButton_actionAdapter(SimtkVisibilityControlDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CancelButton_actionPerformed(e);
    adaptee.dispose();
  }
}

class SimtkVisibilityControlDlg_CloseButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkVisibilityControlDlg adaptee;

  SimtkVisibilityControlDlg_CloseButton_actionAdapter(SimtkVisibilityControlDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CloseButton_actionPerformed(e);
  }
}

