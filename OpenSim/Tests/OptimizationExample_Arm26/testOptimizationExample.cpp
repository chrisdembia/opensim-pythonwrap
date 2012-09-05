/* -------------------------------------------------------------------------- *
 *                   OpenSim:  testOptimizationExample.cpp                    *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Cassidy Kelly                                                   *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied    *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

// Author: Cassidy Kelly

//==============================================================================
//==============================================================================

#include <OpenSim/OpenSim.h>
#include <OpenSim/Auxiliary/auxiliaryTestFunctions.h>

using namespace OpenSim;
using namespace std;

int main()
{
	try {
		
		Storage result1("Arm26_randomSample_states_degrees.sto"), standard1("std_Arm26_randomSample_states_degrees.sto");
		CHECK_STORAGE_AGAINST_STANDARD(result1, standard1, Array<double>(1000., 24), __FILE__, __LINE__, "Arm26 random sample states degrees failed");
		cout << "Arm26 random sample states degrees passed\n";
		
		Storage result2("Arm26_noActivation_states_degrees.sto"), standard2("std_Arm26_noActivation_states_degrees.sto");
		CHECK_STORAGE_AGAINST_STANDARD(result2, standard2, Array<double>(1000., 24), __FILE__, __LINE__, "Arm26 no activation states degrees failed");
		cout << "Arm26 no activation states degrees passed\n";
		
		Storage result3("Arm26_bestSoFar_states_degrees.sto"), standard3("std_Arm26_bestSoFar_states_degrees.sto");
		CHECK_STORAGE_AGAINST_STANDARD(result3, standard3, Array<double>(1000., 24), __FILE__, __LINE__, "Arm26 best so far states degrees failed");
		cout << "Arm26 best so far states degrees passed\n";
	}
	catch (const Exception& e) {
        e.print(cerr);
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}