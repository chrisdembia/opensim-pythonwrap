package org.opensim.view.editors;
import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.NumberFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.border.BevelBorder;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;
import javax.swing.tree.TreePath;
import org.opensim.modeling.OpenSimObject;




/**
 * Assembles the UI. The UI consists of a JTreeTable and a status label.
 * As nodes are loaded by the FileSystemModel2, in a background thread,
 * the status label updates as well as the renderer to draw the node that
 * is being loaded differently.
 *
 * Based on example by Scott Violet, SUN Micro
 */
public class ObjectPropertyViewerPanel extends JPanel {

    /** Model for the JTreeTable. */
    protected OpenSimObjectModel    model;
    /** Used to represent the model. */
    protected JTreeTable         treeTable;
    /** Row the is being reloaded. */
    protected int                reloadRow;
    /** TreePath being reloaded. */
    protected TreePath           reloadPath;
    /** A counter increment as the Timer fies and the same path is
     * being reloaded. */
    protected int                reloadCounter;
    /** Timer used to update reload state. */
    protected Timer              timer;
    /** Used to indicate status. */
    protected JLabel             statusLabel;
    /** Path created with. */
    protected OpenSimObject             object;
    /** Allow in place editing */
    protected boolean             editMode;

    final String[] toolTipStr = {"Property name in xml file", "Current property value", "Description"};


    public ObjectPropertyViewerPanel(OpenSimObject aObject, boolean allowModification) {
        this.object = aObject;
        editMode = allowModification;
        if (object == null)
            return;

        model = createModel(aObject, editMode);
        treeTable = createTreeTable();
        // Create column model and assign renderer to show tooltip
        ColumnHeaderRenderer renderer = new ColumnHeaderRenderer();
        TableColumnModel cmodel = treeTable.getColumnModel();
        int n = toolTipStr.length;
        for (int i=0;i<n;i++) {
          cmodel.getColumn(i).setHeaderRenderer(renderer);
        }

        // Create status bar
        statusLabel = createStatusLabel();
        this.add(new JScrollPane(treeTable));
        //NoStatusLabelForNow this.add(statusLabel, BorderLayout.SOUTH);

        reloadRow = -1;
        reload(model.getRoot(), editMode);
    }

    /**
     * Creates and return a JLabel that is used to indicate the status
     * of loading.
     */
    protected JLabel createStatusLabel() {
        JLabel         retLabel = new JLabel("MyStatusLabel");

        retLabel.setHorizontalAlignment(JLabel.RIGHT);
        retLabel.setBorder(new BevelBorder(BevelBorder.LOWERED));
        return retLabel;
    }

    /**
     * Creates and returns the instanceof JTreeTable that will be used.
     * This also creates, but does not start, the Timer that is used to
     * update the display as files are loaded.
     */
    protected JTreeTable createTreeTable() {
        JTreeTable       treeTable = new JTreeTable(model);

        treeTable.getColumnModel().getColumn(1).setCellRenderer
                                   (new IndicatorRenderer());

        Reloader rl = new Reloader();

        timer = new Timer(700, rl);
        timer.setRepeats(true);
        treeTable.getTree().addTreeExpansionListener(rl);
        return treeTable;
    }

    /**
     * Creates the OpenSimObjectModel that will be used.
     */
    protected OpenSimObjectModel createModel(OpenSimObject object, boolean editable) {
        return new OpenSimObjectModel(object, editable);
    }


    /**
     * Invoked to reload the children of a particular node. This will
     * also restart the timer.
     */
    protected void reload(Object node) {
        model.reloadChildren(node);
        if (!timer.isRunning()) {
            timer.start();
        }
    }

    /**
     * Invoked to reload the children of a particular node. This will
     * also restart the timer.
     */
    protected void reload(Object node, boolean editable) {
        model.reloadChildren(node);
        if (!timer.isRunning()) {
            timer.start();
        }
    }
    /**
     * Updates the status label based on reloadRow.
     */
    protected void updateStatusLabel() {
        if (reloadPath != null) {
            if ((reloadCounter % 4) < 2) {
                statusLabel.setForeground(Color.red);
            }
            else {
                statusLabel.setForeground(Color.blue);
            }
        }
        else if (!model.isReloading()) {
            statusLabel.setForeground(Color.black);
        }
    }


    // Handler for column header painting
    class ColumnHeaderRenderer extends JLabel implements TableCellRenderer {
      public Component getTableCellRendererComponent(JTable table, Object value,
                     boolean isSelected, boolean hasFocus, int row, int column) {
        setToolTipText(toolTipStr[column]);
         setText((value ==null) ? "" : value.toString());
         setBorder(UIManager.getBorder("TableHeader.cellBorder"));
         return this;
      }

    }
    /**
     * Reloader is the ActionListener used in the Timer. In response to
     * the timer updating it will reset the reloadRow/reloadPath and
     * generate the necessary event so that the display will update. It
     * also implements the TreeExpansionListener so that if the tree is
     * altered while loading the reloadRow is updated accordingly.
     */
    class Reloader implements ActionListener, TreeExpansionListener {
        public void actionPerformed(ActionEvent ae) {
            if (!model.isReloading()) {
                // No longer loading.
                timer.stop();
                if (reloadRow != -1) {
                    generateChangeEvent(reloadRow);
                }
                reloadRow = -1;
                reloadPath = null;
            }
            else {
                // Still loading, see if paths changed.
                TreePath       newPath = model.getPathLoading();

                if (newPath == null) {
                    // Hmm... Will usually indicate the reload thread
                    // completed between time we asked if reloading.
                    if (reloadRow != -1) {
                        generateChangeEvent(reloadRow);
                    }
                    reloadRow = -1;
                    reloadPath = null;
                }
                else {
                    // Ok, valid path, see if matches last path.
                    int        newRow = treeTable.getTree().getRowForPath
                                                  (newPath);

                    if (newPath.equals(reloadPath)) {
                        reloadCounter = (reloadCounter + 1) % 8;
                        if (newRow != reloadRow) {
                            int             lastRow = reloadRow;

                            reloadRow = newRow;
                            generateChangeEvent(lastRow);
                        }
                        generateChangeEvent(reloadRow);
                    }
                    else {
                        int          lastRow = reloadRow;

                        reloadCounter = 0;
                        reloadRow = newRow;
                        reloadPath = newPath;
                        if (lastRow != reloadRow) {
                            generateChangeEvent(lastRow);
                        }
                        generateChangeEvent(reloadRow);
                    }
                }
            }
            updateStatusLabel();
        }

        /**
         * Generates and update event for the specified row. FileSystemModel2
         * could do this, but it would not know when the row has changed
         * as a result of expanding/collapsing nodes in the tree.
         */
        protected void generateChangeEvent(int row) {
            if (row != -1) {
                AbstractTableModel     tModel = (AbstractTableModel)treeTable.
                                                 getModel();

                tModel.fireTableChanged(new TableModelEvent
                                       (tModel, row, row, 1));
            }
        }

        //
        // TreeExpansionListener
        //

        /**
         * Invoked when the tree has expanded.
         */
        public void treeExpanded(TreeExpansionEvent te) {
            updateRow();
        }

        /**
         * Invoked when the tree has collapsed.
         */
        public void treeCollapsed(TreeExpansionEvent te) {
            updateRow();
        }

        /**
         * Updates the reloadRow and path, this does not genernate a
         * change event.
         */
        protected void updateRow() {
            reloadPath = model.getPathLoading();

            if (reloadPath != null) {
                reloadRow = treeTable.getTree().getRowForPath(reloadPath);
            }
        }
    }


    /**
     * A renderer that will give an indicator when a cell is being reloaded.
     */
    class IndicatorRenderer extends DefaultTableCellRenderer {
        /** Makes sure the number of displayed in an internationalized
         * manner. */
        protected NumberFormat       formatter;
        /** Row that is currently being painted. */
        protected int                lastRow;


        IndicatorRenderer() {
            setHorizontalAlignment(JLabel.LEFT);
            formatter = NumberFormat.getInstance();
        }

        /**
         * Invoked as part of DefaultTableCellRenderers implemention. Sets
         * the text of the label.
         */
        public void setValue(Object value) {
            setText((value == null) ? "---" : value.toString());
        }

        /**
         * Returns this.
         */
        public Component getTableCellRendererComponent(JTable table,
                            Object value, boolean isSelected, boolean hasFocus,
                            int row, int column) {
            super.getTableCellRendererComponent(table, value, isSelected,
                                                hasFocus, row, column);
            lastRow = row;
            return this;
        }

        /**
         * If the row being painted is also being reloaded this will draw
         * a little indicator.
         */
        public void paint(Graphics g) {
            if (lastRow == reloadRow) {
                int       width = getWidth();
                int       height = getHeight();

                g.setColor(getBackground());
                g.fillRect(0, 0, width, height);
                g.setColor(getForeground());

                int       diameter = Math.min(width, height);

                if (reloadCounter < 5) {
                    g.fillArc((width - diameter) / 2, (height - diameter) / 2,
                              diameter, diameter, 90, -(reloadCounter * 90));
                }
                else {
                    g.fillArc((width - diameter) / 2, (height - diameter) / 2,
                              diameter, diameter, 90,
                              (4 - reloadCounter % 4) * 90);
                }
            }
            else {
                super.paint(g);
            }
        }
    }
}
