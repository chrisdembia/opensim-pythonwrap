/*
 * ExcitationPanelListener.java
 *
 * Created on February 14, 2008, 10:21 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Vector;
import org.jfree.data.xy.XYSeriesCollection;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.view.functionEditor.FunctionNode;
import org.opensim.view.functionEditor.FunctionPanel;
import org.opensim.view.functionEditor.FunctionPanelListener;

/**
 *
 * @author Ayman
 */
public class ExcitationPanelListener implements FunctionPanelListener{
    FunctionPanel functionPanel;
    ControlLinear function;
    /**
     * Creates a new instance of ExcitationPanelListener
     */
    public ExcitationPanelListener(FunctionPanel functionPanel, ControlLinear excitation) {
        this.functionPanel = functionPanel;
        this.function = excitation;
    }

   public void toggleSelectedNode(int series, int node) {
      //updateXYTextFields();
   }

   public void clearSelectedNodes() {
      //updateXYTextFields();
   }

   public void replaceSelectedNode(int series, int node) {
      //updateXYTextFields();
   }

   private void cropDragVector(double dragVector[]) {
      // Don't allow any dragged node to go past either of its neighbors in the X dimension.
       /* Taken out for now. Probably doesn't need function since values are in the dataset anyway!
      double minGap = 99999999.9;
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      if (dragVector[0] < 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == 0 || functionPanel.isNodeSelected(0, index-1))
               continue;
            double gap = function.getX(index) - function.getX(index-1);
            if (gap < minGap)
               minGap = gap;
         }
         // minGap is the smallest [positive] distance between a dragged node and its
         // left neighbor (if unselected). dragVector[0] can't be a larger negative
         // number than this value.
         if (dragVector[0] < -minGap)
            dragVector[0] = -minGap;
      } else if (dragVector[0] > 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == function.getNumberOfPoints()-1 || functionPanel.isNodeSelected(0, index+1))
               continue;
            double gap = function.getX(index+1) - function.getX(index);
            if (gap < minGap)
               minGap = gap;
         }
         // minGap is the smallest [positive] distance between a dragged node and its
         // right neighbor (if unselected). dragVector[0] can't be a larger positive
         // number than this value.
         if (dragVector[0] > minGap)
            dragVector[0] = minGap;
      }*/
   }

   public void dragSelectedNodes(int series, int node, double dragVector[]) {
      cropDragVector(dragVector);
      // Now move all the function points by dragVector.
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode = function.getControlValues().get(index);
         double newX = controlNode.getTime() + dragVector[0];
         double newY = controlNode.getValue() + dragVector[1];
         controlNode.setTime(newX);
         controlNode.setValue(newY);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         seriesCollection.getSeries(series).getDataItem(index).setY(newY);
         seriesCollection.getSeries(series).fireSeriesChanged();
      }
      //updateXYTextFields();
      //setPendingChanges(true, true);
      //notifyListeners(new FunctionModifiedEvent(model, object, function));
   }

   public void duplicateNode(int series, int node) {
      if (function != null && node >= 0 && node < function.getControlValues().getSize()) {
         // Make a new point that is offset slightly in the X direction from
         // the point to be duplicated.
         ControlLinearNode controlNode = function.getControlValues().get(node);
          
         double newX = controlNode.getTime() + 0.00001;
         double newY = controlNode.getValue();
         addNode(0, newX, newY);
      }
   }

   public void deleteNode(int series, int node) {
      if (function != null && node >= 0 && node < function.getControlValues().getSize()) {
         //if (function.deletePoint(node)) {
            //xySeries.delete(node, node);
            //setPendingChanges(true, true);
         //}
      }
   }

   public void addNode(int series, double x, double y) {
      if (function != null) {
         //function.addPoint(x, y);
         //xySeries.add(x, y);
         //setPendingChanges(true, true);
      }
   }

   public void setSelectedNodesToValue(int series, double newValue) {
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode = function.getControlValues().get(index);
         double newX = controlNode.getTime();
         double newY = newValue;
         controlNode.setTime(newX);
         controlNode.setValue(newY);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         seriesCollection.getSeries(series).getDataItem(index).setY(newY);
         seriesCollection.getSeries(series).fireSeriesChanged();
      }
       
   }

    public void deleteSelectedNodes(int series) {
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      // Need to sort indices so that nodes are deleted from last to first thus respecting indices
      Vector<Integer> sortedIndices = new Vector<Integer>(selectedNodes.size());
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         sortedIndices.add(new Integer(index));
      }
      Collections.sort(sortedIndices);
      for (int i=selectedNodes.size()-1; i>=0; i--) {
         int index = sortedIndices.get(i);
         //functionPanel.removeNode();
      }
    }
 
}
