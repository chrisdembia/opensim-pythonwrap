package simtkView.plot;

import javax.swing.*;
import simtkCore.SimtkDB;
import javax.swing.tree.*;
import simtkCore.*;
import java.util.Enumeration;
import simtkModel.*;
import java.awt.event.*;
import java.awt.*;

public class SimtkPlotQuantitySelector extends JPopupMenu implements ActionListener {
  String selectedQuantity;
  JTextField selectedQuantityField;
  public SimtkPlotQuantitySelector(JTextField selectionTextField) {
    selectedQuantityField = selectionTextField;
    // Add an entry per SimEnv, with a cascade menu for Storages and another level for qty
    TreeModel dbTreeModel = SimtkDB.getInstance().getTreeModel();
    Object root = dbTreeModel.getRoot();
    for(int i=0; i < dbTreeModel.getChildCount(root); i++){
      Object obj = ((DefaultMutableTreeNode) dbTreeModel.getChild(root, i)).getUserObject();
      SimtkSimEnv env = (SimtkSimEnv)obj;
      String  envName = env.getName();
      JMenu envMenu = new JMenu(envName);
      add(envMenu);
      Enumeration allStorages = env.getAvailableStorages();
      if (allStorages != null){
       while (allStorages.hasMoreElements()) {
         rdStorage nextStorage = (rdStorage) allStorages.nextElement();
         String storageName = nextStorage.getName();
         JMenu storageMenu = new JMenu(storageName);
         envMenu.add(storageMenu);
         rdArrayStr columnLabels = nextStorage.getColumnLabelsArray();
         int numEntries = columnLabels.getSize();
         int nColumns = numEntries/50+1;
         int nRows = 50;
         GridLayout menuGrid = new GridLayout(nRows,nColumns);
         storageMenu.getPopupMenu().setLayout(menuGrid);
         for (int j=0; j < columnLabels.getSize(); j++){
           String QName = columnLabels.getitem(j);
           JMenuItem QMenuItem = new JMenuItem(QName);
           QMenuItem.setActionCommand(envName+":"+storageName+":"+QName);
           QMenuItem.addActionListener(new ActionListener(){
              /**
               * actionPerformed
               *
               * @param e ActionEvent
               */
              public void actionPerformed(ActionEvent e) {
                selectedQuantity = e.getActionCommand();
                selectedQuantityField.setText(selectedQuantity);
              }
            });
           storageMenu.add(QMenuItem);
         }
      }
     }
    }
  }

  public String getSelectedQuantity()
  {
    return selectedQuantity;
  }
  /**
   * actionPerformed
   *
   * @param e ActionEvent
   */
  public void actionPerformed(ActionEvent e) {

  }
}
