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

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractDynamicsEngine;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.Model;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.MuscleViaPoint;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import org.opensim.modeling.VisibleProperties;
import org.opensim.utils.GeometryFileLocator;
import org.opensim.view.pub.ViewDB;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCylinderSource;
import vtk.vtkLinearTransform;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyData;
import vtk.vtkPolyDataAlgorithm;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkSTLReader;
import vtk.vtkSphereSource;
import vtk.vtkStripper;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkAppendPolyData;
import vtk.vtkArrowSource;
import vtk.vtkLineSource;
import vtk.vtkOBJReader;

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
    private double[] defaultMuscleColor = new double[]{0.8, 0.1, 0.1};
    private double[] defaultMusclePointColor = new double[]{1.0, 0.0, 0.0};
    private double[] defaultMarkerColor = new double[]{1.0, 0.6, 0.8};
    private double[] defaultWrapObjectColor = new double[]{0.0, 1.0, 1.0};
    private boolean useCylinderMuscles=true;
    //private double DEFAULT_MUSCLE_RADIUS = .005;
    //private double DEFAULT_MUSCLE_POINT_RADIUS = .005;
    //private double DEFAULT_MARKER_RADIUS = .01;

    // Maps between objects and vtkProp3D for going from Actor to Object and vice versa
    // Objects are mapped to vtkProp3D in general, but some are known to be assemblies
    // e.g. Muscles, Models
    protected Hashtable<OpenSimObject, vtkProp3D> mapObject2VtkObjects = new Hashtable<OpenSimObject, vtkProp3D>();
    protected Hashtable<vtkProp3D, OpenSimObject> mapVtkObjects2Objects = new Hashtable<vtkProp3D, OpenSimObject>(50);
   
    private Hashtable<OpenSimObject, LineSegmentMuscleDisplayer> mapActuator2Displayer = new Hashtable<OpenSimObject, LineSegmentMuscleDisplayer>();

    protected Hashtable<OpenSimObject, Integer> mapMarkers2Glyphs = new Hashtable<OpenSimObject, Integer>(50);
    protected Hashtable<OpenSimObject, vtkLineSource> mapMarkers2Lines = new Hashtable<OpenSimObject, vtkLineSource>(50);
    protected Hashtable<OpenSimObject, Boolean> markerLinesVisible = new Hashtable<OpenSimObject, Boolean>(50);
    protected vtkActor markerLineActor = new vtkActor();
    protected vtkAppendPolyData markerLinePolyData = new vtkAppendPolyData();
    
    // Markers and muscle points are represented as Glyphs for performance
    private OpenSimvtkGlyphCloud  markersRep=new OpenSimvtkGlyphCloud(false);
    private OpenSimvtkGlyphCloud  musclePointsRep=new OpenSimvtkGlyphCloud(false);
    private OpenSimvtkOrientedGlyphCloud  muscleSegmentsRep = new OpenSimvtkOrientedGlyphCloud();
    private OpenSimvtkOrientedGlyphCloud  forcesRep = new OpenSimvtkOrientedGlyphCloud();

    private vtkProp3DCollection  userObjects = new vtkProp3DCollection();
    private vtkProp3DCollection  bodiesCollection = new vtkProp3DCollection();

    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals(Model aModel) {
        initDefaultShapesAndColors();
        modelDisplayAssembly = createModelAssembly(aModel);
        //modelDisplayAssembly.DebugOn();
        //int rc = modelDisplayAssembly.GetReferenceCount();
        setVisible(true);
    }
    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals() {
        initDefaultShapesAndColors();
        modelDisplayAssembly = new vtkAssembly();
        //modelDisplayAssembly.DebugOn();
        //int rc = modelDisplayAssembly.GetReferenceCount();
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
        String modelFilePath = model.getFilePath();
                
        vtkAssembly modelAssembly = new vtkAssembly();
        // Keep track of ground body to avoid recomputation
        defaultMarkerColor = ViewDB.getInstance().getDefaultMarkersColor();
        AbstractBody gnd = model.getDynamicsEngine().getGroundBody();
        BodySet bodies = model.getDynamicsEngine().getBodySet();
 
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++)
        {
            AbstractBody body = bodies.get(bodyNum);

            // Body actor
            vtkActor bodyRep = createAndAddBodyActor(modelAssembly, body, modelFilePath);

            if(bodyRep!=null) {
               // Fill the maps between objects and display to support picking, highlighting, etc..
               // The reverse map takes an actor to an Object and is filled as actors are created.
               mapObject2VtkObjects.put(body, bodyRep);
               mapVtkObjects2Objects.put(bodyRep, body);
            }

            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new vtkActor is created and attached 
            // to the same xform as the owner body.
            VisibleObject bodyDisplayer = body.getDisplayer();
            for(int j=0; j < bodyDisplayer.countDependents();j++){
                VisibleObject Dependent = bodyDisplayer.getDependent(j);
                
                OpenSimObject owner = Dependent.getOwner();
                if (AbstractMarker.safeDownCast(owner)!=null){
                    int index= getMarkersRep().addLocation(owner);
                    getMarkersRep().setVectorDataAtLocation(index,1,1,1);
                    mapMarkers2Glyphs.put(owner, new Integer(index));
                    vtkLineSource markerLine = new vtkLineSource();
                    mapMarkers2Lines.put(owner, markerLine);
                    markerLinesVisible.put(owner, false);
                    markerLinePolyData.AddInput(markerLine.GetOutput());
                    continue;
                } else if (MusclePoint.safeDownCast(owner)!=null||
                           MuscleViaPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in addActuatorsGeometry
                } else {
                   vtkActor attachmentRep = createAndAddWrapObjectActor(modelAssembly, Dependent);
                   if(attachmentRep!=null) {
                      mapObject2VtkObjects.put(Dependent.getOwner(), attachmentRep);
                      mapVtkObjects2Objects.put(attachmentRep, Dependent.getOwner());
                   }
                }
            }
        } //body

        // Add markers
        modelAssembly.AddPart(getMarkersRep().getVtkActor());

        vtkPolyDataMapper markerLineMapper = new vtkPolyDataMapper();
        markerLineMapper.SetInput(markerLinePolyData.GetOutput());
        markerLineActor.SetMapper(markerLineMapper);
        modelAssembly.AddPart(markerLineActor);

        // Now the muscles and other actuators
        addActuatorsGeometry(model, modelAssembly);

        // Add whole model assembly to object map
        mapObject2VtkObjects.put(model, modelAssembly);
        mapVtkObjects2Objects.put(modelAssembly, model);

        // Now call update to actually set all the positions/transforms of the actors and glyphs
        updateModelDisplay(model);

        return modelAssembly;
    }

   /**
    * Create actor for a single AbstractBody
    */
   private vtkActor createAndAddBodyActor(vtkAssembly modelAssembly, AbstractBody body, String modelFilePath)
   {
      vtkActor bodyRep = new vtkActor();

      VisibleObject bodyDisplayer = body.getDisplayer();

      vtkAppendPolyData bodyPolyData = new vtkAppendPolyData();
      // For each bone in the current body.
      for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {
          String boneFile = GeometryFileLocator.getInstance().getFullname(modelFilePath,bodyDisplayer.getGeometryFileName(k));
          if (boneFile==null)
             continue;
          if (boneFile.endsWith(".vtp")){
              vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
          polyReader.SetFileName(boneFile);

          vtkPolyData poly = polyReader.GetOutput();
          // Create polyData and append it to one common polyData object
          bodyPolyData.AddInput(poly);
          polyReader.GetOutput().ReleaseDataFlagOn();
      }
          else if (boneFile.endsWith(".stl")){
              vtkSTLReader polyReader = new vtkSTLReader();
              polyReader.SetFileName(boneFile);

              vtkPolyData poly = polyReader.GetOutput();
              // Create polyData and append it to one common polyData object
              bodyPolyData.AddInput(poly);
              polyReader.GetOutput().ReleaseDataFlagOn();             
          }
          else if (boneFile.endsWith(".obj")){
              vtkOBJReader objReader = new vtkOBJReader();
              objReader.SetFileName(boneFile);
              vtkPolyData poly = objReader.GetOutput();
              // Create polyData and append it to one common polyData object
              bodyPolyData.AddInput(poly);
          }
          else
              System.out.println("Unexpected extension for geometry file"+boneFile+"while processing body "+body.getName());
      }
      /*
     if (bodyDisplayer.getVisibleProperties().getShowAxes()){
          bodyAxes.SetOrigin(new double[]{0., 0., 0.});
          vtkPolyData axesGeometry = bodyAxes.GetOutput();
          bodyAxes.SetScaleFactor(.3);
          bodyPolyData.AddInput(bodyAxes.GetOutput());
     }*/
      // Mapper
      vtkPolyDataMapper bodyMapper = new vtkPolyDataMapper();
      bodyMapper.SetInput(bodyPolyData.GetOutput());  bodyPolyData=null;
      bodyRep.SetMapper(bodyMapper);
      
      // Scale
      double[] scales = new double[3];
      bodyDisplayer.getScaleFactors(scales);
      bodyRep.SetScale(scales);

      // Add to assembly only if populated to avoid artificially big bounding box
      if (bodyDisplayer.getNumGeometryFiles()>0) {
         bodiesCollection.AddItem(bodyRep);
         modelAssembly.AddPart(bodyRep);
      }
      applyDisplayPrefs(bodyDisplayer, bodyRep);
      return bodyRep;
   }

   /**
    * Create actor for wrap object(s)
    * TODO: Does this really handle multiple geometries under the visibleObject?
    */
   private vtkActor createAndAddWrapObjectActor(vtkAssembly modelAssembly, VisibleObject visibleObject)
   {
      vtkActor attachmentRep = new vtkActor();
      for(int gc=0; gc<visibleObject.countGeometry(); gc++){
         Geometry g = visibleObject.getGeometry(gc);
         AnalyticGeometry ag=null;
         ag = AnalyticGeometry.dynamic_cast(g);
         if (ag != null){  
            vtkPolyData analyticPolyData = AnalyticGeometryDisplayer.getPolyData(ag);

            // Move rep to proper location 
            vtkTransformPolyDataFilter mover = new vtkTransformPolyDataFilter();
            vtkTransform moverTransform = new vtkTransform();
            Transform xform=visibleObject.getTransform();
            double[] matRows = new double[16];
            xform.getMatrix(matRows);
            moverTransform.SetMatrix(convertTransformToVtkMatrix4x4(xform));
            mover.SetInput(analyticPolyData);
            mover.SetTransform(moverTransform);
            
            // Mapper
            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
            mapper.SetInput(mover.GetOutput());
            attachmentRep.SetMapper(mapper);

            // Color/shading
            attachmentRep.GetProperty().SetColor(defaultWrapObjectColor);
            applyDisplayPrefs(visibleObject, attachmentRep);
            //attachmentRep.GetProperty().SetRepresentationToWireframe();
         } else {  // General geometry
            // throw an exception for not implemented though should be identical
            throw new UnsupportedOperationException(
                    "Single Model Visuals: Geometry visualization Not yet implemented");
         }
      }

      if(attachmentRep!=null) modelAssembly.AddPart(attachmentRep);
      applyDisplayPrefs(visibleObject,attachmentRep);
      return attachmentRep;
   }

    /**
     * updateModelDisplay with new transforms cached in animationCallback.
     * This method must be optimized since it's invoked during live animation
     * of simulations and/or analyses (ala IK).
     */
   public void updateModelDisplay(Model model) {
      // Cycle thru bodies and update their transforms from the kinematics engine
        BodySet bodies = model.getDynamicsEngine().getBodySet();
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++){

            AbstractBody body = bodies.get(bodyNum);

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

                if (AbstractMarker.safeDownCast(owner)!=null){
                   // Markers are handled in updateMarkersGeometry
                } else if (MusclePoint.safeDownCast(owner)!=null||
                        MuscleViaPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in updateActuatorsGeometry
                } else {
                   // Must be a wrap object, so we set the wrap object's transform to the body transform (the wrap object
                   // has an additional xform that was set in createModelAssembly specifying the wrap object's xform in its parent body's space)
                   vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                   deptAssembly.SetUserMatrix(bodyVtkTransform);
                }
            }
        }
       
        updateMarkersGeometry(model.getDynamicsEngine().getMarkerSet());
        updateActuatorsGeometry(model);
        updateUserObjects();
   }

   private void updateMarkersGeometry(MarkerSet markers) {
      for (int i=0; i<markers.getSize(); i++)
         updateMarkerGeometry(markers.get(i));
   }

   public void updateMarkerGeometry(AbstractMarker marker) {
      // Convert marker offset to global offset, and update the marker's glyph
      // location and the line to its parent body.
      double[] offset = new double[3];
      double[] gOffset = new double[3];
      double[] origin = {0.0, 0.0, 0.0};
      double[] gOrigin = new double[3];
      int index = mapMarkers2Glyphs.get(marker).intValue();
      AbstractDynamicsEngine de = marker.getBody().getDynamicsEngine();
      marker.getOffset(offset);
      de.transformPosition(marker.getBody(), offset, gOffset);
      de.transformPosition(marker.getBody(), origin, gOrigin);
      getMarkersRep().setLocation(index, gOffset);
      vtkLineSource markerLine = mapMarkers2Lines.get(marker);
      markerLine.SetPoint1(gOffset);
      if (markerLinesVisible.get(marker) == false)
         markerLine.SetPoint2(gOffset);
      else
         markerLine.SetPoint2(gOrigin);
      getMarkersRep().setModified();
   }

   public void setMarkerLineVisible(AbstractMarker marker, boolean state) {
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
            AbstractDynamicsEngine de = marker.getBody().getDynamicsEngine();
            marker.getOffset(offset);
            de.transformPosition(marker.getBody(), offset, gOffset);
            de.transformPosition(marker.getBody(), origin, gOrigin);
            markerLine.SetPoint1(gOffset);
            markerLine.SetPoint2(gOrigin);
         }
         getMarkersRep().setModified();
      }
   }

   /**
    * Functions for dealing with actuator geometry
    */
    private void addActuatorsGeometry(Model mdl, vtkAssembly modelAssembly) {
        ActuatorSet acts = mdl.getActuatorSet();
        if (acts==null) return;
        for(int actNumber=0; actNumber < acts.getSize(); actNumber++){
           addActuatorGeometry(acts.get(actNumber), false);
        }
        modelAssembly.AddPart(getMuscleSegmentsRep().getVtkActor());
        getMuscleSegmentsRep().setModified();
        modelAssembly.AddPart(getMusclePointsRep().getVtkActor());
        getMusclePointsRep().setModified();
        modelAssembly.AddPart(getForcesRep().getVtkActor());
        getForcesRep().setModified();
    }

    public void addActuatorGeometry(AbstractActuator act, boolean callSetModified) {
       AbstractMuscle muscle = AbstractMuscle.safeDownCast(act);
       if(muscle == null) return;   // Could be just a force, in this case add and mark modified
       LineSegmentMuscleDisplayer disp = new LineSegmentMuscleDisplayer(muscle, getMusclePointsRep(), getMuscleSegmentsRep());
       mapActuator2Displayer.put(act, disp);
       disp.addGeometry();
       if (callSetModified) {
          getMuscleSegmentsRep().setModified();
          getMusclePointsRep().setModified();
       }
       muscle=null;
    }

   private void updateActuatorsGeometry(ActuatorSet acts) {
      Iterator<LineSegmentMuscleDisplayer> dispIter = mapActuator2Displayer.values().iterator();
      while(dispIter.hasNext()) dispIter.next().updateGeometry(true);
      getMuscleSegmentsRep().setModified();
      getMusclePointsRep().setModified();
   }

   public void updateActuatorGeometry(AbstractActuator act, boolean callUpdateDisplayer) {
      LineSegmentMuscleDisplayer disp = mapActuator2Displayer.get(act);
      if(disp != null) {
         disp.updateGeometry(callUpdateDisplayer);
         getMuscleSegmentsRep().setModified();
         getMusclePointsRep().setModified();
      }
   }

   public void updateActuatorsGeometry(Model mdl) {
      updateActuatorsGeometry(mdl.getActuatorSet());
   }

   public void removeActuatorGeometry(AbstractActuator act) {
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

   public void addMarkerGeometry(AbstractMarker marker) {
      int index = getMarkersRep().addLocation(marker);
      getMarkersRep().setVectorDataAtLocation(index,1,1,1);
      getMarkersRep().setSelected(index, false);
      getMarkersRep().setModified();
      mapMarkers2Glyphs.put(marker, new Integer(index));
      vtkLineSource markerLine = new vtkLineSource();
      mapMarkers2Lines.put(marker, markerLine);
      markerLinesVisible.put(marker, false);
      markerLinePolyData.AddInput(markerLine.GetOutput());
      updateMarkerGeometry(marker);
   }

   public void removeMarkerGeometry(AbstractMarker marker) {
      int glyphID = mapMarkers2Glyphs.get(marker);
      getMarkersRep().remove(glyphID);
      mapMarkers2Glyphs.remove(marker);

      // There appears to be a bug in removing inputs from
      // a vtkAppendPolyData object-- the output is never updated
      // to reflect the removal. So before removing it, set
      // the marker line to a point, so it is invisible.
      vtkLineSource markerLine = mapMarkers2Lines.get(marker);
      double[] origin = {0.0, 0.0, 0.0};
      markerLine.SetPoint1(origin);
      markerLine.SetPoint2(origin);
      markerLinePolyData.Update();
      markerLinePolyData.RemoveInput(markerLine.GetOutput());
      markerLinePolyData.Modified();
      mapMarkers2Lines.remove(marker);

      markerLinesVisible.remove(marker);
      getMarkersRep().setModified();
   }

   public void setMarkerVisibility(AbstractMarker marker, boolean visible) {
      int index = (mapMarkers2Glyphs.get(marker)).intValue(); 
      vtkLineSource markerLine = mapMarkers2Lines.get(marker);
      if (visible) {
         getMarkersRep().show(index);
         // Set the endpoints of the marker line, because the only other
         // place this is done is updateModelDisplay(), which is not called
         // in this case.
         double[] pos = new double[3];
         double[] gPos = new double[3];
         double[] origin = {0.0, 0.0, 0.0};
         double[] gOrigin = new double[3];
         AbstractBody body = marker.getBody();
         AbstractDynamicsEngine de = body.getDynamicsEngine();
         marker.getOffset(pos);
         de.transformPosition(body, origin, gOrigin);
         de.transformPosition(body, pos, gPos);
         markerLine.SetPoint1(gOrigin);
         markerLine.SetPoint2(gOrigin);
         //markerLine.SetPoint2(gPos);
      } else {
         getMarkersRep().hide(index);
         markerLine.SetPoint1(0.0, 0.0, 0.0);
         markerLine.SetPoint2(0.0, 0.0, 0.0);
      }
      getMarkersRep().setModified();
   }

     /**
      * Get the vtkTransform matrix between ground and a body frame,
      */
     vtkMatrix4x4 getBodyTransform(Model model, AbstractBody body)
     {
            Transform xform = model.getDynamicsEngine().getTransform(body);
            return convertTransformToVtkMatrix4x4(xform);
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
   private vtkMatrix4x4 convertTransformToVtkMatrix4x4(Transform xform) {
      double[] xformAsVector= new double[16];
      xform.getMatrix(xformAsVector);
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

       // Markers
       vtkSphereSource marker=new vtkSphereSource();
       marker.SetRadius(ViewDB.getInstance().getMarkerDisplayRadius());
       marker.SetCenter(0., 0., 0.);
       //getMarkersRep().setColors(defaultMarkerColor, SelectedObject.defaultSelectedColor);
       defaultMarkerColor = ViewDB.getInstance().getDefaultMarkersColor();
       getMarkersRep().setColorRange(defaultMarkerColor, defaultMarkerColor);
       getMarkersRep().setSelectedColor(SelectedObject.defaultSelectedColor);
       vtkStripper strip1 = new vtkStripper();
       strip1.SetInput(marker.GetOutput());
       getMarkersRep().setShape(strip1.GetOutput());
       getMarkersRep().scaleByVectorComponents();
       markerLineActor.GetProperty().SetColor(SelectedObject.defaultSelectedColor); // marker lines are displayed only when markers are selected
       
       // Muscle points
       vtkSphereSource viaPoint=new vtkSphereSource();
       viaPoint.SetRadius(ViewDB.getInstance().getMuscleDisplayRadius());
       viaPoint.SetCenter(0., 0., 0.);
       //getMusclePointsRep().setColors(defaultMusclePointColor, SelectedObject.defaultSelectedColor);
//       getMusclePointsRep().setColorRange(inactiveMuscleColor, defaultMusclePointColor);
       double[] zeroMusclePointColor = new double[]{0.0, 1.0, 0.0};
       getMusclePointsRep().set3ColorRange(inactiveMuscleColor, zeroMusclePointColor, defaultMusclePointColor);
       getMusclePointsRep().setSelectedColor(SelectedObject.defaultSelectedColor);
       vtkStripper strip2 = new vtkStripper();
       strip2.SetInput(viaPoint.GetOutput());
       getMusclePointsRep().setShape(strip2.GetOutput());
       getMusclePointsRep().scaleByVectorComponents();
       
       // Muscle segments 
       vtkPolyDataAlgorithm muscleSgt;  //Either cylinder or ellipsoid for now
       if (useCylinderMuscles) {
           vtkCylinderSource muscleSegment =new vtkCylinderSource();
           muscleSegment.SetRadius(ViewDB.getInstance().getMuscleDisplayRadius());
           muscleSegment.SetHeight(1.0);
           muscleSegment.SetCenter(0.0, 0.0, 0.0);
           muscleSegment.CappingOff();
           getMuscleSegmentsRep().setShape(muscleSegment.GetOutput());
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
            getMuscleSegmentsRep().setShape(stretcher.GetOutput());
       }
       //getMuscleSegmentsRep().setColor(defaultMuscleColor);
//       getMuscleSegmentsRep().setColorRange(inactiveMuscleColor, defaultMuscleColor);
       double[] zeroMuscleColor = new double[]{0.0, 1.0, 0.0};
       getMuscleSegmentsRep().set3ColorRange(inactiveMuscleColor, zeroMuscleColor, defaultMuscleColor);
       
       // Arbitrary forces
       vtkArrowSource aForceDisplay=new vtkArrowSource();
       aForceDisplay.SetShaftRadius(0.02);
       aForceDisplay.SetTipLength(0.2);
       getForcesRep().setColorRange(inactiveMuscleColor, defaultMusclePointColor);
       vtkStripper strip3 = new vtkStripper();
       strip3.SetInput(aForceDisplay.GetOutput());
       getForcesRep().setShape(strip3.GetOutput());
       
    }

    public OpenSimvtkGlyphCloud getGlyphObjectForActor(vtkActor act) {
        if (getMarkersRep().getVtkActor()==act)
            return getMarkersRep();
        else if (getMusclePointsRep().getVtkActor()==act)
            return getMusclePointsRep();
        else
           return null;
    }

    public OpenSimvtkGlyphCloud getMarkersRep() {
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
	/**
	 * Apply user display preference (None, wireframe, shading)
	 */
    private void applyDisplayPrefs(VisibleObject objectDisplayer, vtkActor objectRep) {
        if (objectRep==null) return;
        VisibleProperties props = objectDisplayer.getVisibleProperties();
        int vl = props.getDisplayPreference().swigValue();
        // Show vs. Hide
        if (props.getDisplayPreference() == VisibleProperties.DisplayPreference.None){
            objectRep.SetVisibility(0);
            return;
        }
        objectRep.SetVisibility(1);
        if (props.getDisplayPreference().swigValue()==VisibleProperties.DisplayPreference.WireFrame.swigValue())
            objectRep.GetProperty().SetRepresentationToWireframe();
        else {

            if (props.getDisplayPreference() == VisibleProperties.DisplayPreference.FlatShaded)
                objectRep.GetProperty().SetInterpolationToFlat();
            else
                objectRep.GetProperty().SetRepresentationToSurface();
        }
    }

    public vtkProp3DCollection getUserObjects() {
        return userObjects;
    }
    
}

