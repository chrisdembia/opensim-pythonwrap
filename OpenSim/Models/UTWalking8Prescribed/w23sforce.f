c============================================================
c CALCULATE EXTERNAL FORCES AND EXERT THEM ON BODIES
c============================================================
      subroutine sforce23(t,q,u,sforce,spt,tqlig)

      implicit none

      include 'w23params.h'

#ifndef UNIX
	interface to subroutine sdst2ang
     & [C,ALIAS:'_sdst2ang_'] (aQ,rQAng)
	real*8 aQ(*)
	real*8 rQAng(*)
	end
 
      interface to subroutine sdpos
     & [C,ALIAS:'_sdpos_'] (aBody,aPoint,rPos)
	integer*4 aBody [REFERENCE]
	real*8 aPoint(3)
	real*8 rPos(3)
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

      integer i,xyz,response,draw23


c Ground Force Variables:
      real*8 sforce(3,ns),spt(3,ns),sptv(3,ns)
      real*8 bodysforce(3,ns)
      real*8 x1,x2,gradual
      real*8 flimit

      include 'w23comblk.h'


c==== DATA STATEMENTS: ====
c==== (see 23comblk.h for variable declarations) ====
c     Joint Damping:
c      data jdamp /1.0d-3/ 

c     Ligament torques:
c      data k0lig /0.1390577d0,0.0d0,0.0d0,
c     &            0.0d0,0.0d0,0.0d0,0.0d0,
c     &            0.49257884d0,0.0d0,-0.05d0,
c     &            0.0d0,0.0d0,0.0d0,0.0d0,
c     &            0.49257884d0,0.0d0,-0.05d0/
c      data k1lig1 /-0.35d0,-0.25d0,-0.25d0,
c     &             -2.44d0,-0.03d0, -0.03d0,-6.09d0,
c     &             -4.0d0,-60.21d0,-0.9d0,
c     &             -2.44d0,-0.03d0, -0.03d0,-6.09d0,
c     &             -4.0d0,-60.21d0,-0.9d0/  
c      data k2lig1 /30.72d0,20.36d0,20.36d0,
c     &             5.05d0,14.94d0,14.94d0,33.94d0,
c     &             8.0d0,16.32d0,14.87d0,
c     &             5.05d0,14.94d0,14.94d0,33.94d0,
c     &             8.0d0,16.32d0,14.87d0/
c      data theta1 /0.03d0,0.17d0,0.17d0,
c     &             1.81d0,0.50d0,0.92d0,0.13d0,
c     &             0.2618d0,0.65d0,0.21d0,
c     &             1.81d0,0.50d0,0.92d0,0.13d0,
c     &             0.2618d0,0.65d0,0.21d0/
c      data k1lig2 /0.25d0,0.25d0,0.25d0,
c     &             1.51d0,0.03d0, 0.03d0,11.03d0,
c     &             1.0d0,60.21d0,0.18d0,
c     &             1.51d0,0.03d0, 0.03d0,11.03d0,
c     &             1.0d0,60.21d0,0.18d0/
c      data k2lig2 /-20.36,-20.36,-20.36,
c     &             -21.88d0,-14.94d0,-14.94d0,-11.33d0,
c     &             -22.0d0,-16.32d0,-70.08d0, 
c     &             -21.88d0,-14.94d0,-14.94d0,-11.33d0,
c     &             -22.0d0,-16.32d0,-70.08d0/
c      data theta2 /-0.35d0,-0.17d0,-0.17d0,
c     &             -0.47d0,-0.50d0,-0.92d0,-2.40d0,
c     &             -0.4712d0,-0.65d0,-0.02d0,
c     &             -0.47d0,-0.50d0,-0.92d0,-2.40d0,
c     &             -0.4712d0,-0.65d0,-0.02d0/

c     Ground springs:
c      data y0,b0,b1,c0,c1 /6.5905d-3,0.5336322,0.0d0,0.0d0,-1150.8002d0/    
c      data s0,s1,s2 /0.02d0,10.0d0,500.0d0/
c      data sk,mu,sdamp /6.9d4,0.7d0,1.0d3/
c      data bodyspt / -0.071650,-0.038653,-0.050428,
c     &               -0.091740,-0.038653,0.023202,
c     &                0.123629,-0.038653,-0.029196,
c     &                0.070755,-0.038653,0.069117,
c     &                0.050769,-0.018500,0.003468,
c     &               -0.071650,-0.038653,0.050428,
c     &               -0.091740,-0.038653,-0.023202,
c     &                0.123629,-0.038653,0.029196,
c     &                0.070755,-0.038653,-0.069117,
c     &                0.050769,-0.018500,-0.003468/



c==== Convert the euler parameters to euler angles:
      call sdst2ang(q,yang)
c	do i = 1,23
c	   print*,'yang',i,yang(i)
c	enddo

c==== DAMPING AT THE JOINTS: ====
      do i = 1,dof-6
        tqdamp(i) = -jdamp * u(6+i)
c	print*,'tqdamp=',i,tqdamp(i)
        call sdhinget(joint(6+i),axis(6+i),tqdamp(i))
      enddo


c==== LIGAMENTS AT THE JOINTS: ====
      do i = 1,dof-6
        xlig1(i) = yang(6+i) - theta1(i)
        xlig2(i) = yang(6+i) - theta2(i)
        tqlig(i) = k0lig(i)+k1lig1(i)*dexp(k2lig1(i)*xlig1(i)) +
     &             k1lig2(i)*dexp(k2lig2(i)*xlig2(i))
        call sdhinget(joint(6+i),axis(6+i),tqlig(i))
      enddo


c==== SPRING FORCES OF THE GROUND: ====
      do i = 1,ns
c      Get inertial position and velociy of point:
c	print*,'bodyspt=',i,bodyspt(1,i),bodyspt(2,i),bodyspt(3,i)
        call sdpos(sbody(i),bodyspt(1,i),spt(1,i))
        call sdvel(sbody(i),bodyspt(1,i),sptv(1,i))
c	print*,'spt=',i,spt(1,i),spt(2,i),spt(3,i)
c	print*,'sptv=',i,sptv(1,i),sptv(2,i),sptv(3,i)
c      Spring force in the vertical direction: 
        x1 = spt(2,i) - y0 
        x2 = spt(2,i) - s0
        sforce(1,i) = 0.0d0
        sforce(3,i) = 0.0d0
        gradual = 1 / (1+s1*dexp(s2*x2))
        sforce(2,i) = (b0+b1*x1)*dexp(c0+c1*x1)
c        if (i .eq. 1) then
c          print*,'nodamp= ',sforce(2,i)
c        endif
c     Damp only if the point velocity is downward:
        if (sptv(2,i) .lt. 0.0d0) then
          sforce(2,i) = sforce(2,i)  - sdamp*sptv(2,i)*gradual
        endif
c        if (i .eq. 1) then
c          print*,'  damp= ',sforce(2,i)
c        endif
        if (sforce(2,i) .lt. 1.0d-10) sforce(2,i)=1.0d-10 
c      Spring force in the horizontal directions:
c      X FORCE:
        sforce(1,i) = -sk*(spt(1,i)-sx0(i))-sdamp*sptv(1,i)
        flimit = dsign(mu*sforce(2,i),sforce(1,i))
        if (dabs(sforce(1,i)).gt.dabs(flimit)) then
          sforce(1,i) = flimit
        endif
c      Z FORCE:
        sforce(3,i) = -sk*(spt(3,i)-sz0(i))-sdamp*sptv(3,i)
        flimit = dsign(mu*sforce(2,i),sforce(3,i))
        if (dabs(sforce(3,i)).gt.dabs(flimit)) then
          sforce(3,i) = flimit
        endif
c      Get the force in the body frame: 
        call sdtrans(ground,sforce(1,i),sbody(i),bodysforce(1,i))
c      Apply the force: 
        call sdpointf(sbody(i),bodyspt(1,i),bodysforce(1,i))

c	print*,'sforce=',i,sforce(1,i),sforce(2,i),sforce(3,i)

      enddo

      return
      end

