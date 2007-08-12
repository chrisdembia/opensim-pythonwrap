package org.opensim.tracking;

import javax.swing.JComponent;
import org.opensim.modeling.IO;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Property;
import org.opensim.modeling.PropertySet;

public class ToolCommon {

   public static final String MassFormatStr = "%.3f";
   public static final String TimeFormatStr = "%.3f";
   public static final String CoordinateFormatStr = "%.3f";
   public static final String WeightFormatStr = "%.3f";

   public static void bindProperty(OpenSimObject obj, String propertyName, JComponent comp) { 
      PropertySet pset = obj.getPropertySet();
      Property prop = pset.contains(propertyName);
      if(prop!=null) {
         String comment = prop.getComment();
         if(!comment.equals("")) {
            comp.setToolTipText("<html>"+IO.formatText(comment, "", 120, "<br>")+"<br><br>XML property: <b>"+obj.getType()+" > "+propertyName+"</b></html>");
         }
      } else {
         System.out.println("ToolCommon.bindProperty: Could not find property '"+propertyName+"' in object of type '"+obj.getType()+"'");
      }
   }
}
