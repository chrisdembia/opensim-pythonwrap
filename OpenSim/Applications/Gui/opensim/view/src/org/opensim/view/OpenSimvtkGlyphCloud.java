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
import java.util.Stack;
import org.opensim.modeling.OpenSimObject;
import vtk.vtkActor;
import vtk.vtkDataArray;
import vtk.vtkFloatArray;
import vtk.vtkGlyph3D;
import vtk.vtkIdList;
import vtk.vtkIntArray;
import vtk.vtkLookupTable;
import vtk.vtkPoints;
import vtk.vtkPolyData;
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
    private vtkActor            actor = new vtkActor();
    private vtkPolyDataMapper   mapper = new vtkPolyDataMapper();
    private vtkGlyph3D          glyph= new vtkGlyph3D();
    private vtkFloatArray       lineNormals = null;
    // vectorData is used primarily to "hide" objects, by setting the data to 0,0,0
    // a muscle point is hidden otherwise 1,1,1 except for forces that are really scaled uniformely by mag
    private vtkFloatArray       vectorData = new vtkFloatArray();
    private vtkIntArray         scalarData = null;
    private vtkLookupTable      lookupTable = null;
    private HashMap<OpenSimObject,Integer> mapObjectIdsToPointIds = new HashMap<OpenSimObject,Integer>(100);
    private HashMap<Integer,OpenSimObject> mapPointIdsToObjectIds = new HashMap<Integer,OpenSimObject>(100);

    private Stack<Integer> freeList = new Stack<Integer>();
    
    /**
    * Creates a new instance of OpenSimvtkGlyphCloud.
    * if createScalars is true then obbjects are colored based on scalarValues
    * otherwise it uses Vector magnitude.
    */
    public OpenSimvtkGlyphCloud(boolean createNormals) {
        pointPolyData.SetPoints(pointCloud);
        // Always use vector data because that's how we scale things to make them disappear
        vectorData.SetNumberOfTuples(1);
        vectorData.SetNumberOfComponents(3);
        pointPolyData.GetPointData().SetVectors(vectorData);
        if (createNormals) {
           lineNormals = new vtkFloatArray();
           lineNormals.SetNumberOfTuples(1);
           lineNormals.SetNumberOfComponents(3);
           pointPolyData.GetPointData().SetNormals(lineNormals);
        }
        glyph.GeneratePointIdsOn();
        glyph.SetScaleModeToDataScalingOff(); // So hide/show behavior is disabled by default
    }
    
    public void setShape(vtkPolyData rep) {
        shape = rep;
    }
    public void setDisplayProperties(vtkProperty prop) {
        actor.SetProperty(prop);
    }

   // Single color (doesn't support showing selected/unselected)
   public void setColor(double[] color) {
      actor.GetProperty().SetColor(color);
   }

   // Set both unselected and selected colors
   // Scalar 0 indicates unselected, scalar 1 indicates selected
   public void setColors(double[] unselectedColor, double[] selectedColor) {
      scalarData = new vtkIntArray();
      scalarData.SetNumberOfTuples(1);
      scalarData.SetNumberOfComponents(1);
      pointPolyData.GetPointData().SetScalars(scalarData);
      glyph.SetColorModeToColorByScalar();
      lookupTable = new vtkLookupTable();
      lookupTable.SetNumberOfTableValues(2);
      if(unselectedColor.length==3) lookupTable.SetTableValue(0, unselectedColor[0], unselectedColor[1], unselectedColor[2], 1.0);
      else lookupTable.SetTableValue(0, unselectedColor);
      if(selectedColor.length==3) lookupTable.SetTableValue(1, selectedColor[0], selectedColor[1], selectedColor[2], 1.0);
      else lookupTable.SetTableValue(1, selectedColor);
      mapper.SetLookupTable(lookupTable);
   }

   public void setSelected(int index, boolean selected) {
      if(scalarData!=null && lookupTable!=null) scalarData.SetTuple1(index, selected ? 1 : 0);
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
        if (lineNormals != null) lineNormals.SetTuple3(index, x, y, z);
    }
    
    public void setVectorDataAtLocation(int index, double x, double y, double z) {
        vectorData.SetTuple3(index, x, y, z);
    }
   
    // Used e.g. for the ground reaction forces, it uses the normals to orient the GRF "arrow", and the normal magnitude is used to scale the GRF "arrow"
    public void orientByNormalAndScaleByVector() {
      glyph.SetVectorModeToUseNormal(); 
      glyph.SetScaleModeToScaleByVector(); // scales by vector *magnitude*
    }

    public void setScaleFactor(double d) {
        glyph.SetScaleFactor(d);
    }
   
   public void setModified() {
      pointPolyData.Modified();
   }

   // Used to enable hide/show behavior
   public void scaleByVectorComponents() {
      glyph.SetScaleModeToScaleByVectorComponents();
   }

   /////////////////////////////////////////////////////////////////////////////
   // Add/Remove locations
   /////////////////////////////////////////////////////////////////////////////

   // A point associated with an object
   public int addLocation(OpenSimObject obj) {
      int idx = addLocation();
      mapObjectIdsToPointIds.put(obj, idx);
      mapPointIdsToObjectIds.put(idx, obj);
      return idx;
   }

   public int addLocation() {
      return addLocation(0.,0.,0.);
   }

   public int addLocation(double[] newPoint) {
      return addLocation(newPoint[0],newPoint[1],newPoint[2]);
   }

   public int addLocation(double px, double py, double pz) {
      int idx;
      if(!freeList.empty()) { // reuse existing index that was removed earlier
         idx = freeList.pop().intValue();
         show(idx);
      } else {
         idx = pointCloud.InsertNextPoint(px, py, pz);
         vectorData.InsertTuple3(idx, 1., 1., 1.);
         if (lineNormals != null) lineNormals.InsertTuple3(idx, 0., 0., 0.);
         if (scalarData != null) scalarData.InsertTuple1(idx, 0);
      }
      return idx;
   }

   // This works as long as you've associated scaling with the vector channel
   void remove(int index) {
      freeList.push(index);
      hide(index);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Show/Hide points
   /////////////////////////////////////////////////////////////////////////////
   
   public void show(int index) {
      setVectorDataAtLocation(index, 1., 1., 1.);
   }

   public void hide(int index) {
      setVectorDataAtLocation(index, 0., 0., 0.);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Mapping between picked id's, point id's, and objects
   /////////////////////////////////////////////////////////////////////////////

    public OpenSimObject getPickedObject(int pickedId) {
       glyph.GetOutput().BuildCells();
       vtkIdList ids = new vtkIdList();
       glyph.GetOutput().GetCellPoints(pickedId, ids);
        vtkDataArray inputIds = 
            glyph.GetOutput().GetPointData().GetArray("InputPointIds");
        int inputId = (int)inputIds.GetTuple1(ids.GetId(0));
        System.out.println("GlyphCloud: pickedId="+pickedId+"  inputId="+inputId+"  ids="+ids);
        for(int i=0;i<(int)ids.GetNumberOfIds();i++) {
           System.out.println("["+i+"] = "+(int)ids.GetId(i)+" --> "+(int)inputIds.GetTuple1(ids.GetId(i)));
        }
        return mapPointIdsToObjectIds.get(inputId);
    }
 
    public int getPointId(OpenSimObject object) {
       return mapObjectIdsToPointIds.get(object);
   }

   public void setObjectAtPointId(int id, OpenSimObject obj) {
      // To be safe, get rid of any stale mappings
      Integer oldId = mapObjectIdsToPointIds.get(obj);
      if(oldId!=null && oldId!=id) mapPointIdsToObjectIds.put(oldId,null);
      mapObjectIdsToPointIds.put(obj,id);

      OpenSimObject oldObj = mapPointIdsToObjectIds.get(id);
      if(oldObj!=null && oldObj!=obj) mapObjectIdsToPointIds.put(oldObj,null);
      mapPointIdsToObjectIds.put(id,obj);
   }
}
