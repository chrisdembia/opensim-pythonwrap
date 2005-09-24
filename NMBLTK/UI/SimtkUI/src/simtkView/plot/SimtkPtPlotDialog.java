package simtkView.plot;

import java.awt.print.PrinterJob;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkui.guiUtilities.SimtkJDialog;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import simtkCommands.*;
import ptolemy.plot.*;
import java.util.*;
import ptolemy.plot.Plot;

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
 * Plotting Dialog, low level plotting is provided by ptolemy.plot package from
 * UCBerkeley.
 *
 * @todo perform cleanup on dialog exit as well
 */
public class SimtkPtPlotDialog extends SimtkJDialog{
  Vector plots = new Vector(); // The plot box with all plotting capabilities
  Vector plotIndices = new Vector(); // The plot box with all plotting capabilities
  int  currentPlotIndex = 0;
  Plot currentPlot = new Plot();
  JSplitPane jSplitPane1 = new JSplitPane();
  JPanel jPlotControlPanel = new JPanel();
  FlowLayout flowLayout1 = new FlowLayout();
  JButton jAddPlotButton = new JButton();
  JButton jClearPlotButton = new JButton();
  JList jPlotList = new JList();
  JPanel jPlotCommandsPanel = new JPanel();
  TitledBorder titledBorder1;
  BorderLayout borderLayout2 = new BorderLayout();
  JButton jDeletePlotButton = new JButton();
  Vector _plotHandles = new Vector();
  DefaultListModel plotListModel = new DefaultListModel();
  DefaultComboBoxModel plotQuantitiesModelX;
  DefaultComboBoxModel plotQuantitiesModelY;
  Border border1;
  TitledBorder titledBorder2;
  JButton jPrintPlotButton = new JButton();
  JPanel jPanel1 = new JPanel();
  Border border2;
  JScrollPane jScrollPane1 = new JScrollPane();
  Border border3;
  TitledBorder titledBorder3;
  Border border4;
  TitledBorder titledBorder4;
  JPanel jPanel2 = new JPanel();
  Border border5;
  TitledBorder titledBorder5;
  Border border6;
  TitledBorder titledBorder6;
  Border border7;
  TitledBorder titledBorder7;
  GridBagLayout gridBagLayout2 = new GridBagLayout();
  GridBagLayout gridBagLayout1 = new GridBagLayout();
  JLabel jPlotTitle = new JLabel();
  JTextField jTitleText = new JTextField();
  Hashtable _mapNamesToDatasets = new Hashtable();
  Border border8;
  TitledBorder titledBorder8;
  JButton SelectXButton = new JButton();
  JButton SelectYButton = new JButton();
  JTextField jXTextField = new JTextField();
  JTextField jYTextField = new JTextField();
  JPopupMenu xPopup = new SimtkPlotQuantitySelector(jXTextField);
  JPopupMenu yPopup = new SimtkPlotQuantitySelector(jYTextField);
  JPanel jPlotGridPanel = new JPanel();
  GridLayout gridLayout1 = new GridLayout();
  JPanel jGridPanel = new JPanel();
  JLabel jGridSizeLabel = new JLabel();
  JSpinner jSpinnerY = new JSpinner(new SpinnerNumberModel(1, 1, 5, 1));
  JSpinner jSpinnerX = new JSpinner(new SpinnerNumberModel(1, 1, 5, 1));
  JButton jModifyGrid = new JButton();
  int numPlots = 1;
  JLabel jCurrentPlotLabel = new JLabel();
  JComboBox jCurrentPlotComboBox = new JComboBox();
  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu jMenu1 = new JMenu();
  JMenuItem jMenuItem1 = new JMenuItem();
  JMenuItem jMenuItem2 = new JMenuItem();
  JMenu jMenu2 = new JMenu();
  JMenuItem jMenuItem3 = new JMenuItem();
  GridBagLayout gridBagLayout3 = new GridBagLayout();
  JLabel jLegendLabel = new JLabel();
  JTextField jLegendText = new JTextField();

  public SimtkPtPlotDialog() {
    plotIndices.add(new Integer("1"));
    plots.add(currentPlot);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    currentPlot.clear(true);
    jPlotList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    jPlotList.setModel(plotListModel);
    //Get quantities available for plotting from the environment
    Vector plotQuantities = new Vector();
    SimtkDB.getInstance().getAvailableQuantities(plotQuantities);
    Object[] plotQuantitiesArray = plotQuantities.toArray();
    plotQuantitiesModelX = new DefaultComboBoxModel(plotQuantitiesArray);
    plotQuantitiesModelY = new DefaultComboBoxModel(plotQuantitiesArray);
    //jComboBoxX.setModel(plotQuantitiesModelX);
    //jComboBoxY.setModel(plotQuantitiesModelY);
    jDeletePlotButton.setEnabled(plotListModel.getSize()>0);
    jPrintPlotButton.setEnabled(plotListModel.getSize()>0);
    jAddPlotButton.setEnabled(plotQuantitiesModelX.getSize()>0);
    jPlotList.addListSelectionListener(new ListSelectionListener(){
      public void valueChanged(ListSelectionEvent e) {
        if (e.getValueIsAdjusting() == false) {
          JList source = (JList) e.getSource();
            jDeletePlotButton.setEnabled(source.getSelectedIndex() != -1);
         }
      }
    });
    /*
    jCheckBoxGrid.setSelected(plot.getGrid());
    jCheckBoxStems.setSelected(plot.getImpulses());*/
    jTitleText.addFocusListener(new FocusListener(){
      /**
       * focusGained
       *
       * @param e FocusEvent
       */
      public void focusGained(FocusEvent e) {
      }

      /**
       * focusLost
       *
       * @param e FocusEvent
       */
      public void focusLost(FocusEvent e) {
        // Invoked when editing title is done
        JTextField textSource = (JTextField)e.getSource();
        if (textSource == jTitleText){
          currentPlot.setTitle(jTitleText.getText());
          currentPlot.repaint();
        }
      }
    });
   }
  private void jbInit() throws Exception {
    titledBorder1 = new TitledBorder(BorderFactory.createEmptyBorder(),"");
    border1 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(178, 178, 178));
    titledBorder2 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(178, 178, 178)),"Available Quantities");
    border2 = BorderFactory.createEmptyBorder(1,1,1,1);
    border3 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder3 = new TitledBorder(border3,"Available Quantities");
    border4 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder4 = new TitledBorder(border4,"List of plots");
    border5 = BorderFactory.createLineBorder(new Color(127, 157, 185),2);
    titledBorder5 = new TitledBorder(BorderFactory.createEmptyBorder(),"X axis");
    border6 = BorderFactory.createLineBorder(new Color(127, 157, 185),2);
    titledBorder6 = new TitledBorder(BorderFactory.createEmptyBorder(),"Y axis");
    border7 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder7 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Current plot properties");
    border8 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder8 = new TitledBorder(border8,"Plot Options");
    currentPlot.setLayout(flowLayout1);
    jSplitPane1.setOrientation(JSplitPane.VERTICAL_SPLIT);
    jSplitPane1.setOneTouchExpandable(true);
    jAddPlotButton.setText("Add Plot");
    jAddPlotButton.addActionListener(new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        String xName = (String) jXTextField.getText();
        String yName = (String) jYTextField.getText();
        String envName = xName.substring(0, xName.indexOf(":"));
        SimtkSimEnv simEnv = SimtkDB.getInstance().getSimtkSimEnv(envName);
       // Strip out the leading environment name
        xName = xName.substring(xName.indexOf(":")+1);
        yName = yName.substring(yName.indexOf(":")+1);
        SimtkPlotDataSet newDataSet = new SimtkPlotDataSet(simEnv, xName, yName, jLegendText.getText(), currentPlotIndex);
        // Fix this as indices might not be in sequence due to deletion
        int newDataSetIndex = getNextAvailableIndex();
        newDataSet.setDataSetIndex(newDataSetIndex);
        newDataSet.setPlot(currentPlot);
        jLegendText.setText(newDataSet.getLegend());
        currentPlot.addLegend(newDataSet.getDataSetIndex(), newDataSet.getLegend());
        newDataSet.showPlot();
        plotListModel.add(plotListModel.getSize(), newDataSet.getLegend());
        jPrintPlotButton.setEnabled(true);
        _mapNamesToDatasets.put(newDataSet.getLegend(), newDataSet);
        currentPlot.setTitle(jTitleText.getText());
        currentPlot.repaint();
      }
    });

    jPlotControlPanel.setLayout(borderLayout2);
    jClearPlotButton.setToolTipText("");
    jClearPlotButton.setText("Clear");
    jClearPlotButton.addActionListener(new SimtkPtPlotDialog_jClearPlotButton_actionAdapter(this));
    jPlotList.setBorder(titledBorder1);
    jPlotList.setPreferredSize(new Dimension(180, 100));
    jDeletePlotButton.setText("Delete Plot");
    jDeletePlotButton.addActionListener(new SimtkPtPlotDialog_jDeletePlotButton_actionAdapter(this));
    jPrintPlotButton.setText("Print Plot");
    jPrintPlotButton.addActionListener(new SimtkPtPlotDialog_jPrintPlotButton_actionAdapter(this));
    jPanel1.setLayout(gridBagLayout2);
    jPanel1.setMaximumSize(new Dimension(32767, 32767));
    jPanel1.setMinimumSize(new Dimension(223, 300));
    jPanel1.setPreferredSize(new Dimension(360, 300));
    jScrollPane1.setBorder(titledBorder4);
    jScrollPane1.setMaximumSize(new Dimension(100, 200));
    jScrollPane1.setMinimumSize(new Dimension(33, 48));
    jScrollPane1.setPreferredSize(new Dimension(100, 200));
    jPanel2.setBorder(titledBorder7);
    jPanel2.setMinimumSize(new Dimension(180, 100));
    jPanel2.setPreferredSize(new Dimension(180, 100));
    jPanel2.setToolTipText("");
    jPanel2.setLayout(gridBagLayout1);
    jPlotControlPanel.setMinimumSize(new Dimension(360, 200));
    jPlotControlPanel.setPreferredSize(new Dimension(360, 200));
    jPlotTitle.setHorizontalAlignment(SwingConstants.RIGHT);
    jPlotTitle.setHorizontalTextPosition(SwingConstants.RIGHT);
    jPlotTitle.setText("Plot-Box Title");
    jTitleText.setText("Plot Title goes here");
    this.setTitle("Plotting");

    SelectXButton.setMaximumSize(new Dimension(73, 23));
    SelectXButton.setMinimumSize(new Dimension(73, 23));
    SelectXButton.setPreferredSize(new Dimension(73, 23));
    SelectXButton.setToolTipText("");
    SelectXButton.setMnemonic('0');
    SelectXButton.setText("X-axis ...");
    SelectXButton.addMouseListener(new SimtkPtPlotDialog_SelectXButton_mouseAdapter(this));
    SelectYButton.setMaximumSize(new Dimension(73, 23));
    SelectYButton.setText("Y-axis...");
    SelectYButton.addMouseListener(new SimtkPtPlotDialog_SelectYButton_mouseAdapter(this));
    jXTextField.setMinimumSize(new Dimension(180, 20));
    jXTextField.setPreferredSize(new Dimension(180, 20));
    jXTextField.setToolTipText("");
    jXTextField.setEditable(false);
    jXTextField.setMargin(new Insets(1, 5, 2, 4));
    jXTextField.setText("");
    jYTextField.setMinimumSize(new Dimension(180, 20));
    jYTextField.setPreferredSize(new Dimension(180, 20));
    jYTextField.setEditable(false);
    jYTextField.setText("");
    jPlotGridPanel.setLayout(gridLayout1);
    jGridPanel.setLayout(gridBagLayout3);
    jGridSizeLabel.setToolTipText("");
    jGridSizeLabel.setText("Grid Layout:");
    jGridPanel.setBorder(new TitledBorder(BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151)),"Grid Control"));
    jSpinnerX.setBorder(BorderFactory.createEtchedBorder());
    jSpinnerX.setEnabled(false);
    jSpinnerY.setBorder(BorderFactory.createEtchedBorder());
    jSpinnerY.setEnabled(false);
    jModifyGrid.setText("Modify");
    jModifyGrid.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jModifyGrid_actionPerformed(e);
      }
    });
    jCurrentPlotLabel.setToolTipText("");
    jCurrentPlotLabel.setText("  Current Plot-Box:");
    jMenu1.setText("Template");
    jMenuItem1.setText("Load...");
    jMenuItem2.setText("save...");
    jMenu2.setText("Report");
    jMenuItem3.setText("html");
    jCurrentPlotComboBox.setEnabled(true);
    jCurrentPlotComboBox.setFont(new java.awt.Font("MS Sans Serif", 0, 11));
    jCurrentPlotComboBox.setForeground(Color.black);
    jCurrentPlotComboBox.setBorder(BorderFactory.createEtchedBorder());
    jCurrentPlotComboBox.setDoubleBuffered(false);
    jCurrentPlotComboBox.setEditable(false);
    jCurrentPlotComboBox.setSelectedIndex(-1);
    jCurrentPlotComboBox.setModel(new DefaultComboBoxModel(plotIndices){
      /**
       * setSelectedItem
       *
       * @param anItem Object
       */
      public void setSelectedItem(Object anItem) {
        super.setSelectedItem(anItem);
        currentPlot = (Plot) plots.get(((Integer)anItem).intValue()-1);
        currentPlotIndex = ((Integer)anItem).intValue()-1;
      }
    });
    jLegendLabel.setToolTipText("");
    jLegendLabel.setHorizontalAlignment(SwingConstants.RIGHT);
    jLegendLabel.setHorizontalTextPosition(SwingConstants.RIGHT);
    jLegendLabel.setText("Legend");
    jLegendText.setText("Legend goes here");
    this.getContentPane().add(jSplitPane1,  BorderLayout.CENTER);
    jSplitPane1.add(jPlotControlPanel, JSplitPane.BOTTOM);
    jPlotCommandsPanel.add(jAddPlotButton, null);
    jPlotCommandsPanel.add(jDeletePlotButton, null);
    jPlotCommandsPanel.add(jClearPlotButton, null);
    jPlotCommandsPanel.add(jPrintPlotButton, null);
    jSplitPane1.add(jPlotGridPanel, JSplitPane.TOP);
    jPlotGridPanel.add(currentPlot, null);
    this.getContentPane().add(jPlotCommandsPanel, BorderLayout.SOUTH);
    jPlotControlPanel.add(jPanel1,  BorderLayout.CENTER);
    jPanel1.add(jScrollPane1,                              new GridBagConstraints(1, 0, 2, 2, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(5, 5, 5, 5), 100, 0));
    jScrollPane1.getViewport().add(jPlotList, null);
    jPanel1.add(jPanel2,   new GridBagConstraints(0, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(5, 5, 5, 5), 0, 0));
    jPanel1.add(jGridPanel,                                      new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(5, 5, 5, 5), 0, 0));
    jGridPanel.add(jGridSizeLabel,     new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(5, 13, 5, 0), 0, 0));
    jGridPanel.add(jSpinnerY,       new GridBagConstraints(2, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jGridPanel.add(jModifyGrid,     new GridBagConstraints(3, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jGridPanel.add(jCurrentPlotLabel,     new GridBagConstraints(5, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jGridPanel.add(jCurrentPlotComboBox,      new GridBagConstraints(6, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(5, 0, 5, 5), 0, 0));
    jGridPanel.add(jSpinnerX,   new GridBagConstraints(1, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jPanel2.add(SelectXButton,           new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(SelectYButton,           new GridBagConstraints(0, 3, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jYTextField,            new GridBagConstraints(1, 3, 2, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jPlotTitle,     new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 5, 0, 0), 0, 0));
    jPanel2.add(jTitleText,  new GridBagConstraints(1, 0, 2, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jLegendLabel,    new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 5, 0, 0), 0, 0));
    jPanel2.add(jXTextField,  new GridBagConstraints(2, 2, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jLegendText,  new GridBagConstraints(2, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    jMenuBar1.add(jMenu1);
    jMenuBar1.add(jMenu2);
    jMenu1.add(jMenuItem1);
    jMenu1.add(jMenuItem2);
    jMenu2.add(jMenuItem3);
    this.setJMenuBar(jMenuBar1);
    jSplitPane1.setDividerLocation(250);

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we) {
              jClearPlotButton_actionPerformed(null);
              we.getWindow().dispose();
        }
    });


  }

  void jClearPlotButton_actionPerformed(ActionEvent e) {
    Enumeration enum = _mapNamesToDatasets.elements();
    while (enum.hasMoreElements()) {
      SimtkPlotDataSet dataSet = (SimtkPlotDataSet) enum.nextElement();
      dataSet.cleanup();
      int index = dataSet.getDataSetIndex();
      currentPlot.removeLegend(index);
      currentPlot.clear(index);
      plotListModel.removeElement(dataSet.getLegend());
    }

    currentPlot.clear(true);
    currentPlot.repaint();
    _mapNamesToDatasets.clear();
  }

  void jAddPlotButton_actionPerformed(ActionEvent e) {

    String xName = (String) jXTextField.getText();
    String yName = (String) jYTextField.getText();
    String envName = xName.substring(0, xName.indexOf(":"));
    SimtkSimEnv simEnv = SimtkDB.getInstance().getSimtkSimEnv(envName);
   // Strip out the leading environment name
    xName = xName.substring(xName.indexOf(":")+1);
    yName = yName.substring(yName.indexOf(":")+1);
    SimtkPlotDataSet newDataSet = new SimtkPlotDataSet(simEnv, xName, yName, jLegendText.getText(), currentPlotIndex);
    // Fix this as indices might not be in sequence due to deletion
    int newDataSetIndex = getNextAvailableIndex();
    newDataSet.setDataSetIndex(newDataSetIndex);
    newDataSet.setPlot(currentPlot);
    jLegendText.setText(newDataSet.getLegend());
    currentPlot.addLegend(newDataSet.getDataSetIndex(), newDataSet.getLegend());
    newDataSet.showPlot();
    plotListModel.add(plotListModel.getSize(), newDataSet.getLegend());
    jPrintPlotButton.setEnabled(true);
    _mapNamesToDatasets.put(newDataSet.getLegend(), newDataSet);
    currentPlot.setTitle(jTitleText.getText());
    currentPlot.repaint();
  }
  public int getNextAvailableIndex()
  {
    int availableIndex=0;
    // None exists
    if (_mapNamesToDatasets.size()==0)
      return availableIndex;

    Enumeration elements = _mapNamesToDatasets.elements();
    int[] usedIndices = new int[_mapNamesToDatasets.size()];
    int i=0;
    while(elements.hasMoreElements()){
      SimtkPlotDataSet dataSet = (SimtkPlotDataSet) elements.nextElement();
      usedIndices[i] = dataSet.getDataSetIndex();
      i++;
    }
    java.util.Arrays.sort(usedIndices);
    if (usedIndices[usedIndices.length-1] == usedIndices.length-1)
      availableIndex = usedIndices.length;
    else {
      for (int j = 0; j < usedIndices.length; j++) {
        if (usedIndices[j] < j) {
          availableIndex = j;
          break;
        }
      }
    }
    return availableIndex;
  }
  void jDeletePlotButton_actionPerformed(ActionEvent e) {
    Object[] selectedForDeletion = jPlotList.getSelectedValues();
    for(int i=0; i < selectedForDeletion.length; i++){
      SimtkPlotDataSet dataSet = (SimtkPlotDataSet) _mapNamesToDatasets.get((String) selectedForDeletion[i]);
      dataSet.cleanup();
      int index = dataSet.getDataSetIndex();
      Plot ownerPlot = (Plot) plots.get(dataSet.getPlotBoxIndex());
      ownerPlot.removeLegend(index);
      ownerPlot.clear(index);
      plotListModel.removeElement((String) selectedForDeletion[i]);
      _mapNamesToDatasets.remove((String) selectedForDeletion[i]);
    }
  }

  void jPrintPlotButton_actionPerformed(ActionEvent e) {
    PrintRequestAttributeSet aset = new HashPrintRequestAttributeSet();
    PrinterJob job = PrinterJob.getPrinterJob();
    job.setPrintable(currentPlot);
    if (job.printDialog(aset)) {
        try {
            job.print(aset);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this,
                    "Printing failed:\n" + ex.toString(),
                    "Print Error", JOptionPane.WARNING_MESSAGE);
        }
    }
  }


  void jUpdatePlotButton_actionPerformed(ActionEvent e) {
    /*plot.setGrid(jCheckBoxGrid.isSelected());
    plot.setImpulses(jCheckBoxStems.isSelected());*/
    currentPlot.setTitle(jTitleText.getText());
    currentPlot.repaint();
  }

  void jCheckBoxGrid_actionPerformed(ActionEvent e) {
  }

  void jCheckBoxStems_actionPerformed(ActionEvent e) {
  }

  void SelectXButton_mouseReleased(MouseEvent e) {
    if(e.isPopupTrigger()) {
        xPopup.show(e.getComponent(),
                         e.getX(), e.getY());
  }
}

void SelectYButton_mouseReleased(MouseEvent e) {
  if(e.isPopupTrigger()) {
      yPopup.show(e.getComponent(),
                       e.getX(), e.getY());
}
}

/*
 * Clear all plots callback
 */
class SimtkPtPlotDialog_jClearPlotButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkPtPlotDialog adaptee;

  SimtkPtPlotDialog_jClearPlotButton_actionAdapter(SimtkPtPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jClearPlotButton_actionPerformed(e);
  }
}
/*
 * Delete plot callback class
 */
class SimtkPtPlotDialog_jDeletePlotButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkPtPlotDialog adaptee;

  SimtkPtPlotDialog_jDeletePlotButton_actionAdapter(SimtkPtPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jDeletePlotButton_actionPerformed(e);
  }
}

/**
 * Print plot callback class
 */
class SimtkPtPlotDialog_jPrintPlotButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkPtPlotDialog adaptee;

  SimtkPtPlotDialog_jPrintPlotButton_actionAdapter(SimtkPtPlotDialog adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jPrintPlotButton_actionPerformed(e);
  }
}

class SimtkPtPlotDialog_SelectXButton_mouseAdapter extends java.awt.event.MouseAdapter {
  SimtkPtPlotDialog adaptee;

  SimtkPtPlotDialog_SelectXButton_mouseAdapter(SimtkPtPlotDialog adaptee) {
    this.adaptee = adaptee;
  }

  public void mouseReleased(MouseEvent e) {
    adaptee.SelectXButton_mouseReleased(e);
  }
}

class SimtkPtPlotDialog_SelectYButton_mouseAdapter extends java.awt.event.MouseAdapter {
  SimtkPtPlotDialog adaptee;

  SimtkPtPlotDialog_SelectYButton_mouseAdapter(SimtkPtPlotDialog adaptee) {
    this.adaptee = adaptee;
  }

  public void mouseReleased(MouseEvent e) {
    adaptee.SelectYButton_mouseReleased(e);
  }
}

  void jModifyGrid_actionPerformed(ActionEvent e) {
    JButton source = (JButton) e.getSource();
    if (source.getText()=="Modify"){
      jSpinnerX.setEnabled(true);
      jSpinnerY.setEnabled(true);
      source.setText("Apply");
    }
    else if (source.getText()=="Apply"){
      jSpinnerX.setEnabled(false);
      jSpinnerY.setEnabled(false);
      source.setText("Modify");
      int desiredRows =((Integer)jSpinnerX.getValue()).intValue();
      int desiredColumns =((Integer)jSpinnerY.getValue()).intValue();
      if (desiredRows*desiredColumns < numPlots){
        // Warn that some plot will be removed.
        for (int i =desiredRows*desiredColumns; i < numPlots; i++){
          Plot nextPlot = (Plot)plots.get(i);
          jPlotGridPanel.remove(nextPlot);
          ((DefaultComboBoxModel)jCurrentPlotComboBox.getModel()).removeElementAt(desiredRows*desiredColumns);
        }
        numPlots = desiredRows*desiredColumns;
        gridLayout1 = new GridLayout(desiredRows, desiredColumns);
        jPlotGridPanel.setLayout(gridLayout1);
      }
      else {
        gridLayout1 = new GridLayout(desiredRows, desiredColumns);
        jPlotGridPanel.setLayout(gridLayout1);
        for (int i = numPlots; i < desiredRows * desiredColumns; i++) {
          Plot newPlot = new Plot();
          jPlotGridPanel.add(newPlot);
          plots.add(newPlot);
          ( (DefaultComboBoxModel) jCurrentPlotComboBox.getModel()).addElement(new
              Integer(i + 1));
          numPlots++;
        }
      }
      jPlotGridPanel.repaint();
    }
  }

}
