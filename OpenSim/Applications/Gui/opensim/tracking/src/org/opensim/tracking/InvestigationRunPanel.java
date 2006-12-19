package org.opensim.tracking;

import java.awt.Component;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.modeling.Investigation;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.ViewDB;

public class InvestigationRunPanel  extends workflowWizardPanelBase{
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private InvestigationVisualPanel component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new InvestigationVisualPanel(this);
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
        updateAvailability();
    }
    public void storeSettings(Object settings) {}

    public boolean executeStep() {
        // Make investigation and run it
        final Investigation dInvestigation = component.getInvestigation();
        runDynamicInvestigation(dInvestigation, true);
        return true;
    }
    public void updateAvailability()
    {
        updateValidity(!descriptor.getStepInProgress());
    }

   public void updateVisibility() {
      //Restructure
   }

}

