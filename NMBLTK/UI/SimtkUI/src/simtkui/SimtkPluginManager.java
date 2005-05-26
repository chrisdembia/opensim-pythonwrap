package simtkui;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;

import javax.swing.DefaultListModel;
import javax.swing.event.ListDataListener;

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
 * This class corresponds to the model of the plugin manager meaning that it
 * contains the data relevent to plugin management and bookkeeping but no user
 * interface component.
* The current plugins tab contains
* Name, version, status, resource has a button to unload
* There will be an update tab to update plugins from resources
* The available plugins tab contains
* FileName, source and an install button
*
 */
public class SimtkPluginManager extends DefaultListModel {

  static SimtkPluginManager _dInstance;
  static boolean _instanceFlag=false;
  /**
   * _pluginResources is a list of resources indicated by user or environment
   * These are local directories or repositories referred to using urls (http://)
   * Each esource maintains a list of jar files and or class files corresponding to plugins
   * The list is created on the fly
   */
  //Vector _pluginResources=new Vector();

  /**
   * SimtkPluginManager default constructor, searches directotries and jar files
   * specified by some environment variable (SIMTK_PLUGIN_PATH) for plugins.
   */
  private SimtkPluginManager() {
    String pluginPath = SimtkProperties.getInstance().getProperty("Simtk.plugin.path");
    // Separete path into semicolon separated directories/jars
    if (pluginPath==null)
      return;

    String[] directories = pluginPath.split(";");
    for(int i=0; i < directories.length; i++){
      URL url = null;
      try {
        url = new URL(directories[i]);
        //addPluginsForResource(url);
      }
      catch (MalformedURLException ex) {
        // Could be a regular directory or jar file
        File dir = null;
        dir = new File(directories[i]);
        if (dir.isDirectory())
           addPluginsForResource(dir);
       }
     }
  }

  /**
   * addPluginsForResource
   *
   * @param url URL
   */
  public void addPluginsForResource(URL url) {
    if( this.contains(url))
     return;

   this.addElement((Object)new SimtkPluginResource(url));
 }

  /**
   * addPluginsForResource
   *
   * @param string String
   */
  public void addPluginsForResource(File dir) {
   if( this.contains(dir))
     return;
   this.addElement(new SimtkPluginResource(dir));

 }

  static public SimtkPluginManager getInstance() {
    if (!_instanceFlag) {
      _instanceFlag = true;
      _dInstance = new SimtkPluginManager();
    }
    return _dInstance;
  }


  /**
   * getRowCount
   *
   * @return int
   */
  public int getRowCount() {
    return this.size();
  }

  /**
   * getValueAt
   *
   * @param rowIndex int
   * @param columnIndex int
   * @return Object
   */
  public Object getValueAt(int rowIndex, int columnIndex) {
    Object resource = this.elementAt(rowIndex);
    return this.elementAt(rowIndex);
  }

  /**
   * addListDataListener
   *
   * @param l ListDataListener
   */
  public void addListDataListener(ListDataListener l) {
  }

  /**
   * removeListDataListener
   *
   * @param l ListDataListener
   */
  public void removeListDataListener(ListDataListener l) {
  }

}
