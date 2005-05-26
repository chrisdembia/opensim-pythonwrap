package simtkView.animation;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.swing.BoundedRangeModel;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;

import vtk.vtkActor;
import vtk.vtkActorCollection;
import vtk.vtkCamera;
import vtk.vtkRenderer;
import vtk.vtkTransform;

public class SimtkContinuousAnimation
    extends SimtkAnimation {
  double startTime, endTime, timeStep, currentTime;
  boolean inPlayBackMode = false;
  static String[] reservedChannelNames = {
      "Camera.Position.x", "Camera.Position.y", "Camera.Position.z",
      "Camera.Focus.x", "Camera.Focus.y", "Camera.Focus.z",
      "Camera.Distance",
      "Camera.ClippingRange.min", "Camera.ClippingRange.max"};
  Hashtable actorsChannels;
  boolean upToDate = false;
  public SimtkContinuousAnimation(vtkRenderer renderer) {
    super(renderer);
    buildChannels(); upToDate=false;
  }

  /**
   * generateFrames
   */
  public void addKeyFrames() {

    for (int i = 0; i < keyFrames.size(); i++) {
      SimtkAnimationFrame frame = ( (SimtkAnimationFrame) keyFrames.get(i));
      frame.print();
      // Update Builtin channels from frame
      for (int j = 0; j < reservedChannelNames.length; j++) {
        String channelName = reservedChannelNames[j];
        Object channel = namesToChannels.get(channelName);
        ( (SimtkAnimationChannelScalar) channel).addFrame(frame.simulationTime,
            frame.getChannelValue(channelName));
      }
      Enumeration actorsEnum = actorsChannels.keys();
      // Get actors from animation frame and create channels for them if they don't exist.
      while(actorsEnum.hasMoreElements()) {
        vtkActor anActor = (vtkActor) actorsEnum.nextElement();
        SimtkAnimationChannelActor actorChannel = (SimtkAnimationChannelActor) actorsChannels.get(anActor);
        actorChannel.addFrame(frame.simulationTime, frame.getActorTransform(anActor));
       }
    }
  }

  public void reset(boolean resetFrames) {
    super.reset(resetFrames);
    buildChannels();
    currentTime = startTime;
    upToDate = false;
  }

  /**
   * goBack
   */
  public void goBack() {
    if (currentTime > startTime)
      currentTime -= timeStep;
    gotoTime(currentTime, useCamera);
  }

  /**
   * advance
   */
  public void advance() {
    if (currentTime < endTime)
      currentTime += timeStep;
    gotoTime(currentTime, useCamera);
  }

  public void addFrame(double simulationTime) {
    super.addFrame(simulationTime);
    /**
     * This works only when we're not interpolating anything, otherwise
     * number of actual frames is normally much larger than number of key frames
     */
    upToDate = false;
  }
  /**
   * playBack
   */
  public void playBack() {
    if (!upToDate){
      setupAnimation();
      addKeyFrames();
      upToDate = true;
    }
    if (currentTime >= endTime)
      currentTime = startTime;

    displayTimer = new Timer(animationSpeed, new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        gotoTime(currentTime, useCamera);
        if (currentTime < endTime)
          currentTime += timeStep;
        else {
          displayTimer.stop();
          inPlayBackMode = false;
        }
      }
    });
    displayTimer.start();
    inPlayBackMode = true;

  }

  /**
   * setupAnimation
   */
  private void setupAnimation() {
    SimtkAnimationFrame frame = (SimtkAnimationFrame) keyFrames.getFirst();
    startTime = frame.simulationTime;
    frame = (SimtkAnimationFrame) keyFrames.getLast();
    endTime = frame.simulationTime;
    timeStep = (endTime - startTime) / numFrames;
    vtkActorCollection actors = renderer.GetActors();
    actors.InitTraversal();
    for (int i = 0; i < actors.GetNumberOfItems(); i++) {
      vtkActor anActor = actors.GetNextActor();
      if (!actorsChannels.contains(anActor))
        actorsChannels.put(anActor,
                           new SimtkAnimationChannelActor(anActor.toString(),
            anActor));
    }
    sliderModel.removeChangeListener(this);
    sliderModel.setMaximum(numFrames - 1);
    sliderModel.setMinimum(0);
    sliderModel.setValue(0);
    sliderModel.addChangeListener(this);
  }

  /**
   * saveToFile
   *
   * @param baseFileName String
   */
  public void saveToFile(String baseFileName) {
  }

  /**
   * resetChannels
   */
  private void resetChannels() {
    Enumeration channels = namesToChannels.elements();
    while (channels.hasMoreElements()) {
      Object obj = channels.nextElement();
      SimtkAnimationChannel channel = (SimtkAnimationChannel) obj;
      channel.clear();
    }
  }

  /**
   * stateChanged
   *
   * @param e ChangeEvent
   */
  public void stateChanged(ChangeEvent e) {
    BoundedRangeModel theSlider = (BoundedRangeModel) e.getSource();
    if (theSlider == sliderModel) {
      if (theSlider.getValueIsAdjusting())
        return;
      if (!inPlayBackMode){// if change made by the code rather than user do nothing here
        double currentTimePercent = ((double)(theSlider.getValue()- theSlider.getMinimum()))/(theSlider.getExtent());
        currentTime = startTime+ currentTimePercent*theSlider.getExtent();
        gotoTime(currentTime, useCamera);
      }
    }
    else if (theSlider == speedModel) {
      if (theSlider.getValueIsAdjusting())
        return;
      animationSpeed = theSlider.getValue();
    }
  }

  /**
   * rewind
   */
  public void rewind() {
    currentTime = startTime;
    gotoTime(currentTime, useCamera);
  }

  /**
   * gotoFrame
   *
   * @param currentFrame int
   */
  private void gotoTime(double simulationTime, boolean useSavedCamera) {
    SimtkAnimationFrame nextFrame = computeFrameAtTime(simulationTime,
        useSavedCamera);
    nextFrame.setOn(renderer, useSavedCamera);
    //nextFrame.print();
    int sliderValue = (int) ( (simulationTime - startTime) / timeStep);
    sliderModel.setValue(sliderValue);
    simtkui.SimtkApp.displayInfoMessage("Time="+simulationTime+"\n");

    renderer.GetRenderWindow().Render();
  }

  /**
   * computeFrameAtTime
   *
   * @param simulationTime double
   * @param useSavedCamera boolean
   * @return SimtkAnimationFrame
   *
   * @todo avoid allocation/creation of a new SimtkAnimationFrame everytime evaluation is needed
   */
  private SimtkAnimationFrame computeFrameAtTime(double simulationTime,
                                                 boolean useSavedCamera) {
    SimtkAnimationFrame currentFrame = new SimtkAnimationFrame(simulationTime);
    // Interpolate camera position
    if (useSavedCamera) {
      vtkCamera interpolatedCamera = new vtkCamera();
      double[] interpolatedValues = new double[reservedChannelNames.length];
      for (int i = 0; i < reservedChannelNames.length; i++) {
        Object obj = ( (SimtkAnimationChannelScalar) namesToChannels.get(
            reservedChannelNames[i])).evaluate(simulationTime);
        interpolatedValues[i] = ( (Double) obj).doubleValue();
      }
      interpolatedCamera.SetPosition(interpolatedValues[0],
                                     interpolatedValues[1],
                                     interpolatedValues[2]);
      interpolatedCamera.SetFocalPoint(interpolatedValues[3],
                                       interpolatedValues[4],
                                       interpolatedValues[5]);
      interpolatedCamera.SetDistance(interpolatedValues[6]);
      interpolatedCamera.SetClippingRange(interpolatedValues[7],
                                          interpolatedValues[8]);
      currentFrame.setCamera(interpolatedCamera);
    }
    else
      currentFrame.setCamera(renderer.GetActiveCamera());
      // interpolate actors:
      // Scan renderer for actors and for each one if not in actorsChannels create a channel for it.
      /*
       * @todo check situation where renderer's set of actors is not fixed throughout the simulation/snapshots
       */
    vtkActorCollection actors = renderer.GetActors();
    actors.InitTraversal();
    for (int i = 0; i < actors.GetNumberOfItems(); i++) {
      vtkActor anActor = actors.GetNextActor();
      Object obj = ( (SimtkAnimationChannelActor) actorsChannels.get(anActor)).
          evaluate(simulationTime);

      currentFrame.setActorTransform(anActor, (vtkTransform)obj);
    }
    return currentFrame;
  }

  private void buildChannels() {
    for (int channel = 0; channel < reservedChannelNames.length; channel++) {
      namesToChannels.put(reservedChannelNames[channel],
                          new SimtkAnimationChannelScalar(reservedChannelNames[
          channel]));
    }
    actorsChannels = new Hashtable();

  }
}
