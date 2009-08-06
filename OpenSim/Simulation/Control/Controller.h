// Controller.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
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

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson, Chand T. John, Samuel R. Hamner, Ajay Seth
 */
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// The entire definition of the Controller class is contained inside this
// #ifndef-#define-#endif _Controller_h_ block.  This is done to ensure that,
// if someone were to include Controller.h more than once into a single file
// (such as including Controller.h as well as including another file that also
// includes Controller.h), then the Controller class will not be defined more
// than once.  "#ifndef" means "if not defined."
#ifndef _Controller_h_
#define _Controller_h_

//============================================================================
// INCLUDE
//============================================================================
// These files contain declarations and definitions of variables and methods
// that will be used by the Controller class.
#include <OpenSim/Common/Object.h>
#include "ControlSet.h"

//=============================================================================
//=============================================================================
/**
 * Controller is a class that specifies the interface (i.e., the minimal set
 * of variables and methods that should be defined by any class used to
 * control a Model.  Any class used to control a Model should be a subclass
 * (child) of Controller.  In C++ jargon, Controller is an abstract class,
 * which means that you cannot create an instance of it (i.e. you cannot write
 * code that contains a statement like "Controller controller;" or
 * "Controller controller(&model,&yDesStore);".  However, you can create a
 * subclass of Controller (such as SimpleFeedbackController) that is not
 * abstract, which means you can create an instance of it.  Controller is
 * abstract because it has a method, computeControls, that is "pure virtual."
 * This means that computeControls must be implemented by any subclass of
 * Controller, because Controller itself does not implement computeControls.
 *
 * @author Frank C. Anderson, Chand T. John, Samuel R. Hamner, Ajay Seth
 * @version 1.0
 */

// The definition of the Controller class is wrapped inside this
// namespace OpenSim {} block, which makes the class a part of the
// OpenSim namespace, i.e., the Controller class and all its variables
// and methods can only be used by a file that contains the command
// "using namespace OpenSim;" or prefixes any call to a Controller class
// public method or variable with "OpenSim::", e.g., the Controller
// class would be referred to as OpenSim::Controller.  The advantage of
// this design is that if someone defined another namespace also contained
// a Controller class that is completely different from OpenSim's
// Controller class, you could refer to these two Controller classes
// separately even though both Controller classes have the same name.
namespace OpenSim { 

// This empty declaration of the Model class is necessary because we
// haven't included a definition of the Model class (e.g., Model.h)
// in this file, but we do use the Model class in the code below.
// This way, C++ knows that Model is a class defined elsewhere and
// won't throw compiler errors when it sees the identifier "Model"
// used in the code below.
class Model;

// The entire definition of the Controller class is contained inside
// this code block.  The identifier OSIMSIMULATION_API tells C++ that
// the Controller class will be part of the library files exported by
// the osimSimulation project.  The terms "public Object" tell C++
// that the Controller class is a subclass (child) of the Object class
// in OpenSim.
class OSIMSIMULATION_API Controller : public Object
{

//=============================================================================
// DATA
//=============================================================================
// These are the member variables of the Controller class.  The "protected"
// keyword indicates that these member variables can be accessed not only by
// methods of the Controller class, but also by any subclass of the Controller
// class.
protected:
	/** 
	 * This variable represents the model to be controlled.
	 */
	Model *_model;
	/**
	 * This variable is a flag indicating whether or not the controller is
	 * "on", i.e., an integrator will use this flag to determine whether or
	 * not to use this Controller's computeControls method when running a
	 * simulation.  If _on == true, the controller is "on", whereas if
	 * _on == false, the controller is "off".
	 */
	bool _on;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:
	// These methods can be called to initialize or destroy an object that is
	// an instance of Controller (or really, an instance of a subclass of
	// Controller, since Controller itself cannot be instantiated since it is
	// an abstract class (see above)).  These methods are all "public," which
	// means any code that includes a definition of the Controller class (e.g.,
	// by including Controller.h) can call these methods.

	/**
	 * Default constructor.
	 */
	Controller();

	/**
	 * Another constructor.
	 *
	 * @param aModel The model that is to be controlled by this Controller.
	 */
	Controller(Model *aModel);

	/**
	 * Constructor from an XML Document.
	 *
	 * @param aFileName The name of the XML file in which this Controller is
	 * defined.
	 * @param aUpdateFromXMLNode A flag indicating whether or not to call
	 * updateFromXMLNode() from this constructor.  If true, the method will
	 * be called from this class.  Typically, the flag should be true for this
	 * class, but in the member initializer list for this constructor, this
	 * class's parent class's constructor with the same parameters will be
	 * called, but with aUpdateFromXMLNode set to false.
	 */
	Controller(const std::string &aFileName, bool aUpdateFromXMLNode = true);

	/**
	 * Copy constructor.  This constructor is called by any code that contains
	 * a command of the form "Controller newController(oldController);".
	 *
	 * @param aController The controller to be copied.
	 */
	Controller(const Controller &aController);

	/**
	 * Destructor.  This method should be a member of any subclass of the
	 * Controller class.  It will be called automatically whenever an
	 * instance of the subclass is deleted from memory.
	 */
	virtual ~Controller();
	
private:
	// A "private" method is one that can be called only by this class,
	// and not even by subclasses of this class.

	/**
	 * This method sets all member variables to default (e.g., NULL) values.
	 */
	void setNull();

protected:

	/**
	 * Connect properties to local pointers.  Currently, the Controller class
	 * has no properties, so this method does nothing.  However, a subclass
	 * of Controller (e.g., SimpleFeedbackController) can contain member
	 * variables that are properties, which should be defined in the
	 * setupProperties() method of the subclass.
	 */
	virtual void setupProperties();

	/**
	 * Copy the member variables of the specified controller.  This method is
	 * called by the copy constructor of the Controller class.
	 *
	 * @param aController The controller whose data is to be copied.
	 */
	void copyData(const Controller &aController);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:

#ifndef SWIG

	/**
	 * Assignment operator.  This method is called automatically whenever a
	 * command of the form "controller1 = controller2;" is made, where both
	 * controller1 and controller2 are both of type Controller.  Although
	 * Controller cannot be instantiated directly, a subclass of Controller
	 * could implement its own operator= method that calls Controller's
	 * operator= method.  If the subclass does not implement its own operator=
	 * method, then when a command of the form "controller1 = controller2" is
	 * made, where both controller1 and controller2 are instants of the
	 * subclass, the Controller class's operator= method will be called
	 * automatically.
	 *
	 * @param aController The controller to be copied.
	 * @return Reference to the altered object.
	 */
	Controller& operator=(const Controller &aController);

#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

	// MODEL

	/**
	 * Get a pointer to the model that is being controlled.
	 *
	 * @return Pointer to the model.
	 */
	Model* getModel();

	/**
	 * Set this class's pointer to the model that is being controlled
	 * to point to the model passed into this method.
	 *
	 * @param aModel Pointer to be set to point to the model that
	 * is being controlled.
	 */
	void setModel(Model *aModel);

	// INPUT CONTROL SET OBJECT
	
	/**
	 * Set this class's pointer to the object containing
	 * input controls to point to the ControlSet object passed into
	 * this method.  This method is currently implemented only by the
	 * SimpleFeedbackController class, which is a subclass of Controller.
	 *
	 * @param aControlSet A ControlSet object containing the
	 * input controls of the model for the applied during the input
	 * simulation.
	 */
	virtual void setControlSet(const ControlSet &aControlSet);

	// DESIRED STATES STORAGE OBJECT
	
	/**
	 * Set this class's pointer to the storage object containing
	 * desired model states to point to the storage object passed into
	 * this method.  This method is currently implemented only by the
	 * SimpleFeedbackController class, which is a subclass of Controller.
	 *
	 * @param aYDesStore Pointer to a Storage object containing the
	 * desired states of the model for the controller to achieve during
	 * simulation.
	 */
	virtual void setDesiredStatesStorage(Storage *aYDesStore);

	// ON/OFF

	/**
	 * Get whether or not this controller is on.
	 *
	 * @return true if on, false if off.
	 */
	bool getOn();

	/**
	 * Turn this controller on or off.
	 *
	 * @param aTrueFalse Turns controller on if "true" and off if "false".
	 */
	void setOn(bool aTrueFalse);

	//--------------------------------------------------------------------------
	// CONTROL
	//--------------------------------------------------------------------------

	/**
	 * Compute the controls for a simulation.
	 *
	 * The caller should send in an initial guess.
	 *
	 * Note that this method is "pure virtual", which means that the Controller
	 * class does not implement it, and that subclasses must implement it.
	 *
	 * @param rDT Integration time step in normalized time that is to be taken
	 * next.  Note that the controller can change the value of rDT.
	 * @param aT Current time in normalized time.
	 * @param aY Current states of the model.
	 * @param rControlSet Control set used for the simulation.  This method
	 * alters the control set in order to control the simulation.
	 */
	virtual void
		computeControls(double &rDT,double aT,const double *aY,
		ControlSet &rX) = 0;

//=============================================================================
};	// END of class Controller

}; //namespace
//=============================================================================
//=============================================================================

#endif // __Controller_h__


