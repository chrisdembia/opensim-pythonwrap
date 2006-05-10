package simtkView.plot;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import ptolemy.plot.*;
import simtkModel.*;

public class SimtkEditPlotDialog extends JDialog implements ActionListener {
  private EditablePlot plot = new EditablePlot();   // The plot box with all plotting capabilities
  private rdControl _control;
  JPanel jPlotPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  BorderLayout borderLayout2 = new BorderLayout();
  JPanel jEditPlotControlPanel = new JPanel();
  JButton jRedoButton = new JButton();
  JButton jUndoLastEditButton = new JButton();
  JButton jCancelButton = new JButton();
  JButton jOkButton = new JButton();
  private double[][] _backupControlData;
  JPanel jEditQtySelectionPanel = new JPanel();
  JLabel jEditQtyLabel = new JLabel();
  JComboBox jEditQtyComboBox = new JComboBox();
  ComboBoxModel  editQtyComboBoxModel;
  Object EditQuantities[] = new Object[2];
  final double PLOT_EDIT_ZERO = .001;

  public SimtkEditPlotDialog(rdControl aControl) {
    _control = aControl;
    saveBackupData();
    loadControlIntoPlot();
    EditQuantities[0] = aControl.getName();
    EditQuantities[1] = "excitation_time";
    editQtyComboBoxModel = new DefaultComboBoxModel(EditQuantities);

    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * saveBackupData
   *
   * If times are not permitted to change we should only keep values but it's done in more generality
   * here so that we don't have to touch this part if the assumption about time does change.
   */
  private void saveBackupData() {
    int numNodes = _control.getNumParameters();
    _backupControlData = new double[2][numNodes];
    for (int i = 0; i < numNodes; i++) {
      _backupControlData[0][i]=_control.getParameterTime(i);
      _backupControlData[1][i]=_control.getParameterValue(i);
    }
  }

  /**
   * loadControlIntoPlot
   */
  private void loadControlIntoPlot() {
    plot.addLegend(0, _control.getName());
    plot.setMarksStyle("dots");
    plot.addLegend(1, "activation_intervals");
    int numNodes = _control.getNumParameters();
    for (int i=0; i < numNodes; i++){
      plot.addPoint(0, _control.getParameterTime(i), _control.getParameterValue(i), true);
      plot.addPoint(1, _control.getParameterTime(i), 0., true);
   }

  }

  private void jbInit() throws Exception {
    this.getContentPane().setLayout(borderLayout1);
    jPlotPanel.setLayout(borderLayout2);
    this.setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    this.setModal(true);
    plot.setGrid(true);
    plot.setTitle("Excitation Editor");
    plot.setXLabel("time");
    plot.setXLog(false);
    plot.setYLabel("Excitation");
    //this.getContentPane().add(plot);
    jRedoButton.setText("Redo");
    jRedoButton.addActionListener(new SimtkEditPlotDialog_jRedoButton_actionAdapter(this));
    jUndoLastEditButton.setToolTipText("");
    jUndoLastEditButton.setText("Undo");
    jUndoLastEditButton.addActionListener(new SimtkEditPlotDialog_jUndoLastEditButton_actionAdapter(this));
    jCancelButton.setToolTipText("");
    jCancelButton.setText("Cancel");
    jCancelButton.addActionListener(new SimtkEditPlotDialog_jCancelButton_actionAdapter(this));
    jOkButton.setText("OK");
    jOkButton.addActionListener(new SimtkEditPlotDialog_jOkButton_actionAdapter(this));
    jEditQtyLabel.setToolTipText("");
    jEditQtyLabel.setText("Edit:");
    jEditQtyComboBox.setMaximumRowCount(2);
    jEditQtySelectionPanel.add(jEditQtyLabel, null);
    jEditQtySelectionPanel.add(jEditQtyComboBox, null);
    jEditQtyComboBox.setModel(editQtyComboBoxModel);
    this.getContentPane().add(jPlotPanel, BorderLayout.CENTER);
    jPlotPanel.add(plot, BorderLayout.CENTER);
    this.getContentPane().add(jEditPlotControlPanel,  BorderLayout.SOUTH);
    jEditPlotControlPanel.add(jOkButton, null);
    jEditPlotControlPanel.add(jCancelButton, null);
    jEditPlotControlPanel.add(jUndoLastEditButton, null);
    jEditPlotControlPanel.add(jRedoButton, null);
    jEditPlotControlPanel.add(jEditQtySelectionPanel, null);
    jEditQtyComboBox.addActionListener(this);
  }

  void jOkButton_actionPerformed(ActionEvent e) {
    double[][] data = plot.getData(0);
    // Modify control from data, assume no change in number of nodes
    int numNodes = _control.getNumParameters();
    for (int i=0; i < numNodes; i++){
      if (Math.abs(data[1][0])<PLOT_EDIT_ZERO)
        data[1][0] = 0.0;
      _control.setParameterValue(i, data[1][i]);
   }
   this.dispose();
  }

  void jCancelButton_actionPerformed(ActionEvent e) {
    plot.clear(0);
    plot.removeLegend(0);
    plot.clear(1);
    plot.removeLegend(1);
    restoreBackupData();
    loadControlIntoPlot();
  }

  /**
   * restoreBackupData
   */
  private void restoreBackupData() {
    int numNodes = _control.getNumParameters();
     for (int i = 0; i < numNodes; i++) {
       _control.setParameterValue(i, _backupControlData[1][i]);
      }
  }

  void jUndoLastEditButton_actionPerformed(ActionEvent e) {
    plot.undo();
  }

  void jRedoButton_actionPerformed(ActionEvent e) {
    plot.redo();
  }

  /**
   * actionPerformed
   *
   * @param e ActionEvent
   */
  public void actionPerformed(ActionEvent e) {
    JComboBox cb = (JComboBox)e.getSource();
    int setToEdit = cb.getSelectedIndex();
    plot.setEditable(setToEdit);
  }

}

class SimtkEditPlotDialog_jOkButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkEditPlotDialog adaptee;

  SimtkEditPlotDialog_jOkButton_actionAdapter(SimtkEditPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jOkButton_actionPerformed(e);
  }
}

class SimtkEditPlotDialog_jCancelButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkEditPlotDialog adaptee;

  SimtkEditPlotDialog_jCancelButton_actionAdapter(SimtkEditPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jCancelButton_actionPerformed(e);
  }
}

class SimtkEditPlotDialog_jUndoLastEditButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkEditPlotDialog adaptee;

  SimtkEditPlotDialog_jUndoLastEditButton_actionAdapter(SimtkEditPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jUndoLastEditButton_actionPerformed(e);
  }
}

class SimtkEditPlotDialog_jRedoButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkEditPlotDialog adaptee;

  SimtkEditPlotDialog_jRedoButton_actionAdapter(SimtkEditPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jRedoButton_actionPerformed(e);
  }
}
