/*
 *
 * ActuatorsNode
 * Author(s): Ayman Habib & Jeff Reinbolt
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib & Jeff Reinbolt
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
import javax.swing.Action;
import org.openide.nodes.Node;
import org.openide.util.NbBundle;
import org.opensim.modeling.ActuatorSet;

/**
 *
 * @author Ayman Habib & Jeff Reinbolt
 *
 * Top level Actuators node in Navigator view
 */
public class ActuatorsNode extends OpenSimObjectSetNode {
   
   private static ResourceBundle bundle = NbBundle.getBundle(ActuatorsNode.class);
   /**
    * Creates a new instance of ActuatorsNode
    */
   public ActuatorsNode(ActuatorSet as) {
      super(as);
      setDisplayName(NbBundle.getMessage(ActuatorsNode.class, "CTL_Actuators"));
      getChildren().add(new Node[] {new MusclesNode(as)});
      getChildren().add(new Node[] {new ForcesNode(as)});
      getChildren().add(new Node[] {new TorquesNode(as)});
      getChildren().add(new Node[] {new GeneralizedForcesNode(as)});
   }
   /**
    * Display name
    */
   public String getHtmlDisplayName() {
      
      return NbBundle.getMessage(ActuatorsNode.class, "CTL_Actuators");
   }
   /**
    * Actions, override behavior in OpenSimObjectNode since display options are not available
    */
   public Action[] getActions(boolean b) {
      Action[] classSpecificActions=null;
      classSpecificActions = new Action[]{
         getReviewAction()};
      return classSpecificActions;
   }
   
      public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/actuatorsNode.png");
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
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/actuatorsNode.png");
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
