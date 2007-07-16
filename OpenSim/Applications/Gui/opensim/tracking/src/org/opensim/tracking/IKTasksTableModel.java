package org.opensim.tracking;

import java.util.Observable;
import java.util.Observer;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;

class IKTasksValueCell {
   double value;
   IKTasksModel.ValueType type;
   public IKTasksValueCell(double value, IKTasksModel.ValueType type) { this.value = value; this.type = type; }
}

class IKTasksWeightCell {
   double weight;
   boolean locked;
   public IKTasksWeightCell(double weight, boolean locked) { this.weight = weight; this.locked = locked; }
}

class IKTasksValueCellRenderer extends DefaultTableCellRenderer {

   public void setValue(Object value) {
      IKTasksValueCell obj = (IKTasksValueCell)value;
      switch(obj.type) {
         case FromFile: super.setValue(IKTasksTableModel.FromFileStr); break;
         case DefaultValue: super.setValue(IKTasksTableModel.DefaultStr); break;
         case ManualValue: super.setValue((Double)((IKTasksValueCell)value).value);
      }
   }
}

class IKTasksWeightCellRenderer extends DefaultTableCellRenderer {

   public void setValue(Object value) {
      IKTasksWeightCell obj = (IKTasksWeightCell)value;
      if(obj.locked) {
         super.setValue(IKTasksTableModel.LockedStr);
      }
      else {
         super.setValue((Double)((IKTasksWeightCell)value).weight);
      }
   }
}

public class IKTasksTableModel extends AbstractTableModel implements Observer {
   private String[] columnNames = new String[]{"Enabled", "Name", "Value", "Weight"};
   private IKTasksModel tasks;

   public final static String LockedStr = "LOCKED";
   public final static String FromFileStr = "FROM FILE";
   public final static String DefaultStr = "DEFAULT";

   IKTasksTableModel(IKTasksModel tasks, String type) {
      this.tasks = tasks;
      columnNames[1] = type + " Name";
      tasks.addObserver(this);
   }

   //------------------------------------------------------------------------
   // Listen to events from the IKTasksModel
   //------------------------------------------------------------------------
   public void update(Observable observable, Object obj) {
      IKTasksModelEvent ev = (IKTasksModelEvent)obj;
      switch(ev.op) {
         case AllChanged: 
            fireTableDataChanged();
            break;
         case TaskChanged:
            fireTableRowsUpdated(ev.index,ev.index);
            break;
      }
   }

   //------------------------------------------------------------------------
   // Helper methods
   //------------------------------------------------------------------------
   public IKTasksModel getIKTasksModel() { return tasks; }

   public boolean isSameEnabled(int rows[]) {
      for(int row : rows) if(tasks.getEnabled(row)!=tasks.getEnabled(rows[0])) return false;
      return true;
   }
   public void setEnabled(int rows[], boolean enabled) {
      for(int row : rows) tasks.setEnabled(row, enabled);
   }

   public boolean isSameWeight(int rows[]) {
      for(int row : rows) if(tasks.isLocked(row)!=tasks.isLocked(rows[0]) || (!tasks.isLocked(row) && tasks.getWeight(row)!=tasks.getWeight(rows[0]))) return false;
      return true;
   }
   public void setWeight(int rows[], double weight) {
      for(int row : rows) tasks.setWeight(row, weight);
   }

   public boolean isSameValueType(int rows[]) {
      for(int row : rows) if(tasks.getValueType(row)!=tasks.getValueType(rows[0])) return false;
      return true;
   }
   public boolean isSameDefaultValue(int rows[]) {
      for(int row : rows) if(tasks.getDefaultValue(row)!=tasks.getDefaultValue(rows[0])) return false;
      return true;
   }
   public boolean isSameManualValue(int rows[]) {
      for(int row : rows) if(tasks.getManualValue(row)!=tasks.getManualValue(rows[0])) return false;
      return true;
   }
   public void setManualValue(int rows[], double value) {
      for(int row : rows) tasks.setManualValue(row, value);
   }
   public void setValueType(int rows[], IKTasksModel.ValueType valueType) {
      for(int row : rows) tasks.setValueType(row, valueType);
   }

   //------------------------------------------------------------------------
   // AbstractTableModel methods
   //------------------------------------------------------------------------
   public int getColumnCount() {
      return columnNames.length;
   }

   public int getRowCount() {
      return tasks.size();
   }

   public String getColumnName(int col) {
      return columnNames[col];
   }

   public Object getValueAt(int row, int col) {
      if(col==0) return tasks.getEnabled(row);
      else if(col==1) return tasks.getName(row);
      else if(col==2) return new IKTasksValueCell(tasks.getValue(row), tasks.getValueType(row));
      else if(col==3) return new IKTasksWeightCell(tasks.getWeight(row), tasks.isLocked(row));
      else return null;
   }

   public Class getColumnClass(int col) {
      if(col==0) return Boolean.class;
      else if(col==1) return String.class;
      else if(col==2) return IKTasksValueCell.class;
      else if(col==3) return IKTasksWeightCell.class;
      else return null;
   }

   public boolean isCellEditable(int row, int col) {
      return col==0; // Only enabled column is editable
   }

   public void setValueAt(Object value, int row, int col) {
      assert(col==0);
      tasks.setEnabled(row, ((Boolean)value).booleanValue());
      //fireTableCellUpdated(row, col); // will fire an event when update() gets called due to a change in IKTasksModel
   }
}
