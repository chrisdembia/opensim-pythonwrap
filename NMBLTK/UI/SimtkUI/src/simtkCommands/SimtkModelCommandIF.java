package simtkCommands;
import simtkModel.rdModel;

public interface SimtkModelCommandIF extends SimtkEnvCommandIF{
  // Interface to be implemented by all commands that operate on a model
  public void setModel(rdModel model);

  public rdModel getModel();

}
