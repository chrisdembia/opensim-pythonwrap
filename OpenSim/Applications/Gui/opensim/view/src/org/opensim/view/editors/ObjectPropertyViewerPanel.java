package org.opensim.view.editors;

import java.awt.Component;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.UIManager;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;
import org.opensim.modeling.OpenSimObject;
import org.opensim.swingui.JTableButtonMouseListener;
import org.opensim.swingui.JTableButtonRenderer;

class ObjectPropertyViewerTreeTable extends JTreeTable {
   private TreeTableModelAdapter adapter = null;
   private OpenSimObjectModel model = null;

   public ObjectPropertyViewerTreeTable(OpenSimObjectModel model) {
      super(model);
      this.model = model;
      this.adapter = (TreeTableModelAdapter)getModel();
   }

   public TableCellRenderer getCellRenderer(int row, int column) {
      TableColumn tableColumn = getColumnModel().getColumn(column);
      TableCellRenderer renderer = tableColumn.getCellRenderer();
      if (renderer == null) renderer = getDefaultRenderer(model.getCellClass(adapter.nodeForRow(row), convertColumnIndexToModel(column)));
      return renderer;
   }

   public TableCellEditor getCellEditor(int row, int column) {
      TableColumn tableColumn = getColumnModel().getColumn(column);
      TableCellEditor editor = tableColumn.getCellEditor();
      if (editor == null) editor = getDefaultEditor(model.getCellClass(adapter.nodeForRow(row), convertColumnIndexToModel(column)));
      return editor;
   }
}

/**
 * Assembles the UI (a JTreeTable).
 * Based on example by Scott Violet, SUN Micro
 */
public class ObjectPropertyViewerPanel extends JPanel {
    private static final int controlsColumnWidth = 16;

    protected OpenSimObjectModel model;
    protected JTreeTable         treeTable;
    protected OpenSimObject      object;
    protected boolean            editMode;

    public ObjectPropertyViewerPanel(OpenSimObject aObject, boolean allowModification) {
        this.object = aObject;
        editMode = allowModification;
        if (object == null)
            return;

        model = new OpenSimObjectModel(aObject, editMode);
        //treeTable = new JTreeTable(model);
        treeTable = new ObjectPropertyViewerTreeTable(model);

        // Create column model and assign renderer to show tooltip
        ColumnHeaderRenderer renderer = new ColumnHeaderRenderer();
        for (int i=0;i<model.getColumnCount();i++)
          treeTable.getColumnModel().getColumn(i).setHeaderRenderer(renderer);

        // Set column width for the controls column
        treeTable.getColumnModel().getColumn(1).setPreferredWidth(controlsColumnWidth);
        treeTable.getColumnModel().getColumn(1).setMinWidth(controlsColumnWidth);
        treeTable.getColumnModel().getColumn(1).setMaxWidth(controlsColumnWidth);

        // Don't allow selection (no use for it here)
        treeTable.setRowSelectionAllowed(false);

        treeTable.setDefaultRenderer(JButton.class, new JTableButtonRenderer(treeTable.getDefaultRenderer(JButton.class)));

        // To handle pressing the "controls" buttons
        treeTable.addMouseListener(new JTableButtonMouseListener(treeTable));

        this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        this.add(new JScrollPane(treeTable));

        model.reloadChildren(model.getRoot());
    }

   // Handler for column header painting
   class ColumnHeaderRenderer extends JLabel implements TableCellRenderer {
      public Component getTableCellRendererComponent(JTable table, Object value,
            boolean isSelected, boolean hasFocus, int row, int column) {
         setToolTipText(model.getColumnHeaderToolTip(column));
         setText((value ==null) ? "" : value.toString());
         setBorder(UIManager.getBorder("TableHeader.cellBorder"));
         return this;
      }
   }
}
