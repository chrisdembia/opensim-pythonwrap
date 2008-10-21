//-----------------------------------------------------------------------------
// File:     CoordinateAxis.h
// Class:    CoordinateAxis 
// Parent:   None
// Purpose:  Converts XAxis, YAxis, ZAxis to 0, 1, 2 - but with the ability
//           for the compiler to differentiate the types and method signatures.
//-----------------------------------------------------------------------------
#ifndef SIMTK_COORDINATEAXIS_H 
#define SIMTK_COORDINATEAXIS_H 

/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simmatrix(tm)                       *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2005-7 Stanford University and the Authors.         *
 * Authors: Michael Sherman and Paul Mitiguy                                  *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

//-----------------------------------------------------------------------------
#include <cassert>

//-----------------------------------------------------------------------------
namespace SimTK {

//-----------------------------------------------------------------------------
// These classes allow the compiler to identify specific arguments as types, i.e.,
// XAxis is a specific type of class and allows the compiler to match to a specific method.
// In addition, these classes allow easy conversion of XAxis to 0, YAxis to 1, ZAxis to 2.
//-----------------------------------------------------------------------------
class CoordinateAxis {
public:
    // This typecasts CoordinateAxis into an int
    operator int() const  { return myAxisId; }

    // XAxis.getNextAxis()  returns YAxis; 
    // YAxis.getNextAxis()  returns ZAxis; 
    // ZAxis.getNextAxis()  returns XAxis;
    CoordinateAxis  getNextAxis() const     { return CoordinateAxis( (myAxisId+1) % 3 ); }

    // XAxis.getPreviousAxis()  returns ZAxis; 
    // YAxis.getPreviousAxis()  returns XAxis; 
    // ZAxis.getPreviousAxis()  returns YAxis;
    CoordinateAxis  getPreviousAxis() const { return CoordinateAxis( (myAxisId+2) % 3 ); }

    // XAxis.getThirdAxis(YAxis) returns ZAxis; 
    // XAxis.getThirdAxis(ZAxis) returns YAxis; 
    // YAxis.getThirdAxis(ZAxis) returns XAxis;
    CoordinateAxis  getThirdAxis( const CoordinateAxis& axis2 ) const { 
       assert( isDifferentAxis(axis2) );
       CoordinateAxis nextAxis = getNextAxis();
       return nextAxis.isDifferentAxis(axis2) ? nextAxis : axis2.getNextAxis();
       }

    // Compare various axes.
    bool  isXAxis() const   { return myAxisId == 0; }
    bool  isYAxis() const   { return myAxisId == 1; }
    bool  isZAxis() const   { return myAxisId == 2; }
    bool  isNextAxis( const CoordinateAxis& axis2 ) const                                        { return int(getNextAxis()) == int(axis2); }
    bool  isPreviousAxis( const CoordinateAxis& axis2 ) const                                    { return int(getPreviousAxis()) == int(axis2); }
    bool  isSameAxis( const CoordinateAxis& axis2 ) const                                        { return myAxisId == int(axis2); }
    bool  areAllSameAxes( const CoordinateAxis& axis2, const CoordinateAxis &axis3 ) const       { return isSameAxis(axis2) && isSameAxis(axis3); }
    bool  isDifferentAxis( const CoordinateAxis& axis2 ) const                                   { return myAxisId != int(axis2); }
    bool  areAllDifferentAxes( const CoordinateAxis& axis2, const CoordinateAxis& axis3 ) const  { return isDifferentAxis(axis2) && isDifferentAxis(axis3) && axis2.isDifferentAxis(axis3); }
    bool  isForwardCyclical( const CoordinateAxis& axis2 ) const                                 { return isNextAxis(axis2); }
    bool  isReverseCyclical( const CoordinateAxis& axis2 ) const                                 { return isPreviousAxis(axis2); }

    // Quasi dot-product and cross-product
    int  dotProduct(  const CoordinateAxis& axis2 ) const                         { return isSameAxis(axis2) ? 1 : 0; }
    int  crossProductSign( const CoordinateAxis& axis2 ) const                    { return isSameAxis(axis2) ? 0 : (isNextAxis(axis2) ? 1 : -1); }
    CoordinateAxis  crossProductAxis( const CoordinateAxis& axis2 ) const         { return isSameAxis(axis2) ? CoordinateAxis(myAxisId) : getThirdAxis(axis2); }
    CoordinateAxis  crossProduct( const CoordinateAxis& axis2, int& sign ) const  { sign = crossProductSign(axis2);  return crossProductAxis(axis2); }

    // Get the appropriate CoordinateAxis
    // Check whether or not an index is in proper range
    static CoordinateAxis  getCoordinateAxis( int i )  { assertIndexIsInRange(i);  return (i==0) ? CoordinateAxis(XTypeAxis()) : ((i==1) ? CoordinateAxis(YTypeAxis()) : CoordinateAxis(ZTypeAxis()) ); }
    static bool  isIndexInRange( int i )               { return i>=0 && i<=2; }
    static void  assertIndexIsInRange( int i )         { assert( isIndexInRange(i) ); } 

    // Forward declarations for subsequent helper classes
    class XCoordinateAxis; class YCoordinateAxis; class ZCoordinateAxis;

protected:
    // Declaration of very simple classes
    class XTypeAxis{}; class YTypeAxis{}; class ZTypeAxis{};

    CoordinateAxis( const XTypeAxis& ) : myAxisId(0) {}
    CoordinateAxis( const YTypeAxis& ) : myAxisId(1) {}
    CoordinateAxis( const ZTypeAxis& ) : myAxisId(2) {}
private:            
    explicit CoordinateAxis( int i ) : myAxisId(i) { assertIndexIsInRange(i); }

    int myAxisId;
};


// Helper classes that make it possible to treat an Axis like an integer
class CoordinateAxis::XCoordinateAxis : public CoordinateAxis {
  public: XCoordinateAxis() : CoordinateAxis(XTypeAxis()) {}
};
class CoordinateAxis::YCoordinateAxis : public CoordinateAxis {
  public: YCoordinateAxis() : CoordinateAxis(YTypeAxis()) {}
};
class CoordinateAxis::ZCoordinateAxis : public CoordinateAxis {
  public: ZCoordinateAxis() : CoordinateAxis(ZTypeAxis()) {}
};


// Predefine constants XAxis, YAxis, ZAxis which implicitly convert to integers 0, 1, 2 respectively.
static const CoordinateAxis::XCoordinateAxis  XAxis;
static const CoordinateAxis::YCoordinateAxis  YAxis;
static const CoordinateAxis::ZCoordinateAxis  ZAxis;


//------------------------------------------------------------------------------
}  // End of namespace

//--------------------------------------------------------------------------
#endif // SIMTK_COORDINATEAXIS_H_
//--------------------------------------------------------------------------


