package org.opensim.tracking;

import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.MessageFormat;
import javax.swing.JButton;
import javax.swing.JComponent;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

/**
 * A Class responsible for constructing and showing the tracking workflow wizard
 */
public final class TrackingWorkflowAction extends CallableSystemAction {
    
    static CallableSystemAction executeStepAction;
    public void performAction() {
        // TODO implement action body
        final WizardDescriptor.Iterator iterator = new workflowWizardIterator();
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, new WorkflowDescriptor());
        wizardDescriptor.putProperty("WizardPanel_contentNumbered",Boolean.TRUE);
        wizardDescriptor.setModal(false);

        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle(NbBundle.getMessage(TrackingWorkflowAction.class, "CTL_TrackWorkflowWizardTitle"));
         //wizardDescriptor.putProperty("WizardPanel_helpDisplayed",Boolean.TRUE);
        
        // Add an Execute button to the bottom panel
        executeStepAction = new ExecuteWorkflowStepAction(iterator);
        //wizardDescriptor.setAdditionalOptions(new Object[] {executeButton});
        wizardDescriptor.setButtonListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                Object obj = e.getSource();
                if (obj instanceof JButton){
                      JButton selected = (JButton)obj;
                      // FIXME: this test should be replaced with a robust one
                      if (selected.getText().equalsIgnoreCase("Next >")){
                         // Execute action in addition to Next>
                          JComponent curComponent = (JComponent) iterator.current().getComponent();
                          // Execute only if not executed yet!
                          Object state = curComponent.getClientProperty("Step_executed");
                          if (state instanceof Boolean && ((Boolean)state).booleanValue()==false)
                            executeStepAction.performAction();
                    }
                }
            }});
        Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
        dialog.setResizable(true);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
        // Potentially ask user to save.
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
