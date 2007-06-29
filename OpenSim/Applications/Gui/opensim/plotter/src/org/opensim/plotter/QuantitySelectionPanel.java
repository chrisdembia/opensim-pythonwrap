package org.opensim.plotter;

import java.util.regex.Pattern;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Storage;



// Class for "Single" quantity selection.
class QuantitySelectionPanel extends JPanel
{
   private final JPlotterQuantitySelector jPlotterQuantitySelectorSingle;

   String[] selected;
   boolean isDomain;
   public QuantitySelectionPanel(JPlotterQuantitySelector jPlotterQuantitySelectorSingle, PlotterSourceInterface source, String filterRegex, boolean isDomain)
   {
      this.jPlotterQuantitySelectorSingle = jPlotterQuantitySelectorSingle;
      this.isDomain=isDomain;
      Storage nextStorage = source.getStorage();
      ArrayStr columnLabels = nextStorage.getColumnLabels();
      int numEntries = columnLabels.getSize();
      // make a JList embedded in a ScrollPane and add entries to it
      //final JPopupMenu p = new JPopupMenu();
      DefaultListModel listModel = new DefaultListModel();
      int k = 0;
      for (int j = 0; j < columnLabels.getSize(); j++){
         final String columnName = columnLabels.getitem(j);
         if (Pattern.matches(filterRegex, columnName)){
              listModel.add(k, columnName);
              k++;
         }
      }
      final JList list = new JList(listModel);
      if (this.jPlotterQuantitySelectorSingle.isDomain)
         list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
      else
         list.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
      
      list.addListSelectionListener(new ListSelectionListener() {
         public void valueChanged(ListSelectionEvent e) { 
            Object obj = e.getSource();
            JList lsm = (JList)e.getSource();   // Documentation says it's ListSlectionModel!'

            int firstIndex = e.getFirstIndex();
            int lastIndex = e.getLastIndex();
            boolean isAdjusting = e.getValueIsAdjusting(); 
            if (lsm.isSelectionEmpty()) {
                  selected=null;
            } else {
               // Find out which indexes are selected.
               int[] allSelected = lsm.getSelectedIndices();
               selected = new String[allSelected.length];
               for (int i = 0; i < allSelected.length; i++) {
                  selected[i] = (String) lsm.getModel().getElementAt(allSelected[i]);
               }
            }
         }
        });   // SelectionListener
      list.setVisibleRowCount(10);
      final JScrollPane ext = new JScrollPane(list);
      this.add(ext);
   }

   public String[] getSelected() {
      if (selected != null && selected.length >0){
         return selected;
      }
      return null;
   }
}