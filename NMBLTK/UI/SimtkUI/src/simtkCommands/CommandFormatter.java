package simtkCommands;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * Class responsible for formatting the writing of commands to log file and for
 * parse commands from a log file. This's a utility class with all static methods
 */
final public class CommandFormatter {

  static public String COMMAND_PREFIX="Command"; //Prefix to use when logging ui commands
  static public String COMMAND_ARG_BEGIN="["; //Delimiters for command params in log file
  static public String COMMAND_ARG_END="]";
  static public String QUOTE="'";

  static public String lineSeparator = System.getProperty("line.separator");
  /**
   * formatCommand is the method responsible for formatting a command to be
   * written to a log file
   *
   * @param cmd SimtkCommand
   * @return String
   */
  public static String formatCommand(SimtkCommand cmd)
  {
    String logLine = COMMAND_PREFIX + " " + cmd.getCommandName() + COMMAND_ARG_BEGIN;
    for (Iterator i = cmd._cmdParams.entrySet().iterator(); i.hasNext(); ) {
      Map.Entry e = (Map.Entry) i.next();
      String parmValue = e.getValue().toString();
      if (parmValue.indexOf(" ")!=-1){
        parmValue = QUOTE+parmValue+QUOTE;
      }
      logLine += (" " + e.getKey().toString() + "=" + parmValue);
    }
    logLine += (COMMAND_ARG_END + lineSeparator);

    return logLine;
  }

  /**
   * parseCommand is the reverse method to formatCommand. It's responsible for
   * reading a command from a commandLine and parsing it to generate a
   * SimtkCommand. Right now the assumption is that the line format is:
   * Command <commandName> [{<parmName>=<parmValue>}*]
   * With no spaces between parmName, equal sign and parmValue. This can be
   * relaxed later by making changes only to this class.
   *
   * @param commandLine String
   * @throws CommandFactoryException
   * @return SimtkCommand
   */
  public static SimtkCommand parseCommand(String commandLine) throws CommandFactoryException
  {
    String commandName = commandLine.substring(COMMAND_PREFIX.length(),
                                               commandLine.indexOf(
        COMMAND_ARG_BEGIN));
    commandName = commandName.trim(); // remove leadin/trailing spaces
    // Get the command (throw exception if not found)
    SimtkCommand retCommand = CommandFactory.getCommand(commandName);

    // Set up the hashmap for parameters
    HashMap commandParms = new HashMap(4);
    int openParenIndex = commandLine.indexOf(COMMAND_ARG_BEGIN);
    int closeParenIndex = commandLine.indexOf(COMMAND_ARG_END);
    if (closeParenIndex > openParenIndex + 1) {
      String paramString = commandLine.substring(openParenIndex + 1,
                                                 closeParenIndex);
      // Remove padding
      paramString = paramString.trim();
      while (paramString.length() != 0) {
        // Get a parmName=parmValue string by finding delimiting space
        int nextSpace = paramString.indexOf(" ");
        // Account for quoted parm values that may contain spaces
        boolean hasQuotes = false;
        if (nextSpace!= -1){
          String parmNameValueString = paramString.substring(0, nextSpace);
          // If value is Quoted it's assumed to have spaces, prase until next QUOTE
          int quoteIndex = parmNameValueString.indexOf(QUOTE);
          if (quoteIndex != -1) {
            int endQuoteIndex = paramString.indexOf(QUOTE, quoteIndex + 1);
            if (endQuoteIndex != -1) {
              nextSpace = endQuoteIndex + 1;
              hasQuotes = true;
            }
          }
        }
        int equalSignIndex=-1;
        String parmName;
        String parmValue;
        if (nextSpace == -1) {
          equalSignIndex = paramString.indexOf("=");
          parmName= paramString.substring(0, equalSignIndex);
          parmValue = paramString.substring(equalSignIndex+1);
          if (hasQuotes){
            commandParms.put(parmName, parmValue.substring(1, parmValue.length()-1));
          }
          else
            commandParms.put(parmName, parmValue);
          break;
        }
        String nextParam = paramString.substring(0, nextSpace);
        equalSignIndex = nextParam.indexOf("=");
        parmName= nextParam.substring(0, equalSignIndex);
        parmValue = nextParam.substring(equalSignIndex+1);
        if (hasQuotes){
          commandParms.put(parmName, parmValue.substring(1, parmValue.length()-1));
        }
        else
          commandParms.put(parmName, parmValue);

        paramString = paramString.substring(nextSpace + 1);
        paramString = paramString.trim();
      }

    }
    retCommand.setCommandParams(commandParms);
    return retCommand;
  }
}
