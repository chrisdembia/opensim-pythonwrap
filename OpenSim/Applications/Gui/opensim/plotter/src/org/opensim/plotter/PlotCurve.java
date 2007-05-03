/*
 *
 * PlotCurve
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
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman
 */
public class PlotCurve {
   
   JFreeChart   dChart=null;
   private XYSeries    curveSeries=null;
   private boolean      timeDependent=false;
   private PlotCurveSettings    settings;
   // Source for domain, range needed so that display name (including file can be reconstructed)
   private PlotterSourceInterface domainSource;
   private PlotterSourceInterface rangeSource;
   private int domainStorageIndex;
   private int rangeStorageIndex;
   /**
    * Creates a new instance of PlotCurve
    */
   public PlotCurve(PlotCurveSettings plotCurveSettings, 
           PlotterSourceInterface sourcex, String stringx, 
           PlotterSourceInterface sourcey, String stringy) {
      settings = plotCurveSettings;
      domainSource=sourcex;
      rangeSource=sourcey;
      Storage domainStorage=sourcex.getStorage();
      Storage rangeStorage=sourcey.getStorage();
      ArrayDouble xArray = getDataArrayFromStorage(domainStorage, stringx, true);
      ArrayDouble yArray = getDataArrayFromStorage(rangeStorage, stringy, false);
      
       int size = xArray.getSize();
      // find range of values to display based on minx, maxx
      int startIndex=xArray.findIndex(plotCurveSettings.getXMin());
      if (startIndex ==-1) // Cut to bounds with data
         startIndex=0;
      int endIndex=xArray.rfindIndex(plotCurveSettings.getXMax());
      if (endIndex ==-1) // Cut to bounds with data
         endIndex=yArray.getSize()-1;
      
      //System.out.println("Pre-filtering data first,last="+yArray.getitem(startIndex)+", "+yArray.getitem(endIndex));
      double[] yFiltered = applyFilters(plotCurveSettings.getFilters(), yArray, startIndex, endIndex);
     // Make an XYSeries to hold the data and keep a ref to it with the curve
      setCurveSeries(new XYSeries(plotCurveSettings.getName()));
      for (int i = startIndex;i< endIndex;i++){
           getCurveSeries().add(xArray.getitem(i),yFiltered[i-startIndex]) ;//add the computed values to the series
       }
   }

   private ArrayDouble getDataArrayFromStorage(final Storage storage, final String colName, boolean isDomain ) {
      ArrayDouble Array = new ArrayDouble(storage.getSize());
      if (colName.equalsIgnoreCase("time")){
         storage.getTimeColumn(Array, 0.);
         if (isDomain)
            domainStorageIndex=-1;
         else
            rangeStorageIndex=-1;
      }
      else{
         storage.getDataColumn(colName, Array);
         int storageIndex = storage.getStateIndex(colName);
         if (isDomain)
            domainStorageIndex=storageIndex;
         else
            rangeStorageIndex=storageIndex;
      }
      return Array;
   }

   public XYSeries getCurveSeries() {
      return curveSeries;
   }

   public void setCurveSeries(XYSeries curveSeries) {
      this.curveSeries = curveSeries;
   }

   public String getLegend() {
      return (String) curveSeries.getKey();
   }

   public void setLegend(String legend) {
      curveSeries.setKey(legend);
   }
   
   /**
    * Apply sequence of filters to passed in yArray in the range between start & end inclusive
    */
   private double[] applyFilters(Vector<PlotDataFilter> filters, ArrayDouble yArray, int start, int end) {
      double[] returnValues = new double[end-start+1];
      
      // Copy portion of interest from yArray into returnValues
      for(int i=start; i<end; i++){
         returnValues[i-start]=yArray.getitem(i);
      }
      
      // Now apply the filters
      for(int i=0; i<filters.size(); i++)
         returnValues = filters.get(i).convertData(returnValues);
      
      return returnValues;
   }

   public boolean isTimeDependent() {
      return timeDependent;
   }

   public void setTimeDependent(boolean timeDependent) {
      this.timeDependent = timeDependent;
   }

   public PlotCurveSettings getSettings() {
      return settings;
   }

   public Storage getDomainStorage() {
      return domainSource.getStorage();
   }

   public Storage getRangeStorage() {
      return rangeSource.getStorage();
   }

   public int getDomainStorageIndex() {
      return domainStorageIndex;
   }

   public int getRangeStorageIndex() {
      return rangeStorageIndex;
   }

   void update(String title, 
           PlotCurveSettings plotCurveSettings, 
           PlotterSourceInterface sourcex, String namex, 
           PlotterSourceInterface sourcey, String namey) throws PlotterException {
      settings = plotCurveSettings;
      domainSource=sourcex;
      rangeSource=sourcey;
      Storage domainStorage=domainSource.getStorage();
      Storage rangeStorage=rangeSource.getStorage();
      ArrayDouble xArray = getDataArrayFromStorage(domainStorage, namex, true);
      ArrayDouble yArray = getDataArrayFromStorage(rangeStorage, namey, false);
      
      // Make an XYSeries to hold the data
      setLegend(plotCurveSettings.getName());
      int size = xArray.getSize();
      // find range of values to display based on minx, maxx
      int startIndex=xArray.findIndex(plotCurveSettings.getXMin());
      if (startIndex ==-1) // Cut to bounds with data
         startIndex=0;
      int endIndex=xArray.rfindIndex(plotCurveSettings.getXMax());
      if (endIndex ==-1) // Cut to bounds with data
         endIndex=yArray.getSize()-1;
      
      //System.out.println("Pre-filtering data first,last="+yArray.getitem(startIndex)+", "+yArray.getitem(endIndex));
      double[] yFiltered = applyFilters(plotCurveSettings.getFilters(), yArray, startIndex, endIndex);
      getCurveSeries().clear();
      for (int i = startIndex;i< endIndex;i++){
           getCurveSeries().add(xArray.getitem(i),yFiltered[i-startIndex]) ;//add the computed values to the series
       }
   }

   PlotterSourceInterface getDomainSource() {
      return domainSource;
   }
   
   PlotterSourceInterface getRangeSource() {
      return rangeSource;
   }
   
}
