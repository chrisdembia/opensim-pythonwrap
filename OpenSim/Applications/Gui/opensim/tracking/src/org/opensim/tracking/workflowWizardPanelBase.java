/*
 *
 * workflowWizardPanelBase
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.tracking;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import org.openide.WizardDescriptor;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import javax.swing.JComponent;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.modeling.Investigation;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.ViewDB;

/**
 *
 * @author Ayman Habib
 *
 * Base class for all Tracking Workflow panels 
 */
public abstract class workflowWizardPanelBase implements WizardDescriptor.Panel {
    
     public WorkflowDescriptor descriptor;
     private boolean canProceed=true; // Can proceed to next based on context only.
     protected final int UPDATE_FREQUENCY=100; // How often we update the display in milliseconds
    /**
     * Creates a new instance of workflowWizardPanelBase
     */
    public workflowWizardPanelBase() {
    }
    
    /** Execute the step  */
    abstract boolean executeStep();   
    
    public void updateValidity(boolean canProceed){
        if (this.canProceed != canProceed){
            this.canProceed = canProceed;
            fireChangeEvent();
        }
    }

     final public boolean isValid() {
        // If it is always OK to press Next or Finish, then:
        //System.out.println("Is Valid = "+canProceed+" Gui"+((workflowVisualPanelBase)getComponent()).isGuiCanAdvance());
        return (canProceed && ((workflowVisualPanelBase)getComponent()).isGuiCanAdvance());
        // If it depends on some condition (form filled out...), then:
        // return someCondition();
        // and when this condition changes (last form field filled in...) then:
        // fireChangeEvent();
        // and uncomment the complicated stuff below.
    }
     
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

    /**
     * runDynamicInvestigation does all the leg work of setting up the GUI, callback to run
     * a Dynamic investigation and update display with the resulting animation
     */
    protected void runDynamicInvestigation(final Investigation dInvestigation, final Boolean isDeterministic) {
 
        final AbstractModel model = dInvestigation.getModel();
        AbstractModel visModel=null;     // model used for visualization only
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Run Investigation "+dInvestigation.getName());
        final double investigationDuration = (dInvestigation.getFinalTime() - dInvestigation.getStartTime());
        final double startTime = dInvestigation.getStartTime();
        final SimtkAnimationCallback animationCallback = new SimtkAnimationCallback(model);
        
        dInvestigation.getModel().addIntegCallback(animationCallback);  
        /*Restructure
        // show model in new window if possible
         final ModelWindowVTKTopComponent modelWindow = ViewDB.getCurrentModelWindow();
         if (modelWindow==null){
             // Show warning and proceed thatno animation will be done
             DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("No model is currently open. Results will not be visualized"));
         }
         else {
             animationCallback.extractOffsets(modelWindow.getModel());
         }
         */
        progressHandle.start();
        if (isDeterministic)
            progressHandle.switchToDeterminate(100);
        
        int delay = UPDATE_FREQUENCY; //milliseconds
            ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
              //...Perform a task...
/*Restructure                if (modelWindow!=null){
                        modelWindow.getCanvas().updateDisplayFromDynamicModel(animationCallback, false);
                        modelWindow.getCanvas().repaint();
                }*/
            }};
            
            Timer timer = new Timer(delay, taskPerformer);
        timer.start();
        //try {
        dInvestigation.run();
        /*} catch (IOException ex) {
             DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("The following error has been reported. Please fix and retry.\n "+ex.getMessage()));
        
            ex.printStackTrace();
        }*/
        
        timer.stop();

        if (isDeterministic)
            progressHandle.progress(100);
        progressHandle.finish();
//Restructure            dInvestigation.getModel().removeIntegCallback(animationCallback);
        ((JComponent) getComponent()).putClientProperty("Step_executed", Boolean.TRUE);
        System.gc();
    }
    
}
