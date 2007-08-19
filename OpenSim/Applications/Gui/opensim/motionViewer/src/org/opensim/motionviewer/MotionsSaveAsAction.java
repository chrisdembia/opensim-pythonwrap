package org.opensim.motionviewer;

import org.openide.awt.StatusDisplayer;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction; 
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.utils.FileUtils;
import org.opensim.view.ExplorerTopComponent;

public final class MotionsSaveAsAction extends CallableSystemAction {
  
   public static void saveMotion(Model model, Storage motion, String fileName) {
      StatusDisplayer.getDefault().setStatusText("Saving motion...");
      // Needs to be converted to degrees, therefore we need to make a copy of it first
      Storage motionCopy = new Storage(motion);
      model.getDynamicsEngine().convertRadiansToDegrees(motionCopy);
      String extension = FileUtils.getExtension(fileName);
      if (extension==null)
         fileName += ".sto";
      if(FileUtils.getExtension(fileName).toLowerCase().equals("mot"))
         motionCopy.setWriteSIMMHeader(true); // Write SIMM header for SIMM compatibility
      // TODO: set precision?
      motionCopy.print(fileName);
      MotionsDB.getInstance().setMotionModified(motion,false); 
      StatusDisplayer.getDefault().setStatusText("Saved motion "+motion.getName()+" to "+fileName);
   }

   public void performAction() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if(selected.length==1 && (selected[0] instanceof OneMotionNode)) {
         OneMotionNode node = (OneMotionNode)selected[0];
         String fileName = FileUtils.getInstance().browseForFilenameToSave(FileUtils.MotionFileFilter, true, "");
         if(fileName!=null) saveMotion(node.getModel(), node.getMotion(), fileName);
      }
   }

   public String getName() {
      return NbBundle.getMessage(MotionsSaveAsAction.class, "CTL_MotionsSaveAsAction");
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
   
   public boolean isEnabled() {
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      return (selected.length==1 && (selected[0] instanceof OneMotionNode));
   }
}
