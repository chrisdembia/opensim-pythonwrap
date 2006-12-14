package org.opensim.tracking.tools;

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
import org.opensim.tracking.ExecuteWorkflowStepAction;
import org.opensim.tracking.WorkflowDescriptor;
import org.opensim.view.OpenSimDB;
import org.opensim.view.ViewDB;

public final class ToolsScaleAction extends CallableSystemAction {
   
   public void performAction() {
     final WizardDescriptor.Iterator iterator = new ToolsScaleWizardIterator();
     WorkflowDescriptor descriptor = new WorkflowDescriptor();
     descriptor.setGenericModel(OpenSimDB.getInstance().getCurrentModel());
     WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, descriptor);
     // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
     // {1} will be replaced by WizardDescriptor.Iterator.name()
     wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
     wizardDescriptor.setTitle("Scaling Wizard...");

     final CallableSystemAction executeStepAction = new ExecuteWorkflowStepAction(iterator);
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
    dialog.setVisible(true);
    dialog.toFront();
    boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
    if (!cancelled) {
        // do something
    }
      // TODO implement action body
   }
   
   public String getName() {
      return NbBundle.getMessage(ToolsScaleAction.class, "CTL_ScaleAction");
   }
   
   protected void initialize() {
      super.initialize();
      // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
      putValue("noIconInMenu", Boolean.TRUE);
      ViewDB.getInstance().registerModelCommand(this);
   }
   
   public HelpCtx getHelpCtx() {
      return HelpCtx.DEFAULT_HELP;
   }
   
   protected boolean asynchronous() {
      return false;
   }

   public boolean isEnabled() {
 
      return ViewDB.getInstance().getCurrentModel()!=null;
   }
   
}
