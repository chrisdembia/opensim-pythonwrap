      block data moddat23

c  This file contains various parameters used in the 23 code.

c==============================================================================
c  Revision record:
c   8/18/93  9:40 am
c==============================================================================


      implicit none

      include 'w23params.h'
      include 'w23comblk.h'


c  Segment reference numbers:
      data ground/0/,pelvis/1/,hat/2/,rfemur/3/,rtibia/4/,
     &     rhindfoot/5/,rtoes/6/,lfemur/7/,ltibia/8/,
     &     lhindfoot/9/,ltoes/10/


c  Joint reference numbers:
      data pel/1/,back/2/,
     &     rhip/3/,rkne/4/,rank/5/,rtoe/6/,
     &     lhip/7/,lkne/8/,lank/9/,ltoe/10/


c  Actuator reference numbers:
      data  rfdh/1/,redh/2/
      data  rdfin/3/,rdfev/4/,ropfin/5/,ropfev/6/,rsol/7/
      data  rgas/8/
      data  rbfsh/9/,rvas/10/
      data  rrf/11/,rhams/12/
      data  rgra/13/,rtfl/14/,rsar/15/ 
      data  rgmax_l/16/,rgmax_m/17/,rgmed_a/18/,rgmed_p/19/
      data  radm/20/,radlb/21/,rilpso/22/,rpect/23/,rpiri/24/
      data  respin/25/,rinobl/26/,rexobl/27/
      data  lfdh/28/,ledh/29/
      data  ldfin/30/,ldfev/31/,lopfin/32/,lopfev/33/,lsol/34/   
      data  lgas/35/
      data  lbfsh/36/,lvas/37/
      data  lrf/38/,lhams/39/
      data  lgra/40/,ltfl/41/,lsar/42/ 
      data  lgmax_l/43/,lgmax_m/44/,lgmed_a/45/,lgmed_p/46/
      data  ladm/47/,ladlb/48/,lilpso/49/,lpect/50/,lpiri/51/
      data  lespin/52/,linobl/53/,lexobl/54/



c Number of axes at each joint:
c An array that give the number of axes for a given joint
      data npin/3,3,3,1,2,1,3,1,2,1/

c Joint Numbers:
c An array that gives the SDFAST joint number given a state number
      data joint /1,1,1,1,1,1,2,2,2,3,3,3,4,5,5,6,7,7,7,8,9,9,10,
     &            1,
     &            1,1,1,1,1,1,2,2,2,3,3,3,4,5,5,6,7,7,7,8,9,9,10/

c Axis Numbers:
c An array that gives the SDFAST axis number given a state number
      data axis /1,2,3,4,5,6,1,2,3,1,2,3,1,1,2,1,1,2,3,1,1,2,1,
     &           7,
     &           1,2,3,4,5,6,1,2,3,1,2,3,1,1,2,1,1,2,3,1,1,2,1/

c SPRING BODIES:
c An array that gives the body on which a given spring acts
      data sbody /5,5,5,5,6,9,9,9,9,10/

c SPRING PARAMETERS
      data y0,b0,b1,c0,c1 / 6.5905d-3,
     &     0.5336322d0,0.0d0,0.0d0,-1150.8002d0/    
      data s0,s1,s2 /0.02d0,10.0d0,500.0d0/
      data sk,mu,sdamp /6.9d4,0.7d0,1.0d3/
      data bodyspt / -0.071650d0,-0.038653d0,-0.050428d0,
     &               -0.091740d0,-0.038653d0,0.023202d0,
     &                0.123629d0,-0.038653d0,-0.029196d0,
     &                0.070755d0,-0.038653d0,0.069117d0,
     &                0.050769d0,-0.018500d0,0.003468d0,
     &               -0.071650d0,-0.038653d0,0.050428d0,
     &               -0.091740d0,-0.038653d0,-0.023202d0,
     &                0.123629d0,-0.038653d0,0.029196d0,
     &                0.070755d0,-0.038653d0,-0.069117d0,
     &                0.050769d0,-0.018500d0,-0.003468d0/

c LIGAMENT TORQUES:
      data k0lig /0.1390577d0,0.0d0,0.0d0,
     &            0.0d0,0.0d0,0.0d0,0.0d0,
     &            0.49257884d0,0.0d0,-0.05d0,
     &            0.0d0,0.0d0,0.0d0,0.0d0,
     &            0.49257884d0,0.0d0,-0.05d0/
      data k1lig1 /-0.35d0,-0.25d0,-0.25d0,
     &             -2.44d0,-0.03d0, -0.03d0,-6.09d0,
     &             -4.0d0,-60.21d0,-0.9d0,
     &             -2.44d0,-0.03d0, -0.03d0,-6.09d0,
     &             -4.0d0,-60.21d0,-0.9d0/  
      data k2lig1 /30.72d0,20.36d0,20.36d0,
     &             5.05d0,14.94d0,14.94d0,33.94d0,
     &             8.0d0,16.32d0,14.87d0,
     &             5.05d0,14.94d0,14.94d0,33.94d0,
     &             8.0d0,16.32d0,14.87d0/
      data theta1 /0.03d0,0.17d0,0.17d0,
     &             1.81d0,0.50d0,0.92d0,0.13d0,
     &             0.2618d0,0.65d0,0.21d0,
     &             1.81d0,0.50d0,0.92d0,0.13d0,
     &             0.2618d0,0.65d0,0.21d0/
      data k1lig2 /0.25d0,0.25d0,0.25d0,
     &             1.51d0,0.03d0, 0.03d0,11.03d0,
     &             1.0d0,60.21d0,0.18d0,
     &             1.51d0,0.03d0, 0.03d0,11.03d0,
     &             1.0d0,60.21d0,0.18d0/
      data k2lig2 /-20.36d0,-20.36d0,-20.36d0,
     &             -21.88d0,-14.94d0,-14.94d0,-11.33d0,
     &             -22.0d0,-16.32d0,-70.08d0, 
     &             -21.88d0,-14.94d0,-14.94d0,-11.33d0,
     &             -22.0d0,-16.32d0,-70.08d0/
      data theta2 /-0.35d0,-0.17d0,-0.17d0,
     &             -0.47d0,-0.50d0,-0.92d0,-2.40d0,
     &             -0.4712d0,-0.65d0,-0.02d0,
     &             -0.47d0,-0.50d0,-0.92d0,-2.40d0,
     &             -0.4712d0,-0.65d0,-0.02d0/

c  Gravity:
      data gvec/0.d0,-9.81d0,0.d0/

c  Performance and Constraint Scalings:
      data basal/60.0d0/
      data ctol1/0.10d0/
      data ctol2/0.01d0/
      data ctolm/0.05d0/
      data cs1/1.0d-1/
      data cs2/1.0d-2/
      data cs25/4.0d-2/
      data cs3/1.0d-3/
      data cs4/1.0d-4/
      data cs5/1.0d-5/

c  Reference frame offsets for translating the standard skeletal geometry
c   parameters to the dynamical equations frames. These offsets are to be
c   added to the values returned by "skgspec".
c   The offsets are for: pelvis, hat,
c                        rfemur, rtibia,
c                        rhindfoot, rtoe,
c                        lfemur, ltibia,
c                        lhindfoot, ltoe. 

      data rfo/  0.0707d0, 0.0028d0, 0.0100d0 ,
     &           0.0000d0,-0.3202d0, 0.0000d0 ,
     &           0.0020d0, 0.1715d0, 0.0000d0 ,
     &           0.0000d0, 0.1862d0, 0.0000d0 ,  
     &          -0.0839d0, 0.0094d0,-0.0013d0 ,
     &          -0.0262d0, 0.0065d0,-0.0079d0 ,  
     &           0.0020d0, 0.1715d0, 0.0000d0 ,
     &           0.0000d0, 0.1862d0, 0.0000d0 ,  
     &          -0.0839d0, 0.0094d0, 0.0013d0 ,
     &          -0.0262d0, 0.0065d0, 0.0079d0 /  



      end
