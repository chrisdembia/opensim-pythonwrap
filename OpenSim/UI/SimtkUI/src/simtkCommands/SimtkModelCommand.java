package simtkCommands;

import simtkCore.SimtkDB;
import simtkModel.rdModel;

abstract public class SimtkModelCommand extends SimtkEnvCommand implements SimtkModelCommandIF{
  public SimtkModelCommand() {
  }

  /**
   * getModel
   *
   * @return rdModel
   */
  public rdModel getModel() {
    // Make sure there's a model
    String mdlName = (String) _cmdParams.get("ModelName");
    if (mdlName==null)
      return null;
    rdModel mdl = SimtkDB.getInstance().getModelByName(mdlName);
    return mdl;
  }

  /**
   * setModel
   *
   * @param model rdModel
   */
  public void setModel(rdModel model) {
    if (getEnv() != null)
      addCommandParam("ModelName", model.getName());
  }
}
