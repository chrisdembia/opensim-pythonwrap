/*
 *
 * Plot
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

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author Ayman
 */
public class Plot {
   
   XYSeriesCollection    seriesCollection=null; // All data plotted in this figure
   private ChartPanel chartPanel=null;
   String         xLabel, yLabel;
   JFreeChart     dChart=null;
   private boolean        enableToolTips; // Normally on but for dynamic plots while updating
   /**
    * Creates a new instance of Plot
    */
   public Plot(String title, String xLabel, String yLabel) {
      // Make blank plot
      this.xLabel=xLabel;
      this.yLabel=yLabel;
      
      seriesCollection =new XYSeriesCollection();
      dChart = ChartFactory.createXYLineChart(
              title,
              xLabel,
              yLabel,
              seriesCollection,
              org.jfree.chart.plot.PlotOrientation.VERTICAL,
              true,
              true,
              false);
      
      chartPanel = new ChartPanel(dChart);
      
      XYPlot plot = (XYPlot) dChart.getPlot();
      plot.setDomainCrosshairVisible(true);
      plot.setRangeCrosshairVisible(true);
      
      XYItemRenderer r = plot.getRenderer();
      if (r instanceof XYLineAndShapeRenderer) {
         XYLineAndShapeRenderer renderer = (XYLineAndShapeRenderer) r;
         renderer.setBaseShapesVisible(false);
         renderer.setBaseShapesFilled(false);
      }
      new JOpenSimChartMouseListener(chartPanel);
      chartPanel.setDisplayToolTips(true);
      chartPanel.setInitialDelay(0);
      
   }

   void add(PlotCurve newCurve) {
      String legend = newCurve.getLegend();      
      seriesCollection.addSeries(newCurve.getCurveSeries());
   }

   private boolean checkUniqueCurveName(final String newCurveName) {
      // Check that name is not a duplicate
      boolean isUnique = true;
      for(int i=0;i<seriesCollection.getSeriesCount() && isUnique;i++){
         XYSeries ser = seriesCollection.getSeries(i);
         if (((String)ser.getKey()).compareTo(newCurveName)==0)
            isUnique=false;
      }
      return isUnique;
   }

   public ChartPanel getChartPanel() {
      return chartPanel;
   }
   
   /**
    * Display name for the figure
    */
   public String getTitle() {
      return dChart.getTitle().getText();
   }

   public void setTitle(String title) {
      dChart.setTitle(title);
   }

   void deleteCurve(PlotCurve cvToDelete) {
      seriesCollection.removeSeries(cvToDelete.getCurveSeries());
   }

   public boolean isEnableToolTips() {
      return enableToolTips;
   }

   public void setEnableToolTips(boolean enableToolTips) {
      this.enableToolTips = enableToolTips;
   }

   void setDomainCrosshair(double time) {
      chartPanel.getChart().getXYPlot().setDomainCrosshairValue(time);
   }
   
}
