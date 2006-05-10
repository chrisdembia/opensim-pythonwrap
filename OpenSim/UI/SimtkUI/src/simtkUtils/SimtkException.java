package simtkUtils;

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
 * Base class or internal Simtk exceptions
*  Code patterned after Java's ClassNotFoundException.
 */
public class SimtkException extends Exception {
  /**
   * This field holds the exception ex if the
   * SimtkException(String s, Throwable ex) constructor was
   * used to instantiate the object
    */
  private Throwable ex;

  /**
   * Constructs a <code>SimtkException</code> with no detail message.
   */
  public SimtkException() {
      super((Throwable)null);  // Disallow initCause
  }

  /**
   * Constructs a <code>SimtkException</code> with the
   * specified detail message.
   *
   * @param   s   the detail message.
   */
  public SimtkException(String s) {
      super(s, null);  //  Disallow initCause
  }

  /**
   * Constructs a <code>SimtkException</code> with the
   * specified detail message and optional exception that was
   * raised while loading the class.
   *
   * @param s the detail message
   * @param ex the exception that was raised while loading the class
    */
  public SimtkException(String s, Throwable ex) {
      super(s, null);  //  Disallow initCause
      this.ex = ex;
  }

  /**
   * Returns the exception that was raised if an error occurred while
   * attempting to load the class. Otherwise, returns <tt>null</tt>.
   *
   * <p>This method predates the general-purpose exception chaining facility.
   * The {@link Throwable#getCause()} method is now the preferred means of
   * obtaining this information.
   *
   * @return the <code>Exception</code> that was raised while loading a class
    */
  public Throwable getException() {
      return ex;
  }

  /**
   * Returns the the cause of this exception (the exception that was raised
   * if an error occurred while attempting to load the class; otherwise
   * <tt>null</tt>).
   *
   * @return  the cause of this exception.
   */
  public Throwable getCause() {
      return ex;
  }
}
