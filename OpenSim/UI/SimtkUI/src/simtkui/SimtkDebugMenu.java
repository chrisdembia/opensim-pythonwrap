package simtkui;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JMenuItem;

import opensimModel.Model;
import opensimModel.SWIGTYPE_p_double;
import opensimModel.OpenSimObject;
import opensimModel.VisibleObject;
import simtkui.guiUtilities.SimtkJMenu;

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
 * Intended to encapsulate all model tree originated menus so that
 * the same code is excercised either from the Modeltree UI or from picking on
 * the gfx window.
 */
public class SimtkDebugMenu
    extends SimtkJMenu {
  private final String _defaultProperties[] = {
      "MoveX",
      "MoveY",
      "MoveZ",
      "ShowTranslations",
      "ShowRotations"
  };
  private OpenSimObject _selectedObject = null;
  private String _mdlName = null;

  public SimtkDebugMenu(String menuName, String mdlName,
                        OpenSimObject selectedObject) {
    super(menuName);
    _mdlName = mdlName;
    _selectedObject = selectedObject;
    for (int i = 0; i < _defaultProperties.length; i++) {
      JMenuItem nextMenuItem = new JMenuItem(new DebugAction(i, _selectedObject));
      add(nextMenuItem);
    }
  }

  class DebugAction
      extends AbstractAction {
    private int _idx=0;
    private VisibleObject _object;
    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public DebugAction(int index, OpenSimObject obj){
      super();
      _idx = index;
      _object = (VisibleObject) obj;
      putValue(Action.NAME, _defaultProperties[_idx]);
    }

    public void actionPerformed(ActionEvent e) {
      if (e.getActionCommand()=="MoveX"){
        _object.getTransform().translateX(1.0);
      }
      else if (e.getActionCommand()=="MoveY"){
        _object.getTransform().translateY(1.0);
      }
      else if (e.getActionCommand()=="MoveZ"){
        _object.getTransform().translateZ(1.0);
      }
      else if (e.getActionCommand()=="ShowTranslations"){
        double[] jPos = new double[3];
        _object.getTransform().getPosition(jPos);
        SimtkApp.displayDebugMessage("Position = "+jPos[0]+", "+jPos[1]+", "+jPos[2]);
      }
      else if (e.getActionCommand()=="ShowRotations"){
       double[] jPos = new double[3];
       _object.getTransform().getOrientation(jPos);
       SimtkApp.displayDebugMessage("Orientation = "+jPos[0]+", "+jPos[1]+", "+jPos[2]);

      }
    }

  }
}


