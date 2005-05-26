package simtkui;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Vector;

import simtkUtils.FileUtils;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Class describing one resource which is either a jar file, directory, internet
 * URL. It maintains a list of plugins living in this resource along with their
 * state(Loaded/unloaded/permanent/..)
 * Some of these attributes will not be set untill the plugin is actually loaded
 *
 * @author Ayman Habib
 * @version 1.0
 */

public class SimtkPluginResource {

  protected File dirPath=null;
  protected URL urlPath=null;
  protected int status;
  protected Vector pluginList=new Vector();

  public static final int AVAILABLE = 1;
  public static final int INACCESSIBLE = 2;

  public SimtkPluginResource(File dir) {
    // For now assume we have a directory!
    dirPath = dir;
    String[] plugins = dirPath.list();
    if (plugins == null)
      return;

    status = AVAILABLE;
    for (int i = 0; i < plugins.length; i++) {
      String plugin = plugins[i];
      if (!plugin.toLowerCase().endsWith(".jar") && !plugin.toLowerCase().endsWith(".class"))
        continue;
      // Either a single class file or a jar
      String path = FileUtils.makeFileName(dirPath.getAbsolutePath(),plugin);
      if (plugin.toLowerCase().endsWith(".jar"))
        addPluginJar(path);
      else
        addPluginClass(path);
    }
  }

  /**
   * addPluginClass adds a plugin from a class file
   * This does not load the actual class file, it just lists it in available plugins
   * (It does not look inside the file until asked to load it)
   * @param path String
   */
  private void addPluginClass(String path) {
    pluginList.add(path);
  }

  /**
   * addPluginJar adds a plugin or a set of plugins from a Jar file
   * (It does not look inside the JAR until asked to load it) because:
   * 1. May be undesired by the user
   * 2. It would be very slow
   *
   * @param path String
   */
  private void addPluginJar(String path) {

  }

  /**
   * SimtkPluginResource
   *
   * @param url URL
   */
  public SimtkPluginResource(URL url) {
    urlPath = url;
    status = AVAILABLE; // mark resource as available by default
    try {
      URLConnection resourceConnection = url.openConnection();
    }
    catch (IOException ex) {
      status = INACCESSIBLE;
    }
     return;
 }

  public String toString()
  {
    return dirPath.getAbsolutePath();
  }

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
   * A Class representing the different states of plugins along with any
   * additional info to be shown about plugins
   */
  class SimtkPluginState
  {
  }
}
