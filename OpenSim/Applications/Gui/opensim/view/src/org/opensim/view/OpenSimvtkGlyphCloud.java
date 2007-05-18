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

import java.util.HashMap;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.OpenSimObject;
import vtk.vtkActor;
import vtk.vtkAlgorithm;
import vtk.vtkCubeSource;
import vtk.vtkDataArray;
import vtk.vtkFloatArray;
import vtk.vtkGlyph3D;
import vtk.vtkIdList;
import vtk.vtkPointData;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataAlgorithm;
import vtk.vtkPolyDataMapper;
import vtk.vtkProperty;
import vtk.vtkSphereSource;

/**
 *
 * @author Ayman Habib. An object representing a cloud of visual objects used to display markers, muscle points 
 * efficiently.
 * For markers and muscle points
 */
public class OpenSimvtkGlyphCloud {    // Assume same shape
    
    private vtkPoints           pointCloud = new vtkPoints(); // object centers
    private vtkPolyData         pointPolyData = new vtkPolyData();
    private vtkPolyData         shape=new vtkSphereSource().GetOutput();
    private vtkPolyData         shape2=new vtkCubeSource().GetOutput();
    private vtkActor            actor = new vtkActor();
    private vtkPolyDataMapper   mapper = new vtkPolyDataMapper();
    private vtkGlyph3D          glyph= new vtkGlyph3D();
    private vtkFloatArray       lineNormals = new vtkFloatArray();
    // vectorData is used primarily to "hide" objects, by setting the data to 0,0,0
    // a muscle point is hidden otherwise 1,1,1 except for forces that are really scaled uniformely by mag
    private vtkFloatArray       vectorData = new vtkFloatArray();
    private vtkFloatArray       scalarData = null;
    private HashMap<OpenSimObject,Integer> mapObjectIdsToPointIds = new HashMap<OpenSimObject,Integer>(100);
    private HashMap<Integer,OpenSimObject> mapPointIdsToObjectIds = new HashMap<Integer,OpenSimObject>(100);
    
    /**
    * Creates a new instance of OpenSimvtkGlyphCloud.
    * defaults to not create Scalars
    */
    public OpenSimvtkGlyphCloud() {
       this(false);
    }
    
    /**
    * Creates a new instance of OpenSimvtkGlyphCloud.
    * if createScalars is true then obbjects are colored based on scalarValues
    * otherwise it uses Vector magnitude.
    */
    public OpenSimvtkGlyphCloud(boolean createScalars) {
        lineNormals.SetNumberOfTuples(1);
        lineNormals.SetNumberOfComponents(3);
        pointPolyData.SetPoints(pointCloud);
        pointPolyData.GetPointData().SetNormals(lineNormals);
        vectorData.SetNumberOfTuples(1);
        vectorData.SetNumberOfComponents(3);
        if (createScalars == true) {
           scalarData = new vtkFloatArray();
           scalarData.SetNumberOfTuples(1);
           scalarData.SetNumberOfComponents(1);
           pointPolyData.GetPointData().SetScalars(scalarData);
        }
        pointPolyData.GetPointData().SetVectors(vectorData);
        glyph.GeneratePointIdsOn();
    }
    public int addLocation(double[] newPoint) {
        int id = pointCloud.InsertNextPoint(newPoint);
        lineNormals.InsertTuple3(id, 0., 0., 0.);
        vectorData.InsertTuple3(id, 0., 0., 0.);
        if (scalarData != null)
           scalarData.InsertTuple1(id, 0.0);
        return id;
    }
    public int addLocation(double px, double py, double pz) {
        int id= pointCloud.InsertNextPoint(px, py, pz);
        lineNormals.InsertTuple3(id, 0., 0., 0.);
        vectorData.InsertTuple3(id, 0., 0., 0.);
        if (scalarData != null)
           scalarData.InsertTuple1(id, 0.0);
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
        
       //glyph.SetSource(1, shape);
       //glyph.SetInput(1, pointPolyData);
       //glyph.AddInput(2, pointPolyData);
       //glyph.SetSource(2, shape2);
       //mapper.SetInput(glyph.GetOutput());
       //actor.SetMapper(mapper);
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
    
    public void setScalarDataAtLocation(int index, double x) {
       if (scalarData != null) {
          vtkPointData t = pointPolyData.GetPointData();
          vtkDataArray u = t.GetScalars();
          u.SetTuple1(index, x);
       }
    }
    
    public void orientByNormal() {
        glyph.SetVectorModeToUseNormal(); 
    }
    
    public void colorByScalar() {
        glyph.SetColorModeToColorByScalar(); 
    }

    public void colorByVector() {
        glyph.SetColorModeToColorByVector(); 
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

    int addLocation(double[] gPos, OpenSimObject obj) {
        int idx = addLocation(gPos);

        mapObjectIdsToPointIds.put(obj, idx);
        mapPointIdsToObjectIds.put(idx, obj);
        //System.out.println("Glyph point id="+idx+" object="+obj.getName());
        return idx;
    }
    
    public OpenSimObject getPickedObject(int pickedId) {
       vtkIdList ids = new vtkIdList();
       glyph.GetOutput().GetCellPoints(pickedId, ids);
        vtkDataArray inputIds = 
            glyph.GetOutput().GetPointData().GetArray("InputPointIds");
        int inputId = (int)inputIds.GetTuple1(ids.GetId(0));
        return mapPointIdsToObjectIds.get(inputId);
    }
 
    public int getPointId(OpenSimObject object) {
       return mapObjectIdsToPointIds.get(object);
}
}
