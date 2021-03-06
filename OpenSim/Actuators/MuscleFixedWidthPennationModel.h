#ifndef OPENSIM_MUSCLEFIXEDWIDTHPENNATIONMODEL_H_
#define OPENSIM_MUSCLEFIXEDWIDTHPENNATIONMODEL_H_
/* -------------------------------------------------------------------------- *
 *                 OpenSim:  MuscleFixedWidthPennationModel.h                 *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Matthew Millard                                                 *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */
//#include "OpenSim/Simulation/osimSimulationDLL.h"
#include "Simbody.h"
#include <OpenSim/Actuators/osimActuatorsDLL.h>
#include <OpenSim/Common/Object.h>

namespace OpenSim {

/**
This is a class that acts as a utility class that contains all of the necessary
kinematic equations required to use a fixed width parallelogram pennation model 
to compute the way the muscle fibers deform as the muscle contracts. A 
fixed width parallelogram pennation model makes a number of assumptions:

1. The width of the parallelogram stays constant \n
2. The area of the parallelogram stays constant. \n
3. Fibers are all parallel, and of the same length \n


The parallelogram pennation model achieves a constant area by permitting the 
parallelogram to shear while maintaining a constant height. The constant area
property is intended to mimic the constant volume property of muscle, which 
arises because muscle is incompressible for all practial purposes.

\image html fig_MuscleFixedWidthPennationModel.png

This class has been coded to eliminate duplicate calculations. Thus if a 
function depends on pennationAngle, or cos(pennationAngle), it will request
this quantity rather than re-compute this value itself.

<B>ASSUMPTIONS</B>

1) This pennation model is compatible with muscle models that assume that the 
effect of the pennation of the fiber on the transmission of force from the fiber
to the tendon is multiplicative.  That is

fiberForceAlongTendon = fiberForce * f()

Where 'f()' is the function that relates the pennation of the fibers to how
much force is transmitted from the fiber to the tendon.\n

2) This pennation model assumes that fiber length, and whole muscle length are
known.

 <B> Usage </B>
    This object should be updated through the set methods provided. 
    These set methods will take care of rebuilding the object correctly. If you
    modify the properties directly, the object will not be rebuilt, and upon
    calling any functions an exception will be thrown because the object is out 
    of date with its properties.

@author Matt Millard
@version 0.0

*/
class OSIMACTUATORS_API MuscleFixedWidthPennationModel: public Object{
OpenSim_DECLARE_CONCRETE_OBJECT(MuscleFixedWidthPennationModel, Object);

public:
//==============================================================================
// PROPERTIES
//==============================================================================
    /** @name Property declarations
    These are the serializable properties associated with this class. **/
    /**@{**/
    OpenSim_DECLARE_PROPERTY(optimal_fiber_length, double,
        "optimal or resting fiber length in units of meters");            
    OpenSim_DECLARE_PROPERTY(optimal_pennation_angle, double,
        "pennation angle in radians of a fiber at its optimal length");     
    OpenSim_DECLARE_PROPERTY(maximum_pennation_angle, double,
        "maximum pennation angle in radians");  
    /**@}**/

//==============================================================================
// PUBLIC METHODS
//==============================================================================
    /**        
    @param optimalFiberLength       The length of the fiber (meters) at
                                    its optimal length

    @param optimalPennationAngle    The angle of the fiber (radians) when 
                                    it is at its optimal angle

    @param maximumPennationAngle    The maximum pennation angle permitted. This
                                    is particularly useful to set for muscle 
                                    models that have a pennation singularity.
                                    For those muscles that do not, this 
                                    parameter must be greater than SimTK::Pi/2,
                                    as a pennation angle of Pi/2 will cause
                                    a singularity in several of the 
                                    internal functions of this class.
                                    


    Constructs a ParallelogramPennationModel object, which dictates how the
    movement of the fiber affects its orientation, and how force is 
    transferred from the fiber to the tendon.

    <B>Conditions:</B>
    \verbatim
        0 <  optimalFiberLength
        0 <= optimalPennationAngle < SimTK::Pi/2
        0 <= maximumPennationAngle < SimTK::Pi/2
    \endverbatim

    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        double maxPenAng = acos(0.001);
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng, maxPenAng);
    \endcode

                                        
    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                        1        2               1
    \endverbatim


    */
    MuscleFixedWidthPennationModel(double optimalFiberLength, 
                                   double optimalPennationAngle,
                                   double maximumPennationAngle);
    ///Default constructor. Populates member data with NaN's and other
    ///obviously wrong values
    MuscleFixedWidthPennationModel();

    bool setOptimalPennationAngle(double aOptimalPennationAngle);

    bool setOptimalFiberLength(double aOptimalFiberLength);

    bool setMaximumPennationAngle(double aMaximumPennationAngle);

    /**
        @returns the maximum pennation angle allowed 
    */
    double getMaximumPennationAngle() const;

    /**
        @returns    the minimum fiber length. For this pennation model the 
                    minimum numerically stable fiber length 
                    is parallelogram_height plus 0.001*optimalFiberLength
    */        
    double getMinimumFiberLength() const;

    /**
        @returns    the minimum fiber length along the tendon. For this 
                    pennation model the minimum numerically stable fiber length 
                    is parallelogram_height plus 0.001*optimalFiberLength
    */        
    double getMinimumFiberLengthAlongTendon() const;

    /**
       This function will clamp fiberLength within 0.001*optimalFiberLengths of 
       the minimum fiber length at which singularities occur.
       @param fiberLength is the length of the fiber in meters
       
    */
    double clampFiberLength(double fiberLength) const;

    /**
        @returns height of the paralleogram (m)
    */
    double getParallelogramHeight() const;

    /**
        @returns optimal fiber length (m) 
    */
    double getOptimalFiberLength() const;

    /**
        @returns the optimal pennation angle (radians) 
    */
    double getOptimalPennationAngle() const;

    /**

    @param fiberLength  The length of the fiber (meters)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @returns The projected length of the fiber along the tendon axis
    */
    double calcFiberLengthAlongTendon(double fiberLength, 
                                        double cosPennationAngle) const;

    /**
    @param fiberLength  The length of the fiber (meters)
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param DpennationAngle_DfiberLength The partial derivative of the 
                                        pennation angle with respect to 
                                        fiber length
    @return the partial derivative of the fiber length along the tendon with
            respect to small changes in fiber length
    */
    double calc_DFiberLengthAlongTendon_DfiberLength(double fiberLength,                                     
                                         double sinPennationAngle, 
                                         double cosPennationAngle,                                    
                                         double DpennationAngle_DfiberLength
                                         ) const;

    /**
    @param fiberLength  The length of the fiber (meters)
    @param fiberVelocity The stretch velocity of the fiber (meters/s)
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param pennationAngularVelocity The angular velocity of the pennation
                                    angle.
    */
    double calcFiberVelocityAlongTendon(double fiberLength, 
        double fiberVelocity, double sinPennationAngle, 
        double cosPennationAngle, double pennationAngularVelocity) const;

   
    /**
    @param fiberLength  The length of the fiber (meters)
    @param fiberVelocity The stretch velocity of the fiber (meters/s)
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param pennationAngularVelocity The angular velocity of the pennation
                                    angle.
    @param DpennationAngle_DfiberLength The partial derivative of the 
                                        pennation angle with respect to 
                                        fiber length
    @param DpennationAngularVelocity_DfiberLength The partial derivative of
                              the pennation angular velocity w.r.t. fiber length    
    @return the partial derivative of the fiber velocity along the tendon with
            respect to a change in fiber length


    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        double maxPenAng = acos(0.1);        
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng, maxPenAng);

        double fibLen = optFibLen*2;
        double penAng = fibKin.calcPennationAngle(fibLen);

        double fibVel = 0.2;
        double penAngVel = fibKin.calcPennationAngularVelocity(
                                tan(penAng), fibLen,fibVel);

        double Dphi_Dlce = fibKin.calc_DPennationAngle_DfiberLength(fibLen);

        double DdlceAT_Dlce=
            fibKin.calc_DFiberVelocityAlongTendon_DfiberLength(fibLen,
                                                               fibVel,
                                                               sin(penAng),
                                                               cos(penAng),
                                                               penAngVel,
                                                               Dphi_Dlce);

    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                         0       2       3       14      6         10
    \endverbatim

    */
    double calc_DFiberVelocityAlongTendon_DfiberLength(
                                    double fiberLength, 
                                    double fiberVelocity, 
                                    double sinPennationAngle, 
                                    double cosPennationAngle, 
                                    double pennationAngularVelocity,
                                    double DpennationAngle_DfiberLength,
                                    double DpennationAngularVelocity_DfiberLength
                                    ) const;
    /**
    @param fiberLength  The length of the fiber (meters)
    @param fiberVelocity The stretch velocity of the fiber (meters/s)
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param pennationAngularVelocity The angular velocity of the pennation
                                    angle.
    @param DpennationAngle_DfiberLength The partial derivative of the 
                                        pennation angle with respect to 
                                        fiber length
    @throws SimTk::Exception
        -cosPennationAngle <= 0
        -fiber length <= 0
    @return the partial derivative of the pennation angular velocity with 
            respect to changes in fiber length


    <B>Conditions:</B>
    \verbatim
        0 <  fiberLength 
        pennationAngle < 90 degrees
    \endverbatim
    */
    double calc_DPennationAngularVelocity_DfiberLength(double fiberLength, 
                                            double fiberVelocity,
                                            double sinPennationAngle, 
                                            double cosPennationAngle, 
                                            double pennationAngularVelocity,
                                            double DpennationAngle_DfiberLength                                            
                                            ) const;

    /**
    This function calculates the pennation angle of the fiber given its
    current length. The pennation angle is saturated at SimTK::Pi/2 for fiber
    lengths that are less than, or equal to, the minimum physical fiber length
    for this pennation model.

    @param fiberLength  the length of the fiber (meters)  

    @returns            the current pennation angle (radians)
  
    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng);

        double fibLen = optFibLen*2;
        double penAng = fibKin.calcPennationAngle(fibLen);
    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                        1        2       1       1               2
    \endverbatim

    */
    double calcPennationAngle(double fiberLength) const;
        
    /**
    This function computes the angular velocity of the fiber.
       
    @param tanPennationAngle The result of tan(pennationAngle)

    @param fiberLength      The length of the fiber (meters)

    @param fiberVelocity    The lengthening/shortening velocity of the fiber
                            in (meters/sec)

    @throws SimTk::Exception 
        -if the fiber length is zero

    @returns                 The angular velocity of the fiber (rad/s)

    <B>Conditions:</B>
    \verbatim
        0 <  fiberLength
    \endverbatim

    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng);

        double fibLen = optFibLen*2;           
        double penAng = fibKin.calcPennationAngle(fibLen);
        double fibVel = optFibLen*3/1.0; //3 fiber lengths / second

        //See constructor example to create fibKin
        double penAngVel = fibKin.calcPennationAngularVelocity(
                                        tan(penAng),fibLen,fibVel);
    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                                    1      1       1               1         
    \endverbatim

    */
    double calcPennationAngularVelocity(double tanPennationAngle,
                                        double fiberLength,  
                                        double fiberVelocity) const;
    /**
    @param fiberLength  The length of the fiber (meters)
    @param fiberVelocity The stretch velocity of the fiber (meters/s)
    @param fiberAcceleration The stretch acceleration of the fiber (meters/s^2) 
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param pennationAngularVelocity The angular velocity of the pennation angle.
    @throws SimTK::Exception 
    -If the fiber length is 0 or less
    -If the cos(pennationAngle) is 0 or less
    @return the angular acceleration of the pennation angle (rad/s^2)
    */
    double calcPennationAngularAcceleration(double fiberLength, 
                                            double fiberVelocity,
                                            double fiberAcceleration,
                                            double sinPennationAngle,
                                            double cosPennationAngle,
                                        double pennationAngularVelocity) const;

    /**
    @param fiberLength  The length of the fiber (meters)
    @param fiberVelocity The stretch velocity of the fiber (meters/s)
    @param fiberAcceleration The stretch acceleration of the fiber (meters/s^2) 
    @param sinPennationAngle The sine of the pennation angle (unitless)
    @param cosPennationAngle The cosine of the pennation angle (unitless)
    @param pennationAngularVelocity The angular velocity of the pennation
                                    angle.
    @param pennationAngularAcceleration the angular acceleration of the 
                                        pennation angle (rad/s^2)
    @return the acceleration of the fiber in the direction of the tendon
    */
    double calcFiberAccelerationAlongTendon(double fiberLength, 
                                            double fiberVelocity,
                                            double fiberAcceleration,
                                            double sinPennationAngle,
                                            double cosPennationAngle,
                                     double pennationAngularVelocity,
                                     double pennationAngularAcceleration) const;

    /**
    This function computes the length of the tendon given the length of 
    the muscle, the length of the fiber, and the current pennation angle.

    @param cosPennationAngle    The cosine of the current pennation angle

    @param fiberLength          The length of the fiber (meters)

    @param muscleLength         The length of the whole muscle (meters)

    @returns length of the tendon (meters)

    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng);

        double fibLen = optFibLen*2;
        double penAng = fibKin.calcPennationAngle(fibLen);
        double mclLen = optFibLen*3;

        double tdnLen = fibKin.calcTendonLength(cos(penAng),fibLen, mclLen);
    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                                                    1       1        1         
    \endverbatim

    */
    double calcTendonLength(double cosPennationAngle,
                            double fiberLength, 
                            double muscleLength) const;

    /**
    This function computes the lengthening velocity (or stretch velocity) of
    the tendon.

    @param cosPennationAngle       The cosine of the current pennation angle

    @param sinPennationAngle       The sine of the current pennation angle

    @param pennationAngularVelocity The angular velocity of the fiber (rad/s)  

    @param fiberLength      The length of the fiber (meters)

    @param fiberVelocity    The lengthening/shortening velocity of the 
                            fiber (m/s)

    @param muscleVelocity   The lengthening/shortening velocity of the 
                            path the of the muscle (m/s)

    @returns the rate of tendon stretching (m/s)

    <B>Example:</B>
    \code
          
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        double maxPenAng = acos(0.1);        
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng, maxPenAng);

        double fibLen = optFibLen*2;            
        double penAng = fibKin.calcPennationAngle(fibLen);

        double fibVel = optFibLen*3/1.0; //3 fiber lengths / second
        double penAngVel = fibKin.calcPennationAngularVelocity(
                                tan(penAng),fibLen);
        double mclLen = optFibLen*3;
        double mclVel = optFibLen*4/1.0; //4 fiber lengths/sec

            
        double tdnVel = fibKin.calcTendonVelocity(cos(penAng),sin(penAng),
                                            penAngVel,fibLen,fibVel,mclVel);
    \endcode

      

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Trig     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                                                    3       2        1         
    \endverbatim
    */
    double calcTendonVelocity(double cosPennationAngle,
                                double sinPennationAngle,
                                double pennationAngularVelocity,
                                double fiberLength,    
                                double fiberVelocity,
                                double muscleVelocity) const;

       

    /**
    The partial derivative of the pennation angle with respect to fiber 
    length.

    @param fiberLength      The length of the fiber (meters)

    @returns the partial derivative of fiber angle 
                    w.r.t. fiber length (rad/m)

    <B>Conditions:</B>
    \verbatim
        parallelogramHeight < fiberLength
    \endverbatim

    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        double maxPenAng = acos(0.1);
        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng, maxPenAng);
            
        double fibLen = optFibLen*2;
        double DphiDlce = fibKin.calc_DPennationAngle_DfiberLength(fibLen);
    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                        Sqrt     Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                        1        2       2       5       1       5
    \endverbatim

    */
    double calc_DPennationAngle_DfiberLength(double fiberLength) const;
                
    /**
    The partial derivative of tendon length with respect to fiber length.

    @param fiberLength          The length of the fiber (meters) 

    @param sinPennationAngle    The sin(pennationAngle)

    @param cosPennationAngle    The cos(pennationAngle)

    @param DpennationAngle_DfiberLength The partial derivative of 
                                pennation angle w.r.t. fiber length (rad/m)

    @returns    the partial derivative of tendon length 
                w.r.t. fiber length in (m/m).

    <B>Conditions:</B>
    \verbatim
        0 <  fiberLength
        parallelogramHeight < fiberLength
    \endverbatim

    <B>Example:</B>
    \code
        double optFibLen = 0.1;
        double optPenAng = SimTK::Pi/4.0;
        double maxPenAng = acos(0.1);

        MuscleFixedWidthPennationModel fibKin = 
                            MuscleFixedWidthPennationModel(
                                optFibLen, optPenAng, maxPenAng);

        double fibLen = optFibLen*2;
        double penAng = fibKin.calcPennationAngle(fibLen);
        double DphiDlce = fibKin.calc_DPennationAngle_DfiberLength(fibLen);

        double DtdnDlce = fibKin.calc_DTendonLength_DfiberLength(fibLen,
                                    sin(penAng), cos(penAng),DphiDlce);
    \endcode

    <B>Computational Costs</B>
    \verbatim
    _______________________________________________________________________
                                Comp.   Div.    Mult.   Add.    Assign.
    _______________________________________________________________________
                                2               2       1       1
    \endverbatim

    */
    double calc_DTendonLength_DfiberLength(double fiberLength, 
                                        double sinPennationAngle,
                                        double cosPennationAngle,
                                        double DpennationAngle_DfiberLength
                                        ) const;
    /**
    @param muscleLength the length of the musculo tendon (meters)
    @param tendonLength the length of the tendon (meters
    @return the fiber length (meters)
    */
    double calcFiberLength(  double muscleLength, 
                                double tendonLength) const;

    /**
    @param cosPennationAngle The cos(pennationAngle)
    @param muscleVelocity    The lengthening velocity of the whole muscle (meters/s)
    @param tendonVelocity    The lengening velocity of the tendon (meters/s)
    @return the lengthening velocity of the fiber (meters/s)
    */
    double   calcFiberVelocity( double cosPennationAngle,                                
                                double muscleVelocity, 
                                double tendonVelocity) const;

    void ensureModelUpToDate();
private:
    void setNull();
    void constructProperties();
    void ensurePropertiesSet() const;
    
    void buildModel();

    /**The height of the parallelogram (in meters). Since the width is 
    constant, the height of the parallelogram is also constant.*/
    double m_parallelogramHeight;
    double m_minimumFiberLength;
    double m_maximumSinPennation;   
    double m_minimumFiberLengthAlongTendon;
};
}
#endif //OPENSIM_MUSCLEFIXEDWIDTHPENNATIONMODEL_H_
