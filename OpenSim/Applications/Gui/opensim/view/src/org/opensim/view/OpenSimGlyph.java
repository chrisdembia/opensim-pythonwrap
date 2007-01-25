/*
 * OpenSimGlyph.java
 *
 * Created on January 12, 2007, 5:48 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import vtk.vtkActor;
import vtk.vtkDataArray;
import vtk.vtkFloatArray;
import vtk.vtkGlyph3D;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;

public class OpenSimGlyph {
    // Glyph positions
    vtkPolyData lineData = new vtkPolyData();
    vtkPoints linePoints = new vtkPoints(); // bond centers
    vtkFloatArray lineNormals = new vtkFloatArray(); // bond directions/lengths
    vtkFloatArray colorScalars = new vtkFloatArray();
   
    private vtkGlyph3D lineGlyph = new vtkGlyph3D();

    private vtkActor actor = new vtkActor();
    private vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    private List<String> shapeNames = new ArrayList<String>(5);
    private List<vtkPolyData> shapes = new ArrayList<vtkPolyData>(5);
    
    OpenSimGlyph() {
        
        colorScalars.SetNumberOfComponents(1);
        colorScalars.SetName("colors");

        // glyphColors.setData(lineData);        
        lineNormals.SetNumberOfComponents(3);
        lineData.SetPoints(linePoints);
        lineData.GetPointData().SetNormals(lineNormals);

        lineData.GetPointData().SetScalars(colorScalars);        
        
        lineGlyph.SetInput(lineData);

        mapper.SetInput(lineGlyph.GetOutput());
        
        actor.SetMapper(mapper);

    }
    // Empty arrays/lists and restart
    void flushShapes()
    {
        shapeNames.clear();
        shapes.clear();
    }
    // Override these functions to use TensorGlyph rather than vtkGlyph3D
    public int addGlyphSource(String name, vtkPolyData data) {
        lineGlyph.SetSource(data);
        // growPointsFilter.SetInput(data);
        return 0;
    }
    public void scaleByNormal() {
        lineGlyph.SetScaleModeToScaleByVector(); // Take length from normal
        lineGlyph.SetVectorModeToUseNormal(); // Take direction from normal

        //highlightGlyph.SetScaleModeToScaleByVector(); // Take length from normal
        //highlightGlyph.SetVectorModeToUseNormal(); // Take direction from normal
    }
    public void scaleNone() {
        lineGlyph.SetScaleModeToDataScalingOff(); // Do not adjust size
        //highlightGlyph.SetScaleModeToDataScalingOff(); // Do not adjust size
    }
    public void orientByNormal() {
        lineGlyph.SetVectorModeToUseNormal(); // Take direction from normal        
        //highlightGlyph.SetVectorModeToUseNormal(); // Take direction from normal        
    }
    public void colorByScalar() {
        lineGlyph.SetColorModeToColorByScalar(); // Take color from scalar        
        //highlightGlyph.SetColorModeToColorByScalar(); // Take color from scalar
    }

    class GlyphPosition {
        private vtkPolyData glyphData;
        vtkDataArray colorIndexArray;
        int arrayIndex;
        int unselectedColorIndex;
        
        public GlyphPosition(vtkPolyData d, int i, int c) {
            glyphData = d;
            colorIndexArray = glyphData.GetPointData().GetScalars();
            // colorIndexArray = a;
            arrayIndex = i;
            unselectedColorIndex = c;
        }        
        
        public void setPosition(double[] v) {
            glyphData.GetPoints().SetPoint(arrayIndex, v[0], v[1], v[2]);
        }
        public void setNormal(double[] v) {
            glyphData.GetPointData().GetNormals().SetTuple3(arrayIndex, v[0], v[1], v[2]);
        }
        
    }
    
    
    class GlyphIndex {

        // Hashtable residueGlyphs = new Hashtable();
        // Hashtable atomGlyphs = new Hashtable();
        // Index atoms, residues, etc. to sets of glyphs
        Hashtable objectGlyphs = new Hashtable();
        HashSet allGlyphs = new HashSet();

        vtkPolyData vtkData;
        
        public GlyphIndex() {}
        void setData(vtkPolyData d) {
            vtkData = d;
        }
        
        boolean containsKey(Object o) {
            if (objectGlyphs.containsKey(o)) return true;
            // if (atomGlyphs.containsKey(o)) return true;
            return false;
        }

        public void add(Collection<Object> objectKeys, vtkPolyData pointData, int arrayIndex, int colorIndex) {
            GlyphPosition glyph = new GlyphPosition(pointData, arrayIndex, colorIndex);
            allGlyphs.add(glyph);
            // Index this one glyph by all of the entities it represents
            for (Iterator i = objectKeys.iterator(); i.hasNext(); ) {
                Object o = i.next();
                if (! objectGlyphs.containsKey(o)) objectGlyphs.put(o, new Vector());
                Vector glyphs = (Vector) objectGlyphs.get(o);
                glyphs.add(glyph);
            }
        }

    }
    
}
