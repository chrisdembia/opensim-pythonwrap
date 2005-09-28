package simtkView.plot;

import java.io.*;
import java.util.*;

import simtkCore.*;
import simtkuiEvents.*;

/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: </p>
 * @author Ayman Habib
 * @version 1.0
 * Container for all the data items relevent to a data set to be plotted
 */
public class SimtkPlotDataSet
    implements Observer {
  String _xName;
  String _yName;
  SimtkSimEnv _env;
  String _legend;
  int _dataSetIndexInFigure = -1;
  boolean _timeDependent;
  double _lastTime;
  NmblFigure _figure;
  int _figureIndex;      // index of Figure to shich the dataset will be plotted
  static public final String DEFAULT_LEGEND="Default: x vs. y";

  public SimtkPlotDataSet(SimtkSimEnv env, String xName, String yName, String legend, int figureIndex) {
    this(env, xName, yName);
    if (!legend.equals(DEFAULT_LEGEND) )
      setLegend(legend);
    _figureIndex = figureIndex;
  }

 public SimtkPlotDataSet(SimtkSimEnv env, String xName, String yName) {
    _xName = xName;
    _yName = yName;
    _env = env;
    if (env.isTimeDependent(xName)) {
      _timeDependent = true;
      _env.addObserver(this);
    }
    setLegend(_xName + " vs. " + _yName.substring(_yName.lastIndexOf(":")+1));
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
    _lastTime = _env.getSimulationTime();
    return _env.getDataValues(_xName, _yName, xValues, yValues);
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
    return _env.getDataValues(_xName, _yName, xValues, yValues, _lastTime);
  }

  public void resetTime() {
    _lastTime = 0.0;
  }

  /**
   * update
   *
   * @param o Observable
   * @param arg Object
   */
  public void update(Observable o, Object arg) {
    SimtkSimEnv env = (SimtkSimEnv) o;
    if (arg != null && arg instanceof SimtkSimEnvStateChangeEvent) {
      SimtkSimEnvStateChangeEvent evnt = (SimtkSimEnvStateChangeEvent) arg;
      int oldState = evnt.getOldState();
      int newState = evnt.getNewState();
      if (/*(oldState == SimtkSimEnv.READY ||  oldState == SimtkSimEnv.PLAYBACK) &&*/ newState == SimtkSimEnv.RUNNING) {
        _figure.clear(_dataSetIndexInFigure);
        _lastTime=0.0;
      }
    }
    if (env.getStatus() == SimtkSimEnv.RUNNING) {
      // Find out where the simulation is.
      double time = env.getSimulationTime();
      Vector xValues = new Vector();
      Vector yValues = new Vector();
      getDataValuesSinceTime(xValues, yValues);
      for (int i = 0; i < xValues.size(); i++) {
        double yValue = ( (Double) yValues.get(i)).doubleValue();
        double xValue = ( (Double) xValues.get(i)).doubleValue();
        _figure.addPoint(_dataSetIndexInFigure, xValue, yValue, true);

      }
      _lastTime = time;
      _figure.repaint();
    }
  }


  /**
   * setPlot
   *
   * @param plot Plot
   */
  public void setPlot(NmblFigure plot) {
    _figure = plot;
  }

  public void showPlot()
  {
    Vector xValues = new Vector();
    Vector yValues = new Vector();

    if (getDataValues(xValues, yValues)) {
      boolean first = true;
      for (int i = 0; i < xValues.size(); i++) {
        double yValue = ( (Double) yValues.get(i)).doubleValue();
        double xValue = ( (Double) xValues.get(i)).doubleValue();
        _figure.addPoint(_dataSetIndexInFigure, xValue, yValue, !first);
        first = false;
      }
    }
  }

  /**
   * cleanup
   */
  public synchronized void cleanup() {
    // If a dataSet is time dependent, remove it from env. observers
    if (_timeDependent)
      _env.deleteObserver(this);
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
    fout.println("\t\t\t</plot>");
  }
}
