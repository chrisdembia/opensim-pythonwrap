package org.opensim.motionviewer;

import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.utils.FileUtils;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

public final class FileLoadMotionAction extends CallableSystemAction {
   
   public void performAction() {
      // TODO implement action body
      // Browse for a SIMM motion file
        String fileName = FileUtils.getInstance().browseForFilename(".mot,.sto", "Motion or storage file");
        if (fileName != null){
           // Load file and associate it to a model
           // File is loaded into a SimmMotionData object first then associated with a particular
           // model. This's done in OpenSimDB so that created SimmMotionData is not garbage collected early.
           // also because OpenSimDB has access to all models and as such can decide if it makes sense 
           // to associate the loaded motion with a prticular model.
           MotionsDB.getInstance().loadMotionFile(fileName);
        }
        
   }
   
   public String getName() {
      return NbBundle.getMessage(FileLoadMotionAction.class, "CTL_FileLoadMotionAction");
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
       return OpenSimDB.getInstance().getCurrentModel()!=null;
   }
   
   
}
