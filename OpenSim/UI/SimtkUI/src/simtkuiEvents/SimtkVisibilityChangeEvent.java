package simtkuiEvents;

import opensimModel.VisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * This event is used to communicate visibility change of an VisibleObject.
 * The actual change is not part of the event as it's used to tell the View to
 * update the display of the object in question from the database which has the
 * actual change already.
 */
public class SimtkVisibilityChangeEvent extends SimtkSimulationEvent {
  private String _modelName;
  private VisibleObject _object;

  public SimtkVisibilityChangeEvent(Object source) {
    super(source);
  }
  public SimtkVisibilityChangeEvent(Object source, String modelName, VisibleObject rObj) {
    super(source);
    _modelName = modelName;
    _object = rObj;
  }
  public String getModelName()
  {
    return _modelName;
  }
  public VisibleObject getObject()
  {
    return _object;
  }
 }
