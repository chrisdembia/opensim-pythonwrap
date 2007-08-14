package org.opensim.view;

import org.openide.util.NbBundle;

public final class ObjectDisplayHideAction extends ObjectDisplayShowHideBaseAction {

   public ObjectDisplayHideAction() {
      super(false);
   }

   public String getName() {
      return NbBundle.getMessage(ObjectDisplayHideAction.class, "CTL_ModelDisplayHideAction");
   }
    
}
