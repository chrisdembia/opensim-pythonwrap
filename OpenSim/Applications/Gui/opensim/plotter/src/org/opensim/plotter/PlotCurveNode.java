package org.opensim.plotter;

import javax.swing.tree.DefaultMutableTreeNode;


/**
 * Inner class for individual curves
 */
class PlotCurveNode extends DefaultMutableTreeNode
{
   public PlotCurveNode(PlotCurve crv)
   {
      // implicit super
      setUserObject(crv);
   }

   public String toString() {
      return ((PlotCurve) getUserObject()).getLegend();
   }
}