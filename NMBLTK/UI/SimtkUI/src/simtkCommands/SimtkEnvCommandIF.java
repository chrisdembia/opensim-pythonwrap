package simtkCommands;

import simtkCore.SimtkSimEnv;

/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */

public interface SimtkEnvCommandIF {
  // Interface to be implemented by all commands that operate on a simulation environment
  public void setEnv(SimtkSimEnv env);

  public SimtkSimEnv getEnv();
}
