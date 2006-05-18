package simtkView;

import java.beans.PropertyVetoException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JInternalFrame;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import opensimModel.Model;
import opensimModel.VisibleObject;
import simtkui.MDIDesktopPane;
import simtkui.SimtkApp;
import simtkuiEvents.SimtkCloseModelEvent;
import simtkuiEvents.SimtkModelRedisplayEvent;
import simtkuiEvents.SimtkVisibilityChangeEvent;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * This is the place to maintain, and update views of the model. We create
 * windows here and associate them to actual models. Book-keeping to map model
 * objects to screen back and forth will be done here.
 */
final public class SimtkViewDB implements Observer{
  SimtkDB _simtkDB = SimtkDB.getInstance();
  static private Hashtable _viewTable = new Hashtable();
  static SimtkMdlInternalFrame _currentFrame=null;

  static {
		System.loadLibrary("vtkCommon");
		System.loadLibrary("vtkCommonJava");
		System.loadLibrary("vtkFiltering");
		System.loadLibrary("vtkFilteringJava");
		System.loadLibrary("vtkfreetype");
		System.loadLibrary("vtkexpat");
		System.loadLibrary("vtkjpeg");
		System.loadLibrary("vtkzlib");
		System.loadLibrary("vtktiff");
		System.loadLibrary("vtkpng");
		System.loadLibrary("vtkftgl");
	    System.loadLibrary("vtkDICOMParser");
 	    System.loadLibrary("vtkIO");
	    System.loadLibrary("vtkIOJava");
	    System.loadLibrary("vtkImaging");
	    System.loadLibrary("vtkGraphics");
	    System.loadLibrary("vtkGraphicsJava");
	    System.loadLibrary("vtkRendering");
	    System.loadLibrary("vtkRenderingJava");
	    System.loadLibrary("vtkHybrid");
    try {
      System.loadLibrary("vtkHybridJava");
    } catch (Throwable e) {
      SimtkApp.displayErrorMessage("cannot load vtkHybrid, skipping...");
    }
    SimtkApp.displayDebugMessage(System.getProperty("java.library.path"));
  }

  public SimtkViewDB() {
     _simtkDB = SimtkDB.getInstance();
     _simtkDB.addObserver(this);// Register with DB as interested party
  }

  /**
   * addSimenvToView: Create a window (SimtkMdlInternalFrame) to display the model into and associate it
   * to the simulation environment though the _viewTable
   *
   * @param env SimtkSimEnv
   *
   */

   static public void addSimenvToView(SimtkSimEnv env) {
     // If model is already loaded do nothing. We don't allow multiple models with same name.

     if (_viewTable.containsKey(env.getModel().getName()))
       return;
     SimtkMdlInternalFrame modelFrame = new SimtkMdlInternalFrame(env);
     SimtkApp.getModelDesktopPane().add(modelFrame);

     ((MDIDesktopPane) SimtkApp.getModelDesktopPane()).tileFramesV();
     _viewTable.put(env.getModel().getName(), modelFrame);
     _currentFrame = modelFrame;
    }

   static public SimtkMdlInternalFrame getFrameForModel(Model mdl) {
     if (!_viewTable.containsKey(mdl.getName()))
       return null;

     return (SimtkMdlInternalFrame) _viewTable.get(mdl.getName());
   }

  /**
   * setProperties updates the visible properties of the specified object to
   * match selectedObject
   *
   * @param mdlName String
   * @param selectedObject VisibleObject
   */
  static public void setProperties(String mdlName, VisibleObject selectedObject)
   {
     SimtkMdlInternalFrame mdlFrame = (SimtkMdlInternalFrame) _viewTable.get(mdlName);
     mdlFrame.updateDisplay(selectedObject);
   }

   static public void write2Tiff(String mdlName, String fullFileName)
   {
     SimtkApp.getModelDesktopPane().validate();
     if (!_viewTable.containsKey(mdlName))
       return;
     SimtkMdlInternalFrame mdlFrame =  (SimtkMdlInternalFrame) _viewTable.get(mdlName);
     mdlFrame.write2TiffFile(fullFileName);
     SimtkApp.displayInfoMessage("Saved snapshot of model "+mdlName+" to tiff file "+fullFileName);
   }

  /**
   * getCurrentModelName
   *
   * @return String
   */
  public static String getCurrentModelName() {
    // This's a workaround a bug that caused removed JInternalFrames to stay selected.
    JInternalFrame[] allFrames = SimtkApp.getModelDesktopPane().getAllFrames();
    if (allFrames.length==0)
      return null;

    _currentFrame = (SimtkMdlInternalFrame) SimtkApp.getModelDesktopPane().getSelectedFrame();
    if (_currentFrame==null){
      // Marke first frame in the list as selected and continue
      try {
        allFrames[0].setSelected(true);
        _currentFrame = (SimtkMdlInternalFrame) SimtkApp.getModelDesktopPane().getSelectedFrame();
      }
      catch (PropertyVetoException ex) {
      }
    }
    return _currentFrame.getModelName();
  }

  /**
   * update is the call back function when a change in the model needs to be
   * reflected in one of the displayed windows/frames. Observavle will be passed
   * in as the whole DB
   * arg will be an event with anough info to execute the command. non
   * ViewSpecific commands should be ignored.
   * @todo possibly break the database into multiple observable objects so that
   * the ViewDB doesn't have to disambiguate based on model
   *
   * @param o Observable
   * @param arg Object
   */
  public void update(Observable o, Object arg) {
    if (arg instanceof SimtkCloseModelEvent){
      SimtkCloseModelEvent mdlRemoveEvent = (SimtkCloseModelEvent) arg;
      SimtkMdlInternalFrame mdlFrame = (SimtkMdlInternalFrame) _viewTable.remove(mdlRemoveEvent.getModelName());
      try {
        mdlFrame.setSelected(false);
      }
      catch (PropertyVetoException ex) {
      }
      SimtkApp.getModelDesktopPane().remove(mdlFrame);
      SimtkApp.getModelDesktopPane().repaint();
      Enumeration frames = _viewTable.elements();
      if (frames.hasMoreElements()){
        _currentFrame = (SimtkMdlInternalFrame) frames.nextElement();
      }
      else
        _currentFrame=null;
    }
    else if (arg instanceof SimtkVisibilityChangeEvent) {
      SimtkVisibilityChangeEvent visChangeEvent = (SimtkVisibilityChangeEvent) arg;
      SimtkMdlInternalFrame mdlFrame = (SimtkMdlInternalFrame) _viewTable.get(
          visChangeEvent.getModelName());
      mdlFrame.updateDisplay(visChangeEvent.getObject());
    }
    else if (arg instanceof SimtkModelRedisplayEvent) {
      SimtkModelRedisplayEvent visChangeEvent = (SimtkModelRedisplayEvent) arg;
      SimtkMdlInternalFrame mdlFrame = (SimtkMdlInternalFrame) _viewTable.get(
      visChangeEvent.getModelName());
      if (visChangeEvent.reDraw())
        mdlFrame.recreateDisplay();
      else
        mdlFrame.updateDisplay();
    }
    else
      return;
  }

}
