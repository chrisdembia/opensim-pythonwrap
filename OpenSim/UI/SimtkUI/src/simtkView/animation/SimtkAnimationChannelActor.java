package simtkView.animation;

import java.util.ArrayList;
import java.util.ListIterator;

import vtk.vtkActor;
import vtk.vtkKochanekSpline;
import vtk.vtkTransform;

public class SimtkAnimationChannelActor  extends SimtkAnimationChannel {
  ArrayList  keyFrameTransforms;
  ArrayList  keyFrameTimes;
  boolean     computed;
  vtkActor    actor;
  /**
   * For now we'll use splines to interpolate everything, eventually we'll use Quaternions and SLRP
   */
  vtkKochanekSpline[] interpolatingSplines = new vtkKochanekSpline[6];

  public SimtkAnimationChannelActor(String name, vtkActor actor) {
    super(name);
    this.actor = actor;
    keyFrameTransforms = new ArrayList();
    keyFrameTimes = new ArrayList();
    computed = false;
    for(int i=0; i < 6; i++)
      interpolatingSplines[i] = new vtkKochanekSpline();
  }

  /**
   * addFrame
   *
   * @param animationTime double
   * @param channelValue Object
   */
  public void addFrame(double animationTime, Object channelValue) {
    if (channelValue instanceof vtkTransform){
      vtkTransform xform = (vtkTransform) channelValue;
      if (keyFrameTimes.size()==0){
        keyFrameTimes.add(0, new Double(animationTime));
        keyFrameTransforms.add(0, channelValue);
        return;
      }
      /** @todo try to search from end going backward as it's more common scenario */
      /** @todo Use more efficient datastructure since this's quadratic in number of frames */
      boolean inserted = false;
      ListIterator listIterator = keyFrameTimes.listIterator(0);
      while(listIterator.hasNext()){
        Object nextTimeObject = listIterator.next();
        if (nextTimeObject instanceof Double){
          double t = ((Double) nextTimeObject).doubleValue();
          if (t > animationTime){
            int index = listIterator.nextIndex();
            listIterator.add(new Double(animationTime));
            keyFrameTransforms.add(index, channelValue);
            inserted = true;
            break;
          }
        }
      }
      // If not inserted so far, append it to the end of the list
      if (!inserted){
        keyFrameTimes.add(new Double(animationTime));
        keyFrameTransforms.add(channelValue);
      }
    }
  }

  /**
   * evaluate
   *
   * @param animationTime double
   * @return Object
   */
  public Object evaluate(double animationTime) {
    vtkTransform xform=null;
   /* = new vtkTransform();
    if (computed){
      double pos[] = new double[3];
      double rot[] = new double[3];
      for(int i=0; i <3; i++){
        pos[i] = interpolatingSplines[i].Evaluate(animationTime);
        rot[i+3] = interpolatingSplines[i+3].Evaluate(animationTime);
      }
       xform.Translate(pos);
       xform.RotateX(rot[0]);
       xform.RotateY(rot[1]);
       xform.RotateZ(rot[2]);
    }*/
  boolean found = false;
    for (int i = 0; i < keyFrameTimes.size(); i++) {
      double time = ((Double)keyFrameTimes.get(i)).doubleValue();
      if (time < animationTime)
        continue;
      xform = (vtkTransform)keyFrameTransforms.get(i);
      break;
    }
    if (xform == null)
      xform = (vtkTransform)keyFrameTransforms.get(keyFrameTimes.size()-1);
    return xform;
  }

  /**
   * clear
   */
  public void clear() {
  }

  /**
   * removeFrame
   *
   * @param animationTime double
   */
  public void removeFrame(double animationTime) {
  }
}
