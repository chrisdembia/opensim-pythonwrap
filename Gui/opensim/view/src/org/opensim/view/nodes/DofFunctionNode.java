/*
 *
 * DofFunctionNode
 * Author(s): Peter Loan
 * Copyright (c)  2008, Stanford University, Peter Loan
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
import org.opensim.modeling.TransformAxis;
import org.opensim.view.editors.DofFunctionEditorAction;
import org.opensim.modeling.OpenSimObject;

/**
 *
 * @author Peter Loan
 */
public class DofFunctionNode extends OpenSimObjectNode{
   
   private static ResourceBundle bundle = NbBundle.getBundle(DofFunctionNode.class);
   private String displayName = null;
   private TransformAxis dof = null;
   
   /**
    * Creates a new instance of DofFunctionNode
    */
   public DofFunctionNode(OpenSimObject func, String name, TransformAxis dof) {
      super(func);
      this.displayName = name;
      this.dof = dof;
      setShortDescription(bundle.getString("HINT_FunctionNode"));
      setChildren(Children.LEAF);
   }
   public Image getIcon(int i) {
      URL imageURL = this.getClass().getResource("icons/functionNode.png");
      if (imageURL != null) {
         return new ImageIcon(imageURL, "Function").getImage();
      } else {
         return null;
      }
   }
   public Image getOpenedIcon(int i) {
      return getIcon(i);
   }
   
   /**
    * Display name
    */
   public String getHtmlDisplayName() {
      return displayName;
   }
   
}
