package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.Presenter;
import org.opensim.view.nodes.IsolateCurrentModelAction;

public final class ModelDisplayMenuAction extends CallableSystemAction implements Presenter.Popup {
    
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
      try {
      
         displayMenu.add(new JMenuItem(
                 (ObjectDisplayShowAction) ObjectDisplayShowAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayShowAction"), true)));
         displayMenu.add(new JMenuItem(
                (IsolateCurrentModelAction) IsolateCurrentModelAction.findObject(
                        Class.forName("org.opensim.view.nodes.IsolateCurrentModelAction"), true)));
         displayMenu.add(new JMenuItem(
                 (ObjectDisplayHideAction) ObjectDisplayHideAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayHideAction"), true)));
         displayMenu.add(new JMenuItem(
                (ModelDisplayEditAction) ModelDisplayEditAction.findObject(
                        Class.forName("org.opensim.view.ModelDisplayEditAction"), true)));       
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }     
         
      return displayMenu;
   }
    
}
