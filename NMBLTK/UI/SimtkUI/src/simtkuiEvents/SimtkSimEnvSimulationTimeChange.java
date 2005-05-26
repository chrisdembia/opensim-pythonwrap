package simtkuiEvents;

public class SimtkSimEnvSimulationTimeChange  extends SimtkSimulationEvent{
  double simulationTime;
  public SimtkSimEnvSimulationTimeChange(Object source) {
    super(source);
  }
  public SimtkSimEnvSimulationTimeChange(Object source, double newTime) {
    super(source);
    simulationTime = newTime;
  }
  public double getTime()
  {
    return simulationTime;
  }
}
