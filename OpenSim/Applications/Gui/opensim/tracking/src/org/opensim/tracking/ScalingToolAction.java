package org.opensim.tracking;

import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.text.MessageFormat;
import javax.swing.JButton;
import javax.swing.JComponent;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimmSubject;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.pub.ViewDB;

public final class ScalingToolAction extends CallableSystemAction {
    
    CallableSystemAction executeStepAction;
    public void performAction() {
        // TODO implement action body
       /*
        final WizardDescriptor.Iterator iterator = new ScalingToolWizardIterator();
        WorkflowDescriptor  descriptor = new WorkflowDescriptor();
        
        // Get current model from GUI and set it in descriptor as generic model
         final ModelWindowVTKTopComponent modelWindow = ViewDB.getCurrentModelWindow();
         if (modelWindow==null){
             // Show warning and proceed thatno animation will be done
             DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("No model is currently open. Please file a bug with OpenSim"));
             return;
         }
        
        AbstractModel genericModel = modelWindow.getModel();
        descriptor.setGenericModel(genericModel);
        SimmSubject subject = descriptor.getSubject();
        String modelPath = genericModel.getInputFileName();
        subject.setPathToSubject(new File(modelPath).getParent()+File.separatorChar);
        // Set values in descriptor based on current context
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, descriptor);
        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle("Scaling Tool");
        // Add an Execute button to the bottom panel
        executeStepAction = new ExecuteWorkflowStepAction(iterator);
        //wizardDescriptor.setAdditionalOptions(new Object[] {executeButton});
        
        wizardDescriptor.setButtonListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                Object obj = e.getSource();
                if (obj instanceof JButton){
                      JButton selected = (JButton)obj;
                      // FIXME: this test should be replaced with a robust one
                      if (selected.getText().equalsIgnoreCase("Next >") ||
                          selected.getText().equalsIgnoreCase("Finish")  ){
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
        dialog.setModal(false);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
        if (!cancelled) {
            // do something
        }*/
    }
    
    public String getName() {
        return NbBundle.getMessage(ScalingToolAction.class, "CTL_ScalingToolAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        setEnabled(false);
        ViewDB.registerModelCommand(this);
   }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
