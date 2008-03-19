/*
 * MoveExcitationHandler.java
 *
 * Created on March 11, 2008, 2:52 PM
 *
 * Copyright (c)  2005-2006, Stanford University, Ayman Habib
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

package org.opensim.view.excitationEditor;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreePath;

/**
 *
 * @author Ayman
 */
public class MoveExcitationHandler extends NodeMoveTransferHandler{
    ExcitationsGridJPanel topPanel;
    /** Creates a new instance of MoveExcitationHandler */
    public MoveExcitationHandler(ExcitationsGridJPanel topPanel) {
        this.topPanel = topPanel;
    }

    public void handlePathMove(TreePath currentPath, DefaultTreeModel model, Transferable data) {
        DefaultMutableTreeNode TargetNode = (DefaultMutableTreeNode) currentPath.getLastPathComponent();
        // Type must be correct
        Object targetObject = TargetNode.getUserObject();
        if (!(targetObject instanceof ExcitationColumnJPanel))
            return;
        ExcitationColumnJPanel targetPanel = (ExcitationColumnJPanel)targetObject;
        TreePath[] movedPaths;
        try {
            movedPaths = (TreePath[]) data.getTransferData(DataFlavor.stringFlavor);
            for(int i = 0; i < movedPaths.length; i++) {
                DefaultMutableTreeNode moveNode = (DefaultMutableTreeNode) movedPaths[i].getLastPathComponent();
                Object object2Move = moveNode.getUserObject();
                if (object2Move instanceof ExcitationObject){
                    // get Parent and remove Panel
                   ExcitationColumnJPanel sourcePanel = (ExcitationColumnJPanel)(((DefaultMutableTreeNode) moveNode.getParent()).getUserObject());
                   ExcitationObject eObject = (ExcitationObject)object2Move;
                   sourcePanel.remove(eObject.getPlotPanel());
                   targetPanel.add(eObject.getPlotPanel());
                }
            }
            topPanel.validate();
       } catch (IOException ex) {
            ex.printStackTrace();
        } catch (UnsupportedFlavorException ex) {
            ex.printStackTrace();
        }
    }

    public void handlePathRearrange(TreePath currentPath, DefaultTreeModel model, Transferable data) {
        DefaultMutableTreeNode TargetNode = (DefaultMutableTreeNode) currentPath.getLastPathComponent();
        // Type must be correct
        Object targetObject = TargetNode.getUserObject();
        if (!(targetObject instanceof ExcitationObject))
            return;
        ExcitationColumnJPanel parentPanel = (ExcitationColumnJPanel)((DefaultMutableTreeNode)TargetNode.getParent()).getUserObject();
        TreePath[] movedPaths;
        try {
            movedPaths = (TreePath[]) data.getTransferData(DataFlavor.stringFlavor);
            for(int i = 0; i < movedPaths.length; i++) {
                DefaultMutableTreeNode moveNode = (DefaultMutableTreeNode) movedPaths[i].getLastPathComponent();
                int ndx=TargetNode.getParent().getIndex(moveNode);
                Object object2Move = moveNode.getUserObject();
                if (object2Move instanceof ExcitationObject){
                    // get Parent and remove Panel
                   ExcitationObject eObject=(ExcitationObject) object2Move;
                   parentPanel.remove(eObject.getPlotPanel());
                   parentPanel.add(eObject.getPlotPanel(), ndx+1);
                   System.out.println("Moving panel to new position "+ndx+1);
                }
            }
            topPanel.validate();
       } catch (IOException ex) {
            ex.printStackTrace();
        } catch (UnsupportedFlavorException ex) {
            ex.printStackTrace();
        }
    }

}
