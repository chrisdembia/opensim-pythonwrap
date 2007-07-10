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
         String fileName = null;
         for (;;) {
            fileName = FileUtils.getInstance().browseForFilename(".osim", "OpenSim model", false, true);
            if(fileName==null) break;
            if((new File(fileName)).exists() && !mdl.getInputFileName().equals(fileName)) {
               // File exists and is a different model... Prompt for overwrite.  If no overwrite, repeat loop (open file dialog again)
               Object answer=DialogDisplayer.getDefault().notify(
                  new NotifyDescriptor.Confirmation("Replace existing model "+fileName+"?","Replace Model",NotifyDescriptor.YES_NO_OPTION));
               if(answer==NotifyDescriptor.YES_OPTION) break;
            } else break;
         }
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
