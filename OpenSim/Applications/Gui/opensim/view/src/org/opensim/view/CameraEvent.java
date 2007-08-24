package org.opensim.view;

import java.util.EventObject;

public class CameraEvent extends EventObject {

   public enum Operation{AllDataChanged, CameraAdded, CameraRemoved, CameraRenamed, CameraKeyFrameAdded, CameraKeyFrameRemoved, CameraKeyFrameModified};

   private Operation op;
   private Camera camera;

   public CameraEvent(Object source, Camera camera, Operation op) {
      super(source);
      this.op = op;
      this.camera = camera;
   }

   public Operation getOperation() { return op; }
   public Camera getCamera() { return camera; }
}
