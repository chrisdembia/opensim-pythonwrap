package simtkCommands;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import simtkui.SimtkApp;

abstract public class SimtkExternalCommand extends SimtkCommand {
  public SimtkExternalCommand() {
    super();
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    try {
      Runtime rt = Runtime.getRuntime();

      Process process = rt.exec("");

      InputStreamReader reader =
          new InputStreamReader(process.getInputStream());

      BufferedReader buf_reader =
          new BufferedReader(reader);

      String line;
      while ( (line = buf_reader.readLine()) != null)
        SimtkApp.displayInfoMessage(line);

    }
    catch (IOException e) {
      SimtkApp.displayWarningMessage(String.valueOf(e));
    }
    return true;
  }

  /**
   * isInteractive tells whether the command will be executed as is or if user
   * will be queried from params
   *
   * @return boolean
   */
  abstract boolean isInteractive();

}
