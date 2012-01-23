/*
 * Copyright (c)  2005-2008, Stanford University
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
/*
 * MotionEvent.java
 *
 * Created on June 16, 2006, 8:59 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.motions;

import java.util.EventObject;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;

/**
 *
 * @author Ayman Habib
 */
public class MotionEvent extends EventObject {
    
    public enum Operation{Open, Close, CurrentMotionsChanged, Modified, Assoc};
    private Model model;
    Storage motion;
    Operation op= Operation.Open;
    /**
     * Creates a new instance of MotionEvent
     */
    public MotionEvent(Object source, Model model, Storage motion, Operation op) {
        super(source);
        this.setModel(model);
        this.motion = motion;
        this.op = op;
    }
    public MotionEvent(Object source, Operation op) {
        super(source);
        this.setModel(null);
        this.motion = null;
        this.op = op;
    }
        
    public Model getModel()
    {
        return model;
    }
    
    public Storage getMotion()
    {
        return motion;
    }
    
    public MotionEvent.Operation getOperation()
    {
        return op;
    }

    public void setModel(Model model) {
        this.model = model;
    }
}
