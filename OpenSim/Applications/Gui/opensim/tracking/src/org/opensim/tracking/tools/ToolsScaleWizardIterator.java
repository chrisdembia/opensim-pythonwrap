package org.opensim.tracking.tools;

import java.awt.Component;
import java.util.HashSet;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Set;
import javax.swing.JComponent;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.openide.WizardDescriptor;
import org.opensim.tracking.MarkerPlacementPanel;
import org.opensim.tracking.ScalingPanel;
import org.opensim.tracking.workflowWizardPanelBase;

public final class ToolsScaleWizardIterator implements WizardDescriptor.Iterator {
   
   // To invoke this wizard, copy-paste and run the following code, e.g. from
   // SomeAction.performAction():
    /*
     */
   
   private int index;
   
   private workflowWizardPanelBase[] panels;
   
   /**
    * Initialize panels representing individual wizard's steps and sets
    * various properties for them influencing wizard appearance.
    */
   private workflowWizardPanelBase[] getPanels() {
      if (panels == null) {
         panels = new workflowWizardPanelBase[] {
            new ScalingPanel(),
            new MarkerPlacementPanel()
         };
         String[] steps = new String[panels.length];
         for (int i = 0; i < panels.length; i++) {
            Component c = panels[i].getComponent();
            // Default step name to component name of panel.
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
               jc.putClientProperty("WizardPanel_contentNumbered", Boolean.FALSE);
               // ClientProperty("Step_executed"
               jc.putClientProperty("Step_executed", Boolean.FALSE);
            }
         }
      }
      return panels;
   }
   
   public WizardDescriptor.Panel current() {
      return getPanels()[index];
   }
   
   public String name() {
      return index + 1 + ". of " + getPanels().length;
   }
   
   public boolean hasNext() {
      return index < getPanels().length - 1;
   }
   
   public boolean hasPrevious() {
      return index > 0;
   }
   
   public void nextPanel() {
      if (!hasNext()) {
         throw new NoSuchElementException();
      }
      index++;
   }
   
   public void previousPanel() {
      if (!hasPrevious()) {
         throw new NoSuchElementException();
      }
      index--;
   }
   
   // If nothing unusual changes in the middle of the wizard, simply:
   //public void addChangeListener(ChangeListener l) {}
   //public void removeChangeListener(ChangeListener l) {}
   
   // If something changes dynamically (besides moving between panels), e.g.
   // the number of panels changes in response to user input, then uncomment
   // the following and call when needed: fireChangeEvent();
    
    private Set<ChangeListener> listeners = new HashSet<ChangeListener>(1);
    public final void addChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.add(l);
        }
    }
    public final void removeChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.remove(l);
        }
    }
    protected final void fireChangeEvent() {
        Iterator<ChangeListener> it;
        synchronized (listeners) {
            it = new HashSet<ChangeListener>(listeners).iterator();
        }
        ChangeEvent ev = new ChangeEvent(this);
        while (it.hasNext()) {
            it.next().stateChanged(ev);
        }
    }
    
   
}
