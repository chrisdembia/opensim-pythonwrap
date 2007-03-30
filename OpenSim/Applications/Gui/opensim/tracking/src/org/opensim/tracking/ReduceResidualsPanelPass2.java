package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import org.openide.util.HelpCtx;
import org.opensim.modeling.CMCTool;

public class ReduceResidualsPanelPass2  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private ReduceResidualsVisualPanelPass2 component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new ReduceResidualsVisualPanelPass2(this);
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

    public boolean executeStep() throws IOException {
        
       component.updateWorkflow(descriptor);
        final CMCTool rra = new CMCTool(descriptor.getSetupRRA_pass2Filename());
        try {
            runDynamicTool(rra,false);
        } catch (IOException ex) {
            ex.printStackTrace();
            return false;
        }
        return true;
    }
    
    public void updateAvailability()
    {
        updateValidity(!descriptor.getStepInProgress() && component.isGuiCanAdvance());
    }
   
}

