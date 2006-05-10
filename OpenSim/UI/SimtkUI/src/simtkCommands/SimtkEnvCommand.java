package simtkCommands;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;

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
 * Base class for commands that operate on a SimtkSimEnv. Provides default
 * implementation to set/get environment. Operates on the _cmdParameters array
 */
abstract public class SimtkEnvCommand extends SimtkCommand implements SimtkEnvCommandIF {
  public SimtkEnvCommand() {
  }

  /**
   * getEnv
   *
   * @return SimtkSimEnv
   */
  public SimtkSimEnv getEnv() {
    // Make sure there's an env
    String simenvName = (String) _cmdParams.get("EnvName");
    if (simenvName==null)
      return null;

    return SimtkDB.getInstance().getSimtkSimEnv(simenvName);

  }

  /**
   * setEnv
   *
   * @param env SimtkSimEnv
   */
  public void setEnv(SimtkSimEnv env) {
    if (getEnv()==null)
      addCommandParam("EnvName", env.getName());
  }
}
