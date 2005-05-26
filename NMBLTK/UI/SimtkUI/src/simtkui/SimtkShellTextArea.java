package simtkui;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.BoxLayout;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;

import simtkCommands.CommandFactoryException;
import simtkCommands.CommandFormatter;
import simtkCommands.ExecutionManager;
import simtkCommands.SimtkCommand;
/** Execute commands in a subprocess and display them in a JTextArea.

<p>Loosely based on Example1.java from
http://java.sun.com/products/jfc/tsc/articles/threads/threads2.html
<p>See also
http://developer.java.sun.com/developer/qow/archive/135/index.jsp
and
http://jw.itworld.com/javaworld/jw-12-2000/jw-1229-traps.html
and
ptolmy.ShellTextArea
 */
public class SimtkShellTextArea
    extends JTextArea {

  static private String PROMPT=">>";
  // Cursor, showing where last prompt or result ended.
  private int _promptCursor = PROMPT.length();

  // The command input
  private StringBuffer _commandBuffer = new StringBuffer();
    /** Create the JTextArea, progress bar, status text field and
     *  optionally Start, Cancel and Clear buttons.
     *
     *  @param name A String containing the name to label the JTextArea
     *  with.
     */
  public SimtkShellTextArea() {
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        setText(PROMPT);
        this.addKeyListener(new KeyAdapter(){
          public void keyTyped (KeyEvent keyEvent) {
              switch (keyEvent.getKeyCode()) {
              case KeyEvent.VK_UNDEFINED:
                  if (keyEvent.getKeyChar() == '\b') {
                      if (SimtkShellTextArea.this.getCaretPosition() == _promptCursor) {
                          keyEvent.consume(); // don't backspace over prompt!
                      }
                  }
                  break;

              case KeyEvent.VK_BACK_SPACE:
                  if (SimtkShellTextArea.this.getCaretPosition() == _promptCursor) {
                      keyEvent.consume(); // don't backspace over prompt!
                  }
                  break;
              default:
              }
          }

          public void keyReleased (KeyEvent keyEvent) {
              switch (keyEvent.getKeyCode()) {
              case KeyEvent.VK_BACK_SPACE:
                  if (SimtkShellTextArea.this.getCaretPosition() == _promptCursor) {
                      keyEvent.consume(); // don't backspace over prompt!
                  }
                  break;
              default:
              }
          }

          public void keyPressed (KeyEvent keyEvent) {
              if (!SimtkShellTextArea.this.isEditable()) {
                  Toolkit.getDefaultToolkit().beep();
                  return;
              }
              // Process keys
              switch (keyEvent.getKeyCode()) {
              case KeyEvent.VK_ENTER:
                  keyEvent.consume();
                  SimtkShellTextArea.this.evalCommand();
                  SimtkShellTextArea.this.appendJTextArea("\n"+PROMPT);
                  break;
              case KeyEvent.VK_BACK_SPACE:
                  if (SimtkShellTextArea.this.getCaretPosition() <= _promptCursor) {
                      keyEvent.consume(); // don't backspace over prompt!
                  }
                  break;
              case KeyEvent.VK_LEFT:
                  if (SimtkShellTextArea.this.getCaretPosition() == _promptCursor) {
                      keyEvent.consume();
                  }
                  break;
              default:
                       // Otherwise we got a regular character.
                      // Don't consume it, and TextArea will
                      // take care of displaying it.
              }
          }
    });
    }

    private void evalCommand()
    {
      String newtext = getText().substring(_promptCursor);
      _promptCursor += newtext.length();
      if (_commandBuffer.length() > 0) {
        _commandBuffer.append("\n");
      }
      _commandBuffer.append(newtext);
      String command = _commandBuffer.toString();
      if (command.lastIndexOf(PROMPT) != -1)
        command = command.substring(command.lastIndexOf(PROMPT)+PROMPT.length());
      SimtkCommand nextCommand = null;
      try {
        nextCommand  = CommandFormatter.parseCommand(command);
        ExecutionManager.enQueueCommand(nextCommand);
      }
      catch (CommandFactoryException ex) {
        SimtkApp.displayErrorMessage("Command " + " could not be found.. Ignored");
      }
    }
    ///////////////////////////////////////////////////////////////////
    ////                         public methods                    ////

    /** Append the text message to the JTextArea and include a trailing
     *  newline.
     */
    public void appendJTextArea(final String text) {
        Runnable doAppendJTextArea = new Runnable() {
                public void run() {
                    append(text + '\n');
                    setCaretPosition(getText().length());
                }
            };
        SwingUtilities.invokeLater(doAppendJTextArea);
    }

}

