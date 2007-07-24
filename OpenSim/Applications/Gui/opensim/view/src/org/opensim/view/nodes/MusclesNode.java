/*
 *
 * MusclesNode
 * Author(s): Peter Loan & Jeff Reinbolt
 * Copyright (c) 2007, Stanford University, Peter Loan & Jeff Reinbolt
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

import java.awt.Image;
import java.net.URL;
import javax.swing.ImageIcon;
import java.util.ResourceBundle;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.ObjectGroup;

/**
 *
 * @author Peter Loan & Jeff Reinbolt
 *
 * Muscles node (under Actuators) in Navigator view
 */
public class MusclesNode extends OpenSimObjectNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(MusclesNode.class);
   /**
    * Creates a new instance of MusclesNode
    */
   public MusclesNode(ActuatorSet as) {
      super(as);
      setDisplayName(NbBundle.getMessage(MusclesNode.class, "CTL_Muscles"));
      Children children = getChildren();
      int numMuscleGroups = countMuscleGroups(as);
      int numMuscles = countMuscles(as);
      if (numMuscleGroups == 0) {
         // There are no AbstractMuscle groups, so just add all of the
         // muscles directly under the Muscles node.
         for (int actuatorNum=0; actuatorNum < as.getSize(); actuatorNum++ ) {
            AbstractMuscle muscle = AbstractMuscle.safeDownCast(as.get(actuatorNum));
            if (muscle != null) {
               OneActuatorNode node = new OneActuatorNode(muscle);
               Node[] arrNodes = new Node[1];
               arrNodes[0] = node;
               children.add(arrNodes);
            }
         }
      } else {
         boolean userDefinedAllGroup = false;
         for (int i = 0; i < as.getNumGroups(); i++) {
            ObjectGroup grp = as.getGroup(i);
            ArrayPtrsObj apo = grp.getMembers();
            AbstractMuscle muscle = AbstractMuscle.safeDownCast(apo.get(0));
            // If the first member of the group is an AbstractMuscle, then
            // consider this group to be an AbstractMuscle group.
            if (muscle != null) {
               children.add(new Node[] {new ActuatorGroupNode(grp)});
               if (grp.getName().equals("all"))
                  userDefinedAllGroup = true;
            }
         }
         // Now make the "all" group, if there is not already one by that name
         if (userDefinedAllGroup == false) {
            ObjectGroup allGroup = new ObjectGroup();
            allGroup.setName("all");
            for (int actuatorNum=0; actuatorNum < as.getSize(); actuatorNum++ ) {
               AbstractMuscle muscle = AbstractMuscle.safeDownCast(as.get(actuatorNum));
               if (muscle != null) {
                  allGroup.add(muscle);
               }
            }
            children.add(new Node[] {new ActuatorGroupNode(allGroup)});
         }
      }
      if (getChildren().getNodesCount() == 0)
         setChildren(children.LEAF);
   }
   
   public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/muscleNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
   public Image getOpenedIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/muscleNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
   /**
    * Display name 
    */
   public String getHtmlDisplayName() {
       return NbBundle.getMessage(MusclesNode.class, "CTL_Muscles");
   }

   private int countMuscleGroups(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getNumGroups(); i++) {
         ObjectGroup grp = as.getGroup(i);
         ArrayPtrsObj apo = grp.getMembers();
         if (apo.getSize()==0) continue;  // Gaurd against empty groups
         AbstractMuscle muscle = AbstractMuscle.safeDownCast(apo.get(0)); ////// CRASHHHHHHHHHHHHHHH because cmctool messes around with Actuators!
         // If the first member of the group is an AbstractMuscle, then
         // consider this group to be an AbstractMuscle group.
         if (muscle != null)
            count++;
      }
      return count;
   }

   private int countMuscles(ActuatorSet as) {
      int count = 0;
      for (int i = 0; i < as.getSize(); i++) {
         AbstractMuscle muscle = AbstractMuscle.safeDownCast(as.get(i));
         if (muscle != null)
            count++;
      }
      return count;
   }
}
