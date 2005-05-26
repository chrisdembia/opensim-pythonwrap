// rdSIMMUtilities.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// INCLUDES
//=============================================================================
#include "rdObject.h"
#include "rdIO.h"
#include "rdSIMMUtilities.h"


//=============================================================================
// EXPORTED STATIC CONSTANTS
//=============================================================================
const double rdSIMMUtilities::PI = acos(-1.0);


//=============================================================================
// BONES
//=============================================================================
//_____________________________________________________________________________
/**
 * Load a SIMM bone from file.  The file must be in ASCII format.
 *
 * Memory for the vertices, normals, face counts, and faces is allocated.  The
 * caller is responsible for deleting this memory.
 *
 * @param aFileName File name.
 * @param rBoundingBox Bounding box (xmin, xmax, ymin, ymax, zmin, zmax).
 * @param rNumVerts Number of vertices.
 * @param rVerts Vertices.
 * @param rNormals Normals at the vertices.
 * @param rNumFaces Number of faces or polygons.
 * @param rFaceCounts Number of vertices in each face.
 * @param rFaces List of vertices in each face.
 * @return Total number of face connections.
 */
int rdSIMMUtilities::
LoadBone(const char *aFileName,double rBoundingBox[6],
			int &rNumVerts,double *&rVerts,double *&rNormals,
			int &rNumFaces,int *&rFaceCounts,int *&rFaces)
{

	// CHECK FILE NAME
	if(aFileName==NULL) return(0);
	if(strlen(aFileName)<=0) return(0);

	// OPEN FILE
	FILE *file = rdIO::OpenFile(aFileName,"r");
	if(file==NULL) return(0);

	// READ HEADER
	char header[rdObject::NAME_LENGTH];
	fscanf(file,"%s",header);
	if(strcmp(header,"NORM_ASCII")!=0) {
		fclose(file);
		return(0);
	}
	printf("rdSIMMUtilities.LoadBone: Reading bone file %s.\n",aFileName);

	// NUMBER OF VERTICES AND FACES
	fscanf(file,"%d %d",&rNumVerts,&rNumFaces);
	if((rNumVerts<=0)||(rNumFaces<=0)) {
		fclose(file);
		return(0);
	}

	// BOUNDING BOX
	fscanf(file,"%lf %lf",&rBoundingBox[0],&rBoundingBox[1]);
	fscanf(file,"%lf %lf",&rBoundingBox[2],&rBoundingBox[3]);
	fscanf(file,"%lf %lf",&rBoundingBox[4],&rBoundingBox[5]);

	// ALLOCATE MEMORY
	rVerts = new double[3*rNumVerts];
	rNormals = new double[3*rNumVerts];
	rFaceCounts = new int[rNumFaces];
	int **faces = new int*[rNumFaces];

	// READ VERTICES AND NORMALS
	int i,I;
	for(I=i=0;i<rNumVerts;i++,I+=3) {
		fscanf(file,"%lf %lf %lf,",&rVerts[I+0],&rVerts[I+1],&rVerts[I+2]);
		fscanf(file,"%lf %lf %lf,",&rNormals[I+0],&rNormals[I+1],&rNormals[I+2]);
	}

	// READ FACE COUNTS AND FACES
	int j,total=0;
	for(i=0;i<rNumFaces;i++) {

		// COUNTS
		faces[i] = NULL;
		fscanf(file,"%d",&rFaceCounts[i]);
		if(rFaceCounts[i]<=0) continue;

		// FACES
		total += rFaceCounts[i];
		faces[i] = new int[rFaceCounts[i]];
		for(j=0;j<rFaceCounts[i];j++) {
			fscanf(file,"%d",&faces[i][j]);
		}
	}

	// CONCATENATE FACES
	rFaces = new int[total];
	for(I=i=0;i<rNumFaces;i++) {
		if(faces[i]==NULL) continue;
		for(j=0;j<rFaceCounts[i];j++,I++) {
			rFaces[I] = faces[i][j];
		}
		delete[] faces[i];
	}
	delete[] faces;

	printf("rdSIMMUtilities.LoadBone: %d face connections.\n",total);
	return(total);
}

