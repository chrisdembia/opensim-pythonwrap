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
import org.opensim.modeling.AbstractMuscle;
import org.opensim.view.pub.ViewDB;
import vtk.vtkProp3D;


/**
 *
 * @author Eran Guendelman
 *
 */
public class SelectedObject {
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

   public Model getOwnerModel()
   {
      MusclePoint mp = MusclePoint.safeDownCast(object);
      if(mp != null) return mp.getMuscle().getModel();
      AbstractBody body = AbstractBody.safeDownCast(object);
      if(body != null) return body.getDynamicsEngine().getModel();
      return null;
   }

   public void markSelected(boolean highlight)
   {
      MusclePoint mp = MusclePoint.safeDownCast(object);
      if (mp != null) {
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(mp.getMuscle().getModel());
         OpenSimvtkGlyphCloud cloud = visuals.getMusclePointsRep();
         if (highlight)
            cloud.setScalarDataAtLocation(cloud.getPointId(object), 0.28); // yellow
else
            cloud.setScalarDataAtLocation(cloud.getPointId(object), 0.0); // red
         AbstractMuscle m = mp.getMuscle();
         visuals.updateActuatorGeometry(m, false); //TODO: perhaps overkill for getting musclepoint to update?
      } else { // should check for body here
         double colorComponents[] = {0.8, 0.8, 0.0};
         if (!highlight)
            colorComponents[0] = colorComponents[1] = colorComponents[2] = 1.0;
         vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
         ViewDB.getInstance().applyColor(colorComponents, asm);
      }
   }
}
