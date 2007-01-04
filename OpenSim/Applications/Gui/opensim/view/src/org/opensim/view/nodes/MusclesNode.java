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
import javax.swing.Action;
import org.openide.util.NbBundle;
import org.opensim.modeling.ActuatorSet;

/**
 *
 * @author Ayman Habib
 *
 * Top level Muscles node in Navigator view
 */
public class MusclesNode extends OpenSimNode {
    
    private static ResourceBundle bundle = NbBundle.getBundle(MusclesNode.class);
    /** Creates a new instance of MusclesNode */
    public MusclesNode(ActuatorSet as) {
        super(new MuscleChildren(as));
        setDisplayName(NbBundle.getMessage(MusclesNode.class, "CTL_Actuators"));
    }    

   public Action[] getActions(boolean b) {
      Action[] retValue;
      
      retValue = super.getActions(b);
      return retValue;
   }
}
