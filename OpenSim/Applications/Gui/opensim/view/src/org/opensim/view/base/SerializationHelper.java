/*
 *
 * SerializationHelper
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
package org.opensim.view.base;

import java.beans.XMLEncoder;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

/**
 *
 * @author Ayman
 */
public final class SerializationHelper {
    
    static  SerializationHelper instance=null;
    static  File theFile;
    static  FileOutputStream outStream;
    static  ObjectOutputStream objStream;
    static  XMLEncoder xmlCommandEncoder;
    
    static public SerializationHelper getInstance()
    {
        if (instance == null){
            instance = new SerializationHelper();
        }
        return instance;

    }
    /** Creates a new instance of SerializationHelper */
    protected SerializationHelper() {
           theFile = new File("TheLogfile.log");
            // look for an existing file
            if(theFile.exists()) {
               theFile.delete();
               theFile = new File("TheLogfile.log");
            }
            try {
                // setup a stream to an actual file on the filesystem
                outStream = new FileOutputStream(theFile);
            } catch (FileNotFoundException ex) {
                ex.printStackTrace();
            }
            try {

                // attach a stream capable of writing objects to the stream connected to the file
                objStream = new ObjectOutputStream(outStream);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        try {
           
            xmlCommandEncoder = new XMLEncoder(
                       new BufferedOutputStream(
                             new FileOutputStream("myLog.xml")));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
           
           
    }
    
    public static ObjectOutputStream getLogStream()
    {
        if (objStream == null)
           getInstance();
        
        return objStream;
        
    }

    public static XMLEncoder getCommandEncoder() {
        if (xmlCommandEncoder==null)
           getInstance();
            
         return xmlCommandEncoder;
    }
}
