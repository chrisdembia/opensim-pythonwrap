/*
 * ModelNode.java
 *
 * Created on May 5, 2006, 12:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;


import java.util.Stack;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
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
    boolean topological=false;  // Show topology tree for dynamic model.
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
    
    
    /** Node class to wrap SimmModel objects */
    public static class ConcreteModelNode extends ModelNode<SimmModel> {
        public ConcreteModelNode(SimmModel m) {
            super(m);
            setName(m.getName());
            getChildren().add(new Node[] { new BodiesNode(m) });
        }
    }
    
    /** Node class to wrap SimmModel's collection of SimmBodies */
    public static class BodiesNode extends ModelNode<SimmModel> {
        public BodiesNode(SimmModel m) {
            super(m);
            setName("Bodies");
            
            Stack<BodyNode> stack = new Stack<BodyNode>();
            
            SimmModelIterator i = new SimmModelIterator(m);
            
            while (i.getNextBody() != null) {
                
                SimmBody body = i.getCurrentBody();
                 Children children = getChildren();
               
                if (topological){
                    while (stack.size() > i.getNumAncestors())
                        stack.pop();
                
                    if (stack.size() > 0)
                        children = stack.peek().getChildren();

                    stack.push(new BodyNode(body));
                
                    children.add(new Node[] { stack.peek() });
                }
                else {
                     BodyNode node = new BodyNode(body);
                     Node[] arrNodes = new Node[1];
                     arrNodes[0] = node;
                     children.add(arrNodes);
                }
            }
        }
        
    } // class BodiesNode
    
    /** Node class to wrap SimmBody objects */
    public static class BodyNode extends ModelNode<SimmBody> {
        public BodyNode(SimmBody b) {
            super(b);
            setName(b.getName());
        }
    }
} // class ModelNode
