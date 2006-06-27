package org.opensim.view;

import org.opensim.modeling.SimmBody;


/** Node class to wrap SimmBody objects */
public class BodyNode extends ModelNode<SimmBody> {
    public BodyNode(SimmBody b) {
        super(b);
        setName(b.getName());
    }
    
    public String getHtmlDisplayName() {
        return "<b>Body " + _object.getName() + "</b>" ;
}

}