/*
 *
 * OpenSimObjectSetNode
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

import javax.swing.Action;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ObjectDisplayHideAction;
import org.opensim.view.ObjectDisplayShowAction;
import org.opensim.view.ObjectGenericReviewAction;
import org.opensim.view.ObjectSetDisplayMenuAction;
import org.opensim.view.nodes.OpenSimObjectNode.displayOption;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman. A node backed by an OpenSim Set
 */
public class OpenSimObjectSetNode extends OpenSimObjectNode {
    
    private OpenSimObject openSimObject;
    
    /** Creates a new instance of OpenSimObjectNode */
    public OpenSimObjectSetNode(OpenSimObject obj) {
        super(obj);
       this.openSimObject = obj;
        setDisplayName(obj.getName());
     }
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return getOpenSimObject().getName() ;
    }

    /**
     * Action to be invoked on double clicking.
     */
    public Action getPreferredAction() {
       if (getValidDisplayOptions().size()==0)  // Nothing to show or hide.
           return getReviewAction();

         // Collect objects from children and obtain their visibility status
         Children children = getChildren();
         Node[] theNodes = children.getNodes();
         int collectiveStatus = 3;  // unknown;
         for(int i=0; i<theNodes.length; i++){
            Node node = theNodes[i];
            if (!(node instanceof OpenSimObjectNode))
               continue;
            // Cycle thru children and get their display status, 
            int currentStatus=ViewDB.getInstance().getDisplayStatus(((OpenSimObjectNode) node).getOpenSimObject());
            if (collectiveStatus==3){
               collectiveStatus=currentStatus;
            }
            else {
               if (currentStatus!=collectiveStatus)
                  collectiveStatus=2;  // mixed;
            }
         }
         if (collectiveStatus==3)   
            return getReviewAction();
         if (collectiveStatus==2) collectiveStatus=0;  // Assume hidden if mixed
         
         try {
            if (collectiveStatus==0){   // Hidden
               return ((ObjectDisplayShowAction) ObjectDisplayShowAction.findObject(
                Class.forName("org.opensim.view.ObjectDisplayShowAction"), true));
            }
            else { // 2 for mixed, some shown some hidden, pick show
                    return ((ObjectDisplayHideAction) ObjectDisplayHideAction.findObject(
                    Class.forName("org.opensim.view.ObjectDisplayHideAction"), true));
            }
         } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
         }
            
         return getReviewAction();
    }
          
    /**
     * Return the list of available actions.
     * Subclasses should user super.getActions() to use this
     */
    public Action[] getActions(boolean b) {
      Action[] objectNodeActions;
      try {
         objectNodeActions = new Action[]  {getReviewAction(), 
                                          null, 
                                          (ObjectSetDisplayMenuAction) ObjectSetDisplayMenuAction.findObject(
                 Class.forName("org.opensim.view.ObjectSetDisplayMenuAction"), true)};
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
         objectNodeActions = new Action[] {null};
      }
      return objectNodeActions;
    }
    /**
     * return the Object presented by this node
     */
    public OpenSimObject getOpenSimObject() {
        return openSimObject;
    }

   protected Action getReviewAction() {
      Action act =null;
      try {
         act = (ObjectGenericReviewAction) ObjectGenericReviewAction.findObject(
                    Class.forName("org.opensim.view.ObjectGenericReviewAction"), true);
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      return act;
   }

}
