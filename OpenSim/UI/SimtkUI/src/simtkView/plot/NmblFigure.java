package simtkView.plot;

import java.awt.*;
import javax.swing.*;

import ptolemy.plot.*;
import java.util.*;

public class NmblFigure extends Plot{
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jNmblPlotTopPanel = new JPanel();
  JLabel jFigureLabel = new JLabel();
  BorderLayout borderLayout2 = new BorderLayout();
  public NmblFigure(String caption) {
    super();
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    setFigureCaption(caption);
  }
  private void jbInit() throws Exception {
    this.setLayout(borderLayout1);
    jFigureLabel.setToolTipText("");
    jFigureLabel.setText("     Fig.");
    jNmblPlotTopPanel.setLayout(borderLayout2);
    this.add(jNmblPlotTopPanel,  BorderLayout.NORTH);
    jNmblPlotTopPanel.add(jFigureLabel,  BorderLayout.WEST);
  }

  public void setFigureCaption(String astring)
  {
    jFigureLabel.setText(astring);
  }

  public double[][] getData(int plotIndex)
  {
    Vector pts = (Vector)_points.elementAt(plotIndex);
    int size = pts.size();
    double[][] result = new double[2][size];
    for (int j = 0; j < size; j++) {
        PlotPoint pt = (PlotPoint)pts.elementAt(j);
        result[0][j] = pt.x;
        result[1][j] = pt.y;
    }
    return result;
  }
}
