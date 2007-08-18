/*
 *
 * SelectedObject
 * Author(s): Eran Guendelman
 * Copyright (c) 2005-2007, Stanford University, Eran Guendelman
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view;

import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Model;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.view.pub.ViewDB;
import vtk.vtkProp3D;


/**
 *
 * @author Eran Guendelman
 *
 */
public class SelectedObject {
   public static final double defaultSelectedColor[] = {0.8, 0.8, 0.0};

   OpenSimObject object;

   public SelectedObject(OpenSimObject object) { 
      this.object = object; 
   }

   public OpenSimObject getOpenSimObject() {
      return object;
   }

   public String getStatusText() {
      return object.getType() + ":" + object.getName();
   }

   private Model getModel(MusclePoint mp) { return mp.getMuscle().getModel(); }
   private Model getModel(AbstractBody body) { return body.getDynamicsEngine().getModel(); }
   private Model getModel(AbstractMarker marker) { return marker.getBody().getDynamicsEngine().getModel(); }

   public Model getOwnerModel()
   {
      MusclePoint mp = MusclePoint.safeDownCast(object);
      if(mp != null) return getModel(mp);
      AbstractBody body = AbstractBody.safeDownCast(object);
      if(body != null) return getModel(body);
      AbstractMarker marker = AbstractMarker.safeDownCast(object);
      if(marker != null) return getModel(marker);
      return null;
   }

   public void markSelected(boolean highlight)
   {
      if (MusclePoint.safeDownCast(object) != null) {
         MusclePoint mp = MusclePoint.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(mp));
         OpenSimvtkGlyphCloud cloud = visuals.getMusclePointsRep();
         int id = cloud.getPointId(object);
         if(id>=0) { // just to be safe
            cloud.setSelected(id, highlight);
            AbstractMuscle m = mp.getMuscle();
            visuals.updateActuatorGeometry(m, false); //TODO: perhaps overkill for getting musclepoint to update?
         }
      } else if (AbstractMarker.safeDownCast(object) != null) {
         AbstractMarker marker = AbstractMarker.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(marker));
         OpenSimvtkGlyphCloud cloud = visuals.getMarkersRep();
         int id = cloud.getPointId(object);
         if(id>=0) { // just to be safe
            cloud.setSelected(id, highlight);
            cloud.setModified();
         }
      } else if (AbstractBody.safeDownCast(object) != null) {
         vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
         double unselectedColor[] = {1.0, 1.0, 1.0};
         if(highlight)
            ViewDB.getInstance().applyColor(defaultSelectedColor, asm);
         else
            ViewDB.getInstance().applyColor(unselectedColor, asm);
      }
   }

   private static double[] getGlyphPointBounds(OpenSimvtkGlyphCloud cloud, SingleModelVisuals visuals, OpenSimObject object) {
      double pointSize = 0.05;
      int id = cloud.getPointId(object);
      if(id<0) return null; // just to be safe
      double[] location = new double[3];
      cloud.getLocation(id, location);
      visuals.transformModelToWorldPoint(location); // Transform to world space
      return new double[]{location[0]-pointSize,location[0]+pointSize,
                          location[1]-pointSize,location[1]+pointSize,
                          location[2]-pointSize,location[2]+pointSize};
   }

   public double[] getBounds()
   {
      double[] bounds = null;
      if (MusclePoint.safeDownCast(object) != null) {
         MusclePoint mp = MusclePoint.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(mp));
         bounds = getGlyphPointBounds(visuals.getMusclePointsRep(), visuals, object);
      } else if (AbstractMarker.safeDownCast(object) != null) {
         AbstractMarker marker = AbstractMarker.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(marker));
         bounds = getGlyphPointBounds(visuals.getMarkersRep(), visuals, object);
      } else if (AbstractBody.safeDownCast(object) != null) {
         vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
         if(asm!=null) {
            bounds = asm.GetBounds();
            SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel((AbstractBody)object));
            if(bounds!=null && visuals!=null) visuals.transformModelToWorldBounds(bounds);
         }
      }
      return bounds;
   }
}
