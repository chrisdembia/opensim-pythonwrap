package nmblExcitationEditor;

import java.awt.*;

import javax.swing.*;
import java.awt.event.*;
import javax.swing.border.*;

public class excitationEditortHelpDialog
    extends JDialog implements ActionListener {

  JPanel panel1 = new JPanel();
  JPanel insetsPanel1 = new JPanel();
  JButton button1 = new JButton();
  ImageIcon image1 = new ImageIcon();
  BorderLayout borderLayout1 = new BorderLayout();
  Border border1;
  JEditorPane jEditorPane1 = new JEditorPane();

  public excitationEditortHelpDialog(Frame parent) {
    super(parent);
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  excitationEditortHelpDialog() {
    this(null);
  }

  //Component initialization
  private void jbInit() throws Exception  {
    image1 = new ImageIcon(simtkui.SimtkApp.class.getResource("about.png"));
    border1 = BorderFactory.createCompoundBorder(new EtchedBorder(EtchedBorder.RAISED,Color.white,new Color(151, 159, 173)),BorderFactory.createEmptyBorder(5,5,5,5));
    this.setTitle("About");
    panel1.setLayout(borderLayout1);
    button1.setText("Ok");
    button1.addActionListener(this);
    jEditorPane1.setPreferredSize(new Dimension(400, 111));
    jEditorPane1.setText("Use file/open to load controls file. \nIndividual controls show in " +
    "the tree on the left.\nUse right mouse click on tree entries to select " +
    "controls you want to edit.\nMultiple slections are possible.\nTo edit an individual control, select it " +
    "by name from the drop down at the bottom of the dialog and drag the " +
    "right mouse over the plotting window from left to right.\nRemember to save control file before exiting\n");
    this.getContentPane().add(panel1, null);
    insetsPanel1.add(button1, null);
    panel1.add(insetsPanel1, BorderLayout.SOUTH);
    panel1.add(jEditorPane1,  BorderLayout.CENTER);
    setSize(300, 300);
    setResizable(true);
  }

  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      cancel();
    }
    super.processWindowEvent(e);
  }

  //Close the dialog
  void cancel() {
    dispose();
  }

  //Close the dialog on a button event
  public void actionPerformed(ActionEvent e) {
    if (e.getSource() == button1) {
      cancel();
    }
  }
}
