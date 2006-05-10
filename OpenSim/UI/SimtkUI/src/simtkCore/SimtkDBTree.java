package simtkCore;

import javax.swing.tree.*;
import simtkModel.*;

/**
 * SimtkDBTree is the holder of the abstract Tree representation of the models
 * currently laoded in SimtkUI. Abstract operations on the tree in terms of
 * adding model entities is done here. Visibility/icon stuff and callbacks
 * should be done somewhere else in the UI as they operate on displayed Tree.
 * This class should be treated as a datastructure rather than as a "JTree".
 */
public class SimtkDBTree extends DefaultTreeModel{

  DefaultMutableTreeNode _root = null;

  public SimtkDBTree() {
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
   * @param mdl rdModel
   */
  public void addModelToTree(rdModel mdl) {
    int numModels = getChildCount(_root);
    DefaultMutableTreeNode modelNode = new DefaultMutableTreeNode("Model:"+mdl.getName(), true);
    insertNodeInto(modelNode, _root, numModels);
    { // Create Bodies tree
      DefaultMutableTreeNode bodiesNode = new DefaultMutableTreeNode("Bodies", true);
      insertNodeInto(bodiesNode, modelNode, 0);
      for (int i = 0; i < mdl.getNB(); i++) {
        DefaultMutableTreeNode nextBodyNode = new DefaultMutableTreeNode(
            "Body " + mdl.getBodyName(i), false);
        bodiesNode.add(nextBodyNode);
      }
    }
    { // Create Actuators tree
      DefaultMutableTreeNode ActuatorsNode = new DefaultMutableTreeNode(
          "Actuators", true);
      insertNodeInto(ActuatorsNode, modelNode, 1);
      for (int i = 0; i < mdl.getNA(); i++) {
        DefaultMutableTreeNode nextActuatorSetNode = new DefaultMutableTreeNode(
            "Actuator " + i, false);
        ActuatorsNode.add(nextActuatorSetNode);
      }
    }

  }
}
