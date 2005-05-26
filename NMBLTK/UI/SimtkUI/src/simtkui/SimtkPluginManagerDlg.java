package simtkui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.ListSelectionModel;
import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

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
 * Dialog for Plugin Manager. The actual plugin management is performed by
* the underlying vlass SimtkPluginManager.
 */
public class SimtkPluginManagerDlg extends SimtkJDialog {
  JPanel jSelectionPanel = new JPanel();
  JPanel jOperationsPanel = new JPanel();
  JButton jCloseButton = new JButton();
  BorderLayout borderLayout1 = new BorderLayout();
  JTabbedPane jpluginsPanel = new JTabbedPane();
  JPanel jLoadedPlugins = new JPanel();
  BorderLayout borderLayout3 = new BorderLayout();
  JPanel jContextOpPanel = new JPanel();
  JButton jUnloadPlugin = new JButton();
  JButton jUpdatePlugin = new JButton();
  JPanel jAvailableResources = new JPanel();
  BorderLayout borderLayout4 = new BorderLayout();
  JList jResourceList = new JList();
  JPanel jPanel1 = new JPanel();
  JButton jSavePluginPath = new JButton();
  JButton jRemovePluginResource = new JButton();
  JButton jAddesource = new JButton();
  JPanel jPluginListPanel = new JPanel();
  JScrollPane jPluginDetails = new JScrollPane();
  JList jPluginList = new JList();
  GridLayout gridLayout1 = new GridLayout();
  Border border1;
  TitledBorder titledBorder1;
  Border border2;
  TitledBorder titledBorder2;
  public SimtkPluginManagerDlg(Frame Owner) {
    super(Owner);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    jResourceList.setModel(SimtkPluginManager.getInstance());
    this.pack();
    this.center();
  }
  private void jbInit() throws Exception {
    border1 = BorderFactory.createBevelBorder(BevelBorder.LOWERED,Color.white,Color.white,new Color(124, 124, 124),new Color(178, 178, 178));
    titledBorder1 = new TitledBorder(border1,"Plugins List");
    border2 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
    titledBorder2 = new TitledBorder(border2,"Plugin Description");
    jCloseButton.setText("Close");
    jCloseButton.addActionListener(new SimtkPluginManagerDlg_jCloseButton_actionAdapter(this));
    jSelectionPanel.setLayout(borderLayout1);
    jLoadedPlugins.setLayout(borderLayout3);
    jUnloadPlugin.setToolTipText("");
    jUnloadPlugin.setText("Unload");
    jUpdatePlugin.setToolTipText("");
    jUpdatePlugin.setText("Update");
    jSavePluginPath.setText("Make Persistent");
    jAvailableResources.setLayout(borderLayout4);
    jRemovePluginResource.setToolTipText("");
    jRemovePluginResource.setText("Remove");
    jAddesource.setText("Add");
    jPluginListPanel.setLayout(gridLayout1);
    jPluginList.setAlignmentY((float) 0.5);
    jPluginList.setAutoscrolls(false);
    jPluginList.setBorder(titledBorder1);
    jPluginList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    jPluginDetails.setBorder(titledBorder2);
    this.setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    this.setModal(true);
    this.setTitle("Plugin Manager");
    jSelectionPanel.setMinimumSize(new Dimension(400, 300));
    jSelectionPanel.setPreferredSize(new Dimension(400, 300));
    jLoadedPlugins.add(jContextOpPanel, BorderLayout.SOUTH);
    jContextOpPanel.add(jUnloadPlugin, null);
    this.getContentPane().add(jSelectionPanel, BorderLayout.CENTER);
    this.getContentPane().add(jOperationsPanel, BorderLayout.SOUTH);
    jOperationsPanel.add(jCloseButton, null);
    jSelectionPanel.add(jpluginsPanel,  BorderLayout.CENTER);
    jpluginsPanel.addTab( "Loaded Plugins", jLoadedPlugins);
    jContextOpPanel.add(jUpdatePlugin, null);
    jContextOpPanel.add(jSavePluginPath, null);
    jLoadedPlugins.add(jPluginListPanel, BorderLayout.CENTER);
    jAvailableResources.add(jResourceList, BorderLayout.CENTER);
    jAvailableResources.add(jPanel1,  BorderLayout.SOUTH);
    jPanel1.add(jAddesource, null);
    jPanel1.add(jRemovePluginResource, null);
    jPanel1.add(jSavePluginPath, null);
    jPluginListPanel.add(jPluginList, null);
    jPluginListPanel.add(jPluginDetails, null);
    jpluginsPanel.add(jAvailableResources, "jAvailableResources");
  }

  void jCloseButton_actionPerformed(ActionEvent e) {
    dispose();
  }
}

class SimtkPluginManagerDlg_jCloseButton_actionAdapter implements java.awt.event.ActionListener {
  SimtkPluginManagerDlg adaptee;

  SimtkPluginManagerDlg_jCloseButton_actionAdapter(SimtkPluginManagerDlg adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jCloseButton_actionPerformed(e);
  }
}
