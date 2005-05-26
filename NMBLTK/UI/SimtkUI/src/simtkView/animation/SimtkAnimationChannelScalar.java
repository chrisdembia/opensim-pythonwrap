package simtkView.animation;

import vtk.vtkKochanekSpline;

public class SimtkAnimationChannelScalar extends SimtkAnimationChannel {
  vtkKochanekSpline   interpolant;
  public SimtkAnimationChannelScalar(String name) {
    super(name);
    interpolant = new vtkKochanekSpline();
    interpolant.RemoveAllPoints();
  }

  /**
   * addFrame
   *
   * @param animationTime dounle
   * @param channelValue Object
   *
   * @todo Throw exception if wrong type is passed in
   */
  public void addFrame(double animationTime, Object channelValue) {
    if (channelValue instanceof Double){
      double value = ((Double) channelValue).doubleValue();
      interpolant.AddPoint(animationTime, value);
    }
  }

  /**
   * evaluate
   *
   * @param animationTime double
   * @return Object
   */
  public Object evaluate(double animationTime) {
    double value = interpolant.Evaluate(animationTime);
    return (new Double(value));
  }

  /**
   * clear
   */
  public void clear() {
    interpolant.RemoveAllPoints();
  }

  /**
   * removeFrame
   *
   * @param animationTime double
   */
  public void removeFrame(double animationTime) {
    interpolant.RemovePoint(animationTime);
    interpolant.Compute();
  }
}
