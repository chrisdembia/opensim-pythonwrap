package org.opensim.tracking;

import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.swingui.SwingWorker;

public final class ExecuteWorkflowStepAction extends CallableSystemAction {
    WizardDescriptor.Iterator  iterator;
    public ExecuteWorkflowStepAction(WizardDescriptor.Iterator  iterator)
    {
        this.iterator = iterator;
    }
    public void performAction() {
        // TODO implement action body
        final WizardDescriptor.Panel currentPanel = iterator.current();
        // Do not execute on event patching thread now so as not to freeze the GUI
        if (currentPanel instanceof workflowWizardPanelBase){
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Executing "+currentPanel.getComponent().getName()+"...");
        progressHandle.start();

        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                ((workflowWizardPanelBase)currentPanel).executeStep();
                return this;
            };
            public void finished() {
               progressHandle.finish();
            };
         };
        worker.start();
        /*    SwingUtilities.invokeLater(
                    new Runnable(){
                        public void run(){
                            ((workflowWizardPanelBase)currentPanel).executeStep();
                        };
                    });*/
        }
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
