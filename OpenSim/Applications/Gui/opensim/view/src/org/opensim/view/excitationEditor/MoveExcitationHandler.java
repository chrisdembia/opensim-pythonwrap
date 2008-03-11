/*
 * MoveExcitationHandler.java
 *
 * Created on March 11, 2008, 2:52 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
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
    }

}
