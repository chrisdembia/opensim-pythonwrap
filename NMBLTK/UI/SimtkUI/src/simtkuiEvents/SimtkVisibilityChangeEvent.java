package simtkuiEvents;

import simtkModel.rdVisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * This event is used to communicate visibility change of an rdVisibleObject.
 * The actual change is not part of the event as it's used to tell the View to
 * update the display of the object in question from the database which has the
 * actual change already.
 */
public class SimtkVisibilityChangeEvent extends SimtkSimulationEvent {
  private String _modelName;
  private rdVisibleObject _object;

  public SimtkVisibilityChangeEvent(Object source) {
    super(source);
  }
  public SimtkVisibilityChangeEvent(Object source, String modelName, rdVisibleObject rObj) {
    super(source);
    _modelName = modelName;
    _object = rObj;
  }
  public String getModelName()
  {
    return _modelName;
  }
  public rdVisibleObject getObject()
  {
    return _object;
  }
 }
