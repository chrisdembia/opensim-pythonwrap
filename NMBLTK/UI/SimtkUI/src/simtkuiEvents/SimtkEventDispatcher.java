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
 * The SimtkEventDispatcher is the mainatanier of the list of functions to be
 * called when an event is fired. The plan is to have this expandable so that
 * users can register their own events, fire them and get the system to call the
 * registered functions when the event is fired.
 * Events are by nature asynchronous so they can be fired from anywhere.
 *
 * SimtkEventDispatcher is implemented as a singleton (final) since there should be no reason to
 * to have more than one Dispatcher in the system, otherwise events may get received more than once.
 */
final public class SimtkEventDispatcher {
  public SimtkEventDispatcher() {
  }


  /**
   * handleEvent
   * @param evnt SimtkSimulationEvent
   *
   */
  public static void handleEvent(SimtkSimulationEvent evnt) {
  }
}
