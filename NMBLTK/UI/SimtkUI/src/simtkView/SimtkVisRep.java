package simtkView;

import java.util.Vector;

import simtkModel.Model;
import simtkModel.SWIGTYPE_p_double;
import simtkModel.rdTransform;
import simtkModel.rdVisibleProperties;
import vtk.vtkActor;
import vtk.vtkAssembly;
/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author not attributable
 * @version 1.0
 * Container for vtk specific representations/actors and current display state
 * of an object
 */
public class SimtkVisRep {
  private vtkActor _geomActor;
  private vtkActor _bboxActor;
  private vtkActor _normalsActor;
  private vtkAssembly _axesActor;
  private Vector _attachedActors;
  SWIGTYPE_p_double pos = Model.new_doubleArray(3);
  SWIGTYPE_p_double orient =  Model.new_doubleArray(3);
  double[] jPos = new double[3];
  double[] jOrient = new double[3];

  public SimtkVisRep() {
    _geomActor = null;
    _bboxActor = null;
    _normalsActor = null;
    _axesActor = null;
    _attachedActors = new Vector();
  }

  /**
   * setGeomActor: Sets actor reference for the actor representing geometry
   *
   * @param geomActor vtkActor
   */
  public void setGeomActor(vtkActor geomActor) {
    _geomActor = geomActor;
  }
  public vtkActor getGeomActor() {
    return _geomActor;
  }

  /**
   * setBboxActor: Sets actor reference for the actor representing bounding box
   *
   * @param bboxActor vtkActor
   */
  public void setBboxActor(vtkActor bboxActor) {
    _bboxActor = bboxActor;
  }
  public vtkActor getBboxActor() {
    return _bboxActor;
  }


  /**
   * setNormalsActor: Sets actor reference for the actor representing normals
   *
   * @param bboxActor vtkActor
   */
  public void setNormalsActor(vtkActor normalsActor) {
    _normalsActor = normalsActor;
  }
  public vtkActor getNormalsActor() {
    return _normalsActor;
  }
  /**
   * setAxesActor: Sets actor reference for the actor representing cs at origin
   *
   * @param bboxActor vtkActor
   */
  public void setAxesActor(vtkAssembly axesActor) {
    _axesActor = axesActor;
  }
  public vtkAssembly getAxesActor() {
    return _axesActor;
  }

  public void attachActor(vtkActor anActor) {
    _attachedActors.add(anActor);
  }
  public void detachActor(vtkActor anActor) {
    _attachedActors.remove(anActor);
  }
  /**
   * updateDisplay: set the visibility of the vtkActors according to passed in
   * user preference
   *
   * @param displayPref int
   */
  public void updateDisplay(int displayPref, boolean showNormals, boolean showAxes) {
    vtkActor gActor = getGeomActor();
    vtkActor bActor = getBboxActor();
// Somehow java doesn't think rdVisibleProperties.WireFrame is constant
// so I can't use a switch statement here!!
    if (displayPref == rdVisibleProperties.WireFrame) {
      gActor.VisibilityOn();
      gActor.GetProperty().SetRepresentationToWireframe();
      bActor.VisibilityOff();
    }
    else if (displayPref == rdVisibleProperties.FlatShaded) {
      gActor.VisibilityOn();
      gActor.GetProperty().SetRepresentationToSurface();
      gActor.GetProperty().SetInterpolationToFlat();
      bActor.VisibilityOff();
    }
    else if (displayPref == rdVisibleProperties.None) {
      gActor.VisibilityOff();
      bActor.VisibilityOff();
    }
    else if (displayPref == rdVisibleProperties.BoundingBox) {
      gActor.VisibilityOff();
      bActor.VisibilityOn();
    }
    else { //displayPref==rdVisibleProperties.GouraudShaded
      gActor.VisibilityOn();
      bActor.VisibilityOff();
      gActor.GetProperty().SetRepresentationToSurface();
      gActor.GetProperty().SetInterpolationToGouraud();
    }
    // Handle normals separately
    _normalsActor.SetVisibility(showNormals?1:0);
    _axesActor.SetVisibility(showAxes?1:0);
  }

  /**
   * setTransform sets the xform for all the actors representing a visible
   * object based on its model xform
   * @param xform rdTransform
   */
  public void setTransform(rdTransform xform) {
    xform.getPosition(pos);
    xform.getOrientation(orient);
    for (int i=0; i < 3; i++){
      jPos[i] = Model.doubleArray_get(pos, i);
      jOrient[i] = Model.doubleArray_get(orient, i);
    }

    getGeomActor().SetPosition(jPos);
    getGeomActor().SetOrientation(0., 0., 0.);
    getGeomActor().RotateX(jOrient[0]);
    getGeomActor().RotateY(jOrient[1]);
    getGeomActor().RotateZ(jOrient[2]);

    getBboxActor().SetPosition(jPos);
    getBboxActor().SetOrientation(0., 0., 0.);
   getBboxActor().RotateX(jOrient[0]);
   getBboxActor().RotateY(jOrient[1]);
   getBboxActor().RotateZ(jOrient[2]);

    getNormalsActor().SetPosition(jPos);
    getNormalsActor().SetOrientation(0., 0., 0.);
   getNormalsActor().RotateX(jOrient[0]);
   getNormalsActor().RotateY(jOrient[1]);
   getNormalsActor().RotateZ(jOrient[2]);

    getAxesActor().SetPosition(jPos);
    getAxesActor().SetOrientation(0., 0., 0.);
   getAxesActor().RotateX(jOrient[0]);
   getAxesActor().RotateY(jOrient[1]);
   getAxesActor().RotateZ(jOrient[2]);
   
    for (int i=0; i <_attachedActors.size(); i++){
      ((vtkActor)(_attachedActors.get(i))).SetPosition(jPos);
      ((vtkActor)(_attachedActors.get(i))).SetOrientation(0., 0., 0.);
      ((vtkActor)(_attachedActors.get(i))).RotateX(jOrient[0]);
      ((vtkActor)(_attachedActors.get(i))).RotateY(jOrient[1]);
      ((vtkActor)(_attachedActors.get(i))).RotateZ(jOrient[2]);
    }
  }

  public void setColor(double[] newColor)
  {
    getGeomActor().GetProperty().SetColor(newColor);

    getBboxActor().GetProperty().SetColor(newColor);

    for (int i=0; i <_attachedActors.size(); i++){
      ((vtkActor)(_attachedActors.get(i))).GetProperty().SetColor(newColor);
      ((vtkActor)(_attachedActors.get(i))).GetProperty().SetColor(newColor);
    }
  }

  public void setOpacity(double newOpacity)
  {
    getGeomActor().GetProperty().SetOpacity(newOpacity);

    getBboxActor().GetProperty().SetOpacity(newOpacity);

    for (int i=0; i <_attachedActors.size(); i++){
      ((vtkActor)(_attachedActors.get(i))).GetProperty().SetOpacity(newOpacity);
      ((vtkActor)(_attachedActors.get(i))).GetProperty().SetOpacity(newOpacity);
    }
  }
}
