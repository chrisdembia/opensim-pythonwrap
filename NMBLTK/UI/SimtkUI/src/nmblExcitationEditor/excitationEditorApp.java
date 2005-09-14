package nmblExcitationEditor;

import javax.swing.*;
import java.io.*;
import java.util.*;
import java.awt.*;
import simtkModel.*;

public class excitationEditorApp {
  JFrame frame;
  static { // Workaround lightweight/heavyweight mixing of Swing and awt
    JPopupMenu.setDefaultLightWeightPopupEnabled(false);

    // Initialize C++ components
    System.loadLibrary("xerces-c_2_4_0");
    System.loadLibrary("rdTools");
    System.loadLibrary("rdSimulation");
    System.loadLibrary("suCFSQP");
    System.loadLibrary("rdSQP");
    System.loadLibrary("suAnalyses");
    System.loadLibrary("rdModelDll");
    System.loadLibrary("suS26Gui");
    simtksuS26Pkg.suS26.RegisterTypes();

  }
  //Construct the application
 public excitationEditorApp() {

   javax.swing.SwingUtilities.invokeLater(new Runnable() {
       public void run() {
           createAndShowGUI();
       }
   });
 }

 public void createAndShowGUI()
 {
   frame = new ExcitationEditorFrame();
   //Validate frames that have preset sizes
   //Pack frames that have useful preferred size info, e.g. from their layout

     frame.pack();
   //Center the window
   Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
   Dimension frameSize = frame.getSize();
   if (frameSize.height > screenSize.height) {
     frameSize.height = screenSize.height;
   }
   if (frameSize.width > screenSize.width) {
     frameSize.width = screenSize.width;
   }
   frame.setLocation( (screenSize.width - frameSize.width) / 2,
                     (screenSize.height - frameSize.height) / 2);
   frame.setVisible(true);
 }

 //Main method
 public static void main(String[] args) {
   try {
     UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
   }
   catch (Exception e) {
     e.printStackTrace();
   }
   new excitationEditorApp();
 }

}
