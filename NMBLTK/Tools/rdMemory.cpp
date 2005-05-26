// rdMemory.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdTools.h"
#include "rdMemory.h"


// CONSTANTS


// STATICS


//=============================================================================
// STRING ARRAYS
//=============================================================================
//-----------------------------------------------------------------------------
// SCIENTIFIC
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Allocate a new array of strings.
 *
 * @param aNumStrings Number of strings.
 * @param aStringLength Length of each string.
 * @return Pointer to the array of strings.
 */
char** rdMemory::
NewArrayOfStrings(int aNumStrings,int aStringLength)
{
	if(aNumStrings<=0) return(NULL);
	if(aStringLength<=0) return(NULL);

	// ALLOCATE ARRAY
	char **array = new char*[aNumStrings];
	if(array==NULL) {
		printf("rdMemory.NewStringArray: ERROR- array allocation failed.\n");
		return(NULL);
	}

	// ALLOCATE STRINGS
	int i,j;
	for(i=0;i<aNumStrings;i++) {
		array[i] = new char[aStringLength];
		if(array[i]==NULL) {
			printf("rdMemory.NewStringArray: ERROR- string allocation failed.\n");
			for(j=0;j<i;j++) { delete[] array[j];  array[j]=NULL;}
			return(NULL);
		}
	}

	return(array);
}
//_____________________________________________________________________________
/**
 * Delete an array of pointers.  Note that both the pointers held by the
 * array and the array itself are deleted.
 *
 * @param aNumStrings Number of strings held in the array.
 * @param aStringArray Pointer to the array of strings.
 */
void rdMemory::
DeleteArrayOfStrings(int aNumStrings,char **aArray)
{
	if(aNumStrings<=0) return;
	if(aArray==NULL) return;

	// DELETE STRINGS
	int i;
	for(i=0;i<aNumStrings;i++) {
		if(aArray[i]!=NULL) {
			delete[] aArray[i];
			aArray[i]=NULL;
		}
	}

	// DELETE ARRAY
	delete[] aArray;
	aArray = NULL;
}
