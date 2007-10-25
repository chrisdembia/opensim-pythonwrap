package org.opensim.view;

import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.pub.ViewDB;

public final class FileSaveModelAction extends CallableSystemAction {
   
    public static boolean saveOrSaveAsModel(Model model) {
      if(model==null) return false;
      if(!model.getInputFileName().equals("")) {
         FileSaveAsModelAction.saveModel(model, model.getInputFileName());
         return true;
      }
      else return FileSaveAsModelAction.saveAsModel(model);
    }

    public void performAction() {
      Model model = ViewDB.getInstance().getCurrentModel();
      if (model != null) saveOrSaveAsModel(model);
    }
    
    public String getName() {
        return NbBundle.getMessage(FileSaveModelAction.class, "CTL_SaveModelAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
        //setEnabled(false);
        //ViewDB.getInstance().registerModelCommand(this);
        
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }

   public boolean isEnabled() {
      return ViewDB.getInstance().getCurrentModel()!=null;
   }
    
}
