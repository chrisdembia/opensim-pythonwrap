/* -------------------------------------------------------------------------- *
 *                        OpenSim:  FunctionScaler.cpp                        *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

//=============================================================================
// INCLUDES
//=============================================================================
#include "FunctionScaler.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace OpenSim;
using namespace SimTK;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
/**
 * Constructor from an OpenSim::Function.
 */
FunctionScaler::FunctionScaler(const SimTK::Function* function, double scale) : _function(function), _scale(scale)
{
}

FunctionScaler::~FunctionScaler()
{
    delete _function;
}

//=============================================================================
// SimTK::Function METHODS
//=============================================================================
double FunctionScaler::calcValue(const Vector& x) const {
    return _scale*_function->calcValue(x);
}
double FunctionScaler::calcDerivative(const std::vector<int>& derivComponents, const Vector& x) const {
    return _scale*_function->calcDerivative(derivComponents, x);
}
int FunctionScaler::getArgumentSize() const {
    return _function->getArgumentSize();
}
int FunctionScaler::getMaxDerivativeOrder() const {
    return _function->getMaxDerivativeOrder();
}

