package simtkui;

import javax.swing.*;

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
 * This class is the base class for all Frames that we'll be generating for
 * SimtkUI. Having this class serves many purposes as we can force UI components
 * of plugins to extend this class and also it allows us to provide common
 * functionality and look and feel issues (e.g. icon on top-left, resizing and
 * close-options).
 *
 * The main drawback of this mechanism is that the GUI-designers will not understand or allow operation on derived classes.
 * The workaround is to design UI in a mode where frames inherit from JFrame and run in a different mode where frames inherit
 * from SimFrame.
 */
public class SimFrame extends JFrame{
  public SimFrame(String Title) {
    super("Simtk Dlg:" + Title);
  }
}
