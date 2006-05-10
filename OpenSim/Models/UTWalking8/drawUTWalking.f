c drawUTWalking.f



c===============================================================================

c Draw the UT Walking model

c===============================================================================

      integer function drawutwalking(t,x,y,sforce,spt)



      implicit none

      include 'w23params.h'



      integer status,draw23

      real*8 xaccum

      real*8 sforce(*),spt(*)



      include 'w23comblk.h'



      external draw23



      xaccum = 0.0d0

      pcom(1) = 0.0d0

      pcom(2) = 0.0d0

      pcom(3) = 0.0d0



      drawutwalking = draw23(t,y,nst,pcom,btj,itj,pin,sforce,spt,

     &                       muson,musbod,order,ro,ri,roe,ria,rob,

     &                       viaang,viadof,cylR,cyl,xaccum)





      return

      end




