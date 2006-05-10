package simtkuiEvents;

public class SimtkSimEnvStateChangeEvent extends SimtkSimulationEvent{
  private int oldState;
  private int newState;

  public SimtkSimEnvStateChangeEvent(Object source) {
    super(source);
  }


  public SimtkSimEnvStateChangeEvent(Object source, int oldState, int newState) {
    this(source);
    this.oldState = oldState;
    this.newState = newState;
  }

  /**
   * setOldState
   *
   * @param i int
   */
  public void setOldState(int i) {
    oldState = i;
  }
  public int getOldState() {
    return oldState;
  }

  /**
   * setNewState
   *
   * @param status int
   */
  public void setNewState(int status) {
    newState = status;
  }
  public int getNewState() {
    return newState;
  }
}
