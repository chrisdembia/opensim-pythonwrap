/* Copyright (c) 2006 Stanford University and Ayman Habib.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Define the standard SimTK compliant "version" and "about" routines.
 */


#include "SDFastDLL.h"

#include <string>
#include <cstring>
#include <cctype>


#define STR(var) #var
#define MAKE_VERSION_STRING(maj,min,build)  STR(maj.min.build)
#define MAKE_COPYRIGHT_STRING(y,a) \
    "Copyright (c) " STR(y) " Stanford University, " STR(a)
#define MAKE_STRING(a) STR(a)

#define GET_VERSION_STRING  \
    MAKE_VERSION_STRING(OPENSIM_RDSDFAST_MAJOR_VERSION,  \
                        OPENSIM_RDSDFAST_MINOR_VERSION,  \
                        OPENSIM_RDSDFAST_BUILD_VERSION)

#define GET_COPYRIGHT_STRING \
    MAKE_COPYRIGHT_STRING(OPENSIM_RDSDFAST_COPYRIGHT_YEARS, \
                          OPENSIM_RDSDFAST_AUTHORS)

#define GET_AUTHORS_STRING \
    MAKE_STRING(OPENSIM_RDSDFAST_AUTHORS)

#define GET_LIBRARY_STRING \
    MAKE_STRING(OPENSIM_RDSDFAST_LIBRARY_NAME)

#define GET_TYPE_STRING \
    MAKE_STRING(OPENSIM_RDSDFAST_TYPE)

#ifndef NDEBUG
    #define GET_DEBUG_STRING "debug"
#else
    #define GET_DEBUG_STRING "release"
#endif

extern "C" {

void opensim_version_SDFast(int* major, int* minor, int* build) {
    static const char* l = "OPENSIM library="   GET_LIBRARY_STRING;
    static const char* t = "OPENSIM type="      GET_TYPE_STRING;
    static const char* d = "OPENSIM debug="     GET_DEBUG_STRING;
    static const char* v = "OPENSIM version="   GET_VERSION_STRING;
    static const char* c = "OPENSIM copyright=" GET_COPYRIGHT_STRING;

    if (major) *major = OPENSIM_RDSDFAST_MAJOR_VERSION;
    if (minor) *minor = OPENSIM_RDSDFAST_MINOR_VERSION;
    if (build) *build = OPENSIM_RDSDFAST_BUILD_VERSION;

    // Force statics to be present in the binary (Release mode otherwise 
    // optimizes them away).
    volatile int i=0;
    if (i) { // never true, but compiler doesn't know ...
        *major = *l + *t + *d + *v + *c;
    }
}

void opensim_about_SDFast(const char* key, int maxlen, char* value) {
    if (maxlen <= 0 || value==0) return;
    value[0] = '\0'; // in case we don't find a match
    if (key==0) return;

    // downshift the key
    std::string skey(key);
    for (size_t i=0; i<skey.size(); ++i)
        skey[i] = std::tolower(skey[i]);

    char* v = 0;
    if      (skey == "version")   v = GET_VERSION_STRING;
    else if (skey == "library")   v = GET_LIBRARY_STRING;
    else if (skey == "type")      v = GET_TYPE_STRING;
    else if (skey == "copyright") v = GET_COPYRIGHT_STRING;
    else if (skey == "authors")   v = GET_AUTHORS_STRING;
    else if (skey == "debug")     v = GET_DEBUG_STRING;

    if (v) {
        std::strncpy(value,v,maxlen-1);
        value[maxlen-1] = '\0'; // in case we ran out of room
    }
}

}
