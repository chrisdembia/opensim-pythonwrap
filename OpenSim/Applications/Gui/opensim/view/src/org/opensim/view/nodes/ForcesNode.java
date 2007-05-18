/*
 *
 * ForcesNode
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
import org.opensim.modeling.Force;
import org.opensim.modeling.ObjectGroup;

/**
 *
 * @author Peter Loan
 *
 * Forces node (under Actuators) in Navigator view
 */
public class ForcesNode extends OpenSimObjectNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(ForcesNode.class);
   /**
    * Creates a new instance of ForcesNode
    */
   public ForcesNode(ActuatorSet as) {
      super(as);
      setDisplayName(NbBundle.getMessage(ForcesNode.class, "CTL_Forces"));
      Children children = getChildren();
      int numForceGroups = countForceGroups(as);
      int numForces = countForces(as);
      if (numForceGroups == 0) {
         // There are no Force groups, so just add all of the
         // forces directly under the Forces node.
         for (int actuatorNum=0; actuatorNum < as.getSize(); actuatorNum++ ) {
            Force force = Force.safeDownCast(as.get(actuatorNum));
            if (force != null) {
               OneActuatorNode node = new OneActuatorNode(force);
               Node[] arrNodes = new Node[1];
               arrNodes[0] = node;
               children.add(arrNodes);
            }
         }
      } else {
         for (int i = 0; i < as.getNumGroups(); i++) {
            ObjectGroup grp = as.getGroup(i);
            ArrayPtrsObj apo = grp.getMembers();
            Force force = Force.safeDownCast(apo.get(0));
            // If the first member of the group is a Force, then
            // consider this group to be a Force group.
            if (force != null) {
               children.add(new Node[] {new ActuatorGroupNode(grp)});
            }
         }
      }
   }
   /**
    * Display name 
    */
   public String getHtmlDisplayName() {
       return NbBundle.getMessage(ForcesNode.class, "CTL_Forces");
   }

   private int countForceGroups(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getNumGroups(); i++) {
         ObjectGroup grp = as.getGroup(i);
         ArrayPtrsObj apo = grp.getMembers();
         Force force = Force.safeDownCast(apo.get(0));
         // If the first member of the group is a Force, then
         // consider this group to be a Force group.
         if (force != null)
            count++;
      }
      return count;
   }

   private int countForces(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getSize(); i++) {
         Force force = Force.safeDownCast(as.get(i));
         if (force != null)
            count++;
      }
      return count;
   }
}
