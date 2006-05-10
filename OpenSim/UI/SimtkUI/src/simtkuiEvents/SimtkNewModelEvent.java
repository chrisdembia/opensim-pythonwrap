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
 * An Event to be triggered when a new model is added to the Simtk environment
 */
public class SimtkNewModelEvent extends SimtkSimulationEvent{
  public SimtkNewModelEvent(Object source) {
    super(source);
  }
}
