package simtkView;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JInternalFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JSlider;
import javax.swing.JToolBar;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

import simtkCommands.CommandFactory;
import simtkCommands.SimtkCommand;
import simtkCore.SimtkSimEnv;
import simtkModel.Model;
import simtkModel.SWIGTYPE_p_double;
import simtkModel.rdArrayDouble;
import simtkModel.rdBody;
import simtkModel.rdModel;
import simtkModel.rdObject;
import simtkModel.rdTransform;
import simtkModel.rdVisibleObject;
import simtkModel.rdVisibleProperties;
import simtkModel.suMarker;
import simtkModel.suMarkerSet;
import simtkModel.suSetMarkers;
import simtkUtils.SimtkValidateName;
import simtkView.animation.*;
import simtkui.SimDlgGetName;
import simtkui.SimtkApp;
import simtkuiEvents.SimtkSimEnvStateChangeEvent;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkCamera;
import vtk.vtkGlyph3D;
import vtk.vtkLightCollection;
import vtk.vtkOutlineFilter;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProperty;
import vtk.vtkSphereSource;
import vtk.vtkXMLPolyDataReader;
import simtkuiEvents.*;
import simtkCore.*;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p> This class represents a Full Model's
 * Window. If it has more than one body, the corresponding vtkActors will be
 * created and maintained here as well as the vtkMappers associated with them.
 * It's intended that all vtk specfic functionality would be kept here so that
 * switching to another visualization system if needed is possible. For now
 * we'll use one vtkAssembly per model though performance may be an issue
 * (according to vtk documentation). If this becomes an issue we can use a list
 * of vtkActors rather than one vtkAssembly. This class should define an
 * interface so that actuators or any other objects that has geometry can be
 * added to the model.
 *
 * @author Ayman Habib
 * @version 1.0
 * @todo Change traversal to include all rdVisibleObjects instead of bodies so
 *   that new objects that inherit from rdVsisbleObject (classes that support
 *   the interface defined by rdVsisbleObject) do get displayed automatically.
 * @todo Switch to lazy actor creation where we don't build the boundingbox
 *   actor or the normals actor until they are requested by a view command. We
 *   can do it by initializing all actors to null and then when truning on an
 *   option create proper actor if it's not set.
 * @todo Picking actors from a vtkAssembly didn't work so I'm switching back to
 *   adding actors directly to display. This may need to be revisited when we have real assemblies
 *  as the main advantage of a vtkAssembly is in probagating xforms.
 */
public class SimtkMdlInternalFrame
    extends JInternalFrame implements Observer{
  private SimtkSimEnv _env = null;
  private rdModel _mdl = null; // Keep a reference to rdModel for reverse lookup
  private SimtkCanvas _renWin = null;
  private SimtkAnimation animation = null;

  SimtkCommand _simStartCommand=null;
  SimtkCommand _simStopCommand=null;

  // Keep a map between objects and Visible properties SimtkVisRep which contains state
  // of what's displayed
  private Hashtable _visibleObjects2VisRepMap = new Hashtable();
  private Hashtable _actors2VisibleObjectsMap = new Hashtable();
  private Vector _cameras = new Vector();
  private Vector _cameraNames = new Vector();
  private JMenuBar _frameMenuBar;
  private JMenu _cameraMenu;
  private vtkCamera _frontCamera, _topCamera, _sideCamera;
  static String[] defaultPositions = {"Front", "Top", "Side", "Refit", "New.."};

  JMenuItem jMenuItemFrontCam = new JMenuItem();
  JMenuItem jMenuItemRightCam = new JMenuItem();
  JMenuItem jMenuItemTopCam = new JMenuItem();
  JMenuItem jMenuItemNewCam = new JMenuItem();
  JMenuItem jMenuItemDefaultCam = new JMenuItem();
  JToolBar jSimenvToolBar = new JToolBar();
  JPanel jStatusPanel = new JPanel();
  JProgressBar progressBar = new JProgressBar();
  JButton jStartSimulation = new JButton();
  JButton jStopSimulation = new JButton();
  Border border1;
  JLabel jStatusLabel = new JLabel();
  GridLayout gridLayout1 = new GridLayout();
  JLabel jOperationLabel = new JLabel();
  // Animation related stuff
  JButton jPlayButton = new JButton();
  JButton jBackwardButton = new JButton();
  JButton jFwdButton = new JButton();
  JSlider jAnimationSlider = new JSlider();
  JPanel jAnimationPanel = new JPanel();
  JButton jPauseButton = new JButton();
  JButton jRewindButton = new JButton();
  JSlider jSpeedSlider = new JSlider();
  JButton jKeyFrameButton = new JButton();

  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  ImageIcon image4;
  ImageIcon image5;
  ImageIcon image6;
  ImageIcon image7;
  Border border2;
  //JButton jSaveAnimationButton = new JButton();
  JCheckBox jUseCameraButton = new JCheckBox();
  JComboBox jAnimationType = new JComboBox();
  String[] animationTypeStrings={"Frames", "Manual"};
  JLabel jAnimationSpeedLabel = new JLabel();
  JButton jClearButton = new JButton();

  public SimtkMdlInternalFrame(SimtkSimEnv env) {
    // Create window
    super(env.getName(),
          true, //resizable
          false, //closable
          true, //maximizable
          true); //iconifiable

    _env = env;
    _mdl = env.getModel();
    _env.addObserver(this);
    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    _renWin = new SimtkCanvas(this);
    //...Create the GUI and put it in the window...
    //...Then set the window size or call pack...
    //...Set the window's location.
    Dimension mySize = new Dimension();
    mySize.height = 300;
    mySize.width = 300;
    this.setSize(mySize);
    this.setIconifiable(true);
    this.getContentPane().setLayout(new BorderLayout());
    this.getContentPane().add(jSimenvToolBar, BorderLayout.NORTH);
    this.getContentPane().add(_renWin, BorderLayout.CENTER);
    this.getContentPane().add(jStatusPanel, BorderLayout.SOUTH);

    jStatusPanel.add(progressBar);
    setFrameIcon(SimtkApp.getAppIcon());
    // instantiate an animation and make it observe the environment
    animation = new SimtkDiscreteAnimation(_renWin.GetRenderer());
    jKeyFrameButton.setVisible(false);
    jAnimationType.setModel(new DefaultComboBoxModel(animationTypeStrings));
    registerAnimation(animation, true);
   //jAutoRecordButton.setSelected(animation.getAutoKeyFrames());
    enableAnimationPanel(false);

    // For now we'll use a geometry file to build a vtkActor
    // Setup the XML file reader, we generally expect to have many files one per bone/segment/body
    // One vtkAssembly has been created for the model, add parts to it

    // This loop should be done for all visible objects in the model, this way if
    // a new type is added it gets displayed automatically however we have no way
    // right now to find all visible objects in model as actuators for example do not
    // technically live with the model.
    displayObjects();
//    _renWin.GetRenderer().AddActor(_modelAssembly);
    initDefaultCameras();// This may depend on the model size
    this.pack();
    setVisible(true);
  }

  /**
   * registerAnimation
   *
   * @param animation SimtkAnimation
   */
  private void registerAnimation(SimtkAnimation animation, boolean doit) {
    if (doit){
      _env.addObserver(animation);
      animation.addObserver(this);
      jAnimationSlider.setModel(animation.getSliderModel());
      jUseCameraButton.setSelected(animation.getUseCamera());
       jSpeedSlider.setModel(animation.getSpeedModel());
    }
    else {
      _env.deleteObserver(animation);
      animation.deleteObserver(this);
    }
  }

  /**
   * displayObjects
   */
  public void displayObjects() {
    for (int i = 0; i < _mdl.getNB()+1; i++) {
      // For each visible object, get geometry, read it and display it into a vtkActor then add to modelAssembly
      rdBody nextBody = _mdl.getBody(i);
//      vtkAssembly bodyAssembly = new vtkAssembly();
      Vector bodyRepVector = new Vector();
      int numGeometryFiles = nextBody.getNumGeometryFiles();
      for (int geomFileNumber = 0; geomFileNumber < numGeometryFiles; geomFileNumber++) {
        String geometryFileName = nextBody.getGeometryFileName(geomFileNumber);
        vtkXMLPolyDataReader geometryReader = new vtkXMLPolyDataReader();
        geometryReader.SetFileName(geometryFileName);
        // Read data
        vtkPolyData pd = geometryReader.GetOutput();

        // Get scale factors
        SWIGTYPE_p_double scales =  Model.new_doubleArray(3);
        double[] jScales = new double[3];
        nextBody.getScaleFactors(scales);
        for (int idx=0; idx < 3; idx++){
          jScales[idx] = Model.doubleArray_get(scales, idx);
        }
        Model.free_doubleArray(scales);

        // Create Mapper and set its input from read data
        vtkPolyDataMapper bodyMapper = new vtkPolyDataMapper();
        bodyMapper.SetInput(pd);
        // Create Actor and associate it to mapper
        vtkActor bodyActor = new vtkActor();
        bodyActor.SetMapper(bodyMapper);
        // Scale actor before applying xform or generating other dependent mappers
        bodyActor.SetScale(jScales);
        // Set prefrences
        rdVisibleProperties appProp = nextBody.getVisibleProperties();
        vtkProperty vtkProp = new SimtkVisibleProperties(appProp).
            getVtkProperty();
        bodyActor.SetProperty(vtkProp);

        // Create bbox Actor as well
        vtkActor bboxActor = new vtkActor();
        vtkOutlineFilter bboxFilter = new vtkOutlineFilter();
        bboxFilter.SetInput(pd);
        vtkPolyDataMapper bboxMapper = new vtkPolyDataMapper();
        bboxMapper.SetInput(bboxFilter.GetOutput());
        bboxActor.SetMapper(bboxMapper);
        bboxActor.SetScale(jScales);
        // Now the normals
        vtkActor normalsActor = new vtkActor();
        vtkGlyph3D normalsFilter = new vtkGlyph3D();
        normalsFilter.SetVectorModeToUseNormal();
        normalsFilter.SetScaleModeToScaleByVector();
        normalsFilter.SetScaleFactor(.01);

        normalsFilter.SetInput(pd);
        vtkPolyDataMapper normalsMapper = new vtkPolyDataMapper();
        normalsMapper.SetInput(normalsFilter.GetOutput());
        normalsActor.SetMapper(normalsMapper);
        normalsActor.SetScale(jScales);
        // Get transformation
        rdTransform xform = nextBody.getTransform();

        // CoordinateSystem
         vtkAssembly axesActor = new AxesActor();

       // Create an instance of SimtkVisRep to contain all vtkActors for
        // Geometry, boundingbox, normals
        SimtkVisRep bodyRep = new SimtkVisRep();
        bodyRep.setGeomActor(bodyActor);
        bodyRep.setBboxActor(bboxActor);
        bodyRep.setNormalsActor(normalsActor);
        bodyRep.setAxesActor(axesActor);

        // Get transformation
        bodyRep.setTransform(xform);
        boolean sn = appProp.getShowNormals();
        boolean sa = appProp.getShowAxes();
        bodyRep.updateDisplay(appProp.getDisplayPreference(),
                              sn,
                              sa);
        bodyRepVector.add(bodyRep);
        // Add to forward map body->bodyRepVector
        _visibleObjects2VisRepMap.put(nextBody, bodyRepVector);
        // Update reverse map used for picking
        _actors2VisibleObjectsMap.put(bodyActor, nextBody);
        _actors2VisibleObjectsMap.put(bboxActor, nextBody);
        _actors2VisibleObjectsMap.put(normalsActor, nextBody);
        _actors2VisibleObjectsMap.put(axesActor, nextBody);

        // Create Assembly and add Actors to it
//        bodyAssembly.AddPart(bodyActor);
//        bodyAssembly.AddPart(bboxActor);
//        bodyAssembly.AddPart(normalsActor);

        _renWin.GetRenderer().AddActor(bodyActor);
        _renWin.GetRenderer().AddActor(bboxActor);
        _renWin.GetRenderer().AddActor(normalsActor);
        _renWin.GetRenderer().AddActor(axesActor);
      }
//      _modelAssembly.AddPart(bodyAssembly);
    }
    // Get other objects and display them, use sphere if no gemetry file exists
    Enumeration modelObjects = _env.getModelObjects();
    while(modelObjects.hasMoreElements()){
      Object obj = modelObjects.nextElement();
      rdObject nextObj = (rdObject) obj;
      if (nextObj instanceof suMarkerSet){
        // Get geometry and display
        suSetMarkers markers = ((suMarkerSet) nextObj).getMarkers();
        // Foreach marker, find location, create sphere for it and display
        for(int markerSetIndex=0; markerSetIndex < markers.getSize(); markerSetIndex++){
          suMarker nextMarker = markers.get(markerSetIndex);
          vtkSphereSource sphere = new vtkSphereSource();
          sphere.SetRadius(0.02);
          sphere.SetThetaResolution(18);
          sphere.SetPhiResolution(18);

          // map to graphics objects
          vtkPolyDataMapper map = new vtkPolyDataMapper();
          map.SetInput(sphere.GetOutput());

          // actor coordinates geometry, properties, transformation
          vtkActor markerActor = new vtkActor();
          markerActor.SetMapper(map);
          markerActor.GetProperty().SetColor(0, 0, 1); // color blue
          // Get body transform from segment
           int markerSegment = nextMarker.getRefSegment();
          rdArrayDouble jRelativeLocation = new rdArrayDouble(0.0, 3, 3);
          nextMarker.getLocation(jRelativeLocation);
         SWIGTYPE_p_double relativePos = Model.new_doubleArray(3);
          for (int i = 0; i < 3; i++) {
           Model.doubleArray_set(relativePos, i, jRelativeLocation.getitem(i));
         }

         SWIGTYPE_p_double relativeGlobalLocation = Model.new_doubleArray(3);
         _mdl.getPosition(markerSegment, relativePos, relativeGlobalLocation);
         double[] jPos = new double[3];
         for (int i = 0; i < 3; i++) {
           jPos[i] = Model.doubleArray_get(relativeGlobalLocation, i);
         }
         markerActor.SetPosition(jPos);
         Model.free_doubleArray(relativePos);
         Model.free_doubleArray(relativeGlobalLocation);
           _renWin.GetRenderer().AddActor(markerActor);
          _actors2VisibleObjectsMap.put(markerActor, nextMarker);
          _visibleObjects2VisRepMap.put(nextMarker, markerActor);
        }
      }
    }
  }

  /**
   * getActorForVisibleObject returns the SimtkVisRep for the corresponding
   * rdVisibleObject or null if not found
   *
   * @param vObject rdVisibleObject
   * @return SimtkVisRep that conatins vtkActors as well as state of what's currently displayed
   */
  public Vector getActorsForVisibleObject(rdVisibleObject vObject)
  {
    if (_visibleObjects2VisRepMap.containsKey(vObject)){
      return (Vector) _visibleObjects2VisRepMap.get(vObject);
    }
    return null;
  }

  /**
   * getVisibleObjectForActor: This is a brute force rather expensive method. to
   * find an object given a picked actor.
   * @todo implement datastructures to support reverse lookup.
   *
   * @param act vtkActor
   * @return rdVisibleObject
   */
  rdVisibleObject getVisibleObjectForActor(vtkActor act)
  {
    if (_actors2VisibleObjectsMap.containsKey(act)){
      return (rdVisibleObject) _actors2VisibleObjectsMap.get(act);
    }
    return null;
  }
  /**
   * write2TiffFile
   *
   * @param fullFileName String
   */
  public void write2TiffFile(String fullFileName) {
     _renWin.HardCopy(fullFileName, 1);
  }

  /**
   * getModelName retrieves the name of the model associated with the current
   * frame
   *
   * @return String
   */
  public String getModelName() {
    return _mdl.getName();
  }

  /**
   * updateDisplay
   *
   * @param selectedObject rdVisibleObject
   *
   * The actual change is performed by the database early on, this function only updates the display
   * to be in sync. with rdVisibleProperties of the vObject
   * if vObject is Null then this nothing is done.
   */
  public void updateDisplay(rdVisibleObject vObject) {
    if (vObject != null){
      Vector visRepVector = getActorsForVisibleObject(vObject);
      // Object may have no visible representation for whatever reason
      if (visRepVector == null)
        return;
      int displayPref = vObject.getVisibleProperties().getDisplayPreference();
      for (int i = 0; i < visRepVector.size(); i++) {
        SimtkVisRep visRep = (SimtkVisRep) visRepVector.get(i);
        if (visRep.getGeomActor() == null)
          continue;
        visRep.updateDisplay(displayPref,
                             vObject.getVisibleProperties().getShowNormals(),
                             vObject.getVisibleProperties().getShowAxes());
      }
    }
   _renWin.Render();
  }

  /**
   * updateDisplay
   *
   * This function updates the display when xforms are changed during simulation
   */
  public void updateDisplay() {

   Enumeration e = _visibleObjects2VisRepMap.keys();
   // getMutex and releaseMutex are used to make sure xforms are obtained from the same callback step
   _env.getAnimationCallback().getMutex();
   _env.setSimulationTime(_env.getAnimationCallback().getCurrentTime());
   while (e.hasMoreElements()){
     Object obj = e.nextElement();
     if (obj instanceof rdBody){
       rdBody nextBody = (rdBody) obj;
       Vector bodyRepVector = (Vector) _visibleObjects2VisRepMap.get(nextBody);
       int numBodies = bodyRepVector.size();
       for (int i = 0; i < numBodies; i++) {
         SimtkVisRep bodyRep = (SimtkVisRep) bodyRepVector.elementAt(i);
         bodyRep.setTransform(nextBody.getTransform());
       }
     }
     else if (obj instanceof suMarker){
       suMarker nextMarker = (suMarker) obj;
       vtkActor markerActor =  (vtkActor) _visibleObjects2VisRepMap.get(nextMarker);
       int markerSegment = nextMarker.getRefSegment();
       rdArrayDouble jRelativeLocation = new rdArrayDouble(0.0, 3, 3);
       nextMarker.getLocation(jRelativeLocation);
      SWIGTYPE_p_double relativePos = Model.new_doubleArray(3);
       for (int i = 0; i < 3; i++) {
        Model.doubleArray_set(relativePos, i, jRelativeLocation.getitem(i));
      }

      SWIGTYPE_p_double relativeGlobalLocation = Model.new_doubleArray(3);
      _mdl.getPosition(markerSegment, relativePos, relativeGlobalLocation);
      double[] jPos = new double[3];
      for (int i = 0; i < 3; i++) {
        jPos[i] = Model.doubleArray_get(relativeGlobalLocation, i);
      }
      markerActor.SetPosition(jPos);
      Model.free_doubleArray(relativePos);
      Model.free_doubleArray(relativeGlobalLocation);
    }
   }
   _renWin.Render();
   if (animation instanceof SimtkDiscreteAnimation)
     animation.addFrame(_env.getSimulationTime());
   _env.getAnimationCallback().releaseMutex();
 }
 /**
  * recreateDisplay
  */
 public void recreateDisplay() {
   clearAll();
   displayObjects();
 }

  /**
   * clearAll
   */
  private void clearAll() {
    Enumeration actorsEnum = _actors2VisibleObjectsMap.keys();
    while(actorsEnum.hasMoreElements()){
      Object obj = actorsEnum.nextElement();
      _renWin.GetRenderer().RemoveActor((vtkProp3D)obj);
    }
  }

  /**
   * initDefaultCameras sets the parametrs of default cameras for front, top,
   * right positions
   */
  void initDefaultCameras() {
    // Get box around model
    double[] modelBounds = _renWin.GetRenderer().ComputeVisiblePropBounds();
    // These modelBounds are [xmin, xmax, ymin, ymax, zmin, zmax]
    double[] boxCenter = new double[3];
    for(int i=0; i < 3; i++)
      boxCenter[i] = (modelBounds[2*i]+modelBounds[2*i+1])/2;

    _frontCamera = new vtkCamera();
    _frontCamera.Azimuth(0);
    _frontCamera.Elevation(0);
    _frontCamera.Roll(0);
    _frontCamera.SetViewAngle(30);
    _frontCamera.SetFocalPoint(0, 0, 0);
    _frontCamera.SetViewUp(0, 1, 0);

    _topCamera = new vtkCamera();
    _topCamera.Azimuth(0);
    _topCamera.Elevation(90);
    _topCamera.Roll(0);
    _topCamera.SetViewAngle(30);
    _topCamera.SetFocalPoint(0, 0, 0);
    _topCamera.SetViewUp(1, 0, 0);

    _sideCamera = new vtkCamera();
   _sideCamera.Azimuth(-90);
   _sideCamera.Elevation(0);
   _sideCamera.Roll(0);
   _sideCamera.SetViewAngle(30);
   _sideCamera.SetFocalPoint(0, 0, 0);
   _sideCamera.SetViewUp(0, 1, 0);

   _cameras.add(_frontCamera);
   _cameraNames.add(defaultPositions[0]);
   _cameras.add(_topCamera);
   _cameraNames.add(defaultPositions[1]);
   _cameras.add(_sideCamera);
   _cameraNames.add(defaultPositions[2]);

  }
  private void jbInit() throws Exception {
    _frameMenuBar = new JMenuBar();
    _cameraMenu = new JMenu("Cameras");
    border1 = new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(165, 163, 151));
    border2 = new TitledBorder(BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151)),"");
    jMenuItemFrontCam.setAction(new setPickCameraAction());
    jMenuItemFrontCam.setText(defaultPositions[0]);

    jMenuItemTopCam.setAction(new setPickCameraAction());
    jMenuItemTopCam.setText(defaultPositions[1]);

    jMenuItemRightCam.setAction(new setPickCameraAction());
    jMenuItemRightCam.setText(defaultPositions[2]);

    jMenuItemDefaultCam.setAction(new setPickCameraAction());
    jMenuItemDefaultCam.setText(defaultPositions[3]);

    jMenuItemNewCam.setAction(new createCameraAction());
    jMenuItemNewCam.setText(defaultPositions[4]);

     _simStartCommand = CommandFactory.getCommand("SimtkSimulationStartCmd");
    HashMap startparams = new HashMap(4);
    startparams.put("EnvName", _env.getName());
    _simStartCommand.setCommandParams(startparams);

    _simStopCommand = CommandFactory.getCommand("SimtkSimulationStopCmd");
    HashMap stopparams = new HashMap(4);
    stopparams.put("EnvName", _env.getName());
    _simStopCommand.setCommandParams(stopparams);

    jStartSimulation.setAction(_simStartCommand);
    jStopSimulation.setAction(_simStopCommand);

    image1 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
       "play.gif"));
   image2 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
       "forward.gif"));
   image3 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
     "back.gif"));
   image4 = new ImageIcon(simtkui.SimtkApp.class.getResource(
     "camera.gif"));
   image5 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
      "pause.gif"));
 image6 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
   "rewind.gif"));
    image7 = new ImageIcon(simtkView.SimtkMdlInternalFrame.class.getResource(
      "clear.gif"));

    jSimenvToolBar.setBorder(border1);
    jStatusLabel.setToolTipText("");
    jStatusLabel.setText("");
    jStatusPanel.setLayout(gridLayout1);
    jOperationLabel.setText("");
    progressBar.setBackground(new Color(236, 145, 173));
    jPlayButton.setPreferredSize(new Dimension(25, 25));
    jPlayButton.setToolTipText("Play back animation");
    jPlayButton.setContentAreaFilled(true);
    jPlayButton.setIcon(image1);
    jPlayButton.setText("");
    jPlayButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jPlayButton_actionPerformed(e);
      }
    });

    jKeyFrameButton.setPreferredSize(new Dimension(25, 25));
    jKeyFrameButton.setContentAreaFilled(false);
    jKeyFrameButton.setIcon(image4);
    jKeyFrameButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jKeyFrameButton_actionPerformed(e);
      }
    });

    jBackwardButton.setPreferredSize(new Dimension(25, 25));
    jBackwardButton.setToolTipText("Back one frame");
    jBackwardButton.setIcon(image3);
    jBackwardButton.setText("");
    jBackwardButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jBackwardButton_actionPerformed(e);
      }
    });
    jFwdButton.setPreferredSize(new Dimension(25, 25));
    jFwdButton.setToolTipText("Forward one frame");
    jFwdButton.setContentAreaFilled(true);
    jFwdButton.setIcon(image2);
    jFwdButton.setText("");
    jFwdButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jFwdButton_actionPerformed(e);
      }
    });
    jPauseButton.setOpaque(false);
    jPauseButton.setPreferredSize(new Dimension(25, 25));
    jPauseButton.setToolTipText("Pause animation");
    jPauseButton.setContentAreaFilled(true);
    jPauseButton.setIcon(image5);
    jPauseButton.setText("");
    jPauseButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jPauseButton_actionPerformed(e);
      }
    });

    jRewindButton.setPreferredSize(new Dimension(25, 25));
    jRewindButton.setToolTipText("");
    jRewindButton.setActionCommand("");
    jRewindButton.setIcon(image6);
    jRewindButton.setText("");
    jRewindButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jRewindButton_actionPerformed(e);
      }
    });

    jAnimationPanel.setAlignmentX((float) 0.5);
    jAnimationPanel.setAlignmentY((float) 0.5);
    jAnimationPanel.setBorder(border2);
    jAnimationPanel.setMinimumSize(new Dimension(444, 39));
    jAnimationPanel.setPreferredSize(new Dimension(300, 39));
    jAnimationSlider.setMajorTickSpacing(10);
    jAnimationSlider.setMinorTickSpacing(1);
    jAnimationSlider.setPaintLabels(false);
    jAnimationSlider.setPaintTrack(true);
    jAnimationSlider.setFont(new java.awt.Font("Dialog", 0, 8));
    jAnimationSlider.setMaximumSize(new Dimension(32767, 24));
    jAnimationSlider.setMinimumSize(new Dimension(36, 24));
    jAnimationSlider.setPreferredSize(new Dimension(100, 24));
    jAnimationSlider.setToolTipText("Frames/Time");

    jSpeedSlider.setInverted(true);
    jSpeedSlider.setMajorTickSpacing(5);
    jSpeedSlider.setMaximum(20);
    jSpeedSlider.setMinimum(0);
    jSpeedSlider.setMinorTickSpacing(0);
    jSpeedSlider.setPaintLabels(false);
    jSpeedSlider.setPaintTicks(true);
    jSpeedSlider.setMaximumSize(new Dimension(50, 24));
    jSpeedSlider.setPreferredSize(new Dimension(50, 24));

    /*
     jSaveAnimationButton.setToolTipText("");
    jSaveAnimationButton.setText("Save");
    jSaveAnimationButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jSaveAnimationButton_actionPerformed(e);
      }
    });
    }*/
    jUseCameraButton.setSelected(true);
    jUseCameraButton.setText("Camera");
    jUseCameraButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jUseCameraButton_actionPerformed(e);
      }
    });

    jAnimationType.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jAnimationType_actionPerformed(e);
      }
    });
    jAnimationSpeedLabel.setToolTipText("");
    jAnimationSpeedLabel.setText("Speed:");
    jClearButton.setMaximumSize(new Dimension(40, 23));
    jClearButton.setMinimumSize(new Dimension(40, 23));
    jClearButton.setPreferredSize(new Dimension(25, 25));
    jClearButton.setText("");
    jClearButton.setIcon(image7);
    jClearButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jClearButton_actionPerformed(e);
      }
    });
    _frameMenuBar.add(_cameraMenu);
    _cameraMenu.add(jMenuItemFrontCam);
    _cameraMenu.add(jMenuItemRightCam);
    _cameraMenu.add(jMenuItemTopCam);
    _cameraMenu.add(jMenuItemDefaultCam);
    _cameraMenu.addSeparator();
    _cameraMenu.add(jMenuItemNewCam);
    this.getContentPane().add(jSimenvToolBar, BorderLayout.NORTH);
    //jAnimationPanel.add(jSaveAnimationButton, null);
    jAnimationPanel.add(jClearButton, null);
    jAnimationPanel.add(jBackwardButton, null);
    jAnimationPanel.add(jPlayButton, null);
    jAnimationPanel.add(jFwdButton, null);
    jAnimationPanel.add(jPauseButton, null);
    jAnimationPanel.add(jRewindButton, null);
    jAnimationPanel.add(jAnimationSlider, null);
    jAnimationPanel.add(jUseCameraButton, null);
    jAnimationPanel.add(jAnimationSpeedLabel, null);
    jAnimationPanel.add(jSpeedSlider, null);
    jAnimationPanel.add(jAnimationType, null);
    jAnimationPanel.add(jKeyFrameButton, null);
    jSimenvToolBar.add(jStartSimulation, null);
    jSimenvToolBar.add(jStopSimulation, null);
    jSimenvToolBar.add(jAnimationPanel, null);
    jStatusPanel.add(progressBar, null);
    jStatusPanel.add(jStatusLabel, null);
    jStatusPanel.add(jOperationLabel, null);

    setJMenuBar(_frameMenuBar);
    _cameraMenu.setToolTipText("Manage Cameras");
    _cameraMenu.setText("Cameras");
    this.getContentPane().setLayout(new BorderLayout());
  }

  /**
   * update is called when env. associated with the internal frame signals a change
   *
   * @param o Observable
   * @param arg Object
   */
  public void update(Observable o, Object arg) {
    if (arg instanceof SimtkAnimationAvailableEvent){
      enableAnimationPanel(((SimtkAnimationAvailableEvent)arg).getStatus());
      return;
    }
    if (arg instanceof SimtkSimEnvStateChangeEvent){
      SimtkSimEnvStateChangeEvent evnt = (SimtkSimEnvStateChangeEvent) arg;
      int oldState = evnt.getOldState();
      int newState = evnt.getNewState();
      if (newState == SimtkSimEnv.READY &&  oldState == SimtkSimEnv.RUNNING) {
        progressBar.setVisible(false);
      }
      else if (newState == SimtkSimEnv.RUNNING) {
        progressBar.setVisible(true);
      }
      else if (oldState == SimtkSimEnv.LOADING) {
        progressBar.setVisible(false);
      }
      else if (newState == SimtkSimEnv.LOADING) {
       progressBar.setVisible(true);
     }
     jStatusLabel.setText("Status:"+_env.getStatusString());
    }
    else if (arg instanceof SimtkAnimationTimeChangeEvent){
      double animationTime = ((SimtkAnimationTimeChangeEvent) arg).getTime();
      jOperationLabel.setText("Animation time="+animationTime);
    }
    if (_env.getStatus()!= SimtkSimEnv.PLAYBACK)
      jOperationLabel.setText(_env.getInfoString());
    _simStartCommand.update(o, arg);
    _simStopCommand.update(o, arg);
    if (_env.getDeterministicProgress()==false)
      progressBar.setIndeterminate(true);
    else {
      progressBar.setIndeterminate(false);
     int progress = _env.getProgressPercentage();
      progressBar.setValue(progress);
      // Show percentage only when something happens
      if (progress != 0)
        progressBar.setStringPainted(true);
    }
  }


  private class setPickCameraAction extends AbstractAction {
    private vtkCamera _myCamera;

    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      String cameraName = e.getActionCommand();
      int cameraIndex = _cameraNames.indexOf((Object) cameraName);
      if (cameraIndex != -1){ // Anything other than refit
        vtkCamera selectedCamera = (vtkCamera) _cameras.get(cameraIndex);
        vtkCamera cameraClone = new vtkCamera();
        cameraClone.SetPosition(selectedCamera.GetPosition());
        cameraClone.SetFocalPoint(selectedCamera.GetFocalPoint());
        cameraClone.SetViewAngle(selectedCamera.GetViewAngle());
        cameraClone.SetDistance(selectedCamera.GetDistance());
        cameraClone.SetClippingRange(selectedCamera.GetClippingRange());
        cameraClone.SetViewUp(selectedCamera.GetViewUp());
        cameraClone.SetParallelScale(selectedCamera.GetParallelScale());

        vtkLightCollection lights = _renWin.GetRenderer().GetLights();
        lights.RemoveAllItems();
        _renWin.GetRenderer().CreateLight();
        _renWin.GetRenderer().SetActiveCamera(cameraClone);
     }
      _renWin.resetCamera();// Refit after setting to get model within window
      _renWin.Render();
    }
  }
  private class createCameraAction extends AbstractAction implements SimtkValidateName{
    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public int validateName(String newName) {
      int index = _cameraNames.indexOf((Object) newName);

      if (index > -1 && index < 3 ||
          newName.equals(defaultPositions[3]) ||         //Refit
          newName.equals(defaultPositions[4]) ){         //New..
        return SimtkValidateName.NAME_IS_RESERVED;
      }

      if (index >=3 )
        return SimtkValidateName.NAME_ALREADY_IN_USE;

      // We can get here only if the index was -1
      return SimtkValidateName.NAME_IS_OK;
    }

    public void actionPerformed(ActionEvent e) {
      // Show dialog to name the camera
      SimDlgGetName getNameDlg = new SimDlgGetName("Camera");
      getNameDlg.setValidationMethod(this);
      getNameDlg.setVisible(true);

      if (!getNameDlg.userConfirmed())
        return;
      // User confirmed

      String newCameraName =  getNameDlg.getName();

      // Don't need the dialog anymore
      getNameDlg.dispose();
      // Create new menuitem
      JMenuItem jMenuItemUserCam = new JMenuItem();
      jMenuItemUserCam.setAction(new setPickCameraAction());
      jMenuItemUserCam.setText(newCameraName);
      _cameraMenu.add(jMenuItemUserCam);
      // Clone current camera and insert into Vectors
      _cameraNames.add(newCameraName);
      vtkCamera userCamera = new vtkCamera();
      userCamera.SetPosition(_renWin.GetRenderer().GetActiveCamera().
                             GetPosition());
      userCamera.SetFocalPoint(_renWin.GetRenderer().GetActiveCamera().
                               GetFocalPoint());
      userCamera.SetEyeAngle(_renWin.GetRenderer().GetActiveCamera().
                             GetEyeAngle());
      userCamera.SetDistance(_renWin.GetRenderer().GetActiveCamera().
                             GetDistance());
      userCamera.SetClippingRange(_renWin.GetRenderer().GetActiveCamera().
                                  GetClippingRange());
      userCamera.SetViewUp(_renWin.GetRenderer().GetActiveCamera().GetViewUp());
      userCamera.SetParallelScale(_renWin.GetRenderer().GetActiveCamera().
                                  GetParallelScale());
      _cameras.add(userCamera);
    }
  }
  public SimtkCanvas getRenderWindow()
  {
    return _renWin;
  }
  public void setRenderWindow(SimtkCanvas otherWin)
  {
    _renWin = otherWin;
  }
  void jKeyFrameButton_actionPerformed(ActionEvent e) {
      animation.addFrame();
  }

  void jBackwardButton_actionPerformed(ActionEvent e) {
    _env.setStatus(SimtkSimEnv.PLAYBACK);
    animation.goBack();
  }

  void jFwdButton_actionPerformed(ActionEvent e) {
    _env.setStatus(SimtkSimEnv.PLAYBACK);
    animation.advance();
  }

  void jPlayButton_actionPerformed(ActionEvent e) {
    _env.setStatus(SimtkSimEnv.PLAYBACK);
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        animation.playBack();
      }
    });
  }

  void jPauseButton_actionPerformed(ActionEvent e) {
    _env.setStatus(SimtkSimEnv.PLAYBACK);
    animation.pause();
  }

  void jRewindButton_actionPerformed(ActionEvent e) {
    _env.setStatus(SimtkSimEnv.PLAYBACK);
    animation.rewind();
  }

  void enableAnimationPanel(boolean newState)
  {
    jPlayButton.setEnabled(newState);
    jBackwardButton.setEnabled(newState);
    jFwdButton.setEnabled(newState);
    jAnimationSlider.setEnabled(newState);
    jPauseButton.setEnabled(newState);
    //jSaveAnimationButton.setEnabled(newState);
    jRewindButton.setEnabled(newState);
    jClearButton.setEnabled(newState);
    jSpeedSlider.setEnabled(newState);
  }

  void jSaveAnimationButton_actionPerformed(ActionEvent e) {
    animation.saveToFile("Snapshot");
  }

  void jUseCameraButton_actionPerformed(ActionEvent e) {
    animation.setUseCamera(jUseCameraButton.isSelected());
  }

  void jAnimationType_actionPerformed(ActionEvent e) {
    Object selectedObject = ((JComboBox)e.getSource()).getSelectedItem();
    if (selectedObject instanceof String){
      String selectedString = (String) selectedObject;
      if (selectedString.equalsIgnoreCase(animationTypeStrings[0])){
        if (animation instanceof SimtkDiscreteAnimation)// Nothing has changed
          return;
        else{
          registerAnimation(animation, false);
          animation = new SimtkDiscreteAnimation(_renWin.GetRenderer());
          jKeyFrameButton.setVisible(false);
          registerAnimation(animation, true);
       }
      }
      else if (selectedString.equalsIgnoreCase(animationTypeStrings[1])){
        if (animation instanceof SimtkContinuousAnimation)// Nothing has changed
          return;
        else{
          registerAnimation(animation, false);
          animation = new SimtkContinuousAnimation(_renWin.GetRenderer());
          jKeyFrameButton.setVisible(true);
          registerAnimation(animation, true);
        }
      }
    }
  }

  void jClearButton_actionPerformed(ActionEvent e) {
    animation.reset(true);
  }
}
