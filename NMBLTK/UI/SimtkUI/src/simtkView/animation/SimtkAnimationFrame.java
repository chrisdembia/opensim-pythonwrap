package simtkView.animation;

import java.util.Hashtable;

import simtkui.SimtkApp;
import vtk.*;

/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: </p>
 * @author Ayman Habib
 * @version 1.0
 * Class that abstracts all the channels maintainted by an animation frame
 */
public class SimtkAnimationFrame {
  protected actorMap map;
  protected cameraPos pos;
  protected double simulationTime;
  //protected vtkActorCollection actorCollection;
  /**
   * SimtkAnimationFrame constructor
   *
   * @param camera vtkCamera
   * @param renderer vtkRenderer
   *
   * @todo Check if there's a need for the two parameters rather than one (renderer) and
   * then query the renderer for the Camera
   */
  public SimtkAnimationFrame(vtkCamera camera, vtkRenderer renderer, double simulationTime)
  {
    setCamera(camera);
    map = new actorMap();
    //actorCollection = new vtkActorCollection();
    this.simulationTime = simulationTime;
    synchronized(renderer){
      vtkActorCollection actors = renderer.GetActors();
      actors.InitTraversal();
      for (int i = 0; i < actors.GetNumberOfItems(); i++) {
        vtkActor anActor = actors.GetNextActor();
        //actorCollection.AddItem(anActor);
        double[] actorRotations = anActor.GetOrientation();
        double[] actorPosition = anActor.GetPosition();
        map.addActorXform(anActor, actorPosition, actorRotations);
      }
    }
  }
  public SimtkAnimationFrame(double simulationTime)
  {
    this.simulationTime = simulationTime;
  }

  public void setCamera(vtkCamera avtkCamera)
  {
     double[] currentPos = avtkCamera.GetPosition();
     double[] fp = avtkCamera.GetFocalPoint();
     double distance = avtkCamera.GetDistance();
     double[] cr = avtkCamera.GetClippingRange();
     pos = new cameraPos(currentPos, fp, cr, distance);
  }
/*
  public vtkActorCollection getActorCollection()
  {
    return actorCollection;
  }
 */
  /**
   * setOn positions the camera and all the actors to the positions stored in
   * the current SimtkAnimationFrame
   *
   * @param renderer vtkRenderer
   */
  public void setOn(vtkRenderer renderer, boolean useSavedCamera)
  {
    if (useSavedCamera){
      renderer.GetActiveCamera().SetPosition(pos.pos);
      renderer.GetActiveCamera().SetFocalPoint(pos.foc);
      renderer.GetActiveCamera().SetClippingRange(pos.cr[0], pos.cr[1]);
      renderer.GetActiveCamera().SetDistance(pos.distance);
    }
    actorMap aMap = map;
    vtkActorCollection actors = renderer.GetActors();
    actors.InitTraversal();
    for (int i = 0; i < actors.GetNumberOfItems(); i++){
      vtkActor anActor = actors.GetNextActor();

      double[] savedActorTranslations = (double[])aMap.getTranslations4Actor(anActor);
      double[] savedActorRotations = (double[])aMap.getRotations4Actor(anActor);
      if (savedActorRotations != null)
        anActor.SetOrientation(savedActorRotations);
      if (savedActorRotations != null)
        anActor.SetPosition(savedActorTranslations);

    }

  }

  /**
   * getChannelValue
   *
   * @param string specificChannelName
   * @return Object
   * Reserved ones "Camera.Position.x", "Camera.Position.y", "Camera.Position.z",
      "Camera.Focus.x", "Camera.Focus.y", "Camera.Focus.z",
      "Camera.Distance",
      "Camera.ClippingRange.min", "Camera.ClippingRange.max"

   */
  public Object getChannelValue(String specificChannelName) {
    double value=0.0;
    if (specificChannelName.equalsIgnoreCase("Camera.Position.x")){
      value = pos.pos[0];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Position.y")){
      value = pos.pos[1];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Position.z")){
      value = pos.pos[2];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Focus.x")){
      value = pos.foc[0];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Focus.y")){
      value = pos.foc[1];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Focus.z")){
      value = pos.foc[2];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.Distance")){
      value = pos.distance;
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.ClippingRange.min")){
      value = pos.cr[0];
    }
    else if (specificChannelName.equalsIgnoreCase("Camera.ClippingRange.max")){
      value = pos.cr[1];
    }
    /*else {
      String coord = specificChannelName.substring(specificChannelName.
          lastIndexOf("."));
      String actorName = specificChannelName.substring(0,
          specificChannelName.lastIndexOf("."));
      double[] translations = map.getTranslations4Actor(actorName);
      double[] rotations = map.getRotations4Actor(actorName);
      if (coord.equals(".tx")) {
        value = translations[0];
      }
      else if (coord.equals(".ty")) {
        value = translations[1];
      }
      else if (coord.equals(".tz")) {
        value = translations[2];
      }
      else if (coord.equals(".rx")) {
        value = rotations[0];
      }
      else if (coord.equals(".ry")) {
        value = rotations[1];
      }
      else if (coord.equals(".rz")) {
        value = rotations[2];
      }
    }*/
    return new Double(value);

  }

  public void print()
  {
    simtkui.SimtkApp.displayInfoMessage("Time ="+simulationTime+"\n");
    simtkui.SimtkApp.displayInfoMessage("Position ="+pos.pos[0]+", "+pos.pos[1]+", "+pos.pos[2]+"\n");
    simtkui.SimtkApp.displayInfoMessage("FocalPoint ="+pos.foc[0]+", "+pos.foc[1]+", "+pos.foc[2]+"\n");
    simtkui.SimtkApp.displayInfoMessage("Clipping Range ="+pos.cr[0]+", "+pos.cr[1]+"\n");
    simtkui.SimtkApp.displayInfoMessage("Distance ="+pos.distance+"\n");
  }
  public vtkTransform getActorTransform(vtkActor actor)
  {
    return map.getActorTransform(actor);
  }

  /**
   * setActorTransform
   *
   * @param anActor vtkActor
   * @param obj vtkTransform
   */
  public void setActorTransform(vtkActor anActor, vtkTransform obj) {
    double[] actorRotations = obj.GetOrientation();
    double[] actorPosition = obj.GetPosition();
    if (map == null) map = new actorMap();
    map.addActorXform(anActor, actorPosition, actorRotations);
  }

  private class cameraPos
  {
    public double pos[] = new double[3];
    public double foc[] = new double[3];
    public double cr[] = new double[2];
    public double distance;

    public cameraPos(double[] currentPos, double[] currentFoc, double[] clippingRange, double distance){
      for(int i=0; i <3; i++){
        pos[i] = currentPos[i];
        foc[i] = currentFoc[i];
        if (i < 2)
          cr[i] = clippingRange[i];
      }
      this.distance = distance;
   }
  }

  /**
   * <p>Title: </p>
   *
   * <p>Description: </p>
   *
   * <p>Copyright: Copyright (c) 2005</p>
   *
   * <p>Company: </p>
   * @author Ayman Habib
   * @version 1.0
   * A Map from ctkActors to positions and rotations
   */
  private class actorMap
  {
    Hashtable mapActors2Translations = new Hashtable();
    Hashtable mapActors2Rotations = new Hashtable();
    public actorMap()
    {}
    public void addActorXform(vtkActor actor, double[] translations, double[] rotations)
    {
      double[] newTrans = new double[3];
      double[] newRotations = new double[3];
      System.arraycopy(translations, 0, newTrans, 0, 3);
      System.arraycopy(rotations, 0, newRotations, 0, 3);
      mapActors2Translations.put(actor, translations);
      mapActors2Rotations.put(actor, rotations);
    }
    public double[] getTranslations4Actor(vtkActor actor)
    {
      return (double[])mapActors2Translations.get(actor);
    }
    public double[] getRotations4Actor(vtkActor actor)
    {
      return (double[])mapActors2Rotations.get(actor);
    }
    public vtkTransform getActorTransform(vtkActor actor)
    {
      vtkTransform actorTransform = new vtkTransform();
       double[] translations = getTranslations4Actor(actor);
       actorTransform.Translate(translations);
       double[] rotations = getRotations4Actor(actor);
       actorTransform.RotateX(rotations[0]);
       actorTransform.RotateY(rotations[1]);
       actorTransform.RotateZ(rotations[2]);
      return actorTransform;

    }
  }
}
