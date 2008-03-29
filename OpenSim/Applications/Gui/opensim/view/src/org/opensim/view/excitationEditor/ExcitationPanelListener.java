/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
import java.util.Vector;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.modeling.Function;
import org.opensim.modeling.SetControlNodes;
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
    //ControlLinearNode newControlNode;
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
      
      double minGap = 99999999.9;
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      if (dragVector[0] < 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == 0 || functionPanel.isNodeSelected(0, index-1))
               continue;
            ControlLinearNode cn= getControlNodeForSeries(selectedNodes.get(i).series, index);
            ControlLinearNode cnMinus1= getControlNodeForSeries(selectedNodes.get(i).series, index-1);
            double gap = cn.getTime() - cnMinus1.getTime();
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
            if (index == getControlNodeCountForSeries(selectedNodes.get(i).series)-1 || functionPanel.isNodeSelected(selectedNodes.get(i).series, index+1))
               continue;
            ControlLinearNode cn= getControlNodeForSeries(selectedNodes.get(i).series, index);
            ControlLinearNode cnPlus1= getControlNodeForSeries(selectedNodes.get(i).series, index+1);
            double gap = cnPlus1.getTime() - cn.getTime();
            if (gap < minGap)
               minGap = gap;
         }
         // minGap is the smallest [positive] distance between a dragged node and its
         // right neighbor (if unselected). dragVector[0] can't be a larger positive
         // number than this value.
         if (dragVector[0] > minGap)
            dragVector[0] = minGap;
      }
   }

   public void dragSelectedNodes(int series, int node, double dragVector[]) {
      cropDragVector(dragVector);
      // Now move all the control points by dragVector.
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode=getControlNodeForSeries(series, index);
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
      if (control != null && node >= 0 && node < getControlNodeCountForSeries(series)) {
         // Make a new point that is offset slightly in the X direction from
         // the point to be duplicated.
         ControlLinearNode controlNode=getControlNodeForSeries(series, node);
         
         double newX = controlNode.getTime() + 0.00001;
         double newY = controlNode.getValue();
         // function, control, series
         functions.get(series).addPoint(newX, newY);
         ControlLinearNode newControlNode = new ControlLinearNode(); // Early garbage collection suspect!
         newControlNode.setTime(newX);
         newControlNode.setValue(newY);
         //getSelectedControlNodes(series).insert(node+1, newControlNode);
         if (series==0)
            control.insertNewValueNode(node+1, newControlNode);
         else if (series==1)
            control.insertNewMinNode(node+1, newControlNode);
         else
            control.insertNewMaxNode(node+1, newControlNode);
             
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         XYSeries dSeries=seriesCollection.getSeries(series);
         dSeries.add(newX, newY);
         
      }
   }

   public void deleteNode(int series, int node) {
      if (control != null && node >= 0 && node < control.getControlValues().getSize()) {
         // node is to be removed from:
         // function, control, series
         functions.get(series).deletePoint(node);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         XYSeries dSeries=seriesCollection.getSeries(series);
         dSeries.delete(node, node);
         getSelectedControlNodes(series).remove(node);
       }
   }

   public void addNode(int series, double x, double y) {
      if (control != null) {
         functions.get(series).addPoint(x, y);
         XYSeriesCollection seriesCollection = (XYSeriesCollection) functionPanel.getChart().getXYPlot().getDataset();
         seriesCollection.getSeries(series).add(x, y);
         // Now the control 
         int idx=seriesCollection.getSeries(series).indexOf(x);
         ControlLinearNode node = new ControlLinearNode();
         node.setTime(x);
         node.setValue(y);
         control.insertNewValueNode(idx, node);
      }
   }

   public void setSelectedNodesToValue(int series, double newValue) {
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         ControlLinearNode controlNode = getControlNodeForSeries(series, index);
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
    
    public void replaceFunction(Function aFunction, int index)
    {
        functions.setElementAt(aFunction, index);
    }
    private ControlLinearNode getControlNodeForSeries(int series, int index)
    { 
         return getSelectedControlNodes(series).get(index);
    }

    private int getControlNodeCountForSeries(int series) {
        return getSelectedControlNodes(series).getSize();
    }
    private SetControlNodes getSelectedControlNodes(int series)
    {
         if (series==0)
             return control.getControlValues();
         else if (series==1)
            return control.getControlMinValues();
         else
            return control.getControlMaxValues();
        
    }
}
