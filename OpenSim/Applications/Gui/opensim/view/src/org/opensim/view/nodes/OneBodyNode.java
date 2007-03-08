package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import java.util.ResourceBundle;
import javax.swing.ImageIcon;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractWrapObject;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.WrapObjectSet;

/** Node class to wrap AbstractBody objects */
public class OneBodyNode extends OpenSimObjectNode{
   private static ResourceBundle bundle = NbBundle.getBundle(OneBodyNode.class);
   public OneBodyNode(OpenSimObject b) {
      super(b);
      setShortDescription(bundle.getString("HINT_BodyNode"));
      // Create children for wrap objects associated with body
      AbstractBody bdy = (AbstractBody) b;
      WrapObjectSet wrapObjects = bdy.getWrapObjectSet();
      Children children = getChildren();
      
      for (int index=0; index < wrapObjects.getSize(); index++ ){
         
         AbstractWrapObject wrapObject = wrapObjects.get(index);
         OneWrapObjectNode node = new OneWrapObjectNode(wrapObject);
         Node[] arrNodes = new Node[1];
         arrNodes[0] = node;
         children.add(arrNodes);
         
      }
      
   }

    public Node cloneNode() {
        return new OneBodyNode(getOpensimObject());
    }
    /**
     * Icon for the body node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/body.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Body").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }

}