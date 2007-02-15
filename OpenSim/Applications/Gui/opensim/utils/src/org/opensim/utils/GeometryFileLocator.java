/*
 *
 * GeometryFileLocator
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
package org.opensim.utils;

import java.io.File;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.prefs.Preferences;

/**
 *
 * @author Ayman. Enforces the policy for locating geometry files aka bone files
 * The policy is to search:
 * - directory bones under modelFilePath.
 * - GeometryPath preference directory if set
 * - under installation
 */
public class GeometryFileLocator {
   
   static GeometryFileLocator locator;
   /** Creates a new instance of GeometryFileLocator */
   public GeometryFileLocator() {
   }
   
   public static GeometryFileLocator getInstance(){
      if (locator==null)
         locator = new GeometryFileLocator();
      
      return locator;
   }

   public String getFullname(String modelFilePath, String bareFileName) {
      String candidate=modelFilePath+File.separator+bareFileName;
      if (new File(candidate).exists())
         return candidate;
      candidate = modelFilePath+File.separator+"geometry"+File.separator+bareFileName;
      if (new File(candidate).exists())
         return candidate;
      String GeometryPath=Preferences.userNodeForPackage(TheApp.class).get("GeometryPath", ".");
      if (GeometryPath!=null){
         // Split at ";" to get directoryList
         StringTokenizer tokenizer = new StringTokenizer(GeometryPath, File.pathSeparator);
         Vector<String> dirList = new Vector<String>(4);
         // Try directory list in order
         while(tokenizer.hasMoreElements()){
                String nextDir = tokenizer.nextToken();
                candidate = nextDir+File.separator+bareFileName;
               if (new File(candidate).exists())
                  return candidate;
         }
      }
      return null;
   }
   
}
