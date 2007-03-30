package org.opensim.tracking;

import java.awt.Component;
import java.io.File;
import org.openide.util.HelpCtx;
import org.opensim.view.base.ExecOpenSimProcess;

public class MakeDModelPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private MakeDModelVisualPanel component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new MakeDModelVisualPanel(this);
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
        String modelFilename = descriptor.getDynamicsModelFile();
        String sdfastfile=component.getSDFastfilename();
        String command="makeSDFastModel -IM "+modelFilename+" -OM "+sdfastfile+" -ML "+component.getModelLibrary();
        File f = new File(modelFilename);
        File outFileDir = f.getParentFile();
        boolean success = ExecOpenSimProcess.execute(command, new String[]{""}, outFileDir );
        component.putClientProperty("Step_executed", Boolean.TRUE);
        return true;
   }
    
    public void updateAvailability()
    {
        //System.out.println("Prog="+descriptor.getStepInProgress()+" Gui"+component.isGuiCanAdvance());
        updateValidity(!descriptor.getStepInProgress() && component.isGuiCanAdvance());
    }
}

