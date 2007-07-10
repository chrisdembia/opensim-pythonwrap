package org.opensim.view.editors;

/*
 * OpenSimObjectModel.java
 *
 *
 */

import java.io.IOException;
import javax.swing.SwingUtilities;
import javax.swing.tree.TreePath;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ArrayInt;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Property;
import org.opensim.modeling.PropertySet;
import org.opensim.modeling.VisibleObject;



public class OpenSimObjectModel
    extends AbstractTreeTableModel {

  // Names of the columns.
  static protected String[] cNames = {
      "Name", "Value", "Description"};

  // Types of the columns.
  static protected Class[] cTypes = {
      TreeTableModel.class,
      String.class,
      String.class};

  static protected boolean[] editableColumns = {
      true, // TreeTableModel
      true, // Value
      true}; // UseDefault

  final String[] toolTipStr = {
      "Property name in xml file", "Current property value",
      "Description"};

  /** True if the receiver is valid, once set to false all Threads
   * loading files will stop. */
  protected boolean isValid;

  /** Node currently being reloaded, this becomes somewhat muddy if
   * reloading is happening in multiple threads. */
  protected PropertyNode reloadNode;

  /** > 0 indicates reloading some nodes. */
  int reloadCount;

  /** Flag to indicate if the tree will be editable.
   * This has to be taken in context as:
   * 1. Column 1 which is the tree is editable only to allow expansion/collapse of tree
   *    even if entries are not editable.
   * 2. Values & useDefault are editable only in primitive type rows
   */

  protected boolean isEditable;

  protected boolean isVisibleObject;

  /**
     * Creates a OpenSimObjectModel with the root being <code>rootPath</code>.
     * This does not load it, you should invoke
     * <code>reloadChildren</code> with the root to start loading.
     */
  public OpenSimObjectModel(OpenSimObject obj, boolean isEditable) {
    super(obj);
    isValid = true;
    this.isEditable = isEditable;
    root = new PropertyNode(obj, isEditable);
  }

  //
  // The TreeModel interface
  //

  /**
   * Returns the number of children of <code>node</code>.
   */
  public int getChildCount(Object node) {
    Object[] children = getChildren(node);
    return (children == null) ? 0 : children.length;
  }

  /**
   * Returns the child of <code>node</code> at index <code>i</code>.
   */
  public Object getChild(Object node, int i) {
    return getChildren(node)[i];
  }

  /**
   * Returns true if the passed in object represents a leaf, false
   * otherwise.
   */
  public boolean isLeaf(Object node) {
    return ( (PropertyNode) node).isLeaf();
  }

  //
  //  The TreeTableNode interface.
  //

  /**
   * Returns the number of columns.
   */
  public int getColumnCount() {
    return cNames.length;
  }

  /**
   * Returns the name for a particular column.
   */
  public String getColumnName(int column) {
    return cNames[column];
  }

  /**
   * Returns the class for the particular column.
   */
  public Class getColumnClass(int column) {
    return cTypes[column];
  }

  /**
   * Returns if the particular column is editable.
   */
  public boolean getColumnEditable(int column) {
    return editableColumns[column];
  }
  /**
   * Returns the value of the particular column.
   */
  public Object getValueAt(Object node, int column) {
    PropertyNode fn = (PropertyNode) node;
    boolean toEdit = fn.editable();
    try {
      switch (column) {
        case 0: // Name
          return fn.getName();
        case 1: // Value
          return fn.getValue();
        case 2: // use default
          Object obj = fn.getObject();
          if (obj instanceof Property)
            return ( ( (Property) obj).getComment());
          return "  ";
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
    if (column==1){// Changing Value
      /**
       * The following steps need to be done
       * 1. Map property and index if any to a primitive type
       * 2. Cast aValue into a String sValue;
       * 3. Parse sValue using type info
       * 4. call API to ste the value
       */
      String newValueString = (String) aValue;
      // Only primitive properties and array entries can be edited
      if (((PropertyNode) node).property instanceof Property){
        Property p = (Property) ((PropertyNode) node).property;
        p.setUseDefault(false);
        if (p.getType()== Property.PropertyType.Dbl){
          double newdbl = Double.parseDouble(newValueString);
          p.setValue(newdbl);
        }
        else if (p.getType()== Property.PropertyType.Int){
          int newint = Integer.parseInt(newValueString);
          p.setValue(newint);
        }
        else if (p.getType()== Property.PropertyType.Str){
           p.setValue(newValueString);
        }
        else if (p.getType()==Property.PropertyType.Bool){
          Boolean b = Boolean.valueOf(newValueString);
          p.setValue(b.booleanValue());
        }
      }
      else if (((PropertyNode) node).idx != -1){// Array index of an aggregate/array property
         Property p = (Property) ((PropertyNode) node).getParent().property;
         p.setUseDefault(false);
         if (p.getType()== Property.PropertyType.DblArray){
           double newdbl = Double.parseDouble(newValueString);
           ArrayDouble dblArray = p.getValueDblArray();
           dblArray.set(((PropertyNode) node).idx, newdbl);
           reloadChildren(((PropertyNode) node).getParent());
         }
         else if (p.getType()== Property.PropertyType.IntArray){
          int newint = Integer.parseInt(newValueString);
          ArrayInt intArray = p.getValueIntArray();
          intArray.set(((PropertyNode) node).idx, newint);
          reloadChildren(((PropertyNode) node).getParent());
        }
        else if (p.getType()== Property.PropertyType.StrArray){
          p.getValueStrArray().set(((PropertyNode) node).idx, newValueString);
          reloadChildren(((PropertyNode) node).getParent());
        }
        else if (p.getType()== Property.PropertyType.BoolArray){
          boolean newval = Boolean.getBoolean(newValueString);
          p.getValueBoolArray().set(((PropertyNode) node).idx, newval);
          reloadChildren(((PropertyNode) node).getParent());
        }
     }
    }
  }
  //
  // Some convenience methods.
  //

  /**
   * Reloads the children of the specified node.
   */
  public void reloadChildren(Object node) {
    PropertyNode fn = (PropertyNode) node;

    synchronized (this) {
      reloadCount++;
    }
    new Thread(new PropertyNodeLoader( (PropertyNode) node)).start();
  }

  /**
   * Stops and waits for all threads to finish loading.
   */
  public void stopLoading() {
    isValid = false;
    synchronized (this) {
      while (reloadCount > 0) {
        try {
          wait();
        }
        catch (InterruptedException ie) {}
      }
    }
    isValid = true;
  }

  /**
   * Returns true if the receiver is loading any children.
   */
  public boolean isReloading() {
    return (reloadCount > 0);
  }

  /**
   * Returns the path to the node that is being loaded.
   */
  public TreePath getPathLoading() {
    PropertyNode rn = reloadNode;

    if (rn != null) {
      return new TreePath(rn.getPath());
    }
    return null;
  }

  /**
   * Returns the node being loaded.
   */
  public Object getNodeLoading() {
    return reloadNode;
  }

  protected Object getObject(Object node) {
    PropertyNode PropertyNode = ( (PropertyNode) node);
    return PropertyNode.getObject();
  }

  protected Object[] getChildren(Object node) {
    PropertyNode PropertyNode = ( (PropertyNode) node);
    return PropertyNode.getChildren();
  }

  protected static PropertyNode[] EMPTY_CHILDREN = new PropertyNode[0];

  /**
   * A PropertyNode is a derivative of the File class - though we delegate to
   * the File object rather than subclassing it. It is used to maintain a
   * cache of a directory's children and therefore avoid repeated access
   * to the underlying file system during rendering.
   */
  class PropertyNode {
    /** java.io.File the receiver represents. */
    protected Object property;

    /** Parent PropertyNode of the receiver. */
    private PropertyNode parent;

    /** Children of the receiver. */
    protected PropertyNode[] children;

    /** Path of the receiver. */
    protected String canonicalPath;

    /** will this object be treated as a leaf or as expandible */
    protected boolean aggregate;

    /** in cases where the node corresponds to an array entry, keep index here */
    protected int idx;

    /** Only primitive types in Edit mode should be editable */
    protected boolean isEditable;


    /**
     * PropertyNode constructor that takes object, no parent or index
     *
     * @param property Object
     */
    protected PropertyNode(Object property, boolean editable) {
      this(null, property, -1, editable);
    }

    /**
     * PropertyNode constructor that takes object, no parent or index
     *
     * @param property Object
     */
    protected PropertyNode(Object property) {
      this(null, property, -1, false);
    }

    /**
     * PropertyNode constructor that takes parent as well as object
     *
     * @param parent PropertyNode
     * @param property Object
     */
    protected PropertyNode(PropertyNode parent, Object property, boolean editable) {
      this(parent, property, -1, editable);
    }

    /**
     * PropertyNode constructor taht takes parent, object and an index. used by
     * arrays
     *
     * @param parent PropertyNode
     * @param property Object
     * @param index int
     */
    protected PropertyNode(PropertyNode parent, Object property, int index, boolean editable) {
      this.parent = parent;
      this.property = property;
      this.idx = index;
      aggregate = false;
      this.isEditable = !aggregate && editable;

      if (property instanceof OpenSimObject)
        aggregate = true;
      else if (property instanceof Property) {
        Property.PropertyType propType = ( (Property) property).getType();
        if (propType == Property.PropertyType.Obj ||
            propType == Property.PropertyType.BoolArray ||
            propType == Property.PropertyType.IntArray ||
            propType == Property.PropertyType.FltArray ||
            propType == Property.PropertyType.DblArray ||
            propType == Property.PropertyType.StrArray ||
            propType == Property.PropertyType.ObjArray) {
          aggregate = true;
        }

      }
    }

    /**
     * Returns the the string to be used to display this leaf in the JTree.
     */
    public String getValue() {
      if (property instanceof OpenSimObject)
        return getName();
      else if (property instanceof Property)
        return ( (Property) property).toString();
      else if (idx != -1)
        return (String) property;

        return "unknownValue";
    }

    public String getName() {
      if (property instanceof OpenSimObject)
        return ( (OpenSimObject) property).getName();
      else if (property instanceof Property)
        return ( (Property) property).getName();
      else if (property instanceof String)
       return ( "["+String.valueOf(idx)+"]");

      return ("unknown type!");
    }

    public String toString() {
      return getName();
    }

    /**
     * Returns the parent of the receiver.
     */
    public PropertyNode getParent() {
      return parent;
    }

    /**
     * Returns true if the receiver represents a leaf, that is it is
     * isn't a directory.
     */
    public boolean isLeaf() {
      return!aggregate;
    }

    /**
     * Loads the children, caching the results in the children
     * instance variable.
     */
    protected PropertyNode[] getChildren() {
      return children;
    }

    /**
     * Recursively loads all the children of the receiver.
     */
    protected void loadChildren() {
      children = createChildren();
      for (int counter = children.length - 1; counter >= 0; counter--) {
        Thread.yield(); // Give the GUI CPU time to draw itself.
        if (!children[counter].isLeaf()) {
          children[counter].loadChildren();
        }
      }
    }

    /**
     * Loads the children of of the receiver.
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
            retArray[i] = new PropertyNode(this, prop, isEditable);
          }
        }
        else if (property instanceof Property) {
          Property rdprop = (Property) property;
          Property.PropertyType propType = rdprop.getType();
          if (propType == Property.PropertyType.Obj) {
            OpenSimObject childObj = (OpenSimObject) rdprop.getValueObj();
            PropertySet props = ( (OpenSimObject) childObj).getPropertySet();
            retArray = new PropertyNode[props.getSize()];
            for (int i = 0; i < props.getSize(); i++) {
               Property prop=null;
               try {
                  prop = props.get(i);
               } catch (IOException ex) {
                  ex.printStackTrace();
               }
              retArray[i] = new PropertyNode(this, prop, isEditable);
            }
          }
          else if (propType == Property.PropertyType.DblArray) {
            ArrayDouble dblArray = rdprop.getValueDblArray();
            retArray = new PropertyNode[dblArray.getSize()];
            for (int i = 0; i < dblArray.getSize(); i++) {
              double value = dblArray.getitem(i);
              retArray[i] = new PropertyNode(this, Double.toString(value), i, isEditable);
            }
          }
          else if (propType == Property.PropertyType.StrArray) {
            ArrayStr strArray = rdprop.getValueStrArray();
            retArray = new PropertyNode[strArray.getSize()];
            for (int i = 0; i < strArray.getSize(); i++) {
              String value = strArray.getitem(i);
              retArray[i] = new PropertyNode(this, value, i, isEditable);
            }
          }
          else if (propType == Property.PropertyType.IntArray) {
            ArrayInt intArray = rdprop.getValueIntArray();
            retArray = new PropertyNode[intArray.getSize()];
            for (int i = 0; i < intArray.getSize(); i++) {
              int value = intArray.getitem(i);
              retArray[i] = new PropertyNode(this, new Integer(value), i, isEditable);
            }
          }
          else if (propType == Property.PropertyType.ObjArray) {
            retArray = new PropertyNode[rdprop.getValueObjArraySize()];
            for (int i = 0; i < rdprop.getValueObjArraySize(); i++) {
              OpenSimObject subobj = rdprop.getValueObjPtr(i);
              retArray[i] = new PropertyNode(this, subobj, i, isEditable);
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

    /**
     * Gets the path from the root to the receiver.
     */
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

    /**
     * Sets the children of the receiver, updates the total size,
     * and if generateEvent is true a tree structure changed event
     * is created.
     */
    protected void setChildren(PropertyNode[] newChildren,
                               boolean generateEvent) {

      children = newChildren;

      if (generateEvent) {
        PropertyNode[] path = getPath();

        fireTreeStructureChanged(OpenSimObjectModel.this, path, null,
                                 null);

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
        int[] index = {
            getIndexOfChild(parent, this)};
        Object[] children = {
            this};

        fireTreeNodesChanged(OpenSimObjectModel.this, path, index,
                             children);
      }
    }

    /**
     * getObject
     *
     * @return Object
     */
    private Object getObject() {
      return property;
    }

    /**
     * isEditable
     *
     * @return boolean
     */
    public boolean editable() {
      return !aggregate && this.isEditable;
    }
  }

  /**
   * PropertyNodeLoader can be used to reload all the children of a
   * particular node. It first resets the children of the PropertyNode
   * it is created with, and in its run method will reload all of
   * that nodes children. PropertyNodeLoader may not be running in the event
   * dispatching thread. As swing is not thread safe it is important
   * that we don't generate events in this thread. SwingUtilities.invokeLater
   * is used so that events are generated in the event dispatching thread.
   */
  class PropertyNodeLoader
      implements Runnable {
    /** Node creating children for. */
    PropertyNode node;

    PropertyNodeLoader(PropertyNode node) {
      this.node = node;
      node.setChildren(node.createChildren(), true);
    }

    public void run() {
      PropertyNode[] children = node.getChildren();

      for (int counter = children.length - 1; counter >= 0; counter--) {
        if (!children[counter].isLeaf()) {
          reloadNode = children[counter];
          loadChildren(children[counter]);
          reloadNode = null;
        }
        if (!isValid) {
          counter = 0;
        }
      }
      if (isValid) {
        SwingUtilities.invokeLater(new Runnable() {
          public void run() {
            node.setChildren(node.getChildren(), true);
            synchronized (OpenSimObjectModel.this) {
              reloadCount--;
              OpenSimObjectModel.this.notifyAll();
            }
          }
        });
      }
      else {
        synchronized (OpenSimObjectModel.this) {
          reloadCount--;
          OpenSimObjectModel.this.notifyAll();
        }
      }
    }

    protected void loadChildren(PropertyNode node) {
      if (!node.isLeaf()) {
        final PropertyNode[] children = node.createChildren();

        for (int counter = children.length - 1; counter >= 0;
             counter--) {
          if (!children[counter].isLeaf()) {
            children[counter].loadChildren();
          }
          if (!isValid) {
            counter = 0;
          }
        }
        if (isValid) {
          final PropertyNode fn = node;

          // Reset the children
          SwingUtilities.invokeLater(new Runnable() {
            public void run() {

              fn.setChildren(children, true);
              fn.nodeChanged();
            }
          });
        }
      }
      else {
      }
    }
  }

}
