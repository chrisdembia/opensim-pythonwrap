/*
 * MotionDisplayer.java
 *
 * Created on January 19, 2007, 9:06 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.motionviewer;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Hashtable;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.pub.ViewDB;
import vtk.vtkActor;

/**
 *
 * @author Ayman. This class is used to preprocess motion files (SimmMotionData or similar) so taht
 * 1. Maping column indices to markers, gcs, ... is done only once.
 * 2. If additional objects need to be created for force or other markers they are maintained here.
 * 3. This isolates the display code from the specifics of SimmMotionData so that OpenSim proper creatures can be used.
 */
public class MotionDisplayer {
    
    private AbstractModel   model;
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
    // A local copy of motionObjects so that different motions have different motion objects
    //Hashtable<String, vtkActor> motionObjectInstances =new Hashtable<String, vtkActor>(10);
    
    /** Creates a new instance of MotionDisplayer */
    public MotionDisplayer(SimmMotionData motionData, AbstractModel model) {
        this.model = model;

        ArrayStr colNames = motionData.getColumnNames();
        // We should build sorted lists of object names so that we can find them easily
        for(int i=0; i < motionData.getNumColumns(); i++){
           String columnName = colNames.getitem(i);
           int numClassified = classifyColumn(i, columnName); // find out if column is gencord/muscle/segment/...etc.
           ObjectTypesInMotionFiles cType = mapIndicesToObjectTypes.get(i);
           System.out.println("col= "+columnName+" type= "+cType.toString());
           if (numClassified>1)  // If we did a group then skip the group
              i += (numClassified-1);
        }
    }

    public AbstractModel getModel() {
        return model;
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
     * so we don't want to start name searching from scratch!
     **/
   private int classifyColumn(int columnIndex, String columnName) 
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
            mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.Marker);
            mapIndicesToObjects.put(columnIndex, marker);
            return 1;
         }
      }
     // Body segment since experimental markers are in ground frame as ground_marker_??
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
                  vtkActor actorRep = MotionObjectsDB.getInstance().getMotionObject("marker");
                  mapIndicesToObjects.put(columnIndex, actorRep);
                  mapIndicesToObjects.put(columnIndex+1, actorRep);
                  mapIndicesToObjects.put(columnIndex+2, actorRep);
                  System.out.println("Added marker user object to model");
                  ViewDB.getInstance().getModelVisuals(model).addUserObject(actorRep);
                  return 3;
               }
               else {
                  mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.UNKNOWN);
                  return 0;  // Something else
               }
               
            }
            if (columnName.startsWith(bName+"_force_")){
               if (columnName.equals(bName+"_force_vx")){
                  mapIndicesToObjectTypes.put(columnIndex, ObjectTypesInMotionFiles.Segment_force_p1);
                  mapIndicesToObjectTypes.put(columnIndex+1, ObjectTypesInMotionFiles.Segment_force_p2);
                  mapIndicesToObjectTypes.put(columnIndex+2, ObjectTypesInMotionFiles.Segment_force_p3);
                  mapIndicesToObjectTypes.put(columnIndex+3, ObjectTypesInMotionFiles.Segment_force_p4);
                  mapIndicesToObjectTypes.put(columnIndex+4, ObjectTypesInMotionFiles.Segment_force_p5);
                  mapIndicesToObjectTypes.put(columnIndex+5, ObjectTypesInMotionFiles.Segment_force_p6);
                  vtkActor actorRep = MotionObjectsDB.getInstance().getMotionObject("force");
                  mapIndicesToObjects.put(columnIndex, actorRep);
                  mapIndicesToObjects.put(columnIndex+1, actorRep);
                  mapIndicesToObjects.put(columnIndex+2, actorRep);
                  mapIndicesToObjects.put(columnIndex+3, actorRep);
                  mapIndicesToObjects.put(columnIndex+4, actorRep);
                  mapIndicesToObjects.put(columnIndex+5, actorRep);
                  System.out.println("Added force user object to model");
                  ViewDB.getInstance().getModelVisuals(model).addUserObject(actorRep);
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

   void applyFrameToModel(int currentFrame, SimmMotionData simmMotionData) {
      ArrayStr colNames = simmMotionData.getColumnNames();
      for (int i = 0; i<simmMotionData.getNumColumns(); i++){
         // get Type and apply value
         ObjectTypesInMotionFiles cType = mapIndicesToObjectTypes.get(i);
         String colName = colNames.getitem(i);
         switch(cType){
            case GenCoord:
               ((AbstractCoordinate)(mapIndicesToObjects.get(i))).setValue(simmMotionData.getValue(colName, currentFrame));
               break;
            case Segment_marker_p1:
               vtkActor rep = ((vtkActor)(mapIndicesToObjects.get(i)));
               rep.SetPosition(simmMotionData.getValue(i, currentFrame), 
                       simmMotionData.getValue(i+1, currentFrame),
                       simmMotionData.getValue(i+2, currentFrame));
               break;
            case Segment_force_p1:
               vtkActor rep2 = ((vtkActor)(mapIndicesToObjects.get(i)));
               //rep2.SetUserTransform()  // orientation
               rep2.SetPosition(simmMotionData.getValue(i+3, currentFrame), 
                       simmMotionData.getValue(i+4, currentFrame),
                       simmMotionData.getValue(i+5, currentFrame));
               System.out.println("Force:pos"+simmMotionData.getValue(i+3, currentFrame)+", "
                       + simmMotionData.getValue(i+4, currentFrame)+", "
                       + simmMotionData.getValue(i+5, currentFrame));
                       
               break;
            default:
               break;
         }
      }

   }

}
