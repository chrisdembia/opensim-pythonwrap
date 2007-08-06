package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;
import javax.swing.SwingUtilities;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.BodyScale;
import org.opensim.modeling.BodyScaleSet;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.MarkerData;
import org.opensim.modeling.MarkerPair;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.Measurement;
import org.opensim.modeling.MeasurementSet;
import org.opensim.modeling.Model;
import org.opensim.modeling.ModelScaler;
import org.opensim.modeling.PropertyStr;
import org.opensim.modeling.Scale;
import org.opensim.modeling.ScaleSet;
import org.opensim.modeling.ScaleTool;
import org.opensim.modeling.Storage;
import org.opensim.modeling.rdMath;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;

//==================================================================
// OptionalFile (helper class)
//==================================================================
class OptionalFile {
   public String fileName = "";
   public boolean enabled = false;
   public boolean isValid() { return enabled && !FileUtils.effectivelyNull(fileName); }
   public void fromProperty(String fileName) { 
      if(FileUtils.effectivelyNull(fileName)) { enabled = false; this.fileName = ""; }
      else { enabled = true; this.fileName = fileName; }
   }
   public String toProperty() { 
      return (enabled && !FileUtils.effectivelyNull(fileName)) ? fileName : PropertyStr.getDefaultStr();
   }
}

//==================================================================
// BodyScaleFactors
//==================================================================
class BodyScaleFactors {
   public boolean useManual = false;
   public int[] measurements = new int[]{-1, -1, -1}; // -1 means no measurement applied to that axis, otherwise it's the index of a measurement in the measurement set
   public double[] manualScales = new double[]{1., 1., 1.};

   // UTILITY
   public boolean uniformMeasurements() { return measurements[0]==measurements[1] && measurements[0]==measurements[2]; }
   public boolean uniformManualScales() { return manualScales[0]==manualScales[1] && manualScales[0]==manualScales[2]; }
   public boolean useManualScale() { return useManual; }
   public boolean manualScalesAreIdentity() { return manualScales[0]==1 && manualScales[1]==1 && manualScales[2]==1; }
   public void setUseManualScale(boolean useManual) { this.useManual = useManual; }

   public String toString() {
      return "BodyScaleFactors[measurements={"+measurements[0]+","+measurements[1]+","+measurements[2]+"}"+
               ((manualScales!=null)?(",manualScales={"+manualScales[0]+","+manualScales[1]+","+manualScales[2]+"}"):"")+"]";
   }
}

//==================================================================
// BodySetScaleFactors
//==================================================================
class BodySetScaleFactors extends Vector<BodyScaleFactors> {

   private ScaleToolModel scaleToolModel;
   private BodySet bodySet;
   private Hashtable<String,Integer> mapBodyNameToIndex;

   public BodySetScaleFactors(ScaleToolModel scaleToolModel, BodySet bodySet) {
      super(bodySet.getSize());
      this.scaleToolModel = scaleToolModel;
      this.bodySet = bodySet;

      setSize(bodySet.getSize());
      mapBodyNameToIndex = new Hashtable<String,Integer>(size());

      for(int i=0; i<size(); i++) {
         mapBodyNameToIndex.put(bodySet.get(i).getName(),new Integer(i));
         set(i, new BodyScaleFactors());
      }
   }

   public void print() {
      for(int i=0; i<size(); i++) 
         System.out.println("Body "+i+" ("+bodySet.get(i).getName()+"): "+get(i).toString());
   }

   public void removeMeasurement(int index) {
      for(int i=0; i<size(); i++) {
         for(int j=0; j<3; j++) {
            if(get(i).measurements[j]==index) get(i).measurements[j]=-1;
            else if(get(i).measurements[j]>index) get(i).measurements[j]--;
         }
      }
   }

   private int axisToIndex(String axis) {
      String axisUpper = axis.toUpperCase();
      return (axisUpper.equals("X") ? 0 : (axisUpper.equals("Y") ? 1 : (axisUpper.equals("Z") ? 2 : -1)));
   }
   private String indexToAxis(int index) {
      return (index==0 ? "X" : (index==1 ? "Y" : (index==2 ? "Z" : null)));
   }

   public void fromModelScaler() {
      ModelScaler modelScaler = scaleToolModel.getScaleTool().getModelScaler();

      // Initialize assuming nonuniform
      for(int i=0; i<size(); i++) set(i, new BodyScaleFactors());

      boolean sawManualScale = false;
      for(int o=0; o<modelScaler.getScalingOrder().getSize(); o++) {
         //------------------------------------------------------------------
         // Measurement-based scaling
         //------------------------------------------------------------------
         if(modelScaler.getScalingOrder().getitem(o).equals("measurements")) {
            if(sawManualScale) {
               // measurements after manualScale is a weird case (because measurement based scaling allows only some of the axes to be overwritten... whereas
               // the GUI currently assumes a given coordinate is either using measurements for all 3 axes or manualscales for all 3 axes
            }
            for(int i=0; i<modelScaler.getScalingOrder().getSize(); i++) {
               if(modelScaler.getScalingOrder().getitem(i).equals("measurements")) {
                  MeasurementSet measurementSet = modelScaler.getMeasurementSet();
                  for(int j=0; j<measurementSet.getSize(); j++) {
                     Measurement meas = modelScaler.getMeasurementSet().get(j);
                     if(!meas.getApply()) continue; // TODO -- we should somehow store this in our internal data structure so the user can see the fact that the measurement exists
                     for(int k=0; k<meas.getBodyScaleSet().getSize(); k++) {
                        BodyScale bodyScale = meas.getBodyScaleSet().get(k);
                        Integer bodyIndex = mapBodyNameToIndex.get(bodyScale.getName());
                        if(bodyIndex!=null) {
                           BodyScaleFactors scaleFactors = get(bodyIndex);
                           scaleFactors.useManual = false;
                           ArrayStr axisNames = bodyScale.getAxisNames();
                           for(int l=0; l<axisNames.getSize(); l++) {
                              int index = axisToIndex(axisNames.getitem(l));
                              if(index>=0) scaleFactors.measurements[index] = j;
                           }
                        } else { 
                           System.out.println("ERROR: Body '"+bodyScale.getName()+"' referred to by measurement '"+meas.getName()+"' doesn't exist!"); 
                        }
                     }
                  }
               }
            }
         } 
         //------------------------------------------------------------------
         // Manual scaling
         //------------------------------------------------------------------
         else if(modelScaler.getScalingOrder().getitem(o).equals("manualScale")) {
            sawManualScale = true;
            for(int i=0; i<modelScaler.getScaleSet().getSize(); i++) {
               Scale scale = modelScaler.getScaleSet().get(i);
               Integer bodyIndex = mapBodyNameToIndex.get(scale.getSegmentName());
               if(bodyIndex!=null) {
                  BodyScaleFactors scaleFactors = get(bodyIndex);
                  scaleFactors.useManual = scale.getApply();
                  for(int j=0; j<3; j++) scaleFactors.manualScales[j] = scale.getScaleFactors().getitem(j);
               } else {
                  System.out.println("ERROR: Body '"+scale.getSegmentName()+"' referred to by scale '"+scale.getName()+"' doesn't exist!");
               }
            }
         } else {
            System.out.println("ERROR: Unrecognized string '"+modelScaler.getScalingOrder().getitem(o)+" in scaling order property");
         }
      }

      print();
   }

   public void toModelScaler() {
      ModelScaler modelScaler = scaleToolModel.getScaleTool().getModelScaler();

      ArrayStr array = new ArrayStr();

      //------------------------------------------------------------------
      // Measurement-based scaling
      //------------------------------------------------------------------
      // The measurements are up to date, but what they're applied to isn't
      MeasurementSet measurementSet = modelScaler.getMeasurementSet();
      if(measurementSet.getSize()>0) array.append("measurements");
      for(int i=0; i<measurementSet.getSize(); i++) {
         measurementSet.get(i).getBodyScaleSet().setSize(0);
         measurementSet.get(i).setApply(false);
      }
      for(int i=0; i<size(); i++) {
         for(int j=0; j<3; j++) {
            if(get(i).measurements[j]>=0)
               addToMeasurement(get(i).measurements[j], bodySet.get(i).getName(), j);
         }
      }

      //------------------------------------------------------------------
      // Manual scaling
      //------------------------------------------------------------------
      // Clear the scale set
      modelScaler.getScaleSet().setSize(0);
      for(int i=0; i<size(); i++) {
         // If using manual scales, we'll add it to the scale set with apply==true
         // Otherwise, if it's not the default {1,1,1} scale we'll write it out with apply==false so that 
         // the user can recover these values when they load the setup file
         if(get(i).useManualScale() || !get(i).manualScalesAreIdentity()) {
            Scale scale = new Scale();
            scale.setSegmentName(bodySet.get(i).getName());
            scale.setApply(get(i).useManualScale());
            for(int j=0; j<3; j++) scale.getScaleFactors().set(j,get(i).manualScales[j]);
            modelScaler.getScaleSet().append(Scale.safeDownCast(scale.copy()));
         }
      }
      if(modelScaler.getScaleSet().getSize()>0) array.append("manualScale");

      modelScaler.setScalingOrder(array);
   }

   //------------------------------------------------------------------------
   // Private utility functions
   //------------------------------------------------------------------------

   // axis = 0 (X), 1(Y), 2(Z), or -1 for all axes
   // TODO: make more efficient
   private void addToMeasurement(int index, String bodyName, int axis) {
      ModelScaler modelScaler = scaleToolModel.getScaleTool().getModelScaler();
      Measurement meas = modelScaler.getMeasurementSet().get(index);
      meas.setApply(true);
      BodyScaleSet bodyScaleSet = meas.getBodyScaleSet();
      int bodyScaleIndex = bodyScaleSet.getIndex(bodyName);
      BodyScale bodyScale = null;
      if(bodyScaleIndex < 0) {
         bodyScale = BodyScale.safeDownCast((new BodyScale()).copy()); // Create it on C++ side
         bodyScale.setName(bodyName);
         modelScaler.getMeasurementSet().get(index).getBodyScaleSet().append(bodyScale);
      } else bodyScale = bodyScaleSet.get(bodyScaleIndex);
      if(axis==0 || axis==-1) bodyScale.getAxisNames().append("X");
      if(axis==1 || axis==-1) bodyScale.getAxisNames().append("Y");
      if(axis==2 || axis==-1) bodyScale.getAxisNames().append("Z");
   }
}

//==================================================================
// ScaleToolModel
//==================================================================
public class ScaleToolModel extends Observable implements Observer {

   enum Operation { AllDataChanged, SubjectDataChanged, MarkerSetChanged, MeasurementSetChanged, ModelScalerDataChanged, MarkerPlacerDataChanged };

   private ScaleTool scaleTool = null;
   private Model originalModel = null;
   private MarkerSet originalMarkerSet = null;
   private Model unscaledModel = null;
   private Model scaledModel = null;

   private boolean modifiedSinceLastExecute = true;

   private OptionalFile extraMarkerSetFile = new OptionalFile();
   private MarkerSet extraMarkerSet = null;

   private Hashtable<String,Boolean> markerExistsInModel = new Hashtable<String,Boolean>();
   private Hashtable<String,Boolean> markerExistsInMeasurementTrial = new Hashtable<String,Boolean>();

   private OptionalFile measurementTrialFile = new OptionalFile();
   private MarkerData measurementTrial = null;
   private Vector<Double> measurementValues = null;

   private BodySetScaleFactors bodySetScaleFactors;
   
   private IKCommonModel ikCommonModel; // Stores marker placer stuff that's also common to IKTool

   public ScaleToolModel(Model originalModel) throws IOException {
      // Store original model; create copy of the original model as our unscaled model (i.e. the model we'll scale)
      this.originalModel = originalModel;
      // clone may throw an exception... passed back up to the caller...
      unscaledModel = originalModel.clone();
      unscaledModel.setInputFileName("");
      unscaledModel.setup(); // need to call setup() after clone() because some internal variables aren't (properly) copied
      originalMarkerSet = new MarkerSet(unscaledModel.getDynamicsEngine().getMarkerSet());

      // Create scale tool
      scaleTool = new ScaleTool();
      setName(originalModel.getName()+"-scaled"); // initialize name of output (scaled) model
      setMass(getModelMass(originalModel)); // initialize mass to the subject's current mass

      measurementValues = new Vector<Double>();

      bodySetScaleFactors = new BodySetScaleFactors(this, unscaledModel.getDynamicsEngine().getBodySet());

      ikCommonModel = new IKCommonModel(unscaledModel);
      ikCommonModel.addObserver(this);
   }

   // Simple accessors
   public Model getUnscaledModel() { return unscaledModel; }
   public ScaleTool getScaleTool() { return scaleTool; }
   public IKCommonModel getIKCommonModel() { return ikCommonModel; }

   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------
   
   private void updateScaleTool() {
      scaleTool.setPrintResultFiles(false);
      scaleTool.getGenericModelMaker().setMarkerSetFileName(extraMarkerSetFile.toProperty());
      scaleTool.getModelScaler().setMarkerFileName(measurementTrialFile.toProperty());
      bodySetScaleFactors.toModelScaler();
      ikCommonModel.toMarkerPlacer(scaleTool.getMarkerPlacer());
   }

   public void execute() {
      System.out.println("ScaleToolModel.execute");
      if(isModified()) {
         try {
            System.out.println("scaleToolModel.execute -- actually doing it");

            updateScaleTool();

            Model oldScaledModel = scaledModel;

            scaledModel = unscaledModel.clone();
            scaledModel.setName(scaleTool.getName());
            scaledModel.setInputFileName("");
            scaledModel.setup(); // need to call setup() after clone() because some internal variables aren't (properly) copied

            // TODO: use the Storage's we've already read in rather than reading them again
            if(getModelScalerEnabled()) {
               System.out.println("ModelScaler...");
               // Pass empty path as path to subject, since we already have the measurement trial as an absolute path
               if(!scaleTool.getModelScaler().processModel(scaledModel, "", scaleTool.getSubjectMass())) {
                  // TODO: handle error
               }
            }

            if(getMarkerPlacerEnabled()) {
               System.out.println("MarkerPlacer...");
               // Pass empty path as path to subject, since we already have the static trial as an absolute path
               if(!scaleTool.getMarkerPlacer().processModel(scaledModel, "")) {
                  // TODO: handle error
               }
            }

            assert(SwingUtilities.isEventDispatchThread());
            OpenSimDB.getInstance().replaceModel(oldScaledModel, scaledModel);

            if(getMarkerPlacerEnabled() && scaleTool.getMarkerPlacer().getOutputStorage()!=null) {
               Storage motion = new Storage(scaleTool.getMarkerPlacer().getOutputStorage());
               motion.setName("static pose");
               MotionsDB.getInstance().addMotion(scaledModel, motion);
            }

            resetModified();
         } catch (Exception ex) {
            ex.printStackTrace();
            scaledModel = null;
         }
      }
   }

   public void cancel() {
      System.out.println("ScaleToolModel.cancel");
      if(scaledModel!=null) OpenSimDB.getInstance().removeModel(scaledModel);
      scaledModel = null;
   }

   //------------------------------------------------------------------------
   // Handle updates in the IK Task Set
   //------------------------------------------------------------------------
   public void update(Observable observable, Object obj) {
      if(observable==ikCommonModel) setModified(Operation.MarkerPlacerDataChanged);
   }

   //------------------------------------------------------------------------
   // Modified flag
   //------------------------------------------------------------------------

   private void setModified(Operation change) {
      modifiedSinceLastExecute = true;
      setChanged(); // need to call this before calling notifyObservers
      notifyObservers(change);
   }
   private void resetModified() {
      modifiedSinceLastExecute = false;
   }
   public boolean isModified() {
      return modifiedSinceLastExecute;
   }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   private boolean getBodyScaleFactorsValid(BodyScaleFactors scaleFactors) {
      if(!scaleFactors.useManualScale()) {
         for(int i=0; i<3; i++)
            if(scaleFactors.measurements[i]!=-1 && getMeasurementValue(scaleFactors.measurements[i])==null)
               return false;
      }
      return true;
   }

   private boolean getBodySetScaleFactorsValid() {
      for(int i=0; i<getBodySetScaleFactors().size(); i++)
         if(!getBodyScaleFactorsValid(getBodySetScaleFactors().get(i)))
            return false;
      return true;
   }

   private boolean getModelScalerValid() { return !getModelScalerEnabled() || getBodySetScaleFactorsValid(); }
   private boolean getMarkerPlacerValid() { return !getMarkerPlacerEnabled() || ikCommonModel.isValid(); }

   public boolean isValid() {
      return (!getUseExtraMarkerSet() || getExtraMarkerSetValid()) && getModelScalerValid() && getMarkerPlacerValid();
   }

   //------------------------------------------------------------------------
   // Model Properties
   //------------------------------------------------------------------------

   public void setName(String name) {
      if(!scaleTool.getName().equals(name)) {
         scaleTool.setName(name);
         setModified(Operation.SubjectDataChanged);
      }
   }
   public String getName() {
      return scaleTool.getName();
   }

   public void setMass(double mass) {
      if(scaleTool.getSubjectMass() != mass) {
         scaleTool.setSubjectMass(mass);
         setModified(Operation.SubjectDataChanged);
      }
   }
   public double getMass() {
      return scaleTool.getSubjectMass();
   }

   //------------------------------------------------------------------------
   // Filename effectively null if it's null, or "", or "Unassigned"
   //------------------------------------------------------------------------
   private boolean fileNameEffectivelyNull(String fileName) {
      return fileName==null || fileName.equals("") || fileName.equals(PropertyStr.getDefaultStr());
   }
   private String getFileName(String fileName) {
      return FileUtils.effectivelyNull(fileName) ? "" : fileName;
   }

   //------------------------------------------------------------------------
   // Marker Set Utilities
   //------------------------------------------------------------------------

   private boolean loadExtraMarkerSet(boolean recompute) {
      boolean success = true;
      extraMarkerSet = null;
      if(extraMarkerSetFile.isValid()) {
         try {
            extraMarkerSet = new MarkerSet(extraMarkerSetFile.fileName);
         } catch (IOException ex) {
            extraMarkerSet = null;
            success = false;
         }
      }
      resetMarkers(); // reset markers in our unscaled model
      if(recompute) recomputeMeasurements();
      ikCommonModel.getIKMarkerTasksModel().markerSetChanged();
      return success;
   }

   private void resetMarkers() {
      unscaledModel.getDynamicsEngine().replaceMarkerSet(originalMarkerSet);
      if(extraMarkerSet!=null)
         unscaledModel.getDynamicsEngine().updateMarkerSet(extraMarkerSet);

      // Update hash table
      markerExistsInModel.clear();
      for(int i=0; i<getMarkerSet().getSize(); i++) markerExistsInModel.put(getMarkerSet().get(i).getName(),(Boolean)true);
   }

   public boolean setExtraMarkerSetFileName(String fileName) {
      extraMarkerSetFile.fileName = fileName;
      boolean success = loadExtraMarkerSet(true);
      setModified(Operation.MarkerSetChanged);
      return success;
   }
   public String getExtraMarkerSetFileName() {
      return extraMarkerSetFile.fileName;
   }
   public MarkerSet getExtraMarkerSet() {
      return extraMarkerSet;
   }
   public boolean getExtraMarkerSetValid() {
      return extraMarkerSet!=null;
   }

   public boolean getUseExtraMarkerSet() {
      return extraMarkerSetFile.enabled;
   }
   public void setUseExtraMarkerSet(boolean useIt) {
      if(extraMarkerSetFile.enabled != useIt) {
         extraMarkerSetFile.enabled = useIt;
         loadExtraMarkerSet(true);
         setModified(Operation.MarkerSetChanged);
      }
   }

   public MarkerSet getMarkerSet() {
      return getUnscaledModel().getDynamicsEngine().getMarkerSet();
   }

   public boolean getMarkerExistsInModel(String markerName) {
      return markerExistsInModel.get(markerName)!=null;
   }

   //------------------------------------------------------------------------
   // Model Scaler
   //------------------------------------------------------------------------

   // Model scaler enabled
   public void setModelScalerEnabled(boolean enabled) {
      if(getModelScalerEnabled() != enabled) {
         scaleTool.getModelScaler().setApply(enabled);
         setModified(Operation.ModelScalerDataChanged);
      }
   }
   public boolean getModelScalerEnabled() {
      return scaleTool.getModelScaler().getApply();
   }

   // Preserve mass distribution
   public void setPreserveMassDistribution(boolean enabled) {
      if(scaleTool.getModelScaler().getPreserveMassDist() != enabled) {
         scaleTool.getModelScaler().setPreserveMassDist(enabled);
         setModified(Operation.ModelScalerDataChanged);
      }
   }
   public boolean getPreserveMassDistribution() {
      return scaleTool.getModelScaler().getPreserveMassDist();
   }

   private boolean loadMeasurementTrial(boolean resetTimeRange, boolean recompute) {
      boolean success = true;
      measurementTrial = null; 
      if(measurementTrialFile.isValid()) {
         try {
            measurementTrial = new MarkerData(measurementTrialFile.fileName);
            measurementTrial.convertToUnits(getUnscaledModel().getLengthUnits());
         } catch (IOException ex) {
            measurementTrial = null;
            success = false;
         }
      }
      if(resetTimeRange && measurementTrial!=null) setMeasurementTrialTimeRange(measurementTrial.getTimeRange());
      if(recompute) recomputeMeasurements();

      // Update hash table
      markerExistsInMeasurementTrial.clear();
      if(measurementTrial!=null) {
         for(int i=0; i<measurementTrial.getMarkerNames().getSize(); i++)
            markerExistsInMeasurementTrial.put(measurementTrial.getMarkerNames().getitem(i), (Boolean)true);
      }

      return success;
   }

   // Measurement trial file name
   public boolean setMeasurementTrialFileName(String fileName) {
      measurementTrialFile.fileName = fileName;      
      boolean success = loadMeasurementTrial(true, true);
      setModified(Operation.ModelScalerDataChanged);
      return success;
   }
   public String getMeasurementTrialFileName() {
      return measurementTrialFile.fileName;
   }
   public MarkerData getMeasurementTrial() {
      return measurementTrial;
   }
   public boolean getMeasurementTrialValid() {
      return measurementTrial!=null;
   }

   public void setMeasurementTrialEnabled(boolean enabled) {
      if(measurementTrialFile.enabled != enabled) {
         measurementTrialFile.enabled = enabled;
         loadMeasurementTrial(false,true);
         setModified(Operation.ModelScalerDataChanged);
      }
   }
   public boolean getMeasurementTrialEnabled() {
      return measurementTrialFile.enabled;
   }

   public boolean getMarkerExistsInMeasurementTrial(String markerName) {
      return markerExistsInMeasurementTrial.get(markerName)!=null;
   }

   // Measurement trial time range
   public void setMeasurementTrialTimeRange(double[] timeRange) {
      clampMeasurementTrialTimeRange(timeRange);
      double[] oldRange = getMeasurementTrialTimeRange();
      if(oldRange[0] != timeRange[0] || oldRange[1] != timeRange[1]) {
         ArrayDouble array = new ArrayDouble();
         array.append(timeRange[0]);
         array.append(timeRange[1]);
         scaleTool.getModelScaler().setTimeRange(array);
         setModified(Operation.ModelScalerDataChanged);
      }
   }
   public double[] getMeasurementTrialTimeRange() {
      ArrayDouble array = scaleTool.getModelScaler().getTimeRange();
      return new double[]{array.getitem(0), array.getitem(1)};
   }

   private boolean clampMeasurementTrialTimeRange(double[] timeRange) {
      boolean clamped = false;
      if(measurementTrial!=null) {
         if(timeRange[0] < measurementTrial.getStartFrameTime()) { timeRange[0] = measurementTrial.getStartFrameTime(); clamped = true; }
         if(timeRange[1] > measurementTrial.getLastFrameTime()) { timeRange[1] = measurementTrial.getLastFrameTime(); clamped = true; }
      }
      return clamped;
   }

   //------------------------------------------------------------------------
   // Measurement Set (focuses on the marker pairs in the measurements, not the bodies which the measurement is applied to)
   //------------------------------------------------------------------------

   private ScaleSet createIdentityScaleSet() {
      BodySet bodySet = getUnscaledModel().getDynamicsEngine().getBodySet();
      ScaleSet scaleSet = new ScaleSet();
      ArrayDouble identityScale = new ArrayDouble(1.0,3);
      for(int i=0; i<bodySet.getSize(); i++) {
         Scale scale = new Scale();
         scale.setSegmentName(bodySet.get(i).getName());
         scale.setScaleFactors(identityScale);
         scale.setApply(true);
         scaleSet.append(Scale.safeDownCast(scale.copy()));
      }
      return scaleSet;
   }

   private void resetMeasurementValues() {
      MeasurementSet measurementSet = scaleTool.getModelScaler().getMeasurementSet();
      measurementValues = new Vector<Double>(measurementSet.getSize());
      for(int i=0; i<measurementSet.getSize(); i++) measurementValues.add(null);
   }

   private void recomputeMeasurements() {
      if(measurementTrial==null) resetMeasurementValues();
      else {
         MeasurementSet measurementSet = scaleTool.getModelScaler().getMeasurementSet();
         for(int i=0; i<measurementSet.getSize(); i++) recomputeMeasurement(i);
      }
   }

   private void recomputeMeasurement(int i) {
      if(measurementTrial==null) return;
      MeasurementSet measurementSet = scaleTool.getModelScaler().getMeasurementSet();
      double scaleFactor = scaleTool.getModelScaler().computeMeasurementScaleFactor(getUnscaledModel(), measurementTrial, measurementSet.get(i));
      if(rdMath.isNAN(scaleFactor)) measurementValues.set(i,null);
      else measurementValues.set(i,new Double(scaleFactor));
   }

   public MeasurementSet getMeasurementSet() {
      return scaleTool.getModelScaler().getMeasurementSet();
   }

   String getMeasurementName(int i) {
      return getMeasurementSet().get(i).getName();
   }

   Double getMeasurementValue(int i) {
      return measurementValues.get(i);
   }

   void setMeasurementName(int i, String name) {
      MeasurementSet measurementSet = getMeasurementSet();
      if(i>=measurementSet.getSize()) return; // This does seem to happen if you add and remove measurements quickly in the measurement set panel
                                              // Seems to be because the EditMeasurementNameActionAndFocusListener can process
                                              // the focusLost event even after we've removed that measurement.
      if(!measurementSet.get(i).getName().equals(name)) {
         // Update name
         measurementSet.get(i).setName(name);
         // Fire event
         setModified(Operation.MeasurementSetChanged); // MeasurementRenamed, i
      }
   }

   void setMarkerPairMarker(int i, int pairIndex, int markerIndex, String markerName) {
      MeasurementSet measurementSet = getMeasurementSet();
      assert(0 <= pairIndex && pairIndex < measurementSet.get(i).getMarkerPairSet().getSize());
      assert(markerIndex == 0 || markerIndex == 1);
      measurementSet.get(i).getMarkerPairSet().get(pairIndex).setMarkerName(markerIndex,markerName);
      // Recompute
      recomputeMeasurement(i);
      // Fire event
      setModified(Operation.MeasurementSetChanged); // MeasurementChanged, i
   }

   void addMarkerPair(int i) {
      MeasurementSet measurementSet = getMeasurementSet();
      MarkerPair pair = new MarkerPair("Unassigned", "Unassigned");
      measurementSet.get(i).getMarkerPairSet().insert(0,MarkerPair.safeDownCast(pair.copy()));
      // Recompute
      recomputeMeasurement(i);
      // Fire event
      setModified(Operation.MeasurementSetChanged); // MeasurementChanged, i
   }

   void removeMarkerPair(int i, int pairIndex) {
      MeasurementSet measurementSet = getMeasurementSet();
      measurementSet.get(i).getMarkerPairSet().remove(pairIndex);
      // Recompute
      recomputeMeasurement(i);
      // Fire event
      setModified(Operation.MeasurementSetChanged); // MeasurementChanged, i
   }

   void addMeasurement(String name) {
      MeasurementSet measurementSet = getMeasurementSet();
      Measurement measurement = new Measurement();
      measurement.setName(name);
      measurementSet.append(Measurement.safeDownCast(measurement.copy()));
      // Update parallel measurementValues array
      measurementValues.add(null);
      // Fire event
      setModified(Operation.MeasurementSetChanged); // MeasurementAdded, measurementSet.getSize();
   }

   void removeMeasurement(int i) {
      MeasurementSet measurementSet = getMeasurementSet();
      measurementSet.remove(i);
      // Update indices of all scales that refer to index i or higher
      bodySetScaleFactors.removeMeasurement(i);
      measurementValues.remove(i);
      // Fire event
      setModified(Operation.MeasurementSetChanged); // MeasurementDeleted, i
   }

   //------------------------------------------------------------------------
   // BodyScaleFactors
   //------------------------------------------------------------------------

   public BodySetScaleFactors getBodySetScaleFactors() {
      return bodySetScaleFactors;
   }

   public void bodySetScaleFactorsModified() {
      setModified(Operation.ModelScalerDataChanged);
   }

   //------------------------------------------------------------------------
   // Marker Placer
   //------------------------------------------------------------------------
   // Marker placer enabled
   public void setMarkerPlacerEnabled(boolean enabled) {
      if(getMarkerPlacerEnabled() != enabled) {
         scaleTool.getMarkerPlacer().setApply(enabled);
         setModified(Operation.MarkerPlacerDataChanged);
      }
   }
   public boolean getMarkerPlacerEnabled() {
      return scaleTool.getMarkerPlacer().getApply();
   }

   public boolean getMoveModelMarkers() { return scaleTool.getMarkerPlacer().getMoveModelMarkers(); }
   public void setMoveModelMarkers(boolean move) { 
      if(getMoveModelMarkers() != move) {
         scaleTool.getMarkerPlacer().setMoveModelMarkers(move);
         setModified(Operation.MarkerPlacerDataChanged);
      }
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------

   private void relativeToAbsolutePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();
      scaleTool.getGenericModelMaker().setMarkerSetFileName(FileUtils.makePathAbsolute(scaleTool.getGenericModelMaker().getMarkerSetFileName(),parentDir));
      scaleTool.getModelScaler().setMarkerFileName(FileUtils.makePathAbsolute(scaleTool.getModelScaler().getMarkerFileName(),parentDir));
      scaleTool.getMarkerPlacer().setStaticPoseFileName(FileUtils.makePathAbsolute(scaleTool.getMarkerPlacer().getStaticPoseFileName(),parentDir));
      scaleTool.getMarkerPlacer().setCoordinateFileName(FileUtils.makePathAbsolute(scaleTool.getMarkerPlacer().getCoordinateFileName(),parentDir));
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      ScaleTool newScaleTool = null;
      try {
         newScaleTool = new ScaleTool(fileName);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }
      scaleTool = newScaleTool;
      relativeToAbsolutePaths(fileName);

      // reset some things in the scale tool which we will not use
      scaleTool.getGenericModelMaker().setModelFileName(PropertyStr.getDefaultStr()); // TODO: what should we really set this to?

      // keep internal data in sync
      modifiedSinceLastExecute = true;

      // marker set
      extraMarkerSet = null;
      extraMarkerSetFile.fromProperty(scaleTool.getGenericModelMaker().getMarkerSetFileName());
      loadExtraMarkerSet(false); // will recompute measurements below

      // measurement set and scale factors
      resetMeasurementValues();
      bodySetScaleFactors.fromModelScaler();

      // measurement trial
      measurementTrial = null;
      measurementTrialFile.fromProperty(scaleTool.getModelScaler().getMarkerFileName());
      loadMeasurementTrial(false,false); // will recompute measurements below
      recomputeMeasurements();

      ikCommonModel.fromMarkerPlacer(scaleTool.getMarkerPlacer());

      setModified(Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      XMLExternalFileChooserHelper helper = new XMLExternalFileChooserHelper(fileName);
      helper.addObject(scaleTool.getModelScaler().getMeasurementSet(), "Measurement Set");
      helper.addObject(scaleTool.getModelScaler().getScaleSet(), "Scale Set (manual scale factors)");
      helper.addObject(scaleTool.getMarkerPlacer().getIKTaskSet(), "IK Task Set (for static pose)");
      if(!helper.promptUser()) return false;
      updateScaleTool();
      scaleTool.print(fileName);
      return true;
   }

   //------------------------------------------------------------------------
   // Utility
   //------------------------------------------------------------------------

   public static double getModelMass(Model model) {
      BodySet bodySet = model.getDynamicsEngine().getBodySet();
      double mass = 0;
      for(int i=0; i<bodySet.getSize(); i++)
         mass += bodySet.get(i).getMass();
      return mass;
   }
}
