/*
 *
 * ModelPose
 * Author(s): Ayman Habib
 * Copyright (c)  2005-2006, Stanford University, Ayman Habib
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
