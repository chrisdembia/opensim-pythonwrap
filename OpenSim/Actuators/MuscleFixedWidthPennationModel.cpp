/* -------------------------------------------------------------------------- *
 *                OpenSim:  MuscleFixedWidthPennationModel.cpp                *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Matthew Millard                                                 *
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
#include "MuscleFixedWidthPennationModel.h"
using namespace OpenSim;
using namespace SimTK;
using namespace std;

void MuscleFixedWidthPennationModel::setNull()
{
	setAuthors("Matthew Millard");
    m_parallelogramHeight   = SimTK::NaN;
}

void MuscleFixedWidthPennationModel::constructProperties()
{
    constructProperty_optimal_fiber_length(1.0);
    constructProperty_optimal_pennation_angle(0);
    constructProperty_maximum_pennation_angle(acos(0.1));
}


MuscleFixedWidthPennationModel::MuscleFixedWidthPennationModel()
{
    setNull();
    constructProperties();
    ensureModelUpToDate();
}

MuscleFixedWidthPennationModel::
    MuscleFixedWidthPennationModel(double optimalFiberLength,
                                    double optimalPennationAngle,    
                                    double maximumPennationAngle)
{
    SimTK_ERRCHK_ALWAYS( optimalFiberLength > 0,
        "MuscleFixedWidthPennationModel::"
        "MuscleFixedWidthPennationModel",
        "Optimal fiber length must be greater than zero.");
    
    SimTK_ERRCHK_ALWAYS( optimalPennationAngle < SimTK::Pi/2 
                       && optimalPennationAngle >= 0,
        "MuscleFixedWidthPennationModel::"
        "MuscleFixedWidthPennationModel",
        "Optimal pennation angle be between 0 and Pi/2 radians.");

    SimTK_ERRCHK_ALWAYS(maximumPennationAngle <= SimTK::Pi/2 
                      && maximumPennationAngle >= 0,
      "MuscleFixedWidthPennationModel::"
        "MuscleFixedWidthPennationModel",
        "Maximum pennation angle must be between 0"
        " and Pi/2 radians.");

    setNull();
    constructProperties();

    set_optimal_fiber_length(optimalFiberLength);
    set_optimal_pennation_angle(optimalPennationAngle);
    set_maximum_pennation_angle(maximumPennationAngle);

    ensureModelUpToDate();
}

void MuscleFixedWidthPennationModel::buildModel()
{
    double optimalFiberLength    = get_optimal_fiber_length();
    double optimalPennationAngle = get_optimal_pennation_angle();
    double maximumPennationAngle = get_maximum_pennation_angle();
    
    m_parallelogramHeight    = optimalFiberLength * sin(optimalPennationAngle);
    
    //Compute the minimum pennation angle as the minimum of
    // Pennated Muscle: the length of the fiber at its maximum pennation angle
    // Straight Muscle: 1% of the fiber's optimal length
    if(maximumPennationAngle > SimTK::SignificantReal){

        double fiberLengthCosMaxPenAngle = m_parallelogramHeight
                                            * cos(maximumPennationAngle)
                                            / sin(maximumPennationAngle);
        
        double fiberLengthMaxPenAngle =
                  sqrt(      m_parallelogramHeight * m_parallelogramHeight
                       + fiberLengthCosMaxPenAngle * fiberLengthCosMaxPenAngle);
        
        m_minimumFiberLength = fiberLengthMaxPenAngle;
    }else{
        m_minimumFiberLength = optimalFiberLength*0.01;
    }
    
    //Compute other relevant properties that are used many times
    m_maximumSinPennation    = sin(maximumPennationAngle);
   
    m_minimumFiberLengthAlongTendon 
        =  m_minimumFiberLength*cos(maximumPennationAngle);

    //Mark model as being up to date with its properties
    setObjectIsUpToDateWithProperties();
}

void MuscleFixedWidthPennationModel::ensureModelUpToDate()
{
    ensurePropertiesSet();
    if(isObjectUpToDateWithProperties()==false){
        buildModel();
    }
}

void MuscleFixedWidthPennationModel::ensurePropertiesSet() const
{
    double optFibLen = get_optimal_fiber_length();
    double optPenAng = get_optimal_pennation_angle();
    double maxPenAng = get_maximum_pennation_angle();

    SimTK_ERRCHK1_ALWAYS((  isnan(optFibLen) != true 
                        &&  isnan(optPenAng) != true
                        &&  isnan(maxPenAng) != true),
    "MuscleFixedWidthPennationModel",
    "%s: Properties have not yet been set!.",getName().c_str());

}


bool MuscleFixedWidthPennationModel::
    setOptimalPennationAngle(double aOptimalPennationAngle)
{
    if( aOptimalPennationAngle < SimTK::Pi/2 
        && aOptimalPennationAngle >= 0){
            set_optimal_pennation_angle(aOptimalPennationAngle);
            ensureModelUpToDate();
            return true;
    }else{
            return false;
    }

}

bool MuscleFixedWidthPennationModel::
    setOptimalFiberLength(double aOptimalFiberLength)
{
    if(aOptimalFiberLength > SimTK::SignificantReal){
        set_optimal_fiber_length(aOptimalFiberLength);
        ensureModelUpToDate();
        return true;
    }else{
        return false;
    }

}

bool MuscleFixedWidthPennationModel::
    setMaximumPennationAngle(double aMaximumPennationAngle)
{
   if(aMaximumPennationAngle <= SimTK::Pi/2 
       && aMaximumPennationAngle >= 0){
           set_maximum_pennation_angle(aMaximumPennationAngle);
           ensureModelUpToDate();
           return true;
   }else{
        return false;
   }
                      
}

double MuscleFixedWidthPennationModel::getParallelogramHeight() const
{   

    return m_parallelogramHeight;
}

double MuscleFixedWidthPennationModel::getOptimalFiberLength() const
{   

    return get_optimal_fiber_length();
}

double MuscleFixedWidthPennationModel::getMinimumFiberLength() const
{   

    return m_minimumFiberLength;
}


double MuscleFixedWidthPennationModel::
    getMinimumFiberLengthAlongTendon() const
{   

    return m_minimumFiberLengthAlongTendon;
}

double MuscleFixedWidthPennationModel::
    getMaximumPennationAngle() const
{    
  
    return get_maximum_pennation_angle();
}

double MuscleFixedWidthPennationModel::
    getOptimalPennationAngle() const
{   

    return get_optimal_pennation_angle();
}

double MuscleFixedWidthPennationModel::
    clampFiberLength(double fiberLength) const
{    

    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double clampedFiberLength = 
        max(m_minimumFiberLength, fiberLength);

    return clampedFiberLength;
}

/*==============================================================================
Position level kinematics
==============================================================================*/
double MuscleFixedWidthPennationModel::
    calcPennationAngle(double fiberLength) const
{
    bool test = isObjectUpToDateWithProperties();
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double phi = 0;       
    double optimalPennationAngle = get_optimal_pennation_angle();

    //This computation is only worth performing on pennated muscles
    if(optimalPennationAngle > SimTK::Eps){

        if(fiberLength > m_minimumFiberLength){
            double sin_phi = m_parallelogramHeight/fiberLength;
            
            if(sin_phi < m_maximumSinPennation){
                phi = asin(sin_phi);
            }else{
                phi = get_maximum_pennation_angle();
            }            
        }else{
            phi = get_maximum_pennation_angle();
        }
    }
    return phi;

}

double MuscleFixedWidthPennationModel::
    calcTendonLength(double cosPennationAngle, double fiberLength, 
                                               double muscleLength) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double tl = muscleLength - fiberLength*cosPennationAngle;
    return tl;
}

double MuscleFixedWidthPennationModel::
  calcFiberLengthAlongTendon(double fiberLength, double cosPennationAngle) const
{

    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    return fiberLength*cosPennationAngle;
}

/*==============================================================================
Velocity level kinematics
==============================================================================*/


double MuscleFixedWidthPennationModel::
    calcPennationAngularVelocity(double tanPennationAngle, double fiberLength,  
                                double fiberVelocity) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double dphi=0;
    double optimalPennationAngle = get_optimal_pennation_angle();

    if(optimalPennationAngle > SimTK::Eps){
        SimTK_ERRCHK_ALWAYS( fiberLength > 0,
            "MuscleFixedWidthPennationModel::calcPennationAngularVelocity",
            "Fiber length cannot be zero.");

        dphi = -(fiberVelocity/fiberLength)*tanPennationAngle;
    }
    return dphi;

}

double MuscleFixedWidthPennationModel::
    calcTendonVelocity(double cosPennationAngle,
                            double sinPennationAngle,
                            double pennationAngularVelocity,
                            double fiberLength,    
                            double fiberVelocity,
                            double muscleVelocity) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");
    
    double tendonVelocity = muscleVelocity - fiberVelocity * cosPennationAngle
            + fiberLength * sinPennationAngle * pennationAngularVelocity;
    return tendonVelocity;
}

double MuscleFixedWidthPennationModel::
  calcFiberVelocityAlongTendon(double fiberLength, double fiberVelocity,
                     double sinPennationAngle, double cosPennationAngle, 
                                        double pennationAngularVelocity) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    //double dlceAT = dlce*cos(phi) - lce*sin(phi)*dphidt;
    double dlceAT =     fiberVelocity*cosPennationAngle 
                       -fiberLength*sinPennationAngle*pennationAngularVelocity;
    return dlceAT;
}
/*==============================================================================
Acceleration Level
==============================================================================*/

double MuscleFixedWidthPennationModel::
    calcPennationAngularAcceleration(double fiberLength, 
                                        double fiberVelocity,
                                        double fiberAcceleration,
                                        double sinPennationAngle,
                                        double cosPennationAngle,
                                    double pennationAngularVelocity) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    SimTK_ERRCHK_ALWAYS( fiberLength > 0,
        "MuscleFixedWidthPennationModel::calcPennationAngularAcceleration",
        "Fiber length cannot be zero.");
    SimTK_ERRCHK_ALWAYS( cosPennationAngle > 0,
        "MuscleFixedWidthPennationModel::calcPennationAngularAcceleration",
        "CosPennationAngle cannot be zero.");
    
    double lce      = fiberLength;
    double dlce_dt  = fiberVelocity;
    double ddlce_dtt= fiberAcceleration;

    double sinphi = sinPennationAngle;
    double cosphi = cosPennationAngle;
    double dphi_dt= pennationAngularVelocity;
    
    //ddphi_dtt
    double t1 = sinphi;
    double t3 = cosphi;
    double t8 = dphi_dt * dphi_dt;
    double ddphi_dtt = -(ddlce_dtt * t1 + 0.2e1 * dlce_dt * t3 * dphi_dt 
                        - lce * t1 * t8) / lce / t3;

    return ddphi_dtt;
}

double MuscleFixedWidthPennationModel::
    calcFiberAccelerationAlongTendon(double fiberLength, 
                                        double fiberVelocity,
                                        double fiberAcceleration,
                                        double sinPennationAngle,
                                        double cosPennationAngle,
                                    double pennationAngularVelocity,
                                    double pennationAngularAcceleration) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double lce      = fiberLength;
    double dlce_dt  = fiberVelocity;
    double ddlce_dtt= fiberAcceleration;

    double sinphi   = sinPennationAngle;
    double cosphi   = cosPennationAngle;
    double dphi_dt  = pennationAngularVelocity;
    double ddphi_dtt= pennationAngularAcceleration;
    
    //ddlceAT_dtt
    double t1 = cosphi;
    double t3 = sinphi;
    double t8 = dphi_dt * dphi_dt;
    double ddlceAT_dtt = ddlce_dtt * t1 - 0.2e1 * dlce_dt * t3 * dphi_dt 
                        - lce * t1 * t8 - lce * t3 * ddphi_dtt;

    return ddlceAT_dtt;
}


/*==============================================================================
Kinematic Position Level
Partial Derivatives w.r.t. fiber length 
==============================================================================*/
double MuscleFixedWidthPennationModel::
    calc_DFiberLengthAlongTendon_DfiberLength(double fiberLength,                                     
                                         double sinPennationAngle, 
                                         double cosPennationAngle,                                    
                                         double DpennationAngle_DfiberLength
                                         ) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");
    //Renaming to smaller names, else the equations become unreadable
    double lce      = fiberLength;
    double sinPhi   = sinPennationAngle;
    double cosPhi   = cosPennationAngle;
    double Dphi_Dlce=DpennationAngle_DfiberLength;

    //d/dlce (lce*cos(phi)) = cos(phi) - lce*sin(phi)*dphi_dlce 
    double DlceAT_Dlce = cosPhi - lce*sinPhi*Dphi_Dlce;
    return DlceAT_Dlce;
}


double MuscleFixedWidthPennationModel::
  calc_DPennationAngularVelocity_DfiberLength(double fiberLength, 
                                              double fiberVelocity,
                                              double sinPennationAngle, 
                                              double cosPennationAngle, 
                                          double pennationAngularVelocity,
                                          double DpennationAngle_DfiberLength
                                          ) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");
    //Variable name switches to make the math more easily read
    double lce = fiberLength;
    double dlce = fiberVelocity;
    double sinPhi = sinPennationAngle;
    double cosPhi = cosPennationAngle;
    double dphidt = pennationAngularVelocity;
    double Dphi_Dlce = DpennationAngle_DfiberLength;

    SimTK_ERRCHK_ALWAYS( cosPhi > SimTK::Eps,
    "MuscleFixedWidthPennationModel::calc_DFiberVelocityAlongTendon_DfiberLength",
    "Pennation angle is 90 degrees.");

    double tanPhi = sinPhi/cosPhi;    
    double DtanPhi_Dlce = (1+tanPhi*tanPhi)*Dphi_Dlce;

    //dphidt = -(fiberVelocity/fiberLength)*tanPennationAngle;
    //dphidt = -(dlce/lce)*tanPhi;
    
    SimTK_ERRCHK_ALWAYS( lce > SimTK::Eps,
    "MuscleFixedWidthPennationModel::calc_DFiberVelocityAlongTendon_DfiberLength",
    "Fiber length is close to 0.");
    double Ddphidt_Dlce= (dlce/(lce*lce))*tanPhi
                        -(dlce/lce)*DtanPhi_Dlce;
    return Ddphidt_Dlce;
}

double MuscleFixedWidthPennationModel::
  calc_DFiberVelocityAlongTendon_DfiberLength(
                                double fiberLength, 
                                double fiberVelocity,
                                double sinPennationAngle, 
                                double cosPennationAngle,
                                double pennationAngularVelocity,
                                double DpennationAngle_DfiberLength,
                                double DpennationAngularVelocity_DfiberLength
                                ) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");
    //Variable name switches to make the math more easily read
    double lce = fiberLength;
    double dlce = fiberVelocity;
    double sinPhi = sinPennationAngle;
    double cosPhi = cosPennationAngle;
    double dphidt = pennationAngularVelocity;
    double Dphi_Dlce = DpennationAngle_DfiberLength;
    double Ddphidt_Dlce= DpennationAngularVelocity_DfiberLength;

    //double dlceAT = dlce*cos(phi) - lce*sin(phi)*dphidt;
    //Now taking the partial derivative of dlceAT w.r.t lce
    double DdlceAT_Dlce = dlce*(-sinPhi*Dphi_Dlce)
                          -(1)*sinPhi*dphidt
                          -lce*(cosPhi*Dphi_Dlce)*dphidt
                          -lce*sinPhi*(Ddphidt_Dlce);    
    return DdlceAT_Dlce;
}

double MuscleFixedWidthPennationModel::
    calc_DPennationAngle_DfiberLength(double fiberLength) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    SimTK_ERRCHK_ALWAYS( fiberLength > m_parallelogramHeight ,
     "MuscleFixedWidthPennationModel::calc_DPennationAngle_DfiberLength",
     "%s: Fiber length is below the minimum bound for this muscle.");

    // phi = asin( parallelogramHeight/lce)
    //d_phi/d_lce = d/dlce (asin(parallelogramHeight/lce))

    double t1 = fiberLength*fiberLength;
    double t2 = 1 / t1;
    double t4 = (m_parallelogramHeight*m_parallelogramHeight);
    double t7 = sqrt((1 - t4 * t2));
    double dphi_dlce = -m_parallelogramHeight * t2 / t7;

    return dphi_dlce;
}
                

double MuscleFixedWidthPennationModel::
    calc_DTendonLength_DfiberLength(double fiberLength, 
                                    double sinPennationAngle,
                                    double cosPennationAngle,
                                    double DpennationAngle_DfiberLength)  const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    SimTK_ERRCHK_ALWAYS( fiberLength > m_parallelogramHeight ,
     "MuscleFixedWidthPennationModel::calc_DTendonLength_DfiberLength",
     "Fiber length is below the minimum bound for this muscle.");


    //double dtl_dlce = DmuscleLength_DfiberLength-cosPennationAngle 
    //    + fiberLength * sinPennationAngle * DpennationAngle_DfiberLength;

    double dtl_dlce = -cosPennationAngle 
        + fiberLength * sinPennationAngle * DpennationAngle_DfiberLength;
    return dtl_dlce;
}

/*==============================================================================
Kinematic Fiber Pose Equations
Useful during initialization
==============================================================================*/

double MuscleFixedWidthPennationModel::
    calcFiberVelocity(  double cosPennation,                        
                        double muscleVelocity, 
                        double tendonVelocity) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");    
    double fiberVelocity = (muscleVelocity - tendonVelocity)*cosPennation;

    return fiberVelocity;
}

double MuscleFixedWidthPennationModel::
    calcFiberLength(  double muscleLength, 
                      double tendonLength) const
{
    SimTK_ASSERT(isObjectUpToDateWithProperties()==true,
        "MuscleFixedWidthPennationModel: Model is not"
        " to date with properties");

    double fiberLengthAT = muscleLength-tendonLength;
    double fiberLength = 0;

    if(fiberLengthAT >= getMinimumFiberLengthAlongTendon()){
        fiberLength = sqrt(m_parallelogramHeight*m_parallelogramHeight
                                  +fiberLengthAT*fiberLengthAT);
    }else{
        fiberLength = getMinimumFiberLength();
    }

    return fiberLength;
}
