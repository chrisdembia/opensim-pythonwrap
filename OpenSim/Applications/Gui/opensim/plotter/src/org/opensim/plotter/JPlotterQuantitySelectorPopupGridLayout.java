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

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JTextField;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman
 */
public class JPlotterQuantitySelectorPopupGridLayout extends JPopupMenu {
   private Storage storageToUse;
   private String columnToUse;
   private JTextField   selection;
   private double xMin, xMax;
   private boolean isDomain=false;
   private JPlotterPanel plotterFrame;
   /**
    * Creates a new instance of JPlotterQuantitySelectorPopupGridLayout
    */
   public JPlotterQuantitySelectorPopupGridLayout(JTextField target, JPlotterPanel plotterFrame, boolean isDomain) {
      this.plotterFrame = plotterFrame;
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
      ArrayList<Storage> usedStorages = plotterModel.getLoadedFileStorages();
      // Add a submenu for each loaded file
      for(int i=0; i<usedStorages.size(); i++){
         final Storage nextStorage = usedStorages.get(i);
         JMenu fileSelectionMenu = new JMenu("File:"+nextStorage.getName());
         add(fileSelectionMenu);
         
         // Now add columns of selected file
         ArrayStr columnLabels = nextStorage.getColumnLabels();
         int numEntries = columnLabels.getSize();
         int nColumns = numEntries/50+1;
         int nRows = 50;
         GridLayout menuGrid = new GridLayout(nRows,nColumns);
         fileSelectionMenu.getPopupMenu().setLayout(menuGrid);
         for (int j=0; j < columnLabels.getSize(); j++){
            final String columnName = columnLabels.getitem(j);
            JMenuItem colMenuItem = new JMenuItem(columnName);
            colMenuItem.addActionListener(new ActionListener(){
               public void actionPerformed(ActionEvent e) {
                  setStorageToUse(nextStorage);
                  setColumnToUse(columnName);
                  selection.setText(getStorageToUse().getName()+":"+columnName);
                  if (isDomain){
                     setXMin(getStorageToUse().getColumnMin(columnName));
                     setXMax(getStorageToUse().getColumnMax(columnName));
                  }
                  plotterFrame.updatePlotterFrameVisibilities();
                }});
            fileSelectionMenu.add(colMenuItem);          
         }
         
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

}
