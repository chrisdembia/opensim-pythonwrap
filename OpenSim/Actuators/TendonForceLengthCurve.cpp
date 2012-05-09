/* Author: Matthew Millard
/*
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
#include "TendonForceLengthCurve.h"
#include "SimTKmath.h"

using namespace OpenSim;
using namespace SimTK;
using namespace std;

//=============================================================================
// CONSTRUCTION, COPY CONSTRUCTION, ASSIGNMENT
//=============================================================================
// Uses default (compiler-generated) destructor, copy constructor, copy 
// assignment operator.

TendonForceLengthCurve::TendonForceLengthCurve()
{
    setNull();
    constructProperties();
    setName("default_TendonForceLengthCurve");
}

TendonForceLengthCurve::TendonForceLengthCurve( double strainAtOneNormForce, 
                                                double stiffnessAtOneNormForce,
                                                double curviness,
                                                const std::string& muscleName)
{
    setNull();
    constructProperties();
    setName(muscleName + "_TendonForceLengthCurve");

    setStrainAtOneNormForce(strainAtOneNormForce);
    setStiffnessAtOneNormForce(stiffnessAtOneNormForce);
    setCurviness(curviness);

    buildCurve();
}


TendonForceLengthCurve::TendonForceLengthCurve( double strainAtOneNormForce, 
                                                const std::string& muscleName)
{
    setNull();
    constructProperties();
    setName(muscleName + "_TendonForceLengthCurve");

    setStrainAtOneNormForce(strainAtOneNormForce);
    buildCurve();
}

void TendonForceLengthCurve::setNull()
{
     setObjectIsUpToDateWithProperties(false);
}

void TendonForceLengthCurve::constructProperties()
{   
    constructProperty_strain_at_one_norm_force(0.04);
    constructProperty_stiffness_at_one_norm_force();
    constructProperty_curviness();
}


void TendonForceLengthCurve::buildCurve()
{
    if(isObjectUpToDateWithProperties() == false){
        
        double e0   =  getStrainAtOneNormForce();
        double kiso =  getStiffnessAtOneNormForceInUse();
        double c    =  getCurvinessInUse();        

        //Here's where you call the MuscleCurveFunctionFactory
        MuscleCurveFunction tmp = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    kiso,
                                                                    c,
                                                                    true,
                                                                    getName());            
        this->m_curve = tmp;          
    }
    setObjectIsUpToDateWithProperties(true);
}

SimTK::Vector TendonForceLengthCurve::
    calcReferenceTendonCurveProperties(double strainAtOneNormForce)
{
    SimTK::Vector tdnProp(5);

    //Calculate the stiffness given the strain at 1 norm force.
    //Use the extrapolated exponential tendon curve documented in
    //Thelen, 2003

        double FToe = 0.33; //Normalized force at which the transition from
                            //the exponential to the linear function is made
        double kToe = 3.0;  //The exponential shape factor
        double e0 = strainAtOneNormForce;

    //Compute the normalized strain at which the transition from an 
    //exponential to a linear function is made.
        double FkToe = FToe*kToe;
        double expkToe = exp(kToe);
        double eToe = FkToe*expkToe*e0 / (-0.1e1+ FkToe*expkToe
                                        + expkToe - FToe*expkToe + FToe);
        double kLin = (1-FToe) / (e0 - eToe);

    //Compute the (normalized) potental energy stored at e0. 
        //For a tendon with a strain of 0.04 under 1 unit load, the area
        //computed using the trapezoidal method in Matlab is 
        //1.266816749781739e-002 
    
        //Compute the potental energy stored in the toe region of the exponental
        double peToe = (FToe/(expkToe-1))*( ((eToe/kToe)*exp(kToe) - eToe) 
                                          - ((eToe/kToe)*exp(0.0) -  0.0));
        //Compute the potential energy stored in the linear region of the
        //curve between the toe region and e0
        double peLin = (kLin*(0.5*e0*e0       - eToe*e0   ) + FToe*e0)
                      -(kLin*(0.5*eToe*eToe - eToe*eToe) + FToe*eToe); 
        //Sum the total
        double peTotal = peToe + peLin;
    
    tdnProp[0] = eToe;
    tdnProp[1] = FToe; 
    tdnProp[2] = kToe;
    tdnProp[3] = kLin;
    tdnProp[4] = peTotal;

    return tdnProp;
}

//=============================================================================
// MODEL COMPPONENT INTERFACE
//=============================================================================
void TendonForceLengthCurve::setup(Model& model)
{
    Super::setup(model);
}

void TendonForceLengthCurve::initState(SimTK::State& s) const
{
    Super::initState(s);
}

void TendonForceLengthCurve::createSystem(SimTK::MultibodySystem& system) const
{
    Super::createSystem(system);

    TendonForceLengthCurve* mthis = const_cast<TendonForceLengthCurve*>(this);    
    mthis->buildCurve();
}



//=============================================================================
// GET & SET METHODS
//=============================================================================
double TendonForceLengthCurve::getStrainAtOneNormForce()
{
    return getProperty_strain_at_one_norm_force();
}

double TendonForceLengthCurve::getStiffnessAtOneNormForce()
{
    return getProperty_stiffness_at_one_norm_force();
}

double TendonForceLengthCurve::getStiffnessAtOneNormForceInUse()
{
    
    if(getProperty_stiffness_at_one_norm_force().empty()){

       //Have we computed this already?
        if(isObjectUpToDateWithProperties() == false){            
            SimTK::Vector tdnProp = getReferenceTendon();
            m_stiffnessAtOneNormForceInUse = tdnProp[3];   
        }

    }else{
        m_stiffnessAtOneNormForceInUse 
            = getProperty_stiffness_at_one_norm_force();
    }
    return m_stiffnessAtOneNormForceInUse;
}

double TendonForceLengthCurve::getCurviness()
{
    return getProperty_curviness();
}

double TendonForceLengthCurve::getCurvinessInUse()
{
    if(getProperty_curviness().empty()){

       //Have we computed this already?
        if(isObjectUpToDateWithProperties() == false){
            double e0 = getProperty_strain_at_one_norm_force();
            SimTK::Vector tdnProp = getReferenceTendon();
            double etoe     = tdnProp[0];
            double Ftoe     = tdnProp[1];
            double ktoe     = tdnProp[2];
            double klin     = tdnProp[3];
            double peNorm   = tdnProp[4];

            //Use the bisection method to solve for the curviness parameter 
            //value that results in a tendon curve that has the same normalized
            //strain energy as the extrapolated exponential curve.

            double tol = 1e-6;
            std::string name = getName();
            //double c_opt = fitToReferenceTendon(e0, klin,peNorm,tol,name);

            double c = 0.5;
            double prevC = 0.5;
            double step = 0.25;
            
            MuscleCurveFunction tmp = MuscleCurveFunctionFactory::
                    createTendonForceLengthCurve(   e0,
                                                    klin,
                                                    c,
                                                    true,
                                                    getName());

            double val = tmp.calcIntegral(1+e0);

            double err      = (val-peNorm)/peNorm;
            double prevErr = 0;
            double errStart = err;
            double errMin   = 0;
            
            double solMin           = 0;
            bool flag_improvement   = false;
            bool flag_Newton        = false;

            int maxIter     = 10;
            int iter        = 0;
            int localIter   = 0;
            int evalIter    = 0;


            while(iter < maxIter && abs(err) > tol){ 
                flag_improvement = false;
                localIter        = 0;                

                //Bisection
                while(flag_improvement == false && localIter < 2 
                        && flag_Newton == false){

                    MuscleCurveFunction tmp = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    klin,
                                                                    c+step,
                                                                    true,
                                                                    getName());                
                    val     = tmp.calcIntegral(1+e0);
                    errMin  = (val-peNorm)/peNorm; 
                                    
                    if(abs(errMin) < abs(err)){
                        prevC = c;
                        c   = c+step;
                        prevErr = err;
                        err = errMin;
                        flag_improvement = true;

                        if(err*prevErr < 0)
                            step = step*-1;
                        
                    }else{
                        step = step*-1;
                    }
                    localIter++;
               }

                //1. Compute a Newton step 
                //2. If the Newton step is smaller than the current step, take it
                //3. If the Newton step results in improvement, update.

                //if(flag_improvement == false){
                    double dErr = err-prevErr;
                    double dC   = c-prevC; 
                    double dErrdC= dErr/dC;
                    double deltaC = -err/dErrdC;
                    double cNewton = c + deltaC;

                    if(abs(deltaC) < abs(step)){
                        MuscleCurveFunction tmp = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    klin,
                                                                    cNewton,
                                                                    true,
                                                                    getName());                
                        val     = tmp.calcIntegral(1+e0);
                        errMin  = (val-peNorm)/peNorm; 
                                    
                        if(abs(errMin) < abs(err)){
                            prevC = c;
                            c   = cNewton;
                            prevErr = err;
                            err = errMin;
                            flag_improvement = true;
                            flag_Newton = true;
                            step = deltaC;
                      }
                        localIter++;
                    }
                //}

                evalIter += localIter;
                step = step/2.0;
                iter++;
                //printf("Bisection Iter %i ,err: %f, eval %i\n",
                //    iter,err,evalIter);
            }

            SimTK_ERRCHK1_ALWAYS(err < errStart && errStart > (tol+step),
                "TendonForceLengthCurve::getCurvinessInUse()",
                "%s: Not able to fit a tendon curve to the reference"
                "tendon curve",getName().c_str());

            m_curvinessInUse = c;
        }



    }else{
        m_curvinessInUse 
            = getProperty_curviness();
    }
    return m_curvinessInUse;
}


void TendonForceLengthCurve::
    setStrainAtOneNormForce(double aStrainAtOneNormForce)
{
    if(aStrainAtOneNormForce != getStrainAtOneNormForce() )
    {        
        setProperty_strain_at_one_norm_force(aStrainAtOneNormForce);
        setObjectIsUpToDateWithProperties(false);
    }
}

void TendonForceLengthCurve::
        setStiffnessAtOneNormForce(double aStiffnessAtOneNormForce)
{
    //if(aStiffnessAtOneNormForce != getStiffnessAtOneNormForce() )
    //{
        setProperty_stiffness_at_one_norm_force(aStiffnessAtOneNormForce);
        setObjectIsUpToDateWithProperties(false);
    //}
}

void TendonForceLengthCurve::setCurviness(double aCurviness)
{
    //if(aCurviness != getCurviness() )
    //{
        setProperty_curviness(aCurviness);
        setObjectIsUpToDateWithProperties(false);
    //}
}


SimTK::Vector TendonForceLengthCurve::getReferenceTendon()
{
    if(m_TendonReference.size() == 0){
        double e0 = getStrainAtOneNormForce();
        m_TendonReference = calcReferenceTendonCurveProperties(e0);
    }
    return m_TendonReference;
}

//=============================================================================
// SERVICES
//=============================================================================

double TendonForceLengthCurve::
    calcValue(double aNormLength) const
{
    if(isObjectUpToDateWithProperties() == false){
        TendonForceLengthCurve* mthis = 
            const_cast<TendonForceLengthCurve*>(this);    
        mthis->buildCurve();    
    }

    return m_curve.calcValue(aNormLength);
}

double TendonForceLengthCurve::
    calcDerivative(double aNormLength, int order) const
{
    SimTK_ERRCHK1_ALWAYS(order >= 0 && order <= 2, 
        "TendonForceLengthCurve::calcDerivative",
        "order must be 0, 1, or 2, but %i was entered", order);
    
    if(isObjectUpToDateWithProperties() == false){
        TendonForceLengthCurve* mthis = 
            const_cast<TendonForceLengthCurve*>(this);    
        mthis->buildCurve();    
    }

    return m_curve.calcDerivative(aNormLength,order);
}

double TendonForceLengthCurve::calcIntegral(double aNormLength) const
{
    if(isObjectUpToDateWithProperties() == false){
        TendonForceLengthCurve* mthis = 
            const_cast<TendonForceLengthCurve*>(this);    
        mthis->buildCurve();    
    }

    return m_curve.calcIntegral(aNormLength);
}

SimTK::Vec2 TendonForceLengthCurve::getCurveDomain() const
{
    if(isObjectUpToDateWithProperties() == false){
        TendonForceLengthCurve* mthis = 
            const_cast<TendonForceLengthCurve*>(this);    
        mthis->buildCurve();    
    }

    return m_curve.getCurveDomain();
}

void TendonForceLengthCurve::
    printMuscleCurveToCSVFile(const std::string& path) const
{
    if(isObjectUpToDateWithProperties() == false){
        TendonForceLengthCurve* mthis = 
            const_cast<TendonForceLengthCurve*>(this);    
        mthis->buildCurve();    
    }

    m_curve.printMuscleCurveToCSVFile(path);
}


//==============================================================================
//
// Set up SimTK::Optimizer to fit the tendon curve to a reference curve
//
//==============================================================================

/*
///@cond
class TendonReferenceCurveData {
public:
        double strainAtOneNormForce;
        double stiffnessAtOneNormForce;
        double areaAtOneNormForce;
        string name;
};
///@endcond
///@cond
class ProblemSystem : public OptimizerSystem {
public:
    ProblemSystem(const TendonReferenceCurveData& data,
                  const int numOptVars,
                  const int numEqConst,
                  const int numIEqConst)
                  : tendonData(data), OptimizerSystem(numOptVars) {
        setNumEqualityConstraints(numEqConst);
        setNumInequalityConstraints(numIEqConst);
        iterations = 0;
        
    }


    int objectiveFunc(const Vector &optVariables, 
        bool newVariables, Real& f) const {
        
            double e0 = tendonData.strainAtOneNormForce;
            double k  = tendonData.stiffnessAtOneNormForce;
            double c  = optVariables[0];
            string name= tendonData.name;

            if(c > 1){c = 1;}
            if(c < 0){c = 0;}

            MuscleCurveFunction tmpM = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    k,
                                                                    c,
                                                                    true,
                                                                    name);

            double areaAtOneNormForce = tmpM.calcIntegral(1+e0);
            double areaRef = tendonData.areaAtOneNormForce;
            double relErr = (areaAtOneNormForce - areaRef)/areaRef;
            f = abs(relErr)*abs(relErr)*1000;
            iterations++;
            return(0);
    }

    int getNumIterations(){
        return iterations;
    }


private:
    const TendonReferenceCurveData tendonData;
    int mutable iterations;
};
///@endcond

///@cond
double TendonForceLengthCurve::
    fitToReferenceTendon(   double strainAtOneNormForce,
                            double stiffnessAtOneNormForce,
                            double areaAtOneNormForce, 
                            double relTol,
                            std::string& name) const
{
    TendonReferenceCurveData tdata;
    tdata.strainAtOneNormForce      = strainAtOneNormForce;
    tdata.stiffnessAtOneNormForce   = stiffnessAtOneNormForce;
    tdata.areaAtOneNormForce        = areaAtOneNormForce;
    tdata.name                      = name;

    int numOptVars = 1;
    int numEqConst = 0;
    int numIEqConst= 0;

    ProblemSystem sys(tdata, numOptVars, numEqConst, numIEqConst);

    Vector results(numOptVars);
    Vector lowerBounds(numOptVars);
    Vector upperBounds(numOptVars);

    results[0]      = 0.5;
    lowerBounds[0]  = 0;
    upperBounds[0]  = 1;

    sys.setParameterLimits( lowerBounds, upperBounds );

    Real f = NaN;
    try {
        Optimizer opt( sys ); 
        
        opt.setConvergenceTolerance( relTol );        
        opt.useNumericalGradient(true);
        opt.useNumericalJacobian(true);
        f = opt.optimize( results );
        int iter = sys.getNumIterations();
        printf("Optimizer Iterations %i\n",iter);
    }
    catch (const std::exception& e) {
        printf( "%s: %s: Caught exception while creating fitted tendon curve",
                "TendonForceLengthCurve::fitToReferenceTendon",name.c_str());
        std::cout << e.what() << std::endl;
    }

    return results[0];
}
///@endcond

*/
/*
            int maxIter = 20;
            int iter = 0;

            while(iter < maxIter && abs(err) > tol){ 

                MuscleCurveFunction tmpP = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    klin,
                                                                    c+step,
                                                                    true,
                                                                    getName());

                MuscleCurveFunction tmpM = MuscleCurveFunctionFactory::
                                    createTendonForceLengthCurve(   e0,
                                                                    klin,
                                                                    c-step,
                                                                    true,
                                                                    getName());
                valP = tmpP.calcIntegral(1+e0);
                valM = tmpM.calcIntegral(1+e0);


                errP = abs(peNorm-valP)/peNorm;
                errM = abs(peNorm-valM)/peNorm;

                if(abs(errP) < abs(errM)){
                    errMin = abs(errP);
                    solMin = c+step;
                }else{
                    errMin = abs(errM);
                    solMin = c-step;
                }

                if(abs(errMin) < abs(err)){
                    c = solMin;
                    err = abs(errMin);
                }
                step = step/2.0;
                iter++;
                printf("Bisection Loop %i, err: %f, eval %i\n",iter,err,iter*2);
            }
*/

