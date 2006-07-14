/*
 * ModelNode.java
 *
 * Created on May 5, 2006, 12:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.nodes;


import javax.swing.Action;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.opensim.view.*;

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
