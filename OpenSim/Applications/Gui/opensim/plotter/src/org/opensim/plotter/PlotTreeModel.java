/*
 *
 * PlotTreeModel
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.plotter;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

/**
 *
 * @author Ayman, Class backing up the tree of plots that shows in the plotter dialog
 * with the following Hierarchy
 * -Plots
 *    - Plot
 *       -Curve
 */
public class PlotTreeModel extends DefaultTreeModel {
   
   Plot  currentPlot=null;
   
   /** Creates a new instance of PlotTreeModel */
   public PlotTreeModel() {
      super(new DefaultMutableTreeNode("Plots") , false);
   }
   
   public int getNumberOfPlots()
   {
      return ((DefaultMutableTreeNode)getRoot()).getChildCount();
   }
   
   public Plot getPlot(int index)
   {
      PlotNode fnode = (PlotNode)((DefaultMutableTreeNode)getRoot()).getChildAt(index);
      return (Plot)(fnode.getUserObject());
   }
   public int addPlot(Plot newPlot)
   {
      int pos = getNumberOfPlots();
      // Create a node for the figure
      PlotNode figNode = new PlotNode(newPlot);
      insertNodeInto(figNode, (DefaultMutableTreeNode)getRoot(), pos);
      currentPlot = newPlot;
      return pos;
   }
   /**
    * Get the node that represents a figure
    */
   public PlotNode findPlotNode(Plot fig)
   {
      int nf=getNumberOfPlots();
      for(int i= 0; i<nf; i++){
         PlotNode figNode = (PlotNode) ((DefaultMutableTreeNode)getRoot()).getChildAt(i);
         if (((Plot)figNode.getUserObject()).equals(fig))
            return (PlotNode)figNode;
      }
      return null;
   }
   /**
    * Get the node for the figure that contains the passed in plotCurve
    */
   public PlotNode findPlotNode(PlotCurve cv)
   {
      return (PlotNode) findCurveNode(cv).getParent();
   }
   
   public PlotCurveNode findCurveNode(PlotCurve cv)
   {
      int nf=getNumberOfPlots();
      for(int i= 0; i<nf; i++){
         PlotNode figNode = (PlotNode) ((DefaultMutableTreeNode)getRoot()).getChildAt(i);
         int figNodeChildrenCount = figNode.getChildCount();
         for(int c=0;c<figNodeChildrenCount;c++){
            PlotCurveNode cvNode = (PlotCurveNode) (figNode.getChildAt(c));
            if (cvNode.getUserObject() instanceof PlotCurve){
               if (cvNode.getUserObject().equals(cv))
                  return cvNode;
            }
         }
      }
      return null;

   }
   /**
    * Add a Plot to the current Plot
    */
   public void addPlotCurveToTree(PlotCurve crv)
   {
      // Find node for figure
      int nf=getNumberOfPlots();
      for(int i= 0; i<nf; i++){
         Plot fig = getPlot(i);
         PlotNode figNode = findPlotNode(fig);
         if (fig.equals(currentPlot)){
            // Create node for PlotCurve
            PlotCurveNode cnode = new PlotCurveNode(crv);
            insertNodeInto(cnode, figNode, figNode.getChildCount());
         }
      }
   }
   
}
