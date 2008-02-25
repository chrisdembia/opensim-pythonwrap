package org.opensim.view.editors;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JOptionPane;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.Units;
import org.opensim.view.ExplorerTopComponent;
import org.opensim.view.functionEditor.FunctionEditorTopComponent;
import org.opensim.view.functionEditor.FunctionEditorTopComponent.FunctionEditorOptions;
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
               FunctionEditorOptions options = new FunctionEditorOptions();
               options.title = dof.getJoint().getName();
               if (dof.getMotionType() == AbstractDof.DofType.Rotational) {
                  options.YUnits = new Units(Units.UnitType.simmRadians);
                  options.YDisplayUnits = new Units(Units.UnitType.simmDegrees);
               } else {
                  options.YUnits = new Units(Units.UnitType.simmMeters);
                  options.YDisplayUnits = options.YUnits;
               }
               options.YLabel = options.YDisplayUnits.getLabel();
               if (dof.getCoordinate() != null) {
                  if (dof.getCoordinate().getMotionType() == AbstractDof.DofType.Rotational) {
                     options.XUnits = new Units(Units.UnitType.simmRadians);
                     options.XDisplayUnits = new Units(Units.UnitType.simmDegrees);
                  } else {
                     options.XUnits = new Units(Units.UnitType.simmMeters);
                     options.XDisplayUnits = options.XUnits;
                  }
                  options.XLabel = dof.getCoordinate().getName() + " (deg)";
               }
               functionEditor.open(newModel, dof, newFunction, options);
               functionEditor.requestActive();
            }
         }
      }
    } 
}
