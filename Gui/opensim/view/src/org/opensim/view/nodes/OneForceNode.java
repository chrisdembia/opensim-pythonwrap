/*
 *
 * OneForceNode
 * Author(s): Peter Loan
 * Copyright (c)  2009, Stanford University, Peter Loan
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
package org.opensim.view.nodes;

import java.awt.Image;
import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.openide.nodes.Children;
import org.openide.util.NbBundle;
import org.opensim.modeling.Force;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ObjectDisplayMenuAction;

/**
 *
 * @author Ayman Habib
 */
public class OneForceNode extends OpenSimObjectNode implements DisableableObject{

    private static ResourceBundle bundle = NbBundle.getBundle(OneForceNode.class);
    /**
     * Creates a new instance of OneForceNode
     */
    public OneForceNode(OpenSimObject force) {
        super(force);
        updateDisabledFlag(force);
        setShortDescription(bundle.getString("HINT_OtherForceNode"));
        setChildren(Children.LEAF);
        Force f= Force.safeDownCast(force);
        if (f.getDisplayer()!=null){
            addDisplayOption(displayOption.Showable);
            if (!f.hasGeometryPath())
                addDisplayOption(displayOption.Colorable);
        }
        //addDisplayOption(displayOption.Isolatable);
    }
    public Image getIcon(int i) {
        URL imageURL;
        if (disabled)
            imageURL = this.getClass().getResource("icons/disabledNode.png");
        else
            imageURL = this.getClass().getResource("icons/forceNode.png");
        if (imageURL != null) { 
            return new ImageIcon(imageURL, "Force").getImage();
        } else {
            return null;
        }
    }
   public Image getOpenedIcon(int i) {
        return getIcon(i);
    }

    protected boolean disabled = false;


    @Override
    public boolean isDisabled() {
        return disabled;
    }


    @Override
    public void setDisabled(boolean disabled) {
        //OpenSimDB.getInstance().disableForce(getOpenSimObject(), disabled);
        this.disabled = disabled;
        if (disabled)
            setIconBaseWithExtension("/org/opensim/view/nodes/icons/disabledNode.png");
        else
            setIconBaseWithExtension("/org/opensim/view/nodes/icons/muscleNode.png");
        //refreshNode();

    }


    protected void updateDisabledFlag(final OpenSimObject actuator) {        
        Force f = Force.safeDownCast(actuator);
        //OpenSimContext context = OpenSimDB.getInstance().getContext(f.getModel());
        disabled = f.get_isDisabled();
    }

    public Action[] getActions(boolean b) {
        Action[] superActions = (Action[]) super.getActions(b);        
        // Arrays are fixed size, onvert to a List
        List<Action> actions = java.util.Arrays.asList(superActions);
        // Create new Array of proper size
        Action[] retActions = new Action[actions.size()+1];
        actions.toArray(retActions);
        if (disabled){  // take out display menu ObjectDisplayMenuAction
            for (int i=0; i< retActions.length; i++){
                if (retActions[i] instanceof ObjectDisplayMenuAction){
                    retActions[i] = null; 
                    break;
                }
            }
        }
        try {
            ToggleEnabledStateAction act =(ToggleEnabledStateAction) ToggleEnabledStateAction.findObject(
                    (Class)Class.forName("org.opensim.view.nodes.ToggleEnabledStateAction"), true);
            retActions[actions.size()]=act;
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        return retActions;
    }

    @Override
    public void refreshNode() {
        super.refreshNode();
        updateDisabledFlag(getOpenSimObject());
        setDisabled(disabled);
    }
   
}
