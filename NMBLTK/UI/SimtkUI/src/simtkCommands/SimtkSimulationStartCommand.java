package simtkCommands;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Action;
import javax.swing.Timer;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkModel.rdControl;
import simtkModel.rdControlSet;
import simtkModel.rdManager;
import simtkUtils.FileUtils;
import simtkUtils.SwingWorker;
import simtkui.SimtkApp;
import simtkuiEvents.SimtkSimEnvSimulationTimeChange;
import javax.swing.*;
import simtkModel.*;

public class SimtkSimulationStartCommand
    extends SimtkCommand{
  /**
   * SimtkSimulationStartCommand. Default constructor used to add entries to command
   * table and set initial availability
   */
  public SimtkSimulationStartCommand() {
    super();
    putValue(Action.NAME, "Start");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Start Simulation");
    setEnabled(true);
   }

  /**
   * canUndo
   *
   * @return boolean
   */
  public boolean canUndo() {
    return false;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkSimulationStartCmd";
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    boolean success = true;
    // Make sure there's a model
    String simenvName = (String) _cmdParams.get("EnvName");
    final SimtkSimEnv currentEnv = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
    final rdManager mgr = currentEnv.getSimulationManager();
    // Set model again as it might have changed
    mgr.setModel(currentEnv.getModel());

    rdControlSet controlSet = mgr.getControlSet();
    // Get initial time
    int tiIndex = controlSet.getIndex("ti", 0);
    rdControl tiControl = (tiIndex==-1)?null:controlSet.get("ti");

    if (tiControl != null) {
      mgr.setInitialTime(tiControl.getControlValue(0.0));
    }
      // Get final time
    int tfIndex = controlSet.getIndex("tf", 0);
    rdControl tfControl = (tfIndex==-1)?null:controlSet.get("tf");
    if (tfControl != null) {
      mgr.setFinalTime(tfControl.getControlValue(0.01));
    }
    if (tiControl == null || tfControl ==null){
        rdControl firstControl = controlSet.get(0);
        mgr.setInitialTime(firstControl.getFirstTime());
        mgr.setFinalTime(firstControl.getLastTime());
    }
    mgr.getIntegrator().setMaximumNumberOfSteps(20000);
    mgr.getIntegrator().setMaxDT(1.0e-3);
    mgr.getIntegrator().setUseConstantDT(false);
    //mgr.getIntegrator().setDT(0.00087);
    mgr.getIntegrator().setTolerance(1.0e-5, -1.0);
    mgr.getIntegrator().setFineTolerance(5.0e-7);
    // Create Timer thread for animation
    Timer timer = new Timer(100, new ActionListener(){
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {
        SimtkDB.getInstance().updateModelDisplay(mgr.getModel());
        SimtkSimEnvSimulationTimeChange evnt = new SimtkSimEnvSimulationTimeChange(currentEnv);
        currentEnv.update(evnt);
        }
    });
    currentEnv.setAnimationTimer(timer);

    SwingWorker workerThread = new SwingWorker() {
      /**
       * construct
       *
       * @return Object
       */
      public Object construct() {
        currentEnv.removeStorage(mgr.getIntegrator().getControlStorage());
        currentEnv.removeStorage(mgr.getIntegrator().getStateStorage());
        int nAnalyses = currentEnv.getModel().getNumAnalyses();
       for (int i=0; i < nAnalyses; i++){
         rdAnalysis nextAnalysis = currentEnv.getModel().getAnalysis(i);
         String analysisName = nextAnalysis.getName();
         String analysisType = nextAnalysis.getType();
         rdArrayStorage storages = nextAnalysis.getStorageList();
         for (int j=0; j < storages.getSize(); j++){
           storages.get(j).reset(0);
           currentEnv.removeStorage(storages.get(j));
         }
       }
       currentEnv.setStatus(SimtkSimEnv.STARTED);// This triggers other gui changes thru observers
        currentEnv.getAnimationTimer().start();
        currentEnv.setProgressRange(mgr.getInitialTime(), mgr.getFinalTime());
        currentEnv.addStorage(mgr.getIntegrator().getControlStorage(), true);
        currentEnv.addStorage(mgr.getIntegrator().getStateStorage(), true);
        // Add storages from analyses
        for (int i=0; i < nAnalyses; i++){
         rdAnalysis nextAnalysis = currentEnv.getModel().getAnalysis(i);
         String analysisName = nextAnalysis.getName();
         String analysisType = nextAnalysis.getType();
         rdArrayStorage storages = nextAnalysis.getStorageList();
         for (int j=0; j < storages.getSize(); j++){
           storages.get(j).reset(0);
           currentEnv.addStorage(storages.get(j), true);
         }
       }
       mgr.integrate();
        if (currentEnv.getStoragePreferences().getPStatesStore()){
          String fullpath = FileUtils.makeFileName(currentEnv.getStoragePreferences().getStorageDirectory(),
                                                   currentEnv.getStoragePreferences().getPStatesStorageFile());
          mgr.getIntegrator().getPseudoStateStorage().print(fullpath, .01, "w");
        }
        if (currentEnv.getStoragePreferences().getStatesStore()){
          String fullpath = FileUtils.makeFileName(currentEnv.getStoragePreferences().getStorageDirectory(),
                                                   currentEnv.getStoragePreferences().getStatesStorageFile());
          mgr.getIntegrator().getStateStorage().print(fullpath, .01, "w");
        }
        if (currentEnv.getStoragePreferences().getControlsStore()){
          String fullpath = FileUtils.makeFileName(currentEnv.getStoragePreferences().getStorageDirectory(),
                                                  currentEnv.getStoragePreferences().getControlsStorageFile());
         mgr.getIntegrator().getControlStorage().print(fullpath, .01, "w");
        }
        currentEnv.setSimulationThread(null);
        currentEnv.setStatus(SimtkSimEnv.READY);
        currentEnv.getAnimationTimer().stop();

        return null;
      }
      public void finished() {
        SimtkApp.displayInfoMessage("Done running simulation");
        currentEnv.setStatus(SimtkSimEnv.READY);
     }
    };
    currentEnv.setSimulationThread(workerThread);
    workerThread.start();
    return true;
  }
  /**
   * Command can run in the background
   * @return boolean
   */
  public boolean isBackgroundCmd()
  {
    return false;
  }

  /**
   * whenAvailable override to tell the system that this command is
   * conditionally available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    String simenvName = (String) _cmdParams.get("EnvName");
    if (simenvName==null)
      return false;
   return (SimtkDB.getInstance().getSimtkSimEnv(simenvName).getStatus()==SimtkSimEnv.READY);
  }

  /**
   * isObserver is overloaded to tell the system that the command is
   * conditionally available based on system events
   *
   * @return boolean
   */
  public boolean isObserver() {
    return true;
  }

}
