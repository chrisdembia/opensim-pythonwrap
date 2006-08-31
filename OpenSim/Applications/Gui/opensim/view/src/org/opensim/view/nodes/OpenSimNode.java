/*
 * OpenSimNode.java
 *
 * Created on May 5, 2006, 12:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.nodes;


import java.awt.Image;
import java.awt.datatransfer.Transferable;
import java.io.IOException;
import java.net.URL;
import javax.swing.ImageIcon;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.openide.util.datatransfer.PasteType;
import org.opensim.modeling.SimmModel;

/**
 * 
 * @author ken
 *
 *  Ayman: modified the name to OpenSimNode.
 *
 * Intended as a common base node to enforce common behavior for all OpenSim created nodes.
 * Right now just a place holder.
 */
public class OpenSimNode extends AbstractNode {
    
    /**
     * Creates a new instance of OpenSimNode
     */
    public OpenSimNode() {
        super(new Children.Array());
     }
    
    public OpenSimNode(Children children) {
        super(children);
    }

    public boolean canCopy() {
        return true;
    }

    public PasteType getDropType(Transferable transferable, int i, int i0) {
        PasteType retValue;
        
        retValue = super.getDropType(transferable, i, i0);
        return retValue;
    }

    public boolean canCut() {
         return true;
    }

    public Transferable clipboardCopy() throws IOException {
        Transferable retValue;
        
        retValue = super.clipboardCopy();
        return retValue;
    }

    /** Root node (has all open models as its children). */
    public static class RootNode extends OpenSimNode {
        public RootNode() {
            setDisplayName("Models");
        }
    }
    /**
     * Find the SimmModel for a node by traversingup the tree
     */
    protected SimmModel getModelForNode() {
        if (this instanceof ConcreteModelNode)
            return ((ConcreteModelNode)this).getModel();
        else 
            return ((OpenSimNode)getParentNode()).getModelForNode();
    }

    /**
     * Icon for the body node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/collapsedNode.gif");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/openNode.gif");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "").getImage();
        } else {
            return null;
        }
    }
    

} // class OpenSimNode
