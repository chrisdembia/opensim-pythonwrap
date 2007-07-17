/*
 *
 * ActuatorGroupNode
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
import org.opensim.modeling.ObjectGroup;

/**
 *
 * @author Peter Loan
 *
 * Top level Actuators node in Navigator view
 */
public class ActuatorGroupNode extends OpenSimObjectNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(ActuatorGroupNode.class);
   /**
    * Creates a new instance of ActuatorGroupNode
    */
   public ActuatorGroupNode(ObjectGroup group) {
      super(group);
      setDisplayName(group.getName());
      Children children = getChildren();
      ArrayPtrsObj members = group.getMembers();
      for (int i = 0; i < members.getSize(); i++ ) {
         OneActuatorNode node = new OneActuatorNode(members.get(i));
         Node[] arrNodes = new Node[1];
         arrNodes[0] = node;
         children.add(arrNodes);         
      }
   }
   /**
    * Display name 
    */
   public String getHtmlDisplayName() {
      return getOpenSimObject().getName() ;
   }
}
