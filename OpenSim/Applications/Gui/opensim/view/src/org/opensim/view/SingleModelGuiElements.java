/*
 * SingleModelVisuals.java
 *
 * Created on November 14, 2006, 5:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.util.Vector;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Model;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.ObjectGroup;

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
    
    /**
     * Get a list of names for model bodies
     */
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
    
    /**
     * Get a list of names for model coordinates
     */
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
    /**
     * Get a list of names for actuator groups in model
     */
    public Vector<String> getActuatorGroupNames()
    {
        Vector<String> ret=new Vector<String>(4);
        ActuatorSet actuators = model.getActuatorSet();
        if (actuators !=null){
            ArrayStr muscleGroupNames = new ArrayStr();
            actuators.getGroupNames(muscleGroupNames);
            for(int i=0; i<muscleGroupNames.getSize();i++){
                ret.add(muscleGroupNames.getitem(i));
                AbstractActuator act = actuators.get(i);
            }
        }
       return ret;
    }
    /**
     * Get Actuators that belong to the passed in muscle group
     */
    public Vector<String> getActuatorNamesForGroup(String groupName)
    {
       Vector<String> ret = new Vector<String>(20);
        ActuatorSet actuators = model.getActuatorSet();
        if (actuators !=null){
           ObjectGroup group=actuators.getGroup(groupName);
           assert(group!=null);
           ArrayPtrsObj objects = group.getMembers();
           for(int i=0; i<objects.getSize();i++){
                ret.add(objects.get(i).getName());
           }
        }
        return ret;
   }
}
