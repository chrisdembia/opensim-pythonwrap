/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * SingleModelVisuals.java
 *
 * Created on November 14, 2006, 5:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import org.opensim.modeling.Force;
import org.opensim.modeling.Actuator;
import org.opensim.modeling.Body;
import org.opensim.modeling.ForceSet;
import org.opensim.modeling.Marker;
import org.opensim.modeling.Muscle;
import org.opensim.modeling.Model;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.ConditionalPathPoint;
import org.opensim.modeling.DisplayGeometry.DisplayPreference;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.OpenSimContext;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.PathActuator;
import org.opensim.modeling.PathPoint;
import org.opensim.modeling.VisibleObject;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCylinderSource;
import vtk.vtkLinearTransform;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyDataAlgorithm;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkSphereSource;
import vtk.vtkStripper;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkArrowSource;
import vtk.vtkLineSource;

/**
 *
 * @author Ayman. A class representing the visuals of one model.
 * This class does not actually display the model. Instead it builds the
 * data structures (vtkAssembly) needed to display the model and also
 * maintains the maps for finding an object based on selection and vice versa.
 *
 * Sources of slow down:
 * 1. Too many assemblies (1 per muscle).
 * 2. Too many actors (markers, muscle points) these should replaced with Glyph3D or TensorGlyphs
 * 3. Selection is slow because hashing vtkProp3D apparently doesn't destribute objects evenly use 
 *       some form of Id instead (e.g. vtkId).
 */
public class SingleModelVisuals {
    
    protected vtkAssembly modelDisplayAssembly;   // assembly representing the model
    protected vtkLinearTransform modelDisplayTransform; // extra transform to shift, rotate model
    private double opacity;
    private double[] bounds = new double[6];
    private boolean visible;

    private double[] inactiveMuscleColor = new double[]{0.0, 0.0, 1.0};
    private double[] forceAlongPathColor = new double[]{0.0, 1.0, 0.0};
    private double[] defaultMuscleColor = new double[]{0.8, 0.1, 0.1};
    private double[] defaultMusclePointColor = new double[]{1.0, 0.0, 0.0};
    private double[] defaultWrapObjectColor = new double[]{0.0, 1.0, 1.0};
    private boolean useCylinderMuscles=true;

    // Maps between objects and vtkProp3D for going from Actor to Object and vice versa
    // Objects are mapped to vtkProp3D in general, but some are known to be assemblies
    // e.g. Muscles, Models
    protected Hashtable<OpenSimObject, vtkProp3D> mapObject2VtkObjects = new Hashtable<OpenSimObject, vtkProp3D>();
    protected Hashtable<vtkProp3D, OpenSimObject> mapVtkObjects2Objects = new Hashtable<vtkProp3D, OpenSimObject>(50);
   
    private Hashtable<OpenSimObject, LineSegmentMuscleDisplayer> mapActuator2Displayer = new Hashtable<OpenSimObject, LineSegmentMuscleDisplayer>();
    private Hashtable<OpenSimObject, LineSegmentForceDisplayer> mapPathForces2Displayer = new Hashtable<OpenSimObject, LineSegmentForceDisplayer>();
    private Hashtable<Force, ObjectDisplayerInterface> mapNoPathForces2Displayer = new Hashtable<Force, ObjectDisplayerInterface>();

    protected Hashtable<OpenSimObject, vtkLineSource> mapMarkers2Lines = new Hashtable<OpenSimObject, vtkLineSource>(50);
    //protected Hashtable<OpenSimObject, Boolean> markerLinesVisible = new Hashtable<OpenSimObject, Boolean>(50);
    //protected vtkActor markerLineActor = new vtkActor();
    //protected vtkAppendPolyData markerLinePolyData = new vtkAppendPolyData();
    
    // Markers and muscle points are represented as Glyphs for performance
    private MarkersDisplayer markersRep=new MarkersDisplayer();
    private OpenSimvtkGlyphCloud  musclePointsRep=new OpenSimvtkGlyphCloud(false);
    private OpenSimvtkOrientedGlyphCloud  muscleSegmentsRep = new OpenSimvtkOrientedGlyphCloud();
    private OpenSimvtkOrientedGlyphCloud  forcesRep = new OpenSimvtkOrientedGlyphCloud();
    private OpenSimvtkGlyphCloud  otherPathPointsRep=new OpenSimvtkGlyphCloud(false);
    private OpenSimvtkOrientedGlyphCloud  otherPathSegmentsRep = new OpenSimvtkOrientedGlyphCloud();

    private vtkProp3DCollection  userObjects = new vtkProp3DCollection();
    private vtkProp3DCollection  bodiesCollection = new vtkProp3DCollection();
    private ModelComDisplayer comDisplayer;
    private boolean debug=false;
    private boolean showCOM=false;
    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals(Model aModel) {
        debug = (ViewDB.getInstance().getDebugLevel() >= 1);
        initDefaultShapesAndColors();
        modelDisplayAssembly = createModelAssembly(aModel);
        setVisible(true);
    }
 
    /**
     * Find the vtkProp3D for the passed in object
     */
    public vtkProp3D getVtkRepForObject(OpenSimObject obj)
    {
        return mapObject2VtkObjects.get(obj);
    }
    /**
     * find the Object for passed in vtkProp3D
     */
    public OpenSimObject getObjectForVtkRep(vtkProp3D prop)
    {
        return mapVtkObjects2Objects.get(prop);
    }

    /**************************************************************
     * First Creation of Model Visuals
     **************************************************************/
    /**
     * Create one vtkAssembly representing the model and return it.
     */
    protected vtkAssembly createModelAssembly(Model model)
    {                
        vtkAssembly modelAssembly = new vtkAssembly();
        // Keep track of ground body to avoid recomputation
        Body gnd = model.getGroundBody();
        BodySet bodies = model.getBodySet();
 
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++)
        {
            Body body = bodies.get(bodyNum);

            // Body actor
            vtkAssembly bodyRep = new BodyDisplayer(modelAssembly, body,
                    mapObject2VtkObjects, mapVtkObjects2Objects);

            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new vtkActor is created and attached 
            // to the same xform as the owner body.
            VisibleObject bodyDisplayer = body.getDisplayer();
            for(int j=0; j < bodyDisplayer.countDependents();j++){
                VisibleObject Dependent = bodyDisplayer.getDependent(j);
                
                OpenSimObject owner = Dependent.getOwner();
                if (Marker.safeDownCast(owner)!=null){
                    
                    markersRep.addMarker(Marker.safeDownCast(owner));
                    /*vtkLineSource markerLine = new vtkLineSource();
                    mapMarkers2Lines.put(owner, markerLine);
                    markerLinesVisible.put(owner, false);
                    markerLinePolyData.AddInput(markerLine.GetOutput());*/
                    continue;
                } else if (PathPoint.safeDownCast(owner)!=null||
                           ConditionalPathPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in addGeometryForForces
                } else { // WrapObjects, and any other geometry attached to body
                   vtkActor attachmentRep = DisplayGeometryFactory.createGeometryDisplayer(Dependent, model.getFilePath());
                   if(attachmentRep!=null) {
                      mapObject2VtkObjects.put(Dependent.getOwner(), attachmentRep);
                      mapVtkObjects2Objects.put(attachmentRep, Dependent.getOwner());
                      bodyRep.AddPart(attachmentRep);

                   }
                }
            }
        } //body

        // Add markers
        modelAssembly.AddPart(getMarkersRep().getVtkActor());
        /*
        vtkPolyDataMapper markerLineMapper = new vtkPolyDataMapper();
        markerLineMapper.SetInput(markerLinePolyData.GetOutput());
        markerLineActor.SetMapper(markerLineMapper);
        modelAssembly.AddPart(markerLineActor);*/
        comDisplayer = new ModelComDisplayer(model);
        if (isShowCOM())
            modelAssembly.AddPart(comDisplayer.getVtkActor());

        // Now the muscles and other actuators
        addGeometryForForces(model, modelAssembly);

        // Add whole model assembly to object map
        mapObject2VtkObjects.put(model, modelAssembly);
        mapVtkObjects2Objects.put(modelAssembly, model);

        // Now call update to actually set all the positions/transforms of the actors and glyphs
        updateModelDisplay(model);

        return modelAssembly;
    }


    /**
     * updateModelDisplay with new transforms cached in animationCallback.
     * This method must be optimized since it's invoked during live animation
     * of simulations and/or analyses (ala IK).
     */
   public void updateModelDisplay(Model model) {
      // Cycle thru bodies and update their transforms from the kinematics engine
        BodySet bodies = model.getBodySet();
        int bodiesSize = bodies.getSize();
        for(int bodyNum=0; bodyNum<bodiesSize;  bodyNum++){

            Body body = bodies.get(bodyNum);

            // Fill the maps between objects and display to support picking, highlighting, etc..
            // The reverse map takes an actor to an Object and is filled as actors are created.
            vtkProp3D bodyRep= mapObject2VtkObjects.get(body);
            vtkMatrix4x4 bodyVtkTransform= getBodyTransform(model, body);
            if (bodyRep!=null)
               bodyRep.SetUserMatrix(bodyVtkTransform);

            // For dependents (markers, muscle points, update xforms as well)
            VisibleObject bodyDisplayer = body.getDisplayer();
            for(int j=0; j < bodyDisplayer.countDependents();j++){
                VisibleObject dependent = bodyDisplayer.getDependent(j);
                OpenSimObject owner = dependent.getOwner();

                if (Marker.safeDownCast(owner)!=null){
                   // Markers are handled in updateMarkersGeometry
                } else if (PathPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in updateForceGeometry
                } else {
                   // Must be a wrap object, so we set the wrap object's transform to the body transform (the wrap object
                   // has an additional xform that was set in createModelAssembly specifying the wrap object's xform in its parent body's space)
                   //vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                   //deptAssembly.SetUserMatrix(bodyVtkTransform);
                }
            }
        }
       
        updateMarkersGeometry(model.getMarkerSet());
        updateForceGeometry(model);
        comDisplayer.updateCOMLocation();
        updateUserObjects();
   }

   private void updateMarkersGeometry(MarkerSet markers) {
      for (int i=0; i<markers.getSize(); i++)
         markersRep.updateMarkerGeometry(markers.get(i));
   }

/*
   public void setMarkerLineVisible(Marker marker, boolean state) {
      double[] origin = {0.0, 0.0, 0.0};
      Boolean oldState = markerLinesVisible.get(marker);
      if (state != oldState) {
         markerLinesVisible.put(marker, state);
         vtkLineSource markerLine = mapMarkers2Lines.get(marker);
         if (state == false) {
            markerLine.SetPoint1(origin);
            markerLine.SetPoint2(origin);
         } else {
            double[] offset = new double[3];
            double[] gOffset = new double[3];
            double[] gOrigin = new double[3];
            SimbodyEngine de = marker.getBody().getModel().getSimbodyEngine();
            marker.getOffset(offset);
            OpenSimContext context=OpenSimDB.getInstance().getContext(marker.getBody().getModel());
            context.transformPosition(marker.getBody(), offset, gOffset);
            context.transformPosition(marker.getBody(), origin, gOrigin);
            markerLine.SetPoint1(gOffset);
            markerLine.SetPoint2(gOrigin);
         }
         getMarkersRep().setModified();
      }
   }
*/
   /**
    * Functions for dealing with actuator geometry
    */
    private void addGeometryForForces(Model mdl, vtkAssembly modelAssembly) {
        ForceSet forces = mdl.getForceSet();
        if (forces==null) return;
        for(int fNumber=0; fNumber < forces.getSize(); fNumber++){
           OpenSimObject f = forces.get(fNumber);
           Force force = Force.safeDownCast(f);
           PathActuator pa = PathActuator.safeDownCast(force);
           if (pa!= null) 
               addPathActuatorGeometry(pa, false);
           else if (force.hasGeometryPath()){
               addPathForceGeometry(force, false);
           }
           else
               addNonPathForceGeometry(modelAssembly, force);
        }
        modelAssembly.AddPart(getMuscleSegmentsRep().getVtkActor());
        getMuscleSegmentsRep().setModified();
        modelAssembly.AddPart(getMusclePointsRep().getVtkActor());
        getMusclePointsRep().setModified();
        //Ligaments ropes, other forces acting along a path
        modelAssembly.AddPart(getForceAlongPathPointsRep().getVtkActor());
        getForceAlongPathPointsRep().setModified();
        modelAssembly.AddPart(getForceAlongPathSegmentsRep().getVtkActor());
        getForceAlongPathSegmentsRep().setModified();
    }

    public void addPathActuatorGeometry(Force act, boolean callSetModified) {
       Muscle muscle = Muscle.safeDownCast(act);
       if(muscle == null) return;   // Could be just a force, in this case add and mark modified
       OpenSimContext context=OpenSimDB.getInstance().getContext(muscle.getModel());
        if (context.isDisabled(act)) return;
       LineSegmentMuscleDisplayer disp = new LineSegmentMuscleDisplayer(muscle, getMusclePointsRep(), getMuscleSegmentsRep());
       mapActuator2Displayer.put(act, disp);
       disp.addGeometry();
       if (callSetModified) {
          getMuscleSegmentsRep().setModified();
          getMusclePointsRep().setModified();
       }
       muscle=null;
    }

   private void updateForceGeometry(ForceSet acts) {
      Iterator<LineSegmentMuscleDisplayer> dispIter = mapActuator2Displayer.values().iterator();
      while(dispIter.hasNext()) dispIter.next().updateGeometry(true);
      Iterator<LineSegmentForceDisplayer> fDispIter = mapPathForces2Displayer.values().iterator();
      while(fDispIter.hasNext()) fDispIter.next().updateGeometry(true);
      Enumeration<Force> fNoPathIter = mapNoPathForces2Displayer.keys();
      while(fNoPathIter.hasMoreElements()){
          Force f = fNoPathIter.nextElement();
          OpenSimContext context=OpenSimDB.getInstance().getContext(f.getModel());
          if (context.isDisabled(f)) continue;
          if (f.getDisplayer()==null) continue;
          context.updateDisplayer(f);
          mapNoPathForces2Displayer.get(f).updateGeometry();
      }
     
      getMuscleSegmentsRep().setModified();
      getMusclePointsRep().setModified();
      getForceAlongPathSegmentsRep().setModified();
      getForceAlongPathPointsRep().setModified();
   }

   public void updateActuatorGeometry(Actuator act, boolean callUpdateDisplayer) {
      LineSegmentMuscleDisplayer disp = mapActuator2Displayer.get(act);
      if(disp != null) {
         disp.updateGeometry(callUpdateDisplayer);
         getMuscleSegmentsRep().setModified();
         getMusclePointsRep().setModified();
      }
   }

   public void updateForceGeometry(Model mdl) {
      updateForceGeometry(mdl.getForceSet());
   }

   public void removeActuatorGeometry(Actuator act) {
      LineSegmentMuscleDisplayer disp = mapActuator2Displayer.get(act);
      if(disp != null) {
         disp.removeGeometry();
         mapActuator2Displayer.remove(act);
         getMuscleSegmentsRep().setModified();
         getMusclePointsRep().setModified();
      }
   }

   public void setRenderMuscleActivations(boolean enabled) {
      Iterator<LineSegmentMuscleDisplayer> dispIter = mapActuator2Displayer.values().iterator();
      while(dispIter.hasNext()) dispIter.next().setRenderActivation(enabled);
      getMuscleSegmentsRep().setModified();
      getMusclePointsRep().setModified();
   }

   public void addMarkerGeometry(Marker marker) {
      getMarkersRep().addMarker(marker);
      /*
      vtkLineSource markerLine = new vtkLineSource();
      mapMarkers2Lines.put(marker, markerLine);
      markerLinesVisible.put(marker, false);
      markerLinePolyData.AddInput(markerLine.GetOutput());*/
      getMarkersRep().updateMarkerGeometry(marker);
   }

   public void removeMarkerGeometry(Marker marker) {
      
      getMarkersRep().removeMarkerGeometry(marker);
      // There appears to be a bug in removing inputs from
      // a vtkAppendPolyData object-- the output is never updated
      // to reflect the removal. So before removing it, set
      // the marker line to a point, so it is invisible.
      /*
      vtkLineSource markerLine = mapMarkers2Lines.get(marker);
      double[] origin = {0.0, 0.0, 0.0};
      markerLine.SetPoint1(origin);
      markerLine.SetPoint2(origin);
      markerLinePolyData.Update();
      markerLinePolyData.RemoveInput(markerLine.GetOutput());
      markerLinePolyData.Modified();
      mapMarkers2Lines.remove(marker);

      markerLinesVisible.remove(marker); */
      getMarkersRep().setModified();
   }

   public void setMarkerVisibility(Marker marker, boolean visible) {
      getMarkersRep().setMarkerVisibility(marker, visible);
      }

     /**
      * Get the vtkTransform matrix between ground and a body frame,
      */
     vtkMatrix4x4 getBodyTransform(Model model, Body body)
     {
            double[] flattenedXform = new double[16];
            OpenSimContext dContext = OpenSimDB.getInstance().getContext(model);
            dContext.getTransformAsDouble16(dContext.getTransform(body), flattenedXform);
            return convertTransformToVtkMatrix4x4(flattenedXform);
     }
    /**
     * return a reference to the vtkAssembly representing the model
     */
    public vtkAssembly getModelDisplayAssembly() {
        return modelDisplayAssembly;
    }
    
    public OpenSimObject pickObject(vtkAssemblyPath asmPath) {
        if (asmPath != null) {
         vtkAssemblyNode pickedAsm = asmPath.GetLastNode();
         return mapVtkObjects2Objects.get(pickedAsm.GetViewProp());
        }  
        return null;    // No selection
    }

    /* Make the entire model pickable or not pickable. modelDisplayAssembly.setPickable()
     * does not seem to do anything, so the pickable flag for each actor in the model
     * needs to be set.
     */
    public void setPickable(boolean pickable) {
       if (pickable) {
          modelDisplayAssembly.SetPickable(1);
          Enumeration<vtkProp3D> props = mapObject2VtkObjects.elements();
          while (props.hasMoreElements()) {
             props.nextElement().SetPickable(1);
          }
       } else {
          modelDisplayAssembly.SetPickable(0);
          Enumeration<vtkProp3D> props = mapObject2VtkObjects.elements();
          while (props.hasMoreElements()) {
             props.nextElement().SetPickable(0);
          }
       }
       getMarkersRep().setPickable(pickable);
       musclePointsRep.setPickable(pickable);
       muscleSegmentsRep.setPickable(pickable);
    }
 
    public vtkLinearTransform getModelDisplayTransform() {
        return modelDisplayTransform;
    }

    /**
     * Since there's no global model opacity, we'll take the opacity of the first object
     * we find and use it as value for the Opacity of he model. This has the advantage that
     * if Opacities are the same for all objects then the behavior is as expected.
     */
    public double getOpacity() {
        vtkProp3D prop = modelDisplayAssembly.GetParts().GetLastProp3D();  
        
        if (prop instanceof vtkAssembly){   //recur
            opacity = getAssemblyOpacity((vtkAssembly)prop);            
        }
        else if (prop instanceof vtkActor){ // Could be Actor or whatelse?
            opacity = ((vtkActor)prop).GetProperty().GetOpacity();
        }

        return opacity;
    }

    public void setOpacity(double opacity) {
        this.opacity = opacity;
    }

    /**
     * Compute bounding box for model as this can be useful for initial placement
     *  This is supposed to be a ballpark rather than an accurate estimate so that minor changes to
     * model do not cause overlap, but the bboox is not intended to be kept up-to-date
     * unused and turned out to be very slow for some reason*/
    private void computeModelBoundingbox() {
        modelDisplayAssembly.GetBounds(bounds);
    }

    // NOTE: these functions are necessary in order to deal with the model offsets...
    // Not the most general solution (e.g. if the hierarchy changed and there was more than one user matrix
    // modifying the model then this would not work).  But should work for now.
    public void transformModelToWorldPoint(double[] point) {
      vtkMatrix4x4 body2world = modelDisplayAssembly.GetUserMatrix();
      if(body2world != null) {
         double[] point4 = body2world.MultiplyPoint(new double[]{point[0],point[1],point[2],1.0});
         for(int i=0; i<3; i++) point[i]=point4[i];
      }
    }

    public void transformModelToWorldBounds(double[] bounds) {
      vtkMatrix4x4 body2world = modelDisplayAssembly.GetUserMatrix();
      if(body2world != null) {
         double[] minCorner = body2world.MultiplyPoint(new double[]{bounds[0],bounds[2],bounds[4],1.0});
         double[] width = new double[]{bounds[1]-bounds[0], bounds[3]-bounds[2], bounds[5]-bounds[4]};
         for(int i=0; i<3; i++) { bounds[2*i]=bounds[2*i+1]=minCorner[i]; } // initialize as min corner
         for(int i=0; i<3; i++) for(int j=0; j<3; j++) {
            if(body2world.GetElement(i,j)<0) bounds[2*i]+=width[j]*body2world.GetElement(i,j);
            else bounds[2*i+1]+=width[j]*body2world.GetElement(i,j);
         }
      }
    }

   public double[] getBoundsBodiesOnly() {
      double[] bounds = null;
      bodiesCollection.InitTraversal();
      for(;;) {
         vtkProp3D prop = bodiesCollection.GetNextProp3D();
         if(prop==null) break;
         if(prop.GetVisibility()!=0) bounds = ViewDB.boundsUnion(bounds, prop.GetBounds());
      }
      if (bounds!=null)
         transformModelToWorldBounds(bounds);
      return bounds;
   }

    /**
     * A flag indicating if the model assembly is shown or not for global visibility control
     */
    public boolean isVisible() {
        return visible;
    }

    public void setVisible(boolean onOff) {
        this.visible = onOff;
    }

    double[] getOffset() {
        return modelDisplayAssembly.GetPosition();
    }

    private double getAssemblyOpacity(vtkAssembly anAssembly) {
        vtkProp3DCollection parts = anAssembly.GetParts();
        parts.InitTraversal();
        int n =parts.GetNumberOfItems();
        for(int i=0; i<n; i++){
            vtkProp3D prop = parts.GetNextProp3D();
            if (prop instanceof vtkAssembly){   
                return getAssemblyOpacity((vtkAssembly)prop);
                // Should continue traversal here
            }
            else if (prop instanceof vtkActor){ 
                return ((vtkActor)prop).GetProperty().GetOpacity();
            }
        }
        return 0;
    }
   /**
    * Utility to convert Transform as defined by OpenSim to the form used by vtk
    */
   static vtkMatrix4x4 convertTransformToVtkMatrix4x4(double[] xformAsVector) {
      vtkMatrix4x4 m = new vtkMatrix4x4();    // This should be moved out for performance
      // Transpose the rotation part of the matrix per Pete!!
      for (int row = 0; row < 3; row++){
          for (int col = row; col < 4; col++){
             double swap = xformAsVector[row*4+col];
             xformAsVector[row*4+col]=xformAsVector[col*4+row];
             xformAsVector[col*4+row]=swap;
          }
      }
      m.DeepCopy(xformAsVector);
      return m;
   }

   /**
    * Method used to update display of motion objects during animation 
    */
   private void updateUserObjects() {
      //System.out.println("updateUserObjects");
      ViewDB.getInstance().updateAnnotationAnchors();
   }
   
   public void addUserObject(vtkActor userObj){
      if (getUserObjects().IsItemPresent(userObj)==0){
        getUserObjects().AddItem(userObj);
        modelDisplayAssembly.AddPart(userObj);
      }
   }
   
   public void removeUserObject(vtkActor userObj){
      getUserObjects().RemoveItem(userObj);
      modelDisplayAssembly.RemovePart(userObj);
   }

   /**
    * Functions to deal with glyphs for markers and muscle points/segments
    */
    private void initDefaultShapesAndColors() {

       // MarkerLine
       //markerLineActor.GetProperty().SetColor(SelectedObject.defaultSelectedColor);
       // Muscles
       createMusclePointRep(musclePointsRep);
       createMuscleSegmentRep(muscleSegmentsRep);
       // Ropes, other forces acting along path
       createMusclePointRep(otherPathPointsRep);
       createMuscleSegmentRep(otherPathSegmentsRep);
       otherPathPointsRep.setColorRange(forceAlongPathColor, forceAlongPathColor);
       otherPathSegmentsRep.setColorRange(forceAlongPathColor, forceAlongPathColor);
       // Arbitrary forces
       vtkArrowSource aForceDisplay=new vtkArrowSource();
       aForceDisplay.SetShaftRadius(0.02);
       aForceDisplay.SetTipLength(0.2);
       getForcesRep().setColorRange(inactiveMuscleColor, defaultMusclePointColor);
       vtkStripper strip3 = new vtkStripper();
       strip3.SetInput(aForceDisplay.GetOutput());
       getForcesRep().setShape(strip3.GetOutput());
       // Update global preference for Contact and Wrap geometry
       DisplayGeometryFactory.updateDisplayPreference();
    }

    private void createMuscleSegmentRep(OpenSimvtkOrientedGlyphCloud aMuscleSegmentsRep) {
      
        // Muscle segments 
        vtkPolyDataAlgorithm muscleSgt;  //Either cylinder or ellipsoid for now
        if (useCylinderMuscles) {
            vtkCylinderSource muscleSegment=new vtkCylinderSource();
            muscleSegment.SetRadius(ViewDB.getInstance().getMuscleDisplayRadius());
            muscleSegment.SetHeight(1.0);
            muscleSegment.SetCenter(0.0, 0.0, 0.0);
            muscleSegment.CappingOff();
            aMuscleSegmentsRep.setShape(muscleSegment.GetOutput());
        }
        else {
             vtkSphereSource muscleSegment=new vtkSphereSource();
             muscleSegment.SetRadius(ViewDB.getInstance().getMuscleDisplayRadius());
             vtkTransformPolyDataFilter stretcher = new vtkTransformPolyDataFilter();
             vtkTransform stretcherTransform = new vtkTransform();
             stretcherTransform.Scale(20.0, 0.5/ViewDB.getInstance().getMuscleDisplayRadius(), 20.0);
             muscleSegment.SetCenter(0.0, 0.0, 0.0);
             stretcher.SetInput(muscleSegment.GetOutput());
             stretcher.SetTransform(stretcherTransform);
             aMuscleSegmentsRep.setShape(stretcher.GetOutput());
        }
        aMuscleSegmentsRep.setColorRange(inactiveMuscleColor, defaultMuscleColor);
    }

    private void createMusclePointRep(OpenSimvtkGlyphCloud aMusclePointsRep) {

        // Muscle points
        vtkSphereSource viaPoint=new vtkSphereSource();
        viaPoint.SetRadius(ViewDB.getInstance().getMuscleDisplayRadius());
        viaPoint.SetCenter(0., 0., 0.);
        //getMusclePointsRep().setColors(defaultMusclePointColor, SelectedObject.defaultSelectedColor);
        aMusclePointsRep.setColorRange(inactiveMuscleColor, defaultMusclePointColor);
        aMusclePointsRep.setSelectedColor(SelectedObject.defaultSelectedColor);
        vtkStripper strip2 = new vtkStripper();
        strip2.SetInput(viaPoint.GetOutput());
        aMusclePointsRep.setShape(strip2.GetOutput());
        aMusclePointsRep.scaleByVectorComponents();
    }

    public OpenSimvtkGlyphCloud getGlyphObjectForActor(vtkActor act) {
        if (getMarkersRep().getVtkActor()==act)
            return getMarkersRep();
        else if (getMusclePointsRep().getVtkActor()==act)
            return getMusclePointsRep();
        else
           return null;
    }

    public MarkersDisplayer getMarkersRep() {
        return markersRep;
    }

    public OpenSimvtkGlyphCloud getMusclePointsRep() {
        return musclePointsRep;
    }

    public OpenSimvtkOrientedGlyphCloud getMuscleSegmentsRep() {
        return muscleSegmentsRep;
    }

    public OpenSimvtkOrientedGlyphCloud getForcesRep() {
        return forcesRep;
    }
    // Remmove dead references to help garbage collector.
    public void cleanup() {
        int rc = modelDisplayAssembly.GetReferenceCount();
        vtkProp3DCollection parts = modelDisplayAssembly.GetParts();
        for(int i=parts.GetNumberOfItems()-1; i>=0; i--){
            modelDisplayAssembly.RemovePart(parts.GetLastProp3D());
        }
        getUserObjects().RemoveAllItems();
        userObjects=null;
        bodiesCollection.RemoveAllItems();
        bodiesCollection=null;
                
        modelDisplayAssembly=null;
        mapObject2VtkObjects=null;
        mapVtkObjects2Objects=null;
        markersRep=null;
        musclePointsRep=null;
        muscleSegmentsRep=null;
        
    }
    public vtkProp3DCollection getUserObjects() {
        return userObjects;
    }

    private void addNonPathForceGeometry(vtkAssembly modelAssembly, OpenSimObject fObject) {
        Force f = Force.safeDownCast(fObject);
        OpenSimContext context=OpenSimDB.getInstance().getContext(f.getModel());
        if (context.isDisabled(f)) return;
        if (f.getDisplayer()==null) return;
        TwoBodyForceDisplayer foceDisplayer = new TwoBodyForceDisplayer(f, modelAssembly);
        vtkActor forceActor = foceDisplayer.getActor();
        if (forceActor!=null){
            mapNoPathForces2Displayer.put(f, foceDisplayer);
            mapVtkObjects2Objects.put(forceActor,f);
            mapObject2VtkObjects.put(f, forceActor);
        }
    }

    public OpenSimvtkGlyphCloud getForceAlongPathPointsRep() {
        return otherPathPointsRep;
    }

    public OpenSimvtkOrientedGlyphCloud getForceAlongPathSegmentsRep() {
        return otherPathSegmentsRep;
    }

    private void addPathForceGeometry(Force forceAlongPath, boolean callSetModified) {
        OpenSimContext context=OpenSimDB.getInstance().getContext(forceAlongPath.getModel());
        if (context.isDisabled(forceAlongPath)) return;
        LineSegmentForceDisplayer disp;
        try {
            disp = new LineSegmentForceDisplayer(forceAlongPath, getForceAlongPathPointsRep(), getForceAlongPathSegmentsRep());
            mapPathForces2Displayer.put(forceAlongPath, disp);
            disp.addGeometry();
            if (callSetModified) {
                getForceAlongPathSegmentsRep().setModified();
                getForceAlongPathPointsRep().setModified();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
       //mapActuator2Displayer.put(act, disp);
    }

    public boolean isShowCOM() {
        return showCOM;
    }

    public void setShowCOM(boolean showCOM) {
        if (showCOM) modelDisplayAssembly.AddPart(comDisplayer.getVtkActor());
        else modelDisplayAssembly.RemovePart(comDisplayer.getVtkActor());
        this.showCOM = showCOM;
    }

    public void removeGeometry(OpenSimObject object) {
        if (object instanceof Actuator)
            removeActuatorGeometry((Actuator) object);
        else if (object instanceof Force){
            Force f = Force.safeDownCast(object);
            if (f.hasGeometryPath()){
               removePathForceGeometry(f);
           }
            else
                removeNonPathForceGeometry(f);
        }
            
    }

    private void removePathForceGeometry(Force f) {
        if (f.getDisplayer()!=null){
            f.getDisplayer().setDisplayPreference(DisplayPreference.None);
            mapPathForces2Displayer.get(f).updateGeometry(false);
            getForceAlongPathSegmentsRep().setModified();
            getForceAlongPathPointsRep().setModified();
        }
    }

    private void removeNonPathForceGeometry(Force f) {
        if (f.getDisplayer()!=null){
            f.getDisplayer().setDisplayPreference(DisplayPreference.None);
            mapNoPathForces2Displayer.get(f).updateGeometry();
        }
    }

    public void updateForceGeometry(Force f, boolean visible) {
        if (!visible){  // turning off
            removeGeometry(f);
        }
        else{
            if (mapPathForces2Displayer.get(f)!=null){
                mapPathForces2Displayer.get(f).updateGeometry(true);
                LineSegmentForceDisplayer disp = mapPathForces2Displayer.get(f);
                if(disp != null) {
                    getForceAlongPathSegmentsRep().setModified();
                    getForceAlongPathPointsRep().setModified();
                }
            }
            else if (mapNoPathForces2Displayer.get(f)!=null){
                mapNoPathForces2Displayer.get(f).updateGeometry();
            }
        }
    }
}

