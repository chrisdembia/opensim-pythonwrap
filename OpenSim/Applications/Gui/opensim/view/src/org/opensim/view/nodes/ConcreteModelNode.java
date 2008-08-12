package org.opensim.view.nodes;

import javax.swing.Action;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.Model;
import org.opensim.view.*;
import org.opensim.view.pub.ViewDB;

/**
 * Node class to wrap Model objects
 */
public class ConcreteModelNode extends OpenSimObjectNode {

    public ConcreteModelNode(Model m) {
        super(m);
        
            getChildren().add(new Node[] {new BodiesNode(m.getDynamicsEngine().getBodySet())});
            getChildren().add(new Node[] {new ActuatorsNode(m.getActuatorSet())});
            getChildren().add(new Node[] {new JointsNode(m.getDynamicsEngine().getJointSet())});
      getChildren().add(new Node[] {new MarkersNode(m.getDynamicsEngine().getMarkerSet())});
      addDisplayOption(displayOption.Isolatable);
      addDisplayOption(displayOption.Showable);
   }
   public Model getModel() {
        return (Model) getOpenSimObject();
    }
    /**
     * Actions available in model node popup.
     * @todo replace new'ing with the findObject substitute to avoid runtime "informational" exceptions
     */
    public Action[] getActions(boolean b) {
        Action[] classSpecificActions=null;
        try {
            classSpecificActions = new Action[]{
                (ModelMakeCurrentAction) ModelMakeCurrentAction.findObject(
                        Class.forName("org.opensim.view.nodes.ModelMakeCurrentAction"), true),
                (ModelRenameAction) ModelRenameAction.findObject(
                        Class.forName("org.opensim.view.ModelRenameAction"), true),
                (ModelDisplayMenuAction) ModelDisplayMenuAction.findObject(
                        Class.forName("org.opensim.view.ModelDisplayMenuAction"), true),
                (ModelInfoAction) ModelInfoAction.findObject(
                        Class.forName("org.opensim.view.nodes.ModelInfoAction"), true),
                (ModelCloseSelectedAction) ModelCloseSelectedAction.findObject(
                        Class.forName("org.opensim.view.nodes.ModelCloseSelectedAction"), true),
                
            };
      } catch(ClassNotFoundException e){
            
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

   public Action getPreferredAction() {
      Action act=null;
      try {
         act =(ModelMakeCurrentAction) ModelMakeCurrentAction.findObject(
                    Class.forName("org.opensim.view.nodes.ModelMakeCurrentAction"), true);
      } catch(ClassNotFoundException e){
         
 }
      return act;
   }
}
