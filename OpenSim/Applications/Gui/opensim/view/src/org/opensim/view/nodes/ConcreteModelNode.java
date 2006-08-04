package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.cookies.SaveCookie;
import org.openide.nodes.Node;
import org.opensim.modeling.SimmModel;
import org.opensim.view.*;



/** Node class to wrap SimmModel objects */
public class ConcreteModelNode extends OpenSimNode {
    public ConcreteModelNode(SimmModel m) {
        super();
        setDisplayName(m.getName());
        getChildren().add(new Node[]  {new BodiesNode(m)});
        getChildren().add(new Node[] {new MusclesNode(m)});
   }
    public Action[] getActions(boolean popup) {
        return new Action[]  {(Action)OpenOsimModelAction.findObject(OpenOsimModelAction.class)};
    }

}