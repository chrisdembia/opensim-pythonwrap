package org.opensim.tracking;

import java.io.File;
import java.util.Observable;
import java.util.prefs.Preferences;
import org.opensim.modeling.AbstractTool;
import org.opensim.modeling.Analysis;
import org.opensim.modeling.AnalysisSet;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.tracking.AbstractToolModel.Operation;
import org.opensim.utils.FileUtils;
import org.opensim.utils.TheApp;

public class AbstractToolModel extends Observable {

   enum Operation { AllDataChanged, InputDataChanged, OutputDataChanged, TimeRangeChanged, AnalysisDataChanged, AnalysisAddedOrRemoved, ActuatorsDataChanged, ExternalLoadsDataChanged, ExecutionStateChanged };

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
   public void setReplaceActuatorSet(boolean replace) { 
      if(getReplaceActuatorSet() != replace) {
         tool.setReplaceActuatorSet(replace);
         setModified(Operation.ActuatorsDataChanged);
      }
   }

   public ArrayStr getActuatorSetFiles() { return tool.getActuatorSetFiles(); }
   public void setActuatorSetFiles(ArrayStr files) {
      if(!getActuatorSetFiles().arrayEquals(files)) {
         tool.setActuatorSetFiles(files);
         setModified(Operation.ActuatorsDataChanged);
      }
   }

   public AnalysisSet getAnalysisSet() { return tool.getAnalysisSet(); }
   public void addCopyOfAnalysis(Analysis analysis) {
      Analysis analysisCopy = Analysis.safeDownCast(analysis.copy()); // C++-side copy
      analysisCopy.setName(analysis.getType()); // Change name...  otherwise name will be "default" since currently the analyses we're making copies of come from the registered object table
      getAnalysisSet().append(analysisCopy);
      setModified(Operation.AnalysisAddedOrRemoved);
   }
   public void replaceAnalysis(int i, Analysis analysis) {
      getAnalysisSet().set(i, analysis);
      setModified(Operation.AnalysisDataChanged);
   }
   public void removeAnalysis(int i) {
      getAnalysisSet().remove(i); 
      setModified(Operation.AnalysisAddedOrRemoved);
   }
   // Rely on users to call this since we don't have accessors for all analysis properties
   public void analysisModified(int i) { setModified(Operation.AnalysisDataChanged); }

   public String getModelFileName() { return tool.getModelFilename(); }

   public double getInitialTime() { return tool.getInitialTime(); }
   public void setInitialTime(double time) {
      if(getInitialTime() != time) {
         tool.setInitialTime(time);
         setModified(Operation.TimeRangeChanged);
      }
   }

   public double getFinalTime() { return tool.getFinalTime(); }
   public void setFinalTime(double time) {
      if(getFinalTime() != time) {
         tool.setFinalTime(time);
         setModified(Operation.TimeRangeChanged);
      }
   }

   public int getOutputPrecision() { return tool.getOutputPrecision(); }
   public void setOutputPrecision(int precision) {
      if(getOutputPrecision() != precision) {
         tool.setOutputPrecision(precision);
         setModified(Operation.OutputDataChanged);
      }
   }

   public String getOutputPrefix() { return tool.getName(); } // It's the name of the tool
   public void setOutputPrefix(String name) {
      if(!getOutputPrefix().equals(name)) {
         tool.setName(name);
         setModified(Operation.OutputDataChanged);
      }
   }

   public String getResultsDirectory() { return tool.getResultsDir(); }
   public void setResultsDirectory(String directory) {
      if(!getResultsDirectory().equals(directory)) {
         tool.setResultsDir(directory);
         setModified(Operation.OutputDataChanged);
      }
   }
   protected void setDefaultResultsDirectory(Model model) {
      // Try to come up with a reasonable output directory
      if(!model.getInputFileName().equals("")) tool.setResultsDir((new File(model.getInputFileName())).getParent());
      else tool.setResultsDir(Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", ""));
   }
   
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
      tool.setAllPropertiesUseDefault(false); // To make sure we serialize all properties even after we've changed their values
   }
}

abstract class AbstractToolModelWithExternalLoads extends AbstractToolModel {
   private boolean externalLoadsEnabled = false;

   public AbstractToolModelWithExternalLoads(Model model) { super(model); }

   public boolean getExternalLoadsEnabled() { return externalLoadsEnabled; }
   public void setExternalLoadsEnabled(boolean enabled) {
      if(getExternalLoadsEnabled() != enabled) {
         externalLoadsEnabled = enabled;
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public abstract String getExternalLoadsFileName();
   protected abstract void setExternalLoadsFileNameInternal(String fileName);
   public void setExternalLoadsFileName(String fileName) {
      if(!getExternalLoadsFileName().equals(fileName)) {
         setExternalLoadsFileNameInternal(fileName);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public abstract String getExternalLoadsModelKinematicsFileName();
   protected abstract void setExternalLoadsModelKinematicsFileNameInternal(String fileName);
   public void setExternalLoadsModelKinematicsFileName(String fileName) {
      if(!getExternalLoadsModelKinematicsFileName().equals(fileName)) {
         setExternalLoadsModelKinematicsFileNameInternal(fileName);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public abstract String getExternalLoadsBody1();
   protected abstract void setExternalLoadsBody1Internal(String name);
   public void setExternalLoadsBody1(String name) {
      if(!getExternalLoadsBody1().equals(name)) {
         setExternalLoadsBody1Internal(name);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public abstract String getExternalLoadsBody2();
   protected abstract void setExternalLoadsBody2Internal(String name);
   public void setExternalLoadsBody2(String name) {
      if(!getExternalLoadsBody2().equals(name)) {
         setExternalLoadsBody2Internal(name);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public abstract double getLowpassCutoffFrequencyForLoadKinematics();
   protected abstract void setLowpassCutoffFrequencyForLoadKinematicsInternal(double cutoffFrequency);
   public void setLowpassCutoffFrequencyForLoadKinematics(double cutoffFrequency) {
      if(getLowpassCutoffFrequencyForLoadKinematics() != cutoffFrequency) {
         setLowpassCutoffFrequencyForLoadKinematicsInternal(cutoffFrequency);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   public boolean getFilterLoadKinematics() { return getLowpassCutoffFrequencyForLoadKinematics() > 0; }
   public void setFilterLoadKinematics(boolean filterLoadKinematics) {
      if(getFilterLoadKinematics() != filterLoadKinematics) {
         if(filterLoadKinematics) setLowpassCutoffFrequencyForLoadKinematicsInternal(6);
         else setLowpassCutoffFrequencyForLoadKinematicsInternal(-1);
         setModified(AbstractToolModel.Operation.ExternalLoadsDataChanged);
      }
   }

   protected void updateFromTool() {
      super.updateFromTool();
      externalLoadsEnabled = !FileUtils.effectivelyNull(getExternalLoadsFileName());
   }

   protected void updateTool() {
      super.updateTool();
      if(!externalLoadsEnabled) setExternalLoadsFileNameInternal("");
   }
}

