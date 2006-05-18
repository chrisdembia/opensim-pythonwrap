package simtkCommands;

import simtkCommands.*;
import simtkView.*;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import opensimModel.VisibleObject;
import simtkView.SimtkVisibilityControlDlg;

public class SimtkObjectVisibilityCommand extends SimtkModelObjectCommand{
  public SimtkObjectVisibilityCommand() {
    super();
    putValue(Action.NAME, "Color & Effects");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Modify object vis properties");
    putValue(Action.LONG_DESCRIPTION, "Modify vis properties of model object");
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    VisibleObject visObject = (VisibleObject) getObject();
    SimtkMdlInternalFrame frame = SimtkViewDB.getFrameForModel(getModel());
    Vector actors = frame.getActorsForVisibleObject(visObject);
    SimtkVisibilityControlDlg visDialog = new SimtkVisibilityControlDlg(actors,
        frame.getRenderWindow());
    visDialog.setSize(new Dimension(200, 200));
    visDialog.center();
    visDialog.setVisible(true);
    visDialog.setModal(true);
    return true;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkObjectVisibilityCmd";
  }
}
