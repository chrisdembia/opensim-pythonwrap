package org.opensim.gait;

import java.awt.Dialog;
import java.net.URL;
import java.text.MessageFormat;
import javax.help.HelpBroker;
import javax.help.HelpSet;
import javax.help.HelpSetException;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class GaitWorkflowAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        WizardDescriptor.Iterator iterator = new workflowWizardIterator();
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator);
        wizardDescriptor.setModal(false);

        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle("Subject Specific Gait Workflow");
        //wizardDescriptor.putProperty("WizardPanel_helpDisplayed",Boolean.TRUE);

        Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
        if (!cancelled) {
            // do something
        }

    }
    
    public String getName() {
        return NbBundle.getMessage(GaitWorkflowAction.class, "CTL_GaitWorkflowAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        URL url= this.getClass().getResource("help/help.hs");

        HelpSet hs;
        try {
            hs = new HelpSet(null, url);
            HelpBroker hb = hs.createHelpBroker();
        } catch (HelpSetException ex) {
            ex.printStackTrace();
        }    
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
