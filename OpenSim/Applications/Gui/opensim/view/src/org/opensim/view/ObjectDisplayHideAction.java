package org.opensim.view;

import org.openide.util.NbBundle;

public final class ObjectDisplayHideAction extends ObjectDisplayShowHideBaseAction {

   public ObjectDisplayHideAction() {
      super(false);
   }

   public String getName() {
      return NbBundle.getMessage(ModelDisplayHideAction.class, "CTL_ModelDisplayHideAction");
   }
    
}
