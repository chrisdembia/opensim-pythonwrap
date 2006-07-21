package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.nodes.Node;
import org.opensim.modeling.SimmModel;
import org.opensim.view.*;



/** Node class to wrap SimmModel objects */
public class ConcreteModelNode extends ModelNode<SimmModel> {
    public ConcreteModelNode(SimmModel m) {
        super(m);
        setName(m.getName());
        getChildren().add(new Node[]  {new BodiesNode(m)});
    }
    public Action[] getActions(boolean popup) {
        return new Action[]  {(Action)OpenOsimModelAction.findObject(OpenOsimModelAction.class)};
    }

}