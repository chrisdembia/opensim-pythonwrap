package simtkView;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;

public class SimtkVisibilityControlDlg extends JFrame{
  GridLayout gridLayout2 = new GridLayout();
  JPanel jPanel1 = new JPanel();
  JPanel jPanel2 = new JPanel();
  JPanel jPanel3 = new JPanel();
  JPanel jPanel4 = new JPanel();
  JPanel jPanel5 = new JPanel();
  JPanel jPanel6 = new JPanel();
  JPanel jPanel7 = new JPanel();
  JLabel ObjectNameLabel = new JLabel();
  JLabel ObjectName = new JLabel();
  JComboBox RepresentationComboBox = new JComboBox();
  JLabel SurfaceRepLabel = new JLabel();
  JSlider OpacitySlider = new JSlider();
  JLabel OpacityLabel = new JLabel();
  JButton CancelButton = new JButton();
  JButton OKButton = new JButton();
  JCheckBox NormalsCheckBox = new JCheckBox();
  JCheckBox BoundingBoxCheckBox = new JCheckBox();
  JButton ColorButton = new JButton();
  JButton Apply = new JButton();
  public SimtkVisibilityControlDlg() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    gridLayout2.setColumns(1);
    gridLayout2.setRows(7);
    gridLayout2.setVgap(0);
    this.setDefaultCloseOperation(HIDE_ON_CLOSE);
    this.setEnabled(true);
    this.setForeground(Color.black);
    this.setState(Frame.NORMAL);
    this.setTitle("Visibilty Control");
    this.getContentPane().setLayout(gridLayout2);
    ObjectNameLabel.setText("Object Name:");
    ObjectName.setToolTipText("");
    ObjectName.setText("");
    RepresentationComboBox.setMinimumSize(new Dimension(100, 19));
    RepresentationComboBox.setPreferredSize(new Dimension(100, 19));
    SurfaceRepLabel.setToolTipText("");
    SurfaceRepLabel.setText("Representation");
    OpacitySlider.setMajorTickSpacing(0);
    OpacitySlider.setMaximum(80);
    OpacitySlider.setMinimum(0);
    OpacitySlider.setMinorTickSpacing(0);
    OpacitySlider.setPaintTrack(true);
    OpacitySlider.setMaximumSize(new Dimension(80, 19));
    OpacitySlider.setMinimumSize(new Dimension(80, 19));
    OpacitySlider.setPreferredSize(new Dimension(70, 19));
    OpacityLabel.setToolTipText("");
    OpacityLabel.setText("Opacity:");
    CancelButton.setText("Cancel");
    OKButton.setText("OK");
    NormalsCheckBox.setToolTipText("");
    NormalsCheckBox.setText("Normals");
    BoundingBoxCheckBox.setToolTipText("");
    BoundingBoxCheckBox.setText("BoundingBox");
    ColorButton.setToolTipText("");
    ColorButton.setText("Surface Color");
    Apply.setToolTipText("");
    Apply.setText("Apply");
    this.getContentPane().add(jPanel1, null);
    jPanel1.add(ObjectNameLabel, null);
    jPanel1.add(ObjectName, null);
    this.getContentPane().add(jPanel2, null);
    jPanel2.add(SurfaceRepLabel, null);
    jPanel2.add(RepresentationComboBox, null);
    jPanel4.add(BoundingBoxCheckBox, null);
    jPanel4.add(NormalsCheckBox, null);
    this.getContentPane().add(jPanel5, null);
    jPanel5.add(OpacityLabel, null);
    jPanel5.add(OpacitySlider, null);
    jPanel5.add(ColorButton, null);
    this.getContentPane().add(jPanel4, null);
    this.getContentPane().add(jPanel6, null);
    jPanel6.add(jPanel3, null);
    this.getContentPane().add(jPanel7, null);
    jPanel7.add(Apply, null);
    jPanel7.add(OKButton, null);
    jPanel7.add(CancelButton, null);
  }

}
