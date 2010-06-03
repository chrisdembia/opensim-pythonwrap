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
package org.opensim.view;

import java.io.File;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import javax.swing.SwingUtilities;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.awt.StatusDisplayer;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.logger.OpenSimLogger;
import org.opensim.modeling.Model;
import org.opensim.utils.ErrorDialog;
import org.opensim.utils.FileUtils;
import org.opensim.view.base.ExecOpenSimProcess;
import org.opensim.view.pub.OpenSimDB;

public class FileOpenOsimModelAction extends CallableSystemAction {
    
    protected String fileName;
    
    public void performAction() {
        // TODO implement action body
        // Browse for model file
        String fileName = FileUtils.getInstance().browseForFilename(FileUtils.OpenSimModelFileFilter);
        if (fileName != null){
            ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Loading model file "+fileName+"...");
            try {
                progressHandle.start();
                loadModel(fileName);
                progressHandle.finish();
                StatusDisplayer.getDefault().setStatusText("");
            } catch (IOException ex) {
                progressHandle.finish();
                if (ex.getMessage().startsWith("OldVersionException")) {
                   Object userAnswer = DialogDisplayer.getDefault().notify(
                      new NotifyDescriptor.Confirmation("File "+fileName+" is from an early version of OpenSim, do you want to update it to current version",NotifyDescriptor.YES_NO_OPTION));
                   if(userAnswer==NotifyDescriptor.NO_OPTION) return;

                   File f = new File(fileName);
                   File modelDir = f.getParentFile();
                   String newOsimFileName = FileUtils.addSuffix(fileName, "_v18");
                   String command = "migrate15to18.exe \"" + fileName + "\"" + " \"" + newOsimFileName + "\"";
                   OpenSimLogger.logMessage("Executing ["+command+"]", 0);
                   boolean success = ExecOpenSimProcess.execute(command, null, modelDir );
                   // if file was not generated warn and point to message area
                   File testExists = new File(newOsimFileName);
                   if (!testExists.exists()){
                      DialogDisplayer.getDefault().notify(
                         new NotifyDescriptor.Message("Error updating model file. Please check Message window for details."));
                      success=false;
                   }

                   if (success){
                       try {
                          // Display original model
                          ((FileOpenOsimModelAction) FileOpenOsimModelAction.findObject(
                             (Class)Class.forName("org.opensim.view.FileOpenOsimModelAction"))).loadModel(newOsimFileName);
                       } catch (ClassNotFoundException exc) {
                          exc.printStackTrace();
                       } catch (IOException exc) {
                          DialogDisplayer.getDefault().notify(
                             new NotifyDescriptor.Message("Error opening migrated model file "+newOsimFileName+". Please check Message window for details."));
                       }
                   }
                } else  {
                   ErrorDialog.displayIOExceptionDialog("OpenSim Model Loading Error",
                      "Could not construct a model from "+fileName+".", ex);
                }
            }    
        }
    }

     /**
     * A wrapper around loadModel that handles a Model rather than a filename
     * setup was invoked already on the model
     */
    public boolean loadModel(final Model aModel) throws IOException {
        return loadModel(aModel , false);
    }
    
    public boolean loadModel(final Model aModel, boolean loadInForground) throws IOException {
        boolean retValue = false;
        /*boolean isOk = aModel.builtOK();
        if (!isOk){
            OpenSimLogger.logMessage("Failed to construct model from file "+fileName+"\n", OpenSimLogger.ERROR);
            return retValue;            
        }*/
        if (OpenSimDB.getInstance().hasModel(aModel)){   // If model is already loaded, complain and return.
            OpenSimLogger.logMessage("Model is already loaded\n", OpenSimLogger.ERROR);
            return retValue;            
           
        }
        // Make the window
        if (loadInForground){
            OpenSimDB.getInstance().addModel(aModel);
            return true;
        }
        else 
            SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                    try {
                        OpenSimDB.getInstance().addModel(aModel);
                    } catch (IOException ex) {
                        DialogDisplayer.getDefault().notify(new NotifyDescriptor.Message(ex.getMessage()));
                    }
            }});
        retValue = true;
        return retValue;        
    }
    /**
     * This is the function that does the real work of loading a model file into the GUI
     * @param fileName is the absolute path to the file to be used.
     * @returns true on success else failure
     */
      public boolean loadModel(final String fileName) throws IOException {
         return loadModel(fileName, false);
         
     }
     public boolean loadModel(final String fileName, boolean loadInForground) throws IOException {
        boolean retValue = false;
        Model aModel=null;
        aModel= new Model(fileName);
        if (aModel == null){
             OpenSimLogger.logMessage("Failed to construct model from file "+fileName+"\n", OpenSimLogger.ERROR);
            return retValue;
        }
        ///aModel.initSystem();        // Call 1 to initSystem is it needed?

        // Check if the model uses a SimmKinematicsEngine. If it does,
        // ask the user if he wants to migrate it to a SimbodyEngine.
        // If yes, also check to see if any inertial properties are zero.
        /*
        AbstractDynamicsEngine oldEngine = aModel.getDynamicsEngine();
        SimmKinematicsEngine simmKE = SimmKinematicsEngine.safeDownCast(oldEngine);
        if (simmKE != null) {
           Object userAnswer = DialogDisplayer.getDefault().notify(
              new NotifyDescriptor.Confirmation("The model " + aModel.getName() + " uses a SimmKinematicsEngine, which has been deprecated."
                   + " Also, it cannot be used in dynamic simulations." +
                   " Do you want to convert it to a SimbodyEngine?",
                   NotifyDescriptor.YES_NO_CANCEL_OPTION));
           if (userAnswer == NotifyDescriptor.CANCEL_OPTION)
              return false;
           if (userAnswer == NotifyDescriptor.YES_OPTION) {
               if (aModel.getDynamicsEngine().getBodySet().get("ground")==null){
                   DialogDisplayer.getDefault().notify(
              new NotifyDescriptor.Message("The model " + aModel.getName() + " has no segment with name ground."
                   + " Please rename your base segment to 'ground' and retry."));
                   return false;
               }
              String backupFilename = FileUtils.addSuffix(fileName, "_save");
              aModel.copy().print(backupFilename); 
              OpenSimLogger.logMessage("Backing up model to file "+
                      backupFilename+"\n", OpenSimLogger.INFO);

              AbstractDynamicsEngine newEngine = org.opensim.modeling.opensimModel.makeSimbodyEngine(aModel, simmKE);
              aModel.replaceEngine(newEngine);
              // Now check for zero mass.
              if (hasZeroMasses(aModel) == true) {
                 DialogDisplayer.getDefault().notify(
                    new NotifyDescriptor.Message("The model " + aModel.getName() + " contains one or more bodies with zero mass or inertia." +
                         " This may prevent dynamic simulations from running properly." +
                         " Please use the Property Viewer to check the inertial properties of the bodies before running dynamic simulations.",
                       NotifyDescriptor.WARNING_MESSAGE));
              }
              aModel.copy().print(fileName);  //So user is not prompted again
           }
        }
*/
        return loadModel(aModel, loadInForground);
    }
/*
    // Check the model to see if any of its bodies have zero mass or inertia.
    private boolean hasZeroMasses(Model aModel) {
       AbstractDynamicsEngine engine = aModel.getDynamicsEngine();
       BodySet bodies = engine.getBodySet();
       Body groundBody = engine.getGroundBody();
       double[] inertia = new double[9];
       for (int i=0; i<bodies.getSize(); i++) {
          Body body = bodies.get(i);
          if (Body.getCPtr(body) != Body.getCPtr(groundBody)) {
             if (body.getMass() <= 0.0)
                return true;
             body.getInertia(inertia);
             if (inertia[0] <= 0.0 || inertia[4] <= 0.0 || inertia[8] <= 0.0)
                return true;
          }
       }
 
       return false;
    }
*/
    public String getName() {
        return NbBundle.getMessage(FileOpenOsimModelAction.class, "CTL_OpenOsimModel");
    }
    
    protected String iconResource() {
        return null;
    }
    
    public HelpCtx getHelpCtx() {
        return new HelpCtx(FileOpenOsimModelAction.class);
    }
    
    protected boolean asynchronous() {
        return true;
    }
    /**
     * Bean pattern to support serialization
     */
    public String getFileName()
    {
        return fileName;
    }
    
    public void setFileName(String filename)
    {
        fileName=filename;
    }
    
    public void writeExternal(ObjectOutput out) throws IOException {
       //SerializationHelper.getCommandEncoder().writeObject(this);
       //SerializationHelper.getCommandEncoder().flush();
    }

    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        
    }

    void openModelFile(String string) throws IOException {
        loadModel(string);
    }

}
