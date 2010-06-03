package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.Body;
import org.opensim.modeling.WrapObject;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.WrapObjectSet;
import org.opensim.view.BodyToggleFrameAction;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;

/** Node class to wrap Body objects */
public class OneBodyNode extends OpenSimObjectNode{
   private static ResourceBundle bundle = NbBundle.getBundle(OneBodyNode.class);
   public OneBodyNode(OpenSimObject b) {
      super(b);
      setShortDescription(bundle.getString("HINT_BodyNode"));
      // Create children for wrap objects associated with body
      Body bdy = (Body) b;
      WrapObjectSet wrapObjects = bdy.getWrapObjectSet();
      Children children = getChildren();
      
      for (int index=0; index < wrapObjects.getSize(); index++ ){
         
         WrapObject wrapObject = wrapObjects.get(index);
         OneWrapObjectNode node = new OneWrapObjectNode(wrapObject);
         Node[] arrNodes = new Node[1];
         arrNodes[0] = node;
         children.add(arrNodes);
         
      }

      if(children.getNodesCount()==0) setChildren(Children.LEAF);      
      addDisplayOption(displayOption.Colorable);
      addDisplayOption(displayOption.Isolatable);
      addDisplayOption(displayOption.Showable);
   }

    public Node cloneNode() {
        return new OneBodyNode(getOpenSimObject());
    }
    /**
     * Icon for the body node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/bodyNode.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Body").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }

    public Action[] getActions(boolean b) {
        Action[] superActions = (Action[]) super.getActions(b);        
        // Arrays are fixed size, onvert to a List
        List<Action> actions = java.util.Arrays.asList(superActions);
        // Create new Array of proper size
        Action[] retActions = new Action[actions.size()+1];
        actions.toArray(retActions);
        try {
            // append new command to the end of the list of actions
            retActions[actions.size()] = (BodyToggleFrameAction) BodyToggleFrameAction.findObject(
                     (Class)Class.forName("org.opensim.view.BodyToggleFrameAction"), true);
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        return retActions;
    }

}
