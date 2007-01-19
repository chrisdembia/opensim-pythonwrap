package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractModel;
import org.opensim.view.*;
import org.opensim.view.actions.FileCloseAction;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 * Node class to wrap AbstractModel objects
 */
public class ConcreteModelNode extends OpenSimObjectNode {

    public ConcreteModelNode(AbstractModel m) {
        super(m);
        
        getChildren().add(new Node[] {new BodiesNode(m.getDynamicsEngine().getBodySet())});
        getChildren().add(new Node[] {new MusclesNode(m.getActuatorSet())});
        getChildren().add(new Node[] {new JointsNode(m)});
        getChildren().add(new Node[] {new MotionsNode()});
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
                new ModelDisplayEditAction(), 
                new ModelDisplayHideAction(),
                new ModelDisplayShowAction(),
                new ModelInfoAction()
                
            };
        }
        catch(ClassNotFoundException e){
            
        }
        /**
         * Consolidate the two lists
         * The following is very inefficent. Just testing the idea.
         *
        Action[] superActions;
        
        superActions = super.getActions(b);
        Vector<Action> allActions = new Vector<Action>(10);
        for(int i=0; i<classSpecificActions.length; i++)
           allActions.add(classSpecificActions[i]);
        for(int i=0; i<superActions.length; i++)
           allActions.add(superActions[i]);
        Action[] actionArray = new Action[allActions.size()];
        
        for(int i=0; i <actionArray.length; i++)
           actionArray[i] = allActions.get(i);
        */
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