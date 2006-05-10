      subroutine ydot23(t,ta,tb,idxb,idxe,xb,y,dy)

c  The purpose of this subroutine is to provide an integration routine (runge)
c   with the derivatives of the state-vector (limb positions, limb velocities,
c   actuator forces, and actuator activations).

c==============================================================================
c  Revision record:
c   7/3/93  9:45 am
c==============================================================================
c
c  Input:
c      t = normalized time
c     ta = normalized time of the beginning of the integration interval
c     tb = normalized time of the end of the integration interval
c   idxb = an offset for the index of the control for muscle 1 which points to
c          the beginning of the current interval of integration.
c   idxe = an offset for the index of the control for muscle 1 which points to
c          the ending of the current interval of integration.
c      xb = controls
c      y = state vector
c    sx0 = the x position of a foot spring zero.  Each foot has 5 spring zeros.
c    sz0 = the z position of a foot spring zero.  Each foot has 5 spring zeros.
c          The dimension of sx0 and sz0 is (10) because there are a total of
c          10 springs.
c
c  Output:
c   dy = time derivative of the state vector
c
c
c  In order to do this, "deriv" calls
c
c     force -
c       to apply the muscle and ligament forces and get actuator lengths and
c        shortening velocities,
c
c     sdderiv -
c       to get the accelerations of the joints,
c
c     cntrintpl -
c       to get the excitation signals for each muscle,
c
c     mmatvdot -
c       to get the time derivatives of the muscle activations, and
c
c     mmfdot -
c       to get the time derivatives of actuator force.
c
c  Note that most of the variables used in these subroutines which are not
c   local are declared in "23comblk.h".
c
c  Note also that the order in which the above routines are called is
c   important.
c______________________________________________________________________________


      implicit none

      include 'w23params.h'

      integer i,idxb,idxe
      real*8 sforce(3,ns),spt(3,ns)
      real*8 xt(nmus)

      include 'w23comblk.h'



c  APPLY ALL EXTERNAL FORCES:
      treal = t*xb(bndcntr)
      do i = 1,nq
       q(i) = y(i)
      enddo
      do i = 1,nu
       u(i) = y(nq+i)
      enddo
c --Reset the state for sdfast:
      call sdstate(treal,q,u)
c --Joint ligaments and ground forces:
      call sforce23(treal,q,u,sforce,spt,tqlig)
c --Muscle forces:
      call force23(t,y,q,u)


c  GET ACCELERATIONS AND VELOCITIES:
      call sdderiv(qdot,udot)
      do i = 1,nq
       dy(i) = qdot(i)
      enddo
      do i = 1,nu
       dy(nq+i) = udot(i)
      enddo

c  CALCULATE THE CONTROL VALUES AT THIS TIME STEP:
      call cntrintpl(t,ta,tb,xb,xt,idxb,idxe,nmus)

c  CALCULATE TIME RATE OF CHANGE OF MUSCLE ACTIVATION:
      call mmatvdot(nmus,xt,y(iatv+1),tcrise,tcfall,dy(iatv+1))

c  CALCULATE THE TIME RATE OF CHANGE OF MUSCLE FORCE:
      call mmfdot(nmus,actlen,actsv,
     &            y(imsf+1),y(iatv+1),xt,dy(imsf+1),dy(iint+1))

cccc  SET DERIVATIVES FOR THE PERFORMANCE CRITERION (integral of muscle force)
ccc      do i = 1,nmus
ccc        dy(iint+i) = y(imsf+i)
ccc      enddo
 
c  NORMALIZE THE DERIVATIVES:
      do i = 1,nstpin
       dy(i) = xb(bndcntr) * dy(i)
      enddo


      return
      end
