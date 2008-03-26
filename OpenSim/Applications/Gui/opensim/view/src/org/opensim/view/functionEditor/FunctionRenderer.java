/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * FunctionRenderer.java
 *
 * Created on October 25, 2007, 10:52 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.functionEditor;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.geom.Rectangle2D;
import java.io.Serializable;
import java.util.ArrayList;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.entity.EntityCollection;
import org.jfree.chart.plot.CrosshairState;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYItemRendererState;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer.State;
import org.jfree.data.xy.XYDataset;
import org.jfree.text.TextUtilities;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.TextAnchor;
import org.jfree.util.PaintList;
import org.jfree.util.PublicCloneable;
import org.opensim.modeling.ArrayXYPoint;
import org.opensim.modeling.Function;
import org.opensim.modeling.Units;

/**
 *
 * @author Peter Loan
 */
public class FunctionRenderer extends XYLineAndShapeRendererWithHighlight
        implements XYItemRenderer,
        Cloneable,
        PublicCloneable,
        Serializable {
   
   protected ArrayList<Function> functionList = new ArrayList<Function>(0);
   
   /** For each control point in each function, the shape fill color,
    * which is either the highlight color (yellow) or the default fill
    * color.
    **/
   private ArrayList<PaintList> shapeFillPaintList = new  ArrayList<PaintList>(0);
   /** For each function, the color of the function lines and shape outlines. */
   private PaintList functionPaintList = new  PaintList();
   /** For each function, the shape fill color for unselected control points. */
   private PaintList functionDefaultFillPaintList = new  PaintList();
   /** For each function, the shape fill color for selected control points. */
   private PaintList functionHighlightFillPaintList = new  PaintList();
   
   private Units XUnits;         // units of array of X values
   private Units XDisplayUnits;  // units for displaying X values to user
   private Units YUnits;         // units of array of Y values
   private Units YDisplayUnits;  // units for displaying Y values to user
   
   /** the string to display in the lower left corner of the plot area */
   private String interiorTitle = null;
   private Font interiorTitleFont = new Font("SansSerif", Font.BOLD, 12);
   private Paint interiorTitlePaint = Color.RED;
   
   /** Creates a FunctionRenderer for a single function. */
   public FunctionRenderer(Function theFunction) {
      addFunction(theFunction);
      XUnits = new Units(Units.UnitType.simmRadians);
      XDisplayUnits = new Units(Units.UnitType.simmDegrees);
      YUnits = new Units(Units.UnitType.simmMeters);
      YDisplayUnits = new Units(Units.UnitType.simmMeters);
   }
   /**
    * Separate function for potentially adding more than one function by the Excitation editor e.g. min/max
    */
   public void addFunction(final Function theFunction) {
      functionList.add(theFunction);
      int index = functionList.size()-1;
      shapeFillPaintList.add(new PaintList());
      //functionDefaultFillPaintList.set(new PaintList());
      //functionHighlightFillPaintList.add(new PaintList());
      setFunctionPaint(index, Color.GREEN);
      functionDefaultFillPaintList.setPaint(index, Color.GREEN);
      functionHighlightFillPaintList.setPaint(index, Color.BLACK);
      for (int i=0; i<theFunction.getNumberOfPoints(); i++)
         shapeFillPaintList.get(index).setPaint(i, Color.GREEN);
   }

   /**
    * Draws the visual representation of a single data item.
    *
    * @param g2  the graphics device.
    * @param state  the renderer state.
    * @param dataArea  the area within which the data is being drawn.
    * @param info  collects information about the drawing.
    * @param plot  the plot (can be used to obtain standard color
    *              information etc).
    * @param domainAxis  the domain axis.
    * @param rangeAxis  the range axis.
    * @param dataset  the dataset.
    * @param series  the series index (zero-based).
    * @param item  the item index (zero-based).
    * @param crosshairState  crosshair information for the plot
    *                        (<code>null</code> permitted).
    * @param pass  the pass index.
    */
   public void drawItem(Graphics2D g2,
           XYItemRendererState state,
           Rectangle2D dataArea,
           PlotRenderingInfo info,
           XYPlot plot,
           ValueAxis domainAxis,
           ValueAxis rangeAxis,
           XYDataset dataset,
           int series,
           int item,
           CrosshairState crosshairState,
           int pass) {
      
      // do nothing if item is not visible
      if (!getItemVisible(series, item)) {
         return;
      }
      
      // TODO:
      // get rid of getDrawSeriesLineAsPath() -- always draw as path
      double f1 = rangeAxis.getLowerBound();
      double f2 = rangeAxis.getLowerMargin();
      // first pass draws the background (lines, for instance)
      if (isLinePass(pass)) {
         if (item == 0) {
            if (getDrawSeriesLineAsPath()) {
               State s = (State) state;
               s.seriesPath.reset();
               s.setLastPointGood(false);
            }
         }
         
         if (getItemLineVisible(series, item)) {
            if (getDrawSeriesLineAsPath()) {
               drawPrimaryLineAsPath(state, g2, plot, dataset, pass,
                       series, item, domainAxis, rangeAxis, dataArea);
            } else {
               drawPrimaryLine(state, g2, plot, dataset, pass, series,
                       item, domainAxis, rangeAxis, dataArea);
            }
         }
      }
      // second pass adds shapes where the items are ..
      else if (isItemPass(pass)) {
         
         // setup for collecting optional entity info...
         EntityCollection entities = null;
         if (info != null) {
            entities = info.getOwner().getEntityCollection();
         }
         
         drawSecondaryPass(g2, plot, dataset, pass, series, item,
                 domainAxis, dataArea, rangeAxis, crosshairState, entities);
         
         if (item == dataset.getItemCount(series) - 1)
            drawInteriorTitle(g2, plot, series, item, domainAxis, rangeAxis, dataArea, (State) state);
      }
   }
   
   /**
    * Draws the item (first pass). This method draws the lines
    * connecting the items. Instead of drawing separate lines,
    * a GeneralPath is constructed and drawn at the end of
    * the series painting.
    *
    * @param g2  the graphics device.
    * @param state  the renderer state.
    * @param plot  the plot (can be used to obtain standard color information
    *              etc).
    * @param dataset  the dataset.
    * @param pass  the pass.
    * @param series  the series index (zero-based).
    * @param item  the item index (zero-based).
    * @param domainAxis  the domain axis.
    * @param rangeAxis  the range axis.
    * @param dataArea  the area within which the data is being drawn.
    */
   protected void drawPrimaryLineAsPath(XYItemRendererState state,
           Graphics2D g2, XYPlot plot,
           XYDataset dataset,
           int pass,
           int series,
           int item,
           ValueAxis domainAxis,
           ValueAxis rangeAxis,
           Rectangle2D dataArea) {
      
      if (series >= functionList.size())
         return;
      
      RectangleEdge xAxisLocation = plot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = plot.getRangeAxisEdge();
      
      State s = (State) state;
      ArrayXYPoint xyPts = functionList.get(series).renderAsLineSegments(item);
      if (xyPts != null) {
         for (int i = 0; i < xyPts.getSize(); i++) {
            double datax = (xyPts.get(i).get_x() * XUnits.convertTo(XDisplayUnits));
            double datay = (xyPts.get(i).get_y() * YUnits.convertTo(YDisplayUnits));
            double screenx = domainAxis.valueToJava2D(datax, dataArea, xAxisLocation);
            double screeny = rangeAxis.valueToJava2D(datay, dataArea, yAxisLocation);
            if (!Double.isNaN(screenx) && !Double.isNaN(screeny)) {
               PlotOrientation orientation = plot.getOrientation();
               if (orientation == PlotOrientation.HORIZONTAL) {
                  double tmp = screenx;
                  screenx = screeny;
                  screeny = tmp;
               }
               if (i == 0 && (item == 0 || s.isLastPointGood() == false)) {
                  s.seriesPath.moveTo((float)screenx, (float)screeny);
               } else {
                  s.seriesPath.lineTo((float)screenx, (float)screeny);
               }
               s.setLastPointGood(true);
            }
         }
         functionList.get(series).deleteXYPointArray(xyPts);
      } else {
         s.setLastPointGood(false);
      }
      
      // if this is the last item, draw the path ...
      if (item == dataset.getItemCount(series) - 1) {
         drawFirstPassShape(g2, pass, series, item, s.seriesPath);
      }
   }
   
   /**
    * Draws the first pass shape.
    *
    * @param g2  the graphics device.
    * @param pass  the pass.
    * @param series  the series index.
    * @param item  the item index.
    * @param shape  the shape.
    */
   protected void drawFirstPassShape(Graphics2D g2, int pass, int series,
           int item, Shape shape) {
      g2.setStroke(getItemStroke(series, item));
      g2.setPaint(getFunctionPaint(series));
      g2.draw(shape);
   }
   
   private void drawInteriorTitle(Graphics2D g2, XYPlot plot, int series, int item, ValueAxis domainAxis,
           ValueAxis rangeAxis, Rectangle2D dataArea, State state) {
      RectangleEdge xAxisLocation = plot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = plot.getRangeAxisEdge();
      
      if (this.interiorTitle != null) {
         g2.setFont(this.interiorTitleFont);
         g2.setPaint(this.interiorTitlePaint);
         double textX = domainAxis.valueToJava2D(domainAxis.getUpperBound(), dataArea, xAxisLocation) - 5;
         double textY = rangeAxis.valueToJava2D(rangeAxis.getUpperBound(), dataArea, yAxisLocation) + 5;
         TextUtilities.drawAlignedString(this.interiorTitle, g2, (float)textX, (float)textY, TextAnchor.TOP_RIGHT);
      }
   }
   
   /**
    * Function colors
    * Each function (series) has its own color, which is used for the
    * function lines and the outlines of the node circles. The insides
    * of the circles are white for all nodes in all series. When a node
    * is selected, its fill color is yellow but its outline is still
    * the series color.
    */
   public void highlightNode(int function, int point) {
      if (function < functionList.size())
         shapeFillPaintList.get(function).setPaint(point, functionHighlightFillPaintList.getPaint(function));
   }
   
   public void unhighlightNode(int function, int point) {
      if (function < functionList.size())
         shapeFillPaintList.get(function).setPaint(point, functionDefaultFillPaintList.getPaint(function));
   }
   
   public Paint getNodePaint(int function, int point) {
      if (function < functionList.size())
         return shapeFillPaintList.get(function).getPaint(point);
      else
         return Color.BLACK;
   }
   
   // The item paint is used for the outlines of the control
   // point shapes.
   public Paint getItemPaint(int series, int item) {
      return functionPaintList.getPaint(series);
   }
   
   public Paint getItemFillPaint(int series, int item) {
      return getNodePaint(series, item);
   }
   
   public void setFunctionDefaultFillPaint(int function, Paint paint) {
      if (function < functionList.size()) {
         Paint oldPaint = functionDefaultFillPaintList.getPaint(function);
         functionDefaultFillPaintList.setPaint(function, paint);
         // Update the individual point's fill colors if they were equal to the old default color
         for (int i=0; i<functionList.get(function).getNumberOfPoints(); i++) {
            if (getNodePaint(function, i) == oldPaint)
               unhighlightNode(function, i);
         }
      }
   }
   
   public Paint getFunctionDefaultFillPaint(int function) {
      if (function < functionList.size())
         return functionDefaultFillPaintList.getPaint(function);
      else
         return Color.BLACK;
   }
   
   public void setFunctionHighlightFillPaint(int function, Paint paint) {
      if (function < functionList.size()) {
         Paint oldPaint = functionHighlightFillPaintList.getPaint(function);
         functionHighlightFillPaintList.setPaint(function, paint);
         // Update the individual point's fill colors if they were equal to the old highlight color
         for (int i=0; i<functionList.get(function).getNumberOfPoints(); i++) {
            if (getNodePaint(function, i) == oldPaint)
               highlightNode(function, i);
         }
      }
   }
   
   public Paint getFunctionHighlightFillPaint(int function) {
      if (function < functionList.size())
         return functionHighlightFillPaintList.getPaint(function);
      else
         return Color.BLACK;
   }
   
   public void setFunctionPaint(int function, Paint paint) {
      functionPaintList.setPaint(function, paint);
   }
   
   public Paint getFunctionPaint(int function) {
      if (function < functionList.size())
         return functionPaintList.getPaint(function);
      else
         return Color.BLACK;
   }
   
   public void setXUnits(Units XUnits) {
      this.XUnits = XUnits;
   }
   
   public void setXDisplayUnits(Units XDisplayUnits) {
      this.XDisplayUnits = XDisplayUnits;
   }
   
   public void setYUnits(Units YUnits) {
      this.YUnits = YUnits;
   }
   
   public void setYDisplayUnits(Units YDisplayUnits) {
      this.YDisplayUnits = YDisplayUnits;
   }
   
   public void setInteriorTitle(String title) {
      this.interiorTitle = title;
   }
   
   public String getInteriorTitle() {
      return this.interiorTitle;
   }
   
   public void setInteriorTitlePaint(Paint paint) {
      this.interiorTitlePaint = paint;
   }
   
   public void setInteriorTitleFont(Font font) {
      this.interiorTitleFont = font;
   }
   
   public ArrayList<Function> getFunctionList() {
      return functionList;
   }
}
