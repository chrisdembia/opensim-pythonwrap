package org.opensim.tracking;

import java.util.Vector;
import org.opensim.modeling.OpenSimObject;
import org.opensim.utils.XMLExternalFileChooser;

public class XMLExternalFileChooserHelper {
   public static class Item {
      public OpenSimObject obj;
      public String description;
      public Item(OpenSimObject obj, String description) { this.obj = obj; this.description = description; }
   }

   private Vector<Item> items = new Vector<Item>();

   public void addObject(OpenSimObject obj, String description) {
      items.add(new Item(obj,description));
   }

   public boolean promptUser() {
      String[] names = new String[items.size()];
      String[] externalFileNames = new String[items.size()];
      for(int i=0; i<items.size(); i++) {
         names[i] = items.get(i).description;
         externalFileNames[i] = getXMLExternalFileName(items.get(i).obj);
      }
      boolean result = XMLExternalFileChooser.promptUser(names, externalFileNames);
      if(result) {
         for(int i=0; i<items.size(); i++)
            applyXMLExternalFileName(items.get(i).obj, externalFileNames[i]);
      }
      return result;
   }

   private static String getXMLExternalFileName(OpenSimObject obj) {
      return (!obj.getInlined() && !obj.getDocumentFileName().equals("")) ? obj.getDocumentFileName() : null;
   }

   private static void applyXMLExternalFileName(OpenSimObject obj, String externalFileName) {
      System.out.println("APPLY " + externalFileName + " to " + obj.getType());
      if(externalFileName==null) obj.setInlined(true);
      else obj.setInlined(false, externalFileName);
   }
}
