package org.opensim.view.excitationEditor;
/*****************************************************************************************************
* TreeDropTarget.java
*author: Ulrich Hilger
*http://articles.lightdev.com/tree/tree_article.pdf
*
*TreeDropTarget extends the class "DropTarget", which implements the interface "DropTargetListener".
*DropTargetListener has a few methods, that are called automatically by Swing during drag operation
*(dragOver, dragExit, drop). So we can implement "autoscroll" and "automatic node expansion".
*"autoscroll" means to move the visible part of the tree in the window
*in a way that lets us see the dragged node, wherever the drag operation is being done.
*Since Swing automatically calls the "dragOver" method during the drag operation,
*we can call the "autoscroll" method in "dragOver".
*In "autoscroll" we test, if the node that is being moved,
*is outside a certain area of the visible rectangle of the tree.
*In that case a new rectangle is made visible using the Swing method "scrollRectToVisible".
*
*A collapsed node must be expanded, so that its children become visible and
*we can do a drop on them. The function "automatic node expansion" is also
*implemented in the method "dragOver". There we call the method "updateDragMark",
*which has several functions:
*  - it marks a node over which we are doing a drag (markNode),
*  - it expands this node, if it is collapsed (also in markNode),
*  - it draws an insert marker, when the node being moved is just
*    between two nodes (paintInsertMarker).
*
*In order to see which nodes are being dragged, we need a custom "paintImage" method, 
*which is also called in "dragOver".
*The method "paintImage" gets the current mouse position from "DropTargetDragEvent"
*and then draws a custom image, the actual image being created in the class "NodeMoveTransferHandler",
*because only there we know which nodes are being moved.
*So, there we introduce the variable "dragPath", 
*which is initialised in the method "createTransferable"
*and used in the method "createDragImage" to draw the image of the "dragPath".
*
****************************************************************************************************/

import java.awt.*;
import java.awt.dnd.*;
import java.awt.image.*;
import javax.swing.*;
import javax.swing.tree.*;

public class TreeDropTarget extends DropTarget {
    public TreeDropTarget(NodeMoveTransferHandler h) {
        super();
        this.handler = h;
    }
//    @Override
    public void dragOver(DropTargetDragEvent dtde) {
        JTree tree = (JTree) dtde.getDropTargetContext().getComponent();
        Point loc = dtde.getLocation();
        updateDragMark(tree, loc);
        paintImage(tree, loc);
        autoscroll(tree, loc);
        super.dragOver(dtde);
    }
    public void dragExit(DropTargetDragEvent dtde) {
        clearImage((JTree) dtde.getDropTargetContext().getComponent());
        super.dragExit(dtde);
    }
//    @Override
    public void drop(DropTargetDropEvent dtde) {
        clearImage((JTree) dtde.getDropTargetContext().getComponent());
        super.drop(dtde);
    }
    private final void paintImage(JTree tree, Point location) {
        Point pt = new Point(location);
        BufferedImage[] image = handler.getDragImage();
        if(image != null) {
            tree.paintImmediately(rect2D.getBounds());
            rect2D.setLocation(pt.x-15, pt.y-15);
            int wRect2D = 0;
            int hRect2D= 0;
            for (int i = 0; i < image.length; i++) {
                tree.getGraphics().drawImage(image[i], pt.x-15, pt.y-15, tree);
                pt.y += image[i].getHeight();
                if(wRect2D < image[i].getWidth())
                    wRect2D = image[i].getWidth();
                hRect2D += image[i].getHeight();
            }
            rect2D.setSize(wRect2D, hRect2D);
        }
    }
    private final void clearImage(JTree tree) {
        tree.paintImmediately(rect2D.getBounds());
    }
    private Insets getAutoscrollInsets() {
        return autoscrollInsets;
    }
    private void autoscroll(JTree tree, Point cursorLocation) {
        Insets insets = getAutoscrollInsets();
        Rectangle outer = tree.getVisibleRect();
        Rectangle inner = new Rectangle(
                outer.x+insets.left,
                outer.y+insets.top,
                outer.width-(insets.left+insets.right),
                outer.height-(insets.top+insets.bottom));
        if (!inner.contains(cursorLocation))  {
            Rectangle scrollRect = new Rectangle(
                    cursorLocation.x-insets.left,
                    cursorLocation.y-insets.top,
                    insets.left+insets.right,
                    insets.top+insets.bottom);
            tree.scrollRectToVisible(scrollRect);
        }
    }
    public void updateDragMark(JTree tree, Point location) {
        mostRecentLocation = location;
        int row = tree.getRowForPath(tree.getClosestPathForLocation(location.x, location.y));
        TreePath path = tree.getPathForRow(row);
        if(path != null) {
            Rectangle rowBounds = tree.getPathBounds(path);
      /*
       * find out if we have to mark a tree node or if we
       * have to draw an insertion marker
       */
            int rby = rowBounds.y;
            int topBottomDist = insertAreaHeight / 2;
            // x = top, y = bottom of insert area
            Point topBottom = new Point(rby - topBottomDist, rby + topBottomDist);
            if(topBottom.x <= location.y && topBottom.y >= location.y) {
                // we are inside an insertArea
                paintInsertMarker(tree, location);
            } else {
                // we are inside a node
                markNode(tree, location);
            }
        }
    }
    public Point getMostRecentDragLocation() {
        return mostRecentLocation;
    }
    private void markNode(JTree tree, Point location) {
        TreePath path = tree.getClosestPathForLocation(location.x, location.y);
        if(path != null) {
            if(lastRowBounds != null) {
                Graphics g = tree.getGraphics();
                g.setColor(Color.white);
                g.drawLine(lastRowBounds.x, lastRowBounds.y,
                        lastRowBounds.x + lastRowBounds.width, lastRowBounds.y);
            }
            tree.setSelectionPath(path);
            tree.expandPath(path);
        }
    }
    private void paintInsertMarker(JTree tree, Point location) {
        Graphics g = tree.getGraphics();
        tree.clearSelection();
        int row = tree.getRowForPath(tree.getClosestPathForLocation(location.x, location.y));
        TreePath path = tree.getPathForRow(row);
        if(path != null) {
            Rectangle rowBounds = tree.getPathBounds(path);
            if(lastRowBounds != null) {
                g.setColor(Color.white);
                g.drawLine(lastRowBounds.x, lastRowBounds.y,
                        lastRowBounds.x + lastRowBounds.width, lastRowBounds.y);
            }
            if(rowBounds != null) {
                g.setColor(Color.black);
                g.drawLine(rowBounds.x, rowBounds.y, rowBounds.x + rowBounds.width, rowBounds.y);
            }
            lastRowBounds = rowBounds;
        }
    }
    private Rectangle lastRowBounds;
    private int insertAreaHeight = 8;
    private Insets autoscrollInsets = new Insets(20, 20, 20, 20);
    private Rectangle rect2D = new Rectangle();
    private NodeMoveTransferHandler handler;
    private Point mostRecentLocation;
}

