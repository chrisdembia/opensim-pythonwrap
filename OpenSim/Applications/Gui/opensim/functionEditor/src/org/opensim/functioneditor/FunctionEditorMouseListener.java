/*
 * FunctionEditorMouseListener.java
 *
 * Created on October 25, 2007, 4:39 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.functioneditor;

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.geom.Rectangle2D;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.RectangleEdge;
import org.opensim.modeling.Function;

/**
 *
 * @author Peter Loan
 */
public class FunctionEditorMouseListener implements MouseListener {
   private ChartPanel chartPanel;
   private Function function;

   /** Creates a new instance of FunctionEditorMouseListener */
   public FunctionEditorMouseListener(ChartPanel chartPanel, Function function) {
      this.chartPanel=chartPanel;
      this.function = function;
      chartPanel.addMouseListener(this);
   }

   public void mouseClicked(MouseEvent e) {
      int x=e.getX();
      int y=e.getY();
      // handleClick only serves to locate the Corosshair Values to convert from 
      // Java2D space to data space.
      int mask=e.getModifiers();
      if ((mask & e.CTRL_MASK) !=0){    // Show query only if CTRL button is held down
         XYPlot xyPlot = chartPanel.getChart().getXYPlot();
         XYDataset xyDataset = xyPlot.getDataset();
         chartPanel.getChart().handleClick(x, y, chartPanel.getChartRenderingInfo());
         double dataX = chartPanel.getChart().getXYPlot().getDomainCrosshairValue();
         double dataY = chartPanel.getChart().getXYPlot().getRangeCrosshairValue();
         RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
         RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
         Rectangle2D dataArea = chartPanel.getScreenDataArea();
         for (int i=0; i<xyDataset.getItemCount(0); i++) {
            double sx = xyPlot.getDomainAxis().valueToJava2D(xyDataset.getXValue(0, i), dataArea, xAxisLocation);
            double sy = xyPlot.getRangeAxis().valueToJava2D(xyDataset.getYValue(0, i), dataArea, yAxisLocation);
            double distance = Math.sqrt((sx-x)*(sx-x) + (sy-y)*(sy-y));
            if (distance < 6.0) {
                //String text = String.valueOf(i);
                //xyPlot.addAnnotation(new XYTextAnnotation(text, xyDataset.getXValue(0, i), xyDataset.getYValue(0, i)));
                FunctionEditorTopComponent.findInstance().updateSelectedNodes(i);
                break;
            }
         }
         //String annotationText = String.format("(%1$f, %2$f)", dataX, dataY);
         //chartPanel.getChart().getXYPlot().addAnnotation(new XYTextAnnotation(annotationText, dataX, dataY));
      }
   }

   public void mousePressed(MouseEvent e) {
   }

   public void mouseReleased(MouseEvent e) {
   }

   public void mouseEntered(MouseEvent e) {
   }

   public void mouseExited(MouseEvent e) {
   }
}
