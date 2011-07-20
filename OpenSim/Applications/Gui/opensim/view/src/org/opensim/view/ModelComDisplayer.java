/*
 * ModelComDisplayer.java
 *
 * Created on July 7, 2011, 1:59 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimContext;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;
import vtk.vtkActor;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkSphereSource;

/**
 *
 * @author Ayman
 */
public class ModelComDisplayer {
    
    vtkActor centerOfMassActor = new vtkActor();
    vtkSphereSource comSource = new vtkSphereSource();
    
    /** Creates a new instance of ModelComDisplayer */
    public ModelComDisplayer() {
       vtkPolyDataMapper comMapper = new vtkPolyDataMapper();

       comSource.SetRadius(ViewDB.getInstance().getMarkerDisplayRadius()*2);
       comMapper.SetInput(comSource.GetOutput());
       centerOfMassActor.SetMapper(comMapper);
       centerOfMassActor.GetProperty().SetColor(0.0, 1.0, 0.0); // Green COM for now

    }

    vtkProp3D getVtkActor() {
        return centerOfMassActor;
    }

    void updateCOMLocation(Model model) {
        OpenSimContext context=OpenSimDB.getInstance().getContext(model);
        double[] com = new double[3];
        context.getCenterOfMassInGround(com);
        System.out.println("COM at "+com[0]+","+com[1]+","+com[2]);
        comSource.SetCenter(com);
    }
    
}
