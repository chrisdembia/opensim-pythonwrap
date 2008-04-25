package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import javax.swing.ImageIcon;
import java.util.ResourceBundle;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.MarkerSet;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;

/**
 * Node class to wrap Model's collection of markers
 */
public class MarkersNode extends OpenSimObjectSetNode {
    boolean topological=false;
    private static ResourceBundle bundle = NbBundle.getBundle(MarkersNode.class);

    public MarkersNode(MarkerSet markerSet) {
        super(markerSet);

        for (int markerNum=0; markerNum < markerSet.getSize(); markerNum++ ){

            AbstractMarker marker = markerSet.get(markerNum);
            Children children = getChildren();

            if (topological){
            }
            else {
                OneMarkerNode node = new OneMarkerNode(marker);
                Node[] arrNodes = new Node[1];
                arrNodes[0] = node;
                children.add(arrNodes);
            }
        }
      addDisplayOption(displayOption.Isolatable);
      addDisplayOption(displayOption.Showable);
      addDisplayOption(displayOption.Colorable);
    }

      public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/markersNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
   public Image getOpenedIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/markersNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return "Markers";
    }
    
} // class MarkersNode
