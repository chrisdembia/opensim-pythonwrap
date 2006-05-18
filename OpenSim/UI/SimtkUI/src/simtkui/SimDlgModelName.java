package simtkui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import simtkui.guiUtilities.SimtkJDialog;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * This dialog is used to query the user for model name. Model name has to
 * correspond to a class that:
 * 1. Extends Model.
 * 2. Has no-args constructor
 * 3. Is available in classpath
 * @todo use the generic SimDlgGetName dialog instead to avoid code duplication
 */
public class SimDlgModelName extends SimtkJDialog {
  JPanel jPanel1 = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JLabel jLabel1 = new JLabel();
  JPanel jPanel3 = new JPanel();
  JButton jCancelButton = new JButton();
  JButton jOkButton = new JButton();
  JTextField jModelNameTextField = new JTextField();

  String _modelName = "";
  boolean _userConfirmed = false;

  /**
   * SimDlgModelName: Default constructor
   */
  public SimDlgModelName() {
    super();
    this.setTitle("Simtk Model Selection");
    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * jbInit: Crteated by JBuilder for GUI component intialization
   *
   * @throws Exception
   */
  private void jbInit() throws Exception {
    this.getContentPane().setBackground(SystemColor.control);
    this.setEnabled(true);
    this.setForeground(Color.black);
    this.setLocale(java.util.Locale.getDefault());
    this.setModal(true);
    this.setTitle("Enter Model Name");
    this.getContentPane().setLayout(borderLayout1);
    jLabel1.setAlignmentX( (float) 0.0);
    jLabel1.setAlignmentY( (float) 0.5);
    jLabel1.setToolTipText("");
    jLabel1.setText("Model Name: ");
    jLabel1.setVerticalAlignment(javax.swing.SwingConstants.TOP);
    jLabel1.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
    jCancelButton.setToolTipText("");
    jCancelButton.setHorizontalAlignment(SwingConstants.RIGHT);
    jCancelButton.setText("Cancel");
    jCancelButton.addActionListener(new SimDlgModelName_jCancelButton_actionAdapter(this));
    jOkButton.setToolTipText("Add selected model ");
    jOkButton.setActionCommand("OK");
    jOkButton.setHorizontalAlignment(SwingConstants.CENTER);
    jOkButton.setText("OK");
    jOkButton.addActionListener(new SimDlgModelName_jOkButton_actionAdapter(this));
    jModelNameTextField.setMinimumSize(new Dimension(150, 20));
    jModelNameTextField.setPreferredSize(new Dimension(150, 20));
    jModelNameTextField.setRequestFocusEnabled(true);
    jModelNameTextField.setText("");
    jModelNameTextField.addActionListener(new SimDlgModelName_jModelNameTextField_actionAdapter(this));
    jPanel1.setMinimumSize(new Dimension(250, 30));
    jPanel1.setPreferredSize(new Dimension(250, 30));
    jPanel1.add(jLabel1, null);
    jPanel1.add(jModelNameTextField, null);
    this.getContentPane().add(jPanel1, BorderLayout.CENTER);
    jPanel3.add(jOkButton, null);
    jPanel3.add(jCancelButton, null);
    this.getContentPane().add(jPanel3, BorderLayout.SOUTH);
  }

  void jOkButton_actionPerformed(ActionEvent e) {
    _modelName = jModelNameTextField.getText();
    if (_modelName.length()==0){
      SimtkApp.displayErrorMessage("Please enter the full class name of your model.");
      return;
    }
    this.setVisible(false);
    _userConfirmed = true;
  }

  void jCancelButton_actionPerformed(ActionEvent e) {
    _modelName = "";
    this.setVisible(false);
    _userConfirmed = false;
  }

  /**
   * getModelName: Retrieves model name from the dialog after it's brought down.
   * Returns "" if nothing was assigned or the user cancelled out.
   *
   * @return String
   */
  public String getModelName() {
    return _modelName;
  }

  /**
   * userConfirmed: Returns true if the uer exist the dialog after hittingok,
   * false otherwise
   *
   * @return boolean
   */
  public boolean userConfirmed() {
    return _userConfirmed;
  }

  class SimDlgModelName_jOkButton_actionAdapter
      implements java.awt.event.ActionListener {
    SimDlgModelName adaptee;

    SimDlgModelName_jOkButton_actionAdapter(SimDlgModelName adaptee) {
      this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
      adaptee.jOkButton_actionPerformed(e);
    }
  }

  class SimDlgModelName_jCancelButton_actionAdapter
      implements java.awt.event.ActionListener {
    SimDlgModelName adaptee;

    SimDlgModelName_jCancelButton_actionAdapter(SimDlgModelName adaptee) {
      this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
      adaptee.jCancelButton_actionPerformed(e);
    }
  }

  void jModelNameTextField_actionPerformed(ActionEvent e) {

  }

class SimDlgModelName_jModelNameTextField_actionAdapter implements java.awt.event.ActionListener {
  SimDlgModelName adaptee;

  SimDlgModelName_jModelNameTextField_actionAdapter(SimDlgModelName adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jModelNameTextField_actionPerformed(e);
  }
}
}
