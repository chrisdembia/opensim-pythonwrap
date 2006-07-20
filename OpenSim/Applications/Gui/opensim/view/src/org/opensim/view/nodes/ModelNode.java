/*
 * ModelNode.java
 *
 * Created on May 5, 2006, 12:11 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.nodes;


import java.awt.datatransfer.Transferable;
import java.io.IOException;
import javax.swing.AbstractAction;
import javax.swing.Action;
import org.openide.nodes.AbstractNode;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.Lookup;
import org.openide.util.datatransfer.PasteType;
import org.openide.util.lookup.Lookups;
import org.openide.windows.TopComponent;
import org.openide.windows.TopComponent.Registry;
import org.opensim.modeling.OpenSimObject;

/**
 * 
 * @author ken
 */
public class ModelNode<T> extends AbstractNode implements Node.Cookie {
    
    public T _object = null;

    /** Creates a new instance of ModelNode */
    public ModelNode(T obj) {
        super(new Children.Array(), Lookups.singleton(obj));
        _object = obj;
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

    public Action[] getActions(boolean b) {
        Action[] retValue;
        /*
        static Lookup.Template tpl = new Lookup.Template (OpenSimObject.class);
        Lookup.Result res = Utilities.actionsGlobalContext().lookup (tpl);
        res.addLookupListener (new LookupListener() {
           public void resultChanged (LookupEvent evt) {
             Collection c = ((Lookup.Result) evt.getSource()).allInstances();
             //do something with the collection of 0 or more instances - the collection has changed
             int z = c.size();
           }
        });
        */
        Lookup myLookup = this.getLookup();
        Object obj = myLookup.lookup(OpenSimObject.class);
         
        OpenSimObject obj2 = (OpenSimObject) obj;
        AbstractAction showNameAction = 
                new AbstractAction(obj2.getName()){ public void actionPerformed(java.awt.event.ActionEvent evt){};};
        return (new Action[]{showNameAction});
    }
    
    
    /** Root node (has all open models as its children). */
    public static class RootNode extends ModelNode<String> {
        public RootNode() {
            super("Models");
            setName("Models");
        }
    }
    
   
} // class ModelNode
