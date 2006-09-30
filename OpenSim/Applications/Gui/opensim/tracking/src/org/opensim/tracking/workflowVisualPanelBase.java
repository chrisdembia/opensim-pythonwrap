/*
 *
 * workflowVisualPanelBase
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

import javax.swing.JPanel;
import org.opensim.view.BottomPanelTopComponent;
/**
 *
 * @author Ayman Habib
 *
 * Base class for all visual panels of the tracking workflow to call
 * updatePanel(WorkflowDescriptor) when the panel is displayed.
 * updateWorkflow(WorkflowDescriptor) when the panel is left
 *  keep track of flags to mark
 * executed: if the workflow step has been executed already
 * ready: to indicate if the panel has a valid set of data values to be executed.
 */
public abstract class workflowVisualPanelBase extends JPanel{
    
    workflowWizardPanelBase logicPanel;
    /**
     * Creates a new instance of workflowVisualPanelBase
     */
    protected workflowVisualPanelBase(workflowWizardPanelBase logicPanel) {
        this.logicPanel = logicPanel;
    }
    abstract void updatePanel(WorkflowDescriptor aDescriptor);
    abstract void updateWorkflow(WorkflowDescriptor descriptor);

    abstract public void appendMessage(String message);
    public void displayMessage(String message) {
        BottomPanelTopComponent.findInstance().showErrorMessage(message);
    }
    /**
     * A method to be called to inform the world that the user can hit next
     */
    protected void markValid(boolean valid)
    {
        logicPanel.markValid(valid);
    }
    /**
     * checkValidForm: A method that does the actual validation of the form
     */
    abstract protected boolean checkValidForm();
}
