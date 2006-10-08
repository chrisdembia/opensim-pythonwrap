package org.opensim.tracking;

import java.io.IOException;
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
            component = new ModelLoadingVisualPanel(this);
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
        updateVisibility();
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
        
        component.updateWorkflow(descriptor);
        SimmSubject subject = descriptor.getSubject();
        SimmModel model = descriptor.getModel(); 
        component.appendMessage("Start loading model.\n");
        if (model != null){
            try {
                boolean success=false;
                try {
                    success = ((OpenOsimModelAction) OpenOsimModelAction.findObject(Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(model.getInputFileName());
                } catch (IOException ex) {
                    success=false;
                }
                if (!success)
                    component.appendMessage("Generic Model has failed to load, please check the path.");
                else
                    component.appendMessage("Step 1: Loading generic model - Done.");
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
                component.appendMessage("Generic model has failed to load from file "+model.getInputFileName());
            }
            
            //component.setExecuted(true);
            component.putClientProperty("Step_executed", Boolean.TRUE);
        }
        else{
            DialogDisplayer.getDefault().notify( 
                    new NotifyDescriptor.Message("Generic model has failed to load from file. Path="+subject.getPathToSubject()));
            component.putClientProperty("Step_executed", Boolean.FALSE);
        }
        return true;
    }
    public void updateVisibility()
    {}
}

