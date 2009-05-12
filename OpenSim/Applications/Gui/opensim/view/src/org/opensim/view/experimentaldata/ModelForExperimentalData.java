/*
 * 
 * ModelForExperimentalData.java
 *
 * Created on Feb 23, 09
 *
 * Copyright (c)  2006, Stanford University and Ayman Habib. All rights reserved.
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

package org.opensim.view.experimentaldata;

import java.util.Vector;
import org.opensim.modeling.*;

/**
 *
 * @author ayman
 *
 * A fake model to be used for data import. 
 * has 0 states.
 * potentially one body (ground)
 * empty or a frame visuals
 */
public class ModelForExperimentalData extends Model{
    
    MarkerSet markers;
    private AbstractBody    ground;
    AbstractDynamicsEngine dEngine;
    private AnnotatedMotion motionData;
    private ActuatorSet forces;
    /**
     * Creates a new instance of ModelForExperimentalData
     */
    public ModelForExperimentalData(int i, AnnotatedMotion motionData) {
        setName("ExperimentalData_"+i);
        this.motionData=motionData;
        dEngine = new SimbodyEngine();
        markers = new MarkerSet();
        ground = new Body();
        getGround().setName("ground");
        getGround().setDynamicsEngine(dEngine);
        dEngine.setModel(this);
        dEngine.getBodySet().append(getGround());
        setForces(new ActuatorSet());
        getGround().getDisplayer().setNumGeometryFiles(1);
        getGround().getDisplayer().setGeometryFileName(0, "axes.vtp");
        //getGround().getDisplayer().setGeometryFileName(1, "unitCube.vtp");
        
    }

   public int getNumStates() {
       return 0;
   }
    public void getStateNames(ArrayStr rStateNames) {
        return;
    }
    public AbstractDynamicsEngine getDynamicsEngine() {
        return dEngine;
    }
    public ActuatorSet getActuatorSet() {   
        return null;
    }
    
    public MarkerSet getMarkerSet() {
        return markers;
    }
    
    public void addMarkers(Vector<String> experimentalMarkers)
    {
        for (int i=0; i<experimentalMarkers.size(); i++){
            markers.addMarker(experimentalMarkers.get(i), new double[]{0., 0., 0.}, getGround());
        }
    }
    
    public void addForces(Vector<String> recordedForces)
    {
        for (int i=0; i<recordedForces.size(); i++){
            Force newForce = new Force(getGround().getName());
            newForce.setName(recordedForces.get(i));
            getForces().append(newForce);
        }
    }

    public AnnotatedMotion getMotionData() {
        return motionData;
    }

    private void setMotionData(AnnotatedMotion motionData) {
        this.motionData = motionData;
    }

    public AbstractBody getGround() {
        return ground;
    }

    public ActuatorSet getForces() {
        return forces;
    }

    public void setForces(ActuatorSet forces) {
        this.forces = forces;
    }
}
