package simtkView.plot;

import javax.swing.*;
import simtkCore.SimtkDB;
import javax.swing.tree.*;
import simtkCore.*;
import java.util.Enumeration;
import simtkModel.*;
import java.awt.event.*;

public class SimtkPlotQuantitySelector extends JPopupMenu implements ActionListener {

  public SimtkPlotQuantitySelector() {
    // Add an entry per SimEnv, with a cascade menu for Storages and another level for qty
    TreeModel dbTreeModel = SimtkDB.getInstance().getTreeModel();
    Object root = dbTreeModel.getRoot();
    for(int i=0; i < dbTreeModel.getChildCount(root); i++){
      Object obj = ((DefaultMutableTreeNode) dbTreeModel.getChild(root, i)).getUserObject();
      SimtkSimEnv env = (SimtkSimEnv)obj;
      JMenu envMenu = new JMenu(env.getName());
      add(envMenu);
      Enumeration allStorages = env.getAvailableStorages();
      if (allStorages != null){
       while (allStorages.hasMoreElements()) {
         rdStorage nextStorage = (rdStorage) allStorages.nextElement();
         JMenu storageMenu = new JMenu(nextStorage.getName());
         envMenu.add(storageMenu);
         rdArrayStr columnLabels = nextStorage.getColumnLabelsArray();
         for (int j=0; i < columnLabels.getSize(); i++){
           String QName = columnLabels.getitem(i);
           JMenuItem QMenuItem = new JMenuItem(QName);
           storageMenu.add(QMenuItem);
         }
      }
     }
    }
  }

  /**
   * actionPerformed
   *
   * @param e ActionEvent
   */
  public void actionPerformed(ActionEvent e) {

  }
}
