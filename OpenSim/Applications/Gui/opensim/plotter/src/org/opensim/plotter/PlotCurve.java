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
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.Storage;
import org.opensim.view.pub.OpenSimDB;

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
   //private int domainStorageIndex;
   //private int rangeStorageIndex;
   private String domainName;
   private String[] rangeNames;
   private boolean muscleCurve=false;
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
      String localX = stringx;
      String localY = stringy;
      
      if (stringx.contains(":")){   // Strip qualifiers if any
         String[] names=stringx.split(":",-1);
         localX=names[names.length-1];
      }
      // If motion and stringx  = motion name we really mean time
      if (domainSource instanceof PlotterSourceMotion &&
              localX.equalsIgnoreCase(domainSource.getDisplayName())){    // We'really plotting against time'
          localX="time";
      }
      if (stringy.contains(":")){   // Strip qualifiers if any
         String[] names=stringy.split(":",-1);
         localY=names[names.length-1];
      }
      // The following code assumes x, y are parrallel arrays of the same size
      // which should be enforced by the GUI.
      // In case this restriction is removed, rangeStorage will need to be sampled
      // at domain sample values (e.g. plot quantities against time coming from another storage
       ArrayDouble xArray = getDataArrayFromStorage(domainStorage, localX, true, sourcex.convertAngularUnits());
       ArrayDouble yArray = getDataArrayFromStorage(rangeStorage, localY, false, sourcey.convertAngularUnits());
       int xSize = xArray.getSize();
       int ySize = yArray.getSize();
       if (xSize != ySize)
          throw new UnsupportedOperationException("Domain and range sizes are different"+xSize+" vs."+ySize+". An internal bug.");
       
       int size = xArray.getSize();
       // find range of values to display based on minx, maxx
       // this assumes some ordering on x values so that the set of xValues plotted
       // are those at or higher than the first occurance of the value xMin
       // and less than the last occurance of the value xMax.
       int startIndex=xArray.findIndex(plotCurveSettings.getXMin());
       if (startIndex ==-1) // Cut to bounds with data
           startIndex=0;
       int endIndex=xArray.rfindIndex(plotCurveSettings.getXMax());
       if (endIndex ==-1) // Cut to bounds with data
           endIndex=xArray.getSize()-1;
       double[] yFiltered = applyFilters(plotCurveSettings.getFilters(), yArray, startIndex, endIndex);
       // Make an XYSeries to hold the data and keep a ref to it with the curve
       XYSeries curveSeries = new XYSeries(plotCurveSettings.getName(), false, true);
       setCurveSeries(curveSeries);   // user named curves
       for (int i = startIndex;i< endIndex;i++){
           if (i==startIndex)
                System.out.println("Curve"+plotCurveSettings.getName()+xArray.getitem(i)+","+yFiltered[i-startIndex]);
           getCurveSeries().add(xArray.getitem(i),yFiltered[i-startIndex]) ;//add the computed values to the series
       }
       //getCurveSeries().setKey(stringy);  // do not overwrite users specified name
       domainName = new String(stringx);
       String[] names=stringy.split("\\+");
       rangeNames = new String[names.length];
       System.arraycopy(names, 0, rangeNames, 0, names.length);
    }

   private ArrayDouble getDataArrayFromStorage(final Storage storage, final String colName, boolean isDomain, boolean convertAnglesToDegrees ) {
      ArrayDouble Array = new ArrayDouble(storage.getSize());
      if (colName.equalsIgnoreCase("time")){
         storage.getTimeColumnWithStartTime(Array, 0.);
      }
      else{
         String[] colNames=colName.trim().split("\\+",-1);
         ArrayDouble tempArray=null;
         if (colNames.length>1)
              tempArray = new ArrayDouble(storage.getSize());
         for(int i=0; i<colNames.length; i++){
             colNames[i]=colNames[i].trim();
             if (i==0){
                storage.getDataColumn(colNames[i], Array);
                System.out.println("Summation bug process "+colNames[i]);
                 // have to do this before clamoing since clamping is done in degrees
                if (convertAnglesToDegrees)
                    convertAnglesToDegreesIfNeeded(colNames[i], Array);
                if (settings.isClamp())
                  clampDataArray(Array);
                System.out.println("Summation bug "+colNames[i]+" entry after filtering"+Array.getitem(0));
             }
             else { // get data into temporary array and then add it in place
                 storage.getDataColumn(colNames[i], tempArray);
                 System.out.println("Summation bug  process "+colNames[i]+" raw data"+tempArray.getitem(0));
                 if (convertAnglesToDegrees){
                    convertAnglesToDegreesIfNeeded(colNames[i], tempArray);
                    System.out.println("Summation bug  process "+colNames[i]+" after conversion"+tempArray.getitem(0));
                 }
                 if (settings.isClamp()){
                   clampDataArray(tempArray);
                    System.out.println("Summation bug  process "+colNames[i]+" after clamping"+tempArray.getitem(0));
                 }
                System.out.println("Summation bug "+colNames[i]+" add in"+tempArray.getitem(0));
                 for(int row=0;row<storage.getSize();row++){
                     double newValue = Array.getitem(row)+tempArray.getitem(row);
                     Array.set(row, newValue);
                 }
             }
             System.out.println("Summation bug after loop start entry after filtering"+Array.getitem(0));
        }
         /*
         int storageIndex = storage.getStateIndex(colName);
         if (isDomain)
            domainStorageIndex=storageIndex;
         else
            rangeStorageIndex=storageIndex;*/
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

   public PlotCurveSettings getSettings() {
      return settings;
   }

   public Storage getDomainStorage() {
      return domainSource.getStorage();
   }

   public Storage getRangeStorage() {
      return rangeSource.getStorage();
   }
/*
   public int getDomainStorageIndex() {
      return domainStorageIndex;
   }

   public int getRangeStorageIndex() {
      return rangeStorageIndex;
   }
*/
   void update(String title, 
           PlotCurveSettings plotCurveSettings, 
           PlotterSourceInterface sourcex, String namex, 
           PlotterSourceInterface sourcey, String namey){
      settings = plotCurveSettings;
      domainSource=sourcex;
      rangeSource=sourcey;
      Storage domainStorage=domainSource.getStorage();
      Storage rangeStorage=rangeSource.getStorage();
      ArrayDouble xArray = getDataArrayFromStorage(domainStorage, namex, true, domainSource.convertAngularUnits());
      ArrayDouble yArray = getDataArrayFromStorage(rangeStorage, namey, false, rangeSource.convertAngularUnits());
      
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
   
   public void addDataPoint(double x, double y) {
      double yFiltered = applyFilters(settings.getFilters(), y);
      getCurveSeries().add(x, yFiltered) ;//add the computed values to the series
   }
   /**
    * Apply filters to one value instead of an array
    **/
    private double applyFilters(Vector<PlotDataFilter> filters, double y) {
      double[] yArray = new double[]{y};
      double[] returnValues = new double[1];
      returnValues[0]=yArray[0];
      for(int i=0; i<filters.size(); i++)
         returnValues = filters.get(i).convertData(yArray);
        return returnValues[0];
    }
    
    public String getDomainName()
    {        
        return domainName;
        /*ArrayStr labels = domainSource.getStorage().getColumnLabels();
        int sz=labels.getSize();
        return labels.getitem(domainStorageIndex+1);*/
    }
    
    public String[] getRangeNames() // To support sum of items (over muscles for example)
    {
        return rangeNames;
        /*
        ArrayStr labels = rangeSource.getStorage().getColumnLabels();
        return labels.getitem(rangeStorageIndex+1);*/
    }

   private void clampDataArray(ArrayDouble Array) {
      double dmax=settings.getYmax();
      double dmin=settings.getYmin();
      for (int i = 0;i< Array.getSize();i++){
         if (Array.getitem(i)> dmax)
            Array.setitem(i, dmax);
         else if (Array.getitem(i)< dmin)
            Array.setitem(i, dmin);
       }
      
   }

    private void convertAnglesToDegreesIfNeeded(String string, ArrayDouble tempArray) {
        // Check if name is a rotational degree of freedom in current model if so convert
        // every entry in the pased in array of data values, otherwise do nothing.
        CoordinateSet coords= OpenSimDB.getInstance().getCurrentModel().getDynamicsEngine().getCoordinateSet();
        ArrayStr coordinateNames = new ArrayStr();
        coords.getNames(coordinateNames);
        if (coordinateNames.findIndex(string)!=-1){
            // Check if rotational rather than translational
            AbstractCoordinate coord = coords.get(string);
            if (coord.getMotionType() == AbstractDof.DofType.Rotational){
                double conversion = Math.toDegrees(1.0);
                for(int i=0; i<tempArray.getSize(); i++){
                    tempArray.setitem(i, conversion*tempArray.getitem(i));
                }
            }
            else
                return;
        }
    }

}
