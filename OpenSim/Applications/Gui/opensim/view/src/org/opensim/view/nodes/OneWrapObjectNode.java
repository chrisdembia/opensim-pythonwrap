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

/** Node class to wrap AbstractWrapObject objects */
public class OneWrapObjectNode extends OpenSimObjectNode{
   private static ResourceBundle bundle = NbBundle.getBundle(OneBodyNode.class);
   public OneWrapObjectNode(OpenSimObject b) {
      super(b);
      setShortDescription(bundle.getString("HINT_WrapObjectNode"));
      
   }

    public Node cloneNode() {
        return new OneWrapObjectNode(getOpensimObject());
    }
    /**
     * Icon for the body node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/wrap.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Wrap Object").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }

}