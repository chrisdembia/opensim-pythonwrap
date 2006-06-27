package org.opensim.view;

import java.util.Stack;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;


/** Node class to wrap SimmModel's collection of SimmBodies */
public class BodiesNode extends ModelNode<SimmModel> {
           
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