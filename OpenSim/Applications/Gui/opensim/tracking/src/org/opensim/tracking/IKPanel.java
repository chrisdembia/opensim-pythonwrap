package org.opensim.tracking;

import java.awt.Component;
import java.util.Timer;
import java.util.TimerTask;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.modeling.InvestigationIK;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimtkAnimationCallback;

public class IKPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private IKVisualPanel component;
    
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
        updateVisibility();
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
        final InvestigationIK ik = component.getInvestigation();
        final SimmModel ikModel = ik.getSimmModel();
        //final SimtkAnimationCallback animationCallback = new SimtkAnimationCallback(ikModel);
        //ikModel.addIntegCallback(animationCallback);
        progressHandle.start();
        
    
        // Execute IK on a separate thread
        Runnable runIk = new Runnable(){
            public void run() {
                ik.run();
            }};
    
        runIk.run();
        progressHandle.finish();
        
        component.putClientProperty("Step_executed", Boolean.TRUE);
        return false;
    }
    
    public void updateVisibility()
    {
        Object state = component.getClientProperty("Step_executed");
        if (state instanceof Boolean && ((Boolean)state).booleanValue()==true)
            markValid(true);
        else
            markValid(!descriptor.getStepInProgress());
    }
}

