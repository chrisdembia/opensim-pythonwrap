package vtk;

import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAxes;
import vtk.vtkPolyDataMapper;
import vtk.vtkTubeFilter;

public class AxesActor extends vtkAssembly {

  private double axisLength = 0.5;
  private double axisTextLength = 0.1;
  //private vtkTextActor xactor, yactor, zactor;

  public AxesActor() {
    super();
    createAxes();
  }

  public void createAxes() {
/*
    vtkAxes axes = new vtkAxes();
    axes.SetOrigin(0, 0, 0);
    axes.SetScaleFactor(axisLength);

    xactor = new vtkTextActor();
    yactor = new vtkTextActor();
    zactor = new vtkTextActor();

    xactor.SetInput("X");
    yactor.SetInput("Y");
    zactor.SetInput("Z");

    xactor.ScaledTextOn();
    yactor.ScaledTextOn();
    zactor.ScaledTextOn();

    xactor.GetPositionCoordinate().SetCoordinateSystemToWorld();
    yactor.GetPositionCoordinate().SetCoordinateSystemToWorld();
    zactor.GetPositionCoordinate().SetCoordinateSystemToWorld();

    xactor.GetPositionCoordinate().SetValue(axisLength, 0.0, 0.0);
    yactor.GetPositionCoordinate().SetValue(0.0, axisLength, 0.0);
    zactor.GetPositionCoordinate().SetValue(0.0, 0.0, axisLength);

    xactor.GetTextProperty().SetColor(1.0, 1.0, 1.0);
    xactor.GetTextProperty().ShadowOn();
    xactor.GetTextProperty().ItalicOn();
    xactor.GetTextProperty().BoldOff();

    yactor.GetTextProperty().SetColor(1.0, 1.0, 1.0);
    yactor.GetTextProperty().ShadowOn();
    yactor.GetTextProperty().ItalicOn();
    yactor.GetTextProperty().BoldOff();

    zactor.GetTextProperty().SetColor(1.0, 1.0, 1.0);
    zactor.GetTextProperty().ShadowOn();
    zactor.GetTextProperty().ItalicOn();
    zactor.GetTextProperty().BoldOff();

    xactor.SetMaximumLineHeight(0.25);
    yactor.SetMaximumLineHeight(0.25);
    zactor.SetMaximumLineHeight(0.25);

    vtkTubeFilter tube = new vtkTubeFilter();
    tube.SetInput(axes.GetOutput());
    tube.SetRadius(0.01);
    tube.SetNumberOfSides(6);

    vtkPolyDataMapper tubeMapper = new vtkPolyDataMapper();
    tubeMapper.SetInput(tube.GetOutput());
    
    vtkActor tubeActor = new vtkActor();
    tubeActor.SetMapper(tubeMapper);
    tubeActor.PickableOff();
 */   
  
    int cylRes = 36;
    double cylRadius = 0.01;
    double cylAmbient = 0.5;
    double cylOpacity = 0.5;
    
    //--- x-Cylinder
    vtkCylinderSource xcyl = new vtkCylinderSource();
    xcyl.SetRadius(cylRadius);
    xcyl.SetHeight(axisLength);
    xcyl.CappingOn();
    xcyl.SetResolution(cylRes);
    vtkPolyDataMapper xcylMapper = new vtkPolyDataMapper();
    xcylMapper.SetInput(xcyl.GetOutput());
    vtkActor xcylActor = new vtkActor();
    xcylActor.SetMapper(xcylMapper);
    xcylActor.GetProperty().SetColor(1,0,0);
    xcylActor.RotateZ(-90);
    xcylActor.SetPosition(axisLength/2, 0.0, 0.0);
    xcylActor.GetProperty().SetAmbient(cylAmbient);
    xcylActor.GetProperty().SetOpacity(cylOpacity);

    //--- y-Cylinder
    vtkCylinderSource ycyl = new vtkCylinderSource();
    ycyl.SetRadius(cylRadius);
    ycyl.SetHeight(axisLength);
    ycyl.CappingOn();
    ycyl.SetResolution(cylRes);
    vtkPolyDataMapper ycylMapper = new vtkPolyDataMapper();
    ycylMapper.SetInput(ycyl.GetOutput());
    vtkActor ycylActor = new vtkActor();
    ycylActor.SetMapper(ycylMapper);
    ycylActor.GetProperty().SetColor(0,1,0);
    ycylActor.SetPosition(0.0, axisLength/2, 0.0);
    ycylActor.GetProperty().SetAmbient(cylAmbient);
    ycylActor.GetProperty().SetOpacity(cylOpacity);

    //--- z-Cylinder
    vtkCylinderSource zcyl = new vtkCylinderSource();
    zcyl.SetRadius(cylRadius);
    zcyl.SetHeight(axisLength);
    zcyl.CappingOn();
    zcyl.SetResolution(cylRes);
    vtkPolyDataMapper zcylMapper = new vtkPolyDataMapper();
    zcylMapper.SetInput(zcyl.GetOutput());
    vtkActor zcylActor = new vtkActor();
    zcylActor.SetMapper(zcylMapper);
    zcylActor.GetProperty().SetColor(0,0,1);
    zcylActor.RotateX(90);
    zcylActor.SetPosition(0.0, 0.0, axisLength/2);
    zcylActor.GetProperty().SetAmbient(cylAmbient);
    zcylActor.GetProperty().SetOpacity(cylOpacity);

    int coneRes = 36;
    double coneScale = 0.075;
    double coneAmbient = 0.5;
    double coneOpacity = .5;
    
    //--- x-Cone
    vtkConeSource xcone = new vtkConeSource();
    xcone.SetResolution(coneRes);
    vtkPolyDataMapper xconeMapper = new vtkPolyDataMapper();
    xconeMapper.SetInput(xcone.GetOutput());
    vtkActor xconeActor = new vtkActor();
    xconeActor.SetMapper(xconeMapper);
    xconeActor.GetProperty().SetColor(1,0,0);
    xconeActor.SetScale(coneScale, coneScale, coneScale);
    xconeActor.SetPosition(axisLength+(coneScale/2), 0.0, 0.0);
    xconeActor.GetProperty().SetAmbient(coneAmbient);
    xconeActor.GetProperty().SetOpacity(coneOpacity);

    //--- y-Cone
    vtkConeSource ycone = new vtkConeSource();
    ycone.SetResolution(coneRes);
    vtkPolyDataMapper yconeMapper = new vtkPolyDataMapper();
    yconeMapper.SetInput(ycone.GetOutput());
    vtkActor yconeActor = new vtkActor();
    yconeActor.SetMapper(yconeMapper);
    yconeActor.GetProperty().SetColor(0,1,0);
    yconeActor.RotateZ(90);
    yconeActor.SetScale(coneScale, coneScale, coneScale);
    yconeActor.SetPosition(0.0, axisLength+(coneScale/2), 0.0);
    yconeActor.GetProperty().SetAmbient(coneAmbient);
    yconeActor.GetProperty().SetOpacity(coneOpacity);

    //--- z-Cone
    vtkConeSource zcone = new vtkConeSource();
    zcone.SetResolution(coneRes);
    vtkPolyDataMapper zconeMapper = new vtkPolyDataMapper();
    zconeMapper.SetInput(zcone.GetOutput());
    vtkActor zconeActor = new vtkActor();
    zconeActor.SetMapper(zconeMapper);
    zconeActor.GetProperty().SetColor(0,0,1);
    zconeActor.RotateY(-90);
    zconeActor.SetScale(coneScale, coneScale, coneScale);
    zconeActor.SetPosition(0.0, 0.0, axisLength+(coneScale/2));
    yconeActor.GetProperty().SetAmbient(coneAmbient);
    yconeActor.GetProperty().SetOpacity(coneOpacity);
    
    //--- x-Label
    vtkVectorText xtext = new vtkVectorText();
    xtext.SetText("X");
    vtkPolyDataMapper xtextMapper = new vtkPolyDataMapper();
    xtextMapper.SetInput(xtext.GetOutput());
    final vtkFollower xtextActor = new vtkFollower();
    xtextActor.SetMapper(xtextMapper);
    xtextActor.SetScale(axisTextLength, axisTextLength, axisTextLength);
    xtextActor.GetProperty().SetColor(1, 0, 0);
    xtextActor.SetPosition(axisLength, 0.0, 0.0);
    
    //--- y-Label
    vtkVectorText ytext = new vtkVectorText();
    ytext.SetText("Y");
    vtkPolyDataMapper ytextMapper = new vtkPolyDataMapper();
    ytextMapper.SetInput(ytext.GetOutput());
    final vtkFollower ytextActor = new vtkFollower();
    ytextActor.SetMapper(ytextMapper);
    ytextActor.SetScale(axisTextLength, axisTextLength, axisTextLength);
    ytextActor.GetProperty().SetColor(0, 1, 0);
    ytextActor.SetPosition(0.0, axisLength, 0.0);
    
    //--- z-Label
    vtkVectorText ztext = new vtkVectorText();
    ztext.SetText("Z");
    vtkPolyDataMapper ztextMapper = new vtkPolyDataMapper();
    ztextMapper.SetInput(ztext.GetOutput());
    final vtkFollower ztextActor = new vtkFollower();
    ztextActor.SetMapper(ztextMapper);
    ztextActor.SetScale(axisTextLength, axisTextLength, axisTextLength);
    ztextActor.GetProperty().SetColor(0, 0, 1);
    ztextActor.SetPosition(0.0, 0.0, axisLength);

    //this.AddPart(tubeActor);
    this.AddPart(xcylActor);
    this.AddPart(ycylActor);
    this.AddPart(zcylActor);
    
    this.AddPart(xconeActor);
    this.AddPart(yconeActor);
    this.AddPart(zconeActor);
    
//    this.AddPart(xtextActor);
//    this.AddPart(ytextActor);
//    this.AddPart(ztextActor);

  }

  public void setAxesVisibility(boolean ison) {
    this.SetVisibility(ison ? 1 : 0);

    //xactor.SetVisibility(ison ? 1 : 0);
    //yactor.SetVisibility(ison ? 1 : 0);
    //zactor.SetVisibility(ison ? 1 : 0);
  }

}
