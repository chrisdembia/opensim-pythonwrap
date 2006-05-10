package simtkuiEvents;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * An Event to be triggered when a model is erased from the Simtk environment
 */
public class SimtkCloseModelEvent
    extends SimtkSimulationEvent{
  public SimtkCloseModelEvent(Object source) {
    super(source);
  }

  /**
   * getModelName
   *
   * @return Object
   */
  public Object getModelName() {
    return this.getSource();
  }
}
