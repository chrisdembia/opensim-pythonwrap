/*
 *
 * PlotterQuantityNameFilterTableModel
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.plotter;

import javax.swing.table.AbstractTableModel;

/**
 *
 * @author Ayman
 */
public class PlotterQuantityNameFilterTableModel extends AbstractTableModel {
   /** Creates a new instance of PlotterQuantityNameFilterTableModel */
   PlotterSourceInterface source;
   String[] tableColumnNames= new String[]{"Quantity Name", "Selected"};
   String[] availableQuantities;
   boolean[] selected;
   
   public PlotterQuantityNameFilterTableModel(PlotterSourceInterface source) {
      this.source=source;
      availableQuantities = source.getAllQuantities();
      selected = source.getSelectionStatus();
   }
      
   public int getColumnCount() {
      return tableColumnNames.length;
   }
   
   public int getRowCount() {
      return selected.length;
   }
   
   public String getColumnName(int col) {
      return tableColumnNames[col];
   }
   
   public Object getValueAt(int row, int col) {
      if (col==0)
         return availableQuantities[row];
      else
         return selected[row];
   }
  /*
   * JTable uses this method to determine the default renderer/
   * editor for each cell.  If we didn't implement this method,
   * then the last column would contain text ("true"/"false"),
   * rather than a check box.
   */
  public Class getColumnClass(int c) {
      return getValueAt(0, c).getClass();
  }

   void applyFilter(String regex) {
      selected = source.filterByRegularExprssion(regex);
   }

    public void setValueAt(Object aValue, int row, int col) {
        selected[row] = (Boolean)aValue;
        fireTableCellUpdated(row, col);
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return (columnIndex==1);
    }

    String getNumSelected() {
        int numSelected=0;
        for(int i=0;i<selected.length; i++)
            numSelected += (selected[i]?1:0);
        return numSelected+" items selected";
    }
}
