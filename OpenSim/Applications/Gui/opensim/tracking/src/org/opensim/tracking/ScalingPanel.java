package org.opensim.tracking;

import java.awt.Component;
import java.io.IOException;
import javax.swing.event.ChangeListener;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ScaleSet;
import org.opensim.modeling.ScalerInterface;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmScalerImpl;
import org.opensim.modeling.SimmScalingParams;
import org.opensim.modeling.SimmSubject;
import org.opensim.utils.FileUtils;
import org.opensim.view.OpenOsimModelAction;

public class ScalingPanel  extends workflowWizardPanelBase {
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private ScalingVisualPanel component;
    SimmModel scaledModel;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new ScalingVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        //return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        return new HelpCtx(ScalingPanel.class);
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
    }
    public void storeSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updateWorkflow(descriptor);
    }
    
    public boolean executeStep()
    {   

        // Call scaling with the model and display it in GUI
        //ExecOpenSimProcess.execute("Scale -S "+"900045_setup_scale_ik.xml", new String[0], new File("C:\\Projects\\fca\\900045"));
        SimmSubject subject = descriptor.getSubject();
        SimmScalingParams params = subject.getScalingParams();
        SimmModel model = descriptor.getModel();
        ScalerInterface scaler = new SimmScalerImpl(model);
        ScaleSet scaleSet = params.getScaleSet(model, subject.getPathToSubject());
        component.appendMessage("Obtained scale factors.\n");
        boolean preserveMassDistribution = params.getPreserveMassDist();
        double mass = subject.getMass();
        boolean success = scaler.scaleModel(scaleSet,preserveMassDistribution, mass);
        if (success)
            component.appendMessage("Model has been scaled successfully.\n");
        else
            component.appendMessage("Failed to scale generic model.\n");
        if (success) {  // Open scaled model 
            model.setName(model.getName()+"- Scaled");
            String outputModelName = getOutputModelPath(descriptor);
            params.setOutputModelFileName(outputModelName);
            component.appendMessage("Writing output files.\n");
            params.writeOutputFiles(model, subject.getPathToSubject());
             try {
                component.appendMessage("Opening Scaled Model.\n");
                
                /* A kluge to test how easy is it to overlay models!
                scaledModel = new SimmModel(subject.getPathToSubject()+outputModelName);
                scaledModel.setup();
                TopComponent top = (TopComponent) TopComponent.getRegistry().getOpened().iterator().next();
                if (top instanceof ModelWindowVTKTopComponent){
                    ((ModelWindowVTKTopComponent) top).getCanvas().loadModel(scaledModel);
                }
                */
                // Display original model
                ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(subject.getPathToSubject()+outputModelName);
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
            component.putClientProperty("Step_executed", Boolean.TRUE);

        }
        else
           component.putClientProperty("Step_executed", Boolean.FALSE);
        return true;
    }    

    private String getOutputModelPath(WorkflowDescriptor descriptor) {
        SimmSubject subject = descriptor.getSubject();
        SimmScalingParams params = subject.getScalingParams();
        String userSpecifiedName = params.getOutputModelFileName();
        if (userSpecifiedName.equalsIgnoreCase("Unassigned")){
            String localName = FileUtils.getNextAvailableName(subject.getPathToSubject(), 
                                                               subject.getGenericModelParams().getModelFileName(),
                                                               "xml");
            return localName;
        }
        else
            return userSpecifiedName;
    }
}

