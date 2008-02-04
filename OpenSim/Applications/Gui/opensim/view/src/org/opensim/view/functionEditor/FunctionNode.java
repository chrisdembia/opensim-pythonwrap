/*
 * FunctionNode.java
 *
 * Created on February 1, 2008 at 2:10 PM
 */

package org.opensim.view.functionEditor;

/**
 *
 * @author Peter Loan
 */
public class FunctionNode {
   FunctionNode(int series, int node) {
      this.series = series;
      this.node = node;
   }
   public int series;
   public int node;
}

