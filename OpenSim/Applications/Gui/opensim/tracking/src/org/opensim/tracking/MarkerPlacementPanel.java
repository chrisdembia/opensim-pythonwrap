package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import javax.swing.event.ChangeListener;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.SimmIKSolverImpl;
import org.opensim.modeling.SimmIKTrial;
import org.opensim.modeling.SimmMarkerData;
import org.opensim.modeling.SimmMarkerPlacer;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimmMotionData;
import org.opensim.modeling.SimmSubject;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.modeling.Storage;
import org.opensim.utils.FileUtils;
import org.opensim.view.OpenOsimModelAction;

public class MarkerPlacementPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private workflowVisualPanelBase component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new MarkerPlacementVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updatePanel(descriptor);
        updateAvailability();
   }
    public void storeSettings(Object settings) {}

    boolean executeStep() {
       // Call scaling with the model and display it in GUI
       SimmSubject subject = descriptor.getSubject();
       AbstractModel model = descriptor.getScaledModel();
       SimmMarkerPlacer placer = subject.getMarkerPlacer();
       AbstractModel markerPlacementModel = model.clone();
       markerPlacementModel.setName(model.getName()+"-MarkersPlaced");
       markerPlacementModel.setup();
       // Create a callback to update geometry
       SimtkAnimationCallback animationCallback = new SimtkAnimationCallback(markerPlacementModel);
       markerPlacementModel.addIntegCallback(animationCallback);
       if (placer.processModel(markerPlacementModel, subject.getPathToSubject())){
          // @todo If output file is specified, associate it with scaledModel        
          //markerPlacementModel.setup();
          boolean success=false;
          try {
             try {
                success = ((OpenOsimModelAction) OpenOsimModelAction.
                        findObject(Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(markerPlacementModel);
             } catch (IOException ex) {
                success=false;
             }
             if (!success)
                component.appendMessage("Marker placement model has failed to load.");
             else
                component.appendMessage("Loading model with placed markers- Done.");
          } catch (ClassNotFoundException ex) {
             ex.printStackTrace();
             component.appendMessage("Model has failed to load.");
          }
          component.putClientProperty("Step_executed", Boolean.TRUE);
       } else
          component.putClientProperty("Step_executed", Boolean.FALSE);
       ;
       
       component.putClientProperty("Step_executed", Boolean.TRUE);
       return true;
    }

    public void updateAvailability()
    {
        //System.out.println("MP:"+descriptor.getStepInProgress()+component.isGuiCanAdvance());
        updateValidity(!descriptor.getStepInProgress() && component.isGuiCanAdvance());
    }
    
}

