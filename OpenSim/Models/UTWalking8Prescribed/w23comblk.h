#ifndef _w23comblk_h_
#define _w23comblk_h_
c "jmp54comblk.h"  Type declarations and common blocks for the kicking model.

c==============================================================================
c  Revision record:
c   11/30/93  8:15 am
c==============================================================================
c
c Note that the file "jmp54params.h" must precede this file in a subroutine.
c
c______________________________________________________________________________


c  Declarations for widely used varibles not in common blocks.

c   Time related variables ------
      integer node
      real*8 t,ta,tb,tf,delta,treal

c   Controls -----
      real*8 xv(vcntr),dx(vcntr),rdx(vcntr),rdx2(vcntr)
      real*8 x(ncntr),xb(bndcntr)
      real*8 atrack(nmus),xtrack(nmus)

c   Statevector -----
      real*8 ynode(nnodes,nstpin),y(nstpin),dy(nstpin)
      real*8 yang(nstpin),q(nq),qdot(nq),u(nu),udot(nu)
      real*8 dytrack(nstpin)

c   Ligament Torques -----
      real*8 tq(nu)
      real*8 tqlig(dof-6)

c   Center of mass -----
      real*8 pcom(3),vcom(3),acom(3)
      
c   Performance and contraints -----
      real*8 p,c(nconstr)


c  Declarations for variables in common blocks:

c   Reference numbers -----
c   --segments
      integer ground,pelvis,hat
      integer rfemur,rtibia,rhindfoot,rtoes
      integer lfemur,ltibia,lhindfoot,ltoes
c   --joints
      integer pel,back
      integer rhip,rkne,rank,rtoe
      integer lhip,lkne,lank,ltoe
c   --muscles
      integer rfdh,redh
      integer rdfin,rdfev,ropfin,ropfev,rsol
      integer rgas
      integer rbfsh,rvas
      integer rrf,rhams
      integer rgra,rtfl,rsar
      integer rgmax_l,rgmax_m,rgmed_a,rgmed_p
      integer radm,radlb,rilpso,rpect,rpiri
      integer respin,rinobl,rexobl
      integer lfdh,ledh
      integer ldfin,ldfev,lopfin,lopfev,lsol
      integer lgas
      integer lbfsh,lvas
      integer lrf,lhams
      integer lgra,ltfl,lsar
      integer lgmax_l,lgmax_m,lgmed_a,lgmed_p
      integer ladm,ladlb,lilpso,lpect,lpiri
      integer lespin,linobl,lexobl

c   SDFAST body, joint, and axis numbers -----
      integer npin
      integer joint,axis
      real*8 btj,itj,pin

c   Constraint Names
      character*16 constrname

c   Derivative Node
      integer minnode,maxnode,derivnode

c   Penalty functions -----
      real*8 pen,pennode

c   Performance and constraints -----
      real*8 basal,ctol1,ctol2,ctolm
      real*8 cs1,cs2,cs25,cs3,cs4,cs5

c   Output arrays -----
      integer trys,steps,filesteps
      real*8 time,state,error,length,velocity
      real*8 gforce,sprpt,sprforce
      real*8 copx,copz
      real*8 comacc,comvel,compos
      real*8 jointforce
      real*8 jaccel,acoef
      real*8 jtorque,jinvtrq

c   Runge numerical integration routines -----
      integer stepvec
      real*8 deltavec,tnode

c   Muscle quantities -----
      real*8 lom,lst,pennation,fom
      real*8 actlen,actsv

c   Muscle metabolism -----
      real*8 slow,fast,mass

c   Anthropometry -----
      real*8 toemas,hftmas,tibmas,femmas,pelmas,hatmas
      real*8 bodmas,bodwht

c   Muscle geometry -----
      integer musbod,order,muson,viadof
      real*8 ri,ro,roe,rob,ria,vialen,viaang,viaadd,rfo  
      real*8 cylR,cyl

c   Gravity vector -----
      real*8 gvec

c   Joint damping -----
      real*8 tqdamp,jdamp

c   Ligament torques -----
      real*8 k0lig
      real*8 xlig1,k1lig1,k2lig1,theta1
      real*8 xlig2,k1lig2,k2lig2,theta2

c   Ground springs -----
      integer sbody
      real*8 sx0,sz0,sx0node,sz0node
      real*8 sk,mu,sdamp,s0,s1,s2
      real*8 y0,b0,b1,c0,c1
      real*8 bodyspt

c  Scale factors for the controls, performance, and constraints -----
      real*8 scalex,scalep,scalec

c   Multi-use arrays. These arrays are available for general use.
      integer imlt
      real*8 rmlt

c   Initialization of graphics process
      integer event_draw



c  Common Blocks:

c   Reference numbers -----
      common/ref1/ground,pelvis,hat
      common/ref2/rfemur,rtibia,rhindfoot,rtoes
      common/ref3/lfemur,ltibia,lhindfoot,ltoes
      common/ref4/pel,back
      common/ref5/rhip,rkne,rank,rtoe
      common/ref6/lhip,lkne,lank,ltoe
      common/ref7/rfdh,redh
      common/ref8/rdfin,rdfev,ropfin,ropfev,rsol
      common/ref9/rgas
      common/ref10/rbfsh,rvas
      common/ref11/rrf,rhams
      common/ref12/rgra,rtfl,rsar
      common/ref13/rgmax_l,rgmax_m,rgmed_a,rgmed_p
      common/ref14/radm,radlb,rilpso,rpect,rpiri
      common/ref15/respin,rinobl,rexobl
      common/ref16/lfdh,ledh
      common/ref17/ldfin,ldfev,lopfin,lopfev,lsol
      common/ref18/lgas
      common/ref19/lbfsh,lvas
      common/ref10/lrf,lhams
      common/ref20/lgra,ltfl,lsar
      common/ref21/lgmax_l,lgmax_m,lgmed_a,lgmed_p
      common/ref22/ladm,ladlb,lilpso,lpect,lpiri
      common/ref23/lespin,linobl,lexobl
      common/SDnums1/joint(nq+nu),axis(nq+nu)
      common/SDnums2/npin(nbod)
      common/SDnums3/btj(3,nbod),itj(3,nbod),pin(3,3,nbod)

c   Anthropometry -----
      common /anth1/toemas,hftmas,tibmas,femmas,pelmas,hatmas
      common /anth2/bodmas,bodwht

c   Muscle geometry -----
      common /skg1/musbod(5,nmus),order(5,nmus),muson(nmus),viadof(nmus)  
      common /skg2/ri(3,nmus),ro(3,nmus),roe(3,nmus),rob(3,nmus)
      common /skg3/ria(3,nmus),vialen(nmus),viaang(nmus),viaadd(nmus)
      common /skg4/rfo(3,nbod)
      common /skg5/cylR(nmus),cyl(3,nmus)

c   Muscle quantities -----
      common/actuator2/lom(nmus),lst(nmus),pennation(nmus),fom(nmus)
      common/actuator3/actlen(nmus),actsv(nmus)

c   Muscle metabolism -----
      common/metab1/slow(nmus),fast(nmus),mass(nmus)

c   Penalty function and some constraints -----
      common /penalty/pen(npen),pennode(nnodes,npen),constrname(nconstr)

c   Output arrays -----
      common/out1/trys,steps,filesteps
      common/out2/time(maxstep),state(nstpin,maxstep)
      common/out3/error(nstpin,maxtry)
      common/out4/length(nmus,maxstep),velocity(nmus,maxstep)
      common/out5/gforce(3,maxstep)
      common/out6/sprpt(3,ns,maxstep),sprforce(3,ns,maxstep)
      common/out7/copx(maxstep),copz(maxstep)
      common/out8/comacc(3,maxstep),comvel(3,maxstep),compos(3,maxstep)
      common/out9/jointforce(3,9,maxstep)
      common/out10/jaccel(nu,maxstep),acoef(5,nu)
      common/out11/jtorque(nu,maxstep),jinvtrq(nu,maxstep)

c   Runge numerical integration routines -----
      common/runge1/stepvec(nnodes)
      common/runge2/deltavec(maxstep),tnode(nnodes)

c   Gravity vector -----
      common /gravity/gvec(3)

c   Joint damping -----
      common/jdamp1/jdamp,tqdamp(dof-6)

c   Ligament torques -----
      common/lig0/k0lig(dof-6)
      common/lig1/xlig1(dof-6),k1lig1(dof-6),k2lig1(dof-6),theta1(dof-6)
      common/lig2/xlig2(dof-6),k1lig2(dof-6),k2lig2(dof-6),theta2(dof-6)

c   Ground springs -----
      common /spring1/sx0(ns),sz0(ns)
      common /spring2/sx0node(nnodes,ns),sz0node(nnodes,ns)
      common /spring3/sk,mu,sdamp,s0,s1,s2
      common /spring4/y0,b0,b1,c0,c1
      common /spring5/bodyspt(3,ns)
      common /spring6/sbody(ns)

c  Scale factors for the controls, performance, and constraints -----
      common /scaling/scalex(ncntr),scalep,scalec(nconstr)

c  Performance
      common /whichnode/minnode,maxnode,derivnode
      common /perform/basal,ctol1,ctol2,ctolm
      common /constraint/cs1,cs2,cs25,cs3,cs4,cs5

c   Multi-use arrays -----
      common/multi1/imlt(maxstep)
      common/multi2/rmlt(maxstep)

c   Event-Draw Process Initialization Flag
      common/graph1/event_draw
