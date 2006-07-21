package org.opensim.view.nodes;

import java.util.ResourceBundle;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.SimmBody;

/** Node class to wrap SimmBody objects */
public class BodyNode extends ModelNode<SimmBody> {
    private static ResourceBundle bundle = NbBundle.getBundle(BodyNode.class);
    public BodyNode(SimmBody b) {
        super(b);
        setName(b.getName());
        setShortDescription(bundle.getString("HINT_BodyNode"));
   }
    
    public String getHtmlDisplayName() {
        return "<b>" + _object.getName() + "</b>" ;
    }

    public Node cloneNode() {
        return new BodyNode(_object);
    }
}