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
 * ExcitationPanel.java
 *
 * Created on March 6, 2008, 12:48 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.util.Collections;
import java.util.Vector;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.modeling.Function;
import org.opensim.modeling.SetControlNodes;
import org.opensim.view.functionEditor.FunctionPanel;
import org.opensim.view.functionEditor.FunctionXYSeries;

/**
 *
 * @author Ayman
 */
public class ExcitationPanel extends FunctionPanel{
    JPopupMenu nodePopup;
    boolean addedExcitationOptionsToPopup=false;
    private boolean hidden=false;
    
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
           if (renderer==null) continue;    //Missing ctrl, min, or max
           ControlLinear cl = renderer.getControl();
           SetControlNodes scn = cl.getControlMaxValues();
           int sz = scn.getSize();
           for (int i=sortedIndices.size()-1; i>=0; i--) {
               int index = sortedIndices.get(i);
               //control.deleteControlNode(index);
               if (series==0)
                    renderer.getControl().getControlValues().remove(index);
               else if (series==1)
                    renderer.getControl().getControlMinValues().remove(index);
               else
                   renderer.getControl().getControlMaxValues().remove(index);
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
   /**
    * Override mouse pressed to handle series
    */
   public void mousePressed(MouseEvent e) {
        super.mousePressed(e);
        if (rightClickNode!=null){
            // get series from selected node and show options for it
            final int selectedSeries = rightClickNode.series;
            // update popups to make them specific to excitations
            nodePopup = getNodePopUpMenu();
            if (!addedExcitationOptionsToPopup){
                JMenuItem useStepsMenuItem = new JMenuItem("use steps (toggle)");
                useStepsMenuItem.addActionListener(new ActionListener(){
                    public void actionPerformed(ActionEvent e) {
                        // Get the function # selectedSeries, toggle the use_steps flag, update function display
                        XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();

                        ExcitationRenderer renderer = (ExcitationRenderer) getChart().getXYPlot().getRenderer(selectedSeries);
                        // Current value of use_steps
                        boolean useStepsFlag = renderer.getControl().getUseSteps();
                        renderer.getControl().setUseSteps(!useStepsFlag);
                        // update he functions
                        SetControlNodes cnodes = renderer.getControl().getControlValues();
                        XYSeries ser=seriesCollection.getSeries(selectedSeries);
                        ser.clear();
                        Function ctrlFunction = 
                                ExcitationEditorJPanel.createFunctionFromControlLinear((FunctionXYSeries) ser, cnodes, renderer.getControl(), !renderer.getControl().getUseSteps());
                        renderer.getFunctionList().set(selectedSeries, ctrlFunction);
                    }
                });
                nodePopup.add(useStepsMenuItem);
                addedExcitationOptionsToPopup=true;
            }
        }
   }

    public boolean isCollapsed() {
        return hidden;
    }

    public void setCollapsed(boolean hidden) {
        this.hidden = hidden;
    }
    
}
