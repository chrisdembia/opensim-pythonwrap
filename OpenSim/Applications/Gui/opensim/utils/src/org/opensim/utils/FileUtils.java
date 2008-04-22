/*
 *
 * FileUtils
 * Author(s): Ayman Habib
 * Copyright (c)  2005-2006, Stanford University, Ayman Habib
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.opensim.utils;
import java.awt.Component;
import java.awt.Frame;
import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.filechooser.FileFilter;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;

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
    static JFileChooser dlog = new JFileChooser();
    
    // Some predefined filters
    public static FileFilter OpenSimModelFileFilter = getFileFilter(".osim", "OpenSim model");
    public static FileFilter MotionFileFilter = getFileFilter(".mot,.sto", "Motion or storage file");
    
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
   
   public static String getExtension(String fileName) {
      int index = fileName.lastIndexOf('.');
      return (index==-1) ? null : fileName.substring(index+1);
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
        if (path.endsWith(extension) || path.contains("."))
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
        return browseForFilenameToSave(filter, promptIfReplacing, currentFilename, null);
    }
    
    public String browseForFilenameToSave(FileFilter filter, boolean promptIfReplacing, String currentFilename, Component parent)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        //final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setCurrentDirectory(new File(defaultDir));
        dlog.setName("");
        if(filter!=null) dlog.setFileFilter(filter);
        
        String outFilename=null;
        Component topWindow;
        if (parent==null)
            topWindow = TheApp.getAppFrame();
        else
            topWindow = parent;
        
        for (;;) {
           dlog.setSelectedFile(new File(currentFilename));
           int result = dlog.showSaveDialog(topWindow);
           outFilename = null;
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

    public String browseForFolder()
    {
       return browseForFolder(null);
    }
    
    public String browseForFolder(Frame parent)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        //final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setCurrentDirectory(new File(defaultDir));
        dlog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        
        String outFilename=null;
        Frame topFrame = (parent==null)?TheApp.getAppFrame():parent;
        for (;;) {
           dlog.setSelectedFile(new File(""));
           int result = dlog.showOpenDialog(topFrame);
           outFilename = null;
           if (result == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null)
                outFilename = dlog.getSelectedFile().getAbsolutePath();

           // TODO: prompt to create directory if it doesn't exist?
           break;
       }
       dlog.setFileSelectionMode(JFileChooser.FILES_ONLY);
       if(outFilename != null) Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFile().getParent());
       return outFilename;
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
    public String browseForFilename(FileFilter filter, boolean isRequired2Exist, Component parent)
    {
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        //JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setCurrentDirectory(new File(defaultDir));
        if(filter!=null) dlog.setFileFilter(filter);
        
        String outFilename=null;
        Component topWindow;
        if (parent==null)
            topWindow = TheApp.getAppFrame();
        else
            topWindow = parent;
        for (;;) {
           dlog.setSelectedFile(new File(" "));
           int result = dlog.showOpenDialog(topWindow);
           outFilename = null;
           if (result == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null)
                outFilename = dlog.getSelectedFile().getAbsolutePath();
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
    public String browseForFilename(String extensions, String description, boolean isRequired2Exist, Component parent)
    {
       return browseForFilename(FileUtils.getFileFilter(extensions, description), isRequired2Exist, parent);
    }
    public String browseForFilename(String extensions, String description, Component parent)
    {
        return browseForFilename(extensions, description, true, parent);
    }
    public String browseForFilename(FileFilter filter, Component parent)
    {
        return browseForFilename(filter, true, parent);
    }
    /**
     * A variation that assumes no parent frame (== parent is the Application window)
     */
    public String browseForFilename(String extensions, String description, boolean isRequired2Exist)
    {
       return browseForFilename(FileUtils.getFileFilter(extensions, description), isRequired2Exist, null);
    }
    public String browseForFilename(String extensions, String description)
    {
        return browseForFilename(extensions, description, true, null);
    }
    public String browseForFilename(FileFilter filter)
    {
        return browseForFilename(filter, true, null);
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
    public static String makePathRelative(String filename, String baseDirname)
    {
        if (effectivelyNull(filename)) return filename;
        return makePathRelative(new File(baseDirname), new File(filename));
    }
    
    public static String makePathRelative(File baseDir, File file)
    {
        if (!file.exists()){
            //int test=0;
            return file.getAbsolutePath();
        }
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

   // Treat null, empty string, and "Unassigned" all essentially as empty strings
   public static boolean effectivelyNull(String fileName) {
      return fileName==null || fileName.equals("") || fileName.equals("Unassigned");
   }

   public static String makePathAbsolute(String fileName, String parentDir) {
      if (effectivelyNull(fileName) || (new File(fileName)).isAbsolute()) return fileName;
      else return (new File(parentDir, fileName)).getAbsolutePath();
   }

    public String[] browseForSIMMModelFiles() {
        String extensions="*.jnt,*.msl";
        String desc="SIMM model files, one .jnt file and optional one .msl file";
        // Init dialog to use "WorkDirectory" as thought of by user
        String defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", "");
        // final JFileChooser dlog = new JFileChooser(defaultDir);
        dlog.setCurrentDirectory(new File(defaultDir));
        dlog.setMultiSelectionEnabled(true);
        dlog.setFileFilter(getFileFilter(extensions, desc));
        
        File[] outFiles=null;
        JFrame topFrame = TheApp.getAppFrame();
        for (;;) {
           dlog.setSelectedFile(new File(""));
           int result = dlog.showOpenDialog(topFrame);
           outFiles = null;
           if (result == JFileChooser.APPROVE_OPTION && dlog.getSelectedFiles() != null)
                outFiles = dlog.getSelectedFiles();
           else
              break;
           boolean allExist=true;
           String badFiles="";
           int numJntFiles=0;
           int numMslFiles=0;
           for( int i=0;i<outFiles.length;i++){
               File nextSelectedFile = outFiles[i];
               if (!nextSelectedFile.exists()){
                    try {
                        badFiles += outFiles[i].getCanonicalFile().getName()+" ";
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                   allExist = false;
               }
               else if (nextSelectedFile.getName().endsWith(".jnt"))
                       numJntFiles++;
               else if (nextSelectedFile.getName().endsWith(".msl"))
                       numMslFiles++;                      
           }
           /** 
            * If isRequired2Exist flag is passed in as true we need to make sure the file really exists
            */
           if (allExist==false)
              DialogDisplayer.getDefault().notify(
                      new NotifyDescriptor.Message("Selected file(s) "+badFiles+" do not exist."));
           else if (numJntFiles!=1)
              DialogDisplayer.getDefault().notify(
                      new NotifyDescriptor.Message("One jnt file must be selected."));
           else if (numMslFiles>1)
              DialogDisplayer.getDefault().notify(
                      new NotifyDescriptor.Message("At most one msl file can be selected."));
           else
               break;
       }
       String[] outFilenames=null;
       if(outFiles!=null) {
          outFilenames = new String[outFiles.length];
          for (int i=0; i<outFiles.length;i++){ // either one or two
              if (outFiles[i].getName().endsWith(".jnt"))
                  outFilenames[0]=outFiles[i].getAbsolutePath();
              else
                   outFilenames[1]=outFiles[i].getAbsolutePath();             
          }
          if(outFilenames.length>0) Preferences.userNodeForPackage(TheApp.class).put("WorkDirectory", dlog.getSelectedFiles()[0].getParent());
       }
       // get jnt file followed by muscle file of any into output array
        
       return outFilenames;
    }
}
