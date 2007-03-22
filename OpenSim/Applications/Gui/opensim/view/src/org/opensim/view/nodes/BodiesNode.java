package org.opensim.view.nodes;

import java.io.IOException;
import java.util.ResourceBundle;
import java.util.Stack;
import javax.swing.Action;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.actions.NewAction;
import org.openide.actions.PropertiesAction;
import org.openide.actions.ToolsAction;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.SystemAction;
import org.openide.util.datatransfer.NewType;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.Model;

/**
 * Node class to wrap Model's collection of SimmBodies
 */
public class BodiesNode extends OpenSimObjectNode {
    boolean topological=false;
    private static ResourceBundle bundle = NbBundle.getBundle(BodiesNode.class);

    public BodiesNode(BodySet bodySet) {
        super(bodySet);
         
        //Stack<OneBodyNode> stack = new Stack<OneBodyNode>();

        for (int bodyNum=0; bodyNum < bodySet.getSize(); bodyNum++ ){

            AbstractBody body = bodySet.get(bodyNum);
            Children children = getChildren();

            if (topological){
                /*while (stack.size() > i.getNumAncestors())
                    stack.pop();

                if (stack.size() > 0)
                    children = stack.peek().getChildren();

                stack.push(new BodyNode(body));

                children.add(new Node[] { stack.peek() });*/
            }
            else {
                OneBodyNode node = new OneBodyNode(body);
                Node[] arrNodes = new Node[1];
                arrNodes[0] = node;
                children.add(arrNodes);
            }
        }
        //getChildren().add(new MyChildren(m).getNodes());
    }
    
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return "Bodies";
    }
    
    public Node cloneNode() {
        return new BodiesNode((BodySet)getOpensimObject());
    }
    /*
    public Action[] getActions(boolean context) {
        Action[] result = new Action[] {
                    //SystemAction.get(NewAction.class),
                    null,
                    //SystemAction.get(ToolsAction.class),
                    //SystemAction.get(PropertiesAction.class),
        };
        return result;
    }
    */
} // class BodiesNode
