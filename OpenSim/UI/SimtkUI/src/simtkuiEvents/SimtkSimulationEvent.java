package simtkuiEvents;

import java.util.EventObject;

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
 * Base class for all events to be exchanged between Model, View and UI.
 * Typically this class is subclassed for specific events so that changes can be
 * grouped (e.g. All geometry changes will extend SimtkGeometryChangeEvent so
 * that observers of the model update view to make it up-to-date when the event
 * is received).
 */
public class SimtkSimulationEvent extends EventObject {
  public SimtkSimulationEvent(Object source) {
    super(source);
  }
}
