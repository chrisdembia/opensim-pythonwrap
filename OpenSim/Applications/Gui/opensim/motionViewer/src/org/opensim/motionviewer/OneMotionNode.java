/*
 *
 * OneMotionNode
 * Author(s): Ayman Habib & Jeff Reinbolt
 * Copyright (c)  2005-2006, Stanford University, Ayman Habib & Jeff Reinbolt
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
                (MotionsSetCurrentAction) MotionsSetCurrentAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSetCurrentAction"), true),
                (MotionRenameAction) MotionRenameAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionRenameAction"), true),
                (MotionAppendMotionAction) MotionAppendMotionAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionAppendMotionAction"), true),
                (MotionsSynchronizeAction) MotionsSynchronizeAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSynchronizeAction"), true),
                (MotionsSaveAsAction) MotionsSaveAsAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsSaveAsAction"), true),
                (MotionsCloseAction) MotionsCloseAction.findObject(
                     Class.forName("org.opensim.motionviewer.MotionsCloseAction"), true),
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
