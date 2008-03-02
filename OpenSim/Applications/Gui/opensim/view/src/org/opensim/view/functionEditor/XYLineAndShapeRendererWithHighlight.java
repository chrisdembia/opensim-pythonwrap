/*
 * XYLineAndShapeRendererWithHighlight.java
 *
 * Created on February 13, 2008, 3:39 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;

/**
 *
 * @author Ayman
 */
public abstract class XYLineAndShapeRendererWithHighlight extends XYLineAndShapeRenderer {
    
    /** Creates a new instance of XYLineAndShapeRendererWithHighlight */
    public XYLineAndShapeRendererWithHighlight() {
    }
    abstract public void highlightNode(int function, int point) ;

    abstract public void unhighlightNode(int function, int point) ;
    
}
