#include <cassert>


/*


 According to my reading of the C standard, arrays and pointers are equivalent
 as  formal parameters (i.e. arrays are passed by reference)  In practical
 terms this probably requires that the parameter passing procedures for
 int*, int[], and int[][] are equivalent.  I would like to find out about
 any exceptions to this.
    - PVE


*/

void sdmassmat( double *I );

void rd_sdmassmat( double *I )
{
   assert( I );
   sdmassmat( I );
}