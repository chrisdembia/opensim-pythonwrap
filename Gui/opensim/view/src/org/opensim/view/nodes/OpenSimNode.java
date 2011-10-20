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
import java.io.IOException;
import java.net.URL;
import java.util.Hashtable;
import javax.swing.ImageIcon;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.nodes.PropertySupport;
import org.openide.nodes.Sheet;
//import org.openide.util.Exceptions;
import org.openide.util.Lookup;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Property;
import org.opensim.modeling.Property.PropertyType;

/**
 * 
 * @author ken
 *
 *  Ayman: modified the name to OpenSimNode.
 *
 * Intended as a common base node to enforce common behavior for all OpenSim created nodes.
 */
public class OpenSimNode extends AbstractNode {
    
    static Hashtable<PropertyType, Class> mapPropertyEnumToClass = new Hashtable<PropertyType, Class>();
    static Hashtable<PropertyType, String> mapPropertyEnumToGetters = new Hashtable<PropertyType, String>();
    static Hashtable<PropertyType, String> mapPropertyEnumToSetters = new Hashtable<PropertyType, String>();
    static {
        mapPropertyEnumToClass.put(PropertyType.Int, Integer.class);
        mapPropertyEnumToGetters.put(PropertyType.Int, "getValueInt");
        mapPropertyEnumToClass.put(PropertyType.Dbl, Double.class);
        mapPropertyEnumToGetters.put(PropertyType.Dbl, "getValueDbl");
        mapPropertyEnumToSetters.put(PropertyType.Dbl, "setValueDbl");
        mapPropertyEnumToClass.put(PropertyType.Str, String.class);
        mapPropertyEnumToGetters.put(PropertyType.Str, "getValueStr");
        mapPropertyEnumToClass.put(PropertyType.Bool, Boolean.class);
        mapPropertyEnumToGetters.put(PropertyType.Bool, "getValueBool");
        mapPropertyEnumToClass.put(PropertyType.Obj, OpenSimObject.class);
        mapPropertyEnumToGetters.put(PropertyType.Obj, "getValueObj");
    }
    /**
     * Creates a new instance of OpenSimNode
     */
    public OpenSimNode() {
        super(new Children.Array());
     }
    
    public OpenSimNode(Children children) {
        super(children);
    }

    public OpenSimNode(Children children, Lookup lookup) {
        super(children, lookup);
    }


    /** Root node (has all open models as its children). Unused!*/
    public static class RootNode extends OpenSimNode {
        public RootNode() {
            setDisplayName("Models");
        }
    }
    /**
     * Find the Model for a node by traversing up the tree
     */
    public Model getModelForNode() {
        if (this instanceof ConcreteModelNode)
            return ((ConcreteModelNode)this).getModel();
        else 
            return ((OpenSimNode)getParentNode()).getModelForNode();
    }

    /**
     * Icon for the node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/osimNode.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }
    public OpenSimObjectNode findChild(Object objectToMatch){
       if (this instanceof OpenSimObjectNode){
          if(((OpenSimObjectNode)this).getOpenSimObject().equals(objectToMatch))
             return (OpenSimObjectNode)this;
       }
       
       Node[] children = getChildren().getNodes();
       for(int i=0; i<children.length; i++){
          OpenSimObjectNode matchingNode = ((OpenSimNode)children[i]).findChild(objectToMatch);
          if(matchingNode !=null)
             return matchingNode;
       }
       
       return null;
    }
 
    /* Rename a node that contain a certain object. Check the 'this' node
     * and all its children, recursively, because there may be more than
     * one node that contains the object.
     */
    public void renameObjectNode(Object objectToRename, String newName) {
       if (this instanceof OpenSimObjectNode){
          if (((OpenSimObjectNode)this).getOpenSimObject().equals(objectToRename)) {
             setName(newName);
             setDisplayName(newName);
          }
       }
       
       Node[] children = getChildren().getNodes();
       for (int i=0; i<children.length; i++) {
          ((OpenSimNode)children[i]).renameObjectNode(objectToRename, newName);
       }
    }
/*
    @Override
    public PasteType getDropType(Transferable t, final int action, int index) {
       if (this instanceof OpenSimObjectNode)
        System.out.println(((OpenSimObjectNode)this).toString()+":"+"getDropType");
       DataFlavor[] flavors= t.getTransferDataFlavors();
       System.out.println("Flavors:"+flavors.toString());
        final Node dropNode = NodeTransfer.node( t,
                DnDConstants.ACTION_COPY_OR_MOVE+NodeTransfer.CLIPBOARD_CUT );
        if( null != dropNode ) {
            /*final Movie movie = (Movie)dropNode.getLookup().lookup( Movie.class );
            if( null != movie  && !this.equals( dropNode.getParentNode() )) {
                return new PasteType() {
                    public Transferable paste() throws IOException {
                        getChildren().add( new Node[] { new MovieNode(movie) } );
                        if( (action & DnDConstants.ACTION_MOVE) != 0 ) {
                            dropNode.getParentNode().getChildren().remove( new Node[] {dropNode} );
                        }
                        return null;
                    }
                };
            }
        }
        return null;
    }

    @Override
    public Cookie getCookie(Class clazz) {
       if (this instanceof OpenSimObjectNode)
        System.out.println(((OpenSimObjectNode)this).toString()+":"+"getCookie");
        Children ch = getChildren();

        if (clazz.isInstance(ch)) {
            return (Cookie) ch;
        }

        return super.getCookie(clazz);
    }

    @Override
    protected void createPasteTypes(Transferable t, List s) {
        if (this instanceof OpenSimObjectNode)
       System.out.println(((OpenSimObjectNode)this).toString()+":"+"createPasteTypes");
       super.createPasteTypes(t, s);
        PasteType paste = getDropType( t, DnDConstants.ACTION_COPY, -1 );
        if( null != paste )
            s.add( paste );
    }
*/
    @Override
    public Sheet createSheet() {
        Sheet sheet = Sheet.createDefault();
        Sheet.Set set = Sheet.createPropertiesSet();
        Sheet.Set setExpert = Sheet.createExpertSet();
        sheet.put(set);
        sheet.put(setExpert);
        return sheet;
    }
    /*
    protected void createPasteTypes(Transferable t, List ls) {
    final Node[] ns = NodeTransfer.nodes (t, NodeTransfer.COPY);
    if (ns != null) {
      ls.add (new PasteType () {
        public Transferable paste () throws IOException {
          Node[] nue = new Node[ns.length];
          for (int i = 0; i < nue.length; i++)
            nue[i] = ns[i].cloneNode ();
          getChildren ().add (nue);
          return null;
        }
      });
    }
    // Also try superclass, but give it lower priority:
    super.createPasteTypes(t, ls);
  }*/

} // class OpenSimNode
