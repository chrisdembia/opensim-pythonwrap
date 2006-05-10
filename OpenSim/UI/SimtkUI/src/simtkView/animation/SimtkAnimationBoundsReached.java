package simtkView.animation;

import simtkuiEvents.SimtkSimulationEvent;

public class SimtkAnimationBoundsReached extends SimtkSimulationEvent{
  boolean startOrEnd;

  public SimtkAnimationBoundsReached(Object animationObject, boolean startOrEnd) {
    super(animationObject);
    this.startOrEnd = startOrEnd;
  }
  boolean isStart()
  {
    return startOrEnd;
  }
}
