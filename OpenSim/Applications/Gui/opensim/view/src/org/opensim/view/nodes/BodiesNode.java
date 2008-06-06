package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import javax.swing.ImageIcon;
import java.io.IOException;
import java.util.ResourceBundle;
import java.util.Stack;
import javax.swing.Action;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.actions.NewAction;
import org.openide.actions.PropertiesAction;
import org.openide.actions.ToolsAction;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.SystemAction;
import org.openide.util.datatransfer.NewType;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.Model;

/**
 * Node class to wrap Model's collection of SimmBodies
 */
public class BodiesNode extends OpenSimObjectSetNode {
    boolean topological=false;
    private static ResourceBundle bundle = NbBundle.getBundle(BodiesNode.class);

    public BodiesNode(BodySet bodySet) {
        super(bodySet);
        setDisplayName(NbBundle.getMessage(BodiesNode.class, "CTL_Bodies"));
        //Stack<OneBodyNode> stack = new Stack<OneBodyNode>();

        for (int bodyNum=0; bodyNum < bodySet.getSize(); bodyNum++ ){

            AbstractBody body = bodySet.get(bodyNum);
            Children children = getChildren();

            if (topological){
                /*while (stack.size() > i.getNumAncestors())
                    stack.pop();

                if (stack.size() > 0)
                    children = stack.peek().getChildren();

                stack.push(new BodyNode(body));

                children.add(new Node[] { stack.peek() });*/
            }
            else {
                OneBodyNode node = new OneBodyNode(body);
                Node[] arrNodes = new Node[1];
                arrNodes[0] = node;
                children.add(arrNodes);
            }
        }
      addDisplayOption(displayOption.Isolatable);
      addDisplayOption(displayOption.Showable);
      addDisplayOption(displayOption.Colorable);
    }

      public Image getIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/bodiesNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
   public Image getOpenedIcon(int i) {
      URL imageURL=null;
      try {
         imageURL = Class.forName("org.opensim.view.nodes.OpenSimNode").getResource("/org/opensim/view/nodes/icons/bodiesNode.png");
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
      if (imageURL != null) {
         return new ImageIcon(imageURL, "").getImage();
      } else {
         return null;
      }
   }
   
    /**
     * Display name 
     */
    public String getHtmlDisplayName() {
        
        return "Bodies";
    }
    
} // class BodiesNode
