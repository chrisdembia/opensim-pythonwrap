package org.opensim.utils;

public class Vec3
{
   private double[] vec = new double[]{0,0,0};

   public Vec3() { }
   public Vec3(double x, double y, double z) { vec[0] = x; vec[1] = y; vec[2] = z; }
   public Vec3(double[] vec) { this.vec = vec.clone(); }

   public double[] get() { return vec; }
   public double get(int i) { return vec[i]; }

   public void scale(double a) { vec[0]*=a; vec[1]*=a; vec[2]*=a; }

   public double magnitudeSquared() { return dot(this,this); }
   public double magnitude() { return Math.sqrt(magnitudeSquared()); }

   public void normalize() {
      double magSqr = magnitudeSquared();
      if(magSqr > 1e-8) scale(1/Math.sqrt(magSqr));
      else { vec[0]=vec[1]=vec[2]=0.0; }
   }

   public static double dot(Vec3 v1, Vec3 v2) { return v1.vec[0]*v2.vec[0] + v1.vec[1]*v2.vec[1] + v1.vec[2]*v2.vec[2]; }
   public static Vec3 add(double a, Vec3 v1, double b, Vec3 v2) { 
      return new Vec3(a*v1.vec[0]+b*v2.vec[0],
                      a*v1.vec[1]+b*v2.vec[1],
                      a*v1.vec[2]+b*v2.vec[2]);
   }

   public String toString() { return String.format("%.3f,%.3f,%.3f",vec[0],vec[1],vec[2]); }
}
