/*
 *
 * JointsChildren
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view.nodes;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import javax.swing.event.ChangeListener;
import org.openide.nodes.Children;
import org.openide.nodes.Node;
import org.opensim.modeling.AbstractJoint;
import org.opensim.modeling.Model;
import org.opensim.modeling.JointSet;

/**
 *
 * @author Ayman Habib
 */
public class JointsChildren extends Children.Keys {
    
    private ChangeListener listener;
    Model model;
    
    JointsChildren(Model m) {
        model = m;
    }
    protected void addNotify() {
        refreshList();  // Called when parent node is expanded
    }
    protected void removeNotify() {
        setKeys(Collections.EMPTY_SET);
    }
    protected Node[] createNodes(Object key) {
        AbstractJoint jnt = model.getDynamicsEngine().getJointSet().get((String) key);
        return new Node[] { new OneJointNode(jnt) };
    }
    
    private void refreshList() {
        List<String> keys = new ArrayList<String>();
        JointSet jointSet = model.getDynamicsEngine().getJointSet();

        for (int jointNum=0; jointNum < jointSet.getSize(); jointNum++ ){
             keys.add(jointSet.get(jointNum).getName());
        }
        setKeys(keys);
    }
    
}
