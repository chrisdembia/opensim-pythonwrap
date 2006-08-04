package org.opensim.tracking;

import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ExecuteWorkflowStepAction extends CallableSystemAction {
    WizardDescriptor.Iterator  iterator;
    public ExecuteWorkflowStepAction(WizardDescriptor.Iterator  iterator)
    {
        this.iterator = iterator;
    }
    public void performAction() {
        // TODO implement action body
        WizardDescriptor.Panel currentPanel = iterator.current();
        if (currentPanel instanceof workflowWizardPanelBase)
            ((workflowWizardPanelBase)currentPanel).executeStep();
    }
    
    public String getName() {
        return NbBundle.getMessage(ExecuteWorkflowStepAction.class, "CTL_ExecuteWorkflowStepAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
