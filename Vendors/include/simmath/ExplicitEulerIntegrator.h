#ifndef SimTK_SIMMATH_EXPLICIT_EULER_INTEGRATOR_H_
#define SimTK_SIMMATH_EXPLICIT_EULER_INTEGRATOR_H_

/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simmath(tm)                         *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2007 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
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

#include "SimTKcommon.h"
#include "simmath/internal/common.h"

#include "simmath/Integrator.h"

namespace SimTK {

class ExplicitEulerIntegratorRep;

/**
 * This is an Integrator based on the explicit Euler algorithm.  It is an
 * error controlled, first order explicit integrator.  This is one of the simplest
 * integrators possible.  As such, it is useful as a test case, but usually is
 * a bad choice for real simulations.
 */

class SimTK_SIMMATH_EXPORT ExplicitEulerIntegrator : public Integrator {
public:
    /**
     * Create an ExplicitEulerIntegrator for integrating a System with variable sized steps.
     */
    ExplicitEulerIntegrator(const System& sys);
    /**
     * Create an ExplicitEulerIntegrator for integrating a System with fixed sized steps.
     */
    ExplicitEulerIntegrator(const System& sys, Real stepSize);
    ~ExplicitEulerIntegrator();
};

} // namespace SimTK

#endif // SimTK_SIMMATH_EXPLICIT_EULER_INTEGRATOR_H_


