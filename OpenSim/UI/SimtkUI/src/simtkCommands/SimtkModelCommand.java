package simtkCommands;

import simtkCore.SimtkDB;
import opensimModel.Model;

abstract public class SimtkModelCommand extends SimtkEnvCommand implements SimtkModelCommandIF{
  public SimtkModelCommand() {
  }

  /**
   * getModel
   *
   * @return Model
   */
  public Model getModel() {
    // Make sure there's a model
    String mdlName = (String) _cmdParams.get("ModelName");
    if (mdlName==null)
      return null;
    Model mdl = SimtkDB.getInstance().getModelByName(mdlName);
    return mdl;
  }

  /**
   * setModel
   *
   * @param model Model
   */
  public void setModel(Model model) {
    if (getEnv() != null)
      addCommandParam("ModelName", model.getName());
  }
}
