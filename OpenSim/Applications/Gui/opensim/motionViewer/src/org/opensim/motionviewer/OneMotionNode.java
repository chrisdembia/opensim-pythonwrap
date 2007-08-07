/*
 *
 * OneMotionNode
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
package org.opensim.motionviewer;

import java.awt.Image;
import java.net.URL;
import javax.swing.ImageIcon;
import javax.swing.Action;
import org.openide.nodes.Children;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.view.nodes.*;

/**
 *
 * @author Ayman & Jeff
 */
public class OneMotionNode extends OpenSimObjectNode{

    /** Creates a new instance of OneMotionNode */
   public OneMotionNode(Storage motion) {
      super(motion);
      setChildren(Children.LEAF);
   }
   
   public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/motionNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
//      Image retValue;
//      
//      retValue = super.getIcon(i);
//      return retValue;
   }

   public Image getOpenedIcon(int i) {
       return getIcon(i);
//      Image retValue;
//      
//      retValue = super.getOpenedIcon(i);
//      return retValue;
   }
   
   public Model getModel()
   {
       return getModelForNode();
   }

   public Storage getMotion()
   {
      return (Storage)getOpenSimObject();
   }

    public Action[] getActions(boolean b) {
        Action[] retValue=null;
        try {
            
            retValue = new Action[]{
                (MotionsCloseAction) MotionsCloseAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsCloseAction"), true),
                (MotionsSaveAsAction) MotionsSaveAsAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSaveAsAction"), true),
                (MotionsSynchronizeAction) MotionsSynchronizeAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSynchronizeAction"), true),
                (MotionsSetCurrentAction) MotionsSetCurrentAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSetCurrentAction"), true),
            };
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        
        return retValue;
    }
    
    public String getHtmlDisplayName() {
        String retValue;
        
        retValue = super.getHtmlDisplayName();
        MotionsDB.ModelMotionPair modelMotionPair = new MotionsDB.ModelMotionPair(getModel(), getMotion());
        if (MotionsDB.getInstance().isModelMotionPairCurrent(modelMotionPair))
           retValue = "<b>"+retValue+"</b>";
        return retValue;
    }
}
