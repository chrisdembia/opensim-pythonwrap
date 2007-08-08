/*
 *
 * ModelPose
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view;

import java.util.Vector;
import org.opensim.modeling.*;

/**
 *
 * @author Ayman. A class representing a model pose (set of coordinates)
 */
public class ModelPose {
   private String poseName;
   /*
    * Using parallel arrays instead of one array of <name,value> pairs to minimize
    * overhead but this decision can be revisited if a generic nameValue pairing is needed.
    */
   private Vector<String> coordinateNames = new Vector<String>(4);
   private Vector<Double> coordinateValues = new Vector<Double>(4);
   /** Creates a new instance of ModelPose */
   public ModelPose() {
   }

   public ModelPose(CoordinateSet coords, String name) {
      this(coords, name, false);
   }

   public ModelPose(CoordinateSet coords, String name, boolean isDefault) {
      setPoseName(name);
      for(int i=0; i< coords.getSize(); i++){
         AbstractCoordinate coord = coords.get(i);
         getCoordinateNames().add(coord.getName());
         if (isDefault)
            getCoordinateValues().add(coord.getDefaultValue());
         else
            getCoordinateValues().add(coord.getValue());
      }
   }
   public Vector<Double> getCoordinateValues() {
      return coordinateValues;
   }

   public Vector<String> getCoordinateNames() {
      return coordinateNames;
   }

   public String getPoseName() {
      return poseName;
   }

   public void setPoseName(String poseName) {
      this.poseName = poseName;
   }

   public void setCoordinateNames(Vector<String> coordinateNames) {
      this.coordinateNames = coordinateNames;
   }

   public void setCoordinateValues(Vector<Double> coordinateValues) {
      this.coordinateValues = coordinateValues;
   }

   /** 
    * toString function useful for displaying ModelPose objects in a list
    */
   public String toString() {
      return getPoseName();
   }
   
   
 }
