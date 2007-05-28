/*
 *
 * ModelGUIPrefs
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

/**
 *
 * @author Ayman. A class to encapsulate GUI preferences for a specific model that are not saved with 
 * the model's .osim file
 */

public class ModelSettings {
   private Vector<ModelPose> poses=new Vector<ModelPose>();
   
   public ModelSettings()
   {
   }
   public void addPose(ModelPose newPose)
   {
      getPoses().add(newPose);
      System.out.println("Adding pose:"+newPose.getPoseName());
   }
   public ModelPose getPose(String name)
   {
      for(int i=0; i<getPoses().size(); i++){
         if (name.compareToIgnoreCase(getPoses().get(i).getPoseName())==0){
            return getPoses().get(i);
         }
      }
      return null;
   }
   public int getNumPoses()
   {
      //System.out.println("Found"+ getPoses().size()+"poses");      
      return getPoses().size();
   }

   public Vector<ModelPose> getPoses() {
      return poses;
   }

   public void setPoses(Vector<ModelPose> poses) {
      this.poses = poses;
   }

   public boolean containsPose(String newName) {
      boolean found=false;
      for(int i=0; i<poses.size() && !found; i++){
         found= (poses.get(i).getPoseName().equalsIgnoreCase(newName));
      }
      return found;
   }

   public void deletePoses(Vector<ModelPose> posesToDelete) {
      poses.removeAll(posesToDelete);
   }
}
