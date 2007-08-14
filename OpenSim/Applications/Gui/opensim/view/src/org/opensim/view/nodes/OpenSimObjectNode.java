/*
 *
 * OpenSimObjectNode
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

import java.util.ArrayList;
import javax.swing.Action;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ObjectDisplayHideAction;
import org.opensim.view.ObjectDisplayMenuAction;
import org.opensim.view.ObjectDisplayShowAction;
import org.opensim.view.ObjectGenericReviewAction;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman. A node backed by an OpenSim Object 
 * (or a Set as a set is also an Object)
 */
public class OpenSimObjectNode extends OpenSimNode {
    
    private OpenSimObject openSimObject;
    public enum displayOption{Showable, Isolatable, Colorable};
    private ArrayList<displayOption> validDisplayOptions = new ArrayList<displayOption>();
    
    /** Creates a new instance of OpenSimObjectNode */
    public OpenSimObjectNode(OpenSimObject obj) {
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
              return null;
          
         OpenSimObject obj=getOpenSimObject();
         int currentStatus=ViewDB.getInstance().getDisplayStatus(obj);
         try {
            if (currentStatus==0){   // Hidden
               return ((ObjectDisplayShowAction) ObjectDisplayShowAction.findObject(
                Class.forName("org.opensim.view.ObjectDisplayShowAction"), true));
            }
            else if (currentStatus==1 || currentStatus==2){ // 2 for mixed, some shown some hidden, pick show
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
         boolean showDisplayMenu = validDisplayOptions.size()>0;
         if (showDisplayMenu)
            objectNodeActions = new Action[]  {getReviewAction(), 
                                          null, 
                                          (ObjectDisplayMenuAction) ObjectDisplayMenuAction.findObject(
                 Class.forName("org.opensim.view.ObjectDisplayMenuAction"), true)};
         else
            objectNodeActions = new Action[]  {getReviewAction()};
         
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
   
   protected void addDisplayOption(displayOption newOption)
   {
      if (!getValidDisplayOptions().contains(newOption))
         getValidDisplayOptions().add(newOption);
   }

   public ArrayList<displayOption> getValidDisplayOptions() {
      return validDisplayOptions;
   }
}
