package org.opensim.view;

import java.awt.Color;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.windows.WindowManager;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;
import org.opensim.view.pub.ViewDB;

public final class ObjectDisplayColorAction extends CallableSystemAction {
    
    public void performAction() {
        float[] colorComponents=null;
        // Bring color chooser and apply color to selected nodes.
        JColorChooser objectColorChooser = new JColorChooser();
        Color newColor = objectColorChooser.showDialog((JFrame) WindowManager.getDefault().getMainWindow(),
                "Select new color", Color.WHITE);
        if (newColor != null){
             colorComponents = newColor.getRGBComponents(null);
        }
        else
            return;
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      for(int i=0; i < selected.length; i++){
          if (!(selected[i] instanceof OpenSimObjectNode))
              continue;
         OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            applyOperationToNode(objectNode, new double[]{colorComponents[0], colorComponents[1], colorComponents[2]});
      }
      ViewDB.getInstance().repaintAll();
   }

    private void applyOperationToNode(final OpenSimObjectNode objectNode, double[] newColorComponents) {
        OpenSimObject obj = objectNode.getOpenSimObject();
        Children ch = objectNode.getChildren();
        if (ch.getNodesCount()>0){
            // apply action recursively
            Node[] childNodes=ch.getNodes();
            for(int child=0; child < childNodes.length ; child++){
                if (!(childNodes[child] instanceof OpenSimObjectNode))
                    continue;
               OpenSimObjectNode childNode = (OpenSimObjectNode) childNodes[child];
               applyOperationToNode(childNode, newColorComponents);
            }
        }
        else
            ViewDB.getInstance().setObjectColor(obj, newColorComponents);
    }
    
    // Make it available only if selected objects have representation and belong to same model
    public boolean isEnabled() {
       // The "hide" option is enabled unless every selected node is hidden.
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        boolean isColorable=true;
        for(int i=0; i<selected.length && isColorable; i++){
            isColorable = (selected[i] instanceof OpenSimObjectNode);
            if (isColorable){
                OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
                isColorable=objectNode.getValidDisplayOptions().contains(displayOption.Colorable);
            }
        }
        return isColorable;
    }

    public String getName() {
        return "Color...";
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
