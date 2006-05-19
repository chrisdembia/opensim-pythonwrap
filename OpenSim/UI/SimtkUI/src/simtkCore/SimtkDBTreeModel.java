package simtkCore;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Enumeration;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;

import opensimModel.ActuatorSet;
import opensimModel.Body;
import opensimModel.ControlSet;
import opensimModel.Model;
import opensimModel.OpenSimObject;
import opensimModel.*;

/**
 * SimtkDBTree is the holder of the abstract Tree representation of the models
 * currently laoded in SimtkUI. Abstract operations on the tree in terms of
 * adding model entities is done here. Visibility/icon stuff and callbacks
 * should be done somewhere else in the UI as they operate on displayed Tree.
 * This class should be treated as a datastructure rather than as a "JTree".
 */
public class SimtkDBTreeModel extends DefaultTreeModel{

  DefaultMutableTreeNode _root = null;

  public SimtkDBTreeModel() {
    super( new DefaultMutableTreeNode("Root", true));
    _root = (DefaultMutableTreeNode) getRoot();
    // Make sure being a leaf is not decided based on number of children as we have models without actuators
    // for example but we don't want the "Actuators" node to show as leaf.
    setAsksAllowsChildren(true);
  }

  /**
   * addModelToTree is the place where a model is added to the SimtkDBTree
   * data-structure
   *
   * @param mdl Model
   */
  public void addSimEnvToTree(SimtkSimEnv simEnvironment) {
    int numEnvirnments = getChildCount(_root);
    DefaultMutableTreeNode simenvNode = new DefaultMutableTreeNode(simEnvironment, true);
    insertNodeInto(simenvNode, _root, numEnvirnments);
    updateSimEnvTree((SimtkSimEnv) simenvNode.getUserObject());
  }

  /**
   * updateSimEnvTree updates the tree representation of a simulation environment
   * once changed by loading different model/integrator/...
   *
   * @param simEnvironment SimtkSimEnv Simulation environment that needs updating
   */
  public void updateSimEnvTree(SimtkSimEnv simEnvironment) {
   // Locate node corresponding to simEnvironment
   DefaultMutableTreeNode simenvNode = findSimenvNodeForSimEnv(simEnvironment);
   // Sanity check
   if (simenvNode == null){
     simtkui.SimtkApp.displayErrorMessage(
         "Internal error: Environment node was not found!");
     return;
   }
   updateSimEnvTree(simenvNode);
  }

  /**
   * updateSimEnvTree updates tree representation of a node representing a
   * SimtkEnv
   *
   * @param simenvNode DefaultMutableTreeNode
   */
  public void updateSimEnvTree(DefaultMutableTreeNode simenvNode) {
   simenvNode.removeAllChildren();
   // Data Manager
   DefaultMutableTreeNode dataManagerNode = new DefaultMutableTreeNode("Data Manager", true);
   insertNodeInto(dataManagerNode, simenvNode, 0);
   // Model Manager
   DefaultMutableTreeNode modelManagerNode = new DefaultMutableTreeNode("Model Manager", true);
   insertNodeInto(modelManagerNode, simenvNode, 1);
   // Now the model subtree
   SimtkSimEnv simEnvironment = (SimtkSimEnv) simenvNode.getUserObject();
   Model mdl = simEnvironment.getModel();
   if (mdl != null) {

     DefaultMutableTreeNode modelNode = new DefaultMutableTreeNode(mdl, true);
     insertNodeInto(modelNode, modelManagerNode, 0);
     { // Create Bodies tree
       DefaultMutableTreeNode bodiesNode = new DefaultMutableTreeNode(mdl.getBodySet(), true);
       insertNodeInto(bodiesNode, modelNode, 0);
       for (int i = 0; i < mdl.getNB(); i++) {
         Body bdy = mdl.getBody(i);
             DefaultMutableTreeNode nextBodyNode = new DefaultMutableTreeNode(
               bdy, false);
           bodiesNode.add(nextBodyNode);
       }
     }

     { // Create Actuators tree
       try {
         try {
           DefaultMutableTreeNode ActuatorsNode = new DefaultMutableTreeNode(
               "Actuators", true);
           insertNodeInto(ActuatorsNode, modelNode, 1);
           for (int i = 0; i <mdl.getNA(); i++) {
             DefaultMutableTreeNode nextActuatorSetNode = new
                 DefaultMutableTreeNode(mdl.getActuatorName(i), false);
             ActuatorsNode.add(nextActuatorSetNode);
           }
         }
         catch (IllegalArgumentException ex1) {
         }
       }
       catch (SecurityException ex) {
       }
     }

     Enumeration mdlObjectNames = simEnvironment.getModelObjectNames();
     if (mdlObjectNames != null){
       int idx = 0;
       while (mdlObjectNames.hasMoreElements()) {
         String mdlObjectName = (String) mdlObjectNames.nextElement();
         OpenSimObject mdlObject = simEnvironment.getModelObject(mdlObjectName);
         String objname = mdlObject.getName();
         if (objname.equals(""))
           mdlObject.setName(mdlObjectName);
         DefaultMutableTreeNode userObjectNode = new DefaultMutableTreeNode(
             mdlObject, true);
         insertNodeInto(userObjectNode, modelNode, 2+idx);
         idx++;
       }
     }
     /*
      { // Create Actuators tree
       try {
         // Check if method exists (weaker and more general than checking inheritance)
         Method contactsGetter = mdl.getClass().getMethod("getContactForceSet", null);
         rdContactForceSet contacts = null;
         try {
           contacts = (rdContactForceSet) contactsGetter.invoke(mdl, null);
           DefaultMutableTreeNode ContactsNode = new DefaultMutableTreeNode(
               contacts, true);
           insertNodeInto(ContactsNode, modelNode, 2);
           for (int i = 0; i <contacts.getSize(); i++) {
             DefaultMutableTreeNode nextContactSetNode = new
                 DefaultMutableTreeNode(contacts.get(i), false);
             ContactsNode.add(nextContactSetNode);
           }
         }
         catch (InvocationTargetException ex1) {
         }
         catch (IllegalArgumentException ex1) {
         }
         catch (IllegalAccessException ex1) {
         }

       }
       catch (SecurityException ex) {
       }
       catch (NoSuchMethodException ex) {
       }
     }
     { // Create Analyses tree
        DefaultMutableTreeNode AnalysesNode = new DefaultMutableTreeNode(mdl.getAnalysisSet(), true);
        insertNodeInto(AnalysesNode, modelNode, 2);
        for (int i = 0; i < mdl.getNumAnalyses(); i++) {
          DefaultMutableTreeNode nextAnalysisNode = new DefaultMutableTreeNode(
              mdl.getAnalysis(i), false);
          AnalysesNode.add(nextAnalysisNode);
        }

     }*/
   }
   if (simEnvironment.getSimulationManager() != null && simEnvironment.getSimulationManager().getIntegrand()!= null){
	   // Create nodes for Integrator and Controls
	   DefaultMutableTreeNode simManagerNode = new DefaultMutableTreeNode("Simulation Manager", true);
	   insertNodeInto(simManagerNode, simenvNode, 2);

	   DefaultMutableTreeNode managerNode = new DefaultMutableTreeNode(simEnvironment.getSimulationManager(), true);
	   insertNodeInto(managerNode, simManagerNode, 0);
           ModelIntegrand integrand = simEnvironment.getSimulationManager().getIntegrand();
	   ControlSet cs = integrand.getControlSet();

	   DefaultMutableTreeNode controlNode;
	   if (cs != null){
	     controlNode = new DefaultMutableTreeNode(cs, true);
	     // Create nodes for individual controls
	     int controlSetSize = cs.getSize();
	     for(int i=0; i < controlSetSize; i++){
	       DefaultMutableTreeNode singleControlNode = new DefaultMutableTreeNode(cs.get(i), true);
	       controlNode.add(singleControlNode);
	     }
	   }
	    else
	      controlNode = new DefaultMutableTreeNode("No ControlSet", true);

	   insertNodeInto(controlNode, managerNode, 0);
	   DefaultMutableTreeNode integratorNode = new DefaultMutableTreeNode(simEnvironment.getSimulationManager().getIntegrator(), true);
	   insertNodeInto(integratorNode, managerNode, 1);
  }
  // Tell listeners to update their status
   reload();
 }

  /**
   * findSimenvNodeForSimEnv
   *
   * @param simEnvironment SimtkSimEnv to search for
   * @return DefaultMutableTreeNode corresponding node in the tree
   */
  private DefaultMutableTreeNode findSimenvNodeForSimEnv(SimtkSimEnv
      simEnvironment) {

    DefaultMutableTreeNode simenvNode=null;

   Enumeration children = _root.children();
   while(children.hasMoreElements()){
     DefaultMutableTreeNode nextNode = (DefaultMutableTreeNode) children.nextElement();
     if (nextNode.getUserObject() == simEnvironment){
       simenvNode = nextNode;
       break;
     }
   }
    return simenvNode;
  }

  /**
   * removeModel
   *
   * @param mdl Model

  public void removeModel(Model mdl) {
    int numModels = getChildCount(_root);
    for (int i = 0; i < numModels; i++) {
      DefaultMutableTreeNode modelNode = (DefaultMutableTreeNode) _root.getChildAt(i);
      if (modelNode.getUserObject()==mdl){
        removeNodeFromParent((MutableTreeNode)modelNode);
        break;
      }
    }
  }
  */
  /**
   * findSimEnvForModel
   *
   * @param mdlName String
   */
  public SimtkSimEnv findSimEnvForModel(String mdlName) {
    int numEnvirnments = getChildCount(_root);
    SimtkSimEnv foundEnv=null;
    Enumeration environments = _root.children();
    // Cycle thru top level nodes and find grand children of nodes corresponding to SimtkSimEnv
    while(environments.hasMoreElements()){
      // For every SimtkSimEnv node, find corresponding Model node and check the name of corresponding Model
      DefaultMutableTreeNode nextEnvNode = (DefaultMutableTreeNode) environments.nextElement();
      TreeNode modelManagerNode = nextEnvNode.getChildAt(1);
      // Model manager may not have a model under it.
      if (modelManagerNode.getChildCount()==0)
        continue;
      DefaultMutableTreeNode modelNode = (DefaultMutableTreeNode) modelManagerNode.getChildAt(0);
      if (modelNode.getUserObject() instanceof Model){
        Model mdl = (Model)modelNode.getUserObject();
        String name = mdl.getName();
        if (name.equals(mdlName)){
          foundEnv = (SimtkSimEnv) nextEnvNode.getUserObject();
          break;
        }
      }
    }
    return foundEnv;
  }

  /**
   * removeEnvironment
   *
   * @param simEnv SimtkSimEnv
   */
  public void removeEnvironment(SimtkSimEnv simEnv) {
    // Locate node corresponding to simEnv
    DefaultMutableTreeNode envNode=findSimenvNodeForSimEnv(simEnv);
    if (envNode != null)
      removeNodeFromParent((MutableTreeNode)envNode);
  }
}
