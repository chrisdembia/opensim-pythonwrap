#ifndef SimTK_SIMMATRIX_SPATIAL_ALGEBRA_H_
#define SimTK_SIMMATRIX_SPATIAL_ALGEBRA_H_

/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simmatrix(tm)                       *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2005-10 Stanford University and the Authors.        *
 * Authors: Michael Sherman                                                   *
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

/** @file
These are declarations for special matrices and vectors of use in implementing
Rodriguez and Jain's Spatial Operator Algebra. **/

#include "SimTKcommon/SmallMatrix.h"

#include <iostream>

namespace SimTK {


/**@defgroup SpatialAlgebraUtilities    Spatial Algebra Utilities
   @ingroup GlobalFunctions

These utility functions are used for manipulation of spatial quantities that 
are contained in SpatialVec or SpatialMat objects. These are intended for
expert use and are mostly used in the implemention of friendlier methods such
as those in MobilizedBody that are used to obtain various spatial quantities.

@note Although we use SpatialVec for both, there are two different spatial 
vector bases: one for motion quantities like velocities, accelerations, and 
momentum and another for forces and impulses; be sure to use the appropriate 
functions. Also, we use a pair of ordinary vectors, following Abhi Jain,
rather than the similar but subtly different Plucker basis vectors used by 
Roy Featherstone.

Spatial vectors are used for combined (rotational,translational) quantities. 
These include
@verbatim
     spatial velocity     = (angularVelocity,linearVelocity)
     spatial acceleration = (angularAcceleration,linearAcceleration)
     spatial force        = (moment,force)
@endverbatim

Spatial configuration (pose) has to be handled differently though since
orientation is not a vector quantity. We use the Transform class for this 
concept, which includes an orientation matrix and a translation vector.
@see Transform **/
/*@{*/

/** SpatialVec[0] is the rotational component; [1] is translational. **/
typedef Vec<2,   Vec3>  SpatialVec;
/** This is the type of a transposed SpatialVec. **/
typedef Row<2,   Row3>  SpatialRow;
/** This is used for primarily for spatial mass properties. **/
typedef Mat<2,2, Mat33> SpatialMat;


// Pre-declare methods here so that we can list them in whatever order we'd
// like them to appear in Doxygen.
inline SpatialVec findRelativeVelocity(const Transform&  X_FA,
                                       const SpatialVec& V_FA,
                                       const Transform&  X_FB,
                                       const SpatialVec& V_FB);
inline SpatialVec findRelativeVelocityInF(const Vec3&       p_AB_F,
                                          const SpatialVec& V_FA,
                                          const SpatialVec& V_FB);

inline SpatialVec reverseRelativeVelocity(const Transform&  X_AB,
                                          const SpatialVec& V_AB);
inline SpatialVec reverseRelativeVelocityInA(const Transform&  X_AB,
                                             const SpatialVec& V_AB);

inline SpatialVec shiftVelocityBy(const SpatialVec& V_AB, const Vec3& r_A);
inline SpatialVec shiftVelocityFromTo(const SpatialVec& V_A_BP, 
                                      const Vec3&       fromP_A,
                                      const Vec3&       toQ_A);

inline SpatialVec shiftForceBy(const SpatialVec& F_AP, const Vec3& r_A);
inline SpatialVec shiftForceFromTo(const SpatialVec& F_AP, 
                                   const Vec3&       fromP_A,
                                   const Vec3&       toQ_A);

/** @brief Find the relative spatial velocity between two frames A and B whose 
individual spatial velocities are known with respect to a third frame F, with
the result returned in A.

@param[in]      X_FA
    The pose of frame A measured and expressed in frame F.
@param[in]      V_FA
    The spatial velocity of frame A measured and expressed in frame F.
@param[in]      X_FB
    The pose of frame B measured and expressed in frame F.
@param[in]      V_FB
    The spatial velocity of frame B measured and expressed in frame F.
@return V_AB, the relative spatial velocity of frame B in frame A, expressed 
    in A.

Given the spatial velocity V_FA of frame A in a reference frame F, and
the spatial velocity V_FB of frame B in F, and transforms giving the poses of
frames A and B in F, calculate the relative velocity V_AB of frame B in 
frame A, measured and expressed in A. Typical usage:
@code
    Transform X_GA, X_GB;       // assume these are known from somewhere
    SpatialVec V_GA, V_GB;

    SpatialVec V_AB = findRelativeVelocity(X_FA, V_FA, 
                                           X_FB, V_FB);
@endcode
@note This returns the result expressed in A which is almost always what you
want; however, if you don't want it in that frame you can save 30 flops by
calling findRelativeVelocityInF() instead.

Cost is 51 flops. @see findRelativeVelocityInF() **/
inline SpatialVec findRelativeVelocity(const Transform&  X_FA,
                                       const SpatialVec& V_FA,
                                       const Transform&  X_FB,
                                       const SpatialVec& V_FB)
{
    const Vec3 p_AB_F = X_FB.p() - X_FA.p();                    //  3 flops
    return ~X_FA.R()*findRelativeVelocityInF(p_AB_F,V_FA,V_FB); // 48 flops
}

/** @brief Find the relative spatial velocity between two frames A and B whose 
individual spatial velocities are known in a third frame F, but leave the 
result in F.

@param[in]      p_AB_F
    The vector from the A frame origin OA to the B frame origin OB, but
    expressed in frame F.
@param[in]      V_FA
    The spatial velocity of frame A measured and expressed in frame F.
@param[in]      V_FB
    The spatial velocity of frame B measured and expressed in frame F.
@return V_AB_F, the relative spatial velocity of frame B in frame A, but still 
    expressed in F.

Typically the relative velocity of B in A would be returned in A; most
users will want to use findRelativeVelocity() instead which returns the result
in A. Use of this method saves the substantial cost of reexpressing the result,
so is useful in the rare case that you don't want the final result in A.
Example:
@code
    Transform X_GA, X_GB;       // assume these are known from somewhere
    SpatialVec V_GA, V_GB;

    const Vec3 p_AB_G = X_GB.p() - X_GA.p();
    SpatialVec V_AB_G = findRelativeVelocityInF(p_AB_G, V_GA, V_GB);
@endcode
Cost is 18 flops. @see findRelativeVelocity() **/
inline SpatialVec findRelativeVelocityInF(const Vec3&       p_AB_F,
                                          const SpatialVec& V_FA,
                                          const SpatialVec& V_FB)
{
    // Relative angular velocity of B in A, expressed in F.
    const Vec3 w_AB_F     = V_FB[0] - V_FA[0];              // 3 flops
    // Relative linear velocity of B in A, taken and expressed in F.
    const Vec3 p_AB_F_dot = V_FB[1] - V_FA[1];              // 3 flops
    // Get linear velocity taken in A by removing the component due
    // to A's rotation in F (still expressed in F).
    const Vec3 v_AB_F = p_AB_F_dot - V_FA[0] % p_AB_F;      // 12 flops

    return SpatialVec(w_AB_F, v_AB_F);
}

/** @brief Given the relative velocity of frame B in frame A, reverse that to
give the relative velocity of frame A in B.

@param[in]      X_AB
    The pose of frame B in frame A, measured and expressed in A.
@param[in]      V_AB
    The relative spatial velocity of frame B in frame A, measured and 
    expressed in frame A.
@return V_BA, the relative spatial velocity of frame A in frame B, measured
    and expressed in B.

The input is expressed in the A frame; the result will be expressed in the B
frame instead. If you prefer that the result remain in the A frame you should 
call reverseRelativeVelocityInA() instead to avoid the extra cost of changing 
frames. Example:
@code
    Transform  X_AB;    // assume these are known from somewhere
    SpatialVec V_AB;

    SpatialVec V_BA = reverseRelativeVelocity(X_AB, V_AB);
@endcode
@note If the frame origins were in the same spatial location, then the result 
would just be the negative of the supplied velocity. However, since the linear
component of spatial velocity has to be measured at a point, and we're 
switching from measuring at a point coincident with B's origin OB to one
coincident with A's origin OA, there is going to be a change in the linear
part of the result. The angular velocity will just be negated, though, and
then reexpressed in B.

Cost is 51 flops. @see reverseRelativeVelocityInA() **/
inline SpatialVec reverseRelativeVelocity(const Transform&  X_AB,
                                          const SpatialVec& V_AB)
{
    // Reverse the velocity but with the result still expressed in A.
    const SpatialVec V_BA_A = reverseRelativeVelocityInA(X_AB,V_AB); 
                                                                // 21 flops
    // Then reexpress in B.
    return ~X_AB.R()*V_BA_A;                                    // 30 flops
}

/** @brief Given the relative velocity of frame B in frame A, reverse that to
give the relative velocity of frame A in B, but leave the result expressed
in frame A.

@param[in]      X_AB
    The pose of frame B in frame A, measured and expressed in A.
@param[in]      V_AB
    The relative spatial velocity of frame B in frame A, measured and 
    expressed in frame A.
@return V_BA_A, the relative velocity of frame A in frame B, but still 
    expressed in B.

The input V_AB is expressed in the A frame; you will almost always want the
output V_BA expressed in the B frame which is what the function 
reverseRelativeVelocity() does. However, if you're going to want it in
some other frame ultimately you may prefer to avoid the substantial cost of 
reexpressing it in B now, in which case this routine is useful.

See reverseRelativeVelocity() for more information about what this does. 
Example:
@code
    Transform  X_AB;    // assume these are known from somewhere
    SpatialVec V_AB;    // (expressed in A)

    // result is still expressed in A
    SpatialVec V_BA_A = reverseRelativeVelocityInA(X_AB, V_AB);
@endcode

Cost is 21 flops. @see reverseRelativeVelocity() **/
inline SpatialVec reverseRelativeVelocityInA(const Transform&  X_AB,
                                             const SpatialVec& V_AB)
{
    // Change the measurement point from a point coincident with OB
    // to a point coincident with OA, and negate since we want A's velocity
    // in B rather than the other way around.
    const SpatialVec V_BA_A = -shiftVelocityBy(V_AB, -X_AB.p()); // 21 flops
    return V_BA_A;
}


/** @brief Shift a relative spatial velocity measured at some point to that
same relative spatial quantity but measured at a new point given by an offset
from the old one.

@param[in]      V_AB
    The relative spatial velocity of frame B in frame A, measured and 
    expressed in frame A.
@param[in]      r_A
    The vector offset, expressed in frame A, by which to change the point at 
    which the translational component of the relative spatial velocity is 
    measured.
@return V_A_BQ, the relative velocity of frame B in frame A, but measured at
    the point Q=OB+r rather than at B's origin OB.

Given the spatial velocity V_AB of frame B in A, measured at a point
coincident with B's origin OB, change it to the spatial velocity V_A_BQ 
representing the same relationship but with the velocity measured at a new 
point Q=OB+r for some position vector r. All vectors are measured and expressed
in frame A, including the vector r. Example:
@code
    SpatialVec V_AB;     // assume these are known from somewhere
    Vec3       offset_A; // Q = OB + offset

    SpatialVec V_A_BQ = shiftVelocityBy(V_AB, offset_A);
@endcode

@note The shift in location leaves the relative angular velocity w the same but
results in the linear velocity changing by w X r.

Cost is 12 flops. @see shiftVelocityFromTo() **/
inline SpatialVec shiftVelocityBy(const SpatialVec& V_AB, const Vec3& r_A)
{   return SpatialVec( V_AB[0], V_AB[1] + V_AB[0] % r_A ); } // vp=v + wXr

/** @brief Shift a relative spatial velocity measured at some point P to that
same relative spatial quantity but measured at a new point Q given the points
P and Q.

@param[in]      V_A_BP
    The relative spatial velocity of frame B in frame A, measured and 
    expressed in frame A, with the linear component measured at a point P.
@param[in]      fromP_A
    The "from" point P at which the input linear velocity was measured, given
    as a vector from A's origin OA to the point P, expressed in A.
@param[in]      toQ_A
    The "to" point Q at which we want to re-measure the linear velocity, given
    as a vector from A's origin OA to the point Q, expressed in A.
@return V_A_BQ, the relative velocity of frame B in frame A, but measured at
    the point Q rather than at point P.

Given the spatial velocity V_A_BP of frame B in A, measured at a point P,
change it to the spatial velocity V_A_BQ representing the same relationship but
with the velocity measured at a new point Q. Example:
@code
    // assume these are known from somewhere
    Transform  X_AB;    // contains the vector from OA to OB  
    SpatialVec V_AB;    // linear velocity is measured at origin OB of B
    Vec3       p_AQ;    // vector from OA to some other point Q, in A

    SpatialVec V_A_BQ = shiftVelocityFromTo(V_AB, X_AB.p(), p_AQ);
@endcode

@note There is no way to know whether the supplied velocity was actually
measured at P; this method really just shifts the relative velocity by
the vector r=(to-from). Use it carefully.

Cost is 15 flops. @see shiftVelocityBy() **/
inline SpatialVec shiftVelocityFromTo(const SpatialVec& V_A_BP, 
                                      const Vec3&       fromP_A,
                                      const Vec3&       toQ_A)
{   return shiftVelocityBy(V_A_BP, toQ_A - fromP_A); }



/** @brief Shift a spatial force applied at some point of a body to that
same spatial force applied at a new point given by an offset
from the old one.

@param[in]      F_AP
    A spatial force (moment and linear force), expressed in the A frame,
    whose translational component is applied at a point P.
@param[in]      r_A
    The vector offset, expressed in frame A, by which to change the point at 
    which the translational component of the input force is to be applied.
@return F_AQ, the same physical effect as the input but with the moment
    adjusted to reflect force application at point Q=P+r rather than at the
    original point P.

Given the spatial force F_AP including a pure moment m and a force vector f
applied at a point P, return the equivalent force F_AQ representing the same
physical quantity but as though the force were applied at a point Q=P+r
for some position vector r. All vectors are expressed in frame A. Example: 
@code
    SpatialVec F_AP;     // assume these are known from somewhere
    Vec3       offset_A; // Q = P + offset

    SpatialVec F_AQ = shiftForceBy(F_AP, offset_A);
@endcode

@note The shift in location leaves the force f the same but
results in an adjustment to the moment of -(r X f).

Cost is 12 flops. @see shiftForceFromTo() **/
inline SpatialVec shiftForceBy(const SpatialVec& F_AP, const Vec3& r_A)
{   return SpatialVec(F_AP[0] -  r_A % F_AP[1], F_AP[1]); } // mq = mp - r X f


/** @brief Shift a spatial force applied at some point P of a body to that
same spatial force applied at a new point Q, given P and Q.

@param[in]      F_AP
    A spatial force (moment and linear force), expressed in the A frame, whose 
    translational component is applied at a point P.
@param[in]      fromP_A
    The "from" point P at which the input force is applied, given as a 
    vector from A's origin OA to the point P, expressed in A.
@param[in]      toQ_A
    The "to" point Q to which we want to move the force application point, 
    given as a vector from A's origin OA to the point Q, expressed in A.
@return F_AQ, the same physical effect as the input but with the moment
    adjusted to reflect force application at point Q rather than at the 
    original point P.

Given the spatial force F_AP including a pure moment m and a force vector f
applied at a point P, return the equivalent force F_AQ representing the same
physical quantity but as though the force were applied at a new point Q. All 
vectors are expressed in frame A and points are measured from A's origin OA.
Example:
@code
    // assume these are known from somewhere
    SpatialVec F_AP;    // linear force is applied at point P
    Vec3       p_AP;    // vector from OA to P, in A
    Vec3       p_AQ;    // vector from OA to some other point Q, in A

    SpatialVec F_AQ = shiftForceFromTo(F_AP, p_AP, p_AQ);
@endcode

@note There is no way to know whether the supplied force was actually
applied at P; this method really just shifts the application point by
the vector r=(to-from). Use it carefully.

Cost is 15 flops. @see shiftForceBy() **/
inline SpatialVec shiftForceFromTo(const SpatialVec& F_AP, 
                                   const Vec3&       fromP_A,
                                   const Vec3&       toQ_A)
{   return shiftForceBy(F_AP, toQ_A - fromP_A); }

/*@}*/


// support for efficient matrix multiplication involving the special phi
// matrix

class PhiMatrixTranspose;

class PhiMatrix {
public:
    typedef PhiMatrixTranspose TransposeType;

    PhiMatrix() { setToNaN(); }
    PhiMatrix(const Vec3& l) : l_(l) {}

    void setToZero() { l_ = 0.; }
    void setToNaN()  { l_.setToNaN(); }

    SpatialMat toSpatialMat() const {
        return SpatialMat(Mat33(1), crossMat(l_),
                          Mat33(0),   Mat33(1));
    }

    const Vec3& l() const { return l_; }
private:
    Vec3 l_;
};

class PhiMatrixTranspose {
public:
    PhiMatrixTranspose(const PhiMatrix& phi) : phi(phi) {}

    SpatialMat toSpatialMat() const {
        return SpatialMat(   Mat33(1)    , Mat33(0),
                          crossMat(-l()) , Mat33(1));
    }

    const Vec3& l() const {return phi.l();}
private:
  const PhiMatrix& phi;
};

inline PhiMatrixTranspose
transpose(const PhiMatrix& phi)
{
    PhiMatrixTranspose ret(phi);
    return ret;
}

inline PhiMatrixTranspose
operator~(const PhiMatrix& phi) {return transpose(phi);}

inline SpatialVec
operator*(const PhiMatrix&  phi,
          const SpatialVec& v)
{
    return SpatialVec(v[0] + phi.l() % v[1], // 12 flops
                      v[1]);
}

inline SpatialMat
operator*(const PhiMatrix&  phi,
          const SpatialMat& m)
{
    const Mat33 x = crossMat(phi.l());  // 3 flops
    return SpatialMat( m(0,0) + x*m(1,0), m(0,1) + x*m(1,1), // 108 flops
                           m(1,0)       ,     m(1,1));
}

inline SpatialVec
operator*(const PhiMatrixTranspose& phiT,
          const SpatialVec&         v)
{
    return SpatialVec(v[0],
                      v[1] + v[0] % phiT.l());  // 12 flops
}


inline SpatialMat
operator*(const SpatialMat::THerm&  m,
          const PhiMatrixTranspose& phiT)
{
    const Mat33 x = crossMat(phiT.l()); // 3 flops
    return SpatialMat( m(0,0) - m(0,1) * x, m(0,1),     // 54 flops
                       m(1,0) - m(1,1) * x, m(1,1) );   // 54 flops
}

inline SpatialMat
operator*(const SpatialMat&         m,
          const PhiMatrixTranspose& phiT)
{
    const Mat33 x = crossMat(phiT.l()); // 3 flops
    return SpatialMat( m(0,0) - m(0,1) * x, m(0,1),     // 54 flops
                       m(1,0) - m(1,1) * x, m(1,1) );   // 54 flops
}

inline bool
operator==(const PhiMatrix& p1, const PhiMatrix& p2)
{
    return p1.l() == p2.l();
}

inline bool
operator==(const PhiMatrixTranspose& p1, const PhiMatrixTranspose& p2)
{
    return p1.l() == p2.l();
}
} // namespace SimTK

#endif // SimTK_SIMMATRIX_SPATIAL_ALGEBRA_H_
