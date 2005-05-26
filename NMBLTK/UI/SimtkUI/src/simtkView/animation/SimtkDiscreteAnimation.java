package simtkView.animation;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoundedRangeModel;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;

import vtk.vtkJPEGWriter;
import vtk.vtkRenderer;
import vtk.vtkWindowToImageFilter;

public class SimtkDiscreteAnimation
    extends SimtkAnimation {
  /** Current animation frame */
  int currentFrame;
  boolean inPlayBackMode = false;

  public SimtkDiscreteAnimation(vtkRenderer renderer) {
    super(renderer);
  }

  /**
   * gotoFrame
   *
   * @param currentFrame int
   */
  private void gotoFrame(int frame, boolean useSavedCamera) {
  	if (keyFrames.size() <= frame)
  		return;
  	
    SimtkAnimationFrame nextFrame = (SimtkAnimationFrame) keyFrames.get(frame);
    nextFrame.setOn(renderer, useSavedCamera);
    sliderModel.setValue(frame);

    renderer.GetRenderWindow().Render();
    if (frame == 0) {
      SimtkAnimationBoundsReached updateEvent = new SimtkAnimationBoundsReached(this, true);
      setChanged();
      this.notifyObservers(updateEvent);
    }
    else if (frame == numFrames - 1) {
      SimtkAnimationBoundsReached updateEvent = new SimtkAnimationBoundsReached(this, false);
      setChanged();
      this.notifyObservers(updateEvent);
    }
  }

  /**
   * addFrame
   *
   */
  public void addFrame(double simulationTime) {
    super.addFrame(simulationTime);
    /**
     * This works only when we're not interpolating anything, otherwise
     * number of actual frames is normally much larger than number of key frames
     */
    numFrames = keyFrames.size();
    sliderModel.removeChangeListener(this);
    sliderModel.setMaximum(numFrames - 1);
    sliderModel.setValue(numFrames - 1);
    sliderModel.addChangeListener(this);
  }

  public void goBack() {
    if (currentFrame >= 1) {
      currentFrame--;
      gotoFrame(currentFrame, useCamera);
    }
  }

  /**
   * advance
   */
  public void advance() {
    if (currentFrame < numFrames - 1) {
      currentFrame++;
      gotoFrame(currentFrame, useCamera);
    }
  }

  public void rewind() {
    currentFrame = 0;
    gotoFrame(currentFrame, useCamera);
  }

  public void reset(boolean resetFrames) {
    super.reset(resetFrames);
    currentFrame = 0;
  }
  public void playBack() {

    // If already at the end, restart.
    if (currentFrame == numFrames - 1)
      currentFrame = 0;
    //renderer.GetRenderWindow().DoubleBufferOn();

    displayTimer = new Timer(animationSpeed, new ActionListener() {
      public void actionPerformed(ActionEvent e) {
       //renderer.GetRenderWindow().SetSwapBuffers(1);
       gotoFrame(currentFrame, useCamera);
        if (currentFrame < numFrames - 1)
          currentFrame++;
        else {
     	  displayTimer.stop();
    	  inPlayBackMode = false;
        }
      }
    });
    displayTimer.start();
    inPlayBackMode = true;
  }

  public void saveToFile(String baseFileName) {
    sliderModel.setMaximum(numFrames - 1);
    // If already at the end, restart.
    if (currentFrame == numFrames - 1)
      currentFrame = 0;

    for (int frame = currentFrame; frame <= numFrames - 1; frame++) {
      gotoFrame(frame, useCamera);
      vtkWindowToImageFilter w2i = new vtkWindowToImageFilter();
      w2i.SetInput(renderer.GetRenderWindow());
      vtkJPEGWriter writer = new vtkJPEGWriter();
      writer.SetInput(w2i.GetOutput());
      writer.SetFileName(baseFileName + "." + frame + ".jpg");
      writer.Write();
    }
  }
  public void pause() {
    super.pause();
    inPlayBackMode = false;
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
        currentFrame = theSlider.getValue();
        gotoFrame(currentFrame, useCamera);
      }
    }
    else if (theSlider == speedModel) {
      if (theSlider.getValueIsAdjusting())
        return;
      animationSpeed = theSlider.getValue();
    }
  }

}
