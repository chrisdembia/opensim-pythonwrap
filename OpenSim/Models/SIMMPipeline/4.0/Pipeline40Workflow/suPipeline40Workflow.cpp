// suPipeline40Workflow.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <cstdio>
#include <OpenSim/Tools/GCVSplineSet.h>
#include <OpenSim/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>
#include <OpenSim/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40-helper.h>
#include "suPipeline40Workflow.h"
#include "suPipeline40Workflow-helper.h"



using namespace OpenSim;
using namespace std;
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
suPipeline40Workflow::~suPipeline40Workflow()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suPipeline40Workflow::
suPipeline40Workflow(const std::string &aParametersFileName,
	ActuatorSet *aActuators,ContactForceSet *aContacts) :
	suPipeline40("",aParametersFileName,aActuators,aContacts,false)
{
	initPipeline("", aParametersFileName);
}


//_____________________________________________________________________________
/**
 * Initialize the SIMM Dynamics Pipeline.
 */
void suPipeline40Workflow::
initPipeline(const std::string &workpath, const std::string &paramfile)
{
	// PIPELINE INITIALIZATION
	try {
      string path = workpath + '/';
      string file = paramfile;

	  cout<<"\n\nStartup file = "<<file<<endl<<endl;
      DP_MainStartup_Workflow(_dpd,path.c_str(),file.c_str() ); // populate globals and dpd_

	// ERROR - SHOULD EXIT
   } catch (...) {

		cout<<"\n\nThe SIMM Dynamics Pipeline did not initialize properly.";
		cout<<endl<<endl;
      cleanup();

		string msg = "Pipeline initialization failure.";
		throw Exception(msg,__FILE__,__LINE__);
   }  
	
	// INITIAL STATES
   constructInitialStates();
   
   // CONSTRUCT NAMES
   constructNames();
}


//=============================================================================
// GET AND SET
//=============================================================================


//=============================================================================
// FOR RRA - ADDED BY CHAND, 2/3/2006, AND CLAY, 5/24/2006)
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the constrained coordinates for a simulation.
 *
 * @param y Array of states containing all coordinates.
 */
void suPipeline40Workflow::
computeConstrainedCoordinates(double* y)
{
	computeConstrainedCoords(sdm,y);
}
//_____________________________________________________________________________
/**
 * From a potentially partial specification of the generalized coordinates,
 * form a complete storage of the generalized coordinates (q's) and
 * generalized speeds (u's).
 *
 * @param aQIn Storage containing the q's or a subset of the q's.  Rotational
 * q's should be in degrees.
 * @param rQComplete Storage containing all the q's.  If q's were not
 * in aQIn, the values are set to 0.0.  When a q is constrained, its value
 * is altered to be consistent with the constraint.  The caller is responsible
 * for deleting the memory associated with this storage.
 * @param rUComplete Storage containing all the u's.  The generalized speeds
 * are obtained by spline fitting the q's and differentiating the splines.
 * When a u is constrained, its value is altered to be consisten with the
 * constraint.  The caller is responsible for deleting the memory
 * associated with this storage.
void suPipeline40Workflow::
formCompleteStorages(const OpenSim::Storage &aQIn,
	OpenSim::Storage *&rQComplete,OpenSim::Storage *&rUComplete)
{
	cout<<"suPipeline40Workflow.formCompleteStorages: ERR- this routine should not be executed!\n\n";
	int i;
	int nq = getNumCoordinates();
	int nu = getNumSpeeds();

	// Get coordinate file indices
	string qName,columnLabels;
	Array<int> index(-1,nq);
	columnLabels = "time";
	for(i=0;i<nq;i++) {
		qName = getCoordinateName(i);
		columnLabels += "\t";
		columnLabels += qName;
		index[i] = aQIn.getColumnIndex(qName);
	}

	// Extract Coordinates
	double time;
	Array<double> data(0.0);
	Array<double> q(0.0,nq);
	Storage *qStore = new Storage();
	qStore->setName("GeneralizedCoordinates");
	qStore->setColumnLabels(columnLabels.c_str());
	int size = aQIn.getSize();
	StateVector *vector;
	int j;
	for(i=0;i<size;i++)
	{
		vector = aQIn.getStateVector(i);
		data = vector->getData();
		time = vector->getTime();

		for(j=0;j<nq;j++) {
			q[j] = 0.0;
			if(index[j]<0) continue;
			q[j] = data[index[j]];
		}

		qStore->append(time,nq,&q[0]);
	}

	// Convert to radians
	convertDegreesToRadians(qStore);

	// Compute generalized speeds
	GCVSplineSet tempQset(5,qStore);
	Storage *uStore = tempQset.constructStorage(1);

	// Compute constraints
	Array<double> qu(0.0,nq+nu);
	int qSize = qStore->getSize();
	int uSize = uStore->getSize();
	cout<<"qSize = "<<qSize<<endl<<endl;
	cout<<"uSize = "<<uSize<<endl<<endl;
	rQComplete = new Storage();
	rUComplete = new Storage();
	for(i=0;i<size;i++)
	{
		qStore->getTime(i,time);
		qStore->getData(i,nq,&qu[0]);
		uStore->getData(i,nq,&qu[nq]);
		computeConstrainedCoordinates(&qu[0]);
		rQComplete->append(time,nq,&qu[0]);
		rUComplete->append(time,nu,&qu[nq]);
	}

	// Convert back to degrees
	convertRadiansToDegrees(rQComplete);
	convertRadiansToDegrees(rUComplete);

	// Compute storage object for simulation
	rQComplete->setColumnLabels(columnLabels.c_str());
	rUComplete->setColumnLabels(columnLabels.c_str());
}
 */
