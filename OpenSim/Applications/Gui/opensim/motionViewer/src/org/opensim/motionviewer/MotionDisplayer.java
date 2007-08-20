/*
 * MotionDisplayer.java
 *
 * Created on January 19, 2007, 9:06 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.motionviewer;

import java.util.Hashtable;
import java.util.ArrayList;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.Model;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.StateVector;
import org.opensim.modeling.Storage;
import org.opensim.view.OpenSimvtkGlyphCloud;
import org.opensim.view.SingleModelVisuals;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 * 
 * 
 * 
 * @author Ayman. This class is used to preprocess motion files (Storage or similar) so that
 * 1. Mapping column indices to markersRep, gcs, ... is done only once.
 * 2. If additional objects need to be created for force or other markersRep they are maintained here.
 * 3. This isolates the display code from the specifics of Storage so that OpenSim proper creatures can be used.
 */

public class MotionDisplayer {
    
    public enum ObjectTypesInMotionFiles{GenCoord, 
                                         GenCoord_Velocilty, 
                                         Muscle, 
                                         Marker, 
                                         Segment, 
                                         Segment_marker_p1, 
                                         Segment_marker_p2, 
                                         Segment_marker_p3, 
                                         Segment_force_p1, 
                                         Segment_force_p2, 
                                         Segment_force_p3, 
                                         Segment_force_p4, 
                                         Segment_force_p5, 
                                         Segment_force_p6, 
                                         Segment_torque_p1, 
                                         Segment_torque_p2, 
                                         Segment_torque_p3, 
                                         UNKNOWN};

    Hashtable<Integer, ObjectTypesInMotionFiles> mapIndicesToObjectTypes=new Hashtable<Integer, ObjectTypesInMotionFiles>(40);
    Hashtable<Integer, Object> mapIndicesToObjects=new Hashtable<Integer, Object>(40);
    OpenSimvtkGlyphCloud  forcesRep=new OpenSimvtkGlyphCloud(true);
    OpenSimvtkGlyphCloud  markersRep=new OpenSimvtkGlyphCloud(false);
    private Storage simmMotionData;
    private Model model;

    public class ObjectIndexPair {
       public Object object;
       public int stateVectorIndex; // Actual (0-based) index into state vector
       public ObjectIndexPair(Object obj, int idx) { this.object = obj; this.stateVectorIndex = idx; }
    }
    // For faster access to gencoords/markers/forces to update in applyFrameToModel
    ArrayList<ObjectIndexPair> genCoordColumns=null;
    ArrayList<ObjectIndexPair> segmentMarkerColumns=null; // state vector index of the first of three (x y z) coordinates for a marker
    ArrayList<ObjectIndexPair> segmentForceColumns=null; // state vector index of the first of six (px py pz vx vy vz) coordinates for a force vector

    ArrayDouble interpolatedStates = null;

    boolean statesFile = false; // special type of file that contains full state vectors
    
    // A local copy of motionObjects so that different motions have different motion objects
    //Hashtable<String, vtkActor> motionObjectInstances =new Hashtable<String, vtkActor>(10);
    
    /** Creates a new instance of MotionDisplayer */
    public MotionDisplayer(Storage motionData, Model model) {
        this.model = model;
        simmMotionData = motionData;

        AddMotionObjectsRep(model);

        ArrayStr colNames = motionData.getColumnLabels();
        int numColumnsIncludingTime = colNames.getSize();
        interpolatedStates = new ArrayDouble(0.0, numColumnsIncludingTime-1);

        ArrayStr stateNames = new ArrayStr();
        stateNames.append("time");
        model.getStateNames(stateNames);

        if(colNames.arrayEquals(stateNames)) {
           // This is a states file
           statesFile = true;
           SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
           if(vis!=null) vis.setRenderMuscleActivations(true);
        } else  {
           // We should build sorted lists of object names so that we can find them easily
           for(int i=0; i < numColumnsIncludingTime; i++){
              String columnName = colNames.getitem(i);   // Time is included in labels
              int numClassified = classifyColumn(model, i, columnName); // find out if column is gencord/muscle/segment/...etc.
              ObjectTypesInMotionFiles cType = mapIndicesToObjectTypes.get(i);
              if (numClassified>1)  // If we did a group then skip the group
                 i += (numClassified-1);
           }

           genCoordColumns = new ArrayList<ObjectIndexPair>(numColumnsIncludingTime);
           segmentMarkerColumns = new ArrayList<ObjectIndexPair>(numColumnsIncludingTime);
           segmentForceColumns = new ArrayList<ObjectIndexPair>(numColumnsIncludingTime);
           for (int i = 0; i< numColumnsIncludingTime; i++){
               ObjectTypesInMotionFiles cType = mapIndicesToObjectTypes.get(i);
               switch(cType){
                  case GenCoord: 
                     genCoordColumns.add(new ObjectIndexPair(mapIndicesToObjects.get(i),i-1));
                     break;
                  case Segment_marker_p1:
                     segmentMarkerColumns.add(new ObjectIndexPair(mapIndicesToObjects.get(i),i-1));
                     break;
                  case Segment_force_p1:
                     segmentForceColumns.add(new ObjectIndexPair(mapIndicesToObjects.get(i),i-1));
                     break;
               }
            }
        }
    }

    private void AddMotionObjectsRep(final Model model) {
        forcesRep.setShape(MotionObjectsDB.getInstance().getShape("force"));
        forcesRep.setColor(new double[]{0., 1.0, 0.});
        forcesRep.setOpacity(0.7);
        forcesRep.setScaleFactor(0.001);
        forcesRep.orientByNormalAndScaleByVector();
        
        markersRep.setShape(MotionObjectsDB.getInstance().getShape("marker"));
        markersRep.setColor(new double[]{0.0, 0.0, 1.0}); //Scale , scaleBy

        ViewDB.getInstance().addUserObject(model, forcesRep.getVtkActor());
        ViewDB.getInstance().addUserObject(model, markersRep.getVtkActor());
    }

    //interface applyValue
    //{
    //   public void apply(double val);
    //}
    /*
     * Check what kind of data is at columnIndex, and add object of relevance
     * to the map "mapIndicesToObjects" for quick access during animation
     *
     * returns the number of columns that has been classified since _px may lead to _py, _pz
     * so we don't want to start name searching from scratch.
     * A side effect is the creation of motion object instances and adding them to the model
     **/
   private int classifyColumn(Model model, int columnIndex, String columnName) 
   {
      CoordinateSet coords = model.getDynamicsEngine().getCoordinateSet();
      ObjectTypesInMotionFiles retType = ObjectTypesInMotionFiles.UNKNOWN;
      for (int i = 0; i<coords.getSize(); i++){
         AbstractCoordinate co = coords.get(i);
         // GenCoord
         String cName = co.getName();
         if (cName.equals(columnName)){
            mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.GenCoord);
            mapIndicesToObjects.put(columnIndex, co); //co.setValue();
            return 1;
         }
         // GenCoord_Velocilty
         if (columnName.endsWith("_vel")){
            if (columnName.substring(0, cName.length()-4).equals(cName))
               mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.GenCoord_Velocilty);
               mapIndicesToObjects.put(columnIndex, co); 
               return 1;
         }         
      }
     /* ordering from SIMM
      else if ((musc_index = name_is_muscle(ms, motion->columnname[i], NULL, &sType, &cutoffFreq, yes)) >= 0)
         motion->mopt.muscles[musc_index] = motion->motiondata[i];
      else if ((lig_index = get_ligament_index(ms->modelnum, motion->columnname[i])) >= 0)
         motion->mopt.ligaments[lig_index] = motion->motiondata[i];
      else if ((seg = name_is_marker(ms, motion->columnname[i], &motion_object, &ref, &sType, &cutoffFreq, yes)) >= 0 &&
               motion_object >= 0 && ref >= 0)
         store_motion_object_instance(ms->modelnum, &motion->mopt, seg, motion_object, ref, i);
      else if ((seg = name_is_forceplate(ms, motion->columnname[i], &motion_object, &ref, &sType, &cutoffFreq, yes)) >= 0 &&
               motion_object >= 0 && ref >= 0)
         store_motion_object_instance(ms->modelnum, &motion->mopt, seg, motion_object, ref, i);
      else if ((seg = name_is_body_segment(ms, motion->columnname[i], &motion_object, &ref, &sType, &cutoffFreq, yes)) >= 0 &&
               motion_object >= 0 && ref >= 0)
               */
      // @ToDo muscles
      // @ToDo ligaments
       MarkerSet markers = model.getDynamicsEngine().getMarkerSet();
       for (int i = 0; i<markers.getSize(); i++){
         AbstractMarker marker = markers.get(i);
         // 
         String cName = marker.getName();
         if (columnName.startsWith(cName+"_")){
            mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.Segment_marker_p1);
            mapIndicesToObjectTypes.put(columnIndex+1, ObjectTypesInMotionFiles.Segment_marker_p2);
            mapIndicesToObjectTypes.put(columnIndex+2, ObjectTypesInMotionFiles.Segment_marker_p3);
            int index= markersRep.addLocation(0., 0., 0.);
            mapIndicesToObjects.put(columnIndex, new Integer(index));
            mapIndicesToObjects.put(columnIndex+1, new Integer(index));
            mapIndicesToObjects.put(columnIndex+2, new Integer(index));
            return 3;
         }
      }
     // Body segment since experimental markersRep are in ground frame as ground_marker_??
       BodySet bodySet = model.getDynamicsEngine().getBodySet();
       String[] motionObjectNames=MotionObjectsDB.getInstance().getAvailableNames();
       for (int i = 0; i<bodySet.getSize(); i++){
         AbstractBody bdy = bodySet.get(i);
         // 
         String bName = bdy.getName();
         if (columnName.startsWith(bName+"_")){
            if (columnName.startsWith(bName+"_marker_")){
               if (columnName.equals(bName+"_marker_px")){
                  mapIndicesToObjectTypes.put(columnIndex,   ObjectTypesInMotionFiles.Segment_marker_p1);
                  mapIndicesToObjectTypes.put(columnIndex+1, ObjectTypesInMotionFiles.Segment_marker_p2);
                  mapIndicesToObjectTypes.put(columnIndex+2, ObjectTypesInMotionFiles.Segment_marker_p3);
                  int index= markersRep.addLocation(0., 0., 0.);
                  mapIndicesToObjects.put(columnIndex, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+1, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+2, new Integer(index));
                  return 3;
               }
               else {
                  mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.UNKNOWN);
                  return 0;  // Something else
               }
               
            }
            if (columnName.startsWith(bName+"_force_")){
               if (columnName.equals(bName+"_force_vx")){
                  if (!bName.equalsIgnoreCase("ground")){ // use body frame and xform data while applying.
                     throw new UnsupportedOperationException("Not yet implemented");
                  }
                  mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.Segment_force_p1);
                  mapIndicesToObjectTypes.put(columnIndex+1, ObjectTypesInMotionFiles.Segment_force_p2);
                  mapIndicesToObjectTypes.put(columnIndex+2, ObjectTypesInMotionFiles.Segment_force_p3);
                  mapIndicesToObjectTypes.put(columnIndex+3, ObjectTypesInMotionFiles.Segment_force_p4);
                  mapIndicesToObjectTypes.put(columnIndex+4, ObjectTypesInMotionFiles.Segment_force_p5);
                  mapIndicesToObjectTypes.put(columnIndex+5, ObjectTypesInMotionFiles.Segment_force_p6);
                  int index= forcesRep.addLocation(0., 0., 0.);
                  mapIndicesToObjects.put(columnIndex, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+1, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+2, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+3, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+4, new Integer(index));
                  mapIndicesToObjects.put(columnIndex+5, new Integer(index));
                  return 6;
               }
               else{
                  mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.UNKNOWN);
                  return 0;  // Something else, maybe a velocity component
               }
            }
            mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.Segment);
            mapIndicesToObjects.put(columnIndex, bdy);
            return 1;
         }
      }
      mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.UNKNOWN);
      return 0;
   }

   void applyFrameToModel(int currentFrame) 
   {
      StateVector states=simmMotionData.getStateVector(currentFrame);
      applyStatesToModel(states.getData());
   }

   void applyTimeToModel(double currentTime)
   {
      //TODO: Option to snap to nearest valid storage time rather than interpolate...
      //
      // Better clamp the time otherwise we'll get linear extrapolation outside the valid time range (we might get out-of-range times
      // if we're playing this motion synced with another motion)
      double clampedTime = (currentTime < simmMotionData.getFirstTime()) ? simmMotionData.getFirstTime() : 
                           (currentTime > simmMotionData.getLastTime()) ? simmMotionData.getLastTime() : currentTime;
      simmMotionData.getDataAtTime(clampedTime, interpolatedStates.getSize(), interpolatedStates);
      applyStatesToModel(interpolatedStates);
   }

   private void applyStatesToModel(ArrayDouble states) 
   {
      if(statesFile) {
         model.setStates(states);
      } else {
         for(int i=0; i<genCoordColumns.size(); i++) {
            AbstractCoordinate coord=(AbstractCoordinate)(genCoordColumns.get(i).object);
            if(!coord.getLocked()) {
               int index = genCoordColumns.get(i).stateVectorIndex;
               coord.setValue(states.getitem(index));
            }
         }

         for(int i=0; i<segmentMarkerColumns.size(); i++) {
            int markerIndex = ((Integer)(segmentMarkerColumns.get(i).object)).intValue();
            int index = segmentMarkerColumns.get(i).stateVectorIndex;
            markersRep.setLocation(markerIndex, states.getitem(index), states.getitem(index+1), states.getitem(index+2));
         }
         if(segmentMarkerColumns.size()>0) markersRep.setModified();

         for(int i=0; i<segmentForceColumns.size(); i++) {
            int forceIndex = ((Integer)(segmentForceColumns.get(i).object)).intValue();
            int index = segmentForceColumns.get(i).stateVectorIndex;
            forcesRep.setNormalAtLocation(forceIndex, states.getitem(index), 
                    states.getitem(index+1),
                    states.getitem(index+2));
            forcesRep.setLocation(forceIndex, states.getitem(index+3), 
                    states.getitem(index+4),
                    states.getitem(index+5));
         }
         if(segmentForceColumns.size()>0) forcesRep.setModified();
      }
    }

    /*
     * cleanupDisplay is called when the motion is mode non-current either explicitly by the user or by selecting
     * another motion for the same model and making it current */
    void cleanupDisplay() {
        ViewDB.getInstance().removeUserObject(model, forcesRep.getVtkActor());
        ViewDB.getInstance().removeUserObject(model, markersRep.getVtkActor());

        // Don't attempt to change muscle activation color if we're here because
        // the model is closing... check this by checking model is still in models list
        // This may help fix a crash that Sam got when he closed a model that had a MotionDisplayer
        // associated with it.  It may be because setRenderMuscleActivations ends up updating the actuator
        // geometry, and if the model is closing it may be that it was in the process of being deleted when
        // those actuators were referred to...  So we avoid all that with this if statement.
        if(OpenSimDB.getInstance().hasModel(model) && statesFile) {
           SingleModelVisuals vis = ViewDB.getInstance().getModelVisuals(model);
           if(vis!=null) vis.setRenderMuscleActivations(false);
        }
    }

   public Storage getSimmMotionData() {
      return simmMotionData;
   }

   public Model getModel() {
      return model;
   }

}
