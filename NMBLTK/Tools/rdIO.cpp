// rdIO.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdTools.h"
#include <time.h>
#include "rdIO.h"
#include <direct.h>

// CONSTANTS
const int rdIO::STRLEN = rdIO_STRLEN;
const int rdIO::STRING_INCREMENT = rdIO_STRING_INCREMENT;

// STATICS
bool rdIO::_Scientific = false;
int rdIO::_Pad = 8;
int rdIO::_Precision = 8;
char rdIO::_DoubleFormat[] = "%16.8lf";


//=============================================================================
// FILE NAME UTILITIES
//=============================================================================
//-----------------------------------------------------------------------------
// TIME STAMP
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct a date and time stamp with the format YYYYMMDD_HHMMSS.
 *
 * @return Null terminated character array of the stamp.  The caller must
 * delete this memory.
 */
char* rdIO::
ConstructDateAndTimeStamp()
{
	// GET DATE AND TIME
	time_t timeInSeconds;
	struct tm *timeStruct;
	time(&timeInSeconds);
	timeStruct = localtime(&timeInSeconds);

	// CONSTRUCT STAMP
	char *stamp = new char[64];
	sprintf(stamp,"%d%02d%02d_%02d%02d%02d",
		timeStruct->tm_year+1900,timeStruct->tm_mon+1,timeStruct->tm_mday,
		timeStruct->tm_hour,timeStruct->tm_min,timeStruct->tm_sec);

	return(stamp);
}

//=============================================================================
// NUMBERED OUTPUT
//=============================================================================
//-----------------------------------------------------------------------------
// SCIENTIFIC
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not output of numbers should be in scientific or float
 * format.
 *
 * @param aTrueFalse Scientific notation if true, and float if false.
 */
void rdIO::
SetScientific(bool aTrueFalse)
{
	_Scientific = aTrueFalse;
	ConstructDoubleOutputFormat();
}

//_____________________________________________________________________________
/**
 * Set whether or not output of numbers should be in scientific or float
 * format.
 *
 * @return True if scientific notation, false if float.
 */
bool rdIO::
GetScientific()
{
	return(_Scientific);
}

//-----------------------------------------------------------------------------
// PAD
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the number of digits with which to pad output of numbers.
 * The pad number is used to set the minimum field width by the following
 * formula:
 *		width = pad + precision
 *
 * The formated output string, for example, would have the form
 *		%width.precisionlf.
 *
 * @param aPad Number of digits with which output of numbers is padded.
 */
void rdIO::
SetDigitsPad(int aPad)
{
	if(aPad<0) aPad = -1;
	_Pad = aPad;
	ConstructDoubleOutputFormat();
}
//_____________________________________________________________________________
/**
 * Get the number of digits with which output of numbers is padded.
 * The pad number is used to set the minimum field width by the following
 * formula:
 *		width = pad + precision
 *
 * The formated output string, for example, would have the form
 *		%width.precisionlf.
 *
 * @return aPad Number of digits with which output of number is padded.
 */
int rdIO::
GetDigitsPad()
{
	return(_Pad);
}

//-----------------------------------------------------------------------------
// PRECISION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the precision with which numbers are output.
 * The precision is usually simply the number of decimal places.
 *
 * @param aPrecision Precision.
 */
void rdIO::
SetPrecision(int aPrecision)
{
	if(aPrecision<0) aPrecision = 0;
	_Precision = aPrecision;
	ConstructDoubleOutputFormat();
}
//_____________________________________________________________________________
/**
 * Get the precision with which numbers are output.
 * The precision is usually simply the number of decimal places.
 *
 * @return Precision (often number of decimal places).
 */
int rdIO::
GetPrecision()
{
	return(_Precision);
}

//-----------------------------------------------------------------------------
// OUTPUT FORMAT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the current output format for numbers of type double.
 *
 * The format is maintained as a static variable in class rdIO, so any
 * changes made to the output parameters in class rdIO will be seen globally
 * by all classes using this method.
 *
 * The returned output format will be of the form
 *
 *		"% width.precision lf" (if not scientific)  or
 *		"% width.precision le" (if scientific),
 *
 * where the spaces have been removed and width = pad + precision.
 *
 * @return Format string for output of doubles.
 * @see SetScientific(), SetDigitsPad, SetPrecision.
 */
const char* rdIO::
GetDoubleOutputFormat()
{
	return(_DoubleFormat);
}

//_____________________________________________________________________________
/**
 * Construct a valid output format for numbers of type double.
 * This method is called each time a change is made to any of the output
 * format parameters.
 *
 * @see SetScientific(), SetDigitsPad, SetPrecision.
 */
void rdIO::
ConstructDoubleOutputFormat()
{
	if(_Scientific) {
		if(_Pad<0) {
			sprintf(_DoubleFormat,"%%.%dle",_Precision);
		} else {
			sprintf(_DoubleFormat,"%%%d.%dle",_Pad+_Precision,_Precision);
		}
	} else {
		if(_Pad<0) {
			sprintf(_DoubleFormat,"%%.%dlf",_Precision);
		} else {
			sprintf(_DoubleFormat,"%%%d.%dlf",_Pad+_Precision,_Precision);
		}
	}
}


//=============================================================================
// READ
//=============================================================================
//_____________________________________________________________________________
/**
 * Read lines from the file until a line consisting entirely of a
 * token is read or until the end of the file.  The file pointer is
 * advanced to the first character after the token.
 *
 * Memory is allocated for the description, so the caller is responsible
 * for deleting the returned description.
 *
 * @param aFilePointer File pointer that points to the file.
 * @param aToken Token to which to read.  The token should not contain
 * a carriage return.
 * @return Null terminated String up to a token line.  The ending carriage
 * return is included in the returned string.
 */
char* rdIO::
ReadToTokenLine(FILE *aFP,const char *aToken)
{
	if(aFP==NULL) return(NULL);
	if(aToken==NULL) return(NULL);

	// READ FIRST LINE
	char *line = ReadLine(aFP);
	if(line==NULL)  return(NULL);
	if(strcmp(line,aToken)==0) {
		delete[] line;
		return(NULL);
	}

	// READ REMAINING LINES
	int nNeeded=0,n=0;
	char *s=NULL,*sCopy=NULL;
	while((line!=NULL) && (strcmp(line,aToken)!=0)) {

		// NEEDED LENGTH
		nNeeded += strlen(line) + 2;

		// MAKE ALLOCATIONS
		if(n<=nNeeded) {

			// SIZE
			while(n<=nNeeded) n += STRING_INCREMENT;

			// COPY IF NEEDED
			if(s!=NULL) {
				if(sCopy!=NULL) delete[] sCopy;
				sCopy = new char[sizeof(s)+1];
				strcpy(sCopy,s);
			}

			// INCREASE ALLOCATION
			if(s!=NULL) delete[] s;
			s = new char[n];
			strcpy(s,"");

			// REFORM S1
			if(sCopy!=NULL) strcpy(s,sCopy);
		}

		// ADD LINE
		strcat(s,line);
		strcat(s,"\n");

		// GET NEXT LINE
		delete[] line;
		line = ReadLine(aFP);
	}

	// CLEANUP
	if(line!=NULL) delete[] line;

	return(s);
}
//_____________________________________________________________________________
/**
 * Read a line of text from file.
 *
 * The terminating carriage return is not included in the returned string.
 *
 * This routine allocates memory to store the line, so the caller is
 * responsible for deleting this memory.
 *
 * @param aFP Pointer to the file.
 * @return Line of text not including the terminating carriage return.
 */
char* rdIO::
ReadLine(FILE *aFP)
{
	if(aFP==NULL) return(NULL);

	// ALLOCATE SPACE
	int length = ComputeLineLength(aFP);
	if(length==0) return(NULL);
	char *line = new char[length];
	
	// READ THE LINE
	int i,c;
	for(c=i=0;(c!='\n')&&(c!=EOF);i++) {
		c = getc(aFP);
		if((c=='\n')||(c==EOF)) {
			line[i] = '\0';
		} else {
			line[i] = c;
		}
	}

	return(line);
}

//_____________________________________________________________________________
/**
 * Compute the length of a line.
 *
 * A carriage return defines the end of a line.
 *
 * @param aFP File pointer.
 * @return Length of a line.
 */
int rdIO::
ComputeLineLength(FILE *aFP)
{
	if(aFP==NULL) return(0);

	// STORE THE STREAM LOCATION
	long begin = ftell(aFP);

	// COMPUTE LINE LENGTH
	int c,length;
	for(length=0,c=0;(c!='\n')&&(c!=EOF);length++)  { c = getc(aFP); }

	// RETURN TO THE BEGINNING OF THE LINE
	fseek(aFP,begin,SEEK_SET);

	return(length);
}
//_____________________________________________________________________________
/**
 * Compute the number of steps of a given size to get from some initial time to
 * some final time.
 *
 * If (aTF-aTI)/aDT has a remainder that is greater than 1% of the step size,
 * an additional step is assumed to be needed to step completely to the end
 * of the interval.
 *
 * @param aTI Initial time.
 * @param aTF Final time.
 * @param aDT Step size.  Should be greater than 0.0.
 */
int rdIO::
ComputeNumberOfSteps(double aTI,double aTF,double aDT)
{
	if(aDT<=0) return(0);

	double duration = aTF-aTI;
	int ns = (int)floor(duration/aDT);
	if((ns*aDT)<(duration-1.0e-2*aDT)) {
		ns += 2;
	} else {
		ns += 1;
	}

	return(ns);
}
//_____________________________________________________________________________
/**
 * Read a specified number of characters from file.
 *
 * Memory is allocated for the returned string, so the caller is
 * responsible for deleting this memory.
 *
 * @param aFP File pointer that points to the file.
 * @param aNChar Number of characters in the description.
 * @return Pointer to the string of characters.
 */
char* rdIO::
ReadCharacters(FILE *aFP,int aNChar)
{
	if(aFP==NULL) return(NULL);

	int i,c;
	char *s = new char[aNChar+1];
	for(i=0;i<aNChar;i++) {
		c = getc(aFP);
		if(c==EOF) {
			printf("rdIO.ReadCharacters: ERROR- premature end of file.\n");
			s[i] = NULL;
			break;
		}
		s[i] = c;
	}
	s[aNChar] = NULL;

	return(s);
}

//_____________________________________________________________________________
/**
 * Open a file.
 */
FILE* rdIO::
OpenFile(const char *aFileName,const char *aMode)
{
	FILE *fp = NULL;

	// CHECK FOR VALID FILE NAME
	if(aFileName==NULL) {
		printf("rdIO.OpenFile(const char*,const char*): null filename.\n");
		return(NULL);
	}

	// OPEN THE FILE
	fp = fopen(aFileName,aMode);
	if(fp==NULL) {
		printf("rdIO.OpenFile(const char*,const char*): failed to open %s\n",
		 aFileName);
		return(NULL);
	}

	return(fp);
}
//_____________________________________________________________________________
/**
 * Create a directory. Potentially platform dependent.
  * @return int 0 on success, EEXIST or other error condition
*/
int rdIO::
makeDir(const char *aDirName)
{
	return _mkdir(aDirName);
}

