package org.opensim.plot;

import java.io.*;
import java.util.*;

/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * Copyright (c)  2005</p>
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
public class PlotDataSet {
  String _xName;
  String _yName;
  String _legend;
  int _dataSetIndexInFigure = -1;
  boolean _timeDependent;
  double _lastTime;
  OpenSimFigure _figure;
  int _figureIndex;      // index of Figure to which the dataset will be plotted
  static public final String DEFAULT_LEGEND="Default: x vs. y";
  boolean _connect;
  String _marks;
  ArrayList _dataFilters = new ArrayList();

  public PlotDataSet(String xName, String yName, String legend, int figureIndex, boolean connect, String marks) {
    this(xName, yName, connect, marks);
    if (!legend.equals(DEFAULT_LEGEND) )
      setLegend(legend);
    _figureIndex = figureIndex;
  }

 public PlotDataSet(String xName, String yName, boolean connect, String marks) {
    _xName = xName;
    _yName = yName;

    setLegend(_xName + " vs. " + _yName.substring(_yName.lastIndexOf(":")+1));
    _connect = connect;
    _marks = marks;
  }

  /**
   * setLegend
   *
   * @param string String
   */
  public void setLegend(String string) {
    _legend = string;
  }

  public String getLegend() {
    return _legend;
  }

  public boolean isTimeDependent() {
    return _timeDependent;
  }

  public int getFigureIndex() {
    return _figureIndex;
  }
  public void setDataSetIndex(int index) {
    _dataSetIndexInFigure = index;
  }

  public int getDataSetIndex() {
    return _dataSetIndexInFigure;
  }

  public boolean getDataValues(Vector xValues, Vector yValues) {

    return false;
  }

  /**
   * getDataValuesSinceTime
   *
   * @param _lastTime double
   * @param xValues Vector
   * @param yValues Vector
   */
  public boolean getDataValuesSinceTime(Vector xValues,
                                        Vector yValues) {
    return false;
  }

  public void resetTime() {
    _lastTime = 0.0;
  }



  /**
   * setPlot
   *
   * @param plot Plot
   */
  public void setPlot(OpenSimFigure plot) {
    _figure = plot;
  }

  public void showPlot()
  {
    Vector xValues = new Vector();
    Vector yValues = new Vector();

    if (getDataValues(xValues, yValues)) {
      boolean first = true;
      _figure.setMarksStyle(_marks, _dataSetIndexInFigure);
      double[] yData = getRawData(yValues);
      yData = applyFiltersToData(yData);
      for (int i = 0; i < xValues.size(); i++) {
        double xValue = ( (Double) xValues.get(i)).doubleValue();
        double yValue = yData[i];
        _figure.addPoint(_dataSetIndexInFigure, xValue, yValue, _connect?(!first):false);
        first = false;
      }
    }
  }

  /**
   * getRawData
   *
   * @param yValues Vector
   * @return double[]
   */
  private double[] getRawData(Vector yValues) {
    double[] toReturn = new double[yValues.size()];
    for(int i=0; i < yValues.size(); i++)
      toReturn[i] = ((Double)yValues.get(i)).doubleValue();
    return toReturn;
  }

  /**
   * cleanup
   */
  public synchronized void cleanup() {
    // If a dataSet is time dependent, remove it from env. observers
  }

  /**
   * Encode
   *
   * @return String
   */
  public String Encode() {
    return "[Fig. "+(_figureIndex+1)+"]."+_legend;
  }

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout) {
    fout.println("\t\t\t<plot>");
    fout.println("\t\t\t<qty xName=\"" + _xName + "\" yName=\""+_yName+"\"/>");
    fout.println("\t\t\t<legend value=\"" + _legend + "\"/>");
    for (int i=0; i < _dataFilters.size(); i++){
      PlotDataFilter nextFilter = (PlotDataFilter) _dataFilters.get(i);
      nextFilter.write(fout);
    }
    fout.println("\t\t\t</plot>");
  }
  public void addFilter(PlotDataFilter aFilter)
  {
    _dataFilters.add(aFilter);
  }
  public double[] applyFiltersToData(double[] data)
  {
    double[]  xformed = new double[data.length];
    System.arraycopy(data, 0, xformed, 0, data.length);
    for (int i=0; i < _dataFilters.size(); i++){
      PlotDataFilter nextFilter = (PlotDataFilter) _dataFilters.get(i);
      xformed = nextFilter.convertData(xformed);
    }
    return xformed;
  }
}
