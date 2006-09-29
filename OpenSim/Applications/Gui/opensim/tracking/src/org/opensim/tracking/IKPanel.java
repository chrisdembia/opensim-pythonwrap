package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import javax.swing.event.ChangeListener;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.modeling.SimmIKParams;
import org.opensim.modeling.SimmIKSolverImpl;
import org.opensim.modeling.SimmIKTrialParams;
import org.opensim.modeling.SimmInverseKinematicsTarget;
import org.opensim.modeling.SimmMarkerData;
import org.opensim.modeling.SimmMarkerSet;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.modeling.SimmSubject;
import org.opensim.modeling.Storage;

public class IKPanel  extends workflowWizardPanelBase{
    
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
            component = new IKVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
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
    public void storeSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updateWorkflow(descriptor);
    }
    
    /**
     * @Todo handle new model for IK
     */
    boolean executeStep() {
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Running Inverse Kinematics ");
        progressHandle.start();
        SimmSubject subject = descriptor.getSubject();
        SimmModel model = descriptor.getModel();
        if (!subject.isDefaultIKParams()){
		//  If model needs to be created anew, do it here.
		if (!subject.getIKParams().getModelFileName().equalsIgnoreCase("Unassigned")){
                try {
                    model = new SimmModel(subject.getPathToSubject()+subject.getIKParams().getModelFileName());
		    model.setup();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
		}
		else // Warn model used without scaling or marker placement
                    ;
        }
        SimmIKParams params = subject.getIKParams();
        
        // Adjust model by markers and coordinates in the IK block
        SimmMarkerSet aMarkerArray=params.getMarkerSet();
        model.updateMarkers(aMarkerArray); 
        model.updateCoordinates(subject.getIKParams().getCoordinateSet());
        
        // Process current trial based on selection in the "Visual" panel
        SimmIKTrialParams trialParams = ((IKVisualPanel)component).getSelectedTrial();
        
         // Handle coordinates file to find coordinate values for "FromFile" cooridnates
        
         // @Todo fix directory handing when reading coordinateValues
         
        // Subject path needs to be passed in so that the file is located properly
        SimmMotionData coordinateValues = trialParams.getCoordinateValues(model, subject.getPathToSubject());
        // Create SimmMarkerData Object from trc file of experimental motion data
        SimmMarkerData motionTrialData = new SimmMarkerData(subject.getPathToSubject()+trialParams.getMarkerDataFilename());
        motionTrialData.convertToUnits(model.getLengthUnits());

        Storage inputStorage = new Storage();
        // Convert read trc fil into "common" rdStroage format
        motionTrialData.makeRdStorage(inputStorage);
        if (coordinateValues != null) {
            /* Adjust the user-defined start and end times to make sure they are in the
            * range of the marker data. This must be done so that you only look in the
            * coordinate data for rows that will actually be solved.
            */
            double firstStateTime = inputStorage.getFirstTime();
            double lastStateTime = inputStorage.getLastTime();
            double startTime = (firstStateTime>trialParams.getStartTime()) ? firstStateTime : trialParams.getStartTime();
            double endTime =  (lastStateTime<trialParams.getEndTime()) ? lastStateTime : trialParams.getEndTime();

            /* Add the coordinate data to the marker data. There must be a row of
            * corresponding coordinate data for every row of marker data that will
            * be solved, or it is a fatal error.
            */
            coordinateValues.addToRdStorage(inputStorage, startTime, endTime);
            progressHandle.progress("Start solution from time "+startTime+" to "+endTime);

        }
        component.appendMessage("Setting up the IK problem for trial "+trialParams.getName()+".\n");
        // Create target
        SimmInverseKinematicsTarget target = new SimmInverseKinematicsTarget(model, inputStorage);
        // Create solver
        SimmIKSolverImpl ikSolver = new SimmIKSolverImpl(target, subject.getIKParams());
        // Solve
        Storage	outputStorage = new Storage();
        ikSolver.solveFrames(trialParams, inputStorage, outputStorage);
        progressHandle.finish();
        
        component.appendMessage("Solved trial "+trialParams.getName()+".\n");
        outputStorage.setWriteSIMMHeader(true);
        component.putClientProperty("Step_executed", Boolean.TRUE);
        return false;
    }
    
}

