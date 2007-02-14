/*
 *
 * MusclesNode
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
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

/**
 *
 * @author Ayman Habib
 *
 * Top level Muscles node in Navigator view
 */
public class MusclesNode extends OpenSimObjectNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(MusclesNode.class);
   /** Creates a new instance of MusclesNode */
   public MusclesNode(ActuatorSet as) {
      super(as);
      setDisplayName(NbBundle.getMessage(MusclesNode.class, "CTL_Actuators"));
      Children children = getChildren();
      for (int actuatorNum=0; actuatorNum < as.getSize(); actuatorNum++ ){
         
         AbstractActuator actuator = as.get(actuatorNum);
         
         OneMuscleNode node = new OneMuscleNode(actuator);
         Node[] arrNodes = new Node[1];
         arrNodes[0] = node;
         children.add(arrNodes);         
      }
   }
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return NbBundle.getMessage(MusclesNode.class, "CTL_Actuators");
    }
   
}
