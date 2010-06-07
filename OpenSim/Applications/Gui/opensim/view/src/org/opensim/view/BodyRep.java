/*
 * BodyRep.java
 *
 * Created on April 3, 2010, 1:28 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.Hashtable;
import org.opensim.modeling.Body;
import org.opensim.modeling.VisibleObject;
import org.opensim.view.pub.GeometryFileLocator;
import vtk.FrameActor;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkOBJReader;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkSTLReader;
import vtk.vtkXMLPolyDataReader;

/**
 *
 * @author ayman
 *
 * The visual Representation of one body (bones, base-frame, ..
 */
public class BodyRep extends vtkAssembly{
    
    private FrameActor bodyAxes = new FrameActor();
    private FrameActor jointBFrame = new FrameActor();
    private boolean showAxes = false;
    private boolean showJointBFrame = false;
    protected Hashtable<Body, FrameActor> mapChildren2Frames = new Hashtable<Body, FrameActor>(2);
    private double bFrameScale =1.2;
    private double bFrameRadius =0.005;
    private double pFrameScale = 1.6;
    private double pFrameRadius = .003;
    
    private Body body;
    /** Creates a new instance of BodyRep */
    public BodyRep(vtkAssembly modelAssembly, Body body, String modelFilePath)
   {
      this.body = body;
      jointBFrame.SetScale(bFrameScale);
      jointBFrame.setRadius(bFrameRadius);
      jointBFrame.GetProperty().SetOpacity(0.5);
      bodyAxes.SetScale(2.);
      bodyAxes.setRadius(0.001);
      //bodyAxes.setSymmetric(true);
      //jointBFrame.GetProperty().SetLineStipplePattern(1);
      VisibleObject bodyDisplayer = body.getDisplayer();

      // Scale
      double[] scales = new double[3];
      bodyDisplayer.getScaleFactors(scales);
      //SetScale(scales);
      // For each bone in the current body.
      for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {
          String boneFile = GeometryFileLocator.getInstance().getFullname(modelFilePath,bodyDisplayer.getGeometryFileName(k), false);
          if (boneFile==null)
             continue;
          if (boneFile.toLowerCase().endsWith(".vtp")){
              vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
              polyReader.SetFileName(boneFile);
              vtkPolyData poly = polyReader.GetOutput();
              addBoneFileActor(boneFile, poly, scales);
              polyReader.GetOutput().ReleaseDataFlagOn();
          }
          else if (boneFile.toLowerCase().endsWith(".stl")){
              vtkSTLReader polyReader = new vtkSTLReader();
              polyReader.SetFileName(boneFile);
              vtkPolyData poly = polyReader.GetOutput();
              addBoneFileActor(boneFile, poly, scales);
              polyReader.GetOutput().ReleaseDataFlagOn();
          }
          else if (boneFile.toLowerCase().endsWith(".obj")){
              vtkOBJReader polyReader = new vtkOBJReader();
              polyReader.SetFileName(boneFile);
              vtkPolyData poly = polyReader.GetOutput();
              addBoneFileActor(boneFile, poly, scales);
              polyReader.GetOutput().ReleaseDataFlagOn();
           }
          else
              System.out.println("Unexpected extension for geometry file"+boneFile+"while processing body "+body.getName());
      }
      
      if (bodyDisplayer.getVisibleProperties().getShowAxes()){
          AddPart(getBodyAxes());
      }
      modelAssembly.AddPart(this);
    }

    private void addBoneFileActor(final String boneFile, final vtkPolyData polyData, double[] scales) {

        vtkActor boneActor = new vtkActor();
        vtkPolyDataMapper boneMapper = new vtkPolyDataMapper();
        boneActor.SetMapper(boneMapper);
        // Create polyData and append it to one common polyData object
        boneMapper.SetInput(polyData);
        boneActor.SetScale(scales);
        AddPart(boneActor);
    }

    public vtkActor getBodyAxes() {
        return bodyAxes;
    }

    public boolean isShowAxes() {
        return showAxes;
    }

    public void setShowAxes(boolean showAxes) {
        if (showAxes==false)
            RemovePart(bodyAxes);
        else {
            AddPart(getBodyAxes());
        }
        this.showAxes = showAxes;
        body.getDisplayer().getVisibleProperties().setShowAxes(showAxes);
    }

    public boolean isShowJointBFrame() {
        return showJointBFrame;
    }

    public void setShowJointBFrame(boolean showJointBFrame) {
        this.showJointBFrame = showJointBFrame;
        // if turning On, add jointBFrame Part, else remove it
        if (showJointBFrame==false){
            RemovePart(jointBFrame);
        }
        else {
            if (!body.hasJoint()) return;
            double[] location = new double[3];
            double[] orientation = new double[3];
            body.getJoint().getLocationInChild(location);
            jointBFrame.SetPosition(location);
            body.getJoint().getOrientationInChild(orientation);
            jointBFrame.SetOrientation(orientation);
            AddPart(jointBFrame);
            Modified();
        }
    }

    public void setShowJointPFrame(Body body, boolean state){
        if (state){
        FrameActor jointPFrame = new FrameActor();
        jointPFrame.SetScale(pFrameScale); //.2
        jointPFrame.setRadius(pFrameRadius); //.02
        double[] location = new double[3];
        double[] orientation = new double[3];
        body.getJoint().getLocationInParent(location);
        jointPFrame.SetPosition(location);
        body.getJoint().getOrientationInParent(orientation);
        jointPFrame.SetOrientation(orientation);
            jointPFrame.GetProperty().SetOpacity(0.75);
        jointPFrame.GetProperty().SetLineStipplePattern(2);
        AddPart(jointPFrame);   
        Modified();
        mapChildren2Frames.put(body, jointPFrame);
    }
        else {  // Removing
            FrameActor jointPFrame = mapChildren2Frames.get(body);
            RemovePart(jointPFrame);   
            Modified();
            mapChildren2Frames.remove(body);
        }
    }

    public boolean isShowJointPFrame(Body body){
        return (mapChildren2Frames.get(body)!=null);
    }

}
