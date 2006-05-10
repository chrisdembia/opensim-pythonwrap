package simtkCommands;

import java.awt.event.ActionEvent;
import javax.swing.*;
import java.io.*;
import javax.swing.filechooser.FileFilter;
import simtkui.*;
import simtkUtils.*;
import simtkModel.rdModel;
import simtkCore.*;
import java.util.*;
import simtkui.*;
import simtkui.guiUtilities.*;

public class SimtkFileOpenJarCommand extends SimtkFileOpenCommand {
  boolean _fileNameSet;
  JFileChooser jFileChooser1;
  String _fullModelName;

  public SimtkFileOpenJarCommand() {
    _fileNameSet = false;
    putValue(Action.NAME, getCommandName());
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
    super.setCommandParams(params);
    // Expect exactly one parameter which is file name
    _fileName = (String) params.get("FileName");
    _fileNameSet = true;
  }

  /**
   * actionPerformed
   *
   * @param e ActionEvent
   */
  //public void actionPerformed(ActionEvent e) {
  //}

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkFileOpenJarCmd";
  }
  public boolean execute(){
    // For now we'll open a jar file
    jFileChooser1 = new JFileChooser();
    jFileChooser1.setDialogTitle("Select Model Jar file to open");
    GenericFileFilter filter = new GenericFileFilter("jar", "*.jar");
    jFileChooser1.setFileFilter(filter);
    jFileChooser1.setVisible(true);
    if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) != JFileChooser.APPROVE_OPTION)
      return false;
    _fileName = jFileChooser1.getSelectedFile().getAbsolutePath();
    return addModelFromJar(_fileName);
  }
  private void jbInit() throws Exception {
  }
   /**
    * addModel is the entry point for loading models and potentially other
    * creatures from jar files. It makes the following assumptions:
    * 1. Jar file xxxx_Model.jar contains the model xxxx.class file.
    *
    * @param jarFileName String
    * @return boolean
    */
   synchronized public boolean addModelFromJar(String jarFileName) {
     boolean success = true;
     /*
      * Create the jar class loader
      */
     JarClassLoader jarLoader = new JarClassLoader(jarFileName);
     String bareModelClassName = "No class";
     String classLoaderName = "";
     try {
       /* Load the class from the jar file and resolve it. */
       int indexOfModelInJarName = jarFileName.lastIndexOf("_Model");
       if (indexOfModelInJarName == -1) {
         // Wrong format of jar file name. Abort
         SimtkApp.displayErrorMessage("No class file for model was found in " +
                            jarFileName);
         success = false;
       }
       else {
         int indexOfLastDirSepInJarName = jarFileName.lastIndexOf("\\");
         if (indexOfLastDirSepInJarName == -1)
           bareModelClassName = jarFileName.substring(0, indexOfModelInJarName);
         else
           bareModelClassName = jarFileName.substring(indexOfLastDirSepInJarName +
               1, indexOfModelInJarName);
         classLoaderName= bareModelClassName+"Loader";
         // This is cheating as we're not loading the class from selected Jar file but from path
         // as evident by debugging info
         Class c = jarLoader.loadClass(classLoaderName, true);

          /*
          * Create an instance of the class.
          *
          * Note that created object's constructor-taking-no-arguments
          * will be called as part of the object's creation.
          */
         Object o = c.newInstance();

         // Add the newly created model to the central database
         success = SimtkDB.getInstance().addModel((rdModel) o, null);
       }
     }
     catch (java.lang.ClassNotFoundException e) {
       SimtkApp.displayErrorMessage("Can't find class" + classLoaderName + " in " +
                          jarFileName);
       success = false;
     }
     catch (java.lang.InstantiationException e) {
       SimtkApp.displayErrorMessage("Can't instantiate class" + classLoaderName +
                          " from " + jarFileName);
       success = false;
     }
     catch (java.lang.IllegalAccessException e) {
       SimtkApp.displayErrorMessage("Don't have permission to instantiate class" +
                          classLoaderName + " from " + jarFileName);
       success = false;
     }
     return success;
   }

}
