package simtkui;

import java.io.File;

import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

import simtkCore.SimtkSimEnv;
import simtkModel.*;
import simtkui.guiUtilities.SimtkJDialog;
import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;

public class SimtkSimulationSetupDlg extends SimtkJDialog {
  JPanel jMainPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jBottomPanel = new JPanel();
  JButton jOkButton = new JButton();
  JPanel jSimulationSetupPanel = new JPanel();

  /** Keep a reference to simulation environment */
  SimtkSimEnv  simenv=null;
  boolean storePStates=false;
  boolean storeStates=false;
  boolean storeControls=false;
  boolean gravityState=false;

  JPanel jControlPanel = new JPanel();
  JLabel tfLabel = new JLabel();
  JTextField jTfValue = new JTextField();
  JLabel tiLabel = new JLabel();
  JTextField jTiValue = new JTextField();
  JButton jCancelButton = new JButton();
  FlowLayout flowLayout2 = new FlowLayout();
  Border border1;
  Border border2;
  TitledBorder titledBorder1;
  Border border3;
  TitledBorder titledBorder2;
  Border border4;
  TitledBorder titledBorder3;
  JPanel jStoragePanel = new JPanel();
  Border border5;
  TitledBorder titledBorder4;
  JPanel jStorageControlPanel = new JPanel();
  JLabel jLabel1 = new JLabel();
  JTextField jTextField1 = new JTextField();
  JLabel jLabel2 = new JLabel();
  JTextField jControlStorageFilename = new JTextField();
  JLabel jLabel3 = new JLabel();
  JTextField jPStateStorageFilename = new JTextField();
  JPanel jStoragePStatePanel = new JPanel();
  JLabel jLabel4 = new JLabel();
  JTextField jTextField4 = new JTextField();
  JLabel jLabel5 = new JLabel();
  JTextField jStateStorageFilename = new JTextField();
  JPanel jStorageStatePanel = new JPanel();
  JTextField jTextField6 = new JTextField();
  Border border6;
  TitledBorder titledBorder5;
  JCheckBox jStorePStatesCheckBox = new JCheckBox();
  JCheckBox jStoreStatesCheckBox = new JCheckBox();
  JLabel jLabel6 = new JLabel();
  JCheckBox jStoreControlsCheckBox = new JCheckBox();
  Border border7;
  TitledBorder titledBorder6;
  GridBagLayout gridBagLayout1 = new GridBagLayout();
  GridBagLayout gridBagLayout2 = new GridBagLayout();
  GridBagLayout gridBagLayout3 = new GridBagLayout();
  Border border8;
  JPanel jStorageDirectoryPanel = new JPanel();
  JLabel jStorageDirLabel = new JLabel();
  JTextField jStorageDirTextField = new JTextField();
  JButton jBrowseStorageDir = new JButton();
  BorderLayout borderLayout2 = new BorderLayout();
  Border border9;
  Border border10;
  Border border11;
  Border border12;
  GridBagLayout gridBagLayout4 = new GridBagLayout();
  GridBagLayout gridBagLayout5 = new GridBagLayout();
  Border border13;
  TitledBorder titledBorder7;
  Border border14;
  Border border15;
  JTabbedPane jTabbedPane1 = new JTabbedPane();
  BorderLayout borderLayout3 = new BorderLayout();
  Border border16;
  TitledBorder titledBorder8;
  JTable jInitialStatesTable = new JTable();
  JPanel jInitializationPanel = new JPanel();
  JPanel jInitialConditionsPanel = new JPanel();
  JPanel jGravityPanel = new JPanel();
  Border border17;
  TitledBorder titledBorder9;
  FlowLayout flowLayout1 = new FlowLayout();
  FlowLayout flowLayout3 = new FlowLayout();
  GridBagLayout gridBagLayout6 = new GridBagLayout();
  JScrollPane jScrollPane1 = new JScrollPane();
  Border border18;
  JTable jGravityTable = new JTable();
  JCheckBox jGravityCheckBox = new JCheckBox();
  JPanel jAnalysisPanel = new JPanel();
  BorderLayout borderLayout4 = new BorderLayout();
  JPanel jPanel1 = new JPanel();
  JButton jCustomizeAnalysisBtn = new JButton();
  JButton jIncludeAnalysisBtn = new JButton();
  JButton jRemoveAnalysisBtn = new JButton();
  JPanel jAnalysisListPanel = new JPanel();
  TitledBorder titledBorder10;
  rdArrayAnalysis analyses;
  JTable jAnalysisTable = new JTable();
  BorderLayout borderLayout5 = new BorderLayout();
  JScrollPane jScrollPane2 = new JScrollPane();
  JTextArea jAnalysisDescriptionTextArea = new JTextArea();

  public SimtkSimulationSetupDlg(SimtkSimEnv simEnvironment) {
    super();
    simenv = simEnvironment;
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
     setDialogValues();
  }

  /**
   * setDialogValues
   */
  private void setDialogValues() {
    // Control Frame
    rdControlSet controlSet = simenv.getControlSet();
    int tiIndex = controlSet.getIndex("ti", 0);
    rdControl tiControl = (tiIndex==-1)?null:controlSet.get("ti");
    double tiValue = 0.0;
    if (tiControl != null) {
      tiValue = tiControl.getControlValue(0.0);
    }
    jTiValue.setText(String.valueOf(tiValue));


    double tfValue=1.0;
    int tfIndex = controlSet.getIndex("tf", 0);
    rdControl tfControl = (tfIndex==-1)?null:simenv.getControlSet().get("tf");
    if (tfControl != null) {
     tfValue = tfControl.getControlValue(0.0);
    }
    jTfValue.setText(String.valueOf(tfValue));

   // Storage frame
   SimtkStoragePreferences currentStoragePrefs = simenv.getStoragePreferences();
   jStorageDirTextField.setText(currentStoragePrefs.getStorageDirectory());
   jStorePStatesCheckBox.setSelected(currentStoragePrefs.getPStatesStore());
   jStoreStatesCheckBox.setSelected(currentStoragePrefs.getStatesStore());
   jStoreControlsCheckBox.setSelected(currentStoragePrefs.getControlsStore());
   jPStateStorageFilename.setText(currentStoragePrefs.getPStatesStorageFile());
   jStateStorageFilename.setText(currentStoragePrefs.getStatesStorageFile());
   jControlStorageFilename.setText(currentStoragePrefs.getControlsStorageFile());

   // InitialStates frame
   int nStates = simenv.getModel().getNY();
   Object[][] tableData = new Object[nStates][2];

   for(int i=0; i < nStates; i++){
     tableData[i][0] = simenv.getModel().getStateName(i);
     tableData[i][1] = String.valueOf(simenv.getModel().getInitialState(i));
   }

   String[] columnNames = new String[]{"State Name", "Initial Value"};
   jInitialStatesTable.setModel(new SimtkArrayTableModel(tableData, columnNames));

   // Gravity frame
   Object[][] gravityTableData = new Object[3][2];
   String[] gravityDirs = new String[]{"X", "Y", "Z"};
   SWIGTYPE_p_double g = Model.new_doubleArray(3);
   simenv.getModel().getGravity(g);
   for(int i=0; i < 3; i++){
     gravityTableData[i][0] = gravityDirs[i];
     gravityTableData[i][1] = String.valueOf(Model.doubleArray_get(g, i));
   }
   Model.free_doubleArray(g);
   String[] gColumnNames = new String[]{"Dir", "Value"};
   jGravityTable.setModel(new SimtkArrayTableModel(gravityTableData, gColumnNames));

   // Analyses is a table with model in rdAnalysisFactory
   suAnalysisFactory analysisFactory = suAnalysisFactory.getInstance(simenv.getModel());

   analyses = analysisFactory.getRegisteredAnalyses();
   Object[][] analysisTableData = new Object[analyses.getSize()][2];
   for (int i=0; i < analyses.getSize(); i++){
     analysisTableData[i][0] = analyses.get(i).getName();
     analysisTableData[i][1] = new Boolean(analyses.get(i).getOn());
   }
   String[] aColumnNames = new String[]{"Name", "Enabled"};
   jAnalysisTable.setModel(new SimtkArrayTableModel(analysisTableData, aColumnNames));
   ListSelectionModel analysisSelectionModel = new DefaultListSelectionModel();
   analysisSelectionModel.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
   jAnalysisTable.setSelectionModel(analysisSelectionModel);
   jAnalysisTable.getSelectionModel().addListSelectionListener(new ListSelectionHandler(analyses, jAnalysisDescriptionTextArea));

  }

   private void jbInit() throws Exception {
    border1 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    border2 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder1 = new TitledBorder(border2,"Simulation Time");
    border3 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder2 = new TitledBorder(border3,"Gravity");
    border4 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder3 = new TitledBorder(border4,"Storage");
    border5 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder4 = new TitledBorder(border5,"Storage");
    border6 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder5 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Model initial conditions");
    border7 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder6 = new TitledBorder(border7,"Storage");
    border8 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    border9 = BorderFactory.createEmptyBorder(10,10,0,10);
    border10 = BorderFactory.createEmptyBorder(10,10,10,10);
    border11 = BorderFactory.createEmptyBorder(10,10,10,10);
    border12 = BorderFactory.createEmptyBorder(10,10,10,10);
    border13 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder7 = new TitledBorder(border13,"Initial States");
    border14 = BorderFactory.createCompoundBorder(BorderFactory.createLineBorder(new Color(127, 157, 185),1),BorderFactory.createEmptyBorder(0,3,0,3));
    border15 = BorderFactory.createBevelBorder(BevelBorder.LOWERED,Color.white,Color.white,new Color(115, 114, 105),new Color(165, 163, 151));
    border16 = BorderFactory.createLineBorder(SystemColor.controlText,1);
    titledBorder8 = new TitledBorder(BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151)),"Initial States");
    border17 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    titledBorder9 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Gravity");
    border18 = BorderFactory.createEmptyBorder();
    titledBorder10 = new TitledBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151)),"Available Analyses");
    jMainPanel.setLayout(borderLayout1);
    jOkButton.setText("OK");
    jOkButton.addActionListener(new SimtkSimulationSetupDlg_jOkButton_actionAdapter(this));
    jSimulationSetupPanel.setLayout(gridBagLayout4);
    jSimulationSetupPanel.setBorder(BorderFactory.createEtchedBorder());
    jSimulationSetupPanel.setMinimumSize(new Dimension(600, 67));
    jSimulationSetupPanel.setPreferredSize(new Dimension(600, 67));
    jSimulationSetupPanel.setToolTipText("");
    jSimulationSetupPanel.setVerifyInputWhenFocusTarget(true);
    jMainPanel.setMinimumSize(new Dimension(500, 300));
    jMainPanel.setPreferredSize(new Dimension(500, 300));
    jControlPanel.setAlignmentX((float) 0.5);
    jControlPanel.setBorder(titledBorder1);
    jControlPanel.setMinimumSize(new Dimension(400, 60));
    jControlPanel.setOpaque(true);
    jControlPanel.setPreferredSize(new Dimension(318, 60));
    jControlPanel.setRequestFocusEnabled(true);
    jControlPanel.setToolTipText("");
    jControlPanel.setLayout(flowLayout2);
    tfLabel.setToolTipText("");
    tfLabel.setDisplayedMnemonic('0');
    tfLabel.setText("   End time (tf): ");
    jTfValue.setMinimumSize(new Dimension(51, 20));
    jTfValue.setPreferredSize(new Dimension(51, 20));
    jTfValue.setText("1.0");
    tiLabel.setToolTipText("");
    tiLabel.setText("Start time (ti): ");
    jTiValue.setMinimumSize(new Dimension(51, 20));
    jTiValue.setPreferredSize(new Dimension(51, 20));
    jTiValue.setToolTipText("Start time");
    jTiValue.setText("0.0");
    this.setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    this.setTitle("Simulation Setup");
    this.getContentPane().setLayout(borderLayout3);
    jCancelButton.setActionCommand("jButton1");
    jCancelButton.setText("Cancel");
    jCancelButton.addActionListener(new SimtkSimulationSetupDlg_jCancelButton_actionAdapter(this));
    jStoragePanel.setBorder(titledBorder4);
    jStoragePanel.setLayout(gridBagLayout5);
    jLabel1.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel1.setText("file name:");
    jTextField1.setToolTipText("");
    jTextField1.setText(".005");
    jLabel2.setToolTipText("");
    jLabel2.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel2.setText("dt: ");
    jControlStorageFilename.setPreferredSize(new Dimension(65, 20));
    jControlStorageFilename.setToolTipText("");
    jControlStorageFilename.setText("controls.sto");
    jLabel3.setRequestFocusEnabled(true);
    jLabel3.setToolTipText("");
    jLabel3.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel3.setText("dt: ");
    jPStateStorageFilename.setToolTipText("");
    jPStateStorageFilename.setText("pstates.sto");
    jLabel4.setToolTipText("");
    jLabel4.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel4.setText("file name:");
    jTextField4.setText(".005");
    jLabel5.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel5.setText("dt: ");
    jStateStorageFilename.setPreferredSize(new Dimension(65, 20));
    jStateStorageFilename.setText("states.sto");
    jTextField6.setToolTipText("");
    jTextField6.setText(".005");
    jStorePStatesCheckBox.setBorder(border8);
    jStorePStatesCheckBox.setMaximumSize(new Dimension(61, 19));
    jStorePStatesCheckBox.setActionCommand("Pstates");
    jStorePStatesCheckBox.setHorizontalAlignment(SwingConstants.LEFT);
    jStorePStatesCheckBox.setHorizontalTextPosition(SwingConstants.TRAILING);
    jStorePStatesCheckBox.setText("P-states");
    jStorePStatesCheckBox.addItemListener(new SimtkSimulationSetupDlg_jStorePStatesCheckBox_itemAdapter(this));
    jStoreStatesCheckBox.setMaximumSize(new Dimension(61, 19));
    jStoreStatesCheckBox.setMinimumSize(new Dimension(61, 19));
    jStoreStatesCheckBox.setPreferredSize(new Dimension(61, 19));
    jStoreStatesCheckBox.setHorizontalAlignment(SwingConstants.LEFT);
    jStoreStatesCheckBox.setText("states");
    jStoreStatesCheckBox.addItemListener(new SimtkSimulationSetupDlg_jStoreStatesCheckBox_itemAdapter(this));
    jLabel6.setHorizontalAlignment(SwingConstants.RIGHT);
    jLabel6.setText("file name:");
    jStoreControlsCheckBox.setMaximumSize(new Dimension(61, 19));
    jStoreControlsCheckBox.setMinimumSize(new Dimension(61, 19));
    jStoreControlsCheckBox.setPreferredSize(new Dimension(61, 19));
    jStoreControlsCheckBox.setText("controls");
    jStoreControlsCheckBox.addItemListener(new SimtkSimulationSetupDlg_jStoreControlsCheckBox_itemAdapter(this));
    jStoragePStatePanel.setLayout(gridBagLayout1);
    jStorageStatePanel.setLayout(gridBagLayout2);
    jStorageControlPanel.setLayout(gridBagLayout3);
    jStorageDirectoryPanel.setLayout(borderLayout2);
    jStorageDirLabel.setToolTipText("");
    jStorageDirLabel.setText("Directory:");
    jStorageDirTextField.setMinimumSize(new Dimension(100, 20));
    jStorageDirTextField.setPreferredSize(new Dimension(100, 20));
    jStorageDirTextField.setText(System.getProperty("user.dir"));
    jBrowseStorageDir.setText("Browse...");
    jBrowseStorageDir.addActionListener(new SimtkSimulationSetupDlg_jBrowseStorageDir_actionAdapter(this));
    jStorageDirectoryPanel.setAlignmentY((float) 0.5);
    jStorageDirectoryPanel.setBorder(border9);
    jStorageDirectoryPanel.setDebugGraphicsOptions(0);
    jStoragePStatePanel.setBorder(border10);
    jStorageStatePanel.setBorder(border11);
    jStorageControlPanel.setBorder(border12);
    jInitialConditionsPanel.setBorder(titledBorder8);
    jInitialConditionsPanel.setMinimumSize(new Dimension(341, 188));
    jInitialConditionsPanel.setPreferredSize(new Dimension(341, 188));
    jInitialConditionsPanel.setLayout(flowLayout3);
    jGravityPanel.setBorder(titledBorder9);
    jGravityPanel.setMinimumSize(new Dimension(341, 100));
    jGravityPanel.setPreferredSize(new Dimension(341, 100));
    jGravityPanel.setLayout(flowLayout1);
    jInitializationPanel.setLayout(gridBagLayout6);
    jScrollPane1.setBorder(border18);
    jScrollPane1.setPreferredSize(new Dimension(300, 150));
    jScrollPane1.setRequestFocusEnabled(true);
    jGravityCheckBox.setEnabled(false);
    jGravityCheckBox.setText("Gravity");
    jGravityCheckBox.addItemListener(new SimtkSimulationSetupDlg_jGravityCheckBox_itemAdapter(this));
    jAnalysisPanel.setLayout(borderLayout4);
    jAnalysisPanel.setDebugGraphicsOptions(0);
    jCustomizeAnalysisBtn.setActionCommand("jButton1");
    jCustomizeAnalysisBtn.setText("Customize");
    jIncludeAnalysisBtn.setText("Add");
    jIncludeAnalysisBtn.addActionListener(new SimtkSimulationSetupDlg_jIncludeAnalysisBtn_actionAdapter(this));
    jRemoveAnalysisBtn.setText("Remove");
    jRemoveAnalysisBtn.addActionListener(new SimtkSimulationSetupDlg_jRemoveAnalysisBtn_actionAdapter(this));
    jAnalysisListPanel.setBorder(titledBorder10);
    jAnalysisListPanel.setLayout(borderLayout5);
    jScrollPane2.setMinimumSize(new Dimension(23, 200));
    jScrollPane2.setPreferredSize(new Dimension(2, 200));
    jScrollPane2.setRequestFocusEnabled(true);
    jAnalysisDescriptionTextArea.setEditable(false);
    jAnalysisDescriptionTextArea.setText("Description");
    jAnalysisTable.setMaximumSize(new Dimension(100, 100));
    jAnalysisTable.setMinimumSize(new Dimension(100, 100));
    jAnalysisTable.setPreferredSize(new Dimension(100, 100));
    jPanel1.add(jIncludeAnalysisBtn, null);
    jPanel1.add(jRemoveAnalysisBtn, null);
    jStorageStatePanel.add(jStoreStatesCheckBox, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 10, 0));
    jStorageStatePanel.add(jLabel6, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 5, 5));
    jStorageStatePanel.add(jStateStorageFilename, new GridBagConstraints(2, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 20, 0));
    jStorageStatePanel.add(jLabel5, new GridBagConstraints(3, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 20, 5));
    jStorageStatePanel.add(jTextField6, new GridBagConstraints(4, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 4), 10, 3));
    jTabbedPane1.add(jAnalysisPanel,  "Analyses");
    jAnalysisPanel.add(jPanel1, BorderLayout.SOUTH);
    jPanel1.add(jCustomizeAnalysisBtn, null);
    jTabbedPane1.add(jInitializationPanel,   "Initialization");
    jInitializationPanel.add(jGravityPanel,  new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(5, 5, 0, 4), 0, 0));
    jGravityPanel.add(jGravityCheckBox, null);
    jGravityPanel.add(jGravityTable, null);
    jInitializationPanel.add(jInitialConditionsPanel,  new GridBagConstraints(0, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 5, 30, 4), 0, 0));
    jInitialConditionsPanel.add(jScrollPane1, null);
    jScrollPane1.getViewport().add(jInitialStatesTable, null);
    jStoragePanel.add(jStorageDirectoryPanel, new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 81, 0));
    jStorageDirectoryPanel.add(jStorageDirLabel, BorderLayout.WEST);
    jStorageDirectoryPanel.add(jStorageDirTextField, BorderLayout.CENTER);
    jStorageDirectoryPanel.add(jBrowseStorageDir, BorderLayout.EAST);
    jStoragePanel.add(jStoragePStatePanel, new GridBagConstraints(0, 1, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 12, 0));
    jStoragePStatePanel.add(jStorePStatesCheckBox, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 11, 1));
    jStoragePStatePanel.add(jLabel4, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 5, 5));
    jStoragePStatePanel.add(jPStateStorageFilename, new GridBagConstraints(2, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 20, 0));
    jStoragePStatePanel.add(jLabel3, new GridBagConstraints(3, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 20, 5));
    jStoragePStatePanel.add(jTextField4, new GridBagConstraints(4, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 4), 10, 0));
    jStoragePanel.add(jStorageControlPanel, new GridBagConstraints(0, 3, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 2, 0), 16, 0));
    jStoragePanel.add(jStorageStatePanel, new GridBagConstraints(0, 2, 1, 1, 1.0, 1.0
            ,GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 13, 0));
    jStorageControlPanel.add(jStoreControlsCheckBox, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 7, 0));
    jStorageControlPanel.add(jLabel1, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 5, 5));
    jStorageControlPanel.add(jControlStorageFilename, new GridBagConstraints(2, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 20, 0));
    jStorageControlPanel.add(jLabel2, new GridBagConstraints(3, 0, 1, 1, 0.0, 0.0
            ,GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 20, 5));
    jStorageControlPanel.add(jTextField1, new GridBagConstraints(4, 0, 1, 1, 1.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 4), 10, 3));
    jSimulationSetupPanel.add(jControlPanel,   new GridBagConstraints(0, 0, 1, 1, 1.0, 0.3
            ,GridBagConstraints.NORTH, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    jControlPanel.add(tiLabel, null);
    jControlPanel.add(jTiValue, null);
    jControlPanel.add(tfLabel, null);
    jControlPanel.add(jTfValue, null);
    jSimulationSetupPanel.add(jStoragePanel,    new GridBagConstraints(0, 1, 1, 1, 1.0, 0.7
            ,GridBagConstraints.SOUTH, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 105, 0), 12, 0));
    this.getContentPane().add(jBottomPanel, BorderLayout.SOUTH);
    jBottomPanel.add(jOkButton, null);
    jBottomPanel.add(jCancelButton, null);
    this.getContentPane().add(jTabbedPane1,  BorderLayout.CENTER);
    jTabbedPane1.add(jMainPanel,  "Simulation Setup");
    jMainPanel.add(jSimulationSetupPanel, BorderLayout.CENTER);
    jAnalysisPanel.add(jAnalysisListPanel, BorderLayout.CENTER);
    jAnalysisListPanel.add(jAnalysisTable,  BorderLayout.CENTER);
    jAnalysisListPanel.add(jScrollPane2,  BorderLayout.SOUTH);
    jScrollPane2.getViewport().add(jAnalysisDescriptionTextArea, null);
    this.setModal(true);
   }

  void jOkButton_actionPerformed(ActionEvent e) {
    // Set values as appropriate
    //rdControl tiControl = simenv.getControlSet().get("ti");
    rdControlSet controlSet = simenv.getControlSet();
    int tiIndex = controlSet.getIndex("ti", 0);
    rdControl tiControl = (tiIndex==-1)?null:controlSet.get("ti");
    double tiValue = 0.0;
    if (tiControl != null) {
       tiControl.setControlValue(0.0, Double.parseDouble(this.jTiValue.getText()));
    }

    int tfIndex = controlSet.getIndex("tf", 0);
    rdControl tfControl = (tfIndex==-1)?null:controlSet.get("tf");
    double tfValue = 1.0;
    if (tfControl != null) {
      tfControl.setControlValue(0.0, Double.parseDouble(this.jTfValue.getText()));
    }
    // Check if any of the storage boxes is checked
    SimtkStoragePreferences newStoragePrefs = new SimtkStoragePreferences();
    // Get checkboxes
    newStoragePrefs.setPStatesStore(storePStates);
    newStoragePrefs.setStatesStore(storeStates);
    newStoragePrefs.setControlsStore(storeControls);
    // Verify that directory is valid
    String storageDir = jStorageDirTextField.getText();
    File dir = new File(storageDir);
    if (dir.exists() && dir.isDirectory()){
      newStoragePrefs.setStorageDirectory(storageDir);
    }
    if (storePStates)
      newStoragePrefs.setPStatesStorageFile(jPStateStorageFilename.getText());
    if (storeStates)
      newStoragePrefs.setStatesStorageFile(jStateStorageFilename.getText());
    if (storeControls)
      newStoragePrefs.setControlsStorageFile(jControlStorageFilename.getText());

    simenv.setStoragePreferences(newStoragePrefs);
    // Initial States
    SWIGTYPE_p_double newInitialStates = Model.new_doubleArray(simenv.getModel().getNY());

    for (int i=0; i < simenv.getModel().getNY(); i++){
      Object obj = jInitialStatesTable.getModel().getValueAt(i, 1);
      double val = Double.parseDouble((String)obj);
      Model.doubleArray_set(newInitialStates, i, val);
    }
    simenv.getModel().setInitialStates(newInitialStates);
    Model.free_doubleArray(newInitialStates);

    // Gravity
    SWIGTYPE_p_double newGravityVector = Model.new_doubleArray(3);

   for (int i=0; i < 3; i++){
     Object obj = jGravityTable.getModel().getValueAt(i, 1);
     double val = Double.parseDouble((String)obj);
     Model.doubleArray_set(newGravityVector, i, val);
   }
   simenv.getModel().setGravity(newGravityVector);
   Model.free_doubleArray(newGravityVector);

   // Analysis
   for (int i=0; i < analyses.getSize(); i++){
     if (analyses.get(i).getOn()){
       simenv.getModel().addAnalysis(analyses.get(i));
     }
   }

    this.dispose();
  }


  void jCancelButton_actionPerformed(ActionEvent e) {
    dispose();
  }

  void jStorePStatesCheckBox_itemStateChanged(ItemEvent e) {
    storePStates = (e.getStateChange() == ItemEvent.SELECTED);
  }

  void jStoreStatesCheckBox_itemStateChanged(ItemEvent e) {
    storeStates= (e.getStateChange() == ItemEvent.SELECTED);
  }

  void jStoreControlsCheckBox_itemStateChanged(ItemEvent e) {
    storeControls = (e.getStateChange() == ItemEvent.SELECTED);
  }

  void jBrowseStorageDir_actionPerformed(ActionEvent e) {
    // Show directory browse dialog
    JFileChooser jFileChooser1 = new JFileChooser();
    jFileChooser1.setDialogTitle("Browse for directory to save storage files");
    jFileChooser1.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    jFileChooser1.setVisible(true);

    if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) ==
        JFileChooser.APPROVE_OPTION){
      jStorageDirTextField.setText(jFileChooser1.getSelectedFile().getAbsolutePath());
    }
  }

  void jGravityCheckBox_itemStateChanged(ItemEvent e) {
    gravityState = (e.getStateChange() == ItemEvent.SELECTED);
  }


  class ListSelectionHandler implements ListSelectionListener {
    rdArrayAnalysis   analyses;
    JTextArea         descriptionArea;
    int               selectedIndex;

    public ListSelectionHandler(rdArrayAnalysis analyses, JTextArea descriptionArea)
    {
      this.analyses = analyses;
      this.descriptionArea = descriptionArea;
    }
      public void valueChanged(ListSelectionEvent e) {
        if (!e.getValueIsAdjusting()){
          selectedIndex = e.getFirstIndex();
          rdAnalysis currentAnalysis = analyses.get(selectedIndex);
          descriptionArea.setText(currentAnalysis.getDescription());
        }
      }
      public int getSelectedIndex()
      {
        return selectedIndex;
      }
  }

  void jIncludeAnalysisBtn_actionPerformed(ActionEvent e) {
    analyses.get(jAnalysisTable.getSelectedRow()).setOn(true);
    jAnalysisTable.setValueAt(new Boolean(true), jAnalysisTable.getSelectedRow(), 1);
  }

  void jRemoveAnalysisBtn_actionPerformed(ActionEvent e) {
    analyses.get(jAnalysisTable.getSelectedRow()).setOn(false);
    jAnalysisTable.setValueAt(new Boolean(false), jAnalysisTable.getSelectedRow(), 1);
  }

}

class SimtkSimulationSetupDlg_jOkButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jOkButton_actionAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jOkButton_actionPerformed(e);
  }
}

class SimtkSimulationSetupDlg_jCancelButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jCancelButton_actionAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jCancelButton_actionPerformed(e);
  }
}

class SimtkSimulationSetupDlg_jStorePStatesCheckBox_itemAdapter implements java.awt.event.ItemListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jStorePStatesCheckBox_itemAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void itemStateChanged(ItemEvent e) {
    adaptee.jStorePStatesCheckBox_itemStateChanged(e);
  }
}

class SimtkSimulationSetupDlg_jStoreStatesCheckBox_itemAdapter implements java.awt.event.ItemListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jStoreStatesCheckBox_itemAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void itemStateChanged(ItemEvent e) {
    adaptee.jStoreStatesCheckBox_itemStateChanged(e);
  }
}

class SimtkSimulationSetupDlg_jStoreControlsCheckBox_itemAdapter implements java.awt.event.ItemListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jStoreControlsCheckBox_itemAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void itemStateChanged(ItemEvent e) {
    adaptee.jStoreControlsCheckBox_itemStateChanged(e);
  }
}

class SimtkSimulationSetupDlg_jBrowseStorageDir_actionAdapter implements java.awt.event.ActionListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jBrowseStorageDir_actionAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jBrowseStorageDir_actionPerformed(e);
  }
}

class SimtkSimulationSetupDlg_jGravityCheckBox_itemAdapter implements java.awt.event.ItemListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jGravityCheckBox_itemAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void itemStateChanged(ItemEvent e) {
    adaptee.jGravityCheckBox_itemStateChanged(e);
  }
}

class SimtkSimulationSetupDlg_jIncludeAnalysisBtn_actionAdapter implements java.awt.event.ActionListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jIncludeAnalysisBtn_actionAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jIncludeAnalysisBtn_actionPerformed(e);
  }
}

class SimtkSimulationSetupDlg_jRemoveAnalysisBtn_actionAdapter implements java.awt.event.ActionListener {
  SimtkSimulationSetupDlg adaptee;

  SimtkSimulationSetupDlg_jRemoveAnalysisBtn_actionAdapter(SimtkSimulationSetupDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jRemoveAnalysisBtn_actionPerformed(e);
  }
}
