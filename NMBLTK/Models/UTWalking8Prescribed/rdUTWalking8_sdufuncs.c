


//_____________________________________________________________________________
/**
 *  Apply user-supplied forces to the model.
 */
int sduforce(double t, double q[], double u[])
{
   return 1;
}

//_____________________________________________________________________________
/**
 * Apply prescribed motions to fixed and prescribed gencoords.
 */
int sdumotion(double t, double q[], double u[])
{
   return 1;
}


//_____________________________________________________________________________
/**
 *  Calculate position errors for constrained gencoords.
 */
void sduperr(double t, double q[], double errors[])
{
}

//_____________________________________________________________________________
/**
 * Calculate velocity errors for constrained gencoords.
 */
void sduverr(double t, double q[], double u[], double errors[])
{
}

//_____________________________________________________________________________
/**
 * Calculate acceleration errors for constrained gencoords.
 */
void sduaerr(double t, double q[], double u[], double udot[], double errors[])
{
}


//_____________________________________________________________________________
/**
 * Calculate and apply constraint forces for constrained gencoords.
 */
void sduconsfrc(double t, double q[], double u[], double mults[])
{
}

