package simtkui;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import simtkUtils.FileUtils;

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
 * Keeper of all Properties of simtk. Initialized to System properties then
 * beefed up with more customization.
 * Implemented as a singleton.
 */
public class SimtkProperties extends Properties{

  static SimtkProperties _dInstance;
  static boolean _instanceFlag=false;

  /**
   * SimtkProperties: Constructor that puts system properties in SimtkProperties
   */
  private SimtkProperties() {
    super();
    System.getProperties().putAll(this);
    setProperty("Simtk.plugin.path",FileUtils.makeFileName(System.getProperty("user.dir"),"SimtkPlugins"));
    SimtkApp.displayDebugMessage(toString());
    FileOutputStream out = null;
    try {
      out = new FileOutputStream("appProperties");
      try {
        store(out, "---No Comment---");
        out.close();
      }
      catch (IOException ex2) {
      }
    }
    catch (FileNotFoundException ex) {
    }

  }

  static public SimtkProperties getInstance() {
    if (!_instanceFlag) {
      _instanceFlag = true;
      _dInstance = new SimtkProperties();
    }
    return _dInstance;
  }

  /**
   * loadProperties from specified file into current Properties
   *
   * @param in InputStream
   * @throws IOException
   */
  public void loadProperties(InputStream in) throws IOException {
    _dInstance.load(in);
  }

}
