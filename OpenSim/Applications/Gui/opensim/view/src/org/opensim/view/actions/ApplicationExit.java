/*
 * Copyright (c)  2005-2008, Stanford University
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

   static public boolean confirmExit()
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
         return false;

      // Close all of the models, prompting the user to save them if necessary.
      // If any of the closes returns false, that model was not closed, so abort
      // the exit.
      Object[] models = OpenSimDB.getInstance().getAllModels();
      for (int i=0; i<models.length; i++) {
         if (FileCloseAction.closeModel((Model)models[i]) == false)
            return false;
      }

      return true;
   }
}

