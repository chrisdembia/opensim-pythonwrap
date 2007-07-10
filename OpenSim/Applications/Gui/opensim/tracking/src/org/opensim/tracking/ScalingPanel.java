package org.opensim.tracking;

import java.awt.Component;
import java.io.File;
import java.io.IOException;
import org.openide.util.HelpCtx;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.ScaleSet;
import org.opensim.modeling.Model;
import org.opensim.modeling.ModelScaler;
import org.opensim.modeling.ScaleTool;
import org.opensim.utils.FileUtils;
import org.opensim.view.FileOpenOsimModelAction;

public class ScalingPanel  extends workflowWizardPanelBase {
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private ScalingVisualPanel component;
    Model scaledModel;
    
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
        updateAvailability();
    }
    public void storeSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updateWorkflow(descriptor);
    }
    
    public boolean executeStep() throws IOException
    {   
        // Call scaling with the model and display it in GUI
        ScaleTool subject = descriptor.getSubject();
        ModelScaler params = subject.getModelScaler();
        Model model = descriptor.getModel();
        Model scaledModel = model.clone();
        scaledModel.setName(model.getName()+"-Scaled");
        try {
        // This should be moved after processModel or geometry changes caused by scaling
        // should be probagated properly.
            scaledModel.setup(); 
        } catch (IOException ex) {
            ex.printStackTrace();
        } 
         
         if (params.processModel(scaledModel, subject.getPathToSubject(), subject.getSubjectMass())){
           // @todo If output file is specified, associate it with scaledModel
           descriptor.setScaledModel(scaledModel);
           boolean success=false;
           try {
              try {
                 success = ((FileOpenOsimModelAction) FileOpenOsimModelAction.
                         findObject(Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(scaledModel);
              } catch (IOException ex) {
                 success=false;
              }
              if (!success)
                 component.appendMessage("Scaled model has failed to load.");
              else
                 component.appendMessage("Loading scaled model - Done.");
           } catch (ClassNotFoundException ex) {
              ex.printStackTrace();
              component.appendMessage("Scaled model has failed to load.");
           }
           component.putClientProperty("Step_executed", Boolean.TRUE);
        }
        else
           component.putClientProperty("Step_executed", Boolean.FALSE);
       /*Restructure
        ScalerInterface scaler = new SimmScalerImpl(model);
        ScaleSet scaleSet = params.getScaleSet(model, subject.getPathToSubject());
        component.appendMessage("Obtained scale factors.\n");
        ArrayDouble factors = new ArrayDouble(0.0,3);
        scaleSet.get(1).getScaleFactors(factors);
        System.out.println(factors.getitem(0)+factors.getitem(1)+factors.getitem(2));
        boolean preserveMassDistribution = params.getPreserveMassDist();
        double mass = subject.getMass();
        boolean success = scaler.scaleModel(scaleSet,preserveMassDistribution, mass);
        if (success)
            component.appendMessage("Model has been scaled successfully.\n");
        else
            component.appendMessage("Failed to scale generic model.\n");
        if (success) {  // Open scaled model 
            // We should never change the name of OpenSimObjects
            // that are stored in maps since their name is used by the OpenSimObject.hash()
            // used as an ID everywhere.
            //
            String saveName = model.getName();
            model.setName(saveName+"- Scaled");
            String outputModelName = getOutputModelPath(descriptor);
            params.setOutputModelFileName(outputModelName);
            component.appendMessage("Writing output files.\n");
            params.writeOutputFiles(model, null);   ///PathFix
                
            model.setName(saveName); 
            //double sf[] = new double[3];
            //model.getSimmKinematicsEngine().getBody("pelvis").getDisplayer().getScaleFactors(sf);
            //System.out.println("Scale factors for  pelvis for model in memory"+sf[0]);
             try {
                component.appendMessage("Opening Scaled Model.\n");
                String modelFileName = outputModelName;
                if (!(new File(modelFileName).isAbsolute())){
                    modelFileName = subject.getPathToSubject()+File.separatorChar+outputModelName;
                }
                // Display original model
                ((FileOpenOsimModelAction) FileOpenOsimModelAction.findObject(
                        Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(modelFileName);
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
         }
        */
        return true;
    }    

    private String getOutputModelPath(WorkflowDescriptor descriptor) {
        ScaleTool subject = descriptor.getSubject();
        ModelScaler params = subject.getModelScaler();
        String userSpecifiedName = params.getOutputModelFileName();
           /** Restructure
        if (userSpecifiedName.equalsIgnoreCase("Unassigned")){
            String localName = FileUtils.getNextAvailableName(subject.getPathToSubject(), 
                                                               subject.getGenericModelMaker().getModelFileName(),
                                                               "xml");
            return localName;
        }
        else
            */
            return userSpecifiedName;
    }
    
    public void updateAvailability()
    {
        updateValidity(!descriptor.getStepInProgress() && component.isGuiCanAdvance());
    }
}

