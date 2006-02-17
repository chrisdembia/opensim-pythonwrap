/*
Generated 15-Feb-2006 17:06:52 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (utModelPrescribed.sd)

Bodies        Inb
No  Name      body Joint type  Coords q         Multipliers
--- --------- ---- ----------- ---------------- -----------------------
 -1 $ground                                    |
  0 pelvis     -1  Sixdof        0?  1?  2?    |
                   ...           3?  4?  5? 33 |  0p  1p  2p  3p  4p  5p
  1 hat         0  Gimbal        6?  7?  8?    |  6p  7p  8p
  2 rfemur      0  Gimbal        9? 10? 11?    |  9p 10p 11p
  3 rtibia      2  Gimbal       12? 13? 14?    | 12p 13p 14p
  4 rhindfoot   3  Gimbal       15? 16? 17?    | 15p 16p 17p
  5 rtoes       4  Gimbal       18? 19? 20?    | 18p 19p 20p
  6 lfemur      0  Gimbal       21? 22? 23?    | 21p 22p 23p
  7 ltibia      6  Gimbal       24? 25? 26?    | 24p 25p 26p
  8 lhindfoot   7  Gimbal       27? 28? 29?    | 27p 28p 29p
  9 ltoes       8  Gimbal       30? 31? 32?    | 30p 31p 32p

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[10],inb_[10],outb_[10],njntdof_[10],njntc_[10],njntp_[10],firstq_
      [10],ballq_[10],firstm_[10],firstp_[10];
    int trans_[33];
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
    double grav_[3],mk_[10],ik_[10][3][3],pin_[33][3];
    double rk_[10][3],ri_[10][3],pres_[33],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[33];
    int gravq_[3],mkq_[10],ikq_[10][3][3],pinq_[33][3],rkq_[10][3],riq_[10][3],
      presq_[33],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[10][3],rcom_[10][3],mkrcomt_[10][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[33],psik_[33][3][3],psrcom_[33][3
      ],psrk_[33][3],psri_[33][3];
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
    double curtim_,q_[34],qn_[34],u_[33],cnk_[33][3][3],cnb_[10][3][3];
    double rnk_[33][3],vnk_[33][3],wk_[33][3],rnb_[10][3],vnb_[10][3],wb_[10][3]
      ,wbrcom_[10][3],com_[3],rnkg_[3];
    double Cik_[33][3][3],rikt_[33][3][3],Iko_[33][3][3],mkrk_[33][3][3],Cib_[10
      ][3][3];
    double Wkk_[33][3],Vkk_[33][3],dik_[33][3],rpp_[33][3],rpk_[33][3],rik_[33][
      3],rik2_[33][3];
    double rpri_[33][3],Wik_[33][3],Vik_[33][3],Wirk_[33][3],rkWkk_[33][3],
      Wkrpk_[33][3],VikWkr_[33][3];
    double perr_[33],verr_[33],aerr_[33],mult_[33],ufk_[10][3],utk_[10][3],mfk_[
      10][3],mtk_[10][3];
    double utau_[33],mtau_[33],uacc_[33],uvel_[33],upos_[34];
    double s6_,c6_,s7_,c7_,s8_,c8_,s9_,c9_,s10_,c10_,s11_,c11_,s12_,c12_,s13_,
      c13_,s14_,c14_,s15_,c15_,s16_,c16_,s17_,c17_,s18_,c18_,s19_,c19_,s20_,c20_
      ,s21_,c21_,s22_,c22_,s23_,c23_,s24_,c24_,s25_,c25_,s26_,c26_,s27_,c27_,
      s28_,c28_,s29_,c29_,s30_,c30_,s31_,c31_,s32_,c32_;
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
#define s6 (sdgstate.s6_)
#define c6 (sdgstate.c6_)
#define s7 (sdgstate.s7_)
#define c7 (sdgstate.c7_)
#define s8 (sdgstate.s8_)
#define c8 (sdgstate.c8_)
#define s9 (sdgstate.s9_)
#define c9 (sdgstate.c9_)
#define s10 (sdgstate.s10_)
#define c10 (sdgstate.c10_)
#define s11 (sdgstate.s11_)
#define c11 (sdgstate.c11_)
#define s12 (sdgstate.s12_)
#define c12 (sdgstate.c12_)
#define s13 (sdgstate.s13_)
#define c13 (sdgstate.c13_)
#define s14 (sdgstate.s14_)
#define c14 (sdgstate.c14_)
#define s15 (sdgstate.s15_)
#define c15 (sdgstate.c15_)
#define s16 (sdgstate.s16_)
#define c16 (sdgstate.c16_)
#define s17 (sdgstate.s17_)
#define c17 (sdgstate.c17_)
#define s18 (sdgstate.s18_)
#define c18 (sdgstate.c18_)
#define s19 (sdgstate.s19_)
#define c19 (sdgstate.c19_)
#define s20 (sdgstate.s20_)
#define c20 (sdgstate.c20_)
#define s21 (sdgstate.s21_)
#define c21 (sdgstate.c21_)
#define s22 (sdgstate.s22_)
#define c22 (sdgstate.c22_)
#define s23 (sdgstate.s23_)
#define c23 (sdgstate.c23_)
#define s24 (sdgstate.s24_)
#define c24 (sdgstate.c24_)
#define s25 (sdgstate.s25_)
#define c25 (sdgstate.c25_)
#define s26 (sdgstate.s26_)
#define c26 (sdgstate.c26_)
#define s27 (sdgstate.s27_)
#define c27 (sdgstate.c27_)
#define s28 (sdgstate.s28_)
#define c28 (sdgstate.c28_)
#define s29 (sdgstate.s29_)
#define c29 (sdgstate.c29_)
#define s30 (sdgstate.s30_)
#define c30 (sdgstate.c30_)
#define s31 (sdgstate.s31_)
#define c31 (sdgstate.c31_)
#define s32 (sdgstate.s32_)
#define c32 (sdgstate.c32_)

typedef struct {
    double fs0_[33],qdot_[34],Otk_[33][3],Atk_[33][3],AiOiWi_[33][3],Fstar_[33][
      3];
    double Tstar_[33][3],Fstark_[33][3],Tstark_[33][3],IkWk_[33][3],WkIkWk_[33][
      3],gk_[33][3],IkbWk_[10][3],WkIkbWk_[10][3];
    double w0w0_[10],w1w1_[10],w2w2_[10],w0w1_[10],w0w2_[10],w1w2_[10];
    double w00w11_[10],w00w22_[10],w11w22_[10],ww_[33][33],qraux_[33];
    double mm_[33][33],mlo_[33][33],mdi_[33],IkWpk_[33][33][3],works_[33],
      workss_[33][33];
    double Wpk_[33][33][3],Vpk_[33][33][3],VWri_[33][33][3];
    int wmap_[33],multmap_[33],jpvt_[33],wsiz_,wrank_;
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
    double fs_[33],udot_[33],tauc_[33],dyad_[10][3][3],fc_[33][3],tc_[33][3];
    double ank_[33][3],onk_[33][3],Onkb_[33][3],AOnkri_[33][3],Ankb_[33][3],
      AnkAtk_[33][3],anb_[10][3],onb_[10][3],dyrcom_[10][3];
    double ffk_[33][3],ttk_[33][3],fccikt_[33][3],ffkb_[10][3],ttkb_[10][3];
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
    /* nbod */ 10,
    /* ndof */ 33,
    /* ncons */ 33,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 1,
    /* nlball */ 0,
    /* npres */ 33,
    /* nuser */ 0,
    /* jtype[0] */ 6,
    /* jtype[1] */ 3,
    /* jtype[2] */ 3,
    /* jtype[3] */ 3,
    /* jtype[4] */ 3,
    /* jtype[5] */ 3,
    /* jtype[6] */ 3,
    /* jtype[7] */ 3,
    /* jtype[8] */ 3,
    /* jtype[9] */ 3,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 0,
    /* inb[3] */ 2,
    /* inb[4] */ 3,
    /* inb[5] */ 4,
    /* inb[6] */ 0,
    /* inb[7] */ 6,
    /* inb[8] */ 7,
    /* inb[9] */ 8,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* outb[3] */ 3,
    /* outb[4] */ 4,
    /* outb[5] */ 5,
    /* outb[6] */ 6,
    /* outb[7] */ 7,
    /* outb[8] */ 8,
    /* outb[9] */ 9,
    /* njntdof[0] */ 6,
    /* njntdof[1] */ 3,
    /* njntdof[2] */ 3,
    /* njntdof[3] */ 3,
    /* njntdof[4] */ 3,
    /* njntdof[5] */ 3,
    /* njntdof[6] */ 3,
    /* njntdof[7] */ 3,
    /* njntdof[8] */ 3,
    /* njntdof[9] */ 3,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntc[3] */ 0,
    /* njntc[4] */ 0,
    /* njntc[5] */ 0,
    /* njntc[6] */ 0,
    /* njntc[7] */ 0,
    /* njntc[8] */ 0,
    /* njntc[9] */ 0,
    /* njntp[0] */ 6,
    /* njntp[1] */ 3,
    /* njntp[2] */ 3,
    /* njntp[3] */ 3,
    /* njntp[4] */ 3,
    /* njntp[5] */ 3,
    /* njntp[6] */ 3,
    /* njntp[7] */ 3,
    /* njntp[8] */ 3,
    /* njntp[9] */ 3,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 9,
    /* firstq[3] */ 12,
    /* firstq[4] */ 15,
    /* firstq[5] */ 18,
    /* firstq[6] */ 21,
    /* firstq[7] */ 24,
    /* firstq[8] */ 27,
    /* firstq[9] */ 30,
    /* ballq[0] */ 33,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* ballq[7] */ -104,
    /* ballq[8] */ -104,
    /* ballq[9] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstm[3] */ -1,
    /* firstm[4] */ -1,
    /* firstm[5] */ -1,
    /* firstm[6] */ -1,
    /* firstm[7] */ -1,
    /* firstm[8] */ -1,
    /* firstm[9] */ -1,
    /* firstp[0] */ 0,
    /* firstp[1] */ 6,
    /* firstp[2] */ 9,
    /* firstp[3] */ 12,
    /* firstp[4] */ 15,
    /* firstp[5] */ 18,
    /* firstp[6] */ 21,
    /* firstp[7] */ 24,
    /* firstp[8] */ 27,
    /* firstp[9] */ 30,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* trans[8] */ 0,
    /* trans[9] */ 0,
    /* trans[10] */ 0,
    /* trans[11] */ 0,
    /* trans[12] */ 0,
    /* trans[13] */ 0,
    /* trans[14] */ 0,
    /* trans[15] */ 0,
    /* trans[16] */ 0,
    /* trans[17] */ 0,
    /* trans[18] */ 0,
    /* trans[19] */ 0,
    /* trans[20] */ 0,
    /* trans[21] */ 0,
    /* trans[22] */ 0,
    /* trans[23] */ 0,
    /* trans[24] */ 0,
    /* trans[25] */ 0,
    /* trans[26] */ 0,
    /* trans[27] */ 0,
    /* trans[28] */ 0,
    /* trans[29] */ 0,
    /* trans[30] */ 0,
    /* trans[31] */ 0,
    /* trans[32] */ 0,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 11.15,
    /* mk[1] */ 32.413,
    /* mk[2] */ 8.806,
    /* mk[3] */ 3.51,
    /* mk[4] */ 1.2,
    /* mk[5] */ .205126,
    /* mk[6] */ 8.806,
    /* mk[7] */ 3.51,
    /* mk[8] */ 1.2,
    /* mk[9] */ .205126,

/* inertia */
    /* ik[0][0][0] */ .0973,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .0825,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ .0548,
    /* ik[1][0][0] */ 1.396,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ .7153,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ 1.3552,
    /* ik[2][0][0] */ .1268,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ .0332,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ .1337,
    /* ik[3][0][0] */ .0477,
    /* ik[3][0][1] */ 0.,
    /* ik[3][0][2] */ 0.,
    /* ik[3][1][0] */ 0.,
    /* ik[3][1][1] */ .0048,
    /* ik[3][1][2] */ 0.,
    /* ik[3][2][0] */ 0.,
    /* ik[3][2][1] */ 0.,
    /* ik[3][2][2] */ .0484,
    /* ik[4][0][0] */ .001361,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ .003709,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ .003916,
    /* ik[5][0][0] */ .000117,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ .000179,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ .000119,
    /* ik[6][0][0] */ .1268,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ .0332,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ .1337,
    /* ik[7][0][0] */ .0477,
    /* ik[7][0][1] */ 0.,
    /* ik[7][0][2] */ 0.,
    /* ik[7][1][0] */ 0.,
    /* ik[7][1][1] */ .0048,
    /* ik[7][1][2] */ 0.,
    /* ik[7][2][0] */ 0.,
    /* ik[7][2][1] */ 0.,
    /* ik[7][2][2] */ .0484,
    /* ik[8][0][0] */ .001361,
    /* ik[8][0][1] */ 0.,
    /* ik[8][0][2] */ 0.,
    /* ik[8][1][0] */ 0.,
    /* ik[8][1][1] */ .003709,
    /* ik[8][1][2] */ 0.,
    /* ik[8][2][0] */ 0.,
    /* ik[8][2][1] */ 0.,
    /* ik[8][2][2] */ .003916,
    /* ik[9][0][0] */ .000117,
    /* ik[9][0][1] */ 0.,
    /* ik[9][0][2] */ 0.,
    /* ik[9][1][0] */ 0.,
    /* ik[9][1][1] */ .000179,
    /* ik[9][1][2] */ 0.,
    /* ik[9][2][0] */ 0.,
    /* ik[9][2][1] */ 0.,
    /* ik[9][2][2] */ .000119,

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
    /* pin[3][2] */ 0.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 0.,
    /* pin[6][0] */ 0.,
    /* pin[6][1] */ 0.,
    /* pin[6][2] */ 1.,
    /* pin[7][0] */ 1.,
    /* pin[7][1] */ 0.,
    /* pin[7][2] */ 0.,
    /* pin[8][0] */ 0.,
    /* pin[8][1] */ 1.,
    /* pin[8][2] */ 0.,
    /* pin[9][0] */ 0.,
    /* pin[9][1] */ 0.,
    /* pin[9][2] */ 1.,
    /* pin[10][0] */ 1.,
    /* pin[10][1] */ 0.,
    /* pin[10][2] */ 0.,
    /* pin[11][0] */ 0.,
    /* pin[11][1] */ 1.,
    /* pin[11][2] */ 0.,
    /* pin[12][0] */ 0.,
    /* pin[12][1] */ 0.,
    /* pin[12][2] */ 1.,
    /* pin[13][0] */ 1.,
    /* pin[13][1] */ 0.,
    /* pin[13][2] */ 0.,
    /* pin[14][0] */ 0.,
    /* pin[14][1] */ 1.,
    /* pin[14][2] */ 0.,
    /* pin[15][0] */ 0.,
    /* pin[15][1] */ 0.,
    /* pin[15][2] */ 1.,
    /* pin[16][0] */ 1.,
    /* pin[16][1] */ 0.,
    /* pin[16][2] */ 0.,
    /* pin[17][0] */ 0.,
    /* pin[17][1] */ 1.,
    /* pin[17][2] */ 0.,
    /* pin[18][0] */ 0.,
    /* pin[18][1] */ 0.,
    /* pin[18][2] */ 1.,
    /* pin[19][0] */ 1.,
    /* pin[19][1] */ 0.,
    /* pin[19][2] */ 0.,
    /* pin[20][0] */ 0.,
    /* pin[20][1] */ 1.,
    /* pin[20][2] */ 0.,
    /* pin[21][0] */ 0.,
    /* pin[21][1] */ 0.,
    /* pin[21][2] */ 1.,
    /* pin[22][0] */ -1.,
    /* pin[22][1] */ 0.,
    /* pin[22][2] */ 0.,
    /* pin[23][0] */ 0.,
    /* pin[23][1] */ -1.,
    /* pin[23][2] */ 0.,
    /* pin[24][0] */ 0.,
    /* pin[24][1] */ 0.,
    /* pin[24][2] */ 1.,
    /* pin[25][0] */ -1.,
    /* pin[25][1] */ 0.,
    /* pin[25][2] */ 0.,
    /* pin[26][0] */ 0.,
    /* pin[26][1] */ -1.,
    /* pin[26][2] */ 0.,
    /* pin[27][0] */ 0.,
    /* pin[27][1] */ 0.,
    /* pin[27][2] */ 1.,
    /* pin[28][0] */ -1.,
    /* pin[28][1] */ 0.,
    /* pin[28][2] */ 0.,
    /* pin[29][0] */ 0.,
    /* pin[29][1] */ -1.,
    /* pin[29][2] */ 0.,
    /* pin[30][0] */ 0.,
    /* pin[30][1] */ 0.,
    /* pin[30][2] */ 1.,
    /* pin[31][0] */ -1.,
    /* pin[31][1] */ 0.,
    /* pin[31][2] */ 0.,
    /* pin[32][0] */ 0.,
    /* pin[32][1] */ -1.,
    /* pin[32][2] */ 0.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ 0.,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ -.3202,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ .002,
    /* rk[2][1] */ .1715,
    /* rk[2][2] */ 0.,
    /* rk[3][0] */ 0.,
    /* rk[3][1] */ .1862,
    /* rk[3][2] */ 0.,
    /* rk[4][0] */ -.035902,
    /* rk[4][1] */ .051347,
    /* rk[4][2] */ -.005539,
    /* rk[5][0] */ -.026917,
    /* rk[5][1] */ -.0185,
    /* rk[5][2] */ -.005139,
    /* rk[6][0] */ .002,
    /* rk[6][1] */ .1715,
    /* rk[6][2] */ 0.,
    /* rk[7][0] */ 0.,
    /* rk[7][1] */ .1862,
    /* rk[7][2] */ 0.,
    /* rk[8][0] */ -.035902,
    /* rk[8][1] */ .051347,
    /* rk[8][2] */ .005539,
    /* rk[9][0] */ -.026917,
    /* rk[9][1] */ -.0185,
    /* rk[9][2] */ .005139,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ .127,
    /* ri[1][2] */ 0.,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ -.07,
    /* ri[2][2] */ .0935,
    /* ri[3][0] */ .0033,
    /* ri[3][1] */ -.2294,
    /* ri[3][2] */ 0.,
    /* ri[4][0] */ 0.,
    /* ri[4][1] */ -.2438,
    /* ri[4][2] */ 0.,
    /* ri[5][0] */ .098032,
    /* ri[5][1] */ -.038,
    /* ri[5][2] */ .018078,
    /* ri[6][0] */ 0.,
    /* ri[6][1] */ -.07,
    /* ri[6][2] */ -.0935,
    /* ri[7][0] */ .0033,
    /* ri[7][1] */ -.2294,
    /* ri[7][2] */ 0.,
    /* ri[8][0] */ 0.,
    /* ri[8][1] */ -.2438,
    /* ri[8][2] */ 0.,
    /* ri[9][0] */ .098032,
    /* ri[9][1] */ -.038,
    /* ri[9][2] */ -.018078,

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
    /* pres[9] */ 0.,
    /* pres[10] */ 0.,
    /* pres[11] */ 0.,
    /* pres[12] */ 0.,
    /* pres[13] */ 0.,
    /* pres[14] */ 0.,
    /* pres[15] */ 0.,
    /* pres[16] */ 0.,
    /* pres[17] */ 0.,
    /* pres[18] */ 0.,
    /* pres[19] */ 0.,
    /* pres[20] */ 0.,
    /* pres[21] */ 0.,
    /* pres[22] */ 0.,
    /* pres[23] */ 0.,
    /* pres[24] */ 0.,
    /* pres[25] */ 0.,
    /* pres[26] */ 0.,
    /* pres[27] */ 0.,
    /* pres[28] */ 0.,
    /* pres[29] */ 0.,
    /* pres[30] */ 0.,
    /* pres[31] */ 0.,
    /* pres[32] */ 0.,

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
    /* mmap[9] */ 9,
    /* mmap[10] */ 10,
    /* mmap[11] */ 11,
    /* mmap[12] */ 12,
    /* mmap[13] */ 13,
    /* mmap[14] */ 14,
    /* mmap[15] */ 15,
    /* mmap[16] */ 16,
    /* mmap[17] */ 17,
    /* mmap[18] */ 18,
    /* mmap[19] */ 19,
    /* mmap[20] */ 20,
    /* mmap[21] */ 21,
    /* mmap[22] */ 22,
    /* mmap[23] */ 23,
    /* mmap[24] */ 24,
    /* mmap[25] */ 25,
    /* mmap[26] */ 26,
    /* mmap[27] */ 27,
    /* mmap[28] */ 28,
    /* mmap[29] */ 29,
    /* mmap[30] */ 30,
    /* mmap[31] */ 31,
    /* mmap[32] */ 32,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 1,
    /* gravq[1] */ 1,
    /* gravq[2] */ 1,
    /* mkq[0] */ 0,
    /* mkq[1] */ 0,
    /* mkq[2] */ 0,
    /* mkq[3] */ 0,
    /* mkq[4] */ 0,
    /* mkq[5] */ 0,
    /* mkq[6] */ 0,
    /* mkq[7] */ 0,
    /* mkq[8] */ 0,
    /* mkq[9] */ 0,
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
    /* ikq[7][0][0] */ 0,
    /* ikq[7][0][1] */ 0,
    /* ikq[7][0][2] */ 0,
    /* ikq[7][1][0] */ 0,
    /* ikq[7][1][1] */ 0,
    /* ikq[7][1][2] */ 0,
    /* ikq[7][2][0] */ 0,
    /* ikq[7][2][1] */ 0,
    /* ikq[7][2][2] */ 0,
    /* ikq[8][0][0] */ 0,
    /* ikq[8][0][1] */ 0,
    /* ikq[8][0][2] */ 0,
    /* ikq[8][1][0] */ 0,
    /* ikq[8][1][1] */ 0,
    /* ikq[8][1][2] */ 0,
    /* ikq[8][2][0] */ 0,
    /* ikq[8][2][1] */ 0,
    /* ikq[8][2][2] */ 0,
    /* ikq[9][0][0] */ 0,
    /* ikq[9][0][1] */ 0,
    /* ikq[9][0][2] */ 0,
    /* ikq[9][1][0] */ 0,
    /* ikq[9][1][1] */ 0,
    /* ikq[9][1][2] */ 0,
    /* ikq[9][2][0] */ 0,
    /* ikq[9][2][1] */ 0,
    /* ikq[9][2][2] */ 0,
    /* pinq[0][0] */ 3,
    /* pinq[0][1] */ 3,
    /* pinq[0][2] */ 3,
    /* pinq[1][0] */ 3,
    /* pinq[1][1] */ 3,
    /* pinq[1][2] */ 3,
    /* pinq[2][0] */ 3,
    /* pinq[2][1] */ 3,
    /* pinq[2][2] */ 3,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* pinq[6][0] */ 3,
    /* pinq[6][1] */ 3,
    /* pinq[6][2] */ 3,
    /* pinq[7][0] */ 3,
    /* pinq[7][1] */ 3,
    /* pinq[7][2] */ 3,
    /* pinq[8][0] */ 3,
    /* pinq[8][1] */ 3,
    /* pinq[8][2] */ 3,
    /* pinq[9][0] */ 3,
    /* pinq[9][1] */ 3,
    /* pinq[9][2] */ 3,
    /* pinq[10][0] */ 3,
    /* pinq[10][1] */ 3,
    /* pinq[10][2] */ 3,
    /* pinq[11][0] */ 3,
    /* pinq[11][1] */ 3,
    /* pinq[11][2] */ 3,
    /* pinq[12][0] */ 3,
    /* pinq[12][1] */ 3,
    /* pinq[12][2] */ 3,
    /* pinq[13][0] */ 3,
    /* pinq[13][1] */ 3,
    /* pinq[13][2] */ 3,
    /* pinq[14][0] */ 3,
    /* pinq[14][1] */ 3,
    /* pinq[14][2] */ 3,
    /* pinq[15][0] */ 3,
    /* pinq[15][1] */ 3,
    /* pinq[15][2] */ 3,
    /* pinq[16][0] */ 3,
    /* pinq[16][1] */ 3,
    /* pinq[16][2] */ 3,
    /* pinq[17][0] */ 3,
    /* pinq[17][1] */ 3,
    /* pinq[17][2] */ 3,
    /* pinq[18][0] */ 3,
    /* pinq[18][1] */ 3,
    /* pinq[18][2] */ 3,
    /* pinq[19][0] */ 3,
    /* pinq[19][1] */ 3,
    /* pinq[19][2] */ 3,
    /* pinq[20][0] */ 3,
    /* pinq[20][1] */ 3,
    /* pinq[20][2] */ 3,
    /* pinq[21][0] */ 3,
    /* pinq[21][1] */ 3,
    /* pinq[21][2] */ 3,
    /* pinq[22][0] */ 3,
    /* pinq[22][1] */ 3,
    /* pinq[22][2] */ 3,
    /* pinq[23][0] */ 3,
    /* pinq[23][1] */ 3,
    /* pinq[23][2] */ 3,
    /* pinq[24][0] */ 3,
    /* pinq[24][1] */ 3,
    /* pinq[24][2] */ 3,
    /* pinq[25][0] */ 3,
    /* pinq[25][1] */ 3,
    /* pinq[25][2] */ 3,
    /* pinq[26][0] */ 3,
    /* pinq[26][1] */ 3,
    /* pinq[26][2] */ 3,
    /* pinq[27][0] */ 3,
    /* pinq[27][1] */ 3,
    /* pinq[27][2] */ 3,
    /* pinq[28][0] */ 3,
    /* pinq[28][1] */ 3,
    /* pinq[28][2] */ 3,
    /* pinq[29][0] */ 3,
    /* pinq[29][1] */ 3,
    /* pinq[29][2] */ 3,
    /* pinq[30][0] */ 3,
    /* pinq[30][1] */ 3,
    /* pinq[30][2] */ 3,
    /* pinq[31][0] */ 3,
    /* pinq[31][1] */ 3,
    /* pinq[31][2] */ 3,
    /* pinq[32][0] */ 3,
    /* pinq[32][1] */ 3,
    /* pinq[32][2] */ 3,
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
    /* rkq[7][0] */ 0,
    /* rkq[7][1] */ 0,
    /* rkq[7][2] */ 0,
    /* rkq[8][0] */ 0,
    /* rkq[8][1] */ 0,
    /* rkq[8][2] */ 0,
    /* rkq[9][0] */ 0,
    /* rkq[9][1] */ 0,
    /* rkq[9][2] */ 0,
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
    /* riq[7][0] */ 0,
    /* riq[7][1] */ 0,
    /* riq[7][2] */ 0,
    /* riq[8][0] */ 0,
    /* riq[8][1] */ 0,
    /* riq[8][2] */ 0,
    /* riq[9][0] */ 0,
    /* riq[9][1] */ 0,
    /* riq[9][2] */ 0,
    /* presq[0] */ 3,
    /* presq[1] */ 3,
    /* presq[2] */ 3,
    /* presq[3] */ 3,
    /* presq[4] */ 3,
    /* presq[5] */ 3,
    /* presq[6] */ 3,
    /* presq[7] */ 3,
    /* presq[8] */ 3,
    /* presq[9] */ 3,
    /* presq[10] */ 3,
    /* presq[11] */ 3,
    /* presq[12] */ 3,
    /* presq[13] */ 3,
    /* presq[14] */ 3,
    /* presq[15] */ 3,
    /* presq[16] */ 3,
    /* presq[17] */ 3,
    /* presq[18] */ 3,
    /* presq[19] */ 3,
    /* presq[20] */ 3,
    /* presq[21] */ 3,
    /* presq[22] */ 3,
    /* presq[23] */ 3,
    /* presq[24] */ 3,
    /* presq[25] */ 3,
    /* presq[26] */ 3,
    /* presq[27] */ 3,
    /* presq[28] */ 3,
    /* presq[29] */ 3,
    /* presq[30] */ 3,
    /* presq[31] */ 3,
    /* presq[32] */ 3,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
sdgstate_t sdgstate;
sdglhs_t sdglhs;
sdgrhs_t sdgrhs;
sdgtemp_t sdgtemp;


void sdinit(void)
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
    for (k = 0; k < 10; k++) {
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
    for (k = 0; k < 33; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */

    sumsq = ((pin[0][2]*pin[0][2])+((pin[0][0]*pin[0][0])+(pin[0][1]*pin[0][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[0][0] = (norminv*pin[0][0]);
    pin[0][1] = (norminv*pin[0][1]);
    pin[0][2] = (norminv*pin[0][2]);
    sumsq = ((pin[1][2]*pin[1][2])+((pin[1][0]*pin[1][0])+(pin[1][1]*pin[1][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[1][0] = (norminv*pin[1][0]);
    pin[1][1] = (norminv*pin[1][1]);
    pin[1][2] = (norminv*pin[1][2]);
    sumsq = ((pin[2][2]*pin[2][2])+((pin[2][0]*pin[2][0])+(pin[2][1]*pin[2][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[2][0] = (norminv*pin[2][0]);
    pin[2][1] = (norminv*pin[2][1]);
    pin[2][2] = (norminv*pin[2][2]);
    sumsq = ((pin[6][2]*pin[6][2])+((pin[6][0]*pin[6][0])+(pin[6][1]*pin[6][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[6][0] = (norminv*pin[6][0]);
    pin[6][1] = (norminv*pin[6][1]);
    pin[6][2] = (norminv*pin[6][2]);
    sumsq = ((pin[7][2]*pin[7][2])+((pin[7][0]*pin[7][0])+(pin[7][1]*pin[7][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[7][0] = (norminv*pin[7][0]);
    pin[7][1] = (norminv*pin[7][1]);
    pin[7][2] = (norminv*pin[7][2]);
    sumsq = ((pin[8][2]*pin[8][2])+((pin[8][0]*pin[8][0])+(pin[8][1]*pin[8][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[8][0] = (norminv*pin[8][0]);
    pin[8][1] = (norminv*pin[8][1]);
    pin[8][2] = (norminv*pin[8][2]);
    sumsq = ((pin[9][2]*pin[9][2])+((pin[9][0]*pin[9][0])+(pin[9][1]*pin[9][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[9][0] = (norminv*pin[9][0]);
    pin[9][1] = (norminv*pin[9][1]);
    pin[9][2] = (norminv*pin[9][2]);
    sumsq = ((pin[10][2]*pin[10][2])+((pin[10][0]*pin[10][0])+(pin[10][1]*
      pin[10][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[10][0] = (norminv*pin[10][0]);
    pin[10][1] = (norminv*pin[10][1]);
    pin[10][2] = (norminv*pin[10][2]);
    sumsq = ((pin[11][2]*pin[11][2])+((pin[11][0]*pin[11][0])+(pin[11][1]*
      pin[11][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[11][0] = (norminv*pin[11][0]);
    pin[11][1] = (norminv*pin[11][1]);
    pin[11][2] = (norminv*pin[11][2]);
    sumsq = ((pin[12][2]*pin[12][2])+((pin[12][0]*pin[12][0])+(pin[12][1]*
      pin[12][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[12][0] = (norminv*pin[12][0]);
    pin[12][1] = (norminv*pin[12][1]);
    pin[12][2] = (norminv*pin[12][2]);
    sumsq = ((pin[13][2]*pin[13][2])+((pin[13][0]*pin[13][0])+(pin[13][1]*
      pin[13][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[13][0] = (norminv*pin[13][0]);
    pin[13][1] = (norminv*pin[13][1]);
    pin[13][2] = (norminv*pin[13][2]);
    sumsq = ((pin[14][2]*pin[14][2])+((pin[14][0]*pin[14][0])+(pin[14][1]*
      pin[14][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[14][0] = (norminv*pin[14][0]);
    pin[14][1] = (norminv*pin[14][1]);
    pin[14][2] = (norminv*pin[14][2]);
    sumsq = ((pin[15][2]*pin[15][2])+((pin[15][0]*pin[15][0])+(pin[15][1]*
      pin[15][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[15][0] = (norminv*pin[15][0]);
    pin[15][1] = (norminv*pin[15][1]);
    pin[15][2] = (norminv*pin[15][2]);
    sumsq = ((pin[16][2]*pin[16][2])+((pin[16][0]*pin[16][0])+(pin[16][1]*
      pin[16][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[16][0] = (norminv*pin[16][0]);
    pin[16][1] = (norminv*pin[16][1]);
    pin[16][2] = (norminv*pin[16][2]);
    sumsq = ((pin[17][2]*pin[17][2])+((pin[17][0]*pin[17][0])+(pin[17][1]*
      pin[17][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[17][0] = (norminv*pin[17][0]);
    pin[17][1] = (norminv*pin[17][1]);
    pin[17][2] = (norminv*pin[17][2]);
    sumsq = ((pin[18][2]*pin[18][2])+((pin[18][0]*pin[18][0])+(pin[18][1]*
      pin[18][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[18][0] = (norminv*pin[18][0]);
    pin[18][1] = (norminv*pin[18][1]);
    pin[18][2] = (norminv*pin[18][2]);
    sumsq = ((pin[19][2]*pin[19][2])+((pin[19][0]*pin[19][0])+(pin[19][1]*
      pin[19][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[19][0] = (norminv*pin[19][0]);
    pin[19][1] = (norminv*pin[19][1]);
    pin[19][2] = (norminv*pin[19][2]);
    sumsq = ((pin[20][2]*pin[20][2])+((pin[20][0]*pin[20][0])+(pin[20][1]*
      pin[20][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[20][0] = (norminv*pin[20][0]);
    pin[20][1] = (norminv*pin[20][1]);
    pin[20][2] = (norminv*pin[20][2]);
    sumsq = ((pin[21][2]*pin[21][2])+((pin[21][0]*pin[21][0])+(pin[21][1]*
      pin[21][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[21][0] = (norminv*pin[21][0]);
    pin[21][1] = (norminv*pin[21][1]);
    pin[21][2] = (norminv*pin[21][2]);
    sumsq = ((pin[22][2]*pin[22][2])+((pin[22][0]*pin[22][0])+(pin[22][1]*
      pin[22][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[22][0] = (norminv*pin[22][0]);
    pin[22][1] = (norminv*pin[22][1]);
    pin[22][2] = (norminv*pin[22][2]);
    sumsq = ((pin[23][2]*pin[23][2])+((pin[23][0]*pin[23][0])+(pin[23][1]*
      pin[23][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[23][0] = (norminv*pin[23][0]);
    pin[23][1] = (norminv*pin[23][1]);
    pin[23][2] = (norminv*pin[23][2]);
    sumsq = ((pin[24][2]*pin[24][2])+((pin[24][0]*pin[24][0])+(pin[24][1]*
      pin[24][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[24][0] = (norminv*pin[24][0]);
    pin[24][1] = (norminv*pin[24][1]);
    pin[24][2] = (norminv*pin[24][2]);
    sumsq = ((pin[25][2]*pin[25][2])+((pin[25][0]*pin[25][0])+(pin[25][1]*
      pin[25][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[25][0] = (norminv*pin[25][0]);
    pin[25][1] = (norminv*pin[25][1]);
    pin[25][2] = (norminv*pin[25][2]);
    sumsq = ((pin[26][2]*pin[26][2])+((pin[26][0]*pin[26][0])+(pin[26][1]*
      pin[26][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[26][0] = (norminv*pin[26][0]);
    pin[26][1] = (norminv*pin[26][1]);
    pin[26][2] = (norminv*pin[26][2]);
    sumsq = ((pin[27][2]*pin[27][2])+((pin[27][0]*pin[27][0])+(pin[27][1]*
      pin[27][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[27][0] = (norminv*pin[27][0]);
    pin[27][1] = (norminv*pin[27][1]);
    pin[27][2] = (norminv*pin[27][2]);
    sumsq = ((pin[28][2]*pin[28][2])+((pin[28][0]*pin[28][0])+(pin[28][1]*
      pin[28][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[28][0] = (norminv*pin[28][0]);
    pin[28][1] = (norminv*pin[28][1]);
    pin[28][2] = (norminv*pin[28][2]);
    sumsq = ((pin[29][2]*pin[29][2])+((pin[29][0]*pin[29][0])+(pin[29][1]*
      pin[29][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[29][0] = (norminv*pin[29][0]);
    pin[29][1] = (norminv*pin[29][1]);
    pin[29][2] = (norminv*pin[29][2]);
    sumsq = ((pin[30][2]*pin[30][2])+((pin[30][0]*pin[30][0])+(pin[30][1]*
      pin[30][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[30][0] = (norminv*pin[30][0]);
    pin[30][1] = (norminv*pin[30][1]);
    pin[30][2] = (norminv*pin[30][2]);
    sumsq = ((pin[31][2]*pin[31][2])+((pin[31][0]*pin[31][0])+(pin[31][1]*
      pin[31][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[31][0] = (norminv*pin[31][0]);
    pin[31][1] = (norminv*pin[31][1]);
    pin[31][2] = (norminv*pin[31][2]);
    sumsq = ((pin[32][2]*pin[32][2])+((pin[32][0]*pin[32][0])+(pin[32][1]*
      pin[32][1])));
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[32][0] = (norminv*pin[32][0]);
    pin[32][1] = (norminv*pin[32][1]);
    pin[32][2] = (norminv*pin[32][2]);

/* Zero out Vpk and Wpk */

    for (i = 0; i < 33; i++) {
        for (j = i; j <= 32; j++) {
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
    rcom[7][0] = 0.;
    rcom[7][1] = 0.;
    rcom[7][2] = 0.;
    rcom[8][0] = 0.;
    rcom[8][1] = 0.;
    rcom[8][2] = 0.;
    rcom[9][0] = 0.;
    rcom[9][1] = 0.;
    rcom[9][2] = 0.;
    rkWkk[11][2] = ((.002*pin[11][1])-(.1715*pin[11][0]));
    rkWkk[17][0] = ((.005539*pin[17][1])+(.051347*pin[17][2]));
    rkWkk[17][1] = ((.035902*pin[17][2])-(.005539*pin[17][0]));
    rkWkk[17][2] = -((.035902*pin[17][1])+(.051347*pin[17][0]));
    rkWkk[20][0] = ((.005139*pin[20][1])-(.0185*pin[20][2]));
    rkWkk[20][1] = ((.026917*pin[20][2])-(.005139*pin[20][0]));
    rkWkk[20][2] = ((.0185*pin[20][0])-(.026917*pin[20][1]));
    rkWkk[23][2] = ((.002*pin[23][1])-(.1715*pin[23][0]));
    rkWkk[29][0] = ((.051347*pin[29][2])-(.005539*pin[29][1]));
    rkWkk[29][1] = ((.005539*pin[29][0])+(.035902*pin[29][2]));
    rkWkk[29][2] = -((.035902*pin[29][1])+(.051347*pin[29][0]));
    rkWkk[32][0] = -((.005139*pin[32][1])+(.0185*pin[32][2]));
    rkWkk[32][1] = ((.005139*pin[32][0])+(.026917*pin[32][2]));
    rkWkk[32][2] = ((.0185*pin[32][0])-(.026917*pin[32][1]));

/* Compute mass properties-related constants */

    mtot = 71.005252;
    sdserialno(&i);
    if (i != 30123) {
        sdseterr(7,41);
    }
    roustate = 1;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void sdst2ang(double st[34],
    double stang[33])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 33; i++) {
        stang[i] = st[i];
    }
    sdquat2dc(st[3],st[4],st[5],st[33],dc);
    sddc2ang(dc,&stang[3],&stang[4],&stang[5]);
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void sdang2st(double stang[33],
    double st[34])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 33; i++) {
        st[i] = stang[i];
    }
    sdang2dc(stang[3],stang[4],stang[5],dc);
    sddc2quat(dc,&st[3],&st[4],&st[5],&st[33]);
}

/* Normalize Euler parameters in state. */

void sdnrmsterr(double st[34],
    double normst[34],
    int routine)
{
    int i;
    double norm;

    for (i = 0; i < 34; i++) {
        normst[i] = st[i];
    }
    norm = sqrt(st[3]*st[3]+st[4]*st[4]+st[5]*st[5]+st[33]*st[33]);
    if (routine != 0) {
        if ((norm < .9) || (norm > 1.1)) {
            sdseterr(routine,14);
        }
    }
    if (norm == 0.) {
        normst[33] = 1.;
        norm = 1.;
    }
    norm = 1./norm;
    normst[3] = normst[3]*norm;
    normst[4] = normst[4]*norm;
    normst[5] = normst[5]*norm;
    normst[33] = normst[33]*norm;
}

void sdnormst(double st[34],
    double normst[34])
{

    sdnrmsterr(st,normst,0);
}

void sdstate(double timein,
    double qin[34],
    double uin[33])
{
/*
Compute kinematic information and store it in sdgstate.

Generated 15-Feb-2006 17:06:53 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;
    double ee,stab;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 33; i++) {
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
        for (i = 0; i < 34; i++) {
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
        for (i = 0; i < 33; i++) {
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
    for (i = 0; i < 34; i++) {
        q[i] = qin[i];
    }
/*
Normalize Euler parameters in state
*/
    sdnrmsterr(q,qn,8);
/*
Compute sines and cosines of q
*/
    s6 = sin(q[6]);
    c6 = cos(q[6]);
    s7 = sin(q[7]);
    c7 = cos(q[7]);
    s8 = sin(q[8]);
    c8 = cos(q[8]);
    s9 = sin(q[9]);
    c9 = cos(q[9]);
    s10 = sin(q[10]);
    c10 = cos(q[10]);
    s11 = sin(q[11]);
    c11 = cos(q[11]);
    s12 = sin(q[12]);
    c12 = cos(q[12]);
    s13 = sin(q[13]);
    c13 = cos(q[13]);
    s14 = sin(q[14]);
    c14 = cos(q[14]);
    s15 = sin(q[15]);
    c15 = cos(q[15]);
    s16 = sin(q[16]);
    c16 = cos(q[16]);
    s17 = sin(q[17]);
    c17 = cos(q[17]);
    s18 = sin(q[18]);
    c18 = cos(q[18]);
    s19 = sin(q[19]);
    c19 = cos(q[19]);
    s20 = sin(q[20]);
    c20 = cos(q[20]);
    s21 = sin(q[21]);
    c21 = cos(q[21]);
    s22 = sin(q[22]);
    c22 = cos(q[22]);
    s23 = sin(q[23]);
    c23 = cos(q[23]);
    s24 = sin(q[24]);
    c24 = cos(q[24]);
    s25 = sin(q[25]);
    c25 = cos(q[25]);
    s26 = sin(q[26]);
    c26 = cos(q[26]);
    s27 = sin(q[27]);
    c27 = cos(q[27]);
    s28 = sin(q[28]);
    c28 = cos(q[28]);
    s29 = sin(q[29]);
    c29 = cos(q[29]);
    s30 = sin(q[30]);
    c30 = cos(q[30]);
    s31 = sin(q[31]);
    c31 = cos(q[31]);
    s32 = sin(q[32]);
    c32 = cos(q[32]);
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (1.-(2.*((qn[4]*qn[4])+(qn[5]*qn[5]))));
    Cik[3][0][1] = (2.*((qn[3]*qn[4])-(qn[5]*qn[33])));
    Cik[3][0][2] = (2.*((qn[3]*qn[5])+(qn[4]*qn[33])));
    Cik[3][1][0] = (2.*((qn[3]*qn[4])+(qn[5]*qn[33])));
    Cik[3][1][1] = (1.-(2.*((qn[3]*qn[3])+(qn[5]*qn[5]))));
    Cik[3][1][2] = (2.*((qn[4]*qn[5])-(qn[3]*qn[33])));
    Cik[3][2][0] = (2.*((qn[3]*qn[5])-(qn[4]*qn[33])));
    Cik[3][2][1] = (2.*((qn[3]*qn[33])+(qn[4]*qn[5])));
    Cik[3][2][2] = (1.-(2.*((qn[3]*qn[3])+(qn[4]*qn[4]))));
    Cik[6][0][0] = ((pin[6][0]*pin[6][0])+(c6*(1.-(pin[6][0]*pin[6][0]))));
    Cik[6][0][1] = (((pin[6][0]*pin[6][1])-(pin[6][2]*s6))-(c6*(pin[6][0]*
      pin[6][1])));
    Cik[6][0][2] = (((pin[6][0]*pin[6][2])+(pin[6][1]*s6))-(c6*(pin[6][0]*
      pin[6][2])));
    Cik[6][1][0] = (((pin[6][0]*pin[6][1])+(pin[6][2]*s6))-(c6*(pin[6][0]*
      pin[6][1])));
    Cik[6][1][1] = ((pin[6][1]*pin[6][1])+(c6*(1.-(pin[6][1]*pin[6][1]))));
    Cik[6][1][2] = (((pin[6][1]*pin[6][2])-(pin[6][0]*s6))-(c6*(pin[6][1]*
      pin[6][2])));
    Cik[6][2][0] = (((pin[6][0]*pin[6][2])-(pin[6][1]*s6))-(c6*(pin[6][0]*
      pin[6][2])));
    Cik[6][2][1] = (((pin[6][0]*s6)+(pin[6][1]*pin[6][2]))-(c6*(pin[6][1]*
      pin[6][2])));
    Cik[6][2][2] = ((pin[6][2]*pin[6][2])+(c6*(1.-(pin[6][2]*pin[6][2]))));
    Cik[7][0][0] = ((pin[7][0]*pin[7][0])+(c7*(1.-(pin[7][0]*pin[7][0]))));
    Cik[7][0][1] = (((pin[7][0]*pin[7][1])-(pin[7][2]*s7))-(c7*(pin[7][0]*
      pin[7][1])));
    Cik[7][0][2] = (((pin[7][0]*pin[7][2])+(pin[7][1]*s7))-(c7*(pin[7][0]*
      pin[7][2])));
    Cik[7][1][0] = (((pin[7][0]*pin[7][1])+(pin[7][2]*s7))-(c7*(pin[7][0]*
      pin[7][1])));
    Cik[7][1][1] = ((pin[7][1]*pin[7][1])+(c7*(1.-(pin[7][1]*pin[7][1]))));
    Cik[7][1][2] = (((pin[7][1]*pin[7][2])-(pin[7][0]*s7))-(c7*(pin[7][1]*
      pin[7][2])));
    Cik[7][2][0] = (((pin[7][0]*pin[7][2])-(pin[7][1]*s7))-(c7*(pin[7][0]*
      pin[7][2])));
    Cik[7][2][1] = (((pin[7][0]*s7)+(pin[7][1]*pin[7][2]))-(c7*(pin[7][1]*
      pin[7][2])));
    Cik[7][2][2] = ((pin[7][2]*pin[7][2])+(c7*(1.-(pin[7][2]*pin[7][2]))));
    Cik[8][0][0] = ((pin[8][0]*pin[8][0])+(c8*(1.-(pin[8][0]*pin[8][0]))));
    Cik[8][0][1] = (((pin[8][0]*pin[8][1])-(pin[8][2]*s8))-(c8*(pin[8][0]*
      pin[8][1])));
    Cik[8][0][2] = (((pin[8][0]*pin[8][2])+(pin[8][1]*s8))-(c8*(pin[8][0]*
      pin[8][2])));
    Cik[8][1][0] = (((pin[8][0]*pin[8][1])+(pin[8][2]*s8))-(c8*(pin[8][0]*
      pin[8][1])));
    Cik[8][1][1] = ((pin[8][1]*pin[8][1])+(c8*(1.-(pin[8][1]*pin[8][1]))));
    Cik[8][1][2] = (((pin[8][1]*pin[8][2])-(pin[8][0]*s8))-(c8*(pin[8][1]*
      pin[8][2])));
    Cik[8][2][0] = (((pin[8][0]*pin[8][2])-(pin[8][1]*s8))-(c8*(pin[8][0]*
      pin[8][2])));
    Cik[8][2][1] = (((pin[8][0]*s8)+(pin[8][1]*pin[8][2]))-(c8*(pin[8][1]*
      pin[8][2])));
    Cik[8][2][2] = ((pin[8][2]*pin[8][2])+(c8*(1.-(pin[8][2]*pin[8][2]))));
    Cik[9][0][0] = ((pin[9][0]*pin[9][0])+(c9*(1.-(pin[9][0]*pin[9][0]))));
    Cik[9][0][1] = (((pin[9][0]*pin[9][1])-(pin[9][2]*s9))-(c9*(pin[9][0]*
      pin[9][1])));
    Cik[9][0][2] = (((pin[9][0]*pin[9][2])+(pin[9][1]*s9))-(c9*(pin[9][0]*
      pin[9][2])));
    Cik[9][1][0] = (((pin[9][0]*pin[9][1])+(pin[9][2]*s9))-(c9*(pin[9][0]*
      pin[9][1])));
    Cik[9][1][1] = ((pin[9][1]*pin[9][1])+(c9*(1.-(pin[9][1]*pin[9][1]))));
    Cik[9][1][2] = (((pin[9][1]*pin[9][2])-(pin[9][0]*s9))-(c9*(pin[9][1]*
      pin[9][2])));
    Cik[9][2][0] = (((pin[9][0]*pin[9][2])-(pin[9][1]*s9))-(c9*(pin[9][0]*
      pin[9][2])));
    Cik[9][2][1] = (((pin[9][0]*s9)+(pin[9][1]*pin[9][2]))-(c9*(pin[9][1]*
      pin[9][2])));
    Cik[9][2][2] = ((pin[9][2]*pin[9][2])+(c9*(1.-(pin[9][2]*pin[9][2]))));
    Cik[10][0][0] = ((pin[10][0]*pin[10][0])+(c10*(1.-(pin[10][0]*pin[10][0]))))
      ;
    Cik[10][0][1] = (((pin[10][0]*pin[10][1])-(pin[10][2]*s10))-(c10*(pin[10][0]
      *pin[10][1])));
    Cik[10][0][2] = (((pin[10][0]*pin[10][2])+(pin[10][1]*s10))-(c10*(pin[10][0]
      *pin[10][2])));
    Cik[10][1][0] = (((pin[10][0]*pin[10][1])+(pin[10][2]*s10))-(c10*(pin[10][0]
      *pin[10][1])));
    Cik[10][1][1] = ((pin[10][1]*pin[10][1])+(c10*(1.-(pin[10][1]*pin[10][1]))))
      ;
    Cik[10][1][2] = (((pin[10][1]*pin[10][2])-(pin[10][0]*s10))-(c10*(pin[10][1]
      *pin[10][2])));
    Cik[10][2][0] = (((pin[10][0]*pin[10][2])-(pin[10][1]*s10))-(c10*(pin[10][0]
      *pin[10][2])));
    Cik[10][2][1] = (((pin[10][0]*s10)+(pin[10][1]*pin[10][2]))-(c10*(pin[10][1]
      *pin[10][2])));
    Cik[10][2][2] = ((pin[10][2]*pin[10][2])+(c10*(1.-(pin[10][2]*pin[10][2]))))
      ;
    Cik[11][0][0] = ((pin[11][0]*pin[11][0])+(c11*(1.-(pin[11][0]*pin[11][0]))))
      ;
    Cik[11][0][1] = (((pin[11][0]*pin[11][1])-(pin[11][2]*s11))-(c11*(pin[11][0]
      *pin[11][1])));
    Cik[11][0][2] = (((pin[11][0]*pin[11][2])+(pin[11][1]*s11))-(c11*(pin[11][0]
      *pin[11][2])));
    Cik[11][1][0] = (((pin[11][0]*pin[11][1])+(pin[11][2]*s11))-(c11*(pin[11][0]
      *pin[11][1])));
    Cik[11][1][1] = ((pin[11][1]*pin[11][1])+(c11*(1.-(pin[11][1]*pin[11][1]))))
      ;
    Cik[11][1][2] = (((pin[11][1]*pin[11][2])-(pin[11][0]*s11))-(c11*(pin[11][1]
      *pin[11][2])));
    Cik[11][2][0] = (((pin[11][0]*pin[11][2])-(pin[11][1]*s11))-(c11*(pin[11][0]
      *pin[11][2])));
    Cik[11][2][1] = (((pin[11][0]*s11)+(pin[11][1]*pin[11][2]))-(c11*(pin[11][1]
      *pin[11][2])));
    Cik[11][2][2] = ((pin[11][2]*pin[11][2])+(c11*(1.-(pin[11][2]*pin[11][2]))))
      ;
    Cik[12][0][0] = ((pin[12][0]*pin[12][0])+(c12*(1.-(pin[12][0]*pin[12][0]))))
      ;
    Cik[12][0][1] = (((pin[12][0]*pin[12][1])-(pin[12][2]*s12))-(c12*(pin[12][0]
      *pin[12][1])));
    Cik[12][0][2] = (((pin[12][0]*pin[12][2])+(pin[12][1]*s12))-(c12*(pin[12][0]
      *pin[12][2])));
    Cik[12][1][0] = (((pin[12][0]*pin[12][1])+(pin[12][2]*s12))-(c12*(pin[12][0]
      *pin[12][1])));
    Cik[12][1][1] = ((pin[12][1]*pin[12][1])+(c12*(1.-(pin[12][1]*pin[12][1]))))
      ;
    Cik[12][1][2] = (((pin[12][1]*pin[12][2])-(pin[12][0]*s12))-(c12*(pin[12][1]
      *pin[12][2])));
    Cik[12][2][0] = (((pin[12][0]*pin[12][2])-(pin[12][1]*s12))-(c12*(pin[12][0]
      *pin[12][2])));
    Cik[12][2][1] = (((pin[12][0]*s12)+(pin[12][1]*pin[12][2]))-(c12*(pin[12][1]
      *pin[12][2])));
    Cik[12][2][2] = ((pin[12][2]*pin[12][2])+(c12*(1.-(pin[12][2]*pin[12][2]))))
      ;
    Cik[13][0][0] = ((pin[13][0]*pin[13][0])+(c13*(1.-(pin[13][0]*pin[13][0]))))
      ;
    Cik[13][0][1] = (((pin[13][0]*pin[13][1])-(pin[13][2]*s13))-(c13*(pin[13][0]
      *pin[13][1])));
    Cik[13][0][2] = (((pin[13][0]*pin[13][2])+(pin[13][1]*s13))-(c13*(pin[13][0]
      *pin[13][2])));
    Cik[13][1][0] = (((pin[13][0]*pin[13][1])+(pin[13][2]*s13))-(c13*(pin[13][0]
      *pin[13][1])));
    Cik[13][1][1] = ((pin[13][1]*pin[13][1])+(c13*(1.-(pin[13][1]*pin[13][1]))))
      ;
    Cik[13][1][2] = (((pin[13][1]*pin[13][2])-(pin[13][0]*s13))-(c13*(pin[13][1]
      *pin[13][2])));
    Cik[13][2][0] = (((pin[13][0]*pin[13][2])-(pin[13][1]*s13))-(c13*(pin[13][0]
      *pin[13][2])));
    Cik[13][2][1] = (((pin[13][0]*s13)+(pin[13][1]*pin[13][2]))-(c13*(pin[13][1]
      *pin[13][2])));
    Cik[13][2][2] = ((pin[13][2]*pin[13][2])+(c13*(1.-(pin[13][2]*pin[13][2]))))
      ;
    Cik[14][0][0] = ((pin[14][0]*pin[14][0])+(c14*(1.-(pin[14][0]*pin[14][0]))))
      ;
    Cik[14][0][1] = (((pin[14][0]*pin[14][1])-(pin[14][2]*s14))-(c14*(pin[14][0]
      *pin[14][1])));
    Cik[14][0][2] = (((pin[14][0]*pin[14][2])+(pin[14][1]*s14))-(c14*(pin[14][0]
      *pin[14][2])));
    Cik[14][1][0] = (((pin[14][0]*pin[14][1])+(pin[14][2]*s14))-(c14*(pin[14][0]
      *pin[14][1])));
    Cik[14][1][1] = ((pin[14][1]*pin[14][1])+(c14*(1.-(pin[14][1]*pin[14][1]))))
      ;
    Cik[14][1][2] = (((pin[14][1]*pin[14][2])-(pin[14][0]*s14))-(c14*(pin[14][1]
      *pin[14][2])));
    Cik[14][2][0] = (((pin[14][0]*pin[14][2])-(pin[14][1]*s14))-(c14*(pin[14][0]
      *pin[14][2])));
    Cik[14][2][1] = (((pin[14][0]*s14)+(pin[14][1]*pin[14][2]))-(c14*(pin[14][1]
      *pin[14][2])));
    Cik[14][2][2] = ((pin[14][2]*pin[14][2])+(c14*(1.-(pin[14][2]*pin[14][2]))))
      ;
    Cik[15][0][0] = ((pin[15][0]*pin[15][0])+(c15*(1.-(pin[15][0]*pin[15][0]))))
      ;
    Cik[15][0][1] = (((pin[15][0]*pin[15][1])-(pin[15][2]*s15))-(c15*(pin[15][0]
      *pin[15][1])));
    Cik[15][0][2] = (((pin[15][0]*pin[15][2])+(pin[15][1]*s15))-(c15*(pin[15][0]
      *pin[15][2])));
    Cik[15][1][0] = (((pin[15][0]*pin[15][1])+(pin[15][2]*s15))-(c15*(pin[15][0]
      *pin[15][1])));
    Cik[15][1][1] = ((pin[15][1]*pin[15][1])+(c15*(1.-(pin[15][1]*pin[15][1]))))
      ;
    Cik[15][1][2] = (((pin[15][1]*pin[15][2])-(pin[15][0]*s15))-(c15*(pin[15][1]
      *pin[15][2])));
    Cik[15][2][0] = (((pin[15][0]*pin[15][2])-(pin[15][1]*s15))-(c15*(pin[15][0]
      *pin[15][2])));
    Cik[15][2][1] = (((pin[15][0]*s15)+(pin[15][1]*pin[15][2]))-(c15*(pin[15][1]
      *pin[15][2])));
    Cik[15][2][2] = ((pin[15][2]*pin[15][2])+(c15*(1.-(pin[15][2]*pin[15][2]))))
      ;
    Cik[16][0][0] = ((pin[16][0]*pin[16][0])+(c16*(1.-(pin[16][0]*pin[16][0]))))
      ;
    Cik[16][0][1] = (((pin[16][0]*pin[16][1])-(pin[16][2]*s16))-(c16*(pin[16][0]
      *pin[16][1])));
    Cik[16][0][2] = (((pin[16][0]*pin[16][2])+(pin[16][1]*s16))-(c16*(pin[16][0]
      *pin[16][2])));
    Cik[16][1][0] = (((pin[16][0]*pin[16][1])+(pin[16][2]*s16))-(c16*(pin[16][0]
      *pin[16][1])));
    Cik[16][1][1] = ((pin[16][1]*pin[16][1])+(c16*(1.-(pin[16][1]*pin[16][1]))))
      ;
    Cik[16][1][2] = (((pin[16][1]*pin[16][2])-(pin[16][0]*s16))-(c16*(pin[16][1]
      *pin[16][2])));
    Cik[16][2][0] = (((pin[16][0]*pin[16][2])-(pin[16][1]*s16))-(c16*(pin[16][0]
      *pin[16][2])));
    Cik[16][2][1] = (((pin[16][0]*s16)+(pin[16][1]*pin[16][2]))-(c16*(pin[16][1]
      *pin[16][2])));
    Cik[16][2][2] = ((pin[16][2]*pin[16][2])+(c16*(1.-(pin[16][2]*pin[16][2]))))
      ;
    Cik[17][0][0] = ((pin[17][0]*pin[17][0])+(c17*(1.-(pin[17][0]*pin[17][0]))))
      ;
    Cik[17][0][1] = (((pin[17][0]*pin[17][1])-(pin[17][2]*s17))-(c17*(pin[17][0]
      *pin[17][1])));
    Cik[17][0][2] = (((pin[17][0]*pin[17][2])+(pin[17][1]*s17))-(c17*(pin[17][0]
      *pin[17][2])));
    Cik[17][1][0] = (((pin[17][0]*pin[17][1])+(pin[17][2]*s17))-(c17*(pin[17][0]
      *pin[17][1])));
    Cik[17][1][1] = ((pin[17][1]*pin[17][1])+(c17*(1.-(pin[17][1]*pin[17][1]))))
      ;
    Cik[17][1][2] = (((pin[17][1]*pin[17][2])-(pin[17][0]*s17))-(c17*(pin[17][1]
      *pin[17][2])));
    Cik[17][2][0] = (((pin[17][0]*pin[17][2])-(pin[17][1]*s17))-(c17*(pin[17][0]
      *pin[17][2])));
    Cik[17][2][1] = (((pin[17][0]*s17)+(pin[17][1]*pin[17][2]))-(c17*(pin[17][1]
      *pin[17][2])));
    Cik[17][2][2] = ((pin[17][2]*pin[17][2])+(c17*(1.-(pin[17][2]*pin[17][2]))))
      ;
    Cik[18][0][0] = ((pin[18][0]*pin[18][0])+(c18*(1.-(pin[18][0]*pin[18][0]))))
      ;
    Cik[18][0][1] = (((pin[18][0]*pin[18][1])-(pin[18][2]*s18))-(c18*(pin[18][0]
      *pin[18][1])));
    Cik[18][0][2] = (((pin[18][0]*pin[18][2])+(pin[18][1]*s18))-(c18*(pin[18][0]
      *pin[18][2])));
    Cik[18][1][0] = (((pin[18][0]*pin[18][1])+(pin[18][2]*s18))-(c18*(pin[18][0]
      *pin[18][1])));
    Cik[18][1][1] = ((pin[18][1]*pin[18][1])+(c18*(1.-(pin[18][1]*pin[18][1]))))
      ;
    Cik[18][1][2] = (((pin[18][1]*pin[18][2])-(pin[18][0]*s18))-(c18*(pin[18][1]
      *pin[18][2])));
    Cik[18][2][0] = (((pin[18][0]*pin[18][2])-(pin[18][1]*s18))-(c18*(pin[18][0]
      *pin[18][2])));
    Cik[18][2][1] = (((pin[18][0]*s18)+(pin[18][1]*pin[18][2]))-(c18*(pin[18][1]
      *pin[18][2])));
    Cik[18][2][2] = ((pin[18][2]*pin[18][2])+(c18*(1.-(pin[18][2]*pin[18][2]))))
      ;
    Cik[19][0][0] = ((pin[19][0]*pin[19][0])+(c19*(1.-(pin[19][0]*pin[19][0]))))
      ;
    Cik[19][0][1] = (((pin[19][0]*pin[19][1])-(pin[19][2]*s19))-(c19*(pin[19][0]
      *pin[19][1])));
    Cik[19][0][2] = (((pin[19][0]*pin[19][2])+(pin[19][1]*s19))-(c19*(pin[19][0]
      *pin[19][2])));
    Cik[19][1][0] = (((pin[19][0]*pin[19][1])+(pin[19][2]*s19))-(c19*(pin[19][0]
      *pin[19][1])));
    Cik[19][1][1] = ((pin[19][1]*pin[19][1])+(c19*(1.-(pin[19][1]*pin[19][1]))))
      ;
    Cik[19][1][2] = (((pin[19][1]*pin[19][2])-(pin[19][0]*s19))-(c19*(pin[19][1]
      *pin[19][2])));
    Cik[19][2][0] = (((pin[19][0]*pin[19][2])-(pin[19][1]*s19))-(c19*(pin[19][0]
      *pin[19][2])));
    Cik[19][2][1] = (((pin[19][0]*s19)+(pin[19][1]*pin[19][2]))-(c19*(pin[19][1]
      *pin[19][2])));
    Cik[19][2][2] = ((pin[19][2]*pin[19][2])+(c19*(1.-(pin[19][2]*pin[19][2]))))
      ;
    Cik[20][0][0] = ((pin[20][0]*pin[20][0])+(c20*(1.-(pin[20][0]*pin[20][0]))))
      ;
    Cik[20][0][1] = (((pin[20][0]*pin[20][1])-(pin[20][2]*s20))-(c20*(pin[20][0]
      *pin[20][1])));
    Cik[20][0][2] = (((pin[20][0]*pin[20][2])+(pin[20][1]*s20))-(c20*(pin[20][0]
      *pin[20][2])));
    Cik[20][1][0] = (((pin[20][0]*pin[20][1])+(pin[20][2]*s20))-(c20*(pin[20][0]
      *pin[20][1])));
    Cik[20][1][1] = ((pin[20][1]*pin[20][1])+(c20*(1.-(pin[20][1]*pin[20][1]))))
      ;
    Cik[20][1][2] = (((pin[20][1]*pin[20][2])-(pin[20][0]*s20))-(c20*(pin[20][1]
      *pin[20][2])));
    Cik[20][2][0] = (((pin[20][0]*pin[20][2])-(pin[20][1]*s20))-(c20*(pin[20][0]
      *pin[20][2])));
    Cik[20][2][1] = (((pin[20][0]*s20)+(pin[20][1]*pin[20][2]))-(c20*(pin[20][1]
      *pin[20][2])));
    Cik[20][2][2] = ((pin[20][2]*pin[20][2])+(c20*(1.-(pin[20][2]*pin[20][2]))))
      ;
    Cik[21][0][0] = ((pin[21][0]*pin[21][0])+(c21*(1.-(pin[21][0]*pin[21][0]))))
      ;
    Cik[21][0][1] = (((pin[21][0]*pin[21][1])-(pin[21][2]*s21))-(c21*(pin[21][0]
      *pin[21][1])));
    Cik[21][0][2] = (((pin[21][0]*pin[21][2])+(pin[21][1]*s21))-(c21*(pin[21][0]
      *pin[21][2])));
    Cik[21][1][0] = (((pin[21][0]*pin[21][1])+(pin[21][2]*s21))-(c21*(pin[21][0]
      *pin[21][1])));
    Cik[21][1][1] = ((pin[21][1]*pin[21][1])+(c21*(1.-(pin[21][1]*pin[21][1]))))
      ;
    Cik[21][1][2] = (((pin[21][1]*pin[21][2])-(pin[21][0]*s21))-(c21*(pin[21][1]
      *pin[21][2])));
    Cik[21][2][0] = (((pin[21][0]*pin[21][2])-(pin[21][1]*s21))-(c21*(pin[21][0]
      *pin[21][2])));
    Cik[21][2][1] = (((pin[21][0]*s21)+(pin[21][1]*pin[21][2]))-(c21*(pin[21][1]
      *pin[21][2])));
    Cik[21][2][2] = ((pin[21][2]*pin[21][2])+(c21*(1.-(pin[21][2]*pin[21][2]))))
      ;
    Cik[22][0][0] = ((pin[22][0]*pin[22][0])+(c22*(1.-(pin[22][0]*pin[22][0]))))
      ;
    Cik[22][0][1] = (((pin[22][0]*pin[22][1])-(pin[22][2]*s22))-(c22*(pin[22][0]
      *pin[22][1])));
    Cik[22][0][2] = (((pin[22][0]*pin[22][2])+(pin[22][1]*s22))-(c22*(pin[22][0]
      *pin[22][2])));
    Cik[22][1][0] = (((pin[22][0]*pin[22][1])+(pin[22][2]*s22))-(c22*(pin[22][0]
      *pin[22][1])));
    Cik[22][1][1] = ((pin[22][1]*pin[22][1])+(c22*(1.-(pin[22][1]*pin[22][1]))))
      ;
    Cik[22][1][2] = (((pin[22][1]*pin[22][2])-(pin[22][0]*s22))-(c22*(pin[22][1]
      *pin[22][2])));
    Cik[22][2][0] = (((pin[22][0]*pin[22][2])-(pin[22][1]*s22))-(c22*(pin[22][0]
      *pin[22][2])));
    Cik[22][2][1] = (((pin[22][0]*s22)+(pin[22][1]*pin[22][2]))-(c22*(pin[22][1]
      *pin[22][2])));
    Cik[22][2][2] = ((pin[22][2]*pin[22][2])+(c22*(1.-(pin[22][2]*pin[22][2]))))
      ;
    Cik[23][0][0] = ((pin[23][0]*pin[23][0])+(c23*(1.-(pin[23][0]*pin[23][0]))))
      ;
    Cik[23][0][1] = (((pin[23][0]*pin[23][1])-(pin[23][2]*s23))-(c23*(pin[23][0]
      *pin[23][1])));
    Cik[23][0][2] = (((pin[23][0]*pin[23][2])+(pin[23][1]*s23))-(c23*(pin[23][0]
      *pin[23][2])));
    Cik[23][1][0] = (((pin[23][0]*pin[23][1])+(pin[23][2]*s23))-(c23*(pin[23][0]
      *pin[23][1])));
    Cik[23][1][1] = ((pin[23][1]*pin[23][1])+(c23*(1.-(pin[23][1]*pin[23][1]))))
      ;
    Cik[23][1][2] = (((pin[23][1]*pin[23][2])-(pin[23][0]*s23))-(c23*(pin[23][1]
      *pin[23][2])));
    Cik[23][2][0] = (((pin[23][0]*pin[23][2])-(pin[23][1]*s23))-(c23*(pin[23][0]
      *pin[23][2])));
    Cik[23][2][1] = (((pin[23][0]*s23)+(pin[23][1]*pin[23][2]))-(c23*(pin[23][1]
      *pin[23][2])));
    Cik[23][2][2] = ((pin[23][2]*pin[23][2])+(c23*(1.-(pin[23][2]*pin[23][2]))))
      ;
    Cik[24][0][0] = ((pin[24][0]*pin[24][0])+(c24*(1.-(pin[24][0]*pin[24][0]))))
      ;
    Cik[24][0][1] = (((pin[24][0]*pin[24][1])-(pin[24][2]*s24))-(c24*(pin[24][0]
      *pin[24][1])));
    Cik[24][0][2] = (((pin[24][0]*pin[24][2])+(pin[24][1]*s24))-(c24*(pin[24][0]
      *pin[24][2])));
    Cik[24][1][0] = (((pin[24][0]*pin[24][1])+(pin[24][2]*s24))-(c24*(pin[24][0]
      *pin[24][1])));
    Cik[24][1][1] = ((pin[24][1]*pin[24][1])+(c24*(1.-(pin[24][1]*pin[24][1]))))
      ;
    Cik[24][1][2] = (((pin[24][1]*pin[24][2])-(pin[24][0]*s24))-(c24*(pin[24][1]
      *pin[24][2])));
    Cik[24][2][0] = (((pin[24][0]*pin[24][2])-(pin[24][1]*s24))-(c24*(pin[24][0]
      *pin[24][2])));
    Cik[24][2][1] = (((pin[24][0]*s24)+(pin[24][1]*pin[24][2]))-(c24*(pin[24][1]
      *pin[24][2])));
    Cik[24][2][2] = ((pin[24][2]*pin[24][2])+(c24*(1.-(pin[24][2]*pin[24][2]))))
      ;
    Cik[25][0][0] = ((pin[25][0]*pin[25][0])+(c25*(1.-(pin[25][0]*pin[25][0]))))
      ;
    Cik[25][0][1] = (((pin[25][0]*pin[25][1])-(pin[25][2]*s25))-(c25*(pin[25][0]
      *pin[25][1])));
    Cik[25][0][2] = (((pin[25][0]*pin[25][2])+(pin[25][1]*s25))-(c25*(pin[25][0]
      *pin[25][2])));
    Cik[25][1][0] = (((pin[25][0]*pin[25][1])+(pin[25][2]*s25))-(c25*(pin[25][0]
      *pin[25][1])));
    Cik[25][1][1] = ((pin[25][1]*pin[25][1])+(c25*(1.-(pin[25][1]*pin[25][1]))))
      ;
    Cik[25][1][2] = (((pin[25][1]*pin[25][2])-(pin[25][0]*s25))-(c25*(pin[25][1]
      *pin[25][2])));
    Cik[25][2][0] = (((pin[25][0]*pin[25][2])-(pin[25][1]*s25))-(c25*(pin[25][0]
      *pin[25][2])));
    Cik[25][2][1] = (((pin[25][0]*s25)+(pin[25][1]*pin[25][2]))-(c25*(pin[25][1]
      *pin[25][2])));
    Cik[25][2][2] = ((pin[25][2]*pin[25][2])+(c25*(1.-(pin[25][2]*pin[25][2]))))
      ;
    Cik[26][0][0] = ((pin[26][0]*pin[26][0])+(c26*(1.-(pin[26][0]*pin[26][0]))))
      ;
    Cik[26][0][1] = (((pin[26][0]*pin[26][1])-(pin[26][2]*s26))-(c26*(pin[26][0]
      *pin[26][1])));
    Cik[26][0][2] = (((pin[26][0]*pin[26][2])+(pin[26][1]*s26))-(c26*(pin[26][0]
      *pin[26][2])));
    Cik[26][1][0] = (((pin[26][0]*pin[26][1])+(pin[26][2]*s26))-(c26*(pin[26][0]
      *pin[26][1])));
    Cik[26][1][1] = ((pin[26][1]*pin[26][1])+(c26*(1.-(pin[26][1]*pin[26][1]))))
      ;
    Cik[26][1][2] = (((pin[26][1]*pin[26][2])-(pin[26][0]*s26))-(c26*(pin[26][1]
      *pin[26][2])));
    Cik[26][2][0] = (((pin[26][0]*pin[26][2])-(pin[26][1]*s26))-(c26*(pin[26][0]
      *pin[26][2])));
    Cik[26][2][1] = (((pin[26][0]*s26)+(pin[26][1]*pin[26][2]))-(c26*(pin[26][1]
      *pin[26][2])));
    Cik[26][2][2] = ((pin[26][2]*pin[26][2])+(c26*(1.-(pin[26][2]*pin[26][2]))))
      ;
    Cik[27][0][0] = ((pin[27][0]*pin[27][0])+(c27*(1.-(pin[27][0]*pin[27][0]))))
      ;
    Cik[27][0][1] = (((pin[27][0]*pin[27][1])-(pin[27][2]*s27))-(c27*(pin[27][0]
      *pin[27][1])));
    Cik[27][0][2] = (((pin[27][0]*pin[27][2])+(pin[27][1]*s27))-(c27*(pin[27][0]
      *pin[27][2])));
    Cik[27][1][0] = (((pin[27][0]*pin[27][1])+(pin[27][2]*s27))-(c27*(pin[27][0]
      *pin[27][1])));
    Cik[27][1][1] = ((pin[27][1]*pin[27][1])+(c27*(1.-(pin[27][1]*pin[27][1]))))
      ;
    Cik[27][1][2] = (((pin[27][1]*pin[27][2])-(pin[27][0]*s27))-(c27*(pin[27][1]
      *pin[27][2])));
    Cik[27][2][0] = (((pin[27][0]*pin[27][2])-(pin[27][1]*s27))-(c27*(pin[27][0]
      *pin[27][2])));
    Cik[27][2][1] = (((pin[27][0]*s27)+(pin[27][1]*pin[27][2]))-(c27*(pin[27][1]
      *pin[27][2])));
    Cik[27][2][2] = ((pin[27][2]*pin[27][2])+(c27*(1.-(pin[27][2]*pin[27][2]))))
      ;
    Cik[28][0][0] = ((pin[28][0]*pin[28][0])+(c28*(1.-(pin[28][0]*pin[28][0]))))
      ;
    Cik[28][0][1] = (((pin[28][0]*pin[28][1])-(pin[28][2]*s28))-(c28*(pin[28][0]
      *pin[28][1])));
    Cik[28][0][2] = (((pin[28][0]*pin[28][2])+(pin[28][1]*s28))-(c28*(pin[28][0]
      *pin[28][2])));
    Cik[28][1][0] = (((pin[28][0]*pin[28][1])+(pin[28][2]*s28))-(c28*(pin[28][0]
      *pin[28][1])));
    Cik[28][1][1] = ((pin[28][1]*pin[28][1])+(c28*(1.-(pin[28][1]*pin[28][1]))))
      ;
    Cik[28][1][2] = (((pin[28][1]*pin[28][2])-(pin[28][0]*s28))-(c28*(pin[28][1]
      *pin[28][2])));
    Cik[28][2][0] = (((pin[28][0]*pin[28][2])-(pin[28][1]*s28))-(c28*(pin[28][0]
      *pin[28][2])));
    Cik[28][2][1] = (((pin[28][0]*s28)+(pin[28][1]*pin[28][2]))-(c28*(pin[28][1]
      *pin[28][2])));
    Cik[28][2][2] = ((pin[28][2]*pin[28][2])+(c28*(1.-(pin[28][2]*pin[28][2]))))
      ;
    Cik[29][0][0] = ((pin[29][0]*pin[29][0])+(c29*(1.-(pin[29][0]*pin[29][0]))))
      ;
    Cik[29][0][1] = (((pin[29][0]*pin[29][1])-(pin[29][2]*s29))-(c29*(pin[29][0]
      *pin[29][1])));
    Cik[29][0][2] = (((pin[29][0]*pin[29][2])+(pin[29][1]*s29))-(c29*(pin[29][0]
      *pin[29][2])));
    Cik[29][1][0] = (((pin[29][0]*pin[29][1])+(pin[29][2]*s29))-(c29*(pin[29][0]
      *pin[29][1])));
    Cik[29][1][1] = ((pin[29][1]*pin[29][1])+(c29*(1.-(pin[29][1]*pin[29][1]))))
      ;
    Cik[29][1][2] = (((pin[29][1]*pin[29][2])-(pin[29][0]*s29))-(c29*(pin[29][1]
      *pin[29][2])));
    Cik[29][2][0] = (((pin[29][0]*pin[29][2])-(pin[29][1]*s29))-(c29*(pin[29][0]
      *pin[29][2])));
    Cik[29][2][1] = (((pin[29][0]*s29)+(pin[29][1]*pin[29][2]))-(c29*(pin[29][1]
      *pin[29][2])));
    Cik[29][2][2] = ((pin[29][2]*pin[29][2])+(c29*(1.-(pin[29][2]*pin[29][2]))))
      ;
    Cik[30][0][0] = ((pin[30][0]*pin[30][0])+(c30*(1.-(pin[30][0]*pin[30][0]))))
      ;
    Cik[30][0][1] = (((pin[30][0]*pin[30][1])-(pin[30][2]*s30))-(c30*(pin[30][0]
      *pin[30][1])));
    Cik[30][0][2] = (((pin[30][0]*pin[30][2])+(pin[30][1]*s30))-(c30*(pin[30][0]
      *pin[30][2])));
    Cik[30][1][0] = (((pin[30][0]*pin[30][1])+(pin[30][2]*s30))-(c30*(pin[30][0]
      *pin[30][1])));
    Cik[30][1][1] = ((pin[30][1]*pin[30][1])+(c30*(1.-(pin[30][1]*pin[30][1]))))
      ;
    Cik[30][1][2] = (((pin[30][1]*pin[30][2])-(pin[30][0]*s30))-(c30*(pin[30][1]
      *pin[30][2])));
    Cik[30][2][0] = (((pin[30][0]*pin[30][2])-(pin[30][1]*s30))-(c30*(pin[30][0]
      *pin[30][2])));
    Cik[30][2][1] = (((pin[30][0]*s30)+(pin[30][1]*pin[30][2]))-(c30*(pin[30][1]
      *pin[30][2])));
    Cik[30][2][2] = ((pin[30][2]*pin[30][2])+(c30*(1.-(pin[30][2]*pin[30][2]))))
      ;
    Cik[31][0][0] = ((pin[31][0]*pin[31][0])+(c31*(1.-(pin[31][0]*pin[31][0]))))
      ;
    Cik[31][0][1] = (((pin[31][0]*pin[31][1])-(pin[31][2]*s31))-(c31*(pin[31][0]
      *pin[31][1])));
    Cik[31][0][2] = (((pin[31][0]*pin[31][2])+(pin[31][1]*s31))-(c31*(pin[31][0]
      *pin[31][2])));
    Cik[31][1][0] = (((pin[31][0]*pin[31][1])+(pin[31][2]*s31))-(c31*(pin[31][0]
      *pin[31][1])));
    Cik[31][1][1] = ((pin[31][1]*pin[31][1])+(c31*(1.-(pin[31][1]*pin[31][1]))))
      ;
    Cik[31][1][2] = (((pin[31][1]*pin[31][2])-(pin[31][0]*s31))-(c31*(pin[31][1]
      *pin[31][2])));
    Cik[31][2][0] = (((pin[31][0]*pin[31][2])-(pin[31][1]*s31))-(c31*(pin[31][0]
      *pin[31][2])));
    Cik[31][2][1] = (((pin[31][0]*s31)+(pin[31][1]*pin[31][2]))-(c31*(pin[31][1]
      *pin[31][2])));
    Cik[31][2][2] = ((pin[31][2]*pin[31][2])+(c31*(1.-(pin[31][2]*pin[31][2]))))
      ;
    Cik[32][0][0] = ((pin[32][0]*pin[32][0])+(c32*(1.-(pin[32][0]*pin[32][0]))))
      ;
    Cik[32][0][1] = (((pin[32][0]*pin[32][1])-(pin[32][2]*s32))-(c32*(pin[32][0]
      *pin[32][1])));
    Cik[32][0][2] = (((pin[32][0]*pin[32][2])+(pin[32][1]*s32))-(c32*(pin[32][0]
      *pin[32][2])));
    Cik[32][1][0] = (((pin[32][0]*pin[32][1])+(pin[32][2]*s32))-(c32*(pin[32][0]
      *pin[32][1])));
    Cik[32][1][1] = ((pin[32][1]*pin[32][1])+(c32*(1.-(pin[32][1]*pin[32][1]))))
      ;
    Cik[32][1][2] = (((pin[32][1]*pin[32][2])-(pin[32][0]*s32))-(c32*(pin[32][1]
      *pin[32][2])));
    Cik[32][2][0] = (((pin[32][0]*pin[32][2])-(pin[32][1]*s32))-(c32*(pin[32][0]
      *pin[32][2])));
    Cik[32][2][1] = (((pin[32][0]*s32)+(pin[32][1]*pin[32][2]))-(c32*(pin[32][1]
      *pin[32][2])));
    Cik[32][2][2] = ((pin[32][2]*pin[32][2])+(c32*(1.-(pin[32][2]*pin[32][2]))))
      ;
/*
Compute across-joint direction cosines Cib
*/
    Cib[1][0][0] = ((Cik[8][2][0]*((Cik[6][0][2]*Cik[7][2][2])+((Cik[6][0][0]*
      Cik[7][0][2])+(Cik[6][0][1]*Cik[7][1][2]))))+((Cik[8][0][0]*((Cik[6][0][2]
      *Cik[7][2][0])+((Cik[6][0][0]*Cik[7][0][0])+(Cik[6][0][1]*Cik[7][1][0]))))
      +(Cik[8][1][0]*((Cik[6][0][2]*Cik[7][2][1])+((Cik[6][0][0]*Cik[7][0][1])+(
      Cik[6][0][1]*Cik[7][1][1]))))));
    Cib[1][0][1] = ((Cik[8][2][1]*((Cik[6][0][2]*Cik[7][2][2])+((Cik[6][0][0]*
      Cik[7][0][2])+(Cik[6][0][1]*Cik[7][1][2]))))+((Cik[8][0][1]*((Cik[6][0][2]
      *Cik[7][2][0])+((Cik[6][0][0]*Cik[7][0][0])+(Cik[6][0][1]*Cik[7][1][0]))))
      +(Cik[8][1][1]*((Cik[6][0][2]*Cik[7][2][1])+((Cik[6][0][0]*Cik[7][0][1])+(
      Cik[6][0][1]*Cik[7][1][1]))))));
    Cib[1][0][2] = ((Cik[8][2][2]*((Cik[6][0][2]*Cik[7][2][2])+((Cik[6][0][0]*
      Cik[7][0][2])+(Cik[6][0][1]*Cik[7][1][2]))))+((Cik[8][0][2]*((Cik[6][0][2]
      *Cik[7][2][0])+((Cik[6][0][0]*Cik[7][0][0])+(Cik[6][0][1]*Cik[7][1][0]))))
      +(Cik[8][1][2]*((Cik[6][0][2]*Cik[7][2][1])+((Cik[6][0][0]*Cik[7][0][1])+(
      Cik[6][0][1]*Cik[7][1][1]))))));
    Cib[1][1][0] = ((Cik[8][2][0]*((Cik[6][1][2]*Cik[7][2][2])+((Cik[6][1][0]*
      Cik[7][0][2])+(Cik[6][1][1]*Cik[7][1][2]))))+((Cik[8][0][0]*((Cik[6][1][2]
      *Cik[7][2][0])+((Cik[6][1][0]*Cik[7][0][0])+(Cik[6][1][1]*Cik[7][1][0]))))
      +(Cik[8][1][0]*((Cik[6][1][2]*Cik[7][2][1])+((Cik[6][1][0]*Cik[7][0][1])+(
      Cik[6][1][1]*Cik[7][1][1]))))));
    Cib[1][1][1] = ((Cik[8][2][1]*((Cik[6][1][2]*Cik[7][2][2])+((Cik[6][1][0]*
      Cik[7][0][2])+(Cik[6][1][1]*Cik[7][1][2]))))+((Cik[8][0][1]*((Cik[6][1][2]
      *Cik[7][2][0])+((Cik[6][1][0]*Cik[7][0][0])+(Cik[6][1][1]*Cik[7][1][0]))))
      +(Cik[8][1][1]*((Cik[6][1][2]*Cik[7][2][1])+((Cik[6][1][0]*Cik[7][0][1])+(
      Cik[6][1][1]*Cik[7][1][1]))))));
    Cib[1][1][2] = ((Cik[8][2][2]*((Cik[6][1][2]*Cik[7][2][2])+((Cik[6][1][0]*
      Cik[7][0][2])+(Cik[6][1][1]*Cik[7][1][2]))))+((Cik[8][0][2]*((Cik[6][1][2]
      *Cik[7][2][0])+((Cik[6][1][0]*Cik[7][0][0])+(Cik[6][1][1]*Cik[7][1][0]))))
      +(Cik[8][1][2]*((Cik[6][1][2]*Cik[7][2][1])+((Cik[6][1][0]*Cik[7][0][1])+(
      Cik[6][1][1]*Cik[7][1][1]))))));
    Cib[1][2][0] = ((Cik[8][2][0]*((Cik[6][2][2]*Cik[7][2][2])+((Cik[6][2][0]*
      Cik[7][0][2])+(Cik[6][2][1]*Cik[7][1][2]))))+((Cik[8][0][0]*((Cik[6][2][2]
      *Cik[7][2][0])+((Cik[6][2][0]*Cik[7][0][0])+(Cik[6][2][1]*Cik[7][1][0]))))
      +(Cik[8][1][0]*((Cik[6][2][2]*Cik[7][2][1])+((Cik[6][2][0]*Cik[7][0][1])+(
      Cik[6][2][1]*Cik[7][1][1]))))));
    Cib[1][2][1] = ((Cik[8][2][1]*((Cik[6][2][2]*Cik[7][2][2])+((Cik[6][2][0]*
      Cik[7][0][2])+(Cik[6][2][1]*Cik[7][1][2]))))+((Cik[8][0][1]*((Cik[6][2][2]
      *Cik[7][2][0])+((Cik[6][2][0]*Cik[7][0][0])+(Cik[6][2][1]*Cik[7][1][0]))))
      +(Cik[8][1][1]*((Cik[6][2][2]*Cik[7][2][1])+((Cik[6][2][0]*Cik[7][0][1])+(
      Cik[6][2][1]*Cik[7][1][1]))))));
    Cib[1][2][2] = ((Cik[8][2][2]*((Cik[6][2][2]*Cik[7][2][2])+((Cik[6][2][0]*
      Cik[7][0][2])+(Cik[6][2][1]*Cik[7][1][2]))))+((Cik[8][0][2]*((Cik[6][2][2]
      *Cik[7][2][0])+((Cik[6][2][0]*Cik[7][0][0])+(Cik[6][2][1]*Cik[7][1][0]))))
      +(Cik[8][1][2]*((Cik[6][2][2]*Cik[7][2][1])+((Cik[6][2][0]*Cik[7][0][1])+(
      Cik[6][2][1]*Cik[7][1][1]))))));
    Cib[2][0][0] = ((Cik[11][2][0]*((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
      Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2]))))+((Cik[11][0][0]*((
      Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*Cik[10][0][0])+(Cik[9][0][1]*
      Cik[10][1][0]))))+(Cik[11][1][0]*((Cik[9][0][2]*Cik[10][2][1])+((
      Cik[9][0][0]*Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1]))))));
    Cib[2][0][1] = ((Cik[11][2][1]*((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
      Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2]))))+((Cik[11][0][1]*((
      Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*Cik[10][0][0])+(Cik[9][0][1]*
      Cik[10][1][0]))))+(Cik[11][1][1]*((Cik[9][0][2]*Cik[10][2][1])+((
      Cik[9][0][0]*Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1]))))));
    Cib[2][0][2] = ((Cik[11][2][2]*((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
      Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2]))))+((Cik[11][0][2]*((
      Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*Cik[10][0][0])+(Cik[9][0][1]*
      Cik[10][1][0]))))+(Cik[11][1][2]*((Cik[9][0][2]*Cik[10][2][1])+((
      Cik[9][0][0]*Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1]))))));
    Cib[2][1][0] = ((Cik[11][2][0]*((Cik[9][1][2]*Cik[10][2][2])+((Cik[9][1][0]*
      Cik[10][0][2])+(Cik[9][1][1]*Cik[10][1][2]))))+((Cik[11][0][0]*((
      Cik[9][1][2]*Cik[10][2][0])+((Cik[9][1][0]*Cik[10][0][0])+(Cik[9][1][1]*
      Cik[10][1][0]))))+(Cik[11][1][0]*((Cik[9][1][2]*Cik[10][2][1])+((
      Cik[9][1][0]*Cik[10][0][1])+(Cik[9][1][1]*Cik[10][1][1]))))));
    Cib[2][1][1] = ((Cik[11][2][1]*((Cik[9][1][2]*Cik[10][2][2])+((Cik[9][1][0]*
      Cik[10][0][2])+(Cik[9][1][1]*Cik[10][1][2]))))+((Cik[11][0][1]*((
      Cik[9][1][2]*Cik[10][2][0])+((Cik[9][1][0]*Cik[10][0][0])+(Cik[9][1][1]*
      Cik[10][1][0]))))+(Cik[11][1][1]*((Cik[9][1][2]*Cik[10][2][1])+((
      Cik[9][1][0]*Cik[10][0][1])+(Cik[9][1][1]*Cik[10][1][1]))))));
    Cib[2][1][2] = ((Cik[11][2][2]*((Cik[9][1][2]*Cik[10][2][2])+((Cik[9][1][0]*
      Cik[10][0][2])+(Cik[9][1][1]*Cik[10][1][2]))))+((Cik[11][0][2]*((
      Cik[9][1][2]*Cik[10][2][0])+((Cik[9][1][0]*Cik[10][0][0])+(Cik[9][1][1]*
      Cik[10][1][0]))))+(Cik[11][1][2]*((Cik[9][1][2]*Cik[10][2][1])+((
      Cik[9][1][0]*Cik[10][0][1])+(Cik[9][1][1]*Cik[10][1][1]))))));
    Cib[2][2][0] = ((Cik[11][2][0]*((Cik[9][2][2]*Cik[10][2][2])+((Cik[9][2][0]*
      Cik[10][0][2])+(Cik[9][2][1]*Cik[10][1][2]))))+((Cik[11][0][0]*((
      Cik[9][2][2]*Cik[10][2][0])+((Cik[9][2][0]*Cik[10][0][0])+(Cik[9][2][1]*
      Cik[10][1][0]))))+(Cik[11][1][0]*((Cik[9][2][2]*Cik[10][2][1])+((
      Cik[9][2][0]*Cik[10][0][1])+(Cik[9][2][1]*Cik[10][1][1]))))));
    Cib[2][2][1] = ((Cik[11][2][1]*((Cik[9][2][2]*Cik[10][2][2])+((Cik[9][2][0]*
      Cik[10][0][2])+(Cik[9][2][1]*Cik[10][1][2]))))+((Cik[11][0][1]*((
      Cik[9][2][2]*Cik[10][2][0])+((Cik[9][2][0]*Cik[10][0][0])+(Cik[9][2][1]*
      Cik[10][1][0]))))+(Cik[11][1][1]*((Cik[9][2][2]*Cik[10][2][1])+((
      Cik[9][2][0]*Cik[10][0][1])+(Cik[9][2][1]*Cik[10][1][1]))))));
    Cib[2][2][2] = ((Cik[11][2][2]*((Cik[9][2][2]*Cik[10][2][2])+((Cik[9][2][0]*
      Cik[10][0][2])+(Cik[9][2][1]*Cik[10][1][2]))))+((Cik[11][0][2]*((
      Cik[9][2][2]*Cik[10][2][0])+((Cik[9][2][0]*Cik[10][0][0])+(Cik[9][2][1]*
      Cik[10][1][0]))))+(Cik[11][1][2]*((Cik[9][2][2]*Cik[10][2][1])+((
      Cik[9][2][0]*Cik[10][0][1])+(Cik[9][2][1]*Cik[10][1][1]))))));
    Cib[3][0][0] = ((Cik[14][2][0]*((Cik[12][0][2]*Cik[13][2][2])+((
      Cik[12][0][0]*Cik[13][0][2])+(Cik[12][0][1]*Cik[13][1][2]))))+((
      Cik[14][0][0]*((Cik[12][0][2]*Cik[13][2][0])+((Cik[12][0][0]*Cik[13][0][0]
      )+(Cik[12][0][1]*Cik[13][1][0]))))+(Cik[14][1][0]*((Cik[12][0][2]*
      Cik[13][2][1])+((Cik[12][0][0]*Cik[13][0][1])+(Cik[12][0][1]*Cik[13][1][1]
      ))))));
    Cib[3][0][1] = ((Cik[14][2][1]*((Cik[12][0][2]*Cik[13][2][2])+((
      Cik[12][0][0]*Cik[13][0][2])+(Cik[12][0][1]*Cik[13][1][2]))))+((
      Cik[14][0][1]*((Cik[12][0][2]*Cik[13][2][0])+((Cik[12][0][0]*Cik[13][0][0]
      )+(Cik[12][0][1]*Cik[13][1][0]))))+(Cik[14][1][1]*((Cik[12][0][2]*
      Cik[13][2][1])+((Cik[12][0][0]*Cik[13][0][1])+(Cik[12][0][1]*Cik[13][1][1]
      ))))));
    Cib[3][0][2] = ((Cik[14][2][2]*((Cik[12][0][2]*Cik[13][2][2])+((
      Cik[12][0][0]*Cik[13][0][2])+(Cik[12][0][1]*Cik[13][1][2]))))+((
      Cik[14][0][2]*((Cik[12][0][2]*Cik[13][2][0])+((Cik[12][0][0]*Cik[13][0][0]
      )+(Cik[12][0][1]*Cik[13][1][0]))))+(Cik[14][1][2]*((Cik[12][0][2]*
      Cik[13][2][1])+((Cik[12][0][0]*Cik[13][0][1])+(Cik[12][0][1]*Cik[13][1][1]
      ))))));
    Cib[3][1][0] = ((Cik[14][2][0]*((Cik[12][1][2]*Cik[13][2][2])+((
      Cik[12][1][0]*Cik[13][0][2])+(Cik[12][1][1]*Cik[13][1][2]))))+((
      Cik[14][0][0]*((Cik[12][1][2]*Cik[13][2][0])+((Cik[12][1][0]*Cik[13][0][0]
      )+(Cik[12][1][1]*Cik[13][1][0]))))+(Cik[14][1][0]*((Cik[12][1][2]*
      Cik[13][2][1])+((Cik[12][1][0]*Cik[13][0][1])+(Cik[12][1][1]*Cik[13][1][1]
      ))))));
    Cib[3][1][1] = ((Cik[14][2][1]*((Cik[12][1][2]*Cik[13][2][2])+((
      Cik[12][1][0]*Cik[13][0][2])+(Cik[12][1][1]*Cik[13][1][2]))))+((
      Cik[14][0][1]*((Cik[12][1][2]*Cik[13][2][0])+((Cik[12][1][0]*Cik[13][0][0]
      )+(Cik[12][1][1]*Cik[13][1][0]))))+(Cik[14][1][1]*((Cik[12][1][2]*
      Cik[13][2][1])+((Cik[12][1][0]*Cik[13][0][1])+(Cik[12][1][1]*Cik[13][1][1]
      ))))));
    Cib[3][1][2] = ((Cik[14][2][2]*((Cik[12][1][2]*Cik[13][2][2])+((
      Cik[12][1][0]*Cik[13][0][2])+(Cik[12][1][1]*Cik[13][1][2]))))+((
      Cik[14][0][2]*((Cik[12][1][2]*Cik[13][2][0])+((Cik[12][1][0]*Cik[13][0][0]
      )+(Cik[12][1][1]*Cik[13][1][0]))))+(Cik[14][1][2]*((Cik[12][1][2]*
      Cik[13][2][1])+((Cik[12][1][0]*Cik[13][0][1])+(Cik[12][1][1]*Cik[13][1][1]
      ))))));
    Cib[3][2][0] = ((Cik[14][2][0]*((Cik[12][2][2]*Cik[13][2][2])+((
      Cik[12][2][0]*Cik[13][0][2])+(Cik[12][2][1]*Cik[13][1][2]))))+((
      Cik[14][0][0]*((Cik[12][2][2]*Cik[13][2][0])+((Cik[12][2][0]*Cik[13][0][0]
      )+(Cik[12][2][1]*Cik[13][1][0]))))+(Cik[14][1][0]*((Cik[12][2][2]*
      Cik[13][2][1])+((Cik[12][2][0]*Cik[13][0][1])+(Cik[12][2][1]*Cik[13][1][1]
      ))))));
    Cib[3][2][1] = ((Cik[14][2][1]*((Cik[12][2][2]*Cik[13][2][2])+((
      Cik[12][2][0]*Cik[13][0][2])+(Cik[12][2][1]*Cik[13][1][2]))))+((
      Cik[14][0][1]*((Cik[12][2][2]*Cik[13][2][0])+((Cik[12][2][0]*Cik[13][0][0]
      )+(Cik[12][2][1]*Cik[13][1][0]))))+(Cik[14][1][1]*((Cik[12][2][2]*
      Cik[13][2][1])+((Cik[12][2][0]*Cik[13][0][1])+(Cik[12][2][1]*Cik[13][1][1]
      ))))));
    Cib[3][2][2] = ((Cik[14][2][2]*((Cik[12][2][2]*Cik[13][2][2])+((
      Cik[12][2][0]*Cik[13][0][2])+(Cik[12][2][1]*Cik[13][1][2]))))+((
      Cik[14][0][2]*((Cik[12][2][2]*Cik[13][2][0])+((Cik[12][2][0]*Cik[13][0][0]
      )+(Cik[12][2][1]*Cik[13][1][0]))))+(Cik[14][1][2]*((Cik[12][2][2]*
      Cik[13][2][1])+((Cik[12][2][0]*Cik[13][0][1])+(Cik[12][2][1]*Cik[13][1][1]
      ))))));
    Cib[4][0][0] = ((Cik[17][2][0]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[4][0][1] = ((Cik[17][2][1]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[4][0][2] = ((Cik[17][2][2]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[4][1][0] = ((Cik[17][2][0]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[4][1][1] = ((Cik[17][2][1]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[4][1][2] = ((Cik[17][2][2]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[4][2][0] = ((Cik[17][2][0]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[4][2][1] = ((Cik[17][2][1]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[4][2][2] = ((Cik[17][2][2]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[5][0][0] = ((Cik[20][2][0]*((Cik[18][0][2]*Cik[19][2][2])+((
      Cik[18][0][0]*Cik[19][0][2])+(Cik[18][0][1]*Cik[19][1][2]))))+((
      Cik[20][0][0]*((Cik[18][0][2]*Cik[19][2][0])+((Cik[18][0][0]*Cik[19][0][0]
      )+(Cik[18][0][1]*Cik[19][1][0]))))+(Cik[20][1][0]*((Cik[18][0][2]*
      Cik[19][2][1])+((Cik[18][0][0]*Cik[19][0][1])+(Cik[18][0][1]*Cik[19][1][1]
      ))))));
    Cib[5][0][1] = ((Cik[20][2][1]*((Cik[18][0][2]*Cik[19][2][2])+((
      Cik[18][0][0]*Cik[19][0][2])+(Cik[18][0][1]*Cik[19][1][2]))))+((
      Cik[20][0][1]*((Cik[18][0][2]*Cik[19][2][0])+((Cik[18][0][0]*Cik[19][0][0]
      )+(Cik[18][0][1]*Cik[19][1][0]))))+(Cik[20][1][1]*((Cik[18][0][2]*
      Cik[19][2][1])+((Cik[18][0][0]*Cik[19][0][1])+(Cik[18][0][1]*Cik[19][1][1]
      ))))));
    Cib[5][0][2] = ((Cik[20][2][2]*((Cik[18][0][2]*Cik[19][2][2])+((
      Cik[18][0][0]*Cik[19][0][2])+(Cik[18][0][1]*Cik[19][1][2]))))+((
      Cik[20][0][2]*((Cik[18][0][2]*Cik[19][2][0])+((Cik[18][0][0]*Cik[19][0][0]
      )+(Cik[18][0][1]*Cik[19][1][0]))))+(Cik[20][1][2]*((Cik[18][0][2]*
      Cik[19][2][1])+((Cik[18][0][0]*Cik[19][0][1])+(Cik[18][0][1]*Cik[19][1][1]
      ))))));
    Cib[5][1][0] = ((Cik[20][2][0]*((Cik[18][1][2]*Cik[19][2][2])+((
      Cik[18][1][0]*Cik[19][0][2])+(Cik[18][1][1]*Cik[19][1][2]))))+((
      Cik[20][0][0]*((Cik[18][1][2]*Cik[19][2][0])+((Cik[18][1][0]*Cik[19][0][0]
      )+(Cik[18][1][1]*Cik[19][1][0]))))+(Cik[20][1][0]*((Cik[18][1][2]*
      Cik[19][2][1])+((Cik[18][1][0]*Cik[19][0][1])+(Cik[18][1][1]*Cik[19][1][1]
      ))))));
    Cib[5][1][1] = ((Cik[20][2][1]*((Cik[18][1][2]*Cik[19][2][2])+((
      Cik[18][1][0]*Cik[19][0][2])+(Cik[18][1][1]*Cik[19][1][2]))))+((
      Cik[20][0][1]*((Cik[18][1][2]*Cik[19][2][0])+((Cik[18][1][0]*Cik[19][0][0]
      )+(Cik[18][1][1]*Cik[19][1][0]))))+(Cik[20][1][1]*((Cik[18][1][2]*
      Cik[19][2][1])+((Cik[18][1][0]*Cik[19][0][1])+(Cik[18][1][1]*Cik[19][1][1]
      ))))));
    Cib[5][1][2] = ((Cik[20][2][2]*((Cik[18][1][2]*Cik[19][2][2])+((
      Cik[18][1][0]*Cik[19][0][2])+(Cik[18][1][1]*Cik[19][1][2]))))+((
      Cik[20][0][2]*((Cik[18][1][2]*Cik[19][2][0])+((Cik[18][1][0]*Cik[19][0][0]
      )+(Cik[18][1][1]*Cik[19][1][0]))))+(Cik[20][1][2]*((Cik[18][1][2]*
      Cik[19][2][1])+((Cik[18][1][0]*Cik[19][0][1])+(Cik[18][1][1]*Cik[19][1][1]
      ))))));
    Cib[5][2][0] = ((Cik[20][2][0]*((Cik[18][2][2]*Cik[19][2][2])+((
      Cik[18][2][0]*Cik[19][0][2])+(Cik[18][2][1]*Cik[19][1][2]))))+((
      Cik[20][0][0]*((Cik[18][2][2]*Cik[19][2][0])+((Cik[18][2][0]*Cik[19][0][0]
      )+(Cik[18][2][1]*Cik[19][1][0]))))+(Cik[20][1][0]*((Cik[18][2][2]*
      Cik[19][2][1])+((Cik[18][2][0]*Cik[19][0][1])+(Cik[18][2][1]*Cik[19][1][1]
      ))))));
    Cib[5][2][1] = ((Cik[20][2][1]*((Cik[18][2][2]*Cik[19][2][2])+((
      Cik[18][2][0]*Cik[19][0][2])+(Cik[18][2][1]*Cik[19][1][2]))))+((
      Cik[20][0][1]*((Cik[18][2][2]*Cik[19][2][0])+((Cik[18][2][0]*Cik[19][0][0]
      )+(Cik[18][2][1]*Cik[19][1][0]))))+(Cik[20][1][1]*((Cik[18][2][2]*
      Cik[19][2][1])+((Cik[18][2][0]*Cik[19][0][1])+(Cik[18][2][1]*Cik[19][1][1]
      ))))));
    Cib[5][2][2] = ((Cik[20][2][2]*((Cik[18][2][2]*Cik[19][2][2])+((
      Cik[18][2][0]*Cik[19][0][2])+(Cik[18][2][1]*Cik[19][1][2]))))+((
      Cik[20][0][2]*((Cik[18][2][2]*Cik[19][2][0])+((Cik[18][2][0]*Cik[19][0][0]
      )+(Cik[18][2][1]*Cik[19][1][0]))))+(Cik[20][1][2]*((Cik[18][2][2]*
      Cik[19][2][1])+((Cik[18][2][0]*Cik[19][0][1])+(Cik[18][2][1]*Cik[19][1][1]
      ))))));
    Cib[6][0][0] = ((Cik[23][2][0]*((Cik[21][0][2]*Cik[22][2][2])+((
      Cik[21][0][0]*Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2]))))+((
      Cik[23][0][0]*((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*Cik[22][0][0]
      )+(Cik[21][0][1]*Cik[22][1][0]))))+(Cik[23][1][0]*((Cik[21][0][2]*
      Cik[22][2][1])+((Cik[21][0][0]*Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1]
      ))))));
    Cib[6][0][1] = ((Cik[23][2][1]*((Cik[21][0][2]*Cik[22][2][2])+((
      Cik[21][0][0]*Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2]))))+((
      Cik[23][0][1]*((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*Cik[22][0][0]
      )+(Cik[21][0][1]*Cik[22][1][0]))))+(Cik[23][1][1]*((Cik[21][0][2]*
      Cik[22][2][1])+((Cik[21][0][0]*Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1]
      ))))));
    Cib[6][0][2] = ((Cik[23][2][2]*((Cik[21][0][2]*Cik[22][2][2])+((
      Cik[21][0][0]*Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2]))))+((
      Cik[23][0][2]*((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*Cik[22][0][0]
      )+(Cik[21][0][1]*Cik[22][1][0]))))+(Cik[23][1][2]*((Cik[21][0][2]*
      Cik[22][2][1])+((Cik[21][0][0]*Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1]
      ))))));
    Cib[6][1][0] = ((Cik[23][2][0]*((Cik[21][1][2]*Cik[22][2][2])+((
      Cik[21][1][0]*Cik[22][0][2])+(Cik[21][1][1]*Cik[22][1][2]))))+((
      Cik[23][0][0]*((Cik[21][1][2]*Cik[22][2][0])+((Cik[21][1][0]*Cik[22][0][0]
      )+(Cik[21][1][1]*Cik[22][1][0]))))+(Cik[23][1][0]*((Cik[21][1][2]*
      Cik[22][2][1])+((Cik[21][1][0]*Cik[22][0][1])+(Cik[21][1][1]*Cik[22][1][1]
      ))))));
    Cib[6][1][1] = ((Cik[23][2][1]*((Cik[21][1][2]*Cik[22][2][2])+((
      Cik[21][1][0]*Cik[22][0][2])+(Cik[21][1][1]*Cik[22][1][2]))))+((
      Cik[23][0][1]*((Cik[21][1][2]*Cik[22][2][0])+((Cik[21][1][0]*Cik[22][0][0]
      )+(Cik[21][1][1]*Cik[22][1][0]))))+(Cik[23][1][1]*((Cik[21][1][2]*
      Cik[22][2][1])+((Cik[21][1][0]*Cik[22][0][1])+(Cik[21][1][1]*Cik[22][1][1]
      ))))));
    Cib[6][1][2] = ((Cik[23][2][2]*((Cik[21][1][2]*Cik[22][2][2])+((
      Cik[21][1][0]*Cik[22][0][2])+(Cik[21][1][1]*Cik[22][1][2]))))+((
      Cik[23][0][2]*((Cik[21][1][2]*Cik[22][2][0])+((Cik[21][1][0]*Cik[22][0][0]
      )+(Cik[21][1][1]*Cik[22][1][0]))))+(Cik[23][1][2]*((Cik[21][1][2]*
      Cik[22][2][1])+((Cik[21][1][0]*Cik[22][0][1])+(Cik[21][1][1]*Cik[22][1][1]
      ))))));
    Cib[6][2][0] = ((Cik[23][2][0]*((Cik[21][2][2]*Cik[22][2][2])+((
      Cik[21][2][0]*Cik[22][0][2])+(Cik[21][2][1]*Cik[22][1][2]))))+((
      Cik[23][0][0]*((Cik[21][2][2]*Cik[22][2][0])+((Cik[21][2][0]*Cik[22][0][0]
      )+(Cik[21][2][1]*Cik[22][1][0]))))+(Cik[23][1][0]*((Cik[21][2][2]*
      Cik[22][2][1])+((Cik[21][2][0]*Cik[22][0][1])+(Cik[21][2][1]*Cik[22][1][1]
      ))))));
    Cib[6][2][1] = ((Cik[23][2][1]*((Cik[21][2][2]*Cik[22][2][2])+((
      Cik[21][2][0]*Cik[22][0][2])+(Cik[21][2][1]*Cik[22][1][2]))))+((
      Cik[23][0][1]*((Cik[21][2][2]*Cik[22][2][0])+((Cik[21][2][0]*Cik[22][0][0]
      )+(Cik[21][2][1]*Cik[22][1][0]))))+(Cik[23][1][1]*((Cik[21][2][2]*
      Cik[22][2][1])+((Cik[21][2][0]*Cik[22][0][1])+(Cik[21][2][1]*Cik[22][1][1]
      ))))));
    Cib[6][2][2] = ((Cik[23][2][2]*((Cik[21][2][2]*Cik[22][2][2])+((
      Cik[21][2][0]*Cik[22][0][2])+(Cik[21][2][1]*Cik[22][1][2]))))+((
      Cik[23][0][2]*((Cik[21][2][2]*Cik[22][2][0])+((Cik[21][2][0]*Cik[22][0][0]
      )+(Cik[21][2][1]*Cik[22][1][0]))))+(Cik[23][1][2]*((Cik[21][2][2]*
      Cik[22][2][1])+((Cik[21][2][0]*Cik[22][0][1])+(Cik[21][2][1]*Cik[22][1][1]
      ))))));
    Cib[7][0][0] = ((Cik[26][2][0]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[7][0][1] = ((Cik[26][2][1]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[7][0][2] = ((Cik[26][2][2]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[7][1][0] = ((Cik[26][2][0]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[7][1][1] = ((Cik[26][2][1]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[7][1][2] = ((Cik[26][2][2]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[7][2][0] = ((Cik[26][2][0]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
      ))))));
    Cib[7][2][1] = ((Cik[26][2][1]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
      ))))));
    Cib[7][2][2] = ((Cik[26][2][2]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
      ))))));
    Cib[8][0][0] = ((Cik[29][2][0]*((Cik[27][0][2]*Cik[28][2][2])+((
      Cik[27][0][0]*Cik[28][0][2])+(Cik[27][0][1]*Cik[28][1][2]))))+((
      Cik[29][0][0]*((Cik[27][0][2]*Cik[28][2][0])+((Cik[27][0][0]*Cik[28][0][0]
      )+(Cik[27][0][1]*Cik[28][1][0]))))+(Cik[29][1][0]*((Cik[27][0][2]*
      Cik[28][2][1])+((Cik[27][0][0]*Cik[28][0][1])+(Cik[27][0][1]*Cik[28][1][1]
      ))))));
    Cib[8][0][1] = ((Cik[29][2][1]*((Cik[27][0][2]*Cik[28][2][2])+((
      Cik[27][0][0]*Cik[28][0][2])+(Cik[27][0][1]*Cik[28][1][2]))))+((
      Cik[29][0][1]*((Cik[27][0][2]*Cik[28][2][0])+((Cik[27][0][0]*Cik[28][0][0]
      )+(Cik[27][0][1]*Cik[28][1][0]))))+(Cik[29][1][1]*((Cik[27][0][2]*
      Cik[28][2][1])+((Cik[27][0][0]*Cik[28][0][1])+(Cik[27][0][1]*Cik[28][1][1]
      ))))));
    Cib[8][0][2] = ((Cik[29][2][2]*((Cik[27][0][2]*Cik[28][2][2])+((
      Cik[27][0][0]*Cik[28][0][2])+(Cik[27][0][1]*Cik[28][1][2]))))+((
      Cik[29][0][2]*((Cik[27][0][2]*Cik[28][2][0])+((Cik[27][0][0]*Cik[28][0][0]
      )+(Cik[27][0][1]*Cik[28][1][0]))))+(Cik[29][1][2]*((Cik[27][0][2]*
      Cik[28][2][1])+((Cik[27][0][0]*Cik[28][0][1])+(Cik[27][0][1]*Cik[28][1][1]
      ))))));
    Cib[8][1][0] = ((Cik[29][2][0]*((Cik[27][1][2]*Cik[28][2][2])+((
      Cik[27][1][0]*Cik[28][0][2])+(Cik[27][1][1]*Cik[28][1][2]))))+((
      Cik[29][0][0]*((Cik[27][1][2]*Cik[28][2][0])+((Cik[27][1][0]*Cik[28][0][0]
      )+(Cik[27][1][1]*Cik[28][1][0]))))+(Cik[29][1][0]*((Cik[27][1][2]*
      Cik[28][2][1])+((Cik[27][1][0]*Cik[28][0][1])+(Cik[27][1][1]*Cik[28][1][1]
      ))))));
    Cib[8][1][1] = ((Cik[29][2][1]*((Cik[27][1][2]*Cik[28][2][2])+((
      Cik[27][1][0]*Cik[28][0][2])+(Cik[27][1][1]*Cik[28][1][2]))))+((
      Cik[29][0][1]*((Cik[27][1][2]*Cik[28][2][0])+((Cik[27][1][0]*Cik[28][0][0]
      )+(Cik[27][1][1]*Cik[28][1][0]))))+(Cik[29][1][1]*((Cik[27][1][2]*
      Cik[28][2][1])+((Cik[27][1][0]*Cik[28][0][1])+(Cik[27][1][1]*Cik[28][1][1]
      ))))));
    Cib[8][1][2] = ((Cik[29][2][2]*((Cik[27][1][2]*Cik[28][2][2])+((
      Cik[27][1][0]*Cik[28][0][2])+(Cik[27][1][1]*Cik[28][1][2]))))+((
      Cik[29][0][2]*((Cik[27][1][2]*Cik[28][2][0])+((Cik[27][1][0]*Cik[28][0][0]
      )+(Cik[27][1][1]*Cik[28][1][0]))))+(Cik[29][1][2]*((Cik[27][1][2]*
      Cik[28][2][1])+((Cik[27][1][0]*Cik[28][0][1])+(Cik[27][1][1]*Cik[28][1][1]
      ))))));
    Cib[8][2][0] = ((Cik[29][2][0]*((Cik[27][2][2]*Cik[28][2][2])+((
      Cik[27][2][0]*Cik[28][0][2])+(Cik[27][2][1]*Cik[28][1][2]))))+((
      Cik[29][0][0]*((Cik[27][2][2]*Cik[28][2][0])+((Cik[27][2][0]*Cik[28][0][0]
      )+(Cik[27][2][1]*Cik[28][1][0]))))+(Cik[29][1][0]*((Cik[27][2][2]*
      Cik[28][2][1])+((Cik[27][2][0]*Cik[28][0][1])+(Cik[27][2][1]*Cik[28][1][1]
      ))))));
    Cib[8][2][1] = ((Cik[29][2][1]*((Cik[27][2][2]*Cik[28][2][2])+((
      Cik[27][2][0]*Cik[28][0][2])+(Cik[27][2][1]*Cik[28][1][2]))))+((
      Cik[29][0][1]*((Cik[27][2][2]*Cik[28][2][0])+((Cik[27][2][0]*Cik[28][0][0]
      )+(Cik[27][2][1]*Cik[28][1][0]))))+(Cik[29][1][1]*((Cik[27][2][2]*
      Cik[28][2][1])+((Cik[27][2][0]*Cik[28][0][1])+(Cik[27][2][1]*Cik[28][1][1]
      ))))));
    Cib[8][2][2] = ((Cik[29][2][2]*((Cik[27][2][2]*Cik[28][2][2])+((
      Cik[27][2][0]*Cik[28][0][2])+(Cik[27][2][1]*Cik[28][1][2]))))+((
      Cik[29][0][2]*((Cik[27][2][2]*Cik[28][2][0])+((Cik[27][2][0]*Cik[28][0][0]
      )+(Cik[27][2][1]*Cik[28][1][0]))))+(Cik[29][1][2]*((Cik[27][2][2]*
      Cik[28][2][1])+((Cik[27][2][0]*Cik[28][0][1])+(Cik[27][2][1]*Cik[28][1][1]
      ))))));
    Cib[9][0][0] = ((Cik[32][2][0]*((Cik[30][0][2]*Cik[31][2][2])+((
      Cik[30][0][0]*Cik[31][0][2])+(Cik[30][0][1]*Cik[31][1][2]))))+((
      Cik[32][0][0]*((Cik[30][0][2]*Cik[31][2][0])+((Cik[30][0][0]*Cik[31][0][0]
      )+(Cik[30][0][1]*Cik[31][1][0]))))+(Cik[32][1][0]*((Cik[30][0][2]*
      Cik[31][2][1])+((Cik[30][0][0]*Cik[31][0][1])+(Cik[30][0][1]*Cik[31][1][1]
      ))))));
    Cib[9][0][1] = ((Cik[32][2][1]*((Cik[30][0][2]*Cik[31][2][2])+((
      Cik[30][0][0]*Cik[31][0][2])+(Cik[30][0][1]*Cik[31][1][2]))))+((
      Cik[32][0][1]*((Cik[30][0][2]*Cik[31][2][0])+((Cik[30][0][0]*Cik[31][0][0]
      )+(Cik[30][0][1]*Cik[31][1][0]))))+(Cik[32][1][1]*((Cik[30][0][2]*
      Cik[31][2][1])+((Cik[30][0][0]*Cik[31][0][1])+(Cik[30][0][1]*Cik[31][1][1]
      ))))));
    Cib[9][0][2] = ((Cik[32][2][2]*((Cik[30][0][2]*Cik[31][2][2])+((
      Cik[30][0][0]*Cik[31][0][2])+(Cik[30][0][1]*Cik[31][1][2]))))+((
      Cik[32][0][2]*((Cik[30][0][2]*Cik[31][2][0])+((Cik[30][0][0]*Cik[31][0][0]
      )+(Cik[30][0][1]*Cik[31][1][0]))))+(Cik[32][1][2]*((Cik[30][0][2]*
      Cik[31][2][1])+((Cik[30][0][0]*Cik[31][0][1])+(Cik[30][0][1]*Cik[31][1][1]
      ))))));
    Cib[9][1][0] = ((Cik[32][2][0]*((Cik[30][1][2]*Cik[31][2][2])+((
      Cik[30][1][0]*Cik[31][0][2])+(Cik[30][1][1]*Cik[31][1][2]))))+((
      Cik[32][0][0]*((Cik[30][1][2]*Cik[31][2][0])+((Cik[30][1][0]*Cik[31][0][0]
      )+(Cik[30][1][1]*Cik[31][1][0]))))+(Cik[32][1][0]*((Cik[30][1][2]*
      Cik[31][2][1])+((Cik[30][1][0]*Cik[31][0][1])+(Cik[30][1][1]*Cik[31][1][1]
      ))))));
    Cib[9][1][1] = ((Cik[32][2][1]*((Cik[30][1][2]*Cik[31][2][2])+((
      Cik[30][1][0]*Cik[31][0][2])+(Cik[30][1][1]*Cik[31][1][2]))))+((
      Cik[32][0][1]*((Cik[30][1][2]*Cik[31][2][0])+((Cik[30][1][0]*Cik[31][0][0]
      )+(Cik[30][1][1]*Cik[31][1][0]))))+(Cik[32][1][1]*((Cik[30][1][2]*
      Cik[31][2][1])+((Cik[30][1][0]*Cik[31][0][1])+(Cik[30][1][1]*Cik[31][1][1]
      ))))));
    Cib[9][1][2] = ((Cik[32][2][2]*((Cik[30][1][2]*Cik[31][2][2])+((
      Cik[30][1][0]*Cik[31][0][2])+(Cik[30][1][1]*Cik[31][1][2]))))+((
      Cik[32][0][2]*((Cik[30][1][2]*Cik[31][2][0])+((Cik[30][1][0]*Cik[31][0][0]
      )+(Cik[30][1][1]*Cik[31][1][0]))))+(Cik[32][1][2]*((Cik[30][1][2]*
      Cik[31][2][1])+((Cik[30][1][0]*Cik[31][0][1])+(Cik[30][1][1]*Cik[31][1][1]
      ))))));
    Cib[9][2][0] = ((Cik[32][2][0]*((Cik[30][2][2]*Cik[31][2][2])+((
      Cik[30][2][0]*Cik[31][0][2])+(Cik[30][2][1]*Cik[31][1][2]))))+((
      Cik[32][0][0]*((Cik[30][2][2]*Cik[31][2][0])+((Cik[30][2][0]*Cik[31][0][0]
      )+(Cik[30][2][1]*Cik[31][1][0]))))+(Cik[32][1][0]*((Cik[30][2][2]*
      Cik[31][2][1])+((Cik[30][2][0]*Cik[31][0][1])+(Cik[30][2][1]*Cik[31][1][1]
      ))))));
    Cib[9][2][1] = ((Cik[32][2][1]*((Cik[30][2][2]*Cik[31][2][2])+((
      Cik[30][2][0]*Cik[31][0][2])+(Cik[30][2][1]*Cik[31][1][2]))))+((
      Cik[32][0][1]*((Cik[30][2][2]*Cik[31][2][0])+((Cik[30][2][0]*Cik[31][0][0]
      )+(Cik[30][2][1]*Cik[31][1][0]))))+(Cik[32][1][1]*((Cik[30][2][2]*
      Cik[31][2][1])+((Cik[30][2][0]*Cik[31][0][1])+(Cik[30][2][1]*Cik[31][1][1]
      ))))));
    Cib[9][2][2] = ((Cik[32][2][2]*((Cik[30][2][2]*Cik[31][2][2])+((
      Cik[30][2][0]*Cik[31][0][2])+(Cik[30][2][1]*Cik[31][1][2]))))+((
      Cik[32][0][2]*((Cik[30][2][2]*Cik[31][2][0])+((Cik[30][2][0]*Cik[31][0][0]
      )+(Cik[30][2][1]*Cik[31][1][0]))))+(Cik[32][1][2]*((Cik[30][2][2]*
      Cik[31][2][1])+((Cik[30][2][0]*Cik[31][0][1])+(Cik[30][2][1]*Cik[31][1][1]
      ))))));
/*
Compute gravity
*/
    gk[3][0] = ((Cik[3][2][0]*grav[2])+((Cik[3][0][0]*grav[0])+(Cik[3][1][0]*
      grav[1])));
    gk[3][1] = ((Cik[3][2][1]*grav[2])+((Cik[3][0][1]*grav[0])+(Cik[3][1][1]*
      grav[1])));
    gk[3][2] = ((Cik[3][2][2]*grav[2])+((Cik[3][0][2]*grav[0])+(Cik[3][1][2]*
      grav[1])));
    gk[6][0] = ((Cik[6][2][0]*gk[3][2])+((Cik[6][0][0]*gk[3][0])+(Cik[6][1][0]*
      gk[3][1])));
    gk[6][1] = ((Cik[6][2][1]*gk[3][2])+((Cik[6][0][1]*gk[3][0])+(Cik[6][1][1]*
      gk[3][1])));
    gk[6][2] = ((Cik[6][2][2]*gk[3][2])+((Cik[6][0][2]*gk[3][0])+(Cik[6][1][2]*
      gk[3][1])));
    gk[7][0] = ((Cik[7][2][0]*gk[6][2])+((Cik[7][0][0]*gk[6][0])+(Cik[7][1][0]*
      gk[6][1])));
    gk[7][1] = ((Cik[7][2][1]*gk[6][2])+((Cik[7][0][1]*gk[6][0])+(Cik[7][1][1]*
      gk[6][1])));
    gk[7][2] = ((Cik[7][2][2]*gk[6][2])+((Cik[7][0][2]*gk[6][0])+(Cik[7][1][2]*
      gk[6][1])));
    gk[8][0] = ((Cik[8][2][0]*gk[7][2])+((Cik[8][0][0]*gk[7][0])+(Cik[8][1][0]*
      gk[7][1])));
    gk[8][1] = ((Cik[8][2][1]*gk[7][2])+((Cik[8][0][1]*gk[7][0])+(Cik[8][1][1]*
      gk[7][1])));
    gk[8][2] = ((Cik[8][2][2]*gk[7][2])+((Cik[8][0][2]*gk[7][0])+(Cik[8][1][2]*
      gk[7][1])));
    gk[9][0] = ((Cik[9][2][0]*gk[3][2])+((Cik[9][0][0]*gk[3][0])+(Cik[9][1][0]*
      gk[3][1])));
    gk[9][1] = ((Cik[9][2][1]*gk[3][2])+((Cik[9][0][1]*gk[3][0])+(Cik[9][1][1]*
      gk[3][1])));
    gk[9][2] = ((Cik[9][2][2]*gk[3][2])+((Cik[9][0][2]*gk[3][0])+(Cik[9][1][2]*
      gk[3][1])));
    gk[10][0] = ((Cik[10][2][0]*gk[9][2])+((Cik[10][0][0]*gk[9][0])+(
      Cik[10][1][0]*gk[9][1])));
    gk[10][1] = ((Cik[10][2][1]*gk[9][2])+((Cik[10][0][1]*gk[9][0])+(
      Cik[10][1][1]*gk[9][1])));
    gk[10][2] = ((Cik[10][2][2]*gk[9][2])+((Cik[10][0][2]*gk[9][0])+(
      Cik[10][1][2]*gk[9][1])));
    gk[11][0] = ((Cik[11][2][0]*gk[10][2])+((Cik[11][0][0]*gk[10][0])+(
      Cik[11][1][0]*gk[10][1])));
    gk[11][1] = ((Cik[11][2][1]*gk[10][2])+((Cik[11][0][1]*gk[10][0])+(
      Cik[11][1][1]*gk[10][1])));
    gk[11][2] = ((Cik[11][2][2]*gk[10][2])+((Cik[11][0][2]*gk[10][0])+(
      Cik[11][1][2]*gk[10][1])));
    gk[12][0] = ((Cik[12][2][0]*gk[11][2])+((Cik[12][0][0]*gk[11][0])+(
      Cik[12][1][0]*gk[11][1])));
    gk[12][1] = ((Cik[12][2][1]*gk[11][2])+((Cik[12][0][1]*gk[11][0])+(
      Cik[12][1][1]*gk[11][1])));
    gk[12][2] = ((Cik[12][2][2]*gk[11][2])+((Cik[12][0][2]*gk[11][0])+(
      Cik[12][1][2]*gk[11][1])));
    gk[13][0] = ((Cik[13][2][0]*gk[12][2])+((Cik[13][0][0]*gk[12][0])+(
      Cik[13][1][0]*gk[12][1])));
    gk[13][1] = ((Cik[13][2][1]*gk[12][2])+((Cik[13][0][1]*gk[12][0])+(
      Cik[13][1][1]*gk[12][1])));
    gk[13][2] = ((Cik[13][2][2]*gk[12][2])+((Cik[13][0][2]*gk[12][0])+(
      Cik[13][1][2]*gk[12][1])));
    gk[14][0] = ((Cik[14][2][0]*gk[13][2])+((Cik[14][0][0]*gk[13][0])+(
      Cik[14][1][0]*gk[13][1])));
    gk[14][1] = ((Cik[14][2][1]*gk[13][2])+((Cik[14][0][1]*gk[13][0])+(
      Cik[14][1][1]*gk[13][1])));
    gk[14][2] = ((Cik[14][2][2]*gk[13][2])+((Cik[14][0][2]*gk[13][0])+(
      Cik[14][1][2]*gk[13][1])));
    gk[15][0] = ((Cik[15][2][0]*gk[14][2])+((Cik[15][0][0]*gk[14][0])+(
      Cik[15][1][0]*gk[14][1])));
    gk[15][1] = ((Cik[15][2][1]*gk[14][2])+((Cik[15][0][1]*gk[14][0])+(
      Cik[15][1][1]*gk[14][1])));
    gk[15][2] = ((Cik[15][2][2]*gk[14][2])+((Cik[15][0][2]*gk[14][0])+(
      Cik[15][1][2]*gk[14][1])));
    gk[16][0] = ((Cik[16][2][0]*gk[15][2])+((Cik[16][0][0]*gk[15][0])+(
      Cik[16][1][0]*gk[15][1])));
    gk[16][1] = ((Cik[16][2][1]*gk[15][2])+((Cik[16][0][1]*gk[15][0])+(
      Cik[16][1][1]*gk[15][1])));
    gk[16][2] = ((Cik[16][2][2]*gk[15][2])+((Cik[16][0][2]*gk[15][0])+(
      Cik[16][1][2]*gk[15][1])));
    gk[17][0] = ((Cik[17][2][0]*gk[16][2])+((Cik[17][0][0]*gk[16][0])+(
      Cik[17][1][0]*gk[16][1])));
    gk[17][1] = ((Cik[17][2][1]*gk[16][2])+((Cik[17][0][1]*gk[16][0])+(
      Cik[17][1][1]*gk[16][1])));
    gk[17][2] = ((Cik[17][2][2]*gk[16][2])+((Cik[17][0][2]*gk[16][0])+(
      Cik[17][1][2]*gk[16][1])));
    gk[18][0] = ((Cik[18][2][0]*gk[17][2])+((Cik[18][0][0]*gk[17][0])+(
      Cik[18][1][0]*gk[17][1])));
    gk[18][1] = ((Cik[18][2][1]*gk[17][2])+((Cik[18][0][1]*gk[17][0])+(
      Cik[18][1][1]*gk[17][1])));
    gk[18][2] = ((Cik[18][2][2]*gk[17][2])+((Cik[18][0][2]*gk[17][0])+(
      Cik[18][1][2]*gk[17][1])));
    gk[19][0] = ((Cik[19][2][0]*gk[18][2])+((Cik[19][0][0]*gk[18][0])+(
      Cik[19][1][0]*gk[18][1])));
    gk[19][1] = ((Cik[19][2][1]*gk[18][2])+((Cik[19][0][1]*gk[18][0])+(
      Cik[19][1][1]*gk[18][1])));
    gk[19][2] = ((Cik[19][2][2]*gk[18][2])+((Cik[19][0][2]*gk[18][0])+(
      Cik[19][1][2]*gk[18][1])));
    gk[20][0] = ((Cik[20][2][0]*gk[19][2])+((Cik[20][0][0]*gk[19][0])+(
      Cik[20][1][0]*gk[19][1])));
    gk[20][1] = ((Cik[20][2][1]*gk[19][2])+((Cik[20][0][1]*gk[19][0])+(
      Cik[20][1][1]*gk[19][1])));
    gk[20][2] = ((Cik[20][2][2]*gk[19][2])+((Cik[20][0][2]*gk[19][0])+(
      Cik[20][1][2]*gk[19][1])));
    gk[21][0] = ((Cik[21][2][0]*gk[3][2])+((Cik[21][0][0]*gk[3][0])+(
      Cik[21][1][0]*gk[3][1])));
    gk[21][1] = ((Cik[21][2][1]*gk[3][2])+((Cik[21][0][1]*gk[3][0])+(
      Cik[21][1][1]*gk[3][1])));
    gk[21][2] = ((Cik[21][2][2]*gk[3][2])+((Cik[21][0][2]*gk[3][0])+(
      Cik[21][1][2]*gk[3][1])));
    gk[22][0] = ((Cik[22][2][0]*gk[21][2])+((Cik[22][0][0]*gk[21][0])+(
      Cik[22][1][0]*gk[21][1])));
    gk[22][1] = ((Cik[22][2][1]*gk[21][2])+((Cik[22][0][1]*gk[21][0])+(
      Cik[22][1][1]*gk[21][1])));
    gk[22][2] = ((Cik[22][2][2]*gk[21][2])+((Cik[22][0][2]*gk[21][0])+(
      Cik[22][1][2]*gk[21][1])));
    gk[23][0] = ((Cik[23][2][0]*gk[22][2])+((Cik[23][0][0]*gk[22][0])+(
      Cik[23][1][0]*gk[22][1])));
    gk[23][1] = ((Cik[23][2][1]*gk[22][2])+((Cik[23][0][1]*gk[22][0])+(
      Cik[23][1][1]*gk[22][1])));
    gk[23][2] = ((Cik[23][2][2]*gk[22][2])+((Cik[23][0][2]*gk[22][0])+(
      Cik[23][1][2]*gk[22][1])));
    gk[24][0] = ((Cik[24][2][0]*gk[23][2])+((Cik[24][0][0]*gk[23][0])+(
      Cik[24][1][0]*gk[23][1])));
    gk[24][1] = ((Cik[24][2][1]*gk[23][2])+((Cik[24][0][1]*gk[23][0])+(
      Cik[24][1][1]*gk[23][1])));
    gk[24][2] = ((Cik[24][2][2]*gk[23][2])+((Cik[24][0][2]*gk[23][0])+(
      Cik[24][1][2]*gk[23][1])));
    gk[25][0] = ((Cik[25][2][0]*gk[24][2])+((Cik[25][0][0]*gk[24][0])+(
      Cik[25][1][0]*gk[24][1])));
    gk[25][1] = ((Cik[25][2][1]*gk[24][2])+((Cik[25][0][1]*gk[24][0])+(
      Cik[25][1][1]*gk[24][1])));
    gk[25][2] = ((Cik[25][2][2]*gk[24][2])+((Cik[25][0][2]*gk[24][0])+(
      Cik[25][1][2]*gk[24][1])));
    gk[26][0] = ((Cik[26][2][0]*gk[25][2])+((Cik[26][0][0]*gk[25][0])+(
      Cik[26][1][0]*gk[25][1])));
    gk[26][1] = ((Cik[26][2][1]*gk[25][2])+((Cik[26][0][1]*gk[25][0])+(
      Cik[26][1][1]*gk[25][1])));
    gk[26][2] = ((Cik[26][2][2]*gk[25][2])+((Cik[26][0][2]*gk[25][0])+(
      Cik[26][1][2]*gk[25][1])));
    gk[27][0] = ((Cik[27][2][0]*gk[26][2])+((Cik[27][0][0]*gk[26][0])+(
      Cik[27][1][0]*gk[26][1])));
    gk[27][1] = ((Cik[27][2][1]*gk[26][2])+((Cik[27][0][1]*gk[26][0])+(
      Cik[27][1][1]*gk[26][1])));
    gk[27][2] = ((Cik[27][2][2]*gk[26][2])+((Cik[27][0][2]*gk[26][0])+(
      Cik[27][1][2]*gk[26][1])));
    gk[28][0] = ((Cik[28][2][0]*gk[27][2])+((Cik[28][0][0]*gk[27][0])+(
      Cik[28][1][0]*gk[27][1])));
    gk[28][1] = ((Cik[28][2][1]*gk[27][2])+((Cik[28][0][1]*gk[27][0])+(
      Cik[28][1][1]*gk[27][1])));
    gk[28][2] = ((Cik[28][2][2]*gk[27][2])+((Cik[28][0][2]*gk[27][0])+(
      Cik[28][1][2]*gk[27][1])));
    gk[29][0] = ((Cik[29][2][0]*gk[28][2])+((Cik[29][0][0]*gk[28][0])+(
      Cik[29][1][0]*gk[28][1])));
    gk[29][1] = ((Cik[29][2][1]*gk[28][2])+((Cik[29][0][1]*gk[28][0])+(
      Cik[29][1][1]*gk[28][1])));
    gk[29][2] = ((Cik[29][2][2]*gk[28][2])+((Cik[29][0][2]*gk[28][0])+(
      Cik[29][1][2]*gk[28][1])));
    gk[30][0] = ((Cik[30][2][0]*gk[29][2])+((Cik[30][0][0]*gk[29][0])+(
      Cik[30][1][0]*gk[29][1])));
    gk[30][1] = ((Cik[30][2][1]*gk[29][2])+((Cik[30][0][1]*gk[29][0])+(
      Cik[30][1][1]*gk[29][1])));
    gk[30][2] = ((Cik[30][2][2]*gk[29][2])+((Cik[30][0][2]*gk[29][0])+(
      Cik[30][1][2]*gk[29][1])));
    gk[31][0] = ((Cik[31][2][0]*gk[30][2])+((Cik[31][0][0]*gk[30][0])+(
      Cik[31][1][0]*gk[30][1])));
    gk[31][1] = ((Cik[31][2][1]*gk[30][2])+((Cik[31][0][1]*gk[30][0])+(
      Cik[31][1][1]*gk[30][1])));
    gk[31][2] = ((Cik[31][2][2]*gk[30][2])+((Cik[31][0][2]*gk[30][0])+(
      Cik[31][1][2]*gk[30][1])));
    gk[32][0] = ((Cik[32][2][0]*gk[31][2])+((Cik[32][0][0]*gk[31][0])+(
      Cik[32][1][0]*gk[31][1])));
    gk[32][1] = ((Cik[32][2][1]*gk[31][2])+((Cik[32][0][1]*gk[31][0])+(
      Cik[32][1][1]*gk[31][1])));
    gk[32][2] = ((Cik[32][2][2]*gk[31][2])+((Cik[32][0][2]*gk[31][0])+(
      Cik[32][1][2]*gk[31][1])));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[6][0][0] = ((Cik[3][0][2]*Cik[6][2][0])+((Cik[3][0][0]*Cik[6][0][0])+(
      Cik[3][0][1]*Cik[6][1][0])));
    cnk[6][0][1] = ((Cik[3][0][2]*Cik[6][2][1])+((Cik[3][0][0]*Cik[6][0][1])+(
      Cik[3][0][1]*Cik[6][1][1])));
    cnk[6][0][2] = ((Cik[3][0][2]*Cik[6][2][2])+((Cik[3][0][0]*Cik[6][0][2])+(
      Cik[3][0][1]*Cik[6][1][2])));
    cnk[6][1][0] = ((Cik[3][1][2]*Cik[6][2][0])+((Cik[3][1][0]*Cik[6][0][0])+(
      Cik[3][1][1]*Cik[6][1][0])));
    cnk[6][1][1] = ((Cik[3][1][2]*Cik[6][2][1])+((Cik[3][1][0]*Cik[6][0][1])+(
      Cik[3][1][1]*Cik[6][1][1])));
    cnk[6][1][2] = ((Cik[3][1][2]*Cik[6][2][2])+((Cik[3][1][0]*Cik[6][0][2])+(
      Cik[3][1][1]*Cik[6][1][2])));
    cnk[6][2][0] = ((Cik[3][2][2]*Cik[6][2][0])+((Cik[3][2][0]*Cik[6][0][0])+(
      Cik[3][2][1]*Cik[6][1][0])));
    cnk[6][2][1] = ((Cik[3][2][2]*Cik[6][2][1])+((Cik[3][2][0]*Cik[6][0][1])+(
      Cik[3][2][1]*Cik[6][1][1])));
    cnk[6][2][2] = ((Cik[3][2][2]*Cik[6][2][2])+((Cik[3][2][0]*Cik[6][0][2])+(
      Cik[3][2][1]*Cik[6][1][2])));
    cnk[7][0][0] = ((Cik[7][2][0]*cnk[6][0][2])+((Cik[7][0][0]*cnk[6][0][0])+(
      Cik[7][1][0]*cnk[6][0][1])));
    cnk[7][0][1] = ((Cik[7][2][1]*cnk[6][0][2])+((Cik[7][0][1]*cnk[6][0][0])+(
      Cik[7][1][1]*cnk[6][0][1])));
    cnk[7][0][2] = ((Cik[7][2][2]*cnk[6][0][2])+((Cik[7][0][2]*cnk[6][0][0])+(
      Cik[7][1][2]*cnk[6][0][1])));
    cnk[7][1][0] = ((Cik[7][2][0]*cnk[6][1][2])+((Cik[7][0][0]*cnk[6][1][0])+(
      Cik[7][1][0]*cnk[6][1][1])));
    cnk[7][1][1] = ((Cik[7][2][1]*cnk[6][1][2])+((Cik[7][0][1]*cnk[6][1][0])+(
      Cik[7][1][1]*cnk[6][1][1])));
    cnk[7][1][2] = ((Cik[7][2][2]*cnk[6][1][2])+((Cik[7][0][2]*cnk[6][1][0])+(
      Cik[7][1][2]*cnk[6][1][1])));
    cnk[7][2][0] = ((Cik[7][2][0]*cnk[6][2][2])+((Cik[7][0][0]*cnk[6][2][0])+(
      Cik[7][1][0]*cnk[6][2][1])));
    cnk[7][2][1] = ((Cik[7][2][1]*cnk[6][2][2])+((Cik[7][0][1]*cnk[6][2][0])+(
      Cik[7][1][1]*cnk[6][2][1])));
    cnk[7][2][2] = ((Cik[7][2][2]*cnk[6][2][2])+((Cik[7][0][2]*cnk[6][2][0])+(
      Cik[7][1][2]*cnk[6][2][1])));
    cnk[8][0][0] = ((Cik[8][2][0]*cnk[7][0][2])+((Cik[8][0][0]*cnk[7][0][0])+(
      Cik[8][1][0]*cnk[7][0][1])));
    cnk[8][0][1] = ((Cik[8][2][1]*cnk[7][0][2])+((Cik[8][0][1]*cnk[7][0][0])+(
      Cik[8][1][1]*cnk[7][0][1])));
    cnk[8][0][2] = ((Cik[8][2][2]*cnk[7][0][2])+((Cik[8][0][2]*cnk[7][0][0])+(
      Cik[8][1][2]*cnk[7][0][1])));
    cnk[8][1][0] = ((Cik[8][2][0]*cnk[7][1][2])+((Cik[8][0][0]*cnk[7][1][0])+(
      Cik[8][1][0]*cnk[7][1][1])));
    cnk[8][1][1] = ((Cik[8][2][1]*cnk[7][1][2])+((Cik[8][0][1]*cnk[7][1][0])+(
      Cik[8][1][1]*cnk[7][1][1])));
    cnk[8][1][2] = ((Cik[8][2][2]*cnk[7][1][2])+((Cik[8][0][2]*cnk[7][1][0])+(
      Cik[8][1][2]*cnk[7][1][1])));
    cnk[8][2][0] = ((Cik[8][2][0]*cnk[7][2][2])+((Cik[8][0][0]*cnk[7][2][0])+(
      Cik[8][1][0]*cnk[7][2][1])));
    cnk[8][2][1] = ((Cik[8][2][1]*cnk[7][2][2])+((Cik[8][0][1]*cnk[7][2][0])+(
      Cik[8][1][1]*cnk[7][2][1])));
    cnk[8][2][2] = ((Cik[8][2][2]*cnk[7][2][2])+((Cik[8][0][2]*cnk[7][2][0])+(
      Cik[8][1][2]*cnk[7][2][1])));
    cnk[9][0][0] = ((Cik[3][0][2]*Cik[9][2][0])+((Cik[3][0][0]*Cik[9][0][0])+(
      Cik[3][0][1]*Cik[9][1][0])));
    cnk[9][0][1] = ((Cik[3][0][2]*Cik[9][2][1])+((Cik[3][0][0]*Cik[9][0][1])+(
      Cik[3][0][1]*Cik[9][1][1])));
    cnk[9][0][2] = ((Cik[3][0][2]*Cik[9][2][2])+((Cik[3][0][0]*Cik[9][0][2])+(
      Cik[3][0][1]*Cik[9][1][2])));
    cnk[9][1][0] = ((Cik[3][1][2]*Cik[9][2][0])+((Cik[3][1][0]*Cik[9][0][0])+(
      Cik[3][1][1]*Cik[9][1][0])));
    cnk[9][1][1] = ((Cik[3][1][2]*Cik[9][2][1])+((Cik[3][1][0]*Cik[9][0][1])+(
      Cik[3][1][1]*Cik[9][1][1])));
    cnk[9][1][2] = ((Cik[3][1][2]*Cik[9][2][2])+((Cik[3][1][0]*Cik[9][0][2])+(
      Cik[3][1][1]*Cik[9][1][2])));
    cnk[9][2][0] = ((Cik[3][2][2]*Cik[9][2][0])+((Cik[3][2][0]*Cik[9][0][0])+(
      Cik[3][2][1]*Cik[9][1][0])));
    cnk[9][2][1] = ((Cik[3][2][2]*Cik[9][2][1])+((Cik[3][2][0]*Cik[9][0][1])+(
      Cik[3][2][1]*Cik[9][1][1])));
    cnk[9][2][2] = ((Cik[3][2][2]*Cik[9][2][2])+((Cik[3][2][0]*Cik[9][0][2])+(
      Cik[3][2][1]*Cik[9][1][2])));
    cnk[10][0][0] = ((Cik[10][2][0]*cnk[9][0][2])+((Cik[10][0][0]*cnk[9][0][0])+
      (Cik[10][1][0]*cnk[9][0][1])));
    cnk[10][0][1] = ((Cik[10][2][1]*cnk[9][0][2])+((Cik[10][0][1]*cnk[9][0][0])+
      (Cik[10][1][1]*cnk[9][0][1])));
    cnk[10][0][2] = ((Cik[10][2][2]*cnk[9][0][2])+((Cik[10][0][2]*cnk[9][0][0])+
      (Cik[10][1][2]*cnk[9][0][1])));
    cnk[10][1][0] = ((Cik[10][2][0]*cnk[9][1][2])+((Cik[10][0][0]*cnk[9][1][0])+
      (Cik[10][1][0]*cnk[9][1][1])));
    cnk[10][1][1] = ((Cik[10][2][1]*cnk[9][1][2])+((Cik[10][0][1]*cnk[9][1][0])+
      (Cik[10][1][1]*cnk[9][1][1])));
    cnk[10][1][2] = ((Cik[10][2][2]*cnk[9][1][2])+((Cik[10][0][2]*cnk[9][1][0])+
      (Cik[10][1][2]*cnk[9][1][1])));
    cnk[10][2][0] = ((Cik[10][2][0]*cnk[9][2][2])+((Cik[10][0][0]*cnk[9][2][0])+
      (Cik[10][1][0]*cnk[9][2][1])));
    cnk[10][2][1] = ((Cik[10][2][1]*cnk[9][2][2])+((Cik[10][0][1]*cnk[9][2][0])+
      (Cik[10][1][1]*cnk[9][2][1])));
    cnk[10][2][2] = ((Cik[10][2][2]*cnk[9][2][2])+((Cik[10][0][2]*cnk[9][2][0])+
      (Cik[10][1][2]*cnk[9][2][1])));
    cnk[11][0][0] = ((Cik[11][2][0]*cnk[10][0][2])+((Cik[11][0][0]*cnk[10][0][0]
      )+(Cik[11][1][0]*cnk[10][0][1])));
    cnk[11][0][1] = ((Cik[11][2][1]*cnk[10][0][2])+((Cik[11][0][1]*cnk[10][0][0]
      )+(Cik[11][1][1]*cnk[10][0][1])));
    cnk[11][0][2] = ((Cik[11][2][2]*cnk[10][0][2])+((Cik[11][0][2]*cnk[10][0][0]
      )+(Cik[11][1][2]*cnk[10][0][1])));
    cnk[11][1][0] = ((Cik[11][2][0]*cnk[10][1][2])+((Cik[11][0][0]*cnk[10][1][0]
      )+(Cik[11][1][0]*cnk[10][1][1])));
    cnk[11][1][1] = ((Cik[11][2][1]*cnk[10][1][2])+((Cik[11][0][1]*cnk[10][1][0]
      )+(Cik[11][1][1]*cnk[10][1][1])));
    cnk[11][1][2] = ((Cik[11][2][2]*cnk[10][1][2])+((Cik[11][0][2]*cnk[10][1][0]
      )+(Cik[11][1][2]*cnk[10][1][1])));
    cnk[11][2][0] = ((Cik[11][2][0]*cnk[10][2][2])+((Cik[11][0][0]*cnk[10][2][0]
      )+(Cik[11][1][0]*cnk[10][2][1])));
    cnk[11][2][1] = ((Cik[11][2][1]*cnk[10][2][2])+((Cik[11][0][1]*cnk[10][2][0]
      )+(Cik[11][1][1]*cnk[10][2][1])));
    cnk[11][2][2] = ((Cik[11][2][2]*cnk[10][2][2])+((Cik[11][0][2]*cnk[10][2][0]
      )+(Cik[11][1][2]*cnk[10][2][1])));
    cnk[12][0][0] = ((Cik[12][2][0]*cnk[11][0][2])+((Cik[12][0][0]*cnk[11][0][0]
      )+(Cik[12][1][0]*cnk[11][0][1])));
    cnk[12][0][1] = ((Cik[12][2][1]*cnk[11][0][2])+((Cik[12][0][1]*cnk[11][0][0]
      )+(Cik[12][1][1]*cnk[11][0][1])));
    cnk[12][0][2] = ((Cik[12][2][2]*cnk[11][0][2])+((Cik[12][0][2]*cnk[11][0][0]
      )+(Cik[12][1][2]*cnk[11][0][1])));
    cnk[12][1][0] = ((Cik[12][2][0]*cnk[11][1][2])+((Cik[12][0][0]*cnk[11][1][0]
      )+(Cik[12][1][0]*cnk[11][1][1])));
    cnk[12][1][1] = ((Cik[12][2][1]*cnk[11][1][2])+((Cik[12][0][1]*cnk[11][1][0]
      )+(Cik[12][1][1]*cnk[11][1][1])));
    cnk[12][1][2] = ((Cik[12][2][2]*cnk[11][1][2])+((Cik[12][0][2]*cnk[11][1][0]
      )+(Cik[12][1][2]*cnk[11][1][1])));
    cnk[12][2][0] = ((Cik[12][2][0]*cnk[11][2][2])+((Cik[12][0][0]*cnk[11][2][0]
      )+(Cik[12][1][0]*cnk[11][2][1])));
    cnk[12][2][1] = ((Cik[12][2][1]*cnk[11][2][2])+((Cik[12][0][1]*cnk[11][2][0]
      )+(Cik[12][1][1]*cnk[11][2][1])));
    cnk[12][2][2] = ((Cik[12][2][2]*cnk[11][2][2])+((Cik[12][0][2]*cnk[11][2][0]
      )+(Cik[12][1][2]*cnk[11][2][1])));
    cnk[13][0][0] = ((Cik[13][2][0]*cnk[12][0][2])+((Cik[13][0][0]*cnk[12][0][0]
      )+(Cik[13][1][0]*cnk[12][0][1])));
    cnk[13][0][1] = ((Cik[13][2][1]*cnk[12][0][2])+((Cik[13][0][1]*cnk[12][0][0]
      )+(Cik[13][1][1]*cnk[12][0][1])));
    cnk[13][0][2] = ((Cik[13][2][2]*cnk[12][0][2])+((Cik[13][0][2]*cnk[12][0][0]
      )+(Cik[13][1][2]*cnk[12][0][1])));
    cnk[13][1][0] = ((Cik[13][2][0]*cnk[12][1][2])+((Cik[13][0][0]*cnk[12][1][0]
      )+(Cik[13][1][0]*cnk[12][1][1])));
    cnk[13][1][1] = ((Cik[13][2][1]*cnk[12][1][2])+((Cik[13][0][1]*cnk[12][1][0]
      )+(Cik[13][1][1]*cnk[12][1][1])));
    cnk[13][1][2] = ((Cik[13][2][2]*cnk[12][1][2])+((Cik[13][0][2]*cnk[12][1][0]
      )+(Cik[13][1][2]*cnk[12][1][1])));
    cnk[13][2][0] = ((Cik[13][2][0]*cnk[12][2][2])+((Cik[13][0][0]*cnk[12][2][0]
      )+(Cik[13][1][0]*cnk[12][2][1])));
    cnk[13][2][1] = ((Cik[13][2][1]*cnk[12][2][2])+((Cik[13][0][1]*cnk[12][2][0]
      )+(Cik[13][1][1]*cnk[12][2][1])));
    cnk[13][2][2] = ((Cik[13][2][2]*cnk[12][2][2])+((Cik[13][0][2]*cnk[12][2][0]
      )+(Cik[13][1][2]*cnk[12][2][1])));
    cnk[14][0][0] = ((Cik[14][2][0]*cnk[13][0][2])+((Cik[14][0][0]*cnk[13][0][0]
      )+(Cik[14][1][0]*cnk[13][0][1])));
    cnk[14][0][1] = ((Cik[14][2][1]*cnk[13][0][2])+((Cik[14][0][1]*cnk[13][0][0]
      )+(Cik[14][1][1]*cnk[13][0][1])));
    cnk[14][0][2] = ((Cik[14][2][2]*cnk[13][0][2])+((Cik[14][0][2]*cnk[13][0][0]
      )+(Cik[14][1][2]*cnk[13][0][1])));
    cnk[14][1][0] = ((Cik[14][2][0]*cnk[13][1][2])+((Cik[14][0][0]*cnk[13][1][0]
      )+(Cik[14][1][0]*cnk[13][1][1])));
    cnk[14][1][1] = ((Cik[14][2][1]*cnk[13][1][2])+((Cik[14][0][1]*cnk[13][1][0]
      )+(Cik[14][1][1]*cnk[13][1][1])));
    cnk[14][1][2] = ((Cik[14][2][2]*cnk[13][1][2])+((Cik[14][0][2]*cnk[13][1][0]
      )+(Cik[14][1][2]*cnk[13][1][1])));
    cnk[14][2][0] = ((Cik[14][2][0]*cnk[13][2][2])+((Cik[14][0][0]*cnk[13][2][0]
      )+(Cik[14][1][0]*cnk[13][2][1])));
    cnk[14][2][1] = ((Cik[14][2][1]*cnk[13][2][2])+((Cik[14][0][1]*cnk[13][2][0]
      )+(Cik[14][1][1]*cnk[13][2][1])));
    cnk[14][2][2] = ((Cik[14][2][2]*cnk[13][2][2])+((Cik[14][0][2]*cnk[13][2][0]
      )+(Cik[14][1][2]*cnk[13][2][1])));
    cnk[15][0][0] = ((Cik[15][2][0]*cnk[14][0][2])+((Cik[15][0][0]*cnk[14][0][0]
      )+(Cik[15][1][0]*cnk[14][0][1])));
    cnk[15][0][1] = ((Cik[15][2][1]*cnk[14][0][2])+((Cik[15][0][1]*cnk[14][0][0]
      )+(Cik[15][1][1]*cnk[14][0][1])));
    cnk[15][0][2] = ((Cik[15][2][2]*cnk[14][0][2])+((Cik[15][0][2]*cnk[14][0][0]
      )+(Cik[15][1][2]*cnk[14][0][1])));
    cnk[15][1][0] = ((Cik[15][2][0]*cnk[14][1][2])+((Cik[15][0][0]*cnk[14][1][0]
      )+(Cik[15][1][0]*cnk[14][1][1])));
    cnk[15][1][1] = ((Cik[15][2][1]*cnk[14][1][2])+((Cik[15][0][1]*cnk[14][1][0]
      )+(Cik[15][1][1]*cnk[14][1][1])));
    cnk[15][1][2] = ((Cik[15][2][2]*cnk[14][1][2])+((Cik[15][0][2]*cnk[14][1][0]
      )+(Cik[15][1][2]*cnk[14][1][1])));
    cnk[15][2][0] = ((Cik[15][2][0]*cnk[14][2][2])+((Cik[15][0][0]*cnk[14][2][0]
      )+(Cik[15][1][0]*cnk[14][2][1])));
    cnk[15][2][1] = ((Cik[15][2][1]*cnk[14][2][2])+((Cik[15][0][1]*cnk[14][2][0]
      )+(Cik[15][1][1]*cnk[14][2][1])));
    cnk[15][2][2] = ((Cik[15][2][2]*cnk[14][2][2])+((Cik[15][0][2]*cnk[14][2][0]
      )+(Cik[15][1][2]*cnk[14][2][1])));
    cnk[16][0][0] = ((Cik[16][2][0]*cnk[15][0][2])+((Cik[16][0][0]*cnk[15][0][0]
      )+(Cik[16][1][0]*cnk[15][0][1])));
    cnk[16][0][1] = ((Cik[16][2][1]*cnk[15][0][2])+((Cik[16][0][1]*cnk[15][0][0]
      )+(Cik[16][1][1]*cnk[15][0][1])));
    cnk[16][0][2] = ((Cik[16][2][2]*cnk[15][0][2])+((Cik[16][0][2]*cnk[15][0][0]
      )+(Cik[16][1][2]*cnk[15][0][1])));
    cnk[16][1][0] = ((Cik[16][2][0]*cnk[15][1][2])+((Cik[16][0][0]*cnk[15][1][0]
      )+(Cik[16][1][0]*cnk[15][1][1])));
    cnk[16][1][1] = ((Cik[16][2][1]*cnk[15][1][2])+((Cik[16][0][1]*cnk[15][1][0]
      )+(Cik[16][1][1]*cnk[15][1][1])));
    cnk[16][1][2] = ((Cik[16][2][2]*cnk[15][1][2])+((Cik[16][0][2]*cnk[15][1][0]
      )+(Cik[16][1][2]*cnk[15][1][1])));
    cnk[16][2][0] = ((Cik[16][2][0]*cnk[15][2][2])+((Cik[16][0][0]*cnk[15][2][0]
      )+(Cik[16][1][0]*cnk[15][2][1])));
    cnk[16][2][1] = ((Cik[16][2][1]*cnk[15][2][2])+((Cik[16][0][1]*cnk[15][2][0]
      )+(Cik[16][1][1]*cnk[15][2][1])));
    cnk[16][2][2] = ((Cik[16][2][2]*cnk[15][2][2])+((Cik[16][0][2]*cnk[15][2][0]
      )+(Cik[16][1][2]*cnk[15][2][1])));
    cnk[17][0][0] = ((Cik[17][2][0]*cnk[16][0][2])+((Cik[17][0][0]*cnk[16][0][0]
      )+(Cik[17][1][0]*cnk[16][0][1])));
    cnk[17][0][1] = ((Cik[17][2][1]*cnk[16][0][2])+((Cik[17][0][1]*cnk[16][0][0]
      )+(Cik[17][1][1]*cnk[16][0][1])));
    cnk[17][0][2] = ((Cik[17][2][2]*cnk[16][0][2])+((Cik[17][0][2]*cnk[16][0][0]
      )+(Cik[17][1][2]*cnk[16][0][1])));
    cnk[17][1][0] = ((Cik[17][2][0]*cnk[16][1][2])+((Cik[17][0][0]*cnk[16][1][0]
      )+(Cik[17][1][0]*cnk[16][1][1])));
    cnk[17][1][1] = ((Cik[17][2][1]*cnk[16][1][2])+((Cik[17][0][1]*cnk[16][1][0]
      )+(Cik[17][1][1]*cnk[16][1][1])));
    cnk[17][1][2] = ((Cik[17][2][2]*cnk[16][1][2])+((Cik[17][0][2]*cnk[16][1][0]
      )+(Cik[17][1][2]*cnk[16][1][1])));
    cnk[17][2][0] = ((Cik[17][2][0]*cnk[16][2][2])+((Cik[17][0][0]*cnk[16][2][0]
      )+(Cik[17][1][0]*cnk[16][2][1])));
    cnk[17][2][1] = ((Cik[17][2][1]*cnk[16][2][2])+((Cik[17][0][1]*cnk[16][2][0]
      )+(Cik[17][1][1]*cnk[16][2][1])));
    cnk[17][2][2] = ((Cik[17][2][2]*cnk[16][2][2])+((Cik[17][0][2]*cnk[16][2][0]
      )+(Cik[17][1][2]*cnk[16][2][1])));
    cnk[18][0][0] = ((Cik[18][2][0]*cnk[17][0][2])+((Cik[18][0][0]*cnk[17][0][0]
      )+(Cik[18][1][0]*cnk[17][0][1])));
    cnk[18][0][1] = ((Cik[18][2][1]*cnk[17][0][2])+((Cik[18][0][1]*cnk[17][0][0]
      )+(Cik[18][1][1]*cnk[17][0][1])));
    cnk[18][0][2] = ((Cik[18][2][2]*cnk[17][0][2])+((Cik[18][0][2]*cnk[17][0][0]
      )+(Cik[18][1][2]*cnk[17][0][1])));
    cnk[18][1][0] = ((Cik[18][2][0]*cnk[17][1][2])+((Cik[18][0][0]*cnk[17][1][0]
      )+(Cik[18][1][0]*cnk[17][1][1])));
    cnk[18][1][1] = ((Cik[18][2][1]*cnk[17][1][2])+((Cik[18][0][1]*cnk[17][1][0]
      )+(Cik[18][1][1]*cnk[17][1][1])));
    cnk[18][1][2] = ((Cik[18][2][2]*cnk[17][1][2])+((Cik[18][0][2]*cnk[17][1][0]
      )+(Cik[18][1][2]*cnk[17][1][1])));
    cnk[18][2][0] = ((Cik[18][2][0]*cnk[17][2][2])+((Cik[18][0][0]*cnk[17][2][0]
      )+(Cik[18][1][0]*cnk[17][2][1])));
    cnk[18][2][1] = ((Cik[18][2][1]*cnk[17][2][2])+((Cik[18][0][1]*cnk[17][2][0]
      )+(Cik[18][1][1]*cnk[17][2][1])));
    cnk[18][2][2] = ((Cik[18][2][2]*cnk[17][2][2])+((Cik[18][0][2]*cnk[17][2][0]
      )+(Cik[18][1][2]*cnk[17][2][1])));
    cnk[19][0][0] = ((Cik[19][2][0]*cnk[18][0][2])+((Cik[19][0][0]*cnk[18][0][0]
      )+(Cik[19][1][0]*cnk[18][0][1])));
    cnk[19][0][1] = ((Cik[19][2][1]*cnk[18][0][2])+((Cik[19][0][1]*cnk[18][0][0]
      )+(Cik[19][1][1]*cnk[18][0][1])));
    cnk[19][0][2] = ((Cik[19][2][2]*cnk[18][0][2])+((Cik[19][0][2]*cnk[18][0][0]
      )+(Cik[19][1][2]*cnk[18][0][1])));
    cnk[19][1][0] = ((Cik[19][2][0]*cnk[18][1][2])+((Cik[19][0][0]*cnk[18][1][0]
      )+(Cik[19][1][0]*cnk[18][1][1])));
    cnk[19][1][1] = ((Cik[19][2][1]*cnk[18][1][2])+((Cik[19][0][1]*cnk[18][1][0]
      )+(Cik[19][1][1]*cnk[18][1][1])));
    cnk[19][1][2] = ((Cik[19][2][2]*cnk[18][1][2])+((Cik[19][0][2]*cnk[18][1][0]
      )+(Cik[19][1][2]*cnk[18][1][1])));
    cnk[19][2][0] = ((Cik[19][2][0]*cnk[18][2][2])+((Cik[19][0][0]*cnk[18][2][0]
      )+(Cik[19][1][0]*cnk[18][2][1])));
    cnk[19][2][1] = ((Cik[19][2][1]*cnk[18][2][2])+((Cik[19][0][1]*cnk[18][2][0]
      )+(Cik[19][1][1]*cnk[18][2][1])));
    cnk[19][2][2] = ((Cik[19][2][2]*cnk[18][2][2])+((Cik[19][0][2]*cnk[18][2][0]
      )+(Cik[19][1][2]*cnk[18][2][1])));
    cnk[20][0][0] = ((Cik[20][2][0]*cnk[19][0][2])+((Cik[20][0][0]*cnk[19][0][0]
      )+(Cik[20][1][0]*cnk[19][0][1])));
    cnk[20][0][1] = ((Cik[20][2][1]*cnk[19][0][2])+((Cik[20][0][1]*cnk[19][0][0]
      )+(Cik[20][1][1]*cnk[19][0][1])));
    cnk[20][0][2] = ((Cik[20][2][2]*cnk[19][0][2])+((Cik[20][0][2]*cnk[19][0][0]
      )+(Cik[20][1][2]*cnk[19][0][1])));
    cnk[20][1][0] = ((Cik[20][2][0]*cnk[19][1][2])+((Cik[20][0][0]*cnk[19][1][0]
      )+(Cik[20][1][0]*cnk[19][1][1])));
    cnk[20][1][1] = ((Cik[20][2][1]*cnk[19][1][2])+((Cik[20][0][1]*cnk[19][1][0]
      )+(Cik[20][1][1]*cnk[19][1][1])));
    cnk[20][1][2] = ((Cik[20][2][2]*cnk[19][1][2])+((Cik[20][0][2]*cnk[19][1][0]
      )+(Cik[20][1][2]*cnk[19][1][1])));
    cnk[20][2][0] = ((Cik[20][2][0]*cnk[19][2][2])+((Cik[20][0][0]*cnk[19][2][0]
      )+(Cik[20][1][0]*cnk[19][2][1])));
    cnk[20][2][1] = ((Cik[20][2][1]*cnk[19][2][2])+((Cik[20][0][1]*cnk[19][2][0]
      )+(Cik[20][1][1]*cnk[19][2][1])));
    cnk[20][2][2] = ((Cik[20][2][2]*cnk[19][2][2])+((Cik[20][0][2]*cnk[19][2][0]
      )+(Cik[20][1][2]*cnk[19][2][1])));
    cnk[21][0][0] = ((Cik[3][0][2]*Cik[21][2][0])+((Cik[3][0][0]*Cik[21][0][0])+
      (Cik[3][0][1]*Cik[21][1][0])));
    cnk[21][0][1] = ((Cik[3][0][2]*Cik[21][2][1])+((Cik[3][0][0]*Cik[21][0][1])+
      (Cik[3][0][1]*Cik[21][1][1])));
    cnk[21][0][2] = ((Cik[3][0][2]*Cik[21][2][2])+((Cik[3][0][0]*Cik[21][0][2])+
      (Cik[3][0][1]*Cik[21][1][2])));
    cnk[21][1][0] = ((Cik[3][1][2]*Cik[21][2][0])+((Cik[3][1][0]*Cik[21][0][0])+
      (Cik[3][1][1]*Cik[21][1][0])));
    cnk[21][1][1] = ((Cik[3][1][2]*Cik[21][2][1])+((Cik[3][1][0]*Cik[21][0][1])+
      (Cik[3][1][1]*Cik[21][1][1])));
    cnk[21][1][2] = ((Cik[3][1][2]*Cik[21][2][2])+((Cik[3][1][0]*Cik[21][0][2])+
      (Cik[3][1][1]*Cik[21][1][2])));
    cnk[21][2][0] = ((Cik[3][2][2]*Cik[21][2][0])+((Cik[3][2][0]*Cik[21][0][0])+
      (Cik[3][2][1]*Cik[21][1][0])));
    cnk[21][2][1] = ((Cik[3][2][2]*Cik[21][2][1])+((Cik[3][2][0]*Cik[21][0][1])+
      (Cik[3][2][1]*Cik[21][1][1])));
    cnk[21][2][2] = ((Cik[3][2][2]*Cik[21][2][2])+((Cik[3][2][0]*Cik[21][0][2])+
      (Cik[3][2][1]*Cik[21][1][2])));
    cnk[22][0][0] = ((Cik[22][2][0]*cnk[21][0][2])+((Cik[22][0][0]*cnk[21][0][0]
      )+(Cik[22][1][0]*cnk[21][0][1])));
    cnk[22][0][1] = ((Cik[22][2][1]*cnk[21][0][2])+((Cik[22][0][1]*cnk[21][0][0]
      )+(Cik[22][1][1]*cnk[21][0][1])));
    cnk[22][0][2] = ((Cik[22][2][2]*cnk[21][0][2])+((Cik[22][0][2]*cnk[21][0][0]
      )+(Cik[22][1][2]*cnk[21][0][1])));
    cnk[22][1][0] = ((Cik[22][2][0]*cnk[21][1][2])+((Cik[22][0][0]*cnk[21][1][0]
      )+(Cik[22][1][0]*cnk[21][1][1])));
    cnk[22][1][1] = ((Cik[22][2][1]*cnk[21][1][2])+((Cik[22][0][1]*cnk[21][1][0]
      )+(Cik[22][1][1]*cnk[21][1][1])));
    cnk[22][1][2] = ((Cik[22][2][2]*cnk[21][1][2])+((Cik[22][0][2]*cnk[21][1][0]
      )+(Cik[22][1][2]*cnk[21][1][1])));
    cnk[22][2][0] = ((Cik[22][2][0]*cnk[21][2][2])+((Cik[22][0][0]*cnk[21][2][0]
      )+(Cik[22][1][0]*cnk[21][2][1])));
    cnk[22][2][1] = ((Cik[22][2][1]*cnk[21][2][2])+((Cik[22][0][1]*cnk[21][2][0]
      )+(Cik[22][1][1]*cnk[21][2][1])));
    cnk[22][2][2] = ((Cik[22][2][2]*cnk[21][2][2])+((Cik[22][0][2]*cnk[21][2][0]
      )+(Cik[22][1][2]*cnk[21][2][1])));
    cnk[23][0][0] = ((Cik[23][2][0]*cnk[22][0][2])+((Cik[23][0][0]*cnk[22][0][0]
      )+(Cik[23][1][0]*cnk[22][0][1])));
    cnk[23][0][1] = ((Cik[23][2][1]*cnk[22][0][2])+((Cik[23][0][1]*cnk[22][0][0]
      )+(Cik[23][1][1]*cnk[22][0][1])));
    cnk[23][0][2] = ((Cik[23][2][2]*cnk[22][0][2])+((Cik[23][0][2]*cnk[22][0][0]
      )+(Cik[23][1][2]*cnk[22][0][1])));
    cnk[23][1][0] = ((Cik[23][2][0]*cnk[22][1][2])+((Cik[23][0][0]*cnk[22][1][0]
      )+(Cik[23][1][0]*cnk[22][1][1])));
    cnk[23][1][1] = ((Cik[23][2][1]*cnk[22][1][2])+((Cik[23][0][1]*cnk[22][1][0]
      )+(Cik[23][1][1]*cnk[22][1][1])));
    cnk[23][1][2] = ((Cik[23][2][2]*cnk[22][1][2])+((Cik[23][0][2]*cnk[22][1][0]
      )+(Cik[23][1][2]*cnk[22][1][1])));
    cnk[23][2][0] = ((Cik[23][2][0]*cnk[22][2][2])+((Cik[23][0][0]*cnk[22][2][0]
      )+(Cik[23][1][0]*cnk[22][2][1])));
    cnk[23][2][1] = ((Cik[23][2][1]*cnk[22][2][2])+((Cik[23][0][1]*cnk[22][2][0]
      )+(Cik[23][1][1]*cnk[22][2][1])));
    cnk[23][2][2] = ((Cik[23][2][2]*cnk[22][2][2])+((Cik[23][0][2]*cnk[22][2][0]
      )+(Cik[23][1][2]*cnk[22][2][1])));
    cnk[24][0][0] = ((Cik[24][2][0]*cnk[23][0][2])+((Cik[24][0][0]*cnk[23][0][0]
      )+(Cik[24][1][0]*cnk[23][0][1])));
    cnk[24][0][1] = ((Cik[24][2][1]*cnk[23][0][2])+((Cik[24][0][1]*cnk[23][0][0]
      )+(Cik[24][1][1]*cnk[23][0][1])));
    cnk[24][0][2] = ((Cik[24][2][2]*cnk[23][0][2])+((Cik[24][0][2]*cnk[23][0][0]
      )+(Cik[24][1][2]*cnk[23][0][1])));
    cnk[24][1][0] = ((Cik[24][2][0]*cnk[23][1][2])+((Cik[24][0][0]*cnk[23][1][0]
      )+(Cik[24][1][0]*cnk[23][1][1])));
    cnk[24][1][1] = ((Cik[24][2][1]*cnk[23][1][2])+((Cik[24][0][1]*cnk[23][1][0]
      )+(Cik[24][1][1]*cnk[23][1][1])));
    cnk[24][1][2] = ((Cik[24][2][2]*cnk[23][1][2])+((Cik[24][0][2]*cnk[23][1][0]
      )+(Cik[24][1][2]*cnk[23][1][1])));
    cnk[24][2][0] = ((Cik[24][2][0]*cnk[23][2][2])+((Cik[24][0][0]*cnk[23][2][0]
      )+(Cik[24][1][0]*cnk[23][2][1])));
    cnk[24][2][1] = ((Cik[24][2][1]*cnk[23][2][2])+((Cik[24][0][1]*cnk[23][2][0]
      )+(Cik[24][1][1]*cnk[23][2][1])));
    cnk[24][2][2] = ((Cik[24][2][2]*cnk[23][2][2])+((Cik[24][0][2]*cnk[23][2][0]
      )+(Cik[24][1][2]*cnk[23][2][1])));
    cnk[25][0][0] = ((Cik[25][2][0]*cnk[24][0][2])+((Cik[25][0][0]*cnk[24][0][0]
      )+(Cik[25][1][0]*cnk[24][0][1])));
    cnk[25][0][1] = ((Cik[25][2][1]*cnk[24][0][2])+((Cik[25][0][1]*cnk[24][0][0]
      )+(Cik[25][1][1]*cnk[24][0][1])));
    cnk[25][0][2] = ((Cik[25][2][2]*cnk[24][0][2])+((Cik[25][0][2]*cnk[24][0][0]
      )+(Cik[25][1][2]*cnk[24][0][1])));
    cnk[25][1][0] = ((Cik[25][2][0]*cnk[24][1][2])+((Cik[25][0][0]*cnk[24][1][0]
      )+(Cik[25][1][0]*cnk[24][1][1])));
    cnk[25][1][1] = ((Cik[25][2][1]*cnk[24][1][2])+((Cik[25][0][1]*cnk[24][1][0]
      )+(Cik[25][1][1]*cnk[24][1][1])));
    cnk[25][1][2] = ((Cik[25][2][2]*cnk[24][1][2])+((Cik[25][0][2]*cnk[24][1][0]
      )+(Cik[25][1][2]*cnk[24][1][1])));
    cnk[25][2][0] = ((Cik[25][2][0]*cnk[24][2][2])+((Cik[25][0][0]*cnk[24][2][0]
      )+(Cik[25][1][0]*cnk[24][2][1])));
    cnk[25][2][1] = ((Cik[25][2][1]*cnk[24][2][2])+((Cik[25][0][1]*cnk[24][2][0]
      )+(Cik[25][1][1]*cnk[24][2][1])));
    cnk[25][2][2] = ((Cik[25][2][2]*cnk[24][2][2])+((Cik[25][0][2]*cnk[24][2][0]
      )+(Cik[25][1][2]*cnk[24][2][1])));
    cnk[26][0][0] = ((Cik[26][2][0]*cnk[25][0][2])+((Cik[26][0][0]*cnk[25][0][0]
      )+(Cik[26][1][0]*cnk[25][0][1])));
    cnk[26][0][1] = ((Cik[26][2][1]*cnk[25][0][2])+((Cik[26][0][1]*cnk[25][0][0]
      )+(Cik[26][1][1]*cnk[25][0][1])));
    cnk[26][0][2] = ((Cik[26][2][2]*cnk[25][0][2])+((Cik[26][0][2]*cnk[25][0][0]
      )+(Cik[26][1][2]*cnk[25][0][1])));
    cnk[26][1][0] = ((Cik[26][2][0]*cnk[25][1][2])+((Cik[26][0][0]*cnk[25][1][0]
      )+(Cik[26][1][0]*cnk[25][1][1])));
    cnk[26][1][1] = ((Cik[26][2][1]*cnk[25][1][2])+((Cik[26][0][1]*cnk[25][1][0]
      )+(Cik[26][1][1]*cnk[25][1][1])));
    cnk[26][1][2] = ((Cik[26][2][2]*cnk[25][1][2])+((Cik[26][0][2]*cnk[25][1][0]
      )+(Cik[26][1][2]*cnk[25][1][1])));
    cnk[26][2][0] = ((Cik[26][2][0]*cnk[25][2][2])+((Cik[26][0][0]*cnk[25][2][0]
      )+(Cik[26][1][0]*cnk[25][2][1])));
    cnk[26][2][1] = ((Cik[26][2][1]*cnk[25][2][2])+((Cik[26][0][1]*cnk[25][2][0]
      )+(Cik[26][1][1]*cnk[25][2][1])));
    cnk[26][2][2] = ((Cik[26][2][2]*cnk[25][2][2])+((Cik[26][0][2]*cnk[25][2][0]
      )+(Cik[26][1][2]*cnk[25][2][1])));
    cnk[27][0][0] = ((Cik[27][2][0]*cnk[26][0][2])+((Cik[27][0][0]*cnk[26][0][0]
      )+(Cik[27][1][0]*cnk[26][0][1])));
    cnk[27][0][1] = ((Cik[27][2][1]*cnk[26][0][2])+((Cik[27][0][1]*cnk[26][0][0]
      )+(Cik[27][1][1]*cnk[26][0][1])));
    cnk[27][0][2] = ((Cik[27][2][2]*cnk[26][0][2])+((Cik[27][0][2]*cnk[26][0][0]
      )+(Cik[27][1][2]*cnk[26][0][1])));
    cnk[27][1][0] = ((Cik[27][2][0]*cnk[26][1][2])+((Cik[27][0][0]*cnk[26][1][0]
      )+(Cik[27][1][0]*cnk[26][1][1])));
    cnk[27][1][1] = ((Cik[27][2][1]*cnk[26][1][2])+((Cik[27][0][1]*cnk[26][1][0]
      )+(Cik[27][1][1]*cnk[26][1][1])));
    cnk[27][1][2] = ((Cik[27][2][2]*cnk[26][1][2])+((Cik[27][0][2]*cnk[26][1][0]
      )+(Cik[27][1][2]*cnk[26][1][1])));
    cnk[27][2][0] = ((Cik[27][2][0]*cnk[26][2][2])+((Cik[27][0][0]*cnk[26][2][0]
      )+(Cik[27][1][0]*cnk[26][2][1])));
    cnk[27][2][1] = ((Cik[27][2][1]*cnk[26][2][2])+((Cik[27][0][1]*cnk[26][2][0]
      )+(Cik[27][1][1]*cnk[26][2][1])));
    cnk[27][2][2] = ((Cik[27][2][2]*cnk[26][2][2])+((Cik[27][0][2]*cnk[26][2][0]
      )+(Cik[27][1][2]*cnk[26][2][1])));
    cnk[28][0][0] = ((Cik[28][2][0]*cnk[27][0][2])+((Cik[28][0][0]*cnk[27][0][0]
      )+(Cik[28][1][0]*cnk[27][0][1])));
    cnk[28][0][1] = ((Cik[28][2][1]*cnk[27][0][2])+((Cik[28][0][1]*cnk[27][0][0]
      )+(Cik[28][1][1]*cnk[27][0][1])));
    cnk[28][0][2] = ((Cik[28][2][2]*cnk[27][0][2])+((Cik[28][0][2]*cnk[27][0][0]
      )+(Cik[28][1][2]*cnk[27][0][1])));
    cnk[28][1][0] = ((Cik[28][2][0]*cnk[27][1][2])+((Cik[28][0][0]*cnk[27][1][0]
      )+(Cik[28][1][0]*cnk[27][1][1])));
    cnk[28][1][1] = ((Cik[28][2][1]*cnk[27][1][2])+((Cik[28][0][1]*cnk[27][1][0]
      )+(Cik[28][1][1]*cnk[27][1][1])));
    cnk[28][1][2] = ((Cik[28][2][2]*cnk[27][1][2])+((Cik[28][0][2]*cnk[27][1][0]
      )+(Cik[28][1][2]*cnk[27][1][1])));
    cnk[28][2][0] = ((Cik[28][2][0]*cnk[27][2][2])+((Cik[28][0][0]*cnk[27][2][0]
      )+(Cik[28][1][0]*cnk[27][2][1])));
    cnk[28][2][1] = ((Cik[28][2][1]*cnk[27][2][2])+((Cik[28][0][1]*cnk[27][2][0]
      )+(Cik[28][1][1]*cnk[27][2][1])));
    cnk[28][2][2] = ((Cik[28][2][2]*cnk[27][2][2])+((Cik[28][0][2]*cnk[27][2][0]
      )+(Cik[28][1][2]*cnk[27][2][1])));
    cnk[29][0][0] = ((Cik[29][2][0]*cnk[28][0][2])+((Cik[29][0][0]*cnk[28][0][0]
      )+(Cik[29][1][0]*cnk[28][0][1])));
    cnk[29][0][1] = ((Cik[29][2][1]*cnk[28][0][2])+((Cik[29][0][1]*cnk[28][0][0]
      )+(Cik[29][1][1]*cnk[28][0][1])));
    cnk[29][0][2] = ((Cik[29][2][2]*cnk[28][0][2])+((Cik[29][0][2]*cnk[28][0][0]
      )+(Cik[29][1][2]*cnk[28][0][1])));
    cnk[29][1][0] = ((Cik[29][2][0]*cnk[28][1][2])+((Cik[29][0][0]*cnk[28][1][0]
      )+(Cik[29][1][0]*cnk[28][1][1])));
    cnk[29][1][1] = ((Cik[29][2][1]*cnk[28][1][2])+((Cik[29][0][1]*cnk[28][1][0]
      )+(Cik[29][1][1]*cnk[28][1][1])));
    cnk[29][1][2] = ((Cik[29][2][2]*cnk[28][1][2])+((Cik[29][0][2]*cnk[28][1][0]
      )+(Cik[29][1][2]*cnk[28][1][1])));
    cnk[29][2][0] = ((Cik[29][2][0]*cnk[28][2][2])+((Cik[29][0][0]*cnk[28][2][0]
      )+(Cik[29][1][0]*cnk[28][2][1])));
    cnk[29][2][1] = ((Cik[29][2][1]*cnk[28][2][2])+((Cik[29][0][1]*cnk[28][2][0]
      )+(Cik[29][1][1]*cnk[28][2][1])));
    cnk[29][2][2] = ((Cik[29][2][2]*cnk[28][2][2])+((Cik[29][0][2]*cnk[28][2][0]
      )+(Cik[29][1][2]*cnk[28][2][1])));
    cnk[30][0][0] = ((Cik[30][2][0]*cnk[29][0][2])+((Cik[30][0][0]*cnk[29][0][0]
      )+(Cik[30][1][0]*cnk[29][0][1])));
    cnk[30][0][1] = ((Cik[30][2][1]*cnk[29][0][2])+((Cik[30][0][1]*cnk[29][0][0]
      )+(Cik[30][1][1]*cnk[29][0][1])));
    cnk[30][0][2] = ((Cik[30][2][2]*cnk[29][0][2])+((Cik[30][0][2]*cnk[29][0][0]
      )+(Cik[30][1][2]*cnk[29][0][1])));
    cnk[30][1][0] = ((Cik[30][2][0]*cnk[29][1][2])+((Cik[30][0][0]*cnk[29][1][0]
      )+(Cik[30][1][0]*cnk[29][1][1])));
    cnk[30][1][1] = ((Cik[30][2][1]*cnk[29][1][2])+((Cik[30][0][1]*cnk[29][1][0]
      )+(Cik[30][1][1]*cnk[29][1][1])));
    cnk[30][1][2] = ((Cik[30][2][2]*cnk[29][1][2])+((Cik[30][0][2]*cnk[29][1][0]
      )+(Cik[30][1][2]*cnk[29][1][1])));
    cnk[30][2][0] = ((Cik[30][2][0]*cnk[29][2][2])+((Cik[30][0][0]*cnk[29][2][0]
      )+(Cik[30][1][0]*cnk[29][2][1])));
    cnk[30][2][1] = ((Cik[30][2][1]*cnk[29][2][2])+((Cik[30][0][1]*cnk[29][2][0]
      )+(Cik[30][1][1]*cnk[29][2][1])));
    cnk[30][2][2] = ((Cik[30][2][2]*cnk[29][2][2])+((Cik[30][0][2]*cnk[29][2][0]
      )+(Cik[30][1][2]*cnk[29][2][1])));
    cnk[31][0][0] = ((Cik[31][2][0]*cnk[30][0][2])+((Cik[31][0][0]*cnk[30][0][0]
      )+(Cik[31][1][0]*cnk[30][0][1])));
    cnk[31][0][1] = ((Cik[31][2][1]*cnk[30][0][2])+((Cik[31][0][1]*cnk[30][0][0]
      )+(Cik[31][1][1]*cnk[30][0][1])));
    cnk[31][0][2] = ((Cik[31][2][2]*cnk[30][0][2])+((Cik[31][0][2]*cnk[30][0][0]
      )+(Cik[31][1][2]*cnk[30][0][1])));
    cnk[31][1][0] = ((Cik[31][2][0]*cnk[30][1][2])+((Cik[31][0][0]*cnk[30][1][0]
      )+(Cik[31][1][0]*cnk[30][1][1])));
    cnk[31][1][1] = ((Cik[31][2][1]*cnk[30][1][2])+((Cik[31][0][1]*cnk[30][1][0]
      )+(Cik[31][1][1]*cnk[30][1][1])));
    cnk[31][1][2] = ((Cik[31][2][2]*cnk[30][1][2])+((Cik[31][0][2]*cnk[30][1][0]
      )+(Cik[31][1][2]*cnk[30][1][1])));
    cnk[31][2][0] = ((Cik[31][2][0]*cnk[30][2][2])+((Cik[31][0][0]*cnk[30][2][0]
      )+(Cik[31][1][0]*cnk[30][2][1])));
    cnk[31][2][1] = ((Cik[31][2][1]*cnk[30][2][2])+((Cik[31][0][1]*cnk[30][2][0]
      )+(Cik[31][1][1]*cnk[30][2][1])));
    cnk[31][2][2] = ((Cik[31][2][2]*cnk[30][2][2])+((Cik[31][0][2]*cnk[30][2][0]
      )+(Cik[31][1][2]*cnk[30][2][1])));
    cnk[32][0][0] = ((Cik[32][2][0]*cnk[31][0][2])+((Cik[32][0][0]*cnk[31][0][0]
      )+(Cik[32][1][0]*cnk[31][0][1])));
    cnk[32][0][1] = ((Cik[32][2][1]*cnk[31][0][2])+((Cik[32][0][1]*cnk[31][0][0]
      )+(Cik[32][1][1]*cnk[31][0][1])));
    cnk[32][0][2] = ((Cik[32][2][2]*cnk[31][0][2])+((Cik[32][0][2]*cnk[31][0][0]
      )+(Cik[32][1][2]*cnk[31][0][1])));
    cnk[32][1][0] = ((Cik[32][2][0]*cnk[31][1][2])+((Cik[32][0][0]*cnk[31][1][0]
      )+(Cik[32][1][0]*cnk[31][1][1])));
    cnk[32][1][1] = ((Cik[32][2][1]*cnk[31][1][2])+((Cik[32][0][1]*cnk[31][1][0]
      )+(Cik[32][1][1]*cnk[31][1][1])));
    cnk[32][1][2] = ((Cik[32][2][2]*cnk[31][1][2])+((Cik[32][0][2]*cnk[31][1][0]
      )+(Cik[32][1][2]*cnk[31][1][1])));
    cnk[32][2][0] = ((Cik[32][2][0]*cnk[31][2][2])+((Cik[32][0][0]*cnk[31][2][0]
      )+(Cik[32][1][0]*cnk[31][2][1])));
    cnk[32][2][1] = ((Cik[32][2][1]*cnk[31][2][2])+((Cik[32][0][1]*cnk[31][2][0]
      )+(Cik[32][1][1]*cnk[31][2][1])));
    cnk[32][2][2] = ((Cik[32][2][2]*cnk[31][2][2])+((Cik[32][0][2]*cnk[31][2][0]
      )+(Cik[32][1][2]*cnk[31][2][1])));
    cnb[0][0][0] = Cik[3][0][0];
    cnb[0][0][1] = Cik[3][0][1];
    cnb[0][0][2] = Cik[3][0][2];
    cnb[0][1][0] = Cik[3][1][0];
    cnb[0][1][1] = Cik[3][1][1];
    cnb[0][1][2] = Cik[3][1][2];
    cnb[0][2][0] = Cik[3][2][0];
    cnb[0][2][1] = Cik[3][2][1];
    cnb[0][2][2] = Cik[3][2][2];
    cnb[1][0][0] = cnk[8][0][0];
    cnb[1][0][1] = cnk[8][0][1];
    cnb[1][0][2] = cnk[8][0][2];
    cnb[1][1][0] = cnk[8][1][0];
    cnb[1][1][1] = cnk[8][1][1];
    cnb[1][1][2] = cnk[8][1][2];
    cnb[1][2][0] = cnk[8][2][0];
    cnb[1][2][1] = cnk[8][2][1];
    cnb[1][2][2] = cnk[8][2][2];
    cnb[2][0][0] = cnk[11][0][0];
    cnb[2][0][1] = cnk[11][0][1];
    cnb[2][0][2] = cnk[11][0][2];
    cnb[2][1][0] = cnk[11][1][0];
    cnb[2][1][1] = cnk[11][1][1];
    cnb[2][1][2] = cnk[11][1][2];
    cnb[2][2][0] = cnk[11][2][0];
    cnb[2][2][1] = cnk[11][2][1];
    cnb[2][2][2] = cnk[11][2][2];
    cnb[3][0][0] = cnk[14][0][0];
    cnb[3][0][1] = cnk[14][0][1];
    cnb[3][0][2] = cnk[14][0][2];
    cnb[3][1][0] = cnk[14][1][0];
    cnb[3][1][1] = cnk[14][1][1];
    cnb[3][1][2] = cnk[14][1][2];
    cnb[3][2][0] = cnk[14][2][0];
    cnb[3][2][1] = cnk[14][2][1];
    cnb[3][2][2] = cnk[14][2][2];
    cnb[4][0][0] = cnk[17][0][0];
    cnb[4][0][1] = cnk[17][0][1];
    cnb[4][0][2] = cnk[17][0][2];
    cnb[4][1][0] = cnk[17][1][0];
    cnb[4][1][1] = cnk[17][1][1];
    cnb[4][1][2] = cnk[17][1][2];
    cnb[4][2][0] = cnk[17][2][0];
    cnb[4][2][1] = cnk[17][2][1];
    cnb[4][2][2] = cnk[17][2][2];
    cnb[5][0][0] = cnk[20][0][0];
    cnb[5][0][1] = cnk[20][0][1];
    cnb[5][0][2] = cnk[20][0][2];
    cnb[5][1][0] = cnk[20][1][0];
    cnb[5][1][1] = cnk[20][1][1];
    cnb[5][1][2] = cnk[20][1][2];
    cnb[5][2][0] = cnk[20][2][0];
    cnb[5][2][1] = cnk[20][2][1];
    cnb[5][2][2] = cnk[20][2][2];
    cnb[6][0][0] = cnk[23][0][0];
    cnb[6][0][1] = cnk[23][0][1];
    cnb[6][0][2] = cnk[23][0][2];
    cnb[6][1][0] = cnk[23][1][0];
    cnb[6][1][1] = cnk[23][1][1];
    cnb[6][1][2] = cnk[23][1][2];
    cnb[6][2][0] = cnk[23][2][0];
    cnb[6][2][1] = cnk[23][2][1];
    cnb[6][2][2] = cnk[23][2][2];
    cnb[7][0][0] = cnk[26][0][0];
    cnb[7][0][1] = cnk[26][0][1];
    cnb[7][0][2] = cnk[26][0][2];
    cnb[7][1][0] = cnk[26][1][0];
    cnb[7][1][1] = cnk[26][1][1];
    cnb[7][1][2] = cnk[26][1][2];
    cnb[7][2][0] = cnk[26][2][0];
    cnb[7][2][1] = cnk[26][2][1];
    cnb[7][2][2] = cnk[26][2][2];
    cnb[8][0][0] = cnk[29][0][0];
    cnb[8][0][1] = cnk[29][0][1];
    cnb[8][0][2] = cnk[29][0][2];
    cnb[8][1][0] = cnk[29][1][0];
    cnb[8][1][1] = cnk[29][1][1];
    cnb[8][1][2] = cnk[29][1][2];
    cnb[8][2][0] = cnk[29][2][0];
    cnb[8][2][1] = cnk[29][2][1];
    cnb[8][2][2] = cnk[29][2][2];
    cnb[9][0][0] = cnk[32][0][0];
    cnb[9][0][1] = cnk[32][0][1];
    cnb[9][0][2] = cnk[32][0][2];
    cnb[9][1][0] = cnk[32][1][0];
    cnb[9][1][1] = cnk[32][1][1];
    cnb[9][1][2] = cnk[32][1][2];
    cnb[9][2][0] = cnk[32][2][0];
    cnb[9][2][1] = cnk[32][2][1];
    cnb[9][2][2] = cnk[32][2][2];
/*
Compute q-related auxiliary variables
*/
    rpp[0][0] = (pin[0][0]*q[0]);
    rpp[0][1] = (pin[0][1]*q[0]);
    rpp[0][2] = (pin[0][2]*q[0]);
    rpp[1][0] = (pin[1][0]*q[1]);
    rpp[1][1] = (pin[1][1]*q[1]);
    rpp[1][2] = (pin[1][2]*q[1]);
    rpp[2][0] = (pin[2][0]*q[2]);
    rpp[2][1] = (pin[2][1]*q[2]);
    rpp[2][2] = (pin[2][2]*q[2]);
    rik[9][0] = ((.0935*Cik[9][2][0])-(.07*Cik[9][1][0]));
    rik[9][1] = ((.0935*Cik[9][2][1])-(.07*Cik[9][1][1]));
    rik[9][2] = ((.0935*Cik[9][2][2])-(.07*Cik[9][1][2]));
    rik[12][0] = ((.0033*Cik[12][0][0])-(.2294*Cik[12][1][0]));
    rik[12][1] = ((.0033*Cik[12][0][1])-(.2294*Cik[12][1][1]));
    rik[12][2] = ((.0033*Cik[12][0][2])-(.2294*Cik[12][1][2]));
    rik[18][0] = ((.018078*Cik[18][2][0])+((.098032*Cik[18][0][0])-(.038*
      Cik[18][1][0])));
    rik[18][1] = ((.018078*Cik[18][2][1])+((.098032*Cik[18][0][1])-(.038*
      Cik[18][1][1])));
    rik[18][2] = ((.018078*Cik[18][2][2])+((.098032*Cik[18][0][2])-(.038*
      Cik[18][1][2])));
    rik[21][0] = -((.07*Cik[21][1][0])+(.0935*Cik[21][2][0]));
    rik[21][1] = -((.07*Cik[21][1][1])+(.0935*Cik[21][2][1]));
    rik[21][2] = -((.07*Cik[21][1][2])+(.0935*Cik[21][2][2]));
    rik[24][0] = ((.0033*Cik[24][0][0])-(.2294*Cik[24][1][0]));
    rik[24][1] = ((.0033*Cik[24][0][1])-(.2294*Cik[24][1][1]));
    rik[24][2] = ((.0033*Cik[24][0][2])-(.2294*Cik[24][1][2]));
    rik[30][0] = (((.098032*Cik[30][0][0])-(.038*Cik[30][1][0]))-(.018078*
      Cik[30][2][0]));
    rik[30][1] = (((.098032*Cik[30][0][1])-(.038*Cik[30][1][1]))-(.018078*
      Cik[30][2][1]));
    rik[30][2] = (((.098032*Cik[30][0][2])-(.038*Cik[30][1][2]))-(.018078*
      Cik[30][2][2]));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[1][0] = (rpp[0][0]+rpp[1][0]);
    rnk[1][1] = (rpp[0][1]+rpp[1][1]);
    rnk[1][2] = (rpp[0][2]+rpp[1][2]);
    rnk[2][0] = (rnk[1][0]+rpp[2][0]);
    rnk[2][1] = (rnk[1][1]+rpp[2][1]);
    rnk[2][2] = (rnk[1][2]+rpp[2][2]);
    rnk[6][0] = (rnk[2][0]+(.127*Cik[3][0][1]));
    rnk[6][1] = (rnk[2][1]+(.127*Cik[3][1][1]));
    rnk[6][2] = (rnk[2][2]+(.127*Cik[3][2][1]));
    rnk[8][0] = (rnk[6][0]+(.3202*cnk[8][0][1]));
    rnk[8][1] = (rnk[6][1]+(.3202*cnk[8][1][1]));
    rnk[8][2] = (rnk[6][2]+(.3202*cnk[8][2][1]));
    rnk[9][0] = (rnk[2][0]+((.0935*Cik[3][0][2])-(.07*Cik[3][0][1])));
    rnk[9][1] = (rnk[2][1]+((.0935*Cik[3][1][2])-(.07*Cik[3][1][1])));
    rnk[9][2] = (rnk[2][2]+((.0935*Cik[3][2][2])-(.07*Cik[3][2][1])));
    rnk[11][0] = (rnk[9][0]-((.002*cnk[11][0][0])+(.1715*cnk[11][0][1])));
    rnk[11][1] = (rnk[9][1]-((.002*cnk[11][1][0])+(.1715*cnk[11][1][1])));
    rnk[11][2] = (rnk[9][2]-((.002*cnk[11][2][0])+(.1715*cnk[11][2][1])));
    rnk[12][0] = (rnk[11][0]+((.0033*cnk[11][0][0])-(.2294*cnk[11][0][1])));
    rnk[12][1] = (rnk[11][1]+((.0033*cnk[11][1][0])-(.2294*cnk[11][1][1])));
    rnk[12][2] = (rnk[11][2]+((.0033*cnk[11][2][0])-(.2294*cnk[11][2][1])));
    rnk[14][0] = (rnk[12][0]-(.1862*cnk[14][0][1]));
    rnk[14][1] = (rnk[12][1]-(.1862*cnk[14][1][1]));
    rnk[14][2] = (rnk[12][2]-(.1862*cnk[14][2][1]));
    rnk[15][0] = (rnk[14][0]-(.2438*cnk[14][0][1]));
    rnk[15][1] = (rnk[14][1]-(.2438*cnk[14][1][1]));
    rnk[15][2] = (rnk[14][2]-(.2438*cnk[14][2][1]));
    rnk[17][0] = (rnk[15][0]+((.005539*cnk[17][0][2])+((.035902*cnk[17][0][0])-(
      .051347*cnk[17][0][1]))));
    rnk[17][1] = (rnk[15][1]+((.005539*cnk[17][1][2])+((.035902*cnk[17][1][0])-(
      .051347*cnk[17][1][1]))));
    rnk[17][2] = (rnk[15][2]+((.005539*cnk[17][2][2])+((.035902*cnk[17][2][0])-(
      .051347*cnk[17][2][1]))));
    rnk[18][0] = (rnk[17][0]+((.018078*cnk[17][0][2])+((.098032*cnk[17][0][0])-(
      .038*cnk[17][0][1]))));
    rnk[18][1] = (rnk[17][1]+((.018078*cnk[17][1][2])+((.098032*cnk[17][1][0])-(
      .038*cnk[17][1][1]))));
    rnk[18][2] = (rnk[17][2]+((.018078*cnk[17][2][2])+((.098032*cnk[17][2][0])-(
      .038*cnk[17][2][1]))));
    rnk[20][0] = (rnk[18][0]+((.005139*cnk[20][0][2])+((.0185*cnk[20][0][1])+(
      .026917*cnk[20][0][0]))));
    rnk[20][1] = (rnk[18][1]+((.005139*cnk[20][1][2])+((.0185*cnk[20][1][1])+(
      .026917*cnk[20][1][0]))));
    rnk[20][2] = (rnk[18][2]+((.005139*cnk[20][2][2])+((.0185*cnk[20][2][1])+(
      .026917*cnk[20][2][0]))));
    rnk[21][0] = (rnk[2][0]-((.07*Cik[3][0][1])+(.0935*Cik[3][0][2])));
    rnk[21][1] = (rnk[2][1]-((.07*Cik[3][1][1])+(.0935*Cik[3][1][2])));
    rnk[21][2] = (rnk[2][2]-((.07*Cik[3][2][1])+(.0935*Cik[3][2][2])));
    rnk[23][0] = (rnk[21][0]-((.002*cnk[23][0][0])+(.1715*cnk[23][0][1])));
    rnk[23][1] = (rnk[21][1]-((.002*cnk[23][1][0])+(.1715*cnk[23][1][1])));
    rnk[23][2] = (rnk[21][2]-((.002*cnk[23][2][0])+(.1715*cnk[23][2][1])));
    rnk[24][0] = (rnk[23][0]+((.0033*cnk[23][0][0])-(.2294*cnk[23][0][1])));
    rnk[24][1] = (rnk[23][1]+((.0033*cnk[23][1][0])-(.2294*cnk[23][1][1])));
    rnk[24][2] = (rnk[23][2]+((.0033*cnk[23][2][0])-(.2294*cnk[23][2][1])));
    rnk[26][0] = (rnk[24][0]-(.1862*cnk[26][0][1]));
    rnk[26][1] = (rnk[24][1]-(.1862*cnk[26][1][1]));
    rnk[26][2] = (rnk[24][2]-(.1862*cnk[26][2][1]));
    rnk[27][0] = (rnk[26][0]-(.2438*cnk[26][0][1]));
    rnk[27][1] = (rnk[26][1]-(.2438*cnk[26][1][1]));
    rnk[27][2] = (rnk[26][2]-(.2438*cnk[26][2][1]));
    rnk[29][0] = (rnk[27][0]+(((.035902*cnk[29][0][0])-(.051347*cnk[29][0][1]))-
      (.005539*cnk[29][0][2])));
    rnk[29][1] = (rnk[27][1]+(((.035902*cnk[29][1][0])-(.051347*cnk[29][1][1]))-
      (.005539*cnk[29][1][2])));
    rnk[29][2] = (rnk[27][2]+(((.035902*cnk[29][2][0])-(.051347*cnk[29][2][1]))-
      (.005539*cnk[29][2][2])));
    rnk[30][0] = (rnk[29][0]+(((.098032*cnk[29][0][0])-(.038*cnk[29][0][1]))-(
      .018078*cnk[29][0][2])));
    rnk[30][1] = (rnk[29][1]+(((.098032*cnk[29][1][0])-(.038*cnk[29][1][1]))-(
      .018078*cnk[29][1][2])));
    rnk[30][2] = (rnk[29][2]+(((.098032*cnk[29][2][0])-(.038*cnk[29][2][1]))-(
      .018078*cnk[29][2][2])));
    rnk[32][0] = (rnk[30][0]+(((.0185*cnk[32][0][1])+(.026917*cnk[32][0][0]))-(
      .005139*cnk[32][0][2])));
    rnk[32][1] = (rnk[30][1]+(((.0185*cnk[32][1][1])+(.026917*cnk[32][1][0]))-(
      .005139*cnk[32][1][2])));
    rnk[32][2] = (rnk[30][2]+(((.0185*cnk[32][2][1])+(.026917*cnk[32][2][0]))-(
      .005139*cnk[32][2][2])));
    rnb[0][0] = rnk[2][0];
    rnb[0][1] = rnk[2][1];
    rnb[0][2] = rnk[2][2];
    rnb[1][0] = rnk[8][0];
    rnb[1][1] = rnk[8][1];
    rnb[1][2] = rnk[8][2];
    rnb[2][0] = rnk[11][0];
    rnb[2][1] = rnk[11][1];
    rnb[2][2] = rnk[11][2];
    rnb[3][0] = rnk[14][0];
    rnb[3][1] = rnk[14][1];
    rnb[3][2] = rnk[14][2];
    rnb[4][0] = rnk[17][0];
    rnb[4][1] = rnk[17][1];
    rnb[4][2] = rnk[17][2];
    rnb[5][0] = rnk[20][0];
    rnb[5][1] = rnk[20][1];
    rnb[5][2] = rnk[20][2];
    rnb[6][0] = rnk[23][0];
    rnb[6][1] = rnk[23][1];
    rnb[6][2] = rnk[23][2];
    rnb[7][0] = rnk[26][0];
    rnb[7][1] = rnk[26][1];
    rnb[7][2] = rnk[26][2];
    rnb[8][0] = rnk[29][0];
    rnb[8][1] = rnk[29][1];
    rnb[8][2] = rnk[29][2];
    rnb[9][0] = rnk[32][0];
    rnb[9][1] = rnk[32][1];
    rnb[9][2] = rnk[32][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = (.0140834652625414*((.205126*rnk[32][0])+((1.2*rnk[29][0])+((3.51*
      rnk[26][0])+((8.806*rnk[23][0])+((.205126*rnk[20][0])+((1.2*rnk[17][0])+((
      3.51*rnk[14][0])+((8.806*rnk[11][0])+((11.15*rnk[2][0])+(32.413*rnk[8][0])
      ))))))))));
    com[1] = (.0140834652625414*((.205126*rnk[32][1])+((1.2*rnk[29][1])+((3.51*
      rnk[26][1])+((8.806*rnk[23][1])+((.205126*rnk[20][1])+((1.2*rnk[17][1])+((
      3.51*rnk[14][1])+((8.806*rnk[11][1])+((11.15*rnk[2][1])+(32.413*rnk[8][1])
      ))))))))));
    com[2] = (.0140834652625414*((.205126*rnk[32][2])+((1.2*rnk[29][2])+((3.51*
      rnk[26][2])+((8.806*rnk[23][2])+((.205126*rnk[20][2])+((1.2*rnk[17][2])+((
      3.51*rnk[14][2])+((8.806*rnk[11][2])+((11.15*rnk[2][2])+(32.413*rnk[8][2])
      ))))))))));
/*
Compute constraint position errors
*/
    skipqs: ;
/*
Check for locked gimbal tree joint
*/
    if ((fabs((fabs(((((cnk[6][2][2]*pin[6][2])+((cnk[6][2][0]*pin[6][0])+(
      cnk[6][2][1]*pin[6][1])))*((cnk[8][2][2]*pin[8][2])+((cnk[8][2][0]*
      pin[8][0])+(cnk[8][2][1]*pin[8][1]))))+((((cnk[6][0][2]*pin[6][2])+((
      cnk[6][0][0]*pin[6][0])+(cnk[6][0][1]*pin[6][1])))*((cnk[8][0][2]*
      pin[8][2])+((cnk[8][0][0]*pin[8][0])+(cnk[8][0][1]*pin[8][1]))))+(((
      cnk[6][1][2]*pin[6][2])+((cnk[6][1][0]*pin[6][0])+(cnk[6][1][1]*pin[6][1])
      ))*((cnk[8][1][2]*pin[8][2])+((cnk[8][1][0]*pin[8][0])+(cnk[8][1][1]*
      pin[8][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[9][2][2]*pin[9][2])+((cnk[9][2][0]*pin[9][0])+(
      cnk[9][2][1]*pin[9][1])))*((cnk[11][2][2]*pin[11][2])+((cnk[11][2][0]*
      pin[11][0])+(cnk[11][2][1]*pin[11][1]))))+((((cnk[9][0][2]*pin[9][2])+((
      cnk[9][0][0]*pin[9][0])+(cnk[9][0][1]*pin[9][1])))*((cnk[11][0][2]*
      pin[11][2])+((cnk[11][0][0]*pin[11][0])+(cnk[11][0][1]*pin[11][1]))))+(((
      cnk[9][1][2]*pin[9][2])+((cnk[9][1][0]*pin[9][0])+(cnk[9][1][1]*pin[9][1])
      ))*((cnk[11][1][2]*pin[11][2])+((cnk[11][1][0]*pin[11][0])+(cnk[11][1][1]*
      pin[11][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[12][2][2]*pin[12][2])+((cnk[12][2][0]*pin[12][0])+(
      cnk[12][2][1]*pin[12][1])))*((cnk[14][2][2]*pin[14][2])+((cnk[14][2][0]*
      pin[14][0])+(cnk[14][2][1]*pin[14][1]))))+((((cnk[12][0][2]*pin[12][2])+((
      cnk[12][0][0]*pin[12][0])+(cnk[12][0][1]*pin[12][1])))*((cnk[14][0][2]*
      pin[14][2])+((cnk[14][0][0]*pin[14][0])+(cnk[14][0][1]*pin[14][1]))))+(((
      cnk[12][1][2]*pin[12][2])+((cnk[12][1][0]*pin[12][0])+(cnk[12][1][1]*
      pin[12][1])))*((cnk[14][1][2]*pin[14][2])+((cnk[14][1][0]*pin[14][0])+(
      cnk[14][1][1]*pin[14][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[15][2][2]*pin[15][2])+((cnk[15][2][0]*pin[15][0])+(
      cnk[15][2][1]*pin[15][1])))*((cnk[17][2][2]*pin[17][2])+((cnk[17][2][0]*
      pin[17][0])+(cnk[17][2][1]*pin[17][1]))))+((((cnk[15][0][2]*pin[15][2])+((
      cnk[15][0][0]*pin[15][0])+(cnk[15][0][1]*pin[15][1])))*((cnk[17][0][2]*
      pin[17][2])+((cnk[17][0][0]*pin[17][0])+(cnk[17][0][1]*pin[17][1]))))+(((
      cnk[15][1][2]*pin[15][2])+((cnk[15][1][0]*pin[15][0])+(cnk[15][1][1]*
      pin[15][1])))*((cnk[17][1][2]*pin[17][2])+((cnk[17][1][0]*pin[17][0])+(
      cnk[17][1][1]*pin[17][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[18][2][2]*pin[18][2])+((cnk[18][2][0]*pin[18][0])+(
      cnk[18][2][1]*pin[18][1])))*((cnk[20][2][2]*pin[20][2])+((cnk[20][2][0]*
      pin[20][0])+(cnk[20][2][1]*pin[20][1]))))+((((cnk[18][0][2]*pin[18][2])+((
      cnk[18][0][0]*pin[18][0])+(cnk[18][0][1]*pin[18][1])))*((cnk[20][0][2]*
      pin[20][2])+((cnk[20][0][0]*pin[20][0])+(cnk[20][0][1]*pin[20][1]))))+(((
      cnk[18][1][2]*pin[18][2])+((cnk[18][1][0]*pin[18][0])+(cnk[18][1][1]*
      pin[18][1])))*((cnk[20][1][2]*pin[20][2])+((cnk[20][1][0]*pin[20][0])+(
      cnk[20][1][1]*pin[20][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[21][2][2]*pin[21][2])+((cnk[21][2][0]*pin[21][0])+(
      cnk[21][2][1]*pin[21][1])))*((cnk[23][2][2]*pin[23][2])+((cnk[23][2][0]*
      pin[23][0])+(cnk[23][2][1]*pin[23][1]))))+((((cnk[21][0][2]*pin[21][2])+((
      cnk[21][0][0]*pin[21][0])+(cnk[21][0][1]*pin[21][1])))*((cnk[23][0][2]*
      pin[23][2])+((cnk[23][0][0]*pin[23][0])+(cnk[23][0][1]*pin[23][1]))))+(((
      cnk[21][1][2]*pin[21][2])+((cnk[21][1][0]*pin[21][0])+(cnk[21][1][1]*
      pin[21][1])))*((cnk[23][1][2]*pin[23][2])+((cnk[23][1][0]*pin[23][0])+(
      cnk[23][1][1]*pin[23][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[24][2][2]*pin[24][2])+((cnk[24][2][0]*pin[24][0])+(
      cnk[24][2][1]*pin[24][1])))*((cnk[26][2][2]*pin[26][2])+((cnk[26][2][0]*
      pin[26][0])+(cnk[26][2][1]*pin[26][1]))))+((((cnk[24][0][2]*pin[24][2])+((
      cnk[24][0][0]*pin[24][0])+(cnk[24][0][1]*pin[24][1])))*((cnk[26][0][2]*
      pin[26][2])+((cnk[26][0][0]*pin[26][0])+(cnk[26][0][1]*pin[26][1]))))+(((
      cnk[24][1][2]*pin[24][2])+((cnk[24][1][0]*pin[24][0])+(cnk[24][1][1]*
      pin[24][1])))*((cnk[26][1][2]*pin[26][2])+((cnk[26][1][0]*pin[26][0])+(
      cnk[26][1][1]*pin[26][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[27][2][2]*pin[27][2])+((cnk[27][2][0]*pin[27][0])+(
      cnk[27][2][1]*pin[27][1])))*((cnk[29][2][2]*pin[29][2])+((cnk[29][2][0]*
      pin[29][0])+(cnk[29][2][1]*pin[29][1]))))+((((cnk[27][0][2]*pin[27][2])+((
      cnk[27][0][0]*pin[27][0])+(cnk[27][0][1]*pin[27][1])))*((cnk[29][0][2]*
      pin[29][2])+((cnk[29][0][0]*pin[29][0])+(cnk[29][0][1]*pin[29][1]))))+(((
      cnk[27][1][2]*pin[27][2])+((cnk[27][1][0]*pin[27][0])+(cnk[27][1][1]*
      pin[27][1])))*((cnk[29][1][2]*pin[29][2])+((cnk[29][1][0]*pin[29][0])+(
      cnk[29][1][1]*pin[29][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[30][2][2]*pin[30][2])+((cnk[30][2][0]*pin[30][0])+(
      cnk[30][2][1]*pin[30][1])))*((cnk[32][2][2]*pin[32][2])+((cnk[32][2][0]*
      pin[32][0])+(cnk[32][2][1]*pin[32][1]))))+((((cnk[30][0][2]*pin[30][2])+((
      cnk[30][0][0]*pin[30][0])+(cnk[30][0][1]*pin[30][1])))*((cnk[32][0][2]*
      pin[32][2])+((cnk[32][0][0]*pin[32][0])+(cnk[32][0][1]*pin[32][1]))))+(((
      cnk[30][1][2]*pin[30][2])+((cnk[30][1][0]*pin[30][0])+(cnk[30][1][1]*
      pin[30][1])))*((cnk[32][1][2]*pin[32][2])+((cnk[32][1][0]*pin[32][0])+(
      cnk[32][1][1]*pin[32][1])))))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 33; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
    Wik[6][0] = (pin[6][0]*u[6]);
    Wik[6][1] = (pin[6][1]*u[6]);
    Wik[6][2] = (pin[6][2]*u[6]);
    Wik[7][0] = (pin[7][0]*u[7]);
    Wik[7][1] = (pin[7][1]*u[7]);
    Wik[7][2] = (pin[7][2]*u[7]);
    Wik[8][0] = (pin[8][0]*u[8]);
    Wik[8][1] = (pin[8][1]*u[8]);
    Wik[8][2] = (pin[8][2]*u[8]);
    Wik[9][0] = (pin[9][0]*u[9]);
    Wik[9][1] = (pin[9][1]*u[9]);
    Wik[9][2] = (pin[9][2]*u[9]);
    Wik[10][0] = (pin[10][0]*u[10]);
    Wik[10][1] = (pin[10][1]*u[10]);
    Wik[10][2] = (pin[10][2]*u[10]);
    Wik[11][0] = (pin[11][0]*u[11]);
    Wik[11][1] = (pin[11][1]*u[11]);
    Wik[11][2] = (pin[11][2]*u[11]);
    Wik[12][0] = (pin[12][0]*u[12]);
    Wik[12][1] = (pin[12][1]*u[12]);
    Wik[12][2] = (pin[12][2]*u[12]);
    Wik[13][0] = (pin[13][0]*u[13]);
    Wik[13][1] = (pin[13][1]*u[13]);
    Wik[13][2] = (pin[13][2]*u[13]);
    Wik[14][0] = (pin[14][0]*u[14]);
    Wik[14][1] = (pin[14][1]*u[14]);
    Wik[14][2] = (pin[14][2]*u[14]);
    Wik[15][0] = (pin[15][0]*u[15]);
    Wik[15][1] = (pin[15][1]*u[15]);
    Wik[15][2] = (pin[15][2]*u[15]);
    Wik[16][0] = (pin[16][0]*u[16]);
    Wik[16][1] = (pin[16][1]*u[16]);
    Wik[16][2] = (pin[16][2]*u[16]);
    Wik[17][0] = (pin[17][0]*u[17]);
    Wik[17][1] = (pin[17][1]*u[17]);
    Wik[17][2] = (pin[17][2]*u[17]);
    Wik[18][0] = (pin[18][0]*u[18]);
    Wik[18][1] = (pin[18][1]*u[18]);
    Wik[18][2] = (pin[18][2]*u[18]);
    Wik[19][0] = (pin[19][0]*u[19]);
    Wik[19][1] = (pin[19][1]*u[19]);
    Wik[19][2] = (pin[19][2]*u[19]);
    Wik[20][0] = (pin[20][0]*u[20]);
    Wik[20][1] = (pin[20][1]*u[20]);
    Wik[20][2] = (pin[20][2]*u[20]);
    Wik[21][0] = (pin[21][0]*u[21]);
    Wik[21][1] = (pin[21][1]*u[21]);
    Wik[21][2] = (pin[21][2]*u[21]);
    Wik[22][0] = (pin[22][0]*u[22]);
    Wik[22][1] = (pin[22][1]*u[22]);
    Wik[22][2] = (pin[22][2]*u[22]);
    Wik[23][0] = (pin[23][0]*u[23]);
    Wik[23][1] = (pin[23][1]*u[23]);
    Wik[23][2] = (pin[23][2]*u[23]);
    Wik[24][0] = (pin[24][0]*u[24]);
    Wik[24][1] = (pin[24][1]*u[24]);
    Wik[24][2] = (pin[24][2]*u[24]);
    Wik[25][0] = (pin[25][0]*u[25]);
    Wik[25][1] = (pin[25][1]*u[25]);
    Wik[25][2] = (pin[25][2]*u[25]);
    Wik[26][0] = (pin[26][0]*u[26]);
    Wik[26][1] = (pin[26][1]*u[26]);
    Wik[26][2] = (pin[26][2]*u[26]);
    Wik[27][0] = (pin[27][0]*u[27]);
    Wik[27][1] = (pin[27][1]*u[27]);
    Wik[27][2] = (pin[27][2]*u[27]);
    Wik[28][0] = (pin[28][0]*u[28]);
    Wik[28][1] = (pin[28][1]*u[28]);
    Wik[28][2] = (pin[28][2]*u[28]);
    Wik[29][0] = (pin[29][0]*u[29]);
    Wik[29][1] = (pin[29][1]*u[29]);
    Wik[29][2] = (pin[29][2]*u[29]);
    Wik[30][0] = (pin[30][0]*u[30]);
    Wik[30][1] = (pin[30][1]*u[30]);
    Wik[30][2] = (pin[30][2]*u[30]);
    Wik[31][0] = (pin[31][0]*u[31]);
    Wik[31][1] = (pin[31][1]*u[31]);
    Wik[31][2] = (pin[31][2]*u[31]);
    Wik[32][0] = (pin[32][0]*u[32]);
    Wik[32][1] = (pin[32][1]*u[32]);
    Wik[32][2] = (pin[32][2]*u[32]);
    Vik[0][0] = (pin[0][0]*u[0]);
    Vik[0][1] = (pin[0][1]*u[0]);
    Vik[0][2] = (pin[0][2]*u[0]);
    Vik[1][0] = (pin[1][0]*u[1]);
    Vik[1][1] = (pin[1][1]*u[1]);
    Vik[1][2] = (pin[1][2]*u[1]);
    Vik[2][0] = (pin[2][0]*u[2]);
    Vik[2][1] = (pin[2][1]*u[2]);
    Vik[2][2] = (pin[2][2]*u[2]);
/*
Compute wk & wb (angular velocities)
*/
    wk[6][0] = (Wik[6][0]+((Cik[6][2][0]*u[5])+((Cik[6][0][0]*u[3])+(
      Cik[6][1][0]*u[4]))));
    wk[6][1] = (Wik[6][1]+((Cik[6][2][1]*u[5])+((Cik[6][0][1]*u[3])+(
      Cik[6][1][1]*u[4]))));
    wk[6][2] = (Wik[6][2]+((Cik[6][2][2]*u[5])+((Cik[6][0][2]*u[3])+(
      Cik[6][1][2]*u[4]))));
    wk[7][0] = (Wik[7][0]+((Cik[7][2][0]*wk[6][2])+((Cik[7][0][0]*wk[6][0])+(
      Cik[7][1][0]*wk[6][1]))));
    wk[7][1] = (Wik[7][1]+((Cik[7][2][1]*wk[6][2])+((Cik[7][0][1]*wk[6][0])+(
      Cik[7][1][1]*wk[6][1]))));
    wk[7][2] = (Wik[7][2]+((Cik[7][2][2]*wk[6][2])+((Cik[7][0][2]*wk[6][0])+(
      Cik[7][1][2]*wk[6][1]))));
    wk[8][0] = (Wik[8][0]+((Cik[8][2][0]*wk[7][2])+((Cik[8][0][0]*wk[7][0])+(
      Cik[8][1][0]*wk[7][1]))));
    wk[8][1] = (Wik[8][1]+((Cik[8][2][1]*wk[7][2])+((Cik[8][0][1]*wk[7][0])+(
      Cik[8][1][1]*wk[7][1]))));
    wk[8][2] = (Wik[8][2]+((Cik[8][2][2]*wk[7][2])+((Cik[8][0][2]*wk[7][0])+(
      Cik[8][1][2]*wk[7][1]))));
    wk[9][0] = (Wik[9][0]+((Cik[9][2][0]*u[5])+((Cik[9][0][0]*u[3])+(
      Cik[9][1][0]*u[4]))));
    wk[9][1] = (Wik[9][1]+((Cik[9][2][1]*u[5])+((Cik[9][0][1]*u[3])+(
      Cik[9][1][1]*u[4]))));
    wk[9][2] = (Wik[9][2]+((Cik[9][2][2]*u[5])+((Cik[9][0][2]*u[3])+(
      Cik[9][1][2]*u[4]))));
    wk[10][0] = (Wik[10][0]+((Cik[10][2][0]*wk[9][2])+((Cik[10][0][0]*wk[9][0])+
      (Cik[10][1][0]*wk[9][1]))));
    wk[10][1] = (Wik[10][1]+((Cik[10][2][1]*wk[9][2])+((Cik[10][0][1]*wk[9][0])+
      (Cik[10][1][1]*wk[9][1]))));
    wk[10][2] = (Wik[10][2]+((Cik[10][2][2]*wk[9][2])+((Cik[10][0][2]*wk[9][0])+
      (Cik[10][1][2]*wk[9][1]))));
    wk[11][0] = (Wik[11][0]+((Cik[11][2][0]*wk[10][2])+((Cik[11][0][0]*wk[10][0]
      )+(Cik[11][1][0]*wk[10][1]))));
    wk[11][1] = (Wik[11][1]+((Cik[11][2][1]*wk[10][2])+((Cik[11][0][1]*wk[10][0]
      )+(Cik[11][1][1]*wk[10][1]))));
    wk[11][2] = (Wik[11][2]+((Cik[11][2][2]*wk[10][2])+((Cik[11][0][2]*wk[10][0]
      )+(Cik[11][1][2]*wk[10][1]))));
    wk[12][0] = (Wik[12][0]+((Cik[12][2][0]*wk[11][2])+((Cik[12][0][0]*wk[11][0]
      )+(Cik[12][1][0]*wk[11][1]))));
    wk[12][1] = (Wik[12][1]+((Cik[12][2][1]*wk[11][2])+((Cik[12][0][1]*wk[11][0]
      )+(Cik[12][1][1]*wk[11][1]))));
    wk[12][2] = (Wik[12][2]+((Cik[12][2][2]*wk[11][2])+((Cik[12][0][2]*wk[11][0]
      )+(Cik[12][1][2]*wk[11][1]))));
    wk[13][0] = (Wik[13][0]+((Cik[13][2][0]*wk[12][2])+((Cik[13][0][0]*wk[12][0]
      )+(Cik[13][1][0]*wk[12][1]))));
    wk[13][1] = (Wik[13][1]+((Cik[13][2][1]*wk[12][2])+((Cik[13][0][1]*wk[12][0]
      )+(Cik[13][1][1]*wk[12][1]))));
    wk[13][2] = (Wik[13][2]+((Cik[13][2][2]*wk[12][2])+((Cik[13][0][2]*wk[12][0]
      )+(Cik[13][1][2]*wk[12][1]))));
    wk[14][0] = (Wik[14][0]+((Cik[14][2][0]*wk[13][2])+((Cik[14][0][0]*wk[13][0]
      )+(Cik[14][1][0]*wk[13][1]))));
    wk[14][1] = (Wik[14][1]+((Cik[14][2][1]*wk[13][2])+((Cik[14][0][1]*wk[13][0]
      )+(Cik[14][1][1]*wk[13][1]))));
    wk[14][2] = (Wik[14][2]+((Cik[14][2][2]*wk[13][2])+((Cik[14][0][2]*wk[13][0]
      )+(Cik[14][1][2]*wk[13][1]))));
    wk[15][0] = (Wik[15][0]+((Cik[15][2][0]*wk[14][2])+((Cik[15][0][0]*wk[14][0]
      )+(Cik[15][1][0]*wk[14][1]))));
    wk[15][1] = (Wik[15][1]+((Cik[15][2][1]*wk[14][2])+((Cik[15][0][1]*wk[14][0]
      )+(Cik[15][1][1]*wk[14][1]))));
    wk[15][2] = (Wik[15][2]+((Cik[15][2][2]*wk[14][2])+((Cik[15][0][2]*wk[14][0]
      )+(Cik[15][1][2]*wk[14][1]))));
    wk[16][0] = (Wik[16][0]+((Cik[16][2][0]*wk[15][2])+((Cik[16][0][0]*wk[15][0]
      )+(Cik[16][1][0]*wk[15][1]))));
    wk[16][1] = (Wik[16][1]+((Cik[16][2][1]*wk[15][2])+((Cik[16][0][1]*wk[15][0]
      )+(Cik[16][1][1]*wk[15][1]))));
    wk[16][2] = (Wik[16][2]+((Cik[16][2][2]*wk[15][2])+((Cik[16][0][2]*wk[15][0]
      )+(Cik[16][1][2]*wk[15][1]))));
    wk[17][0] = (Wik[17][0]+((Cik[17][2][0]*wk[16][2])+((Cik[17][0][0]*wk[16][0]
      )+(Cik[17][1][0]*wk[16][1]))));
    wk[17][1] = (Wik[17][1]+((Cik[17][2][1]*wk[16][2])+((Cik[17][0][1]*wk[16][0]
      )+(Cik[17][1][1]*wk[16][1]))));
    wk[17][2] = (Wik[17][2]+((Cik[17][2][2]*wk[16][2])+((Cik[17][0][2]*wk[16][0]
      )+(Cik[17][1][2]*wk[16][1]))));
    wk[18][0] = (Wik[18][0]+((Cik[18][2][0]*wk[17][2])+((Cik[18][0][0]*wk[17][0]
      )+(Cik[18][1][0]*wk[17][1]))));
    wk[18][1] = (Wik[18][1]+((Cik[18][2][1]*wk[17][2])+((Cik[18][0][1]*wk[17][0]
      )+(Cik[18][1][1]*wk[17][1]))));
    wk[18][2] = (Wik[18][2]+((Cik[18][2][2]*wk[17][2])+((Cik[18][0][2]*wk[17][0]
      )+(Cik[18][1][2]*wk[17][1]))));
    wk[19][0] = (Wik[19][0]+((Cik[19][2][0]*wk[18][2])+((Cik[19][0][0]*wk[18][0]
      )+(Cik[19][1][0]*wk[18][1]))));
    wk[19][1] = (Wik[19][1]+((Cik[19][2][1]*wk[18][2])+((Cik[19][0][1]*wk[18][0]
      )+(Cik[19][1][1]*wk[18][1]))));
    wk[19][2] = (Wik[19][2]+((Cik[19][2][2]*wk[18][2])+((Cik[19][0][2]*wk[18][0]
      )+(Cik[19][1][2]*wk[18][1]))));
    wk[20][0] = (Wik[20][0]+((Cik[20][2][0]*wk[19][2])+((Cik[20][0][0]*wk[19][0]
      )+(Cik[20][1][0]*wk[19][1]))));
    wk[20][1] = (Wik[20][1]+((Cik[20][2][1]*wk[19][2])+((Cik[20][0][1]*wk[19][0]
      )+(Cik[20][1][1]*wk[19][1]))));
    wk[20][2] = (Wik[20][2]+((Cik[20][2][2]*wk[19][2])+((Cik[20][0][2]*wk[19][0]
      )+(Cik[20][1][2]*wk[19][1]))));
    wk[21][0] = (Wik[21][0]+((Cik[21][2][0]*u[5])+((Cik[21][0][0]*u[3])+(
      Cik[21][1][0]*u[4]))));
    wk[21][1] = (Wik[21][1]+((Cik[21][2][1]*u[5])+((Cik[21][0][1]*u[3])+(
      Cik[21][1][1]*u[4]))));
    wk[21][2] = (Wik[21][2]+((Cik[21][2][2]*u[5])+((Cik[21][0][2]*u[3])+(
      Cik[21][1][2]*u[4]))));
    wk[22][0] = (Wik[22][0]+((Cik[22][2][0]*wk[21][2])+((Cik[22][0][0]*wk[21][0]
      )+(Cik[22][1][0]*wk[21][1]))));
    wk[22][1] = (Wik[22][1]+((Cik[22][2][1]*wk[21][2])+((Cik[22][0][1]*wk[21][0]
      )+(Cik[22][1][1]*wk[21][1]))));
    wk[22][2] = (Wik[22][2]+((Cik[22][2][2]*wk[21][2])+((Cik[22][0][2]*wk[21][0]
      )+(Cik[22][1][2]*wk[21][1]))));
    wk[23][0] = (Wik[23][0]+((Cik[23][2][0]*wk[22][2])+((Cik[23][0][0]*wk[22][0]
      )+(Cik[23][1][0]*wk[22][1]))));
    wk[23][1] = (Wik[23][1]+((Cik[23][2][1]*wk[22][2])+((Cik[23][0][1]*wk[22][0]
      )+(Cik[23][1][1]*wk[22][1]))));
    wk[23][2] = (Wik[23][2]+((Cik[23][2][2]*wk[22][2])+((Cik[23][0][2]*wk[22][0]
      )+(Cik[23][1][2]*wk[22][1]))));
    wk[24][0] = (Wik[24][0]+((Cik[24][2][0]*wk[23][2])+((Cik[24][0][0]*wk[23][0]
      )+(Cik[24][1][0]*wk[23][1]))));
    wk[24][1] = (Wik[24][1]+((Cik[24][2][1]*wk[23][2])+((Cik[24][0][1]*wk[23][0]
      )+(Cik[24][1][1]*wk[23][1]))));
    wk[24][2] = (Wik[24][2]+((Cik[24][2][2]*wk[23][2])+((Cik[24][0][2]*wk[23][0]
      )+(Cik[24][1][2]*wk[23][1]))));
    wk[25][0] = (Wik[25][0]+((Cik[25][2][0]*wk[24][2])+((Cik[25][0][0]*wk[24][0]
      )+(Cik[25][1][0]*wk[24][1]))));
    wk[25][1] = (Wik[25][1]+((Cik[25][2][1]*wk[24][2])+((Cik[25][0][1]*wk[24][0]
      )+(Cik[25][1][1]*wk[24][1]))));
    wk[25][2] = (Wik[25][2]+((Cik[25][2][2]*wk[24][2])+((Cik[25][0][2]*wk[24][0]
      )+(Cik[25][1][2]*wk[24][1]))));
    wk[26][0] = (Wik[26][0]+((Cik[26][2][0]*wk[25][2])+((Cik[26][0][0]*wk[25][0]
      )+(Cik[26][1][0]*wk[25][1]))));
    wk[26][1] = (Wik[26][1]+((Cik[26][2][1]*wk[25][2])+((Cik[26][0][1]*wk[25][0]
      )+(Cik[26][1][1]*wk[25][1]))));
    wk[26][2] = (Wik[26][2]+((Cik[26][2][2]*wk[25][2])+((Cik[26][0][2]*wk[25][0]
      )+(Cik[26][1][2]*wk[25][1]))));
    wk[27][0] = (Wik[27][0]+((Cik[27][2][0]*wk[26][2])+((Cik[27][0][0]*wk[26][0]
      )+(Cik[27][1][0]*wk[26][1]))));
    wk[27][1] = (Wik[27][1]+((Cik[27][2][1]*wk[26][2])+((Cik[27][0][1]*wk[26][0]
      )+(Cik[27][1][1]*wk[26][1]))));
    wk[27][2] = (Wik[27][2]+((Cik[27][2][2]*wk[26][2])+((Cik[27][0][2]*wk[26][0]
      )+(Cik[27][1][2]*wk[26][1]))));
    wk[28][0] = (Wik[28][0]+((Cik[28][2][0]*wk[27][2])+((Cik[28][0][0]*wk[27][0]
      )+(Cik[28][1][0]*wk[27][1]))));
    wk[28][1] = (Wik[28][1]+((Cik[28][2][1]*wk[27][2])+((Cik[28][0][1]*wk[27][0]
      )+(Cik[28][1][1]*wk[27][1]))));
    wk[28][2] = (Wik[28][2]+((Cik[28][2][2]*wk[27][2])+((Cik[28][0][2]*wk[27][0]
      )+(Cik[28][1][2]*wk[27][1]))));
    wk[29][0] = (Wik[29][0]+((Cik[29][2][0]*wk[28][2])+((Cik[29][0][0]*wk[28][0]
      )+(Cik[29][1][0]*wk[28][1]))));
    wk[29][1] = (Wik[29][1]+((Cik[29][2][1]*wk[28][2])+((Cik[29][0][1]*wk[28][0]
      )+(Cik[29][1][1]*wk[28][1]))));
    wk[29][2] = (Wik[29][2]+((Cik[29][2][2]*wk[28][2])+((Cik[29][0][2]*wk[28][0]
      )+(Cik[29][1][2]*wk[28][1]))));
    wk[30][0] = (Wik[30][0]+((Cik[30][2][0]*wk[29][2])+((Cik[30][0][0]*wk[29][0]
      )+(Cik[30][1][0]*wk[29][1]))));
    wk[30][1] = (Wik[30][1]+((Cik[30][2][1]*wk[29][2])+((Cik[30][0][1]*wk[29][0]
      )+(Cik[30][1][1]*wk[29][1]))));
    wk[30][2] = (Wik[30][2]+((Cik[30][2][2]*wk[29][2])+((Cik[30][0][2]*wk[29][0]
      )+(Cik[30][1][2]*wk[29][1]))));
    wk[31][0] = (Wik[31][0]+((Cik[31][2][0]*wk[30][2])+((Cik[31][0][0]*wk[30][0]
      )+(Cik[31][1][0]*wk[30][1]))));
    wk[31][1] = (Wik[31][1]+((Cik[31][2][1]*wk[30][2])+((Cik[31][0][1]*wk[30][0]
      )+(Cik[31][1][1]*wk[30][1]))));
    wk[31][2] = (Wik[31][2]+((Cik[31][2][2]*wk[30][2])+((Cik[31][0][2]*wk[30][0]
      )+(Cik[31][1][2]*wk[30][1]))));
    wk[32][0] = (Wik[32][0]+((Cik[32][2][0]*wk[31][2])+((Cik[32][0][0]*wk[31][0]
      )+(Cik[32][1][0]*wk[31][1]))));
    wk[32][1] = (Wik[32][1]+((Cik[32][2][1]*wk[31][2])+((Cik[32][0][1]*wk[31][0]
      )+(Cik[32][1][1]*wk[31][1]))));
    wk[32][2] = (Wik[32][2]+((Cik[32][2][2]*wk[31][2])+((Cik[32][0][2]*wk[31][0]
      )+(Cik[32][1][2]*wk[31][1]))));
    wb[0][0] = u[3];
    wb[0][1] = u[4];
    wb[0][2] = u[5];
    wb[1][0] = wk[8][0];
    wb[1][1] = wk[8][1];
    wb[1][2] = wk[8][2];
    wb[2][0] = wk[11][0];
    wb[2][1] = wk[11][1];
    wb[2][2] = wk[11][2];
    wb[3][0] = wk[14][0];
    wb[3][1] = wk[14][1];
    wb[3][2] = wk[14][2];
    wb[4][0] = wk[17][0];
    wb[4][1] = wk[17][1];
    wb[4][2] = wk[17][2];
    wb[5][0] = wk[20][0];
    wb[5][1] = wk[20][1];
    wb[5][2] = wk[20][2];
    wb[6][0] = wk[23][0];
    wb[6][1] = wk[23][1];
    wb[6][2] = wk[23][2];
    wb[7][0] = wk[26][0];
    wb[7][1] = wk[26][1];
    wb[7][2] = wk[26][2];
    wb[8][0] = wk[29][0];
    wb[8][1] = wk[29][1];
    wb[8][2] = wk[29][2];
    wb[9][0] = wk[32][0];
    wb[9][1] = wk[32][1];
    wb[9][2] = wk[32][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[9][0] = ((.07*u[5])+(.0935*u[4]));
    Wirk[12][2] = -((.0033*wk[11][1])+(.2294*wk[11][0]));
    Wirk[18][0] = ((.018078*wk[17][1])+(.038*wk[17][2]));
    Wirk[18][1] = ((.098032*wk[17][2])-(.018078*wk[17][0]));
    Wirk[18][2] = -((.038*wk[17][0])+(.098032*wk[17][1]));
    Wirk[21][0] = ((.07*u[5])-(.0935*u[4]));
    Wirk[24][2] = -((.0033*wk[23][1])+(.2294*wk[23][0]));
    Wirk[30][0] = ((.038*wk[29][2])-(.018078*wk[29][1]));
    Wirk[30][1] = ((.018078*wk[29][0])+(.098032*wk[29][2]));
    Wirk[30][2] = -((.038*wk[29][0])+(.098032*wk[29][1]));
    Wkrpk[11][2] = ((.002*wk[11][1])-(.1715*wk[11][0]));
    Wkrpk[17][0] = ((.005539*wk[17][1])+(.051347*wk[17][2]));
    Wkrpk[17][1] = ((.035902*wk[17][2])-(.005539*wk[17][0]));
    Wkrpk[17][2] = -((.035902*wk[17][1])+(.051347*wk[17][0]));
    Wkrpk[20][0] = ((.005139*wk[20][1])-(.0185*wk[20][2]));
    Wkrpk[20][1] = ((.026917*wk[20][2])-(.005139*wk[20][0]));
    Wkrpk[20][2] = ((.0185*wk[20][0])-(.026917*wk[20][1]));
    Wkrpk[23][2] = ((.002*wk[23][1])-(.1715*wk[23][0]));
    Wkrpk[29][0] = ((.051347*wk[29][2])-(.005539*wk[29][1]));
    Wkrpk[29][1] = ((.005539*wk[29][0])+(.035902*wk[29][2]));
    Wkrpk[29][2] = -((.035902*wk[29][1])+(.051347*wk[29][0]));
    Wkrpk[32][0] = -((.005139*wk[32][1])+(.0185*wk[32][2]));
    Wkrpk[32][1] = ((.005139*wk[32][0])+(.026917*wk[32][2]));
    Wkrpk[32][2] = ((.0185*wk[32][0])-(.026917*wk[32][1]));
    WkIkWk[5][0] = -(.0277*(u[4]*u[5]));
    WkIkWk[5][1] = (.0425*(u[3]*u[5]));
    WkIkWk[5][2] = -(.0148*(u[3]*u[4]));
    WkIkWk[8][0] = (.6399*(wk[8][1]*wk[8][2]));
    WkIkWk[8][1] = (.0407999999999999*(wk[8][0]*wk[8][2]));
    WkIkWk[8][2] = -(.6807*(wk[8][0]*wk[8][1]));
    WkIkWk[11][0] = (.1005*(wk[11][1]*wk[11][2]));
    WkIkWk[11][1] = -(.00690000000000002*(wk[11][0]*wk[11][2]));
    WkIkWk[11][2] = -(.0936*(wk[11][0]*wk[11][1]));
    WkIkWk[14][0] = (.0436*(wk[14][1]*wk[14][2]));
    WkIkWk[14][1] = -(.000699999999999999*(wk[14][0]*wk[14][2]));
    WkIkWk[14][2] = -(.0429*(wk[14][0]*wk[14][1]));
    WkIkWk[17][0] = (.000207*(wk[17][1]*wk[17][2]));
    WkIkWk[17][1] = -(.002555*(wk[17][0]*wk[17][2]));
    WkIkWk[17][2] = (.002348*(wk[17][0]*wk[17][1]));
    WkIkWk[20][0] = -(6e-5*(wk[20][1]*wk[20][2]));
    WkIkWk[20][1] = -(2.00000000000001e-6*(wk[20][0]*wk[20][2]));
    WkIkWk[20][2] = (6.2e-5*(wk[20][0]*wk[20][1]));
    WkIkWk[23][0] = (.1005*(wk[23][1]*wk[23][2]));
    WkIkWk[23][1] = -(.00690000000000002*(wk[23][0]*wk[23][2]));
    WkIkWk[23][2] = -(.0936*(wk[23][0]*wk[23][1]));
    WkIkWk[26][0] = (.0436*(wk[26][1]*wk[26][2]));
    WkIkWk[26][1] = -(.000699999999999999*(wk[26][0]*wk[26][2]));
    WkIkWk[26][2] = -(.0429*(wk[26][0]*wk[26][1]));
    WkIkWk[29][0] = (.000207*(wk[29][1]*wk[29][2]));
    WkIkWk[29][1] = -(.002555*(wk[29][0]*wk[29][2]));
    WkIkWk[29][2] = (.002348*(wk[29][0]*wk[29][1]));
    WkIkWk[32][0] = -(6e-5*(wk[32][1]*wk[32][2]));
    WkIkWk[32][1] = -(2.00000000000001e-6*(wk[32][0]*wk[32][2]));
    WkIkWk[32][2] = (6.2e-5*(wk[32][0]*wk[32][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (u[3]*u[3]);
    w0w0[1] = (wk[8][0]*wk[8][0]);
    w0w0[2] = (wk[11][0]*wk[11][0]);
    w0w0[3] = (wk[14][0]*wk[14][0]);
    w0w0[4] = (wk[17][0]*wk[17][0]);
    w0w0[5] = (wk[20][0]*wk[20][0]);
    w0w0[6] = (wk[23][0]*wk[23][0]);
    w0w0[7] = (wk[26][0]*wk[26][0]);
    w0w0[8] = (wk[29][0]*wk[29][0]);
    w0w0[9] = (wk[32][0]*wk[32][0]);
    w1w1[0] = (u[4]*u[4]);
    w1w1[1] = (wk[8][1]*wk[8][1]);
    w1w1[2] = (wk[11][1]*wk[11][1]);
    w1w1[3] = (wk[14][1]*wk[14][1]);
    w1w1[4] = (wk[17][1]*wk[17][1]);
    w1w1[5] = (wk[20][1]*wk[20][1]);
    w1w1[6] = (wk[23][1]*wk[23][1]);
    w1w1[7] = (wk[26][1]*wk[26][1]);
    w1w1[8] = (wk[29][1]*wk[29][1]);
    w1w1[9] = (wk[32][1]*wk[32][1]);
    w2w2[0] = (u[5]*u[5]);
    w2w2[1] = (wk[8][2]*wk[8][2]);
    w2w2[2] = (wk[11][2]*wk[11][2]);
    w2w2[3] = (wk[14][2]*wk[14][2]);
    w2w2[4] = (wk[17][2]*wk[17][2]);
    w2w2[5] = (wk[20][2]*wk[20][2]);
    w2w2[6] = (wk[23][2]*wk[23][2]);
    w2w2[7] = (wk[26][2]*wk[26][2]);
    w2w2[8] = (wk[29][2]*wk[29][2]);
    w2w2[9] = (wk[32][2]*wk[32][2]);
    w0w1[0] = (u[3]*u[4]);
    w0w1[1] = (wk[8][0]*wk[8][1]);
    w0w1[2] = (wk[11][0]*wk[11][1]);
    w0w1[3] = (wk[14][0]*wk[14][1]);
    w0w1[4] = (wk[17][0]*wk[17][1]);
    w0w1[5] = (wk[20][0]*wk[20][1]);
    w0w1[6] = (wk[23][0]*wk[23][1]);
    w0w1[7] = (wk[26][0]*wk[26][1]);
    w0w1[8] = (wk[29][0]*wk[29][1]);
    w0w1[9] = (wk[32][0]*wk[32][1]);
    w0w2[0] = (u[3]*u[5]);
    w0w2[1] = (wk[8][0]*wk[8][2]);
    w0w2[2] = (wk[11][0]*wk[11][2]);
    w0w2[3] = (wk[14][0]*wk[14][2]);
    w0w2[4] = (wk[17][0]*wk[17][2]);
    w0w2[5] = (wk[20][0]*wk[20][2]);
    w0w2[6] = (wk[23][0]*wk[23][2]);
    w0w2[7] = (wk[26][0]*wk[26][2]);
    w0w2[8] = (wk[29][0]*wk[29][2]);
    w0w2[9] = (wk[32][0]*wk[32][2]);
    w1w2[0] = (u[4]*u[5]);
    w1w2[1] = (wk[8][1]*wk[8][2]);
    w1w2[2] = (wk[11][1]*wk[11][2]);
    w1w2[3] = (wk[14][1]*wk[14][2]);
    w1w2[4] = (wk[17][1]*wk[17][2]);
    w1w2[5] = (wk[20][1]*wk[20][2]);
    w1w2[6] = (wk[23][1]*wk[23][2]);
    w1w2[7] = (wk[26][1]*wk[26][2]);
    w1w2[8] = (wk[29][1]*wk[29][2]);
    w1w2[9] = (wk[32][1]*wk[32][2]);
    w00w11[0] = -(w0w0[0]+w1w1[0]);
    w00w11[1] = -(w0w0[1]+w1w1[1]);
    w00w11[2] = -(w0w0[2]+w1w1[2]);
    w00w11[3] = -(w0w0[3]+w1w1[3]);
    w00w11[4] = -(w0w0[4]+w1w1[4]);
    w00w11[5] = -(w0w0[5]+w1w1[5]);
    w00w11[6] = -(w0w0[6]+w1w1[6]);
    w00w11[7] = -(w0w0[7]+w1w1[7]);
    w00w11[8] = -(w0w0[8]+w1w1[8]);
    w00w11[9] = -(w0w0[9]+w1w1[9]);
    w00w22[0] = -(w0w0[0]+w2w2[0]);
    w00w22[1] = -(w0w0[1]+w2w2[1]);
    w00w22[2] = -(w0w0[2]+w2w2[2]);
    w00w22[3] = -(w0w0[3]+w2w2[3]);
    w00w22[4] = -(w0w0[4]+w2w2[4]);
    w00w22[5] = -(w0w0[5]+w2w2[5]);
    w00w22[6] = -(w0w0[6]+w2w2[6]);
    w00w22[7] = -(w0w0[7]+w2w2[7]);
    w00w22[8] = -(w0w0[8]+w2w2[8]);
    w00w22[9] = -(w0w0[9]+w2w2[9]);
    w11w22[0] = -(w1w1[0]+w2w2[0]);
    w11w22[1] = -(w1w1[1]+w2w2[1]);
    w11w22[2] = -(w1w1[2]+w2w2[2]);
    w11w22[3] = -(w1w1[3]+w2w2[3]);
    w11w22[4] = -(w1w1[4]+w2w2[4]);
    w11w22[5] = -(w1w1[5]+w2w2[5]);
    w11w22[6] = -(w1w1[6]+w2w2[6]);
    w11w22[7] = -(w1w1[7]+w2w2[7]);
    w11w22[8] = -(w1w1[8]+w2w2[8]);
    w11w22[9] = -(w1w1[9]+w2w2[9]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[1][0] = (Vik[0][0]+Vik[1][0]);
    vnk[1][1] = (Vik[0][1]+Vik[1][1]);
    vnk[1][2] = (Vik[0][2]+Vik[1][2]);
    vnk[2][0] = (Vik[2][0]+vnk[1][0]);
    vnk[2][1] = (Vik[2][1]+vnk[1][1]);
    vnk[2][2] = (Vik[2][2]+vnk[1][2]);
    vnk[6][0] = (vnk[2][0]+(.127*((Cik[3][0][2]*u[3])-(Cik[3][0][0]*u[5]))));
    vnk[6][1] = (vnk[2][1]+(.127*((Cik[3][1][2]*u[3])-(Cik[3][1][0]*u[5]))));
    vnk[6][2] = (vnk[2][2]+(.127*((Cik[3][2][2]*u[3])-(Cik[3][2][0]*u[5]))));
    vnk[8][0] = (vnk[6][0]+(.3202*((cnk[8][0][2]*wk[8][0])-(cnk[8][0][0]*
      wk[8][2]))));
    vnk[8][1] = (vnk[6][1]+(.3202*((cnk[8][1][2]*wk[8][0])-(cnk[8][1][0]*
      wk[8][2]))));
    vnk[8][2] = (vnk[6][2]+(.3202*((cnk[8][2][2]*wk[8][0])-(cnk[8][2][0]*
      wk[8][2]))));
    vnk[9][0] = (vnk[2][0]+(((Cik[3][0][0]*Wirk[9][0])-(.0935*(Cik[3][0][1]*u[3]
      )))-(.07*(Cik[3][0][2]*u[3]))));
    vnk[9][1] = (vnk[2][1]+(((Cik[3][1][0]*Wirk[9][0])-(.0935*(Cik[3][1][1]*u[3]
      )))-(.07*(Cik[3][1][2]*u[3]))));
    vnk[9][2] = (vnk[2][2]+(((Cik[3][2][0]*Wirk[9][0])-(.0935*(Cik[3][2][1]*u[3]
      )))-(.07*(Cik[3][2][2]*u[3]))));
    vnk[11][0] = (vnk[9][0]+((cnk[11][0][2]*Wkrpk[11][2])+((.1715*(cnk[11][0][0]
      *wk[11][2]))-(.002*(cnk[11][0][1]*wk[11][2])))));
    vnk[11][1] = (vnk[9][1]+((cnk[11][1][2]*Wkrpk[11][2])+((.1715*(cnk[11][1][0]
      *wk[11][2]))-(.002*(cnk[11][1][1]*wk[11][2])))));
    vnk[11][2] = (vnk[9][2]+((cnk[11][2][2]*Wkrpk[11][2])+((.1715*(cnk[11][2][0]
      *wk[11][2]))-(.002*(cnk[11][2][1]*wk[11][2])))));
    vnk[12][0] = (vnk[11][0]+((cnk[11][0][2]*Wirk[12][2])+((.0033*(cnk[11][0][1]
      *wk[11][2]))+(.2294*(cnk[11][0][0]*wk[11][2])))));
    vnk[12][1] = (vnk[11][1]+((cnk[11][1][2]*Wirk[12][2])+((.0033*(cnk[11][1][1]
      *wk[11][2]))+(.2294*(cnk[11][1][0]*wk[11][2])))));
    vnk[12][2] = (vnk[11][2]+((cnk[11][2][2]*Wirk[12][2])+((.0033*(cnk[11][2][1]
      *wk[11][2]))+(.2294*(cnk[11][2][0]*wk[11][2])))));
    vnk[14][0] = (vnk[12][0]+(.1862*((cnk[14][0][0]*wk[14][2])-(cnk[14][0][2]*
      wk[14][0]))));
    vnk[14][1] = (vnk[12][1]+(.1862*((cnk[14][1][0]*wk[14][2])-(cnk[14][1][2]*
      wk[14][0]))));
    vnk[14][2] = (vnk[12][2]+(.1862*((cnk[14][2][0]*wk[14][2])-(cnk[14][2][2]*
      wk[14][0]))));
    vnk[15][0] = (vnk[14][0]+(.2438*((cnk[14][0][0]*wk[14][2])-(cnk[14][0][2]*
      wk[14][0]))));
    vnk[15][1] = (vnk[14][1]+(.2438*((cnk[14][1][0]*wk[14][2])-(cnk[14][1][2]*
      wk[14][0]))));
    vnk[15][2] = (vnk[14][2]+(.2438*((cnk[14][2][0]*wk[14][2])-(cnk[14][2][2]*
      wk[14][0]))));
    vnk[17][0] = (vnk[15][0]+((cnk[17][0][2]*Wkrpk[17][2])+((cnk[17][0][0]*
      Wkrpk[17][0])+(cnk[17][0][1]*Wkrpk[17][1]))));
    vnk[17][1] = (vnk[15][1]+((cnk[17][1][2]*Wkrpk[17][2])+((cnk[17][1][0]*
      Wkrpk[17][0])+(cnk[17][1][1]*Wkrpk[17][1]))));
    vnk[17][2] = (vnk[15][2]+((cnk[17][2][2]*Wkrpk[17][2])+((cnk[17][2][0]*
      Wkrpk[17][0])+(cnk[17][2][1]*Wkrpk[17][1]))));
    vnk[18][0] = (vnk[17][0]+((cnk[17][0][2]*Wirk[18][2])+((cnk[17][0][0]*
      Wirk[18][0])+(cnk[17][0][1]*Wirk[18][1]))));
    vnk[18][1] = (vnk[17][1]+((cnk[17][1][2]*Wirk[18][2])+((cnk[17][1][0]*
      Wirk[18][0])+(cnk[17][1][1]*Wirk[18][1]))));
    vnk[18][2] = (vnk[17][2]+((cnk[17][2][2]*Wirk[18][2])+((cnk[17][2][0]*
      Wirk[18][0])+(cnk[17][2][1]*Wirk[18][1]))));
    vnk[20][0] = (vnk[18][0]+((cnk[20][0][2]*Wkrpk[20][2])+((cnk[20][0][0]*
      Wkrpk[20][0])+(cnk[20][0][1]*Wkrpk[20][1]))));
    vnk[20][1] = (vnk[18][1]+((cnk[20][1][2]*Wkrpk[20][2])+((cnk[20][1][0]*
      Wkrpk[20][0])+(cnk[20][1][1]*Wkrpk[20][1]))));
    vnk[20][2] = (vnk[18][2]+((cnk[20][2][2]*Wkrpk[20][2])+((cnk[20][2][0]*
      Wkrpk[20][0])+(cnk[20][2][1]*Wkrpk[20][1]))));
    vnk[21][0] = (vnk[2][0]+(((.0935*(Cik[3][0][1]*u[3]))+(Cik[3][0][0]*
      Wirk[21][0]))-(.07*(Cik[3][0][2]*u[3]))));
    vnk[21][1] = (vnk[2][1]+(((.0935*(Cik[3][1][1]*u[3]))+(Cik[3][1][0]*
      Wirk[21][0]))-(.07*(Cik[3][1][2]*u[3]))));
    vnk[21][2] = (vnk[2][2]+(((.0935*(Cik[3][2][1]*u[3]))+(Cik[3][2][0]*
      Wirk[21][0]))-(.07*(Cik[3][2][2]*u[3]))));
    vnk[23][0] = (vnk[21][0]+((cnk[23][0][2]*Wkrpk[23][2])+((.1715*(
      cnk[23][0][0]*wk[23][2]))-(.002*(cnk[23][0][1]*wk[23][2])))));
    vnk[23][1] = (vnk[21][1]+((cnk[23][1][2]*Wkrpk[23][2])+((.1715*(
      cnk[23][1][0]*wk[23][2]))-(.002*(cnk[23][1][1]*wk[23][2])))));
    vnk[23][2] = (vnk[21][2]+((cnk[23][2][2]*Wkrpk[23][2])+((.1715*(
      cnk[23][2][0]*wk[23][2]))-(.002*(cnk[23][2][1]*wk[23][2])))));
    vnk[24][0] = (vnk[23][0]+((cnk[23][0][2]*Wirk[24][2])+((.0033*(cnk[23][0][1]
      *wk[23][2]))+(.2294*(cnk[23][0][0]*wk[23][2])))));
    vnk[24][1] = (vnk[23][1]+((cnk[23][1][2]*Wirk[24][2])+((.0033*(cnk[23][1][1]
      *wk[23][2]))+(.2294*(cnk[23][1][0]*wk[23][2])))));
    vnk[24][2] = (vnk[23][2]+((cnk[23][2][2]*Wirk[24][2])+((.0033*(cnk[23][2][1]
      *wk[23][2]))+(.2294*(cnk[23][2][0]*wk[23][2])))));
    vnk[26][0] = (vnk[24][0]+(.1862*((cnk[26][0][0]*wk[26][2])-(cnk[26][0][2]*
      wk[26][0]))));
    vnk[26][1] = (vnk[24][1]+(.1862*((cnk[26][1][0]*wk[26][2])-(cnk[26][1][2]*
      wk[26][0]))));
    vnk[26][2] = (vnk[24][2]+(.1862*((cnk[26][2][0]*wk[26][2])-(cnk[26][2][2]*
      wk[26][0]))));
    vnk[27][0] = (vnk[26][0]+(.2438*((cnk[26][0][0]*wk[26][2])-(cnk[26][0][2]*
      wk[26][0]))));
    vnk[27][1] = (vnk[26][1]+(.2438*((cnk[26][1][0]*wk[26][2])-(cnk[26][1][2]*
      wk[26][0]))));
    vnk[27][2] = (vnk[26][2]+(.2438*((cnk[26][2][0]*wk[26][2])-(cnk[26][2][2]*
      wk[26][0]))));
    vnk[29][0] = (vnk[27][0]+((cnk[29][0][2]*Wkrpk[29][2])+((cnk[29][0][0]*
      Wkrpk[29][0])+(cnk[29][0][1]*Wkrpk[29][1]))));
    vnk[29][1] = (vnk[27][1]+((cnk[29][1][2]*Wkrpk[29][2])+((cnk[29][1][0]*
      Wkrpk[29][0])+(cnk[29][1][1]*Wkrpk[29][1]))));
    vnk[29][2] = (vnk[27][2]+((cnk[29][2][2]*Wkrpk[29][2])+((cnk[29][2][0]*
      Wkrpk[29][0])+(cnk[29][2][1]*Wkrpk[29][1]))));
    vnk[30][0] = (vnk[29][0]+((cnk[29][0][2]*Wirk[30][2])+((cnk[29][0][0]*
      Wirk[30][0])+(cnk[29][0][1]*Wirk[30][1]))));
    vnk[30][1] = (vnk[29][1]+((cnk[29][1][2]*Wirk[30][2])+((cnk[29][1][0]*
      Wirk[30][0])+(cnk[29][1][1]*Wirk[30][1]))));
    vnk[30][2] = (vnk[29][2]+((cnk[29][2][2]*Wirk[30][2])+((cnk[29][2][0]*
      Wirk[30][0])+(cnk[29][2][1]*Wirk[30][1]))));
    vnk[32][0] = (vnk[30][0]+((cnk[32][0][2]*Wkrpk[32][2])+((cnk[32][0][0]*
      Wkrpk[32][0])+(cnk[32][0][1]*Wkrpk[32][1]))));
    vnk[32][1] = (vnk[30][1]+((cnk[32][1][2]*Wkrpk[32][2])+((cnk[32][1][0]*
      Wkrpk[32][0])+(cnk[32][1][1]*Wkrpk[32][1]))));
    vnk[32][2] = (vnk[30][2]+((cnk[32][2][2]*Wkrpk[32][2])+((cnk[32][2][0]*
      Wkrpk[32][0])+(cnk[32][2][1]*Wkrpk[32][1]))));
    vnb[0][0] = vnk[2][0];
    vnb[0][1] = vnk[2][1];
    vnb[0][2] = vnk[2][2];
    vnb[1][0] = vnk[8][0];
    vnb[1][1] = vnk[8][1];
    vnb[1][2] = vnk[8][2];
    vnb[2][0] = vnk[11][0];
    vnb[2][1] = vnk[11][1];
    vnb[2][2] = vnk[11][2];
    vnb[3][0] = vnk[14][0];
    vnb[3][1] = vnk[14][1];
    vnb[3][2] = vnk[14][2];
    vnb[4][0] = vnk[17][0];
    vnb[4][1] = vnk[17][1];
    vnb[4][2] = vnk[17][2];
    vnb[5][0] = vnk[20][0];
    vnb[5][1] = vnk[20][1];
    vnb[5][2] = vnk[20][2];
    vnb[6][0] = vnk[23][0];
    vnb[6][1] = vnk[23][1];
    vnb[6][2] = vnk[23][2];
    vnb[7][0] = vnk[26][0];
    vnb[7][1] = vnk[26][1];
    vnb[7][2] = vnk[26][2];
    vnb[8][0] = vnk[29][0];
    vnb[8][1] = vnk[29][1];
    vnb[8][2] = vnk[29][2];
    vnb[9][0] = vnk[32][0];
    vnb[9][1] = vnk[32][1];
    vnb[9][2] = vnk[32][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = (.5*((q[33]*u[3])+((q[4]*u[5])-(q[5]*u[4]))));
    qdot[4] = (.5*((q[5]*u[3])+((q[33]*u[4])-(q[3]*u[5]))));
    qdot[5] = (.5*(((q[3]*u[4])+(q[33]*u[5]))-(q[4]*u[3])));
    qdot[33] = -(.5*((q[3]*u[3])+((q[4]*u[4])+(q[5]*u[5]))));
    if (stabvel  !=  0.) {
        ee = ((q[33]*q[33])+((q[5]*q[5])+((q[3]*q[3])+(q[4]*q[4]))));
        stab = ((stabvel*(1.-ee))/ee);
        qdot[3] = (qdot[3]+(q[3]*stab));
        qdot[4] = (qdot[4]+(q[4]*stab));
        qdot[5] = (qdot[5]+(q[5]*stab));
        qdot[33] = (qdot[33]+(q[33]*stab));
    }
    qdot[6] = u[6];
    qdot[7] = u[7];
    qdot[8] = u[8];
    qdot[9] = u[9];
    qdot[10] = u[10];
    qdot[11] = u[11];
    qdot[12] = u[12];
    qdot[13] = u[13];
    qdot[14] = u[14];
    qdot[15] = u[15];
    qdot[16] = u[16];
    qdot[17] = u[17];
    qdot[18] = u[18];
    qdot[19] = u[19];
    qdot[20] = u[20];
    qdot[21] = u[21];
    qdot[22] = u[22];
    qdot[23] = u[23];
    qdot[24] = u[24];
    qdot[25] = u[25];
    qdot[26] = u[26];
    qdot[27] = u[27];
    qdot[28] = u[28];
    qdot[29] = u[29];
    qdot[30] = u[30];
    qdot[31] = u[31];
    qdot[32] = u[32];
/*
Compute constraint velocity errors
*/
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 33; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
Initialize prescribed motions
*/
    uacc[0] = 0.;
    uvel[0] = u[0];
    upos[0] = q[0];
    uacc[1] = 0.;
    uvel[1] = u[1];
    upos[1] = q[1];
    uacc[2] = 0.;
    uvel[2] = u[2];
    upos[2] = q[2];
    uacc[3] = 0.;
    uvel[3] = u[3];
    upos[3] = q[3];
    uacc[4] = 0.;
    uvel[4] = u[4];
    upos[4] = q[4];
    uacc[5] = 0.;
    uvel[5] = u[5];
    upos[5] = q[5];
    uacc[6] = 0.;
    uvel[6] = u[6];
    upos[6] = q[6];
    uacc[7] = 0.;
    uvel[7] = u[7];
    upos[7] = q[7];
    uacc[8] = 0.;
    uvel[8] = u[8];
    upos[8] = q[8];
    uacc[9] = 0.;
    uvel[9] = u[9];
    upos[9] = q[9];
    uacc[10] = 0.;
    uvel[10] = u[10];
    upos[10] = q[10];
    uacc[11] = 0.;
    uvel[11] = u[11];
    upos[11] = q[11];
    uacc[12] = 0.;
    uvel[12] = u[12];
    upos[12] = q[12];
    uacc[13] = 0.;
    uvel[13] = u[13];
    upos[13] = q[13];
    uacc[14] = 0.;
    uvel[14] = u[14];
    upos[14] = q[14];
    uacc[15] = 0.;
    uvel[15] = u[15];
    upos[15] = q[15];
    uacc[16] = 0.;
    uvel[16] = u[16];
    upos[16] = q[16];
    uacc[17] = 0.;
    uvel[17] = u[17];
    upos[17] = q[17];
    uacc[18] = 0.;
    uvel[18] = u[18];
    upos[18] = q[18];
    uacc[19] = 0.;
    uvel[19] = u[19];
    upos[19] = q[19];
    uacc[20] = 0.;
    uvel[20] = u[20];
    upos[20] = q[20];
    uacc[21] = 0.;
    uvel[21] = u[21];
    upos[21] = q[21];
    uacc[22] = 0.;
    uvel[22] = u[22];
    upos[22] = q[22];
    uacc[23] = 0.;
    uvel[23] = u[23];
    upos[23] = q[23];
    uacc[24] = 0.;
    uvel[24] = u[24];
    upos[24] = q[24];
    uacc[25] = 0.;
    uvel[25] = u[25];
    upos[25] = q[25];
    uacc[26] = 0.;
    uvel[26] = u[26];
    upos[26] = q[26];
    uacc[27] = 0.;
    uvel[27] = u[27];
    upos[27] = q[27];
    uacc[28] = 0.;
    uvel[28] = u[28];
    upos[28] = q[28];
    uacc[29] = 0.;
    uvel[29] = u[29];
    upos[29] = q[29];
    uacc[30] = 0.;
    uvel[30] = u[30];
    upos[30] = q[30];
    uacc[31] = 0.;
    uvel[31] = u[31];
    upos[31] = q[31];
    uacc[32] = 0.;
    uvel[32] = u[32];
    upos[32] = q[32];
/*
 Used 0.16 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 2621 adds/subtracts/negates
                   3976 multiplies
                      1 divides
                   1604 assignments
*/
}

void sdqdot(double oqdot[34])
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 33; i++) {
        oqdot[i] = qdot[i];
    }
}

void sdu2qdot(double uin[33],
    double oqdot[34])
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 32; i++) {
        oqdot[i] = uin[i];
    }
    oqdot[3] = (.5*((q[33]*uin[3])+((q[4]*uin[5])-(q[5]*uin[4]))));
    oqdot[4] = (.5*((q[5]*uin[3])+((q[33]*uin[4])-(q[3]*uin[5]))));
    oqdot[5] = (.5*(((q[3]*uin[4])+(q[33]*uin[5]))-(q[4]*uin[3])));
    oqdot[33] = -(.5*((q[3]*uin[3])+((q[4]*uin[4])+(q[5]*uin[5]))));
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                     16 multiplies
                      0 divides
                     37 assignments
*/
}

void sdpsstate(double lqin[1])
{

    if (roustate != 2) {
        sdseterr(9,23);
        return;
    }
}

void sddovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[3][3][0] = 1.;
        Wpk[3][4][0] = 1.;
        Wpk[3][5][0] = 1.;
        Wpk[3][6][0] = Cik[6][0][0];
        Wpk[3][6][1] = Cik[6][0][1];
        Wpk[3][6][2] = Cik[6][0][2];
        Wpk[3][7][0] = ((Cik[6][0][2]*Cik[7][2][0])+((Cik[6][0][0]*Cik[7][0][0])
          +(Cik[6][0][1]*Cik[7][1][0])));
        Wpk[3][7][1] = ((Cik[6][0][2]*Cik[7][2][1])+((Cik[6][0][0]*Cik[7][0][1])
          +(Cik[6][0][1]*Cik[7][1][1])));
        Wpk[3][7][2] = ((Cik[6][0][2]*Cik[7][2][2])+((Cik[6][0][0]*Cik[7][0][2])
          +(Cik[6][0][1]*Cik[7][1][2])));
        Wpk[3][8][0] = ((Cik[8][2][0]*Wpk[3][7][2])+((Cik[8][0][0]*Wpk[3][7][0])
          +(Cik[8][1][0]*Wpk[3][7][1])));
        Wpk[3][8][1] = ((Cik[8][2][1]*Wpk[3][7][2])+((Cik[8][0][1]*Wpk[3][7][0])
          +(Cik[8][1][1]*Wpk[3][7][1])));
        Wpk[3][8][2] = ((Cik[8][2][2]*Wpk[3][7][2])+((Cik[8][0][2]*Wpk[3][7][0])
          +(Cik[8][1][2]*Wpk[3][7][1])));
        Wpk[3][9][0] = Cik[9][0][0];
        Wpk[3][9][1] = Cik[9][0][1];
        Wpk[3][9][2] = Cik[9][0][2];
        Wpk[3][10][0] = ((Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*
          Cik[10][0][0])+(Cik[9][0][1]*Cik[10][1][0])));
        Wpk[3][10][1] = ((Cik[9][0][2]*Cik[10][2][1])+((Cik[9][0][0]*
          Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1])));
        Wpk[3][10][2] = ((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
          Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2])));
        Wpk[3][11][0] = ((Cik[11][2][0]*Wpk[3][10][2])+((Cik[11][0][0]*
          Wpk[3][10][0])+(Cik[11][1][0]*Wpk[3][10][1])));
        Wpk[3][11][1] = ((Cik[11][2][1]*Wpk[3][10][2])+((Cik[11][0][1]*
          Wpk[3][10][0])+(Cik[11][1][1]*Wpk[3][10][1])));
        Wpk[3][11][2] = ((Cik[11][2][2]*Wpk[3][10][2])+((Cik[11][0][2]*
          Wpk[3][10][0])+(Cik[11][1][2]*Wpk[3][10][1])));
        Wpk[3][12][0] = ((Cik[12][2][0]*Wpk[3][11][2])+((Cik[12][0][0]*
          Wpk[3][11][0])+(Cik[12][1][0]*Wpk[3][11][1])));
        Wpk[3][12][1] = ((Cik[12][2][1]*Wpk[3][11][2])+((Cik[12][0][1]*
          Wpk[3][11][0])+(Cik[12][1][1]*Wpk[3][11][1])));
        Wpk[3][12][2] = ((Cik[12][2][2]*Wpk[3][11][2])+((Cik[12][0][2]*
          Wpk[3][11][0])+(Cik[12][1][2]*Wpk[3][11][1])));
        Wpk[3][13][0] = ((Cik[13][2][0]*Wpk[3][12][2])+((Cik[13][0][0]*
          Wpk[3][12][0])+(Cik[13][1][0]*Wpk[3][12][1])));
        Wpk[3][13][1] = ((Cik[13][2][1]*Wpk[3][12][2])+((Cik[13][0][1]*
          Wpk[3][12][0])+(Cik[13][1][1]*Wpk[3][12][1])));
        Wpk[3][13][2] = ((Cik[13][2][2]*Wpk[3][12][2])+((Cik[13][0][2]*
          Wpk[3][12][0])+(Cik[13][1][2]*Wpk[3][12][1])));
        Wpk[3][14][0] = ((Cik[14][2][0]*Wpk[3][13][2])+((Cik[14][0][0]*
          Wpk[3][13][0])+(Cik[14][1][0]*Wpk[3][13][1])));
        Wpk[3][14][1] = ((Cik[14][2][1]*Wpk[3][13][2])+((Cik[14][0][1]*
          Wpk[3][13][0])+(Cik[14][1][1]*Wpk[3][13][1])));
        Wpk[3][14][2] = ((Cik[14][2][2]*Wpk[3][13][2])+((Cik[14][0][2]*
          Wpk[3][13][0])+(Cik[14][1][2]*Wpk[3][13][1])));
        Wpk[3][15][0] = ((Cik[15][2][0]*Wpk[3][14][2])+((Cik[15][0][0]*
          Wpk[3][14][0])+(Cik[15][1][0]*Wpk[3][14][1])));
        Wpk[3][15][1] = ((Cik[15][2][1]*Wpk[3][14][2])+((Cik[15][0][1]*
          Wpk[3][14][0])+(Cik[15][1][1]*Wpk[3][14][1])));
        Wpk[3][15][2] = ((Cik[15][2][2]*Wpk[3][14][2])+((Cik[15][0][2]*
          Wpk[3][14][0])+(Cik[15][1][2]*Wpk[3][14][1])));
        Wpk[3][16][0] = ((Cik[16][2][0]*Wpk[3][15][2])+((Cik[16][0][0]*
          Wpk[3][15][0])+(Cik[16][1][0]*Wpk[3][15][1])));
        Wpk[3][16][1] = ((Cik[16][2][1]*Wpk[3][15][2])+((Cik[16][0][1]*
          Wpk[3][15][0])+(Cik[16][1][1]*Wpk[3][15][1])));
        Wpk[3][16][2] = ((Cik[16][2][2]*Wpk[3][15][2])+((Cik[16][0][2]*
          Wpk[3][15][0])+(Cik[16][1][2]*Wpk[3][15][1])));
        Wpk[3][17][0] = ((Cik[17][2][0]*Wpk[3][16][2])+((Cik[17][0][0]*
          Wpk[3][16][0])+(Cik[17][1][0]*Wpk[3][16][1])));
        Wpk[3][17][1] = ((Cik[17][2][1]*Wpk[3][16][2])+((Cik[17][0][1]*
          Wpk[3][16][0])+(Cik[17][1][1]*Wpk[3][16][1])));
        Wpk[3][17][2] = ((Cik[17][2][2]*Wpk[3][16][2])+((Cik[17][0][2]*
          Wpk[3][16][0])+(Cik[17][1][2]*Wpk[3][16][1])));
        Wpk[3][18][0] = ((Cik[18][2][0]*Wpk[3][17][2])+((Cik[18][0][0]*
          Wpk[3][17][0])+(Cik[18][1][0]*Wpk[3][17][1])));
        Wpk[3][18][1] = ((Cik[18][2][1]*Wpk[3][17][2])+((Cik[18][0][1]*
          Wpk[3][17][0])+(Cik[18][1][1]*Wpk[3][17][1])));
        Wpk[3][18][2] = ((Cik[18][2][2]*Wpk[3][17][2])+((Cik[18][0][2]*
          Wpk[3][17][0])+(Cik[18][1][2]*Wpk[3][17][1])));
        Wpk[3][19][0] = ((Cik[19][2][0]*Wpk[3][18][2])+((Cik[19][0][0]*
          Wpk[3][18][0])+(Cik[19][1][0]*Wpk[3][18][1])));
        Wpk[3][19][1] = ((Cik[19][2][1]*Wpk[3][18][2])+((Cik[19][0][1]*
          Wpk[3][18][0])+(Cik[19][1][1]*Wpk[3][18][1])));
        Wpk[3][19][2] = ((Cik[19][2][2]*Wpk[3][18][2])+((Cik[19][0][2]*
          Wpk[3][18][0])+(Cik[19][1][2]*Wpk[3][18][1])));
        Wpk[3][20][0] = ((Cik[20][2][0]*Wpk[3][19][2])+((Cik[20][0][0]*
          Wpk[3][19][0])+(Cik[20][1][0]*Wpk[3][19][1])));
        Wpk[3][20][1] = ((Cik[20][2][1]*Wpk[3][19][2])+((Cik[20][0][1]*
          Wpk[3][19][0])+(Cik[20][1][1]*Wpk[3][19][1])));
        Wpk[3][20][2] = ((Cik[20][2][2]*Wpk[3][19][2])+((Cik[20][0][2]*
          Wpk[3][19][0])+(Cik[20][1][2]*Wpk[3][19][1])));
        Wpk[3][21][0] = Cik[21][0][0];
        Wpk[3][21][1] = Cik[21][0][1];
        Wpk[3][21][2] = Cik[21][0][2];
        Wpk[3][22][0] = ((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*
          Cik[22][0][0])+(Cik[21][0][1]*Cik[22][1][0])));
        Wpk[3][22][1] = ((Cik[21][0][2]*Cik[22][2][1])+((Cik[21][0][0]*
          Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1])));
        Wpk[3][22][2] = ((Cik[21][0][2]*Cik[22][2][2])+((Cik[21][0][0]*
          Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2])));
        Wpk[3][23][0] = ((Cik[23][2][0]*Wpk[3][22][2])+((Cik[23][0][0]*
          Wpk[3][22][0])+(Cik[23][1][0]*Wpk[3][22][1])));
        Wpk[3][23][1] = ((Cik[23][2][1]*Wpk[3][22][2])+((Cik[23][0][1]*
          Wpk[3][22][0])+(Cik[23][1][1]*Wpk[3][22][1])));
        Wpk[3][23][2] = ((Cik[23][2][2]*Wpk[3][22][2])+((Cik[23][0][2]*
          Wpk[3][22][0])+(Cik[23][1][2]*Wpk[3][22][1])));
        Wpk[3][24][0] = ((Cik[24][2][0]*Wpk[3][23][2])+((Cik[24][0][0]*
          Wpk[3][23][0])+(Cik[24][1][0]*Wpk[3][23][1])));
        Wpk[3][24][1] = ((Cik[24][2][1]*Wpk[3][23][2])+((Cik[24][0][1]*
          Wpk[3][23][0])+(Cik[24][1][1]*Wpk[3][23][1])));
        Wpk[3][24][2] = ((Cik[24][2][2]*Wpk[3][23][2])+((Cik[24][0][2]*
          Wpk[3][23][0])+(Cik[24][1][2]*Wpk[3][23][1])));
        Wpk[3][25][0] = ((Cik[25][2][0]*Wpk[3][24][2])+((Cik[25][0][0]*
          Wpk[3][24][0])+(Cik[25][1][0]*Wpk[3][24][1])));
        Wpk[3][25][1] = ((Cik[25][2][1]*Wpk[3][24][2])+((Cik[25][0][1]*
          Wpk[3][24][0])+(Cik[25][1][1]*Wpk[3][24][1])));
        Wpk[3][25][2] = ((Cik[25][2][2]*Wpk[3][24][2])+((Cik[25][0][2]*
          Wpk[3][24][0])+(Cik[25][1][2]*Wpk[3][24][1])));
        Wpk[3][26][0] = ((Cik[26][2][0]*Wpk[3][25][2])+((Cik[26][0][0]*
          Wpk[3][25][0])+(Cik[26][1][0]*Wpk[3][25][1])));
        Wpk[3][26][1] = ((Cik[26][2][1]*Wpk[3][25][2])+((Cik[26][0][1]*
          Wpk[3][25][0])+(Cik[26][1][1]*Wpk[3][25][1])));
        Wpk[3][26][2] = ((Cik[26][2][2]*Wpk[3][25][2])+((Cik[26][0][2]*
          Wpk[3][25][0])+(Cik[26][1][2]*Wpk[3][25][1])));
        Wpk[3][27][0] = ((Cik[27][2][0]*Wpk[3][26][2])+((Cik[27][0][0]*
          Wpk[3][26][0])+(Cik[27][1][0]*Wpk[3][26][1])));
        Wpk[3][27][1] = ((Cik[27][2][1]*Wpk[3][26][2])+((Cik[27][0][1]*
          Wpk[3][26][0])+(Cik[27][1][1]*Wpk[3][26][1])));
        Wpk[3][27][2] = ((Cik[27][2][2]*Wpk[3][26][2])+((Cik[27][0][2]*
          Wpk[3][26][0])+(Cik[27][1][2]*Wpk[3][26][1])));
        Wpk[3][28][0] = ((Cik[28][2][0]*Wpk[3][27][2])+((Cik[28][0][0]*
          Wpk[3][27][0])+(Cik[28][1][0]*Wpk[3][27][1])));
        Wpk[3][28][1] = ((Cik[28][2][1]*Wpk[3][27][2])+((Cik[28][0][1]*
          Wpk[3][27][0])+(Cik[28][1][1]*Wpk[3][27][1])));
        Wpk[3][28][2] = ((Cik[28][2][2]*Wpk[3][27][2])+((Cik[28][0][2]*
          Wpk[3][27][0])+(Cik[28][1][2]*Wpk[3][27][1])));
        Wpk[3][29][0] = ((Cik[29][2][0]*Wpk[3][28][2])+((Cik[29][0][0]*
          Wpk[3][28][0])+(Cik[29][1][0]*Wpk[3][28][1])));
        Wpk[3][29][1] = ((Cik[29][2][1]*Wpk[3][28][2])+((Cik[29][0][1]*
          Wpk[3][28][0])+(Cik[29][1][1]*Wpk[3][28][1])));
        Wpk[3][29][2] = ((Cik[29][2][2]*Wpk[3][28][2])+((Cik[29][0][2]*
          Wpk[3][28][0])+(Cik[29][1][2]*Wpk[3][28][1])));
        Wpk[3][30][0] = ((Cik[30][2][0]*Wpk[3][29][2])+((Cik[30][0][0]*
          Wpk[3][29][0])+(Cik[30][1][0]*Wpk[3][29][1])));
        Wpk[3][30][1] = ((Cik[30][2][1]*Wpk[3][29][2])+((Cik[30][0][1]*
          Wpk[3][29][0])+(Cik[30][1][1]*Wpk[3][29][1])));
        Wpk[3][30][2] = ((Cik[30][2][2]*Wpk[3][29][2])+((Cik[30][0][2]*
          Wpk[3][29][0])+(Cik[30][1][2]*Wpk[3][29][1])));
        Wpk[3][31][0] = ((Cik[31][2][0]*Wpk[3][30][2])+((Cik[31][0][0]*
          Wpk[3][30][0])+(Cik[31][1][0]*Wpk[3][30][1])));
        Wpk[3][31][1] = ((Cik[31][2][1]*Wpk[3][30][2])+((Cik[31][0][1]*
          Wpk[3][30][0])+(Cik[31][1][1]*Wpk[3][30][1])));
        Wpk[3][31][2] = ((Cik[31][2][2]*Wpk[3][30][2])+((Cik[31][0][2]*
          Wpk[3][30][0])+(Cik[31][1][2]*Wpk[3][30][1])));
        Wpk[3][32][0] = ((Cik[32][2][0]*Wpk[3][31][2])+((Cik[32][0][0]*
          Wpk[3][31][0])+(Cik[32][1][0]*Wpk[3][31][1])));
        Wpk[3][32][1] = ((Cik[32][2][1]*Wpk[3][31][2])+((Cik[32][0][1]*
          Wpk[3][31][0])+(Cik[32][1][1]*Wpk[3][31][1])));
        Wpk[3][32][2] = ((Cik[32][2][2]*Wpk[3][31][2])+((Cik[32][0][2]*
          Wpk[3][31][0])+(Cik[32][1][2]*Wpk[3][31][1])));
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = 1.;
        Wpk[4][6][0] = Cik[6][1][0];
        Wpk[4][6][1] = Cik[6][1][1];
        Wpk[4][6][2] = Cik[6][1][2];
        Wpk[4][7][0] = ((Cik[6][1][2]*Cik[7][2][0])+((Cik[6][1][0]*Cik[7][0][0])
          +(Cik[6][1][1]*Cik[7][1][0])));
        Wpk[4][7][1] = ((Cik[6][1][2]*Cik[7][2][1])+((Cik[6][1][0]*Cik[7][0][1])
          +(Cik[6][1][1]*Cik[7][1][1])));
        Wpk[4][7][2] = ((Cik[6][1][2]*Cik[7][2][2])+((Cik[6][1][0]*Cik[7][0][2])
          +(Cik[6][1][1]*Cik[7][1][2])));
        Wpk[4][8][0] = ((Cik[8][2][0]*Wpk[4][7][2])+((Cik[8][0][0]*Wpk[4][7][0])
          +(Cik[8][1][0]*Wpk[4][7][1])));
        Wpk[4][8][1] = ((Cik[8][2][1]*Wpk[4][7][2])+((Cik[8][0][1]*Wpk[4][7][0])
          +(Cik[8][1][1]*Wpk[4][7][1])));
        Wpk[4][8][2] = ((Cik[8][2][2]*Wpk[4][7][2])+((Cik[8][0][2]*Wpk[4][7][0])
          +(Cik[8][1][2]*Wpk[4][7][1])));
        Wpk[4][9][0] = Cik[9][1][0];
        Wpk[4][9][1] = Cik[9][1][1];
        Wpk[4][9][2] = Cik[9][1][2];
        Wpk[4][10][0] = ((Cik[9][1][2]*Cik[10][2][0])+((Cik[9][1][0]*
          Cik[10][0][0])+(Cik[9][1][1]*Cik[10][1][0])));
        Wpk[4][10][1] = ((Cik[9][1][2]*Cik[10][2][1])+((Cik[9][1][0]*
          Cik[10][0][1])+(Cik[9][1][1]*Cik[10][1][1])));
        Wpk[4][10][2] = ((Cik[9][1][2]*Cik[10][2][2])+((Cik[9][1][0]*
          Cik[10][0][2])+(Cik[9][1][1]*Cik[10][1][2])));
        Wpk[4][11][0] = ((Cik[11][2][0]*Wpk[4][10][2])+((Cik[11][0][0]*
          Wpk[4][10][0])+(Cik[11][1][0]*Wpk[4][10][1])));
        Wpk[4][11][1] = ((Cik[11][2][1]*Wpk[4][10][2])+((Cik[11][0][1]*
          Wpk[4][10][0])+(Cik[11][1][1]*Wpk[4][10][1])));
        Wpk[4][11][2] = ((Cik[11][2][2]*Wpk[4][10][2])+((Cik[11][0][2]*
          Wpk[4][10][0])+(Cik[11][1][2]*Wpk[4][10][1])));
        Wpk[4][12][0] = ((Cik[12][2][0]*Wpk[4][11][2])+((Cik[12][0][0]*
          Wpk[4][11][0])+(Cik[12][1][0]*Wpk[4][11][1])));
        Wpk[4][12][1] = ((Cik[12][2][1]*Wpk[4][11][2])+((Cik[12][0][1]*
          Wpk[4][11][0])+(Cik[12][1][1]*Wpk[4][11][1])));
        Wpk[4][12][2] = ((Cik[12][2][2]*Wpk[4][11][2])+((Cik[12][0][2]*
          Wpk[4][11][0])+(Cik[12][1][2]*Wpk[4][11][1])));
        Wpk[4][13][0] = ((Cik[13][2][0]*Wpk[4][12][2])+((Cik[13][0][0]*
          Wpk[4][12][0])+(Cik[13][1][0]*Wpk[4][12][1])));
        Wpk[4][13][1] = ((Cik[13][2][1]*Wpk[4][12][2])+((Cik[13][0][1]*
          Wpk[4][12][0])+(Cik[13][1][1]*Wpk[4][12][1])));
        Wpk[4][13][2] = ((Cik[13][2][2]*Wpk[4][12][2])+((Cik[13][0][2]*
          Wpk[4][12][0])+(Cik[13][1][2]*Wpk[4][12][1])));
        Wpk[4][14][0] = ((Cik[14][2][0]*Wpk[4][13][2])+((Cik[14][0][0]*
          Wpk[4][13][0])+(Cik[14][1][0]*Wpk[4][13][1])));
        Wpk[4][14][1] = ((Cik[14][2][1]*Wpk[4][13][2])+((Cik[14][0][1]*
          Wpk[4][13][0])+(Cik[14][1][1]*Wpk[4][13][1])));
        Wpk[4][14][2] = ((Cik[14][2][2]*Wpk[4][13][2])+((Cik[14][0][2]*
          Wpk[4][13][0])+(Cik[14][1][2]*Wpk[4][13][1])));
        Wpk[4][15][0] = ((Cik[15][2][0]*Wpk[4][14][2])+((Cik[15][0][0]*
          Wpk[4][14][0])+(Cik[15][1][0]*Wpk[4][14][1])));
        Wpk[4][15][1] = ((Cik[15][2][1]*Wpk[4][14][2])+((Cik[15][0][1]*
          Wpk[4][14][0])+(Cik[15][1][1]*Wpk[4][14][1])));
        Wpk[4][15][2] = ((Cik[15][2][2]*Wpk[4][14][2])+((Cik[15][0][2]*
          Wpk[4][14][0])+(Cik[15][1][2]*Wpk[4][14][1])));
        Wpk[4][16][0] = ((Cik[16][2][0]*Wpk[4][15][2])+((Cik[16][0][0]*
          Wpk[4][15][0])+(Cik[16][1][0]*Wpk[4][15][1])));
        Wpk[4][16][1] = ((Cik[16][2][1]*Wpk[4][15][2])+((Cik[16][0][1]*
          Wpk[4][15][0])+(Cik[16][1][1]*Wpk[4][15][1])));
        Wpk[4][16][2] = ((Cik[16][2][2]*Wpk[4][15][2])+((Cik[16][0][2]*
          Wpk[4][15][0])+(Cik[16][1][2]*Wpk[4][15][1])));
        Wpk[4][17][0] = ((Cik[17][2][0]*Wpk[4][16][2])+((Cik[17][0][0]*
          Wpk[4][16][0])+(Cik[17][1][0]*Wpk[4][16][1])));
        Wpk[4][17][1] = ((Cik[17][2][1]*Wpk[4][16][2])+((Cik[17][0][1]*
          Wpk[4][16][0])+(Cik[17][1][1]*Wpk[4][16][1])));
        Wpk[4][17][2] = ((Cik[17][2][2]*Wpk[4][16][2])+((Cik[17][0][2]*
          Wpk[4][16][0])+(Cik[17][1][2]*Wpk[4][16][1])));
        Wpk[4][18][0] = ((Cik[18][2][0]*Wpk[4][17][2])+((Cik[18][0][0]*
          Wpk[4][17][0])+(Cik[18][1][0]*Wpk[4][17][1])));
        Wpk[4][18][1] = ((Cik[18][2][1]*Wpk[4][17][2])+((Cik[18][0][1]*
          Wpk[4][17][0])+(Cik[18][1][1]*Wpk[4][17][1])));
        Wpk[4][18][2] = ((Cik[18][2][2]*Wpk[4][17][2])+((Cik[18][0][2]*
          Wpk[4][17][0])+(Cik[18][1][2]*Wpk[4][17][1])));
        Wpk[4][19][0] = ((Cik[19][2][0]*Wpk[4][18][2])+((Cik[19][0][0]*
          Wpk[4][18][0])+(Cik[19][1][0]*Wpk[4][18][1])));
        Wpk[4][19][1] = ((Cik[19][2][1]*Wpk[4][18][2])+((Cik[19][0][1]*
          Wpk[4][18][0])+(Cik[19][1][1]*Wpk[4][18][1])));
        Wpk[4][19][2] = ((Cik[19][2][2]*Wpk[4][18][2])+((Cik[19][0][2]*
          Wpk[4][18][0])+(Cik[19][1][2]*Wpk[4][18][1])));
        Wpk[4][20][0] = ((Cik[20][2][0]*Wpk[4][19][2])+((Cik[20][0][0]*
          Wpk[4][19][0])+(Cik[20][1][0]*Wpk[4][19][1])));
        Wpk[4][20][1] = ((Cik[20][2][1]*Wpk[4][19][2])+((Cik[20][0][1]*
          Wpk[4][19][0])+(Cik[20][1][1]*Wpk[4][19][1])));
        Wpk[4][20][2] = ((Cik[20][2][2]*Wpk[4][19][2])+((Cik[20][0][2]*
          Wpk[4][19][0])+(Cik[20][1][2]*Wpk[4][19][1])));
        Wpk[4][21][0] = Cik[21][1][0];
        Wpk[4][21][1] = Cik[21][1][1];
        Wpk[4][21][2] = Cik[21][1][2];
        Wpk[4][22][0] = ((Cik[21][1][2]*Cik[22][2][0])+((Cik[21][1][0]*
          Cik[22][0][0])+(Cik[21][1][1]*Cik[22][1][0])));
        Wpk[4][22][1] = ((Cik[21][1][2]*Cik[22][2][1])+((Cik[21][1][0]*
          Cik[22][0][1])+(Cik[21][1][1]*Cik[22][1][1])));
        Wpk[4][22][2] = ((Cik[21][1][2]*Cik[22][2][2])+((Cik[21][1][0]*
          Cik[22][0][2])+(Cik[21][1][1]*Cik[22][1][2])));
        Wpk[4][23][0] = ((Cik[23][2][0]*Wpk[4][22][2])+((Cik[23][0][0]*
          Wpk[4][22][0])+(Cik[23][1][0]*Wpk[4][22][1])));
        Wpk[4][23][1] = ((Cik[23][2][1]*Wpk[4][22][2])+((Cik[23][0][1]*
          Wpk[4][22][0])+(Cik[23][1][1]*Wpk[4][22][1])));
        Wpk[4][23][2] = ((Cik[23][2][2]*Wpk[4][22][2])+((Cik[23][0][2]*
          Wpk[4][22][0])+(Cik[23][1][2]*Wpk[4][22][1])));
        Wpk[4][24][0] = ((Cik[24][2][0]*Wpk[4][23][2])+((Cik[24][0][0]*
          Wpk[4][23][0])+(Cik[24][1][0]*Wpk[4][23][1])));
        Wpk[4][24][1] = ((Cik[24][2][1]*Wpk[4][23][2])+((Cik[24][0][1]*
          Wpk[4][23][0])+(Cik[24][1][1]*Wpk[4][23][1])));
        Wpk[4][24][2] = ((Cik[24][2][2]*Wpk[4][23][2])+((Cik[24][0][2]*
          Wpk[4][23][0])+(Cik[24][1][2]*Wpk[4][23][1])));
        Wpk[4][25][0] = ((Cik[25][2][0]*Wpk[4][24][2])+((Cik[25][0][0]*
          Wpk[4][24][0])+(Cik[25][1][0]*Wpk[4][24][1])));
        Wpk[4][25][1] = ((Cik[25][2][1]*Wpk[4][24][2])+((Cik[25][0][1]*
          Wpk[4][24][0])+(Cik[25][1][1]*Wpk[4][24][1])));
        Wpk[4][25][2] = ((Cik[25][2][2]*Wpk[4][24][2])+((Cik[25][0][2]*
          Wpk[4][24][0])+(Cik[25][1][2]*Wpk[4][24][1])));
        Wpk[4][26][0] = ((Cik[26][2][0]*Wpk[4][25][2])+((Cik[26][0][0]*
          Wpk[4][25][0])+(Cik[26][1][0]*Wpk[4][25][1])));
        Wpk[4][26][1] = ((Cik[26][2][1]*Wpk[4][25][2])+((Cik[26][0][1]*
          Wpk[4][25][0])+(Cik[26][1][1]*Wpk[4][25][1])));
        Wpk[4][26][2] = ((Cik[26][2][2]*Wpk[4][25][2])+((Cik[26][0][2]*
          Wpk[4][25][0])+(Cik[26][1][2]*Wpk[4][25][1])));
        Wpk[4][27][0] = ((Cik[27][2][0]*Wpk[4][26][2])+((Cik[27][0][0]*
          Wpk[4][26][0])+(Cik[27][1][0]*Wpk[4][26][1])));
        Wpk[4][27][1] = ((Cik[27][2][1]*Wpk[4][26][2])+((Cik[27][0][1]*
          Wpk[4][26][0])+(Cik[27][1][1]*Wpk[4][26][1])));
        Wpk[4][27][2] = ((Cik[27][2][2]*Wpk[4][26][2])+((Cik[27][0][2]*
          Wpk[4][26][0])+(Cik[27][1][2]*Wpk[4][26][1])));
        Wpk[4][28][0] = ((Cik[28][2][0]*Wpk[4][27][2])+((Cik[28][0][0]*
          Wpk[4][27][0])+(Cik[28][1][0]*Wpk[4][27][1])));
        Wpk[4][28][1] = ((Cik[28][2][1]*Wpk[4][27][2])+((Cik[28][0][1]*
          Wpk[4][27][0])+(Cik[28][1][1]*Wpk[4][27][1])));
        Wpk[4][28][2] = ((Cik[28][2][2]*Wpk[4][27][2])+((Cik[28][0][2]*
          Wpk[4][27][0])+(Cik[28][1][2]*Wpk[4][27][1])));
        Wpk[4][29][0] = ((Cik[29][2][0]*Wpk[4][28][2])+((Cik[29][0][0]*
          Wpk[4][28][0])+(Cik[29][1][0]*Wpk[4][28][1])));
        Wpk[4][29][1] = ((Cik[29][2][1]*Wpk[4][28][2])+((Cik[29][0][1]*
          Wpk[4][28][0])+(Cik[29][1][1]*Wpk[4][28][1])));
        Wpk[4][29][2] = ((Cik[29][2][2]*Wpk[4][28][2])+((Cik[29][0][2]*
          Wpk[4][28][0])+(Cik[29][1][2]*Wpk[4][28][1])));
        Wpk[4][30][0] = ((Cik[30][2][0]*Wpk[4][29][2])+((Cik[30][0][0]*
          Wpk[4][29][0])+(Cik[30][1][0]*Wpk[4][29][1])));
        Wpk[4][30][1] = ((Cik[30][2][1]*Wpk[4][29][2])+((Cik[30][0][1]*
          Wpk[4][29][0])+(Cik[30][1][1]*Wpk[4][29][1])));
        Wpk[4][30][2] = ((Cik[30][2][2]*Wpk[4][29][2])+((Cik[30][0][2]*
          Wpk[4][29][0])+(Cik[30][1][2]*Wpk[4][29][1])));
        Wpk[4][31][0] = ((Cik[31][2][0]*Wpk[4][30][2])+((Cik[31][0][0]*
          Wpk[4][30][0])+(Cik[31][1][0]*Wpk[4][30][1])));
        Wpk[4][31][1] = ((Cik[31][2][1]*Wpk[4][30][2])+((Cik[31][0][1]*
          Wpk[4][30][0])+(Cik[31][1][1]*Wpk[4][30][1])));
        Wpk[4][31][2] = ((Cik[31][2][2]*Wpk[4][30][2])+((Cik[31][0][2]*
          Wpk[4][30][0])+(Cik[31][1][2]*Wpk[4][30][1])));
        Wpk[4][32][0] = ((Cik[32][2][0]*Wpk[4][31][2])+((Cik[32][0][0]*
          Wpk[4][31][0])+(Cik[32][1][0]*Wpk[4][31][1])));
        Wpk[4][32][1] = ((Cik[32][2][1]*Wpk[4][31][2])+((Cik[32][0][1]*
          Wpk[4][31][0])+(Cik[32][1][1]*Wpk[4][31][1])));
        Wpk[4][32][2] = ((Cik[32][2][2]*Wpk[4][31][2])+((Cik[32][0][2]*
          Wpk[4][31][0])+(Cik[32][1][2]*Wpk[4][31][1])));
        Wpk[5][5][2] = 1.;
        Wpk[5][6][0] = Cik[6][2][0];
        Wpk[5][6][1] = Cik[6][2][1];
        Wpk[5][6][2] = Cik[6][2][2];
        Wpk[5][7][0] = ((Cik[6][2][2]*Cik[7][2][0])+((Cik[6][2][0]*Cik[7][0][0])
          +(Cik[6][2][1]*Cik[7][1][0])));
        Wpk[5][7][1] = ((Cik[6][2][2]*Cik[7][2][1])+((Cik[6][2][0]*Cik[7][0][1])
          +(Cik[6][2][1]*Cik[7][1][1])));
        Wpk[5][7][2] = ((Cik[6][2][2]*Cik[7][2][2])+((Cik[6][2][0]*Cik[7][0][2])
          +(Cik[6][2][1]*Cik[7][1][2])));
        Wpk[5][8][0] = ((Cik[8][2][0]*Wpk[5][7][2])+((Cik[8][0][0]*Wpk[5][7][0])
          +(Cik[8][1][0]*Wpk[5][7][1])));
        Wpk[5][8][1] = ((Cik[8][2][1]*Wpk[5][7][2])+((Cik[8][0][1]*Wpk[5][7][0])
          +(Cik[8][1][1]*Wpk[5][7][1])));
        Wpk[5][8][2] = ((Cik[8][2][2]*Wpk[5][7][2])+((Cik[8][0][2]*Wpk[5][7][0])
          +(Cik[8][1][2]*Wpk[5][7][1])));
        Wpk[5][9][0] = Cik[9][2][0];
        Wpk[5][9][1] = Cik[9][2][1];
        Wpk[5][9][2] = Cik[9][2][2];
        Wpk[5][10][0] = ((Cik[9][2][2]*Cik[10][2][0])+((Cik[9][2][0]*
          Cik[10][0][0])+(Cik[9][2][1]*Cik[10][1][0])));
        Wpk[5][10][1] = ((Cik[9][2][2]*Cik[10][2][1])+((Cik[9][2][0]*
          Cik[10][0][1])+(Cik[9][2][1]*Cik[10][1][1])));
        Wpk[5][10][2] = ((Cik[9][2][2]*Cik[10][2][2])+((Cik[9][2][0]*
          Cik[10][0][2])+(Cik[9][2][1]*Cik[10][1][2])));
        Wpk[5][11][0] = ((Cik[11][2][0]*Wpk[5][10][2])+((Cik[11][0][0]*
          Wpk[5][10][0])+(Cik[11][1][0]*Wpk[5][10][1])));
        Wpk[5][11][1] = ((Cik[11][2][1]*Wpk[5][10][2])+((Cik[11][0][1]*
          Wpk[5][10][0])+(Cik[11][1][1]*Wpk[5][10][1])));
        Wpk[5][11][2] = ((Cik[11][2][2]*Wpk[5][10][2])+((Cik[11][0][2]*
          Wpk[5][10][0])+(Cik[11][1][2]*Wpk[5][10][1])));
        Wpk[5][12][0] = ((Cik[12][2][0]*Wpk[5][11][2])+((Cik[12][0][0]*
          Wpk[5][11][0])+(Cik[12][1][0]*Wpk[5][11][1])));
        Wpk[5][12][1] = ((Cik[12][2][1]*Wpk[5][11][2])+((Cik[12][0][1]*
          Wpk[5][11][0])+(Cik[12][1][1]*Wpk[5][11][1])));
        Wpk[5][12][2] = ((Cik[12][2][2]*Wpk[5][11][2])+((Cik[12][0][2]*
          Wpk[5][11][0])+(Cik[12][1][2]*Wpk[5][11][1])));
        Wpk[5][13][0] = ((Cik[13][2][0]*Wpk[5][12][2])+((Cik[13][0][0]*
          Wpk[5][12][0])+(Cik[13][1][0]*Wpk[5][12][1])));
        Wpk[5][13][1] = ((Cik[13][2][1]*Wpk[5][12][2])+((Cik[13][0][1]*
          Wpk[5][12][0])+(Cik[13][1][1]*Wpk[5][12][1])));
        Wpk[5][13][2] = ((Cik[13][2][2]*Wpk[5][12][2])+((Cik[13][0][2]*
          Wpk[5][12][0])+(Cik[13][1][2]*Wpk[5][12][1])));
        Wpk[5][14][0] = ((Cik[14][2][0]*Wpk[5][13][2])+((Cik[14][0][0]*
          Wpk[5][13][0])+(Cik[14][1][0]*Wpk[5][13][1])));
        Wpk[5][14][1] = ((Cik[14][2][1]*Wpk[5][13][2])+((Cik[14][0][1]*
          Wpk[5][13][0])+(Cik[14][1][1]*Wpk[5][13][1])));
        Wpk[5][14][2] = ((Cik[14][2][2]*Wpk[5][13][2])+((Cik[14][0][2]*
          Wpk[5][13][0])+(Cik[14][1][2]*Wpk[5][13][1])));
        Wpk[5][15][0] = ((Cik[15][2][0]*Wpk[5][14][2])+((Cik[15][0][0]*
          Wpk[5][14][0])+(Cik[15][1][0]*Wpk[5][14][1])));
        Wpk[5][15][1] = ((Cik[15][2][1]*Wpk[5][14][2])+((Cik[15][0][1]*
          Wpk[5][14][0])+(Cik[15][1][1]*Wpk[5][14][1])));
        Wpk[5][15][2] = ((Cik[15][2][2]*Wpk[5][14][2])+((Cik[15][0][2]*
          Wpk[5][14][0])+(Cik[15][1][2]*Wpk[5][14][1])));
        Wpk[5][16][0] = ((Cik[16][2][0]*Wpk[5][15][2])+((Cik[16][0][0]*
          Wpk[5][15][0])+(Cik[16][1][0]*Wpk[5][15][1])));
        Wpk[5][16][1] = ((Cik[16][2][1]*Wpk[5][15][2])+((Cik[16][0][1]*
          Wpk[5][15][0])+(Cik[16][1][1]*Wpk[5][15][1])));
        Wpk[5][16][2] = ((Cik[16][2][2]*Wpk[5][15][2])+((Cik[16][0][2]*
          Wpk[5][15][0])+(Cik[16][1][2]*Wpk[5][15][1])));
        Wpk[5][17][0] = ((Cik[17][2][0]*Wpk[5][16][2])+((Cik[17][0][0]*
          Wpk[5][16][0])+(Cik[17][1][0]*Wpk[5][16][1])));
        Wpk[5][17][1] = ((Cik[17][2][1]*Wpk[5][16][2])+((Cik[17][0][1]*
          Wpk[5][16][0])+(Cik[17][1][1]*Wpk[5][16][1])));
        Wpk[5][17][2] = ((Cik[17][2][2]*Wpk[5][16][2])+((Cik[17][0][2]*
          Wpk[5][16][0])+(Cik[17][1][2]*Wpk[5][16][1])));
        Wpk[5][18][0] = ((Cik[18][2][0]*Wpk[5][17][2])+((Cik[18][0][0]*
          Wpk[5][17][0])+(Cik[18][1][0]*Wpk[5][17][1])));
        Wpk[5][18][1] = ((Cik[18][2][1]*Wpk[5][17][2])+((Cik[18][0][1]*
          Wpk[5][17][0])+(Cik[18][1][1]*Wpk[5][17][1])));
        Wpk[5][18][2] = ((Cik[18][2][2]*Wpk[5][17][2])+((Cik[18][0][2]*
          Wpk[5][17][0])+(Cik[18][1][2]*Wpk[5][17][1])));
        Wpk[5][19][0] = ((Cik[19][2][0]*Wpk[5][18][2])+((Cik[19][0][0]*
          Wpk[5][18][0])+(Cik[19][1][0]*Wpk[5][18][1])));
        Wpk[5][19][1] = ((Cik[19][2][1]*Wpk[5][18][2])+((Cik[19][0][1]*
          Wpk[5][18][0])+(Cik[19][1][1]*Wpk[5][18][1])));
        Wpk[5][19][2] = ((Cik[19][2][2]*Wpk[5][18][2])+((Cik[19][0][2]*
          Wpk[5][18][0])+(Cik[19][1][2]*Wpk[5][18][1])));
        Wpk[5][20][0] = ((Cik[20][2][0]*Wpk[5][19][2])+((Cik[20][0][0]*
          Wpk[5][19][0])+(Cik[20][1][0]*Wpk[5][19][1])));
        Wpk[5][20][1] = ((Cik[20][2][1]*Wpk[5][19][2])+((Cik[20][0][1]*
          Wpk[5][19][0])+(Cik[20][1][1]*Wpk[5][19][1])));
        Wpk[5][20][2] = ((Cik[20][2][2]*Wpk[5][19][2])+((Cik[20][0][2]*
          Wpk[5][19][0])+(Cik[20][1][2]*Wpk[5][19][1])));
        Wpk[5][21][0] = Cik[21][2][0];
        Wpk[5][21][1] = Cik[21][2][1];
        Wpk[5][21][2] = Cik[21][2][2];
        Wpk[5][22][0] = ((Cik[21][2][2]*Cik[22][2][0])+((Cik[21][2][0]*
          Cik[22][0][0])+(Cik[21][2][1]*Cik[22][1][0])));
        Wpk[5][22][1] = ((Cik[21][2][2]*Cik[22][2][1])+((Cik[21][2][0]*
          Cik[22][0][1])+(Cik[21][2][1]*Cik[22][1][1])));
        Wpk[5][22][2] = ((Cik[21][2][2]*Cik[22][2][2])+((Cik[21][2][0]*
          Cik[22][0][2])+(Cik[21][2][1]*Cik[22][1][2])));
        Wpk[5][23][0] = ((Cik[23][2][0]*Wpk[5][22][2])+((Cik[23][0][0]*
          Wpk[5][22][0])+(Cik[23][1][0]*Wpk[5][22][1])));
        Wpk[5][23][1] = ((Cik[23][2][1]*Wpk[5][22][2])+((Cik[23][0][1]*
          Wpk[5][22][0])+(Cik[23][1][1]*Wpk[5][22][1])));
        Wpk[5][23][2] = ((Cik[23][2][2]*Wpk[5][22][2])+((Cik[23][0][2]*
          Wpk[5][22][0])+(Cik[23][1][2]*Wpk[5][22][1])));
        Wpk[5][24][0] = ((Cik[24][2][0]*Wpk[5][23][2])+((Cik[24][0][0]*
          Wpk[5][23][0])+(Cik[24][1][0]*Wpk[5][23][1])));
        Wpk[5][24][1] = ((Cik[24][2][1]*Wpk[5][23][2])+((Cik[24][0][1]*
          Wpk[5][23][0])+(Cik[24][1][1]*Wpk[5][23][1])));
        Wpk[5][24][2] = ((Cik[24][2][2]*Wpk[5][23][2])+((Cik[24][0][2]*
          Wpk[5][23][0])+(Cik[24][1][2]*Wpk[5][23][1])));
        Wpk[5][25][0] = ((Cik[25][2][0]*Wpk[5][24][2])+((Cik[25][0][0]*
          Wpk[5][24][0])+(Cik[25][1][0]*Wpk[5][24][1])));
        Wpk[5][25][1] = ((Cik[25][2][1]*Wpk[5][24][2])+((Cik[25][0][1]*
          Wpk[5][24][0])+(Cik[25][1][1]*Wpk[5][24][1])));
        Wpk[5][25][2] = ((Cik[25][2][2]*Wpk[5][24][2])+((Cik[25][0][2]*
          Wpk[5][24][0])+(Cik[25][1][2]*Wpk[5][24][1])));
        Wpk[5][26][0] = ((Cik[26][2][0]*Wpk[5][25][2])+((Cik[26][0][0]*
          Wpk[5][25][0])+(Cik[26][1][0]*Wpk[5][25][1])));
        Wpk[5][26][1] = ((Cik[26][2][1]*Wpk[5][25][2])+((Cik[26][0][1]*
          Wpk[5][25][0])+(Cik[26][1][1]*Wpk[5][25][1])));
        Wpk[5][26][2] = ((Cik[26][2][2]*Wpk[5][25][2])+((Cik[26][0][2]*
          Wpk[5][25][0])+(Cik[26][1][2]*Wpk[5][25][1])));
        Wpk[5][27][0] = ((Cik[27][2][0]*Wpk[5][26][2])+((Cik[27][0][0]*
          Wpk[5][26][0])+(Cik[27][1][0]*Wpk[5][26][1])));
        Wpk[5][27][1] = ((Cik[27][2][1]*Wpk[5][26][2])+((Cik[27][0][1]*
          Wpk[5][26][0])+(Cik[27][1][1]*Wpk[5][26][1])));
        Wpk[5][27][2] = ((Cik[27][2][2]*Wpk[5][26][2])+((Cik[27][0][2]*
          Wpk[5][26][0])+(Cik[27][1][2]*Wpk[5][26][1])));
        Wpk[5][28][0] = ((Cik[28][2][0]*Wpk[5][27][2])+((Cik[28][0][0]*
          Wpk[5][27][0])+(Cik[28][1][0]*Wpk[5][27][1])));
        Wpk[5][28][1] = ((Cik[28][2][1]*Wpk[5][27][2])+((Cik[28][0][1]*
          Wpk[5][27][0])+(Cik[28][1][1]*Wpk[5][27][1])));
        Wpk[5][28][2] = ((Cik[28][2][2]*Wpk[5][27][2])+((Cik[28][0][2]*
          Wpk[5][27][0])+(Cik[28][1][2]*Wpk[5][27][1])));
        Wpk[5][29][0] = ((Cik[29][2][0]*Wpk[5][28][2])+((Cik[29][0][0]*
          Wpk[5][28][0])+(Cik[29][1][0]*Wpk[5][28][1])));
        Wpk[5][29][1] = ((Cik[29][2][1]*Wpk[5][28][2])+((Cik[29][0][1]*
          Wpk[5][28][0])+(Cik[29][1][1]*Wpk[5][28][1])));
        Wpk[5][29][2] = ((Cik[29][2][2]*Wpk[5][28][2])+((Cik[29][0][2]*
          Wpk[5][28][0])+(Cik[29][1][2]*Wpk[5][28][1])));
        Wpk[5][30][0] = ((Cik[30][2][0]*Wpk[5][29][2])+((Cik[30][0][0]*
          Wpk[5][29][0])+(Cik[30][1][0]*Wpk[5][29][1])));
        Wpk[5][30][1] = ((Cik[30][2][1]*Wpk[5][29][2])+((Cik[30][0][1]*
          Wpk[5][29][0])+(Cik[30][1][1]*Wpk[5][29][1])));
        Wpk[5][30][2] = ((Cik[30][2][2]*Wpk[5][29][2])+((Cik[30][0][2]*
          Wpk[5][29][0])+(Cik[30][1][2]*Wpk[5][29][1])));
        Wpk[5][31][0] = ((Cik[31][2][0]*Wpk[5][30][2])+((Cik[31][0][0]*
          Wpk[5][30][0])+(Cik[31][1][0]*Wpk[5][30][1])));
        Wpk[5][31][1] = ((Cik[31][2][1]*Wpk[5][30][2])+((Cik[31][0][1]*
          Wpk[5][30][0])+(Cik[31][1][1]*Wpk[5][30][1])));
        Wpk[5][31][2] = ((Cik[31][2][2]*Wpk[5][30][2])+((Cik[31][0][2]*
          Wpk[5][30][0])+(Cik[31][1][2]*Wpk[5][30][1])));
        Wpk[5][32][0] = ((Cik[32][2][0]*Wpk[5][31][2])+((Cik[32][0][0]*
          Wpk[5][31][0])+(Cik[32][1][0]*Wpk[5][31][1])));
        Wpk[5][32][1] = ((Cik[32][2][1]*Wpk[5][31][2])+((Cik[32][0][1]*
          Wpk[5][31][0])+(Cik[32][1][1]*Wpk[5][31][1])));
        Wpk[5][32][2] = ((Cik[32][2][2]*Wpk[5][31][2])+((Cik[32][0][2]*
          Wpk[5][31][0])+(Cik[32][1][2]*Wpk[5][31][1])));
        Wpk[6][6][0] = pin[6][0];
        Wpk[6][6][1] = pin[6][1];
        Wpk[6][6][2] = pin[6][2];
        Wpk[6][7][0] = ((Cik[7][2][0]*pin[6][2])+((Cik[7][0][0]*pin[6][0])+(
          Cik[7][1][0]*pin[6][1])));
        Wpk[6][7][1] = ((Cik[7][2][1]*pin[6][2])+((Cik[7][0][1]*pin[6][0])+(
          Cik[7][1][1]*pin[6][1])));
        Wpk[6][7][2] = ((Cik[7][2][2]*pin[6][2])+((Cik[7][0][2]*pin[6][0])+(
          Cik[7][1][2]*pin[6][1])));
        Wpk[6][8][0] = ((Cik[8][2][0]*Wpk[6][7][2])+((Cik[8][0][0]*Wpk[6][7][0])
          +(Cik[8][1][0]*Wpk[6][7][1])));
        Wpk[6][8][1] = ((Cik[8][2][1]*Wpk[6][7][2])+((Cik[8][0][1]*Wpk[6][7][0])
          +(Cik[8][1][1]*Wpk[6][7][1])));
        Wpk[6][8][2] = ((Cik[8][2][2]*Wpk[6][7][2])+((Cik[8][0][2]*Wpk[6][7][0])
          +(Cik[8][1][2]*Wpk[6][7][1])));
        Wpk[7][7][0] = pin[7][0];
        Wpk[7][7][1] = pin[7][1];
        Wpk[7][7][2] = pin[7][2];
        Wpk[7][8][0] = ((Cik[8][2][0]*pin[7][2])+((Cik[8][0][0]*pin[7][0])+(
          Cik[8][1][0]*pin[7][1])));
        Wpk[7][8][1] = ((Cik[8][2][1]*pin[7][2])+((Cik[8][0][1]*pin[7][0])+(
          Cik[8][1][1]*pin[7][1])));
        Wpk[7][8][2] = ((Cik[8][2][2]*pin[7][2])+((Cik[8][0][2]*pin[7][0])+(
          Cik[8][1][2]*pin[7][1])));
        Wpk[8][8][0] = pin[8][0];
        Wpk[8][8][1] = pin[8][1];
        Wpk[8][8][2] = pin[8][2];
        Wpk[9][9][0] = pin[9][0];
        Wpk[9][9][1] = pin[9][1];
        Wpk[9][9][2] = pin[9][2];
        Wpk[9][10][0] = ((Cik[10][2][0]*pin[9][2])+((Cik[10][0][0]*pin[9][0])+(
          Cik[10][1][0]*pin[9][1])));
        Wpk[9][10][1] = ((Cik[10][2][1]*pin[9][2])+((Cik[10][0][1]*pin[9][0])+(
          Cik[10][1][1]*pin[9][1])));
        Wpk[9][10][2] = ((Cik[10][2][2]*pin[9][2])+((Cik[10][0][2]*pin[9][0])+(
          Cik[10][1][2]*pin[9][1])));
        Wpk[9][11][0] = ((Cik[11][2][0]*Wpk[9][10][2])+((Cik[11][0][0]*
          Wpk[9][10][0])+(Cik[11][1][0]*Wpk[9][10][1])));
        Wpk[9][11][1] = ((Cik[11][2][1]*Wpk[9][10][2])+((Cik[11][0][1]*
          Wpk[9][10][0])+(Cik[11][1][1]*Wpk[9][10][1])));
        Wpk[9][11][2] = ((Cik[11][2][2]*Wpk[9][10][2])+((Cik[11][0][2]*
          Wpk[9][10][0])+(Cik[11][1][2]*Wpk[9][10][1])));
        Wpk[9][12][0] = ((Cik[12][2][0]*Wpk[9][11][2])+((Cik[12][0][0]*
          Wpk[9][11][0])+(Cik[12][1][0]*Wpk[9][11][1])));
        Wpk[9][12][1] = ((Cik[12][2][1]*Wpk[9][11][2])+((Cik[12][0][1]*
          Wpk[9][11][0])+(Cik[12][1][1]*Wpk[9][11][1])));
        Wpk[9][12][2] = ((Cik[12][2][2]*Wpk[9][11][2])+((Cik[12][0][2]*
          Wpk[9][11][0])+(Cik[12][1][2]*Wpk[9][11][1])));
        Wpk[9][13][0] = ((Cik[13][2][0]*Wpk[9][12][2])+((Cik[13][0][0]*
          Wpk[9][12][0])+(Cik[13][1][0]*Wpk[9][12][1])));
        Wpk[9][13][1] = ((Cik[13][2][1]*Wpk[9][12][2])+((Cik[13][0][1]*
          Wpk[9][12][0])+(Cik[13][1][1]*Wpk[9][12][1])));
        Wpk[9][13][2] = ((Cik[13][2][2]*Wpk[9][12][2])+((Cik[13][0][2]*
          Wpk[9][12][0])+(Cik[13][1][2]*Wpk[9][12][1])));
        Wpk[9][14][0] = ((Cik[14][2][0]*Wpk[9][13][2])+((Cik[14][0][0]*
          Wpk[9][13][0])+(Cik[14][1][0]*Wpk[9][13][1])));
        Wpk[9][14][1] = ((Cik[14][2][1]*Wpk[9][13][2])+((Cik[14][0][1]*
          Wpk[9][13][0])+(Cik[14][1][1]*Wpk[9][13][1])));
        Wpk[9][14][2] = ((Cik[14][2][2]*Wpk[9][13][2])+((Cik[14][0][2]*
          Wpk[9][13][0])+(Cik[14][1][2]*Wpk[9][13][1])));
        Wpk[9][15][0] = ((Cik[15][2][0]*Wpk[9][14][2])+((Cik[15][0][0]*
          Wpk[9][14][0])+(Cik[15][1][0]*Wpk[9][14][1])));
        Wpk[9][15][1] = ((Cik[15][2][1]*Wpk[9][14][2])+((Cik[15][0][1]*
          Wpk[9][14][0])+(Cik[15][1][1]*Wpk[9][14][1])));
        Wpk[9][15][2] = ((Cik[15][2][2]*Wpk[9][14][2])+((Cik[15][0][2]*
          Wpk[9][14][0])+(Cik[15][1][2]*Wpk[9][14][1])));
        Wpk[9][16][0] = ((Cik[16][2][0]*Wpk[9][15][2])+((Cik[16][0][0]*
          Wpk[9][15][0])+(Cik[16][1][0]*Wpk[9][15][1])));
        Wpk[9][16][1] = ((Cik[16][2][1]*Wpk[9][15][2])+((Cik[16][0][1]*
          Wpk[9][15][0])+(Cik[16][1][1]*Wpk[9][15][1])));
        Wpk[9][16][2] = ((Cik[16][2][2]*Wpk[9][15][2])+((Cik[16][0][2]*
          Wpk[9][15][0])+(Cik[16][1][2]*Wpk[9][15][1])));
        Wpk[9][17][0] = ((Cik[17][2][0]*Wpk[9][16][2])+((Cik[17][0][0]*
          Wpk[9][16][0])+(Cik[17][1][0]*Wpk[9][16][1])));
        Wpk[9][17][1] = ((Cik[17][2][1]*Wpk[9][16][2])+((Cik[17][0][1]*
          Wpk[9][16][0])+(Cik[17][1][1]*Wpk[9][16][1])));
        Wpk[9][17][2] = ((Cik[17][2][2]*Wpk[9][16][2])+((Cik[17][0][2]*
          Wpk[9][16][0])+(Cik[17][1][2]*Wpk[9][16][1])));
        Wpk[9][18][0] = ((Cik[18][2][0]*Wpk[9][17][2])+((Cik[18][0][0]*
          Wpk[9][17][0])+(Cik[18][1][0]*Wpk[9][17][1])));
        Wpk[9][18][1] = ((Cik[18][2][1]*Wpk[9][17][2])+((Cik[18][0][1]*
          Wpk[9][17][0])+(Cik[18][1][1]*Wpk[9][17][1])));
        Wpk[9][18][2] = ((Cik[18][2][2]*Wpk[9][17][2])+((Cik[18][0][2]*
          Wpk[9][17][0])+(Cik[18][1][2]*Wpk[9][17][1])));
        Wpk[9][19][0] = ((Cik[19][2][0]*Wpk[9][18][2])+((Cik[19][0][0]*
          Wpk[9][18][0])+(Cik[19][1][0]*Wpk[9][18][1])));
        Wpk[9][19][1] = ((Cik[19][2][1]*Wpk[9][18][2])+((Cik[19][0][1]*
          Wpk[9][18][0])+(Cik[19][1][1]*Wpk[9][18][1])));
        Wpk[9][19][2] = ((Cik[19][2][2]*Wpk[9][18][2])+((Cik[19][0][2]*
          Wpk[9][18][0])+(Cik[19][1][2]*Wpk[9][18][1])));
        Wpk[9][20][0] = ((Cik[20][2][0]*Wpk[9][19][2])+((Cik[20][0][0]*
          Wpk[9][19][0])+(Cik[20][1][0]*Wpk[9][19][1])));
        Wpk[9][20][1] = ((Cik[20][2][1]*Wpk[9][19][2])+((Cik[20][0][1]*
          Wpk[9][19][0])+(Cik[20][1][1]*Wpk[9][19][1])));
        Wpk[9][20][2] = ((Cik[20][2][2]*Wpk[9][19][2])+((Cik[20][0][2]*
          Wpk[9][19][0])+(Cik[20][1][2]*Wpk[9][19][1])));
        Wpk[10][10][0] = pin[10][0];
        Wpk[10][10][1] = pin[10][1];
        Wpk[10][10][2] = pin[10][2];
        Wpk[10][11][0] = ((Cik[11][2][0]*pin[10][2])+((Cik[11][0][0]*pin[10][0])
          +(Cik[11][1][0]*pin[10][1])));
        Wpk[10][11][1] = ((Cik[11][2][1]*pin[10][2])+((Cik[11][0][1]*pin[10][0])
          +(Cik[11][1][1]*pin[10][1])));
        Wpk[10][11][2] = ((Cik[11][2][2]*pin[10][2])+((Cik[11][0][2]*pin[10][0])
          +(Cik[11][1][2]*pin[10][1])));
        Wpk[10][12][0] = ((Cik[12][2][0]*Wpk[10][11][2])+((Cik[12][0][0]*
          Wpk[10][11][0])+(Cik[12][1][0]*Wpk[10][11][1])));
        Wpk[10][12][1] = ((Cik[12][2][1]*Wpk[10][11][2])+((Cik[12][0][1]*
          Wpk[10][11][0])+(Cik[12][1][1]*Wpk[10][11][1])));
        Wpk[10][12][2] = ((Cik[12][2][2]*Wpk[10][11][2])+((Cik[12][0][2]*
          Wpk[10][11][0])+(Cik[12][1][2]*Wpk[10][11][1])));
        Wpk[10][13][0] = ((Cik[13][2][0]*Wpk[10][12][2])+((Cik[13][0][0]*
          Wpk[10][12][0])+(Cik[13][1][0]*Wpk[10][12][1])));
        Wpk[10][13][1] = ((Cik[13][2][1]*Wpk[10][12][2])+((Cik[13][0][1]*
          Wpk[10][12][0])+(Cik[13][1][1]*Wpk[10][12][1])));
        Wpk[10][13][2] = ((Cik[13][2][2]*Wpk[10][12][2])+((Cik[13][0][2]*
          Wpk[10][12][0])+(Cik[13][1][2]*Wpk[10][12][1])));
        Wpk[10][14][0] = ((Cik[14][2][0]*Wpk[10][13][2])+((Cik[14][0][0]*
          Wpk[10][13][0])+(Cik[14][1][0]*Wpk[10][13][1])));
        Wpk[10][14][1] = ((Cik[14][2][1]*Wpk[10][13][2])+((Cik[14][0][1]*
          Wpk[10][13][0])+(Cik[14][1][1]*Wpk[10][13][1])));
        Wpk[10][14][2] = ((Cik[14][2][2]*Wpk[10][13][2])+((Cik[14][0][2]*
          Wpk[10][13][0])+(Cik[14][1][2]*Wpk[10][13][1])));
        Wpk[10][15][0] = ((Cik[15][2][0]*Wpk[10][14][2])+((Cik[15][0][0]*
          Wpk[10][14][0])+(Cik[15][1][0]*Wpk[10][14][1])));
        Wpk[10][15][1] = ((Cik[15][2][1]*Wpk[10][14][2])+((Cik[15][0][1]*
          Wpk[10][14][0])+(Cik[15][1][1]*Wpk[10][14][1])));
        Wpk[10][15][2] = ((Cik[15][2][2]*Wpk[10][14][2])+((Cik[15][0][2]*
          Wpk[10][14][0])+(Cik[15][1][2]*Wpk[10][14][1])));
        Wpk[10][16][0] = ((Cik[16][2][0]*Wpk[10][15][2])+((Cik[16][0][0]*
          Wpk[10][15][0])+(Cik[16][1][0]*Wpk[10][15][1])));
        Wpk[10][16][1] = ((Cik[16][2][1]*Wpk[10][15][2])+((Cik[16][0][1]*
          Wpk[10][15][0])+(Cik[16][1][1]*Wpk[10][15][1])));
        Wpk[10][16][2] = ((Cik[16][2][2]*Wpk[10][15][2])+((Cik[16][0][2]*
          Wpk[10][15][0])+(Cik[16][1][2]*Wpk[10][15][1])));
        Wpk[10][17][0] = ((Cik[17][2][0]*Wpk[10][16][2])+((Cik[17][0][0]*
          Wpk[10][16][0])+(Cik[17][1][0]*Wpk[10][16][1])));
        Wpk[10][17][1] = ((Cik[17][2][1]*Wpk[10][16][2])+((Cik[17][0][1]*
          Wpk[10][16][0])+(Cik[17][1][1]*Wpk[10][16][1])));
        Wpk[10][17][2] = ((Cik[17][2][2]*Wpk[10][16][2])+((Cik[17][0][2]*
          Wpk[10][16][0])+(Cik[17][1][2]*Wpk[10][16][1])));
        Wpk[10][18][0] = ((Cik[18][2][0]*Wpk[10][17][2])+((Cik[18][0][0]*
          Wpk[10][17][0])+(Cik[18][1][0]*Wpk[10][17][1])));
        Wpk[10][18][1] = ((Cik[18][2][1]*Wpk[10][17][2])+((Cik[18][0][1]*
          Wpk[10][17][0])+(Cik[18][1][1]*Wpk[10][17][1])));
        Wpk[10][18][2] = ((Cik[18][2][2]*Wpk[10][17][2])+((Cik[18][0][2]*
          Wpk[10][17][0])+(Cik[18][1][2]*Wpk[10][17][1])));
        Wpk[10][19][0] = ((Cik[19][2][0]*Wpk[10][18][2])+((Cik[19][0][0]*
          Wpk[10][18][0])+(Cik[19][1][0]*Wpk[10][18][1])));
        Wpk[10][19][1] = ((Cik[19][2][1]*Wpk[10][18][2])+((Cik[19][0][1]*
          Wpk[10][18][0])+(Cik[19][1][1]*Wpk[10][18][1])));
        Wpk[10][19][2] = ((Cik[19][2][2]*Wpk[10][18][2])+((Cik[19][0][2]*
          Wpk[10][18][0])+(Cik[19][1][2]*Wpk[10][18][1])));
        Wpk[10][20][0] = ((Cik[20][2][0]*Wpk[10][19][2])+((Cik[20][0][0]*
          Wpk[10][19][0])+(Cik[20][1][0]*Wpk[10][19][1])));
        Wpk[10][20][1] = ((Cik[20][2][1]*Wpk[10][19][2])+((Cik[20][0][1]*
          Wpk[10][19][0])+(Cik[20][1][1]*Wpk[10][19][1])));
        Wpk[10][20][2] = ((Cik[20][2][2]*Wpk[10][19][2])+((Cik[20][0][2]*
          Wpk[10][19][0])+(Cik[20][1][2]*Wpk[10][19][1])));
        Wpk[11][11][0] = pin[11][0];
        Wpk[11][11][1] = pin[11][1];
        Wpk[11][11][2] = pin[11][2];
        Wpk[11][12][0] = ((Cik[12][2][0]*pin[11][2])+((Cik[12][0][0]*pin[11][0])
          +(Cik[12][1][0]*pin[11][1])));
        Wpk[11][12][1] = ((Cik[12][2][1]*pin[11][2])+((Cik[12][0][1]*pin[11][0])
          +(Cik[12][1][1]*pin[11][1])));
        Wpk[11][12][2] = ((Cik[12][2][2]*pin[11][2])+((Cik[12][0][2]*pin[11][0])
          +(Cik[12][1][2]*pin[11][1])));
        Wpk[11][13][0] = ((Cik[13][2][0]*Wpk[11][12][2])+((Cik[13][0][0]*
          Wpk[11][12][0])+(Cik[13][1][0]*Wpk[11][12][1])));
        Wpk[11][13][1] = ((Cik[13][2][1]*Wpk[11][12][2])+((Cik[13][0][1]*
          Wpk[11][12][0])+(Cik[13][1][1]*Wpk[11][12][1])));
        Wpk[11][13][2] = ((Cik[13][2][2]*Wpk[11][12][2])+((Cik[13][0][2]*
          Wpk[11][12][0])+(Cik[13][1][2]*Wpk[11][12][1])));
        Wpk[11][14][0] = ((Cik[14][2][0]*Wpk[11][13][2])+((Cik[14][0][0]*
          Wpk[11][13][0])+(Cik[14][1][0]*Wpk[11][13][1])));
        Wpk[11][14][1] = ((Cik[14][2][1]*Wpk[11][13][2])+((Cik[14][0][1]*
          Wpk[11][13][0])+(Cik[14][1][1]*Wpk[11][13][1])));
        Wpk[11][14][2] = ((Cik[14][2][2]*Wpk[11][13][2])+((Cik[14][0][2]*
          Wpk[11][13][0])+(Cik[14][1][2]*Wpk[11][13][1])));
        Wpk[11][15][0] = ((Cik[15][2][0]*Wpk[11][14][2])+((Cik[15][0][0]*
          Wpk[11][14][0])+(Cik[15][1][0]*Wpk[11][14][1])));
        Wpk[11][15][1] = ((Cik[15][2][1]*Wpk[11][14][2])+((Cik[15][0][1]*
          Wpk[11][14][0])+(Cik[15][1][1]*Wpk[11][14][1])));
        Wpk[11][15][2] = ((Cik[15][2][2]*Wpk[11][14][2])+((Cik[15][0][2]*
          Wpk[11][14][0])+(Cik[15][1][2]*Wpk[11][14][1])));
        Wpk[11][16][0] = ((Cik[16][2][0]*Wpk[11][15][2])+((Cik[16][0][0]*
          Wpk[11][15][0])+(Cik[16][1][0]*Wpk[11][15][1])));
        Wpk[11][16][1] = ((Cik[16][2][1]*Wpk[11][15][2])+((Cik[16][0][1]*
          Wpk[11][15][0])+(Cik[16][1][1]*Wpk[11][15][1])));
        Wpk[11][16][2] = ((Cik[16][2][2]*Wpk[11][15][2])+((Cik[16][0][2]*
          Wpk[11][15][0])+(Cik[16][1][2]*Wpk[11][15][1])));
        Wpk[11][17][0] = ((Cik[17][2][0]*Wpk[11][16][2])+((Cik[17][0][0]*
          Wpk[11][16][0])+(Cik[17][1][0]*Wpk[11][16][1])));
        Wpk[11][17][1] = ((Cik[17][2][1]*Wpk[11][16][2])+((Cik[17][0][1]*
          Wpk[11][16][0])+(Cik[17][1][1]*Wpk[11][16][1])));
        Wpk[11][17][2] = ((Cik[17][2][2]*Wpk[11][16][2])+((Cik[17][0][2]*
          Wpk[11][16][0])+(Cik[17][1][2]*Wpk[11][16][1])));
        Wpk[11][18][0] = ((Cik[18][2][0]*Wpk[11][17][2])+((Cik[18][0][0]*
          Wpk[11][17][0])+(Cik[18][1][0]*Wpk[11][17][1])));
        Wpk[11][18][1] = ((Cik[18][2][1]*Wpk[11][17][2])+((Cik[18][0][1]*
          Wpk[11][17][0])+(Cik[18][1][1]*Wpk[11][17][1])));
        Wpk[11][18][2] = ((Cik[18][2][2]*Wpk[11][17][2])+((Cik[18][0][2]*
          Wpk[11][17][0])+(Cik[18][1][2]*Wpk[11][17][1])));
        Wpk[11][19][0] = ((Cik[19][2][0]*Wpk[11][18][2])+((Cik[19][0][0]*
          Wpk[11][18][0])+(Cik[19][1][0]*Wpk[11][18][1])));
        Wpk[11][19][1] = ((Cik[19][2][1]*Wpk[11][18][2])+((Cik[19][0][1]*
          Wpk[11][18][0])+(Cik[19][1][1]*Wpk[11][18][1])));
        Wpk[11][19][2] = ((Cik[19][2][2]*Wpk[11][18][2])+((Cik[19][0][2]*
          Wpk[11][18][0])+(Cik[19][1][2]*Wpk[11][18][1])));
        Wpk[11][20][0] = ((Cik[20][2][0]*Wpk[11][19][2])+((Cik[20][0][0]*
          Wpk[11][19][0])+(Cik[20][1][0]*Wpk[11][19][1])));
        Wpk[11][20][1] = ((Cik[20][2][1]*Wpk[11][19][2])+((Cik[20][0][1]*
          Wpk[11][19][0])+(Cik[20][1][1]*Wpk[11][19][1])));
        Wpk[11][20][2] = ((Cik[20][2][2]*Wpk[11][19][2])+((Cik[20][0][2]*
          Wpk[11][19][0])+(Cik[20][1][2]*Wpk[11][19][1])));
        Wpk[12][12][0] = pin[12][0];
        Wpk[12][12][1] = pin[12][1];
        Wpk[12][12][2] = pin[12][2];
        Wpk[12][13][0] = ((Cik[13][2][0]*pin[12][2])+((Cik[13][0][0]*pin[12][0])
          +(Cik[13][1][0]*pin[12][1])));
        Wpk[12][13][1] = ((Cik[13][2][1]*pin[12][2])+((Cik[13][0][1]*pin[12][0])
          +(Cik[13][1][1]*pin[12][1])));
        Wpk[12][13][2] = ((Cik[13][2][2]*pin[12][2])+((Cik[13][0][2]*pin[12][0])
          +(Cik[13][1][2]*pin[12][1])));
        Wpk[12][14][0] = ((Cik[14][2][0]*Wpk[12][13][2])+((Cik[14][0][0]*
          Wpk[12][13][0])+(Cik[14][1][0]*Wpk[12][13][1])));
        Wpk[12][14][1] = ((Cik[14][2][1]*Wpk[12][13][2])+((Cik[14][0][1]*
          Wpk[12][13][0])+(Cik[14][1][1]*Wpk[12][13][1])));
        Wpk[12][14][2] = ((Cik[14][2][2]*Wpk[12][13][2])+((Cik[14][0][2]*
          Wpk[12][13][0])+(Cik[14][1][2]*Wpk[12][13][1])));
        Wpk[12][15][0] = ((Cik[15][2][0]*Wpk[12][14][2])+((Cik[15][0][0]*
          Wpk[12][14][0])+(Cik[15][1][0]*Wpk[12][14][1])));
        Wpk[12][15][1] = ((Cik[15][2][1]*Wpk[12][14][2])+((Cik[15][0][1]*
          Wpk[12][14][0])+(Cik[15][1][1]*Wpk[12][14][1])));
        Wpk[12][15][2] = ((Cik[15][2][2]*Wpk[12][14][2])+((Cik[15][0][2]*
          Wpk[12][14][0])+(Cik[15][1][2]*Wpk[12][14][1])));
        Wpk[12][16][0] = ((Cik[16][2][0]*Wpk[12][15][2])+((Cik[16][0][0]*
          Wpk[12][15][0])+(Cik[16][1][0]*Wpk[12][15][1])));
        Wpk[12][16][1] = ((Cik[16][2][1]*Wpk[12][15][2])+((Cik[16][0][1]*
          Wpk[12][15][0])+(Cik[16][1][1]*Wpk[12][15][1])));
        Wpk[12][16][2] = ((Cik[16][2][2]*Wpk[12][15][2])+((Cik[16][0][2]*
          Wpk[12][15][0])+(Cik[16][1][2]*Wpk[12][15][1])));
        Wpk[12][17][0] = ((Cik[17][2][0]*Wpk[12][16][2])+((Cik[17][0][0]*
          Wpk[12][16][0])+(Cik[17][1][0]*Wpk[12][16][1])));
        Wpk[12][17][1] = ((Cik[17][2][1]*Wpk[12][16][2])+((Cik[17][0][1]*
          Wpk[12][16][0])+(Cik[17][1][1]*Wpk[12][16][1])));
        Wpk[12][17][2] = ((Cik[17][2][2]*Wpk[12][16][2])+((Cik[17][0][2]*
          Wpk[12][16][0])+(Cik[17][1][2]*Wpk[12][16][1])));
        Wpk[12][18][0] = ((Cik[18][2][0]*Wpk[12][17][2])+((Cik[18][0][0]*
          Wpk[12][17][0])+(Cik[18][1][0]*Wpk[12][17][1])));
        Wpk[12][18][1] = ((Cik[18][2][1]*Wpk[12][17][2])+((Cik[18][0][1]*
          Wpk[12][17][0])+(Cik[18][1][1]*Wpk[12][17][1])));
        Wpk[12][18][2] = ((Cik[18][2][2]*Wpk[12][17][2])+((Cik[18][0][2]*
          Wpk[12][17][0])+(Cik[18][1][2]*Wpk[12][17][1])));
        Wpk[12][19][0] = ((Cik[19][2][0]*Wpk[12][18][2])+((Cik[19][0][0]*
          Wpk[12][18][0])+(Cik[19][1][0]*Wpk[12][18][1])));
        Wpk[12][19][1] = ((Cik[19][2][1]*Wpk[12][18][2])+((Cik[19][0][1]*
          Wpk[12][18][0])+(Cik[19][1][1]*Wpk[12][18][1])));
        Wpk[12][19][2] = ((Cik[19][2][2]*Wpk[12][18][2])+((Cik[19][0][2]*
          Wpk[12][18][0])+(Cik[19][1][2]*Wpk[12][18][1])));
        Wpk[12][20][0] = ((Cik[20][2][0]*Wpk[12][19][2])+((Cik[20][0][0]*
          Wpk[12][19][0])+(Cik[20][1][0]*Wpk[12][19][1])));
        Wpk[12][20][1] = ((Cik[20][2][1]*Wpk[12][19][2])+((Cik[20][0][1]*
          Wpk[12][19][0])+(Cik[20][1][1]*Wpk[12][19][1])));
        Wpk[12][20][2] = ((Cik[20][2][2]*Wpk[12][19][2])+((Cik[20][0][2]*
          Wpk[12][19][0])+(Cik[20][1][2]*Wpk[12][19][1])));
        Wpk[13][13][0] = pin[13][0];
        Wpk[13][13][1] = pin[13][1];
        Wpk[13][13][2] = pin[13][2];
        Wpk[13][14][0] = ((Cik[14][2][0]*pin[13][2])+((Cik[14][0][0]*pin[13][0])
          +(Cik[14][1][0]*pin[13][1])));
        Wpk[13][14][1] = ((Cik[14][2][1]*pin[13][2])+((Cik[14][0][1]*pin[13][0])
          +(Cik[14][1][1]*pin[13][1])));
        Wpk[13][14][2] = ((Cik[14][2][2]*pin[13][2])+((Cik[14][0][2]*pin[13][0])
          +(Cik[14][1][2]*pin[13][1])));
        Wpk[13][15][0] = ((Cik[15][2][0]*Wpk[13][14][2])+((Cik[15][0][0]*
          Wpk[13][14][0])+(Cik[15][1][0]*Wpk[13][14][1])));
        Wpk[13][15][1] = ((Cik[15][2][1]*Wpk[13][14][2])+((Cik[15][0][1]*
          Wpk[13][14][0])+(Cik[15][1][1]*Wpk[13][14][1])));
        Wpk[13][15][2] = ((Cik[15][2][2]*Wpk[13][14][2])+((Cik[15][0][2]*
          Wpk[13][14][0])+(Cik[15][1][2]*Wpk[13][14][1])));
        Wpk[13][16][0] = ((Cik[16][2][0]*Wpk[13][15][2])+((Cik[16][0][0]*
          Wpk[13][15][0])+(Cik[16][1][0]*Wpk[13][15][1])));
        Wpk[13][16][1] = ((Cik[16][2][1]*Wpk[13][15][2])+((Cik[16][0][1]*
          Wpk[13][15][0])+(Cik[16][1][1]*Wpk[13][15][1])));
        Wpk[13][16][2] = ((Cik[16][2][2]*Wpk[13][15][2])+((Cik[16][0][2]*
          Wpk[13][15][0])+(Cik[16][1][2]*Wpk[13][15][1])));
        Wpk[13][17][0] = ((Cik[17][2][0]*Wpk[13][16][2])+((Cik[17][0][0]*
          Wpk[13][16][0])+(Cik[17][1][0]*Wpk[13][16][1])));
        Wpk[13][17][1] = ((Cik[17][2][1]*Wpk[13][16][2])+((Cik[17][0][1]*
          Wpk[13][16][0])+(Cik[17][1][1]*Wpk[13][16][1])));
        Wpk[13][17][2] = ((Cik[17][2][2]*Wpk[13][16][2])+((Cik[17][0][2]*
          Wpk[13][16][0])+(Cik[17][1][2]*Wpk[13][16][1])));
        Wpk[13][18][0] = ((Cik[18][2][0]*Wpk[13][17][2])+((Cik[18][0][0]*
          Wpk[13][17][0])+(Cik[18][1][0]*Wpk[13][17][1])));
        Wpk[13][18][1] = ((Cik[18][2][1]*Wpk[13][17][2])+((Cik[18][0][1]*
          Wpk[13][17][0])+(Cik[18][1][1]*Wpk[13][17][1])));
        Wpk[13][18][2] = ((Cik[18][2][2]*Wpk[13][17][2])+((Cik[18][0][2]*
          Wpk[13][17][0])+(Cik[18][1][2]*Wpk[13][17][1])));
        Wpk[13][19][0] = ((Cik[19][2][0]*Wpk[13][18][2])+((Cik[19][0][0]*
          Wpk[13][18][0])+(Cik[19][1][0]*Wpk[13][18][1])));
        Wpk[13][19][1] = ((Cik[19][2][1]*Wpk[13][18][2])+((Cik[19][0][1]*
          Wpk[13][18][0])+(Cik[19][1][1]*Wpk[13][18][1])));
        Wpk[13][19][2] = ((Cik[19][2][2]*Wpk[13][18][2])+((Cik[19][0][2]*
          Wpk[13][18][0])+(Cik[19][1][2]*Wpk[13][18][1])));
        Wpk[13][20][0] = ((Cik[20][2][0]*Wpk[13][19][2])+((Cik[20][0][0]*
          Wpk[13][19][0])+(Cik[20][1][0]*Wpk[13][19][1])));
        Wpk[13][20][1] = ((Cik[20][2][1]*Wpk[13][19][2])+((Cik[20][0][1]*
          Wpk[13][19][0])+(Cik[20][1][1]*Wpk[13][19][1])));
        Wpk[13][20][2] = ((Cik[20][2][2]*Wpk[13][19][2])+((Cik[20][0][2]*
          Wpk[13][19][0])+(Cik[20][1][2]*Wpk[13][19][1])));
        Wpk[14][14][0] = pin[14][0];
        Wpk[14][14][1] = pin[14][1];
        Wpk[14][14][2] = pin[14][2];
        Wpk[14][15][0] = ((Cik[15][2][0]*pin[14][2])+((Cik[15][0][0]*pin[14][0])
          +(Cik[15][1][0]*pin[14][1])));
        Wpk[14][15][1] = ((Cik[15][2][1]*pin[14][2])+((Cik[15][0][1]*pin[14][0])
          +(Cik[15][1][1]*pin[14][1])));
        Wpk[14][15][2] = ((Cik[15][2][2]*pin[14][2])+((Cik[15][0][2]*pin[14][0])
          +(Cik[15][1][2]*pin[14][1])));
        Wpk[14][16][0] = ((Cik[16][2][0]*Wpk[14][15][2])+((Cik[16][0][0]*
          Wpk[14][15][0])+(Cik[16][1][0]*Wpk[14][15][1])));
        Wpk[14][16][1] = ((Cik[16][2][1]*Wpk[14][15][2])+((Cik[16][0][1]*
          Wpk[14][15][0])+(Cik[16][1][1]*Wpk[14][15][1])));
        Wpk[14][16][2] = ((Cik[16][2][2]*Wpk[14][15][2])+((Cik[16][0][2]*
          Wpk[14][15][0])+(Cik[16][1][2]*Wpk[14][15][1])));
        Wpk[14][17][0] = ((Cik[17][2][0]*Wpk[14][16][2])+((Cik[17][0][0]*
          Wpk[14][16][0])+(Cik[17][1][0]*Wpk[14][16][1])));
        Wpk[14][17][1] = ((Cik[17][2][1]*Wpk[14][16][2])+((Cik[17][0][1]*
          Wpk[14][16][0])+(Cik[17][1][1]*Wpk[14][16][1])));
        Wpk[14][17][2] = ((Cik[17][2][2]*Wpk[14][16][2])+((Cik[17][0][2]*
          Wpk[14][16][0])+(Cik[17][1][2]*Wpk[14][16][1])));
        Wpk[14][18][0] = ((Cik[18][2][0]*Wpk[14][17][2])+((Cik[18][0][0]*
          Wpk[14][17][0])+(Cik[18][1][0]*Wpk[14][17][1])));
        Wpk[14][18][1] = ((Cik[18][2][1]*Wpk[14][17][2])+((Cik[18][0][1]*
          Wpk[14][17][0])+(Cik[18][1][1]*Wpk[14][17][1])));
        Wpk[14][18][2] = ((Cik[18][2][2]*Wpk[14][17][2])+((Cik[18][0][2]*
          Wpk[14][17][0])+(Cik[18][1][2]*Wpk[14][17][1])));
        Wpk[14][19][0] = ((Cik[19][2][0]*Wpk[14][18][2])+((Cik[19][0][0]*
          Wpk[14][18][0])+(Cik[19][1][0]*Wpk[14][18][1])));
        Wpk[14][19][1] = ((Cik[19][2][1]*Wpk[14][18][2])+((Cik[19][0][1]*
          Wpk[14][18][0])+(Cik[19][1][1]*Wpk[14][18][1])));
        Wpk[14][19][2] = ((Cik[19][2][2]*Wpk[14][18][2])+((Cik[19][0][2]*
          Wpk[14][18][0])+(Cik[19][1][2]*Wpk[14][18][1])));
        Wpk[14][20][0] = ((Cik[20][2][0]*Wpk[14][19][2])+((Cik[20][0][0]*
          Wpk[14][19][0])+(Cik[20][1][0]*Wpk[14][19][1])));
        Wpk[14][20][1] = ((Cik[20][2][1]*Wpk[14][19][2])+((Cik[20][0][1]*
          Wpk[14][19][0])+(Cik[20][1][1]*Wpk[14][19][1])));
        Wpk[14][20][2] = ((Cik[20][2][2]*Wpk[14][19][2])+((Cik[20][0][2]*
          Wpk[14][19][0])+(Cik[20][1][2]*Wpk[14][19][1])));
        Wpk[15][15][0] = pin[15][0];
        Wpk[15][15][1] = pin[15][1];
        Wpk[15][15][2] = pin[15][2];
        Wpk[15][16][0] = ((Cik[16][2][0]*pin[15][2])+((Cik[16][0][0]*pin[15][0])
          +(Cik[16][1][0]*pin[15][1])));
        Wpk[15][16][1] = ((Cik[16][2][1]*pin[15][2])+((Cik[16][0][1]*pin[15][0])
          +(Cik[16][1][1]*pin[15][1])));
        Wpk[15][16][2] = ((Cik[16][2][2]*pin[15][2])+((Cik[16][0][2]*pin[15][0])
          +(Cik[16][1][2]*pin[15][1])));
        Wpk[15][17][0] = ((Cik[17][2][0]*Wpk[15][16][2])+((Cik[17][0][0]*
          Wpk[15][16][0])+(Cik[17][1][0]*Wpk[15][16][1])));
        Wpk[15][17][1] = ((Cik[17][2][1]*Wpk[15][16][2])+((Cik[17][0][1]*
          Wpk[15][16][0])+(Cik[17][1][1]*Wpk[15][16][1])));
        Wpk[15][17][2] = ((Cik[17][2][2]*Wpk[15][16][2])+((Cik[17][0][2]*
          Wpk[15][16][0])+(Cik[17][1][2]*Wpk[15][16][1])));
        Wpk[15][18][0] = ((Cik[18][2][0]*Wpk[15][17][2])+((Cik[18][0][0]*
          Wpk[15][17][0])+(Cik[18][1][0]*Wpk[15][17][1])));
        Wpk[15][18][1] = ((Cik[18][2][1]*Wpk[15][17][2])+((Cik[18][0][1]*
          Wpk[15][17][0])+(Cik[18][1][1]*Wpk[15][17][1])));
        Wpk[15][18][2] = ((Cik[18][2][2]*Wpk[15][17][2])+((Cik[18][0][2]*
          Wpk[15][17][0])+(Cik[18][1][2]*Wpk[15][17][1])));
        Wpk[15][19][0] = ((Cik[19][2][0]*Wpk[15][18][2])+((Cik[19][0][0]*
          Wpk[15][18][0])+(Cik[19][1][0]*Wpk[15][18][1])));
        Wpk[15][19][1] = ((Cik[19][2][1]*Wpk[15][18][2])+((Cik[19][0][1]*
          Wpk[15][18][0])+(Cik[19][1][1]*Wpk[15][18][1])));
        Wpk[15][19][2] = ((Cik[19][2][2]*Wpk[15][18][2])+((Cik[19][0][2]*
          Wpk[15][18][0])+(Cik[19][1][2]*Wpk[15][18][1])));
        Wpk[15][20][0] = ((Cik[20][2][0]*Wpk[15][19][2])+((Cik[20][0][0]*
          Wpk[15][19][0])+(Cik[20][1][0]*Wpk[15][19][1])));
        Wpk[15][20][1] = ((Cik[20][2][1]*Wpk[15][19][2])+((Cik[20][0][1]*
          Wpk[15][19][0])+(Cik[20][1][1]*Wpk[15][19][1])));
        Wpk[15][20][2] = ((Cik[20][2][2]*Wpk[15][19][2])+((Cik[20][0][2]*
          Wpk[15][19][0])+(Cik[20][1][2]*Wpk[15][19][1])));
        Wpk[16][16][0] = pin[16][0];
        Wpk[16][16][1] = pin[16][1];
        Wpk[16][16][2] = pin[16][2];
        Wpk[16][17][0] = ((Cik[17][2][0]*pin[16][2])+((Cik[17][0][0]*pin[16][0])
          +(Cik[17][1][0]*pin[16][1])));
        Wpk[16][17][1] = ((Cik[17][2][1]*pin[16][2])+((Cik[17][0][1]*pin[16][0])
          +(Cik[17][1][1]*pin[16][1])));
        Wpk[16][17][2] = ((Cik[17][2][2]*pin[16][2])+((Cik[17][0][2]*pin[16][0])
          +(Cik[17][1][2]*pin[16][1])));
        Wpk[16][18][0] = ((Cik[18][2][0]*Wpk[16][17][2])+((Cik[18][0][0]*
          Wpk[16][17][0])+(Cik[18][1][0]*Wpk[16][17][1])));
        Wpk[16][18][1] = ((Cik[18][2][1]*Wpk[16][17][2])+((Cik[18][0][1]*
          Wpk[16][17][0])+(Cik[18][1][1]*Wpk[16][17][1])));
        Wpk[16][18][2] = ((Cik[18][2][2]*Wpk[16][17][2])+((Cik[18][0][2]*
          Wpk[16][17][0])+(Cik[18][1][2]*Wpk[16][17][1])));
        Wpk[16][19][0] = ((Cik[19][2][0]*Wpk[16][18][2])+((Cik[19][0][0]*
          Wpk[16][18][0])+(Cik[19][1][0]*Wpk[16][18][1])));
        Wpk[16][19][1] = ((Cik[19][2][1]*Wpk[16][18][2])+((Cik[19][0][1]*
          Wpk[16][18][0])+(Cik[19][1][1]*Wpk[16][18][1])));
        Wpk[16][19][2] = ((Cik[19][2][2]*Wpk[16][18][2])+((Cik[19][0][2]*
          Wpk[16][18][0])+(Cik[19][1][2]*Wpk[16][18][1])));
        Wpk[16][20][0] = ((Cik[20][2][0]*Wpk[16][19][2])+((Cik[20][0][0]*
          Wpk[16][19][0])+(Cik[20][1][0]*Wpk[16][19][1])));
        Wpk[16][20][1] = ((Cik[20][2][1]*Wpk[16][19][2])+((Cik[20][0][1]*
          Wpk[16][19][0])+(Cik[20][1][1]*Wpk[16][19][1])));
        Wpk[16][20][2] = ((Cik[20][2][2]*Wpk[16][19][2])+((Cik[20][0][2]*
          Wpk[16][19][0])+(Cik[20][1][2]*Wpk[16][19][1])));
        Wpk[17][17][0] = pin[17][0];
        Wpk[17][17][1] = pin[17][1];
        Wpk[17][17][2] = pin[17][2];
        Wpk[17][18][0] = ((Cik[18][2][0]*pin[17][2])+((Cik[18][0][0]*pin[17][0])
          +(Cik[18][1][0]*pin[17][1])));
        Wpk[17][18][1] = ((Cik[18][2][1]*pin[17][2])+((Cik[18][0][1]*pin[17][0])
          +(Cik[18][1][1]*pin[17][1])));
        Wpk[17][18][2] = ((Cik[18][2][2]*pin[17][2])+((Cik[18][0][2]*pin[17][0])
          +(Cik[18][1][2]*pin[17][1])));
        Wpk[17][19][0] = ((Cik[19][2][0]*Wpk[17][18][2])+((Cik[19][0][0]*
          Wpk[17][18][0])+(Cik[19][1][0]*Wpk[17][18][1])));
        Wpk[17][19][1] = ((Cik[19][2][1]*Wpk[17][18][2])+((Cik[19][0][1]*
          Wpk[17][18][0])+(Cik[19][1][1]*Wpk[17][18][1])));
        Wpk[17][19][2] = ((Cik[19][2][2]*Wpk[17][18][2])+((Cik[19][0][2]*
          Wpk[17][18][0])+(Cik[19][1][2]*Wpk[17][18][1])));
        Wpk[17][20][0] = ((Cik[20][2][0]*Wpk[17][19][2])+((Cik[20][0][0]*
          Wpk[17][19][0])+(Cik[20][1][0]*Wpk[17][19][1])));
        Wpk[17][20][1] = ((Cik[20][2][1]*Wpk[17][19][2])+((Cik[20][0][1]*
          Wpk[17][19][0])+(Cik[20][1][1]*Wpk[17][19][1])));
        Wpk[17][20][2] = ((Cik[20][2][2]*Wpk[17][19][2])+((Cik[20][0][2]*
          Wpk[17][19][0])+(Cik[20][1][2]*Wpk[17][19][1])));
        Wpk[18][18][0] = pin[18][0];
        Wpk[18][18][1] = pin[18][1];
        Wpk[18][18][2] = pin[18][2];
        Wpk[18][19][0] = ((Cik[19][2][0]*pin[18][2])+((Cik[19][0][0]*pin[18][0])
          +(Cik[19][1][0]*pin[18][1])));
        Wpk[18][19][1] = ((Cik[19][2][1]*pin[18][2])+((Cik[19][0][1]*pin[18][0])
          +(Cik[19][1][1]*pin[18][1])));
        Wpk[18][19][2] = ((Cik[19][2][2]*pin[18][2])+((Cik[19][0][2]*pin[18][0])
          +(Cik[19][1][2]*pin[18][1])));
        Wpk[18][20][0] = ((Cik[20][2][0]*Wpk[18][19][2])+((Cik[20][0][0]*
          Wpk[18][19][0])+(Cik[20][1][0]*Wpk[18][19][1])));
        Wpk[18][20][1] = ((Cik[20][2][1]*Wpk[18][19][2])+((Cik[20][0][1]*
          Wpk[18][19][0])+(Cik[20][1][1]*Wpk[18][19][1])));
        Wpk[18][20][2] = ((Cik[20][2][2]*Wpk[18][19][2])+((Cik[20][0][2]*
          Wpk[18][19][0])+(Cik[20][1][2]*Wpk[18][19][1])));
        Wpk[19][19][0] = pin[19][0];
        Wpk[19][19][1] = pin[19][1];
        Wpk[19][19][2] = pin[19][2];
        Wpk[19][20][0] = ((Cik[20][2][0]*pin[19][2])+((Cik[20][0][0]*pin[19][0])
          +(Cik[20][1][0]*pin[19][1])));
        Wpk[19][20][1] = ((Cik[20][2][1]*pin[19][2])+((Cik[20][0][1]*pin[19][0])
          +(Cik[20][1][1]*pin[19][1])));
        Wpk[19][20][2] = ((Cik[20][2][2]*pin[19][2])+((Cik[20][0][2]*pin[19][0])
          +(Cik[20][1][2]*pin[19][1])));
        Wpk[20][20][0] = pin[20][0];
        Wpk[20][20][1] = pin[20][1];
        Wpk[20][20][2] = pin[20][2];
        Wpk[21][21][0] = pin[21][0];
        Wpk[21][21][1] = pin[21][1];
        Wpk[21][21][2] = pin[21][2];
        Wpk[21][22][0] = ((Cik[22][2][0]*pin[21][2])+((Cik[22][0][0]*pin[21][0])
          +(Cik[22][1][0]*pin[21][1])));
        Wpk[21][22][1] = ((Cik[22][2][1]*pin[21][2])+((Cik[22][0][1]*pin[21][0])
          +(Cik[22][1][1]*pin[21][1])));
        Wpk[21][22][2] = ((Cik[22][2][2]*pin[21][2])+((Cik[22][0][2]*pin[21][0])
          +(Cik[22][1][2]*pin[21][1])));
        Wpk[21][23][0] = ((Cik[23][2][0]*Wpk[21][22][2])+((Cik[23][0][0]*
          Wpk[21][22][0])+(Cik[23][1][0]*Wpk[21][22][1])));
        Wpk[21][23][1] = ((Cik[23][2][1]*Wpk[21][22][2])+((Cik[23][0][1]*
          Wpk[21][22][0])+(Cik[23][1][1]*Wpk[21][22][1])));
        Wpk[21][23][2] = ((Cik[23][2][2]*Wpk[21][22][2])+((Cik[23][0][2]*
          Wpk[21][22][0])+(Cik[23][1][2]*Wpk[21][22][1])));
        Wpk[21][24][0] = ((Cik[24][2][0]*Wpk[21][23][2])+((Cik[24][0][0]*
          Wpk[21][23][0])+(Cik[24][1][0]*Wpk[21][23][1])));
        Wpk[21][24][1] = ((Cik[24][2][1]*Wpk[21][23][2])+((Cik[24][0][1]*
          Wpk[21][23][0])+(Cik[24][1][1]*Wpk[21][23][1])));
        Wpk[21][24][2] = ((Cik[24][2][2]*Wpk[21][23][2])+((Cik[24][0][2]*
          Wpk[21][23][0])+(Cik[24][1][2]*Wpk[21][23][1])));
        Wpk[21][25][0] = ((Cik[25][2][0]*Wpk[21][24][2])+((Cik[25][0][0]*
          Wpk[21][24][0])+(Cik[25][1][0]*Wpk[21][24][1])));
        Wpk[21][25][1] = ((Cik[25][2][1]*Wpk[21][24][2])+((Cik[25][0][1]*
          Wpk[21][24][0])+(Cik[25][1][1]*Wpk[21][24][1])));
        Wpk[21][25][2] = ((Cik[25][2][2]*Wpk[21][24][2])+((Cik[25][0][2]*
          Wpk[21][24][0])+(Cik[25][1][2]*Wpk[21][24][1])));
        Wpk[21][26][0] = ((Cik[26][2][0]*Wpk[21][25][2])+((Cik[26][0][0]*
          Wpk[21][25][0])+(Cik[26][1][0]*Wpk[21][25][1])));
        Wpk[21][26][1] = ((Cik[26][2][1]*Wpk[21][25][2])+((Cik[26][0][1]*
          Wpk[21][25][0])+(Cik[26][1][1]*Wpk[21][25][1])));
        Wpk[21][26][2] = ((Cik[26][2][2]*Wpk[21][25][2])+((Cik[26][0][2]*
          Wpk[21][25][0])+(Cik[26][1][2]*Wpk[21][25][1])));
        Wpk[21][27][0] = ((Cik[27][2][0]*Wpk[21][26][2])+((Cik[27][0][0]*
          Wpk[21][26][0])+(Cik[27][1][0]*Wpk[21][26][1])));
        Wpk[21][27][1] = ((Cik[27][2][1]*Wpk[21][26][2])+((Cik[27][0][1]*
          Wpk[21][26][0])+(Cik[27][1][1]*Wpk[21][26][1])));
        Wpk[21][27][2] = ((Cik[27][2][2]*Wpk[21][26][2])+((Cik[27][0][2]*
          Wpk[21][26][0])+(Cik[27][1][2]*Wpk[21][26][1])));
        Wpk[21][28][0] = ((Cik[28][2][0]*Wpk[21][27][2])+((Cik[28][0][0]*
          Wpk[21][27][0])+(Cik[28][1][0]*Wpk[21][27][1])));
        Wpk[21][28][1] = ((Cik[28][2][1]*Wpk[21][27][2])+((Cik[28][0][1]*
          Wpk[21][27][0])+(Cik[28][1][1]*Wpk[21][27][1])));
        Wpk[21][28][2] = ((Cik[28][2][2]*Wpk[21][27][2])+((Cik[28][0][2]*
          Wpk[21][27][0])+(Cik[28][1][2]*Wpk[21][27][1])));
        Wpk[21][29][0] = ((Cik[29][2][0]*Wpk[21][28][2])+((Cik[29][0][0]*
          Wpk[21][28][0])+(Cik[29][1][0]*Wpk[21][28][1])));
        Wpk[21][29][1] = ((Cik[29][2][1]*Wpk[21][28][2])+((Cik[29][0][1]*
          Wpk[21][28][0])+(Cik[29][1][1]*Wpk[21][28][1])));
        Wpk[21][29][2] = ((Cik[29][2][2]*Wpk[21][28][2])+((Cik[29][0][2]*
          Wpk[21][28][0])+(Cik[29][1][2]*Wpk[21][28][1])));
        Wpk[21][30][0] = ((Cik[30][2][0]*Wpk[21][29][2])+((Cik[30][0][0]*
          Wpk[21][29][0])+(Cik[30][1][0]*Wpk[21][29][1])));
        Wpk[21][30][1] = ((Cik[30][2][1]*Wpk[21][29][2])+((Cik[30][0][1]*
          Wpk[21][29][0])+(Cik[30][1][1]*Wpk[21][29][1])));
        Wpk[21][30][2] = ((Cik[30][2][2]*Wpk[21][29][2])+((Cik[30][0][2]*
          Wpk[21][29][0])+(Cik[30][1][2]*Wpk[21][29][1])));
        Wpk[21][31][0] = ((Cik[31][2][0]*Wpk[21][30][2])+((Cik[31][0][0]*
          Wpk[21][30][0])+(Cik[31][1][0]*Wpk[21][30][1])));
        Wpk[21][31][1] = ((Cik[31][2][1]*Wpk[21][30][2])+((Cik[31][0][1]*
          Wpk[21][30][0])+(Cik[31][1][1]*Wpk[21][30][1])));
        Wpk[21][31][2] = ((Cik[31][2][2]*Wpk[21][30][2])+((Cik[31][0][2]*
          Wpk[21][30][0])+(Cik[31][1][2]*Wpk[21][30][1])));
        Wpk[21][32][0] = ((Cik[32][2][0]*Wpk[21][31][2])+((Cik[32][0][0]*
          Wpk[21][31][0])+(Cik[32][1][0]*Wpk[21][31][1])));
        Wpk[21][32][1] = ((Cik[32][2][1]*Wpk[21][31][2])+((Cik[32][0][1]*
          Wpk[21][31][0])+(Cik[32][1][1]*Wpk[21][31][1])));
        Wpk[21][32][2] = ((Cik[32][2][2]*Wpk[21][31][2])+((Cik[32][0][2]*
          Wpk[21][31][0])+(Cik[32][1][2]*Wpk[21][31][1])));
        Wpk[22][22][0] = pin[22][0];
        Wpk[22][22][1] = pin[22][1];
        Wpk[22][22][2] = pin[22][2];
        Wpk[22][23][0] = ((Cik[23][2][0]*pin[22][2])+((Cik[23][0][0]*pin[22][0])
          +(Cik[23][1][0]*pin[22][1])));
        Wpk[22][23][1] = ((Cik[23][2][1]*pin[22][2])+((Cik[23][0][1]*pin[22][0])
          +(Cik[23][1][1]*pin[22][1])));
        Wpk[22][23][2] = ((Cik[23][2][2]*pin[22][2])+((Cik[23][0][2]*pin[22][0])
          +(Cik[23][1][2]*pin[22][1])));
        Wpk[22][24][0] = ((Cik[24][2][0]*Wpk[22][23][2])+((Cik[24][0][0]*
          Wpk[22][23][0])+(Cik[24][1][0]*Wpk[22][23][1])));
        Wpk[22][24][1] = ((Cik[24][2][1]*Wpk[22][23][2])+((Cik[24][0][1]*
          Wpk[22][23][0])+(Cik[24][1][1]*Wpk[22][23][1])));
        Wpk[22][24][2] = ((Cik[24][2][2]*Wpk[22][23][2])+((Cik[24][0][2]*
          Wpk[22][23][0])+(Cik[24][1][2]*Wpk[22][23][1])));
        Wpk[22][25][0] = ((Cik[25][2][0]*Wpk[22][24][2])+((Cik[25][0][0]*
          Wpk[22][24][0])+(Cik[25][1][0]*Wpk[22][24][1])));
        Wpk[22][25][1] = ((Cik[25][2][1]*Wpk[22][24][2])+((Cik[25][0][1]*
          Wpk[22][24][0])+(Cik[25][1][1]*Wpk[22][24][1])));
        Wpk[22][25][2] = ((Cik[25][2][2]*Wpk[22][24][2])+((Cik[25][0][2]*
          Wpk[22][24][0])+(Cik[25][1][2]*Wpk[22][24][1])));
        Wpk[22][26][0] = ((Cik[26][2][0]*Wpk[22][25][2])+((Cik[26][0][0]*
          Wpk[22][25][0])+(Cik[26][1][0]*Wpk[22][25][1])));
        Wpk[22][26][1] = ((Cik[26][2][1]*Wpk[22][25][2])+((Cik[26][0][1]*
          Wpk[22][25][0])+(Cik[26][1][1]*Wpk[22][25][1])));
        Wpk[22][26][2] = ((Cik[26][2][2]*Wpk[22][25][2])+((Cik[26][0][2]*
          Wpk[22][25][0])+(Cik[26][1][2]*Wpk[22][25][1])));
        Wpk[22][27][0] = ((Cik[27][2][0]*Wpk[22][26][2])+((Cik[27][0][0]*
          Wpk[22][26][0])+(Cik[27][1][0]*Wpk[22][26][1])));
        Wpk[22][27][1] = ((Cik[27][2][1]*Wpk[22][26][2])+((Cik[27][0][1]*
          Wpk[22][26][0])+(Cik[27][1][1]*Wpk[22][26][1])));
        Wpk[22][27][2] = ((Cik[27][2][2]*Wpk[22][26][2])+((Cik[27][0][2]*
          Wpk[22][26][0])+(Cik[27][1][2]*Wpk[22][26][1])));
        Wpk[22][28][0] = ((Cik[28][2][0]*Wpk[22][27][2])+((Cik[28][0][0]*
          Wpk[22][27][0])+(Cik[28][1][0]*Wpk[22][27][1])));
        Wpk[22][28][1] = ((Cik[28][2][1]*Wpk[22][27][2])+((Cik[28][0][1]*
          Wpk[22][27][0])+(Cik[28][1][1]*Wpk[22][27][1])));
        Wpk[22][28][2] = ((Cik[28][2][2]*Wpk[22][27][2])+((Cik[28][0][2]*
          Wpk[22][27][0])+(Cik[28][1][2]*Wpk[22][27][1])));
        Wpk[22][29][0] = ((Cik[29][2][0]*Wpk[22][28][2])+((Cik[29][0][0]*
          Wpk[22][28][0])+(Cik[29][1][0]*Wpk[22][28][1])));
        Wpk[22][29][1] = ((Cik[29][2][1]*Wpk[22][28][2])+((Cik[29][0][1]*
          Wpk[22][28][0])+(Cik[29][1][1]*Wpk[22][28][1])));
        Wpk[22][29][2] = ((Cik[29][2][2]*Wpk[22][28][2])+((Cik[29][0][2]*
          Wpk[22][28][0])+(Cik[29][1][2]*Wpk[22][28][1])));
        Wpk[22][30][0] = ((Cik[30][2][0]*Wpk[22][29][2])+((Cik[30][0][0]*
          Wpk[22][29][0])+(Cik[30][1][0]*Wpk[22][29][1])));
        Wpk[22][30][1] = ((Cik[30][2][1]*Wpk[22][29][2])+((Cik[30][0][1]*
          Wpk[22][29][0])+(Cik[30][1][1]*Wpk[22][29][1])));
        Wpk[22][30][2] = ((Cik[30][2][2]*Wpk[22][29][2])+((Cik[30][0][2]*
          Wpk[22][29][0])+(Cik[30][1][2]*Wpk[22][29][1])));
        Wpk[22][31][0] = ((Cik[31][2][0]*Wpk[22][30][2])+((Cik[31][0][0]*
          Wpk[22][30][0])+(Cik[31][1][0]*Wpk[22][30][1])));
        Wpk[22][31][1] = ((Cik[31][2][1]*Wpk[22][30][2])+((Cik[31][0][1]*
          Wpk[22][30][0])+(Cik[31][1][1]*Wpk[22][30][1])));
        Wpk[22][31][2] = ((Cik[31][2][2]*Wpk[22][30][2])+((Cik[31][0][2]*
          Wpk[22][30][0])+(Cik[31][1][2]*Wpk[22][30][1])));
        Wpk[22][32][0] = ((Cik[32][2][0]*Wpk[22][31][2])+((Cik[32][0][0]*
          Wpk[22][31][0])+(Cik[32][1][0]*Wpk[22][31][1])));
        Wpk[22][32][1] = ((Cik[32][2][1]*Wpk[22][31][2])+((Cik[32][0][1]*
          Wpk[22][31][0])+(Cik[32][1][1]*Wpk[22][31][1])));
        Wpk[22][32][2] = ((Cik[32][2][2]*Wpk[22][31][2])+((Cik[32][0][2]*
          Wpk[22][31][0])+(Cik[32][1][2]*Wpk[22][31][1])));
        Wpk[23][23][0] = pin[23][0];
        Wpk[23][23][1] = pin[23][1];
        Wpk[23][23][2] = pin[23][2];
        Wpk[23][24][0] = ((Cik[24][2][0]*pin[23][2])+((Cik[24][0][0]*pin[23][0])
          +(Cik[24][1][0]*pin[23][1])));
        Wpk[23][24][1] = ((Cik[24][2][1]*pin[23][2])+((Cik[24][0][1]*pin[23][0])
          +(Cik[24][1][1]*pin[23][1])));
        Wpk[23][24][2] = ((Cik[24][2][2]*pin[23][2])+((Cik[24][0][2]*pin[23][0])
          +(Cik[24][1][2]*pin[23][1])));
        Wpk[23][25][0] = ((Cik[25][2][0]*Wpk[23][24][2])+((Cik[25][0][0]*
          Wpk[23][24][0])+(Cik[25][1][0]*Wpk[23][24][1])));
        Wpk[23][25][1] = ((Cik[25][2][1]*Wpk[23][24][2])+((Cik[25][0][1]*
          Wpk[23][24][0])+(Cik[25][1][1]*Wpk[23][24][1])));
        Wpk[23][25][2] = ((Cik[25][2][2]*Wpk[23][24][2])+((Cik[25][0][2]*
          Wpk[23][24][0])+(Cik[25][1][2]*Wpk[23][24][1])));
        Wpk[23][26][0] = ((Cik[26][2][0]*Wpk[23][25][2])+((Cik[26][0][0]*
          Wpk[23][25][0])+(Cik[26][1][0]*Wpk[23][25][1])));
        Wpk[23][26][1] = ((Cik[26][2][1]*Wpk[23][25][2])+((Cik[26][0][1]*
          Wpk[23][25][0])+(Cik[26][1][1]*Wpk[23][25][1])));
        Wpk[23][26][2] = ((Cik[26][2][2]*Wpk[23][25][2])+((Cik[26][0][2]*
          Wpk[23][25][0])+(Cik[26][1][2]*Wpk[23][25][1])));
        Wpk[23][27][0] = ((Cik[27][2][0]*Wpk[23][26][2])+((Cik[27][0][0]*
          Wpk[23][26][0])+(Cik[27][1][0]*Wpk[23][26][1])));
        Wpk[23][27][1] = ((Cik[27][2][1]*Wpk[23][26][2])+((Cik[27][0][1]*
          Wpk[23][26][0])+(Cik[27][1][1]*Wpk[23][26][1])));
        Wpk[23][27][2] = ((Cik[27][2][2]*Wpk[23][26][2])+((Cik[27][0][2]*
          Wpk[23][26][0])+(Cik[27][1][2]*Wpk[23][26][1])));
        Wpk[23][28][0] = ((Cik[28][2][0]*Wpk[23][27][2])+((Cik[28][0][0]*
          Wpk[23][27][0])+(Cik[28][1][0]*Wpk[23][27][1])));
        Wpk[23][28][1] = ((Cik[28][2][1]*Wpk[23][27][2])+((Cik[28][0][1]*
          Wpk[23][27][0])+(Cik[28][1][1]*Wpk[23][27][1])));
        Wpk[23][28][2] = ((Cik[28][2][2]*Wpk[23][27][2])+((Cik[28][0][2]*
          Wpk[23][27][0])+(Cik[28][1][2]*Wpk[23][27][1])));
        Wpk[23][29][0] = ((Cik[29][2][0]*Wpk[23][28][2])+((Cik[29][0][0]*
          Wpk[23][28][0])+(Cik[29][1][0]*Wpk[23][28][1])));
        Wpk[23][29][1] = ((Cik[29][2][1]*Wpk[23][28][2])+((Cik[29][0][1]*
          Wpk[23][28][0])+(Cik[29][1][1]*Wpk[23][28][1])));
        Wpk[23][29][2] = ((Cik[29][2][2]*Wpk[23][28][2])+((Cik[29][0][2]*
          Wpk[23][28][0])+(Cik[29][1][2]*Wpk[23][28][1])));
        Wpk[23][30][0] = ((Cik[30][2][0]*Wpk[23][29][2])+((Cik[30][0][0]*
          Wpk[23][29][0])+(Cik[30][1][0]*Wpk[23][29][1])));
        Wpk[23][30][1] = ((Cik[30][2][1]*Wpk[23][29][2])+((Cik[30][0][1]*
          Wpk[23][29][0])+(Cik[30][1][1]*Wpk[23][29][1])));
        Wpk[23][30][2] = ((Cik[30][2][2]*Wpk[23][29][2])+((Cik[30][0][2]*
          Wpk[23][29][0])+(Cik[30][1][2]*Wpk[23][29][1])));
        Wpk[23][31][0] = ((Cik[31][2][0]*Wpk[23][30][2])+((Cik[31][0][0]*
          Wpk[23][30][0])+(Cik[31][1][0]*Wpk[23][30][1])));
        Wpk[23][31][1] = ((Cik[31][2][1]*Wpk[23][30][2])+((Cik[31][0][1]*
          Wpk[23][30][0])+(Cik[31][1][1]*Wpk[23][30][1])));
        Wpk[23][31][2] = ((Cik[31][2][2]*Wpk[23][30][2])+((Cik[31][0][2]*
          Wpk[23][30][0])+(Cik[31][1][2]*Wpk[23][30][1])));
        Wpk[23][32][0] = ((Cik[32][2][0]*Wpk[23][31][2])+((Cik[32][0][0]*
          Wpk[23][31][0])+(Cik[32][1][0]*Wpk[23][31][1])));
        Wpk[23][32][1] = ((Cik[32][2][1]*Wpk[23][31][2])+((Cik[32][0][1]*
          Wpk[23][31][0])+(Cik[32][1][1]*Wpk[23][31][1])));
        Wpk[23][32][2] = ((Cik[32][2][2]*Wpk[23][31][2])+((Cik[32][0][2]*
          Wpk[23][31][0])+(Cik[32][1][2]*Wpk[23][31][1])));
        Wpk[24][24][0] = pin[24][0];
        Wpk[24][24][1] = pin[24][1];
        Wpk[24][24][2] = pin[24][2];
        Wpk[24][25][0] = ((Cik[25][2][0]*pin[24][2])+((Cik[25][0][0]*pin[24][0])
          +(Cik[25][1][0]*pin[24][1])));
        Wpk[24][25][1] = ((Cik[25][2][1]*pin[24][2])+((Cik[25][0][1]*pin[24][0])
          +(Cik[25][1][1]*pin[24][1])));
        Wpk[24][25][2] = ((Cik[25][2][2]*pin[24][2])+((Cik[25][0][2]*pin[24][0])
          +(Cik[25][1][2]*pin[24][1])));
        Wpk[24][26][0] = ((Cik[26][2][0]*Wpk[24][25][2])+((Cik[26][0][0]*
          Wpk[24][25][0])+(Cik[26][1][0]*Wpk[24][25][1])));
        Wpk[24][26][1] = ((Cik[26][2][1]*Wpk[24][25][2])+((Cik[26][0][1]*
          Wpk[24][25][0])+(Cik[26][1][1]*Wpk[24][25][1])));
        Wpk[24][26][2] = ((Cik[26][2][2]*Wpk[24][25][2])+((Cik[26][0][2]*
          Wpk[24][25][0])+(Cik[26][1][2]*Wpk[24][25][1])));
        Wpk[24][27][0] = ((Cik[27][2][0]*Wpk[24][26][2])+((Cik[27][0][0]*
          Wpk[24][26][0])+(Cik[27][1][0]*Wpk[24][26][1])));
        Wpk[24][27][1] = ((Cik[27][2][1]*Wpk[24][26][2])+((Cik[27][0][1]*
          Wpk[24][26][0])+(Cik[27][1][1]*Wpk[24][26][1])));
        Wpk[24][27][2] = ((Cik[27][2][2]*Wpk[24][26][2])+((Cik[27][0][2]*
          Wpk[24][26][0])+(Cik[27][1][2]*Wpk[24][26][1])));
        Wpk[24][28][0] = ((Cik[28][2][0]*Wpk[24][27][2])+((Cik[28][0][0]*
          Wpk[24][27][0])+(Cik[28][1][0]*Wpk[24][27][1])));
        Wpk[24][28][1] = ((Cik[28][2][1]*Wpk[24][27][2])+((Cik[28][0][1]*
          Wpk[24][27][0])+(Cik[28][1][1]*Wpk[24][27][1])));
        Wpk[24][28][2] = ((Cik[28][2][2]*Wpk[24][27][2])+((Cik[28][0][2]*
          Wpk[24][27][0])+(Cik[28][1][2]*Wpk[24][27][1])));
        Wpk[24][29][0] = ((Cik[29][2][0]*Wpk[24][28][2])+((Cik[29][0][0]*
          Wpk[24][28][0])+(Cik[29][1][0]*Wpk[24][28][1])));
        Wpk[24][29][1] = ((Cik[29][2][1]*Wpk[24][28][2])+((Cik[29][0][1]*
          Wpk[24][28][0])+(Cik[29][1][1]*Wpk[24][28][1])));
        Wpk[24][29][2] = ((Cik[29][2][2]*Wpk[24][28][2])+((Cik[29][0][2]*
          Wpk[24][28][0])+(Cik[29][1][2]*Wpk[24][28][1])));
        Wpk[24][30][0] = ((Cik[30][2][0]*Wpk[24][29][2])+((Cik[30][0][0]*
          Wpk[24][29][0])+(Cik[30][1][0]*Wpk[24][29][1])));
        Wpk[24][30][1] = ((Cik[30][2][1]*Wpk[24][29][2])+((Cik[30][0][1]*
          Wpk[24][29][0])+(Cik[30][1][1]*Wpk[24][29][1])));
        Wpk[24][30][2] = ((Cik[30][2][2]*Wpk[24][29][2])+((Cik[30][0][2]*
          Wpk[24][29][0])+(Cik[30][1][2]*Wpk[24][29][1])));
        Wpk[24][31][0] = ((Cik[31][2][0]*Wpk[24][30][2])+((Cik[31][0][0]*
          Wpk[24][30][0])+(Cik[31][1][0]*Wpk[24][30][1])));
        Wpk[24][31][1] = ((Cik[31][2][1]*Wpk[24][30][2])+((Cik[31][0][1]*
          Wpk[24][30][0])+(Cik[31][1][1]*Wpk[24][30][1])));
        Wpk[24][31][2] = ((Cik[31][2][2]*Wpk[24][30][2])+((Cik[31][0][2]*
          Wpk[24][30][0])+(Cik[31][1][2]*Wpk[24][30][1])));
        Wpk[24][32][0] = ((Cik[32][2][0]*Wpk[24][31][2])+((Cik[32][0][0]*
          Wpk[24][31][0])+(Cik[32][1][0]*Wpk[24][31][1])));
        Wpk[24][32][1] = ((Cik[32][2][1]*Wpk[24][31][2])+((Cik[32][0][1]*
          Wpk[24][31][0])+(Cik[32][1][1]*Wpk[24][31][1])));
        Wpk[24][32][2] = ((Cik[32][2][2]*Wpk[24][31][2])+((Cik[32][0][2]*
          Wpk[24][31][0])+(Cik[32][1][2]*Wpk[24][31][1])));
        Wpk[25][25][0] = pin[25][0];
        Wpk[25][25][1] = pin[25][1];
        Wpk[25][25][2] = pin[25][2];
        Wpk[25][26][0] = ((Cik[26][2][0]*pin[25][2])+((Cik[26][0][0]*pin[25][0])
          +(Cik[26][1][0]*pin[25][1])));
        Wpk[25][26][1] = ((Cik[26][2][1]*pin[25][2])+((Cik[26][0][1]*pin[25][0])
          +(Cik[26][1][1]*pin[25][1])));
        Wpk[25][26][2] = ((Cik[26][2][2]*pin[25][2])+((Cik[26][0][2]*pin[25][0])
          +(Cik[26][1][2]*pin[25][1])));
        Wpk[25][27][0] = ((Cik[27][2][0]*Wpk[25][26][2])+((Cik[27][0][0]*
          Wpk[25][26][0])+(Cik[27][1][0]*Wpk[25][26][1])));
        Wpk[25][27][1] = ((Cik[27][2][1]*Wpk[25][26][2])+((Cik[27][0][1]*
          Wpk[25][26][0])+(Cik[27][1][1]*Wpk[25][26][1])));
        Wpk[25][27][2] = ((Cik[27][2][2]*Wpk[25][26][2])+((Cik[27][0][2]*
          Wpk[25][26][0])+(Cik[27][1][2]*Wpk[25][26][1])));
        Wpk[25][28][0] = ((Cik[28][2][0]*Wpk[25][27][2])+((Cik[28][0][0]*
          Wpk[25][27][0])+(Cik[28][1][0]*Wpk[25][27][1])));
        Wpk[25][28][1] = ((Cik[28][2][1]*Wpk[25][27][2])+((Cik[28][0][1]*
          Wpk[25][27][0])+(Cik[28][1][1]*Wpk[25][27][1])));
        Wpk[25][28][2] = ((Cik[28][2][2]*Wpk[25][27][2])+((Cik[28][0][2]*
          Wpk[25][27][0])+(Cik[28][1][2]*Wpk[25][27][1])));
        Wpk[25][29][0] = ((Cik[29][2][0]*Wpk[25][28][2])+((Cik[29][0][0]*
          Wpk[25][28][0])+(Cik[29][1][0]*Wpk[25][28][1])));
        Wpk[25][29][1] = ((Cik[29][2][1]*Wpk[25][28][2])+((Cik[29][0][1]*
          Wpk[25][28][0])+(Cik[29][1][1]*Wpk[25][28][1])));
        Wpk[25][29][2] = ((Cik[29][2][2]*Wpk[25][28][2])+((Cik[29][0][2]*
          Wpk[25][28][0])+(Cik[29][1][2]*Wpk[25][28][1])));
        Wpk[25][30][0] = ((Cik[30][2][0]*Wpk[25][29][2])+((Cik[30][0][0]*
          Wpk[25][29][0])+(Cik[30][1][0]*Wpk[25][29][1])));
        Wpk[25][30][1] = ((Cik[30][2][1]*Wpk[25][29][2])+((Cik[30][0][1]*
          Wpk[25][29][0])+(Cik[30][1][1]*Wpk[25][29][1])));
        Wpk[25][30][2] = ((Cik[30][2][2]*Wpk[25][29][2])+((Cik[30][0][2]*
          Wpk[25][29][0])+(Cik[30][1][2]*Wpk[25][29][1])));
        Wpk[25][31][0] = ((Cik[31][2][0]*Wpk[25][30][2])+((Cik[31][0][0]*
          Wpk[25][30][0])+(Cik[31][1][0]*Wpk[25][30][1])));
        Wpk[25][31][1] = ((Cik[31][2][1]*Wpk[25][30][2])+((Cik[31][0][1]*
          Wpk[25][30][0])+(Cik[31][1][1]*Wpk[25][30][1])));
        Wpk[25][31][2] = ((Cik[31][2][2]*Wpk[25][30][2])+((Cik[31][0][2]*
          Wpk[25][30][0])+(Cik[31][1][2]*Wpk[25][30][1])));
        Wpk[25][32][0] = ((Cik[32][2][0]*Wpk[25][31][2])+((Cik[32][0][0]*
          Wpk[25][31][0])+(Cik[32][1][0]*Wpk[25][31][1])));
        Wpk[25][32][1] = ((Cik[32][2][1]*Wpk[25][31][2])+((Cik[32][0][1]*
          Wpk[25][31][0])+(Cik[32][1][1]*Wpk[25][31][1])));
        Wpk[25][32][2] = ((Cik[32][2][2]*Wpk[25][31][2])+((Cik[32][0][2]*
          Wpk[25][31][0])+(Cik[32][1][2]*Wpk[25][31][1])));
        Wpk[26][26][0] = pin[26][0];
        Wpk[26][26][1] = pin[26][1];
        Wpk[26][26][2] = pin[26][2];
        Wpk[26][27][0] = ((Cik[27][2][0]*pin[26][2])+((Cik[27][0][0]*pin[26][0])
          +(Cik[27][1][0]*pin[26][1])));
        Wpk[26][27][1] = ((Cik[27][2][1]*pin[26][2])+((Cik[27][0][1]*pin[26][0])
          +(Cik[27][1][1]*pin[26][1])));
        Wpk[26][27][2] = ((Cik[27][2][2]*pin[26][2])+((Cik[27][0][2]*pin[26][0])
          +(Cik[27][1][2]*pin[26][1])));
        Wpk[26][28][0] = ((Cik[28][2][0]*Wpk[26][27][2])+((Cik[28][0][0]*
          Wpk[26][27][0])+(Cik[28][1][0]*Wpk[26][27][1])));
        Wpk[26][28][1] = ((Cik[28][2][1]*Wpk[26][27][2])+((Cik[28][0][1]*
          Wpk[26][27][0])+(Cik[28][1][1]*Wpk[26][27][1])));
        Wpk[26][28][2] = ((Cik[28][2][2]*Wpk[26][27][2])+((Cik[28][0][2]*
          Wpk[26][27][0])+(Cik[28][1][2]*Wpk[26][27][1])));
        Wpk[26][29][0] = ((Cik[29][2][0]*Wpk[26][28][2])+((Cik[29][0][0]*
          Wpk[26][28][0])+(Cik[29][1][0]*Wpk[26][28][1])));
        Wpk[26][29][1] = ((Cik[29][2][1]*Wpk[26][28][2])+((Cik[29][0][1]*
          Wpk[26][28][0])+(Cik[29][1][1]*Wpk[26][28][1])));
        Wpk[26][29][2] = ((Cik[29][2][2]*Wpk[26][28][2])+((Cik[29][0][2]*
          Wpk[26][28][0])+(Cik[29][1][2]*Wpk[26][28][1])));
        Wpk[26][30][0] = ((Cik[30][2][0]*Wpk[26][29][2])+((Cik[30][0][0]*
          Wpk[26][29][0])+(Cik[30][1][0]*Wpk[26][29][1])));
        Wpk[26][30][1] = ((Cik[30][2][1]*Wpk[26][29][2])+((Cik[30][0][1]*
          Wpk[26][29][0])+(Cik[30][1][1]*Wpk[26][29][1])));
        Wpk[26][30][2] = ((Cik[30][2][2]*Wpk[26][29][2])+((Cik[30][0][2]*
          Wpk[26][29][0])+(Cik[30][1][2]*Wpk[26][29][1])));
        Wpk[26][31][0] = ((Cik[31][2][0]*Wpk[26][30][2])+((Cik[31][0][0]*
          Wpk[26][30][0])+(Cik[31][1][0]*Wpk[26][30][1])));
        Wpk[26][31][1] = ((Cik[31][2][1]*Wpk[26][30][2])+((Cik[31][0][1]*
          Wpk[26][30][0])+(Cik[31][1][1]*Wpk[26][30][1])));
        Wpk[26][31][2] = ((Cik[31][2][2]*Wpk[26][30][2])+((Cik[31][0][2]*
          Wpk[26][30][0])+(Cik[31][1][2]*Wpk[26][30][1])));
        Wpk[26][32][0] = ((Cik[32][2][0]*Wpk[26][31][2])+((Cik[32][0][0]*
          Wpk[26][31][0])+(Cik[32][1][0]*Wpk[26][31][1])));
        Wpk[26][32][1] = ((Cik[32][2][1]*Wpk[26][31][2])+((Cik[32][0][1]*
          Wpk[26][31][0])+(Cik[32][1][1]*Wpk[26][31][1])));
        Wpk[26][32][2] = ((Cik[32][2][2]*Wpk[26][31][2])+((Cik[32][0][2]*
          Wpk[26][31][0])+(Cik[32][1][2]*Wpk[26][31][1])));
        Wpk[27][27][0] = pin[27][0];
        Wpk[27][27][1] = pin[27][1];
        Wpk[27][27][2] = pin[27][2];
        Wpk[27][28][0] = ((Cik[28][2][0]*pin[27][2])+((Cik[28][0][0]*pin[27][0])
          +(Cik[28][1][0]*pin[27][1])));
        Wpk[27][28][1] = ((Cik[28][2][1]*pin[27][2])+((Cik[28][0][1]*pin[27][0])
          +(Cik[28][1][1]*pin[27][1])));
        Wpk[27][28][2] = ((Cik[28][2][2]*pin[27][2])+((Cik[28][0][2]*pin[27][0])
          +(Cik[28][1][2]*pin[27][1])));
        Wpk[27][29][0] = ((Cik[29][2][0]*Wpk[27][28][2])+((Cik[29][0][0]*
          Wpk[27][28][0])+(Cik[29][1][0]*Wpk[27][28][1])));
        Wpk[27][29][1] = ((Cik[29][2][1]*Wpk[27][28][2])+((Cik[29][0][1]*
          Wpk[27][28][0])+(Cik[29][1][1]*Wpk[27][28][1])));
        Wpk[27][29][2] = ((Cik[29][2][2]*Wpk[27][28][2])+((Cik[29][0][2]*
          Wpk[27][28][0])+(Cik[29][1][2]*Wpk[27][28][1])));
        Wpk[27][30][0] = ((Cik[30][2][0]*Wpk[27][29][2])+((Cik[30][0][0]*
          Wpk[27][29][0])+(Cik[30][1][0]*Wpk[27][29][1])));
        Wpk[27][30][1] = ((Cik[30][2][1]*Wpk[27][29][2])+((Cik[30][0][1]*
          Wpk[27][29][0])+(Cik[30][1][1]*Wpk[27][29][1])));
        Wpk[27][30][2] = ((Cik[30][2][2]*Wpk[27][29][2])+((Cik[30][0][2]*
          Wpk[27][29][0])+(Cik[30][1][2]*Wpk[27][29][1])));
        Wpk[27][31][0] = ((Cik[31][2][0]*Wpk[27][30][2])+((Cik[31][0][0]*
          Wpk[27][30][0])+(Cik[31][1][0]*Wpk[27][30][1])));
        Wpk[27][31][1] = ((Cik[31][2][1]*Wpk[27][30][2])+((Cik[31][0][1]*
          Wpk[27][30][0])+(Cik[31][1][1]*Wpk[27][30][1])));
        Wpk[27][31][2] = ((Cik[31][2][2]*Wpk[27][30][2])+((Cik[31][0][2]*
          Wpk[27][30][0])+(Cik[31][1][2]*Wpk[27][30][1])));
        Wpk[27][32][0] = ((Cik[32][2][0]*Wpk[27][31][2])+((Cik[32][0][0]*
          Wpk[27][31][0])+(Cik[32][1][0]*Wpk[27][31][1])));
        Wpk[27][32][1] = ((Cik[32][2][1]*Wpk[27][31][2])+((Cik[32][0][1]*
          Wpk[27][31][0])+(Cik[32][1][1]*Wpk[27][31][1])));
        Wpk[27][32][2] = ((Cik[32][2][2]*Wpk[27][31][2])+((Cik[32][0][2]*
          Wpk[27][31][0])+(Cik[32][1][2]*Wpk[27][31][1])));
        Wpk[28][28][0] = pin[28][0];
        Wpk[28][28][1] = pin[28][1];
        Wpk[28][28][2] = pin[28][2];
        Wpk[28][29][0] = ((Cik[29][2][0]*pin[28][2])+((Cik[29][0][0]*pin[28][0])
          +(Cik[29][1][0]*pin[28][1])));
        Wpk[28][29][1] = ((Cik[29][2][1]*pin[28][2])+((Cik[29][0][1]*pin[28][0])
          +(Cik[29][1][1]*pin[28][1])));
        Wpk[28][29][2] = ((Cik[29][2][2]*pin[28][2])+((Cik[29][0][2]*pin[28][0])
          +(Cik[29][1][2]*pin[28][1])));
        Wpk[28][30][0] = ((Cik[30][2][0]*Wpk[28][29][2])+((Cik[30][0][0]*
          Wpk[28][29][0])+(Cik[30][1][0]*Wpk[28][29][1])));
        Wpk[28][30][1] = ((Cik[30][2][1]*Wpk[28][29][2])+((Cik[30][0][1]*
          Wpk[28][29][0])+(Cik[30][1][1]*Wpk[28][29][1])));
        Wpk[28][30][2] = ((Cik[30][2][2]*Wpk[28][29][2])+((Cik[30][0][2]*
          Wpk[28][29][0])+(Cik[30][1][2]*Wpk[28][29][1])));
        Wpk[28][31][0] = ((Cik[31][2][0]*Wpk[28][30][2])+((Cik[31][0][0]*
          Wpk[28][30][0])+(Cik[31][1][0]*Wpk[28][30][1])));
        Wpk[28][31][1] = ((Cik[31][2][1]*Wpk[28][30][2])+((Cik[31][0][1]*
          Wpk[28][30][0])+(Cik[31][1][1]*Wpk[28][30][1])));
        Wpk[28][31][2] = ((Cik[31][2][2]*Wpk[28][30][2])+((Cik[31][0][2]*
          Wpk[28][30][0])+(Cik[31][1][2]*Wpk[28][30][1])));
        Wpk[28][32][0] = ((Cik[32][2][0]*Wpk[28][31][2])+((Cik[32][0][0]*
          Wpk[28][31][0])+(Cik[32][1][0]*Wpk[28][31][1])));
        Wpk[28][32][1] = ((Cik[32][2][1]*Wpk[28][31][2])+((Cik[32][0][1]*
          Wpk[28][31][0])+(Cik[32][1][1]*Wpk[28][31][1])));
        Wpk[28][32][2] = ((Cik[32][2][2]*Wpk[28][31][2])+((Cik[32][0][2]*
          Wpk[28][31][0])+(Cik[32][1][2]*Wpk[28][31][1])));
        Wpk[29][29][0] = pin[29][0];
        Wpk[29][29][1] = pin[29][1];
        Wpk[29][29][2] = pin[29][2];
        Wpk[29][30][0] = ((Cik[30][2][0]*pin[29][2])+((Cik[30][0][0]*pin[29][0])
          +(Cik[30][1][0]*pin[29][1])));
        Wpk[29][30][1] = ((Cik[30][2][1]*pin[29][2])+((Cik[30][0][1]*pin[29][0])
          +(Cik[30][1][1]*pin[29][1])));
        Wpk[29][30][2] = ((Cik[30][2][2]*pin[29][2])+((Cik[30][0][2]*pin[29][0])
          +(Cik[30][1][2]*pin[29][1])));
        Wpk[29][31][0] = ((Cik[31][2][0]*Wpk[29][30][2])+((Cik[31][0][0]*
          Wpk[29][30][0])+(Cik[31][1][0]*Wpk[29][30][1])));
        Wpk[29][31][1] = ((Cik[31][2][1]*Wpk[29][30][2])+((Cik[31][0][1]*
          Wpk[29][30][0])+(Cik[31][1][1]*Wpk[29][30][1])));
        Wpk[29][31][2] = ((Cik[31][2][2]*Wpk[29][30][2])+((Cik[31][0][2]*
          Wpk[29][30][0])+(Cik[31][1][2]*Wpk[29][30][1])));
        Wpk[29][32][0] = ((Cik[32][2][0]*Wpk[29][31][2])+((Cik[32][0][0]*
          Wpk[29][31][0])+(Cik[32][1][0]*Wpk[29][31][1])));
        Wpk[29][32][1] = ((Cik[32][2][1]*Wpk[29][31][2])+((Cik[32][0][1]*
          Wpk[29][31][0])+(Cik[32][1][1]*Wpk[29][31][1])));
        Wpk[29][32][2] = ((Cik[32][2][2]*Wpk[29][31][2])+((Cik[32][0][2]*
          Wpk[29][31][0])+(Cik[32][1][2]*Wpk[29][31][1])));
        Wpk[30][30][0] = pin[30][0];
        Wpk[30][30][1] = pin[30][1];
        Wpk[30][30][2] = pin[30][2];
        Wpk[30][31][0] = ((Cik[31][2][0]*pin[30][2])+((Cik[31][0][0]*pin[30][0])
          +(Cik[31][1][0]*pin[30][1])));
        Wpk[30][31][1] = ((Cik[31][2][1]*pin[30][2])+((Cik[31][0][1]*pin[30][0])
          +(Cik[31][1][1]*pin[30][1])));
        Wpk[30][31][2] = ((Cik[31][2][2]*pin[30][2])+((Cik[31][0][2]*pin[30][0])
          +(Cik[31][1][2]*pin[30][1])));
        Wpk[30][32][0] = ((Cik[32][2][0]*Wpk[30][31][2])+((Cik[32][0][0]*
          Wpk[30][31][0])+(Cik[32][1][0]*Wpk[30][31][1])));
        Wpk[30][32][1] = ((Cik[32][2][1]*Wpk[30][31][2])+((Cik[32][0][1]*
          Wpk[30][31][0])+(Cik[32][1][1]*Wpk[30][31][1])));
        Wpk[30][32][2] = ((Cik[32][2][2]*Wpk[30][31][2])+((Cik[32][0][2]*
          Wpk[30][31][0])+(Cik[32][1][2]*Wpk[30][31][1])));
        Wpk[31][31][0] = pin[31][0];
        Wpk[31][31][1] = pin[31][1];
        Wpk[31][31][2] = pin[31][2];
        Wpk[31][32][0] = ((Cik[32][2][0]*pin[31][2])+((Cik[32][0][0]*pin[31][0])
          +(Cik[32][1][0]*pin[31][1])));
        Wpk[31][32][1] = ((Cik[32][2][1]*pin[31][2])+((Cik[32][0][1]*pin[31][0])
          +(Cik[32][1][1]*pin[31][1])));
        Wpk[31][32][2] = ((Cik[32][2][2]*pin[31][2])+((Cik[32][0][2]*pin[31][0])
          +(Cik[32][1][2]*pin[31][1])));
        Wpk[32][32][0] = pin[32][0];
        Wpk[32][32][1] = pin[32][1];
        Wpk[32][32][2] = pin[32][2];
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = pin[0][0];
        Vpk[0][0][1] = pin[0][1];
        Vpk[0][0][2] = pin[0][2];
        Vpk[0][1][0] = pin[0][0];
        Vpk[0][1][1] = pin[0][1];
        Vpk[0][1][2] = pin[0][2];
        Vpk[0][2][0] = pin[0][0];
        Vpk[0][2][1] = pin[0][1];
        Vpk[0][2][2] = pin[0][2];
        Vpk[0][3][0] = ((Cik[3][2][0]*pin[0][2])+((Cik[3][0][0]*pin[0][0])+(
          Cik[3][1][0]*pin[0][1])));
        Vpk[0][3][1] = ((Cik[3][2][1]*pin[0][2])+((Cik[3][0][1]*pin[0][0])+(
          Cik[3][1][1]*pin[0][1])));
        Vpk[0][3][2] = ((Cik[3][2][2]*pin[0][2])+((Cik[3][0][2]*pin[0][0])+(
          Cik[3][1][2]*pin[0][1])));
        Vpk[0][4][0] = Vpk[0][3][0];
        Vpk[0][4][1] = Vpk[0][3][1];
        Vpk[0][4][2] = Vpk[0][3][2];
        Vpk[0][5][0] = Vpk[0][3][0];
        Vpk[0][5][1] = Vpk[0][3][1];
        Vpk[0][5][2] = Vpk[0][3][2];
        Vpk[0][6][0] = ((Cik[6][2][0]*Vpk[0][3][2])+((Cik[6][0][0]*Vpk[0][3][0])
          +(Cik[6][1][0]*Vpk[0][3][1])));
        Vpk[0][6][1] = ((Cik[6][2][1]*Vpk[0][3][2])+((Cik[6][0][1]*Vpk[0][3][0])
          +(Cik[6][1][1]*Vpk[0][3][1])));
        Vpk[0][6][2] = ((Cik[6][2][2]*Vpk[0][3][2])+((Cik[6][0][2]*Vpk[0][3][0])
          +(Cik[6][1][2]*Vpk[0][3][1])));
        Vpk[0][7][0] = ((Cik[7][2][0]*Vpk[0][6][2])+((Cik[7][0][0]*Vpk[0][6][0])
          +(Cik[7][1][0]*Vpk[0][6][1])));
        Vpk[0][7][1] = ((Cik[7][2][1]*Vpk[0][6][2])+((Cik[7][0][1]*Vpk[0][6][0])
          +(Cik[7][1][1]*Vpk[0][6][1])));
        Vpk[0][7][2] = ((Cik[7][2][2]*Vpk[0][6][2])+((Cik[7][0][2]*Vpk[0][6][0])
          +(Cik[7][1][2]*Vpk[0][6][1])));
        Vpk[0][8][0] = ((Cik[8][2][0]*Vpk[0][7][2])+((Cik[8][0][0]*Vpk[0][7][0])
          +(Cik[8][1][0]*Vpk[0][7][1])));
        Vpk[0][8][1] = ((Cik[8][2][1]*Vpk[0][7][2])+((Cik[8][0][1]*Vpk[0][7][0])
          +(Cik[8][1][1]*Vpk[0][7][1])));
        Vpk[0][8][2] = ((Cik[8][2][2]*Vpk[0][7][2])+((Cik[8][0][2]*Vpk[0][7][0])
          +(Cik[8][1][2]*Vpk[0][7][1])));
        Vpk[0][9][0] = ((Cik[9][2][0]*Vpk[0][3][2])+((Cik[9][0][0]*Vpk[0][3][0])
          +(Cik[9][1][0]*Vpk[0][3][1])));
        Vpk[0][9][1] = ((Cik[9][2][1]*Vpk[0][3][2])+((Cik[9][0][1]*Vpk[0][3][0])
          +(Cik[9][1][1]*Vpk[0][3][1])));
        Vpk[0][9][2] = ((Cik[9][2][2]*Vpk[0][3][2])+((Cik[9][0][2]*Vpk[0][3][0])
          +(Cik[9][1][2]*Vpk[0][3][1])));
        Vpk[0][10][0] = ((Cik[10][2][0]*Vpk[0][9][2])+((Cik[10][0][0]*
          Vpk[0][9][0])+(Cik[10][1][0]*Vpk[0][9][1])));
        Vpk[0][10][1] = ((Cik[10][2][1]*Vpk[0][9][2])+((Cik[10][0][1]*
          Vpk[0][9][0])+(Cik[10][1][1]*Vpk[0][9][1])));
        Vpk[0][10][2] = ((Cik[10][2][2]*Vpk[0][9][2])+((Cik[10][0][2]*
          Vpk[0][9][0])+(Cik[10][1][2]*Vpk[0][9][1])));
        Vpk[0][11][0] = ((Cik[11][2][0]*Vpk[0][10][2])+((Cik[11][0][0]*
          Vpk[0][10][0])+(Cik[11][1][0]*Vpk[0][10][1])));
        Vpk[0][11][1] = ((Cik[11][2][1]*Vpk[0][10][2])+((Cik[11][0][1]*
          Vpk[0][10][0])+(Cik[11][1][1]*Vpk[0][10][1])));
        Vpk[0][11][2] = ((Cik[11][2][2]*Vpk[0][10][2])+((Cik[11][0][2]*
          Vpk[0][10][0])+(Cik[11][1][2]*Vpk[0][10][1])));
        Vpk[0][12][0] = ((Cik[12][2][0]*Vpk[0][11][2])+((Cik[12][0][0]*
          Vpk[0][11][0])+(Cik[12][1][0]*Vpk[0][11][1])));
        Vpk[0][12][1] = ((Cik[12][2][1]*Vpk[0][11][2])+((Cik[12][0][1]*
          Vpk[0][11][0])+(Cik[12][1][1]*Vpk[0][11][1])));
        Vpk[0][12][2] = ((Cik[12][2][2]*Vpk[0][11][2])+((Cik[12][0][2]*
          Vpk[0][11][0])+(Cik[12][1][2]*Vpk[0][11][1])));
        Vpk[0][13][0] = ((Cik[13][2][0]*Vpk[0][12][2])+((Cik[13][0][0]*
          Vpk[0][12][0])+(Cik[13][1][0]*Vpk[0][12][1])));
        Vpk[0][13][1] = ((Cik[13][2][1]*Vpk[0][12][2])+((Cik[13][0][1]*
          Vpk[0][12][0])+(Cik[13][1][1]*Vpk[0][12][1])));
        Vpk[0][13][2] = ((Cik[13][2][2]*Vpk[0][12][2])+((Cik[13][0][2]*
          Vpk[0][12][0])+(Cik[13][1][2]*Vpk[0][12][1])));
        Vpk[0][14][0] = ((Cik[14][2][0]*Vpk[0][13][2])+((Cik[14][0][0]*
          Vpk[0][13][0])+(Cik[14][1][0]*Vpk[0][13][1])));
        Vpk[0][14][1] = ((Cik[14][2][1]*Vpk[0][13][2])+((Cik[14][0][1]*
          Vpk[0][13][0])+(Cik[14][1][1]*Vpk[0][13][1])));
        Vpk[0][14][2] = ((Cik[14][2][2]*Vpk[0][13][2])+((Cik[14][0][2]*
          Vpk[0][13][0])+(Cik[14][1][2]*Vpk[0][13][1])));
        Vpk[0][15][0] = ((Cik[15][2][0]*Vpk[0][14][2])+((Cik[15][0][0]*
          Vpk[0][14][0])+(Cik[15][1][0]*Vpk[0][14][1])));
        Vpk[0][15][1] = ((Cik[15][2][1]*Vpk[0][14][2])+((Cik[15][0][1]*
          Vpk[0][14][0])+(Cik[15][1][1]*Vpk[0][14][1])));
        Vpk[0][15][2] = ((Cik[15][2][2]*Vpk[0][14][2])+((Cik[15][0][2]*
          Vpk[0][14][0])+(Cik[15][1][2]*Vpk[0][14][1])));
        Vpk[0][16][0] = ((Cik[16][2][0]*Vpk[0][15][2])+((Cik[16][0][0]*
          Vpk[0][15][0])+(Cik[16][1][0]*Vpk[0][15][1])));
        Vpk[0][16][1] = ((Cik[16][2][1]*Vpk[0][15][2])+((Cik[16][0][1]*
          Vpk[0][15][0])+(Cik[16][1][1]*Vpk[0][15][1])));
        Vpk[0][16][2] = ((Cik[16][2][2]*Vpk[0][15][2])+((Cik[16][0][2]*
          Vpk[0][15][0])+(Cik[16][1][2]*Vpk[0][15][1])));
        Vpk[0][17][0] = ((Cik[17][2][0]*Vpk[0][16][2])+((Cik[17][0][0]*
          Vpk[0][16][0])+(Cik[17][1][0]*Vpk[0][16][1])));
        Vpk[0][17][1] = ((Cik[17][2][1]*Vpk[0][16][2])+((Cik[17][0][1]*
          Vpk[0][16][0])+(Cik[17][1][1]*Vpk[0][16][1])));
        Vpk[0][17][2] = ((Cik[17][2][2]*Vpk[0][16][2])+((Cik[17][0][2]*
          Vpk[0][16][0])+(Cik[17][1][2]*Vpk[0][16][1])));
        Vpk[0][18][0] = ((Cik[18][2][0]*Vpk[0][17][2])+((Cik[18][0][0]*
          Vpk[0][17][0])+(Cik[18][1][0]*Vpk[0][17][1])));
        Vpk[0][18][1] = ((Cik[18][2][1]*Vpk[0][17][2])+((Cik[18][0][1]*
          Vpk[0][17][0])+(Cik[18][1][1]*Vpk[0][17][1])));
        Vpk[0][18][2] = ((Cik[18][2][2]*Vpk[0][17][2])+((Cik[18][0][2]*
          Vpk[0][17][0])+(Cik[18][1][2]*Vpk[0][17][1])));
        Vpk[0][19][0] = ((Cik[19][2][0]*Vpk[0][18][2])+((Cik[19][0][0]*
          Vpk[0][18][0])+(Cik[19][1][0]*Vpk[0][18][1])));
        Vpk[0][19][1] = ((Cik[19][2][1]*Vpk[0][18][2])+((Cik[19][0][1]*
          Vpk[0][18][0])+(Cik[19][1][1]*Vpk[0][18][1])));
        Vpk[0][19][2] = ((Cik[19][2][2]*Vpk[0][18][2])+((Cik[19][0][2]*
          Vpk[0][18][0])+(Cik[19][1][2]*Vpk[0][18][1])));
        Vpk[0][20][0] = ((Cik[20][2][0]*Vpk[0][19][2])+((Cik[20][0][0]*
          Vpk[0][19][0])+(Cik[20][1][0]*Vpk[0][19][1])));
        Vpk[0][20][1] = ((Cik[20][2][1]*Vpk[0][19][2])+((Cik[20][0][1]*
          Vpk[0][19][0])+(Cik[20][1][1]*Vpk[0][19][1])));
        Vpk[0][20][2] = ((Cik[20][2][2]*Vpk[0][19][2])+((Cik[20][0][2]*
          Vpk[0][19][0])+(Cik[20][1][2]*Vpk[0][19][1])));
        Vpk[0][21][0] = ((Cik[21][2][0]*Vpk[0][3][2])+((Cik[21][0][0]*
          Vpk[0][3][0])+(Cik[21][1][0]*Vpk[0][3][1])));
        Vpk[0][21][1] = ((Cik[21][2][1]*Vpk[0][3][2])+((Cik[21][0][1]*
          Vpk[0][3][0])+(Cik[21][1][1]*Vpk[0][3][1])));
        Vpk[0][21][2] = ((Cik[21][2][2]*Vpk[0][3][2])+((Cik[21][0][2]*
          Vpk[0][3][0])+(Cik[21][1][2]*Vpk[0][3][1])));
        Vpk[0][22][0] = ((Cik[22][2][0]*Vpk[0][21][2])+((Cik[22][0][0]*
          Vpk[0][21][0])+(Cik[22][1][0]*Vpk[0][21][1])));
        Vpk[0][22][1] = ((Cik[22][2][1]*Vpk[0][21][2])+((Cik[22][0][1]*
          Vpk[0][21][0])+(Cik[22][1][1]*Vpk[0][21][1])));
        Vpk[0][22][2] = ((Cik[22][2][2]*Vpk[0][21][2])+((Cik[22][0][2]*
          Vpk[0][21][0])+(Cik[22][1][2]*Vpk[0][21][1])));
        Vpk[0][23][0] = ((Cik[23][2][0]*Vpk[0][22][2])+((Cik[23][0][0]*
          Vpk[0][22][0])+(Cik[23][1][0]*Vpk[0][22][1])));
        Vpk[0][23][1] = ((Cik[23][2][1]*Vpk[0][22][2])+((Cik[23][0][1]*
          Vpk[0][22][0])+(Cik[23][1][1]*Vpk[0][22][1])));
        Vpk[0][23][2] = ((Cik[23][2][2]*Vpk[0][22][2])+((Cik[23][0][2]*
          Vpk[0][22][0])+(Cik[23][1][2]*Vpk[0][22][1])));
        Vpk[0][24][0] = ((Cik[24][2][0]*Vpk[0][23][2])+((Cik[24][0][0]*
          Vpk[0][23][0])+(Cik[24][1][0]*Vpk[0][23][1])));
        Vpk[0][24][1] = ((Cik[24][2][1]*Vpk[0][23][2])+((Cik[24][0][1]*
          Vpk[0][23][0])+(Cik[24][1][1]*Vpk[0][23][1])));
        Vpk[0][24][2] = ((Cik[24][2][2]*Vpk[0][23][2])+((Cik[24][0][2]*
          Vpk[0][23][0])+(Cik[24][1][2]*Vpk[0][23][1])));
        Vpk[0][25][0] = ((Cik[25][2][0]*Vpk[0][24][2])+((Cik[25][0][0]*
          Vpk[0][24][0])+(Cik[25][1][0]*Vpk[0][24][1])));
        Vpk[0][25][1] = ((Cik[25][2][1]*Vpk[0][24][2])+((Cik[25][0][1]*
          Vpk[0][24][0])+(Cik[25][1][1]*Vpk[0][24][1])));
        Vpk[0][25][2] = ((Cik[25][2][2]*Vpk[0][24][2])+((Cik[25][0][2]*
          Vpk[0][24][0])+(Cik[25][1][2]*Vpk[0][24][1])));
        Vpk[0][26][0] = ((Cik[26][2][0]*Vpk[0][25][2])+((Cik[26][0][0]*
          Vpk[0][25][0])+(Cik[26][1][0]*Vpk[0][25][1])));
        Vpk[0][26][1] = ((Cik[26][2][1]*Vpk[0][25][2])+((Cik[26][0][1]*
          Vpk[0][25][0])+(Cik[26][1][1]*Vpk[0][25][1])));
        Vpk[0][26][2] = ((Cik[26][2][2]*Vpk[0][25][2])+((Cik[26][0][2]*
          Vpk[0][25][0])+(Cik[26][1][2]*Vpk[0][25][1])));
        Vpk[0][27][0] = ((Cik[27][2][0]*Vpk[0][26][2])+((Cik[27][0][0]*
          Vpk[0][26][0])+(Cik[27][1][0]*Vpk[0][26][1])));
        Vpk[0][27][1] = ((Cik[27][2][1]*Vpk[0][26][2])+((Cik[27][0][1]*
          Vpk[0][26][0])+(Cik[27][1][1]*Vpk[0][26][1])));
        Vpk[0][27][2] = ((Cik[27][2][2]*Vpk[0][26][2])+((Cik[27][0][2]*
          Vpk[0][26][0])+(Cik[27][1][2]*Vpk[0][26][1])));
        Vpk[0][28][0] = ((Cik[28][2][0]*Vpk[0][27][2])+((Cik[28][0][0]*
          Vpk[0][27][0])+(Cik[28][1][0]*Vpk[0][27][1])));
        Vpk[0][28][1] = ((Cik[28][2][1]*Vpk[0][27][2])+((Cik[28][0][1]*
          Vpk[0][27][0])+(Cik[28][1][1]*Vpk[0][27][1])));
        Vpk[0][28][2] = ((Cik[28][2][2]*Vpk[0][27][2])+((Cik[28][0][2]*
          Vpk[0][27][0])+(Cik[28][1][2]*Vpk[0][27][1])));
        Vpk[0][29][0] = ((Cik[29][2][0]*Vpk[0][28][2])+((Cik[29][0][0]*
          Vpk[0][28][0])+(Cik[29][1][0]*Vpk[0][28][1])));
        Vpk[0][29][1] = ((Cik[29][2][1]*Vpk[0][28][2])+((Cik[29][0][1]*
          Vpk[0][28][0])+(Cik[29][1][1]*Vpk[0][28][1])));
        Vpk[0][29][2] = ((Cik[29][2][2]*Vpk[0][28][2])+((Cik[29][0][2]*
          Vpk[0][28][0])+(Cik[29][1][2]*Vpk[0][28][1])));
        Vpk[0][30][0] = ((Cik[30][2][0]*Vpk[0][29][2])+((Cik[30][0][0]*
          Vpk[0][29][0])+(Cik[30][1][0]*Vpk[0][29][1])));
        Vpk[0][30][1] = ((Cik[30][2][1]*Vpk[0][29][2])+((Cik[30][0][1]*
          Vpk[0][29][0])+(Cik[30][1][1]*Vpk[0][29][1])));
        Vpk[0][30][2] = ((Cik[30][2][2]*Vpk[0][29][2])+((Cik[30][0][2]*
          Vpk[0][29][0])+(Cik[30][1][2]*Vpk[0][29][1])));
        Vpk[0][31][0] = ((Cik[31][2][0]*Vpk[0][30][2])+((Cik[31][0][0]*
          Vpk[0][30][0])+(Cik[31][1][0]*Vpk[0][30][1])));
        Vpk[0][31][1] = ((Cik[31][2][1]*Vpk[0][30][2])+((Cik[31][0][1]*
          Vpk[0][30][0])+(Cik[31][1][1]*Vpk[0][30][1])));
        Vpk[0][31][2] = ((Cik[31][2][2]*Vpk[0][30][2])+((Cik[31][0][2]*
          Vpk[0][30][0])+(Cik[31][1][2]*Vpk[0][30][1])));
        Vpk[0][32][0] = ((Cik[32][2][0]*Vpk[0][31][2])+((Cik[32][0][0]*
          Vpk[0][31][0])+(Cik[32][1][0]*Vpk[0][31][1])));
        Vpk[0][32][1] = ((Cik[32][2][1]*Vpk[0][31][2])+((Cik[32][0][1]*
          Vpk[0][31][0])+(Cik[32][1][1]*Vpk[0][31][1])));
        Vpk[0][32][2] = ((Cik[32][2][2]*Vpk[0][31][2])+((Cik[32][0][2]*
          Vpk[0][31][0])+(Cik[32][1][2]*Vpk[0][31][1])));
        Vpk[1][1][0] = pin[1][0];
        Vpk[1][1][1] = pin[1][1];
        Vpk[1][1][2] = pin[1][2];
        Vpk[1][2][0] = pin[1][0];
        Vpk[1][2][1] = pin[1][1];
        Vpk[1][2][2] = pin[1][2];
        Vpk[1][3][0] = ((Cik[3][2][0]*pin[1][2])+((Cik[3][0][0]*pin[1][0])+(
          Cik[3][1][0]*pin[1][1])));
        Vpk[1][3][1] = ((Cik[3][2][1]*pin[1][2])+((Cik[3][0][1]*pin[1][0])+(
          Cik[3][1][1]*pin[1][1])));
        Vpk[1][3][2] = ((Cik[3][2][2]*pin[1][2])+((Cik[3][0][2]*pin[1][0])+(
          Cik[3][1][2]*pin[1][1])));
        Vpk[1][4][0] = Vpk[1][3][0];
        Vpk[1][4][1] = Vpk[1][3][1];
        Vpk[1][4][2] = Vpk[1][3][2];
        Vpk[1][5][0] = Vpk[1][3][0];
        Vpk[1][5][1] = Vpk[1][3][1];
        Vpk[1][5][2] = Vpk[1][3][2];
        Vpk[1][6][0] = ((Cik[6][2][0]*Vpk[1][3][2])+((Cik[6][0][0]*Vpk[1][3][0])
          +(Cik[6][1][0]*Vpk[1][3][1])));
        Vpk[1][6][1] = ((Cik[6][2][1]*Vpk[1][3][2])+((Cik[6][0][1]*Vpk[1][3][0])
          +(Cik[6][1][1]*Vpk[1][3][1])));
        Vpk[1][6][2] = ((Cik[6][2][2]*Vpk[1][3][2])+((Cik[6][0][2]*Vpk[1][3][0])
          +(Cik[6][1][2]*Vpk[1][3][1])));
        Vpk[1][7][0] = ((Cik[7][2][0]*Vpk[1][6][2])+((Cik[7][0][0]*Vpk[1][6][0])
          +(Cik[7][1][0]*Vpk[1][6][1])));
        Vpk[1][7][1] = ((Cik[7][2][1]*Vpk[1][6][2])+((Cik[7][0][1]*Vpk[1][6][0])
          +(Cik[7][1][1]*Vpk[1][6][1])));
        Vpk[1][7][2] = ((Cik[7][2][2]*Vpk[1][6][2])+((Cik[7][0][2]*Vpk[1][6][0])
          +(Cik[7][1][2]*Vpk[1][6][1])));
        Vpk[1][8][0] = ((Cik[8][2][0]*Vpk[1][7][2])+((Cik[8][0][0]*Vpk[1][7][0])
          +(Cik[8][1][0]*Vpk[1][7][1])));
        Vpk[1][8][1] = ((Cik[8][2][1]*Vpk[1][7][2])+((Cik[8][0][1]*Vpk[1][7][0])
          +(Cik[8][1][1]*Vpk[1][7][1])));
        Vpk[1][8][2] = ((Cik[8][2][2]*Vpk[1][7][2])+((Cik[8][0][2]*Vpk[1][7][0])
          +(Cik[8][1][2]*Vpk[1][7][1])));
        Vpk[1][9][0] = ((Cik[9][2][0]*Vpk[1][3][2])+((Cik[9][0][0]*Vpk[1][3][0])
          +(Cik[9][1][0]*Vpk[1][3][1])));
        Vpk[1][9][1] = ((Cik[9][2][1]*Vpk[1][3][2])+((Cik[9][0][1]*Vpk[1][3][0])
          +(Cik[9][1][1]*Vpk[1][3][1])));
        Vpk[1][9][2] = ((Cik[9][2][2]*Vpk[1][3][2])+((Cik[9][0][2]*Vpk[1][3][0])
          +(Cik[9][1][2]*Vpk[1][3][1])));
        Vpk[1][10][0] = ((Cik[10][2][0]*Vpk[1][9][2])+((Cik[10][0][0]*
          Vpk[1][9][0])+(Cik[10][1][0]*Vpk[1][9][1])));
        Vpk[1][10][1] = ((Cik[10][2][1]*Vpk[1][9][2])+((Cik[10][0][1]*
          Vpk[1][9][0])+(Cik[10][1][1]*Vpk[1][9][1])));
        Vpk[1][10][2] = ((Cik[10][2][2]*Vpk[1][9][2])+((Cik[10][0][2]*
          Vpk[1][9][0])+(Cik[10][1][2]*Vpk[1][9][1])));
        Vpk[1][11][0] = ((Cik[11][2][0]*Vpk[1][10][2])+((Cik[11][0][0]*
          Vpk[1][10][0])+(Cik[11][1][0]*Vpk[1][10][1])));
        Vpk[1][11][1] = ((Cik[11][2][1]*Vpk[1][10][2])+((Cik[11][0][1]*
          Vpk[1][10][0])+(Cik[11][1][1]*Vpk[1][10][1])));
        Vpk[1][11][2] = ((Cik[11][2][2]*Vpk[1][10][2])+((Cik[11][0][2]*
          Vpk[1][10][0])+(Cik[11][1][2]*Vpk[1][10][1])));
        Vpk[1][12][0] = ((Cik[12][2][0]*Vpk[1][11][2])+((Cik[12][0][0]*
          Vpk[1][11][0])+(Cik[12][1][0]*Vpk[1][11][1])));
        Vpk[1][12][1] = ((Cik[12][2][1]*Vpk[1][11][2])+((Cik[12][0][1]*
          Vpk[1][11][0])+(Cik[12][1][1]*Vpk[1][11][1])));
        Vpk[1][12][2] = ((Cik[12][2][2]*Vpk[1][11][2])+((Cik[12][0][2]*
          Vpk[1][11][0])+(Cik[12][1][2]*Vpk[1][11][1])));
        Vpk[1][13][0] = ((Cik[13][2][0]*Vpk[1][12][2])+((Cik[13][0][0]*
          Vpk[1][12][0])+(Cik[13][1][0]*Vpk[1][12][1])));
        Vpk[1][13][1] = ((Cik[13][2][1]*Vpk[1][12][2])+((Cik[13][0][1]*
          Vpk[1][12][0])+(Cik[13][1][1]*Vpk[1][12][1])));
        Vpk[1][13][2] = ((Cik[13][2][2]*Vpk[1][12][2])+((Cik[13][0][2]*
          Vpk[1][12][0])+(Cik[13][1][2]*Vpk[1][12][1])));
        Vpk[1][14][0] = ((Cik[14][2][0]*Vpk[1][13][2])+((Cik[14][0][0]*
          Vpk[1][13][0])+(Cik[14][1][0]*Vpk[1][13][1])));
        Vpk[1][14][1] = ((Cik[14][2][1]*Vpk[1][13][2])+((Cik[14][0][1]*
          Vpk[1][13][0])+(Cik[14][1][1]*Vpk[1][13][1])));
        Vpk[1][14][2] = ((Cik[14][2][2]*Vpk[1][13][2])+((Cik[14][0][2]*
          Vpk[1][13][0])+(Cik[14][1][2]*Vpk[1][13][1])));
        Vpk[1][15][0] = ((Cik[15][2][0]*Vpk[1][14][2])+((Cik[15][0][0]*
          Vpk[1][14][0])+(Cik[15][1][0]*Vpk[1][14][1])));
        Vpk[1][15][1] = ((Cik[15][2][1]*Vpk[1][14][2])+((Cik[15][0][1]*
          Vpk[1][14][0])+(Cik[15][1][1]*Vpk[1][14][1])));
        Vpk[1][15][2] = ((Cik[15][2][2]*Vpk[1][14][2])+((Cik[15][0][2]*
          Vpk[1][14][0])+(Cik[15][1][2]*Vpk[1][14][1])));
        Vpk[1][16][0] = ((Cik[16][2][0]*Vpk[1][15][2])+((Cik[16][0][0]*
          Vpk[1][15][0])+(Cik[16][1][0]*Vpk[1][15][1])));
        Vpk[1][16][1] = ((Cik[16][2][1]*Vpk[1][15][2])+((Cik[16][0][1]*
          Vpk[1][15][0])+(Cik[16][1][1]*Vpk[1][15][1])));
        Vpk[1][16][2] = ((Cik[16][2][2]*Vpk[1][15][2])+((Cik[16][0][2]*
          Vpk[1][15][0])+(Cik[16][1][2]*Vpk[1][15][1])));
        Vpk[1][17][0] = ((Cik[17][2][0]*Vpk[1][16][2])+((Cik[17][0][0]*
          Vpk[1][16][0])+(Cik[17][1][0]*Vpk[1][16][1])));
        Vpk[1][17][1] = ((Cik[17][2][1]*Vpk[1][16][2])+((Cik[17][0][1]*
          Vpk[1][16][0])+(Cik[17][1][1]*Vpk[1][16][1])));
        Vpk[1][17][2] = ((Cik[17][2][2]*Vpk[1][16][2])+((Cik[17][0][2]*
          Vpk[1][16][0])+(Cik[17][1][2]*Vpk[1][16][1])));
        Vpk[1][18][0] = ((Cik[18][2][0]*Vpk[1][17][2])+((Cik[18][0][0]*
          Vpk[1][17][0])+(Cik[18][1][0]*Vpk[1][17][1])));
        Vpk[1][18][1] = ((Cik[18][2][1]*Vpk[1][17][2])+((Cik[18][0][1]*
          Vpk[1][17][0])+(Cik[18][1][1]*Vpk[1][17][1])));
        Vpk[1][18][2] = ((Cik[18][2][2]*Vpk[1][17][2])+((Cik[18][0][2]*
          Vpk[1][17][0])+(Cik[18][1][2]*Vpk[1][17][1])));
        Vpk[1][19][0] = ((Cik[19][2][0]*Vpk[1][18][2])+((Cik[19][0][0]*
          Vpk[1][18][0])+(Cik[19][1][0]*Vpk[1][18][1])));
        Vpk[1][19][1] = ((Cik[19][2][1]*Vpk[1][18][2])+((Cik[19][0][1]*
          Vpk[1][18][0])+(Cik[19][1][1]*Vpk[1][18][1])));
        Vpk[1][19][2] = ((Cik[19][2][2]*Vpk[1][18][2])+((Cik[19][0][2]*
          Vpk[1][18][0])+(Cik[19][1][2]*Vpk[1][18][1])));
        Vpk[1][20][0] = ((Cik[20][2][0]*Vpk[1][19][2])+((Cik[20][0][0]*
          Vpk[1][19][0])+(Cik[20][1][0]*Vpk[1][19][1])));
        Vpk[1][20][1] = ((Cik[20][2][1]*Vpk[1][19][2])+((Cik[20][0][1]*
          Vpk[1][19][0])+(Cik[20][1][1]*Vpk[1][19][1])));
        Vpk[1][20][2] = ((Cik[20][2][2]*Vpk[1][19][2])+((Cik[20][0][2]*
          Vpk[1][19][0])+(Cik[20][1][2]*Vpk[1][19][1])));
        Vpk[1][21][0] = ((Cik[21][2][0]*Vpk[1][3][2])+((Cik[21][0][0]*
          Vpk[1][3][0])+(Cik[21][1][0]*Vpk[1][3][1])));
        Vpk[1][21][1] = ((Cik[21][2][1]*Vpk[1][3][2])+((Cik[21][0][1]*
          Vpk[1][3][0])+(Cik[21][1][1]*Vpk[1][3][1])));
        Vpk[1][21][2] = ((Cik[21][2][2]*Vpk[1][3][2])+((Cik[21][0][2]*
          Vpk[1][3][0])+(Cik[21][1][2]*Vpk[1][3][1])));
        Vpk[1][22][0] = ((Cik[22][2][0]*Vpk[1][21][2])+((Cik[22][0][0]*
          Vpk[1][21][0])+(Cik[22][1][0]*Vpk[1][21][1])));
        Vpk[1][22][1] = ((Cik[22][2][1]*Vpk[1][21][2])+((Cik[22][0][1]*
          Vpk[1][21][0])+(Cik[22][1][1]*Vpk[1][21][1])));
        Vpk[1][22][2] = ((Cik[22][2][2]*Vpk[1][21][2])+((Cik[22][0][2]*
          Vpk[1][21][0])+(Cik[22][1][2]*Vpk[1][21][1])));
        Vpk[1][23][0] = ((Cik[23][2][0]*Vpk[1][22][2])+((Cik[23][0][0]*
          Vpk[1][22][0])+(Cik[23][1][0]*Vpk[1][22][1])));
        Vpk[1][23][1] = ((Cik[23][2][1]*Vpk[1][22][2])+((Cik[23][0][1]*
          Vpk[1][22][0])+(Cik[23][1][1]*Vpk[1][22][1])));
        Vpk[1][23][2] = ((Cik[23][2][2]*Vpk[1][22][2])+((Cik[23][0][2]*
          Vpk[1][22][0])+(Cik[23][1][2]*Vpk[1][22][1])));
        Vpk[1][24][0] = ((Cik[24][2][0]*Vpk[1][23][2])+((Cik[24][0][0]*
          Vpk[1][23][0])+(Cik[24][1][0]*Vpk[1][23][1])));
        Vpk[1][24][1] = ((Cik[24][2][1]*Vpk[1][23][2])+((Cik[24][0][1]*
          Vpk[1][23][0])+(Cik[24][1][1]*Vpk[1][23][1])));
        Vpk[1][24][2] = ((Cik[24][2][2]*Vpk[1][23][2])+((Cik[24][0][2]*
          Vpk[1][23][0])+(Cik[24][1][2]*Vpk[1][23][1])));
        Vpk[1][25][0] = ((Cik[25][2][0]*Vpk[1][24][2])+((Cik[25][0][0]*
          Vpk[1][24][0])+(Cik[25][1][0]*Vpk[1][24][1])));
        Vpk[1][25][1] = ((Cik[25][2][1]*Vpk[1][24][2])+((Cik[25][0][1]*
          Vpk[1][24][0])+(Cik[25][1][1]*Vpk[1][24][1])));
        Vpk[1][25][2] = ((Cik[25][2][2]*Vpk[1][24][2])+((Cik[25][0][2]*
          Vpk[1][24][0])+(Cik[25][1][2]*Vpk[1][24][1])));
        Vpk[1][26][0] = ((Cik[26][2][0]*Vpk[1][25][2])+((Cik[26][0][0]*
          Vpk[1][25][0])+(Cik[26][1][0]*Vpk[1][25][1])));
        Vpk[1][26][1] = ((Cik[26][2][1]*Vpk[1][25][2])+((Cik[26][0][1]*
          Vpk[1][25][0])+(Cik[26][1][1]*Vpk[1][25][1])));
        Vpk[1][26][2] = ((Cik[26][2][2]*Vpk[1][25][2])+((Cik[26][0][2]*
          Vpk[1][25][0])+(Cik[26][1][2]*Vpk[1][25][1])));
        Vpk[1][27][0] = ((Cik[27][2][0]*Vpk[1][26][2])+((Cik[27][0][0]*
          Vpk[1][26][0])+(Cik[27][1][0]*Vpk[1][26][1])));
        Vpk[1][27][1] = ((Cik[27][2][1]*Vpk[1][26][2])+((Cik[27][0][1]*
          Vpk[1][26][0])+(Cik[27][1][1]*Vpk[1][26][1])));
        Vpk[1][27][2] = ((Cik[27][2][2]*Vpk[1][26][2])+((Cik[27][0][2]*
          Vpk[1][26][0])+(Cik[27][1][2]*Vpk[1][26][1])));
        Vpk[1][28][0] = ((Cik[28][2][0]*Vpk[1][27][2])+((Cik[28][0][0]*
          Vpk[1][27][0])+(Cik[28][1][0]*Vpk[1][27][1])));
        Vpk[1][28][1] = ((Cik[28][2][1]*Vpk[1][27][2])+((Cik[28][0][1]*
          Vpk[1][27][0])+(Cik[28][1][1]*Vpk[1][27][1])));
        Vpk[1][28][2] = ((Cik[28][2][2]*Vpk[1][27][2])+((Cik[28][0][2]*
          Vpk[1][27][0])+(Cik[28][1][2]*Vpk[1][27][1])));
        Vpk[1][29][0] = ((Cik[29][2][0]*Vpk[1][28][2])+((Cik[29][0][0]*
          Vpk[1][28][0])+(Cik[29][1][0]*Vpk[1][28][1])));
        Vpk[1][29][1] = ((Cik[29][2][1]*Vpk[1][28][2])+((Cik[29][0][1]*
          Vpk[1][28][0])+(Cik[29][1][1]*Vpk[1][28][1])));
        Vpk[1][29][2] = ((Cik[29][2][2]*Vpk[1][28][2])+((Cik[29][0][2]*
          Vpk[1][28][0])+(Cik[29][1][2]*Vpk[1][28][1])));
        Vpk[1][30][0] = ((Cik[30][2][0]*Vpk[1][29][2])+((Cik[30][0][0]*
          Vpk[1][29][0])+(Cik[30][1][0]*Vpk[1][29][1])));
        Vpk[1][30][1] = ((Cik[30][2][1]*Vpk[1][29][2])+((Cik[30][0][1]*
          Vpk[1][29][0])+(Cik[30][1][1]*Vpk[1][29][1])));
        Vpk[1][30][2] = ((Cik[30][2][2]*Vpk[1][29][2])+((Cik[30][0][2]*
          Vpk[1][29][0])+(Cik[30][1][2]*Vpk[1][29][1])));
        Vpk[1][31][0] = ((Cik[31][2][0]*Vpk[1][30][2])+((Cik[31][0][0]*
          Vpk[1][30][0])+(Cik[31][1][0]*Vpk[1][30][1])));
        Vpk[1][31][1] = ((Cik[31][2][1]*Vpk[1][30][2])+((Cik[31][0][1]*
          Vpk[1][30][0])+(Cik[31][1][1]*Vpk[1][30][1])));
        Vpk[1][31][2] = ((Cik[31][2][2]*Vpk[1][30][2])+((Cik[31][0][2]*
          Vpk[1][30][0])+(Cik[31][1][2]*Vpk[1][30][1])));
        Vpk[1][32][0] = ((Cik[32][2][0]*Vpk[1][31][2])+((Cik[32][0][0]*
          Vpk[1][31][0])+(Cik[32][1][0]*Vpk[1][31][1])));
        Vpk[1][32][1] = ((Cik[32][2][1]*Vpk[1][31][2])+((Cik[32][0][1]*
          Vpk[1][31][0])+(Cik[32][1][1]*Vpk[1][31][1])));
        Vpk[1][32][2] = ((Cik[32][2][2]*Vpk[1][31][2])+((Cik[32][0][2]*
          Vpk[1][31][0])+(Cik[32][1][2]*Vpk[1][31][1])));
        Vpk[2][2][0] = pin[2][0];
        Vpk[2][2][1] = pin[2][1];
        Vpk[2][2][2] = pin[2][2];
        Vpk[2][3][0] = ((Cik[3][2][0]*pin[2][2])+((Cik[3][0][0]*pin[2][0])+(
          Cik[3][1][0]*pin[2][1])));
        Vpk[2][3][1] = ((Cik[3][2][1]*pin[2][2])+((Cik[3][0][1]*pin[2][0])+(
          Cik[3][1][1]*pin[2][1])));
        Vpk[2][3][2] = ((Cik[3][2][2]*pin[2][2])+((Cik[3][0][2]*pin[2][0])+(
          Cik[3][1][2]*pin[2][1])));
        Vpk[2][4][0] = Vpk[2][3][0];
        Vpk[2][4][1] = Vpk[2][3][1];
        Vpk[2][4][2] = Vpk[2][3][2];
        Vpk[2][5][0] = Vpk[2][3][0];
        Vpk[2][5][1] = Vpk[2][3][1];
        Vpk[2][5][2] = Vpk[2][3][2];
        Vpk[2][6][0] = ((Cik[6][2][0]*Vpk[2][3][2])+((Cik[6][0][0]*Vpk[2][3][0])
          +(Cik[6][1][0]*Vpk[2][3][1])));
        Vpk[2][6][1] = ((Cik[6][2][1]*Vpk[2][3][2])+((Cik[6][0][1]*Vpk[2][3][0])
          +(Cik[6][1][1]*Vpk[2][3][1])));
        Vpk[2][6][2] = ((Cik[6][2][2]*Vpk[2][3][2])+((Cik[6][0][2]*Vpk[2][3][0])
          +(Cik[6][1][2]*Vpk[2][3][1])));
        Vpk[2][7][0] = ((Cik[7][2][0]*Vpk[2][6][2])+((Cik[7][0][0]*Vpk[2][6][0])
          +(Cik[7][1][0]*Vpk[2][6][1])));
        Vpk[2][7][1] = ((Cik[7][2][1]*Vpk[2][6][2])+((Cik[7][0][1]*Vpk[2][6][0])
          +(Cik[7][1][1]*Vpk[2][6][1])));
        Vpk[2][7][2] = ((Cik[7][2][2]*Vpk[2][6][2])+((Cik[7][0][2]*Vpk[2][6][0])
          +(Cik[7][1][2]*Vpk[2][6][1])));
        Vpk[2][8][0] = ((Cik[8][2][0]*Vpk[2][7][2])+((Cik[8][0][0]*Vpk[2][7][0])
          +(Cik[8][1][0]*Vpk[2][7][1])));
        Vpk[2][8][1] = ((Cik[8][2][1]*Vpk[2][7][2])+((Cik[8][0][1]*Vpk[2][7][0])
          +(Cik[8][1][1]*Vpk[2][7][1])));
        Vpk[2][8][2] = ((Cik[8][2][2]*Vpk[2][7][2])+((Cik[8][0][2]*Vpk[2][7][0])
          +(Cik[8][1][2]*Vpk[2][7][1])));
        Vpk[2][9][0] = ((Cik[9][2][0]*Vpk[2][3][2])+((Cik[9][0][0]*Vpk[2][3][0])
          +(Cik[9][1][0]*Vpk[2][3][1])));
        Vpk[2][9][1] = ((Cik[9][2][1]*Vpk[2][3][2])+((Cik[9][0][1]*Vpk[2][3][0])
          +(Cik[9][1][1]*Vpk[2][3][1])));
        Vpk[2][9][2] = ((Cik[9][2][2]*Vpk[2][3][2])+((Cik[9][0][2]*Vpk[2][3][0])
          +(Cik[9][1][2]*Vpk[2][3][1])));
        Vpk[2][10][0] = ((Cik[10][2][0]*Vpk[2][9][2])+((Cik[10][0][0]*
          Vpk[2][9][0])+(Cik[10][1][0]*Vpk[2][9][1])));
        Vpk[2][10][1] = ((Cik[10][2][1]*Vpk[2][9][2])+((Cik[10][0][1]*
          Vpk[2][9][0])+(Cik[10][1][1]*Vpk[2][9][1])));
        Vpk[2][10][2] = ((Cik[10][2][2]*Vpk[2][9][2])+((Cik[10][0][2]*
          Vpk[2][9][0])+(Cik[10][1][2]*Vpk[2][9][1])));
        Vpk[2][11][0] = ((Cik[11][2][0]*Vpk[2][10][2])+((Cik[11][0][0]*
          Vpk[2][10][0])+(Cik[11][1][0]*Vpk[2][10][1])));
        Vpk[2][11][1] = ((Cik[11][2][1]*Vpk[2][10][2])+((Cik[11][0][1]*
          Vpk[2][10][0])+(Cik[11][1][1]*Vpk[2][10][1])));
        Vpk[2][11][2] = ((Cik[11][2][2]*Vpk[2][10][2])+((Cik[11][0][2]*
          Vpk[2][10][0])+(Cik[11][1][2]*Vpk[2][10][1])));
        Vpk[2][12][0] = ((Cik[12][2][0]*Vpk[2][11][2])+((Cik[12][0][0]*
          Vpk[2][11][0])+(Cik[12][1][0]*Vpk[2][11][1])));
        Vpk[2][12][1] = ((Cik[12][2][1]*Vpk[2][11][2])+((Cik[12][0][1]*
          Vpk[2][11][0])+(Cik[12][1][1]*Vpk[2][11][1])));
        Vpk[2][12][2] = ((Cik[12][2][2]*Vpk[2][11][2])+((Cik[12][0][2]*
          Vpk[2][11][0])+(Cik[12][1][2]*Vpk[2][11][1])));
        Vpk[2][13][0] = ((Cik[13][2][0]*Vpk[2][12][2])+((Cik[13][0][0]*
          Vpk[2][12][0])+(Cik[13][1][0]*Vpk[2][12][1])));
        Vpk[2][13][1] = ((Cik[13][2][1]*Vpk[2][12][2])+((Cik[13][0][1]*
          Vpk[2][12][0])+(Cik[13][1][1]*Vpk[2][12][1])));
        Vpk[2][13][2] = ((Cik[13][2][2]*Vpk[2][12][2])+((Cik[13][0][2]*
          Vpk[2][12][0])+(Cik[13][1][2]*Vpk[2][12][1])));
        Vpk[2][14][0] = ((Cik[14][2][0]*Vpk[2][13][2])+((Cik[14][0][0]*
          Vpk[2][13][0])+(Cik[14][1][0]*Vpk[2][13][1])));
        Vpk[2][14][1] = ((Cik[14][2][1]*Vpk[2][13][2])+((Cik[14][0][1]*
          Vpk[2][13][0])+(Cik[14][1][1]*Vpk[2][13][1])));
        Vpk[2][14][2] = ((Cik[14][2][2]*Vpk[2][13][2])+((Cik[14][0][2]*
          Vpk[2][13][0])+(Cik[14][1][2]*Vpk[2][13][1])));
        Vpk[2][15][0] = ((Cik[15][2][0]*Vpk[2][14][2])+((Cik[15][0][0]*
          Vpk[2][14][0])+(Cik[15][1][0]*Vpk[2][14][1])));
        Vpk[2][15][1] = ((Cik[15][2][1]*Vpk[2][14][2])+((Cik[15][0][1]*
          Vpk[2][14][0])+(Cik[15][1][1]*Vpk[2][14][1])));
        Vpk[2][15][2] = ((Cik[15][2][2]*Vpk[2][14][2])+((Cik[15][0][2]*
          Vpk[2][14][0])+(Cik[15][1][2]*Vpk[2][14][1])));
        Vpk[2][16][0] = ((Cik[16][2][0]*Vpk[2][15][2])+((Cik[16][0][0]*
          Vpk[2][15][0])+(Cik[16][1][0]*Vpk[2][15][1])));
        Vpk[2][16][1] = ((Cik[16][2][1]*Vpk[2][15][2])+((Cik[16][0][1]*
          Vpk[2][15][0])+(Cik[16][1][1]*Vpk[2][15][1])));
        Vpk[2][16][2] = ((Cik[16][2][2]*Vpk[2][15][2])+((Cik[16][0][2]*
          Vpk[2][15][0])+(Cik[16][1][2]*Vpk[2][15][1])));
        Vpk[2][17][0] = ((Cik[17][2][0]*Vpk[2][16][2])+((Cik[17][0][0]*
          Vpk[2][16][0])+(Cik[17][1][0]*Vpk[2][16][1])));
        Vpk[2][17][1] = ((Cik[17][2][1]*Vpk[2][16][2])+((Cik[17][0][1]*
          Vpk[2][16][0])+(Cik[17][1][1]*Vpk[2][16][1])));
        Vpk[2][17][2] = ((Cik[17][2][2]*Vpk[2][16][2])+((Cik[17][0][2]*
          Vpk[2][16][0])+(Cik[17][1][2]*Vpk[2][16][1])));
        Vpk[2][18][0] = ((Cik[18][2][0]*Vpk[2][17][2])+((Cik[18][0][0]*
          Vpk[2][17][0])+(Cik[18][1][0]*Vpk[2][17][1])));
        Vpk[2][18][1] = ((Cik[18][2][1]*Vpk[2][17][2])+((Cik[18][0][1]*
          Vpk[2][17][0])+(Cik[18][1][1]*Vpk[2][17][1])));
        Vpk[2][18][2] = ((Cik[18][2][2]*Vpk[2][17][2])+((Cik[18][0][2]*
          Vpk[2][17][0])+(Cik[18][1][2]*Vpk[2][17][1])));
        Vpk[2][19][0] = ((Cik[19][2][0]*Vpk[2][18][2])+((Cik[19][0][0]*
          Vpk[2][18][0])+(Cik[19][1][0]*Vpk[2][18][1])));
        Vpk[2][19][1] = ((Cik[19][2][1]*Vpk[2][18][2])+((Cik[19][0][1]*
          Vpk[2][18][0])+(Cik[19][1][1]*Vpk[2][18][1])));
        Vpk[2][19][2] = ((Cik[19][2][2]*Vpk[2][18][2])+((Cik[19][0][2]*
          Vpk[2][18][0])+(Cik[19][1][2]*Vpk[2][18][1])));
        Vpk[2][20][0] = ((Cik[20][2][0]*Vpk[2][19][2])+((Cik[20][0][0]*
          Vpk[2][19][0])+(Cik[20][1][0]*Vpk[2][19][1])));
        Vpk[2][20][1] = ((Cik[20][2][1]*Vpk[2][19][2])+((Cik[20][0][1]*
          Vpk[2][19][0])+(Cik[20][1][1]*Vpk[2][19][1])));
        Vpk[2][20][2] = ((Cik[20][2][2]*Vpk[2][19][2])+((Cik[20][0][2]*
          Vpk[2][19][0])+(Cik[20][1][2]*Vpk[2][19][1])));
        Vpk[2][21][0] = ((Cik[21][2][0]*Vpk[2][3][2])+((Cik[21][0][0]*
          Vpk[2][3][0])+(Cik[21][1][0]*Vpk[2][3][1])));
        Vpk[2][21][1] = ((Cik[21][2][1]*Vpk[2][3][2])+((Cik[21][0][1]*
          Vpk[2][3][0])+(Cik[21][1][1]*Vpk[2][3][1])));
        Vpk[2][21][2] = ((Cik[21][2][2]*Vpk[2][3][2])+((Cik[21][0][2]*
          Vpk[2][3][0])+(Cik[21][1][2]*Vpk[2][3][1])));
        Vpk[2][22][0] = ((Cik[22][2][0]*Vpk[2][21][2])+((Cik[22][0][0]*
          Vpk[2][21][0])+(Cik[22][1][0]*Vpk[2][21][1])));
        Vpk[2][22][1] = ((Cik[22][2][1]*Vpk[2][21][2])+((Cik[22][0][1]*
          Vpk[2][21][0])+(Cik[22][1][1]*Vpk[2][21][1])));
        Vpk[2][22][2] = ((Cik[22][2][2]*Vpk[2][21][2])+((Cik[22][0][2]*
          Vpk[2][21][0])+(Cik[22][1][2]*Vpk[2][21][1])));
        Vpk[2][23][0] = ((Cik[23][2][0]*Vpk[2][22][2])+((Cik[23][0][0]*
          Vpk[2][22][0])+(Cik[23][1][0]*Vpk[2][22][1])));
        Vpk[2][23][1] = ((Cik[23][2][1]*Vpk[2][22][2])+((Cik[23][0][1]*
          Vpk[2][22][0])+(Cik[23][1][1]*Vpk[2][22][1])));
        Vpk[2][23][2] = ((Cik[23][2][2]*Vpk[2][22][2])+((Cik[23][0][2]*
          Vpk[2][22][0])+(Cik[23][1][2]*Vpk[2][22][1])));
        Vpk[2][24][0] = ((Cik[24][2][0]*Vpk[2][23][2])+((Cik[24][0][0]*
          Vpk[2][23][0])+(Cik[24][1][0]*Vpk[2][23][1])));
        Vpk[2][24][1] = ((Cik[24][2][1]*Vpk[2][23][2])+((Cik[24][0][1]*
          Vpk[2][23][0])+(Cik[24][1][1]*Vpk[2][23][1])));
        Vpk[2][24][2] = ((Cik[24][2][2]*Vpk[2][23][2])+((Cik[24][0][2]*
          Vpk[2][23][0])+(Cik[24][1][2]*Vpk[2][23][1])));
        Vpk[2][25][0] = ((Cik[25][2][0]*Vpk[2][24][2])+((Cik[25][0][0]*
          Vpk[2][24][0])+(Cik[25][1][0]*Vpk[2][24][1])));
        Vpk[2][25][1] = ((Cik[25][2][1]*Vpk[2][24][2])+((Cik[25][0][1]*
          Vpk[2][24][0])+(Cik[25][1][1]*Vpk[2][24][1])));
        Vpk[2][25][2] = ((Cik[25][2][2]*Vpk[2][24][2])+((Cik[25][0][2]*
          Vpk[2][24][0])+(Cik[25][1][2]*Vpk[2][24][1])));
        Vpk[2][26][0] = ((Cik[26][2][0]*Vpk[2][25][2])+((Cik[26][0][0]*
          Vpk[2][25][0])+(Cik[26][1][0]*Vpk[2][25][1])));
        Vpk[2][26][1] = ((Cik[26][2][1]*Vpk[2][25][2])+((Cik[26][0][1]*
          Vpk[2][25][0])+(Cik[26][1][1]*Vpk[2][25][1])));
        Vpk[2][26][2] = ((Cik[26][2][2]*Vpk[2][25][2])+((Cik[26][0][2]*
          Vpk[2][25][0])+(Cik[26][1][2]*Vpk[2][25][1])));
        Vpk[2][27][0] = ((Cik[27][2][0]*Vpk[2][26][2])+((Cik[27][0][0]*
          Vpk[2][26][0])+(Cik[27][1][0]*Vpk[2][26][1])));
        Vpk[2][27][1] = ((Cik[27][2][1]*Vpk[2][26][2])+((Cik[27][0][1]*
          Vpk[2][26][0])+(Cik[27][1][1]*Vpk[2][26][1])));
        Vpk[2][27][2] = ((Cik[27][2][2]*Vpk[2][26][2])+((Cik[27][0][2]*
          Vpk[2][26][0])+(Cik[27][1][2]*Vpk[2][26][1])));
        Vpk[2][28][0] = ((Cik[28][2][0]*Vpk[2][27][2])+((Cik[28][0][0]*
          Vpk[2][27][0])+(Cik[28][1][0]*Vpk[2][27][1])));
        Vpk[2][28][1] = ((Cik[28][2][1]*Vpk[2][27][2])+((Cik[28][0][1]*
          Vpk[2][27][0])+(Cik[28][1][1]*Vpk[2][27][1])));
        Vpk[2][28][2] = ((Cik[28][2][2]*Vpk[2][27][2])+((Cik[28][0][2]*
          Vpk[2][27][0])+(Cik[28][1][2]*Vpk[2][27][1])));
        Vpk[2][29][0] = ((Cik[29][2][0]*Vpk[2][28][2])+((Cik[29][0][0]*
          Vpk[2][28][0])+(Cik[29][1][0]*Vpk[2][28][1])));
        Vpk[2][29][1] = ((Cik[29][2][1]*Vpk[2][28][2])+((Cik[29][0][1]*
          Vpk[2][28][0])+(Cik[29][1][1]*Vpk[2][28][1])));
        Vpk[2][29][2] = ((Cik[29][2][2]*Vpk[2][28][2])+((Cik[29][0][2]*
          Vpk[2][28][0])+(Cik[29][1][2]*Vpk[2][28][1])));
        Vpk[2][30][0] = ((Cik[30][2][0]*Vpk[2][29][2])+((Cik[30][0][0]*
          Vpk[2][29][0])+(Cik[30][1][0]*Vpk[2][29][1])));
        Vpk[2][30][1] = ((Cik[30][2][1]*Vpk[2][29][2])+((Cik[30][0][1]*
          Vpk[2][29][0])+(Cik[30][1][1]*Vpk[2][29][1])));
        Vpk[2][30][2] = ((Cik[30][2][2]*Vpk[2][29][2])+((Cik[30][0][2]*
          Vpk[2][29][0])+(Cik[30][1][2]*Vpk[2][29][1])));
        Vpk[2][31][0] = ((Cik[31][2][0]*Vpk[2][30][2])+((Cik[31][0][0]*
          Vpk[2][30][0])+(Cik[31][1][0]*Vpk[2][30][1])));
        Vpk[2][31][1] = ((Cik[31][2][1]*Vpk[2][30][2])+((Cik[31][0][1]*
          Vpk[2][30][0])+(Cik[31][1][1]*Vpk[2][30][1])));
        Vpk[2][31][2] = ((Cik[31][2][2]*Vpk[2][30][2])+((Cik[31][0][2]*
          Vpk[2][30][0])+(Cik[31][1][2]*Vpk[2][30][1])));
        Vpk[2][32][0] = ((Cik[32][2][0]*Vpk[2][31][2])+((Cik[32][0][0]*
          Vpk[2][31][0])+(Cik[32][1][0]*Vpk[2][31][1])));
        Vpk[2][32][1] = ((Cik[32][2][1]*Vpk[2][31][2])+((Cik[32][0][1]*
          Vpk[2][31][0])+(Cik[32][1][1]*Vpk[2][31][1])));
        Vpk[2][32][2] = ((Cik[32][2][2]*Vpk[2][31][2])+((Cik[32][0][2]*
          Vpk[2][31][0])+(Cik[32][1][2]*Vpk[2][31][1])));
        Vpk[3][6][0] = (.127*Cik[6][2][0]);
        Vpk[3][6][1] = (.127*Cik[6][2][1]);
        Vpk[3][6][2] = (.127*Cik[6][2][2]);
        Vpk[3][7][0] = (.127*((Cik[6][2][2]*Cik[7][2][0])+((Cik[6][2][0]*
          Cik[7][0][0])+(Cik[6][2][1]*Cik[7][1][0]))));
        Vpk[3][7][1] = (.127*((Cik[6][2][2]*Cik[7][2][1])+((Cik[6][2][0]*
          Cik[7][0][1])+(Cik[6][2][1]*Cik[7][1][1]))));
        Vpk[3][7][2] = (.127*((Cik[6][2][2]*Cik[7][2][2])+((Cik[6][2][0]*
          Cik[7][0][2])+(Cik[6][2][1]*Cik[7][1][2]))));
        Vpk[3][8][0] = (((Cik[8][2][0]*Vpk[3][7][2])+((Cik[8][0][0]*Vpk[3][7][0]
          )+(Cik[8][1][0]*Vpk[3][7][1])))-(.3202*Wpk[3][8][2]));
        Vpk[3][8][1] = ((Cik[8][2][1]*Vpk[3][7][2])+((Cik[8][0][1]*Vpk[3][7][0])
          +(Cik[8][1][1]*Vpk[3][7][1])));
        Vpk[3][8][2] = ((.3202*Wpk[3][8][0])+((Cik[8][2][2]*Vpk[3][7][2])+((
          Cik[8][0][2]*Vpk[3][7][0])+(Cik[8][1][2]*Vpk[3][7][1]))));
        Vpk[3][9][0] = -((.07*Cik[9][2][0])+(.0935*Cik[9][1][0]));
        Vpk[3][9][1] = -((.07*Cik[9][2][1])+(.0935*Cik[9][1][1]));
        Vpk[3][9][2] = -((.07*Cik[9][2][2])+(.0935*Cik[9][1][2]));
        Vpk[3][10][0] = ((Cik[10][2][0]*Vpk[3][9][2])+((Cik[10][0][0]*
          Vpk[3][9][0])+(Cik[10][1][0]*Vpk[3][9][1])));
        Vpk[3][10][1] = ((Cik[10][2][1]*Vpk[3][9][2])+((Cik[10][0][1]*
          Vpk[3][9][0])+(Cik[10][1][1]*Vpk[3][9][1])));
        Vpk[3][10][2] = ((Cik[10][2][2]*Vpk[3][9][2])+((Cik[10][0][2]*
          Vpk[3][9][0])+(Cik[10][1][2]*Vpk[3][9][1])));
        Vpk[3][11][0] = ((.1715*Wpk[3][11][2])+((Cik[11][2][0]*Vpk[3][10][2])+((
          Cik[11][0][0]*Vpk[3][10][0])+(Cik[11][1][0]*Vpk[3][10][1]))));
        Vpk[3][11][1] = (((Cik[11][2][1]*Vpk[3][10][2])+((Cik[11][0][1]*
          Vpk[3][10][0])+(Cik[11][1][1]*Vpk[3][10][1])))-(.002*Wpk[3][11][2]));
        Vpk[3][11][2] = (((.002*Wpk[3][11][1])-(.1715*Wpk[3][11][0]))+((
          Cik[11][2][2]*Vpk[3][10][2])+((Cik[11][0][2]*Vpk[3][10][0])+(
          Cik[11][1][2]*Vpk[3][10][1]))));
        VWri[3][12][0] = (Vpk[3][11][0]+(.2294*Wpk[3][11][2]));
        VWri[3][12][1] = (Vpk[3][11][1]+(.0033*Wpk[3][11][2]));
        VWri[3][12][2] = (Vpk[3][11][2]-((.0033*Wpk[3][11][1])+(.2294*
          Wpk[3][11][0])));
        Vpk[3][12][0] = ((Cik[12][2][0]*VWri[3][12][2])+((Cik[12][0][0]*
          VWri[3][12][0])+(Cik[12][1][0]*VWri[3][12][1])));
        Vpk[3][12][1] = ((Cik[12][2][1]*VWri[3][12][2])+((Cik[12][0][1]*
          VWri[3][12][0])+(Cik[12][1][1]*VWri[3][12][1])));
        Vpk[3][12][2] = ((Cik[12][2][2]*VWri[3][12][2])+((Cik[12][0][2]*
          VWri[3][12][0])+(Cik[12][1][2]*VWri[3][12][1])));
        Vpk[3][13][0] = ((Cik[13][2][0]*Vpk[3][12][2])+((Cik[13][0][0]*
          Vpk[3][12][0])+(Cik[13][1][0]*Vpk[3][12][1])));
        Vpk[3][13][1] = ((Cik[13][2][1]*Vpk[3][12][2])+((Cik[13][0][1]*
          Vpk[3][12][0])+(Cik[13][1][1]*Vpk[3][12][1])));
        Vpk[3][13][2] = ((Cik[13][2][2]*Vpk[3][12][2])+((Cik[13][0][2]*
          Vpk[3][12][0])+(Cik[13][1][2]*Vpk[3][12][1])));
        Vpk[3][14][0] = ((.1862*Wpk[3][14][2])+((Cik[14][2][0]*Vpk[3][13][2])+((
          Cik[14][0][0]*Vpk[3][13][0])+(Cik[14][1][0]*Vpk[3][13][1]))));
        Vpk[3][14][1] = ((Cik[14][2][1]*Vpk[3][13][2])+((Cik[14][0][1]*
          Vpk[3][13][0])+(Cik[14][1][1]*Vpk[3][13][1])));
        Vpk[3][14][2] = (((Cik[14][2][2]*Vpk[3][13][2])+((Cik[14][0][2]*
          Vpk[3][13][0])+(Cik[14][1][2]*Vpk[3][13][1])))-(.1862*Wpk[3][14][0]));
        VWri[3][15][0] = (Vpk[3][14][0]+(.2438*Wpk[3][14][2]));
        VWri[3][15][2] = (Vpk[3][14][2]-(.2438*Wpk[3][14][0]));
        Vpk[3][15][0] = ((Cik[15][2][0]*VWri[3][15][2])+((Cik[15][0][0]*
          VWri[3][15][0])+(Cik[15][1][0]*Vpk[3][14][1])));
        Vpk[3][15][1] = ((Cik[15][2][1]*VWri[3][15][2])+((Cik[15][0][1]*
          VWri[3][15][0])+(Cik[15][1][1]*Vpk[3][14][1])));
        Vpk[3][15][2] = ((Cik[15][2][2]*VWri[3][15][2])+((Cik[15][0][2]*
          VWri[3][15][0])+(Cik[15][1][2]*Vpk[3][14][1])));
        Vpk[3][16][0] = ((Cik[16][2][0]*Vpk[3][15][2])+((Cik[16][0][0]*
          Vpk[3][15][0])+(Cik[16][1][0]*Vpk[3][15][1])));
        Vpk[3][16][1] = ((Cik[16][2][1]*Vpk[3][15][2])+((Cik[16][0][1]*
          Vpk[3][15][0])+(Cik[16][1][1]*Vpk[3][15][1])));
        Vpk[3][16][2] = ((Cik[16][2][2]*Vpk[3][15][2])+((Cik[16][0][2]*
          Vpk[3][15][0])+(Cik[16][1][2]*Vpk[3][15][1])));
        Vpk[3][17][0] = (((.005539*Wpk[3][17][1])+(.051347*Wpk[3][17][2]))+((
          Cik[17][2][0]*Vpk[3][16][2])+((Cik[17][0][0]*Vpk[3][16][0])+(
          Cik[17][1][0]*Vpk[3][16][1]))));
        Vpk[3][17][1] = (((.035902*Wpk[3][17][2])-(.005539*Wpk[3][17][0]))+((
          Cik[17][2][1]*Vpk[3][16][2])+((Cik[17][0][1]*Vpk[3][16][0])+(
          Cik[17][1][1]*Vpk[3][16][1]))));
        Vpk[3][17][2] = (((Cik[17][2][2]*Vpk[3][16][2])+((Cik[17][0][2]*
          Vpk[3][16][0])+(Cik[17][1][2]*Vpk[3][16][1])))-((.035902*Wpk[3][17][1]
          )+(.051347*Wpk[3][17][0])));
        VWri[3][18][0] = (Vpk[3][17][0]+((.018078*Wpk[3][17][1])+(.038*
          Wpk[3][17][2])));
        VWri[3][18][1] = (Vpk[3][17][1]+((.098032*Wpk[3][17][2])-(.018078*
          Wpk[3][17][0])));
        VWri[3][18][2] = (Vpk[3][17][2]-((.038*Wpk[3][17][0])+(.098032*
          Wpk[3][17][1])));
        Vpk[3][18][0] = ((Cik[18][2][0]*VWri[3][18][2])+((Cik[18][0][0]*
          VWri[3][18][0])+(Cik[18][1][0]*VWri[3][18][1])));
        Vpk[3][18][1] = ((Cik[18][2][1]*VWri[3][18][2])+((Cik[18][0][1]*
          VWri[3][18][0])+(Cik[18][1][1]*VWri[3][18][1])));
        Vpk[3][18][2] = ((Cik[18][2][2]*VWri[3][18][2])+((Cik[18][0][2]*
          VWri[3][18][0])+(Cik[18][1][2]*VWri[3][18][1])));
        Vpk[3][19][0] = ((Cik[19][2][0]*Vpk[3][18][2])+((Cik[19][0][0]*
          Vpk[3][18][0])+(Cik[19][1][0]*Vpk[3][18][1])));
        Vpk[3][19][1] = ((Cik[19][2][1]*Vpk[3][18][2])+((Cik[19][0][1]*
          Vpk[3][18][0])+(Cik[19][1][1]*Vpk[3][18][1])));
        Vpk[3][19][2] = ((Cik[19][2][2]*Vpk[3][18][2])+((Cik[19][0][2]*
          Vpk[3][18][0])+(Cik[19][1][2]*Vpk[3][18][1])));
        Vpk[3][20][0] = (((.005139*Wpk[3][20][1])-(.0185*Wpk[3][20][2]))+((
          Cik[20][2][0]*Vpk[3][19][2])+((Cik[20][0][0]*Vpk[3][19][0])+(
          Cik[20][1][0]*Vpk[3][19][1]))));
        Vpk[3][20][1] = (((.026917*Wpk[3][20][2])-(.005139*Wpk[3][20][0]))+((
          Cik[20][2][1]*Vpk[3][19][2])+((Cik[20][0][1]*Vpk[3][19][0])+(
          Cik[20][1][1]*Vpk[3][19][1]))));
        Vpk[3][20][2] = (((.0185*Wpk[3][20][0])-(.026917*Wpk[3][20][1]))+((
          Cik[20][2][2]*Vpk[3][19][2])+((Cik[20][0][2]*Vpk[3][19][0])+(
          Cik[20][1][2]*Vpk[3][19][1]))));
        Vpk[3][21][0] = ((.0935*Cik[21][1][0])-(.07*Cik[21][2][0]));
        Vpk[3][21][1] = ((.0935*Cik[21][1][1])-(.07*Cik[21][2][1]));
        Vpk[3][21][2] = ((.0935*Cik[21][1][2])-(.07*Cik[21][2][2]));
        Vpk[3][22][0] = ((Cik[22][2][0]*Vpk[3][21][2])+((Cik[22][0][0]*
          Vpk[3][21][0])+(Cik[22][1][0]*Vpk[3][21][1])));
        Vpk[3][22][1] = ((Cik[22][2][1]*Vpk[3][21][2])+((Cik[22][0][1]*
          Vpk[3][21][0])+(Cik[22][1][1]*Vpk[3][21][1])));
        Vpk[3][22][2] = ((Cik[22][2][2]*Vpk[3][21][2])+((Cik[22][0][2]*
          Vpk[3][21][0])+(Cik[22][1][2]*Vpk[3][21][1])));
        Vpk[3][23][0] = ((.1715*Wpk[3][23][2])+((Cik[23][2][0]*Vpk[3][22][2])+((
          Cik[23][0][0]*Vpk[3][22][0])+(Cik[23][1][0]*Vpk[3][22][1]))));
        Vpk[3][23][1] = (((Cik[23][2][1]*Vpk[3][22][2])+((Cik[23][0][1]*
          Vpk[3][22][0])+(Cik[23][1][1]*Vpk[3][22][1])))-(.002*Wpk[3][23][2]));
        Vpk[3][23][2] = (((.002*Wpk[3][23][1])-(.1715*Wpk[3][23][0]))+((
          Cik[23][2][2]*Vpk[3][22][2])+((Cik[23][0][2]*Vpk[3][22][0])+(
          Cik[23][1][2]*Vpk[3][22][1]))));
        VWri[3][24][0] = (Vpk[3][23][0]+(.2294*Wpk[3][23][2]));
        VWri[3][24][1] = (Vpk[3][23][1]+(.0033*Wpk[3][23][2]));
        VWri[3][24][2] = (Vpk[3][23][2]-((.0033*Wpk[3][23][1])+(.2294*
          Wpk[3][23][0])));
        Vpk[3][24][0] = ((Cik[24][2][0]*VWri[3][24][2])+((Cik[24][0][0]*
          VWri[3][24][0])+(Cik[24][1][0]*VWri[3][24][1])));
        Vpk[3][24][1] = ((Cik[24][2][1]*VWri[3][24][2])+((Cik[24][0][1]*
          VWri[3][24][0])+(Cik[24][1][1]*VWri[3][24][1])));
        Vpk[3][24][2] = ((Cik[24][2][2]*VWri[3][24][2])+((Cik[24][0][2]*
          VWri[3][24][0])+(Cik[24][1][2]*VWri[3][24][1])));
        Vpk[3][25][0] = ((Cik[25][2][0]*Vpk[3][24][2])+((Cik[25][0][0]*
          Vpk[3][24][0])+(Cik[25][1][0]*Vpk[3][24][1])));
        Vpk[3][25][1] = ((Cik[25][2][1]*Vpk[3][24][2])+((Cik[25][0][1]*
          Vpk[3][24][0])+(Cik[25][1][1]*Vpk[3][24][1])));
        Vpk[3][25][2] = ((Cik[25][2][2]*Vpk[3][24][2])+((Cik[25][0][2]*
          Vpk[3][24][0])+(Cik[25][1][2]*Vpk[3][24][1])));
        Vpk[3][26][0] = ((.1862*Wpk[3][26][2])+((Cik[26][2][0]*Vpk[3][25][2])+((
          Cik[26][0][0]*Vpk[3][25][0])+(Cik[26][1][0]*Vpk[3][25][1]))));
        Vpk[3][26][1] = ((Cik[26][2][1]*Vpk[3][25][2])+((Cik[26][0][1]*
          Vpk[3][25][0])+(Cik[26][1][1]*Vpk[3][25][1])));
        Vpk[3][26][2] = (((Cik[26][2][2]*Vpk[3][25][2])+((Cik[26][0][2]*
          Vpk[3][25][0])+(Cik[26][1][2]*Vpk[3][25][1])))-(.1862*Wpk[3][26][0]));
        VWri[3][27][0] = (Vpk[3][26][0]+(.2438*Wpk[3][26][2]));
        VWri[3][27][2] = (Vpk[3][26][2]-(.2438*Wpk[3][26][0]));
        Vpk[3][27][0] = ((Cik[27][2][0]*VWri[3][27][2])+((Cik[27][0][0]*
          VWri[3][27][0])+(Cik[27][1][0]*Vpk[3][26][1])));
        Vpk[3][27][1] = ((Cik[27][2][1]*VWri[3][27][2])+((Cik[27][0][1]*
          VWri[3][27][0])+(Cik[27][1][1]*Vpk[3][26][1])));
        Vpk[3][27][2] = ((Cik[27][2][2]*VWri[3][27][2])+((Cik[27][0][2]*
          VWri[3][27][0])+(Cik[27][1][2]*Vpk[3][26][1])));
        Vpk[3][28][0] = ((Cik[28][2][0]*Vpk[3][27][2])+((Cik[28][0][0]*
          Vpk[3][27][0])+(Cik[28][1][0]*Vpk[3][27][1])));
        Vpk[3][28][1] = ((Cik[28][2][1]*Vpk[3][27][2])+((Cik[28][0][1]*
          Vpk[3][27][0])+(Cik[28][1][1]*Vpk[3][27][1])));
        Vpk[3][28][2] = ((Cik[28][2][2]*Vpk[3][27][2])+((Cik[28][0][2]*
          Vpk[3][27][0])+(Cik[28][1][2]*Vpk[3][27][1])));
        Vpk[3][29][0] = (((.051347*Wpk[3][29][2])-(.005539*Wpk[3][29][1]))+((
          Cik[29][2][0]*Vpk[3][28][2])+((Cik[29][0][0]*Vpk[3][28][0])+(
          Cik[29][1][0]*Vpk[3][28][1]))));
        Vpk[3][29][1] = (((.005539*Wpk[3][29][0])+(.035902*Wpk[3][29][2]))+((
          Cik[29][2][1]*Vpk[3][28][2])+((Cik[29][0][1]*Vpk[3][28][0])+(
          Cik[29][1][1]*Vpk[3][28][1]))));
        Vpk[3][29][2] = (((Cik[29][2][2]*Vpk[3][28][2])+((Cik[29][0][2]*
          Vpk[3][28][0])+(Cik[29][1][2]*Vpk[3][28][1])))-((.035902*Wpk[3][29][1]
          )+(.051347*Wpk[3][29][0])));
        VWri[3][30][0] = (Vpk[3][29][0]+((.038*Wpk[3][29][2])-(.018078*
          Wpk[3][29][1])));
        VWri[3][30][1] = (Vpk[3][29][1]+((.018078*Wpk[3][29][0])+(.098032*
          Wpk[3][29][2])));
        VWri[3][30][2] = (Vpk[3][29][2]-((.038*Wpk[3][29][0])+(.098032*
          Wpk[3][29][1])));
        Vpk[3][30][0] = ((Cik[30][2][0]*VWri[3][30][2])+((Cik[30][0][0]*
          VWri[3][30][0])+(Cik[30][1][0]*VWri[3][30][1])));
        Vpk[3][30][1] = ((Cik[30][2][1]*VWri[3][30][2])+((Cik[30][0][1]*
          VWri[3][30][0])+(Cik[30][1][1]*VWri[3][30][1])));
        Vpk[3][30][2] = ((Cik[30][2][2]*VWri[3][30][2])+((Cik[30][0][2]*
          VWri[3][30][0])+(Cik[30][1][2]*VWri[3][30][1])));
        Vpk[3][31][0] = ((Cik[31][2][0]*Vpk[3][30][2])+((Cik[31][0][0]*
          Vpk[3][30][0])+(Cik[31][1][0]*Vpk[3][30][1])));
        Vpk[3][31][1] = ((Cik[31][2][1]*Vpk[3][30][2])+((Cik[31][0][1]*
          Vpk[3][30][0])+(Cik[31][1][1]*Vpk[3][30][1])));
        Vpk[3][31][2] = ((Cik[31][2][2]*Vpk[3][30][2])+((Cik[31][0][2]*
          Vpk[3][30][0])+(Cik[31][1][2]*Vpk[3][30][1])));
        Vpk[3][32][0] = (((Cik[32][2][0]*Vpk[3][31][2])+((Cik[32][0][0]*
          Vpk[3][31][0])+(Cik[32][1][0]*Vpk[3][31][1])))-((.005139*Wpk[3][32][1]
          )+(.0185*Wpk[3][32][2])));
        Vpk[3][32][1] = (((.005139*Wpk[3][32][0])+(.026917*Wpk[3][32][2]))+((
          Cik[32][2][1]*Vpk[3][31][2])+((Cik[32][0][1]*Vpk[3][31][0])+(
          Cik[32][1][1]*Vpk[3][31][1]))));
        Vpk[3][32][2] = (((.0185*Wpk[3][32][0])-(.026917*Wpk[3][32][1]))+((
          Cik[32][2][2]*Vpk[3][31][2])+((Cik[32][0][2]*Vpk[3][31][0])+(
          Cik[32][1][2]*Vpk[3][31][1]))));
        Vpk[4][8][0] = -(.3202*Wpk[4][8][2]);
        Vpk[4][8][2] = (.3202*Wpk[4][8][0]);
        Vpk[4][9][0] = (.0935*Cik[9][0][0]);
        Vpk[4][9][1] = (.0935*Cik[9][0][1]);
        Vpk[4][9][2] = (.0935*Cik[9][0][2]);
        Vpk[4][10][0] = (.0935*((Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*
          Cik[10][0][0])+(Cik[9][0][1]*Cik[10][1][0]))));
        Vpk[4][10][1] = (.0935*((Cik[9][0][2]*Cik[10][2][1])+((Cik[9][0][0]*
          Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1]))));
        Vpk[4][10][2] = (.0935*((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
          Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2]))));
        Vpk[4][11][0] = ((.1715*Wpk[4][11][2])+((Cik[11][2][0]*Vpk[4][10][2])+((
          Cik[11][0][0]*Vpk[4][10][0])+(Cik[11][1][0]*Vpk[4][10][1]))));
        Vpk[4][11][1] = (((Cik[11][2][1]*Vpk[4][10][2])+((Cik[11][0][1]*
          Vpk[4][10][0])+(Cik[11][1][1]*Vpk[4][10][1])))-(.002*Wpk[4][11][2]));
        Vpk[4][11][2] = (((.002*Wpk[4][11][1])-(.1715*Wpk[4][11][0]))+((
          Cik[11][2][2]*Vpk[4][10][2])+((Cik[11][0][2]*Vpk[4][10][0])+(
          Cik[11][1][2]*Vpk[4][10][1]))));
        VWri[4][12][0] = (Vpk[4][11][0]+(.2294*Wpk[4][11][2]));
        VWri[4][12][1] = (Vpk[4][11][1]+(.0033*Wpk[4][11][2]));
        VWri[4][12][2] = (Vpk[4][11][2]-((.0033*Wpk[4][11][1])+(.2294*
          Wpk[4][11][0])));
        Vpk[4][12][0] = ((Cik[12][2][0]*VWri[4][12][2])+((Cik[12][0][0]*
          VWri[4][12][0])+(Cik[12][1][0]*VWri[4][12][1])));
        Vpk[4][12][1] = ((Cik[12][2][1]*VWri[4][12][2])+((Cik[12][0][1]*
          VWri[4][12][0])+(Cik[12][1][1]*VWri[4][12][1])));
        Vpk[4][12][2] = ((Cik[12][2][2]*VWri[4][12][2])+((Cik[12][0][2]*
          VWri[4][12][0])+(Cik[12][1][2]*VWri[4][12][1])));
        Vpk[4][13][0] = ((Cik[13][2][0]*Vpk[4][12][2])+((Cik[13][0][0]*
          Vpk[4][12][0])+(Cik[13][1][0]*Vpk[4][12][1])));
        Vpk[4][13][1] = ((Cik[13][2][1]*Vpk[4][12][2])+((Cik[13][0][1]*
          Vpk[4][12][0])+(Cik[13][1][1]*Vpk[4][12][1])));
        Vpk[4][13][2] = ((Cik[13][2][2]*Vpk[4][12][2])+((Cik[13][0][2]*
          Vpk[4][12][0])+(Cik[13][1][2]*Vpk[4][12][1])));
        Vpk[4][14][0] = ((.1862*Wpk[4][14][2])+((Cik[14][2][0]*Vpk[4][13][2])+((
          Cik[14][0][0]*Vpk[4][13][0])+(Cik[14][1][0]*Vpk[4][13][1]))));
        Vpk[4][14][1] = ((Cik[14][2][1]*Vpk[4][13][2])+((Cik[14][0][1]*
          Vpk[4][13][0])+(Cik[14][1][1]*Vpk[4][13][1])));
        Vpk[4][14][2] = (((Cik[14][2][2]*Vpk[4][13][2])+((Cik[14][0][2]*
          Vpk[4][13][0])+(Cik[14][1][2]*Vpk[4][13][1])))-(.1862*Wpk[4][14][0]));
        VWri[4][15][0] = (Vpk[4][14][0]+(.2438*Wpk[4][14][2]));
        VWri[4][15][2] = (Vpk[4][14][2]-(.2438*Wpk[4][14][0]));
        Vpk[4][15][0] = ((Cik[15][2][0]*VWri[4][15][2])+((Cik[15][0][0]*
          VWri[4][15][0])+(Cik[15][1][0]*Vpk[4][14][1])));
        Vpk[4][15][1] = ((Cik[15][2][1]*VWri[4][15][2])+((Cik[15][0][1]*
          VWri[4][15][0])+(Cik[15][1][1]*Vpk[4][14][1])));
        Vpk[4][15][2] = ((Cik[15][2][2]*VWri[4][15][2])+((Cik[15][0][2]*
          VWri[4][15][0])+(Cik[15][1][2]*Vpk[4][14][1])));
        Vpk[4][16][0] = ((Cik[16][2][0]*Vpk[4][15][2])+((Cik[16][0][0]*
          Vpk[4][15][0])+(Cik[16][1][0]*Vpk[4][15][1])));
        Vpk[4][16][1] = ((Cik[16][2][1]*Vpk[4][15][2])+((Cik[16][0][1]*
          Vpk[4][15][0])+(Cik[16][1][1]*Vpk[4][15][1])));
        Vpk[4][16][2] = ((Cik[16][2][2]*Vpk[4][15][2])+((Cik[16][0][2]*
          Vpk[4][15][0])+(Cik[16][1][2]*Vpk[4][15][1])));
        Vpk[4][17][0] = (((.005539*Wpk[4][17][1])+(.051347*Wpk[4][17][2]))+((
          Cik[17][2][0]*Vpk[4][16][2])+((Cik[17][0][0]*Vpk[4][16][0])+(
          Cik[17][1][0]*Vpk[4][16][1]))));
        Vpk[4][17][1] = (((.035902*Wpk[4][17][2])-(.005539*Wpk[4][17][0]))+((
          Cik[17][2][1]*Vpk[4][16][2])+((Cik[17][0][1]*Vpk[4][16][0])+(
          Cik[17][1][1]*Vpk[4][16][1]))));
        Vpk[4][17][2] = (((Cik[17][2][2]*Vpk[4][16][2])+((Cik[17][0][2]*
          Vpk[4][16][0])+(Cik[17][1][2]*Vpk[4][16][1])))-((.035902*Wpk[4][17][1]
          )+(.051347*Wpk[4][17][0])));
        VWri[4][18][0] = (Vpk[4][17][0]+((.018078*Wpk[4][17][1])+(.038*
          Wpk[4][17][2])));
        VWri[4][18][1] = (Vpk[4][17][1]+((.098032*Wpk[4][17][2])-(.018078*
          Wpk[4][17][0])));
        VWri[4][18][2] = (Vpk[4][17][2]-((.038*Wpk[4][17][0])+(.098032*
          Wpk[4][17][1])));
        Vpk[4][18][0] = ((Cik[18][2][0]*VWri[4][18][2])+((Cik[18][0][0]*
          VWri[4][18][0])+(Cik[18][1][0]*VWri[4][18][1])));
        Vpk[4][18][1] = ((Cik[18][2][1]*VWri[4][18][2])+((Cik[18][0][1]*
          VWri[4][18][0])+(Cik[18][1][1]*VWri[4][18][1])));
        Vpk[4][18][2] = ((Cik[18][2][2]*VWri[4][18][2])+((Cik[18][0][2]*
          VWri[4][18][0])+(Cik[18][1][2]*VWri[4][18][1])));
        Vpk[4][19][0] = ((Cik[19][2][0]*Vpk[4][18][2])+((Cik[19][0][0]*
          Vpk[4][18][0])+(Cik[19][1][0]*Vpk[4][18][1])));
        Vpk[4][19][1] = ((Cik[19][2][1]*Vpk[4][18][2])+((Cik[19][0][1]*
          Vpk[4][18][0])+(Cik[19][1][1]*Vpk[4][18][1])));
        Vpk[4][19][2] = ((Cik[19][2][2]*Vpk[4][18][2])+((Cik[19][0][2]*
          Vpk[4][18][0])+(Cik[19][1][2]*Vpk[4][18][1])));
        Vpk[4][20][0] = (((.005139*Wpk[4][20][1])-(.0185*Wpk[4][20][2]))+((
          Cik[20][2][0]*Vpk[4][19][2])+((Cik[20][0][0]*Vpk[4][19][0])+(
          Cik[20][1][0]*Vpk[4][19][1]))));
        Vpk[4][20][1] = (((.026917*Wpk[4][20][2])-(.005139*Wpk[4][20][0]))+((
          Cik[20][2][1]*Vpk[4][19][2])+((Cik[20][0][1]*Vpk[4][19][0])+(
          Cik[20][1][1]*Vpk[4][19][1]))));
        Vpk[4][20][2] = (((.0185*Wpk[4][20][0])-(.026917*Wpk[4][20][1]))+((
          Cik[20][2][2]*Vpk[4][19][2])+((Cik[20][0][2]*Vpk[4][19][0])+(
          Cik[20][1][2]*Vpk[4][19][1]))));
        Vpk[4][21][0] = -(.0935*Cik[21][0][0]);
        Vpk[4][21][1] = -(.0935*Cik[21][0][1]);
        Vpk[4][21][2] = -(.0935*Cik[21][0][2]);
        Vpk[4][22][0] = -(.0935*((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*
          Cik[22][0][0])+(Cik[21][0][1]*Cik[22][1][0]))));
        Vpk[4][22][1] = -(.0935*((Cik[21][0][2]*Cik[22][2][1])+((Cik[21][0][0]*
          Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1]))));
        Vpk[4][22][2] = -(.0935*((Cik[21][0][2]*Cik[22][2][2])+((Cik[21][0][0]*
          Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2]))));
        Vpk[4][23][0] = ((.1715*Wpk[4][23][2])+((Cik[23][2][0]*Vpk[4][22][2])+((
          Cik[23][0][0]*Vpk[4][22][0])+(Cik[23][1][0]*Vpk[4][22][1]))));
        Vpk[4][23][1] = (((Cik[23][2][1]*Vpk[4][22][2])+((Cik[23][0][1]*
          Vpk[4][22][0])+(Cik[23][1][1]*Vpk[4][22][1])))-(.002*Wpk[4][23][2]));
        Vpk[4][23][2] = (((.002*Wpk[4][23][1])-(.1715*Wpk[4][23][0]))+((
          Cik[23][2][2]*Vpk[4][22][2])+((Cik[23][0][2]*Vpk[4][22][0])+(
          Cik[23][1][2]*Vpk[4][22][1]))));
        VWri[4][24][0] = (Vpk[4][23][0]+(.2294*Wpk[4][23][2]));
        VWri[4][24][1] = (Vpk[4][23][1]+(.0033*Wpk[4][23][2]));
        VWri[4][24][2] = (Vpk[4][23][2]-((.0033*Wpk[4][23][1])+(.2294*
          Wpk[4][23][0])));
        Vpk[4][24][0] = ((Cik[24][2][0]*VWri[4][24][2])+((Cik[24][0][0]*
          VWri[4][24][0])+(Cik[24][1][0]*VWri[4][24][1])));
        Vpk[4][24][1] = ((Cik[24][2][1]*VWri[4][24][2])+((Cik[24][0][1]*
          VWri[4][24][0])+(Cik[24][1][1]*VWri[4][24][1])));
        Vpk[4][24][2] = ((Cik[24][2][2]*VWri[4][24][2])+((Cik[24][0][2]*
          VWri[4][24][0])+(Cik[24][1][2]*VWri[4][24][1])));
        Vpk[4][25][0] = ((Cik[25][2][0]*Vpk[4][24][2])+((Cik[25][0][0]*
          Vpk[4][24][0])+(Cik[25][1][0]*Vpk[4][24][1])));
        Vpk[4][25][1] = ((Cik[25][2][1]*Vpk[4][24][2])+((Cik[25][0][1]*
          Vpk[4][24][0])+(Cik[25][1][1]*Vpk[4][24][1])));
        Vpk[4][25][2] = ((Cik[25][2][2]*Vpk[4][24][2])+((Cik[25][0][2]*
          Vpk[4][24][0])+(Cik[25][1][2]*Vpk[4][24][1])));
        Vpk[4][26][0] = ((.1862*Wpk[4][26][2])+((Cik[26][2][0]*Vpk[4][25][2])+((
          Cik[26][0][0]*Vpk[4][25][0])+(Cik[26][1][0]*Vpk[4][25][1]))));
        Vpk[4][26][1] = ((Cik[26][2][1]*Vpk[4][25][2])+((Cik[26][0][1]*
          Vpk[4][25][0])+(Cik[26][1][1]*Vpk[4][25][1])));
        Vpk[4][26][2] = (((Cik[26][2][2]*Vpk[4][25][2])+((Cik[26][0][2]*
          Vpk[4][25][0])+(Cik[26][1][2]*Vpk[4][25][1])))-(.1862*Wpk[4][26][0]));
        VWri[4][27][0] = (Vpk[4][26][0]+(.2438*Wpk[4][26][2]));
        VWri[4][27][2] = (Vpk[4][26][2]-(.2438*Wpk[4][26][0]));
        Vpk[4][27][0] = ((Cik[27][2][0]*VWri[4][27][2])+((Cik[27][0][0]*
          VWri[4][27][0])+(Cik[27][1][0]*Vpk[4][26][1])));
        Vpk[4][27][1] = ((Cik[27][2][1]*VWri[4][27][2])+((Cik[27][0][1]*
          VWri[4][27][0])+(Cik[27][1][1]*Vpk[4][26][1])));
        Vpk[4][27][2] = ((Cik[27][2][2]*VWri[4][27][2])+((Cik[27][0][2]*
          VWri[4][27][0])+(Cik[27][1][2]*Vpk[4][26][1])));
        Vpk[4][28][0] = ((Cik[28][2][0]*Vpk[4][27][2])+((Cik[28][0][0]*
          Vpk[4][27][0])+(Cik[28][1][0]*Vpk[4][27][1])));
        Vpk[4][28][1] = ((Cik[28][2][1]*Vpk[4][27][2])+((Cik[28][0][1]*
          Vpk[4][27][0])+(Cik[28][1][1]*Vpk[4][27][1])));
        Vpk[4][28][2] = ((Cik[28][2][2]*Vpk[4][27][2])+((Cik[28][0][2]*
          Vpk[4][27][0])+(Cik[28][1][2]*Vpk[4][27][1])));
        Vpk[4][29][0] = (((.051347*Wpk[4][29][2])-(.005539*Wpk[4][29][1]))+((
          Cik[29][2][0]*Vpk[4][28][2])+((Cik[29][0][0]*Vpk[4][28][0])+(
          Cik[29][1][0]*Vpk[4][28][1]))));
        Vpk[4][29][1] = (((.005539*Wpk[4][29][0])+(.035902*Wpk[4][29][2]))+((
          Cik[29][2][1]*Vpk[4][28][2])+((Cik[29][0][1]*Vpk[4][28][0])+(
          Cik[29][1][1]*Vpk[4][28][1]))));
        Vpk[4][29][2] = (((Cik[29][2][2]*Vpk[4][28][2])+((Cik[29][0][2]*
          Vpk[4][28][0])+(Cik[29][1][2]*Vpk[4][28][1])))-((.035902*Wpk[4][29][1]
          )+(.051347*Wpk[4][29][0])));
        VWri[4][30][0] = (Vpk[4][29][0]+((.038*Wpk[4][29][2])-(.018078*
          Wpk[4][29][1])));
        VWri[4][30][1] = (Vpk[4][29][1]+((.018078*Wpk[4][29][0])+(.098032*
          Wpk[4][29][2])));
        VWri[4][30][2] = (Vpk[4][29][2]-((.038*Wpk[4][29][0])+(.098032*
          Wpk[4][29][1])));
        Vpk[4][30][0] = ((Cik[30][2][0]*VWri[4][30][2])+((Cik[30][0][0]*
          VWri[4][30][0])+(Cik[30][1][0]*VWri[4][30][1])));
        Vpk[4][30][1] = ((Cik[30][2][1]*VWri[4][30][2])+((Cik[30][0][1]*
          VWri[4][30][0])+(Cik[30][1][1]*VWri[4][30][1])));
        Vpk[4][30][2] = ((Cik[30][2][2]*VWri[4][30][2])+((Cik[30][0][2]*
          VWri[4][30][0])+(Cik[30][1][2]*VWri[4][30][1])));
        Vpk[4][31][0] = ((Cik[31][2][0]*Vpk[4][30][2])+((Cik[31][0][0]*
          Vpk[4][30][0])+(Cik[31][1][0]*Vpk[4][30][1])));
        Vpk[4][31][1] = ((Cik[31][2][1]*Vpk[4][30][2])+((Cik[31][0][1]*
          Vpk[4][30][0])+(Cik[31][1][1]*Vpk[4][30][1])));
        Vpk[4][31][2] = ((Cik[31][2][2]*Vpk[4][30][2])+((Cik[31][0][2]*
          Vpk[4][30][0])+(Cik[31][1][2]*Vpk[4][30][1])));
        Vpk[4][32][0] = (((Cik[32][2][0]*Vpk[4][31][2])+((Cik[32][0][0]*
          Vpk[4][31][0])+(Cik[32][1][0]*Vpk[4][31][1])))-((.005139*Wpk[4][32][1]
          )+(.0185*Wpk[4][32][2])));
        Vpk[4][32][1] = (((.005139*Wpk[4][32][0])+(.026917*Wpk[4][32][2]))+((
          Cik[32][2][1]*Vpk[4][31][2])+((Cik[32][0][1]*Vpk[4][31][0])+(
          Cik[32][1][1]*Vpk[4][31][1]))));
        Vpk[4][32][2] = (((.0185*Wpk[4][32][0])-(.026917*Wpk[4][32][1]))+((
          Cik[32][2][2]*Vpk[4][31][2])+((Cik[32][0][2]*Vpk[4][31][0])+(
          Cik[32][1][2]*Vpk[4][31][1]))));
        Vpk[5][6][0] = -(.127*Cik[6][0][0]);
        Vpk[5][6][1] = -(.127*Cik[6][0][1]);
        Vpk[5][6][2] = -(.127*Cik[6][0][2]);
        Vpk[5][7][0] = -(.127*((Cik[6][0][2]*Cik[7][2][0])+((Cik[6][0][0]*
          Cik[7][0][0])+(Cik[6][0][1]*Cik[7][1][0]))));
        Vpk[5][7][1] = -(.127*((Cik[6][0][2]*Cik[7][2][1])+((Cik[6][0][0]*
          Cik[7][0][1])+(Cik[6][0][1]*Cik[7][1][1]))));
        Vpk[5][7][2] = -(.127*((Cik[6][0][2]*Cik[7][2][2])+((Cik[6][0][0]*
          Cik[7][0][2])+(Cik[6][0][1]*Cik[7][1][2]))));
        Vpk[5][8][0] = (((Cik[8][2][0]*Vpk[5][7][2])+((Cik[8][0][0]*Vpk[5][7][0]
          )+(Cik[8][1][0]*Vpk[5][7][1])))-(.3202*Wpk[5][8][2]));
        Vpk[5][8][1] = ((Cik[8][2][1]*Vpk[5][7][2])+((Cik[8][0][1]*Vpk[5][7][0])
          +(Cik[8][1][1]*Vpk[5][7][1])));
        Vpk[5][8][2] = ((.3202*Wpk[5][8][0])+((Cik[8][2][2]*Vpk[5][7][2])+((
          Cik[8][0][2]*Vpk[5][7][0])+(Cik[8][1][2]*Vpk[5][7][1]))));
        Vpk[5][9][0] = (.07*Cik[9][0][0]);
        Vpk[5][9][1] = (.07*Cik[9][0][1]);
        Vpk[5][9][2] = (.07*Cik[9][0][2]);
        Vpk[5][10][0] = (.07*((Cik[9][0][2]*Cik[10][2][0])+((Cik[9][0][0]*
          Cik[10][0][0])+(Cik[9][0][1]*Cik[10][1][0]))));
        Vpk[5][10][1] = (.07*((Cik[9][0][2]*Cik[10][2][1])+((Cik[9][0][0]*
          Cik[10][0][1])+(Cik[9][0][1]*Cik[10][1][1]))));
        Vpk[5][10][2] = (.07*((Cik[9][0][2]*Cik[10][2][2])+((Cik[9][0][0]*
          Cik[10][0][2])+(Cik[9][0][1]*Cik[10][1][2]))));
        Vpk[5][11][0] = ((.1715*Wpk[5][11][2])+((Cik[11][2][0]*Vpk[5][10][2])+((
          Cik[11][0][0]*Vpk[5][10][0])+(Cik[11][1][0]*Vpk[5][10][1]))));
        Vpk[5][11][1] = (((Cik[11][2][1]*Vpk[5][10][2])+((Cik[11][0][1]*
          Vpk[5][10][0])+(Cik[11][1][1]*Vpk[5][10][1])))-(.002*Wpk[5][11][2]));
        Vpk[5][11][2] = (((.002*Wpk[5][11][1])-(.1715*Wpk[5][11][0]))+((
          Cik[11][2][2]*Vpk[5][10][2])+((Cik[11][0][2]*Vpk[5][10][0])+(
          Cik[11][1][2]*Vpk[5][10][1]))));
        VWri[5][12][0] = (Vpk[5][11][0]+(.2294*Wpk[5][11][2]));
        VWri[5][12][1] = (Vpk[5][11][1]+(.0033*Wpk[5][11][2]));
        VWri[5][12][2] = (Vpk[5][11][2]-((.0033*Wpk[5][11][1])+(.2294*
          Wpk[5][11][0])));
        Vpk[5][12][0] = ((Cik[12][2][0]*VWri[5][12][2])+((Cik[12][0][0]*
          VWri[5][12][0])+(Cik[12][1][0]*VWri[5][12][1])));
        Vpk[5][12][1] = ((Cik[12][2][1]*VWri[5][12][2])+((Cik[12][0][1]*
          VWri[5][12][0])+(Cik[12][1][1]*VWri[5][12][1])));
        Vpk[5][12][2] = ((Cik[12][2][2]*VWri[5][12][2])+((Cik[12][0][2]*
          VWri[5][12][0])+(Cik[12][1][2]*VWri[5][12][1])));
        Vpk[5][13][0] = ((Cik[13][2][0]*Vpk[5][12][2])+((Cik[13][0][0]*
          Vpk[5][12][0])+(Cik[13][1][0]*Vpk[5][12][1])));
        Vpk[5][13][1] = ((Cik[13][2][1]*Vpk[5][12][2])+((Cik[13][0][1]*
          Vpk[5][12][0])+(Cik[13][1][1]*Vpk[5][12][1])));
        Vpk[5][13][2] = ((Cik[13][2][2]*Vpk[5][12][2])+((Cik[13][0][2]*
          Vpk[5][12][0])+(Cik[13][1][2]*Vpk[5][12][1])));
        Vpk[5][14][0] = ((.1862*Wpk[5][14][2])+((Cik[14][2][0]*Vpk[5][13][2])+((
          Cik[14][0][0]*Vpk[5][13][0])+(Cik[14][1][0]*Vpk[5][13][1]))));
        Vpk[5][14][1] = ((Cik[14][2][1]*Vpk[5][13][2])+((Cik[14][0][1]*
          Vpk[5][13][0])+(Cik[14][1][1]*Vpk[5][13][1])));
        Vpk[5][14][2] = (((Cik[14][2][2]*Vpk[5][13][2])+((Cik[14][0][2]*
          Vpk[5][13][0])+(Cik[14][1][2]*Vpk[5][13][1])))-(.1862*Wpk[5][14][0]));
        VWri[5][15][0] = (Vpk[5][14][0]+(.2438*Wpk[5][14][2]));
        VWri[5][15][2] = (Vpk[5][14][2]-(.2438*Wpk[5][14][0]));
        Vpk[5][15][0] = ((Cik[15][2][0]*VWri[5][15][2])+((Cik[15][0][0]*
          VWri[5][15][0])+(Cik[15][1][0]*Vpk[5][14][1])));
        Vpk[5][15][1] = ((Cik[15][2][1]*VWri[5][15][2])+((Cik[15][0][1]*
          VWri[5][15][0])+(Cik[15][1][1]*Vpk[5][14][1])));
        Vpk[5][15][2] = ((Cik[15][2][2]*VWri[5][15][2])+((Cik[15][0][2]*
          VWri[5][15][0])+(Cik[15][1][2]*Vpk[5][14][1])));
        Vpk[5][16][0] = ((Cik[16][2][0]*Vpk[5][15][2])+((Cik[16][0][0]*
          Vpk[5][15][0])+(Cik[16][1][0]*Vpk[5][15][1])));
        Vpk[5][16][1] = ((Cik[16][2][1]*Vpk[5][15][2])+((Cik[16][0][1]*
          Vpk[5][15][0])+(Cik[16][1][1]*Vpk[5][15][1])));
        Vpk[5][16][2] = ((Cik[16][2][2]*Vpk[5][15][2])+((Cik[16][0][2]*
          Vpk[5][15][0])+(Cik[16][1][2]*Vpk[5][15][1])));
        Vpk[5][17][0] = (((.005539*Wpk[5][17][1])+(.051347*Wpk[5][17][2]))+((
          Cik[17][2][0]*Vpk[5][16][2])+((Cik[17][0][0]*Vpk[5][16][0])+(
          Cik[17][1][0]*Vpk[5][16][1]))));
        Vpk[5][17][1] = (((.035902*Wpk[5][17][2])-(.005539*Wpk[5][17][0]))+((
          Cik[17][2][1]*Vpk[5][16][2])+((Cik[17][0][1]*Vpk[5][16][0])+(
          Cik[17][1][1]*Vpk[5][16][1]))));
        Vpk[5][17][2] = (((Cik[17][2][2]*Vpk[5][16][2])+((Cik[17][0][2]*
          Vpk[5][16][0])+(Cik[17][1][2]*Vpk[5][16][1])))-((.035902*Wpk[5][17][1]
          )+(.051347*Wpk[5][17][0])));
        VWri[5][18][0] = (Vpk[5][17][0]+((.018078*Wpk[5][17][1])+(.038*
          Wpk[5][17][2])));
        VWri[5][18][1] = (Vpk[5][17][1]+((.098032*Wpk[5][17][2])-(.018078*
          Wpk[5][17][0])));
        VWri[5][18][2] = (Vpk[5][17][2]-((.038*Wpk[5][17][0])+(.098032*
          Wpk[5][17][1])));
        Vpk[5][18][0] = ((Cik[18][2][0]*VWri[5][18][2])+((Cik[18][0][0]*
          VWri[5][18][0])+(Cik[18][1][0]*VWri[5][18][1])));
        Vpk[5][18][1] = ((Cik[18][2][1]*VWri[5][18][2])+((Cik[18][0][1]*
          VWri[5][18][0])+(Cik[18][1][1]*VWri[5][18][1])));
        Vpk[5][18][2] = ((Cik[18][2][2]*VWri[5][18][2])+((Cik[18][0][2]*
          VWri[5][18][0])+(Cik[18][1][2]*VWri[5][18][1])));
        Vpk[5][19][0] = ((Cik[19][2][0]*Vpk[5][18][2])+((Cik[19][0][0]*
          Vpk[5][18][0])+(Cik[19][1][0]*Vpk[5][18][1])));
        Vpk[5][19][1] = ((Cik[19][2][1]*Vpk[5][18][2])+((Cik[19][0][1]*
          Vpk[5][18][0])+(Cik[19][1][1]*Vpk[5][18][1])));
        Vpk[5][19][2] = ((Cik[19][2][2]*Vpk[5][18][2])+((Cik[19][0][2]*
          Vpk[5][18][0])+(Cik[19][1][2]*Vpk[5][18][1])));
        Vpk[5][20][0] = (((.005139*Wpk[5][20][1])-(.0185*Wpk[5][20][2]))+((
          Cik[20][2][0]*Vpk[5][19][2])+((Cik[20][0][0]*Vpk[5][19][0])+(
          Cik[20][1][0]*Vpk[5][19][1]))));
        Vpk[5][20][1] = (((.026917*Wpk[5][20][2])-(.005139*Wpk[5][20][0]))+((
          Cik[20][2][1]*Vpk[5][19][2])+((Cik[20][0][1]*Vpk[5][19][0])+(
          Cik[20][1][1]*Vpk[5][19][1]))));
        Vpk[5][20][2] = (((.0185*Wpk[5][20][0])-(.026917*Wpk[5][20][1]))+((
          Cik[20][2][2]*Vpk[5][19][2])+((Cik[20][0][2]*Vpk[5][19][0])+(
          Cik[20][1][2]*Vpk[5][19][1]))));
        Vpk[5][21][0] = (.07*Cik[21][0][0]);
        Vpk[5][21][1] = (.07*Cik[21][0][1]);
        Vpk[5][21][2] = (.07*Cik[21][0][2]);
        Vpk[5][22][0] = (.07*((Cik[21][0][2]*Cik[22][2][0])+((Cik[21][0][0]*
          Cik[22][0][0])+(Cik[21][0][1]*Cik[22][1][0]))));
        Vpk[5][22][1] = (.07*((Cik[21][0][2]*Cik[22][2][1])+((Cik[21][0][0]*
          Cik[22][0][1])+(Cik[21][0][1]*Cik[22][1][1]))));
        Vpk[5][22][2] = (.07*((Cik[21][0][2]*Cik[22][2][2])+((Cik[21][0][0]*
          Cik[22][0][2])+(Cik[21][0][1]*Cik[22][1][2]))));
        Vpk[5][23][0] = ((.1715*Wpk[5][23][2])+((Cik[23][2][0]*Vpk[5][22][2])+((
          Cik[23][0][0]*Vpk[5][22][0])+(Cik[23][1][0]*Vpk[5][22][1]))));
        Vpk[5][23][1] = (((Cik[23][2][1]*Vpk[5][22][2])+((Cik[23][0][1]*
          Vpk[5][22][0])+(Cik[23][1][1]*Vpk[5][22][1])))-(.002*Wpk[5][23][2]));
        Vpk[5][23][2] = (((.002*Wpk[5][23][1])-(.1715*Wpk[5][23][0]))+((
          Cik[23][2][2]*Vpk[5][22][2])+((Cik[23][0][2]*Vpk[5][22][0])+(
          Cik[23][1][2]*Vpk[5][22][1]))));
        VWri[5][24][0] = (Vpk[5][23][0]+(.2294*Wpk[5][23][2]));
        VWri[5][24][1] = (Vpk[5][23][1]+(.0033*Wpk[5][23][2]));
        VWri[5][24][2] = (Vpk[5][23][2]-((.0033*Wpk[5][23][1])+(.2294*
          Wpk[5][23][0])));
        Vpk[5][24][0] = ((Cik[24][2][0]*VWri[5][24][2])+((Cik[24][0][0]*
          VWri[5][24][0])+(Cik[24][1][0]*VWri[5][24][1])));
        Vpk[5][24][1] = ((Cik[24][2][1]*VWri[5][24][2])+((Cik[24][0][1]*
          VWri[5][24][0])+(Cik[24][1][1]*VWri[5][24][1])));
        Vpk[5][24][2] = ((Cik[24][2][2]*VWri[5][24][2])+((Cik[24][0][2]*
          VWri[5][24][0])+(Cik[24][1][2]*VWri[5][24][1])));
        Vpk[5][25][0] = ((Cik[25][2][0]*Vpk[5][24][2])+((Cik[25][0][0]*
          Vpk[5][24][0])+(Cik[25][1][0]*Vpk[5][24][1])));
        Vpk[5][25][1] = ((Cik[25][2][1]*Vpk[5][24][2])+((Cik[25][0][1]*
          Vpk[5][24][0])+(Cik[25][1][1]*Vpk[5][24][1])));
        Vpk[5][25][2] = ((Cik[25][2][2]*Vpk[5][24][2])+((Cik[25][0][2]*
          Vpk[5][24][0])+(Cik[25][1][2]*Vpk[5][24][1])));
        Vpk[5][26][0] = ((.1862*Wpk[5][26][2])+((Cik[26][2][0]*Vpk[5][25][2])+((
          Cik[26][0][0]*Vpk[5][25][0])+(Cik[26][1][0]*Vpk[5][25][1]))));
        Vpk[5][26][1] = ((Cik[26][2][1]*Vpk[5][25][2])+((Cik[26][0][1]*
          Vpk[5][25][0])+(Cik[26][1][1]*Vpk[5][25][1])));
        Vpk[5][26][2] = (((Cik[26][2][2]*Vpk[5][25][2])+((Cik[26][0][2]*
          Vpk[5][25][0])+(Cik[26][1][2]*Vpk[5][25][1])))-(.1862*Wpk[5][26][0]));
        VWri[5][27][0] = (Vpk[5][26][0]+(.2438*Wpk[5][26][2]));
        VWri[5][27][2] = (Vpk[5][26][2]-(.2438*Wpk[5][26][0]));
        Vpk[5][27][0] = ((Cik[27][2][0]*VWri[5][27][2])+((Cik[27][0][0]*
          VWri[5][27][0])+(Cik[27][1][0]*Vpk[5][26][1])));
        Vpk[5][27][1] = ((Cik[27][2][1]*VWri[5][27][2])+((Cik[27][0][1]*
          VWri[5][27][0])+(Cik[27][1][1]*Vpk[5][26][1])));
        Vpk[5][27][2] = ((Cik[27][2][2]*VWri[5][27][2])+((Cik[27][0][2]*
          VWri[5][27][0])+(Cik[27][1][2]*Vpk[5][26][1])));
        Vpk[5][28][0] = ((Cik[28][2][0]*Vpk[5][27][2])+((Cik[28][0][0]*
          Vpk[5][27][0])+(Cik[28][1][0]*Vpk[5][27][1])));
        Vpk[5][28][1] = ((Cik[28][2][1]*Vpk[5][27][2])+((Cik[28][0][1]*
          Vpk[5][27][0])+(Cik[28][1][1]*Vpk[5][27][1])));
        Vpk[5][28][2] = ((Cik[28][2][2]*Vpk[5][27][2])+((Cik[28][0][2]*
          Vpk[5][27][0])+(Cik[28][1][2]*Vpk[5][27][1])));
        Vpk[5][29][0] = (((.051347*Wpk[5][29][2])-(.005539*Wpk[5][29][1]))+((
          Cik[29][2][0]*Vpk[5][28][2])+((Cik[29][0][0]*Vpk[5][28][0])+(
          Cik[29][1][0]*Vpk[5][28][1]))));
        Vpk[5][29][1] = (((.005539*Wpk[5][29][0])+(.035902*Wpk[5][29][2]))+((
          Cik[29][2][1]*Vpk[5][28][2])+((Cik[29][0][1]*Vpk[5][28][0])+(
          Cik[29][1][1]*Vpk[5][28][1]))));
        Vpk[5][29][2] = (((Cik[29][2][2]*Vpk[5][28][2])+((Cik[29][0][2]*
          Vpk[5][28][0])+(Cik[29][1][2]*Vpk[5][28][1])))-((.035902*Wpk[5][29][1]
          )+(.051347*Wpk[5][29][0])));
        VWri[5][30][0] = (Vpk[5][29][0]+((.038*Wpk[5][29][2])-(.018078*
          Wpk[5][29][1])));
        VWri[5][30][1] = (Vpk[5][29][1]+((.018078*Wpk[5][29][0])+(.098032*
          Wpk[5][29][2])));
        VWri[5][30][2] = (Vpk[5][29][2]-((.038*Wpk[5][29][0])+(.098032*
          Wpk[5][29][1])));
        Vpk[5][30][0] = ((Cik[30][2][0]*VWri[5][30][2])+((Cik[30][0][0]*
          VWri[5][30][0])+(Cik[30][1][0]*VWri[5][30][1])));
        Vpk[5][30][1] = ((Cik[30][2][1]*VWri[5][30][2])+((Cik[30][0][1]*
          VWri[5][30][0])+(Cik[30][1][1]*VWri[5][30][1])));
        Vpk[5][30][2] = ((Cik[30][2][2]*VWri[5][30][2])+((Cik[30][0][2]*
          VWri[5][30][0])+(Cik[30][1][2]*VWri[5][30][1])));
        Vpk[5][31][0] = ((Cik[31][2][0]*Vpk[5][30][2])+((Cik[31][0][0]*
          Vpk[5][30][0])+(Cik[31][1][0]*Vpk[5][30][1])));
        Vpk[5][31][1] = ((Cik[31][2][1]*Vpk[5][30][2])+((Cik[31][0][1]*
          Vpk[5][30][0])+(Cik[31][1][1]*Vpk[5][30][1])));
        Vpk[5][31][2] = ((Cik[31][2][2]*Vpk[5][30][2])+((Cik[31][0][2]*
          Vpk[5][30][0])+(Cik[31][1][2]*Vpk[5][30][1])));
        Vpk[5][32][0] = (((Cik[32][2][0]*Vpk[5][31][2])+((Cik[32][0][0]*
          Vpk[5][31][0])+(Cik[32][1][0]*Vpk[5][31][1])))-((.005139*Wpk[5][32][1]
          )+(.0185*Wpk[5][32][2])));
        Vpk[5][32][1] = (((.005139*Wpk[5][32][0])+(.026917*Wpk[5][32][2]))+((
          Cik[32][2][1]*Vpk[5][31][2])+((Cik[32][0][1]*Vpk[5][31][0])+(
          Cik[32][1][1]*Vpk[5][31][1]))));
        Vpk[5][32][2] = (((.0185*Wpk[5][32][0])-(.026917*Wpk[5][32][1]))+((
          Cik[32][2][2]*Vpk[5][31][2])+((Cik[32][0][2]*Vpk[5][31][0])+(
          Cik[32][1][2]*Vpk[5][31][1]))));
        Vpk[6][8][0] = -(.3202*Wpk[6][8][2]);
        Vpk[6][8][2] = (.3202*Wpk[6][8][0]);
        Vpk[7][8][0] = -(.3202*Wpk[7][8][2]);
        Vpk[7][8][2] = (.3202*Wpk[7][8][0]);
        Vpk[8][8][0] = -(.3202*pin[8][2]);
        Vpk[8][8][2] = (.3202*pin[8][0]);
        Vpk[9][11][0] = (.1715*Wpk[9][11][2]);
        Vpk[9][11][1] = -(.002*Wpk[9][11][2]);
        Vpk[9][11][2] = ((.002*Wpk[9][11][1])-(.1715*Wpk[9][11][0]));
        VWri[9][12][2] = (Vpk[9][11][2]-((.0033*Wpk[9][11][1])+(.2294*
          Wpk[9][11][0])));
        Vpk[9][12][0] = ((Cik[12][2][0]*VWri[9][12][2])+((.0013*(Cik[12][1][0]*
          Wpk[9][11][2]))+(.4009*(Cik[12][0][0]*Wpk[9][11][2]))));
        Vpk[9][12][1] = ((Cik[12][2][1]*VWri[9][12][2])+((.0013*(Cik[12][1][1]*
          Wpk[9][11][2]))+(.4009*(Cik[12][0][1]*Wpk[9][11][2]))));
        Vpk[9][12][2] = ((Cik[12][2][2]*VWri[9][12][2])+((.0013*(Cik[12][1][2]*
          Wpk[9][11][2]))+(.4009*(Cik[12][0][2]*Wpk[9][11][2]))));
        Vpk[9][13][0] = ((Cik[13][2][0]*Vpk[9][12][2])+((Cik[13][0][0]*
          Vpk[9][12][0])+(Cik[13][1][0]*Vpk[9][12][1])));
        Vpk[9][13][1] = ((Cik[13][2][1]*Vpk[9][12][2])+((Cik[13][0][1]*
          Vpk[9][12][0])+(Cik[13][1][1]*Vpk[9][12][1])));
        Vpk[9][13][2] = ((Cik[13][2][2]*Vpk[9][12][2])+((Cik[13][0][2]*
          Vpk[9][12][0])+(Cik[13][1][2]*Vpk[9][12][1])));
        Vpk[9][14][0] = ((.1862*Wpk[9][14][2])+((Cik[14][2][0]*Vpk[9][13][2])+((
          Cik[14][0][0]*Vpk[9][13][0])+(Cik[14][1][0]*Vpk[9][13][1]))));
        Vpk[9][14][1] = ((Cik[14][2][1]*Vpk[9][13][2])+((Cik[14][0][1]*
          Vpk[9][13][0])+(Cik[14][1][1]*Vpk[9][13][1])));
        Vpk[9][14][2] = (((Cik[14][2][2]*Vpk[9][13][2])+((Cik[14][0][2]*
          Vpk[9][13][0])+(Cik[14][1][2]*Vpk[9][13][1])))-(.1862*Wpk[9][14][0]));
        VWri[9][15][0] = (Vpk[9][14][0]+(.2438*Wpk[9][14][2]));
        VWri[9][15][2] = (Vpk[9][14][2]-(.2438*Wpk[9][14][0]));
        Vpk[9][15][0] = ((Cik[15][2][0]*VWri[9][15][2])+((Cik[15][0][0]*
          VWri[9][15][0])+(Cik[15][1][0]*Vpk[9][14][1])));
        Vpk[9][15][1] = ((Cik[15][2][1]*VWri[9][15][2])+((Cik[15][0][1]*
          VWri[9][15][0])+(Cik[15][1][1]*Vpk[9][14][1])));
        Vpk[9][15][2] = ((Cik[15][2][2]*VWri[9][15][2])+((Cik[15][0][2]*
          VWri[9][15][0])+(Cik[15][1][2]*Vpk[9][14][1])));
        Vpk[9][16][0] = ((Cik[16][2][0]*Vpk[9][15][2])+((Cik[16][0][0]*
          Vpk[9][15][0])+(Cik[16][1][0]*Vpk[9][15][1])));
        Vpk[9][16][1] = ((Cik[16][2][1]*Vpk[9][15][2])+((Cik[16][0][1]*
          Vpk[9][15][0])+(Cik[16][1][1]*Vpk[9][15][1])));
        Vpk[9][16][2] = ((Cik[16][2][2]*Vpk[9][15][2])+((Cik[16][0][2]*
          Vpk[9][15][0])+(Cik[16][1][2]*Vpk[9][15][1])));
        Vpk[9][17][0] = (((.005539*Wpk[9][17][1])+(.051347*Wpk[9][17][2]))+((
          Cik[17][2][0]*Vpk[9][16][2])+((Cik[17][0][0]*Vpk[9][16][0])+(
          Cik[17][1][0]*Vpk[9][16][1]))));
        Vpk[9][17][1] = (((.035902*Wpk[9][17][2])-(.005539*Wpk[9][17][0]))+((
          Cik[17][2][1]*Vpk[9][16][2])+((Cik[17][0][1]*Vpk[9][16][0])+(
          Cik[17][1][1]*Vpk[9][16][1]))));
        Vpk[9][17][2] = (((Cik[17][2][2]*Vpk[9][16][2])+((Cik[17][0][2]*
          Vpk[9][16][0])+(Cik[17][1][2]*Vpk[9][16][1])))-((.035902*Wpk[9][17][1]
          )+(.051347*Wpk[9][17][0])));
        VWri[9][18][0] = (Vpk[9][17][0]+((.018078*Wpk[9][17][1])+(.038*
          Wpk[9][17][2])));
        VWri[9][18][1] = (Vpk[9][17][1]+((.098032*Wpk[9][17][2])-(.018078*
          Wpk[9][17][0])));
        VWri[9][18][2] = (Vpk[9][17][2]-((.038*Wpk[9][17][0])+(.098032*
          Wpk[9][17][1])));
        Vpk[9][18][0] = ((Cik[18][2][0]*VWri[9][18][2])+((Cik[18][0][0]*
          VWri[9][18][0])+(Cik[18][1][0]*VWri[9][18][1])));
        Vpk[9][18][1] = ((Cik[18][2][1]*VWri[9][18][2])+((Cik[18][0][1]*
          VWri[9][18][0])+(Cik[18][1][1]*VWri[9][18][1])));
        Vpk[9][18][2] = ((Cik[18][2][2]*VWri[9][18][2])+((Cik[18][0][2]*
          VWri[9][18][0])+(Cik[18][1][2]*VWri[9][18][1])));
        Vpk[9][19][0] = ((Cik[19][2][0]*Vpk[9][18][2])+((Cik[19][0][0]*
          Vpk[9][18][0])+(Cik[19][1][0]*Vpk[9][18][1])));
        Vpk[9][19][1] = ((Cik[19][2][1]*Vpk[9][18][2])+((Cik[19][0][1]*
          Vpk[9][18][0])+(Cik[19][1][1]*Vpk[9][18][1])));
        Vpk[9][19][2] = ((Cik[19][2][2]*Vpk[9][18][2])+((Cik[19][0][2]*
          Vpk[9][18][0])+(Cik[19][1][2]*Vpk[9][18][1])));
        Vpk[9][20][0] = (((.005139*Wpk[9][20][1])-(.0185*Wpk[9][20][2]))+((
          Cik[20][2][0]*Vpk[9][19][2])+((Cik[20][0][0]*Vpk[9][19][0])+(
          Cik[20][1][0]*Vpk[9][19][1]))));
        Vpk[9][20][1] = (((.026917*Wpk[9][20][2])-(.005139*Wpk[9][20][0]))+((
          Cik[20][2][1]*Vpk[9][19][2])+((Cik[20][0][1]*Vpk[9][19][0])+(
          Cik[20][1][1]*Vpk[9][19][1]))));
        Vpk[9][20][2] = (((.0185*Wpk[9][20][0])-(.026917*Wpk[9][20][1]))+((
          Cik[20][2][2]*Vpk[9][19][2])+((Cik[20][0][2]*Vpk[9][19][0])+(
          Cik[20][1][2]*Vpk[9][19][1]))));
        Vpk[10][11][0] = (.1715*Wpk[10][11][2]);
        Vpk[10][11][1] = -(.002*Wpk[10][11][2]);
        Vpk[10][11][2] = ((.002*Wpk[10][11][1])-(.1715*Wpk[10][11][0]));
        VWri[10][12][2] = (Vpk[10][11][2]-((.0033*Wpk[10][11][1])+(.2294*
          Wpk[10][11][0])));
        Vpk[10][12][0] = ((Cik[12][2][0]*VWri[10][12][2])+((.0013*(Cik[12][1][0]
          *Wpk[10][11][2]))+(.4009*(Cik[12][0][0]*Wpk[10][11][2]))));
        Vpk[10][12][1] = ((Cik[12][2][1]*VWri[10][12][2])+((.0013*(Cik[12][1][1]
          *Wpk[10][11][2]))+(.4009*(Cik[12][0][1]*Wpk[10][11][2]))));
        Vpk[10][12][2] = ((Cik[12][2][2]*VWri[10][12][2])+((.0013*(Cik[12][1][2]
          *Wpk[10][11][2]))+(.4009*(Cik[12][0][2]*Wpk[10][11][2]))));
        Vpk[10][13][0] = ((Cik[13][2][0]*Vpk[10][12][2])+((Cik[13][0][0]*
          Vpk[10][12][0])+(Cik[13][1][0]*Vpk[10][12][1])));
        Vpk[10][13][1] = ((Cik[13][2][1]*Vpk[10][12][2])+((Cik[13][0][1]*
          Vpk[10][12][0])+(Cik[13][1][1]*Vpk[10][12][1])));
        Vpk[10][13][2] = ((Cik[13][2][2]*Vpk[10][12][2])+((Cik[13][0][2]*
          Vpk[10][12][0])+(Cik[13][1][2]*Vpk[10][12][1])));
        Vpk[10][14][0] = ((.1862*Wpk[10][14][2])+((Cik[14][2][0]*Vpk[10][13][2])
          +((Cik[14][0][0]*Vpk[10][13][0])+(Cik[14][1][0]*Vpk[10][13][1]))));
        Vpk[10][14][1] = ((Cik[14][2][1]*Vpk[10][13][2])+((Cik[14][0][1]*
          Vpk[10][13][0])+(Cik[14][1][1]*Vpk[10][13][1])));
        Vpk[10][14][2] = (((Cik[14][2][2]*Vpk[10][13][2])+((Cik[14][0][2]*
          Vpk[10][13][0])+(Cik[14][1][2]*Vpk[10][13][1])))-(.1862*Wpk[10][14][0]
          ));
        VWri[10][15][0] = (Vpk[10][14][0]+(.2438*Wpk[10][14][2]));
        VWri[10][15][2] = (Vpk[10][14][2]-(.2438*Wpk[10][14][0]));
        Vpk[10][15][0] = ((Cik[15][2][0]*VWri[10][15][2])+((Cik[15][0][0]*
          VWri[10][15][0])+(Cik[15][1][0]*Vpk[10][14][1])));
        Vpk[10][15][1] = ((Cik[15][2][1]*VWri[10][15][2])+((Cik[15][0][1]*
          VWri[10][15][0])+(Cik[15][1][1]*Vpk[10][14][1])));
        Vpk[10][15][2] = ((Cik[15][2][2]*VWri[10][15][2])+((Cik[15][0][2]*
          VWri[10][15][0])+(Cik[15][1][2]*Vpk[10][14][1])));
        Vpk[10][16][0] = ((Cik[16][2][0]*Vpk[10][15][2])+((Cik[16][0][0]*
          Vpk[10][15][0])+(Cik[16][1][0]*Vpk[10][15][1])));
        Vpk[10][16][1] = ((Cik[16][2][1]*Vpk[10][15][2])+((Cik[16][0][1]*
          Vpk[10][15][0])+(Cik[16][1][1]*Vpk[10][15][1])));
        Vpk[10][16][2] = ((Cik[16][2][2]*Vpk[10][15][2])+((Cik[16][0][2]*
          Vpk[10][15][0])+(Cik[16][1][2]*Vpk[10][15][1])));
        Vpk[10][17][0] = (((.005539*Wpk[10][17][1])+(.051347*Wpk[10][17][2]))+((
          Cik[17][2][0]*Vpk[10][16][2])+((Cik[17][0][0]*Vpk[10][16][0])+(
          Cik[17][1][0]*Vpk[10][16][1]))));
        Vpk[10][17][1] = (((.035902*Wpk[10][17][2])-(.005539*Wpk[10][17][0]))+((
          Cik[17][2][1]*Vpk[10][16][2])+((Cik[17][0][1]*Vpk[10][16][0])+(
          Cik[17][1][1]*Vpk[10][16][1]))));
        Vpk[10][17][2] = (((Cik[17][2][2]*Vpk[10][16][2])+((Cik[17][0][2]*
          Vpk[10][16][0])+(Cik[17][1][2]*Vpk[10][16][1])))-((.035902*
          Wpk[10][17][1])+(.051347*Wpk[10][17][0])));
        VWri[10][18][0] = (Vpk[10][17][0]+((.018078*Wpk[10][17][1])+(.038*
          Wpk[10][17][2])));
        VWri[10][18][1] = (Vpk[10][17][1]+((.098032*Wpk[10][17][2])-(.018078*
          Wpk[10][17][0])));
        VWri[10][18][2] = (Vpk[10][17][2]-((.038*Wpk[10][17][0])+(.098032*
          Wpk[10][17][1])));
        Vpk[10][18][0] = ((Cik[18][2][0]*VWri[10][18][2])+((Cik[18][0][0]*
          VWri[10][18][0])+(Cik[18][1][0]*VWri[10][18][1])));
        Vpk[10][18][1] = ((Cik[18][2][1]*VWri[10][18][2])+((Cik[18][0][1]*
          VWri[10][18][0])+(Cik[18][1][1]*VWri[10][18][1])));
        Vpk[10][18][2] = ((Cik[18][2][2]*VWri[10][18][2])+((Cik[18][0][2]*
          VWri[10][18][0])+(Cik[18][1][2]*VWri[10][18][1])));
        Vpk[10][19][0] = ((Cik[19][2][0]*Vpk[10][18][2])+((Cik[19][0][0]*
          Vpk[10][18][0])+(Cik[19][1][0]*Vpk[10][18][1])));
        Vpk[10][19][1] = ((Cik[19][2][1]*Vpk[10][18][2])+((Cik[19][0][1]*
          Vpk[10][18][0])+(Cik[19][1][1]*Vpk[10][18][1])));
        Vpk[10][19][2] = ((Cik[19][2][2]*Vpk[10][18][2])+((Cik[19][0][2]*
          Vpk[10][18][0])+(Cik[19][1][2]*Vpk[10][18][1])));
        Vpk[10][20][0] = (((.005139*Wpk[10][20][1])-(.0185*Wpk[10][20][2]))+((
          Cik[20][2][0]*Vpk[10][19][2])+((Cik[20][0][0]*Vpk[10][19][0])+(
          Cik[20][1][0]*Vpk[10][19][1]))));
        Vpk[10][20][1] = (((.026917*Wpk[10][20][2])-(.005139*Wpk[10][20][0]))+((
          Cik[20][2][1]*Vpk[10][19][2])+((Cik[20][0][1]*Vpk[10][19][0])+(
          Cik[20][1][1]*Vpk[10][19][1]))));
        Vpk[10][20][2] = (((.0185*Wpk[10][20][0])-(.026917*Wpk[10][20][1]))+((
          Cik[20][2][2]*Vpk[10][19][2])+((Cik[20][0][2]*Vpk[10][19][0])+(
          Cik[20][1][2]*Vpk[10][19][1]))));
        Vpk[11][11][0] = (.1715*pin[11][2]);
        Vpk[11][11][1] = -(.002*pin[11][2]);
        Vpk[11][11][2] = ((.002*pin[11][1])-(.1715*pin[11][0]));
        VWri[11][12][2] = (Vpk[11][11][2]-((.0033*pin[11][1])+(.2294*pin[11][0])
          ));
        Vpk[11][12][0] = ((Cik[12][2][0]*VWri[11][12][2])+((.0013*(Cik[12][1][0]
          *pin[11][2]))+(.4009*(Cik[12][0][0]*pin[11][2]))));
        Vpk[11][12][1] = ((Cik[12][2][1]*VWri[11][12][2])+((.0013*(Cik[12][1][1]
          *pin[11][2]))+(.4009*(Cik[12][0][1]*pin[11][2]))));
        Vpk[11][12][2] = ((Cik[12][2][2]*VWri[11][12][2])+((.0013*(Cik[12][1][2]
          *pin[11][2]))+(.4009*(Cik[12][0][2]*pin[11][2]))));
        Vpk[11][13][0] = ((Cik[13][2][0]*Vpk[11][12][2])+((Cik[13][0][0]*
          Vpk[11][12][0])+(Cik[13][1][0]*Vpk[11][12][1])));
        Vpk[11][13][1] = ((Cik[13][2][1]*Vpk[11][12][2])+((Cik[13][0][1]*
          Vpk[11][12][0])+(Cik[13][1][1]*Vpk[11][12][1])));
        Vpk[11][13][2] = ((Cik[13][2][2]*Vpk[11][12][2])+((Cik[13][0][2]*
          Vpk[11][12][0])+(Cik[13][1][2]*Vpk[11][12][1])));
        Vpk[11][14][0] = ((.1862*Wpk[11][14][2])+((Cik[14][2][0]*Vpk[11][13][2])
          +((Cik[14][0][0]*Vpk[11][13][0])+(Cik[14][1][0]*Vpk[11][13][1]))));
        Vpk[11][14][1] = ((Cik[14][2][1]*Vpk[11][13][2])+((Cik[14][0][1]*
          Vpk[11][13][0])+(Cik[14][1][1]*Vpk[11][13][1])));
        Vpk[11][14][2] = (((Cik[14][2][2]*Vpk[11][13][2])+((Cik[14][0][2]*
          Vpk[11][13][0])+(Cik[14][1][2]*Vpk[11][13][1])))-(.1862*Wpk[11][14][0]
          ));
        VWri[11][15][0] = (Vpk[11][14][0]+(.2438*Wpk[11][14][2]));
        VWri[11][15][2] = (Vpk[11][14][2]-(.2438*Wpk[11][14][0]));
        Vpk[11][15][0] = ((Cik[15][2][0]*VWri[11][15][2])+((Cik[15][0][0]*
          VWri[11][15][0])+(Cik[15][1][0]*Vpk[11][14][1])));
        Vpk[11][15][1] = ((Cik[15][2][1]*VWri[11][15][2])+((Cik[15][0][1]*
          VWri[11][15][0])+(Cik[15][1][1]*Vpk[11][14][1])));
        Vpk[11][15][2] = ((Cik[15][2][2]*VWri[11][15][2])+((Cik[15][0][2]*
          VWri[11][15][0])+(Cik[15][1][2]*Vpk[11][14][1])));
        Vpk[11][16][0] = ((Cik[16][2][0]*Vpk[11][15][2])+((Cik[16][0][0]*
          Vpk[11][15][0])+(Cik[16][1][0]*Vpk[11][15][1])));
        Vpk[11][16][1] = ((Cik[16][2][1]*Vpk[11][15][2])+((Cik[16][0][1]*
          Vpk[11][15][0])+(Cik[16][1][1]*Vpk[11][15][1])));
        Vpk[11][16][2] = ((Cik[16][2][2]*Vpk[11][15][2])+((Cik[16][0][2]*
          Vpk[11][15][0])+(Cik[16][1][2]*Vpk[11][15][1])));
        Vpk[11][17][0] = (((.005539*Wpk[11][17][1])+(.051347*Wpk[11][17][2]))+((
          Cik[17][2][0]*Vpk[11][16][2])+((Cik[17][0][0]*Vpk[11][16][0])+(
          Cik[17][1][0]*Vpk[11][16][1]))));
        Vpk[11][17][1] = (((.035902*Wpk[11][17][2])-(.005539*Wpk[11][17][0]))+((
          Cik[17][2][1]*Vpk[11][16][2])+((Cik[17][0][1]*Vpk[11][16][0])+(
          Cik[17][1][1]*Vpk[11][16][1]))));
        Vpk[11][17][2] = (((Cik[17][2][2]*Vpk[11][16][2])+((Cik[17][0][2]*
          Vpk[11][16][0])+(Cik[17][1][2]*Vpk[11][16][1])))-((.035902*
          Wpk[11][17][1])+(.051347*Wpk[11][17][0])));
        VWri[11][18][0] = (Vpk[11][17][0]+((.018078*Wpk[11][17][1])+(.038*
          Wpk[11][17][2])));
        VWri[11][18][1] = (Vpk[11][17][1]+((.098032*Wpk[11][17][2])-(.018078*
          Wpk[11][17][0])));
        VWri[11][18][2] = (Vpk[11][17][2]-((.038*Wpk[11][17][0])+(.098032*
          Wpk[11][17][1])));
        Vpk[11][18][0] = ((Cik[18][2][0]*VWri[11][18][2])+((Cik[18][0][0]*
          VWri[11][18][0])+(Cik[18][1][0]*VWri[11][18][1])));
        Vpk[11][18][1] = ((Cik[18][2][1]*VWri[11][18][2])+((Cik[18][0][1]*
          VWri[11][18][0])+(Cik[18][1][1]*VWri[11][18][1])));
        Vpk[11][18][2] = ((Cik[18][2][2]*VWri[11][18][2])+((Cik[18][0][2]*
          VWri[11][18][0])+(Cik[18][1][2]*VWri[11][18][1])));
        Vpk[11][19][0] = ((Cik[19][2][0]*Vpk[11][18][2])+((Cik[19][0][0]*
          Vpk[11][18][0])+(Cik[19][1][0]*Vpk[11][18][1])));
        Vpk[11][19][1] = ((Cik[19][2][1]*Vpk[11][18][2])+((Cik[19][0][1]*
          Vpk[11][18][0])+(Cik[19][1][1]*Vpk[11][18][1])));
        Vpk[11][19][2] = ((Cik[19][2][2]*Vpk[11][18][2])+((Cik[19][0][2]*
          Vpk[11][18][0])+(Cik[19][1][2]*Vpk[11][18][1])));
        Vpk[11][20][0] = (((.005139*Wpk[11][20][1])-(.0185*Wpk[11][20][2]))+((
          Cik[20][2][0]*Vpk[11][19][2])+((Cik[20][0][0]*Vpk[11][19][0])+(
          Cik[20][1][0]*Vpk[11][19][1]))));
        Vpk[11][20][1] = (((.026917*Wpk[11][20][2])-(.005139*Wpk[11][20][0]))+((
          Cik[20][2][1]*Vpk[11][19][2])+((Cik[20][0][1]*Vpk[11][19][0])+(
          Cik[20][1][1]*Vpk[11][19][1]))));
        Vpk[11][20][2] = (((.0185*Wpk[11][20][0])-(.026917*Wpk[11][20][1]))+((
          Cik[20][2][2]*Vpk[11][19][2])+((Cik[20][0][2]*Vpk[11][19][0])+(
          Cik[20][1][2]*Vpk[11][19][1]))));
        Vpk[12][14][0] = (.1862*Wpk[12][14][2]);
        Vpk[12][14][2] = -(.1862*Wpk[12][14][0]);
        Vpk[12][15][0] = (.43*((Cik[15][0][0]*Wpk[12][14][2])-(Cik[15][2][0]*
          Wpk[12][14][0])));
        Vpk[12][15][1] = (.43*((Cik[15][0][1]*Wpk[12][14][2])-(Cik[15][2][1]*
          Wpk[12][14][0])));
        Vpk[12][15][2] = (.43*((Cik[15][0][2]*Wpk[12][14][2])-(Cik[15][2][2]*
          Wpk[12][14][0])));
        Vpk[12][16][0] = ((Cik[16][2][0]*Vpk[12][15][2])+((Cik[16][0][0]*
          Vpk[12][15][0])+(Cik[16][1][0]*Vpk[12][15][1])));
        Vpk[12][16][1] = ((Cik[16][2][1]*Vpk[12][15][2])+((Cik[16][0][1]*
          Vpk[12][15][0])+(Cik[16][1][1]*Vpk[12][15][1])));
        Vpk[12][16][2] = ((Cik[16][2][2]*Vpk[12][15][2])+((Cik[16][0][2]*
          Vpk[12][15][0])+(Cik[16][1][2]*Vpk[12][15][1])));
        Vpk[12][17][0] = (((.005539*Wpk[12][17][1])+(.051347*Wpk[12][17][2]))+((
          Cik[17][2][0]*Vpk[12][16][2])+((Cik[17][0][0]*Vpk[12][16][0])+(
          Cik[17][1][0]*Vpk[12][16][1]))));
        Vpk[12][17][1] = (((.035902*Wpk[12][17][2])-(.005539*Wpk[12][17][0]))+((
          Cik[17][2][1]*Vpk[12][16][2])+((Cik[17][0][1]*Vpk[12][16][0])+(
          Cik[17][1][1]*Vpk[12][16][1]))));
        Vpk[12][17][2] = (((Cik[17][2][2]*Vpk[12][16][2])+((Cik[17][0][2]*
          Vpk[12][16][0])+(Cik[17][1][2]*Vpk[12][16][1])))-((.035902*
          Wpk[12][17][1])+(.051347*Wpk[12][17][0])));
        VWri[12][18][0] = (Vpk[12][17][0]+((.018078*Wpk[12][17][1])+(.038*
          Wpk[12][17][2])));
        VWri[12][18][1] = (Vpk[12][17][1]+((.098032*Wpk[12][17][2])-(.018078*
          Wpk[12][17][0])));
        VWri[12][18][2] = (Vpk[12][17][2]-((.038*Wpk[12][17][0])+(.098032*
          Wpk[12][17][1])));
        Vpk[12][18][0] = ((Cik[18][2][0]*VWri[12][18][2])+((Cik[18][0][0]*
          VWri[12][18][0])+(Cik[18][1][0]*VWri[12][18][1])));
        Vpk[12][18][1] = ((Cik[18][2][1]*VWri[12][18][2])+((Cik[18][0][1]*
          VWri[12][18][0])+(Cik[18][1][1]*VWri[12][18][1])));
        Vpk[12][18][2] = ((Cik[18][2][2]*VWri[12][18][2])+((Cik[18][0][2]*
          VWri[12][18][0])+(Cik[18][1][2]*VWri[12][18][1])));
        Vpk[12][19][0] = ((Cik[19][2][0]*Vpk[12][18][2])+((Cik[19][0][0]*
          Vpk[12][18][0])+(Cik[19][1][0]*Vpk[12][18][1])));
        Vpk[12][19][1] = ((Cik[19][2][1]*Vpk[12][18][2])+((Cik[19][0][1]*
          Vpk[12][18][0])+(Cik[19][1][1]*Vpk[12][18][1])));
        Vpk[12][19][2] = ((Cik[19][2][2]*Vpk[12][18][2])+((Cik[19][0][2]*
          Vpk[12][18][0])+(Cik[19][1][2]*Vpk[12][18][1])));
        Vpk[12][20][0] = (((.005139*Wpk[12][20][1])-(.0185*Wpk[12][20][2]))+((
          Cik[20][2][0]*Vpk[12][19][2])+((Cik[20][0][0]*Vpk[12][19][0])+(
          Cik[20][1][0]*Vpk[12][19][1]))));
        Vpk[12][20][1] = (((.026917*Wpk[12][20][2])-(.005139*Wpk[12][20][0]))+((
          Cik[20][2][1]*Vpk[12][19][2])+((Cik[20][0][1]*Vpk[12][19][0])+(
          Cik[20][1][1]*Vpk[12][19][1]))));
        Vpk[12][20][2] = (((.0185*Wpk[12][20][0])-(.026917*Wpk[12][20][1]))+((
          Cik[20][2][2]*Vpk[12][19][2])+((Cik[20][0][2]*Vpk[12][19][0])+(
          Cik[20][1][2]*Vpk[12][19][1]))));
        Vpk[13][14][0] = (.1862*Wpk[13][14][2]);
        Vpk[13][14][2] = -(.1862*Wpk[13][14][0]);
        Vpk[13][15][0] = (.43*((Cik[15][0][0]*Wpk[13][14][2])-(Cik[15][2][0]*
          Wpk[13][14][0])));
        Vpk[13][15][1] = (.43*((Cik[15][0][1]*Wpk[13][14][2])-(Cik[15][2][1]*
          Wpk[13][14][0])));
        Vpk[13][15][2] = (.43*((Cik[15][0][2]*Wpk[13][14][2])-(Cik[15][2][2]*
          Wpk[13][14][0])));
        Vpk[13][16][0] = ((Cik[16][2][0]*Vpk[13][15][2])+((Cik[16][0][0]*
          Vpk[13][15][0])+(Cik[16][1][0]*Vpk[13][15][1])));
        Vpk[13][16][1] = ((Cik[16][2][1]*Vpk[13][15][2])+((Cik[16][0][1]*
          Vpk[13][15][0])+(Cik[16][1][1]*Vpk[13][15][1])));
        Vpk[13][16][2] = ((Cik[16][2][2]*Vpk[13][15][2])+((Cik[16][0][2]*
          Vpk[13][15][0])+(Cik[16][1][2]*Vpk[13][15][1])));
        Vpk[13][17][0] = (((.005539*Wpk[13][17][1])+(.051347*Wpk[13][17][2]))+((
          Cik[17][2][0]*Vpk[13][16][2])+((Cik[17][0][0]*Vpk[13][16][0])+(
          Cik[17][1][0]*Vpk[13][16][1]))));
        Vpk[13][17][1] = (((.035902*Wpk[13][17][2])-(.005539*Wpk[13][17][0]))+((
          Cik[17][2][1]*Vpk[13][16][2])+((Cik[17][0][1]*Vpk[13][16][0])+(
          Cik[17][1][1]*Vpk[13][16][1]))));
        Vpk[13][17][2] = (((Cik[17][2][2]*Vpk[13][16][2])+((Cik[17][0][2]*
          Vpk[13][16][0])+(Cik[17][1][2]*Vpk[13][16][1])))-((.035902*
          Wpk[13][17][1])+(.051347*Wpk[13][17][0])));
        VWri[13][18][0] = (Vpk[13][17][0]+((.018078*Wpk[13][17][1])+(.038*
          Wpk[13][17][2])));
        VWri[13][18][1] = (Vpk[13][17][1]+((.098032*Wpk[13][17][2])-(.018078*
          Wpk[13][17][0])));
        VWri[13][18][2] = (Vpk[13][17][2]-((.038*Wpk[13][17][0])+(.098032*
          Wpk[13][17][1])));
        Vpk[13][18][0] = ((Cik[18][2][0]*VWri[13][18][2])+((Cik[18][0][0]*
          VWri[13][18][0])+(Cik[18][1][0]*VWri[13][18][1])));
        Vpk[13][18][1] = ((Cik[18][2][1]*VWri[13][18][2])+((Cik[18][0][1]*
          VWri[13][18][0])+(Cik[18][1][1]*VWri[13][18][1])));
        Vpk[13][18][2] = ((Cik[18][2][2]*VWri[13][18][2])+((Cik[18][0][2]*
          VWri[13][18][0])+(Cik[18][1][2]*VWri[13][18][1])));
        Vpk[13][19][0] = ((Cik[19][2][0]*Vpk[13][18][2])+((Cik[19][0][0]*
          Vpk[13][18][0])+(Cik[19][1][0]*Vpk[13][18][1])));
        Vpk[13][19][1] = ((Cik[19][2][1]*Vpk[13][18][2])+((Cik[19][0][1]*
          Vpk[13][18][0])+(Cik[19][1][1]*Vpk[13][18][1])));
        Vpk[13][19][2] = ((Cik[19][2][2]*Vpk[13][18][2])+((Cik[19][0][2]*
          Vpk[13][18][0])+(Cik[19][1][2]*Vpk[13][18][1])));
        Vpk[13][20][0] = (((.005139*Wpk[13][20][1])-(.0185*Wpk[13][20][2]))+((
          Cik[20][2][0]*Vpk[13][19][2])+((Cik[20][0][0]*Vpk[13][19][0])+(
          Cik[20][1][0]*Vpk[13][19][1]))));
        Vpk[13][20][1] = (((.026917*Wpk[13][20][2])-(.005139*Wpk[13][20][0]))+((
          Cik[20][2][1]*Vpk[13][19][2])+((Cik[20][0][1]*Vpk[13][19][0])+(
          Cik[20][1][1]*Vpk[13][19][1]))));
        Vpk[13][20][2] = (((.0185*Wpk[13][20][0])-(.026917*Wpk[13][20][1]))+((
          Cik[20][2][2]*Vpk[13][19][2])+((Cik[20][0][2]*Vpk[13][19][0])+(
          Cik[20][1][2]*Vpk[13][19][1]))));
        Vpk[14][14][0] = (.1862*pin[14][2]);
        Vpk[14][14][2] = -(.1862*pin[14][0]);
        Vpk[14][15][0] = (.43*((Cik[15][0][0]*pin[14][2])-(Cik[15][2][0]*
          pin[14][0])));
        Vpk[14][15][1] = (.43*((Cik[15][0][1]*pin[14][2])-(Cik[15][2][1]*
          pin[14][0])));
        Vpk[14][15][2] = (.43*((Cik[15][0][2]*pin[14][2])-(Cik[15][2][2]*
          pin[14][0])));
        Vpk[14][16][0] = ((Cik[16][2][0]*Vpk[14][15][2])+((Cik[16][0][0]*
          Vpk[14][15][0])+(Cik[16][1][0]*Vpk[14][15][1])));
        Vpk[14][16][1] = ((Cik[16][2][1]*Vpk[14][15][2])+((Cik[16][0][1]*
          Vpk[14][15][0])+(Cik[16][1][1]*Vpk[14][15][1])));
        Vpk[14][16][2] = ((Cik[16][2][2]*Vpk[14][15][2])+((Cik[16][0][2]*
          Vpk[14][15][0])+(Cik[16][1][2]*Vpk[14][15][1])));
        Vpk[14][17][0] = (((.005539*Wpk[14][17][1])+(.051347*Wpk[14][17][2]))+((
          Cik[17][2][0]*Vpk[14][16][2])+((Cik[17][0][0]*Vpk[14][16][0])+(
          Cik[17][1][0]*Vpk[14][16][1]))));
        Vpk[14][17][1] = (((.035902*Wpk[14][17][2])-(.005539*Wpk[14][17][0]))+((
          Cik[17][2][1]*Vpk[14][16][2])+((Cik[17][0][1]*Vpk[14][16][0])+(
          Cik[17][1][1]*Vpk[14][16][1]))));
        Vpk[14][17][2] = (((Cik[17][2][2]*Vpk[14][16][2])+((Cik[17][0][2]*
          Vpk[14][16][0])+(Cik[17][1][2]*Vpk[14][16][1])))-((.035902*
          Wpk[14][17][1])+(.051347*Wpk[14][17][0])));
        VWri[14][18][0] = (Vpk[14][17][0]+((.018078*Wpk[14][17][1])+(.038*
          Wpk[14][17][2])));
        VWri[14][18][1] = (Vpk[14][17][1]+((.098032*Wpk[14][17][2])-(.018078*
          Wpk[14][17][0])));
        VWri[14][18][2] = (Vpk[14][17][2]-((.038*Wpk[14][17][0])+(.098032*
          Wpk[14][17][1])));
        Vpk[14][18][0] = ((Cik[18][2][0]*VWri[14][18][2])+((Cik[18][0][0]*
          VWri[14][18][0])+(Cik[18][1][0]*VWri[14][18][1])));
        Vpk[14][18][1] = ((Cik[18][2][1]*VWri[14][18][2])+((Cik[18][0][1]*
          VWri[14][18][0])+(Cik[18][1][1]*VWri[14][18][1])));
        Vpk[14][18][2] = ((Cik[18][2][2]*VWri[14][18][2])+((Cik[18][0][2]*
          VWri[14][18][0])+(Cik[18][1][2]*VWri[14][18][1])));
        Vpk[14][19][0] = ((Cik[19][2][0]*Vpk[14][18][2])+((Cik[19][0][0]*
          Vpk[14][18][0])+(Cik[19][1][0]*Vpk[14][18][1])));
        Vpk[14][19][1] = ((Cik[19][2][1]*Vpk[14][18][2])+((Cik[19][0][1]*
          Vpk[14][18][0])+(Cik[19][1][1]*Vpk[14][18][1])));
        Vpk[14][19][2] = ((Cik[19][2][2]*Vpk[14][18][2])+((Cik[19][0][2]*
          Vpk[14][18][0])+(Cik[19][1][2]*Vpk[14][18][1])));
        Vpk[14][20][0] = (((.005139*Wpk[14][20][1])-(.0185*Wpk[14][20][2]))+((
          Cik[20][2][0]*Vpk[14][19][2])+((Cik[20][0][0]*Vpk[14][19][0])+(
          Cik[20][1][0]*Vpk[14][19][1]))));
        Vpk[14][20][1] = (((.026917*Wpk[14][20][2])-(.005139*Wpk[14][20][0]))+((
          Cik[20][2][1]*Vpk[14][19][2])+((Cik[20][0][1]*Vpk[14][19][0])+(
          Cik[20][1][1]*Vpk[14][19][1]))));
        Vpk[14][20][2] = (((.0185*Wpk[14][20][0])-(.026917*Wpk[14][20][1]))+((
          Cik[20][2][2]*Vpk[14][19][2])+((Cik[20][0][2]*Vpk[14][19][0])+(
          Cik[20][1][2]*Vpk[14][19][1]))));
        Vpk[15][17][0] = ((.005539*Wpk[15][17][1])+(.051347*Wpk[15][17][2]));
        Vpk[15][17][1] = ((.035902*Wpk[15][17][2])-(.005539*Wpk[15][17][0]));
        Vpk[15][17][2] = -((.035902*Wpk[15][17][1])+(.051347*Wpk[15][17][0]));
        VWri[15][18][0] = (Vpk[15][17][0]+((.018078*Wpk[15][17][1])+(.038*
          Wpk[15][17][2])));
        VWri[15][18][1] = (Vpk[15][17][1]+((.098032*Wpk[15][17][2])-(.018078*
          Wpk[15][17][0])));
        VWri[15][18][2] = (Vpk[15][17][2]-((.038*Wpk[15][17][0])+(.098032*
          Wpk[15][17][1])));
        Vpk[15][18][0] = ((Cik[18][2][0]*VWri[15][18][2])+((Cik[18][0][0]*
          VWri[15][18][0])+(Cik[18][1][0]*VWri[15][18][1])));
        Vpk[15][18][1] = ((Cik[18][2][1]*VWri[15][18][2])+((Cik[18][0][1]*
          VWri[15][18][0])+(Cik[18][1][1]*VWri[15][18][1])));
        Vpk[15][18][2] = ((Cik[18][2][2]*VWri[15][18][2])+((Cik[18][0][2]*
          VWri[15][18][0])+(Cik[18][1][2]*VWri[15][18][1])));
        Vpk[15][19][0] = ((Cik[19][2][0]*Vpk[15][18][2])+((Cik[19][0][0]*
          Vpk[15][18][0])+(Cik[19][1][0]*Vpk[15][18][1])));
        Vpk[15][19][1] = ((Cik[19][2][1]*Vpk[15][18][2])+((Cik[19][0][1]*
          Vpk[15][18][0])+(Cik[19][1][1]*Vpk[15][18][1])));
        Vpk[15][19][2] = ((Cik[19][2][2]*Vpk[15][18][2])+((Cik[19][0][2]*
          Vpk[15][18][0])+(Cik[19][1][2]*Vpk[15][18][1])));
        Vpk[15][20][0] = (((.005139*Wpk[15][20][1])-(.0185*Wpk[15][20][2]))+((
          Cik[20][2][0]*Vpk[15][19][2])+((Cik[20][0][0]*Vpk[15][19][0])+(
          Cik[20][1][0]*Vpk[15][19][1]))));
        Vpk[15][20][1] = (((.026917*Wpk[15][20][2])-(.005139*Wpk[15][20][0]))+((
          Cik[20][2][1]*Vpk[15][19][2])+((Cik[20][0][1]*Vpk[15][19][0])+(
          Cik[20][1][1]*Vpk[15][19][1]))));
        Vpk[15][20][2] = (((.0185*Wpk[15][20][0])-(.026917*Wpk[15][20][1]))+((
          Cik[20][2][2]*Vpk[15][19][2])+((Cik[20][0][2]*Vpk[15][19][0])+(
          Cik[20][1][2]*Vpk[15][19][1]))));
        Vpk[16][17][0] = ((.005539*Wpk[16][17][1])+(.051347*Wpk[16][17][2]));
        Vpk[16][17][1] = ((.035902*Wpk[16][17][2])-(.005539*Wpk[16][17][0]));
        Vpk[16][17][2] = -((.035902*Wpk[16][17][1])+(.051347*Wpk[16][17][0]));
        VWri[16][18][0] = (Vpk[16][17][0]+((.018078*Wpk[16][17][1])+(.038*
          Wpk[16][17][2])));
        VWri[16][18][1] = (Vpk[16][17][1]+((.098032*Wpk[16][17][2])-(.018078*
          Wpk[16][17][0])));
        VWri[16][18][2] = (Vpk[16][17][2]-((.038*Wpk[16][17][0])+(.098032*
          Wpk[16][17][1])));
        Vpk[16][18][0] = ((Cik[18][2][0]*VWri[16][18][2])+((Cik[18][0][0]*
          VWri[16][18][0])+(Cik[18][1][0]*VWri[16][18][1])));
        Vpk[16][18][1] = ((Cik[18][2][1]*VWri[16][18][2])+((Cik[18][0][1]*
          VWri[16][18][0])+(Cik[18][1][1]*VWri[16][18][1])));
        Vpk[16][18][2] = ((Cik[18][2][2]*VWri[16][18][2])+((Cik[18][0][2]*
          VWri[16][18][0])+(Cik[18][1][2]*VWri[16][18][1])));
        Vpk[16][19][0] = ((Cik[19][2][0]*Vpk[16][18][2])+((Cik[19][0][0]*
          Vpk[16][18][0])+(Cik[19][1][0]*Vpk[16][18][1])));
        Vpk[16][19][1] = ((Cik[19][2][1]*Vpk[16][18][2])+((Cik[19][0][1]*
          Vpk[16][18][0])+(Cik[19][1][1]*Vpk[16][18][1])));
        Vpk[16][19][2] = ((Cik[19][2][2]*Vpk[16][18][2])+((Cik[19][0][2]*
          Vpk[16][18][0])+(Cik[19][1][2]*Vpk[16][18][1])));
        Vpk[16][20][0] = (((.005139*Wpk[16][20][1])-(.0185*Wpk[16][20][2]))+((
          Cik[20][2][0]*Vpk[16][19][2])+((Cik[20][0][0]*Vpk[16][19][0])+(
          Cik[20][1][0]*Vpk[16][19][1]))));
        Vpk[16][20][1] = (((.026917*Wpk[16][20][2])-(.005139*Wpk[16][20][0]))+((
          Cik[20][2][1]*Vpk[16][19][2])+((Cik[20][0][1]*Vpk[16][19][0])+(
          Cik[20][1][1]*Vpk[16][19][1]))));
        Vpk[16][20][2] = (((.0185*Wpk[16][20][0])-(.026917*Wpk[16][20][1]))+((
          Cik[20][2][2]*Vpk[16][19][2])+((Cik[20][0][2]*Vpk[16][19][0])+(
          Cik[20][1][2]*Vpk[16][19][1]))));
        Vpk[17][17][0] = ((.005539*pin[17][1])+(.051347*pin[17][2]));
        Vpk[17][17][1] = ((.035902*pin[17][2])-(.005539*pin[17][0]));
        Vpk[17][17][2] = -((.035902*pin[17][1])+(.051347*pin[17][0]));
        VWri[17][18][0] = (Vpk[17][17][0]+((.018078*pin[17][1])+(.038*pin[17][2]
          )));
        VWri[17][18][1] = (Vpk[17][17][1]+((.098032*pin[17][2])-(.018078*
          pin[17][0])));
        VWri[17][18][2] = (Vpk[17][17][2]-((.038*pin[17][0])+(.098032*pin[17][1]
          )));
        Vpk[17][18][0] = ((Cik[18][2][0]*VWri[17][18][2])+((Cik[18][0][0]*
          VWri[17][18][0])+(Cik[18][1][0]*VWri[17][18][1])));
        Vpk[17][18][1] = ((Cik[18][2][1]*VWri[17][18][2])+((Cik[18][0][1]*
          VWri[17][18][0])+(Cik[18][1][1]*VWri[17][18][1])));
        Vpk[17][18][2] = ((Cik[18][2][2]*VWri[17][18][2])+((Cik[18][0][2]*
          VWri[17][18][0])+(Cik[18][1][2]*VWri[17][18][1])));
        Vpk[17][19][0] = ((Cik[19][2][0]*Vpk[17][18][2])+((Cik[19][0][0]*
          Vpk[17][18][0])+(Cik[19][1][0]*Vpk[17][18][1])));
        Vpk[17][19][1] = ((Cik[19][2][1]*Vpk[17][18][2])+((Cik[19][0][1]*
          Vpk[17][18][0])+(Cik[19][1][1]*Vpk[17][18][1])));
        Vpk[17][19][2] = ((Cik[19][2][2]*Vpk[17][18][2])+((Cik[19][0][2]*
          Vpk[17][18][0])+(Cik[19][1][2]*Vpk[17][18][1])));
        Vpk[17][20][0] = (((.005139*Wpk[17][20][1])-(.0185*Wpk[17][20][2]))+((
          Cik[20][2][0]*Vpk[17][19][2])+((Cik[20][0][0]*Vpk[17][19][0])+(
          Cik[20][1][0]*Vpk[17][19][1]))));
        Vpk[17][20][1] = (((.026917*Wpk[17][20][2])-(.005139*Wpk[17][20][0]))+((
          Cik[20][2][1]*Vpk[17][19][2])+((Cik[20][0][1]*Vpk[17][19][0])+(
          Cik[20][1][1]*Vpk[17][19][1]))));
        Vpk[17][20][2] = (((.0185*Wpk[17][20][0])-(.026917*Wpk[17][20][1]))+((
          Cik[20][2][2]*Vpk[17][19][2])+((Cik[20][0][2]*Vpk[17][19][0])+(
          Cik[20][1][2]*Vpk[17][19][1]))));
        Vpk[18][20][0] = ((.005139*Wpk[18][20][1])-(.0185*Wpk[18][20][2]));
        Vpk[18][20][1] = ((.026917*Wpk[18][20][2])-(.005139*Wpk[18][20][0]));
        Vpk[18][20][2] = ((.0185*Wpk[18][20][0])-(.026917*Wpk[18][20][1]));
        Vpk[19][20][0] = ((.005139*Wpk[19][20][1])-(.0185*Wpk[19][20][2]));
        Vpk[19][20][1] = ((.026917*Wpk[19][20][2])-(.005139*Wpk[19][20][0]));
        Vpk[19][20][2] = ((.0185*Wpk[19][20][0])-(.026917*Wpk[19][20][1]));
        Vpk[20][20][0] = ((.005139*pin[20][1])-(.0185*pin[20][2]));
        Vpk[20][20][1] = ((.026917*pin[20][2])-(.005139*pin[20][0]));
        Vpk[20][20][2] = ((.0185*pin[20][0])-(.026917*pin[20][1]));
        Vpk[21][23][0] = (.1715*Wpk[21][23][2]);
        Vpk[21][23][1] = -(.002*Wpk[21][23][2]);
        Vpk[21][23][2] = ((.002*Wpk[21][23][1])-(.1715*Wpk[21][23][0]));
        VWri[21][24][2] = (Vpk[21][23][2]-((.0033*Wpk[21][23][1])+(.2294*
          Wpk[21][23][0])));
        Vpk[21][24][0] = ((Cik[24][2][0]*VWri[21][24][2])+((.0013*(Cik[24][1][0]
          *Wpk[21][23][2]))+(.4009*(Cik[24][0][0]*Wpk[21][23][2]))));
        Vpk[21][24][1] = ((Cik[24][2][1]*VWri[21][24][2])+((.0013*(Cik[24][1][1]
          *Wpk[21][23][2]))+(.4009*(Cik[24][0][1]*Wpk[21][23][2]))));
        Vpk[21][24][2] = ((Cik[24][2][2]*VWri[21][24][2])+((.0013*(Cik[24][1][2]
          *Wpk[21][23][2]))+(.4009*(Cik[24][0][2]*Wpk[21][23][2]))));
        Vpk[21][25][0] = ((Cik[25][2][0]*Vpk[21][24][2])+((Cik[25][0][0]*
          Vpk[21][24][0])+(Cik[25][1][0]*Vpk[21][24][1])));
        Vpk[21][25][1] = ((Cik[25][2][1]*Vpk[21][24][2])+((Cik[25][0][1]*
          Vpk[21][24][0])+(Cik[25][1][1]*Vpk[21][24][1])));
        Vpk[21][25][2] = ((Cik[25][2][2]*Vpk[21][24][2])+((Cik[25][0][2]*
          Vpk[21][24][0])+(Cik[25][1][2]*Vpk[21][24][1])));
        Vpk[21][26][0] = ((.1862*Wpk[21][26][2])+((Cik[26][2][0]*Vpk[21][25][2])
          +((Cik[26][0][0]*Vpk[21][25][0])+(Cik[26][1][0]*Vpk[21][25][1]))));
        Vpk[21][26][1] = ((Cik[26][2][1]*Vpk[21][25][2])+((Cik[26][0][1]*
          Vpk[21][25][0])+(Cik[26][1][1]*Vpk[21][25][1])));
        Vpk[21][26][2] = (((Cik[26][2][2]*Vpk[21][25][2])+((Cik[26][0][2]*
          Vpk[21][25][0])+(Cik[26][1][2]*Vpk[21][25][1])))-(.1862*Wpk[21][26][0]
          ));
        VWri[21][27][0] = (Vpk[21][26][0]+(.2438*Wpk[21][26][2]));
        VWri[21][27][2] = (Vpk[21][26][2]-(.2438*Wpk[21][26][0]));
        Vpk[21][27][0] = ((Cik[27][2][0]*VWri[21][27][2])+((Cik[27][0][0]*
          VWri[21][27][0])+(Cik[27][1][0]*Vpk[21][26][1])));
        Vpk[21][27][1] = ((Cik[27][2][1]*VWri[21][27][2])+((Cik[27][0][1]*
          VWri[21][27][0])+(Cik[27][1][1]*Vpk[21][26][1])));
        Vpk[21][27][2] = ((Cik[27][2][2]*VWri[21][27][2])+((Cik[27][0][2]*
          VWri[21][27][0])+(Cik[27][1][2]*Vpk[21][26][1])));
        Vpk[21][28][0] = ((Cik[28][2][0]*Vpk[21][27][2])+((Cik[28][0][0]*
          Vpk[21][27][0])+(Cik[28][1][0]*Vpk[21][27][1])));
        Vpk[21][28][1] = ((Cik[28][2][1]*Vpk[21][27][2])+((Cik[28][0][1]*
          Vpk[21][27][0])+(Cik[28][1][1]*Vpk[21][27][1])));
        Vpk[21][28][2] = ((Cik[28][2][2]*Vpk[21][27][2])+((Cik[28][0][2]*
          Vpk[21][27][0])+(Cik[28][1][2]*Vpk[21][27][1])));
        Vpk[21][29][0] = (((.051347*Wpk[21][29][2])-(.005539*Wpk[21][29][1]))+((
          Cik[29][2][0]*Vpk[21][28][2])+((Cik[29][0][0]*Vpk[21][28][0])+(
          Cik[29][1][0]*Vpk[21][28][1]))));
        Vpk[21][29][1] = (((.005539*Wpk[21][29][0])+(.035902*Wpk[21][29][2]))+((
          Cik[29][2][1]*Vpk[21][28][2])+((Cik[29][0][1]*Vpk[21][28][0])+(
          Cik[29][1][1]*Vpk[21][28][1]))));
        Vpk[21][29][2] = (((Cik[29][2][2]*Vpk[21][28][2])+((Cik[29][0][2]*
          Vpk[21][28][0])+(Cik[29][1][2]*Vpk[21][28][1])))-((.035902*
          Wpk[21][29][1])+(.051347*Wpk[21][29][0])));
        VWri[21][30][0] = (Vpk[21][29][0]+((.038*Wpk[21][29][2])-(.018078*
          Wpk[21][29][1])));
        VWri[21][30][1] = (Vpk[21][29][1]+((.018078*Wpk[21][29][0])+(.098032*
          Wpk[21][29][2])));
        VWri[21][30][2] = (Vpk[21][29][2]-((.038*Wpk[21][29][0])+(.098032*
          Wpk[21][29][1])));
        Vpk[21][30][0] = ((Cik[30][2][0]*VWri[21][30][2])+((Cik[30][0][0]*
          VWri[21][30][0])+(Cik[30][1][0]*VWri[21][30][1])));
        Vpk[21][30][1] = ((Cik[30][2][1]*VWri[21][30][2])+((Cik[30][0][1]*
          VWri[21][30][0])+(Cik[30][1][1]*VWri[21][30][1])));
        Vpk[21][30][2] = ((Cik[30][2][2]*VWri[21][30][2])+((Cik[30][0][2]*
          VWri[21][30][0])+(Cik[30][1][2]*VWri[21][30][1])));
        Vpk[21][31][0] = ((Cik[31][2][0]*Vpk[21][30][2])+((Cik[31][0][0]*
          Vpk[21][30][0])+(Cik[31][1][0]*Vpk[21][30][1])));
        Vpk[21][31][1] = ((Cik[31][2][1]*Vpk[21][30][2])+((Cik[31][0][1]*
          Vpk[21][30][0])+(Cik[31][1][1]*Vpk[21][30][1])));
        Vpk[21][31][2] = ((Cik[31][2][2]*Vpk[21][30][2])+((Cik[31][0][2]*
          Vpk[21][30][0])+(Cik[31][1][2]*Vpk[21][30][1])));
        Vpk[21][32][0] = (((Cik[32][2][0]*Vpk[21][31][2])+((Cik[32][0][0]*
          Vpk[21][31][0])+(Cik[32][1][0]*Vpk[21][31][1])))-((.005139*
          Wpk[21][32][1])+(.0185*Wpk[21][32][2])));
        Vpk[21][32][1] = (((.005139*Wpk[21][32][0])+(.026917*Wpk[21][32][2]))+((
          Cik[32][2][1]*Vpk[21][31][2])+((Cik[32][0][1]*Vpk[21][31][0])+(
          Cik[32][1][1]*Vpk[21][31][1]))));
        Vpk[21][32][2] = (((.0185*Wpk[21][32][0])-(.026917*Wpk[21][32][1]))+((
          Cik[32][2][2]*Vpk[21][31][2])+((Cik[32][0][2]*Vpk[21][31][0])+(
          Cik[32][1][2]*Vpk[21][31][1]))));
        Vpk[22][23][0] = (.1715*Wpk[22][23][2]);
        Vpk[22][23][1] = -(.002*Wpk[22][23][2]);
        Vpk[22][23][2] = ((.002*Wpk[22][23][1])-(.1715*Wpk[22][23][0]));
        VWri[22][24][2] = (Vpk[22][23][2]-((.0033*Wpk[22][23][1])+(.2294*
          Wpk[22][23][0])));
        Vpk[22][24][0] = ((Cik[24][2][0]*VWri[22][24][2])+((.0013*(Cik[24][1][0]
          *Wpk[22][23][2]))+(.4009*(Cik[24][0][0]*Wpk[22][23][2]))));
        Vpk[22][24][1] = ((Cik[24][2][1]*VWri[22][24][2])+((.0013*(Cik[24][1][1]
          *Wpk[22][23][2]))+(.4009*(Cik[24][0][1]*Wpk[22][23][2]))));
        Vpk[22][24][2] = ((Cik[24][2][2]*VWri[22][24][2])+((.0013*(Cik[24][1][2]
          *Wpk[22][23][2]))+(.4009*(Cik[24][0][2]*Wpk[22][23][2]))));
        Vpk[22][25][0] = ((Cik[25][2][0]*Vpk[22][24][2])+((Cik[25][0][0]*
          Vpk[22][24][0])+(Cik[25][1][0]*Vpk[22][24][1])));
        Vpk[22][25][1] = ((Cik[25][2][1]*Vpk[22][24][2])+((Cik[25][0][1]*
          Vpk[22][24][0])+(Cik[25][1][1]*Vpk[22][24][1])));
        Vpk[22][25][2] = ((Cik[25][2][2]*Vpk[22][24][2])+((Cik[25][0][2]*
          Vpk[22][24][0])+(Cik[25][1][2]*Vpk[22][24][1])));
        Vpk[22][26][0] = ((.1862*Wpk[22][26][2])+((Cik[26][2][0]*Vpk[22][25][2])
          +((Cik[26][0][0]*Vpk[22][25][0])+(Cik[26][1][0]*Vpk[22][25][1]))));
        Vpk[22][26][1] = ((Cik[26][2][1]*Vpk[22][25][2])+((Cik[26][0][1]*
          Vpk[22][25][0])+(Cik[26][1][1]*Vpk[22][25][1])));
        Vpk[22][26][2] = (((Cik[26][2][2]*Vpk[22][25][2])+((Cik[26][0][2]*
          Vpk[22][25][0])+(Cik[26][1][2]*Vpk[22][25][1])))-(.1862*Wpk[22][26][0]
          ));
        VWri[22][27][0] = (Vpk[22][26][0]+(.2438*Wpk[22][26][2]));
        VWri[22][27][2] = (Vpk[22][26][2]-(.2438*Wpk[22][26][0]));
        Vpk[22][27][0] = ((Cik[27][2][0]*VWri[22][27][2])+((Cik[27][0][0]*
          VWri[22][27][0])+(Cik[27][1][0]*Vpk[22][26][1])));
        Vpk[22][27][1] = ((Cik[27][2][1]*VWri[22][27][2])+((Cik[27][0][1]*
          VWri[22][27][0])+(Cik[27][1][1]*Vpk[22][26][1])));
        Vpk[22][27][2] = ((Cik[27][2][2]*VWri[22][27][2])+((Cik[27][0][2]*
          VWri[22][27][0])+(Cik[27][1][2]*Vpk[22][26][1])));
        Vpk[22][28][0] = ((Cik[28][2][0]*Vpk[22][27][2])+((Cik[28][0][0]*
          Vpk[22][27][0])+(Cik[28][1][0]*Vpk[22][27][1])));
        Vpk[22][28][1] = ((Cik[28][2][1]*Vpk[22][27][2])+((Cik[28][0][1]*
          Vpk[22][27][0])+(Cik[28][1][1]*Vpk[22][27][1])));
        Vpk[22][28][2] = ((Cik[28][2][2]*Vpk[22][27][2])+((Cik[28][0][2]*
          Vpk[22][27][0])+(Cik[28][1][2]*Vpk[22][27][1])));
        Vpk[22][29][0] = (((.051347*Wpk[22][29][2])-(.005539*Wpk[22][29][1]))+((
          Cik[29][2][0]*Vpk[22][28][2])+((Cik[29][0][0]*Vpk[22][28][0])+(
          Cik[29][1][0]*Vpk[22][28][1]))));
        Vpk[22][29][1] = (((.005539*Wpk[22][29][0])+(.035902*Wpk[22][29][2]))+((
          Cik[29][2][1]*Vpk[22][28][2])+((Cik[29][0][1]*Vpk[22][28][0])+(
          Cik[29][1][1]*Vpk[22][28][1]))));
        Vpk[22][29][2] = (((Cik[29][2][2]*Vpk[22][28][2])+((Cik[29][0][2]*
          Vpk[22][28][0])+(Cik[29][1][2]*Vpk[22][28][1])))-((.035902*
          Wpk[22][29][1])+(.051347*Wpk[22][29][0])));
        VWri[22][30][0] = (Vpk[22][29][0]+((.038*Wpk[22][29][2])-(.018078*
          Wpk[22][29][1])));
        VWri[22][30][1] = (Vpk[22][29][1]+((.018078*Wpk[22][29][0])+(.098032*
          Wpk[22][29][2])));
        VWri[22][30][2] = (Vpk[22][29][2]-((.038*Wpk[22][29][0])+(.098032*
          Wpk[22][29][1])));
        Vpk[22][30][0] = ((Cik[30][2][0]*VWri[22][30][2])+((Cik[30][0][0]*
          VWri[22][30][0])+(Cik[30][1][0]*VWri[22][30][1])));
        Vpk[22][30][1] = ((Cik[30][2][1]*VWri[22][30][2])+((Cik[30][0][1]*
          VWri[22][30][0])+(Cik[30][1][1]*VWri[22][30][1])));
        Vpk[22][30][2] = ((Cik[30][2][2]*VWri[22][30][2])+((Cik[30][0][2]*
          VWri[22][30][0])+(Cik[30][1][2]*VWri[22][30][1])));
        Vpk[22][31][0] = ((Cik[31][2][0]*Vpk[22][30][2])+((Cik[31][0][0]*
          Vpk[22][30][0])+(Cik[31][1][0]*Vpk[22][30][1])));
        Vpk[22][31][1] = ((Cik[31][2][1]*Vpk[22][30][2])+((Cik[31][0][1]*
          Vpk[22][30][0])+(Cik[31][1][1]*Vpk[22][30][1])));
        Vpk[22][31][2] = ((Cik[31][2][2]*Vpk[22][30][2])+((Cik[31][0][2]*
          Vpk[22][30][0])+(Cik[31][1][2]*Vpk[22][30][1])));
        Vpk[22][32][0] = (((Cik[32][2][0]*Vpk[22][31][2])+((Cik[32][0][0]*
          Vpk[22][31][0])+(Cik[32][1][0]*Vpk[22][31][1])))-((.005139*
          Wpk[22][32][1])+(.0185*Wpk[22][32][2])));
        Vpk[22][32][1] = (((.005139*Wpk[22][32][0])+(.026917*Wpk[22][32][2]))+((
          Cik[32][2][1]*Vpk[22][31][2])+((Cik[32][0][1]*Vpk[22][31][0])+(
          Cik[32][1][1]*Vpk[22][31][1]))));
        Vpk[22][32][2] = (((.0185*Wpk[22][32][0])-(.026917*Wpk[22][32][1]))+((
          Cik[32][2][2]*Vpk[22][31][2])+((Cik[32][0][2]*Vpk[22][31][0])+(
          Cik[32][1][2]*Vpk[22][31][1]))));
        Vpk[23][23][0] = (.1715*pin[23][2]);
        Vpk[23][23][1] = -(.002*pin[23][2]);
        Vpk[23][23][2] = ((.002*pin[23][1])-(.1715*pin[23][0]));
        VWri[23][24][2] = (Vpk[23][23][2]-((.0033*pin[23][1])+(.2294*pin[23][0])
          ));
        Vpk[23][24][0] = ((Cik[24][2][0]*VWri[23][24][2])+((.0013*(Cik[24][1][0]
          *pin[23][2]))+(.4009*(Cik[24][0][0]*pin[23][2]))));
        Vpk[23][24][1] = ((Cik[24][2][1]*VWri[23][24][2])+((.0013*(Cik[24][1][1]
          *pin[23][2]))+(.4009*(Cik[24][0][1]*pin[23][2]))));
        Vpk[23][24][2] = ((Cik[24][2][2]*VWri[23][24][2])+((.0013*(Cik[24][1][2]
          *pin[23][2]))+(.4009*(Cik[24][0][2]*pin[23][2]))));
        Vpk[23][25][0] = ((Cik[25][2][0]*Vpk[23][24][2])+((Cik[25][0][0]*
          Vpk[23][24][0])+(Cik[25][1][0]*Vpk[23][24][1])));
        Vpk[23][25][1] = ((Cik[25][2][1]*Vpk[23][24][2])+((Cik[25][0][1]*
          Vpk[23][24][0])+(Cik[25][1][1]*Vpk[23][24][1])));
        Vpk[23][25][2] = ((Cik[25][2][2]*Vpk[23][24][2])+((Cik[25][0][2]*
          Vpk[23][24][0])+(Cik[25][1][2]*Vpk[23][24][1])));
        Vpk[23][26][0] = ((.1862*Wpk[23][26][2])+((Cik[26][2][0]*Vpk[23][25][2])
          +((Cik[26][0][0]*Vpk[23][25][0])+(Cik[26][1][0]*Vpk[23][25][1]))));
        Vpk[23][26][1] = ((Cik[26][2][1]*Vpk[23][25][2])+((Cik[26][0][1]*
          Vpk[23][25][0])+(Cik[26][1][1]*Vpk[23][25][1])));
        Vpk[23][26][2] = (((Cik[26][2][2]*Vpk[23][25][2])+((Cik[26][0][2]*
          Vpk[23][25][0])+(Cik[26][1][2]*Vpk[23][25][1])))-(.1862*Wpk[23][26][0]
          ));
        VWri[23][27][0] = (Vpk[23][26][0]+(.2438*Wpk[23][26][2]));
        VWri[23][27][2] = (Vpk[23][26][2]-(.2438*Wpk[23][26][0]));
        Vpk[23][27][0] = ((Cik[27][2][0]*VWri[23][27][2])+((Cik[27][0][0]*
          VWri[23][27][0])+(Cik[27][1][0]*Vpk[23][26][1])));
        Vpk[23][27][1] = ((Cik[27][2][1]*VWri[23][27][2])+((Cik[27][0][1]*
          VWri[23][27][0])+(Cik[27][1][1]*Vpk[23][26][1])));
        Vpk[23][27][2] = ((Cik[27][2][2]*VWri[23][27][2])+((Cik[27][0][2]*
          VWri[23][27][0])+(Cik[27][1][2]*Vpk[23][26][1])));
        Vpk[23][28][0] = ((Cik[28][2][0]*Vpk[23][27][2])+((Cik[28][0][0]*
          Vpk[23][27][0])+(Cik[28][1][0]*Vpk[23][27][1])));
        Vpk[23][28][1] = ((Cik[28][2][1]*Vpk[23][27][2])+((Cik[28][0][1]*
          Vpk[23][27][0])+(Cik[28][1][1]*Vpk[23][27][1])));
        Vpk[23][28][2] = ((Cik[28][2][2]*Vpk[23][27][2])+((Cik[28][0][2]*
          Vpk[23][27][0])+(Cik[28][1][2]*Vpk[23][27][1])));
        Vpk[23][29][0] = (((.051347*Wpk[23][29][2])-(.005539*Wpk[23][29][1]))+((
          Cik[29][2][0]*Vpk[23][28][2])+((Cik[29][0][0]*Vpk[23][28][0])+(
          Cik[29][1][0]*Vpk[23][28][1]))));
        Vpk[23][29][1] = (((.005539*Wpk[23][29][0])+(.035902*Wpk[23][29][2]))+((
          Cik[29][2][1]*Vpk[23][28][2])+((Cik[29][0][1]*Vpk[23][28][0])+(
          Cik[29][1][1]*Vpk[23][28][1]))));
        Vpk[23][29][2] = (((Cik[29][2][2]*Vpk[23][28][2])+((Cik[29][0][2]*
          Vpk[23][28][0])+(Cik[29][1][2]*Vpk[23][28][1])))-((.035902*
          Wpk[23][29][1])+(.051347*Wpk[23][29][0])));
        VWri[23][30][0] = (Vpk[23][29][0]+((.038*Wpk[23][29][2])-(.018078*
          Wpk[23][29][1])));
        VWri[23][30][1] = (Vpk[23][29][1]+((.018078*Wpk[23][29][0])+(.098032*
          Wpk[23][29][2])));
        VWri[23][30][2] = (Vpk[23][29][2]-((.038*Wpk[23][29][0])+(.098032*
          Wpk[23][29][1])));
        Vpk[23][30][0] = ((Cik[30][2][0]*VWri[23][30][2])+((Cik[30][0][0]*
          VWri[23][30][0])+(Cik[30][1][0]*VWri[23][30][1])));
        Vpk[23][30][1] = ((Cik[30][2][1]*VWri[23][30][2])+((Cik[30][0][1]*
          VWri[23][30][0])+(Cik[30][1][1]*VWri[23][30][1])));
        Vpk[23][30][2] = ((Cik[30][2][2]*VWri[23][30][2])+((Cik[30][0][2]*
          VWri[23][30][0])+(Cik[30][1][2]*VWri[23][30][1])));
        Vpk[23][31][0] = ((Cik[31][2][0]*Vpk[23][30][2])+((Cik[31][0][0]*
          Vpk[23][30][0])+(Cik[31][1][0]*Vpk[23][30][1])));
        Vpk[23][31][1] = ((Cik[31][2][1]*Vpk[23][30][2])+((Cik[31][0][1]*
          Vpk[23][30][0])+(Cik[31][1][1]*Vpk[23][30][1])));
        Vpk[23][31][2] = ((Cik[31][2][2]*Vpk[23][30][2])+((Cik[31][0][2]*
          Vpk[23][30][0])+(Cik[31][1][2]*Vpk[23][30][1])));
        Vpk[23][32][0] = (((Cik[32][2][0]*Vpk[23][31][2])+((Cik[32][0][0]*
          Vpk[23][31][0])+(Cik[32][1][0]*Vpk[23][31][1])))-((.005139*
          Wpk[23][32][1])+(.0185*Wpk[23][32][2])));
        Vpk[23][32][1] = (((.005139*Wpk[23][32][0])+(.026917*Wpk[23][32][2]))+((
          Cik[32][2][1]*Vpk[23][31][2])+((Cik[32][0][1]*Vpk[23][31][0])+(
          Cik[32][1][1]*Vpk[23][31][1]))));
        Vpk[23][32][2] = (((.0185*Wpk[23][32][0])-(.026917*Wpk[23][32][1]))+((
          Cik[32][2][2]*Vpk[23][31][2])+((Cik[32][0][2]*Vpk[23][31][0])+(
          Cik[32][1][2]*Vpk[23][31][1]))));
        Vpk[24][26][0] = (.1862*Wpk[24][26][2]);
        Vpk[24][26][2] = -(.1862*Wpk[24][26][0]);
        Vpk[24][27][0] = (.43*((Cik[27][0][0]*Wpk[24][26][2])-(Cik[27][2][0]*
          Wpk[24][26][0])));
        Vpk[24][27][1] = (.43*((Cik[27][0][1]*Wpk[24][26][2])-(Cik[27][2][1]*
          Wpk[24][26][0])));
        Vpk[24][27][2] = (.43*((Cik[27][0][2]*Wpk[24][26][2])-(Cik[27][2][2]*
          Wpk[24][26][0])));
        Vpk[24][28][0] = ((Cik[28][2][0]*Vpk[24][27][2])+((Cik[28][0][0]*
          Vpk[24][27][0])+(Cik[28][1][0]*Vpk[24][27][1])));
        Vpk[24][28][1] = ((Cik[28][2][1]*Vpk[24][27][2])+((Cik[28][0][1]*
          Vpk[24][27][0])+(Cik[28][1][1]*Vpk[24][27][1])));
        Vpk[24][28][2] = ((Cik[28][2][2]*Vpk[24][27][2])+((Cik[28][0][2]*
          Vpk[24][27][0])+(Cik[28][1][2]*Vpk[24][27][1])));
        Vpk[24][29][0] = (((.051347*Wpk[24][29][2])-(.005539*Wpk[24][29][1]))+((
          Cik[29][2][0]*Vpk[24][28][2])+((Cik[29][0][0]*Vpk[24][28][0])+(
          Cik[29][1][0]*Vpk[24][28][1]))));
        Vpk[24][29][1] = (((.005539*Wpk[24][29][0])+(.035902*Wpk[24][29][2]))+((
          Cik[29][2][1]*Vpk[24][28][2])+((Cik[29][0][1]*Vpk[24][28][0])+(
          Cik[29][1][1]*Vpk[24][28][1]))));
        Vpk[24][29][2] = (((Cik[29][2][2]*Vpk[24][28][2])+((Cik[29][0][2]*
          Vpk[24][28][0])+(Cik[29][1][2]*Vpk[24][28][1])))-((.035902*
          Wpk[24][29][1])+(.051347*Wpk[24][29][0])));
        VWri[24][30][0] = (Vpk[24][29][0]+((.038*Wpk[24][29][2])-(.018078*
          Wpk[24][29][1])));
        VWri[24][30][1] = (Vpk[24][29][1]+((.018078*Wpk[24][29][0])+(.098032*
          Wpk[24][29][2])));
        VWri[24][30][2] = (Vpk[24][29][2]-((.038*Wpk[24][29][0])+(.098032*
          Wpk[24][29][1])));
        Vpk[24][30][0] = ((Cik[30][2][0]*VWri[24][30][2])+((Cik[30][0][0]*
          VWri[24][30][0])+(Cik[30][1][0]*VWri[24][30][1])));
        Vpk[24][30][1] = ((Cik[30][2][1]*VWri[24][30][2])+((Cik[30][0][1]*
          VWri[24][30][0])+(Cik[30][1][1]*VWri[24][30][1])));
        Vpk[24][30][2] = ((Cik[30][2][2]*VWri[24][30][2])+((Cik[30][0][2]*
          VWri[24][30][0])+(Cik[30][1][2]*VWri[24][30][1])));
        Vpk[24][31][0] = ((Cik[31][2][0]*Vpk[24][30][2])+((Cik[31][0][0]*
          Vpk[24][30][0])+(Cik[31][1][0]*Vpk[24][30][1])));
        Vpk[24][31][1] = ((Cik[31][2][1]*Vpk[24][30][2])+((Cik[31][0][1]*
          Vpk[24][30][0])+(Cik[31][1][1]*Vpk[24][30][1])));
        Vpk[24][31][2] = ((Cik[31][2][2]*Vpk[24][30][2])+((Cik[31][0][2]*
          Vpk[24][30][0])+(Cik[31][1][2]*Vpk[24][30][1])));
        Vpk[24][32][0] = (((Cik[32][2][0]*Vpk[24][31][2])+((Cik[32][0][0]*
          Vpk[24][31][0])+(Cik[32][1][0]*Vpk[24][31][1])))-((.005139*
          Wpk[24][32][1])+(.0185*Wpk[24][32][2])));
        Vpk[24][32][1] = (((.005139*Wpk[24][32][0])+(.026917*Wpk[24][32][2]))+((
          Cik[32][2][1]*Vpk[24][31][2])+((Cik[32][0][1]*Vpk[24][31][0])+(
          Cik[32][1][1]*Vpk[24][31][1]))));
        Vpk[24][32][2] = (((.0185*Wpk[24][32][0])-(.026917*Wpk[24][32][1]))+((
          Cik[32][2][2]*Vpk[24][31][2])+((Cik[32][0][2]*Vpk[24][31][0])+(
          Cik[32][1][2]*Vpk[24][31][1]))));
        Vpk[25][26][0] = (.1862*Wpk[25][26][2]);
        Vpk[25][26][2] = -(.1862*Wpk[25][26][0]);
        Vpk[25][27][0] = (.43*((Cik[27][0][0]*Wpk[25][26][2])-(Cik[27][2][0]*
          Wpk[25][26][0])));
        Vpk[25][27][1] = (.43*((Cik[27][0][1]*Wpk[25][26][2])-(Cik[27][2][1]*
          Wpk[25][26][0])));
        Vpk[25][27][2] = (.43*((Cik[27][0][2]*Wpk[25][26][2])-(Cik[27][2][2]*
          Wpk[25][26][0])));
        Vpk[25][28][0] = ((Cik[28][2][0]*Vpk[25][27][2])+((Cik[28][0][0]*
          Vpk[25][27][0])+(Cik[28][1][0]*Vpk[25][27][1])));
        Vpk[25][28][1] = ((Cik[28][2][1]*Vpk[25][27][2])+((Cik[28][0][1]*
          Vpk[25][27][0])+(Cik[28][1][1]*Vpk[25][27][1])));
        Vpk[25][28][2] = ((Cik[28][2][2]*Vpk[25][27][2])+((Cik[28][0][2]*
          Vpk[25][27][0])+(Cik[28][1][2]*Vpk[25][27][1])));
        Vpk[25][29][0] = (((.051347*Wpk[25][29][2])-(.005539*Wpk[25][29][1]))+((
          Cik[29][2][0]*Vpk[25][28][2])+((Cik[29][0][0]*Vpk[25][28][0])+(
          Cik[29][1][0]*Vpk[25][28][1]))));
        Vpk[25][29][1] = (((.005539*Wpk[25][29][0])+(.035902*Wpk[25][29][2]))+((
          Cik[29][2][1]*Vpk[25][28][2])+((Cik[29][0][1]*Vpk[25][28][0])+(
          Cik[29][1][1]*Vpk[25][28][1]))));
        Vpk[25][29][2] = (((Cik[29][2][2]*Vpk[25][28][2])+((Cik[29][0][2]*
          Vpk[25][28][0])+(Cik[29][1][2]*Vpk[25][28][1])))-((.035902*
          Wpk[25][29][1])+(.051347*Wpk[25][29][0])));
        VWri[25][30][0] = (Vpk[25][29][0]+((.038*Wpk[25][29][2])-(.018078*
          Wpk[25][29][1])));
        VWri[25][30][1] = (Vpk[25][29][1]+((.018078*Wpk[25][29][0])+(.098032*
          Wpk[25][29][2])));
        VWri[25][30][2] = (Vpk[25][29][2]-((.038*Wpk[25][29][0])+(.098032*
          Wpk[25][29][1])));
        Vpk[25][30][0] = ((Cik[30][2][0]*VWri[25][30][2])+((Cik[30][0][0]*
          VWri[25][30][0])+(Cik[30][1][0]*VWri[25][30][1])));
        Vpk[25][30][1] = ((Cik[30][2][1]*VWri[25][30][2])+((Cik[30][0][1]*
          VWri[25][30][0])+(Cik[30][1][1]*VWri[25][30][1])));
        Vpk[25][30][2] = ((Cik[30][2][2]*VWri[25][30][2])+((Cik[30][0][2]*
          VWri[25][30][0])+(Cik[30][1][2]*VWri[25][30][1])));
        Vpk[25][31][0] = ((Cik[31][2][0]*Vpk[25][30][2])+((Cik[31][0][0]*
          Vpk[25][30][0])+(Cik[31][1][0]*Vpk[25][30][1])));
        Vpk[25][31][1] = ((Cik[31][2][1]*Vpk[25][30][2])+((Cik[31][0][1]*
          Vpk[25][30][0])+(Cik[31][1][1]*Vpk[25][30][1])));
        Vpk[25][31][2] = ((Cik[31][2][2]*Vpk[25][30][2])+((Cik[31][0][2]*
          Vpk[25][30][0])+(Cik[31][1][2]*Vpk[25][30][1])));
        Vpk[25][32][0] = (((Cik[32][2][0]*Vpk[25][31][2])+((Cik[32][0][0]*
          Vpk[25][31][0])+(Cik[32][1][0]*Vpk[25][31][1])))-((.005139*
          Wpk[25][32][1])+(.0185*Wpk[25][32][2])));
        Vpk[25][32][1] = (((.005139*Wpk[25][32][0])+(.026917*Wpk[25][32][2]))+((
          Cik[32][2][1]*Vpk[25][31][2])+((Cik[32][0][1]*Vpk[25][31][0])+(
          Cik[32][1][1]*Vpk[25][31][1]))));
        Vpk[25][32][2] = (((.0185*Wpk[25][32][0])-(.026917*Wpk[25][32][1]))+((
          Cik[32][2][2]*Vpk[25][31][2])+((Cik[32][0][2]*Vpk[25][31][0])+(
          Cik[32][1][2]*Vpk[25][31][1]))));
        Vpk[26][26][0] = (.1862*pin[26][2]);
        Vpk[26][26][2] = -(.1862*pin[26][0]);
        Vpk[26][27][0] = (.43*((Cik[27][0][0]*pin[26][2])-(Cik[27][2][0]*
          pin[26][0])));
        Vpk[26][27][1] = (.43*((Cik[27][0][1]*pin[26][2])-(Cik[27][2][1]*
          pin[26][0])));
        Vpk[26][27][2] = (.43*((Cik[27][0][2]*pin[26][2])-(Cik[27][2][2]*
          pin[26][0])));
        Vpk[26][28][0] = ((Cik[28][2][0]*Vpk[26][27][2])+((Cik[28][0][0]*
          Vpk[26][27][0])+(Cik[28][1][0]*Vpk[26][27][1])));
        Vpk[26][28][1] = ((Cik[28][2][1]*Vpk[26][27][2])+((Cik[28][0][1]*
          Vpk[26][27][0])+(Cik[28][1][1]*Vpk[26][27][1])));
        Vpk[26][28][2] = ((Cik[28][2][2]*Vpk[26][27][2])+((Cik[28][0][2]*
          Vpk[26][27][0])+(Cik[28][1][2]*Vpk[26][27][1])));
        Vpk[26][29][0] = (((.051347*Wpk[26][29][2])-(.005539*Wpk[26][29][1]))+((
          Cik[29][2][0]*Vpk[26][28][2])+((Cik[29][0][0]*Vpk[26][28][0])+(
          Cik[29][1][0]*Vpk[26][28][1]))));
        Vpk[26][29][1] = (((.005539*Wpk[26][29][0])+(.035902*Wpk[26][29][2]))+((
          Cik[29][2][1]*Vpk[26][28][2])+((Cik[29][0][1]*Vpk[26][28][0])+(
          Cik[29][1][1]*Vpk[26][28][1]))));
        Vpk[26][29][2] = (((Cik[29][2][2]*Vpk[26][28][2])+((Cik[29][0][2]*
          Vpk[26][28][0])+(Cik[29][1][2]*Vpk[26][28][1])))-((.035902*
          Wpk[26][29][1])+(.051347*Wpk[26][29][0])));
        VWri[26][30][0] = (Vpk[26][29][0]+((.038*Wpk[26][29][2])-(.018078*
          Wpk[26][29][1])));
        VWri[26][30][1] = (Vpk[26][29][1]+((.018078*Wpk[26][29][0])+(.098032*
          Wpk[26][29][2])));
        VWri[26][30][2] = (Vpk[26][29][2]-((.038*Wpk[26][29][0])+(.098032*
          Wpk[26][29][1])));
        Vpk[26][30][0] = ((Cik[30][2][0]*VWri[26][30][2])+((Cik[30][0][0]*
          VWri[26][30][0])+(Cik[30][1][0]*VWri[26][30][1])));
        Vpk[26][30][1] = ((Cik[30][2][1]*VWri[26][30][2])+((Cik[30][0][1]*
          VWri[26][30][0])+(Cik[30][1][1]*VWri[26][30][1])));
        Vpk[26][30][2] = ((Cik[30][2][2]*VWri[26][30][2])+((Cik[30][0][2]*
          VWri[26][30][0])+(Cik[30][1][2]*VWri[26][30][1])));
        Vpk[26][31][0] = ((Cik[31][2][0]*Vpk[26][30][2])+((Cik[31][0][0]*
          Vpk[26][30][0])+(Cik[31][1][0]*Vpk[26][30][1])));
        Vpk[26][31][1] = ((Cik[31][2][1]*Vpk[26][30][2])+((Cik[31][0][1]*
          Vpk[26][30][0])+(Cik[31][1][1]*Vpk[26][30][1])));
        Vpk[26][31][2] = ((Cik[31][2][2]*Vpk[26][30][2])+((Cik[31][0][2]*
          Vpk[26][30][0])+(Cik[31][1][2]*Vpk[26][30][1])));
        Vpk[26][32][0] = (((Cik[32][2][0]*Vpk[26][31][2])+((Cik[32][0][0]*
          Vpk[26][31][0])+(Cik[32][1][0]*Vpk[26][31][1])))-((.005139*
          Wpk[26][32][1])+(.0185*Wpk[26][32][2])));
        Vpk[26][32][1] = (((.005139*Wpk[26][32][0])+(.026917*Wpk[26][32][2]))+((
          Cik[32][2][1]*Vpk[26][31][2])+((Cik[32][0][1]*Vpk[26][31][0])+(
          Cik[32][1][1]*Vpk[26][31][1]))));
        Vpk[26][32][2] = (((.0185*Wpk[26][32][0])-(.026917*Wpk[26][32][1]))+((
          Cik[32][2][2]*Vpk[26][31][2])+((Cik[32][0][2]*Vpk[26][31][0])+(
          Cik[32][1][2]*Vpk[26][31][1]))));
        Vpk[27][29][0] = ((.051347*Wpk[27][29][2])-(.005539*Wpk[27][29][1]));
        Vpk[27][29][1] = ((.005539*Wpk[27][29][0])+(.035902*Wpk[27][29][2]));
        Vpk[27][29][2] = -((.035902*Wpk[27][29][1])+(.051347*Wpk[27][29][0]));
        VWri[27][30][0] = (Vpk[27][29][0]+((.038*Wpk[27][29][2])-(.018078*
          Wpk[27][29][1])));
        VWri[27][30][1] = (Vpk[27][29][1]+((.018078*Wpk[27][29][0])+(.098032*
          Wpk[27][29][2])));
        VWri[27][30][2] = (Vpk[27][29][2]-((.038*Wpk[27][29][0])+(.098032*
          Wpk[27][29][1])));
        Vpk[27][30][0] = ((Cik[30][2][0]*VWri[27][30][2])+((Cik[30][0][0]*
          VWri[27][30][0])+(Cik[30][1][0]*VWri[27][30][1])));
        Vpk[27][30][1] = ((Cik[30][2][1]*VWri[27][30][2])+((Cik[30][0][1]*
          VWri[27][30][0])+(Cik[30][1][1]*VWri[27][30][1])));
        Vpk[27][30][2] = ((Cik[30][2][2]*VWri[27][30][2])+((Cik[30][0][2]*
          VWri[27][30][0])+(Cik[30][1][2]*VWri[27][30][1])));
        Vpk[27][31][0] = ((Cik[31][2][0]*Vpk[27][30][2])+((Cik[31][0][0]*
          Vpk[27][30][0])+(Cik[31][1][0]*Vpk[27][30][1])));
        Vpk[27][31][1] = ((Cik[31][2][1]*Vpk[27][30][2])+((Cik[31][0][1]*
          Vpk[27][30][0])+(Cik[31][1][1]*Vpk[27][30][1])));
        Vpk[27][31][2] = ((Cik[31][2][2]*Vpk[27][30][2])+((Cik[31][0][2]*
          Vpk[27][30][0])+(Cik[31][1][2]*Vpk[27][30][1])));
        Vpk[27][32][0] = (((Cik[32][2][0]*Vpk[27][31][2])+((Cik[32][0][0]*
          Vpk[27][31][0])+(Cik[32][1][0]*Vpk[27][31][1])))-((.005139*
          Wpk[27][32][1])+(.0185*Wpk[27][32][2])));
        Vpk[27][32][1] = (((.005139*Wpk[27][32][0])+(.026917*Wpk[27][32][2]))+((
          Cik[32][2][1]*Vpk[27][31][2])+((Cik[32][0][1]*Vpk[27][31][0])+(
          Cik[32][1][1]*Vpk[27][31][1]))));
        Vpk[27][32][2] = (((.0185*Wpk[27][32][0])-(.026917*Wpk[27][32][1]))+((
          Cik[32][2][2]*Vpk[27][31][2])+((Cik[32][0][2]*Vpk[27][31][0])+(
          Cik[32][1][2]*Vpk[27][31][1]))));
        Vpk[28][29][0] = ((.051347*Wpk[28][29][2])-(.005539*Wpk[28][29][1]));
        Vpk[28][29][1] = ((.005539*Wpk[28][29][0])+(.035902*Wpk[28][29][2]));
        Vpk[28][29][2] = -((.035902*Wpk[28][29][1])+(.051347*Wpk[28][29][0]));
        VWri[28][30][0] = (Vpk[28][29][0]+((.038*Wpk[28][29][2])-(.018078*
          Wpk[28][29][1])));
        VWri[28][30][1] = (Vpk[28][29][1]+((.018078*Wpk[28][29][0])+(.098032*
          Wpk[28][29][2])));
        VWri[28][30][2] = (Vpk[28][29][2]-((.038*Wpk[28][29][0])+(.098032*
          Wpk[28][29][1])));
        Vpk[28][30][0] = ((Cik[30][2][0]*VWri[28][30][2])+((Cik[30][0][0]*
          VWri[28][30][0])+(Cik[30][1][0]*VWri[28][30][1])));
        Vpk[28][30][1] = ((Cik[30][2][1]*VWri[28][30][2])+((Cik[30][0][1]*
          VWri[28][30][0])+(Cik[30][1][1]*VWri[28][30][1])));
        Vpk[28][30][2] = ((Cik[30][2][2]*VWri[28][30][2])+((Cik[30][0][2]*
          VWri[28][30][0])+(Cik[30][1][2]*VWri[28][30][1])));
        Vpk[28][31][0] = ((Cik[31][2][0]*Vpk[28][30][2])+((Cik[31][0][0]*
          Vpk[28][30][0])+(Cik[31][1][0]*Vpk[28][30][1])));
        Vpk[28][31][1] = ((Cik[31][2][1]*Vpk[28][30][2])+((Cik[31][0][1]*
          Vpk[28][30][0])+(Cik[31][1][1]*Vpk[28][30][1])));
        Vpk[28][31][2] = ((Cik[31][2][2]*Vpk[28][30][2])+((Cik[31][0][2]*
          Vpk[28][30][0])+(Cik[31][1][2]*Vpk[28][30][1])));
        Vpk[28][32][0] = (((Cik[32][2][0]*Vpk[28][31][2])+((Cik[32][0][0]*
          Vpk[28][31][0])+(Cik[32][1][0]*Vpk[28][31][1])))-((.005139*
          Wpk[28][32][1])+(.0185*Wpk[28][32][2])));
        Vpk[28][32][1] = (((.005139*Wpk[28][32][0])+(.026917*Wpk[28][32][2]))+((
          Cik[32][2][1]*Vpk[28][31][2])+((Cik[32][0][1]*Vpk[28][31][0])+(
          Cik[32][1][1]*Vpk[28][31][1]))));
        Vpk[28][32][2] = (((.0185*Wpk[28][32][0])-(.026917*Wpk[28][32][1]))+((
          Cik[32][2][2]*Vpk[28][31][2])+((Cik[32][0][2]*Vpk[28][31][0])+(
          Cik[32][1][2]*Vpk[28][31][1]))));
        Vpk[29][29][0] = ((.051347*pin[29][2])-(.005539*pin[29][1]));
        Vpk[29][29][1] = ((.005539*pin[29][0])+(.035902*pin[29][2]));
        Vpk[29][29][2] = -((.035902*pin[29][1])+(.051347*pin[29][0]));
        VWri[29][30][0] = (Vpk[29][29][0]+((.038*pin[29][2])-(.018078*pin[29][1]
          )));
        VWri[29][30][1] = (Vpk[29][29][1]+((.018078*pin[29][0])+(.098032*
          pin[29][2])));
        VWri[29][30][2] = (Vpk[29][29][2]-((.038*pin[29][0])+(.098032*pin[29][1]
          )));
        Vpk[29][30][0] = ((Cik[30][2][0]*VWri[29][30][2])+((Cik[30][0][0]*
          VWri[29][30][0])+(Cik[30][1][0]*VWri[29][30][1])));
        Vpk[29][30][1] = ((Cik[30][2][1]*VWri[29][30][2])+((Cik[30][0][1]*
          VWri[29][30][0])+(Cik[30][1][1]*VWri[29][30][1])));
        Vpk[29][30][2] = ((Cik[30][2][2]*VWri[29][30][2])+((Cik[30][0][2]*
          VWri[29][30][0])+(Cik[30][1][2]*VWri[29][30][1])));
        Vpk[29][31][0] = ((Cik[31][2][0]*Vpk[29][30][2])+((Cik[31][0][0]*
          Vpk[29][30][0])+(Cik[31][1][0]*Vpk[29][30][1])));
        Vpk[29][31][1] = ((Cik[31][2][1]*Vpk[29][30][2])+((Cik[31][0][1]*
          Vpk[29][30][0])+(Cik[31][1][1]*Vpk[29][30][1])));
        Vpk[29][31][2] = ((Cik[31][2][2]*Vpk[29][30][2])+((Cik[31][0][2]*
          Vpk[29][30][0])+(Cik[31][1][2]*Vpk[29][30][1])));
        Vpk[29][32][0] = (((Cik[32][2][0]*Vpk[29][31][2])+((Cik[32][0][0]*
          Vpk[29][31][0])+(Cik[32][1][0]*Vpk[29][31][1])))-((.005139*
          Wpk[29][32][1])+(.0185*Wpk[29][32][2])));
        Vpk[29][32][1] = (((.005139*Wpk[29][32][0])+(.026917*Wpk[29][32][2]))+((
          Cik[32][2][1]*Vpk[29][31][2])+((Cik[32][0][1]*Vpk[29][31][0])+(
          Cik[32][1][1]*Vpk[29][31][1]))));
        Vpk[29][32][2] = (((.0185*Wpk[29][32][0])-(.026917*Wpk[29][32][1]))+((
          Cik[32][2][2]*Vpk[29][31][2])+((Cik[32][0][2]*Vpk[29][31][0])+(
          Cik[32][1][2]*Vpk[29][31][1]))));
        Vpk[30][32][0] = -((.005139*Wpk[30][32][1])+(.0185*Wpk[30][32][2]));
        Vpk[30][32][1] = ((.005139*Wpk[30][32][0])+(.026917*Wpk[30][32][2]));
        Vpk[30][32][2] = ((.0185*Wpk[30][32][0])-(.026917*Wpk[30][32][1]));
        Vpk[31][32][0] = -((.005139*Wpk[31][32][1])+(.0185*Wpk[31][32][2]));
        Vpk[31][32][1] = ((.005139*Wpk[31][32][0])+(.026917*Wpk[31][32][2]));
        Vpk[31][32][2] = ((.0185*Wpk[31][32][0])-(.026917*Wpk[31][32][1]));
        Vpk[32][32][0] = -((.005139*pin[32][1])+(.0185*pin[32][2]));
        Vpk[32][32][1] = ((.005139*pin[32][0])+(.026917*pin[32][2]));
        Vpk[32][32][2] = ((.0185*pin[32][0])-(.026917*pin[32][1]));
        vpkflg = 1;
    }
/*
 Used 0.11 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 3392 adds/subtracts/negates
                   4929 multiplies
                      0 divides
                   1775 assignments
*/
}

void sddoltau(void)
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

void sddoiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
        Otk[6][0] = ((Wik[6][2]*wk[6][1])-(Wik[6][1]*wk[6][2]));
        Otk[6][1] = ((Wik[6][0]*wk[6][2])-(Wik[6][2]*wk[6][0]));
        Otk[6][2] = ((Wik[6][1]*wk[6][0])-(Wik[6][0]*wk[6][1]));
        Otk[7][0] = (((Cik[7][2][0]*Otk[6][2])+((Cik[7][0][0]*Otk[6][0])+(
          Cik[7][1][0]*Otk[6][1])))+((Wik[7][2]*wk[7][1])-(Wik[7][1]*wk[7][2])))
          ;
        Otk[7][1] = (((Cik[7][2][1]*Otk[6][2])+((Cik[7][0][1]*Otk[6][0])+(
          Cik[7][1][1]*Otk[6][1])))+((Wik[7][0]*wk[7][2])-(Wik[7][2]*wk[7][0])))
          ;
        Otk[7][2] = (((Cik[7][2][2]*Otk[6][2])+((Cik[7][0][2]*Otk[6][0])+(
          Cik[7][1][2]*Otk[6][1])))+((Wik[7][1]*wk[7][0])-(Wik[7][0]*wk[7][1])))
          ;
        Otk[8][0] = (((Cik[8][2][0]*Otk[7][2])+((Cik[8][0][0]*Otk[7][0])+(
          Cik[8][1][0]*Otk[7][1])))+((Wik[8][2]*wk[8][1])-(Wik[8][1]*wk[8][2])))
          ;
        Otk[8][1] = (((Cik[8][2][1]*Otk[7][2])+((Cik[8][0][1]*Otk[7][0])+(
          Cik[8][1][1]*Otk[7][1])))+((Wik[8][0]*wk[8][2])-(Wik[8][2]*wk[8][0])))
          ;
        Otk[8][2] = (((Cik[8][2][2]*Otk[7][2])+((Cik[8][0][2]*Otk[7][0])+(
          Cik[8][1][2]*Otk[7][1])))+((Wik[8][1]*wk[8][0])-(Wik[8][0]*wk[8][1])))
          ;
        Otk[9][0] = ((Wik[9][2]*wk[9][1])-(Wik[9][1]*wk[9][2]));
        Otk[9][1] = ((Wik[9][0]*wk[9][2])-(Wik[9][2]*wk[9][0]));
        Otk[9][2] = ((Wik[9][1]*wk[9][0])-(Wik[9][0]*wk[9][1]));
        Otk[10][0] = (((Cik[10][2][0]*Otk[9][2])+((Cik[10][0][0]*Otk[9][0])+(
          Cik[10][1][0]*Otk[9][1])))+((Wik[10][2]*wk[10][1])-(Wik[10][1]*
          wk[10][2])));
        Otk[10][1] = (((Cik[10][2][1]*Otk[9][2])+((Cik[10][0][1]*Otk[9][0])+(
          Cik[10][1][1]*Otk[9][1])))+((Wik[10][0]*wk[10][2])-(Wik[10][2]*
          wk[10][0])));
        Otk[10][2] = (((Cik[10][2][2]*Otk[9][2])+((Cik[10][0][2]*Otk[9][0])+(
          Cik[10][1][2]*Otk[9][1])))+((Wik[10][1]*wk[10][0])-(Wik[10][0]*
          wk[10][1])));
        Otk[11][0] = (((Cik[11][2][0]*Otk[10][2])+((Cik[11][0][0]*Otk[10][0])+(
          Cik[11][1][0]*Otk[10][1])))+((Wik[11][2]*wk[11][1])-(Wik[11][1]*
          wk[11][2])));
        Otk[11][1] = (((Cik[11][2][1]*Otk[10][2])+((Cik[11][0][1]*Otk[10][0])+(
          Cik[11][1][1]*Otk[10][1])))+((Wik[11][0]*wk[11][2])-(Wik[11][2]*
          wk[11][0])));
        Otk[11][2] = (((Cik[11][2][2]*Otk[10][2])+((Cik[11][0][2]*Otk[10][0])+(
          Cik[11][1][2]*Otk[10][1])))+((Wik[11][1]*wk[11][0])-(Wik[11][0]*
          wk[11][1])));
        Otk[12][0] = (((Cik[12][2][0]*Otk[11][2])+((Cik[12][0][0]*Otk[11][0])+(
          Cik[12][1][0]*Otk[11][1])))+((Wik[12][2]*wk[12][1])-(Wik[12][1]*
          wk[12][2])));
        Otk[12][1] = (((Cik[12][2][1]*Otk[11][2])+((Cik[12][0][1]*Otk[11][0])+(
          Cik[12][1][1]*Otk[11][1])))+((Wik[12][0]*wk[12][2])-(Wik[12][2]*
          wk[12][0])));
        Otk[12][2] = (((Cik[12][2][2]*Otk[11][2])+((Cik[12][0][2]*Otk[11][0])+(
          Cik[12][1][2]*Otk[11][1])))+((Wik[12][1]*wk[12][0])-(Wik[12][0]*
          wk[12][1])));
        Otk[13][0] = (((Cik[13][2][0]*Otk[12][2])+((Cik[13][0][0]*Otk[12][0])+(
          Cik[13][1][0]*Otk[12][1])))+((Wik[13][2]*wk[13][1])-(Wik[13][1]*
          wk[13][2])));
        Otk[13][1] = (((Cik[13][2][1]*Otk[12][2])+((Cik[13][0][1]*Otk[12][0])+(
          Cik[13][1][1]*Otk[12][1])))+((Wik[13][0]*wk[13][2])-(Wik[13][2]*
          wk[13][0])));
        Otk[13][2] = (((Cik[13][2][2]*Otk[12][2])+((Cik[13][0][2]*Otk[12][0])+(
          Cik[13][1][2]*Otk[12][1])))+((Wik[13][1]*wk[13][0])-(Wik[13][0]*
          wk[13][1])));
        Otk[14][0] = (((Cik[14][2][0]*Otk[13][2])+((Cik[14][0][0]*Otk[13][0])+(
          Cik[14][1][0]*Otk[13][1])))+((Wik[14][2]*wk[14][1])-(Wik[14][1]*
          wk[14][2])));
        Otk[14][1] = (((Cik[14][2][1]*Otk[13][2])+((Cik[14][0][1]*Otk[13][0])+(
          Cik[14][1][1]*Otk[13][1])))+((Wik[14][0]*wk[14][2])-(Wik[14][2]*
          wk[14][0])));
        Otk[14][2] = (((Cik[14][2][2]*Otk[13][2])+((Cik[14][0][2]*Otk[13][0])+(
          Cik[14][1][2]*Otk[13][1])))+((Wik[14][1]*wk[14][0])-(Wik[14][0]*
          wk[14][1])));
        Otk[15][0] = (((Cik[15][2][0]*Otk[14][2])+((Cik[15][0][0]*Otk[14][0])+(
          Cik[15][1][0]*Otk[14][1])))+((Wik[15][2]*wk[15][1])-(Wik[15][1]*
          wk[15][2])));
        Otk[15][1] = (((Cik[15][2][1]*Otk[14][2])+((Cik[15][0][1]*Otk[14][0])+(
          Cik[15][1][1]*Otk[14][1])))+((Wik[15][0]*wk[15][2])-(Wik[15][2]*
          wk[15][0])));
        Otk[15][2] = (((Cik[15][2][2]*Otk[14][2])+((Cik[15][0][2]*Otk[14][0])+(
          Cik[15][1][2]*Otk[14][1])))+((Wik[15][1]*wk[15][0])-(Wik[15][0]*
          wk[15][1])));
        Otk[16][0] = (((Cik[16][2][0]*Otk[15][2])+((Cik[16][0][0]*Otk[15][0])+(
          Cik[16][1][0]*Otk[15][1])))+((Wik[16][2]*wk[16][1])-(Wik[16][1]*
          wk[16][2])));
        Otk[16][1] = (((Cik[16][2][1]*Otk[15][2])+((Cik[16][0][1]*Otk[15][0])+(
          Cik[16][1][1]*Otk[15][1])))+((Wik[16][0]*wk[16][2])-(Wik[16][2]*
          wk[16][0])));
        Otk[16][2] = (((Cik[16][2][2]*Otk[15][2])+((Cik[16][0][2]*Otk[15][0])+(
          Cik[16][1][2]*Otk[15][1])))+((Wik[16][1]*wk[16][0])-(Wik[16][0]*
          wk[16][1])));
        Otk[17][0] = (((Cik[17][2][0]*Otk[16][2])+((Cik[17][0][0]*Otk[16][0])+(
          Cik[17][1][0]*Otk[16][1])))+((Wik[17][2]*wk[17][1])-(Wik[17][1]*
          wk[17][2])));
        Otk[17][1] = (((Cik[17][2][1]*Otk[16][2])+((Cik[17][0][1]*Otk[16][0])+(
          Cik[17][1][1]*Otk[16][1])))+((Wik[17][0]*wk[17][2])-(Wik[17][2]*
          wk[17][0])));
        Otk[17][2] = (((Cik[17][2][2]*Otk[16][2])+((Cik[17][0][2]*Otk[16][0])+(
          Cik[17][1][2]*Otk[16][1])))+((Wik[17][1]*wk[17][0])-(Wik[17][0]*
          wk[17][1])));
        Otk[18][0] = (((Cik[18][2][0]*Otk[17][2])+((Cik[18][0][0]*Otk[17][0])+(
          Cik[18][1][0]*Otk[17][1])))+((Wik[18][2]*wk[18][1])-(Wik[18][1]*
          wk[18][2])));
        Otk[18][1] = (((Cik[18][2][1]*Otk[17][2])+((Cik[18][0][1]*Otk[17][0])+(
          Cik[18][1][1]*Otk[17][1])))+((Wik[18][0]*wk[18][2])-(Wik[18][2]*
          wk[18][0])));
        Otk[18][2] = (((Cik[18][2][2]*Otk[17][2])+((Cik[18][0][2]*Otk[17][0])+(
          Cik[18][1][2]*Otk[17][1])))+((Wik[18][1]*wk[18][0])-(Wik[18][0]*
          wk[18][1])));
        Otk[19][0] = (((Cik[19][2][0]*Otk[18][2])+((Cik[19][0][0]*Otk[18][0])+(
          Cik[19][1][0]*Otk[18][1])))+((Wik[19][2]*wk[19][1])-(Wik[19][1]*
          wk[19][2])));
        Otk[19][1] = (((Cik[19][2][1]*Otk[18][2])+((Cik[19][0][1]*Otk[18][0])+(
          Cik[19][1][1]*Otk[18][1])))+((Wik[19][0]*wk[19][2])-(Wik[19][2]*
          wk[19][0])));
        Otk[19][2] = (((Cik[19][2][2]*Otk[18][2])+((Cik[19][0][2]*Otk[18][0])+(
          Cik[19][1][2]*Otk[18][1])))+((Wik[19][1]*wk[19][0])-(Wik[19][0]*
          wk[19][1])));
        Otk[20][0] = (((Cik[20][2][0]*Otk[19][2])+((Cik[20][0][0]*Otk[19][0])+(
          Cik[20][1][0]*Otk[19][1])))+((Wik[20][2]*wk[20][1])-(Wik[20][1]*
          wk[20][2])));
        Otk[20][1] = (((Cik[20][2][1]*Otk[19][2])+((Cik[20][0][1]*Otk[19][0])+(
          Cik[20][1][1]*Otk[19][1])))+((Wik[20][0]*wk[20][2])-(Wik[20][2]*
          wk[20][0])));
        Otk[20][2] = (((Cik[20][2][2]*Otk[19][2])+((Cik[20][0][2]*Otk[19][0])+(
          Cik[20][1][2]*Otk[19][1])))+((Wik[20][1]*wk[20][0])-(Wik[20][0]*
          wk[20][1])));
        Otk[21][0] = ((Wik[21][2]*wk[21][1])-(Wik[21][1]*wk[21][2]));
        Otk[21][1] = ((Wik[21][0]*wk[21][2])-(Wik[21][2]*wk[21][0]));
        Otk[21][2] = ((Wik[21][1]*wk[21][0])-(Wik[21][0]*wk[21][1]));
        Otk[22][0] = (((Cik[22][2][0]*Otk[21][2])+((Cik[22][0][0]*Otk[21][0])+(
          Cik[22][1][0]*Otk[21][1])))+((Wik[22][2]*wk[22][1])-(Wik[22][1]*
          wk[22][2])));
        Otk[22][1] = (((Cik[22][2][1]*Otk[21][2])+((Cik[22][0][1]*Otk[21][0])+(
          Cik[22][1][1]*Otk[21][1])))+((Wik[22][0]*wk[22][2])-(Wik[22][2]*
          wk[22][0])));
        Otk[22][2] = (((Cik[22][2][2]*Otk[21][2])+((Cik[22][0][2]*Otk[21][0])+(
          Cik[22][1][2]*Otk[21][1])))+((Wik[22][1]*wk[22][0])-(Wik[22][0]*
          wk[22][1])));
        Otk[23][0] = (((Cik[23][2][0]*Otk[22][2])+((Cik[23][0][0]*Otk[22][0])+(
          Cik[23][1][0]*Otk[22][1])))+((Wik[23][2]*wk[23][1])-(Wik[23][1]*
          wk[23][2])));
        Otk[23][1] = (((Cik[23][2][1]*Otk[22][2])+((Cik[23][0][1]*Otk[22][0])+(
          Cik[23][1][1]*Otk[22][1])))+((Wik[23][0]*wk[23][2])-(Wik[23][2]*
          wk[23][0])));
        Otk[23][2] = (((Cik[23][2][2]*Otk[22][2])+((Cik[23][0][2]*Otk[22][0])+(
          Cik[23][1][2]*Otk[22][1])))+((Wik[23][1]*wk[23][0])-(Wik[23][0]*
          wk[23][1])));
        Otk[24][0] = (((Cik[24][2][0]*Otk[23][2])+((Cik[24][0][0]*Otk[23][0])+(
          Cik[24][1][0]*Otk[23][1])))+((Wik[24][2]*wk[24][1])-(Wik[24][1]*
          wk[24][2])));
        Otk[24][1] = (((Cik[24][2][1]*Otk[23][2])+((Cik[24][0][1]*Otk[23][0])+(
          Cik[24][1][1]*Otk[23][1])))+((Wik[24][0]*wk[24][2])-(Wik[24][2]*
          wk[24][0])));
        Otk[24][2] = (((Cik[24][2][2]*Otk[23][2])+((Cik[24][0][2]*Otk[23][0])+(
          Cik[24][1][2]*Otk[23][1])))+((Wik[24][1]*wk[24][0])-(Wik[24][0]*
          wk[24][1])));
        Otk[25][0] = (((Cik[25][2][0]*Otk[24][2])+((Cik[25][0][0]*Otk[24][0])+(
          Cik[25][1][0]*Otk[24][1])))+((Wik[25][2]*wk[25][1])-(Wik[25][1]*
          wk[25][2])));
        Otk[25][1] = (((Cik[25][2][1]*Otk[24][2])+((Cik[25][0][1]*Otk[24][0])+(
          Cik[25][1][1]*Otk[24][1])))+((Wik[25][0]*wk[25][2])-(Wik[25][2]*
          wk[25][0])));
        Otk[25][2] = (((Cik[25][2][2]*Otk[24][2])+((Cik[25][0][2]*Otk[24][0])+(
          Cik[25][1][2]*Otk[24][1])))+((Wik[25][1]*wk[25][0])-(Wik[25][0]*
          wk[25][1])));
        Otk[26][0] = (((Cik[26][2][0]*Otk[25][2])+((Cik[26][0][0]*Otk[25][0])+(
          Cik[26][1][0]*Otk[25][1])))+((Wik[26][2]*wk[26][1])-(Wik[26][1]*
          wk[26][2])));
        Otk[26][1] = (((Cik[26][2][1]*Otk[25][2])+((Cik[26][0][1]*Otk[25][0])+(
          Cik[26][1][1]*Otk[25][1])))+((Wik[26][0]*wk[26][2])-(Wik[26][2]*
          wk[26][0])));
        Otk[26][2] = (((Cik[26][2][2]*Otk[25][2])+((Cik[26][0][2]*Otk[25][0])+(
          Cik[26][1][2]*Otk[25][1])))+((Wik[26][1]*wk[26][0])-(Wik[26][0]*
          wk[26][1])));
        Otk[27][0] = (((Cik[27][2][0]*Otk[26][2])+((Cik[27][0][0]*Otk[26][0])+(
          Cik[27][1][0]*Otk[26][1])))+((Wik[27][2]*wk[27][1])-(Wik[27][1]*
          wk[27][2])));
        Otk[27][1] = (((Cik[27][2][1]*Otk[26][2])+((Cik[27][0][1]*Otk[26][0])+(
          Cik[27][1][1]*Otk[26][1])))+((Wik[27][0]*wk[27][2])-(Wik[27][2]*
          wk[27][0])));
        Otk[27][2] = (((Cik[27][2][2]*Otk[26][2])+((Cik[27][0][2]*Otk[26][0])+(
          Cik[27][1][2]*Otk[26][1])))+((Wik[27][1]*wk[27][0])-(Wik[27][0]*
          wk[27][1])));
        Otk[28][0] = (((Cik[28][2][0]*Otk[27][2])+((Cik[28][0][0]*Otk[27][0])+(
          Cik[28][1][0]*Otk[27][1])))+((Wik[28][2]*wk[28][1])-(Wik[28][1]*
          wk[28][2])));
        Otk[28][1] = (((Cik[28][2][1]*Otk[27][2])+((Cik[28][0][1]*Otk[27][0])+(
          Cik[28][1][1]*Otk[27][1])))+((Wik[28][0]*wk[28][2])-(Wik[28][2]*
          wk[28][0])));
        Otk[28][2] = (((Cik[28][2][2]*Otk[27][2])+((Cik[28][0][2]*Otk[27][0])+(
          Cik[28][1][2]*Otk[27][1])))+((Wik[28][1]*wk[28][0])-(Wik[28][0]*
          wk[28][1])));
        Otk[29][0] = (((Cik[29][2][0]*Otk[28][2])+((Cik[29][0][0]*Otk[28][0])+(
          Cik[29][1][0]*Otk[28][1])))+((Wik[29][2]*wk[29][1])-(Wik[29][1]*
          wk[29][2])));
        Otk[29][1] = (((Cik[29][2][1]*Otk[28][2])+((Cik[29][0][1]*Otk[28][0])+(
          Cik[29][1][1]*Otk[28][1])))+((Wik[29][0]*wk[29][2])-(Wik[29][2]*
          wk[29][0])));
        Otk[29][2] = (((Cik[29][2][2]*Otk[28][2])+((Cik[29][0][2]*Otk[28][0])+(
          Cik[29][1][2]*Otk[28][1])))+((Wik[29][1]*wk[29][0])-(Wik[29][0]*
          wk[29][1])));
        Otk[30][0] = (((Cik[30][2][0]*Otk[29][2])+((Cik[30][0][0]*Otk[29][0])+(
          Cik[30][1][0]*Otk[29][1])))+((Wik[30][2]*wk[30][1])-(Wik[30][1]*
          wk[30][2])));
        Otk[30][1] = (((Cik[30][2][1]*Otk[29][2])+((Cik[30][0][1]*Otk[29][0])+(
          Cik[30][1][1]*Otk[29][1])))+((Wik[30][0]*wk[30][2])-(Wik[30][2]*
          wk[30][0])));
        Otk[30][2] = (((Cik[30][2][2]*Otk[29][2])+((Cik[30][0][2]*Otk[29][0])+(
          Cik[30][1][2]*Otk[29][1])))+((Wik[30][1]*wk[30][0])-(Wik[30][0]*
          wk[30][1])));
        Otk[31][0] = (((Cik[31][2][0]*Otk[30][2])+((Cik[31][0][0]*Otk[30][0])+(
          Cik[31][1][0]*Otk[30][1])))+((Wik[31][2]*wk[31][1])-(Wik[31][1]*
          wk[31][2])));
        Otk[31][1] = (((Cik[31][2][1]*Otk[30][2])+((Cik[31][0][1]*Otk[30][0])+(
          Cik[31][1][1]*Otk[30][1])))+((Wik[31][0]*wk[31][2])-(Wik[31][2]*
          wk[31][0])));
        Otk[31][2] = (((Cik[31][2][2]*Otk[30][2])+((Cik[31][0][2]*Otk[30][0])+(
          Cik[31][1][2]*Otk[30][1])))+((Wik[31][1]*wk[31][0])-(Wik[31][0]*
          wk[31][1])));
        Otk[32][0] = (((Cik[32][2][0]*Otk[31][2])+((Cik[32][0][0]*Otk[31][0])+(
          Cik[32][1][0]*Otk[31][1])))+((Wik[32][2]*wk[32][1])-(Wik[32][1]*
          wk[32][2])));
        Otk[32][1] = (((Cik[32][2][1]*Otk[31][2])+((Cik[32][0][1]*Otk[31][0])+(
          Cik[32][1][1]*Otk[31][1])))+((Wik[32][0]*wk[32][2])-(Wik[32][2]*
          wk[32][0])));
        Otk[32][2] = (((Cik[32][2][2]*Otk[31][2])+((Cik[32][0][2]*Otk[31][0])+(
          Cik[32][1][2]*Otk[31][1])))+((Wik[32][1]*wk[32][0])-(Wik[32][0]*
          wk[32][1])));
/*
Compute Atk (inertial linear acceleration)
*/
        AiOiWi[6][0] = (.127*(u[3]*u[4]));
        AiOiWi[6][1] = -(.127*((u[3]*u[3])+(u[5]*u[5])));
        AiOiWi[6][2] = (.127*(u[4]*u[5]));
        Atk[6][0] = ((AiOiWi[6][2]*Cik[6][2][0])+((AiOiWi[6][0]*Cik[6][0][0])+(
          AiOiWi[6][1]*Cik[6][1][0])));
        Atk[6][1] = ((AiOiWi[6][2]*Cik[6][2][1])+((AiOiWi[6][0]*Cik[6][0][1])+(
          AiOiWi[6][1]*Cik[6][1][1])));
        Atk[6][2] = ((AiOiWi[6][2]*Cik[6][2][2])+((AiOiWi[6][0]*Cik[6][0][2])+(
          AiOiWi[6][1]*Cik[6][1][2])));
        Atk[7][0] = ((Atk[6][2]*Cik[7][2][0])+((Atk[6][0]*Cik[7][0][0])+(
          Atk[6][1]*Cik[7][1][0])));
        Atk[7][1] = ((Atk[6][2]*Cik[7][2][1])+((Atk[6][0]*Cik[7][0][1])+(
          Atk[6][1]*Cik[7][1][1])));
        Atk[7][2] = ((Atk[6][2]*Cik[7][2][2])+((Atk[6][0]*Cik[7][0][2])+(
          Atk[6][1]*Cik[7][1][2])));
        Atk[8][0] = ((.3202*((wk[8][0]*wk[8][1])-Otk[8][2]))+((Atk[7][2]*
          Cik[8][2][0])+((Atk[7][0]*Cik[8][0][0])+(Atk[7][1]*Cik[8][1][0]))));
        Atk[8][1] = (((Atk[7][2]*Cik[8][2][1])+((Atk[7][0]*Cik[8][0][1])+(
          Atk[7][1]*Cik[8][1][1])))-(.3202*((wk[8][0]*wk[8][0])+(wk[8][2]*
          wk[8][2]))));
        Atk[8][2] = ((.3202*(Otk[8][0]+(wk[8][1]*wk[8][2])))+((Atk[7][2]*
          Cik[8][2][2])+((Atk[7][0]*Cik[8][0][2])+(Atk[7][1]*Cik[8][1][2]))));
        AiOiWi[9][0] = ((.0935*(u[3]*u[5]))-(.07*(u[3]*u[4])));
        AiOiWi[9][1] = ((.07*(u[3]*u[3]))+(u[5]*Wirk[9][0]));
        AiOiWi[9][2] = -((.0935*(u[3]*u[3]))+(u[4]*Wirk[9][0]));
        Atk[9][0] = ((AiOiWi[9][2]*Cik[9][2][0])+((AiOiWi[9][0]*Cik[9][0][0])+(
          AiOiWi[9][1]*Cik[9][1][0])));
        Atk[9][1] = ((AiOiWi[9][2]*Cik[9][2][1])+((AiOiWi[9][0]*Cik[9][0][1])+(
          AiOiWi[9][1]*Cik[9][1][1])));
        Atk[9][2] = ((AiOiWi[9][2]*Cik[9][2][2])+((AiOiWi[9][0]*Cik[9][0][2])+(
          AiOiWi[9][1]*Cik[9][1][2])));
        Atk[10][0] = ((Atk[9][2]*Cik[10][2][0])+((Atk[9][0]*Cik[10][0][0])+(
          Atk[9][1]*Cik[10][1][0])));
        Atk[10][1] = ((Atk[9][2]*Cik[10][2][1])+((Atk[9][0]*Cik[10][0][1])+(
          Atk[9][1]*Cik[10][1][1])));
        Atk[10][2] = ((Atk[9][2]*Cik[10][2][2])+((Atk[9][0]*Cik[10][0][2])+(
          Atk[9][1]*Cik[10][1][2])));
        Atk[11][0] = (((.1715*Otk[11][2])+((.002*(wk[11][2]*wk[11][2]))+(
          wk[11][1]*Wkrpk[11][2])))+((Atk[10][2]*Cik[11][2][0])+((Atk[10][0]*
          Cik[11][0][0])+(Atk[10][1]*Cik[11][1][0]))));
        Atk[11][1] = (((Atk[10][2]*Cik[11][2][1])+((Atk[10][0]*Cik[11][0][1])+(
          Atk[10][1]*Cik[11][1][1])))+(((.1715*(wk[11][2]*wk[11][2]))-(wk[11][0]
          *Wkrpk[11][2]))-(.002*Otk[11][2])));
        Atk[11][2] = (((Atk[10][2]*Cik[11][2][2])+((Atk[10][0]*Cik[11][0][2])+(
          Atk[10][1]*Cik[11][1][2])))+(((.002*Otk[11][1])-(.1715*Otk[11][0]))-((
          .002*(wk[11][0]*wk[11][2]))+(.1715*(wk[11][1]*wk[11][2])))));
        AiOiWi[12][0] = (Atk[11][0]+((.2294*Otk[11][2])+((Wirk[12][2]*wk[11][1])
          -(.0033*(wk[11][2]*wk[11][2])))));
        AiOiWi[12][1] = (Atk[11][1]+((.0033*Otk[11][2])+((.2294*(wk[11][2]*
          wk[11][2]))-(Wirk[12][2]*wk[11][0]))));
        AiOiWi[12][2] = (Atk[11][2]+(((.0033*(wk[11][0]*wk[11][2]))-(.2294*(
          wk[11][1]*wk[11][2])))-((.0033*Otk[11][1])+(.2294*Otk[11][0]))));
        Atk[12][0] = ((AiOiWi[12][2]*Cik[12][2][0])+((AiOiWi[12][0]*
          Cik[12][0][0])+(AiOiWi[12][1]*Cik[12][1][0])));
        Atk[12][1] = ((AiOiWi[12][2]*Cik[12][2][1])+((AiOiWi[12][0]*
          Cik[12][0][1])+(AiOiWi[12][1]*Cik[12][1][1])));
        Atk[12][2] = ((AiOiWi[12][2]*Cik[12][2][2])+((AiOiWi[12][0]*
          Cik[12][0][2])+(AiOiWi[12][1]*Cik[12][1][2])));
        Atk[13][0] = ((Atk[12][2]*Cik[13][2][0])+((Atk[12][0]*Cik[13][0][0])+(
          Atk[12][1]*Cik[13][1][0])));
        Atk[13][1] = ((Atk[12][2]*Cik[13][2][1])+((Atk[12][0]*Cik[13][0][1])+(
          Atk[12][1]*Cik[13][1][1])));
        Atk[13][2] = ((Atk[12][2]*Cik[13][2][2])+((Atk[12][0]*Cik[13][0][2])+(
          Atk[12][1]*Cik[13][1][2])));
        Atk[14][0] = ((.1862*(Otk[14][2]-(wk[14][0]*wk[14][1])))+((Atk[13][2]*
          Cik[14][2][0])+((Atk[13][0]*Cik[14][0][0])+(Atk[13][1]*Cik[14][1][0]))
          ));
        Atk[14][1] = ((.1862*((wk[14][0]*wk[14][0])+(wk[14][2]*wk[14][2])))+((
          Atk[13][2]*Cik[14][2][1])+((Atk[13][0]*Cik[14][0][1])+(Atk[13][1]*
          Cik[14][1][1]))));
        Atk[14][2] = (((Atk[13][2]*Cik[14][2][2])+((Atk[13][0]*Cik[14][0][2])+(
          Atk[13][1]*Cik[14][1][2])))-(.1862*(Otk[14][0]+(wk[14][1]*wk[14][2])))
          );
        AiOiWi[15][0] = (Atk[14][0]+(.2438*(Otk[14][2]-(wk[14][0]*wk[14][1]))));
        AiOiWi[15][1] = (Atk[14][1]+(.2438*((wk[14][0]*wk[14][0])+(wk[14][2]*
          wk[14][2]))));
        AiOiWi[15][2] = (Atk[14][2]-(.2438*(Otk[14][0]+(wk[14][1]*wk[14][2]))));
        Atk[15][0] = ((AiOiWi[15][2]*Cik[15][2][0])+((AiOiWi[15][0]*
          Cik[15][0][0])+(AiOiWi[15][1]*Cik[15][1][0])));
        Atk[15][1] = ((AiOiWi[15][2]*Cik[15][2][1])+((AiOiWi[15][0]*
          Cik[15][0][1])+(AiOiWi[15][1]*Cik[15][1][1])));
        Atk[15][2] = ((AiOiWi[15][2]*Cik[15][2][2])+((AiOiWi[15][0]*
          Cik[15][0][2])+(AiOiWi[15][1]*Cik[15][1][2])));
        Atk[16][0] = ((Atk[15][2]*Cik[16][2][0])+((Atk[15][0]*Cik[16][0][0])+(
          Atk[15][1]*Cik[16][1][0])));
        Atk[16][1] = ((Atk[15][2]*Cik[16][2][1])+((Atk[15][0]*Cik[16][0][1])+(
          Atk[15][1]*Cik[16][1][1])));
        Atk[16][2] = ((Atk[15][2]*Cik[16][2][2])+((Atk[15][0]*Cik[16][0][2])+(
          Atk[15][1]*Cik[16][1][2])));
        Atk[17][0] = (((Atk[16][2]*Cik[17][2][0])+((Atk[16][0]*Cik[17][0][0])+(
          Atk[16][1]*Cik[17][1][0])))+(((.005539*Otk[17][1])+(.051347*Otk[17][2]
          ))+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*Wkrpk[17][1]))));
        Atk[17][1] = (((Atk[16][2]*Cik[17][2][1])+((Atk[16][0]*Cik[17][0][1])+(
          Atk[16][1]*Cik[17][1][1])))+(((.035902*Otk[17][2])-(.005539*Otk[17][0]
          ))+((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
        Atk[17][2] = (((Atk[16][2]*Cik[17][2][2])+((Atk[16][0]*Cik[17][0][2])+(
          Atk[16][1]*Cik[17][1][2])))+(((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*
          Wkrpk[17][0]))-((.035902*Otk[17][1])+(.051347*Otk[17][0]))));
        AiOiWi[18][0] = (Atk[17][0]+(((.018078*Otk[17][1])+(.038*Otk[17][2]))+((
          Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
        AiOiWi[18][1] = (Atk[17][1]+(((.098032*Otk[17][2])-(.018078*Otk[17][0]))
          +((Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
        AiOiWi[18][2] = (Atk[17][2]+(((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*
          wk[17][1]))-((.038*Otk[17][0])+(.098032*Otk[17][1]))));
        Atk[18][0] = ((AiOiWi[18][2]*Cik[18][2][0])+((AiOiWi[18][0]*
          Cik[18][0][0])+(AiOiWi[18][1]*Cik[18][1][0])));
        Atk[18][1] = ((AiOiWi[18][2]*Cik[18][2][1])+((AiOiWi[18][0]*
          Cik[18][0][1])+(AiOiWi[18][1]*Cik[18][1][1])));
        Atk[18][2] = ((AiOiWi[18][2]*Cik[18][2][2])+((AiOiWi[18][0]*
          Cik[18][0][2])+(AiOiWi[18][1]*Cik[18][1][2])));
        Atk[19][0] = ((Atk[18][2]*Cik[19][2][0])+((Atk[18][0]*Cik[19][0][0])+(
          Atk[18][1]*Cik[19][1][0])));
        Atk[19][1] = ((Atk[18][2]*Cik[19][2][1])+((Atk[18][0]*Cik[19][0][1])+(
          Atk[18][1]*Cik[19][1][1])));
        Atk[19][2] = ((Atk[18][2]*Cik[19][2][2])+((Atk[18][0]*Cik[19][0][2])+(
          Atk[18][1]*Cik[19][1][2])));
        Atk[20][0] = (((Atk[19][2]*Cik[20][2][0])+((Atk[19][0]*Cik[20][0][0])+(
          Atk[19][1]*Cik[20][1][0])))+(((.005139*Otk[20][1])-(.0185*Otk[20][2]))
          +((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
        Atk[20][1] = (((Atk[19][2]*Cik[20][2][1])+((Atk[19][0]*Cik[20][0][1])+(
          Atk[19][1]*Cik[20][1][1])))+(((.026917*Otk[20][2])-(.005139*Otk[20][0]
          ))+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*Wkrpk[20][2]))));
        Atk[20][2] = (((Atk[19][2]*Cik[20][2][2])+((Atk[19][0]*Cik[20][0][2])+(
          Atk[19][1]*Cik[20][1][2])))+(((.0185*Otk[20][0])-(.026917*Otk[20][1]))
          +((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*Wkrpk[20][0]))));
        AiOiWi[21][0] = -((.07*(u[3]*u[4]))+(.0935*(u[3]*u[5])));
        AiOiWi[21][1] = ((.07*(u[3]*u[3]))+(u[5]*Wirk[21][0]));
        AiOiWi[21][2] = ((.0935*(u[3]*u[3]))-(u[4]*Wirk[21][0]));
        Atk[21][0] = ((AiOiWi[21][2]*Cik[21][2][0])+((AiOiWi[21][0]*
          Cik[21][0][0])+(AiOiWi[21][1]*Cik[21][1][0])));
        Atk[21][1] = ((AiOiWi[21][2]*Cik[21][2][1])+((AiOiWi[21][0]*
          Cik[21][0][1])+(AiOiWi[21][1]*Cik[21][1][1])));
        Atk[21][2] = ((AiOiWi[21][2]*Cik[21][2][2])+((AiOiWi[21][0]*
          Cik[21][0][2])+(AiOiWi[21][1]*Cik[21][1][2])));
        Atk[22][0] = ((Atk[21][2]*Cik[22][2][0])+((Atk[21][0]*Cik[22][0][0])+(
          Atk[21][1]*Cik[22][1][0])));
        Atk[22][1] = ((Atk[21][2]*Cik[22][2][1])+((Atk[21][0]*Cik[22][0][1])+(
          Atk[21][1]*Cik[22][1][1])));
        Atk[22][2] = ((Atk[21][2]*Cik[22][2][2])+((Atk[21][0]*Cik[22][0][2])+(
          Atk[21][1]*Cik[22][1][2])));
        Atk[23][0] = (((.1715*Otk[23][2])+((.002*(wk[23][2]*wk[23][2]))+(
          wk[23][1]*Wkrpk[23][2])))+((Atk[22][2]*Cik[23][2][0])+((Atk[22][0]*
          Cik[23][0][0])+(Atk[22][1]*Cik[23][1][0]))));
        Atk[23][1] = (((Atk[22][2]*Cik[23][2][1])+((Atk[22][0]*Cik[23][0][1])+(
          Atk[22][1]*Cik[23][1][1])))+(((.1715*(wk[23][2]*wk[23][2]))-(wk[23][0]
          *Wkrpk[23][2]))-(.002*Otk[23][2])));
        Atk[23][2] = (((Atk[22][2]*Cik[23][2][2])+((Atk[22][0]*Cik[23][0][2])+(
          Atk[22][1]*Cik[23][1][2])))+(((.002*Otk[23][1])-(.1715*Otk[23][0]))-((
          .002*(wk[23][0]*wk[23][2]))+(.1715*(wk[23][1]*wk[23][2])))));
        AiOiWi[24][0] = (Atk[23][0]+((.2294*Otk[23][2])+((Wirk[24][2]*wk[23][1])
          -(.0033*(wk[23][2]*wk[23][2])))));
        AiOiWi[24][1] = (Atk[23][1]+((.0033*Otk[23][2])+((.2294*(wk[23][2]*
          wk[23][2]))-(Wirk[24][2]*wk[23][0]))));
        AiOiWi[24][2] = (Atk[23][2]+(((.0033*(wk[23][0]*wk[23][2]))-(.2294*(
          wk[23][1]*wk[23][2])))-((.0033*Otk[23][1])+(.2294*Otk[23][0]))));
        Atk[24][0] = ((AiOiWi[24][2]*Cik[24][2][0])+((AiOiWi[24][0]*
          Cik[24][0][0])+(AiOiWi[24][1]*Cik[24][1][0])));
        Atk[24][1] = ((AiOiWi[24][2]*Cik[24][2][1])+((AiOiWi[24][0]*
          Cik[24][0][1])+(AiOiWi[24][1]*Cik[24][1][1])));
        Atk[24][2] = ((AiOiWi[24][2]*Cik[24][2][2])+((AiOiWi[24][0]*
          Cik[24][0][2])+(AiOiWi[24][1]*Cik[24][1][2])));
        Atk[25][0] = ((Atk[24][2]*Cik[25][2][0])+((Atk[24][0]*Cik[25][0][0])+(
          Atk[24][1]*Cik[25][1][0])));
        Atk[25][1] = ((Atk[24][2]*Cik[25][2][1])+((Atk[24][0]*Cik[25][0][1])+(
          Atk[24][1]*Cik[25][1][1])));
        Atk[25][2] = ((Atk[24][2]*Cik[25][2][2])+((Atk[24][0]*Cik[25][0][2])+(
          Atk[24][1]*Cik[25][1][2])));
        Atk[26][0] = ((.1862*(Otk[26][2]-(wk[26][0]*wk[26][1])))+((Atk[25][2]*
          Cik[26][2][0])+((Atk[25][0]*Cik[26][0][0])+(Atk[25][1]*Cik[26][1][0]))
          ));
        Atk[26][1] = ((.1862*((wk[26][0]*wk[26][0])+(wk[26][2]*wk[26][2])))+((
          Atk[25][2]*Cik[26][2][1])+((Atk[25][0]*Cik[26][0][1])+(Atk[25][1]*
          Cik[26][1][1]))));
        Atk[26][2] = (((Atk[25][2]*Cik[26][2][2])+((Atk[25][0]*Cik[26][0][2])+(
          Atk[25][1]*Cik[26][1][2])))-(.1862*(Otk[26][0]+(wk[26][1]*wk[26][2])))
          );
        AiOiWi[27][0] = (Atk[26][0]+(.2438*(Otk[26][2]-(wk[26][0]*wk[26][1]))));
        AiOiWi[27][1] = (Atk[26][1]+(.2438*((wk[26][0]*wk[26][0])+(wk[26][2]*
          wk[26][2]))));
        AiOiWi[27][2] = (Atk[26][2]-(.2438*(Otk[26][0]+(wk[26][1]*wk[26][2]))));
        Atk[27][0] = ((AiOiWi[27][2]*Cik[27][2][0])+((AiOiWi[27][0]*
          Cik[27][0][0])+(AiOiWi[27][1]*Cik[27][1][0])));
        Atk[27][1] = ((AiOiWi[27][2]*Cik[27][2][1])+((AiOiWi[27][0]*
          Cik[27][0][1])+(AiOiWi[27][1]*Cik[27][1][1])));
        Atk[27][2] = ((AiOiWi[27][2]*Cik[27][2][2])+((AiOiWi[27][0]*
          Cik[27][0][2])+(AiOiWi[27][1]*Cik[27][1][2])));
        Atk[28][0] = ((Atk[27][2]*Cik[28][2][0])+((Atk[27][0]*Cik[28][0][0])+(
          Atk[27][1]*Cik[28][1][0])));
        Atk[28][1] = ((Atk[27][2]*Cik[28][2][1])+((Atk[27][0]*Cik[28][0][1])+(
          Atk[27][1]*Cik[28][1][1])));
        Atk[28][2] = ((Atk[27][2]*Cik[28][2][2])+((Atk[27][0]*Cik[28][0][2])+(
          Atk[27][1]*Cik[28][1][2])));
        Atk[29][0] = (((Atk[28][2]*Cik[29][2][0])+((Atk[28][0]*Cik[29][0][0])+(
          Atk[28][1]*Cik[29][1][0])))+(((.051347*Otk[29][2])-(.005539*Otk[29][1]
          ))+((wk[29][1]*Wkrpk[29][2])-(wk[29][2]*Wkrpk[29][1]))));
        Atk[29][1] = (((Atk[28][2]*Cik[29][2][1])+((Atk[28][0]*Cik[29][0][1])+(
          Atk[28][1]*Cik[29][1][1])))+(((.005539*Otk[29][0])+(.035902*Otk[29][2]
          ))+((wk[29][2]*Wkrpk[29][0])-(wk[29][0]*Wkrpk[29][2]))));
        Atk[29][2] = (((Atk[28][2]*Cik[29][2][2])+((Atk[28][0]*Cik[29][0][2])+(
          Atk[28][1]*Cik[29][1][2])))+(((wk[29][0]*Wkrpk[29][1])-(wk[29][1]*
          Wkrpk[29][0]))-((.035902*Otk[29][1])+(.051347*Otk[29][0]))));
        AiOiWi[30][0] = (Atk[29][0]+(((.038*Otk[29][2])-(.018078*Otk[29][1]))+((
          Wirk[30][2]*wk[29][1])-(Wirk[30][1]*wk[29][2]))));
        AiOiWi[30][1] = (Atk[29][1]+(((.018078*Otk[29][0])+(.098032*Otk[29][2]))
          +((Wirk[30][0]*wk[29][2])-(Wirk[30][2]*wk[29][0]))));
        AiOiWi[30][2] = (Atk[29][2]+(((Wirk[30][1]*wk[29][0])-(Wirk[30][0]*
          wk[29][1]))-((.038*Otk[29][0])+(.098032*Otk[29][1]))));
        Atk[30][0] = ((AiOiWi[30][2]*Cik[30][2][0])+((AiOiWi[30][0]*
          Cik[30][0][0])+(AiOiWi[30][1]*Cik[30][1][0])));
        Atk[30][1] = ((AiOiWi[30][2]*Cik[30][2][1])+((AiOiWi[30][0]*
          Cik[30][0][1])+(AiOiWi[30][1]*Cik[30][1][1])));
        Atk[30][2] = ((AiOiWi[30][2]*Cik[30][2][2])+((AiOiWi[30][0]*
          Cik[30][0][2])+(AiOiWi[30][1]*Cik[30][1][2])));
        Atk[31][0] = ((Atk[30][2]*Cik[31][2][0])+((Atk[30][0]*Cik[31][0][0])+(
          Atk[30][1]*Cik[31][1][0])));
        Atk[31][1] = ((Atk[30][2]*Cik[31][2][1])+((Atk[30][0]*Cik[31][0][1])+(
          Atk[30][1]*Cik[31][1][1])));
        Atk[31][2] = ((Atk[30][2]*Cik[31][2][2])+((Atk[30][0]*Cik[31][0][2])+(
          Atk[30][1]*Cik[31][1][2])));
        Atk[32][0] = (((Atk[31][2]*Cik[32][2][0])+((Atk[31][0]*Cik[32][0][0])+(
          Atk[31][1]*Cik[32][1][0])))+(((wk[32][1]*Wkrpk[32][2])-(wk[32][2]*
          Wkrpk[32][1]))-((.005139*Otk[32][1])+(.0185*Otk[32][2]))));
        Atk[32][1] = (((Atk[31][2]*Cik[32][2][1])+((Atk[31][0]*Cik[32][0][1])+(
          Atk[31][1]*Cik[32][1][1])))+(((.005139*Otk[32][0])+(.026917*Otk[32][2]
          ))+((wk[32][2]*Wkrpk[32][0])-(wk[32][0]*Wkrpk[32][2]))));
        Atk[32][2] = (((Atk[31][2]*Cik[32][2][2])+((Atk[31][0]*Cik[32][0][2])+(
          Atk[31][1]*Cik[32][1][2])))+(((.0185*Otk[32][0])-(.026917*Otk[32][1]))
          +((wk[32][0]*Wkrpk[32][1])-(wk[32][1]*Wkrpk[32][0]))));
        inerflg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  611 adds/subtracts/negates
                    811 multiplies
                      0 divides
                    189 assignments
*/
}

void sddofs0(void)
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
        Fstar[5][0] = -(ufk[0][0]+(11.15*gk[3][0]));
        Fstar[5][1] = -(ufk[0][1]+(11.15*gk[3][1]));
        Fstar[5][2] = -(ufk[0][2]+(11.15*gk[3][2]));
        Fstar[8][0] = ((32.413*(Atk[8][0]-gk[8][0]))-ufk[1][0]);
        Fstar[8][1] = ((32.413*(Atk[8][1]-gk[8][1]))-ufk[1][1]);
        Fstar[8][2] = ((32.413*(Atk[8][2]-gk[8][2]))-ufk[1][2]);
        Fstar[11][0] = ((8.806*(Atk[11][0]-gk[11][0]))-ufk[2][0]);
        Fstar[11][1] = ((8.806*(Atk[11][1]-gk[11][1]))-ufk[2][1]);
        Fstar[11][2] = ((8.806*(Atk[11][2]-gk[11][2]))-ufk[2][2]);
        Fstar[14][0] = ((3.51*(Atk[14][0]-gk[14][0]))-ufk[3][0]);
        Fstar[14][1] = ((3.51*(Atk[14][1]-gk[14][1]))-ufk[3][1]);
        Fstar[14][2] = ((3.51*(Atk[14][2]-gk[14][2]))-ufk[3][2]);
        Fstar[17][0] = ((1.2*(Atk[17][0]-gk[17][0]))-ufk[4][0]);
        Fstar[17][1] = ((1.2*(Atk[17][1]-gk[17][1]))-ufk[4][1]);
        Fstar[17][2] = ((1.2*(Atk[17][2]-gk[17][2]))-ufk[4][2]);
        Fstar[20][0] = ((.205126*(Atk[20][0]-gk[20][0]))-ufk[5][0]);
        Fstar[20][1] = ((.205126*(Atk[20][1]-gk[20][1]))-ufk[5][1]);
        Fstar[20][2] = ((.205126*(Atk[20][2]-gk[20][2]))-ufk[5][2]);
        Fstar[23][0] = ((8.806*(Atk[23][0]-gk[23][0]))-ufk[6][0]);
        Fstar[23][1] = ((8.806*(Atk[23][1]-gk[23][1]))-ufk[6][1]);
        Fstar[23][2] = ((8.806*(Atk[23][2]-gk[23][2]))-ufk[6][2]);
        Fstar[26][0] = ((3.51*(Atk[26][0]-gk[26][0]))-ufk[7][0]);
        Fstar[26][1] = ((3.51*(Atk[26][1]-gk[26][1]))-ufk[7][1]);
        Fstar[26][2] = ((3.51*(Atk[26][2]-gk[26][2]))-ufk[7][2]);
        Fstar[29][0] = ((1.2*(Atk[29][0]-gk[29][0]))-ufk[8][0]);
        Fstar[29][1] = ((1.2*(Atk[29][1]-gk[29][1]))-ufk[8][1]);
        Fstar[29][2] = ((1.2*(Atk[29][2]-gk[29][2]))-ufk[8][2]);
        Fstar[32][0] = ((.205126*(Atk[32][0]-gk[32][0]))-ufk[9][0]);
        Fstar[32][1] = ((.205126*(Atk[32][1]-gk[32][1]))-ufk[9][1]);
        Fstar[32][2] = ((.205126*(Atk[32][2]-gk[32][2]))-ufk[9][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = (WkIkWk[5][0]-utk[0][0]);
        Tstar[5][1] = (WkIkWk[5][1]-utk[0][1]);
        Tstar[5][2] = (WkIkWk[5][2]-utk[0][2]);
        Tstar[8][0] = ((WkIkWk[8][0]+(1.396*Otk[8][0]))-utk[1][0]);
        Tstar[8][1] = ((WkIkWk[8][1]+(.7153*Otk[8][1]))-utk[1][1]);
        Tstar[8][2] = ((WkIkWk[8][2]+(1.3552*Otk[8][2]))-utk[1][2]);
        Tstar[11][0] = ((WkIkWk[11][0]+(.1268*Otk[11][0]))-utk[2][0]);
        Tstar[11][1] = ((WkIkWk[11][1]+(.0332*Otk[11][1]))-utk[2][1]);
        Tstar[11][2] = ((WkIkWk[11][2]+(.1337*Otk[11][2]))-utk[2][2]);
        Tstar[14][0] = ((WkIkWk[14][0]+(.0477*Otk[14][0]))-utk[3][0]);
        Tstar[14][1] = ((WkIkWk[14][1]+(.0048*Otk[14][1]))-utk[3][1]);
        Tstar[14][2] = ((WkIkWk[14][2]+(.0484*Otk[14][2]))-utk[3][2]);
        Tstar[17][0] = ((WkIkWk[17][0]+(.001361*Otk[17][0]))-utk[4][0]);
        Tstar[17][1] = ((WkIkWk[17][1]+(.003709*Otk[17][1]))-utk[4][1]);
        Tstar[17][2] = ((WkIkWk[17][2]+(.003916*Otk[17][2]))-utk[4][2]);
        Tstar[20][0] = ((WkIkWk[20][0]+(.000117*Otk[20][0]))-utk[5][0]);
        Tstar[20][1] = ((WkIkWk[20][1]+(.000179*Otk[20][1]))-utk[5][1]);
        Tstar[20][2] = ((WkIkWk[20][2]+(.000119*Otk[20][2]))-utk[5][2]);
        Tstar[23][0] = ((WkIkWk[23][0]+(.1268*Otk[23][0]))-utk[6][0]);
        Tstar[23][1] = ((WkIkWk[23][1]+(.0332*Otk[23][1]))-utk[6][1]);
        Tstar[23][2] = ((WkIkWk[23][2]+(.1337*Otk[23][2]))-utk[6][2]);
        Tstar[26][0] = ((WkIkWk[26][0]+(.0477*Otk[26][0]))-utk[7][0]);
        Tstar[26][1] = ((WkIkWk[26][1]+(.0048*Otk[26][1]))-utk[7][1]);
        Tstar[26][2] = ((WkIkWk[26][2]+(.0484*Otk[26][2]))-utk[7][2]);
        Tstar[29][0] = ((WkIkWk[29][0]+(.001361*Otk[29][0]))-utk[8][0]);
        Tstar[29][1] = ((WkIkWk[29][1]+(.003709*Otk[29][1]))-utk[8][1]);
        Tstar[29][2] = ((WkIkWk[29][2]+(.003916*Otk[29][2]))-utk[8][2]);
        Tstar[32][0] = ((WkIkWk[32][0]+(.000117*Otk[32][0]))-utk[9][0]);
        Tstar[32][1] = ((WkIkWk[32][1]+(.000179*Otk[32][1]))-utk[9][1]);
        Tstar[32][2] = ((WkIkWk[32][2]+(.000119*Otk[32][2]))-utk[9][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        temp[0] = (((Fstar[14][2]*Vpk[0][14][2])+((Fstar[14][0]*Vpk[0][14][0])+(
          Fstar[14][1]*Vpk[0][14][1])))+(((Fstar[11][2]*Vpk[0][11][2])+((
          Fstar[11][0]*Vpk[0][11][0])+(Fstar[11][1]*Vpk[0][11][1])))+(((
          Fstar[5][2]*Vpk[0][3][2])+((Fstar[5][0]*Vpk[0][3][0])+(Fstar[5][1]*
          Vpk[0][3][1])))+((Fstar[8][2]*Vpk[0][8][2])+((Fstar[8][0]*Vpk[0][8][0]
          )+(Fstar[8][1]*Vpk[0][8][1]))))));
        temp[1] = (((Fstar[26][2]*Vpk[0][26][2])+((Fstar[26][0]*Vpk[0][26][0])+(
          Fstar[26][1]*Vpk[0][26][1])))+(((Fstar[23][2]*Vpk[0][23][2])+((
          Fstar[23][0]*Vpk[0][23][0])+(Fstar[23][1]*Vpk[0][23][1])))+(((
          Fstar[20][2]*Vpk[0][20][2])+((Fstar[20][0]*Vpk[0][20][0])+(
          Fstar[20][1]*Vpk[0][20][1])))+(((Fstar[17][2]*Vpk[0][17][2])+((
          Fstar[17][0]*Vpk[0][17][0])+(Fstar[17][1]*Vpk[0][17][1])))+temp[0]))))
          ;
        fs0[0] = (utau[0]-(((Fstar[32][2]*Vpk[0][32][2])+((Fstar[32][0]*
          Vpk[0][32][0])+(Fstar[32][1]*Vpk[0][32][1])))+(((Fstar[29][2]*
          Vpk[0][29][2])+((Fstar[29][0]*Vpk[0][29][0])+(Fstar[29][1]*
          Vpk[0][29][1])))+temp[1])));
        temp[0] = (((Fstar[14][2]*Vpk[1][14][2])+((Fstar[14][0]*Vpk[1][14][0])+(
          Fstar[14][1]*Vpk[1][14][1])))+(((Fstar[11][2]*Vpk[1][11][2])+((
          Fstar[11][0]*Vpk[1][11][0])+(Fstar[11][1]*Vpk[1][11][1])))+(((
          Fstar[5][2]*Vpk[1][3][2])+((Fstar[5][0]*Vpk[1][3][0])+(Fstar[5][1]*
          Vpk[1][3][1])))+((Fstar[8][2]*Vpk[1][8][2])+((Fstar[8][0]*Vpk[1][8][0]
          )+(Fstar[8][1]*Vpk[1][8][1]))))));
        temp[1] = (((Fstar[26][2]*Vpk[1][26][2])+((Fstar[26][0]*Vpk[1][26][0])+(
          Fstar[26][1]*Vpk[1][26][1])))+(((Fstar[23][2]*Vpk[1][23][2])+((
          Fstar[23][0]*Vpk[1][23][0])+(Fstar[23][1]*Vpk[1][23][1])))+(((
          Fstar[20][2]*Vpk[1][20][2])+((Fstar[20][0]*Vpk[1][20][0])+(
          Fstar[20][1]*Vpk[1][20][1])))+(((Fstar[17][2]*Vpk[1][17][2])+((
          Fstar[17][0]*Vpk[1][17][0])+(Fstar[17][1]*Vpk[1][17][1])))+temp[0]))))
          ;
        fs0[1] = (utau[1]-(((Fstar[32][2]*Vpk[1][32][2])+((Fstar[32][0]*
          Vpk[1][32][0])+(Fstar[32][1]*Vpk[1][32][1])))+(((Fstar[29][2]*
          Vpk[1][29][2])+((Fstar[29][0]*Vpk[1][29][0])+(Fstar[29][1]*
          Vpk[1][29][1])))+temp[1])));
        temp[0] = (((Fstar[14][2]*Vpk[2][14][2])+((Fstar[14][0]*Vpk[2][14][0])+(
          Fstar[14][1]*Vpk[2][14][1])))+(((Fstar[11][2]*Vpk[2][11][2])+((
          Fstar[11][0]*Vpk[2][11][0])+(Fstar[11][1]*Vpk[2][11][1])))+(((
          Fstar[5][2]*Vpk[2][3][2])+((Fstar[5][0]*Vpk[2][3][0])+(Fstar[5][1]*
          Vpk[2][3][1])))+((Fstar[8][2]*Vpk[2][8][2])+((Fstar[8][0]*Vpk[2][8][0]
          )+(Fstar[8][1]*Vpk[2][8][1]))))));
        temp[1] = (((Fstar[26][2]*Vpk[2][26][2])+((Fstar[26][0]*Vpk[2][26][0])+(
          Fstar[26][1]*Vpk[2][26][1])))+(((Fstar[23][2]*Vpk[2][23][2])+((
          Fstar[23][0]*Vpk[2][23][0])+(Fstar[23][1]*Vpk[2][23][1])))+(((
          Fstar[20][2]*Vpk[2][20][2])+((Fstar[20][0]*Vpk[2][20][0])+(
          Fstar[20][1]*Vpk[2][20][1])))+(((Fstar[17][2]*Vpk[2][17][2])+((
          Fstar[17][0]*Vpk[2][17][0])+(Fstar[17][1]*Vpk[2][17][1])))+temp[0]))))
          ;
        fs0[2] = (utau[2]-(((Fstar[32][2]*Vpk[2][32][2])+((Fstar[32][0]*
          Vpk[2][32][0])+(Fstar[32][1]*Vpk[2][32][1])))+(((Fstar[29][2]*
          Vpk[2][29][2])+((Fstar[29][0]*Vpk[2][29][0])+(Fstar[29][1]*
          Vpk[2][29][1])))+temp[1])));
        temp[0] = ((Tstar[5][0]+(((Fstar[8][2]*Vpk[3][8][2])+((Fstar[8][0]*
          Vpk[3][8][0])+(Fstar[8][1]*Vpk[3][8][1])))+((Tstar[8][2]*Wpk[3][8][2])
          +((Tstar[8][0]*Wpk[3][8][0])+(Tstar[8][1]*Wpk[3][8][1])))))+(((
          Fstar[11][2]*Vpk[3][11][2])+((Fstar[11][0]*Vpk[3][11][0])+(
          Fstar[11][1]*Vpk[3][11][1])))+((Tstar[11][2]*Wpk[3][11][2])+((
          Tstar[11][0]*Wpk[3][11][0])+(Tstar[11][1]*Wpk[3][11][1])))));
        temp[1] = ((((Fstar[17][2]*Vpk[3][17][2])+((Fstar[17][0]*Vpk[3][17][0])+
          (Fstar[17][1]*Vpk[3][17][1])))+((Tstar[17][2]*Wpk[3][17][2])+((
          Tstar[17][0]*Wpk[3][17][0])+(Tstar[17][1]*Wpk[3][17][1]))))+(temp[0]+(
          ((Fstar[14][2]*Vpk[3][14][2])+((Fstar[14][0]*Vpk[3][14][0])+(
          Fstar[14][1]*Vpk[3][14][1])))+((Tstar[14][2]*Wpk[3][14][2])+((
          Tstar[14][0]*Wpk[3][14][0])+(Tstar[14][1]*Wpk[3][14][1]))))));
        temp[2] = ((((Fstar[23][2]*Vpk[3][23][2])+((Fstar[23][0]*Vpk[3][23][0])+
          (Fstar[23][1]*Vpk[3][23][1])))+((Tstar[23][2]*Wpk[3][23][2])+((
          Tstar[23][0]*Wpk[3][23][0])+(Tstar[23][1]*Wpk[3][23][1]))))+((((
          Fstar[20][2]*Vpk[3][20][2])+((Fstar[20][0]*Vpk[3][20][0])+(
          Fstar[20][1]*Vpk[3][20][1])))+((Tstar[20][2]*Wpk[3][20][2])+((
          Tstar[20][0]*Wpk[3][20][0])+(Tstar[20][1]*Wpk[3][20][1]))))+temp[1]));
        temp[3] = ((((Fstar[29][2]*Vpk[3][29][2])+((Fstar[29][0]*Vpk[3][29][0])+
          (Fstar[29][1]*Vpk[3][29][1])))+((Tstar[29][2]*Wpk[3][29][2])+((
          Tstar[29][0]*Wpk[3][29][0])+(Tstar[29][1]*Wpk[3][29][1]))))+((((
          Fstar[26][2]*Vpk[3][26][2])+((Fstar[26][0]*Vpk[3][26][0])+(
          Fstar[26][1]*Vpk[3][26][1])))+((Tstar[26][2]*Wpk[3][26][2])+((
          Tstar[26][0]*Wpk[3][26][0])+(Tstar[26][1]*Wpk[3][26][1]))))+temp[2]));
        fs0[3] = (utau[3]-((((Fstar[32][2]*Vpk[3][32][2])+((Fstar[32][0]*
          Vpk[3][32][0])+(Fstar[32][1]*Vpk[3][32][1])))+((Tstar[32][2]*
          Wpk[3][32][2])+((Tstar[32][0]*Wpk[3][32][0])+(Tstar[32][1]*
          Wpk[3][32][1]))))+temp[3]));
        temp[0] = ((Tstar[5][1]+((.3202*((Fstar[8][2]*Wpk[4][8][0])-(Fstar[8][0]
          *Wpk[4][8][2])))+((Tstar[8][2]*Wpk[4][8][2])+((Tstar[8][0]*
          Wpk[4][8][0])+(Tstar[8][1]*Wpk[4][8][1])))))+(((Fstar[11][2]*
          Vpk[4][11][2])+((Fstar[11][0]*Vpk[4][11][0])+(Fstar[11][1]*
          Vpk[4][11][1])))+((Tstar[11][2]*Wpk[4][11][2])+((Tstar[11][0]*
          Wpk[4][11][0])+(Tstar[11][1]*Wpk[4][11][1])))));
        temp[1] = ((((Fstar[17][2]*Vpk[4][17][2])+((Fstar[17][0]*Vpk[4][17][0])+
          (Fstar[17][1]*Vpk[4][17][1])))+((Tstar[17][2]*Wpk[4][17][2])+((
          Tstar[17][0]*Wpk[4][17][0])+(Tstar[17][1]*Wpk[4][17][1]))))+(temp[0]+(
          ((Fstar[14][2]*Vpk[4][14][2])+((Fstar[14][0]*Vpk[4][14][0])+(
          Fstar[14][1]*Vpk[4][14][1])))+((Tstar[14][2]*Wpk[4][14][2])+((
          Tstar[14][0]*Wpk[4][14][0])+(Tstar[14][1]*Wpk[4][14][1]))))));
        temp[2] = ((((Fstar[23][2]*Vpk[4][23][2])+((Fstar[23][0]*Vpk[4][23][0])+
          (Fstar[23][1]*Vpk[4][23][1])))+((Tstar[23][2]*Wpk[4][23][2])+((
          Tstar[23][0]*Wpk[4][23][0])+(Tstar[23][1]*Wpk[4][23][1]))))+((((
          Fstar[20][2]*Vpk[4][20][2])+((Fstar[20][0]*Vpk[4][20][0])+(
          Fstar[20][1]*Vpk[4][20][1])))+((Tstar[20][2]*Wpk[4][20][2])+((
          Tstar[20][0]*Wpk[4][20][0])+(Tstar[20][1]*Wpk[4][20][1]))))+temp[1]));
        temp[3] = ((((Fstar[29][2]*Vpk[4][29][2])+((Fstar[29][0]*Vpk[4][29][0])+
          (Fstar[29][1]*Vpk[4][29][1])))+((Tstar[29][2]*Wpk[4][29][2])+((
          Tstar[29][0]*Wpk[4][29][0])+(Tstar[29][1]*Wpk[4][29][1]))))+((((
          Fstar[26][2]*Vpk[4][26][2])+((Fstar[26][0]*Vpk[4][26][0])+(
          Fstar[26][1]*Vpk[4][26][1])))+((Tstar[26][2]*Wpk[4][26][2])+((
          Tstar[26][0]*Wpk[4][26][0])+(Tstar[26][1]*Wpk[4][26][1]))))+temp[2]));
        fs0[4] = (utau[4]-((((Fstar[32][2]*Vpk[4][32][2])+((Fstar[32][0]*
          Vpk[4][32][0])+(Fstar[32][1]*Vpk[4][32][1])))+((Tstar[32][2]*
          Wpk[4][32][2])+((Tstar[32][0]*Wpk[4][32][0])+(Tstar[32][1]*
          Wpk[4][32][1]))))+temp[3]));
        temp[0] = ((Tstar[5][2]+(((Fstar[8][2]*Vpk[5][8][2])+((Fstar[8][0]*
          Vpk[5][8][0])+(Fstar[8][1]*Vpk[5][8][1])))+((Tstar[8][2]*Wpk[5][8][2])
          +((Tstar[8][0]*Wpk[5][8][0])+(Tstar[8][1]*Wpk[5][8][1])))))+(((
          Fstar[11][2]*Vpk[5][11][2])+((Fstar[11][0]*Vpk[5][11][0])+(
          Fstar[11][1]*Vpk[5][11][1])))+((Tstar[11][2]*Wpk[5][11][2])+((
          Tstar[11][0]*Wpk[5][11][0])+(Tstar[11][1]*Wpk[5][11][1])))));
        temp[1] = ((((Fstar[17][2]*Vpk[5][17][2])+((Fstar[17][0]*Vpk[5][17][0])+
          (Fstar[17][1]*Vpk[5][17][1])))+((Tstar[17][2]*Wpk[5][17][2])+((
          Tstar[17][0]*Wpk[5][17][0])+(Tstar[17][1]*Wpk[5][17][1]))))+(temp[0]+(
          ((Fstar[14][2]*Vpk[5][14][2])+((Fstar[14][0]*Vpk[5][14][0])+(
          Fstar[14][1]*Vpk[5][14][1])))+((Tstar[14][2]*Wpk[5][14][2])+((
          Tstar[14][0]*Wpk[5][14][0])+(Tstar[14][1]*Wpk[5][14][1]))))));
        temp[2] = ((((Fstar[23][2]*Vpk[5][23][2])+((Fstar[23][0]*Vpk[5][23][0])+
          (Fstar[23][1]*Vpk[5][23][1])))+((Tstar[23][2]*Wpk[5][23][2])+((
          Tstar[23][0]*Wpk[5][23][0])+(Tstar[23][1]*Wpk[5][23][1]))))+((((
          Fstar[20][2]*Vpk[5][20][2])+((Fstar[20][0]*Vpk[5][20][0])+(
          Fstar[20][1]*Vpk[5][20][1])))+((Tstar[20][2]*Wpk[5][20][2])+((
          Tstar[20][0]*Wpk[5][20][0])+(Tstar[20][1]*Wpk[5][20][1]))))+temp[1]));
        temp[3] = ((((Fstar[29][2]*Vpk[5][29][2])+((Fstar[29][0]*Vpk[5][29][0])+
          (Fstar[29][1]*Vpk[5][29][1])))+((Tstar[29][2]*Wpk[5][29][2])+((
          Tstar[29][0]*Wpk[5][29][0])+(Tstar[29][1]*Wpk[5][29][1]))))+((((
          Fstar[26][2]*Vpk[5][26][2])+((Fstar[26][0]*Vpk[5][26][0])+(
          Fstar[26][1]*Vpk[5][26][1])))+((Tstar[26][2]*Wpk[5][26][2])+((
          Tstar[26][0]*Wpk[5][26][0])+(Tstar[26][1]*Wpk[5][26][1]))))+temp[2]));
        fs0[5] = (utau[5]-((((Fstar[32][2]*Vpk[5][32][2])+((Fstar[32][0]*
          Vpk[5][32][0])+(Fstar[32][1]*Vpk[5][32][1])))+((Tstar[32][2]*
          Wpk[5][32][2])+((Tstar[32][0]*Wpk[5][32][0])+(Tstar[32][1]*
          Wpk[5][32][1]))))+temp[3]));
        fs0[6] = (utau[6]-((.3202*((Fstar[8][2]*Wpk[6][8][0])-(Fstar[8][0]*
          Wpk[6][8][2])))+((Tstar[8][2]*Wpk[6][8][2])+((Tstar[8][0]*Wpk[6][8][0]
          )+(Tstar[8][1]*Wpk[6][8][1])))));
        fs0[7] = (utau[7]-((.3202*((Fstar[8][2]*Wpk[7][8][0])-(Fstar[8][0]*
          Wpk[7][8][2])))+((Tstar[8][2]*Wpk[7][8][2])+((Tstar[8][0]*Wpk[7][8][0]
          )+(Tstar[8][1]*Wpk[7][8][1])))));
        fs0[8] = (utau[8]-((.3202*((Fstar[8][2]*pin[8][0])-(Fstar[8][0]*
          pin[8][2])))+((pin[8][2]*Tstar[8][2])+((pin[8][0]*Tstar[8][0])+(
          pin[8][1]*Tstar[8][1])))));
        temp[0] = ((((Fstar[11][2]*Vpk[9][11][2])+((.1715*(Fstar[11][0]*
          Wpk[9][11][2]))-(.002*(Fstar[11][1]*Wpk[9][11][2]))))+((Tstar[11][2]*
          Wpk[9][11][2])+((Tstar[11][0]*Wpk[9][11][0])+(Tstar[11][1]*
          Wpk[9][11][1]))))+(((Fstar[14][2]*Vpk[9][14][2])+((Fstar[14][0]*
          Vpk[9][14][0])+(Fstar[14][1]*Vpk[9][14][1])))+((Tstar[14][2]*
          Wpk[9][14][2])+((Tstar[14][0]*Wpk[9][14][0])+(Tstar[14][1]*
          Wpk[9][14][1])))));
        fs0[9] = (utau[9]-((((Fstar[20][2]*Vpk[9][20][2])+((Fstar[20][0]*
          Vpk[9][20][0])+(Fstar[20][1]*Vpk[9][20][1])))+((Tstar[20][2]*
          Wpk[9][20][2])+((Tstar[20][0]*Wpk[9][20][0])+(Tstar[20][1]*
          Wpk[9][20][1]))))+((((Fstar[17][2]*Vpk[9][17][2])+((Fstar[17][0]*
          Vpk[9][17][0])+(Fstar[17][1]*Vpk[9][17][1])))+((Tstar[17][2]*
          Wpk[9][17][2])+((Tstar[17][0]*Wpk[9][17][0])+(Tstar[17][1]*
          Wpk[9][17][1]))))+temp[0])));
        temp[0] = ((((Fstar[11][2]*Vpk[10][11][2])+((.1715*(Fstar[11][0]*
          Wpk[10][11][2]))-(.002*(Fstar[11][1]*Wpk[10][11][2]))))+((Tstar[11][2]
          *Wpk[10][11][2])+((Tstar[11][0]*Wpk[10][11][0])+(Tstar[11][1]*
          Wpk[10][11][1]))))+(((Fstar[14][2]*Vpk[10][14][2])+((Fstar[14][0]*
          Vpk[10][14][0])+(Fstar[14][1]*Vpk[10][14][1])))+((Tstar[14][2]*
          Wpk[10][14][2])+((Tstar[14][0]*Wpk[10][14][0])+(Tstar[14][1]*
          Wpk[10][14][1])))));
        fs0[10] = (utau[10]-((((Fstar[20][2]*Vpk[10][20][2])+((Fstar[20][0]*
          Vpk[10][20][0])+(Fstar[20][1]*Vpk[10][20][1])))+((Tstar[20][2]*
          Wpk[10][20][2])+((Tstar[20][0]*Wpk[10][20][0])+(Tstar[20][1]*
          Wpk[10][20][1]))))+((((Fstar[17][2]*Vpk[10][17][2])+((Fstar[17][0]*
          Vpk[10][17][0])+(Fstar[17][1]*Vpk[10][17][1])))+((Tstar[17][2]*
          Wpk[10][17][2])+((Tstar[17][0]*Wpk[10][17][0])+(Tstar[17][1]*
          Wpk[10][17][1]))))+temp[0])));
        temp[0] = ((((Fstar[11][2]*Vpk[11][11][2])+((.1715*(Fstar[11][0]*
          pin[11][2]))-(.002*(Fstar[11][1]*pin[11][2]))))+((pin[11][2]*
          Tstar[11][2])+((pin[11][0]*Tstar[11][0])+(pin[11][1]*Tstar[11][1]))))+
          (((Fstar[14][2]*Vpk[11][14][2])+((Fstar[14][0]*Vpk[11][14][0])+(
          Fstar[14][1]*Vpk[11][14][1])))+((Tstar[14][2]*Wpk[11][14][2])+((
          Tstar[14][0]*Wpk[11][14][0])+(Tstar[14][1]*Wpk[11][14][1])))));
        fs0[11] = (utau[11]-((((Fstar[20][2]*Vpk[11][20][2])+((Fstar[20][0]*
          Vpk[11][20][0])+(Fstar[20][1]*Vpk[11][20][1])))+((Tstar[20][2]*
          Wpk[11][20][2])+((Tstar[20][0]*Wpk[11][20][0])+(Tstar[20][1]*
          Wpk[11][20][1]))))+((((Fstar[17][2]*Vpk[11][17][2])+((Fstar[17][0]*
          Vpk[11][17][0])+(Fstar[17][1]*Vpk[11][17][1])))+((Tstar[17][2]*
          Wpk[11][17][2])+((Tstar[17][0]*Wpk[11][17][0])+(Tstar[17][1]*
          Wpk[11][17][1]))))+temp[0])));
        temp[0] = (((.1862*((Fstar[14][0]*Wpk[12][14][2])-(Fstar[14][2]*
          Wpk[12][14][0])))+((Tstar[14][2]*Wpk[12][14][2])+((Tstar[14][0]*
          Wpk[12][14][0])+(Tstar[14][1]*Wpk[12][14][1]))))+(((Fstar[17][2]*
          Vpk[12][17][2])+((Fstar[17][0]*Vpk[12][17][0])+(Fstar[17][1]*
          Vpk[12][17][1])))+((Tstar[17][2]*Wpk[12][17][2])+((Tstar[17][0]*
          Wpk[12][17][0])+(Tstar[17][1]*Wpk[12][17][1])))));
        fs0[12] = (utau[12]-(temp[0]+(((Fstar[20][2]*Vpk[12][20][2])+((
          Fstar[20][0]*Vpk[12][20][0])+(Fstar[20][1]*Vpk[12][20][1])))+((
          Tstar[20][2]*Wpk[12][20][2])+((Tstar[20][0]*Wpk[12][20][0])+(
          Tstar[20][1]*Wpk[12][20][1]))))));
        temp[0] = (((.1862*((Fstar[14][0]*Wpk[13][14][2])-(Fstar[14][2]*
          Wpk[13][14][0])))+((Tstar[14][2]*Wpk[13][14][2])+((Tstar[14][0]*
          Wpk[13][14][0])+(Tstar[14][1]*Wpk[13][14][1]))))+(((Fstar[17][2]*
          Vpk[13][17][2])+((Fstar[17][0]*Vpk[13][17][0])+(Fstar[17][1]*
          Vpk[13][17][1])))+((Tstar[17][2]*Wpk[13][17][2])+((Tstar[17][0]*
          Wpk[13][17][0])+(Tstar[17][1]*Wpk[13][17][1])))));
        fs0[13] = (utau[13]-(temp[0]+(((Fstar[20][2]*Vpk[13][20][2])+((
          Fstar[20][0]*Vpk[13][20][0])+(Fstar[20][1]*Vpk[13][20][1])))+((
          Tstar[20][2]*Wpk[13][20][2])+((Tstar[20][0]*Wpk[13][20][0])+(
          Tstar[20][1]*Wpk[13][20][1]))))));
        temp[0] = (((.1862*((Fstar[14][0]*pin[14][2])-(Fstar[14][2]*pin[14][0]))
          )+((pin[14][2]*Tstar[14][2])+((pin[14][0]*Tstar[14][0])+(pin[14][1]*
          Tstar[14][1]))))+(((Fstar[17][2]*Vpk[14][17][2])+((Fstar[17][0]*
          Vpk[14][17][0])+(Fstar[17][1]*Vpk[14][17][1])))+((Tstar[17][2]*
          Wpk[14][17][2])+((Tstar[17][0]*Wpk[14][17][0])+(Tstar[17][1]*
          Wpk[14][17][1])))));
        fs0[14] = (utau[14]-(temp[0]+(((Fstar[20][2]*Vpk[14][20][2])+((
          Fstar[20][0]*Vpk[14][20][0])+(Fstar[20][1]*Vpk[14][20][1])))+((
          Tstar[20][2]*Wpk[14][20][2])+((Tstar[20][0]*Wpk[14][20][0])+(
          Tstar[20][1]*Wpk[14][20][1]))))));
        fs0[15] = (utau[15]-((((Fstar[17][2]*Vpk[15][17][2])+((Fstar[17][0]*
          Vpk[15][17][0])+(Fstar[17][1]*Vpk[15][17][1])))+((Tstar[17][2]*
          Wpk[15][17][2])+((Tstar[17][0]*Wpk[15][17][0])+(Tstar[17][1]*
          Wpk[15][17][1]))))+(((Fstar[20][2]*Vpk[15][20][2])+((Fstar[20][0]*
          Vpk[15][20][0])+(Fstar[20][1]*Vpk[15][20][1])))+((Tstar[20][2]*
          Wpk[15][20][2])+((Tstar[20][0]*Wpk[15][20][0])+(Tstar[20][1]*
          Wpk[15][20][1]))))));
        fs0[16] = (utau[16]-((((Fstar[17][2]*Vpk[16][17][2])+((Fstar[17][0]*
          Vpk[16][17][0])+(Fstar[17][1]*Vpk[16][17][1])))+((Tstar[17][2]*
          Wpk[16][17][2])+((Tstar[17][0]*Wpk[16][17][0])+(Tstar[17][1]*
          Wpk[16][17][1]))))+(((Fstar[20][2]*Vpk[16][20][2])+((Fstar[20][0]*
          Vpk[16][20][0])+(Fstar[20][1]*Vpk[16][20][1])))+((Tstar[20][2]*
          Wpk[16][20][2])+((Tstar[20][0]*Wpk[16][20][0])+(Tstar[20][1]*
          Wpk[16][20][1]))))));
        fs0[17] = (utau[17]-((((Fstar[17][2]*Vpk[17][17][2])+((Fstar[17][0]*
          Vpk[17][17][0])+(Fstar[17][1]*Vpk[17][17][1])))+((pin[17][2]*
          Tstar[17][2])+((pin[17][0]*Tstar[17][0])+(pin[17][1]*Tstar[17][1]))))+
          (((Fstar[20][2]*Vpk[17][20][2])+((Fstar[20][0]*Vpk[17][20][0])+(
          Fstar[20][1]*Vpk[17][20][1])))+((Tstar[20][2]*Wpk[17][20][2])+((
          Tstar[20][0]*Wpk[17][20][0])+(Tstar[20][1]*Wpk[17][20][1]))))));
        fs0[18] = (utau[18]-(((Fstar[20][2]*Vpk[18][20][2])+((Fstar[20][0]*
          Vpk[18][20][0])+(Fstar[20][1]*Vpk[18][20][1])))+((Tstar[20][2]*
          Wpk[18][20][2])+((Tstar[20][0]*Wpk[18][20][0])+(Tstar[20][1]*
          Wpk[18][20][1])))));
        fs0[19] = (utau[19]-(((Fstar[20][2]*Vpk[19][20][2])+((Fstar[20][0]*
          Vpk[19][20][0])+(Fstar[20][1]*Vpk[19][20][1])))+((Tstar[20][2]*
          Wpk[19][20][2])+((Tstar[20][0]*Wpk[19][20][0])+(Tstar[20][1]*
          Wpk[19][20][1])))));
        fs0[20] = (utau[20]-(((Fstar[20][2]*Vpk[20][20][2])+((Fstar[20][0]*
          Vpk[20][20][0])+(Fstar[20][1]*Vpk[20][20][1])))+((pin[20][2]*
          Tstar[20][2])+((pin[20][0]*Tstar[20][0])+(pin[20][1]*Tstar[20][1])))))
          ;
        temp[0] = ((((Fstar[23][2]*Vpk[21][23][2])+((.1715*(Fstar[23][0]*
          Wpk[21][23][2]))-(.002*(Fstar[23][1]*Wpk[21][23][2]))))+((Tstar[23][2]
          *Wpk[21][23][2])+((Tstar[23][0]*Wpk[21][23][0])+(Tstar[23][1]*
          Wpk[21][23][1]))))+(((Fstar[26][2]*Vpk[21][26][2])+((Fstar[26][0]*
          Vpk[21][26][0])+(Fstar[26][1]*Vpk[21][26][1])))+((Tstar[26][2]*
          Wpk[21][26][2])+((Tstar[26][0]*Wpk[21][26][0])+(Tstar[26][1]*
          Wpk[21][26][1])))));
        fs0[21] = (utau[21]-((((Fstar[32][2]*Vpk[21][32][2])+((Fstar[32][0]*
          Vpk[21][32][0])+(Fstar[32][1]*Vpk[21][32][1])))+((Tstar[32][2]*
          Wpk[21][32][2])+((Tstar[32][0]*Wpk[21][32][0])+(Tstar[32][1]*
          Wpk[21][32][1]))))+((((Fstar[29][2]*Vpk[21][29][2])+((Fstar[29][0]*
          Vpk[21][29][0])+(Fstar[29][1]*Vpk[21][29][1])))+((Tstar[29][2]*
          Wpk[21][29][2])+((Tstar[29][0]*Wpk[21][29][0])+(Tstar[29][1]*
          Wpk[21][29][1]))))+temp[0])));
        temp[0] = ((((Fstar[23][2]*Vpk[22][23][2])+((.1715*(Fstar[23][0]*
          Wpk[22][23][2]))-(.002*(Fstar[23][1]*Wpk[22][23][2]))))+((Tstar[23][2]
          *Wpk[22][23][2])+((Tstar[23][0]*Wpk[22][23][0])+(Tstar[23][1]*
          Wpk[22][23][1]))))+(((Fstar[26][2]*Vpk[22][26][2])+((Fstar[26][0]*
          Vpk[22][26][0])+(Fstar[26][1]*Vpk[22][26][1])))+((Tstar[26][2]*
          Wpk[22][26][2])+((Tstar[26][0]*Wpk[22][26][0])+(Tstar[26][1]*
          Wpk[22][26][1])))));
        fs0[22] = (utau[22]-((((Fstar[32][2]*Vpk[22][32][2])+((Fstar[32][0]*
          Vpk[22][32][0])+(Fstar[32][1]*Vpk[22][32][1])))+((Tstar[32][2]*
          Wpk[22][32][2])+((Tstar[32][0]*Wpk[22][32][0])+(Tstar[32][1]*
          Wpk[22][32][1]))))+((((Fstar[29][2]*Vpk[22][29][2])+((Fstar[29][0]*
          Vpk[22][29][0])+(Fstar[29][1]*Vpk[22][29][1])))+((Tstar[29][2]*
          Wpk[22][29][2])+((Tstar[29][0]*Wpk[22][29][0])+(Tstar[29][1]*
          Wpk[22][29][1]))))+temp[0])));
        temp[0] = ((((Fstar[23][2]*Vpk[23][23][2])+((.1715*(Fstar[23][0]*
          pin[23][2]))-(.002*(Fstar[23][1]*pin[23][2]))))+((pin[23][2]*
          Tstar[23][2])+((pin[23][0]*Tstar[23][0])+(pin[23][1]*Tstar[23][1]))))+
          (((Fstar[26][2]*Vpk[23][26][2])+((Fstar[26][0]*Vpk[23][26][0])+(
          Fstar[26][1]*Vpk[23][26][1])))+((Tstar[26][2]*Wpk[23][26][2])+((
          Tstar[26][0]*Wpk[23][26][0])+(Tstar[26][1]*Wpk[23][26][1])))));
        fs0[23] = (utau[23]-((((Fstar[32][2]*Vpk[23][32][2])+((Fstar[32][0]*
          Vpk[23][32][0])+(Fstar[32][1]*Vpk[23][32][1])))+((Tstar[32][2]*
          Wpk[23][32][2])+((Tstar[32][0]*Wpk[23][32][0])+(Tstar[32][1]*
          Wpk[23][32][1]))))+((((Fstar[29][2]*Vpk[23][29][2])+((Fstar[29][0]*
          Vpk[23][29][0])+(Fstar[29][1]*Vpk[23][29][1])))+((Tstar[29][2]*
          Wpk[23][29][2])+((Tstar[29][0]*Wpk[23][29][0])+(Tstar[29][1]*
          Wpk[23][29][1]))))+temp[0])));
        temp[0] = (((.1862*((Fstar[26][0]*Wpk[24][26][2])-(Fstar[26][2]*
          Wpk[24][26][0])))+((Tstar[26][2]*Wpk[24][26][2])+((Tstar[26][0]*
          Wpk[24][26][0])+(Tstar[26][1]*Wpk[24][26][1]))))+(((Fstar[29][2]*
          Vpk[24][29][2])+((Fstar[29][0]*Vpk[24][29][0])+(Fstar[29][1]*
          Vpk[24][29][1])))+((Tstar[29][2]*Wpk[24][29][2])+((Tstar[29][0]*
          Wpk[24][29][0])+(Tstar[29][1]*Wpk[24][29][1])))));
        fs0[24] = (utau[24]-(temp[0]+(((Fstar[32][2]*Vpk[24][32][2])+((
          Fstar[32][0]*Vpk[24][32][0])+(Fstar[32][1]*Vpk[24][32][1])))+((
          Tstar[32][2]*Wpk[24][32][2])+((Tstar[32][0]*Wpk[24][32][0])+(
          Tstar[32][1]*Wpk[24][32][1]))))));
        temp[0] = (((.1862*((Fstar[26][0]*Wpk[25][26][2])-(Fstar[26][2]*
          Wpk[25][26][0])))+((Tstar[26][2]*Wpk[25][26][2])+((Tstar[26][0]*
          Wpk[25][26][0])+(Tstar[26][1]*Wpk[25][26][1]))))+(((Fstar[29][2]*
          Vpk[25][29][2])+((Fstar[29][0]*Vpk[25][29][0])+(Fstar[29][1]*
          Vpk[25][29][1])))+((Tstar[29][2]*Wpk[25][29][2])+((Tstar[29][0]*
          Wpk[25][29][0])+(Tstar[29][1]*Wpk[25][29][1])))));
        fs0[25] = (utau[25]-(temp[0]+(((Fstar[32][2]*Vpk[25][32][2])+((
          Fstar[32][0]*Vpk[25][32][0])+(Fstar[32][1]*Vpk[25][32][1])))+((
          Tstar[32][2]*Wpk[25][32][2])+((Tstar[32][0]*Wpk[25][32][0])+(
          Tstar[32][1]*Wpk[25][32][1]))))));
        temp[0] = (((.1862*((Fstar[26][0]*pin[26][2])-(Fstar[26][2]*pin[26][0]))
          )+((pin[26][2]*Tstar[26][2])+((pin[26][0]*Tstar[26][0])+(pin[26][1]*
          Tstar[26][1]))))+(((Fstar[29][2]*Vpk[26][29][2])+((Fstar[29][0]*
          Vpk[26][29][0])+(Fstar[29][1]*Vpk[26][29][1])))+((Tstar[29][2]*
          Wpk[26][29][2])+((Tstar[29][0]*Wpk[26][29][0])+(Tstar[29][1]*
          Wpk[26][29][1])))));
        fs0[26] = (utau[26]-(temp[0]+(((Fstar[32][2]*Vpk[26][32][2])+((
          Fstar[32][0]*Vpk[26][32][0])+(Fstar[32][1]*Vpk[26][32][1])))+((
          Tstar[32][2]*Wpk[26][32][2])+((Tstar[32][0]*Wpk[26][32][0])+(
          Tstar[32][1]*Wpk[26][32][1]))))));
        fs0[27] = (utau[27]-((((Fstar[29][2]*Vpk[27][29][2])+((Fstar[29][0]*
          Vpk[27][29][0])+(Fstar[29][1]*Vpk[27][29][1])))+((Tstar[29][2]*
          Wpk[27][29][2])+((Tstar[29][0]*Wpk[27][29][0])+(Tstar[29][1]*
          Wpk[27][29][1]))))+(((Fstar[32][2]*Vpk[27][32][2])+((Fstar[32][0]*
          Vpk[27][32][0])+(Fstar[32][1]*Vpk[27][32][1])))+((Tstar[32][2]*
          Wpk[27][32][2])+((Tstar[32][0]*Wpk[27][32][0])+(Tstar[32][1]*
          Wpk[27][32][1]))))));
        fs0[28] = (utau[28]-((((Fstar[29][2]*Vpk[28][29][2])+((Fstar[29][0]*
          Vpk[28][29][0])+(Fstar[29][1]*Vpk[28][29][1])))+((Tstar[29][2]*
          Wpk[28][29][2])+((Tstar[29][0]*Wpk[28][29][0])+(Tstar[29][1]*
          Wpk[28][29][1]))))+(((Fstar[32][2]*Vpk[28][32][2])+((Fstar[32][0]*
          Vpk[28][32][0])+(Fstar[32][1]*Vpk[28][32][1])))+((Tstar[32][2]*
          Wpk[28][32][2])+((Tstar[32][0]*Wpk[28][32][0])+(Tstar[32][1]*
          Wpk[28][32][1]))))));
        fs0[29] = (utau[29]-((((Fstar[29][2]*Vpk[29][29][2])+((Fstar[29][0]*
          Vpk[29][29][0])+(Fstar[29][1]*Vpk[29][29][1])))+((pin[29][2]*
          Tstar[29][2])+((pin[29][0]*Tstar[29][0])+(pin[29][1]*Tstar[29][1]))))+
          (((Fstar[32][2]*Vpk[29][32][2])+((Fstar[32][0]*Vpk[29][32][0])+(
          Fstar[32][1]*Vpk[29][32][1])))+((Tstar[32][2]*Wpk[29][32][2])+((
          Tstar[32][0]*Wpk[29][32][0])+(Tstar[32][1]*Wpk[29][32][1]))))));
        fs0[30] = (utau[30]-(((Fstar[32][2]*Vpk[30][32][2])+((Fstar[32][0]*
          Vpk[30][32][0])+(Fstar[32][1]*Vpk[30][32][1])))+((Tstar[32][2]*
          Wpk[30][32][2])+((Tstar[32][0]*Wpk[30][32][0])+(Tstar[32][1]*
          Wpk[30][32][1])))));
        fs0[31] = (utau[31]-(((Fstar[32][2]*Vpk[31][32][2])+((Fstar[32][0]*
          Vpk[31][32][0])+(Fstar[32][1]*Vpk[31][32][1])))+((Tstar[32][2]*
          Wpk[31][32][2])+((Tstar[32][0]*Wpk[31][32][0])+(Tstar[32][1]*
          Wpk[31][32][1])))));
        fs0[32] = (utau[32]-(((Fstar[32][2]*Vpk[32][32][2])+((Fstar[32][0]*
          Vpk[32][32][0])+(Fstar[32][1]*Vpk[32][32][1])))+((pin[32][2]*
          Tstar[32][2])+((pin[32][0]*Tstar[32][0])+(pin[32][1]*Tstar[32][1])))))
          ;
        fs0flg = 1;
    }
/*
 Used 0.03 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  740 adds/subtracts/negates
                    699 multiplies
                      0 divides
                    123 assignments
*/
}

void sddomm(int routine)
{
    int dumroutine,errnum;
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        sddovpk();
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[0][11][2])+((Vpk[0][11][0]*
          Vpk[0][11][0])+(Vpk[0][11][1]*Vpk[0][11][1]))))+((11.15*((Vpk[0][3][2]
          *Vpk[0][3][2])+((Vpk[0][3][0]*Vpk[0][3][0])+(Vpk[0][3][1]*Vpk[0][3][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[0][8][2])+((Vpk[0][8][0]*Vpk[0][8][0])
          +(Vpk[0][8][1]*Vpk[0][8][1]))))));
        temp[1] = ((.205126*((Vpk[0][20][2]*Vpk[0][20][2])+((Vpk[0][20][0]*
          Vpk[0][20][0])+(Vpk[0][20][1]*Vpk[0][20][1]))))+((1.2*((Vpk[0][17][2]*
          Vpk[0][17][2])+((Vpk[0][17][0]*Vpk[0][17][0])+(Vpk[0][17][1]*
          Vpk[0][17][1]))))+((3.51*((Vpk[0][14][2]*Vpk[0][14][2])+((
          Vpk[0][14][0]*Vpk[0][14][0])+(Vpk[0][14][1]*Vpk[0][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][29][2]*Vpk[0][29][2])+((Vpk[0][29][0]*
          Vpk[0][29][0])+(Vpk[0][29][1]*Vpk[0][29][1]))))+((3.51*((Vpk[0][26][2]
          *Vpk[0][26][2])+((Vpk[0][26][0]*Vpk[0][26][0])+(Vpk[0][26][1]*
          Vpk[0][26][1]))))+((8.806*((Vpk[0][23][2]*Vpk[0][23][2])+((
          Vpk[0][23][0]*Vpk[0][23][0])+(Vpk[0][23][1]*Vpk[0][23][1]))))+temp[1])
          ));
        mm[0][0] = ((.205126*((Vpk[0][32][2]*Vpk[0][32][2])+((Vpk[0][32][0]*
          Vpk[0][32][0])+(Vpk[0][32][1]*Vpk[0][32][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[1][11][2])+((Vpk[0][11][0]*
          Vpk[1][11][0])+(Vpk[0][11][1]*Vpk[1][11][1]))))+((11.15*((Vpk[0][3][2]
          *Vpk[1][3][2])+((Vpk[0][3][0]*Vpk[1][3][0])+(Vpk[0][3][1]*Vpk[1][3][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[1][8][2])+((Vpk[0][8][0]*Vpk[1][8][0])
          +(Vpk[0][8][1]*Vpk[1][8][1]))))));
        temp[1] = ((.205126*((Vpk[0][20][2]*Vpk[1][20][2])+((Vpk[0][20][0]*
          Vpk[1][20][0])+(Vpk[0][20][1]*Vpk[1][20][1]))))+((1.2*((Vpk[0][17][2]*
          Vpk[1][17][2])+((Vpk[0][17][0]*Vpk[1][17][0])+(Vpk[0][17][1]*
          Vpk[1][17][1]))))+((3.51*((Vpk[0][14][2]*Vpk[1][14][2])+((
          Vpk[0][14][0]*Vpk[1][14][0])+(Vpk[0][14][1]*Vpk[1][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][29][2]*Vpk[1][29][2])+((Vpk[0][29][0]*
          Vpk[1][29][0])+(Vpk[0][29][1]*Vpk[1][29][1]))))+((3.51*((Vpk[0][26][2]
          *Vpk[1][26][2])+((Vpk[0][26][0]*Vpk[1][26][0])+(Vpk[0][26][1]*
          Vpk[1][26][1]))))+((8.806*((Vpk[0][23][2]*Vpk[1][23][2])+((
          Vpk[0][23][0]*Vpk[1][23][0])+(Vpk[0][23][1]*Vpk[1][23][1]))))+temp[1])
          ));
        mm[0][1] = ((.205126*((Vpk[0][32][2]*Vpk[1][32][2])+((Vpk[0][32][0]*
          Vpk[1][32][0])+(Vpk[0][32][1]*Vpk[1][32][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[2][11][2])+((Vpk[0][11][0]*
          Vpk[2][11][0])+(Vpk[0][11][1]*Vpk[2][11][1]))))+((11.15*((Vpk[0][3][2]
          *Vpk[2][3][2])+((Vpk[0][3][0]*Vpk[2][3][0])+(Vpk[0][3][1]*Vpk[2][3][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[2][8][2])+((Vpk[0][8][0]*Vpk[2][8][0])
          +(Vpk[0][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((.205126*((Vpk[0][20][2]*Vpk[2][20][2])+((Vpk[0][20][0]*
          Vpk[2][20][0])+(Vpk[0][20][1]*Vpk[2][20][1]))))+((1.2*((Vpk[0][17][2]*
          Vpk[2][17][2])+((Vpk[0][17][0]*Vpk[2][17][0])+(Vpk[0][17][1]*
          Vpk[2][17][1]))))+((3.51*((Vpk[0][14][2]*Vpk[2][14][2])+((
          Vpk[0][14][0]*Vpk[2][14][0])+(Vpk[0][14][1]*Vpk[2][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][29][2]*Vpk[2][29][2])+((Vpk[0][29][0]*
          Vpk[2][29][0])+(Vpk[0][29][1]*Vpk[2][29][1]))))+((3.51*((Vpk[0][26][2]
          *Vpk[2][26][2])+((Vpk[0][26][0]*Vpk[2][26][0])+(Vpk[0][26][1]*
          Vpk[2][26][1]))))+((8.806*((Vpk[0][23][2]*Vpk[2][23][2])+((
          Vpk[0][23][0]*Vpk[2][23][0])+(Vpk[0][23][1]*Vpk[2][23][1]))))+temp[1])
          ));
        mm[0][2] = ((.205126*((Vpk[0][32][2]*Vpk[2][32][2])+((Vpk[0][32][0]*
          Vpk[2][32][0])+(Vpk[0][32][1]*Vpk[2][32][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[0][14][2]*Vpk[3][14][2])+((Vpk[0][14][0]*
          Vpk[3][14][0])+(Vpk[0][14][1]*Vpk[3][14][1]))))+((8.806*((
          Vpk[0][11][2]*Vpk[3][11][2])+((Vpk[0][11][0]*Vpk[3][11][0])+(
          Vpk[0][11][1]*Vpk[3][11][1]))))+(32.413*((Vpk[0][8][2]*Vpk[3][8][2])+(
          (Vpk[0][8][0]*Vpk[3][8][0])+(Vpk[0][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((8.806*((Vpk[0][23][2]*Vpk[3][23][2])+((Vpk[0][23][0]*
          Vpk[3][23][0])+(Vpk[0][23][1]*Vpk[3][23][1]))))+((.205126*((
          Vpk[0][20][2]*Vpk[3][20][2])+((Vpk[0][20][0]*Vpk[3][20][0])+(
          Vpk[0][20][1]*Vpk[3][20][1]))))+((1.2*((Vpk[0][17][2]*Vpk[3][17][2])+(
          (Vpk[0][17][0]*Vpk[3][17][0])+(Vpk[0][17][1]*Vpk[3][17][1]))))+temp[0]
          )));
        mm[0][3] = ((.205126*((Vpk[0][32][2]*Vpk[3][32][2])+((Vpk[0][32][0]*
          Vpk[3][32][0])+(Vpk[0][32][1]*Vpk[3][32][1]))))+((1.2*((Vpk[0][29][2]*
          Vpk[3][29][2])+((Vpk[0][29][0]*Vpk[3][29][0])+(Vpk[0][29][1]*
          Vpk[3][29][1]))))+((3.51*((Vpk[0][26][2]*Vpk[3][26][2])+((
          Vpk[0][26][0]*Vpk[3][26][0])+(Vpk[0][26][1]*Vpk[3][26][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[0][17][2]*Vpk[4][17][2])+((Vpk[0][17][0]*
          Vpk[4][17][0])+(Vpk[0][17][1]*Vpk[4][17][1]))))+((3.51*((Vpk[0][14][2]
          *Vpk[4][14][2])+((Vpk[0][14][0]*Vpk[4][14][0])+(Vpk[0][14][1]*
          Vpk[4][14][1]))))+((8.806*((Vpk[0][11][2]*Vpk[4][11][2])+((
          Vpk[0][11][0]*Vpk[4][11][0])+(Vpk[0][11][1]*Vpk[4][11][1]))))+(
          10.3786426*((Vpk[0][8][2]*Wpk[4][8][0])-(Vpk[0][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[0][26][2]*Vpk[4][26][2])+((Vpk[0][26][0]*
          Vpk[4][26][0])+(Vpk[0][26][1]*Vpk[4][26][1]))))+((8.806*((
          Vpk[0][23][2]*Vpk[4][23][2])+((Vpk[0][23][0]*Vpk[4][23][0])+(
          Vpk[0][23][1]*Vpk[4][23][1]))))+((.205126*((Vpk[0][20][2]*
          Vpk[4][20][2])+((Vpk[0][20][0]*Vpk[4][20][0])+(Vpk[0][20][1]*
          Vpk[4][20][1]))))+temp[0])));
        mm[0][4] = ((.205126*((Vpk[0][32][2]*Vpk[4][32][2])+((Vpk[0][32][0]*
          Vpk[4][32][0])+(Vpk[0][32][1]*Vpk[4][32][1]))))+((1.2*((Vpk[0][29][2]*
          Vpk[4][29][2])+((Vpk[0][29][0]*Vpk[4][29][0])+(Vpk[0][29][1]*
          Vpk[4][29][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[0][14][2]*Vpk[5][14][2])+((Vpk[0][14][0]*
          Vpk[5][14][0])+(Vpk[0][14][1]*Vpk[5][14][1]))))+((8.806*((
          Vpk[0][11][2]*Vpk[5][11][2])+((Vpk[0][11][0]*Vpk[5][11][0])+(
          Vpk[0][11][1]*Vpk[5][11][1]))))+(32.413*((Vpk[0][8][2]*Vpk[5][8][2])+(
          (Vpk[0][8][0]*Vpk[5][8][0])+(Vpk[0][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((8.806*((Vpk[0][23][2]*Vpk[5][23][2])+((Vpk[0][23][0]*
          Vpk[5][23][0])+(Vpk[0][23][1]*Vpk[5][23][1]))))+((.205126*((
          Vpk[0][20][2]*Vpk[5][20][2])+((Vpk[0][20][0]*Vpk[5][20][0])+(
          Vpk[0][20][1]*Vpk[5][20][1]))))+((1.2*((Vpk[0][17][2]*Vpk[5][17][2])+(
          (Vpk[0][17][0]*Vpk[5][17][0])+(Vpk[0][17][1]*Vpk[5][17][1]))))+temp[0]
          )));
        mm[0][5] = ((.205126*((Vpk[0][32][2]*Vpk[5][32][2])+((Vpk[0][32][0]*
          Vpk[5][32][0])+(Vpk[0][32][1]*Vpk[5][32][1]))))+((1.2*((Vpk[0][29][2]*
          Vpk[5][29][2])+((Vpk[0][29][0]*Vpk[5][29][0])+(Vpk[0][29][1]*
          Vpk[5][29][1]))))+((3.51*((Vpk[0][26][2]*Vpk[5][26][2])+((
          Vpk[0][26][0]*Vpk[5][26][0])+(Vpk[0][26][1]*Vpk[5][26][1]))))+temp[1])
          ));
        mm[0][6] = (10.3786426*((Vpk[0][8][2]*Wpk[6][8][0])-(Vpk[0][8][0]*
          Wpk[6][8][2])));
        mm[0][7] = (10.3786426*((Vpk[0][8][2]*Wpk[7][8][0])-(Vpk[0][8][0]*
          Wpk[7][8][2])));
        mm[0][8] = (10.3786426*((pin[8][0]*Vpk[0][8][2])-(pin[8][2]*Vpk[0][8][0]
          )));
        temp[0] = ((1.2*((Vpk[0][17][2]*Vpk[9][17][2])+((Vpk[0][17][0]*
          Vpk[9][17][0])+(Vpk[0][17][1]*Vpk[9][17][1]))))+((3.51*((Vpk[0][14][2]
          *Vpk[9][14][2])+((Vpk[0][14][0]*Vpk[9][14][0])+(Vpk[0][14][1]*
          Vpk[9][14][1]))))+(8.806*((Vpk[0][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[0][11][0]*Wpk[9][11][2]))-(.002*(Vpk[0][11][1]*Wpk[9][11][2]))))))
          );
        mm[0][9] = ((.205126*((Vpk[0][20][2]*Vpk[9][20][2])+((Vpk[0][20][0]*
          Vpk[9][20][0])+(Vpk[0][20][1]*Vpk[9][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][17][2]*Vpk[10][17][2])+((Vpk[0][17][0]*
          Vpk[10][17][0])+(Vpk[0][17][1]*Vpk[10][17][1]))))+((3.51*((
          Vpk[0][14][2]*Vpk[10][14][2])+((Vpk[0][14][0]*Vpk[10][14][0])+(
          Vpk[0][14][1]*Vpk[10][14][1]))))+(8.806*((Vpk[0][11][2]*Vpk[10][11][2]
          )+((.1715*(Vpk[0][11][0]*Wpk[10][11][2]))-(.002*(Vpk[0][11][1]*
          Wpk[10][11][2])))))));
        mm[0][10] = ((.205126*((Vpk[0][20][2]*Vpk[10][20][2])+((Vpk[0][20][0]*
          Vpk[10][20][0])+(Vpk[0][20][1]*Vpk[10][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][17][2]*Vpk[11][17][2])+((Vpk[0][17][0]*
          Vpk[11][17][0])+(Vpk[0][17][1]*Vpk[11][17][1]))))+((3.51*((
          Vpk[0][14][2]*Vpk[11][14][2])+((Vpk[0][14][0]*Vpk[11][14][0])+(
          Vpk[0][14][1]*Vpk[11][14][1]))))+(8.806*((Vpk[0][11][2]*Vpk[11][11][2]
          )+((.1715*(pin[11][2]*Vpk[0][11][0]))-(.002*(pin[11][2]*Vpk[0][11][1])
          ))))));
        mm[0][11] = ((.205126*((Vpk[0][20][2]*Vpk[11][20][2])+((Vpk[0][20][0]*
          Vpk[11][20][0])+(Vpk[0][20][1]*Vpk[11][20][1]))))+temp[0]);
        mm[0][12] = ((.205126*((Vpk[0][20][2]*Vpk[12][20][2])+((Vpk[0][20][0]*
          Vpk[12][20][0])+(Vpk[0][20][1]*Vpk[12][20][1]))))+((.653562*((
          Vpk[0][14][0]*Wpk[12][14][2])-(Vpk[0][14][2]*Wpk[12][14][0])))+(1.2*((
          Vpk[0][17][2]*Vpk[12][17][2])+((Vpk[0][17][0]*Vpk[12][17][0])+(
          Vpk[0][17][1]*Vpk[12][17][1]))))));
        mm[0][13] = ((.205126*((Vpk[0][20][2]*Vpk[13][20][2])+((Vpk[0][20][0]*
          Vpk[13][20][0])+(Vpk[0][20][1]*Vpk[13][20][1]))))+((.653562*((
          Vpk[0][14][0]*Wpk[13][14][2])-(Vpk[0][14][2]*Wpk[13][14][0])))+(1.2*((
          Vpk[0][17][2]*Vpk[13][17][2])+((Vpk[0][17][0]*Vpk[13][17][0])+(
          Vpk[0][17][1]*Vpk[13][17][1]))))));
        mm[0][14] = ((.205126*((Vpk[0][20][2]*Vpk[14][20][2])+((Vpk[0][20][0]*
          Vpk[14][20][0])+(Vpk[0][20][1]*Vpk[14][20][1]))))+((.653562*((
          pin[14][2]*Vpk[0][14][0])-(pin[14][0]*Vpk[0][14][2])))+(1.2*((
          Vpk[0][17][2]*Vpk[14][17][2])+((Vpk[0][17][0]*Vpk[14][17][0])+(
          Vpk[0][17][1]*Vpk[14][17][1]))))));
        mm[0][15] = ((.205126*((Vpk[0][20][2]*Vpk[15][20][2])+((Vpk[0][20][0]*
          Vpk[15][20][0])+(Vpk[0][20][1]*Vpk[15][20][1]))))+(1.2*((Vpk[0][17][2]
          *Vpk[15][17][2])+((Vpk[0][17][0]*Vpk[15][17][0])+(Vpk[0][17][1]*
          Vpk[15][17][1])))));
        mm[0][16] = ((.205126*((Vpk[0][20][2]*Vpk[16][20][2])+((Vpk[0][20][0]*
          Vpk[16][20][0])+(Vpk[0][20][1]*Vpk[16][20][1]))))+(1.2*((Vpk[0][17][2]
          *Vpk[16][17][2])+((Vpk[0][17][0]*Vpk[16][17][0])+(Vpk[0][17][1]*
          Vpk[16][17][1])))));
        mm[0][17] = ((.205126*((Vpk[0][20][2]*Vpk[17][20][2])+((Vpk[0][20][0]*
          Vpk[17][20][0])+(Vpk[0][20][1]*Vpk[17][20][1]))))+(1.2*((Vpk[0][17][2]
          *Vpk[17][17][2])+((Vpk[0][17][0]*Vpk[17][17][0])+(Vpk[0][17][1]*
          Vpk[17][17][1])))));
        mm[0][18] = (.205126*((Vpk[0][20][2]*Vpk[18][20][2])+((Vpk[0][20][0]*
          Vpk[18][20][0])+(Vpk[0][20][1]*Vpk[18][20][1]))));
        mm[0][19] = (.205126*((Vpk[0][20][2]*Vpk[19][20][2])+((Vpk[0][20][0]*
          Vpk[19][20][0])+(Vpk[0][20][1]*Vpk[19][20][1]))));
        mm[0][20] = (.205126*((Vpk[0][20][2]*Vpk[20][20][2])+((Vpk[0][20][0]*
          Vpk[20][20][0])+(Vpk[0][20][1]*Vpk[20][20][1]))));
        temp[0] = ((1.2*((Vpk[0][29][2]*Vpk[21][29][2])+((Vpk[0][29][0]*
          Vpk[21][29][0])+(Vpk[0][29][1]*Vpk[21][29][1]))))+((3.51*((
          Vpk[0][26][2]*Vpk[21][26][2])+((Vpk[0][26][0]*Vpk[21][26][0])+(
          Vpk[0][26][1]*Vpk[21][26][1]))))+(8.806*((Vpk[0][23][2]*Vpk[21][23][2]
          )+((.1715*(Vpk[0][23][0]*Wpk[21][23][2]))-(.002*(Vpk[0][23][1]*
          Wpk[21][23][2])))))));
        mm[0][21] = ((.205126*((Vpk[0][32][2]*Vpk[21][32][2])+((Vpk[0][32][0]*
          Vpk[21][32][0])+(Vpk[0][32][1]*Vpk[21][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][29][2]*Vpk[22][29][2])+((Vpk[0][29][0]*
          Vpk[22][29][0])+(Vpk[0][29][1]*Vpk[22][29][1]))))+((3.51*((
          Vpk[0][26][2]*Vpk[22][26][2])+((Vpk[0][26][0]*Vpk[22][26][0])+(
          Vpk[0][26][1]*Vpk[22][26][1]))))+(8.806*((Vpk[0][23][2]*Vpk[22][23][2]
          )+((.1715*(Vpk[0][23][0]*Wpk[22][23][2]))-(.002*(Vpk[0][23][1]*
          Wpk[22][23][2])))))));
        mm[0][22] = ((.205126*((Vpk[0][32][2]*Vpk[22][32][2])+((Vpk[0][32][0]*
          Vpk[22][32][0])+(Vpk[0][32][1]*Vpk[22][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][29][2]*Vpk[23][29][2])+((Vpk[0][29][0]*
          Vpk[23][29][0])+(Vpk[0][29][1]*Vpk[23][29][1]))))+((3.51*((
          Vpk[0][26][2]*Vpk[23][26][2])+((Vpk[0][26][0]*Vpk[23][26][0])+(
          Vpk[0][26][1]*Vpk[23][26][1]))))+(8.806*((Vpk[0][23][2]*Vpk[23][23][2]
          )+((.1715*(pin[23][2]*Vpk[0][23][0]))-(.002*(pin[23][2]*Vpk[0][23][1])
          ))))));
        mm[0][23] = ((.205126*((Vpk[0][32][2]*Vpk[23][32][2])+((Vpk[0][32][0]*
          Vpk[23][32][0])+(Vpk[0][32][1]*Vpk[23][32][1]))))+temp[0]);
        mm[0][24] = ((.205126*((Vpk[0][32][2]*Vpk[24][32][2])+((Vpk[0][32][0]*
          Vpk[24][32][0])+(Vpk[0][32][1]*Vpk[24][32][1]))))+((.653562*((
          Vpk[0][26][0]*Wpk[24][26][2])-(Vpk[0][26][2]*Wpk[24][26][0])))+(1.2*((
          Vpk[0][29][2]*Vpk[24][29][2])+((Vpk[0][29][0]*Vpk[24][29][0])+(
          Vpk[0][29][1]*Vpk[24][29][1]))))));
        mm[0][25] = ((.205126*((Vpk[0][32][2]*Vpk[25][32][2])+((Vpk[0][32][0]*
          Vpk[25][32][0])+(Vpk[0][32][1]*Vpk[25][32][1]))))+((.653562*((
          Vpk[0][26][0]*Wpk[25][26][2])-(Vpk[0][26][2]*Wpk[25][26][0])))+(1.2*((
          Vpk[0][29][2]*Vpk[25][29][2])+((Vpk[0][29][0]*Vpk[25][29][0])+(
          Vpk[0][29][1]*Vpk[25][29][1]))))));
        mm[0][26] = ((.205126*((Vpk[0][32][2]*Vpk[26][32][2])+((Vpk[0][32][0]*
          Vpk[26][32][0])+(Vpk[0][32][1]*Vpk[26][32][1]))))+((.653562*((
          pin[26][2]*Vpk[0][26][0])-(pin[26][0]*Vpk[0][26][2])))+(1.2*((
          Vpk[0][29][2]*Vpk[26][29][2])+((Vpk[0][29][0]*Vpk[26][29][0])+(
          Vpk[0][29][1]*Vpk[26][29][1]))))));
        mm[0][27] = ((.205126*((Vpk[0][32][2]*Vpk[27][32][2])+((Vpk[0][32][0]*
          Vpk[27][32][0])+(Vpk[0][32][1]*Vpk[27][32][1]))))+(1.2*((Vpk[0][29][2]
          *Vpk[27][29][2])+((Vpk[0][29][0]*Vpk[27][29][0])+(Vpk[0][29][1]*
          Vpk[27][29][1])))));
        mm[0][28] = ((.205126*((Vpk[0][32][2]*Vpk[28][32][2])+((Vpk[0][32][0]*
          Vpk[28][32][0])+(Vpk[0][32][1]*Vpk[28][32][1]))))+(1.2*((Vpk[0][29][2]
          *Vpk[28][29][2])+((Vpk[0][29][0]*Vpk[28][29][0])+(Vpk[0][29][1]*
          Vpk[28][29][1])))));
        mm[0][29] = ((.205126*((Vpk[0][32][2]*Vpk[29][32][2])+((Vpk[0][32][0]*
          Vpk[29][32][0])+(Vpk[0][32][1]*Vpk[29][32][1]))))+(1.2*((Vpk[0][29][2]
          *Vpk[29][29][2])+((Vpk[0][29][0]*Vpk[29][29][0])+(Vpk[0][29][1]*
          Vpk[29][29][1])))));
        mm[0][30] = (.205126*((Vpk[0][32][2]*Vpk[30][32][2])+((Vpk[0][32][0]*
          Vpk[30][32][0])+(Vpk[0][32][1]*Vpk[30][32][1]))));
        mm[0][31] = (.205126*((Vpk[0][32][2]*Vpk[31][32][2])+((Vpk[0][32][0]*
          Vpk[31][32][0])+(Vpk[0][32][1]*Vpk[31][32][1]))));
        mm[0][32] = (.205126*((Vpk[0][32][2]*Vpk[32][32][2])+((Vpk[0][32][0]*
          Vpk[32][32][0])+(Vpk[0][32][1]*Vpk[32][32][1]))));
        temp[0] = ((8.806*((Vpk[1][11][2]*Vpk[1][11][2])+((Vpk[1][11][0]*
          Vpk[1][11][0])+(Vpk[1][11][1]*Vpk[1][11][1]))))+((11.15*((Vpk[1][3][2]
          *Vpk[1][3][2])+((Vpk[1][3][0]*Vpk[1][3][0])+(Vpk[1][3][1]*Vpk[1][3][1]
          ))))+(32.413*((Vpk[1][8][2]*Vpk[1][8][2])+((Vpk[1][8][0]*Vpk[1][8][0])
          +(Vpk[1][8][1]*Vpk[1][8][1]))))));
        temp[1] = ((.205126*((Vpk[1][20][2]*Vpk[1][20][2])+((Vpk[1][20][0]*
          Vpk[1][20][0])+(Vpk[1][20][1]*Vpk[1][20][1]))))+((1.2*((Vpk[1][17][2]*
          Vpk[1][17][2])+((Vpk[1][17][0]*Vpk[1][17][0])+(Vpk[1][17][1]*
          Vpk[1][17][1]))))+((3.51*((Vpk[1][14][2]*Vpk[1][14][2])+((
          Vpk[1][14][0]*Vpk[1][14][0])+(Vpk[1][14][1]*Vpk[1][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[1][29][2]*Vpk[1][29][2])+((Vpk[1][29][0]*
          Vpk[1][29][0])+(Vpk[1][29][1]*Vpk[1][29][1]))))+((3.51*((Vpk[1][26][2]
          *Vpk[1][26][2])+((Vpk[1][26][0]*Vpk[1][26][0])+(Vpk[1][26][1]*
          Vpk[1][26][1]))))+((8.806*((Vpk[1][23][2]*Vpk[1][23][2])+((
          Vpk[1][23][0]*Vpk[1][23][0])+(Vpk[1][23][1]*Vpk[1][23][1]))))+temp[1])
          ));
        mm[1][1] = ((.205126*((Vpk[1][32][2]*Vpk[1][32][2])+((Vpk[1][32][0]*
          Vpk[1][32][0])+(Vpk[1][32][1]*Vpk[1][32][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[1][11][2]*Vpk[2][11][2])+((Vpk[1][11][0]*
          Vpk[2][11][0])+(Vpk[1][11][1]*Vpk[2][11][1]))))+((11.15*((Vpk[1][3][2]
          *Vpk[2][3][2])+((Vpk[1][3][0]*Vpk[2][3][0])+(Vpk[1][3][1]*Vpk[2][3][1]
          ))))+(32.413*((Vpk[1][8][2]*Vpk[2][8][2])+((Vpk[1][8][0]*Vpk[2][8][0])
          +(Vpk[1][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((.205126*((Vpk[1][20][2]*Vpk[2][20][2])+((Vpk[1][20][0]*
          Vpk[2][20][0])+(Vpk[1][20][1]*Vpk[2][20][1]))))+((1.2*((Vpk[1][17][2]*
          Vpk[2][17][2])+((Vpk[1][17][0]*Vpk[2][17][0])+(Vpk[1][17][1]*
          Vpk[2][17][1]))))+((3.51*((Vpk[1][14][2]*Vpk[2][14][2])+((
          Vpk[1][14][0]*Vpk[2][14][0])+(Vpk[1][14][1]*Vpk[2][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[1][29][2]*Vpk[2][29][2])+((Vpk[1][29][0]*
          Vpk[2][29][0])+(Vpk[1][29][1]*Vpk[2][29][1]))))+((3.51*((Vpk[1][26][2]
          *Vpk[2][26][2])+((Vpk[1][26][0]*Vpk[2][26][0])+(Vpk[1][26][1]*
          Vpk[2][26][1]))))+((8.806*((Vpk[1][23][2]*Vpk[2][23][2])+((
          Vpk[1][23][0]*Vpk[2][23][0])+(Vpk[1][23][1]*Vpk[2][23][1]))))+temp[1])
          ));
        mm[1][2] = ((.205126*((Vpk[1][32][2]*Vpk[2][32][2])+((Vpk[1][32][0]*
          Vpk[2][32][0])+(Vpk[1][32][1]*Vpk[2][32][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[1][14][2]*Vpk[3][14][2])+((Vpk[1][14][0]*
          Vpk[3][14][0])+(Vpk[1][14][1]*Vpk[3][14][1]))))+((8.806*((
          Vpk[1][11][2]*Vpk[3][11][2])+((Vpk[1][11][0]*Vpk[3][11][0])+(
          Vpk[1][11][1]*Vpk[3][11][1]))))+(32.413*((Vpk[1][8][2]*Vpk[3][8][2])+(
          (Vpk[1][8][0]*Vpk[3][8][0])+(Vpk[1][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((8.806*((Vpk[1][23][2]*Vpk[3][23][2])+((Vpk[1][23][0]*
          Vpk[3][23][0])+(Vpk[1][23][1]*Vpk[3][23][1]))))+((.205126*((
          Vpk[1][20][2]*Vpk[3][20][2])+((Vpk[1][20][0]*Vpk[3][20][0])+(
          Vpk[1][20][1]*Vpk[3][20][1]))))+((1.2*((Vpk[1][17][2]*Vpk[3][17][2])+(
          (Vpk[1][17][0]*Vpk[3][17][0])+(Vpk[1][17][1]*Vpk[3][17][1]))))+temp[0]
          )));
        mm[1][3] = ((.205126*((Vpk[1][32][2]*Vpk[3][32][2])+((Vpk[1][32][0]*
          Vpk[3][32][0])+(Vpk[1][32][1]*Vpk[3][32][1]))))+((1.2*((Vpk[1][29][2]*
          Vpk[3][29][2])+((Vpk[1][29][0]*Vpk[3][29][0])+(Vpk[1][29][1]*
          Vpk[3][29][1]))))+((3.51*((Vpk[1][26][2]*Vpk[3][26][2])+((
          Vpk[1][26][0]*Vpk[3][26][0])+(Vpk[1][26][1]*Vpk[3][26][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[1][17][2]*Vpk[4][17][2])+((Vpk[1][17][0]*
          Vpk[4][17][0])+(Vpk[1][17][1]*Vpk[4][17][1]))))+((3.51*((Vpk[1][14][2]
          *Vpk[4][14][2])+((Vpk[1][14][0]*Vpk[4][14][0])+(Vpk[1][14][1]*
          Vpk[4][14][1]))))+((8.806*((Vpk[1][11][2]*Vpk[4][11][2])+((
          Vpk[1][11][0]*Vpk[4][11][0])+(Vpk[1][11][1]*Vpk[4][11][1]))))+(
          10.3786426*((Vpk[1][8][2]*Wpk[4][8][0])-(Vpk[1][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[1][26][2]*Vpk[4][26][2])+((Vpk[1][26][0]*
          Vpk[4][26][0])+(Vpk[1][26][1]*Vpk[4][26][1]))))+((8.806*((
          Vpk[1][23][2]*Vpk[4][23][2])+((Vpk[1][23][0]*Vpk[4][23][0])+(
          Vpk[1][23][1]*Vpk[4][23][1]))))+((.205126*((Vpk[1][20][2]*
          Vpk[4][20][2])+((Vpk[1][20][0]*Vpk[4][20][0])+(Vpk[1][20][1]*
          Vpk[4][20][1]))))+temp[0])));
        mm[1][4] = ((.205126*((Vpk[1][32][2]*Vpk[4][32][2])+((Vpk[1][32][0]*
          Vpk[4][32][0])+(Vpk[1][32][1]*Vpk[4][32][1]))))+((1.2*((Vpk[1][29][2]*
          Vpk[4][29][2])+((Vpk[1][29][0]*Vpk[4][29][0])+(Vpk[1][29][1]*
          Vpk[4][29][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[1][14][2]*Vpk[5][14][2])+((Vpk[1][14][0]*
          Vpk[5][14][0])+(Vpk[1][14][1]*Vpk[5][14][1]))))+((8.806*((
          Vpk[1][11][2]*Vpk[5][11][2])+((Vpk[1][11][0]*Vpk[5][11][0])+(
          Vpk[1][11][1]*Vpk[5][11][1]))))+(32.413*((Vpk[1][8][2]*Vpk[5][8][2])+(
          (Vpk[1][8][0]*Vpk[5][8][0])+(Vpk[1][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((8.806*((Vpk[1][23][2]*Vpk[5][23][2])+((Vpk[1][23][0]*
          Vpk[5][23][0])+(Vpk[1][23][1]*Vpk[5][23][1]))))+((.205126*((
          Vpk[1][20][2]*Vpk[5][20][2])+((Vpk[1][20][0]*Vpk[5][20][0])+(
          Vpk[1][20][1]*Vpk[5][20][1]))))+((1.2*((Vpk[1][17][2]*Vpk[5][17][2])+(
          (Vpk[1][17][0]*Vpk[5][17][0])+(Vpk[1][17][1]*Vpk[5][17][1]))))+temp[0]
          )));
        mm[1][5] = ((.205126*((Vpk[1][32][2]*Vpk[5][32][2])+((Vpk[1][32][0]*
          Vpk[5][32][0])+(Vpk[1][32][1]*Vpk[5][32][1]))))+((1.2*((Vpk[1][29][2]*
          Vpk[5][29][2])+((Vpk[1][29][0]*Vpk[5][29][0])+(Vpk[1][29][1]*
          Vpk[5][29][1]))))+((3.51*((Vpk[1][26][2]*Vpk[5][26][2])+((
          Vpk[1][26][0]*Vpk[5][26][0])+(Vpk[1][26][1]*Vpk[5][26][1]))))+temp[1])
          ));
        mm[1][6] = (10.3786426*((Vpk[1][8][2]*Wpk[6][8][0])-(Vpk[1][8][0]*
          Wpk[6][8][2])));
        mm[1][7] = (10.3786426*((Vpk[1][8][2]*Wpk[7][8][0])-(Vpk[1][8][0]*
          Wpk[7][8][2])));
        mm[1][8] = (10.3786426*((pin[8][0]*Vpk[1][8][2])-(pin[8][2]*Vpk[1][8][0]
          )));
        temp[0] = ((1.2*((Vpk[1][17][2]*Vpk[9][17][2])+((Vpk[1][17][0]*
          Vpk[9][17][0])+(Vpk[1][17][1]*Vpk[9][17][1]))))+((3.51*((Vpk[1][14][2]
          *Vpk[9][14][2])+((Vpk[1][14][0]*Vpk[9][14][0])+(Vpk[1][14][1]*
          Vpk[9][14][1]))))+(8.806*((Vpk[1][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[1][11][0]*Wpk[9][11][2]))-(.002*(Vpk[1][11][1]*Wpk[9][11][2]))))))
          );
        mm[1][9] = ((.205126*((Vpk[1][20][2]*Vpk[9][20][2])+((Vpk[1][20][0]*
          Vpk[9][20][0])+(Vpk[1][20][1]*Vpk[9][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][17][2]*Vpk[10][17][2])+((Vpk[1][17][0]*
          Vpk[10][17][0])+(Vpk[1][17][1]*Vpk[10][17][1]))))+((3.51*((
          Vpk[1][14][2]*Vpk[10][14][2])+((Vpk[1][14][0]*Vpk[10][14][0])+(
          Vpk[1][14][1]*Vpk[10][14][1]))))+(8.806*((Vpk[1][11][2]*Vpk[10][11][2]
          )+((.1715*(Vpk[1][11][0]*Wpk[10][11][2]))-(.002*(Vpk[1][11][1]*
          Wpk[10][11][2])))))));
        mm[1][10] = ((.205126*((Vpk[1][20][2]*Vpk[10][20][2])+((Vpk[1][20][0]*
          Vpk[10][20][0])+(Vpk[1][20][1]*Vpk[10][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][17][2]*Vpk[11][17][2])+((Vpk[1][17][0]*
          Vpk[11][17][0])+(Vpk[1][17][1]*Vpk[11][17][1]))))+((3.51*((
          Vpk[1][14][2]*Vpk[11][14][2])+((Vpk[1][14][0]*Vpk[11][14][0])+(
          Vpk[1][14][1]*Vpk[11][14][1]))))+(8.806*((Vpk[1][11][2]*Vpk[11][11][2]
          )+((.1715*(pin[11][2]*Vpk[1][11][0]))-(.002*(pin[11][2]*Vpk[1][11][1])
          ))))));
        mm[1][11] = ((.205126*((Vpk[1][20][2]*Vpk[11][20][2])+((Vpk[1][20][0]*
          Vpk[11][20][0])+(Vpk[1][20][1]*Vpk[11][20][1]))))+temp[0]);
        mm[1][12] = ((.205126*((Vpk[1][20][2]*Vpk[12][20][2])+((Vpk[1][20][0]*
          Vpk[12][20][0])+(Vpk[1][20][1]*Vpk[12][20][1]))))+((.653562*((
          Vpk[1][14][0]*Wpk[12][14][2])-(Vpk[1][14][2]*Wpk[12][14][0])))+(1.2*((
          Vpk[1][17][2]*Vpk[12][17][2])+((Vpk[1][17][0]*Vpk[12][17][0])+(
          Vpk[1][17][1]*Vpk[12][17][1]))))));
        mm[1][13] = ((.205126*((Vpk[1][20][2]*Vpk[13][20][2])+((Vpk[1][20][0]*
          Vpk[13][20][0])+(Vpk[1][20][1]*Vpk[13][20][1]))))+((.653562*((
          Vpk[1][14][0]*Wpk[13][14][2])-(Vpk[1][14][2]*Wpk[13][14][0])))+(1.2*((
          Vpk[1][17][2]*Vpk[13][17][2])+((Vpk[1][17][0]*Vpk[13][17][0])+(
          Vpk[1][17][1]*Vpk[13][17][1]))))));
        mm[1][14] = ((.205126*((Vpk[1][20][2]*Vpk[14][20][2])+((Vpk[1][20][0]*
          Vpk[14][20][0])+(Vpk[1][20][1]*Vpk[14][20][1]))))+((.653562*((
          pin[14][2]*Vpk[1][14][0])-(pin[14][0]*Vpk[1][14][2])))+(1.2*((
          Vpk[1][17][2]*Vpk[14][17][2])+((Vpk[1][17][0]*Vpk[14][17][0])+(
          Vpk[1][17][1]*Vpk[14][17][1]))))));
        mm[1][15] = ((.205126*((Vpk[1][20][2]*Vpk[15][20][2])+((Vpk[1][20][0]*
          Vpk[15][20][0])+(Vpk[1][20][1]*Vpk[15][20][1]))))+(1.2*((Vpk[1][17][2]
          *Vpk[15][17][2])+((Vpk[1][17][0]*Vpk[15][17][0])+(Vpk[1][17][1]*
          Vpk[15][17][1])))));
        mm[1][16] = ((.205126*((Vpk[1][20][2]*Vpk[16][20][2])+((Vpk[1][20][0]*
          Vpk[16][20][0])+(Vpk[1][20][1]*Vpk[16][20][1]))))+(1.2*((Vpk[1][17][2]
          *Vpk[16][17][2])+((Vpk[1][17][0]*Vpk[16][17][0])+(Vpk[1][17][1]*
          Vpk[16][17][1])))));
        mm[1][17] = ((.205126*((Vpk[1][20][2]*Vpk[17][20][2])+((Vpk[1][20][0]*
          Vpk[17][20][0])+(Vpk[1][20][1]*Vpk[17][20][1]))))+(1.2*((Vpk[1][17][2]
          *Vpk[17][17][2])+((Vpk[1][17][0]*Vpk[17][17][0])+(Vpk[1][17][1]*
          Vpk[17][17][1])))));
        mm[1][18] = (.205126*((Vpk[1][20][2]*Vpk[18][20][2])+((Vpk[1][20][0]*
          Vpk[18][20][0])+(Vpk[1][20][1]*Vpk[18][20][1]))));
        mm[1][19] = (.205126*((Vpk[1][20][2]*Vpk[19][20][2])+((Vpk[1][20][0]*
          Vpk[19][20][0])+(Vpk[1][20][1]*Vpk[19][20][1]))));
        mm[1][20] = (.205126*((Vpk[1][20][2]*Vpk[20][20][2])+((Vpk[1][20][0]*
          Vpk[20][20][0])+(Vpk[1][20][1]*Vpk[20][20][1]))));
        temp[0] = ((1.2*((Vpk[1][29][2]*Vpk[21][29][2])+((Vpk[1][29][0]*
          Vpk[21][29][0])+(Vpk[1][29][1]*Vpk[21][29][1]))))+((3.51*((
          Vpk[1][26][2]*Vpk[21][26][2])+((Vpk[1][26][0]*Vpk[21][26][0])+(
          Vpk[1][26][1]*Vpk[21][26][1]))))+(8.806*((Vpk[1][23][2]*Vpk[21][23][2]
          )+((.1715*(Vpk[1][23][0]*Wpk[21][23][2]))-(.002*(Vpk[1][23][1]*
          Wpk[21][23][2])))))));
        mm[1][21] = ((.205126*((Vpk[1][32][2]*Vpk[21][32][2])+((Vpk[1][32][0]*
          Vpk[21][32][0])+(Vpk[1][32][1]*Vpk[21][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][29][2]*Vpk[22][29][2])+((Vpk[1][29][0]*
          Vpk[22][29][0])+(Vpk[1][29][1]*Vpk[22][29][1]))))+((3.51*((
          Vpk[1][26][2]*Vpk[22][26][2])+((Vpk[1][26][0]*Vpk[22][26][0])+(
          Vpk[1][26][1]*Vpk[22][26][1]))))+(8.806*((Vpk[1][23][2]*Vpk[22][23][2]
          )+((.1715*(Vpk[1][23][0]*Wpk[22][23][2]))-(.002*(Vpk[1][23][1]*
          Wpk[22][23][2])))))));
        mm[1][22] = ((.205126*((Vpk[1][32][2]*Vpk[22][32][2])+((Vpk[1][32][0]*
          Vpk[22][32][0])+(Vpk[1][32][1]*Vpk[22][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][29][2]*Vpk[23][29][2])+((Vpk[1][29][0]*
          Vpk[23][29][0])+(Vpk[1][29][1]*Vpk[23][29][1]))))+((3.51*((
          Vpk[1][26][2]*Vpk[23][26][2])+((Vpk[1][26][0]*Vpk[23][26][0])+(
          Vpk[1][26][1]*Vpk[23][26][1]))))+(8.806*((Vpk[1][23][2]*Vpk[23][23][2]
          )+((.1715*(pin[23][2]*Vpk[1][23][0]))-(.002*(pin[23][2]*Vpk[1][23][1])
          ))))));
        mm[1][23] = ((.205126*((Vpk[1][32][2]*Vpk[23][32][2])+((Vpk[1][32][0]*
          Vpk[23][32][0])+(Vpk[1][32][1]*Vpk[23][32][1]))))+temp[0]);
        mm[1][24] = ((.205126*((Vpk[1][32][2]*Vpk[24][32][2])+((Vpk[1][32][0]*
          Vpk[24][32][0])+(Vpk[1][32][1]*Vpk[24][32][1]))))+((.653562*((
          Vpk[1][26][0]*Wpk[24][26][2])-(Vpk[1][26][2]*Wpk[24][26][0])))+(1.2*((
          Vpk[1][29][2]*Vpk[24][29][2])+((Vpk[1][29][0]*Vpk[24][29][0])+(
          Vpk[1][29][1]*Vpk[24][29][1]))))));
        mm[1][25] = ((.205126*((Vpk[1][32][2]*Vpk[25][32][2])+((Vpk[1][32][0]*
          Vpk[25][32][0])+(Vpk[1][32][1]*Vpk[25][32][1]))))+((.653562*((
          Vpk[1][26][0]*Wpk[25][26][2])-(Vpk[1][26][2]*Wpk[25][26][0])))+(1.2*((
          Vpk[1][29][2]*Vpk[25][29][2])+((Vpk[1][29][0]*Vpk[25][29][0])+(
          Vpk[1][29][1]*Vpk[25][29][1]))))));
        mm[1][26] = ((.205126*((Vpk[1][32][2]*Vpk[26][32][2])+((Vpk[1][32][0]*
          Vpk[26][32][0])+(Vpk[1][32][1]*Vpk[26][32][1]))))+((.653562*((
          pin[26][2]*Vpk[1][26][0])-(pin[26][0]*Vpk[1][26][2])))+(1.2*((
          Vpk[1][29][2]*Vpk[26][29][2])+((Vpk[1][29][0]*Vpk[26][29][0])+(
          Vpk[1][29][1]*Vpk[26][29][1]))))));
        mm[1][27] = ((.205126*((Vpk[1][32][2]*Vpk[27][32][2])+((Vpk[1][32][0]*
          Vpk[27][32][0])+(Vpk[1][32][1]*Vpk[27][32][1]))))+(1.2*((Vpk[1][29][2]
          *Vpk[27][29][2])+((Vpk[1][29][0]*Vpk[27][29][0])+(Vpk[1][29][1]*
          Vpk[27][29][1])))));
        mm[1][28] = ((.205126*((Vpk[1][32][2]*Vpk[28][32][2])+((Vpk[1][32][0]*
          Vpk[28][32][0])+(Vpk[1][32][1]*Vpk[28][32][1]))))+(1.2*((Vpk[1][29][2]
          *Vpk[28][29][2])+((Vpk[1][29][0]*Vpk[28][29][0])+(Vpk[1][29][1]*
          Vpk[28][29][1])))));
        mm[1][29] = ((.205126*((Vpk[1][32][2]*Vpk[29][32][2])+((Vpk[1][32][0]*
          Vpk[29][32][0])+(Vpk[1][32][1]*Vpk[29][32][1]))))+(1.2*((Vpk[1][29][2]
          *Vpk[29][29][2])+((Vpk[1][29][0]*Vpk[29][29][0])+(Vpk[1][29][1]*
          Vpk[29][29][1])))));
        mm[1][30] = (.205126*((Vpk[1][32][2]*Vpk[30][32][2])+((Vpk[1][32][0]*
          Vpk[30][32][0])+(Vpk[1][32][1]*Vpk[30][32][1]))));
        mm[1][31] = (.205126*((Vpk[1][32][2]*Vpk[31][32][2])+((Vpk[1][32][0]*
          Vpk[31][32][0])+(Vpk[1][32][1]*Vpk[31][32][1]))));
        mm[1][32] = (.205126*((Vpk[1][32][2]*Vpk[32][32][2])+((Vpk[1][32][0]*
          Vpk[32][32][0])+(Vpk[1][32][1]*Vpk[32][32][1]))));
        temp[0] = ((8.806*((Vpk[2][11][2]*Vpk[2][11][2])+((Vpk[2][11][0]*
          Vpk[2][11][0])+(Vpk[2][11][1]*Vpk[2][11][1]))))+((11.15*((Vpk[2][3][2]
          *Vpk[2][3][2])+((Vpk[2][3][0]*Vpk[2][3][0])+(Vpk[2][3][1]*Vpk[2][3][1]
          ))))+(32.413*((Vpk[2][8][2]*Vpk[2][8][2])+((Vpk[2][8][0]*Vpk[2][8][0])
          +(Vpk[2][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((.205126*((Vpk[2][20][2]*Vpk[2][20][2])+((Vpk[2][20][0]*
          Vpk[2][20][0])+(Vpk[2][20][1]*Vpk[2][20][1]))))+((1.2*((Vpk[2][17][2]*
          Vpk[2][17][2])+((Vpk[2][17][0]*Vpk[2][17][0])+(Vpk[2][17][1]*
          Vpk[2][17][1]))))+((3.51*((Vpk[2][14][2]*Vpk[2][14][2])+((
          Vpk[2][14][0]*Vpk[2][14][0])+(Vpk[2][14][1]*Vpk[2][14][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[2][29][2]*Vpk[2][29][2])+((Vpk[2][29][0]*
          Vpk[2][29][0])+(Vpk[2][29][1]*Vpk[2][29][1]))))+((3.51*((Vpk[2][26][2]
          *Vpk[2][26][2])+((Vpk[2][26][0]*Vpk[2][26][0])+(Vpk[2][26][1]*
          Vpk[2][26][1]))))+((8.806*((Vpk[2][23][2]*Vpk[2][23][2])+((
          Vpk[2][23][0]*Vpk[2][23][0])+(Vpk[2][23][1]*Vpk[2][23][1]))))+temp[1])
          ));
        mm[2][2] = ((.205126*((Vpk[2][32][2]*Vpk[2][32][2])+((Vpk[2][32][0]*
          Vpk[2][32][0])+(Vpk[2][32][1]*Vpk[2][32][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[2][14][2]*Vpk[3][14][2])+((Vpk[2][14][0]*
          Vpk[3][14][0])+(Vpk[2][14][1]*Vpk[3][14][1]))))+((8.806*((
          Vpk[2][11][2]*Vpk[3][11][2])+((Vpk[2][11][0]*Vpk[3][11][0])+(
          Vpk[2][11][1]*Vpk[3][11][1]))))+(32.413*((Vpk[2][8][2]*Vpk[3][8][2])+(
          (Vpk[2][8][0]*Vpk[3][8][0])+(Vpk[2][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((8.806*((Vpk[2][23][2]*Vpk[3][23][2])+((Vpk[2][23][0]*
          Vpk[3][23][0])+(Vpk[2][23][1]*Vpk[3][23][1]))))+((.205126*((
          Vpk[2][20][2]*Vpk[3][20][2])+((Vpk[2][20][0]*Vpk[3][20][0])+(
          Vpk[2][20][1]*Vpk[3][20][1]))))+((1.2*((Vpk[2][17][2]*Vpk[3][17][2])+(
          (Vpk[2][17][0]*Vpk[3][17][0])+(Vpk[2][17][1]*Vpk[3][17][1]))))+temp[0]
          )));
        mm[2][3] = ((.205126*((Vpk[2][32][2]*Vpk[3][32][2])+((Vpk[2][32][0]*
          Vpk[3][32][0])+(Vpk[2][32][1]*Vpk[3][32][1]))))+((1.2*((Vpk[2][29][2]*
          Vpk[3][29][2])+((Vpk[2][29][0]*Vpk[3][29][0])+(Vpk[2][29][1]*
          Vpk[3][29][1]))))+((3.51*((Vpk[2][26][2]*Vpk[3][26][2])+((
          Vpk[2][26][0]*Vpk[3][26][0])+(Vpk[2][26][1]*Vpk[3][26][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[2][17][2]*Vpk[4][17][2])+((Vpk[2][17][0]*
          Vpk[4][17][0])+(Vpk[2][17][1]*Vpk[4][17][1]))))+((3.51*((Vpk[2][14][2]
          *Vpk[4][14][2])+((Vpk[2][14][0]*Vpk[4][14][0])+(Vpk[2][14][1]*
          Vpk[4][14][1]))))+((8.806*((Vpk[2][11][2]*Vpk[4][11][2])+((
          Vpk[2][11][0]*Vpk[4][11][0])+(Vpk[2][11][1]*Vpk[4][11][1]))))+(
          10.3786426*((Vpk[2][8][2]*Wpk[4][8][0])-(Vpk[2][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[2][26][2]*Vpk[4][26][2])+((Vpk[2][26][0]*
          Vpk[4][26][0])+(Vpk[2][26][1]*Vpk[4][26][1]))))+((8.806*((
          Vpk[2][23][2]*Vpk[4][23][2])+((Vpk[2][23][0]*Vpk[4][23][0])+(
          Vpk[2][23][1]*Vpk[4][23][1]))))+((.205126*((Vpk[2][20][2]*
          Vpk[4][20][2])+((Vpk[2][20][0]*Vpk[4][20][0])+(Vpk[2][20][1]*
          Vpk[4][20][1]))))+temp[0])));
        mm[2][4] = ((.205126*((Vpk[2][32][2]*Vpk[4][32][2])+((Vpk[2][32][0]*
          Vpk[4][32][0])+(Vpk[2][32][1]*Vpk[4][32][1]))))+((1.2*((Vpk[2][29][2]*
          Vpk[4][29][2])+((Vpk[2][29][0]*Vpk[4][29][0])+(Vpk[2][29][1]*
          Vpk[4][29][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[2][14][2]*Vpk[5][14][2])+((Vpk[2][14][0]*
          Vpk[5][14][0])+(Vpk[2][14][1]*Vpk[5][14][1]))))+((8.806*((
          Vpk[2][11][2]*Vpk[5][11][2])+((Vpk[2][11][0]*Vpk[5][11][0])+(
          Vpk[2][11][1]*Vpk[5][11][1]))))+(32.413*((Vpk[2][8][2]*Vpk[5][8][2])+(
          (Vpk[2][8][0]*Vpk[5][8][0])+(Vpk[2][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((8.806*((Vpk[2][23][2]*Vpk[5][23][2])+((Vpk[2][23][0]*
          Vpk[5][23][0])+(Vpk[2][23][1]*Vpk[5][23][1]))))+((.205126*((
          Vpk[2][20][2]*Vpk[5][20][2])+((Vpk[2][20][0]*Vpk[5][20][0])+(
          Vpk[2][20][1]*Vpk[5][20][1]))))+((1.2*((Vpk[2][17][2]*Vpk[5][17][2])+(
          (Vpk[2][17][0]*Vpk[5][17][0])+(Vpk[2][17][1]*Vpk[5][17][1]))))+temp[0]
          )));
        mm[2][5] = ((.205126*((Vpk[2][32][2]*Vpk[5][32][2])+((Vpk[2][32][0]*
          Vpk[5][32][0])+(Vpk[2][32][1]*Vpk[5][32][1]))))+((1.2*((Vpk[2][29][2]*
          Vpk[5][29][2])+((Vpk[2][29][0]*Vpk[5][29][0])+(Vpk[2][29][1]*
          Vpk[5][29][1]))))+((3.51*((Vpk[2][26][2]*Vpk[5][26][2])+((
          Vpk[2][26][0]*Vpk[5][26][0])+(Vpk[2][26][1]*Vpk[5][26][1]))))+temp[1])
          ));
        mm[2][6] = (10.3786426*((Vpk[2][8][2]*Wpk[6][8][0])-(Vpk[2][8][0]*
          Wpk[6][8][2])));
        mm[2][7] = (10.3786426*((Vpk[2][8][2]*Wpk[7][8][0])-(Vpk[2][8][0]*
          Wpk[7][8][2])));
        mm[2][8] = (10.3786426*((pin[8][0]*Vpk[2][8][2])-(pin[8][2]*Vpk[2][8][0]
          )));
        temp[0] = ((1.2*((Vpk[2][17][2]*Vpk[9][17][2])+((Vpk[2][17][0]*
          Vpk[9][17][0])+(Vpk[2][17][1]*Vpk[9][17][1]))))+((3.51*((Vpk[2][14][2]
          *Vpk[9][14][2])+((Vpk[2][14][0]*Vpk[9][14][0])+(Vpk[2][14][1]*
          Vpk[9][14][1]))))+(8.806*((Vpk[2][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[2][11][0]*Wpk[9][11][2]))-(.002*(Vpk[2][11][1]*Wpk[9][11][2]))))))
          );
        mm[2][9] = ((.205126*((Vpk[2][20][2]*Vpk[9][20][2])+((Vpk[2][20][0]*
          Vpk[9][20][0])+(Vpk[2][20][1]*Vpk[9][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][17][2]*Vpk[10][17][2])+((Vpk[2][17][0]*
          Vpk[10][17][0])+(Vpk[2][17][1]*Vpk[10][17][1]))))+((3.51*((
          Vpk[2][14][2]*Vpk[10][14][2])+((Vpk[2][14][0]*Vpk[10][14][0])+(
          Vpk[2][14][1]*Vpk[10][14][1]))))+(8.806*((Vpk[2][11][2]*Vpk[10][11][2]
          )+((.1715*(Vpk[2][11][0]*Wpk[10][11][2]))-(.002*(Vpk[2][11][1]*
          Wpk[10][11][2])))))));
        mm[2][10] = ((.205126*((Vpk[2][20][2]*Vpk[10][20][2])+((Vpk[2][20][0]*
          Vpk[10][20][0])+(Vpk[2][20][1]*Vpk[10][20][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][17][2]*Vpk[11][17][2])+((Vpk[2][17][0]*
          Vpk[11][17][0])+(Vpk[2][17][1]*Vpk[11][17][1]))))+((3.51*((
          Vpk[2][14][2]*Vpk[11][14][2])+((Vpk[2][14][0]*Vpk[11][14][0])+(
          Vpk[2][14][1]*Vpk[11][14][1]))))+(8.806*((Vpk[2][11][2]*Vpk[11][11][2]
          )+((.1715*(pin[11][2]*Vpk[2][11][0]))-(.002*(pin[11][2]*Vpk[2][11][1])
          ))))));
        mm[2][11] = ((.205126*((Vpk[2][20][2]*Vpk[11][20][2])+((Vpk[2][20][0]*
          Vpk[11][20][0])+(Vpk[2][20][1]*Vpk[11][20][1]))))+temp[0]);
        mm[2][12] = ((.205126*((Vpk[2][20][2]*Vpk[12][20][2])+((Vpk[2][20][0]*
          Vpk[12][20][0])+(Vpk[2][20][1]*Vpk[12][20][1]))))+((.653562*((
          Vpk[2][14][0]*Wpk[12][14][2])-(Vpk[2][14][2]*Wpk[12][14][0])))+(1.2*((
          Vpk[2][17][2]*Vpk[12][17][2])+((Vpk[2][17][0]*Vpk[12][17][0])+(
          Vpk[2][17][1]*Vpk[12][17][1]))))));
        mm[2][13] = ((.205126*((Vpk[2][20][2]*Vpk[13][20][2])+((Vpk[2][20][0]*
          Vpk[13][20][0])+(Vpk[2][20][1]*Vpk[13][20][1]))))+((.653562*((
          Vpk[2][14][0]*Wpk[13][14][2])-(Vpk[2][14][2]*Wpk[13][14][0])))+(1.2*((
          Vpk[2][17][2]*Vpk[13][17][2])+((Vpk[2][17][0]*Vpk[13][17][0])+(
          Vpk[2][17][1]*Vpk[13][17][1]))))));
        mm[2][14] = ((.205126*((Vpk[2][20][2]*Vpk[14][20][2])+((Vpk[2][20][0]*
          Vpk[14][20][0])+(Vpk[2][20][1]*Vpk[14][20][1]))))+((.653562*((
          pin[14][2]*Vpk[2][14][0])-(pin[14][0]*Vpk[2][14][2])))+(1.2*((
          Vpk[2][17][2]*Vpk[14][17][2])+((Vpk[2][17][0]*Vpk[14][17][0])+(
          Vpk[2][17][1]*Vpk[14][17][1]))))));
        mm[2][15] = ((.205126*((Vpk[2][20][2]*Vpk[15][20][2])+((Vpk[2][20][0]*
          Vpk[15][20][0])+(Vpk[2][20][1]*Vpk[15][20][1]))))+(1.2*((Vpk[2][17][2]
          *Vpk[15][17][2])+((Vpk[2][17][0]*Vpk[15][17][0])+(Vpk[2][17][1]*
          Vpk[15][17][1])))));
        mm[2][16] = ((.205126*((Vpk[2][20][2]*Vpk[16][20][2])+((Vpk[2][20][0]*
          Vpk[16][20][0])+(Vpk[2][20][1]*Vpk[16][20][1]))))+(1.2*((Vpk[2][17][2]
          *Vpk[16][17][2])+((Vpk[2][17][0]*Vpk[16][17][0])+(Vpk[2][17][1]*
          Vpk[16][17][1])))));
        mm[2][17] = ((.205126*((Vpk[2][20][2]*Vpk[17][20][2])+((Vpk[2][20][0]*
          Vpk[17][20][0])+(Vpk[2][20][1]*Vpk[17][20][1]))))+(1.2*((Vpk[2][17][2]
          *Vpk[17][17][2])+((Vpk[2][17][0]*Vpk[17][17][0])+(Vpk[2][17][1]*
          Vpk[17][17][1])))));
        mm[2][18] = (.205126*((Vpk[2][20][2]*Vpk[18][20][2])+((Vpk[2][20][0]*
          Vpk[18][20][0])+(Vpk[2][20][1]*Vpk[18][20][1]))));
        mm[2][19] = (.205126*((Vpk[2][20][2]*Vpk[19][20][2])+((Vpk[2][20][0]*
          Vpk[19][20][0])+(Vpk[2][20][1]*Vpk[19][20][1]))));
        mm[2][20] = (.205126*((Vpk[2][20][2]*Vpk[20][20][2])+((Vpk[2][20][0]*
          Vpk[20][20][0])+(Vpk[2][20][1]*Vpk[20][20][1]))));
        temp[0] = ((1.2*((Vpk[2][29][2]*Vpk[21][29][2])+((Vpk[2][29][0]*
          Vpk[21][29][0])+(Vpk[2][29][1]*Vpk[21][29][1]))))+((3.51*((
          Vpk[2][26][2]*Vpk[21][26][2])+((Vpk[2][26][0]*Vpk[21][26][0])+(
          Vpk[2][26][1]*Vpk[21][26][1]))))+(8.806*((Vpk[2][23][2]*Vpk[21][23][2]
          )+((.1715*(Vpk[2][23][0]*Wpk[21][23][2]))-(.002*(Vpk[2][23][1]*
          Wpk[21][23][2])))))));
        mm[2][21] = ((.205126*((Vpk[2][32][2]*Vpk[21][32][2])+((Vpk[2][32][0]*
          Vpk[21][32][0])+(Vpk[2][32][1]*Vpk[21][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][29][2]*Vpk[22][29][2])+((Vpk[2][29][0]*
          Vpk[22][29][0])+(Vpk[2][29][1]*Vpk[22][29][1]))))+((3.51*((
          Vpk[2][26][2]*Vpk[22][26][2])+((Vpk[2][26][0]*Vpk[22][26][0])+(
          Vpk[2][26][1]*Vpk[22][26][1]))))+(8.806*((Vpk[2][23][2]*Vpk[22][23][2]
          )+((.1715*(Vpk[2][23][0]*Wpk[22][23][2]))-(.002*(Vpk[2][23][1]*
          Wpk[22][23][2])))))));
        mm[2][22] = ((.205126*((Vpk[2][32][2]*Vpk[22][32][2])+((Vpk[2][32][0]*
          Vpk[22][32][0])+(Vpk[2][32][1]*Vpk[22][32][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][29][2]*Vpk[23][29][2])+((Vpk[2][29][0]*
          Vpk[23][29][0])+(Vpk[2][29][1]*Vpk[23][29][1]))))+((3.51*((
          Vpk[2][26][2]*Vpk[23][26][2])+((Vpk[2][26][0]*Vpk[23][26][0])+(
          Vpk[2][26][1]*Vpk[23][26][1]))))+(8.806*((Vpk[2][23][2]*Vpk[23][23][2]
          )+((.1715*(pin[23][2]*Vpk[2][23][0]))-(.002*(pin[23][2]*Vpk[2][23][1])
          ))))));
        mm[2][23] = ((.205126*((Vpk[2][32][2]*Vpk[23][32][2])+((Vpk[2][32][0]*
          Vpk[23][32][0])+(Vpk[2][32][1]*Vpk[23][32][1]))))+temp[0]);
        mm[2][24] = ((.205126*((Vpk[2][32][2]*Vpk[24][32][2])+((Vpk[2][32][0]*
          Vpk[24][32][0])+(Vpk[2][32][1]*Vpk[24][32][1]))))+((.653562*((
          Vpk[2][26][0]*Wpk[24][26][2])-(Vpk[2][26][2]*Wpk[24][26][0])))+(1.2*((
          Vpk[2][29][2]*Vpk[24][29][2])+((Vpk[2][29][0]*Vpk[24][29][0])+(
          Vpk[2][29][1]*Vpk[24][29][1]))))));
        mm[2][25] = ((.205126*((Vpk[2][32][2]*Vpk[25][32][2])+((Vpk[2][32][0]*
          Vpk[25][32][0])+(Vpk[2][32][1]*Vpk[25][32][1]))))+((.653562*((
          Vpk[2][26][0]*Wpk[25][26][2])-(Vpk[2][26][2]*Wpk[25][26][0])))+(1.2*((
          Vpk[2][29][2]*Vpk[25][29][2])+((Vpk[2][29][0]*Vpk[25][29][0])+(
          Vpk[2][29][1]*Vpk[25][29][1]))))));
        mm[2][26] = ((.205126*((Vpk[2][32][2]*Vpk[26][32][2])+((Vpk[2][32][0]*
          Vpk[26][32][0])+(Vpk[2][32][1]*Vpk[26][32][1]))))+((.653562*((
          pin[26][2]*Vpk[2][26][0])-(pin[26][0]*Vpk[2][26][2])))+(1.2*((
          Vpk[2][29][2]*Vpk[26][29][2])+((Vpk[2][29][0]*Vpk[26][29][0])+(
          Vpk[2][29][1]*Vpk[26][29][1]))))));
        mm[2][27] = ((.205126*((Vpk[2][32][2]*Vpk[27][32][2])+((Vpk[2][32][0]*
          Vpk[27][32][0])+(Vpk[2][32][1]*Vpk[27][32][1]))))+(1.2*((Vpk[2][29][2]
          *Vpk[27][29][2])+((Vpk[2][29][0]*Vpk[27][29][0])+(Vpk[2][29][1]*
          Vpk[27][29][1])))));
        mm[2][28] = ((.205126*((Vpk[2][32][2]*Vpk[28][32][2])+((Vpk[2][32][0]*
          Vpk[28][32][0])+(Vpk[2][32][1]*Vpk[28][32][1]))))+(1.2*((Vpk[2][29][2]
          *Vpk[28][29][2])+((Vpk[2][29][0]*Vpk[28][29][0])+(Vpk[2][29][1]*
          Vpk[28][29][1])))));
        mm[2][29] = ((.205126*((Vpk[2][32][2]*Vpk[29][32][2])+((Vpk[2][32][0]*
          Vpk[29][32][0])+(Vpk[2][32][1]*Vpk[29][32][1]))))+(1.2*((Vpk[2][29][2]
          *Vpk[29][29][2])+((Vpk[2][29][0]*Vpk[29][29][0])+(Vpk[2][29][1]*
          Vpk[29][29][1])))));
        mm[2][30] = (.205126*((Vpk[2][32][2]*Vpk[30][32][2])+((Vpk[2][32][0]*
          Vpk[30][32][0])+(Vpk[2][32][1]*Vpk[30][32][1]))));
        mm[2][31] = (.205126*((Vpk[2][32][2]*Vpk[31][32][2])+((Vpk[2][32][0]*
          Vpk[31][32][0])+(Vpk[2][32][1]*Vpk[31][32][1]))));
        mm[2][32] = (.205126*((Vpk[2][32][2]*Vpk[32][32][2])+((Vpk[2][32][0]*
          Vpk[32][32][0])+(Vpk[2][32][1]*Vpk[32][32][1]))));
        temp[0] = ((32.413*((Vpk[3][8][2]*Vpk[3][8][2])+((Vpk[3][8][0]*
          Vpk[3][8][0])+(Vpk[3][8][1]*Vpk[3][8][1]))))+((1.3552*(Wpk[3][8][2]*
          Wpk[3][8][2]))+((.7153*(Wpk[3][8][1]*Wpk[3][8][1]))+(1.396*(
          Wpk[3][8][0]*Wpk[3][8][0])))));
        temp[1] = (((8.806*((Vpk[3][11][2]*Vpk[3][11][2])+((Vpk[3][11][0]*
          Vpk[3][11][0])+(Vpk[3][11][1]*Vpk[3][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[3][11][2]))+((.0332*(Wpk[3][11][1]*Wpk[3][11][1]))+(.1268*(
          Wpk[3][11][0]*Wpk[3][11][0])))))+temp[0]);
        temp[2] = (((3.51*((Vpk[3][14][2]*Vpk[3][14][2])+((Vpk[3][14][0]*
          Vpk[3][14][0])+(Vpk[3][14][1]*Vpk[3][14][1]))))+((.0484*(Wpk[3][14][2]
          *Wpk[3][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[3][14][1]))+(.0477*(
          Wpk[3][14][0]*Wpk[3][14][0])))))+temp[1]);
        temp[3] = (((1.2*((Vpk[3][17][2]*Vpk[3][17][2])+((Vpk[3][17][0]*
          Vpk[3][17][0])+(Vpk[3][17][1]*Vpk[3][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[3][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[3][17][0]))
          +(.003709*(Wpk[3][17][1]*Wpk[3][17][1])))))+temp[2]);
        temp[4] = (((.205126*((Vpk[3][20][2]*Vpk[3][20][2])+((Vpk[3][20][0]*
          Vpk[3][20][0])+(Vpk[3][20][1]*Vpk[3][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[3][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[3][20][0]))
          +(.000179*(Wpk[3][20][1]*Wpk[3][20][1])))))+temp[3]);
        temp[5] = (((8.806*((Vpk[3][23][2]*Vpk[3][23][2])+((Vpk[3][23][0]*
          Vpk[3][23][0])+(Vpk[3][23][1]*Vpk[3][23][1]))))+((.1337*(Wpk[3][23][2]
          *Wpk[3][23][2]))+((.0332*(Wpk[3][23][1]*Wpk[3][23][1]))+(.1268*(
          Wpk[3][23][0]*Wpk[3][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[3][26][2]*Vpk[3][26][2])+((Vpk[3][26][0]*
          Vpk[3][26][0])+(Vpk[3][26][1]*Vpk[3][26][1]))))+((.0484*(Wpk[3][26][2]
          *Wpk[3][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[3][26][1]))+(.0477*(
          Wpk[3][26][0]*Wpk[3][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[3][29][2]*Vpk[3][29][2])+((Vpk[3][29][0]*
          Vpk[3][29][0])+(Vpk[3][29][1]*Vpk[3][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[3][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[3][29][0]))
          +(.003709*(Wpk[3][29][1]*Wpk[3][29][1])))))+temp[6]);
        mm[3][3] = (.0973+(((.205126*((Vpk[3][32][2]*Vpk[3][32][2])+((
          Vpk[3][32][0]*Vpk[3][32][0])+(Vpk[3][32][1]*Vpk[3][32][1]))))+((
          .000119*(Wpk[3][32][2]*Wpk[3][32][2]))+((.000117*(Wpk[3][32][0]*
          Wpk[3][32][0]))+(.000179*(Wpk[3][32][1]*Wpk[3][32][1])))))+temp[7]));
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[4][11][2])+((Vpk[3][11][0]*
          Vpk[4][11][0])+(Vpk[3][11][1]*Vpk[4][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[4][11][2]))+((.0332*(Wpk[3][11][1]*Wpk[4][11][1]))+(.1268*(
          Wpk[3][11][0]*Wpk[4][11][0])))));
        temp[1] = ((3.51*((Vpk[3][14][2]*Vpk[4][14][2])+((Vpk[3][14][0]*
          Vpk[4][14][0])+(Vpk[3][14][1]*Vpk[4][14][1]))))+((.0484*(Wpk[3][14][2]
          *Wpk[4][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[4][14][1]))+(.0477*(
          Wpk[3][14][0]*Wpk[4][14][0])))));
        temp[2] = ((1.2*((Vpk[3][17][2]*Vpk[4][17][2])+((Vpk[3][17][0]*
          Vpk[4][17][0])+(Vpk[3][17][1]*Vpk[4][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[4][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[4][17][0]))
          +(.003709*(Wpk[3][17][1]*Wpk[4][17][1])))));
        temp[3] = ((.205126*((Vpk[3][20][2]*Vpk[4][20][2])+((Vpk[3][20][0]*
          Vpk[4][20][0])+(Vpk[3][20][1]*Vpk[4][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[4][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[4][20][0]))
          +(.000179*(Wpk[3][20][1]*Wpk[4][20][1])))));
        temp[4] = (temp[3]+(temp[2]+(temp[1]+(temp[0]+((10.3786426*((
          Vpk[3][8][2]*Wpk[4][8][0])-(Vpk[3][8][0]*Wpk[4][8][2])))+((1.3552*(
          Wpk[3][8][2]*Wpk[4][8][2]))+((.7153*(Wpk[3][8][1]*Wpk[4][8][1]))+(
          1.396*(Wpk[3][8][0]*Wpk[4][8][0])))))))));
        temp[5] = (((8.806*((Vpk[3][23][2]*Vpk[4][23][2])+((Vpk[3][23][0]*
          Vpk[4][23][0])+(Vpk[3][23][1]*Vpk[4][23][1]))))+((.1337*(Wpk[3][23][2]
          *Wpk[4][23][2]))+((.0332*(Wpk[3][23][1]*Wpk[4][23][1]))+(.1268*(
          Wpk[3][23][0]*Wpk[4][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[3][26][2]*Vpk[4][26][2])+((Vpk[3][26][0]*
          Vpk[4][26][0])+(Vpk[3][26][1]*Vpk[4][26][1]))))+((.0484*(Wpk[3][26][2]
          *Wpk[4][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[4][26][1]))+(.0477*(
          Wpk[3][26][0]*Wpk[4][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[3][29][2]*Vpk[4][29][2])+((Vpk[3][29][0]*
          Vpk[4][29][0])+(Vpk[3][29][1]*Vpk[4][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[4][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[4][29][0]))
          +(.003709*(Wpk[3][29][1]*Wpk[4][29][1])))))+temp[6]);
        mm[3][4] = (((.205126*((Vpk[3][32][2]*Vpk[4][32][2])+((Vpk[3][32][0]*
          Vpk[4][32][0])+(Vpk[3][32][1]*Vpk[4][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[4][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[4][32][0]))
          +(.000179*(Wpk[3][32][1]*Wpk[4][32][1])))))+temp[7]);
        temp[0] = ((32.413*((Vpk[3][8][2]*Vpk[5][8][2])+((Vpk[3][8][0]*
          Vpk[5][8][0])+(Vpk[3][8][1]*Vpk[5][8][1]))))+((1.3552*(Wpk[3][8][2]*
          Wpk[5][8][2]))+((.7153*(Wpk[3][8][1]*Wpk[5][8][1]))+(1.396*(
          Wpk[3][8][0]*Wpk[5][8][0])))));
        temp[1] = (((8.806*((Vpk[3][11][2]*Vpk[5][11][2])+((Vpk[3][11][0]*
          Vpk[5][11][0])+(Vpk[3][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[5][11][2]))+((.0332*(Wpk[3][11][1]*Wpk[5][11][1]))+(.1268*(
          Wpk[3][11][0]*Wpk[5][11][0])))))+temp[0]);
        temp[2] = (((3.51*((Vpk[3][14][2]*Vpk[5][14][2])+((Vpk[3][14][0]*
          Vpk[5][14][0])+(Vpk[3][14][1]*Vpk[5][14][1]))))+((.0484*(Wpk[3][14][2]
          *Wpk[5][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[5][14][1]))+(.0477*(
          Wpk[3][14][0]*Wpk[5][14][0])))))+temp[1]);
        temp[3] = (((1.2*((Vpk[3][17][2]*Vpk[5][17][2])+((Vpk[3][17][0]*
          Vpk[5][17][0])+(Vpk[3][17][1]*Vpk[5][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[5][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[5][17][0]))
          +(.003709*(Wpk[3][17][1]*Wpk[5][17][1])))))+temp[2]);
        temp[4] = (((.205126*((Vpk[3][20][2]*Vpk[5][20][2])+((Vpk[3][20][0]*
          Vpk[5][20][0])+(Vpk[3][20][1]*Vpk[5][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[5][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[5][20][0]))
          +(.000179*(Wpk[3][20][1]*Wpk[5][20][1])))))+temp[3]);
        temp[5] = (((8.806*((Vpk[3][23][2]*Vpk[5][23][2])+((Vpk[3][23][0]*
          Vpk[5][23][0])+(Vpk[3][23][1]*Vpk[5][23][1]))))+((.1337*(Wpk[3][23][2]
          *Wpk[5][23][2]))+((.0332*(Wpk[3][23][1]*Wpk[5][23][1]))+(.1268*(
          Wpk[3][23][0]*Wpk[5][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[3][26][2]*Vpk[5][26][2])+((Vpk[3][26][0]*
          Vpk[5][26][0])+(Vpk[3][26][1]*Vpk[5][26][1]))))+((.0484*(Wpk[3][26][2]
          *Wpk[5][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[5][26][1]))+(.0477*(
          Wpk[3][26][0]*Wpk[5][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[3][29][2]*Vpk[5][29][2])+((Vpk[3][29][0]*
          Vpk[5][29][0])+(Vpk[3][29][1]*Vpk[5][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[5][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[5][29][0]))
          +(.003709*(Wpk[3][29][1]*Wpk[5][29][1])))))+temp[6]);
        mm[3][5] = (((.205126*((Vpk[3][32][2]*Vpk[5][32][2])+((Vpk[3][32][0]*
          Vpk[5][32][0])+(Vpk[3][32][1]*Vpk[5][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[5][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[5][32][0]))
          +(.000179*(Wpk[3][32][1]*Wpk[5][32][1])))))+temp[7]);
        mm[3][6] = ((10.3786426*((Vpk[3][8][2]*Wpk[6][8][0])-(Vpk[3][8][0]*
          Wpk[6][8][2])))+((1.3552*(Wpk[3][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[3][8][1]*Wpk[6][8][1]))+(1.396*(Wpk[3][8][0]*Wpk[6][8][0])))));
        mm[3][7] = ((10.3786426*((Vpk[3][8][2]*Wpk[7][8][0])-(Vpk[3][8][0]*
          Wpk[7][8][2])))+((1.3552*(Wpk[3][8][2]*Wpk[7][8][2]))+((.7153*(
          Wpk[3][8][1]*Wpk[7][8][1]))+(1.396*(Wpk[3][8][0]*Wpk[7][8][0])))));
        mm[3][8] = ((10.3786426*((pin[8][0]*Vpk[3][8][2])-(pin[8][2]*
          Vpk[3][8][0])))+((1.3552*(pin[8][2]*Wpk[3][8][2]))+((.7153*(pin[8][1]*
          Wpk[3][8][1]))+(1.396*(pin[8][0]*Wpk[3][8][0])))));
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[9][11][2])+((.1715*(Vpk[3][11][0]*
          Wpk[9][11][2]))-(.002*(Vpk[3][11][1]*Wpk[9][11][2])))))+((.1337*(
          Wpk[3][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[3][11][1]*Wpk[9][11][1]))+(
          .1268*(Wpk[3][11][0]*Wpk[9][11][0])))));
        temp[1] = (((3.51*((Vpk[3][14][2]*Vpk[9][14][2])+((Vpk[3][14][0]*
          Vpk[9][14][0])+(Vpk[3][14][1]*Vpk[9][14][1]))))+((.0484*(Wpk[3][14][2]
          *Wpk[9][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[9][14][1]))+(.0477*(
          Wpk[3][14][0]*Wpk[9][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][17][2]*Vpk[9][17][2])+((Vpk[3][17][0]*
          Vpk[9][17][0])+(Vpk[3][17][1]*Vpk[9][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[9][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[9][17][0]))
          +(.003709*(Wpk[3][17][1]*Wpk[9][17][1])))))+temp[1]);
        mm[3][9] = (((.205126*((Vpk[3][20][2]*Vpk[9][20][2])+((Vpk[3][20][0]*
          Vpk[9][20][0])+(Vpk[3][20][1]*Vpk[9][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[9][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[9][20][0]))
          +(.000179*(Wpk[3][20][1]*Wpk[9][20][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[10][11][2])+((.1715*(Vpk[3][11][0]
          *Wpk[10][11][2]))-(.002*(Vpk[3][11][1]*Wpk[10][11][2])))))+((.1337*(
          Wpk[3][11][2]*Wpk[10][11][2]))+((.0332*(Wpk[3][11][1]*Wpk[10][11][1]))
          +(.1268*(Wpk[3][11][0]*Wpk[10][11][0])))));
        temp[1] = (((3.51*((Vpk[3][14][2]*Vpk[10][14][2])+((Vpk[3][14][0]*
          Vpk[10][14][0])+(Vpk[3][14][1]*Vpk[10][14][1]))))+((.0484*(
          Wpk[3][14][2]*Wpk[10][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[10][14][1]))
          +(.0477*(Wpk[3][14][0]*Wpk[10][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][17][2]*Vpk[10][17][2])+((Vpk[3][17][0]*
          Vpk[10][17][0])+(Vpk[3][17][1]*Vpk[10][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[10][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[10][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[10][17][1])))))+temp[1]);
        mm[3][10] = (((.205126*((Vpk[3][20][2]*Vpk[10][20][2])+((Vpk[3][20][0]*
          Vpk[10][20][0])+(Vpk[3][20][1]*Vpk[10][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[10][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[10][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[10][20][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[3][14][2]*Vpk[11][14][2])+((Vpk[3][14][0]*
          Vpk[11][14][0])+(Vpk[3][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[3][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[3][14][1]*Wpk[11][14][1]))
          +(.0477*(Wpk[3][14][0]*Wpk[11][14][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[3][11][2]*Vpk[11][11][2])+((.1715*(
          pin[11][2]*Vpk[3][11][0]))-(.002*(pin[11][2]*Vpk[3][11][1])))))+((
          .1337*(pin[11][2]*Wpk[3][11][2]))+((.0332*(pin[11][1]*Wpk[3][11][1]))+
          (.1268*(pin[11][0]*Wpk[3][11][0]))))));
        temp[2] = (((1.2*((Vpk[3][17][2]*Vpk[11][17][2])+((Vpk[3][17][0]*
          Vpk[11][17][0])+(Vpk[3][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[11][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[11][17][1])))))+temp[1]);
        mm[3][11] = (((.205126*((Vpk[3][20][2]*Vpk[11][20][2])+((Vpk[3][20][0]*
          Vpk[11][20][0])+(Vpk[3][20][1]*Vpk[11][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[11][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[11][20][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[3][17][2]*Vpk[12][17][2])+((Vpk[3][17][0]*
          Vpk[12][17][0])+(Vpk[3][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[12][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[3][20][2]*Vpk[12][20][2])+((Vpk[3][20][0]*
          Vpk[12][20][0])+(Vpk[3][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[12][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[12][20][1])))));
        mm[3][12] = (temp[1]+(((.653562*((Vpk[3][14][0]*Wpk[12][14][2])-(
          Vpk[3][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[3][14][2]*Wpk[12][14][2])
          )+((.0048*(Wpk[3][14][1]*Wpk[12][14][1]))+(.0477*(Wpk[3][14][0]*
          Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[3][17][2]*Vpk[13][17][2])+((Vpk[3][17][0]*
          Vpk[13][17][0])+(Vpk[3][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[13][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[3][20][2]*Vpk[13][20][2])+((Vpk[3][20][0]*
          Vpk[13][20][0])+(Vpk[3][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[13][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[13][20][1])))));
        mm[3][13] = (temp[1]+(((.653562*((Vpk[3][14][0]*Wpk[13][14][2])-(
          Vpk[3][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[3][14][2]*Wpk[13][14][2])
          )+((.0048*(Wpk[3][14][1]*Wpk[13][14][1]))+(.0477*(Wpk[3][14][0]*
          Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[3][14][0])-(pin[14][0]*
          Vpk[3][14][2])))+((.0484*(pin[14][2]*Wpk[3][14][2]))+((.0048*(
          pin[14][1]*Wpk[3][14][1]))+(.0477*(pin[14][0]*Wpk[3][14][0])))))+((1.2
          *((Vpk[3][17][2]*Vpk[14][17][2])+((Vpk[3][17][0]*Vpk[14][17][0])+(
          Vpk[3][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[3][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[3][17][1]*Wpk[14][17][1]))))));
        mm[3][14] = (((.205126*((Vpk[3][20][2]*Vpk[14][20][2])+((Vpk[3][20][0]*
          Vpk[14][20][0])+(Vpk[3][20][1]*Vpk[14][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[14][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[14][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][17][2]*Vpk[15][17][2])+((Vpk[3][17][0]*
          Vpk[15][17][0])+(Vpk[3][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[15][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[15][17][1])))));
        mm[3][15] = (((.205126*((Vpk[3][20][2]*Vpk[15][20][2])+((Vpk[3][20][0]*
          Vpk[15][20][0])+(Vpk[3][20][1]*Vpk[15][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[15][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[15][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][17][2]*Vpk[16][17][2])+((Vpk[3][17][0]*
          Vpk[16][17][0])+(Vpk[3][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[3][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[3][17][0]*Wpk[16][17][0]
          ))+(.003709*(Wpk[3][17][1]*Wpk[16][17][1])))));
        mm[3][16] = (((.205126*((Vpk[3][20][2]*Vpk[16][20][2])+((Vpk[3][20][0]*
          Vpk[16][20][0])+(Vpk[3][20][1]*Vpk[16][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[16][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[16][20][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[3][20][2]*Vpk[17][20][2])+((Vpk[3][20][0]*
          Vpk[17][20][0])+(Vpk[3][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[17][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[17][20][1])))));
        mm[3][17] = (temp[0]+((1.2*((Vpk[3][17][2]*Vpk[17][17][2])+((
          Vpk[3][17][0]*Vpk[17][17][0])+(Vpk[3][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[3][17][2]))+((.001361*(pin[17][0]*
          Wpk[3][17][0]))+(.003709*(pin[17][1]*Wpk[3][17][1]))))));
        mm[3][18] = ((.205126*((Vpk[3][20][2]*Vpk[18][20][2])+((Vpk[3][20][0]*
          Vpk[18][20][0])+(Vpk[3][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[18][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[18][20][1])))));
        mm[3][19] = ((.205126*((Vpk[3][20][2]*Vpk[19][20][2])+((Vpk[3][20][0]*
          Vpk[19][20][0])+(Vpk[3][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[3][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[3][20][0]*Wpk[19][20][0]
          ))+(.000179*(Wpk[3][20][1]*Wpk[19][20][1])))));
        mm[3][20] = ((.205126*((Vpk[3][20][2]*Vpk[20][20][2])+((Vpk[3][20][0]*
          Vpk[20][20][0])+(Vpk[3][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[3][20][2]))+((.000117*(pin[20][0]*Wpk[3][20][0]))+(
          .000179*(pin[20][1]*Wpk[3][20][1])))));
        temp[0] = ((8.806*((Vpk[3][23][2]*Vpk[21][23][2])+((.1715*(Vpk[3][23][0]
          *Wpk[21][23][2]))-(.002*(Vpk[3][23][1]*Wpk[21][23][2])))))+((.1337*(
          Wpk[3][23][2]*Wpk[21][23][2]))+((.0332*(Wpk[3][23][1]*Wpk[21][23][1]))
          +(.1268*(Wpk[3][23][0]*Wpk[21][23][0])))));
        temp[1] = (((3.51*((Vpk[3][26][2]*Vpk[21][26][2])+((Vpk[3][26][0]*
          Vpk[21][26][0])+(Vpk[3][26][1]*Vpk[21][26][1]))))+((.0484*(
          Wpk[3][26][2]*Wpk[21][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[21][26][1]))
          +(.0477*(Wpk[3][26][0]*Wpk[21][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][29][2]*Vpk[21][29][2])+((Vpk[3][29][0]*
          Vpk[21][29][0])+(Vpk[3][29][1]*Vpk[21][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[21][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[21][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[21][29][1])))))+temp[1]);
        mm[3][21] = (((.205126*((Vpk[3][32][2]*Vpk[21][32][2])+((Vpk[3][32][0]*
          Vpk[21][32][0])+(Vpk[3][32][1]*Vpk[21][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[21][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[21][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[21][32][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[3][23][2]*Vpk[22][23][2])+((.1715*(Vpk[3][23][0]
          *Wpk[22][23][2]))-(.002*(Vpk[3][23][1]*Wpk[22][23][2])))))+((.1337*(
          Wpk[3][23][2]*Wpk[22][23][2]))+((.0332*(Wpk[3][23][1]*Wpk[22][23][1]))
          +(.1268*(Wpk[3][23][0]*Wpk[22][23][0])))));
        temp[1] = (((3.51*((Vpk[3][26][2]*Vpk[22][26][2])+((Vpk[3][26][0]*
          Vpk[22][26][0])+(Vpk[3][26][1]*Vpk[22][26][1]))))+((.0484*(
          Wpk[3][26][2]*Wpk[22][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[22][26][1]))
          +(.0477*(Wpk[3][26][0]*Wpk[22][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][29][2]*Vpk[22][29][2])+((Vpk[3][29][0]*
          Vpk[22][29][0])+(Vpk[3][29][1]*Vpk[22][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[22][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[22][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[22][29][1])))))+temp[1]);
        mm[3][22] = (((.205126*((Vpk[3][32][2]*Vpk[22][32][2])+((Vpk[3][32][0]*
          Vpk[22][32][0])+(Vpk[3][32][1]*Vpk[22][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[22][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[22][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[22][32][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[3][26][2]*Vpk[23][26][2])+((Vpk[3][26][0]*
          Vpk[23][26][0])+(Vpk[3][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[3][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[3][26][1]*Wpk[23][26][1]))
          +(.0477*(Wpk[3][26][0]*Wpk[23][26][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[3][23][2]*Vpk[23][23][2])+((.1715*(
          pin[23][2]*Vpk[3][23][0]))-(.002*(pin[23][2]*Vpk[3][23][1])))))+((
          .1337*(pin[23][2]*Wpk[3][23][2]))+((.0332*(pin[23][1]*Wpk[3][23][1]))+
          (.1268*(pin[23][0]*Wpk[3][23][0]))))));
        temp[2] = (((1.2*((Vpk[3][29][2]*Vpk[23][29][2])+((Vpk[3][29][0]*
          Vpk[23][29][0])+(Vpk[3][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[23][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[23][29][1])))))+temp[1]);
        mm[3][23] = (((.205126*((Vpk[3][32][2]*Vpk[23][32][2])+((Vpk[3][32][0]*
          Vpk[23][32][0])+(Vpk[3][32][1]*Vpk[23][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[23][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[23][32][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[3][29][2]*Vpk[24][29][2])+((Vpk[3][29][0]*
          Vpk[24][29][0])+(Vpk[3][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[24][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[3][32][2]*Vpk[24][32][2])+((Vpk[3][32][0]*
          Vpk[24][32][0])+(Vpk[3][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[24][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[24][32][1])))));
        mm[3][24] = (temp[1]+(((.653562*((Vpk[3][26][0]*Wpk[24][26][2])-(
          Vpk[3][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[3][26][2]*Wpk[24][26][2])
          )+((.0048*(Wpk[3][26][1]*Wpk[24][26][1]))+(.0477*(Wpk[3][26][0]*
          Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[3][29][2]*Vpk[25][29][2])+((Vpk[3][29][0]*
          Vpk[25][29][0])+(Vpk[3][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[25][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[3][32][2]*Vpk[25][32][2])+((Vpk[3][32][0]*
          Vpk[25][32][0])+(Vpk[3][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[25][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[25][32][1])))));
        mm[3][25] = (temp[1]+(((.653562*((Vpk[3][26][0]*Wpk[25][26][2])-(
          Vpk[3][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[3][26][2]*Wpk[25][26][2])
          )+((.0048*(Wpk[3][26][1]*Wpk[25][26][1]))+(.0477*(Wpk[3][26][0]*
          Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[3][26][0])-(pin[26][0]*
          Vpk[3][26][2])))+((.0484*(pin[26][2]*Wpk[3][26][2]))+((.0048*(
          pin[26][1]*Wpk[3][26][1]))+(.0477*(pin[26][0]*Wpk[3][26][0])))))+((1.2
          *((Vpk[3][29][2]*Vpk[26][29][2])+((Vpk[3][29][0]*Vpk[26][29][0])+(
          Vpk[3][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[3][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[3][29][1]*Wpk[26][29][1]))))));
        mm[3][26] = (((.205126*((Vpk[3][32][2]*Vpk[26][32][2])+((Vpk[3][32][0]*
          Vpk[26][32][0])+(Vpk[3][32][1]*Vpk[26][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[26][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[26][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][29][2]*Vpk[27][29][2])+((Vpk[3][29][0]*
          Vpk[27][29][0])+(Vpk[3][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[27][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[27][29][1])))));
        mm[3][27] = (((.205126*((Vpk[3][32][2]*Vpk[27][32][2])+((Vpk[3][32][0]*
          Vpk[27][32][0])+(Vpk[3][32][1]*Vpk[27][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[27][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[27][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][29][2]*Vpk[28][29][2])+((Vpk[3][29][0]*
          Vpk[28][29][0])+(Vpk[3][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[3][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[3][29][0]*Wpk[28][29][0]
          ))+(.003709*(Wpk[3][29][1]*Wpk[28][29][1])))));
        mm[3][28] = (((.205126*((Vpk[3][32][2]*Vpk[28][32][2])+((Vpk[3][32][0]*
          Vpk[28][32][0])+(Vpk[3][32][1]*Vpk[28][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[28][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[28][32][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[3][32][2]*Vpk[29][32][2])+((Vpk[3][32][0]*
          Vpk[29][32][0])+(Vpk[3][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[29][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[29][32][1])))));
        mm[3][29] = (temp[0]+((1.2*((Vpk[3][29][2]*Vpk[29][29][2])+((
          Vpk[3][29][0]*Vpk[29][29][0])+(Vpk[3][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[3][29][2]))+((.001361*(pin[29][0]*
          Wpk[3][29][0]))+(.003709*(pin[29][1]*Wpk[3][29][1]))))));
        mm[3][30] = ((.205126*((Vpk[3][32][2]*Vpk[30][32][2])+((Vpk[3][32][0]*
          Vpk[30][32][0])+(Vpk[3][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[30][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[30][32][1])))));
        mm[3][31] = ((.205126*((Vpk[3][32][2]*Vpk[31][32][2])+((Vpk[3][32][0]*
          Vpk[31][32][0])+(Vpk[3][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[3][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[3][32][0]*Wpk[31][32][0]
          ))+(.000179*(Wpk[3][32][1]*Wpk[31][32][1])))));
        mm[3][32] = ((.205126*((Vpk[3][32][2]*Vpk[32][32][2])+((Vpk[3][32][0]*
          Vpk[32][32][0])+(Vpk[3][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[3][32][2]))+((.000117*(pin[32][0]*Wpk[3][32][0]))+(
          .000179*(pin[32][1]*Wpk[3][32][1])))));
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[4][11][2])+((Vpk[4][11][0]*
          Vpk[4][11][0])+(Vpk[4][11][1]*Vpk[4][11][1]))))+((.1337*(Wpk[4][11][2]
          *Wpk[4][11][2]))+((.0332*(Wpk[4][11][1]*Wpk[4][11][1]))+(.1268*(
          Wpk[4][11][0]*Wpk[4][11][0])))));
        temp[1] = ((3.51*((Vpk[4][14][2]*Vpk[4][14][2])+((Vpk[4][14][0]*
          Vpk[4][14][0])+(Vpk[4][14][1]*Vpk[4][14][1]))))+((.0484*(Wpk[4][14][2]
          *Wpk[4][14][2]))+((.0048*(Wpk[4][14][1]*Wpk[4][14][1]))+(.0477*(
          Wpk[4][14][0]*Wpk[4][14][0])))));
        temp[2] = ((1.2*((Vpk[4][17][2]*Vpk[4][17][2])+((Vpk[4][17][0]*
          Vpk[4][17][0])+(Vpk[4][17][1]*Vpk[4][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[4][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[4][17][0]))
          +(.003709*(Wpk[4][17][1]*Wpk[4][17][1])))));
        temp[3] = ((.205126*((Vpk[4][20][2]*Vpk[4][20][2])+((Vpk[4][20][0]*
          Vpk[4][20][0])+(Vpk[4][20][1]*Vpk[4][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[4][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[4][20][0]))
          +(.000179*(Wpk[4][20][1]*Wpk[4][20][1])))));
        temp[4] = (temp[3]+(temp[2]+(temp[1]+(((3.32324136052*((Wpk[4][8][0]*
          Wpk[4][8][0])+(Wpk[4][8][2]*Wpk[4][8][2])))+((1.3552*(Wpk[4][8][2]*
          Wpk[4][8][2]))+((.7153*(Wpk[4][8][1]*Wpk[4][8][1]))+(1.396*(
          Wpk[4][8][0]*Wpk[4][8][0])))))+temp[0]))));
        temp[5] = (((8.806*((Vpk[4][23][2]*Vpk[4][23][2])+((Vpk[4][23][0]*
          Vpk[4][23][0])+(Vpk[4][23][1]*Vpk[4][23][1]))))+((.1337*(Wpk[4][23][2]
          *Wpk[4][23][2]))+((.0332*(Wpk[4][23][1]*Wpk[4][23][1]))+(.1268*(
          Wpk[4][23][0]*Wpk[4][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[4][26][2]*Vpk[4][26][2])+((Vpk[4][26][0]*
          Vpk[4][26][0])+(Vpk[4][26][1]*Vpk[4][26][1]))))+((.0484*(Wpk[4][26][2]
          *Wpk[4][26][2]))+((.0048*(Wpk[4][26][1]*Wpk[4][26][1]))+(.0477*(
          Wpk[4][26][0]*Wpk[4][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[4][29][2]*Vpk[4][29][2])+((Vpk[4][29][0]*
          Vpk[4][29][0])+(Vpk[4][29][1]*Vpk[4][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[4][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[4][29][0]))
          +(.003709*(Wpk[4][29][1]*Wpk[4][29][1])))))+temp[6]);
        mm[4][4] = (.0825+(((.205126*((Vpk[4][32][2]*Vpk[4][32][2])+((
          Vpk[4][32][0]*Vpk[4][32][0])+(Vpk[4][32][1]*Vpk[4][32][1]))))+((
          .000119*(Wpk[4][32][2]*Wpk[4][32][2]))+((.000117*(Wpk[4][32][0]*
          Wpk[4][32][0]))+(.000179*(Wpk[4][32][1]*Wpk[4][32][1])))))+temp[7]));
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[5][11][2])+((Vpk[4][11][0]*
          Vpk[5][11][0])+(Vpk[4][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[4][11][2]
          *Wpk[5][11][2]))+((.0332*(Wpk[4][11][1]*Wpk[5][11][1]))+(.1268*(
          Wpk[4][11][0]*Wpk[5][11][0])))));
        temp[1] = ((3.51*((Vpk[4][14][2]*Vpk[5][14][2])+((Vpk[4][14][0]*
          Vpk[5][14][0])+(Vpk[4][14][1]*Vpk[5][14][1]))))+((.0484*(Wpk[4][14][2]
          *Wpk[5][14][2]))+((.0048*(Wpk[4][14][1]*Wpk[5][14][1]))+(.0477*(
          Wpk[4][14][0]*Wpk[5][14][0])))));
        temp[2] = ((1.2*((Vpk[4][17][2]*Vpk[5][17][2])+((Vpk[4][17][0]*
          Vpk[5][17][0])+(Vpk[4][17][1]*Vpk[5][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[5][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[5][17][0]))
          +(.003709*(Wpk[4][17][1]*Wpk[5][17][1])))));
        temp[3] = ((.205126*((Vpk[4][20][2]*Vpk[5][20][2])+((Vpk[4][20][0]*
          Vpk[5][20][0])+(Vpk[4][20][1]*Vpk[5][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[5][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[5][20][0]))
          +(.000179*(Wpk[4][20][1]*Wpk[5][20][1])))));
        temp[4] = (temp[3]+(temp[2]+(temp[1]+(temp[0]+((10.3786426*((
          Vpk[5][8][2]*Wpk[4][8][0])-(Vpk[5][8][0]*Wpk[4][8][2])))+((1.3552*(
          Wpk[4][8][2]*Wpk[5][8][2]))+((.7153*(Wpk[4][8][1]*Wpk[5][8][1]))+(
          1.396*(Wpk[4][8][0]*Wpk[5][8][0])))))))));
        temp[5] = (((8.806*((Vpk[4][23][2]*Vpk[5][23][2])+((Vpk[4][23][0]*
          Vpk[5][23][0])+(Vpk[4][23][1]*Vpk[5][23][1]))))+((.1337*(Wpk[4][23][2]
          *Wpk[5][23][2]))+((.0332*(Wpk[4][23][1]*Wpk[5][23][1]))+(.1268*(
          Wpk[4][23][0]*Wpk[5][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[4][26][2]*Vpk[5][26][2])+((Vpk[4][26][0]*
          Vpk[5][26][0])+(Vpk[4][26][1]*Vpk[5][26][1]))))+((.0484*(Wpk[4][26][2]
          *Wpk[5][26][2]))+((.0048*(Wpk[4][26][1]*Wpk[5][26][1]))+(.0477*(
          Wpk[4][26][0]*Wpk[5][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[4][29][2]*Vpk[5][29][2])+((Vpk[4][29][0]*
          Vpk[5][29][0])+(Vpk[4][29][1]*Vpk[5][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[5][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[5][29][0]))
          +(.003709*(Wpk[4][29][1]*Wpk[5][29][1])))))+temp[6]);
        mm[4][5] = (((.205126*((Vpk[4][32][2]*Vpk[5][32][2])+((Vpk[4][32][0]*
          Vpk[5][32][0])+(Vpk[4][32][1]*Vpk[5][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[5][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[5][32][0]))
          +(.000179*(Wpk[4][32][1]*Wpk[5][32][1])))))+temp[7]);
        mm[4][6] = ((3.32324136052*((Wpk[4][8][0]*Wpk[6][8][0])+(Wpk[4][8][2]*
          Wpk[6][8][2])))+((1.3552*(Wpk[4][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[4][8][1]*Wpk[6][8][1]))+(1.396*(Wpk[4][8][0]*Wpk[6][8][0])))));
        mm[4][7] = ((3.32324136052*((Wpk[4][8][0]*Wpk[7][8][0])+(Wpk[4][8][2]*
          Wpk[7][8][2])))+((1.3552*(Wpk[4][8][2]*Wpk[7][8][2]))+((.7153*(
          Wpk[4][8][1]*Wpk[7][8][1]))+(1.396*(Wpk[4][8][0]*Wpk[7][8][0])))));
        mm[4][8] = ((3.32324136052*((pin[8][0]*Wpk[4][8][0])+(pin[8][2]*
          Wpk[4][8][2])))+((1.3552*(pin[8][2]*Wpk[4][8][2]))+((.7153*(pin[8][1]*
          Wpk[4][8][1]))+(1.396*(pin[8][0]*Wpk[4][8][0])))));
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[9][11][2])+((.1715*(Vpk[4][11][0]*
          Wpk[9][11][2]))-(.002*(Vpk[4][11][1]*Wpk[9][11][2])))))+((.1337*(
          Wpk[4][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[4][11][1]*Wpk[9][11][1]))+(
          .1268*(Wpk[4][11][0]*Wpk[9][11][0])))));
        temp[1] = (((3.51*((Vpk[4][14][2]*Vpk[9][14][2])+((Vpk[4][14][0]*
          Vpk[9][14][0])+(Vpk[4][14][1]*Vpk[9][14][1]))))+((.0484*(Wpk[4][14][2]
          *Wpk[9][14][2]))+((.0048*(Wpk[4][14][1]*Wpk[9][14][1]))+(.0477*(
          Wpk[4][14][0]*Wpk[9][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][17][2]*Vpk[9][17][2])+((Vpk[4][17][0]*
          Vpk[9][17][0])+(Vpk[4][17][1]*Vpk[9][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[9][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[9][17][0]))
          +(.003709*(Wpk[4][17][1]*Wpk[9][17][1])))))+temp[1]);
        mm[4][9] = (((.205126*((Vpk[4][20][2]*Vpk[9][20][2])+((Vpk[4][20][0]*
          Vpk[9][20][0])+(Vpk[4][20][1]*Vpk[9][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[9][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[9][20][0]))
          +(.000179*(Wpk[4][20][1]*Wpk[9][20][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[10][11][2])+((.1715*(Vpk[4][11][0]
          *Wpk[10][11][2]))-(.002*(Vpk[4][11][1]*Wpk[10][11][2])))))+((.1337*(
          Wpk[4][11][2]*Wpk[10][11][2]))+((.0332*(Wpk[4][11][1]*Wpk[10][11][1]))
          +(.1268*(Wpk[4][11][0]*Wpk[10][11][0])))));
        temp[1] = (((3.51*((Vpk[4][14][2]*Vpk[10][14][2])+((Vpk[4][14][0]*
          Vpk[10][14][0])+(Vpk[4][14][1]*Vpk[10][14][1]))))+((.0484*(
          Wpk[4][14][2]*Wpk[10][14][2]))+((.0048*(Wpk[4][14][1]*Wpk[10][14][1]))
          +(.0477*(Wpk[4][14][0]*Wpk[10][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][17][2]*Vpk[10][17][2])+((Vpk[4][17][0]*
          Vpk[10][17][0])+(Vpk[4][17][1]*Vpk[10][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[10][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[10][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[10][17][1])))))+temp[1]);
        mm[4][10] = (((.205126*((Vpk[4][20][2]*Vpk[10][20][2])+((Vpk[4][20][0]*
          Vpk[10][20][0])+(Vpk[4][20][1]*Vpk[10][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[10][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[10][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[10][20][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[4][14][2]*Vpk[11][14][2])+((Vpk[4][14][0]*
          Vpk[11][14][0])+(Vpk[4][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[4][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[4][14][1]*Wpk[11][14][1]))
          +(.0477*(Wpk[4][14][0]*Wpk[11][14][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[4][11][2]*Vpk[11][11][2])+((.1715*(
          pin[11][2]*Vpk[4][11][0]))-(.002*(pin[11][2]*Vpk[4][11][1])))))+((
          .1337*(pin[11][2]*Wpk[4][11][2]))+((.0332*(pin[11][1]*Wpk[4][11][1]))+
          (.1268*(pin[11][0]*Wpk[4][11][0]))))));
        temp[2] = (((1.2*((Vpk[4][17][2]*Vpk[11][17][2])+((Vpk[4][17][0]*
          Vpk[11][17][0])+(Vpk[4][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[11][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[11][17][1])))))+temp[1]);
        mm[4][11] = (((.205126*((Vpk[4][20][2]*Vpk[11][20][2])+((Vpk[4][20][0]*
          Vpk[11][20][0])+(Vpk[4][20][1]*Vpk[11][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[11][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[11][20][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[4][17][2]*Vpk[12][17][2])+((Vpk[4][17][0]*
          Vpk[12][17][0])+(Vpk[4][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[12][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[4][20][2]*Vpk[12][20][2])+((Vpk[4][20][0]*
          Vpk[12][20][0])+(Vpk[4][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[12][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[12][20][1])))));
        mm[4][12] = (temp[1]+(((.653562*((Vpk[4][14][0]*Wpk[12][14][2])-(
          Vpk[4][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[4][14][2]*Wpk[12][14][2])
          )+((.0048*(Wpk[4][14][1]*Wpk[12][14][1]))+(.0477*(Wpk[4][14][0]*
          Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[4][17][2]*Vpk[13][17][2])+((Vpk[4][17][0]*
          Vpk[13][17][0])+(Vpk[4][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[13][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[4][20][2]*Vpk[13][20][2])+((Vpk[4][20][0]*
          Vpk[13][20][0])+(Vpk[4][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[13][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[13][20][1])))));
        mm[4][13] = (temp[1]+(((.653562*((Vpk[4][14][0]*Wpk[13][14][2])-(
          Vpk[4][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[4][14][2]*Wpk[13][14][2])
          )+((.0048*(Wpk[4][14][1]*Wpk[13][14][1]))+(.0477*(Wpk[4][14][0]*
          Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[4][14][0])-(pin[14][0]*
          Vpk[4][14][2])))+((.0484*(pin[14][2]*Wpk[4][14][2]))+((.0048*(
          pin[14][1]*Wpk[4][14][1]))+(.0477*(pin[14][0]*Wpk[4][14][0])))))+((1.2
          *((Vpk[4][17][2]*Vpk[14][17][2])+((Vpk[4][17][0]*Vpk[14][17][0])+(
          Vpk[4][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[4][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[4][17][1]*Wpk[14][17][1]))))));
        mm[4][14] = (((.205126*((Vpk[4][20][2]*Vpk[14][20][2])+((Vpk[4][20][0]*
          Vpk[14][20][0])+(Vpk[4][20][1]*Vpk[14][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[14][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[14][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][17][2]*Vpk[15][17][2])+((Vpk[4][17][0]*
          Vpk[15][17][0])+(Vpk[4][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[15][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[15][17][1])))));
        mm[4][15] = (((.205126*((Vpk[4][20][2]*Vpk[15][20][2])+((Vpk[4][20][0]*
          Vpk[15][20][0])+(Vpk[4][20][1]*Vpk[15][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[15][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[15][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][17][2]*Vpk[16][17][2])+((Vpk[4][17][0]*
          Vpk[16][17][0])+(Vpk[4][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[4][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[4][17][0]*Wpk[16][17][0]
          ))+(.003709*(Wpk[4][17][1]*Wpk[16][17][1])))));
        mm[4][16] = (((.205126*((Vpk[4][20][2]*Vpk[16][20][2])+((Vpk[4][20][0]*
          Vpk[16][20][0])+(Vpk[4][20][1]*Vpk[16][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[16][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[16][20][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[4][20][2]*Vpk[17][20][2])+((Vpk[4][20][0]*
          Vpk[17][20][0])+(Vpk[4][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[17][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[17][20][1])))));
        mm[4][17] = (temp[0]+((1.2*((Vpk[4][17][2]*Vpk[17][17][2])+((
          Vpk[4][17][0]*Vpk[17][17][0])+(Vpk[4][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[4][17][2]))+((.001361*(pin[17][0]*
          Wpk[4][17][0]))+(.003709*(pin[17][1]*Wpk[4][17][1]))))));
        mm[4][18] = ((.205126*((Vpk[4][20][2]*Vpk[18][20][2])+((Vpk[4][20][0]*
          Vpk[18][20][0])+(Vpk[4][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[18][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[18][20][1])))));
        mm[4][19] = ((.205126*((Vpk[4][20][2]*Vpk[19][20][2])+((Vpk[4][20][0]*
          Vpk[19][20][0])+(Vpk[4][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[4][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[4][20][0]*Wpk[19][20][0]
          ))+(.000179*(Wpk[4][20][1]*Wpk[19][20][1])))));
        mm[4][20] = ((.205126*((Vpk[4][20][2]*Vpk[20][20][2])+((Vpk[4][20][0]*
          Vpk[20][20][0])+(Vpk[4][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[4][20][2]))+((.000117*(pin[20][0]*Wpk[4][20][0]))+(
          .000179*(pin[20][1]*Wpk[4][20][1])))));
        temp[0] = ((8.806*((Vpk[4][23][2]*Vpk[21][23][2])+((.1715*(Vpk[4][23][0]
          *Wpk[21][23][2]))-(.002*(Vpk[4][23][1]*Wpk[21][23][2])))))+((.1337*(
          Wpk[4][23][2]*Wpk[21][23][2]))+((.0332*(Wpk[4][23][1]*Wpk[21][23][1]))
          +(.1268*(Wpk[4][23][0]*Wpk[21][23][0])))));
        temp[1] = (((3.51*((Vpk[4][26][2]*Vpk[21][26][2])+((Vpk[4][26][0]*
          Vpk[21][26][0])+(Vpk[4][26][1]*Vpk[21][26][1]))))+((.0484*(
          Wpk[4][26][2]*Wpk[21][26][2]))+((.0048*(Wpk[4][26][1]*Wpk[21][26][1]))
          +(.0477*(Wpk[4][26][0]*Wpk[21][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][29][2]*Vpk[21][29][2])+((Vpk[4][29][0]*
          Vpk[21][29][0])+(Vpk[4][29][1]*Vpk[21][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[21][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[21][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[21][29][1])))))+temp[1]);
        mm[4][21] = (((.205126*((Vpk[4][32][2]*Vpk[21][32][2])+((Vpk[4][32][0]*
          Vpk[21][32][0])+(Vpk[4][32][1]*Vpk[21][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[21][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[21][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[21][32][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[4][23][2]*Vpk[22][23][2])+((.1715*(Vpk[4][23][0]
          *Wpk[22][23][2]))-(.002*(Vpk[4][23][1]*Wpk[22][23][2])))))+((.1337*(
          Wpk[4][23][2]*Wpk[22][23][2]))+((.0332*(Wpk[4][23][1]*Wpk[22][23][1]))
          +(.1268*(Wpk[4][23][0]*Wpk[22][23][0])))));
        temp[1] = (((3.51*((Vpk[4][26][2]*Vpk[22][26][2])+((Vpk[4][26][0]*
          Vpk[22][26][0])+(Vpk[4][26][1]*Vpk[22][26][1]))))+((.0484*(
          Wpk[4][26][2]*Wpk[22][26][2]))+((.0048*(Wpk[4][26][1]*Wpk[22][26][1]))
          +(.0477*(Wpk[4][26][0]*Wpk[22][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][29][2]*Vpk[22][29][2])+((Vpk[4][29][0]*
          Vpk[22][29][0])+(Vpk[4][29][1]*Vpk[22][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[22][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[22][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[22][29][1])))))+temp[1]);
        mm[4][22] = (((.205126*((Vpk[4][32][2]*Vpk[22][32][2])+((Vpk[4][32][0]*
          Vpk[22][32][0])+(Vpk[4][32][1]*Vpk[22][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[22][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[22][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[22][32][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[4][26][2]*Vpk[23][26][2])+((Vpk[4][26][0]*
          Vpk[23][26][0])+(Vpk[4][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[4][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[4][26][1]*Wpk[23][26][1]))
          +(.0477*(Wpk[4][26][0]*Wpk[23][26][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[4][23][2]*Vpk[23][23][2])+((.1715*(
          pin[23][2]*Vpk[4][23][0]))-(.002*(pin[23][2]*Vpk[4][23][1])))))+((
          .1337*(pin[23][2]*Wpk[4][23][2]))+((.0332*(pin[23][1]*Wpk[4][23][1]))+
          (.1268*(pin[23][0]*Wpk[4][23][0]))))));
        temp[2] = (((1.2*((Vpk[4][29][2]*Vpk[23][29][2])+((Vpk[4][29][0]*
          Vpk[23][29][0])+(Vpk[4][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[23][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[23][29][1])))))+temp[1]);
        mm[4][23] = (((.205126*((Vpk[4][32][2]*Vpk[23][32][2])+((Vpk[4][32][0]*
          Vpk[23][32][0])+(Vpk[4][32][1]*Vpk[23][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[23][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[23][32][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[4][29][2]*Vpk[24][29][2])+((Vpk[4][29][0]*
          Vpk[24][29][0])+(Vpk[4][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[24][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[4][32][2]*Vpk[24][32][2])+((Vpk[4][32][0]*
          Vpk[24][32][0])+(Vpk[4][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[24][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[24][32][1])))));
        mm[4][24] = (temp[1]+(((.653562*((Vpk[4][26][0]*Wpk[24][26][2])-(
          Vpk[4][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[4][26][2]*Wpk[24][26][2])
          )+((.0048*(Wpk[4][26][1]*Wpk[24][26][1]))+(.0477*(Wpk[4][26][0]*
          Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[4][29][2]*Vpk[25][29][2])+((Vpk[4][29][0]*
          Vpk[25][29][0])+(Vpk[4][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[25][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[4][32][2]*Vpk[25][32][2])+((Vpk[4][32][0]*
          Vpk[25][32][0])+(Vpk[4][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[25][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[25][32][1])))));
        mm[4][25] = (temp[1]+(((.653562*((Vpk[4][26][0]*Wpk[25][26][2])-(
          Vpk[4][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[4][26][2]*Wpk[25][26][2])
          )+((.0048*(Wpk[4][26][1]*Wpk[25][26][1]))+(.0477*(Wpk[4][26][0]*
          Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[4][26][0])-(pin[26][0]*
          Vpk[4][26][2])))+((.0484*(pin[26][2]*Wpk[4][26][2]))+((.0048*(
          pin[26][1]*Wpk[4][26][1]))+(.0477*(pin[26][0]*Wpk[4][26][0])))))+((1.2
          *((Vpk[4][29][2]*Vpk[26][29][2])+((Vpk[4][29][0]*Vpk[26][29][0])+(
          Vpk[4][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[4][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[4][29][1]*Wpk[26][29][1]))))));
        mm[4][26] = (((.205126*((Vpk[4][32][2]*Vpk[26][32][2])+((Vpk[4][32][0]*
          Vpk[26][32][0])+(Vpk[4][32][1]*Vpk[26][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[26][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[26][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][29][2]*Vpk[27][29][2])+((Vpk[4][29][0]*
          Vpk[27][29][0])+(Vpk[4][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[27][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[27][29][1])))));
        mm[4][27] = (((.205126*((Vpk[4][32][2]*Vpk[27][32][2])+((Vpk[4][32][0]*
          Vpk[27][32][0])+(Vpk[4][32][1]*Vpk[27][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[27][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[27][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][29][2]*Vpk[28][29][2])+((Vpk[4][29][0]*
          Vpk[28][29][0])+(Vpk[4][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[4][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[4][29][0]*Wpk[28][29][0]
          ))+(.003709*(Wpk[4][29][1]*Wpk[28][29][1])))));
        mm[4][28] = (((.205126*((Vpk[4][32][2]*Vpk[28][32][2])+((Vpk[4][32][0]*
          Vpk[28][32][0])+(Vpk[4][32][1]*Vpk[28][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[28][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[28][32][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[4][32][2]*Vpk[29][32][2])+((Vpk[4][32][0]*
          Vpk[29][32][0])+(Vpk[4][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[29][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[29][32][1])))));
        mm[4][29] = (temp[0]+((1.2*((Vpk[4][29][2]*Vpk[29][29][2])+((
          Vpk[4][29][0]*Vpk[29][29][0])+(Vpk[4][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[4][29][2]))+((.001361*(pin[29][0]*
          Wpk[4][29][0]))+(.003709*(pin[29][1]*Wpk[4][29][1]))))));
        mm[4][30] = ((.205126*((Vpk[4][32][2]*Vpk[30][32][2])+((Vpk[4][32][0]*
          Vpk[30][32][0])+(Vpk[4][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[30][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[30][32][1])))));
        mm[4][31] = ((.205126*((Vpk[4][32][2]*Vpk[31][32][2])+((Vpk[4][32][0]*
          Vpk[31][32][0])+(Vpk[4][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[4][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[4][32][0]*Wpk[31][32][0]
          ))+(.000179*(Wpk[4][32][1]*Wpk[31][32][1])))));
        mm[4][32] = ((.205126*((Vpk[4][32][2]*Vpk[32][32][2])+((Vpk[4][32][0]*
          Vpk[32][32][0])+(Vpk[4][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[4][32][2]))+((.000117*(pin[32][0]*Wpk[4][32][0]))+(
          .000179*(pin[32][1]*Wpk[4][32][1])))));
        temp[0] = ((32.413*((Vpk[5][8][2]*Vpk[5][8][2])+((Vpk[5][8][0]*
          Vpk[5][8][0])+(Vpk[5][8][1]*Vpk[5][8][1]))))+((1.3552*(Wpk[5][8][2]*
          Wpk[5][8][2]))+((.7153*(Wpk[5][8][1]*Wpk[5][8][1]))+(1.396*(
          Wpk[5][8][0]*Wpk[5][8][0])))));
        temp[1] = (((8.806*((Vpk[5][11][2]*Vpk[5][11][2])+((Vpk[5][11][0]*
          Vpk[5][11][0])+(Vpk[5][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[5][11][2]
          *Wpk[5][11][2]))+((.0332*(Wpk[5][11][1]*Wpk[5][11][1]))+(.1268*(
          Wpk[5][11][0]*Wpk[5][11][0])))))+temp[0]);
        temp[2] = (((3.51*((Vpk[5][14][2]*Vpk[5][14][2])+((Vpk[5][14][0]*
          Vpk[5][14][0])+(Vpk[5][14][1]*Vpk[5][14][1]))))+((.0484*(Wpk[5][14][2]
          *Wpk[5][14][2]))+((.0048*(Wpk[5][14][1]*Wpk[5][14][1]))+(.0477*(
          Wpk[5][14][0]*Wpk[5][14][0])))))+temp[1]);
        temp[3] = (((1.2*((Vpk[5][17][2]*Vpk[5][17][2])+((Vpk[5][17][0]*
          Vpk[5][17][0])+(Vpk[5][17][1]*Vpk[5][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[5][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[5][17][0]))
          +(.003709*(Wpk[5][17][1]*Wpk[5][17][1])))))+temp[2]);
        temp[4] = (((.205126*((Vpk[5][20][2]*Vpk[5][20][2])+((Vpk[5][20][0]*
          Vpk[5][20][0])+(Vpk[5][20][1]*Vpk[5][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[5][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[5][20][0]))
          +(.000179*(Wpk[5][20][1]*Wpk[5][20][1])))))+temp[3]);
        temp[5] = (((8.806*((Vpk[5][23][2]*Vpk[5][23][2])+((Vpk[5][23][0]*
          Vpk[5][23][0])+(Vpk[5][23][1]*Vpk[5][23][1]))))+((.1337*(Wpk[5][23][2]
          *Wpk[5][23][2]))+((.0332*(Wpk[5][23][1]*Wpk[5][23][1]))+(.1268*(
          Wpk[5][23][0]*Wpk[5][23][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[5][26][2]*Vpk[5][26][2])+((Vpk[5][26][0]*
          Vpk[5][26][0])+(Vpk[5][26][1]*Vpk[5][26][1]))))+((.0484*(Wpk[5][26][2]
          *Wpk[5][26][2]))+((.0048*(Wpk[5][26][1]*Wpk[5][26][1]))+(.0477*(
          Wpk[5][26][0]*Wpk[5][26][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[5][29][2]*Vpk[5][29][2])+((Vpk[5][29][0]*
          Vpk[5][29][0])+(Vpk[5][29][1]*Vpk[5][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[5][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[5][29][0]))
          +(.003709*(Wpk[5][29][1]*Wpk[5][29][1])))))+temp[6]);
        mm[5][5] = (.0548+(((.205126*((Vpk[5][32][2]*Vpk[5][32][2])+((
          Vpk[5][32][0]*Vpk[5][32][0])+(Vpk[5][32][1]*Vpk[5][32][1]))))+((
          .000119*(Wpk[5][32][2]*Wpk[5][32][2]))+((.000117*(Wpk[5][32][0]*
          Wpk[5][32][0]))+(.000179*(Wpk[5][32][1]*Wpk[5][32][1])))))+temp[7]));
        mm[5][6] = ((10.3786426*((Vpk[5][8][2]*Wpk[6][8][0])-(Vpk[5][8][0]*
          Wpk[6][8][2])))+((1.3552*(Wpk[5][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[5][8][1]*Wpk[6][8][1]))+(1.396*(Wpk[5][8][0]*Wpk[6][8][0])))));
        mm[5][7] = ((10.3786426*((Vpk[5][8][2]*Wpk[7][8][0])-(Vpk[5][8][0]*
          Wpk[7][8][2])))+((1.3552*(Wpk[5][8][2]*Wpk[7][8][2]))+((.7153*(
          Wpk[5][8][1]*Wpk[7][8][1]))+(1.396*(Wpk[5][8][0]*Wpk[7][8][0])))));
        mm[5][8] = ((10.3786426*((pin[8][0]*Vpk[5][8][2])-(pin[8][2]*
          Vpk[5][8][0])))+((1.3552*(pin[8][2]*Wpk[5][8][2]))+((.7153*(pin[8][1]*
          Wpk[5][8][1]))+(1.396*(pin[8][0]*Wpk[5][8][0])))));
        temp[0] = ((8.806*((Vpk[5][11][2]*Vpk[9][11][2])+((.1715*(Vpk[5][11][0]*
          Wpk[9][11][2]))-(.002*(Vpk[5][11][1]*Wpk[9][11][2])))))+((.1337*(
          Wpk[5][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[5][11][1]*Wpk[9][11][1]))+(
          .1268*(Wpk[5][11][0]*Wpk[9][11][0])))));
        temp[1] = (((3.51*((Vpk[5][14][2]*Vpk[9][14][2])+((Vpk[5][14][0]*
          Vpk[9][14][0])+(Vpk[5][14][1]*Vpk[9][14][1]))))+((.0484*(Wpk[5][14][2]
          *Wpk[9][14][2]))+((.0048*(Wpk[5][14][1]*Wpk[9][14][1]))+(.0477*(
          Wpk[5][14][0]*Wpk[9][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[5][17][2]*Vpk[9][17][2])+((Vpk[5][17][0]*
          Vpk[9][17][0])+(Vpk[5][17][1]*Vpk[9][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[9][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[9][17][0]))
          +(.003709*(Wpk[5][17][1]*Wpk[9][17][1])))))+temp[1]);
        mm[5][9] = (((.205126*((Vpk[5][20][2]*Vpk[9][20][2])+((Vpk[5][20][0]*
          Vpk[9][20][0])+(Vpk[5][20][1]*Vpk[9][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[9][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[9][20][0]))
          +(.000179*(Wpk[5][20][1]*Wpk[9][20][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[5][11][2]*Vpk[10][11][2])+((.1715*(Vpk[5][11][0]
          *Wpk[10][11][2]))-(.002*(Vpk[5][11][1]*Wpk[10][11][2])))))+((.1337*(
          Wpk[5][11][2]*Wpk[10][11][2]))+((.0332*(Wpk[5][11][1]*Wpk[10][11][1]))
          +(.1268*(Wpk[5][11][0]*Wpk[10][11][0])))));
        temp[1] = (((3.51*((Vpk[5][14][2]*Vpk[10][14][2])+((Vpk[5][14][0]*
          Vpk[10][14][0])+(Vpk[5][14][1]*Vpk[10][14][1]))))+((.0484*(
          Wpk[5][14][2]*Wpk[10][14][2]))+((.0048*(Wpk[5][14][1]*Wpk[10][14][1]))
          +(.0477*(Wpk[5][14][0]*Wpk[10][14][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[5][17][2]*Vpk[10][17][2])+((Vpk[5][17][0]*
          Vpk[10][17][0])+(Vpk[5][17][1]*Vpk[10][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[10][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[10][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[10][17][1])))))+temp[1]);
        mm[5][10] = (((.205126*((Vpk[5][20][2]*Vpk[10][20][2])+((Vpk[5][20][0]*
          Vpk[10][20][0])+(Vpk[5][20][1]*Vpk[10][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[10][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[10][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[10][20][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[5][14][2]*Vpk[11][14][2])+((Vpk[5][14][0]*
          Vpk[11][14][0])+(Vpk[5][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[5][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[5][14][1]*Wpk[11][14][1]))
          +(.0477*(Wpk[5][14][0]*Wpk[11][14][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[5][11][2]*Vpk[11][11][2])+((.1715*(
          pin[11][2]*Vpk[5][11][0]))-(.002*(pin[11][2]*Vpk[5][11][1])))))+((
          .1337*(pin[11][2]*Wpk[5][11][2]))+((.0332*(pin[11][1]*Wpk[5][11][1]))+
          (.1268*(pin[11][0]*Wpk[5][11][0]))))));
        temp[2] = (((1.2*((Vpk[5][17][2]*Vpk[11][17][2])+((Vpk[5][17][0]*
          Vpk[11][17][0])+(Vpk[5][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[11][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[11][17][1])))))+temp[1]);
        mm[5][11] = (((.205126*((Vpk[5][20][2]*Vpk[11][20][2])+((Vpk[5][20][0]*
          Vpk[11][20][0])+(Vpk[5][20][1]*Vpk[11][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[11][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[11][20][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[5][17][2]*Vpk[12][17][2])+((Vpk[5][17][0]*
          Vpk[12][17][0])+(Vpk[5][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[12][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[5][20][2]*Vpk[12][20][2])+((Vpk[5][20][0]*
          Vpk[12][20][0])+(Vpk[5][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[12][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[12][20][1])))));
        mm[5][12] = (temp[1]+(((.653562*((Vpk[5][14][0]*Wpk[12][14][2])-(
          Vpk[5][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[5][14][2]*Wpk[12][14][2])
          )+((.0048*(Wpk[5][14][1]*Wpk[12][14][1]))+(.0477*(Wpk[5][14][0]*
          Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[5][17][2]*Vpk[13][17][2])+((Vpk[5][17][0]*
          Vpk[13][17][0])+(Vpk[5][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[13][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[5][20][2]*Vpk[13][20][2])+((Vpk[5][20][0]*
          Vpk[13][20][0])+(Vpk[5][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[13][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[13][20][1])))));
        mm[5][13] = (temp[1]+(((.653562*((Vpk[5][14][0]*Wpk[13][14][2])-(
          Vpk[5][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[5][14][2]*Wpk[13][14][2])
          )+((.0048*(Wpk[5][14][1]*Wpk[13][14][1]))+(.0477*(Wpk[5][14][0]*
          Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[5][14][0])-(pin[14][0]*
          Vpk[5][14][2])))+((.0484*(pin[14][2]*Wpk[5][14][2]))+((.0048*(
          pin[14][1]*Wpk[5][14][1]))+(.0477*(pin[14][0]*Wpk[5][14][0])))))+((1.2
          *((Vpk[5][17][2]*Vpk[14][17][2])+((Vpk[5][17][0]*Vpk[14][17][0])+(
          Vpk[5][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[5][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[5][17][1]*Wpk[14][17][1]))))));
        mm[5][14] = (((.205126*((Vpk[5][20][2]*Vpk[14][20][2])+((Vpk[5][20][0]*
          Vpk[14][20][0])+(Vpk[5][20][1]*Vpk[14][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[14][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[14][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][17][2]*Vpk[15][17][2])+((Vpk[5][17][0]*
          Vpk[15][17][0])+(Vpk[5][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[15][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[15][17][1])))));
        mm[5][15] = (((.205126*((Vpk[5][20][2]*Vpk[15][20][2])+((Vpk[5][20][0]*
          Vpk[15][20][0])+(Vpk[5][20][1]*Vpk[15][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[15][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[15][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][17][2]*Vpk[16][17][2])+((Vpk[5][17][0]*
          Vpk[16][17][0])+(Vpk[5][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[5][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[5][17][0]*Wpk[16][17][0]
          ))+(.003709*(Wpk[5][17][1]*Wpk[16][17][1])))));
        mm[5][16] = (((.205126*((Vpk[5][20][2]*Vpk[16][20][2])+((Vpk[5][20][0]*
          Vpk[16][20][0])+(Vpk[5][20][1]*Vpk[16][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[16][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[16][20][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[5][20][2]*Vpk[17][20][2])+((Vpk[5][20][0]*
          Vpk[17][20][0])+(Vpk[5][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[17][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[17][20][1])))));
        mm[5][17] = (temp[0]+((1.2*((Vpk[5][17][2]*Vpk[17][17][2])+((
          Vpk[5][17][0]*Vpk[17][17][0])+(Vpk[5][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[5][17][2]))+((.001361*(pin[17][0]*
          Wpk[5][17][0]))+(.003709*(pin[17][1]*Wpk[5][17][1]))))));
        mm[5][18] = ((.205126*((Vpk[5][20][2]*Vpk[18][20][2])+((Vpk[5][20][0]*
          Vpk[18][20][0])+(Vpk[5][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[18][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[18][20][1])))));
        mm[5][19] = ((.205126*((Vpk[5][20][2]*Vpk[19][20][2])+((Vpk[5][20][0]*
          Vpk[19][20][0])+(Vpk[5][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[5][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[5][20][0]*Wpk[19][20][0]
          ))+(.000179*(Wpk[5][20][1]*Wpk[19][20][1])))));
        mm[5][20] = ((.205126*((Vpk[5][20][2]*Vpk[20][20][2])+((Vpk[5][20][0]*
          Vpk[20][20][0])+(Vpk[5][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[5][20][2]))+((.000117*(pin[20][0]*Wpk[5][20][0]))+(
          .000179*(pin[20][1]*Wpk[5][20][1])))));
        temp[0] = ((8.806*((Vpk[5][23][2]*Vpk[21][23][2])+((.1715*(Vpk[5][23][0]
          *Wpk[21][23][2]))-(.002*(Vpk[5][23][1]*Wpk[21][23][2])))))+((.1337*(
          Wpk[5][23][2]*Wpk[21][23][2]))+((.0332*(Wpk[5][23][1]*Wpk[21][23][1]))
          +(.1268*(Wpk[5][23][0]*Wpk[21][23][0])))));
        temp[1] = (((3.51*((Vpk[5][26][2]*Vpk[21][26][2])+((Vpk[5][26][0]*
          Vpk[21][26][0])+(Vpk[5][26][1]*Vpk[21][26][1]))))+((.0484*(
          Wpk[5][26][2]*Wpk[21][26][2]))+((.0048*(Wpk[5][26][1]*Wpk[21][26][1]))
          +(.0477*(Wpk[5][26][0]*Wpk[21][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[5][29][2]*Vpk[21][29][2])+((Vpk[5][29][0]*
          Vpk[21][29][0])+(Vpk[5][29][1]*Vpk[21][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[21][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[21][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[21][29][1])))))+temp[1]);
        mm[5][21] = (((.205126*((Vpk[5][32][2]*Vpk[21][32][2])+((Vpk[5][32][0]*
          Vpk[21][32][0])+(Vpk[5][32][1]*Vpk[21][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[21][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[21][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[21][32][1])))))+temp[2]);
        temp[0] = ((8.806*((Vpk[5][23][2]*Vpk[22][23][2])+((.1715*(Vpk[5][23][0]
          *Wpk[22][23][2]))-(.002*(Vpk[5][23][1]*Wpk[22][23][2])))))+((.1337*(
          Wpk[5][23][2]*Wpk[22][23][2]))+((.0332*(Wpk[5][23][1]*Wpk[22][23][1]))
          +(.1268*(Wpk[5][23][0]*Wpk[22][23][0])))));
        temp[1] = (((3.51*((Vpk[5][26][2]*Vpk[22][26][2])+((Vpk[5][26][0]*
          Vpk[22][26][0])+(Vpk[5][26][1]*Vpk[22][26][1]))))+((.0484*(
          Wpk[5][26][2]*Wpk[22][26][2]))+((.0048*(Wpk[5][26][1]*Wpk[22][26][1]))
          +(.0477*(Wpk[5][26][0]*Wpk[22][26][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[5][29][2]*Vpk[22][29][2])+((Vpk[5][29][0]*
          Vpk[22][29][0])+(Vpk[5][29][1]*Vpk[22][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[22][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[22][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[22][29][1])))))+temp[1]);
        mm[5][22] = (((.205126*((Vpk[5][32][2]*Vpk[22][32][2])+((Vpk[5][32][0]*
          Vpk[22][32][0])+(Vpk[5][32][1]*Vpk[22][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[22][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[22][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[22][32][1])))))+temp[2]);
        temp[0] = ((3.51*((Vpk[5][26][2]*Vpk[23][26][2])+((Vpk[5][26][0]*
          Vpk[23][26][0])+(Vpk[5][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[5][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[5][26][1]*Wpk[23][26][1]))
          +(.0477*(Wpk[5][26][0]*Wpk[23][26][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[5][23][2]*Vpk[23][23][2])+((.1715*(
          pin[23][2]*Vpk[5][23][0]))-(.002*(pin[23][2]*Vpk[5][23][1])))))+((
          .1337*(pin[23][2]*Wpk[5][23][2]))+((.0332*(pin[23][1]*Wpk[5][23][1]))+
          (.1268*(pin[23][0]*Wpk[5][23][0]))))));
        temp[2] = (((1.2*((Vpk[5][29][2]*Vpk[23][29][2])+((Vpk[5][29][0]*
          Vpk[23][29][0])+(Vpk[5][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[23][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[23][29][1])))))+temp[1]);
        mm[5][23] = (((.205126*((Vpk[5][32][2]*Vpk[23][32][2])+((Vpk[5][32][0]*
          Vpk[23][32][0])+(Vpk[5][32][1]*Vpk[23][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[23][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[23][32][1])))))+temp[2]);
        temp[0] = ((1.2*((Vpk[5][29][2]*Vpk[24][29][2])+((Vpk[5][29][0]*
          Vpk[24][29][0])+(Vpk[5][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[24][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[5][32][2]*Vpk[24][32][2])+((Vpk[5][32][0]*
          Vpk[24][32][0])+(Vpk[5][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[24][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[24][32][1])))));
        mm[5][24] = (temp[1]+(((.653562*((Vpk[5][26][0]*Wpk[24][26][2])-(
          Vpk[5][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[5][26][2]*Wpk[24][26][2])
          )+((.0048*(Wpk[5][26][1]*Wpk[24][26][1]))+(.0477*(Wpk[5][26][0]*
          Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[5][29][2]*Vpk[25][29][2])+((Vpk[5][29][0]*
          Vpk[25][29][0])+(Vpk[5][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[25][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[5][32][2]*Vpk[25][32][2])+((Vpk[5][32][0]*
          Vpk[25][32][0])+(Vpk[5][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[25][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[25][32][1])))));
        mm[5][25] = (temp[1]+(((.653562*((Vpk[5][26][0]*Wpk[25][26][2])-(
          Vpk[5][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[5][26][2]*Wpk[25][26][2])
          )+((.0048*(Wpk[5][26][1]*Wpk[25][26][1]))+(.0477*(Wpk[5][26][0]*
          Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[5][26][0])-(pin[26][0]*
          Vpk[5][26][2])))+((.0484*(pin[26][2]*Wpk[5][26][2]))+((.0048*(
          pin[26][1]*Wpk[5][26][1]))+(.0477*(pin[26][0]*Wpk[5][26][0])))))+((1.2
          *((Vpk[5][29][2]*Vpk[26][29][2])+((Vpk[5][29][0]*Vpk[26][29][0])+(
          Vpk[5][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[5][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[5][29][1]*Wpk[26][29][1]))))));
        mm[5][26] = (((.205126*((Vpk[5][32][2]*Vpk[26][32][2])+((Vpk[5][32][0]*
          Vpk[26][32][0])+(Vpk[5][32][1]*Vpk[26][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[26][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[26][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][29][2]*Vpk[27][29][2])+((Vpk[5][29][0]*
          Vpk[27][29][0])+(Vpk[5][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[27][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[27][29][1])))));
        mm[5][27] = (((.205126*((Vpk[5][32][2]*Vpk[27][32][2])+((Vpk[5][32][0]*
          Vpk[27][32][0])+(Vpk[5][32][1]*Vpk[27][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[27][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[27][32][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][29][2]*Vpk[28][29][2])+((Vpk[5][29][0]*
          Vpk[28][29][0])+(Vpk[5][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[5][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[5][29][0]*Wpk[28][29][0]
          ))+(.003709*(Wpk[5][29][1]*Wpk[28][29][1])))));
        mm[5][28] = (((.205126*((Vpk[5][32][2]*Vpk[28][32][2])+((Vpk[5][32][0]*
          Vpk[28][32][0])+(Vpk[5][32][1]*Vpk[28][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[28][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[28][32][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[5][32][2]*Vpk[29][32][2])+((Vpk[5][32][0]*
          Vpk[29][32][0])+(Vpk[5][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[29][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[29][32][1])))));
        mm[5][29] = (temp[0]+((1.2*((Vpk[5][29][2]*Vpk[29][29][2])+((
          Vpk[5][29][0]*Vpk[29][29][0])+(Vpk[5][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[5][29][2]))+((.001361*(pin[29][0]*
          Wpk[5][29][0]))+(.003709*(pin[29][1]*Wpk[5][29][1]))))));
        mm[5][30] = ((.205126*((Vpk[5][32][2]*Vpk[30][32][2])+((Vpk[5][32][0]*
          Vpk[30][32][0])+(Vpk[5][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[30][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[30][32][1])))));
        mm[5][31] = ((.205126*((Vpk[5][32][2]*Vpk[31][32][2])+((Vpk[5][32][0]*
          Vpk[31][32][0])+(Vpk[5][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[5][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[5][32][0]*Wpk[31][32][0]
          ))+(.000179*(Wpk[5][32][1]*Wpk[31][32][1])))));
        mm[5][32] = ((.205126*((Vpk[5][32][2]*Vpk[32][32][2])+((Vpk[5][32][0]*
          Vpk[32][32][0])+(Vpk[5][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[5][32][2]))+((.000117*(pin[32][0]*Wpk[5][32][0]))+(
          .000179*(pin[32][1]*Wpk[5][32][1])))));
        mm[6][6] = ((3.32324136052*((Wpk[6][8][0]*Wpk[6][8][0])+(Wpk[6][8][2]*
          Wpk[6][8][2])))+((1.3552*(Wpk[6][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[6][8][1]*Wpk[6][8][1]))+(1.396*(Wpk[6][8][0]*Wpk[6][8][0])))));
        mm[6][7] = ((3.32324136052*((Wpk[6][8][0]*Wpk[7][8][0])+(Wpk[6][8][2]*
          Wpk[7][8][2])))+((1.3552*(Wpk[6][8][2]*Wpk[7][8][2]))+((.7153*(
          Wpk[6][8][1]*Wpk[7][8][1]))+(1.396*(Wpk[6][8][0]*Wpk[7][8][0])))));
        mm[6][8] = ((3.32324136052*((pin[8][0]*Wpk[6][8][0])+(pin[8][2]*
          Wpk[6][8][2])))+((1.3552*(pin[8][2]*Wpk[6][8][2]))+((.7153*(pin[8][1]*
          Wpk[6][8][1]))+(1.396*(pin[8][0]*Wpk[6][8][0])))));
        mm[6][9] = 0.;
        mm[6][10] = 0.;
        mm[6][11] = 0.;
        mm[6][12] = 0.;
        mm[6][13] = 0.;
        mm[6][14] = 0.;
        mm[6][15] = 0.;
        mm[6][16] = 0.;
        mm[6][17] = 0.;
        mm[6][18] = 0.;
        mm[6][19] = 0.;
        mm[6][20] = 0.;
        mm[6][21] = 0.;
        mm[6][22] = 0.;
        mm[6][23] = 0.;
        mm[6][24] = 0.;
        mm[6][25] = 0.;
        mm[6][26] = 0.;
        mm[6][27] = 0.;
        mm[6][28] = 0.;
        mm[6][29] = 0.;
        mm[6][30] = 0.;
        mm[6][31] = 0.;
        mm[6][32] = 0.;
        mm[7][7] = ((3.32324136052*((Wpk[7][8][0]*Wpk[7][8][0])+(Wpk[7][8][2]*
          Wpk[7][8][2])))+((1.3552*(Wpk[7][8][2]*Wpk[7][8][2]))+((.7153*(
          Wpk[7][8][1]*Wpk[7][8][1]))+(1.396*(Wpk[7][8][0]*Wpk[7][8][0])))));
        mm[7][8] = ((3.32324136052*((pin[8][0]*Wpk[7][8][0])+(pin[8][2]*
          Wpk[7][8][2])))+((1.3552*(pin[8][2]*Wpk[7][8][2]))+((.7153*(pin[8][1]*
          Wpk[7][8][1]))+(1.396*(pin[8][0]*Wpk[7][8][0])))));
        mm[7][9] = 0.;
        mm[7][10] = 0.;
        mm[7][11] = 0.;
        mm[7][12] = 0.;
        mm[7][13] = 0.;
        mm[7][14] = 0.;
        mm[7][15] = 0.;
        mm[7][16] = 0.;
        mm[7][17] = 0.;
        mm[7][18] = 0.;
        mm[7][19] = 0.;
        mm[7][20] = 0.;
        mm[7][21] = 0.;
        mm[7][22] = 0.;
        mm[7][23] = 0.;
        mm[7][24] = 0.;
        mm[7][25] = 0.;
        mm[7][26] = 0.;
        mm[7][27] = 0.;
        mm[7][28] = 0.;
        mm[7][29] = 0.;
        mm[7][30] = 0.;
        mm[7][31] = 0.;
        mm[7][32] = 0.;
        mm[8][8] = ((3.32324136052*((pin[8][0]*pin[8][0])+(pin[8][2]*pin[8][2]))
          )+((1.3552*(pin[8][2]*pin[8][2]))+((.7153*(pin[8][1]*pin[8][1]))+(
          1.396*(pin[8][0]*pin[8][0])))));
        mm[8][9] = 0.;
        mm[8][10] = 0.;
        mm[8][11] = 0.;
        mm[8][12] = 0.;
        mm[8][13] = 0.;
        mm[8][14] = 0.;
        mm[8][15] = 0.;
        mm[8][16] = 0.;
        mm[8][17] = 0.;
        mm[8][18] = 0.;
        mm[8][19] = 0.;
        mm[8][20] = 0.;
        mm[8][21] = 0.;
        mm[8][22] = 0.;
        mm[8][23] = 0.;
        mm[8][24] = 0.;
        mm[8][25] = 0.;
        mm[8][26] = 0.;
        mm[8][27] = 0.;
        mm[8][28] = 0.;
        mm[8][29] = 0.;
        mm[8][30] = 0.;
        mm[8][31] = 0.;
        mm[8][32] = 0.;
        temp[0] = ((3.51*((Vpk[9][14][2]*Vpk[9][14][2])+((Vpk[9][14][0]*
          Vpk[9][14][0])+(Vpk[9][14][1]*Vpk[9][14][1]))))+((.0484*(Wpk[9][14][2]
          *Wpk[9][14][2]))+((.0048*(Wpk[9][14][1]*Wpk[9][14][1]))+(.0477*(
          Wpk[9][14][0]*Wpk[9][14][0])))));
        temp[1] = ((1.2*((Vpk[9][17][2]*Vpk[9][17][2])+((Vpk[9][17][0]*
          Vpk[9][17][0])+(Vpk[9][17][1]*Vpk[9][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[9][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[9][17][0]))
          +(.003709*(Wpk[9][17][1]*Wpk[9][17][1])))));
        temp[2] = ((.205126*((Vpk[9][20][2]*Vpk[9][20][2])+((Vpk[9][20][0]*
          Vpk[9][20][0])+(Vpk[9][20][1]*Vpk[9][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[9][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[9][20][0]))
          +(.000179*(Wpk[9][20][1]*Wpk[9][20][1])))));
        mm[9][9] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(Wpk[9][11][2]
          *Wpk[9][11][2]))+(Vpk[9][11][2]*Vpk[9][11][2])))+((.1337*(
          Wpk[9][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[9][11][1]*Wpk[9][11][1]))+(
          .1268*(Wpk[9][11][0]*Wpk[9][11][0]))))))));
        temp[0] = ((3.51*((Vpk[9][14][2]*Vpk[10][14][2])+((Vpk[9][14][0]*
          Vpk[10][14][0])+(Vpk[9][14][1]*Vpk[10][14][1]))))+((.0484*(
          Wpk[9][14][2]*Wpk[10][14][2]))+((.0048*(Wpk[9][14][1]*Wpk[10][14][1]))
          +(.0477*(Wpk[9][14][0]*Wpk[10][14][0])))));
        temp[1] = ((1.2*((Vpk[9][17][2]*Vpk[10][17][2])+((Vpk[9][17][0]*
          Vpk[10][17][0])+(Vpk[9][17][1]*Vpk[10][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[10][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[10][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[10][17][1])))));
        temp[2] = ((.205126*((Vpk[9][20][2]*Vpk[10][20][2])+((Vpk[9][20][0]*
          Vpk[10][20][0])+(Vpk[9][20][1]*Vpk[10][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[10][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[10][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[10][20][1])))));
        mm[9][10] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(
          Wpk[9][11][2]*Wpk[10][11][2]))+(Vpk[9][11][2]*Vpk[10][11][2])))+((
          .1337*(Wpk[9][11][2]*Wpk[10][11][2]))+((.0332*(Wpk[9][11][1]*
          Wpk[10][11][1]))+(.1268*(Wpk[9][11][0]*Wpk[10][11][0]))))))));
        temp[0] = ((3.51*((Vpk[9][14][2]*Vpk[11][14][2])+((Vpk[9][14][0]*
          Vpk[11][14][0])+(Vpk[9][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[9][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[9][14][1]*Wpk[11][14][1]))
          +(.0477*(Wpk[9][14][0]*Wpk[11][14][0])))));
        temp[1] = ((1.2*((Vpk[9][17][2]*Vpk[11][17][2])+((Vpk[9][17][0]*
          Vpk[11][17][0])+(Vpk[9][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[11][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[11][17][1])))));
        temp[2] = ((.205126*((Vpk[9][20][2]*Vpk[11][20][2])+((Vpk[9][20][0]*
          Vpk[11][20][0])+(Vpk[9][20][1]*Vpk[11][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[11][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[11][20][1])))));
        mm[9][11] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(pin[11][2]*
          Wpk[9][11][2]))+(Vpk[9][11][2]*Vpk[11][11][2])))+((.1337*(pin[11][2]*
          Wpk[9][11][2]))+((.0332*(pin[11][1]*Wpk[9][11][1]))+(.1268*(pin[11][0]
          *Wpk[9][11][0]))))))));
        temp[0] = ((1.2*((Vpk[9][17][2]*Vpk[12][17][2])+((Vpk[9][17][0]*
          Vpk[12][17][0])+(Vpk[9][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[12][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[9][20][2]*Vpk[12][20][2])+((Vpk[9][20][0]*
          Vpk[12][20][0])+(Vpk[9][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[12][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[12][20][1])))));
        mm[9][12] = (temp[1]+(((.653562*((Vpk[9][14][0]*Wpk[12][14][2])-(
          Vpk[9][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[9][14][2]*Wpk[12][14][2])
          )+((.0048*(Wpk[9][14][1]*Wpk[12][14][1]))+(.0477*(Wpk[9][14][0]*
          Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[9][17][2]*Vpk[13][17][2])+((Vpk[9][17][0]*
          Vpk[13][17][0])+(Vpk[9][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[13][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[9][20][2]*Vpk[13][20][2])+((Vpk[9][20][0]*
          Vpk[13][20][0])+(Vpk[9][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[13][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[13][20][1])))));
        mm[9][13] = (temp[1]+(((.653562*((Vpk[9][14][0]*Wpk[13][14][2])-(
          Vpk[9][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[9][14][2]*Wpk[13][14][2])
          )+((.0048*(Wpk[9][14][1]*Wpk[13][14][1]))+(.0477*(Wpk[9][14][0]*
          Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[9][14][0])-(pin[14][0]*
          Vpk[9][14][2])))+((.0484*(pin[14][2]*Wpk[9][14][2]))+((.0048*(
          pin[14][1]*Wpk[9][14][1]))+(.0477*(pin[14][0]*Wpk[9][14][0])))))+((1.2
          *((Vpk[9][17][2]*Vpk[14][17][2])+((Vpk[9][17][0]*Vpk[14][17][0])+(
          Vpk[9][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[9][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[9][17][1]*Wpk[14][17][1]))))));
        mm[9][14] = (((.205126*((Vpk[9][20][2]*Vpk[14][20][2])+((Vpk[9][20][0]*
          Vpk[14][20][0])+(Vpk[9][20][1]*Vpk[14][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[14][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[14][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[9][17][2]*Vpk[15][17][2])+((Vpk[9][17][0]*
          Vpk[15][17][0])+(Vpk[9][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[15][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[15][17][1])))));
        mm[9][15] = (((.205126*((Vpk[9][20][2]*Vpk[15][20][2])+((Vpk[9][20][0]*
          Vpk[15][20][0])+(Vpk[9][20][1]*Vpk[15][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[15][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[15][20][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[9][17][2]*Vpk[16][17][2])+((Vpk[9][17][0]*
          Vpk[16][17][0])+(Vpk[9][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[9][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[9][17][0]*Wpk[16][17][0]
          ))+(.003709*(Wpk[9][17][1]*Wpk[16][17][1])))));
        mm[9][16] = (((.205126*((Vpk[9][20][2]*Vpk[16][20][2])+((Vpk[9][20][0]*
          Vpk[16][20][0])+(Vpk[9][20][1]*Vpk[16][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[16][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[16][20][1])))))+temp[0]);
        temp[0] = ((.205126*((Vpk[9][20][2]*Vpk[17][20][2])+((Vpk[9][20][0]*
          Vpk[17][20][0])+(Vpk[9][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[17][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[17][20][1])))));
        mm[9][17] = (temp[0]+((1.2*((Vpk[9][17][2]*Vpk[17][17][2])+((
          Vpk[9][17][0]*Vpk[17][17][0])+(Vpk[9][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[9][17][2]))+((.001361*(pin[17][0]*
          Wpk[9][17][0]))+(.003709*(pin[17][1]*Wpk[9][17][1]))))));
        mm[9][18] = ((.205126*((Vpk[9][20][2]*Vpk[18][20][2])+((Vpk[9][20][0]*
          Vpk[18][20][0])+(Vpk[9][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[18][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[18][20][1])))));
        mm[9][19] = ((.205126*((Vpk[9][20][2]*Vpk[19][20][2])+((Vpk[9][20][0]*
          Vpk[19][20][0])+(Vpk[9][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[9][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[9][20][0]*Wpk[19][20][0]
          ))+(.000179*(Wpk[9][20][1]*Wpk[19][20][1])))));
        mm[9][20] = ((.205126*((Vpk[9][20][2]*Vpk[20][20][2])+((Vpk[9][20][0]*
          Vpk[20][20][0])+(Vpk[9][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[9][20][2]))+((.000117*(pin[20][0]*Wpk[9][20][0]))+(
          .000179*(pin[20][1]*Wpk[9][20][1])))));
        mm[9][21] = 0.;
        mm[9][22] = 0.;
        mm[9][23] = 0.;
        mm[9][24] = 0.;
        mm[9][25] = 0.;
        mm[9][26] = 0.;
        mm[9][27] = 0.;
        mm[9][28] = 0.;
        mm[9][29] = 0.;
        mm[9][30] = 0.;
        mm[9][31] = 0.;
        mm[9][32] = 0.;
        temp[0] = ((3.51*((Vpk[10][14][2]*Vpk[10][14][2])+((Vpk[10][14][0]*
          Vpk[10][14][0])+(Vpk[10][14][1]*Vpk[10][14][1]))))+((.0484*(
          Wpk[10][14][2]*Wpk[10][14][2]))+((.0048*(Wpk[10][14][1]*Wpk[10][14][1]
          ))+(.0477*(Wpk[10][14][0]*Wpk[10][14][0])))));
        temp[1] = ((1.2*((Vpk[10][17][2]*Vpk[10][17][2])+((Vpk[10][17][0]*
          Vpk[10][17][0])+(Vpk[10][17][1]*Vpk[10][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[10][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[10][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[10][17][1])))));
        temp[2] = ((.205126*((Vpk[10][20][2]*Vpk[10][20][2])+((Vpk[10][20][0]*
          Vpk[10][20][0])+(Vpk[10][20][1]*Vpk[10][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[10][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[10][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[10][20][1])))));
        mm[10][10] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(
          Wpk[10][11][2]*Wpk[10][11][2]))+(Vpk[10][11][2]*Vpk[10][11][2])))+((
          .1337*(Wpk[10][11][2]*Wpk[10][11][2]))+((.0332*(Wpk[10][11][1]*
          Wpk[10][11][1]))+(.1268*(Wpk[10][11][0]*Wpk[10][11][0]))))))));
        temp[0] = ((3.51*((Vpk[10][14][2]*Vpk[11][14][2])+((Vpk[10][14][0]*
          Vpk[11][14][0])+(Vpk[10][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[10][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[10][14][1]*Wpk[11][14][1]
          ))+(.0477*(Wpk[10][14][0]*Wpk[11][14][0])))));
        temp[1] = ((1.2*((Vpk[10][17][2]*Vpk[11][17][2])+((Vpk[10][17][0]*
          Vpk[11][17][0])+(Vpk[10][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[11][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[11][17][1])))));
        temp[2] = ((.205126*((Vpk[10][20][2]*Vpk[11][20][2])+((Vpk[10][20][0]*
          Vpk[11][20][0])+(Vpk[10][20][1]*Vpk[11][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[11][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[11][20][1])))));
        mm[10][11] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(pin[11][2]*
          Wpk[10][11][2]))+(Vpk[10][11][2]*Vpk[11][11][2])))+((.1337*(pin[11][2]
          *Wpk[10][11][2]))+((.0332*(pin[11][1]*Wpk[10][11][1]))+(.1268*(
          pin[11][0]*Wpk[10][11][0]))))))));
        temp[0] = ((1.2*((Vpk[10][17][2]*Vpk[12][17][2])+((Vpk[10][17][0]*
          Vpk[12][17][0])+(Vpk[10][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[12][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[10][20][2]*Vpk[12][20][2])+((Vpk[10][20][0]*
          Vpk[12][20][0])+(Vpk[10][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[12][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[12][20][1])))));
        mm[10][12] = (temp[1]+(((.653562*((Vpk[10][14][0]*Wpk[12][14][2])-(
          Vpk[10][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[10][14][2]*
          Wpk[12][14][2]))+((.0048*(Wpk[10][14][1]*Wpk[12][14][1]))+(.0477*(
          Wpk[10][14][0]*Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[10][17][2]*Vpk[13][17][2])+((Vpk[10][17][0]*
          Vpk[13][17][0])+(Vpk[10][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[13][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[10][20][2]*Vpk[13][20][2])+((Vpk[10][20][0]*
          Vpk[13][20][0])+(Vpk[10][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[13][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[13][20][1])))));
        mm[10][13] = (temp[1]+(((.653562*((Vpk[10][14][0]*Wpk[13][14][2])-(
          Vpk[10][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[10][14][2]*
          Wpk[13][14][2]))+((.0048*(Wpk[10][14][1]*Wpk[13][14][1]))+(.0477*(
          Wpk[10][14][0]*Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[10][14][0])-(pin[14][0]*
          Vpk[10][14][2])))+((.0484*(pin[14][2]*Wpk[10][14][2]))+((.0048*(
          pin[14][1]*Wpk[10][14][1]))+(.0477*(pin[14][0]*Wpk[10][14][0])))))+((
          1.2*((Vpk[10][17][2]*Vpk[14][17][2])+((Vpk[10][17][0]*Vpk[14][17][0])+
          (Vpk[10][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[10][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[10][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[10][17][1]*Wpk[14][17][1]))))));
        mm[10][14] = (((.205126*((Vpk[10][20][2]*Vpk[14][20][2])+((
          Vpk[10][20][0]*Vpk[14][20][0])+(Vpk[10][20][1]*Vpk[14][20][1]))))+((
          .000119*(Wpk[10][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[14][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[14][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[10][17][2]*Vpk[15][17][2])+((Vpk[10][17][0]*
          Vpk[15][17][0])+(Vpk[10][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[15][17][1])))));
        mm[10][15] = (((.205126*((Vpk[10][20][2]*Vpk[15][20][2])+((
          Vpk[10][20][0]*Vpk[15][20][0])+(Vpk[10][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[10][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[10][17][2]*Vpk[16][17][2])+((Vpk[10][17][0]*
          Vpk[16][17][0])+(Vpk[10][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[10][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[10][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[10][17][1]*Wpk[16][17][1])))));
        mm[10][16] = (((.205126*((Vpk[10][20][2]*Vpk[16][20][2])+((
          Vpk[10][20][0]*Vpk[16][20][0])+(Vpk[10][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[10][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[10][20][2]*Vpk[17][20][2])+((Vpk[10][20][0]*
          Vpk[17][20][0])+(Vpk[10][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[17][20][1])))));
        mm[10][17] = (temp[0]+((1.2*((Vpk[10][17][2]*Vpk[17][17][2])+((
          Vpk[10][17][0]*Vpk[17][17][0])+(Vpk[10][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[10][17][2]))+((.001361*(pin[17][0]*
          Wpk[10][17][0]))+(.003709*(pin[17][1]*Wpk[10][17][1]))))));
        mm[10][18] = ((.205126*((Vpk[10][20][2]*Vpk[18][20][2])+((Vpk[10][20][0]
          *Vpk[18][20][0])+(Vpk[10][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[18][20][1])))));
        mm[10][19] = ((.205126*((Vpk[10][20][2]*Vpk[19][20][2])+((Vpk[10][20][0]
          *Vpk[19][20][0])+(Vpk[10][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[10][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[10][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[10][20][1]*Wpk[19][20][1])))));
        mm[10][20] = ((.205126*((Vpk[10][20][2]*Vpk[20][20][2])+((Vpk[10][20][0]
          *Vpk[20][20][0])+(Vpk[10][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[10][20][2]))+((.000117*(pin[20][0]*Wpk[10][20][0]))+(
          .000179*(pin[20][1]*Wpk[10][20][1])))));
        mm[10][21] = 0.;
        mm[10][22] = 0.;
        mm[10][23] = 0.;
        mm[10][24] = 0.;
        mm[10][25] = 0.;
        mm[10][26] = 0.;
        mm[10][27] = 0.;
        mm[10][28] = 0.;
        mm[10][29] = 0.;
        mm[10][30] = 0.;
        mm[10][31] = 0.;
        mm[10][32] = 0.;
        temp[0] = (((3.51*((Vpk[11][14][2]*Vpk[11][14][2])+((Vpk[11][14][0]*
          Vpk[11][14][0])+(Vpk[11][14][1]*Vpk[11][14][1]))))+((.0484*(
          Wpk[11][14][2]*Wpk[11][14][2]))+((.0048*(Wpk[11][14][1]*Wpk[11][14][1]
          ))+(.0477*(Wpk[11][14][0]*Wpk[11][14][0])))))+((8.806*((.02941625*(
          pin[11][2]*pin[11][2]))+(Vpk[11][11][2]*Vpk[11][11][2])))+((.1337*(
          pin[11][2]*pin[11][2]))+((.0332*(pin[11][1]*pin[11][1]))+(.1268*(
          pin[11][0]*pin[11][0]))))));
        temp[1] = (((1.2*((Vpk[11][17][2]*Vpk[11][17][2])+((Vpk[11][17][0]*
          Vpk[11][17][0])+(Vpk[11][17][1]*Vpk[11][17][1]))))+((.003916*(
          Wpk[11][17][2]*Wpk[11][17][2]))+((.001361*(Wpk[11][17][0]*
          Wpk[11][17][0]))+(.003709*(Wpk[11][17][1]*Wpk[11][17][1])))))+temp[0])
          ;
        mm[11][11] = (((.205126*((Vpk[11][20][2]*Vpk[11][20][2])+((
          Vpk[11][20][0]*Vpk[11][20][0])+(Vpk[11][20][1]*Vpk[11][20][1]))))+((
          .000119*(Wpk[11][20][2]*Wpk[11][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[11][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[11][20][1])))))+temp[1])
          ;
        temp[0] = ((1.2*((Vpk[11][17][2]*Vpk[12][17][2])+((Vpk[11][17][0]*
          Vpk[12][17][0])+(Vpk[11][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[11][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[11][17][0]*
          Wpk[12][17][0]))+(.003709*(Wpk[11][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[11][20][2]*Vpk[12][20][2])+((Vpk[11][20][0]*
          Vpk[12][20][0])+(Vpk[11][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[11][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[12][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[12][20][1])))));
        mm[11][12] = (temp[1]+(((.653562*((Vpk[11][14][0]*Wpk[12][14][2])-(
          Vpk[11][14][2]*Wpk[12][14][0])))+((.0484*(Wpk[11][14][2]*
          Wpk[12][14][2]))+((.0048*(Wpk[11][14][1]*Wpk[12][14][1]))+(.0477*(
          Wpk[11][14][0]*Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[11][17][2]*Vpk[13][17][2])+((Vpk[11][17][0]*
          Vpk[13][17][0])+(Vpk[11][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[11][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[11][17][0]*
          Wpk[13][17][0]))+(.003709*(Wpk[11][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[11][20][2]*Vpk[13][20][2])+((Vpk[11][20][0]*
          Vpk[13][20][0])+(Vpk[11][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[11][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[13][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[13][20][1])))));
        mm[11][13] = (temp[1]+(((.653562*((Vpk[11][14][0]*Wpk[13][14][2])-(
          Vpk[11][14][2]*Wpk[13][14][0])))+((.0484*(Wpk[11][14][2]*
          Wpk[13][14][2]))+((.0048*(Wpk[11][14][1]*Wpk[13][14][1]))+(.0477*(
          Wpk[11][14][0]*Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[14][2]*Vpk[11][14][0])-(pin[14][0]*
          Vpk[11][14][2])))+((.0484*(pin[14][2]*Wpk[11][14][2]))+((.0048*(
          pin[14][1]*Wpk[11][14][1]))+(.0477*(pin[14][0]*Wpk[11][14][0])))))+((
          1.2*((Vpk[11][17][2]*Vpk[14][17][2])+((Vpk[11][17][0]*Vpk[14][17][0])+
          (Vpk[11][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[11][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[11][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[11][17][1]*Wpk[14][17][1]))))));
        mm[11][14] = (((.205126*((Vpk[11][20][2]*Vpk[14][20][2])+((
          Vpk[11][20][0]*Vpk[14][20][0])+(Vpk[11][20][1]*Vpk[14][20][1]))))+((
          .000119*(Wpk[11][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[14][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[14][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[11][17][2]*Vpk[15][17][2])+((Vpk[11][17][0]*
          Vpk[15][17][0])+(Vpk[11][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[11][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[11][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[11][17][1]*Wpk[15][17][1])))));
        mm[11][15] = (((.205126*((Vpk[11][20][2]*Vpk[15][20][2])+((
          Vpk[11][20][0]*Vpk[15][20][0])+(Vpk[11][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[11][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[11][17][2]*Vpk[16][17][2])+((Vpk[11][17][0]*
          Vpk[16][17][0])+(Vpk[11][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[11][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[11][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[11][17][1]*Wpk[16][17][1])))));
        mm[11][16] = (((.205126*((Vpk[11][20][2]*Vpk[16][20][2])+((
          Vpk[11][20][0]*Vpk[16][20][0])+(Vpk[11][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[11][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[11][20][2]*Vpk[17][20][2])+((Vpk[11][20][0]*
          Vpk[17][20][0])+(Vpk[11][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[11][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[17][20][1])))));
        mm[11][17] = (temp[0]+((1.2*((Vpk[11][17][2]*Vpk[17][17][2])+((
          Vpk[11][17][0]*Vpk[17][17][0])+(Vpk[11][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[11][17][2]))+((.001361*(pin[17][0]*
          Wpk[11][17][0]))+(.003709*(pin[17][1]*Wpk[11][17][1]))))));
        mm[11][18] = ((.205126*((Vpk[11][20][2]*Vpk[18][20][2])+((Vpk[11][20][0]
          *Vpk[18][20][0])+(Vpk[11][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[11][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[18][20][1])))));
        mm[11][19] = ((.205126*((Vpk[11][20][2]*Vpk[19][20][2])+((Vpk[11][20][0]
          *Vpk[19][20][0])+(Vpk[11][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[11][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[11][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[11][20][1]*Wpk[19][20][1])))));
        mm[11][20] = ((.205126*((Vpk[11][20][2]*Vpk[20][20][2])+((Vpk[11][20][0]
          *Vpk[20][20][0])+(Vpk[11][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[11][20][2]))+((.000117*(pin[20][0]*Wpk[11][20][0]))+(
          .000179*(pin[20][1]*Wpk[11][20][1])))));
        mm[11][21] = 0.;
        mm[11][22] = 0.;
        mm[11][23] = 0.;
        mm[11][24] = 0.;
        mm[11][25] = 0.;
        mm[11][26] = 0.;
        mm[11][27] = 0.;
        mm[11][28] = 0.;
        mm[11][29] = 0.;
        mm[11][30] = 0.;
        mm[11][31] = 0.;
        mm[11][32] = 0.;
        temp[0] = ((1.2*((Vpk[12][17][2]*Vpk[12][17][2])+((Vpk[12][17][0]*
          Vpk[12][17][0])+(Vpk[12][17][1]*Vpk[12][17][1]))))+((.003916*(
          Wpk[12][17][2]*Wpk[12][17][2]))+((.001361*(Wpk[12][17][0]*
          Wpk[12][17][0]))+(.003709*(Wpk[12][17][1]*Wpk[12][17][1])))));
        temp[1] = ((.205126*((Vpk[12][20][2]*Vpk[12][20][2])+((Vpk[12][20][0]*
          Vpk[12][20][0])+(Vpk[12][20][1]*Vpk[12][20][1]))))+((.000119*(
          Wpk[12][20][2]*Wpk[12][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[12][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[12][20][1])))));
        mm[12][12] = (temp[1]+(((.1216932444*((Wpk[12][14][0]*Wpk[12][14][0])+(
          Wpk[12][14][2]*Wpk[12][14][2])))+((.0484*(Wpk[12][14][2]*
          Wpk[12][14][2]))+((.0048*(Wpk[12][14][1]*Wpk[12][14][1]))+(.0477*(
          Wpk[12][14][0]*Wpk[12][14][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[12][17][2]*Vpk[13][17][2])+((Vpk[12][17][0]*
          Vpk[13][17][0])+(Vpk[12][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[12][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[12][17][0]*
          Wpk[13][17][0]))+(.003709*(Wpk[12][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[12][20][2]*Vpk[13][20][2])+((Vpk[12][20][0]*
          Vpk[13][20][0])+(Vpk[12][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[12][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[13][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[13][20][1])))));
        mm[12][13] = (temp[1]+(((.1216932444*((Wpk[12][14][0]*Wpk[13][14][0])+(
          Wpk[12][14][2]*Wpk[13][14][2])))+((.0484*(Wpk[12][14][2]*
          Wpk[13][14][2]))+((.0048*(Wpk[12][14][1]*Wpk[13][14][1]))+(.0477*(
          Wpk[12][14][0]*Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.1216932444*((pin[14][0]*Wpk[12][14][0])+(pin[14][2]*
          Wpk[12][14][2])))+((.0484*(pin[14][2]*Wpk[12][14][2]))+((.0048*(
          pin[14][1]*Wpk[12][14][1]))+(.0477*(pin[14][0]*Wpk[12][14][0])))))+((
          1.2*((Vpk[12][17][2]*Vpk[14][17][2])+((Vpk[12][17][0]*Vpk[14][17][0])+
          (Vpk[12][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[12][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[12][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[12][17][1]*Wpk[14][17][1]))))));
        mm[12][14] = (((.205126*((Vpk[12][20][2]*Vpk[14][20][2])+((
          Vpk[12][20][0]*Vpk[14][20][0])+(Vpk[12][20][1]*Vpk[14][20][1]))))+((
          .000119*(Wpk[12][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[14][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[14][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[12][17][2]*Vpk[15][17][2])+((Vpk[12][17][0]*
          Vpk[15][17][0])+(Vpk[12][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[12][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[12][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[12][17][1]*Wpk[15][17][1])))));
        mm[12][15] = (((.205126*((Vpk[12][20][2]*Vpk[15][20][2])+((
          Vpk[12][20][0]*Vpk[15][20][0])+(Vpk[12][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[12][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[12][17][2]*Vpk[16][17][2])+((Vpk[12][17][0]*
          Vpk[16][17][0])+(Vpk[12][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[12][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[12][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[12][17][1]*Wpk[16][17][1])))));
        mm[12][16] = (((.205126*((Vpk[12][20][2]*Vpk[16][20][2])+((
          Vpk[12][20][0]*Vpk[16][20][0])+(Vpk[12][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[12][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[12][20][2]*Vpk[17][20][2])+((Vpk[12][20][0]*
          Vpk[17][20][0])+(Vpk[12][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[12][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[17][20][1])))));
        mm[12][17] = (temp[0]+((1.2*((Vpk[12][17][2]*Vpk[17][17][2])+((
          Vpk[12][17][0]*Vpk[17][17][0])+(Vpk[12][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[12][17][2]))+((.001361*(pin[17][0]*
          Wpk[12][17][0]))+(.003709*(pin[17][1]*Wpk[12][17][1]))))));
        mm[12][18] = ((.205126*((Vpk[12][20][2]*Vpk[18][20][2])+((Vpk[12][20][0]
          *Vpk[18][20][0])+(Vpk[12][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[12][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[18][20][1])))));
        mm[12][19] = ((.205126*((Vpk[12][20][2]*Vpk[19][20][2])+((Vpk[12][20][0]
          *Vpk[19][20][0])+(Vpk[12][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[12][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[12][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[12][20][1]*Wpk[19][20][1])))));
        mm[12][20] = ((.205126*((Vpk[12][20][2]*Vpk[20][20][2])+((Vpk[12][20][0]
          *Vpk[20][20][0])+(Vpk[12][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[12][20][2]))+((.000117*(pin[20][0]*Wpk[12][20][0]))+(
          .000179*(pin[20][1]*Wpk[12][20][1])))));
        mm[12][21] = 0.;
        mm[12][22] = 0.;
        mm[12][23] = 0.;
        mm[12][24] = 0.;
        mm[12][25] = 0.;
        mm[12][26] = 0.;
        mm[12][27] = 0.;
        mm[12][28] = 0.;
        mm[12][29] = 0.;
        mm[12][30] = 0.;
        mm[12][31] = 0.;
        mm[12][32] = 0.;
        temp[0] = ((1.2*((Vpk[13][17][2]*Vpk[13][17][2])+((Vpk[13][17][0]*
          Vpk[13][17][0])+(Vpk[13][17][1]*Vpk[13][17][1]))))+((.003916*(
          Wpk[13][17][2]*Wpk[13][17][2]))+((.001361*(Wpk[13][17][0]*
          Wpk[13][17][0]))+(.003709*(Wpk[13][17][1]*Wpk[13][17][1])))));
        temp[1] = ((.205126*((Vpk[13][20][2]*Vpk[13][20][2])+((Vpk[13][20][0]*
          Vpk[13][20][0])+(Vpk[13][20][1]*Vpk[13][20][1]))))+((.000119*(
          Wpk[13][20][2]*Wpk[13][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[13][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[13][20][1])))));
        mm[13][13] = (temp[1]+(((.1216932444*((Wpk[13][14][0]*Wpk[13][14][0])+(
          Wpk[13][14][2]*Wpk[13][14][2])))+((.0484*(Wpk[13][14][2]*
          Wpk[13][14][2]))+((.0048*(Wpk[13][14][1]*Wpk[13][14][1]))+(.0477*(
          Wpk[13][14][0]*Wpk[13][14][0])))))+temp[0]));
        temp[0] = (((.1216932444*((pin[14][0]*Wpk[13][14][0])+(pin[14][2]*
          Wpk[13][14][2])))+((.0484*(pin[14][2]*Wpk[13][14][2]))+((.0048*(
          pin[14][1]*Wpk[13][14][1]))+(.0477*(pin[14][0]*Wpk[13][14][0])))))+((
          1.2*((Vpk[13][17][2]*Vpk[14][17][2])+((Vpk[13][17][0]*Vpk[14][17][0])+
          (Vpk[13][17][1]*Vpk[14][17][1]))))+((.003916*(Wpk[13][17][2]*
          Wpk[14][17][2]))+((.001361*(Wpk[13][17][0]*Wpk[14][17][0]))+(.003709*(
          Wpk[13][17][1]*Wpk[14][17][1]))))));
        mm[13][14] = (((.205126*((Vpk[13][20][2]*Vpk[14][20][2])+((
          Vpk[13][20][0]*Vpk[14][20][0])+(Vpk[13][20][1]*Vpk[14][20][1]))))+((
          .000119*(Wpk[13][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[14][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[14][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[13][17][2]*Vpk[15][17][2])+((Vpk[13][17][0]*
          Vpk[15][17][0])+(Vpk[13][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[13][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[13][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[13][17][1]*Wpk[15][17][1])))));
        mm[13][15] = (((.205126*((Vpk[13][20][2]*Vpk[15][20][2])+((
          Vpk[13][20][0]*Vpk[15][20][0])+(Vpk[13][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[13][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[13][17][2]*Vpk[16][17][2])+((Vpk[13][17][0]*
          Vpk[16][17][0])+(Vpk[13][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[13][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[13][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[13][17][1]*Wpk[16][17][1])))));
        mm[13][16] = (((.205126*((Vpk[13][20][2]*Vpk[16][20][2])+((
          Vpk[13][20][0]*Vpk[16][20][0])+(Vpk[13][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[13][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[13][20][2]*Vpk[17][20][2])+((Vpk[13][20][0]*
          Vpk[17][20][0])+(Vpk[13][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[13][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[17][20][1])))));
        mm[13][17] = (temp[0]+((1.2*((Vpk[13][17][2]*Vpk[17][17][2])+((
          Vpk[13][17][0]*Vpk[17][17][0])+(Vpk[13][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[13][17][2]))+((.001361*(pin[17][0]*
          Wpk[13][17][0]))+(.003709*(pin[17][1]*Wpk[13][17][1]))))));
        mm[13][18] = ((.205126*((Vpk[13][20][2]*Vpk[18][20][2])+((Vpk[13][20][0]
          *Vpk[18][20][0])+(Vpk[13][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[13][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[18][20][1])))));
        mm[13][19] = ((.205126*((Vpk[13][20][2]*Vpk[19][20][2])+((Vpk[13][20][0]
          *Vpk[19][20][0])+(Vpk[13][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[13][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[13][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[13][20][1]*Wpk[19][20][1])))));
        mm[13][20] = ((.205126*((Vpk[13][20][2]*Vpk[20][20][2])+((Vpk[13][20][0]
          *Vpk[20][20][0])+(Vpk[13][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[13][20][2]))+((.000117*(pin[20][0]*Wpk[13][20][0]))+(
          .000179*(pin[20][1]*Wpk[13][20][1])))));
        mm[13][21] = 0.;
        mm[13][22] = 0.;
        mm[13][23] = 0.;
        mm[13][24] = 0.;
        mm[13][25] = 0.;
        mm[13][26] = 0.;
        mm[13][27] = 0.;
        mm[13][28] = 0.;
        mm[13][29] = 0.;
        mm[13][30] = 0.;
        mm[13][31] = 0.;
        mm[13][32] = 0.;
        temp[0] = (((.1216932444*((pin[14][0]*pin[14][0])+(pin[14][2]*pin[14][2]
          )))+((.0484*(pin[14][2]*pin[14][2]))+((.0048*(pin[14][1]*pin[14][1]))+
          (.0477*(pin[14][0]*pin[14][0])))))+((1.2*((Vpk[14][17][2]*
          Vpk[14][17][2])+((Vpk[14][17][0]*Vpk[14][17][0])+(Vpk[14][17][1]*
          Vpk[14][17][1]))))+((.003916*(Wpk[14][17][2]*Wpk[14][17][2]))+((
          .001361*(Wpk[14][17][0]*Wpk[14][17][0]))+(.003709*(Wpk[14][17][1]*
          Wpk[14][17][1]))))));
        mm[14][14] = (((.205126*((Vpk[14][20][2]*Vpk[14][20][2])+((
          Vpk[14][20][0]*Vpk[14][20][0])+(Vpk[14][20][1]*Vpk[14][20][1]))))+((
          .000119*(Wpk[14][20][2]*Wpk[14][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[14][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[14][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[14][17][2]*Vpk[15][17][2])+((Vpk[14][17][0]*
          Vpk[15][17][0])+(Vpk[14][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[14][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[14][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[14][17][1]*Wpk[15][17][1])))));
        mm[14][15] = (((.205126*((Vpk[14][20][2]*Vpk[15][20][2])+((
          Vpk[14][20][0]*Vpk[15][20][0])+(Vpk[14][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[14][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[14][17][2]*Vpk[16][17][2])+((Vpk[14][17][0]*
          Vpk[16][17][0])+(Vpk[14][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[14][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[14][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[14][17][1]*Wpk[16][17][1])))));
        mm[14][16] = (((.205126*((Vpk[14][20][2]*Vpk[16][20][2])+((
          Vpk[14][20][0]*Vpk[16][20][0])+(Vpk[14][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[14][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[14][20][2]*Vpk[17][20][2])+((Vpk[14][20][0]*
          Vpk[17][20][0])+(Vpk[14][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[14][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[17][20][1])))));
        mm[14][17] = (temp[0]+((1.2*((Vpk[14][17][2]*Vpk[17][17][2])+((
          Vpk[14][17][0]*Vpk[17][17][0])+(Vpk[14][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[14][17][2]))+((.001361*(pin[17][0]*
          Wpk[14][17][0]))+(.003709*(pin[17][1]*Wpk[14][17][1]))))));
        mm[14][18] = ((.205126*((Vpk[14][20][2]*Vpk[18][20][2])+((Vpk[14][20][0]
          *Vpk[18][20][0])+(Vpk[14][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[14][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[18][20][1])))));
        mm[14][19] = ((.205126*((Vpk[14][20][2]*Vpk[19][20][2])+((Vpk[14][20][0]
          *Vpk[19][20][0])+(Vpk[14][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[14][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[14][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[14][20][1]*Wpk[19][20][1])))));
        mm[14][20] = ((.205126*((Vpk[14][20][2]*Vpk[20][20][2])+((Vpk[14][20][0]
          *Vpk[20][20][0])+(Vpk[14][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[14][20][2]))+((.000117*(pin[20][0]*Wpk[14][20][0]))+(
          .000179*(pin[20][1]*Wpk[14][20][1])))));
        mm[14][21] = 0.;
        mm[14][22] = 0.;
        mm[14][23] = 0.;
        mm[14][24] = 0.;
        mm[14][25] = 0.;
        mm[14][26] = 0.;
        mm[14][27] = 0.;
        mm[14][28] = 0.;
        mm[14][29] = 0.;
        mm[14][30] = 0.;
        mm[14][31] = 0.;
        mm[14][32] = 0.;
        temp[0] = ((1.2*((Vpk[15][17][2]*Vpk[15][17][2])+((Vpk[15][17][0]*
          Vpk[15][17][0])+(Vpk[15][17][1]*Vpk[15][17][1]))))+((.003916*(
          Wpk[15][17][2]*Wpk[15][17][2]))+((.001361*(Wpk[15][17][0]*
          Wpk[15][17][0]))+(.003709*(Wpk[15][17][1]*Wpk[15][17][1])))));
        mm[15][15] = (((.205126*((Vpk[15][20][2]*Vpk[15][20][2])+((
          Vpk[15][20][0]*Vpk[15][20][0])+(Vpk[15][20][1]*Vpk[15][20][1]))))+((
          .000119*(Wpk[15][20][2]*Wpk[15][20][2]))+((.000117*(Wpk[15][20][0]*
          Wpk[15][20][0]))+(.000179*(Wpk[15][20][1]*Wpk[15][20][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[15][17][2]*Vpk[16][17][2])+((Vpk[15][17][0]*
          Vpk[16][17][0])+(Vpk[15][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[15][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[15][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[15][17][1]*Wpk[16][17][1])))));
        mm[15][16] = (((.205126*((Vpk[15][20][2]*Vpk[16][20][2])+((
          Vpk[15][20][0]*Vpk[16][20][0])+(Vpk[15][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[15][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[15][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[15][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[15][20][2]*Vpk[17][20][2])+((Vpk[15][20][0]*
          Vpk[17][20][0])+(Vpk[15][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[15][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[15][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[15][20][1]*Wpk[17][20][1])))));
        mm[15][17] = (temp[0]+((1.2*((Vpk[15][17][2]*Vpk[17][17][2])+((
          Vpk[15][17][0]*Vpk[17][17][0])+(Vpk[15][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[15][17][2]))+((.001361*(pin[17][0]*
          Wpk[15][17][0]))+(.003709*(pin[17][1]*Wpk[15][17][1]))))));
        mm[15][18] = ((.205126*((Vpk[15][20][2]*Vpk[18][20][2])+((Vpk[15][20][0]
          *Vpk[18][20][0])+(Vpk[15][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[15][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[15][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[15][20][1]*Wpk[18][20][1])))));
        mm[15][19] = ((.205126*((Vpk[15][20][2]*Vpk[19][20][2])+((Vpk[15][20][0]
          *Vpk[19][20][0])+(Vpk[15][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[15][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[15][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[15][20][1]*Wpk[19][20][1])))));
        mm[15][20] = ((.205126*((Vpk[15][20][2]*Vpk[20][20][2])+((Vpk[15][20][0]
          *Vpk[20][20][0])+(Vpk[15][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[15][20][2]))+((.000117*(pin[20][0]*Wpk[15][20][0]))+(
          .000179*(pin[20][1]*Wpk[15][20][1])))));
        mm[15][21] = 0.;
        mm[15][22] = 0.;
        mm[15][23] = 0.;
        mm[15][24] = 0.;
        mm[15][25] = 0.;
        mm[15][26] = 0.;
        mm[15][27] = 0.;
        mm[15][28] = 0.;
        mm[15][29] = 0.;
        mm[15][30] = 0.;
        mm[15][31] = 0.;
        mm[15][32] = 0.;
        temp[0] = ((1.2*((Vpk[16][17][2]*Vpk[16][17][2])+((Vpk[16][17][0]*
          Vpk[16][17][0])+(Vpk[16][17][1]*Vpk[16][17][1]))))+((.003916*(
          Wpk[16][17][2]*Wpk[16][17][2]))+((.001361*(Wpk[16][17][0]*
          Wpk[16][17][0]))+(.003709*(Wpk[16][17][1]*Wpk[16][17][1])))));
        mm[16][16] = (((.205126*((Vpk[16][20][2]*Vpk[16][20][2])+((
          Vpk[16][20][0]*Vpk[16][20][0])+(Vpk[16][20][1]*Vpk[16][20][1]))))+((
          .000119*(Wpk[16][20][2]*Wpk[16][20][2]))+((.000117*(Wpk[16][20][0]*
          Wpk[16][20][0]))+(.000179*(Wpk[16][20][1]*Wpk[16][20][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[16][20][2]*Vpk[17][20][2])+((Vpk[16][20][0]*
          Vpk[17][20][0])+(Vpk[16][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[16][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[16][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[16][20][1]*Wpk[17][20][1])))));
        mm[16][17] = (temp[0]+((1.2*((Vpk[16][17][2]*Vpk[17][17][2])+((
          Vpk[16][17][0]*Vpk[17][17][0])+(Vpk[16][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*Wpk[16][17][2]))+((.001361*(pin[17][0]*
          Wpk[16][17][0]))+(.003709*(pin[17][1]*Wpk[16][17][1]))))));
        mm[16][18] = ((.205126*((Vpk[16][20][2]*Vpk[18][20][2])+((Vpk[16][20][0]
          *Vpk[18][20][0])+(Vpk[16][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[16][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[16][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[16][20][1]*Wpk[18][20][1])))));
        mm[16][19] = ((.205126*((Vpk[16][20][2]*Vpk[19][20][2])+((Vpk[16][20][0]
          *Vpk[19][20][0])+(Vpk[16][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[16][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[16][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[16][20][1]*Wpk[19][20][1])))));
        mm[16][20] = ((.205126*((Vpk[16][20][2]*Vpk[20][20][2])+((Vpk[16][20][0]
          *Vpk[20][20][0])+(Vpk[16][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[16][20][2]))+((.000117*(pin[20][0]*Wpk[16][20][0]))+(
          .000179*(pin[20][1]*Wpk[16][20][1])))));
        mm[16][21] = 0.;
        mm[16][22] = 0.;
        mm[16][23] = 0.;
        mm[16][24] = 0.;
        mm[16][25] = 0.;
        mm[16][26] = 0.;
        mm[16][27] = 0.;
        mm[16][28] = 0.;
        mm[16][29] = 0.;
        mm[16][30] = 0.;
        mm[16][31] = 0.;
        mm[16][32] = 0.;
        temp[0] = ((.205126*((Vpk[17][20][2]*Vpk[17][20][2])+((Vpk[17][20][0]*
          Vpk[17][20][0])+(Vpk[17][20][1]*Vpk[17][20][1]))))+((.000119*(
          Wpk[17][20][2]*Wpk[17][20][2]))+((.000117*(Wpk[17][20][0]*
          Wpk[17][20][0]))+(.000179*(Wpk[17][20][1]*Wpk[17][20][1])))));
        mm[17][17] = (temp[0]+((1.2*((Vpk[17][17][2]*Vpk[17][17][2])+((
          Vpk[17][17][0]*Vpk[17][17][0])+(Vpk[17][17][1]*Vpk[17][17][1]))))+((
          .003916*(pin[17][2]*pin[17][2]))+((.001361*(pin[17][0]*pin[17][0]))+(
          .003709*(pin[17][1]*pin[17][1]))))));
        mm[17][18] = ((.205126*((Vpk[17][20][2]*Vpk[18][20][2])+((Vpk[17][20][0]
          *Vpk[18][20][0])+(Vpk[17][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[17][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[17][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[17][20][1]*Wpk[18][20][1])))));
        mm[17][19] = ((.205126*((Vpk[17][20][2]*Vpk[19][20][2])+((Vpk[17][20][0]
          *Vpk[19][20][0])+(Vpk[17][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[17][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[17][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[17][20][1]*Wpk[19][20][1])))));
        mm[17][20] = ((.205126*((Vpk[17][20][2]*Vpk[20][20][2])+((Vpk[17][20][0]
          *Vpk[20][20][0])+(Vpk[17][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[17][20][2]))+((.000117*(pin[20][0]*Wpk[17][20][0]))+(
          .000179*(pin[20][1]*Wpk[17][20][1])))));
        mm[17][21] = 0.;
        mm[17][22] = 0.;
        mm[17][23] = 0.;
        mm[17][24] = 0.;
        mm[17][25] = 0.;
        mm[17][26] = 0.;
        mm[17][27] = 0.;
        mm[17][28] = 0.;
        mm[17][29] = 0.;
        mm[17][30] = 0.;
        mm[17][31] = 0.;
        mm[17][32] = 0.;
        mm[18][18] = ((.205126*((Vpk[18][20][2]*Vpk[18][20][2])+((Vpk[18][20][0]
          *Vpk[18][20][0])+(Vpk[18][20][1]*Vpk[18][20][1]))))+((.000119*(
          Wpk[18][20][2]*Wpk[18][20][2]))+((.000117*(Wpk[18][20][0]*
          Wpk[18][20][0]))+(.000179*(Wpk[18][20][1]*Wpk[18][20][1])))));
        mm[18][19] = ((.205126*((Vpk[18][20][2]*Vpk[19][20][2])+((Vpk[18][20][0]
          *Vpk[19][20][0])+(Vpk[18][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[18][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[18][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[18][20][1]*Wpk[19][20][1])))));
        mm[18][20] = ((.205126*((Vpk[18][20][2]*Vpk[20][20][2])+((Vpk[18][20][0]
          *Vpk[20][20][0])+(Vpk[18][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[18][20][2]))+((.000117*(pin[20][0]*Wpk[18][20][0]))+(
          .000179*(pin[20][1]*Wpk[18][20][1])))));
        mm[18][21] = 0.;
        mm[18][22] = 0.;
        mm[18][23] = 0.;
        mm[18][24] = 0.;
        mm[18][25] = 0.;
        mm[18][26] = 0.;
        mm[18][27] = 0.;
        mm[18][28] = 0.;
        mm[18][29] = 0.;
        mm[18][30] = 0.;
        mm[18][31] = 0.;
        mm[18][32] = 0.;
        mm[19][19] = ((.205126*((Vpk[19][20][2]*Vpk[19][20][2])+((Vpk[19][20][0]
          *Vpk[19][20][0])+(Vpk[19][20][1]*Vpk[19][20][1]))))+((.000119*(
          Wpk[19][20][2]*Wpk[19][20][2]))+((.000117*(Wpk[19][20][0]*
          Wpk[19][20][0]))+(.000179*(Wpk[19][20][1]*Wpk[19][20][1])))));
        mm[19][20] = ((.205126*((Vpk[19][20][2]*Vpk[20][20][2])+((Vpk[19][20][0]
          *Vpk[20][20][0])+(Vpk[19][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*Wpk[19][20][2]))+((.000117*(pin[20][0]*Wpk[19][20][0]))+(
          .000179*(pin[20][1]*Wpk[19][20][1])))));
        mm[19][21] = 0.;
        mm[19][22] = 0.;
        mm[19][23] = 0.;
        mm[19][24] = 0.;
        mm[19][25] = 0.;
        mm[19][26] = 0.;
        mm[19][27] = 0.;
        mm[19][28] = 0.;
        mm[19][29] = 0.;
        mm[19][30] = 0.;
        mm[19][31] = 0.;
        mm[19][32] = 0.;
        mm[20][20] = ((.205126*((Vpk[20][20][2]*Vpk[20][20][2])+((Vpk[20][20][0]
          *Vpk[20][20][0])+(Vpk[20][20][1]*Vpk[20][20][1]))))+((.000119*(
          pin[20][2]*pin[20][2]))+((.000117*(pin[20][0]*pin[20][0]))+(.000179*(
          pin[20][1]*pin[20][1])))));
        mm[20][21] = 0.;
        mm[20][22] = 0.;
        mm[20][23] = 0.;
        mm[20][24] = 0.;
        mm[20][25] = 0.;
        mm[20][26] = 0.;
        mm[20][27] = 0.;
        mm[20][28] = 0.;
        mm[20][29] = 0.;
        mm[20][30] = 0.;
        mm[20][31] = 0.;
        mm[20][32] = 0.;
        temp[0] = ((3.51*((Vpk[21][26][2]*Vpk[21][26][2])+((Vpk[21][26][0]*
          Vpk[21][26][0])+(Vpk[21][26][1]*Vpk[21][26][1]))))+((.0484*(
          Wpk[21][26][2]*Wpk[21][26][2]))+((.0048*(Wpk[21][26][1]*Wpk[21][26][1]
          ))+(.0477*(Wpk[21][26][0]*Wpk[21][26][0])))));
        temp[1] = ((1.2*((Vpk[21][29][2]*Vpk[21][29][2])+((Vpk[21][29][0]*
          Vpk[21][29][0])+(Vpk[21][29][1]*Vpk[21][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[21][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[21][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[21][29][1])))));
        temp[2] = ((.205126*((Vpk[21][32][2]*Vpk[21][32][2])+((Vpk[21][32][0]*
          Vpk[21][32][0])+(Vpk[21][32][1]*Vpk[21][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[21][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[21][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[21][32][1])))));
        mm[21][21] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(
          Wpk[21][23][2]*Wpk[21][23][2]))+(Vpk[21][23][2]*Vpk[21][23][2])))+((
          .1337*(Wpk[21][23][2]*Wpk[21][23][2]))+((.0332*(Wpk[21][23][1]*
          Wpk[21][23][1]))+(.1268*(Wpk[21][23][0]*Wpk[21][23][0]))))))));
        temp[0] = ((3.51*((Vpk[21][26][2]*Vpk[22][26][2])+((Vpk[21][26][0]*
          Vpk[22][26][0])+(Vpk[21][26][1]*Vpk[22][26][1]))))+((.0484*(
          Wpk[21][26][2]*Wpk[22][26][2]))+((.0048*(Wpk[21][26][1]*Wpk[22][26][1]
          ))+(.0477*(Wpk[21][26][0]*Wpk[22][26][0])))));
        temp[1] = ((1.2*((Vpk[21][29][2]*Vpk[22][29][2])+((Vpk[21][29][0]*
          Vpk[22][29][0])+(Vpk[21][29][1]*Vpk[22][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[22][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[22][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[22][29][1])))));
        temp[2] = ((.205126*((Vpk[21][32][2]*Vpk[22][32][2])+((Vpk[21][32][0]*
          Vpk[22][32][0])+(Vpk[21][32][1]*Vpk[22][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[22][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[22][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[22][32][1])))));
        mm[21][22] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(
          Wpk[21][23][2]*Wpk[22][23][2]))+(Vpk[21][23][2]*Vpk[22][23][2])))+((
          .1337*(Wpk[21][23][2]*Wpk[22][23][2]))+((.0332*(Wpk[21][23][1]*
          Wpk[22][23][1]))+(.1268*(Wpk[21][23][0]*Wpk[22][23][0]))))))));
        temp[0] = ((3.51*((Vpk[21][26][2]*Vpk[23][26][2])+((Vpk[21][26][0]*
          Vpk[23][26][0])+(Vpk[21][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[21][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[21][26][1]*Wpk[23][26][1]
          ))+(.0477*(Wpk[21][26][0]*Wpk[23][26][0])))));
        temp[1] = ((1.2*((Vpk[21][29][2]*Vpk[23][29][2])+((Vpk[21][29][0]*
          Vpk[23][29][0])+(Vpk[21][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[23][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[23][29][1])))));
        temp[2] = ((.205126*((Vpk[21][32][2]*Vpk[23][32][2])+((Vpk[21][32][0]*
          Vpk[23][32][0])+(Vpk[21][32][1]*Vpk[23][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[23][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[23][32][1])))));
        mm[21][23] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(pin[23][2]*
          Wpk[21][23][2]))+(Vpk[21][23][2]*Vpk[23][23][2])))+((.1337*(pin[23][2]
          *Wpk[21][23][2]))+((.0332*(pin[23][1]*Wpk[21][23][1]))+(.1268*(
          pin[23][0]*Wpk[21][23][0]))))))));
        temp[0] = ((1.2*((Vpk[21][29][2]*Vpk[24][29][2])+((Vpk[21][29][0]*
          Vpk[24][29][0])+(Vpk[21][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[24][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[21][32][2]*Vpk[24][32][2])+((Vpk[21][32][0]*
          Vpk[24][32][0])+(Vpk[21][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[24][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[24][32][1])))));
        mm[21][24] = (temp[1]+(((.653562*((Vpk[21][26][0]*Wpk[24][26][2])-(
          Vpk[21][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[21][26][2]*
          Wpk[24][26][2]))+((.0048*(Wpk[21][26][1]*Wpk[24][26][1]))+(.0477*(
          Wpk[21][26][0]*Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[21][29][2]*Vpk[25][29][2])+((Vpk[21][29][0]*
          Vpk[25][29][0])+(Vpk[21][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[25][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[21][32][2]*Vpk[25][32][2])+((Vpk[21][32][0]*
          Vpk[25][32][0])+(Vpk[21][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[25][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[25][32][1])))));
        mm[21][25] = (temp[1]+(((.653562*((Vpk[21][26][0]*Wpk[25][26][2])-(
          Vpk[21][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[21][26][2]*
          Wpk[25][26][2]))+((.0048*(Wpk[21][26][1]*Wpk[25][26][1]))+(.0477*(
          Wpk[21][26][0]*Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[21][26][0])-(pin[26][0]*
          Vpk[21][26][2])))+((.0484*(pin[26][2]*Wpk[21][26][2]))+((.0048*(
          pin[26][1]*Wpk[21][26][1]))+(.0477*(pin[26][0]*Wpk[21][26][0])))))+((
          1.2*((Vpk[21][29][2]*Vpk[26][29][2])+((Vpk[21][29][0]*Vpk[26][29][0])+
          (Vpk[21][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[21][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[21][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[21][29][1]*Wpk[26][29][1]))))));
        mm[21][26] = (((.205126*((Vpk[21][32][2]*Vpk[26][32][2])+((
          Vpk[21][32][0]*Vpk[26][32][0])+(Vpk[21][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[21][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[21][29][2]*Vpk[27][29][2])+((Vpk[21][29][0]*
          Vpk[27][29][0])+(Vpk[21][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[27][29][1])))));
        mm[21][27] = (((.205126*((Vpk[21][32][2]*Vpk[27][32][2])+((
          Vpk[21][32][0]*Vpk[27][32][0])+(Vpk[21][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[21][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[21][29][2]*Vpk[28][29][2])+((Vpk[21][29][0]*
          Vpk[28][29][0])+(Vpk[21][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[21][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[21][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[21][29][1]*Wpk[28][29][1])))));
        mm[21][28] = (((.205126*((Vpk[21][32][2]*Vpk[28][32][2])+((
          Vpk[21][32][0]*Vpk[28][32][0])+(Vpk[21][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[21][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[21][32][2]*Vpk[29][32][2])+((Vpk[21][32][0]*
          Vpk[29][32][0])+(Vpk[21][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[29][32][1])))));
        mm[21][29] = (temp[0]+((1.2*((Vpk[21][29][2]*Vpk[29][29][2])+((
          Vpk[21][29][0]*Vpk[29][29][0])+(Vpk[21][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[21][29][2]))+((.001361*(pin[29][0]*
          Wpk[21][29][0]))+(.003709*(pin[29][1]*Wpk[21][29][1]))))));
        mm[21][30] = ((.205126*((Vpk[21][32][2]*Vpk[30][32][2])+((Vpk[21][32][0]
          *Vpk[30][32][0])+(Vpk[21][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[30][32][1])))));
        mm[21][31] = ((.205126*((Vpk[21][32][2]*Vpk[31][32][2])+((Vpk[21][32][0]
          *Vpk[31][32][0])+(Vpk[21][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[21][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[21][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[21][32][1]*Wpk[31][32][1])))));
        mm[21][32] = ((.205126*((Vpk[21][32][2]*Vpk[32][32][2])+((Vpk[21][32][0]
          *Vpk[32][32][0])+(Vpk[21][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[21][32][2]))+((.000117*(pin[32][0]*Wpk[21][32][0]))+(
          .000179*(pin[32][1]*Wpk[21][32][1])))));
        temp[0] = ((3.51*((Vpk[22][26][2]*Vpk[22][26][2])+((Vpk[22][26][0]*
          Vpk[22][26][0])+(Vpk[22][26][1]*Vpk[22][26][1]))))+((.0484*(
          Wpk[22][26][2]*Wpk[22][26][2]))+((.0048*(Wpk[22][26][1]*Wpk[22][26][1]
          ))+(.0477*(Wpk[22][26][0]*Wpk[22][26][0])))));
        temp[1] = ((1.2*((Vpk[22][29][2]*Vpk[22][29][2])+((Vpk[22][29][0]*
          Vpk[22][29][0])+(Vpk[22][29][1]*Vpk[22][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[22][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[22][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[22][29][1])))));
        temp[2] = ((.205126*((Vpk[22][32][2]*Vpk[22][32][2])+((Vpk[22][32][0]*
          Vpk[22][32][0])+(Vpk[22][32][1]*Vpk[22][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[22][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[22][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[22][32][1])))));
        mm[22][22] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(
          Wpk[22][23][2]*Wpk[22][23][2]))+(Vpk[22][23][2]*Vpk[22][23][2])))+((
          .1337*(Wpk[22][23][2]*Wpk[22][23][2]))+((.0332*(Wpk[22][23][1]*
          Wpk[22][23][1]))+(.1268*(Wpk[22][23][0]*Wpk[22][23][0]))))))));
        temp[0] = ((3.51*((Vpk[22][26][2]*Vpk[23][26][2])+((Vpk[22][26][0]*
          Vpk[23][26][0])+(Vpk[22][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[22][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[22][26][1]*Wpk[23][26][1]
          ))+(.0477*(Wpk[22][26][0]*Wpk[23][26][0])))));
        temp[1] = ((1.2*((Vpk[22][29][2]*Vpk[23][29][2])+((Vpk[22][29][0]*
          Vpk[23][29][0])+(Vpk[22][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[23][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[23][29][1])))));
        temp[2] = ((.205126*((Vpk[22][32][2]*Vpk[23][32][2])+((Vpk[22][32][0]*
          Vpk[23][32][0])+(Vpk[22][32][1]*Vpk[23][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[23][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[23][32][1])))));
        mm[22][23] = (temp[2]+(temp[1]+(temp[0]+((8.806*((.02941625*(pin[23][2]*
          Wpk[22][23][2]))+(Vpk[22][23][2]*Vpk[23][23][2])))+((.1337*(pin[23][2]
          *Wpk[22][23][2]))+((.0332*(pin[23][1]*Wpk[22][23][1]))+(.1268*(
          pin[23][0]*Wpk[22][23][0]))))))));
        temp[0] = ((1.2*((Vpk[22][29][2]*Vpk[24][29][2])+((Vpk[22][29][0]*
          Vpk[24][29][0])+(Vpk[22][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[24][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[22][32][2]*Vpk[24][32][2])+((Vpk[22][32][0]*
          Vpk[24][32][0])+(Vpk[22][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[24][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[24][32][1])))));
        mm[22][24] = (temp[1]+(((.653562*((Vpk[22][26][0]*Wpk[24][26][2])-(
          Vpk[22][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[22][26][2]*
          Wpk[24][26][2]))+((.0048*(Wpk[22][26][1]*Wpk[24][26][1]))+(.0477*(
          Wpk[22][26][0]*Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[22][29][2]*Vpk[25][29][2])+((Vpk[22][29][0]*
          Vpk[25][29][0])+(Vpk[22][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[25][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[22][32][2]*Vpk[25][32][2])+((Vpk[22][32][0]*
          Vpk[25][32][0])+(Vpk[22][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[25][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[25][32][1])))));
        mm[22][25] = (temp[1]+(((.653562*((Vpk[22][26][0]*Wpk[25][26][2])-(
          Vpk[22][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[22][26][2]*
          Wpk[25][26][2]))+((.0048*(Wpk[22][26][1]*Wpk[25][26][1]))+(.0477*(
          Wpk[22][26][0]*Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[22][26][0])-(pin[26][0]*
          Vpk[22][26][2])))+((.0484*(pin[26][2]*Wpk[22][26][2]))+((.0048*(
          pin[26][1]*Wpk[22][26][1]))+(.0477*(pin[26][0]*Wpk[22][26][0])))))+((
          1.2*((Vpk[22][29][2]*Vpk[26][29][2])+((Vpk[22][29][0]*Vpk[26][29][0])+
          (Vpk[22][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[22][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[22][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[22][29][1]*Wpk[26][29][1]))))));
        mm[22][26] = (((.205126*((Vpk[22][32][2]*Vpk[26][32][2])+((
          Vpk[22][32][0]*Vpk[26][32][0])+(Vpk[22][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[22][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[22][29][2]*Vpk[27][29][2])+((Vpk[22][29][0]*
          Vpk[27][29][0])+(Vpk[22][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[27][29][1])))));
        mm[22][27] = (((.205126*((Vpk[22][32][2]*Vpk[27][32][2])+((
          Vpk[22][32][0]*Vpk[27][32][0])+(Vpk[22][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[22][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[22][29][2]*Vpk[28][29][2])+((Vpk[22][29][0]*
          Vpk[28][29][0])+(Vpk[22][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[22][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[22][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[22][29][1]*Wpk[28][29][1])))));
        mm[22][28] = (((.205126*((Vpk[22][32][2]*Vpk[28][32][2])+((
          Vpk[22][32][0]*Vpk[28][32][0])+(Vpk[22][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[22][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[22][32][2]*Vpk[29][32][2])+((Vpk[22][32][0]*
          Vpk[29][32][0])+(Vpk[22][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[29][32][1])))));
        mm[22][29] = (temp[0]+((1.2*((Vpk[22][29][2]*Vpk[29][29][2])+((
          Vpk[22][29][0]*Vpk[29][29][0])+(Vpk[22][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[22][29][2]))+((.001361*(pin[29][0]*
          Wpk[22][29][0]))+(.003709*(pin[29][1]*Wpk[22][29][1]))))));
        mm[22][30] = ((.205126*((Vpk[22][32][2]*Vpk[30][32][2])+((Vpk[22][32][0]
          *Vpk[30][32][0])+(Vpk[22][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[30][32][1])))));
        mm[22][31] = ((.205126*((Vpk[22][32][2]*Vpk[31][32][2])+((Vpk[22][32][0]
          *Vpk[31][32][0])+(Vpk[22][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[22][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[22][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[22][32][1]*Wpk[31][32][1])))));
        mm[22][32] = ((.205126*((Vpk[22][32][2]*Vpk[32][32][2])+((Vpk[22][32][0]
          *Vpk[32][32][0])+(Vpk[22][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[22][32][2]))+((.000117*(pin[32][0]*Wpk[22][32][0]))+(
          .000179*(pin[32][1]*Wpk[22][32][1])))));
        temp[0] = (((3.51*((Vpk[23][26][2]*Vpk[23][26][2])+((Vpk[23][26][0]*
          Vpk[23][26][0])+(Vpk[23][26][1]*Vpk[23][26][1]))))+((.0484*(
          Wpk[23][26][2]*Wpk[23][26][2]))+((.0048*(Wpk[23][26][1]*Wpk[23][26][1]
          ))+(.0477*(Wpk[23][26][0]*Wpk[23][26][0])))))+((8.806*((.02941625*(
          pin[23][2]*pin[23][2]))+(Vpk[23][23][2]*Vpk[23][23][2])))+((.1337*(
          pin[23][2]*pin[23][2]))+((.0332*(pin[23][1]*pin[23][1]))+(.1268*(
          pin[23][0]*pin[23][0]))))));
        temp[1] = (((1.2*((Vpk[23][29][2]*Vpk[23][29][2])+((Vpk[23][29][0]*
          Vpk[23][29][0])+(Vpk[23][29][1]*Vpk[23][29][1]))))+((.003916*(
          Wpk[23][29][2]*Wpk[23][29][2]))+((.001361*(Wpk[23][29][0]*
          Wpk[23][29][0]))+(.003709*(Wpk[23][29][1]*Wpk[23][29][1])))))+temp[0])
          ;
        mm[23][23] = (((.205126*((Vpk[23][32][2]*Vpk[23][32][2])+((
          Vpk[23][32][0]*Vpk[23][32][0])+(Vpk[23][32][1]*Vpk[23][32][1]))))+((
          .000119*(Wpk[23][32][2]*Wpk[23][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[23][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[23][32][1])))))+temp[1])
          ;
        temp[0] = ((1.2*((Vpk[23][29][2]*Vpk[24][29][2])+((Vpk[23][29][0]*
          Vpk[24][29][0])+(Vpk[23][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[23][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[23][29][0]*
          Wpk[24][29][0]))+(.003709*(Wpk[23][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[23][32][2]*Vpk[24][32][2])+((Vpk[23][32][0]*
          Vpk[24][32][0])+(Vpk[23][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[23][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[24][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[24][32][1])))));
        mm[23][24] = (temp[1]+(((.653562*((Vpk[23][26][0]*Wpk[24][26][2])-(
          Vpk[23][26][2]*Wpk[24][26][0])))+((.0484*(Wpk[23][26][2]*
          Wpk[24][26][2]))+((.0048*(Wpk[23][26][1]*Wpk[24][26][1]))+(.0477*(
          Wpk[23][26][0]*Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[23][29][2]*Vpk[25][29][2])+((Vpk[23][29][0]*
          Vpk[25][29][0])+(Vpk[23][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[23][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[23][29][0]*
          Wpk[25][29][0]))+(.003709*(Wpk[23][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[23][32][2]*Vpk[25][32][2])+((Vpk[23][32][0]*
          Vpk[25][32][0])+(Vpk[23][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[23][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[25][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[25][32][1])))));
        mm[23][25] = (temp[1]+(((.653562*((Vpk[23][26][0]*Wpk[25][26][2])-(
          Vpk[23][26][2]*Wpk[25][26][0])))+((.0484*(Wpk[23][26][2]*
          Wpk[25][26][2]))+((.0048*(Wpk[23][26][1]*Wpk[25][26][1]))+(.0477*(
          Wpk[23][26][0]*Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.653562*((pin[26][2]*Vpk[23][26][0])-(pin[26][0]*
          Vpk[23][26][2])))+((.0484*(pin[26][2]*Wpk[23][26][2]))+((.0048*(
          pin[26][1]*Wpk[23][26][1]))+(.0477*(pin[26][0]*Wpk[23][26][0])))))+((
          1.2*((Vpk[23][29][2]*Vpk[26][29][2])+((Vpk[23][29][0]*Vpk[26][29][0])+
          (Vpk[23][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[23][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[23][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[23][29][1]*Wpk[26][29][1]))))));
        mm[23][26] = (((.205126*((Vpk[23][32][2]*Vpk[26][32][2])+((
          Vpk[23][32][0]*Vpk[26][32][0])+(Vpk[23][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[23][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[23][29][2]*Vpk[27][29][2])+((Vpk[23][29][0]*
          Vpk[27][29][0])+(Vpk[23][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[23][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[23][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[23][29][1]*Wpk[27][29][1])))));
        mm[23][27] = (((.205126*((Vpk[23][32][2]*Vpk[27][32][2])+((
          Vpk[23][32][0]*Vpk[27][32][0])+(Vpk[23][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[23][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[23][29][2]*Vpk[28][29][2])+((Vpk[23][29][0]*
          Vpk[28][29][0])+(Vpk[23][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[23][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[23][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[23][29][1]*Wpk[28][29][1])))));
        mm[23][28] = (((.205126*((Vpk[23][32][2]*Vpk[28][32][2])+((
          Vpk[23][32][0]*Vpk[28][32][0])+(Vpk[23][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[23][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[23][32][2]*Vpk[29][32][2])+((Vpk[23][32][0]*
          Vpk[29][32][0])+(Vpk[23][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[23][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[29][32][1])))));
        mm[23][29] = (temp[0]+((1.2*((Vpk[23][29][2]*Vpk[29][29][2])+((
          Vpk[23][29][0]*Vpk[29][29][0])+(Vpk[23][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[23][29][2]))+((.001361*(pin[29][0]*
          Wpk[23][29][0]))+(.003709*(pin[29][1]*Wpk[23][29][1]))))));
        mm[23][30] = ((.205126*((Vpk[23][32][2]*Vpk[30][32][2])+((Vpk[23][32][0]
          *Vpk[30][32][0])+(Vpk[23][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[23][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[30][32][1])))));
        mm[23][31] = ((.205126*((Vpk[23][32][2]*Vpk[31][32][2])+((Vpk[23][32][0]
          *Vpk[31][32][0])+(Vpk[23][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[23][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[23][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[23][32][1]*Wpk[31][32][1])))));
        mm[23][32] = ((.205126*((Vpk[23][32][2]*Vpk[32][32][2])+((Vpk[23][32][0]
          *Vpk[32][32][0])+(Vpk[23][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[23][32][2]))+((.000117*(pin[32][0]*Wpk[23][32][0]))+(
          .000179*(pin[32][1]*Wpk[23][32][1])))));
        temp[0] = ((1.2*((Vpk[24][29][2]*Vpk[24][29][2])+((Vpk[24][29][0]*
          Vpk[24][29][0])+(Vpk[24][29][1]*Vpk[24][29][1]))))+((.003916*(
          Wpk[24][29][2]*Wpk[24][29][2]))+((.001361*(Wpk[24][29][0]*
          Wpk[24][29][0]))+(.003709*(Wpk[24][29][1]*Wpk[24][29][1])))));
        temp[1] = ((.205126*((Vpk[24][32][2]*Vpk[24][32][2])+((Vpk[24][32][0]*
          Vpk[24][32][0])+(Vpk[24][32][1]*Vpk[24][32][1]))))+((.000119*(
          Wpk[24][32][2]*Wpk[24][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[24][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[24][32][1])))));
        mm[24][24] = (temp[1]+(((.1216932444*((Wpk[24][26][0]*Wpk[24][26][0])+(
          Wpk[24][26][2]*Wpk[24][26][2])))+((.0484*(Wpk[24][26][2]*
          Wpk[24][26][2]))+((.0048*(Wpk[24][26][1]*Wpk[24][26][1]))+(.0477*(
          Wpk[24][26][0]*Wpk[24][26][0])))))+temp[0]));
        temp[0] = ((1.2*((Vpk[24][29][2]*Vpk[25][29][2])+((Vpk[24][29][0]*
          Vpk[25][29][0])+(Vpk[24][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[24][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[24][29][0]*
          Wpk[25][29][0]))+(.003709*(Wpk[24][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[24][32][2]*Vpk[25][32][2])+((Vpk[24][32][0]*
          Vpk[25][32][0])+(Vpk[24][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[24][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[25][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[25][32][1])))));
        mm[24][25] = (temp[1]+(((.1216932444*((Wpk[24][26][0]*Wpk[25][26][0])+(
          Wpk[24][26][2]*Wpk[25][26][2])))+((.0484*(Wpk[24][26][2]*
          Wpk[25][26][2]))+((.0048*(Wpk[24][26][1]*Wpk[25][26][1]))+(.0477*(
          Wpk[24][26][0]*Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.1216932444*((pin[26][0]*Wpk[24][26][0])+(pin[26][2]*
          Wpk[24][26][2])))+((.0484*(pin[26][2]*Wpk[24][26][2]))+((.0048*(
          pin[26][1]*Wpk[24][26][1]))+(.0477*(pin[26][0]*Wpk[24][26][0])))))+((
          1.2*((Vpk[24][29][2]*Vpk[26][29][2])+((Vpk[24][29][0]*Vpk[26][29][0])+
          (Vpk[24][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[24][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[24][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[24][29][1]*Wpk[26][29][1]))))));
        mm[24][26] = (((.205126*((Vpk[24][32][2]*Vpk[26][32][2])+((
          Vpk[24][32][0]*Vpk[26][32][0])+(Vpk[24][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[24][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[24][29][2]*Vpk[27][29][2])+((Vpk[24][29][0]*
          Vpk[27][29][0])+(Vpk[24][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[24][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[24][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[24][29][1]*Wpk[27][29][1])))));
        mm[24][27] = (((.205126*((Vpk[24][32][2]*Vpk[27][32][2])+((
          Vpk[24][32][0]*Vpk[27][32][0])+(Vpk[24][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[24][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[24][29][2]*Vpk[28][29][2])+((Vpk[24][29][0]*
          Vpk[28][29][0])+(Vpk[24][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[24][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[24][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[24][29][1]*Wpk[28][29][1])))));
        mm[24][28] = (((.205126*((Vpk[24][32][2]*Vpk[28][32][2])+((
          Vpk[24][32][0]*Vpk[28][32][0])+(Vpk[24][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[24][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[24][32][2]*Vpk[29][32][2])+((Vpk[24][32][0]*
          Vpk[29][32][0])+(Vpk[24][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[24][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[29][32][1])))));
        mm[24][29] = (temp[0]+((1.2*((Vpk[24][29][2]*Vpk[29][29][2])+((
          Vpk[24][29][0]*Vpk[29][29][0])+(Vpk[24][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[24][29][2]))+((.001361*(pin[29][0]*
          Wpk[24][29][0]))+(.003709*(pin[29][1]*Wpk[24][29][1]))))));
        mm[24][30] = ((.205126*((Vpk[24][32][2]*Vpk[30][32][2])+((Vpk[24][32][0]
          *Vpk[30][32][0])+(Vpk[24][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[24][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[30][32][1])))));
        mm[24][31] = ((.205126*((Vpk[24][32][2]*Vpk[31][32][2])+((Vpk[24][32][0]
          *Vpk[31][32][0])+(Vpk[24][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[24][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[24][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[24][32][1]*Wpk[31][32][1])))));
        mm[24][32] = ((.205126*((Vpk[24][32][2]*Vpk[32][32][2])+((Vpk[24][32][0]
          *Vpk[32][32][0])+(Vpk[24][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[24][32][2]))+((.000117*(pin[32][0]*Wpk[24][32][0]))+(
          .000179*(pin[32][1]*Wpk[24][32][1])))));
        temp[0] = ((1.2*((Vpk[25][29][2]*Vpk[25][29][2])+((Vpk[25][29][0]*
          Vpk[25][29][0])+(Vpk[25][29][1]*Vpk[25][29][1]))))+((.003916*(
          Wpk[25][29][2]*Wpk[25][29][2]))+((.001361*(Wpk[25][29][0]*
          Wpk[25][29][0]))+(.003709*(Wpk[25][29][1]*Wpk[25][29][1])))));
        temp[1] = ((.205126*((Vpk[25][32][2]*Vpk[25][32][2])+((Vpk[25][32][0]*
          Vpk[25][32][0])+(Vpk[25][32][1]*Vpk[25][32][1]))))+((.000119*(
          Wpk[25][32][2]*Wpk[25][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[25][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[25][32][1])))));
        mm[25][25] = (temp[1]+(((.1216932444*((Wpk[25][26][0]*Wpk[25][26][0])+(
          Wpk[25][26][2]*Wpk[25][26][2])))+((.0484*(Wpk[25][26][2]*
          Wpk[25][26][2]))+((.0048*(Wpk[25][26][1]*Wpk[25][26][1]))+(.0477*(
          Wpk[25][26][0]*Wpk[25][26][0])))))+temp[0]));
        temp[0] = (((.1216932444*((pin[26][0]*Wpk[25][26][0])+(pin[26][2]*
          Wpk[25][26][2])))+((.0484*(pin[26][2]*Wpk[25][26][2]))+((.0048*(
          pin[26][1]*Wpk[25][26][1]))+(.0477*(pin[26][0]*Wpk[25][26][0])))))+((
          1.2*((Vpk[25][29][2]*Vpk[26][29][2])+((Vpk[25][29][0]*Vpk[26][29][0])+
          (Vpk[25][29][1]*Vpk[26][29][1]))))+((.003916*(Wpk[25][29][2]*
          Wpk[26][29][2]))+((.001361*(Wpk[25][29][0]*Wpk[26][29][0]))+(.003709*(
          Wpk[25][29][1]*Wpk[26][29][1]))))));
        mm[25][26] = (((.205126*((Vpk[25][32][2]*Vpk[26][32][2])+((
          Vpk[25][32][0]*Vpk[26][32][0])+(Vpk[25][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[25][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[25][29][2]*Vpk[27][29][2])+((Vpk[25][29][0]*
          Vpk[27][29][0])+(Vpk[25][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[25][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[25][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[25][29][1]*Wpk[27][29][1])))));
        mm[25][27] = (((.205126*((Vpk[25][32][2]*Vpk[27][32][2])+((
          Vpk[25][32][0]*Vpk[27][32][0])+(Vpk[25][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[25][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[25][29][2]*Vpk[28][29][2])+((Vpk[25][29][0]*
          Vpk[28][29][0])+(Vpk[25][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[25][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[25][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[25][29][1]*Wpk[28][29][1])))));
        mm[25][28] = (((.205126*((Vpk[25][32][2]*Vpk[28][32][2])+((
          Vpk[25][32][0]*Vpk[28][32][0])+(Vpk[25][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[25][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[25][32][2]*Vpk[29][32][2])+((Vpk[25][32][0]*
          Vpk[29][32][0])+(Vpk[25][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[25][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[29][32][1])))));
        mm[25][29] = (temp[0]+((1.2*((Vpk[25][29][2]*Vpk[29][29][2])+((
          Vpk[25][29][0]*Vpk[29][29][0])+(Vpk[25][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[25][29][2]))+((.001361*(pin[29][0]*
          Wpk[25][29][0]))+(.003709*(pin[29][1]*Wpk[25][29][1]))))));
        mm[25][30] = ((.205126*((Vpk[25][32][2]*Vpk[30][32][2])+((Vpk[25][32][0]
          *Vpk[30][32][0])+(Vpk[25][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[25][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[30][32][1])))));
        mm[25][31] = ((.205126*((Vpk[25][32][2]*Vpk[31][32][2])+((Vpk[25][32][0]
          *Vpk[31][32][0])+(Vpk[25][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[25][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[25][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[25][32][1]*Wpk[31][32][1])))));
        mm[25][32] = ((.205126*((Vpk[25][32][2]*Vpk[32][32][2])+((Vpk[25][32][0]
          *Vpk[32][32][0])+(Vpk[25][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[25][32][2]))+((.000117*(pin[32][0]*Wpk[25][32][0]))+(
          .000179*(pin[32][1]*Wpk[25][32][1])))));
        temp[0] = (((.1216932444*((pin[26][0]*pin[26][0])+(pin[26][2]*pin[26][2]
          )))+((.0484*(pin[26][2]*pin[26][2]))+((.0048*(pin[26][1]*pin[26][1]))+
          (.0477*(pin[26][0]*pin[26][0])))))+((1.2*((Vpk[26][29][2]*
          Vpk[26][29][2])+((Vpk[26][29][0]*Vpk[26][29][0])+(Vpk[26][29][1]*
          Vpk[26][29][1]))))+((.003916*(Wpk[26][29][2]*Wpk[26][29][2]))+((
          .001361*(Wpk[26][29][0]*Wpk[26][29][0]))+(.003709*(Wpk[26][29][1]*
          Wpk[26][29][1]))))));
        mm[26][26] = (((.205126*((Vpk[26][32][2]*Vpk[26][32][2])+((
          Vpk[26][32][0]*Vpk[26][32][0])+(Vpk[26][32][1]*Vpk[26][32][1]))))+((
          .000119*(Wpk[26][32][2]*Wpk[26][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[26][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[26][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[26][29][2]*Vpk[27][29][2])+((Vpk[26][29][0]*
          Vpk[27][29][0])+(Vpk[26][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[26][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[26][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[26][29][1]*Wpk[27][29][1])))));
        mm[26][27] = (((.205126*((Vpk[26][32][2]*Vpk[27][32][2])+((
          Vpk[26][32][0]*Vpk[27][32][0])+(Vpk[26][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[26][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[26][29][2]*Vpk[28][29][2])+((Vpk[26][29][0]*
          Vpk[28][29][0])+(Vpk[26][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[26][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[26][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[26][29][1]*Wpk[28][29][1])))));
        mm[26][28] = (((.205126*((Vpk[26][32][2]*Vpk[28][32][2])+((
          Vpk[26][32][0]*Vpk[28][32][0])+(Vpk[26][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[26][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[26][32][2]*Vpk[29][32][2])+((Vpk[26][32][0]*
          Vpk[29][32][0])+(Vpk[26][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[26][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[29][32][1])))));
        mm[26][29] = (temp[0]+((1.2*((Vpk[26][29][2]*Vpk[29][29][2])+((
          Vpk[26][29][0]*Vpk[29][29][0])+(Vpk[26][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[26][29][2]))+((.001361*(pin[29][0]*
          Wpk[26][29][0]))+(.003709*(pin[29][1]*Wpk[26][29][1]))))));
        mm[26][30] = ((.205126*((Vpk[26][32][2]*Vpk[30][32][2])+((Vpk[26][32][0]
          *Vpk[30][32][0])+(Vpk[26][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[26][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[30][32][1])))));
        mm[26][31] = ((.205126*((Vpk[26][32][2]*Vpk[31][32][2])+((Vpk[26][32][0]
          *Vpk[31][32][0])+(Vpk[26][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[26][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[26][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[26][32][1]*Wpk[31][32][1])))));
        mm[26][32] = ((.205126*((Vpk[26][32][2]*Vpk[32][32][2])+((Vpk[26][32][0]
          *Vpk[32][32][0])+(Vpk[26][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[26][32][2]))+((.000117*(pin[32][0]*Wpk[26][32][0]))+(
          .000179*(pin[32][1]*Wpk[26][32][1])))));
        temp[0] = ((1.2*((Vpk[27][29][2]*Vpk[27][29][2])+((Vpk[27][29][0]*
          Vpk[27][29][0])+(Vpk[27][29][1]*Vpk[27][29][1]))))+((.003916*(
          Wpk[27][29][2]*Wpk[27][29][2]))+((.001361*(Wpk[27][29][0]*
          Wpk[27][29][0]))+(.003709*(Wpk[27][29][1]*Wpk[27][29][1])))));
        mm[27][27] = (((.205126*((Vpk[27][32][2]*Vpk[27][32][2])+((
          Vpk[27][32][0]*Vpk[27][32][0])+(Vpk[27][32][1]*Vpk[27][32][1]))))+((
          .000119*(Wpk[27][32][2]*Wpk[27][32][2]))+((.000117*(Wpk[27][32][0]*
          Wpk[27][32][0]))+(.000179*(Wpk[27][32][1]*Wpk[27][32][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[27][29][2]*Vpk[28][29][2])+((Vpk[27][29][0]*
          Vpk[28][29][0])+(Vpk[27][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[27][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[27][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[27][29][1]*Wpk[28][29][1])))));
        mm[27][28] = (((.205126*((Vpk[27][32][2]*Vpk[28][32][2])+((
          Vpk[27][32][0]*Vpk[28][32][0])+(Vpk[27][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[27][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[27][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[27][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[27][32][2]*Vpk[29][32][2])+((Vpk[27][32][0]*
          Vpk[29][32][0])+(Vpk[27][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[27][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[27][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[27][32][1]*Wpk[29][32][1])))));
        mm[27][29] = (temp[0]+((1.2*((Vpk[27][29][2]*Vpk[29][29][2])+((
          Vpk[27][29][0]*Vpk[29][29][0])+(Vpk[27][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[27][29][2]))+((.001361*(pin[29][0]*
          Wpk[27][29][0]))+(.003709*(pin[29][1]*Wpk[27][29][1]))))));
        mm[27][30] = ((.205126*((Vpk[27][32][2]*Vpk[30][32][2])+((Vpk[27][32][0]
          *Vpk[30][32][0])+(Vpk[27][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[27][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[27][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[27][32][1]*Wpk[30][32][1])))));
        mm[27][31] = ((.205126*((Vpk[27][32][2]*Vpk[31][32][2])+((Vpk[27][32][0]
          *Vpk[31][32][0])+(Vpk[27][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[27][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[27][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[27][32][1]*Wpk[31][32][1])))));
        mm[27][32] = ((.205126*((Vpk[27][32][2]*Vpk[32][32][2])+((Vpk[27][32][0]
          *Vpk[32][32][0])+(Vpk[27][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[27][32][2]))+((.000117*(pin[32][0]*Wpk[27][32][0]))+(
          .000179*(pin[32][1]*Wpk[27][32][1])))));
        temp[0] = ((1.2*((Vpk[28][29][2]*Vpk[28][29][2])+((Vpk[28][29][0]*
          Vpk[28][29][0])+(Vpk[28][29][1]*Vpk[28][29][1]))))+((.003916*(
          Wpk[28][29][2]*Wpk[28][29][2]))+((.001361*(Wpk[28][29][0]*
          Wpk[28][29][0]))+(.003709*(Wpk[28][29][1]*Wpk[28][29][1])))));
        mm[28][28] = (((.205126*((Vpk[28][32][2]*Vpk[28][32][2])+((
          Vpk[28][32][0]*Vpk[28][32][0])+(Vpk[28][32][1]*Vpk[28][32][1]))))+((
          .000119*(Wpk[28][32][2]*Wpk[28][32][2]))+((.000117*(Wpk[28][32][0]*
          Wpk[28][32][0]))+(.000179*(Wpk[28][32][1]*Wpk[28][32][1])))))+temp[0])
          ;
        temp[0] = ((.205126*((Vpk[28][32][2]*Vpk[29][32][2])+((Vpk[28][32][0]*
          Vpk[29][32][0])+(Vpk[28][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[28][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[28][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[28][32][1]*Wpk[29][32][1])))));
        mm[28][29] = (temp[0]+((1.2*((Vpk[28][29][2]*Vpk[29][29][2])+((
          Vpk[28][29][0]*Vpk[29][29][0])+(Vpk[28][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*Wpk[28][29][2]))+((.001361*(pin[29][0]*
          Wpk[28][29][0]))+(.003709*(pin[29][1]*Wpk[28][29][1]))))));
        mm[28][30] = ((.205126*((Vpk[28][32][2]*Vpk[30][32][2])+((Vpk[28][32][0]
          *Vpk[30][32][0])+(Vpk[28][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[28][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[28][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[28][32][1]*Wpk[30][32][1])))));
        mm[28][31] = ((.205126*((Vpk[28][32][2]*Vpk[31][32][2])+((Vpk[28][32][0]
          *Vpk[31][32][0])+(Vpk[28][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[28][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[28][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[28][32][1]*Wpk[31][32][1])))));
        mm[28][32] = ((.205126*((Vpk[28][32][2]*Vpk[32][32][2])+((Vpk[28][32][0]
          *Vpk[32][32][0])+(Vpk[28][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[28][32][2]))+((.000117*(pin[32][0]*Wpk[28][32][0]))+(
          .000179*(pin[32][1]*Wpk[28][32][1])))));
        temp[0] = ((.205126*((Vpk[29][32][2]*Vpk[29][32][2])+((Vpk[29][32][0]*
          Vpk[29][32][0])+(Vpk[29][32][1]*Vpk[29][32][1]))))+((.000119*(
          Wpk[29][32][2]*Wpk[29][32][2]))+((.000117*(Wpk[29][32][0]*
          Wpk[29][32][0]))+(.000179*(Wpk[29][32][1]*Wpk[29][32][1])))));
        mm[29][29] = (temp[0]+((1.2*((Vpk[29][29][2]*Vpk[29][29][2])+((
          Vpk[29][29][0]*Vpk[29][29][0])+(Vpk[29][29][1]*Vpk[29][29][1]))))+((
          .003916*(pin[29][2]*pin[29][2]))+((.001361*(pin[29][0]*pin[29][0]))+(
          .003709*(pin[29][1]*pin[29][1]))))));
        mm[29][30] = ((.205126*((Vpk[29][32][2]*Vpk[30][32][2])+((Vpk[29][32][0]
          *Vpk[30][32][0])+(Vpk[29][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[29][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[29][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[29][32][1]*Wpk[30][32][1])))));
        mm[29][31] = ((.205126*((Vpk[29][32][2]*Vpk[31][32][2])+((Vpk[29][32][0]
          *Vpk[31][32][0])+(Vpk[29][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[29][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[29][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[29][32][1]*Wpk[31][32][1])))));
        mm[29][32] = ((.205126*((Vpk[29][32][2]*Vpk[32][32][2])+((Vpk[29][32][0]
          *Vpk[32][32][0])+(Vpk[29][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[29][32][2]))+((.000117*(pin[32][0]*Wpk[29][32][0]))+(
          .000179*(pin[32][1]*Wpk[29][32][1])))));
        mm[30][30] = ((.205126*((Vpk[30][32][2]*Vpk[30][32][2])+((Vpk[30][32][0]
          *Vpk[30][32][0])+(Vpk[30][32][1]*Vpk[30][32][1]))))+((.000119*(
          Wpk[30][32][2]*Wpk[30][32][2]))+((.000117*(Wpk[30][32][0]*
          Wpk[30][32][0]))+(.000179*(Wpk[30][32][1]*Wpk[30][32][1])))));
        mm[30][31] = ((.205126*((Vpk[30][32][2]*Vpk[31][32][2])+((Vpk[30][32][0]
          *Vpk[31][32][0])+(Vpk[30][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[30][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[30][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[30][32][1]*Wpk[31][32][1])))));
        mm[30][32] = ((.205126*((Vpk[30][32][2]*Vpk[32][32][2])+((Vpk[30][32][0]
          *Vpk[32][32][0])+(Vpk[30][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[30][32][2]))+((.000117*(pin[32][0]*Wpk[30][32][0]))+(
          .000179*(pin[32][1]*Wpk[30][32][1])))));
        mm[31][31] = ((.205126*((Vpk[31][32][2]*Vpk[31][32][2])+((Vpk[31][32][0]
          *Vpk[31][32][0])+(Vpk[31][32][1]*Vpk[31][32][1]))))+((.000119*(
          Wpk[31][32][2]*Wpk[31][32][2]))+((.000117*(Wpk[31][32][0]*
          Wpk[31][32][0]))+(.000179*(Wpk[31][32][1]*Wpk[31][32][1])))));
        mm[31][32] = ((.205126*((Vpk[31][32][2]*Vpk[32][32][2])+((Vpk[31][32][0]
          *Vpk[32][32][0])+(Vpk[31][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*Wpk[31][32][2]))+((.000117*(pin[32][0]*Wpk[31][32][0]))+(
          .000179*(pin[32][1]*Wpk[31][32][1])))));
        mm[32][32] = ((.205126*((Vpk[32][32][2]*Vpk[32][32][2])+((Vpk[32][32][0]
          *Vpk[32][32][0])+(Vpk[32][32][1]*Vpk[32][32][1]))))+((.000119*(
          pin[32][2]*pin[32][2]))+((.000117*(pin[32][0]*pin[32][0]))+(.000179*(
          pin[32][1]*pin[32][1])))));
/*
Check for singular mass matrix
*/
        for (i = 0; i < 33; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.17 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 3834 adds/subtracts/negates
                   6786 multiplies
                      0 divides
                    895 assignments
*/
}

void sddommldu(int routine)
{
    int i;
    int dumroutine,errnum;

    if (mmlduflg == 0) {
        sddomm(routine);
/*
Numerically decompose the mass matrix
*/
        sdldudcomp(33,33,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 33; i++) {
            if (mdi[i] <= 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmlduflg = 1;
        }
    }
}

void sdlhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    sddommldu(routine);
    sddofs0();
}

void sdmfrc(double imult[33])
{
/*
Calculate forces due to constraint multipliers.

*/

    if (pres[0]  !=  0.) {
        mtau[0] = imult[0];
    } else {
        mtau[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        mtau[1] = imult[1];
    } else {
        mtau[1] = 0.;
    }
    if (pres[2]  !=  0.) {
        mtau[2] = imult[2];
    } else {
        mtau[2] = 0.;
    }
    if (pres[3]  !=  0.) {
        mtau[3] = imult[3];
    } else {
        mtau[3] = 0.;
    }
    if (pres[4]  !=  0.) {
        mtau[4] = imult[4];
    } else {
        mtau[4] = 0.;
    }
    if (pres[5]  !=  0.) {
        mtau[5] = imult[5];
    } else {
        mtau[5] = 0.;
    }
    if (pres[6]  !=  0.) {
        mtau[6] = imult[6];
    } else {
        mtau[6] = 0.;
    }
    if (pres[7]  !=  0.) {
        mtau[7] = imult[7];
    } else {
        mtau[7] = 0.;
    }
    if (pres[8]  !=  0.) {
        mtau[8] = imult[8];
    } else {
        mtau[8] = 0.;
    }
    if (pres[9]  !=  0.) {
        mtau[9] = imult[9];
    } else {
        mtau[9] = 0.;
    }
    if (pres[10]  !=  0.) {
        mtau[10] = imult[10];
    } else {
        mtau[10] = 0.;
    }
    if (pres[11]  !=  0.) {
        mtau[11] = imult[11];
    } else {
        mtau[11] = 0.;
    }
    if (pres[12]  !=  0.) {
        mtau[12] = imult[12];
    } else {
        mtau[12] = 0.;
    }
    if (pres[13]  !=  0.) {
        mtau[13] = imult[13];
    } else {
        mtau[13] = 0.;
    }
    if (pres[14]  !=  0.) {
        mtau[14] = imult[14];
    } else {
        mtau[14] = 0.;
    }
    if (pres[15]  !=  0.) {
        mtau[15] = imult[15];
    } else {
        mtau[15] = 0.;
    }
    if (pres[16]  !=  0.) {
        mtau[16] = imult[16];
    } else {
        mtau[16] = 0.;
    }
    if (pres[17]  !=  0.) {
        mtau[17] = imult[17];
    } else {
        mtau[17] = 0.;
    }
    if (pres[18]  !=  0.) {
        mtau[18] = imult[18];
    } else {
        mtau[18] = 0.;
    }
    if (pres[19]  !=  0.) {
        mtau[19] = imult[19];
    } else {
        mtau[19] = 0.;
    }
    if (pres[20]  !=  0.) {
        mtau[20] = imult[20];
    } else {
        mtau[20] = 0.;
    }
    if (pres[21]  !=  0.) {
        mtau[21] = imult[21];
    } else {
        mtau[21] = 0.;
    }
    if (pres[22]  !=  0.) {
        mtau[22] = imult[22];
    } else {
        mtau[22] = 0.;
    }
    if (pres[23]  !=  0.) {
        mtau[23] = imult[23];
    } else {
        mtau[23] = 0.;
    }
    if (pres[24]  !=  0.) {
        mtau[24] = imult[24];
    } else {
        mtau[24] = 0.;
    }
    if (pres[25]  !=  0.) {
        mtau[25] = imult[25];
    } else {
        mtau[25] = 0.;
    }
    if (pres[26]  !=  0.) {
        mtau[26] = imult[26];
    } else {
        mtau[26] = 0.;
    }
    if (pres[27]  !=  0.) {
        mtau[27] = imult[27];
    } else {
        mtau[27] = 0.;
    }
    if (pres[28]  !=  0.) {
        mtau[28] = imult[28];
    } else {
        mtau[28] = 0.;
    }
    if (pres[29]  !=  0.) {
        mtau[29] = imult[29];
    } else {
        mtau[29] = 0.;
    }
    if (pres[30]  !=  0.) {
        mtau[30] = imult[30];
    } else {
        mtau[30] = 0.;
    }
    if (pres[31]  !=  0.) {
        mtau[31] = imult[31];
    } else {
        mtau[31] = 0.;
    }
    if (pres[32]  !=  0.) {
        mtau[32] = imult[32];
    } else {
        mtau[32] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     66 assignments
*/
}

void sdequivht(double tau[33])
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[33][3],tstareq[33][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[5][0] = -(ufk[0][0]+(11.15*gk[3][0]));
    fstareq[5][1] = -(ufk[0][1]+(11.15*gk[3][1]));
    fstareq[5][2] = -(ufk[0][2]+(11.15*gk[3][2]));
    fstareq[8][0] = -(ufk[1][0]+(32.413*gk[8][0]));
    fstareq[8][1] = -(ufk[1][1]+(32.413*gk[8][1]));
    fstareq[8][2] = -(ufk[1][2]+(32.413*gk[8][2]));
    fstareq[11][0] = -(ufk[2][0]+(8.806*gk[11][0]));
    fstareq[11][1] = -(ufk[2][1]+(8.806*gk[11][1]));
    fstareq[11][2] = -(ufk[2][2]+(8.806*gk[11][2]));
    fstareq[14][0] = -(ufk[3][0]+(3.51*gk[14][0]));
    fstareq[14][1] = -(ufk[3][1]+(3.51*gk[14][1]));
    fstareq[14][2] = -(ufk[3][2]+(3.51*gk[14][2]));
    fstareq[17][0] = -(ufk[4][0]+(1.2*gk[17][0]));
    fstareq[17][1] = -(ufk[4][1]+(1.2*gk[17][1]));
    fstareq[17][2] = -(ufk[4][2]+(1.2*gk[17][2]));
    fstareq[20][0] = -(ufk[5][0]+(.205126*gk[20][0]));
    fstareq[20][1] = -(ufk[5][1]+(.205126*gk[20][1]));
    fstareq[20][2] = -(ufk[5][2]+(.205126*gk[20][2]));
    fstareq[23][0] = -(ufk[6][0]+(8.806*gk[23][0]));
    fstareq[23][1] = -(ufk[6][1]+(8.806*gk[23][1]));
    fstareq[23][2] = -(ufk[6][2]+(8.806*gk[23][2]));
    fstareq[26][0] = -(ufk[7][0]+(3.51*gk[26][0]));
    fstareq[26][1] = -(ufk[7][1]+(3.51*gk[26][1]));
    fstareq[26][2] = -(ufk[7][2]+(3.51*gk[26][2]));
    fstareq[29][0] = -(ufk[8][0]+(1.2*gk[29][0]));
    fstareq[29][1] = -(ufk[8][1]+(1.2*gk[29][1]));
    fstareq[29][2] = -(ufk[8][2]+(1.2*gk[29][2]));
    fstareq[32][0] = -(ufk[9][0]+(.205126*gk[32][0]));
    fstareq[32][1] = -(ufk[9][1]+(.205126*gk[32][1]));
    fstareq[32][2] = -(ufk[9][2]+(.205126*gk[32][2]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    temp[0] = (((fstareq[14][2]*Vpk[0][14][2])+((fstareq[14][0]*Vpk[0][14][0])+(
      fstareq[14][1]*Vpk[0][14][1])))+(((fstareq[11][2]*Vpk[0][11][2])+((
      fstareq[11][0]*Vpk[0][11][0])+(fstareq[11][1]*Vpk[0][11][1])))+(((
      fstareq[5][2]*Vpk[0][3][2])+((fstareq[5][0]*Vpk[0][3][0])+(fstareq[5][1]*
      Vpk[0][3][1])))+((fstareq[8][2]*Vpk[0][8][2])+((fstareq[8][0]*Vpk[0][8][0]
      )+(fstareq[8][1]*Vpk[0][8][1]))))));
    temp[1] = (((fstareq[26][2]*Vpk[0][26][2])+((fstareq[26][0]*Vpk[0][26][0])+(
      fstareq[26][1]*Vpk[0][26][1])))+(((fstareq[23][2]*Vpk[0][23][2])+((
      fstareq[23][0]*Vpk[0][23][0])+(fstareq[23][1]*Vpk[0][23][1])))+(((
      fstareq[20][2]*Vpk[0][20][2])+((fstareq[20][0]*Vpk[0][20][0])+(
      fstareq[20][1]*Vpk[0][20][1])))+(((fstareq[17][2]*Vpk[0][17][2])+((
      fstareq[17][0]*Vpk[0][17][0])+(fstareq[17][1]*Vpk[0][17][1])))+temp[0]))))
      ;
    tau[0] = (utau[0]-(((fstareq[32][2]*Vpk[0][32][2])+((fstareq[32][0]*
      Vpk[0][32][0])+(fstareq[32][1]*Vpk[0][32][1])))+(((fstareq[29][2]*
      Vpk[0][29][2])+((fstareq[29][0]*Vpk[0][29][0])+(fstareq[29][1]*
      Vpk[0][29][1])))+temp[1])));
    temp[0] = (((fstareq[14][2]*Vpk[1][14][2])+((fstareq[14][0]*Vpk[1][14][0])+(
      fstareq[14][1]*Vpk[1][14][1])))+(((fstareq[11][2]*Vpk[1][11][2])+((
      fstareq[11][0]*Vpk[1][11][0])+(fstareq[11][1]*Vpk[1][11][1])))+(((
      fstareq[5][2]*Vpk[1][3][2])+((fstareq[5][0]*Vpk[1][3][0])+(fstareq[5][1]*
      Vpk[1][3][1])))+((fstareq[8][2]*Vpk[1][8][2])+((fstareq[8][0]*Vpk[1][8][0]
      )+(fstareq[8][1]*Vpk[1][8][1]))))));
    temp[1] = (((fstareq[26][2]*Vpk[1][26][2])+((fstareq[26][0]*Vpk[1][26][0])+(
      fstareq[26][1]*Vpk[1][26][1])))+(((fstareq[23][2]*Vpk[1][23][2])+((
      fstareq[23][0]*Vpk[1][23][0])+(fstareq[23][1]*Vpk[1][23][1])))+(((
      fstareq[20][2]*Vpk[1][20][2])+((fstareq[20][0]*Vpk[1][20][0])+(
      fstareq[20][1]*Vpk[1][20][1])))+(((fstareq[17][2]*Vpk[1][17][2])+((
      fstareq[17][0]*Vpk[1][17][0])+(fstareq[17][1]*Vpk[1][17][1])))+temp[0]))))
      ;
    tau[1] = (utau[1]-(((fstareq[32][2]*Vpk[1][32][2])+((fstareq[32][0]*
      Vpk[1][32][0])+(fstareq[32][1]*Vpk[1][32][1])))+(((fstareq[29][2]*
      Vpk[1][29][2])+((fstareq[29][0]*Vpk[1][29][0])+(fstareq[29][1]*
      Vpk[1][29][1])))+temp[1])));
    temp[0] = (((fstareq[14][2]*Vpk[2][14][2])+((fstareq[14][0]*Vpk[2][14][0])+(
      fstareq[14][1]*Vpk[2][14][1])))+(((fstareq[11][2]*Vpk[2][11][2])+((
      fstareq[11][0]*Vpk[2][11][0])+(fstareq[11][1]*Vpk[2][11][1])))+(((
      fstareq[5][2]*Vpk[2][3][2])+((fstareq[5][0]*Vpk[2][3][0])+(fstareq[5][1]*
      Vpk[2][3][1])))+((fstareq[8][2]*Vpk[2][8][2])+((fstareq[8][0]*Vpk[2][8][0]
      )+(fstareq[8][1]*Vpk[2][8][1]))))));
    temp[1] = (((fstareq[26][2]*Vpk[2][26][2])+((fstareq[26][0]*Vpk[2][26][0])+(
      fstareq[26][1]*Vpk[2][26][1])))+(((fstareq[23][2]*Vpk[2][23][2])+((
      fstareq[23][0]*Vpk[2][23][0])+(fstareq[23][1]*Vpk[2][23][1])))+(((
      fstareq[20][2]*Vpk[2][20][2])+((fstareq[20][0]*Vpk[2][20][0])+(
      fstareq[20][1]*Vpk[2][20][1])))+(((fstareq[17][2]*Vpk[2][17][2])+((
      fstareq[17][0]*Vpk[2][17][0])+(fstareq[17][1]*Vpk[2][17][1])))+temp[0]))))
      ;
    tau[2] = (utau[2]-(((fstareq[32][2]*Vpk[2][32][2])+((fstareq[32][0]*
      Vpk[2][32][0])+(fstareq[32][1]*Vpk[2][32][1])))+(((fstareq[29][2]*
      Vpk[2][29][2])+((fstareq[29][0]*Vpk[2][29][0])+(fstareq[29][1]*
      Vpk[2][29][1])))+temp[1])));
    temp[0] = ((((fstareq[11][2]*Vpk[3][11][2])+((fstareq[11][0]*Vpk[3][11][0])+
      (fstareq[11][1]*Vpk[3][11][1])))-((utk[2][2]*Wpk[3][11][2])+((utk[2][0]*
      Wpk[3][11][0])+(utk[2][1]*Wpk[3][11][1]))))+((((fstareq[8][2]*Vpk[3][8][2]
      )+((fstareq[8][0]*Vpk[3][8][0])+(fstareq[8][1]*Vpk[3][8][1])))-((utk[1][2]
      *Wpk[3][8][2])+((utk[1][0]*Wpk[3][8][0])+(utk[1][1]*Wpk[3][8][1]))))-
      utk[0][0]));
    temp[1] = ((((fstareq[17][2]*Vpk[3][17][2])+((fstareq[17][0]*Vpk[3][17][0])+
      (fstareq[17][1]*Vpk[3][17][1])))-((utk[4][2]*Wpk[3][17][2])+((utk[4][0]*
      Wpk[3][17][0])+(utk[4][1]*Wpk[3][17][1]))))+((((fstareq[14][2]*
      Vpk[3][14][2])+((fstareq[14][0]*Vpk[3][14][0])+(fstareq[14][1]*
      Vpk[3][14][1])))-((utk[3][2]*Wpk[3][14][2])+((utk[3][0]*Wpk[3][14][0])+(
      utk[3][1]*Wpk[3][14][1]))))+temp[0]));
    temp[2] = ((((fstareq[23][2]*Vpk[3][23][2])+((fstareq[23][0]*Vpk[3][23][0])+
      (fstareq[23][1]*Vpk[3][23][1])))-((utk[6][2]*Wpk[3][23][2])+((utk[6][0]*
      Wpk[3][23][0])+(utk[6][1]*Wpk[3][23][1]))))+((((fstareq[20][2]*
      Vpk[3][20][2])+((fstareq[20][0]*Vpk[3][20][0])+(fstareq[20][1]*
      Vpk[3][20][1])))-((utk[5][2]*Wpk[3][20][2])+((utk[5][0]*Wpk[3][20][0])+(
      utk[5][1]*Wpk[3][20][1]))))+temp[1]));
    temp[3] = ((((fstareq[29][2]*Vpk[3][29][2])+((fstareq[29][0]*Vpk[3][29][0])+
      (fstareq[29][1]*Vpk[3][29][1])))-((utk[8][2]*Wpk[3][29][2])+((utk[8][0]*
      Wpk[3][29][0])+(utk[8][1]*Wpk[3][29][1]))))+((((fstareq[26][2]*
      Vpk[3][26][2])+((fstareq[26][0]*Vpk[3][26][0])+(fstareq[26][1]*
      Vpk[3][26][1])))-((utk[7][2]*Wpk[3][26][2])+((utk[7][0]*Wpk[3][26][0])+(
      utk[7][1]*Wpk[3][26][1]))))+temp[2]));
    tau[3] = (utau[3]-((((fstareq[32][2]*Vpk[3][32][2])+((fstareq[32][0]*
      Vpk[3][32][0])+(fstareq[32][1]*Vpk[3][32][1])))-((utk[9][2]*Wpk[3][32][2])
      +((utk[9][0]*Wpk[3][32][0])+(utk[9][1]*Wpk[3][32][1]))))+temp[3]));
    temp[0] = ((((.3202*((fstareq[8][2]*Wpk[4][8][0])-(fstareq[8][0]*
      Wpk[4][8][2])))-((utk[1][2]*Wpk[4][8][2])+((utk[1][0]*Wpk[4][8][0])+(
      utk[1][1]*Wpk[4][8][1]))))-utk[0][1])+(((fstareq[11][2]*Vpk[4][11][2])+((
      fstareq[11][0]*Vpk[4][11][0])+(fstareq[11][1]*Vpk[4][11][1])))-((utk[2][2]
      *Wpk[4][11][2])+((utk[2][0]*Wpk[4][11][0])+(utk[2][1]*Wpk[4][11][1])))));
    temp[1] = ((((fstareq[17][2]*Vpk[4][17][2])+((fstareq[17][0]*Vpk[4][17][0])+
      (fstareq[17][1]*Vpk[4][17][1])))-((utk[4][2]*Wpk[4][17][2])+((utk[4][0]*
      Wpk[4][17][0])+(utk[4][1]*Wpk[4][17][1]))))+((((fstareq[14][2]*
      Vpk[4][14][2])+((fstareq[14][0]*Vpk[4][14][0])+(fstareq[14][1]*
      Vpk[4][14][1])))-((utk[3][2]*Wpk[4][14][2])+((utk[3][0]*Wpk[4][14][0])+(
      utk[3][1]*Wpk[4][14][1]))))+temp[0]));
    temp[2] = ((((fstareq[23][2]*Vpk[4][23][2])+((fstareq[23][0]*Vpk[4][23][0])+
      (fstareq[23][1]*Vpk[4][23][1])))-((utk[6][2]*Wpk[4][23][2])+((utk[6][0]*
      Wpk[4][23][0])+(utk[6][1]*Wpk[4][23][1]))))+((((fstareq[20][2]*
      Vpk[4][20][2])+((fstareq[20][0]*Vpk[4][20][0])+(fstareq[20][1]*
      Vpk[4][20][1])))-((utk[5][2]*Wpk[4][20][2])+((utk[5][0]*Wpk[4][20][0])+(
      utk[5][1]*Wpk[4][20][1]))))+temp[1]));
    temp[3] = ((((fstareq[29][2]*Vpk[4][29][2])+((fstareq[29][0]*Vpk[4][29][0])+
      (fstareq[29][1]*Vpk[4][29][1])))-((utk[8][2]*Wpk[4][29][2])+((utk[8][0]*
      Wpk[4][29][0])+(utk[8][1]*Wpk[4][29][1]))))+((((fstareq[26][2]*
      Vpk[4][26][2])+((fstareq[26][0]*Vpk[4][26][0])+(fstareq[26][1]*
      Vpk[4][26][1])))-((utk[7][2]*Wpk[4][26][2])+((utk[7][0]*Wpk[4][26][0])+(
      utk[7][1]*Wpk[4][26][1]))))+temp[2]));
    tau[4] = (utau[4]-((((fstareq[32][2]*Vpk[4][32][2])+((fstareq[32][0]*
      Vpk[4][32][0])+(fstareq[32][1]*Vpk[4][32][1])))-((utk[9][2]*Wpk[4][32][2])
      +((utk[9][0]*Wpk[4][32][0])+(utk[9][1]*Wpk[4][32][1]))))+temp[3]));
    temp[0] = ((((fstareq[11][2]*Vpk[5][11][2])+((fstareq[11][0]*Vpk[5][11][0])+
      (fstareq[11][1]*Vpk[5][11][1])))-((utk[2][2]*Wpk[5][11][2])+((utk[2][0]*
      Wpk[5][11][0])+(utk[2][1]*Wpk[5][11][1]))))+((((fstareq[8][2]*Vpk[5][8][2]
      )+((fstareq[8][0]*Vpk[5][8][0])+(fstareq[8][1]*Vpk[5][8][1])))-((utk[1][2]
      *Wpk[5][8][2])+((utk[1][0]*Wpk[5][8][0])+(utk[1][1]*Wpk[5][8][1]))))-
      utk[0][2]));
    temp[1] = ((((fstareq[17][2]*Vpk[5][17][2])+((fstareq[17][0]*Vpk[5][17][0])+
      (fstareq[17][1]*Vpk[5][17][1])))-((utk[4][2]*Wpk[5][17][2])+((utk[4][0]*
      Wpk[5][17][0])+(utk[4][1]*Wpk[5][17][1]))))+((((fstareq[14][2]*
      Vpk[5][14][2])+((fstareq[14][0]*Vpk[5][14][0])+(fstareq[14][1]*
      Vpk[5][14][1])))-((utk[3][2]*Wpk[5][14][2])+((utk[3][0]*Wpk[5][14][0])+(
      utk[3][1]*Wpk[5][14][1]))))+temp[0]));
    temp[2] = ((((fstareq[23][2]*Vpk[5][23][2])+((fstareq[23][0]*Vpk[5][23][0])+
      (fstareq[23][1]*Vpk[5][23][1])))-((utk[6][2]*Wpk[5][23][2])+((utk[6][0]*
      Wpk[5][23][0])+(utk[6][1]*Wpk[5][23][1]))))+((((fstareq[20][2]*
      Vpk[5][20][2])+((fstareq[20][0]*Vpk[5][20][0])+(fstareq[20][1]*
      Vpk[5][20][1])))-((utk[5][2]*Wpk[5][20][2])+((utk[5][0]*Wpk[5][20][0])+(
      utk[5][1]*Wpk[5][20][1]))))+temp[1]));
    temp[3] = ((((fstareq[29][2]*Vpk[5][29][2])+((fstareq[29][0]*Vpk[5][29][0])+
      (fstareq[29][1]*Vpk[5][29][1])))-((utk[8][2]*Wpk[5][29][2])+((utk[8][0]*
      Wpk[5][29][0])+(utk[8][1]*Wpk[5][29][1]))))+((((fstareq[26][2]*
      Vpk[5][26][2])+((fstareq[26][0]*Vpk[5][26][0])+(fstareq[26][1]*
      Vpk[5][26][1])))-((utk[7][2]*Wpk[5][26][2])+((utk[7][0]*Wpk[5][26][0])+(
      utk[7][1]*Wpk[5][26][1]))))+temp[2]));
    tau[5] = (utau[5]-((((fstareq[32][2]*Vpk[5][32][2])+((fstareq[32][0]*
      Vpk[5][32][0])+(fstareq[32][1]*Vpk[5][32][1])))-((utk[9][2]*Wpk[5][32][2])
      +((utk[9][0]*Wpk[5][32][0])+(utk[9][1]*Wpk[5][32][1]))))+temp[3]));
    tau[6] = (utau[6]-((.3202*((fstareq[8][2]*Wpk[6][8][0])-(fstareq[8][0]*
      Wpk[6][8][2])))-((utk[1][2]*Wpk[6][8][2])+((utk[1][0]*Wpk[6][8][0])+(
      utk[1][1]*Wpk[6][8][1])))));
    tau[7] = (utau[7]-((.3202*((fstareq[8][2]*Wpk[7][8][0])-(fstareq[8][0]*
      Wpk[7][8][2])))-((utk[1][2]*Wpk[7][8][2])+((utk[1][0]*Wpk[7][8][0])+(
      utk[1][1]*Wpk[7][8][1])))));
    tau[8] = (utau[8]-((.3202*((fstareq[8][2]*pin[8][0])-(fstareq[8][0]*
      pin[8][2])))-((pin[8][2]*utk[1][2])+((pin[8][0]*utk[1][0])+(pin[8][1]*
      utk[1][1])))));
    temp[0] = ((((fstareq[11][2]*Vpk[9][11][2])+((.1715*(fstareq[11][0]*
      Wpk[9][11][2]))-(.002*(fstareq[11][1]*Wpk[9][11][2]))))-((utk[2][2]*
      Wpk[9][11][2])+((utk[2][0]*Wpk[9][11][0])+(utk[2][1]*Wpk[9][11][1]))))+(((
      fstareq[14][2]*Vpk[9][14][2])+((fstareq[14][0]*Vpk[9][14][0])+(
      fstareq[14][1]*Vpk[9][14][1])))-((utk[3][2]*Wpk[9][14][2])+((utk[3][0]*
      Wpk[9][14][0])+(utk[3][1]*Wpk[9][14][1])))));
    tau[9] = (utau[9]-((((fstareq[20][2]*Vpk[9][20][2])+((fstareq[20][0]*
      Vpk[9][20][0])+(fstareq[20][1]*Vpk[9][20][1])))-((utk[5][2]*Wpk[9][20][2])
      +((utk[5][0]*Wpk[9][20][0])+(utk[5][1]*Wpk[9][20][1]))))+((((
      fstareq[17][2]*Vpk[9][17][2])+((fstareq[17][0]*Vpk[9][17][0])+(
      fstareq[17][1]*Vpk[9][17][1])))-((utk[4][2]*Wpk[9][17][2])+((utk[4][0]*
      Wpk[9][17][0])+(utk[4][1]*Wpk[9][17][1]))))+temp[0])));
    temp[0] = ((((fstareq[11][2]*Vpk[10][11][2])+((.1715*(fstareq[11][0]*
      Wpk[10][11][2]))-(.002*(fstareq[11][1]*Wpk[10][11][2]))))-((utk[2][2]*
      Wpk[10][11][2])+((utk[2][0]*Wpk[10][11][0])+(utk[2][1]*Wpk[10][11][1]))))+
      (((fstareq[14][2]*Vpk[10][14][2])+((fstareq[14][0]*Vpk[10][14][0])+(
      fstareq[14][1]*Vpk[10][14][1])))-((utk[3][2]*Wpk[10][14][2])+((utk[3][0]*
      Wpk[10][14][0])+(utk[3][1]*Wpk[10][14][1])))));
    tau[10] = (utau[10]-((((fstareq[20][2]*Vpk[10][20][2])+((fstareq[20][0]*
      Vpk[10][20][0])+(fstareq[20][1]*Vpk[10][20][1])))-((utk[5][2]*
      Wpk[10][20][2])+((utk[5][0]*Wpk[10][20][0])+(utk[5][1]*Wpk[10][20][1]))))+
      ((((fstareq[17][2]*Vpk[10][17][2])+((fstareq[17][0]*Vpk[10][17][0])+(
      fstareq[17][1]*Vpk[10][17][1])))-((utk[4][2]*Wpk[10][17][2])+((utk[4][0]*
      Wpk[10][17][0])+(utk[4][1]*Wpk[10][17][1]))))+temp[0])));
    temp[0] = ((((fstareq[11][2]*Vpk[11][11][2])+((.1715*(fstareq[11][0]*
      pin[11][2]))-(.002*(fstareq[11][1]*pin[11][2]))))-((pin[11][2]*utk[2][2])+
      ((pin[11][0]*utk[2][0])+(pin[11][1]*utk[2][1]))))+(((fstareq[14][2]*
      Vpk[11][14][2])+((fstareq[14][0]*Vpk[11][14][0])+(fstareq[14][1]*
      Vpk[11][14][1])))-((utk[3][2]*Wpk[11][14][2])+((utk[3][0]*Wpk[11][14][0])+
      (utk[3][1]*Wpk[11][14][1])))));
    tau[11] = (utau[11]-((((fstareq[20][2]*Vpk[11][20][2])+((fstareq[20][0]*
      Vpk[11][20][0])+(fstareq[20][1]*Vpk[11][20][1])))-((utk[5][2]*
      Wpk[11][20][2])+((utk[5][0]*Wpk[11][20][0])+(utk[5][1]*Wpk[11][20][1]))))+
      ((((fstareq[17][2]*Vpk[11][17][2])+((fstareq[17][0]*Vpk[11][17][0])+(
      fstareq[17][1]*Vpk[11][17][1])))-((utk[4][2]*Wpk[11][17][2])+((utk[4][0]*
      Wpk[11][17][0])+(utk[4][1]*Wpk[11][17][1]))))+temp[0])));
    temp[0] = (((.1862*((fstareq[14][0]*Wpk[12][14][2])-(fstareq[14][2]*
      Wpk[12][14][0])))-((utk[3][2]*Wpk[12][14][2])+((utk[3][0]*Wpk[12][14][0])+
      (utk[3][1]*Wpk[12][14][1]))))+(((fstareq[17][2]*Vpk[12][17][2])+((
      fstareq[17][0]*Vpk[12][17][0])+(fstareq[17][1]*Vpk[12][17][1])))-((
      utk[4][2]*Wpk[12][17][2])+((utk[4][0]*Wpk[12][17][0])+(utk[4][1]*
      Wpk[12][17][1])))));
    tau[12] = (utau[12]-(temp[0]+(((fstareq[20][2]*Vpk[12][20][2])+((
      fstareq[20][0]*Vpk[12][20][0])+(fstareq[20][1]*Vpk[12][20][1])))-((
      utk[5][2]*Wpk[12][20][2])+((utk[5][0]*Wpk[12][20][0])+(utk[5][1]*
      Wpk[12][20][1]))))));
    temp[0] = (((.1862*((fstareq[14][0]*Wpk[13][14][2])-(fstareq[14][2]*
      Wpk[13][14][0])))-((utk[3][2]*Wpk[13][14][2])+((utk[3][0]*Wpk[13][14][0])+
      (utk[3][1]*Wpk[13][14][1]))))+(((fstareq[17][2]*Vpk[13][17][2])+((
      fstareq[17][0]*Vpk[13][17][0])+(fstareq[17][1]*Vpk[13][17][1])))-((
      utk[4][2]*Wpk[13][17][2])+((utk[4][0]*Wpk[13][17][0])+(utk[4][1]*
      Wpk[13][17][1])))));
    tau[13] = (utau[13]-(temp[0]+(((fstareq[20][2]*Vpk[13][20][2])+((
      fstareq[20][0]*Vpk[13][20][0])+(fstareq[20][1]*Vpk[13][20][1])))-((
      utk[5][2]*Wpk[13][20][2])+((utk[5][0]*Wpk[13][20][0])+(utk[5][1]*
      Wpk[13][20][1]))))));
    temp[0] = (((.1862*((fstareq[14][0]*pin[14][2])-(fstareq[14][2]*pin[14][0]))
      )-((pin[14][2]*utk[3][2])+((pin[14][0]*utk[3][0])+(pin[14][1]*utk[3][1])))
      )+(((fstareq[17][2]*Vpk[14][17][2])+((fstareq[17][0]*Vpk[14][17][0])+(
      fstareq[17][1]*Vpk[14][17][1])))-((utk[4][2]*Wpk[14][17][2])+((utk[4][0]*
      Wpk[14][17][0])+(utk[4][1]*Wpk[14][17][1])))));
    tau[14] = (utau[14]-(temp[0]+(((fstareq[20][2]*Vpk[14][20][2])+((
      fstareq[20][0]*Vpk[14][20][0])+(fstareq[20][1]*Vpk[14][20][1])))-((
      utk[5][2]*Wpk[14][20][2])+((utk[5][0]*Wpk[14][20][0])+(utk[5][1]*
      Wpk[14][20][1]))))));
    tau[15] = (utau[15]-((((fstareq[17][2]*Vpk[15][17][2])+((fstareq[17][0]*
      Vpk[15][17][0])+(fstareq[17][1]*Vpk[15][17][1])))-((utk[4][2]*
      Wpk[15][17][2])+((utk[4][0]*Wpk[15][17][0])+(utk[4][1]*Wpk[15][17][1]))))+
      (((fstareq[20][2]*Vpk[15][20][2])+((fstareq[20][0]*Vpk[15][20][0])+(
      fstareq[20][1]*Vpk[15][20][1])))-((utk[5][2]*Wpk[15][20][2])+((utk[5][0]*
      Wpk[15][20][0])+(utk[5][1]*Wpk[15][20][1]))))));
    tau[16] = (utau[16]-((((fstareq[17][2]*Vpk[16][17][2])+((fstareq[17][0]*
      Vpk[16][17][0])+(fstareq[17][1]*Vpk[16][17][1])))-((utk[4][2]*
      Wpk[16][17][2])+((utk[4][0]*Wpk[16][17][0])+(utk[4][1]*Wpk[16][17][1]))))+
      (((fstareq[20][2]*Vpk[16][20][2])+((fstareq[20][0]*Vpk[16][20][0])+(
      fstareq[20][1]*Vpk[16][20][1])))-((utk[5][2]*Wpk[16][20][2])+((utk[5][0]*
      Wpk[16][20][0])+(utk[5][1]*Wpk[16][20][1]))))));
    tau[17] = (utau[17]-((((fstareq[17][2]*Vpk[17][17][2])+((fstareq[17][0]*
      Vpk[17][17][0])+(fstareq[17][1]*Vpk[17][17][1])))-((pin[17][2]*utk[4][2])+
      ((pin[17][0]*utk[4][0])+(pin[17][1]*utk[4][1]))))+(((fstareq[20][2]*
      Vpk[17][20][2])+((fstareq[20][0]*Vpk[17][20][0])+(fstareq[20][1]*
      Vpk[17][20][1])))-((utk[5][2]*Wpk[17][20][2])+((utk[5][0]*Wpk[17][20][0])+
      (utk[5][1]*Wpk[17][20][1]))))));
    tau[18] = (utau[18]-(((fstareq[20][2]*Vpk[18][20][2])+((fstareq[20][0]*
      Vpk[18][20][0])+(fstareq[20][1]*Vpk[18][20][1])))-((utk[5][2]*
      Wpk[18][20][2])+((utk[5][0]*Wpk[18][20][0])+(utk[5][1]*Wpk[18][20][1])))))
      ;
    tau[19] = (utau[19]-(((fstareq[20][2]*Vpk[19][20][2])+((fstareq[20][0]*
      Vpk[19][20][0])+(fstareq[20][1]*Vpk[19][20][1])))-((utk[5][2]*
      Wpk[19][20][2])+((utk[5][0]*Wpk[19][20][0])+(utk[5][1]*Wpk[19][20][1])))))
      ;
    tau[20] = (utau[20]-(((fstareq[20][2]*Vpk[20][20][2])+((fstareq[20][0]*
      Vpk[20][20][0])+(fstareq[20][1]*Vpk[20][20][1])))-((pin[20][2]*utk[5][2])+
      ((pin[20][0]*utk[5][0])+(pin[20][1]*utk[5][1])))));
    temp[0] = ((((fstareq[23][2]*Vpk[21][23][2])+((.1715*(fstareq[23][0]*
      Wpk[21][23][2]))-(.002*(fstareq[23][1]*Wpk[21][23][2]))))-((utk[6][2]*
      Wpk[21][23][2])+((utk[6][0]*Wpk[21][23][0])+(utk[6][1]*Wpk[21][23][1]))))+
      (((fstareq[26][2]*Vpk[21][26][2])+((fstareq[26][0]*Vpk[21][26][0])+(
      fstareq[26][1]*Vpk[21][26][1])))-((utk[7][2]*Wpk[21][26][2])+((utk[7][0]*
      Wpk[21][26][0])+(utk[7][1]*Wpk[21][26][1])))));
    tau[21] = (utau[21]-((((fstareq[32][2]*Vpk[21][32][2])+((fstareq[32][0]*
      Vpk[21][32][0])+(fstareq[32][1]*Vpk[21][32][1])))-((utk[9][2]*
      Wpk[21][32][2])+((utk[9][0]*Wpk[21][32][0])+(utk[9][1]*Wpk[21][32][1]))))+
      ((((fstareq[29][2]*Vpk[21][29][2])+((fstareq[29][0]*Vpk[21][29][0])+(
      fstareq[29][1]*Vpk[21][29][1])))-((utk[8][2]*Wpk[21][29][2])+((utk[8][0]*
      Wpk[21][29][0])+(utk[8][1]*Wpk[21][29][1]))))+temp[0])));
    temp[0] = ((((fstareq[23][2]*Vpk[22][23][2])+((.1715*(fstareq[23][0]*
      Wpk[22][23][2]))-(.002*(fstareq[23][1]*Wpk[22][23][2]))))-((utk[6][2]*
      Wpk[22][23][2])+((utk[6][0]*Wpk[22][23][0])+(utk[6][1]*Wpk[22][23][1]))))+
      (((fstareq[26][2]*Vpk[22][26][2])+((fstareq[26][0]*Vpk[22][26][0])+(
      fstareq[26][1]*Vpk[22][26][1])))-((utk[7][2]*Wpk[22][26][2])+((utk[7][0]*
      Wpk[22][26][0])+(utk[7][1]*Wpk[22][26][1])))));
    tau[22] = (utau[22]-((((fstareq[32][2]*Vpk[22][32][2])+((fstareq[32][0]*
      Vpk[22][32][0])+(fstareq[32][1]*Vpk[22][32][1])))-((utk[9][2]*
      Wpk[22][32][2])+((utk[9][0]*Wpk[22][32][0])+(utk[9][1]*Wpk[22][32][1]))))+
      ((((fstareq[29][2]*Vpk[22][29][2])+((fstareq[29][0]*Vpk[22][29][0])+(
      fstareq[29][1]*Vpk[22][29][1])))-((utk[8][2]*Wpk[22][29][2])+((utk[8][0]*
      Wpk[22][29][0])+(utk[8][1]*Wpk[22][29][1]))))+temp[0])));
    temp[0] = ((((fstareq[23][2]*Vpk[23][23][2])+((.1715*(fstareq[23][0]*
      pin[23][2]))-(.002*(fstareq[23][1]*pin[23][2]))))-((pin[23][2]*utk[6][2])+
      ((pin[23][0]*utk[6][0])+(pin[23][1]*utk[6][1]))))+(((fstareq[26][2]*
      Vpk[23][26][2])+((fstareq[26][0]*Vpk[23][26][0])+(fstareq[26][1]*
      Vpk[23][26][1])))-((utk[7][2]*Wpk[23][26][2])+((utk[7][0]*Wpk[23][26][0])+
      (utk[7][1]*Wpk[23][26][1])))));
    tau[23] = (utau[23]-((((fstareq[32][2]*Vpk[23][32][2])+((fstareq[32][0]*
      Vpk[23][32][0])+(fstareq[32][1]*Vpk[23][32][1])))-((utk[9][2]*
      Wpk[23][32][2])+((utk[9][0]*Wpk[23][32][0])+(utk[9][1]*Wpk[23][32][1]))))+
      ((((fstareq[29][2]*Vpk[23][29][2])+((fstareq[29][0]*Vpk[23][29][0])+(
      fstareq[29][1]*Vpk[23][29][1])))-((utk[8][2]*Wpk[23][29][2])+((utk[8][0]*
      Wpk[23][29][0])+(utk[8][1]*Wpk[23][29][1]))))+temp[0])));
    temp[0] = (((.1862*((fstareq[26][0]*Wpk[24][26][2])-(fstareq[26][2]*
      Wpk[24][26][0])))-((utk[7][2]*Wpk[24][26][2])+((utk[7][0]*Wpk[24][26][0])+
      (utk[7][1]*Wpk[24][26][1]))))+(((fstareq[29][2]*Vpk[24][29][2])+((
      fstareq[29][0]*Vpk[24][29][0])+(fstareq[29][1]*Vpk[24][29][1])))-((
      utk[8][2]*Wpk[24][29][2])+((utk[8][0]*Wpk[24][29][0])+(utk[8][1]*
      Wpk[24][29][1])))));
    tau[24] = (utau[24]-(temp[0]+(((fstareq[32][2]*Vpk[24][32][2])+((
      fstareq[32][0]*Vpk[24][32][0])+(fstareq[32][1]*Vpk[24][32][1])))-((
      utk[9][2]*Wpk[24][32][2])+((utk[9][0]*Wpk[24][32][0])+(utk[9][1]*
      Wpk[24][32][1]))))));
    temp[0] = (((.1862*((fstareq[26][0]*Wpk[25][26][2])-(fstareq[26][2]*
      Wpk[25][26][0])))-((utk[7][2]*Wpk[25][26][2])+((utk[7][0]*Wpk[25][26][0])+
      (utk[7][1]*Wpk[25][26][1]))))+(((fstareq[29][2]*Vpk[25][29][2])+((
      fstareq[29][0]*Vpk[25][29][0])+(fstareq[29][1]*Vpk[25][29][1])))-((
      utk[8][2]*Wpk[25][29][2])+((utk[8][0]*Wpk[25][29][0])+(utk[8][1]*
      Wpk[25][29][1])))));
    tau[25] = (utau[25]-(temp[0]+(((fstareq[32][2]*Vpk[25][32][2])+((
      fstareq[32][0]*Vpk[25][32][0])+(fstareq[32][1]*Vpk[25][32][1])))-((
      utk[9][2]*Wpk[25][32][2])+((utk[9][0]*Wpk[25][32][0])+(utk[9][1]*
      Wpk[25][32][1]))))));
    temp[0] = (((.1862*((fstareq[26][0]*pin[26][2])-(fstareq[26][2]*pin[26][0]))
      )-((pin[26][2]*utk[7][2])+((pin[26][0]*utk[7][0])+(pin[26][1]*utk[7][1])))
      )+(((fstareq[29][2]*Vpk[26][29][2])+((fstareq[29][0]*Vpk[26][29][0])+(
      fstareq[29][1]*Vpk[26][29][1])))-((utk[8][2]*Wpk[26][29][2])+((utk[8][0]*
      Wpk[26][29][0])+(utk[8][1]*Wpk[26][29][1])))));
    tau[26] = (utau[26]-(temp[0]+(((fstareq[32][2]*Vpk[26][32][2])+((
      fstareq[32][0]*Vpk[26][32][0])+(fstareq[32][1]*Vpk[26][32][1])))-((
      utk[9][2]*Wpk[26][32][2])+((utk[9][0]*Wpk[26][32][0])+(utk[9][1]*
      Wpk[26][32][1]))))));
    tau[27] = (utau[27]-((((fstareq[29][2]*Vpk[27][29][2])+((fstareq[29][0]*
      Vpk[27][29][0])+(fstareq[29][1]*Vpk[27][29][1])))-((utk[8][2]*
      Wpk[27][29][2])+((utk[8][0]*Wpk[27][29][0])+(utk[8][1]*Wpk[27][29][1]))))+
      (((fstareq[32][2]*Vpk[27][32][2])+((fstareq[32][0]*Vpk[27][32][0])+(
      fstareq[32][1]*Vpk[27][32][1])))-((utk[9][2]*Wpk[27][32][2])+((utk[9][0]*
      Wpk[27][32][0])+(utk[9][1]*Wpk[27][32][1]))))));
    tau[28] = (utau[28]-((((fstareq[29][2]*Vpk[28][29][2])+((fstareq[29][0]*
      Vpk[28][29][0])+(fstareq[29][1]*Vpk[28][29][1])))-((utk[8][2]*
      Wpk[28][29][2])+((utk[8][0]*Wpk[28][29][0])+(utk[8][1]*Wpk[28][29][1]))))+
      (((fstareq[32][2]*Vpk[28][32][2])+((fstareq[32][0]*Vpk[28][32][0])+(
      fstareq[32][1]*Vpk[28][32][1])))-((utk[9][2]*Wpk[28][32][2])+((utk[9][0]*
      Wpk[28][32][0])+(utk[9][1]*Wpk[28][32][1]))))));
    tau[29] = (utau[29]-((((fstareq[29][2]*Vpk[29][29][2])+((fstareq[29][0]*
      Vpk[29][29][0])+(fstareq[29][1]*Vpk[29][29][1])))-((pin[29][2]*utk[8][2])+
      ((pin[29][0]*utk[8][0])+(pin[29][1]*utk[8][1]))))+(((fstareq[32][2]*
      Vpk[29][32][2])+((fstareq[32][0]*Vpk[29][32][0])+(fstareq[32][1]*
      Vpk[29][32][1])))-((utk[9][2]*Wpk[29][32][2])+((utk[9][0]*Wpk[29][32][0])+
      (utk[9][1]*Wpk[29][32][1]))))));
    tau[30] = (utau[30]-(((fstareq[32][2]*Vpk[30][32][2])+((fstareq[32][0]*
      Vpk[30][32][0])+(fstareq[32][1]*Vpk[30][32][1])))-((utk[9][2]*
      Wpk[30][32][2])+((utk[9][0]*Wpk[30][32][0])+(utk[9][1]*Wpk[30][32][1])))))
      ;
    tau[31] = (utau[31]-(((fstareq[32][2]*Vpk[31][32][2])+((fstareq[32][0]*
      Vpk[31][32][0])+(fstareq[32][1]*Vpk[31][32][1])))-((utk[9][2]*
      Wpk[31][32][2])+((utk[9][0]*Wpk[31][32][0])+(utk[9][1]*Wpk[31][32][1])))))
      ;
    tau[32] = (utau[32]-(((fstareq[32][2]*Vpk[32][32][2])+((fstareq[32][0]*
      Vpk[32][32][0])+(fstareq[32][1]*Vpk[32][32][1])))-((pin[32][2]*utk[9][2])+
      ((pin[32][0]*utk[9][0])+(pin[32][1]*utk[9][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  683 adds/subtracts/negates
                    672 multiplies
                      0 divides
                     93 assignments
*/
}

void sdfs0(void)
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
    fs[9] = fs0[9];
    fs[10] = fs0[10];
    fs[11] = fs0[11];
    fs[12] = fs0[12];
    fs[13] = fs0[13];
    fs[14] = fs0[14];
    fs[15] = fs0[15];
    fs[16] = fs0[16];
    fs[17] = fs0[17];
    fs[18] = fs0[18];
    fs[19] = fs0[19];
    fs[20] = fs0[20];
    fs[21] = fs0[21];
    fs[22] = fs0[22];
    fs[23] = fs0[23];
    fs[24] = fs0[24];
    fs[25] = fs0[25];
    fs[26] = fs0[26];
    fs[27] = fs0[27];
    fs[28] = fs0[28];
    fs[29] = fs0[29];
    fs[30] = fs0[30];
    fs[31] = fs0[31];
    fs[32] = fs0[32];
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdfsmult(void)
{

/*
Compute Fs (multiplier-generated forces only)
*/
    sddovpk();
    fs[0] = mtau[0];
    fs[1] = mtau[1];
    fs[2] = mtau[2];
    fs[3] = mtau[3];
    fs[4] = mtau[4];
    fs[5] = mtau[5];
    fs[6] = mtau[6];
    fs[7] = mtau[7];
    fs[8] = mtau[8];
    fs[9] = mtau[9];
    fs[10] = mtau[10];
    fs[11] = mtau[11];
    fs[12] = mtau[12];
    fs[13] = mtau[13];
    fs[14] = mtau[14];
    fs[15] = mtau[15];
    fs[16] = mtau[16];
    fs[17] = mtau[17];
    fs[18] = mtau[18];
    fs[19] = mtau[19];
    fs[20] = mtau[20];
    fs[21] = mtau[21];
    fs[22] = mtau[22];
    fs[23] = mtau[23];
    fs[24] = mtau[24];
    fs[25] = mtau[25];
    fs[26] = mtau[26];
    fs[27] = mtau[27];
    fs[28] = mtau[28];
    fs[29] = mtau[29];
    fs[30] = mtau[30];
    fs[31] = mtau[31];
    fs[32] = mtau[32];
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdfsfull(void)
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
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
    fs[21] = (fs[21]+fs0[21]);
    fs[22] = (fs[22]+fs0[22]);
    fs[23] = (fs[23]+fs0[23]);
    fs[24] = (fs[24]+fs0[24]);
    fs[25] = (fs[25]+fs0[25]);
    fs[26] = (fs[26]+fs0[26]);
    fs[27] = (fs[27]+fs0[27]);
    fs[28] = (fs[28]+fs0[28]);
    fs[29] = (fs[29]+fs0[29]);
    fs[30] = (fs[30]+fs0[30]);
    fs[31] = (fs[31]+fs0[31]);
    fs[32] = (fs[32]+fs0[32]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   33 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdfsgenmult(void)
{

/*
Compute Fs (generic multiplier-generated forces)
*/
    sddovpk();
    temp[0] = (((mfk[3][2]*Vpk[0][14][2])+((mfk[3][0]*Vpk[0][14][0])+(mfk[3][1]*
      Vpk[0][14][1])))+(((mfk[2][2]*Vpk[0][11][2])+((mfk[2][0]*Vpk[0][11][0])+(
      mfk[2][1]*Vpk[0][11][1])))+(((mfk[0][2]*Vpk[0][3][2])+((mfk[0][0]*
      Vpk[0][3][0])+(mfk[0][1]*Vpk[0][3][1])))+((mfk[1][2]*Vpk[0][8][2])+((
      mfk[1][0]*Vpk[0][8][0])+(mfk[1][1]*Vpk[0][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[0][26][2])+((mfk[7][0]*Vpk[0][26][0])+(mfk[7][1]*
      Vpk[0][26][1])))+(((mfk[6][2]*Vpk[0][23][2])+((mfk[6][0]*Vpk[0][23][0])+(
      mfk[6][1]*Vpk[0][23][1])))+(((mfk[5][2]*Vpk[0][20][2])+((mfk[5][0]*
      Vpk[0][20][0])+(mfk[5][1]*Vpk[0][20][1])))+(((mfk[4][2]*Vpk[0][17][2])+((
      mfk[4][0]*Vpk[0][17][0])+(mfk[4][1]*Vpk[0][17][1])))+temp[0]))));
    fs[0] = (mtau[0]+(((mfk[9][2]*Vpk[0][32][2])+((mfk[9][0]*Vpk[0][32][0])+(
      mfk[9][1]*Vpk[0][32][1])))+(((mfk[8][2]*Vpk[0][29][2])+((mfk[8][0]*
      Vpk[0][29][0])+(mfk[8][1]*Vpk[0][29][1])))+temp[1])));
    temp[0] = (((mfk[3][2]*Vpk[1][14][2])+((mfk[3][0]*Vpk[1][14][0])+(mfk[3][1]*
      Vpk[1][14][1])))+(((mfk[2][2]*Vpk[1][11][2])+((mfk[2][0]*Vpk[1][11][0])+(
      mfk[2][1]*Vpk[1][11][1])))+(((mfk[0][2]*Vpk[1][3][2])+((mfk[0][0]*
      Vpk[1][3][0])+(mfk[0][1]*Vpk[1][3][1])))+((mfk[1][2]*Vpk[1][8][2])+((
      mfk[1][0]*Vpk[1][8][0])+(mfk[1][1]*Vpk[1][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[1][26][2])+((mfk[7][0]*Vpk[1][26][0])+(mfk[7][1]*
      Vpk[1][26][1])))+(((mfk[6][2]*Vpk[1][23][2])+((mfk[6][0]*Vpk[1][23][0])+(
      mfk[6][1]*Vpk[1][23][1])))+(((mfk[5][2]*Vpk[1][20][2])+((mfk[5][0]*
      Vpk[1][20][0])+(mfk[5][1]*Vpk[1][20][1])))+(((mfk[4][2]*Vpk[1][17][2])+((
      mfk[4][0]*Vpk[1][17][0])+(mfk[4][1]*Vpk[1][17][1])))+temp[0]))));
    fs[1] = (mtau[1]+(((mfk[9][2]*Vpk[1][32][2])+((mfk[9][0]*Vpk[1][32][0])+(
      mfk[9][1]*Vpk[1][32][1])))+(((mfk[8][2]*Vpk[1][29][2])+((mfk[8][0]*
      Vpk[1][29][0])+(mfk[8][1]*Vpk[1][29][1])))+temp[1])));
    temp[0] = (((mfk[3][2]*Vpk[2][14][2])+((mfk[3][0]*Vpk[2][14][0])+(mfk[3][1]*
      Vpk[2][14][1])))+(((mfk[2][2]*Vpk[2][11][2])+((mfk[2][0]*Vpk[2][11][0])+(
      mfk[2][1]*Vpk[2][11][1])))+(((mfk[0][2]*Vpk[2][3][2])+((mfk[0][0]*
      Vpk[2][3][0])+(mfk[0][1]*Vpk[2][3][1])))+((mfk[1][2]*Vpk[2][8][2])+((
      mfk[1][0]*Vpk[2][8][0])+(mfk[1][1]*Vpk[2][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[2][26][2])+((mfk[7][0]*Vpk[2][26][0])+(mfk[7][1]*
      Vpk[2][26][1])))+(((mfk[6][2]*Vpk[2][23][2])+((mfk[6][0]*Vpk[2][23][0])+(
      mfk[6][1]*Vpk[2][23][1])))+(((mfk[5][2]*Vpk[2][20][2])+((mfk[5][0]*
      Vpk[2][20][0])+(mfk[5][1]*Vpk[2][20][1])))+(((mfk[4][2]*Vpk[2][17][2])+((
      mfk[4][0]*Vpk[2][17][0])+(mfk[4][1]*Vpk[2][17][1])))+temp[0]))));
    fs[2] = (mtau[2]+(((mfk[9][2]*Vpk[2][32][2])+((mfk[9][0]*Vpk[2][32][0])+(
      mfk[9][1]*Vpk[2][32][1])))+(((mfk[8][2]*Vpk[2][29][2])+((mfk[8][0]*
      Vpk[2][29][0])+(mfk[8][1]*Vpk[2][29][1])))+temp[1])));
    temp[0] = ((mtk[0][0]+(((mfk[1][2]*Vpk[3][8][2])+((mfk[1][0]*Vpk[3][8][0])+(
      mfk[1][1]*Vpk[3][8][1])))+((mtk[1][2]*Wpk[3][8][2])+((mtk[1][0]*
      Wpk[3][8][0])+(mtk[1][1]*Wpk[3][8][1])))))+(((mfk[2][2]*Vpk[3][11][2])+((
      mfk[2][0]*Vpk[3][11][0])+(mfk[2][1]*Vpk[3][11][1])))+((mtk[2][2]*
      Wpk[3][11][2])+((mtk[2][0]*Wpk[3][11][0])+(mtk[2][1]*Wpk[3][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[3][17][2])+((mfk[4][0]*Vpk[3][17][0])+(mfk[4][1]
      *Vpk[3][17][1])))+((mtk[4][2]*Wpk[3][17][2])+((mtk[4][0]*Wpk[3][17][0])+(
      mtk[4][1]*Wpk[3][17][1]))))+(temp[0]+(((mfk[3][2]*Vpk[3][14][2])+((
      mfk[3][0]*Vpk[3][14][0])+(mfk[3][1]*Vpk[3][14][1])))+((mtk[3][2]*
      Wpk[3][14][2])+((mtk[3][0]*Wpk[3][14][0])+(mtk[3][1]*Wpk[3][14][1]))))));
    temp[2] = ((((mfk[6][2]*Vpk[3][23][2])+((mfk[6][0]*Vpk[3][23][0])+(mfk[6][1]
      *Vpk[3][23][1])))+((mtk[6][2]*Wpk[3][23][2])+((mtk[6][0]*Wpk[3][23][0])+(
      mtk[6][1]*Wpk[3][23][1]))))+((((mfk[5][2]*Vpk[3][20][2])+((mfk[5][0]*
      Vpk[3][20][0])+(mfk[5][1]*Vpk[3][20][1])))+((mtk[5][2]*Wpk[3][20][2])+((
      mtk[5][0]*Wpk[3][20][0])+(mtk[5][1]*Wpk[3][20][1]))))+temp[1]));
    temp[3] = ((((mfk[8][2]*Vpk[3][29][2])+((mfk[8][0]*Vpk[3][29][0])+(mfk[8][1]
      *Vpk[3][29][1])))+((mtk[8][2]*Wpk[3][29][2])+((mtk[8][0]*Wpk[3][29][0])+(
      mtk[8][1]*Wpk[3][29][1]))))+((((mfk[7][2]*Vpk[3][26][2])+((mfk[7][0]*
      Vpk[3][26][0])+(mfk[7][1]*Vpk[3][26][1])))+((mtk[7][2]*Wpk[3][26][2])+((
      mtk[7][0]*Wpk[3][26][0])+(mtk[7][1]*Wpk[3][26][1]))))+temp[2]));
    fs[3] = (mtau[3]+((((mfk[9][2]*Vpk[3][32][2])+((mfk[9][0]*Vpk[3][32][0])+(
      mfk[9][1]*Vpk[3][32][1])))+((mtk[9][2]*Wpk[3][32][2])+((mtk[9][0]*
      Wpk[3][32][0])+(mtk[9][1]*Wpk[3][32][1]))))+temp[3]));
    temp[0] = ((((.3202*((mfk[1][0]*Wpk[4][8][2])-(mfk[1][2]*Wpk[4][8][0])))-((
      mtk[1][2]*Wpk[4][8][2])+((mtk[1][0]*Wpk[4][8][0])+(mtk[1][1]*Wpk[4][8][1])
      )))-mtk[0][1])-(((mfk[2][2]*Vpk[4][11][2])+((mfk[2][0]*Vpk[4][11][0])+(
      mfk[2][1]*Vpk[4][11][1])))+((mtk[2][2]*Wpk[4][11][2])+((mtk[2][0]*
      Wpk[4][11][0])+(mtk[2][1]*Wpk[4][11][1])))));
    temp[1] = ((temp[0]-(((mfk[3][2]*Vpk[4][14][2])+((mfk[3][0]*Vpk[4][14][0])+(
      mfk[3][1]*Vpk[4][14][1])))+((mtk[3][2]*Wpk[4][14][2])+((mtk[3][0]*
      Wpk[4][14][0])+(mtk[3][1]*Wpk[4][14][1])))))-(((mfk[4][2]*Vpk[4][17][2])+(
      (mfk[4][0]*Vpk[4][17][0])+(mfk[4][1]*Vpk[4][17][1])))+((mtk[4][2]*
      Wpk[4][17][2])+((mtk[4][0]*Wpk[4][17][0])+(mtk[4][1]*Wpk[4][17][1])))));
    temp[2] = ((temp[1]-(((mfk[5][2]*Vpk[4][20][2])+((mfk[5][0]*Vpk[4][20][0])+(
      mfk[5][1]*Vpk[4][20][1])))+((mtk[5][2]*Wpk[4][20][2])+((mtk[5][0]*
      Wpk[4][20][0])+(mtk[5][1]*Wpk[4][20][1])))))-(((mfk[6][2]*Vpk[4][23][2])+(
      (mfk[6][0]*Vpk[4][23][0])+(mfk[6][1]*Vpk[4][23][1])))+((mtk[6][2]*
      Wpk[4][23][2])+((mtk[6][0]*Wpk[4][23][0])+(mtk[6][1]*Wpk[4][23][1])))));
    temp[3] = ((temp[2]-(((mfk[7][2]*Vpk[4][26][2])+((mfk[7][0]*Vpk[4][26][0])+(
      mfk[7][1]*Vpk[4][26][1])))+((mtk[7][2]*Wpk[4][26][2])+((mtk[7][0]*
      Wpk[4][26][0])+(mtk[7][1]*Wpk[4][26][1])))))-(((mfk[8][2]*Vpk[4][29][2])+(
      (mfk[8][0]*Vpk[4][29][0])+(mfk[8][1]*Vpk[4][29][1])))+((mtk[8][2]*
      Wpk[4][29][2])+((mtk[8][0]*Wpk[4][29][0])+(mtk[8][1]*Wpk[4][29][1])))));
    fs[4] = (mtau[4]-(temp[3]-(((mfk[9][2]*Vpk[4][32][2])+((mfk[9][0]*
      Vpk[4][32][0])+(mfk[9][1]*Vpk[4][32][1])))+((mtk[9][2]*Wpk[4][32][2])+((
      mtk[9][0]*Wpk[4][32][0])+(mtk[9][1]*Wpk[4][32][1]))))));
    temp[0] = ((mtk[0][2]+(((mfk[1][2]*Vpk[5][8][2])+((mfk[1][0]*Vpk[5][8][0])+(
      mfk[1][1]*Vpk[5][8][1])))+((mtk[1][2]*Wpk[5][8][2])+((mtk[1][0]*
      Wpk[5][8][0])+(mtk[1][1]*Wpk[5][8][1])))))+(((mfk[2][2]*Vpk[5][11][2])+((
      mfk[2][0]*Vpk[5][11][0])+(mfk[2][1]*Vpk[5][11][1])))+((mtk[2][2]*
      Wpk[5][11][2])+((mtk[2][0]*Wpk[5][11][0])+(mtk[2][1]*Wpk[5][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[5][17][2])+((mfk[4][0]*Vpk[5][17][0])+(mfk[4][1]
      *Vpk[5][17][1])))+((mtk[4][2]*Wpk[5][17][2])+((mtk[4][0]*Wpk[5][17][0])+(
      mtk[4][1]*Wpk[5][17][1]))))+(temp[0]+(((mfk[3][2]*Vpk[5][14][2])+((
      mfk[3][0]*Vpk[5][14][0])+(mfk[3][1]*Vpk[5][14][1])))+((mtk[3][2]*
      Wpk[5][14][2])+((mtk[3][0]*Wpk[5][14][0])+(mtk[3][1]*Wpk[5][14][1]))))));
    temp[2] = ((((mfk[6][2]*Vpk[5][23][2])+((mfk[6][0]*Vpk[5][23][0])+(mfk[6][1]
      *Vpk[5][23][1])))+((mtk[6][2]*Wpk[5][23][2])+((mtk[6][0]*Wpk[5][23][0])+(
      mtk[6][1]*Wpk[5][23][1]))))+((((mfk[5][2]*Vpk[5][20][2])+((mfk[5][0]*
      Vpk[5][20][0])+(mfk[5][1]*Vpk[5][20][1])))+((mtk[5][2]*Wpk[5][20][2])+((
      mtk[5][0]*Wpk[5][20][0])+(mtk[5][1]*Wpk[5][20][1]))))+temp[1]));
    temp[3] = ((((mfk[8][2]*Vpk[5][29][2])+((mfk[8][0]*Vpk[5][29][0])+(mfk[8][1]
      *Vpk[5][29][1])))+((mtk[8][2]*Wpk[5][29][2])+((mtk[8][0]*Wpk[5][29][0])+(
      mtk[8][1]*Wpk[5][29][1]))))+((((mfk[7][2]*Vpk[5][26][2])+((mfk[7][0]*
      Vpk[5][26][0])+(mfk[7][1]*Vpk[5][26][1])))+((mtk[7][2]*Wpk[5][26][2])+((
      mtk[7][0]*Wpk[5][26][0])+(mtk[7][1]*Wpk[5][26][1]))))+temp[2]));
    fs[5] = (mtau[5]+((((mfk[9][2]*Vpk[5][32][2])+((mfk[9][0]*Vpk[5][32][0])+(
      mfk[9][1]*Vpk[5][32][1])))+((mtk[9][2]*Wpk[5][32][2])+((mtk[9][0]*
      Wpk[5][32][0])+(mtk[9][1]*Wpk[5][32][1]))))+temp[3]));
    fs[6] = (mtau[6]-((.3202*((mfk[1][0]*Wpk[6][8][2])-(mfk[1][2]*Wpk[6][8][0]))
      )-((mtk[1][2]*Wpk[6][8][2])+((mtk[1][0]*Wpk[6][8][0])+(mtk[1][1]*
      Wpk[6][8][1])))));
    fs[7] = (mtau[7]-((.3202*((mfk[1][0]*Wpk[7][8][2])-(mfk[1][2]*Wpk[7][8][0]))
      )-((mtk[1][2]*Wpk[7][8][2])+((mtk[1][0]*Wpk[7][8][0])+(mtk[1][1]*
      Wpk[7][8][1])))));
    fs[8] = (mtau[8]-((.3202*((mfk[1][0]*pin[8][2])-(mfk[1][2]*pin[8][0])))-((
      mtk[1][2]*pin[8][2])+((mtk[1][0]*pin[8][0])+(mtk[1][1]*pin[8][1])))));
    temp[0] = (((((.002*(mfk[2][1]*Wpk[9][11][2]))-(.1715*(mfk[2][0]*
      Wpk[9][11][2])))-(mfk[2][2]*Vpk[9][11][2]))-((mtk[2][2]*Wpk[9][11][2])+((
      mtk[2][0]*Wpk[9][11][0])+(mtk[2][1]*Wpk[9][11][1]))))-(((mfk[3][2]*
      Vpk[9][14][2])+((mfk[3][0]*Vpk[9][14][0])+(mfk[3][1]*Vpk[9][14][1])))+((
      mtk[3][2]*Wpk[9][14][2])+((mtk[3][0]*Wpk[9][14][0])+(mtk[3][1]*
      Wpk[9][14][1])))));
    fs[9] = (mtau[9]-((temp[0]-(((mfk[4][2]*Vpk[9][17][2])+((mfk[4][0]*
      Vpk[9][17][0])+(mfk[4][1]*Vpk[9][17][1])))+((mtk[4][2]*Wpk[9][17][2])+((
      mtk[4][0]*Wpk[9][17][0])+(mtk[4][1]*Wpk[9][17][1])))))-(((mfk[5][2]*
      Vpk[9][20][2])+((mfk[5][0]*Vpk[9][20][0])+(mfk[5][1]*Vpk[9][20][1])))+((
      mtk[5][2]*Wpk[9][20][2])+((mtk[5][0]*Wpk[9][20][0])+(mtk[5][1]*
      Wpk[9][20][1]))))));
    temp[0] = (((((.002*(mfk[2][1]*Wpk[10][11][2]))-(.1715*(mfk[2][0]*
      Wpk[10][11][2])))-(mfk[2][2]*Vpk[10][11][2]))-((mtk[2][2]*Wpk[10][11][2])+
      ((mtk[2][0]*Wpk[10][11][0])+(mtk[2][1]*Wpk[10][11][1]))))-(((mfk[3][2]*
      Vpk[10][14][2])+((mfk[3][0]*Vpk[10][14][0])+(mfk[3][1]*Vpk[10][14][1])))+(
      (mtk[3][2]*Wpk[10][14][2])+((mtk[3][0]*Wpk[10][14][0])+(mtk[3][1]*
      Wpk[10][14][1])))));
    fs[10] = (mtau[10]-((temp[0]-(((mfk[4][2]*Vpk[10][17][2])+((mfk[4][0]*
      Vpk[10][17][0])+(mfk[4][1]*Vpk[10][17][1])))+((mtk[4][2]*Wpk[10][17][2])+(
      (mtk[4][0]*Wpk[10][17][0])+(mtk[4][1]*Wpk[10][17][1])))))-(((mfk[5][2]*
      Vpk[10][20][2])+((mfk[5][0]*Vpk[10][20][0])+(mfk[5][1]*Vpk[10][20][1])))+(
      (mtk[5][2]*Wpk[10][20][2])+((mtk[5][0]*Wpk[10][20][0])+(mtk[5][1]*
      Wpk[10][20][1]))))));
    temp[0] = (((((.002*(mfk[2][1]*pin[11][2]))-(.1715*(mfk[2][0]*pin[11][2])))-
      (mfk[2][2]*Vpk[11][11][2]))-((mtk[2][2]*pin[11][2])+((mtk[2][0]*pin[11][0]
      )+(mtk[2][1]*pin[11][1]))))-(((mfk[3][2]*Vpk[11][14][2])+((mfk[3][0]*
      Vpk[11][14][0])+(mfk[3][1]*Vpk[11][14][1])))+((mtk[3][2]*Wpk[11][14][2])+(
      (mtk[3][0]*Wpk[11][14][0])+(mtk[3][1]*Wpk[11][14][1])))));
    fs[11] = (mtau[11]-((temp[0]-(((mfk[4][2]*Vpk[11][17][2])+((mfk[4][0]*
      Vpk[11][17][0])+(mfk[4][1]*Vpk[11][17][1])))+((mtk[4][2]*Wpk[11][17][2])+(
      (mtk[4][0]*Wpk[11][17][0])+(mtk[4][1]*Wpk[11][17][1])))))-(((mfk[5][2]*
      Vpk[11][20][2])+((mfk[5][0]*Vpk[11][20][0])+(mfk[5][1]*Vpk[11][20][1])))+(
      (mtk[5][2]*Wpk[11][20][2])+((mtk[5][0]*Wpk[11][20][0])+(mtk[5][1]*
      Wpk[11][20][1]))))));
    temp[0] = (((.1862*((mfk[3][2]*Wpk[12][14][0])-(mfk[3][0]*Wpk[12][14][2])))-
      ((mtk[3][2]*Wpk[12][14][2])+((mtk[3][0]*Wpk[12][14][0])+(mtk[3][1]*
      Wpk[12][14][1]))))-(((mfk[4][2]*Vpk[12][17][2])+((mfk[4][0]*Vpk[12][17][0]
      )+(mfk[4][1]*Vpk[12][17][1])))+((mtk[4][2]*Wpk[12][17][2])+((mtk[4][0]*
      Wpk[12][17][0])+(mtk[4][1]*Wpk[12][17][1])))));
    fs[12] = (mtau[12]-(temp[0]-(((mfk[5][2]*Vpk[12][20][2])+((mfk[5][0]*
      Vpk[12][20][0])+(mfk[5][1]*Vpk[12][20][1])))+((mtk[5][2]*Wpk[12][20][2])+(
      (mtk[5][0]*Wpk[12][20][0])+(mtk[5][1]*Wpk[12][20][1]))))));
    temp[0] = (((.1862*((mfk[3][2]*Wpk[13][14][0])-(mfk[3][0]*Wpk[13][14][2])))-
      ((mtk[3][2]*Wpk[13][14][2])+((mtk[3][0]*Wpk[13][14][0])+(mtk[3][1]*
      Wpk[13][14][1]))))-(((mfk[4][2]*Vpk[13][17][2])+((mfk[4][0]*Vpk[13][17][0]
      )+(mfk[4][1]*Vpk[13][17][1])))+((mtk[4][2]*Wpk[13][17][2])+((mtk[4][0]*
      Wpk[13][17][0])+(mtk[4][1]*Wpk[13][17][1])))));
    fs[13] = (mtau[13]-(temp[0]-(((mfk[5][2]*Vpk[13][20][2])+((mfk[5][0]*
      Vpk[13][20][0])+(mfk[5][1]*Vpk[13][20][1])))+((mtk[5][2]*Wpk[13][20][2])+(
      (mtk[5][0]*Wpk[13][20][0])+(mtk[5][1]*Wpk[13][20][1]))))));
    temp[0] = (((.1862*((mfk[3][2]*pin[14][0])-(mfk[3][0]*pin[14][2])))-((
      mtk[3][2]*pin[14][2])+((mtk[3][0]*pin[14][0])+(mtk[3][1]*pin[14][1]))))-((
      (mfk[4][2]*Vpk[14][17][2])+((mfk[4][0]*Vpk[14][17][0])+(mfk[4][1]*
      Vpk[14][17][1])))+((mtk[4][2]*Wpk[14][17][2])+((mtk[4][0]*Wpk[14][17][0])+
      (mtk[4][1]*Wpk[14][17][1])))));
    fs[14] = (mtau[14]-(temp[0]-(((mfk[5][2]*Vpk[14][20][2])+((mfk[5][0]*
      Vpk[14][20][0])+(mfk[5][1]*Vpk[14][20][1])))+((mtk[5][2]*Wpk[14][20][2])+(
      (mtk[5][0]*Wpk[14][20][0])+(mtk[5][1]*Wpk[14][20][1]))))));
    fs[15] = (mtau[15]+((((mfk[4][2]*Vpk[15][17][2])+((mfk[4][0]*Vpk[15][17][0])
      +(mfk[4][1]*Vpk[15][17][1])))+((mtk[4][2]*Wpk[15][17][2])+((mtk[4][0]*
      Wpk[15][17][0])+(mtk[4][1]*Wpk[15][17][1]))))+(((mfk[5][2]*Vpk[15][20][2])
      +((mfk[5][0]*Vpk[15][20][0])+(mfk[5][1]*Vpk[15][20][1])))+((mtk[5][2]*
      Wpk[15][20][2])+((mtk[5][0]*Wpk[15][20][0])+(mtk[5][1]*Wpk[15][20][1])))))
      );
    fs[16] = (mtau[16]+((((mfk[4][2]*Vpk[16][17][2])+((mfk[4][0]*Vpk[16][17][0])
      +(mfk[4][1]*Vpk[16][17][1])))+((mtk[4][2]*Wpk[16][17][2])+((mtk[4][0]*
      Wpk[16][17][0])+(mtk[4][1]*Wpk[16][17][1]))))+(((mfk[5][2]*Vpk[16][20][2])
      +((mfk[5][0]*Vpk[16][20][0])+(mfk[5][1]*Vpk[16][20][1])))+((mtk[5][2]*
      Wpk[16][20][2])+((mtk[5][0]*Wpk[16][20][0])+(mtk[5][1]*Wpk[16][20][1])))))
      );
    fs[17] = (mtau[17]+((((mfk[4][2]*Vpk[17][17][2])+((mfk[4][0]*Vpk[17][17][0])
      +(mfk[4][1]*Vpk[17][17][1])))+((mtk[4][2]*pin[17][2])+((mtk[4][0]*
      pin[17][0])+(mtk[4][1]*pin[17][1]))))+(((mfk[5][2]*Vpk[17][20][2])+((
      mfk[5][0]*Vpk[17][20][0])+(mfk[5][1]*Vpk[17][20][1])))+((mtk[5][2]*
      Wpk[17][20][2])+((mtk[5][0]*Wpk[17][20][0])+(mtk[5][1]*Wpk[17][20][1])))))
      );
    fs[18] = (mtau[18]+(((mfk[5][2]*Vpk[18][20][2])+((mfk[5][0]*Vpk[18][20][0])+
      (mfk[5][1]*Vpk[18][20][1])))+((mtk[5][2]*Wpk[18][20][2])+((mtk[5][0]*
      Wpk[18][20][0])+(mtk[5][1]*Wpk[18][20][1])))));
    fs[19] = (mtau[19]+(((mfk[5][2]*Vpk[19][20][2])+((mfk[5][0]*Vpk[19][20][0])+
      (mfk[5][1]*Vpk[19][20][1])))+((mtk[5][2]*Wpk[19][20][2])+((mtk[5][0]*
      Wpk[19][20][0])+(mtk[5][1]*Wpk[19][20][1])))));
    fs[20] = (mtau[20]+(((mfk[5][2]*Vpk[20][20][2])+((mfk[5][0]*Vpk[20][20][0])+
      (mfk[5][1]*Vpk[20][20][1])))+((mtk[5][2]*pin[20][2])+((mtk[5][0]*
      pin[20][0])+(mtk[5][1]*pin[20][1])))));
    temp[0] = (((((.002*(mfk[6][1]*Wpk[21][23][2]))-(.1715*(mfk[6][0]*
      Wpk[21][23][2])))-(mfk[6][2]*Vpk[21][23][2]))-((mtk[6][2]*Wpk[21][23][2])+
      ((mtk[6][0]*Wpk[21][23][0])+(mtk[6][1]*Wpk[21][23][1]))))-(((mfk[7][2]*
      Vpk[21][26][2])+((mfk[7][0]*Vpk[21][26][0])+(mfk[7][1]*Vpk[21][26][1])))+(
      (mtk[7][2]*Wpk[21][26][2])+((mtk[7][0]*Wpk[21][26][0])+(mtk[7][1]*
      Wpk[21][26][1])))));
    fs[21] = (mtau[21]-((temp[0]-(((mfk[8][2]*Vpk[21][29][2])+((mfk[8][0]*
      Vpk[21][29][0])+(mfk[8][1]*Vpk[21][29][1])))+((mtk[8][2]*Wpk[21][29][2])+(
      (mtk[8][0]*Wpk[21][29][0])+(mtk[8][1]*Wpk[21][29][1])))))-(((mfk[9][2]*
      Vpk[21][32][2])+((mfk[9][0]*Vpk[21][32][0])+(mfk[9][1]*Vpk[21][32][1])))+(
      (mtk[9][2]*Wpk[21][32][2])+((mtk[9][0]*Wpk[21][32][0])+(mtk[9][1]*
      Wpk[21][32][1]))))));
    temp[0] = (((((.002*(mfk[6][1]*Wpk[22][23][2]))-(.1715*(mfk[6][0]*
      Wpk[22][23][2])))-(mfk[6][2]*Vpk[22][23][2]))-((mtk[6][2]*Wpk[22][23][2])+
      ((mtk[6][0]*Wpk[22][23][0])+(mtk[6][1]*Wpk[22][23][1]))))-(((mfk[7][2]*
      Vpk[22][26][2])+((mfk[7][0]*Vpk[22][26][0])+(mfk[7][1]*Vpk[22][26][1])))+(
      (mtk[7][2]*Wpk[22][26][2])+((mtk[7][0]*Wpk[22][26][0])+(mtk[7][1]*
      Wpk[22][26][1])))));
    fs[22] = (mtau[22]-((temp[0]-(((mfk[8][2]*Vpk[22][29][2])+((mfk[8][0]*
      Vpk[22][29][0])+(mfk[8][1]*Vpk[22][29][1])))+((mtk[8][2]*Wpk[22][29][2])+(
      (mtk[8][0]*Wpk[22][29][0])+(mtk[8][1]*Wpk[22][29][1])))))-(((mfk[9][2]*
      Vpk[22][32][2])+((mfk[9][0]*Vpk[22][32][0])+(mfk[9][1]*Vpk[22][32][1])))+(
      (mtk[9][2]*Wpk[22][32][2])+((mtk[9][0]*Wpk[22][32][0])+(mtk[9][1]*
      Wpk[22][32][1]))))));
    temp[0] = (((((.002*(mfk[6][1]*pin[23][2]))-(.1715*(mfk[6][0]*pin[23][2])))-
      (mfk[6][2]*Vpk[23][23][2]))-((mtk[6][2]*pin[23][2])+((mtk[6][0]*pin[23][0]
      )+(mtk[6][1]*pin[23][1]))))-(((mfk[7][2]*Vpk[23][26][2])+((mfk[7][0]*
      Vpk[23][26][0])+(mfk[7][1]*Vpk[23][26][1])))+((mtk[7][2]*Wpk[23][26][2])+(
      (mtk[7][0]*Wpk[23][26][0])+(mtk[7][1]*Wpk[23][26][1])))));
    fs[23] = (mtau[23]-((temp[0]-(((mfk[8][2]*Vpk[23][29][2])+((mfk[8][0]*
      Vpk[23][29][0])+(mfk[8][1]*Vpk[23][29][1])))+((mtk[8][2]*Wpk[23][29][2])+(
      (mtk[8][0]*Wpk[23][29][0])+(mtk[8][1]*Wpk[23][29][1])))))-(((mfk[9][2]*
      Vpk[23][32][2])+((mfk[9][0]*Vpk[23][32][0])+(mfk[9][1]*Vpk[23][32][1])))+(
      (mtk[9][2]*Wpk[23][32][2])+((mtk[9][0]*Wpk[23][32][0])+(mtk[9][1]*
      Wpk[23][32][1]))))));
    temp[0] = (((.1862*((mfk[7][2]*Wpk[24][26][0])-(mfk[7][0]*Wpk[24][26][2])))-
      ((mtk[7][2]*Wpk[24][26][2])+((mtk[7][0]*Wpk[24][26][0])+(mtk[7][1]*
      Wpk[24][26][1]))))-(((mfk[8][2]*Vpk[24][29][2])+((mfk[8][0]*Vpk[24][29][0]
      )+(mfk[8][1]*Vpk[24][29][1])))+((mtk[8][2]*Wpk[24][29][2])+((mtk[8][0]*
      Wpk[24][29][0])+(mtk[8][1]*Wpk[24][29][1])))));
    fs[24] = (mtau[24]-(temp[0]-(((mfk[9][2]*Vpk[24][32][2])+((mfk[9][0]*
      Vpk[24][32][0])+(mfk[9][1]*Vpk[24][32][1])))+((mtk[9][2]*Wpk[24][32][2])+(
      (mtk[9][0]*Wpk[24][32][0])+(mtk[9][1]*Wpk[24][32][1]))))));
    temp[0] = (((.1862*((mfk[7][2]*Wpk[25][26][0])-(mfk[7][0]*Wpk[25][26][2])))-
      ((mtk[7][2]*Wpk[25][26][2])+((mtk[7][0]*Wpk[25][26][0])+(mtk[7][1]*
      Wpk[25][26][1]))))-(((mfk[8][2]*Vpk[25][29][2])+((mfk[8][0]*Vpk[25][29][0]
      )+(mfk[8][1]*Vpk[25][29][1])))+((mtk[8][2]*Wpk[25][29][2])+((mtk[8][0]*
      Wpk[25][29][0])+(mtk[8][1]*Wpk[25][29][1])))));
    fs[25] = (mtau[25]-(temp[0]-(((mfk[9][2]*Vpk[25][32][2])+((mfk[9][0]*
      Vpk[25][32][0])+(mfk[9][1]*Vpk[25][32][1])))+((mtk[9][2]*Wpk[25][32][2])+(
      (mtk[9][0]*Wpk[25][32][0])+(mtk[9][1]*Wpk[25][32][1]))))));
    temp[0] = (((.1862*((mfk[7][2]*pin[26][0])-(mfk[7][0]*pin[26][2])))-((
      mtk[7][2]*pin[26][2])+((mtk[7][0]*pin[26][0])+(mtk[7][1]*pin[26][1]))))-((
      (mfk[8][2]*Vpk[26][29][2])+((mfk[8][0]*Vpk[26][29][0])+(mfk[8][1]*
      Vpk[26][29][1])))+((mtk[8][2]*Wpk[26][29][2])+((mtk[8][0]*Wpk[26][29][0])+
      (mtk[8][1]*Wpk[26][29][1])))));
    fs[26] = (mtau[26]-(temp[0]-(((mfk[9][2]*Vpk[26][32][2])+((mfk[9][0]*
      Vpk[26][32][0])+(mfk[9][1]*Vpk[26][32][1])))+((mtk[9][2]*Wpk[26][32][2])+(
      (mtk[9][0]*Wpk[26][32][0])+(mtk[9][1]*Wpk[26][32][1]))))));
    fs[27] = (mtau[27]+((((mfk[8][2]*Vpk[27][29][2])+((mfk[8][0]*Vpk[27][29][0])
      +(mfk[8][1]*Vpk[27][29][1])))+((mtk[8][2]*Wpk[27][29][2])+((mtk[8][0]*
      Wpk[27][29][0])+(mtk[8][1]*Wpk[27][29][1]))))+(((mfk[9][2]*Vpk[27][32][2])
      +((mfk[9][0]*Vpk[27][32][0])+(mfk[9][1]*Vpk[27][32][1])))+((mtk[9][2]*
      Wpk[27][32][2])+((mtk[9][0]*Wpk[27][32][0])+(mtk[9][1]*Wpk[27][32][1])))))
      );
    fs[28] = (mtau[28]+((((mfk[8][2]*Vpk[28][29][2])+((mfk[8][0]*Vpk[28][29][0])
      +(mfk[8][1]*Vpk[28][29][1])))+((mtk[8][2]*Wpk[28][29][2])+((mtk[8][0]*
      Wpk[28][29][0])+(mtk[8][1]*Wpk[28][29][1]))))+(((mfk[9][2]*Vpk[28][32][2])
      +((mfk[9][0]*Vpk[28][32][0])+(mfk[9][1]*Vpk[28][32][1])))+((mtk[9][2]*
      Wpk[28][32][2])+((mtk[9][0]*Wpk[28][32][0])+(mtk[9][1]*Wpk[28][32][1])))))
      );
    fs[29] = (mtau[29]+((((mfk[8][2]*Vpk[29][29][2])+((mfk[8][0]*Vpk[29][29][0])
      +(mfk[8][1]*Vpk[29][29][1])))+((mtk[8][2]*pin[29][2])+((mtk[8][0]*
      pin[29][0])+(mtk[8][1]*pin[29][1]))))+(((mfk[9][2]*Vpk[29][32][2])+((
      mfk[9][0]*Vpk[29][32][0])+(mfk[9][1]*Vpk[29][32][1])))+((mtk[9][2]*
      Wpk[29][32][2])+((mtk[9][0]*Wpk[29][32][0])+(mtk[9][1]*Wpk[29][32][1])))))
      );
    fs[30] = (mtau[30]+(((mfk[9][2]*Vpk[30][32][2])+((mfk[9][0]*Vpk[30][32][0])+
      (mfk[9][1]*Vpk[30][32][1])))+((mtk[9][2]*Wpk[30][32][2])+((mtk[9][0]*
      Wpk[30][32][0])+(mtk[9][1]*Wpk[30][32][1])))));
    fs[31] = (mtau[31]+(((mfk[9][2]*Vpk[31][32][2])+((mfk[9][0]*Vpk[31][32][0])+
      (mfk[9][1]*Vpk[31][32][1])))+((mtk[9][2]*Wpk[31][32][2])+((mtk[9][0]*
      Wpk[31][32][0])+(mtk[9][1]*Wpk[31][32][1])))));
    fs[32] = (mtau[32]+(((mfk[9][2]*Vpk[32][32][2])+((mfk[9][0]*Vpk[32][32][0])+
      (mfk[9][1]*Vpk[32][32][1])))+((mtk[9][2]*pin[32][2])+((mtk[9][0]*
      pin[32][0])+(mtk[9][1]*pin[32][1])))));
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  623 adds/subtracts/negates
                    642 multiplies
                      0 divides
                     63 assignments
*/
}

void sdfsgenfull(void)
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
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
    fs[21] = (fs[21]+fs0[21]);
    fs[22] = (fs[22]+fs0[22]);
    fs[23] = (fs[23]+fs0[23]);
    fs[24] = (fs[24]+fs0[24]);
    fs[25] = (fs[25]+fs0[25]);
    fs[26] = (fs[26]+fs0[26]);
    fs[27] = (fs[27]+fs0[27]);
    fs[28] = (fs[28]+fs0[28]);
    fs[29] = (fs[29]+fs0[29]);
    fs[30] = (fs[30]+fs0[30]);
    fs[31] = (fs[31]+fs0[31]);
    fs[32] = (fs[32]+fs0[32]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   33 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdfulltrq(double udotin[33],
    double multin[33],
    double trqout[33])
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[33][3],tstarr[33][3],Otkr[33][3],Atir[33][3],Atkr[33][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Compute multiplier-generated forces
*/
    sdmfrc(multin);
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[6][0] = (((Cik[6][2][0]*udotin[5])+((Cik[6][0][0]*udotin[3])+(
      Cik[6][1][0]*udotin[4])))+((pin[6][0]*udotin[6])+((Wik[6][2]*wk[6][1])-(
      Wik[6][1]*wk[6][2]))));
    Otkr[6][1] = (((Cik[6][2][1]*udotin[5])+((Cik[6][0][1]*udotin[3])+(
      Cik[6][1][1]*udotin[4])))+((pin[6][1]*udotin[6])+((Wik[6][0]*wk[6][2])-(
      Wik[6][2]*wk[6][0]))));
    Otkr[6][2] = (((Cik[6][2][2]*udotin[5])+((Cik[6][0][2]*udotin[3])+(
      Cik[6][1][2]*udotin[4])))+((pin[6][2]*udotin[6])+((Wik[6][1]*wk[6][0])-(
      Wik[6][0]*wk[6][1]))));
    Otkr[7][0] = (((Cik[7][2][0]*Otkr[6][2])+((Cik[7][0][0]*Otkr[6][0])+(
      Cik[7][1][0]*Otkr[6][1])))+((pin[7][0]*udotin[7])+((Wik[7][2]*wk[7][1])-(
      Wik[7][1]*wk[7][2]))));
    Otkr[7][1] = (((Cik[7][2][1]*Otkr[6][2])+((Cik[7][0][1]*Otkr[6][0])+(
      Cik[7][1][1]*Otkr[6][1])))+((pin[7][1]*udotin[7])+((Wik[7][0]*wk[7][2])-(
      Wik[7][2]*wk[7][0]))));
    Otkr[7][2] = (((Cik[7][2][2]*Otkr[6][2])+((Cik[7][0][2]*Otkr[6][0])+(
      Cik[7][1][2]*Otkr[6][1])))+((pin[7][2]*udotin[7])+((Wik[7][1]*wk[7][0])-(
      Wik[7][0]*wk[7][1]))));
    Otkr[8][0] = (((Cik[8][2][0]*Otkr[7][2])+((Cik[8][0][0]*Otkr[7][0])+(
      Cik[8][1][0]*Otkr[7][1])))+((pin[8][0]*udotin[8])+((Wik[8][2]*wk[8][1])-(
      Wik[8][1]*wk[8][2]))));
    Otkr[8][1] = (((Cik[8][2][1]*Otkr[7][2])+((Cik[8][0][1]*Otkr[7][0])+(
      Cik[8][1][1]*Otkr[7][1])))+((pin[8][1]*udotin[8])+((Wik[8][0]*wk[8][2])-(
      Wik[8][2]*wk[8][0]))));
    Otkr[8][2] = (((Cik[8][2][2]*Otkr[7][2])+((Cik[8][0][2]*Otkr[7][0])+(
      Cik[8][1][2]*Otkr[7][1])))+((pin[8][2]*udotin[8])+((Wik[8][1]*wk[8][0])-(
      Wik[8][0]*wk[8][1]))));
    Otkr[9][0] = (((Cik[9][2][0]*udotin[5])+((Cik[9][0][0]*udotin[3])+(
      Cik[9][1][0]*udotin[4])))+((pin[9][0]*udotin[9])+((Wik[9][2]*wk[9][1])-(
      Wik[9][1]*wk[9][2]))));
    Otkr[9][1] = (((Cik[9][2][1]*udotin[5])+((Cik[9][0][1]*udotin[3])+(
      Cik[9][1][1]*udotin[4])))+((pin[9][1]*udotin[9])+((Wik[9][0]*wk[9][2])-(
      Wik[9][2]*wk[9][0]))));
    Otkr[9][2] = (((Cik[9][2][2]*udotin[5])+((Cik[9][0][2]*udotin[3])+(
      Cik[9][1][2]*udotin[4])))+((pin[9][2]*udotin[9])+((Wik[9][1]*wk[9][0])-(
      Wik[9][0]*wk[9][1]))));
    Otkr[10][0] = (((Cik[10][2][0]*Otkr[9][2])+((Cik[10][0][0]*Otkr[9][0])+(
      Cik[10][1][0]*Otkr[9][1])))+((pin[10][0]*udotin[10])+((Wik[10][2]*
      wk[10][1])-(Wik[10][1]*wk[10][2]))));
    Otkr[10][1] = (((Cik[10][2][1]*Otkr[9][2])+((Cik[10][0][1]*Otkr[9][0])+(
      Cik[10][1][1]*Otkr[9][1])))+((pin[10][1]*udotin[10])+((Wik[10][0]*
      wk[10][2])-(Wik[10][2]*wk[10][0]))));
    Otkr[10][2] = (((Cik[10][2][2]*Otkr[9][2])+((Cik[10][0][2]*Otkr[9][0])+(
      Cik[10][1][2]*Otkr[9][1])))+((pin[10][2]*udotin[10])+((Wik[10][1]*
      wk[10][0])-(Wik[10][0]*wk[10][1]))));
    Otkr[11][0] = (((Cik[11][2][0]*Otkr[10][2])+((Cik[11][0][0]*Otkr[10][0])+(
      Cik[11][1][0]*Otkr[10][1])))+((pin[11][0]*udotin[11])+((Wik[11][2]*
      wk[11][1])-(Wik[11][1]*wk[11][2]))));
    Otkr[11][1] = (((Cik[11][2][1]*Otkr[10][2])+((Cik[11][0][1]*Otkr[10][0])+(
      Cik[11][1][1]*Otkr[10][1])))+((pin[11][1]*udotin[11])+((Wik[11][0]*
      wk[11][2])-(Wik[11][2]*wk[11][0]))));
    Otkr[11][2] = (((Cik[11][2][2]*Otkr[10][2])+((Cik[11][0][2]*Otkr[10][0])+(
      Cik[11][1][2]*Otkr[10][1])))+((pin[11][2]*udotin[11])+((Wik[11][1]*
      wk[11][0])-(Wik[11][0]*wk[11][1]))));
    Otkr[12][0] = (((Cik[12][2][0]*Otkr[11][2])+((Cik[12][0][0]*Otkr[11][0])+(
      Cik[12][1][0]*Otkr[11][1])))+((pin[12][0]*udotin[12])+((Wik[12][2]*
      wk[12][1])-(Wik[12][1]*wk[12][2]))));
    Otkr[12][1] = (((Cik[12][2][1]*Otkr[11][2])+((Cik[12][0][1]*Otkr[11][0])+(
      Cik[12][1][1]*Otkr[11][1])))+((pin[12][1]*udotin[12])+((Wik[12][0]*
      wk[12][2])-(Wik[12][2]*wk[12][0]))));
    Otkr[12][2] = (((Cik[12][2][2]*Otkr[11][2])+((Cik[12][0][2]*Otkr[11][0])+(
      Cik[12][1][2]*Otkr[11][1])))+((pin[12][2]*udotin[12])+((Wik[12][1]*
      wk[12][0])-(Wik[12][0]*wk[12][1]))));
    Otkr[13][0] = (((Cik[13][2][0]*Otkr[12][2])+((Cik[13][0][0]*Otkr[12][0])+(
      Cik[13][1][0]*Otkr[12][1])))+((pin[13][0]*udotin[13])+((Wik[13][2]*
      wk[13][1])-(Wik[13][1]*wk[13][2]))));
    Otkr[13][1] = (((Cik[13][2][1]*Otkr[12][2])+((Cik[13][0][1]*Otkr[12][0])+(
      Cik[13][1][1]*Otkr[12][1])))+((pin[13][1]*udotin[13])+((Wik[13][0]*
      wk[13][2])-(Wik[13][2]*wk[13][0]))));
    Otkr[13][2] = (((Cik[13][2][2]*Otkr[12][2])+((Cik[13][0][2]*Otkr[12][0])+(
      Cik[13][1][2]*Otkr[12][1])))+((pin[13][2]*udotin[13])+((Wik[13][1]*
      wk[13][0])-(Wik[13][0]*wk[13][1]))));
    Otkr[14][0] = (((Cik[14][2][0]*Otkr[13][2])+((Cik[14][0][0]*Otkr[13][0])+(
      Cik[14][1][0]*Otkr[13][1])))+((pin[14][0]*udotin[14])+((Wik[14][2]*
      wk[14][1])-(Wik[14][1]*wk[14][2]))));
    Otkr[14][1] = (((Cik[14][2][1]*Otkr[13][2])+((Cik[14][0][1]*Otkr[13][0])+(
      Cik[14][1][1]*Otkr[13][1])))+((pin[14][1]*udotin[14])+((Wik[14][0]*
      wk[14][2])-(Wik[14][2]*wk[14][0]))));
    Otkr[14][2] = (((Cik[14][2][2]*Otkr[13][2])+((Cik[14][0][2]*Otkr[13][0])+(
      Cik[14][1][2]*Otkr[13][1])))+((pin[14][2]*udotin[14])+((Wik[14][1]*
      wk[14][0])-(Wik[14][0]*wk[14][1]))));
    Otkr[15][0] = (((Cik[15][2][0]*Otkr[14][2])+((Cik[15][0][0]*Otkr[14][0])+(
      Cik[15][1][0]*Otkr[14][1])))+((pin[15][0]*udotin[15])+((Wik[15][2]*
      wk[15][1])-(Wik[15][1]*wk[15][2]))));
    Otkr[15][1] = (((Cik[15][2][1]*Otkr[14][2])+((Cik[15][0][1]*Otkr[14][0])+(
      Cik[15][1][1]*Otkr[14][1])))+((pin[15][1]*udotin[15])+((Wik[15][0]*
      wk[15][2])-(Wik[15][2]*wk[15][0]))));
    Otkr[15][2] = (((Cik[15][2][2]*Otkr[14][2])+((Cik[15][0][2]*Otkr[14][0])+(
      Cik[15][1][2]*Otkr[14][1])))+((pin[15][2]*udotin[15])+((Wik[15][1]*
      wk[15][0])-(Wik[15][0]*wk[15][1]))));
    Otkr[16][0] = (((Cik[16][2][0]*Otkr[15][2])+((Cik[16][0][0]*Otkr[15][0])+(
      Cik[16][1][0]*Otkr[15][1])))+((pin[16][0]*udotin[16])+((Wik[16][2]*
      wk[16][1])-(Wik[16][1]*wk[16][2]))));
    Otkr[16][1] = (((Cik[16][2][1]*Otkr[15][2])+((Cik[16][0][1]*Otkr[15][0])+(
      Cik[16][1][1]*Otkr[15][1])))+((pin[16][1]*udotin[16])+((Wik[16][0]*
      wk[16][2])-(Wik[16][2]*wk[16][0]))));
    Otkr[16][2] = (((Cik[16][2][2]*Otkr[15][2])+((Cik[16][0][2]*Otkr[15][0])+(
      Cik[16][1][2]*Otkr[15][1])))+((pin[16][2]*udotin[16])+((Wik[16][1]*
      wk[16][0])-(Wik[16][0]*wk[16][1]))));
    Otkr[17][0] = (((Cik[17][2][0]*Otkr[16][2])+((Cik[17][0][0]*Otkr[16][0])+(
      Cik[17][1][0]*Otkr[16][1])))+((pin[17][0]*udotin[17])+((Wik[17][2]*
      wk[17][1])-(Wik[17][1]*wk[17][2]))));
    Otkr[17][1] = (((Cik[17][2][1]*Otkr[16][2])+((Cik[17][0][1]*Otkr[16][0])+(
      Cik[17][1][1]*Otkr[16][1])))+((pin[17][1]*udotin[17])+((Wik[17][0]*
      wk[17][2])-(Wik[17][2]*wk[17][0]))));
    Otkr[17][2] = (((Cik[17][2][2]*Otkr[16][2])+((Cik[17][0][2]*Otkr[16][0])+(
      Cik[17][1][2]*Otkr[16][1])))+((pin[17][2]*udotin[17])+((Wik[17][1]*
      wk[17][0])-(Wik[17][0]*wk[17][1]))));
    Otkr[18][0] = (((Cik[18][2][0]*Otkr[17][2])+((Cik[18][0][0]*Otkr[17][0])+(
      Cik[18][1][0]*Otkr[17][1])))+((pin[18][0]*udotin[18])+((Wik[18][2]*
      wk[18][1])-(Wik[18][1]*wk[18][2]))));
    Otkr[18][1] = (((Cik[18][2][1]*Otkr[17][2])+((Cik[18][0][1]*Otkr[17][0])+(
      Cik[18][1][1]*Otkr[17][1])))+((pin[18][1]*udotin[18])+((Wik[18][0]*
      wk[18][2])-(Wik[18][2]*wk[18][0]))));
    Otkr[18][2] = (((Cik[18][2][2]*Otkr[17][2])+((Cik[18][0][2]*Otkr[17][0])+(
      Cik[18][1][2]*Otkr[17][1])))+((pin[18][2]*udotin[18])+((Wik[18][1]*
      wk[18][0])-(Wik[18][0]*wk[18][1]))));
    Otkr[19][0] = (((Cik[19][2][0]*Otkr[18][2])+((Cik[19][0][0]*Otkr[18][0])+(
      Cik[19][1][0]*Otkr[18][1])))+((pin[19][0]*udotin[19])+((Wik[19][2]*
      wk[19][1])-(Wik[19][1]*wk[19][2]))));
    Otkr[19][1] = (((Cik[19][2][1]*Otkr[18][2])+((Cik[19][0][1]*Otkr[18][0])+(
      Cik[19][1][1]*Otkr[18][1])))+((pin[19][1]*udotin[19])+((Wik[19][0]*
      wk[19][2])-(Wik[19][2]*wk[19][0]))));
    Otkr[19][2] = (((Cik[19][2][2]*Otkr[18][2])+((Cik[19][0][2]*Otkr[18][0])+(
      Cik[19][1][2]*Otkr[18][1])))+((pin[19][2]*udotin[19])+((Wik[19][1]*
      wk[19][0])-(Wik[19][0]*wk[19][1]))));
    Otkr[20][0] = (((Cik[20][2][0]*Otkr[19][2])+((Cik[20][0][0]*Otkr[19][0])+(
      Cik[20][1][0]*Otkr[19][1])))+((pin[20][0]*udotin[20])+((Wik[20][2]*
      wk[20][1])-(Wik[20][1]*wk[20][2]))));
    Otkr[20][1] = (((Cik[20][2][1]*Otkr[19][2])+((Cik[20][0][1]*Otkr[19][0])+(
      Cik[20][1][1]*Otkr[19][1])))+((pin[20][1]*udotin[20])+((Wik[20][0]*
      wk[20][2])-(Wik[20][2]*wk[20][0]))));
    Otkr[20][2] = (((Cik[20][2][2]*Otkr[19][2])+((Cik[20][0][2]*Otkr[19][0])+(
      Cik[20][1][2]*Otkr[19][1])))+((pin[20][2]*udotin[20])+((Wik[20][1]*
      wk[20][0])-(Wik[20][0]*wk[20][1]))));
    Otkr[21][0] = (((Cik[21][2][0]*udotin[5])+((Cik[21][0][0]*udotin[3])+(
      Cik[21][1][0]*udotin[4])))+((pin[21][0]*udotin[21])+((Wik[21][2]*wk[21][1]
      )-(Wik[21][1]*wk[21][2]))));
    Otkr[21][1] = (((Cik[21][2][1]*udotin[5])+((Cik[21][0][1]*udotin[3])+(
      Cik[21][1][1]*udotin[4])))+((pin[21][1]*udotin[21])+((Wik[21][0]*wk[21][2]
      )-(Wik[21][2]*wk[21][0]))));
    Otkr[21][2] = (((Cik[21][2][2]*udotin[5])+((Cik[21][0][2]*udotin[3])+(
      Cik[21][1][2]*udotin[4])))+((pin[21][2]*udotin[21])+((Wik[21][1]*wk[21][0]
      )-(Wik[21][0]*wk[21][1]))));
    Otkr[22][0] = (((Cik[22][2][0]*Otkr[21][2])+((Cik[22][0][0]*Otkr[21][0])+(
      Cik[22][1][0]*Otkr[21][1])))+((pin[22][0]*udotin[22])+((Wik[22][2]*
      wk[22][1])-(Wik[22][1]*wk[22][2]))));
    Otkr[22][1] = (((Cik[22][2][1]*Otkr[21][2])+((Cik[22][0][1]*Otkr[21][0])+(
      Cik[22][1][1]*Otkr[21][1])))+((pin[22][1]*udotin[22])+((Wik[22][0]*
      wk[22][2])-(Wik[22][2]*wk[22][0]))));
    Otkr[22][2] = (((Cik[22][2][2]*Otkr[21][2])+((Cik[22][0][2]*Otkr[21][0])+(
      Cik[22][1][2]*Otkr[21][1])))+((pin[22][2]*udotin[22])+((Wik[22][1]*
      wk[22][0])-(Wik[22][0]*wk[22][1]))));
    Otkr[23][0] = (((Cik[23][2][0]*Otkr[22][2])+((Cik[23][0][0]*Otkr[22][0])+(
      Cik[23][1][0]*Otkr[22][1])))+((pin[23][0]*udotin[23])+((Wik[23][2]*
      wk[23][1])-(Wik[23][1]*wk[23][2]))));
    Otkr[23][1] = (((Cik[23][2][1]*Otkr[22][2])+((Cik[23][0][1]*Otkr[22][0])+(
      Cik[23][1][1]*Otkr[22][1])))+((pin[23][1]*udotin[23])+((Wik[23][0]*
      wk[23][2])-(Wik[23][2]*wk[23][0]))));
    Otkr[23][2] = (((Cik[23][2][2]*Otkr[22][2])+((Cik[23][0][2]*Otkr[22][0])+(
      Cik[23][1][2]*Otkr[22][1])))+((pin[23][2]*udotin[23])+((Wik[23][1]*
      wk[23][0])-(Wik[23][0]*wk[23][1]))));
    Otkr[24][0] = (((Cik[24][2][0]*Otkr[23][2])+((Cik[24][0][0]*Otkr[23][0])+(
      Cik[24][1][0]*Otkr[23][1])))+((pin[24][0]*udotin[24])+((Wik[24][2]*
      wk[24][1])-(Wik[24][1]*wk[24][2]))));
    Otkr[24][1] = (((Cik[24][2][1]*Otkr[23][2])+((Cik[24][0][1]*Otkr[23][0])+(
      Cik[24][1][1]*Otkr[23][1])))+((pin[24][1]*udotin[24])+((Wik[24][0]*
      wk[24][2])-(Wik[24][2]*wk[24][0]))));
    Otkr[24][2] = (((Cik[24][2][2]*Otkr[23][2])+((Cik[24][0][2]*Otkr[23][0])+(
      Cik[24][1][2]*Otkr[23][1])))+((pin[24][2]*udotin[24])+((Wik[24][1]*
      wk[24][0])-(Wik[24][0]*wk[24][1]))));
    Otkr[25][0] = (((Cik[25][2][0]*Otkr[24][2])+((Cik[25][0][0]*Otkr[24][0])+(
      Cik[25][1][0]*Otkr[24][1])))+((pin[25][0]*udotin[25])+((Wik[25][2]*
      wk[25][1])-(Wik[25][1]*wk[25][2]))));
    Otkr[25][1] = (((Cik[25][2][1]*Otkr[24][2])+((Cik[25][0][1]*Otkr[24][0])+(
      Cik[25][1][1]*Otkr[24][1])))+((pin[25][1]*udotin[25])+((Wik[25][0]*
      wk[25][2])-(Wik[25][2]*wk[25][0]))));
    Otkr[25][2] = (((Cik[25][2][2]*Otkr[24][2])+((Cik[25][0][2]*Otkr[24][0])+(
      Cik[25][1][2]*Otkr[24][1])))+((pin[25][2]*udotin[25])+((Wik[25][1]*
      wk[25][0])-(Wik[25][0]*wk[25][1]))));
    Otkr[26][0] = (((Cik[26][2][0]*Otkr[25][2])+((Cik[26][0][0]*Otkr[25][0])+(
      Cik[26][1][0]*Otkr[25][1])))+((pin[26][0]*udotin[26])+((Wik[26][2]*
      wk[26][1])-(Wik[26][1]*wk[26][2]))));
    Otkr[26][1] = (((Cik[26][2][1]*Otkr[25][2])+((Cik[26][0][1]*Otkr[25][0])+(
      Cik[26][1][1]*Otkr[25][1])))+((pin[26][1]*udotin[26])+((Wik[26][0]*
      wk[26][2])-(Wik[26][2]*wk[26][0]))));
    Otkr[26][2] = (((Cik[26][2][2]*Otkr[25][2])+((Cik[26][0][2]*Otkr[25][0])+(
      Cik[26][1][2]*Otkr[25][1])))+((pin[26][2]*udotin[26])+((Wik[26][1]*
      wk[26][0])-(Wik[26][0]*wk[26][1]))));
    Otkr[27][0] = (((Cik[27][2][0]*Otkr[26][2])+((Cik[27][0][0]*Otkr[26][0])+(
      Cik[27][1][0]*Otkr[26][1])))+((pin[27][0]*udotin[27])+((Wik[27][2]*
      wk[27][1])-(Wik[27][1]*wk[27][2]))));
    Otkr[27][1] = (((Cik[27][2][1]*Otkr[26][2])+((Cik[27][0][1]*Otkr[26][0])+(
      Cik[27][1][1]*Otkr[26][1])))+((pin[27][1]*udotin[27])+((Wik[27][0]*
      wk[27][2])-(Wik[27][2]*wk[27][0]))));
    Otkr[27][2] = (((Cik[27][2][2]*Otkr[26][2])+((Cik[27][0][2]*Otkr[26][0])+(
      Cik[27][1][2]*Otkr[26][1])))+((pin[27][2]*udotin[27])+((Wik[27][1]*
      wk[27][0])-(Wik[27][0]*wk[27][1]))));
    Otkr[28][0] = (((Cik[28][2][0]*Otkr[27][2])+((Cik[28][0][0]*Otkr[27][0])+(
      Cik[28][1][0]*Otkr[27][1])))+((pin[28][0]*udotin[28])+((Wik[28][2]*
      wk[28][1])-(Wik[28][1]*wk[28][2]))));
    Otkr[28][1] = (((Cik[28][2][1]*Otkr[27][2])+((Cik[28][0][1]*Otkr[27][0])+(
      Cik[28][1][1]*Otkr[27][1])))+((pin[28][1]*udotin[28])+((Wik[28][0]*
      wk[28][2])-(Wik[28][2]*wk[28][0]))));
    Otkr[28][2] = (((Cik[28][2][2]*Otkr[27][2])+((Cik[28][0][2]*Otkr[27][0])+(
      Cik[28][1][2]*Otkr[27][1])))+((pin[28][2]*udotin[28])+((Wik[28][1]*
      wk[28][0])-(Wik[28][0]*wk[28][1]))));
    Otkr[29][0] = (((Cik[29][2][0]*Otkr[28][2])+((Cik[29][0][0]*Otkr[28][0])+(
      Cik[29][1][0]*Otkr[28][1])))+((pin[29][0]*udotin[29])+((Wik[29][2]*
      wk[29][1])-(Wik[29][1]*wk[29][2]))));
    Otkr[29][1] = (((Cik[29][2][1]*Otkr[28][2])+((Cik[29][0][1]*Otkr[28][0])+(
      Cik[29][1][1]*Otkr[28][1])))+((pin[29][1]*udotin[29])+((Wik[29][0]*
      wk[29][2])-(Wik[29][2]*wk[29][0]))));
    Otkr[29][2] = (((Cik[29][2][2]*Otkr[28][2])+((Cik[29][0][2]*Otkr[28][0])+(
      Cik[29][1][2]*Otkr[28][1])))+((pin[29][2]*udotin[29])+((Wik[29][1]*
      wk[29][0])-(Wik[29][0]*wk[29][1]))));
    Otkr[30][0] = (((Cik[30][2][0]*Otkr[29][2])+((Cik[30][0][0]*Otkr[29][0])+(
      Cik[30][1][0]*Otkr[29][1])))+((pin[30][0]*udotin[30])+((Wik[30][2]*
      wk[30][1])-(Wik[30][1]*wk[30][2]))));
    Otkr[30][1] = (((Cik[30][2][1]*Otkr[29][2])+((Cik[30][0][1]*Otkr[29][0])+(
      Cik[30][1][1]*Otkr[29][1])))+((pin[30][1]*udotin[30])+((Wik[30][0]*
      wk[30][2])-(Wik[30][2]*wk[30][0]))));
    Otkr[30][2] = (((Cik[30][2][2]*Otkr[29][2])+((Cik[30][0][2]*Otkr[29][0])+(
      Cik[30][1][2]*Otkr[29][1])))+((pin[30][2]*udotin[30])+((Wik[30][1]*
      wk[30][0])-(Wik[30][0]*wk[30][1]))));
    Otkr[31][0] = (((Cik[31][2][0]*Otkr[30][2])+((Cik[31][0][0]*Otkr[30][0])+(
      Cik[31][1][0]*Otkr[30][1])))+((pin[31][0]*udotin[31])+((Wik[31][2]*
      wk[31][1])-(Wik[31][1]*wk[31][2]))));
    Otkr[31][1] = (((Cik[31][2][1]*Otkr[30][2])+((Cik[31][0][1]*Otkr[30][0])+(
      Cik[31][1][1]*Otkr[30][1])))+((pin[31][1]*udotin[31])+((Wik[31][0]*
      wk[31][2])-(Wik[31][2]*wk[31][0]))));
    Otkr[31][2] = (((Cik[31][2][2]*Otkr[30][2])+((Cik[31][0][2]*Otkr[30][0])+(
      Cik[31][1][2]*Otkr[30][1])))+((pin[31][2]*udotin[31])+((Wik[31][1]*
      wk[31][0])-(Wik[31][0]*wk[31][1]))));
    Otkr[32][0] = (((Cik[32][2][0]*Otkr[31][2])+((Cik[32][0][0]*Otkr[31][0])+(
      Cik[32][1][0]*Otkr[31][1])))+((pin[32][0]*udotin[32])+((Wik[32][2]*
      wk[32][1])-(Wik[32][1]*wk[32][2]))));
    Otkr[32][1] = (((Cik[32][2][1]*Otkr[31][2])+((Cik[32][0][1]*Otkr[31][0])+(
      Cik[32][1][1]*Otkr[31][1])))+((pin[32][1]*udotin[32])+((Wik[32][0]*
      wk[32][2])-(Wik[32][2]*wk[32][0]))));
    Otkr[32][2] = (((Cik[32][2][2]*Otkr[31][2])+((Cik[32][0][2]*Otkr[31][0])+(
      Cik[32][1][2]*Otkr[31][1])))+((pin[32][2]*udotin[32])+((Wik[32][1]*
      wk[32][0])-(Wik[32][0]*wk[32][1]))));
    Atkr[0][0] = (pin[0][0]*udotin[0]);
    Atkr[0][1] = (pin[0][1]*udotin[0]);
    Atkr[0][2] = (pin[0][2]*udotin[0]);
    Atkr[1][0] = (Atkr[0][0]+(pin[1][0]*udotin[1]));
    Atkr[1][1] = (Atkr[0][1]+(pin[1][1]*udotin[1]));
    Atkr[1][2] = (Atkr[0][2]+(pin[1][2]*udotin[1]));
    Atkr[2][0] = (Atkr[1][0]+(pin[2][0]*udotin[2]));
    Atkr[2][1] = (Atkr[1][1]+(pin[2][1]*udotin[2]));
    Atkr[2][2] = (Atkr[1][2]+(pin[2][2]*udotin[2]));
    Atkr[3][0] = ((Atkr[2][2]*Cik[3][2][0])+((Atkr[2][0]*Cik[3][0][0])+(
      Atkr[2][1]*Cik[3][1][0])));
    Atkr[3][1] = ((Atkr[2][2]*Cik[3][2][1])+((Atkr[2][0]*Cik[3][0][1])+(
      Atkr[2][1]*Cik[3][1][1])));
    Atkr[3][2] = ((Atkr[2][2]*Cik[3][2][2])+((Atkr[2][0]*Cik[3][0][2])+(
      Atkr[2][1]*Cik[3][1][2])));
    Atir[6][0] = (Atkr[3][0]+(.127*((u[3]*u[4])-udotin[5])));
    Atir[6][1] = (Atkr[3][1]-(.127*((u[3]*u[3])+(u[5]*u[5]))));
    Atir[6][2] = (Atkr[3][2]+(.127*(udotin[3]+(u[4]*u[5]))));
    Atkr[6][0] = ((Atir[6][2]*Cik[6][2][0])+((Atir[6][0]*Cik[6][0][0])+(
      Atir[6][1]*Cik[6][1][0])));
    Atkr[6][1] = ((Atir[6][2]*Cik[6][2][1])+((Atir[6][0]*Cik[6][0][1])+(
      Atir[6][1]*Cik[6][1][1])));
    Atkr[6][2] = ((Atir[6][2]*Cik[6][2][2])+((Atir[6][0]*Cik[6][0][2])+(
      Atir[6][1]*Cik[6][1][2])));
    Atkr[7][0] = ((Atkr[6][2]*Cik[7][2][0])+((Atkr[6][0]*Cik[7][0][0])+(
      Atkr[6][1]*Cik[7][1][0])));
    Atkr[7][1] = ((Atkr[6][2]*Cik[7][2][1])+((Atkr[6][0]*Cik[7][0][1])+(
      Atkr[6][1]*Cik[7][1][1])));
    Atkr[7][2] = ((Atkr[6][2]*Cik[7][2][2])+((Atkr[6][0]*Cik[7][0][2])+(
      Atkr[6][1]*Cik[7][1][2])));
    Atkr[8][0] = ((.3202*((wk[8][0]*wk[8][1])-Otkr[8][2]))+((Atkr[7][2]*
      Cik[8][2][0])+((Atkr[7][0]*Cik[8][0][0])+(Atkr[7][1]*Cik[8][1][0]))));
    Atkr[8][1] = (((Atkr[7][2]*Cik[8][2][1])+((Atkr[7][0]*Cik[8][0][1])+(
      Atkr[7][1]*Cik[8][1][1])))-(.3202*((wk[8][0]*wk[8][0])+(wk[8][2]*wk[8][2])
      )));
    Atkr[8][2] = ((.3202*(Otkr[8][0]+(wk[8][1]*wk[8][2])))+((Atkr[7][2]*
      Cik[8][2][2])+((Atkr[7][0]*Cik[8][0][2])+(Atkr[7][1]*Cik[8][1][2]))));
    Atir[9][0] = (Atkr[3][0]+(((.07*udotin[5])+(.0935*udotin[4]))+((.0935*(u[3]*
      u[5]))-(.07*(u[3]*u[4])))));
    Atir[9][1] = (Atkr[3][1]+(((.07*(u[3]*u[3]))+(u[5]*Wirk[9][0]))-(.0935*
      udotin[3])));
    Atir[9][2] = (Atkr[3][2]-((.07*udotin[3])+((.0935*(u[3]*u[3]))+(u[4]*
      Wirk[9][0]))));
    Atkr[9][0] = ((Atir[9][2]*Cik[9][2][0])+((Atir[9][0]*Cik[9][0][0])+(
      Atir[9][1]*Cik[9][1][0])));
    Atkr[9][1] = ((Atir[9][2]*Cik[9][2][1])+((Atir[9][0]*Cik[9][0][1])+(
      Atir[9][1]*Cik[9][1][1])));
    Atkr[9][2] = ((Atir[9][2]*Cik[9][2][2])+((Atir[9][0]*Cik[9][0][2])+(
      Atir[9][1]*Cik[9][1][2])));
    Atkr[10][0] = ((Atkr[9][2]*Cik[10][2][0])+((Atkr[9][0]*Cik[10][0][0])+(
      Atkr[9][1]*Cik[10][1][0])));
    Atkr[10][1] = ((Atkr[9][2]*Cik[10][2][1])+((Atkr[9][0]*Cik[10][0][1])+(
      Atkr[9][1]*Cik[10][1][1])));
    Atkr[10][2] = ((Atkr[9][2]*Cik[10][2][2])+((Atkr[9][0]*Cik[10][0][2])+(
      Atkr[9][1]*Cik[10][1][2])));
    Atkr[11][0] = (((.1715*Otkr[11][2])+((.002*(wk[11][2]*wk[11][2]))+(wk[11][1]
      *Wkrpk[11][2])))+((Atkr[10][2]*Cik[11][2][0])+((Atkr[10][0]*Cik[11][0][0])
      +(Atkr[10][1]*Cik[11][1][0]))));
    Atkr[11][1] = (((Atkr[10][2]*Cik[11][2][1])+((Atkr[10][0]*Cik[11][0][1])+(
      Atkr[10][1]*Cik[11][1][1])))+(((.1715*(wk[11][2]*wk[11][2]))-(wk[11][0]*
      Wkrpk[11][2]))-(.002*Otkr[11][2])));
    Atkr[11][2] = (((Atkr[10][2]*Cik[11][2][2])+((Atkr[10][0]*Cik[11][0][2])+(
      Atkr[10][1]*Cik[11][1][2])))+(((.002*Otkr[11][1])-(.1715*Otkr[11][0]))-((
      .002*(wk[11][0]*wk[11][2]))+(.1715*(wk[11][1]*wk[11][2])))));
    Atir[12][0] = (Atkr[11][0]+((.2294*Otkr[11][2])+((Wirk[12][2]*wk[11][1])-(
      .0033*(wk[11][2]*wk[11][2])))));
    Atir[12][1] = (Atkr[11][1]+((.0033*Otkr[11][2])+((.2294*(wk[11][2]*wk[11][2]
      ))-(Wirk[12][2]*wk[11][0]))));
    Atir[12][2] = (Atkr[11][2]+(((.0033*(wk[11][0]*wk[11][2]))-(.2294*(wk[11][1]
      *wk[11][2])))-((.0033*Otkr[11][1])+(.2294*Otkr[11][0]))));
    Atkr[12][0] = ((Atir[12][2]*Cik[12][2][0])+((Atir[12][0]*Cik[12][0][0])+(
      Atir[12][1]*Cik[12][1][0])));
    Atkr[12][1] = ((Atir[12][2]*Cik[12][2][1])+((Atir[12][0]*Cik[12][0][1])+(
      Atir[12][1]*Cik[12][1][1])));
    Atkr[12][2] = ((Atir[12][2]*Cik[12][2][2])+((Atir[12][0]*Cik[12][0][2])+(
      Atir[12][1]*Cik[12][1][2])));
    Atkr[13][0] = ((Atkr[12][2]*Cik[13][2][0])+((Atkr[12][0]*Cik[13][0][0])+(
      Atkr[12][1]*Cik[13][1][0])));
    Atkr[13][1] = ((Atkr[12][2]*Cik[13][2][1])+((Atkr[12][0]*Cik[13][0][1])+(
      Atkr[12][1]*Cik[13][1][1])));
    Atkr[13][2] = ((Atkr[12][2]*Cik[13][2][2])+((Atkr[12][0]*Cik[13][0][2])+(
      Atkr[12][1]*Cik[13][1][2])));
    Atkr[14][0] = ((.1862*(Otkr[14][2]-(wk[14][0]*wk[14][1])))+((Atkr[13][2]*
      Cik[14][2][0])+((Atkr[13][0]*Cik[14][0][0])+(Atkr[13][1]*Cik[14][1][0]))))
      ;
    Atkr[14][1] = ((.1862*((wk[14][0]*wk[14][0])+(wk[14][2]*wk[14][2])))+((
      Atkr[13][2]*Cik[14][2][1])+((Atkr[13][0]*Cik[14][0][1])+(Atkr[13][1]*
      Cik[14][1][1]))));
    Atkr[14][2] = (((Atkr[13][2]*Cik[14][2][2])+((Atkr[13][0]*Cik[14][0][2])+(
      Atkr[13][1]*Cik[14][1][2])))-(.1862*(Otkr[14][0]+(wk[14][1]*wk[14][2]))));
    Atir[15][0] = (Atkr[14][0]+(.2438*(Otkr[14][2]-(wk[14][0]*wk[14][1]))));
    Atir[15][1] = (Atkr[14][1]+(.2438*((wk[14][0]*wk[14][0])+(wk[14][2]*
      wk[14][2]))));
    Atir[15][2] = (Atkr[14][2]-(.2438*(Otkr[14][0]+(wk[14][1]*wk[14][2]))));
    Atkr[15][0] = ((Atir[15][2]*Cik[15][2][0])+((Atir[15][0]*Cik[15][0][0])+(
      Atir[15][1]*Cik[15][1][0])));
    Atkr[15][1] = ((Atir[15][2]*Cik[15][2][1])+((Atir[15][0]*Cik[15][0][1])+(
      Atir[15][1]*Cik[15][1][1])));
    Atkr[15][2] = ((Atir[15][2]*Cik[15][2][2])+((Atir[15][0]*Cik[15][0][2])+(
      Atir[15][1]*Cik[15][1][2])));
    Atkr[16][0] = ((Atkr[15][2]*Cik[16][2][0])+((Atkr[15][0]*Cik[16][0][0])+(
      Atkr[15][1]*Cik[16][1][0])));
    Atkr[16][1] = ((Atkr[15][2]*Cik[16][2][1])+((Atkr[15][0]*Cik[16][0][1])+(
      Atkr[15][1]*Cik[16][1][1])));
    Atkr[16][2] = ((Atkr[15][2]*Cik[16][2][2])+((Atkr[15][0]*Cik[16][0][2])+(
      Atkr[15][1]*Cik[16][1][2])));
    Atkr[17][0] = (((Atkr[16][2]*Cik[17][2][0])+((Atkr[16][0]*Cik[17][0][0])+(
      Atkr[16][1]*Cik[17][1][0])))+(((.005539*Otkr[17][1])+(.051347*Otkr[17][2])
      )+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*Wkrpk[17][1]))));
    Atkr[17][1] = (((Atkr[16][2]*Cik[17][2][1])+((Atkr[16][0]*Cik[17][0][1])+(
      Atkr[16][1]*Cik[17][1][1])))+(((.035902*Otkr[17][2])-(.005539*Otkr[17][0])
      )+((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
    Atkr[17][2] = (((Atkr[16][2]*Cik[17][2][2])+((Atkr[16][0]*Cik[17][0][2])+(
      Atkr[16][1]*Cik[17][1][2])))+(((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*
      Wkrpk[17][0]))-((.035902*Otkr[17][1])+(.051347*Otkr[17][0]))));
    Atir[18][0] = (Atkr[17][0]+(((.018078*Otkr[17][1])+(.038*Otkr[17][2]))+((
      Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
    Atir[18][1] = (Atkr[17][1]+(((.098032*Otkr[17][2])-(.018078*Otkr[17][0]))+((
      Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
    Atir[18][2] = (Atkr[17][2]+(((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*wk[17][1])
      )-((.038*Otkr[17][0])+(.098032*Otkr[17][1]))));
    Atkr[18][0] = ((Atir[18][2]*Cik[18][2][0])+((Atir[18][0]*Cik[18][0][0])+(
      Atir[18][1]*Cik[18][1][0])));
    Atkr[18][1] = ((Atir[18][2]*Cik[18][2][1])+((Atir[18][0]*Cik[18][0][1])+(
      Atir[18][1]*Cik[18][1][1])));
    Atkr[18][2] = ((Atir[18][2]*Cik[18][2][2])+((Atir[18][0]*Cik[18][0][2])+(
      Atir[18][1]*Cik[18][1][2])));
    Atkr[19][0] = ((Atkr[18][2]*Cik[19][2][0])+((Atkr[18][0]*Cik[19][0][0])+(
      Atkr[18][1]*Cik[19][1][0])));
    Atkr[19][1] = ((Atkr[18][2]*Cik[19][2][1])+((Atkr[18][0]*Cik[19][0][1])+(
      Atkr[18][1]*Cik[19][1][1])));
    Atkr[19][2] = ((Atkr[18][2]*Cik[19][2][2])+((Atkr[18][0]*Cik[19][0][2])+(
      Atkr[18][1]*Cik[19][1][2])));
    Atkr[20][0] = (((Atkr[19][2]*Cik[20][2][0])+((Atkr[19][0]*Cik[20][0][0])+(
      Atkr[19][1]*Cik[20][1][0])))+(((.005139*Otkr[20][1])-(.0185*Otkr[20][2]))+
      ((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
    Atkr[20][1] = (((Atkr[19][2]*Cik[20][2][1])+((Atkr[19][0]*Cik[20][0][1])+(
      Atkr[19][1]*Cik[20][1][1])))+(((.026917*Otkr[20][2])-(.005139*Otkr[20][0])
      )+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*Wkrpk[20][2]))));
    Atkr[20][2] = (((Atkr[19][2]*Cik[20][2][2])+((Atkr[19][0]*Cik[20][0][2])+(
      Atkr[19][1]*Cik[20][1][2])))+(((.0185*Otkr[20][0])-(.026917*Otkr[20][1]))+
      ((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*Wkrpk[20][0]))));
    Atir[21][0] = (Atkr[3][0]+(((.07*udotin[5])-(.0935*udotin[4]))-((.07*(u[3]*
      u[4]))+(.0935*(u[3]*u[5])))));
    Atir[21][1] = (Atkr[3][1]+((.0935*udotin[3])+((.07*(u[3]*u[3]))+(u[5]*
      Wirk[21][0]))));
    Atir[21][2] = (Atkr[3][2]+(((.0935*(u[3]*u[3]))-(u[4]*Wirk[21][0]))-(.07*
      udotin[3])));
    Atkr[21][0] = ((Atir[21][2]*Cik[21][2][0])+((Atir[21][0]*Cik[21][0][0])+(
      Atir[21][1]*Cik[21][1][0])));
    Atkr[21][1] = ((Atir[21][2]*Cik[21][2][1])+((Atir[21][0]*Cik[21][0][1])+(
      Atir[21][1]*Cik[21][1][1])));
    Atkr[21][2] = ((Atir[21][2]*Cik[21][2][2])+((Atir[21][0]*Cik[21][0][2])+(
      Atir[21][1]*Cik[21][1][2])));
    Atkr[22][0] = ((Atkr[21][2]*Cik[22][2][0])+((Atkr[21][0]*Cik[22][0][0])+(
      Atkr[21][1]*Cik[22][1][0])));
    Atkr[22][1] = ((Atkr[21][2]*Cik[22][2][1])+((Atkr[21][0]*Cik[22][0][1])+(
      Atkr[21][1]*Cik[22][1][1])));
    Atkr[22][2] = ((Atkr[21][2]*Cik[22][2][2])+((Atkr[21][0]*Cik[22][0][2])+(
      Atkr[21][1]*Cik[22][1][2])));
    Atkr[23][0] = (((.1715*Otkr[23][2])+((.002*(wk[23][2]*wk[23][2]))+(wk[23][1]
      *Wkrpk[23][2])))+((Atkr[22][2]*Cik[23][2][0])+((Atkr[22][0]*Cik[23][0][0])
      +(Atkr[22][1]*Cik[23][1][0]))));
    Atkr[23][1] = (((Atkr[22][2]*Cik[23][2][1])+((Atkr[22][0]*Cik[23][0][1])+(
      Atkr[22][1]*Cik[23][1][1])))+(((.1715*(wk[23][2]*wk[23][2]))-(wk[23][0]*
      Wkrpk[23][2]))-(.002*Otkr[23][2])));
    Atkr[23][2] = (((Atkr[22][2]*Cik[23][2][2])+((Atkr[22][0]*Cik[23][0][2])+(
      Atkr[22][1]*Cik[23][1][2])))+(((.002*Otkr[23][1])-(.1715*Otkr[23][0]))-((
      .002*(wk[23][0]*wk[23][2]))+(.1715*(wk[23][1]*wk[23][2])))));
    Atir[24][0] = (Atkr[23][0]+((.2294*Otkr[23][2])+((Wirk[24][2]*wk[23][1])-(
      .0033*(wk[23][2]*wk[23][2])))));
    Atir[24][1] = (Atkr[23][1]+((.0033*Otkr[23][2])+((.2294*(wk[23][2]*wk[23][2]
      ))-(Wirk[24][2]*wk[23][0]))));
    Atir[24][2] = (Atkr[23][2]+(((.0033*(wk[23][0]*wk[23][2]))-(.2294*(wk[23][1]
      *wk[23][2])))-((.0033*Otkr[23][1])+(.2294*Otkr[23][0]))));
    Atkr[24][0] = ((Atir[24][2]*Cik[24][2][0])+((Atir[24][0]*Cik[24][0][0])+(
      Atir[24][1]*Cik[24][1][0])));
    Atkr[24][1] = ((Atir[24][2]*Cik[24][2][1])+((Atir[24][0]*Cik[24][0][1])+(
      Atir[24][1]*Cik[24][1][1])));
    Atkr[24][2] = ((Atir[24][2]*Cik[24][2][2])+((Atir[24][0]*Cik[24][0][2])+(
      Atir[24][1]*Cik[24][1][2])));
    Atkr[25][0] = ((Atkr[24][2]*Cik[25][2][0])+((Atkr[24][0]*Cik[25][0][0])+(
      Atkr[24][1]*Cik[25][1][0])));
    Atkr[25][1] = ((Atkr[24][2]*Cik[25][2][1])+((Atkr[24][0]*Cik[25][0][1])+(
      Atkr[24][1]*Cik[25][1][1])));
    Atkr[25][2] = ((Atkr[24][2]*Cik[25][2][2])+((Atkr[24][0]*Cik[25][0][2])+(
      Atkr[24][1]*Cik[25][1][2])));
    Atkr[26][0] = ((.1862*(Otkr[26][2]-(wk[26][0]*wk[26][1])))+((Atkr[25][2]*
      Cik[26][2][0])+((Atkr[25][0]*Cik[26][0][0])+(Atkr[25][1]*Cik[26][1][0]))))
      ;
    Atkr[26][1] = ((.1862*((wk[26][0]*wk[26][0])+(wk[26][2]*wk[26][2])))+((
      Atkr[25][2]*Cik[26][2][1])+((Atkr[25][0]*Cik[26][0][1])+(Atkr[25][1]*
      Cik[26][1][1]))));
    Atkr[26][2] = (((Atkr[25][2]*Cik[26][2][2])+((Atkr[25][0]*Cik[26][0][2])+(
      Atkr[25][1]*Cik[26][1][2])))-(.1862*(Otkr[26][0]+(wk[26][1]*wk[26][2]))));
    Atir[27][0] = (Atkr[26][0]+(.2438*(Otkr[26][2]-(wk[26][0]*wk[26][1]))));
    Atir[27][1] = (Atkr[26][1]+(.2438*((wk[26][0]*wk[26][0])+(wk[26][2]*
      wk[26][2]))));
    Atir[27][2] = (Atkr[26][2]-(.2438*(Otkr[26][0]+(wk[26][1]*wk[26][2]))));
    Atkr[27][0] = ((Atir[27][2]*Cik[27][2][0])+((Atir[27][0]*Cik[27][0][0])+(
      Atir[27][1]*Cik[27][1][0])));
    Atkr[27][1] = ((Atir[27][2]*Cik[27][2][1])+((Atir[27][0]*Cik[27][0][1])+(
      Atir[27][1]*Cik[27][1][1])));
    Atkr[27][2] = ((Atir[27][2]*Cik[27][2][2])+((Atir[27][0]*Cik[27][0][2])+(
      Atir[27][1]*Cik[27][1][2])));
    Atkr[28][0] = ((Atkr[27][2]*Cik[28][2][0])+((Atkr[27][0]*Cik[28][0][0])+(
      Atkr[27][1]*Cik[28][1][0])));
    Atkr[28][1] = ((Atkr[27][2]*Cik[28][2][1])+((Atkr[27][0]*Cik[28][0][1])+(
      Atkr[27][1]*Cik[28][1][1])));
    Atkr[28][2] = ((Atkr[27][2]*Cik[28][2][2])+((Atkr[27][0]*Cik[28][0][2])+(
      Atkr[27][1]*Cik[28][1][2])));
    Atkr[29][0] = (((Atkr[28][2]*Cik[29][2][0])+((Atkr[28][0]*Cik[29][0][0])+(
      Atkr[28][1]*Cik[29][1][0])))+(((.051347*Otkr[29][2])-(.005539*Otkr[29][1])
      )+((wk[29][1]*Wkrpk[29][2])-(wk[29][2]*Wkrpk[29][1]))));
    Atkr[29][1] = (((Atkr[28][2]*Cik[29][2][1])+((Atkr[28][0]*Cik[29][0][1])+(
      Atkr[28][1]*Cik[29][1][1])))+(((.005539*Otkr[29][0])+(.035902*Otkr[29][2])
      )+((wk[29][2]*Wkrpk[29][0])-(wk[29][0]*Wkrpk[29][2]))));
    Atkr[29][2] = (((Atkr[28][2]*Cik[29][2][2])+((Atkr[28][0]*Cik[29][0][2])+(
      Atkr[28][1]*Cik[29][1][2])))+(((wk[29][0]*Wkrpk[29][1])-(wk[29][1]*
      Wkrpk[29][0]))-((.035902*Otkr[29][1])+(.051347*Otkr[29][0]))));
    Atir[30][0] = (Atkr[29][0]+(((.038*Otkr[29][2])-(.018078*Otkr[29][1]))+((
      Wirk[30][2]*wk[29][1])-(Wirk[30][1]*wk[29][2]))));
    Atir[30][1] = (Atkr[29][1]+(((.018078*Otkr[29][0])+(.098032*Otkr[29][2]))+((
      Wirk[30][0]*wk[29][2])-(Wirk[30][2]*wk[29][0]))));
    Atir[30][2] = (Atkr[29][2]+(((Wirk[30][1]*wk[29][0])-(Wirk[30][0]*wk[29][1])
      )-((.038*Otkr[29][0])+(.098032*Otkr[29][1]))));
    Atkr[30][0] = ((Atir[30][2]*Cik[30][2][0])+((Atir[30][0]*Cik[30][0][0])+(
      Atir[30][1]*Cik[30][1][0])));
    Atkr[30][1] = ((Atir[30][2]*Cik[30][2][1])+((Atir[30][0]*Cik[30][0][1])+(
      Atir[30][1]*Cik[30][1][1])));
    Atkr[30][2] = ((Atir[30][2]*Cik[30][2][2])+((Atir[30][0]*Cik[30][0][2])+(
      Atir[30][1]*Cik[30][1][2])));
    Atkr[31][0] = ((Atkr[30][2]*Cik[31][2][0])+((Atkr[30][0]*Cik[31][0][0])+(
      Atkr[30][1]*Cik[31][1][0])));
    Atkr[31][1] = ((Atkr[30][2]*Cik[31][2][1])+((Atkr[30][0]*Cik[31][0][1])+(
      Atkr[30][1]*Cik[31][1][1])));
    Atkr[31][2] = ((Atkr[30][2]*Cik[31][2][2])+((Atkr[30][0]*Cik[31][0][2])+(
      Atkr[30][1]*Cik[31][1][2])));
    Atkr[32][0] = (((Atkr[31][2]*Cik[32][2][0])+((Atkr[31][0]*Cik[32][0][0])+(
      Atkr[31][1]*Cik[32][1][0])))+(((wk[32][1]*Wkrpk[32][2])-(wk[32][2]*
      Wkrpk[32][1]))-((.005139*Otkr[32][1])+(.0185*Otkr[32][2]))));
    Atkr[32][1] = (((Atkr[31][2]*Cik[32][2][1])+((Atkr[31][0]*Cik[32][0][1])+(
      Atkr[31][1]*Cik[32][1][1])))+(((.005139*Otkr[32][0])+(.026917*Otkr[32][2])
      )+((wk[32][2]*Wkrpk[32][0])-(wk[32][0]*Wkrpk[32][2]))));
    Atkr[32][2] = (((Atkr[31][2]*Cik[32][2][2])+((Atkr[31][0]*Cik[32][0][2])+(
      Atkr[31][1]*Cik[32][1][2])))+(((.0185*Otkr[32][0])-(.026917*Otkr[32][1]))+
      ((wk[32][0]*Wkrpk[32][1])-(wk[32][1]*Wkrpk[32][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = (ufk[0][0]+(11.15*(gk[3][0]-Atkr[3][0])));
    fstarr[5][1] = (ufk[0][1]+(11.15*(gk[3][1]-Atkr[3][1])));
    fstarr[5][2] = (ufk[0][2]+(11.15*(gk[3][2]-Atkr[3][2])));
    fstarr[8][0] = (ufk[1][0]+(32.413*(gk[8][0]-Atkr[8][0])));
    fstarr[8][1] = (ufk[1][1]+(32.413*(gk[8][1]-Atkr[8][1])));
    fstarr[8][2] = (ufk[1][2]+(32.413*(gk[8][2]-Atkr[8][2])));
    fstarr[11][0] = (ufk[2][0]+(8.806*(gk[11][0]-Atkr[11][0])));
    fstarr[11][1] = (ufk[2][1]+(8.806*(gk[11][1]-Atkr[11][1])));
    fstarr[11][2] = (ufk[2][2]+(8.806*(gk[11][2]-Atkr[11][2])));
    fstarr[14][0] = (ufk[3][0]+(3.51*(gk[14][0]-Atkr[14][0])));
    fstarr[14][1] = (ufk[3][1]+(3.51*(gk[14][1]-Atkr[14][1])));
    fstarr[14][2] = (ufk[3][2]+(3.51*(gk[14][2]-Atkr[14][2])));
    fstarr[17][0] = (ufk[4][0]+(1.2*(gk[17][0]-Atkr[17][0])));
    fstarr[17][1] = (ufk[4][1]+(1.2*(gk[17][1]-Atkr[17][1])));
    fstarr[17][2] = (ufk[4][2]+(1.2*(gk[17][2]-Atkr[17][2])));
    fstarr[20][0] = (ufk[5][0]+(.205126*(gk[20][0]-Atkr[20][0])));
    fstarr[20][1] = (ufk[5][1]+(.205126*(gk[20][1]-Atkr[20][1])));
    fstarr[20][2] = (ufk[5][2]+(.205126*(gk[20][2]-Atkr[20][2])));
    fstarr[23][0] = (ufk[6][0]+(8.806*(gk[23][0]-Atkr[23][0])));
    fstarr[23][1] = (ufk[6][1]+(8.806*(gk[23][1]-Atkr[23][1])));
    fstarr[23][2] = (ufk[6][2]+(8.806*(gk[23][2]-Atkr[23][2])));
    fstarr[26][0] = (ufk[7][0]+(3.51*(gk[26][0]-Atkr[26][0])));
    fstarr[26][1] = (ufk[7][1]+(3.51*(gk[26][1]-Atkr[26][1])));
    fstarr[26][2] = (ufk[7][2]+(3.51*(gk[26][2]-Atkr[26][2])));
    fstarr[29][0] = (ufk[8][0]+(1.2*(gk[29][0]-Atkr[29][0])));
    fstarr[29][1] = (ufk[8][1]+(1.2*(gk[29][1]-Atkr[29][1])));
    fstarr[29][2] = (ufk[8][2]+(1.2*(gk[29][2]-Atkr[29][2])));
    fstarr[32][0] = (ufk[9][0]+(.205126*(gk[32][0]-Atkr[32][0])));
    fstarr[32][1] = (ufk[9][1]+(.205126*(gk[32][1]-Atkr[32][1])));
    fstarr[32][2] = (ufk[9][2]+(.205126*(gk[32][2]-Atkr[32][2])));
    tstarr[5][0] = (utk[0][0]-(WkIkWk[5][0]+(.0973*udotin[3])));
    tstarr[5][1] = (utk[0][1]-(WkIkWk[5][1]+(.0825*udotin[4])));
    tstarr[5][2] = (utk[0][2]-(WkIkWk[5][2]+(.0548*udotin[5])));
    tstarr[8][0] = (utk[1][0]-(WkIkWk[8][0]+(1.396*Otkr[8][0])));
    tstarr[8][1] = (utk[1][1]-(WkIkWk[8][1]+(.7153*Otkr[8][1])));
    tstarr[8][2] = (utk[1][2]-(WkIkWk[8][2]+(1.3552*Otkr[8][2])));
    tstarr[11][0] = (utk[2][0]-(WkIkWk[11][0]+(.1268*Otkr[11][0])));
    tstarr[11][1] = (utk[2][1]-(WkIkWk[11][1]+(.0332*Otkr[11][1])));
    tstarr[11][2] = (utk[2][2]-(WkIkWk[11][2]+(.1337*Otkr[11][2])));
    tstarr[14][0] = (utk[3][0]-(WkIkWk[14][0]+(.0477*Otkr[14][0])));
    tstarr[14][1] = (utk[3][1]-(WkIkWk[14][1]+(.0048*Otkr[14][1])));
    tstarr[14][2] = (utk[3][2]-(WkIkWk[14][2]+(.0484*Otkr[14][2])));
    tstarr[17][0] = (utk[4][0]-(WkIkWk[17][0]+(.001361*Otkr[17][0])));
    tstarr[17][1] = (utk[4][1]-(WkIkWk[17][1]+(.003709*Otkr[17][1])));
    tstarr[17][2] = (utk[4][2]-(WkIkWk[17][2]+(.003916*Otkr[17][2])));
    tstarr[20][0] = (utk[5][0]-(WkIkWk[20][0]+(.000117*Otkr[20][0])));
    tstarr[20][1] = (utk[5][1]-(WkIkWk[20][1]+(.000179*Otkr[20][1])));
    tstarr[20][2] = (utk[5][2]-(WkIkWk[20][2]+(.000119*Otkr[20][2])));
    tstarr[23][0] = (utk[6][0]-(WkIkWk[23][0]+(.1268*Otkr[23][0])));
    tstarr[23][1] = (utk[6][1]-(WkIkWk[23][1]+(.0332*Otkr[23][1])));
    tstarr[23][2] = (utk[6][2]-(WkIkWk[23][2]+(.1337*Otkr[23][2])));
    tstarr[26][0] = (utk[7][0]-(WkIkWk[26][0]+(.0477*Otkr[26][0])));
    tstarr[26][1] = (utk[7][1]-(WkIkWk[26][1]+(.0048*Otkr[26][1])));
    tstarr[26][2] = (utk[7][2]-(WkIkWk[26][2]+(.0484*Otkr[26][2])));
    tstarr[29][0] = (utk[8][0]-(WkIkWk[29][0]+(.001361*Otkr[29][0])));
    tstarr[29][1] = (utk[8][1]-(WkIkWk[29][1]+(.003709*Otkr[29][1])));
    tstarr[29][2] = (utk[8][2]-(WkIkWk[29][2]+(.003916*Otkr[29][2])));
    tstarr[32][0] = (utk[9][0]-(WkIkWk[32][0]+(.000117*Otkr[32][0])));
    tstarr[32][1] = (utk[9][1]-(WkIkWk[32][1]+(.000179*Otkr[32][1])));
    tstarr[32][2] = (utk[9][2]-(WkIkWk[32][2]+(.000119*Otkr[32][2])));
/*
Now calculate the torques
*/
    sddovpk();
    temp[0] = (((fstarr[14][2]*Vpk[0][14][2])+((fstarr[14][0]*Vpk[0][14][0])+(
      fstarr[14][1]*Vpk[0][14][1])))+(((fstarr[11][2]*Vpk[0][11][2])+((
      fstarr[11][0]*Vpk[0][11][0])+(fstarr[11][1]*Vpk[0][11][1])))+(((
      fstarr[5][2]*Vpk[0][3][2])+((fstarr[5][0]*Vpk[0][3][0])+(fstarr[5][1]*
      Vpk[0][3][1])))+((fstarr[8][2]*Vpk[0][8][2])+((fstarr[8][0]*Vpk[0][8][0])+
      (fstarr[8][1]*Vpk[0][8][1]))))));
    temp[1] = (((fstarr[26][2]*Vpk[0][26][2])+((fstarr[26][0]*Vpk[0][26][0])+(
      fstarr[26][1]*Vpk[0][26][1])))+(((fstarr[23][2]*Vpk[0][23][2])+((
      fstarr[23][0]*Vpk[0][23][0])+(fstarr[23][1]*Vpk[0][23][1])))+(((
      fstarr[20][2]*Vpk[0][20][2])+((fstarr[20][0]*Vpk[0][20][0])+(fstarr[20][1]
      *Vpk[0][20][1])))+(((fstarr[17][2]*Vpk[0][17][2])+((fstarr[17][0]*
      Vpk[0][17][0])+(fstarr[17][1]*Vpk[0][17][1])))+temp[0]))));
    trqout[0] = -((mtau[0]+utau[0])+(((fstarr[32][2]*Vpk[0][32][2])+((
      fstarr[32][0]*Vpk[0][32][0])+(fstarr[32][1]*Vpk[0][32][1])))+(((
      fstarr[29][2]*Vpk[0][29][2])+((fstarr[29][0]*Vpk[0][29][0])+(fstarr[29][1]
      *Vpk[0][29][1])))+temp[1])));
    temp[0] = (((fstarr[14][2]*Vpk[1][14][2])+((fstarr[14][0]*Vpk[1][14][0])+(
      fstarr[14][1]*Vpk[1][14][1])))+(((fstarr[11][2]*Vpk[1][11][2])+((
      fstarr[11][0]*Vpk[1][11][0])+(fstarr[11][1]*Vpk[1][11][1])))+(((
      fstarr[5][2]*Vpk[1][3][2])+((fstarr[5][0]*Vpk[1][3][0])+(fstarr[5][1]*
      Vpk[1][3][1])))+((fstarr[8][2]*Vpk[1][8][2])+((fstarr[8][0]*Vpk[1][8][0])+
      (fstarr[8][1]*Vpk[1][8][1]))))));
    temp[1] = (((fstarr[26][2]*Vpk[1][26][2])+((fstarr[26][0]*Vpk[1][26][0])+(
      fstarr[26][1]*Vpk[1][26][1])))+(((fstarr[23][2]*Vpk[1][23][2])+((
      fstarr[23][0]*Vpk[1][23][0])+(fstarr[23][1]*Vpk[1][23][1])))+(((
      fstarr[20][2]*Vpk[1][20][2])+((fstarr[20][0]*Vpk[1][20][0])+(fstarr[20][1]
      *Vpk[1][20][1])))+(((fstarr[17][2]*Vpk[1][17][2])+((fstarr[17][0]*
      Vpk[1][17][0])+(fstarr[17][1]*Vpk[1][17][1])))+temp[0]))));
    trqout[1] = -((mtau[1]+utau[1])+(((fstarr[32][2]*Vpk[1][32][2])+((
      fstarr[32][0]*Vpk[1][32][0])+(fstarr[32][1]*Vpk[1][32][1])))+(((
      fstarr[29][2]*Vpk[1][29][2])+((fstarr[29][0]*Vpk[1][29][0])+(fstarr[29][1]
      *Vpk[1][29][1])))+temp[1])));
    temp[0] = (((fstarr[14][2]*Vpk[2][14][2])+((fstarr[14][0]*Vpk[2][14][0])+(
      fstarr[14][1]*Vpk[2][14][1])))+(((fstarr[11][2]*Vpk[2][11][2])+((
      fstarr[11][0]*Vpk[2][11][0])+(fstarr[11][1]*Vpk[2][11][1])))+(((
      fstarr[5][2]*Vpk[2][3][2])+((fstarr[5][0]*Vpk[2][3][0])+(fstarr[5][1]*
      Vpk[2][3][1])))+((fstarr[8][2]*Vpk[2][8][2])+((fstarr[8][0]*Vpk[2][8][0])+
      (fstarr[8][1]*Vpk[2][8][1]))))));
    temp[1] = (((fstarr[26][2]*Vpk[2][26][2])+((fstarr[26][0]*Vpk[2][26][0])+(
      fstarr[26][1]*Vpk[2][26][1])))+(((fstarr[23][2]*Vpk[2][23][2])+((
      fstarr[23][0]*Vpk[2][23][0])+(fstarr[23][1]*Vpk[2][23][1])))+(((
      fstarr[20][2]*Vpk[2][20][2])+((fstarr[20][0]*Vpk[2][20][0])+(fstarr[20][1]
      *Vpk[2][20][1])))+(((fstarr[17][2]*Vpk[2][17][2])+((fstarr[17][0]*
      Vpk[2][17][0])+(fstarr[17][1]*Vpk[2][17][1])))+temp[0]))));
    trqout[2] = -((mtau[2]+utau[2])+(((fstarr[32][2]*Vpk[2][32][2])+((
      fstarr[32][0]*Vpk[2][32][0])+(fstarr[32][1]*Vpk[2][32][1])))+(((
      fstarr[29][2]*Vpk[2][29][2])+((fstarr[29][0]*Vpk[2][29][0])+(fstarr[29][1]
      *Vpk[2][29][1])))+temp[1])));
    temp[0] = ((tstarr[5][0]+(((fstarr[8][2]*Vpk[3][8][2])+((fstarr[8][0]*
      Vpk[3][8][0])+(fstarr[8][1]*Vpk[3][8][1])))+((tstarr[8][2]*Wpk[3][8][2])+(
      (tstarr[8][0]*Wpk[3][8][0])+(tstarr[8][1]*Wpk[3][8][1])))))+(((
      fstarr[11][2]*Vpk[3][11][2])+((fstarr[11][0]*Vpk[3][11][0])+(fstarr[11][1]
      *Vpk[3][11][1])))+((tstarr[11][2]*Wpk[3][11][2])+((tstarr[11][0]*
      Wpk[3][11][0])+(tstarr[11][1]*Wpk[3][11][1])))));
    temp[1] = ((((fstarr[17][2]*Vpk[3][17][2])+((fstarr[17][0]*Vpk[3][17][0])+(
      fstarr[17][1]*Vpk[3][17][1])))+((tstarr[17][2]*Wpk[3][17][2])+((
      tstarr[17][0]*Wpk[3][17][0])+(tstarr[17][1]*Wpk[3][17][1]))))+(temp[0]+(((
      fstarr[14][2]*Vpk[3][14][2])+((fstarr[14][0]*Vpk[3][14][0])+(fstarr[14][1]
      *Vpk[3][14][1])))+((tstarr[14][2]*Wpk[3][14][2])+((tstarr[14][0]*
      Wpk[3][14][0])+(tstarr[14][1]*Wpk[3][14][1]))))));
    temp[2] = ((((fstarr[23][2]*Vpk[3][23][2])+((fstarr[23][0]*Vpk[3][23][0])+(
      fstarr[23][1]*Vpk[3][23][1])))+((tstarr[23][2]*Wpk[3][23][2])+((
      tstarr[23][0]*Wpk[3][23][0])+(tstarr[23][1]*Wpk[3][23][1]))))+((((
      fstarr[20][2]*Vpk[3][20][2])+((fstarr[20][0]*Vpk[3][20][0])+(fstarr[20][1]
      *Vpk[3][20][1])))+((tstarr[20][2]*Wpk[3][20][2])+((tstarr[20][0]*
      Wpk[3][20][0])+(tstarr[20][1]*Wpk[3][20][1]))))+temp[1]));
    temp[3] = ((((fstarr[29][2]*Vpk[3][29][2])+((fstarr[29][0]*Vpk[3][29][0])+(
      fstarr[29][1]*Vpk[3][29][1])))+((tstarr[29][2]*Wpk[3][29][2])+((
      tstarr[29][0]*Wpk[3][29][0])+(tstarr[29][1]*Wpk[3][29][1]))))+((((
      fstarr[26][2]*Vpk[3][26][2])+((fstarr[26][0]*Vpk[3][26][0])+(fstarr[26][1]
      *Vpk[3][26][1])))+((tstarr[26][2]*Wpk[3][26][2])+((tstarr[26][0]*
      Wpk[3][26][0])+(tstarr[26][1]*Wpk[3][26][1]))))+temp[2]));
    trqout[3] = -((mtau[3]+utau[3])+((((fstarr[32][2]*Vpk[3][32][2])+((
      fstarr[32][0]*Vpk[3][32][0])+(fstarr[32][1]*Vpk[3][32][1])))+((
      tstarr[32][2]*Wpk[3][32][2])+((tstarr[32][0]*Wpk[3][32][0])+(tstarr[32][1]
      *Wpk[3][32][1]))))+temp[3]));
    temp[0] = ((tstarr[5][1]+((.3202*((fstarr[8][2]*Wpk[4][8][0])-(fstarr[8][0]*
      Wpk[4][8][2])))+((tstarr[8][2]*Wpk[4][8][2])+((tstarr[8][0]*Wpk[4][8][0])+
      (tstarr[8][1]*Wpk[4][8][1])))))+(((fstarr[11][2]*Vpk[4][11][2])+((
      fstarr[11][0]*Vpk[4][11][0])+(fstarr[11][1]*Vpk[4][11][1])))+((
      tstarr[11][2]*Wpk[4][11][2])+((tstarr[11][0]*Wpk[4][11][0])+(tstarr[11][1]
      *Wpk[4][11][1])))));
    temp[1] = ((((fstarr[17][2]*Vpk[4][17][2])+((fstarr[17][0]*Vpk[4][17][0])+(
      fstarr[17][1]*Vpk[4][17][1])))+((tstarr[17][2]*Wpk[4][17][2])+((
      tstarr[17][0]*Wpk[4][17][0])+(tstarr[17][1]*Wpk[4][17][1]))))+(temp[0]+(((
      fstarr[14][2]*Vpk[4][14][2])+((fstarr[14][0]*Vpk[4][14][0])+(fstarr[14][1]
      *Vpk[4][14][1])))+((tstarr[14][2]*Wpk[4][14][2])+((tstarr[14][0]*
      Wpk[4][14][0])+(tstarr[14][1]*Wpk[4][14][1]))))));
    temp[2] = ((((fstarr[23][2]*Vpk[4][23][2])+((fstarr[23][0]*Vpk[4][23][0])+(
      fstarr[23][1]*Vpk[4][23][1])))+((tstarr[23][2]*Wpk[4][23][2])+((
      tstarr[23][0]*Wpk[4][23][0])+(tstarr[23][1]*Wpk[4][23][1]))))+((((
      fstarr[20][2]*Vpk[4][20][2])+((fstarr[20][0]*Vpk[4][20][0])+(fstarr[20][1]
      *Vpk[4][20][1])))+((tstarr[20][2]*Wpk[4][20][2])+((tstarr[20][0]*
      Wpk[4][20][0])+(tstarr[20][1]*Wpk[4][20][1]))))+temp[1]));
    temp[3] = ((((fstarr[29][2]*Vpk[4][29][2])+((fstarr[29][0]*Vpk[4][29][0])+(
      fstarr[29][1]*Vpk[4][29][1])))+((tstarr[29][2]*Wpk[4][29][2])+((
      tstarr[29][0]*Wpk[4][29][0])+(tstarr[29][1]*Wpk[4][29][1]))))+((((
      fstarr[26][2]*Vpk[4][26][2])+((fstarr[26][0]*Vpk[4][26][0])+(fstarr[26][1]
      *Vpk[4][26][1])))+((tstarr[26][2]*Wpk[4][26][2])+((tstarr[26][0]*
      Wpk[4][26][0])+(tstarr[26][1]*Wpk[4][26][1]))))+temp[2]));
    trqout[4] = -((mtau[4]+utau[4])+((((fstarr[32][2]*Vpk[4][32][2])+((
      fstarr[32][0]*Vpk[4][32][0])+(fstarr[32][1]*Vpk[4][32][1])))+((
      tstarr[32][2]*Wpk[4][32][2])+((tstarr[32][0]*Wpk[4][32][0])+(tstarr[32][1]
      *Wpk[4][32][1]))))+temp[3]));
    temp[0] = ((tstarr[5][2]+(((fstarr[8][2]*Vpk[5][8][2])+((fstarr[8][0]*
      Vpk[5][8][0])+(fstarr[8][1]*Vpk[5][8][1])))+((tstarr[8][2]*Wpk[5][8][2])+(
      (tstarr[8][0]*Wpk[5][8][0])+(tstarr[8][1]*Wpk[5][8][1])))))+(((
      fstarr[11][2]*Vpk[5][11][2])+((fstarr[11][0]*Vpk[5][11][0])+(fstarr[11][1]
      *Vpk[5][11][1])))+((tstarr[11][2]*Wpk[5][11][2])+((tstarr[11][0]*
      Wpk[5][11][0])+(tstarr[11][1]*Wpk[5][11][1])))));
    temp[1] = ((((fstarr[17][2]*Vpk[5][17][2])+((fstarr[17][0]*Vpk[5][17][0])+(
      fstarr[17][1]*Vpk[5][17][1])))+((tstarr[17][2]*Wpk[5][17][2])+((
      tstarr[17][0]*Wpk[5][17][0])+(tstarr[17][1]*Wpk[5][17][1]))))+(temp[0]+(((
      fstarr[14][2]*Vpk[5][14][2])+((fstarr[14][0]*Vpk[5][14][0])+(fstarr[14][1]
      *Vpk[5][14][1])))+((tstarr[14][2]*Wpk[5][14][2])+((tstarr[14][0]*
      Wpk[5][14][0])+(tstarr[14][1]*Wpk[5][14][1]))))));
    temp[2] = ((((fstarr[23][2]*Vpk[5][23][2])+((fstarr[23][0]*Vpk[5][23][0])+(
      fstarr[23][1]*Vpk[5][23][1])))+((tstarr[23][2]*Wpk[5][23][2])+((
      tstarr[23][0]*Wpk[5][23][0])+(tstarr[23][1]*Wpk[5][23][1]))))+((((
      fstarr[20][2]*Vpk[5][20][2])+((fstarr[20][0]*Vpk[5][20][0])+(fstarr[20][1]
      *Vpk[5][20][1])))+((tstarr[20][2]*Wpk[5][20][2])+((tstarr[20][0]*
      Wpk[5][20][0])+(tstarr[20][1]*Wpk[5][20][1]))))+temp[1]));
    temp[3] = ((((fstarr[29][2]*Vpk[5][29][2])+((fstarr[29][0]*Vpk[5][29][0])+(
      fstarr[29][1]*Vpk[5][29][1])))+((tstarr[29][2]*Wpk[5][29][2])+((
      tstarr[29][0]*Wpk[5][29][0])+(tstarr[29][1]*Wpk[5][29][1]))))+((((
      fstarr[26][2]*Vpk[5][26][2])+((fstarr[26][0]*Vpk[5][26][0])+(fstarr[26][1]
      *Vpk[5][26][1])))+((tstarr[26][2]*Wpk[5][26][2])+((tstarr[26][0]*
      Wpk[5][26][0])+(tstarr[26][1]*Wpk[5][26][1]))))+temp[2]));
    trqout[5] = -((mtau[5]+utau[5])+((((fstarr[32][2]*Vpk[5][32][2])+((
      fstarr[32][0]*Vpk[5][32][0])+(fstarr[32][1]*Vpk[5][32][1])))+((
      tstarr[32][2]*Wpk[5][32][2])+((tstarr[32][0]*Wpk[5][32][0])+(tstarr[32][1]
      *Wpk[5][32][1]))))+temp[3]));
    trqout[6] = -((mtau[6]+utau[6])+((.3202*((fstarr[8][2]*Wpk[6][8][0])-(
      fstarr[8][0]*Wpk[6][8][2])))+((tstarr[8][2]*Wpk[6][8][2])+((tstarr[8][0]*
      Wpk[6][8][0])+(tstarr[8][1]*Wpk[6][8][1])))));
    trqout[7] = -((mtau[7]+utau[7])+((.3202*((fstarr[8][2]*Wpk[7][8][0])-(
      fstarr[8][0]*Wpk[7][8][2])))+((tstarr[8][2]*Wpk[7][8][2])+((tstarr[8][0]*
      Wpk[7][8][0])+(tstarr[8][1]*Wpk[7][8][1])))));
    trqout[8] = -((mtau[8]+utau[8])+((.3202*((fstarr[8][2]*pin[8][0])-(
      fstarr[8][0]*pin[8][2])))+((pin[8][2]*tstarr[8][2])+((pin[8][0]*
      tstarr[8][0])+(pin[8][1]*tstarr[8][1])))));
    temp[0] = ((((fstarr[11][2]*Vpk[9][11][2])+((.1715*(fstarr[11][0]*
      Wpk[9][11][2]))-(.002*(fstarr[11][1]*Wpk[9][11][2]))))+((tstarr[11][2]*
      Wpk[9][11][2])+((tstarr[11][0]*Wpk[9][11][0])+(tstarr[11][1]*Wpk[9][11][1]
      ))))+(((fstarr[14][2]*Vpk[9][14][2])+((fstarr[14][0]*Vpk[9][14][0])+(
      fstarr[14][1]*Vpk[9][14][1])))+((tstarr[14][2]*Wpk[9][14][2])+((
      tstarr[14][0]*Wpk[9][14][0])+(tstarr[14][1]*Wpk[9][14][1])))));
    trqout[9] = -((mtau[9]+utau[9])+((((fstarr[20][2]*Vpk[9][20][2])+((
      fstarr[20][0]*Vpk[9][20][0])+(fstarr[20][1]*Vpk[9][20][1])))+((
      tstarr[20][2]*Wpk[9][20][2])+((tstarr[20][0]*Wpk[9][20][0])+(tstarr[20][1]
      *Wpk[9][20][1]))))+((((fstarr[17][2]*Vpk[9][17][2])+((fstarr[17][0]*
      Vpk[9][17][0])+(fstarr[17][1]*Vpk[9][17][1])))+((tstarr[17][2]*
      Wpk[9][17][2])+((tstarr[17][0]*Wpk[9][17][0])+(tstarr[17][1]*Wpk[9][17][1]
      ))))+temp[0])));
    temp[0] = ((((fstarr[11][2]*Vpk[10][11][2])+((.1715*(fstarr[11][0]*
      Wpk[10][11][2]))-(.002*(fstarr[11][1]*Wpk[10][11][2]))))+((tstarr[11][2]*
      Wpk[10][11][2])+((tstarr[11][0]*Wpk[10][11][0])+(tstarr[11][1]*
      Wpk[10][11][1]))))+(((fstarr[14][2]*Vpk[10][14][2])+((fstarr[14][0]*
      Vpk[10][14][0])+(fstarr[14][1]*Vpk[10][14][1])))+((tstarr[14][2]*
      Wpk[10][14][2])+((tstarr[14][0]*Wpk[10][14][0])+(tstarr[14][1]*
      Wpk[10][14][1])))));
    trqout[10] = -((mtau[10]+utau[10])+((((fstarr[20][2]*Vpk[10][20][2])+((
      fstarr[20][0]*Vpk[10][20][0])+(fstarr[20][1]*Vpk[10][20][1])))+((
      tstarr[20][2]*Wpk[10][20][2])+((tstarr[20][0]*Wpk[10][20][0])+(
      tstarr[20][1]*Wpk[10][20][1]))))+((((fstarr[17][2]*Vpk[10][17][2])+((
      fstarr[17][0]*Vpk[10][17][0])+(fstarr[17][1]*Vpk[10][17][1])))+((
      tstarr[17][2]*Wpk[10][17][2])+((tstarr[17][0]*Wpk[10][17][0])+(
      tstarr[17][1]*Wpk[10][17][1]))))+temp[0])));
    temp[0] = ((((fstarr[11][2]*Vpk[11][11][2])+((.1715*(fstarr[11][0]*
      pin[11][2]))-(.002*(fstarr[11][1]*pin[11][2]))))+((pin[11][2]*
      tstarr[11][2])+((pin[11][0]*tstarr[11][0])+(pin[11][1]*tstarr[11][1]))))+(
      ((fstarr[14][2]*Vpk[11][14][2])+((fstarr[14][0]*Vpk[11][14][0])+(
      fstarr[14][1]*Vpk[11][14][1])))+((tstarr[14][2]*Wpk[11][14][2])+((
      tstarr[14][0]*Wpk[11][14][0])+(tstarr[14][1]*Wpk[11][14][1])))));
    trqout[11] = -((mtau[11]+utau[11])+((((fstarr[20][2]*Vpk[11][20][2])+((
      fstarr[20][0]*Vpk[11][20][0])+(fstarr[20][1]*Vpk[11][20][1])))+((
      tstarr[20][2]*Wpk[11][20][2])+((tstarr[20][0]*Wpk[11][20][0])+(
      tstarr[20][1]*Wpk[11][20][1]))))+((((fstarr[17][2]*Vpk[11][17][2])+((
      fstarr[17][0]*Vpk[11][17][0])+(fstarr[17][1]*Vpk[11][17][1])))+((
      tstarr[17][2]*Wpk[11][17][2])+((tstarr[17][0]*Wpk[11][17][0])+(
      tstarr[17][1]*Wpk[11][17][1]))))+temp[0])));
    temp[0] = (((.1862*((fstarr[14][0]*Wpk[12][14][2])-(fstarr[14][2]*
      Wpk[12][14][0])))+((tstarr[14][2]*Wpk[12][14][2])+((tstarr[14][0]*
      Wpk[12][14][0])+(tstarr[14][1]*Wpk[12][14][1]))))+(((fstarr[17][2]*
      Vpk[12][17][2])+((fstarr[17][0]*Vpk[12][17][0])+(fstarr[17][1]*
      Vpk[12][17][1])))+((tstarr[17][2]*Wpk[12][17][2])+((tstarr[17][0]*
      Wpk[12][17][0])+(tstarr[17][1]*Wpk[12][17][1])))));
    trqout[12] = -((mtau[12]+utau[12])+(temp[0]+(((fstarr[20][2]*Vpk[12][20][2])
      +((fstarr[20][0]*Vpk[12][20][0])+(fstarr[20][1]*Vpk[12][20][1])))+((
      tstarr[20][2]*Wpk[12][20][2])+((tstarr[20][0]*Wpk[12][20][0])+(
      tstarr[20][1]*Wpk[12][20][1]))))));
    temp[0] = (((.1862*((fstarr[14][0]*Wpk[13][14][2])-(fstarr[14][2]*
      Wpk[13][14][0])))+((tstarr[14][2]*Wpk[13][14][2])+((tstarr[14][0]*
      Wpk[13][14][0])+(tstarr[14][1]*Wpk[13][14][1]))))+(((fstarr[17][2]*
      Vpk[13][17][2])+((fstarr[17][0]*Vpk[13][17][0])+(fstarr[17][1]*
      Vpk[13][17][1])))+((tstarr[17][2]*Wpk[13][17][2])+((tstarr[17][0]*
      Wpk[13][17][0])+(tstarr[17][1]*Wpk[13][17][1])))));
    trqout[13] = -((mtau[13]+utau[13])+(temp[0]+(((fstarr[20][2]*Vpk[13][20][2])
      +((fstarr[20][0]*Vpk[13][20][0])+(fstarr[20][1]*Vpk[13][20][1])))+((
      tstarr[20][2]*Wpk[13][20][2])+((tstarr[20][0]*Wpk[13][20][0])+(
      tstarr[20][1]*Wpk[13][20][1]))))));
    temp[0] = (((.1862*((fstarr[14][0]*pin[14][2])-(fstarr[14][2]*pin[14][0])))+
      ((pin[14][2]*tstarr[14][2])+((pin[14][0]*tstarr[14][0])+(pin[14][1]*
      tstarr[14][1]))))+(((fstarr[17][2]*Vpk[14][17][2])+((fstarr[17][0]*
      Vpk[14][17][0])+(fstarr[17][1]*Vpk[14][17][1])))+((tstarr[17][2]*
      Wpk[14][17][2])+((tstarr[17][0]*Wpk[14][17][0])+(tstarr[17][1]*
      Wpk[14][17][1])))));
    trqout[14] = -((mtau[14]+utau[14])+(temp[0]+(((fstarr[20][2]*Vpk[14][20][2])
      +((fstarr[20][0]*Vpk[14][20][0])+(fstarr[20][1]*Vpk[14][20][1])))+((
      tstarr[20][2]*Wpk[14][20][2])+((tstarr[20][0]*Wpk[14][20][0])+(
      tstarr[20][1]*Wpk[14][20][1]))))));
    trqout[15] = -((mtau[15]+utau[15])+((((fstarr[17][2]*Vpk[15][17][2])+((
      fstarr[17][0]*Vpk[15][17][0])+(fstarr[17][1]*Vpk[15][17][1])))+((
      tstarr[17][2]*Wpk[15][17][2])+((tstarr[17][0]*Wpk[15][17][0])+(
      tstarr[17][1]*Wpk[15][17][1]))))+(((fstarr[20][2]*Vpk[15][20][2])+((
      fstarr[20][0]*Vpk[15][20][0])+(fstarr[20][1]*Vpk[15][20][1])))+((
      tstarr[20][2]*Wpk[15][20][2])+((tstarr[20][0]*Wpk[15][20][0])+(
      tstarr[20][1]*Wpk[15][20][1]))))));
    trqout[16] = -((mtau[16]+utau[16])+((((fstarr[17][2]*Vpk[16][17][2])+((
      fstarr[17][0]*Vpk[16][17][0])+(fstarr[17][1]*Vpk[16][17][1])))+((
      tstarr[17][2]*Wpk[16][17][2])+((tstarr[17][0]*Wpk[16][17][0])+(
      tstarr[17][1]*Wpk[16][17][1]))))+(((fstarr[20][2]*Vpk[16][20][2])+((
      fstarr[20][0]*Vpk[16][20][0])+(fstarr[20][1]*Vpk[16][20][1])))+((
      tstarr[20][2]*Wpk[16][20][2])+((tstarr[20][0]*Wpk[16][20][0])+(
      tstarr[20][1]*Wpk[16][20][1]))))));
    trqout[17] = -((mtau[17]+utau[17])+((((fstarr[17][2]*Vpk[17][17][2])+((
      fstarr[17][0]*Vpk[17][17][0])+(fstarr[17][1]*Vpk[17][17][1])))+((
      pin[17][2]*tstarr[17][2])+((pin[17][0]*tstarr[17][0])+(pin[17][1]*
      tstarr[17][1]))))+(((fstarr[20][2]*Vpk[17][20][2])+((fstarr[20][0]*
      Vpk[17][20][0])+(fstarr[20][1]*Vpk[17][20][1])))+((tstarr[20][2]*
      Wpk[17][20][2])+((tstarr[20][0]*Wpk[17][20][0])+(tstarr[20][1]*
      Wpk[17][20][1]))))));
    trqout[18] = -((mtau[18]+utau[18])+(((fstarr[20][2]*Vpk[18][20][2])+((
      fstarr[20][0]*Vpk[18][20][0])+(fstarr[20][1]*Vpk[18][20][1])))+((
      tstarr[20][2]*Wpk[18][20][2])+((tstarr[20][0]*Wpk[18][20][0])+(
      tstarr[20][1]*Wpk[18][20][1])))));
    trqout[19] = -((mtau[19]+utau[19])+(((fstarr[20][2]*Vpk[19][20][2])+((
      fstarr[20][0]*Vpk[19][20][0])+(fstarr[20][1]*Vpk[19][20][1])))+((
      tstarr[20][2]*Wpk[19][20][2])+((tstarr[20][0]*Wpk[19][20][0])+(
      tstarr[20][1]*Wpk[19][20][1])))));
    trqout[20] = -((mtau[20]+utau[20])+(((fstarr[20][2]*Vpk[20][20][2])+((
      fstarr[20][0]*Vpk[20][20][0])+(fstarr[20][1]*Vpk[20][20][1])))+((
      pin[20][2]*tstarr[20][2])+((pin[20][0]*tstarr[20][0])+(pin[20][1]*
      tstarr[20][1])))));
    temp[0] = ((((fstarr[23][2]*Vpk[21][23][2])+((.1715*(fstarr[23][0]*
      Wpk[21][23][2]))-(.002*(fstarr[23][1]*Wpk[21][23][2]))))+((tstarr[23][2]*
      Wpk[21][23][2])+((tstarr[23][0]*Wpk[21][23][0])+(tstarr[23][1]*
      Wpk[21][23][1]))))+(((fstarr[26][2]*Vpk[21][26][2])+((fstarr[26][0]*
      Vpk[21][26][0])+(fstarr[26][1]*Vpk[21][26][1])))+((tstarr[26][2]*
      Wpk[21][26][2])+((tstarr[26][0]*Wpk[21][26][0])+(tstarr[26][1]*
      Wpk[21][26][1])))));
    trqout[21] = -((mtau[21]+utau[21])+((((fstarr[32][2]*Vpk[21][32][2])+((
      fstarr[32][0]*Vpk[21][32][0])+(fstarr[32][1]*Vpk[21][32][1])))+((
      tstarr[32][2]*Wpk[21][32][2])+((tstarr[32][0]*Wpk[21][32][0])+(
      tstarr[32][1]*Wpk[21][32][1]))))+((((fstarr[29][2]*Vpk[21][29][2])+((
      fstarr[29][0]*Vpk[21][29][0])+(fstarr[29][1]*Vpk[21][29][1])))+((
      tstarr[29][2]*Wpk[21][29][2])+((tstarr[29][0]*Wpk[21][29][0])+(
      tstarr[29][1]*Wpk[21][29][1]))))+temp[0])));
    temp[0] = ((((fstarr[23][2]*Vpk[22][23][2])+((.1715*(fstarr[23][0]*
      Wpk[22][23][2]))-(.002*(fstarr[23][1]*Wpk[22][23][2]))))+((tstarr[23][2]*
      Wpk[22][23][2])+((tstarr[23][0]*Wpk[22][23][0])+(tstarr[23][1]*
      Wpk[22][23][1]))))+(((fstarr[26][2]*Vpk[22][26][2])+((fstarr[26][0]*
      Vpk[22][26][0])+(fstarr[26][1]*Vpk[22][26][1])))+((tstarr[26][2]*
      Wpk[22][26][2])+((tstarr[26][0]*Wpk[22][26][0])+(tstarr[26][1]*
      Wpk[22][26][1])))));
    trqout[22] = -((mtau[22]+utau[22])+((((fstarr[32][2]*Vpk[22][32][2])+((
      fstarr[32][0]*Vpk[22][32][0])+(fstarr[32][1]*Vpk[22][32][1])))+((
      tstarr[32][2]*Wpk[22][32][2])+((tstarr[32][0]*Wpk[22][32][0])+(
      tstarr[32][1]*Wpk[22][32][1]))))+((((fstarr[29][2]*Vpk[22][29][2])+((
      fstarr[29][0]*Vpk[22][29][0])+(fstarr[29][1]*Vpk[22][29][1])))+((
      tstarr[29][2]*Wpk[22][29][2])+((tstarr[29][0]*Wpk[22][29][0])+(
      tstarr[29][1]*Wpk[22][29][1]))))+temp[0])));
    temp[0] = ((((fstarr[23][2]*Vpk[23][23][2])+((.1715*(fstarr[23][0]*
      pin[23][2]))-(.002*(fstarr[23][1]*pin[23][2]))))+((pin[23][2]*
      tstarr[23][2])+((pin[23][0]*tstarr[23][0])+(pin[23][1]*tstarr[23][1]))))+(
      ((fstarr[26][2]*Vpk[23][26][2])+((fstarr[26][0]*Vpk[23][26][0])+(
      fstarr[26][1]*Vpk[23][26][1])))+((tstarr[26][2]*Wpk[23][26][2])+((
      tstarr[26][0]*Wpk[23][26][0])+(tstarr[26][1]*Wpk[23][26][1])))));
    trqout[23] = -((mtau[23]+utau[23])+((((fstarr[32][2]*Vpk[23][32][2])+((
      fstarr[32][0]*Vpk[23][32][0])+(fstarr[32][1]*Vpk[23][32][1])))+((
      tstarr[32][2]*Wpk[23][32][2])+((tstarr[32][0]*Wpk[23][32][0])+(
      tstarr[32][1]*Wpk[23][32][1]))))+((((fstarr[29][2]*Vpk[23][29][2])+((
      fstarr[29][0]*Vpk[23][29][0])+(fstarr[29][1]*Vpk[23][29][1])))+((
      tstarr[29][2]*Wpk[23][29][2])+((tstarr[29][0]*Wpk[23][29][0])+(
      tstarr[29][1]*Wpk[23][29][1]))))+temp[0])));
    temp[0] = (((.1862*((fstarr[26][0]*Wpk[24][26][2])-(fstarr[26][2]*
      Wpk[24][26][0])))+((tstarr[26][2]*Wpk[24][26][2])+((tstarr[26][0]*
      Wpk[24][26][0])+(tstarr[26][1]*Wpk[24][26][1]))))+(((fstarr[29][2]*
      Vpk[24][29][2])+((fstarr[29][0]*Vpk[24][29][0])+(fstarr[29][1]*
      Vpk[24][29][1])))+((tstarr[29][2]*Wpk[24][29][2])+((tstarr[29][0]*
      Wpk[24][29][0])+(tstarr[29][1]*Wpk[24][29][1])))));
    trqout[24] = -((mtau[24]+utau[24])+(temp[0]+(((fstarr[32][2]*Vpk[24][32][2])
      +((fstarr[32][0]*Vpk[24][32][0])+(fstarr[32][1]*Vpk[24][32][1])))+((
      tstarr[32][2]*Wpk[24][32][2])+((tstarr[32][0]*Wpk[24][32][0])+(
      tstarr[32][1]*Wpk[24][32][1]))))));
    temp[0] = (((.1862*((fstarr[26][0]*Wpk[25][26][2])-(fstarr[26][2]*
      Wpk[25][26][0])))+((tstarr[26][2]*Wpk[25][26][2])+((tstarr[26][0]*
      Wpk[25][26][0])+(tstarr[26][1]*Wpk[25][26][1]))))+(((fstarr[29][2]*
      Vpk[25][29][2])+((fstarr[29][0]*Vpk[25][29][0])+(fstarr[29][1]*
      Vpk[25][29][1])))+((tstarr[29][2]*Wpk[25][29][2])+((tstarr[29][0]*
      Wpk[25][29][0])+(tstarr[29][1]*Wpk[25][29][1])))));
    trqout[25] = -((mtau[25]+utau[25])+(temp[0]+(((fstarr[32][2]*Vpk[25][32][2])
      +((fstarr[32][0]*Vpk[25][32][0])+(fstarr[32][1]*Vpk[25][32][1])))+((
      tstarr[32][2]*Wpk[25][32][2])+((tstarr[32][0]*Wpk[25][32][0])+(
      tstarr[32][1]*Wpk[25][32][1]))))));
    temp[0] = (((.1862*((fstarr[26][0]*pin[26][2])-(fstarr[26][2]*pin[26][0])))+
      ((pin[26][2]*tstarr[26][2])+((pin[26][0]*tstarr[26][0])+(pin[26][1]*
      tstarr[26][1]))))+(((fstarr[29][2]*Vpk[26][29][2])+((fstarr[29][0]*
      Vpk[26][29][0])+(fstarr[29][1]*Vpk[26][29][1])))+((tstarr[29][2]*
      Wpk[26][29][2])+((tstarr[29][0]*Wpk[26][29][0])+(tstarr[29][1]*
      Wpk[26][29][1])))));
    trqout[26] = -((mtau[26]+utau[26])+(temp[0]+(((fstarr[32][2]*Vpk[26][32][2])
      +((fstarr[32][0]*Vpk[26][32][0])+(fstarr[32][1]*Vpk[26][32][1])))+((
      tstarr[32][2]*Wpk[26][32][2])+((tstarr[32][0]*Wpk[26][32][0])+(
      tstarr[32][1]*Wpk[26][32][1]))))));
    trqout[27] = -((mtau[27]+utau[27])+((((fstarr[29][2]*Vpk[27][29][2])+((
      fstarr[29][0]*Vpk[27][29][0])+(fstarr[29][1]*Vpk[27][29][1])))+((
      tstarr[29][2]*Wpk[27][29][2])+((tstarr[29][0]*Wpk[27][29][0])+(
      tstarr[29][1]*Wpk[27][29][1]))))+(((fstarr[32][2]*Vpk[27][32][2])+((
      fstarr[32][0]*Vpk[27][32][0])+(fstarr[32][1]*Vpk[27][32][1])))+((
      tstarr[32][2]*Wpk[27][32][2])+((tstarr[32][0]*Wpk[27][32][0])+(
      tstarr[32][1]*Wpk[27][32][1]))))));
    trqout[28] = -((mtau[28]+utau[28])+((((fstarr[29][2]*Vpk[28][29][2])+((
      fstarr[29][0]*Vpk[28][29][0])+(fstarr[29][1]*Vpk[28][29][1])))+((
      tstarr[29][2]*Wpk[28][29][2])+((tstarr[29][0]*Wpk[28][29][0])+(
      tstarr[29][1]*Wpk[28][29][1]))))+(((fstarr[32][2]*Vpk[28][32][2])+((
      fstarr[32][0]*Vpk[28][32][0])+(fstarr[32][1]*Vpk[28][32][1])))+((
      tstarr[32][2]*Wpk[28][32][2])+((tstarr[32][0]*Wpk[28][32][0])+(
      tstarr[32][1]*Wpk[28][32][1]))))));
    trqout[29] = -((mtau[29]+utau[29])+((((fstarr[29][2]*Vpk[29][29][2])+((
      fstarr[29][0]*Vpk[29][29][0])+(fstarr[29][1]*Vpk[29][29][1])))+((
      pin[29][2]*tstarr[29][2])+((pin[29][0]*tstarr[29][0])+(pin[29][1]*
      tstarr[29][1]))))+(((fstarr[32][2]*Vpk[29][32][2])+((fstarr[32][0]*
      Vpk[29][32][0])+(fstarr[32][1]*Vpk[29][32][1])))+((tstarr[32][2]*
      Wpk[29][32][2])+((tstarr[32][0]*Wpk[29][32][0])+(tstarr[32][1]*
      Wpk[29][32][1]))))));
    trqout[30] = -((mtau[30]+utau[30])+(((fstarr[32][2]*Vpk[30][32][2])+((
      fstarr[32][0]*Vpk[30][32][0])+(fstarr[32][1]*Vpk[30][32][1])))+((
      tstarr[32][2]*Wpk[30][32][2])+((tstarr[32][0]*Wpk[30][32][0])+(
      tstarr[32][1]*Wpk[30][32][1])))));
    trqout[31] = -((mtau[31]+utau[31])+(((fstarr[32][2]*Vpk[31][32][2])+((
      fstarr[32][0]*Vpk[31][32][0])+(fstarr[32][1]*Vpk[31][32][1])))+((
      tstarr[32][2]*Wpk[31][32][2])+((tstarr[32][0]*Wpk[31][32][0])+(
      tstarr[32][1]*Wpk[31][32][1])))));
    trqout[32] = -((mtau[32]+utau[32])+(((fstarr[32][2]*Vpk[32][32][2])+((
      fstarr[32][0]*Vpk[32][32][0])+(fstarr[32][1]*Vpk[32][32][1])))+((
      pin[32][2]*tstarr[32][2])+((pin[32][0]*tstarr[32][0])+(pin[32][1]*
      tstarr[32][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.05 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 1556 adds/subtracts/negates
                   1647 multiplies
                      0 divides
                    324 assignments
*/
}

void sdcomptrq(double udotin[33],
    double trqout[33])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    int i;
    double multin[33];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    for (i = 0; i < 33; i++) {
        multin[i] = 0.;
    }
    sdfulltrq(udotin,multin,trqout);
}

void sdmulttrq(double multin[33],
    double trqout[33])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    sdmfrc(multin);
    sdfsmult();
    for (i = 0; i < 33; i++) {
        trqout[i] = fs[i];
    }
}

void sdrhs(void)
{
/*
Generated 15-Feb-2006 17:06:53 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = (mtau[0]+utau[0]);
    tauc[1] = (mtau[1]+utau[1]);
    tauc[2] = (mtau[2]+utau[2]);
    tauc[3] = (mtau[3]+utau[3]);
    tauc[4] = (mtau[4]+utau[4]);
    tauc[5] = (mtau[5]+utau[5]);
    tauc[6] = (mtau[6]+utau[6]);
    tauc[7] = (mtau[7]+utau[7]);
    tauc[8] = (mtau[8]+utau[8]);
    tauc[9] = (mtau[9]+utau[9]);
    tauc[10] = (mtau[10]+utau[10]);
    tauc[11] = (mtau[11]+utau[11]);
    tauc[12] = (mtau[12]+utau[12]);
    tauc[13] = (mtau[13]+utau[13]);
    tauc[14] = (mtau[14]+utau[14]);
    tauc[15] = (mtau[15]+utau[15]);
    tauc[16] = (mtau[16]+utau[16]);
    tauc[17] = (mtau[17]+utau[17]);
    tauc[18] = (mtau[18]+utau[18]);
    tauc[19] = (mtau[19]+utau[19]);
    tauc[20] = (mtau[20]+utau[20]);
    tauc[21] = (mtau[21]+utau[21]);
    tauc[22] = (mtau[22]+utau[22]);
    tauc[23] = (mtau[23]+utau[23]);
    tauc[24] = (mtau[24]+utau[24]);
    tauc[25] = (mtau[25]+utau[25]);
    tauc[26] = (mtau[26]+utau[26]);
    tauc[27] = (mtau[27]+utau[27]);
    tauc[28] = (mtau[28]+utau[28]);
    tauc[29] = (mtau[29]+utau[29]);
    tauc[30] = (mtau[30]+utau[30]);
    tauc[31] = (mtau[31]+utau[31]);
    tauc[32] = (mtau[32]+utau[32]);
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[6][0] = ((pin[6][0]*udot[6])+((Cik[6][2][0]*udot[5])+((Cik[6][0][0]*
      udot[3])+(Cik[6][1][0]*udot[4]))));
    Onkb[6][1] = ((pin[6][1]*udot[6])+((Cik[6][2][1]*udot[5])+((Cik[6][0][1]*
      udot[3])+(Cik[6][1][1]*udot[4]))));
    Onkb[6][2] = ((pin[6][2]*udot[6])+((Cik[6][2][2]*udot[5])+((Cik[6][0][2]*
      udot[3])+(Cik[6][1][2]*udot[4]))));
    Onkb[7][0] = ((pin[7][0]*udot[7])+((Cik[7][2][0]*Onkb[6][2])+((Cik[7][0][0]*
      Onkb[6][0])+(Cik[7][1][0]*Onkb[6][1]))));
    Onkb[7][1] = ((pin[7][1]*udot[7])+((Cik[7][2][1]*Onkb[6][2])+((Cik[7][0][1]*
      Onkb[6][0])+(Cik[7][1][1]*Onkb[6][1]))));
    Onkb[7][2] = ((pin[7][2]*udot[7])+((Cik[7][2][2]*Onkb[6][2])+((Cik[7][0][2]*
      Onkb[6][0])+(Cik[7][1][2]*Onkb[6][1]))));
    Onkb[8][0] = ((pin[8][0]*udot[8])+((Cik[8][2][0]*Onkb[7][2])+((Cik[8][0][0]*
      Onkb[7][0])+(Cik[8][1][0]*Onkb[7][1]))));
    Onkb[8][1] = ((pin[8][1]*udot[8])+((Cik[8][2][1]*Onkb[7][2])+((Cik[8][0][1]*
      Onkb[7][0])+(Cik[8][1][1]*Onkb[7][1]))));
    Onkb[8][2] = ((pin[8][2]*udot[8])+((Cik[8][2][2]*Onkb[7][2])+((Cik[8][0][2]*
      Onkb[7][0])+(Cik[8][1][2]*Onkb[7][1]))));
    Onkb[9][0] = ((pin[9][0]*udot[9])+((Cik[9][2][0]*udot[5])+((Cik[9][0][0]*
      udot[3])+(Cik[9][1][0]*udot[4]))));
    Onkb[9][1] = ((pin[9][1]*udot[9])+((Cik[9][2][1]*udot[5])+((Cik[9][0][1]*
      udot[3])+(Cik[9][1][1]*udot[4]))));
    Onkb[9][2] = ((pin[9][2]*udot[9])+((Cik[9][2][2]*udot[5])+((Cik[9][0][2]*
      udot[3])+(Cik[9][1][2]*udot[4]))));
    Onkb[10][0] = ((pin[10][0]*udot[10])+((Cik[10][2][0]*Onkb[9][2])+((
      Cik[10][0][0]*Onkb[9][0])+(Cik[10][1][0]*Onkb[9][1]))));
    Onkb[10][1] = ((pin[10][1]*udot[10])+((Cik[10][2][1]*Onkb[9][2])+((
      Cik[10][0][1]*Onkb[9][0])+(Cik[10][1][1]*Onkb[9][1]))));
    Onkb[10][2] = ((pin[10][2]*udot[10])+((Cik[10][2][2]*Onkb[9][2])+((
      Cik[10][0][2]*Onkb[9][0])+(Cik[10][1][2]*Onkb[9][1]))));
    Onkb[11][0] = ((pin[11][0]*udot[11])+((Cik[11][2][0]*Onkb[10][2])+((
      Cik[11][0][0]*Onkb[10][0])+(Cik[11][1][0]*Onkb[10][1]))));
    Onkb[11][1] = ((pin[11][1]*udot[11])+((Cik[11][2][1]*Onkb[10][2])+((
      Cik[11][0][1]*Onkb[10][0])+(Cik[11][1][1]*Onkb[10][1]))));
    Onkb[11][2] = ((pin[11][2]*udot[11])+((Cik[11][2][2]*Onkb[10][2])+((
      Cik[11][0][2]*Onkb[10][0])+(Cik[11][1][2]*Onkb[10][1]))));
    Onkb[12][0] = ((pin[12][0]*udot[12])+((Cik[12][2][0]*Onkb[11][2])+((
      Cik[12][0][0]*Onkb[11][0])+(Cik[12][1][0]*Onkb[11][1]))));
    Onkb[12][1] = ((pin[12][1]*udot[12])+((Cik[12][2][1]*Onkb[11][2])+((
      Cik[12][0][1]*Onkb[11][0])+(Cik[12][1][1]*Onkb[11][1]))));
    Onkb[12][2] = ((pin[12][2]*udot[12])+((Cik[12][2][2]*Onkb[11][2])+((
      Cik[12][0][2]*Onkb[11][0])+(Cik[12][1][2]*Onkb[11][1]))));
    Onkb[13][0] = ((pin[13][0]*udot[13])+((Cik[13][2][0]*Onkb[12][2])+((
      Cik[13][0][0]*Onkb[12][0])+(Cik[13][1][0]*Onkb[12][1]))));
    Onkb[13][1] = ((pin[13][1]*udot[13])+((Cik[13][2][1]*Onkb[12][2])+((
      Cik[13][0][1]*Onkb[12][0])+(Cik[13][1][1]*Onkb[12][1]))));
    Onkb[13][2] = ((pin[13][2]*udot[13])+((Cik[13][2][2]*Onkb[12][2])+((
      Cik[13][0][2]*Onkb[12][0])+(Cik[13][1][2]*Onkb[12][1]))));
    Onkb[14][0] = ((pin[14][0]*udot[14])+((Cik[14][2][0]*Onkb[13][2])+((
      Cik[14][0][0]*Onkb[13][0])+(Cik[14][1][0]*Onkb[13][1]))));
    Onkb[14][1] = ((pin[14][1]*udot[14])+((Cik[14][2][1]*Onkb[13][2])+((
      Cik[14][0][1]*Onkb[13][0])+(Cik[14][1][1]*Onkb[13][1]))));
    Onkb[14][2] = ((pin[14][2]*udot[14])+((Cik[14][2][2]*Onkb[13][2])+((
      Cik[14][0][2]*Onkb[13][0])+(Cik[14][1][2]*Onkb[13][1]))));
    Onkb[15][0] = ((pin[15][0]*udot[15])+((Cik[15][2][0]*Onkb[14][2])+((
      Cik[15][0][0]*Onkb[14][0])+(Cik[15][1][0]*Onkb[14][1]))));
    Onkb[15][1] = ((pin[15][1]*udot[15])+((Cik[15][2][1]*Onkb[14][2])+((
      Cik[15][0][1]*Onkb[14][0])+(Cik[15][1][1]*Onkb[14][1]))));
    Onkb[15][2] = ((pin[15][2]*udot[15])+((Cik[15][2][2]*Onkb[14][2])+((
      Cik[15][0][2]*Onkb[14][0])+(Cik[15][1][2]*Onkb[14][1]))));
    Onkb[16][0] = ((pin[16][0]*udot[16])+((Cik[16][2][0]*Onkb[15][2])+((
      Cik[16][0][0]*Onkb[15][0])+(Cik[16][1][0]*Onkb[15][1]))));
    Onkb[16][1] = ((pin[16][1]*udot[16])+((Cik[16][2][1]*Onkb[15][2])+((
      Cik[16][0][1]*Onkb[15][0])+(Cik[16][1][1]*Onkb[15][1]))));
    Onkb[16][2] = ((pin[16][2]*udot[16])+((Cik[16][2][2]*Onkb[15][2])+((
      Cik[16][0][2]*Onkb[15][0])+(Cik[16][1][2]*Onkb[15][1]))));
    Onkb[17][0] = ((pin[17][0]*udot[17])+((Cik[17][2][0]*Onkb[16][2])+((
      Cik[17][0][0]*Onkb[16][0])+(Cik[17][1][0]*Onkb[16][1]))));
    Onkb[17][1] = ((pin[17][1]*udot[17])+((Cik[17][2][1]*Onkb[16][2])+((
      Cik[17][0][1]*Onkb[16][0])+(Cik[17][1][1]*Onkb[16][1]))));
    Onkb[17][2] = ((pin[17][2]*udot[17])+((Cik[17][2][2]*Onkb[16][2])+((
      Cik[17][0][2]*Onkb[16][0])+(Cik[17][1][2]*Onkb[16][1]))));
    Onkb[18][0] = ((pin[18][0]*udot[18])+((Cik[18][2][0]*Onkb[17][2])+((
      Cik[18][0][0]*Onkb[17][0])+(Cik[18][1][0]*Onkb[17][1]))));
    Onkb[18][1] = ((pin[18][1]*udot[18])+((Cik[18][2][1]*Onkb[17][2])+((
      Cik[18][0][1]*Onkb[17][0])+(Cik[18][1][1]*Onkb[17][1]))));
    Onkb[18][2] = ((pin[18][2]*udot[18])+((Cik[18][2][2]*Onkb[17][2])+((
      Cik[18][0][2]*Onkb[17][0])+(Cik[18][1][2]*Onkb[17][1]))));
    Onkb[19][0] = ((pin[19][0]*udot[19])+((Cik[19][2][0]*Onkb[18][2])+((
      Cik[19][0][0]*Onkb[18][0])+(Cik[19][1][0]*Onkb[18][1]))));
    Onkb[19][1] = ((pin[19][1]*udot[19])+((Cik[19][2][1]*Onkb[18][2])+((
      Cik[19][0][1]*Onkb[18][0])+(Cik[19][1][1]*Onkb[18][1]))));
    Onkb[19][2] = ((pin[19][2]*udot[19])+((Cik[19][2][2]*Onkb[18][2])+((
      Cik[19][0][2]*Onkb[18][0])+(Cik[19][1][2]*Onkb[18][1]))));
    Onkb[20][0] = ((pin[20][0]*udot[20])+((Cik[20][2][0]*Onkb[19][2])+((
      Cik[20][0][0]*Onkb[19][0])+(Cik[20][1][0]*Onkb[19][1]))));
    Onkb[20][1] = ((pin[20][1]*udot[20])+((Cik[20][2][1]*Onkb[19][2])+((
      Cik[20][0][1]*Onkb[19][0])+(Cik[20][1][1]*Onkb[19][1]))));
    Onkb[20][2] = ((pin[20][2]*udot[20])+((Cik[20][2][2]*Onkb[19][2])+((
      Cik[20][0][2]*Onkb[19][0])+(Cik[20][1][2]*Onkb[19][1]))));
    Onkb[21][0] = ((pin[21][0]*udot[21])+((Cik[21][2][0]*udot[5])+((
      Cik[21][0][0]*udot[3])+(Cik[21][1][0]*udot[4]))));
    Onkb[21][1] = ((pin[21][1]*udot[21])+((Cik[21][2][1]*udot[5])+((
      Cik[21][0][1]*udot[3])+(Cik[21][1][1]*udot[4]))));
    Onkb[21][2] = ((pin[21][2]*udot[21])+((Cik[21][2][2]*udot[5])+((
      Cik[21][0][2]*udot[3])+(Cik[21][1][2]*udot[4]))));
    Onkb[22][0] = ((pin[22][0]*udot[22])+((Cik[22][2][0]*Onkb[21][2])+((
      Cik[22][0][0]*Onkb[21][0])+(Cik[22][1][0]*Onkb[21][1]))));
    Onkb[22][1] = ((pin[22][1]*udot[22])+((Cik[22][2][1]*Onkb[21][2])+((
      Cik[22][0][1]*Onkb[21][0])+(Cik[22][1][1]*Onkb[21][1]))));
    Onkb[22][2] = ((pin[22][2]*udot[22])+((Cik[22][2][2]*Onkb[21][2])+((
      Cik[22][0][2]*Onkb[21][0])+(Cik[22][1][2]*Onkb[21][1]))));
    Onkb[23][0] = ((pin[23][0]*udot[23])+((Cik[23][2][0]*Onkb[22][2])+((
      Cik[23][0][0]*Onkb[22][0])+(Cik[23][1][0]*Onkb[22][1]))));
    Onkb[23][1] = ((pin[23][1]*udot[23])+((Cik[23][2][1]*Onkb[22][2])+((
      Cik[23][0][1]*Onkb[22][0])+(Cik[23][1][1]*Onkb[22][1]))));
    Onkb[23][2] = ((pin[23][2]*udot[23])+((Cik[23][2][2]*Onkb[22][2])+((
      Cik[23][0][2]*Onkb[22][0])+(Cik[23][1][2]*Onkb[22][1]))));
    Onkb[24][0] = ((pin[24][0]*udot[24])+((Cik[24][2][0]*Onkb[23][2])+((
      Cik[24][0][0]*Onkb[23][0])+(Cik[24][1][0]*Onkb[23][1]))));
    Onkb[24][1] = ((pin[24][1]*udot[24])+((Cik[24][2][1]*Onkb[23][2])+((
      Cik[24][0][1]*Onkb[23][0])+(Cik[24][1][1]*Onkb[23][1]))));
    Onkb[24][2] = ((pin[24][2]*udot[24])+((Cik[24][2][2]*Onkb[23][2])+((
      Cik[24][0][2]*Onkb[23][0])+(Cik[24][1][2]*Onkb[23][1]))));
    Onkb[25][0] = ((pin[25][0]*udot[25])+((Cik[25][2][0]*Onkb[24][2])+((
      Cik[25][0][0]*Onkb[24][0])+(Cik[25][1][0]*Onkb[24][1]))));
    Onkb[25][1] = ((pin[25][1]*udot[25])+((Cik[25][2][1]*Onkb[24][2])+((
      Cik[25][0][1]*Onkb[24][0])+(Cik[25][1][1]*Onkb[24][1]))));
    Onkb[25][2] = ((pin[25][2]*udot[25])+((Cik[25][2][2]*Onkb[24][2])+((
      Cik[25][0][2]*Onkb[24][0])+(Cik[25][1][2]*Onkb[24][1]))));
    Onkb[26][0] = ((pin[26][0]*udot[26])+((Cik[26][2][0]*Onkb[25][2])+((
      Cik[26][0][0]*Onkb[25][0])+(Cik[26][1][0]*Onkb[25][1]))));
    Onkb[26][1] = ((pin[26][1]*udot[26])+((Cik[26][2][1]*Onkb[25][2])+((
      Cik[26][0][1]*Onkb[25][0])+(Cik[26][1][1]*Onkb[25][1]))));
    Onkb[26][2] = ((pin[26][2]*udot[26])+((Cik[26][2][2]*Onkb[25][2])+((
      Cik[26][0][2]*Onkb[25][0])+(Cik[26][1][2]*Onkb[25][1]))));
    Onkb[27][0] = ((pin[27][0]*udot[27])+((Cik[27][2][0]*Onkb[26][2])+((
      Cik[27][0][0]*Onkb[26][0])+(Cik[27][1][0]*Onkb[26][1]))));
    Onkb[27][1] = ((pin[27][1]*udot[27])+((Cik[27][2][1]*Onkb[26][2])+((
      Cik[27][0][1]*Onkb[26][0])+(Cik[27][1][1]*Onkb[26][1]))));
    Onkb[27][2] = ((pin[27][2]*udot[27])+((Cik[27][2][2]*Onkb[26][2])+((
      Cik[27][0][2]*Onkb[26][0])+(Cik[27][1][2]*Onkb[26][1]))));
    Onkb[28][0] = ((pin[28][0]*udot[28])+((Cik[28][2][0]*Onkb[27][2])+((
      Cik[28][0][0]*Onkb[27][0])+(Cik[28][1][0]*Onkb[27][1]))));
    Onkb[28][1] = ((pin[28][1]*udot[28])+((Cik[28][2][1]*Onkb[27][2])+((
      Cik[28][0][1]*Onkb[27][0])+(Cik[28][1][1]*Onkb[27][1]))));
    Onkb[28][2] = ((pin[28][2]*udot[28])+((Cik[28][2][2]*Onkb[27][2])+((
      Cik[28][0][2]*Onkb[27][0])+(Cik[28][1][2]*Onkb[27][1]))));
    Onkb[29][0] = ((pin[29][0]*udot[29])+((Cik[29][2][0]*Onkb[28][2])+((
      Cik[29][0][0]*Onkb[28][0])+(Cik[29][1][0]*Onkb[28][1]))));
    Onkb[29][1] = ((pin[29][1]*udot[29])+((Cik[29][2][1]*Onkb[28][2])+((
      Cik[29][0][1]*Onkb[28][0])+(Cik[29][1][1]*Onkb[28][1]))));
    Onkb[29][2] = ((pin[29][2]*udot[29])+((Cik[29][2][2]*Onkb[28][2])+((
      Cik[29][0][2]*Onkb[28][0])+(Cik[29][1][2]*Onkb[28][1]))));
    Onkb[30][0] = ((pin[30][0]*udot[30])+((Cik[30][2][0]*Onkb[29][2])+((
      Cik[30][0][0]*Onkb[29][0])+(Cik[30][1][0]*Onkb[29][1]))));
    Onkb[30][1] = ((pin[30][1]*udot[30])+((Cik[30][2][1]*Onkb[29][2])+((
      Cik[30][0][1]*Onkb[29][0])+(Cik[30][1][1]*Onkb[29][1]))));
    Onkb[30][2] = ((pin[30][2]*udot[30])+((Cik[30][2][2]*Onkb[29][2])+((
      Cik[30][0][2]*Onkb[29][0])+(Cik[30][1][2]*Onkb[29][1]))));
    Onkb[31][0] = ((pin[31][0]*udot[31])+((Cik[31][2][0]*Onkb[30][2])+((
      Cik[31][0][0]*Onkb[30][0])+(Cik[31][1][0]*Onkb[30][1]))));
    Onkb[31][1] = ((pin[31][1]*udot[31])+((Cik[31][2][1]*Onkb[30][2])+((
      Cik[31][0][1]*Onkb[30][0])+(Cik[31][1][1]*Onkb[30][1]))));
    Onkb[31][2] = ((pin[31][2]*udot[31])+((Cik[31][2][2]*Onkb[30][2])+((
      Cik[31][0][2]*Onkb[30][0])+(Cik[31][1][2]*Onkb[30][1]))));
    Onkb[32][0] = ((pin[32][0]*udot[32])+((Cik[32][2][0]*Onkb[31][2])+((
      Cik[32][0][0]*Onkb[31][0])+(Cik[32][1][0]*Onkb[31][1]))));
    Onkb[32][1] = ((pin[32][1]*udot[32])+((Cik[32][2][1]*Onkb[31][2])+((
      Cik[32][0][1]*Onkb[31][0])+(Cik[32][1][1]*Onkb[31][1]))));
    Onkb[32][2] = ((pin[32][2]*udot[32])+((Cik[32][2][2]*Onkb[31][2])+((
      Cik[32][0][2]*Onkb[31][0])+(Cik[32][1][2]*Onkb[31][1]))));
    onk[8][0] = (Onkb[8][0]+Otk[8][0]);
    onk[8][1] = (Onkb[8][1]+Otk[8][1]);
    onk[8][2] = (Onkb[8][2]+Otk[8][2]);
    onk[11][0] = (Onkb[11][0]+Otk[11][0]);
    onk[11][1] = (Onkb[11][1]+Otk[11][1]);
    onk[11][2] = (Onkb[11][2]+Otk[11][2]);
    onk[14][0] = (Onkb[14][0]+Otk[14][0]);
    onk[14][1] = (Onkb[14][1]+Otk[14][1]);
    onk[14][2] = (Onkb[14][2]+Otk[14][2]);
    onk[17][0] = (Onkb[17][0]+Otk[17][0]);
    onk[17][1] = (Onkb[17][1]+Otk[17][1]);
    onk[17][2] = (Onkb[17][2]+Otk[17][2]);
    onk[20][0] = (Onkb[20][0]+Otk[20][0]);
    onk[20][1] = (Onkb[20][1]+Otk[20][1]);
    onk[20][2] = (Onkb[20][2]+Otk[20][2]);
    onk[23][0] = (Onkb[23][0]+Otk[23][0]);
    onk[23][1] = (Onkb[23][1]+Otk[23][1]);
    onk[23][2] = (Onkb[23][2]+Otk[23][2]);
    onk[26][0] = (Onkb[26][0]+Otk[26][0]);
    onk[26][1] = (Onkb[26][1]+Otk[26][1]);
    onk[26][2] = (Onkb[26][2]+Otk[26][2]);
    onk[29][0] = (Onkb[29][0]+Otk[29][0]);
    onk[29][1] = (Onkb[29][1]+Otk[29][1]);
    onk[29][2] = (Onkb[29][2]+Otk[29][2]);
    onk[32][0] = (Onkb[32][0]+Otk[32][0]);
    onk[32][1] = (Onkb[32][1]+Otk[32][1]);
    onk[32][2] = (Onkb[32][2]+Otk[32][2]);
    onb[0][0] = udot[3];
    onb[0][1] = udot[4];
    onb[0][2] = udot[5];
    onb[1][0] = onk[8][0];
    onb[1][1] = onk[8][1];
    onb[1][2] = onk[8][2];
    onb[2][0] = onk[11][0];
    onb[2][1] = onk[11][1];
    onb[2][2] = onk[11][2];
    onb[3][0] = onk[14][0];
    onb[3][1] = onk[14][1];
    onb[3][2] = onk[14][2];
    onb[4][0] = onk[17][0];
    onb[4][1] = onk[17][1];
    onb[4][2] = onk[17][2];
    onb[5][0] = onk[20][0];
    onb[5][1] = onk[20][1];
    onb[5][2] = onk[20][2];
    onb[6][0] = onk[23][0];
    onb[6][1] = onk[23][1];
    onb[6][2] = onk[23][2];
    onb[7][0] = onk[26][0];
    onb[7][1] = onk[26][1];
    onb[7][2] = onk[26][2];
    onb[8][0] = onk[29][0];
    onb[8][1] = onk[29][1];
    onb[8][2] = onk[29][2];
    onb[9][0] = onk[32][0];
    onb[9][1] = onk[32][1];
    onb[9][2] = onk[32][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-udot[5]);
    dyad[0][0][2] = (udot[4]+w0w2[0]);
    dyad[0][1][0] = (udot[5]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-udot[3]);
    dyad[0][2][0] = (w0w2[0]-udot[4]);
    dyad[0][2][1] = (udot[3]+w1w2[0]);
    dyad[0][2][2] = w00w11[0];
    dyad[1][0][0] = w11w22[1];
    dyad[1][0][1] = (w0w1[1]-onk[8][2]);
    dyad[1][0][2] = (onk[8][1]+w0w2[1]);
    dyad[1][1][0] = (onk[8][2]+w0w1[1]);
    dyad[1][1][1] = w00w22[1];
    dyad[1][1][2] = (w1w2[1]-onk[8][0]);
    dyad[1][2][0] = (w0w2[1]-onk[8][1]);
    dyad[1][2][1] = (onk[8][0]+w1w2[1]);
    dyad[1][2][2] = w00w11[1];
    dyad[2][0][0] = w11w22[2];
    dyad[2][0][1] = (w0w1[2]-onk[11][2]);
    dyad[2][0][2] = (onk[11][1]+w0w2[2]);
    dyad[2][1][0] = (onk[11][2]+w0w1[2]);
    dyad[2][1][1] = w00w22[2];
    dyad[2][1][2] = (w1w2[2]-onk[11][0]);
    dyad[2][2][0] = (w0w2[2]-onk[11][1]);
    dyad[2][2][1] = (onk[11][0]+w1w2[2]);
    dyad[2][2][2] = w00w11[2];
    dyad[3][0][0] = w11w22[3];
    dyad[3][0][1] = (w0w1[3]-onk[14][2]);
    dyad[3][0][2] = (onk[14][1]+w0w2[3]);
    dyad[3][1][0] = (onk[14][2]+w0w1[3]);
    dyad[3][1][1] = w00w22[3];
    dyad[3][1][2] = (w1w2[3]-onk[14][0]);
    dyad[3][2][0] = (w0w2[3]-onk[14][1]);
    dyad[3][2][1] = (onk[14][0]+w1w2[3]);
    dyad[3][2][2] = w00w11[3];
    dyad[4][0][0] = w11w22[4];
    dyad[4][0][1] = (w0w1[4]-onk[17][2]);
    dyad[4][0][2] = (onk[17][1]+w0w2[4]);
    dyad[4][1][0] = (onk[17][2]+w0w1[4]);
    dyad[4][1][1] = w00w22[4];
    dyad[4][1][2] = (w1w2[4]-onk[17][0]);
    dyad[4][2][0] = (w0w2[4]-onk[17][1]);
    dyad[4][2][1] = (onk[17][0]+w1w2[4]);
    dyad[4][2][2] = w00w11[4];
    dyad[5][0][0] = w11w22[5];
    dyad[5][0][1] = (w0w1[5]-onk[20][2]);
    dyad[5][0][2] = (onk[20][1]+w0w2[5]);
    dyad[5][1][0] = (onk[20][2]+w0w1[5]);
    dyad[5][1][1] = w00w22[5];
    dyad[5][1][2] = (w1w2[5]-onk[20][0]);
    dyad[5][2][0] = (w0w2[5]-onk[20][1]);
    dyad[5][2][1] = (onk[20][0]+w1w2[5]);
    dyad[5][2][2] = w00w11[5];
    dyad[6][0][0] = w11w22[6];
    dyad[6][0][1] = (w0w1[6]-onk[23][2]);
    dyad[6][0][2] = (onk[23][1]+w0w2[6]);
    dyad[6][1][0] = (onk[23][2]+w0w1[6]);
    dyad[6][1][1] = w00w22[6];
    dyad[6][1][2] = (w1w2[6]-onk[23][0]);
    dyad[6][2][0] = (w0w2[6]-onk[23][1]);
    dyad[6][2][1] = (onk[23][0]+w1w2[6]);
    dyad[6][2][2] = w00w11[6];
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-onk[26][2]);
    dyad[7][0][2] = (onk[26][1]+w0w2[7]);
    dyad[7][1][0] = (onk[26][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-onk[26][0]);
    dyad[7][2][0] = (w0w2[7]-onk[26][1]);
    dyad[7][2][1] = (onk[26][0]+w1w2[7]);
    dyad[7][2][2] = w00w11[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-onk[29][2]);
    dyad[8][0][2] = (onk[29][1]+w0w2[8]);
    dyad[8][1][0] = (onk[29][2]+w0w1[8]);
    dyad[8][1][1] = w00w22[8];
    dyad[8][1][2] = (w1w2[8]-onk[29][0]);
    dyad[8][2][0] = (w0w2[8]-onk[29][1]);
    dyad[8][2][1] = (onk[29][0]+w1w2[8]);
    dyad[8][2][2] = w00w11[8];
    dyad[9][0][0] = w11w22[9];
    dyad[9][0][1] = (w0w1[9]-onk[32][2]);
    dyad[9][0][2] = (onk[32][1]+w0w2[9]);
    dyad[9][1][0] = (onk[32][2]+w0w1[9]);
    dyad[9][1][1] = w00w22[9];
    dyad[9][1][2] = (w1w2[9]-onk[32][0]);
    dyad[9][2][0] = (w0w2[9]-onk[32][1]);
    dyad[9][2][1] = (onk[32][0]+w1w2[9]);
    dyad[9][2][2] = w00w11[9];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[0][0] = (pin[0][0]*udot[0]);
    Ankb[0][1] = (pin[0][1]*udot[0]);
    Ankb[0][2] = (pin[0][2]*udot[0]);
    Ankb[1][0] = (Ankb[0][0]+(pin[1][0]*udot[1]));
    Ankb[1][1] = (Ankb[0][1]+(pin[1][1]*udot[1]));
    Ankb[1][2] = (Ankb[0][2]+(pin[1][2]*udot[1]));
    Ankb[2][0] = (Ankb[1][0]+(pin[2][0]*udot[2]));
    Ankb[2][1] = (Ankb[1][1]+(pin[2][1]*udot[2]));
    Ankb[2][2] = (Ankb[1][2]+(pin[2][2]*udot[2]));
    Ankb[3][0] = ((Ankb[2][2]*Cik[3][2][0])+((Ankb[2][0]*Cik[3][0][0])+(
      Ankb[2][1]*Cik[3][1][0])));
    Ankb[3][1] = ((Ankb[2][2]*Cik[3][2][1])+((Ankb[2][0]*Cik[3][0][1])+(
      Ankb[2][1]*Cik[3][1][1])));
    Ankb[3][2] = ((Ankb[2][2]*Cik[3][2][2])+((Ankb[2][0]*Cik[3][0][2])+(
      Ankb[2][1]*Cik[3][1][2])));
    AOnkri[6][0] = (Ankb[3][0]-(.127*udot[5]));
    AOnkri[6][2] = (Ankb[3][2]+(.127*udot[3]));
    Ankb[6][0] = ((AOnkri[6][2]*Cik[6][2][0])+((Ankb[3][1]*Cik[6][1][0])+(
      AOnkri[6][0]*Cik[6][0][0])));
    Ankb[6][1] = ((AOnkri[6][2]*Cik[6][2][1])+((Ankb[3][1]*Cik[6][1][1])+(
      AOnkri[6][0]*Cik[6][0][1])));
    Ankb[6][2] = ((AOnkri[6][2]*Cik[6][2][2])+((Ankb[3][1]*Cik[6][1][2])+(
      AOnkri[6][0]*Cik[6][0][2])));
    Ankb[7][0] = ((Ankb[6][2]*Cik[7][2][0])+((Ankb[6][0]*Cik[7][0][0])+(
      Ankb[6][1]*Cik[7][1][0])));
    Ankb[7][1] = ((Ankb[6][2]*Cik[7][2][1])+((Ankb[6][0]*Cik[7][0][1])+(
      Ankb[6][1]*Cik[7][1][1])));
    Ankb[7][2] = ((Ankb[6][2]*Cik[7][2][2])+((Ankb[6][0]*Cik[7][0][2])+(
      Ankb[6][1]*Cik[7][1][2])));
    Ankb[8][0] = (((Ankb[7][2]*Cik[8][2][0])+((Ankb[7][0]*Cik[8][0][0])+(
      Ankb[7][1]*Cik[8][1][0])))-(.3202*Onkb[8][2]));
    Ankb[8][1] = ((Ankb[7][2]*Cik[8][2][1])+((Ankb[7][0]*Cik[8][0][1])+(
      Ankb[7][1]*Cik[8][1][1])));
    Ankb[8][2] = ((.3202*Onkb[8][0])+((Ankb[7][2]*Cik[8][2][2])+((Ankb[7][0]*
      Cik[8][0][2])+(Ankb[7][1]*Cik[8][1][2]))));
    AOnkri[9][0] = (Ankb[3][0]+((.07*udot[5])+(.0935*udot[4])));
    AOnkri[9][1] = (Ankb[3][1]-(.0935*udot[3]));
    AOnkri[9][2] = (Ankb[3][2]-(.07*udot[3]));
    Ankb[9][0] = ((AOnkri[9][2]*Cik[9][2][0])+((AOnkri[9][0]*Cik[9][0][0])+(
      AOnkri[9][1]*Cik[9][1][0])));
    Ankb[9][1] = ((AOnkri[9][2]*Cik[9][2][1])+((AOnkri[9][0]*Cik[9][0][1])+(
      AOnkri[9][1]*Cik[9][1][1])));
    Ankb[9][2] = ((AOnkri[9][2]*Cik[9][2][2])+((AOnkri[9][0]*Cik[9][0][2])+(
      AOnkri[9][1]*Cik[9][1][2])));
    Ankb[10][0] = ((Ankb[9][2]*Cik[10][2][0])+((Ankb[9][0]*Cik[10][0][0])+(
      Ankb[9][1]*Cik[10][1][0])));
    Ankb[10][1] = ((Ankb[9][2]*Cik[10][2][1])+((Ankb[9][0]*Cik[10][0][1])+(
      Ankb[9][1]*Cik[10][1][1])));
    Ankb[10][2] = ((Ankb[9][2]*Cik[10][2][2])+((Ankb[9][0]*Cik[10][0][2])+(
      Ankb[9][1]*Cik[10][1][2])));
    Ankb[11][0] = ((.1715*Onkb[11][2])+((Ankb[10][2]*Cik[11][2][0])+((
      Ankb[10][0]*Cik[11][0][0])+(Ankb[10][1]*Cik[11][1][0]))));
    Ankb[11][1] = (((Ankb[10][2]*Cik[11][2][1])+((Ankb[10][0]*Cik[11][0][1])+(
      Ankb[10][1]*Cik[11][1][1])))-(.002*Onkb[11][2]));
    Ankb[11][2] = (((.002*Onkb[11][1])-(.1715*Onkb[11][0]))+((Ankb[10][2]*
      Cik[11][2][2])+((Ankb[10][0]*Cik[11][0][2])+(Ankb[10][1]*Cik[11][1][2]))))
      ;
    AOnkri[12][0] = (Ankb[11][0]+(.2294*Onkb[11][2]));
    AOnkri[12][1] = (Ankb[11][1]+(.0033*Onkb[11][2]));
    AOnkri[12][2] = (Ankb[11][2]-((.0033*Onkb[11][1])+(.2294*Onkb[11][0])));
    Ankb[12][0] = ((AOnkri[12][2]*Cik[12][2][0])+((AOnkri[12][0]*Cik[12][0][0])+
      (AOnkri[12][1]*Cik[12][1][0])));
    Ankb[12][1] = ((AOnkri[12][2]*Cik[12][2][1])+((AOnkri[12][0]*Cik[12][0][1])+
      (AOnkri[12][1]*Cik[12][1][1])));
    Ankb[12][2] = ((AOnkri[12][2]*Cik[12][2][2])+((AOnkri[12][0]*Cik[12][0][2])+
      (AOnkri[12][1]*Cik[12][1][2])));
    Ankb[13][0] = ((Ankb[12][2]*Cik[13][2][0])+((Ankb[12][0]*Cik[13][0][0])+(
      Ankb[12][1]*Cik[13][1][0])));
    Ankb[13][1] = ((Ankb[12][2]*Cik[13][2][1])+((Ankb[12][0]*Cik[13][0][1])+(
      Ankb[12][1]*Cik[13][1][1])));
    Ankb[13][2] = ((Ankb[12][2]*Cik[13][2][2])+((Ankb[12][0]*Cik[13][0][2])+(
      Ankb[12][1]*Cik[13][1][2])));
    Ankb[14][0] = ((.1862*Onkb[14][2])+((Ankb[13][2]*Cik[14][2][0])+((
      Ankb[13][0]*Cik[14][0][0])+(Ankb[13][1]*Cik[14][1][0]))));
    Ankb[14][1] = ((Ankb[13][2]*Cik[14][2][1])+((Ankb[13][0]*Cik[14][0][1])+(
      Ankb[13][1]*Cik[14][1][1])));
    Ankb[14][2] = (((Ankb[13][2]*Cik[14][2][2])+((Ankb[13][0]*Cik[14][0][2])+(
      Ankb[13][1]*Cik[14][1][2])))-(.1862*Onkb[14][0]));
    AOnkri[15][0] = (Ankb[14][0]+(.2438*Onkb[14][2]));
    AOnkri[15][2] = (Ankb[14][2]-(.2438*Onkb[14][0]));
    Ankb[15][0] = ((AOnkri[15][2]*Cik[15][2][0])+((Ankb[14][1]*Cik[15][1][0])+(
      AOnkri[15][0]*Cik[15][0][0])));
    Ankb[15][1] = ((AOnkri[15][2]*Cik[15][2][1])+((Ankb[14][1]*Cik[15][1][1])+(
      AOnkri[15][0]*Cik[15][0][1])));
    Ankb[15][2] = ((AOnkri[15][2]*Cik[15][2][2])+((Ankb[14][1]*Cik[15][1][2])+(
      AOnkri[15][0]*Cik[15][0][2])));
    Ankb[16][0] = ((Ankb[15][2]*Cik[16][2][0])+((Ankb[15][0]*Cik[16][0][0])+(
      Ankb[15][1]*Cik[16][1][0])));
    Ankb[16][1] = ((Ankb[15][2]*Cik[16][2][1])+((Ankb[15][0]*Cik[16][0][1])+(
      Ankb[15][1]*Cik[16][1][1])));
    Ankb[16][2] = ((Ankb[15][2]*Cik[16][2][2])+((Ankb[15][0]*Cik[16][0][2])+(
      Ankb[15][1]*Cik[16][1][2])));
    Ankb[17][0] = (((.005539*Onkb[17][1])+(.051347*Onkb[17][2]))+((Ankb[16][2]*
      Cik[17][2][0])+((Ankb[16][0]*Cik[17][0][0])+(Ankb[16][1]*Cik[17][1][0]))))
      ;
    Ankb[17][1] = (((.035902*Onkb[17][2])-(.005539*Onkb[17][0]))+((Ankb[16][2]*
      Cik[17][2][1])+((Ankb[16][0]*Cik[17][0][1])+(Ankb[16][1]*Cik[17][1][1]))))
      ;
    Ankb[17][2] = (((Ankb[16][2]*Cik[17][2][2])+((Ankb[16][0]*Cik[17][0][2])+(
      Ankb[16][1]*Cik[17][1][2])))-((.035902*Onkb[17][1])+(.051347*Onkb[17][0]))
      );
    AOnkri[18][0] = (Ankb[17][0]+((.018078*Onkb[17][1])+(.038*Onkb[17][2])));
    AOnkri[18][1] = (Ankb[17][1]+((.098032*Onkb[17][2])-(.018078*Onkb[17][0])));
    AOnkri[18][2] = (Ankb[17][2]-((.038*Onkb[17][0])+(.098032*Onkb[17][1])));
    Ankb[18][0] = ((AOnkri[18][2]*Cik[18][2][0])+((AOnkri[18][0]*Cik[18][0][0])+
      (AOnkri[18][1]*Cik[18][1][0])));
    Ankb[18][1] = ((AOnkri[18][2]*Cik[18][2][1])+((AOnkri[18][0]*Cik[18][0][1])+
      (AOnkri[18][1]*Cik[18][1][1])));
    Ankb[18][2] = ((AOnkri[18][2]*Cik[18][2][2])+((AOnkri[18][0]*Cik[18][0][2])+
      (AOnkri[18][1]*Cik[18][1][2])));
    Ankb[19][0] = ((Ankb[18][2]*Cik[19][2][0])+((Ankb[18][0]*Cik[19][0][0])+(
      Ankb[18][1]*Cik[19][1][0])));
    Ankb[19][1] = ((Ankb[18][2]*Cik[19][2][1])+((Ankb[18][0]*Cik[19][0][1])+(
      Ankb[18][1]*Cik[19][1][1])));
    Ankb[19][2] = ((Ankb[18][2]*Cik[19][2][2])+((Ankb[18][0]*Cik[19][0][2])+(
      Ankb[18][1]*Cik[19][1][2])));
    Ankb[20][0] = (((.005139*Onkb[20][1])-(.0185*Onkb[20][2]))+((Ankb[19][2]*
      Cik[20][2][0])+((Ankb[19][0]*Cik[20][0][0])+(Ankb[19][1]*Cik[20][1][0]))))
      ;
    Ankb[20][1] = (((.026917*Onkb[20][2])-(.005139*Onkb[20][0]))+((Ankb[19][2]*
      Cik[20][2][1])+((Ankb[19][0]*Cik[20][0][1])+(Ankb[19][1]*Cik[20][1][1]))))
      ;
    Ankb[20][2] = (((.0185*Onkb[20][0])-(.026917*Onkb[20][1]))+((Ankb[19][2]*
      Cik[20][2][2])+((Ankb[19][0]*Cik[20][0][2])+(Ankb[19][1]*Cik[20][1][2]))))
      ;
    AOnkri[21][0] = (Ankb[3][0]+((.07*udot[5])-(.0935*udot[4])));
    AOnkri[21][1] = (Ankb[3][1]+(.0935*udot[3]));
    AOnkri[21][2] = (Ankb[3][2]-(.07*udot[3]));
    Ankb[21][0] = ((AOnkri[21][2]*Cik[21][2][0])+((AOnkri[21][0]*Cik[21][0][0])+
      (AOnkri[21][1]*Cik[21][1][0])));
    Ankb[21][1] = ((AOnkri[21][2]*Cik[21][2][1])+((AOnkri[21][0]*Cik[21][0][1])+
      (AOnkri[21][1]*Cik[21][1][1])));
    Ankb[21][2] = ((AOnkri[21][2]*Cik[21][2][2])+((AOnkri[21][0]*Cik[21][0][2])+
      (AOnkri[21][1]*Cik[21][1][2])));
    Ankb[22][0] = ((Ankb[21][2]*Cik[22][2][0])+((Ankb[21][0]*Cik[22][0][0])+(
      Ankb[21][1]*Cik[22][1][0])));
    Ankb[22][1] = ((Ankb[21][2]*Cik[22][2][1])+((Ankb[21][0]*Cik[22][0][1])+(
      Ankb[21][1]*Cik[22][1][1])));
    Ankb[22][2] = ((Ankb[21][2]*Cik[22][2][2])+((Ankb[21][0]*Cik[22][0][2])+(
      Ankb[21][1]*Cik[22][1][2])));
    Ankb[23][0] = ((.1715*Onkb[23][2])+((Ankb[22][2]*Cik[23][2][0])+((
      Ankb[22][0]*Cik[23][0][0])+(Ankb[22][1]*Cik[23][1][0]))));
    Ankb[23][1] = (((Ankb[22][2]*Cik[23][2][1])+((Ankb[22][0]*Cik[23][0][1])+(
      Ankb[22][1]*Cik[23][1][1])))-(.002*Onkb[23][2]));
    Ankb[23][2] = (((.002*Onkb[23][1])-(.1715*Onkb[23][0]))+((Ankb[22][2]*
      Cik[23][2][2])+((Ankb[22][0]*Cik[23][0][2])+(Ankb[22][1]*Cik[23][1][2]))))
      ;
    AOnkri[24][0] = (Ankb[23][0]+(.2294*Onkb[23][2]));
    AOnkri[24][1] = (Ankb[23][1]+(.0033*Onkb[23][2]));
    AOnkri[24][2] = (Ankb[23][2]-((.0033*Onkb[23][1])+(.2294*Onkb[23][0])));
    Ankb[24][0] = ((AOnkri[24][2]*Cik[24][2][0])+((AOnkri[24][0]*Cik[24][0][0])+
      (AOnkri[24][1]*Cik[24][1][0])));
    Ankb[24][1] = ((AOnkri[24][2]*Cik[24][2][1])+((AOnkri[24][0]*Cik[24][0][1])+
      (AOnkri[24][1]*Cik[24][1][1])));
    Ankb[24][2] = ((AOnkri[24][2]*Cik[24][2][2])+((AOnkri[24][0]*Cik[24][0][2])+
      (AOnkri[24][1]*Cik[24][1][2])));
    Ankb[25][0] = ((Ankb[24][2]*Cik[25][2][0])+((Ankb[24][0]*Cik[25][0][0])+(
      Ankb[24][1]*Cik[25][1][0])));
    Ankb[25][1] = ((Ankb[24][2]*Cik[25][2][1])+((Ankb[24][0]*Cik[25][0][1])+(
      Ankb[24][1]*Cik[25][1][1])));
    Ankb[25][2] = ((Ankb[24][2]*Cik[25][2][2])+((Ankb[24][0]*Cik[25][0][2])+(
      Ankb[24][1]*Cik[25][1][2])));
    Ankb[26][0] = ((.1862*Onkb[26][2])+((Ankb[25][2]*Cik[26][2][0])+((
      Ankb[25][0]*Cik[26][0][0])+(Ankb[25][1]*Cik[26][1][0]))));
    Ankb[26][1] = ((Ankb[25][2]*Cik[26][2][1])+((Ankb[25][0]*Cik[26][0][1])+(
      Ankb[25][1]*Cik[26][1][1])));
    Ankb[26][2] = (((Ankb[25][2]*Cik[26][2][2])+((Ankb[25][0]*Cik[26][0][2])+(
      Ankb[25][1]*Cik[26][1][2])))-(.1862*Onkb[26][0]));
    AOnkri[27][0] = (Ankb[26][0]+(.2438*Onkb[26][2]));
    AOnkri[27][2] = (Ankb[26][2]-(.2438*Onkb[26][0]));
    Ankb[27][0] = ((AOnkri[27][2]*Cik[27][2][0])+((Ankb[26][1]*Cik[27][1][0])+(
      AOnkri[27][0]*Cik[27][0][0])));
    Ankb[27][1] = ((AOnkri[27][2]*Cik[27][2][1])+((Ankb[26][1]*Cik[27][1][1])+(
      AOnkri[27][0]*Cik[27][0][1])));
    Ankb[27][2] = ((AOnkri[27][2]*Cik[27][2][2])+((Ankb[26][1]*Cik[27][1][2])+(
      AOnkri[27][0]*Cik[27][0][2])));
    Ankb[28][0] = ((Ankb[27][2]*Cik[28][2][0])+((Ankb[27][0]*Cik[28][0][0])+(
      Ankb[27][1]*Cik[28][1][0])));
    Ankb[28][1] = ((Ankb[27][2]*Cik[28][2][1])+((Ankb[27][0]*Cik[28][0][1])+(
      Ankb[27][1]*Cik[28][1][1])));
    Ankb[28][2] = ((Ankb[27][2]*Cik[28][2][2])+((Ankb[27][0]*Cik[28][0][2])+(
      Ankb[27][1]*Cik[28][1][2])));
    Ankb[29][0] = (((.051347*Onkb[29][2])-(.005539*Onkb[29][1]))+((Ankb[28][2]*
      Cik[29][2][0])+((Ankb[28][0]*Cik[29][0][0])+(Ankb[28][1]*Cik[29][1][0]))))
      ;
    Ankb[29][1] = (((.005539*Onkb[29][0])+(.035902*Onkb[29][2]))+((Ankb[28][2]*
      Cik[29][2][1])+((Ankb[28][0]*Cik[29][0][1])+(Ankb[28][1]*Cik[29][1][1]))))
      ;
    Ankb[29][2] = (((Ankb[28][2]*Cik[29][2][2])+((Ankb[28][0]*Cik[29][0][2])+(
      Ankb[28][1]*Cik[29][1][2])))-((.035902*Onkb[29][1])+(.051347*Onkb[29][0]))
      );
    AOnkri[30][0] = (Ankb[29][0]+((.038*Onkb[29][2])-(.018078*Onkb[29][1])));
    AOnkri[30][1] = (Ankb[29][1]+((.018078*Onkb[29][0])+(.098032*Onkb[29][2])));
    AOnkri[30][2] = (Ankb[29][2]-((.038*Onkb[29][0])+(.098032*Onkb[29][1])));
    Ankb[30][0] = ((AOnkri[30][2]*Cik[30][2][0])+((AOnkri[30][0]*Cik[30][0][0])+
      (AOnkri[30][1]*Cik[30][1][0])));
    Ankb[30][1] = ((AOnkri[30][2]*Cik[30][2][1])+((AOnkri[30][0]*Cik[30][0][1])+
      (AOnkri[30][1]*Cik[30][1][1])));
    Ankb[30][2] = ((AOnkri[30][2]*Cik[30][2][2])+((AOnkri[30][0]*Cik[30][0][2])+
      (AOnkri[30][1]*Cik[30][1][2])));
    Ankb[31][0] = ((Ankb[30][2]*Cik[31][2][0])+((Ankb[30][0]*Cik[31][0][0])+(
      Ankb[30][1]*Cik[31][1][0])));
    Ankb[31][1] = ((Ankb[30][2]*Cik[31][2][1])+((Ankb[30][0]*Cik[31][0][1])+(
      Ankb[30][1]*Cik[31][1][1])));
    Ankb[31][2] = ((Ankb[30][2]*Cik[31][2][2])+((Ankb[30][0]*Cik[31][0][2])+(
      Ankb[30][1]*Cik[31][1][2])));
    Ankb[32][0] = (((Ankb[31][2]*Cik[32][2][0])+((Ankb[31][0]*Cik[32][0][0])+(
      Ankb[31][1]*Cik[32][1][0])))-((.005139*Onkb[32][1])+(.0185*Onkb[32][2])));
    Ankb[32][1] = (((.005139*Onkb[32][0])+(.026917*Onkb[32][2]))+((Ankb[31][2]*
      Cik[32][2][1])+((Ankb[31][0]*Cik[32][0][1])+(Ankb[31][1]*Cik[32][1][1]))))
      ;
    Ankb[32][2] = (((.0185*Onkb[32][0])-(.026917*Onkb[32][1]))+((Ankb[31][2]*
      Cik[32][2][2])+((Ankb[31][0]*Cik[32][0][2])+(Ankb[31][1]*Cik[32][1][2]))))
      ;
    ank[5][0] = ((Ankb[3][2]*Cik[3][0][2])+((Ankb[3][0]*Cik[3][0][0])+(
      Ankb[3][1]*Cik[3][0][1])));
    ank[5][1] = ((Ankb[3][2]*Cik[3][1][2])+((Ankb[3][0]*Cik[3][1][0])+(
      Ankb[3][1]*Cik[3][1][1])));
    ank[5][2] = ((Ankb[3][2]*Cik[3][2][2])+((Ankb[3][0]*Cik[3][2][0])+(
      Ankb[3][1]*Cik[3][2][1])));
    AnkAtk[8][0] = (Ankb[8][0]+Atk[8][0]);
    AnkAtk[8][1] = (Ankb[8][1]+Atk[8][1]);
    AnkAtk[8][2] = (Ankb[8][2]+Atk[8][2]);
    ank[8][0] = ((AnkAtk[8][2]*cnk[8][0][2])+((AnkAtk[8][0]*cnk[8][0][0])+(
      AnkAtk[8][1]*cnk[8][0][1])));
    ank[8][1] = ((AnkAtk[8][2]*cnk[8][1][2])+((AnkAtk[8][0]*cnk[8][1][0])+(
      AnkAtk[8][1]*cnk[8][1][1])));
    ank[8][2] = ((AnkAtk[8][2]*cnk[8][2][2])+((AnkAtk[8][0]*cnk[8][2][0])+(
      AnkAtk[8][1]*cnk[8][2][1])));
    AnkAtk[11][0] = (Ankb[11][0]+Atk[11][0]);
    AnkAtk[11][1] = (Ankb[11][1]+Atk[11][1]);
    AnkAtk[11][2] = (Ankb[11][2]+Atk[11][2]);
    ank[11][0] = ((AnkAtk[11][2]*cnk[11][0][2])+((AnkAtk[11][0]*cnk[11][0][0])+(
      AnkAtk[11][1]*cnk[11][0][1])));
    ank[11][1] = ((AnkAtk[11][2]*cnk[11][1][2])+((AnkAtk[11][0]*cnk[11][1][0])+(
      AnkAtk[11][1]*cnk[11][1][1])));
    ank[11][2] = ((AnkAtk[11][2]*cnk[11][2][2])+((AnkAtk[11][0]*cnk[11][2][0])+(
      AnkAtk[11][1]*cnk[11][2][1])));
    AnkAtk[14][0] = (Ankb[14][0]+Atk[14][0]);
    AnkAtk[14][1] = (Ankb[14][1]+Atk[14][1]);
    AnkAtk[14][2] = (Ankb[14][2]+Atk[14][2]);
    ank[14][0] = ((AnkAtk[14][2]*cnk[14][0][2])+((AnkAtk[14][0]*cnk[14][0][0])+(
      AnkAtk[14][1]*cnk[14][0][1])));
    ank[14][1] = ((AnkAtk[14][2]*cnk[14][1][2])+((AnkAtk[14][0]*cnk[14][1][0])+(
      AnkAtk[14][1]*cnk[14][1][1])));
    ank[14][2] = ((AnkAtk[14][2]*cnk[14][2][2])+((AnkAtk[14][0]*cnk[14][2][0])+(
      AnkAtk[14][1]*cnk[14][2][1])));
    AnkAtk[17][0] = (Ankb[17][0]+Atk[17][0]);
    AnkAtk[17][1] = (Ankb[17][1]+Atk[17][1]);
    AnkAtk[17][2] = (Ankb[17][2]+Atk[17][2]);
    ank[17][0] = ((AnkAtk[17][2]*cnk[17][0][2])+((AnkAtk[17][0]*cnk[17][0][0])+(
      AnkAtk[17][1]*cnk[17][0][1])));
    ank[17][1] = ((AnkAtk[17][2]*cnk[17][1][2])+((AnkAtk[17][0]*cnk[17][1][0])+(
      AnkAtk[17][1]*cnk[17][1][1])));
    ank[17][2] = ((AnkAtk[17][2]*cnk[17][2][2])+((AnkAtk[17][0]*cnk[17][2][0])+(
      AnkAtk[17][1]*cnk[17][2][1])));
    AnkAtk[20][0] = (Ankb[20][0]+Atk[20][0]);
    AnkAtk[20][1] = (Ankb[20][1]+Atk[20][1]);
    AnkAtk[20][2] = (Ankb[20][2]+Atk[20][2]);
    ank[20][0] = ((AnkAtk[20][2]*cnk[20][0][2])+((AnkAtk[20][0]*cnk[20][0][0])+(
      AnkAtk[20][1]*cnk[20][0][1])));
    ank[20][1] = ((AnkAtk[20][2]*cnk[20][1][2])+((AnkAtk[20][0]*cnk[20][1][0])+(
      AnkAtk[20][1]*cnk[20][1][1])));
    ank[20][2] = ((AnkAtk[20][2]*cnk[20][2][2])+((AnkAtk[20][0]*cnk[20][2][0])+(
      AnkAtk[20][1]*cnk[20][2][1])));
    AnkAtk[23][0] = (Ankb[23][0]+Atk[23][0]);
    AnkAtk[23][1] = (Ankb[23][1]+Atk[23][1]);
    AnkAtk[23][2] = (Ankb[23][2]+Atk[23][2]);
    ank[23][0] = ((AnkAtk[23][2]*cnk[23][0][2])+((AnkAtk[23][0]*cnk[23][0][0])+(
      AnkAtk[23][1]*cnk[23][0][1])));
    ank[23][1] = ((AnkAtk[23][2]*cnk[23][1][2])+((AnkAtk[23][0]*cnk[23][1][0])+(
      AnkAtk[23][1]*cnk[23][1][1])));
    ank[23][2] = ((AnkAtk[23][2]*cnk[23][2][2])+((AnkAtk[23][0]*cnk[23][2][0])+(
      AnkAtk[23][1]*cnk[23][2][1])));
    AnkAtk[26][0] = (Ankb[26][0]+Atk[26][0]);
    AnkAtk[26][1] = (Ankb[26][1]+Atk[26][1]);
    AnkAtk[26][2] = (Ankb[26][2]+Atk[26][2]);
    ank[26][0] = ((AnkAtk[26][2]*cnk[26][0][2])+((AnkAtk[26][0]*cnk[26][0][0])+(
      AnkAtk[26][1]*cnk[26][0][1])));
    ank[26][1] = ((AnkAtk[26][2]*cnk[26][1][2])+((AnkAtk[26][0]*cnk[26][1][0])+(
      AnkAtk[26][1]*cnk[26][1][1])));
    ank[26][2] = ((AnkAtk[26][2]*cnk[26][2][2])+((AnkAtk[26][0]*cnk[26][2][0])+(
      AnkAtk[26][1]*cnk[26][2][1])));
    AnkAtk[29][0] = (Ankb[29][0]+Atk[29][0]);
    AnkAtk[29][1] = (Ankb[29][1]+Atk[29][1]);
    AnkAtk[29][2] = (Ankb[29][2]+Atk[29][2]);
    ank[29][0] = ((AnkAtk[29][2]*cnk[29][0][2])+((AnkAtk[29][0]*cnk[29][0][0])+(
      AnkAtk[29][1]*cnk[29][0][1])));
    ank[29][1] = ((AnkAtk[29][2]*cnk[29][1][2])+((AnkAtk[29][0]*cnk[29][1][0])+(
      AnkAtk[29][1]*cnk[29][1][1])));
    ank[29][2] = ((AnkAtk[29][2]*cnk[29][2][2])+((AnkAtk[29][0]*cnk[29][2][0])+(
      AnkAtk[29][1]*cnk[29][2][1])));
    AnkAtk[32][0] = (Ankb[32][0]+Atk[32][0]);
    AnkAtk[32][1] = (Ankb[32][1]+Atk[32][1]);
    AnkAtk[32][2] = (Ankb[32][2]+Atk[32][2]);
    ank[32][0] = ((AnkAtk[32][2]*cnk[32][0][2])+((AnkAtk[32][0]*cnk[32][0][0])+(
      AnkAtk[32][1]*cnk[32][0][1])));
    ank[32][1] = ((AnkAtk[32][2]*cnk[32][1][2])+((AnkAtk[32][0]*cnk[32][1][0])+(
      AnkAtk[32][1]*cnk[32][1][1])));
    ank[32][2] = ((AnkAtk[32][2]*cnk[32][2][2])+((AnkAtk[32][0]*cnk[32][2][0])+(
      AnkAtk[32][1]*cnk[32][2][1])));
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    anb[1][0] = ank[8][0];
    anb[1][1] = ank[8][1];
    anb[1][2] = ank[8][2];
    anb[2][0] = ank[11][0];
    anb[2][1] = ank[11][1];
    anb[2][2] = ank[11][2];
    anb[3][0] = ank[14][0];
    anb[3][1] = ank[14][1];
    anb[3][2] = ank[14][2];
    anb[4][0] = ank[17][0];
    anb[4][1] = ank[17][1];
    anb[4][2] = ank[17][2];
    anb[5][0] = ank[20][0];
    anb[5][1] = ank[20][1];
    anb[5][2] = ank[20][2];
    anb[6][0] = ank[23][0];
    anb[6][1] = ank[23][1];
    anb[6][2] = ank[23][2];
    anb[7][0] = ank[26][0];
    anb[7][1] = ank[26][1];
    anb[7][2] = ank[26][2];
    anb[8][0] = ank[29][0];
    anb[8][1] = ank[29][1];
    anb[8][2] = ank[29][2];
    anb[9][0] = ank[32][0];
    anb[9][1] = ank[32][1];
    anb[9][2] = ank[32][2];
/*
Compute constraint acceleration errors
*/
    roustate = 3;
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  696 adds/subtracts/negates
                    747 multiplies
                      0 divides
                    465 assignments
*/
}

void sdmassmat(double mmat[33][33])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 33; i++) {
        for (j = i; j <= 32; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void sdfrcmat(double fmat[33])
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 33; i++) {
        fmat[i] = fs0[i];
    }
}

void sdpseudo(double lqout[1],
    double luout[1])
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsqdot(double lqdout[1])
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsudot(double ludout[1])
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdperr(double errs[33])
{
/*
Return position constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(26,23);
        return;
    }
    if (pres[0]  !=  0.) {
        perr[0] = (q[0]-upos[0]);
    } else {
        perr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        perr[1] = (q[1]-upos[1]);
    } else {
        perr[1] = 0.;
    }
    if (pres[2]  !=  0.) {
        perr[2] = (q[2]-upos[2]);
    } else {
        perr[2] = 0.;
    }
    if (pres[3]  !=  0.) {
        perr[3] = (q[3]-upos[3]);
    } else {
        perr[3] = 0.;
    }
    if (pres[4]  !=  0.) {
        perr[4] = (q[4]-upos[4]);
    } else {
        perr[4] = 0.;
    }
    if (pres[5]  !=  0.) {
        perr[5] = (q[5]-upos[5]);
    } else {
        perr[5] = 0.;
    }
    if (pres[6]  !=  0.) {
        perr[6] = (q[6]-upos[6]);
    } else {
        perr[6] = 0.;
    }
    if (pres[7]  !=  0.) {
        perr[7] = (q[7]-upos[7]);
    } else {
        perr[7] = 0.;
    }
    if (pres[8]  !=  0.) {
        perr[8] = (q[8]-upos[8]);
    } else {
        perr[8] = 0.;
    }
    if (pres[9]  !=  0.) {
        perr[9] = (q[9]-upos[9]);
    } else {
        perr[9] = 0.;
    }
    if (pres[10]  !=  0.) {
        perr[10] = (q[10]-upos[10]);
    } else {
        perr[10] = 0.;
    }
    if (pres[11]  !=  0.) {
        perr[11] = (q[11]-upos[11]);
    } else {
        perr[11] = 0.;
    }
    if (pres[12]  !=  0.) {
        perr[12] = (q[12]-upos[12]);
    } else {
        perr[12] = 0.;
    }
    if (pres[13]  !=  0.) {
        perr[13] = (q[13]-upos[13]);
    } else {
        perr[13] = 0.;
    }
    if (pres[14]  !=  0.) {
        perr[14] = (q[14]-upos[14]);
    } else {
        perr[14] = 0.;
    }
    if (pres[15]  !=  0.) {
        perr[15] = (q[15]-upos[15]);
    } else {
        perr[15] = 0.;
    }
    if (pres[16]  !=  0.) {
        perr[16] = (q[16]-upos[16]);
    } else {
        perr[16] = 0.;
    }
    if (pres[17]  !=  0.) {
        perr[17] = (q[17]-upos[17]);
    } else {
        perr[17] = 0.;
    }
    if (pres[18]  !=  0.) {
        perr[18] = (q[18]-upos[18]);
    } else {
        perr[18] = 0.;
    }
    if (pres[19]  !=  0.) {
        perr[19] = (q[19]-upos[19]);
    } else {
        perr[19] = 0.;
    }
    if (pres[20]  !=  0.) {
        perr[20] = (q[20]-upos[20]);
    } else {
        perr[20] = 0.;
    }
    if (pres[21]  !=  0.) {
        perr[21] = (q[21]-upos[21]);
    } else {
        perr[21] = 0.;
    }
    if (pres[22]  !=  0.) {
        perr[22] = (q[22]-upos[22]);
    } else {
        perr[22] = 0.;
    }
    if (pres[23]  !=  0.) {
        perr[23] = (q[23]-upos[23]);
    } else {
        perr[23] = 0.;
    }
    if (pres[24]  !=  0.) {
        perr[24] = (q[24]-upos[24]);
    } else {
        perr[24] = 0.;
    }
    if (pres[25]  !=  0.) {
        perr[25] = (q[25]-upos[25]);
    } else {
        perr[25] = 0.;
    }
    if (pres[26]  !=  0.) {
        perr[26] = (q[26]-upos[26]);
    } else {
        perr[26] = 0.;
    }
    if (pres[27]  !=  0.) {
        perr[27] = (q[27]-upos[27]);
    } else {
        perr[27] = 0.;
    }
    if (pres[28]  !=  0.) {
        perr[28] = (q[28]-upos[28]);
    } else {
        perr[28] = 0.;
    }
    if (pres[29]  !=  0.) {
        perr[29] = (q[29]-upos[29]);
    } else {
        perr[29] = 0.;
    }
    if (pres[30]  !=  0.) {
        perr[30] = (q[30]-upos[30]);
    } else {
        perr[30] = 0.;
    }
    if (pres[31]  !=  0.) {
        perr[31] = (q[31]-upos[31]);
    } else {
        perr[31] = 0.;
    }
    if (pres[32]  !=  0.) {
        perr[32] = (q[32]-upos[32]);
    } else {
        perr[32] = 0.;
    }
    errs[0] = perr[0];
    errs[1] = perr[1];
    errs[2] = perr[2];
    errs[3] = perr[3];
    errs[4] = perr[4];
    errs[5] = perr[5];
    errs[6] = perr[6];
    errs[7] = perr[7];
    errs[8] = perr[8];
    errs[9] = perr[9];
    errs[10] = perr[10];
    errs[11] = perr[11];
    errs[12] = perr[12];
    errs[13] = perr[13];
    errs[14] = perr[14];
    errs[15] = perr[15];
    errs[16] = perr[16];
    errs[17] = perr[17];
    errs[18] = perr[18];
    errs[19] = perr[19];
    errs[20] = perr[20];
    errs[21] = perr[21];
    errs[22] = perr[22];
    errs[23] = perr[23];
    errs[24] = perr[24];
    errs[25] = perr[25];
    errs[26] = perr[26];
    errs[27] = perr[27];
    errs[28] = perr[28];
    errs[29] = perr[29];
    errs[30] = perr[30];
    errs[31] = perr[31];
    errs[32] = perr[32];
}

void sdverr(double errs[33])
{
/*
Return velocity constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(27,23);
        return;
    }
    if (pres[0]  !=  0.) {
        verr[0] = (u[0]-uvel[0]);
    } else {
        verr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        verr[1] = (u[1]-uvel[1]);
    } else {
        verr[1] = 0.;
    }
    if (pres[2]  !=  0.) {
        verr[2] = (u[2]-uvel[2]);
    } else {
        verr[2] = 0.;
    }
    if (pres[3]  !=  0.) {
        verr[3] = (u[3]-uvel[3]);
    } else {
        verr[3] = 0.;
    }
    if (pres[4]  !=  0.) {
        verr[4] = (u[4]-uvel[4]);
    } else {
        verr[4] = 0.;
    }
    if (pres[5]  !=  0.) {
        verr[5] = (u[5]-uvel[5]);
    } else {
        verr[5] = 0.;
    }
    if (pres[6]  !=  0.) {
        verr[6] = (u[6]-uvel[6]);
    } else {
        verr[6] = 0.;
    }
    if (pres[7]  !=  0.) {
        verr[7] = (u[7]-uvel[7]);
    } else {
        verr[7] = 0.;
    }
    if (pres[8]  !=  0.) {
        verr[8] = (u[8]-uvel[8]);
    } else {
        verr[8] = 0.;
    }
    if (pres[9]  !=  0.) {
        verr[9] = (u[9]-uvel[9]);
    } else {
        verr[9] = 0.;
    }
    if (pres[10]  !=  0.) {
        verr[10] = (u[10]-uvel[10]);
    } else {
        verr[10] = 0.;
    }
    if (pres[11]  !=  0.) {
        verr[11] = (u[11]-uvel[11]);
    } else {
        verr[11] = 0.;
    }
    if (pres[12]  !=  0.) {
        verr[12] = (u[12]-uvel[12]);
    } else {
        verr[12] = 0.;
    }
    if (pres[13]  !=  0.) {
        verr[13] = (u[13]-uvel[13]);
    } else {
        verr[13] = 0.;
    }
    if (pres[14]  !=  0.) {
        verr[14] = (u[14]-uvel[14]);
    } else {
        verr[14] = 0.;
    }
    if (pres[15]  !=  0.) {
        verr[15] = (u[15]-uvel[15]);
    } else {
        verr[15] = 0.;
    }
    if (pres[16]  !=  0.) {
        verr[16] = (u[16]-uvel[16]);
    } else {
        verr[16] = 0.;
    }
    if (pres[17]  !=  0.) {
        verr[17] = (u[17]-uvel[17]);
    } else {
        verr[17] = 0.;
    }
    if (pres[18]  !=  0.) {
        verr[18] = (u[18]-uvel[18]);
    } else {
        verr[18] = 0.;
    }
    if (pres[19]  !=  0.) {
        verr[19] = (u[19]-uvel[19]);
    } else {
        verr[19] = 0.;
    }
    if (pres[20]  !=  0.) {
        verr[20] = (u[20]-uvel[20]);
    } else {
        verr[20] = 0.;
    }
    if (pres[21]  !=  0.) {
        verr[21] = (u[21]-uvel[21]);
    } else {
        verr[21] = 0.;
    }
    if (pres[22]  !=  0.) {
        verr[22] = (u[22]-uvel[22]);
    } else {
        verr[22] = 0.;
    }
    if (pres[23]  !=  0.) {
        verr[23] = (u[23]-uvel[23]);
    } else {
        verr[23] = 0.;
    }
    if (pres[24]  !=  0.) {
        verr[24] = (u[24]-uvel[24]);
    } else {
        verr[24] = 0.;
    }
    if (pres[25]  !=  0.) {
        verr[25] = (u[25]-uvel[25]);
    } else {
        verr[25] = 0.;
    }
    if (pres[26]  !=  0.) {
        verr[26] = (u[26]-uvel[26]);
    } else {
        verr[26] = 0.;
    }
    if (pres[27]  !=  0.) {
        verr[27] = (u[27]-uvel[27]);
    } else {
        verr[27] = 0.;
    }
    if (pres[28]  !=  0.) {
        verr[28] = (u[28]-uvel[28]);
    } else {
        verr[28] = 0.;
    }
    if (pres[29]  !=  0.) {
        verr[29] = (u[29]-uvel[29]);
    } else {
        verr[29] = 0.;
    }
    if (pres[30]  !=  0.) {
        verr[30] = (u[30]-uvel[30]);
    } else {
        verr[30] = 0.;
    }
    if (pres[31]  !=  0.) {
        verr[31] = (u[31]-uvel[31]);
    } else {
        verr[31] = 0.;
    }
    if (pres[32]  !=  0.) {
        verr[32] = (u[32]-uvel[32]);
    } else {
        verr[32] = 0.;
    }
    errs[0] = verr[0];
    errs[1] = verr[1];
    errs[2] = verr[2];
    errs[3] = verr[3];
    errs[4] = verr[4];
    errs[5] = verr[5];
    errs[6] = verr[6];
    errs[7] = verr[7];
    errs[8] = verr[8];
    errs[9] = verr[9];
    errs[10] = verr[10];
    errs[11] = verr[11];
    errs[12] = verr[12];
    errs[13] = verr[13];
    errs[14] = verr[14];
    errs[15] = verr[15];
    errs[16] = verr[16];
    errs[17] = verr[17];
    errs[18] = verr[18];
    errs[19] = verr[19];
    errs[20] = verr[20];
    errs[21] = verr[21];
    errs[22] = verr[22];
    errs[23] = verr[23];
    errs[24] = verr[24];
    errs[25] = verr[25];
    errs[26] = verr[26];
    errs[27] = verr[27];
    errs[28] = verr[28];
    errs[29] = verr[29];
    errs[30] = verr[30];
    errs[31] = verr[31];
    errs[32] = verr[32];
}

void sdaerr(double errs[33])
{
/*
Return acceleration constraint errors.

*/

    if (roustate != 3) {
        sdseterr(35,24);
        return;
    }
    if (pres[0]  !=  0.) {
        aerr[0] = (udot[0]-uacc[0]);
    } else {
        aerr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        aerr[1] = (udot[1]-uacc[1]);
    } else {
        aerr[1] = 0.;
    }
    if (pres[2]  !=  0.) {
        aerr[2] = (udot[2]-uacc[2]);
    } else {
        aerr[2] = 0.;
    }
    if (pres[3]  !=  0.) {
        aerr[3] = (udot[3]-uacc[3]);
    } else {
        aerr[3] = 0.;
    }
    if (pres[4]  !=  0.) {
        aerr[4] = (udot[4]-uacc[4]);
    } else {
        aerr[4] = 0.;
    }
    if (pres[5]  !=  0.) {
        aerr[5] = (udot[5]-uacc[5]);
    } else {
        aerr[5] = 0.;
    }
    if (pres[6]  !=  0.) {
        aerr[6] = (udot[6]-uacc[6]);
    } else {
        aerr[6] = 0.;
    }
    if (pres[7]  !=  0.) {
        aerr[7] = (udot[7]-uacc[7]);
    } else {
        aerr[7] = 0.;
    }
    if (pres[8]  !=  0.) {
        aerr[8] = (udot[8]-uacc[8]);
    } else {
        aerr[8] = 0.;
    }
    if (pres[9]  !=  0.) {
        aerr[9] = (udot[9]-uacc[9]);
    } else {
        aerr[9] = 0.;
    }
    if (pres[10]  !=  0.) {
        aerr[10] = (udot[10]-uacc[10]);
    } else {
        aerr[10] = 0.;
    }
    if (pres[11]  !=  0.) {
        aerr[11] = (udot[11]-uacc[11]);
    } else {
        aerr[11] = 0.;
    }
    if (pres[12]  !=  0.) {
        aerr[12] = (udot[12]-uacc[12]);
    } else {
        aerr[12] = 0.;
    }
    if (pres[13]  !=  0.) {
        aerr[13] = (udot[13]-uacc[13]);
    } else {
        aerr[13] = 0.;
    }
    if (pres[14]  !=  0.) {
        aerr[14] = (udot[14]-uacc[14]);
    } else {
        aerr[14] = 0.;
    }
    if (pres[15]  !=  0.) {
        aerr[15] = (udot[15]-uacc[15]);
    } else {
        aerr[15] = 0.;
    }
    if (pres[16]  !=  0.) {
        aerr[16] = (udot[16]-uacc[16]);
    } else {
        aerr[16] = 0.;
    }
    if (pres[17]  !=  0.) {
        aerr[17] = (udot[17]-uacc[17]);
    } else {
        aerr[17] = 0.;
    }
    if (pres[18]  !=  0.) {
        aerr[18] = (udot[18]-uacc[18]);
    } else {
        aerr[18] = 0.;
    }
    if (pres[19]  !=  0.) {
        aerr[19] = (udot[19]-uacc[19]);
    } else {
        aerr[19] = 0.;
    }
    if (pres[20]  !=  0.) {
        aerr[20] = (udot[20]-uacc[20]);
    } else {
        aerr[20] = 0.;
    }
    if (pres[21]  !=  0.) {
        aerr[21] = (udot[21]-uacc[21]);
    } else {
        aerr[21] = 0.;
    }
    if (pres[22]  !=  0.) {
        aerr[22] = (udot[22]-uacc[22]);
    } else {
        aerr[22] = 0.;
    }
    if (pres[23]  !=  0.) {
        aerr[23] = (udot[23]-uacc[23]);
    } else {
        aerr[23] = 0.;
    }
    if (pres[24]  !=  0.) {
        aerr[24] = (udot[24]-uacc[24]);
    } else {
        aerr[24] = 0.;
    }
    if (pres[25]  !=  0.) {
        aerr[25] = (udot[25]-uacc[25]);
    } else {
        aerr[25] = 0.;
    }
    if (pres[26]  !=  0.) {
        aerr[26] = (udot[26]-uacc[26]);
    } else {
        aerr[26] = 0.;
    }
    if (pres[27]  !=  0.) {
        aerr[27] = (udot[27]-uacc[27]);
    } else {
        aerr[27] = 0.;
    }
    if (pres[28]  !=  0.) {
        aerr[28] = (udot[28]-uacc[28]);
    } else {
        aerr[28] = 0.;
    }
    if (pres[29]  !=  0.) {
        aerr[29] = (udot[29]-uacc[29]);
    } else {
        aerr[29] = 0.;
    }
    if (pres[30]  !=  0.) {
        aerr[30] = (udot[30]-uacc[30]);
    } else {
        aerr[30] = 0.;
    }
    if (pres[31]  !=  0.) {
        aerr[31] = (udot[31]-uacc[31]);
    } else {
        aerr[31] = 0.;
    }
    if (pres[32]  !=  0.) {
        aerr[32] = (udot[32]-uacc[32]);
    } else {
        aerr[32] = 0.;
    }
    errs[0] = aerr[0];
    errs[1] = aerr[1];
    errs[2] = aerr[2];
    errs[3] = aerr[3];
    errs[4] = aerr[4];
    errs[5] = aerr[5];
    errs[6] = aerr[6];
    errs[7] = aerr[7];
    errs[8] = aerr[8];
    errs[9] = aerr[9];
    errs[10] = aerr[10];
    errs[11] = aerr[11];
    errs[12] = aerr[12];
    errs[13] = aerr[13];
    errs[14] = aerr[14];
    errs[15] = aerr[15];
    errs[16] = aerr[16];
    errs[17] = aerr[17];
    errs[18] = aerr[18];
    errs[19] = aerr[19];
    errs[20] = aerr[20];
    errs[21] = aerr[21];
    errs[22] = aerr[22];
    errs[23] = aerr[23];
    errs[24] = aerr[24];
    errs[25] = aerr[25];
    errs[26] = aerr[26];
    errs[27] = aerr[27];
    errs[28] = aerr[28];
    errs[29] = aerr[29];
    errs[30] = aerr[30];
    errs[31] = aerr[31];
    errs[32] = aerr[32];
}
int 
sdchkbnum(int routine,
    int bnum)
{

    if ((bnum < -1) || (bnum > 9)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(int routine,
    int jnum)
{

    if ((jnum < 0) || (jnum > 9)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(int routine,
    int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        sdseterr(routine,21);
        return 1;
    }
    return 0;
}
int 
sdchkjaxis(int routine,
    int jnum,
    int axnum)
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
sdchkjpin(int routine,
    int jnum,
    int pinno)
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
int 
sdindx(int joint,
    int axis)
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

void sdpresacc(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(13,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(13,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uacc[sdindx(joint,axis)] = prval;
    }
}

void sdpresvel(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(14,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(14,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uvel[sdindx(joint,axis)] = prval;
    }
}

void sdprespos(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(15,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(15,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        upos[sdindx(joint,axis)] = prval;
    }
}

void sdgetht(int joint,
    int axis,
    double *torque)
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

void sdhinget(int joint,
    int axis,
    double torque)
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

void sdpointf(int body,
    double point[3],
    double force[3])
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

void sdbodyt(int body,
    double torque[3])
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

void sddoww(int routine)
{
    double pp[33][33],dpp[33][33];
    int i,j,c;
    double sum;
    double dfk[10][3],dtk[10][3],dtau[33],dltci[1][3],dltc[1][3],dlfci[1][3],
      dlfc[1][3];
    double dTinb[1][3],dToutb[1][3],dltaufi[1][3],dltaufo[1][3],dltauti[1][3],
      dltauto[1][3];
    double dfs[33],row[33],dinvrow[33];

    roustate = 2;
    if (wwflg == 0) {
/*
Compute constraint effects
*/
        sddovpk();
        sddommldu(routine);
/*
Constraint 0 (prescribed motion)
*/
        if (pres[0]  !=  0.) {
            dtau[0] = 1.;
        } else {
            dtau[0] = 0.;
        }
        dfs[0] = dtau[0];
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[0][i] = row[i];
            dpp[i][0] = dinvrow[i];
        }
        wmap[0] = 0;
/*
Constraint 1 (prescribed motion)
*/
        if (pres[1]  !=  0.) {
            dtau[1] = 1.;
        } else {
            dtau[1] = 0.;
        }
        dfs[1] = dtau[1];
        dfs[0] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[1][i] = row[i];
            dpp[i][1] = dinvrow[i];
        }
        wmap[1] = 1;
/*
Constraint 2 (prescribed motion)
*/
        if (pres[2]  !=  0.) {
            dtau[2] = 1.;
        } else {
            dtau[2] = 0.;
        }
        dfs[2] = dtau[2];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[2][i] = row[i];
            dpp[i][2] = dinvrow[i];
        }
        wmap[2] = 2;
/*
Constraint 3 (prescribed motion)
*/
        if (pres[3]  !=  0.) {
            dtau[3] = 1.;
        } else {
            dtau[3] = 0.;
        }
        dfs[3] = dtau[3];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[3][i] = row[i];
            dpp[i][3] = dinvrow[i];
        }
        wmap[3] = 3;
/*
Constraint 4 (prescribed motion)
*/
        if (pres[4]  !=  0.) {
            dtau[4] = 1.;
        } else {
            dtau[4] = 0.;
        }
        dfs[4] = dtau[4];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[4][i] = row[i];
            dpp[i][4] = dinvrow[i];
        }
        wmap[4] = 4;
/*
Constraint 5 (prescribed motion)
*/
        if (pres[5]  !=  0.) {
            dtau[5] = 1.;
        } else {
            dtau[5] = 0.;
        }
        dfs[5] = dtau[5];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[5][i] = row[i];
            dpp[i][5] = dinvrow[i];
        }
        wmap[5] = 5;
/*
Constraint 6 (prescribed motion)
*/
        if (pres[6]  !=  0.) {
            dtau[6] = 1.;
        } else {
            dtau[6] = 0.;
        }
        dfs[6] = dtau[6];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[6][i] = row[i];
            dpp[i][6] = dinvrow[i];
        }
        wmap[6] = 6;
/*
Constraint 7 (prescribed motion)
*/
        if (pres[7]  !=  0.) {
            dtau[7] = 1.;
        } else {
            dtau[7] = 0.;
        }
        dfs[7] = dtau[7];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[7][i] = row[i];
            dpp[i][7] = dinvrow[i];
        }
        wmap[7] = 7;
/*
Constraint 8 (prescribed motion)
*/
        if (pres[8]  !=  0.) {
            dtau[8] = 1.;
        } else {
            dtau[8] = 0.;
        }
        dfs[8] = dtau[8];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[8][i] = row[i];
            dpp[i][8] = dinvrow[i];
        }
        wmap[8] = 8;
/*
Constraint 9 (prescribed motion)
*/
        if (pres[9]  !=  0.) {
            dtau[9] = 1.;
        } else {
            dtau[9] = 0.;
        }
        dfs[9] = dtau[9];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[9][i] = row[i];
            dpp[i][9] = dinvrow[i];
        }
        wmap[9] = 9;
/*
Constraint 10 (prescribed motion)
*/
        if (pres[10]  !=  0.) {
            dtau[10] = 1.;
        } else {
            dtau[10] = 0.;
        }
        dfs[10] = dtau[10];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[10][i] = row[i];
            dpp[i][10] = dinvrow[i];
        }
        wmap[10] = 10;
/*
Constraint 11 (prescribed motion)
*/
        if (pres[11]  !=  0.) {
            dtau[11] = 1.;
        } else {
            dtau[11] = 0.;
        }
        dfs[11] = dtau[11];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[11][i] = row[i];
            dpp[i][11] = dinvrow[i];
        }
        wmap[11] = 11;
/*
Constraint 12 (prescribed motion)
*/
        if (pres[12]  !=  0.) {
            dtau[12] = 1.;
        } else {
            dtau[12] = 0.;
        }
        dfs[12] = dtau[12];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[12][i] = row[i];
            dpp[i][12] = dinvrow[i];
        }
        wmap[12] = 12;
/*
Constraint 13 (prescribed motion)
*/
        if (pres[13]  !=  0.) {
            dtau[13] = 1.;
        } else {
            dtau[13] = 0.;
        }
        dfs[13] = dtau[13];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[13][i] = row[i];
            dpp[i][13] = dinvrow[i];
        }
        wmap[13] = 13;
/*
Constraint 14 (prescribed motion)
*/
        if (pres[14]  !=  0.) {
            dtau[14] = 1.;
        } else {
            dtau[14] = 0.;
        }
        dfs[14] = dtau[14];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[14][i] = row[i];
            dpp[i][14] = dinvrow[i];
        }
        wmap[14] = 14;
/*
Constraint 15 (prescribed motion)
*/
        if (pres[15]  !=  0.) {
            dtau[15] = 1.;
        } else {
            dtau[15] = 0.;
        }
        dfs[15] = dtau[15];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[15][i] = row[i];
            dpp[i][15] = dinvrow[i];
        }
        wmap[15] = 15;
/*
Constraint 16 (prescribed motion)
*/
        if (pres[16]  !=  0.) {
            dtau[16] = 1.;
        } else {
            dtau[16] = 0.;
        }
        dfs[16] = dtau[16];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[16][i] = row[i];
            dpp[i][16] = dinvrow[i];
        }
        wmap[16] = 16;
/*
Constraint 17 (prescribed motion)
*/
        if (pres[17]  !=  0.) {
            dtau[17] = 1.;
        } else {
            dtau[17] = 0.;
        }
        dfs[17] = dtau[17];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[17][i] = row[i];
            dpp[i][17] = dinvrow[i];
        }
        wmap[17] = 17;
/*
Constraint 18 (prescribed motion)
*/
        if (pres[18]  !=  0.) {
            dtau[18] = 1.;
        } else {
            dtau[18] = 0.;
        }
        dfs[18] = dtau[18];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[18][i] = row[i];
            dpp[i][18] = dinvrow[i];
        }
        wmap[18] = 18;
/*
Constraint 19 (prescribed motion)
*/
        if (pres[19]  !=  0.) {
            dtau[19] = 1.;
        } else {
            dtau[19] = 0.;
        }
        dfs[19] = dtau[19];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[19][i] = row[i];
            dpp[i][19] = dinvrow[i];
        }
        wmap[19] = 19;
/*
Constraint 20 (prescribed motion)
*/
        if (pres[20]  !=  0.) {
            dtau[20] = 1.;
        } else {
            dtau[20] = 0.;
        }
        dfs[20] = dtau[20];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[20][i] = row[i];
            dpp[i][20] = dinvrow[i];
        }
        wmap[20] = 20;
/*
Constraint 21 (prescribed motion)
*/
        if (pres[21]  !=  0.) {
            dtau[21] = 1.;
        } else {
            dtau[21] = 0.;
        }
        dfs[21] = dtau[21];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[21][i] = row[i];
            dpp[i][21] = dinvrow[i];
        }
        wmap[21] = 21;
/*
Constraint 22 (prescribed motion)
*/
        if (pres[22]  !=  0.) {
            dtau[22] = 1.;
        } else {
            dtau[22] = 0.;
        }
        dfs[22] = dtau[22];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[22][i] = row[i];
            dpp[i][22] = dinvrow[i];
        }
        wmap[22] = 22;
/*
Constraint 23 (prescribed motion)
*/
        if (pres[23]  !=  0.) {
            dtau[23] = 1.;
        } else {
            dtau[23] = 0.;
        }
        dfs[23] = dtau[23];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[23][i] = row[i];
            dpp[i][23] = dinvrow[i];
        }
        wmap[23] = 23;
/*
Constraint 24 (prescribed motion)
*/
        if (pres[24]  !=  0.) {
            dtau[24] = 1.;
        } else {
            dtau[24] = 0.;
        }
        dfs[24] = dtau[24];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[24][i] = row[i];
            dpp[i][24] = dinvrow[i];
        }
        wmap[24] = 24;
/*
Constraint 25 (prescribed motion)
*/
        if (pres[25]  !=  0.) {
            dtau[25] = 1.;
        } else {
            dtau[25] = 0.;
        }
        dfs[25] = dtau[25];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[25][i] = row[i];
            dpp[i][25] = dinvrow[i];
        }
        wmap[25] = 25;
/*
Constraint 26 (prescribed motion)
*/
        if (pres[26]  !=  0.) {
            dtau[26] = 1.;
        } else {
            dtau[26] = 0.;
        }
        dfs[26] = dtau[26];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[26][i] = row[i];
            dpp[i][26] = dinvrow[i];
        }
        wmap[26] = 26;
/*
Constraint 27 (prescribed motion)
*/
        if (pres[27]  !=  0.) {
            dtau[27] = 1.;
        } else {
            dtau[27] = 0.;
        }
        dfs[27] = dtau[27];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[27][i] = row[i];
            dpp[i][27] = dinvrow[i];
        }
        wmap[27] = 27;
/*
Constraint 28 (prescribed motion)
*/
        if (pres[28]  !=  0.) {
            dtau[28] = 1.;
        } else {
            dtau[28] = 0.;
        }
        dfs[28] = dtau[28];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[28][i] = row[i];
            dpp[i][28] = dinvrow[i];
        }
        wmap[28] = 28;
/*
Constraint 29 (prescribed motion)
*/
        if (pres[29]  !=  0.) {
            dtau[29] = 1.;
        } else {
            dtau[29] = 0.;
        }
        dfs[29] = dtau[29];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[29][i] = row[i];
            dpp[i][29] = dinvrow[i];
        }
        wmap[29] = 29;
/*
Constraint 30 (prescribed motion)
*/
        if (pres[30]  !=  0.) {
            dtau[30] = 1.;
        } else {
            dtau[30] = 0.;
        }
        dfs[30] = dtau[30];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[31] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[30][i] = row[i];
            dpp[i][30] = dinvrow[i];
        }
        wmap[30] = 30;
/*
Constraint 31 (prescribed motion)
*/
        if (pres[31]  !=  0.) {
            dtau[31] = 1.;
        } else {
            dtau[31] = 0.;
        }
        dfs[31] = dtau[31];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[32] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[31][i] = row[i];
            dpp[i][31] = dinvrow[i];
        }
        wmap[31] = 31;
/*
Constraint 32 (prescribed motion)
*/
        if (pres[32]  !=  0.) {
            dtau[32] = 1.;
        } else {
            dtau[32] = 0.;
        }
        dfs[32] = dtau[32];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        dfs[7] = 0.;
        dfs[8] = 0.;
        dfs[9] = 0.;
        dfs[10] = 0.;
        dfs[11] = 0.;
        dfs[12] = 0.;
        dfs[13] = 0.;
        dfs[14] = 0.;
        dfs[15] = 0.;
        dfs[16] = 0.;
        dfs[17] = 0.;
        dfs[18] = 0.;
        dfs[19] = 0.;
        dfs[20] = 0.;
        dfs[21] = 0.;
        dfs[22] = 0.;
        dfs[23] = 0.;
        dfs[24] = 0.;
        dfs[25] = 0.;
        dfs[26] = 0.;
        dfs[27] = 0.;
        dfs[28] = 0.;
        dfs[29] = 0.;
        dfs[30] = 0.;
        dfs[31] = 0.;
        sdldubsl(33,33,mmap,mlo,dfs,row);
        sdldubsd(33,33,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 32; i++) {
            pp[32][i] = row[i];
            dpp[i][32] = dinvrow[i];
        }
        wmap[32] = 32;
/*
Produce constraint coefficient matrix WW
*/
        for (c = 0; c <= 32; c++) {
            for (i = c; i <= 32; i++) {
                sum = 0.;
                for (j = 0; j <= 32; j++) {
                    sum = sum+pp[wmap[c]][j]*dpp[j][wmap[i]];
                }
                ww[wmap[c]][wmap[i]] = sum;
                ww[wmap[i]][wmap[c]] = sum;
            }
        }
/*
Form QR decomposition of WW
*/
        sdqrdcomp(33,33,33,33,wmap,wmap,ww,qraux,jpvt);
        wwflg = 1;
    }
/*
 Used 0.22 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 18513 adds/subtracts/negates
                   18513 multiplies
                      0 divides
                   23529 assignments
*/
}

void sdxudot0(int routine,
    double oudot0[33])
{
/*
Compute unconstrained equations
*/
    int i;

    sdlhs(routine);
/*
Solve equations ignoring constraints
*/
    sdfs0();
    sdldubslv(33,33,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 32; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdudot0(double oudot0[33])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

void sdsetudot(double iudot[33])
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 32; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

void sdxudotm(int routine,
    double imult[33],
    double oudotm[33])
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    sdmfrc(imult);
    sdfsmult();
    sdldubslv(33,33,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 32; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     33 assignments
*/
}

void sdudotm(double imult[33],
    double oudotm[33])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

void sdderiv(double oqdot[34],
    double oudot[33])
{
/*
This is the derivative section for a 10-body ground-based
system with 33 hinge degree(s) of freedom.
33 of the degrees of freedom may follow prescribed motion.
There are 33 constraints.
*/
    double workr[33],bb[33],b0[33],v0[33],p0[33];
    int iwork[33];
    int i,j;
    double udot0[33],udot1[33];

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
    wsiz = 33;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    sdaerr(b0);
    if (stabvel  !=  0.) {
        sdverr(v0);
    }
    if (stabpos  !=  0.) {
        sdperr(p0);
    }
/*
Stabilize constraints using Baumgarte's method
*/
    for (i = 0; i <= 32; i++) {
        bb[i] = -b0[i];
    }
    if (stabvel  !=  0.) {
        for (i = 0; i <= 32; i++) {
            bb[i] = bb[i]-stabvel*v0[i];
        }
    }
    if (stabpos  !=  0.) {
        for (i = 0; i <= 32; i++) {
            bb[i] = bb[i]-stabpos*p0[i];
        }
    }
/*
Compute and decompose constraint matrix WW
*/
    sddoww(17);
/*
Numerically solve for constraint multipliers
*/
    sdqrbslv(33,33,33,33,wmap,wmap,1e-13,workr,iwork,ww,qraux,jpvt,bb,mult,&
      wrank);
    for (i = 0; i <= 32; i++) {
        multmap[i] = 0;
    }
    for (i = 0; i < wrank; i++) {
        multmap[jpvt[i]] = 1;
    }
    j = 0;
    for (i = 0; i <= 32; i++) {
        if (multmap[i] != 0) {
            multmap[j] = wmap[i];
            j = j+1;
        }
    }
/*
Compute final udots
*/
    sdxudotm(17,mult,udot1);
    for (i = 0; i <= 32; i++) {
        udot[i] = udot0[i]+udot1[i];
    }
    sdrhs();
    for (i = 0; i <= 33; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 32; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  132 adds/subtracts/negates
                     66 multiplies
                      0 divides
                    199 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void sdresid(double eqdot[34],
    double eudot[33],
    double emults[33],
    double resid[100])
{
    int i;
    double uderrs[33],p0[33];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 34; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 33; i++) {
        resid[34+i] = uderrs[i];
    }
    sdverr(&resid[67]);
    if (stabpos  !=  0.) {
        sdperr(p0);
        for (i = 0; i < 33; i++) {
            resid[67+i] = resid[67+i]+stabpos*p0[i];
        }
    }
    for (i = 0; i < 33; i++) {
        udot[i] = eudot[i];
    }
    for (i = 0; i < 33; i++) {
        mult[i] = emults[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   67 adds/subtracts/negates
                     33 multiplies
                      0 divides
                    166 assignments
*/
}

void sdmult(double omults[33],
    int *owrank,
    int omultmap[33])
{
    int i;

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    for (i = 0; i < 33; i++) {
        omults[i] = mult[i];
        if (i <= wrank-1) {
            omultmap[i] = multmap[i];
        } else {
            omultmap[i] = -1;
        }
    }
    *owrank = wrank;
}

void sdreac(double force[10][3],
    double torque[10][3])
{
/*
Generated 15-Feb-2006 17:06:53 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
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
    fc[32][0] = ((.205126*(AnkAtk[32][0]-gk[32][0]))-ufk[9][0]);
    fc[32][1] = ((.205126*(AnkAtk[32][1]-gk[32][1]))-ufk[9][1]);
    fc[32][2] = ((.205126*(AnkAtk[32][2]-gk[32][2]))-ufk[9][2]);
    tc[32][0] = ((WkIkWk[32][0]+(.000117*onk[32][0]))-(utk[9][0]-((.005139*
      fc[32][1])+(.0185*fc[32][2]))));
    tc[32][1] = ((WkIkWk[32][1]+(.000179*onk[32][1]))-(utk[9][1]+((.005139*
      fc[32][0])+(.026917*fc[32][2]))));
    tc[32][2] = ((WkIkWk[32][2]+(.000119*onk[32][2]))-(utk[9][2]+((.0185*
      fc[32][0])-(.026917*fc[32][1]))));
    fccikt[32][0] = ((Cik[32][0][2]*fc[32][2])+((Cik[32][0][0]*fc[32][0])+(
      Cik[32][0][1]*fc[32][1])));
    fccikt[32][1] = ((Cik[32][1][2]*fc[32][2])+((Cik[32][1][0]*fc[32][0])+(
      Cik[32][1][1]*fc[32][1])));
    fccikt[32][2] = ((Cik[32][2][2]*fc[32][2])+((Cik[32][2][0]*fc[32][0])+(
      Cik[32][2][1]*fc[32][1])));
    ffk[31][0] = -fccikt[32][0];
    ffk[31][1] = -fccikt[32][1];
    ffk[31][2] = -fccikt[32][2];
    ttk[31][0] = -((Cik[32][0][2]*tc[32][2])+((Cik[32][0][0]*tc[32][0])+(
      Cik[32][0][1]*tc[32][1])));
    ttk[31][1] = -((Cik[32][1][2]*tc[32][2])+((Cik[32][1][0]*tc[32][0])+(
      Cik[32][1][1]*tc[32][1])));
    ttk[31][2] = -((Cik[32][2][2]*tc[32][2])+((Cik[32][2][0]*tc[32][0])+(
      Cik[32][2][1]*tc[32][1])));
    fc[31][0] = -ffk[31][0];
    fc[31][1] = -ffk[31][1];
    fc[31][2] = -ffk[31][2];
    tc[31][0] = -ttk[31][0];
    tc[31][1] = -ttk[31][1];
    tc[31][2] = -ttk[31][2];
    fccikt[31][0] = ((Cik[31][0][2]*fc[31][2])+((Cik[31][0][0]*fc[31][0])+(
      Cik[31][0][1]*fc[31][1])));
    fccikt[31][1] = ((Cik[31][1][2]*fc[31][2])+((Cik[31][1][0]*fc[31][0])+(
      Cik[31][1][1]*fc[31][1])));
    fccikt[31][2] = ((Cik[31][2][2]*fc[31][2])+((Cik[31][2][0]*fc[31][0])+(
      Cik[31][2][1]*fc[31][1])));
    ffk[30][0] = -fccikt[31][0];
    ffk[30][1] = -fccikt[31][1];
    ffk[30][2] = -fccikt[31][2];
    ttk[30][0] = -((Cik[31][0][2]*tc[31][2])+((Cik[31][0][0]*tc[31][0])+(
      Cik[31][0][1]*tc[31][1])));
    ttk[30][1] = -((Cik[31][1][2]*tc[31][2])+((Cik[31][1][0]*tc[31][0])+(
      Cik[31][1][1]*tc[31][1])));
    ttk[30][2] = -((Cik[31][2][2]*tc[31][2])+((Cik[31][2][0]*tc[31][0])+(
      Cik[31][2][1]*tc[31][1])));
    fc[30][0] = -ffk[30][0];
    fc[30][1] = -ffk[30][1];
    fc[30][2] = -ffk[30][2];
    tc[30][0] = -ttk[30][0];
    tc[30][1] = -ttk[30][1];
    tc[30][2] = -ttk[30][2];
    fccikt[30][0] = ((Cik[30][0][2]*fc[30][2])+((Cik[30][0][0]*fc[30][0])+(
      Cik[30][0][1]*fc[30][1])));
    fccikt[30][1] = ((Cik[30][1][2]*fc[30][2])+((Cik[30][1][0]*fc[30][0])+(
      Cik[30][1][1]*fc[30][1])));
    fccikt[30][2] = ((Cik[30][2][2]*fc[30][2])+((Cik[30][2][0]*fc[30][0])+(
      Cik[30][2][1]*fc[30][1])));
    ffk[29][0] = (ufk[8][0]-fccikt[30][0]);
    ffk[29][1] = (ufk[8][1]-fccikt[30][1]);
    ffk[29][2] = (ufk[8][2]-fccikt[30][2]);
    ttk[29][0] = (utk[8][0]-(((.018078*fccikt[30][1])-(.038*fccikt[30][2]))+((
      Cik[30][0][2]*tc[30][2])+((Cik[30][0][0]*tc[30][0])+(Cik[30][0][1]*
      tc[30][1])))));
    ttk[29][1] = (utk[8][1]-(((Cik[30][1][2]*tc[30][2])+((Cik[30][1][0]*
      tc[30][0])+(Cik[30][1][1]*tc[30][1])))-((.018078*fccikt[30][0])+(.098032*
      fccikt[30][2]))));
    ttk[29][2] = (utk[8][2]-(((.038*fccikt[30][0])+(.098032*fccikt[30][1]))+((
      Cik[30][2][2]*tc[30][2])+((Cik[30][2][0]*tc[30][0])+(Cik[30][2][1]*
      tc[30][1])))));
    fc[29][0] = ((1.2*(AnkAtk[29][0]-gk[29][0]))-ffk[29][0]);
    fc[29][1] = ((1.2*(AnkAtk[29][1]-gk[29][1]))-ffk[29][1]);
    fc[29][2] = ((1.2*(AnkAtk[29][2]-gk[29][2]))-ffk[29][2]);
    tc[29][0] = ((WkIkWk[29][0]+(.001361*onk[29][0]))-(ttk[29][0]+((.051347*
      fc[29][2])-(.005539*fc[29][1]))));
    tc[29][1] = ((WkIkWk[29][1]+(.003709*onk[29][1]))-(ttk[29][1]+((.005539*
      fc[29][0])+(.035902*fc[29][2]))));
    tc[29][2] = ((WkIkWk[29][2]+(.003916*onk[29][2]))-(ttk[29][2]-((.035902*
      fc[29][1])+(.051347*fc[29][0]))));
    fccikt[29][0] = ((Cik[29][0][2]*fc[29][2])+((Cik[29][0][0]*fc[29][0])+(
      Cik[29][0][1]*fc[29][1])));
    fccikt[29][1] = ((Cik[29][1][2]*fc[29][2])+((Cik[29][1][0]*fc[29][0])+(
      Cik[29][1][1]*fc[29][1])));
    fccikt[29][2] = ((Cik[29][2][2]*fc[29][2])+((Cik[29][2][0]*fc[29][0])+(
      Cik[29][2][1]*fc[29][1])));
    ffk[28][0] = -fccikt[29][0];
    ffk[28][1] = -fccikt[29][1];
    ffk[28][2] = -fccikt[29][2];
    ttk[28][0] = -((Cik[29][0][2]*tc[29][2])+((Cik[29][0][0]*tc[29][0])+(
      Cik[29][0][1]*tc[29][1])));
    ttk[28][1] = -((Cik[29][1][2]*tc[29][2])+((Cik[29][1][0]*tc[29][0])+(
      Cik[29][1][1]*tc[29][1])));
    ttk[28][2] = -((Cik[29][2][2]*tc[29][2])+((Cik[29][2][0]*tc[29][0])+(
      Cik[29][2][1]*tc[29][1])));
    fc[28][0] = -ffk[28][0];
    fc[28][1] = -ffk[28][1];
    fc[28][2] = -ffk[28][2];
    tc[28][0] = -ttk[28][0];
    tc[28][1] = -ttk[28][1];
    tc[28][2] = -ttk[28][2];
    fccikt[28][0] = ((Cik[28][0][2]*fc[28][2])+((Cik[28][0][0]*fc[28][0])+(
      Cik[28][0][1]*fc[28][1])));
    fccikt[28][1] = ((Cik[28][1][2]*fc[28][2])+((Cik[28][1][0]*fc[28][0])+(
      Cik[28][1][1]*fc[28][1])));
    fccikt[28][2] = ((Cik[28][2][2]*fc[28][2])+((Cik[28][2][0]*fc[28][0])+(
      Cik[28][2][1]*fc[28][1])));
    ffk[27][0] = -fccikt[28][0];
    ffk[27][1] = -fccikt[28][1];
    ffk[27][2] = -fccikt[28][2];
    ttk[27][0] = -((Cik[28][0][2]*tc[28][2])+((Cik[28][0][0]*tc[28][0])+(
      Cik[28][0][1]*tc[28][1])));
    ttk[27][1] = -((Cik[28][1][2]*tc[28][2])+((Cik[28][1][0]*tc[28][0])+(
      Cik[28][1][1]*tc[28][1])));
    ttk[27][2] = -((Cik[28][2][2]*tc[28][2])+((Cik[28][2][0]*tc[28][0])+(
      Cik[28][2][1]*tc[28][1])));
    fc[27][0] = -ffk[27][0];
    fc[27][1] = -ffk[27][1];
    fc[27][2] = -ffk[27][2];
    tc[27][0] = -ttk[27][0];
    tc[27][1] = -ttk[27][1];
    tc[27][2] = -ttk[27][2];
    fccikt[27][0] = ((Cik[27][0][2]*fc[27][2])+((Cik[27][0][0]*fc[27][0])+(
      Cik[27][0][1]*fc[27][1])));
    fccikt[27][1] = ((Cik[27][1][2]*fc[27][2])+((Cik[27][1][0]*fc[27][0])+(
      Cik[27][1][1]*fc[27][1])));
    fccikt[27][2] = ((Cik[27][2][2]*fc[27][2])+((Cik[27][2][0]*fc[27][0])+(
      Cik[27][2][1]*fc[27][1])));
    ffk[26][0] = (ufk[7][0]-fccikt[27][0]);
    ffk[26][1] = (ufk[7][1]-fccikt[27][1]);
    ffk[26][2] = (ufk[7][2]-fccikt[27][2]);
    ttk[26][0] = (utk[7][0]-(((Cik[27][0][2]*tc[27][2])+((Cik[27][0][0]*
      tc[27][0])+(Cik[27][0][1]*tc[27][1])))-(.2438*fccikt[27][2])));
    ttk[26][1] = (utk[7][1]-((Cik[27][1][2]*tc[27][2])+((Cik[27][1][0]*tc[27][0]
      )+(Cik[27][1][1]*tc[27][1]))));
    ttk[26][2] = (utk[7][2]-((.2438*fccikt[27][0])+((Cik[27][2][2]*tc[27][2])+((
      Cik[27][2][0]*tc[27][0])+(Cik[27][2][1]*tc[27][1])))));
    fc[26][0] = ((3.51*(AnkAtk[26][0]-gk[26][0]))-ffk[26][0]);
    fc[26][1] = ((3.51*(AnkAtk[26][1]-gk[26][1]))-ffk[26][1]);
    fc[26][2] = ((3.51*(AnkAtk[26][2]-gk[26][2]))-ffk[26][2]);
    tc[26][0] = ((WkIkWk[26][0]+(.0477*onk[26][0]))-(ttk[26][0]+(.1862*fc[26][2]
      )));
    tc[26][1] = ((WkIkWk[26][1]+(.0048*onk[26][1]))-ttk[26][1]);
    tc[26][2] = ((WkIkWk[26][2]+(.0484*onk[26][2]))-(ttk[26][2]-(.1862*fc[26][0]
      )));
    fccikt[26][0] = ((Cik[26][0][2]*fc[26][2])+((Cik[26][0][0]*fc[26][0])+(
      Cik[26][0][1]*fc[26][1])));
    fccikt[26][1] = ((Cik[26][1][2]*fc[26][2])+((Cik[26][1][0]*fc[26][0])+(
      Cik[26][1][1]*fc[26][1])));
    fccikt[26][2] = ((Cik[26][2][2]*fc[26][2])+((Cik[26][2][0]*fc[26][0])+(
      Cik[26][2][1]*fc[26][1])));
    ffk[25][0] = -fccikt[26][0];
    ffk[25][1] = -fccikt[26][1];
    ffk[25][2] = -fccikt[26][2];
    ttk[25][0] = -((Cik[26][0][2]*tc[26][2])+((Cik[26][0][0]*tc[26][0])+(
      Cik[26][0][1]*tc[26][1])));
    ttk[25][1] = -((Cik[26][1][2]*tc[26][2])+((Cik[26][1][0]*tc[26][0])+(
      Cik[26][1][1]*tc[26][1])));
    ttk[25][2] = -((Cik[26][2][2]*tc[26][2])+((Cik[26][2][0]*tc[26][0])+(
      Cik[26][2][1]*tc[26][1])));
    fc[25][0] = -ffk[25][0];
    fc[25][1] = -ffk[25][1];
    fc[25][2] = -ffk[25][2];
    tc[25][0] = -ttk[25][0];
    tc[25][1] = -ttk[25][1];
    tc[25][2] = -ttk[25][2];
    fccikt[25][0] = ((Cik[25][0][2]*fc[25][2])+((Cik[25][0][0]*fc[25][0])+(
      Cik[25][0][1]*fc[25][1])));
    fccikt[25][1] = ((Cik[25][1][2]*fc[25][2])+((Cik[25][1][0]*fc[25][0])+(
      Cik[25][1][1]*fc[25][1])));
    fccikt[25][2] = ((Cik[25][2][2]*fc[25][2])+((Cik[25][2][0]*fc[25][0])+(
      Cik[25][2][1]*fc[25][1])));
    ffk[24][0] = -fccikt[25][0];
    ffk[24][1] = -fccikt[25][1];
    ffk[24][2] = -fccikt[25][2];
    ttk[24][0] = -((Cik[25][0][2]*tc[25][2])+((Cik[25][0][0]*tc[25][0])+(
      Cik[25][0][1]*tc[25][1])));
    ttk[24][1] = -((Cik[25][1][2]*tc[25][2])+((Cik[25][1][0]*tc[25][0])+(
      Cik[25][1][1]*tc[25][1])));
    ttk[24][2] = -((Cik[25][2][2]*tc[25][2])+((Cik[25][2][0]*tc[25][0])+(
      Cik[25][2][1]*tc[25][1])));
    fc[24][0] = -ffk[24][0];
    fc[24][1] = -ffk[24][1];
    fc[24][2] = -ffk[24][2];
    tc[24][0] = -ttk[24][0];
    tc[24][1] = -ttk[24][1];
    tc[24][2] = -ttk[24][2];
    fccikt[24][0] = ((Cik[24][0][2]*fc[24][2])+((Cik[24][0][0]*fc[24][0])+(
      Cik[24][0][1]*fc[24][1])));
    fccikt[24][1] = ((Cik[24][1][2]*fc[24][2])+((Cik[24][1][0]*fc[24][0])+(
      Cik[24][1][1]*fc[24][1])));
    fccikt[24][2] = ((Cik[24][2][2]*fc[24][2])+((Cik[24][2][0]*fc[24][0])+(
      Cik[24][2][1]*fc[24][1])));
    ffk[23][0] = (ufk[6][0]-fccikt[24][0]);
    ffk[23][1] = (ufk[6][1]-fccikt[24][1]);
    ffk[23][2] = (ufk[6][2]-fccikt[24][2]);
    ttk[23][0] = (utk[6][0]-(((Cik[24][0][2]*tc[24][2])+((Cik[24][0][0]*
      tc[24][0])+(Cik[24][0][1]*tc[24][1])))-(.2294*fccikt[24][2])));
    ttk[23][1] = (utk[6][1]-(((Cik[24][1][2]*tc[24][2])+((Cik[24][1][0]*
      tc[24][0])+(Cik[24][1][1]*tc[24][1])))-(.0033*fccikt[24][2])));
    ttk[23][2] = (utk[6][2]-(((.0033*fccikt[24][1])+(.2294*fccikt[24][0]))+((
      Cik[24][2][2]*tc[24][2])+((Cik[24][2][0]*tc[24][0])+(Cik[24][2][1]*
      tc[24][1])))));
    fc[23][0] = ((8.806*(AnkAtk[23][0]-gk[23][0]))-ffk[23][0]);
    fc[23][1] = ((8.806*(AnkAtk[23][1]-gk[23][1]))-ffk[23][1]);
    fc[23][2] = ((8.806*(AnkAtk[23][2]-gk[23][2]))-ffk[23][2]);
    tc[23][0] = ((WkIkWk[23][0]+(.1268*onk[23][0]))-(ttk[23][0]+(.1715*fc[23][2]
      )));
    tc[23][1] = ((WkIkWk[23][1]+(.0332*onk[23][1]))-(ttk[23][1]-(.002*fc[23][2])
      ));
    tc[23][2] = ((WkIkWk[23][2]+(.1337*onk[23][2]))-(ttk[23][2]+((.002*fc[23][1]
      )-(.1715*fc[23][0]))));
    fccikt[23][0] = ((Cik[23][0][2]*fc[23][2])+((Cik[23][0][0]*fc[23][0])+(
      Cik[23][0][1]*fc[23][1])));
    fccikt[23][1] = ((Cik[23][1][2]*fc[23][2])+((Cik[23][1][0]*fc[23][0])+(
      Cik[23][1][1]*fc[23][1])));
    fccikt[23][2] = ((Cik[23][2][2]*fc[23][2])+((Cik[23][2][0]*fc[23][0])+(
      Cik[23][2][1]*fc[23][1])));
    ffk[22][0] = -fccikt[23][0];
    ffk[22][1] = -fccikt[23][1];
    ffk[22][2] = -fccikt[23][2];
    ttk[22][0] = -((Cik[23][0][2]*tc[23][2])+((Cik[23][0][0]*tc[23][0])+(
      Cik[23][0][1]*tc[23][1])));
    ttk[22][1] = -((Cik[23][1][2]*tc[23][2])+((Cik[23][1][0]*tc[23][0])+(
      Cik[23][1][1]*tc[23][1])));
    ttk[22][2] = -((Cik[23][2][2]*tc[23][2])+((Cik[23][2][0]*tc[23][0])+(
      Cik[23][2][1]*tc[23][1])));
    fc[22][0] = -ffk[22][0];
    fc[22][1] = -ffk[22][1];
    fc[22][2] = -ffk[22][2];
    tc[22][0] = -ttk[22][0];
    tc[22][1] = -ttk[22][1];
    tc[22][2] = -ttk[22][2];
    fccikt[22][0] = ((Cik[22][0][2]*fc[22][2])+((Cik[22][0][0]*fc[22][0])+(
      Cik[22][0][1]*fc[22][1])));
    fccikt[22][1] = ((Cik[22][1][2]*fc[22][2])+((Cik[22][1][0]*fc[22][0])+(
      Cik[22][1][1]*fc[22][1])));
    fccikt[22][2] = ((Cik[22][2][2]*fc[22][2])+((Cik[22][2][0]*fc[22][0])+(
      Cik[22][2][1]*fc[22][1])));
    ffk[21][0] = -fccikt[22][0];
    ffk[21][1] = -fccikt[22][1];
    ffk[21][2] = -fccikt[22][2];
    ttk[21][0] = -((Cik[22][0][2]*tc[22][2])+((Cik[22][0][0]*tc[22][0])+(
      Cik[22][0][1]*tc[22][1])));
    ttk[21][1] = -((Cik[22][1][2]*tc[22][2])+((Cik[22][1][0]*tc[22][0])+(
      Cik[22][1][1]*tc[22][1])));
    ttk[21][2] = -((Cik[22][2][2]*tc[22][2])+((Cik[22][2][0]*tc[22][0])+(
      Cik[22][2][1]*tc[22][1])));
    fc[21][0] = -ffk[21][0];
    fc[21][1] = -ffk[21][1];
    fc[21][2] = -ffk[21][2];
    tc[21][0] = -ttk[21][0];
    tc[21][1] = -ttk[21][1];
    tc[21][2] = -ttk[21][2];
    fccikt[21][0] = ((Cik[21][0][2]*fc[21][2])+((Cik[21][0][0]*fc[21][0])+(
      Cik[21][0][1]*fc[21][1])));
    fccikt[21][1] = ((Cik[21][1][2]*fc[21][2])+((Cik[21][1][0]*fc[21][0])+(
      Cik[21][1][1]*fc[21][1])));
    fccikt[21][2] = ((Cik[21][2][2]*fc[21][2])+((Cik[21][2][0]*fc[21][0])+(
      Cik[21][2][1]*fc[21][1])));
    ffk[5][0] = (ufk[0][0]-fccikt[21][0]);
    ffk[5][1] = (ufk[0][1]-fccikt[21][1]);
    ffk[5][2] = (ufk[0][2]-fccikt[21][2]);
    ttk[5][0] = (utk[0][0]-(((.0935*fccikt[21][1])-(.07*fccikt[21][2]))+((
      Cik[21][0][2]*tc[21][2])+((Cik[21][0][0]*tc[21][0])+(Cik[21][0][1]*
      tc[21][1])))));
    ttk[5][1] = (utk[0][1]-(((Cik[21][1][2]*tc[21][2])+((Cik[21][1][0]*tc[21][0]
      )+(Cik[21][1][1]*tc[21][1])))-(.0935*fccikt[21][0])));
    ttk[5][2] = (utk[0][2]-((.07*fccikt[21][0])+((Cik[21][2][2]*tc[21][2])+((
      Cik[21][2][0]*tc[21][0])+(Cik[21][2][1]*tc[21][1])))));
    fc[20][0] = ((.205126*(AnkAtk[20][0]-gk[20][0]))-ufk[5][0]);
    fc[20][1] = ((.205126*(AnkAtk[20][1]-gk[20][1]))-ufk[5][1]);
    fc[20][2] = ((.205126*(AnkAtk[20][2]-gk[20][2]))-ufk[5][2]);
    tc[20][0] = ((WkIkWk[20][0]+(.000117*onk[20][0]))-(utk[5][0]+((.005139*
      fc[20][1])-(.0185*fc[20][2]))));
    tc[20][1] = ((WkIkWk[20][1]+(.000179*onk[20][1]))-(utk[5][1]+((.026917*
      fc[20][2])-(.005139*fc[20][0]))));
    tc[20][2] = ((WkIkWk[20][2]+(.000119*onk[20][2]))-(utk[5][2]+((.0185*
      fc[20][0])-(.026917*fc[20][1]))));
    fccikt[20][0] = ((Cik[20][0][2]*fc[20][2])+((Cik[20][0][0]*fc[20][0])+(
      Cik[20][0][1]*fc[20][1])));
    fccikt[20][1] = ((Cik[20][1][2]*fc[20][2])+((Cik[20][1][0]*fc[20][0])+(
      Cik[20][1][1]*fc[20][1])));
    fccikt[20][2] = ((Cik[20][2][2]*fc[20][2])+((Cik[20][2][0]*fc[20][0])+(
      Cik[20][2][1]*fc[20][1])));
    ffk[19][0] = -fccikt[20][0];
    ffk[19][1] = -fccikt[20][1];
    ffk[19][2] = -fccikt[20][2];
    ttk[19][0] = -((Cik[20][0][2]*tc[20][2])+((Cik[20][0][0]*tc[20][0])+(
      Cik[20][0][1]*tc[20][1])));
    ttk[19][1] = -((Cik[20][1][2]*tc[20][2])+((Cik[20][1][0]*tc[20][0])+(
      Cik[20][1][1]*tc[20][1])));
    ttk[19][2] = -((Cik[20][2][2]*tc[20][2])+((Cik[20][2][0]*tc[20][0])+(
      Cik[20][2][1]*tc[20][1])));
    fc[19][0] = -ffk[19][0];
    fc[19][1] = -ffk[19][1];
    fc[19][2] = -ffk[19][2];
    tc[19][0] = -ttk[19][0];
    tc[19][1] = -ttk[19][1];
    tc[19][2] = -ttk[19][2];
    fccikt[19][0] = ((Cik[19][0][2]*fc[19][2])+((Cik[19][0][0]*fc[19][0])+(
      Cik[19][0][1]*fc[19][1])));
    fccikt[19][1] = ((Cik[19][1][2]*fc[19][2])+((Cik[19][1][0]*fc[19][0])+(
      Cik[19][1][1]*fc[19][1])));
    fccikt[19][2] = ((Cik[19][2][2]*fc[19][2])+((Cik[19][2][0]*fc[19][0])+(
      Cik[19][2][1]*fc[19][1])));
    ffk[18][0] = -fccikt[19][0];
    ffk[18][1] = -fccikt[19][1];
    ffk[18][2] = -fccikt[19][2];
    ttk[18][0] = -((Cik[19][0][2]*tc[19][2])+((Cik[19][0][0]*tc[19][0])+(
      Cik[19][0][1]*tc[19][1])));
    ttk[18][1] = -((Cik[19][1][2]*tc[19][2])+((Cik[19][1][0]*tc[19][0])+(
      Cik[19][1][1]*tc[19][1])));
    ttk[18][2] = -((Cik[19][2][2]*tc[19][2])+((Cik[19][2][0]*tc[19][0])+(
      Cik[19][2][1]*tc[19][1])));
    fc[18][0] = -ffk[18][0];
    fc[18][1] = -ffk[18][1];
    fc[18][2] = -ffk[18][2];
    tc[18][0] = -ttk[18][0];
    tc[18][1] = -ttk[18][1];
    tc[18][2] = -ttk[18][2];
    fccikt[18][0] = ((Cik[18][0][2]*fc[18][2])+((Cik[18][0][0]*fc[18][0])+(
      Cik[18][0][1]*fc[18][1])));
    fccikt[18][1] = ((Cik[18][1][2]*fc[18][2])+((Cik[18][1][0]*fc[18][0])+(
      Cik[18][1][1]*fc[18][1])));
    fccikt[18][2] = ((Cik[18][2][2]*fc[18][2])+((Cik[18][2][0]*fc[18][0])+(
      Cik[18][2][1]*fc[18][1])));
    ffk[17][0] = (ufk[4][0]-fccikt[18][0]);
    ffk[17][1] = (ufk[4][1]-fccikt[18][1]);
    ffk[17][2] = (ufk[4][2]-fccikt[18][2]);
    ttk[17][0] = (utk[4][0]-(((Cik[18][0][2]*tc[18][2])+((Cik[18][0][0]*
      tc[18][0])+(Cik[18][0][1]*tc[18][1])))-((.018078*fccikt[18][1])+(.038*
      fccikt[18][2]))));
    ttk[17][1] = (utk[4][1]-(((.018078*fccikt[18][0])-(.098032*fccikt[18][2]))+(
      (Cik[18][1][2]*tc[18][2])+((Cik[18][1][0]*tc[18][0])+(Cik[18][1][1]*
      tc[18][1])))));
    ttk[17][2] = (utk[4][2]-(((.038*fccikt[18][0])+(.098032*fccikt[18][1]))+((
      Cik[18][2][2]*tc[18][2])+((Cik[18][2][0]*tc[18][0])+(Cik[18][2][1]*
      tc[18][1])))));
    fc[17][0] = ((1.2*(AnkAtk[17][0]-gk[17][0]))-ffk[17][0]);
    fc[17][1] = ((1.2*(AnkAtk[17][1]-gk[17][1]))-ffk[17][1]);
    fc[17][2] = ((1.2*(AnkAtk[17][2]-gk[17][2]))-ffk[17][2]);
    tc[17][0] = ((WkIkWk[17][0]+(.001361*onk[17][0]))-(ttk[17][0]+((.005539*
      fc[17][1])+(.051347*fc[17][2]))));
    tc[17][1] = ((WkIkWk[17][1]+(.003709*onk[17][1]))-(ttk[17][1]+((.035902*
      fc[17][2])-(.005539*fc[17][0]))));
    tc[17][2] = ((WkIkWk[17][2]+(.003916*onk[17][2]))-(ttk[17][2]-((.035902*
      fc[17][1])+(.051347*fc[17][0]))));
    fccikt[17][0] = ((Cik[17][0][2]*fc[17][2])+((Cik[17][0][0]*fc[17][0])+(
      Cik[17][0][1]*fc[17][1])));
    fccikt[17][1] = ((Cik[17][1][2]*fc[17][2])+((Cik[17][1][0]*fc[17][0])+(
      Cik[17][1][1]*fc[17][1])));
    fccikt[17][2] = ((Cik[17][2][2]*fc[17][2])+((Cik[17][2][0]*fc[17][0])+(
      Cik[17][2][1]*fc[17][1])));
    ffk[16][0] = -fccikt[17][0];
    ffk[16][1] = -fccikt[17][1];
    ffk[16][2] = -fccikt[17][2];
    ttk[16][0] = -((Cik[17][0][2]*tc[17][2])+((Cik[17][0][0]*tc[17][0])+(
      Cik[17][0][1]*tc[17][1])));
    ttk[16][1] = -((Cik[17][1][2]*tc[17][2])+((Cik[17][1][0]*tc[17][0])+(
      Cik[17][1][1]*tc[17][1])));
    ttk[16][2] = -((Cik[17][2][2]*tc[17][2])+((Cik[17][2][0]*tc[17][0])+(
      Cik[17][2][1]*tc[17][1])));
    fc[16][0] = -ffk[16][0];
    fc[16][1] = -ffk[16][1];
    fc[16][2] = -ffk[16][2];
    tc[16][0] = -ttk[16][0];
    tc[16][1] = -ttk[16][1];
    tc[16][2] = -ttk[16][2];
    fccikt[16][0] = ((Cik[16][0][2]*fc[16][2])+((Cik[16][0][0]*fc[16][0])+(
      Cik[16][0][1]*fc[16][1])));
    fccikt[16][1] = ((Cik[16][1][2]*fc[16][2])+((Cik[16][1][0]*fc[16][0])+(
      Cik[16][1][1]*fc[16][1])));
    fccikt[16][2] = ((Cik[16][2][2]*fc[16][2])+((Cik[16][2][0]*fc[16][0])+(
      Cik[16][2][1]*fc[16][1])));
    ffk[15][0] = -fccikt[16][0];
    ffk[15][1] = -fccikt[16][1];
    ffk[15][2] = -fccikt[16][2];
    ttk[15][0] = -((Cik[16][0][2]*tc[16][2])+((Cik[16][0][0]*tc[16][0])+(
      Cik[16][0][1]*tc[16][1])));
    ttk[15][1] = -((Cik[16][1][2]*tc[16][2])+((Cik[16][1][0]*tc[16][0])+(
      Cik[16][1][1]*tc[16][1])));
    ttk[15][2] = -((Cik[16][2][2]*tc[16][2])+((Cik[16][2][0]*tc[16][0])+(
      Cik[16][2][1]*tc[16][1])));
    fc[15][0] = -ffk[15][0];
    fc[15][1] = -ffk[15][1];
    fc[15][2] = -ffk[15][2];
    tc[15][0] = -ttk[15][0];
    tc[15][1] = -ttk[15][1];
    tc[15][2] = -ttk[15][2];
    fccikt[15][0] = ((Cik[15][0][2]*fc[15][2])+((Cik[15][0][0]*fc[15][0])+(
      Cik[15][0][1]*fc[15][1])));
    fccikt[15][1] = ((Cik[15][1][2]*fc[15][2])+((Cik[15][1][0]*fc[15][0])+(
      Cik[15][1][1]*fc[15][1])));
    fccikt[15][2] = ((Cik[15][2][2]*fc[15][2])+((Cik[15][2][0]*fc[15][0])+(
      Cik[15][2][1]*fc[15][1])));
    ffk[14][0] = (ufk[3][0]-fccikt[15][0]);
    ffk[14][1] = (ufk[3][1]-fccikt[15][1]);
    ffk[14][2] = (ufk[3][2]-fccikt[15][2]);
    ttk[14][0] = (utk[3][0]-(((Cik[15][0][2]*tc[15][2])+((Cik[15][0][0]*
      tc[15][0])+(Cik[15][0][1]*tc[15][1])))-(.2438*fccikt[15][2])));
    ttk[14][1] = (utk[3][1]-((Cik[15][1][2]*tc[15][2])+((Cik[15][1][0]*tc[15][0]
      )+(Cik[15][1][1]*tc[15][1]))));
    ttk[14][2] = (utk[3][2]-((.2438*fccikt[15][0])+((Cik[15][2][2]*tc[15][2])+((
      Cik[15][2][0]*tc[15][0])+(Cik[15][2][1]*tc[15][1])))));
    fc[14][0] = ((3.51*(AnkAtk[14][0]-gk[14][0]))-ffk[14][0]);
    fc[14][1] = ((3.51*(AnkAtk[14][1]-gk[14][1]))-ffk[14][1]);
    fc[14][2] = ((3.51*(AnkAtk[14][2]-gk[14][2]))-ffk[14][2]);
    tc[14][0] = ((WkIkWk[14][0]+(.0477*onk[14][0]))-(ttk[14][0]+(.1862*fc[14][2]
      )));
    tc[14][1] = ((WkIkWk[14][1]+(.0048*onk[14][1]))-ttk[14][1]);
    tc[14][2] = ((WkIkWk[14][2]+(.0484*onk[14][2]))-(ttk[14][2]-(.1862*fc[14][0]
      )));
    fccikt[14][0] = ((Cik[14][0][2]*fc[14][2])+((Cik[14][0][0]*fc[14][0])+(
      Cik[14][0][1]*fc[14][1])));
    fccikt[14][1] = ((Cik[14][1][2]*fc[14][2])+((Cik[14][1][0]*fc[14][0])+(
      Cik[14][1][1]*fc[14][1])));
    fccikt[14][2] = ((Cik[14][2][2]*fc[14][2])+((Cik[14][2][0]*fc[14][0])+(
      Cik[14][2][1]*fc[14][1])));
    ffk[13][0] = -fccikt[14][0];
    ffk[13][1] = -fccikt[14][1];
    ffk[13][2] = -fccikt[14][2];
    ttk[13][0] = -((Cik[14][0][2]*tc[14][2])+((Cik[14][0][0]*tc[14][0])+(
      Cik[14][0][1]*tc[14][1])));
    ttk[13][1] = -((Cik[14][1][2]*tc[14][2])+((Cik[14][1][0]*tc[14][0])+(
      Cik[14][1][1]*tc[14][1])));
    ttk[13][2] = -((Cik[14][2][2]*tc[14][2])+((Cik[14][2][0]*tc[14][0])+(
      Cik[14][2][1]*tc[14][1])));
    fc[13][0] = -ffk[13][0];
    fc[13][1] = -ffk[13][1];
    fc[13][2] = -ffk[13][2];
    tc[13][0] = -ttk[13][0];
    tc[13][1] = -ttk[13][1];
    tc[13][2] = -ttk[13][2];
    fccikt[13][0] = ((Cik[13][0][2]*fc[13][2])+((Cik[13][0][0]*fc[13][0])+(
      Cik[13][0][1]*fc[13][1])));
    fccikt[13][1] = ((Cik[13][1][2]*fc[13][2])+((Cik[13][1][0]*fc[13][0])+(
      Cik[13][1][1]*fc[13][1])));
    fccikt[13][2] = ((Cik[13][2][2]*fc[13][2])+((Cik[13][2][0]*fc[13][0])+(
      Cik[13][2][1]*fc[13][1])));
    ffk[12][0] = -fccikt[13][0];
    ffk[12][1] = -fccikt[13][1];
    ffk[12][2] = -fccikt[13][2];
    ttk[12][0] = -((Cik[13][0][2]*tc[13][2])+((Cik[13][0][0]*tc[13][0])+(
      Cik[13][0][1]*tc[13][1])));
    ttk[12][1] = -((Cik[13][1][2]*tc[13][2])+((Cik[13][1][0]*tc[13][0])+(
      Cik[13][1][1]*tc[13][1])));
    ttk[12][2] = -((Cik[13][2][2]*tc[13][2])+((Cik[13][2][0]*tc[13][0])+(
      Cik[13][2][1]*tc[13][1])));
    fc[12][0] = -ffk[12][0];
    fc[12][1] = -ffk[12][1];
    fc[12][2] = -ffk[12][2];
    tc[12][0] = -ttk[12][0];
    tc[12][1] = -ttk[12][1];
    tc[12][2] = -ttk[12][2];
    fccikt[12][0] = ((Cik[12][0][2]*fc[12][2])+((Cik[12][0][0]*fc[12][0])+(
      Cik[12][0][1]*fc[12][1])));
    fccikt[12][1] = ((Cik[12][1][2]*fc[12][2])+((Cik[12][1][0]*fc[12][0])+(
      Cik[12][1][1]*fc[12][1])));
    fccikt[12][2] = ((Cik[12][2][2]*fc[12][2])+((Cik[12][2][0]*fc[12][0])+(
      Cik[12][2][1]*fc[12][1])));
    ffk[11][0] = (ufk[2][0]-fccikt[12][0]);
    ffk[11][1] = (ufk[2][1]-fccikt[12][1]);
    ffk[11][2] = (ufk[2][2]-fccikt[12][2]);
    ttk[11][0] = (utk[2][0]-(((Cik[12][0][2]*tc[12][2])+((Cik[12][0][0]*
      tc[12][0])+(Cik[12][0][1]*tc[12][1])))-(.2294*fccikt[12][2])));
    ttk[11][1] = (utk[2][1]-(((Cik[12][1][2]*tc[12][2])+((Cik[12][1][0]*
      tc[12][0])+(Cik[12][1][1]*tc[12][1])))-(.0033*fccikt[12][2])));
    ttk[11][2] = (utk[2][2]-(((.0033*fccikt[12][1])+(.2294*fccikt[12][0]))+((
      Cik[12][2][2]*tc[12][2])+((Cik[12][2][0]*tc[12][0])+(Cik[12][2][1]*
      tc[12][1])))));
    fc[11][0] = ((8.806*(AnkAtk[11][0]-gk[11][0]))-ffk[11][0]);
    fc[11][1] = ((8.806*(AnkAtk[11][1]-gk[11][1]))-ffk[11][1]);
    fc[11][2] = ((8.806*(AnkAtk[11][2]-gk[11][2]))-ffk[11][2]);
    tc[11][0] = ((WkIkWk[11][0]+(.1268*onk[11][0]))-(ttk[11][0]+(.1715*fc[11][2]
      )));
    tc[11][1] = ((WkIkWk[11][1]+(.0332*onk[11][1]))-(ttk[11][1]-(.002*fc[11][2])
      ));
    tc[11][2] = ((WkIkWk[11][2]+(.1337*onk[11][2]))-(ttk[11][2]+((.002*fc[11][1]
      )-(.1715*fc[11][0]))));
    fccikt[11][0] = ((Cik[11][0][2]*fc[11][2])+((Cik[11][0][0]*fc[11][0])+(
      Cik[11][0][1]*fc[11][1])));
    fccikt[11][1] = ((Cik[11][1][2]*fc[11][2])+((Cik[11][1][0]*fc[11][0])+(
      Cik[11][1][1]*fc[11][1])));
    fccikt[11][2] = ((Cik[11][2][2]*fc[11][2])+((Cik[11][2][0]*fc[11][0])+(
      Cik[11][2][1]*fc[11][1])));
    ffk[10][0] = -fccikt[11][0];
    ffk[10][1] = -fccikt[11][1];
    ffk[10][2] = -fccikt[11][2];
    ttk[10][0] = -((Cik[11][0][2]*tc[11][2])+((Cik[11][0][0]*tc[11][0])+(
      Cik[11][0][1]*tc[11][1])));
    ttk[10][1] = -((Cik[11][1][2]*tc[11][2])+((Cik[11][1][0]*tc[11][0])+(
      Cik[11][1][1]*tc[11][1])));
    ttk[10][2] = -((Cik[11][2][2]*tc[11][2])+((Cik[11][2][0]*tc[11][0])+(
      Cik[11][2][1]*tc[11][1])));
    fc[10][0] = -ffk[10][0];
    fc[10][1] = -ffk[10][1];
    fc[10][2] = -ffk[10][2];
    tc[10][0] = -ttk[10][0];
    tc[10][1] = -ttk[10][1];
    tc[10][2] = -ttk[10][2];
    fccikt[10][0] = ((Cik[10][0][2]*fc[10][2])+((Cik[10][0][0]*fc[10][0])+(
      Cik[10][0][1]*fc[10][1])));
    fccikt[10][1] = ((Cik[10][1][2]*fc[10][2])+((Cik[10][1][0]*fc[10][0])+(
      Cik[10][1][1]*fc[10][1])));
    fccikt[10][2] = ((Cik[10][2][2]*fc[10][2])+((Cik[10][2][0]*fc[10][0])+(
      Cik[10][2][1]*fc[10][1])));
    ffk[9][0] = -fccikt[10][0];
    ffk[9][1] = -fccikt[10][1];
    ffk[9][2] = -fccikt[10][2];
    ttk[9][0] = -((Cik[10][0][2]*tc[10][2])+((Cik[10][0][0]*tc[10][0])+(
      Cik[10][0][1]*tc[10][1])));
    ttk[9][1] = -((Cik[10][1][2]*tc[10][2])+((Cik[10][1][0]*tc[10][0])+(
      Cik[10][1][1]*tc[10][1])));
    ttk[9][2] = -((Cik[10][2][2]*tc[10][2])+((Cik[10][2][0]*tc[10][0])+(
      Cik[10][2][1]*tc[10][1])));
    fc[9][0] = -ffk[9][0];
    fc[9][1] = -ffk[9][1];
    fc[9][2] = -ffk[9][2];
    tc[9][0] = -ttk[9][0];
    tc[9][1] = -ttk[9][1];
    tc[9][2] = -ttk[9][2];
    fccikt[9][0] = ((Cik[9][0][2]*fc[9][2])+((Cik[9][0][0]*fc[9][0])+(
      Cik[9][0][1]*fc[9][1])));
    fccikt[9][1] = ((Cik[9][1][2]*fc[9][2])+((Cik[9][1][0]*fc[9][0])+(
      Cik[9][1][1]*fc[9][1])));
    fccikt[9][2] = ((Cik[9][2][2]*fc[9][2])+((Cik[9][2][0]*fc[9][0])+(
      Cik[9][2][1]*fc[9][1])));
    ffk[5][0] = (ffk[5][0]-fccikt[9][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[9][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[9][2]);
    ttk[5][0] = (ttk[5][0]-(((Cik[9][0][2]*tc[9][2])+((Cik[9][0][0]*tc[9][0])+(
      Cik[9][0][1]*tc[9][1])))-((.07*fccikt[9][2])+(.0935*fccikt[9][1]))));
    ttk[5][1] = (ttk[5][1]-((.0935*fccikt[9][0])+((Cik[9][1][2]*tc[9][2])+((
      Cik[9][1][0]*tc[9][0])+(Cik[9][1][1]*tc[9][1])))));
    ttk[5][2] = (ttk[5][2]-((.07*fccikt[9][0])+((Cik[9][2][2]*tc[9][2])+((
      Cik[9][2][0]*tc[9][0])+(Cik[9][2][1]*tc[9][1])))));
    fc[8][0] = ((32.413*(AnkAtk[8][0]-gk[8][0]))-ufk[1][0]);
    fc[8][1] = ((32.413*(AnkAtk[8][1]-gk[8][1]))-ufk[1][1]);
    fc[8][2] = ((32.413*(AnkAtk[8][2]-gk[8][2]))-ufk[1][2]);
    tc[8][0] = ((WkIkWk[8][0]+(1.396*onk[8][0]))-(utk[1][0]-(.3202*fc[8][2])));
    tc[8][1] = ((WkIkWk[8][1]+(.7153*onk[8][1]))-utk[1][1]);
    tc[8][2] = ((WkIkWk[8][2]+(1.3552*onk[8][2]))-(utk[1][2]+(.3202*fc[8][0])));
    fccikt[8][0] = ((Cik[8][0][2]*fc[8][2])+((Cik[8][0][0]*fc[8][0])+(
      Cik[8][0][1]*fc[8][1])));
    fccikt[8][1] = ((Cik[8][1][2]*fc[8][2])+((Cik[8][1][0]*fc[8][0])+(
      Cik[8][1][1]*fc[8][1])));
    fccikt[8][2] = ((Cik[8][2][2]*fc[8][2])+((Cik[8][2][0]*fc[8][0])+(
      Cik[8][2][1]*fc[8][1])));
    ffk[7][0] = -fccikt[8][0];
    ffk[7][1] = -fccikt[8][1];
    ffk[7][2] = -fccikt[8][2];
    ttk[7][0] = -((Cik[8][0][2]*tc[8][2])+((Cik[8][0][0]*tc[8][0])+(Cik[8][0][1]
      *tc[8][1])));
    ttk[7][1] = -((Cik[8][1][2]*tc[8][2])+((Cik[8][1][0]*tc[8][0])+(Cik[8][1][1]
      *tc[8][1])));
    ttk[7][2] = -((Cik[8][2][2]*tc[8][2])+((Cik[8][2][0]*tc[8][0])+(Cik[8][2][1]
      *tc[8][1])));
    fc[7][0] = -ffk[7][0];
    fc[7][1] = -ffk[7][1];
    fc[7][2] = -ffk[7][2];
    tc[7][0] = -ttk[7][0];
    tc[7][1] = -ttk[7][1];
    tc[7][2] = -ttk[7][2];
    fccikt[7][0] = ((Cik[7][0][2]*fc[7][2])+((Cik[7][0][0]*fc[7][0])+(
      Cik[7][0][1]*fc[7][1])));
    fccikt[7][1] = ((Cik[7][1][2]*fc[7][2])+((Cik[7][1][0]*fc[7][0])+(
      Cik[7][1][1]*fc[7][1])));
    fccikt[7][2] = ((Cik[7][2][2]*fc[7][2])+((Cik[7][2][0]*fc[7][0])+(
      Cik[7][2][1]*fc[7][1])));
    ffk[6][0] = -fccikt[7][0];
    ffk[6][1] = -fccikt[7][1];
    ffk[6][2] = -fccikt[7][2];
    ttk[6][0] = -((Cik[7][0][2]*tc[7][2])+((Cik[7][0][0]*tc[7][0])+(Cik[7][0][1]
      *tc[7][1])));
    ttk[6][1] = -((Cik[7][1][2]*tc[7][2])+((Cik[7][1][0]*tc[7][0])+(Cik[7][1][1]
      *tc[7][1])));
    ttk[6][2] = -((Cik[7][2][2]*tc[7][2])+((Cik[7][2][0]*tc[7][0])+(Cik[7][2][1]
      *tc[7][1])));
    fc[6][0] = -ffk[6][0];
    fc[6][1] = -ffk[6][1];
    fc[6][2] = -ffk[6][2];
    tc[6][0] = -ttk[6][0];
    tc[6][1] = -ttk[6][1];
    tc[6][2] = -ttk[6][2];
    fccikt[6][0] = ((Cik[6][0][2]*fc[6][2])+((Cik[6][0][0]*fc[6][0])+(
      Cik[6][0][1]*fc[6][1])));
    fccikt[6][1] = ((Cik[6][1][2]*fc[6][2])+((Cik[6][1][0]*fc[6][0])+(
      Cik[6][1][1]*fc[6][1])));
    fccikt[6][2] = ((Cik[6][2][2]*fc[6][2])+((Cik[6][2][0]*fc[6][0])+(
      Cik[6][2][1]*fc[6][1])));
    ffk[5][0] = (ffk[5][0]-fccikt[6][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[6][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[6][2]);
    ttk[5][0] = (ttk[5][0]-((.127*fccikt[6][2])+((Cik[6][0][2]*tc[6][2])+((
      Cik[6][0][0]*tc[6][0])+(Cik[6][0][1]*tc[6][1])))));
    ttk[5][1] = (ttk[5][1]-((Cik[6][1][2]*tc[6][2])+((Cik[6][1][0]*tc[6][0])+(
      Cik[6][1][1]*tc[6][1]))));
    ttk[5][2] = (ttk[5][2]-(((Cik[6][2][2]*tc[6][2])+((Cik[6][2][0]*tc[6][0])+(
      Cik[6][2][1]*tc[6][1])))-(.127*fccikt[6][0])));
    fc[5][0] = ((11.15*(Ankb[3][0]-gk[3][0]))-ffk[5][0]);
    fc[5][1] = ((11.15*(Ankb[3][1]-gk[3][1]))-ffk[5][1]);
    fc[5][2] = ((11.15*(Ankb[3][2]-gk[3][2]))-ffk[5][2]);
    tc[5][0] = ((WkIkWk[5][0]+(.0973*udot[3]))-ttk[5][0]);
    tc[5][1] = ((WkIkWk[5][1]+(.0825*udot[4]))-ttk[5][1]);
    tc[5][2] = ((WkIkWk[5][2]+(.0548*udot[5]))-ttk[5][2]);
    fccikt[5][0] = fc[5][0];
    fccikt[5][1] = fc[5][1];
    fccikt[5][2] = fc[5][2];
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -tc[5][0];
    ttk[4][1] = -tc[5][1];
    ttk[4][2] = -tc[5][2];
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = fc[4][0];
    fccikt[4][1] = fc[4][1];
    fccikt[4][2] = fc[4][2];
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -tc[4][0];
    ttk[3][1] = -tc[4][1];
    ttk[3][2] = -tc[4][2];
    fc[3][0] = -ffk[3][0];
    fc[3][1] = -ffk[3][1];
    fc[3][2] = -ffk[3][2];
    tc[3][0] = -ttk[3][0];
    tc[3][1] = -ttk[3][1];
    tc[3][2] = -ttk[3][2];
    fccikt[3][0] = ((Cik[3][0][2]*fc[3][2])+((Cik[3][0][0]*fc[3][0])+(
      Cik[3][0][1]*fc[3][1])));
    fccikt[3][1] = ((Cik[3][1][2]*fc[3][2])+((Cik[3][1][0]*fc[3][0])+(
      Cik[3][1][1]*fc[3][1])));
    fccikt[3][2] = ((Cik[3][2][2]*fc[3][2])+((Cik[3][2][0]*fc[3][0])+(
      Cik[3][2][1]*fc[3][1])));
    ffk[2][0] = -fccikt[3][0];
    ffk[2][1] = -fccikt[3][1];
    ffk[2][2] = -fccikt[3][2];
    ttk[2][0] = -((Cik[3][0][2]*tc[3][2])+((Cik[3][0][0]*tc[3][0])+(Cik[3][0][1]
      *tc[3][1])));
    ttk[2][1] = -((Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(Cik[3][1][1]
      *tc[3][1])));
    ttk[2][2] = -((Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(Cik[3][2][1]
      *tc[3][1])));
    fc[2][0] = -ffk[2][0];
    fc[2][1] = -ffk[2][1];
    fc[2][2] = -ffk[2][2];
    tc[2][0] = -ttk[2][0];
    tc[2][1] = -ttk[2][1];
    tc[2][2] = -ttk[2][2];
    fccikt[2][0] = fc[2][0];
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -(tc[2][0]+((fccikt[2][2]*rpp[2][1])-(fccikt[2][1]*rpp[2][2])));
    ttk[1][1] = -(tc[2][1]+((fccikt[2][0]*rpp[2][2])-(fccikt[2][2]*rpp[2][0])));
    ttk[1][2] = -(tc[2][2]+((fccikt[2][1]*rpp[2][0])-(fccikt[2][0]*rpp[2][1])));
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
    ttk[0][0] = -(tc[1][0]+((fccikt[1][2]*rpp[1][1])-(fccikt[1][1]*rpp[1][2])));
    ttk[0][1] = -(tc[1][1]+((fccikt[1][0]*rpp[1][2])-(fccikt[1][2]*rpp[1][0])));
    ttk[0][2] = -(tc[1][2]+((fccikt[1][1]*rpp[1][0])-(fccikt[1][0]*rpp[1][1])));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[5][0];
    torque[0][0] = tc[5][0];
    force[0][1] = fc[5][1];
    torque[0][1] = tc[5][1];
    force[0][2] = fc[5][2];
    torque[0][2] = tc[5][2];
    force[1][0] = fc[8][0];
    torque[1][0] = tc[8][0];
    force[1][1] = fc[8][1];
    torque[1][1] = tc[8][1];
    force[1][2] = fc[8][2];
    torque[1][2] = tc[8][2];
    force[2][0] = fc[11][0];
    torque[2][0] = tc[11][0];
    force[2][1] = fc[11][1];
    torque[2][1] = tc[11][1];
    force[2][2] = fc[11][2];
    torque[2][2] = tc[11][2];
    force[3][0] = fc[14][0];
    torque[3][0] = tc[14][0];
    force[3][1] = fc[14][1];
    torque[3][1] = tc[14][1];
    force[3][2] = fc[14][2];
    torque[3][2] = tc[14][2];
    force[4][0] = fc[17][0];
    torque[4][0] = tc[17][0];
    force[4][1] = fc[17][1];
    torque[4][1] = tc[17][1];
    force[4][2] = fc[17][2];
    torque[4][2] = tc[17][2];
    force[5][0] = fc[20][0];
    torque[5][0] = tc[20][0];
    force[5][1] = fc[20][1];
    torque[5][1] = tc[20][1];
    force[5][2] = fc[20][2];
    torque[5][2] = tc[20][2];
    force[6][0] = fc[23][0];
    torque[6][0] = tc[23][0];
    force[6][1] = fc[23][1];
    torque[6][1] = tc[23][1];
    force[6][2] = fc[23][2];
    torque[6][2] = tc[23][2];
    force[7][0] = fc[26][0];
    torque[7][0] = tc[26][0];
    force[7][1] = fc[26][1];
    torque[7][1] = tc[26][1];
    force[7][2] = fc[26][2];
    torque[7][2] = tc[26][2];
    force[8][0] = fc[29][0];
    torque[8][0] = tc[29][0];
    force[8][1] = fc[29][1];
    torque[8][1] = tc[29][1];
    force[8][2] = fc[29][2];
    torque[8][2] = tc[29][2];
    force[9][0] = fc[32][0];
    torque[9][0] = tc[32][0];
    force[9][1] = fc[32][1];
    torque[9][1] = tc[32][1];
    force[9][2] = fc[32][2];
    torque[9][2] = tc[32][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  870 adds/subtracts/negates
                    648 multiplies
                      0 divides
                    546 assignments
*/
}

void sdmom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 15-Feb-2006 17:06:53 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[10][3],hnk[10][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lm[0] = ((.205126*vnk[32][0])+((1.2*vnk[29][0])+((3.51*vnk[26][0])+((8.806*
      vnk[23][0])+((.205126*vnk[20][0])+((1.2*vnk[17][0])+((3.51*vnk[14][0])+((
      8.806*vnk[11][0])+((11.15*vnk[2][0])+(32.413*vnk[8][0]))))))))));
    lm[1] = ((.205126*vnk[32][1])+((1.2*vnk[29][1])+((3.51*vnk[26][1])+((8.806*
      vnk[23][1])+((.205126*vnk[20][1])+((1.2*vnk[17][1])+((3.51*vnk[14][1])+((
      8.806*vnk[11][1])+((11.15*vnk[2][1])+(32.413*vnk[8][1]))))))))));
    lm[2] = ((.205126*vnk[32][2])+((1.2*vnk[29][2])+((3.51*vnk[26][2])+((8.806*
      vnk[23][2])+((.205126*vnk[20][2])+((1.2*vnk[17][2])+((3.51*vnk[14][2])+((
      8.806*vnk[11][2])+((11.15*vnk[2][2])+(32.413*vnk[8][2]))))))))));
    temp[0] = (((11.15*((rnk[2][1]*vnk[2][2])-(rnk[2][2]*vnk[2][1])))+((.0548*(
      Cik[3][0][2]*u[5]))+((.0825*(Cik[3][0][1]*u[4]))+(.0973*(Cik[3][0][0]*u[3]
      )))))+((32.413*((rnk[8][1]*vnk[8][2])-(rnk[8][2]*vnk[8][1])))+((1.3552*(
      cnk[8][0][2]*wk[8][2]))+((.7153*(cnk[8][0][1]*wk[8][1]))+(1.396*(
      cnk[8][0][0]*wk[8][0]))))));
    temp[1] = (((3.51*((rnk[14][1]*vnk[14][2])-(rnk[14][2]*vnk[14][1])))+((.0484
      *(cnk[14][0][2]*wk[14][2]))+((.0048*(cnk[14][0][1]*wk[14][1]))+(.0477*(
      cnk[14][0][0]*wk[14][0])))))+(((8.806*((rnk[11][1]*vnk[11][2])-(rnk[11][2]
      *vnk[11][1])))+((.1337*(cnk[11][0][2]*wk[11][2]))+((.0332*(cnk[11][0][1]*
      wk[11][1]))+(.1268*(cnk[11][0][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[20][1]*vnk[20][2])-(rnk[20][2]*vnk[20][1])))+((
      .000119*(cnk[20][0][2]*wk[20][2]))+((.000117*(cnk[20][0][0]*wk[20][0]))+(
      .000179*(cnk[20][0][1]*wk[20][1])))))+(((1.2*((rnk[17][1]*vnk[17][2])-(
      rnk[17][2]*vnk[17][1])))+((.003916*(cnk[17][0][2]*wk[17][2]))+((.001361*(
      cnk[17][0][0]*wk[17][0]))+(.003709*(cnk[17][0][1]*wk[17][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[26][1]*vnk[26][2])-(rnk[26][2]*vnk[26][1])))+((.0484
      *(cnk[26][0][2]*wk[26][2]))+((.0048*(cnk[26][0][1]*wk[26][1]))+(.0477*(
      cnk[26][0][0]*wk[26][0])))))+(((8.806*((rnk[23][1]*vnk[23][2])-(rnk[23][2]
      *vnk[23][1])))+((.1337*(cnk[23][0][2]*wk[23][2]))+((.0332*(cnk[23][0][1]*
      wk[23][1]))+(.1268*(cnk[23][0][0]*wk[23][0])))))+temp[2]));
    am[0] = ((((.205126*((rnk[32][1]*vnk[32][2])-(rnk[32][2]*vnk[32][1])))+((
      .000119*(cnk[32][0][2]*wk[32][2]))+((.000117*(cnk[32][0][0]*wk[32][0]))+(
      .000179*(cnk[32][0][1]*wk[32][1])))))+(((1.2*((rnk[29][1]*vnk[29][2])-(
      rnk[29][2]*vnk[29][1])))+((.003916*(cnk[29][0][2]*wk[29][2]))+((.001361*(
      cnk[29][0][0]*wk[29][0]))+(.003709*(cnk[29][0][1]*wk[29][1])))))+temp[3]))
      -((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = (((11.15*((rnk[2][2]*vnk[2][0])-(rnk[2][0]*vnk[2][2])))+((.0548*(
      Cik[3][1][2]*u[5]))+((.0825*(Cik[3][1][1]*u[4]))+(.0973*(Cik[3][1][0]*u[3]
      )))))+((32.413*((rnk[8][2]*vnk[8][0])-(rnk[8][0]*vnk[8][2])))+((1.3552*(
      cnk[8][1][2]*wk[8][2]))+((.7153*(cnk[8][1][1]*wk[8][1]))+(1.396*(
      cnk[8][1][0]*wk[8][0]))))));
    temp[1] = (((3.51*((rnk[14][2]*vnk[14][0])-(rnk[14][0]*vnk[14][2])))+((.0484
      *(cnk[14][1][2]*wk[14][2]))+((.0048*(cnk[14][1][1]*wk[14][1]))+(.0477*(
      cnk[14][1][0]*wk[14][0])))))+(((8.806*((rnk[11][2]*vnk[11][0])-(rnk[11][0]
      *vnk[11][2])))+((.1337*(cnk[11][1][2]*wk[11][2]))+((.0332*(cnk[11][1][1]*
      wk[11][1]))+(.1268*(cnk[11][1][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[20][2]*vnk[20][0])-(rnk[20][0]*vnk[20][2])))+((
      .000119*(cnk[20][1][2]*wk[20][2]))+((.000117*(cnk[20][1][0]*wk[20][0]))+(
      .000179*(cnk[20][1][1]*wk[20][1])))))+(((1.2*((rnk[17][2]*vnk[17][0])-(
      rnk[17][0]*vnk[17][2])))+((.003916*(cnk[17][1][2]*wk[17][2]))+((.001361*(
      cnk[17][1][0]*wk[17][0]))+(.003709*(cnk[17][1][1]*wk[17][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[26][2]*vnk[26][0])-(rnk[26][0]*vnk[26][2])))+((.0484
      *(cnk[26][1][2]*wk[26][2]))+((.0048*(cnk[26][1][1]*wk[26][1]))+(.0477*(
      cnk[26][1][0]*wk[26][0])))))+(((8.806*((rnk[23][2]*vnk[23][0])-(rnk[23][0]
      *vnk[23][2])))+((.1337*(cnk[23][1][2]*wk[23][2]))+((.0332*(cnk[23][1][1]*
      wk[23][1]))+(.1268*(cnk[23][1][0]*wk[23][0])))))+temp[2]));
    am[1] = ((((.205126*((rnk[32][2]*vnk[32][0])-(rnk[32][0]*vnk[32][2])))+((
      .000119*(cnk[32][1][2]*wk[32][2]))+((.000117*(cnk[32][1][0]*wk[32][0]))+(
      .000179*(cnk[32][1][1]*wk[32][1])))))+(((1.2*((rnk[29][2]*vnk[29][0])-(
      rnk[29][0]*vnk[29][2])))+((.003916*(cnk[29][1][2]*wk[29][2]))+((.001361*(
      cnk[29][1][0]*wk[29][0]))+(.003709*(cnk[29][1][1]*wk[29][1])))))+temp[3]))
      -((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = (((11.15*((rnk[2][0]*vnk[2][1])-(rnk[2][1]*vnk[2][0])))+((.0548*(
      Cik[3][2][2]*u[5]))+((.0825*(Cik[3][2][1]*u[4]))+(.0973*(Cik[3][2][0]*u[3]
      )))))+((32.413*((rnk[8][0]*vnk[8][1])-(rnk[8][1]*vnk[8][0])))+((1.3552*(
      cnk[8][2][2]*wk[8][2]))+((.7153*(cnk[8][2][1]*wk[8][1]))+(1.396*(
      cnk[8][2][0]*wk[8][0]))))));
    temp[1] = (((3.51*((rnk[14][0]*vnk[14][1])-(rnk[14][1]*vnk[14][0])))+((.0484
      *(cnk[14][2][2]*wk[14][2]))+((.0048*(cnk[14][2][1]*wk[14][1]))+(.0477*(
      cnk[14][2][0]*wk[14][0])))))+(((8.806*((rnk[11][0]*vnk[11][1])-(rnk[11][1]
      *vnk[11][0])))+((.1337*(cnk[11][2][2]*wk[11][2]))+((.0332*(cnk[11][2][1]*
      wk[11][1]))+(.1268*(cnk[11][2][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[20][0]*vnk[20][1])-(rnk[20][1]*vnk[20][0])))+((
      .000119*(cnk[20][2][2]*wk[20][2]))+((.000117*(cnk[20][2][0]*wk[20][0]))+(
      .000179*(cnk[20][2][1]*wk[20][1])))))+(((1.2*((rnk[17][0]*vnk[17][1])-(
      rnk[17][1]*vnk[17][0])))+((.003916*(cnk[17][2][2]*wk[17][2]))+((.001361*(
      cnk[17][2][0]*wk[17][0]))+(.003709*(cnk[17][2][1]*wk[17][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[26][0]*vnk[26][1])-(rnk[26][1]*vnk[26][0])))+((.0484
      *(cnk[26][2][2]*wk[26][2]))+((.0048*(cnk[26][2][1]*wk[26][1]))+(.0477*(
      cnk[26][2][0]*wk[26][0])))))+(((8.806*((rnk[23][0]*vnk[23][1])-(rnk[23][1]
      *vnk[23][0])))+((.1337*(cnk[23][2][2]*wk[23][2]))+((.0332*(cnk[23][2][1]*
      wk[23][1]))+(.1268*(cnk[23][2][0]*wk[23][0])))))+temp[2]));
    am[2] = ((((.205126*((rnk[32][0]*vnk[32][1])-(rnk[32][1]*vnk[32][0])))+((
      .000119*(cnk[32][2][2]*wk[32][2]))+((.000117*(cnk[32][2][0]*wk[32][0]))+(
      .000179*(cnk[32][2][1]*wk[32][1])))))+(((1.2*((rnk[29][0]*vnk[29][1])-(
      rnk[29][1]*vnk[29][0])))+((.003916*(cnk[29][2][2]*wk[29][2]))+((.001361*(
      cnk[29][2][0]*wk[29][0]))+(.003709*(cnk[29][2][1]*wk[29][1])))))+temp[3]))
      -((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = (((11.15*((vnk[2][2]*vnk[2][2])+((vnk[2][0]*vnk[2][0])+(vnk[2][1]*
      vnk[2][1]))))+((.0548*(u[5]*u[5]))+((.0825*(u[4]*u[4]))+(.0973*(u[3]*u[3])
      ))))+((32.413*((vnk[8][2]*vnk[8][2])+((vnk[8][0]*vnk[8][0])+(vnk[8][1]*
      vnk[8][1]))))+((1.3552*(wk[8][2]*wk[8][2]))+((.7153*(wk[8][1]*wk[8][1]))+(
      1.396*(wk[8][0]*wk[8][0]))))));
    temp[1] = (((3.51*((vnk[14][2]*vnk[14][2])+((vnk[14][0]*vnk[14][0])+(
      vnk[14][1]*vnk[14][1]))))+((.0484*(wk[14][2]*wk[14][2]))+((.0048*(
      wk[14][1]*wk[14][1]))+(.0477*(wk[14][0]*wk[14][0])))))+(((8.806*((
      vnk[11][2]*vnk[11][2])+((vnk[11][0]*vnk[11][0])+(vnk[11][1]*vnk[11][1]))))
      +((.1337*(wk[11][2]*wk[11][2]))+((.0332*(wk[11][1]*wk[11][1]))+(.1268*(
      wk[11][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((vnk[20][2]*vnk[20][2])+((vnk[20][0]*vnk[20][0])+(
      vnk[20][1]*vnk[20][1]))))+((.000119*(wk[20][2]*wk[20][2]))+((.000117*(
      wk[20][0]*wk[20][0]))+(.000179*(wk[20][1]*wk[20][1])))))+(((1.2*((
      vnk[17][2]*vnk[17][2])+((vnk[17][0]*vnk[17][0])+(vnk[17][1]*vnk[17][1]))))
      +((.003916*(wk[17][2]*wk[17][2]))+((.001361*(wk[17][0]*wk[17][0]))+(
      .003709*(wk[17][1]*wk[17][1])))))+temp[1]));
    temp[3] = (((3.51*((vnk[26][2]*vnk[26][2])+((vnk[26][0]*vnk[26][0])+(
      vnk[26][1]*vnk[26][1]))))+((.0484*(wk[26][2]*wk[26][2]))+((.0048*(
      wk[26][1]*wk[26][1]))+(.0477*(wk[26][0]*wk[26][0])))))+(((8.806*((
      vnk[23][2]*vnk[23][2])+((vnk[23][0]*vnk[23][0])+(vnk[23][1]*vnk[23][1]))))
      +((.1337*(wk[23][2]*wk[23][2]))+((.0332*(wk[23][1]*wk[23][1]))+(.1268*(
      wk[23][0]*wk[23][0])))))+temp[2]));
    *ke = (.5*(((.205126*((vnk[32][2]*vnk[32][2])+((vnk[32][0]*vnk[32][0])+(
      vnk[32][1]*vnk[32][1]))))+((.000119*(wk[32][2]*wk[32][2]))+((.000117*(
      wk[32][0]*wk[32][0]))+(.000179*(wk[32][1]*wk[32][1])))))+(((1.2*((
      vnk[29][2]*vnk[29][2])+((vnk[29][0]*vnk[29][0])+(vnk[29][1]*vnk[29][1]))))
      +((.003916*(wk[29][2]*wk[29][2]))+((.001361*(wk[29][0]*wk[29][0]))+(
      .003709*(wk[29][1]*wk[29][1])))))+temp[3])));
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  239 adds/subtracts/negates
                    407 multiplies
                      0 divides
                     23 assignments
*/
}

void sdsys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 15-Feb-2006 17:06:53 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[33][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = 71.005252;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    temp[0] = (((11.15*((rnk[2][1]*rnk[2][1])+(rnk[2][2]*rnk[2][2])))+((.0548*(
      Cik[3][0][2]*Cik[3][0][2]))+((.0825*(Cik[3][0][1]*Cik[3][0][1]))+(.0973*(
      Cik[3][0][0]*Cik[3][0][0])))))+((32.413*((rnk[8][1]*rnk[8][1])+(rnk[8][2]*
      rnk[8][2])))+((1.3552*(cnk[8][0][2]*cnk[8][0][2]))+((.7153*(cnk[8][0][1]*
      cnk[8][0][1]))+(1.396*(cnk[8][0][0]*cnk[8][0][0]))))));
    temp[1] = (((3.51*((rnk[14][1]*rnk[14][1])+(rnk[14][2]*rnk[14][2])))+((.0484
      *(cnk[14][0][2]*cnk[14][0][2]))+((.0048*(cnk[14][0][1]*cnk[14][0][1]))+(
      .0477*(cnk[14][0][0]*cnk[14][0][0])))))+(((8.806*((rnk[11][1]*rnk[11][1])+
      (rnk[11][2]*rnk[11][2])))+((.1337*(cnk[11][0][2]*cnk[11][0][2]))+((.0332*(
      cnk[11][0][1]*cnk[11][0][1]))+(.1268*(cnk[11][0][0]*cnk[11][0][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[20][1]*rnk[20][1])+(rnk[20][2]*rnk[20][2])))+((
      .000119*(cnk[20][0][2]*cnk[20][0][2]))+((.000117*(cnk[20][0][0]*
      cnk[20][0][0]))+(.000179*(cnk[20][0][1]*cnk[20][0][1])))))+(((1.2*((
      rnk[17][1]*rnk[17][1])+(rnk[17][2]*rnk[17][2])))+((.003916*(cnk[17][0][2]*
      cnk[17][0][2]))+((.001361*(cnk[17][0][0]*cnk[17][0][0]))+(.003709*(
      cnk[17][0][1]*cnk[17][0][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[26][1]*rnk[26][1])+(rnk[26][2]*rnk[26][2])))+((.0484
      *(cnk[26][0][2]*cnk[26][0][2]))+((.0048*(cnk[26][0][1]*cnk[26][0][1]))+(
      .0477*(cnk[26][0][0]*cnk[26][0][0])))))+(((8.806*((rnk[23][1]*rnk[23][1])+
      (rnk[23][2]*rnk[23][2])))+((.1337*(cnk[23][0][2]*cnk[23][0][2]))+((.0332*(
      cnk[23][0][1]*cnk[23][0][1]))+(.1268*(cnk[23][0][0]*cnk[23][0][0])))))+
      temp[2]));
    icm[0][0] = ((((.205126*((rnk[32][1]*rnk[32][1])+(rnk[32][2]*rnk[32][2])))+(
      (.000119*(cnk[32][0][2]*cnk[32][0][2]))+((.000117*(cnk[32][0][0]*
      cnk[32][0][0]))+(.000179*(cnk[32][0][1]*cnk[32][0][1])))))+(((1.2*((
      rnk[29][1]*rnk[29][1])+(rnk[29][2]*rnk[29][2])))+((.003916*(cnk[29][0][2]*
      cnk[29][0][2]))+((.001361*(cnk[29][0][0]*cnk[29][0][0]))+(.003709*(
      cnk[29][0][1]*cnk[29][0][1])))))+temp[3]))-(71.005252*((com[1]*com[1])+(
      com[2]*com[2]))));
    temp[0] = ((((.0548*(Cik[3][0][2]*Cik[3][1][2]))+((.0825*(Cik[3][0][1]*
      Cik[3][1][1]))+(.0973*(Cik[3][0][0]*Cik[3][1][0]))))-(11.15*(rnk[2][0]*
      rnk[2][1])))+(((1.3552*(cnk[8][0][2]*cnk[8][1][2]))+((.7153*(cnk[8][0][1]*
      cnk[8][1][1]))+(1.396*(cnk[8][0][0]*cnk[8][1][0]))))-(32.413*(rnk[8][0]*
      rnk[8][1]))));
    temp[1] = ((((.0484*(cnk[14][0][2]*cnk[14][1][2]))+((.0048*(cnk[14][0][1]*
      cnk[14][1][1]))+(.0477*(cnk[14][0][0]*cnk[14][1][0]))))-(3.51*(rnk[14][0]*
      rnk[14][1])))+((((.1337*(cnk[11][0][2]*cnk[11][1][2]))+((.0332*(
      cnk[11][0][1]*cnk[11][1][1]))+(.1268*(cnk[11][0][0]*cnk[11][1][0]))))-(
      8.806*(rnk[11][0]*rnk[11][1])))+temp[0]));
    temp[2] = ((((.000119*(cnk[20][0][2]*cnk[20][1][2]))+((.000117*(
      cnk[20][0][0]*cnk[20][1][0]))+(.000179*(cnk[20][0][1]*cnk[20][1][1]))))-(
      .205126*(rnk[20][0]*rnk[20][1])))+((((.003916*(cnk[17][0][2]*cnk[17][1][2]
      ))+((.001361*(cnk[17][0][0]*cnk[17][1][0]))+(.003709*(cnk[17][0][1]*
      cnk[17][1][1]))))-(1.2*(rnk[17][0]*rnk[17][1])))+temp[1]));
    temp[3] = ((((.0484*(cnk[26][0][2]*cnk[26][1][2]))+((.0048*(cnk[26][0][1]*
      cnk[26][1][1]))+(.0477*(cnk[26][0][0]*cnk[26][1][0]))))-(3.51*(rnk[26][0]*
      rnk[26][1])))+((((.1337*(cnk[23][0][2]*cnk[23][1][2]))+((.0332*(
      cnk[23][0][1]*cnk[23][1][1]))+(.1268*(cnk[23][0][0]*cnk[23][1][0]))))-(
      8.806*(rnk[23][0]*rnk[23][1])))+temp[2]));
    icm[0][1] = ((71.005252*(com[0]*com[1]))+((((.000119*(cnk[32][0][2]*
      cnk[32][1][2]))+((.000117*(cnk[32][0][0]*cnk[32][1][0]))+(.000179*(
      cnk[32][0][1]*cnk[32][1][1]))))-(.205126*(rnk[32][0]*rnk[32][1])))+((((
      .003916*(cnk[29][0][2]*cnk[29][1][2]))+((.001361*(cnk[29][0][0]*
      cnk[29][1][0]))+(.003709*(cnk[29][0][1]*cnk[29][1][1]))))-(1.2*(rnk[29][0]
      *rnk[29][1])))+temp[3])));
    temp[0] = ((((.0548*(Cik[3][0][2]*Cik[3][2][2]))+((.0825*(Cik[3][0][1]*
      Cik[3][2][1]))+(.0973*(Cik[3][0][0]*Cik[3][2][0]))))-(11.15*(rnk[2][0]*
      rnk[2][2])))+(((1.3552*(cnk[8][0][2]*cnk[8][2][2]))+((.7153*(cnk[8][0][1]*
      cnk[8][2][1]))+(1.396*(cnk[8][0][0]*cnk[8][2][0]))))-(32.413*(rnk[8][0]*
      rnk[8][2]))));
    temp[1] = ((((.0484*(cnk[14][0][2]*cnk[14][2][2]))+((.0048*(cnk[14][0][1]*
      cnk[14][2][1]))+(.0477*(cnk[14][0][0]*cnk[14][2][0]))))-(3.51*(rnk[14][0]*
      rnk[14][2])))+((((.1337*(cnk[11][0][2]*cnk[11][2][2]))+((.0332*(
      cnk[11][0][1]*cnk[11][2][1]))+(.1268*(cnk[11][0][0]*cnk[11][2][0]))))-(
      8.806*(rnk[11][0]*rnk[11][2])))+temp[0]));
    temp[2] = ((((.000119*(cnk[20][0][2]*cnk[20][2][2]))+((.000117*(
      cnk[20][0][0]*cnk[20][2][0]))+(.000179*(cnk[20][0][1]*cnk[20][2][1]))))-(
      .205126*(rnk[20][0]*rnk[20][2])))+((((.003916*(cnk[17][0][2]*cnk[17][2][2]
      ))+((.001361*(cnk[17][0][0]*cnk[17][2][0]))+(.003709*(cnk[17][0][1]*
      cnk[17][2][1]))))-(1.2*(rnk[17][0]*rnk[17][2])))+temp[1]));
    temp[3] = ((((.0484*(cnk[26][0][2]*cnk[26][2][2]))+((.0048*(cnk[26][0][1]*
      cnk[26][2][1]))+(.0477*(cnk[26][0][0]*cnk[26][2][0]))))-(3.51*(rnk[26][0]*
      rnk[26][2])))+((((.1337*(cnk[23][0][2]*cnk[23][2][2]))+((.0332*(
      cnk[23][0][1]*cnk[23][2][1]))+(.1268*(cnk[23][0][0]*cnk[23][2][0]))))-(
      8.806*(rnk[23][0]*rnk[23][2])))+temp[2]));
    icm[0][2] = ((71.005252*(com[0]*com[2]))+((((.000119*(cnk[32][0][2]*
      cnk[32][2][2]))+((.000117*(cnk[32][0][0]*cnk[32][2][0]))+(.000179*(
      cnk[32][0][1]*cnk[32][2][1]))))-(.205126*(rnk[32][0]*rnk[32][2])))+((((
      .003916*(cnk[29][0][2]*cnk[29][2][2]))+((.001361*(cnk[29][0][0]*
      cnk[29][2][0]))+(.003709*(cnk[29][0][1]*cnk[29][2][1]))))-(1.2*(rnk[29][0]
      *rnk[29][2])))+temp[3])));
    icm[1][0] = icm[0][1];
    temp[0] = (((11.15*((rnk[2][0]*rnk[2][0])+(rnk[2][2]*rnk[2][2])))+((.0548*(
      Cik[3][1][2]*Cik[3][1][2]))+((.0825*(Cik[3][1][1]*Cik[3][1][1]))+(.0973*(
      Cik[3][1][0]*Cik[3][1][0])))))+((32.413*((rnk[8][0]*rnk[8][0])+(rnk[8][2]*
      rnk[8][2])))+((1.3552*(cnk[8][1][2]*cnk[8][1][2]))+((.7153*(cnk[8][1][1]*
      cnk[8][1][1]))+(1.396*(cnk[8][1][0]*cnk[8][1][0]))))));
    temp[1] = (((3.51*((rnk[14][0]*rnk[14][0])+(rnk[14][2]*rnk[14][2])))+((.0484
      *(cnk[14][1][2]*cnk[14][1][2]))+((.0048*(cnk[14][1][1]*cnk[14][1][1]))+(
      .0477*(cnk[14][1][0]*cnk[14][1][0])))))+(((8.806*((rnk[11][0]*rnk[11][0])+
      (rnk[11][2]*rnk[11][2])))+((.1337*(cnk[11][1][2]*cnk[11][1][2]))+((.0332*(
      cnk[11][1][1]*cnk[11][1][1]))+(.1268*(cnk[11][1][0]*cnk[11][1][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[20][0]*rnk[20][0])+(rnk[20][2]*rnk[20][2])))+((
      .000119*(cnk[20][1][2]*cnk[20][1][2]))+((.000117*(cnk[20][1][0]*
      cnk[20][1][0]))+(.000179*(cnk[20][1][1]*cnk[20][1][1])))))+(((1.2*((
      rnk[17][0]*rnk[17][0])+(rnk[17][2]*rnk[17][2])))+((.003916*(cnk[17][1][2]*
      cnk[17][1][2]))+((.001361*(cnk[17][1][0]*cnk[17][1][0]))+(.003709*(
      cnk[17][1][1]*cnk[17][1][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[26][0]*rnk[26][0])+(rnk[26][2]*rnk[26][2])))+((.0484
      *(cnk[26][1][2]*cnk[26][1][2]))+((.0048*(cnk[26][1][1]*cnk[26][1][1]))+(
      .0477*(cnk[26][1][0]*cnk[26][1][0])))))+(((8.806*((rnk[23][0]*rnk[23][0])+
      (rnk[23][2]*rnk[23][2])))+((.1337*(cnk[23][1][2]*cnk[23][1][2]))+((.0332*(
      cnk[23][1][1]*cnk[23][1][1]))+(.1268*(cnk[23][1][0]*cnk[23][1][0])))))+
      temp[2]));
    icm[1][1] = ((((.205126*((rnk[32][0]*rnk[32][0])+(rnk[32][2]*rnk[32][2])))+(
      (.000119*(cnk[32][1][2]*cnk[32][1][2]))+((.000117*(cnk[32][1][0]*
      cnk[32][1][0]))+(.000179*(cnk[32][1][1]*cnk[32][1][1])))))+(((1.2*((
      rnk[29][0]*rnk[29][0])+(rnk[29][2]*rnk[29][2])))+((.003916*(cnk[29][1][2]*
      cnk[29][1][2]))+((.001361*(cnk[29][1][0]*cnk[29][1][0]))+(.003709*(
      cnk[29][1][1]*cnk[29][1][1])))))+temp[3]))-(71.005252*((com[0]*com[0])+(
      com[2]*com[2]))));
    temp[0] = ((((.0548*(Cik[3][1][2]*Cik[3][2][2]))+((.0825*(Cik[3][1][1]*
      Cik[3][2][1]))+(.0973*(Cik[3][1][0]*Cik[3][2][0]))))-(11.15*(rnk[2][1]*
      rnk[2][2])))+(((1.3552*(cnk[8][1][2]*cnk[8][2][2]))+((.7153*(cnk[8][1][1]*
      cnk[8][2][1]))+(1.396*(cnk[8][1][0]*cnk[8][2][0]))))-(32.413*(rnk[8][1]*
      rnk[8][2]))));
    temp[1] = ((((.0484*(cnk[14][1][2]*cnk[14][2][2]))+((.0048*(cnk[14][1][1]*
      cnk[14][2][1]))+(.0477*(cnk[14][1][0]*cnk[14][2][0]))))-(3.51*(rnk[14][1]*
      rnk[14][2])))+((((.1337*(cnk[11][1][2]*cnk[11][2][2]))+((.0332*(
      cnk[11][1][1]*cnk[11][2][1]))+(.1268*(cnk[11][1][0]*cnk[11][2][0]))))-(
      8.806*(rnk[11][1]*rnk[11][2])))+temp[0]));
    temp[2] = ((((.000119*(cnk[20][1][2]*cnk[20][2][2]))+((.000117*(
      cnk[20][1][0]*cnk[20][2][0]))+(.000179*(cnk[20][1][1]*cnk[20][2][1]))))-(
      .205126*(rnk[20][1]*rnk[20][2])))+((((.003916*(cnk[17][1][2]*cnk[17][2][2]
      ))+((.001361*(cnk[17][1][0]*cnk[17][2][0]))+(.003709*(cnk[17][1][1]*
      cnk[17][2][1]))))-(1.2*(rnk[17][1]*rnk[17][2])))+temp[1]));
    temp[3] = ((((.0484*(cnk[26][1][2]*cnk[26][2][2]))+((.0048*(cnk[26][1][1]*
      cnk[26][2][1]))+(.0477*(cnk[26][1][0]*cnk[26][2][0]))))-(3.51*(rnk[26][1]*
      rnk[26][2])))+((((.1337*(cnk[23][1][2]*cnk[23][2][2]))+((.0332*(
      cnk[23][1][1]*cnk[23][2][1]))+(.1268*(cnk[23][1][0]*cnk[23][2][0]))))-(
      8.806*(rnk[23][1]*rnk[23][2])))+temp[2]));
    icm[1][2] = ((71.005252*(com[1]*com[2]))+((((.000119*(cnk[32][1][2]*
      cnk[32][2][2]))+((.000117*(cnk[32][1][0]*cnk[32][2][0]))+(.000179*(
      cnk[32][1][1]*cnk[32][2][1]))))-(.205126*(rnk[32][1]*rnk[32][2])))+((((
      .003916*(cnk[29][1][2]*cnk[29][2][2]))+((.001361*(cnk[29][1][0]*
      cnk[29][2][0]))+(.003709*(cnk[29][1][1]*cnk[29][2][1]))))-(1.2*(rnk[29][1]
      *rnk[29][2])))+temp[3])));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((11.15*((rnk[2][0]*rnk[2][0])+(rnk[2][1]*rnk[2][1])))+((.0548*(
      Cik[3][2][2]*Cik[3][2][2]))+((.0825*(Cik[3][2][1]*Cik[3][2][1]))+(.0973*(
      Cik[3][2][0]*Cik[3][2][0])))))+((32.413*((rnk[8][0]*rnk[8][0])+(rnk[8][1]*
      rnk[8][1])))+((1.3552*(cnk[8][2][2]*cnk[8][2][2]))+((.7153*(cnk[8][2][1]*
      cnk[8][2][1]))+(1.396*(cnk[8][2][0]*cnk[8][2][0]))))));
    temp[1] = (((3.51*((rnk[14][0]*rnk[14][0])+(rnk[14][1]*rnk[14][1])))+((.0484
      *(cnk[14][2][2]*cnk[14][2][2]))+((.0048*(cnk[14][2][1]*cnk[14][2][1]))+(
      .0477*(cnk[14][2][0]*cnk[14][2][0])))))+(((8.806*((rnk[11][0]*rnk[11][0])+
      (rnk[11][1]*rnk[11][1])))+((.1337*(cnk[11][2][2]*cnk[11][2][2]))+((.0332*(
      cnk[11][2][1]*cnk[11][2][1]))+(.1268*(cnk[11][2][0]*cnk[11][2][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[20][0]*rnk[20][0])+(rnk[20][1]*rnk[20][1])))+((
      .000119*(cnk[20][2][2]*cnk[20][2][2]))+((.000117*(cnk[20][2][0]*
      cnk[20][2][0]))+(.000179*(cnk[20][2][1]*cnk[20][2][1])))))+(((1.2*((
      rnk[17][0]*rnk[17][0])+(rnk[17][1]*rnk[17][1])))+((.003916*(cnk[17][2][2]*
      cnk[17][2][2]))+((.001361*(cnk[17][2][0]*cnk[17][2][0]))+(.003709*(
      cnk[17][2][1]*cnk[17][2][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[26][0]*rnk[26][0])+(rnk[26][1]*rnk[26][1])))+((.0484
      *(cnk[26][2][2]*cnk[26][2][2]))+((.0048*(cnk[26][2][1]*cnk[26][2][1]))+(
      .0477*(cnk[26][2][0]*cnk[26][2][0])))))+(((8.806*((rnk[23][0]*rnk[23][0])+
      (rnk[23][1]*rnk[23][1])))+((.1337*(cnk[23][2][2]*cnk[23][2][2]))+((.0332*(
      cnk[23][2][1]*cnk[23][2][1]))+(.1268*(cnk[23][2][0]*cnk[23][2][0])))))+
      temp[2]));
    icm[2][2] = ((((.205126*((rnk[32][0]*rnk[32][0])+(rnk[32][1]*rnk[32][1])))+(
      (.000119*(cnk[32][2][2]*cnk[32][2][2]))+((.000117*(cnk[32][2][0]*
      cnk[32][2][0]))+(.000179*(cnk[32][2][1]*cnk[32][2][1])))))+(((1.2*((
      rnk[29][0]*rnk[29][0])+(rnk[29][1]*rnk[29][1])))+((.003916*(cnk[29][2][2]*
      cnk[29][2][2]))+((.001361*(cnk[29][2][0]*cnk[29][2][0]))+(.003709*(
      cnk[29][2][1]*cnk[29][2][1])))))+temp[3]))-(71.005252*((com[0]*com[0])+(
      com[1]*com[1]))));
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  273 adds/subtracts/negates
                    525 multiplies
                      0 divides
                     37 assignments
*/
}

void sdpos(int body,
    double pt[3],
    double loc[3])
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

void sdvel(int body,
    double pt[3],
    double velo[3])
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

void sdorient(int body,
    double dircos[3][3])
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

void sdangvel(int body,
    double avel[3])
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

void sdtrans(int frbod,
    double ivec[3],
    int tobod,
    double ovec[3])
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

void sdrel2cart(int coord,
    int body,
    double point[3],
    double linchg[3],
    double rotchg[3])
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 32)) {
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

void sdacc(int body,
    double pt[3],
    double accel[3])
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

void sdangacc(int body,
    double aacc[3])
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

void sdgrav(double gravin[3])
{

    grav[0] = gravin[0];
    gravq[0] = 3;
    grav[1] = gravin[1];
    gravq[1] = 3;
    grav[2] = gravin[2];
    gravq[2] = 3;
    roustate = 0;
}

void sdmass(int body,
    double massin)
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

void sdiner(int body,
    double inerin[3][3])
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

void sdbtj(int joint,
    double btjin[3])
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

void sditj(int joint,
    double itjin[3])
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

void sdpin(int joint,
    int pinno,
    double pinin[3])
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

void sdpres(int joint,
    int axis,
    int presin)
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

void sdconschg(void)
{

    wwflg = 0;
}

void sdstab(double velin,
    double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void sdgetgrav(double gravout[3])
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void sdgetmass(int body,
    double *massout)
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

void sdgetiner(int body,
    double inerout[3][3])
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

void sdgetbtj(int joint,
    double btjout[3])
{

    if (sdchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void sdgetitj(int joint,
    double itjout[3])
{

    if (sdchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void sdgetpin(int joint,
    int pinno,
    double pinout[3])
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

void sdgetpres(int joint,
    int axis,
    int *presout)
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

void sdgetstab(double *velout,
    double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void sdinfo(int info[50])
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
    info[11] = 33;
/* info entries from 12-49 are reserved */
}

void sdjnt(int joint,
    int info[50],
    int tran[6])
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

void sdcons(int consno,
    int info[50])
{

    if (sdchkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

void sdgentime(int *gentm)
{

    *gentm = 170640;
}
/*
Done. CPU seconds used: 13.44  Memory used: 1687552 bytes.
Equation complexity:
  sdstate:  2621 adds  3976 multiplies     1 divides  1604 assignments
  sdderiv: 94121 adds 100888 multiplies  1251 divides 105822 assignments
  sdresid:  5711 adds  7356 multiplies     0 divides  2796 assignments
  sdreac:    870 adds   648 multiplies     0 divides   546 assignments
  sdmom:     239 adds   407 multiplies     0 divides    23 assignments
  sdsys:     273 adds   525 multiplies     0 divides    37 assignments
*/
