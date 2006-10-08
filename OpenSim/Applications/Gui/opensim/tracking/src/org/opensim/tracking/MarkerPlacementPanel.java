package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import javax.swing.event.ChangeListener;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.SimmIKSolverImpl;
import org.opensim.modeling.SimmIKTrialParams;
import org.opensim.modeling.SimmInverseKinematicsTarget;
import org.opensim.modeling.SimmMarkerData;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.modeling.SimmMarkerSet;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.modeling.SimmSubject;
import org.opensim.modeling.Storage;
import org.opensim.utils.FileUtils;
import org.opensim.view.OpenOsimModelAction;

public class MarkerPlacementPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private workflowVisualPanelBase component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new MarkerPlacementVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updatePanel(descriptor);
        updateVisibility();
    }
    public void storeSettings(Object settings) {}

    boolean executeStep() {
            // Call scaling with the model and display it in GUI
            SimmSubject subject = descriptor.getSubject();
            SimmModel model = descriptor.getModel();
            SimmMarkerPlacementParams params = subject.getMarkerPlacementParams();
            SimmMarkerSet paramsMarkerSet=params.getMarkerSet();
            model.updateMarkers(paramsMarkerSet); // This should be markerSet, could this work using proxy classes?
            component.appendMessage("Updating markers and coordinates.\n");
            SimmMotionData coordinateValues=null;
            if (!params.getCoordinateFileName().equalsIgnoreCase("Unassigned")){
                // @FIXME check that file exists
                coordinateValues = new SimmMotionData(subject.getPathToSubject()+params.getCoordinateFileName());
                model.updateCoordinates(params.getCoordinateSet());
            }
            if (coordinateValues==null)
                coordinateValues = new SimmMotionData();
            
            // Make up a SimmIKTrialParams
            component.appendMessage("Reading static pose.\n");
            SimmMarkerData staticPose = new SimmMarkerData(subject.getPathToSubject()+params.getStaticPoseFilename());
            // Convert read trc fil into "common" rdStroage format
            Storage inputStorage = new Storage();
            staticPose.makeRdStorage(inputStorage);
            ArrayDouble timeRange = params.getTimeRange();
            component.appendMessage("Averaging static pose.\n");
            staticPose.averageFrames(0.01, timeRange.getitem(0), timeRange.getitem(1));
            staticPose.convertToUnits(model.getLengthUnits());

            // Delete any markers from the model that are not in the static
            // pose marker file.
            model.deleteUnusedMarkers(staticPose.getMarkerNames());
            SimmIKTrialParams options = new SimmIKTrialParams();
            options.setStartTime(timeRange.getitem(0));
            options.setEndTime(timeRange.getitem(1));
            options.setIncludeMarkers(true);
            // Convert read trc fil into "common" rdStroage format
            staticPose.makeRdStorage(inputStorage);
            if(coordinateValues.getNumColumns()>0) {
                 coordinateValues.addToRdStorage(inputStorage,timeRange.getitem(0),timeRange.getitem(1));
            }
            inputStorage.print("markers_coords.sto"); 
                  // Create target 

            // Create target
            SimmInverseKinematicsTarget target = new SimmInverseKinematicsTarget(model, inputStorage);
            // Create solver
            SimmIKSolverImpl ikSolver = new SimmIKSolverImpl(target);
            // Solve
            Storage	outputStorage = new Storage();
            component.appendMessage("Solving averaged frame from static pose.\n");
            ikSolver.solveFrames(options, inputStorage, outputStorage);

            // MOVE THE MARKERS TO CORRESPOND TO EXPERIMENTAL LOCATIONS
            component.appendMessage("Moving markers on model.\n");
            model.moveMarkersToCloud(outputStorage);
            
            String userSpecifiedName = params.getOutputModelFileName();
            String localName;
            if (userSpecifiedName.equalsIgnoreCase("Unassigned")){
                 localName = FileUtils.getNextAvailableName(subject.getPathToSubject(), 
                                                                   subject.getGenericModelParams().getModelFileName()+"MP",
                                                                   "xml");
            }
            else
                localName= userSpecifiedName;
            
            model.setName(model.getName()+"- Markers");
            params.setOutputModelFileName(localName);
            params.writeOutputFiles(model, outputStorage, subject.getPathToSubject());
            component.appendMessage("Opening model with moved markers.\n");
           try {
                // Display original model
                ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(subject.getPathToSubject()+localName);
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            } catch (IOException ex) {
                DialogDisplayer.getDefault().notify(
                    new NotifyDescriptor.Message("Model could not be located. Please file a bug!"));
            };
            component.putClientProperty("Step_executed", Boolean.TRUE);
            return true;
    }

    public void updateVisibility()
    {
        Object isExecuted = component.getClientProperty("Step_executed");
        if (isExecuted != null && (Boolean)isExecuted==Boolean.TRUE ){
            markValid(true);
        }
        markValid(!descriptor.getStepInProgress() );
    }
    
}

