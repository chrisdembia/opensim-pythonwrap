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
import java.net.URI;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.filesystems.FileObject;
import org.openide.filesystems.FileUtil;
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
     */
    static FileUtils instance=null;

    // Some predefined filters
    public static FileFilter OpenSimModelFileFilter = getFileFilter(".osim", "OpenSim model");
    
    public static String getNextAvailableName(String folder, String baseName) {
        File baseFile = new File(baseName);
        if (baseFile.isAbsolute()){ // user specified a full path. Ignore passed in folder
            folder = baseFile.getParent();
        }
        else
            baseName = folder+baseName;
        // Here folder and baseName are consistent for a file and a parent directory
        File parentDir = new File(folder);
        // Handle extension
        String stripExtension = baseName.substring(0, baseName.lastIndexOf('.'));
        if (stripExtension.contains("_"))
            stripExtension = stripExtension.substring(0, baseName.lastIndexOf('_'));
        String extensionString = baseName.substring(baseName.lastIndexOf('.')); // includes .
        // Cycle thru and check if the file exists, return first available
        boolean found = false;
        int index=1;
        while(!found){
            String suffix = "_"+String.valueOf(index);
            File nextCandidate = new File(stripExtension+suffix+extensionString);
            if (!nextCandidate.exists()){
                return stripExtension+suffix+extensionString;
            }
            index++;
        }
        // unreached
        return null;
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
        if(extensions==null || desc==null) return null;
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

    // If promptIfReplacing==true then it prompts user if they are trying to replacing an existing file.  
    // If currentFilename!=null, and the user chooses that file, then the prompt is skipped, since it is assumed they're simply saving over their currently loaded copy.
    public String browseForFilenameToSave(FileFilter filter, boolean promptIfReplacing, String currentFilename)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        final JFileChooser dlog = new JFileChooser(defaultDir);
        if(filter!=null) dlog.setFileFilter(filter);
        
        String outFilename=null;
        JFrame topFrame = TheApp.getAppFrame();
        for (;;) {
           int result = dlog.showSaveDialog(topFrame);
           if (result == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null)
                outFilename = dlog.getSelectedFile().getAbsolutePath();
           if(outFilename!=null && promptIfReplacing && (new File(outFilename)).exists() && (currentFilename==null || !currentFilename.equals(outFilename))) {
              // Attempting to overwrite a file other than currentFilename
              Object answer = DialogDisplayer.getDefault().notify(new NotifyDescriptor.Confirmation("Replace file "+outFilename+"?","Replace file?",NotifyDescriptor.YES_NO_OPTION));
              if(answer==NotifyDescriptor.YES_OPTION) break;
           } else break;
       }
       if(outFilename != null) Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
       return outFilename;
    }
    public String browseForFilenameToSave(String extensions, String description, boolean promptIfReplacing, String currentFilename)
    {
       return browseForFilenameToSave(FileUtils.getFileFilter(extensions, description), promptIfReplacing, currentFilename);
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
    public String browseForFilename(FileFilter filter, boolean isRequired2Exist)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        final JFileChooser dlog = new JFileChooser(defaultDir);
        if(filter!=null) dlog.setFileFilter(filter);
        
        String outFilename=null;
        JFrame topFrame = TheApp.getAppFrame();
        for (;;) {
           int result = dlog.showOpenDialog(topFrame);
           if (result == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null)
                outFilename= dlog.getSelectedFile().getAbsolutePath();
           /** 
            * If isRequired2Exist flag is passed in as true we need to make sure the file really exists
            */
           if (isRequired2Exist && outFilename!= null && !(new File(outFilename)).exists())
              DialogDisplayer.getDefault().notify(
                      new NotifyDescriptor.Message("Selected file "+outFilename+" does not exist."));
           else break;
       }
       if(outFilename != null) Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
       return outFilename;
    }
    public String browseForFilename(String extensions, String description, boolean isRequired2Exist)
    {
       return browseForFilename(FileUtils.getFileFilter(extensions, description), isRequired2Exist);
    }
    /**
     * browseForFilename is a hlper function used to browse for files with specified 
     * extensions and desciption. see browseForFilename(String , String , boolean )
     * for details.
     */
    public String browseForFilename(String extensions, String description)
    {
        return browseForFilename(extensions, description, true);
    }
    
    /**
     * getInstance: gets the singlton instance of the FileUtils class
     */
     public static FileUtils getInstance()
    {
        if (instance==null)
            instance = new FileUtils();
        
        return instance;
    }
    /**
     * makePathRelative converts the second parameter (file) to be relative
     * to baseDir. If this is not possible it returns null. The caller
     * would need to use the absolute path then.
     *
     * Both file and baseDir, baseDir is assumed to be a Dir
     *
     */
    public String makePathRelative(File baseDir, File file)
    {
        String relative = null;
        if (baseDir.isDirectory()){
            if (baseDir.equals(file))
                relative = ".";
            else {
                StringBuffer b = new StringBuffer();
                File base = baseDir;
                String filePath = file.getAbsolutePath();
                while(!filePath.startsWith(slashify(base.getAbsolutePath()))){
                    base = base.getParentFile();
                    if (base == null)
                        return null;
                    b.append("../");
                }
                URI u = base.toURI().relativize(file.toURI());
                b.append(u.getPath());
                if (b.charAt(b.length() -1)=='/'){
                    b.setLength(b.length() -1);
                }
                relative = b.toString();
            }            
        }
        return relative;
    }
    
    public static String slashify(String path){
        if (path.endsWith(File.separator))
            return path;
        else
            return path + File.separatorChar;
    }
}
