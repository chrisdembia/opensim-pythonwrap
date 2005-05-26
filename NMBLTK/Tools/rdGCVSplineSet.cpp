// rdGCVSplineSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdMath.h"
#include "rdGCVSplineSet.h"


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdGCVSplineSet::~rdGCVSplineSet()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdGCVSplineSet::
rdGCVSplineSet()
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a set of generalized cross-validated splines from file.
 *
 * @param aFileName Name of the file.
 */
rdGCVSplineSet::
rdGCVSplineSet(const char *aFileName) :
	rdFunctionSet(aFileName)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a set of generalized cross-validated splines based on the states
 * stored in an rdStorage object.
 *
 * Each column in the rdStorage object is fit with a spline of the specified
 * degree and is named the name of its corresponding column label.  Note that
 * column labels in the storage object are assumed to be tab delimited.
 *
 * @param aDegree Degree of the constructed splines (1, 3, 5, or 7).
 * @param aStore Storage object.
 * @param aErrorVariance Estimate of the variance of the error in the data to
 * be fit.  If negative, the variance will be estimated.  If 0.0, the fit will
 * try to fit the data points exactly- no smoothing.  If
 * positive, the fits will be smoothed according to the specified variance.
 * The larger the error veriance, the more the smoothing.  Note that this is
 * the error variance assumed for each column in the rdStorage.  If different
 * variances should be set for the various columns, you will need to
 * construct each rdGCVSpline individually.
 * @see rdStorage
 * @see rdGCVSpline
 */
rdGCVSplineSet::
rdGCVSplineSet(int aDegree,rdStorage *aStore,double aErrorVariance)
{
	setNull();
	if(aStore==NULL) return;
	setName(aStore->getName());

	// CAPACITY
	rdStateVector *vec = aStore->getStateVector(0);
	if(vec==NULL) return;
	ensureCapacity(2*vec->getSize());

	// CONSTRUCT
	construct(aDegree,aStore,aErrorVariance);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void rdGCVSplineSet::
setNull()
{
	setType("rdGCVSplineSet");
}
//_____________________________________________________________________________
/**
 * Construct a set of generalized cross-validated splines based on the states
 * stored in an rdStorage object.
 *
 * @param aDegree Degree of the constructed splines (1, 3, 5, or 7).
 * @param aStore Storage object.
 * @param aErrorVariance Error variance for the data.
 */
void rdGCVSplineSet::
construct(int aDegree,rdStorage *aStore,double aErrorVariance)
{
	if(aStore==NULL) return;

	// DESCRIPTION
	setDescription(aStore->getDescription());

	// GET COLUMN NAMES
	const char *labels = aStore->getColumnLabels();
	char *name,*names = new char[strlen(labels)+1];
	char tmp[rdObject::NAME_LENGTH];
	strcpy(names,labels);

	// LOOP THROUGHT THE STATES
	int i,nTime=1,nData=1;
	double *times=NULL,*data=NULL;
	rdGCVSpline *spline;
	name = strtok(names,"\t");
	printf("rdGCVSplineSet.construct:  contructing splines...\n");
	for(i=0;nData>0;i++) {

		// GET TIMES AND DATA
		nTime = aStore->getTimeColumn(times,i);
		nData = aStore->getDataColumn(i,data);

		// CHECK
		if(nTime!=nData) {
			printf("\nrdGCVSplineSet.construct: ERR- number of times (%d)",nTime);
			printf(" and number of data (%d) don't agree.\n",nData);
			break;
		}
		if(nData==0) break;

		// GET COLUMN NAME
		// Delimiter is assumed to be a tab.
		name = strtok(NULL,"\t");
		if(name==NULL) {
			sprintf(tmp,"data_%d",i);
			name = tmp;
		}

		// CONSTRUCT SPLINE
		printf("%s\t",name);
		spline = new rdGCVSpline(aDegree,nData,times,data,name,aErrorVariance);

		// ADD SPLINE
		append(spline);
	}
	printf("\n%d splines constructed.\n\n",i);

	// MIN AND MAX TIME
	setMinX(aStore->getFirstTime());
	setMaxX(aStore->getLastTime());

	// CLEANUP
	if(names!=NULL) delete[] names;
	if(times!=NULL) delete[] times;
	if(data!=NULL) delete[] data;
}


//=============================================================================
// SET AND GET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the function at a specified index.
 *
 * @param aIndex Index of the desired function:  0 <= aIndex < getSize().
 * @return Function at index aIndex.  If aIndex is not value NULL is returned.
 */
rdGCVSpline* rdGCVSplineSet::
getGCVSpline(int aIndex)
{
	rdGCVSpline *func = (rdGCVSpline *)get(aIndex);
	return(func);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a storage object (see rdStorage) for this spline \set\ or for some
 * derivative of this spline set.
 *
 * @param aDerivOrder Derivative order.  0 constructs from the spline,
 * 1 constructs from the first derivative of the spline, 2 constructs from
 * the second derivative of the spline, etc.
 * @param aDX Spacing of the data points in the independent variable.  If
 * negative the spacing of the independent variable is taken from the
 * original data, as determined from the first non-NULL spline in the set.
 * aDX has a default value of -1.
 * @return Storage object.  If a valid storage object cannot be constructed
 * NULL is returned.
 * @see rdStorage
 */
rdStorage* rdGCVSplineSet::
constructStorage(int aDerivOrder,double aDX)
{
	if(aDerivOrder<0) return(NULL);
	if(getSize()<=0) return(NULL);

	// GET FIRST NON-NULL SPLINE
	rdGCVSpline *spl;
	int i;
	int n = getSize();
	for(i=0;i<n;i++) {
		spl = getGCVSpline(i);
		if(spl!=NULL) break;
	}
	if(spl==NULL) return(NULL);

	// HOW MANY X STEPS
	double xRange = getMaxX() - getMinX();
	int nSteps;
	if(aDX<=0.0) {
		nSteps = spl->getSize();
	} else {
		nSteps = 10 + (int)(xRange/aDX);
	}

	// CONSTRUCT STORAGE OBJECT
	char name[2*rdObject::NAME_LENGTH];
	if(aDerivOrder==0) {
		sprintf(name,"%s_GCVSpline",getName().c_str());
	} else {
		sprintf(name,"%s_GCVSpline_Deriv_%d",getName().c_str(),aDerivOrder);
	}
	rdStorage *store = new rdStorage(nSteps,name);

	// DESCRIPTION
	store->setDescription(getDescription());

	// SET COLUMN LABELS
	rdGCVSpline *spline;
	int len = n*(rdObject::NAME_LENGTH+4);
	char *labels = new char[len];
	strcpy(labels,"time");
	for(i=0;i<n;i++) {
		spline = getGCVSpline(i);
		if(spline==NULL) {
			sprintf(name,"\tdata_%d",i);
		} else {
			sprintf(name,"\t%s",spline->getName().c_str());
		}
		strcat(labels,name);
	}
	store->setColumnLabels(labels);

	// SET STATES
	double x = getMinX();
	double *y = new double[n];

	// GET ORIGINAL INDEPENDENT VARIABLES

	// LOOP THROUGH THE DATA
	// constant increments
	if(aDX>0.0) {
		while(x <= getMaxX()) {

			// LOOP THROUGH SPLINES
			for(i=0;i<n;i++) {
				spline = getGCVSpline(i);

				// SET Y
				if(spline==NULL) {
					y[i] = rdMath::NAN;
				} else {
					y[i] = spline->evaluate(aDerivOrder,x);
				}
			}

			// APPEND
			store->append(x,n,y);

			// ADVANCE X
			if(x < getMaxX()) {
				x += aDX;
				if(x > getMaxX())  x = getMaxX();

			// FINISHED
			} else {
				break;
			}
		}

	// original independent variable increments
	} else {

		int ix;
		const rdArray<double> &xOrig = spl->getX();
		for(ix=0;ix<nSteps;ix++) {

			// ONLY WITHIN BOUNDS OF THE SET
			if(xOrig[ix]<getMinX()) continue;
			if(xOrig[ix]>getMaxX()) break;

			// LOOP THROUGH SPLINES
			for(i=0;i<n;i++) {
				spline = getGCVSpline(i);

				// SET Y
				if(spline==NULL) {
					y[i] = rdMath::NAN;
				} else {
					y[i] = spline->evaluate(aDerivOrder,xOrig[ix]);
				}
			}

			// APPEND
			store->append(xOrig[ix],n,y);
		}
	}

	// CLEANUP
	if(y!=NULL) delete[] y;
	if(labels!=NULL) delete[] labels;

	return(store);
}
