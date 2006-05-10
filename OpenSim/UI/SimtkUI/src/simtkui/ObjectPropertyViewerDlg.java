package simtkui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.border.TitledBorder;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableModel;

import simtkModel.rdObject;

public class ObjectPropertyViewerDlg extends JDialog {
  JPanel jMainPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jBottomPanel = new JPanel();
  FlowLayout flowLayout1 = new FlowLayout();
  JButton jOkButton = new JButton();
  JList jPropertyList = new JList();
  TableModel _objectProperties = null;
  JTable jPropertyTable = null;
  TitledBorder titledBorder1;

  public ObjectPropertyViewerDlg(rdObject aObject) {
    super();
    _objectProperties = new SimtkObjectTableModel(aObject);
    jPropertyTable = new JTable(_objectProperties);
    JTableHeader header = new JTableHeader();
    header.setResizingAllowed(true);
    header.setTable(jPropertyTable);
    try {
      jbInit();
      this.pack();

    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    titledBorder1 = new TitledBorder("");
    jMainPanel.setLayout(borderLayout1);
    jBottomPanel.setLayout(flowLayout1);
    jOkButton.setToolTipText("");
    jOkButton.setActionCommand("OK");
    jOkButton.setText("OK");
    jOkButton.addActionListener(new ActionListener() {
      /**
       * actionPerformed
       *
       * @param e ActionEvent
       */
      public void actionPerformed(ActionEvent e) {

      }
    });
    this.setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    this.setModal(true);
    this.setTitle("Object Property Viewer");
    jPropertyList.setBorder(BorderFactory.createEtchedBorder());
    jPropertyList.setMinimumSize(new Dimension(0, 0));
    jPropertyList.setPreferredSize(new Dimension(0, 0));
    jPropertyList.setToolTipText("");
    jPropertyList.setFixedCellHeight(-1);
    jPropertyList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    jPropertyTable.setAlignmentX((float) 0.5);
    jPropertyTable.setAutoscrolls(true);
    jPropertyTable.setBorder(BorderFactory.createLineBorder(Color.black));
    jPropertyTable.setOpaque(false);
    jPropertyTable.setAutoCreateColumnsFromModel(true);
    jPropertyTable.setAutoResizeMode(JTable.AUTO_RESIZE_NEXT_COLUMN);
    jPropertyTable.setColumnSelectionAllowed(false);
    jPropertyTable.setRowHeight(16);
    jPropertyTable.setRowMargin(3);
    jPropertyTable.setRowSelectionAllowed(true);
    JTableHeader _header = new JTableHeader();
    _header.setVisible(true);
    jPropertyTable.setTableHeader(_header);
    this.getContentPane().add(jMainPanel, BorderLayout.CENTER);
    jMainPanel.add(jBottomPanel, BorderLayout.SOUTH);
    jBottomPanel.add(jOkButton, null);
    jMainPanel.add(jPropertyTable,  BorderLayout.CENTER);
  }
}
