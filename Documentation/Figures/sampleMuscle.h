class Muscle : public Object 
{
	// SERIALIZED MEMBER VARIABLES
	/** Optimal strength of the muscle. */
	PropertyDbl optimalStrengthProp;

	/** Optimal fiber length. */
	PropertyDbl optimalFiberLengthProp;

	/** Tendon slack length. */
	PropertyDbl tendonSlackLengthProp;

	/** Spherical wrap obstacle. */
	PropertyObj wrapSphereProp;

	// NON-SERIALIZED MEMBER VARIABLES
	/** Calculated total muscle length. */
	double lmt;

	// METHODS BELOW HERE ...
}
