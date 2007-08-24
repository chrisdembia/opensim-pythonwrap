package org.opensim.view;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Vector;
import vtk.vtkCamera;
import vtk.vtkPanel;

// TODO: generalize concept of animatable quantities

public class Camera 
{
   public static class Configuration {
      public double roll = 0;
      public double distance = 1;
      public double viewAngle = 30;
      public double[] position = new double[]{1, 0, 0};
      public double[] focalPoint = new double[]{0, 0, 0};
      public double[] direction = new double[]{1, 0, 0};
      public double[] viewUp = new double[]{0, 1, 0};
      public double[] clippingRange = new double[]{0, 1000};

      private static double dot(double[] vec1, double[] vec2) { return vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2]; }
      private static void normalize(double[] vec) {
         double magnitudeSquared = dot(vec,vec);
         if(magnitudeSquared>1e-8) { double mag = Math.sqrt(magnitudeSquared); vec[0]/=mag; vec[1]/=mag; vec[2]/=mag; }
         else { vec[0] = vec[1] = vec[2] = 0; }
      }
      private static double[] slerp(double[] vec1, double[] vec2, double t) {
         double dot = dot(vec1,vec2);
         double dot_threshold = 0.9995;
         double[] result = new double[]{0,0,0};
         if(dot > dot_threshold) {
            // Vectors are already close - linearly interpolate and normalize
            for(int i=0; i<3; i++) result[i] = vec1[i]+t*(vec2[i]-vec1[i]);
            normalize(result);
            return result;
         }
         if(dot<-1) dot=-1; else if(dot>1) dot=1;
         double theta = Math.acos(dot);
         double st = Math.sin(theta);
         double stt = Math.sin(t*theta);
         double somtt = Math.sin((1-t)*theta);
         for(int i=0; i<3; i++) result[i] = (somtt/st)*vec1[i] + (stt/st)*vec2[i];
         return result;
      }

      public static Configuration interpolate(
            Configuration config1, Configuration config2, double t) 
      {
         //System.out.println("Interpolating with "+t);
         Configuration config = new Configuration();
         config.roll = config1.roll + t * (config2.roll-config1.roll);
         config.viewAngle = config1.viewAngle + t * (config2.viewAngle-config1.viewAngle);
         for(int i=0; i<3; i++) {
            config.focalPoint[i] = config1.focalPoint[i] + t * (config2.focalPoint[i]-config1.focalPoint[i]);
            //config.viewUp[i] = config1.viewUp[i] + t * (config2.viewUp[i]-config1.viewUp[i]);
         }
         config.distance = config1.distance + t * (config2.distance-config1.distance);
         double[] direction = slerp(config1.direction,config2.direction,t);
         for(int i=0; i<3; i++) config.position[i] = config.focalPoint[i] + config.distance * direction[i];
         //config.position[i] = config1.position[i] + t * (config2.position[i]-config1.position[i]);
         for(int i=0; i<2; i++) 
            config.clippingRange[i] = config1.clippingRange[i] + t * (config2.clippingRange[i]-config1.clippingRange[i]);
         return config;
      }

      public String toString() {
         return String.format("rl=%.3f dist=%.3f pos=%.3f,%.3f,%.3f foc=%.3f,%.3f,%.3f dir=%.3f,%.3f,%.3f nea=%.3f far=%.3f ang=%.3f",
               roll,distance,position[0],position[1],position[2],
               focalPoint[0],focalPoint[1],focalPoint[2],
               direction[0],direction[1],direction[2],
               clippingRange[0],clippingRange[1],viewAngle);
      }

      public static Configuration getFromView(vtkPanel panel) {
         vtkCamera currentCamera = panel.GetRenderer().GetActiveCamera();
         Configuration config = new Configuration();
         config.roll = currentCamera.GetRoll();
         config.distance = currentCamera.GetDistance();
         config.viewAngle = currentCamera.GetViewAngle();
         config.position = currentCamera.GetPosition().clone();
         config.focalPoint = currentCamera.GetFocalPoint().clone();
         config.direction = currentCamera.GetDirectionOfProjection().clone();
         config.viewUp = currentCamera.GetViewUp().clone();
         config.clippingRange = currentCamera.GetClippingRange().clone();
         return config;
      }

      public void applyToView(vtkPanel panel) {
         vtkCamera currentCamera = panel.GetRenderer().GetActiveCamera();
         currentCamera.SetPosition(position);
         currentCamera.SetFocalPoint(focalPoint);
         currentCamera.SetViewAngle(viewAngle);
         currentCamera.SetRoll(roll);
         //currentCamera.SetDistance(distance);
         //currentCamera.SetViewUp(viewUp);
         currentCamera.SetClippingRange(clippingRange);
      }

      public void read(BufferedReader reader) throws IOException {
         roll = Double.parseDouble(reader.readLine());
         distance = Double.parseDouble(reader.readLine());
         viewAngle = Double.parseDouble(reader.readLine());
         for(int i=0; i<3; i++) position[i] = Double.parseDouble(reader.readLine());
         for(int i=0; i<3; i++) focalPoint[i] = Double.parseDouble(reader.readLine());
         for(int i=0; i<3; i++) direction[i] = Double.parseDouble(reader.readLine());
         for(int i=0; i<3; i++) viewUp[i] = Double.parseDouble(reader.readLine());
         for(int i=0; i<2; i++) clippingRange[i] = Double.parseDouble(reader.readLine());
      }

      public void write(BufferedWriter writer) throws IOException {
         writer.write(roll+"\n");
         writer.write(distance+"\n");
         writer.write(viewAngle+"\n");
         for(int i=0; i<3; i++) writer.write(position[i]+"\n");
         for(int i=0; i<3; i++) writer.write(focalPoint[i]+"\n");
         for(int i=0; i<3; i++) writer.write(direction[i]+"\n");
         for(int i=0; i<3; i++) writer.write(viewUp[i]+"\n");
         for(int i=0; i<2; i++) writer.write(clippingRange[i]+"\n");
      }
   }

   private class ConfigurationKeyFrame {
      public double time;
      public Configuration config;
      public ConfigurationKeyFrame(double time, Configuration config) { 
         this.time = time; this.config = config;
      }
   }

   private String name;
   private Vector<ConfigurationKeyFrame> configurationKeyFrames = new Vector<ConfigurationKeyFrame>();

   public String getName() { return name; }
   public void setName(String name) { 
      this.name = name; 
      CameraDB.getInstance().fireEvent(new CameraEvent(this, this, CameraEvent.Operation.CameraRenamed));
   }

   public int getNumKeyFrames() { return configurationKeyFrames.size(); }
   public double getKeyFrameTime(int i) { return configurationKeyFrames.get(i).time; }

   public Configuration getKeyFrameConfiguration(int i) { return configurationKeyFrames.get(i).config; }
   public void setKeyFrameConfiguration(int i, Configuration config) { 
      configurationKeyFrames.get(i).config = config; 
      CameraDB.getInstance().fireEvent(new CameraEvent(this, this, CameraEvent.Operation.CameraKeyFrameModified));
   }

   public void addKeyFrame(double time, Configuration config) {
      boolean inserted = false;
      for(int i=0; i<configurationKeyFrames.size();i++) {
         if(configurationKeyFrames.get(i).time>time) {
            configurationKeyFrames.add(i,new ConfigurationKeyFrame(time,config));
            inserted = true;
            break;
         }
      }
      if(!inserted) { configurationKeyFrames.add(new ConfigurationKeyFrame(time,config)); }
      CameraDB.getInstance().fireEvent(new CameraEvent(this, this, CameraEvent.Operation.CameraKeyFrameAdded));
   }
   public void removeKeyFrame(int i) {
      configurationKeyFrames.remove(i);
      CameraDB.getInstance().fireEvent(new CameraEvent(this, this, CameraEvent.Operation.CameraKeyFrameRemoved));
   }

   private double transitionFunction(double t) { return t; }

   public Configuration getConfiguration(double time) {
      if(getNumKeyFrames()==0) return null;
      if(time < getKeyFrameTime(0)) return getKeyFrameConfiguration(0);
      for(int i=0; i<getNumKeyFrames()-1; i++)
         if(getKeyFrameTime(i+1)>time) {
            double t0 = getKeyFrameTime(i);
            double t1 = getKeyFrameTime(i+1);
            return Configuration.interpolate(
                  getKeyFrameConfiguration(i),
                  getKeyFrameConfiguration(i+1),
                  transitionFunction((time-t0)/(t1-t0)));
         }
      return getKeyFrameConfiguration(getNumKeyFrames()-1);
   }

   public void read(BufferedReader reader) throws IOException{
      name = reader.readLine();
      int n = Integer.parseInt(reader.readLine());
      configurationKeyFrames.setSize(0);
      for(int i=0; i<n; i++) {
         double time = Double.parseDouble(reader.readLine());
         Configuration config = new Configuration();
         config.read(reader);
         configurationKeyFrames.add(new ConfigurationKeyFrame(time,config));
      }
   }

   public void write(BufferedWriter writer) throws IOException {
      writer.write(name+"\n");
      writer.write(getNumKeyFrames()+"\n");
      for(int i=0; i<getNumKeyFrames(); i++) {
         writer.write(getKeyFrameTime(i)+"\n");
         getKeyFrameConfiguration(i).write(writer);
      }
   }
}
