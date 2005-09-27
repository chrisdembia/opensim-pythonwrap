package simtkView.plot;

import ptolemy.plot.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

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

  public void setGrid(boolean grid)
  {
    this.setGrid(grid);
  }

}
