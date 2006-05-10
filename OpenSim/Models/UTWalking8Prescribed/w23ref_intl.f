      subroutine ref_intl23

c  This subroutine transforms the coordinates of the actuators and the knee
c   ligaments from the standard reference frames to the dynamical equations
c   reference frames.

c==============================================================================
c  Revision record:
c   11/19/93  7:15 pm
c==============================================================================

      implicit none

      include 'w23params.h'

      integer i,j
      real*8 footang 

      include 'w23comblk.h'


c  Transform the skeletal geometry values from the standard reference frames
c   to the dynamical equations reference frames:

c  Set a rotation angle for the foot frame:
      footang = dtr * 5.0

c RFDH -----

      ro(1,rfdh) = ro(1,rfdh) + rfo(1,rhindfoot)
      ro(2,rfdh) = ro(2,rfdh) + rfo(2,rhindfoot)
      ro(3,rfdh) = ro(3,rfdh) + rfo(3,rhindfoot)

      ri(1,rfdh) = ri(1,rfdh) + rfo(1,rtoes)
      ri(2,rfdh) = ri(2,rfdh) + rfo(2,rtoes)
      ri(3,rfdh) = ri(3,rfdh) + rfo(3,rtoes)



c  REDH -----

      ro(1,redh) = ro(1,redh) + rfo(1,rhindfoot)
      ro(2,redh) = ro(2,redh) + rfo(2,rhindfoot)
      ro(3,redh) = ro(3,redh) + rfo(3,rhindfoot)

      ri(1,redh) = ri(1,redh) + rfo(1,rtoes)
      ri(2,redh) = ri(2,redh) + rfo(2,rtoes)
      ri(3,redh) = ri(3,redh) + rfo(3,rtoes)



c  RDFIN -----

      ro(1,rdfin) = ro(1,rdfin) + rfo(1,rtibia)
      ro(2,rdfin) = ro(2,rdfin) + rfo(2,rtibia)
      ro(3,rdfin) = ro(3,rdfin) + rfo(3,rtibia)

      ri(1,rdfin) = ri(1,rdfin) + rfo(1,rhindfoot)
      ri(2,rdfin) = ri(2,rdfin) + rfo(2,rhindfoot)
      ri(3,rdfin) = ri(3,rdfin) + rfo(3,rhindfoot)

      call yrotate(ri(1,rdfin),footang,ri(1,rdfin))


c  RDFEV -----

      ro(1,rdfev) = ro(1,rdfev) + rfo(1,rtibia)
      ro(2,rdfev) = ro(2,rdfev) + rfo(2,rtibia)
      ro(3,rdfev) = ro(3,rdfev) + rfo(3,rtibia)

      ri(1,rdfev) = ri(1,rdfev) + rfo(1,rhindfoot)
      ri(2,rdfev) = ri(2,rdfev) + rfo(2,rhindfoot)
      ri(3,rdfev) = ri(3,rdfev) + rfo(3,rhindfoot)

      call yrotate(ri(1,rdfev),footang,ri(1,rdfev))


c  ROPFIN -----

      ro(1,ropfin) = ro(1,ropfin) + rfo(1,rtibia)
      ro(2,ropfin) = ro(2,ropfin) + rfo(2,rtibia)
      ro(3,ropfin) = ro(3,ropfin) + rfo(3,rtibia)

      ri(1,ropfin) = ri(1,ropfin) + rfo(1,rhindfoot)
      ri(2,ropfin) = ri(2,ropfin) + rfo(2,rhindfoot)
      ri(3,ropfin) = ri(3,ropfin) + rfo(3,rhindfoot)

      call yrotate(ri(1,ropfin),footang,ri(1,ropfin))


c  ROPFEV -----

      ro(1,ropfev) = ro(1,ropfev) + rfo(1,rtibia)
      ro(2,ropfev) = ro(2,ropfev) + rfo(2,rtibia)
      ro(3,ropfev) = ro(3,ropfev) + rfo(3,rtibia)

      ri(1,ropfev) = ri(1,ropfev) + rfo(1,rhindfoot)
      ri(2,ropfev) = ri(2,ropfev) + rfo(2,rhindfoot)
      ri(3,ropfev) = ri(3,ropfev) + rfo(3,rhindfoot)

      call yrotate(ri(1,ropfev),footang,ri(1,ropfev))


c  RSOL -----

      ro(1,rsol) = ro(1,rsol) + rfo(1,rtibia)
      ro(2,rsol) = ro(2,rsol) + rfo(2,rtibia)
      ro(3,rsol) = ro(3,rsol) + rfo(3,rtibia)

      ri(1,rsol) = ri(1,rsol) + rfo(1,rhindfoot)
      ri(2,rsol) = ri(2,rsol) + rfo(2,rhindfoot)
      ri(3,rsol) = ri(3,rsol) + rfo(3,rhindfoot)

      call yrotate(ri(1,rsol),footang,ri(1,rsol))


c  RGAS -----

      ro(1,rgas) = ro(1,rgas) + rfo(1,rfemur)
      ro(2,rgas) = ro(2,rgas) + rfo(2,rfemur)
      ro(3,rgas) = ro(3,rgas) + rfo(3,rfemur)

      ri(1,rgas) = ri(1,rgas) + rfo(1,rhindfoot)
      ri(2,rgas) = ri(2,rgas) + rfo(2,rhindfoot)
      ri(3,rgas) = ri(3,rgas) + rfo(3,rhindfoot)

      ria(1,rgas) = ria(1,rgas) + rfo(1,rtibia)
      ria(2,rgas) = ria(2,rgas) + rfo(2,rtibia)
      ria(3,rgas) = ria(3,rgas) + rfo(3,rtibia)

      rob(1,rgas) = rob(1,rgas) + rfo(1,rtibia)
      rob(2,rgas) = rob(2,rgas) + rfo(2,rtibia)
      rob(3,rgas) = rob(3,rgas) + rfo(3,rtibia)

      roe(1,rgas) = roe(1,rgas) + rfo(1,rfemur)
      roe(2,rgas) = roe(2,rgas) + rfo(2,rfemur)
      roe(3,rgas) = roe(3,rgas) + rfo(3,rfemur)

      call yrotate(ri(1,rgas),footang,ri(1,rgas))


c  RBFSH -----

      ro(1,rbfsh) = ro(1,rbfsh) + rfo(1,rfemur)
      ro(2,rbfsh) = ro(2,rbfsh) + rfo(2,rfemur)
      ro(3,rbfsh) = ro(3,rbfsh) + rfo(3,rfemur)

      ri(1,rbfsh) = ri(1,rbfsh) + rfo(1,rtibia)
      ri(2,rbfsh) = ri(2,rbfsh) + rfo(2,rtibia)
      ri(3,rbfsh) = ri(3,rbfsh) + rfo(3,rtibia)

      roe(1,rbfsh) = roe(1,rbfsh) + rfo(1,rfemur)
      roe(2,rbfsh) = roe(2,rbfsh) + rfo(2,rfemur)
      roe(3,rbfsh) = roe(3,rbfsh) + rfo(3,rfemur)



c  RVAS -----

      ro(1,rvas) = ro(1,rvas) + rfo(1,rfemur)
      ro(2,rvas) = ro(2,rvas) + rfo(2,rfemur)
      ro(3,rvas) = ro(3,rvas) + rfo(3,rfemur)

      roe(1,rvas) = roe(1,rvas) + rfo(1,rfemur)
      roe(2,rvas) = roe(2,rvas) + rfo(2,rfemur)
      roe(3,rvas) = roe(3,rvas) + rfo(3,rfemur)

      ri(1,rvas) = ri(1,rvas) + rfo(1,rfemur)
      ri(2,rvas) = ri(2,rvas) + rfo(2,rfemur)
      ri(3,rvas) = ri(3,rvas) + rfo(3,rfemur)



c  RRF -----

      ro(1,rrf) = ro(1,rrf) + rfo(1,pelvis)
      ro(2,rrf) = ro(2,rrf) + rfo(2,pelvis)
      ro(3,rrf) = ro(3,rrf) + rfo(3,pelvis)

      roe(1,rrf) = roe(1,rrf) + rfo(1,rfemur)
      roe(2,rrf) = roe(2,rrf) + rfo(2,rfemur)
      roe(3,rrf) = roe(3,rrf) + rfo(3,rfemur)

      ri(1,rrf) = ri(1,rrf) + rfo(1,rfemur)
      ri(2,rrf) = ri(2,rrf) + rfo(2,rfemur)
      ri(3,rrf) = ri(3,rrf) + rfo(3,rfemur)



c  RHAMS -----

      ro(1,rhams) = ro(1,rhams) + rfo(1,pelvis)
      ro(2,rhams) = ro(2,rhams) + rfo(2,pelvis)
      ro(3,rhams) = ro(3,rhams) + rfo(3,pelvis)

      ri(1,rhams) = ri(1,rhams) + rfo(1,rtibia)
      ri(2,rhams) = ri(2,rhams) + rfo(2,rtibia)
      ri(3,rhams) = ri(3,rhams) + rfo(3,rtibia)

      roe(1,rhams) = roe(1,rhams) + rfo(1,rfemur)
      roe(2,rhams) = roe(2,rhams) + rfo(2,rfemur)
      roe(3,rhams) = roe(3,rhams) + rfo(3,rfemur)



c  RGRA -----

      ro(1,rgra) = ro(1,rgra) + rfo(1,pelvis)
      ro(2,rgra) = ro(2,rgra) + rfo(2,pelvis)
      ro(3,rgra) = ro(3,rgra) + rfo(3,pelvis)

      ri(1,rgra) = ri(1,rgra) + rfo(1,rtibia)
      ri(2,rgra) = ri(2,rgra) + rfo(2,rtibia)
      ri(3,rgra) = ri(3,rgra) + rfo(3,rtibia)



c  RTFL -----

      ro(1,rtfl) = ro(1,rtfl) + rfo(1,pelvis)
      ro(2,rtfl) = ro(2,rtfl) + rfo(2,pelvis)
      ro(3,rtfl) = ro(3,rtfl) + rfo(3,pelvis)

      ria(1,rtfl) = ria(1,rtfl) + rfo(1,rfemur)
      ria(2,rtfl) = ria(2,rtfl) + rfo(2,rfemur)
      ria(3,rtfl) = ria(3,rtfl) + rfo(3,rfemur)

      rob(1,rtfl) = rob(1,rtfl) + rfo(1,rfemur)
      rob(2,rtfl) = rob(2,rtfl) + rfo(2,rfemur)
      rob(3,rtfl) = rob(3,rtfl) + rfo(3,rfemur)

      ri(1,rtfl) = ri(1,rtfl) + rfo(1,rtibia)
      ri(2,rtfl) = ri(2,rtfl) + rfo(2,rtibia)
      ri(3,rtfl) = ri(3,rtfl) + rfo(3,rtibia)



c  RSAR -----

      ro(1,rsar) = ro(1,rsar) + rfo(1,pelvis)
      ro(2,rsar) = ro(2,rsar) + rfo(2,pelvis)
      ro(3,rsar) = ro(3,rsar) + rfo(3,pelvis)

      ria(1,rsar) = ria(1,rsar) + rfo(1,rfemur)
      ria(2,rsar) = ria(2,rsar) + rfo(2,rfemur)
      ria(3,rsar) = ria(3,rsar) + rfo(3,rfemur)

      rob(1,rsar) = rob(1,rsar) + rfo(1,rfemur)
      rob(2,rsar) = rob(2,rsar) + rfo(2,rfemur)
      rob(3,rsar) = rob(3,rsar) + rfo(3,rfemur)

      ri(1,rsar) = ri(1,rsar) + rfo(1,rtibia)
      ri(2,rsar) = ri(2,rsar) + rfo(2,rtibia)
      ri(3,rsar) = ri(3,rsar) + rfo(3,rtibia)



c  RGMAX_L -----

      ro(1,rgmax_l) = ro(1,rgmax_l) + rfo(1,pelvis)
      ro(2,rgmax_l) = ro(2,rgmax_l) + rfo(2,pelvis)
      ro(3,rgmax_l) = ro(3,rgmax_l) + rfo(3,pelvis)

      ri(1,rgmax_l) = ri(1,rgmax_l) + rfo(1,rfemur)
      ri(2,rgmax_l) = ri(2,rgmax_l) + rfo(2,rfemur)
      ri(3,rgmax_l) = ri(3,rgmax_l) + rfo(3,rfemur)

      roe(1,rgmax_l) = roe(1,rgmax_l) + rfo(1,pelvis)
      roe(2,rgmax_l) = roe(2,rgmax_l) + rfo(2,pelvis)
      roe(3,rgmax_l) = roe(3,rgmax_l) + rfo(3,pelvis)



c  RGMAX_M ----- 

      ro(1,rgmax_m) = ro(1,rgmax_m) + rfo(1,pelvis)
      ro(2,rgmax_m) = ro(2,rgmax_m) + rfo(2,pelvis)
      ro(3,rgmax_m) = ro(3,rgmax_m) + rfo(3,pelvis)

      ri(1,rgmax_m) = ri(1,rgmax_m) + rfo(1,rfemur)
      ri(2,rgmax_m) = ri(2,rgmax_m) + rfo(2,rfemur)
      ri(3,rgmax_m) = ri(3,rgmax_m) + rfo(3,rfemur)

      roe(1,rgmax_m) = roe(1,rgmax_m) + rfo(1,pelvis)
      roe(2,rgmax_m) = roe(2,rgmax_m) + rfo(2,pelvis)
      roe(3,rgmax_m) = roe(3,rgmax_m) + rfo(3,pelvis)



c  RGMEDA -----

      ro(1,rgmed_a) = ro(1,rgmed_a) + rfo(1,pelvis)
      ro(2,rgmed_a) = ro(2,rgmed_a) + rfo(2,pelvis)
      ro(3,rgmed_a) = ro(3,rgmed_a) + rfo(3,pelvis)

      ri(1,rgmed_a) = ri(1,rgmed_a) + rfo(1,rfemur)
      ri(2,rgmed_a) = ri(2,rgmed_a) + rfo(2,rfemur)
      ri(3,rgmed_a) = ri(3,rgmed_a) + rfo(3,rfemur)



c  RGMEDP -----

      ro(1,rgmed_p) = ro(1,rgmed_p) + rfo(1,pelvis)
      ro(2,rgmed_p) = ro(2,rgmed_p) + rfo(2,pelvis)
      ro(3,rgmed_p) = ro(3,rgmed_p) + rfo(3,pelvis)

      ri(1,rgmed_p) = ri(1,rgmed_p) + rfo(1,rfemur)
      ri(2,rgmed_p) = ri(2,rgmed_p) + rfo(2,rfemur)
      ri(3,rgmed_p) = ri(3,rgmed_p) + rfo(3,rfemur)



c  RADM -----

      ro(1,radm) = ro(1,radm) + rfo(1,pelvis)
      ro(2,radm) = ro(2,radm) + rfo(2,pelvis)
      ro(3,radm) = ro(3,radm) + rfo(3,pelvis)

      ri(1,radm) = ri(1,radm) + rfo(1,rfemur)
      ri(2,radm) = ri(2,radm) + rfo(2,rfemur)
      ri(3,radm) = ri(3,radm) + rfo(3,rfemur)



c  RADLB -----

      ro(1,radlb) = ro(1,radlb) + rfo(1,pelvis)
      ro(2,radlb) = ro(2,radlb) + rfo(2,pelvis)
      ro(3,radlb) = ro(3,radlb) + rfo(3,pelvis)

      ri(1,radlb) = ri(1,radlb) + rfo(1,rfemur)
      ri(2,radlb) = ri(2,radlb) + rfo(2,rfemur)
      ri(3,radlb) = ri(3,radlb) + rfo(3,rfemur)



c  RILPSO -----

      ro(1,rilpso) = ro(1,rilpso) + rfo(1,pelvis)
      ro(2,rilpso) = ro(2,rilpso) + rfo(2,pelvis)
      ro(3,rilpso) = ro(3,rilpso) + rfo(3,pelvis)

      ri(1,rilpso) = ri(1,rilpso) + rfo(1,rfemur)
      ri(2,rilpso) = ri(2,rilpso) + rfo(2,rfemur)
      ri(3,rilpso) = ri(3,rilpso) + rfo(3,rfemur)

      roe(1,rilpso) = roe(1,rilpso) + rfo(1,pelvis)
      roe(2,rilpso) = roe(2,rilpso) + rfo(2,pelvis)
      roe(3,rilpso) = roe(3,rilpso) + rfo(3,pelvis)



c  RPECT -----

      ro(1,rpect) = ro(1,rpect) + rfo(1,pelvis)
      ro(2,rpect) = ro(2,rpect) + rfo(2,pelvis)
      ro(3,rpect) = ro(3,rpect) + rfo(3,pelvis)

      ri(1,rpect) = ri(1,rpect) + rfo(1,rfemur)
      ri(2,rpect) = ri(2,rpect) + rfo(2,rfemur)
      ri(3,rpect) = ri(3,rpect) + rfo(3,rfemur)



c  RPIRI -----

      ro(1,rpiri) = ro(1,rpiri) + rfo(1,pelvis)
      ro(2,rpiri) = ro(2,rpiri) + rfo(2,pelvis)
      ro(3,rpiri) = ro(3,rpiri) + rfo(3,pelvis)

      ri(1,rpiri) = ri(1,rpiri) + rfo(1,rfemur)
      ri(2,rpiri) = ri(2,rpiri) + rfo(2,rfemur)
      ri(3,rpiri) = ri(3,rpiri) + rfo(3,rfemur)


c  RESPIN -----

      ro(1,respin) = ro(1,respin) + rfo(1,pelvis)
      ro(2,respin) = ro(2,respin) + rfo(2,pelvis)
      ro(3,respin) = ro(3,respin) + rfo(3,pelvis)

      ri(1,respin) = ri(1,respin) + rfo(1,hat)
      ri(2,respin) = ri(2,respin) + rfo(2,hat)
      ri(3,respin) = ri(3,respin) + rfo(3,hat)

c  RINOBL -----

      ro(1,rinobl) = ro(1,rinobl) + rfo(1,pelvis)
      ro(2,rinobl) = ro(2,rinobl) + rfo(2,pelvis)
      ro(3,rinobl) = ro(3,rinobl) + rfo(3,pelvis)

      ri(1,rinobl) = ri(1,rinobl) + rfo(1,hat)
      ri(2,rinobl) = ri(2,rinobl) + rfo(2,hat)
      ri(3,rinobl) = ri(3,rinobl) + rfo(3,hat)

c  REXOBL -----

      ro(1,rexobl) = ro(1,rexobl) + rfo(1,pelvis)
      ro(2,rexobl) = ro(2,rexobl) + rfo(2,pelvis)
      ro(3,rexobl) = ro(3,rexobl) + rfo(3,pelvis)

      ri(1,rexobl) = ri(1,rexobl) + rfo(1,hat)
      ri(2,rexobl) = ri(2,rexobl) + rfo(2,hat)
      ri(3,rexobl) = ri(3,rexobl) + rfo(3,hat)





c  LEFT SIDE OF THE BODY:
c   All the left-side parameters were initialized in skgspec() to be
c   the same as the right side.  This is fine except for the z components.
c   The left side is exactly the same as the right side except that the
c   z components are all the negatives of the right side components
c   (i.e., the body is reflected about the central sagital plane). 
c   ALSO, since ro,ri,roe,rob,ria for the right side all underwent
c   the above transformations, the left side must be updated also.
     
c  Incorporate above transformations into the left side parameters:
      do i = 1,nmushalf
        do j = 1,3 
         ro(j,nmushalf+i) = ro(j,i)
         ri(j,nmushalf+i) = ri(j,i)
         roe(j,nmushalf+i) = roe(j,i)
         rob(j,nmushalf+i) = rob(j,i)
         ria(j,nmushalf+i) = ria(j,i)
        enddo
      enddo

c  Now the left and right sides are exactly the same. We must reflect
c  about the central sagital axis (.i.e., z => -z).

c  Negate the z compononts:
      do i = 1,nmushalf
         ro(3,nmushalf+i) = -ro(3,i)
         ri(3,nmushalf+i) = -ri(3,i)
         roe(3,nmushalf+i) = -roe(3,i)
         rob(3,nmushalf+i) = -rob(3,i)
         ria(3,nmushalf+i) = -ria(3,i)
      enddo





      return
      end




c=======================================================================
c  Rotate a vector about the y axis:
c=======================================================================
      subroutine yrotate(u,ang,v)

      implicit none
      real*8 u(3),ang,v(3)

      v(1) = dcos(ang)*u(1) - dsin(ang)*u(3)
      v(2) = u(2)
      v(3) = dsin(ang)*u(1) + dcos(ang)*u(3)

      return
      end
