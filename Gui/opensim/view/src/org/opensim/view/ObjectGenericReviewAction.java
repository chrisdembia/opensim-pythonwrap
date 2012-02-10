/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.opensim.view;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.editors.ObjectEditDialogMaker;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.nodes.OneBodyNode;
import org.opensim.view.nodes.OneJointNode;
import org.opensim.view.pub.ViewDB;
import LSJava.LSPropertyEditors.LSPropertyEditorRigidBody;
import LSJava.LSPropertyEditors.LSPropertyEditorJoint;


public final class ObjectGenericReviewAction  extends CallableSystemAction {
   
   public boolean isEnabled() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      return selected.length==1;
   }
   
   public void performAction() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if( selected.length == 1 ) {
         OpenSimObjectNode osimObjectNode = (OpenSimObjectNode) selected[0];
         ModelWindowVTKTopComponent ownerWindow = ViewDB.getInstance().getCurrentModelWindow();
         
         // If osimObjectNode is a rigid body, open the easy-to-use rigid body property editor (also provides the older table version). 
         if( osimObjectNode instanceof OneBodyNode )
           LSJava.LSPropertyEditors.LSPropertyEditorRigidBody.NewLSPropertyEditorRigidBody( (OneBodyNode)osimObjectNode, ownerWindow );
         
         // If osimObjectNode is a joint (connection), open the easy-to-use joint property editor (also provides the older table version). 
         else if( osimObjectNode instanceof OneJointNode )
           new LSJava.LSPropertyEditors.LSPropertyEditorJoint( (OneJointNode)osimObjectNode, ownerWindow );

         // Otherwise create older editor window to edit the properties (this is opened from user's selection of Navigator window).
         else {
            boolean allowEdit = false;
            ObjectEditDialogMaker editorDialog = new ObjectEditDialogMaker( osimObjectNode.getOpenSimObject(), ownerWindow, allowEdit, "OK" ); 
            editorDialog.process();
         }

      } 
      else { // Should never happen
         DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message("Review of multiple objects is not supported."));
      }
   }
   
   public String getName() {
      return "Property Viewer";
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
