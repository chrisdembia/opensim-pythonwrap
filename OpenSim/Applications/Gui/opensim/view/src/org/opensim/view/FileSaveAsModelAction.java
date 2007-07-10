package org.opensim.view;

import java.io.File;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class FileSaveAsModelAction extends CallableSystemAction {
  
   public static void saveModel(Model model, String fileName) {
      StatusDisplayer.getDefault().setStatusText("Saving model...");
      OpenSimDB.getInstance().saveModel(model, fileName);
      StatusDisplayer.getDefault().setStatusText("Saved model "+model.getName()+" to "+fileName);
   }

   public void performAction() {
      Model mdl = ViewDB.getInstance().getCurrentModel();
      if (mdl != null) {
         String fileName = FileUtils.getInstance().browseForFilenameToSave(FileUtils.OpenSimModelFileFilter, true, mdl.getInputFileName());
         if(fileName!=null) saveModel(mdl, fileName);
      }
   }
   
   public String getName() {
      return NbBundle.getMessage(FileSaveAsModelAction.class, "CTL_FileSaveAsModelAction");
   }
   
   protected void initialize() {
      super.initialize();
      // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
      putValue("noIconInMenu", Boolean.TRUE);
      setEnabled(false);
      ViewDB.getInstance().registerModelCommand(this);
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
