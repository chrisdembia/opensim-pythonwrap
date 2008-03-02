/*
 * ExcitationTreeModel.java
 *
 * Created on February 4, 2008, 2:32 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;

/**
 *
 * @author Ayman
 */
public class ExcitationTreeModel extends DefaultTreeModel{

    /** Creates a new instance of ExcitationTreeModel */
    public ExcitationTreeModel(DefaultMutableTreeNode root) {
        super(root);    // implicit but just in case
    }
    public void appendChild(MutableTreeNode newChild,
                               MutableTreeNode parent) {
        insertNodeInto(newChild, parent, parent.getChildCount());
    }
}
