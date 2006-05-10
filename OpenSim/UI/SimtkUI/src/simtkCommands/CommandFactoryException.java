package simtkCommands;

import simtkUtils.SimtkException;

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
 * Internal CommandFactory exceptions due to incorrect
 * initialization of command manager or trying to use commands that were not
 * properly integrated into the system.
 */
public class CommandFactoryException extends SimtkException {
  /**
   * Constructs a <code>CommandFactoryException</code> with no detail message.
   */
  public CommandFactoryException() {
      super(null);  // Disallow initCause
  }

  /**
   * Constructs a <code>CommandFactoryException</code> with the
   * specified detail message.
   *
   * @param   s   the detail message.
   */
  public CommandFactoryException(String s) {
      super(s, null);  //  Disallow initCause
  }

  /**
   * Constructs a <code>CommandFactoryException</code> with the
   * specified detail message and optional exception that was
   * raised while loading the class.
   *
   * @param s the detail message
   * @param ex the exception that was raised while loading the class
   */
  public CommandFactoryException(String s, Throwable ex) {
      super(s, ex);  //  Disallow initCause
  }

}
