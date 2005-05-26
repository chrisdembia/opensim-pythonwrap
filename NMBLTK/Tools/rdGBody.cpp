// rdGBody.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdMath.h"
#include "rdMtx.h"
#include "rdLine.h"
#include "rdGBody.h"
#include "rdGBodies.h"


//=============================================================================
// STATIC VARIABLES
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdGBody::~rdGBody()
{
	if(_vertices!=NULL) { delete _vertices;  _vertices=NULL; }
	if(_edges!=NULL) { delete _edges;  _edges=NULL; }
	if(_triangles!=NULL) { delete _triangles;  _triangles=NULL; }
}

//_____________________________________________________________________________
/**
 * Construct an empty graphics body.
 */
rdGBody::rdGBody()
{
	setNull();

	// TYPE
	setType("rdGBody");
}

//_____________________________________________________________________________
/**
 * Construct a graphics body from an XML Element.
 *
 * @param aElement XML element.
 */
rdGBody::rdGBody(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();
	if(_node==NULL) return;

	// DATA
	updateData();

	// VERTICES
	DOMElement *elmt;
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"rdVertices");
	if(elmt==NULL) {
		printf("rdGBody(aElement): ERROR- no vertices found for %s.\n",
			getName());
	} else {
		_vertices = new rdVertices(elmt);
	}

	// EDGES
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"rdEdges");
	if(elmt!=NULL) {
		_edges = new rdEdges(elmt);
	}
	updateEdgeIndices();

	// TRIANGLES
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"rdTriangles");
	if(elmt==NULL) {
		printf("rdGBody(aElement): WARN- no triangles found for %s.\n",
			getName());
	} else {
		_triangles = new rdTriangles(elmt);
	}
	if(_triangles!=NULL) _triangles->setVertices(_vertices);
	updateTriangleIndices();

	// CHILD BODIES
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"rdGBodies");
	if(elmt!=NULL) {
		_bodies = new rdGBodies(elmt);
	}

	// COMPUTE BOUNDS
	computeBounds();
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdGBody::
setNull()
{
	_origin[0] = _origin[1] = _origin[2] = 0.0;
	_x[0] = 1.0;   _x[1] = 0.0;  _x[2] = 0.0;
	_y[0] = 0.0;   _y[1] = 1.0;  _y[2] = 0.0;
	_z[0] = 0.0;   _z[1] = 0.0;  _z[2] = 1.0;
	_px[0] = _py[0] = _pz[0] = _origin[0];
	_px[1] = _py[1] = _pz[1] = _origin[1];
	_px[2] = _py[2] = _pz[2] = _origin[2];
	_edges = NULL;
	_vertices = NULL;
	_triangles = NULL;
	_bodies = NULL;
	_lower[0] = _lower[1] = _lower[2] = -1.0;
	_upper[0] = _upper[1] = _upper[2] = -1.0;
	_density = 1.0;
	_mass = 0.0;
	_com[0] = _com[1] = _com[2] = 0.0;
	rdMtx::Assign(3,3,0.0,&_inertia[0][0]);
}



//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// ORIGIN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the origin of the body.
 *
 * Whenever the origin is set, the points _px, _py, and _pz, which are used
 * to set desired directions for the coordinate axes of the body, are also
 * set to the value of the origin
 *
 * @param aX New x coordinate.
 * @param aY New y coordinate.
 * @param aZ New z coordinate.
 */
void rdGBody::
setOrigin(double aX,double aY,double aZ)
{
	printf("rdGBody.setOrigin: %lf %lf %lf\n",aX,aY,aZ);
	_origin[0] = aX;
	_origin[1] = aY;
	_origin[2] = aZ;

	// RESET AXIS POINTS
	setPX(aX,aY,aZ);
	setPY(aX,aY,aZ);
	setPZ(aX,aY,aZ);
}
//_____________________________________________________________________________
/**
 * Get the origin of the body.
 *
 * @param aOrigin Array into which to put the current origin.
 */
void rdGBody::
getOrigin(double aOrigin[3]) const
{
	if(aOrigin==NULL) return;
	aOrigin[0] = _origin[0];
	aOrigin[1] = _origin[1];
	aOrigin[2] = _origin[2];
}

//-----------------------------------------------------------------------------
// PX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a point along the desired x axis of the body.
 *
 * @param aX New x coordinate.
 * @param aY New y coordinate.
 * @param aZ New z coordinate.
 */
void rdGBody::
setPX(double aX,double aY,double aZ)
{
	_px[0] = aX;
	_px[1] = aY;
	_px[2] = aZ;
}

//-----------------------------------------------------------------------------
// PY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a point along the desired y axis of the body.
 *
 * @param aX New x coordinate.
 * @param aY New y coordinate.
 * @param aZ New z coordinate.
 */
void rdGBody::
setPY(double aX,double aY,double aZ)
{
	_py[0] = aX;
	_py[1] = aY;
	_py[2] = aZ;
}

//-----------------------------------------------------------------------------
// PZ
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a point along the desired z axis of the body.
 *
 * @param aX New x coordinate.
 * @param aY New y coordinate.
 * @param aZ New z coordinate.
 */
void rdGBody::
setPZ(double aX,double aY,double aZ)
{
	_pz[0] = aX;
	_pz[1] = aY;
	_pz[2] = aZ;
}

//-----------------------------------------------------------------------------
// DENSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the density of this body.
 *
 * @param aDensity Density.
 */
void rdGBody::
setDensity(double aDensity)
{
	_density = aDensity;
	if(_density<0.0) _density = 0.0;
}
//_____________________________________________________________________________
/**
 * Get the density of this body.
 *
 * @return Density.
 */
double rdGBody::
getDensity() const
{
	return(_density);
}

//-----------------------------------------------------------------------------
// MASS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the mass of this body.
 *
 * @param aMass Mass.
 */
void rdGBody::
setMass(double aMass)
{
	_mass = aMass;
	if(_mass<0.0) _mass = 0.0;
}
//_____________________________________________________________________________
/**
 * Get the mass of this body.
 *
 * @return Mass.
 */
double rdGBody::
getMass() const
{
	return(_mass);
}

//-----------------------------------------------------------------------------
// CENTER OF MASS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the center of mass of this body.
 *
 * @param aCOM Center of mass.
 */
void rdGBody::
setCenterOfMass(const double aCOM[3])
{
	if(aCOM==NULL) return;
	rdMtx::Assign(1,3,aCOM,_com);
}
//_____________________________________________________________________________
/**
 * Get the center of mass of this body.
 *
 * @param rCOM Center of mass.
 */
void rdGBody::
getCenterOfMass(double rCOM[3]) const
{
	if(rCOM==NULL) return;
	rdMtx::Assign(1,3,_com,rCOM);
}

//-----------------------------------------------------------------------------
// INERTIA TENSOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the inertia tensor of this body.
 *
 * @param aInertiaTensor Inertia tensor.
 */
void rdGBody::
setInertiaTensor(const double aI[9])
{
	if(aI==NULL) return;
	rdMtx::Assign(1,9,aI,&_inertia[0][0]);
	_inertia[1][0] = _inertia[0][1];
	_inertia[2][0] = _inertia[0][2];
	_inertia[2][1] = _inertia[1][2];
}
//_____________________________________________________________________________
/**
 * Get the inertia tensor of this body.
 *
 * @param aInertiaTensor Inertia tensor.
 */
void rdGBody::
getInertiaTensor(double rI[9]) const
{
	if(rI==NULL) return;
	rdMtx::Assign(1,9,&_inertia[0][0],rI);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// TRANSLATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Translate the vertices of this body by a specified amount.
 *
 * @param aX Amount to translate in the X direction.
 * @param aY Amount to translate in the Y direction.
 * @param aZ Amount to translate in the Z direction.
 */
void rdGBody::
translate(double aX,double aY,double aZ)
{
	if(_vertices==NULL) return;
	_vertices->translate(aX,aY,aZ);
}

//-----------------------------------------------------------------------------
// ROTATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Rotate a the vertices of this body about the X, Y, or Z axis by a
 * specified amount.
 *
 * @param aXYZ Specify whether to rotate about the X (aXYZ=0), Y (aXYZ=1),
 * or Z (aXYZ=2) axes.  If aXYZ is not 0, 1, or 2, no rotation is performed.
 * @param aRadians Amount of rotation in radians.
 */
void rdGBody::
rotate(int aXYZ,double aRadians)
{
	if(_vertices==NULL) return;
	_vertices->rotate(aXYZ,aRadians);
}

//_____________________________________________________________________________
/**
 * Rotate a the vertices of this body about a point about the X, Y, or Z axis
 * by a specified amount.
 *
 * @param aXYZ Specify whether to rotate about the X (aXYZ=0), Y (aXYZ=1),
 * or Z (aXYZ=2) axes.  If aXYZ is not 0, 1, or 2, no rotation is performed.
 * @param aRadians Amount of rotation in radians.
 * @param Point about which to rotate.
 */
void rdGBody::
rotate(int aXYZ,double aRadians,const double aP[3])
{
	if(_vertices==NULL) return;
	_vertices->translate(-aP[0],-aP[1],-aP[2]);
	_vertices->rotate(aXYZ,aRadians);
	_vertices->translate(aP[0],aP[1],aP[2]);
}


//=============================================================================
// UTILITIES
//=============================================================================
//-----------------------------------------------------------------------------
// INSIDE BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine whether or not a point is inside this body.  This method assumes
 * that this body is a closed volume.  If this body is not closed, the
 * returned result may not be meaningful.
 *
 * @param aPoint Point to be examined.
 * @return True if point is inside. False if point is not inside.
 */
bool rdGBody::
isInside(const double aPoint[3]) const
{
	if(aPoint==NULL) return(false);
	if(_triangles==NULL) return(false);

	// CREATE A VERTICAL LINE PASSING THROUGH aPoint
	double direction[] = { 0.0, 1.0, 0.0 };
	rdLine line(aPoint[0],aPoint[1],aPoint[2],direction);


	// CHECK INTERSECTION OF LINE WITH ALL TRIANGLES IN BODY
	rdTriangle *tri;
	rdTriangle::INTERSECTION type;
	double r[3],p1[3],p2[3];
	int nIntersections,nInterior=0,nEdge=0;
	int i;
	//printf("Intersecting with %d triangles...\n",_triangles->getFirstEmpty());
	for(i=0;i<_triangles->getFirstEmpty();i++) {

		// GET TRIANGLE
		tri = _triangles->getTriangle(i);
		if(tri==NULL) continue;

		// GET INTERSECTION WITH TRIANGLE
		type = tri->computeIntersection(&line,p1,p2);
		if(type==rdTriangle::NONE) {
			//printf("none\n");
			continue;
		}

		// DIRECTION- ACCEPT ONLY POSITIVE
		rdMtx::Subtract(1,3,p1,aPoint,r);
		if(rdMtx::DotProduct(3,direction,r) < 0.0) continue;

		// INTERIOR
		if(type==rdTriangle::POINT_INTERIOR) {
			nInterior++;
			//printf("interior\n");

		// EDGE
		} else if((type==rdTriangle::POINT_EDGE01) ||
						(type==rdTriangle::POINT_EDGE12) ||
							(type==rdTriangle::POINT_EDGE20)) {
			//printf("edge\n");
			nEdge++;

		// UNHANDLED
		} else {
			printf("unhandled\n");
		}
	}

	// TOTAL NUMBER OF INTERSECTIONS
	nIntersections = nInterior + nEdge/2;

	// IF nIntersections IS ODD, POINT IS INSIDE
	if((nIntersections % 2) == 1) {
		//printf("rdGBody.isInside: n=%d  p=%lf,%lf,%lf\n",nIntersections,
		//	aPoint[0],aPoint[1],aPoint[2]);
		return(true);
	}

	return(false);
}

//-----------------------------------------------------------------------------
// INERTIAL PROPERTIES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Estimate the inertial properties of this body.
 *
 * The inertial properties include mass, center of mass, and the inertia
 * tensor.  These properties are estimated by assuming a uniform density and
 * integrating over the volume of the body.  A cube of finite dimension
 * (aCubeSize) is used as the volume element dx*dy*dz for performing the
 * integration.
 *
 * If aCubeSize has a value less than or equal to zero, the size of the
 * cube is chosen to be 0.01 times the size of the smallest dimension
 * of the body.  That is, aCubeSize = 0.01*(upper[i]-lower[i]), i=0,1, or 2,
 * whichever is smallest.
 *
 * @param aCubeSize Length of the side of the cube used to integrate over
 * the volume of the body.
 */
void rdGBody::
estimateInertialProperties(double aCubeSize)
{
	// INITIALIZE
	_mass = 0.0;
	rdMtx::Assign(1,3,0.0,_com);
	rdMtx::Assign(3,3,0.0,&_inertia[0][0]);

	// BOUNDS
	computeBounds();

	// CUBE SIZE
	double dd = aCubeSize;
	double dy,dz;
	if(dd<=0.0) {
		dd = 0.025*(_upper[0]-_lower[0]);
		dy = 0.025*(_upper[1]-_lower[1]);
		dz = 0.025*(_upper[2]-_lower[2]);
		if(dy<dd) dd = dy;
		if(dz<dd) dd = dz;
		if(dd<=0.0) {
			printf("rdGBody.estimateInertialProperties: ERROR- Body has no ");
			printf("volume.\n");
			return;
		}
	}
	printf("rdGBody.estimateInertialProperties: volume element size = %lf.\n",
		dd);

	// INTEGRATE OVER THE BOUNDING CUBE
	int nAccepted=0,nRejected=0;
	double p[3];  // Position of cube center of mass.
	double dm = 1000.0 * _density * dd * dd * dd;  // Mass of cube.
	double Iaa = dm * dd * dd / 6.0;      // Moment of inertia of cube
	printf("rdGBody.estimateInertialProperties: volume element mass = %lf.\n",
		dm);
	// Z
	for(p[2]=_lower[2]+0.5*dd;p[2]<_upper[2];p[2]+=dd) {

		// Y
		for(p[1]=_lower[1]+0.5*dd;p[1]<_upper[1];p[1]+=dd) {

			// X
			for(p[0]=_lower[0]+0.5*dd;p[0]<_upper[0];p[0]+=dd) {

				// IF p OUTSIDE CONTINUE
				if(!isInside(p)) {
					//printf("Rejecting: %8.4lf %8.4lf %8.4lf\n",p[0],p[1],p[2]);
					nRejected++;
					continue;
				}
				//printf("Accepting: %8.4lf %8.4lf %8.4lf\n",p[0],p[1],p[2]);
				nAccepted++;

				// MASS
				_mass += dm;

				// CENTER OF MASS
				_com[0] += dm*p[0];
				_com[1] += dm*p[1];
				_com[2] += dm*p[2];
				
				// MOMENTS OF INERTIA
				_inertia[0][0] += Iaa  +  dm*(p[1]*p[1] + p[2]*p[2]);
				_inertia[1][1] += Iaa  +  dm*(p[0]*p[0] + p[2]*p[2]);
				_inertia[2][2] += Iaa  +  dm*(p[0]*p[0] + p[1]*p[1]);

				// PRODUCTS OF INERTIA
				_inertia[0][1] += -dm * p[0] * p[1];
				_inertia[0][2] += -dm * p[0] * p[2];
				_inertia[1][2] += -dm * p[1] * p[2];
			}
		}
	}

	// PRODUCTS OF INERTIA
	_inertia[1][0] = _inertia[0][1];
	_inertia[2][0] = _inertia[0][2];
	_inertia[2][1] = _inertia[1][2];

	// FINAL CALCULATIONS
	if(_mass<=0.0) {
		printf("rdGBody.estimateInertialProperties: WARN- body has zero mass.\n");
		return;
	}
	double massRecip = 1.0/_mass;
	rdMtx::Multiply(1,3,_com,massRecip,_com);

	// PRINT
	printf("\nGraphics Body: %s\n",getName());
	printf("\tvolume elements = %d (accepted)  %d (rejected)  %d (total)\n",
		nAccepted,nRejected,nAccepted+nRejected);
	printf("\tdensity = %8.16le\n",_density);
	printf("\tmass = %8.16lf\n",_mass);
	printf("\tcom = %8.16lf %8.16lf %8.16lf\n",_com[0],_com[1],_com[2]);
	printf("\tinertia = \n");
	rdMtx::Print(3,3,&_inertia[0][0],16);
}

//-----------------------------------------------------------------------------
// FRAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute a new body frame.
 *
 * This procedure is done based on what has been set for the origin, px, py,
 * and pz.  All vertices in the body are translated so that the new origin
 * lies at the point originally set for the origin, then they are rotated
 * so that if possible, the x axis passes through px, the y axis through py,
 * and the z axis through pz.  When finished, the origin will be (0,0,0).
 */
void rdGBody::
computeNewFrame()
{
	// DETERMIN NEW AXES
	rdMtx::Subtract(1,3,_px,_origin,_x);
	rdMtx::Subtract(1,3,_py,_origin,_y);
	rdMtx::Subtract(1,3,_pz,_origin,_z);
	double magx = rdMtx::Normalize(3,_x,_x);
	double magy = rdMtx::Normalize(3,_y,_y);
	double magz = rdMtx::Normalize(3,_z,_z);

	// DETERMIN ROTATIONS
	// For simplicity, only rotations about the y axis are considered for now.
	double angy;
	if(magx<rdMath::SMALL) {
		angy = 0.0;
	} else {
		angy = atan2(_x[2],_x[0]);
	}
	printf("rdGBody.computeNewFrame: Rotating by %lf degrees\n",
		rdMath::RTD*angy);

	// TRANSLATE
	translate(-_origin[0],-_origin[1],-_origin[2]);

	// ROTATE
	if(angy!=0.0) rotate(1,angy);

	// RESET ORIGIN
	setOrigin(0.0,0.0,0.0);
}

//-----------------------------------------------------------------------------
// EDGE INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the edge indices.
 */
void rdGBody::
updateEdgeIndices()
{
	if(_edges==NULL) return;
	_edges->updateIndices(_vertices);
}

//-----------------------------------------------------------------------------
// TRIANGLE INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the triangle indices.
 */
void rdGBody::
updateTriangleIndices()
{
	if(_triangles==NULL) return;
	_triangles->updateIndices();
}

//-----------------------------------------------------------------------------
// BOUNDS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the bounds of this body.
 */
void rdGBody::
computeBounds()
{
	computeLowerBounds();
	computeUpperBounds();
}

//_____________________________________________________________________________
/**
 * Compute the lower bounds of this body.
 */
void rdGBody::
computeLowerBounds()
{
	_lower[0] = _lower[1] = _lower[2] = -1.0;

	int i;
	double val;
	rdV3D *v3d;
	for(i=0;i<_vertices->getFirstEmpty();i++) {

		// GET VERTEX
		v3d = _vertices->getVertex(i);
		if(v3d==NULL) continue;

		// INITIALIZE TO FIRST VERTEX
		if(i==0) {
			_lower[0] = v3d->getX();
			_lower[1] = v3d->getY();
			_lower[2] = v3d->getZ();

		// COMPARE
		} else {
			// X
			val = v3d->getX();
			if(val<_lower[0]) _lower[0] = val;

			// Y
			val = v3d->getY();
			if(val<_lower[1]) _lower[1] = val;

			// Z
			val = v3d->getZ();
			if(val<_lower[2]) _lower[2] = val;
		}
	}
}

//_____________________________________________________________________________
/**
 * Compute the upper bounds of this body.
 */
void rdGBody::
computeUpperBounds()
{
	_upper[0] = _upper[1] = _upper[2] = 1.0;

	int i;
	double val;
	rdV3D *v3d;
	for(i=0;i<_vertices->getFirstEmpty();i++) {

		// GET VERTEX
		v3d = _vertices->getVertex(i);
		if(v3d==NULL) continue;

		// INITIALIZE TO FIRST VERTEX
		if(i==0) {
			_upper[0] = v3d->getX();
			_upper[1] = v3d->getY();
			_upper[2] = v3d->getZ();

		// COMPARE
		} else {
			// X
			val = v3d->getX();
			if(val>_upper[0]) _upper[0] = val;

			// Y
			val = v3d->getY();
			if(val>_upper[1]) _upper[1] = val;

			// Z
			val = v3d->getZ();
			if(val>_upper[2]) _upper[2] = val;
		}
	}
}


//-----------------------------------------------------------------------------
// BONE FILE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Print a SIMM bone file.
 *
 * @param aFileName Name of output file.
 */
void rdGBody::
printBoneFile(const char *aFileName)
{
	if((_vertices==NULL)||(_triangles==NULL)) {
		printf("rdGBody.printBoneFile: ERROR- not a valid surface.\n");
		return;
	}

	// UPDATE TRIANGLE INDICES
	updateTriangleIndices();

	// COMPUTE BOUNDS
	computeBounds();

	// CONSTRUCT FILE NAME
	const char *namePtr = aFileName;
	char name[rdObject_NAME_LENGTH];
	if(namePtr==NULL) {
		strcpy(name,getName());
		strcat(name,".asc");
		namePtr = name;
	}

	// OPEN FILE
	FILE *fp = fopen(namePtr,"w");
	if(fp==NULL) {
		printf("rdGBody.printBoneFile: ERROR- could not open file %s.\n",
			namePtr);
	}

	// WRITE HEADER
	fprintf(fp,"NORM_ASCII\n");

	// NUMBER OF VERTICES AND TRIANGLES
	fprintf(fp,"%d",_vertices->getFirstEmpty());
	fprintf(fp," %d\n",_triangles->getFirstEmpty());

	// BOUNDS
	fprintf(fp,"%lf %lf %lf",_lower[0],_lower[1],_lower[2]);
	fprintf(fp," %lf %lf %lf\n",_upper[0],_upper[1],_upper[2]);

	// VERTICES
	rdV3D *v3d;
	int i;
	for(i=0;i<_vertices->getFirstEmpty();i++) {
		v3d = _vertices->getVertex(i);
		if(v3d==NULL) {
			fprintf(fp,"0.0 0.0 0.0 0.0 0.0 0.0\n");
			continue;
		}
		fprintf(fp,"%lf %lf %lf ",v3d->getX(),v3d->getY(),v3d->getZ());
		fprintf(fp,"1.0 0.0 0.0\n");
	}

	// POLYGONS
	rdTriangle *tri;
	for(i=0;i<_triangles->getFirstEmpty();i++) {
		tri = _triangles->getTriangle(i);
		if(tri==NULL) {
			fprintf(fp,"0.0 0.0 0.0 0.0 0.0 0.0\n");
			continue;
		}
		fprintf(fp,"3 %d %d %d\n",tri->getVertexIndex(0),
			tri->getVertexIndex(1),tri->getVertexIndex(2));
	}
	fprintf(fp,"\n");

	// CLOSE FILE
	fclose(fp);
}


//=============================================================================
// XML
//=============================================================================
//-----------------------------------------------------------------------------
// UPDATE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 *
 * @param aDeep If true, update this object and all its child objects
 * (that is, member variables that are rdObject's); if false, update only
 * the member variables that are not rdObject's.
 */
void rdGBody::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObject::updateObject(aDeep);

	// MEMBER DATA
	updateData();

	// DEEP?
	if(!aDeep) return;

	// VERTICES
	if(_vertices!=NULL) _vertices->updateObject();

	// EDGES
	if(_edges!=NULL) _edges->updateObject();

	// TRIANGLES
	if(_triangles!=NULL) _triangles->updateObject();

	// BODIES
	if(_bodies!=NULL) _bodies->updateObject();
}
//_____________________________________________________________________________
/**
 * Update the member data of this object based on its XML node.  Member
 * objects (children) are not updated.
 */
void rdGBody::
updateData()
{
	if(_node==NULL) return;

	// VARIABLES
	DOMElement *elmt;
	double *data;

	// ORIGIN
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"origin");
	int n = rdXMLNode::GetDblArray(elmt,data);
	if(data==NULL) {
		printf("rdGBody(aElement): WARN- no origin.\n");
		return;
	} else if(n!=3) {
		printf("rdGBody(aElement): ERROR- origin has %d coordinates.\n",n);
		delete[] data;
	} else {
		setOrigin(data[0],data[1],data[2]);
		delete[] data;
	}

	// PX
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"px");
	n = rdXMLNode::GetDblArray(elmt,data);
	if(data==NULL) {
		printf("rdGBody(aElement): WARN- no px.\n");
	} else if(n!=3) {
		printf("rdGBody(aElement): ERROR- px has %d coordinates.\n",n);
		delete[] data;
	} else {
		setPX(data[0],data[1],data[2]);
		delete[] data;
	}

	// DENSITY
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"density");
	n = rdXMLNode::GetDblArray(elmt,data);
	if(n==1) {
		setDensity(data[0]);
		delete[] data;
	}

	// MASS
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"mass");
	n = rdXMLNode::GetDblArray(elmt,data);
	if(n==1) {
		setMass(data[0]);
		delete[] data;
	}

	// CENTER OF MASS
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"com");
	n = rdXMLNode::GetDblArray(elmt,data);
	if(n==3) {
		setCenterOfMass(data);
		delete[] data;
	}

	// INERTIA TENSOR
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"inertiaTensor");
	n = rdXMLNode::GetDblArray(elmt,data);
	if(n==9) {
		setInertiaTensor(data);
		delete[] data;
	}

}

//-----------------------------------------------------------------------------
// UPDATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node representing this object.
 *
 * @param aDeep If true, update the XML node of this object AND the XML nodes
 * of all class members that are rdObjects (child nodes);  if false, update
 * only the XML node of this object without updating the XML nodes of its
 * children.
 */
void rdGBody::
updateNode(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObject::updateNode();

	// ORIGIN
	DOMElement *elmt;
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"origin");
	if(elmt==NULL) elmt = rdXMLNode::AppendNewElement(_node,"origin");
	rdXMLNode::SetDblArray(elmt,3,_origin);

	// PX
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"px");
	rdXMLNode::SetDblArray(elmt,3,_px);

	// DENSITY
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"density");
	if(elmt==NULL) elmt = rdXMLNode::AppendNewElement(_node,"density");
	rdXMLNode::SetDblArray(elmt,1,&_density);

	// MASS
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"mass");
	if(elmt==NULL) elmt = rdXMLNode::AppendNewElement(_node,"mass");
	rdXMLNode::SetDblArray(elmt,1,&_mass);

	// CENTER OF MASS
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"com");
	if(elmt==NULL) elmt = rdXMLNode::AppendNewElement(_node,"com");
	rdXMLNode::SetDblArray(elmt,3,_com);

	// INERTIA TENSOR
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"inertiaTensor");
	if(elmt==NULL) elmt = rdXMLNode::AppendNewElement(_node,"inertiaTensor");
	rdXMLNode::SetDblArray(elmt,9,&_inertia[0][0]);


	// DEEP?
	if(!aDeep) return;

	// VERTICES
	if(_vertices!=NULL) _vertices->updateNode();

	// EDGES
	if(_edges!=NULL) _edges->updateNode();

	// TRIANGLES
	if(_triangles!=NULL) _triangles->updateNode();

	// BODIES
	if(_bodies!=NULL) _bodies->updateNode();

	// Note- lower and upper bounds are not updated because they can be
	// recomputed every time.
}


