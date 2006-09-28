package org.opensim.plot;

import java.io.PrintWriter;

public class PlotScaleFilter implements PlotDataFilter {
  double _scale=1.0;
  public PlotScaleFilter(double scaleFactor) {
    _scale = scaleFactor;
  }

  /**
   * convertData
   *
   * @param pre double[]
   * @return double[]
   */
  public double[] convertData(double[] pre) {
    for (int i=0; i < pre.length; i++)
      pre[i] = pre[i] * _scale;
    return pre;
  }

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout) {
    fout.println("\t\t\t<filter name=\"scale\" value=\""+_scale+"\"/>");
  }
}
