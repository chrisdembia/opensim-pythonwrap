package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import opensimModel.Model;
import opensimModel.VisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * This is a base class for all commands that change model visibility
 * (Wireframe, Solid, shaded, ...)
 */
abstract public class SimtkVisChangeCommand extends SimtkCommand implements SimtkUndoableCommand {

  public static final int NONE = 0;
  public static final int WIREFRAME = 1;
  public static final int FLAT_SHADED = 3;
  public static final int GOURAUD_SHADED = 4;
  public static final int PHONG_SHADED = 5;
  public static final int BOUNDING_BOX = 6;

  public static final int SHOW_NORMALS = 7;
  public static final int HIDE_NORMALS = 8;
  public static final int SHOW_GEOM_CS = 9;
  public static final int HIDE_GEOM_CS = 10;

  boolean _modelNameIsSet = false;
  boolean _objectIsSet = false;
  boolean _properyIsSet = false;
  private int  _selectedProperty=-1;

  /** The command saves its state with it in case it gets undone. This is done using Memento
   * design pattern where a class responsible for the save/restore state is instantiated and kept
   * around.
   */
  private Memento _state=null;

  /**
   * SimtkVisChangeCommand is the base class for all Visibility changing commands
   */
  public  SimtkVisChangeCommand()
   {
     super();
     putValue(Action.NAME, getCommandName());
     _selectedProperty = GOURAUD_SHADED;
   }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
    super.setCommandParams(params);
    if (_cmdParams.containsKey("ModelName"))
      _modelNameIsSet = true;
    if (_cmdParams.containsKey("ObjectName"))
      _objectIsSet = true;
  }

  /**
   * setModelName: sets the name of the Model to which the object belongs
   *
   * @param mdlName String
   */
  public void setModelName(String mdlName)
  {
    this._cmdParams.put("ModelName", mdlName);
   _modelNameIsSet = true;
  }

  /**
   * setObject: sets the reference to the object whose visibility is affected
   *
   * @param rObj VisibleObject
   */
  public void setObject(VisibleObject rObj)
  {
    this._cmdParams.put("Object", rObj);
   _objectIsSet = true;

  }

  /**
   * setProperty: sets the value of the property that needs to be applied to the
   * selected model object
   *
   * @param newVisProperty int
   */
  public void setProperty(int newVisProperty)
  {
    _selectedProperty = newVisProperty;
    _properyIsSet = true;
  }

  public boolean execute() {
    boolean success = true;
    // Make sure there's a model
    String mdlName = (String) _cmdParams.get("ModelName");
    VisibleObject rdVisObj;
    Object object = _cmdParams.get("Object");
    if (object instanceof VisibleObject)
      rdVisObj = (VisibleObject) object;
    else if (object instanceof String) {
      Model mdl = SimtkDB.getInstance().getModelByName(mdlName);
      String objectName = object.toString();
      rdVisObj = mdl.getVisibleObjectByName(objectName);
      if (rdVisObj == null) // Object was not found
        return false;
    }
    else
      return false;

    SimtkDB.getInstance().setProperties(mdlName, rdVisObj, _selectedProperty);
    return success;
  }

  /**
   * Implementation of the methods for the SimtkUndoableCommand interface:
   *
   * canUndo tells if the command is undoable. The fact that the class implements the interface
   * SimtkUndoableCommand should intself imply that this method returns true.
   *
   * @return boolean
   */
  public boolean canUndo()
  {
    return true;
  }
  /**
   * For an undoable command this is the function called by the execution manager to ask the
   * command to save its state.
   */
  public void saveState()
  {
    String mdlName = (String) _cmdParams.get("ModelName");
    String objectName = _cmdParams.get("Object").toString();
    Model mdl =  SimtkDB.getInstance().getModelByName(mdlName);
    VisibleObject obj = mdl.getVisibleObjectByName(objectName );
    _state = new Memento(obj, _selectedProperty);
  }
  /**
   * reverse execute the command (restore state to that before execute).
   *
   * @return boolean
   */
  public boolean undo()
  {
    String mdlName = (String) _cmdParams.get("ModelName");
    String objectName = _cmdParams.get("Object").toString();
    Model mdl =  SimtkDB.getInstance().getModelByName(mdlName);
    VisibleObject obj = mdl.getVisibleObjectByName(objectName );
    SimtkDB.getInstance().setProperties(mdlName, obj, _state.getReverseProp());
    return true;
  }

  class Memento {
    /**
     * Memento
     *
     * @param VisibleObject obj objects whose state is being saved and int newProperty property to be set
     */
    private int _reverseProp;
    public Memento(VisibleObject obj, int newProperty) {
      // Actual display preference
      if (newProperty==WIREFRAME ||
          newProperty==FLAT_SHADED ||
          newProperty==GOURAUD_SHADED ||
          newProperty==BOUNDING_BOX ||
          newProperty==NONE ||
          newProperty==PHONG_SHADED ){
        _reverseProp = obj.getVisibleProperties().getDisplayPreference().swigValue();
      }
      else if (newProperty == SHOW_NORMALS || newProperty == HIDE_NORMALS) {
        _reverseProp = obj.getVisibleProperties().getShowNormals() ?
            SHOW_NORMALS : HIDE_NORMALS;
      }
      else if (newProperty == SHOW_GEOM_CS || newProperty == HIDE_GEOM_CS) {
        _reverseProp = obj.getVisibleProperties().getShowAxes() ? SHOW_GEOM_CS :
            HIDE_GEOM_CS;
      }

    }
    /**
     * retrieve property that needs to be reapplied.
     * @return int
     */
    int getReverseProp()
    {
      return _reverseProp;
    }
  }
}
