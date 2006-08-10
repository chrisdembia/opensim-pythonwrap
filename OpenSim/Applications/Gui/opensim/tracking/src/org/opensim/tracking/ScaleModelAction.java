package org.opensim.tracking;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class ScaleModelAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        /*
        SimmScalingParams params = subject.getScalingParams();
        SimmModel model = descriptor.getModel();
        ScalerInterface scaler = new SimmScalerImpl(model);
        ScaleSet scaleSet = params.getScaleSet(model, subject.getPathToSubject());
        boolean preserveMassDistribution = params.getPreserveMassDist();
        double mass = subject.getMass();
        boolean success = scaler.scaleModel(scaleSet,preserveMassDistribution, mass);
        model.setName(model.getName()+"- Scaled");
        String outputModelName = getOutputModelPath(descriptor);
        params.setOutputModelFileName(outputModelName);
        params.writeOutputFiles(model, subject.getPathToSubject());
        try {
            // Display original model
            ((OpenOsimModelAction) OpenOsimModelAction.findObject(
                    Class.forName("org.opensim.view.OpenOsimModelAction"))).loadModel(subject.getPathToSubject()+outputModelName);
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
         **/
    }
    
    public String getName() {
        return NbBundle.getMessage(ScaleModelAction.class, "CTL_ScaleModelAction");
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
    /**
     * This methods sets all the parameters necessary for scaling regardless of whether
     * scaling is done thru workflow or as a separate command
     */
    public void setParams() {
        
    }
}
