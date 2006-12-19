package org.opensim.tracking;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.opensim.modeling.Analysis;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.OpenOsimModelAction;
import org.opensim.modeling.InvestigationCMCGait;

public class ReduceResidualsPanelPass1  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private ReduceResidualsVisualPanelPass1 component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new ReduceResidualsVisualPanelPass1(this);
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
        updateAvailability();
    }
    public void storeSettings(Object settings) {
       descriptor = (WorkflowDescriptor) settings;
       component.updateWorkflow(descriptor);
    }

    public boolean executeStep() {
        component.updateWorkflow(descriptor);
        final InvestigationCMCGait rra = new InvestigationCMCGait(descriptor.getSetupRRA_pass1Filename());
        runDynamicInvestigation(rra, false);
         return true;
    }
    
    public void updateAvailability()
    {
        updateValidity(!descriptor.getStepInProgress() && component.isGuiCanAdvance());
    }
   
}

