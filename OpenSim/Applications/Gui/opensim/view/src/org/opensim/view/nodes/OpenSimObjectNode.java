/*
 *
 * OpenSimObjectNode
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
package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ViewDB;
import org.opensim.view.editors.ObjectEditDialogMaker;

/**
 *
 * @author Ayman. A node backed by an OpenSim Object 
 * (or a Set as a set is also an Object)
 */
public class OpenSimObjectNode extends OpenSimNode {
    
    private OpenSimObject opensimObject;
    /** Creates a new instance of OpenSimObjectNode */
    public OpenSimObjectNode(OpenSimObject obj) {
       this.opensimObject = obj;
        setDisplayName(obj.getName());
     }
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return getOpensimObject().getName() ;
    }

    /**
     * Action to be invoked on double clicking.
     */
    public Action getPreferredAction() {
        return getReviewAction();
    }
    /**
     * Return the list of available actions.
     * Subclasses should user super.getActions() to use this
     */
    public Action[] getActions(boolean b) {
        return (new Action[] {getReviewAction()});
    }
    /**
     * Action to review the object associated with the node
     */
    public Action getReviewAction() {
        final AbstractModel ownerModel = getModelForNode();
        //retValue = super.getActions(opensimObject);
        Action reviewAction = new CallableSystemAction(){
            /**
             * @todo handle no views situation where getCurrenWindow() returns null
             */
            public void performAction() {
                 ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(OpenSimObjectNode.this.getOpensimObject(),
                         ViewDB.getInstance().getCurrenWindow());
                 editorDialog.process();
            }

            public String getName() {
                return "Review...";
            }

            public HelpCtx getHelpCtx() {
                return null;
            }}; 
        return reviewAction;
    }
    /**
     * return the Object presented by this node
     */
    public OpenSimObject getOpensimObject() {
        return opensimObject;
    }
    
}
