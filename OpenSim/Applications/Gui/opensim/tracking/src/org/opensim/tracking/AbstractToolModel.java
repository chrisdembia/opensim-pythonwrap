/*
 * Copyright (c)  2005-2008, Stanford University
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

public abstract class AbstractToolModel extends Observable {

   enum Operation { AllDataChanged, InputDataChanged, OutputDataChanged, TimeRangeChanged, AnalysisDataChanged, AnalysisAddedOrRemoved, ActuatorsDataChanged, ExternalLoadsDataChanged, IntegratorSettingsChanged, ExecutionStateChanged };

   private boolean modifiedSinceLastExecute = true;
   private boolean executing = false;

   protected Model originalModel = originalModel = null;
   protected Model model = null;
   protected AbstractTool tool = null;

   public AbstractToolModel(Model originalModel) {
      this.originalModel = originalModel;
   }

   public void setTool(AbstractTool tool) { this.tool = tool; }
   public AbstractTool getTool() { return tool; }

   //------------------------------------------------------------------------
   // Get/Set Values
   //------------------------------------------------------------------------

   public Model getOriginalModel() { return originalModel; }

   public Model getModel() { return model; }
   protected void setModel(Model model) { this.model = model; }

   //------------------------------------------------------------------------
   // Actuators
   //------------------------------------------------------------------------
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

   //------------------------------------------------------------------------
   // Analyses
   //------------------------------------------------------------------------
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

   //------------------------------------------------------------------------
   // Time range settings
   //------------------------------------------------------------------------
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

   //------------------------------------------------------------------------
   // Ouptut settings
   //------------------------------------------------------------------------
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
   
   //------------------------------------------------------------------------
   // Integrator settings
   //------------------------------------------------------------------------
   public int getMaximumNumberOfSteps() { return tool.getMaximumNumberOfSteps(); }
   public void setMaximumNumberOfSteps(int maxSteps) {
      if(getMaximumNumberOfSteps() != maxSteps) {
         tool.setMaximumNumberOfSteps(maxSteps);
         setModified(Operation.IntegratorSettingsChanged);
      }
   }
   public double getMaxDT() { return tool.getMaxDT(); }
   public void setMaxDT(double maxDT) {
      if(getMaxDT() != maxDT) {
         tool.setMaxDT(maxDT);
         setModified(Operation.IntegratorSettingsChanged);
      }
   }
   public double getErrorTolerance() { return tool.getErrorTolerance(); }
   public void setErrorTolerance(double tolerance) {
      if(getErrorTolerance() != tolerance) {
         tool.setErrorTolerance(tolerance);
         setModified(Operation.IntegratorSettingsChanged);
      }
   }
   public double getFineTolerance() { return tool.getFineTolerance(); }
   public void setFineTolerance(double tolerance) {
      if(getFineTolerance() != tolerance) {
         tool.setFineTolerance(tolerance);
         setModified(Operation.IntegratorSettingsChanged);
      }
   }

   //------------------------------------------------------------------------
   // Other settings
   //------------------------------------------------------------------------
   public boolean getSolveForEquilibrium() { return tool.getSolveForEquilibrium(); }
   public void setSolveForEquilibrium(boolean solve) {
      if(getSolveForEquilibrium() != solve) {
         tool.setSolveForEquilibrium(solve);
         setModified(Operation.InputDataChanged);
      }
   }

   //------------------------------------------------------------------------
   // Functions to override
   //------------------------------------------------------------------------

   public abstract double[] getAvailableTimeRange();

   public abstract boolean isValid();

   public abstract void execute();
   public abstract void cancel();

   public abstract boolean loadSettings(String fileName);
   public abstract boolean saveSettings(String fileName);

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

   protected void AbsoluteToRelativePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();
      
      tool.setModelFilename(FileUtils.makePathRelative(tool.getModelFilename(), parentDir));
      tool.setResultsDir(FileUtils.makePathRelative(tool.getResultsDir(), parentDir));

      ArrayStr actuatorSetFiles = getActuatorSetFiles();
      for(int i=0; i<actuatorSetFiles.getSize(); i++)
         actuatorSetFiles.set(i, FileUtils.makePathRelative(actuatorSetFiles.getitem(i), parentDir));
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

   public boolean isValid() {
      return !getExternalLoadsEnabled() || ((new File(getExternalLoadsFileName()).exists()) && (new File(getExternalLoadsModelKinematicsFileName()).exists()));
   }

   protected double[] intersectTimeRanges(double[] range1, double[] range2) {
      return new double[]{(range1[0]>range2[0])?range1[0]:range2[0], (range1[1]<range2[1])?range1[1]:range2[1]};
   }
}

