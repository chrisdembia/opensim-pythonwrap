/*
 * FunctionXYSeries.java
 *
 * Created on October 31, 2007, 4:44 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.functioneditor;

import java.io.Serializable;
import org.jfree.data.xy.XYDataItem;
import org.jfree.data.xy.XYSeries;

/**
 *
 * @author Peter Loan
 */
public class FunctionXYSeries extends XYSeries implements Cloneable, Serializable {
   
   /** Creates a new instance of FunctionXYSeries */
   public FunctionXYSeries(Comparable key) {
      super(key, true, true);
   }
   
   public void updateByIndex(int index, Number x, Number y) {
      XYDataItem newNode = new XYDataItem(x, y);
      data.remove(index);
      data.add(index, newNode);
      fireSeriesChanged();
   }
}
