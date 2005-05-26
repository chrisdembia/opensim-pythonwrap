// testSimulation.cpp
// Author:  Frank C. Anderson


// INCLUDES
#include <iostream>
#include <string>
#include <iostream>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdObject.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdException.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Tools/rdIO.h>
#include <RD/Tools/rdXMLDocument.h>
#include <RD/Tools/rdArray.h>
#include <RD/Tools/rdPropertyInt.h>
#include <RD/Tools/rdPropertyDbl.h>
#include <RD/Tools/rdPropertyStr.h>
#include <RD/Tools/rdPropertyIntArray.h>
#include <RD/Tools/rdPropertyStrArray.h>
#include <RD/Tools/rdPropertyObjArray.h>
#include <RD/Simulation/Control/rdControlLinearNode.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Control/rdControlConstant.h>
#include <RD/Simulation/Control/rdControlSet.h>
#include <RD/Simulation/Model/rdForce.h>
#include <RD/Simulation/Model/rdGeneralizedForce.h>
#include <RD/Actuators/rdGeneralizedForceAtv.h>
#include <RD/Simulation/Model/rdActuatorSet.h>
#include <RD/Actuators/rdLinearSetPoint.h>
#include <RD/Actuators/rdPolynomialSetPoint.h>
#include <RD/Simulation/Model/rdContactForceSet.h>


using namespace std;


// DECLARATIONS
void TestControlLinearNode();
void TestControlLinear();
void TestControlSet1();
void TestControlSet2();
void TestControlSerialization();
void TestControlSetSerialization();
void TestActuatorSetSerialization();
void TestContactForceSetSerialization();


//_____________________________________________________________________________
/**
 * Test the rdSimulation library.
 */
int main(int argc, char* argv[])
{
	// PARSE COMMAND LINE

	// CONTROLS
	//TestControlLinearNode();
	//TestControlLinear();
	//TestControlSet1();
	//TestControlSet2();
	//TestControlSerialization();
	//TestControlSetSerialization();
	//TestActuatorSetSerialization();
	//TestContactForceSetSerialization();

	return(0);
}


//_____________________________________________________________________________
/**
 * Test the serialization of a contact force set.
 */
void TestContactForceSetSerialization()
{

	//=============
	// OUTPUT
	//=============
	//-------------
	// EMPTY CONTROL SET
	//-------------
	rdContactForceSet contactSet1;
	contactSet1.setName("contactSet1");
	
	//-------------
	// rdLinearSetPoint
	//-------------
	rdLinearSetPoint linear;
	linear.setName("s1");
	contactSet1.append(&linear);

	//-------------
	// rdPolynomialSetPoint
	//-------------
	rdPolynomialSetPoint poly;
	poly.setName("s2");
	contactSet1.append(&poly);

	//-------------
	// PRINT
	//-------------
	contactSet1.print("contactSet1.ctx");


	//=============
	// INPUT
	//=============
	//-------------
	// REGISTER OBJECT TYPES
	//-------------
	rdObject::RegisterType(linear);
	rdObject::RegisterType(poly);

	//-------------
	// READ CONTACT SET
	//-------------
	rdContactForceSet contactSet2("fallingBlock.ctx");
	contactSet2.setName("contactSet2");
	int index=0;
	rdContactForce *ctx = (rdContactForce*)contactSet2.get(index);
	cout<<"\n\n"<<ctx->getName()<<endl;
	ctx->check();
	rdPropertySet &propSet = ctx->getPropertySet();
	rdProperty *propA = propSet.get("body_A");
	rdProperty *propB = propSet.get("body_B");
	cout<<endl;
	cout<<"\nproperty address "<<propA<<endl;
	cout<<propA<<": "<<propA->getValueInt()<<endl;
	cout<<"\nproperty address "<<propB<<endl;
	cout<<propB<<": "<<propB->getValueInt()<<endl;
	cout<<endl;

	propA->setValue((int)3);
	cout<<"\nproperty address "<<propA<<endl;
	cout<<propA<<": "<<propA->getValueInt()<<endl;

	ctx->check();


	//-------------
	// PRINT
	//-------------
	contactSet2.updateXMLNode(NULL);
	contactSet2.print("contactSet2.act");
}

//_____________________________________________________________________________
/**
 * Test the serialization of an actuator set.
 */
void TestActuatorSetSerialization()
{

	//=============
	// REGISTER
	//=============
	rdObject::RegisterType(rdForce());
	rdObject::RegisterType(rdGeneralizedForce());
	rdObject::RegisterType(rdGeneralizedForceAtv());

	
	//=============
	// OUTPUT
	//=============
	//-------------
	// EMPTY CONTROL SET
	//-------------
	rdActuatorSet actuatorSet1;
	actuatorSet1.setName("actuatorSet1");
	actuatorSet1.setMemoryOwner(false);
	
	//-------------
	// 0 rdForce
	//-------------
	rdForce force1;
	force1.setName("force1");
	actuatorSet1.append(&force1);

	//-------------
	// 1 rdForce
	//-------------
	rdForce force2;
	force2.setName("force2");
	actuatorSet1.append(&force2);

	//-------------
	// 2 rdGeneralizedForceAtv
	//-------------
	rdGeneralizedForceAtv genForceAtv1;
	genForceAtv1.setName("genForceAtv1");
	actuatorSet1.append(&genForceAtv1);

	//-------------
	// 3 rdGeneralizedForce
	//-------------
	rdGeneralizedForce genForce1;
	genForce1.setName("genForce1");
	actuatorSet1.append(&genForce1);

	//-------------
	// 4 rdGeneralizedForceAtv
	//-------------
	rdGeneralizedForceAtv genForceAtv2;
	genForceAtv2.setName("genForceAtv2");
	actuatorSet1.append(&genForceAtv2);

	//-------------
	// 5 rdForce
	//-------------
	rdForce force3;
	force3.setName("force3");
	actuatorSet1.append(&force3);

	//-------------
	// PRINT
	//-------------
	actuatorSet1.print("actuatorSet1.act");


	//=============
	// INPUT
	//=============

	//-------------
	// READ
	//-------------
	rdActuatorSet actuatorSet2("actuatorSet1.act");
	actuatorSet2.setName("actuatorSet2");
	actuatorSet2.updateXMLNode(NULL);

	//-------------
	// PRINT
	//-------------
	actuatorSet2.print("actuatorSet2.act");


	//=============
	// ASSIGNMENT
	//=============
	rdActuatorSet actuatorSet;
	actuatorSet = actuatorSet2;
	actuatorSet.setMemoryOwner(true);
	actuatorSet.setName("AssignedToActuatorSet2");
	actuatorSet.print("actuatorSetAssigned.act");
}


//_____________________________________________________________________________
/**
 * Test the serialization of a control set.
 */
void TestControlSetSerialization()
{

	//=============
	// OUTPUT
	//=============
	//-------------
	// EMPTY CONTROL SET
	//-------------
	rdControlSet controlSet1;
	controlSet1.setName("testSet1");
	
	//-------------
	// CONSTANT
	//-------------
	// 0
	rdControlConstant cntrConst;
	cntrConst.setName("tf");
	controlSet1.append(&cntrConst);

	//-------------
	// LINEAR
	//-------------
	// 1
	rdControlLinear cntrLin;
	cntrLin.setName("soleus");
	controlSet1.append(&cntrLin);
	// 2
	cntrLin.setName("gastroc");
	controlSet1.append(&cntrLin);


	//-------------
	// GET & SET CONTROL VALUES
	//-------------
	int i;
	double t;
	rdArray<double> x(0.0);
	controlSet1.getControlValues(0.0,x);
	cout<<x<<endl;
	for(t=1.0;t<=10.0;t++) {
		for(i=0;i<x.getSize();i++) x[i] = t;
		controlSet1.setControlValues(t,x);
	}
	controlSet1.getControlValues(1.1,x);
	cout<<x<<endl;

	//-------------
	// PRINT
	//-------------
	controlSet1.print("controlSet1.ctr");


	//=============
	// INPUT
	//=============
	//-------------
	// REGISTER OBJECT TYPES
	//-------------
	rdObject::RegisterType(rdControlConstant());
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// LOAD
	rdControlSet controlSet2("controlSet1.ctr");

	// GET VALUES
	controlSet2.setControlValues(0.0,x);
	controlSet2.getControlValues(0.0,x);
	cout<<x<<endl;
	controlSet2.getControlValues(8.4,x);
	cout<<x<<endl;
	controlSet2.setControlValues(4.2,x);
	controlSet2.getControlValues(4.2,x);
	cout<<x<<endl;

	// PRINT
	controlSet2.setName("testSet2");
	controlSet2.updateXMLNode(NULL);
	controlSet2.print("controlSet2.ctr");


	//=============
	// INPUT WITH DEFAULTS
	//=============
	//-------------
	// READ CONTROL SET
	//-------------
	rdControlSet controlSetDefaults("controlSetWithDefaults.ctr");
	controlSetDefaults.setName("testSetDefaults");
	controlSetDefaults.updateXMLNode(NULL);

	//-------------
	// PRINT
	//-------------
	controlSetDefaults.print("controlSetDefaults.ctr");
}


//_____________________________________________________________________________
/**
 * Test the serialization of the control types.
 * Right now only rdControlConstant and rdControlLinear are tested.
 */
void TestControlSerialization()
{
	//-------------
	// CONSTANT
	//-------------
	rdControlConstant cntrConst;
	cntrConst.print("const.ctr");

	// MEMORY LEAK TESTING
	rdArrayPtrs<rdObject> nodes;
	nodes.append( new rdControlLinearNode() );
	rdPropertyObjArray *objArray = new rdPropertyObjArray("nodes",nodes);
	delete objArray;

	//-------------
	// LINEAR
	//-------------
	rdControlLinear cntrLin;
	rdPropertySet &properties = cntrLin.getPropertySet();
	rdProperty *property = properties.get("nodes");
	rdArrayPtrs<rdObject> &value = property->getValueObjArray();
	cout << "value size = " << value.getSize() << endl;
	cntrLin.print("linear.ctr");
}

//_____________________________________________________________________________
/**
 * Test the parameter methods of rdControlSet.
 */
void TestControlSet2()
{
	rdIO::SetPrecision(8);

	// REGISTER CONTROL TYPES
	rdControlConstant controlConstant;
	rdControlLinear controlLinear;
	rdControlSet::RegisterType(controlConstant);
	rdControlSet::RegisterType(controlLinear);

	// READ IN TEST FILE
	rdControlSet controlSet("test.ctr");

	// GET PARAMETER LISTS
	int i,j;
	// Lower, Upper
	double tLower=rdMath::MINUS_INFINITY,tUpper=10.0;
	rdArray<int> list(-1);
	controlSet.getParameterList(tLower,tUpper,list);
	printf("parameters (%lf,%lf):",tLower,tUpper);
	for(i=0;i<list.getSize();i++) {
		printf(" %d",list[i]);
	}
	printf("\n\n");
	// Time
	double t = 0.41;
	controlSet.getParameterList(t,list);
	printf("parameters (%lf):",t);
	for(i=0;i<list.getSize();i++) {
		printf(" %d",list[i]);
	}
	printf("\n\n");

	// ADD A BUNCH OF CONTROL PARAMETERS
	double dt = 0.1;
	rdArray<double> x(0.0);
	x.setSize(controlSet.getSize());
	for(t=0.6,i=0;i<200;i++,t+=dt) {
		for(j=0;j<x.getSize();j++) {
			x[j] = (double)i;
		}
		controlSet.setControlValues(t,x);
	}
	controlSet.print("testLarge.ctr");
	rdControlSet controlSet2("testLarge.ctr");
	controlSet2.print("testLargeCopy.ctr");

	// GET PARAMETERS AND SET PARAMETERS- A PERFORMANCE TEST
	// List
	tLower=20.4,tUpper=20.5;
	controlSet.getParameterList(tLower,tUpper,list);
	printf("parameters (%lf,%lf):",tLower,tUpper);
	for(i=0;i<list.getSize();i++) {
		printf(" %d",list[i]);
	}
	printf("\n\n");
	// Get
	rdArray<double> p(0.0);
	controlSet.getParameterValues(p,&list);
	for(i=0;i<p.getSize();i++) {
		printf("p[%d] = %lf\n",list[i],p[i]);
	}
	// Set
	for(i=0;i<p.getSize();i++) {
		p[i] = 10000.0;
	}
	controlSet.setParameterValues(p,&list);
	controlSet.print("testLargeAltered.ctr");
}

//_____________________________________________________________________________
/**
 * Test basic features of rdControlSet.
 */
void TestControlSet1()
{
	rdIO::SetScientific(true);

	// REGISTER CONTROL TYPES
	rdControlConstant controlConstant;
	rdControlLinear controlLinear;
	rdControlSet::RegisterType(controlConstant);
	rdControlSet::RegisterType(controlLinear);

	// PRINT DEFAULT FILE
	rdControlSet defaultSet;
	defaultSet.setName("test");
	defaultSet.print("default.ctr");

	// READ IN AND WRITE OUT TEST FILE
	rdControlSet controlSet("test.ctr");
	controlSet.print("testCopy.ctr");

	// GET A PARTICULAR CONTROL
	int index = controlSet.getIndex("targetDT");
	rdControl *control = controlSet.get(index);
	if(control!=NULL) {
		printf("targetDT = %lf\n",control->getControlValue(0.0));
	} else {
		printf("Control for ankleVelocity not found.\n");
	}

	// GET ACTUATOR CONTROLS
	double t = 0.15;
	rdArray<double> x(0.0);
	rdArray<int> list(-1);
	controlSet.getControlList("rdControlLinear",list);
	controlSet.getControlValues(t,x,false);
	int i;
	printf("t=%lf\n",t);
	for(i=0;i<list.getSize();i++) {
		control = controlSet.get(list[i]);
		cout<<control->getName()<<": "<<x[list[i]]<<endl;
	}

	// GET PARAMETERS
	rdArray<double> p(0.0);
	controlSet.getParameterValues(p,false);
	printf("parameters: ");
	for(i=0;i<p.getSize();i++) {
		printf(" %lf",p[i]);
	}
	printf("\n");

	// ALTER PARAMETERS
	p[0] = -1.21;
	p[1] = 100.0;
	p[2] = 200.0;
	p[3] = 400.0;
	p[4] = 500.0;
	p[5] = 600.0;
	p[6] = 700.0;
	p[7] = 800.0;
	p[8] = 900.0;
	controlSet.setParameterValues(p,false);

	// GET CONTROLS AGAIN
	index = controlSet.getIndex("targetDT");
	printf("targetDT = %lf\n",controlSet.get(index)->getControlValue(t));
	controlSet.getControlList("rdControlLinear",list);
	controlSet.getControlValues(t,x);
	printf("t=%lf\n",t);
	for(i=0;i<list.getSize();i++) {
		control = controlSet.get(list[i]);
		cout<<control->getName()<<": "<<x[list[i]]<<endl;
	}

}

///_____________________________________________________________________________
/**
 * Test rdControlLinear.
 */
void TestControlLinear()
{
	rdIO::SetScientific(true);

	// CONSTRUCT
	rdControlLinear control;

	// SET VALUES
	int i,n=10;
	for(i=0;i<n;i++) {
		control.setControlValue((double)i,(double)i);
	}

	// GET VALUES
	double t,dt=0.1;
	printf("\nsize = %ld\n",control.getNumParameters());
	for(t=-1.0;t<=n;t+=dt) {
		printf("%lf %lf\n",t,control.getControlValue(t));
	}

	// CHANGE CONTROL VALUES
	for(i=0;i<n;i++) {
		control.setControlValue((double)i,2.0*(double)i);
	}
	control.setControlValue(0.5,-10.0);

	// GET VALUES
	printf("\nsize = %ld\n",control.getNumParameters());
	for(t=-1.0;t<=n;t+=dt) {
		printf("%lf %lf\n",t,control.getControlValue(t));
	}


	printf("\n\n");
}

//_____________________________________________________________________________
/**
 * Test rdControlLinearNode.
 */
void TestControlLinearNode()
{
	rdIO::SetScientific(true);

	// ARRAY OF NODES
	rdControlLinearNode node;
	rdArray<rdControlLinearNode> nodes(node);

	// APPEND TO ARRAY
	int i,n=10;
	for(i=0;i<n;i++) {
		node.setTime((double)i);
		nodes.append(node);
	}

	// PRINT
	char *tmp;
	for(i=0;i<nodes.getSize();i++) {
		tmp = nodes[i].toString();
		printf("node[%d]: %s\n",i,tmp);
		if(tmp!=NULL) delete[] tmp;
	}

	// FIND NODE
	node.setTime(2.9);
	int index = nodes.searchBinary(node);
	printf("node[%d] = %lf\n",index,nodes[index].getTime());

	// EQUALITY
	rdControlLinearNode n1(0.0),n2(1.0e-14);
	printf("\nEQUALITY TEST\n");
	printf("n1: %s\n",n1.toString());
	printf("n2: %s\n",n2.toString());
	printf("\nnode equality tolerance = %le\n",node.GetEqualityTolerance());
	if(n1==n2) printf("equal = true\n");
	else printf("equal = false\n");

	node.SetEqualityTolerance(0.0);
	printf("\nnode equality tolerance = %le\n",node.GetEqualityTolerance());
	if(n1==n2) printf("equal = true\n");
	else printf("equal = false\n");

	node.SetEqualityTolerance(0.1);
	printf("\nnode equality tolerance = %le\n",node.GetEqualityTolerance());
	if(n1==n2) printf("equal = true\n");
	else printf("equal = false\n");


	printf("\n\n");
}
