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
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;

/**
 *
 * @author Ayman
 */
public class ModelSettingsSerializer {
   
   String filename;
   private ModelSettings settings;
   /**
    * Creates a new instance of ModelSettingsSerializer 
    * filename to serialize from/to for the model
    */
   public ModelSettingsSerializer(String filename, boolean read) {
      this.filename = filename;
      if (read)
         read();
   }
   
   public void read()
   {
      try{
         XMLDecoder decoder = new XMLDecoder(
                 new FileInputStream(filename));
         settings=((ModelSettings)decoder.readObject());
         //System.out.println("Found ModelGUIPrefs with");
      }catch (FileNotFoundException e){
         //System.out.println("not found");
         settings = new ModelSettings();
      }
   }
   
   public void write()
   {
      // Show message to prompt user
     NotifyDescriptor dlg = new NotifyDescriptor.Confirmation("Do you want to save model settings to file?");
     if(DialogDisplayer.getDefault().notify(dlg)==NotifyDescriptor.OK_OPTION){
         XMLEncoder encoder;
         try {
            encoder = new XMLEncoder(new FileOutputStream(filename));
            encoder.writeObject(settings);
            encoder.close();
         } catch (FileNotFoundException ex) {
            ex.printStackTrace();
         }
     }
   }

   public ModelSettings getPrefs() {
      return settings;
   }
   
}
