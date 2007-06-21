/*
 *
 * JPlotterQuantitySelectorPopupGridLayout
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.plotter;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.regex.Pattern;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.view.SingleModelGuiElements;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman, this class is responsible for showing and arranging 
 * the set of quantities to be displayed for user selection in the plotter
 * A popup with list of Files is shown ad on user pick a dialog is shown for 
 * picking quantities.
 */
public class JPlotterQuantitySelectorPopupList extends JPopupMenu {
   private Storage storageToUse;
   private String columnToUse;
   private JTextField   selection;
   private double xMin, xMax;
   private boolean isDomain=false;
   private JPlotterPanel plotterPanel;
   public final String COLUMN_SEPARATOR=", ";
   public final String INTERVAL_SEPARATOR="-";

   /**
    * Creates a new instance of JPlotterQuantitySelectorPopupList
    */
   public JPlotterQuantitySelectorPopupList(JTextField target, JPlotterPanel plotterPanel, boolean isDomain) {
      this.plotterPanel = plotterPanel;
      this.isDomain=isDomain;
      selection=target;
      setXMin(0.0);
      setXMax(1.0);
   }
   /**
    * Update the list of menu items in the popup based on current contents of the plotterModel
    * and a flag indicating where the sources to consider are files or Analyses 
    */
   public void updateList(PlotterModel plotterModel, boolean useFileSource) {
       removeAll();
       if (useFileSource){ 
           ArrayList<PlotterSourceFile> usedFileSources = plotterModel.getLoadedFileSources();
           // Add a submenu for each loaded file
           for(int i=0; i<usedFileSources.size(); i++){
               final PlotterSourceFile source = usedFileSources.get(i);
               final Storage nextStorage = source.getStorage();
               JMenuItem selectedFileMenuItem = new JMenuItem("File:"+source.getDisplayName()+"...");
               selectedFileMenuItem.addActionListener(new ActionListener(){
                   public void actionPerformed(ActionEvent e) {
                       // Create panel then the dialog that contains it
                       QuantitySelectionPanel quantityPanel = new QuantitySelectionPanel(source,
                               plotterPanel.getQuantityFilterRegex(), isDomain);
                       DialogDescriptor dlg = new DialogDescriptor(quantityPanel,"Select Quantity");
                       dlg.setModal(true);
                       DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
                       Object userInput = dlg.getValue();
                       if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
                           String[] columnNames=quantityPanel.getSelected();
                           if (columnNames==null)
                              return;  // Nothing was selected.
                           String columnNamesDisplayString="";
                           for(int sel=0; sel<columnNames.length; sel++){
                               columnNamesDisplayString += columnNames[sel];
                               if (sel < columnNames.length-1)
                                   columnNamesDisplayString+= COLUMN_SEPARATOR;
                           }
                           selection.setText(source.getDisplayName()+":"+columnNamesDisplayString);
                       }
                       plotterPanel.updatePlotterWithSelection();
                       
                   }});
                   add(selectedFileMenuItem);
           }
       }
       else {   //Analysis source, create a list 
           // Get a dropdown of coordinate names
           Model currentModel = OpenSimDB.getInstance().getCurrentModel();
           SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(currentModel);
           String[] coordinateNames = guiElem.getCoordinateNames();
           for(int i=0; i<coordinateNames.length; i++){
               final String coordinateName = coordinateNames[i];
               JMenuItem selectedGCItem = new JMenuItem(coordinateName);
               selectedGCItem.addActionListener(new ActionListener(){
                   public void actionPerformed(ActionEvent e) {
                       selection.setText("Model:"+coordinateName);
                       plotterPanel.updatePlotterWithSelection();
                   }});
               add(selectedGCItem);
            }
           /*
           ArrayList<PlotterSourceAnalysis> usedAnalysisSources = plotterModel.getAnalysisSources();
           // Add a submenu for each loaded file
           for(int i=0; i<usedAnalysisSources.size(); i++){
               final PlotterSourceAnalysis source = usedAnalysisSources.get(i);
               final Storage nextStorage = source.getStorage();
               JMenuItem selectedFileMenuItem = new JMenuItem("Analysis:"+source.getDisplayName()+"...");
               selectedFileMenuItem.addActionListener(new ActionListener(){
                   public void actionPerformed(ActionEvent e) {
                       // Create panel then the dialog that contains it
                       QuantitySelectionPanel quantityPanel = new QuantitySelectionPanel(source,
                               plotterPanel.getQuantityFilterRegex(), isDomain);
                       DialogDescriptor dlg = new DialogDescriptor(quantityPanel,"Select Quantity");
                       dlg.setModal(true);
                       DialogDisplayer.getDefault().createDialog(dlg).setVisible(true);
                       Object userInput = dlg.getValue();
                       if (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0){
                           String[] columnNames=quantityPanel.getSelected();
                           String columnNamesDisplayString="";
                           for(int sel=0; sel<columnNames.length; sel++){
                               columnNamesDisplayString += columnNames[sel];
                               if (sel < columnNames.length-1)
                                   columnNamesDisplayString+= COLUMN_SEPARATOR;
                           }
                           selection.setText(source.getDisplayName()+":"+columnNamesDisplayString);
                       }
                       plotterPanel.updatePlotterWithSelection();
                       
                   }});
                   add(selectedFileMenuItem);
           }*/
           
       }
   }
  
   public Storage getStorageToUse() {
      return storageToUse;
   }

   public void setStorageToUse(Storage storageToUse) {
      this.storageToUse = storageToUse;
   }

   public String getColumnToUse() {
      return columnToUse;
   }

   public void setColumnToUse(String columnToUse) {
      this.columnToUse = columnToUse;
   }

   public double getXMin() {
      return xMin;
   }

   public void setXMin(double xMin) {
      this.xMin = xMin;
   }

   public double getXMax() {
      return xMax;
   }

   public void setXMax(double xMax) {
      this.xMax = xMax;
   }

   public void setLabel(String label) {
      super.setLabel(label);
   }


   // Inner class for quantity selection panel
   class QuantitySelectionPanel extends javax.swing.JPanel
   {
      String[] selected;
      boolean isDomain;
      public QuantitySelectionPanel(PlotterSourceInterface source, String filterRegex, boolean isDomain)
      {
            this.isDomain=isDomain;
            Storage nextStorage = source.getStorage();
            ArrayStr columnLabels = nextStorage.getColumnLabels();
            int numEntries = columnLabels.getSize();
            // make a JList embedded in a ScrollPane and add entries to it
            //final JPopupMenu p = new JPopupMenu();
            DefaultListModel listModel = new DefaultListModel();
            int k=0;
            for (int j=0; j < columnLabels.getSize(); j++){
               final String columnName = columnLabels.getitem(j);
               if (Pattern.matches(filterRegex, columnName)){
                    listModel.add(k, columnName);
                    k++;
               }
            }
           final JList list = new JList(listModel);
           if (JPlotterQuantitySelectorPopupList.this.isDomain)
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
                          selected[i]=(String)lsm.getModel().getElementAt(allSelected[i]);
                    }
                }
            }
        });   // SelectionListener
        list.setVisibleRowCount(10);
        final JScrollPane ext = new JScrollPane(list);
        this.add(ext);
      }

      private String[] getSelected() {
         if (selected != null && selected.length >0){
            return selected;
         }
         return null;
      }
   }
}
