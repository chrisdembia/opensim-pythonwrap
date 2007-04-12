package org.opensim.plotter;

import java.io.*;

public interface PlotDataFilter {
  public double[] convertData(double[] pre) ;

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout);
}
