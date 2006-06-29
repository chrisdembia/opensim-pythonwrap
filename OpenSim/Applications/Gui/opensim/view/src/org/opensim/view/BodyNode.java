package org.opensim.view;

import javax.swing.Action;
import org.opensim.modeling.SimmBody;


/** Node class to wrap SimmBody objects */
public class BodyNode extends ModelNode<SimmBody> {
    public BodyNode(SimmBody b) {
        super(b);
        setName(b.getName());
    }
    
    public String getHtmlDisplayName() {
        return "<b>" + _object.getName() + "</b>" ;
    }

}