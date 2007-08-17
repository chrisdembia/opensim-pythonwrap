/*
 *
 * ModelSettingsSerializer
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
package org.opensim.view;

import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.modeling.Model;

/**
 *
 * @author Ayman
 */
public class ModelSettingsSerializer {
   
   private String filename;
   private ModelSettings settings;
   /**
    * Creates a new instance of ModelSettingsSerializer 
    * filename to serialize from/to for the model
    */
   public ModelSettingsSerializer(String filename, boolean read) {
      this.setFilename(filename);
      if (read)
         read();
   }
   
   public void read()
   {
      if (getFilename()==null){ // Model has not been serialized ever before
         settings = new ModelSettings(); 
         return;
      }
      try{
         XMLDecoder decoder = new XMLDecoder(
                 new FileInputStream(getFilename()));
         settings=((ModelSettings)decoder.readObject());
         //System.out.println("Found ModelGUIPrefs with");
      }catch (FileNotFoundException e){
         //System.out.println("not found");
         settings = new ModelSettings();
      }
   }
   
   public Object confirmAndWrite(Model model)
   {
      if(getFilename()==null) { // Settings don't have a filename associated with them, can't save
         return NotifyDescriptor.NO_OPTION;
      }
      // Show message to prompt user
     String modelName = (model!=null && model.getName()!=null) ? model.getName() : "";
     String modelFileName = (model!=null && model.getInputFileName()!=null) ? (new File(model.getInputFileName())).getName() : "";
     String modelStr = modelName+" ("+modelFileName+")";
     NotifyDescriptor dlg = new NotifyDescriptor.Confirmation("Do you want to save settings (e.g. poses) for model "+modelStr+" to file?", "Save model settings?");
     Object userSelection=DialogDisplayer.getDefault().notify(dlg);
     if(((Integer)userSelection).intValue()==((Integer)NotifyDescriptor.OK_OPTION).intValue()){
         XMLEncoder encoder;
         try {
            encoder = new XMLEncoder(new FileOutputStream(getFilename()));
            encoder.writeObject(settings);
            encoder.close();
         } catch (FileNotFoundException ex) {
            ex.printStackTrace();
         }
     }
     return userSelection;
   }

   public ModelSettings getPrefs() {
      return settings;
   }

   public String getFilename() {
      return filename;
   }

   public void setFilename(String filename) {
      this.filename = filename;
   }
   
}
