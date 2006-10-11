package org.opensim.tracking;

import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.WizardDescriptor;
import org.openide.util.Cancellable;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.swingui.SwingWorker;

/**
 * Execute a task of the workflow on a worker thread
 */
public final class ExecuteWorkflowStepAction extends CallableSystemAction {
    WizardDescriptor.Iterator  iterator;
    static boolean executing=false;
    public ExecuteWorkflowStepAction(WizardDescriptor.Iterator  iterator)
    {
        this.iterator = iterator;
    }
    public void performAction() {
        // TODO implement action body
        final WizardDescriptor.Panel currentPanel = iterator.current();
        
        // Do not execute on event patching thread now so as not to freeze the GUI
        if (currentPanel instanceof workflowWizardPanelBase){
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle(
                "Executing "+currentPanel.getComponent().getName()+"...", 
                new Cancellable(){
                public boolean cancel() {
                    iterator.previousPanel();
                    return true;
                }});
        /*
        JComponent progressComp=ProgressHandleFactory.createProgressComponent(progressHandle);
        final JDialog progressframe = new JDialog(new JFrame());
        progressframe.setTitle(currentPanel.getComponent().getName()+ " progress ...");
        progressframe.setAlwaysOnTop(true);
        progressframe.setModal(false);
        progressframe.setLocation(500,500);
        progressframe.setPreferredSize(new Dimension(300,60));
        //progressframe.setUndecorated(true);
        progressframe.getContentPane().setLayout(new java.awt.BorderLayout());
        progressframe.getContentPane().add(progressComp);
        progressframe.pack();
         **/
        progressHandle.start();
        
        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                ((workflowWizardPanelBase)currentPanel).descriptor.stepInProgress=true;
                ((workflowWizardPanelBase)currentPanel).executeStep();
                ((workflowWizardPanelBase)currentPanel).descriptor.stepInProgress=false;
                return this;
            };
           public void finished() {
               progressHandle.finish();
               workflowWizardPanelBase displayedPanel = (workflowWizardPanelBase) iterator.current();
               displayedPanel.updateVisibility();
               //progressframe.dispose();

            };
         };
        worker.start();
        //progressframe.setVisible(true);
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
