package simtkView;

import java.awt.event.ActionEvent;
import java.util.HashMap;

import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.ExecutionManager;
import simtkCommands.SimtkCommand;
import opensimModel.VisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author not attributable
 * @version 1.0
 * Currently unused but intended to encapsulate all the visibility menus so that
 * the same code is excercised either from the Modeltree UI or from picking on
 * the gfx window.
 */
public class SimtkColorMenu
    extends JMenu {
  private final JMenu _visibilityControlMenu = new JMenu("Colors");
  private final String availableVisProperties[] = {
      "Surface",
      "Ambient",
      "Diffuse",
      "Specular"
  };
  private final String correspondingCommands[] = {
      "SimtkVisColorSrfCmd",
      "SimtkVisColorAmbientCmd",
      "SimtkVisGouraudShadedCmd",
      "SimtkVisBoundingBoxCmd",
      "SimtkVisNoneCmd",
      "SimtkVisToggleNormalsCmd"
  };
  private VisibleObject _selectedObject=null;
  private String _mdlName=null;

  public SimtkColorMenu(String menuName, String mdlName, VisibleObject selectedObject)
  {
    super(menuName);
    _mdlName = mdlName;
    _selectedObject = selectedObject;
    for (int i = 0; i < availableVisProperties.length; i++) {
      JMenuItem nextMenuItem = new JMenuItem(new ChangeVisibility(availableVisProperties[i]));
      add(nextMenuItem);
    }
  }
  /**
   * Inner class for Visibility control.
   */
  private class ChangeVisibility extends AbstractAction {

    ChangeVisibility(String StyleName) {
      super(StyleName);
    }

    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      for(int i=0; i < availableVisProperties.length; i++){
        if (e.getActionCommand()==availableVisProperties[i]){
          if (_selectedObject != null){
            // Build a command that will change property and fire event to update views
            SimtkCommand changeDisplayCommand = null;
            try {
              changeDisplayCommand = CommandFactory.getCommand(
                  correspondingCommands[i]);
              HashMap params = new HashMap(4);
              params.put("ModelName", _mdlName);
              params.put("Object", _selectedObject);

              changeDisplayCommand.setCommandParams(params);
              ExecutionManager.enQueueCommand(changeDisplayCommand);
            }
            catch (CommandFactoryException ex) {
            }

          }
          break;
        }
      }

    }
  }
}
