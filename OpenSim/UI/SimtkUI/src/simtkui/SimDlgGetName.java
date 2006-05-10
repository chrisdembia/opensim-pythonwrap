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

import simtkUtils.SimtkValidateName;
import simtkui.guiUtilities.SimtkJDialog;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @todo: allow passing as parameter a list of invalid names or a function that
 * validates names to be invoked by ok so that invalid names are rejected right
 * while the dialog is up.
 *
 * @author Ayman Habib
 * @version 1.0 This dialog is used to query the user for generic name.
 */
public class SimDlgGetName
    extends SimtkJDialog {
  JPanel jPanel1 = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JLabel jLabel1 = new JLabel();
  JPanel jPanel3 = new JPanel();
  JButton jCancelButton = new JButton();
  JButton jOkButton = new JButton();
  JTextField jNameTextField = new JTextField();

  String _Name = "";
  boolean _userConfirmed = false;
  private String _nameForwhat="";
  protected SimtkValidateName _validatingObject=null;
  /**
   * SimDlgGetName: Default constructor
   */
  public SimDlgGetName(String nameFor) {
    super();
    _nameForwhat = nameFor;
    this.setTitle("Simtk Get Name for "+_nameForwhat);
    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    this.pack();
    this.center();
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
    this.setTitle("Enter "+_nameForwhat+" Name");
    this.getContentPane().setLayout(borderLayout1);
    jLabel1.setAlignmentX( (float) 0.0);
    jLabel1.setAlignmentY( (float) 0.5);
    jLabel1.setToolTipText("");
    jLabel1.setText(" Name: ");
    jLabel1.setVerticalAlignment(javax.swing.SwingConstants.TOP);
    jLabel1.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
    jCancelButton.setToolTipText("");
    jCancelButton.setHorizontalAlignment(SwingConstants.RIGHT);
    jCancelButton.setText("Cancel");
    jCancelButton.addActionListener(new SimDlgGetName_jCancelButton_actionAdapter(this));
    jOkButton.setToolTipText("Accept "+_nameForwhat+" name");
    jOkButton.setActionCommand("OK");
    jOkButton.setHorizontalAlignment(SwingConstants.CENTER);
    jOkButton.setText("OK");
    jOkButton.addActionListener(new SimDlgGetName_jOkButton_actionAdapter(this));
    jNameTextField.setMinimumSize(new Dimension(150, 20));
    jNameTextField.setPreferredSize(new Dimension(150, 20));
    jNameTextField.setRequestFocusEnabled(true);
    jNameTextField.setText("");
    jNameTextField.addActionListener(new SimDlgGetName_jNameTextField_actionAdapter(this));
    jPanel1.setMinimumSize(new Dimension(250, 30));
    jPanel1.setPreferredSize(new Dimension(250, 30));
    jPanel1.add(jLabel1, null);
    jPanel1.add(jNameTextField, null);
    this.getContentPane().add(jPanel1, BorderLayout.CENTER);
    jPanel3.add(jOkButton, null);
    jPanel3.add(jCancelButton, null);
    this.getContentPane().add(jPanel3, BorderLayout.SOUTH);
  }

  void jOkButton_actionPerformed(ActionEvent e) {
    _Name = jNameTextField.getText().trim(); // Remove leading and trailing spaces

    if (_Name.length()==0){
      SimtkApp.displayErrorMessage("Blank is not a valid name.");
      return;
    }
    // If a validation object is registered, invoke validation method
    if (_validatingObject != null){
      // invoke validation method so that the error is reported right here at the dialog
      int validationStatus = _validatingObject.validateName(_Name);
      if (validationStatus != SimtkValidateName.NAME_IS_OK){
        switch(validationStatus){
         case SimtkValidateName.NAME_IS_RESERVED:
          SimtkApp.displayErrorMessage("The name " + _Name +
                                  " is reserved, please use a different name.");
          break;
        case SimtkValidateName.NAME_ALREADY_IN_USE:
          SimtkApp.displayErrorMessage("The name " + _Name +
                                  " is already in use, please use a different name.");
          break;
        case SimtkValidateName.NAME_HAS_ILLEGAL_CHARACTERS:
        default:
          SimtkApp.displayErrorMessage("The name " + _Name +
                                  " is not a valid name, please use a different name.");
          break;

        }
        return;
      }
    }
    this.setVisible(false);
    _userConfirmed = true;
  }

  void jCancelButton_actionPerformed(ActionEvent e) {
    _Name = "";
    this.setVisible(false);
    _userConfirmed = false;
  }

  /**
   * getName: Retrieves  name from the dialog after it's brought down.
   * Returns "" if nothing was assigned or the user cancelled out.
   *
   * @return String
   */
  public String getName() {
    return _Name;
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

  void jNameTextField_actionPerformed(ActionEvent e) {

  }

  public void setValidationMethod(SimtkValidateName objToValidate)
  {
    _validatingObject=objToValidate;
  }

  class SimDlgGetName_jOkButton_actionAdapter
      implements java.awt.event.ActionListener {
    SimDlgGetName adaptee;

    SimDlgGetName_jOkButton_actionAdapter(SimDlgGetName adaptee) {
      this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
      adaptee.jOkButton_actionPerformed(e);
    }
  }

  class SimDlgGetName_jCancelButton_actionAdapter
      implements java.awt.event.ActionListener {
    SimDlgGetName adaptee;

    SimDlgGetName_jCancelButton_actionAdapter(SimDlgGetName adaptee) {
      this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
      adaptee.jCancelButton_actionPerformed(e);
    }
  }

  class SimDlgGetName_jNameTextField_actionAdapter
      implements java.awt.event.ActionListener {
    SimDlgGetName adaptee;

    SimDlgGetName_jNameTextField_actionAdapter(SimDlgGetName adaptee) {
      this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
      adaptee.jNameTextField_actionPerformed(e);
    }
  }
}
