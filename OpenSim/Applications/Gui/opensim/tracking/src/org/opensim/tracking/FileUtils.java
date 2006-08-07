/*
 *
 * FileUtils
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
package org.opensim.tracking;
import java.io.File;

/**
 *
 * @author Ayman
 *
 * Class intended to have only static helper methods for operating on files and directories
 */
public final class FileUtils {
    
    /**
     * getNextAvailableName for a file with prefix baseName in passed in folder
     * use "." for current directory
     *
     * Extension is assumed to include trailing path separator char
     * String returned is the local name only and is not the full path
     */ 
    public static String getNextAvailableName(String folder, String baseName, String extension)
    {
        // Check that thae folder do exist, otherwise return the passed in name, ext
        File parentDir = new File(folder);
        String extensionString = (extension==null)?"":extension;
        if (!parentDir.isDirectory()){
            if (extension==null)
                return baseName;
            else
                return baseName+File.separator+extension;
        }
         // Cycle thru and check if the file exists, return first available
        boolean found = false;
        int index=0;
         while(!found){
            String suffix = (index==0)?"":"_"+String.valueOf(index);
            File nextCandidate = new File(folder+baseName+suffix+File.separatorChar+extensionString);
            if (!nextCandidate.exists()){
                return baseName+suffix+File.separatorChar+extensionString;
            }
            index++;
        }
        // unreached
        return null;
    }
    
    public static String getNextAvailableName(String folder, String baseName)
    {
        return getNextAvailableName(folder, baseName, null);
    }
    /**
     * utility method to add suffix to a file name
     */
    public static String addSuffix(String filenameWithExtension, String suffix) {
           if( filenameWithExtension == null ) return null;
            int lastDotLocation  = filenameWithExtension.lastIndexOf(".");
            if (lastDotLocation==-1)
                return null;
            else
                return filenameWithExtension.substring(0, lastDotLocation)
                        +suffix
                        +filenameWithExtension.substring(lastDotLocation);

    }
}
