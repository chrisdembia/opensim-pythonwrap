package simtkView.animation;

import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Observable;
import java.util.Observer;

import javax.swing.BoundedRangeModel;
import javax.swing.DefaultBoundedRangeModel;
import javax.swing.Timer;
import javax.swing.event.ChangeListener;

import simtkCore.SimtkSimEnv;
import simtkuiEvents.SimtkSimEnvStateChangeEvent;
import vtk.vtkCamera;
import vtk.vtkRenderer;

/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: </p>
 * This class abstracts the notion of an animation. It offers the ability to
 * record key frames while a simulation is running and playing them back at any
 * point. KeyFrames are stored as a linked list and initially are not visible
 * explicitly though this functionality should easily be added.
 *
 *  One object of this type is instantiated per model window. It extends Observable
 *  since we need to enable/disable the animation control buttons based on the availability
 *  keyFrames and where the animation is along the keyframe list. It's also an Observer since it tracks
 *  environment changes so that it can automatically start recording.
 *
 * @author Ayman Habib
 * @version 1.0
 */
public abstract class SimtkAnimation
    extends Observable
    implements Observer, ChangeListener {

  /** Actual Keyframes maintained as a LinkedList */
  LinkedList keyFrames = new LinkedList();

  /** A table that maps animation channel names to Simulation Channels */
  Hashtable namesToChannels = new Hashtable();

  /** Renderer for the window in which animation is performed */
  vtkRenderer renderer;

  /** Support/model for an animation slider */
  BoundedRangeModel sliderModel = new DefaultBoundedRangeModel();

  /** Support for a speed control slider */
  BoundedRangeModel speedModel = new DefaultBoundedRangeModel();
  /** Timer object for playback of animation to keep the GUI live and control animation speed */
  Timer displayTimer;
  final static int SPEED = 10;


  final static int DEFAULT_FRAMES = 200;
  int numFrames = DEFAULT_FRAMES;

  /** USer selected animation speed (time between display updates .. Smaller is FASTER) */
  int animationSpeed;

  /** Whether keyframes are user controlled or automatic during simuation default to true */
  // boolean autoKeyFrames;
  /** Whether to interpolate and keep track of camera position during playback default to true */
  boolean useCamera;

  String[] actorChannels = {".tx", ".ty", ".tz", ".rx", ".ry", ".rz"};
  /**
   * SimtkAnimation constructor
   *
   * @param renderer vtkRenderer is the renderer associated with the vtk Window
   *   in which we display the animation
   */
  public SimtkAnimation(vtkRenderer renderer) {
    reset(true);
    this.renderer = renderer;
    sliderModel.addChangeListener(this);
    speedModel.setMaximum(100);
    speedModel.setMinimum(0);
    speedModel.addChangeListener(this);
    animationSpeed = SPEED;
    // autoKeyFrames = true;
    useCamera = true;
  }

  public synchronized int getAvailableFrames() {
    return keyFrames.size();
  }

  public BoundedRangeModel getSliderModel() {
    return sliderModel;
  }

  public BoundedRangeModel getSpeedModel() {
    return speedModel;
  }

  public void setUseCamera(boolean useCamera) {
    this.useCamera = useCamera;
  }

  public boolean getUseCamera() {
    return useCamera;
  }

  /**
   * update
   *
   * @param o Observable
   * @param arg Object
   */
  public void update(Observable o, Object arg) {
    SimtkSimEnv env = (SimtkSimEnv) o;
    if (arg != null && arg instanceof SimtkSimEnvStateChangeEvent) {
      SimtkSimEnvStateChangeEvent evnt = (SimtkSimEnvStateChangeEvent) arg;
      int oldState = evnt.getOldState();
      int newState = evnt.getNewState();
      if (oldState == SimtkSimEnv.READY && newState == SimtkSimEnv.STARTED) {
        reset(true);
        SimtkAnimationAvailableEvent updateEvent = new
            SimtkAnimationAvailableEvent(this, false);
        setChanged();
        this.notifyObservers(updateEvent);
      }
      if (oldState == SimtkSimEnv.STARTED && newState == SimtkSimEnv.READY) {
        SimtkAnimationAvailableEvent updateEvent = new
            SimtkAnimationAvailableEvent(this, true);
        setChanged();
        this.notifyObservers(updateEvent);
      }
    }
  }

  /**
   * addFrame
   *
   */
  public synchronized void addFrame(double simulationTime) {
    vtkCamera avtkCamera = renderer.GetActiveCamera();
    keyFrames.addLast(new SimtkAnimationFrame(avtkCamera, renderer, simulationTime));
  }

  /**
   * addFrame. Called from screen capture of the animation window. No associated
   * time is assumed
   */
  public synchronized void addFrame() {
    addFrame(keyFrames.size());
  }

  /**
   * goBack
   */
  public abstract void goBack();

  public abstract void advance();

  public abstract void rewind();
  /**
   * pause
   */
  public void pause() {
    if (displayTimer != null) {
      displayTimer.stop();
    }
  }


  public void reset(boolean resetFrames) {
    if (resetFrames)
      keyFrames.clear();
  }

  /**
   * playBack
   */
  public abstract void playBack();

  public abstract void saveToFile(String baseFileName);
}
