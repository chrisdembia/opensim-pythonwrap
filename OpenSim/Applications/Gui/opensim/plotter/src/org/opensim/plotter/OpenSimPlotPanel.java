package org.opensim.plotter;

import java.awt.*;
import javax.swing.*;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;

public class OpenSimPlotPanel extends ChartPanel 
{
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jOpenSimlPlotTopPanel = new JPanel();
  JLabel jPlotLabel = new JLabel();
  BorderLayout borderLayout2 = new BorderLayout();
  public OpenSimPlotPanel(JFreeChart chart) {
      super(chart);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    //setFigureCaption(caption);
  }
  private void jbInit() throws Exception {
    this.setLayout(borderLayout1);  //Plot
    jPlotLabel.setToolTipText("");
    jPlotLabel.setText("     Plot.");
    jOpenSimlPlotTopPanel.setLayout(borderLayout2);
    this.add(jOpenSimlPlotTopPanel,  BorderLayout.NORTH);   //Plot
    jOpenSimlPlotTopPanel.add(jPlotLabel,  BorderLayout.WEST);
  }

  public void setFigureCaption(String astring)
  {
    jPlotLabel.setText(astring);
  }

  public double[][] getData(int plotIndex)
  {
      return new double[2][2];
  }

    void removeLegend(int index) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void clear(int index) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void clear(boolean b) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    int getLegendDataset(String aLegend) {
        return 0;
    }

    void setYLabel(String string) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void setXLabel(String string) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void setTitle(String titleString) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void setXRange(double d, double d0) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void setYRange(double d, double d0) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    void setMarksStyle(String _marks, int _dataSetIndexInFigure) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    String getYLabel() {
        return null;
    }

    String getXLabel() {
        return null;
    }

    String getTitle() {
        return null;
    }

    void addLegend(int i, String string) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    double[] getXRange() {
        return null;
    }

    double[] getYRange() {
        return null;
    }
}
