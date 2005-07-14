package simtkui;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Toolkit;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.MissingResourceException;
import java.util.Properties;
import java.util.ResourceBundle;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JDesktopPane;
import javax.swing.JLabel;
import javax.swing.JPopupMenu;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;

/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */

public class SimtkApp {
  boolean packFrame = false;
  static Component _topFrame = null;
  static JTextArea _messageArea = null;
  static JTextArea _logArea = null;
  static JDesktopPane _modelDesktopPane = null;
  static SimtkMainFrame frame;

  static JLabel _statusBar = null;
  private static Image _appImage = null;
  private static Icon _appIcon = null;
  static final String lineSeparator = System.getProperty("line.separator");
  public static final boolean _debug = true;

  /**
   * user preferences as specified by properties
   */
  static Properties _props;
  static Properties defaultProperties;
  String[] defaultPropNames={"ApplicationTitle",
  							 "Application.Menus.Help.Label",
  							 "Application.Menus.Test.Show",
							 "Application.Directories.Persistent"};
  String[] defaultPropValues={"Nmbl Application",
  							  "Help",
							  "True",
							  "True"};
  // Resource bundle for internationalized and accessible text
   private static ResourceBundle bundle = null;

  // enums for message types
  public static final int MESSAGE_INFO = 0;
  public static final int MESSAGE_DEBUG = 1;
  public static final int MESSAGE_LOG = 2;
  public static final int MESSAGE_WARNING = 3;
  public static final int MESSAGE_ERROR = 4;

  static { // Workaround lightweight/heavyweight mixing of Swing and awt
    JPopupMenu.setDefaultLightWeightPopupEnabled(false);

    // Initialize C++ components
    System.loadLibrary("rdModelDll");

  }

  //Construct the application
  public SimtkApp() {

    InputStream strm = null;
    try {
      _props = new Properties(createDefaultProperties());
      strm = new FileInputStream("user.properties");
      _props.load(strm);
      strm.close();
    }
    catch (FileNotFoundException ex) {
    }
    catch (IOException ex1) {
    }
    finally {
    	String startDirectory =_props.getProperty("Application.StartDirectory");
    	if (startDirectory == null)
    		startDirectory = System.getProperty("user.dir");
      _props.setProperty("Application.CurrentDirectory", startDirectory);
    }
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
        public void run() {
            createAndShowGUI();
        }
    });
  }

  public void createAndShowGUI()
  {
    frame = new SimtkMainFrame();
    //Validate frames that have preset sizes
    //Pack frames that have useful preferred size info, e.g. from their layout
    if (packFrame) {
      frame.pack();
    }
    else {
      frame.validate();
    }
    //Center the window
    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    Dimension frameSize = frame.getSize();
    if (frameSize.height > screenSize.height) {
      frameSize.height = screenSize.height;
    }
    if (frameSize.width > screenSize.width) {
      frameSize.width = screenSize.width;
    }
    frame.setLocation( (screenSize.width - frameSize.width) / 2,
                      (screenSize.height - frameSize.height) / 2);
    frame.setVisible(true);
  }

  //Main method
  public static void main(String[] args) {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    new SimtkApp();
  }

  /**
   * setTopComponent: Sets the parent component. This is needed as some
   * commannds require a parent component (e.g. plotting commands will need parent window or those that
   * bring up a file chooser)
   *
   * @param topFrame Component
   */
  public static void setTopComponent(Component topFrame) {
    _topFrame = topFrame;
  }

  public static Component getTopComponent() {
    return _topFrame;
  }

  public static void setMessageArea(JTextArea messageArea) {
    _messageArea = messageArea;
  }

  public static void setLogArea(JTextArea logArea) {
    _logArea = logArea;
  }

  /**
   * displayMessage is a common entry point for all displayxxxMessage functions
   * so that control over what messages to display is centralized
   *
   * @param msg String
   * @param errorLevel int
   */
  static private void displayMessage(String msg, int errorLevel) {
    switch (errorLevel) {
      case MESSAGE_DEBUG:
      case MESSAGE_LOG: {
        _logArea.append(msg);
        return;
      }
      case MESSAGE_INFO:
      case MESSAGE_WARNING:
      case MESSAGE_ERROR:
      default:
        break;
    }
    _messageArea.append(msg+ lineSeparator);
  }

  /**
   * displayInfoMessage: Displays an info message in the message window
   *
   * @param msg String
   */
  static public void displayInfoMessage(String msg) {
    displayMessage(msg, MESSAGE_INFO);
  }

  /**
   * displayInfoMessage: Displays a Debug message in the message window. Should be used for
   * writing debugging messages that shouldn't show up in production code
   *
   * @param msg String
   */
  static public void displayDebugMessage(String msg) {
    displayMessage(msg, MESSAGE_DEBUG);
  }

  /**
   * displayLogMessage: Displays a Log message in the message window. Should be used for
   * echo'ing messages that will also show in the log file.
   *
   * @param msg String
   */
  static public void displayLogMessage(String msg) {
    displayMessage(msg, MESSAGE_LOG);
  }

  static public void displayWarningMessage(String msg) {
    displayMessage(msg, MESSAGE_WARNING);
  }

  static public void displayErrorMessage(String msg) {
    displayMessage(msg, MESSAGE_ERROR);
  }

  static public void setModelDesktopPane(JDesktopPane mPane) {
    _modelDesktopPane = mPane;
  }

  static public JDesktopPane getModelDesktopPane() {
    return _modelDesktopPane;
  }

  /**
   * setStatusBar
   *
   * @param statusBar JLabel
   */
  public static void setStatusBar(JLabel statusBar) {
    _statusBar = statusBar;
  }

  public static JLabel getStatusBar() {
    return _statusBar;
  }

  /**
   * getAppImage: Lazy creation of icon to be associated with application
   *
   * @return Image
   */
  public static Image getAppImage() {
    if (_appImage == null) {
      java.net.URL imgURL = SimtkApp.class.getResource("nmbltk.gif");
      if (imgURL != null) {
        _appImage = new ImageIcon(imgURL).getImage();
      }
      else
        _appImage = null;
    }
    return _appImage;
  }

  /**
   * getAppIcon:  Lazy creation of icon to be associated with application
   * Method is static so that we don't create these over and over
   * @return Icon
   */
  public static Icon getAppIcon() {
    getAppImage();
    if (_appImage != null)
      _appIcon = new ImageIcon(_appImage);

    return _appIcon;
  }

  public static JTabbedPane getExtensionPane() {
    return frame.getExtensionPane();
  }
  /**
    * This method returns a string from the app's resource bundle.
    */
   public static String getString(String key) {
       String value = null;
       try {
           value = getProperty(key);
       } catch (MissingResourceException e) {
           System.out.println("java.util.MissingResourceException: Couldn't find value for: " + key);
       }
       if(value == null) {
           value = "Could not find resource: " + key + "  ";
       }
       return value;
   }


   /**
    * Returns the resource bundle associated with this demo. Used
    * to get accessable and internationalized strings.
    */
   public static ResourceBundle getResourceBundle() {
       if(bundle == null) {
           bundle = ResourceBundle.getBundle("simtkui.SimtkApp");
       }
       return bundle;
   }

   /**
    * Returns the value for the specified property name
    */
   public static String getProperty(String aPropertyName) {
     return _props.getProperty(aPropertyName);
   }

   /**
     * Set value for corresponding property name/key
     */
   public static void setProperty(String key, String value) {
    _props.put(key, value);
   }

   public Properties createDefaultProperties()
   {
   	Properties defaults = new Properties();
   	for (int i=0; i < defaultPropNames.length; i++)
   		defaults.setProperty(defaultPropNames[i], defaultPropValues[i]);
   	return defaults;
   }
 }
