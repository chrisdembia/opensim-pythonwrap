package simtkUtils;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * A Class to provide utilities related to file names and paths to isolate os
 * dependent features (path separator.. etc.)
 *
 * @author Ayman Habib
 * @version 1.0
 */
public final class FileUtils {
  static public String makeFileName(String path, String fileName)
  {
    return (path+System.getProperty("file.separator")+fileName);
  }
}
