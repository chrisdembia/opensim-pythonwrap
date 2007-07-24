/*
 *
 * JointsNode
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
import java.net.URL;
import java.util.ResourceBundle;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.opensim.view.nodes.*;

/**
 *
 * @author Ayman Habib
 *
 * Top level motions node in Navigator view
 */
public class MotionsNode extends OpenSimNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(MotionsNode.class);
   
   /** Creates a new instance of MotionsNode */
   public MotionsNode() {
      setDisplayName("Motions");
      setName("Motions"); // To be used by findNode();
   }
   
   /**
    * Icon for the node, same as OpenSimNode
    **/
   public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/motionsNode.png");
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
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/motionsNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }

}
