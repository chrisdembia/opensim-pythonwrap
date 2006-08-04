package org.opensim.view;

import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Collection;
import javax.swing.JButton;
import javax.swing.JPopupMenu;
import org.openide.util.HelpCtx;
import org.openide.util.Lookup;
import org.openide.util.LookupEvent;
import org.openide.util.LookupListener;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.base.CamerasMenu;
import org.opensim.view.base.OpenSimBaseCanvas;

public final class CameraAction extends CallableSystemAction 
        implements LookupListener{
    
    Lookup.Template tpl = new Lookup.Template (ModelWindowVTKTopComponent.class);
    private Lookup.Result result = Utilities.actionsGlobalContext().lookup(tpl);
    ModelWindowVTKTopComponent   tc;
    
    public CameraAction()
    {
        result.addLookupListener (this);

    }
    public void performAction() {
        // TODO implement action body
    }
    
    public String getName() {
        return NbBundle.getMessage(CameraAction.class, "CTL_CameraAction");
    }
    
    protected String iconResource() {
        return "org/opensim/view/camera.gif";
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }

    public Component getToolbarPresenter() {
        
        final Component toolbarButton= new JButton("Camera >");
        toolbarButton.addMouseListener(new MouseAdapter(){  
              public void mousePressed(MouseEvent e) { showSettingsPopup(e); }
               private void showSettingsPopup(MouseEvent e) {
                   if (tc==null)
                       return;
                  JPopupMenu settingsMenu = new JPopupMenu();
                  settingsMenu.add(new CamerasMenu(tc.getCanvas()));
                  settingsMenu.show(toolbarButton, e.getX(), e.getY());
              }
        });
         return toolbarButton;
    }

    public void resultChanged(LookupEvent lookupEvent) {
        Lookup.Result r = (Lookup.Result) lookupEvent.getSource();
        Collection c = r.allInstances();
        if (!c.isEmpty()) {
            tc = (ModelWindowVTKTopComponent) c.iterator().next();
        }
    }
    
}
