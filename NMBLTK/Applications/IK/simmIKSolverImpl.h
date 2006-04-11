#ifndef __simmIKSolverImpl_h__
#define __simmIKSolverImpl_h__

#include <NMBLTK/Simulation/SIMM/IKSolverInterface.h>
#include <NMBLTK/Simulation/Model/nmblKinematicsEngine.h>
#include <NMBLTK/Tools/rdStorage.h>

class rdOptimizationTarget;
class rdFSQP;
class simmIKParams;
class simmIKTrialParams;
class simmInverseKinematicsTarget;

// simmIKSolverImpl.h
// Author: Ayman Habib
/* Copyright (c) 2005, Stanford University and Ayman Habib
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

class simmIKSolverImpl : public IKSolverInterface 
{
public:
	simmIKSolverImpl(simmInverseKinematicsTarget&	aOptimizationTarget,
					const simmIKParams&		aIKParams);

	virtual void solveFrames(const simmIKTrialParams& aIKOptions, rdStorage& inputData, rdStorage& outputData);
};

#endif // __simmIKSolverImpl_h__


