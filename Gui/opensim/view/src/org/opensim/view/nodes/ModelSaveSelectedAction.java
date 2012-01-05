package org.opensim.view.nodes;

import java.util.ArrayList;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.Model;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.FileSaveModelAction;

public final class ModelSaveSelectedAction extends CallableSystemAction {
   
    public void performAction() {
        Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
        // Action shouldn't be available otherwise'
        // Cycle thru selected models and cache referenes since closing a model changes selected nodes
        ArrayList<Model> modelsToSave = new ArrayList<Model>();
        for(int i=0; i<selected.length; i++){
            if (selected[i] instanceof ConcreteModelNode){
                ConcreteModelNode modelNode = (ConcreteModelNode) selected[i];
                Model mdl = modelNode.getModel();
                modelsToSave.add(mdl);
            }
        }
        for(int i=0; i<modelsToSave.size(); i++){
            // Piggyback on common code in FileCloseAction
            FileSaveModelAction.saveOrSaveAsModel(modelsToSave.get(i));
        }
    }
   
   public String getName() {
      return NbBundle.getMessage(ModelSaveSelectedAction.class, "CTL_ModelSaveSelectedAction");
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
      return selected.length>=1;
   }
}
