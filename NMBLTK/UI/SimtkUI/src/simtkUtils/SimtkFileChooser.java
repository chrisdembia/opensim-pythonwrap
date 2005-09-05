package simtkUtils;

import java.io.File;

import javax.swing.JFileChooser;

import simtkui.SimtkApp;
import simtkui.guiUtilities.GenericFileFilter;

public class SimtkFileChooser {

  private SimtkFileChooser() {
  }

  public static String getFile(String title, String description, String extension)
  {
    // Show filechooser to browse for directory, file to open
    JFileChooser jFileChooser1 = new JFileChooser(System.getProperty("user.dir"));
    jFileChooser1.setDialogTitle(title);
     if (SimtkApp.getProperty("Application.Directories.Persistent").equalsIgnoreCase("True")){
      jFileChooser1.setCurrentDirectory(new File(SimtkApp.getProperty("Application.CurrentDirectory")));
    }
    GenericFileFilter filter = new GenericFileFilter(description, extension);
    jFileChooser1.setFileFilter(filter);
    jFileChooser1.setVisible(true);
    if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) !=
        JFileChooser.APPROVE_OPTION)
      return null;
     SimtkApp.setProperty("Application.CurrentDirectory", jFileChooser1.getSelectedFile().getParent());
     System.setProperty("user.dir", jFileChooser1.getSelectedFile().getParent());
    return jFileChooser1.getSelectedFile().getAbsolutePath();
  }
}
