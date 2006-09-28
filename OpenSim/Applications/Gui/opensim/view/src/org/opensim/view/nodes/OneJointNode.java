/*
 *
 * OneMuscleNode
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

import java.awt.Image;
import java.net.URL;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmModel;
import org.opensim.view.ViewDB;
import org.opensim.view.editors.ObjectEditDialogMaker;

/**
 *
 * @author Ayman Habib
 */
public class OneJointNode extends OpenSimNode{
    
    /** Creates a new instance of OneMuscleNode */
    public OneJointNode(String key) {
        setDisplayName(key);
    }
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("icons/joint.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Joint").getImage();
        } else {
            return null;
        }
    }
   public Image getOpenedIcon(int i) {
        return getIcon(i);
    }
   /*
   public Action[] getActions(boolean b) {
        Action[] retValue;
        
        final SimmModel ownerModel = getModelForNode();
        //retValue = super.getActions(b);
        Action reviewAction = new CallableSystemAction(){
            public void performAction() {
                 ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(BodyNode.this.b, 
                                                    ViewDB.getInstance().getVTKTopComponentForModel(ownerModel));
                 editorDialog.process();
            }

            public String getName() {
                return "Review";
            }

            public HelpCtx getHelpCtx() {
                return null;
            }}; 
        return (new Action[] {reviewAction});
         
        return null;
    }
    */
}
