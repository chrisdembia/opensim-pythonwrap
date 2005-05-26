package simtkView;

import java.awt.Component;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JTree;
import javax.swing.UIManager;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeCellRenderer;

import simtkCore.SimtkSimEnv;
import simtkui.SimtkApp;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Renderer for the simulation tree intended to show specialized icons as needed
 * in the tree.
 *
 * @author Ayman Habib
 * @version 1.0
 */
public class SimtkMdlTreeRenderer extends JLabel implements TreeCellRenderer {
  public SimtkMdlTreeRenderer() {
    setFont(UIManager.getFont( "Tree.font"));
    setOpaque( true );
  }

  /**
   * getTreeCellRendererComponent
   *
   * @param tree JTree
   * @param value Object
   * @param selected boolean
   * @param expanded boolean
   * @param leaf boolean
   * @param row int
   * @param hasFocus boolean
   * @return Component
   */
  public Component getTreeCellRendererComponent(JTree tree, Object value,
                                                boolean selected,
                                                boolean expanded, boolean leaf,
                                                int row, boolean hasFocus) {
    if (value != null)
      setText(value.toString());
    else
      setText("");

      //
      // Set the colors for the cell.
      //
    if (selected) {
      setBackground(UIManager.getColor("Tree.selectionBackground"));
      setForeground(UIManager.getColor(
          "Tree.selectionForeground"));
    }
    else {
      setBackground(UIManager.getColor("Tree.textBackground"));
      setForeground(UIManager.getColor("Tree.textForeground"));
    }
    //
    // The type of the node is stored in the user object which can be a String for nodes
    // not connected to model objects in the mutable tree node.
    //
    //setIcon(null);

    if (value instanceof DefaultMutableTreeNode) { // Guard against undefined node types
      DefaultMutableTreeNode node = (DefaultMutableTreeNode) value;
      Object o = node.getUserObject();

      if (o instanceof SimtkSimEnv) {
        setIcon(SimtkApp.getAppIcon());
      }
      // Eventually these nodes will have objects associated with them and
      // we can provide a common API to get their icon  file probably a dictionary that
      // maps types to icons can be implemented in this class and so can be made extensible
      // with registery access
      else if (o instanceof String && ((String) o).equals("Data Manager")){
        java.net.URL imgURL = simtkui.SimtkApp.class.getResource("data-icon_16x16.jpg");
        Image dataMgrImage = null;
        if (imgURL != null){
          dataMgrImage = new ImageIcon(imgURL).getImage();
        }
        else
          dataMgrImage = null;
          if (dataMgrImage != null)
            setIcon( new ImageIcon(dataMgrImage));
    }

    }
    return (this);

  }

}
