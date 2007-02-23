/*
 * OpenSimvtkGlyphCloud.java
 *
 * Created on January 25, 2007, 9:39 AM
 *
 * Copyright (c) 2006, Stanford University and Ayman Habib. All rights reserved.
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

import vtk.vtkActor;
import vtk.vtkDataArray;
import vtk.vtkFloatArray;
import vtk.vtkGlyph3D;
import vtk.vtkPointData;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProperty;
import vtk.vtkSphereSource;

/**
 *
 * @author Ayman Habib. An object representing a cloud of visual objects used to display markers, muscle points 
 * efficiently.
 */
public class OpenSimvtkGlyphCloud {    // Assume same shape
    
    private vtkPoints           pointCloud = new vtkPoints(); // object centers
    private vtkPolyData         pointPolyData = new vtkPolyData();
    private vtkPolyData         shape=new vtkSphereSource().GetOutput();
    private vtkActor            actor = new vtkActor();
    private vtkPolyDataMapper   mapper = new vtkPolyDataMapper();
    private vtkGlyph3D          glyph= new vtkGlyph3D();
    private vtkFloatArray       lineNormals = new vtkFloatArray();
    private vtkFloatArray       vectorData = new vtkFloatArray();
    /**
    * Creates a new instance of OpenSimvtkGlyphCloud
    */
    public OpenSimvtkGlyphCloud() {
        lineNormals.SetNumberOfTuples(1);
        lineNormals.SetNumberOfComponents(3);
        pointPolyData.SetPoints(pointCloud);
        pointPolyData.GetPointData().SetNormals(lineNormals);
        vectorData.SetNumberOfTuples(1);
        vectorData.SetNumberOfComponents(3);
        pointPolyData.GetPointData().SetVectors(vectorData);
        glyph.GeneratePointIdsOn();
       
    }
    public int addLocation(double[] newPoint) {
        int id = pointCloud.InsertNextPoint(newPoint);
        lineNormals.InsertTuple3(id, 0., 0., 0.);
        vectorData.InsertTuple3(id, 0., 0., 0.);
        return id;
    }
    public int addLocation(double px, double py, double pz) {
        int id= pointCloud.InsertNextPoint(px, py, pz);
        lineNormals.InsertTuple3(id, 0., 0., 0.);
        vectorData.InsertTuple3(id, 0., 0., 0.);
        return id;
    }
    
    public void setShape(vtkPolyData rep) {
        shape = rep;
    }
    public void setDisplayProperties(vtkProperty prop) {
        actor.SetProperty(prop);
    }
    public void setColor(double[] color) {
        actor.GetProperty().SetColor(color);
    }
    public void setOpacity(double newOpacity) {
        actor.GetProperty().SetOpacity(newOpacity);
    }
    
    public vtkActor getVtkActor() {
        glyph.SetSource(shape);
        glyph.SetInput(pointPolyData);
        mapper.SetInput(glyph.GetOutput());
        actor.SetMapper(mapper);
        
        return actor;
    }
    
    public void setLocation(int index, double x, double y, double z) {
        pointCloud.SetPoint(index, x, y, z);
    }

    public void setLocation(int index, double[] point) {
        pointCloud.SetPoint(index, point[0], point[1], point[2]);
    }
    
    public void setNormalAtLocation(int index, double x, double y, double z) {
        vtkPointData t = pointPolyData.GetPointData();
        vtkDataArray u = t.GetNormals();
        u.SetTuple3(index, x, y, z);
    }
    
    public void setVectorDataAtLocation(int index, double x, double y, double z) {
        vtkPointData t = pointPolyData.GetPointData();
        vtkDataArray u = t.GetVectors();
        u.SetTuple3(index, x, y, z);
    }
    
    public void orientByNormal() {
        glyph.SetVectorModeToUseNormal(); 
    }
    
    public void colorByScalar() {
        glyph.SetColorModeToColorByScalar(); 
    }

    public void setScaleFactor(double d) {
        glyph.SetScaleFactor(d);
    }
    
    public void scaleByVector()
    {
        glyph.SetScaleModeToScaleByVector();
    }
    
   public void setModified() {
      pointPolyData.Modified();
   }

   void scaleByVectorComponents() {
      glyph.SetScaleModeToScaleByVectorComponents();
   }
   
   // This works as long as you've associated scaling with the vector channel
   void remove(int index) {
      setVectorDataAtLocation(index, 0., 0., 0.);
   }
}
