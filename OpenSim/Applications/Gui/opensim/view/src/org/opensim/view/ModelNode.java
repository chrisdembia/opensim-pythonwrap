/*
 * ModelNode.java
 *
 * Created on May 5, 2006, 12:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;


import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.util.Stack;
import javax.swing.AbstractAction;
import javax.swing.Action;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.SystemAction;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;

/**
 *
 * @author ken
 */
public class ModelNode<T> extends AbstractNode {
    
    public T _object = null;
    /** Creates a new instance of ModelNode */
    public ModelNode(T obj) {
        super(new Children.Array());
        _object = obj;
    }
    
    /** Root node (has all open models as its children). */
    public static class RootNode extends ModelNode<String> {
        public RootNode() {
            super("Models");
            setName("Models");
        }
    }
    
} // class ModelNode
