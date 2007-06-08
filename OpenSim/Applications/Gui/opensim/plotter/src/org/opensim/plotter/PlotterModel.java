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
import java.util.Hashtable;
import java.util.Vector;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import org.opensim.modeling.AbstractCoordinate;
import org.opensim.modeling.Analysis;
import org.opensim.modeling.AnalysisSet;
import org.opensim.modeling.AnalyzeTool;
import org.opensim.modeling.ArrayStorage;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.modeling.MuscleAnalysis;
import org.opensim.modeling.StateVector;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman. This class represents the data structure backing the Plotter dialog.
 * Initially it maps to a single JFree.ChartPanel but eventually will correspond to a list 
 * of those.
 */
public class PlotterModel {
   // All sources (Storages) are kept here as a linear list
   private ArrayList<PlotterSourceInterface>    sources = new ArrayList<PlotterSourceInterface>(4); // Data loaded from files
   ArrayList<String>     availableQuantities = new ArrayList<String>(50);
   ArrayList<Plot>     availablePlots = new ArrayList<Plot>(2);
   private int currentPlotIndex=0;
   private PlotTreeModel              plotTreeModel = new PlotTreeModel();   // Tree on the right
   private Vector<Model> loadedModels = new Vector<Model>(4);
   Hashtable<Model, AnalyzeTool> models2AnalyzeToolInstances = new Hashtable<Model, AnalyzeTool>(4);
   Vector refs = new Vector(10);
   /** Creates a new instance of PlotterModel */
   public PlotterModel() {
         Plot figure = new Plot("Title", "x-label", "y-label");
         availablePlots.add(0, figure);
         plotTreeModel.addPlot(figure);
   }
   
   public void addFile(String filename)
   {
      sources.add(new PlotterSourceFile(filename));
   }
   
    public void addModel(Model aModel)
    {
        if (loadedModels.contains(aModel))
            return;
        AnalysisSet analyses=aModel.getAnalysisSet();
        
        // If model does not have std analyses we'll add them here
        if (analyses.get("MuscleAnalysis")==null){
           Analysis muscleAnalysis = new MuscleAnalysis(aModel);
           analyses.append(muscleAnalysis);
           refs.add(muscleAnalysis);
        }
        /*
         if (analyses.get("MomentArmAnalysis")==null){
            analyses.append(new MomentArmAnalysis(aModel));
        }
        */   
        for(int i=0; i<analyses.getSize(); i++){
            Analysis a = analyses.get(i);
            ArrayStorage storages = a.getStorageList();
            for(int j=0; j<storages.getSize(); j++){
               Storage str = storages.get(j);
               sources.add(new PlotterSourceAnalysis(aModel, storages.get(j), str.getName()));
            }
        }
        AnalyzeTool tool = new AnalyzeTool(aModel);
        models2AnalyzeToolInstances.put(aModel, tool);
    }
  /**
    * Get available quantities to use as a Domain variable
    * source is a boolean used to specify if Analysis or File radio button 
    * have been selected.
    */

   public ArrayList<PlotterSourceFile> getLoadedFileSources() {
      ArrayList<PlotterSourceFile> fileSources = new ArrayList<PlotterSourceFile>();
      for(int i=0; i<sources.size(); i++){
         if (sources.get(i) instanceof PlotterSourceFile)
            fileSources.add((PlotterSourceFile) sources.get(i));
      }
      return fileSources;
   }

   /**
    * Add a curve to the PlotterModel. If a new figure is created as a side effect of this it's returned
    * otherwise null is returned to indicate that no new Panel was created. The actual addition should be
    * done by the caller JPlotterFrame
    */
   PlotCurve addCurve(String title, PlotCurveSettings plotCurveSettings, 
           PlotterSourceInterface source1, String string1, 
           PlotterSourceInterface source2, String string2) throws PlotterException {

      Plot currentPlot = availablePlots.get(currentPlotIndex);
      PlotCurve newCurve = new PlotCurve(plotCurveSettings, source1, string1, source2, string2);
      currentPlot.add(newCurve);
      
      //currentPlot.dChart.getXYPlot().addAnnotation(new XYTextAnnotation("text", ));
      plotTreeModel.addPlotCurveToTree(newCurve);
      currentPlot.setTitle(title);
      currentPlot.getChartPanel().getChart().getXYPlot().getDomainAxis().setLabel(string1);
      currentPlot.getChartPanel().getChart().getXYPlot().getRangeAxis().setLabel("");
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
           PlotterSourceInterface domainSource, String domainColumnName, 
           PlotterSourceInterface rangeSource, String rangeColumnName) throws PlotterException {
      
      Plot currentPlot = availablePlots.get(currentPlotIndex);
      currentPlot.setTitle(title);
      currentCurve.update(title, plotCurveSettings, domainSource, domainColumnName, rangeSource, rangeColumnName);
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

   void addSource(PlotterSourceFile src) {
      sources.add(src);
   }

   PlotterSourceFile getSource(String fileName, String columnName) {
      // Cycle thru availabe sources, check for their names and if found check name exists
      for(int i=0; i<sources.size(); i++){
         if (sources.get(i) instanceof PlotterSourceFile){
            PlotterSourceFile src = (PlotterSourceFile) sources.get(i);
            
            if (src.getDisplayName().compareTo(fileName)==0){
               // Make a storage and check that columnName is valid
               if (columnName.compareTo("time")==0)
                  return src;
               if(src.getStorage().getStateIndex(columnName)!=-1)
                  return src;
               else
                  return null;
            }
         }
      }
      return null;
   }
   
   int countSources() {
       return sources.size();
   }

    ArrayList<PlotterSourceAnalysis> getAnalysisSources() {
      ArrayList<PlotterSourceAnalysis> analysisSources = new ArrayList<PlotterSourceAnalysis>();
      for(int i=0; i<sources.size(); i++){
         if (sources.get(i) instanceof PlotterSourceAnalysis)
            analysisSources.add((PlotterSourceAnalysis) sources.get(i));
      }
      return analysisSources;
    }
    
    public AnalyzeTool getAnalyzeTool(Model model)
    {
       return models2AnalyzeToolInstances.get(model);
    }

}