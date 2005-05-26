c "jmp54params.h"

c This file contains parameters used in the jmp54 model.

c==============================================================================
c  Revision record:
c   12/14/93  8:45 am
c==============================================================================

c______________________________________________________________________________
c
c   nis = maximum number of integration steps allowed in the nominal forward
c          integration.
c   dof = degrees of freedom
c  dof2 = 2 * dof

c     nmus = number of muscles
c    ncntr = total number of control nodes
c   nnodes = number of control nodes per muscle
c  nintvls = number of control intervals  [nintvls = nnodes-1]

c    nst = number of states
c nstpin = nst + number of additional quantities integrated in the state vector
c           These additional quantities may be muscle stress, fdot, metabolic
c           energy, etc. (Normally, nstpin = nst+1)

c   ivel = an offset pointer for the joint angular velocities in the state
c           vector. For example, the angular velocity of joint i is y(ivel+i).
c   imsf = an offset pointer for the muscle forces in the state vector
c   iatv = an offset pointer for the muscle activations in the state vector

c    nconstr = total number of constraints
c  neqconstr = number of equality constraints. This number is passed to VF02AD
c               as the true number of equality constraints.
c  pseudo_eq = number of pseudo-equality constraints. This is the number of
c               "equality" constraints reported to the remainder of the code.
c               neqconstr = pseudo_eq if true equality constraints are used.
c               Otherwise, pseudo_eq is the number of inequality constraints
c               which are constructed to operate as equality constraints
c               (e.g., pseudo_eq=1  if an inequality constraint is defined
c               such that c(1) = -abs(fv)/1000.0 ).

c      nndcs = number of constraints defined at each node.

c   npen = number of penalty functions

c   lw = the workspace size of VF02AD
c     >=  5*ncntr^2 + 19*ncntr + 14 + 3*nconstr + (nconstr+1)/2
c           + max( nconstr , 3*ncntr+3 )

c  dtr = conversion factor from degrees to radians
c  rtd = conversion factor from radians to degrees

c  tcrise = muscle activation rise time constant.
c  tcfall = muscle activation decay time constant.

c   maxstep = dimension of the output arrays in "jmp54arry".
c             This should be nis*nnodes, but this is often way too large.
c    maxtry = dimension of the error array in "jmp54nomvrunge".
c             This should be int( dble(nnodes*nis)/mindelta ), but this is even
c             more outrageous than the required size of maxstep. Try something
c             like 2*maxstep.

c      ncntri = number of controls for the initialization program
c    nconstri = number of constraints for the initialization program
c  neqconstri = number of equality contstraints for the initialization program.
c  pseudo_eqi = number of pseudo-equality constraints for the initialization
c                program (See "pseudo_eq" above)
c_______________________________________________________________________________


      integer dof,dof2,nmus,nmushalf
      integer nst,nstpin
      integer nbod,njnt,nq,nu,ns
      integer ivel,imsf,iatv,iint
      integer nnodes,nintvls,ncntr,muscntr
      integer bndcntr,vcntr
      integer nconstr,neqconstr,pseudo_eq,nndcs
      integer npen,lw
      integer maxstep,maxtry
      integer ncntr1,nconstr1,neqconstr1,pseudo_eq1
      integer ncntr2,nconstr2,neqconstr2,pseudo_eq2

      real*8  dtr,rtd,tcrise,tcfall
      real*8  tfinal

c final time
ccc      parameter(tfinal = 0.60d0)
      parameter(tfinal = 0.56d0)

c main
      parameter(dof=23,dof2=46,nmus=54,nmushalf=27)
      parameter(nst=155,nstpin=425)
      parameter(nbod=10,njnt=10,nq=24,nu=23,ns=10)
      parameter(ivel=24,imsf=47,iatv=101,iint=155)

ccc      parameter(nnodes=16,nintvls=15,ncntr=810,muscntr=810)
ccc      parameter(bndcntr=865)
      parameter(nnodes=15,nintvls=14)
      parameter(ncntr=810,muscntr=810,bndcntr=811,vcntr=162)

      parameter(nconstr=90,neqconstr=0,pseudo_eq=90,nndcs=0)
      parameter(npen=5,lw=8000000)
      parameter(dtr=0.01745329252d0,rtd=57.2957795132d0)

c muscle
ccc   NOMINAL
      parameter(tcrise=45.d0,tcfall=5.d0)
ccc     parameter(tcrise=45.d0,tcfall=5.d0)
ccc   TYPICAL
ccc   parameter(tcrise=100.d0,tcfall=20.d0)
ccc   SHORT
ccc      parameter(tcrise=90.909d0,tcfall=14.706d0)
ccc   REALLY SHORT FOR TRACKING TEST
ccc      parameter(tcrise=200.d0,tcfall=200.d0)
ccc   SAME RISE AND DECAY
ccc      parameter(tcrise=45.d0,tcfall=90.d0)


c output arrays
      parameter(maxstep=8000,maxtry=9500)

c initialization
      parameter(ncntr1=4,nconstr1=2,neqconstr1=0,pseudo_eq1=2)
      parameter(ncntr2=27,nconstr2=10,neqconstr2=10,pseudo_eq2=0)



