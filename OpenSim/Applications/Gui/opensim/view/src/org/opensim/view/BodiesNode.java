package org.opensim.view;

import java.beans.PropertyChangeListener;
import java.util.Stack;
import javax.swing.Action;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;


/** Node class to wrap SimmModel's collection of SimmBodies */
public class BodiesNode extends ModelNode<SimmModel> {
    boolean topological=false;

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
    public Action[] getActions(boolean b) {
        Action[] retValue;

        retValue = super.getActions(b);

        return retValue;
    }
} // class BodiesNode
