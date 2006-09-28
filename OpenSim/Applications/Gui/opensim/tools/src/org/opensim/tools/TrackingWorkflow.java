/*
 *
 * TrackingWorkflow
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
package org.opensim.tools;

import org.opensim.modeling.SimmGenericModelParams;
import org.opensim.modeling.SimmIKParams;
import org.opensim.modeling.SimmMarkerPlacementParams;
import org.opensim.modeling.SimmScalingParams;
import org.opensim.modeling.SimmSubject;

/**
 *
 * @author Ayman, 
 *
 * A Compact representation of the tracking workflow to be used by different ttols and wizards
 * that compose the tracking workflow
 */
public class TrackingWorkflow {
    
    private SimmGenericModelParams genericModelParams=null;
    private SimmScalingParams scalingParams=null;
    private SimmMarkerPlacementParams markerPlacementParams=null;
    private SimmIKParams IKParams=null;
    
    
    /** Creates a new instance of TrackingWorkflow */
    public TrackingWorkflow() {
        genericModelParams = new SimmGenericModelParams();
        scalingParams = new SimmScalingParams();
        markerPlacementParams = new SimmMarkerPlacementParams();
        IKParams = new SimmIKParams();
    }

    public SimmGenericModelParams getGenericModelParams() {
        if (genericModelParams==null){
            genericModelParams=new SimmGenericModelParams();
        }
        return genericModelParams;
    }

    public void setGenericModelParams(SimmGenericModelParams genericModelParams) {
        this.genericModelParams = genericModelParams;
    }

    public SimmScalingParams getScalingParams() {
        if (scalingParams==null){
            scalingParams=new SimmScalingParams();
        }
        return scalingParams;
    }

    public void setScalingParams(SimmScalingParams scalingParams) {
        this.scalingParams = scalingParams;
    }

    public SimmMarkerPlacementParams getMarkerPlacementParams() {
        if (markerPlacementParams==null){
            markerPlacementParams=new SimmMarkerPlacementParams();
        }
        return markerPlacementParams;
    }

    public void setMarkerPlacementParams(SimmMarkerPlacementParams markerPlacementParams) {
        this.markerPlacementParams = markerPlacementParams;
    }

    public SimmIKParams getIKParams() {
        if (IKParams==null){
            IKParams=new SimmIKParams();
        }
        return IKParams;
    }

    public void setIKParams(SimmIKParams IKParams) {
        this.IKParams = IKParams;
    }
    
}
