/*
 * FunctionPlot.java
 *
 * Created on March 27, 2008, 10:01 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CrosshairState;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYItemRendererState;
import org.jfree.data.xy.XYDataset;

/**
 *
 * @author Peter Loan
 */
public class FunctionPlot extends XYPlot {
   
   /** Creates a new instance of FunctionPlot */
   public FunctionPlot() {
      super();
   }

   public FunctionPlot(XYDataset dataset,
                       ValueAxis domainAxis,
                       ValueAxis rangeAxis,
                       XYItemRenderer renderer) {
      super(dataset, domainAxis, rangeAxis, renderer);
   }

   public boolean render(Graphics2D g2,
                         Rectangle2D dataArea,
                         int index,
                         PlotRenderingInfo info,
                         CrosshairState crosshairState) {

      FunctionRenderer renderer = (FunctionRenderer)getRenderer(index);
      XYDataset dataset = getDataset(index);
      ValueAxis xAxis = getDomainAxisForDataset(index);
      ValueAxis yAxis = getRangeAxisForDataset(index);
      XYItemRendererState state = renderer.initialise(g2, dataArea, this, dataset, info);
      renderer.drawFunctions(g2, state, dataArea, this, xAxis, yAxis, dataset, crosshairState);

      return true;
   }
}
