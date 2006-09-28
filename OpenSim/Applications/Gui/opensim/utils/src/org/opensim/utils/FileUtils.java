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
package org.opensim.utils;
import java.io.File;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.windows.WindowManager;

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
    public static String getNextAvailableName(String folder, String baseName, String extension) {
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
    
    public static String getNextAvailableName(String folder, String baseName) {
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
    /**
     * Extension should contain the leading . e.g. ".xml"
     */
    public static String addExtensionIfNeeded(String path, String extension) {
        if (path.endsWith("extension") || path.contains("."))
            return path;
        // just append extension
        return path+extension;
    }
        
   /**
     * Utility to create file filters to browse for files of specified "extension" with "description"
     */
    public static FileFilter getFileFilter(final String extensions, final String desc) {
        // Parse the list of extensions passed in as (*.xyz, *.abc .de) into an array[]
        Vector<String> extensionList = new Vector<String>(2);
        if (extensions.contains(",")){
            StringTokenizer tokenizer = new StringTokenizer(extensions," ,*()");
            while(tokenizer.hasMoreElements()){
                extensionList.add(tokenizer.nextToken());
            }
        }
        else
            extensionList.add(0, extensions);
        
        // Copy list into an array[] (not necessary but to make a final object to be used by inner class
        // Could be done more efficiently
        final String[] extensionsArray = new String[extensionList.size()];
        for(int i=0; i<extensionsArray.length;i++)
            extensionsArray[i] = extensionList.get(i);
        
        return  new FileFilter() {
            public boolean accept(File f) {
                boolean test = false;
                for(int i=0; i<extensionsArray.length && !test; i++){
                    test = f.isDirectory() || f.getName().toLowerCase().endsWith(extensionsArray[i]);
                 }
                return test;
            }
            
            public String getDescription() {
                return desc +" ("+extensions+")";
            }
        };
    }
    /**
     * One common place to do the following common functions:
     * 1. Browse for a file using user's "workingDirectory" as initial dir.
     * 2. get file name
     * 3. set new "workingDirectory" based on selection
     * 4. return full path name of selected file
     *
     * If the file is required and a non-existant name is entered and isRequired2Exist==true
     *    then this function returns null 
     *
     * @todo this could be improved by making our own JFileChooser container JPanel
     */
    public static String browseForFilename(String extensions, String description, boolean isRequired2Exist)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setFileFilter(FileUtils.getFileFilter(extensions, description));
        
        String outFilename=null;
        if (dlog.showOpenDialog((JFrame) WindowManager.getDefault().getMainWindow()) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
             outFilename= dlog.getSelectedFile().getAbsolutePath();
             Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
       }
        /** 
         * If isRequired2Exist flag is passed in as true we ned to make sure the file really exists
         */
       if (isRequired2Exist && outFilename!= null){
            File outfile = new File(outFilename);
            if (!outfile.exists()){
                DialogDisplayer.getDefault().notify(
                        new NotifyDescriptor.Message("Selected file "+outFilename+" does not exist."));
                // This could be done better
                return browseForFilename(extensions, description, isRequired2Exist);
            }
       }
       return outFilename;
    }
    
    public static String browseForFilename(String extensions, String description)
    {
        return browseForFilename(extensions, description, true);
    }
    
}
