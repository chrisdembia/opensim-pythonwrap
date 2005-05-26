// INCLUDES
#include "suMarkerSet.h"
#include "rdModel.h"
#include <RD/Tools/suScaleSet.h>
#include "rdBody.h"

using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suMarkerSet::~suMarkerSet(void)
{}

//_____________________________________________________________________________
/**
 * Constructor of a markerSet from a file.
 */
suMarkerSet::suMarkerSet(const string& markersFileName):
rdSet<suMarker>(markersFileName)
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Default constructor of a markerSet.
 */
suMarkerSet::suMarkerSet():
rdSet<suMarker>()
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Copy constructor of a markerSet.
 */
suMarkerSet::suMarkerSet(const suMarkerSet& aMarkerSet):
rdSet<suMarker>(aMarkerSet)
{
	setNull();
	*this = aMarkerSet;
}

//--------------------------------------------------------------------------
// OPERATORS
//--------------------------------------------------------------------------
#ifndef SWIG

suMarkerSet& suMarkerSet::
operator=(const suMarkerSet &aMarkerSet)
{
	rdSet<suMarker>::operator=(aMarkerSet);
	return (*this);
}
#endif
//_____________________________________________________________________________
/**
 * Check if the marker set uses weights 
 */
bool suMarkerSet::
usesWeights() const
{
	bool wighted = false;

	for(int i=0; i < getSize(); i++){
		suMarker* nextMarker = get(i);
		if (nextMarker->getWeight()!= 1.0){
			wighted = true;
			break;
		}
	}

	return wighted;
}

void suMarkerSet::setNull()
{
	setType("suMarkerSet");
	setName("MarkerSet");
}
//_____________________________________________________________________________
/**
 * Bind markers in the marker set to the model.
 * Works by going through the markers and for each one finding the body associated
 * Currently this function returns true if any marker maps to model and so  
 * it does not give complete feedback as
 * to if there're markers that didn't map to model segments
 * @param model is the model used for binding
 * 
 * @return true if any marker is bound to model else false. 
 */
bool suMarkerSet::
bindMarkersToModel(rdModel *model)
{
	bool bound = false;
	for(int i=0; i < getSize(); i++){
		suMarker* nextMarker = get(i);
		const string& refSegmentName = nextMarker->getReferenceSegmentName();
		int bodyIndex = model->getBodyIndex(refSegmentName);
		if (bodyIndex>=0){	// rdSDFast::GROUND = -1
			nextMarker->setRefSegment(bodyIndex);
			rdBody *body = model->getBody(bodyIndex);
			body->addObserver(*nextMarker);
			bound = true;
		}
	}
	return bound;
}
//_____________________________________________________________________________
/**
 * Get names of markers in the marker set
 */
void suMarkerSet::
getMarkerNames(rdArray<string>& aMarkerNamesArray)
{
	for(int i=0; i < getSize(); i++){
		suMarker* nextMarker = get(i);
		aMarkerNamesArray.append(nextMarker->getName());
	}

}
//_____________________________________________________________________________
/**
 * Scale marker set by a set of scale factors
 */
void suMarkerSet::
scale(suScaleSet& scaleSet)
{
	rdArray<double>	scaleFactors(1.0, 3);
	for(int i=0; i < getSize(); i++){
		suMarker* nextMarker = get(i);
		const string& refSegmentName = nextMarker->getReferenceSegmentName();
		bool found = false;
		for (int j=0; j < scaleSet.getSize() && !found; j++){
			suScale* nextScale = scaleSet.get(j);
			if (nextScale->getSegmentName() == refSegmentName){
				found = true;
				nextScale->getScaleFactors(scaleFactors);
				nextMarker->scaleBy(scaleFactors);
			}
		}
	}

}
//_____________________________________________________________________________
/**
 * Allow markers to be presented in geometry frame rather than COM frame
 * and use this function to make marker locations relative to COM.
 *
 * @param model is the model whose segment COMs are to be used
 */
void suMarkerSet::
makeRelativeToCom(rdModel *model)
{
	rdArray<double>	scaleFactors(1.0, 3);
	rdArray<double>	loc(0.0, 3);

	for(int i=0; i < getSize(); i++){
		suMarker* nextMarker = get(i);
		const int markerSegment = nextMarker->getRefSegment();
		rdBody *segment = model->getBody(markerSegment);
		double	segmentCom[3];
		segment->getCenterOfMass(segmentCom);

		nextMarker->getLocation(loc);
		// Adjust by Com
		for(int j=0; j <3; j++){
			loc[j] -= segmentCom[j];
		}
		nextMarker->setLocation(loc);
	}
}
//_____________________________________________________________________________
/**
 * Retrieve the set of markers in the set
 */
const rdSet<suMarker> &
suMarkerSet::getMarkers() const
{
	return (*this);
}