package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractModel;
import org.opensim.view.*;
import org.opensim.view.actions.FileCloseAction;



/**
 * Node class to wrap AbstractModel objects
 */
public class ConcreteModelNode extends OpenSimObjectNode {

    public ConcreteModelNode(AbstractModel m) {
        super(m);
        
        getChildren().add(new Node[] {new BodiesNode(m.getDynamicsEngine().getBodySet())});
        getChildren().add(new Node[] {new MusclesNode(m.getActuatorSet())});
        getChildren().add(new Node[] {new JointsNode(m)});
   }
    public AbstractModel getModel()
    {
        return (AbstractModel) getOpensimObject();
    }
    /**
     * Actions available in model node popup.
     * @todo replace new'ing with the findObject substitute to avoid runtime "informational" exceptions
     */
    public Action[] getActions(boolean b) {
        Action[] classSpecificActions=null;
        try {
            classSpecificActions = new Action[]{
                (FileCloseAction)FileCloseAction.findObject(
                        Class.forName("org.opensim.view.actions.FileCloseAction")),
                (ViewMakeNewAction)ViewMakeNewAction.findObject(
                        Class.forName("org.opensim.view.nodes.ViewMakeNewAction")), 
                getTreeModelMakeCurrentAction(),
                (ModelDisplayShowAction)ModelDisplayShowAction.findObject(
                        Class.forName("org.opensim.view.ModelDisplayShowAction")), 
                (ModelDisplayHideAction)ModelDisplayHideAction.findObject(
                        Class.forName("org.opensim.view.ModelDisplayHideAction")), 
                (ModelDisplayEditAction)ModelDisplayEditAction.findObject(
                        Class.forName("org.opensim.view.ModelDisplayEditAction")), 
            };
        }
        catch(ClassNotFoundException e){
            
        }
        return classSpecificActions;
    }

    public String getHtmlDisplayName() {
        String retValue;
        
        retValue = super.getHtmlDisplayName();
        if (getModel()==ViewDB.getCurrentModel())
            retValue="<b>"+retValue+"</b>";
            
        return retValue;
    }

    Action getTreeModelMakeCurrentAction()
    {
           return new CallableSystemAction(){
            /**
             * @todo handle no views situation where getCurrenWindow() returns null
             */
            public void performAction() {
                 OpenSimDB.getInstance().setCurrentModel(getModel());
            }

            public String getName() {
                return "Make Current";
            }

            public HelpCtx getHelpCtx() {
                return null;
            }
            public boolean isEnabled() {
                return OpenSimDB.getInstance().getCurrentModel()!=getModel();
            }};

    }
}