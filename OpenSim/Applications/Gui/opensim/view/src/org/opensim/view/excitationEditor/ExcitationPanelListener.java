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
import org.opensim.modeling.Function;
import org.opensim.view.functionEditor.FunctionNode;
import org.opensim.view.functionEditor.FunctionPanel;
import org.opensim.view.functionEditor.FunctionPanelListener;
import org.opensim.view.functionEditor.FunctionXYSeries;

/**
 *
 * @author Ayman
 */
public class ExcitationPanelListener implements FunctionPanelListener{
    FunctionPanel functionPanel;
    ControlLinear control;
    Vector<Function> functions=new  Vector<Function>(3);
    /**
     * Creates a new instance of ExcitationPanelListener
     */
    public ExcitationPanelListener(FunctionPanel functionPanel, ControlLinear excitation, Vector<Function> functions) {
        this.functionPanel = functionPanel;
        this.control = excitation;
        this.functions=functions;
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
      /*
      double minGap = 99999999.9;
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      if (dragVector[0] < 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == 0 || functionPanel.isNodeSelected(0, index-1))
               continue;
            double gap = control.getX(index) - control.getX(index-1);
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
            if (index == control.getNumberOfPoints()-1 || functionPanel.isNodeSelected(0, index+1))
               continue;
            double gap = control.getX(index+1) - control.getX(index);
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
      // Now move all the control points by dragVector.
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode;
         if (series==0)
             controlNode = control.getControlValues().get(index);
         else if (series==1)
            controlNode = control.getControlMinValues().get(index);
         else
            controlNode = control.getControlMaxValues().get(index);

         double newX = controlNode.getTime() + dragVector[0];
         double newY = controlNode.getValue() + dragVector[1];
         controlNode.setTime(newX);
         controlNode.setValue(newY);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         ((FunctionXYSeries)seriesCollection.getSeries(series)).updateByIndex(index, newX, newY);
         // Update the function so that when render as line segment is called it's uptodate'
         functions.get(series).setX(index, newX);
         functions.get(series).setY(index, newY);
         seriesCollection.getSeries(series).fireSeriesChanged();
      }
      //updateXYTextFields();
      //setPendingChanges(true, true);
      //notifyListeners(new FunctionModifiedEvent(model, object, control));
   }

   public void duplicateNode(int series, int node) {
      if (control != null && node >= 0 && node < control.getControlValues().getSize()) {
         // Make a new point that is offset slightly in the X direction from
         // the point to be duplicated.
         ControlLinearNode controlNode = control.getControlValues().get(node);
          
         double newX = controlNode.getTime() + 0.00001;
         double newY = controlNode.getValue();
         addNode(0, newX, newY);
      }
   }

   public void deleteNode(int series, int node) {
      if (control != null && node >= 0 && node < control.getControlValues().getSize()) {
         //if (control.deletePoint(node)) {
            //xySeries.delete(node, node);
            //setPendingChanges(true, true);
         //}
      }
   }

   public void addNode(int series, double x, double y) {
      if (control != null) {
         //control.addPoint(x, y);
         //xySeries.add(x, y);
         //setPendingChanges(true, true);
      }
   }

   public void setSelectedNodesToValue(int series, double newValue) {
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode = control.getControlValues().get(index);
         double newX = controlNode.getTime();
         double newY = newValue;
         controlNode.setTime(newX);
         controlNode.setValue(newY);
         // Update underlying function
         functions.get(series).setX(index, newX);
         functions.get(series).setY(index, newY);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         seriesCollection.getSeries(series).getDataItem(index).setY(newY);
         seriesCollection.getSeries(series).fireSeriesChanged();
      }
       
   }

   public void deleteSelectedNodes() {
 
   }
 
    public void addFunction(Function aFunction)
    {
        functions.add(aFunction);
    }
    
    public void removeFunction(Function aFunction)
    {
        functions.remove(aFunction);
    }
}
