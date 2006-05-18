package simtkUtils;

import opensimModel.Model;
import opensimModel.OpenSimObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * A class to represent the abstraction of a selection from the user interface
 * or the display/graphics window
 */
public class SimtkSelection {
  private Model _mdl;    // Selected model
  private OpenSimObject _obj;   // Selected object within model, could be same as _mdl if whole model is selected
  public SimtkSelection() {
    _mdl = null;
    _obj = null;
  }
  public SimtkSelection(Model mdl) {
    _mdl = mdl;
    _obj = null;
  }
  public SimtkSelection(Model mdl, OpenSimObject obj) {
    _mdl = mdl;
    _obj = obj;
  }
  void setModel(Model mdl)
  {
    _mdl = mdl;
  }
  Model getModel()
  {
    return _mdl;
  }
  void setObject(OpenSimObject obj)
  {
    _obj = obj;
  }
  OpenSimObject getObject()
  {
    return _obj;
  }
}
