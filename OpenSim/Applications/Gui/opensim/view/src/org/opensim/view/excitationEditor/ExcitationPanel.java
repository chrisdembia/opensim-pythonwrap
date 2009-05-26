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

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.io.IOException;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.Axis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.event.AxisChangeEvent;
import org.jfree.chart.event.AxisChangeListener;
import org.jfree.data.Range;
import org.jfree.data.general.SeriesChangeEvent;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.modeling.Function;
import org.opensim.modeling.LinearFunction;
import org.opensim.modeling.SetControlNodes;
import org.opensim.modeling.Storage;
import org.opensim.utils.DialogUtils;
import org.opensim.utils.FileUtils;
import org.opensim.utils.OpenSimDialog;
import org.opensim.view.functionEditor.FunctionPanel;
import org.opensim.view.functionEditor.FunctionPanelListener;
import org.opensim.view.functionEditor.FunctionXYSeries;

/**
 *
 * @author Ayman
 */
public class ExcitationPanel extends FunctionPanel{
    JPopupMenu nodePopup;
    boolean addedExcitationOptionsToPopup=false;
    //boolean addedImportOptionsToPopup=false;
    private boolean collapsed=false;
    ControlLinear backup;
    private boolean changed = false;    // Whenever something is changed we need to turn this flag on so that revert works while Backup clears it. 
    private ExcitationRenderer renderer = null;
    
    /** Creates a new instance of ExcitationPanel */
   public ExcitationPanel(JFreeChart chart) {
      super(chart);
      chart.getXYPlot().getDomainAxis().setAutoRangeMinimumSize(0.0001);
      chart.getXYPlot().getRangeAxis().setAutoRangeMinimumSize(0.0001);
      renderer = (ExcitationRenderer)chart.getXYPlot().getRenderer(0);
      backup = new ControlLinear(renderer.getControl());    // Keep copy of contents incase user restores
      chart.getXYPlot().getRangeAxis().setRangeWithMargins(new Range(renderer.getControl().getDefaultParameterMin(),
              renderer.getControl().getDefaultParameterMax()));
      chart.getXYPlot().getRangeAxis().setAutoRange(false);
      chart.getXYPlot().getRangeAxis().addChangeListener(new EnforceExcitationRange());

      updateAddNodePopUpMenu();
    }
    
   public void deleteSelectedNodes()
   {
      // Deleting nodes is handled by FunctionPanel, but ExcitationPanel
      // needs to know if any nodes were deleted, so it can set its 'changed' flag.
      int num = selectedNodes.size();
      super.deleteSelectedNodes();
      if (selectedNodes.size() < num)
         setChanged(true);
   }
   
   public void setSelectedNodesToValue(int series, double newValue) {
      if (renderer == null || !renderer.getSeriesShapesVisible(series))
         return;
      // Make sure we cant set values outside range using this backdoor
      if (renderer.getControl().getDefaultParameterMin() > newValue ||
              renderer.getControl().getDefaultParameterMax() < newValue){
          // Trying to set value outside range: ignore
          return;
      }
      for (int i=0; i<selectedNodes.size(); i++) {
         int selIndex = selectedNodes.get(i).node;
         int selSeries = selectedNodes.get(i).series;
         if (selSeries == series) {
            ControlLinearNode controlNode = renderer.getControl().getControlValues().get(selIndex);
            double newX = controlNode.getTime();
            double newY = newValue;
            controlNode.setTime(newX);
            controlNode.setValue(newY);
            // Update underlying function
            renderer.setSeriesPointXY(selSeries, selIndex, newX, newY);
            XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();
            seriesCollection.getSeries(selSeries).getDataItem(selIndex).setY(newY);
            seriesCollection.getSeries(selSeries).fireSeriesChanged();
         }
      }
      setChanged(true);
       
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
                        // Current value of use_steps
                        boolean useStepsFlag = renderer.getControl().getUseSteps();
                        renderer.getControl().setUseSteps(!useStepsFlag);
                        update(selectedSeries);
                        setChanged(true);
                    }
                });
                nodePopup.add(useStepsMenuItem);
                addedExcitationOptionsToPopup=true;
            }
        } 
   }
   
   public void update()
   {
       XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();
       for (int i=0; i<seriesCollection.getSeriesCount(); i++)
            update(i);
   }
   /**
    * Update a series displayed in the excitationPanel corresponding to passed in index
    */
   public void update(int series)
   {
        XYSeriesCollection seriesCollection = (XYSeriesCollection) getChart().getXYPlot().getDataset();

        ExcitationRenderer renderer = (ExcitationRenderer) getChart().getXYPlot().getRenderer();
        // Current value of use_steps
        //boolean useStepsFlag = renderer.getControl().getUseSteps();
        //renderer.getControl().setUseSteps(!useStepsFlag);
        // update he functions
        if (renderer==null)
            return;
        SetControlNodes cnodes=null;
        if (series==0)
            cnodes = renderer.getControl().getControlValues();
        else if (series==1)
            cnodes=renderer.getControl().getControlMinValues();
        else
            cnodes=renderer.getControl().getControlMaxValues();
        
        XYSeries ser=seriesCollection.getSeries(series);
        ser.clear();
        // RenderingInfo keeps stale refs need to be removed from the Chart
        Function ctrlFunction = null;
        if (series==0)
             ctrlFunction=ExcitationEditorJPanel.createFunctionFromControlLinear((FunctionXYSeries) ser, 
                     cnodes, !renderer.getControl().getUseSteps());
        else
             ctrlFunction=ExcitationEditorJPanel.createFunctionFromControlLinear((FunctionXYSeries) ser, 
                     cnodes, true);
        renderer.replaceFunction(series, ctrlFunction);
        
        // The following is a hack adopted from the FunctionPanel to nvoke methods on listeners directly instead of using events!!
        Object[] listeners = functionPanelListeners.getListenerList();
        for (int i = listeners.length - 2; i >= 0; i -= 2) {
            if (listeners[i] == FunctionPanelListener.class) {
                ((ExcitationPanelListener) listeners[i + 1]).replaceFunction(ctrlFunction, series);
            }
        }
        seriesCollection.seriesChanged(new SeriesChangeEvent(this));
        setChanged(true);
       
   }

    public boolean isCollapsed() {
        return collapsed;
    }

    public void setCollapsed(boolean coll) {
        this.collapsed = coll;
    }

    public boolean isChanged() {
        return changed;
    }

    public void setChanged(boolean changed) {
        this.changed = changed;
    }
    
    public String getControlName()
    {
        return (renderer.getControl().getName());
    }
    // Check that a point is under a function, to be used by min/max/value error-checking
    public void backup()
    {
        if (isChanged()){
            ExcitationRenderer renderer = (ExcitationRenderer) getChart().getXYPlot().getRenderer();
            backup = new ControlLinear(renderer.getControl());
            update();
        }
    }
    public void restore()
    {
        if (isChanged()){
            //ControlLinear restored = new ControlLinear(backup);
            renderer.getControl().copyData(backup);
            
            Object[] listeners = functionPanelListeners.getListenerList();
            for (int i = listeners.length - 2; i >= 0; i -= 2) {
                if (listeners[i] == FunctionPanelListener.class) {
                    ((ExcitationPanelListener) listeners[i + 1]).setControl(renderer.getControl());
                }
            }
            update();
            setChanged(false);
        }
    }

    void showBaseShape(int series, boolean b) {
      if (renderer==null)
          return;
      renderer.setSeriesShapesVisible(series, b);
    }

    void toggleMinMaxShading(boolean b) {
      if (renderer==null)
          return;
      if (b)
         renderer.setFillMode(ExcitationRenderer.ExcitationFillMode.MIN_MAX);
      else
         renderer.setFillMode(ExcitationRenderer.ExcitationFillMode.NONE);
    }

    public void mouseReleased(MouseEvent e) {
        super.mouseReleased(e);
    }

    private void updateAddNodePopUpMenu() {
        addNodePopUpMenu.removeAll();
        String[] seriesNames = new String[]{"Max", "Excitation", "Min"};
        int[] seriesNumbers = new int[]{2, 0, 1};
        for(int i=0; i<3; i++){
            JMenuItem nextAddMenuItem = new JMenuItem("Add Control Point to "+seriesNames[i]);
            final int idx=seriesNumbers[i];
            nextAddMenuItem.addActionListener(new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    int locX = getRightClickX();
                    int locY = getRightClickY();
                    // This handles the series and function
                    int newNodeIndex = addNode(idx, locX, locY);                    
                }
            });
            addNodePopUpMenu.add(nextAddMenuItem);
        }
        addNodePopUpMenu.addSeparator();
        // Add item for importing data curve into Panel
        JMenuItem overlayMenuItem = new JMenuItem("Import data from a file");
        overlayMenuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                // Browse for a file, then show curve selection filter
                String fileName = FileUtils.getInstance().browseForFilename(".sto, .mot", "Data file", ExcitationPanel.this);
                if (fileName==null) return; // No file was selected
                Storage s=null;
                try {
                    s = new Storage(fileName);
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                if (s == null) return;  // Bad file
                // Open file and show filter to select columns. Return names
                FilterableStringArray namesSource = new FilterableStringArray(s.getColumnLabels());
                NameFilterJPanel filterPanel = new NameFilterJPanel(namesSource, false);
                OpenSimDialog selectionDlg=DialogUtils.createDialogForPanelWithParent(null, filterPanel, "Select Columns");
                DialogUtils.addStandardButtons(selectionDlg);
                selectionDlg.setModal(true);
                selectionDlg.setVisible(true);
                if (selectionDlg.getDialogReturnValue()==selectionDlg.OK_OPTION) {
                    String[] selNames = new String[filterPanel.getNumSelected()];
                    System.arraycopy(filterPanel.getSelected(), 0, selNames, 0, filterPanel.getNumSelected());
                    // create a curve against time for each selected column and add it to tthe chart
                    ArrayDouble times = new ArrayDouble();
                    s.getTimeColumn(times);
                    Function f = new LinearFunction();
                    for(int i=0; i<selNames.length;i++ ){
                        XYSeries nextCurve=new XYSeries(selNames[i]);
                        ArrayDouble data = new ArrayDouble();
                        int index = s.getStateIndex(selNames[i]);
                        s.getDataColumn(index, data);
                        for(int j=0; j<data.getSize(); j++){
                            nextCurve.add(times.getitem(j), data.getitem(j), false);
                            f.addPoint(times.getitem(j), data.getitem(j));
                            //System.out.println("index="+j+" data="+data.getitem(j)+ " at time="+times.getitem(j));
                        }
                        ((XYSeriesCollection)getChart().getXYPlot().getDataset()).addSeries(nextCurve);
                        ExcitationRenderer renderer = (ExcitationRenderer)getChart().getXYPlot().getRenderer(0);
                        renderer.addFunction(f, false);
                    }
                }
            }
        });
        addNodePopUpMenu.add(overlayMenuItem);
    }
    class EnforceExcitationRange implements AxisChangeListener {
        public void axisChanged(AxisChangeEvent event) {
            Axis axis = event.getAxis();
            if (axis instanceof ValueAxis) {
                ValueAxis va = (ValueAxis)axis;
                if (va.isAutoRange()) {
                    va.setAutoRange(false);
                    va.setRangeWithMargins(new Range(renderer.getControl().getDefaultParameterMin(),
              renderer.getControl().getDefaultParameterMax()));;
                }
            }
        }
    }
}
