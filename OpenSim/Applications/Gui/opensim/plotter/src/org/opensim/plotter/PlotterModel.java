/*
 *
 * PlotterModel
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

import java.util.ArrayList;
import java.util.Collection;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import org.jfree.chart.ChartPanel;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman. This class represents the data structure backing the Plotter dialog.
 * Initially it maps to a single JFree.ChartPanel but eventually will correspond to a list 
 * of those.
 */
public class PlotterModel {
   
   ArrayList<ChartPanel> charts=new ArrayList<ChartPanel>(2);
   private ArrayList<Storage>    fileStorages = new ArrayList<Storage>(4); // Data loaded from files
   private ArrayList<Storage>    analysisStorages = new ArrayList<Storage>(4); // Data loaded from analyses
   ArrayList<String>     availableQuantities = new ArrayList<String>(50);
   
   /** Creates a new instance of PlotterModel */
   public PlotterModel() {
   }
   
   public void addFileStorage(Storage aStorage)
   {
      fileStorages.add(aStorage);
   }
   /**
    * Get available quantities to use as a Domain variable
    * source is a boolean used to specify if Analysis or File radio button 
    * have been selected.
    */

   public ArrayList<Storage> getFileStorages() {
      return fileStorages;
   }

   public ArrayList<Storage> getAnalysisStorages() {
      return analysisStorages;
   }

}
