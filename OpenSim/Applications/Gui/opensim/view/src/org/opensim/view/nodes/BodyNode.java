package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import java.util.ResourceBundle;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.view.ViewDB;
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
        
        final SimmModel ownerModel = getModelForNode();
        //retValue = super.getActions(b);
        Action reviewAction = new CallableSystemAction(){
            public void performAction() {
                 ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(BodyNode.this.b, 
                                                    ViewDB.getInstance().getVTKTopComponentForModel(ownerModel));
                 editorDialog.process();
            }

            public String getName() {
                return "Review";
            }

            public HelpCtx getHelpCtx() {
                return null;
            }}; 
        return (new Action[] {reviewAction});
    }
    /**
     * Icon for the body node 
     **/
    public Image getIcon(int i) {
        URL imageURL = this.getClass().getResource("/org/opensim/view/nodes/icons/body.png");
        if (imageURL != null) {
            return new ImageIcon(imageURL, "Body").getImage();
        } else {
            return null;
        }
    }

    public Image getOpenedIcon(int i) {
        return getIcon(i);
    }
    
}