/*
 *
 * PlotterSourceInterface
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

import java.util.Vector;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman. A class respresenting a Source of data for plotting. This is either a file
 * in which case all columns in the file are available for selection or an Analysis/Model
 */
public interface PlotterSourceInterface {
   
   public String[] getAllQuantities();
   
   public Vector<String> getSelectedQuantities();
   
   public boolean[] getSelectionStatus();
   
   public void clearSelectionStatus();

   public boolean[] filterByRegularExprssion(String regex);
   
   public boolean[] toggleItemSelection(String item);
   
   public String getDisplayName();

   public Storage getStorage();
   
   public boolean isStorageLive();
   
   public void setStorageLive(boolean b);

   public double getDefaultMin(String domainName);
   
   public double getDefaultMax(String domainName);

}
