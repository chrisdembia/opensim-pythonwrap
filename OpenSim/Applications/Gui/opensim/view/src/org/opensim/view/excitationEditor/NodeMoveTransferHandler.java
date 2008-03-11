
package org.opensim.view.excitationEditor;
/*****************************************************************************************************
* NodeMoveTransferHandler.java
*author: Ulrich Hilger
*http://articles.lightdev.com/tree/tree_article.pdf
*
* The NodeMoveTransferHandler extends the class "TransferHandler" and
* overrides the method "createTransferable"
* where we state what happens at the beginning of the drag operation.
* There we simply test if the component is a tree
* and all selected tree paths are passed in an array to the "GenericTransferable".
* Additionally we call the methode "createDragImage"
* in order to create a semi transparent image of the nodes being moved.
*
* As soon as the user releases the mouse key, Swing automatically calls the method "exportDone".
* There we test if a node is selected, and this one serves as target node.
* Then we get all tree paths from the Transferable and each is moved to the new
* parent node (addNodes), respectively inserted between two nodes (insertNodes).
*
* The method "createDragImage" uses the cell renderer of the tree to get the components
* by which the nodes being moved are represented (usually JLabels).
* It then creates a semi transparent BufferedImage and draws the Components (JLabels) on them.
* The image created is returned using the method "getDragImage".
* ("getDragImage" is called by "paintImage" in "TreeDropTarget".)
****************************************************************************************************/

import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.image.*;
import java.io.*;
import javax.swing.*;
import javax.swing.tree.*;
public abstract class NodeMoveTransferHandler extends TransferHandler {
    public NodeMoveTransferHandler() {
        super();
    }
//    @Override
    protected Transferable createTransferable(JComponent c) {
        Transferable t = null;
        if(c instanceof JTree) {
            JTree tree = (JTree) c;
            t = new GenericTransferable(tree.getSelectionPaths());
            dragPath = tree.getSelectionPaths();
            createDragImage(tree);
        }
        return t;
    }
//    @Override 
    protected void exportDone(JComponent source, Transferable data, int action) {
        if(source instanceof JTree) {
            JTree tree = (JTree) source;
            DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
            TreePath currentPath = tree.getSelectionPath();
            ///System.out.println("Destination node="+currentPath.getLastPathComponent().toString());
            if(currentPath != null) {
                System.out.println("addNodes");
                addNodes(currentPath, model, data);
                handlePathMove(currentPath, model, data);
            } else {
                System.out.println("insertNodes");
                insertNodes(tree, model, data);
                handlePathRearrange(currentPath, model, data);
           }
        }
        dragPath = null;
        super.exportDone(source, data, action);
    }
    /**
     * Move nodes out from their parent to the currentPath
     */
    private void addNodes(TreePath currentPath, DefaultTreeModel model, Transferable data) {
        MutableTreeNode targetNode = (MutableTreeNode) currentPath.getLastPathComponent();
        try {
            TreePath[] movedPaths = (TreePath[]) data.getTransferData(DataFlavor.stringFlavor);
            for(int i = 0; i < movedPaths.length; i++) {
                MutableTreeNode moveNode = (MutableTreeNode) movedPaths[i].getLastPathComponent();
                if(!moveNode.equals(targetNode)) {
                    MutableTreeNode oldParent = (MutableTreeNode) moveNode.getParent();
                    int oldIndex = model.getIndexOfChild(oldParent, moveNode);
                    if(oldParent == null) return ;
                    model.removeNodeFromParent(moveNode);
                    try{
                        model.insertNodeInto(moveNode, targetNode, targetNode.getChildCount());
                    }catch(IllegalArgumentException ex){
                        model.insertNodeInto(moveNode, oldParent, oldIndex);
                    }
                }
            }
        } catch (UnsupportedFlavorException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    /**
     * Change the order of children in same parent
     */
    private void insertNodes(JTree tree, DefaultTreeModel model, Transferable data) {
        Point location = ((TreeDropTarget) tree.getDropTarget()).getMostRecentDragLocation();
        TreePath path = tree.getClosestPathForLocation(location.x, location.y);
        MutableTreeNode targetNode = (MutableTreeNode) path.getLastPathComponent();
        MutableTreeNode parent = (MutableTreeNode) targetNode.getParent();
        try {
            TreePath[] movedPaths = (TreePath[]) data.getTransferData(DataFlavor.stringFlavor);
            for(int i = 0; i < movedPaths.length; i++) {
                MutableTreeNode moveNode = (MutableTreeNode) movedPaths[i].getLastPathComponent();
                if(!moveNode.equals(targetNode)) {
                    MutableTreeNode oldParent = (MutableTreeNode) moveNode.getParent();
                    int oldIndex = model.getIndexOfChild(oldParent, moveNode);
                    if(oldParent == null) return ;
                    model.removeNodeFromParent(moveNode);
                    try{
                        model.insertNodeInto(moveNode, parent, model.getIndexOfChild(parent, targetNode));
                    }catch(IllegalArgumentException ex){
                        model.insertNodeInto(moveNode, oldParent, oldIndex);
                    }
                }
            }
        } catch (UnsupportedFlavorException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
//    @Override
    public int getSourceActions(JComponent c) {
        return TransferHandler.MOVE;
    }
    public BufferedImage[] getDragImage() {
        return image;
    }
    private void createDragImage(JTree tree) {
        if (dragPath != null) {
            try {
                image = new BufferedImage[dragPath.length];
                for (int i = 0; i < dragPath.length; i++) {
                    Rectangle pathBounds = tree.getPathBounds(dragPath[i]);
                    TreeCellRenderer r = tree.getCellRenderer();
                    DefaultTreeModel m = (DefaultTreeModel)tree.getModel();
                    boolean nIsLeaf = m.isLeaf(dragPath[i].getLastPathComponent());
                    MutableTreeNode draggedNode = (MutableTreeNode) dragPath[i].getLastPathComponent();
                    JComponent lbl = (JComponent)r.getTreeCellRendererComponent(tree, draggedNode, false ,
                            tree.isExpanded(dragPath[i]),nIsLeaf, 0,false);
                    lbl.setBounds(pathBounds);
                    BufferedImage img = new BufferedImage(lbl.getWidth(), lbl.getHeight(),
                            BufferedImage.TYPE_INT_ARGB_PRE);
                    Graphics2D graphics = img.createGraphics();
                    graphics.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f));
                    lbl.setOpaque(false);
                    lbl.paint(graphics);
                    graphics.dispose();
                    image[i] = img;
                }
            } catch (RuntimeException re) {}
        }
    }

    abstract public void handlePathMove(TreePath currentPath, DefaultTreeModel model, Transferable data) ;
    abstract public void handlePathRearrange(TreePath currentPath, DefaultTreeModel model, Transferable data) ;
    
    private TreePath[] dragPath;
    private BufferedImage[] image;
}