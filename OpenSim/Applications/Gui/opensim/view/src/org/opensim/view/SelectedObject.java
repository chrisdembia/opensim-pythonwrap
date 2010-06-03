/*
 *
 * SelectedObject
 * Author(s): Eran Guendelman
 * Copyright (c)  2005-2007, Stanford University, Eran Guendelman
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
package org.opensim.view;

import org.opensim.modeling.WrapObject;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Model;
import org.opensim.modeling.Body;
import org.opensim.modeling.Marker;
import org.opensim.modeling.Muscle;
import org.opensim.modeling.OpenSimContext;
import org.opensim.modeling.PathPoint;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;
import vtk.vtkActor;
import vtk.vtkCaptionActor2D;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;


/**
 *
 * @author Eran Guendelman
 *
 */
public class SelectedObject implements Selectable {
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

   private Model getModel(PathPoint mp) { return mp.getBody().getModel(); }
   private Model getModel(Body body) { return body.getModel(); }
   private Model getModel(WrapObject wrapObj) { return getModel(wrapObj.getBody()); }
   private Model getModel(Marker marker) { return marker.getBody().getModel(); }

   public Model getOwnerModel()
   {
      PathPoint mp = PathPoint.safeDownCast(object);
      if(mp != null) return getModel(mp);
      Body body = Body.safeDownCast(object);
      if(body != null) return getModel(body);
      Marker marker = Marker.safeDownCast(object);
      if(marker != null) return getModel(marker);
      WrapObject wrapObj = WrapObject.safeDownCast(object);
      if(wrapObj != null) return getModel(wrapObj.getBody());
      
      return null;
   }

   public void markSelected(boolean highlight)
   {
      if (PathPoint.safeDownCast(object) != null) {
         PathPoint mp = PathPoint.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(mp));
         OpenSimvtkGlyphCloud cloud = visuals.getMusclePointsRep();
         int id = cloud.getPointId(object);
         if(id>=0) { // just to be safe
            cloud.setSelected(id, highlight);
            Muscle m = Muscle.safeDownCast(mp.getPath().getOwner());
            visuals.updateActuatorGeometry(m, false); //TODO: perhaps overkill for getting musclepoint to update?
         }
      } else if (Marker.safeDownCast(object) != null) {
         Marker marker = Marker.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(marker));
         OpenSimvtkGlyphCloud cloud = visuals.getMarkersRep();
         int id = cloud.getPointId(object);
         if(id>=0) { // just to be safe
            cloud.setSelected(id, highlight);
            cloud.setModified();
         }
      } else if (Body.safeDownCast(object) != null) {
         BodyRep asm = (BodyRep) ViewDB.getInstance().getVtkRepForObject(object);
         double unselectedColor[] = {1.0, 1.0, 1.0};
         if(highlight){
             // Save existing color with the body for later restoration
             Body b=(Body)object;
             vtkProp3DCollection props =asm.GetParts();
             double[] currentColor = ((vtkActor)props.GetLastProp3D()).GetProperty().GetColor();
             b.getDisplayer().getVisibleProperties().setColor(currentColor);
             ViewDB.getInstance().applyColor(defaultSelectedColor, asm);
         }
         else{
            Body b=(Body)object;
            double[] actualColor = new double[3];
            b.getDisplayer().getVisibleProperties().getColor(actualColor);
            ViewDB.getInstance().applyColor(actualColor, asm);
         }
      }
   }

   public static double[] getGlyphPointBounds(OpenSimvtkGlyphCloud cloud, SingleModelVisuals visuals, OpenSimObject object) {
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
      if (PathPoint.safeDownCast(object) != null) {
         PathPoint mp = PathPoint.safeDownCast(object);
         Model dModel = getModel(mp);
         OpenSimContext context = OpenSimDB.getInstance().getContext(dModel);
         if (!(context.isActivePathPoint(mp))) return null;
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(dModel);
         // If muscle is now hidden return
         int displayStatus = ViewDB.getInstance().getDisplayStatus(mp.getPath().getOwner());
         if (displayStatus==0) return null;
         bounds = getGlyphPointBounds(visuals.getMusclePointsRep(), visuals, object);
      } else if (Marker.safeDownCast(object) != null) {
         Marker marker = Marker.safeDownCast(object);
         SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(marker));
         // Check if not visible, return
         int displayStatus = ViewDB.getInstance().getDisplayStatus(marker);
         if (displayStatus==0) return null;
         bounds = getGlyphPointBounds(visuals.getMarkersRep(), visuals, object);
         
      } else { // if (AbstractBody.safeDownCast(object) != null)
          // Check if object is visible 
         int displayStatus = ViewDB.getInstance().getDisplayStatus(object);
         if (displayStatus==0) return null;
         vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
         if(asm!=null) {
            bounds = asm.GetBounds();
            Body dBody = null;
            if (Body.safeDownCast(object)!=null )
                dBody = Body.safeDownCast(object);
            else if (WrapObject.safeDownCast(object)!=null)
                dBody = (WrapObject.safeDownCast(object)).getBody();
            if (dBody != null){
                SingleModelVisuals visuals = ViewDB.getInstance().getModelVisuals(getModel(dBody));
            if(bounds!=null && visuals!=null) visuals.transformModelToWorldBounds(bounds);
         }
      }
      }
      return bounds;
   }

    public void updateAnchor(vtkCaptionActor2D caption) {
             double[] bounds=getBounds();
             if (bounds == null){   // object currently invisible
                 caption.SetVisibility(0);
                 return;
}
             else
                 caption.SetVisibility(1);
             caption.SetAttachmentPoint(new double[]{
                 (bounds[0]+bounds[1])/2.0,
                 (bounds[2]+bounds[3])/2.0,
                 (bounds[4]+bounds[5])/2.0,
             });
    }
}
