package org.opensim.tracking;

import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import org.opensim.modeling.IKTool;
import org.opensim.modeling.IKTrial;
import org.opensim.modeling.Model;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;

//==================================================================
// IKToolModel
//==================================================================
// Only deals with a single (the first) IKTrial in the IKTrialSet of IKTool
public class IKToolModel extends Observable implements Observer {

   enum Operation { AllDataChanged, IKTaskSetChanged };

   private IKTool ikTool = null;
   private Model model = null;

   private boolean modifiedSinceLastExecute = true;

   private IKCommonModel ikCommonModel;

   public IKToolModel(Model originalModel) throws IOException {
      // Store original model
      this.model = originalModel;

      // Create IK tool
      ikTool = new IKTool();
      ikTool.setModel(model);

      ikCommonModel = new IKCommonModel(model);
      ikCommonModel.addObserver(this);
   }

   public Model getModel() { return model; }
   public IKTool getIKTool() { return ikTool; }
   public IKCommonModel getIKCommonModel() { return ikCommonModel; }
   
   //------------------------------------------------------------------------
   // Utilities for running/canceling tool
   //------------------------------------------------------------------------

   private void updateIKTool() {
      ikCommonModel.toIKTool(ikTool);
   }

   public void execute() {
      System.out.println("IKToolModel.execute");
      if(isModified()) {
         try {
            System.out.println("IKToolModel.execute -- actually doing it");
            updateIKTool();
            ikTool.run();
            // TODO: add/update motion in model
            resetModified();
         } catch (Exception ex) {
            ex.printStackTrace();
         }
      }
   }

   public void cancel() {
      System.out.println("IKToolModel.cancel");
      // TODO: remove motion from model
   }

   //------------------------------------------------------------------------
   // Handle updates in the IK Task Set
   //------------------------------------------------------------------------
   public void update(Observable observable, Object obj) {
      if(observable==ikCommonModel) setModified(Operation.IKTaskSetChanged);
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

   public boolean isValid() {
      return ikCommonModel.isValid();
   }

   //------------------------------------------------------------------------
   // Load/Save Settings
   //------------------------------------------------------------------------
   
   private void relativeToAbsolutePaths(String parentFileName) {
      String parentDir = (new File(parentFileName)).getParent();
      for(int i=0; i<ikTool.getIKTrialSet().getSize(); i++) {
         IKTrial trial = ikTool.getIKTrialSet().get(i);
         trial.setMarkerDataFileName(FileUtils.makePathAbsolute(trial.getMarkerDataFileName(),parentDir));
         trial.setCoordinateFileName(FileUtils.makePathAbsolute(trial.getCoordinateFileName(),parentDir));
      }
   }

   public boolean loadSettings(String fileName) {
      // TODO: set current working directory before trying to read it?
      IKTool newIKTool = null;
      try {
         newIKTool = new IKTool(fileName, model);
      } catch (IOException ex) {
         ErrorDialog.displayIOExceptionDialog("Error loading file","Could not load "+fileName,ex);
         return false;
      }
      ikTool = newIKTool;
      relativeToAbsolutePaths(fileName);

      // keep internal data in sync
      modifiedSinceLastExecute = true;

      ikCommonModel.fromIKTool(ikTool);

      setModified(Operation.AllDataChanged);
      return true;
   }

   public boolean saveSettings(String fileName) {
      updateIKTool();
      ikTool.print(fileName);
      return true;
   }
}
