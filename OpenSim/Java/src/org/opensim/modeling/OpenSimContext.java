/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class OpenSimContext extends OpenSimObject {
  private long swigCPtr;

  public OpenSimContext(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.OpenSimContext_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(OpenSimContext obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_OpenSimContext(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public OpenSimContext(SWIGTYPE_p_SimTK__State s, Model model) {
    this(opensimModelJNI.new_OpenSimContext(SWIGTYPE_p_SimTK__State.getCPtr(s), Model.getCPtr(model), model), true);
  }

  public void setState(SWIGTYPE_p_SimTK__State s) {
    opensimModelJNI.OpenSimContext_setState(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public void setModel(Model m) {
    opensimModelJNI.OpenSimContext_setModel(swigCPtr, this, Model.getCPtr(m), m);
  }

  public void setStates(ArrayDouble states) {
    opensimModelJNI.OpenSimContext_setStates__SWIG_0(swigCPtr, this, ArrayDouble.getCPtr(states), states);
  }

  public void setStates(double[] statesBuffer) {
    opensimModelJNI.OpenSimContext_setStates__SWIG_1(swigCPtr, this, statesBuffer);
  }

  public void computeConstrainedCoordinates(double[] statesBuffer) {
    opensimModelJNI.OpenSimContext_computeConstrainedCoordinates(swigCPtr, this, statesBuffer);
  }

  public void getStates(double[] statesBuffer) {
    opensimModelJNI.OpenSimContext_getStates__SWIG_0(swigCPtr, this, statesBuffer);
  }

  public void getStates(ArrayDouble rStates) {
    opensimModelJNI.OpenSimContext_getStates__SWIG_1(swigCPtr, this, ArrayDouble.getCPtr(rStates), rStates);
  }

  public void recreateSystemAfterSystemExistsKeepStage() {
    opensimModelJNI.OpenSimContext_recreateSystemAfterSystemExistsKeepStage(swigCPtr, this);
  }

  public void recreateSystemAfterSystemExists() {
    opensimModelJNI.OpenSimContext_recreateSystemAfterSystemExists(swigCPtr, this);
  }

  public void transformPosition(Body body, double[] offset, double[] gOffset) {
    opensimModelJNI.OpenSimContext_transformPosition(swigCPtr, this, Body.getCPtr(body), body, offset, gOffset);
  }

  public SWIGTYPE_p_Transform getTransform(Body body) {
    return new SWIGTYPE_p_Transform(opensimModelJNI.OpenSimContext_getTransform(swigCPtr, this, Body.getCPtr(body), body), true);
  }

  public void transform(Body ground, double[] d, Body body, double[] dragVectorBody) {
    opensimModelJNI.OpenSimContext_transform(swigCPtr, this, Body.getCPtr(ground), ground, d, Body.getCPtr(body), body, dragVectorBody);
  }

  public double getValue(Coordinate coord) {
    return opensimModelJNI.OpenSimContext_getValue(swigCPtr, this, Coordinate.getCPtr(coord), coord);
  }

  public boolean getLocked(Coordinate coord) {
    return opensimModelJNI.OpenSimContext_getLocked(swigCPtr, this, Coordinate.getCPtr(coord), coord);
  }

  public void setValue(Coordinate coord, double d, boolean enforceConstraints) {
    opensimModelJNI.OpenSimContext_setValue__SWIG_0(swigCPtr, this, Coordinate.getCPtr(coord), coord, d, enforceConstraints);
  }

  public void setValue(Coordinate coord, double d) {
    opensimModelJNI.OpenSimContext_setValue__SWIG_1(swigCPtr, this, Coordinate.getCPtr(coord), coord, d);
  }

  public void setClamped(Coordinate coord, boolean newValue) {
    opensimModelJNI.OpenSimContext_setClamped(swigCPtr, this, Coordinate.getCPtr(coord), coord, newValue);
  }

  public boolean getClamped(Coordinate coord) {
    return opensimModelJNI.OpenSimContext_getClamped(swigCPtr, this, Coordinate.getCPtr(coord), coord);
  }

  public void setLocked(Coordinate coord, boolean newValue) {
    opensimModelJNI.OpenSimContext_setLocked(swigCPtr, this, Coordinate.getCPtr(coord), coord, newValue);
  }

  public boolean isConstrained(Coordinate coord) {
    return opensimModelJNI.OpenSimContext_isConstrained(swigCPtr, this, Coordinate.getCPtr(coord), coord);
  }

  public boolean isDisabled(Constraint constraint) {
    return opensimModelJNI.OpenSimContext_isDisabled__SWIG_0(swigCPtr, this, Constraint.getCPtr(constraint), constraint);
  }

  public void setDisabled(Constraint constraint, boolean disable) {
    opensimModelJNI.OpenSimContext_setDisabled__SWIG_0(swigCPtr, this, Constraint.getCPtr(constraint), constraint, disable);
  }

  public boolean isDisabled(Force force) {
    return opensimModelJNI.OpenSimContext_isDisabled__SWIG_1(swigCPtr, this, Force.getCPtr(force), force);
  }

  public void setDisabled(Force force, boolean disable) {
    opensimModelJNI.OpenSimContext_setDisabled__SWIG_1(swigCPtr, this, Force.getCPtr(force), force, disable);
  }

  public double getActivation(Muscle act) {
    return opensimModelJNI.OpenSimContext_getActivation(swigCPtr, this, Muscle.getCPtr(act), act);
  }

  public double getMuscleLength(Muscle act) {
    return opensimModelJNI.OpenSimContext_getMuscleLength(swigCPtr, this, Muscle.getCPtr(act), act);
  }

  public ArrayPathPoint getCurrentPath(Muscle act) {
    return new ArrayPathPoint(opensimModelJNI.OpenSimContext_getCurrentPath(swigCPtr, this, Muscle.getCPtr(act), act), false);
  }

  public ArrayPathPoint getCurrentDisplayPath(GeometryPath path) {
    return new ArrayPathPoint(opensimModelJNI.OpenSimContext_getCurrentDisplayPath(swigCPtr, this, GeometryPath.getCPtr(path), path), false);
  }

  public void updateDisplayer(Force f) {
    opensimModelJNI.OpenSimContext_updateDisplayer(swigCPtr, this, Force.getCPtr(f), f);
  }

  public void copyMuscle(Muscle from, Muscle to) {
    opensimModelJNI.OpenSimContext_copyMuscle(swigCPtr, this, Muscle.getCPtr(from), from, Muscle.getCPtr(to), to);
  }

  public void replacePropertyFunction(OpenSimObject obj, Function aOldFunction, Function aNewFunction) {
    opensimModelJNI.OpenSimContext_replacePropertyFunction(swigCPtr, this, OpenSimObject.getCPtr(obj), obj, Function.getCPtr(aOldFunction), aOldFunction, Function.getCPtr(aNewFunction), aNewFunction);
  }

  public void setXFunction(MovingPathPoint mmp, Function newFunction) {
    opensimModelJNI.OpenSimContext_setXFunction(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Function.getCPtr(newFunction), newFunction);
  }

  public void setYFunction(MovingPathPoint mmp, Function newFunction) {
    opensimModelJNI.OpenSimContext_setYFunction(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Function.getCPtr(newFunction), newFunction);
  }

  public void setZFunction(MovingPathPoint mmp, Function newFunction) {
    opensimModelJNI.OpenSimContext_setZFunction(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Function.getCPtr(newFunction), newFunction);
  }

  public void setXCoordinate(MovingPathPoint mmp, Coordinate newCoord) {
    opensimModelJNI.OpenSimContext_setXCoordinate(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Coordinate.getCPtr(newCoord), newCoord);
  }

  public void setYCoordinate(MovingPathPoint mmp, Coordinate newCoord) {
    opensimModelJNI.OpenSimContext_setYCoordinate(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Coordinate.getCPtr(newCoord), newCoord);
  }

  public void setZCoordinate(MovingPathPoint mmp, Coordinate newCoord) {
    opensimModelJNI.OpenSimContext_setZCoordinate(swigCPtr, this, MovingPathPoint.getCPtr(mmp), mmp, Coordinate.getCPtr(newCoord), newCoord);
  }

  public void setBody(PathPoint pathPoint, Body newBody) {
    opensimModelJNI.OpenSimContext_setBody__SWIG_0(swigCPtr, this, PathPoint.getCPtr(pathPoint), pathPoint, Body.getCPtr(newBody), newBody);
  }

  public void setCoordinate(ConditionalPathPoint via, Coordinate newCoord) {
    opensimModelJNI.OpenSimContext_setCoordinate(swigCPtr, this, ConditionalPathPoint.getCPtr(via), via, Coordinate.getCPtr(newCoord), newCoord);
  }

  public void setRangeMin(ConditionalPathPoint via, double d) {
    opensimModelJNI.OpenSimContext_setRangeMin(swigCPtr, this, ConditionalPathPoint.getCPtr(via), via, d);
  }

  public void setRangeMax(ConditionalPathPoint via, double d) {
    opensimModelJNI.OpenSimContext_setRangeMax(swigCPtr, this, ConditionalPathPoint.getCPtr(via), via, d);
  }

  public boolean replacePathPoint(GeometryPath p, PathPoint mp, PathPoint newPoint) {
    return opensimModelJNI.OpenSimContext_replacePathPoint(swigCPtr, this, GeometryPath.getCPtr(p), p, PathPoint.getCPtr(mp), mp, PathPoint.getCPtr(newPoint), newPoint);
  }

  public void setLocation(PathPoint mp, int i, double d) {
    opensimModelJNI.OpenSimContext_setLocation(swigCPtr, this, PathPoint.getCPtr(mp), mp, i, d);
  }

  public void setEndPoint(PathWrap mw, int newEndPt) {
    opensimModelJNI.OpenSimContext_setEndPoint(swigCPtr, this, PathWrap.getCPtr(mw), mw, newEndPt);
  }

  public void addPathPoint(GeometryPath p, int menuChoice, Body body) {
    opensimModelJNI.OpenSimContext_addPathPoint(swigCPtr, this, GeometryPath.getCPtr(p), p, menuChoice, Body.getCPtr(body), body);
  }

  public boolean deletePathPoint(GeometryPath p, int menuChoice) {
    return opensimModelJNI.OpenSimContext_deletePathPoint(swigCPtr, this, GeometryPath.getCPtr(p), p, menuChoice);
  }

  public boolean isActivePathPoint(PathPoint mp) {
    return opensimModelJNI.OpenSimContext_isActivePathPoint(swigCPtr, this, PathPoint.getCPtr(mp), mp);
  }

  public void setStartPoint(PathWrap mw, int newStartPt) {
    opensimModelJNI.OpenSimContext_setStartPoint(swigCPtr, this, PathWrap.getCPtr(mw), mw, newStartPt);
  }

  public void addPathWrap(GeometryPath p, WrapObject awo) {
    opensimModelJNI.OpenSimContext_addPathWrap(swigCPtr, this, GeometryPath.getCPtr(p), p, WrapObject.getCPtr(awo), awo);
  }

  public void moveUpPathWrap(GeometryPath p, int num) {
    opensimModelJNI.OpenSimContext_moveUpPathWrap(swigCPtr, this, GeometryPath.getCPtr(p), p, num);
  }

  public void moveDownPathWrap(GeometryPath p, int num) {
    opensimModelJNI.OpenSimContext_moveDownPathWrap(swigCPtr, this, GeometryPath.getCPtr(p), p, num);
  }

  public void deletePathWrap(GeometryPath p, int num) {
    opensimModelJNI.OpenSimContext_deletePathWrap(swigCPtr, this, GeometryPath.getCPtr(p), p, num);
  }

  public void setBody(Marker currentMarker, Body newBody, boolean b) {
    opensimModelJNI.OpenSimContext_setBody__SWIG_1(swigCPtr, this, Marker.getCPtr(currentMarker), currentMarker, Body.getCPtr(newBody), newBody, b);
  }

  public int replaceMarkerSet(Model model, MarkerSet aMarkerSet) {
    return opensimModelJNI.OpenSimContext_replaceMarkerSet(swigCPtr, this, Model.getCPtr(model), model, MarkerSet.getCPtr(aMarkerSet), aMarkerSet);
  }

  public void getCenterOfMassInGround(double[] com) {
    opensimModelJNI.OpenSimContext_getCenterOfMassInGround(swigCPtr, this, com);
  }

  public int step(Analysis analysis) {
    return opensimModelJNI.OpenSimContext_step(swigCPtr, this, Analysis.getCPtr(analysis), analysis);
  }

  public boolean solveInverseKinematics(InverseKinematicsTool ikTool) {
    return opensimModelJNI.OpenSimContext_solveInverseKinematics(swigCPtr, this, InverseKinematicsTool.getCPtr(ikTool), ikTool);
  }

  public void setStatesFromMotion(AnalyzeTool analyzeTool, Storage aMotion, boolean aInDegrees) {
    opensimModelJNI.OpenSimContext_setStatesFromMotion(swigCPtr, this, AnalyzeTool.getCPtr(analyzeTool), analyzeTool, Storage.getCPtr(aMotion), aMotion, aInDegrees);
  }

  public void loadStatesFromFile(AnalyzeTool analyzeTool) {
    opensimModelJNI.OpenSimContext_loadStatesFromFile(swigCPtr, this, AnalyzeTool.getCPtr(analyzeTool), analyzeTool);
  }

  public boolean processModelScale(ModelScaler modelScaler, Model aModel, String aPathToSubject, double aFinalMass) {
    return opensimModelJNI.OpenSimContext_processModelScale__SWIG_0(swigCPtr, this, ModelScaler.getCPtr(modelScaler), modelScaler, Model.getCPtr(aModel), aModel, aPathToSubject, aFinalMass);
  }

  public boolean processModelScale(ModelScaler modelScaler, Model aModel, String aPathToSubject) {
    return opensimModelJNI.OpenSimContext_processModelScale__SWIG_1(swigCPtr, this, ModelScaler.getCPtr(modelScaler), modelScaler, Model.getCPtr(aModel), aModel, aPathToSubject);
  }

  public boolean processModelScale(ModelScaler modelScaler, Model aModel) {
    return opensimModelJNI.OpenSimContext_processModelScale__SWIG_2(swigCPtr, this, ModelScaler.getCPtr(modelScaler), modelScaler, Model.getCPtr(aModel), aModel);
  }

  public boolean processModelMarkerPlacer(MarkerPlacer markerPlacer, Model aModel, String aPathToSubject) {
    return opensimModelJNI.OpenSimContext_processModelMarkerPlacer__SWIG_0(swigCPtr, this, MarkerPlacer.getCPtr(markerPlacer), markerPlacer, Model.getCPtr(aModel), aModel, aPathToSubject);
  }

  public boolean processModelMarkerPlacer(MarkerPlacer markerPlacer, Model aModel) {
    return opensimModelJNI.OpenSimContext_processModelMarkerPlacer__SWIG_1(swigCPtr, this, MarkerPlacer.getCPtr(markerPlacer), markerPlacer, Model.getCPtr(aModel), aModel);
  }

  public double computeMeasurementScaleFactor(ModelScaler modelScaler, Model aModel, MarkerData aMarkerData, Measurement aMeasurement) {
    return opensimModelJNI.OpenSimContext_computeMeasurementScaleFactor(swigCPtr, this, ModelScaler.getCPtr(modelScaler), modelScaler, Model.getCPtr(aModel), aModel, MarkerData.getCPtr(aMarkerData), aMarkerData, Measurement.getCPtr(aMeasurement), aMeasurement);
  }

  public void replaceTransformAxisFunction(TransformAxis aDof, Function aFunction) {
    opensimModelJNI.OpenSimContext_replaceTransformAxisFunction(swigCPtr, this, TransformAxis.getCPtr(aDof), aDof, Function.getCPtr(aFunction), aFunction);
  }

  public static boolean isNaN(double v) {
    return opensimModelJNI.OpenSimContext_isNaN(v);
  }

  public double getTime() {
    return opensimModelJNI.OpenSimContext_getTime(swigCPtr, this);
  }

  public static void getTransformAsDouble16(SWIGTYPE_p_Transform aTransform, double[] flattened) {
    opensimModelJNI.OpenSimContext_getTransformAsDouble16(SWIGTYPE_p_Transform.getCPtr(aTransform), flattened);
  }

  public void setDefaultsFromState() {
    opensimModelJNI.OpenSimContext_setDefaultsFromState(swigCPtr, this);
  }

  public void realizePosition() {
    opensimModelJNI.OpenSimContext_realizePosition(swigCPtr, this);
  }

  public void realizeVelocity() {
    opensimModelJNI.OpenSimContext_realizeVelocity(swigCPtr, this);
  }

}
