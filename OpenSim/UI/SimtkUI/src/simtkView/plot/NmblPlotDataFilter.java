package simtkView.plot;

import java.io.*;

public interface NmblPlotDataFilter {
  public double[] convertData(double[] pre) ;

  /**
   * write
   *
   * @param fout PrintWriter
   */
  public void write(PrintWriter fout);
}
