package org.opensim.swingui;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JButton;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.TableColumnModel;

// NOTE: Apparently even using this listener I can't get JButton actions to activate -- i.e. if you
// create a JButton using an AbstractAction, typically pressing that button would activate that action,
// but if you put the button in a table and use this listener, that doesn't seem to work despite the fact
// that this listener forwards mouse events to the button...   I think the reason is that the JButton's
// position on the screen is not really defined since the table's cell renderer stamps the same button
// in multiple places...  So the button's "pressed" state never gets properly updated.
public class JTableButtonMouseListener implements MouseListener {

  private JTable table;

  private void forwardEventToButton(MouseEvent e) {
    TableColumnModel columnModel = table.getColumnModel();
    int column = columnModel.getColumnIndexAtX(e.getX());
    int row    = e.getY() / table.getRowHeight();
    Object value;
    JButton button;

    if(row >= table.getRowCount() || row < 0 || column >= table.getColumnCount() || column < 0)
      return;

    value = table.getValueAt(row, column);

    if(!(value instanceof JButton)) return;

    button = (JButton)value;

    MouseEvent buttonEvent = (MouseEvent)SwingUtilities.convertMouseEvent(table, e, button);
    button.dispatchEvent(buttonEvent);
    // This is necessary so that when a button is pressed and released
    // it gets rendered properly.  Otherwise, the button may still appear
    // pressed down when it has been released.
    table.repaint();
  }

  public JTableButtonMouseListener(JTable table) { this.table = table; }

  public void mouseClicked(MouseEvent e) { forwardEventToButton(e); }
  public void mouseEntered(MouseEvent e) { forwardEventToButton(e); }
  public void mouseExited(MouseEvent e) { forwardEventToButton(e); }
  public void mousePressed(MouseEvent e) { forwardEventToButton(e); }
  public void mouseReleased(MouseEvent e) { forwardEventToButton(e); }
}
