package org.opensim.tracking;

import java.awt.Dialog;
import java.text.MessageFormat;
import javax.swing.JButton;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class TrackingWorkflowAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        WizardDescriptor.Iterator iterator = new workflowWizardIterator();
        WorkflowDescriptor  workflow = new WorkflowDescriptor();
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, workflow);
        wizardDescriptor.putProperty("WizardPanel_contentNumbered",Boolean.FALSE);
        wizardDescriptor.setModal(false);

        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle("OpenSim Tracking Workflow");
         //wizardDescriptor.putProperty("WizardPanel_helpDisplayed",Boolean.TRUE);
        JButton executeButton = new JButton(new ExecuteWorkflowStepAction(iterator));
        wizardDescriptor.setAdditionalOptions(new Object[] {executeButton});
        Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;

    }
    
    public String getName() {
        return NbBundle.getMessage(TrackingWorkflowAction.class, "CTL_TrackWorkflowAction");
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
