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
import javax.swing.JPanel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman. This class represents the data structure backing the Plotter dialog.
 * Initially it maps to a single JFree.ChartPanel but eventually will correspond to a list 
 * of those.
 */
public class PlotterModel {
   
   private ArrayList<Storage>    fileStorages = new ArrayList<Storage>(4); // Data loaded from files
   private ArrayList<Storage>    analysisStorages = new ArrayList<Storage>(4); // Data loaded from analyses
   ArrayList<String>     availableQuantities = new ArrayList<String>(50);
   ArrayList<Plot>     availablePlots = new ArrayList<Plot>(2);
   private int currentPlotIndex=0;
   private PlotTreeModel              plotTreeModel = new PlotTreeModel();   // Tree on the right
   
   /** Creates a new instance of PlotterModel */
   public PlotterModel() {
         Plot figure = new Plot("Title", "x-label", "y-label");
         availablePlots.add(0, figure);
         plotTreeModel.addPlot(figure);
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

   public ArrayList<Storage> getLoadedFileStorages() {
      return fileStorages;
   }

   public ArrayList<Storage> getLoadedAnalysisStorages() {
      return analysisStorages;
   }
   /**
    * Add a curve to the PlotterModel. If a new figure is created as a side effect of this it's returned
    * otherwise null is returned to indicate that no new Panel was created. The actual addition should be
    * done by the caller JPlotterFrame
    */
   PlotCurve addCurve(String title, PlotCurveSettings plotCurveSettings, 
           Storage storage1, String string1, 
           Storage storage2, String string2) throws PlotterException {

      Plot currentPlot = availablePlots.get(currentPlotIndex);
      PlotCurve newCurve = new PlotCurve(plotCurveSettings, storage1, string1, storage2, string2);
      currentPlot.add(newCurve);
      
      //currentPlot.dChart.getXYPlot().addAnnotation(new XYTextAnnotation("text", ));
      plotTreeModel.addPlotCurveToTree(newCurve);
      currentPlot.setTitle(title);
      return newCurve;
   }

   TreeModel getPlotTreeModel() {
      return plotTreeModel;
   }
   /**
    * Delete all curves from a figure 
    * Delete the panel too?
    */
   void deletePlot(Plot figToDelete) {
      PlotNode figNode = plotTreeModel.findPlotNode(figToDelete);
      figNode.removeFromParent();
      
   }

   void deleteCurve(PlotCurve cvToDelete) {
      PlotNode figNode = plotTreeModel.findPlotNode(cvToDelete);
      if (figNode ==null)  // Owner figure might have been deleted already
         return;
      // Actual object deletion
      ((Plot)figNode.getUserObject()).deleteCurve(cvToDelete);
      // Removal from tree
      PlotCurveNode cNode = plotTreeModel.findCurveNode(cvToDelete);
      figNode.remove(figNode.getIndex(cNode));
      plotTreeModel.reload((TreeNode) figNode);
      
   }

   Plot getCurrentPlot()
   {
      return availablePlots.get(currentPlotIndex);
   }

   void updateCurve(PlotCurve currentCurve, String title, 
           PlotCurveSettings plotCurveSettings, 
           Storage domainStorage, String domainColumnName, 
           Storage rangeStorage, String rangeColumnName) throws PlotterException {
      
      Plot currentPlot = availablePlots.get(currentPlotIndex);
      currentPlot.setTitle(title);
      currentCurve.update(title, plotCurveSettings, domainStorage, domainColumnName, rangeStorage, rangeColumnName);
      // Find path and mark it as changed to update the tree 
       TreeNode[] path=plotTreeModel.getPathToRoot((TreeNode) plotTreeModel.getRoot());
       PlotCurveNode cNode = plotTreeModel.findCurveNode(currentCurve);
       PlotNode fNode = (PlotNode)((TreeNode)cNode).getParent();
       plotTreeModel.reload(fNode);
   }

   Plot getPlotForCurve(PlotCurve cv) {
      PlotCurveNode cNode = plotTreeModel.findCurveNode(cv);
      PlotNode fNode = (PlotNode)((TreeNode)cNode).getParent();
      return ((Plot)fNode.getUserObject());
   }
}
