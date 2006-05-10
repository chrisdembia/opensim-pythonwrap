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
 * Interface to be implemented by classes that need to validate names using
 * SimDlgGetName class
 */
public abstract interface SimtkValidateName {
  // Possible error messages
  public static final int NAME_IS_OK = 0;
  public static final int NAME_ALREADY_IN_USE = 1;
  public static final int NAME_HAS_ILLEGAL_CHARACTERS = 2;
  public static final int NAME_IS_RESERVED = 3;

  abstract int validateName(String nameToValidate);

}
