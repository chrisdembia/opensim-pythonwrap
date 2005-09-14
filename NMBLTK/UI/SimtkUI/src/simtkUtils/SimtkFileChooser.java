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
    JFileChooser jFileChooser1 = null;

    try {
      jFileChooser1 = createJFileChooser();
    }
    catch (Exception ex) {
      return null;
    }
    jFileChooser1 = new JFileChooser(System.getProperty("user.dir"));

    jFileChooser1.setDialogTitle(title);
    GenericFileFilter filter = new GenericFileFilter(description, extension);
    jFileChooser1.setFileFilter(filter);
    jFileChooser1.setVisible(true);
    if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) !=
        JFileChooser.APPROVE_OPTION)
      return null;
     System.setProperty("user.dir", jFileChooser1.getSelectedFile().getParent());
    return jFileChooser1.getSelectedFile().getAbsolutePath();
  }
   private static final int MAX_JFILECHOOSER_ATTEMPTS = 5;

   public static JFileChooser createJFileChooser() throws Exception {

     JFileChooser fileChooser = null;
     int attempts = 0;

     while (fileChooser == null) {
       try {
         fileChooser = new JFileChooser();
       }
       catch (NullPointerException e) {
         if (attempts < MAX_JFILECHOOSER_ATTEMPTS) {
           attempts++;

           /*
            * Wait a while for what it's worth
            */
           try {
             Thread.sleep(10);
           }
           catch (InterruptedException e2) {
           }
         }
         else {
           System.out.println(
               "Too many NullPointerExceptions instantiating JFileChooser.Given up...");
               throw new Exception("Unable to instantiate aJFileChooser object");
            }
         }
       }
       return fileChooser;
     }

}
