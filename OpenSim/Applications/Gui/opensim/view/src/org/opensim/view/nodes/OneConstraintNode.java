package org.opensim.view.nodes;

import java.awt.Image;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.net.URL;
import java.util.Enumeration;
import java.util.ResourceBundle;
import javax.swing.ImageIcon;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.nodes.PropertySupport;
import org.openide.nodes.Sheet;
import org.openide.util.NbBundle;
import org.opensim.modeling.OpenSimObject;

/** Node class to wrap AbstractMarker objects */
public class OneConstraintNode extends OpenSimObjectNode{
   private static ResourceBundle bundle = NbBundle.getBundle(OneConstraintNode.class);
   public OneConstraintNode(OpenSimObject b) {
      super(b);
      setShortDescription(bundle.getString("HINT_ConstraintNode"));
      setChildren(Children.LEAF);      
      //addDisplayOption(displayOption.Isolatable);
      //ddDisplayOption(displayOption.Showable);
   }

    public Node cloneNode() {
        return new OneConstraintNode(getOpenSimObject());
    }
    /**
     * Icon for the constraint node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/markerNode.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Constraint").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }

    @Override
    public Sheet createSheet() {
        Sheet retValue;
        
        retValue = super.createSheet();
        /*
        OpenSimObject obj = getOpenSimObject();
        org.opensim.modeling.PropertySet ps= obj.getPropertySet();
        try {
            org.opensim.modeling.Property isDisabledProp = ps.get("isDisabled");
            PropertySupport.Reflection nextNodeProp;
            nextNodeProp = new PropertySupport.Reflection(isDisabledProp, OpenSimNode.mapPropertyEnumToClass.get(isDisabledProp.getType()), mapPropertyEnumToGetters.get(isDisabledProp.getType()), 
                    "setValue");
            nextNodeProp.setName(isDisabledProp.getName());
            getSet().put(nextNodeProp);
        } catch (IOException ex) {
            ex.printStackTrace();
        } catch (NoSuchMethodException ex) {
            ex.printStackTrace();
        }
        */
        return retValue;
    }
}
