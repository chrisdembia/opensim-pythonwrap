package org.opensim.plot;

import java.io.PrintWriter;

public class PlotOffsetFilter implements PlotDataFilter{
  double _offset;
  public PlotOffsetFilter(double offset) {
    _offset = offset;
  }

  /**
   * convertData
   *
   * @param pre double[]
   * @return double[]
   */
  public double[] convertData(double[] pre) {
    for (int i=0; i < pre.length; i++)
      pre[i] = _offset + (pre[i]);
    return pre;
  }

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout) {
    fout.println("\t\t\t<filter name=\"offset\" value=\""+_offset+"\"/>");
  }
}
