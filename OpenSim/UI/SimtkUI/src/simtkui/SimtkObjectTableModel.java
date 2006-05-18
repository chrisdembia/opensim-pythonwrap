package simtkui;

import javax.swing.table.AbstractTableModel;

import opensimModel.OpenSimObject;
import opensimModel.Property;
import opensimModel.PropertySet;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Table model for object review dialog. Maps properties from an OpenSimObject to a
 * table of strings to be displayed by the review object dialog. Current layout
 * is:
 * "Property name", "Property Value", "Use Default"
 * Last column (use default) is used to indicate if the value displayed was
 * enetered by the user dicrectly or is inherited from some default object.
 *
 * @author Ayman Habib
 * @version 1.0
 */
public class SimtkObjectTableModel extends AbstractTableModel {
  private OpenSimObject _aObject;
  private String _columnLabels[] = {"Propery name", "Property Value", "Use Default"};
  private String[] _rowLabels;
  private String[] _rowValues;
  private String[] _useDefaults;

  public SimtkObjectTableModel(OpenSimObject aObject) {
    _aObject = aObject;
    buildTable();
  }

  /**
   * buildTable
   */
  private void buildTable() {
    PropertySet objectProps = _aObject.getPropertySet();
    int sz = objectProps.getSize();
    _rowLabels = new String[sz];
    _rowValues = new String[sz];
    _useDefaults = new String[sz];
    for (int i = 0; i < objectProps.getSize(); i++) {
      Property prop = objectProps.get(i);
      _rowLabels[i] = prop.getName();
         if(prop.getType()== Property.PropertyType.Int)
          _rowValues[i] = String.valueOf(prop.getValueInt());
        else if(prop.getType()== Property.PropertyType.Dbl)
          _rowValues[i] = String.valueOf(prop.getValueDbl());
        else // For now we just show the type until we can map all types to strings
          _rowValues[i] = prop.getTypeAsString();

       _useDefaults[i] = (prop.getUseDefault()) ? "Yes" : "No";
    }
  }

  public int getRowCount() {
    /**We'll have one row per property (+1 for label?)*/
    return _aObject.getPropertySet().getSize();
  }
  public int getColumnCount() {
    /**We'll have two columns one for property name and the other for value */
    return 3;
  }
  public String getColumnName(int columnIndex) {
     return _columnLabels[columnIndex];
  }
  public Class getColumnClass(int columnIndex) {
    /**@todo Implement this javax.swing.table.TableModel method*/
    return _columnLabels[columnIndex].getClass();
  }

  public Object getValueAt(int rowIndex, int columnIndex) {
    if (columnIndex == 0)
      return (_rowLabels[rowIndex]);
    else if (columnIndex == 1)
      return (_rowValues[rowIndex]);
    else
      return (_useDefaults[rowIndex]);
  }
  public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
    /**@todo Implement this javax.swing.table.TableModel method*/
    throw new java.lang.UnsupportedOperationException("Method setValueAt() not yet implemented.");
  }

}
