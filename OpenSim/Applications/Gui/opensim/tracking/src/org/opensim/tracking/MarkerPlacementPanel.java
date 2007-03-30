package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import org.openide.util.HelpCtx;
import org.opensim.modeling.MarkerPlacer;
import org.opensim.modeling.Model;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.ScaleTool;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.FileOpenOsimModelAction;

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

    public boolean executeStep() throws IOException {
       // Call scaling with the model and display it in GUI
       ScaleTool subject = descriptor.getSubject();
       Model model = descriptor.getScaledModel();
       MarkerPlacer placer = subject.getMarkerPlacer();
       Model markerPlacementModel = model.clone();
       // save coords
       int nStates = model.getNumStates();
       double[] saveStates = new double[nStates];
       model.getDynamicsEngine().getConfiguration(saveStates);
       
       markerPlacementModel.setName(model.getName()+"-MarkersPlaced");
       markerPlacementModel.setup();
       // Create a callback to update geometry
       SimtkAnimationCallback animationCallback = SimtkAnimationCallback.CreateAnimationCallback(markerPlacementModel);
       if (placer.processModel(markerPlacementModel, subject.getPathToSubject())){
          // @todo If output file is specified, associate it with scaledModel        
          //markerPlacementModel.setup();
          descriptor.setIKModel(markerPlacementModel);
          // restore states
          markerPlacementModel.getDynamicsEngine().setConfiguration(saveStates);
          markerPlacementModel.getActuatorSet().updateGeometry();
          
          boolean success=false;
          try {
             try {
                success = ((FileOpenOsimModelAction) FileOpenOsimModelAction.
                        findObject(Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(markerPlacementModel);
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

