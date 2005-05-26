package simtkUtils;

import java.awt.Dimension;
import java.awt.Frame;
import java.awt.HeadlessException;
import java.awt.Toolkit;

import javax.swing.JDialog;

import simtkui.SimtkApp;
/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 *
 * Wrapper class around JDialog to provide common look and file, and possibly some
 * trailing support functionality (reading contents from file/string).
 */

public class JSimtkDialog extends JDialog {

  public JSimtkDialog(Frame owner) throws HeadlessException {
    super(owner, false);
  }

  public JSimtkDialog() throws HeadlessException {
    super((Frame)SimtkApp.getTopComponent());
  }

  public void center()
  {
    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    Dimension frameSize = getSize();
    if (frameSize.height > screenSize.height) {
      frameSize.height = screenSize.height;
    }
    if (frameSize.width > screenSize.width) {
      frameSize.width = screenSize.width;
    }
    setLocation( (screenSize.width - frameSize.width) / 2,
                (screenSize.height - frameSize.height) / 2);

  }
}
