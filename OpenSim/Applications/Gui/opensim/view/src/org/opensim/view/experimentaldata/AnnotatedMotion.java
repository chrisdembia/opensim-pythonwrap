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
 * AnnotatedMotion.java
 *
 * Created on February 19, 2009, 9:16 AM
 *
 */

package org.opensim.view.experimentaldata;

import java.util.Vector;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.StateVector;
import org.opensim.modeling.Storage;
import org.opensim.view.motions.MotionControlJPanel;
import org.opensim.view.motions.MotionDisplayer;
import vtk.vtkTransform;

/**
 *
 * @author ayman
 */
public class AnnotatedMotion extends Storage { // MotionDisplayer needs to know when the attributes have changed
    
    private Vector<String> markerNames=null;
    private Vector<String> forceNames=null;
    private static Vector<String[]> patterns = new Vector<String[]>(6);
    private static Vector<ExperimentalDataItemType> classifications = new Vector<ExperimentalDataItemType>(6);
    private Vector<ExperimentalDataObject> classified=new Vector<ExperimentalDataObject>(10);
    private double[] boundingBox = new double[]{1000., 10000., 10000., -1., -1., -1.};
    private double unitConversion = 1.0;
    private boolean boundingBoxComputed=false;
    private double[] currentRotations = new double[]{0., 0., 0.};
    /** Creates a new instance of AnnotatedMotion 
     * This constructor is called when a trc file is read (so we know it is 
     * Marker only data already.
     */
    public AnnotatedMotion(Storage storage, ArrayStr markerNames) {
        super(storage);
        setupPatterns();
        int rowSize = storage.getSmallestNumberOfStates();
        double[] mins = new double[rowSize];
        double[] maxs = new double[rowSize];
        for(int t=0;t<rowSize;t++){
            mins[t]=100000;
            maxs[t]=-100000;
        }
        getMinMax(mins, maxs);
        int minXIndex=-1;
        int maxXIndex=-1;
        for(int i=0; i<markerNames.getSize(); i++){
            String markerName=markerNames.getitem(i);
            ExperimentalDataObject markerObject = new ExperimentalDataObject(
                    ExperimentalDataItemType.MarkerData, markerName, i*3);
            classified.add(markerObject);
            for(int coord=0; coord<3; coord++){
                //System.out.println("checking index "+(i*3+coord)+"& "+(i*3+coord+3));
                if (getBoundingBox()[coord] > mins[i*3+coord]){
                    getBoundingBox()[coord] = mins[i*3+coord];
                    if (coord==1) minXIndex=i;
                }
                if (getBoundingBox()[coord+3] < maxs[i*3+coord]){
                    getBoundingBox()[coord+3] = maxs[i*3+coord];
                    if (coord==1) maxXIndex=i;
                }
            }
            //System.out.println("-------------------------");

        }
        System.out.println("minY, maxY are at markers "+minXIndex+", "+maxXIndex);
        System.out.println("Bounding box="+
                getBoundingBox()[0]+", "+
                getBoundingBox()[1]+", "+
                getBoundingBox()[2]+", "+
                getBoundingBox()[3]+", "+
                getBoundingBox()[4]+", "+
                getBoundingBox()[5]
                );
        for (int i=0; i<6; i++) getBoundingBox()[i]/= getUnitConversion();
        setBoundingBoxComputed(true);
    }

        /** Creates a new instance of AnnotatedMotion */
    public AnnotatedMotion(Storage storage) {
        super(storage);
        setupPatterns();
        classified=classifyColumns();
    }

    public Vector<String> getMarkerNames() {
        return getNamesOfObjectsOfType(ExperimentalDataItemType.MarkerData);
    }

    public void setMarkerNames(Vector<String> markerNames) {
        this.markerNames = markerNames;
    }

    public Vector<String> getForceNames() {
        return getNamesOfObjectsOfType(ExperimentalDataItemType.ForceData);
    }

    private void setupPatterns() {
        patterns.add(0,  new String[]{"_vx", "_vy", "_vz", "_px", "_py", "_pz"});
        patterns.add(1,  new String[]{"_vx", "_vy", "_vz"});
        patterns.add(2,  new String[]{"_tx", "_ty", "_tz"});
        patterns.add(3,  new String[]{"_px", "_py", "_pz"});
        patterns.add(4,  new String[]{"_1", "_2", "_3"});
        patterns.add(5,  new String[]{"_x", "_y", "_z"});
        classifications.add(0, ExperimentalDataItemType.ForceData);
        classifications.add(1, ExperimentalDataItemType.PointData);
        classifications.add(2, ExperimentalDataItemType.PointData);
        classifications.add(3, ExperimentalDataItemType.PointData);
        classifications.add(4, ExperimentalDataItemType.PointData);
        classifications.add(5, ExperimentalDataItemType.PointData);
        
    }
    public Vector<ExperimentalDataObject> classifyColumns() {
        ArrayStr labels=getColumnLabels();
        int labelsSz = labels.getSize();
        Vector<String> labelsVector = labels.toVector();
        Vector<ExperimentalDataObject> classified = new Vector<ExperimentalDataObject>(4);
        // Start at 1 since label[0] is time
        for (int i=1;i< labelsVector.size(); i++){
            boolean found =false;
            ExperimentalDataItemType columnType = ExperimentalDataItemType.Unknown;
            String label = labelsVector.get(i);
            String baseName="";
            for(int patternIdx=0; patternIdx <6 && !found; patternIdx++) {
                boolean foundPatternAtIdx=true;
                String nextLabel=label;
                // For the pattern (patterns[patternIdx]) check exact match
                for(int k=0; k<patterns.get(patternIdx).length; k++){
                    String testAgainst=patterns.get(patternIdx)[k];
                    baseName=label.substring(0, label.length()-testAgainst.length()); // Could be moved outside k loop
                    if((i+k) > (labelsVector.size()-1)){
                        foundPatternAtIdx=false;
                        break;               
                    }
                    System.out.println("labelsVector.size()"+labelsVector.size());
                    System.out.println("test index"+i+k);
                    label= labelsVector.get(i+k);
                    if (!(label.endsWith(testAgainst))){
                        foundPatternAtIdx=false;
                        break;
                    }
                }
                if (foundPatternAtIdx){
                    found=true;
                    columnType = classifications.get(patternIdx);
                    classified.add(new ExperimentalDataObject(columnType, baseName, i));
                    System.out.println("Found "+columnType.toString()+ " at index "+i);
                    i+=(columnType.getNumberOfColumns()-1);
                    break;
                }
            }
            if (!found){
                classified.add(new ExperimentalDataObject(columnType, label, i));
                System.out.println("Column "+columnType.toString()+ " unclassified");
            }
        }
        return classified;
    }

    public Vector<ExperimentalDataObject> getClassified() {
        return classified;
    }

    public Vector<String> getOtherNames() {
        return getNamesOfObjectsOfType(ExperimentalDataItemType.Unknown);
    }

    private Vector<String> getNamesOfObjectsOfType(ExperimentalDataItemType aDataType) {
        Vector<String> results = new Vector<String>(4);
        if (classified !=null && classified.size()!=0){
            for(ExperimentalDataObject dataObject:classified){
                if (dataObject.getObjectType()==aDataType)
                    results.add(dataObject.getName());
            }     
        }
        return results;
    }

    void hideObject(ExperimentalDataObject dataObject) {
       dataObject.setDisplayed(false);
    }
    
    void showObject(ExperimentalDataObject dataObject) {
        dataObject.setDisplayed(true);
    }

    void toggleObjectTrail(ExperimentalDataObject obj) {
        // We'll create a separate table to keep track ofr trails. '
        MotionDisplayer displayer=MotionControlJPanel.getInstance().getMasterMotion().getDisplayer(this);
        displayer.toggleTrail(obj);
        obj.setTrailDisplayed(!obj.isTrailDisplayed());
    }

    public double[] getBoundingBox() {
        return boundingBox;
    }

    public double getUnitConversion() {
        return unitConversion;
    }

    public void setUnitConversion(double unitConversion) {
        this.unitConversion = unitConversion;
        for (int i=0; i<6; i++) getBoundingBox()[i]/= unitConversion;
    }

    public boolean isBoundingBoxComputed() {
        return boundingBoxComputed;
    }

    public void setBoundingBoxComputed(boolean boundingBoxComputed) {
        this.boundingBoxComputed = boundingBoxComputed;
    }
    
    public void applyTransform(vtkTransform vtktransform) {
        // Should know what data to apply xform to and how
        // for example mrkers are xformed as is but force vectors would not apply translations etc.
        // utilize the "clasified" table
        if (classified !=null && classified.size()!=0){
            for(ExperimentalDataObject dataObject:classified){
                if (dataObject.getObjectType()==ExperimentalDataItemType.PointData ||
                    dataObject.getObjectType()==ExperimentalDataItemType.MarkerData){
                    int startIndex = dataObject.getStartIndexInFileNotIncludingTime();
                
                    Vector<Integer> indices = new Vector<Integer>(3);
                    for (int i=0; i< dataObject.getObjectType().getNumberOfColumns(); i++){
                        indices.add(startIndex+i);
                    }
                    assert(indices.size()==3);
                    double[] point3 = new double[]{0., 0., 0. };
                    for (int rowNumber=0; rowNumber<getSize(); rowNumber++){
                        StateVector row = getStateVector(rowNumber);
                        for(int coord=0; coord <3; coord++) {
                            point3[coord] = row.getData().getitem(startIndex+coord);
                        }
                         double[] xformed = vtktransform.TransformDoublePoint(point3); //inplace
                         for(int coord=0; coord <3; coord++) {
                            row.getData().setitem(startIndex+coord, xformed[coord]);
                        }
                       
                    }
                }
            }
        }
    }

    void saveRotations(double[] d) {
        for(int i=0; i<3; i++)
            getCurrentRotations()[i]=d[i];
    }

    public double[] getCurrentRotations() {
        return currentRotations;
    }

    public void setCurrentRotations(double[] currentRotations) {
        this.currentRotations = currentRotations;
    }
    
    
    public void getMinMax(double[] mins, double[] maxs) {
      int rowSize = getStateVector(0).getSize();
      for(int t=0; t<rowSize;t++){
          mins[t] = getStateVector(0).getData().getitem(t);
          maxs[t] = getStateVector(0).getData().getitem(t);
      }
      for(int i=1; i< getSize(); i++){
          StateVector vec = getStateVector(i);
          // Timestamp
          // Dataitem j
          for(int j=0; j< rowSize; j++){
              if (vec.getData().getitem(j) < mins[j]) 
                  mins[j]=vec.getData().getitem(j);
              if (vec.getData().getitem(j) > maxs[j]) 
                  maxs[j]=vec.getData().getitem(j);
          }
      }
  }

}