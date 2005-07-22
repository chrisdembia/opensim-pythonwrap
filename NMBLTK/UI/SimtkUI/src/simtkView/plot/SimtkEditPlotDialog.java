package simtkView.plot;
import ptolemy.plot.*;
import simtkModel.*;
import simtkui.guiUtilities.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SimtkEditPlotDialog extends SimtkJDialog {
  private Plot plot = new EditablePlot();   // The plot box with all plotting capabilities
  private rdControl _control;
  private final double PAD=0.1;
  JPanel jPlotPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jEditPlotControlPanel = new JPanel();
  JButton jRedoButton = new JButton();
  JButton jUndoLastEditButton = new JButton();
  JButton jCancelButton = new JButton();
  JButton jOkButton = new JButton();
  public SimtkEditPlotDialog(rdControl aControl) {
    _control = aControl;
    loadControlIntoPlot();
    getContentPane().add(plot);
  }

  /**
   * loadControlIntoPlot
   */
  private void loadControlIntoPlot() {
    plot.addLegend(0, _control.getName());
    plot.setMarksStyle("dots");
    plot.setXRange(_control.getFirstTime(), _control.getLastTime());
    plot.setYRange(_control.getControlValue(_control.getFirstTime())-PAD, _control.getControlValue(_control.getLastTime())+PAD);
    int numNodes = _control.getNumParameters();
    for (int i=0; i < numNodes; i++){
      plot.addPoint(0, _control.getParameterTime(i), _control.getParameterValue(i), true);
    }
  }

  public SimtkEditPlotDialog() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    this.getContentPane().setLayout(borderLayout1);
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
    this.getContentPane().add(jPlotPanel, BorderLayout.CENTER);
    this.getContentPane().add(jEditPlotControlPanel,  BorderLayout.SOUTH);
    jEditPlotControlPanel.add(jOkButton, null);
    jEditPlotControlPanel.add(jCancelButton, null);
    jEditPlotControlPanel.add(jUndoLastEditButton, null);
    jEditPlotControlPanel.add(jRedoButton, null);
  }

  void jOkButton_actionPerformed(ActionEvent e) {
    // Get data from dialog and apply to Control
  }

  void jCancelButton_actionPerformed(ActionEvent e) {

  }

  void jUndoLastEditButton_actionPerformed(ActionEvent e) {

  }

  void jRedoButton_actionPerformed(ActionEvent e) {

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
