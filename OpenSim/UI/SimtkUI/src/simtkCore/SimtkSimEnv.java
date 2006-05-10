package simtkCore;

import java.io.*;
import java.util.*;

import javax.swing.Timer;

import simtkModel.*;
import simtkUtils.*;
import simtkView.*;
import simtkui.*;
import simtkuiEvents.*;

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
  rdModelIntegrand integrand = null;

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
  private Hashtable _availableData = new Hashtable(4);
  private Hashtable _timeVaryingData = new Hashtable(4);

  /** The follwoing enums describe the status of the simulation environment with regard to ability to start simulation */
  public static final int NOT_READY = 1;
  public static final int LOADING = 2;
  public static final int READY = 3;
  public static final int RUNNING = 4;
  public static final int READY_HAS_RESULTS = 5;
  public static final int PLAYBACK = 6;


  public SimtkSimEnv(String name) {
    status=NOT_READY;
    this.name = name;
    storagePrefs = new SimtkStoragePreferences();
  }

  public String getName() {
    return name;
  }
  public void setModel(rdModel aModel)
  {
    model = aModel;

    integrand = new rdModelIntegrand(model);
    controlSet = integrand.getControlSet();
    manager = new rdManager(integrand);
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
    integrand = new rdModelIntegrand(model);
    controlSet = integrand.getControlSet();
    manager = new rdManager(integrand);
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
    return manager.getIntegrand().getControlSet();
  }

  public void setControlSet(rdControlSet aControlSet) {
    manager.getIntegrand().setControlSet(aControlSet);
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
    //System.out.println(getStatus());
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
/*    if (status != STARTED){ // recompute status on the fly based on availability of model, controls, ..
      if (getControlSet()==null || getModel()==null)
        setStatus(NOT_READY);
      else
        setStatus(READY);
    }*/
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
      case NOT_READY:
       return "Not Ready";
      case LOADING:
       return "Loading ...";
      case READY:
        return "Ready";
      case RUNNING:
        return "Running ...";
      case READY_HAS_RESULTS:
        return "Ready, Results Available";
      case PLAYBACK:
        return "Play back";
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
    if (safeStatus==RUNNING){
      _infoStatus= "t="+String.valueOf(currentTime);
    }
    else if (safeStatus==PLAYBACK){
      _infoStatus= "t="+String.valueOf(currentTime);
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
    int progress = (int) ((currentTime - _rangeStart)/(_rangeEnd - _rangeStart)*100.0);
    //System.out.println("Progress="+progress);
    return progress;
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
/*    if (manager == null || manager.getIntegrator()==null)
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
    }*/
    rdArrayStr columnLabels;
    Enumeration allStorages = _availableData.elements();
    if (allStorages != null){
     int idx = 0;
     while (allStorages.hasMoreElements()) {
       rdStorage nextStorage = (rdStorage) allStorages.nextElement();
       columnLabels = nextStorage.getColumnLabelsArray();
       for (int i=0; i < columnLabels.getSize(); i++){
         String fullName = name+":"+nextStorage.getName()+":"+columnLabels.getitem(i);
         if (plotQuantitiesModel.contains(fullName))
           continue;
         plotQuantitiesModel.addElement(fullName);
       }
     }
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
    // Assume storage comes from xName
    String storageName = xName.substring(0, xName.lastIndexOf(":"));
    rdStorage useStorage = (rdStorage) _availableData.get(storageName);
    if (useStorage!=null){
      String bareXName = xName.substring(xName.lastIndexOf(":") + 1);
      String bareYName = yName.substring(yName.lastIndexOf(":") + 1);
      int startRowIndex = useStorage.findIndex(0, startTime);
      int xIndex = useStorage.getColumnIndex(bareXName);
      int yIndex = useStorage.getColumnIndex(bareYName);
      double  xVal, yVal;
      int numRows = useStorage.getSize();
      for (int i = startRowIndex; i < numRows; i++) {
        // Assumption if name is not found then it's time. This assumption is valid only
        // because user selects from a provided list of quantitiies
        if (xIndex == -1)
          xVal = useStorage.getStateVector(i).getTime();
        else
          xVal = useStorage.getStateVector(i).getData().getitem(xIndex);

        yVal = useStorage.getStateVector(i).getData().getitem(yIndex);

        xValues.add( new Double(xVal));
        yValues.add( new Double(yVal));
      }
//      simtkui.SimtkApp.displayInfoMessage("Adding rows from "+startRowIndex+" to "+numRows+"\n");
      return true;
    }
    return false;
  }

  public boolean addStorage(rdStorage newStorage, boolean timeVarying) {
    if (_timeVaryingData.get(newStorage.getName())== null){
      _timeVaryingData.put(newStorage.getName(), new Boolean(timeVarying));
      return addStorage(newStorage);
    }
    else
      return false;
  }
  /**
   * addStorage
   *
   * @param newStorage rdStorage
   * @return boolean true if success else false
   */
  private boolean addStorage(rdStorage newStorage) {
    _availableData.put(newStorage.getName(), newStorage);
    return true;
  }

  /**
   * addStorage
   *
   * @param newStorage rdStorage
   * @return boolean true if success else false
   */
  public void removeStorage(rdStorage toRemoveStorage) {
    _availableData.remove(toRemoveStorage.getName());
    _timeVaryingData.remove(toRemoveStorage.getName());
    return;
  }
  public Enumeration getAvailableStorages()
  {
    return _availableData.elements();
  }

  /**
   * isTimeDependent
   *
   * @param xName String
   * @return boolean true if xName corresponds to atime varying quantity
   */
  public boolean isTimeDependent(String xName) {
    String storageName = xName.substring(0, xName.lastIndexOf(":"));
    return ((Boolean)_timeVaryingData.get(storageName)).booleanValue();
  }

  /**
   * removeStorageDynamicStorages
   */
  public void removeDynamicStorages() {
    int nAnalyses = getModel().getNumAnalyses();
    for (int i=0; i < nAnalyses; i++){
      rdAnalysis nextAnalysis = getModel().getAnalysis(i);
      String analysisName = nextAnalysis.getName();
      String analysisType = nextAnalysis.getType();
      rdArrayStorage storages = nextAnalysis.getStorageList();
      for (int j=0; j < storages.getSize(); j++){
        removeStorage(storages.get(j));
      }
    }
  }

  /**
   * addStorageDynamicStorages
   */
  public void addDynamicStorages() {
    int nAnalyses = getModel().getNumAnalyses();
    for (int i=0; i < nAnalyses; i++){
      rdAnalysis nextAnalysis = getModel().getAnalysis(i);
      String analysisName = nextAnalysis.getName();
      String analysisType = nextAnalysis.getType();
      rdArrayStorage storages = nextAnalysis.getStorageList();
      for (int j=0; j < storages.getSize(); j++){
        addStorage(storages.get(j), true);
      }
    }
 }

  /**
   * setSimulationTime
   *
   * @param d double is the cached value of simulation time thru the animation callback
   */
  public void setSimulationTime(double d) {
    currentTime = d;
  }

  public double getSimulationTime() {
    return currentTime;
  }
}
