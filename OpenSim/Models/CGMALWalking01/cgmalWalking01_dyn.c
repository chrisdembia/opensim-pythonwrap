/*
Generated 18-Jun-2003 17:59:44 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (cgmalWalking01.sd)

Bodies        Inb
No  Name      body Joint type  Coords q
--- --------- ---- ----------- ----------------
 -1 $ground                                    
  0 RFoot      -1  Planar        0   1   2     
  1 RTibia      0  Pin           3             
  2 RFemur      1  Pin           4             
  3 HAT         2  Pin           5             
  4 LFemur      3  Pin           6             
  5 LTibia      4  Pin           7             
  6 LFoot       5  Pin           8             

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[7],inb_[7],outb_[7],njntdof_[7],njntc_[7],njntp_[7],firstq_[7],
      ballq_[7],firstm_[7],firstp_[7];
    int trans_[9];
} sdgtopo_t;
#define ground (sdgtopo.ground_)
#define nbod (sdgtopo.nbod_)
#define ndof (sdgtopo.ndof_)
#define ncons (sdgtopo.ncons_)
#define nloop (sdgtopo.nloop_)
#define nldof (sdgtopo.nldof_)
#define nloopc (sdgtopo.nloopc_)
#define nball (sdgtopo.nball_)
#define nlball (sdgtopo.nlball_)
#define npres (sdgtopo.npres_)
#define nuser (sdgtopo.nuser_)
#define jtype (sdgtopo.jtype_)
#define inb (sdgtopo.inb_)
#define outb (sdgtopo.outb_)
#define njntdof (sdgtopo.njntdof_)
#define njntc (sdgtopo.njntc_)
#define njntp (sdgtopo.njntp_)
#define firstq (sdgtopo.firstq_)
#define ballq (sdgtopo.ballq_)
#define firstm (sdgtopo.firstm_)
#define firstp (sdgtopo.firstp_)
#define trans (sdgtopo.trans_)

typedef struct {
    double grav_[3],mk_[7],ik_[7][3][3],pin_[9][3];
    double rk_[7][3],ri_[7][3],pres_[9],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[9];
    int gravq_[3],mkq_[7],ikq_[7][3][3],pinq_[9][3],rkq_[7][3],riq_[7][3],presq_
      [9],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[7][3],rcom_[7][3],mkrcomt_[7][3][3],psikg_[3][3],
      psrcomg_[3],psrkg_[3],psrig_[3],psmk_[9],psik_[9][3][3],psrcom_[9][3],
      psrk_[9][3],psri_[9][3];
} sdginput_t;
#define grav (sdginput.grav_)
#define mk (sdginput.mk_)
#define ik (sdginput.ik_)
#define pin (sdginput.pin_)
#define rk (sdginput.rk_)
#define ri (sdginput.ri_)
#define pres (sdginput.pres_)
#define stabvel (sdginput.stabvel_)
#define stabpos (sdginput.stabpos_)
#define rhead (sdginput.rhead_)
#define rcom (sdginput.rcom_)
#define psrcomg (sdginput.psrcomg_)
#define psrcom (sdginput.psrcom_)
#define mkrcomt (sdginput.mkrcomt_)
#define psmk (sdginput.psmk_)
#define psik (sdginput.psik_)
#define psrk (sdginput.psrk_)
#define psri (sdginput.psri_)
#define psmkg (sdginput.psmkg_)
#define psikg (sdginput.psikg_)
#define psrkg (sdginput.psrkg_)
#define psrig (sdginput.psrig_)
#define mtot (sdginput.mtot_)
#define mfrcflg (sdginput.mfrcflg_)
#define roustate (sdginput.roustate_)
#define vpkflg (sdginput.vpkflg_)
#define inerflg (sdginput.inerflg_)
#define mmflg (sdginput.mmflg_)
#define mmlduflg (sdginput.mmlduflg_)
#define wwflg (sdginput.wwflg_)
#define ltauflg (sdginput.ltauflg_)
#define fs0flg (sdginput.fs0flg_)
#define ii (sdginput.ii_)
#define mmap (sdginput.mmap_)
#define gravq (sdginput.gravq_)
#define mkq (sdginput.mkq_)
#define ikq (sdginput.ikq_)
#define pinq (sdginput.pinq_)
#define rkq (sdginput.rkq_)
#define riq (sdginput.riq_)
#define presq (sdginput.presq_)
#define stabvelq (sdginput.stabvelq_)
#define stabposq (sdginput.stabposq_)

typedef struct {
    double curtim_,q_[9],qn_[9],u_[9],cnk_[9][3][3],cnb_[7][3][3];
    double rnk_[9][3],vnk_[9][3],wk_[9][3],rnb_[7][3],vnb_[7][3],wb_[7][3],
      wbrcom_[7][3],com_[3],rnkg_[3];
    double Cik_[9][3][3],rikt_[9][3][3],Iko_[9][3][3],mkrk_[9][3][3],Cib_[7][3][
      3];
    double Wkk_[9][3],Vkk_[9][3],dik_[9][3],rpp_[9][3],rpk_[9][3],rik_[9][3],
      rik2_[9][3];
    double rpri_[9][3],Wik_[9][3],Vik_[9][3],Wirk_[9][3],rkWkk_[9][3],Wkrpk_[9][
      3],VikWkr_[9][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[7][3],utk_[7][3],mfk_[7][3],
      mtk_[7][3];
    double utau_[9],mtau_[9],uacc_[9],uvel_[9],upos_[9];
    double s2_,c2_,s3_,c3_,s4_,c4_,s5_,c5_,s6_,c6_,s7_,c7_,s8_,c8_;
} sdgstate_t;
#define curtim (sdgstate.curtim_)
#define q (sdgstate.q_)
#define qn (sdgstate.qn_)
#define u (sdgstate.u_)
#define cnk (sdgstate.cnk_)
#define cnb (sdgstate.cnb_)
#define rnkg (sdgstate.rnkg_)
#define rnk (sdgstate.rnk_)
#define rnb (sdgstate.rnb_)
#define vnk (sdgstate.vnk_)
#define vnb (sdgstate.vnb_)
#define wk (sdgstate.wk_)
#define wb (sdgstate.wb_)
#define com (sdgstate.com_)
#define Cik (sdgstate.Cik_)
#define Cib (sdgstate.Cib_)
#define rikt (sdgstate.rikt_)
#define Iko (sdgstate.Iko_)
#define mkrk (sdgstate.mkrk_)
#define Wkk (sdgstate.Wkk_)
#define Vkk (sdgstate.Vkk_)
#define dik (sdgstate.dik_)
#define rpp (sdgstate.rpp_)
#define rpk (sdgstate.rpk_)
#define rik (sdgstate.rik_)
#define rik2 (sdgstate.rik2_)
#define rpri (sdgstate.rpri_)
#define Wik (sdgstate.Wik_)
#define Vik (sdgstate.Vik_)
#define Wirk (sdgstate.Wirk_)
#define rkWkk (sdgstate.rkWkk_)
#define Wkrpk (sdgstate.Wkrpk_)
#define VikWkr (sdgstate.VikWkr_)
#define wbrcom (sdgstate.wbrcom_)
#define perr (sdgstate.perr_)
#define verr (sdgstate.verr_)
#define aerr (sdgstate.aerr_)
#define mult (sdgstate.mult_)
#define ufk (sdgstate.ufk_)
#define utk (sdgstate.utk_)
#define utau (sdgstate.utau_)
#define mfk (sdgstate.mfk_)
#define mtk (sdgstate.mtk_)
#define mtau (sdgstate.mtau_)
#define uacc (sdgstate.uacc_)
#define uvel (sdgstate.uvel_)
#define upos (sdgstate.upos_)
#define s2 (sdgstate.s2_)
#define c2 (sdgstate.c2_)
#define s3 (sdgstate.s3_)
#define c3 (sdgstate.c3_)
#define s4 (sdgstate.s4_)
#define c4 (sdgstate.c4_)
#define s5 (sdgstate.s5_)
#define c5 (sdgstate.c5_)
#define s6 (sdgstate.s6_)
#define c6 (sdgstate.c6_)
#define s7 (sdgstate.s7_)
#define c7 (sdgstate.c7_)
#define s8 (sdgstate.s8_)
#define c8 (sdgstate.c8_)

typedef struct {
    double fs0_[9],qdot_[9],Otk_[9][3],Atk_[9][3],AiOiWi_[9][3],Fstar_[9][3];
    double Tstar_[9][3],Fstark_[9][3],Tstark_[9][3],IkWk_[9][3],WkIkWk_[9][3],
      gk_[9][3],IkbWk_[7][3],WkIkbWk_[7][3];
    double w0w0_[7],w1w1_[7],w2w2_[7],w0w1_[7],w0w2_[7],w1w2_[7];
    double w00w11_[7],w00w22_[7],w11w22_[7],ww_[1][1],qraux_[1];
    double mm_[9][9],mlo_[9][9],mdi_[9],IkWpk_[9][9][3],works_[9],workss_[9][9];
    double Wpk_[9][9][3],Vpk_[9][9][3],VWri_[9][9][3];
    int wmap_[1],multmap_[1],jpvt_[1],wsiz_,wrank_;
} sdglhs_t;
#define qdot (sdglhs.qdot_)
#define Otk (sdglhs.Otk_)
#define Atk (sdglhs.Atk_)
#define AiOiWi (sdglhs.AiOiWi_)
#define Fstar (sdglhs.Fstar_)
#define Tstar (sdglhs.Tstar_)
#define fs0 (sdglhs.fs0_)
#define Fstark (sdglhs.Fstark_)
#define Tstark (sdglhs.Tstark_)
#define IkWk (sdglhs.IkWk_)
#define IkbWk (sdglhs.IkbWk_)
#define WkIkWk (sdglhs.WkIkWk_)
#define WkIkbWk (sdglhs.WkIkbWk_)
#define gk (sdglhs.gk_)
#define w0w0 (sdglhs.w0w0_)
#define w1w1 (sdglhs.w1w1_)
#define w2w2 (sdglhs.w2w2_)
#define w0w1 (sdglhs.w0w1_)
#define w0w2 (sdglhs.w0w2_)
#define w1w2 (sdglhs.w1w2_)
#define w00w11 (sdglhs.w00w11_)
#define w00w22 (sdglhs.w00w22_)
#define w11w22 (sdglhs.w11w22_)
#define ww (sdglhs.ww_)
#define qraux (sdglhs.qraux_)
#define mm (sdglhs.mm_)
#define mlo (sdglhs.mlo_)
#define mdi (sdglhs.mdi_)
#define IkWpk (sdglhs.IkWpk_)
#define works (sdglhs.works_)
#define workss (sdglhs.workss_)
#define Wpk (sdglhs.Wpk_)
#define Vpk (sdglhs.Vpk_)
#define VWri (sdglhs.VWri_)
#define wmap (sdglhs.wmap_)
#define multmap (sdglhs.multmap_)
#define jpvt (sdglhs.jpvt_)
#define wsiz (sdglhs.wsiz_)
#define wrank (sdglhs.wrank_)

typedef struct {
    double fs_[9],udot_[9],tauc_[9],dyad_[7][3][3],fc_[9][3],tc_[9][3];
    double ank_[9][3],onk_[9][3],Onkb_[9][3],AOnkri_[9][3],Ankb_[9][3],AnkAtk_[9
      ][3],anb_[7][3],onb_[7][3],dyrcom_[7][3];
    double ffk_[9][3],ttk_[9][3],fccikt_[9][3],ffkb_[7][3],ttkb_[7][3];
} sdgrhs_t;
#define fs (sdgrhs.fs_)
#define udot (sdgrhs.udot_)
#define ank (sdgrhs.ank_)
#define anb (sdgrhs.anb_)
#define onk (sdgrhs.onk_)
#define onb (sdgrhs.onb_)
#define Onkb (sdgrhs.Onkb_)
#define AOnkri (sdgrhs.AOnkri_)
#define Ankb (sdgrhs.Ankb_)
#define AnkAtk (sdgrhs.AnkAtk_)
#define dyrcom (sdgrhs.dyrcom_)
#define ffk (sdgrhs.ffk_)
#define ttk (sdgrhs.ttk_)
#define fccikt (sdgrhs.fccikt_)
#define ffkb (sdgrhs.ffkb_)
#define ttkb (sdgrhs.ttkb_)
#define dyad (sdgrhs.dyad_)
#define fc (sdgrhs.fc_)
#define tc (sdgrhs.tc_)
#define tauc (sdgrhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} sdgtemp_t;
#define temp (sdgtemp.temp_)
#define tmat1 (sdgtemp.tmat1_)
#define tmat2 (sdgtemp.tmat2_)
#define tvec1 (sdgtemp.tvec1_)
#define tvec2 (sdgtemp.tvec2_)
#define tvec3 (sdgtemp.tvec3_)
#define tvec4 (sdgtemp.tvec4_)
#define tvec5 (sdgtemp.tvec5_)
#define tsc1 (sdgtemp.tsc1_)
#define tsc2 (sdgtemp.tsc2_)
#define tsc3 (sdgtemp.tsc3_)

sdgtopo_t sdgtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 7,
    /* ndof */ 9,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 8,
    /* jtype[1] */ 1,
    /* jtype[2] */ 1,
    /* jtype[3] */ 1,
    /* jtype[4] */ 1,
    /* jtype[5] */ 1,
    /* jtype[6] */ 1,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 1,
    /* inb[3] */ 2,
    /* inb[4] */ 3,
    /* inb[5] */ 4,
    /* inb[6] */ 5,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* outb[3] */ 3,
    /* outb[4] */ 4,
    /* outb[5] */ 5,
    /* outb[6] */ 6,
    /* njntdof[0] */ 3,
    /* njntdof[1] */ 1,
    /* njntdof[2] */ 1,
    /* njntdof[3] */ 1,
    /* njntdof[4] */ 1,
    /* njntdof[5] */ 1,
    /* njntdof[6] */ 1,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntc[3] */ 0,
    /* njntc[4] */ 0,
    /* njntc[5] */ 0,
    /* njntc[6] */ 0,
    /* njntp[0] */ 0,
    /* njntp[1] */ 0,
    /* njntp[2] */ 0,
    /* njntp[3] */ 0,
    /* njntp[4] */ 0,
    /* njntp[5] */ 0,
    /* njntp[6] */ 0,
    /* firstq[0] */ 0,
    /* firstq[1] */ 3,
    /* firstq[2] */ 4,
    /* firstq[3] */ 5,
    /* firstq[4] */ 6,
    /* firstq[5] */ 7,
    /* firstq[6] */ 8,
    /* ballq[0] */ -104,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstm[3] */ -1,
    /* firstm[4] */ -1,
    /* firstm[5] */ -1,
    /* firstm[6] */ -1,
    /* firstp[0] */ -1,
    /* firstp[1] */ -1,
    /* firstp[2] */ -1,
    /* firstp[3] */ -1,
    /* firstp[4] */ -1,
    /* firstp[5] */ -1,
    /* firstp[6] */ -1,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 0,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* trans[8] */ 0,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ -9.81,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 1.41,
    /* mk[1] */ 3.51,
    /* mk[2] */ 8.81,
    /* mk[3] */ 43.56,
    /* mk[4] */ 8.81,
    /* mk[5] */ 3.51,
    /* mk[6] */ 1.41,

/* inertia */
    /* ik[0][0][0] */ .0017,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .0067,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ .0068,
    /* ik[1][0][0] */ .0477,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ .0048,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ .0484,
    /* ik[2][0][0] */ .1268,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ .0332,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ .1337,
    /* ik[3][0][0] */ 3.1524,
    /* ik[3][0][1] */ 0.,
    /* ik[3][0][2] */ 0.,
    /* ik[3][1][0] */ 0.,
    /* ik[3][1][1] */ .7978,
    /* ik[3][1][2] */ 0.,
    /* ik[3][2][0] */ 0.,
    /* ik[3][2][1] */ 0.,
    /* ik[3][2][2] */ 3.0691,
    /* ik[4][0][0] */ .1268,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ .0332,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ .1337,
    /* ik[5][0][0] */ .0477,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ .0048,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ .0484,
    /* ik[6][0][0] */ .0017,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ .0067,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ .0068,

/* tree hinge axis vectors */
    /* pin[0][0] */ 1.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 0.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 1.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 0.,
    /* pin[2][2] */ 1.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 1.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 1.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 1.,
    /* pin[6][0] */ 0.,
    /* pin[6][1] */ 0.,
    /* pin[6][2] */ -1.,
    /* pin[7][0] */ 0.,
    /* pin[7][1] */ 0.,
    /* pin[7][2] */ -1.,
    /* pin[8][0] */ 0.,
    /* pin[8][1] */ 0.,
    /* pin[8][2] */ -1.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ -.0917,
    /* rk[0][1] */ -.0387,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ -.2438,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ .0033,
    /* rk[2][1] */ -.2294,
    /* rk[2][2] */ 0.,
    /* rk[3][0] */ 0.,
    /* rk[3][1] */ -.4027,
    /* rk[3][2] */ .0935,
    /* rk[4][0] */ .002,
    /* rk[4][1] */ .1715,
    /* rk[4][2] */ 0.,
    /* rk[5][0] */ 0.,
    /* rk[5][1] */ .1862,
    /* rk[5][2] */ 0.,
    /* rk[6][0] */ -.0459,
    /* rk[6][1] */ .0513,
    /* rk[6][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ -.0459,
    /* ri[1][1] */ .0513,
    /* ri[1][2] */ 0.,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ .1862,
    /* ri[2][2] */ 0.,
    /* ri[3][0] */ .002,
    /* ri[3][1] */ .1715,
    /* ri[3][2] */ 0.,
    /* ri[4][0] */ 0.,
    /* ri[4][1] */ -.4027,
    /* ri[4][2] */ -.0935,
    /* ri[5][0] */ .0033,
    /* ri[5][1] */ -.2294,
    /* ri[5][2] */ 0.,
    /* ri[6][0] */ 0.,
    /* ri[6][1] */ -.2438,
    /* ri[6][2] */ 0.,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,
    /* pres[5] */ 0.,
    /* pres[6] */ 0.,
    /* pres[7] */ 0.,
    /* pres[8] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,
    /* mmap[5] */ 5,
    /* mmap[6] */ 6,
    /* mmap[7] */ 7,
    /* mmap[8] */ 8,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 3,
    /* gravq[1] */ 3,
    /* gravq[2] */ 3,
    /* mkq[0] */ 0,
    /* mkq[1] */ 0,
    /* mkq[2] */ 0,
    /* mkq[3] */ 0,
    /* mkq[4] */ 0,
    /* mkq[5] */ 0,
    /* mkq[6] */ 0,
    /* ikq[0][0][0] */ 0,
    /* ikq[0][0][1] */ 0,
    /* ikq[0][0][2] */ 0,
    /* ikq[0][1][0] */ 0,
    /* ikq[0][1][1] */ 0,
    /* ikq[0][1][2] */ 0,
    /* ikq[0][2][0] */ 0,
    /* ikq[0][2][1] */ 0,
    /* ikq[0][2][2] */ 0,
    /* ikq[1][0][0] */ 0,
    /* ikq[1][0][1] */ 0,
    /* ikq[1][0][2] */ 0,
    /* ikq[1][1][0] */ 0,
    /* ikq[1][1][1] */ 0,
    /* ikq[1][1][2] */ 0,
    /* ikq[1][2][0] */ 0,
    /* ikq[1][2][1] */ 0,
    /* ikq[1][2][2] */ 0,
    /* ikq[2][0][0] */ 0,
    /* ikq[2][0][1] */ 0,
    /* ikq[2][0][2] */ 0,
    /* ikq[2][1][0] */ 0,
    /* ikq[2][1][1] */ 0,
    /* ikq[2][1][2] */ 0,
    /* ikq[2][2][0] */ 0,
    /* ikq[2][2][1] */ 0,
    /* ikq[2][2][2] */ 0,
    /* ikq[3][0][0] */ 0,
    /* ikq[3][0][1] */ 0,
    /* ikq[3][0][2] */ 0,
    /* ikq[3][1][0] */ 0,
    /* ikq[3][1][1] */ 0,
    /* ikq[3][1][2] */ 0,
    /* ikq[3][2][0] */ 0,
    /* ikq[3][2][1] */ 0,
    /* ikq[3][2][2] */ 0,
    /* ikq[4][0][0] */ 0,
    /* ikq[4][0][1] */ 0,
    /* ikq[4][0][2] */ 0,
    /* ikq[4][1][0] */ 0,
    /* ikq[4][1][1] */ 0,
    /* ikq[4][1][2] */ 0,
    /* ikq[4][2][0] */ 0,
    /* ikq[4][2][1] */ 0,
    /* ikq[4][2][2] */ 0,
    /* ikq[5][0][0] */ 0,
    /* ikq[5][0][1] */ 0,
    /* ikq[5][0][2] */ 0,
    /* ikq[5][1][0] */ 0,
    /* ikq[5][1][1] */ 0,
    /* ikq[5][1][2] */ 0,
    /* ikq[5][2][0] */ 0,
    /* ikq[5][2][1] */ 0,
    /* ikq[5][2][2] */ 0,
    /* ikq[6][0][0] */ 0,
    /* ikq[6][0][1] */ 0,
    /* ikq[6][0][2] */ 0,
    /* ikq[6][1][0] */ 0,
    /* ikq[6][1][1] */ 0,
    /* ikq[6][1][2] */ 0,
    /* ikq[6][2][0] */ 0,
    /* ikq[6][2][1] */ 0,
    /* ikq[6][2][2] */ 0,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* pinq[2][0] */ 0,
    /* pinq[2][1] */ 0,
    /* pinq[2][2] */ 0,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* pinq[6][0] */ 0,
    /* pinq[6][1] */ 0,
    /* pinq[6][2] */ 0,
    /* pinq[7][0] */ 0,
    /* pinq[7][1] */ 0,
    /* pinq[7][2] */ 0,
    /* pinq[8][0] */ 0,
    /* pinq[8][1] */ 0,
    /* pinq[8][2] */ 0,
    /* rkq[0][0] */ 0,
    /* rkq[0][1] */ 0,
    /* rkq[0][2] */ 0,
    /* rkq[1][0] */ 0,
    /* rkq[1][1] */ 0,
    /* rkq[1][2] */ 0,
    /* rkq[2][0] */ 0,
    /* rkq[2][1] */ 0,
    /* rkq[2][2] */ 0,
    /* rkq[3][0] */ 0,
    /* rkq[3][1] */ 0,
    /* rkq[3][2] */ 0,
    /* rkq[4][0] */ 0,
    /* rkq[4][1] */ 0,
    /* rkq[4][2] */ 0,
    /* rkq[5][0] */ 0,
    /* rkq[5][1] */ 0,
    /* rkq[5][2] */ 0,
    /* rkq[6][0] */ 0,
    /* rkq[6][1] */ 0,
    /* rkq[6][2] */ 0,
    /* riq[0][0] */ 0,
    /* riq[0][1] */ 0,
    /* riq[0][2] */ 0,
    /* riq[1][0] */ 0,
    /* riq[1][1] */ 0,
    /* riq[1][2] */ 0,
    /* riq[2][0] */ 0,
    /* riq[2][1] */ 0,
    /* riq[2][2] */ 0,
    /* riq[3][0] */ 0,
    /* riq[3][1] */ 0,
    /* riq[3][2] */ 0,
    /* riq[4][0] */ 0,
    /* riq[4][1] */ 0,
    /* riq[4][2] */ 0,
    /* riq[5][0] */ 0,
    /* riq[5][1] */ 0,
    /* riq[5][2] */ 0,
    /* riq[6][0] */ 0,
    /* riq[6][1] */ 0,
    /* riq[6][2] */ 0,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* presq[6] */ 0,
    /* presq[7] */ 0,
    /* presq[8] */ 0,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
sdgstate_t sdgstate;
sdglhs_t sdglhs;
sdgrhs_t sdgrhs;
sdgtemp_t sdgtemp;


sdinit()
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            sdseterr(7,25);
        }
    }
    for (k = 0; k < 7; k++) {
        if (mkq[k] == 1) {
            sdseterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                sdseterr(7,29);
            }
            if (riq[k][i] == 1) {
                sdseterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    sdseterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 9; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 9; i++) {
        for (j = i; j <= 8; j++) {
            for (k = 0; k < 3; k++) {
                Vpk[i][j][k] = 0.;
                Wpk[i][j][k] = 0.;
            }
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = 0.;
    rcom[0][1] = 0.;
    rcom[0][2] = 0.;
    rcom[1][0] = 0.;
    rcom[1][1] = 0.;
    rcom[1][2] = 0.;
    rcom[2][0] = 0.;
    rcom[2][1] = 0.;
    rcom[2][2] = 0.;
    rcom[3][0] = 0.;
    rcom[3][1] = 0.;
    rcom[3][2] = 0.;
    rcom[4][0] = 0.;
    rcom[4][1] = 0.;
    rcom[4][2] = 0.;
    rcom[5][0] = 0.;
    rcom[5][1] = 0.;
    rcom[5][2] = 0.;
    rcom[6][0] = 0.;
    rcom[6][1] = 0.;
    rcom[6][2] = 0.;

/* Compute mass properties-related constants */

    mtot = 71.02;
    sdserialno(&i);
    if (i != 70405) {
        sdseterr(7,41);
    }
    roustate = 1;
}

sdstate(timein,qin,uin)
    double timein,qin[9],uin[9];
{
/*
Compute kinematic information and store it in sdgstate.

Generated 18-Jun-2003 17:59:44 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 9; i++) {
            if (presq[i] == 1) {
                sdseterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 9; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 9; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 9; i++) {
        q[i] = qin[i];
    }
/*
Compute sines and cosines of q
*/
    s2 = sin(q[2]);
    c2 = cos(q[2]);
    s3 = sin(q[3]);
    c3 = cos(q[3]);
    s4 = sin(q[4]);
    c4 = cos(q[4]);
    s5 = sin(q[5]);
    c5 = cos(q[5]);
    s6 = sin(q[6]);
    c6 = cos(q[6]);
    s7 = sin(q[7]);
    c7 = cos(q[7]);
    s8 = sin(q[8]);
    c8 = cos(q[8]);
/*
Compute across-axis direction cosines Cik
*/
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
    gk[2][0] = ((grav[0]*c2)+(grav[1]*s2));
    gk[2][1] = ((grav[1]*c2)-(grav[0]*s2));
    gk[3][0] = ((gk[2][0]*c3)+(gk[2][1]*s3));
    gk[3][1] = ((gk[2][1]*c3)-(gk[2][0]*s3));
    gk[4][0] = ((gk[3][0]*c4)+(gk[3][1]*s4));
    gk[4][1] = ((gk[3][1]*c4)-(gk[3][0]*s4));
    gk[5][0] = ((gk[4][0]*c5)+(gk[4][1]*s5));
    gk[5][1] = ((gk[4][1]*c5)-(gk[4][0]*s5));
    gk[6][0] = ((gk[5][0]*c6)-(gk[5][1]*s6));
    gk[6][1] = ((gk[5][0]*s6)+(gk[5][1]*c6));
    gk[7][0] = ((gk[6][0]*c7)-(gk[6][1]*s7));
    gk[7][1] = ((gk[6][0]*s7)+(gk[6][1]*c7));
    gk[8][0] = ((gk[7][0]*c8)-(gk[7][1]*s8));
    gk[8][1] = ((gk[7][0]*s8)+(gk[7][1]*c8));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[3][0][0] = ((c2*c3)-(s2*s3));
    cnk[3][0][1] = -((s2*c3)+(s3*c2));
    cnk[3][1][0] = ((s2*c3)+(s3*c2));
    cnk[3][1][1] = ((c2*c3)-(s2*s3));
    cnk[4][0][0] = ((cnk[3][0][0]*c4)+(cnk[3][0][1]*s4));
    cnk[4][0][1] = ((cnk[3][0][1]*c4)-(cnk[3][0][0]*s4));
    cnk[4][1][0] = ((cnk[3][1][0]*c4)+(cnk[3][1][1]*s4));
    cnk[4][1][1] = ((cnk[3][1][1]*c4)-(cnk[3][1][0]*s4));
    cnk[5][0][0] = ((cnk[4][0][0]*c5)+(cnk[4][0][1]*s5));
    cnk[5][0][1] = ((cnk[4][0][1]*c5)-(cnk[4][0][0]*s5));
    cnk[5][1][0] = ((cnk[4][1][0]*c5)+(cnk[4][1][1]*s5));
    cnk[5][1][1] = ((cnk[4][1][1]*c5)-(cnk[4][1][0]*s5));
    cnk[6][0][0] = ((cnk[5][0][0]*c6)-(cnk[5][0][1]*s6));
    cnk[6][0][1] = ((cnk[5][0][0]*s6)+(cnk[5][0][1]*c6));
    cnk[6][1][0] = ((cnk[5][1][0]*c6)-(cnk[5][1][1]*s6));
    cnk[6][1][1] = ((cnk[5][1][0]*s6)+(cnk[5][1][1]*c6));
    cnk[7][0][0] = ((cnk[6][0][0]*c7)-(cnk[6][0][1]*s7));
    cnk[7][0][1] = ((cnk[6][0][0]*s7)+(cnk[6][0][1]*c7));
    cnk[7][1][0] = ((cnk[6][1][0]*c7)-(cnk[6][1][1]*s7));
    cnk[7][1][1] = ((cnk[6][1][0]*s7)+(cnk[6][1][1]*c7));
    cnk[8][0][0] = ((cnk[7][0][0]*c8)-(cnk[7][0][1]*s8));
    cnk[8][0][1] = ((cnk[7][0][0]*s8)+(cnk[7][0][1]*c8));
    cnk[8][1][0] = ((cnk[7][1][0]*c8)-(cnk[7][1][1]*s8));
    cnk[8][1][1] = ((cnk[7][1][0]*s8)+(cnk[7][1][1]*c8));
    cnb[0][0][0] = c2;
    cnb[0][0][1] = -s2;
    cnb[0][0][2] = 0.;
    cnb[0][1][0] = s2;
    cnb[0][1][1] = c2;
    cnb[0][1][2] = 0.;
    cnb[0][2][0] = 0.;
    cnb[0][2][1] = 0.;
    cnb[0][2][2] = 1.;
    cnb[1][0][0] = cnk[3][0][0];
    cnb[1][0][1] = cnk[3][0][1];
    cnb[1][0][2] = 0.;
    cnb[1][1][0] = cnk[3][1][0];
    cnb[1][1][1] = cnk[3][1][1];
    cnb[1][1][2] = 0.;
    cnb[1][2][0] = 0.;
    cnb[1][2][1] = 0.;
    cnb[1][2][2] = 1.;
    cnb[2][0][0] = cnk[4][0][0];
    cnb[2][0][1] = cnk[4][0][1];
    cnb[2][0][2] = 0.;
    cnb[2][1][0] = cnk[4][1][0];
    cnb[2][1][1] = cnk[4][1][1];
    cnb[2][1][2] = 0.;
    cnb[2][2][0] = 0.;
    cnb[2][2][1] = 0.;
    cnb[2][2][2] = 1.;
    cnb[3][0][0] = cnk[5][0][0];
    cnb[3][0][1] = cnk[5][0][1];
    cnb[3][0][2] = 0.;
    cnb[3][1][0] = cnk[5][1][0];
    cnb[3][1][1] = cnk[5][1][1];
    cnb[3][1][2] = 0.;
    cnb[3][2][0] = 0.;
    cnb[3][2][1] = 0.;
    cnb[3][2][2] = 1.;
    cnb[4][0][0] = cnk[6][0][0];
    cnb[4][0][1] = cnk[6][0][1];
    cnb[4][0][2] = 0.;
    cnb[4][1][0] = cnk[6][1][0];
    cnb[4][1][1] = cnk[6][1][1];
    cnb[4][1][2] = 0.;
    cnb[4][2][0] = 0.;
    cnb[4][2][1] = 0.;
    cnb[4][2][2] = 1.;
    cnb[5][0][0] = cnk[7][0][0];
    cnb[5][0][1] = cnk[7][0][1];
    cnb[5][0][2] = 0.;
    cnb[5][1][0] = cnk[7][1][0];
    cnb[5][1][1] = cnk[7][1][1];
    cnb[5][1][2] = 0.;
    cnb[5][2][0] = 0.;
    cnb[5][2][1] = 0.;
    cnb[5][2][2] = 1.;
    cnb[6][0][0] = cnk[8][0][0];
    cnb[6][0][1] = cnk[8][0][1];
    cnb[6][0][2] = 0.;
    cnb[6][1][0] = cnk[8][1][0];
    cnb[6][1][1] = cnk[8][1][1];
    cnb[6][1][2] = 0.;
    cnb[6][2][0] = 0.;
    cnb[6][2][1] = 0.;
    cnb[6][2][2] = 1.;
/*
Compute q-related auxiliary variables
*/
    rik[3][0] = ((.0513*s3)-(.0459*c3));
    rik[3][1] = (.2438+((.0459*s3)+(.0513*c3)));
    rik[4][0] = ((.1862*s4)-.0033);
    rik[4][1] = (.2294+(.1862*c4));
    rik[5][0] = ((.002*c5)+(.1715*s5));
    rik[5][1] = (.4027+((.1715*c5)-(.002*s5)));
    rik[6][0] = ((.4027*s6)-.002);
    rik[6][1] = -(.1715+(.4027*c6));
    rik[7][0] = ((.0033*c7)+(.2294*s7));
    rik[7][1] = (((.0033*s7)-(.2294*c7))-.1862);
    rik[8][0] = (.0459+(.2438*s8));
    rik[8][1] = -(.0513+(.2438*c8));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[2][0] = (q[0]+((.0917*c2)-(.0387*s2)));
    rnk[2][1] = (q[1]+((.0387*c2)+(.0917*s2)));
    rnk[3][0] = ((.2438*cnk[3][0][1])+(rnk[2][0]-((.0459*c2)+(.0513*s2))));
    rnk[3][1] = ((.2438*cnk[3][1][1])+(rnk[2][1]+((.0513*c2)-(.0459*s2))));
    rnk[4][0] = ((rnk[3][0]+(.1862*cnk[3][0][1]))+((.2294*cnk[4][0][1])-(.0033*
      cnk[4][0][0])));
    rnk[4][1] = ((rnk[3][1]+(.1862*cnk[3][1][1]))+((.2294*cnk[4][1][1])-(.0033*
      cnk[4][1][0])));
    rnk[5][0] = ((.4027*cnk[5][0][1])+(rnk[4][0]+((.002*cnk[4][0][0])+(.1715*
      cnk[4][0][1]))));
    rnk[5][1] = ((.4027*cnk[5][1][1])+(rnk[4][1]+((.002*cnk[4][1][0])+(.1715*
      cnk[4][1][1]))));
    rnk[6][0] = ((rnk[5][0]-(.4027*cnk[5][0][1]))-((.002*cnk[6][0][0])+(.1715*
      cnk[6][0][1])));
    rnk[6][1] = ((rnk[5][1]-(.4027*cnk[5][1][1]))-((.002*cnk[6][1][0])+(.1715*
      cnk[6][1][1])));
    rnk[7][0] = ((rnk[6][0]+((.0033*cnk[6][0][0])-(.2294*cnk[6][0][1])))-(.1862*
      cnk[7][0][1]));
    rnk[7][1] = ((rnk[6][1]+((.0033*cnk[6][1][0])-(.2294*cnk[6][1][1])))-(.1862*
      cnk[7][1][1]));
    rnk[8][0] = ((rnk[7][0]-(.2438*cnk[7][0][1]))+((.0459*cnk[8][0][0])-(.0513*
      cnk[8][0][1])));
    rnk[8][1] = ((rnk[7][1]-(.2438*cnk[7][1][1]))+((.0459*cnk[8][1][0])-(.0513*
      cnk[8][1][1])));
    rnb[0][0] = rnk[2][0];
    rnb[0][1] = rnk[2][1];
    rnb[0][2] = 0.;
    rnb[1][0] = rnk[3][0];
    rnb[1][1] = rnk[3][1];
    rnb[1][2] = 0.;
    rnb[2][0] = rnk[4][0];
    rnb[2][1] = rnk[4][1];
    rnb[2][2] = 0.;
    rnb[3][0] = rnk[5][0];
    rnb[3][1] = rnk[5][1];
    rnb[3][2] = -.0935;
    rnb[4][0] = rnk[6][0];
    rnb[4][1] = rnk[6][1];
    rnb[4][2] = -.187;
    rnb[5][0] = rnk[7][0];
    rnb[5][1] = rnk[7][1];
    rnb[5][2] = -.187;
    rnb[6][0] = rnk[8][0];
    rnb[6][1] = rnk[8][1];
    rnb[6][2] = -.187;
/*
Compute com (system mass center location in N)
*/
    com[0] = (.0140805406927626*((1.41*rnk[8][0])+((3.51*rnk[7][0])+((8.81*
      rnk[6][0])+((43.56*rnk[5][0])+((8.81*rnk[4][0])+((1.41*rnk[2][0])+(3.51*
      rnk[3][0]))))))));
    com[1] = (.0140805406927626*((1.41*rnk[8][1])+((3.51*rnk[7][1])+((8.81*
      rnk[6][1])+((43.56*rnk[5][1])+((8.81*rnk[4][1])+((1.41*rnk[2][1])+(3.51*
      rnk[3][1]))))))));
    com[2] = -.0935;
    skipqs: ;
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 9; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[3][2] = (u[2]+u[3]);
    wk[4][2] = (u[4]+wk[3][2]);
    wk[5][2] = (u[5]+wk[4][2]);
    wk[6][2] = (wk[5][2]-u[6]);
    wk[7][2] = (wk[6][2]-u[7]);
    wk[8][2] = (wk[7][2]-u[8]);
    wb[0][0] = 0.;
    wb[0][1] = 0.;
    wb[0][2] = u[2];
    wb[1][0] = 0.;
    wb[1][1] = 0.;
    wb[1][2] = wk[3][2];
    wb[2][0] = 0.;
    wb[2][1] = 0.;
    wb[2][2] = wk[4][2];
    wb[3][0] = 0.;
    wb[3][1] = 0.;
    wb[3][2] = wk[5][2];
    wb[4][0] = 0.;
    wb[4][1] = 0.;
    wb[4][2] = wk[6][2];
    wb[5][0] = 0.;
    wb[5][1] = 0.;
    wb[5][2] = wk[7][2];
    wb[6][0] = 0.;
    wb[6][1] = 0.;
    wb[6][2] = wk[8][2];
/*
Compute auxiliary variables involving wk
*/
/*
Compute temporaries for use in SDRHS
*/
    w2w2[0] = (u[2]*u[2]);
    w2w2[1] = (wk[3][2]*wk[3][2]);
    w2w2[2] = (wk[4][2]*wk[4][2]);
    w2w2[3] = (wk[5][2]*wk[5][2]);
    w2w2[4] = (wk[6][2]*wk[6][2]);
    w2w2[5] = (wk[7][2]*wk[7][2]);
    w2w2[6] = (wk[8][2]*wk[8][2]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[2][0] = (u[0]-((.0387*(u[2]*c2))+(.0917*(u[2]*s2))));
    vnk[2][1] = (u[1]+((.0917*(u[2]*c2))-(.0387*(u[2]*s2))));
    vnk[3][0] = ((vnk[2][0]+((.0459*(u[2]*s2))-(.0513*(u[2]*c2))))-(.2438*(
      cnk[3][0][0]*wk[3][2])));
    vnk[3][1] = ((vnk[2][1]-((.0459*(u[2]*c2))+(.0513*(u[2]*s2))))-(.2438*(
      cnk[3][1][0]*wk[3][2])));
    vnk[4][0] = ((vnk[3][0]-(.1862*(cnk[3][0][0]*wk[3][2])))-((.0033*(
      cnk[4][0][1]*wk[4][2]))+(.2294*(cnk[4][0][0]*wk[4][2]))));
    vnk[4][1] = ((vnk[3][1]-(.1862*(cnk[3][1][0]*wk[3][2])))-((.0033*(
      cnk[4][1][1]*wk[4][2]))+(.2294*(cnk[4][1][0]*wk[4][2]))));
    vnk[5][0] = ((vnk[4][0]+((.002*(cnk[4][0][1]*wk[4][2]))-(.1715*(cnk[4][0][0]
      *wk[4][2]))))-(.4027*(cnk[5][0][0]*wk[5][2])));
    vnk[5][1] = ((vnk[4][1]+((.002*(cnk[4][1][1]*wk[4][2]))-(.1715*(cnk[4][1][0]
      *wk[4][2]))))-(.4027*(cnk[5][1][0]*wk[5][2])));
    vnk[6][0] = ((vnk[5][0]+(.4027*(cnk[5][0][0]*wk[5][2])))+((.1715*(
      cnk[6][0][0]*wk[6][2]))-(.002*(cnk[6][0][1]*wk[6][2]))));
    vnk[6][1] = ((vnk[5][1]+(.4027*(cnk[5][1][0]*wk[5][2])))+((.1715*(
      cnk[6][1][0]*wk[6][2]))-(.002*(cnk[6][1][1]*wk[6][2]))));
    vnk[7][0] = ((.1862*(cnk[7][0][0]*wk[7][2]))+(vnk[6][0]+((.0033*(
      cnk[6][0][1]*wk[6][2]))+(.2294*(cnk[6][0][0]*wk[6][2])))));
    vnk[7][1] = ((.1862*(cnk[7][1][0]*wk[7][2]))+(vnk[6][1]+((.0033*(
      cnk[6][1][1]*wk[6][2]))+(.2294*(cnk[6][1][0]*wk[6][2])))));
    vnk[8][0] = ((vnk[7][0]+(.2438*(cnk[7][0][0]*wk[7][2])))+((.0459*(
      cnk[8][0][1]*wk[8][2]))+(.0513*(cnk[8][0][0]*wk[8][2]))));
    vnk[8][1] = ((vnk[7][1]+(.2438*(cnk[7][1][0]*wk[7][2])))+((.0459*(
      cnk[8][1][1]*wk[8][2]))+(.0513*(cnk[8][1][0]*wk[8][2]))));
    vnb[0][0] = vnk[2][0];
    vnb[0][1] = vnk[2][1];
    vnb[0][2] = 0.;
    vnb[1][0] = vnk[3][0];
    vnb[1][1] = vnk[3][1];
    vnb[1][2] = 0.;
    vnb[2][0] = vnk[4][0];
    vnb[2][1] = vnk[4][1];
    vnb[2][2] = 0.;
    vnb[3][0] = vnk[5][0];
    vnb[3][1] = vnk[5][1];
    vnb[3][2] = 0.;
    vnb[4][0] = vnk[6][0];
    vnb[4][1] = vnk[6][1];
    vnb[4][2] = 0.;
    vnb[5][0] = vnk[7][0];
    vnb[5][1] = vnk[7][1];
    vnb[5][2] = 0.;
    vnb[6][0] = vnk[8][0];
    vnb[6][1] = vnk[8][1];
    vnb[6][2] = 0.;
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = u[3];
    qdot[4] = u[4];
    qdot[5] = u[5];
    qdot[6] = u[6];
    qdot[7] = u[7];
    qdot[8] = u[8];
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 9; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 0.10 seconds CPU time,
 24576 additional bytes of memory.
 Equations contain  155 adds/subtracts/negates
                    237 multiplies
                      0 divides
                    298 assignments
*/
}

sdqdot(oqdot)
    double oqdot[9];
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 8; i++) {
        oqdot[i] = qdot[i];
    }
}

sdu2qdot(uin,oqdot)
    double uin[9],oqdot[9];
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 8; i++) {
        oqdot[i] = uin[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdpsstate(lqin)
    double lqin[1];
{

    if (roustate != 2) {
        sdseterr(9,23);
        return;
    }
}

sddovpk()
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[2][2][2] = 1.;
        Wpk[2][3][2] = 1.;
        Wpk[2][4][2] = 1.;
        Wpk[2][5][2] = 1.;
        Wpk[2][6][2] = 1.;
        Wpk[2][7][2] = 1.;
        Wpk[2][8][2] = 1.;
        Wpk[3][3][2] = 1.;
        Wpk[3][4][2] = 1.;
        Wpk[3][5][2] = 1.;
        Wpk[3][6][2] = 1.;
        Wpk[3][7][2] = 1.;
        Wpk[3][8][2] = 1.;
        Wpk[4][4][2] = 1.;
        Wpk[4][5][2] = 1.;
        Wpk[4][6][2] = 1.;
        Wpk[4][7][2] = 1.;
        Wpk[4][8][2] = 1.;
        Wpk[5][5][2] = 1.;
        Wpk[5][6][2] = 1.;
        Wpk[5][7][2] = 1.;
        Wpk[5][8][2] = 1.;
        Wpk[6][6][2] = -1.;
        Wpk[6][7][2] = -1.;
        Wpk[6][8][2] = -1.;
        Wpk[7][7][2] = -1.;
        Wpk[7][8][2] = -1.;
        Wpk[8][8][2] = -1.;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = 1.;
        Vpk[0][1][0] = 1.;
        Vpk[0][2][0] = c2;
        Vpk[0][2][1] = -s2;
        Vpk[0][3][0] = ((c2*c3)-(s2*s3));
        Vpk[0][3][1] = -((s2*c3)+(s3*c2));
        Vpk[0][4][0] = ((Vpk[0][3][0]*c4)+(Vpk[0][3][1]*s4));
        Vpk[0][4][1] = ((Vpk[0][3][1]*c4)-(Vpk[0][3][0]*s4));
        Vpk[0][5][0] = ((Vpk[0][4][0]*c5)+(Vpk[0][4][1]*s5));
        Vpk[0][5][1] = ((Vpk[0][4][1]*c5)-(Vpk[0][4][0]*s5));
        Vpk[0][6][0] = ((Vpk[0][5][0]*c6)-(Vpk[0][5][1]*s6));
        Vpk[0][6][1] = ((Vpk[0][5][0]*s6)+(Vpk[0][5][1]*c6));
        Vpk[0][7][0] = ((Vpk[0][6][0]*c7)-(Vpk[0][6][1]*s7));
        Vpk[0][7][1] = ((Vpk[0][6][0]*s7)+(Vpk[0][6][1]*c7));
        Vpk[0][8][0] = ((Vpk[0][7][0]*c8)-(Vpk[0][7][1]*s8));
        Vpk[0][8][1] = ((Vpk[0][7][0]*s8)+(Vpk[0][7][1]*c8));
        Vpk[1][1][1] = 1.;
        Vpk[1][2][0] = s2;
        Vpk[1][2][1] = c2;
        Vpk[1][3][0] = ((s2*c3)+(s3*c2));
        Vpk[1][3][1] = ((c2*c3)-(s2*s3));
        Vpk[1][4][0] = ((Vpk[1][3][0]*c4)+(Vpk[1][3][1]*s4));
        Vpk[1][4][1] = ((Vpk[1][3][1]*c4)-(Vpk[1][3][0]*s4));
        Vpk[1][5][0] = ((Vpk[1][4][0]*c5)+(Vpk[1][4][1]*s5));
        Vpk[1][5][1] = ((Vpk[1][4][1]*c5)-(Vpk[1][4][0]*s5));
        Vpk[1][6][0] = ((Vpk[1][5][0]*c6)-(Vpk[1][5][1]*s6));
        Vpk[1][6][1] = ((Vpk[1][5][0]*s6)+(Vpk[1][5][1]*c6));
        Vpk[1][7][0] = ((Vpk[1][6][0]*c7)-(Vpk[1][6][1]*s7));
        Vpk[1][7][1] = ((Vpk[1][6][0]*s7)+(Vpk[1][6][1]*c7));
        Vpk[1][8][0] = ((Vpk[1][7][0]*c8)-(Vpk[1][7][1]*s8));
        Vpk[1][8][1] = ((Vpk[1][7][0]*s8)+(Vpk[1][7][1]*c8));
        Vpk[2][2][0] = -.0387;
        Vpk[2][2][1] = .0917;
        Vpk[2][3][0] = (((.0458*s3)-(.09*c3))-.2438);
        Vpk[2][3][1] = ((.0458*c3)+(.09*s3));
        VWri[2][4][0] = (Vpk[2][3][0]-.1862);
        Vpk[2][4][0] = (((Vpk[2][3][1]*s4)+(VWri[2][4][0]*c4))-.2294);
        Vpk[2][4][1] = (((Vpk[2][3][1]*c4)-(VWri[2][4][0]*s4))-.0033);
        VWri[2][5][0] = (Vpk[2][4][0]-.1715);
        VWri[2][5][1] = (.002+Vpk[2][4][1]);
        Vpk[2][5][0] = (((VWri[2][5][0]*c5)+(VWri[2][5][1]*s5))-.4027);
        Vpk[2][5][1] = ((VWri[2][5][1]*c5)-(VWri[2][5][0]*s5));
        VWri[2][6][0] = (.4027+Vpk[2][5][0]);
        Vpk[2][6][0] = (.1715+((VWri[2][6][0]*c6)-(Vpk[2][5][1]*s6)));
        Vpk[2][6][1] = (((Vpk[2][5][1]*c6)+(VWri[2][6][0]*s6))-.002);
        VWri[2][7][0] = (.2294+Vpk[2][6][0]);
        VWri[2][7][1] = (.0033+Vpk[2][6][1]);
        Vpk[2][7][0] = (.1862+((VWri[2][7][0]*c7)-(VWri[2][7][1]*s7)));
        Vpk[2][7][1] = ((VWri[2][7][0]*s7)+(VWri[2][7][1]*c7));
        VWri[2][8][0] = (.2438+Vpk[2][7][0]);
        Vpk[2][8][0] = (.0513+((VWri[2][8][0]*c8)-(Vpk[2][7][1]*s8)));
        Vpk[2][8][1] = (.0459+((Vpk[2][7][1]*c8)+(VWri[2][8][0]*s8)));
        Vpk[3][3][0] = -.2438;
        Vpk[3][4][0] = -(.2294+(.43*c4));
        Vpk[3][4][1] = ((.43*s4)-.0033);
        VWri[3][5][0] = (Vpk[3][4][0]-.1715);
        VWri[3][5][1] = (.002+Vpk[3][4][1]);
        Vpk[3][5][0] = (((VWri[3][5][0]*c5)+(VWri[3][5][1]*s5))-.4027);
        Vpk[3][5][1] = ((VWri[3][5][1]*c5)-(VWri[3][5][0]*s5));
        VWri[3][6][0] = (.4027+Vpk[3][5][0]);
        Vpk[3][6][0] = (.1715+((VWri[3][6][0]*c6)-(Vpk[3][5][1]*s6)));
        Vpk[3][6][1] = (((Vpk[3][5][1]*c6)+(VWri[3][6][0]*s6))-.002);
        VWri[3][7][0] = (.2294+Vpk[3][6][0]);
        VWri[3][7][1] = (.0033+Vpk[3][6][1]);
        Vpk[3][7][0] = (.1862+((VWri[3][7][0]*c7)-(VWri[3][7][1]*s7)));
        Vpk[3][7][1] = ((VWri[3][7][0]*s7)+(VWri[3][7][1]*c7));
        VWri[3][8][0] = (.2438+Vpk[3][7][0]);
        Vpk[3][8][0] = (.0513+((VWri[3][8][0]*c8)-(Vpk[3][7][1]*s8)));
        Vpk[3][8][1] = (.0459+((Vpk[3][7][1]*c8)+(VWri[3][8][0]*s8)));
        Vpk[4][4][0] = -.2294;
        Vpk[4][4][1] = -.0033;
        Vpk[4][5][0] = -(.4027+((.0013*s5)+(.4009*c5)));
        Vpk[4][5][1] = ((.4009*s5)-(.0013*c5));
        VWri[4][6][0] = (.4027+Vpk[4][5][0]);
        Vpk[4][6][0] = (.1715+((VWri[4][6][0]*c6)-(Vpk[4][5][1]*s6)));
        Vpk[4][6][1] = (((Vpk[4][5][1]*c6)+(VWri[4][6][0]*s6))-.002);
        VWri[4][7][0] = (.2294+Vpk[4][6][0]);
        VWri[4][7][1] = (.0033+Vpk[4][6][1]);
        Vpk[4][7][0] = (.1862+((VWri[4][7][0]*c7)-(VWri[4][7][1]*s7)));
        Vpk[4][7][1] = ((VWri[4][7][0]*s7)+(VWri[4][7][1]*c7));
        VWri[4][8][0] = (.2438+Vpk[4][7][0]);
        Vpk[4][8][0] = (.0513+((VWri[4][8][0]*c8)-(Vpk[4][7][1]*s8)));
        Vpk[4][8][1] = (.0459+((Vpk[4][7][1]*c8)+(VWri[4][8][0]*s8)));
        Vpk[5][5][0] = -.4027;
        Vpk[5][6][0] = .1715;
        Vpk[5][6][1] = -.002;
        Vpk[5][7][0] = (.1862+((.4009*c7)-(.0013*s7)));
        Vpk[5][7][1] = ((.0013*c7)+(.4009*s7));
        VWri[5][8][0] = (.2438+Vpk[5][7][0]);
        Vpk[5][8][0] = (.0513+((VWri[5][8][0]*c8)-(Vpk[5][7][1]*s8)));
        Vpk[5][8][1] = (.0459+((Vpk[5][7][1]*c8)+(VWri[5][8][0]*s8)));
        Vpk[6][6][0] = -.1715;
        Vpk[6][6][1] = .002;
        Vpk[6][7][0] = (((.0013*s7)-(.4009*c7))-.1862);
        Vpk[6][7][1] = -((.0013*c7)+(.4009*s7));
        VWri[6][8][0] = (Vpk[6][7][0]-.2438);
        Vpk[6][8][0] = (((VWri[6][8][0]*c8)-(Vpk[6][7][1]*s8))-.0513);
        Vpk[6][8][1] = (((Vpk[6][7][1]*c8)+(VWri[6][8][0]*s8))-.0459);
        Vpk[7][7][0] = -.1862;
        Vpk[7][8][0] = -(.0513+(.43*c8));
        Vpk[7][8][1] = -(.0459+(.43*s8));
        Vpk[8][8][0] = -.0513;
        Vpk[8][8][1] = -.0459;
        vpkflg = 1;
    }
/*
 Used 0.07 seconds CPU time,
 16384 additional bytes of memory.
 Equations contain  117 adds/subtracts/negates
                    124 multiplies
                      0 divides
                    131 assignments
*/
}

sddoltau()
{

/*
Compute effect of loop hinge torques
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

sddoiner()
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[2][0] = -(.0917*(u[2]*u[2]));
        Atk[2][1] = -(.0387*(u[2]*u[2]));
        AiOiWi[3][0] = (Atk[2][0]+(.0459*(u[2]*u[2])));
        AiOiWi[3][1] = (Atk[2][1]-(.0513*(u[2]*u[2])));
        Atk[3][0] = ((AiOiWi[3][0]*c3)+(AiOiWi[3][1]*s3));
        Atk[3][1] = (((AiOiWi[3][1]*c3)-(AiOiWi[3][0]*s3))-(.2438*(wk[3][2]*
          wk[3][2])));
        AiOiWi[4][1] = (Atk[3][1]-(.1862*(wk[3][2]*wk[3][2])));
        Atk[4][0] = ((.0033*(wk[4][2]*wk[4][2]))+((AiOiWi[4][1]*s4)+(Atk[3][0]*
          c4)));
        Atk[4][1] = (((AiOiWi[4][1]*c4)-(Atk[3][0]*s4))-(.2294*(wk[4][2]*
          wk[4][2])));
        AiOiWi[5][0] = (Atk[4][0]-(.002*(wk[4][2]*wk[4][2])));
        AiOiWi[5][1] = (Atk[4][1]-(.1715*(wk[4][2]*wk[4][2])));
        Atk[5][0] = ((AiOiWi[5][0]*c5)+(AiOiWi[5][1]*s5));
        Atk[5][1] = (((AiOiWi[5][1]*c5)-(AiOiWi[5][0]*s5))-(.4027*(wk[5][2]*
          wk[5][2])));
        AiOiWi[6][1] = (Atk[5][1]+(.4027*(wk[5][2]*wk[5][2])));
        Atk[6][0] = ((.002*(wk[6][2]*wk[6][2]))+((Atk[5][0]*c6)-(AiOiWi[6][1]*s6
          )));
        Atk[6][1] = ((.1715*(wk[6][2]*wk[6][2]))+((AiOiWi[6][1]*c6)+(Atk[5][0]*
          s6)));
        AiOiWi[7][0] = (Atk[6][0]-(.0033*(wk[6][2]*wk[6][2])));
        AiOiWi[7][1] = (Atk[6][1]+(.2294*(wk[6][2]*wk[6][2])));
        Atk[7][0] = ((AiOiWi[7][0]*c7)-(AiOiWi[7][1]*s7));
        Atk[7][1] = ((.1862*(wk[7][2]*wk[7][2]))+((AiOiWi[7][0]*s7)+(
          AiOiWi[7][1]*c7)));
        AiOiWi[8][1] = (Atk[7][1]+(.2438*(wk[7][2]*wk[7][2])));
        Atk[8][0] = (((Atk[7][0]*c8)-(AiOiWi[8][1]*s8))-(.0459*(wk[8][2]*
          wk[8][2])));
        Atk[8][1] = ((.0513*(wk[8][2]*wk[8][2]))+((AiOiWi[8][1]*c8)+(Atk[7][0]*
          s8)));
        inerflg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   32 adds/subtracts/negates
                     64 multiplies
                      0 divides
                     23 assignments
*/
}

sddofs0()
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        sddoltau();
        sddoiner();
/*
Compute Fstar (forces)
*/
        Fstar[2][0] = ((1.41*(Atk[2][0]-gk[2][0]))-ufk[0][0]);
        Fstar[2][1] = ((1.41*(Atk[2][1]-gk[2][1]))-ufk[0][1]);
        Fstar[2][2] = -(ufk[0][2]+(1.41*grav[2]));
        Fstar[3][0] = ((3.51*(Atk[3][0]-gk[3][0]))-ufk[1][0]);
        Fstar[3][1] = ((3.51*(Atk[3][1]-gk[3][1]))-ufk[1][1]);
        Fstar[3][2] = -(ufk[1][2]+(3.51*grav[2]));
        Fstar[4][0] = ((8.81*(Atk[4][0]-gk[4][0]))-ufk[2][0]);
        Fstar[4][1] = ((8.81*(Atk[4][1]-gk[4][1]))-ufk[2][1]);
        Fstar[4][2] = -(ufk[2][2]+(8.81*grav[2]));
        Fstar[5][0] = ((43.56*(Atk[5][0]-gk[5][0]))-ufk[3][0]);
        Fstar[5][1] = ((43.56*(Atk[5][1]-gk[5][1]))-ufk[3][1]);
        Fstar[5][2] = -(ufk[3][2]+(43.56*grav[2]));
        Fstar[6][0] = ((8.81*(Atk[6][0]-gk[6][0]))-ufk[4][0]);
        Fstar[6][1] = ((8.81*(Atk[6][1]-gk[6][1]))-ufk[4][1]);
        Fstar[6][2] = -(ufk[4][2]+(8.81*grav[2]));
        Fstar[7][0] = ((3.51*(Atk[7][0]-gk[7][0]))-ufk[5][0]);
        Fstar[7][1] = ((3.51*(Atk[7][1]-gk[7][1]))-ufk[5][1]);
        Fstar[7][2] = -(ufk[5][2]+(3.51*grav[2]));
        Fstar[8][0] = ((1.41*(Atk[8][0]-gk[8][0]))-ufk[6][0]);
        Fstar[8][1] = ((1.41*(Atk[8][1]-gk[8][1]))-ufk[6][1]);
        Fstar[8][2] = -(ufk[6][2]+(1.41*grav[2]));
/*
Compute Tstar (torques)
*/
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        fs0[0] = (utau[0]-(((Fstar[8][0]*Vpk[0][8][0])+(Fstar[8][1]*Vpk[0][8][1]
          ))+(((Fstar[7][0]*Vpk[0][7][0])+(Fstar[7][1]*Vpk[0][7][1]))+(((
          Fstar[6][0]*Vpk[0][6][0])+(Fstar[6][1]*Vpk[0][6][1]))+(((Fstar[5][0]*
          Vpk[0][5][0])+(Fstar[5][1]*Vpk[0][5][1]))+(((Fstar[4][0]*Vpk[0][4][0])
          +(Fstar[4][1]*Vpk[0][4][1]))+(((Fstar[2][0]*c2)-(Fstar[2][1]*s2))+((
          Fstar[3][0]*Vpk[0][3][0])+(Fstar[3][1]*Vpk[0][3][1])))))))));
        fs0[1] = (utau[1]-(((Fstar[8][0]*Vpk[1][8][0])+(Fstar[8][1]*Vpk[1][8][1]
          ))+(((Fstar[7][0]*Vpk[1][7][0])+(Fstar[7][1]*Vpk[1][7][1]))+(((
          Fstar[6][0]*Vpk[1][6][0])+(Fstar[6][1]*Vpk[1][6][1]))+(((Fstar[5][0]*
          Vpk[1][5][0])+(Fstar[5][1]*Vpk[1][5][1]))+(((Fstar[4][0]*Vpk[1][4][0])
          +(Fstar[4][1]*Vpk[1][4][1]))+(((Fstar[2][0]*s2)+(Fstar[2][1]*c2))+((
          Fstar[3][0]*Vpk[1][3][0])+(Fstar[3][1]*Vpk[1][3][1])))))))));
        temp[0] = ((((Fstar[7][0]*Vpk[2][7][0])+(Fstar[7][1]*Vpk[2][7][1]))-
          utk[5][2])+((((Fstar[6][0]*Vpk[2][6][0])+(Fstar[6][1]*Vpk[2][6][1]))-
          utk[4][2])+((((Fstar[5][0]*Vpk[2][5][0])+(Fstar[5][1]*Vpk[2][5][1]))-
          utk[3][2])+((((Fstar[4][0]*Vpk[2][4][0])+(Fstar[4][1]*Vpk[2][4][1]))-
          utk[2][2])+((((.0917*Fstar[2][1])-(.0387*Fstar[2][0]))-utk[0][2])+(((
          Fstar[3][0]*Vpk[2][3][0])+(Fstar[3][1]*Vpk[2][3][1]))-utk[1][2]))))));
        fs0[2] = (utau[2]-((((Fstar[8][0]*Vpk[2][8][0])+(Fstar[8][1]*
          Vpk[2][8][1]))-utk[6][2])+temp[0]));
        fs0[3] = (utau[3]-((((Fstar[8][0]*Vpk[3][8][0])+(Fstar[8][1]*
          Vpk[3][8][1]))-utk[6][2])+((((Fstar[7][0]*Vpk[3][7][0])+(Fstar[7][1]*
          Vpk[3][7][1]))-utk[5][2])+((((Fstar[6][0]*Vpk[3][6][0])+(Fstar[6][1]*
          Vpk[3][6][1]))-utk[4][2])+((((Fstar[5][0]*Vpk[3][5][0])+(Fstar[5][1]*
          Vpk[3][5][1]))-utk[3][2])+((((Fstar[4][0]*Vpk[3][4][0])+(Fstar[4][1]*
          Vpk[3][4][1]))-utk[2][2])-(utk[1][2]+(.2438*Fstar[3][0]))))))));
        fs0[4] = (utau[4]-((((Fstar[8][0]*Vpk[4][8][0])+(Fstar[8][1]*
          Vpk[4][8][1]))-utk[6][2])+((((Fstar[7][0]*Vpk[4][7][0])+(Fstar[7][1]*
          Vpk[4][7][1]))-utk[5][2])+((((Fstar[6][0]*Vpk[4][6][0])+(Fstar[6][1]*
          Vpk[4][6][1]))-utk[4][2])+((((Fstar[5][0]*Vpk[4][5][0])+(Fstar[5][1]*
          Vpk[4][5][1]))-utk[3][2])-(utk[2][2]+((.0033*Fstar[4][1])+(.2294*
          Fstar[4][0]))))))));
        fs0[5] = (utau[5]-((((Fstar[8][0]*Vpk[5][8][0])+(Fstar[8][1]*
          Vpk[5][8][1]))-utk[6][2])+((((Fstar[7][0]*Vpk[5][7][0])+(Fstar[7][1]*
          Vpk[5][7][1]))-utk[5][2])+((((.1715*Fstar[6][0])-(.002*Fstar[6][1]))-
          utk[4][2])-(utk[3][2]+(.4027*Fstar[5][0]))))));
        fs0[6] = (utau[6]-((utk[6][2]+((Fstar[8][0]*Vpk[6][8][0])+(Fstar[8][1]*
          Vpk[6][8][1])))+((utk[4][2]+((.002*Fstar[6][1])-(.1715*Fstar[6][0])))+
          (utk[5][2]+((Fstar[7][0]*Vpk[6][7][0])+(Fstar[7][1]*Vpk[6][7][1]))))))
          ;
        fs0[7] = (utau[7]-((utk[5][2]-(.1862*Fstar[7][0]))+(utk[6][2]+((
          Fstar[8][0]*Vpk[7][8][0])+(Fstar[8][1]*Vpk[7][8][1])))));
        fs0[8] = (utau[8]-(utk[6][2]-((.0459*Fstar[8][1])+(.0513*Fstar[8][0]))))
          ;
        fs0flg = 1;
    }
/*
 Used 0.03 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain  151 adds/subtracts/negates
                    102 multiplies
                      0 divides
                     31 assignments
*/
}

sddomm(routine)
    int routine;
{
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        sddovpk();
        temp[0] = ((3.51*((Vpk[0][7][0]*Vpk[0][7][0])+(Vpk[0][7][1]*Vpk[0][7][1]
          )))+((8.81*((Vpk[0][6][0]*Vpk[0][6][0])+(Vpk[0][6][1]*Vpk[0][6][1])))+
          ((43.56*((Vpk[0][5][0]*Vpk[0][5][0])+(Vpk[0][5][1]*Vpk[0][5][1])))+((
          3.51*((Vpk[0][3][0]*Vpk[0][3][0])+(Vpk[0][3][1]*Vpk[0][3][1])))+(8.81*
          ((Vpk[0][4][0]*Vpk[0][4][0])+(Vpk[0][4][1]*Vpk[0][4][1])))))));
        mm[0][0] = (1.41+((1.41*((Vpk[0][8][0]*Vpk[0][8][0])+(Vpk[0][8][1]*
          Vpk[0][8][1])))+temp[0]));
        temp[0] = ((3.51*((Vpk[0][7][0]*Vpk[1][7][0])+(Vpk[0][7][1]*Vpk[1][7][1]
          )))+((8.81*((Vpk[0][6][0]*Vpk[1][6][0])+(Vpk[0][6][1]*Vpk[1][6][1])))+
          ((43.56*((Vpk[0][5][0]*Vpk[1][5][0])+(Vpk[0][5][1]*Vpk[1][5][1])))+((
          3.51*((Vpk[0][3][0]*Vpk[1][3][0])+(Vpk[0][3][1]*Vpk[1][3][1])))+(8.81*
          ((Vpk[0][4][0]*Vpk[1][4][0])+(Vpk[0][4][1]*Vpk[1][4][1])))))));
        mm[0][1] = ((1.41*((Vpk[0][8][0]*Vpk[1][8][0])+(Vpk[0][8][1]*
          Vpk[1][8][1])))+temp[0]);
        temp[0] = ((3.51*((Vpk[0][7][0]*Vpk[2][7][0])+(Vpk[0][7][1]*Vpk[2][7][1]
          )))+((8.81*((Vpk[0][6][0]*Vpk[2][6][0])+(Vpk[0][6][1]*Vpk[2][6][1])))+
          ((43.56*((Vpk[0][5][0]*Vpk[2][5][0])+(Vpk[0][5][1]*Vpk[2][5][1])))+((
          8.81*((Vpk[0][4][0]*Vpk[2][4][0])+(Vpk[0][4][1]*Vpk[2][4][1])))+((3.51
          *((Vpk[0][3][0]*Vpk[2][3][0])+(Vpk[0][3][1]*Vpk[2][3][1])))-(1.41*((
          .0387*c2)+(.0917*s2))))))));
        mm[0][2] = ((1.41*((Vpk[0][8][0]*Vpk[2][8][0])+(Vpk[0][8][1]*
          Vpk[2][8][1])))+temp[0]);
        mm[0][3] = ((1.41*((Vpk[0][8][0]*Vpk[3][8][0])+(Vpk[0][8][1]*
          Vpk[3][8][1])))+((3.51*((Vpk[0][7][0]*Vpk[3][7][0])+(Vpk[0][7][1]*
          Vpk[3][7][1])))+((8.81*((Vpk[0][6][0]*Vpk[3][6][0])+(Vpk[0][6][1]*
          Vpk[3][6][1])))+((43.56*((Vpk[0][5][0]*Vpk[3][5][0])+(Vpk[0][5][1]*
          Vpk[3][5][1])))+((8.81*((Vpk[0][4][0]*Vpk[3][4][0])+(Vpk[0][4][1]*
          Vpk[3][4][1])))-(.855738*Vpk[0][3][0]))))));
        mm[0][4] = ((1.41*((Vpk[0][8][0]*Vpk[4][8][0])+(Vpk[0][8][1]*
          Vpk[4][8][1])))+((3.51*((Vpk[0][7][0]*Vpk[4][7][0])+(Vpk[0][7][1]*
          Vpk[4][7][1])))+((8.81*((Vpk[0][6][0]*Vpk[4][6][0])+(Vpk[0][6][1]*
          Vpk[4][6][1])))+((43.56*((Vpk[0][5][0]*Vpk[4][5][0])+(Vpk[0][5][1]*
          Vpk[4][5][1])))-(8.81*((.0033*Vpk[0][4][1])+(.2294*Vpk[0][4][0])))))))
          ;
        mm[0][5] = ((1.41*((Vpk[0][8][0]*Vpk[5][8][0])+(Vpk[0][8][1]*
          Vpk[5][8][1])))+((3.51*((Vpk[0][7][0]*Vpk[5][7][0])+(Vpk[0][7][1]*
          Vpk[5][7][1])))+((8.81*((.1715*Vpk[0][6][0])-(.002*Vpk[0][6][1])))-(
          17.541612*Vpk[0][5][0]))));
        mm[0][6] = ((1.41*((Vpk[0][8][0]*Vpk[6][8][0])+(Vpk[0][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[0][7][0]*Vpk[6][7][0])+(Vpk[0][7][1]*
          Vpk[6][7][1])))+(8.81*((.002*Vpk[0][6][1])-(.1715*Vpk[0][6][0])))));
        mm[0][7] = ((1.41*((Vpk[0][8][0]*Vpk[7][8][0])+(Vpk[0][8][1]*
          Vpk[7][8][1])))-(.653562*Vpk[0][7][0]));
        mm[0][8] = -(1.41*((.0459*Vpk[0][8][1])+(.0513*Vpk[0][8][0])));
        temp[0] = ((3.51*((Vpk[1][7][0]*Vpk[1][7][0])+(Vpk[1][7][1]*Vpk[1][7][1]
          )))+((8.81*((Vpk[1][6][0]*Vpk[1][6][0])+(Vpk[1][6][1]*Vpk[1][6][1])))+
          ((43.56*((Vpk[1][5][0]*Vpk[1][5][0])+(Vpk[1][5][1]*Vpk[1][5][1])))+((
          3.51*((Vpk[1][3][0]*Vpk[1][3][0])+(Vpk[1][3][1]*Vpk[1][3][1])))+(8.81*
          ((Vpk[1][4][0]*Vpk[1][4][0])+(Vpk[1][4][1]*Vpk[1][4][1])))))));
        mm[1][1] = (1.41+((1.41*((Vpk[1][8][0]*Vpk[1][8][0])+(Vpk[1][8][1]*
          Vpk[1][8][1])))+temp[0]));
        temp[0] = ((3.51*((Vpk[1][7][0]*Vpk[2][7][0])+(Vpk[1][7][1]*Vpk[2][7][1]
          )))+((8.81*((Vpk[1][6][0]*Vpk[2][6][0])+(Vpk[1][6][1]*Vpk[2][6][1])))+
          ((43.56*((Vpk[1][5][0]*Vpk[2][5][0])+(Vpk[1][5][1]*Vpk[2][5][1])))+((
          8.81*((Vpk[1][4][0]*Vpk[2][4][0])+(Vpk[1][4][1]*Vpk[2][4][1])))+((1.41
          *((.0917*c2)-(.0387*s2)))+(3.51*((Vpk[1][3][0]*Vpk[2][3][0])+(
          Vpk[1][3][1]*Vpk[2][3][1]))))))));
        mm[1][2] = ((1.41*((Vpk[1][8][0]*Vpk[2][8][0])+(Vpk[1][8][1]*
          Vpk[2][8][1])))+temp[0]);
        mm[1][3] = ((1.41*((Vpk[1][8][0]*Vpk[3][8][0])+(Vpk[1][8][1]*
          Vpk[3][8][1])))+((3.51*((Vpk[1][7][0]*Vpk[3][7][0])+(Vpk[1][7][1]*
          Vpk[3][7][1])))+((8.81*((Vpk[1][6][0]*Vpk[3][6][0])+(Vpk[1][6][1]*
          Vpk[3][6][1])))+((43.56*((Vpk[1][5][0]*Vpk[3][5][0])+(Vpk[1][5][1]*
          Vpk[3][5][1])))+((8.81*((Vpk[1][4][0]*Vpk[3][4][0])+(Vpk[1][4][1]*
          Vpk[3][4][1])))-(.855738*Vpk[1][3][0]))))));
        mm[1][4] = ((1.41*((Vpk[1][8][0]*Vpk[4][8][0])+(Vpk[1][8][1]*
          Vpk[4][8][1])))+((3.51*((Vpk[1][7][0]*Vpk[4][7][0])+(Vpk[1][7][1]*
          Vpk[4][7][1])))+((8.81*((Vpk[1][6][0]*Vpk[4][6][0])+(Vpk[1][6][1]*
          Vpk[4][6][1])))+((43.56*((Vpk[1][5][0]*Vpk[4][5][0])+(Vpk[1][5][1]*
          Vpk[4][5][1])))-(8.81*((.0033*Vpk[1][4][1])+(.2294*Vpk[1][4][0])))))))
          ;
        mm[1][5] = ((1.41*((Vpk[1][8][0]*Vpk[5][8][0])+(Vpk[1][8][1]*
          Vpk[5][8][1])))+((3.51*((Vpk[1][7][0]*Vpk[5][7][0])+(Vpk[1][7][1]*
          Vpk[5][7][1])))+((8.81*((.1715*Vpk[1][6][0])-(.002*Vpk[1][6][1])))-(
          17.541612*Vpk[1][5][0]))));
        mm[1][6] = ((1.41*((Vpk[1][8][0]*Vpk[6][8][0])+(Vpk[1][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[1][7][0]*Vpk[6][7][0])+(Vpk[1][7][1]*
          Vpk[6][7][1])))+(8.81*((.002*Vpk[1][6][1])-(.1715*Vpk[1][6][0])))));
        mm[1][7] = ((1.41*((Vpk[1][8][0]*Vpk[7][8][0])+(Vpk[1][8][1]*
          Vpk[7][8][1])))-(.653562*Vpk[1][7][0]));
        mm[1][8] = -(1.41*((.0459*Vpk[1][8][1])+(.0513*Vpk[1][8][0])));
        temp[0] = ((3.51*((Vpk[2][7][0]*Vpk[2][7][0])+(Vpk[2][7][1]*Vpk[2][7][1]
          )))+((8.81*((Vpk[2][6][0]*Vpk[2][6][0])+(Vpk[2][6][1]*Vpk[2][6][1])))+
          ((43.56*((Vpk[2][5][0]*Vpk[2][5][0])+(Vpk[2][5][1]*Vpk[2][5][1])))+((
          3.51*((Vpk[2][3][0]*Vpk[2][3][0])+(Vpk[2][3][1]*Vpk[2][3][1])))+(8.81*
          ((Vpk[2][4][0]*Vpk[2][4][0])+(Vpk[2][4][1]*Vpk[2][4][1])))))));
        mm[2][2] = (3.4608682778+((1.41*((Vpk[2][8][0]*Vpk[2][8][0])+(
          Vpk[2][8][1]*Vpk[2][8][1])))+temp[0]));
        mm[2][3] = (3.4401+((1.41*((Vpk[2][8][0]*Vpk[3][8][0])+(Vpk[2][8][1]*
          Vpk[3][8][1])))+((3.51*((Vpk[2][7][0]*Vpk[3][7][0])+(Vpk[2][7][1]*
          Vpk[3][7][1])))+((8.81*((Vpk[2][6][0]*Vpk[3][6][0])+(Vpk[2][6][1]*
          Vpk[3][6][1])))+((43.56*((Vpk[2][5][0]*Vpk[3][5][0])+(Vpk[2][5][1]*
          Vpk[3][5][1])))+((8.81*((Vpk[2][4][0]*Vpk[3][4][0])+(Vpk[2][4][1]*
          Vpk[3][4][1])))-(.855738*Vpk[2][3][0])))))));
        mm[2][4] = (3.3917+((1.41*((Vpk[2][8][0]*Vpk[4][8][0])+(Vpk[2][8][1]*
          Vpk[4][8][1])))+((3.51*((Vpk[2][7][0]*Vpk[4][7][0])+(Vpk[2][7][1]*
          Vpk[4][7][1])))+((8.81*((Vpk[2][6][0]*Vpk[4][6][0])+(Vpk[2][6][1]*
          Vpk[4][6][1])))+((43.56*((Vpk[2][5][0]*Vpk[4][5][0])+(Vpk[2][5][1]*
          Vpk[4][5][1])))-(8.81*((.0033*Vpk[2][4][1])+(.2294*Vpk[2][4][0])))))))
          );
        mm[2][5] = (3.258+((1.41*((Vpk[2][8][0]*Vpk[5][8][0])+(Vpk[2][8][1]*
          Vpk[5][8][1])))+((3.51*((Vpk[2][7][0]*Vpk[5][7][0])+(Vpk[2][7][1]*
          Vpk[5][7][1])))+((8.81*((.1715*Vpk[2][6][0])-(.002*Vpk[2][6][1])))-(
          17.541612*Vpk[2][5][0])))));
        mm[2][6] = (((1.41*((Vpk[2][8][0]*Vpk[6][8][0])+(Vpk[2][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[2][7][0]*Vpk[6][7][0])+(Vpk[2][7][1]*
          Vpk[6][7][1])))+(8.81*((.002*Vpk[2][6][1])-(.1715*Vpk[2][6][0])))))-
          .1889);
        mm[2][7] = (((1.41*((Vpk[2][8][0]*Vpk[7][8][0])+(Vpk[2][8][1]*
          Vpk[7][8][1])))-.0068)-(.0484+(.653562*Vpk[2][7][0])));
        mm[2][8] = -(.0068+(1.41*((.0459*Vpk[2][8][1])+(.0513*Vpk[2][8][0]))));
        mm[3][3] = (3.6487289244+((1.41*((Vpk[3][8][0]*Vpk[3][8][0])+(
          Vpk[3][8][1]*Vpk[3][8][1])))+((3.51*((Vpk[3][7][0]*Vpk[3][7][0])+(
          Vpk[3][7][1]*Vpk[3][7][1])))+((8.81*((Vpk[3][6][0]*Vpk[3][6][0])+(
          Vpk[3][6][1]*Vpk[3][6][1])))+((8.81*((Vpk[3][4][0]*Vpk[3][4][0])+(
          Vpk[3][4][1]*Vpk[3][4][1])))+(43.56*((Vpk[3][5][0]*Vpk[3][5][0])+(
          Vpk[3][5][1]*Vpk[3][5][1]))))))));
        mm[3][4] = (3.3917+((1.41*((Vpk[3][8][0]*Vpk[4][8][0])+(Vpk[3][8][1]*
          Vpk[4][8][1])))+((3.51*((Vpk[3][7][0]*Vpk[4][7][0])+(Vpk[3][7][1]*
          Vpk[4][7][1])))+((8.81*((Vpk[3][6][0]*Vpk[4][6][0])+(Vpk[3][6][1]*
          Vpk[4][6][1])))+((43.56*((Vpk[3][5][0]*Vpk[4][5][0])+(Vpk[3][5][1]*
          Vpk[4][5][1])))-(8.81*((.0033*Vpk[3][4][1])+(.2294*Vpk[3][4][0])))))))
          );
        mm[3][5] = (3.258+((1.41*((Vpk[3][8][0]*Vpk[5][8][0])+(Vpk[3][8][1]*
          Vpk[5][8][1])))+((3.51*((Vpk[3][7][0]*Vpk[5][7][0])+(Vpk[3][7][1]*
          Vpk[5][7][1])))+((8.81*((.1715*Vpk[3][6][0])-(.002*Vpk[3][6][1])))-(
          17.541612*Vpk[3][5][0])))));
        mm[3][6] = (((1.41*((Vpk[3][8][0]*Vpk[6][8][0])+(Vpk[3][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[3][7][0]*Vpk[6][7][0])+(Vpk[3][7][1]*
          Vpk[6][7][1])))+(8.81*((.002*Vpk[3][6][1])-(.1715*Vpk[3][6][0])))))-
          .1889);
        mm[3][7] = (((1.41*((Vpk[3][8][0]*Vpk[7][8][0])+(Vpk[3][8][1]*
          Vpk[7][8][1])))-.0068)-(.0484+(.653562*Vpk[3][7][0])));
        mm[3][8] = -(.0068+(1.41*((.0459*Vpk[3][8][1])+(.0513*Vpk[3][8][0]))));
        mm[4][4] = (3.8554165525+((1.41*((Vpk[4][8][0]*Vpk[4][8][0])+(
          Vpk[4][8][1]*Vpk[4][8][1])))+((3.51*((Vpk[4][7][0]*Vpk[4][7][0])+(
          Vpk[4][7][1]*Vpk[4][7][1])))+((8.81*((Vpk[4][6][0]*Vpk[4][6][0])+(
          Vpk[4][6][1]*Vpk[4][6][1])))+(43.56*((Vpk[4][5][0]*Vpk[4][5][0])+(
          Vpk[4][5][1]*Vpk[4][5][1])))))));
        mm[4][5] = (3.258+((1.41*((Vpk[4][8][0]*Vpk[5][8][0])+(Vpk[4][8][1]*
          Vpk[5][8][1])))+((3.51*((Vpk[4][7][0]*Vpk[5][7][0])+(Vpk[4][7][1]*
          Vpk[5][7][1])))+((8.81*((.1715*Vpk[4][6][0])-(.002*Vpk[4][6][1])))-(
          17.541612*Vpk[4][5][0])))));
        mm[4][6] = (((1.41*((Vpk[4][8][0]*Vpk[6][8][0])+(Vpk[4][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[4][7][0]*Vpk[6][7][0])+(Vpk[4][7][1]*
          Vpk[6][7][1])))+(8.81*((.002*Vpk[4][6][1])-(.1715*Vpk[4][6][0])))))-
          .1889);
        mm[4][7] = (((1.41*((Vpk[4][8][0]*Vpk[7][8][0])+(Vpk[4][8][1]*
          Vpk[7][8][1])))-.0068)-(.0484+(.653562*Vpk[4][7][0])));
        mm[4][8] = -(.0068+(1.41*((.0459*Vpk[4][8][1])+(.0513*Vpk[4][8][0]))));
        mm[5][5] = (10.5811643149+((1.41*((Vpk[5][8][0]*Vpk[5][8][0])+(
          Vpk[5][8][1]*Vpk[5][8][1])))+(3.51*((Vpk[5][7][0]*Vpk[5][7][0])+(
          Vpk[5][7][1]*Vpk[5][7][1])))));
        mm[5][6] = (((1.41*((Vpk[5][8][0]*Vpk[6][8][0])+(Vpk[5][8][1]*
          Vpk[6][8][1])))+((3.51*((Vpk[5][7][0]*Vpk[6][7][0])+(Vpk[5][7][1]*
          Vpk[6][7][1])))-.0484))-.3996571625);
        mm[5][7] = (((1.41*((Vpk[5][8][0]*Vpk[7][8][0])+(Vpk[5][8][1]*
          Vpk[7][8][1])))-.0068)-(.0484+(.653562*Vpk[5][7][0])));
        mm[5][8] = -(.0068+(1.41*((.0459*Vpk[5][8][1])+(.0513*Vpk[5][8][0]))));
        mm[6][6] = (.4480571625+((1.41*((Vpk[6][8][0]*Vpk[6][8][0])+(
          Vpk[6][8][1]*Vpk[6][8][1])))+(3.51*((Vpk[6][7][0]*Vpk[6][7][0])+(
          Vpk[6][7][1]*Vpk[6][7][1])))));
        mm[6][7] = (.0552+((1.41*((Vpk[6][8][0]*Vpk[7][8][0])+(Vpk[6][8][1]*
          Vpk[7][8][1])))-(.653562*Vpk[6][7][0])));
        mm[6][8] = (.0068-(1.41*((.0459*Vpk[6][8][1])+(.0513*Vpk[6][8][0]))));
        mm[7][7] = (.1768932444+(1.41*((Vpk[7][8][0]*Vpk[7][8][0])+(Vpk[7][8][1]
          *Vpk[7][8][1]))));
        mm[7][8] = (.0068-(1.41*((.0459*Vpk[7][8][1])+(.0513*Vpk[7][8][0]))));
        mm[8][8] = .013481285;
/*
Check for singular mass matrix
*/
        for (i = 0; i < 9; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        mmflg = 1;
    }
/*
 Used 0.08 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  279 adds/subtracts/negates
                    417 multiplies
                      0 divides
                     51 assignments
*/
}

sddommldu(routine)
    int routine;
{
    int i;

    if (mmlduflg == 0) {
        sddomm(routine);
/*
Numerically decompose the mass matrix
*/
        sdldudcomp(9,9,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 9; i++) {
            if (mdi[i] <= 1e-13) {
                sdseterr(routine,47);
            }
        }
        mmlduflg = 1;
    }
}

sdlhs(routine)
    int routine;
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    sddommldu(routine);
    sddofs0();
}

sdmassmat(mmat)
    double mmat[9][9];
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 9; i++) {
        for (j = i; j <= 8; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

sdfrcmat(fmat)
    double fmat[9];
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 9; i++) {
        fmat[i] = fs0[i];
    }
}

sdmfrc(imult)
    double imult[1];
{

}

sdequivht(tau)
    double tau[9];
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[9][3],tstareq[9][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[2][0] = -(ufk[0][0]+(1.41*gk[2][0]));
    fstareq[2][1] = -(ufk[0][1]+(1.41*gk[2][1]));
    fstareq[2][2] = -(ufk[0][2]+(1.41*grav[2]));
    fstareq[3][0] = -(ufk[1][0]+(3.51*gk[3][0]));
    fstareq[3][1] = -(ufk[1][1]+(3.51*gk[3][1]));
    fstareq[3][2] = -(ufk[1][2]+(3.51*grav[2]));
    fstareq[4][0] = -(ufk[2][0]+(8.81*gk[4][0]));
    fstareq[4][1] = -(ufk[2][1]+(8.81*gk[4][1]));
    fstareq[4][2] = -(ufk[2][2]+(8.81*grav[2]));
    fstareq[5][0] = -(ufk[3][0]+(43.56*gk[5][0]));
    fstareq[5][1] = -(ufk[3][1]+(43.56*gk[5][1]));
    fstareq[5][2] = -(ufk[3][2]+(43.56*grav[2]));
    fstareq[6][0] = -(ufk[4][0]+(8.81*gk[6][0]));
    fstareq[6][1] = -(ufk[4][1]+(8.81*gk[6][1]));
    fstareq[6][2] = -(ufk[4][2]+(8.81*grav[2]));
    fstareq[7][0] = -(ufk[5][0]+(3.51*gk[7][0]));
    fstareq[7][1] = -(ufk[5][1]+(3.51*gk[7][1]));
    fstareq[7][2] = -(ufk[5][2]+(3.51*grav[2]));
    fstareq[8][0] = -(ufk[6][0]+(1.41*gk[8][0]));
    fstareq[8][1] = -(ufk[6][1]+(1.41*gk[8][1]));
    fstareq[8][2] = -(ufk[6][2]+(1.41*grav[2]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    tau[0] = (utau[0]-(((fstareq[8][0]*Vpk[0][8][0])+(fstareq[8][1]*Vpk[0][8][1]
      ))+(((fstareq[7][0]*Vpk[0][7][0])+(fstareq[7][1]*Vpk[0][7][1]))+(((
      fstareq[6][0]*Vpk[0][6][0])+(fstareq[6][1]*Vpk[0][6][1]))+(((fstareq[5][0]
      *Vpk[0][5][0])+(fstareq[5][1]*Vpk[0][5][1]))+(((fstareq[4][0]*Vpk[0][4][0]
      )+(fstareq[4][1]*Vpk[0][4][1]))+(((fstareq[2][0]*c2)-(fstareq[2][1]*s2))+(
      (fstareq[3][0]*Vpk[0][3][0])+(fstareq[3][1]*Vpk[0][3][1])))))))));
    tau[1] = (utau[1]-(((fstareq[8][0]*Vpk[1][8][0])+(fstareq[8][1]*Vpk[1][8][1]
      ))+(((fstareq[7][0]*Vpk[1][7][0])+(fstareq[7][1]*Vpk[1][7][1]))+(((
      fstareq[6][0]*Vpk[1][6][0])+(fstareq[6][1]*Vpk[1][6][1]))+(((fstareq[5][0]
      *Vpk[1][5][0])+(fstareq[5][1]*Vpk[1][5][1]))+(((fstareq[4][0]*Vpk[1][4][0]
      )+(fstareq[4][1]*Vpk[1][4][1]))+(((fstareq[2][0]*s2)+(fstareq[2][1]*c2))+(
      (fstareq[3][0]*Vpk[1][3][0])+(fstareq[3][1]*Vpk[1][3][1])))))))));
    temp[0] = ((((fstareq[7][0]*Vpk[2][7][0])+(fstareq[7][1]*Vpk[2][7][1]))-
      utk[5][2])+((((fstareq[6][0]*Vpk[2][6][0])+(fstareq[6][1]*Vpk[2][6][1]))-
      utk[4][2])+((((fstareq[5][0]*Vpk[2][5][0])+(fstareq[5][1]*Vpk[2][5][1]))-
      utk[3][2])+((((fstareq[4][0]*Vpk[2][4][0])+(fstareq[4][1]*Vpk[2][4][1]))-
      utk[2][2])+((((.0917*fstareq[2][1])-(.0387*fstareq[2][0]))-utk[0][2])+(((
      fstareq[3][0]*Vpk[2][3][0])+(fstareq[3][1]*Vpk[2][3][1]))-utk[1][2]))))));
    tau[2] = (utau[2]-((((fstareq[8][0]*Vpk[2][8][0])+(fstareq[8][1]*
      Vpk[2][8][1]))-utk[6][2])+temp[0]));
    tau[3] = (utau[3]-((((fstareq[8][0]*Vpk[3][8][0])+(fstareq[8][1]*
      Vpk[3][8][1]))-utk[6][2])+((((fstareq[7][0]*Vpk[3][7][0])+(fstareq[7][1]*
      Vpk[3][7][1]))-utk[5][2])+((((fstareq[6][0]*Vpk[3][6][0])+(fstareq[6][1]*
      Vpk[3][6][1]))-utk[4][2])+((((fstareq[5][0]*Vpk[3][5][0])+(fstareq[5][1]*
      Vpk[3][5][1]))-utk[3][2])+((((fstareq[4][0]*Vpk[3][4][0])+(fstareq[4][1]*
      Vpk[3][4][1]))-utk[2][2])-(utk[1][2]+(.2438*fstareq[3][0]))))))));
    tau[4] = (utau[4]-((((fstareq[8][0]*Vpk[4][8][0])+(fstareq[8][1]*
      Vpk[4][8][1]))-utk[6][2])+((((fstareq[7][0]*Vpk[4][7][0])+(fstareq[7][1]*
      Vpk[4][7][1]))-utk[5][2])+((((fstareq[6][0]*Vpk[4][6][0])+(fstareq[6][1]*
      Vpk[4][6][1]))-utk[4][2])+((((fstareq[5][0]*Vpk[4][5][0])+(fstareq[5][1]*
      Vpk[4][5][1]))-utk[3][2])-(utk[2][2]+((.0033*fstareq[4][1])+(.2294*
      fstareq[4][0]))))))));
    tau[5] = (utau[5]-((((fstareq[8][0]*Vpk[5][8][0])+(fstareq[8][1]*
      Vpk[5][8][1]))-utk[6][2])+((((fstareq[7][0]*Vpk[5][7][0])+(fstareq[7][1]*
      Vpk[5][7][1]))-utk[5][2])+((((.1715*fstareq[6][0])-(.002*fstareq[6][1]))-
      utk[4][2])-(utk[3][2]+(.4027*fstareq[5][0]))))));
    tau[6] = (utau[6]-((utk[6][2]+((fstareq[8][0]*Vpk[6][8][0])+(fstareq[8][1]*
      Vpk[6][8][1])))+((utk[4][2]+((.002*fstareq[6][1])-(.1715*fstareq[6][0])))+
      (utk[5][2]+((fstareq[7][0]*Vpk[6][7][0])+(fstareq[7][1]*Vpk[6][7][1]))))))
      ;
    tau[7] = (utau[7]-((utk[5][2]-(.1862*fstareq[7][0]))+(utk[6][2]+((
      fstareq[8][0]*Vpk[7][8][0])+(fstareq[8][1]*Vpk[7][8][1])))));
    tau[8] = (utau[8]-(utk[6][2]-((.0459*fstareq[8][1])+(.0513*fstareq[8][0]))))
      ;
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.03 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain  151 adds/subtracts/negates
                    102 multiplies
                      0 divides
                     31 assignments
*/
}

sdfulltrq(udotin,multin,trqout)
    double udotin[9],multin[1],trqout[9];
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[9][3],tstarr[9][3],Otkr[9][3],Atir[9][3],Atkr[9][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[3][2] = (udotin[2]+udotin[3]);
    Otkr[4][2] = (Otkr[3][2]+udotin[4]);
    Otkr[5][2] = (Otkr[4][2]+udotin[5]);
    Otkr[6][2] = (Otkr[5][2]-udotin[6]);
    Otkr[7][2] = (Otkr[6][2]-udotin[7]);
    Otkr[8][2] = (Otkr[7][2]-udotin[8]);
    Atkr[2][0] = (((udotin[0]*c2)+(udotin[1]*s2))-((.0387*udotin[2])+(.0917*(
      u[2]*u[2]))));
    Atkr[2][1] = (((.0917*udotin[2])-(.0387*(u[2]*u[2])))+((udotin[1]*c2)-(
      udotin[0]*s2)));
    Atir[3][0] = (Atkr[2][0]+((.0459*(u[2]*u[2]))-(.0513*udotin[2])));
    Atir[3][1] = (Atkr[2][1]-((.0459*udotin[2])+(.0513*(u[2]*u[2]))));
    Atkr[3][0] = (((Atir[3][0]*c3)+(Atir[3][1]*s3))-(.2438*Otkr[3][2]));
    Atkr[3][1] = (((Atir[3][1]*c3)-(Atir[3][0]*s3))-(.2438*(wk[3][2]*wk[3][2])))
      ;
    Atir[4][0] = (Atkr[3][0]-(.1862*Otkr[3][2]));
    Atir[4][1] = (Atkr[3][1]-(.1862*(wk[3][2]*wk[3][2])));
    Atkr[4][0] = (((.0033*(wk[4][2]*wk[4][2]))-(.2294*Otkr[4][2]))+((Atir[4][0]*
      c4)+(Atir[4][1]*s4)));
    Atkr[4][1] = (((Atir[4][1]*c4)-(Atir[4][0]*s4))-((.0033*Otkr[4][2])+(.2294*(
      wk[4][2]*wk[4][2]))));
    Atir[5][0] = (Atkr[4][0]-((.002*(wk[4][2]*wk[4][2]))+(.1715*Otkr[4][2])));
    Atir[5][1] = (Atkr[4][1]+((.002*Otkr[4][2])-(.1715*(wk[4][2]*wk[4][2]))));
    Atkr[5][0] = (((Atir[5][0]*c5)+(Atir[5][1]*s5))-(.4027*Otkr[5][2]));
    Atkr[5][1] = (((Atir[5][1]*c5)-(Atir[5][0]*s5))-(.4027*(wk[5][2]*wk[5][2])))
      ;
    Atir[6][0] = (Atkr[5][0]+(.4027*Otkr[5][2]));
    Atir[6][1] = (Atkr[5][1]+(.4027*(wk[5][2]*wk[5][2])));
    Atkr[6][0] = (((.002*(wk[6][2]*wk[6][2]))+(.1715*Otkr[6][2]))+((Atir[6][0]*
      c6)-(Atir[6][1]*s6)));
    Atkr[6][1] = (((.1715*(wk[6][2]*wk[6][2]))-(.002*Otkr[6][2]))+((Atir[6][0]*
      s6)+(Atir[6][1]*c6)));
    Atir[7][0] = (Atkr[6][0]+((.2294*Otkr[6][2])-(.0033*(wk[6][2]*wk[6][2]))));
    Atir[7][1] = (Atkr[6][1]+((.0033*Otkr[6][2])+(.2294*(wk[6][2]*wk[6][2]))));
    Atkr[7][0] = ((.1862*Otkr[7][2])+((Atir[7][0]*c7)-(Atir[7][1]*s7)));
    Atkr[7][1] = ((.1862*(wk[7][2]*wk[7][2]))+((Atir[7][0]*s7)+(Atir[7][1]*c7)))
      ;
    Atir[8][0] = (Atkr[7][0]+(.2438*Otkr[7][2]));
    Atir[8][1] = (Atkr[7][1]+(.2438*(wk[7][2]*wk[7][2])));
    Atkr[8][0] = (((.0513*Otkr[8][2])-(.0459*(wk[8][2]*wk[8][2])))+((Atir[8][0]*
      c8)-(Atir[8][1]*s8)));
    Atkr[8][1] = (((.0459*Otkr[8][2])+(.0513*(wk[8][2]*wk[8][2])))+((Atir[8][0]*
      s8)+(Atir[8][1]*c8)));
/*
Accumulate all forces and torques
*/
    fstarr[2][0] = (ufk[0][0]+(1.41*(gk[2][0]-Atkr[2][0])));
    fstarr[2][1] = (ufk[0][1]+(1.41*(gk[2][1]-Atkr[2][1])));
    fstarr[2][2] = (ufk[0][2]+(1.41*grav[2]));
    fstarr[3][0] = (ufk[1][0]+(3.51*(gk[3][0]-Atkr[3][0])));
    fstarr[3][1] = (ufk[1][1]+(3.51*(gk[3][1]-Atkr[3][1])));
    fstarr[3][2] = (ufk[1][2]+(3.51*grav[2]));
    fstarr[4][0] = (ufk[2][0]+(8.81*(gk[4][0]-Atkr[4][0])));
    fstarr[4][1] = (ufk[2][1]+(8.81*(gk[4][1]-Atkr[4][1])));
    fstarr[4][2] = (ufk[2][2]+(8.81*grav[2]));
    fstarr[5][0] = (ufk[3][0]+(43.56*(gk[5][0]-Atkr[5][0])));
    fstarr[5][1] = (ufk[3][1]+(43.56*(gk[5][1]-Atkr[5][1])));
    fstarr[5][2] = (ufk[3][2]+(43.56*grav[2]));
    fstarr[6][0] = (ufk[4][0]+(8.81*(gk[6][0]-Atkr[6][0])));
    fstarr[6][1] = (ufk[4][1]+(8.81*(gk[6][1]-Atkr[6][1])));
    fstarr[6][2] = (ufk[4][2]+(8.81*grav[2]));
    fstarr[7][0] = (ufk[5][0]+(3.51*(gk[7][0]-Atkr[7][0])));
    fstarr[7][1] = (ufk[5][1]+(3.51*(gk[7][1]-Atkr[7][1])));
    fstarr[7][2] = (ufk[5][2]+(3.51*grav[2]));
    fstarr[8][0] = (ufk[6][0]+(1.41*(gk[8][0]-Atkr[8][0])));
    fstarr[8][1] = (ufk[6][1]+(1.41*(gk[8][1]-Atkr[8][1])));
    fstarr[8][2] = (ufk[6][2]+(1.41*grav[2]));
    tstarr[2][2] = (utk[0][2]-(.0068*udotin[2]));
    tstarr[3][2] = (utk[1][2]-(.0484*Otkr[3][2]));
    tstarr[4][2] = (utk[2][2]-(.1337*Otkr[4][2]));
    tstarr[5][2] = (utk[3][2]-(3.0691*Otkr[5][2]));
    tstarr[6][2] = (utk[4][2]-(.1337*Otkr[6][2]));
    tstarr[7][2] = (utk[5][2]-(.0484*Otkr[7][2]));
    tstarr[8][2] = (utk[6][2]-(.0068*Otkr[8][2]));
/*
Now calculate the torques
*/
    sddovpk();
    trqout[0] = -(utau[0]+(((fstarr[8][0]*Vpk[0][8][0])+(fstarr[8][1]*
      Vpk[0][8][1]))+(((fstarr[7][0]*Vpk[0][7][0])+(fstarr[7][1]*Vpk[0][7][1]))+
      (((fstarr[6][0]*Vpk[0][6][0])+(fstarr[6][1]*Vpk[0][6][1]))+(((fstarr[5][0]
      *Vpk[0][5][0])+(fstarr[5][1]*Vpk[0][5][1]))+(((fstarr[4][0]*Vpk[0][4][0])+
      (fstarr[4][1]*Vpk[0][4][1]))+(((fstarr[2][0]*c2)-(fstarr[2][1]*s2))+((
      fstarr[3][0]*Vpk[0][3][0])+(fstarr[3][1]*Vpk[0][3][1])))))))));
    trqout[1] = -(utau[1]+(((fstarr[8][0]*Vpk[1][8][0])+(fstarr[8][1]*
      Vpk[1][8][1]))+(((fstarr[7][0]*Vpk[1][7][0])+(fstarr[7][1]*Vpk[1][7][1]))+
      (((fstarr[6][0]*Vpk[1][6][0])+(fstarr[6][1]*Vpk[1][6][1]))+(((fstarr[5][0]
      *Vpk[1][5][0])+(fstarr[5][1]*Vpk[1][5][1]))+(((fstarr[4][0]*Vpk[1][4][0])+
      (fstarr[4][1]*Vpk[1][4][1]))+(((fstarr[2][0]*s2)+(fstarr[2][1]*c2))+((
      fstarr[3][0]*Vpk[1][3][0])+(fstarr[3][1]*Vpk[1][3][1])))))))));
    temp[0] = ((tstarr[7][2]+((fstarr[7][0]*Vpk[2][7][0])+(fstarr[7][1]*
      Vpk[2][7][1])))+((tstarr[6][2]+((fstarr[6][0]*Vpk[2][6][0])+(fstarr[6][1]*
      Vpk[2][6][1])))+((tstarr[5][2]+((fstarr[5][0]*Vpk[2][5][0])+(fstarr[5][1]*
      Vpk[2][5][1])))+((tstarr[4][2]+((fstarr[4][0]*Vpk[2][4][0])+(fstarr[4][1]*
      Vpk[2][4][1])))+((tstarr[2][2]+((.0917*fstarr[2][1])-(.0387*fstarr[2][0]))
      )+(tstarr[3][2]+((fstarr[3][0]*Vpk[2][3][0])+(fstarr[3][1]*Vpk[2][3][1])))
      )))));
    trqout[2] = -(utau[2]+((tstarr[8][2]+((fstarr[8][0]*Vpk[2][8][0])+(
      fstarr[8][1]*Vpk[2][8][1])))+temp[0]));
    trqout[3] = -(utau[3]+((tstarr[8][2]+((fstarr[8][0]*Vpk[3][8][0])+(
      fstarr[8][1]*Vpk[3][8][1])))+((tstarr[7][2]+((fstarr[7][0]*Vpk[3][7][0])+(
      fstarr[7][1]*Vpk[3][7][1])))+((tstarr[6][2]+((fstarr[6][0]*Vpk[3][6][0])+(
      fstarr[6][1]*Vpk[3][6][1])))+((tstarr[5][2]+((fstarr[5][0]*Vpk[3][5][0])+(
      fstarr[5][1]*Vpk[3][5][1])))+((tstarr[3][2]-(.2438*fstarr[3][0]))+(
      tstarr[4][2]+((fstarr[4][0]*Vpk[3][4][0])+(fstarr[4][1]*Vpk[3][4][1]))))))
      )));
    trqout[4] = -(utau[4]+((tstarr[8][2]+((fstarr[8][0]*Vpk[4][8][0])+(
      fstarr[8][1]*Vpk[4][8][1])))+((tstarr[7][2]+((fstarr[7][0]*Vpk[4][7][0])+(
      fstarr[7][1]*Vpk[4][7][1])))+((tstarr[6][2]+((fstarr[6][0]*Vpk[4][6][0])+(
      fstarr[6][1]*Vpk[4][6][1])))+((tstarr[4][2]-((.0033*fstarr[4][1])+(.2294*
      fstarr[4][0])))+(tstarr[5][2]+((fstarr[5][0]*Vpk[4][5][0])+(fstarr[5][1]*
      Vpk[4][5][1]))))))));
    trqout[5] = -(utau[5]+((tstarr[8][2]+((fstarr[8][0]*Vpk[5][8][0])+(
      fstarr[8][1]*Vpk[5][8][1])))+((tstarr[7][2]+((fstarr[7][0]*Vpk[5][7][0])+(
      fstarr[7][1]*Vpk[5][7][1])))+((tstarr[5][2]-(.4027*fstarr[5][0]))+(
      tstarr[6][2]+((.1715*fstarr[6][0])-(.002*fstarr[6][1])))))));
    trqout[6] = -(utau[6]+((((fstarr[8][0]*Vpk[6][8][0])+(fstarr[8][1]*
      Vpk[6][8][1]))-tstarr[8][2])+((((.002*fstarr[6][1])-(.1715*fstarr[6][0]))-
      tstarr[6][2])+(((fstarr[7][0]*Vpk[6][7][0])+(fstarr[7][1]*Vpk[6][7][1]))-
      tstarr[7][2]))));
    trqout[7] = -(utau[7]+((((fstarr[8][0]*Vpk[7][8][0])+(fstarr[8][1]*
      Vpk[7][8][1]))-tstarr[8][2])-(tstarr[7][2]+(.1862*fstarr[7][0]))));
    trqout[8] = ((tstarr[8][2]+((.0459*fstarr[8][1])+(.0513*fstarr[8][0])))-
      utau[8]);
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.06 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain  219 adds/subtracts/negates
                    197 multiplies
                      0 divides
                     70 assignments
*/
}

sdcomptrq(udotin,trqout)
    double udotin[9],trqout[9];
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    double multin[1];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    sdfulltrq(udotin,multin,trqout);
}

sdmulttrq(multin,trqout)
    double multin[1],trqout[9];
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    for (i = 0; i < 9; i++) {
        trqout[i] = 0.;
    }
}

sdfs0()
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
    fs[5] = fs0[5];
    fs[6] = fs0[6];
    fs[7] = fs0[7];
    fs[8] = fs0[8];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdfsmult()
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 9; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdfsfull()
{

/*
Compute Fs (including all forces)
*/
    sdfsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdfsgenmult()
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 9; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdfsgenfull()
{

/*
Compute Fs (incl generic mult & other forces)
*/
    sdfsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdrhs()
{
/*
Generated 18-Jun-2003 17:59:45 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = utau[0];
    tauc[1] = utau[1];
    tauc[2] = utau[2];
    tauc[3] = utau[3];
    tauc[4] = utau[4];
    tauc[5] = utau[5];
    tauc[6] = utau[6];
    tauc[7] = utau[7];
    tauc[8] = utau[8];
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[3][2] = (udot[2]+udot[3]);
    Onkb[4][2] = (Onkb[3][2]+udot[4]);
    Onkb[5][2] = (Onkb[4][2]+udot[5]);
    Onkb[6][2] = (Onkb[5][2]-udot[6]);
    Onkb[7][2] = (Onkb[6][2]-udot[7]);
    Onkb[8][2] = (Onkb[7][2]-udot[8]);
    onb[0][0] = 0.;
    onb[0][1] = 0.;
    onb[0][2] = udot[2];
    onb[1][0] = 0.;
    onb[1][1] = 0.;
    onb[1][2] = Onkb[3][2];
    onb[2][0] = 0.;
    onb[2][1] = 0.;
    onb[2][2] = Onkb[4][2];
    onb[3][0] = 0.;
    onb[3][1] = 0.;
    onb[3][2] = Onkb[5][2];
    onb[4][0] = 0.;
    onb[4][1] = 0.;
    onb[4][2] = Onkb[6][2];
    onb[5][0] = 0.;
    onb[5][1] = 0.;
    onb[5][2] = Onkb[7][2];
    onb[6][0] = 0.;
    onb[6][1] = 0.;
    onb[6][2] = Onkb[8][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = -w2w2[0];
    dyad[0][0][1] = -udot[2];
    dyad[0][0][2] = 0.;
    dyad[0][1][0] = udot[2];
    dyad[0][1][1] = -w2w2[0];
    dyad[0][1][2] = 0.;
    dyad[0][2][0] = 0.;
    dyad[0][2][1] = 0.;
    dyad[0][2][2] = 0.;
    dyad[1][0][0] = -w2w2[1];
    dyad[1][0][1] = -Onkb[3][2];
    dyad[1][0][2] = 0.;
    dyad[1][1][0] = Onkb[3][2];
    dyad[1][1][1] = -w2w2[1];
    dyad[1][1][2] = 0.;
    dyad[1][2][0] = 0.;
    dyad[1][2][1] = 0.;
    dyad[1][2][2] = 0.;
    dyad[2][0][0] = -w2w2[2];
    dyad[2][0][1] = -Onkb[4][2];
    dyad[2][0][2] = 0.;
    dyad[2][1][0] = Onkb[4][2];
    dyad[2][1][1] = -w2w2[2];
    dyad[2][1][2] = 0.;
    dyad[2][2][0] = 0.;
    dyad[2][2][1] = 0.;
    dyad[2][2][2] = 0.;
    dyad[3][0][0] = -w2w2[3];
    dyad[3][0][1] = -Onkb[5][2];
    dyad[3][0][2] = 0.;
    dyad[3][1][0] = Onkb[5][2];
    dyad[3][1][1] = -w2w2[3];
    dyad[3][1][2] = 0.;
    dyad[3][2][0] = 0.;
    dyad[3][2][1] = 0.;
    dyad[3][2][2] = 0.;
    dyad[4][0][0] = -w2w2[4];
    dyad[4][0][1] = -Onkb[6][2];
    dyad[4][0][2] = 0.;
    dyad[4][1][0] = Onkb[6][2];
    dyad[4][1][1] = -w2w2[4];
    dyad[4][1][2] = 0.;
    dyad[4][2][0] = 0.;
    dyad[4][2][1] = 0.;
    dyad[4][2][2] = 0.;
    dyad[5][0][0] = -w2w2[5];
    dyad[5][0][1] = -Onkb[7][2];
    dyad[5][0][2] = 0.;
    dyad[5][1][0] = Onkb[7][2];
    dyad[5][1][1] = -w2w2[5];
    dyad[5][1][2] = 0.;
    dyad[5][2][0] = 0.;
    dyad[5][2][1] = 0.;
    dyad[5][2][2] = 0.;
    dyad[6][0][0] = -w2w2[6];
    dyad[6][0][1] = -Onkb[8][2];
    dyad[6][0][2] = 0.;
    dyad[6][1][0] = Onkb[8][2];
    dyad[6][1][1] = -w2w2[6];
    dyad[6][1][2] = 0.;
    dyad[6][2][0] = 0.;
    dyad[6][2][1] = 0.;
    dyad[6][2][2] = 0.;
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[2][0] = (((udot[0]*c2)+(udot[1]*s2))-(.0387*udot[2]));
    Ankb[2][1] = ((.0917*udot[2])+((udot[1]*c2)-(udot[0]*s2)));
    AOnkri[3][0] = (Ankb[2][0]-(.0513*udot[2]));
    AOnkri[3][1] = (Ankb[2][1]-(.0459*udot[2]));
    Ankb[3][0] = (((AOnkri[3][0]*c3)+(AOnkri[3][1]*s3))-(.2438*Onkb[3][2]));
    Ankb[3][1] = ((AOnkri[3][1]*c3)-(AOnkri[3][0]*s3));
    AOnkri[4][0] = (Ankb[3][0]-(.1862*Onkb[3][2]));
    Ankb[4][0] = (((Ankb[3][1]*s4)+(AOnkri[4][0]*c4))-(.2294*Onkb[4][2]));
    Ankb[4][1] = (((Ankb[3][1]*c4)-(AOnkri[4][0]*s4))-(.0033*Onkb[4][2]));
    AOnkri[5][0] = (Ankb[4][0]-(.1715*Onkb[4][2]));
    AOnkri[5][1] = (Ankb[4][1]+(.002*Onkb[4][2]));
    Ankb[5][0] = (((AOnkri[5][0]*c5)+(AOnkri[5][1]*s5))-(.4027*Onkb[5][2]));
    Ankb[5][1] = ((AOnkri[5][1]*c5)-(AOnkri[5][0]*s5));
    AOnkri[6][0] = (Ankb[5][0]+(.4027*Onkb[5][2]));
    Ankb[6][0] = ((.1715*Onkb[6][2])+((AOnkri[6][0]*c6)-(Ankb[5][1]*s6)));
    Ankb[6][1] = (((Ankb[5][1]*c6)+(AOnkri[6][0]*s6))-(.002*Onkb[6][2]));
    AOnkri[7][0] = (Ankb[6][0]+(.2294*Onkb[6][2]));
    AOnkri[7][1] = (Ankb[6][1]+(.0033*Onkb[6][2]));
    Ankb[7][0] = ((.1862*Onkb[7][2])+((AOnkri[7][0]*c7)-(AOnkri[7][1]*s7)));
    Ankb[7][1] = ((AOnkri[7][0]*s7)+(AOnkri[7][1]*c7));
    AOnkri[8][0] = (Ankb[7][0]+(.2438*Onkb[7][2]));
    Ankb[8][0] = ((.0513*Onkb[8][2])+((AOnkri[8][0]*c8)-(Ankb[7][1]*s8)));
    Ankb[8][1] = ((.0459*Onkb[8][2])+((Ankb[7][1]*c8)+(AOnkri[8][0]*s8)));
    AnkAtk[2][0] = (Ankb[2][0]+Atk[2][0]);
    AnkAtk[2][1] = (Ankb[2][1]+Atk[2][1]);
    ank[2][0] = ((AnkAtk[2][0]*c2)-(AnkAtk[2][1]*s2));
    ank[2][1] = ((AnkAtk[2][0]*s2)+(AnkAtk[2][1]*c2));
    AnkAtk[3][0] = (Ankb[3][0]+Atk[3][0]);
    AnkAtk[3][1] = (Ankb[3][1]+Atk[3][1]);
    ank[3][0] = ((AnkAtk[3][0]*cnk[3][0][0])+(AnkAtk[3][1]*cnk[3][0][1]));
    ank[3][1] = ((AnkAtk[3][0]*cnk[3][1][0])+(AnkAtk[3][1]*cnk[3][1][1]));
    AnkAtk[4][0] = (Ankb[4][0]+Atk[4][0]);
    AnkAtk[4][1] = (Ankb[4][1]+Atk[4][1]);
    ank[4][0] = ((AnkAtk[4][0]*cnk[4][0][0])+(AnkAtk[4][1]*cnk[4][0][1]));
    ank[4][1] = ((AnkAtk[4][0]*cnk[4][1][0])+(AnkAtk[4][1]*cnk[4][1][1]));
    AnkAtk[5][0] = (Ankb[5][0]+Atk[5][0]);
    AnkAtk[5][1] = (Ankb[5][1]+Atk[5][1]);
    ank[5][0] = ((AnkAtk[5][0]*cnk[5][0][0])+(AnkAtk[5][1]*cnk[5][0][1]));
    ank[5][1] = ((AnkAtk[5][0]*cnk[5][1][0])+(AnkAtk[5][1]*cnk[5][1][1]));
    AnkAtk[6][0] = (Ankb[6][0]+Atk[6][0]);
    AnkAtk[6][1] = (Ankb[6][1]+Atk[6][1]);
    ank[6][0] = ((AnkAtk[6][0]*cnk[6][0][0])+(AnkAtk[6][1]*cnk[6][0][1]));
    ank[6][1] = ((AnkAtk[6][0]*cnk[6][1][0])+(AnkAtk[6][1]*cnk[6][1][1]));
    AnkAtk[7][0] = (Ankb[7][0]+Atk[7][0]);
    AnkAtk[7][1] = (Ankb[7][1]+Atk[7][1]);
    ank[7][0] = ((AnkAtk[7][0]*cnk[7][0][0])+(AnkAtk[7][1]*cnk[7][0][1]));
    ank[7][1] = ((AnkAtk[7][0]*cnk[7][1][0])+(AnkAtk[7][1]*cnk[7][1][1]));
    AnkAtk[8][0] = (Ankb[8][0]+Atk[8][0]);
    AnkAtk[8][1] = (Ankb[8][1]+Atk[8][1]);
    ank[8][0] = ((AnkAtk[8][0]*cnk[8][0][0])+(AnkAtk[8][1]*cnk[8][0][1]));
    ank[8][1] = ((AnkAtk[8][0]*cnk[8][1][0])+(AnkAtk[8][1]*cnk[8][1][1]));
    anb[0][0] = ank[2][0];
    anb[0][1] = ank[2][1];
    anb[0][2] = 0.;
    anb[1][0] = ank[3][0];
    anb[1][1] = ank[3][1];
    anb[1][2] = 0.;
    anb[2][0] = ank[4][0];
    anb[2][1] = ank[4][1];
    anb[2][2] = 0.;
    anb[3][0] = ank[5][0];
    anb[3][1] = ank[5][1];
    anb[3][2] = 0.;
    anb[4][0] = ank[6][0];
    anb[4][1] = ank[6][1];
    anb[4][2] = 0.;
    anb[5][0] = ank[7][0];
    anb[5][1] = ank[7][1];
    anb[5][2] = 0.;
    anb[6][0] = ank[8][0];
    anb[6][1] = ank[8][1];
    anb[6][2] = 0.;
    roustate = 3;
/*
 Used 0.04 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   89 adds/subtracts/negates
                     76 multiplies
                      0 divides
                    171 assignments
*/
}

sdpseudo(lqout,luout)
    double lqout[1],luout[1];
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

sdpsqdot(lqdout)
    double lqdout[1];
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

sdpsudot(ludout)
    double ludout[1];
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

sdperr(errs)
    double errs[1];
{

}

sdverr(errs)
    double errs[1];
{

}

sdaerr(errs)
    double errs[1];
{

}
int 
sdindx(joint,axis)
    int joint,axis;
{
    int offs,gotit;

    if (sdchkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

sdpresacc(joint,axis,prval)
    int joint,axis;
    double prval;
{

}

sdpresvel(joint,axis,prval)
    int joint,axis;
    double prval;
{

}

sdprespos(joint,axis,prval)
    int joint,axis;
    double prval;
{

}

sdgetht(joint,axis,torque)
    int joint,axis;
    double *torque;
{

    if (sdchkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(30,24);
        return;
    }
    *torque = tauc[sdindx(joint,axis)];
}

sdhinget(joint,axis,torque)
    int joint,axis;
    double torque;
{

    if (sdchkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[sdindx(joint,axis)] = mtau[sdindx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[sdindx(joint,axis)] = utau[sdindx(joint,axis)]+torque;
    }
}

sdpointf(body,point,force)
    int body;
    double point[3],force[3];
{
    double torque[3];

    if (sdchkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

sdbodyt(body,torque)
    int body;
    double torque[3];
{

    if (sdchkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

sddoww(routine)
    int routine;
{

    roustate = 2;
    if (wwflg == 0) {
        wwflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

sdxudot0(routine,oudot0)
    int routine;
    double oudot0[9];
{
/*
Compute unconstrained equations
*/
    int i;

    sdlhs(routine);
/*
Solve equations for udots
*/
    sdfs0();
    sdldubslv(9,9,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 8; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      9 assignments
*/
}

sdudot0(oudot0)
    double oudot0[9];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

sdsetudot(iudot)
    double iudot[9];
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 8; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

sdxudotm(routine,imult,oudotm)
    int routine;
    double imult[1],oudotm[9];
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    for (i = 0; i <= 8; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 8; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     18 assignments
*/
}

sdudotm(imult,oudotm)
    double imult[1],oudotm[9];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

sdderiv(oqdot,oudot)
    double oqdot[9],oudot[9];
{
/*
This is the derivative section for a 7-body ground-based
system with 9 hinge degree(s) of freedom.
*/
    int i;
    double udot0[9],udot1[9];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        sdseterr(17,32);
    }
    if (stabposq == 1) {
        sdseterr(17,33);
    }
    wsiz = 0;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    wrank = 0;
    for (i = 0; i <= 8; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 8; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     18 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

sdresid(eqdot,eudot,emults,resid)
    double eqdot[9],eudot[9],emults[1],resid[18];
{
    int i;
    double uderrs[9];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 9; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 9; i++) {
        resid[9+i] = uderrs[i];
    }
    for (i = 0; i < 9; i++) {
        udot[i] = eudot[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdmult(omults,owrank,omultmap)
    double omults[1];
    int *owrank,omultmap[1];
{

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    *owrank = wrank;
}

sdreac(force,torque)
    double force[7][3],torque[7][3];
{
/*
Generated 18-Jun-2003 17:59:45 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

    if (roustate != 3) {
        sdseterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[8][0] = ((1.41*(AnkAtk[8][0]-gk[8][0]))-ufk[6][0]);
    fc[8][1] = ((1.41*(AnkAtk[8][1]-gk[8][1]))-ufk[6][1]);
    fc[8][2] = -(ufk[6][2]+(1.41*grav[2]));
    tc[8][0] = -(utk[6][0]+(.0513*fc[8][2]));
    tc[8][1] = -(utk[6][1]+(.0459*fc[8][2]));
    tc[8][2] = ((.0068*Onkb[8][2])-(utk[6][2]-((.0459*fc[8][1])+(.0513*fc[8][0])
      )));
    fccikt[8][0] = ((fc[8][0]*c8)+(fc[8][1]*s8));
    fccikt[8][1] = ((fc[8][1]*c8)-(fc[8][0]*s8));
    fccikt[8][2] = fc[8][2];
    ffk[7][0] = (ufk[5][0]-fccikt[8][0]);
    ffk[7][1] = (ufk[5][1]-fccikt[8][1]);
    ffk[7][2] = (ufk[5][2]-fccikt[8][2]);
    ttk[7][0] = (utk[5][0]-(((tc[8][0]*c8)+(tc[8][1]*s8))-(.2438*fccikt[8][2])))
      ;
    ttk[7][1] = (utk[5][1]-((tc[8][1]*c8)-(tc[8][0]*s8)));
    ttk[7][2] = (utk[5][2]-(tc[8][2]+(.2438*fccikt[8][0])));
    fc[7][0] = ((3.51*(AnkAtk[7][0]-gk[7][0]))-ffk[7][0]);
    fc[7][1] = ((3.51*(AnkAtk[7][1]-gk[7][1]))-ffk[7][1]);
    fc[7][2] = -(ffk[7][2]+(3.51*grav[2]));
    tc[7][0] = -(ttk[7][0]+(.1862*fc[7][2]));
    tc[7][1] = -ttk[7][1];
    tc[7][2] = ((.0484*Onkb[7][2])-(ttk[7][2]-(.1862*fc[7][0])));
    fccikt[7][0] = ((fc[7][0]*c7)+(fc[7][1]*s7));
    fccikt[7][1] = ((fc[7][1]*c7)-(fc[7][0]*s7));
    fccikt[7][2] = fc[7][2];
    ffk[6][0] = (ufk[4][0]-fccikt[7][0]);
    ffk[6][1] = (ufk[4][1]-fccikt[7][1]);
    ffk[6][2] = (ufk[4][2]-fccikt[7][2]);
    ttk[6][0] = (utk[4][0]-(((tc[7][0]*c7)+(tc[7][1]*s7))-(.2294*fccikt[7][2])))
      ;
    ttk[6][1] = (utk[4][1]-(((tc[7][1]*c7)-(tc[7][0]*s7))-(.0033*fccikt[7][2])))
      ;
    ttk[6][2] = (utk[4][2]-(tc[7][2]+((.0033*fccikt[7][1])+(.2294*fccikt[7][0]))
      ));
    fc[6][0] = ((8.81*(AnkAtk[6][0]-gk[6][0]))-ffk[6][0]);
    fc[6][1] = ((8.81*(AnkAtk[6][1]-gk[6][1]))-ffk[6][1]);
    fc[6][2] = -(ffk[6][2]+(8.81*grav[2]));
    tc[6][0] = -(ttk[6][0]+(.1715*fc[6][2]));
    tc[6][1] = -(ttk[6][1]-(.002*fc[6][2]));
    tc[6][2] = ((.1337*Onkb[6][2])-(ttk[6][2]+((.002*fc[6][1])-(.1715*fc[6][0]))
      ));
    fccikt[6][0] = ((fc[6][0]*c6)+(fc[6][1]*s6));
    fccikt[6][1] = ((fc[6][1]*c6)-(fc[6][0]*s6));
    fccikt[6][2] = fc[6][2];
    ffk[5][0] = (ufk[3][0]-fccikt[6][0]);
    ffk[5][1] = (ufk[3][1]-fccikt[6][1]);
    ffk[5][2] = (ufk[3][2]-fccikt[6][2]);
    ttk[5][0] = (utk[3][0]-(((.0935*fccikt[6][1])-(.4027*fccikt[6][2]))+((
      tc[6][0]*c6)+(tc[6][1]*s6))));
    ttk[5][1] = (utk[3][1]-(((tc[6][1]*c6)-(tc[6][0]*s6))-(.0935*fccikt[6][0])))
      ;
    ttk[5][2] = (utk[3][2]-(tc[6][2]+(.4027*fccikt[6][0])));
    fc[5][0] = ((43.56*(AnkAtk[5][0]-gk[5][0]))-ffk[5][0]);
    fc[5][1] = ((43.56*(AnkAtk[5][1]-gk[5][1]))-ffk[5][1]);
    fc[5][2] = -(ffk[5][2]+(43.56*grav[2]));
    tc[5][0] = -(ttk[5][0]-((.0935*fc[5][1])+(.4027*fc[5][2])));
    tc[5][1] = -(ttk[5][1]+(.0935*fc[5][0]));
    tc[5][2] = ((3.0691*Onkb[5][2])-(ttk[5][2]+(.4027*fc[5][0])));
    fccikt[5][0] = ((fc[5][0]*c5)-(fc[5][1]*s5));
    fccikt[5][1] = ((fc[5][0]*s5)+(fc[5][1]*c5));
    fccikt[5][2] = fc[5][2];
    ffk[4][0] = (ufk[2][0]-fccikt[5][0]);
    ffk[4][1] = (ufk[2][1]-fccikt[5][1]);
    ffk[4][2] = (ufk[2][2]-fccikt[5][2]);
    ttk[4][0] = (utk[2][0]-((.1715*fccikt[5][2])+((tc[5][0]*c5)-(tc[5][1]*s5))))
      ;
    ttk[4][1] = (utk[2][1]-(((tc[5][0]*s5)+(tc[5][1]*c5))-(.002*fccikt[5][2])));
    ttk[4][2] = (utk[2][2]-(tc[5][2]+((.002*fccikt[5][1])-(.1715*fccikt[5][0])))
      );
    fc[4][0] = ((8.81*(AnkAtk[4][0]-gk[4][0]))-ffk[4][0]);
    fc[4][1] = ((8.81*(AnkAtk[4][1]-gk[4][1]))-ffk[4][1]);
    fc[4][2] = -(ffk[4][2]+(8.81*grav[2]));
    tc[4][0] = -(ttk[4][0]-(.2294*fc[4][2]));
    tc[4][1] = -(ttk[4][1]-(.0033*fc[4][2]));
    tc[4][2] = ((.1337*Onkb[4][2])-(ttk[4][2]+((.0033*fc[4][1])+(.2294*fc[4][0])
      )));
    fccikt[4][0] = ((fc[4][0]*c4)-(fc[4][1]*s4));
    fccikt[4][1] = ((fc[4][0]*s4)+(fc[4][1]*c4));
    fccikt[4][2] = fc[4][2];
    ffk[3][0] = (ufk[1][0]-fccikt[4][0]);
    ffk[3][1] = (ufk[1][1]-fccikt[4][1]);
    ffk[3][2] = (ufk[1][2]-fccikt[4][2]);
    ttk[3][0] = (utk[1][0]-((.1862*fccikt[4][2])+((tc[4][0]*c4)-(tc[4][1]*s4))))
      ;
    ttk[3][1] = (utk[1][1]-((tc[4][0]*s4)+(tc[4][1]*c4)));
    ttk[3][2] = (utk[1][2]-(tc[4][2]-(.1862*fccikt[4][0])));
    fc[3][0] = ((3.51*(AnkAtk[3][0]-gk[3][0]))-ffk[3][0]);
    fc[3][1] = ((3.51*(AnkAtk[3][1]-gk[3][1]))-ffk[3][1]);
    fc[3][2] = -(ffk[3][2]+(3.51*grav[2]));
    tc[3][0] = -(ttk[3][0]-(.2438*fc[3][2]));
    tc[3][1] = -ttk[3][1];
    tc[3][2] = ((.0484*Onkb[3][2])-(ttk[3][2]+(.2438*fc[3][0])));
    fccikt[3][0] = ((fc[3][0]*c3)-(fc[3][1]*s3));
    fccikt[3][1] = ((fc[3][0]*s3)+(fc[3][1]*c3));
    fccikt[3][2] = fc[3][2];
    ffk[2][0] = (ufk[0][0]-fccikt[3][0]);
    ffk[2][1] = (ufk[0][1]-fccikt[3][1]);
    ffk[2][2] = (ufk[0][2]-fccikt[3][2]);
    ttk[2][0] = (utk[0][0]-((.0513*fccikt[3][2])+((tc[3][0]*c3)-(tc[3][1]*s3))))
      ;
    ttk[2][1] = (utk[0][1]-((.0459*fccikt[3][2])+((tc[3][0]*s3)+(tc[3][1]*c3))))
      ;
    ttk[2][2] = (utk[0][2]-(tc[3][2]-((.0459*fccikt[3][1])+(.0513*fccikt[3][0]))
      ));
    fc[2][0] = ((1.41*(AnkAtk[2][0]-gk[2][0]))-ffk[2][0]);
    fc[2][1] = ((1.41*(AnkAtk[2][1]-gk[2][1]))-ffk[2][1]);
    fc[2][2] = -(ffk[2][2]+(1.41*grav[2]));
    tc[2][0] = -(ttk[2][0]-(.0387*fc[2][2]));
    tc[2][1] = -(ttk[2][1]+(.0917*fc[2][2]));
    tc[2][2] = ((.0068*udot[2])-(ttk[2][2]+((.0387*fc[2][0])-(.0917*fc[2][1]))))
      ;
    fccikt[2][0] = ((fc[2][0]*c2)-(fc[2][1]*s2));
    fccikt[2][1] = ((fc[2][0]*s2)+(fc[2][1]*c2));
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -((tc[2][0]*c2)-(tc[2][1]*s2));
    ttk[1][1] = -((tc[2][0]*s2)+(tc[2][1]*c2));
    ttk[1][2] = -tc[2][2];
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = fc[1][0];
    fccikt[1][1] = fc[1][1];
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = -fccikt[1][0];
    ffk[0][1] = -fccikt[1][1];
    ffk[0][2] = -fccikt[1][2];
    ttk[0][0] = -(tc[1][0]+(fccikt[1][2]*q[1]));
    ttk[0][1] = -tc[1][1];
    ttk[0][2] = -(tc[1][2]-(fccikt[1][0]*q[1]));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[2][0];
    torque[0][0] = tc[2][0];
    force[0][1] = fc[2][1];
    torque[0][1] = tc[2][1];
    force[0][2] = fc[2][2];
    torque[0][2] = tc[2][2];
    force[1][0] = fc[3][0];
    torque[1][0] = tc[3][0];
    force[1][1] = fc[3][1];
    torque[1][1] = tc[3][1];
    force[1][2] = fc[3][2];
    torque[1][2] = tc[3][2];
    force[2][0] = fc[4][0];
    torque[2][0] = tc[4][0];
    force[2][1] = fc[4][1];
    torque[2][1] = tc[4][1];
    force[2][2] = fc[4][2];
    torque[2][2] = tc[4][2];
    force[3][0] = fc[5][0];
    torque[3][0] = tc[5][0];
    force[3][1] = fc[5][1];
    torque[3][1] = tc[5][1];
    force[3][2] = fc[5][2];
    torque[3][2] = tc[5][2];
    force[4][0] = fc[6][0];
    torque[4][0] = tc[6][0];
    force[4][1] = fc[6][1];
    torque[4][1] = tc[6][1];
    force[4][2] = fc[6][2];
    torque[4][2] = tc[6][2];
    force[5][0] = fc[7][0];
    torque[5][0] = tc[7][0];
    force[5][1] = fc[7][1];
    torque[5][1] = tc[7][1];
    force[5][2] = fc[7][2];
    torque[5][2] = tc[7][2];
    force[6][0] = fc[8][0];
    torque[6][0] = tc[8][0];
    force[6][1] = fc[8][1];
    torque[6][1] = tc[8][1];
    force[6][2] = fc[8][2];
    torque[6][2] = tc[8][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.05 seconds CPU time,
 16384 additional bytes of memory.
 Equations contain  197 adds/subtracts/negates
                    130 multiplies
                      0 divides
                    168 assignments
*/
}

sdmom(lm,am,ke)
    double lm[3],am[3],*ke;
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 18-Jun-2003 17:59:45 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[7][3],hnk[7][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lm[0] = ((1.41*vnk[8][0])+((3.51*vnk[7][0])+((8.81*vnk[6][0])+((43.56*
      vnk[5][0])+((8.81*vnk[4][0])+((1.41*vnk[2][0])+(3.51*vnk[3][0])))))));
    lm[1] = ((1.41*vnk[8][1])+((3.51*vnk[7][1])+((8.81*vnk[6][1])+((43.56*
      vnk[5][1])+((8.81*vnk[4][1])+((1.41*vnk[2][1])+(3.51*vnk[3][1])))))));
    lm[2] = 0.;
    am[0] = (((.26367*vnk[8][1])+((.65637*vnk[7][1])+((1.64747*vnk[6][1])+(
      4.07286*vnk[5][1]))))-(.0935*lm[1]));
    am[1] = ((.0935*lm[0])-((.26367*vnk[8][0])+((.65637*vnk[7][0])+((1.64747*
      vnk[6][0])+(4.07286*vnk[5][0])))));
    temp[0] = (((.1337*wk[6][2])+(8.81*((rnk[6][0]*vnk[6][1])-(rnk[6][1]*
      vnk[6][0]))))+(((3.0691*wk[5][2])+(43.56*((rnk[5][0]*vnk[5][1])-(rnk[5][1]
      *vnk[5][0]))))+(((.1337*wk[4][2])+(8.81*((rnk[4][0]*vnk[4][1])-(rnk[4][1]*
      vnk[4][0]))))+(((.0068*u[2])+(1.41*((rnk[2][0]*vnk[2][1])-(rnk[2][1]*
      vnk[2][0]))))+((.0484*wk[3][2])+(3.51*((rnk[3][0]*vnk[3][1])-(rnk[3][1]*
      vnk[3][0]))))))));
    am[2] = ((((.0068*wk[8][2])+(1.41*((rnk[8][0]*vnk[8][1])-(rnk[8][1]*
      vnk[8][0]))))+(((.0484*wk[7][2])+(3.51*((rnk[7][0]*vnk[7][1])-(rnk[7][1]*
      vnk[7][0]))))+temp[0]))-((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = (((3.0691*(wk[5][2]*wk[5][2]))+(43.56*((vnk[5][0]*vnk[5][0])+(
      vnk[5][1]*vnk[5][1]))))+(((.1337*(wk[4][2]*wk[4][2]))+(8.81*((vnk[4][0]*
      vnk[4][0])+(vnk[4][1]*vnk[4][1]))))+(((.0068*(u[2]*u[2]))+(1.41*((
      vnk[2][0]*vnk[2][0])+(vnk[2][1]*vnk[2][1]))))+((.0484*(wk[3][2]*wk[3][2]))
      +(3.51*((vnk[3][0]*vnk[3][0])+(vnk[3][1]*vnk[3][1])))))));
    *ke = (.5*(((.0068*(wk[8][2]*wk[8][2]))+(1.41*((vnk[8][0]*vnk[8][0])+(
      vnk[8][1]*vnk[8][1]))))+(((.0484*(wk[7][2]*wk[7][2]))+(3.51*((vnk[7][0]*
      vnk[7][0])+(vnk[7][1]*vnk[7][1]))))+(((.1337*(wk[6][2]*wk[6][2]))+(8.81*((
      vnk[6][0]*vnk[6][0])+(vnk[6][1]*vnk[6][1]))))+temp[0]))));
/*
 Used 0.02 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   62 adds/subtracts/negates
                     90 multiplies
                      0 divides
                      9 assignments
*/
}

sdsys(mtoto,cm,icm)
    double *mtoto,cm[3],icm[3][3];
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 18-Jun-2003 17:59:45 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[9][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = 71.02;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = -.0935;
    temp[0] = (((43.56*(.00874225+(rnk[5][1]*rnk[5][1])))+((.7978*(cnk[5][0][1]*
      cnk[5][0][1]))+(3.1524*(cnk[5][0][0]*cnk[5][0][0]))))+(((8.81*(rnk[4][1]*
      rnk[4][1]))+((.0332*(cnk[4][0][1]*cnk[4][0][1]))+(.1268*(cnk[4][0][0]*
      cnk[4][0][0]))))+(((.005*(s2*s2))+(1.41*(rnk[2][1]*rnk[2][1])))+((3.51*(
      rnk[3][1]*rnk[3][1]))+((.0048*(cnk[3][0][1]*cnk[3][0][1]))+(.0477*(
      cnk[3][0][0]*cnk[3][0][0])))))));
    temp[1] = ((((1.41*(.034969+(rnk[8][1]*rnk[8][1])))+((.0017*(cnk[8][0][0]*
      cnk[8][0][0]))+(.0067*(cnk[8][0][1]*cnk[8][0][1]))))+(((3.51*(.034969+(
      rnk[7][1]*rnk[7][1])))+((.0048*(cnk[7][0][1]*cnk[7][0][1]))+(.0477*(
      cnk[7][0][0]*cnk[7][0][0]))))+(((8.81*(.034969+(rnk[6][1]*rnk[6][1])))+((
      .0332*(cnk[6][0][1]*cnk[6][0][1]))+(.1268*(cnk[6][0][0]*cnk[6][0][0]))))+
      temp[0])))-(71.02*(.00874225+(com[1]*com[1]))));
    icm[0][0] = (.0017+temp[1]);
    temp[0] = ((((.7978*(cnk[5][0][1]*cnk[5][1][1]))+(3.1524*(cnk[5][0][0]*
      cnk[5][1][0])))-(43.56*(rnk[5][0]*rnk[5][1])))+((((.0332*(cnk[4][0][1]*
      cnk[4][1][1]))+(.1268*(cnk[4][0][0]*cnk[4][1][0])))-(8.81*(rnk[4][0]*
      rnk[4][1])))+((((.0048*(cnk[3][0][1]*cnk[3][1][1]))+(.0477*(cnk[3][0][0]*
      cnk[3][1][0])))-(3.51*(rnk[3][0]*rnk[3][1])))-((.005*(s2*c2))+(1.41*(
      rnk[2][0]*rnk[2][1]))))));
    icm[0][1] = ((71.02*(com[0]*com[1]))+((((.0017*(cnk[8][0][0]*cnk[8][1][0]))+
      (.0067*(cnk[8][0][1]*cnk[8][1][1])))-(1.41*(rnk[8][0]*rnk[8][1])))+((((
      .0048*(cnk[7][0][1]*cnk[7][1][1]))+(.0477*(cnk[7][0][0]*cnk[7][1][0])))-(
      3.51*(rnk[7][0]*rnk[7][1])))+((((.0332*(cnk[6][0][1]*cnk[6][1][1]))+(.1268
      *(cnk[6][0][0]*cnk[6][1][0])))-(8.81*(rnk[6][0]*rnk[6][1])))+temp[0]))));
    icm[0][2] = (((.26367*rnk[8][0])+((.65637*rnk[7][0])+((1.64747*rnk[6][0])+(
      4.07286*rnk[5][0]))))-(6.64037*com[0]));
    icm[1][0] = icm[0][1];
    temp[0] = (((43.56*(.00874225+(rnk[5][0]*rnk[5][0])))+((.7978*(cnk[5][1][1]*
      cnk[5][1][1]))+(3.1524*(cnk[5][1][0]*cnk[5][1][0]))))+(((8.81*(rnk[4][0]*
      rnk[4][0]))+((.0332*(cnk[4][1][1]*cnk[4][1][1]))+(.1268*(cnk[4][1][0]*
      cnk[4][1][0]))))+(((.005*(c2*c2))+(1.41*(rnk[2][0]*rnk[2][0])))+((3.51*(
      rnk[3][0]*rnk[3][0]))+((.0048*(cnk[3][1][1]*cnk[3][1][1]))+(.0477*(
      cnk[3][1][0]*cnk[3][1][0])))))));
    temp[1] = ((((1.41*(.034969+(rnk[8][0]*rnk[8][0])))+((.0017*(cnk[8][1][0]*
      cnk[8][1][0]))+(.0067*(cnk[8][1][1]*cnk[8][1][1]))))+(((3.51*(.034969+(
      rnk[7][0]*rnk[7][0])))+((.0048*(cnk[7][1][1]*cnk[7][1][1]))+(.0477*(
      cnk[7][1][0]*cnk[7][1][0]))))+(((8.81*(.034969+(rnk[6][0]*rnk[6][0])))+((
      .0332*(cnk[6][1][1]*cnk[6][1][1]))+(.1268*(cnk[6][1][0]*cnk[6][1][0]))))+
      temp[0])))-(71.02*(.00874225+(com[0]*com[0]))));
    icm[1][1] = (.0017+temp[1]);
    icm[1][2] = (((.26367*rnk[8][1])+((.65637*rnk[7][1])+((1.64747*rnk[6][1])+(
      4.07286*rnk[5][1]))))-(6.64037*com[1]));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = ((1.41*((rnk[8][0]*rnk[8][0])+(rnk[8][1]*rnk[8][1])))+((3.51*((
      rnk[7][0]*rnk[7][0])+(rnk[7][1]*rnk[7][1])))+((8.81*((rnk[6][0]*rnk[6][0])
      +(rnk[6][1]*rnk[6][1])))+((43.56*((rnk[5][0]*rnk[5][0])+(rnk[5][1]*
      rnk[5][1])))+((8.81*((rnk[4][0]*rnk[4][0])+(rnk[4][1]*rnk[4][1])))+((1.41*
      ((rnk[2][0]*rnk[2][0])+(rnk[2][1]*rnk[2][1])))+(3.51*((rnk[3][0]*rnk[3][0]
      )+(rnk[3][1]*rnk[3][1])))))))));
    icm[2][2] = (3.4469+(temp[0]-(71.02*((com[0]*com[0])+(com[1]*com[1])))));
/*
 Used 0.07 seconds CPU time,
 16384 additional bytes of memory.
 Equations contain   96 adds/subtracts/negates
                    160 multiplies
                      0 divides
                     19 assignments
*/
}

sdpos(body,pt,loc)
    int body;
    double pt[3],loc[3];
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

sdvel(body,pt,velo)
    int body;
    double pt[3],velo[3];
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

sdorient(body,dircos)
    int body;
    double dircos[3][3];
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (sdchkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

sdangvel(body,avel)
    int body;
    double avel[3];
{
/*
Return angular velocity of the body.

*/

    if (sdchkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

sdtrans(frbod,ivec,tobod,ovec)
    int frbod;
    double ivec[3];
    int tobod;
    double ovec[3];
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (sdchkbnum(25,frbod) != 0) {
        return;
    }
    if (sdchkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(25,23);
        return;
    }
    if (frbod == tobod) {
        sdvcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

sdrel2cart(coord,body,point,linchg,rotchg)
    int coord,body;
    double point[3],linchg[3],rotchg[3];
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 8)) {
        sdseterr(59,45);
        return;
    }
    if (sdchkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        sdvset(0.,0.,0.,linchg);
        sdvset(0.,0.,0.,rotchg);
        return;
    }
    sddovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        sdvcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    sdvcross(rotchg,pv,linchg);
    sdvadd(linchg,lin,linchg);
}

sdacc(body,pt,accel)
    int body;
    double pt[3],accel[3];
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (sdchkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

sdangacc(body,aacc)
    int body;
    double aacc[3];
{
/*
Return angular acceleration of the body.

*/

    if (sdchkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

sdgrav(gravin)
    double gravin[3];
{

    grav[0] = gravin[0];
    gravq[0] = 3;
    grav[1] = gravin[1];
    gravq[1] = 3;
    grav[2] = gravin[2];
    gravq[2] = 3;
    roustate = 0;
}

sdmass(body,massin)
    int body;
    double massin;
{

    if (sdchkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        sdseterr(2,19);
    }
    roustate = 0;
}

sdiner(body,inerin)
    int body;
    double inerin[3][3];
{
    int anyques;

    if (sdchkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(3,19);
    }
    roustate = 0;
}

sdbtj(joint,btjin)
    int joint;
    double btjin[3];
{
    int anyques;

    if (sdchkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(4,19);
    }
    roustate = 0;
}

sditj(joint,itjin)
    int joint;
    double itjin[3];
{
    int anyques;

    if (sdchkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(5,19);
    }
    roustate = 0;
}

sdpin(joint,pinno,pinin)
    int joint,pinno;
    double pinin[3];
{
    int anyques,offs;

    if (sdchkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(6,19);
    }
    roustate = 0;
}

sdpres(joint,axis,presin)
    int joint,axis,presin;
{
    int anyques;

    if (sdchkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        sdseterr(37,20);
    }
    anyques = 0;
    if (presq[sdindx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[sdindx(joint,axis)] = 1.;
        } else {
            pres[sdindx(joint,axis)] = 0.;
        }
        presq[sdindx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(37,19);
    }
    wwflg = 0;
}

sdstab(velin,posin)
    double velin,posin;
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

sdgetgrav(gravout)
    double gravout[3];
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

sdgetmass(body,massout)
    int body;
    double *massout;
{

    if (sdchkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(40,15);
        return;
    }
    *massout = mk[body];
}



#define rdNU 9
void rd_sdmassmat(double *aI)
{
	int i,j;
	double I[rdNU][rdNU];
	sdmassmat(I);

	for(i=0;i<rdNU;i++) {
		for(j=0;j<rdNU;j++,aI++) {
			*aI = I[i][j];
		}
	}
}



sdgetiner(body,inerout)
    int body;
    double inerout[3][3];
{

    if (sdchkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

sdgetbtj(joint,btjout)
    int joint;
    double btjout[3];
{

    if (sdchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

sdgetitj(joint,itjout)
    int joint;
    double itjout[3];
{

    if (sdchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

sdgetpin(joint,pinno,pinout)
    int joint,pinno;
    double pinout[3];
{
    int offs;

    if (sdchkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

sdgetpres(joint,axis,presout)
    int joint,axis,*presout;
{

    if (sdchkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

sdgetstab(velout,posout)
    double *velout,*posout;
{

    *velout = stabvel;
    *posout = stabpos;
}

sdinfo(info)
    int info[50];
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 0;
/* info entries from 12-49 are reserved */
}

sdjnt(joint,info,tran)
    int joint,info[50],tran[6];
{
    int i,offs;

    if (sdchkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

sdcons(consno,info)
    int consno,info[50];
{

    if (sdchkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}
int 
sdchkbnum(routine,bnum)
    int routine,bnum;
{

    if ((bnum < -1) || (bnum > 6)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(routine,jnum)
    int routine,jnum;
{

    if ((jnum < 0) || (jnum > 6)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(routine,ucnum)
    int routine,ucnum;
{

    if ((ucnum < 0) || (ucnum > -1)) {
        sdseterr(routine,21);
        return 1;
    }
    return 0;
}
int 
sdchkjaxis(routine,jnum,axnum)
    int routine,jnum,axnum;
{
    int maxax;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        sdseterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdchkjpin(routine,jnum,pinno)
    int routine,jnum,pinno;
{
    int maxax,pinok;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        sdseterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

sdst2ang(st,stang)
    double st[9],stang[9];
{
    int i;

    for (i = 0; i < 9; i++) {
        stang[i] = st[i];
    }
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

sdang2st(stang,st)
    double stang[9],st[9];
{
    int i;

    for (i = 0; i < 9; i++) {
        st[i] = stang[i];
    }
}

/* Normalize Euler parameters in state. */

sdnrmsterr(st,normst,routine)
    double st[9],normst[9];
    int routine;
{
    int i;

    for (i = 0; i < 9; i++) {
        normst[i] = st[i];
    }
}

sdnormst(st,normst)
    double st[9],normst[9];
{

    sdnrmsterr(st,normst,0);
}

sdgentime(gentm)
    int *gentm;
{

    *gentm = 175922;
}
/*
Done. CPU seconds used: 0.63  Memory used: 1007616 bytes.
Equation complexity:
  sdstate:   155 adds   237 multiplies     0 divides   298 assignments
  sdderiv:   869 adds  1029 multiplies     9 divides   939 assignments
  sdresid:   434 adds   397 multiplies     0 divides   399 assignments
  sdreac:    197 adds   130 multiplies     0 divides   168 assignments
  sdmom:      62 adds    90 multiplies     0 divides     9 assignments
  sdsys:      96 adds   160 multiplies     0 divides    19 assignments
*/
