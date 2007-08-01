package org.opensim.view.editors;

import java.awt.Component;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.UIManager;
import javax.swing.table.TableCellRenderer;
import org.opensim.modeling.OpenSimObject;

/**
 * Assembles the UI (a JTreeTable).
 * Based on example by Scott Violet, SUN Micro
 */
public class ObjectPropertyViewerPanel extends JPanel {
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
        treeTable = new JTreeTable(model);

        // Create column model and assign renderer to show tooltip
        ColumnHeaderRenderer renderer = new ColumnHeaderRenderer();
        for (int i=0;i<model.getColumnCount();i++)
          treeTable.getColumnModel().getColumn(i).setHeaderRenderer(renderer);

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
