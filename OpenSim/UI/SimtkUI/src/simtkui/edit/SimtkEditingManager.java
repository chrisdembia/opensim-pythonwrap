package simtkui.edit;

import java.util.Hashtable;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * A Class to manager which editor to be invoked for specific types. As of now
 * it handles only classes not derived from OpenSimObject but that can easily be
 * changed. SimtkEditingManager is consulted before any editing operation is performed
 */
public final class SimtkEditingManager {
  static boolean _instanceFlag = false;
  static SimtkEditingManager _dInstance;
  Hashtable editorsTable= new Hashtable();

  private SimtkEditingManager() {
    // Initially no special casing. all types are edited with
  }

  static public SimtkEditingManager getInstance() {
    if (!_instanceFlag) {
      _instanceFlag = true;
      _dInstance = new SimtkEditingManager();
    }
    return _dInstance;
  }

  public void register(Class className, Class editorClassName)
  {
      editorsTable.put((Object)className, (Object) editorClassName);
  }

  public void unRegister(Class className)
  {
    editorsTable.remove((Object) className);
  }

  public void editObject(Object obj)
  {
    Class objClass = obj.getClass();
    if (editorsTable.containsKey(objClass)){
      Class editorClass = (Class) editorsTable.get(objClass);
     }
  }
}
