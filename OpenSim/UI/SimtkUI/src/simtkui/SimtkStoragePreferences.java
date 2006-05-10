package simtkui;

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
 * This class provides the datastructure to maintain storage preferences for
 * simulation (e.g. what results to tore, at what frequency and where).
 */
public class SimtkStoragePreferences {
  String _storageDirectory=null;
  boolean _pstatesStore=false;
  boolean _statesStore=false;
  boolean _controlsStore=false;
  String _pstatesFilename, _statesFilename, _controlsFilename;

  /**
   * SimtkStoragePreferences default constructor to set file names for srorage
   * to defaults, sets period to .005, and store results in current user
   * directory. These options shouild be customizable from property files.
   */
  public SimtkStoragePreferences() {
    _storageDirectory=System.getProperty("user.dir");
    _pstatesStore=false;
    _statesStore=false;
    _controlsStore=false;
    _pstatesFilename="pseudo_states.sto";
    _statesFilename="states.sto";
    _controlsFilename="controls.sto";
  }

  /**
   * setStorageDirectory
   *
   * @param newDirectory String
   */
  public void setStorageDirectory(String newDirectory)
  {
    _storageDirectory=newDirectory;
  }

  /**
   * getStorageDirectory retrieves the storage directory name
   *
   * @return String
   */
  public String getStorageDirectory()
  {
    return _storageDirectory;
  }
  public void setPStatesStore(boolean pstatesStore)
  {
    _pstatesStore= pstatesStore;
  }
  public boolean getPStatesStore()
  {
    return _pstatesStore;
  }
  public void setStatesStore(boolean statesStore)
  {
    _statesStore= statesStore;
  }
  public boolean getStatesStore()
  {
    return _statesStore;
  }
  public void setControlsStore(boolean controlsStore)
  {
    _controlsStore= controlsStore;
  }
  public boolean getControlsStore()
  {
    return _controlsStore;
  }
  public void setPStatesStorageFile(String pstatesStorageFile)
  {
    _pstatesFilename= pstatesStorageFile;
  }
  public String getPStatesStorageFile()
  {
    return _pstatesFilename;
  }
  public void setStatesStorageFile(String statesStorageFile)
  {
    _statesFilename= statesStorageFile;
  }
  public String getStatesStorageFile()
  {
    return _statesFilename;
  }
  public void setControlsStorageFile(String controlsStorageFile)
  {
    _controlsFilename= controlsStorageFile;
  }
  public String getControlsStorageFile()
  {
    return _controlsFilename;
  }
}
