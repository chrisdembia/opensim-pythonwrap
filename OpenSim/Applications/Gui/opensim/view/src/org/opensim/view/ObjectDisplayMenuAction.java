package org.opensim.view;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.Presenter;

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
       displayMenu.add(new JMenuItem(    new ObjectDisplayHideAction()));
       displayMenu.add(new JMenuItem(    new ObjectDisplayShowAction()));
       displayMenu.add(new JMenuItem(    new ObjectDisplayWireframeAction()));
       displayMenu.add(new JMenuItem(    new ObjectDisplaySurfaceFlatAction()));
       displayMenu.add(new JMenuItem(    new ObjectDisplaySurfaceGouraudAction()));
       displayMenu.add(new JMenuItem(    new ObjectDisplaySurfaceAction()));
      
      return displayMenu;
   }
    
}
