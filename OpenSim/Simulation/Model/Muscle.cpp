// Muscle.cpp
// Author: Peter Loan, Ajay Seth
/*
 * Copyright (c)  2011, Stanford University. All rights reserved. 
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

//=============================================================================
// INCLUDES
//=============================================================================
#include "Muscle.h"

#include <OpenSim/Simulation/SimbodyEngine/Body.h>
#include <OpenSim/Simulation/SimbodyEngine/SimbodyEngine.h>
#include "ConditionalPathPoint.h"
#include "PointForceDirection.h"
#include "GeometryPath.h"

#include "Model.h"


#include <OpenSim/Common/XMLDocument.h>

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;
using SimTK::Vec3;

static int counter=0;
//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Muscle::Muscle() : PathActuator()
{
	setNull();
	setupProperties();
	// override the value of default _minControl, _maxControl
	setPropertyValue("min_control", 0.0);
	setPropertyValue("max_control", 1.0);
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
Muscle::~Muscle()
{
	VisibleObject* disp;
	if ((disp = getDisplayer())){
		 // Free up allocated geometry objects
		disp->freeGeometry();
	}
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMuscle Muscle to be copied.
 */
Muscle::Muscle(const Muscle &aMuscle) : PathActuator(aMuscle)
{
	setNull();
	setupProperties();
	copyData(aMuscle);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one Muscle to another.
 *
 * @param aMuscle Muscle to be copied.
 */
void Muscle::copyData(const Muscle &aMuscle)
{
	setPropertyValue("max_isometric_force", aMuscle.getPropertyValue<double>("max_isometric_force"));
	setPropertyValue("optimal_fiber_length", aMuscle.getPropertyValue<double>("optimal_fiber_length"));
	setPropertyValue("tendon_slack_length", aMuscle.getPropertyValue<double>("tendon_slack_length"));
	setPropertyValue("pennation_angle_at_optimal", aMuscle.getPropertyValue<double>("pennation_angle_at_optimal"));
	setPropertyValue("max_contraction_velocity", aMuscle.getPropertyValue<double>("max_contraction_velocity"));
}

//_____________________________________________________________________________
/**
 * Set the data members of this Muscle to their null values.
 */
void Muscle::setNull()
{
	setType("Muscle");
}

//_____________________________________________________________________________
/**
 * Override default implementation by object to intercept and fix the XML node
 * underneath the model to match current version
 */
void Muscle::updateFromXMLNode(SimTK::Xml::Element& aNode, int versionNumber)
{
	if ( versionNumber < XMLDocument::getLatestVersion()){
		if (Object::getDebugLevel()>=1)
			cout << "Updating Muscle object to latest format..." << endl;
		
		if (versionNumber <= 20301){
				SimTK::Xml::element_iterator pathIter = aNode.element_begin("GeometryPath");
				if (pathIter != aNode.element_end()){
					XMLDocument::renameChildNode(*pathIter, "MusclePointSet", "PathPointSet");
					XMLDocument::renameChildNode(*pathIter, "MuscleWrapSet", "PathWrapSet");
					}
				else { // There was no GeometryPath, just MusclePointSet
					XMLDocument::renameChildNode(aNode, "MusclePointSet", "PathPointSet");
					XMLDocument::renameChildNode(aNode, "MuscleWrapSet", "PathWrapSet");
					// Now create a "GeometryPath" node and move MusclePointSet & MuscleWrapSet under it
					SimTK::Xml::Element myPathElement("GeometryPath");
					SimTK::Xml::element_iterator  pathPointSetIter = aNode.element_begin("PathPointSet");
					SimTK::Xml::Node moveNode = aNode.removeNode(pathPointSetIter);
					myPathElement.insertNodeAfter(myPathElement.element_end(),moveNode);
					SimTK::Xml::element_iterator  pathWrapSetIter = aNode.element_begin("PathWrapSet");
					moveNode = aNode.removeNode(pathWrapSetIter);
					myPathElement.insertNodeAfter(myPathElement.element_end(),moveNode);
					aNode.insertNodeAfter(aNode.element_end(), myPathElement);
					}
			XMLDocument::renameChildNode(aNode, "pennation_angle", "pennation_angle_at_optimal");
					}

	}
	// Call base class now assuming aNode has been corrected for current version
	PathActuator::updateFromXMLNode(aNode, versionNumber);
}


//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void Muscle::setupProperties()
{
	addProperty<double>("max_isometric_force",
		"double",
		"Maximum isometric force that the fibers can generate",
		1000.0);
	addProperty<double>("optimal_fiber_length",
		"double",
		"Optimal length of the muscle fibers",
		0.1);
	addProperty<double>("tendon_slack_length",
		"double",
		"Resting length of the tendon",
		0.2);
	addProperty<double>("pennation_angle_at_optimal",
		"double",
		"Angle between tendon and fibers at optimal fiber length",
		0.0);
	addProperty<double>("max_contraction_velocity",
		"double",
		"Maximum contraction velocity of the fibers, in optimal fiberlengths per second",
		10.0);
}

void Muscle::addStateVariables(const Array<std::string> &stateVariableNames)
{
	PathActuator::addStateVariables(stateVariableNames);
	for (int i = 0; i < stateVariableNames.getSize(); ++i)
		addCacheVariable<double>(stateVariableNames[i] + "_deriv", 0., SimTK::Stage::Dynamics);
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @param aMuscle The muscle from which to copy its data
 * @return Reference to this object.
 */
Muscle& Muscle::operator=(const Muscle &aMuscle)
{
	// base class
	PathActuator::operator=(aMuscle);

	copyData(aMuscle);

	return(*this);
}


//=============================================================================
// GENERIC NORMALIZED FORCE-LENGTH-VELOCIY PROPERTIES
//=============================================================================
//_____________________________________________________________________________
/**
 * Evaluate the normalized force-length-velocity curve for the muscle.
 * A simple generic implementation is used here.  Derived classes should
 * override this method for more precise evaluation of the
 * force-length-velocity curve.
 *
 * @param aActivation Activation level of the muscle.  1.0 is full activation;
 * 0.0 is no activation.
 * @param aNormalizedLength Normalized length of the muscle fibers.  1.0 indicates
 * the muscle fibers are at their optimal length.  Lnorm = L / Lo.
 * @param aNormalizedVelocity Normalized shortening velocity of the muscle fibers.
 * Positive values indicate concentric contraction (shortening); negative values
 * indicate eccentric contraction (lengthening).  Normalized velocity is
 * the fiber shortening velocity divided by the maximum shortening velocity times
 * the optimal fiber length.  Vnorm = V / (Vmax*Lo).
 * @return Force normalized by the optimal force.
 */
double Muscle::evaluateForceLengthVelocityCurve(double aActivation, double aNormalizedLength, double aNormalizedVelocity) const
{
	// force-length
	double fLength = exp(-17.33 * fabs(pow(aNormalizedLength-1.0,3)));

	// force-velocity
	double fVelocity = 1.8  -  1.8 / (1.0 + exp( (0.04 - aNormalizedVelocity)/0.18) );

	return aActivation * fLength * fVelocity;
}


//=============================================================================
// GET
//=============================================================================
//-----------------------------------------------------------------------------
// PENNATION ANGLE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the current pennation angle of the muscle fiber(s).
 *
 * @param Pennation angle.
 */
double Muscle::getPennationAngle(const SimTK::State& s) const
{
	return calcPennation( getFiberLength(s),getPropertyValue<double>("optimal_fiber_length"),getPropertyValue<double>("pennation_angle_at_optimal") );
}
//_____________________________________________________________________________
/**
 * Get the length of the tendon.
 *
 * @return Current length of the tendon.
 */
double Muscle::getTendonLength(const SimTK::State& s) const
{
	return getLength(s) - getFiberLengthAlongTendon(s);
}
//_____________________________________________________________________________
/**
 * Get the length of the muscle fiber(s) along the tendon. This method
 * accounts for the pennation angle. 
 *
 * @return Current length of the muscle fiber(s) along the direction of
 * the tendon.
 */
double Muscle::getFiberLengthAlongTendon(const SimTK::State& s) const
{
	return getFiberLength(s) * cos(getPennationAngle(s));
}





//-----------------------------------------------------------------------------
// FORCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the force generated by the muscle fibers. This accounts for
 * pennation angle. That is, the fiber force is computed by dividing the
 * actuator force by the cosine of the pennation angle.
 *
 * @return Force in the muscle fibers.
 */
double Muscle::getFiberForce(const SimTK::State& s) const
{
	double force;
	double cos_penang = cos(getPennationAngle(s));
	if(fabs(cos_penang) < SimTK::Zero) {
		force = SimTK::NaN;
	} else {
		force = getForce(s) / cos_penang;
	}

	return force;
}
//_____________________________________________________________________________
/**
 * Get the active force generated by the muscle fibers.
 *
 * @return Current active force of the muscle fibers.
 */
double Muscle::getActiveFiberForce(const SimTK::State& s) const
{
	return getFiberForce(s) - getPassiveFiberForce(s);
}
//_____________________________________________________________________________
/**
 * Get the active force generated by the muscle fibers along the direction
 * of the tendon.
 *
 * @return Current active force of the muscle fibers along tendon.
 */
double Muscle::getActiveFiberForceAlongTendon(const SimTK::State& s) const
{
	return getActiveFiberForce(s) * cos(getPennationAngle(s));
}
//_____________________________________________________________________________
/**
 * Get the passive force generated by the muscle fibers along the direction
 * of the tendon.
 *
 * @return Current passive force of the muscle fibers along tendon.
 */
double Muscle::getPassiveFiberForceAlongTendon(const SimTK::State& s) const
{
	return getPassiveFiberForce(s) * cos(getPennationAngle(s));
}


//--------------------------------------------------------------------------
// COMPUTATIONS
//--------------------------------------------------------------------------

//_____________________________________________________________________________
/**
 * Utility function to calculate the current pennation angle in a
 * muscle. Pennation angle increases as muscle fibers shorten. The implicit
 * modeling assumption is that muscles have constant width.
 *
 * @param aFiberLength Current fiber length of muscle.
 * @param aOptimalFiberLength Optimal fiber length of muscle.
 * @param aInitialPennationAngle Pennation angle at optimal fiber length (in radians).
 * @return Current pennation angle (in radians).
 */
double Muscle::calcPennation( double aFiberLength, double aOptimalFiberLength,
											    double aInitialPennationAngle) const
{
	if (aFiberLength < SimTK::Eps)
		return 0.0;

   double value = aOptimalFiberLength * sin(aInitialPennationAngle) / aFiberLength;

   if ( isnan(value)  ) 
       return 0.0;
   else if (value <= 0.0 )
      return 0.0;
   else if (value >= 1.0)
		return SimTK_PI/2.0;
   else
      return asin(value);
}

//=============================================================================
// FORCE APPLICATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Apply the muscle's force at its points of attachment to the bodies.
 */
void Muscle::computeForce(const SimTK::State& s, 
							  SimTK::Vector_<SimTK::SpatialVec>& bodyForces, 
							  SimTK::Vector& generalizedForces) const
{
	PathActuator::computeForce(s, bodyForces, generalizedForces);

	// NOTE: Force could be negative, in particular during CMC, when the optimizer is computing
	// gradients, it will setForce(+1) and setForce(-1) to compute the derivative with respect to force.
	if (getForce(s) < -SimTK::SqrtEps) {
		string msg = getType()+"::computeForce, muscle force < 0 for muscle '" + getName() +"' ";
		//cout << msg << " at time = " << s.getTime() << endl;
		//throw Exception(msg);
    }
}

void Muscle::updateGeometry(const SimTK::State& s) const
{
	updPropertyValue<GeometryPath>("GeometryPath").updateGeometry(s);
}