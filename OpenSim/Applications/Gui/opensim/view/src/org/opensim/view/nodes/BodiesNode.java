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
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;

/** Node class to wrap SimmModel's collection of SimmBodies */
public class BodiesNode extends OpenSimNode {
    boolean topological=false;
    SimmModel   m;
    private static ResourceBundle bundle = NbBundle.getBundle(BodiesNode.class);

    public BodiesNode(SimmModel m) {
        super();
        setDisplayName("Bodies");
        this.m = m;
        
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
        //getChildren().add(new MyChildren(m).getNodes());
    }
    public Node cloneNode() {
        return new BodiesNode(m);
    }
    
    public Action[] getActions(boolean context) {
        Action[] result = new Action[] {
                    SystemAction.get(NewAction.class),
                    null,
                    SystemAction.get(ToolsAction.class),
                    SystemAction.get(PropertiesAction.class),
        };
        return result;
    }
    
   public NewType[] getNewTypes() {
        return new NewType[] { new NewType() {
            public String getName() {
                return bundle.getString("LBL_NewBody");
            }
            public HelpCtx getHelpCtx() {
                return null;
            }
            public void create() throws IOException {
                String title = bundle.getString("LBL_Newbody_dialog");
                String msg = bundle.getString("MSG_Newbody_dialog_key");
                NotifyDescriptor.InputLine desc = new NotifyDescriptor.InputLine(msg, title);
                DialogDisplayer.getDefault().notify(desc);
                String key = desc.getInputText();
                if ("".equals(key)) return;
              }
        } };
    }

} // class BodiesNode
