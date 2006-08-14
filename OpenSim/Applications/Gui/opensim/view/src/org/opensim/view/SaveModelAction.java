package org.opensim.view;

import java.util.Collection;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.Lookup;
import org.openide.util.LookupEvent;
import org.openide.util.LookupListener;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmModel;

public final class SaveModelAction extends CallableSystemAction {
    
    Lookup.Template tpl = new Lookup.Template (ModelWindowVTKTopComponent.class);
    Lookup.Result res = Utilities.actionsGlobalContext().lookup (tpl);
    ModelWindowVTKTopComponent active;
    
    public void performAction() {
        // TODO implement action body
        // Get current active top component
        if (active != null){
            SimmModel mdl = active.getModel();
            StatusDisplayer.getDefault().setStatusText("Saving model "+mdl.getName()+"to file.");
            mdl.print(mdl.getInputFileName());
            StatusDisplayer.getDefault().setStatusText("");
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(SaveModelAction.class, "CTL_SaveModelAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        
        res.addLookupListener (new LookupListener() {
           public void resultChanged (LookupEvent evt) {
             Collection c = ((Lookup.Result) evt.getSource()).allInstances();
             //do something with the collection of 0 or more instances - the collection has changed
             if (!c.isEmpty()) {
                active = (ModelWindowVTKTopComponent) c.iterator().next();
                 SaveModelAction.this.setEnabled(true);
             }
             else{
                 active = null;
                 SaveModelAction.this.setEnabled(false);
             }
           }
        });

    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
}
