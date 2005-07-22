package simtkui;

import java.awt.AWTEvent;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Point;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.WindowEvent;
import java.util.Observable;
import java.util.Observer;

import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import javax.swing.text.PlainDocument;

//import org.jpf.toolbox.Boot;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.ExecutionManager;
import simtkCommands.SimtkCommand;
import simtkCore.SimtkDB;
import simtkCore.SimtkDBTreeModel;
import simtkCore.SimtkSimEnv;
import simtkView.SimtkMdlTree;
import simtkView.SimtkViewDB;
import simtkui.guiUtilities.SimtkJMenuFactory;
import simtkuiEvents.SimtkCloseModelEvent;
import simtkuiEvents.SimtkNewModelEvent;
import simtkuiEvents.SimtkNewSimEnvEvent;
import simtkuiEvents.SimtkSimulationEvent;
import simtkuiEvents.SimtkUpdateTreeEvent;
import simtkCommands.*;
import javax.swing.*;
/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */

public class SimtkMainFrame extends JFrame implements Observer {
//  JPanel contentPane;
  // MenuBar
  JMenuBar jMenuBar1 = SimtkJMenuFactory.createTopMenuBar();
  // Top level menus
  //-------- File ---------------
  JMenu jMenuFile = SimtkJMenuFactory.createMenu("File");
  // File Submenus
  JMenuItem jModelByNameMenuItem = new JMenuItem();
  JMenuItem jModelBrowseMenuItem = new JMenuItem();
  JMenuItem jSaveModelMenuItem = new JMenuItem();
  JMenuItem jMenuFileExit = new JMenuItem();

  //-------- Window -------------
  JMenu jMenuWindow = new JMenu();
  //-------- Scripting ----------
  JMenu jMenuScript = new JMenu();
  JMenuItem jMenuLoadScript = new JMenuItem();
  JCheckBoxMenuItem jCheckToggleSingleStep = new JCheckBoxMenuItem();
  //-------- Plot ---------------
  JMenu jMenuPlot = SimtkJMenuFactory.createMenu("Plot");
  //-------- Help ---------------
  JMenu jMenuHelp = new JMenu();
  // Help Submenus
  JMenuItem jMenuHelpAbout = new JMenuItem();

  // ToolBar
  JToolBar jToolBar = new JToolBar();
  JButton jOpenModelButton = new JButton();
  JButton jCloseModelButton = new JButton();
  JButton jHelpButton = new JButton();
  JButton jSnapShotButton = new JButton();

  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  ImageIcon image4;
  ImageIcon image5;
  ImageIcon image6;

  // Status Bar
  JLabel statusBar = new JLabel();
  BorderLayout borderLayout1 = new BorderLayout();
  JSplitPane jSplitPane1 = new JSplitPane();
  JSplitPane jSplitPane2 = new JSplitPane();

  SimtkDB simtkDB = SimtkDB.getInstance();
  ExecutionManager execManager = new ExecutionManager();
  MDIDesktopPane modelDesktopPane = new MDIDesktopPane();

  SimtkMdlTree jSimDBTree = new SimtkMdlTree();
  JScrollPane jMainPane = new JScrollPane();
  JTabbedPane jBottomPane = new JTabbedPane();
  JScrollPane jMessagePane = new JScrollPane();
  JTextArea jMessageArea = new JTextArea();
  BorderLayout borderLayout2 = new BorderLayout();
  JMenu jTestMenu = SimtkJMenuFactory.createMenu("Test");
  JMenuItem jTestMenuItem = new JMenuItem();
  JMenu jPluginsMenu = SimtkJMenuFactory.createMenu("Plugins");
  JMenuItem jInvokePluginMgr = new JMenuItem();
  JButton jUndoButton = new JButton();
  JButton jRedoButton = new JButton();
  JMenuItem jNewEnvMenuItem = new JMenuItem();
  JMenuItem jFlushScriptMenuitem = new JMenuItem();

  SimtkCommand _undoCommand = null;
  SimtkCommand _redoCommand = null;
  JScrollPane jLogPane = new JScrollPane();
  JScrollPane jShellPane = new JScrollPane();
  SimtkShellTextArea jShellArea = new SimtkShellTextArea();
  JTextArea jLogTextArea = new JTextArea();
  Border border1;
  JMenuItem jactivateAll = new JMenuItem();
  JMenuItem jWorkflowMenuitem = new JMenuItem();
  JMenuItem jPlotMenuitem = new JMenuItem();
  Border border2;
  JScrollPane jModelTreeScroll = new JScrollPane();
  JTree jTree1 = new JTree();
  //Construct the frame
  public SimtkMainFrame() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);

    try {
      // The following needs to be set here rather than at the caller SimtkApp since subsequent
      // calls
      SimtkApp.setTopComponent(this);
      SimtkApp.setMessageArea(jMessageArea);
      SimtkApp.setLogArea(jLogTextArea);
      jMessagePane.add(jLogTextArea);
      modelDesktopPane.setDragMode(JDesktopPane.OUTLINE_DRAG_MODE);
      SimtkApp.setModelDesktopPane(modelDesktopPane);
      // Initialize the database
      simtkDB.addObserver(this);
      simtkDB.addObserver(new SimtkViewDB());
      jbInit();
      SimtkApp.setStatusBar(statusBar);
      jSimDBTree.initialize();
      jSimDBTree.addCustomCommands();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  /**
   * jbInit is the default method generated by JBuilder to intialize GUI
   * components. We use it to instialize/assign commands to menu items and
   * toolbar buttons shown on main menu.
   *
   *
   * @throws Exception
   */
  private void jbInit() throws Exception {
    image1 = new ImageIcon(simtkui.SimtkApp.class.getResource(
        "openFile.png"));
    image2 = new ImageIcon(simtkui.SimtkApp.class.getResource(
        "closeFile.png"));
    image3 = new ImageIcon(simtkui.SimtkApp.class.getResource(
      "help.png"));
    image4 = new ImageIcon(simtkui.SimtkApp.class.getResource(
      "camera.gif"));
    image5 = new ImageIcon(simtkui.SimtkApp.class.getResource(
      "x_undo.jpg"));
    image6 = new ImageIcon(simtkui.SimtkApp.class.getResource(
      "x_redo.jpg"));
    border1 = BorderFactory.createBevelBorder(BevelBorder.LOWERED,Color.white,Color.white,new Color(115, 114, 105),new Color(165, 163, 151));
    border2 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    getContentPane().setLayout(borderLayout1);
    this.setSize(new Dimension(400, 300));
    this.getContentPane().setBackground(SystemColor.control);
    this.setTitle(SimtkApp.getString("ApplicationTitle"));

    statusBar.setText(" ");
    // File Menu
    jMenuFile.setDebugGraphicsOptions(DebugGraphics.NONE_OPTION);
    //jMenuFile.setText("File");

    jMenuFileExit.setAction(CommandFactory.getCommand("SimtkFileExitCmd"));
    jMenuHelp.setText(SimtkApp.getString("Application.Menus.Help.Label"));
    jMenuHelpAbout.setText("About");
    jMenuHelpAbout.addActionListener(new SimtkMainFrame_jMenuHelpAbout_ActionAdapter(this));

    jOpenModelButton.setAction(CommandFactory.getCommand("SimtkFileOpenByNameCmd"));
    jOpenModelButton.setIcon(image1);

    jModelBrowseMenuItem.setText("Browse for Model");
    jCloseModelButton.setAction(CommandFactory.getCommand("SimtkFileCloseCmd"));
    jCloseModelButton.setIcon(image2);

    jHelpButton.setAction(CommandFactory.getCommand("SimtkFileHelpCmd"));
    // @todo provide actual implementation for command SimtkFileHelpCmd
    jHelpButton.setIcon(image3);

    jSplitPane1.setOrientation(JSplitPane.VERTICAL_SPLIT);
    jSplitPane1.setDebugGraphicsOptions(DebugGraphics.NONE_OPTION);
    jSplitPane1.setDoubleBuffered(true);
    jSplitPane1.setMaximumSize(new Dimension(2147483647, 2147483647));
    jSplitPane1.setMinimumSize(new Dimension(800, 400));
    jSplitPane1.setPreferredSize(new Dimension(800, 400));
    jSplitPane1.setToolTipText("");
    jSplitPane1.setContinuousLayout(true);
    jSplitPane1.setDividerSize(6);
    jSplitPane1.setLastDividerLocation(150);
    jSplitPane1.setOneTouchExpandable(true);
    jSplitPane1.setResizeWeight(0.7);
    jSplitPane2.setDoubleBuffered(true);
    jSplitPane2.setToolTipText("");
    jSplitPane2.setContinuousLayout(true);
    jSplitPane2.setDividerSize(6);
    jSplitPane2.setLastDividerLocation(80);
    jSplitPane2.setOneTouchExpandable(true);

    jMainPane.setBackground(Color.darkGray);
    modelDesktopPane.setLayout(null);
    modelDesktopPane.setForeground(Color.black);
    modelDesktopPane.setMinimumSize(new Dimension(800, 500));
    modelDesktopPane.setPreferredSize(new Dimension(800, 500));
    modelDesktopPane.setRequestFocusEnabled(true);

    jSimDBTree.addMouseListener(new SimtkMainFrame_jSimDBTree_mouseAdapter(this));

    jMessagePane.setHorizontalScrollBarPolicy(JScrollPane.
                                              HORIZONTAL_SCROLLBAR_ALWAYS);
    jMessagePane.setVerticalScrollBarPolicy(JScrollPane.
                                            VERTICAL_SCROLLBAR_ALWAYS);
    jMessagePane.setViewportBorder(null);
    jMessagePane.setEnabled(false);
    jMessagePane.setBorder(BorderFactory.createLoweredBevelBorder());
    jMessagePane.setPreferredSize(new Dimension(21, 21));
    jMessagePane.setToolTipText("");
    jNewEnvMenuItem.setAction(CommandFactory.getCommand("SimtkFileNewSimEnvCmd"));
    jModelByNameMenuItem.setAction(CommandFactory.getCommand("SimtkFileOpenByNameCmd"));
    jModelBrowseMenuItem.setAction(CommandFactory.getCommand("SimtkFileBrowseForModelCmd"));
    jMessageArea.setOpaque(true);
    jMessageArea.setToolTipText("");
    jMessageArea.setEditable(false);
    jMessageArea.setSelectedTextColor(Color.white);
    jMessageArea.setSelectionStart(0);
    jMessageArea.setText("");
    jMessageArea.setLineWrap(true);
    jMessageArea.setRows(0);
    jMessageArea.setWrapStyleWord(true);
    jSnapShotButton.setAction(CommandFactory.getCommand("SimtkSnapShotCmd"));
    jSnapShotButton.setIcon(image4);
    jSnapShotButton.setSelectedIcon(image4);
    jSnapShotButton.setVerifyInputWhenFocusTarget(true);
    image1.setDescription("");
    image2.setDescription("");
    image3.setDescription("");
    jSaveModelMenuItem.setAction(CommandFactory.getCommand("SimtkSaveModelCmd"));
    jMenuScript.setText("Scripting");
    jMenuLoadScript.setAction(CommandFactory.getCommand("SimtkLoadScriptCmd"));
    jCheckToggleSingleStep.setActionCommand("");
    jCheckToggleSingleStep.setText("Single Step");
    jCheckToggleSingleStep.addActionListener(new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        CommandFactory.toggleCommandPlaybackSingleStep();
      }
    });
    jFlushScriptMenuitem.setText("flush script");
    jFlushScriptMenuitem.addActionListener(new ActionListener(){
  /**
   * actionPerformed
   *
   * @param e ActionEvent
   */
  public void actionPerformed(ActionEvent e) {
    CommandFactory.flushCommandLog();
  }
});

    jTestMenuItem.setAction(CommandFactory.getCommand("TestCmd"));
    jTestMenu.setToolTipText("Some test commands");
    jTestMenu.setText("Test");
    jInvokePluginMgr.setToolTipText("Invoke Plugin Manager");
    jInvokePluginMgr.setText("Plugin Mgr");
    jInvokePluginMgr.addActionListener(new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        SimtkPluginManagerDlg pmDlg = new SimtkPluginManagerDlg((Frame)SimtkApp.getTopComponent());
        pmDlg.setVisible(true);
      }
    });
    jactivateAll.addActionListener(new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        try {
          //Boot.main(null);
        }
        catch (Throwable ex) {
        }
      }

    });
    jUndoButton.setText("Undo");
    _undoCommand = CommandFactory.getCommand("SimtkUndoLastCmd");
    jUndoButton.setAction(_undoCommand);
    jUndoButton.setIcon(image5);
    // Make undo and redo commands observe execManager to enable disable themselves properly
    execManager.addObserver(_undoCommand);

    jRedoButton.setText("Redo");
    _redoCommand = CommandFactory.getCommand("SimtkRedoLastCmd");
    jRedoButton.setAction(_redoCommand);
    jRedoButton.setIcon(image6);
    execManager.addObserver(_redoCommand);

    jLogTextArea.setOpaque(true);
    jLogTextArea.setToolTipText("");
    jLogTextArea.setEditable(false);
    jLogTextArea.setSelectionEnd(0);
    jLogTextArea.setText("");
    jLogTextArea.setColumns(0);
    jLogTextArea.setRows(0);
    jLogTextArea.setWrapStyleWord(true);
    jLogPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
    jLogPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    jLogPane.setEnabled(false);
    jLogPane.setBorder(border1);
    jactivateAll.setText("Activate all");
    /*
    jWorkflowMenuitem.setText("Workflow");
    SimtkCommand invokeWorkflowCmd = new SimtkWorkFlowCommand();
    jWorkflowMenuitem.setAction(invokeWorkflowCmd);
   */
    jToolBar.add(jOpenModelButton);
    jToolBar.add(jCloseModelButton);
    jToolBar.add(jHelpButton);
    jToolBar.add(jSnapShotButton);
    jToolBar.add(jUndoButton, null);
    jToolBar.add(jRedoButton, null);
    jMenuPlot.add(jPlotMenuitem);
    SimtkCommand invokePlotCmd = CommandFactory.getCommand("SimtkGrapherCmd");
    jPlotMenuitem.setAction(invokePlotCmd);

    jMenuFile.add(jNewEnvMenuItem);
    jMenuFile.add(jModelByNameMenuItem);
    jMenuFile.add(jModelBrowseMenuItem);
    jMenuFile.add(jSaveModelMenuItem);
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);

    SimtkJMenuFactory.addTopMenu(jMenuFile);
    SimtkJMenuFactory.addTopMenu(new SimtkWindowMenu(modelDesktopPane));
    SimtkJMenuFactory.addTopMenu(jMenuScript);
    SimtkJMenuFactory.addTopMenu(jPluginsMenu);
    SimtkJMenuFactory.addTopMenu(jMenuHelp);
    SimtkJMenuFactory.addTopMenu(jMenuPlot);
    this.setJMenuBar(jMenuBar1);
    getContentPane().add(statusBar, BorderLayout.WEST);

    getContentPane().add(jSplitPane1, BorderLayout.CENTER);
    jSplitPane1.add(jSplitPane2, JSplitPane.TOP);
    //jSplitPane2.add(jSimDBTree, JSplitPane.LEFT);
    jSplitPane2.add(jMainPane, JSplitPane.RIGHT);
    jSplitPane2.add(jModelTreeScroll, JSplitPane.LEFT);
    jMainPane.getViewport().add(modelDesktopPane);
    jSplitPane1.add(jBottomPane, JSplitPane.BOTTOM);
    jBottomPane.addTab("Messages", jMessagePane);
    jBottomPane.add(jLogPane, "Log");
    jBottomPane.add(jShellPane, "Shell");
    jLogPane.getViewport().add(jLogTextArea, null);
    jLogTextArea.setDocument(new PlainDocument());
    jShellPane.getViewport().add(jShellArea);
    jMessagePane.getViewport().add(jMessageArea, null);
    jMenuScript.add(jMenuLoadScript);
    jMenuScript.add(jCheckToggleSingleStep);
    jMenuScript.add(jFlushScriptMenuitem);
    if (SimtkApp.getString("Application.Menus.Test.Show").equals("yes")){
      SimtkJMenuFactory.addTopMenu(jTestMenu);
      jTestMenu.add(jTestMenuItem);
    }
    jPluginsMenu.add(jInvokePluginMgr);
    jPluginsMenu.add(jactivateAll);
    /*
     jPluginsMenu.add(jWorkflowMenuitem);
    jPluginsMenu.add(jPlotMenuitem);
    */
    this.getContentPane().add(jToolBar, BorderLayout.NORTH);
    jModelTreeScroll.getViewport().add(jSimDBTree, null);
    jSplitPane1.setDividerLocation(600);
    jSplitPane2.setDividerLocation(150);

    this.setIconImage(SimtkApp.getAppImage());
    this.setSize(1000, 800);
  }

  //File | Exit action performed
  public void jMenuFileExit_actionPerformed(ActionEvent e) {
    try {
      ExecutionManager.enQueueCommand(CommandFactory.getCommand(
          "SimtkFileExitCmd"));
    }
    catch (CommandFactoryException ex) {
      SimtkApp.displayDebugMessage("Exit Command: " + "SimtkFileExitCmd"+ " could not be found.. Ignored");
    }
  }

  //Help | About action performed
  public void jMenuHelpAbout_actionPerformed(ActionEvent e) {
    SimtkMainFrame_AboutBox dlg = new SimtkMainFrame_AboutBox(this);
    Dimension dlgSize = dlg.getPreferredSize();
    Dimension frmSize = getSize();
    Point loc = getLocation();
    dlg.setLocation( (frmSize.width - dlgSize.width) / 2 + loc.x,
                    (frmSize.height - dlgSize.height) / 2 + loc.y);
    dlg.setModal(true);
    dlg.pack();
    dlg.show();
  }

  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      jMenuFileExit_actionPerformed(null);
    }
    else
      super.processWindowEvent(e);
  }

  /**
   * update
   *
   * @param o Observable
   * @param arg Object
   *
   * @todo build an event object from the ModelChange hierarchy and pass it around as arg
   * so that selective updates can be done and are not costly. In general we don't want to
   * redraw the tree every time something happens to the model.
   * @todo if this function becomes busy with lots of if else conditions we may want to pass its
   * responsibilities to a dedicated class (e.g. SimtkEventDispatcher).
   */
  public void update(Observable o, Object arg)
  {
      SimtkSimulationEvent evnt = (SimtkSimulationEvent) arg;

      if (evnt instanceof SimtkNewModelEvent){
        SimtkSimEnv env = (SimtkSimEnv) evnt.getSource();
        SimtkViewDB.addSimenvToView(env);
        jSimDBTree.setModel(simtkDB.getTreeModel());
      }
      else if (evnt instanceof SimtkCloseModelEvent) {
        jSimDBTree.setModel(simtkDB.getTreeModel());
        jSimDBTree.repaint();
       }
       else if (evnt instanceof SimtkNewSimEnvEvent || evnt instanceof SimtkUpdateTreeEvent){
         SimtkSimEnv curEnv = (SimtkSimEnv) evnt.getSource();
         ((SimtkDBTreeModel)simtkDB.getTreeModel()).updateSimEnvTree(curEnv);
         jSimDBTree.setModel(simtkDB.getTreeModel());
       }
  }


  /**
   * jSimDBTree_mousePressed entry point for all callbacks from right mouse
   * clicks on model tree. Only one function jSimDBTree_mousePressed is used and
   * set for both mouse pressed and released as the exact mouse event is
   * platform dependent.
   * @todo When actual objects are added to the tree, get commands from command
   * manager and associate to created menu-items. Also create popups on the fly
   * based on object type (e.g. visible objects would have visibility controls).
   * We may have to have these precreated for efficiency.
   *
   * @param e MouseEvent
   */
  void jSimDBTree_mousePressed(MouseEvent e) {
    if (e.isPopupTrigger()) {
      jSimDBTree.handleMousePressed(e);
    }
  }

  public JTabbedPane getExtensionPane()
  {
    return jBottomPane;
  }

}

class SimtkMainFrame_jMenuFileExit_ActionAdapter implements ActionListener {
  SimtkMainFrame adaptee;

  SimtkMainFrame_jMenuFileExit_ActionAdapter(SimtkMainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuFileExit_actionPerformed(e);
  }
}

class SimtkMainFrame_jMenuHelpAbout_ActionAdapter implements ActionListener {
  SimtkMainFrame adaptee;

  SimtkMainFrame_jMenuHelpAbout_ActionAdapter(SimtkMainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuHelpAbout_actionPerformed(e);
  }
}

class SimtkMainFrame_jSimDBTree_mouseAdapter extends java.awt.event.MouseAdapter {
  SimtkMainFrame adaptee;

  SimtkMainFrame_jSimDBTree_mouseAdapter(SimtkMainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void mousePressed(MouseEvent e) {
    adaptee.jSimDBTree_mousePressed(e);
  }
  public void mouseReleased(MouseEvent e) {
    adaptee.jSimDBTree_mousePressed(e);// use same callback to avoid code duplication
  }
}
