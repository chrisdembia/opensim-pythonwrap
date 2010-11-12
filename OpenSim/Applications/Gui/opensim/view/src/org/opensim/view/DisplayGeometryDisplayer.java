/*
 * DisplayGeometryDisplayer.java
 *
 * Created on April 3, 2010, 1:28 AM
 *
 * Author(s): Ayman Habib
 * Copyright (c)  2005-2010, Stanford University, Ayman Habib
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
package org.opensim.view;

import java.awt.Color;
import org.opensim.modeling.Body;
import org.opensim.modeling.DisplayGeometry;
import org.opensim.modeling.GeometrySet;
import org.opensim.modeling.VisibleObject;
import org.opensim.view.pub.GeometryFileLocator;
import org.opensim.view.pub.ViewDB;
import vtk.FrameActor;
import vtk.vtkActor;
import vtk.vtkBMPReader;
import vtk.vtkImageReader2;
import vtk.vtkJPEGReader;
import vtk.vtkPNGReader;
import vtk.vtkTexture;
import vtk.vtkTransform;

/**
 *
 * @author ayman
 *
 * The visual Representation of one body (bones, base-frame, ..
 */
public class DisplayGeometryDisplayer extends vtkActor 
//        implements ColorableInterface, HidableInterface
{
    DisplayGeometry displayGeometry;
    private Color color=Color.WHITE;
    String modelFilePath;
    /**
     * Creates a new instance of BodyDisplayer
     */
    public DisplayGeometryDisplayer(DisplayGeometry displayGeometry, String modelFilePath) {
        this.displayGeometry = displayGeometry;
        this.modelFilePath=modelFilePath;
        String boneFile = GeometryFileLocator.getInstance().getFullname(modelFilePath,displayGeometry.getGeometryFile(), false);
        GeometryFactory.populateActorFromFile(boneFile, this);
        applyAttributesToActor();        
    }
    
    public void setHidden(boolean toHide) {
        ViewDB.getInstance().toggleObjectDisplay(displayGeometry, !toHide);
        Modified();
        ViewDB.getInstance().repaintAll();
    }
    
    public boolean isHidden() {
        return (ViewDB.getInstance().getDisplayStatus(displayGeometry)!=1);
    }
    
    public void setShading(int shading) {
        ViewDB.getInstance().setObjectRepresentation(displayGeometry, shading, shading);
        Modified();
        ViewDB.getInstance().repaintAll();
    }
    
    public int getShading() {
        return ViewDB.getInstance().getDisplayStatus(displayGeometry);
    }
    
    public void setColor(Color newColor) {
        float[] colorComp = new float[3];
        newColor.getRGBColorComponents(colorComp);
        double[] colorCompDbl = new double[3];
        for(int i=0;i<3;i++) colorCompDbl[i]=colorComp[i];
        ViewDB.getInstance().setObjectColor(displayGeometry, colorCompDbl);
        color = newColor;
    }
    
    public Color getColor() {
        return color;
    }
    
    private void applyAttributesToActor() {        
        // Apply texture if any
        String textureFile = displayGeometry.getTextureFile();
        if (textureFile!=null && !textureFile.equalsIgnoreCase("")){
            // Get full path
            textureFile = GeometryFileLocator.getInstance().getFullname(modelFilePath,displayGeometry.getTextureFile(), false);
            vtkTexture texture = new vtkTexture();
            vtkImageReader2 textureReader=null;
            if (textureFile.toLowerCase().endsWith(".bmp")){
                textureReader = new vtkBMPReader();
                textureReader.SetFileName(textureFile);
                textureReader.Update();
                texture.SetInputConnection(textureReader.GetOutputPort());
            } else if (textureFile.toLowerCase().endsWith(".jpg")){
                textureReader = new vtkJPEGReader();
                textureReader.SetFileName(textureFile);
                textureReader.Update();
                texture.SetInputConnection(textureReader.GetOutputPort());
            }  else if (textureFile.toLowerCase().endsWith(".png")){
                textureReader = new vtkPNGReader();
                textureReader.SetFileName(textureFile);
                textureReader.Update();
                texture.SetInputConnection(textureReader.GetOutputPort());
            }
            if (textureReader!=null){
                texture.InterpolateOn();
                SetTexture(texture);
            }
        } else { // We assume if there's texture then it includes color as well, otherwise we read it in'
            // Color
            double[] dColor = new double[]{1., 1., 1.};
            displayGeometry.getColor(dColor);
            GetProperty().SetColor(dColor);
        }
        // Transform
        double[] rotationsAndTranslations = new double[6];
        displayGeometry.getRotationsAndTranslationsAsArray6(rotationsAndTranslations);
        vtkTransform xform = new vtkTransform();
        setTransformFromArray6(rotationsAndTranslations, xform);
        SetUserTransform(xform);
        /*
         * Scale
         */
        double[] scales = new double[]{1., 1., 1.};
        displayGeometry.getScaleFactors(scales);
        SetScale(scales);
        /**
         * Representation
         */
        applyDisplayPreferenceToActor();
        /**
         * Opacity
         */
        GetProperty().SetOpacity(displayGeometry.getOpacity());
    }
    
    private void setTransformFromArray6(final double[] rotationsAndTranslations, final vtkTransform xform) {
        xform.RotateX(Math.toDegrees(rotationsAndTranslations[0]));
        xform.RotateY(Math.toDegrees(rotationsAndTranslations[1]));
        xform.RotateZ(Math.toDegrees(rotationsAndTranslations[2]));
        xform.Translate(rotationsAndTranslations[3], rotationsAndTranslations[4], rotationsAndTranslations[5]);
    }
    
    protected void applyDisplayPreferenceToActor() {
        
        switch(displayGeometry.getDisplayPreference().swigValue()) {
            case 0:
                SetVisibility(0);
                break;
            case 1:
                GetProperty().SetRepresentationToWireframe();
                break;
            case 2:
            case 3:
                GetProperty().SetRepresentationToSurface();
                GetProperty().SetInterpolationToFlat();
                break;
            case 4:
            default:
                GetProperty().SetRepresentationToSurface();
                GetProperty().SetInterpolationToGouraud();
        }
    }
    
    public void setColor(double[] colorComponents) {
        displayGeometry.setColor(colorComponents);
    }
    
    public void setOpacity(double newOpacity) {
        displayGeometry.setOpacity(newOpacity);
    }
    
    public double getOpacity() {
        return displayGeometry.getOpacity();
    }

    public DisplayGeometry.DisplayPreference getDisplayPreference() {
        return displayGeometry.getDisplayPreference();
    }

    public void setDisplayPreference(DisplayGeometry.DisplayPreference newPref) {
        displayGeometry.setDisplayPreference(newPref);
        applyDisplayPreferenceToActor();
    }
}
