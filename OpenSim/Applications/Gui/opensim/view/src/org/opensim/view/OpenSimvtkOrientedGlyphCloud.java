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
import vtk.vtkCylinderSource;
import vtk.vtkDataArray;
import vtk.vtkFloatArray;
import vtk.vtkPointData;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProperty;
import vtk.vtkTensorGlyph;

/**
 *
 * @author Ayman Habib. An object representing a cloud of visual objects used to display markers, muscle points 
 * efficiently.
 */
public class OpenSimvtkOrientedGlyphCloud {    // Assume same shape
    
    private vtkPoints           pointCloud = new vtkPoints(); // object centers
    private vtkPolyData         pointPolyData = new vtkPolyData();
    private vtkPolyData         shape=new vtkCylinderSource().GetOutput();
    private vtkActor            actor = new vtkActor();
    private vtkPolyDataMapper   mapper = new vtkPolyDataMapper();
    private vtkTensorGlyph      glyph= new vtkTensorGlyph();
    private vtkFloatArray       tensorData = new vtkFloatArray();
    
    /**
    * Creates a new instance of OpenSimvtkGlyphCloud
    */
    public OpenSimvtkOrientedGlyphCloud() {
        tensorData.SetNumberOfTuples(1);
        tensorData.SetNumberOfComponents(9);
        pointPolyData.SetPoints(pointCloud);
        pointPolyData.GetPointData().SetTensors(tensorData);
        glyph.ExtractEigenvaluesOff();
        glyph.ThreeGlyphsOff();
        glyph.SymmetricOff();
    }
    public int addLocation(double[] newPoint) {
        int id = pointCloud.InsertNextPoint(newPoint);
        tensorData.InsertTuple9(id, 1., 0., 0., 0., 1., 0., 0., 0., 1.);
        return id;
    }
    public int addLocation(double px, double py, double pz) {
        int id= pointCloud.InsertNextPoint(px, py, pz);
        tensorData.InsertTuple9(id, 1., 0., 0., 0., 1., 0., 0., 0., 1.);
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
    
    public void setPoint(int index, double x, double y, double z) {
        
        pointCloud.SetPoint(index, x, y, z);
    }
    
    public void setTensorDataAtPoint(int index, double xx, double xy, double xz,
            double yx, double yy, double yz,
            double zx, double zy, double zz) {
        vtkPointData t = pointPolyData.GetPointData();
        t.GetTensors().SetTuple9(index, xx, xy, xz, yx, yy, yz, zx, zy, zz);
        //t.GetTensors().SetTuple9(index, xx, yx, zx, xy, yy, zy, zx, zy, zz);
    }

   public vtkFloatArray getTensorData() {
      return tensorData;
   }

   public void setTensorData(vtkFloatArray tensorData) {
      this.tensorData = tensorData;
   }

   void setModified() {
      mapper.Modified();
   }
        
}
