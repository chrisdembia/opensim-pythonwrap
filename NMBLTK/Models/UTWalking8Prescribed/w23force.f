      subroutine force23(t,y,q,u)



c  This subroutine calculates the actuator lengths and shortening velocities,

c   and applies the muscle and ligament forces for the SD/FAST routines.



c==============================================================================

c  Revision record:

c   11/19/93  7:20 pm

c==============================================================================

c

c  Input:

c      t = time

c      y = state vector

c      q = generalized coordinates

c      u = generalized velocities

c______________________________________________________________________________





      implicit none

c	INTERFACES FOR C ROUTINES

#ifndef UNIX
      interface to integer*4 function bgCrossVector
     & [C,ALIAS:'_bgCrossVector_'] (A,B,C)
	real*8 A(*) 
	real*8 B(*)
	real*8 C(*)
	end
#endif

      include 'w23params.h'

#ifndef UNIX
      interface to integer*4 function scylinder
     & [C,ALIAS:'_scylinder_'] (R,P,q,t,S,Pq,qt,tS,L,active)
	real*8 R [REFERENCE]
	real*8 P(3)
	real*8 q(3)
	real*8 t(3)
	real*8 S(3)
	real*8 Pq [REFERENCE]
	real*8 qt [REFERENCE]
	real*8 tS [REFERENCE]
	real*8 L  [REFERENCE]
	integer*4 active [REFERENCE]
	end

      interface to subroutine sdvel
     & [C,ALIAS:'_sdvel_'] (aBody,aPoint,rVel)
	integer*4 aBody [REFERENCE]
	real*8 aPoint(3)
	real*8 rVel(3)
	end

      interface to subroutine sdtrans
     & [C,ALIAS:'_sdtrans_'] (aBody1,aVec1,aBody2,rVec2)
	integer*4 aBody1 [REFERENCE]
	real*8 aVec1(3)
	integer*4 aBody2 [REFERENCE]
	real*8 rVec2(3)
	end

      interface to subroutine sdpointf
     & [C,ALIAS:'_sdpointf_'] (aBody,aPoint,aForce)
	integer*4 aBody [REFERENCE]
	real*8 aPoint(3)
	real*8 aForce(3)
	end

      interface to subroutine sdhinget
     & [C,ALIAS:'_sdhinget_'] (aJoint,aAxis,aTorque)
	integer*4 aJoint [REFERENCE]
	integer*4 aAxis [REFERENCE]
	real*8 aTorque [REFERENCE]
	end
#endif


      integer i,j

      integer status,active,scylinder

      real*8 Pcyl(3),qcyl(3),tcyl(3),Scyl(3),Pq,qt,tS,L

      real*8 frc(nmus),ractlen,actlena,actlenb,actsva,actsvb,temp,trq

      real*8 tvec(3),fvec(3),ovl(3),ivl(3),pqif(3)

      real*8 ovec(3),ovece(3),ivec(3),ivece(3),uvec(3),vvec(3)

      real*8 cma(6)

      real*8 rvasma,rvast,rrfma,rrft

      real*8 lvasma,lvast,lrfma,lrft

      real*8 rdist



      include 'w23comblk.h'



      data cma/ 4.3150d-2, 1.9901d-2, 4.8976d-2,

     &          3.5231d-2, 1.0575d-2, 1.1472d-3 /



c  Calculate the actual muscle forces:

      do i = 1,nmus

       frc(i) = y(imsf+i) * fom(i)

      enddo





c  Calculate the actuator lengths and shortening velocities, and apply the

c   muscle forces:











c=======================================================

c ===========  Right Side ==============================

c=======================================================





c   Hindfoot to Toe muscles ---------------------------------------------------





      do i = rfdh,redh

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(rhindfoot,ovec,rtoe,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(rhindfoot,ovec,ovl)

       call sdvel(rtoe,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,rtoe,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(rtoe,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rtoe,fvec,rhindfoot,fvec)

       call sdpointf(rhindfoot,ovec,fvec)

      enddo



c------------------------------------------------------------------------------





      





c   Tibia to Hindfoot muscles -------------------------------------------------



      do i = rdfin,rsol

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(rtibia,ovec,rhindfoot,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(rtibia,ovec,ovl)

       call sdvel(rhindfoot,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,rhindfoot,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(rhindfoot,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rhindfoot,fvec,rtibia,fvec)

       call sdpointf(rtibia,ovec,fvec)

      enddo



c------------------------------------------------------------------------------













c   Femur to Tibia to Foot muscles --------------------------------------------

c    Gastrocnemius



c  Femur to Tibia section -----

c   This section of Gastroc is modeled using a via cylinder.

c   The math for the via cylinders was developed by Brian Garner.

c   Transform the insertion into the femur frame

       call sdtransform(rtibia,ria(1,rgas),rfemur,ivec)

       ovec(1) = ro(1,rgas)

       ovec(2) = ro(2,rgas)

       ovec(3) = ro(3,rgas)

c   Transform the origin and insertion to the cylinder frame.

       do j = 1,3

         Scyl(j) = ivec(j) - cyl(j,rgas)

         Pcyl(j) = ovec(j) - cyl(j,rgas)

       enddo

c   Get the length of this portion of gastroc
cDEC$ ALIAS scylinder,"_scylinder_"	
       status = scylinder(cylR(rgas),Pcyl,qcyl,tcyl,Scyl,
     &                                       Pq,qt,tS,L,active) 

       actlena = vialen(rgas) + Pq + qt + tS 

c   If the viacylinder is active, set the new origin to t() and

c   transform from the cylinder frame back to the femur frame

c   Also, compute the new reciprocal of the distance between t and S

       if (active .eq. 1) then

         ovec(1) = tcyl(1) + cyl(1,rgas)

         ovec(2) = tcyl(2) + cyl(2,rgas)

         ovec(3) = tcyl(3) + cyl(3,rgas)

         rdist = 1.0d0 / tS

       else

         rdist = 1.0d0 / L

       endif 

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = (ivec(1) - ovec(1)) * rdist 

       uvec(2) = (ivec(2) - ovec(2)) * rdist

       uvec(3) = (ivec(3) - ovec(3)) * rdist

c  Get the shortening velocity of the actuator

       call sdvel(rfemur,ovec,ovl)

       call sdvel(rtibia,ria(1,rgas),ivl)

       vvec(1) = ivl(1) - ovl(1)

       vvec(2) = ivl(2) - ovl(2)

       vvec(3) = ivl(3) - ovl(3)

       call sdtrans(0,vvec,rfemur,vvec)

       actsva = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(rgas)

       fvec(2) = uvec(2) * frc(rgas)

       fvec(3) = uvec(3) * frc(rgas)

c   Apply the force at the origin point:

       call sdpointf(rfemur,ovec,fvec)

c   Rotate this force vector to the insertion frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rfemur,fvec,rtibia,fvec)

c  Apply the force at the insertion point:

       call sdpointf(rtibia,ria(1,rgas),fvec)



c  Tibia to Foot section -----

c   Define a vector from the insertion to the origin:

      ivec(1) = ri(1,rgas)

      ivec(2) = ri(2,rgas)

      ivec(3) = ri(3,rgas)

      ovec(1) = rob(1,rgas)

      ovec(2) = rob(2,rgas)

      ovec(3) = rob(3,rgas)

      call sdtransform(rtibia,ovec,rhindfoot,tvec)

      uvec(1) = tvec(1) - ivec(1)

      uvec(2) = tvec(2) - ivec(2)

      uvec(3) = tvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                  + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(rtibia,ovec,ovl)

       call sdvel(rhindfoot,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rhindfoot,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(rgas)

       fvec(2) = uvec(2) * frc(rgas)

       fvec(3) = uvec(3) * frc(rgas)

c   Apply the force at the insertion point:

       call sdpointf(rhindfoot,ivec,fvec)

c  Rotate this force vector to the rtibia frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rhindfoot,fvec,rtibia,fvec)

c  Apply the force at the origin point:

       call sdpointf(rtibia,ovec,fvec)



c  Calculate the total length and shortening velocity:

       actlen(rgas) = actlena + actlenb

       actsv(rgas) = actsva + actsvb



c -----------------------------------------------------------------------------













c   Femur to Tibia muscles ----------------------------------------------------

c    Biceps Femoris (short head)



c    Biceps Femoris has a sometimes via point.



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,rbfsh)

       ovec(2) = ro(2,rbfsh)

       ovec(3) = ro(3,rbfsh)

       ivec(1) = ri(1,rbfsh)

       ivec(2) = ri(2,rbfsh)

       ivec(3) = ri(3,rbfsh)

       call sdtransform(rfemur,ovec,rtibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(rbfsh) = actlena + vialen(rbfsh)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(rfemur,ovec,ovl)

       call sdvel(rtibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rtibia,vvec)

c   Calculate the actuator shortening velocity:

       actsv(rbfsh) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(rbfsh)

       fvec(2) = uvec(2) * frc(rbfsh)

       fvec(3) = uvec(3) * frc(rbfsh)

c   Apply the force at the insertion point:

       call sdpointf(rtibia,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rtibia,fvec,rfemur,fvec)

       call sdpointf(rfemur,ovec,fvec)

c -----------------------------------------------------------------------------













c Patella Muscles (Vasti & Rectus Femoris)  -----------------------------------



c   Because of the complexity of the knee, instead of applying forces to the

c   bones we have used torque angle curves from Spoor to estimate the 

c   moment arm for vasti and rectus femoris at the knee.  From this relation

c   it is also possible to get both the length and shortening velocities 

c   of these muscles.  The moment arm curves are fitted with a 5th degree

c   polynomial.  The data for this polynomial is held in the vector cma().

c   Note the the number 0.1829..d0 is a constant of integration needed

c   to get the proper actuator length for Vasti. Similarly for rectus 

c   femoris.





c   Vasti 



c   Curve fit for VAS from experimental data

c  (Spoor,C.W. 1992. Knee muscle moment arms from MRI.... J. Biomech.)

c   moment arm:

      rvasma = cma(1) - cma(2)*q(13) - cma(3)*q(13)**2

     & - cma(4)*q(13)**3 - cma(5)*q(13)**4 - cma(6)*q(13)**5

c   actuator length:

      actlen(rvas) = 0.179976d0 - cma(1)*q(13) + cma(2)*q(13)**2/2

     & + cma(3)*q(13)**3/3 + cma(4)*q(13)**4/4

     & + cma(5)*q(13)**5/5 + cma(6)*q(13)**6/6

c   actuator shortening velocity:

      actsv(rvas) =  - rvasma * u(13)

c   torque:

      rvast = rvasma * frc(rvas)

c   apply the torque at the knee:

      call sdhinget(joint(13),axis(13),rvast)



c   Rectus Femoris



c   Knee section ----



c   Curve fit for RF from experimental data

c  (Spoor,C.W. 1992. Knee muscle moment arms from MRI.... J. Biomech.)

c   moment arm:

      rrfma = cma(1) - cma(2)*q(13) - cma(3)*q(13)**2

     & - cma(4)*q(13)**3 - cma(5)*q(13)**4 - cma(6)*q(13)**5

c   actuator length:

      actlena = -0.01d0 - cma(1)*q(13) + cma(2)*q(13)**2/2

     & + cma(3)*q(13)**3/3 + cma(4)*q(13)**4/4

     & + cma(5)*q(13)**5/5 + cma(6)*q(13)**6/6

c   actuator shortening velocity:

      actsva =  - rrfma * u(13)

c   torque:

      rrft = rrfma * frc(rrf)

c   apply the torque at the knee:

      call sdhinget(joint(13),axis(13),rrft)



c   Hip section ----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame.

       ovec(1) = ro(1,rrf)

       ovec(2) = ro(2,rrf)

       ovec(3) = ro(3,rrf)

       call sdtransform(pelvis,ovec,rfemur,tvec)

       ivec(1) = roe(1,rrf)

       ivec(2) = roe(2,rrf)

       ivec(3) = roe(3,rrf)

       uvec(1) = tvec(1) - ivec(1)

       uvec(2) = tvec(2) - ivec(2)

       uvec(3) = tvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                    + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

c  Get the velocity of the origin and effective origin points:

       call sdvel(pelvis,ovec,ovl)

       call sdvel(rfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate the velocity vector to the rfemur frame:

       call sdtrans(ground,vvec,rfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(rrf)

       fvec(2) = uvec(2) * frc(rrf)

       fvec(3) = uvec(3) * frc(rrf)

c   Apply the force at the insertion point:

       call sdpointf(rfemur,ivec,fvec)

c  Rotate this force vector to the pelvis frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rfemur,fvec,pelvis,fvec)

c  Apply the force at the origin point:

       call sdpointf(pelvis,ovec,fvec)

c  Calculate the total length and shortening velocity:

       actlen(rrf) = actlena + actlenb

       actsv(rrf) = actsva + actsvb





c -----------------------------------------------------------------------------















c   Pelvis to Tibia muscles ---------------------------------------------------

c     Hamstrings (Biceps Femoris Long Head, Semimembranosus, Semitendinosus)

c     HAMS has a viacylinder implemented by the rouine scylinder.

c     This routine was developed by Brian Garner.

      do i = rhams,rhams

c   Transform the origin and insertion points to the viacylinder frame (rfemur).

       call sdtransform(pelvis,ro(1,i),rfemur,ovec)

       call sdtransform(rtibia,ri(1,i),rfemur,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,i)

         Scyl(j) = ivec(j) - cyl(j,i)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(i),Pcyl,qcyl,tcyl,Scyl,

     &  Pq,qt,tS,L,active) 

c   Set the actuator length

       actlen(i) = Pq + qt + tS + vialen(i) 



       if (active .eq. 1) then

c   The viacylinder is active...

         do j = 1,3

           ovece(j) = tcyl(j) + cyl(j,i)

           ivece(j) = qcyl(j) + cyl(j,i)

         enddo

c      --Femur to Tibia 

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovece(1)) * rdist 

         uvec(2) = (ivec(2)-ovece(2)) * rdist 

         uvec(3) = (ivec(3)-ovece(3)) * rdist 

c      Find the shortening velocity of this section         

         call sdvel(rfemur,ovece,ovl)

         call sdvel(rtibia,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,rfemur,vvec)

         actsva = vvec(1)*uvec(1) + vvec(2)*uvec(2) + 

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(rfemur,ovece,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(rfemur,fvec,rtibia,fvec)

         call sdpointf(rtibia,ri(1,i),fvec) 

c      --Pelvis to Femur 

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / Pq 

         uvec(1) = (ovec(1)-ivece(1)) * rdist 

         uvec(2) = (ovec(2)-ivece(2)) * rdist 

         uvec(3) = (ovec(3)-ivece(3)) * rdist 

c      Find the shortening velocity of this section         

         call sdvel(rfemur,ivece,ivl)

         call sdvel(pelvis,ro(1,i),ovl)

         vvec(1) = ovl(1) - ivl(1)

         vvec(2) = ovl(2) - ivl(2)

         vvec(3) = ovl(3) - ivl(3)

         call sdtrans(0,vvec,rfemur,vvec)

         actsvb = vvec(1)*uvec(1) + vvec(2)*uvec(2) + 

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(rfemur,ivece,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(rfemur,fvec,pelvis,fvec)

         call sdpointf(pelvis,ro(1,i),fvec) 

c      Set the total shortening velocity

         actsv(i) = actsva + actsvb



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,rhams),ovl)

         call sdvel(rtibia,ri(1,rhams),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,rfemur,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) + 

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdtrans(rfemur,fvec,pelvis,fvec)

         call sdpointf(pelvis,ro(1,i),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,rtibia,fvec)

         call sdpointf(rtibia,ri(1,i),fvec) 

       endif 

c -----------------------------------------------------------------------------







c   Pelvis to Tibia muscles ---------------------------------------------------

c    Gracilis



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,rgra)

       ovec(2) = ro(2,rgra)

       ovec(3) = ro(3,rgra)

       ivec(1) = ri(1,rgra)

       ivec(2) = ri(2,rgra)

       ivec(3) = ri(3,rgra)

       call sdtransform(pelvis,ovec,rtibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(rgra) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                    + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(rgra)

       actlen(rgra) = actlen(rgra) + vialen(rgra)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(rtibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the rtibia frame:

       call sdtrans(0,vvec,rtibia,vvec)

c   Calculate the actuator shortening velocity:

       actsv(rgra) = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(rgra)

       fvec(2) = uvec(2) * frc(rgra)

       fvec(3) = uvec(3) * frc(rgra)

c   Apply the force at the insertion point:

       call sdpointf(rtibia,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rtibia,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)



      enddo

c -----------------------------------------------------------------------------















c   Pelvis to Femur to Tibia muscles ------------------------------------------

c    Tensor Fasciae Latae, Sartorius



      do i = rtfl,rsar



c   Femur to Tibia section -----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = rob(1,i)

       ovec(2) = rob(2,i)

       ovec(3) = rob(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(rfemur,ovec,rtibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                   + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(rfemur,ovec,ovl)

       call sdvel(rtibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rtibia,vvec)

c   Calculate the actuator shortening velocity:

       actsva = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point.

       call sdpointf(rtibia,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rtibia,fvec,rfemur,fvec)

       call sdpointf(rfemur,ovec,fvec)



c  Pelvis to rfemur section -----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ria(1,i)

       ivec(2) = ria(2,i)

       ivec(3) = ria(3,i)

       call sdtransform(pelvis,ovec,rfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                   + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(rfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point.

       call sdpointf(rfemur,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)

c  Calculate the actual length and shortening velocity:

       actlen(i) = actlena + actlenb + vialen(i)

       actsv(i) = actsva + actsvb



      enddo



c -----------------------------------------------------------------------------











c   Pelvis to Femur muscles ---------------------------------------------------



c    Gluteus Maximus - Lateral, Gluteus Maximus - Medial ------------

c     The gluteal muscles pass over a viacylinder.

c     The routine scylinder was developed by Brian Garner.



      do i = rgmax_l,rgmax_m



c   Transform the insertion point to the viacylinder frame (pelvis).

       call sdtransform(pelvis,ro(1,i),pelvis,ovec)

       call sdtransform(rfemur,ri(1,i),pelvis,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,i)

         Scyl(j) = ivec(j) - cyl(j,i)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(i),Pcyl,qcyl,tcyl,Scyl,

     &                                         Pq,qt,tS,L,active)

c   Set the actuator length

       actlen(i) = Pq + qt + tS + vialen(i)



       if (active .eq. 1) then

c   The viacylinder is active...

         do j = 1,3

           ovec(j) = tcyl(j) + cyl(j,i)

         enddo

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(pelvis,ovec,ovl)

         call sdvel(rfemur,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(pelvis,ovec,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,rfemur,fvec)

         call sdpointf(rfemur,ri(1,i),fvec)



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,i),ovl)

         call sdvel(rfemur,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(pelvis,ro(1,i),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,rfemur,fvec)

         call sdpointf(rfemur,ri(1,i),fvec)

       endif



      enddo







c   Gluteus Medius/Minimus, Adductor Magnus, Adductors Longus/Brevis --------



      do i = rgmed_a,radlb



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       if(y(10) .gt. viaang(i))then

        ovec(1) = roe(1,i)

        ovec(2) = roe(2,i)

        ovec(3) = roe(3,i)

        actlen(i) = vialen(i) + viaadd(i)

       else

        ovec(1) = ro(1,i)

        ovec(2) = ro(2,i)

        ovec(3) = ro(3,i)

        actlen(i) = vialen(i)

       endif

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,rfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(i) = actlena + actlen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(rfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(rfemur,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)



      enddo







c    Iliopsoas -----------------------------

c     Iliopsoas passes over a viacylinder implemented by the routine scylinder.

c     The routine was developed by Brian Garner.

c   Transform the insertion point to the viacylinder frame (pelvis).

       call sdtransform(pelvis,ro(1,rilpso),pelvis,ovec)

       call sdtransform(rfemur,ri(1,rilpso),pelvis,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,rilpso)

         Scyl(j) = ivec(j) - cyl(j,rilpso)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(rilpso),Pcyl,qcyl,tcyl,Scyl,

     &                                         Pq,qt,tS,L,active)

c   Set the actuator length

       actlen(rilpso) = Pq + qt + tS + vialen(rilpso)



       if (active .eq. 1) then

c   The viacylinder is active...

c         print*,'RILPSO: via cylinder is active'

         do j = 1,3

           ovec(j) = tcyl(j) + cyl(j,rilpso)

         enddo

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(pelvis,ovec,ovl)

         call sdvel(rfemur,ri(1,rilpso),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(rilpso) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(rilpso)*uvec(1)

         fvec(2) = frc(rilpso)*uvec(2)

         fvec(3) = frc(rilpso)*uvec(3)

         call sdpointf(pelvis,ovec,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,rfemur,fvec)

         call sdpointf(rfemur,ri(1,rilpso),fvec)



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,rilpso),ovl)

         call sdvel(rfemur,ri(1,rilpso),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(rilpso) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(rilpso)*uvec(1)

         fvec(2) = frc(rilpso)*uvec(2)

         fvec(3) = frc(rilpso)*uvec(3)

         call sdpointf(pelvis,ro(1,rilpso),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,rfemur,fvec)

         call sdpointf(rfemur,ri(1,rilpso),fvec)

       endif

c       print*,'    l = ',actlen(rilpso),'   v = ',actsv(rilpso)  



c    Pectinius, Piriformis -----------------



      do i = rpect,rpiri



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       if(y(10) .gt. viaang(i))then

        ovec(1) = roe(1,i)

        ovec(2) = roe(2,i)

        ovec(3) = roe(3,i)

        actlen(i) = vialen(i) + viaadd(i)

       else

        ovec(1) = ro(1,i)

        ovec(2) = ro(2,i)

        ovec(3) = ro(3,i)

        actlen(i) = vialen(i)

       endif

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,rfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(i) = actlena + actlen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(rfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,rfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(rfemur,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(rfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)



      enddo





c -----------------------------------------------------------------------------













c   Pelvis to HAT muscles ---------------------------------------------------





      do i = respin,rexobl

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,hat,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(hat,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,hat,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(hat,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(hat,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)

      enddo



      















c===============================================================

c===================  Left side: ===============================

c===============================================================





c   Hindfoot to Toe muscles ---------------------------------------------------





      do i = lfdh,ledh

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(lhindfoot,ovec,ltoe,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(lhindfoot,ovec,ovl)

       call sdvel(ltoe,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,ltoe,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(ltoe,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(ltoe,fvec,lhindfoot,fvec)

       call sdpointf(lhindfoot,ovec,fvec)

      enddo



c------------------------------------------------------------------------------





      





c   Tibia to Hindfoot muscles -------------------------------------------------



      do i = ldfin,lsol

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(ltibia,ovec,lhindfoot,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(ltibia,ovec,ovl)

       call sdvel(lhindfoot,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,lhindfoot,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(lhindfoot,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lhindfoot,fvec,ltibia,fvec)

       call sdpointf(ltibia,ovec,fvec)

      enddo



c------------------------------------------------------------------------------













c   Femur to Tibia to Foot muscles --------------------------------------------

c    Gastrocnemius



c  Femur to Tibia section -----

c   This section of Gastroc is modeled using a via cylinder.

c   The math for the via cylinders was developed by Brian Garner.

c   Transform the insertion into the femur frame

       call sdtransform(ltibia,ria(1,lgas),lfemur,ivec)

       ovec(1) = ro(1,lgas)

       ovec(2) = ro(2,lgas)

       ovec(3) = ro(3,lgas)

c   Transform the origin and insertion to the cylinder frame.

       do j = 1,3

         Scyl(j) = ivec(j) - cyl(j,lgas)

         Pcyl(j) = ovec(j) - cyl(j,lgas)

       enddo

c   Get the length of this portion of gastroc

       status = scylinder(cylR(lgas),Pcyl,qcyl,tcyl,Scyl,

     &                                          Pq,qt,tS,L,active)

       actlena = vialen(lgas) + Pq + qt + tS

c   If the viacylinder is active, set the new origin to t() and

c   transform from the cylinder frame back to the femur frame

c   Also, compute the new reciprocal of the distance between t and S

       if (active .eq. 1) then

         ovec(1) = tcyl(1) + cyl(1,lgas)

         ovec(2) = tcyl(2) + cyl(2,lgas)

         ovec(3) = tcyl(3) + cyl(3,lgas)

         rdist = 1.0d0 / tS

       else

         rdist = 1.0d0 / L

       endif

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = (ivec(1) - ovec(1)) * rdist

       uvec(2) = (ivec(2) - ovec(2)) * rdist

       uvec(3) = (ivec(3) - ovec(3)) * rdist

c  Get the shortening velocity of the actuator

       call sdvel(lfemur,ovec,ovl)

       call sdvel(ltibia,ria(1,lgas),ivl)

       vvec(1) = ivl(1) - ovl(1)

       vvec(2) = ivl(2) - ovl(2)

       vvec(3) = ivl(3) - ovl(3)

       call sdtrans(0,vvec,lfemur,vvec)

       actsva = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(lgas)

       fvec(2) = uvec(2) * frc(lgas)

       fvec(3) = uvec(3) * frc(lgas)

c   Apply the force at the origin point:

       call sdpointf(lfemur,ovec,fvec)

c   Rotate this force vector to the insertion frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lfemur,fvec,ltibia,fvec)

c  Apply the force at the insertion point:

       call sdpointf(ltibia,ria(1,lgas),fvec)



c  Tibia to Foot section -----

c   Define a vector from the insertion to the origin:

      ivec(1) = ri(1,lgas)

      ivec(2) = ri(2,lgas)

      ivec(3) = ri(3,lgas)

      ovec(1) = rob(1,lgas)

      ovec(2) = rob(2,lgas)

      ovec(3) = rob(3,lgas)

      call sdtransform(ltibia,ovec,lhindfoot,tvec)

      uvec(1) = tvec(1) - ivec(1)

      uvec(2) = tvec(2) - ivec(2)

      uvec(3) = tvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                  + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(ltibia,ovec,ovl)

       call sdvel(lhindfoot,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,lhindfoot,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(lgas)

       fvec(2) = uvec(2) * frc(lgas)

       fvec(3) = uvec(3) * frc(lgas)

c   Apply the force at the insertion point:

       call sdpointf(lhindfoot,ivec,fvec)

c  Rotate this force vector to the ltibia frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lhindfoot,fvec,ltibia,fvec)

c  Apply the force at the origin point:

       call sdpointf(ltibia,ovec,fvec)



c  Calculate the total length and shortening velocity:

       actlen(lgas) = actlena + actlenb

       actsv(lgas) = actsva + actsvb



c -----------------------------------------------------------------------------









c   Femur to Tibia muscles ----------------------------------------------------

c    Biceps Femoris (short head)



c    Biceps Femoris has a sometimes via point.



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,lbfsh)

       ovec(2) = ro(2,lbfsh)

       ovec(3) = ro(3,lbfsh)

       ivec(1) = ri(1,lbfsh)

       ivec(2) = ri(2,lbfsh)

       ivec(3) = ri(3,lbfsh)

       call sdtransform(lfemur,ovec,ltibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(lbfsh) = actlena + vialen(lbfsh)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(lfemur,ovec,ovl)

       call sdvel(ltibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,ltibia,vvec)

c   Calculate the actuator shortening velocity:

       actsv(lbfsh) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(lbfsh)

       fvec(2) = uvec(2) * frc(lbfsh)

       fvec(3) = uvec(3) * frc(lbfsh)

c   Apply the force at the insertion point:

       call sdpointf(ltibia,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(ltibia,fvec,lfemur,fvec)

       call sdpointf(lfemur,ovec,fvec)







c Patella Muscles (Vasti & Rectus Femoris)  -----------------------------------



c   Because of the complexity of the knee, instead of applying forces to the

c   bones we have used torque angle curves from Spoor to estimate the 

c   moment arm for vasti and rectus femoris at the knee.  From this relation

c   it is also possible to get both the length and shortening velocities 

c   of these muscles.  The moment arm curves are fitted with a 5th degree

c   polynomial.  The data for this polynomial is held in the vector cma().

c   Note the the number 0.1829..d0 is a constant of integration needed

c   to get the proper actuator length for Vasti. Similarly for rectus 

c   femoris.





c   Vasti 



c   Curve fit for VAS from experimental data

c  (Spoor,C.W. 1992. Knee muscle moment arms from MRI.... J. Biomech.25:201-206)

c   moment arm:

      lvasma = cma(1) - cma(2)*q(20) - cma(3)*q(20)**2

     & - cma(4)*q(20)**3 - cma(5)*q(20)**4 - cma(6)*q(20)**5

c   actuator length:

      actlen(lvas) = 0.179976d0 - cma(1)*q(20) + cma(2)*q(20)**2/2

     & + cma(3)*q(20)**3/3 + cma(4)*q(20)**4/4

     & + cma(5)*q(20)**5/5 + cma(6)*q(20)**6/6

c   actuator shortening velocity:

      actsv(lvas) =  - lvasma * u(20)

c   torque:

      lvast = lvasma * frc(lvas)

c   apply the torque at the knee:

      call sdhinget(joint(20),axis(20),lvast)







c   Rectus Femoris



c   Knee section ----



c   Curve fit for RF from experimental data

c  (Spoor,C.W. 1992. Knee muscle moment arms from MRI.... J. Biomech.)

c   moment arm:

      lrfma = cma(1) - cma(2)*q(20) - cma(3)*q(20)**2

     & - cma(4)*q(20)**3 - cma(5)*q(20)**4 - cma(6)*q(20)**5

c   actuator length:

      actlena = -0.01d0 - cma(1)*q(20) + cma(2)*q(20)**2/2

     & + cma(3)*q(20)**3/3 + cma(4)*q(20)**4/4

     & + cma(5)*q(20)**5/5 + cma(6)*q(20)**6/6

c   actuator shortening velocity:

      actsva =  - lrfma * u(20)

c   torque:

      lrft = lrfma * frc(lrf)

c   apply the torque at the knee:

      call sdhinget(joint(20),axis(20),lrft)



c   Hip section ----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame.

       ovec(1) = ro(1,lrf)

       ovec(2) = ro(2,lrf)

       ovec(3) = ro(3,lrf)

       call sdtransform(pelvis,ovec,lfemur,tvec)

       ivec(1) = roe(1,lrf)

       ivec(2) = roe(2,lrf)

       ivec(3) = roe(3,lrf)

       uvec(1) = tvec(1) - ivec(1)

       uvec(2) = tvec(2) - ivec(2)

       uvec(3) = tvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                    + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

c  Get the velocity of the origin and effective origin points:

       call sdvel(pelvis,ovec,ovl)

       call sdvel(lfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate the velocity vector to the lfemur frame:

       call sdtrans(ground,vvec,lfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(lrf)

       fvec(2) = uvec(2) * frc(lrf)

       fvec(3) = uvec(3) * frc(lrf)

c   Apply the force at the insertion point:

       call sdpointf(lfemur,ivec,fvec)

c  Rotate this force vector to the pelvis frame:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lfemur,fvec,pelvis,fvec)

c  Apply the force at the origin point:

       call sdpointf(pelvis,ovec,fvec)

c  Calculate the total length and shortening velocity:

       actlen(lrf) = actlena + actlenb

       actsv(lrf) = actsva + actsvb





c -----------------------------------------------------------------------------















c   Pelvis to Tibia muscles ---------------------------------------------------

c     Hamstrings (Biceps Femoris Long Head, Semimembranosus, Semitendinosus)

c     HAMS has a viacylinder implemented by the rouine scylinder.

c     This routine was developed by Brian Garner.

      do i = lhams,lhams

c   Transform origin and insertion points to the viacylinder frame (lfemur). 

       call sdtransform(pelvis,ro(1,i),lfemur,ovec)

       call sdtransform(ltibia,ri(1,i),lfemur,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,i)

         Scyl(j) = ivec(j) - cyl(j,i)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(i),Pcyl,qcyl,tcyl,Scyl,

     &  Pq,qt,tS,L,active)   

c   Set the actuator length

       actlen(i) = Pq + qt + tS + vialen(i)



       if (active .eq. 1) then

c   The viacylinder is active...

         do j = 1,3

           ovece(j) = tcyl(j) + cyl(j,i)

           ivece(j) = qcyl(j) + cyl(j,i)

         enddo

c      --Femur to Tibia

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovece(1)) * rdist

         uvec(2) = (ivec(2)-ovece(2)) * rdist

         uvec(3) = (ivec(3)-ovece(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(lfemur,ovece,ovl)

         call sdvel(ltibia,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,lfemur,vvec)

         actsva = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(lfemur,ovece,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(lfemur,fvec,ltibia,fvec)

         call sdpointf(ltibia,ri(1,i),fvec)

c      --Pelvis to Femur

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / Pq

         uvec(1) = (ovec(1)-ivece(1)) * rdist

         uvec(2) = (ovec(2)-ivece(2)) * rdist

         uvec(3) = (ovec(3)-ivece(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(lfemur,ivece,ivl)

         call sdvel(pelvis,ro(1,i),ovl)

         vvec(1) = ovl(1) - ivl(1)

         vvec(2) = ovl(2) - ivl(2)

         vvec(3) = ovl(3) - ivl(3)

         call sdtrans(0,vvec,lfemur,vvec)

         actsvb = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(lfemur,ivece,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(lfemur,fvec,pelvis,fvec)

         call sdpointf(pelvis,ro(1,i),fvec)

c      Set the total shortening velocity

         actsv(i) = actsva + actsvb



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,i),ovl)

         call sdvel(ltibia,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,lfemur,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdtrans(lfemur,fvec,pelvis,fvec)

         call sdpointf(pelvis,ro(1,i),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,ltibia,fvec)

         call sdpointf(ltibia,ri(1,i),fvec)

       endif

      enddo

c -----------------------------------------------------------------------------













c   Pelvis to Tibia muscles ---------------------------------------------------

c    Gracilis



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,lgra)

       ovec(2) = ro(2,lgra)

       ovec(3) = ro(3,lgra)

       ivec(1) = ri(1,lgra)

       ivec(2) = ri(2,lgra)

       ivec(3) = ri(3,lgra)

       call sdtransform(pelvis,ovec,ltibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(lgra) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                    + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(lgra)

       actlen(lgra) = actlen(lgra) + vialen(lgra)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(ltibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the ltibia frame:

       call sdtrans(0,vvec,ltibia,vvec)

c   Calculate the actuator shortening velocity:

       actsv(lgra) = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(lgra)

       fvec(2) = uvec(2) * frc(lgra)

       fvec(3) = uvec(3) * frc(lgra)

c   Apply the force at the insertion point:

       call sdpointf(ltibia,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(ltibia,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)

c -----------------------------------------------------------------------------















c   Pelvis to Femur to Tibia muscles ------------------------------------------

c    Tensor Fasciae Latae, Sartorius



      do i = ltfl,lsar



c   Femur to Tibia section -----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = rob(1,i)

       ovec(2) = rob(2,i)

       ovec(3) = rob(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(lfemur,ovec,ltibia,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                   + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(lfemur,ovec,ovl)

       call sdvel(ltibia,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,ltibia,vvec)

c   Calculate the actuator shortening velocity:

       actsva = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point.

       call sdpointf(ltibia,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(ltibia,fvec,lfemur,fvec)

       call sdpointf(lfemur,ovec,fvec)



c  Pelvis to lfemur section -----



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ria(1,i)

       ivec(2) = ria(2,i)

       ivec(3) = ria(3,i)

       call sdtransform(pelvis,ovec,lfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlenb = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                   + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlenb

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(lfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,lfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsvb = uvec(1)*vvec(1) + uvec(2)*vvec(2) + uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point.

       call sdpointf(lfemur,ivec,fvec)

c  Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)

c  Calculate the actual length and shortening velocity:

       actlen(i) = actlena + actlenb + vialen(i)

       actsv(i) = actsva + actsvb



      enddo



c -----------------------------------------------------------------------------













c   Pelvis to Femur muscles ---------------------------------------------------



c    Gluteus Maximus - Lateral, Gluteus Maximus - Medial ------------

c     The gluteal muscles pass over a viacylinder.

c     The routine scylinder was developed by Brian Garner.



      do i = lgmax_l,lgmax_m



c   Transform the insertion point to the viacylinder frame (pelvis).

       call sdtransform(pelvis,ro(1,i),pelvis,ovec)

       call sdtransform(lfemur,ri(1,i),pelvis,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,i)

         Scyl(j) = ivec(j) - cyl(j,i)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(i),Pcyl,qcyl,tcyl,Scyl,

     &                                         Pq,qt,tS,L,active)

c   Set the actuator length

       actlen(i) = Pq + qt + tS + vialen(i)



       if (active .eq. 1) then

c   The viacylinder is active...

         do j = 1,3

           ovec(j) = tcyl(j) + cyl(j,i)

         enddo

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(pelvis,ovec,ovl)

         call sdvel(lfemur,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(pelvis,ovec,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,lfemur,fvec)

         call sdpointf(lfemur,ri(1,i),fvec)



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,i),ovl)

         call sdvel(lfemur,ri(1,i),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(i) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(i)*uvec(1)

         fvec(2) = frc(i)*uvec(2)

         fvec(3) = frc(i)*uvec(3)

         call sdpointf(pelvis,ro(1,i),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,lfemur,fvec)

         call sdpointf(lfemur,ri(1,i),fvec)

       endif



      enddo







c    Gluteus Medius/Minimus, Adductor Magnus, Adductors Longus/Brevis ---------



      do i = lgmed_a,ladlb



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       if(y(17) .gt. viaang(i))then

        ovec(1) = roe(1,i)

        ovec(2) = roe(2,i)

        ovec(3) = roe(3,i)

        actlen(i) = vialen(i) + viaadd(i)

       else

        ovec(1) = ro(1,i)

        ovec(2) = ro(2,i)

        ovec(3) = ro(3,i)

        actlen(i) = vialen(i)

       endif

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,lfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(i) = actlena + actlen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(lfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,lfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(lfemur,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)



      enddo







c    Iliopsoas -----------------------------

c     Iliopsoas passes over a viacylinder implemented by the routine scylinder.

c     The routine was developed by Brian Garner.

c   Transform the insertion point to the viacylinder frame (pelvis).

       call sdtransform(pelvis,ro(1,lilpso),pelvis,ovec)

       call sdtransform(lfemur,ri(1,lilpso),pelvis,ivec)

c   Get the origin and insertion in the cylinder frame.

       do j = 1,3

         Pcyl(j) = ovec(j) - cyl(j,lilpso)

         Scyl(j) = ivec(j) - cyl(j,lilpso)

       enddo

c   Implement the viacylinder

       status = scylinder(cylR(lilpso),Pcyl,qcyl,tcyl,Scyl,

     &                                         Pq,qt,tS,L,active)

c   Set the actuator length

       actlen(lilpso) = Pq + qt + tS + vialen(lilpso)

       if (active .eq. 1) then

c   The viacylinder is active...

         do j = 1,3

           ovec(j) = tcyl(j) + cyl(j,lilpso)

         enddo

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / tS

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity of this section

         call sdvel(pelvis,ovec,ovl)

         call sdvel(lfemur,ri(1,lilpso),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(lilpso) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(lilpso)*uvec(1)

         fvec(2) = frc(lilpso)*uvec(2)

         fvec(3) = frc(lilpso)*uvec(3)

         call sdpointf(pelvis,ovec,fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,lfemur,fvec)

         call sdpointf(lfemur,ri(1,lilpso),fvec)



       else

c   The viacylinder is not active...

c      Find the unit vector in the direction of the force

         rdist = 1.0d0 / L

         uvec(1) = (ivec(1)-ovec(1)) * rdist

         uvec(2) = (ivec(2)-ovec(2)) * rdist

         uvec(3) = (ivec(3)-ovec(3)) * rdist

c      Find the shortening velocity

         call sdvel(pelvis,ro(1,lilpso),ovl)

         call sdvel(lfemur,ri(1,lilpso),ivl)

         vvec(1) = ivl(1) - ovl(1)

         vvec(2) = ivl(2) - ovl(2)

         vvec(3) = ivl(3) - ovl(3)

         call sdtrans(0,vvec,pelvis,vvec)

         actsv(lilpso) = vvec(1)*uvec(1) + vvec(2)*uvec(2) +

     &              vvec(3)*uvec(3)

c      Apply the force

         fvec(1) = frc(lilpso)*uvec(1)

         fvec(2) = frc(lilpso)*uvec(2)

         fvec(3) = frc(lilpso)*uvec(3)

         call sdpointf(pelvis,ro(1,lilpso),fvec)

         fvec(1) = -fvec(1)

         fvec(2) = -fvec(2)

         fvec(3) = -fvec(3)

         call sdtrans(pelvis,fvec,lfemur,fvec)

         call sdpointf(lfemur,ri(1,lilpso),fvec)

       endif





c    Pectinius, Piriformis -----------------

      do i = lpect,lpiri



c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       if(y(17) .gt. viaang(i))then

        ovec(1) = roe(1,i)

        ovec(2) = roe(2,i)

        ovec(3) = roe(3,i)

        actlen(i) = vialen(i) + viaadd(i)

       else

        ovec(1) = ro(1,i)

        ovec(2) = ro(2,i)

        ovec(3) = ro(3,i)

        actlen(i) = vialen(i)

       endif

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,lfemur,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlena = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlena

       actlen(i) = actlena + actlen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(lfemur,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(0,vvec,lfemur,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(lfemur,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(lfemur,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)



      enddo





c -----------------------------------------------------------------------------













c   Pelvis to HAT muscles ---------------------------------------------------





      do i = lespin,lexobl

c   Calculate the components of a vector directed from the insertion point to

c    the origin point defined in the insertion segment frame:

       ovec(1) = ro(1,i)

       ovec(2) = ro(2,i)

       ovec(3) = ro(3,i)

       ivec(1) = ri(1,i)

       ivec(2) = ri(2,i)

       ivec(3) = ri(3,i)

       call sdtransform(pelvis,ovec,hat,uvec)

       uvec(1) = uvec(1) - ivec(1)

       uvec(2) = uvec(2) - ivec(2)

       uvec(3) = uvec(3) - ivec(3)

c   Calculate the actuator length:

       actlen(i) = dsqrt( uvec(1)*uvec(1) + uvec(2)*uvec(2)

     &                       + uvec(3)*uvec(3) )

       ractlen = 1.d0 / actlen(i)

       actlen(i) = actlen(i) + vialen(i)

c  Determine the components of a unit vector directed along the actuator:

       uvec(1) = uvec(1) * ractlen

       uvec(2) = uvec(2) * ractlen

       uvec(3) = uvec(3) * ractlen

       call sdvel(pelvis,ovec,ovl)

       call sdvel(hat,ivec,ivl)

       vvec(1) = ovl(1) - ivl(1)

       vvec(2) = ovl(2) - ivl(2)

       vvec(3) = ovl(3) - ivl(3)

c  Rotate this vector to the insertion frame:

       call sdtrans(ground,vvec,hat,vvec)

c   Calculate the actuator shortening velocity:

       actsv(i) = uvec(1)*vvec(1)+uvec(2)*vvec(2)+uvec(3)*vvec(3)

c   Calculate the vector of muscle force:

       fvec(1) = uvec(1) * frc(i)

       fvec(2) = uvec(2) * frc(i)

       fvec(3) = uvec(3) * frc(i)

c   Apply the force at the insertion point:

       call sdpointf(hat,ivec,fvec)

c   Apply the opposite force at the origin point:

       fvec(1) = -fvec(1)

       fvec(2) = -fvec(2)

       fvec(3) = -fvec(3)

       call sdtrans(hat,fvec,pelvis,fvec)

       call sdpointf(pelvis,ovec,fvec)

      enddo





c=============================================================================













      return

      end

