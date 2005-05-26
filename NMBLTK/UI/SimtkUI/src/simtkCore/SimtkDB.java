package simtkCore;

/**
 * We're importing simtkBlock library here which is an example model just so that the code can
 * be compiled (i.e. rdModel is defined).
 * SWIG generated wrappers entangle the model specific JNI code (rdBlock) with the generic code
 * (rdActuatedModel_SDFast) and lower classes. All implementations go thru one class (rdBlockModuleJNI)
 * that is declared final with static methods.
 *
 * @todo separate simtkModel wrappers into two classes, generic one that's imported here and is part of simtk and a model specific
 * wrapper that can be loaded separately. This way the code doesn't have to import the simtkBlock package.
 * Ayman 03/24/04.
 */
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Toolkit;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Vector;

import javax.swing.tree.TreeModel;

import simtkCommands.SimtkVisChangeCommand;
import simtkModel.rdActuatorSet;
import simtkModel.rdContactForceSet;
import simtkModel.rdControlSet;
import simtkModel.rdModel;
import simtkModel.rdObject;
import simtkModel.rdVisibleObject;
import simtkModel.rdVisibleProperties;
import simtksuS26Pkg.rdActuatedModel_SDFast;
import simtkui.SimDlgGetName;
import simtkui.SimtkApp;
import simtkui.edit.SimtkObjectViewerDlg;
import simtkuiEvents.SimtkCloseModelEvent;
import simtkuiEvents.SimtkModelRedisplayEvent;
import simtkuiEvents.SimtkNewModelEvent;
import simtkuiEvents.SimtkNewSimEnvEvent;
import simtkuiEvents.SimtkUpdateTreeEvent;
import simtkuiEvents.SimtkVisibilityChangeEvent;
/**
 * <p>Title: SimtkDB</p>
 *
 * <p>Description: SimtkDB is the maintainer for all tables of models,
 * simulations, and all data being used for simulation. It is implemented as a
 * singleton to have access to it from anywhere in the Simtk environment without
 * having to pass around a reference using SimtkDB.getInstance().
 * This class and classes accessible from it represent the Model part of the
 * Model_View_Controller acrchitecture implemented in
 * Simtk and as such sould not have any UI or Viewing specific
 * data. It extends Observale so that View and UI can register their interest in
 * Model changes while being decoupled from it.</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 *
 * @author Ayman Habib
 * @version 1.0
 */
public class SimtkDB extends Observable {
  /**
   * The tree model _dbTreeModel is the keeper of the list of models currently loaded
   * _modelTable is a hashtable that maps model names to actual models.
   * _dbTreeModel is another representation of the same table represented as a tree.
   */
  private SimtkDBTreeModel _dbTreeModel = new SimtkDBTreeModel();
  private Hashtable _modelTable = new Hashtable();
  private Hashtable _simenvTable = new Hashtable();
  static boolean _instanceFlag = false;
  private Hashtable _modelChangedTable = new Hashtable(); // flags to indicate if model has changed
  static SimtkDB _dInstance;

  /*
   * Maintain a map between model names and models. This should make command unique without having
   * to assign IDs that may not regenerate.
   */

  /**
   * initialize is a place holder for initialization code, if any, that's needed
   * to setup internal data-structures.
   */
  public void initialize() {
  }

  /**
   * getInstance is the only way to access the single SimtkDB instance
   * maintained by this class.
   *
   * @return SimtkDB
   */
  static public SimtkDB getInstance() {
    if (!_instanceFlag) {
      _instanceFlag = true;
      _dInstance = new SimtkDB();
      _dInstance.initialize();
    }
    return _dInstance;
  }

  /**
   * getTreeModel queries the database for the TreeModel which is an abstract
   * tree representation of the database
   *
   * @return TreeModel
   */
  public TreeModel getTreeModel() {
    return _dbTreeModel;
  }

  /**
   * addModel is the preferred way to add a model to the SimtkDB. This is just a
   * book-keeping operatoin, the actual openning of a file to instantiate the
   * model is done somewhere-else.
   *
   * @param mdl rdModel: the model to be added
   * @return boolean true on success. Possible causes of failure are duplicate
   *   names or some other database consistecy issue. Models should probably
   *   provide a sanity check function (validate) to be invoked before the
   *   model is added to make sure the model has made it safely through the
   *   journey from whatever shape the model started in to Simtk.
   */
  public boolean addModel(rdModel mdl, String SimEnvName)
  {
    boolean success = true;

    // Update database
    if (_modelTable.containsKey(mdl.getName())){
      return false;
    }
    // Create new simenv if not passed in
    if (SimEnvName!= null){
      if (getSimtkSimEnv(SimEnvName)==null)
        createNewSimEnv(SimEnvName);
    }
    SimtkSimEnv newSimEnv = (SimEnvName==null)? createNewSimEnv() : getSimtkSimEnv(SimEnvName);
    newSimEnv.setModel(mdl);
    // Update tree to reflect new model
    _dbTreeModel.updateSimEnvTree(newSimEnv);
    _modelTable.put(mdl.getName(), mdl);
    _modelChangedTable.put(mdl.getName(), Boolean.FALSE);
    // Notify the world to update its view
    SimtkNewModelEvent ev = new SimtkNewModelEvent(newSimEnv);
    setChanged();
    this.notifyObservers(ev);
    return success;
  }

  /**
   * createNewSimEnv
   *
   * @param SimEnvName String
   */
  public SimtkSimEnv createNewSimEnv(String SimEnvName) {
    // Instantiate the new simulation environment
   SimtkSimEnv newSimEnv = new SimtkSimEnv(SimEnvName);
   // Book keeping to keep track of newSimEnv
   _dbTreeModel.addSimEnvToTree(newSimEnv);
   _simenvTable.put(newSimEnv.getName(), newSimEnv);

   // Notify the world to update its view
   SimtkNewSimEnvEvent ev = new SimtkNewSimEnvEvent(newSimEnv);
   setChanged();
   this.notifyObservers(ev);
   return newSimEnv;
 }

  /**
   * createNewSimEnv, no names passed
   *
   * @return SimtkSimEnv
   */
  public SimtkSimEnv createNewSimEnv() {
    String baseName = "SimEnv";
    // MAke name for new environment
    int idx = _simenvTable.size()+1;
    String proposedName = baseName+idx;
    while(_simenvTable.containsKey(proposedName)){
      idx++;
      proposedName = baseName+idx;
   }
   return createNewSimEnv(proposedName);
  }

  public rdModel getModelByName(String modelName)
  {
    if (_modelTable.containsKey((Object) modelName))
      return (rdModel) _modelTable.get((Object) modelName);
    // Should never get here
    return null;
  }

  public SimtkSimEnv getSimtkSimEnv(String simekEnvName)
  {
    if (_simenvTable.containsKey((Object) simekEnvName))
     return (SimtkSimEnv) _simenvTable.get((Object) simekEnvName);
   return null;
  }
  /**
   * getNumberOfModels returns the number of models currently open in the
   * application
   *
   * @return int
   */
  public int getNumberOfModels()
  {
    return _modelTable.size();
  }

  /**
   * needToSave: Checks if a specific model has been changed and needs to be
   * saved
   *
   * @param modelName String
   * @return boolean
   */
  public boolean needToSave(String modelName)
  {
    return (_modelChangedTable.get((Object) modelName)==Boolean.TRUE);
  }

  /**
   * confirmOnExit Checks to see if any model has changed and not saved (has a
   * dirty bit)
   *
   * @return boolean
   */
  public boolean confirmOnExit()
  {
    boolean someModelChanged = false;
    Enumeration mapElements = _modelChangedTable.elements();
    Enumeration mapKeys = _modelChangedTable.keys();
    while(mapElements.hasMoreElements() && !someModelChanged){
      someModelChanged = (mapElements.nextElement()==Boolean.TRUE);
    }
    return someModelChanged;
  }
  /**
   * setProperties
   *
   * @param mdlName String
   * @param rdVisObj rdVisibleObject
   * @param _selectedProperty int
   *
   */
  public void setProperties(String mdlName, rdVisibleObject rdVisObj,
                            int property) {
    // Change the model
    // Check against old value so that you don't fire an event unnecessarily
    switch (property) {
      case SimtkVisChangeCommand.WIREFRAME:
        rdVisObj.getVisibleProperties().setDisplayPreference(rdVisibleProperties.WireFrame);
        break;
      case SimtkVisChangeCommand.FLAT_SHADED:
        rdVisObj.getVisibleProperties().setDisplayPreference(rdVisibleProperties.FlatShaded);
        break;
      case SimtkVisChangeCommand.NONE:
        rdVisObj.getVisibleProperties().setDisplayPreference(rdVisibleProperties.None);
       break;
     case SimtkVisChangeCommand.BOUNDING_BOX:
       rdVisObj.getVisibleProperties().setDisplayPreference(rdVisibleProperties.BoundingBox);
       break;
     case SimtkVisChangeCommand.SHOW_NORMALS:
       rdVisObj.getVisibleProperties().setShowNormals(true);
       break;
     case SimtkVisChangeCommand.HIDE_NORMALS:
       rdVisObj.getVisibleProperties().setShowNormals(false);
       break;
     case SimtkVisChangeCommand.SHOW_GEOM_CS:
       rdVisObj.getVisibleProperties().setShowAxes(true);
       break;
     case SimtkVisChangeCommand.HIDE_GEOM_CS:
       rdVisObj.getVisibleProperties().setShowAxes(false);
       break;
      case SimtkVisChangeCommand.GOURAUD_SHADED:
      default:
        rdVisObj.getVisibleProperties().setDisplayPreference(rdVisibleProperties.GouraudShaded);
        break;
    }
    processVisibleChange(mdlName, rdVisObj);
    return;

  }

  /**
   * processVisibleChange
   *
   * @param mdlName String
   * @param rdVisObj rdVisibleObject
   */
  public void processVisibleChange(String mdlName, rdVisibleObject rdVisObj) {
    _modelChangedTable.put(mdlName, Boolean.TRUE);
    // Create an event to signal change
    SimtkVisibilityChangeEvent evnt = new SimtkVisibilityChangeEvent(this, mdlName, rdVisObj);
    setChanged();
    this.notifyObservers(evnt);
  }

  /**
   * removeModel
   *
   * @param string String
   */
  public void removeModel(String mdlName) {
    // Remove named model from hashTables and Tell Viw to do the same
    rdModel mdl = (rdModel) _modelTable.get(mdlName);
    _modelTable.remove((Object) mdlName);
    _modelChangedTable.remove((Object) mdlName);
//    _dbTreeModel.removeModel(mdl);
    SimtkCloseModelEvent ev = new SimtkCloseModelEvent(mdlName);
    setChanged();
    this.notifyObservers(ev);
  }

  /**
   * saveModel: attempts to save the specified model to its xml representation
   *
   * @param mdlName String
   * @return boolean
   */
  public boolean saveModel(String mdlName) {
    rdModel mdl = (rdModel) _modelTable.get(mdlName);
    String filename = mdl.getModelDescriptionFileName();
    if (filename!= null && filename.length()!= 0)
      mdl.print(filename);
    else {
      // Query user for file name
      SimDlgGetName getNameDlg = new SimDlgGetName("Preferences file (xml)");
      getNameDlg.setVisible(true);
      if (!getNameDlg.userConfirmed())
        return false;
      // User confirmed
      String fileName =  getNameDlg.getName();
      // Don't need the dialog anymore
      getNameDlg.dispose();
      mdl.print(fileName);
    }
    _modelChangedTable.put((Object) mdlName, Boolean.FALSE);
    return false;
  }

  /**
   * updateModelDisplay is called to trigger redisplay of model during animation
   *
   * @param mdl rdModel
   */
  public void updateModelDisplay(rdModel mdl)
  {
    SimtkModelRedisplayEvent ev = new SimtkModelRedisplayEvent(mdl, mdl.getName());
    setChanged();
    this.notifyObservers(ev);
  }
  /**
   * reCreateModelDisplay is called to trigger recreation of the model display.
   *
   * @param mdl rdModel
   */
  public void reCreateModelDisplay(rdModel mdl)
  {
    SimtkModelRedisplayEvent ev = new SimtkModelRedisplayEvent(mdl, mdl.getName(), true);
    setChanged();
    this.notifyObservers(ev);
  }
  /**
   * reviewObject Shows dialog of generic object editor
   *
   * @param mdlName String
   * @param rdObj rdObject
   */
  public void reviewObject(String mdlName, rdObject rdObj) {
    // instantiate and invoke dialog based on rdObj
    SimtkObjectViewerDlg dlg = new SimtkObjectViewerDlg((Frame)SimtkApp.getTopComponent(), rdObj, false, mdlName);
    dlg.pack();
    //Center the window
    dlg.center();
    dlg.setVisible(true);
  }

  /**
   * exportObject
   *
   * @param rdObj rdObject
   */
  public boolean exportObject(rdObject rdObj) {
    SimDlgGetName getNameDlg = new SimDlgGetName("XML File ");
    getNameDlg.setVisible(true);
    if (!getNameDlg.userConfirmed())
      return false;
    // User confirmed
    String fileName =  new String(getNameDlg.getName());
    // Don't need the dialog anymore
    getNameDlg.dispose();
    rdObj.print(fileName);
    return true;
  }

  /**
   * editObject
   *
   * @param mdlName String
   * @param rdObj rdObject
   */
  public void editObject(String mdlName, rdObject rdObj) {

    // instantiate and invoke dialog based on rdObj
   SimtkObjectViewerDlg dlg = new SimtkObjectViewerDlg((Frame)SimtkApp.getTopComponent(), rdObj, true, mdlName);
   dlg.pack();
   //Center the window
  Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
  Dimension frameSize = dlg.getSize();
  if (frameSize.height > screenSize.height) {
    frameSize.height = screenSize.height;
  }
  if (frameSize.width > screenSize.width) {
    frameSize.width = screenSize.width;
  }
  dlg.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
  dlg.setVisible(true);
 }

  /**
   * getEnvForModel retrieves the SimtkEnv corresponding to specified model
   *
   * @param mdlToClose String
   * @return SimtkSimEnv
   */
  public SimtkSimEnv getEnvForModel(String mdlName) {
    return _dbTreeModel.findSimEnvForModel(mdlName);
  }

  /**
   * removeSimEnv removes a full Simulation environment from the system
   *
   * @param simEnv SimtkSimEnv
   */
  public void removeSimEnv(SimtkSimEnv simEnv) {
    // Remove environment from tree
    _dbTreeModel.removeEnvironment(simEnv);
    // remove model from model maintainance tables and notify observers
    removeModel(simEnv.getModel().getName());
    // Cleanup _simenvTable
    _simenvTable.remove(simEnv.getName());

  }

  /**
   * addControlSet: Adds controlset to the simulation manager
   *
   * @param controlSet rdControlSet
   * @param SimEnvName String
   * @return boolean
   * @todo Check if we can put some SWIG pragma to make sure the controlSet
   *   doesn't get deleted by the garbage collector. For now we live with the
   *   kluge of keeping a reference with the simenv
   */
  public boolean addControlSet(rdControlSet controlSet, String SimEnvName)
  {
    boolean success = true;

    SimtkSimEnv simEnv = (SimEnvName==null)? createNewSimEnv() : getSimtkSimEnv(SimEnvName);
    // The only reason we keep reference to controlSet with simEnv is to avoid garbage collection
    simEnv.controlSet = controlSet;
    simEnv.setControlSet(controlSet);
    // Notify the world to update its view
    SimtkUpdateTreeEvent ev = new SimtkUpdateTreeEvent(simEnv);
    setChanged();
    this.notifyObservers(ev);
    return success;
  }

  /**
   * addContactForceSet
   *
   * @param newContactSet rdContactForceSet
   * @param string String
   * @return boolean
   */
  public boolean addContactForceSet(rdContactForceSet newContactSet,
                                    String SimEnvName) {
    boolean success = true;

    SimtkSimEnv simEnv = (SimEnvName==null)? createNewSimEnv() : getSimtkSimEnv(SimEnvName);
    simEnv.contactForceSet = newContactSet;
    for(int i=0; i < newContactSet.getSize(); i++)
      ((rdActuatedModel_SDFast)simEnv.getModel()).getContactForceSet().append(newContactSet.get(i));
    SimtkUpdateTreeEvent ev = new SimtkUpdateTreeEvent(simEnv);
   setChanged();
   this.notifyObservers(ev);
   return success;

  }

  /**
   * addActuatorSet
   *
   * @param newActuatorset rdActuatorSet
   * @param string String
   * @return boolean
   */
  public boolean addActuatorSet(rdActuatorSet newActuatorset, String SimEnvName) {
    boolean success = true;
   SimtkSimEnv simEnv = (SimEnvName==null)? createNewSimEnv() : getSimtkSimEnv(SimEnvName);
   /** We'll keep around a reference to newActuatorset so that it's not deleted by garbage collector */
   simEnv.actuatorSet = newActuatorset;
  Method actuatorsGetter = null;
  try {
    actuatorsGetter = simEnv.getModel().getClass().getMethod("getActuatorSet", null);
  }
  catch (SecurityException ex) {
    return false;
  }
  catch (NoSuchMethodException ex) {
    return false;
  }
   rdActuatorSet actuators = null;
   try {
     actuators = (rdActuatorSet) actuatorsGetter.invoke(simEnv.getModel(), null);
   }
   catch (InvocationTargetException ex1) {
     return false;
  }
   catch (IllegalArgumentException ex1) {
     return false;
   }
   catch (IllegalAccessException ex1) {
     return false;
  }

   for(int i=0; i < newActuatorset.getSize(); i++)
     actuators.append(newActuatorset.get(i));

   SimtkUpdateTreeEvent ev = new SimtkUpdateTreeEvent(simEnv);
   setChanged();
   this.notifyObservers(ev);
   return success;
  }

  public boolean addModelObject(String SimEnvName, String objectName, rdObject modelObject)
  {
    boolean success = true;

    SimtkSimEnv simEnv = (SimEnvName==null)? createNewSimEnv() : getSimtkSimEnv(SimEnvName);
    // The only reason we keep reference to controlSet with simEnv is to avoid garbage collection
    simEnv.addModelObject(objectName, modelObject);
    // Notify model tree to update its view
    SimtkUpdateTreeEvent ev = new SimtkUpdateTreeEvent(simEnv);
    setChanged();
    this.notifyObservers(ev);
    // Notify display to update its view
    SimtkModelRedisplayEvent displayev = new SimtkModelRedisplayEvent(simEnv, simEnv.getModel().getName(), true);
    setChanged();
    this.notifyObservers(displayev);
   return success;
  }

  /**
   * getAvailableQuantities
   *
   * @param plotQuantitiesModel DefaultListModel
   */
  public void getAvailableQuantities(Vector plotQuantitiesModel) {
    Enumeration envs = _simenvTable.elements();
   while(envs.hasMoreElements()){
      SimtkSimEnv env = (SimtkSimEnv)envs.nextElement();
      env.getAvailableQuantities(plotQuantitiesModel);
    }
  }
}
