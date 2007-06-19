package org.opensim.tracking;

import java.awt.Component;
import java.io.File;
import java.lang.reflect.InvocationTargetException;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.view.JavaAnimationCallback;
import org.opensim.modeling.Model;
import org.opensim.modeling.IKTool;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.view.pub.ViewDB;
import javax.swing.SwingUtilities;

public class IKPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private IKVisualPanel component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new IKVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
    /*
    private final Set<ChangeListener> listeners = new HashSet<ChangeListener>(1);
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
     */
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updatePanel(descriptor);
        updateAvailability();
    }
    public void storeSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updateWorkflow(descriptor);
    }
    
    /**
     * Execute IK Step
     */
    public boolean executeStep() {
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Running Inverse Kinematics ");
        final IKTool ik = component.getSimulationTool();
        // @FIXME should be current trial
        final double startTime = ik.getIKTrialSet().get(0).getStartTime();
        final double endTime = ik.getIKTrialSet().get(0).getEndTime();
        final Model ikModel = ik.getModel();
        
         final JavaAnimationCallback animationCallback = new JavaAnimationCallback(ikModel);
         ikModel.addIntegCallback(animationCallback);
         animationCallback.setStepInterval(3);  
         progressHandle.start();
                  
         // Execute IK. We're already on a worker thread
         ik.run();

         try {
            SwingUtilities.invokeAndWait(new Runnable(){
               public void run() {
                  ViewDB.getInstance().updateModelDisplay(ikModel);
               }});
         } catch (InterruptedException ex) {
            ex.printStackTrace();
         } catch (InvocationTargetException ex) {
            ex.printStackTrace();
         }
         
         progressHandle.finish();
        // Associate motion to model
        component.putClientProperty("Step_executed", Boolean.TRUE);
        
        // Load resulting motion and associate it with ik model
        //unnecessary OpenSimDB.getInstance().setCurrentModel(ikModel);        
        String ikFilePath = new File(ik.getDocumentFileName()).getParent();
        final String motionFilePath = ikFilePath+File.separator+ik.getIKTrialSet().get(0).getOutputMotionFilename();
        if (new File(motionFilePath).exists()) {
            // Run in Swing thread since it calls MotionDisplayer.classifyColumn down the line which makes calls to vtk glyph stuff
            try {
               SwingUtilities.invokeAndWait(new Runnable(){
                  public void run() {
                     MotionsDB.getInstance().loadMotionFile(motionFilePath);
                  }});
            } catch (InterruptedException ex) {
               ex.printStackTrace();
            } catch (InvocationTargetException ex) {
               ex.printStackTrace();
            }
        }
        // Remove callback as it's owned by Java and we don't want it destroyed along with the model.
        ikModel.removeIntegCallback(animationCallback);
        return false;
    }
    
    public void updateAvailability()
    {
        Object state = component.getClientProperty("Step_executed");
        if (state instanceof Boolean && ((Boolean)state).booleanValue()==true)
            updateValidity(true);
        else {
            updateValidity(!descriptor.getStepInProgress());            
        }
    }

   public void updateVisibility() {
   }
}

