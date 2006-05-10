c w23parameters.f

c Routines for setting and getting parameters for the walking model.





c============================================================
c SET THE FORCE OF A MUSCLE
c============================================================
      subroutine setfom(aMuscle,aFOM)
      implicit none
      include 'w23params.h'
      integer aMuscle
		real*8 aFOM
      include 'w23comblk.h'

      fom(aMuscle) = aFOM

      return
      end

c============================================================
c GET THE FORCE OF A MUSCLE
c============================================================
      real*8 function getfom(aMuscle)
      implicit none
      include 'w23params.h'
      integer aMuscle
      include 'w23comblk.h'

      getFOM = fom(aMuscle)

      return
      end




c============================================================

c GET LENGTHS OF THE ACTUATORS

c============================================================

      subroutine getactuatorlengths(aLengths)



      implicit none

      include 'w23params.h'



      integer i

      real*8 aLengths(nmus)

 

      include 'w23comblk.h'



      do i=1,nmus

        aLengths(i) = actlen(i)

      enddo



      return

      end



c============================================================

c GET VELOCITIES OF THE ACTUATORS

c============================================================

      subroutine getactuatorvelocities(aVelocities)



      implicit none

      include 'w23params.h'



      integer i

      real*8 aVelocities(nmus)

 

      include 'w23comblk.h'



      do i=1,nmus

        aVelocities(i) = actsv(i)

      enddo



      return

      end



c===============================================================================

c SET WHICH MUSCLES TO DRAW

c===============================================================================

      subroutine setmuson(mus,onoff)



      implicit none

      include 'w23params.h'



      integer mus,onoff



      include 'w23comblk.h'



      muson(mus) = onoff



      return

      end




