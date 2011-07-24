/*
* Copyright (c)  2008, Stanford University, All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
*   1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
*   2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
*   3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
*   4. Credits to developers may not be removed from executables
*     created from modifications of the source.
*   5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <OpenSim/Common/PiecewiseLinearFunction.h>
#include <OpenSim/Auxiliary/auxiliaryTestFunctions.h>

using namespace OpenSim;
using namespace std;

int main() {
    try {
        double x[] = {0.0, 1.0, 2.0, 2.5, 5.0, 10.0};
        double y[] = {0.5, 0.7, 2.0, -1.0, 0.5, 0.1};
        PiecewiseLinearFunction f1(6, x, y);
        FunctionAdapter adapter(f1);
        const SimTK::Function& f2 = *f1.createSimTKFunction();
        SimTK::Vector xvec(1);
        vector<int> deriv(1, 0);
        for (int i = 0; i < 100; ++i) {
            xvec[0] = i*0.01;
            ASSERT_EQUAL(f1.calcValue(xvec), adapter.calcValue(xvec), 1e-10, __FILE__, __LINE__);
            ASSERT_EQUAL(f1.calcDerivative(deriv,xvec), adapter.calcDerivative(deriv,xvec), 1e-10, __FILE__, __LINE__);
            ASSERT_EQUAL(f1.calcValue(xvec), f2.calcValue(xvec),  1e-10, __FILE__, __LINE__);
            ASSERT_EQUAL(f1.calcDerivative(deriv,xvec), f2.calcDerivative(deriv,xvec), 1e-10, __FILE__, __LINE__);
        }
        ASSERT(adapter.getArgumentSize() == 1, __FILE__, __LINE__);
    }
    catch (const Exception& e) {
        e.print(cerr);
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
