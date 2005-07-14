package simtkView.animation;

import simtkuiEvents.SimtkSimulationEvent;

public class SimtkAnimationTimeChangeEvent
    extends SimtkSimulationEvent{
  double simulationTime;
  public SimtkAnimationTimeChangeEvent(Object source, double newTime) {
    super(source);
    this.simulationTime = newTime;
  }
  public double getTime()
  {
    return simulationTime;
  }
}
