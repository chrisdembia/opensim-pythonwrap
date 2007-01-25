/*
 *
 * MotionObjectsDB
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
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
package org.opensim.motionviewer;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;
import vtk.vtkActor;
import vtk.vtkArrowSource;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkSphereSource;

/**
 *
 * @author Ayman. Collection of built in motion objects with room for growth through 
 * registering new object names, types.
 */
public class MotionObjectsDB {
   
   /** Creates a new instance of MotionObjectsDB */
   static MotionObjectsDB instance;
   // Map model to an ArrayList of Motions linked with it
   static Hashtable<String, vtkPolyData> motionObjectsMap =
           new Hashtable<String, vtkPolyData>(10);
   
   /** Creates a new instance of MotionsDB */
   private MotionObjectsDB() {
      // default motion objects
      // ball
      motionObjectsMap.put("ball", createBall());
      // marker
      motionObjectsMap.put("marker", createMarker());
      // force
      motionObjectsMap.put("force", createArrow());
      /*
      motionObjectsMap.put("torque", new vtkSphereSource());
      motionObjectsMap.put("arrow", new vtkSphereSource());
      motionObjectsMap.put("body_com", new vtkSphereSource());
      motionObjectsMap.put("com", new vtkSphereSource());
       **/
   }
   
   public static synchronized MotionObjectsDB getInstance() {
      if (instance == null) {
         instance = new MotionObjectsDB();
         
      }
      return instance;
   }

   String[] getAvailableNames() {
      Set<String> keys=motionObjectsMap.keySet();
      String[] names = new String[keys.size()];
      Iterator<String> keyIterator = keys.iterator();
      int i=0;
      while(keyIterator.hasNext())
         names[i++]=keyIterator.next();
      
      return names;
   }
   
   void addNewMotionObject(String newObjectName, vtkPolyData newObjectRep) {
      motionObjectsMap.put(newObjectName, newObjectRep);
   }

   private vtkPolyData createBall() {
      vtkSphereSource ball = new vtkSphereSource();
      ball.SetRadius(1.0);
      ball.SetCenter(0., 0., 0.);
      return ball.GetOutput();
   }

   private vtkPolyData createMarker() {
      vtkSphereSource marker=new vtkSphereSource();
      marker.SetRadius(.01);
      marker.SetCenter(0., 0., 0.);
      return marker.GetOutput();
   }

   private vtkPolyData createArrow() {
      vtkArrowSource force=new vtkArrowSource();
      force.SetShaftRadius(0.02);
      force.SetTipLength(0.1);
      return force.GetOutput();
   }

    vtkPolyData getShape(String shapeName) {
        return motionObjectsMap.get(shapeName);
    }
   
}
