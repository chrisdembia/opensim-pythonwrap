// suDecompHardUTWalkNoCompPrescribed.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* 
 * This routine is different from suDecompHardUTWalk in that it does not apply 
 * forces due to any of the actuators, gravity, centripetal, or coriolis force.
 * The only forces that are decomposed are those that are applied via force,
 * torque, or generalized force appliers that are set before the decomposition
 * routine is called.  These forces are not decomposed individually - it is their
 * net contribution to the ground reaction force that is determined.  
 * This routine is different from suDecompHardUTWalkNoComp in that the constructor 
 * for this version takes a UTWalking8Prescribed model instead of a UTWalking8 model.
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <math.h>
#include <float.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdSprings.h>
#include <NMBLTK/Models/UTWalking8Prescribed/rdUTWalking8Prescribed.h>
#include <NMBLTK/SQP/rdSQP.h>
#include <NMBLTK/Tools/rdPointConstraint.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include "suDecompTargetNoCompPrescribed.h"
#include "suDecompHardUTWalkNoCompPrescribed.h"


using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================


//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suDecompHardUTWalkNoCompPrescribed::~suDecompHardUTWalkNoCompPrescribed()
{
	if(_x!=NULL) { delete[] _x;  _x=NULL; }
	if(_yCopy!=NULL) { delete[] _yCopy;  _yCopy=NULL; }
	if(_yTmp!=NULL) { delete[] _yTmp;  _yTmp=NULL; }
	if(_xsSprMap!=NULL) { delete[] _xsSprMap;  _xsSprMap=NULL; }
	if(_xsXYZMap!=NULL) { delete[] _xsXYZMap;  _xsXYZMap=NULL; }
	if(_prescribedSpringForceStorage!=NULL) 
		{delete[] _prescribedSpringForceStorage; _prescribedSpringForceStorage=NULL; }
}
//_____________________________________________________________________________
/**
 * Construct a hard-constraint decomposition analysis based on an
 * rdUTWalking8Prescribed model.
 */
suDecompHardUTWalkNoCompPrescribed::suDecompHardUTWalkNoCompPrescribed(rdUTWalking8Prescribed *aModel, 
	rdStorage *aPrescribedSpringForceStorage, bool aModelIsSagittal) : suDecompNoComp(aModel)
{
	setNull();

	// LOCAL WORK ARRAYS
	_yCopy = new double[_model->getNY()];
	_yTmp = new double[_model->getNY()];
	_x = new double[_model->getNX()];

	// MAPPING ARRAYS
	int ns = _model->getNP();
	_xsSprMap = new int[3*ns];
	_xsXYZMap = new int[3*ns];

	// PERFORMANCE CRITERION WEIGHTS
	_wXS = 1.0e-2;
	_wAcc = 1.0;

	// BODY CONSTRAINTS
	clearBodyConstraints();

	// SPRING FORCE STORAGE
	_prescribedSpringForceStorage = aPrescribedSpringForceStorage;

	// SET SAGITTAL
	_modelIsSagittal = aModelIsSagittal;


}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void suDecompHardUTWalkNoCompPrescribed::
setNull()
{
	_c = 0;
	_nxs = 0;
	_xsSprMap = NULL,
	_xsXYZMap = NULL;
	_wXS = 1.0;
	_wAcc = 1.0;
	_point[0] = _point[1] = _point[2] = 0.0;
	_yCopy = NULL;
	_yTmp = NULL;
	_x = NULL;
	_modelIsSagittal = false;

}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the contact point for a specified contact element.
 *
 * @param aIndex Index to the model contact element.
 * @return Pointer to the contact point.  The contact point is a local
 * variable member, so there is no danger of the pointer becoming
 * invalid.
 */
double* suDecompHardUTWalkNoCompPrescribed::
getContactPoint(int aIndex)
{
	_model->getContactPointB(aIndex,_point);
	return(_point);
}
//_____________________________________________________________________________
/**
 * Get the prescribed spring forces storage.
 *
 * @return Prescribed spring forces storage.
 */
rdStorage* suDecompHardUTWalkNoCompPrescribed::
getPrescribedSpringForceStorage()
{
	return(_prescribedSpringForceStorage);
}


//=============================================================================
// DECOMPOSITION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Decompose the ground reaction force by assuming hard constraints.
 */
void suDecompHardUTWalkNoCompPrescribed::
compute(double *aXPrev,double *aYPrev,int step,double dt,double t,
		  double *xt,double *y)
{
	printf("\n\ntime = %lf\n",t);

	// CAST MODEL
	rdUTWalking8Prescribed *model = (rdUTWalking8Prescribed*)_model;

	// INDEX TO ACTIVATIONS
	int iatv = _model->getNQ() + _model->getNU() + _model->getNX();

	// SET CONFIGURATION
	model->set(t,xt,y);

	// GROUND SPRINGS
	int np = model->getNP();
	int s,n,I;
	double svel[rdUTWalking8Prescribed_NS][3];
	double spos[rdUTWalking8Prescribed_NS][3];
	double sfrc[rdUTWalking8Prescribed_NS][3];
	double *sfrcPrescribed = new double[6*rdUTWalking8Prescribed_NS];
	_prescribedSpringForceStorage->getDataAtTime(t*_model->getTimeNormConstant(),6*rdUTWalking8Prescribed_NS,sfrcPrescribed);
	for(s=0;s<rdUTWalking8Prescribed_NS;s++){
		for(n=3;n<6;n++){
			I = rdMtx::ComputeIndex(s,6,n);
			sfrc[s][n-3] = sfrcPrescribed[I];
		}
	}

	// VARIABLE DECLARATIONS
	int i,j;
	double xs[3*rdUTWalking8Prescribed_NS];
	double fs[rdUTWalking8Prescribed_NS][3];
	double g[3];
	model->getGravity(g);
	double dqdt[rdUTWalking8Prescribed_NQ],dudt[rdUTWalking8Prescribed_NU];
	double sacc[rdUTWalking8Prescribed_NS][3],saccOpt[rdUTWalking8Prescribed_NS][3];

	// DETERMINE THE CONTROLS
	determineControls(sfrc);
	if(_nxs<=0) {
		printf("\n\nNo springs in contact!\n\n");
		return;
	}

	// DETERMINE THE CONSTRAINTS
	determineConstraints();

	// CREATE THE OPTIMIZATION OBJECTS
	suDecompTargetNoCompPrescribed *decompTarget =
		new suDecompTargetNoCompPrescribed(_nxs,getNumberConstraints(),this);
	rdFSQP *sqp = new rdFSQP(decompTarget);
	sqp->setMaxIterations(200);
//	sqp->setMaxIterations(400);
	sqp->setNonlinearEqualityConstraintTolerance(1.0e-4);
	sqp->setConvergenceCriterion(1.0e-2);
	sqp->setPrintLevel(0);

	// SOLVE OPTIMIZATION PROBLEM ONLY ONCE

	// SET INITIAL GUESS
	for(i=0;i<_nxs;i++) xs[i] = 1.0;

	sqp->computeOptimalControls(xs,xs);

	// RECORD CONTACT POINT ACCELERATIONS
	if(_recordContactPointAccelerations){
		suComputeContactPointAccelerations(xs, _c, saccOpt);
		_cpaStore[_c]->append(t*model->getTimeNormConstant(),3*np,&saccOpt[0][0]);
	}

	// RESET CONSTRAINT VALUES
	clearBodyConstraintValues();

	// RESET GRAVITY
	model->setGravity(g);

	// SET SPRING FORCES
	setSpringForces(xs,fs);
	for(i=0;i<np;i++) for(j=0;j<3;j++) _f[_c][i][j] = fs[i][j];

	// FILL STORAGE ARRAY
	_fStore[_c]->append(t*model->getTimeNormConstant(),3*np,&_f[_c][0][0]);

	// CLEANUP
	if(decompTarget!=NULL) { delete decompTarget; decompTarget=NULL; }
	if(sqp!=NULL) { delete sqp; sqp=NULL; }
}
//_____________________________________________________________________________
/**
 * Determine the controls for the decomposition.
 */
void suDecompHardUTWalkNoCompPrescribed::
determineControls(double sfrc[][3])
{
	int i;

	// RESET MAPPINGS
	int np = _model->getNP();
	_nxs = 0;
	for(i=0;i<3*np;i++) {
		_xsSprMap[i] = -1;
		_xsXYZMap[i] = -1;
	}

	// SET CONTACT ESTABLISHED
	if(!getUsePresetContactEstablishedSettings()) {
		for(i=0;i<np;i++) {
			if(fabs(sfrc[i][1])<getContactThreshold()) {
				_contactEstablished[i] = false;
			} else {
				_contactEstablished[i] = true;
			}
		}
	}

	// SET CONTROLS MAP
	for(i=0;i<np;i++) {
		if(getContactEstablished(i)) {
			_xsSprMap[_nxs] = i;
			_xsSprMap[_nxs+1] = i;
			_xsSprMap[_nxs+2] = i;
			_xsXYZMap[_nxs] = 0;
			_xsXYZMap[_nxs+1] = 1;
			_xsXYZMap[_nxs+2] = 2;
			_nxs += 3;
		}
	}

	// PRINT
//	printf("\n\nControl Maps:\n");
	for(i=0;i<3*np;i++) {
//		printf("%d: %d %d\n",i,_xsSprMap[i],_xsXYZMap[i]);
	}
//	printf("\n");
}
//_____________________________________________________________________________
/**
 * Determine the constraints for the decomposition.
 */
void suDecompHardUTWalkNoCompPrescribed::
determineConstraints()
{
	int i,ibc,ipc;
	double x[] = {1.0,0.0,0.0};
	double y[] = {0.0,1.0,0.0};
	double z[] = {0.0,0.0,1.0};
	double p[3];
	rdPointConstraint *pc[3];
	int rHindInContact=0;
	int lHindInContact=0;

	// CAST MODEL
	rdUTWalking8Prescribed *model = (rdUTWalking8Prescribed*)_model;

	// CLEAR ANY PREVIOUS CONSTRAINTS
	clearBodyConstraints();

	// RIGHT HINDFOOT
	ibc = 0;

	if(_modelIsSagittal){
	
		for(ipc=0,i=0;i<4;i++) {
	
			// spring 0 hits before 1 and 2 hits before 3 - we only need to constrain foot based 
			// on one rear spring and one fore spring
			if(!_contactEstablished[i] || i==1 || i==2) continue;

			// pc0
			if(ipc==0) {
				_bc[ibc].setID(model->getContactBodyB(i));
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				pc[ipc]->setC0(x);
				pc[ipc]->setC1(y);
			//	pc[ipc]->setC2(z);
				ipc++;	

			// pc1
			} else if(ipc==1) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				//_bc[ibc].constructConstraintsForPoint1();
				pc[ipc]->setC0(y);
				ipc++;
	
			// pc2
			//} else if(ipc==2) {
			//	pc[ipc] = _bc[ibc].getPC(ipc);
			//	pc[ipc]->setID(i);
			//	model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			//	pc[ipc]->setPoint(p);
			//	_bc[ibc].constructConstraintsForPoint2();
			//	ipc++;

			// NO MORE THAN 2 ON A BODY
			} else {
				printf("Enough constraints on body.\n");
			}
		}
		rHindInContact = ipc;
		if(ipc>0) ibc++;	

		// RIGHT TOES
		for(ipc=0,i=4;i<5;i++) {	

			if(!_contactEstablished[i]) continue;

			_bc[ibc].setID(model->getContactBodyB(i));
			pc[0] = _bc[ibc].getPC(ipc);
			pc[0]->setID(i);
			model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			pc[ipc]->setPoint(p);	
	
			// THREE CONSTRAINT DIRECTIONS BECAUSE HINDFOOT IS NOT IN CONTACT
			// Actually, when only one contact point on the hindfoot is in contact, the toe
			// actually has three degrees of freedom because of the metatarsal joint.
			// Therefore, it must be constrained in three directions.
			if(rHindInContact<=1 ) {
				pc[0]->setC0(x);
				pc[0]->setC1(y);
			//	pc[0]->setC2(z);

			// ONE CONSTRAINT DIRECTION ORTHOGONAL TO TO JOINT BECAUSE
			// HINDFOOT IS IN CONTACT
			} else {
				double p2[3],p3[3],p4[3],c0[3];
				model->getPosition(model->getContactBodyB(7),getContactPoint(7),p2);
				model->getPosition(model->getContactBodyB(8),getContactPoint(8),p3);
				model->getPosition(model->getContactBodyB(9),getContactPoint(9),p4);
				double r23[3],r34[3];
				rdMtx::Subtract(1,3,p3,p2,r23);
				rdMtx::Subtract(1,3,p4,p3,r34);
				rdMtx::CrossProduct(r23,r34,c0);
				pc[0]->zeroConstraints();
				pc[0]->setC0(c0);
				pc[0]->normalizeConstraints();
			}
			ipc++;
		}
		if(ipc>0) ibc++;

	} else {

		// RIGHT HINDFOOT
		for(ipc=0,i=0;i<4;i++) {
	
			if(!_contactEstablished[i]) continue;

			// pc0
			if(ipc==0) {
				_bc[ibc].setID(model->getContactBodyB(i));
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				pc[ipc]->setC0(x);
				pc[ipc]->setC1(y);
				pc[ipc]->setC2(z);
				ipc++;

			// pc1
			} else if(ipc==1) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				_bc[ibc].constructConstraintsForPoint1();
				ipc++;

			// pc2
			} else if(ipc==2) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				_bc[ibc].constructConstraintsForPoint2();
				ipc++;

			// NO MORE THAN 3 ON A BODY
			} else {
				printf("Enough constraints on body.\n");
			}
		}
		rHindInContact = ipc;
		if(ipc>0) ibc++;

		// RIGHT TOES
		for(ipc=0,i=4;i<5;i++) {

			if(!_contactEstablished[i]) continue;

			_bc[ibc].setID(model->getContactBodyB(i));
			pc[0] = _bc[ibc].getPC(ipc);
			pc[0]->setID(i);
			model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			pc[ipc]->setPoint(p);

			// THREE CONSTRAINT DIRECTIONS BECAUSE HINDFOOT IS NOT IN CONTACT
			// Actually, when only one contact point on the hindfoot is in contact, the toe
			// actually has three degrees of freedom because of the metatarsal joint.
			// Therefore, it must be constrained in three directions.
			if(rHindInContact<=1 ) {
				pc[0]->setC0(x);
				pc[0]->setC1(y);
				pc[0]->setC2(z);

			// ONE CONSTRAINT DIRECTION ORTHOGONAL TO TO JOINT BECAUSE
			// HINDFOOT IS IN CONTACT
			} else {
				double p2[3],p3[3],p4[3],c0[3];
				model->getPosition(model->getContactBodyB(7),getContactPoint(7),p2);
				model->getPosition(model->getContactBodyB(8),getContactPoint(8),p3);
				model->getPosition(model->getContactBodyB(9),getContactPoint(9),p4);
				double r23[3],r34[3];
				rdMtx::Subtract(1,3,p3,p2,r23);
				rdMtx::Subtract(1,3,p4,p3,r34);
				rdMtx::CrossProduct(r23,r34,c0);
				pc[0]->zeroConstraints();
				pc[0]->setC0(c0);
				pc[0]->normalizeConstraints();
			}
			ipc++;
		}
		if(ipc>0) ibc++;
	}

	// LEFT HINDFOOT

	if(_modelIsSagittal){
	
		for(ipc=0,i=5;i<9;i++) {
	
			// spring 6 hits before 5 and 8 hits before 7 - we only need to constrain foot based 
			// on one rear spring and one fore spring
			if(!_contactEstablished[i] || i==5 || i==7) continue;

			// pc0
			if(ipc==0) {
				_bc[ibc].setID(model->getContactBodyB(i));
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				pc[ipc]->setC0(x);
				pc[ipc]->setC1(y);
			//	pc[ipc]->setC2(z);
				ipc++;	

			// pc1
			} else if(ipc==1) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				//_bc[ibc].constructConstraintsForPoint1();
				pc[ipc]->setC0(y);
				ipc++;
	
			// pc2
			//} else if(ipc==2) {
			//	pc[ipc] = _bc[ibc].getPC(ipc);
			//	pc[ipc]->setID(i);
			//	model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			//	pc[ipc]->setPoint(p);
			//	_bc[ibc].constructConstraintsForPoint2();
			//	ipc++;

			// NO MORE THAN 2 ON A BODY
			} else {
				printf("Enough constraints on body.\n");
			}
		}
		lHindInContact = ipc;
		if(ipc>0) ibc++;	

		// LEFT TOES
		for(ipc=0,i=9;i<10;i++) {	

			if(!_contactEstablished[i]) continue;

			_bc[ibc].setID(model->getContactBodyB(i));
			pc[0] = _bc[ibc].getPC(ipc);
			pc[0]->setID(i);
			model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			pc[ipc]->setPoint(p);	
	
			// THREE CONSTRAINT DIRECTIONS BECAUSE HINDFOOT IS NOT IN CONTACT
			// Actually, when only one contact point on the hindfoot is in contact, the toe
			// actually has three degrees of freedom because of the metatarsal joint.
			// Therefore, it must be constrained in three directions.
			if(lHindInContact<=1 ) {
				pc[0]->setC0(x);
				pc[0]->setC1(y);
			//	pc[0]->setC2(z);

			// ONE CONSTRAINT DIRECTION ORTHOGONAL TO TO JOINT BECAUSE
			// HINDFOOT IS IN CONTACT
			} else {
				double p2[3],p3[3],p4[3],c0[3];
				model->getPosition(model->getContactBodyB(7),getContactPoint(7),p2);
				model->getPosition(model->getContactBodyB(8),getContactPoint(8),p3);
				model->getPosition(model->getContactBodyB(9),getContactPoint(9),p4);
				double r23[3],r34[3];
				rdMtx::Subtract(1,3,p3,p2,r23);
				rdMtx::Subtract(1,3,p4,p3,r34);
				rdMtx::CrossProduct(r23,r34,c0);
				pc[0]->zeroConstraints();
				pc[0]->setC0(c0);
				pc[0]->normalizeConstraints();
			}
			ipc++;
		}
		if(ipc>0) ibc++;

	} else {

		// LEFT HINDFOOT
		for(ipc=0,i=5;i<9;i++) {
	
			if(!_contactEstablished[i]) continue;

			// pc0
			if(ipc==0) {
				_bc[ibc].setID(model->getContactBodyB(i));
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				pc[ipc]->setC0(x);
				pc[ipc]->setC1(y);
				pc[ipc]->setC2(z);
				ipc++;

			// pc1
			} else if(ipc==1) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				_bc[ibc].constructConstraintsForPoint1();
				ipc++;

			// pc2
			} else if(ipc==2) {
				pc[ipc] = _bc[ibc].getPC(ipc);
				pc[ipc]->setID(i);
				model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
				pc[ipc]->setPoint(p);
				_bc[ibc].constructConstraintsForPoint2();
				ipc++;

			// NO MORE THAN 3 ON A BODY
			} else {
				printf("Enough constraints on body.\n");
			}
		}
		lHindInContact = ipc;
		if(ipc>0) ibc++;

		// LEFT TOES
		for(ipc=0,i=9;i<10;i++) {

			if(!_contactEstablished[i]) continue;

			_bc[ibc].setID(model->getContactBodyB(i));
			pc[0] = _bc[ibc].getPC(ipc);
			pc[0]->setID(i);
			model->getPosition(model->getContactBodyB(i),getContactPoint(i),p);
			pc[ipc]->setPoint(p);

			// THREE CONSTRAINT DIRECTIONS BECAUSE HINDFOOT IS NOT IN CONTACT
			// Actually, when only one contact point on the hindfoot is in contact, the toe
			// actually has three degrees of freedom because of the metatarsal joint.
			// Therefore, it must be constrained in three directions.
			if(lHindInContact<=1 ) {
				pc[0]->setC0(x);
				pc[0]->setC1(y);
				pc[0]->setC2(z);

			// ONE CONSTRAINT DIRECTION ORTHOGONAL TO TO JOINT BECAUSE
			// HINDFOOT IS IN CONTACT
			} else {
				double p2[3],p3[3],p4[3],c0[3];
				model->getPosition(model->getContactBodyB(7),getContactPoint(7),p2);
				model->getPosition(model->getContactBodyB(8),getContactPoint(8),p3);
				model->getPosition(model->getContactBodyB(9),getContactPoint(9),p4);
				double r23[3],r34[3];
				rdMtx::Subtract(1,3,p3,p2,r23);
				rdMtx::Subtract(1,3,p4,p3,r34);
				rdMtx::CrossProduct(r23,r34,c0);
				pc[0]->zeroConstraints();
				pc[0]->setC0(c0);
				pc[0]->normalizeConstraints();
			}
			ipc++;
		}
		if(ipc>0) ibc++;
	}

//	printf("suDecompHardUTWalkNoCompPrescribed.determineConstraints: NC = %d\n",
//		getNumberConstraints());
}
//_____________________________________________________________________________
/**
 * Set spring force array based on decomposition controls.
 */
int suDecompHardUTWalkNoCompPrescribed::
getNumberConstraints()
{
	int i,nc;
	for(nc=i=0;i<4;i++) {
		nc += _bc[i].getNC();
	}
	return(nc);
}
//_____________________________________________________________________________
/**
 * Clear all body constraints.
 */
void suDecompHardUTWalkNoCompPrescribed::
clearBodyConstraints()
{
	int i;
	for(i=0;i<4;i++) {
		_bc[i].clear();
	}
}
//_____________________________________________________________________________
/**
 * Clear all constraint values--- set them to 0.0.
 */
void suDecompHardUTWalkNoCompPrescribed::
clearBodyConstraintValues()
{
	int i;
	for(i=0;i<4;i++) {
		_bc[i].clearValues();
	}
}
//_____________________________________________________________________________
/**
 * Set the relavent constraint values.
 */
void suDecompHardUTWalkNoCompPrescribed::
setBodyConstraintValues(int aN,int aID[],double aV[][3])
{
	int i;
	for(i=0;i<4;i++) {
		_bc[i].setValues(aN,aID,aV);
	}
}
//_____________________________________________________________________________
/**
 * Set spring force array based on decomposition controls.
 */
void suDecompHardUTWalkNoCompPrescribed::
setSpringForces(double *aXS,double aFS[][3])
{
	int i,j;

	// ZERO SPRING FORCES
	for(i=0;i<_model->getNP();i++) {
		for(j=0;j<3;j++) aFS[i][j] = 0.0;
	}

	// STEP THROUGH CONTROLS
	for(i=0;i<_nxs;i++) {
		aFS[_xsSprMap[i]][_xsXYZMap[i]] = aXS[i];
	}
}
//_____________________________________________________________________________
/**
 * Apply appropriate component force.
 *
 * @param aC Index of the component.
 */
void suDecompHardUTWalkNoCompPrescribed::
applyComponentForce(int aC)
{
	int i;

	// GET A COPY OF THE STATES AND CONTROLS
	_model->getStates(_yTmp);
	_model->getControls(_x);

	// GRAVITY
	double g0[3] = { 0.0, 0.0, 0.0 };
	double g[3];
	_model->getGravity(g);

	// ZERO GRAVITY
	_model->setGravity(g0);

	// ZERO VELOCITIES
	int nq = _model->getNQ();
	int nu = _model->getNU();
	for(i=0;i<nu;i++) _yTmp[nq+i] = 0.0;

	// SET STATES
	_model->setStates(_yTmp);

	// IMPLEMENT FORCE, TORQUE, AND GENERALIZED FORCE APPLIERS
	rdDerivCallbackSet *callbackSet;
	callbackSet = _model->getDerivCallbackSet();
	callbackSet->applyActuation(_model->getTime(),_x,_yTmp);
}



//==============================================================================
// OPTIMIZATION
//==============================================================================
//------------------------------------------------------------------------------
// PERFORMANCE
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Compute performance given x.
 */
int suDecompHardUTWalkNoCompPrescribed::
suComputePerformance(double *x,double *p)
{
	int i;

	// COMPUTE PERFORMANCE
	*p = 0.0;
	for(i=0;i<_nxs;i++) {
		*p += _wXS*_wXS * x[i]*x[i];
	}

	return(0);
}
//------------------------------------------------------------------------------
// PERFORMANCE
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Compute performance given x.
 */
int suDecompHardUTWalkNoCompPrescribed::
suComputePerformanceGradient(double *x,double *p)
{
	int i;

	// COMPUTE PERFORMANCE
	*p = 0.0;
	for(i=0;i<_nxs;i++) {
		*p += 2.0 * _wXS*_wXS * x[i];
	}

	return(0);
}
//______________________________________________________________________________
/**
 * Compute a constraint given x.
 */
int suDecompHardUTWalkNoCompPrescribed::
suComputeConstraint(double *x,int ic,double *c)
{
	int i,j;

	// COPY THE STATES
	_model->getStates(_yCopy);

	// APPLY COMPONENT FORCES
	applyComponentForce(_c);

	// APPLY SPRING FORCES
	int np = _model->getNP();
	double fs[rdUTWalking8Prescribed_NS][3];
	setSpringForces(x,fs);
	for(i=0;i<np;i++) {
		_model->applyForce(_model->getContactBodyB(i),getContactPoint(i),fs[i]);
	}

	// COMPUTE ACCELERATIONS
	double dqdt[rdUTWalking8Prescribed_NQ],dudt[rdUTWalking8Prescribed_NU];
	_model->computeAccelerations(dqdt,dudt);

	// EVALUATE THE CONSTRAINT
	bool evaluated = false;
	int nc,id,whichC;
	double fsAcc[3];
	for(nc=i=0;i<4;i++) {

		// LOOP ON POINT CONSTRAINTS
		for(j=0;j<3;j++) {
			nc += _bc[i].getPC(j)->getNC();
			if(nc<ic) continue;

			// GET THE ACCELERATION
			id = _bc[i].getPC(j)->getID();
			_model->getAcceleration(_model->getContactBodyB(id),
				getContactPoint(id),fsAcc);

			// WHICH CONSTRAINT DIRECTION
			whichC = _bc[i].getPC(j)->getNC() - (nc-ic) - 1;

			// EVALUATE
			if(whichC==0) {
				*c = _bc[i].getPC(j)->evaluateC0(fsAcc);
				evaluated = true;
			} else if(whichC==1) {
				*c = _bc[i].getPC(j)->evaluateC1(fsAcc);
				evaluated = true;
			} else if(whichC==2) {
				*c = _bc[i].getPC(j)->evaluateC2(fsAcc);
				evaluated = true;
			} else {
				printf("suDecompHardUTWalkNoCompPrescribed.suComputeConstraint: ERROR- invalid C\n");
			}

			// BREAK?
			if(evaluated) break;
		}

		// BREAK?
		if(evaluated) break;
	}

	// WEIGHT FACTOR
	*c *= _wAcc;
	//printf("%d = %lf\n",ic-1,*c);

	// RESTORE THE STATES
	_model->setStates(_yCopy);

	return(0);
}

//______________________________________________________________________________
/**
 * Compute contact point accelerations.
 */
int suDecompHardUTWalkNoCompPrescribed::
suComputeContactPointAccelerations(double *x,int c,double cpa[][3])
{
	int i;

	// COPY THE STATES
	_model->getStates(_yCopy);

	// APPLY COMPONENT FORCES
	applyComponentForce(c);

	// APPLY SPRING FORCES
	int np = _model->getNP();
	double fs[rdUTWalking8Prescribed_NS][3];
	setSpringForces(x,fs);
	for(i=0;i<np;i++) {
		_model->applyForce(_model->getContactBodyB(i),getContactPoint(i),fs[i]);
	}

	// COMPUTE ACCELERATIONS
	double dqdt[rdUTWalking8Prescribed_NQ],dudt[rdUTWalking8Prescribed_NU];
	_model->computeAccelerations(dqdt,dudt);

	// RECORD CONTACT POINT ACCELERATIONS
	for(i=0;i<np;i++) {
		_model->getAcceleration(_model->getContactBodyB(i),getContactPoint(i),
			cpa[i]);
	}

	// RESTORE THE STATES
	_model->setStates(_yCopy);

	return(0);
}
