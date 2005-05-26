      subroutine setmusfrc23(ynode)

c==============================================================================
c  Revision Record:
c   12/14/93  8:00 am
c==============================================================================

      implicit none

      include 'w23params.h'

#ifndef UNIX
	interface to subroutine sdstate
     & [C,ALIAS:'_sdstate_'] (aT,aQ,aU)
	real*8 aT [REFERENCE]
	real*8 aQ(*)
	real*8 aU(*)
	end
#endif

      integer i
      real*8 musfrc

      include 'w23comblk.h'

      external musfrc

c     INITIALIZE TIME
      treal = 0.0d0

c     SET GENERALIZED COORDINATES AND SPEEDS
      do i = 1,nq
        q(i) = ynode(1,i)
      enddo
      do i = 1,nu
        u(i) = ynode(1,nq+i)
      enddo

c     SET STATES
      do i = 1,nstpin
        y(i) = ynode(1,i)
      enddo

c     INITIALIZE SDFAST
      call sdstate(treal,q,u)

c     SET MUSCLE FORCES
      call force23(t,y,q,u)
      do i = 1,nmus
        ynode(1,imsf+i) = musfrc(i,y(iatv+i),actlen(i),actsv(i))
ccc        print*,"musfrc(",i,") = ",ynode(1,imsf+i)
      enddo
  
      return
      end
