package simtkUtils;

import simtkModel.rdModel;
import simtkModel.rdObject;

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
  private rdModel _mdl;    // Selected model
  private rdObject _obj;   // Selected object within model, could be same as _mdl if whole model is selected
  public SimtkSelection() {
    _mdl = null;
    _obj = null;
  }
  public SimtkSelection(rdModel mdl) {
    _mdl = mdl;
    _obj = null;
  }
  public SimtkSelection(rdModel mdl, rdObject obj) {
    _mdl = mdl;
    _obj = obj;
  }
  void setModel(rdModel mdl)
  {
    _mdl = mdl;
  }
  rdModel getModel()
  {
    return _mdl;
  }
  void setObject(rdObject obj)
  {
    _obj = obj;
  }
  rdObject getObject()
  {
    return _obj;
  }
}
