package simtkuiEvents;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * This event is used to communicate xform changes while animating a simulation
 */
public class SimtkModelRedisplayEvent
    extends SimtkSimulationEvent {
  private String _modelName;
  private boolean _reDraw;// default to false, if true display will be recreated from scratch (expensive)

  public SimtkModelRedisplayEvent(Object source) {
    super(source);
  }
  public SimtkModelRedisplayEvent(Object source, String modelName) {
    this(source, modelName, false);
   }
  public SimtkModelRedisplayEvent(Object source, String modelName, boolean reDraw) {
     super(source);
     _modelName = modelName;
     _reDraw = reDraw;
  }
  public String getModelName()
  {
    return _modelName;
  }
  public boolean reDraw()
  {
    return _reDraw;
  }
 }
