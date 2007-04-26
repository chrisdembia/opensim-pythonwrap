package org.opensim.plotter;

import javax.swing.tree.DefaultMutableTreeNode;

/**
 * Class representing a node in the tree of plots used by the Plotter dialog
 */
class PlotNode extends DefaultMutableTreeNode
{
   public PlotNode(Plot fig){
      // implicit super
      setUserObject(fig);
   }

   public String toString() {
      return ((Plot) getUserObject()).getTitle();
   } 

}