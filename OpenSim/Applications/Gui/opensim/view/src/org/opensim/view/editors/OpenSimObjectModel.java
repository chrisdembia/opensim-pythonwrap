package org.opensim.view.editors;

import java.awt.Insets;
import java.awt.event.MouseEvent;
import java.io.IOException;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.event.MouseInputAdapter;
import org.opensim.modeling.ArrayBool;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ArrayInt;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Property;
import org.opensim.modeling.PropertySet;

//=========================================================================
// OpenSimObjectModel
//=========================================================================
public class OpenSimObjectModel extends AbstractTreeTableModel {
  // Names of the columns.
  static protected String[] cNames = { "Name", "", "Value", "Description" };

  // Types of the columns.
  static protected Class[] cTypes = { TreeTableModel.class, JButton.class, String.class, String.class };

  // Column header tool tips
  static final String[] toolTipStr = { "Property name in xml file", "Controls for array properties", "Current property value", "Description"};

  // Whether columns are editable
  // Column 0 is the tree, needs to be "editable" in order for expansion/collapse of nodes
  static protected boolean[] editableColumns = { true, false, true, false };

  // Whether the table as a whole is editable (false if we're just viewing properties)
  protected boolean isEditable;

  static protected PropertyNode[] EMPTY_CHILDREN = new PropertyNode[0];

  protected final Icon addIcon = new ImageIcon(getClass().getResource("/org/opensim/swingui/addSymbol.png"));
  protected final Icon removeIcon = new ImageIcon(getClass().getResource("/org/opensim/swingui/closeSymbol.png"));

  //-------------------------------------------------------------------------
  // Constructor
  //-------------------------------------------------------------------------

  public OpenSimObjectModel(OpenSimObject obj, boolean isEditable) {
    super(obj);
    this.isEditable = isEditable;
    root = new PropertyNode(obj);
  }

  public String getColumnHeaderToolTip(int column) { return toolTipStr[column]; }

  //-------------------------------------------------------------------------
  // The TreeModel interface
  //-------------------------------------------------------------------------

  public int getChildCount(Object node) {
    Object[] children = getChildren(node);
    return (children == null) ? 0 : children.length;
  }

  public Object getChild(Object node, int i) {
    return getChildren(node)[i];
  }

  public boolean isLeaf(Object node) { 
     return ( (PropertyNode) node).isLeaf(); 
  }

  //-------------------------------------------------------------------------
  // The TreeTableModel interface
  //-------------------------------------------------------------------------

  public int getColumnCount() { return cNames.length; }

  public String getColumnName(int column) { return cNames[column]; }

  // Unfortunately, JTable calls this method in some more places rather than always going through getCellEditor, getCellRenderer...
  // So the net result is that the editor will think it's editing string even when it edits numbers
  public Class getColumnClass(int column) { return cTypes[column]; }

  // This is for the cell renderer
  public Class getCellClass(Object node, int column) { 
     if(column==2) return ((PropertyNode)node).getValueClass();
     else return cTypes[column];
  }

  public boolean isCellEditable(Object node, int column) {
//     return column == 0 || (isEditable && editableColumns[column] && ((PropertyNode)node).editable());
   return true;
  }

  /**
   * Returns the value of the particular column.
   */
  public Object getValueAt(Object node, int column) {
    PropertyNode fn = (PropertyNode) node;
    try {
      switch (column) {
        case 0: // Name
          return fn.getName();
        case 1: // Controls
          return fn.getControlButton();
        case 2: // Value
          return fn.getValue();
        case 3: // Description
          return fn.getDescription();
      }
    }
    catch (SecurityException se) {}

    return null;
  }

  /**
   * This's the function to be invoked when editing is finished.
   * It should update the underlying node, refresh display and fire-events as needed.
   *
   * @param aValue Object
   * @param node Object
   * @param column int
   *
   * This has the side effect of turning off the switch to useDefault value.
   * Might be better to do it inside appropriate setValue() method except that array properties 
   * and scalar properties are not handled the same. -Ayman 02/07
   */
  public void setValueAt(Object aValue, Object node, int column) {
    if (column==2) ((PropertyNode)node).setValue(aValue);
  }

  //-------------------------------------------------------------------------
  // Some convenience methods
  //-------------------------------------------------------------------------

  /**
   * Reloads the children of the specified node.
   */
  public void reloadChildren(Object node) {
    PropertyNode fn = (PropertyNode) node;
    fn.loadChildren();
    fn.setChildren(fn.getChildren(), true);
    fn.nodeChanged();
  }

  protected Object[] getChildren(Object node) {
    return ((PropertyNode)node).getChildren();
  }

  //=========================================================================
  // PropertyNode
  //=========================================================================

  class PropertyNode {
    private PropertyNode parent;
    protected Object property; // May be OpenSimObject or a Property
    protected PropertyNode[] children;
    protected Property.PropertyType propValueType = null; // Indicates property type of this node (NOTE: an item of a PropertyDblArray gets the type PropertyDbl!)

    /** will this object be treated as a leaf or as expandible */
    protected boolean aggregate;

    /** in cases where the node corresponds to an array entry, keep index here, and property will be the property array containing the item */
    protected int idx;

    protected JButton controlButton = null;

    //-----------------------------------------------------------------------
    // Constructors
    //-----------------------------------------------------------------------
    /**
     * PropertyNode constructor that takes object, no parent or index
     *
     * @param property Object
     */
    protected PropertyNode(Object property) {
      this(null, property, -1);
    }

    /**
     * PropertyNode constructor that takes parent as well as object
     *
     * @param parent PropertyNode
     * @param property Object
     */
    protected PropertyNode(PropertyNode parent, Object property) {
      this(parent, property, -1);
    }

    /**
     * PropertyNode constructor taht takes parent, object and an index. used by
     * arrays
     *
     * @param parent PropertyNode
     * @param property Object
     * @param index int
     */
    protected PropertyNode(PropertyNode parent, Object property, int index) {
      this.parent = parent;
      this.property = property;
      this.idx = index;
      aggregate = false;

      if (property instanceof OpenSimObject) {
         aggregate = true;
      } else if (property instanceof Property) {
         Property.PropertyType propType = ( (Property) property).getType();

         if(propType==Property.PropertyType.Dbl || (propType==Property.PropertyType.DblArray && idx!=-1)) propValueType = Property.PropertyType.Dbl; 
         else if(propType==Property.PropertyType.Int || (propType==Property.PropertyType.IntArray && idx!=-1)) propValueType = Property.PropertyType.Int; 
         else if(propType==Property.PropertyType.Str || (propType==Property.PropertyType.StrArray && idx!=-1)) propValueType = Property.PropertyType.Str; 
         else if(propType==Property.PropertyType.Bool || (propType==Property.PropertyType.BoolArray && idx!=-1)) propValueType = Property.PropertyType.Bool; 

         if(propType == Property.PropertyType.DblArray ||
            propType == Property.PropertyType.IntArray ||
            propType == Property.PropertyType.StrArray ||
            propType == Property.PropertyType.BoolArray)
         {
            if(idx==-1) {
               aggregate = true;

               // Button to add array item
               controlButton = new JButton(addIcon);
               controlButton.addMouseListener(new MouseInputAdapter() {
                  public void mousePressed(MouseEvent evt) { addPropertyItem(); }
               });
            } else {
               // Button to delete array item
               controlButton = new JButton(removeIcon);
               controlButton.addMouseListener(new MouseInputAdapter() {
                  public void mousePressed(MouseEvent evt) { removePropertyItem(); }
               });
            }
         }
         else if(propType == Property.PropertyType.Obj ||
                 propType == Property.PropertyType.ObjPtr ||
                 propType == Property.PropertyType.ObjArray)
         {
            aggregate = true;
         }
      }

      if(controlButton!=null) {
         controlButton.setContentAreaFilled(false);
         controlButton.setMargin(new Insets(0,0,0,0));
         controlButton.setOpaque(true);
      }
    }

    //-----------------------------------------------------------------------
    // Basic get/set/queries
    //-----------------------------------------------------------------------
    
    public String toString() { return getName(); }

    public PropertyNode getParent() { return parent; }

    public boolean isLeaf() { return !aggregate; }

    protected PropertyNode[] getChildren() { return children; }

    public String getDescription() {
       if(property instanceof Property && idx==-1) return ((Property)property).getComment();
       else return " ";
    }

    public boolean editable() { return !aggregate; }

    //-----------------------------------------------------------------------
    // Add/Remove for property arrays
    //-----------------------------------------------------------------------

    // This is the parent node for a property array, and we want to add an item to the array
    private void addPropertyItem() {
      Property p = (Property)property;
      // TODO: what values should we use to populate newly created item?
      if (p.getType() == Property.PropertyType.DblArray) p.getValueDblArray().append(0.0);
      else if (p.getType() == Property.PropertyType.IntArray) p.getValueIntArray().append(0);
      else if (p.getType() == Property.PropertyType.StrArray) p.getValueStrArray().append("");
      else if (p.getType() == Property.PropertyType.BoolArray) p.getValueBoolArray().append(true);
      reloadChildren(this);
    }

    // This is an item in a property array, and we remove this item
    private void removePropertyItem() {
      if(idx != -1) {
         Property p = (Property)getParent().property;
         if (p.getType() == Property.PropertyType.DblArray) p.getValueDblArray().remove(idx);
         else if (p.getType() == Property.PropertyType.IntArray) p.getValueIntArray().remove(idx);
         else if (p.getType() == Property.PropertyType.StrArray) p.getValueStrArray().remove(idx);
         else if (p.getType() == Property.PropertyType.BoolArray) p.getValueBoolArray().remove(idx);
         reloadChildren(getParent());
      }
    }

    //-----------------------------------------------------------------------
    // Basic get/set/queries
    //-----------------------------------------------------------------------

    public Object getValue() {
      if (property instanceof OpenSimObject)
        return getName();
      else if (property instanceof Property) {
         Property p = (Property)property;
         if(propValueType == Property.PropertyType.Dbl) { 
            if(idx==-1) return (Double)p.getValueDbl();
            else return (Double)p.getValueDblArray().getitem(idx); 
         } else if(propValueType == Property.PropertyType.Int) {
            if(idx==-1) return (Integer)p.getValueInt();
            else return (Integer)p.getValueIntArray().getitem(idx); 
         } else if(propValueType == Property.PropertyType.Str) {
            if(idx==-1) return (String)p.getValueStr();
            else return (String)p.getValueStrArray().getitem(idx); 
         } else if(propValueType == Property.PropertyType.Bool) {
            if(idx==-1) return (Boolean)p.getValueBool();
            else return (Boolean)p.getValueBoolArray().getitem(idx); 
         } else return p.toString();
      }
      return "unknownValue";
    }

    public Class getValueClass() { 
      if (property instanceof OpenSimObject) return String.class;
      else if (property instanceof Property) {
         Property p = (Property)property;
         if(propValueType == Property.PropertyType.Dbl) return Double.class;
         else if(propValueType == Property.PropertyType.Int) return Integer.class;
         else if(propValueType == Property.PropertyType.Str) return String.class;
         else if(propValueType == Property.PropertyType.Bool) return Boolean.class;
         else return String.class;
      } else return String.class;
    }

    public String getName() {
      if (property instanceof OpenSimObject)
        return ( (OpenSimObject) property).getName();
      else if (property instanceof Property && idx==-1)
        return ( (Property) property).getName();
      else if (idx!=-1)
       return ( "["+String.valueOf(idx)+"]");

      return ("unknown type!");
    }

   public JButton getControlButton() {
      return controlButton;
   }

   public void setValue(Object value) {
      /**
      * The following steps need to be done
      * 1. Map property and index if any to a primitive type
      * 2. Cast value into a String sValue;
      * 3. Parse sValue using type info
      * 4. call API to ste the value
      */
      // Only primitive properties and array entries can be edited
      if(property instanceof Property) {
         Property p = (Property)property;
         p.setUseDefault(false);

         // NOTE: I wanted the values to come in as Double, Integer, etc. but due to some weirdness the table editor thinks
         // it's editing a string in the cases of Double, Integer, and String... so I check this below (value instanceof String) to be safe
         try {
            if(propValueType == Property.PropertyType.Dbl) { 
               double val = (value instanceof String) ? Double.parseDouble((String)value) : ((Double)value).doubleValue();
               if(idx==-1) p.setValue(val); else p.getValueDblArray().set(idx, val);
            } else if(propValueType == Property.PropertyType.Int) {
               int val = (value instanceof String) ? Integer.parseInt((String)value) : ((Integer)value).intValue();
               if(idx==-1) p.setValue(val); else p.getValueIntArray().set(idx, val);
            } else if(propValueType == Property.PropertyType.Str) {
               String val = (String)value;
               if(idx==-1) p.setValue(val); else p.getValueStrArray().set(idx, val);
            } else if(propValueType == Property.PropertyType.Bool) {
               boolean val = ((Boolean)value).booleanValue();
               if(idx==-1) p.setValue(val); else p.getValueBoolArray().set(idx, val);
            }
         } catch (NumberFormatException ex) { // might get a parsing exception
         }

         if(idx!=-1) reloadChildren(getParent());
      }
   }

    /**
     * Creates PropertyNodes for the children of this node.
     *
     * @return PropertyNode[]
     * @todo Complete the list of types of Property that are aggregates:
     *   primitive types already work as well as Arrays of doubles and Strings.
     *   Left: Arrays of objects and actual editing/change-probagation
     */
    protected PropertyNode[] createChildren() {
      PropertyNode[] retArray = null;

      try {
        if (property instanceof OpenSimObject) {
          PropertySet props = ( (OpenSimObject) property).getPropertySet();
          retArray = new PropertyNode[props.getSize()];
          for (int i = 0; i < props.getSize(); i++) {
                  Property prop=null;
                  try {
                     prop = props.get(i);
                  } catch (IOException ex) {
                     ex.printStackTrace();
                  }
            retArray[i] = new PropertyNode(this, prop);
          }
        }
        else if (property instanceof Property) {
          Property rdprop = (Property) property;
          Property.PropertyType propType = rdprop.getType();
          if (propType == Property.PropertyType.Obj || propType == Property.PropertyType.ObjPtr) {
             boolean objPtr=(propType == Property.PropertyType.ObjPtr);
            OpenSimObject childObj = (objPtr)?(OpenSimObject) rdprop.getValueObjPtr():(OpenSimObject) rdprop.getValueObj();
            if (childObj==null) return EMPTY_CHILDREN;
            PropertySet props = ( (OpenSimObject) childObj).getPropertySet();
            retArray = new PropertyNode[props.getSize()];
            for (int i = 0; i < props.getSize(); i++) {
               Property prop=null;
               try {
                  prop = props.get(i);
               } catch (IOException ex) {
                  ex.printStackTrace();
               }
              retArray[i] = new PropertyNode(this, prop);
            }
          }
          else if (propType == Property.PropertyType.DblArray) {
            ArrayDouble dblArray = rdprop.getValueDblArray();
            retArray = new PropertyNode[dblArray.getSize()];
            for (int i = 0; i < dblArray.getSize(); i++) retArray[i] = new PropertyNode(this, property, i);
          }
          else if (propType == Property.PropertyType.IntArray) {
            ArrayInt intArray = rdprop.getValueIntArray();
            retArray = new PropertyNode[intArray.getSize()];
            for (int i = 0; i < intArray.getSize(); i++) retArray[i] = new PropertyNode(this, property, i);
          }
          else if (propType == Property.PropertyType.StrArray) {
            ArrayStr strArray = rdprop.getValueStrArray();
            retArray = new PropertyNode[strArray.getSize()];
            for (int i = 0; i < strArray.getSize(); i++) retArray[i] = new PropertyNode(this, property, i);
          }
          else if (propType == Property.PropertyType.BoolArray) {
            ArrayBool boolArray = rdprop.getValueBoolArray();
            retArray = new PropertyNode[boolArray.getSize()];
            for (int i = 0; i < boolArray.getSize(); i++) retArray[i] = new PropertyNode(this, property, i);
          }
          else if (propType == Property.PropertyType.ObjArray) {
            retArray = new PropertyNode[rdprop.getValueObjArraySize()];
            for (int i = 0; i < rdprop.getValueObjArraySize(); i++) {
              OpenSimObject subobj = rdprop.getValueObjPtr(i);
              retArray[i] = new PropertyNode(this, subobj, i);
            }
          }
        }
      }
      catch (SecurityException se) {}
      if (retArray == null) {
        retArray = EMPTY_CHILDREN;
      }
      return retArray;
    }

    //-----------------------------------------------------------------------
    // Path utilities
    //-----------------------------------------------------------------------

    public PropertyNode[] getPath() {
      return getPathToRoot(this, 0);
    }

    protected PropertyNode[] getPathToRoot(PropertyNode aNode, int depth) {
      PropertyNode[] retNodes;

      if (aNode == null) {
        if (depth == 0)
          return null;
        else
          retNodes = new PropertyNode[depth];
      }
      else {
        depth++;
        retNodes = getPathToRoot(aNode.getParent(), depth);
        retNodes[retNodes.length - depth] = aNode;
      }
      return retNodes;
    }

    //-----------------------------------------------------------------------
    // Node/Children utilities
    //-----------------------------------------------------------------------

    /**
     * Recursively loads all the children of the receiver.
     */
    protected void loadChildren() {
      children = createChildren();
      for (int counter = children.length - 1; counter >= 0; counter--) {
        if (!children[counter].isLeaf()) {
          children[counter].loadChildren();
        }
      }
    }

    /**
     * Sets the children of the receiver, updates the total size,
     * and if generateEvent is true a tree structure changed event
     * is created.
     */
    protected void setChildren(PropertyNode[] newChildren, boolean generateEvent) {
      children = newChildren;
      if (generateEvent) {
        PropertyNode[] path = getPath();
        fireTreeStructureChanged(OpenSimObjectModel.this, path, null, null);
      }
    }

    /**
     * Can be invoked when a node has changed, will create the
     * appropriate event.
     */
    protected void nodeChanged() {
      PropertyNode parent = getParent();
      if (parent != null) {
        PropertyNode[] path = parent.getPath();
        int[] index = { getIndexOfChild(parent, this)};
        Object[] children = { this};
        fireTreeNodesChanged(OpenSimObjectModel.this, path, index, children);
      }
    }
  }
}
