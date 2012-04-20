package org.opensim.view.nodes;

import java.awt.Image;
import java.io.IOException;
import java.net.URL;
import java.util.List;
import javax.swing.ImageIcon;
import java.util.ResourceBundle;
import javax.swing.Action;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.Exceptions;
import org.openide.util.NbBundle;
import org.opensim.modeling.Marker;
import org.opensim.modeling.MarkerSet;
import org.opensim.view.markerEditor.MarkersSaveToFileAction;
import org.opensim.view.markerEditor.MarkersLoadFromFileAction;
import org.opensim.view.markerEditor.NewMarkerAction;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;

/**
 * Node class to wrap Model's collection of markers
 */
public class MarkersNode extends OpenSimObjectSetNode {
    private static ResourceBundle bundle = NbBundle.getBundle(MarkersNode.class);

    public MarkersNode(MarkerSet markerSet) {
        super(markerSet);
        setDisplayName(NbBundle.getMessage(MarkersNode.class, "CTL_Markers"));
        updateChildNodes(markerSet);
      addDisplayOption(displayOption.Isolatable);
      addDisplayOption(displayOption.Showable);
    }

    public void updateChildNodes(MarkerSet markerSet) {
        for (int markerNum=0; markerNum < markerSet.getSize(); markerNum++ ){

            Marker marker = markerSet.get(markerNum);
            Children children = getChildren();

            OneMarkerNode node = new OneMarkerNode(marker);
            Node[] arrNodes = new Node[1];
            arrNodes[0] = node;
            children.add(arrNodes);
        }
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

    public Action[] getActions(boolean b) {
        // Get actions from parent (generic object menu for review, display)
        Action[] superActions = (Action[]) super.getActions(b);        
        // Arrays are fixed size, onvert to a List
        List<Action> actions = java.util.Arrays.asList(superActions);
        // Create new Array of proper size
        Action[] retActions = new Action[actions.size()+3];
        actions.toArray(retActions);
        // append new command to the end of the list of actions
        retActions[actions.size()] = new NewMarkerAction();
        retActions[actions.size()+1] = new MarkersSaveToFileAction();
        retActions[actions.size()+2] = new MarkersLoadFromFileAction();
        return retActions;
    }

} // class MarkersNode
