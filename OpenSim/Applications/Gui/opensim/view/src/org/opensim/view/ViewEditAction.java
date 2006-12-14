package org.opensim.view;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.TheApp;

/**
 * A Class representing the action of renaming a graphics window.
 *
 * @todo this class should be final per netBeans 
 */

public class ViewEditAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                ViewEditJDialog dlg = 
                new ViewEditJDialog(TheApp.getAppFrame(), true, ViewDB.getInstance().getCurrenWindow());
                dlg.setLocationRelativeTo(ExplorerTopComponent.getDefault());
                dlg.setVisible(true);
            }
        });
        /*
        DialogDescriptor viewEditDlg = new DialogDescriptor(new RenameViewPanel(ViewDB.getInstance().getCurrenWindow()), "Rename View");
        viewEditDlg.addPropertyChangeListener(new PropertyChangeListener(){
            public void propertyChange(PropertyChangeEvent evt) {
                Object obj = evt.getSource();
                String propName = evt.getPropertyName();
                if (propName.equalsIgnoreCase("Value")){
                    int acceptReject = ((Integer)evt.getNewValue()).intValue();
                    if (acceptReject==1){   //OK
                        ViewDB.getInstance().getCurrenWindow().setTabDisplayName("OK");
                        ViewDB.getInstance().getCurrenWindow().setDisplayName("OK");
                    }
                    else {  //Cancel
                        ViewDB.getInstance().getCurrenWindow().setTabDisplayName("Cancel");
                        ViewDB.getInstance().getCurrenWindow().setDisplayName("Cancel");                        
                    }
                }
            }});
        DialogDisplayer.getDefault().createDialog(viewEditDlg).setVisible(true);
        */
    }
    
    public String getName() {
        return NbBundle.getMessage(ViewEditAction.class, "CTL_EditViewAction");
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
