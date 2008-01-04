/*
 * FunctionPanel.java
 *
 * Created on November 15, 2007, 10:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.functioneditor;

import java.awt.AWTEvent;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.geom.Rectangle2D;
import java.text.NumberFormat;
import java.util.ArrayList;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.annotations.XYTextAnnotation;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.TextAnchor;

/**
 *
 * @author Peter Loan
 */
public class FunctionPanel extends ChartPanel
                        implements KeyListener {

   private boolean picking = false;
   private boolean dragging = false;
   /** Crosshairs are displayed while dragging points or when
    * the crosshairs checkbox is selected.
    */
   private boolean showCrosshairs = false;
   private boolean mandatoryCrosshairs = false;
   private boolean domainAxisAutoRange = true;
   private boolean rangeAxisAutoRange = true;
   int dragNode = -1;
   int dragScreenXOld = -1, dragScreenYOld = -1;
   int lastMouseX = -1, lastMouseY = -1;
   double dragDataXOld = -99.9, dragDataYOld = -99.9;
   int lastLeftButtonClickCount = 0;
   int lastLeftButtonClickNode = -1;
   int rightClickNode = -1;
   int rightClickX = -1;
   int rightClickY = -1;
   private Point boxSelectPoint = null;
   private transient Rectangle2D boxSelectRectangle = null;
   private ArrayList<Integer> oldBoxSelectNodes = null;
   private final java.awt.Color boxSelectColor = java.awt.Color.green; // to get purple select box
   private JPopupMenu addNodePopUpMenu;
   private JPopupMenu nodePopUpMenu;
   private XYTextAnnotation crosshairAnnotation = null;
   public static final String DUPLICATE_NODE_COMMAND = "DUPLICATE_NODE";
   public static final String DELETE_NODE_COMMAND = "DELETE_NODE";
   public static final String ADD_NODE_COMMAND = "ADD_NODE";

   /** Creates a new instance of FunctionPanel */
   public FunctionPanel(JFreeChart chart) {
      super(chart);
      //this.setFocusable(true);
      this.enableEvents(AWTEvent.INPUT_METHOD_EVENT_MASK);
      this.enableEvents(AWTEvent.KEY_EVENT_MASK);
      this.addKeyListener(this);
      this.nodePopUpMenu = createNodePopupMenu();
      this.addNodePopUpMenu = createAddNodePopupMenu();
      this.crosshairAnnotation = new XYTextAnnotation("", 0, 0);
      this.crosshairAnnotation.setTextAnchor(TextAnchor.BOTTOM_LEFT);
   }

   public void updateCursorLocation(MouseEvent e) {
      lastMouseX = e.getX();
      lastMouseY = e.getY();
   }

   public void mouseEntered(MouseEvent e) {
      e.getComponent().requestFocusInWindow();
      updateCursorLocation(e);
      updateCrosshairs(e.getX(), e.getY());
   }

   public void mouseExited(MouseEvent e) {
      updateCursorLocation(e);
      updateCrosshairs(-1, -1);
      super.mouseExited(e);
   }

   public void mousePressed(MouseEvent e) {
      this.requestFocusInWindow();
      updateCursorLocation(e);
      int leftClickNode = -1;
      int keyMods = e.getModifiers();
      if ((keyMods & InputEvent.BUTTON1_MASK) > 0) {
         leftClickNode = findNodeAt(e.getX(), e.getY());

         // Some code to handle double clicking on an object, but which does so in a way that the sequence
         // CTRL-Click and Click does not count as a double click.  This avoids
         // treating as double click the case where the user selects an object
         // (CTRL-Click) and quickly starts dragging (Click & Drag) 
         if (leftClickNode != -1 && picking == false) {
            if (e.getClickCount() == lastLeftButtonClickCount+1 && leftClickNode == lastLeftButtonClickNode) {
               //handleDoubleClick(leftClickNode);
               return; 
            } else {
               lastLeftButtonClickCount = e.getClickCount();
               lastLeftButtonClickNode = leftClickNode;
            } 
         } else {
            lastLeftButtonClickCount = -1;
            lastLeftButtonClickNode = -1;
         }
      }

      if ((keyMods & InputEvent.BUTTON3_MASK) > 0) {
         rightClickNode = findNodeAt(e.getX(), e.getY());
         rightClickX = e.getX();
         rightClickY = e.getY();
      } else if (picking == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         if (leftClickNode == -1) {
            // Picking mode is on, but the user clicked away from a control point.
            // So clear the selections (unless Shift is pressed) and prepare for a box select.
            if ((keyMods & InputEvent.SHIFT_MASK) <= 0)
               FunctionEditorTopComponent.findInstance().clearSelectedNodes();
            startBoxSelect(e);
         } else {
            if ((keyMods & InputEvent.SHIFT_MASK) > 0) {
               FunctionEditorTopComponent.findInstance().toggleAddSelectedNode(leftClickNode);
            } else {
               FunctionEditorTopComponent.findInstance().replaceSelectedNode(leftClickNode);
            }
         }
      } else if ((leftClickNode != -1) && FunctionEditorTopComponent.findInstance().isSelected(leftClickNode) == true) {
         XYPlot xyPlot = getChart().getXYPlot();
         dragNode = leftClickNode;
         dragScreenXOld = e.getX();
         dragScreenYOld = e.getY();
         RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
         RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
         Rectangle2D dataArea = getScreenDataArea();
         dragDataXOld = xyPlot.getDomainAxis().java2DToValue((double)e.getX(), dataArea, xAxisLocation);
         dragDataYOld = xyPlot.getRangeAxis().java2DToValue((double)e.getY(), dataArea, yAxisLocation);
         setDragging(true);
         // During dragging, the crosshairs lock onto the center of the dragNode
         double crosshairX = xyPlot.getDataset().getXValue(0, dragNode);
         double crosshairY = xyPlot.getDataset().getYValue(0, dragNode);
         double crosshairScreenX = xyPlot.getDomainAxis().valueToJava2D(crosshairX, dataArea, xAxisLocation);
         double crosshairScreenY = xyPlot.getRangeAxis().valueToJava2D(crosshairY, dataArea, yAxisLocation);
         updateCrosshairs((int)crosshairScreenX, (int)crosshairScreenY);
         picking = false;
      } else {
         super.mousePressed(e);
      }
   }

   public void mouseDragged(MouseEvent e) {
      updateCursorLocation(e);
      int keyMods = e.getModifiers();
      if (picking == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         // do nothing; you're still in picking mode
         dragScreenXOld = e.getX();
         dragScreenYOld = e.getY();
         updateCrosshairs(e.getX(), e.getY());
         doBoxSelect(e);
      } else if (getDragging() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         if (e.getX() != dragScreenXOld || e.getY() != dragScreenYOld) {
            if (dragNode != -1) {
               XYPlot xyPlot = getChart().getXYPlot();
               RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
               RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
               Rectangle2D dataArea = getScreenDataArea();
               double dragDataXNew = xyPlot.getDomainAxis().java2DToValue((double)e.getX(), dataArea, xAxisLocation);
               double dragDataYNew = xyPlot.getRangeAxis().java2DToValue((double)e.getY(), dataArea, yAxisLocation);
               if (dragDataXNew > xyPlot.getDomainAxis().getUpperBound())
                  dragDataXNew = xyPlot.getDomainAxis().getUpperBound();
               else if (dragDataXNew < xyPlot.getDomainAxis().getLowerBound())
                  dragDataXNew = xyPlot.getDomainAxis().getLowerBound();
               if (dragDataYNew > xyPlot.getRangeAxis().getUpperBound())
                  dragDataYNew = xyPlot.getRangeAxis().getUpperBound();
               else if (dragDataYNew < xyPlot.getRangeAxis().getLowerBound())
                  dragDataYNew = xyPlot.getRangeAxis().getLowerBound();
               // the amount to drag the objects is the distance between dragPtOld and dragPtNew
               double dragVector[] = new double[2];
               dragVector[0] = dragDataXNew - dragDataXOld;
               dragVector[1] = dragDataYNew - dragDataYOld;
               // drag the selected objects
               FunctionEditorTopComponent.findInstance().dragSelectedNodes(dragNode, dragVector);
               // store the new point as the old, for use next time
               dragDataXOld = dragDataXNew;
               dragDataYOld = dragDataYNew;
               // During dragging, the crosshairs lock onto the center of the dragNode
               double crosshairX = xyPlot.getDataset().getXValue(0, dragNode);
               double crosshairY = xyPlot.getDataset().getYValue(0, dragNode);
               double crosshairScreenX = xyPlot.getDomainAxis().valueToJava2D(crosshairX, dataArea, xAxisLocation);
               double crosshairScreenY = xyPlot.getRangeAxis().valueToJava2D(crosshairY, dataArea, yAxisLocation);
               updateCrosshairs((int)crosshairScreenX, (int)crosshairScreenY);
            }
         }
         dragScreenXOld = e.getX();
         dragScreenYOld = e.getY();
      } else {
         super.mouseDragged(e);
      }
   }

   public void mouseMoved(MouseEvent e) {
      updateCursorLocation(e);
      if (showCrosshairs == true) {
         updateCrosshairs(e.getX(), e.getY());
      } else {
         super.mouseMoved(e);
      }
   }

   public void mouseReleased(MouseEvent e) {
      updateCursorLocation(e);
      int keyMods = e.getModifiers();
      if (picking == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         endBoxSelect(e);
      } else if (getDragging() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         dragNode = -1;
         dragScreenXOld = -1;
         dragScreenYOld = -1;
         dragDataXOld = -99.9;
         dragDataYOld = -99.9;
         setDragging(false);
      } else if ((keyMods & InputEvent.BUTTON3_MASK) > 0 && e.isPopupTrigger()) {
         if (rightClickNode >= 0 && this.nodePopUpMenu != null)
            this.nodePopUpMenu.show(this, e.getX(), e.getY());
         else if (this.addNodePopUpMenu != null)
            this.addNodePopUpMenu.show(this, e.getX(), e.getY());
      } else {
         super.mouseReleased(e);
      }
   }

   private void startBoxSelect(MouseEvent e) {
      if (this.boxSelectRectangle == null) {
         Rectangle2D screenDataArea = getScreenDataArea(e.getX(), e.getY());
         if (screenDataArea != null) {
            this.boxSelectPoint = getPointInRectangle(e.getX(), e.getY(), screenDataArea);
         }
         else {
            this.boxSelectPoint = null;
         }
      }
   }

   private void doBoxSelect(MouseEvent e) {
      // if no initial boxSelect point was set, ignore dragging...
      if (this.boxSelectPoint == null)
         return;

      Graphics2D g2 = (Graphics2D) getGraphics();

      // Use XOR to erase the old rectangle, if any.
      g2.setXORMode(boxSelectColor);
      if (this.boxSelectRectangle != null)
         g2.draw(this.boxSelectRectangle);
      // Save the current paint color. You need to restore it
      // after highlighting the control points in order for
      // the XOR drawing of the box to work properly.
      Paint savedPaint = g2.getPaint();
      g2.setPaintMode();

      Rectangle2D scaledDataArea = getScreenDataArea(
         (int) this.boxSelectPoint.getX(), (int) this.boxSelectPoint.getY());
      // Box can be dragged in any direction, so compute proper min and max
      // given direction of drag and bounds of data area.
      double xmin=0, xmax=0, ymin=0, ymax=0;
      if (e.getX() < this.boxSelectPoint.getX()) {
         xmin = Math.max(e.getX(), scaledDataArea.getMinX());
         xmax = this.boxSelectPoint.getX();
      } else {
         xmin = this.boxSelectPoint.getX();
         xmax = Math.min(e.getX(), scaledDataArea.getMaxX());
      }
      if (e.getY() < this.boxSelectPoint.getY()) {
         ymin = Math.max(e.getY(), scaledDataArea.getMinY());
         ymax = this.boxSelectPoint.getY();
      } else {
         ymin = this.boxSelectPoint.getY();
         ymax = Math.min(e.getY(), scaledDataArea.getMaxY());
      }
      this.boxSelectRectangle = new Rectangle2D.Double(xmin, ymin, xmax - xmin, ymax - ymin);

      XYPlot xyPlot = getChart().getXYPlot();
      ArrayList<Integer> newBoxSelectNodes = getBoxSelectNodes(this.boxSelectRectangle);
      // For the nodes that were picked up with the latest box resizing, toggle their select state
      for (int i=0; i<newBoxSelectNodes.size(); i++) {
         if (oldBoxSelectNodes == null || oldBoxSelectNodes.contains(newBoxSelectNodes.get(i)) == false) {
            FunctionEditorTopComponent.findInstance().toggleAddSelectedNode(newBoxSelectNodes.get(i));
            // Draw the control point with the new color
            xyPlot.getRenderer().drawItem(g2, null, getScreenDataArea(), null, xyPlot,
               xyPlot.getDomainAxis(), xyPlot.getRangeAxis(), xyPlot.getDataset(), 0,
               newBoxSelectNodes.get(i), null, 1);
         }
      }
      // For the nodes that dropped out with the latest box resizing, toggle their select state
      if (oldBoxSelectNodes != null) {
         for (int i=0; i<oldBoxSelectNodes.size(); i++) {
            if (newBoxSelectNodes.contains(oldBoxSelectNodes.get(i)) == false) {
               FunctionEditorTopComponent.findInstance().toggleAddSelectedNode(oldBoxSelectNodes.get(i));
               // Draw the control point with the new color
               xyPlot.getRenderer().drawItem(g2, null, getScreenDataArea(), null, xyPlot,
                  xyPlot.getDomainAxis(), xyPlot.getRangeAxis(), xyPlot.getDataset(), 0,
                  oldBoxSelectNodes.get(i), null, 1);
            }
         }
      }
      oldBoxSelectNodes = newBoxSelectNodes;

      // Use XOR to draw the new rectangle.
      g2.setPaint(savedPaint);
      g2.setXORMode(boxSelectColor);
      if (this.boxSelectRectangle != null)
         g2.draw(this.boxSelectRectangle);

      g2.dispose();
   }

   private void endBoxSelect(MouseEvent e) {
      // use XOR to erase the last zoom rectangle.
      if (this.boxSelectRectangle != null) {
         Graphics2D g2 = (Graphics2D) getGraphics();
         g2.setXORMode(boxSelectColor);
         g2.draw(this.boxSelectRectangle);
         this.boxSelectPoint = null;
         this.boxSelectRectangle = null;
         this.oldBoxSelectNodes = null;
      }
   }

   private ArrayList<Integer> getBoxSelectNodes(Rectangle2D box) {
      ArrayList<Integer> nodes = new ArrayList<Integer>(0);
      XYPlot xyPlot = getChart().getXYPlot();
      XYDataset xyDataset = xyPlot.getDataset();
      // Compute dataBox (data coordinates, X right, Y up)
      // from box (screen coordinates, X right, Y down)
      RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
      Rectangle2D dataArea = getScreenDataArea();
      double dataXMin = xyPlot.getDomainAxis().java2DToValue(box.getMinX(), dataArea, xAxisLocation);
      double dataXMax = xyPlot.getDomainAxis().java2DToValue(box.getMaxX(), dataArea, xAxisLocation);
      double dataYMin = xyPlot.getRangeAxis().java2DToValue(box.getMaxY(), dataArea, yAxisLocation);
      double dataYMax = xyPlot.getRangeAxis().java2DToValue(box.getMinY(), dataArea, yAxisLocation);
      Rectangle2D dataBox = new Rectangle2D.Double(dataXMin, dataYMin, dataXMax - dataXMin, dataYMax - dataYMin);
      //System.out.println("box = " + box.getMinX() + " " + box.getMaxX() + " " + box.getMinY() + " " + box.getMaxY());
      //System.out.println("dataBox = " + dataBox.getMinX() + " " + dataBox.getMaxX() + " " + dataBox.getMinY() + " " + dataBox.getMaxY());
      for (int i=0; i<xyDataset.getItemCount(0); i++) {
         double x = xyDataset.getXValue(0, i);
         double y = xyDataset.getYValue(0, i);
         if (dataBox.contains(x, y) == true)
            nodes.add(i);
      }
      return nodes;
   }

   /* This method is in ChartPanel, but is private. */
   private Point getPointInRectangle(int x, int y, Rectangle2D area) {
       x = (int) Math.max(Math.ceil(area.getMinX()), Math.min(x, 
               Math.floor(area.getMaxX())));   
       y = (int) Math.max(Math.ceil(area.getMinY()), Math.min(y, 
               Math.floor(area.getMaxY())));
       return new Point(x, y);
   }

   public void updateCrosshairs(int screenX, int screenY) {
      XYPlot xyPlot = getChart().getXYPlot();
      if (showCrosshairs == true) {
         RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
         RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
         Rectangle2D dataArea = getScreenDataArea();
         double crosshairX = xyPlot.getDomainAxis().java2DToValue((double)screenX, dataArea, xAxisLocation);
         double crosshairY = xyPlot.getRangeAxis().java2DToValue((double)screenY, dataArea, yAxisLocation);
         if (crosshairX < xyPlot.getDomainAxis().getLowerBound() ||
             crosshairX > xyPlot.getDomainAxis().getUpperBound() ||
             crosshairY < xyPlot.getRangeAxis().getLowerBound() ||
             crosshairY > xyPlot.getRangeAxis().getUpperBound()) {
            xyPlot.setDomainCrosshairVisible(false);
            xyPlot.setRangeCrosshairVisible(false);
            crosshairAnnotation.setText("");
         } else {
            xyPlot.setDomainCrosshairVisible(true);
            xyPlot.setRangeCrosshairVisible(true);
            /** The xyPlot's crosshairs are updated with the screen coordinates of the XY location.
             * The annotation's text and location is updated with the data coordinates.
             * The format used for displaying the XY data coordinates is taken from the
             * format used for the X and Y axis tick labels. This format is not normally
             * accessible here, but a method was added to NumberTickUnit to provide it.
             * If this turns out to be problematic, the format could always be changed
             * to use a fixed number of significant digits.
             */
            NumberAxis dna = (NumberAxis)xyPlot.getDomainAxis();
            NumberFormat dnf = (NumberFormat)dna.getTickUnit().getFormatter().clone();
            dnf.setMaximumFractionDigits(dnf.getMaximumFractionDigits()+3);
            String xString = dnf.format(crosshairX);
            NumberAxis rna = (NumberAxis)xyPlot.getRangeAxis();
            NumberFormat rnf = (NumberFormat)rna.getTickUnit().getFormatter().clone();
            rnf.setMaximumFractionDigits(rnf.getMaximumFractionDigits()+3);
            String yString = rnf.format(crosshairY);
            crosshairAnnotation.setText("(" + xString + ", " + yString + ")");
            crosshairAnnotation.setX(crosshairX);
            crosshairAnnotation.setY(crosshairY);
            xyPlot.handleClick(screenX, screenY, this.getChartRenderingInfo().getPlotInfo());
         }
      }
   }

   public void setDragging(boolean state) {
      XYPlot xyPlot = getChart().getXYPlot();
      dragging = state;
      if (state == true) {
         // Save the autoRange state, then set it to false for dragging.
         domainAxisAutoRange = xyPlot.getDomainAxis().isAutoRange();
         rangeAxisAutoRange = xyPlot.getRangeAxis().isAutoRange();
         xyPlot.getDomainAxis().setAutoRange(false);
         xyPlot.getRangeAxis().setAutoRange(false);
      } else {
         // Restore the autoRange state
         xyPlot.getDomainAxis().setAutoRange(domainAxisAutoRange);
         xyPlot.getRangeAxis().setAutoRange(rangeAxisAutoRange);
      }
      if (mandatoryCrosshairs == false)
         setCrosshairsState(state);
   }

   public boolean getDragging() {
      return this.dragging;
   }

   public void setMandatoryCrosshairs(boolean state) {
      mandatoryCrosshairs = state;
      setCrosshairsState(state);
      if (state == true)
         updateCrosshairs(-1, -1);
   }

   public void setCrosshairsState(boolean state) {
      XYPlot xyPlot = getChart().getXYPlot();
      // With two ways to turn on/off crosshairs, it's possible
      // to call this method twice in a row with state=true.
      // But you want to add the annotation only once.
      if (state == true && showCrosshairs == false) {
         crosshairAnnotation.setText("");
         xyPlot.addAnnotation(crosshairAnnotation);
      } else if (state == false) {
         xyPlot.removeAnnotation(crosshairAnnotation);
      }
      if (state == false) {
         xyPlot.setDomainCrosshairVisible(false);
         xyPlot.setRangeCrosshairVisible(false);
      }
      showCrosshairs = state;
   }

   public void keyPressed(KeyEvent e) {
      if (e.getKeyCode() == KeyEvent.VK_CONTROL)
         picking = true;
      else if (e.getKeyCode() == KeyEvent.VK_F1) {
         //mandatoryCrosshairs = true;
         //setCrosshairsState(true);
         //updateCrosshairs(lastMouseX, lastMouseY);
      }
   }

   public void keyTyped(KeyEvent e) { }

   public void keyReleased(KeyEvent e) {
      if (e.getKeyCode() == KeyEvent.VK_CONTROL)
         picking = false;
      else if (e.getKeyCode() == KeyEvent.VK_F1) {
         //mandatoryCrosshairs = false;
         //setCrosshairsState(false);
      }
   }

   private int findNodeAt(int x, int y) {
      XYPlot xyPlot = getChart().getXYPlot();
      XYDataset xyDataset = xyPlot.getDataset();
      RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
      Rectangle2D dataArea = getScreenDataArea();
      // Loop through the nodes from last to first, so if the circles
      // for two or more nodes overlap, you get the one drawn on top.
      for (int i=xyDataset.getItemCount(0)-1; i>=0; i--) {
         double sx = xyPlot.getDomainAxis().valueToJava2D(xyDataset.getXValue(0, i), dataArea, xAxisLocation);
         double sy = xyPlot.getRangeAxis().valueToJava2D(xyDataset.getYValue(0, i), dataArea, yAxisLocation);
         double distance = Math.sqrt((sx-x)*(sx-x) + (sy-y)*(sy-y));
         if (distance < 6.0) {
            return i;
         }
      }
      return -1;
   }

   protected JPopupMenu createNodePopupMenu() {

       JPopupMenu menu = new JPopupMenu("Node Commands");

       JMenuItem duplicateNodeItem = new JMenuItem("Duplicate control point");
       duplicateNodeItem.setActionCommand(DUPLICATE_NODE_COMMAND);
       duplicateNodeItem.addActionListener(this);
       menu.add(duplicateNodeItem);

       JMenuItem deleteNodeItem = new JMenuItem("Delete control point");
       deleteNodeItem.setActionCommand(DELETE_NODE_COMMAND);
       deleteNodeItem.addActionListener(this);
       menu.add(deleteNodeItem);

       return menu;
   }

   protected JPopupMenu createAddNodePopupMenu() {

       JPopupMenu menu = new JPopupMenu("Node Commands");

       JMenuItem addNodeItem = new JMenuItem("Add control point");
       addNodeItem.setActionCommand(ADD_NODE_COMMAND);
       addNodeItem.addActionListener(this);
       menu.add(addNodeItem);

       return menu;
   }

    public void actionPerformed(ActionEvent event) {

        String command = event.getActionCommand();

        if (command.equals(DUPLICATE_NODE_COMMAND)) {
            FunctionEditorTopComponent.findInstance().duplicateNode(rightClickNode);
            rightClickNode = -1;
        }
        else if (command.equals(DELETE_NODE_COMMAND)) {
            FunctionEditorTopComponent.findInstance().deleteNode(rightClickNode);
            rightClickNode = -1;
        }
        else if (command.equals(ADD_NODE_COMMAND)) {
            addNode(rightClickX, rightClickY);
            rightClickNode = -1;
        }
    }
 
    private void addNode(int screenX, int screenY) {
      XYPlot xyPlot = getChart().getXYPlot();
      RectangleEdge xAxisLocation = xyPlot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = xyPlot.getRangeAxisEdge();
      Rectangle2D dataArea = getScreenDataArea();
      double newNodeX = xyPlot.getDomainAxis().java2DToValue(screenX, dataArea, xAxisLocation);
      double newNodeY = xyPlot.getRangeAxis().java2DToValue(screenY, dataArea, yAxisLocation);
      FunctionEditorTopComponent.findInstance().addNode(newNodeX, newNodeY);
    }
 }
