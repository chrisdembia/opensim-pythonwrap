package org.opensim.tracking;

import java.awt.Dialog;
import java.io.IOException;
import java.text.MessageFormat;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.swingui.SwingWorker;

public final class InvestigationAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        WizardDescriptor.Iterator iterator = new InvestigationWizardIterator();
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, new WorkflowDescriptor());
        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle("Run investigation");
        Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
        if (!cancelled) {
            final InvestigationRunPanel curPanel = (InvestigationRunPanel) iterator.current();
                final SwingWorker worker = new SwingWorker() {

                public Object construct()  { // runs in a worker thread
               try {
                  curPanel.executeStep(); 
               } catch (IOException ex) {
                  ex.printStackTrace();
               } 
                   return this;
                }
                public void finished() {
                }
                };
            worker.start();
         }
    }
    
    public String getName() {
        return NbBundle.getMessage(InvestigationAction.class, "CTL_InvestigationAction");
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
