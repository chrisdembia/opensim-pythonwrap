package org.opensim.view;

import org.openide.util.NbBundle;

public final class ObjectDisplayShowAction extends ObjectDisplayShowHideBaseAction {

   public ObjectDisplayShowAction() {
      super(true);
   }

   public String getName() {
      return NbBundle.getMessage(ModelDisplayHideAction.class, "CTL_ModelDisplayShowAction");
   }

}
