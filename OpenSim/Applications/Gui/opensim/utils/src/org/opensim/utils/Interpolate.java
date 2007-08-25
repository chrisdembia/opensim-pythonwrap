package org.opensim.utils;

public class Interpolate
{
   public static double linear(double v1, double v2, double t) { return v1 + t*(v2-v1); }

   public static Vec3 linear(Vec3 v1, Vec3 v2, double t) {
      return new Vec3(v1.get(0)+t*(v2.get(0)-v1.get(0)),
                      v1.get(1)+t*(v2.get(1)-v1.get(1)),
                      v1.get(2)+t*(v2.get(2)-v1.get(2)));
   }

   public static Vec3 spherical(Vec3 v1, Vec3 v2, double t) {
      double dot = Vec3.dot(v1,v2);
      double dot_threshold = 0.9995;
      if(dot > dot_threshold) {
         // Vectors are already close - linearly interpolate and normalize
         Vec3 result = linear(v1,v2,t);
         result.normalize();
         return result;
      }
      if(dot<-1) dot=-1; else if(dot>1) dot=1;
      double theta = Math.acos(dot);
      double st = Math.sin(theta);
      double stt = Math.sin(t*theta);
      double somtt = Math.sin((1-t)*theta);
      return Vec3.add(somtt/st, v1, stt/st, v2);
   }
}
