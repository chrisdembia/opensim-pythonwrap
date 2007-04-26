package org.opensim.plotter;

import java.io.PrintWriter;

public class PlotOffsetFilter implements PlotDataFilter{
  double value=0.0;
  public PlotOffsetFilter(double offset) {
    value = offset;
  }

  /**
   * convertData
   *
   * @param pre double[]
   * @return double[]
   */
  public double[] convertData(double[] pre) {
    for (int i=0; i < pre.length; i++)
      pre[i] = value + (pre[i]);
    return pre;
  }

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout) {
    fout.println("\t\t\t<filter name=\"offset\" value=\""+value+"\"/>");
  }
}
