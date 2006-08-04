package org.opensim.view.nodes;

import java.util.ResourceBundle;
import javax.swing.Action;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.openide.windows.TopComponent;
import org.opensim.modeling.SimmBody;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.editors.ObjectEditDialogMaker;

/** Node class to wrap SimmBody objects */
public class BodyNode extends OpenSimNode{
    SimmBody b;
    private static ResourceBundle bundle = NbBundle.getBundle(BodyNode.class);
    public BodyNode(SimmBody b) {
        super();
        this.b = b;
        setDisplayName(b.getName());
        setShortDescription(bundle.getString("HINT_BodyNode"));
   }
    
    public String getHtmlDisplayName() {
        
        return b.getName() ;
    }
    public Node cloneNode() {
        return new BodyNode(b);
    }

    public Action[] getActions(boolean b) {
        Action[] retValue;
        
        retValue = super.getActions(b);
 /*       Action reviewAction = new CallableSystemAction(){
            public void performAction() {
                 ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(BodyNode.this.b, (ModelWindowVTKTopComponent)null);
                 editorDialog.process();
            }

            public String getName() {
                return "Review";
            }

            public HelpCtx getHelpCtx() {
                return null;
            }}; */
        return (retValue);
    }
    
}