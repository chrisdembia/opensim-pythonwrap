package org.opensim.tracking;

import java.io.File;
import java.util.Observable;
import org.opensim.modeling.AbstractTool;
import org.opensim.modeling.AnalysisSet;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.utils.FileUtils;

public class AbstractToolModel extends Observable {

   enum Operation { AllDataChanged, ExecutionStateChanged };

   private boolean modifiedSinceLastExecute = true;
   private boolean executing = false;

   protected Model model = null;
   protected AbstractTool tool = null;

   public AbstractToolModel(Model model) {
      this.model = model;
   }

   public void setTool(AbstractTool tool) {
      this.tool = tool;
   }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public Model getModel() { return model; }
   protected void setModel(Model model) { this.model = model; }

   // Actuators
   public boolean getReplaceActuatorSet() { return tool.getReplaceActuatorSet(); }
   public ArrayStr getActuatorSetFiles() { return tool.getActuatorSetFiles(); }

   public AnalysisSet getAnalysisSet() { return tool.getAnalysisSet(); }

   public String getModelFileName() { return tool.getModelFilename(); }
   public double getInitialTime() { return tool.getInitialTime(); }
   public double getFinalTime() { return tool.getFinalTime(); }
   public int getOutputPrecision() { return tool.getOutputPrecision(); }
   public String getResultsDirectory() { return tool.getResultsDir(); }
   
   // Integrator settings
   public double getMaximumNumberOfSteps() { return tool.getMaximumNumberOfSteps(); }
   public double getMaxDT() { return tool.getMaxDT(); }
   public double getErrorTolerance() { return tool.getErrorTolerance(); }
   public double getFineTolerance() { return tool.getFineTolerance(); }

   //------------------------------------------------------------------------
   // Execution status
   //------------------------------------------------------------------------

   protected void setExecuting(boolean executing) {
      if(this.executing != executing) {
         this.executing = executing;
         setChanged();
         notifyObservers(Operation.ExecutionStateChanged);
      }
   }
   public boolean isExecuting() {
      return executing;
   }

   //------------------------------------------------------------------------
   // Modified flag
   //------------------------------------------------------------------------

   protected void setModified(Object change) {
      modifiedSinceLastExecute = true;
      setChanged(); // need to call this before calling notifyObservers
      notifyObservers(change);
   }
   protected void resetModified() {
      modifiedSinceLastExecute = false;
   }
   public boolean isModified() {
      return modifiedSinceLastExecute;
   }

   //------------------------------------------------------------------------
   // Sync model to/from tool
   //------------------------------------------------------------------------

   protected void relativeToAbsolutePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();

      tool.setModelFilename(FileUtils.makePathAbsolute(tool.getModelFilename(), parentDir));
      tool.setResultsDir(FileUtils.makePathAbsolute(tool.getResultsDir(), parentDir));

      ArrayStr actuatorSetFiles = getActuatorSetFiles();
      for(int i=0; i<actuatorSetFiles.getSize(); i++)
         actuatorSetFiles.set(i, FileUtils.makePathAbsolute(actuatorSetFiles.getitem(i), parentDir));
   }

   protected void updateFromTool() {

   }

   protected void updateTool() {

   }
}

abstract class AbstractToolModelWithExternalLoads extends AbstractToolModel {
   public AbstractToolModelWithExternalLoads(Model model) { super(model); }
   public abstract String getExternalLoadsFileName();
   public abstract String getExternalLoadsModelKinematicsFileName();
   public abstract String getExternalLoadsBody1();
   public abstract String getExternalLoadsBody2();
   public abstract double getLowpassCutoffFrequencyForLoadKinematics();
}

