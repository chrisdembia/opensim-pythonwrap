package org.opensim.tracking;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.Timer;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.modeling.Model;
import org.opensim.modeling.IKTool;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.motionviewer.MotionsDB;
import org.opensim.view.SingleModelVisuals;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

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
        final double investigationDuration = endTime - startTime;
        final Model ikModel = ik.getModel();
        
         final SimtkAnimationCallback animationCallback = SimtkAnimationCallback.CreateAnimationCallback(ikModel);
         animationCallback.setStepInterval(1);         
         progressHandle.start();
         
         int delay = 50; //milliseconds
         final SingleModelVisuals visModel = ViewDB.getInstance().getModelVisuals(ikModel);
         final ViewDB viewdb = ViewDB.getInstance();
         
         // Adaptively compute frame display time and use it as guess for timer period
         long t0 = 0, t1=0;
         int frameDisplayTime=0;
         t0 = System.currentTimeMillis();
         viewdb.updateModelDisplay(visModel, animationCallback);
         t1 = System.currentTimeMillis();
         frameDisplayTime = (int)(t1-t0);
         //System.out.println("frameDisplayTime="+frameDisplayTime)       ;
         ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
               viewdb.updateModelDisplay(visModel, animationCallback);
            }
         };
         Timer timer = new Timer(frameDisplayTime, taskPerformer);
         timer.start();
         // Execute IK. We're already on a worker thread
         ik.run();

         viewdb.updateModelDisplay(visModel, animationCallback);
         timer.stop();

         progressHandle.finish();
        // Associate motion to model
        component.putClientProperty("Step_executed", Boolean.TRUE);
        
        // Load resulting motion and associate it with ik model
        //unnecessary OpenSimDB.getInstance().setCurrentModel(ikModel);        
        String ikFilePath = new File(ik.getDocumentFileName()).getParent();
        String motionFilePath = ikFilePath+File.separator+ik.getIKTrialSet().get(0).getOutputMotionFilename();
        if (new File(motionFilePath).exists())
            MotionsDB.getInstance().loadMotionFile(motionFilePath);
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

