package simtkCommands;
import opensimModel.Model;

public interface SimtkModelCommandIF extends SimtkEnvCommandIF{
  // Interface to be implemented by all commands that operate on a model
  public void setModel(Model model);

  public Model getModel();

}
