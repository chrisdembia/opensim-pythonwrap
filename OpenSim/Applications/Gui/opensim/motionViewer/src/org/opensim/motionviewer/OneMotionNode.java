/*
 *
 * OneMotionNode
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
package org.opensim.motionviewer;

import java.awt.Image;
import org.opensim.modeling.SimmMotionData;
import org.opensim.view.nodes.OpenSimObjectNode;

/**
 *
 * @author Ayman
 */
public class OneMotionNode extends OpenSimObjectNode{
   
   /** Creates a new instance of OneMotionNode */
   public OneMotionNode(SimmMotionData motion) {
      super(motion);
   }

   public Image getIcon(int i) {
      Image retValue;
      
      retValue = super.getIcon(i);
      return retValue;
   }

   public Image getOpenedIcon(int i) {
      Image retValue;
      
      retValue = super.getOpenedIcon(i);
      return retValue;
   }
   
}
