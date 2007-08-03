package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.Presenter;
import org.opensim.view.nodes.OpenSimObjectNode;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;

public final class ObjectDisplayMenuAction extends CallableSystemAction implements Presenter.Popup {
    
    public boolean isEnabled() {
        return true;
    }

    public void performAction() {
    }
    
    public String getName() {
        return "Display";
    }
        
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }

   public void actionPerformed(ActionEvent e) {
   }

   public JMenuItem getPopupPresenter() {
      JMenu displayMenu = new JMenu("Display");
      boolean showShadingOptions=false;
      // Check that selected objects support the operations
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // If any selected object is hidden (or any selected group is mixed), return false.
        for(int i=0; i < selected.length; i++){
           if (! (selected[i] instanceof OpenSimObjectNode))
              continue;
            OpenSimObjectNode objectNode = (OpenSimObjectNode) selected[i];
            if (objectNode.getValidDisplayOptions().contains(displayOption.Colorable))
               showShadingOptions=true;
        }

      try {
      
         displayMenu.add(new JMenuItem(
                 (ObjectDisplayShowAction) ObjectDisplayShowAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayShowAction"), true)));
         displayMenu.add(new JMenuItem(
                 (ObjectDisplayShowOnlyAction) ObjectDisplayShowOnlyAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayShowOnlyAction"), true)));
         displayMenu.add(new JMenuItem(
                 (ObjectDisplayHideAction) ObjectDisplayHideAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayHideAction"), true)));
         if (showShadingOptions){
            displayMenu.addSeparator();
            displayMenu.add(new JMenuItem(
                    (ObjectDisplaySurfaceFlatAction) ObjectDisplaySurfaceFlatAction.findObject(
                    Class.forName("org.opensim.view.ObjectDisplaySurfaceFlatAction"), true)));
            displayMenu.add(new JMenuItem(
                    (ObjectDisplaySurfaceGouraudAction) ObjectDisplaySurfaceGouraudAction.findObject(
                    Class.forName("org.opensim.view.ObjectDisplaySurfaceGouraudAction"), true)));
            displayMenu.add(new JMenuItem(
                    (ObjectDisplayWireframeAction) ObjectDisplayWireframeAction.findObject(
                    Class.forName("org.opensim.view.ObjectDisplayWireframeAction"), true)));
         }
       } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }     
         
      return displayMenu;
   }
    
}
