package simtkui;

import java.io.File;
import java.net.URL;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Class describing one resource which is either a file, directory, internet
 * URL. It maintains a list of plugins living in this resource along with their
 * state(Loaded/unloaded/permanent/..)
* Some of this attributes will not be set untill the plugin is actually loaded
 *
 * @author Ayman Habib
 * @version 1.0
 */

abstract class SimtkPlugin {
  static int UNKNOWN=0;
  static int LOADED=1;
  static int UNLOADED=2;
  static int PERMANENT=3;
  static int INUSE=4;

  private int status=UNKNOWN;

  protected String name;  /** Displayed name of plugin */
  protected String version; /** Plugin version */
  protected String appVersion; /** Version of Simtk the plugin is compatible with  */
  protected String author; /** Plugin author  */
  protected String[] dependentPlugins; /** Plugins that current plugin depend on */
  protected String shortDescription; /** Short description of the functionality offered by plugin */
  protected boolean hasGuiElements=false; /** Plugin has GUI elements */
  protected boolean hasSimulationElements=false; /** Plugin has Simulation elements */
  protected URL helpUrl; /* Help for the plugin */
  protected File path;
  public SimtkPlugin(File dir) {
    // For now assume we have a directory!
    path = dir;
  }
  public String getName()
  {
    return name;
  }

  public String getVersion()
  {
    return version;
  }
  public String getAppVersion()
  {
    return appVersion;
  }
  public String getAuthor()
  {
    return author;
  }
  public String[] getDependentPlugins()
 {
   return dependentPlugins;
 }
 public int getStatus()
  {
    return status;
  }
  public void setStatus(int newStatus)
  {
    status = newStatus;
  }

  public String getShortDescription()
  {
    return shortDescription;
  }

  public URL getHelpUrl()
  {
    return helpUrl;
  }

  public String toString()
  {
    return path.getAbsolutePath();
  }
}
