/*
 *
 * PlotCurveSettings
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

import java.util.Vector;
import org.opensim.modeling.ArrayDouble;
import org.opensim.plotter.JPlotterPanel;
/**
 *
 * @author Ayman
 */
public class PlotCurveSettings {
   private String name;
   private double xMin=0.0;
   private double xMax=1.0;
   private double scale=1.0;
   private double offset=0.0;
   private boolean rectify=false;
   private boolean clamp=false;
   private double ymin=0.0;
   private double ymax=1.0;
   private String xLabel, yLabel;
   private Vector<PlotDataFilter> filters = new Vector<PlotDataFilter>(4);
   private boolean musclePlot=false;
   
   /** Creates a new instance of PlotCurveSettings */
   public PlotCurveSettings(JPlotterPanel plotterFrame) {
      setName(plotterFrame.getCurveName());
      setXMin(plotterFrame.getMinX());
      setXMax(plotterFrame.getMaxX());
      boolean rectify = plotterFrame.getRectify();
       
      if (rectify)
         filters.add(new PlotRectifyFilter());
      if (plotterFrame.isClamp()){
         ymin=plotterFrame.getMinY();
         ymax=plotterFrame.getMaxY();
         clamp=true;
      }
      setMusclePlot(plotterFrame.isBuiltinMuscleCurve());
   }

   public String getName() {
      return name;
   }

   public void setName(String name) {
      this.name = name;
   }


   public double getXMin() {
      return xMin;
   }

   public void setXMin(double xMin) {
      this.xMin = xMin;
   }

   public double getXMax() {
      return xMax;
   }

   public void setXMax(double xMax) {
      this.xMax = xMax;
   }

   public double getScale() {
      return scale;
   }

   public void setScale(double scale) {
      this.scale = scale;
   }

   public double getOffset() {
      return offset;
   }

   public void setOffset(double offset) {
      this.offset = offset;
   }

   public boolean isRectify() {
      return rectify;
   }

   public void setRectify(boolean rectify) {
      this.rectify = rectify;
   }

   String getXLabel() {
      return xLabel;
   }

   String getYLabel() {
      return yLabel;
   }

   public void setXLabel(String xLabel) {
      this.xLabel = xLabel;
   }

   public void setYLabel(String yLabel) {
      this.yLabel = yLabel;
   }

   Vector<PlotDataFilter> getFilters() {
      return filters;
   }

    public boolean isMusclePlot() {
        return musclePlot;
    }

    public void setMusclePlot(boolean musclePlot) {
        this.musclePlot = musclePlot;
    }

   public boolean isClamp() {
      return clamp;
   }

   public double getYmin() {
      return ymin;
   }

   public double getYmax() {
      return ymax;
   }
   
}
