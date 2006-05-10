package simtkui;

import javax.swing.table.DefaultTableModel;

/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */

public class SimtkArrayTableModel extends DefaultTableModel {

  public SimtkArrayTableModel(Object[][] tableDate, Object[] colNames) {
    super(tableDate, colNames);
  }

  public boolean isCellEditable(int row, int column) {
      return column==1;
  }

}
