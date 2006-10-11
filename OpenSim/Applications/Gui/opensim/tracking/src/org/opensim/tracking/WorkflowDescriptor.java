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
    SimmModel   dGenericModel = null;
    SimmModel   ikModel = null;
    // Extra items needed for RRA, CMC, Forward/perturb
    private String      dynamicsModelFile;
    private String      setupRRA_pass1Filename;
    private String      setupRRA_pass2Filename;
    private String      setupCMCFilename;
    private String      setupInvestigationFilename;
    private String      setupIKFilename;
    
    private String      RRAoutputMotionFilename;
    private String      dynamicsDir;
    private String      IKoutfilename;
    public Boolean     stepInProgress=false;
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
        // Until MarkerSet is an object we'll disable the option from the GUI'
        setUseOwnMarkers(false/*dSubject.getGenericModelParams().getMarkerSet().getSize()>0*/);
    }

    void setSubjectFile(String fullPathToSubjectFile) {
        SimmSubject newSubject = new SimmSubject(fullPathToSubjectFile);
        if (newSubject!=null){
            dSubject = newSubject;
            updateCachedValues();
        }
        /* else
           throw new UnsupportedOperationException("Not yet implemented");*/
    }

    public String getSetupRRA_pass1Filename() {
        return setupRRA_pass1Filename;
    }

    public void setSetupRRA_pass1Filename(String setupRRA_pass1Filename) {
        this.setupRRA_pass1Filename = setupRRA_pass1Filename;
    }

    public String getSetupRRA_pass2Filename() {
        return setupRRA_pass2Filename;
    }

    public void setSetupRRA_pass2Filename(String setupRRA_pass2Filename) {
        this.setupRRA_pass2Filename = setupRRA_pass2Filename;
    }

    public String getSetupCMCFilename() {
        return setupCMCFilename;
    }

    public void setSetupCMCFilename(String setupCMCFilename) {
        this.setupCMCFilename = setupCMCFilename;
    }

    public String getRRAoutputMotionFilename() {
        return RRAoutputMotionFilename;
    }

    public void setRRAoutputMotionFilename(String RRAoutputMotionFilename) {
        this.RRAoutputMotionFilename = RRAoutputMotionFilename;
    }

    public String getDynamicsModelFile() {
        return dynamicsModelFile;
    }

    public void setDynamicsModelFile(String dynamicsModelFile) {
        this.dynamicsModelFile = dynamicsModelFile;
    }

    void setDynamicsDir(String string) {
        dynamicsDir = string;
    }

    public String getDynamicsDir() {
        return dynamicsDir;
    }

    public Boolean getStepInProgress() {
        return stepInProgress;
    }

    public void setStepInProgress(Boolean stepInProgress) {
        this.stepInProgress = stepInProgress;
    }

    public String getSetupIKFilename() {
        return setupIKFilename;
    }

    public void setSetupIKFilename(String setupIKFilename) {
        this.setupIKFilename = setupIKFilename;
    }

    String getIKoutfilename() {
        return IKoutfilename;
    }

    public void setIKoutfilename(String IKoutfilename) {
        this.IKoutfilename = IKoutfilename;
    }

 }
