package simtkCore;

import java.io.File;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Vector;

import javax.swing.Timer;

import simtkModel.rdActuatorSet;
import simtkModel.rdArrayStr;
import simtkModel.rdContactForceSet;
import simtkModel.rdControlSet;
import simtkModel.rdIntegRKF;
import simtkModel.rdManager;
import simtkModel.rdModel;
import simtkModel.rdObject;
import simtkModel.rdSimtkAnimationCallback;
import simtkModel.rdStorage;
import simtkModel.suMarkerSet;
import simtkUtils.SwingWorker;
import simtkView.SimtkMdlInternalFrame;
import simtkView.SimtkViewDB;
import simtkui.SimtkApp;
import simtkui.SimtkStoragePreferences;
import simtkuiEvents.SimtkSimEnvStateChangeEvent;
import simtkuiEvents.SimtkSimulationEvent;

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
 *
 * @todo Make contactForceSet and actuatorSet visible in the tree and make them
 *   private with getter and setter methods
 *  @todo USe the generic ModelObjects and SimulationObejcts rather than PDB specific concepts
 * of model, actuators, contacts.
 */
public class SimtkSimEnv extends Observable {

  /** Simulation manager */
  private rdManager manager=null;
  private rdModel model=null;
  /** Keep around contactForceSet and actuatorSet to be used in model construction */
  rdControlSet controlSet=null;
  rdContactForceSet contactForceSet=null;
  rdActuatorSet actuatorSet=null;
  suMarkerSet markerSet=null;

  private String _infoStatus="";
  private String name;
  /** Keep a reference to simulation thread ni case it needs to be interrupted later */
  private SwingWorker simulationThread=null;
  private Timer timer=null;
  private int status;
  private rdSimtkAnimationCallback animationCallback=null;
  private SimtkStoragePreferences storagePrefs=null;
  private File _preferredDirectory;
  // Attributes to control the progress bar shown for the internalframe
  private double _rangeStart, _rangeEnd;
  private boolean _deterministicProgress;
  private double currentTime;
  // Hashtable to hold objects that do not belong to the model but can be provided by users (e.g. markers)
  // the name modelObjects is due to the fact that they would show under the model subtree.
  private Hashtable _modelObjects = new Hashtable(4);

  /** The follwoing enums describe the status of the simulation environment with regard to ability to start simulation */
  public static final int NOT_READY = 1;
  public static final int LOADING = 2;
  public static final int READY = 3;
  public static final int STARTED = 4;
  public static final int PLAYBACK = 5;

  public SimtkSimEnv(String name) {
    status=NOT_READY;
    this.name = name;
    storagePrefs = new SimtkStoragePreferences();
    if (manager==null)
      manager = new rdManager(null,null);
  }

  public String getName() {
    return name;
  }
  public void setModel(rdModel aModel)
  {
    model = aModel;
    manager.setModel(aModel);
    if (manager.getControlSet()==null){
      controlSet = null;
    }
    animationCallback = new rdSimtkAnimationCallback(aModel);
 }


  public rdModel getModel()
  {
    return model;
  }

   public rdManager getSimulationManager()
  {
     return manager;
  }

  /**
   * createSimulationManager is invoked after a model is set to create the integrator and rdManager
   */
  public void createSimulationManager() {
    if (model==null)
      return;
    controlSet = null;
    manager = new rdManager(model,controlSet);
  }

  public String toString()
  {
    return name;
  }

  /**
   * getIntegrator
   *
   * @return Object
   */
  public rdIntegRKF getIntegrator() {
    return manager.getIntegrator();
  }

  /**
   * getControlSet
   *
   * @return Object
   */
  public rdControlSet getControlSet() {
    return manager.getControlSet();
  }

  public void setControlSet(rdControlSet aControlSet) {
    manager.setControlSet(aControlSet);
  }

  public void setSimulationThread(SwingWorker thread)
  {
    simulationThread = thread;
  }
  public SwingWorker getSimulationThread()
  {
    return simulationThread;
  }

  public rdSimtkAnimationCallback getAnimationCallback()
  {
    return animationCallback;
  }
  /**
   * setStatus sets the status of the simulation environment for the purposes of
   * context sensitive menus enablement
   *
   * @param status boolean
   */
  public void setStatus(int status)
  {
    boolean changed = false;
    SimtkSimEnvStateChangeEvent evnt = new SimtkSimEnvStateChangeEvent(this);

    synchronized (this) {
      if (this.status!=status){
        changed = true;
        evnt.setOldState(this.status);
        evnt.setNewState(status);
        this.status=status;
      }
    }
    if (changed)
      update(evnt);

  }

  /**
   * getStatus recovers the status of the simulation environment
   *
   * @return int
   */
   synchronized public int getStatus()
  {
    if (status != STARTED){ // recompute status on the fly based on availability of model, controls, ..
      if (getControlSet()==null || getModel()==null)
        status = NOT_READY;
      else
        status = READY;
    }
    return status;
  }

  /**
   * setAnimationThread
   *
   * @param timer Timer
   */
  public void setAnimationTimer(Timer timer) {
    this.timer = timer;
  }

  public Timer getAnimationTimer() {
    return timer;
  }

  public void setStoragePreferences(SimtkStoragePreferences storagePreferences)
  {
    storagePrefs=storagePreferences;
  }

  public SimtkStoragePreferences getStoragePreferences()
  {
    return storagePrefs;
  }

  /**
   * setContactForceSet
   *
   * @param newContactSet rdContactForceSet
   */
  public void setContactForceSet(rdContactForceSet newContactSet) {
    contactForceSet=newContactSet;
  }

  public void setActuatorSet(rdActuatorSet actuatorSet) {
    this.actuatorSet= actuatorSet;
  }

  /**
   * getStatusString returns the status of the simulation environment in terms of the ability to run
   * simulation
   *
   * @return String
   */
  public String getStatusString() {
    int safeStatus;
    synchronized(this) { safeStatus = status; };
    switch(safeStatus){
      case 1:
       return "NOT_READY";
      case 2:
       return "LOADING ...";
      case 3:
        return "READY";
      case 4:
        return "STARTED";
      case 5:
        return "PLAYBACK";
    }
    return "undefined!";
  }

  /**
   * getInfoString
   *
   * @return String
   */
  public String getInfoString() {
    int safeStatus;
    synchronized(this) { safeStatus = status; };
    if (safeStatus==STARTED){
      currentTime = animationCallback.getCurrentTime();
      _infoStatus= "t="+String.valueOf(currentTime);
    }
    else if (safeStatus==PLAYBACK){
      _infoStatus= "t="+String.valueOf(animationCallback.getCurrentTime());
    }
    return _infoStatus;
  }

  public synchronized double getCurrentTime()
  {
    return currentTime;
  }
  /**
   * update is the function used to tell observers (specifically the frame
   * containing the visuals for the model associated with the environment) about
   * environment changes
   */
  public void update(SimtkSimulationEvent evnt) {
    setChanged();
    notifyObservers(evnt);
  }

  /**
   * setInfoString is the method used to set the text in the status line of the
   * frame associated with the environmnet. Once called, it internally triggers
   * the update mechanism that displays the message
   *
   * @param newMessage String
   */
  public void setInfoString(String newMessage) {
    synchronized(this) {
      _infoStatus = newMessage;
    }
    update(null);
  }

  /**
   * setProgressRange
   *
   * @param startTime double
   * @param endTime double
   */
  public void setProgressRange(double startTime, double endTime) {
    _deterministicProgress = true;
    _rangeStart = startTime;
    _rangeEnd = endTime;
  }

  /**
   * getCommandPercentage
   *
   * @return int
   */
  public int getProgressPercentage() {
    if (_rangeEnd==_rangeStart)
      return 0;
    return (int) ((currentTime - _rangeStart)/(_rangeEnd - _rangeStart)*100.0);
  }

  public void setDeterministicProgress(boolean aCanMeasureProgress)
  {
    _deterministicProgress = aCanMeasureProgress;
  }

  public boolean getDeterministicProgress()
  {
    return _deterministicProgress;
  }
  /**
   * getAssociatedFrame: is a method for the simulation environment to get the
   * handle of the internal frame associated with it.
   *
   * @return SimtkMdlInternalFrame
   * @todo Investigate if a JComponent would do rather than the concrete class
   *   SimtkMdlInternalFrame in order not to expose the hierarchy, what we lose is the
   * access to actors, and vtkObjects that users potentially need.
   * @todo look into the case of having multiple windows
   *   assocated with the environment
   */
  public SimtkMdlInternalFrame getAssociatedFrame() {
    return SimtkViewDB.getFrameForModel(model);
  }

  /**
   * setPreferredDirectory: Keeps track of user's preferred folder for data files
   *
   * @param aFolder File
   */
  public void setPreferredDirectory(File aFolder)
  {
    if (aFolder.isDirectory()){
      _preferredDirectory=aFolder;
    }
  }

  public File getPreferredDirectory()
  {
    return _preferredDirectory;
  }

  /**
   * addModelObject
   *
   * @param string object name
   * @param Object object reference
   */
  public void addModelObject(String aName, rdObject modelObject) {
    _modelObjects.put(aName, modelObject);
  }

  public rdObject getModelObject(String aName) {
      return (rdObject) _modelObjects.get(aName);
  }
  public void removeModelObject(String aName) {
    _modelObjects.remove(aName);
  }
  public Enumeration getModelObjectNames(){
    return _modelObjects.keys();
  }
  public Enumeration getModelObjects(){
    return _modelObjects.elements();
  }

  /**
   * getAvailableQuantities. Called from the plotting facility to find out what quantities are available
   * for plotting.
   *
   * @param plotQuantitiesModel DefaultListModel
   */
  public void getAvailableQuantities(Vector plotQuantitiesModel) {
    if (manager == null || manager.getIntegrator()==null)
      return;
    rdStorage kinematicsStorage = manager.getIntegrator().getStateStorage();
    if (kinematicsStorage == null)
      return;
    rdArrayStr columnLabels = kinematicsStorage.getColumnLabelsArray();
    for (int i=0; i < columnLabels.getSize(); i++){
      String fullName = name+"."+columnLabels.getitem(i);
      if (plotQuantitiesModel.contains(fullName))
        continue;
      plotQuantitiesModel.addElement(fullName);
    }
    // Repeat for controls
    rdStorage controlStorage = manager.getIntegrator().getControlStorage();
    if (controlStorage == null)
      return;
    columnLabels = controlStorage.getColumnLabelsArray();
    for (int i=0; i < columnLabels.getSize(); i++){
      String fullName = name+"."+columnLabels.getitem(i);
      if (plotQuantitiesModel.contains(fullName))
        continue;
      plotQuantitiesModel.addElement(fullName);
    }
  }

  /**
   * getDataValues with no initial time
   *
   * @param xName String
   * @param yName String
   * @param xValues Vector
   * @param yValues Vector
   * @return boolean
   */
  public boolean getDataValues(String xName, String yName, Vector xValues,
                               Vector yValues) {
    return getDataValues(xName, yName, xValues, yValues, 0.0);
  }
  /**
   * getDataValues starting from a specific time
   *
   * @param xName String
   * @param yName String
   * @param xValues Vector
   * @param yValues Vector
   * @return boolean
   */
  public boolean getDataValues(String xName, String yName, Vector xValues,
                               Vector yValues, double startTime) {
    // Search available rdStorage(s) for one containing both labels and whn found collect data
    if (manager == null || manager.getIntegrator()==null)
      return false;
    rdStorage useStorage;
    for (int storageIndex=0; storageIndex < 2; storageIndex++){
      if (storageIndex==0)
        useStorage = manager.getIntegrator().getStateStorage();
      else if (storageIndex ==1){
        useStorage = manager.getIntegrator().getControlStorage();
      }
      else
        return false;
      if (useStorage == null)
        return false;
      int rowIndex = useStorage.findIndex(0, startTime);
      SimtkApp.displayDebugMessage("Found index = "+rowIndex+" time="+startTime+"\n");
      if (rowIndex==-1)
        return false;
      int xIndex = useStorage.getColumnIndex(xName);
      int yIndex = useStorage.getColumnIndex(yName);
      if ( (xIndex != -1 || xName.equals("time")) && yIndex != -1) {
        for (int i = rowIndex; i < useStorage.getSize(); i++) {
          if (xIndex != -1)
            xValues.add(
                        new Double(useStorage.getStateVector(i).getData().
                                   getitem(xIndex)));
          else
            xValues.add(
                        new Double(useStorage.getStateVector(i).getTime()));
          yValues.add(
                      new Double(useStorage.getStateVector(i).getData().
                                 getitem(yIndex)));
        }
        return true;
      }
    }
    return false;
  }
}
