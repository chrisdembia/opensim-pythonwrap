/*
 *
 * JOpenSimChartMouseListener
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.plotter;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.annotations.XYTextAnnotation;

/**
 *
 * @author Ayman
 */
public class JOpenSimChartMouseListener implements MouseListener {
   ChartPanel chartPanel;
   /** Creates a new instance of JOpenSimChartMouseListener */
   public JOpenSimChartMouseListener(ChartPanel chartPanel) {
      this.chartPanel=chartPanel;
      chartPanel.addMouseListener(this);
   }

   public void mouseClicked(MouseEvent e) {
      int x=e.getX();
      int y=e.getY();
      // handleClick only serves to locate the Corosshair Values to convert from 
      // Java2D space to data space.
      int mask=e.getModifiers();
      if ((mask & e.CTRL_MASK) !=0){    // Show query only if CTRL button is held down
          chartPanel.getChart().handleClick(x, y, chartPanel.getChartRenderingInfo());
          double dataX = chartPanel.getChart().getXYPlot().getDomainCrosshairValue();
          double dataY = chartPanel.getChart().getXYPlot().getRangeCrosshairValue();
          //%[argument_index$][flags][width][.precision]conversion
          String annotationText = String.format("(%1$f, %2$f)", dataX, dataY);
          chartPanel.getChart().getXYPlot().addAnnotation(new XYTextAnnotation(annotationText, dataX, dataY));
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
