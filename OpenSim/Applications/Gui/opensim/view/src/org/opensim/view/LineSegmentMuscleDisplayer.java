package org.opensim.view;

import java.util.Hashtable;
import java.util.Vector;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ArrayMusclePoint;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.LineGeometry;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.MusclePointSet;
import org.opensim.modeling.MuscleWrapPoint;
import org.opensim.modeling.VisibleObject;
import org.opensim.modeling.VisibleProperties.DisplayPreference;
import vtk.vtkMatrix4x4;

public class LineSegmentMuscleDisplayer {

   private AbstractMuscle act;

   private OpenSimvtkGlyphCloud musclePointsRep;
   private OpenSimvtkOrientedGlyphCloud muscleSegmentsRep;

   Hashtable<MusclePoint,Integer> mapMusclePointToGlyphId = new Hashtable<MusclePoint,Integer>(10);
   Vector<Integer> musclePointGlyphIds = new Vector<Integer>(10);
   Vector<Integer> muscleSegmentGlyphIds = new Vector<Integer>(10);

   public LineSegmentMuscleDisplayer(AbstractMuscle act, OpenSimvtkGlyphCloud musclePointsRep, OpenSimvtkOrientedGlyphCloud muscleSegmentsRep)
   {
      this.act = act;
      this.musclePointsRep = musclePointsRep;
      this.muscleSegmentsRep = muscleSegmentsRep;
   }

   private void freeGlyphIds()
   {
      //System.out.println("LineSegmentMuscleDisplay ("+act.getName()+"): freeGlyphIds");
      for(int i=0; i<musclePointGlyphIds.size(); i++) musclePointsRep.remove(musclePointGlyphIds.get(i));
      musclePointGlyphIds.clear();
      for(int i=0; i<muscleSegmentGlyphIds.size(); i++) muscleSegmentsRep.remove(muscleSegmentGlyphIds.get(i));
      muscleSegmentGlyphIds.clear();
      mapMusclePointToGlyphId.clear();
   }

   // TODO: deal with remapping selections?
   private void updateGlyphIds()
   {
      int oldPointsSize = musclePointGlyphIds.size();
      int oldSegmentsSize = muscleSegmentGlyphIds.size();

      int newPointsSize;
      int newSegmentsSize;

      VisibleObject actuatorDisplayer = act.getDisplayer();
      if (actuatorDisplayer == null) {
         newPointsSize = 0;
         newSegmentsSize = 0;
      } else {
         newPointsSize = act.getAttachmentSet().getSize();
         newSegmentsSize = actuatorDisplayer.countGeometry();
      }

      // allocate glyph id's
      if(newPointsSize > oldPointsSize) {
         //System.out.println("LineSegmentMuscleDisplay ("+act.getName()+"): updateGlyphIds - points "+oldPointsSize+"->"+newPointsSize);

         MusclePointSet as = act.getAttachmentSet();
         // for muscle points, we assume the visible points are fixed attachments or moving via points, and we assume
         // the number of these doesn't change between typical updates... so we allocate the exact number of requested points
         musclePointGlyphIds.setSize(newPointsSize);
         mapMusclePointToGlyphId.clear();
         for(int i=oldPointsSize; i<newPointsSize; i++) {
            int index = musclePointsRep.addLocation();
            musclePointGlyphIds.set(i, index);
            musclePointsRep.setVectorDataAtLocation(index,1,1,1);
         }
         for(int i=0; i<newPointsSize; i++) {
            musclePointsRep.setObjectAtPointId(musclePointGlyphIds.get(i), as.get(i));
            mapMusclePointToGlyphId.put(as.get(i), musclePointGlyphIds.get(i));
         }
      }

      if(newSegmentsSize > oldSegmentsSize) {
         //System.out.println("LineSegmentMuscleDisplay ("+act.getName()+"): updateGlyphIds - segments "+oldSegmentsSize+"->"+newSegmentsSize);

         // for segments, due to wrapping, the number may change frequently, so we overallocate the glyph id's to
         // avoid having to frequently reset the glyphs
         int capacity = (oldSegmentsSize > 0) ? oldSegmentsSize : 1;
         while(capacity < newSegmentsSize) capacity *= 2;
         newSegmentsSize = capacity;
         muscleSegmentGlyphIds.setSize(newSegmentsSize);
         for(int i=oldSegmentsSize; i<newSegmentsSize; i++) {
            int index = muscleSegmentsRep.addLocation();
            muscleSegmentGlyphIds.set(i, index);
         }
      }
   }

   public void addGeometry()
   {
      act.updateDisplayer();
      updateGlyphIds();
      updateGeometry(false);
   }

   public void updateGeometry(boolean callUpdateDisplayer)
   {
      // Get attachments and connect them
      if(callUpdateDisplayer) act.updateDisplayer();
      VisibleObject actuatorDisplayer = act.getDisplayer();
      if (actuatorDisplayer == null) return;

      DisplayPreference dp = actuatorDisplayer.getVisibleProperties().getDisplayPreference();
      if (dp == DisplayPreference.None) return; // TODO: is this the right thing to do?

      // Account for possible increase in number of muscle segments
      updateGlyphIds();

      // Set all glyphs to hidden to begin with
      for(int i=0; i<musclePointGlyphIds.size(); i++) musclePointsRep.hide(musclePointGlyphIds.get(i));
      for(int i=0; i<muscleSegmentGlyphIds.size(); i++) muscleSegmentsRep.hide(muscleSegmentGlyphIds.get(i));

      // A displayer is found, get geometry
      int geomSize = actuatorDisplayer.countGeometry();
      if (geomSize > 0) {
         double[] axis = new double[]{0.0, 0.0, 0.0};
         double[] center = new double[]{0.0, 0.0, 0.0};
         double[] position1 = new double[3];
         double[] position2 = new double[3];

         ArrayMusclePoint path=act.getCurrentPath();

         // Points are already in inertial frame
         for(int i=0; i<geomSize; i++) {
            Geometry geomEntry = actuatorDisplayer.getGeometry(i);
            LineGeometry geomLine = LineGeometry.dynamic_cast(geomEntry);
            geomLine.getPoints(position1, position2);
           
            // 
            // Draw cylinder for muscle segment
            //
            for(int d=0; d <3; d++){
               axis[d] = position1[d]-position2[d];
               center[d] = (position1[d]+position2[d])/2.0;
            }
            double length = normalizeAndGetLength(axis);
            double[] xform = getCylinderTransform(axis, center);
            int idx = muscleSegmentGlyphIds.get(i).intValue(); // we should have enough muscleSegmentGlyphIds allocated at this point sinec we had called updateGlyphIds()
            muscleSegmentsRep.show(idx);
            muscleSegmentsRep.setLocation(idx, center);
            muscleSegmentsRep.setTensorDataAtLocation(idx, 
                             xform[0], xform[4], xform[8],
                             length*xform[1], length*xform[5], length*xform[9],
                             xform[2], xform[6], xform[10]);

            //
            // Draw non-wrap muscle points
            //
            MusclePoint pt1 = path.get(i);
            if(MuscleWrapPoint.safeDownCast(pt1)==null) {
               Integer pointIdx = mapMusclePointToGlyphId.get(pt1);
               if(pointIdx!=null) { // shouldn't be null!  but what should we do if it is??
                  idx = pointIdx.intValue();
                  musclePointsRep.show(idx);
                  musclePointsRep.setLocation(idx, position1);
               }
            }
            if(i==geomSize-1) {
               // Draw last point if it's non-wrap
               MusclePoint pt2 = path.get(i+1);
               if(MuscleWrapPoint.safeDownCast(pt2)==null) {
                  Integer pointIdx = mapMusclePointToGlyphId.get(pt2);
                  if(pointIdx!=null) { // shouldn't be null!  but what should we do if it is??
                     idx = pointIdx.intValue();
                     musclePointsRep.show(idx);
                     musclePointsRep.setLocation(idx, position2);
                  }
               }
            }
         }
      }

      // We'll let SingleModelVisuals call setModified() as necessary so we avoid calling it repeatedly when unnecessary
      //muscleSegmentsRep.setModified();
      //musclePointsRep.setModified();
   }

   public void removeGeometry()
   {
      freeGlyphIds();
      VisibleObject actuatorDisplayer = act.getDisplayer();
      if(actuatorDisplayer!=null) actuatorDisplayer.getVisibleProperties().setDisplayPreference(DisplayPreference.None);
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
