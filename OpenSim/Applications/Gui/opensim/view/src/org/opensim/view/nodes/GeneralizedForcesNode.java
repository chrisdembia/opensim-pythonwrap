/*
 *
 * GeneralizedForcesNode
 * Author(s): Peter Loan
 * Copyright (c) 2007, Stanford University, Peter Loan
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view.nodes;

import java.util.ResourceBundle;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.GeneralizedForce;
import org.opensim.modeling.ObjectGroup;

/**
 *
 * @author Peter Loan
 *
 * GeneralizedForces node (under Actuators) in Navigator view
 */
public class GeneralizedForcesNode extends OpenSimObjectNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(GeneralizedForcesNode.class);
   /**
    * Creates a new instance of GeneralizedForcesNode
    */
   public GeneralizedForcesNode(ActuatorSet as) {
      super(as);
      setDisplayName(NbBundle.getMessage(GeneralizedForcesNode.class, "CTL_GeneralizedForces"));
      Children children = getChildren();
      int numGeneralizedForceGroups = countGeneralizedForceGroups(as);
      int numGeneralizedForces = countGeneralizedForces(as);
      if (numGeneralizedForceGroups == 0) {
         // There are no GeneralizedForce groups, so just add all of the
         // generalized forces directly under the GeneralizedForces node.
         for (int actuatorNum=0; actuatorNum < as.getSize(); actuatorNum++ ) {
            GeneralizedForce genforce = GeneralizedForce.safeDownCast(as.get(actuatorNum));
            if (genforce != null) {
               OneActuatorNode node = new OneActuatorNode(genforce);
               Node[] arrNodes = new Node[1];
               arrNodes[0] = node;
               children.add(arrNodes);
            }
         }
      } else {
         for (int i = 0; i < as.getNumGroups(); i++) {
            ObjectGroup grp = as.getGroup(i);
            ArrayPtrsObj apo = grp.getMembers();
            GeneralizedForce genforce = GeneralizedForce.safeDownCast(apo.get(0));
            // If the first member of the group is a GeneralizedForce, then
            // consider this group to be a GeneralizedForce group.
            if (genforce != null) {
               children.add(new Node[] {new ActuatorGroupNode(grp)});
            }
         }
      }
      if (getChildren().getNodesCount() == 0)
         setChildren(children.LEAF);
   }
   /**
    * Display name 
    */
   public String getHtmlDisplayName() {
       return NbBundle.getMessage(GeneralizedForcesNode.class, "CTL_GeneralizedForces");
   }

   private int countGeneralizedForceGroups(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getNumGroups(); i++) {
         ObjectGroup grp = as.getGroup(i);
         ArrayPtrsObj apo = grp.getMembers();
         if (apo.getSize()==0) continue;  // Gaurd against empty groups
         GeneralizedForce genforce = GeneralizedForce.safeDownCast(apo.get(0));
         // If the first member of the group is a GeneralizedForce, then
         // consider this group to be a GeneralizedForce group.
         if (genforce != null)
            count++;
      }
      return count;
   }

   private int countGeneralizedForces(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getSize(); i++) {
         GeneralizedForce genforce = GeneralizedForce.safeDownCast(as.get(i));
         if (genforce != null)
            count++;
      }
      return count;
   }
}

