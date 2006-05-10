package simtkui.guiUtilities;

import java.io.File;

public class GenericFileFilter extends javax.swing.filechooser.FileFilter {

  private String _extension;
  private String _desc;

  public GenericFileFilter(String extention, String desc) {
      super();
      this._extension = new String(extention);
      this._desc = new String(desc);
  }

    public boolean accept(File f) {
      return (f.isDirectory() || f.getName().endsWith(_extension));
    }

    public String getDescription() {
      return (_desc);
    }

}

