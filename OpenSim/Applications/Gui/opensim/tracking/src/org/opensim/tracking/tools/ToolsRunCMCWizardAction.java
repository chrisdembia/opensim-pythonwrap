package org.opensim.tracking.tools;

import java.awt.Component;
import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.text.MessageFormat;
import javax.swing.JButton;
import javax.swing.JComponent;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.swingui.SwingWorker;
import org.opensim.tracking.ComputedMuscleControlPanel;
import org.opensim.tracking.WorkflowDescriptor;
import org.opensim.tracking.workflowWizardPanelBase;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

// An example action demonstrating how the wizard could be called from within
// your code. You can copy-paste the code below wherever you need.
public final class ToolsRunCMCWizardAction extends CallableSystemAction {
   
   private workflowWizardPanelBase[] panels;   
   
   public void performAction() {
      WorkflowDescriptor descriptor = new WorkflowDescriptor();

      WizardDescriptor wizardDescriptor = new WizardDescriptor(getPanels(), descriptor);
      // {0} will be replaced by WizardDesriptor.Panel.getComponent().getName()
      wizardDescriptor.setTitleFormat(new MessageFormat("{0}"));
      wizardDescriptor.setTitle("Computed Muscle Control");
      //wizardDescriptor.setAdditionalOptions(new Object[] {executeButton});
      Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
      dialog.setVisible(true);
      dialog.toFront();
      boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
      if (!cancelled) {
         final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
               try {
                  ((workflowWizardPanelBase)panels[0]).executeStep();
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
   
   /**
    * Initialize panels representing individual wizard's steps and sets
    * various properties for them influencing wizard appearance.
    */
   private WizardDescriptor.Panel[] getPanels() {
      if (panels == null) {
         panels = new workflowWizardPanelBase[] {
            new ComputedMuscleControlPanel()
         };
         String[] steps = new String[panels.length];
         for (int i = 0; i < panels.length; i++) {
            Component c = panels[i].getComponent();
            // Default step name to component name of panel. Mainly useful
            // for getting the name of the target chooser to appear in the
            // list of steps.
            steps[i] = c.getName();
            if (c instanceof JComponent) { // assume Swing components
               JComponent jc = (JComponent) c;
               // Sets step number of a component
               jc.putClientProperty("WizardPanel_contentSelectedIndex", new Integer(i));
               // Sets steps names for a panel
               jc.putClientProperty("WizardPanel_contentData", steps);
               // Turn on subtitle creation on each step
               jc.putClientProperty("WizardPanel_autoWizardStyle", Boolean.TRUE);
               // Show steps on the left side with the image on the background
               jc.putClientProperty("WizardPanel_contentDisplayed", Boolean.TRUE);
               // Turn on numbering of all steps
               jc.putClientProperty("WizardPanel_contentNumbered", Boolean.TRUE);
               
            }
         }
      }
      return panels;
   }
   
   public String getName() {
      return "Computed Muscle Control...";
   }
   
   public String iconResource() {
      return null;
   }
   
   public HelpCtx getHelpCtx() {
      return HelpCtx.DEFAULT_HELP;
   }
   
   protected boolean asynchronous() {
      return false;
   }
   
   public boolean isEnabled() {
      return true;
   }

   protected void initialize() {
      super.initialize();
   }
   
}

