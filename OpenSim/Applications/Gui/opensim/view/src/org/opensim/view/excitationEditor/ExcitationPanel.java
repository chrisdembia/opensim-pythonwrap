/*
 * ExcitationPanel.java
 *
 * Created on March 6, 2008, 12:48 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import java.util.Collections;
import java.util.Vector;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeriesCollection;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.view.functionEditor.FunctionPanel;

/**
 *
 * @author Ayman
 */
public class ExcitationPanel extends FunctionPanel{
    
    /** Creates a new instance of ExcitationPanel */
   public ExcitationPanel(JFreeChart chart) {
      super(chart);
    }
    
   public void deleteSelectedNodes()
   {
       XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();
       
        // Need to sort indices so that nodes are deleted from last to first thus respecting indices
       for (int series=0; series < seriesCollection.getSeriesCount(); series++){
           Vector<Integer> sortedIndices = new Vector<Integer>(selectedNodes.size());
           for (int i=0; i<selectedNodes.size(); i++) {
               int index = selectedNodes.get(i).node;
               if (selectedNodes.get(i).series==series)
                    sortedIndices.add(new Integer(index));
           }
           Collections.sort(sortedIndices);
           ExcitationRenderer renderer = (ExcitationRenderer) getChart().getXYPlot().getRenderer(series);
           for (int i=sortedIndices.size()-1; i>=0; i--) {
               int index = sortedIndices.get(i);
               //control.deleteControlNode(index);
               // Update underlying function
               renderer.getFunctionList().get(series).deletePoint(index);
               seriesCollection.getSeries(series).remove(index);
               seriesCollection.getSeries(series).fireSeriesChanged();
               
           }
       }
       clearSelectedNodes();      
   }
   
   public void setSelectedNodesToValue(int series, double newValue) {
      ExcitationRenderer renderer = (ExcitationRenderer) getChart().getXYPlot().getRenderer(series);
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode = renderer.getControl().getControlValues().get(index);
         double newX = controlNode.getTime();
         double newY = newValue;
         controlNode.setTime(newX);
         controlNode.setValue(newY);
         // Update underlying function
         renderer.getFunctionList().get(series).setX(index, newX);
         renderer.getFunctionList().get(series).setY(index, newY);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();
         seriesCollection.getSeries(series).getDataItem(index).setY(newY);
         seriesCollection.getSeries(series).fireSeriesChanged();
      }
       
   }
}
