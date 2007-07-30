/*
 *
 * PlotterSourceAnalysis
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
package org.opensim.plotter;

import java.util.Vector;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman. A class representing the Source=Model/Analysis radio button
 */
public class PlotterSourceAnalysis implements PlotterSourceInterface {
   
   private String[] allAvailable;
   private boolean[] selectionStatus;
   private String displayName;
   private Storage   storage;
   private Model model;
   private boolean live;    // Flag indicating whether the storage underneath is live 
   /** Creates a new instance of PlotterSourceAnalysis */
   public PlotterSourceAnalysis(Model aModel, Storage storage, String modelAnalysisString) {
      model = aModel;
      this.storage = storage;
      live=true;
      displayName = modelAnalysisString;
      ArrayStr labels = storage.getColumnLabels();
      allAvailable = new String[labels.getSize()];
      selectionStatus = new boolean[labels.getSize()];
      for(int i=0; i<labels.getSize(); i++){
         allAvailable[i]=labels.getitem(i);
         selectionStatus[i]=false;
      }
      //System.out.println("Created PlotterSourceAnalysis DisplayName="+displayName);
   }

   public String[] getAllQuantities() {
      return allAvailable;
   }

   public Vector<String> getSelectedQuantities() {
      int countSelected = 0;
      Vector<String> selectedVec = new Vector<String>(4);
      for(int i=0; i<selectionStatus.length ;i++){
         if (selectionStatus[i]){
               countSelected += 1;
               selectedVec.add(allAvailable[i]);
         }
      }
      return selectedVec;
   }

   public boolean[] filterByRegularExprssion(String regex) throws PatternSyntaxException {
       Pattern p = Pattern.compile(regex);
       
      for(int i=0; i<allAvailable.length ;i++)
       selectionStatus[i] = p.matcher(allAvailable[i]).matches();
       
       return selectionStatus;
   }

   public boolean[] toggleItemSelection(String item) {      
      for(int i=0; i<allAvailable.length ;i++){
         if (allAvailable[i].compareTo(item)==0)
            selectionStatus[i] = !selectionStatus[i];
      }
      return getSelectionStatus();
   }

   public boolean[] getSelectionStatus() {
      return selectionStatus;
   }

   public void setSelectionStatus(boolean[] selectionStatus) {
      this.selectionStatus = selectionStatus;
   }

   public String getDisplayName() {
      return displayName;
   }

   public Storage getStorage() {
      return storage;
   }

    public void clearSelectionStatus() {
    }

    public boolean isStorageLive() {
        return live;
    }

    public void setStorageLive(boolean b) {
        live=b;
        if (b==false)
            storage=null;
    }
    public String toString() {
        return storage.getName();
    }

   Model getModel() {
      return model;
   }

   public double getDefaultMin(String domainName) {
      AbstractCoordinate coord = model.getDynamicsEngine().getCoordinateSet().get(domainName);
      if (coord==null)
         return 0.0;
      double min = coord.getRangeMin();
      if (coord.getMotionType() == AbstractDof.DofType.Rotational){
         min = Math.toDegrees(min);
      }
      return min;
   }

   public double getDefaultMax(String domainName) {
      AbstractCoordinate coord = model.getDynamicsEngine().getCoordinateSet().get(domainName);
      if (coord==null)
         return 1.0;
      double max = coord.getRangeMax();
      if (coord.getMotionType() == AbstractDof.DofType.Rotational){
         max = Math.toDegrees(max);
      }
      return max;
   }

   public boolean isValidName(String columnName) {
      for(int i=0;i<allAvailable.length;i++){
         if (allAvailable[i].compareTo(columnName)==0)
            return true;
      }
      return false;
   }
}
