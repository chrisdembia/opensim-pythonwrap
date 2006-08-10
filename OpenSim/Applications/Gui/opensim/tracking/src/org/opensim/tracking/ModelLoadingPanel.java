package org.opensim.tracking;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ScaleSet;
import org.opensim.modeling.ScalerInterface;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmScalerImpl;
import org.opensim.modeling.SimmScalingParams;
import org.opensim.modeling.SimmSubject;
import org.opensim.tracking.workflowWizardPanelBase;
import org.opensim.view.OpenOsimModelAction;


public class ModelLoadingPanel extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private ModelLoadingVisualPanel component;
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public ModelLoadingVisualPanel getComponent() {
        if (component == null) {
            component = new ModelLoadingVisualPanel();
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        //return HelpCtx.DEFAULT_HELP;  
        // If you have context help:
        //return new HelpCtx(ModelLoadingPanel.class);
        return new HelpCtx(ModelLoadingPanel.class);
    }
    
    public boolean isValid() {
        // If it is always OK to press Next or Finish, then:
        return checkValidPanel();
        // If it depends on some condition (form filled out...), then:
        // return someCondition();
        // and when this condition changes (last form field filled in...) then:
        // fireChangeEvent();
        // and uncomment the complicated stuff below.
    }
    
    private boolean checkValidPanel() {
        // You can advance only if there's a model
        return component.hasModel();
    }
    
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
     
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        //System.out.println("read settings");
        // Update cached values
        descriptor.updateCachedValues();
        component.updatePanel(descriptor);
    }
    public void storeSettings(Object settings) {
        //System.out.println("Store settings");
       descriptor = (WorkflowDescriptor) settings;
       component.updateWorkflow(descriptor);
     }
    /**
     * The meat of the panel happens in this function which is now associated to the execute button in the GUI
     * it tries to load the model based on user input and report errors on failure.
     */
    public boolean executeStep()
    {   
        // Load model and markers into GUI
        // Create a subject instance. This should be moved to the non-GUI counterpart class.
        // Calling setSubject also creates the model in descriptor;
        //descriptor.setSubject(new SimmSubject(component.getSubjectPath()));
        
        SimmSubject subject = descriptor.getSubject();
        SimmModel model = descriptor.getModel(); 
        if (model != null){
            try {
                // Display original model
                boolean success = ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(model.getInputFileName());
                if (!success)
                    component.setMessage("Model has failed to load, please check the path.");
                else
                    component.setMessage("Step 1: Loading generic model - Done.");
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
                component.setMessage("Model has failed to load from file "+model.getInputFileName());
            }
            component.setExecuted(true);
            
        }
        else
            DialogDisplayer.getDefault().notify( 
                    new NotifyDescriptor.Message("Generic model failed to load."));
        return true;
    }
}

