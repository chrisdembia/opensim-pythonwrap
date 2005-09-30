package simtkView.plot;

import java.io.*;
import java.net.*;
import java.util.*;
import javax.print.attribute.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;

import com.microstar.xml.*;
import simtkCore.*;
import simtkUtils.*;

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
public class SimtkPtPlotDialog extends JDialog{
  Vector figures = new Vector(); // The plot box with all plotting capabilities
  Vector plotIndices = new Vector(); // The plot box with all plotting capabilities
  int  currentFigureIndex = 0;
  NmblFigure currentFigure = new NmblFigure("Figure 1");
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
  JPanel jCurrentFigurePanel = new JPanel();
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
  int numFigures = 1;
  JLabel jCurrentPlotLabel = new JLabel();
  JComboBox jCurrentPlotComboBox = new JComboBox();
  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu jMenu1 = new JMenu();
  JMenuItem jLoadTemplateMenuItem = new JMenuItem();
  JMenuItem jSaveTemplateMenuItem = new JMenuItem();
  GridBagLayout gridBagLayout3 = new GridBagLayout();
  JTextField jLegendText = new JTextField();
  NmblPlotTemplateXMLParser _parser;
  JLabel jXLabel = new JLabel();
  JLabel jYLabel = new JLabel();
  JTextField jXLabelValue = new JTextField();
  JTextField jYLabelValue = new JTextField();
  JPanel jPanel2 = new JPanel();
  GridBagLayout gridBagLayout4 = new GridBagLayout();
  Border border9;
  TitledBorder titledBorder9;
  JLabel jLegendLabel = new JLabel();
  JLabel jLabelLegend = new JLabel();
  JLabel jLabel1 = new JLabel();
  JButton jApplyTitleChangesButton = new JButton();

  public SimtkPtPlotDialog() {
    plotIndices.add(new Integer("1"));
    figures.add(currentFigure);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    currentFigure.clear(true);
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
    jCheckBoxStems.setSelected(plot.getImpulses());
    jTitleText.addFocusListener(new textFieldsFocusListener());
    jXLabelValue.addFocusListener(new textFieldsFocusListener());
    jYLabelValue.addFocusListener(new textFieldsFocusListener());*/
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
    titledBorder7 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Current Figure");
    border8 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder8 = new TitledBorder(border8,"Plot Options");
    border9 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder9 = new TitledBorder(border9,"Current plot");
    currentFigure.setLayout(flowLayout1);
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
        String userLegend = jLegendText.getText();
        addDataSet(currentFigureIndex, xName, yName, userLegend);
        jLegendText.setText(SimtkPlotDataSet.DEFAULT_LEGEND);
        currentFigure.setTitle(jTitleText.getText());
        currentFigure.setXLabel(jXLabelValue.getText());
        currentFigure.setYLabel(jYLabelValue.getText());
        currentFigure.repaint();
      }
    });

    jPlotControlPanel.setLayout(borderLayout2);
    jClearPlotButton.setToolTipText("");
    jClearPlotButton.setText("Clear");
    jClearPlotButton.addActionListener(new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        Enumeration enum = _mapNamesToDatasets.elements();
        while (enum.hasMoreElements()) {
          SimtkPlotDataSet dataSet = (SimtkPlotDataSet) enum.nextElement();
          if (dataSet.getFigureIndex()!= currentFigureIndex)
            continue;
          dataSet.cleanup();
          int index = dataSet.getDataSetIndex();
          currentFigure.removeLegend(index);
          currentFigure.clear(index);
          plotListModel.removeElement(dataSet.Encode());
          _mapNamesToDatasets.remove(dataSet.Encode());
        }
        currentFigure.clear(true);
        currentFigure.repaint();
      }
    });

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
    jCurrentFigurePanel.setBorder(new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Current Figure"));
    jCurrentFigurePanel.setMinimumSize(new Dimension(180, 100));
    jCurrentFigurePanel.setPreferredSize(new Dimension(180, 100));
    jCurrentFigurePanel.setToolTipText("");
    jCurrentFigurePanel.setLayout(gridBagLayout1);
    jPlotControlPanel.setMinimumSize(new Dimension(360, 200));
    jPlotControlPanel.setPreferredSize(new Dimension(360, 200));
    jPlotTitle.setHorizontalAlignment(SwingConstants.RIGHT);
    jPlotTitle.setHorizontalTextPosition(SwingConstants.RIGHT);
    jPlotTitle.setText("Figure Title");
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
    jGridPanel.setPreferredSize(new Dimension(211, 60));
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
    jCurrentPlotLabel.setText("  Current Figure:");
    jMenu1.setText("Template");
    jLoadTemplateMenuItem.setText("Load...");
    jLoadTemplateMenuItem.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jLoadTemplateMenuItem_actionPerformed(e);
      }
    });
    jSaveTemplateMenuItem.setText("save...");
    jSaveTemplateMenuItem.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jSaveTemplateMenuItem_actionPerformed(e);
      }
    });
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
        setCurrentFigure(((Integer)anItem).intValue()-1);
      }
    });
    jLegendText.setText(SimtkPlotDataSet.DEFAULT_LEGEND);
    flowLayout1.setAlignment(FlowLayout.LEFT);
    jXLabel.setText("X-Label");
    jYLabel.setText("Y-Label");
    jXLabelValue.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jXLabelValue_actionPerformed(e);
      }
    });
    jXLabelValue.setToolTipText("");
    jXLabelValue.setText("X-Label");
    jYLabelValue.setText("Y-Label");
    jPanel2.setLayout(gridBagLayout4);
    jPanel2.setBorder(new TitledBorder(BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151)),"Current Pllot"));
    jLabel1.setText("Legend");
    jApplyTitleChangesButton.setText("Update");
    jApplyTitleChangesButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jApplyFigTitleChanges_actionPerformed(e);
      }
    });
    this.getContentPane().add(jSplitPane1,  BorderLayout.CENTER);
    jSplitPane1.add(jPlotControlPanel, JSplitPane.BOTTOM);
    jPlotCommandsPanel.add(jCurrentPlotLabel, null);
    jPlotCommandsPanel.add(jCurrentPlotComboBox, null);
    jPlotCommandsPanel.add(jAddPlotButton, null);
    jPlotCommandsPanel.add(jDeletePlotButton, null);
    jPlotCommandsPanel.add(jClearPlotButton, null);
    jPlotCommandsPanel.add(jPrintPlotButton, null);
    jSplitPane1.add(jPlotGridPanel, JSplitPane.TOP);
    jPlotGridPanel.add(currentFigure, null);
    this.getContentPane().add(jPlotCommandsPanel, BorderLayout.SOUTH);
    jPlotControlPanel.add(jPanel1,  BorderLayout.CENTER);
    jPanel1.add(jScrollPane1,                               new GridBagConstraints(1, 0, 2, 3, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(5, 5, 5, 5), 100, 0));
    jScrollPane1.getViewport().add(jPlotList, null);
    jPanel1.add(jCurrentFigurePanel,        new GridBagConstraints(0, 1, 1, 1, 1.0, 0.7
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(5, 5, 0, 5), 0, 0));
    jPanel1.add(jGridPanel,                                                   new GridBagConstraints(0, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.NORTHWEST, GridBagConstraints.HORIZONTAL, new Insets(5, 5, 5, 5), 0, 0));
    jGridPanel.add(jGridSizeLabel,     new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(5, 13, 5, 0), 0, 0));
    jGridPanel.add(jSpinnerY,       new GridBagConstraints(2, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jGridPanel.add(jModifyGrid,     new GridBagConstraints(3, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jGridPanel.add(jSpinnerX,   new GridBagConstraints(1, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));
    jPanel1.add(jPanel2,   new GridBagConstraints(0, 2, 1, 1, 1.0, 0.7
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(5, 5, 5, 5), 0, 0));
    jPanel2.add(jLegendText,                  new GridBagConstraints(1, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(SelectXButton,         new GridBagConstraints(0, 1, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(SelectYButton,          new GridBagConstraints(0, 2, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jXTextField,     new GridBagConstraints(1, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jYTextField,      new GridBagConstraints(1, 2, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
    jPanel2.add(jLabel1,   new GridBagConstraints(0, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 5, 0, 0), 0, 0));
    jCurrentFigurePanel.add(jPlotTitle,                           new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 5, 0, 0), 0, 0));
    jCurrentFigurePanel.add(jTitleText,                      new GridBagConstraints(1, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 150, 0));
    jCurrentFigurePanel.add(jYLabel,                new GridBagConstraints(0, 2, 1, 1, 1.0, 1.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 5, 0, 0), 0, 0));
    jCurrentFigurePanel.add(jXLabelValue,            new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 150, 0));
    jCurrentFigurePanel.add(jYLabelValue,       new GridBagConstraints(1, 2, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 150, 0));
    jCurrentFigurePanel.add(jXLabel,               new GridBagConstraints(0, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 5, 0, 0), 0, 0));
    jCurrentFigurePanel.add(jApplyTitleChangesButton,     new GridBagConstraints(2, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
    jMenuBar1.add(jMenu1);
    jMenu1.add(jLoadTemplateMenuItem);
    jMenu1.add(jSaveTemplateMenuItem);
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
  }

  public int getNextAvailableIndex(int figureIndex)
  {
    int availableIndex=0;
    // None exists
    if (_mapNamesToDatasets.size()==0)
      return availableIndex;

    Enumeration elements = _mapNamesToDatasets.elements();
    int[] usedIndices = new int[_mapNamesToDatasets.size()];
    int plotsInCurrentFigure=0;
    while(elements.hasMoreElements()){
      SimtkPlotDataSet dataSet = (SimtkPlotDataSet) elements.nextElement();
      if (figureIndex != dataSet.getFigureIndex())
        continue;
      usedIndices[plotsInCurrentFigure] = dataSet.getDataSetIndex();
      plotsInCurrentFigure++;
    }
    if (plotsInCurrentFigure==0)
      return 0;

    java.util.Arrays.sort(usedIndices, 0, plotsInCurrentFigure);

    if (usedIndices[plotsInCurrentFigure-1] == plotsInCurrentFigure-1)
      availableIndex = plotsInCurrentFigure;
    else {
      for (int j = 0; j < plotsInCurrentFigure; j++) {
        if (usedIndices[j] != j) {
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
      NmblFigure ownerPlot = (NmblFigure) figures.get(dataSet.getFigureIndex());
      ownerPlot.removeLegend(index);
      ownerPlot.clear(index);
      plotListModel.removeElement((String) selectedForDeletion[i]);
      _mapNamesToDatasets.remove((String) selectedForDeletion[i]);
    }
  }

  void jPrintPlotButton_actionPerformed(ActionEvent e) {
    PrintRequestAttributeSet aset = new HashPrintRequestAttributeSet();
    PrinterJob job = PrinterJob.getPrinterJob();
    job.setPrintable(currentFigure);
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
    currentFigure.setTitle(jTitleText.getText());
    currentFigure.repaint();
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
      setGridSize(desiredRows, desiredColumns);
      jPlotGridPanel.repaint();
    }
  }

  /**
   * Check if a legend exists already in the same figure
   * @param aLegend String
   * @param figure NmblFigure
   * @return boolean
   */
  public boolean legendExists(String aLegend, NmblFigure figure)
  {
    return (figure.getLegendDataset(aLegend)!= -1);
  }

  public NmblFigure getFigure(int onebasedIndex)
  {
    return (NmblFigure) figures.get(onebasedIndex-1);
  }

  /**
   * Save current configuration of plots into a template file
   * @param e ActionEvent
   */
  void jSaveTemplateMenuItem_actionPerformed(ActionEvent e) {
    try {
      String fileName = SimtkFileChooser.getFile("Select file to save template to", "xml", "*.xml");
      if (fileName == null)
        return;
      fileName = fileName+".xml";
        OutputStream fout = new FileOutputStream(fileName);
        write(new OutputStreamWriter(fout));
    } catch (IOException ex) {
        JOptionPane.showMessageDialog(this,
                "Error writing file:\n" + ex.toString(),
                "NMBL Plotting Error", JOptionPane.WARNING_MESSAGE);
    }
  }

  public synchronized void write(Writer out) {
      // Auto-flush is disabled.
      PrintWriter output = new PrintWriter(new BufferedWriter(out), false);
      try {
        writeHeader(output);
        writeFigures(output);
        writeFooter(output);
        output.flush();
     }
     catch (IOException ex) {
     }
   }

  /**
   * writeFooter
   *
   * @param fout FileOutputStream
   */
  private void writeFooter(PrintWriter fout) throws IOException {
    fout.println("</nmblPlotTemplate>");
  }

  /**
   * writeFigures
   *
   * @param fout FileOutputStream
   */
  private void writeFigures(PrintWriter fout) throws IOException  {
    fout.println("\t<Grid rows=\""
                 +gridLayout1.getRows()+
                 "\" columns=\""
                 +gridLayout1.getColumns()+
                 "\" />");
    for (int i=0; i < numFigures; i++){
      NmblFigure nextFigure = (NmblFigure) figures.get(i);
      fout.println("\t\t<Figure id=\""+(i+1)+"\" title=\""+nextFigure.getTitle()+"\">");
      fout.println("\t\t<grid value=\""+nextFigure.getGrid()+"\"/>");
      fout.println("\t\t<xLabel>"+nextFigure.getXLabel()+"</xLabel>");
      fout.println("\t\t<yLabel>"+nextFigure.getYLabel()+"</yLabel>");
      fout.println("\t\t<xRange min=\""+nextFigure.getXRange()[0] +"\" max=\""+nextFigure.getXRange()[1] +"\"/>");
      fout.println("\t\t<yRange min=\""+nextFigure.getYRange()[0] +"\" max=\""+nextFigure.getYRange()[1] +"\"/>");
      fout.println("\t\t<plots>");
      Enumeration dataSets=_mapNamesToDatasets.elements();
      // Traverse the list of all datasets and write them, each will reference a figure by its id
      while (dataSets.hasMoreElements()){
        SimtkPlotDataSet nextPlot = (SimtkPlotDataSet) dataSets.nextElement();
        if (nextPlot.getFigureIndex()!= i)
          continue;
        nextPlot.write(fout);
      }
      fout.println("\t\t</plots>");
      fout.println("\t\t</Figure>");
    }

  }

  /**
   * writeHeader
   *
   * @param fout FileOutputStream
   */
  private void writeHeader(PrintWriter fout)  throws IOException {
    fout.println("<?xml version=\"1.0\" standalone=\"yes\"?>");
    fout.println("<nmblPlotTemplate version=\"0.1\">");
    //fout.println("\t<title value=\"Plot Template\"/>");
  }

  void jLoadTemplateMenuItem_actionPerformed(ActionEvent e) {
    try {
      String fileName = SimtkFileChooser.getFile("Select template file to load", "xml", "*.xml");
      File templateFileFullPath = new File(fileName);
      if (fileName == null)
        return;
         read(new URL("file", null, templateFileFullPath.getParent()),
             new FileInputStream(templateFileFullPath.getName()));
    }
    catch (FileNotFoundException ex) {
    }
    catch (MalformedURLException ex) {
    }
    catch (IOException ex1) {
    }
  }

  /**
   * read
   *
   * @param uRL URL
   * @param fileInputStream FileInputStream
   */
  private void read(URL base, FileInputStream in) throws IOException {
    BufferedInputStream bin = new BufferedInputStream(in);
    // Peek at the file...
    bin.mark(9);
    // Read 8 bytes in case 16-bit encoding is being used.
    byte[] peek = new byte[8];
    bin.read(peek);
    bin.reset();
    if ((new String(peek)).startsWith("<?xm")) {
        // file is an XML file.
        _parser = new NmblPlotTemplateXMLParser(this);
        try {
            _parser.parse(base, bin);
        } catch (Exception ex) {
            String msg;
            if (ex instanceof XmlException) {
                XmlException xmlex = (XmlException)ex;
                msg =
                    "NMBL Application: failed to parse template file:\n"
                    + "line: " + xmlex.getLine()
                    + ", column: " + xmlex.getColumn()
                    + "\nIn entity: " + xmlex.getSystemId()
                    + "\n";
            } else {
                msg = "Failed to parse template file\n";
            }
            System.err.println(msg + ex.toString());
            ex.printStackTrace();
        }
    }
  }

  /**
   * setGridSize
   *
   * @param rows int
   * @param columns int
   */
  public void setGridSize(int desiredRows, int desiredColumns) {
    if (desiredRows*desiredColumns < numFigures){
      // Warn that some plot will be removed.

      for (int i =desiredRows*desiredColumns; i < numFigures; i++){
        NmblFigure nextPlot = (NmblFigure)figures.get(i);
        jPlotGridPanel.remove(nextPlot);
        ((DefaultComboBoxModel)jCurrentPlotComboBox.getModel()).removeElementAt(desiredRows*desiredColumns);
      }
      numFigures = desiredRows*desiredColumns;
      gridLayout1 = new GridLayout(desiredRows, desiredColumns);
      jPlotGridPanel.setLayout(gridLayout1);
    }
    else {
      gridLayout1 = new GridLayout(desiredRows, desiredColumns);
      jPlotGridPanel.setLayout(gridLayout1);
      for (int i = numFigures; i < desiredRows * desiredColumns; i++) {
        NmblFigure newPlot = new NmblFigure("Figure:"+(i+1));
        jPlotGridPanel.add(newPlot);
        figures.add(newPlot);
        ( (DefaultComboBoxModel) jCurrentPlotComboBox.getModel()).addElement(new
            Integer(i + 1));
        numFigures++;
      }
    }
  }

  void jXLabelValue_actionPerformed(ActionEvent e) {

  }

  /**
   * addDataSet
   *
   * @param currentFigureId int
   * @param qtyXName String
   * @param qtyYName String
   * @param legend String
   */
  public void addDataSet(int zeroBasedCurrentFigureId, String xName, String yName,
                         String userLegend) {
    /**
     * FIXME: find a general mechanism for handling SimEnv by querying the user for what env. to use.
     */
    SimtkSimEnv simEnv = SimtkDB.getInstance().getSimtkSimEnv("SimEnv1");
    if (simEnv==null){
      simtkui.SimtkApp.displayWarningMessage("No Simulation environment SimEnv1 to bind template.");
      return;
    }
    int saveCurrentFigureIndex = currentFigureIndex;
    currentFigureIndex = zeroBasedCurrentFigureId;
   SimtkPlotDataSet newDataSet = new SimtkPlotDataSet(simEnv, xName, yName, userLegend, currentFigureIndex);
   currentFigure = (NmblFigure) figures.get(currentFigureIndex);
   if (legendExists(newDataSet.getLegend(), currentFigure)){
     JOptionPane.showMessageDialog(SimtkPtPlotDialog.this,
     "Legend "+newDataSet.getLegend()+" is already in use in current Figure, please change it and retry",
     "NMBL Error", JOptionPane.WARNING_MESSAGE);
     // Restore current figure set from the UI so that it is consistent with the dialog
     currentFigureIndex = saveCurrentFigureIndex;
     currentFigure = (NmblFigure) figures.get(currentFigureIndex);
     return;
   }
   // Fix this as indices might not be in sequence due to deletion
   int newDataSetIndex = getNextAvailableIndex(currentFigureIndex);
   newDataSet.setDataSetIndex(newDataSetIndex);
   newDataSet.setPlot(currentFigure);
   //jLegendText.setText(newDataSet.getLegend());
   currentFigure.addLegend(newDataSet.getDataSetIndex(), newDataSet.getLegend());
   newDataSet.showPlot();
   plotListModel.add(plotListModel.getSize(), newDataSet.Encode());
   jPrintPlotButton.setEnabled(true);
   _mapNamesToDatasets.put(newDataSet.Encode(), newDataSet);
   // Restore current figure set from the UI so that it is consistent with the dialog
   currentFigureIndex = saveCurrentFigureIndex;
   currentFigure = (NmblFigure) figures.get(currentFigureIndex);
 }

  private void setCurrentFigure(int zeroBasedIndex)
  {
    currentFigure = (NmblFigure) figures.get(zeroBasedIndex);
    currentFigureIndex = zeroBasedIndex;
    jTitleText.setText(currentFigure.getTitle());
    jXLabelValue.setText(currentFigure.getXLabel());
    jYLabelValue.setText(currentFigure.getYLabel());
  }

  public void updateUIWithCurrentFigure()
  {
    setCurrentFigure(currentFigureIndex);
  }
  /**
   * Class to handle text fields modifications
   * <p>Title: UI for Simtk Prototype</p>
   * <p>Description: UI for Simtk Prototype</p>
   * <p>Copyright: Copyright (c) 2004</p>
   * <p>Company: Stanford University</p>
   * @author not attributable
   * @version 1.0
   */
  private class textFieldsFocusListener implements FocusListener
  {
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
          currentFigure.setTitle(jTitleText.getText());
        }
        else if (textSource == jXLabelValue){
          currentFigure.setXLabel(jXLabelValue.getText());
        }
        else if (textSource == jYLabelValue){
          currentFigure.setYLabel(jYLabelValue.getText());
        }
        currentFigure.repaint();
      }
    }

  void jApplyFigTitleChanges_actionPerformed(ActionEvent e) {
    currentFigure.setTitle(jTitleText.getText());
    currentFigure.setXLabel(jXLabelValue.getText());
    currentFigure.setYLabel(jYLabelValue.getText());
    updateUIWithCurrentFigure();
    currentFigure.repaint();
  }

}
