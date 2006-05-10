      subroutine spring23(q,u,sforce,spt)
c--------------------------------------------------------------

      implicit none

      include 'w23params.h'

      integer i,j
      real*8 sforce(3,ns),spt(3,ns),sptv(3,ns)
      real*8 flimit
     
      include 'w23comblk.h'
 
      do i = 1,ns

      call sdpos(sbody(i),bodyspt(1,i),spt(1,i))
      call sdvel(sbody(i),bodyspt(1,i),sptv(1,i))

      sforce(1,i) = -sk*(spt(1,i)-sx0(i))-sdamp*sptv(1,i)
      flimit = dsign(mu*sforce(2,i),sforce(1,i))
      if (dabs(sforce(1,i)).gt.dabs(flimit)) then       
       sx0(i) = spt(1,i) + (flimit+sdamp*sptv(1,i))/sk
       sforce(1,i) = flimit
      endif

      sforce(3,i) = -sk*(spt(3,i)-sz0(i))-sdamp*sptv(3,i)
      flimit = dsign(mu*sforce(2,i),sforce(3,i))
      if (dabs(sforce(3,i)).gt.dabs(flimit)) then       
       sz0(i) = spt(3,i) + (flimit+sdamp*sptv(3,i))/sk
       sforce(3,i) = flimit
      endif

      enddo

      return
      end
