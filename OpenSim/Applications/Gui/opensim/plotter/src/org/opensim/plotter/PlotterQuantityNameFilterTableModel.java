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

import java.util.Vector;
import java.util.regex.Pattern;
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
   Vector<Integer> shownQuantities=new Vector<Integer>(50);
   boolean[] selected;
   
   public PlotterQuantityNameFilterTableModel(PlotterSourceInterface source) {
      this.source=source;
      availableQuantities = source.getAllQuantities();
      showAll();
      source.clearSelectionStatus();
      selected = source.getSelectionStatus();
      select(".*", false);
   }

    private void showAll() {
        shownQuantities.clear();
        for(int i=0;i<availableQuantities.length;i++)
            shownQuantities.add(i);
    }
      
   public int getColumnCount() {
      return tableColumnNames.length;
   }
   
   public int getRowCount() {
      return shownQuantities.size();
   }
   
   public String getColumnName(int col) {
      return tableColumnNames[col];
   }
   
   public Object getValueAt(int row, int col) {
      if (col==0)
         return availableQuantities[shownQuantities.get(row)];
      else
         return selected[shownQuantities.get(row)];
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
        selected[shownQuantities.get(row)] = (Boolean)aValue;
        fireTableCellUpdated(row, col);
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return (columnIndex==1);
    }

    int getNumSelected() {
        int numSelected=0;
        for(int i=0;i<selected.length; i++)
            numSelected += (selected[i]?1:0);
        return numSelected;
    }
    int getNumShownAndSelected() {
        int numShownAndSelected=0;
        for(int i=0;i<shownQuantities.size(); i++)
            numShownAndSelected += (selected[shownQuantities.get(i)]?1:0);
        return numShownAndSelected;
    }

    String[] getSelected()
    {
        String[] sel = new String[getNumSelected()];
        int j=0;
        for(int i=0;i<selected.length; i++){
            if (selected[i]){
                sel[j]=availableQuantities[i];
                j++;
            }
        }
        return sel;
    }
    String getSelectedAsString() {
        String selectedString="";
        boolean first=true;
        for(int i=0;i<selected.length; i++){
            if (selected[i]){
                if (first){
                    selectedString += availableQuantities[i];
                    first=false;
                }
                else
                    selectedString += ", "+availableQuantities[i];;
            }
        }
        return selectedString;
    }

    void markSelectedNames(Vector<String> names) {
        for(int n=0; n<names.size();n++){
            String name = names.get(n);
            boolean found=false;
            for(int i=0; i<availableQuantities.length && !found; i++){
                if (availableQuantities[i].compareTo(name)==0)
                    selected[i]=true;
            }
        }
        fireTableCellUpdated(0, 0);

    }
    
    void restrictNamesBy(String pattern){
      Pattern p = Pattern.compile(pattern);
      shownQuantities.clear();
      for(int i=0; i<availableQuantities.length ;i++){
        System.out.println("Match ["+availableQuantities[i]+"] against pattern "+pattern+" returns "+p.matcher(availableQuantities[i]).matches());
        if (p.matcher(availableQuantities[i]).matches())
            shownQuantities.add(i);
      }
      fireTableDataChanged();
        
    }

    void select(String pattern, boolean b) {
      Pattern p = Pattern.compile(pattern);
      for(int i=0; i<shownQuantities.size() ;i++){
        if (p.matcher(availableQuantities[i]).matches())
            selected[i]=b;
      }
      fireTableDataChanged();
    }

    void selectShown(boolean b) {
      for(int i=0; i<shownQuantities.size() ;i++){
            selected[shownQuantities.get(i)]=b;
      }
      fireTableDataChanged();
    }
}
