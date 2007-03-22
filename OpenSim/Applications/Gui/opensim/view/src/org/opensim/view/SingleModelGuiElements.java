/*
 * SingleModelVisuals.java
 *
 * Created on November 14, 2006, 5:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import org.opensim.modeling.Model;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.CoordinateSet;

/**
 *
 * @author Pete Loan & Ayman Habib
 */
public class SingleModelGuiElements {
    String preferredUnits; // Place holder for model specific Gui pref.
    Model model;   // model that Gui elements are created for
    
    private static String[] bodyNames=null;
    private static String[] coordinateNames=null;
    
    public SingleModelGuiElements(Model model)
    {
       this.model=model;
    }
    
    public String[] getBodyNames()
    {
       if (bodyNames==null){
         BodySet bodies = model.getDynamicsEngine().getBodySet();
         bodyNames = new String[bodies.getSize()];
         for (int i = 0; i < bodies.getSize(); i++)
            bodyNames[i] = new String(bodies.get(i).getName());
           
       }
       return bodyNames;
    }
    
    public String[] getCoordinateNames()
    {
       if (coordinateNames==null){
         CoordinateSet coordinates = model.getDynamicsEngine().getCoordinateSet();
         coordinateNames = new String[coordinates.getSize()];
         for (int i = 0; i < coordinates.getSize(); i++)
            coordinateNames[i] = new String(coordinates.get(i).getName());
       }
       return coordinateNames;
    }
    
    public String[] getActuatorGroupNames()
    {
       return null;
    }
    
    public String[] getActuatorNamesForGroup(String groupName)
    {
       return null;
    }
}
