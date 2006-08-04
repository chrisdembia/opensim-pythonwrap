/*
 *
 * WorkflowDescriptor
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
package org.opensim.tracking;

import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmSubject;

/**
 *
 * @author Ayman
 * A class used to package the user input/settings in the workflow wizard. 
 *
 * @todo Look into serializing/deserializing this class to the twf (tracking workflow file)
 */
public class WorkflowDescriptor {
    
    SimmSubject dSubject=null;
    boolean     useOwnModel=false;
    boolean     useOwnMarkers = false;
    transient   SimmModel   dGenericModel = null;
    /**
     * Constructor, Creates a new instance of WorkflowDescriptor
     * 
     * @todo look into why the no-arg constructor for SIMMModel crashes and init subject
     * in constructor instead of using setSubject
     */
    public WorkflowDescriptor()
    {
        dSubject = new SimmSubject();
    }
    /**  init subject to a subject created from an external file */
    public void setSubject(SimmSubject aSubject)
    {
        dSubject = aSubject;
    }

    public SimmSubject getSubject()
    {
        return dSubject;
    }
    
    public SimmModel getModel() {   // Lazily get the Model 
        if (dGenericModel==null && dSubject != null){
            dGenericModel = dSubject.createModel();
        }
        return dGenericModel;
    }
    
    public void setUseOwnModel(boolean b)
    {
        useOwnModel = b;
    }
    
    public boolean getUseOwnModel()
    {
        return useOwnModel;
    }
    
     public void setUseOwnMarkers(boolean b)
    {
        useOwnMarkers = b;
    }
    
    public boolean getUseOwnMarkers()
    {
        return useOwnMarkers;
    }

    void updateCachedValues() {
        String modelFilename = dSubject.getGenericModelParams().getModelFileName();
        setUseOwnModel(!modelFilename.equalsIgnoreCase("Unassigned"));
        setUseOwnMarkers(dSubject.getGenericModelParams().getMarkerSet().getSize()>0);
    }

    void setSubjectFile(String fullPathToSubjectFile) {
        SimmSubject newSubject = new SimmSubject(fullPathToSubjectFile);
        if (newSubject!=null){
            dSubject = newSubject;
            updateCachedValues();
        }
         else
           throw new UnsupportedOperationException("Not yet implemented");
    }
   
}
