// suPipeline40.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Peter V. Ehrhart, Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef SU_PIPELINE_40
#define SU_PIPELINE_40


//=============================================================================
// INCLUDES
//=============================================================================
#include <string>
#include <NMBLTK/Simulation/SDFast/rdSDFastDLL.h>
#include <NMBLTK/Simulation/SDFast/rdActuatedModel_SDFast.h>


class rdActuatorSet;
class rdContactForceSet;
class suScaleSet;
struct DP_Data;

//namespace su {// nonviolent protest


//=============================================================================
//=============================================================================
/**
 * A class that wraps a model created by the SIMM Dynamics Pipeline 3.2.3
 *
 * @author Peter V. Ehrhart, Frank C. Anderson, Saryn R. Goldberg
 * @version 1.0
 */
class RDSDFAST_API suPipeline40 : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Flag indicating whether or not the SIMM actuators should included as
	part of the actuation for the pipeline model.  The default is true. */
	bool _includePipelineActuators;
protected:
	/** Array for holding the initial states. */
	rdArray<double> _yi;
	/** Structure used to hold pipeline related variables. */
   DP_Data *_dpd;

//=============================================================================
// METHODS
//=============================================================================
public:
	// CONSTRUCTION
   suPipeline40(const std::string &aWorkpath,const std::string &aParamfile,
		rdActuatorSet *aActuators,rdContactForceSet *aContacts,
		bool performInitialization=true);
   virtual ~suPipeline40() = 0;
protected:
	void setNull();
	void cleanup();
	void constructInitialStates();
	void constructNames();
	virtual void initPipeline(const std::string &workpath, const std::string &paramfile);

public:

	// NUMBERS OF THINGS
	virtual int getNX() const;
	virtual int getNA() const;
	virtual int getNY() const;

	// NAMES
	virtual std::string getActuatorName(int aIndex) const;
	virtual std::string getControlName(int aIndex) const;
	virtual std::string getStateName(int aIndex) const;

	// INDICES
	virtual int getActuatorIndex(const std::string &aName) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual int getStateIndex(const std::string &aName) const;

	// CONTROLS
	virtual void setControl(int aIndex,double aValue);
	virtual void setControl(const std::string &aName,double aValue);
	virtual void setControls(const double aX[]);
	virtual double getControl(const std::string &aName) const;
	virtual double getControl(int aIndex) const;
	virtual void getControls(double aX[]) const;

	// INITIAL STATES
	virtual void setInitialStates(const double aY[]);
	virtual void getInitialStates(double rY[]) const;
	virtual double getInitialState(int aIndex) const;

	// STATES
	virtual void setStates(const double aY[]);
	virtual void getStates(double rY[]) const;
	virtual double getState(int aIndex) const;

	// CONFIGURATION
	virtual void setConfiguration(const double aY[]);
	virtual void setConfiguration(const double aQ[],const double aU[]);

	//SCALING
	virtual bool scale(const suScaleSet& aScaleSet);
	// ACTUATION
	//void setIncludePipelineActuators(bool aTrueFalse);
	bool getIncludePipelineActuators() const;
	virtual void computeActuation();
	//virtual void computeActuatorStateDerivatives(double rDY[]);
	virtual void applyActuatorForce(int aID);
	virtual void applyActuatorForces();
	virtual void setActuatorForce(int aID, double aForce);
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorStress(int aID) const;
	virtual double getActuatorSpeed(int aID) const;
	virtual double getActuatorPower(int aID) const;

	// CONTACT
	void computeContact();
	void applyContactForce(int aID);
	void applyContactForces();

	// DERIVATIVES
	virtual void computeAuxiliaryDerivatives(double *dydt);

	// FOR RRA - ADDED BY CHAND, 2/3/2006
	virtual void setIncludePipelineActuators(bool include);

//=============================================================================
};	// END of class suPipeline40
//=============================================================================
//=============================================================================

//} // namespace su
#endif // guard
