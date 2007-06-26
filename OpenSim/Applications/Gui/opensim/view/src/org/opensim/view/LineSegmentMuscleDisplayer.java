package org.opensim.view;

import java.util.Vector;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ArrayMusclePoint;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.LineGeometry;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.MuscleWrapPoint;
import org.opensim.modeling.VisibleObject;
import org.opensim.modeling.VisibleProperties.DisplayPreference;
import vtk.vtkMatrix4x4;

public class LineSegmentMuscleDisplayer {

   private AbstractMuscle act;
   private OpenSimvtkGlyphCloud musclePointsRep;
   private OpenSimvtkOrientedGlyphCloud muscleSegmentsRep;

   Vector<Integer> pointGlyphIds = new Vector<Integer>(3);
   Vector<Integer> segmentGlyphIds = new Vector<Integer>(3);

   public LineSegmentMuscleDisplayer(AbstractMuscle act, OpenSimvtkGlyphCloud musclePointsRep, OpenSimvtkOrientedGlyphCloud muscleSegmentsRep)
   {
      this.act = act;
      this.musclePointsRep = musclePointsRep;
      this.muscleSegmentsRep = muscleSegmentsRep;
   }

   public void addGeometry() 
   {
       // Get attachments and connect them
       VisibleObject actuatorDisplayer = act.getDisplayer();
       if (actuatorDisplayer == null) return;

       // A displayer is found, get geometry
       int geomSize = actuatorDisplayer.countGeometry();
       if (geomSize > 0){
          ArrayMusclePoint path=act.getCurrentPath();
          double defaultLocation[] = new double[]{0,0,0};
          for(int i=0; i<geomSize; i++) {
             // Add placeholder for the segment
             int idx = muscleSegmentsRep.addLocation(defaultLocation);
             segmentGlyphIds.add(new Integer(idx));
             
             // Add muscle point at position1 of segment, and if this is the last segment also at position2
             MusclePoint pt1 = path.get(i);
             if (MuscleWrapPoint.safeDownCast(pt1)!= null)
                pt1.setPickable(false);
             idx = musclePointsRep.addLocation(defaultLocation, path.get(i));
             musclePointsRep.setVectorDataAtLocation(idx,1,1,1);
             pointGlyphIds.add(new Integer(idx));

             if(i==geomSize-1) {
                MusclePoint pt2 = path.get(i+1);
                if (MuscleWrapPoint.safeDownCast(pt2)!= null)
                   pt2.setPickable(false);
                idx = musclePointsRep.addLocation(defaultLocation, path.get(i+1));
                musclePointsRep.setVectorDataAtLocation(idx,1,1,1);
                pointGlyphIds.add(new Integer(idx));
             }
          } // Attachments
       }
   }

   public void removeGeometry()
   {
      VisibleObject actuatorDisplayer = act.getDisplayer();
      if (actuatorDisplayer == null) return;
      // Turn the display of the actuator off so its geometry will be removed from the VTK objects
      actuatorDisplayer.getVisibleProperties().setDisplayPreference(DisplayPreference.None);
      updateGeometry(false);
   }

   public void updateGeometry(boolean callUpdateDisplayer) 
   {
      double[] axis = new double[]{0.0, 0.0, 0.0};
      double[] center = new double[]{0.0, 0.0, 0.0};
      // Get attachments and connect them
      if(callUpdateDisplayer) act.updateDisplayer();
      VisibleObject actuatorDisplayer = act.getDisplayer();
      if (actuatorDisplayer == null) return;

      boolean visible = false;
      DisplayPreference dp = actuatorDisplayer.getVisibleProperties().getDisplayPreference();
      if (dp != DisplayPreference.None)
         visible = true;

      // A displayer is found, get geometry
      int geomSize = actuatorDisplayer.countGeometry();
      if (visible == false)
         geomSize = 0;

      updateActuatorGlyphIds(geomSize);         

      if (geomSize > 0) {
         double[] position1 = new double[3];
         double[] position2 = new double[3];
         // Points are already in inertial frame
         for(int i=0; i<geomSize; i++) {
            Geometry geomEntry = actuatorDisplayer.getGeometry(i);
            LineGeometry geomLine = LineGeometry.dynamic_cast(geomEntry);
            geomLine.getPoints(position1, position2);
               
            for(int d=0; d <3; d++){
               axis[d]=position1[d]-position2[d];
               center[d] = (position1[d]+position2[d])/2.0;
            }
            // Create a cylinder connecting position1, position2
            double[] unitAxis = new double[]{axis[0], axis[1], axis[2]};
            double length = normalizeAndGetLength(axis);
            double[] xform = getCylinderTransform(axis, center) ;
            int idx = segmentGlyphIds.get(i).intValue();
            muscleSegmentsRep.setLocation(idx, center);
            muscleSegmentsRep.setTensorDataAtLocation(idx, 
                             xform[0], xform[4], xform[8],
                             length*xform[1], length*xform[5], length*xform[9],
                             xform[2], xform[6], xform[10]
                    );

            // Draw muscle point at position1 of segment, and if this is the last segment also at position2
            int pointIdx = pointGlyphIds.get(i).intValue();
            musclePointsRep.setLocation(pointIdx, position1);
            if(i==geomSize-1) {
                pointIdx = pointGlyphIds.get(i+1).intValue();
                musclePointsRep.setLocation(pointIdx, position2);
            }
         }
      }

      muscleSegmentsRep.setModified();
      musclePointsRep.setModified();
   }

   private void updateActuatorGlyphIds(int newNumSegments) 
   {
      int origNumSegments = segmentGlyphIds.size();
      if (newNumSegments>origNumSegments){   // Make extra segments (and points) and attach them 
         // We always want to maintain one more point than number of segments
         if(origNumSegments==0) {
            int pointIdx = musclePointsRep.addLocation(0.0, 0.0, 0.0); // always one more muscle point than number of segments
            musclePointsRep.setVectorDataAtLocation(pointIdx,1,1,1);
            pointGlyphIds.add(new Integer(pointIdx));
         }
         // Add required number of segments, and one point for each segment
         for(int i=origNumSegments; i<newNumSegments; i++) {
            int idx = muscleSegmentsRep.addLocation(0.0, 0.0, 0.0);
            segmentGlyphIds.add(new Integer(idx));
            int pointIdx = musclePointsRep.addLocation(0.0, 0.0, 0.0);
            musclePointsRep.setVectorDataAtLocation(pointIdx,1,1,1);
            pointGlyphIds.add(new Integer(pointIdx));
         }
         // Sanity check: number of points should be number of segments + 1
         assert(pointGlyphIds.size()==segmentGlyphIds.size()+1);
      }
      else if (origNumSegments>newNumSegments){ // remove unused segments
         for(int i=newNumSegments; i<origNumSegments; i++) {
            muscleSegmentsRep.remove(segmentGlyphIds.get(i).intValue());
            musclePointsRep.remove(pointGlyphIds.get(i+1).intValue()); // always one more muscle point than number of segments
         }
         segmentGlyphIds.setSize(newNumSegments);
         if(newNumSegments == 0) {
            musclePointsRep.remove(pointGlyphIds.get(0).intValue());
            pointGlyphIds.setSize(0);
         } else {
            pointGlyphIds.setSize(newNumSegments+1);
         }
      }
   }

    /**
     * Get the transform that takes a unit cylinder aligned with Y axis to a cylnder connecting 2 points
     */
    vtkMatrix4x4 retTransform = new vtkMatrix4x4();
    double[]     retTransformVector = new double[16];
    double[] newX = new double[3];
    double[] oldXCrossNewY = new double[3]; // NewZ
    double[] getCylinderTransform(double[] normalizedAxis, double[] origin) {
        //Assume normalizedAxis is already normalized
        //double length = normalizeAndGetLength(axis);
        
        // yaxis is the unit vector
        for (int i=0; i < 3; i++){
            retTransformVector[i*4+ 1]= normalizedAxis[i];
        }
        oldXCrossNewY[0] = 0.0;
        oldXCrossNewY[1] = -normalizedAxis[2];
        oldXCrossNewY[2] = normalizedAxis[1];
        
        normalizeAndGetLength(oldXCrossNewY);
        for (int i=0; i < 3; i++){
            retTransformVector[i*4+ 2]= oldXCrossNewY[i];
        }
        newX[0] = normalizedAxis[1]*oldXCrossNewY[2]-normalizedAxis[2]*oldXCrossNewY[1];
        newX[1] = normalizedAxis[2]*oldXCrossNewY[0]-normalizedAxis[0]*oldXCrossNewY[2];
        newX[2] = normalizedAxis[0]*oldXCrossNewY[1]-normalizedAxis[1]*oldXCrossNewY[0];
        normalizeAndGetLength(newX);
       for (int i=0; i < 3; i++){
          retTransformVector[i*4]= newX[i];
          retTransformVector[i*4+ 3]= origin[i];
         }
        for(int i=12; i<15;i++)
            retTransformVector[i]=0.0;
        retTransformVector[15]=1.0;
        //retTransform.DeepCopy(retTransformVector);
        return retTransformVector;
    }
    /**
     * Normalize a vector and return its length
     */
    private double normalizeAndGetLength(double[] vector3)
    {
        double length = Math.sqrt(vector3[0]*vector3[0]+
                                  vector3[1]*vector3[1]+
                                  vector3[2]*vector3[2]);
        // normalize
        for(int d=0; d <3; d++)
            vector3[d]=vector3[d]/length;
        return length;
    }
}
