/*
 * ExcitationObject.java
 *
 * Created on February 5, 2008, 5:10 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 *
 */

package org.opensim.view.excitationEditor;

import java.awt.BasicStroke;
import java.awt.Color;
import javax.swing.tree.DefaultMutableTreeNode;
import org.jfree.chart.plot.Plot;
import org.opensim.view.functionEditor.FunctionPanel;

/**
 *
 * @author Ayman. A class made up to represent a node in the tree of excitations 
 * on the left of the Excitation Editor
 */
public class ExcitationObject extends DefaultMutableTreeNode{
    
    FunctionPanel excitationPanel;
    String name;
    /**
     * Creates a new instance of ExcitationObject
     */
    public ExcitationObject(FunctionPanel aPlot, String name) {
        this.excitationPanel = aPlot;
        this.name = name;
    }
    
    public String toString()
    {
       String filtered = name;
       if (filtered.contains(".")){
           filtered = filtered.substring(0, name.indexOf('.')); 
       }
       return filtered;
    }
    
    FunctionPanel getPlotPanel()
    {
        return excitationPanel;
    }
    
    void markSelected(Boolean select)
    {
        Plot plot = excitationPanel.getChart().getPlot();
        if (select){            
            plot.setOutlinePaint(Color.RED);
            plot.setOutlineStroke(new BasicStroke(4.0f));
        }
        else {
            plot.setOutlinePaint(Color.GRAY);
            plot.setOutlineStroke(new BasicStroke(1.0f));
           
        }
    }
}
