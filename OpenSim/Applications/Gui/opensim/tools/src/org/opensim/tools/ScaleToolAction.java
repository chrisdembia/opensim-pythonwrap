package org.opensim.tools;

import java.awt.Dialog;
import java.io.File;
import java.text.MessageFormat;
import org.openide.DialogDisplayer;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmGenericModelParams;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmScalingParams;
import org.opensim.modeling.SimmSubject;
import org.opensim.tools.common.ExecOpenSimProcess;
import org.opensim.view.ViewDB;

public final class ScaleToolAction extends CallableSystemAction {
    
    SimmGenericModelParams genericModelParams=null;
    SimmScalingParams scalingParams=null;
    SimmMarkerPlacementParams markerPlacementParams=null;
    
    public void performAction() {
        // TODO implement action body

        // Here we're scaling current model, 
        WizardDescriptor.Iterator iterator = new ScaleToolWizardIterator();
        // Create a fresh workflow that we'll use only for Sclaing and marker placement.
        SimmModel curModel = ViewDB.getInstance().getCurrentModelWindow().getModel();
        String currentModelFile = curModel.getInputFileName();
        // Should warn about model saving but all tools now work on a file rather than a model.
        // so that's the only way to do it without modifying the API.
        curModel.print(currentModelFile);
        TrackingWorkflow scaleWorkflow = new TrackingWorkflow();
        scaleWorkflow.getGenericModelParams().setModelFileName(currentModelFile);
        WizardDescriptor wizardDescriptor = new WizardDescriptor(iterator, scaleWorkflow);
        // {0} will be replaced by WizardDescriptor.Panel.getComponent().getName()
        // {1} will be replaced by WizardDescriptor.Iterator.name()
        wizardDescriptor.setTitleFormat(new MessageFormat("{0} ({1})"));
        wizardDescriptor.setTitle("Scaling Tool");
        Dialog dialog = DialogDisplayer.getDefault().createDialog(wizardDescriptor);
        dialog.setVisible(true);
        dialog.toFront();
        boolean cancelled = wizardDescriptor.getValue() != WizardDescriptor.FINISH_OPTION;
        if (!cancelled) {
            // Save scaleWorkflow into an intermediate file and run scale in a reasonable directory!
            SimmSubject temp = new SimmSubject();
            temp.getGenericModelParams().copyData(scaleWorkflow.getGenericModelParams());
            scaleWorkflow.getScalingParams().copy().print("CopyInGui.xml");
            temp.getScalingParams().copyData(scaleWorkflow.getScalingParams());
            temp.getMarkerPlacementParams().copyData(scaleWorkflow.getMarkerPlacementParams());
            // Find a reasonable directory to run 
            temp.print("_scale_ik_setup.xml");
            boolean success = ExecOpenSimProcess.execute("Scale -S _scale_ik_setup.xml", new String[1], new File("C:/Test/wf"));
            if (success){
                // Open the scaled model in the GUI.
                
            }
            
        }
        
    }
    
    public String getName() {
        return NbBundle.getMessage(ScaleToolAction.class, "CTL_ScaleAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
