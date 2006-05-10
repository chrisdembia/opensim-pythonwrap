package simtkView.animation;

import simtkuiEvents.SimtkSimulationEvent;

public class SimtkAnimationAvailableEvent extends SimtkSimulationEvent{
  boolean available;
  public SimtkAnimationAvailableEvent(Object source, boolean available) {
    super(source);
    this.available = available;
  }
  public boolean getStatus()
  {
    return available;
  }
}
