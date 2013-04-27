#ifndef OPENSIM_METABOLIC_POWER_PROBE_BHARGAVA2004_H_
#define OPENSIM_METABOLIC_POWER_PROBE_BHARGAVA2004_H_
/* -------------------------------------------------------------------------- *
 *             OpenSim:  MuscleMetabolicPowerProbeBhargava2004.h              *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Tim Dorn                                                        *
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

#include "Probe.h"
#include "Model.h"
#include <OpenSim/Common/PiecewiseLinearFunction.h>
#include <OpenSim/Simulation/Model/Muscle.h>

namespace OpenSim { 

//=============================================================================
//             MUSCLE METABOLIC POWER PROBE (Bhargava, et al., 2004)
//=============================================================================
/**
 * MuscleMetabolicPowerProbeBhargava2004 is a ModelComponent Probe for computing the 
 * net metabolic energy rate of a set of Muscles in the model during a simulation. 
 * 
 * Based on the following paper:
 *
 * <a href="http://www.ncbi.nlm.nih.gov/pubmed/14672571">
 * Bhargava, L. J., Pandy, M. G. and Anderson, F. C. (2004). 
 * A phenomenological model for estimating metabolic energy consumption
 * in muscle contraction. J Biomech 37, 81-8.</a>
 *
 * <I>Note that the equations below that describe the particular implementation of 
 * MuscleMetabolicPowerProbeBhargava2004 may slightly differ from the equations
 * described in the representative publication above. Note also that we define
 * positive muscle velocity to indicate lengthening (eccentric contraction) and
 * negative muscle velocity to indicate shortening (concentric contraction).</I>
 *
 *
 * Muscle metabolic power (or rate of metabolic energy consumption) is equal to the
 * rate at which heat is liberated plus the rate at which work is done:\n
 * <B>Edot = Bdot + sumOfAllMuscles(Adot + Mdot + Sdot + Wdot).</B>
 *
 *       - Bdot is the basal heat rate (W).
 *       - Adot is the activation heat rate (W).
 *       - Mdot is the maintenance heat rate (W).
 *       - Sdot is the shortening heat rate (W).
 *       - Wdot is the mechanical work rate (W).
 *
 *
 * This probe also uses muscle parameters stored in the MetabolicMuscle object for each muscle.
 * The full set of all MetabolicMuscles (MetabolicMuscleSet) is a property of this probe:
 * 
 * - m = The mass of the muscle (kg).
 * - r = Ratio of slow twitch fibers in the muscle (between 0 and 1).
 * - Adot_slow = Activation constant for slow twitch fibers (W/kg).
 * - Adot_fast = Activation constant for fast twitch fibers (W/kg).
 * - Mdot_slow = Maintenance constant for slow twitch fibers (W/kg).
 * - Mdot_fast = Maintenance constant for slow twitch fibers (W/kg).
 *
 *
 * <H2><B> BASAL HEAT RATE (W) </B></H2>
 * If <I>basal_rate_on</I> is set to true, then Bdot is calculated as follows:\n
 * <B>Bdot = basal_coefficient * (m_body^basal_exponent)</B>
 *     - m_body = mass of the entire model
 *     - basal_coefficient and basal_exponent are defined by their respective properties.\n
 * <I>Note that this quantity is muscle independant. Rather it is calculated on a whole body level.</I>
 *
 *
 * <H2><B> ACTIVATION HEAT RATE (W) </B></H2>
 * If <I>activation_rate_on</I> is set to true, then Adot is calculated as follows:\n
 * <B>Adot = m * [ Adot_slow * r * sin((pi/2)*u)    +    Adot_fast * (1-r) * (1-cos((pi/2)*u)) ]</B>
 *     - u = muscle excitation at the current time.
 *
 *
 * <H2><B> MAINTENANCE HEAT RATE (W) </B></H2>
 * If <I>maintenance_rate_on</I> is set to true, then Mdot is calculated as follows:\n
 * <B>Mdot = m * f * [ Mdot_slow * r * sin((pi/2)*u)    +    Mdot_fast * (1-r) * (1-cos((pi/2)*u)) ]</B>
 * - u = muscle excitation at the current time.
 * - f is a piecewise linear function that describes the normalized fiber length denendence
 * of the maintenance heat rate (default curve is shown below):
 * \image html fig_NormalizedFiberLengthDependenceOfMaintenanceHeatRateBhargava2004.png
 *
 *
 * <H2><B> SHORTENING HEAT RATE (W) </B></H2>
 * If <I>shortening_rate_on</I> is set to true, then Sdot is calculated as follows:\n
 * <B>Sdot = -alpha * v_CE</B>
 *
 * If use_force_dependent_shortening_prop_constant = true,
 *     - <B>alpha = (0.16 * F_CE_iso) + (0.18 * F_CE)   </B>,   <I>v_CE >= 0 (concentric / isometric contraction)</I>
 *     - <B>alpha = 0.157 * F_CE                        </B>,   <I>v_CE <  0 (eccentric contraction)</I>
 * 
 *     - v_CE = muscle fiber velocity at the current time.
 *     - F_CE = force developed by the contractile (active) element of muscle at the current time.
 *     - F_CE_iso = force that would be developed by the contractile element of muscle under isometric conditions with the current activation and fiber length.
 *
 * If use_force_dependent_shortening_prop_constant = false,
 *     - <B>alpha = 0.25 * (F_CE + F_PASSIVE),   </B>,   <I>v_CE >= 0 (concentric / isometric contraction)</I>
 *     - <B>alpha = 0.00                         </B>,   <I>v_CE <  0 (eccentric contraction)</I>
 *
 *      where F_PASSIVE = passive force developed by the muscle fiber velocity at the current time.
 *
 *
 * <H2><B> MECHANICAL WORK RATE (W) </B></H2>
 * If <I>mechanical_work_rate_on</I> is set to true, then Wdot is calculated as follows:\n
 * <B>Wdot = -F_CE * v_CE       </B>,   <I>v_CE >= 0 (concentric / isometric contraction)</I>\n
 * <B>Wdot = 0                  </B>,   <I>v_CE <  0 (eccentric contraction)</I>
 *     - v_CE = muscle fiber velocity at the current time.
 *     - F_CE = force developed by the contractile element of muscle at the current time.\n
 *
 *
 * Note that if enforce_minimum_heat_rate_per_muscle == true AND 
 * activation_rate_on == shortening_rate_on == maintenance_rate_on == true, then the total heat
 * rate (AMdot + Mdot + Sdot) will be capped to a minimum value of 1.0 W/kg (Umberger(2003), page 104).
 *
 * @author Tim Dorn
 */

class OSIMSIMULATION_API MuscleMetabolicPowerProbeBhargava2004 : public Probe {
OpenSim_DECLARE_CONCRETE_OBJECT(MuscleMetabolicPowerProbeBhargava2004, Probe);
public:

//==============================================================================
//==============================================================================
	class MetabolicMuscleParameter;
	class MetabolicMuscleParameterSet;

//==============================================================================
// PROPERTIES
//==============================================================================
    /** @name Property declarations
    These are the serializable properties associated with this class. **/
    /**@{**/
    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(activation_rate_on, 
        bool,
        "Specify whether activation heat rate is to be calculated (true/false).");

    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(maintenance_rate_on, 
        bool,
        "Specify whether maintenance heat rate is to be calculated (true/false).");

    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(shortening_rate_on, 
        bool,
        "Specify whether shortening heat rate is to be calculated (true/false).");

    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(basal_rate_on, 
        bool,
        "Specify whether basal heat rate is to be calculated (true/false).");

    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(mechanical_work_rate_on, 
        bool,
        "Specify whether mechanical work rate is to be calculated (true/false).");

    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(enforce_minimum_heat_rate_per_muscle, 
        bool,
        "Specify whether the total heat rate for a muscle will be clamped to a "
        "minimum value of 1.0 W/kg (true/false).");

    /** Default curve shown in doxygen. **/
    OpenSim_DECLARE_PROPERTY(normalized_fiber_length_dependence_on_maintenance_rate, 
        PiecewiseLinearFunction,
        "Contains a PiecewiseLinearFunction object that describes the "
        "normalized fiber length dependence on maintenance rate.");

    /** Disabled by default. **/
    OpenSim_DECLARE_PROPERTY(use_force_dependent_shortening_prop_constant, 
        bool,
        "Specify whether to use a force dependent shortening proportionality "
        "constant (true/false).");

    /** Default value = 1.2. **/
    OpenSim_DECLARE_PROPERTY(basal_coefficient, 
        double,
        "Basal metabolic coefficient.");

    /** Default value = 1.0. **/
    OpenSim_DECLARE_PROPERTY(basal_exponent, 
        double,
        "Basal metabolic exponent.");

    OpenSim_DECLARE_PROPERTY(metabolic_parameters,
        MetabolicMuscleParameterSet,
        "A MetabolicMuscleParameterSet containing the muscle information "
        "required to calculate metabolic energy expenditure. If multiple "
        "muscles are contained in the set, then the probe will sum the "
        "metabolic powers from all muscles.");
    /**@}**/

//=============================================================================
// PUBLIC METHODS
//=============================================================================
    typedef std::map<std::string, MetabolicMuscleParameter*> MuscleMap;

    //--------------------------------------------------------------------------
    // Constructor(s) and Setup
    //--------------------------------------------------------------------------
    /** Default constructor */
    MuscleMetabolicPowerProbeBhargava2004();

    /** Convenience constructor */
    MuscleMetabolicPowerProbeBhargava2004(
        const bool activation_rate_on, 
        const bool maintenance_rate_on, 
        const bool shortening_rate_on, 
        const bool basal_rate_on, 
        const bool work_rate_on);



    //-----------------------------------------------------------------------------
    // Computation
    //-----------------------------------------------------------------------------
    /** Compute muscle metabolic power. */
    virtual SimTK::Vector computeProbeInputs(const SimTK::State& state) const OVERRIDE_11;

    /** Returns the number of probe inputs in the vector returned by computeProbeInputs(). */
    int getNumProbeInputs() const OVERRIDE_11;

    /** Returns the column labels of the probe values for reporting. 
        Currently uses the Probe name as the column label, so be sure
        to name your probe appropiately!*/
    virtual OpenSim::Array<std::string> getProbeOutputLabels() const OVERRIDE_11;



    //-----------------------------------------------------------------------------
    /** @name     MuscleMetabolicPowerProbeBhargava2004 Interface
    These accessor methods are to be used when setting up a new muscle 
    metabolic analysis from the API. The basic operation is as follows:
    @code
    MuscleMetabolicPowerProbeUmberger2010* myProbe new MuscleMetabolicPowerProbeUmberger2010(...); 
    model.addProbe(myProbe);
    myProbe->addMuscle("muscleName1", ... );
    myProbe->addMuscle("muscleName2", ... );
    myProbe->addMuscle("muscleName3", ... );
    myProbe->removeMuscle("muscleName3");
    myProbe->setOperation("integrate")           // See OpenSim::Probe for other operations
    @endcode
    @note It is important to first add the metabolic probe to the model before
    calling any other methods that may modify its properties. This is because 
    some methods (e.g. addMuscle() or useCalculatedMass) may require information
    about the muscles to sucsessfully execute, and this information can only be
    obtained if the metabolic probe is already 'connected' to the model.
    */
    // Get the number of muscles being analysed in the metabolic analysis. */
    const int getNumMetabolicMuscles() const;

	/** Add a muscle and its parameters so that it can be included in the metabolic analysis. */
    void addMuscle(const std::string& muscleName, 
        double ratio_slow_twitch_fibers, 
        double activation_constant_slow_twitch,
        double activation_constant_fast_twitch,
        double maintenance_constant_slow_twitch,
        double maintenance_constant_fast_twitch);

    /** Add a muscle and its parameters so that it can be included in the metabolic analysis. */
    void addMuscle(const std::string& muscleName, 
        double ratio_slow_twitch_fibers, 
        double activation_constant_slow_twitch,
        double activation_constant_fast_twitch,
        double maintenance_constant_slow_twitch,
        double maintenance_constant_fast_twitch,
		double muscle_mass);

    /** Remove a muscle from the metabolic analysis. */
    void removeMuscle(const std::string& muscleName);

    // Set an existing muscle to use a provided muscle mass. */
    void useProvidedMass(const std::string& muscleName, double providedMass);

    /** Set an existing muscle to calculate its own mass. */
    void useCalculatedMass(const std::string& muscleName);

    /** Get whether the muscle mass is being explicitly provided.
       True means that it is using the property <provided_muscle_mass>
       False means that the muscle mass is being calculated from muscle properties. */
    bool isUsingProvidedMass(const std::string& muscleName);

    /** Get the muscle mass used in the metabolic analysis. The value
        returned will depend on if the muscle mass is explicitly provided
        (i.e. isUsingProvidedMass = true), or if it is being automatically
        calculated from muscle data already present in the model
        (i.e. isUsingProvidedMass = true). */
    const double getMuscleMass(const std::string& muscleName) const;

    /** Get the ratio of slow twitch fibers for an existing muscle. */
    const double getRatioSlowTwitchFibers(const std::string& muscleName) const;

    /** Set the ratio of slow twitch fibers for an existing muscle. */
    void setRatioSlowTwitchFibers(const std::string& muscleName, const double& ratio);

    /** Get the activation constant for slow twitch fibers for an existing muscle. */
    const double getActivationConstantSlowTwitch(const std::string& muscleName) const;

    /** Set the activation constant for slow twitch fibers for an existing muscle. */
    void setActivationConstantSlowTwitch(const std::string& muscleName, const double& c);

    /** Get the activation constant for fast twitch fibers for an existing muscle. */
    const double getActivationConstantFastTwitch(const std::string& muscleName) const;

    /** Set the activation constant for fast twitch fibers for an existing muscle. */
    void setActivationConstantFastTwitch(const std::string& muscleName, const double& c);

    /** Get the maintenance constant for slow twitch fibers for an existing muscle. */
    const double getMaintenanceConstantSlowTwitch(const std::string& muscleName) const;

    /** Set the maintenance constant for slow twitch fibers for an existing muscle. */
    void setMaintenanceConstantSlowTwitch(const std::string& muscleName, const double& c);

    /** Get the maintenance constant for fast twitch fibers for an existing muscle. */
    const double getMaintenanceConstantFastTwitch(const std::string& muscleName) const;

    /** Set the maintenance constant for fast twitch fibers for an existing muscle. */
    void setMaintenanceConstantFastTwitch(const std::string& muscleName, const double& c);




//==============================================================================
// PRIVATE
//==============================================================================
private:
    //--------------------------------------------------------------------------
    // Data
    //--------------------------------------------------------------------------
    MuscleMap _muscleMap;


    //--------------------------------------------------------------------------
    // ModelComponent Interface
    //--------------------------------------------------------------------------
    void connectToModel(Model& aModel) OVERRIDE_11;
    void connectIndividualMetabolicMuscle(Model& aModel, MetabolicMuscleParameter& mm);

    void setNull();
    void constructProperties();


    //--------------------------------------------------------------------------
    // MetabolicMuscleParameter Private Interface
    //--------------------------------------------------------------------------
    // Get const MetabolicMuscleParameter from the MuscleMap using a string accessor.
    const MetabolicMuscleParameter* getMetabolicParameters(
        const std::string& muscleName) const;

    // Get writable MetabolicMuscleParameter from the MuscleMap using a string accessor.
    MetabolicMuscleParameter* updMetabolicParameters(
        const std::string& muscleName);

public:
	//==============================================================================
	//==============================================================================
	//                          MetabolicMuscleParameter
	//==============================================================================
	/**
	 * MetabolicMuscleParameter is an Object class that hold the metabolic
	 * parameters required to calculate metabolic power for a single muscle. 
	 *
	 * <H2><B> MetabolicMuscleParameter Properties </B></H2>
	 *
	 * REQUIRED PROPERTIES
	 * - <B>specific_tension</B> = The specific tension of the muscle (Pascals (N/m^2)).
	 * - <B>density</B> = The density of the muscle (kg/m^3).
	 * - <B>ratio_slow_twitch_fibers</B> = Ratio of slow twitch fibers in the muscle (must be between 0 and 1).
	 * - <B>activation_constant_slow_twitch</B>  = Activation constant for slow twitch fibers (W/kg).
	 * - <B>activation_constant_fast_twitch</B>  = Activation constant for fast twitch fibers (W/kg).
	 * - <B>maintenance_constant_slow_twitch</B> = Maintenance constant for slow twitch fibers (W/kg).
	 * - <B>maintenance_constant_fast_twitch</B> = Maintenance constant for slow twitch fibers (W/kg).
	 *
	 * OPTIONAL PROPERTIES
	 * - <B>use_provided_muscle_mass</B> = An optional flag that allows the user to
	 *      explicitly specify a muscle mass. If set to true, the <provided_muscle_mass>
	 *      property must be specified. The default setting is false, in which case, the
	 *      muscle mass is calculated from the following formula:
	 *          m = (Fmax/specific_tension)*density*Lm_opt, where 
	 *              specific_tension and density are properties defined above
	 *                  (note that their default values are set based on mammalian muscle,
	 *                  0.25e6 N/m^2 and 1059.7 kg/m^3, respectively);
	 *              Fmax and Lm_opt are the maximum isometric force and optimal 
	 *                  fiber length, respectively, of the muscle.
	 *
	 * - <B>provided_muscle_mass</B> = The user specified muscle mass (kg).
	 *
	 *
	 * @author Tim Dorn
	 */
	class OSIMSIMULATION_API 
		MetabolicMuscleParameter : public Object  
	{
		OpenSim_DECLARE_CONCRETE_OBJECT(MuscleMetabolicPowerProbeBhargava2004::MetabolicMuscleParameter, Object);
	public:
	//==============================================================================
	// PROPERTIES
	//==============================================================================
		/** @name Property declarations
		These are the serializable properties associated with this class. **/
		/**@{**/
		OpenSim_DECLARE_PROPERTY(specific_tension, double,
			"The specific tension of the muscle (Pascals (N/m^2)).");

		OpenSim_DECLARE_PROPERTY(density, double,
			"The density of the muscle (kg/m^3).");

		OpenSim_DECLARE_PROPERTY(ratio_slow_twitch_fibers, double,
			"Ratio of slow twitch fibers in the muscle (must be between 0 and 1).");

		OpenSim_DECLARE_OPTIONAL_PROPERTY(use_provided_muscle_mass, bool,
			"An optional flag that allows the user to explicitly specify a muscle mass. "
			"If set to true, the <provided_muscle_mass> property must be specified.");

		OpenSim_DECLARE_OPTIONAL_PROPERTY(provided_muscle_mass, double,
			"The user specified muscle mass (kg).");

		OpenSim_DECLARE_PROPERTY(activation_constant_slow_twitch, double,
			"Activation constant for slow twitch fibers (W/kg).");

		OpenSim_DECLARE_PROPERTY(activation_constant_fast_twitch, double,
			"Activation constant for fast twitch fibers (W/kg).");

		OpenSim_DECLARE_PROPERTY(maintenance_constant_slow_twitch, double,
			"Maintenance constant for slow twitch fibers (W/kg).");

		OpenSim_DECLARE_PROPERTY(maintenance_constant_fast_twitch, double,
			"Maintenance constant for fast twitch fibers (W/kg).");
		/**@}**/

	//=============================================================================
	// DATA
	//=============================================================================
	// These private member variables are kept here because they apply to 
	// a single muscle, but are not set in this class -- rather, they are
	// set by the probes that own them.
	protected:
		Muscle* _musc;          // Internal pointer to the muscle that corresponds
								// to these parameters.
		double _muscMass;       // The mass of the muscle (depends on if
								// <use_provided_muscle_mass> is true or false.



	//=============================================================================
	// METHODS
	//=============================================================================
	public:
		//--------------------------------------------------------------------------
		// Constructor(s)
		//--------------------------------------------------------------------------
		MetabolicMuscleParameter();

		MetabolicMuscleParameter(
				const std::string& muscleName,
				double ratio_slow_twitch_fibers, 
				double muscle_mass = SimTK::NaN);

		MetabolicMuscleParameter(
			const std::string& muscleName,
			double ratio_slow_twitch_fibers, 
			double activation_constant_slow_twitch,
			double activation_constant_fast_twitch,
			double maintenance_constant_slow_twitch,
			double maintenance_constant_fast_twitch,
			double muscle_mass = SimTK::NaN);


		// Uses default (compiler-generated) destructor, copy constructor, copy 
		// assignment operator.


		//--------------------------------------------------------------------------
		// Muscle mass
		//--------------------------------------------------------------------------
		const double getMuscleMass() const      { return _muscMass; }
		void setMuscleMass();    
    


		//--------------------------------------------------------------------------
		// Internal muscle pointer
		//--------------------------------------------------------------------------
		const Muscle* getMuscle() const         { return _musc; }
		void setMuscle(Muscle* m)               { _musc = m; }



	private:
		//--------------------------------------------------------------------------
		// Object Interface
		//--------------------------------------------------------------------------
		void setNull();
		void constructProperties();

	//=============================================================================
	};	// END of class MetabolicMuscleParameter
	//=============================================================================





	//==============================================================================
	//==============================================================================
	//==============================================================================
	//                          MetabolicMuscleParameterSet
	//==============================================================================
	/**
	 * MetabolicMuscleParameterSet is a class that holds the set of 
	 * MetabolicMuscleParameters for each muscle.
	 */
	class OSIMSIMULATION_API 
		MetabolicMuscleParameterSet : public Set<MetabolicMuscleParameter>
	{
		OpenSim_DECLARE_CONCRETE_OBJECT(
			MetabolicMuscleParameterSet, Set<MetabolicMuscleParameter>);

	public:
		MetabolicMuscleParameterSet()  { setAuthors("Tim Dorn"); }
    

	//=============================================================================
	};	// END of class MetabolicMuscleParameterSet
	//=============================================================================



//=============================================================================
};	// END of class MuscleMetabolicPowerProbeBhargava2004
//=============================================================================


}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef OPENSIM_METABOLIC_POWER_PROBE_BHARGAVA2004_H_
