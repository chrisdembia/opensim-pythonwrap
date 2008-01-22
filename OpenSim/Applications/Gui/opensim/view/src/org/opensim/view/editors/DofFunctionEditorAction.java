package org.opensim.view.editors;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JOptionPane;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.functionEditor.FunctionEditorTopComponent;
import org.opensim.view.nodes.DofFunctionNode;
import org.opensim.view.pub.OpenSimDB;

/**
 * Action which shows FunctionEditor component.
 */
public class DofFunctionEditorAction extends AbstractAction {

    private AbstractDof dof = null;

    public DofFunctionEditorAction(AbstractDof dof) {
        super(NbBundle.getMessage(DofFunctionEditorAction.class, "CTL_FunctionEditorAction"));
        this.dof = dof;
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(FunctionEditorTopComponent.ICON_PATH, true)));
    }
    
   public void actionPerformed(ActionEvent evt) {
      FunctionEditorTopComponent functionEditor = (FunctionEditorTopComponent) FunctionEditorTopComponent.findInstance();
      Node[] selected = ExplorerTopComponent.findInstance().getExplorerManager().getSelectedNodes();
      if (selected.length > 0 && selected[0] instanceof DofFunctionNode && dof != null) {
         DofFunctionNode funcNode = (DofFunctionNode) selected[0];
         Function currentFunction = functionEditor.getFunction();
         Model currentModel = OpenSimDB.getInstance().getCurrentModel();
         Function newFunction = Function.safeDownCast(funcNode.getOpenSimObject());
         Model newModel = dof.getJoint().getDynamicsEngine().getModel();
         if (newFunction != null && Function.getCPtr(newFunction) != Function.getCPtr(currentFunction)) {
            if (Model.getCPtr(newModel) != Model.getCPtr(currentModel)) {
               Object[] options = {"OK"};
               int answer = JOptionPane.showOptionDialog(functionEditor,
                       "You can only edit functions that are in the current model.",
                       "Function Editor",
                       JOptionPane.DEFAULT_OPTION,
                       JOptionPane.WARNING_MESSAGE,
                       null,
                       options,
                       options[0]);
            } else {
               functionEditor.addChangeListener(new DofFunctionEventListener());
               functionEditor.open(newModel, dof, newFunction, "title", "Xlabel", "Ylabel");
               functionEditor.requestActive();
            }
         }
      }
    } 
}
