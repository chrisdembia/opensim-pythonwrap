class Muscle : public Object 
{
	// VARIABLE MEMBERS
	/** Optimal strength of the muscle. */
	PropertyDbl optimalStrengthProp;
	double &optimalStrength;

	/** Optimal fiber length. */
	PropertyDbl optimalFiberLengthProp;
	double &optimalFiberLength;

	/** Tendon slack length. */
	PropertyDbl tendonSlackLengthProp;
	double &tendonSlackLength;

	/** Spherical wrap obstacle. */
	PropertyObj wrapSphereProp;
	WrapSphere &wrapSphere;

	// METHODS BELOW HERE ...
}
