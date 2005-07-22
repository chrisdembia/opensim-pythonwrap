package simtkView.plot;

import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import ptolemy.plot.Plot;
import simtkCore.SimtkSimEnv;
import simtkuiEvents.SimtkSimEnvStateChangeEvent;

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
  String _storageName;
  int _dataSetIndex = -1;
  boolean _timeDependent;
  double _lastTime;
  Plot _plot;

  public SimtkPlotDataSet(SimtkSimEnv env, String xName, String yName) {
    _xName = xName;
    _yName = yName;
    _env = env;
    if (env.isTimeDependent(xName)) {
      _timeDependent = true;
      _env.addObserver(this);
    }
  }

  public String getLegend() {
    return _xName + " vs. " + _yName.substring(_yName.lastIndexOf(":")+1);
  }

  public boolean isTimeDependent() {
    return _timeDependent;
  }

  public void setDataSetIndex(int index) {
    _dataSetIndex = index;
  }

  public int getDataSetIndex() {
    return _dataSetIndex;
  }

  public boolean getDataValues(Vector xValues, Vector yValues) {
    _lastTime = _env.getAnimationCallback().getCurrentTime();
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
      if (/*(oldState == SimtkSimEnv.READY ||  oldState == SimtkSimEnv.PLAYBACK) &&*/ newState == SimtkSimEnv.STARTED) {
        _plot.clear(_dataSetIndex);
        _lastTime=0.0;
      }
    }
    if (env.getStatus() == SimtkSimEnv.STARTED) {
      // Find out where the simulation is.
      double time = env.getAnimationCallback().getCurrentTime();
      Vector xValues = new Vector();
      Vector yValues = new Vector();
      getDataValuesSinceTime(xValues, yValues);
      for (int i = 0; i < xValues.size(); i++) {
        double yValue = ( (Double) yValues.get(i)).doubleValue();
        double xValue = ( (Double) xValues.get(i)).doubleValue();
        _plot.addPoint(_dataSetIndex, xValue, yValue, true);

      }
      _lastTime = time;
      _plot.repaint();
    }
  }


  /**
   * setPlot
   *
   * @param plot Plot
   */
  public void setPlot(Plot plot) {
    _plot = plot;
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
        _plot.addPoint(_dataSetIndex, xValue, yValue, !first);
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
}
