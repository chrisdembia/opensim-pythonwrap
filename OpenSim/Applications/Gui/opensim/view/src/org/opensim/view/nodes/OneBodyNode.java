package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import java.util.ResourceBundle;
import javax.swing.ImageIcon;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.OpenSimObject;

/** Node class to wrap AbstractBody objects */
public class OneBodyNode extends OpenSimObjectNode{
    private static ResourceBundle bundle = NbBundle.getBundle(OneBodyNode.class);
    public OneBodyNode(OpenSimObject b) {
        super(b);
        setShortDescription(bundle.getString("HINT_BodyNode"));
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