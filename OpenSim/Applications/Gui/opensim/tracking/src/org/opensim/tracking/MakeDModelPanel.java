package org.opensim.tracking;

import java.awt.Component;
import java.io.File;
import java.io.IOException;
import javax.swing.event.ChangeListener;
import org.openide.util.HelpCtx;
import org.opensim.modeling.SimmModel;

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

    }
    public void storeSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updateWorkflow(descriptor);
    }

    boolean executeStep() {
        String modelFilename = descriptor.getDynamicsModelFile();
        String dynamicsDirectory=component.getDynamicsDirectory();
        SimmModel model;
        try { //String aFolderName, String aMuscleFileName, String aBonePath, String aKineticsFile)
            model = new SimmModel(modelFilename);
         model.setup();  // Just incase some setup is needed before Dynamcis are saved
        if (dynamicsDirectory.endsWith(File.separator))
            model.getSimmKinematicsEngine().saveDynamics(dynamicsDirectory, 
                    component.getMuscleFilename(),
                    ".",
                    component.getKineticsFilename());
        else
            model.getSimmKinematicsEngine().saveDynamics(dynamicsDirectory+File.separator,
                    component.getMuscleFilename(),
                    ".",
                    component.getKineticsFilename());
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        component.putClientProperty("Step_executed", Boolean.TRUE);
        return true;
   }
    
}

