/*
 *
 * CoordinateTableModel
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
package org.opensim.coordinateviewer;

import javax.swing.table.AbstractTableModel;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.Model;
import org.opensim.modeling.CoordinateSet;
/**
 *
 * @author Ayman
 */
public class CoordinateTableModel extends AbstractTableModel{
   
   Object[][] contents;
   String[] columnNames= new String[]{"Coordinate", "c", "l", "value"};
   int numCoords;
   private Model model;
   private CoordinateSet coords;
   /** Creates a new instance of CoordinateTableModel */
   public CoordinateTableModel(Model aModel) {
      model = aModel;
      if (model==null){
         reset();
         return;
      }
      coords = model.getDynamicsEngine().getCoordinateSet();
      numCoords = coords.getSize();
      contents = new Object[numCoords][5];
      for(int i=0; i<numCoords; i++){
         AbstractCoordinate coord = coords.get(i);
         contents[i][0]=coord.getName();
         contents[i][1]=(coord.getClamped())?Boolean.TRUE:Boolean.FALSE; // Clamped
         contents[i][2]=(coord.getLocked())?Boolean.TRUE:Boolean.FALSE; // Locked
         contents[i][3]=coord.getValue(); // Value
         
      }
   }

   public int getRowCount() {
      return numCoords;
   }

   public int getColumnCount() { // name, clamped, locked, text, slider
      return 4;
   }

   public Object getValueAt(int rowIndex, int columnIndex) {
      return contents[rowIndex][columnIndex];
   }

   public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
      super.setValueAt(aValue, rowIndex, columnIndex);
   }

   public String getColumnName(int column) {
      return columnNames[column];
   }

   public Class<?> getColumnClass(int columnIndex) {
      return getValueAt(0, columnIndex).getClass();
   }

   public boolean isCellEditable(int rowIndex, int columnIndex) {
      return true;
   }
   
   public void reset() {
      contents = new Object[0][4];
      numCoords=0;
   }

   public Model getModel() {
      return model;
   }

   AbstractCoordinate getCoordinate(int row) {
      return coords.get(row);
   }
   
}
