package org.opensim.tracking;

import java.awt.Component;
import javax.swing.event.ChangeListener;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ArrayPtrsSimmMarker;
import org.opensim.modeling.SimmIKSolverImpl;
import org.opensim.modeling.SimmIKTrialParams;
import org.opensim.modeling.SimmInverseKinematicsTarget;
import org.opensim.modeling.SimmMarkerData;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.modeling.SimmSubject;
import org.opensim.modeling.Storage;
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
            component = new MarkerPlacementVisualPanel();
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
    public boolean isValid() {
        // If it is always OK to press Next or Finish, then:
        return true;
        // If it depends on some condition (form filled out...), then:
        // return someCondition();
        // and when this condition changes (last form field filled in...) then:
        // fireChangeEvent();
        // and uncomment the complicated stuff below.
    }
    
    public final void addChangeListener(ChangeListener l) {}
    public final void removeChangeListener(ChangeListener l) {}
    /*
    private final Set<ChangeListener> listeners = new HashSet<ChangeListener>(1);
    public final void addChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.add(l);
        }
    }
    public final void removeChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.remove(l);
        }
    }
    protected final void fireChangeEvent() {
        Iterator<ChangeListener> it;
        synchronized (listeners) {
            it = new HashSet<ChangeListener>(listeners).iterator();
        }
        ChangeEvent ev = new ChangeEvent(this);
        while (it.hasNext()) {
            it.next().stateChanged(ev);
        }
    }
     */
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updatePanel(descriptor);
    }
    public void storeSettings(Object settings) {}

    boolean executeStep() {
            // Call scaling with the model and display it in GUI
            SimmSubject subject = descriptor.getSubject();
            SimmModel model = descriptor.getModel();
            SimmMarkerPlacementParams params = subject.getMarkerPlacementParams();
            ArrayPtrsSimmMarker aMarkerArray=params.getMarkerSet();
            model.updateMarkers(aMarkerArray); // This should be markerSet, could this work using proxy classes?
            if (!params.getCoordinateFileName().equalsIgnoreCase("Unassigned")){
                SimmMotionData coordinateValues = new SimmMotionData(subject.getPathToSubject()+params.getCoordinateFileName());
                model.updateCoordinates(params.getCoordinateSet());
            }
            // Make up a SimmIKTrialParams
            SimmMarkerData staticPose = new SimmMarkerData(subject.getPathToSubject()+params.getStaticPoseFilename());
            // Convert read trc fil into "common" rdStroage format
            Storage inputStorage = new Storage();
            staticPose.makeRdStorage(inputStorage);
            ArrayDouble timeRange = params.getTimeRange();
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
            // Create target
            SimmInverseKinematicsTarget target = new SimmInverseKinematicsTarget(model, inputStorage);
            // Create solver
            SimmIKSolverImpl ikSolver = new SimmIKSolverImpl(target, subject.getIKParams());
            // Solve
            Storage	outputStorage = new Storage();
            ikSolver.solveFrames(options, inputStorage, outputStorage);

            // MOVE THE MARKERS TO CORRESPOND TO EXPERIMENTAL LOCATIONS
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
            try {
                // Display original model
                ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(subject.getPathToSubject()+localName);
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            }
            component.setExecuted(true);
            return true;
    }

    
}

