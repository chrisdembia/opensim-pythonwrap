/*
 * ApplicationExit.java
 *
 * Created on August 17, 2007, 1:43 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.actions;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JOptionPane;
import org.openide.LifecycleManager;
import org.opensim.utils.TheApp;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.modeling.Model;

/**
 *
 * @author Peter Loan
 */
public class ApplicationExit extends WindowAdapter
{
   // This function is called when the app's close (X) box is clicked.
   public void windowClosing(WindowEvent e)
   {
      // Do nothing, because Installer::closing() will be called next,
      // and that function needs to process the exit because it's the
      // only function called when File...Exit is chosen.
      //confirmExit();
   }

   static public void confirmExit()
   {
      // Make sure the user really wants to quit.
      Object[] options = {"Yes", "Cancel"};
      int answer = JOptionPane.showOptionDialog(null,
         "Are you sure you want to exit?",
         "OpenSim",
         JOptionPane.YES_NO_OPTION,
         JOptionPane.WARNING_MESSAGE,
         null,
         options,
         options[1]);
      if (answer == 1)
         return;

      // Close all of the models, prompting the user to save them if necessary.
      // If any of the closes returns false, that model was not closed, so abort
      // the exit.
      Object[] models = OpenSimDB.getInstance().getAllModels();
      for (int i=0; i<models.length; i++) {
         if (FileCloseAction.closeModel((Model)models[i]) == false)
            return;
      }

      // Clean up and exit.
      LifecycleManager.getDefault().exit();
      TheApp.getAppFrame().dispose();
      System.exit(0);
   }
}

