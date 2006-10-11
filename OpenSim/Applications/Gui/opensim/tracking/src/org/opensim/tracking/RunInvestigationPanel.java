package org.opensim.tracking;

import java.awt.Component;
import java.util.TimerTask;
import java.util.Timer;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.modeling.Investigation;
import org.opensim.modeling.Model;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.ViewDB;

public class RunInvestigationPanel  extends workflowWizardPanelBase{
    SimtkAnimationCallback animationCallback;
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private AnalysisVisualPanel component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new AnalysisVisualPanel(this);
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
        updateVisibility();
    }
    public void storeSettings(Object settings) {}

    boolean executeStep() {
        // Make investigation and run it
        final Investigation dInvestigation = component.getInvestigation();
        runDynamicInvestigation(dInvestigation, true);
        return true;
    }
    public void updateVisibility()
    {
        markValid(!descriptor.getStepInProgress());        
    }

}

