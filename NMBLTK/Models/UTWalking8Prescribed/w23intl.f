      subroutine intl23(x,ynode,
     &                       maxitr,drvtype,dx,sclflg,inf,sxo,szo)


c  This subroutine loads the controls and initial conditions. It also sets

c   various initial values.



c==============================================================================

c  Revision record:

c   11/30/93  8:10 am

c==============================================================================

c

c  Input: none

c

c  Output:

c         x = controls

c     ynode = initial state vector

c    maxitr = maximum number of iterations allowed

c   drvtype = type of derivatives to be calculated

c        dx = perturbation size for the derivatives

c    sclflg = a flag indicating whether scaling is to be used or not

c______________________________________________________________________________
c      use ifport
      implicit none

      include 'w23params.h'


#ifndef UNIX
  	interface to subroutine sdinit
     & [C,ALIAS:'_sdinit_'] ()
	end

  	interface to subroutine sdgrav
     & [C,ALIAS:'_sdgrav_'] (aGrav)
	real*8 aGrav(3)
	end

  	interface to subroutine sdgetmass
     & [C,ALIAS:'_sdgetmass_'] (aBody,rMass)
	integer*4 aBody [REFERENCE]
	real*8 rMass [REFERENCE]
	end

	interface to subroutine sdstate
     & [C,ALIAS:'_sdstate_'] (aT,aQ,aU)
	real*8 aT [REFERENCE]
	real*8 aQ(*)
	real*8 aU(*)
	end

	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
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
#endif



      integer i,j,k

      integer maxitr,drvtype,sclflg,inf

      integer mpt(nmus)

      real*8 dxi,df,stabvel,stabpos
      real*8 spt(3,ns),sxo(ns),szo(ns)
      real*8 com(3),footVel(3),footAngVel(3)

      integer clen,len_trim
      character*50 musset,skgset
      character*256 initdir,filename

      double precision testmas

      logical ex

      include 'w23comblk.h'

      real*8 musfrc

      data musset/'./lower.mus.23'/
      data skgset/'./lower.skg.23'/



c     BELOW FROM BLOCK DATA MODDAT


c     ABOVE FROM BLOCK DATA MODDAT






      data mpt/
     & 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,
     & 21,22,23,24,25,26,27,
     & 28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47, 
     & 48,49,50,51,52,53,54/

      data com/0.0d0,0.0d0,0.0d0/

      external musfrc,len_trim


c  Initialize the SD/FAST routines:
      call sdgrav(gvec)
      call sdinit

c  GET INIT FILE LOCATION FROM ENVIRONMENT
      call getenv("D_OptWlkInit",initdir)
      call strcrnch(initdir,clen)
c      print*,'clen = ',clen
      if(clen.eq.0) then
         initdir = '.'
      endif
      print*,'initdir = ',initdir

c  Which node is being altered
      filename = initdir(1:clen)//'/wnode.in'
      print*,'Loading ',filename
      open(10,file=filename)
      read(10,*) minnode,maxnode,derivnode
      close(10)
c      print*,minnode,maxnode,derivnode

c  Load the controls:
      filename = initdir(1:clen)//'/wcontrols'
      print*,'Loading ',filename
      inquire(file=filename,exist=ex)   

      if(.not. ex)then

ccc       print *

       print *,'**ERROR**  File "wcontrols" not found  ** ERROR **'

ccc       print *

       stop

      endif

      open(10,file=filename)

       read(10,*)(tnode(i),i=1,nnodes)

       read(10,*) (x(i), i=1,ncntr)

      close(10)

ccc      x(i) = x(i) / 1.13d0



c  Load the constraint names
      filename = initdir(1:clen)//'/constr.23'
      print*,'Loading ',filename
      open(10,file=filename)

      do i = 1,nconstr

        read(10,100) constrname(i)

      enddo

      close(10)



c  Load the initial conditions:
      filename = initdir(1:clen)//'/winit.in'
      print*,'Loading ',filename
      inquire(file=filename,exist=ex)

      if(.not. ex)then

ccc       print *

       print *,'**ERROR**  File "winit.in" not found ** ERROR **'   

ccc       print *

       stop

      endif



      open(20,file=filename)

       read(20,*) maxitr,drvtype,sclflg,dxi,df,inf

       read(20,*) ( y(i), i=1,dof+1)

       read(20,*) ( y(ivel+i), i=1,dof)

      close(20)

      do i = 1,nmus

       y(imsf+i) = x(i)

      enddo

      do i = 1,nmus

       y(iatv+i) = x(i)

      enddo

      print*,'final time = ',tfinal



c  Unbound the controls

      call xunbound23(x,x)



c  Set derivatives perturbation size

      call setdx(dxi,df,dx)



c  Turn the muscles on:

      do i = 1,nmus

       muson(i) = 1

      enddo



c  Read in the SD/FAST numbers: 
      filename = initdir(1:clen)//'/sd.23'
      print*,'Loading ',filename
      open(30,file=filename, 

     &     status='old')

c     BODYTOJOINT VECTORS:

       do i = 1,nbod

         read(30,*)(btj(k,i),k=1,3)

       enddo

c     INBTOJOINT VECTORS:

       do i = 1,nbod

         read(30,*)(itj(k,i),k=1,3)

       enddo

c     PIN AXSES:
       do i = 1,nbod
        do j = 1,npin(i)
         read(30,*)(pin(k,j,i),k=1,3)
        enddo
       enddo
      close(30)





c  Convert angles to radians:

c  (note that first three states are translations.)

      do i = 4,nq

         y(i) = dtr * y(i)

      enddo

      do i = 4,nu
         y(ivel+i) = dtr * y(ivel+i)
      enddo 





c CONVERT TO EULER PARAMETERS:
      call sdang2st(y,y)



c  Initialize the penalty functions:

      do i = 1,npen
       pennode(1,i) = 0.d0
      enddo







c  Initialize integration variables:
      stepvec(1) = 0


c  Get the segment masses and the total body weight:
      call sdgetmass(pelvis,pelmas)
      call sdgetmass(hat,hatmas)
      call sdgetmass(rfemur,femmas)
      call sdgetmass(rtibia,tibmas)
      call sdgetmass(rhindfoot,hftmas)
      call sdgetmass(rtoes,toemas)

      bodmas = pelmas + hatmas + 2.d0*(femmas+tibmas+hftmas+toemas)
      bodwht = -gvec(2) * bodmas 
      print*,'gvec = ',gvec(1),gvec(2),gvec(3)
      print*,'bodwht = ',bodwht
      print*,'bodmas = ',bodmas


c  Initialize various muscle model quanitites:
      filename = initdir(1:clen)//'/lower.mus.23'
      print*,'Muscle file: ',filename
      call mmspec(filename,nmus,mpt,fom,lom,lst,pennation,slow,mass)

      call mmintl(nmus,fom,lom,lst,pennation,slow,mass)

      do i = 1,nmus

ccc        print*,'mass ',i,' = ',mass(i)

        fast(i) = 1.d0 - slow(i)

      enddo





c  Initialize the skeletal geometry:
      filename = initdir(1:clen)//'/lower.skg.23'
      print*,'Geometry file: ',filename
      call skgspec23(filename,nmus,mpt,musbod,order,

     &             ro,ri,roe,rob,ria,vialen,viaang,viaadd,viadof)



c  Read in the viacylinder coordinates for GAS and HAMS:

      do i = 1,nmus

        do j = 1,3

          cyl(j,i) = 0.0d0

        enddo

      enddo

      filename = initdir(1:clen)//'/viaarcs.23'
      print*,'Loading ',filename
      open(20,file=filename)

       read(20,*)cyl(1,rgas),cyl(2,rgas),cyl(3,rgas),

     &           cylR(rgas)

       read(20,*)cyl(1,rhams),cyl(2,rhams),cyl(3,rhams),

     &           cylR(rhams)

       read(20,*)cyl(1,rgmax_l),cyl(2,rgmax_l),cyl(3,rgmax_l),

     &           cylR(rgmax_l)

       read(20,*)cyl(1,rgmax_m),cyl(2,rgmax_m),cyl(3,rgmax_m),  

     &           cylR(rgmax_m)

       read(20,*)cyl(1,rilpso),cyl(2,rilpso),cyl(3,rilpso),

     &           cylR(rilpso)

       read(20,*)cyl(1,lgas),cyl(2,lgas),cyl(3,lgas),

     &           cylR(lgas)

       read(20,*)cyl(1,lhams),cyl(2,lhams),cyl(3,lhams),

     &           cylR(lhams)

       read(20,*)cyl(1,lgmax_l),cyl(2,lgmax_l),cyl(3,lgmax_l),

     &           cylR(lgmax_l)

       read(20,*)cyl(1,lgmax_m),cyl(2,lgmax_m),cyl(3,lgmax_m),

     &           cylR(lgmax_m)

       read(20,*)cyl(1,lilpso),cyl(2,lilpso),cyl(3,lilpso),

     &           cylR(lilpso)

      close(20)



c  Transform the actuator coordinates:

      call ref_intl23





c FIND PELVIS Y, PELVIS 0z, 0subtalar, AND 0toe

      print*,'Initializing positions...'

      call init1(y)



c ASSIGN VELOCITIES

c   angular: HipY, Ank, Sub

      call init2(y)

c   translational: Pelvis X, Y, Z 

ccc      call init3(y)

c	print*,'rhindfoot = ',rhindfoot
	print*,'com=',com(1),com(2),com(3)
      call sdvel(rhindfoot,com,footVel)

      y(25) = -footVel(1)

      y(26) = -footVel(2)

      y(27) = -footVel(3)

      print*,'velocities = ',y(25),y(26),y(27)





c  Initialize sx0 and sz0:

      print*,'Initializing sx0 and sz0 ...'

      do i = 1,nq

       q(i) = y(i)

      enddo

      do i = 1,nu

       u(i) = y(ivel+i)

      enddo

      call sdstate(tnode(1),q,u)

c   ALL TO ZERO

      do i = 1,ns

       call sdpos(sbody(i),bodyspt(1,i),spt(1,i))

       sx0node(1,i) = spt(1,i)

       sz0node(1,i) = spt(3,i)

      enddo

c   RIGHT FOOT

      sx0node(1,1) = spt(1,1) - 28.d0/sk       

      sz0node(1,1) = spt(3,1) - 43.d0/sk       

      sx0node(1,2) = spt(1,2) - 53.d0/sk       

      sz0node(1,2) = spt(3,2) - 47.d0/sk       

      sx0node(1,3) = spt(1,3) - 28.d0/sk       

      sz0node(1,3) = spt(3,3) + 21.d0/sk       

      sx0node(1,4) = spt(1,4) - 63.d0/sk       

      sz0node(1,4) = spt(3,4) +  7.d0/sk       

      sx0node(1,5) = spt(1,5) -  2.d0/sk       

      sz0node(1,5) = spt(3,5) -  1.d0/sk



c   FOR CALLING ROUTINE

      do i = 1,ns

        sxo(i) = sx0node(1,i)

        szo(i) = sz0node(1,i)

      enddo   



c  ASSIGN TO ynode

c      print*,'Assign to ynode ...'

      do i = 1,nstpin

        do j = 1,nnodes

          ynode(j,i) = 0.d0

        enddo

      enddo

      do i = 1,nst

       ynode(1,i) = y(i)

      enddo



c  COMPUTE THE MUSCLE FORCES GIVEN ynode

c      print*,'Computing th muscle forces ...'

      call xbound23(x,xb,ynode)

      call setmusfrc23(ynode)



c  SET GRAPHICS INITIALIZATION FLAG TO ZERO (meaning not initialized)

      event_draw = 0



      print*,'Finished in intl.'

100   format(a)



      return

      end











c============================================================================

      subroutine setdx(dxi,df,dx)

c============================================================================

      implicit none



      include "w23params.h"



      integer i,j,k,l,len

      real*8 dxi,denom

      real*8 pn(vcntr),cn(vcntr+1,nconstr)

      real*8 df,dxc(nconstr+1)

      character*5 base

      character*21 extension

      character*41 filename

      logical ex



      include "w23comblk.h"



      data base/'drvs.'/



c  Construct File Name

      write(extension,*)derivnode

      filename = base//extension

      call strcrnch(filename,len)



c  Does file exist

      inquire(file=filename,exist=ex)

      if(.not.ex) then

        print*,'Could not find file ',filename

        do i = 1,vcntr

          dx(i) = dxi

        enddo

        return

      endif     

 

c  Read in derivatives

      open(30,file=filename,status='unknown')

       read(30,*)i,j,k,l

       read(30,*) (pn(j),j=1,vcntr)

       do j = 1,nconstr

         read(30,*) (cn(i,j),i=1,vcntr)

       enddo

      close(30)



c  Compute best average dx

      do i = 1,vcntr

        do j = 1,nconstr

          denom = dmax1(1.d-12,dabs(cn(i,j)))

          dxc(j) = df/denom

        enddo

        denom = dmax1(1.d-12,dabs(pn(i)))

        dxc(nconstr+1) = df/denom



c     average

ccc        dx(i) = 0

ccc        do j = 1,nconstr+1

ccc          dx(i) = dx(i) + dxc(j)

ccc        enddo

ccc        dx(i) = dx(i)/(nconstr+1)

ccc        dx(i) = dmin1(dx(i),0.9d0)



c     accurate for most volotile constraint

        dx(i) = 0.9d0

        do j = 1,nconstr+1

           dx(i) = dmin1(dx(i),dxc(j))

        enddo



        enddo



      return

      end











c============================================================================

      subroutine init1(y)

c============================================================================



      implicit none



      include "w23params.h"

#ifndef UNIX
	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end

	interface to subroutine sdst2ang
     & [C,ALIAS:'_sdst2ang_'] (aQ,rQAng)
	real*8 aQ(*)
	real*8 rQAng(*)
	end
#endif

      integer n

      parameter(n=4)



      integer i



      real*8 acc

      real*8 is(nq+nu)

      real*8 ix(n),idx(n),ic(n),icx(n,n)

      real*8 converge



      data acc/1.0d-6/



      include "w23comblk.h"

      print*,'gvec = ',gvec(1),gvec(2),gvec(3)


c COPY THE STATES INTO A NEW VECTOR

      call sdst2ang(y,is)

      do i = 1,nu

        is(nq+i) = 0.0d0

      enddo


c   SET THE CONTROLS

      ix(1) = is(2)

      ix(2) = is(6)

      ix(3) = is(15)

      ix(4) = is(16)



cITERATION LOOP - - - - - - - - - - - - - - -

20    continue



c   EVALUATE THE CONSTRAINTS

      call evalc1(is,ic)


c   EVALUATE THE DERIVATIVE OF THE CONSTRAINTS

      call evalcx1(ix,is,icx)



c   FIND THE CHANGE IN X

      call evaldx1(ic,icx,idx)



c   CHANGE THE CONTROLS AND THE STATES

      do i = 1,n

        ix(i) = ix(i) + 1.0d-1*idx(i)

      enddo

      call setstate1(ix,is)



c   CHECK FOR CONVERGENCE

      converge = 0.0d0

      do i = 1,n

         converge = converge + ic(i)*ic(i)

      enddo

      if (converge .gt. acc) goto 20

c - - - - - - - - - -- - - - - - - -- - - - -



      

c   SET THE ORIGINAL STATE VECTOR

      call sdang2st(is,y)





      return

      end



      





c===========================================================================

      subroutine setstate1(ix,is)

c===========================================================================

      implicit none

      include "w23params.h"

      integer n

      parameter (n=4)

      real*8 ix(n),is(nq+nu)

      include "w23comblk.h"



      is(2) = ix(1)

      is(6) = ix(2)

      is(15) = ix(3)

      is(16) = ix(4)



      return

      end











c===========================================================================

      subroutine evalc1(is,ic)

c===========================================================================



      implicit none



      include "w23params.h"

c#ifndef UNIX
	interface to subroutine sdstate
     & [C,ALIAS:'_sdstate_'] (aT,aQ,aU)
	real*8 aT [REFERENCE]
	real*8 aQ(*)
	real*8 aU(*)
	end

	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end
c#endif

      integer i,n

      parameter(n=4)



      real*8 fy

      real*8 is(nq+nu),ic(n)

      real*8 sforce(3,ns),spt(3,ns),sptv(3,ns)



      data fy/831.d0/



      include "w23comblk.h"





c COMPUTE SPRING FORCES

      call sdang2st(is,q)

      do i = 1,nu

         u(i) = is(nq+i)

      enddo

      call sdstate(0.0d0,q,u)

      call sforce23(0.0d0,q,u,sforce,spt,tqlig)



c COMPUTE CONSTRAINTS

      ic(1) = 1.0d-3 * (sforce(2,1) - 236.d0)

      ic(2) = 1.0d-3 * (sforce(2,3) - 212.d0)

      ic(3) = 1.0d-3 * (sforce(2,4) - 173.d0)

      ic(4) = 1.0d-3 * (sforce(2,1) + sforce(2,2) + sforce(2,3) + 

     &                  sforce(2,4) + sforce(2,5) - fy)



      return

      end











c===========================================================================

      subroutine evalcx1(ix,is,icx)

c===========================================================================



      implicit none



      include "w23params.h"





      integer i,j,n

      parameter (n=4)

   

      real*8 deltax

      real*8 ix(n),is(nq+nu),icx(n,n)

      real*8 ixb(n),ixf(n),icf(n),icb(n)



      include "w23comblk.h"



      data deltax/1.0d-6/





c SET THE CONTROLS

      do i = 1,n

        ixb(i) = ix(i)

        ixf(i) = ix(i)

      enddo



c COMPUTE THE NUMERICAL DERIVATIVES

      do i = 1,n



c     FORWARD

        ixf(i) = ix(i) + deltax

        call setstate1(ixf,is)

        call evalc1(is,icf)

        ixf(i) = ix(i)

        call setstate1(ix,is)



c     BACKWARD

        ixb(i) = ix(i) - deltax

        call setstate1(ixb,is)

        call evalc1(is,icb)

        ixb(i) = ix(i)

        call setstate1(ix,is)



c     DERIVATIVE

        do j = 1,n

            icx(j,i) = 0.5d0 * (icf(j) - icb(j)) / deltax

        enddo



      enddo





      return

      end









c===========================================================================

      subroutine evaldx1(ic,icx,idx)

c===========================================================================



      implicit none



      integer n

      parameter(n=4)



      real*8 ic(n),icx(n,n),idx(n)

      real*8 icxt(n,n),icneg(n)



      integer rtn,bgTransposeMtx,bgScaleMtx,bgSolveLinear

      external bgTransposeMtx,bgScaleMtx,bgSolveLinear



c TRANSPOSE icx FOR C

      rtn = bgTransposeMtx(n,n,icx,icxt)
cDEC$ ALIAS bgTransposeMtx,"_bgtransposemtx_"	



c NEGATE THE CONSTRAINTS

cDEC$ ALIAS bgScaleMtx,"_bgscalemtx_"	
      rtn = bgScaleMtx(1,n,ic,-1.0d0,icneg)



c SOLVE LINEAR icxt * idx = icneg 

cDEC$ ALIAS bgSolveLinear,"_bgsolvelinear_"	
      rtn = bgSolveLinear(n,icxt,idx,icneg)





      return

      end























c============================================================================

      subroutine init2(y)

c============================================================================



      implicit none



      include "w23params.h"

c#ifndef UNIX
	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end

	interface to subroutine sdst2ang
     & [C,ALIAS:'_sdst2ang_'] (aQ,rQAng)
	real*8 aQ(*)
	real*8 rQAng(*)
	end
c#endif

      integer n

      parameter(n=3)



      integer i



      real*8 acc

      real*8 is(nq+nu)

      real*8 ix(n),idx(n),ic(n),icx(n,n)

      real*8 converge



      data acc/1.0d-6/



      include "w23comblk.h"



c COPY THE STATES INTO A NEW VECTOR

      call sdst2ang(y,is)
      do i = 1,nu

        is(nq+i) = y(nq+i)

      enddo



c SET THE CONTROLS

      ix(1) = is(36)

      ix(2) = is(38)

      ix(3) = is(39)



c ITERATION LOOP - - - - - - - - - - - - - - -

20    continue



c   EVALUATE THE CONSTRAINTS

      call evalc2(is,ic)



c   EVALUATE THE DERIVATIVE OF THE CONSTRAINTS

      call evalcx2(ix,is,icx)



c   FIND THE CHANGE IN X

      call evaldx2(ic,icx,idx)



c   CHANGE THE CONTROLS AND THE STATES

      do i = 1,n

        ix(i) = ix(i) + 1.0d-1*idx(i)

      enddo

      call setstate2(ix,is)



c   CHECK FOR CONVERGENCE

      converge = 0.0d0

      do i = 1,n

         converge = converge + ic(i)*ic(i)

      enddo

      if (converge .gt. acc) goto 20

c - - - - - - - - - -- - - - - - - -- - - - -



      

c   SET THE ORIGINAL STATE VECTOR

      call sdang2st(is,y)

      do i = 1,nu
        y(nq+i) = is(nq+i)
      enddo





      return

      end



      





c===========================================================================

      subroutine setstate2(ix,is)

c===========================================================================

      implicit none

      include "w23params.h"

      integer n

      parameter (n=3)

      real*8 ix(n),is(nq+nu)

      include "w23comblk.h"



      is(36) = ix(1)

      is(38) = ix(2)

      is(39) = ix(3)



      return

      end











c===========================================================================

      subroutine evalc2(is,ic)

c===========================================================================



      implicit none



      include "w23params.h"

c#ifndef UNIX
	interface to subroutine sdstate
     & [C,ALIAS:'_sdstate_'] (aT,aQ,aU)
	real*8 aT [REFERENCE]
	real*8 aQ(*)
	real*8 aU(*)
	end

	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end

	interface to subroutine sdangvel
     & [C,ALIAS:'_sdangvel_'] (aBody,rAngVel)
	integer*4 aBody [REFERENCE]
	real*8 rAngVel(3)
	end

      interface to subroutine sdtrans
     & [C,ALIAS:'_sdtrans_'] (aBody1,aVec1,aBody2,rVec2)
	integer*4 aBody1 [REFERENCE]
	real*8 aVec1(3)
	integer*4 aBody2 [REFERENCE]
	real*8 rVec2(3)
	end
c#endif

      integer i,n

      parameter(n=3)



      real*8 is(nq+nu),ic(n)

      real*8 footAngVel(3)



      include "w23comblk.h"





c COMPUTE THE FOOT ANGULAR VELOCITY 

      call sdang2st(is,q)

      do i = 1,nu

         u(i) = is(nq+i)

      enddo

      call sdstate(0.0d0,q,u)

      call sdangvel(rhindfoot,footAngVel)

      call sdtrans(rhindfoot,footAngVel,ground,footAngVel) 



c COMPUTE CONSTRAINTS

      ic(1) = footAngVel(1)

      ic(2) = footAngVel(2)

      ic(3) = footAngVel(3)





      return

      end











c===========================================================================

      subroutine evalcx2(ix,is,icx)

c===========================================================================



      implicit none



      include "w23params.h"





      integer i,j,n

      parameter (n=3)

   

      real*8 deltax

      real*8 ix(n),is(nq+nu),icx(n,n)

      real*8 ixb(n),ixf(n),icf(n),icb(n)



      include "w23comblk.h"



      data deltax/1.0d-6/





c SET THE CONTROLS

      do i = 1,n

        ixb(i) = ix(i)

        ixf(i) = ix(i)

      enddo



c COMPUTE THE NUMERICAL DERIVATIVES

      do i = 1,n



c     FORWARD

        ixf(i) = ix(i) + deltax

        call setstate2(ixf,is)

        call evalc2(is,icf)

        ixf(i) = ix(i)

        call setstate2(ix,is)



c     BACKWARD

        ixb(i) = ix(i) - deltax

        call setstate2(ixb,is)

        call evalc2(is,icb)

        ixb(i) = ix(i)

        call setstate2(ix,is)



c     DERIVATIVE

        do j = 1,n

            icx(j,i) = 0.5d0 * (icf(j) - icb(j)) / deltax

        enddo



      enddo





      return

      end









c===========================================================================

      subroutine evaldx2(ic,icx,idx)

c===========================================================================



      implicit none



      integer n

      parameter(n=3)



      real*8 ic(n),icx(n,n),idx(n)

      real*8 icxt(n,n),icneg(n)



      integer rtn,bgTransposeMtx,bgScaleMtx,bgSolveLinear

      external bgTransposeMtx,bgScaleMtx,bgSolveLinear



c TRANSPOSE icx FOR C

      rtn = bgTransposeMtx(n,n,icx,icxt)
cDEC$ ALIAS bgTransposeMtx,"_bgtransposemtx_"	



c NEGATE THE CONSTRAINTS

      rtn = bgScaleMtx(1,n,ic,-1.0d0,icneg)
cDEC$ ALIAS bgScaleMtx,"_bgscalemtx_"	



c SOLVE LINEAR icxt * idx = icneg 

cDEC$ ALIAS bgSolveLinear,"_bgsolvelinear_"	
      rtn = bgSolveLinear(n,icxt,idx,icneg)





      return

      end



















c============================================================================

      subroutine init3(y)

c============================================================================



      implicit none



      include "w23params.h"


c#ifndef UNIX
	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end

	interface to subroutine sdst2ang
     & [C,ALIAS:'_sdst2ang_'] (aQ,rQAng)
	real*8 aQ(*)
	real*8 rQAng(*)
	end
c#endif


      integer n

      parameter(n=3)



      integer i



      real*8 acc

      real*8 is(nq+nu)

      real*8 ix(n),idx(n),ic(n),icx(n,n)

      real*8 converge



      data acc/1.0d-6/



      include "w23comblk.h"



c COPY THE STATES INTO A NEW VECTOR

      call sdst2ang(y,is)

      do i = 1,nu

        is(nq+i) = y(nq+i) 

      enddo



c   SET THE CONTROLS

      ix(1) = is(25)

      ix(2) = is(26)

      ix(3) = is(27)



cITERATION LOOP - - - - - - - - - - - - - - -

20    continue



c   EVALUATE THE CONSTRAINTS

      call evalc3(is,ic)



c   EVALUATE THE DERIVATIVE OF THE CONSTRAINTS

      call evalcx3(ix,is,icx)



c   FIND THE CHANGE IN X

      call evaldx3(ic,icx,idx)



c   CHANGE THE CONTROLS AND THE STATES

      do i = 1,n

        ix(i) = ix(i) + 1.0d-1*idx(i)

      enddo

      call setstate3(ix,is)



c   CHECK FOR CONVERGENCE

      converge = 0.0d0

      do i = 1,n

         converge = converge + ic(i)*ic(i)

      enddo

      if (converge .gt. acc) goto 20

c - - - - - - - - - -- - - - - - - -- - - - -



      

c   SET THE ORIGINAL STATE VECTOR

      call sdang2st(is,y)

      do i = 1,nu

        y(nq+i) = is(nq+i)

      enddo





      return

      end



      





c===========================================================================

      subroutine setstate3(ix,is)

c===========================================================================

      implicit none

      include "w23params.h"

      integer n

      parameter (n=3)

      real*8 ix(n),is(nq+nu)

      include "w23comblk.h"



      is(25) = ix(1)

      is(26) = ix(2)

      is(27) = ix(3)



      return

      end











c===========================================================================

      subroutine evalc3(is,ic)

c===========================================================================



      implicit none



      include "w23params.h"


c#ifndef UNIX
	interface to subroutine sdstate
     & [C,ALIAS:'_sdstate_'] (aT,aQ,aU)
	real*8 aT [REFERENCE]
	real*8 aQ(*)
	real*8 aU(*)
	end

	interface to subroutine sdang2st
     & [C,ALIAS:'_sdang2st_'] (aQAng,rQ)
	real*8 aQAng(*)
	real*8 rQ(*)
	end

	interface to subroutine sdvel
     & [C,ALIAS:'_sdvel_'] (aBody,aPoint,rVel)
	integer*4 aBody [REFERENCE]
	real*8 aPoint(3)
	real*8 rVel(3)
	end
c#endif

      integer i,n

      parameter(n=3)



      real*8 is(nq+nu),ic(n)

      real*8 com(3),footVel(3)



      include "w23comblk.h"

 

      data com/0.0d0,0.0d0,0.0d0/





c COMPUTE THE FOOT CENTER OF MASS INERTIAL VELOCITY 

      call sdang2st(is,q)

      do i = 1,nu

         u(i) = is(nq+i)

      enddo

      call sdstate(0.0d0,q,u)

      call sdvel(rhindfoot,com,footVel)



c COMPUTE CONSTRAINTS

      ic(1) = footVel(1)

      ic(2) = footVel(2)

      ic(3) = footVel(3)





      return

      end











c===========================================================================

      subroutine evalcx3(ix,is,icx)

c===========================================================================



      implicit none



      include "w23params.h"





      integer i,j,n

      parameter (n=3)

   

      real*8 deltax

      real*8 ix(n),is(nq+nu),icx(n,n)

      real*8 ixb(n),ixf(n),icf(n),icb(n)



      include "w23comblk.h"



      data deltax/1.0d-6/





c SET THE CONTROLS

      do i = 1,n

        ixb(i) = ix(i)

        ixf(i) = ix(i)

      enddo



c COMPUTE THE NUMERICAL DERIVATIVES

      do i = 1,n



c     FORWARD

        ixf(i) = ix(i) + deltax

        call setstate3(ixf,is)

        call evalc3(is,icf)

        ixf(i) = ix(i)

        call setstate3(ix,is)



c     BACKWARD

        ixb(i) = ix(i) - deltax

        call setstate3(ixb,is)

        call evalc3(is,icb)

        ixb(i) = ix(i)

        call setstate3(ix,is)



c     DERIVATIVE

        do j = 1,n

            icx(j,i) = 0.5d0 * (icf(j) - icb(j)) / deltax

        enddo



      enddo





      return

      end









c===========================================================================

      subroutine evaldx3(ic,icx,idx)

c===========================================================================



      implicit none



      integer n

      parameter(n=3)



      real*8 ic(n),icx(n,n),idx(n)

      real*8 icxt(n,n),icneg(n)



      integer rtn,bgTransposeMtx,bgScaleMtx,bgSolveLinear

      external bgTransposeMtx,bgScaleMtx,bgSolveLinear



c TRANSPOSE icx FOR C

cDEC$ ALIAS bgTransposeMtx,"_bgtransposemtx_"	
      rtn = bgTransposeMtx(n,n,icx,icxt)


c NEGATE THE CONSTRAINTS
cDEC$ ALIAS bgScaleMtx,"_bgscalemtx_"	
      rtn = bgScaleMtx(1,n,ic,-1.0d0,icneg)


c SOLVE LINEAR icxt * idx = icneg 
cDEC$ ALIAS bgSolveLinear,"_bgsolvelinear_"
      rtn = bgSolveLinear(n,icxt,idx,icneg)



      return

      end









