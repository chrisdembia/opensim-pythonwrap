package simtkui.guiUtilities;

import javax.swing.JMenu;

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
 * Base class for all menus used by the Gui
 */
public class SimtkJMenu extends JMenu{
  /**
   * SimtkJMenu default constructor with no name
   */
  public SimtkJMenu() {
    super();
  }

  /**
   * SimtkJMenu constructor that takes menu name
   *
   * @param menuName String
   */
  public SimtkJMenu(String menuName) {
    super(menuName);
    setName(menuName);
  }

}
