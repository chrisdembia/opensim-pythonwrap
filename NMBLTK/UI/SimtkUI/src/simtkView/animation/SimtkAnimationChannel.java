package simtkView.animation;


/**
 * Scalar animation channel
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2005</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */
public abstract class SimtkAnimationChannel {
  String channelName;
  public SimtkAnimationChannel(String name)
  {
    channelName = name;
  }
  public String getName()
  {
    return channelName;
  }
  public abstract void addFrame(double animationTime, Object channelValue);
  public abstract Object evaluate(double animationTime);
  public abstract void clear();
  public abstract void removeFrame(double animationTime);

}
