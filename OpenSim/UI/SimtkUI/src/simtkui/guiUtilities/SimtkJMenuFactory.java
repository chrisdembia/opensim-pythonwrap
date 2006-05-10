package simtkui.guiUtilities;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.JMenu;
import javax.swing.JMenuBar;

import simtkCommands.SimtkCommand;

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
 * Menus need to register with this class SimtkJMenuRegitery so that plugins can
 * access them and add to them. This class keeps a map between menus (assumed
 * top level/one per the whole Gui) and associated classes.
 */
public final class SimtkJMenuFactory {
  static private Hashtable _menuNames2Menus = new Hashtable();
  static private Hashtable _classNames2Menus = new Hashtable();
  static private Hashtable _topMenus = new Hashtable();
   static private JMenuBar _topMenuBar;

  public SimtkJMenuFactory() {
    _menuNames2Menus.clear();
    _classNames2Menus.clear();
    _topMenus.clear();
  }

  public static JMenuBar createTopMenuBar(){
    _topMenuBar = new JMenuBar();
    return _topMenuBar;
  }

  public static JMenuBar getTopMenuBar(){
    return _topMenuBar;
  }
  /**
   * createMenu: Creates and registers a menu with the Menu Factory
   *
   * @param menuName String
   * @return SimtkJMenu
   */
  public static SimtkJMenu createMenu(String menuName){
    SimtkJMenu newMenu = new SimtkJMenu(menuName);
    _menuNames2Menus.put(menuName, newMenu);
    return newMenu;
  }

  /**
   * getMenu retrieves menu object registered to a name
   *
   * @param menuName String
   * @return SimtkJMenu
   */
  public static SimtkJMenu getMenu(String menuName){
    return (SimtkJMenu) _menuNames2Menus.get(menuName);
  }

  /**
   * createTopMenu
   *
   * @param string String
   * @return SimtkJMenu
   */
  public static SimtkJMenu createTopMenu(String string) {
    return null;
  }
  public static boolean registerActionWithClass(String className, SimtkCommand command)
  {
    if (_classNames2Menus.containsKey(className)){
      // A custom menu already exists
      Vector classActionVector = (Vector) _classNames2Menus.get(className);
      // Check using "contains" fails since different instances of same command have different identities
      Iterator cmdIterator = classActionVector.iterator();
      boolean found = false;
      String newCmdName = command.getCommandName();
      while (cmdIterator.hasNext() && !found) {
        SimtkCommand cmd = (SimtkCommand) cmdIterator.next();
        found = cmd.getCommandName().equals(newCmdName);
      }
      if (!found){
        // If action already there don't add it again
        classActionVector.add(command);
      }
    }
    else {
      // Create a new vector of commands
      Vector classActionVector = new Vector(3);
      classActionVector.addElement(command);
      _classNames2Menus.put(className, classActionVector);
    }
    return (true);
  }
  public static Vector getRegisteredActions(String className)
  {
    Vector registeredCommands = new Vector();
    String currentClassName = className;
    try {
      while (currentClassName != "java.lang.Object"){
        Object regMenus = _classNames2Menus.get(currentClassName);
        if (regMenus != null)
          registeredCommands.addAll( (Vector) regMenus);
        Class dynaclass = Class.forName(currentClassName);
        String parentClassName = dynaclass.getSuperclass().getName();
        currentClassName = parentClassName;
      }
    }
    catch (ClassNotFoundException ex) {
    }
    return registeredCommands;
  }

  /**
   * addTopMenu
   *
   * @param jMenuFile JMenu
   */
  public static void addTopMenu(JMenu aJMenu) {
    _topMenus.put(aJMenu.getText(), aJMenu);
    getTopMenuBar().add(aJMenu);
    getTopMenuBar().updateUI();
  }

  public static JMenu getTopMenu(String aMenuName)
  {
    if (_topMenus.containsKey(aMenuName)){
     return  (JMenu) _topMenus.get((Object)aMenuName);
    }
    return null;
  }

  public static void removeTopMenu(String aMenuName)
  {
    _topMenus.remove((Object) aMenuName);
  }
}
