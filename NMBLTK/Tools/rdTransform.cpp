// rdTransform.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "rdMath.h"
#include "rdMtx.h"
#include "rdTransform.h"
#include "rdPropertyDblArray.h"

//=============================================================================
// STATIC VARIABLES
//=============================================================================
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdTransform::~rdTransform()
{
}

//_____________________________________________________________________________
/**
 * Construct an identity Transform.
 *
 */
rdTransform::rdTransform()
{
	setNull();

	// TYPE
	setType("rdTransform");

	for(int i=0; i < 4; i++)
		for(int j=0; j < 4; j++)
			_matrix4[i][j] = (i==j)?1.0:0.0;

	_angles[0] = _angles[1] = _angles[2] = 0.0;
}

//_____________________________________________________________________________
/**
 * Copy constructor
 *
 */
rdTransform::rdTransform(const rdTransform &aTransform):
rdObject(aTransform)
{
	setNull();

	//Assignment
	(*this) = aTransform;

	for(int i=0; i<3; i++)
		_angles[i] = aTransform._angles[i];
}

//_____________________________________________________________________________
/**
 * Construct a copy of this rdTransform.
 */
rdObject* rdTransform::
copy() const
{
	return(new rdTransform(*this));
}
// Construct a transform to rotate around a vector with specified angle
rdTransform::rdTransform(const double aAngle, double aVector[3])
{

}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdTransform::
setNull()
{
	setupSerializedMembers();

}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdTransform::
setupSerializedMembers()
{
}
//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
rdTransform& rdTransform::operator=(const rdTransform &aTransform)
{
	setNull();
	int i;
	for(i=0; i < 4; i++)
		for(int j=0; j < 4; j++)
			_matrix4[i][j]= aTransform._matrix4[i][j];

	for(i=0; i<3; i++)
		_angles[i] = aTransform._angles[i];
	return (*this);

}
//=============================================================================
// SET / GET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the position vector.
 *
 */
void rdTransform::
getPosition(double pos[3]) const
{
	for(int i=0; i<3; i++)
		pos[i] = _matrix4[i][3];
}
//_____________________________________________________________________________
/**
 * Set the position vector.
 *
 */
void rdTransform::
setPosition(const double pos[3])
{
	for(int i=0; i<3; i++)
		_matrix4[i][3]=pos[i];

}

//_____________________________________________________________________________
/**
 * Get orientation vector from matrix
 *
 * Actually vtk specifies transform using translations and rotations
 * so it's more efficient to store them in this format.
 *
 * @todo check if it's more efficient to make and maintain the matrix and 
 *  if there's an API to set the transformation matrix directly in vtk.
 */
void rdTransform::
getOrientation(double orientation[3]) const
{
  int i;

  // first rotate about y axis
/*  double x2 = _matrix4[2][0];
  double y2 = _matrix4[2][1];
  double z2 = _matrix4[2][2];

  double x3 = _matrix4[1][0];
  double y3 = _matrix4[1][1];
  double z3 = _matrix4[1][2];

  double d1 = sqrt(x2*x2 + z2*z2);

  double cosTheta, sinTheta;
  if (d1 < rdMath::SMALL) 
    {
    cosTheta = 1.0;
    sinTheta = 0.0;
    }
  else 
    {
    cosTheta = z2/d1;
    sinTheta = x2/d1;
    }

  double theta = atan2(sinTheta, cosTheta);
  orientation[1] = -theta/rdMath::DTR;

  // now rotate about x axis
  double d = sqrt(x2*x2 + y2*y2 + z2*z2);

  double sinPhi, cosPhi;
  if (d < rdMath::SMALL) 
    {
    sinPhi = 0.0;
    cosPhi = 1.0;
    }
  else if (d1 < rdMath::SMALL) 
    {
    sinPhi = y2/d;
    cosPhi = z2/d;
    }
  else 
    {
    sinPhi = y2/d;
    cosPhi = (x2*x2 + z2*z2)/(d1*d);
    }

  double phi = atan2(sinPhi, cosPhi);
  orientation[0] = phi/rdMath::DTR;

  // finally, rotate about z
  double x3p = x3*cosTheta - z3*sinTheta;
  double y3p = - sinPhi*sinTheta*x3 + cosPhi*y3 - sinPhi*cosTheta*z3;
  double d2 = sqrt(x3p*x3p + y3p*y3p);

  double cosAlpha, sinAlpha;
  if (d2 < rdMath::SMALL) 
    {
    cosAlpha = 1.0;
    sinAlpha = 0.0;
    }
  else 
    {
    cosAlpha = y3p/d2;
    sinAlpha = x3p/d2;
    }

  double alpha = atan2(sinAlpha, cosAlpha);
  orientation[2] = alpha/rdMath::DTR;*/
	
	for(i=0; i<3; i++)
		orientation[i]=_angles[i]/rdMath::DTR;


}
// Do we need to pass in Order? This may need to be removed in favor of actual
// translate/rotate combinations
void rdTransform::
setOrientation(const double orientation[3])
{
	for(int i=0; i<3; i++)
		_angles[i]=orientation[i];

}
//_____________________________________________________________________________
/**
 * Set transform matrix to identity
 *
 */
void rdTransform::
setIdentity()
{
	rdMtx::Identity(4, (double *)_matrix4);
}
//_____________________________________________________________________________
/**
 * Set transform matrix based on angles, rotation order and preference
 *
 */
void rdTransform::
rotate(const double r[3], const AnglePreference preference, const RotationOrder order)
{
	// Convert angle to radians as this's what low level functions use
	for(int rotAxisIndex=0; rotAxisIndex<3; rotAxisIndex++){
		rdTransform::AxisName nextAxis = getRotationAxis(rotAxisIndex, order);
		switch(nextAxis){
			case X:
				rotateX(r[rotAxisIndex], preference);
				break;
			case Y:
				rotateY(r[rotAxisIndex], preference);
				break;
			case Z:
				rotateZ(r[rotAxisIndex], preference);
				break;
			case NoAxis:
				break;

		}
	}
}
//_____________________________________________________________________________
/**
 * Rotate by r degrees or radians around X axis
 *
 */
void rdTransform::
rotateX(double r, const AnglePreference preference)
{
	// Convert angle to radians as this's what low level functions use
	double rInRadians = (preference==Radians)? r : (r * rdMath::DTR);
	double RotationMatrix[4][4];
	rdMtx::Identity(4, (double *)RotationMatrix);
		// COMPUTE SIN AND COS
	double c = cos(rInRadians);
	double s = sin(rInRadians);
	RotationMatrix[1][1] = RotationMatrix[2][2] = c;
	RotationMatrix[1][2] = s;
	RotationMatrix[2][1] = -s;
	rdMtx::Multiply(4, 4, 4, (double *)_matrix4, (double *)RotationMatrix, (double *)_matrix4);

}
//_____________________________________________________________________________
/**
 * Rotate by r degrees or radians around Y axis
 *
 */
void rdTransform::
rotateY(double r, const AnglePreference preference)
{
	// Convert angle to radians as this's what low level functions use
	double rInRadians = (preference==Radians)? r : (r * rdMath::DTR);
	double RotationMatrix[4][4];
	rdMtx::Identity(4, (double *)RotationMatrix);
		// COMPUTE SIN AND COS
	double c = cos(rInRadians);
	double s = sin(rInRadians);
	RotationMatrix[0][0] = RotationMatrix[2][2] = c;
	RotationMatrix[2][0] = s;
	RotationMatrix[0][2] = -s;
	rdMtx::Multiply(4, 4, 4, (double *)_matrix4, (double *)RotationMatrix, (double *)_matrix4);
}
//_____________________________________________________________________________
/**
 * Rotate by r degrees or radians around Z axis
 *
 */
void rdTransform::
rotateZ(double r, const AnglePreference preference)
{
	// Convert angle to radians as this's what low level functions use
	double rInRadians = (preference==Radians)? r : (r * rdMath::DTR);
	double RotationMatrix[4][4];
	rdMtx::Identity(4, (double *)RotationMatrix);
		// COMPUTE SIN AND COS
	double c = cos(rInRadians);
	double s = sin(rInRadians);
	RotationMatrix[0][0] = RotationMatrix[1][1] = c;
	RotationMatrix[0][1] = s;
	RotationMatrix[1][0] = -s;
	rdMtx::Multiply(4, 4, 4, (double *)_matrix4, (double *)RotationMatrix, (double *)_matrix4);
}
//_____________________________________________________________________________
/**
 * Rotate by r degrees or radians around arbitrary axis
 *
 */
void rdTransform::
rotateAxis(double r, const AnglePreference preference, const double axis[3])
{

}
//_____________________________________________________________________________
/**
 * Translate by double in X direction
 *
 */
void rdTransform::
translateX(const double tX)
{
		_matrix4[0][3] += tX;
}
//_____________________________________________________________________________
/**
 * Translate by double in Y direction
 *
 */
void rdTransform::
translateY(const double tY)
{
		_matrix4[1][3] += tY;
}
//_____________________________________________________________________________
/**
 * Translate by double in Z direction
 *
 */
void rdTransform::
translateZ(const double tZ)
{
		_matrix4[2][3] += tZ;
}

//_____________________________________________________________________________
/**
 * Translate by vector t
 *
 */
void rdTransform::
translate(const double t[3])
{
	for (int i=0; i < 3; i++)
		_matrix4[i][3] += t[i];
}
/**
 * Return 0 for X, 1 for Y 2 for Z index i starts at 0
 * A careful assignment of numbers to enums will make this much smaller 
 * but much harder to debug or understand!
 * where it can be achieved by bitwise operations
 * eg. XYZ=00.01.10 to indicate X then Y then Z
 * XZY=00.10.01 to indicate X then Z then Y
 * ....
 * then we can return ((order << (2*i))& 03)
 */
rdTransform::AxisName rdTransform::
getRotationAxis(const int i, RotationOrder order)
{
	if (i==0){
		switch(order){
			case XYZ:
			case XZY:
				return X;
			case YXZ:
			case YZX:
				return Y;
			case ZXY:
			case ZYX:
				return Z;
			default:
				return NoAxis;
		}
	} 
	else if (i==1) {
		switch(order){
			case YXZ:
			case ZXY:
				return X;
			case XYZ:
			case ZYX:
				return Y;
			case YZX:
			case XZY:
				return Z;
			default:
				return NoAxis;
		}

	} 
	else if (i==2) {
		switch(order){
			case ZYX:
			case YZX:
				return X;
			case XZY:
			case ZXY:
				return Y;
			case XYZ:
			case YXZ:
				return Z;
			default:
				return NoAxis;
		}

	} 
	else 
		return NoAxis;
}
/**
 * Debugging 
 */
void rdTransform::printMatrix()
{
	cout << "Xform: " << endl;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			cout << _matrix4[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}