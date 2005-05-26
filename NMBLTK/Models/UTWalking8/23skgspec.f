      subroutine skgspec23(skgsrq,nmus,mpt,musbod,order,
     &           ro,ri,roe,rob,ria,vialen,viaang,viaadd,viadof)

c  This subroutine returns standard skeletal geometry values for those muscles
c   requested by the user.

c==============================================================================
c  Revision record:
c   6/10/93  8:45 am
c==============================================================================

c  Input:
c   skgsrq = an assumed length character string indicating which skeletal
c             geometry set is requested.
c     nmus = number of muscles (>0)  
c      mpt = a vector specifying which skeletal geometry data from the
c            specified set are requested.
c
c  Output:
c       ro = muscle origin
c       ri = muscle insertion
c
c      roe = effective origin due to a via point
c      rob = effective origin for the distal segment of split muscles
c      ria = effective insertion for the proximal segment of split muscles
c
c   vialen = length adjustment due to via points
c   viaang = joint angle at which a "sometimes" via point becomes active
c   viaadd = length which must be added when a "sometimes" via point becomes
c            active
c______________________________________________________________________________


      implicit none

      integer nmus,mpt(nmus),musbod(5,nmus),order(5,nmus),viadof(nmus)
      real*8 ro(3,nmus),ri(3,nmus),roe(3,nmus),rob(3,nmus),ria(3,nmus)
      real*8 vialen(nmus),viaang(nmus),viaadd(nmus)

      integer i,nload,mmax
      parameter (mmax=101)

      integer smusbod(5,mmax),sorder(5,mmax),sviadof(mmax)
      real*8 sro(3,mmax),sri(3,mmax),sroe(3,mmax),srob(3,mmax)
      real*8 sria(3,mmax),svialen(mmax),sviaang(mmax),sviaadd(mmax)
      real*8 dtr

      logical ex

      character*6 mflag
      character*(*) skgsrq



c  Define the degrees to radians conversion factor:
      dtr = dasin(1.d0) / 90.d0



c  Error checking -------------------------------------------------------------

c   Check for none or too many muscles:
      if(nmus .lt. 1)then
       write(6,200)
       write(6,300)
       stop

      elseif(nmus .gt. mmax)then
       write(6,200)
       write(6,400)mmax
       stop

      endif

c  ----------------------------------------------------------------------------


c  Load the specified skeletal geometry set -----------------------------------

      inquire(file=skgsrq,exist=ex)

      if(.not. ex)then
       write(6,200)
       write(6,700)skgsrq
       stop
      endif


      open(4,file=skgsrq)


      nload = 0
10    read(4,100,end=20)mflag
      call lowercase(mflag)

      if(mflag .eq. 'muscle')then

       nload = nload + 1
       if(nload .gt. mmax)then
        write(6,600)mmax
        stop
       endif

       read(4,*)(smusbod(i,nload),i=1,5)
       read(4,*)(sorder(i,nload),i=1,5)
       read(4,*)(sro(i,nload),i=1,3),(sri(i,nload),i=1,3)
       read(4,*)(sroe(i,nload),i=1,3)
       read(4,*)(srob(i,nload),i=1,3),(sria(i,nload),i=1,3)
       read(4,*)svialen(nload),sviaang(nload),sviaadd(nload)
       read(4,*)sviadof(nload)

      endif

      go to 10

20    close(4)

c  ----------------------------------------------------------------------------



c  More error checking --------------------------------------------------------

c   Check for bad muscle specification:
      do i = 1,nmus

       if((mpt(i) .lt. 1) .or. (mpt(i) .gt. nload))then
        write(6,200)
        write(6,500)i
        stop
       endif

      enddo

c  ----------------------------------------------------------------------------




c  Load the specified skeletal geometry parameters ----------------------------

      do i = 1,nmus

       musbod(1,i) = smusbod(1,mpt(i))
       musbod(2,i) = smusbod(2,mpt(i))
       musbod(3,i) = smusbod(3,mpt(i))
       musbod(4,i) = smusbod(4,mpt(i))
       musbod(5,i) = smusbod(5,mpt(i))

       order(1,i) = sorder(1,mpt(i))
       order(2,i) = sorder(2,mpt(i))
       order(3,i) = sorder(3,mpt(i))
       order(4,i) = sorder(4,mpt(i))
       order(5,i) = sorder(5,mpt(i))

       ro(1,i) = sro(1,mpt(i))
       ro(2,i) = sro(2,mpt(i))
       ro(3,i) = sro(3,mpt(i))

       ri(1,i) = sri(1,mpt(i))
       ri(2,i) = sri(2,mpt(i))
       ri(3,i) = sri(3,mpt(i))

       roe(1,i) = sroe(1,mpt(i))
       roe(2,i) = sroe(2,mpt(i))
       roe(3,i) = sroe(3,mpt(i))

       rob(1,i) = srob(1,mpt(i))
       rob(2,i) = srob(2,mpt(i))
       rob(3,i) = srob(3,mpt(i))

       ria(1,i) = sria(1,mpt(i))
       ria(2,i) = sria(2,mpt(i))
       ria(3,i) = sria(3,mpt(i))

       vialen(i) = svialen(mpt(i))
       viaang(i) = sviaang(mpt(i)) * dtr
       viaadd(i) = sviaadd(mpt(i))
       viadof(i) = sviadof(mpt(i))

      enddo

c -----------------------------------------------------------------------------



      return


100   format(a)
200   format(/,1x,'** ERROR **')
300   format(1x,'At least one muscle must be specified.')
400   format(1x,'Too many muscles have been specified. The maximum allow
     &ed = ',i3,'.')
500   format(1x,'Invalid muscle specification for muscle number ',i3,'.'
     &)
600   format(1x,'Too many muscles in input file. The maximum allowed = '
     & ,i3,'.')
700   format(1x,'Cannot access muscle set ',a)


      end





      subroutine lowercase(string)

c  This subroutine converts a string to all lower case.

      implicit none

      integer i,strlen,ascnum
      character*(*) string


      strlen = len(string)

      do 5 i = 1,strlen

       ascnum = ichar(string(i:i))

       if((ascnum .gt. 64) .and. (ascnum .lt. 91))then
        string(i:i) = char(ascnum+32)
       endif

5     continue

      return
      end
