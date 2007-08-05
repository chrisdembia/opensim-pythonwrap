/*
Generated 31-Jul-2007 11:59:36 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (gait23.sd)

Bodies        Inb
No  Name      body Joint type  Coords q         Multipliers
--- --------- ---- ----------- ---------------- -----------------------
 -1 $ground                                    |
  0 pelvis     -1  Bushing       0?  1?  2?    |
                   ...           3?  4?  5?    |  0p  1p  2p  3p  4p  5p
  1 femur_r     0  Gimbal        6?  7?  8?    |  6p  7p  8p
  2 tibia_r     1  Planar        9  10  11?    |  9p
  3 talus_r     2  Pin          12?            | 10p
  4 calcn_r     3  Pin          13?            | 11p
  5 toes_r      4  Pin          14?            | 12p
  6 femur_l     0  Gimbal       15? 16? 17?    | 13p 14p 15p
  7 tibia_l     6  Planar       18  19  20?    | 16p
  8 talus_l     7  Pin          21?            | 17p
  9 calcn_l     8  Pin          22?            | 18p
 10 toes_l      9  Pin          23?            | 19p
 11 torso       0  Gimbal       24? 25? 26?    | 20p 21p 22p

User Constraints

  0 knee_r_tx_con                              | 23
  1 knee_r_ty_con                              | 24
  2 knee_l_tx_con                              | 25
  3 knee_l_ty_con                              | 26

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[12],inb_[12],outb_[12],njntdof_[12],njntc_[12],njntp_[12],firstq_
      [12],ballq_[12],firstm_[12],firstp_[12];
    int trans_[27],firstu_[4];
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
#define firstu (sdgtopo.firstu_)

typedef struct {
    double grav_[3],mk_[12],ik_[12][3][3],pin_[27][3];
    double rk_[12][3],ri_[12][3],pres_[27],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[27];
    int gravq_[3],mkq_[12],ikq_[12][3][3],pinq_[27][3],rkq_[12][3],riq_[12][3],
      presq_[27],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[12][3],rcom_[12][3],mkrcomt_[12][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[27],psik_[27][3][3],psrcom_[27][3
      ],psrk_[27][3],psri_[27][3];
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
    double curtim_,q_[27],qn_[27],u_[27],cnk_[27][3][3],cnb_[12][3][3];
    double rnk_[27][3],vnk_[27][3],wk_[27][3],rnb_[12][3],vnb_[12][3],wb_[12][3]
      ,wbrcom_[12][3],com_[3],rnkg_[3];
    double Cik_[27][3][3],rikt_[27][3][3],Iko_[27][3][3],mkrk_[27][3][3],Cib_[12
      ][3][3];
    double Wkk_[27][3],Vkk_[27][3],dik_[27][3],rpp_[27][3],rpk_[27][3],rik_[27][
      3],rik2_[27][3];
    double rpri_[27][3],Wik_[27][3],Vik_[27][3],Wirk_[27][3],rkWkk_[27][3],
      Wkrpk_[27][3],VikWkr_[27][3];
    double perr_[27],verr_[27],aerr_[27],mult_[27],ufk_[12][3],utk_[12][3],mfk_[
      12][3],mtk_[12][3];
    double utau_[27],mtau_[27],uacc_[27],uvel_[27],upos_[27];
    double s3_,c3_,s4_,c4_,s5_,c5_,s6_,c6_,s7_,c7_,s8_,c8_,s11_,c11_,s12_,c12_,
      s13_,c13_,s14_,c14_,s15_,c15_,s16_,c16_,s17_,c17_,s20_,c20_,s21_,c21_,s22_
      ,c22_,s23_,c23_,s24_,c24_,s25_,c25_,s26_,c26_;
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

typedef struct {
    double fs0_[27],qdot_[27],Otk_[27][3],Atk_[27][3],AiOiWi_[27][3],Fstar_[27][
      3];
    double Tstar_[27][3],Fstark_[27][3],Tstark_[27][3],IkWk_[27][3],WkIkWk_[27][
      3],gk_[27][3],IkbWk_[12][3],WkIkbWk_[12][3];
    double w0w0_[12],w1w1_[12],w2w2_[12],w0w1_[12],w0w2_[12],w1w2_[12];
    double w00w11_[12],w00w22_[12],w11w22_[12],ww_[27][27],qraux_[27];
    double mm_[27][27],mlo_[27][27],mdi_[27],IkWpk_[27][27][3],works_[27],
      workss_[27][27];
    double Wpk_[27][27][3],Vpk_[27][27][3],VWri_[27][27][3];
    int wmap_[27],multmap_[27],jpvt_[27],wsiz_,wrank_;
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
    double fs_[27],udot_[27],tauc_[27],dyad_[12][3][3],fc_[27][3],tc_[27][3];
    double ank_[27][3],onk_[27][3],Onkb_[27][3],AOnkri_[27][3],Ankb_[27][3],
      AnkAtk_[27][3],anb_[12][3],onb_[12][3],dyrcom_[12][3];
    double ffk_[27][3],ttk_[27][3],fccikt_[27][3],ffkb_[12][3],ttkb_[12][3];
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
    /* nbod */ 12,
    /* ndof */ 27,
    /* ncons */ 27,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 23,
    /* nuser */ 4,
    /* jtype[0] */ 10,
    /* jtype[1] */ 3,
    /* jtype[2] */ 8,
    /* jtype[3] */ 1,
    /* jtype[4] */ 1,
    /* jtype[5] */ 1,
    /* jtype[6] */ 3,
    /* jtype[7] */ 8,
    /* jtype[8] */ 1,
    /* jtype[9] */ 1,
    /* jtype[10] */ 1,
    /* jtype[11] */ 3,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 1,
    /* inb[3] */ 2,
    /* inb[4] */ 3,
    /* inb[5] */ 4,
    /* inb[6] */ 0,
    /* inb[7] */ 6,
    /* inb[8] */ 7,
    /* inb[9] */ 8,
    /* inb[10] */ 9,
    /* inb[11] */ 0,
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
    /* outb[10] */ 10,
    /* outb[11] */ 11,
    /* njntdof[0] */ 6,
    /* njntdof[1] */ 3,
    /* njntdof[2] */ 3,
    /* njntdof[3] */ 1,
    /* njntdof[4] */ 1,
    /* njntdof[5] */ 1,
    /* njntdof[6] */ 3,
    /* njntdof[7] */ 3,
    /* njntdof[8] */ 1,
    /* njntdof[9] */ 1,
    /* njntdof[10] */ 1,
    /* njntdof[11] */ 3,
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
    /* njntc[10] */ 0,
    /* njntc[11] */ 0,
    /* njntp[0] */ 6,
    /* njntp[1] */ 3,
    /* njntp[2] */ 1,
    /* njntp[3] */ 1,
    /* njntp[4] */ 1,
    /* njntp[5] */ 1,
    /* njntp[6] */ 3,
    /* njntp[7] */ 1,
    /* njntp[8] */ 1,
    /* njntp[9] */ 1,
    /* njntp[10] */ 1,
    /* njntp[11] */ 3,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 9,
    /* firstq[3] */ 12,
    /* firstq[4] */ 13,
    /* firstq[5] */ 14,
    /* firstq[6] */ 15,
    /* firstq[7] */ 18,
    /* firstq[8] */ 21,
    /* firstq[9] */ 22,
    /* firstq[10] */ 23,
    /* firstq[11] */ 24,
    /* ballq[0] */ -104,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* ballq[7] */ -104,
    /* ballq[8] */ -104,
    /* ballq[9] */ -104,
    /* ballq[10] */ -104,
    /* ballq[11] */ -104,
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
    /* firstm[10] */ -1,
    /* firstm[11] */ -1,
    /* firstp[0] */ 0,
    /* firstp[1] */ 6,
    /* firstp[2] */ 9,
    /* firstp[3] */ 10,
    /* firstp[4] */ 11,
    /* firstp[5] */ 12,
    /* firstp[6] */ 13,
    /* firstp[7] */ 16,
    /* firstp[8] */ 17,
    /* firstp[9] */ 18,
    /* firstp[10] */ 19,
    /* firstp[11] */ 20,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* trans[8] */ 0,
    /* trans[9] */ 1,
    /* trans[10] */ 1,
    /* trans[11] */ 0,
    /* trans[12] */ 0,
    /* trans[13] */ 0,
    /* trans[14] */ 0,
    /* trans[15] */ 0,
    /* trans[16] */ 0,
    /* trans[17] */ 0,
    /* trans[18] */ 1,
    /* trans[19] */ 1,
    /* trans[20] */ 0,
    /* trans[21] */ 0,
    /* trans[22] */ 0,
    /* trans[23] */ 0,
    /* trans[24] */ 0,
    /* trans[25] */ 0,
    /* trans[26] */ 0,
    /* firstu[0] */ 23,
    /* firstu[1] */ 24,
    /* firstu[2] */ 25,
    /* firstu[3] */ 26,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ -9.80665,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 11.777,
    /* mk[1] */ 9.3014,
    /* mk[2] */ 3.7075,
    /* mk[3] */ .1,
    /* mk[4] */ 1.25,
    /* mk[5] */ .2166,
    /* mk[6] */ 9.3014,
    /* mk[7] */ 3.7075,
    /* mk[8] */ .1,
    /* mk[9] */ 1.25,
    /* mk[10] */ .2166,
    /* mk[11] */ 34.2366,

/* inertia */
    /* ik[0][0][0] */ .1028,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .0871,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ .0579,
    /* ik[1][0][0] */ .1339,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ .0351,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ .1412,
    /* ik[2][0][0] */ .0504,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ .0051,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ .0511,
    /* ik[3][0][0] */ .001,
    /* ik[3][0][1] */ 0.,
    /* ik[3][0][2] */ 0.,
    /* ik[3][1][0] */ 0.,
    /* ik[3][1][1] */ .001,
    /* ik[3][1][2] */ 0.,
    /* ik[3][2][0] */ 0.,
    /* ik[3][2][1] */ 0.,
    /* ik[3][2][2] */ .001,
    /* ik[4][0][0] */ .0014,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ .0039,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ .0041,
    /* ik[5][0][0] */ .0001,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ .0002,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ .001,
    /* ik[6][0][0] */ .1339,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ .0351,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ .1412,
    /* ik[7][0][0] */ .0504,
    /* ik[7][0][1] */ 0.,
    /* ik[7][0][2] */ 0.,
    /* ik[7][1][0] */ 0.,
    /* ik[7][1][1] */ .0051,
    /* ik[7][1][2] */ 0.,
    /* ik[7][2][0] */ 0.,
    /* ik[7][2][1] */ 0.,
    /* ik[7][2][2] */ .0511,
    /* ik[8][0][0] */ .001,
    /* ik[8][0][1] */ 0.,
    /* ik[8][0][2] */ 0.,
    /* ik[8][1][0] */ 0.,
    /* ik[8][1][1] */ .001,
    /* ik[8][1][2] */ 0.,
    /* ik[8][2][0] */ 0.,
    /* ik[8][2][1] */ 0.,
    /* ik[8][2][2] */ .001,
    /* ik[9][0][0] */ .0014,
    /* ik[9][0][1] */ 0.,
    /* ik[9][0][2] */ 0.,
    /* ik[9][1][0] */ 0.,
    /* ik[9][1][1] */ .0039,
    /* ik[9][1][2] */ 0.,
    /* ik[9][2][0] */ 0.,
    /* ik[9][2][1] */ 0.,
    /* ik[9][2][2] */ .0041,
    /* ik[10][0][0] */ .0001,
    /* ik[10][0][1] */ 0.,
    /* ik[10][0][2] */ 0.,
    /* ik[10][1][0] */ 0.,
    /* ik[10][1][1] */ .0002,
    /* ik[10][1][2] */ 0.,
    /* ik[10][2][0] */ 0.,
    /* ik[10][2][1] */ 0.,
    /* ik[10][2][2] */ .001,
    /* ik[11][0][0] */ 1.4745,
    /* ik[11][0][1] */ 0.,
    /* ik[11][0][2] */ 0.,
    /* ik[11][1][0] */ 0.,
    /* ik[11][1][1] */ .7555,
    /* ik[11][1][2] */ 0.,
    /* ik[11][2][0] */ 0.,
    /* ik[11][2][1] */ 0.,
    /* ik[11][2][2] */ 1.4314,

/* tree hinge axis vectors */
    /* pin[0][0] */ 0.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 1.,
    /* pin[1][0] */ 1.,
    /* pin[1][1] */ 0.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 1.,
    /* pin[2][2] */ 0.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 1.,
    /* pin[4][0] */ 1.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 1.,
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
    /* pin[9][0] */ 1.,
    /* pin[9][1] */ 0.,
    /* pin[9][2] */ 0.,
    /* pin[10][0] */ 0.,
    /* pin[10][1] */ 1.,
    /* pin[10][2] */ 0.,
    /* pin[11][0] */ 0.,
    /* pin[11][1] */ 0.,
    /* pin[11][2] */ 1.,
    /* pin[12][0] */ -.1050135476,
    /* pin[12][1] */ -.1740224503,
    /* pin[12][2] */ .9791263154,
    /* pin[13][0] */ .7871796069,
    /* pin[13][1] */ .6047474573,
    /* pin[13][2] */ -.1209494915,
    /* pin[14][0] */ -.5809543969,
    /* pin[14][1] */ 0.,
    /* pin[14][2] */ .8139361085,
    /* pin[15][0] */ 0.,
    /* pin[15][1] */ 0.,
    /* pin[15][2] */ 1.,
    /* pin[16][0] */ -1.,
    /* pin[16][1] */ 0.,
    /* pin[16][2] */ 0.,
    /* pin[17][0] */ 0.,
    /* pin[17][1] */ -1.,
    /* pin[17][2] */ 0.,
    /* pin[18][0] */ 1.,
    /* pin[18][1] */ 0.,
    /* pin[18][2] */ 0.,
    /* pin[19][0] */ 0.,
    /* pin[19][1] */ 1.,
    /* pin[19][2] */ 0.,
    /* pin[20][0] */ 0.,
    /* pin[20][1] */ 0.,
    /* pin[20][2] */ 1.,
    /* pin[21][0] */ .1050135476,
    /* pin[21][1] */ -.1740224503,
    /* pin[21][2] */ .9791263154,
    /* pin[22][0] */ -.7871796069,
    /* pin[22][1] */ -.6047474573,
    /* pin[22][2] */ -.1209494915,
    /* pin[23][0] */ .5809543969,
    /* pin[23][1] */ 0.,
    /* pin[23][2] */ .8139361085,
    /* pin[24][0] */ 0.,
    /* pin[24][1] */ 0.,
    /* pin[24][2] */ 1.,
    /* pin[25][0] */ 1.,
    /* pin[25][1] */ 0.,
    /* pin[25][2] */ 0.,
    /* pin[26][0] */ 0.,
    /* pin[26][1] */ 1.,
    /* pin[26][2] */ 0.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ .0707,
    /* rk[0][1] */ 0.,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ .17,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ 0.,
    /* rk[2][1] */ .1867,
    /* rk[2][2] */ 0.,
    /* rk[3][0] */ 0.,
    /* rk[3][1] */ 0.,
    /* rk[3][2] */ 0.,
    /* rk[4][0] */ -.1,
    /* rk[4][1] */ -.03,
    /* rk[4][2] */ 0.,
    /* rk[5][0] */ -.0346,
    /* rk[5][1] */ -.006,
    /* rk[5][2] */ .0175,
    /* rk[6][0] */ 0.,
    /* rk[6][1] */ .17,
    /* rk[6][2] */ 0.,
    /* rk[7][0] */ 0.,
    /* rk[7][1] */ .1867,
    /* rk[7][2] */ 0.,
    /* rk[8][0] */ 0.,
    /* rk[8][1] */ 0.,
    /* rk[8][2] */ 0.,
    /* rk[9][0] */ -.1,
    /* rk[9][1] */ -.03,
    /* rk[9][2] */ 0.,
    /* rk[10][0] */ -.0346,
    /* rk[10][1] */ -.006,
    /* rk[10][2] */ -.0175,
    /* rk[11][0] */ .03,
    /* rk[11][1] */ -.32,
    /* rk[11][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ -.0661,
    /* ri[1][2] */ .0835,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ .17,
    /* ri[2][2] */ 0.,
    /* ri[3][0] */ 0.,
    /* ri[3][1] */ -.2433,
    /* ri[3][2] */ 0.,
    /* ri[4][0] */ -.04877,
    /* ri[4][1] */ -.04195,
    /* ri[4][2] */ .00792,
    /* ri[5][0] */ .0788,
    /* ri[5][1] */ -.032,
    /* ri[5][2] */ .00108,
    /* ri[6][0] */ 0.,
    /* ri[6][1] */ -.0661,
    /* ri[6][2] */ -.0835,
    /* ri[7][0] */ 0.,
    /* ri[7][1] */ .17,
    /* ri[7][2] */ 0.,
    /* ri[8][0] */ 0.,
    /* ri[8][1] */ -.2433,
    /* ri[8][2] */ 0.,
    /* ri[9][0] */ -.04877,
    /* ri[9][1] */ -.04195,
    /* ri[9][2] */ -.00792,
    /* ri[10][0] */ .0788,
    /* ri[10][1] */ -.032,
    /* ri[10][2] */ -.00108,
    /* ri[11][0] */ -.03,
    /* ri[11][1] */ .0815,
    /* ri[11][2] */ 0.,

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

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 3,
    /* gravq[1] */ 3,
    /* gravq[2] */ 3,
    /* mkq[0] */ 3,
    /* mkq[1] */ 3,
    /* mkq[2] */ 3,
    /* mkq[3] */ 3,
    /* mkq[4] */ 3,
    /* mkq[5] */ 3,
    /* mkq[6] */ 3,
    /* mkq[7] */ 3,
    /* mkq[8] */ 3,
    /* mkq[9] */ 3,
    /* mkq[10] */ 3,
    /* mkq[11] */ 3,
    /* ikq[0][0][0] */ 3,
    /* ikq[0][0][1] */ 3,
    /* ikq[0][0][2] */ 3,
    /* ikq[0][1][0] */ 3,
    /* ikq[0][1][1] */ 3,
    /* ikq[0][1][2] */ 3,
    /* ikq[0][2][0] */ 3,
    /* ikq[0][2][1] */ 3,
    /* ikq[0][2][2] */ 3,
    /* ikq[1][0][0] */ 3,
    /* ikq[1][0][1] */ 3,
    /* ikq[1][0][2] */ 3,
    /* ikq[1][1][0] */ 3,
    /* ikq[1][1][1] */ 3,
    /* ikq[1][1][2] */ 3,
    /* ikq[1][2][0] */ 3,
    /* ikq[1][2][1] */ 3,
    /* ikq[1][2][2] */ 3,
    /* ikq[2][0][0] */ 3,
    /* ikq[2][0][1] */ 3,
    /* ikq[2][0][2] */ 3,
    /* ikq[2][1][0] */ 3,
    /* ikq[2][1][1] */ 3,
    /* ikq[2][1][2] */ 3,
    /* ikq[2][2][0] */ 3,
    /* ikq[2][2][1] */ 3,
    /* ikq[2][2][2] */ 3,
    /* ikq[3][0][0] */ 3,
    /* ikq[3][0][1] */ 3,
    /* ikq[3][0][2] */ 3,
    /* ikq[3][1][0] */ 3,
    /* ikq[3][1][1] */ 3,
    /* ikq[3][1][2] */ 3,
    /* ikq[3][2][0] */ 3,
    /* ikq[3][2][1] */ 3,
    /* ikq[3][2][2] */ 3,
    /* ikq[4][0][0] */ 3,
    /* ikq[4][0][1] */ 3,
    /* ikq[4][0][2] */ 3,
    /* ikq[4][1][0] */ 3,
    /* ikq[4][1][1] */ 3,
    /* ikq[4][1][2] */ 3,
    /* ikq[4][2][0] */ 3,
    /* ikq[4][2][1] */ 3,
    /* ikq[4][2][2] */ 3,
    /* ikq[5][0][0] */ 3,
    /* ikq[5][0][1] */ 3,
    /* ikq[5][0][2] */ 3,
    /* ikq[5][1][0] */ 3,
    /* ikq[5][1][1] */ 3,
    /* ikq[5][1][2] */ 3,
    /* ikq[5][2][0] */ 3,
    /* ikq[5][2][1] */ 3,
    /* ikq[5][2][2] */ 3,
    /* ikq[6][0][0] */ 3,
    /* ikq[6][0][1] */ 3,
    /* ikq[6][0][2] */ 3,
    /* ikq[6][1][0] */ 3,
    /* ikq[6][1][1] */ 3,
    /* ikq[6][1][2] */ 3,
    /* ikq[6][2][0] */ 3,
    /* ikq[6][2][1] */ 3,
    /* ikq[6][2][2] */ 3,
    /* ikq[7][0][0] */ 3,
    /* ikq[7][0][1] */ 3,
    /* ikq[7][0][2] */ 3,
    /* ikq[7][1][0] */ 3,
    /* ikq[7][1][1] */ 3,
    /* ikq[7][1][2] */ 3,
    /* ikq[7][2][0] */ 3,
    /* ikq[7][2][1] */ 3,
    /* ikq[7][2][2] */ 3,
    /* ikq[8][0][0] */ 3,
    /* ikq[8][0][1] */ 3,
    /* ikq[8][0][2] */ 3,
    /* ikq[8][1][0] */ 3,
    /* ikq[8][1][1] */ 3,
    /* ikq[8][1][2] */ 3,
    /* ikq[8][2][0] */ 3,
    /* ikq[8][2][1] */ 3,
    /* ikq[8][2][2] */ 3,
    /* ikq[9][0][0] */ 3,
    /* ikq[9][0][1] */ 3,
    /* ikq[9][0][2] */ 3,
    /* ikq[9][1][0] */ 3,
    /* ikq[9][1][1] */ 3,
    /* ikq[9][1][2] */ 3,
    /* ikq[9][2][0] */ 3,
    /* ikq[9][2][1] */ 3,
    /* ikq[9][2][2] */ 3,
    /* ikq[10][0][0] */ 3,
    /* ikq[10][0][1] */ 3,
    /* ikq[10][0][2] */ 3,
    /* ikq[10][1][0] */ 3,
    /* ikq[10][1][1] */ 3,
    /* ikq[10][1][2] */ 3,
    /* ikq[10][2][0] */ 3,
    /* ikq[10][2][1] */ 3,
    /* ikq[10][2][2] */ 3,
    /* ikq[11][0][0] */ 3,
    /* ikq[11][0][1] */ 3,
    /* ikq[11][0][2] */ 3,
    /* ikq[11][1][0] */ 3,
    /* ikq[11][1][1] */ 3,
    /* ikq[11][1][2] */ 3,
    /* ikq[11][2][0] */ 3,
    /* ikq[11][2][1] */ 3,
    /* ikq[11][2][2] */ 3,
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
    /* rkq[0][0] */ 3,
    /* rkq[0][1] */ 3,
    /* rkq[0][2] */ 3,
    /* rkq[1][0] */ 3,
    /* rkq[1][1] */ 3,
    /* rkq[1][2] */ 3,
    /* rkq[2][0] */ 3,
    /* rkq[2][1] */ 3,
    /* rkq[2][2] */ 3,
    /* rkq[3][0] */ 3,
    /* rkq[3][1] */ 3,
    /* rkq[3][2] */ 3,
    /* rkq[4][0] */ 3,
    /* rkq[4][1] */ 3,
    /* rkq[4][2] */ 3,
    /* rkq[5][0] */ 3,
    /* rkq[5][1] */ 3,
    /* rkq[5][2] */ 3,
    /* rkq[6][0] */ 3,
    /* rkq[6][1] */ 3,
    /* rkq[6][2] */ 3,
    /* rkq[7][0] */ 3,
    /* rkq[7][1] */ 3,
    /* rkq[7][2] */ 3,
    /* rkq[8][0] */ 3,
    /* rkq[8][1] */ 3,
    /* rkq[8][2] */ 3,
    /* rkq[9][0] */ 3,
    /* rkq[9][1] */ 3,
    /* rkq[9][2] */ 3,
    /* rkq[10][0] */ 3,
    /* rkq[10][1] */ 3,
    /* rkq[10][2] */ 3,
    /* rkq[11][0] */ 3,
    /* rkq[11][1] */ 3,
    /* rkq[11][2] */ 3,
    /* riq[0][0] */ 3,
    /* riq[0][1] */ 3,
    /* riq[0][2] */ 3,
    /* riq[1][0] */ 3,
    /* riq[1][1] */ 3,
    /* riq[1][2] */ 3,
    /* riq[2][0] */ 3,
    /* riq[2][1] */ 3,
    /* riq[2][2] */ 3,
    /* riq[3][0] */ 3,
    /* riq[3][1] */ 3,
    /* riq[3][2] */ 3,
    /* riq[4][0] */ 3,
    /* riq[4][1] */ 3,
    /* riq[4][2] */ 3,
    /* riq[5][0] */ 3,
    /* riq[5][1] */ 3,
    /* riq[5][2] */ 3,
    /* riq[6][0] */ 3,
    /* riq[6][1] */ 3,
    /* riq[6][2] */ 3,
    /* riq[7][0] */ 3,
    /* riq[7][1] */ 3,
    /* riq[7][2] */ 3,
    /* riq[8][0] */ 3,
    /* riq[8][1] */ 3,
    /* riq[8][2] */ 3,
    /* riq[9][0] */ 3,
    /* riq[9][1] */ 3,
    /* riq[9][2] */ 3,
    /* riq[10][0] */ 3,
    /* riq[10][1] */ 3,
    /* riq[10][2] */ 3,
    /* riq[11][0] */ 3,
    /* riq[11][1] */ 3,
    /* riq[11][2] */ 3,
    /* presq[0] */ 3,
    /* presq[1] */ 3,
    /* presq[2] */ 3,
    /* presq[3] */ 3,
    /* presq[4] */ 3,
    /* presq[5] */ 3,
    /* presq[6] */ 3,
    /* presq[7] */ 3,
    /* presq[8] */ 3,
    /* presq[9] */ 0,
    /* presq[10] */ 0,
    /* presq[11] */ 3,
    /* presq[12] */ 3,
    /* presq[13] */ 3,
    /* presq[14] */ 3,
    /* presq[15] */ 3,
    /* presq[16] */ 3,
    /* presq[17] */ 3,
    /* presq[18] */ 0,
    /* presq[19] */ 0,
    /* presq[20] */ 3,
    /* presq[21] */ 3,
    /* presq[22] */ 3,
    /* presq[23] */ 3,
    /* presq[24] */ 3,
    /* presq[25] */ 3,
    /* presq[26] */ 3,
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
    for (k = 0; k < 12; k++) {
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
    for (k = 0; k < 27; k++) {
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

/* Zero out Vpk and Wpk */

    for (i = 0; i < 27; i++) {
        for (j = i; j <= 26; j++) {
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
    rcom[10][0] = 0.;
    rcom[10][1] = 0.;
    rcom[10][2] = 0.;
    rcom[11][0] = 0.;
    rcom[11][1] = 0.;
    rcom[11][2] = 0.;
    rkWkk[5][0] = ((pin[2][2]*rk[0][1])-(pin[2][1]*rk[0][2]));
    rkWkk[5][1] = ((pin[2][0]*rk[0][2])-(pin[2][2]*rk[0][0]));
    rkWkk[5][2] = ((pin[2][1]*rk[0][0])-(pin[2][0]*rk[0][1]));
    rkWkk[8][0] = ((pin[8][2]*rk[1][1])-(pin[8][1]*rk[1][2]));
    rkWkk[8][1] = ((pin[8][0]*rk[1][2])-(pin[8][2]*rk[1][0]));
    rkWkk[8][2] = ((pin[8][1]*rk[1][0])-(pin[8][0]*rk[1][1]));
    rkWkk[11][0] = ((pin[11][2]*rk[2][1])-(pin[11][1]*rk[2][2]));
    rkWkk[11][1] = ((pin[11][0]*rk[2][2])-(pin[11][2]*rk[2][0]));
    rkWkk[11][2] = ((pin[11][1]*rk[2][0])-(pin[11][0]*rk[2][1]));
    rkWkk[12][0] = ((pin[12][2]*rk[3][1])-(pin[12][1]*rk[3][2]));
    rkWkk[12][1] = ((pin[12][0]*rk[3][2])-(pin[12][2]*rk[3][0]));
    rkWkk[12][2] = ((pin[12][1]*rk[3][0])-(pin[12][0]*rk[3][1]));
    rkWkk[13][0] = ((pin[13][2]*rk[4][1])-(pin[13][1]*rk[4][2]));
    rkWkk[13][1] = ((pin[13][0]*rk[4][2])-(pin[13][2]*rk[4][0]));
    rkWkk[13][2] = ((pin[13][1]*rk[4][0])-(pin[13][0]*rk[4][1]));
    rkWkk[14][0] = ((pin[14][2]*rk[5][1])-(pin[14][1]*rk[5][2]));
    rkWkk[14][1] = ((pin[14][0]*rk[5][2])-(pin[14][2]*rk[5][0]));
    rkWkk[14][2] = ((pin[14][1]*rk[5][0])-(pin[14][0]*rk[5][1]));
    rkWkk[17][0] = ((pin[17][2]*rk[6][1])-(pin[17][1]*rk[6][2]));
    rkWkk[17][1] = ((pin[17][0]*rk[6][2])-(pin[17][2]*rk[6][0]));
    rkWkk[17][2] = ((pin[17][1]*rk[6][0])-(pin[17][0]*rk[6][1]));
    rkWkk[20][0] = ((pin[20][2]*rk[7][1])-(pin[20][1]*rk[7][2]));
    rkWkk[20][1] = ((pin[20][0]*rk[7][2])-(pin[20][2]*rk[7][0]));
    rkWkk[20][2] = ((pin[20][1]*rk[7][0])-(pin[20][0]*rk[7][1]));
    rkWkk[21][0] = ((pin[21][2]*rk[8][1])-(pin[21][1]*rk[8][2]));
    rkWkk[21][1] = ((pin[21][0]*rk[8][2])-(pin[21][2]*rk[8][0]));
    rkWkk[21][2] = ((pin[21][1]*rk[8][0])-(pin[21][0]*rk[8][1]));
    rkWkk[22][0] = ((pin[22][2]*rk[9][1])-(pin[22][1]*rk[9][2]));
    rkWkk[22][1] = ((pin[22][0]*rk[9][2])-(pin[22][2]*rk[9][0]));
    rkWkk[22][2] = ((pin[22][1]*rk[9][0])-(pin[22][0]*rk[9][1]));
    rkWkk[23][0] = ((pin[23][2]*rk[10][1])-(pin[23][1]*rk[10][2]));
    rkWkk[23][1] = ((pin[23][0]*rk[10][2])-(pin[23][2]*rk[10][0]));
    rkWkk[23][2] = ((pin[23][1]*rk[10][0])-(pin[23][0]*rk[10][1]));
    rkWkk[26][0] = ((pin[26][2]*rk[11][1])-(pin[26][1]*rk[11][2]));
    rkWkk[26][1] = ((pin[26][0]*rk[11][2])-(pin[26][2]*rk[11][0]));
    rkWkk[26][2] = ((pin[26][1]*rk[11][0])-(pin[26][0]*rk[11][1]));
    dik[6][0] = (ri[1][0]-rk[0][0]);
    dik[6][1] = (ri[1][1]-rk[0][1]);
    dik[6][2] = (ri[1][2]-rk[0][2]);
    dik[9][0] = (ri[2][0]-rk[1][0]);
    dik[9][1] = (ri[2][1]-rk[1][1]);
    dik[9][2] = (ri[2][2]-rk[1][2]);
    dik[12][0] = (ri[3][0]-rk[2][0]);
    dik[12][1] = (ri[3][1]-rk[2][1]);
    dik[12][2] = (ri[3][2]-rk[2][2]);
    dik[13][0] = (ri[4][0]-rk[3][0]);
    dik[13][1] = (ri[4][1]-rk[3][1]);
    dik[13][2] = (ri[4][2]-rk[3][2]);
    dik[14][0] = (ri[5][0]-rk[4][0]);
    dik[14][1] = (ri[5][1]-rk[4][1]);
    dik[14][2] = (ri[5][2]-rk[4][2]);
    dik[15][0] = (ri[6][0]-rk[0][0]);
    dik[15][1] = (ri[6][1]-rk[0][1]);
    dik[15][2] = (ri[6][2]-rk[0][2]);
    dik[18][0] = (ri[7][0]-rk[6][0]);
    dik[18][1] = (ri[7][1]-rk[6][1]);
    dik[18][2] = (ri[7][2]-rk[6][2]);
    dik[21][0] = (ri[8][0]-rk[7][0]);
    dik[21][1] = (ri[8][1]-rk[7][1]);
    dik[21][2] = (ri[8][2]-rk[7][2]);
    dik[22][0] = (ri[9][0]-rk[8][0]);
    dik[22][1] = (ri[9][1]-rk[8][1]);
    dik[22][2] = (ri[9][2]-rk[8][2]);
    dik[23][0] = (ri[10][0]-rk[9][0]);
    dik[23][1] = (ri[10][1]-rk[9][1]);
    dik[23][2] = (ri[10][2]-rk[9][2]);
    dik[24][0] = (ri[11][0]-rk[0][0]);
    dik[24][1] = (ri[11][1]-rk[0][1]);
    dik[24][2] = (ri[11][2]-rk[0][2]);

/* Compute mass properties-related constants */

    mtot = (mk[11]+(mk[10]+(mk[9]+(mk[8]+(mk[7]+(mk[6]+(mk[5]+(mk[4]+(mk[3]+(
      mk[2]+(mk[0]+mk[1])))))))))));
    mkrk[5][0][1] = -(mk[0]*rk[0][2]);
    mkrk[5][0][2] = (mk[0]*rk[0][1]);
    mkrk[5][1][0] = (mk[0]*rk[0][2]);
    mkrk[5][1][2] = -(mk[0]*rk[0][0]);
    mkrk[5][2][0] = -(mk[0]*rk[0][1]);
    mkrk[5][2][1] = (mk[0]*rk[0][0]);
    mkrk[8][0][1] = -(mk[1]*rk[1][2]);
    mkrk[8][0][2] = (mk[1]*rk[1][1]);
    mkrk[8][1][0] = (mk[1]*rk[1][2]);
    mkrk[8][1][2] = -(mk[1]*rk[1][0]);
    mkrk[8][2][0] = -(mk[1]*rk[1][1]);
    mkrk[8][2][1] = (mk[1]*rk[1][0]);
    mkrk[11][0][1] = -(mk[2]*rk[2][2]);
    mkrk[11][0][2] = (mk[2]*rk[2][1]);
    mkrk[11][1][0] = (mk[2]*rk[2][2]);
    mkrk[11][1][2] = -(mk[2]*rk[2][0]);
    mkrk[11][2][0] = -(mk[2]*rk[2][1]);
    mkrk[11][2][1] = (mk[2]*rk[2][0]);
    mkrk[12][0][1] = -(mk[3]*rk[3][2]);
    mkrk[12][0][2] = (mk[3]*rk[3][1]);
    mkrk[12][1][0] = (mk[3]*rk[3][2]);
    mkrk[12][1][2] = -(mk[3]*rk[3][0]);
    mkrk[12][2][0] = -(mk[3]*rk[3][1]);
    mkrk[12][2][1] = (mk[3]*rk[3][0]);
    mkrk[13][0][1] = -(mk[4]*rk[4][2]);
    mkrk[13][0][2] = (mk[4]*rk[4][1]);
    mkrk[13][1][0] = (mk[4]*rk[4][2]);
    mkrk[13][1][2] = -(mk[4]*rk[4][0]);
    mkrk[13][2][0] = -(mk[4]*rk[4][1]);
    mkrk[13][2][1] = (mk[4]*rk[4][0]);
    mkrk[14][0][1] = -(mk[5]*rk[5][2]);
    mkrk[14][0][2] = (mk[5]*rk[5][1]);
    mkrk[14][1][0] = (mk[5]*rk[5][2]);
    mkrk[14][1][2] = -(mk[5]*rk[5][0]);
    mkrk[14][2][0] = -(mk[5]*rk[5][1]);
    mkrk[14][2][1] = (mk[5]*rk[5][0]);
    mkrk[17][0][1] = -(mk[6]*rk[6][2]);
    mkrk[17][0][2] = (mk[6]*rk[6][1]);
    mkrk[17][1][0] = (mk[6]*rk[6][2]);
    mkrk[17][1][2] = -(mk[6]*rk[6][0]);
    mkrk[17][2][0] = -(mk[6]*rk[6][1]);
    mkrk[17][2][1] = (mk[6]*rk[6][0]);
    mkrk[20][0][1] = -(mk[7]*rk[7][2]);
    mkrk[20][0][2] = (mk[7]*rk[7][1]);
    mkrk[20][1][0] = (mk[7]*rk[7][2]);
    mkrk[20][1][2] = -(mk[7]*rk[7][0]);
    mkrk[20][2][0] = -(mk[7]*rk[7][1]);
    mkrk[20][2][1] = (mk[7]*rk[7][0]);
    mkrk[21][0][1] = -(mk[8]*rk[8][2]);
    mkrk[21][0][2] = (mk[8]*rk[8][1]);
    mkrk[21][1][0] = (mk[8]*rk[8][2]);
    mkrk[21][1][2] = -(mk[8]*rk[8][0]);
    mkrk[21][2][0] = -(mk[8]*rk[8][1]);
    mkrk[21][2][1] = (mk[8]*rk[8][0]);
    mkrk[22][0][1] = -(mk[9]*rk[9][2]);
    mkrk[22][0][2] = (mk[9]*rk[9][1]);
    mkrk[22][1][0] = (mk[9]*rk[9][2]);
    mkrk[22][1][2] = -(mk[9]*rk[9][0]);
    mkrk[22][2][0] = -(mk[9]*rk[9][1]);
    mkrk[22][2][1] = (mk[9]*rk[9][0]);
    mkrk[23][0][1] = -(mk[10]*rk[10][2]);
    mkrk[23][0][2] = (mk[10]*rk[10][1]);
    mkrk[23][1][0] = (mk[10]*rk[10][2]);
    mkrk[23][1][2] = -(mk[10]*rk[10][0]);
    mkrk[23][2][0] = -(mk[10]*rk[10][1]);
    mkrk[23][2][1] = (mk[10]*rk[10][0]);
    mkrk[26][0][1] = -(mk[11]*rk[11][2]);
    mkrk[26][0][2] = (mk[11]*rk[11][1]);
    mkrk[26][1][0] = (mk[11]*rk[11][2]);
    mkrk[26][1][2] = -(mk[11]*rk[11][0]);
    mkrk[26][2][0] = -(mk[11]*rk[11][1]);
    mkrk[26][2][1] = (mk[11]*rk[11][0]);
    Iko[5][0][0] = (ik[0][0][0]-((mkrk[5][0][1]*rk[0][2])-(mkrk[5][0][2]*
      rk[0][1])));
    Iko[5][0][1] = (ik[0][0][1]-(mkrk[5][0][2]*rk[0][0]));
    Iko[5][0][2] = (ik[0][0][2]+(mkrk[5][0][1]*rk[0][0]));
    Iko[5][1][0] = (ik[0][1][0]+(mkrk[5][1][2]*rk[0][1]));
    Iko[5][1][1] = (ik[0][1][1]-((mkrk[5][1][2]*rk[0][0])-(mkrk[5][1][0]*
      rk[0][2])));
    Iko[5][1][2] = (ik[0][1][2]-(mkrk[5][1][0]*rk[0][1]));
    Iko[5][2][0] = (ik[0][2][0]-(mkrk[5][2][1]*rk[0][2]));
    Iko[5][2][1] = (ik[0][2][1]+(mkrk[5][2][0]*rk[0][2]));
    Iko[5][2][2] = (ik[0][2][2]-((mkrk[5][2][0]*rk[0][1])-(mkrk[5][2][1]*
      rk[0][0])));
    Iko[8][0][0] = (ik[1][0][0]-((mkrk[8][0][1]*rk[1][2])-(mkrk[8][0][2]*
      rk[1][1])));
    Iko[8][0][1] = (ik[1][0][1]-(mkrk[8][0][2]*rk[1][0]));
    Iko[8][0][2] = (ik[1][0][2]+(mkrk[8][0][1]*rk[1][0]));
    Iko[8][1][0] = (ik[1][1][0]+(mkrk[8][1][2]*rk[1][1]));
    Iko[8][1][1] = (ik[1][1][1]-((mkrk[8][1][2]*rk[1][0])-(mkrk[8][1][0]*
      rk[1][2])));
    Iko[8][1][2] = (ik[1][1][2]-(mkrk[8][1][0]*rk[1][1]));
    Iko[8][2][0] = (ik[1][2][0]-(mkrk[8][2][1]*rk[1][2]));
    Iko[8][2][1] = (ik[1][2][1]+(mkrk[8][2][0]*rk[1][2]));
    Iko[8][2][2] = (ik[1][2][2]-((mkrk[8][2][0]*rk[1][1])-(mkrk[8][2][1]*
      rk[1][0])));
    Iko[11][0][0] = (ik[2][0][0]-((mkrk[11][0][1]*rk[2][2])-(mkrk[11][0][2]*
      rk[2][1])));
    Iko[11][0][1] = (ik[2][0][1]-(mkrk[11][0][2]*rk[2][0]));
    Iko[11][0][2] = (ik[2][0][2]+(mkrk[11][0][1]*rk[2][0]));
    Iko[11][1][0] = (ik[2][1][0]+(mkrk[11][1][2]*rk[2][1]));
    Iko[11][1][1] = (ik[2][1][1]-((mkrk[11][1][2]*rk[2][0])-(mkrk[11][1][0]*
      rk[2][2])));
    Iko[11][1][2] = (ik[2][1][2]-(mkrk[11][1][0]*rk[2][1]));
    Iko[11][2][0] = (ik[2][2][0]-(mkrk[11][2][1]*rk[2][2]));
    Iko[11][2][1] = (ik[2][2][1]+(mkrk[11][2][0]*rk[2][2]));
    Iko[11][2][2] = (ik[2][2][2]-((mkrk[11][2][0]*rk[2][1])-(mkrk[11][2][1]*
      rk[2][0])));
    Iko[12][0][0] = (ik[3][0][0]-((mkrk[12][0][1]*rk[3][2])-(mkrk[12][0][2]*
      rk[3][1])));
    Iko[12][0][1] = (ik[3][0][1]-(mkrk[12][0][2]*rk[3][0]));
    Iko[12][0][2] = (ik[3][0][2]+(mkrk[12][0][1]*rk[3][0]));
    Iko[12][1][0] = (ik[3][1][0]+(mkrk[12][1][2]*rk[3][1]));
    Iko[12][1][1] = (ik[3][1][1]-((mkrk[12][1][2]*rk[3][0])-(mkrk[12][1][0]*
      rk[3][2])));
    Iko[12][1][2] = (ik[3][1][2]-(mkrk[12][1][0]*rk[3][1]));
    Iko[12][2][0] = (ik[3][2][0]-(mkrk[12][2][1]*rk[3][2]));
    Iko[12][2][1] = (ik[3][2][1]+(mkrk[12][2][0]*rk[3][2]));
    Iko[12][2][2] = (ik[3][2][2]-((mkrk[12][2][0]*rk[3][1])-(mkrk[12][2][1]*
      rk[3][0])));
    Iko[13][0][0] = (ik[4][0][0]-((mkrk[13][0][1]*rk[4][2])-(mkrk[13][0][2]*
      rk[4][1])));
    Iko[13][0][1] = (ik[4][0][1]-(mkrk[13][0][2]*rk[4][0]));
    Iko[13][0][2] = (ik[4][0][2]+(mkrk[13][0][1]*rk[4][0]));
    Iko[13][1][0] = (ik[4][1][0]+(mkrk[13][1][2]*rk[4][1]));
    Iko[13][1][1] = (ik[4][1][1]-((mkrk[13][1][2]*rk[4][0])-(mkrk[13][1][0]*
      rk[4][2])));
    Iko[13][1][2] = (ik[4][1][2]-(mkrk[13][1][0]*rk[4][1]));
    Iko[13][2][0] = (ik[4][2][0]-(mkrk[13][2][1]*rk[4][2]));
    Iko[13][2][1] = (ik[4][2][1]+(mkrk[13][2][0]*rk[4][2]));
    Iko[13][2][2] = (ik[4][2][2]-((mkrk[13][2][0]*rk[4][1])-(mkrk[13][2][1]*
      rk[4][0])));
    Iko[14][0][0] = (ik[5][0][0]-((mkrk[14][0][1]*rk[5][2])-(mkrk[14][0][2]*
      rk[5][1])));
    Iko[14][0][1] = (ik[5][0][1]-(mkrk[14][0][2]*rk[5][0]));
    Iko[14][0][2] = (ik[5][0][2]+(mkrk[14][0][1]*rk[5][0]));
    Iko[14][1][0] = (ik[5][1][0]+(mkrk[14][1][2]*rk[5][1]));
    Iko[14][1][1] = (ik[5][1][1]-((mkrk[14][1][2]*rk[5][0])-(mkrk[14][1][0]*
      rk[5][2])));
    Iko[14][1][2] = (ik[5][1][2]-(mkrk[14][1][0]*rk[5][1]));
    Iko[14][2][0] = (ik[5][2][0]-(mkrk[14][2][1]*rk[5][2]));
    Iko[14][2][1] = (ik[5][2][1]+(mkrk[14][2][0]*rk[5][2]));
    Iko[14][2][2] = (ik[5][2][2]-((mkrk[14][2][0]*rk[5][1])-(mkrk[14][2][1]*
      rk[5][0])));
    Iko[17][0][0] = (ik[6][0][0]-((mkrk[17][0][1]*rk[6][2])-(mkrk[17][0][2]*
      rk[6][1])));
    Iko[17][0][1] = (ik[6][0][1]-(mkrk[17][0][2]*rk[6][0]));
    Iko[17][0][2] = (ik[6][0][2]+(mkrk[17][0][1]*rk[6][0]));
    Iko[17][1][0] = (ik[6][1][0]+(mkrk[17][1][2]*rk[6][1]));
    Iko[17][1][1] = (ik[6][1][1]-((mkrk[17][1][2]*rk[6][0])-(mkrk[17][1][0]*
      rk[6][2])));
    Iko[17][1][2] = (ik[6][1][2]-(mkrk[17][1][0]*rk[6][1]));
    Iko[17][2][0] = (ik[6][2][0]-(mkrk[17][2][1]*rk[6][2]));
    Iko[17][2][1] = (ik[6][2][1]+(mkrk[17][2][0]*rk[6][2]));
    Iko[17][2][2] = (ik[6][2][2]-((mkrk[17][2][0]*rk[6][1])-(mkrk[17][2][1]*
      rk[6][0])));
    Iko[20][0][0] = (ik[7][0][0]-((mkrk[20][0][1]*rk[7][2])-(mkrk[20][0][2]*
      rk[7][1])));
    Iko[20][0][1] = (ik[7][0][1]-(mkrk[20][0][2]*rk[7][0]));
    Iko[20][0][2] = (ik[7][0][2]+(mkrk[20][0][1]*rk[7][0]));
    Iko[20][1][0] = (ik[7][1][0]+(mkrk[20][1][2]*rk[7][1]));
    Iko[20][1][1] = (ik[7][1][1]-((mkrk[20][1][2]*rk[7][0])-(mkrk[20][1][0]*
      rk[7][2])));
    Iko[20][1][2] = (ik[7][1][2]-(mkrk[20][1][0]*rk[7][1]));
    Iko[20][2][0] = (ik[7][2][0]-(mkrk[20][2][1]*rk[7][2]));
    Iko[20][2][1] = (ik[7][2][1]+(mkrk[20][2][0]*rk[7][2]));
    Iko[20][2][2] = (ik[7][2][2]-((mkrk[20][2][0]*rk[7][1])-(mkrk[20][2][1]*
      rk[7][0])));
    Iko[21][0][0] = (ik[8][0][0]-((mkrk[21][0][1]*rk[8][2])-(mkrk[21][0][2]*
      rk[8][1])));
    Iko[21][0][1] = (ik[8][0][1]-(mkrk[21][0][2]*rk[8][0]));
    Iko[21][0][2] = (ik[8][0][2]+(mkrk[21][0][1]*rk[8][0]));
    Iko[21][1][0] = (ik[8][1][0]+(mkrk[21][1][2]*rk[8][1]));
    Iko[21][1][1] = (ik[8][1][1]-((mkrk[21][1][2]*rk[8][0])-(mkrk[21][1][0]*
      rk[8][2])));
    Iko[21][1][2] = (ik[8][1][2]-(mkrk[21][1][0]*rk[8][1]));
    Iko[21][2][0] = (ik[8][2][0]-(mkrk[21][2][1]*rk[8][2]));
    Iko[21][2][1] = (ik[8][2][1]+(mkrk[21][2][0]*rk[8][2]));
    Iko[21][2][2] = (ik[8][2][2]-((mkrk[21][2][0]*rk[8][1])-(mkrk[21][2][1]*
      rk[8][0])));
    Iko[22][0][0] = (ik[9][0][0]-((mkrk[22][0][1]*rk[9][2])-(mkrk[22][0][2]*
      rk[9][1])));
    Iko[22][0][1] = (ik[9][0][1]-(mkrk[22][0][2]*rk[9][0]));
    Iko[22][0][2] = (ik[9][0][2]+(mkrk[22][0][1]*rk[9][0]));
    Iko[22][1][0] = (ik[9][1][0]+(mkrk[22][1][2]*rk[9][1]));
    Iko[22][1][1] = (ik[9][1][1]-((mkrk[22][1][2]*rk[9][0])-(mkrk[22][1][0]*
      rk[9][2])));
    Iko[22][1][2] = (ik[9][1][2]-(mkrk[22][1][0]*rk[9][1]));
    Iko[22][2][0] = (ik[9][2][0]-(mkrk[22][2][1]*rk[9][2]));
    Iko[22][2][1] = (ik[9][2][1]+(mkrk[22][2][0]*rk[9][2]));
    Iko[22][2][2] = (ik[9][2][2]-((mkrk[22][2][0]*rk[9][1])-(mkrk[22][2][1]*
      rk[9][0])));
    Iko[23][0][0] = (ik[10][0][0]-((mkrk[23][0][1]*rk[10][2])-(mkrk[23][0][2]*
      rk[10][1])));
    Iko[23][0][1] = (ik[10][0][1]-(mkrk[23][0][2]*rk[10][0]));
    Iko[23][0][2] = (ik[10][0][2]+(mkrk[23][0][1]*rk[10][0]));
    Iko[23][1][0] = (ik[10][1][0]+(mkrk[23][1][2]*rk[10][1]));
    Iko[23][1][1] = (ik[10][1][1]-((mkrk[23][1][2]*rk[10][0])-(mkrk[23][1][0]*
      rk[10][2])));
    Iko[23][1][2] = (ik[10][1][2]-(mkrk[23][1][0]*rk[10][1]));
    Iko[23][2][0] = (ik[10][2][0]-(mkrk[23][2][1]*rk[10][2]));
    Iko[23][2][1] = (ik[10][2][1]+(mkrk[23][2][0]*rk[10][2]));
    Iko[23][2][2] = (ik[10][2][2]-((mkrk[23][2][0]*rk[10][1])-(mkrk[23][2][1]*
      rk[10][0])));
    Iko[26][0][0] = (ik[11][0][0]-((mkrk[26][0][1]*rk[11][2])-(mkrk[26][0][2]*
      rk[11][1])));
    Iko[26][0][1] = (ik[11][0][1]-(mkrk[26][0][2]*rk[11][0]));
    Iko[26][0][2] = (ik[11][0][2]+(mkrk[26][0][1]*rk[11][0]));
    Iko[26][1][0] = (ik[11][1][0]+(mkrk[26][1][2]*rk[11][1]));
    Iko[26][1][1] = (ik[11][1][1]-((mkrk[26][1][2]*rk[11][0])-(mkrk[26][1][0]*
      rk[11][2])));
    Iko[26][1][2] = (ik[11][1][2]-(mkrk[26][1][0]*rk[11][1]));
    Iko[26][2][0] = (ik[11][2][0]-(mkrk[26][2][1]*rk[11][2]));
    Iko[26][2][1] = (ik[11][2][1]+(mkrk[26][2][0]*rk[11][2]));
    Iko[26][2][2] = (ik[11][2][2]-((mkrk[26][2][0]*rk[11][1])-(mkrk[26][2][1]*
      rk[11][0])));
    sdserialno(&i);
    if (i != 70405) {
        sdseterr(7,41);
    }
    roustate = 1;
}

sdstate(timein,qin,uin)
    double timein,qin[27],uin[27];
{
/*
Compute kinematic information and store it in sdgstate.

Generated 31-Jul-2007 11:59:37 by SD/FAST, Kane's formulation
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
        for (i = 0; i < 27; i++) {
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
        for (i = 0; i < 27; i++) {
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
        for (i = 0; i < 27; i++) {
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
    for (i = 0; i < 27; i++) {
        q[i] = qin[i];
    }
/*
Compute sines and cosines of q
*/
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
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = ((pin[0][0]*pin[0][0])+(c3*(1.-(pin[0][0]*pin[0][0]))));
    Cik[3][0][1] = (((pin[0][0]*pin[0][1])-(pin[0][2]*s3))-(c3*(pin[0][0]*
      pin[0][1])));
    Cik[3][0][2] = (((pin[0][0]*pin[0][2])+(pin[0][1]*s3))-(c3*(pin[0][0]*
      pin[0][2])));
    Cik[3][1][0] = (((pin[0][0]*pin[0][1])+(pin[0][2]*s3))-(c3*(pin[0][0]*
      pin[0][1])));
    Cik[3][1][1] = ((pin[0][1]*pin[0][1])+(c3*(1.-(pin[0][1]*pin[0][1]))));
    Cik[3][1][2] = (((pin[0][1]*pin[0][2])-(pin[0][0]*s3))-(c3*(pin[0][1]*
      pin[0][2])));
    Cik[3][2][0] = (((pin[0][0]*pin[0][2])-(pin[0][1]*s3))-(c3*(pin[0][0]*
      pin[0][2])));
    Cik[3][2][1] = (((pin[0][0]*s3)+(pin[0][1]*pin[0][2]))-(c3*(pin[0][1]*
      pin[0][2])));
    Cik[3][2][2] = ((pin[0][2]*pin[0][2])+(c3*(1.-(pin[0][2]*pin[0][2]))));
    Cik[4][0][0] = ((pin[1][0]*pin[1][0])+(c4*(1.-(pin[1][0]*pin[1][0]))));
    Cik[4][0][1] = (((pin[1][0]*pin[1][1])-(pin[1][2]*s4))-(c4*(pin[1][0]*
      pin[1][1])));
    Cik[4][0][2] = (((pin[1][0]*pin[1][2])+(pin[1][1]*s4))-(c4*(pin[1][0]*
      pin[1][2])));
    Cik[4][1][0] = (((pin[1][0]*pin[1][1])+(pin[1][2]*s4))-(c4*(pin[1][0]*
      pin[1][1])));
    Cik[4][1][1] = ((pin[1][1]*pin[1][1])+(c4*(1.-(pin[1][1]*pin[1][1]))));
    Cik[4][1][2] = (((pin[1][1]*pin[1][2])-(pin[1][0]*s4))-(c4*(pin[1][1]*
      pin[1][2])));
    Cik[4][2][0] = (((pin[1][0]*pin[1][2])-(pin[1][1]*s4))-(c4*(pin[1][0]*
      pin[1][2])));
    Cik[4][2][1] = (((pin[1][0]*s4)+(pin[1][1]*pin[1][2]))-(c4*(pin[1][1]*
      pin[1][2])));
    Cik[4][2][2] = ((pin[1][2]*pin[1][2])+(c4*(1.-(pin[1][2]*pin[1][2]))));
    Cik[5][0][0] = ((pin[2][0]*pin[2][0])+(c5*(1.-(pin[2][0]*pin[2][0]))));
    Cik[5][0][1] = (((pin[2][0]*pin[2][1])-(pin[2][2]*s5))-(c5*(pin[2][0]*
      pin[2][1])));
    Cik[5][0][2] = (((pin[2][0]*pin[2][2])+(pin[2][1]*s5))-(c5*(pin[2][0]*
      pin[2][2])));
    Cik[5][1][0] = (((pin[2][0]*pin[2][1])+(pin[2][2]*s5))-(c5*(pin[2][0]*
      pin[2][1])));
    Cik[5][1][1] = ((pin[2][1]*pin[2][1])+(c5*(1.-(pin[2][1]*pin[2][1]))));
    Cik[5][1][2] = (((pin[2][1]*pin[2][2])-(pin[2][0]*s5))-(c5*(pin[2][1]*
      pin[2][2])));
    Cik[5][2][0] = (((pin[2][0]*pin[2][2])-(pin[2][1]*s5))-(c5*(pin[2][0]*
      pin[2][2])));
    Cik[5][2][1] = (((pin[2][0]*s5)+(pin[2][1]*pin[2][2]))-(c5*(pin[2][1]*
      pin[2][2])));
    Cik[5][2][2] = ((pin[2][2]*pin[2][2])+(c5*(1.-(pin[2][2]*pin[2][2]))));
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
/*
Compute across-joint direction cosines Cib
*/
    Cib[0][0][0] = ((Cik[5][2][0]*((Cik[3][0][2]*Cik[4][2][2])+((Cik[3][0][0]*
      Cik[4][0][2])+(Cik[3][0][1]*Cik[4][1][2]))))+((Cik[5][0][0]*((Cik[3][0][2]
      *Cik[4][2][0])+((Cik[3][0][0]*Cik[4][0][0])+(Cik[3][0][1]*Cik[4][1][0]))))
      +(Cik[5][1][0]*((Cik[3][0][2]*Cik[4][2][1])+((Cik[3][0][0]*Cik[4][0][1])+(
      Cik[3][0][1]*Cik[4][1][1]))))));
    Cib[0][0][1] = ((Cik[5][2][1]*((Cik[3][0][2]*Cik[4][2][2])+((Cik[3][0][0]*
      Cik[4][0][2])+(Cik[3][0][1]*Cik[4][1][2]))))+((Cik[5][0][1]*((Cik[3][0][2]
      *Cik[4][2][0])+((Cik[3][0][0]*Cik[4][0][0])+(Cik[3][0][1]*Cik[4][1][0]))))
      +(Cik[5][1][1]*((Cik[3][0][2]*Cik[4][2][1])+((Cik[3][0][0]*Cik[4][0][1])+(
      Cik[3][0][1]*Cik[4][1][1]))))));
    Cib[0][0][2] = ((Cik[5][2][2]*((Cik[3][0][2]*Cik[4][2][2])+((Cik[3][0][0]*
      Cik[4][0][2])+(Cik[3][0][1]*Cik[4][1][2]))))+((Cik[5][0][2]*((Cik[3][0][2]
      *Cik[4][2][0])+((Cik[3][0][0]*Cik[4][0][0])+(Cik[3][0][1]*Cik[4][1][0]))))
      +(Cik[5][1][2]*((Cik[3][0][2]*Cik[4][2][1])+((Cik[3][0][0]*Cik[4][0][1])+(
      Cik[3][0][1]*Cik[4][1][1]))))));
    Cib[0][1][0] = ((Cik[5][2][0]*((Cik[3][1][2]*Cik[4][2][2])+((Cik[3][1][0]*
      Cik[4][0][2])+(Cik[3][1][1]*Cik[4][1][2]))))+((Cik[5][0][0]*((Cik[3][1][2]
      *Cik[4][2][0])+((Cik[3][1][0]*Cik[4][0][0])+(Cik[3][1][1]*Cik[4][1][0]))))
      +(Cik[5][1][0]*((Cik[3][1][2]*Cik[4][2][1])+((Cik[3][1][0]*Cik[4][0][1])+(
      Cik[3][1][1]*Cik[4][1][1]))))));
    Cib[0][1][1] = ((Cik[5][2][1]*((Cik[3][1][2]*Cik[4][2][2])+((Cik[3][1][0]*
      Cik[4][0][2])+(Cik[3][1][1]*Cik[4][1][2]))))+((Cik[5][0][1]*((Cik[3][1][2]
      *Cik[4][2][0])+((Cik[3][1][0]*Cik[4][0][0])+(Cik[3][1][1]*Cik[4][1][0]))))
      +(Cik[5][1][1]*((Cik[3][1][2]*Cik[4][2][1])+((Cik[3][1][0]*Cik[4][0][1])+(
      Cik[3][1][1]*Cik[4][1][1]))))));
    Cib[0][1][2] = ((Cik[5][2][2]*((Cik[3][1][2]*Cik[4][2][2])+((Cik[3][1][0]*
      Cik[4][0][2])+(Cik[3][1][1]*Cik[4][1][2]))))+((Cik[5][0][2]*((Cik[3][1][2]
      *Cik[4][2][0])+((Cik[3][1][0]*Cik[4][0][0])+(Cik[3][1][1]*Cik[4][1][0]))))
      +(Cik[5][1][2]*((Cik[3][1][2]*Cik[4][2][1])+((Cik[3][1][0]*Cik[4][0][1])+(
      Cik[3][1][1]*Cik[4][1][1]))))));
    Cib[0][2][0] = ((Cik[5][2][0]*((Cik[3][2][2]*Cik[4][2][2])+((Cik[3][2][0]*
      Cik[4][0][2])+(Cik[3][2][1]*Cik[4][1][2]))))+((Cik[5][0][0]*((Cik[3][2][2]
      *Cik[4][2][0])+((Cik[3][2][0]*Cik[4][0][0])+(Cik[3][2][1]*Cik[4][1][0]))))
      +(Cik[5][1][0]*((Cik[3][2][2]*Cik[4][2][1])+((Cik[3][2][0]*Cik[4][0][1])+(
      Cik[3][2][1]*Cik[4][1][1]))))));
    Cib[0][2][1] = ((Cik[5][2][1]*((Cik[3][2][2]*Cik[4][2][2])+((Cik[3][2][0]*
      Cik[4][0][2])+(Cik[3][2][1]*Cik[4][1][2]))))+((Cik[5][0][1]*((Cik[3][2][2]
      *Cik[4][2][0])+((Cik[3][2][0]*Cik[4][0][0])+(Cik[3][2][1]*Cik[4][1][0]))))
      +(Cik[5][1][1]*((Cik[3][2][2]*Cik[4][2][1])+((Cik[3][2][0]*Cik[4][0][1])+(
      Cik[3][2][1]*Cik[4][1][1]))))));
    Cib[0][2][2] = ((Cik[5][2][2]*((Cik[3][2][2]*Cik[4][2][2])+((Cik[3][2][0]*
      Cik[4][0][2])+(Cik[3][2][1]*Cik[4][1][2]))))+((Cik[5][0][2]*((Cik[3][2][2]
      *Cik[4][2][0])+((Cik[3][2][0]*Cik[4][0][0])+(Cik[3][2][1]*Cik[4][1][0]))))
      +(Cik[5][1][2]*((Cik[3][2][2]*Cik[4][2][1])+((Cik[3][2][0]*Cik[4][0][1])+(
      Cik[3][2][1]*Cik[4][1][1]))))));
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
    Cib[6][0][0] = ((Cik[17][2][0]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[6][0][1] = ((Cik[17][2][1]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[6][0][2] = ((Cik[17][2][2]*((Cik[15][0][2]*Cik[16][2][2])+((
      Cik[15][0][0]*Cik[16][0][2])+(Cik[15][0][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][0][2]*Cik[16][2][0])+((Cik[15][0][0]*Cik[16][0][0]
      )+(Cik[15][0][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][0][2]*
      Cik[16][2][1])+((Cik[15][0][0]*Cik[16][0][1])+(Cik[15][0][1]*Cik[16][1][1]
      ))))));
    Cib[6][1][0] = ((Cik[17][2][0]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[6][1][1] = ((Cik[17][2][1]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[6][1][2] = ((Cik[17][2][2]*((Cik[15][1][2]*Cik[16][2][2])+((
      Cik[15][1][0]*Cik[16][0][2])+(Cik[15][1][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][1][2]*Cik[16][2][0])+((Cik[15][1][0]*Cik[16][0][0]
      )+(Cik[15][1][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][1][2]*
      Cik[16][2][1])+((Cik[15][1][0]*Cik[16][0][1])+(Cik[15][1][1]*Cik[16][1][1]
      ))))));
    Cib[6][2][0] = ((Cik[17][2][0]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][0]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][0]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[6][2][1] = ((Cik[17][2][1]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][1]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][1]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[6][2][2] = ((Cik[17][2][2]*((Cik[15][2][2]*Cik[16][2][2])+((
      Cik[15][2][0]*Cik[16][0][2])+(Cik[15][2][1]*Cik[16][1][2]))))+((
      Cik[17][0][2]*((Cik[15][2][2]*Cik[16][2][0])+((Cik[15][2][0]*Cik[16][0][0]
      )+(Cik[15][2][1]*Cik[16][1][0]))))+(Cik[17][1][2]*((Cik[15][2][2]*
      Cik[16][2][1])+((Cik[15][2][0]*Cik[16][0][1])+(Cik[15][2][1]*Cik[16][1][1]
      ))))));
    Cib[11][0][0] = ((Cik[26][2][0]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[11][0][1] = ((Cik[26][2][1]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[11][0][2] = ((Cik[26][2][2]*((Cik[24][0][2]*Cik[25][2][2])+((
      Cik[24][0][0]*Cik[25][0][2])+(Cik[24][0][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][0][2]*Cik[25][2][0])+((Cik[24][0][0]*Cik[25][0][0]
      )+(Cik[24][0][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][0][2]*
      Cik[25][2][1])+((Cik[24][0][0]*Cik[25][0][1])+(Cik[24][0][1]*Cik[25][1][1]
      ))))));
    Cib[11][1][0] = ((Cik[26][2][0]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[11][1][1] = ((Cik[26][2][1]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[11][1][2] = ((Cik[26][2][2]*((Cik[24][1][2]*Cik[25][2][2])+((
      Cik[24][1][0]*Cik[25][0][2])+(Cik[24][1][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][1][2]*Cik[25][2][0])+((Cik[24][1][0]*Cik[25][0][0]
      )+(Cik[24][1][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][1][2]*
      Cik[25][2][1])+((Cik[24][1][0]*Cik[25][0][1])+(Cik[24][1][1]*Cik[25][1][1]
      ))))));
    Cib[11][2][0] = ((Cik[26][2][0]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][0]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][0]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
      ))))));
    Cib[11][2][1] = ((Cik[26][2][1]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][1]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][1]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
      ))))));
    Cib[11][2][2] = ((Cik[26][2][2]*((Cik[24][2][2]*Cik[25][2][2])+((
      Cik[24][2][0]*Cik[25][0][2])+(Cik[24][2][1]*Cik[25][1][2]))))+((
      Cik[26][0][2]*((Cik[24][2][2]*Cik[25][2][0])+((Cik[24][2][0]*Cik[25][0][0]
      )+(Cik[24][2][1]*Cik[25][1][0]))))+(Cik[26][1][2]*((Cik[24][2][2]*
      Cik[25][2][1])+((Cik[24][2][0]*Cik[25][0][1])+(Cik[24][2][1]*Cik[25][1][1]
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
    gk[4][0] = ((Cik[4][2][0]*gk[3][2])+((Cik[4][0][0]*gk[3][0])+(Cik[4][1][0]*
      gk[3][1])));
    gk[4][1] = ((Cik[4][2][1]*gk[3][2])+((Cik[4][0][1]*gk[3][0])+(Cik[4][1][1]*
      gk[3][1])));
    gk[4][2] = ((Cik[4][2][2]*gk[3][2])+((Cik[4][0][2]*gk[3][0])+(Cik[4][1][2]*
      gk[3][1])));
    gk[5][0] = ((Cik[5][2][0]*gk[4][2])+((Cik[5][0][0]*gk[4][0])+(Cik[5][1][0]*
      gk[4][1])));
    gk[5][1] = ((Cik[5][2][1]*gk[4][2])+((Cik[5][0][1]*gk[4][0])+(Cik[5][1][1]*
      gk[4][1])));
    gk[5][2] = ((Cik[5][2][2]*gk[4][2])+((Cik[5][0][2]*gk[4][0])+(Cik[5][1][2]*
      gk[4][1])));
    gk[6][0] = ((Cik[6][2][0]*gk[5][2])+((Cik[6][0][0]*gk[5][0])+(Cik[6][1][0]*
      gk[5][1])));
    gk[6][1] = ((Cik[6][2][1]*gk[5][2])+((Cik[6][0][1]*gk[5][0])+(Cik[6][1][1]*
      gk[5][1])));
    gk[6][2] = ((Cik[6][2][2]*gk[5][2])+((Cik[6][0][2]*gk[5][0])+(Cik[6][1][2]*
      gk[5][1])));
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
    gk[11][0] = ((Cik[11][2][0]*gk[8][2])+((Cik[11][0][0]*gk[8][0])+(
      Cik[11][1][0]*gk[8][1])));
    gk[11][1] = ((Cik[11][2][1]*gk[8][2])+((Cik[11][0][1]*gk[8][0])+(
      Cik[11][1][1]*gk[8][1])));
    gk[11][2] = ((Cik[11][2][2]*gk[8][2])+((Cik[11][0][2]*gk[8][0])+(
      Cik[11][1][2]*gk[8][1])));
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
    gk[15][0] = ((Cik[15][2][0]*gk[5][2])+((Cik[15][0][0]*gk[5][0])+(
      Cik[15][1][0]*gk[5][1])));
    gk[15][1] = ((Cik[15][2][1]*gk[5][2])+((Cik[15][0][1]*gk[5][0])+(
      Cik[15][1][1]*gk[5][1])));
    gk[15][2] = ((Cik[15][2][2]*gk[5][2])+((Cik[15][0][2]*gk[5][0])+(
      Cik[15][1][2]*gk[5][1])));
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
    gk[20][0] = ((Cik[20][2][0]*gk[17][2])+((Cik[20][0][0]*gk[17][0])+(
      Cik[20][1][0]*gk[17][1])));
    gk[20][1] = ((Cik[20][2][1]*gk[17][2])+((Cik[20][0][1]*gk[17][0])+(
      Cik[20][1][1]*gk[17][1])));
    gk[20][2] = ((Cik[20][2][2]*gk[17][2])+((Cik[20][0][2]*gk[17][0])+(
      Cik[20][1][2]*gk[17][1])));
    gk[21][0] = ((Cik[21][2][0]*gk[20][2])+((Cik[21][0][0]*gk[20][0])+(
      Cik[21][1][0]*gk[20][1])));
    gk[21][1] = ((Cik[21][2][1]*gk[20][2])+((Cik[21][0][1]*gk[20][0])+(
      Cik[21][1][1]*gk[20][1])));
    gk[21][2] = ((Cik[21][2][2]*gk[20][2])+((Cik[21][0][2]*gk[20][0])+(
      Cik[21][1][2]*gk[20][1])));
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
    gk[24][0] = ((Cik[24][2][0]*gk[5][2])+((Cik[24][0][0]*gk[5][0])+(
      Cik[24][1][0]*gk[5][1])));
    gk[24][1] = ((Cik[24][2][1]*gk[5][2])+((Cik[24][0][1]*gk[5][0])+(
      Cik[24][1][1]*gk[5][1])));
    gk[24][2] = ((Cik[24][2][2]*gk[5][2])+((Cik[24][0][2]*gk[5][0])+(
      Cik[24][1][2]*gk[5][1])));
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
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[4][0][0] = ((Cik[3][0][2]*Cik[4][2][0])+((Cik[3][0][0]*Cik[4][0][0])+(
      Cik[3][0][1]*Cik[4][1][0])));
    cnk[4][0][1] = ((Cik[3][0][2]*Cik[4][2][1])+((Cik[3][0][0]*Cik[4][0][1])+(
      Cik[3][0][1]*Cik[4][1][1])));
    cnk[4][0][2] = ((Cik[3][0][2]*Cik[4][2][2])+((Cik[3][0][0]*Cik[4][0][2])+(
      Cik[3][0][1]*Cik[4][1][2])));
    cnk[4][1][0] = ((Cik[3][1][2]*Cik[4][2][0])+((Cik[3][1][0]*Cik[4][0][0])+(
      Cik[3][1][1]*Cik[4][1][0])));
    cnk[4][1][1] = ((Cik[3][1][2]*Cik[4][2][1])+((Cik[3][1][0]*Cik[4][0][1])+(
      Cik[3][1][1]*Cik[4][1][1])));
    cnk[4][1][2] = ((Cik[3][1][2]*Cik[4][2][2])+((Cik[3][1][0]*Cik[4][0][2])+(
      Cik[3][1][1]*Cik[4][1][2])));
    cnk[4][2][0] = ((Cik[3][2][2]*Cik[4][2][0])+((Cik[3][2][0]*Cik[4][0][0])+(
      Cik[3][2][1]*Cik[4][1][0])));
    cnk[4][2][1] = ((Cik[3][2][2]*Cik[4][2][1])+((Cik[3][2][0]*Cik[4][0][1])+(
      Cik[3][2][1]*Cik[4][1][1])));
    cnk[4][2][2] = ((Cik[3][2][2]*Cik[4][2][2])+((Cik[3][2][0]*Cik[4][0][2])+(
      Cik[3][2][1]*Cik[4][1][2])));
    cnk[5][0][0] = ((Cik[5][2][0]*cnk[4][0][2])+((Cik[5][0][0]*cnk[4][0][0])+(
      Cik[5][1][0]*cnk[4][0][1])));
    cnk[5][0][1] = ((Cik[5][2][1]*cnk[4][0][2])+((Cik[5][0][1]*cnk[4][0][0])+(
      Cik[5][1][1]*cnk[4][0][1])));
    cnk[5][0][2] = ((Cik[5][2][2]*cnk[4][0][2])+((Cik[5][0][2]*cnk[4][0][0])+(
      Cik[5][1][2]*cnk[4][0][1])));
    cnk[5][1][0] = ((Cik[5][2][0]*cnk[4][1][2])+((Cik[5][0][0]*cnk[4][1][0])+(
      Cik[5][1][0]*cnk[4][1][1])));
    cnk[5][1][1] = ((Cik[5][2][1]*cnk[4][1][2])+((Cik[5][0][1]*cnk[4][1][0])+(
      Cik[5][1][1]*cnk[4][1][1])));
    cnk[5][1][2] = ((Cik[5][2][2]*cnk[4][1][2])+((Cik[5][0][2]*cnk[4][1][0])+(
      Cik[5][1][2]*cnk[4][1][1])));
    cnk[5][2][0] = ((Cik[5][2][0]*cnk[4][2][2])+((Cik[5][0][0]*cnk[4][2][0])+(
      Cik[5][1][0]*cnk[4][2][1])));
    cnk[5][2][1] = ((Cik[5][2][1]*cnk[4][2][2])+((Cik[5][0][1]*cnk[4][2][0])+(
      Cik[5][1][1]*cnk[4][2][1])));
    cnk[5][2][2] = ((Cik[5][2][2]*cnk[4][2][2])+((Cik[5][0][2]*cnk[4][2][0])+(
      Cik[5][1][2]*cnk[4][2][1])));
    cnk[6][0][0] = ((Cik[6][2][0]*cnk[5][0][2])+((Cik[6][0][0]*cnk[5][0][0])+(
      Cik[6][1][0]*cnk[5][0][1])));
    cnk[6][0][1] = ((Cik[6][2][1]*cnk[5][0][2])+((Cik[6][0][1]*cnk[5][0][0])+(
      Cik[6][1][1]*cnk[5][0][1])));
    cnk[6][0][2] = ((Cik[6][2][2]*cnk[5][0][2])+((Cik[6][0][2]*cnk[5][0][0])+(
      Cik[6][1][2]*cnk[5][0][1])));
    cnk[6][1][0] = ((Cik[6][2][0]*cnk[5][1][2])+((Cik[6][0][0]*cnk[5][1][0])+(
      Cik[6][1][0]*cnk[5][1][1])));
    cnk[6][1][1] = ((Cik[6][2][1]*cnk[5][1][2])+((Cik[6][0][1]*cnk[5][1][0])+(
      Cik[6][1][1]*cnk[5][1][1])));
    cnk[6][1][2] = ((Cik[6][2][2]*cnk[5][1][2])+((Cik[6][0][2]*cnk[5][1][0])+(
      Cik[6][1][2]*cnk[5][1][1])));
    cnk[6][2][0] = ((Cik[6][2][0]*cnk[5][2][2])+((Cik[6][0][0]*cnk[5][2][0])+(
      Cik[6][1][0]*cnk[5][2][1])));
    cnk[6][2][1] = ((Cik[6][2][1]*cnk[5][2][2])+((Cik[6][0][1]*cnk[5][2][0])+(
      Cik[6][1][1]*cnk[5][2][1])));
    cnk[6][2][2] = ((Cik[6][2][2]*cnk[5][2][2])+((Cik[6][0][2]*cnk[5][2][0])+(
      Cik[6][1][2]*cnk[5][2][1])));
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
    cnk[11][0][0] = ((Cik[11][2][0]*cnk[8][0][2])+((Cik[11][0][0]*cnk[8][0][0])+
      (Cik[11][1][0]*cnk[8][0][1])));
    cnk[11][0][1] = ((Cik[11][2][1]*cnk[8][0][2])+((Cik[11][0][1]*cnk[8][0][0])+
      (Cik[11][1][1]*cnk[8][0][1])));
    cnk[11][0][2] = ((Cik[11][2][2]*cnk[8][0][2])+((Cik[11][0][2]*cnk[8][0][0])+
      (Cik[11][1][2]*cnk[8][0][1])));
    cnk[11][1][0] = ((Cik[11][2][0]*cnk[8][1][2])+((Cik[11][0][0]*cnk[8][1][0])+
      (Cik[11][1][0]*cnk[8][1][1])));
    cnk[11][1][1] = ((Cik[11][2][1]*cnk[8][1][2])+((Cik[11][0][1]*cnk[8][1][0])+
      (Cik[11][1][1]*cnk[8][1][1])));
    cnk[11][1][2] = ((Cik[11][2][2]*cnk[8][1][2])+((Cik[11][0][2]*cnk[8][1][0])+
      (Cik[11][1][2]*cnk[8][1][1])));
    cnk[11][2][0] = ((Cik[11][2][0]*cnk[8][2][2])+((Cik[11][0][0]*cnk[8][2][0])+
      (Cik[11][1][0]*cnk[8][2][1])));
    cnk[11][2][1] = ((Cik[11][2][1]*cnk[8][2][2])+((Cik[11][0][1]*cnk[8][2][0])+
      (Cik[11][1][1]*cnk[8][2][1])));
    cnk[11][2][2] = ((Cik[11][2][2]*cnk[8][2][2])+((Cik[11][0][2]*cnk[8][2][0])+
      (Cik[11][1][2]*cnk[8][2][1])));
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
    cnk[15][0][0] = ((Cik[15][2][0]*cnk[5][0][2])+((Cik[15][0][0]*cnk[5][0][0])+
      (Cik[15][1][0]*cnk[5][0][1])));
    cnk[15][0][1] = ((Cik[15][2][1]*cnk[5][0][2])+((Cik[15][0][1]*cnk[5][0][0])+
      (Cik[15][1][1]*cnk[5][0][1])));
    cnk[15][0][2] = ((Cik[15][2][2]*cnk[5][0][2])+((Cik[15][0][2]*cnk[5][0][0])+
      (Cik[15][1][2]*cnk[5][0][1])));
    cnk[15][1][0] = ((Cik[15][2][0]*cnk[5][1][2])+((Cik[15][0][0]*cnk[5][1][0])+
      (Cik[15][1][0]*cnk[5][1][1])));
    cnk[15][1][1] = ((Cik[15][2][1]*cnk[5][1][2])+((Cik[15][0][1]*cnk[5][1][0])+
      (Cik[15][1][1]*cnk[5][1][1])));
    cnk[15][1][2] = ((Cik[15][2][2]*cnk[5][1][2])+((Cik[15][0][2]*cnk[5][1][0])+
      (Cik[15][1][2]*cnk[5][1][1])));
    cnk[15][2][0] = ((Cik[15][2][0]*cnk[5][2][2])+((Cik[15][0][0]*cnk[5][2][0])+
      (Cik[15][1][0]*cnk[5][2][1])));
    cnk[15][2][1] = ((Cik[15][2][1]*cnk[5][2][2])+((Cik[15][0][1]*cnk[5][2][0])+
      (Cik[15][1][1]*cnk[5][2][1])));
    cnk[15][2][2] = ((Cik[15][2][2]*cnk[5][2][2])+((Cik[15][0][2]*cnk[5][2][0])+
      (Cik[15][1][2]*cnk[5][2][1])));
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
    cnk[20][0][0] = ((Cik[20][2][0]*cnk[17][0][2])+((Cik[20][0][0]*cnk[17][0][0]
      )+(Cik[20][1][0]*cnk[17][0][1])));
    cnk[20][0][1] = ((Cik[20][2][1]*cnk[17][0][2])+((Cik[20][0][1]*cnk[17][0][0]
      )+(Cik[20][1][1]*cnk[17][0][1])));
    cnk[20][0][2] = ((Cik[20][2][2]*cnk[17][0][2])+((Cik[20][0][2]*cnk[17][0][0]
      )+(Cik[20][1][2]*cnk[17][0][1])));
    cnk[20][1][0] = ((Cik[20][2][0]*cnk[17][1][2])+((Cik[20][0][0]*cnk[17][1][0]
      )+(Cik[20][1][0]*cnk[17][1][1])));
    cnk[20][1][1] = ((Cik[20][2][1]*cnk[17][1][2])+((Cik[20][0][1]*cnk[17][1][0]
      )+(Cik[20][1][1]*cnk[17][1][1])));
    cnk[20][1][2] = ((Cik[20][2][2]*cnk[17][1][2])+((Cik[20][0][2]*cnk[17][1][0]
      )+(Cik[20][1][2]*cnk[17][1][1])));
    cnk[20][2][0] = ((Cik[20][2][0]*cnk[17][2][2])+((Cik[20][0][0]*cnk[17][2][0]
      )+(Cik[20][1][0]*cnk[17][2][1])));
    cnk[20][2][1] = ((Cik[20][2][1]*cnk[17][2][2])+((Cik[20][0][1]*cnk[17][2][0]
      )+(Cik[20][1][1]*cnk[17][2][1])));
    cnk[20][2][2] = ((Cik[20][2][2]*cnk[17][2][2])+((Cik[20][0][2]*cnk[17][2][0]
      )+(Cik[20][1][2]*cnk[17][2][1])));
    cnk[21][0][0] = ((Cik[21][2][0]*cnk[20][0][2])+((Cik[21][0][0]*cnk[20][0][0]
      )+(Cik[21][1][0]*cnk[20][0][1])));
    cnk[21][0][1] = ((Cik[21][2][1]*cnk[20][0][2])+((Cik[21][0][1]*cnk[20][0][0]
      )+(Cik[21][1][1]*cnk[20][0][1])));
    cnk[21][0][2] = ((Cik[21][2][2]*cnk[20][0][2])+((Cik[21][0][2]*cnk[20][0][0]
      )+(Cik[21][1][2]*cnk[20][0][1])));
    cnk[21][1][0] = ((Cik[21][2][0]*cnk[20][1][2])+((Cik[21][0][0]*cnk[20][1][0]
      )+(Cik[21][1][0]*cnk[20][1][1])));
    cnk[21][1][1] = ((Cik[21][2][1]*cnk[20][1][2])+((Cik[21][0][1]*cnk[20][1][0]
      )+(Cik[21][1][1]*cnk[20][1][1])));
    cnk[21][1][2] = ((Cik[21][2][2]*cnk[20][1][2])+((Cik[21][0][2]*cnk[20][1][0]
      )+(Cik[21][1][2]*cnk[20][1][1])));
    cnk[21][2][0] = ((Cik[21][2][0]*cnk[20][2][2])+((Cik[21][0][0]*cnk[20][2][0]
      )+(Cik[21][1][0]*cnk[20][2][1])));
    cnk[21][2][1] = ((Cik[21][2][1]*cnk[20][2][2])+((Cik[21][0][1]*cnk[20][2][0]
      )+(Cik[21][1][1]*cnk[20][2][1])));
    cnk[21][2][2] = ((Cik[21][2][2]*cnk[20][2][2])+((Cik[21][0][2]*cnk[20][2][0]
      )+(Cik[21][1][2]*cnk[20][2][1])));
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
    cnk[24][0][0] = ((Cik[24][2][0]*cnk[5][0][2])+((Cik[24][0][0]*cnk[5][0][0])+
      (Cik[24][1][0]*cnk[5][0][1])));
    cnk[24][0][1] = ((Cik[24][2][1]*cnk[5][0][2])+((Cik[24][0][1]*cnk[5][0][0])+
      (Cik[24][1][1]*cnk[5][0][1])));
    cnk[24][0][2] = ((Cik[24][2][2]*cnk[5][0][2])+((Cik[24][0][2]*cnk[5][0][0])+
      (Cik[24][1][2]*cnk[5][0][1])));
    cnk[24][1][0] = ((Cik[24][2][0]*cnk[5][1][2])+((Cik[24][0][0]*cnk[5][1][0])+
      (Cik[24][1][0]*cnk[5][1][1])));
    cnk[24][1][1] = ((Cik[24][2][1]*cnk[5][1][2])+((Cik[24][0][1]*cnk[5][1][0])+
      (Cik[24][1][1]*cnk[5][1][1])));
    cnk[24][1][2] = ((Cik[24][2][2]*cnk[5][1][2])+((Cik[24][0][2]*cnk[5][1][0])+
      (Cik[24][1][2]*cnk[5][1][1])));
    cnk[24][2][0] = ((Cik[24][2][0]*cnk[5][2][2])+((Cik[24][0][0]*cnk[5][2][0])+
      (Cik[24][1][0]*cnk[5][2][1])));
    cnk[24][2][1] = ((Cik[24][2][1]*cnk[5][2][2])+((Cik[24][0][1]*cnk[5][2][0])+
      (Cik[24][1][1]*cnk[5][2][1])));
    cnk[24][2][2] = ((Cik[24][2][2]*cnk[5][2][2])+((Cik[24][0][2]*cnk[5][2][0])+
      (Cik[24][1][2]*cnk[5][2][1])));
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
    cnb[0][0][0] = cnk[5][0][0];
    cnb[0][0][1] = cnk[5][0][1];
    cnb[0][0][2] = cnk[5][0][2];
    cnb[0][1][0] = cnk[5][1][0];
    cnb[0][1][1] = cnk[5][1][1];
    cnb[0][1][2] = cnk[5][1][2];
    cnb[0][2][0] = cnk[5][2][0];
    cnb[0][2][1] = cnk[5][2][1];
    cnb[0][2][2] = cnk[5][2][2];
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
    cnb[3][0][0] = cnk[12][0][0];
    cnb[3][0][1] = cnk[12][0][1];
    cnb[3][0][2] = cnk[12][0][2];
    cnb[3][1][0] = cnk[12][1][0];
    cnb[3][1][1] = cnk[12][1][1];
    cnb[3][1][2] = cnk[12][1][2];
    cnb[3][2][0] = cnk[12][2][0];
    cnb[3][2][1] = cnk[12][2][1];
    cnb[3][2][2] = cnk[12][2][2];
    cnb[4][0][0] = cnk[13][0][0];
    cnb[4][0][1] = cnk[13][0][1];
    cnb[4][0][2] = cnk[13][0][2];
    cnb[4][1][0] = cnk[13][1][0];
    cnb[4][1][1] = cnk[13][1][1];
    cnb[4][1][2] = cnk[13][1][2];
    cnb[4][2][0] = cnk[13][2][0];
    cnb[4][2][1] = cnk[13][2][1];
    cnb[4][2][2] = cnk[13][2][2];
    cnb[5][0][0] = cnk[14][0][0];
    cnb[5][0][1] = cnk[14][0][1];
    cnb[5][0][2] = cnk[14][0][2];
    cnb[5][1][0] = cnk[14][1][0];
    cnb[5][1][1] = cnk[14][1][1];
    cnb[5][1][2] = cnk[14][1][2];
    cnb[5][2][0] = cnk[14][2][0];
    cnb[5][2][1] = cnk[14][2][1];
    cnb[5][2][2] = cnk[14][2][2];
    cnb[6][0][0] = cnk[17][0][0];
    cnb[6][0][1] = cnk[17][0][1];
    cnb[6][0][2] = cnk[17][0][2];
    cnb[6][1][0] = cnk[17][1][0];
    cnb[6][1][1] = cnk[17][1][1];
    cnb[6][1][2] = cnk[17][1][2];
    cnb[6][2][0] = cnk[17][2][0];
    cnb[6][2][1] = cnk[17][2][1];
    cnb[6][2][2] = cnk[17][2][2];
    cnb[7][0][0] = cnk[20][0][0];
    cnb[7][0][1] = cnk[20][0][1];
    cnb[7][0][2] = cnk[20][0][2];
    cnb[7][1][0] = cnk[20][1][0];
    cnb[7][1][1] = cnk[20][1][1];
    cnb[7][1][2] = cnk[20][1][2];
    cnb[7][2][0] = cnk[20][2][0];
    cnb[7][2][1] = cnk[20][2][1];
    cnb[7][2][2] = cnk[20][2][2];
    cnb[8][0][0] = cnk[21][0][0];
    cnb[8][0][1] = cnk[21][0][1];
    cnb[8][0][2] = cnk[21][0][2];
    cnb[8][1][0] = cnk[21][1][0];
    cnb[8][1][1] = cnk[21][1][1];
    cnb[8][1][2] = cnk[21][1][2];
    cnb[8][2][0] = cnk[21][2][0];
    cnb[8][2][1] = cnk[21][2][1];
    cnb[8][2][2] = cnk[21][2][2];
    cnb[9][0][0] = cnk[22][0][0];
    cnb[9][0][1] = cnk[22][0][1];
    cnb[9][0][2] = cnk[22][0][2];
    cnb[9][1][0] = cnk[22][1][0];
    cnb[9][1][1] = cnk[22][1][1];
    cnb[9][1][2] = cnk[22][1][2];
    cnb[9][2][0] = cnk[22][2][0];
    cnb[9][2][1] = cnk[22][2][1];
    cnb[9][2][2] = cnk[22][2][2];
    cnb[10][0][0] = cnk[23][0][0];
    cnb[10][0][1] = cnk[23][0][1];
    cnb[10][0][2] = cnk[23][0][2];
    cnb[10][1][0] = cnk[23][1][0];
    cnb[10][1][1] = cnk[23][1][1];
    cnb[10][1][2] = cnk[23][1][2];
    cnb[10][2][0] = cnk[23][2][0];
    cnb[10][2][1] = cnk[23][2][1];
    cnb[10][2][2] = cnk[23][2][2];
    cnb[11][0][0] = cnk[26][0][0];
    cnb[11][0][1] = cnk[26][0][1];
    cnb[11][0][2] = cnk[26][0][2];
    cnb[11][1][0] = cnk[26][1][0];
    cnb[11][1][1] = cnk[26][1][1];
    cnb[11][1][2] = cnk[26][1][2];
    cnb[11][2][0] = cnk[26][2][0];
    cnb[11][2][1] = cnk[26][2][1];
    cnb[11][2][2] = cnk[26][2][2];
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
    rpp[9][0] = (pin[9][0]*q[9]);
    rpp[9][1] = (pin[9][1]*q[9]);
    rpp[9][2] = (pin[9][2]*q[9]);
    rpp[10][0] = (pin[10][0]*q[10]);
    rpp[10][1] = (pin[10][1]*q[10]);
    rpp[10][2] = (pin[10][2]*q[10]);
    rpp[18][0] = (pin[18][0]*q[18]);
    rpp[18][1] = (pin[18][1]*q[18]);
    rpp[18][2] = (pin[18][2]*q[18]);
    rpp[19][0] = (pin[19][0]*q[19]);
    rpp[19][1] = (pin[19][1]*q[19]);
    rpp[19][2] = (pin[19][2]*q[19]);
    rpri[0][0] = (ri[0][0]+rpp[0][0]);
    rpri[0][1] = (ri[0][1]+rpp[0][1]);
    rpri[0][2] = (ri[0][2]+rpp[0][2]);
    rpri[9][0] = (ri[2][0]+rpp[9][0]);
    rpri[9][1] = (ri[2][1]+rpp[9][1]);
    rpri[9][2] = (ri[2][2]+rpp[9][2]);
    rpri[18][0] = (ri[7][0]+rpp[18][0]);
    rpri[18][1] = (ri[7][1]+rpp[18][1]);
    rpri[18][2] = (ri[7][2]+rpp[18][2]);
    rik[0][0] = (ri[0][0]+rpp[0][0]);
    rik[0][1] = (ri[0][1]+rpp[0][1]);
    rik[0][2] = (ri[0][2]+rpp[0][2]);
    rik[6][0] = ((Cik[6][2][0]*ri[1][2])+((Cik[6][0][0]*ri[1][0])+(Cik[6][1][0]*
      ri[1][1])));
    rik[6][1] = ((Cik[6][2][1]*ri[1][2])+((Cik[6][0][1]*ri[1][0])+(Cik[6][1][1]*
      ri[1][1])));
    rik[6][2] = ((Cik[6][2][2]*ri[1][2])+((Cik[6][0][2]*ri[1][0])+(Cik[6][1][2]*
      ri[1][1])));
    rik[9][0] = (ri[2][0]+rpp[9][0]);
    rik[9][1] = (ri[2][1]+rpp[9][1]);
    rik[9][2] = (ri[2][2]+rpp[9][2]);
    rik[12][0] = (((Cik[12][2][0]*ri[3][2])+((Cik[12][0][0]*ri[3][0])+(
      Cik[12][1][0]*ri[3][1])))-rk[3][0]);
    rik[12][1] = (((Cik[12][2][1]*ri[3][2])+((Cik[12][0][1]*ri[3][0])+(
      Cik[12][1][1]*ri[3][1])))-rk[3][1]);
    rik[12][2] = (((Cik[12][2][2]*ri[3][2])+((Cik[12][0][2]*ri[3][0])+(
      Cik[12][1][2]*ri[3][1])))-rk[3][2]);
    rik[13][0] = (((Cik[13][2][0]*ri[4][2])+((Cik[13][0][0]*ri[4][0])+(
      Cik[13][1][0]*ri[4][1])))-rk[4][0]);
    rik[13][1] = (((Cik[13][2][1]*ri[4][2])+((Cik[13][0][1]*ri[4][0])+(
      Cik[13][1][1]*ri[4][1])))-rk[4][1]);
    rik[13][2] = (((Cik[13][2][2]*ri[4][2])+((Cik[13][0][2]*ri[4][0])+(
      Cik[13][1][2]*ri[4][1])))-rk[4][2]);
    rik[14][0] = (((Cik[14][2][0]*ri[5][2])+((Cik[14][0][0]*ri[5][0])+(
      Cik[14][1][0]*ri[5][1])))-rk[5][0]);
    rik[14][1] = (((Cik[14][2][1]*ri[5][2])+((Cik[14][0][1]*ri[5][0])+(
      Cik[14][1][1]*ri[5][1])))-rk[5][1]);
    rik[14][2] = (((Cik[14][2][2]*ri[5][2])+((Cik[14][0][2]*ri[5][0])+(
      Cik[14][1][2]*ri[5][1])))-rk[5][2]);
    rik[15][0] = ((Cik[15][2][0]*ri[6][2])+((Cik[15][0][0]*ri[6][0])+(
      Cik[15][1][0]*ri[6][1])));
    rik[15][1] = ((Cik[15][2][1]*ri[6][2])+((Cik[15][0][1]*ri[6][0])+(
      Cik[15][1][1]*ri[6][1])));
    rik[15][2] = ((Cik[15][2][2]*ri[6][2])+((Cik[15][0][2]*ri[6][0])+(
      Cik[15][1][2]*ri[6][1])));
    rik[18][0] = (ri[7][0]+rpp[18][0]);
    rik[18][1] = (ri[7][1]+rpp[18][1]);
    rik[18][2] = (ri[7][2]+rpp[18][2]);
    rik[21][0] = (((Cik[21][2][0]*ri[8][2])+((Cik[21][0][0]*ri[8][0])+(
      Cik[21][1][0]*ri[8][1])))-rk[8][0]);
    rik[21][1] = (((Cik[21][2][1]*ri[8][2])+((Cik[21][0][1]*ri[8][0])+(
      Cik[21][1][1]*ri[8][1])))-rk[8][1]);
    rik[21][2] = (((Cik[21][2][2]*ri[8][2])+((Cik[21][0][2]*ri[8][0])+(
      Cik[21][1][2]*ri[8][1])))-rk[8][2]);
    rik[22][0] = (((Cik[22][2][0]*ri[9][2])+((Cik[22][0][0]*ri[9][0])+(
      Cik[22][1][0]*ri[9][1])))-rk[9][0]);
    rik[22][1] = (((Cik[22][2][1]*ri[9][2])+((Cik[22][0][1]*ri[9][0])+(
      Cik[22][1][1]*ri[9][1])))-rk[9][1]);
    rik[22][2] = (((Cik[22][2][2]*ri[9][2])+((Cik[22][0][2]*ri[9][0])+(
      Cik[22][1][2]*ri[9][1])))-rk[9][2]);
    rik[23][0] = (((Cik[23][2][0]*ri[10][2])+((Cik[23][0][0]*ri[10][0])+(
      Cik[23][1][0]*ri[10][1])))-rk[10][0]);
    rik[23][1] = (((Cik[23][2][1]*ri[10][2])+((Cik[23][0][1]*ri[10][0])+(
      Cik[23][1][1]*ri[10][1])))-rk[10][1]);
    rik[23][2] = (((Cik[23][2][2]*ri[10][2])+((Cik[23][0][2]*ri[10][0])+(
      Cik[23][1][2]*ri[10][1])))-rk[10][2]);
    rik[24][0] = ((Cik[24][2][0]*ri[11][2])+((Cik[24][0][0]*ri[11][0])+(
      Cik[24][1][0]*ri[11][1])));
    rik[24][1] = ((Cik[24][2][1]*ri[11][2])+((Cik[24][0][1]*ri[11][0])+(
      Cik[24][1][1]*ri[11][1])));
    rik[24][2] = ((Cik[24][2][2]*ri[11][2])+((Cik[24][0][2]*ri[11][0])+(
      Cik[24][1][2]*ri[11][1])));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[0][0] = (ri[0][0]+rpp[0][0]);
    rnk[0][1] = (ri[0][1]+rpp[0][1]);
    rnk[0][2] = (ri[0][2]+rpp[0][2]);
    rnk[1][0] = (rnk[0][0]+rpp[1][0]);
    rnk[1][1] = (rnk[0][1]+rpp[1][1]);
    rnk[1][2] = (rnk[0][2]+rpp[1][2]);
    rnk[2][0] = (rnk[1][0]+rpp[2][0]);
    rnk[2][1] = (rnk[1][1]+rpp[2][1]);
    rnk[2][2] = (rnk[1][2]+rpp[2][2]);
    rnk[5][0] = (rnk[2][0]-((cnk[5][0][2]*rk[0][2])+((cnk[5][0][0]*rk[0][0])+(
      cnk[5][0][1]*rk[0][1]))));
    rnk[5][1] = (rnk[2][1]-((cnk[5][1][2]*rk[0][2])+((cnk[5][1][0]*rk[0][0])+(
      cnk[5][1][1]*rk[0][1]))));
    rnk[5][2] = (rnk[2][2]-((cnk[5][2][2]*rk[0][2])+((cnk[5][2][0]*rk[0][0])+(
      cnk[5][2][1]*rk[0][1]))));
    rnk[6][0] = (rnk[5][0]+((cnk[5][0][2]*ri[1][2])+((cnk[5][0][0]*ri[1][0])+(
      cnk[5][0][1]*ri[1][1]))));
    rnk[6][1] = (rnk[5][1]+((cnk[5][1][2]*ri[1][2])+((cnk[5][1][0]*ri[1][0])+(
      cnk[5][1][1]*ri[1][1]))));
    rnk[6][2] = (rnk[5][2]+((cnk[5][2][2]*ri[1][2])+((cnk[5][2][0]*ri[1][0])+(
      cnk[5][2][1]*ri[1][1]))));
    rnk[8][0] = (rnk[6][0]-((cnk[8][0][2]*rk[1][2])+((cnk[8][0][0]*rk[1][0])+(
      cnk[8][0][1]*rk[1][1]))));
    rnk[8][1] = (rnk[6][1]-((cnk[8][1][2]*rk[1][2])+((cnk[8][1][0]*rk[1][0])+(
      cnk[8][1][1]*rk[1][1]))));
    rnk[8][2] = (rnk[6][2]-((cnk[8][2][2]*rk[1][2])+((cnk[8][2][0]*rk[1][0])+(
      cnk[8][2][1]*rk[1][1]))));
    rnk[9][0] = ((rnk[8][0]+((cnk[8][0][2]*ri[2][2])+((cnk[8][0][0]*ri[2][0])+(
      cnk[8][0][1]*ri[2][1]))))+((cnk[8][0][2]*rpp[9][2])+((cnk[8][0][0]*
      rpp[9][0])+(cnk[8][0][1]*rpp[9][1]))));
    rnk[9][1] = ((rnk[8][1]+((cnk[8][1][2]*ri[2][2])+((cnk[8][1][0]*ri[2][0])+(
      cnk[8][1][1]*ri[2][1]))))+((cnk[8][1][2]*rpp[9][2])+((cnk[8][1][0]*
      rpp[9][0])+(cnk[8][1][1]*rpp[9][1]))));
    rnk[9][2] = ((rnk[8][2]+((cnk[8][2][2]*ri[2][2])+((cnk[8][2][0]*ri[2][0])+(
      cnk[8][2][1]*ri[2][1]))))+((cnk[8][2][2]*rpp[9][2])+((cnk[8][2][0]*
      rpp[9][0])+(cnk[8][2][1]*rpp[9][1]))));
    rnk[10][0] = (rnk[9][0]+((cnk[8][0][2]*rpp[10][2])+((cnk[8][0][0]*rpp[10][0]
      )+(cnk[8][0][1]*rpp[10][1]))));
    rnk[10][1] = (rnk[9][1]+((cnk[8][1][2]*rpp[10][2])+((cnk[8][1][0]*rpp[10][0]
      )+(cnk[8][1][1]*rpp[10][1]))));
    rnk[10][2] = (rnk[9][2]+((cnk[8][2][2]*rpp[10][2])+((cnk[8][2][0]*rpp[10][0]
      )+(cnk[8][2][1]*rpp[10][1]))));
    rnk[11][0] = (rnk[10][0]-((cnk[11][0][2]*rk[2][2])+((cnk[11][0][0]*rk[2][0])
      +(cnk[11][0][1]*rk[2][1]))));
    rnk[11][1] = (rnk[10][1]-((cnk[11][1][2]*rk[2][2])+((cnk[11][1][0]*rk[2][0])
      +(cnk[11][1][1]*rk[2][1]))));
    rnk[11][2] = (rnk[10][2]-((cnk[11][2][2]*rk[2][2])+((cnk[11][2][0]*rk[2][0])
      +(cnk[11][2][1]*rk[2][1]))));
    rnk[12][0] = ((rnk[11][0]+((cnk[11][0][2]*ri[3][2])+((cnk[11][0][0]*ri[3][0]
      )+(cnk[11][0][1]*ri[3][1]))))-((cnk[12][0][2]*rk[3][2])+((cnk[12][0][0]*
      rk[3][0])+(cnk[12][0][1]*rk[3][1]))));
    rnk[12][1] = ((rnk[11][1]+((cnk[11][1][2]*ri[3][2])+((cnk[11][1][0]*ri[3][0]
      )+(cnk[11][1][1]*ri[3][1]))))-((cnk[12][1][2]*rk[3][2])+((cnk[12][1][0]*
      rk[3][0])+(cnk[12][1][1]*rk[3][1]))));
    rnk[12][2] = ((rnk[11][2]+((cnk[11][2][2]*ri[3][2])+((cnk[11][2][0]*ri[3][0]
      )+(cnk[11][2][1]*ri[3][1]))))-((cnk[12][2][2]*rk[3][2])+((cnk[12][2][0]*
      rk[3][0])+(cnk[12][2][1]*rk[3][1]))));
    rnk[13][0] = ((rnk[12][0]+((cnk[12][0][2]*ri[4][2])+((cnk[12][0][0]*ri[4][0]
      )+(cnk[12][0][1]*ri[4][1]))))-((cnk[13][0][2]*rk[4][2])+((cnk[13][0][0]*
      rk[4][0])+(cnk[13][0][1]*rk[4][1]))));
    rnk[13][1] = ((rnk[12][1]+((cnk[12][1][2]*ri[4][2])+((cnk[12][1][0]*ri[4][0]
      )+(cnk[12][1][1]*ri[4][1]))))-((cnk[13][1][2]*rk[4][2])+((cnk[13][1][0]*
      rk[4][0])+(cnk[13][1][1]*rk[4][1]))));
    rnk[13][2] = ((rnk[12][2]+((cnk[12][2][2]*ri[4][2])+((cnk[12][2][0]*ri[4][0]
      )+(cnk[12][2][1]*ri[4][1]))))-((cnk[13][2][2]*rk[4][2])+((cnk[13][2][0]*
      rk[4][0])+(cnk[13][2][1]*rk[4][1]))));
    rnk[14][0] = ((rnk[13][0]+((cnk[13][0][2]*ri[5][2])+((cnk[13][0][0]*ri[5][0]
      )+(cnk[13][0][1]*ri[5][1]))))-((cnk[14][0][2]*rk[5][2])+((cnk[14][0][0]*
      rk[5][0])+(cnk[14][0][1]*rk[5][1]))));
    rnk[14][1] = ((rnk[13][1]+((cnk[13][1][2]*ri[5][2])+((cnk[13][1][0]*ri[5][0]
      )+(cnk[13][1][1]*ri[5][1]))))-((cnk[14][1][2]*rk[5][2])+((cnk[14][1][0]*
      rk[5][0])+(cnk[14][1][1]*rk[5][1]))));
    rnk[14][2] = ((rnk[13][2]+((cnk[13][2][2]*ri[5][2])+((cnk[13][2][0]*ri[5][0]
      )+(cnk[13][2][1]*ri[5][1]))))-((cnk[14][2][2]*rk[5][2])+((cnk[14][2][0]*
      rk[5][0])+(cnk[14][2][1]*rk[5][1]))));
    rnk[15][0] = (rnk[5][0]+((cnk[5][0][2]*ri[6][2])+((cnk[5][0][0]*ri[6][0])+(
      cnk[5][0][1]*ri[6][1]))));
    rnk[15][1] = (rnk[5][1]+((cnk[5][1][2]*ri[6][2])+((cnk[5][1][0]*ri[6][0])+(
      cnk[5][1][1]*ri[6][1]))));
    rnk[15][2] = (rnk[5][2]+((cnk[5][2][2]*ri[6][2])+((cnk[5][2][0]*ri[6][0])+(
      cnk[5][2][1]*ri[6][1]))));
    rnk[17][0] = (rnk[15][0]-((cnk[17][0][2]*rk[6][2])+((cnk[17][0][0]*rk[6][0])
      +(cnk[17][0][1]*rk[6][1]))));
    rnk[17][1] = (rnk[15][1]-((cnk[17][1][2]*rk[6][2])+((cnk[17][1][0]*rk[6][0])
      +(cnk[17][1][1]*rk[6][1]))));
    rnk[17][2] = (rnk[15][2]-((cnk[17][2][2]*rk[6][2])+((cnk[17][2][0]*rk[6][0])
      +(cnk[17][2][1]*rk[6][1]))));
    rnk[18][0] = ((rnk[17][0]+((cnk[17][0][2]*ri[7][2])+((cnk[17][0][0]*ri[7][0]
      )+(cnk[17][0][1]*ri[7][1]))))+((cnk[17][0][2]*rpp[18][2])+((cnk[17][0][0]*
      rpp[18][0])+(cnk[17][0][1]*rpp[18][1]))));
    rnk[18][1] = ((rnk[17][1]+((cnk[17][1][2]*ri[7][2])+((cnk[17][1][0]*ri[7][0]
      )+(cnk[17][1][1]*ri[7][1]))))+((cnk[17][1][2]*rpp[18][2])+((cnk[17][1][0]*
      rpp[18][0])+(cnk[17][1][1]*rpp[18][1]))));
    rnk[18][2] = ((rnk[17][2]+((cnk[17][2][2]*ri[7][2])+((cnk[17][2][0]*ri[7][0]
      )+(cnk[17][2][1]*ri[7][1]))))+((cnk[17][2][2]*rpp[18][2])+((cnk[17][2][0]*
      rpp[18][0])+(cnk[17][2][1]*rpp[18][1]))));
    rnk[19][0] = (rnk[18][0]+((cnk[17][0][2]*rpp[19][2])+((cnk[17][0][0]*
      rpp[19][0])+(cnk[17][0][1]*rpp[19][1]))));
    rnk[19][1] = (rnk[18][1]+((cnk[17][1][2]*rpp[19][2])+((cnk[17][1][0]*
      rpp[19][0])+(cnk[17][1][1]*rpp[19][1]))));
    rnk[19][2] = (rnk[18][2]+((cnk[17][2][2]*rpp[19][2])+((cnk[17][2][0]*
      rpp[19][0])+(cnk[17][2][1]*rpp[19][1]))));
    rnk[20][0] = (rnk[19][0]-((cnk[20][0][2]*rk[7][2])+((cnk[20][0][0]*rk[7][0])
      +(cnk[20][0][1]*rk[7][1]))));
    rnk[20][1] = (rnk[19][1]-((cnk[20][1][2]*rk[7][2])+((cnk[20][1][0]*rk[7][0])
      +(cnk[20][1][1]*rk[7][1]))));
    rnk[20][2] = (rnk[19][2]-((cnk[20][2][2]*rk[7][2])+((cnk[20][2][0]*rk[7][0])
      +(cnk[20][2][1]*rk[7][1]))));
    rnk[21][0] = ((rnk[20][0]+((cnk[20][0][2]*ri[8][2])+((cnk[20][0][0]*ri[8][0]
      )+(cnk[20][0][1]*ri[8][1]))))-((cnk[21][0][2]*rk[8][2])+((cnk[21][0][0]*
      rk[8][0])+(cnk[21][0][1]*rk[8][1]))));
    rnk[21][1] = ((rnk[20][1]+((cnk[20][1][2]*ri[8][2])+((cnk[20][1][0]*ri[8][0]
      )+(cnk[20][1][1]*ri[8][1]))))-((cnk[21][1][2]*rk[8][2])+((cnk[21][1][0]*
      rk[8][0])+(cnk[21][1][1]*rk[8][1]))));
    rnk[21][2] = ((rnk[20][2]+((cnk[20][2][2]*ri[8][2])+((cnk[20][2][0]*ri[8][0]
      )+(cnk[20][2][1]*ri[8][1]))))-((cnk[21][2][2]*rk[8][2])+((cnk[21][2][0]*
      rk[8][0])+(cnk[21][2][1]*rk[8][1]))));
    rnk[22][0] = ((rnk[21][0]+((cnk[21][0][2]*ri[9][2])+((cnk[21][0][0]*ri[9][0]
      )+(cnk[21][0][1]*ri[9][1]))))-((cnk[22][0][2]*rk[9][2])+((cnk[22][0][0]*
      rk[9][0])+(cnk[22][0][1]*rk[9][1]))));
    rnk[22][1] = ((rnk[21][1]+((cnk[21][1][2]*ri[9][2])+((cnk[21][1][0]*ri[9][0]
      )+(cnk[21][1][1]*ri[9][1]))))-((cnk[22][1][2]*rk[9][2])+((cnk[22][1][0]*
      rk[9][0])+(cnk[22][1][1]*rk[9][1]))));
    rnk[22][2] = ((rnk[21][2]+((cnk[21][2][2]*ri[9][2])+((cnk[21][2][0]*ri[9][0]
      )+(cnk[21][2][1]*ri[9][1]))))-((cnk[22][2][2]*rk[9][2])+((cnk[22][2][0]*
      rk[9][0])+(cnk[22][2][1]*rk[9][1]))));
    rnk[23][0] = ((rnk[22][0]+((cnk[22][0][2]*ri[10][2])+((cnk[22][0][0]*
      ri[10][0])+(cnk[22][0][1]*ri[10][1]))))-((cnk[23][0][2]*rk[10][2])+((
      cnk[23][0][0]*rk[10][0])+(cnk[23][0][1]*rk[10][1]))));
    rnk[23][1] = ((rnk[22][1]+((cnk[22][1][2]*ri[10][2])+((cnk[22][1][0]*
      ri[10][0])+(cnk[22][1][1]*ri[10][1]))))-((cnk[23][1][2]*rk[10][2])+((
      cnk[23][1][0]*rk[10][0])+(cnk[23][1][1]*rk[10][1]))));
    rnk[23][2] = ((rnk[22][2]+((cnk[22][2][2]*ri[10][2])+((cnk[22][2][0]*
      ri[10][0])+(cnk[22][2][1]*ri[10][1]))))-((cnk[23][2][2]*rk[10][2])+((
      cnk[23][2][0]*rk[10][0])+(cnk[23][2][1]*rk[10][1]))));
    rnk[24][0] = (rnk[5][0]+((cnk[5][0][2]*ri[11][2])+((cnk[5][0][0]*ri[11][0])+
      (cnk[5][0][1]*ri[11][1]))));
    rnk[24][1] = (rnk[5][1]+((cnk[5][1][2]*ri[11][2])+((cnk[5][1][0]*ri[11][0])+
      (cnk[5][1][1]*ri[11][1]))));
    rnk[24][2] = (rnk[5][2]+((cnk[5][2][2]*ri[11][2])+((cnk[5][2][0]*ri[11][0])+
      (cnk[5][2][1]*ri[11][1]))));
    rnk[26][0] = (rnk[24][0]-((cnk[26][0][2]*rk[11][2])+((cnk[26][0][0]*
      rk[11][0])+(cnk[26][0][1]*rk[11][1]))));
    rnk[26][1] = (rnk[24][1]-((cnk[26][1][2]*rk[11][2])+((cnk[26][1][0]*
      rk[11][0])+(cnk[26][1][1]*rk[11][1]))));
    rnk[26][2] = (rnk[24][2]-((cnk[26][2][2]*rk[11][2])+((cnk[26][2][0]*
      rk[11][0])+(cnk[26][2][1]*rk[11][1]))));
    rnb[0][0] = rnk[5][0];
    rnb[0][1] = rnk[5][1];
    rnb[0][2] = rnk[5][2];
    rnb[1][0] = rnk[8][0];
    rnb[1][1] = rnk[8][1];
    rnb[1][2] = rnk[8][2];
    rnb[2][0] = rnk[11][0];
    rnb[2][1] = rnk[11][1];
    rnb[2][2] = rnk[11][2];
    rnb[3][0] = rnk[12][0];
    rnb[3][1] = rnk[12][1];
    rnb[3][2] = rnk[12][2];
    rnb[4][0] = rnk[13][0];
    rnb[4][1] = rnk[13][1];
    rnb[4][2] = rnk[13][2];
    rnb[5][0] = rnk[14][0];
    rnb[5][1] = rnk[14][1];
    rnb[5][2] = rnk[14][2];
    rnb[6][0] = rnk[17][0];
    rnb[6][1] = rnk[17][1];
    rnb[6][2] = rnk[17][2];
    rnb[7][0] = rnk[20][0];
    rnb[7][1] = rnk[20][1];
    rnb[7][2] = rnk[20][2];
    rnb[8][0] = rnk[21][0];
    rnb[8][1] = rnk[21][1];
    rnb[8][2] = rnk[21][2];
    rnb[9][0] = rnk[22][0];
    rnb[9][1] = rnk[22][1];
    rnb[9][2] = rnk[22][2];
    rnb[10][0] = rnk[23][0];
    rnb[10][1] = rnk[23][1];
    rnb[10][2] = rnk[23][2];
    rnb[11][0] = rnk[26][0];
    rnb[11][1] = rnk[26][1];
    rnb[11][2] = rnk[26][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = ((1./mtot)*((mk[11]*rnk[26][0])+((mk[10]*rnk[23][0])+((mk[9]*
      rnk[22][0])+((mk[8]*rnk[21][0])+((mk[7]*rnk[20][0])+((mk[6]*rnk[17][0])+((
      mk[5]*rnk[14][0])+((mk[4]*rnk[13][0])+((mk[3]*rnk[12][0])+((mk[2]*
      rnk[11][0])+((mk[0]*rnk[5][0])+(mk[1]*rnk[8][0])))))))))))));
    com[1] = ((1./mtot)*((mk[11]*rnk[26][1])+((mk[10]*rnk[23][1])+((mk[9]*
      rnk[22][1])+((mk[8]*rnk[21][1])+((mk[7]*rnk[20][1])+((mk[6]*rnk[17][1])+((
      mk[5]*rnk[14][1])+((mk[4]*rnk[13][1])+((mk[3]*rnk[12][1])+((mk[2]*
      rnk[11][1])+((mk[0]*rnk[5][1])+(mk[1]*rnk[8][1])))))))))))));
    com[2] = ((1./mtot)*((mk[11]*rnk[26][2])+((mk[10]*rnk[23][2])+((mk[9]*
      rnk[22][2])+((mk[8]*rnk[21][2])+((mk[7]*rnk[20][2])+((mk[6]*rnk[17][2])+((
      mk[5]*rnk[14][2])+((mk[4]*rnk[13][2])+((mk[3]*rnk[12][2])+((mk[2]*
      rnk[11][2])+((mk[0]*rnk[5][2])+(mk[1]*rnk[8][2])))))))))))));
/*
Compute constraint position errors
*/
    skipqs: ;
/*
Check for locked gimbal tree joint
*/
    if ((fabs((fabs(((((Cik[3][2][2]*pin[0][2])+((Cik[3][2][0]*pin[0][0])+(
      Cik[3][2][1]*pin[0][1])))*((cnk[5][2][2]*pin[2][2])+((cnk[5][2][0]*
      pin[2][0])+(cnk[5][2][1]*pin[2][1]))))+((((Cik[3][0][2]*pin[0][2])+((
      Cik[3][0][0]*pin[0][0])+(Cik[3][0][1]*pin[0][1])))*((cnk[5][0][2]*
      pin[2][2])+((cnk[5][0][0]*pin[2][0])+(cnk[5][0][1]*pin[2][1]))))+(((
      Cik[3][1][2]*pin[0][2])+((Cik[3][1][0]*pin[0][0])+(Cik[3][1][1]*pin[0][1])
      ))*((cnk[5][1][2]*pin[2][2])+((cnk[5][1][0]*pin[2][0])+(cnk[5][1][1]*
      pin[2][1])))))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[6][2][2]*pin[6][2])+((cnk[6][2][0]*pin[6][0])+(
      cnk[6][2][1]*pin[6][1])))*((cnk[8][2][2]*pin[8][2])+((cnk[8][2][0]*
      pin[8][0])+(cnk[8][2][1]*pin[8][1]))))+((((cnk[6][0][2]*pin[6][2])+((
      cnk[6][0][0]*pin[6][0])+(cnk[6][0][1]*pin[6][1])))*((cnk[8][0][2]*
      pin[8][2])+((cnk[8][0][0]*pin[8][0])+(cnk[8][0][1]*pin[8][1]))))+(((
      cnk[6][1][2]*pin[6][2])+((cnk[6][1][0]*pin[6][0])+(cnk[6][1][1]*pin[6][1])
      ))*((cnk[8][1][2]*pin[8][2])+((cnk[8][1][0]*pin[8][0])+(cnk[8][1][1]*
      pin[8][1])))))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[15][2][2]*pin[15][2])+((cnk[15][2][0]*pin[15][0])+(
      cnk[15][2][1]*pin[15][1])))*((cnk[17][2][2]*pin[17][2])+((cnk[17][2][0]*
      pin[17][0])+(cnk[17][2][1]*pin[17][1]))))+((((cnk[15][0][2]*pin[15][2])+((
      cnk[15][0][0]*pin[15][0])+(cnk[15][0][1]*pin[15][1])))*((cnk[17][0][2]*
      pin[17][2])+((cnk[17][0][0]*pin[17][0])+(cnk[17][0][1]*pin[17][1]))))+(((
      cnk[15][1][2]*pin[15][2])+((cnk[15][1][0]*pin[15][0])+(cnk[15][1][1]*
      pin[15][1])))*((cnk[17][1][2]*pin[17][2])+((cnk[17][1][0]*pin[17][0])+(
      cnk[17][1][1]*pin[17][1])))))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((((cnk[24][2][2]*pin[24][2])+((cnk[24][2][0]*pin[24][0])+(
      cnk[24][2][1]*pin[24][1])))*((cnk[26][2][2]*pin[26][2])+((cnk[26][2][0]*
      pin[26][0])+(cnk[26][2][1]*pin[26][1]))))+((((cnk[24][0][2]*pin[24][2])+((
      cnk[24][0][0]*pin[24][0])+(cnk[24][0][1]*pin[24][1])))*((cnk[26][0][2]*
      pin[26][2])+((cnk[26][0][0]*pin[26][0])+(cnk[26][0][1]*pin[26][1]))))+(((
      cnk[24][1][2]*pin[24][2])+((cnk[24][1][0]*pin[24][0])+(cnk[24][1][1]*
      pin[24][1])))*((cnk[26][1][2]*pin[26][2])+((cnk[26][1][0]*pin[26][0])+(
      cnk[26][1][1]*pin[26][1])))))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    sduperr(curtim,q,&perr[23]);
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 27; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
    Wik[3][0] = (pin[0][0]*u[3]);
    Wik[3][1] = (pin[0][1]*u[3]);
    Wik[3][2] = (pin[0][2]*u[3]);
    Wik[4][0] = (pin[1][0]*u[4]);
    Wik[4][1] = (pin[1][1]*u[4]);
    Wik[4][2] = (pin[1][2]*u[4]);
    Wik[5][0] = (pin[2][0]*u[5]);
    Wik[5][1] = (pin[2][1]*u[5]);
    Wik[5][2] = (pin[2][2]*u[5]);
    Wik[6][0] = (pin[6][0]*u[6]);
    Wik[6][1] = (pin[6][1]*u[6]);
    Wik[6][2] = (pin[6][2]*u[6]);
    Wik[7][0] = (pin[7][0]*u[7]);
    Wik[7][1] = (pin[7][1]*u[7]);
    Wik[7][2] = (pin[7][2]*u[7]);
    Wik[8][0] = (pin[8][0]*u[8]);
    Wik[8][1] = (pin[8][1]*u[8]);
    Wik[8][2] = (pin[8][2]*u[8]);
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
    Vik[0][0] = (pin[0][0]*u[0]);
    Vik[0][1] = (pin[0][1]*u[0]);
    Vik[0][2] = (pin[0][2]*u[0]);
    Vik[1][0] = (pin[1][0]*u[1]);
    Vik[1][1] = (pin[1][1]*u[1]);
    Vik[1][2] = (pin[1][2]*u[1]);
    Vik[2][0] = (pin[2][0]*u[2]);
    Vik[2][1] = (pin[2][1]*u[2]);
    Vik[2][2] = (pin[2][2]*u[2]);
    Vik[9][0] = (pin[9][0]*u[9]);
    Vik[9][1] = (pin[9][1]*u[9]);
    Vik[9][2] = (pin[9][2]*u[9]);
    Vik[10][0] = (pin[10][0]*u[10]);
    Vik[10][1] = (pin[10][1]*u[10]);
    Vik[10][2] = (pin[10][2]*u[10]);
    Vik[18][0] = (pin[18][0]*u[18]);
    Vik[18][1] = (pin[18][1]*u[18]);
    Vik[18][2] = (pin[18][2]*u[18]);
    Vik[19][0] = (pin[19][0]*u[19]);
    Vik[19][1] = (pin[19][1]*u[19]);
    Vik[19][2] = (pin[19][2]*u[19]);
/*
Compute wk & wb (angular velocities)
*/
    wk[4][0] = (Wik[4][0]+((Cik[4][2][0]*Wik[3][2])+((Cik[4][0][0]*Wik[3][0])+(
      Cik[4][1][0]*Wik[3][1]))));
    wk[4][1] = (Wik[4][1]+((Cik[4][2][1]*Wik[3][2])+((Cik[4][0][1]*Wik[3][0])+(
      Cik[4][1][1]*Wik[3][1]))));
    wk[4][2] = (Wik[4][2]+((Cik[4][2][2]*Wik[3][2])+((Cik[4][0][2]*Wik[3][0])+(
      Cik[4][1][2]*Wik[3][1]))));
    wk[5][0] = (Wik[5][0]+((Cik[5][2][0]*wk[4][2])+((Cik[5][0][0]*wk[4][0])+(
      Cik[5][1][0]*wk[4][1]))));
    wk[5][1] = (Wik[5][1]+((Cik[5][2][1]*wk[4][2])+((Cik[5][0][1]*wk[4][0])+(
      Cik[5][1][1]*wk[4][1]))));
    wk[5][2] = (Wik[5][2]+((Cik[5][2][2]*wk[4][2])+((Cik[5][0][2]*wk[4][0])+(
      Cik[5][1][2]*wk[4][1]))));
    wk[6][0] = (Wik[6][0]+((Cik[6][2][0]*wk[5][2])+((Cik[6][0][0]*wk[5][0])+(
      Cik[6][1][0]*wk[5][1]))));
    wk[6][1] = (Wik[6][1]+((Cik[6][2][1]*wk[5][2])+((Cik[6][0][1]*wk[5][0])+(
      Cik[6][1][1]*wk[5][1]))));
    wk[6][2] = (Wik[6][2]+((Cik[6][2][2]*wk[5][2])+((Cik[6][0][2]*wk[5][0])+(
      Cik[6][1][2]*wk[5][1]))));
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
    wk[11][0] = (Wik[11][0]+((Cik[11][2][0]*wk[8][2])+((Cik[11][0][0]*wk[8][0])+
      (Cik[11][1][0]*wk[8][1]))));
    wk[11][1] = (Wik[11][1]+((Cik[11][2][1]*wk[8][2])+((Cik[11][0][1]*wk[8][0])+
      (Cik[11][1][1]*wk[8][1]))));
    wk[11][2] = (Wik[11][2]+((Cik[11][2][2]*wk[8][2])+((Cik[11][0][2]*wk[8][0])+
      (Cik[11][1][2]*wk[8][1]))));
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
    wk[15][0] = (Wik[15][0]+((Cik[15][2][0]*wk[5][2])+((Cik[15][0][0]*wk[5][0])+
      (Cik[15][1][0]*wk[5][1]))));
    wk[15][1] = (Wik[15][1]+((Cik[15][2][1]*wk[5][2])+((Cik[15][0][1]*wk[5][0])+
      (Cik[15][1][1]*wk[5][1]))));
    wk[15][2] = (Wik[15][2]+((Cik[15][2][2]*wk[5][2])+((Cik[15][0][2]*wk[5][0])+
      (Cik[15][1][2]*wk[5][1]))));
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
    wk[20][0] = (Wik[20][0]+((Cik[20][2][0]*wk[17][2])+((Cik[20][0][0]*wk[17][0]
      )+(Cik[20][1][0]*wk[17][1]))));
    wk[20][1] = (Wik[20][1]+((Cik[20][2][1]*wk[17][2])+((Cik[20][0][1]*wk[17][0]
      )+(Cik[20][1][1]*wk[17][1]))));
    wk[20][2] = (Wik[20][2]+((Cik[20][2][2]*wk[17][2])+((Cik[20][0][2]*wk[17][0]
      )+(Cik[20][1][2]*wk[17][1]))));
    wk[21][0] = (Wik[21][0]+((Cik[21][2][0]*wk[20][2])+((Cik[21][0][0]*wk[20][0]
      )+(Cik[21][1][0]*wk[20][1]))));
    wk[21][1] = (Wik[21][1]+((Cik[21][2][1]*wk[20][2])+((Cik[21][0][1]*wk[20][0]
      )+(Cik[21][1][1]*wk[20][1]))));
    wk[21][2] = (Wik[21][2]+((Cik[21][2][2]*wk[20][2])+((Cik[21][0][2]*wk[20][0]
      )+(Cik[21][1][2]*wk[20][1]))));
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
    wk[24][0] = (Wik[24][0]+((Cik[24][2][0]*wk[5][2])+((Cik[24][0][0]*wk[5][0])+
      (Cik[24][1][0]*wk[5][1]))));
    wk[24][1] = (Wik[24][1]+((Cik[24][2][1]*wk[5][2])+((Cik[24][0][1]*wk[5][0])+
      (Cik[24][1][1]*wk[5][1]))));
    wk[24][2] = (Wik[24][2]+((Cik[24][2][2]*wk[5][2])+((Cik[24][0][2]*wk[5][0])+
      (Cik[24][1][2]*wk[5][1]))));
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
    wb[0][0] = wk[5][0];
    wb[0][1] = wk[5][1];
    wb[0][2] = wk[5][2];
    wb[1][0] = wk[8][0];
    wb[1][1] = wk[8][1];
    wb[1][2] = wk[8][2];
    wb[2][0] = wk[11][0];
    wb[2][1] = wk[11][1];
    wb[2][2] = wk[11][2];
    wb[3][0] = wk[12][0];
    wb[3][1] = wk[12][1];
    wb[3][2] = wk[12][2];
    wb[4][0] = wk[13][0];
    wb[4][1] = wk[13][1];
    wb[4][2] = wk[13][2];
    wb[5][0] = wk[14][0];
    wb[5][1] = wk[14][1];
    wb[5][2] = wk[14][2];
    wb[6][0] = wk[17][0];
    wb[6][1] = wk[17][1];
    wb[6][2] = wk[17][2];
    wb[7][0] = wk[20][0];
    wb[7][1] = wk[20][1];
    wb[7][2] = wk[20][2];
    wb[8][0] = wk[21][0];
    wb[8][1] = wk[21][1];
    wb[8][2] = wk[21][2];
    wb[9][0] = wk[22][0];
    wb[9][1] = wk[22][1];
    wb[9][2] = wk[22][2];
    wb[10][0] = wk[23][0];
    wb[10][1] = wk[23][1];
    wb[10][2] = wk[23][2];
    wb[11][0] = wk[26][0];
    wb[11][1] = wk[26][1];
    wb[11][2] = wk[26][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[6][0] = ((ri[1][2]*wk[5][1])-(ri[1][1]*wk[5][2]));
    Wirk[6][1] = ((ri[1][0]*wk[5][2])-(ri[1][2]*wk[5][0]));
    Wirk[6][2] = ((ri[1][1]*wk[5][0])-(ri[1][0]*wk[5][1]));
    Wirk[9][0] = ((ri[2][2]*wk[8][1])-(ri[2][1]*wk[8][2]));
    Wirk[9][1] = ((ri[2][0]*wk[8][2])-(ri[2][2]*wk[8][0]));
    Wirk[9][2] = ((ri[2][1]*wk[8][0])-(ri[2][0]*wk[8][1]));
    Wirk[12][0] = ((ri[3][2]*wk[11][1])-(ri[3][1]*wk[11][2]));
    Wirk[12][1] = ((ri[3][0]*wk[11][2])-(ri[3][2]*wk[11][0]));
    Wirk[12][2] = ((ri[3][1]*wk[11][0])-(ri[3][0]*wk[11][1]));
    Wirk[13][0] = ((ri[4][2]*wk[12][1])-(ri[4][1]*wk[12][2]));
    Wirk[13][1] = ((ri[4][0]*wk[12][2])-(ri[4][2]*wk[12][0]));
    Wirk[13][2] = ((ri[4][1]*wk[12][0])-(ri[4][0]*wk[12][1]));
    Wirk[14][0] = ((ri[5][2]*wk[13][1])-(ri[5][1]*wk[13][2]));
    Wirk[14][1] = ((ri[5][0]*wk[13][2])-(ri[5][2]*wk[13][0]));
    Wirk[14][2] = ((ri[5][1]*wk[13][0])-(ri[5][0]*wk[13][1]));
    Wirk[15][0] = ((ri[6][2]*wk[5][1])-(ri[6][1]*wk[5][2]));
    Wirk[15][1] = ((ri[6][0]*wk[5][2])-(ri[6][2]*wk[5][0]));
    Wirk[15][2] = ((ri[6][1]*wk[5][0])-(ri[6][0]*wk[5][1]));
    Wirk[18][0] = ((ri[7][2]*wk[17][1])-(ri[7][1]*wk[17][2]));
    Wirk[18][1] = ((ri[7][0]*wk[17][2])-(ri[7][2]*wk[17][0]));
    Wirk[18][2] = ((ri[7][1]*wk[17][0])-(ri[7][0]*wk[17][1]));
    Wirk[21][0] = ((ri[8][2]*wk[20][1])-(ri[8][1]*wk[20][2]));
    Wirk[21][1] = ((ri[8][0]*wk[20][2])-(ri[8][2]*wk[20][0]));
    Wirk[21][2] = ((ri[8][1]*wk[20][0])-(ri[8][0]*wk[20][1]));
    Wirk[22][0] = ((ri[9][2]*wk[21][1])-(ri[9][1]*wk[21][2]));
    Wirk[22][1] = ((ri[9][0]*wk[21][2])-(ri[9][2]*wk[21][0]));
    Wirk[22][2] = ((ri[9][1]*wk[21][0])-(ri[9][0]*wk[21][1]));
    Wirk[23][0] = ((ri[10][2]*wk[22][1])-(ri[10][1]*wk[22][2]));
    Wirk[23][1] = ((ri[10][0]*wk[22][2])-(ri[10][2]*wk[22][0]));
    Wirk[23][2] = ((ri[10][1]*wk[22][0])-(ri[10][0]*wk[22][1]));
    Wirk[24][0] = ((ri[11][2]*wk[5][1])-(ri[11][1]*wk[5][2]));
    Wirk[24][1] = ((ri[11][0]*wk[5][2])-(ri[11][2]*wk[5][0]));
    Wirk[24][2] = ((ri[11][1]*wk[5][0])-(ri[11][0]*wk[5][1]));
    Wkrpk[5][0] = ((rk[0][1]*wk[5][2])-(rk[0][2]*wk[5][1]));
    Wkrpk[5][1] = ((rk[0][2]*wk[5][0])-(rk[0][0]*wk[5][2]));
    Wkrpk[5][2] = ((rk[0][0]*wk[5][1])-(rk[0][1]*wk[5][0]));
    Wkrpk[8][0] = ((rk[1][1]*wk[8][2])-(rk[1][2]*wk[8][1]));
    Wkrpk[8][1] = ((rk[1][2]*wk[8][0])-(rk[1][0]*wk[8][2]));
    Wkrpk[8][2] = ((rk[1][0]*wk[8][1])-(rk[1][1]*wk[8][0]));
    Wkrpk[9][0] = ((rpp[9][2]*wk[8][1])-(rpp[9][1]*wk[8][2]));
    Wkrpk[9][1] = ((rpp[9][0]*wk[8][2])-(rpp[9][2]*wk[8][0]));
    Wkrpk[9][2] = ((rpp[9][1]*wk[8][0])-(rpp[9][0]*wk[8][1]));
    Wkrpk[10][0] = ((rpp[10][2]*wk[8][1])-(rpp[10][1]*wk[8][2]));
    Wkrpk[10][1] = ((rpp[10][0]*wk[8][2])-(rpp[10][2]*wk[8][0]));
    Wkrpk[10][2] = ((rpp[10][1]*wk[8][0])-(rpp[10][0]*wk[8][1]));
    Wkrpk[11][0] = ((rk[2][1]*wk[11][2])-(rk[2][2]*wk[11][1]));
    Wkrpk[11][1] = ((rk[2][2]*wk[11][0])-(rk[2][0]*wk[11][2]));
    Wkrpk[11][2] = ((rk[2][0]*wk[11][1])-(rk[2][1]*wk[11][0]));
    Wkrpk[12][0] = ((rk[3][1]*wk[12][2])-(rk[3][2]*wk[12][1]));
    Wkrpk[12][1] = ((rk[3][2]*wk[12][0])-(rk[3][0]*wk[12][2]));
    Wkrpk[12][2] = ((rk[3][0]*wk[12][1])-(rk[3][1]*wk[12][0]));
    Wkrpk[13][0] = ((rk[4][1]*wk[13][2])-(rk[4][2]*wk[13][1]));
    Wkrpk[13][1] = ((rk[4][2]*wk[13][0])-(rk[4][0]*wk[13][2]));
    Wkrpk[13][2] = ((rk[4][0]*wk[13][1])-(rk[4][1]*wk[13][0]));
    Wkrpk[14][0] = ((rk[5][1]*wk[14][2])-(rk[5][2]*wk[14][1]));
    Wkrpk[14][1] = ((rk[5][2]*wk[14][0])-(rk[5][0]*wk[14][2]));
    Wkrpk[14][2] = ((rk[5][0]*wk[14][1])-(rk[5][1]*wk[14][0]));
    Wkrpk[17][0] = ((rk[6][1]*wk[17][2])-(rk[6][2]*wk[17][1]));
    Wkrpk[17][1] = ((rk[6][2]*wk[17][0])-(rk[6][0]*wk[17][2]));
    Wkrpk[17][2] = ((rk[6][0]*wk[17][1])-(rk[6][1]*wk[17][0]));
    Wkrpk[18][0] = ((rpp[18][2]*wk[17][1])-(rpp[18][1]*wk[17][2]));
    Wkrpk[18][1] = ((rpp[18][0]*wk[17][2])-(rpp[18][2]*wk[17][0]));
    Wkrpk[18][2] = ((rpp[18][1]*wk[17][0])-(rpp[18][0]*wk[17][1]));
    Wkrpk[19][0] = ((rpp[19][2]*wk[17][1])-(rpp[19][1]*wk[17][2]));
    Wkrpk[19][1] = ((rpp[19][0]*wk[17][2])-(rpp[19][2]*wk[17][0]));
    Wkrpk[19][2] = ((rpp[19][1]*wk[17][0])-(rpp[19][0]*wk[17][1]));
    Wkrpk[20][0] = ((rk[7][1]*wk[20][2])-(rk[7][2]*wk[20][1]));
    Wkrpk[20][1] = ((rk[7][2]*wk[20][0])-(rk[7][0]*wk[20][2]));
    Wkrpk[20][2] = ((rk[7][0]*wk[20][1])-(rk[7][1]*wk[20][0]));
    Wkrpk[21][0] = ((rk[8][1]*wk[21][2])-(rk[8][2]*wk[21][1]));
    Wkrpk[21][1] = ((rk[8][2]*wk[21][0])-(rk[8][0]*wk[21][2]));
    Wkrpk[21][2] = ((rk[8][0]*wk[21][1])-(rk[8][1]*wk[21][0]));
    Wkrpk[22][0] = ((rk[9][1]*wk[22][2])-(rk[9][2]*wk[22][1]));
    Wkrpk[22][1] = ((rk[9][2]*wk[22][0])-(rk[9][0]*wk[22][2]));
    Wkrpk[22][2] = ((rk[9][0]*wk[22][1])-(rk[9][1]*wk[22][0]));
    Wkrpk[23][0] = ((rk[10][1]*wk[23][2])-(rk[10][2]*wk[23][1]));
    Wkrpk[23][1] = ((rk[10][2]*wk[23][0])-(rk[10][0]*wk[23][2]));
    Wkrpk[23][2] = ((rk[10][0]*wk[23][1])-(rk[10][1]*wk[23][0]));
    Wkrpk[26][0] = ((rk[11][1]*wk[26][2])-(rk[11][2]*wk[26][1]));
    Wkrpk[26][1] = ((rk[11][2]*wk[26][0])-(rk[11][0]*wk[26][2]));
    Wkrpk[26][2] = ((rk[11][0]*wk[26][1])-(rk[11][1]*wk[26][0]));
    VikWkr[9][0] = (Vik[9][0]+Wkrpk[9][0]);
    VikWkr[9][1] = (Vik[9][1]+Wkrpk[9][1]);
    VikWkr[9][2] = (Vik[9][2]+Wkrpk[9][2]);
    VikWkr[10][0] = (Vik[10][0]+Wkrpk[10][0]);
    VikWkr[10][1] = (Vik[10][1]+Wkrpk[10][1]);
    VikWkr[10][2] = (Vik[10][2]+Wkrpk[10][2]);
    VikWkr[18][0] = (Vik[18][0]+Wkrpk[18][0]);
    VikWkr[18][1] = (Vik[18][1]+Wkrpk[18][1]);
    VikWkr[18][2] = (Vik[18][2]+Wkrpk[18][2]);
    VikWkr[19][0] = (Vik[19][0]+Wkrpk[19][0]);
    VikWkr[19][1] = (Vik[19][1]+Wkrpk[19][1]);
    VikWkr[19][2] = (Vik[19][2]+Wkrpk[19][2]);
    IkWk[5][0] = ((ik[0][0][2]*wk[5][2])+((ik[0][0][0]*wk[5][0])+(ik[0][0][1]*
      wk[5][1])));
    IkWk[5][1] = ((ik[0][1][2]*wk[5][2])+((ik[0][1][0]*wk[5][0])+(ik[0][1][1]*
      wk[5][1])));
    IkWk[5][2] = ((ik[0][2][2]*wk[5][2])+((ik[0][2][0]*wk[5][0])+(ik[0][2][1]*
      wk[5][1])));
    WkIkWk[5][0] = ((IkWk[5][2]*wk[5][1])-(IkWk[5][1]*wk[5][2]));
    WkIkWk[5][1] = ((IkWk[5][0]*wk[5][2])-(IkWk[5][2]*wk[5][0]));
    WkIkWk[5][2] = ((IkWk[5][1]*wk[5][0])-(IkWk[5][0]*wk[5][1]));
    IkWk[8][0] = ((ik[1][0][2]*wk[8][2])+((ik[1][0][0]*wk[8][0])+(ik[1][0][1]*
      wk[8][1])));
    IkWk[8][1] = ((ik[1][1][2]*wk[8][2])+((ik[1][1][0]*wk[8][0])+(ik[1][1][1]*
      wk[8][1])));
    IkWk[8][2] = ((ik[1][2][2]*wk[8][2])+((ik[1][2][0]*wk[8][0])+(ik[1][2][1]*
      wk[8][1])));
    WkIkWk[8][0] = ((IkWk[8][2]*wk[8][1])-(IkWk[8][1]*wk[8][2]));
    WkIkWk[8][1] = ((IkWk[8][0]*wk[8][2])-(IkWk[8][2]*wk[8][0]));
    WkIkWk[8][2] = ((IkWk[8][1]*wk[8][0])-(IkWk[8][0]*wk[8][1]));
    IkWk[11][0] = ((ik[2][0][2]*wk[11][2])+((ik[2][0][0]*wk[11][0])+(ik[2][0][1]
      *wk[11][1])));
    IkWk[11][1] = ((ik[2][1][2]*wk[11][2])+((ik[2][1][0]*wk[11][0])+(ik[2][1][1]
      *wk[11][1])));
    IkWk[11][2] = ((ik[2][2][2]*wk[11][2])+((ik[2][2][0]*wk[11][0])+(ik[2][2][1]
      *wk[11][1])));
    WkIkWk[11][0] = ((IkWk[11][2]*wk[11][1])-(IkWk[11][1]*wk[11][2]));
    WkIkWk[11][1] = ((IkWk[11][0]*wk[11][2])-(IkWk[11][2]*wk[11][0]));
    WkIkWk[11][2] = ((IkWk[11][1]*wk[11][0])-(IkWk[11][0]*wk[11][1]));
    IkWk[12][0] = ((ik[3][0][2]*wk[12][2])+((ik[3][0][0]*wk[12][0])+(ik[3][0][1]
      *wk[12][1])));
    IkWk[12][1] = ((ik[3][1][2]*wk[12][2])+((ik[3][1][0]*wk[12][0])+(ik[3][1][1]
      *wk[12][1])));
    IkWk[12][2] = ((ik[3][2][2]*wk[12][2])+((ik[3][2][0]*wk[12][0])+(ik[3][2][1]
      *wk[12][1])));
    WkIkWk[12][0] = ((IkWk[12][2]*wk[12][1])-(IkWk[12][1]*wk[12][2]));
    WkIkWk[12][1] = ((IkWk[12][0]*wk[12][2])-(IkWk[12][2]*wk[12][0]));
    WkIkWk[12][2] = ((IkWk[12][1]*wk[12][0])-(IkWk[12][0]*wk[12][1]));
    IkWk[13][0] = ((ik[4][0][2]*wk[13][2])+((ik[4][0][0]*wk[13][0])+(ik[4][0][1]
      *wk[13][1])));
    IkWk[13][1] = ((ik[4][1][2]*wk[13][2])+((ik[4][1][0]*wk[13][0])+(ik[4][1][1]
      *wk[13][1])));
    IkWk[13][2] = ((ik[4][2][2]*wk[13][2])+((ik[4][2][0]*wk[13][0])+(ik[4][2][1]
      *wk[13][1])));
    WkIkWk[13][0] = ((IkWk[13][2]*wk[13][1])-(IkWk[13][1]*wk[13][2]));
    WkIkWk[13][1] = ((IkWk[13][0]*wk[13][2])-(IkWk[13][2]*wk[13][0]));
    WkIkWk[13][2] = ((IkWk[13][1]*wk[13][0])-(IkWk[13][0]*wk[13][1]));
    IkWk[14][0] = ((ik[5][0][2]*wk[14][2])+((ik[5][0][0]*wk[14][0])+(ik[5][0][1]
      *wk[14][1])));
    IkWk[14][1] = ((ik[5][1][2]*wk[14][2])+((ik[5][1][0]*wk[14][0])+(ik[5][1][1]
      *wk[14][1])));
    IkWk[14][2] = ((ik[5][2][2]*wk[14][2])+((ik[5][2][0]*wk[14][0])+(ik[5][2][1]
      *wk[14][1])));
    WkIkWk[14][0] = ((IkWk[14][2]*wk[14][1])-(IkWk[14][1]*wk[14][2]));
    WkIkWk[14][1] = ((IkWk[14][0]*wk[14][2])-(IkWk[14][2]*wk[14][0]));
    WkIkWk[14][2] = ((IkWk[14][1]*wk[14][0])-(IkWk[14][0]*wk[14][1]));
    IkWk[17][0] = ((ik[6][0][2]*wk[17][2])+((ik[6][0][0]*wk[17][0])+(ik[6][0][1]
      *wk[17][1])));
    IkWk[17][1] = ((ik[6][1][2]*wk[17][2])+((ik[6][1][0]*wk[17][0])+(ik[6][1][1]
      *wk[17][1])));
    IkWk[17][2] = ((ik[6][2][2]*wk[17][2])+((ik[6][2][0]*wk[17][0])+(ik[6][2][1]
      *wk[17][1])));
    WkIkWk[17][0] = ((IkWk[17][2]*wk[17][1])-(IkWk[17][1]*wk[17][2]));
    WkIkWk[17][1] = ((IkWk[17][0]*wk[17][2])-(IkWk[17][2]*wk[17][0]));
    WkIkWk[17][2] = ((IkWk[17][1]*wk[17][0])-(IkWk[17][0]*wk[17][1]));
    IkWk[20][0] = ((ik[7][0][2]*wk[20][2])+((ik[7][0][0]*wk[20][0])+(ik[7][0][1]
      *wk[20][1])));
    IkWk[20][1] = ((ik[7][1][2]*wk[20][2])+((ik[7][1][0]*wk[20][0])+(ik[7][1][1]
      *wk[20][1])));
    IkWk[20][2] = ((ik[7][2][2]*wk[20][2])+((ik[7][2][0]*wk[20][0])+(ik[7][2][1]
      *wk[20][1])));
    WkIkWk[20][0] = ((IkWk[20][2]*wk[20][1])-(IkWk[20][1]*wk[20][2]));
    WkIkWk[20][1] = ((IkWk[20][0]*wk[20][2])-(IkWk[20][2]*wk[20][0]));
    WkIkWk[20][2] = ((IkWk[20][1]*wk[20][0])-(IkWk[20][0]*wk[20][1]));
    IkWk[21][0] = ((ik[8][0][2]*wk[21][2])+((ik[8][0][0]*wk[21][0])+(ik[8][0][1]
      *wk[21][1])));
    IkWk[21][1] = ((ik[8][1][2]*wk[21][2])+((ik[8][1][0]*wk[21][0])+(ik[8][1][1]
      *wk[21][1])));
    IkWk[21][2] = ((ik[8][2][2]*wk[21][2])+((ik[8][2][0]*wk[21][0])+(ik[8][2][1]
      *wk[21][1])));
    WkIkWk[21][0] = ((IkWk[21][2]*wk[21][1])-(IkWk[21][1]*wk[21][2]));
    WkIkWk[21][1] = ((IkWk[21][0]*wk[21][2])-(IkWk[21][2]*wk[21][0]));
    WkIkWk[21][2] = ((IkWk[21][1]*wk[21][0])-(IkWk[21][0]*wk[21][1]));
    IkWk[22][0] = ((ik[9][0][2]*wk[22][2])+((ik[9][0][0]*wk[22][0])+(ik[9][0][1]
      *wk[22][1])));
    IkWk[22][1] = ((ik[9][1][2]*wk[22][2])+((ik[9][1][0]*wk[22][0])+(ik[9][1][1]
      *wk[22][1])));
    IkWk[22][2] = ((ik[9][2][2]*wk[22][2])+((ik[9][2][0]*wk[22][0])+(ik[9][2][1]
      *wk[22][1])));
    WkIkWk[22][0] = ((IkWk[22][2]*wk[22][1])-(IkWk[22][1]*wk[22][2]));
    WkIkWk[22][1] = ((IkWk[22][0]*wk[22][2])-(IkWk[22][2]*wk[22][0]));
    WkIkWk[22][2] = ((IkWk[22][1]*wk[22][0])-(IkWk[22][0]*wk[22][1]));
    IkWk[23][0] = ((ik[10][0][2]*wk[23][2])+((ik[10][0][0]*wk[23][0])+(
      ik[10][0][1]*wk[23][1])));
    IkWk[23][1] = ((ik[10][1][2]*wk[23][2])+((ik[10][1][0]*wk[23][0])+(
      ik[10][1][1]*wk[23][1])));
    IkWk[23][2] = ((ik[10][2][2]*wk[23][2])+((ik[10][2][0]*wk[23][0])+(
      ik[10][2][1]*wk[23][1])));
    WkIkWk[23][0] = ((IkWk[23][2]*wk[23][1])-(IkWk[23][1]*wk[23][2]));
    WkIkWk[23][1] = ((IkWk[23][0]*wk[23][2])-(IkWk[23][2]*wk[23][0]));
    WkIkWk[23][2] = ((IkWk[23][1]*wk[23][0])-(IkWk[23][0]*wk[23][1]));
    IkWk[26][0] = ((ik[11][0][2]*wk[26][2])+((ik[11][0][0]*wk[26][0])+(
      ik[11][0][1]*wk[26][1])));
    IkWk[26][1] = ((ik[11][1][2]*wk[26][2])+((ik[11][1][0]*wk[26][0])+(
      ik[11][1][1]*wk[26][1])));
    IkWk[26][2] = ((ik[11][2][2]*wk[26][2])+((ik[11][2][0]*wk[26][0])+(
      ik[11][2][1]*wk[26][1])));
    WkIkWk[26][0] = ((IkWk[26][2]*wk[26][1])-(IkWk[26][1]*wk[26][2]));
    WkIkWk[26][1] = ((IkWk[26][0]*wk[26][2])-(IkWk[26][2]*wk[26][0]));
    WkIkWk[26][2] = ((IkWk[26][1]*wk[26][0])-(IkWk[26][0]*wk[26][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (wk[5][0]*wk[5][0]);
    w0w0[1] = (wk[8][0]*wk[8][0]);
    w0w0[2] = (wk[11][0]*wk[11][0]);
    w0w0[3] = (wk[12][0]*wk[12][0]);
    w0w0[4] = (wk[13][0]*wk[13][0]);
    w0w0[5] = (wk[14][0]*wk[14][0]);
    w0w0[6] = (wk[17][0]*wk[17][0]);
    w0w0[7] = (wk[20][0]*wk[20][0]);
    w0w0[8] = (wk[21][0]*wk[21][0]);
    w0w0[9] = (wk[22][0]*wk[22][0]);
    w0w0[10] = (wk[23][0]*wk[23][0]);
    w0w0[11] = (wk[26][0]*wk[26][0]);
    w1w1[0] = (wk[5][1]*wk[5][1]);
    w1w1[1] = (wk[8][1]*wk[8][1]);
    w1w1[2] = (wk[11][1]*wk[11][1]);
    w1w1[3] = (wk[12][1]*wk[12][1]);
    w1w1[4] = (wk[13][1]*wk[13][1]);
    w1w1[5] = (wk[14][1]*wk[14][1]);
    w1w1[6] = (wk[17][1]*wk[17][1]);
    w1w1[7] = (wk[20][1]*wk[20][1]);
    w1w1[8] = (wk[21][1]*wk[21][1]);
    w1w1[9] = (wk[22][1]*wk[22][1]);
    w1w1[10] = (wk[23][1]*wk[23][1]);
    w1w1[11] = (wk[26][1]*wk[26][1]);
    w2w2[0] = (wk[5][2]*wk[5][2]);
    w2w2[1] = (wk[8][2]*wk[8][2]);
    w2w2[2] = (wk[11][2]*wk[11][2]);
    w2w2[3] = (wk[12][2]*wk[12][2]);
    w2w2[4] = (wk[13][2]*wk[13][2]);
    w2w2[5] = (wk[14][2]*wk[14][2]);
    w2w2[6] = (wk[17][2]*wk[17][2]);
    w2w2[7] = (wk[20][2]*wk[20][2]);
    w2w2[8] = (wk[21][2]*wk[21][2]);
    w2w2[9] = (wk[22][2]*wk[22][2]);
    w2w2[10] = (wk[23][2]*wk[23][2]);
    w2w2[11] = (wk[26][2]*wk[26][2]);
    w0w1[0] = (wk[5][0]*wk[5][1]);
    w0w1[1] = (wk[8][0]*wk[8][1]);
    w0w1[2] = (wk[11][0]*wk[11][1]);
    w0w1[3] = (wk[12][0]*wk[12][1]);
    w0w1[4] = (wk[13][0]*wk[13][1]);
    w0w1[5] = (wk[14][0]*wk[14][1]);
    w0w1[6] = (wk[17][0]*wk[17][1]);
    w0w1[7] = (wk[20][0]*wk[20][1]);
    w0w1[8] = (wk[21][0]*wk[21][1]);
    w0w1[9] = (wk[22][0]*wk[22][1]);
    w0w1[10] = (wk[23][0]*wk[23][1]);
    w0w1[11] = (wk[26][0]*wk[26][1]);
    w0w2[0] = (wk[5][0]*wk[5][2]);
    w0w2[1] = (wk[8][0]*wk[8][2]);
    w0w2[2] = (wk[11][0]*wk[11][2]);
    w0w2[3] = (wk[12][0]*wk[12][2]);
    w0w2[4] = (wk[13][0]*wk[13][2]);
    w0w2[5] = (wk[14][0]*wk[14][2]);
    w0w2[6] = (wk[17][0]*wk[17][2]);
    w0w2[7] = (wk[20][0]*wk[20][2]);
    w0w2[8] = (wk[21][0]*wk[21][2]);
    w0w2[9] = (wk[22][0]*wk[22][2]);
    w0w2[10] = (wk[23][0]*wk[23][2]);
    w0w2[11] = (wk[26][0]*wk[26][2]);
    w1w2[0] = (wk[5][1]*wk[5][2]);
    w1w2[1] = (wk[8][1]*wk[8][2]);
    w1w2[2] = (wk[11][1]*wk[11][2]);
    w1w2[3] = (wk[12][1]*wk[12][2]);
    w1w2[4] = (wk[13][1]*wk[13][2]);
    w1w2[5] = (wk[14][1]*wk[14][2]);
    w1w2[6] = (wk[17][1]*wk[17][2]);
    w1w2[7] = (wk[20][1]*wk[20][2]);
    w1w2[8] = (wk[21][1]*wk[21][2]);
    w1w2[9] = (wk[22][1]*wk[22][2]);
    w1w2[10] = (wk[23][1]*wk[23][2]);
    w1w2[11] = (wk[26][1]*wk[26][2]);
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
    w00w11[10] = -(w0w0[10]+w1w1[10]);
    w00w11[11] = -(w0w0[11]+w1w1[11]);
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
    w00w22[10] = -(w0w0[10]+w2w2[10]);
    w00w22[11] = -(w0w0[11]+w2w2[11]);
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
    w11w22[10] = -(w1w1[10]+w2w2[10]);
    w11w22[11] = -(w1w1[11]+w2w2[11]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[1][0] = (Vik[0][0]+Vik[1][0]);
    vnk[1][1] = (Vik[0][1]+Vik[1][1]);
    vnk[1][2] = (Vik[0][2]+Vik[1][2]);
    vnk[2][0] = (Vik[2][0]+vnk[1][0]);
    vnk[2][1] = (Vik[2][1]+vnk[1][1]);
    vnk[2][2] = (Vik[2][2]+vnk[1][2]);
    vnk[5][0] = (vnk[2][0]+((cnk[5][0][2]*Wkrpk[5][2])+((cnk[5][0][0]*
      Wkrpk[5][0])+(cnk[5][0][1]*Wkrpk[5][1]))));
    vnk[5][1] = (vnk[2][1]+((cnk[5][1][2]*Wkrpk[5][2])+((cnk[5][1][0]*
      Wkrpk[5][0])+(cnk[5][1][1]*Wkrpk[5][1]))));
    vnk[5][2] = (vnk[2][2]+((cnk[5][2][2]*Wkrpk[5][2])+((cnk[5][2][0]*
      Wkrpk[5][0])+(cnk[5][2][1]*Wkrpk[5][1]))));
    vnk[6][0] = (vnk[5][0]+((cnk[5][0][2]*Wirk[6][2])+((cnk[5][0][0]*Wirk[6][0])
      +(cnk[5][0][1]*Wirk[6][1]))));
    vnk[6][1] = (vnk[5][1]+((cnk[5][1][2]*Wirk[6][2])+((cnk[5][1][0]*Wirk[6][0])
      +(cnk[5][1][1]*Wirk[6][1]))));
    vnk[6][2] = (vnk[5][2]+((cnk[5][2][2]*Wirk[6][2])+((cnk[5][2][0]*Wirk[6][0])
      +(cnk[5][2][1]*Wirk[6][1]))));
    vnk[8][0] = (vnk[6][0]+((cnk[8][0][2]*Wkrpk[8][2])+((cnk[8][0][0]*
      Wkrpk[8][0])+(cnk[8][0][1]*Wkrpk[8][1]))));
    vnk[8][1] = (vnk[6][1]+((cnk[8][1][2]*Wkrpk[8][2])+((cnk[8][1][0]*
      Wkrpk[8][0])+(cnk[8][1][1]*Wkrpk[8][1]))));
    vnk[8][2] = (vnk[6][2]+((cnk[8][2][2]*Wkrpk[8][2])+((cnk[8][2][0]*
      Wkrpk[8][0])+(cnk[8][2][1]*Wkrpk[8][1]))));
    vnk[9][0] = ((vnk[8][0]+((cnk[8][0][2]*Wirk[9][2])+((cnk[8][0][0]*Wirk[9][0]
      )+(cnk[8][0][1]*Wirk[9][1]))))+((cnk[8][0][2]*VikWkr[9][2])+((cnk[8][0][0]
      *VikWkr[9][0])+(cnk[8][0][1]*VikWkr[9][1]))));
    vnk[9][1] = ((vnk[8][1]+((cnk[8][1][2]*Wirk[9][2])+((cnk[8][1][0]*Wirk[9][0]
      )+(cnk[8][1][1]*Wirk[9][1]))))+((cnk[8][1][2]*VikWkr[9][2])+((cnk[8][1][0]
      *VikWkr[9][0])+(cnk[8][1][1]*VikWkr[9][1]))));
    vnk[9][2] = ((vnk[8][2]+((cnk[8][2][2]*Wirk[9][2])+((cnk[8][2][0]*Wirk[9][0]
      )+(cnk[8][2][1]*Wirk[9][1]))))+((cnk[8][2][2]*VikWkr[9][2])+((cnk[8][2][0]
      *VikWkr[9][0])+(cnk[8][2][1]*VikWkr[9][1]))));
    vnk[10][0] = (vnk[9][0]+((cnk[8][0][2]*VikWkr[10][2])+((cnk[8][0][0]*
      VikWkr[10][0])+(cnk[8][0][1]*VikWkr[10][1]))));
    vnk[10][1] = (vnk[9][1]+((cnk[8][1][2]*VikWkr[10][2])+((cnk[8][1][0]*
      VikWkr[10][0])+(cnk[8][1][1]*VikWkr[10][1]))));
    vnk[10][2] = (vnk[9][2]+((cnk[8][2][2]*VikWkr[10][2])+((cnk[8][2][0]*
      VikWkr[10][0])+(cnk[8][2][1]*VikWkr[10][1]))));
    vnk[11][0] = (vnk[10][0]+((cnk[11][0][2]*Wkrpk[11][2])+((cnk[11][0][0]*
      Wkrpk[11][0])+(cnk[11][0][1]*Wkrpk[11][1]))));
    vnk[11][1] = (vnk[10][1]+((cnk[11][1][2]*Wkrpk[11][2])+((cnk[11][1][0]*
      Wkrpk[11][0])+(cnk[11][1][1]*Wkrpk[11][1]))));
    vnk[11][2] = (vnk[10][2]+((cnk[11][2][2]*Wkrpk[11][2])+((cnk[11][2][0]*
      Wkrpk[11][0])+(cnk[11][2][1]*Wkrpk[11][1]))));
    vnk[12][0] = ((vnk[11][0]+((cnk[11][0][2]*Wirk[12][2])+((cnk[11][0][0]*
      Wirk[12][0])+(cnk[11][0][1]*Wirk[12][1]))))+((cnk[12][0][2]*Wkrpk[12][2])+
      ((cnk[12][0][0]*Wkrpk[12][0])+(cnk[12][0][1]*Wkrpk[12][1]))));
    vnk[12][1] = ((vnk[11][1]+((cnk[11][1][2]*Wirk[12][2])+((cnk[11][1][0]*
      Wirk[12][0])+(cnk[11][1][1]*Wirk[12][1]))))+((cnk[12][1][2]*Wkrpk[12][2])+
      ((cnk[12][1][0]*Wkrpk[12][0])+(cnk[12][1][1]*Wkrpk[12][1]))));
    vnk[12][2] = ((vnk[11][2]+((cnk[11][2][2]*Wirk[12][2])+((cnk[11][2][0]*
      Wirk[12][0])+(cnk[11][2][1]*Wirk[12][1]))))+((cnk[12][2][2]*Wkrpk[12][2])+
      ((cnk[12][2][0]*Wkrpk[12][0])+(cnk[12][2][1]*Wkrpk[12][1]))));
    vnk[13][0] = ((vnk[12][0]+((cnk[12][0][2]*Wirk[13][2])+((cnk[12][0][0]*
      Wirk[13][0])+(cnk[12][0][1]*Wirk[13][1]))))+((cnk[13][0][2]*Wkrpk[13][2])+
      ((cnk[13][0][0]*Wkrpk[13][0])+(cnk[13][0][1]*Wkrpk[13][1]))));
    vnk[13][1] = ((vnk[12][1]+((cnk[12][1][2]*Wirk[13][2])+((cnk[12][1][0]*
      Wirk[13][0])+(cnk[12][1][1]*Wirk[13][1]))))+((cnk[13][1][2]*Wkrpk[13][2])+
      ((cnk[13][1][0]*Wkrpk[13][0])+(cnk[13][1][1]*Wkrpk[13][1]))));
    vnk[13][2] = ((vnk[12][2]+((cnk[12][2][2]*Wirk[13][2])+((cnk[12][2][0]*
      Wirk[13][0])+(cnk[12][2][1]*Wirk[13][1]))))+((cnk[13][2][2]*Wkrpk[13][2])+
      ((cnk[13][2][0]*Wkrpk[13][0])+(cnk[13][2][1]*Wkrpk[13][1]))));
    vnk[14][0] = ((vnk[13][0]+((cnk[13][0][2]*Wirk[14][2])+((cnk[13][0][0]*
      Wirk[14][0])+(cnk[13][0][1]*Wirk[14][1]))))+((cnk[14][0][2]*Wkrpk[14][2])+
      ((cnk[14][0][0]*Wkrpk[14][0])+(cnk[14][0][1]*Wkrpk[14][1]))));
    vnk[14][1] = ((vnk[13][1]+((cnk[13][1][2]*Wirk[14][2])+((cnk[13][1][0]*
      Wirk[14][0])+(cnk[13][1][1]*Wirk[14][1]))))+((cnk[14][1][2]*Wkrpk[14][2])+
      ((cnk[14][1][0]*Wkrpk[14][0])+(cnk[14][1][1]*Wkrpk[14][1]))));
    vnk[14][2] = ((vnk[13][2]+((cnk[13][2][2]*Wirk[14][2])+((cnk[13][2][0]*
      Wirk[14][0])+(cnk[13][2][1]*Wirk[14][1]))))+((cnk[14][2][2]*Wkrpk[14][2])+
      ((cnk[14][2][0]*Wkrpk[14][0])+(cnk[14][2][1]*Wkrpk[14][1]))));
    vnk[15][0] = (vnk[5][0]+((cnk[5][0][2]*Wirk[15][2])+((cnk[5][0][0]*
      Wirk[15][0])+(cnk[5][0][1]*Wirk[15][1]))));
    vnk[15][1] = (vnk[5][1]+((cnk[5][1][2]*Wirk[15][2])+((cnk[5][1][0]*
      Wirk[15][0])+(cnk[5][1][1]*Wirk[15][1]))));
    vnk[15][2] = (vnk[5][2]+((cnk[5][2][2]*Wirk[15][2])+((cnk[5][2][0]*
      Wirk[15][0])+(cnk[5][2][1]*Wirk[15][1]))));
    vnk[17][0] = (vnk[15][0]+((cnk[17][0][2]*Wkrpk[17][2])+((cnk[17][0][0]*
      Wkrpk[17][0])+(cnk[17][0][1]*Wkrpk[17][1]))));
    vnk[17][1] = (vnk[15][1]+((cnk[17][1][2]*Wkrpk[17][2])+((cnk[17][1][0]*
      Wkrpk[17][0])+(cnk[17][1][1]*Wkrpk[17][1]))));
    vnk[17][2] = (vnk[15][2]+((cnk[17][2][2]*Wkrpk[17][2])+((cnk[17][2][0]*
      Wkrpk[17][0])+(cnk[17][2][1]*Wkrpk[17][1]))));
    vnk[18][0] = ((vnk[17][0]+((cnk[17][0][2]*Wirk[18][2])+((cnk[17][0][0]*
      Wirk[18][0])+(cnk[17][0][1]*Wirk[18][1]))))+((cnk[17][0][2]*VikWkr[18][2])
      +((cnk[17][0][0]*VikWkr[18][0])+(cnk[17][0][1]*VikWkr[18][1]))));
    vnk[18][1] = ((vnk[17][1]+((cnk[17][1][2]*Wirk[18][2])+((cnk[17][1][0]*
      Wirk[18][0])+(cnk[17][1][1]*Wirk[18][1]))))+((cnk[17][1][2]*VikWkr[18][2])
      +((cnk[17][1][0]*VikWkr[18][0])+(cnk[17][1][1]*VikWkr[18][1]))));
    vnk[18][2] = ((vnk[17][2]+((cnk[17][2][2]*Wirk[18][2])+((cnk[17][2][0]*
      Wirk[18][0])+(cnk[17][2][1]*Wirk[18][1]))))+((cnk[17][2][2]*VikWkr[18][2])
      +((cnk[17][2][0]*VikWkr[18][0])+(cnk[17][2][1]*VikWkr[18][1]))));
    vnk[19][0] = (vnk[18][0]+((cnk[17][0][2]*VikWkr[19][2])+((cnk[17][0][0]*
      VikWkr[19][0])+(cnk[17][0][1]*VikWkr[19][1]))));
    vnk[19][1] = (vnk[18][1]+((cnk[17][1][2]*VikWkr[19][2])+((cnk[17][1][0]*
      VikWkr[19][0])+(cnk[17][1][1]*VikWkr[19][1]))));
    vnk[19][2] = (vnk[18][2]+((cnk[17][2][2]*VikWkr[19][2])+((cnk[17][2][0]*
      VikWkr[19][0])+(cnk[17][2][1]*VikWkr[19][1]))));
    vnk[20][0] = (vnk[19][0]+((cnk[20][0][2]*Wkrpk[20][2])+((cnk[20][0][0]*
      Wkrpk[20][0])+(cnk[20][0][1]*Wkrpk[20][1]))));
    vnk[20][1] = (vnk[19][1]+((cnk[20][1][2]*Wkrpk[20][2])+((cnk[20][1][0]*
      Wkrpk[20][0])+(cnk[20][1][1]*Wkrpk[20][1]))));
    vnk[20][2] = (vnk[19][2]+((cnk[20][2][2]*Wkrpk[20][2])+((cnk[20][2][0]*
      Wkrpk[20][0])+(cnk[20][2][1]*Wkrpk[20][1]))));
    vnk[21][0] = ((vnk[20][0]+((cnk[20][0][2]*Wirk[21][2])+((cnk[20][0][0]*
      Wirk[21][0])+(cnk[20][0][1]*Wirk[21][1]))))+((cnk[21][0][2]*Wkrpk[21][2])+
      ((cnk[21][0][0]*Wkrpk[21][0])+(cnk[21][0][1]*Wkrpk[21][1]))));
    vnk[21][1] = ((vnk[20][1]+((cnk[20][1][2]*Wirk[21][2])+((cnk[20][1][0]*
      Wirk[21][0])+(cnk[20][1][1]*Wirk[21][1]))))+((cnk[21][1][2]*Wkrpk[21][2])+
      ((cnk[21][1][0]*Wkrpk[21][0])+(cnk[21][1][1]*Wkrpk[21][1]))));
    vnk[21][2] = ((vnk[20][2]+((cnk[20][2][2]*Wirk[21][2])+((cnk[20][2][0]*
      Wirk[21][0])+(cnk[20][2][1]*Wirk[21][1]))))+((cnk[21][2][2]*Wkrpk[21][2])+
      ((cnk[21][2][0]*Wkrpk[21][0])+(cnk[21][2][1]*Wkrpk[21][1]))));
    vnk[22][0] = ((vnk[21][0]+((cnk[21][0][2]*Wirk[22][2])+((cnk[21][0][0]*
      Wirk[22][0])+(cnk[21][0][1]*Wirk[22][1]))))+((cnk[22][0][2]*Wkrpk[22][2])+
      ((cnk[22][0][0]*Wkrpk[22][0])+(cnk[22][0][1]*Wkrpk[22][1]))));
    vnk[22][1] = ((vnk[21][1]+((cnk[21][1][2]*Wirk[22][2])+((cnk[21][1][0]*
      Wirk[22][0])+(cnk[21][1][1]*Wirk[22][1]))))+((cnk[22][1][2]*Wkrpk[22][2])+
      ((cnk[22][1][0]*Wkrpk[22][0])+(cnk[22][1][1]*Wkrpk[22][1]))));
    vnk[22][2] = ((vnk[21][2]+((cnk[21][2][2]*Wirk[22][2])+((cnk[21][2][0]*
      Wirk[22][0])+(cnk[21][2][1]*Wirk[22][1]))))+((cnk[22][2][2]*Wkrpk[22][2])+
      ((cnk[22][2][0]*Wkrpk[22][0])+(cnk[22][2][1]*Wkrpk[22][1]))));
    vnk[23][0] = ((vnk[22][0]+((cnk[22][0][2]*Wirk[23][2])+((cnk[22][0][0]*
      Wirk[23][0])+(cnk[22][0][1]*Wirk[23][1]))))+((cnk[23][0][2]*Wkrpk[23][2])+
      ((cnk[23][0][0]*Wkrpk[23][0])+(cnk[23][0][1]*Wkrpk[23][1]))));
    vnk[23][1] = ((vnk[22][1]+((cnk[22][1][2]*Wirk[23][2])+((cnk[22][1][0]*
      Wirk[23][0])+(cnk[22][1][1]*Wirk[23][1]))))+((cnk[23][1][2]*Wkrpk[23][2])+
      ((cnk[23][1][0]*Wkrpk[23][0])+(cnk[23][1][1]*Wkrpk[23][1]))));
    vnk[23][2] = ((vnk[22][2]+((cnk[22][2][2]*Wirk[23][2])+((cnk[22][2][0]*
      Wirk[23][0])+(cnk[22][2][1]*Wirk[23][1]))))+((cnk[23][2][2]*Wkrpk[23][2])+
      ((cnk[23][2][0]*Wkrpk[23][0])+(cnk[23][2][1]*Wkrpk[23][1]))));
    vnk[24][0] = (vnk[5][0]+((cnk[5][0][2]*Wirk[24][2])+((cnk[5][0][0]*
      Wirk[24][0])+(cnk[5][0][1]*Wirk[24][1]))));
    vnk[24][1] = (vnk[5][1]+((cnk[5][1][2]*Wirk[24][2])+((cnk[5][1][0]*
      Wirk[24][0])+(cnk[5][1][1]*Wirk[24][1]))));
    vnk[24][2] = (vnk[5][2]+((cnk[5][2][2]*Wirk[24][2])+((cnk[5][2][0]*
      Wirk[24][0])+(cnk[5][2][1]*Wirk[24][1]))));
    vnk[26][0] = (vnk[24][0]+((cnk[26][0][2]*Wkrpk[26][2])+((cnk[26][0][0]*
      Wkrpk[26][0])+(cnk[26][0][1]*Wkrpk[26][1]))));
    vnk[26][1] = (vnk[24][1]+((cnk[26][1][2]*Wkrpk[26][2])+((cnk[26][1][0]*
      Wkrpk[26][0])+(cnk[26][1][1]*Wkrpk[26][1]))));
    vnk[26][2] = (vnk[24][2]+((cnk[26][2][2]*Wkrpk[26][2])+((cnk[26][2][0]*
      Wkrpk[26][0])+(cnk[26][2][1]*Wkrpk[26][1]))));
    vnb[0][0] = vnk[5][0];
    vnb[0][1] = vnk[5][1];
    vnb[0][2] = vnk[5][2];
    vnb[1][0] = vnk[8][0];
    vnb[1][1] = vnk[8][1];
    vnb[1][2] = vnk[8][2];
    vnb[2][0] = vnk[11][0];
    vnb[2][1] = vnk[11][1];
    vnb[2][2] = vnk[11][2];
    vnb[3][0] = vnk[12][0];
    vnb[3][1] = vnk[12][1];
    vnb[3][2] = vnk[12][2];
    vnb[4][0] = vnk[13][0];
    vnb[4][1] = vnk[13][1];
    vnb[4][2] = vnk[13][2];
    vnb[5][0] = vnk[14][0];
    vnb[5][1] = vnk[14][1];
    vnb[5][2] = vnk[14][2];
    vnb[6][0] = vnk[17][0];
    vnb[6][1] = vnk[17][1];
    vnb[6][2] = vnk[17][2];
    vnb[7][0] = vnk[20][0];
    vnb[7][1] = vnk[20][1];
    vnb[7][2] = vnk[20][2];
    vnb[8][0] = vnk[21][0];
    vnb[8][1] = vnk[21][1];
    vnb[8][2] = vnk[21][2];
    vnb[9][0] = vnk[22][0];
    vnb[9][1] = vnk[22][1];
    vnb[9][2] = vnk[22][2];
    vnb[10][0] = vnk[23][0];
    vnb[10][1] = vnk[23][1];
    vnb[10][2] = vnk[23][2];
    vnb[11][0] = vnk[26][0];
    vnb[11][1] = vnk[26][1];
    vnb[11][2] = vnk[26][2];
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
/*
Compute constraint velocity errors
*/
    skipus: ;
    sduverr(curtim,q,u,&verr[23]);
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 27; i++) {
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
/*
 Used 0.58 seconds CPU time,
 98304 additional bytes of memory.
 Equations contain 2238 adds/subtracts/negates
                   3162 multiplies
                      3 divides
                   1521 assignments
*/
}

sdqdot(oqdot)
    double oqdot[27];
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 26; i++) {
        oqdot[i] = qdot[i];
    }
}

sdu2qdot(uin,oqdot)
    double uin[27],oqdot[27];
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 26; i++) {
        oqdot[i] = uin[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
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
        Wpk[3][3][0] = pin[0][0];
        Wpk[3][3][1] = pin[0][1];
        Wpk[3][3][2] = pin[0][2];
        Wpk[3][4][0] = ((Cik[4][2][0]*pin[0][2])+((Cik[4][0][0]*pin[0][0])+(
          Cik[4][1][0]*pin[0][1])));
        Wpk[3][4][1] = ((Cik[4][2][1]*pin[0][2])+((Cik[4][0][1]*pin[0][0])+(
          Cik[4][1][1]*pin[0][1])));
        Wpk[3][4][2] = ((Cik[4][2][2]*pin[0][2])+((Cik[4][0][2]*pin[0][0])+(
          Cik[4][1][2]*pin[0][1])));
        Wpk[3][5][0] = ((Cik[5][2][0]*Wpk[3][4][2])+((Cik[5][0][0]*Wpk[3][4][0])
          +(Cik[5][1][0]*Wpk[3][4][1])));
        Wpk[3][5][1] = ((Cik[5][2][1]*Wpk[3][4][2])+((Cik[5][0][1]*Wpk[3][4][0])
          +(Cik[5][1][1]*Wpk[3][4][1])));
        Wpk[3][5][2] = ((Cik[5][2][2]*Wpk[3][4][2])+((Cik[5][0][2]*Wpk[3][4][0])
          +(Cik[5][1][2]*Wpk[3][4][1])));
        Wpk[3][6][0] = ((Cik[6][2][0]*Wpk[3][5][2])+((Cik[6][0][0]*Wpk[3][5][0])
          +(Cik[6][1][0]*Wpk[3][5][1])));
        Wpk[3][6][1] = ((Cik[6][2][1]*Wpk[3][5][2])+((Cik[6][0][1]*Wpk[3][5][0])
          +(Cik[6][1][1]*Wpk[3][5][1])));
        Wpk[3][6][2] = ((Cik[6][2][2]*Wpk[3][5][2])+((Cik[6][0][2]*Wpk[3][5][0])
          +(Cik[6][1][2]*Wpk[3][5][1])));
        Wpk[3][7][0] = ((Cik[7][2][0]*Wpk[3][6][2])+((Cik[7][0][0]*Wpk[3][6][0])
          +(Cik[7][1][0]*Wpk[3][6][1])));
        Wpk[3][7][1] = ((Cik[7][2][1]*Wpk[3][6][2])+((Cik[7][0][1]*Wpk[3][6][0])
          +(Cik[7][1][1]*Wpk[3][6][1])));
        Wpk[3][7][2] = ((Cik[7][2][2]*Wpk[3][6][2])+((Cik[7][0][2]*Wpk[3][6][0])
          +(Cik[7][1][2]*Wpk[3][6][1])));
        Wpk[3][8][0] = ((Cik[8][2][0]*Wpk[3][7][2])+((Cik[8][0][0]*Wpk[3][7][0])
          +(Cik[8][1][0]*Wpk[3][7][1])));
        Wpk[3][8][1] = ((Cik[8][2][1]*Wpk[3][7][2])+((Cik[8][0][1]*Wpk[3][7][0])
          +(Cik[8][1][1]*Wpk[3][7][1])));
        Wpk[3][8][2] = ((Cik[8][2][2]*Wpk[3][7][2])+((Cik[8][0][2]*Wpk[3][7][0])
          +(Cik[8][1][2]*Wpk[3][7][1])));
        Wpk[3][9][0] = Wpk[3][8][0];
        Wpk[3][9][1] = Wpk[3][8][1];
        Wpk[3][9][2] = Wpk[3][8][2];
        Wpk[3][10][0] = Wpk[3][8][0];
        Wpk[3][10][1] = Wpk[3][8][1];
        Wpk[3][10][2] = Wpk[3][8][2];
        Wpk[3][11][0] = ((Cik[11][2][0]*Wpk[3][8][2])+((Cik[11][0][0]*
          Wpk[3][8][0])+(Cik[11][1][0]*Wpk[3][8][1])));
        Wpk[3][11][1] = ((Cik[11][2][1]*Wpk[3][8][2])+((Cik[11][0][1]*
          Wpk[3][8][0])+(Cik[11][1][1]*Wpk[3][8][1])));
        Wpk[3][11][2] = ((Cik[11][2][2]*Wpk[3][8][2])+((Cik[11][0][2]*
          Wpk[3][8][0])+(Cik[11][1][2]*Wpk[3][8][1])));
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
        Wpk[3][15][0] = ((Cik[15][2][0]*Wpk[3][5][2])+((Cik[15][0][0]*
          Wpk[3][5][0])+(Cik[15][1][0]*Wpk[3][5][1])));
        Wpk[3][15][1] = ((Cik[15][2][1]*Wpk[3][5][2])+((Cik[15][0][1]*
          Wpk[3][5][0])+(Cik[15][1][1]*Wpk[3][5][1])));
        Wpk[3][15][2] = ((Cik[15][2][2]*Wpk[3][5][2])+((Cik[15][0][2]*
          Wpk[3][5][0])+(Cik[15][1][2]*Wpk[3][5][1])));
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
        Wpk[3][18][0] = Wpk[3][17][0];
        Wpk[3][18][1] = Wpk[3][17][1];
        Wpk[3][18][2] = Wpk[3][17][2];
        Wpk[3][19][0] = Wpk[3][17][0];
        Wpk[3][19][1] = Wpk[3][17][1];
        Wpk[3][19][2] = Wpk[3][17][2];
        Wpk[3][20][0] = ((Cik[20][2][0]*Wpk[3][17][2])+((Cik[20][0][0]*
          Wpk[3][17][0])+(Cik[20][1][0]*Wpk[3][17][1])));
        Wpk[3][20][1] = ((Cik[20][2][1]*Wpk[3][17][2])+((Cik[20][0][1]*
          Wpk[3][17][0])+(Cik[20][1][1]*Wpk[3][17][1])));
        Wpk[3][20][2] = ((Cik[20][2][2]*Wpk[3][17][2])+((Cik[20][0][2]*
          Wpk[3][17][0])+(Cik[20][1][2]*Wpk[3][17][1])));
        Wpk[3][21][0] = ((Cik[21][2][0]*Wpk[3][20][2])+((Cik[21][0][0]*
          Wpk[3][20][0])+(Cik[21][1][0]*Wpk[3][20][1])));
        Wpk[3][21][1] = ((Cik[21][2][1]*Wpk[3][20][2])+((Cik[21][0][1]*
          Wpk[3][20][0])+(Cik[21][1][1]*Wpk[3][20][1])));
        Wpk[3][21][2] = ((Cik[21][2][2]*Wpk[3][20][2])+((Cik[21][0][2]*
          Wpk[3][20][0])+(Cik[21][1][2]*Wpk[3][20][1])));
        Wpk[3][22][0] = ((Cik[22][2][0]*Wpk[3][21][2])+((Cik[22][0][0]*
          Wpk[3][21][0])+(Cik[22][1][0]*Wpk[3][21][1])));
        Wpk[3][22][1] = ((Cik[22][2][1]*Wpk[3][21][2])+((Cik[22][0][1]*
          Wpk[3][21][0])+(Cik[22][1][1]*Wpk[3][21][1])));
        Wpk[3][22][2] = ((Cik[22][2][2]*Wpk[3][21][2])+((Cik[22][0][2]*
          Wpk[3][21][0])+(Cik[22][1][2]*Wpk[3][21][1])));
        Wpk[3][23][0] = ((Cik[23][2][0]*Wpk[3][22][2])+((Cik[23][0][0]*
          Wpk[3][22][0])+(Cik[23][1][0]*Wpk[3][22][1])));
        Wpk[3][23][1] = ((Cik[23][2][1]*Wpk[3][22][2])+((Cik[23][0][1]*
          Wpk[3][22][0])+(Cik[23][1][1]*Wpk[3][22][1])));
        Wpk[3][23][2] = ((Cik[23][2][2]*Wpk[3][22][2])+((Cik[23][0][2]*
          Wpk[3][22][0])+(Cik[23][1][2]*Wpk[3][22][1])));
        Wpk[3][24][0] = ((Cik[24][2][0]*Wpk[3][5][2])+((Cik[24][0][0]*
          Wpk[3][5][0])+(Cik[24][1][0]*Wpk[3][5][1])));
        Wpk[3][24][1] = ((Cik[24][2][1]*Wpk[3][5][2])+((Cik[24][0][1]*
          Wpk[3][5][0])+(Cik[24][1][1]*Wpk[3][5][1])));
        Wpk[3][24][2] = ((Cik[24][2][2]*Wpk[3][5][2])+((Cik[24][0][2]*
          Wpk[3][5][0])+(Cik[24][1][2]*Wpk[3][5][1])));
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
        Wpk[4][4][0] = pin[1][0];
        Wpk[4][4][1] = pin[1][1];
        Wpk[4][4][2] = pin[1][2];
        Wpk[4][5][0] = ((Cik[5][2][0]*pin[1][2])+((Cik[5][0][0]*pin[1][0])+(
          Cik[5][1][0]*pin[1][1])));
        Wpk[4][5][1] = ((Cik[5][2][1]*pin[1][2])+((Cik[5][0][1]*pin[1][0])+(
          Cik[5][1][1]*pin[1][1])));
        Wpk[4][5][2] = ((Cik[5][2][2]*pin[1][2])+((Cik[5][0][2]*pin[1][0])+(
          Cik[5][1][2]*pin[1][1])));
        Wpk[4][6][0] = ((Cik[6][2][0]*Wpk[4][5][2])+((Cik[6][0][0]*Wpk[4][5][0])
          +(Cik[6][1][0]*Wpk[4][5][1])));
        Wpk[4][6][1] = ((Cik[6][2][1]*Wpk[4][5][2])+((Cik[6][0][1]*Wpk[4][5][0])
          +(Cik[6][1][1]*Wpk[4][5][1])));
        Wpk[4][6][2] = ((Cik[6][2][2]*Wpk[4][5][2])+((Cik[6][0][2]*Wpk[4][5][0])
          +(Cik[6][1][2]*Wpk[4][5][1])));
        Wpk[4][7][0] = ((Cik[7][2][0]*Wpk[4][6][2])+((Cik[7][0][0]*Wpk[4][6][0])
          +(Cik[7][1][0]*Wpk[4][6][1])));
        Wpk[4][7][1] = ((Cik[7][2][1]*Wpk[4][6][2])+((Cik[7][0][1]*Wpk[4][6][0])
          +(Cik[7][1][1]*Wpk[4][6][1])));
        Wpk[4][7][2] = ((Cik[7][2][2]*Wpk[4][6][2])+((Cik[7][0][2]*Wpk[4][6][0])
          +(Cik[7][1][2]*Wpk[4][6][1])));
        Wpk[4][8][0] = ((Cik[8][2][0]*Wpk[4][7][2])+((Cik[8][0][0]*Wpk[4][7][0])
          +(Cik[8][1][0]*Wpk[4][7][1])));
        Wpk[4][8][1] = ((Cik[8][2][1]*Wpk[4][7][2])+((Cik[8][0][1]*Wpk[4][7][0])
          +(Cik[8][1][1]*Wpk[4][7][1])));
        Wpk[4][8][2] = ((Cik[8][2][2]*Wpk[4][7][2])+((Cik[8][0][2]*Wpk[4][7][0])
          +(Cik[8][1][2]*Wpk[4][7][1])));
        Wpk[4][9][0] = Wpk[4][8][0];
        Wpk[4][9][1] = Wpk[4][8][1];
        Wpk[4][9][2] = Wpk[4][8][2];
        Wpk[4][10][0] = Wpk[4][8][0];
        Wpk[4][10][1] = Wpk[4][8][1];
        Wpk[4][10][2] = Wpk[4][8][2];
        Wpk[4][11][0] = ((Cik[11][2][0]*Wpk[4][8][2])+((Cik[11][0][0]*
          Wpk[4][8][0])+(Cik[11][1][0]*Wpk[4][8][1])));
        Wpk[4][11][1] = ((Cik[11][2][1]*Wpk[4][8][2])+((Cik[11][0][1]*
          Wpk[4][8][0])+(Cik[11][1][1]*Wpk[4][8][1])));
        Wpk[4][11][2] = ((Cik[11][2][2]*Wpk[4][8][2])+((Cik[11][0][2]*
          Wpk[4][8][0])+(Cik[11][1][2]*Wpk[4][8][1])));
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
        Wpk[4][15][0] = ((Cik[15][2][0]*Wpk[4][5][2])+((Cik[15][0][0]*
          Wpk[4][5][0])+(Cik[15][1][0]*Wpk[4][5][1])));
        Wpk[4][15][1] = ((Cik[15][2][1]*Wpk[4][5][2])+((Cik[15][0][1]*
          Wpk[4][5][0])+(Cik[15][1][1]*Wpk[4][5][1])));
        Wpk[4][15][2] = ((Cik[15][2][2]*Wpk[4][5][2])+((Cik[15][0][2]*
          Wpk[4][5][0])+(Cik[15][1][2]*Wpk[4][5][1])));
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
        Wpk[4][18][0] = Wpk[4][17][0];
        Wpk[4][18][1] = Wpk[4][17][1];
        Wpk[4][18][2] = Wpk[4][17][2];
        Wpk[4][19][0] = Wpk[4][17][0];
        Wpk[4][19][1] = Wpk[4][17][1];
        Wpk[4][19][2] = Wpk[4][17][2];
        Wpk[4][20][0] = ((Cik[20][2][0]*Wpk[4][17][2])+((Cik[20][0][0]*
          Wpk[4][17][0])+(Cik[20][1][0]*Wpk[4][17][1])));
        Wpk[4][20][1] = ((Cik[20][2][1]*Wpk[4][17][2])+((Cik[20][0][1]*
          Wpk[4][17][0])+(Cik[20][1][1]*Wpk[4][17][1])));
        Wpk[4][20][2] = ((Cik[20][2][2]*Wpk[4][17][2])+((Cik[20][0][2]*
          Wpk[4][17][0])+(Cik[20][1][2]*Wpk[4][17][1])));
        Wpk[4][21][0] = ((Cik[21][2][0]*Wpk[4][20][2])+((Cik[21][0][0]*
          Wpk[4][20][0])+(Cik[21][1][0]*Wpk[4][20][1])));
        Wpk[4][21][1] = ((Cik[21][2][1]*Wpk[4][20][2])+((Cik[21][0][1]*
          Wpk[4][20][0])+(Cik[21][1][1]*Wpk[4][20][1])));
        Wpk[4][21][2] = ((Cik[21][2][2]*Wpk[4][20][2])+((Cik[21][0][2]*
          Wpk[4][20][0])+(Cik[21][1][2]*Wpk[4][20][1])));
        Wpk[4][22][0] = ((Cik[22][2][0]*Wpk[4][21][2])+((Cik[22][0][0]*
          Wpk[4][21][0])+(Cik[22][1][0]*Wpk[4][21][1])));
        Wpk[4][22][1] = ((Cik[22][2][1]*Wpk[4][21][2])+((Cik[22][0][1]*
          Wpk[4][21][0])+(Cik[22][1][1]*Wpk[4][21][1])));
        Wpk[4][22][2] = ((Cik[22][2][2]*Wpk[4][21][2])+((Cik[22][0][2]*
          Wpk[4][21][0])+(Cik[22][1][2]*Wpk[4][21][1])));
        Wpk[4][23][0] = ((Cik[23][2][0]*Wpk[4][22][2])+((Cik[23][0][0]*
          Wpk[4][22][0])+(Cik[23][1][0]*Wpk[4][22][1])));
        Wpk[4][23][1] = ((Cik[23][2][1]*Wpk[4][22][2])+((Cik[23][0][1]*
          Wpk[4][22][0])+(Cik[23][1][1]*Wpk[4][22][1])));
        Wpk[4][23][2] = ((Cik[23][2][2]*Wpk[4][22][2])+((Cik[23][0][2]*
          Wpk[4][22][0])+(Cik[23][1][2]*Wpk[4][22][1])));
        Wpk[4][24][0] = ((Cik[24][2][0]*Wpk[4][5][2])+((Cik[24][0][0]*
          Wpk[4][5][0])+(Cik[24][1][0]*Wpk[4][5][1])));
        Wpk[4][24][1] = ((Cik[24][2][1]*Wpk[4][5][2])+((Cik[24][0][1]*
          Wpk[4][5][0])+(Cik[24][1][1]*Wpk[4][5][1])));
        Wpk[4][24][2] = ((Cik[24][2][2]*Wpk[4][5][2])+((Cik[24][0][2]*
          Wpk[4][5][0])+(Cik[24][1][2]*Wpk[4][5][1])));
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
        Wpk[5][5][0] = pin[2][0];
        Wpk[5][5][1] = pin[2][1];
        Wpk[5][5][2] = pin[2][2];
        Wpk[5][6][0] = ((Cik[6][2][0]*pin[2][2])+((Cik[6][0][0]*pin[2][0])+(
          Cik[6][1][0]*pin[2][1])));
        Wpk[5][6][1] = ((Cik[6][2][1]*pin[2][2])+((Cik[6][0][1]*pin[2][0])+(
          Cik[6][1][1]*pin[2][1])));
        Wpk[5][6][2] = ((Cik[6][2][2]*pin[2][2])+((Cik[6][0][2]*pin[2][0])+(
          Cik[6][1][2]*pin[2][1])));
        Wpk[5][7][0] = ((Cik[7][2][0]*Wpk[5][6][2])+((Cik[7][0][0]*Wpk[5][6][0])
          +(Cik[7][1][0]*Wpk[5][6][1])));
        Wpk[5][7][1] = ((Cik[7][2][1]*Wpk[5][6][2])+((Cik[7][0][1]*Wpk[5][6][0])
          +(Cik[7][1][1]*Wpk[5][6][1])));
        Wpk[5][7][2] = ((Cik[7][2][2]*Wpk[5][6][2])+((Cik[7][0][2]*Wpk[5][6][0])
          +(Cik[7][1][2]*Wpk[5][6][1])));
        Wpk[5][8][0] = ((Cik[8][2][0]*Wpk[5][7][2])+((Cik[8][0][0]*Wpk[5][7][0])
          +(Cik[8][1][0]*Wpk[5][7][1])));
        Wpk[5][8][1] = ((Cik[8][2][1]*Wpk[5][7][2])+((Cik[8][0][1]*Wpk[5][7][0])
          +(Cik[8][1][1]*Wpk[5][7][1])));
        Wpk[5][8][2] = ((Cik[8][2][2]*Wpk[5][7][2])+((Cik[8][0][2]*Wpk[5][7][0])
          +(Cik[8][1][2]*Wpk[5][7][1])));
        Wpk[5][9][0] = Wpk[5][8][0];
        Wpk[5][9][1] = Wpk[5][8][1];
        Wpk[5][9][2] = Wpk[5][8][2];
        Wpk[5][10][0] = Wpk[5][8][0];
        Wpk[5][10][1] = Wpk[5][8][1];
        Wpk[5][10][2] = Wpk[5][8][2];
        Wpk[5][11][0] = ((Cik[11][2][0]*Wpk[5][8][2])+((Cik[11][0][0]*
          Wpk[5][8][0])+(Cik[11][1][0]*Wpk[5][8][1])));
        Wpk[5][11][1] = ((Cik[11][2][1]*Wpk[5][8][2])+((Cik[11][0][1]*
          Wpk[5][8][0])+(Cik[11][1][1]*Wpk[5][8][1])));
        Wpk[5][11][2] = ((Cik[11][2][2]*Wpk[5][8][2])+((Cik[11][0][2]*
          Wpk[5][8][0])+(Cik[11][1][2]*Wpk[5][8][1])));
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
        Wpk[5][15][0] = ((Cik[15][2][0]*pin[2][2])+((Cik[15][0][0]*pin[2][0])+(
          Cik[15][1][0]*pin[2][1])));
        Wpk[5][15][1] = ((Cik[15][2][1]*pin[2][2])+((Cik[15][0][1]*pin[2][0])+(
          Cik[15][1][1]*pin[2][1])));
        Wpk[5][15][2] = ((Cik[15][2][2]*pin[2][2])+((Cik[15][0][2]*pin[2][0])+(
          Cik[15][1][2]*pin[2][1])));
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
        Wpk[5][18][0] = Wpk[5][17][0];
        Wpk[5][18][1] = Wpk[5][17][1];
        Wpk[5][18][2] = Wpk[5][17][2];
        Wpk[5][19][0] = Wpk[5][17][0];
        Wpk[5][19][1] = Wpk[5][17][1];
        Wpk[5][19][2] = Wpk[5][17][2];
        Wpk[5][20][0] = ((Cik[20][2][0]*Wpk[5][17][2])+((Cik[20][0][0]*
          Wpk[5][17][0])+(Cik[20][1][0]*Wpk[5][17][1])));
        Wpk[5][20][1] = ((Cik[20][2][1]*Wpk[5][17][2])+((Cik[20][0][1]*
          Wpk[5][17][0])+(Cik[20][1][1]*Wpk[5][17][1])));
        Wpk[5][20][2] = ((Cik[20][2][2]*Wpk[5][17][2])+((Cik[20][0][2]*
          Wpk[5][17][0])+(Cik[20][1][2]*Wpk[5][17][1])));
        Wpk[5][21][0] = ((Cik[21][2][0]*Wpk[5][20][2])+((Cik[21][0][0]*
          Wpk[5][20][0])+(Cik[21][1][0]*Wpk[5][20][1])));
        Wpk[5][21][1] = ((Cik[21][2][1]*Wpk[5][20][2])+((Cik[21][0][1]*
          Wpk[5][20][0])+(Cik[21][1][1]*Wpk[5][20][1])));
        Wpk[5][21][2] = ((Cik[21][2][2]*Wpk[5][20][2])+((Cik[21][0][2]*
          Wpk[5][20][0])+(Cik[21][1][2]*Wpk[5][20][1])));
        Wpk[5][22][0] = ((Cik[22][2][0]*Wpk[5][21][2])+((Cik[22][0][0]*
          Wpk[5][21][0])+(Cik[22][1][0]*Wpk[5][21][1])));
        Wpk[5][22][1] = ((Cik[22][2][1]*Wpk[5][21][2])+((Cik[22][0][1]*
          Wpk[5][21][0])+(Cik[22][1][1]*Wpk[5][21][1])));
        Wpk[5][22][2] = ((Cik[22][2][2]*Wpk[5][21][2])+((Cik[22][0][2]*
          Wpk[5][21][0])+(Cik[22][1][2]*Wpk[5][21][1])));
        Wpk[5][23][0] = ((Cik[23][2][0]*Wpk[5][22][2])+((Cik[23][0][0]*
          Wpk[5][22][0])+(Cik[23][1][0]*Wpk[5][22][1])));
        Wpk[5][23][1] = ((Cik[23][2][1]*Wpk[5][22][2])+((Cik[23][0][1]*
          Wpk[5][22][0])+(Cik[23][1][1]*Wpk[5][22][1])));
        Wpk[5][23][2] = ((Cik[23][2][2]*Wpk[5][22][2])+((Cik[23][0][2]*
          Wpk[5][22][0])+(Cik[23][1][2]*Wpk[5][22][1])));
        Wpk[5][24][0] = ((Cik[24][2][0]*pin[2][2])+((Cik[24][0][0]*pin[2][0])+(
          Cik[24][1][0]*pin[2][1])));
        Wpk[5][24][1] = ((Cik[24][2][1]*pin[2][2])+((Cik[24][0][1]*pin[2][0])+(
          Cik[24][1][1]*pin[2][1])));
        Wpk[5][24][2] = ((Cik[24][2][2]*pin[2][2])+((Cik[24][0][2]*pin[2][0])+(
          Cik[24][1][2]*pin[2][1])));
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
        Wpk[6][9][0] = Wpk[6][8][0];
        Wpk[6][9][1] = Wpk[6][8][1];
        Wpk[6][9][2] = Wpk[6][8][2];
        Wpk[6][10][0] = Wpk[6][8][0];
        Wpk[6][10][1] = Wpk[6][8][1];
        Wpk[6][10][2] = Wpk[6][8][2];
        Wpk[6][11][0] = ((Cik[11][2][0]*Wpk[6][8][2])+((Cik[11][0][0]*
          Wpk[6][8][0])+(Cik[11][1][0]*Wpk[6][8][1])));
        Wpk[6][11][1] = ((Cik[11][2][1]*Wpk[6][8][2])+((Cik[11][0][1]*
          Wpk[6][8][0])+(Cik[11][1][1]*Wpk[6][8][1])));
        Wpk[6][11][2] = ((Cik[11][2][2]*Wpk[6][8][2])+((Cik[11][0][2]*
          Wpk[6][8][0])+(Cik[11][1][2]*Wpk[6][8][1])));
        Wpk[6][12][0] = ((Cik[12][2][0]*Wpk[6][11][2])+((Cik[12][0][0]*
          Wpk[6][11][0])+(Cik[12][1][0]*Wpk[6][11][1])));
        Wpk[6][12][1] = ((Cik[12][2][1]*Wpk[6][11][2])+((Cik[12][0][1]*
          Wpk[6][11][0])+(Cik[12][1][1]*Wpk[6][11][1])));
        Wpk[6][12][2] = ((Cik[12][2][2]*Wpk[6][11][2])+((Cik[12][0][2]*
          Wpk[6][11][0])+(Cik[12][1][2]*Wpk[6][11][1])));
        Wpk[6][13][0] = ((Cik[13][2][0]*Wpk[6][12][2])+((Cik[13][0][0]*
          Wpk[6][12][0])+(Cik[13][1][0]*Wpk[6][12][1])));
        Wpk[6][13][1] = ((Cik[13][2][1]*Wpk[6][12][2])+((Cik[13][0][1]*
          Wpk[6][12][0])+(Cik[13][1][1]*Wpk[6][12][1])));
        Wpk[6][13][2] = ((Cik[13][2][2]*Wpk[6][12][2])+((Cik[13][0][2]*
          Wpk[6][12][0])+(Cik[13][1][2]*Wpk[6][12][1])));
        Wpk[6][14][0] = ((Cik[14][2][0]*Wpk[6][13][2])+((Cik[14][0][0]*
          Wpk[6][13][0])+(Cik[14][1][0]*Wpk[6][13][1])));
        Wpk[6][14][1] = ((Cik[14][2][1]*Wpk[6][13][2])+((Cik[14][0][1]*
          Wpk[6][13][0])+(Cik[14][1][1]*Wpk[6][13][1])));
        Wpk[6][14][2] = ((Cik[14][2][2]*Wpk[6][13][2])+((Cik[14][0][2]*
          Wpk[6][13][0])+(Cik[14][1][2]*Wpk[6][13][1])));
        Wpk[7][7][0] = pin[7][0];
        Wpk[7][7][1] = pin[7][1];
        Wpk[7][7][2] = pin[7][2];
        Wpk[7][8][0] = ((Cik[8][2][0]*pin[7][2])+((Cik[8][0][0]*pin[7][0])+(
          Cik[8][1][0]*pin[7][1])));
        Wpk[7][8][1] = ((Cik[8][2][1]*pin[7][2])+((Cik[8][0][1]*pin[7][0])+(
          Cik[8][1][1]*pin[7][1])));
        Wpk[7][8][2] = ((Cik[8][2][2]*pin[7][2])+((Cik[8][0][2]*pin[7][0])+(
          Cik[8][1][2]*pin[7][1])));
        Wpk[7][9][0] = Wpk[7][8][0];
        Wpk[7][9][1] = Wpk[7][8][1];
        Wpk[7][9][2] = Wpk[7][8][2];
        Wpk[7][10][0] = Wpk[7][8][0];
        Wpk[7][10][1] = Wpk[7][8][1];
        Wpk[7][10][2] = Wpk[7][8][2];
        Wpk[7][11][0] = ((Cik[11][2][0]*Wpk[7][8][2])+((Cik[11][0][0]*
          Wpk[7][8][0])+(Cik[11][1][0]*Wpk[7][8][1])));
        Wpk[7][11][1] = ((Cik[11][2][1]*Wpk[7][8][2])+((Cik[11][0][1]*
          Wpk[7][8][0])+(Cik[11][1][1]*Wpk[7][8][1])));
        Wpk[7][11][2] = ((Cik[11][2][2]*Wpk[7][8][2])+((Cik[11][0][2]*
          Wpk[7][8][0])+(Cik[11][1][2]*Wpk[7][8][1])));
        Wpk[7][12][0] = ((Cik[12][2][0]*Wpk[7][11][2])+((Cik[12][0][0]*
          Wpk[7][11][0])+(Cik[12][1][0]*Wpk[7][11][1])));
        Wpk[7][12][1] = ((Cik[12][2][1]*Wpk[7][11][2])+((Cik[12][0][1]*
          Wpk[7][11][0])+(Cik[12][1][1]*Wpk[7][11][1])));
        Wpk[7][12][2] = ((Cik[12][2][2]*Wpk[7][11][2])+((Cik[12][0][2]*
          Wpk[7][11][0])+(Cik[12][1][2]*Wpk[7][11][1])));
        Wpk[7][13][0] = ((Cik[13][2][0]*Wpk[7][12][2])+((Cik[13][0][0]*
          Wpk[7][12][0])+(Cik[13][1][0]*Wpk[7][12][1])));
        Wpk[7][13][1] = ((Cik[13][2][1]*Wpk[7][12][2])+((Cik[13][0][1]*
          Wpk[7][12][0])+(Cik[13][1][1]*Wpk[7][12][1])));
        Wpk[7][13][2] = ((Cik[13][2][2]*Wpk[7][12][2])+((Cik[13][0][2]*
          Wpk[7][12][0])+(Cik[13][1][2]*Wpk[7][12][1])));
        Wpk[7][14][0] = ((Cik[14][2][0]*Wpk[7][13][2])+((Cik[14][0][0]*
          Wpk[7][13][0])+(Cik[14][1][0]*Wpk[7][13][1])));
        Wpk[7][14][1] = ((Cik[14][2][1]*Wpk[7][13][2])+((Cik[14][0][1]*
          Wpk[7][13][0])+(Cik[14][1][1]*Wpk[7][13][1])));
        Wpk[7][14][2] = ((Cik[14][2][2]*Wpk[7][13][2])+((Cik[14][0][2]*
          Wpk[7][13][0])+(Cik[14][1][2]*Wpk[7][13][1])));
        Wpk[8][8][0] = pin[8][0];
        Wpk[8][8][1] = pin[8][1];
        Wpk[8][8][2] = pin[8][2];
        Wpk[8][9][0] = pin[8][0];
        Wpk[8][9][1] = pin[8][1];
        Wpk[8][9][2] = pin[8][2];
        Wpk[8][10][0] = pin[8][0];
        Wpk[8][10][1] = pin[8][1];
        Wpk[8][10][2] = pin[8][2];
        Wpk[8][11][0] = ((Cik[11][2][0]*pin[8][2])+((Cik[11][0][0]*pin[8][0])+(
          Cik[11][1][0]*pin[8][1])));
        Wpk[8][11][1] = ((Cik[11][2][1]*pin[8][2])+((Cik[11][0][1]*pin[8][0])+(
          Cik[11][1][1]*pin[8][1])));
        Wpk[8][11][2] = ((Cik[11][2][2]*pin[8][2])+((Cik[11][0][2]*pin[8][0])+(
          Cik[11][1][2]*pin[8][1])));
        Wpk[8][12][0] = ((Cik[12][2][0]*Wpk[8][11][2])+((Cik[12][0][0]*
          Wpk[8][11][0])+(Cik[12][1][0]*Wpk[8][11][1])));
        Wpk[8][12][1] = ((Cik[12][2][1]*Wpk[8][11][2])+((Cik[12][0][1]*
          Wpk[8][11][0])+(Cik[12][1][1]*Wpk[8][11][1])));
        Wpk[8][12][2] = ((Cik[12][2][2]*Wpk[8][11][2])+((Cik[12][0][2]*
          Wpk[8][11][0])+(Cik[12][1][2]*Wpk[8][11][1])));
        Wpk[8][13][0] = ((Cik[13][2][0]*Wpk[8][12][2])+((Cik[13][0][0]*
          Wpk[8][12][0])+(Cik[13][1][0]*Wpk[8][12][1])));
        Wpk[8][13][1] = ((Cik[13][2][1]*Wpk[8][12][2])+((Cik[13][0][1]*
          Wpk[8][12][0])+(Cik[13][1][1]*Wpk[8][12][1])));
        Wpk[8][13][2] = ((Cik[13][2][2]*Wpk[8][12][2])+((Cik[13][0][2]*
          Wpk[8][12][0])+(Cik[13][1][2]*Wpk[8][12][1])));
        Wpk[8][14][0] = ((Cik[14][2][0]*Wpk[8][13][2])+((Cik[14][0][0]*
          Wpk[8][13][0])+(Cik[14][1][0]*Wpk[8][13][1])));
        Wpk[8][14][1] = ((Cik[14][2][1]*Wpk[8][13][2])+((Cik[14][0][1]*
          Wpk[8][13][0])+(Cik[14][1][1]*Wpk[8][13][1])));
        Wpk[8][14][2] = ((Cik[14][2][2]*Wpk[8][13][2])+((Cik[14][0][2]*
          Wpk[8][13][0])+(Cik[14][1][2]*Wpk[8][13][1])));
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
        Wpk[13][13][0] = pin[13][0];
        Wpk[13][13][1] = pin[13][1];
        Wpk[13][13][2] = pin[13][2];
        Wpk[13][14][0] = ((Cik[14][2][0]*pin[13][2])+((Cik[14][0][0]*pin[13][0])
          +(Cik[14][1][0]*pin[13][1])));
        Wpk[13][14][1] = ((Cik[14][2][1]*pin[13][2])+((Cik[14][0][1]*pin[13][0])
          +(Cik[14][1][1]*pin[13][1])));
        Wpk[13][14][2] = ((Cik[14][2][2]*pin[13][2])+((Cik[14][0][2]*pin[13][0])
          +(Cik[14][1][2]*pin[13][1])));
        Wpk[14][14][0] = pin[14][0];
        Wpk[14][14][1] = pin[14][1];
        Wpk[14][14][2] = pin[14][2];
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
        Wpk[15][18][0] = Wpk[15][17][0];
        Wpk[15][18][1] = Wpk[15][17][1];
        Wpk[15][18][2] = Wpk[15][17][2];
        Wpk[15][19][0] = Wpk[15][17][0];
        Wpk[15][19][1] = Wpk[15][17][1];
        Wpk[15][19][2] = Wpk[15][17][2];
        Wpk[15][20][0] = ((Cik[20][2][0]*Wpk[15][17][2])+((Cik[20][0][0]*
          Wpk[15][17][0])+(Cik[20][1][0]*Wpk[15][17][1])));
        Wpk[15][20][1] = ((Cik[20][2][1]*Wpk[15][17][2])+((Cik[20][0][1]*
          Wpk[15][17][0])+(Cik[20][1][1]*Wpk[15][17][1])));
        Wpk[15][20][2] = ((Cik[20][2][2]*Wpk[15][17][2])+((Cik[20][0][2]*
          Wpk[15][17][0])+(Cik[20][1][2]*Wpk[15][17][1])));
        Wpk[15][21][0] = ((Cik[21][2][0]*Wpk[15][20][2])+((Cik[21][0][0]*
          Wpk[15][20][0])+(Cik[21][1][0]*Wpk[15][20][1])));
        Wpk[15][21][1] = ((Cik[21][2][1]*Wpk[15][20][2])+((Cik[21][0][1]*
          Wpk[15][20][0])+(Cik[21][1][1]*Wpk[15][20][1])));
        Wpk[15][21][2] = ((Cik[21][2][2]*Wpk[15][20][2])+((Cik[21][0][2]*
          Wpk[15][20][0])+(Cik[21][1][2]*Wpk[15][20][1])));
        Wpk[15][22][0] = ((Cik[22][2][0]*Wpk[15][21][2])+((Cik[22][0][0]*
          Wpk[15][21][0])+(Cik[22][1][0]*Wpk[15][21][1])));
        Wpk[15][22][1] = ((Cik[22][2][1]*Wpk[15][21][2])+((Cik[22][0][1]*
          Wpk[15][21][0])+(Cik[22][1][1]*Wpk[15][21][1])));
        Wpk[15][22][2] = ((Cik[22][2][2]*Wpk[15][21][2])+((Cik[22][0][2]*
          Wpk[15][21][0])+(Cik[22][1][2]*Wpk[15][21][1])));
        Wpk[15][23][0] = ((Cik[23][2][0]*Wpk[15][22][2])+((Cik[23][0][0]*
          Wpk[15][22][0])+(Cik[23][1][0]*Wpk[15][22][1])));
        Wpk[15][23][1] = ((Cik[23][2][1]*Wpk[15][22][2])+((Cik[23][0][1]*
          Wpk[15][22][0])+(Cik[23][1][1]*Wpk[15][22][1])));
        Wpk[15][23][2] = ((Cik[23][2][2]*Wpk[15][22][2])+((Cik[23][0][2]*
          Wpk[15][22][0])+(Cik[23][1][2]*Wpk[15][22][1])));
        Wpk[16][16][0] = pin[16][0];
        Wpk[16][16][1] = pin[16][1];
        Wpk[16][16][2] = pin[16][2];
        Wpk[16][17][0] = ((Cik[17][2][0]*pin[16][2])+((Cik[17][0][0]*pin[16][0])
          +(Cik[17][1][0]*pin[16][1])));
        Wpk[16][17][1] = ((Cik[17][2][1]*pin[16][2])+((Cik[17][0][1]*pin[16][0])
          +(Cik[17][1][1]*pin[16][1])));
        Wpk[16][17][2] = ((Cik[17][2][2]*pin[16][2])+((Cik[17][0][2]*pin[16][0])
          +(Cik[17][1][2]*pin[16][1])));
        Wpk[16][18][0] = Wpk[16][17][0];
        Wpk[16][18][1] = Wpk[16][17][1];
        Wpk[16][18][2] = Wpk[16][17][2];
        Wpk[16][19][0] = Wpk[16][17][0];
        Wpk[16][19][1] = Wpk[16][17][1];
        Wpk[16][19][2] = Wpk[16][17][2];
        Wpk[16][20][0] = ((Cik[20][2][0]*Wpk[16][17][2])+((Cik[20][0][0]*
          Wpk[16][17][0])+(Cik[20][1][0]*Wpk[16][17][1])));
        Wpk[16][20][1] = ((Cik[20][2][1]*Wpk[16][17][2])+((Cik[20][0][1]*
          Wpk[16][17][0])+(Cik[20][1][1]*Wpk[16][17][1])));
        Wpk[16][20][2] = ((Cik[20][2][2]*Wpk[16][17][2])+((Cik[20][0][2]*
          Wpk[16][17][0])+(Cik[20][1][2]*Wpk[16][17][1])));
        Wpk[16][21][0] = ((Cik[21][2][0]*Wpk[16][20][2])+((Cik[21][0][0]*
          Wpk[16][20][0])+(Cik[21][1][0]*Wpk[16][20][1])));
        Wpk[16][21][1] = ((Cik[21][2][1]*Wpk[16][20][2])+((Cik[21][0][1]*
          Wpk[16][20][0])+(Cik[21][1][1]*Wpk[16][20][1])));
        Wpk[16][21][2] = ((Cik[21][2][2]*Wpk[16][20][2])+((Cik[21][0][2]*
          Wpk[16][20][0])+(Cik[21][1][2]*Wpk[16][20][1])));
        Wpk[16][22][0] = ((Cik[22][2][0]*Wpk[16][21][2])+((Cik[22][0][0]*
          Wpk[16][21][0])+(Cik[22][1][0]*Wpk[16][21][1])));
        Wpk[16][22][1] = ((Cik[22][2][1]*Wpk[16][21][2])+((Cik[22][0][1]*
          Wpk[16][21][0])+(Cik[22][1][1]*Wpk[16][21][1])));
        Wpk[16][22][2] = ((Cik[22][2][2]*Wpk[16][21][2])+((Cik[22][0][2]*
          Wpk[16][21][0])+(Cik[22][1][2]*Wpk[16][21][1])));
        Wpk[16][23][0] = ((Cik[23][2][0]*Wpk[16][22][2])+((Cik[23][0][0]*
          Wpk[16][22][0])+(Cik[23][1][0]*Wpk[16][22][1])));
        Wpk[16][23][1] = ((Cik[23][2][1]*Wpk[16][22][2])+((Cik[23][0][1]*
          Wpk[16][22][0])+(Cik[23][1][1]*Wpk[16][22][1])));
        Wpk[16][23][2] = ((Cik[23][2][2]*Wpk[16][22][2])+((Cik[23][0][2]*
          Wpk[16][22][0])+(Cik[23][1][2]*Wpk[16][22][1])));
        Wpk[17][17][0] = pin[17][0];
        Wpk[17][17][1] = pin[17][1];
        Wpk[17][17][2] = pin[17][2];
        Wpk[17][18][0] = pin[17][0];
        Wpk[17][18][1] = pin[17][1];
        Wpk[17][18][2] = pin[17][2];
        Wpk[17][19][0] = pin[17][0];
        Wpk[17][19][1] = pin[17][1];
        Wpk[17][19][2] = pin[17][2];
        Wpk[17][20][0] = ((Cik[20][2][0]*pin[17][2])+((Cik[20][0][0]*pin[17][0])
          +(Cik[20][1][0]*pin[17][1])));
        Wpk[17][20][1] = ((Cik[20][2][1]*pin[17][2])+((Cik[20][0][1]*pin[17][0])
          +(Cik[20][1][1]*pin[17][1])));
        Wpk[17][20][2] = ((Cik[20][2][2]*pin[17][2])+((Cik[20][0][2]*pin[17][0])
          +(Cik[20][1][2]*pin[17][1])));
        Wpk[17][21][0] = ((Cik[21][2][0]*Wpk[17][20][2])+((Cik[21][0][0]*
          Wpk[17][20][0])+(Cik[21][1][0]*Wpk[17][20][1])));
        Wpk[17][21][1] = ((Cik[21][2][1]*Wpk[17][20][2])+((Cik[21][0][1]*
          Wpk[17][20][0])+(Cik[21][1][1]*Wpk[17][20][1])));
        Wpk[17][21][2] = ((Cik[21][2][2]*Wpk[17][20][2])+((Cik[21][0][2]*
          Wpk[17][20][0])+(Cik[21][1][2]*Wpk[17][20][1])));
        Wpk[17][22][0] = ((Cik[22][2][0]*Wpk[17][21][2])+((Cik[22][0][0]*
          Wpk[17][21][0])+(Cik[22][1][0]*Wpk[17][21][1])));
        Wpk[17][22][1] = ((Cik[22][2][1]*Wpk[17][21][2])+((Cik[22][0][1]*
          Wpk[17][21][0])+(Cik[22][1][1]*Wpk[17][21][1])));
        Wpk[17][22][2] = ((Cik[22][2][2]*Wpk[17][21][2])+((Cik[22][0][2]*
          Wpk[17][21][0])+(Cik[22][1][2]*Wpk[17][21][1])));
        Wpk[17][23][0] = ((Cik[23][2][0]*Wpk[17][22][2])+((Cik[23][0][0]*
          Wpk[17][22][0])+(Cik[23][1][0]*Wpk[17][22][1])));
        Wpk[17][23][1] = ((Cik[23][2][1]*Wpk[17][22][2])+((Cik[23][0][1]*
          Wpk[17][22][0])+(Cik[23][1][1]*Wpk[17][22][1])));
        Wpk[17][23][2] = ((Cik[23][2][2]*Wpk[17][22][2])+((Cik[23][0][2]*
          Wpk[17][22][0])+(Cik[23][1][2]*Wpk[17][22][1])));
        Wpk[20][20][0] = pin[20][0];
        Wpk[20][20][1] = pin[20][1];
        Wpk[20][20][2] = pin[20][2];
        Wpk[20][21][0] = ((Cik[21][2][0]*pin[20][2])+((Cik[21][0][0]*pin[20][0])
          +(Cik[21][1][0]*pin[20][1])));
        Wpk[20][21][1] = ((Cik[21][2][1]*pin[20][2])+((Cik[21][0][1]*pin[20][0])
          +(Cik[21][1][1]*pin[20][1])));
        Wpk[20][21][2] = ((Cik[21][2][2]*pin[20][2])+((Cik[21][0][2]*pin[20][0])
          +(Cik[21][1][2]*pin[20][1])));
        Wpk[20][22][0] = ((Cik[22][2][0]*Wpk[20][21][2])+((Cik[22][0][0]*
          Wpk[20][21][0])+(Cik[22][1][0]*Wpk[20][21][1])));
        Wpk[20][22][1] = ((Cik[22][2][1]*Wpk[20][21][2])+((Cik[22][0][1]*
          Wpk[20][21][0])+(Cik[22][1][1]*Wpk[20][21][1])));
        Wpk[20][22][2] = ((Cik[22][2][2]*Wpk[20][21][2])+((Cik[22][0][2]*
          Wpk[20][21][0])+(Cik[22][1][2]*Wpk[20][21][1])));
        Wpk[20][23][0] = ((Cik[23][2][0]*Wpk[20][22][2])+((Cik[23][0][0]*
          Wpk[20][22][0])+(Cik[23][1][0]*Wpk[20][22][1])));
        Wpk[20][23][1] = ((Cik[23][2][1]*Wpk[20][22][2])+((Cik[23][0][1]*
          Wpk[20][22][0])+(Cik[23][1][1]*Wpk[20][22][1])));
        Wpk[20][23][2] = ((Cik[23][2][2]*Wpk[20][22][2])+((Cik[23][0][2]*
          Wpk[20][22][0])+(Cik[23][1][2]*Wpk[20][22][1])));
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
        Wpk[22][22][0] = pin[22][0];
        Wpk[22][22][1] = pin[22][1];
        Wpk[22][22][2] = pin[22][2];
        Wpk[22][23][0] = ((Cik[23][2][0]*pin[22][2])+((Cik[23][0][0]*pin[22][0])
          +(Cik[23][1][0]*pin[22][1])));
        Wpk[22][23][1] = ((Cik[23][2][1]*pin[22][2])+((Cik[23][0][1]*pin[22][0])
          +(Cik[23][1][1]*pin[22][1])));
        Wpk[22][23][2] = ((Cik[23][2][2]*pin[22][2])+((Cik[23][0][2]*pin[22][0])
          +(Cik[23][1][2]*pin[22][1])));
        Wpk[23][23][0] = pin[23][0];
        Wpk[23][23][1] = pin[23][1];
        Wpk[23][23][2] = pin[23][2];
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
        Wpk[25][25][0] = pin[25][0];
        Wpk[25][25][1] = pin[25][1];
        Wpk[25][25][2] = pin[25][2];
        Wpk[25][26][0] = ((Cik[26][2][0]*pin[25][2])+((Cik[26][0][0]*pin[25][0])
          +(Cik[26][1][0]*pin[25][1])));
        Wpk[25][26][1] = ((Cik[26][2][1]*pin[25][2])+((Cik[26][0][1]*pin[25][0])
          +(Cik[26][1][1]*pin[25][1])));
        Wpk[25][26][2] = ((Cik[26][2][2]*pin[25][2])+((Cik[26][0][2]*pin[25][0])
          +(Cik[26][1][2]*pin[25][1])));
        Wpk[26][26][0] = pin[26][0];
        Wpk[26][26][1] = pin[26][1];
        Wpk[26][26][2] = pin[26][2];
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
        Vpk[0][4][0] = ((Cik[4][2][0]*Vpk[0][3][2])+((Cik[4][0][0]*Vpk[0][3][0])
          +(Cik[4][1][0]*Vpk[0][3][1])));
        Vpk[0][4][1] = ((Cik[4][2][1]*Vpk[0][3][2])+((Cik[4][0][1]*Vpk[0][3][0])
          +(Cik[4][1][1]*Vpk[0][3][1])));
        Vpk[0][4][2] = ((Cik[4][2][2]*Vpk[0][3][2])+((Cik[4][0][2]*Vpk[0][3][0])
          +(Cik[4][1][2]*Vpk[0][3][1])));
        Vpk[0][5][0] = ((Cik[5][2][0]*Vpk[0][4][2])+((Cik[5][0][0]*Vpk[0][4][0])
          +(Cik[5][1][0]*Vpk[0][4][1])));
        Vpk[0][5][1] = ((Cik[5][2][1]*Vpk[0][4][2])+((Cik[5][0][1]*Vpk[0][4][0])
          +(Cik[5][1][1]*Vpk[0][4][1])));
        Vpk[0][5][2] = ((Cik[5][2][2]*Vpk[0][4][2])+((Cik[5][0][2]*Vpk[0][4][0])
          +(Cik[5][1][2]*Vpk[0][4][1])));
        Vpk[0][6][0] = ((Cik[6][2][0]*Vpk[0][5][2])+((Cik[6][0][0]*Vpk[0][5][0])
          +(Cik[6][1][0]*Vpk[0][5][1])));
        Vpk[0][6][1] = ((Cik[6][2][1]*Vpk[0][5][2])+((Cik[6][0][1]*Vpk[0][5][0])
          +(Cik[6][1][1]*Vpk[0][5][1])));
        Vpk[0][6][2] = ((Cik[6][2][2]*Vpk[0][5][2])+((Cik[6][0][2]*Vpk[0][5][0])
          +(Cik[6][1][2]*Vpk[0][5][1])));
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
        Vpk[0][9][0] = Vpk[0][8][0];
        Vpk[0][9][1] = Vpk[0][8][1];
        Vpk[0][9][2] = Vpk[0][8][2];
        Vpk[0][10][0] = Vpk[0][8][0];
        Vpk[0][10][1] = Vpk[0][8][1];
        Vpk[0][10][2] = Vpk[0][8][2];
        Vpk[0][11][0] = ((Cik[11][2][0]*Vpk[0][8][2])+((Cik[11][0][0]*
          Vpk[0][8][0])+(Cik[11][1][0]*Vpk[0][8][1])));
        Vpk[0][11][1] = ((Cik[11][2][1]*Vpk[0][8][2])+((Cik[11][0][1]*
          Vpk[0][8][0])+(Cik[11][1][1]*Vpk[0][8][1])));
        Vpk[0][11][2] = ((Cik[11][2][2]*Vpk[0][8][2])+((Cik[11][0][2]*
          Vpk[0][8][0])+(Cik[11][1][2]*Vpk[0][8][1])));
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
        Vpk[0][15][0] = ((Cik[15][2][0]*Vpk[0][5][2])+((Cik[15][0][0]*
          Vpk[0][5][0])+(Cik[15][1][0]*Vpk[0][5][1])));
        Vpk[0][15][1] = ((Cik[15][2][1]*Vpk[0][5][2])+((Cik[15][0][1]*
          Vpk[0][5][0])+(Cik[15][1][1]*Vpk[0][5][1])));
        Vpk[0][15][2] = ((Cik[15][2][2]*Vpk[0][5][2])+((Cik[15][0][2]*
          Vpk[0][5][0])+(Cik[15][1][2]*Vpk[0][5][1])));
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
        Vpk[0][18][0] = Vpk[0][17][0];
        Vpk[0][18][1] = Vpk[0][17][1];
        Vpk[0][18][2] = Vpk[0][17][2];
        Vpk[0][19][0] = Vpk[0][17][0];
        Vpk[0][19][1] = Vpk[0][17][1];
        Vpk[0][19][2] = Vpk[0][17][2];
        Vpk[0][20][0] = ((Cik[20][2][0]*Vpk[0][17][2])+((Cik[20][0][0]*
          Vpk[0][17][0])+(Cik[20][1][0]*Vpk[0][17][1])));
        Vpk[0][20][1] = ((Cik[20][2][1]*Vpk[0][17][2])+((Cik[20][0][1]*
          Vpk[0][17][0])+(Cik[20][1][1]*Vpk[0][17][1])));
        Vpk[0][20][2] = ((Cik[20][2][2]*Vpk[0][17][2])+((Cik[20][0][2]*
          Vpk[0][17][0])+(Cik[20][1][2]*Vpk[0][17][1])));
        Vpk[0][21][0] = ((Cik[21][2][0]*Vpk[0][20][2])+((Cik[21][0][0]*
          Vpk[0][20][0])+(Cik[21][1][0]*Vpk[0][20][1])));
        Vpk[0][21][1] = ((Cik[21][2][1]*Vpk[0][20][2])+((Cik[21][0][1]*
          Vpk[0][20][0])+(Cik[21][1][1]*Vpk[0][20][1])));
        Vpk[0][21][2] = ((Cik[21][2][2]*Vpk[0][20][2])+((Cik[21][0][2]*
          Vpk[0][20][0])+(Cik[21][1][2]*Vpk[0][20][1])));
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
        Vpk[0][24][0] = ((Cik[24][2][0]*Vpk[0][5][2])+((Cik[24][0][0]*
          Vpk[0][5][0])+(Cik[24][1][0]*Vpk[0][5][1])));
        Vpk[0][24][1] = ((Cik[24][2][1]*Vpk[0][5][2])+((Cik[24][0][1]*
          Vpk[0][5][0])+(Cik[24][1][1]*Vpk[0][5][1])));
        Vpk[0][24][2] = ((Cik[24][2][2]*Vpk[0][5][2])+((Cik[24][0][2]*
          Vpk[0][5][0])+(Cik[24][1][2]*Vpk[0][5][1])));
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
        Vpk[1][4][0] = ((Cik[4][2][0]*Vpk[1][3][2])+((Cik[4][0][0]*Vpk[1][3][0])
          +(Cik[4][1][0]*Vpk[1][3][1])));
        Vpk[1][4][1] = ((Cik[4][2][1]*Vpk[1][3][2])+((Cik[4][0][1]*Vpk[1][3][0])
          +(Cik[4][1][1]*Vpk[1][3][1])));
        Vpk[1][4][2] = ((Cik[4][2][2]*Vpk[1][3][2])+((Cik[4][0][2]*Vpk[1][3][0])
          +(Cik[4][1][2]*Vpk[1][3][1])));
        Vpk[1][5][0] = ((Cik[5][2][0]*Vpk[1][4][2])+((Cik[5][0][0]*Vpk[1][4][0])
          +(Cik[5][1][0]*Vpk[1][4][1])));
        Vpk[1][5][1] = ((Cik[5][2][1]*Vpk[1][4][2])+((Cik[5][0][1]*Vpk[1][4][0])
          +(Cik[5][1][1]*Vpk[1][4][1])));
        Vpk[1][5][2] = ((Cik[5][2][2]*Vpk[1][4][2])+((Cik[5][0][2]*Vpk[1][4][0])
          +(Cik[5][1][2]*Vpk[1][4][1])));
        Vpk[1][6][0] = ((Cik[6][2][0]*Vpk[1][5][2])+((Cik[6][0][0]*Vpk[1][5][0])
          +(Cik[6][1][0]*Vpk[1][5][1])));
        Vpk[1][6][1] = ((Cik[6][2][1]*Vpk[1][5][2])+((Cik[6][0][1]*Vpk[1][5][0])
          +(Cik[6][1][1]*Vpk[1][5][1])));
        Vpk[1][6][2] = ((Cik[6][2][2]*Vpk[1][5][2])+((Cik[6][0][2]*Vpk[1][5][0])
          +(Cik[6][1][2]*Vpk[1][5][1])));
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
        Vpk[1][9][0] = Vpk[1][8][0];
        Vpk[1][9][1] = Vpk[1][8][1];
        Vpk[1][9][2] = Vpk[1][8][2];
        Vpk[1][10][0] = Vpk[1][8][0];
        Vpk[1][10][1] = Vpk[1][8][1];
        Vpk[1][10][2] = Vpk[1][8][2];
        Vpk[1][11][0] = ((Cik[11][2][0]*Vpk[1][8][2])+((Cik[11][0][0]*
          Vpk[1][8][0])+(Cik[11][1][0]*Vpk[1][8][1])));
        Vpk[1][11][1] = ((Cik[11][2][1]*Vpk[1][8][2])+((Cik[11][0][1]*
          Vpk[1][8][0])+(Cik[11][1][1]*Vpk[1][8][1])));
        Vpk[1][11][2] = ((Cik[11][2][2]*Vpk[1][8][2])+((Cik[11][0][2]*
          Vpk[1][8][0])+(Cik[11][1][2]*Vpk[1][8][1])));
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
        Vpk[1][15][0] = ((Cik[15][2][0]*Vpk[1][5][2])+((Cik[15][0][0]*
          Vpk[1][5][0])+(Cik[15][1][0]*Vpk[1][5][1])));
        Vpk[1][15][1] = ((Cik[15][2][1]*Vpk[1][5][2])+((Cik[15][0][1]*
          Vpk[1][5][0])+(Cik[15][1][1]*Vpk[1][5][1])));
        Vpk[1][15][2] = ((Cik[15][2][2]*Vpk[1][5][2])+((Cik[15][0][2]*
          Vpk[1][5][0])+(Cik[15][1][2]*Vpk[1][5][1])));
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
        Vpk[1][18][0] = Vpk[1][17][0];
        Vpk[1][18][1] = Vpk[1][17][1];
        Vpk[1][18][2] = Vpk[1][17][2];
        Vpk[1][19][0] = Vpk[1][17][0];
        Vpk[1][19][1] = Vpk[1][17][1];
        Vpk[1][19][2] = Vpk[1][17][2];
        Vpk[1][20][0] = ((Cik[20][2][0]*Vpk[1][17][2])+((Cik[20][0][0]*
          Vpk[1][17][0])+(Cik[20][1][0]*Vpk[1][17][1])));
        Vpk[1][20][1] = ((Cik[20][2][1]*Vpk[1][17][2])+((Cik[20][0][1]*
          Vpk[1][17][0])+(Cik[20][1][1]*Vpk[1][17][1])));
        Vpk[1][20][2] = ((Cik[20][2][2]*Vpk[1][17][2])+((Cik[20][0][2]*
          Vpk[1][17][0])+(Cik[20][1][2]*Vpk[1][17][1])));
        Vpk[1][21][0] = ((Cik[21][2][0]*Vpk[1][20][2])+((Cik[21][0][0]*
          Vpk[1][20][0])+(Cik[21][1][0]*Vpk[1][20][1])));
        Vpk[1][21][1] = ((Cik[21][2][1]*Vpk[1][20][2])+((Cik[21][0][1]*
          Vpk[1][20][0])+(Cik[21][1][1]*Vpk[1][20][1])));
        Vpk[1][21][2] = ((Cik[21][2][2]*Vpk[1][20][2])+((Cik[21][0][2]*
          Vpk[1][20][0])+(Cik[21][1][2]*Vpk[1][20][1])));
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
        Vpk[1][24][0] = ((Cik[24][2][0]*Vpk[1][5][2])+((Cik[24][0][0]*
          Vpk[1][5][0])+(Cik[24][1][0]*Vpk[1][5][1])));
        Vpk[1][24][1] = ((Cik[24][2][1]*Vpk[1][5][2])+((Cik[24][0][1]*
          Vpk[1][5][0])+(Cik[24][1][1]*Vpk[1][5][1])));
        Vpk[1][24][2] = ((Cik[24][2][2]*Vpk[1][5][2])+((Cik[24][0][2]*
          Vpk[1][5][0])+(Cik[24][1][2]*Vpk[1][5][1])));
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
        Vpk[2][2][0] = pin[2][0];
        Vpk[2][2][1] = pin[2][1];
        Vpk[2][2][2] = pin[2][2];
        Vpk[2][3][0] = ((Cik[3][2][0]*pin[2][2])+((Cik[3][0][0]*pin[2][0])+(
          Cik[3][1][0]*pin[2][1])));
        Vpk[2][3][1] = ((Cik[3][2][1]*pin[2][2])+((Cik[3][0][1]*pin[2][0])+(
          Cik[3][1][1]*pin[2][1])));
        Vpk[2][3][2] = ((Cik[3][2][2]*pin[2][2])+((Cik[3][0][2]*pin[2][0])+(
          Cik[3][1][2]*pin[2][1])));
        Vpk[2][4][0] = ((Cik[4][2][0]*Vpk[2][3][2])+((Cik[4][0][0]*Vpk[2][3][0])
          +(Cik[4][1][0]*Vpk[2][3][1])));
        Vpk[2][4][1] = ((Cik[4][2][1]*Vpk[2][3][2])+((Cik[4][0][1]*Vpk[2][3][0])
          +(Cik[4][1][1]*Vpk[2][3][1])));
        Vpk[2][4][2] = ((Cik[4][2][2]*Vpk[2][3][2])+((Cik[4][0][2]*Vpk[2][3][0])
          +(Cik[4][1][2]*Vpk[2][3][1])));
        Vpk[2][5][0] = ((Cik[5][2][0]*Vpk[2][4][2])+((Cik[5][0][0]*Vpk[2][4][0])
          +(Cik[5][1][0]*Vpk[2][4][1])));
        Vpk[2][5][1] = ((Cik[5][2][1]*Vpk[2][4][2])+((Cik[5][0][1]*Vpk[2][4][0])
          +(Cik[5][1][1]*Vpk[2][4][1])));
        Vpk[2][5][2] = ((Cik[5][2][2]*Vpk[2][4][2])+((Cik[5][0][2]*Vpk[2][4][0])
          +(Cik[5][1][2]*Vpk[2][4][1])));
        Vpk[2][6][0] = ((Cik[6][2][0]*Vpk[2][5][2])+((Cik[6][0][0]*Vpk[2][5][0])
          +(Cik[6][1][0]*Vpk[2][5][1])));
        Vpk[2][6][1] = ((Cik[6][2][1]*Vpk[2][5][2])+((Cik[6][0][1]*Vpk[2][5][0])
          +(Cik[6][1][1]*Vpk[2][5][1])));
        Vpk[2][6][2] = ((Cik[6][2][2]*Vpk[2][5][2])+((Cik[6][0][2]*Vpk[2][5][0])
          +(Cik[6][1][2]*Vpk[2][5][1])));
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
        Vpk[2][9][0] = Vpk[2][8][0];
        Vpk[2][9][1] = Vpk[2][8][1];
        Vpk[2][9][2] = Vpk[2][8][2];
        Vpk[2][10][0] = Vpk[2][8][0];
        Vpk[2][10][1] = Vpk[2][8][1];
        Vpk[2][10][2] = Vpk[2][8][2];
        Vpk[2][11][0] = ((Cik[11][2][0]*Vpk[2][8][2])+((Cik[11][0][0]*
          Vpk[2][8][0])+(Cik[11][1][0]*Vpk[2][8][1])));
        Vpk[2][11][1] = ((Cik[11][2][1]*Vpk[2][8][2])+((Cik[11][0][1]*
          Vpk[2][8][0])+(Cik[11][1][1]*Vpk[2][8][1])));
        Vpk[2][11][2] = ((Cik[11][2][2]*Vpk[2][8][2])+((Cik[11][0][2]*
          Vpk[2][8][0])+(Cik[11][1][2]*Vpk[2][8][1])));
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
        Vpk[2][15][0] = ((Cik[15][2][0]*Vpk[2][5][2])+((Cik[15][0][0]*
          Vpk[2][5][0])+(Cik[15][1][0]*Vpk[2][5][1])));
        Vpk[2][15][1] = ((Cik[15][2][1]*Vpk[2][5][2])+((Cik[15][0][1]*
          Vpk[2][5][0])+(Cik[15][1][1]*Vpk[2][5][1])));
        Vpk[2][15][2] = ((Cik[15][2][2]*Vpk[2][5][2])+((Cik[15][0][2]*
          Vpk[2][5][0])+(Cik[15][1][2]*Vpk[2][5][1])));
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
        Vpk[2][18][0] = Vpk[2][17][0];
        Vpk[2][18][1] = Vpk[2][17][1];
        Vpk[2][18][2] = Vpk[2][17][2];
        Vpk[2][19][0] = Vpk[2][17][0];
        Vpk[2][19][1] = Vpk[2][17][1];
        Vpk[2][19][2] = Vpk[2][17][2];
        Vpk[2][20][0] = ((Cik[20][2][0]*Vpk[2][17][2])+((Cik[20][0][0]*
          Vpk[2][17][0])+(Cik[20][1][0]*Vpk[2][17][1])));
        Vpk[2][20][1] = ((Cik[20][2][1]*Vpk[2][17][2])+((Cik[20][0][1]*
          Vpk[2][17][0])+(Cik[20][1][1]*Vpk[2][17][1])));
        Vpk[2][20][2] = ((Cik[20][2][2]*Vpk[2][17][2])+((Cik[20][0][2]*
          Vpk[2][17][0])+(Cik[20][1][2]*Vpk[2][17][1])));
        Vpk[2][21][0] = ((Cik[21][2][0]*Vpk[2][20][2])+((Cik[21][0][0]*
          Vpk[2][20][0])+(Cik[21][1][0]*Vpk[2][20][1])));
        Vpk[2][21][1] = ((Cik[21][2][1]*Vpk[2][20][2])+((Cik[21][0][1]*
          Vpk[2][20][0])+(Cik[21][1][1]*Vpk[2][20][1])));
        Vpk[2][21][2] = ((Cik[21][2][2]*Vpk[2][20][2])+((Cik[21][0][2]*
          Vpk[2][20][0])+(Cik[21][1][2]*Vpk[2][20][1])));
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
        Vpk[2][24][0] = ((Cik[24][2][0]*Vpk[2][5][2])+((Cik[24][0][0]*
          Vpk[2][5][0])+(Cik[24][1][0]*Vpk[2][5][1])));
        Vpk[2][24][1] = ((Cik[24][2][1]*Vpk[2][5][2])+((Cik[24][0][1]*
          Vpk[2][5][0])+(Cik[24][1][1]*Vpk[2][5][1])));
        Vpk[2][24][2] = ((Cik[24][2][2]*Vpk[2][5][2])+((Cik[24][0][2]*
          Vpk[2][5][0])+(Cik[24][1][2]*Vpk[2][5][1])));
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
        Vpk[3][5][0] = ((rk[0][1]*Wpk[3][5][2])-(rk[0][2]*Wpk[3][5][1]));
        Vpk[3][5][1] = ((rk[0][2]*Wpk[3][5][0])-(rk[0][0]*Wpk[3][5][2]));
        Vpk[3][5][2] = ((rk[0][0]*Wpk[3][5][1])-(rk[0][1]*Wpk[3][5][0]));
        VWri[3][6][0] = (Vpk[3][5][0]+((ri[1][2]*Wpk[3][5][1])-(ri[1][1]*
          Wpk[3][5][2])));
        VWri[3][6][1] = (Vpk[3][5][1]+((ri[1][0]*Wpk[3][5][2])-(ri[1][2]*
          Wpk[3][5][0])));
        VWri[3][6][2] = (Vpk[3][5][2]+((ri[1][1]*Wpk[3][5][0])-(ri[1][0]*
          Wpk[3][5][1])));
        Vpk[3][6][0] = ((Cik[6][2][0]*VWri[3][6][2])+((Cik[6][0][0]*
          VWri[3][6][0])+(Cik[6][1][0]*VWri[3][6][1])));
        Vpk[3][6][1] = ((Cik[6][2][1]*VWri[3][6][2])+((Cik[6][0][1]*
          VWri[3][6][0])+(Cik[6][1][1]*VWri[3][6][1])));
        Vpk[3][6][2] = ((Cik[6][2][2]*VWri[3][6][2])+((Cik[6][0][2]*
          VWri[3][6][0])+(Cik[6][1][2]*VWri[3][6][1])));
        Vpk[3][7][0] = ((Cik[7][2][0]*Vpk[3][6][2])+((Cik[7][0][0]*Vpk[3][6][0])
          +(Cik[7][1][0]*Vpk[3][6][1])));
        Vpk[3][7][1] = ((Cik[7][2][1]*Vpk[3][6][2])+((Cik[7][0][1]*Vpk[3][6][0])
          +(Cik[7][1][1]*Vpk[3][6][1])));
        Vpk[3][7][2] = ((Cik[7][2][2]*Vpk[3][6][2])+((Cik[7][0][2]*Vpk[3][6][0])
          +(Cik[7][1][2]*Vpk[3][6][1])));
        Vpk[3][8][0] = (((Cik[8][2][0]*Vpk[3][7][2])+((Cik[8][0][0]*Vpk[3][7][0]
          )+(Cik[8][1][0]*Vpk[3][7][1])))+((rk[1][1]*Wpk[3][8][2])-(rk[1][2]*
          Wpk[3][8][1])));
        Vpk[3][8][1] = (((Cik[8][2][1]*Vpk[3][7][2])+((Cik[8][0][1]*Vpk[3][7][0]
          )+(Cik[8][1][1]*Vpk[3][7][1])))+((rk[1][2]*Wpk[3][8][0])-(rk[1][0]*
          Wpk[3][8][2])));
        Vpk[3][8][2] = (((Cik[8][2][2]*Vpk[3][7][2])+((Cik[8][0][2]*Vpk[3][7][0]
          )+(Cik[8][1][2]*Vpk[3][7][1])))+((rk[1][0]*Wpk[3][8][1])-(rk[1][1]*
          Wpk[3][8][0])));
        VWri[3][9][0] = (Vpk[3][8][0]+((ri[2][2]*Wpk[3][8][1])-(ri[2][1]*
          Wpk[3][8][2])));
        VWri[3][9][1] = (Vpk[3][8][1]+((ri[2][0]*Wpk[3][8][2])-(ri[2][2]*
          Wpk[3][8][0])));
        VWri[3][9][2] = (Vpk[3][8][2]+((ri[2][1]*Wpk[3][8][0])-(ri[2][0]*
          Wpk[3][8][1])));
        Vpk[3][9][0] = (VWri[3][9][0]+((rpp[9][2]*Wpk[3][8][1])-(rpp[9][1]*
          Wpk[3][8][2])));
        Vpk[3][9][1] = (VWri[3][9][1]+((rpp[9][0]*Wpk[3][8][2])-(rpp[9][2]*
          Wpk[3][8][0])));
        Vpk[3][9][2] = (VWri[3][9][2]+((rpp[9][1]*Wpk[3][8][0])-(rpp[9][0]*
          Wpk[3][8][1])));
        Vpk[3][10][0] = (Vpk[3][9][0]+((rpp[10][2]*Wpk[3][8][1])-(rpp[10][1]*
          Wpk[3][8][2])));
        Vpk[3][10][1] = (Vpk[3][9][1]+((rpp[10][0]*Wpk[3][8][2])-(rpp[10][2]*
          Wpk[3][8][0])));
        Vpk[3][10][2] = (Vpk[3][9][2]+((rpp[10][1]*Wpk[3][8][0])-(rpp[10][0]*
          Wpk[3][8][1])));
        Vpk[3][11][0] = (((Cik[11][2][0]*Vpk[3][10][2])+((Cik[11][0][0]*
          Vpk[3][10][0])+(Cik[11][1][0]*Vpk[3][10][1])))+((rk[2][1]*
          Wpk[3][11][2])-(rk[2][2]*Wpk[3][11][1])));
        Vpk[3][11][1] = (((Cik[11][2][1]*Vpk[3][10][2])+((Cik[11][0][1]*
          Vpk[3][10][0])+(Cik[11][1][1]*Vpk[3][10][1])))+((rk[2][2]*
          Wpk[3][11][0])-(rk[2][0]*Wpk[3][11][2])));
        Vpk[3][11][2] = (((Cik[11][2][2]*Vpk[3][10][2])+((Cik[11][0][2]*
          Vpk[3][10][0])+(Cik[11][1][2]*Vpk[3][10][1])))+((rk[2][0]*
          Wpk[3][11][1])-(rk[2][1]*Wpk[3][11][0])));
        VWri[3][12][0] = (Vpk[3][11][0]+((ri[3][2]*Wpk[3][11][1])-(ri[3][1]*
          Wpk[3][11][2])));
        VWri[3][12][1] = (Vpk[3][11][1]+((ri[3][0]*Wpk[3][11][2])-(ri[3][2]*
          Wpk[3][11][0])));
        VWri[3][12][2] = (Vpk[3][11][2]+((ri[3][1]*Wpk[3][11][0])-(ri[3][0]*
          Wpk[3][11][1])));
        Vpk[3][12][0] = (((Cik[12][2][0]*VWri[3][12][2])+((Cik[12][0][0]*
          VWri[3][12][0])+(Cik[12][1][0]*VWri[3][12][1])))+((rk[3][1]*
          Wpk[3][12][2])-(rk[3][2]*Wpk[3][12][1])));
        Vpk[3][12][1] = (((Cik[12][2][1]*VWri[3][12][2])+((Cik[12][0][1]*
          VWri[3][12][0])+(Cik[12][1][1]*VWri[3][12][1])))+((rk[3][2]*
          Wpk[3][12][0])-(rk[3][0]*Wpk[3][12][2])));
        Vpk[3][12][2] = (((Cik[12][2][2]*VWri[3][12][2])+((Cik[12][0][2]*
          VWri[3][12][0])+(Cik[12][1][2]*VWri[3][12][1])))+((rk[3][0]*
          Wpk[3][12][1])-(rk[3][1]*Wpk[3][12][0])));
        VWri[3][13][0] = (Vpk[3][12][0]+((ri[4][2]*Wpk[3][12][1])-(ri[4][1]*
          Wpk[3][12][2])));
        VWri[3][13][1] = (Vpk[3][12][1]+((ri[4][0]*Wpk[3][12][2])-(ri[4][2]*
          Wpk[3][12][0])));
        VWri[3][13][2] = (Vpk[3][12][2]+((ri[4][1]*Wpk[3][12][0])-(ri[4][0]*
          Wpk[3][12][1])));
        Vpk[3][13][0] = (((Cik[13][2][0]*VWri[3][13][2])+((Cik[13][0][0]*
          VWri[3][13][0])+(Cik[13][1][0]*VWri[3][13][1])))+((rk[4][1]*
          Wpk[3][13][2])-(rk[4][2]*Wpk[3][13][1])));
        Vpk[3][13][1] = (((Cik[13][2][1]*VWri[3][13][2])+((Cik[13][0][1]*
          VWri[3][13][0])+(Cik[13][1][1]*VWri[3][13][1])))+((rk[4][2]*
          Wpk[3][13][0])-(rk[4][0]*Wpk[3][13][2])));
        Vpk[3][13][2] = (((Cik[13][2][2]*VWri[3][13][2])+((Cik[13][0][2]*
          VWri[3][13][0])+(Cik[13][1][2]*VWri[3][13][1])))+((rk[4][0]*
          Wpk[3][13][1])-(rk[4][1]*Wpk[3][13][0])));
        VWri[3][14][0] = (Vpk[3][13][0]+((ri[5][2]*Wpk[3][13][1])-(ri[5][1]*
          Wpk[3][13][2])));
        VWri[3][14][1] = (Vpk[3][13][1]+((ri[5][0]*Wpk[3][13][2])-(ri[5][2]*
          Wpk[3][13][0])));
        VWri[3][14][2] = (Vpk[3][13][2]+((ri[5][1]*Wpk[3][13][0])-(ri[5][0]*
          Wpk[3][13][1])));
        Vpk[3][14][0] = (((Cik[14][2][0]*VWri[3][14][2])+((Cik[14][0][0]*
          VWri[3][14][0])+(Cik[14][1][0]*VWri[3][14][1])))+((rk[5][1]*
          Wpk[3][14][2])-(rk[5][2]*Wpk[3][14][1])));
        Vpk[3][14][1] = (((Cik[14][2][1]*VWri[3][14][2])+((Cik[14][0][1]*
          VWri[3][14][0])+(Cik[14][1][1]*VWri[3][14][1])))+((rk[5][2]*
          Wpk[3][14][0])-(rk[5][0]*Wpk[3][14][2])));
        Vpk[3][14][2] = (((Cik[14][2][2]*VWri[3][14][2])+((Cik[14][0][2]*
          VWri[3][14][0])+(Cik[14][1][2]*VWri[3][14][1])))+((rk[5][0]*
          Wpk[3][14][1])-(rk[5][1]*Wpk[3][14][0])));
        VWri[3][15][0] = (Vpk[3][5][0]+((ri[6][2]*Wpk[3][5][1])-(ri[6][1]*
          Wpk[3][5][2])));
        VWri[3][15][1] = (Vpk[3][5][1]+((ri[6][0]*Wpk[3][5][2])-(ri[6][2]*
          Wpk[3][5][0])));
        VWri[3][15][2] = (Vpk[3][5][2]+((ri[6][1]*Wpk[3][5][0])-(ri[6][0]*
          Wpk[3][5][1])));
        Vpk[3][15][0] = ((Cik[15][2][0]*VWri[3][15][2])+((Cik[15][0][0]*
          VWri[3][15][0])+(Cik[15][1][0]*VWri[3][15][1])));
        Vpk[3][15][1] = ((Cik[15][2][1]*VWri[3][15][2])+((Cik[15][0][1]*
          VWri[3][15][0])+(Cik[15][1][1]*VWri[3][15][1])));
        Vpk[3][15][2] = ((Cik[15][2][2]*VWri[3][15][2])+((Cik[15][0][2]*
          VWri[3][15][0])+(Cik[15][1][2]*VWri[3][15][1])));
        Vpk[3][16][0] = ((Cik[16][2][0]*Vpk[3][15][2])+((Cik[16][0][0]*
          Vpk[3][15][0])+(Cik[16][1][0]*Vpk[3][15][1])));
        Vpk[3][16][1] = ((Cik[16][2][1]*Vpk[3][15][2])+((Cik[16][0][1]*
          Vpk[3][15][0])+(Cik[16][1][1]*Vpk[3][15][1])));
        Vpk[3][16][2] = ((Cik[16][2][2]*Vpk[3][15][2])+((Cik[16][0][2]*
          Vpk[3][15][0])+(Cik[16][1][2]*Vpk[3][15][1])));
        Vpk[3][17][0] = (((Cik[17][2][0]*Vpk[3][16][2])+((Cik[17][0][0]*
          Vpk[3][16][0])+(Cik[17][1][0]*Vpk[3][16][1])))+((rk[6][1]*
          Wpk[3][17][2])-(rk[6][2]*Wpk[3][17][1])));
        Vpk[3][17][1] = (((Cik[17][2][1]*Vpk[3][16][2])+((Cik[17][0][1]*
          Vpk[3][16][0])+(Cik[17][1][1]*Vpk[3][16][1])))+((rk[6][2]*
          Wpk[3][17][0])-(rk[6][0]*Wpk[3][17][2])));
        Vpk[3][17][2] = (((Cik[17][2][2]*Vpk[3][16][2])+((Cik[17][0][2]*
          Vpk[3][16][0])+(Cik[17][1][2]*Vpk[3][16][1])))+((rk[6][0]*
          Wpk[3][17][1])-(rk[6][1]*Wpk[3][17][0])));
        VWri[3][18][0] = (Vpk[3][17][0]+((ri[7][2]*Wpk[3][17][1])-(ri[7][1]*
          Wpk[3][17][2])));
        VWri[3][18][1] = (Vpk[3][17][1]+((ri[7][0]*Wpk[3][17][2])-(ri[7][2]*
          Wpk[3][17][0])));
        VWri[3][18][2] = (Vpk[3][17][2]+((ri[7][1]*Wpk[3][17][0])-(ri[7][0]*
          Wpk[3][17][1])));
        Vpk[3][18][0] = (VWri[3][18][0]+((rpp[18][2]*Wpk[3][17][1])-(rpp[18][1]*
          Wpk[3][17][2])));
        Vpk[3][18][1] = (VWri[3][18][1]+((rpp[18][0]*Wpk[3][17][2])-(rpp[18][2]*
          Wpk[3][17][0])));
        Vpk[3][18][2] = (VWri[3][18][2]+((rpp[18][1]*Wpk[3][17][0])-(rpp[18][0]*
          Wpk[3][17][1])));
        Vpk[3][19][0] = (Vpk[3][18][0]+((rpp[19][2]*Wpk[3][17][1])-(rpp[19][1]*
          Wpk[3][17][2])));
        Vpk[3][19][1] = (Vpk[3][18][1]+((rpp[19][0]*Wpk[3][17][2])-(rpp[19][2]*
          Wpk[3][17][0])));
        Vpk[3][19][2] = (Vpk[3][18][2]+((rpp[19][1]*Wpk[3][17][0])-(rpp[19][0]*
          Wpk[3][17][1])));
        Vpk[3][20][0] = (((Cik[20][2][0]*Vpk[3][19][2])+((Cik[20][0][0]*
          Vpk[3][19][0])+(Cik[20][1][0]*Vpk[3][19][1])))+((rk[7][1]*
          Wpk[3][20][2])-(rk[7][2]*Wpk[3][20][1])));
        Vpk[3][20][1] = (((Cik[20][2][1]*Vpk[3][19][2])+((Cik[20][0][1]*
          Vpk[3][19][0])+(Cik[20][1][1]*Vpk[3][19][1])))+((rk[7][2]*
          Wpk[3][20][0])-(rk[7][0]*Wpk[3][20][2])));
        Vpk[3][20][2] = (((Cik[20][2][2]*Vpk[3][19][2])+((Cik[20][0][2]*
          Vpk[3][19][0])+(Cik[20][1][2]*Vpk[3][19][1])))+((rk[7][0]*
          Wpk[3][20][1])-(rk[7][1]*Wpk[3][20][0])));
        VWri[3][21][0] = (Vpk[3][20][0]+((ri[8][2]*Wpk[3][20][1])-(ri[8][1]*
          Wpk[3][20][2])));
        VWri[3][21][1] = (Vpk[3][20][1]+((ri[8][0]*Wpk[3][20][2])-(ri[8][2]*
          Wpk[3][20][0])));
        VWri[3][21][2] = (Vpk[3][20][2]+((ri[8][1]*Wpk[3][20][0])-(ri[8][0]*
          Wpk[3][20][1])));
        Vpk[3][21][0] = (((Cik[21][2][0]*VWri[3][21][2])+((Cik[21][0][0]*
          VWri[3][21][0])+(Cik[21][1][0]*VWri[3][21][1])))+((rk[8][1]*
          Wpk[3][21][2])-(rk[8][2]*Wpk[3][21][1])));
        Vpk[3][21][1] = (((Cik[21][2][1]*VWri[3][21][2])+((Cik[21][0][1]*
          VWri[3][21][0])+(Cik[21][1][1]*VWri[3][21][1])))+((rk[8][2]*
          Wpk[3][21][0])-(rk[8][0]*Wpk[3][21][2])));
        Vpk[3][21][2] = (((Cik[21][2][2]*VWri[3][21][2])+((Cik[21][0][2]*
          VWri[3][21][0])+(Cik[21][1][2]*VWri[3][21][1])))+((rk[8][0]*
          Wpk[3][21][1])-(rk[8][1]*Wpk[3][21][0])));
        VWri[3][22][0] = (Vpk[3][21][0]+((ri[9][2]*Wpk[3][21][1])-(ri[9][1]*
          Wpk[3][21][2])));
        VWri[3][22][1] = (Vpk[3][21][1]+((ri[9][0]*Wpk[3][21][2])-(ri[9][2]*
          Wpk[3][21][0])));
        VWri[3][22][2] = (Vpk[3][21][2]+((ri[9][1]*Wpk[3][21][0])-(ri[9][0]*
          Wpk[3][21][1])));
        Vpk[3][22][0] = (((Cik[22][2][0]*VWri[3][22][2])+((Cik[22][0][0]*
          VWri[3][22][0])+(Cik[22][1][0]*VWri[3][22][1])))+((rk[9][1]*
          Wpk[3][22][2])-(rk[9][2]*Wpk[3][22][1])));
        Vpk[3][22][1] = (((Cik[22][2][1]*VWri[3][22][2])+((Cik[22][0][1]*
          VWri[3][22][0])+(Cik[22][1][1]*VWri[3][22][1])))+((rk[9][2]*
          Wpk[3][22][0])-(rk[9][0]*Wpk[3][22][2])));
        Vpk[3][22][2] = (((Cik[22][2][2]*VWri[3][22][2])+((Cik[22][0][2]*
          VWri[3][22][0])+(Cik[22][1][2]*VWri[3][22][1])))+((rk[9][0]*
          Wpk[3][22][1])-(rk[9][1]*Wpk[3][22][0])));
        VWri[3][23][0] = (Vpk[3][22][0]+((ri[10][2]*Wpk[3][22][1])-(ri[10][1]*
          Wpk[3][22][2])));
        VWri[3][23][1] = (Vpk[3][22][1]+((ri[10][0]*Wpk[3][22][2])-(ri[10][2]*
          Wpk[3][22][0])));
        VWri[3][23][2] = (Vpk[3][22][2]+((ri[10][1]*Wpk[3][22][0])-(ri[10][0]*
          Wpk[3][22][1])));
        Vpk[3][23][0] = (((Cik[23][2][0]*VWri[3][23][2])+((Cik[23][0][0]*
          VWri[3][23][0])+(Cik[23][1][0]*VWri[3][23][1])))+((rk[10][1]*
          Wpk[3][23][2])-(rk[10][2]*Wpk[3][23][1])));
        Vpk[3][23][1] = (((Cik[23][2][1]*VWri[3][23][2])+((Cik[23][0][1]*
          VWri[3][23][0])+(Cik[23][1][1]*VWri[3][23][1])))+((rk[10][2]*
          Wpk[3][23][0])-(rk[10][0]*Wpk[3][23][2])));
        Vpk[3][23][2] = (((Cik[23][2][2]*VWri[3][23][2])+((Cik[23][0][2]*
          VWri[3][23][0])+(Cik[23][1][2]*VWri[3][23][1])))+((rk[10][0]*
          Wpk[3][23][1])-(rk[10][1]*Wpk[3][23][0])));
        VWri[3][24][0] = (Vpk[3][5][0]+((ri[11][2]*Wpk[3][5][1])-(ri[11][1]*
          Wpk[3][5][2])));
        VWri[3][24][1] = (Vpk[3][5][1]+((ri[11][0]*Wpk[3][5][2])-(ri[11][2]*
          Wpk[3][5][0])));
        VWri[3][24][2] = (Vpk[3][5][2]+((ri[11][1]*Wpk[3][5][0])-(ri[11][0]*
          Wpk[3][5][1])));
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
        Vpk[3][26][0] = (((Cik[26][2][0]*Vpk[3][25][2])+((Cik[26][0][0]*
          Vpk[3][25][0])+(Cik[26][1][0]*Vpk[3][25][1])))+((rk[11][1]*
          Wpk[3][26][2])-(rk[11][2]*Wpk[3][26][1])));
        Vpk[3][26][1] = (((Cik[26][2][1]*Vpk[3][25][2])+((Cik[26][0][1]*
          Vpk[3][25][0])+(Cik[26][1][1]*Vpk[3][25][1])))+((rk[11][2]*
          Wpk[3][26][0])-(rk[11][0]*Wpk[3][26][2])));
        Vpk[3][26][2] = (((Cik[26][2][2]*Vpk[3][25][2])+((Cik[26][0][2]*
          Vpk[3][25][0])+(Cik[26][1][2]*Vpk[3][25][1])))+((rk[11][0]*
          Wpk[3][26][1])-(rk[11][1]*Wpk[3][26][0])));
        Vpk[4][5][0] = ((rk[0][1]*Wpk[4][5][2])-(rk[0][2]*Wpk[4][5][1]));
        Vpk[4][5][1] = ((rk[0][2]*Wpk[4][5][0])-(rk[0][0]*Wpk[4][5][2]));
        Vpk[4][5][2] = ((rk[0][0]*Wpk[4][5][1])-(rk[0][1]*Wpk[4][5][0]));
        VWri[4][6][0] = (Vpk[4][5][0]+((ri[1][2]*Wpk[4][5][1])-(ri[1][1]*
          Wpk[4][5][2])));
        VWri[4][6][1] = (Vpk[4][5][1]+((ri[1][0]*Wpk[4][5][2])-(ri[1][2]*
          Wpk[4][5][0])));
        VWri[4][6][2] = (Vpk[4][5][2]+((ri[1][1]*Wpk[4][5][0])-(ri[1][0]*
          Wpk[4][5][1])));
        Vpk[4][6][0] = ((Cik[6][2][0]*VWri[4][6][2])+((Cik[6][0][0]*
          VWri[4][6][0])+(Cik[6][1][0]*VWri[4][6][1])));
        Vpk[4][6][1] = ((Cik[6][2][1]*VWri[4][6][2])+((Cik[6][0][1]*
          VWri[4][6][0])+(Cik[6][1][1]*VWri[4][6][1])));
        Vpk[4][6][2] = ((Cik[6][2][2]*VWri[4][6][2])+((Cik[6][0][2]*
          VWri[4][6][0])+(Cik[6][1][2]*VWri[4][6][1])));
        Vpk[4][7][0] = ((Cik[7][2][0]*Vpk[4][6][2])+((Cik[7][0][0]*Vpk[4][6][0])
          +(Cik[7][1][0]*Vpk[4][6][1])));
        Vpk[4][7][1] = ((Cik[7][2][1]*Vpk[4][6][2])+((Cik[7][0][1]*Vpk[4][6][0])
          +(Cik[7][1][1]*Vpk[4][6][1])));
        Vpk[4][7][2] = ((Cik[7][2][2]*Vpk[4][6][2])+((Cik[7][0][2]*Vpk[4][6][0])
          +(Cik[7][1][2]*Vpk[4][6][1])));
        Vpk[4][8][0] = (((Cik[8][2][0]*Vpk[4][7][2])+((Cik[8][0][0]*Vpk[4][7][0]
          )+(Cik[8][1][0]*Vpk[4][7][1])))+((rk[1][1]*Wpk[4][8][2])-(rk[1][2]*
          Wpk[4][8][1])));
        Vpk[4][8][1] = (((Cik[8][2][1]*Vpk[4][7][2])+((Cik[8][0][1]*Vpk[4][7][0]
          )+(Cik[8][1][1]*Vpk[4][7][1])))+((rk[1][2]*Wpk[4][8][0])-(rk[1][0]*
          Wpk[4][8][2])));
        Vpk[4][8][2] = (((Cik[8][2][2]*Vpk[4][7][2])+((Cik[8][0][2]*Vpk[4][7][0]
          )+(Cik[8][1][2]*Vpk[4][7][1])))+((rk[1][0]*Wpk[4][8][1])-(rk[1][1]*
          Wpk[4][8][0])));
        VWri[4][9][0] = (Vpk[4][8][0]+((ri[2][2]*Wpk[4][8][1])-(ri[2][1]*
          Wpk[4][8][2])));
        VWri[4][9][1] = (Vpk[4][8][1]+((ri[2][0]*Wpk[4][8][2])-(ri[2][2]*
          Wpk[4][8][0])));
        VWri[4][9][2] = (Vpk[4][8][2]+((ri[2][1]*Wpk[4][8][0])-(ri[2][0]*
          Wpk[4][8][1])));
        Vpk[4][9][0] = (VWri[4][9][0]+((rpp[9][2]*Wpk[4][8][1])-(rpp[9][1]*
          Wpk[4][8][2])));
        Vpk[4][9][1] = (VWri[4][9][1]+((rpp[9][0]*Wpk[4][8][2])-(rpp[9][2]*
          Wpk[4][8][0])));
        Vpk[4][9][2] = (VWri[4][9][2]+((rpp[9][1]*Wpk[4][8][0])-(rpp[9][0]*
          Wpk[4][8][1])));
        Vpk[4][10][0] = (Vpk[4][9][0]+((rpp[10][2]*Wpk[4][8][1])-(rpp[10][1]*
          Wpk[4][8][2])));
        Vpk[4][10][1] = (Vpk[4][9][1]+((rpp[10][0]*Wpk[4][8][2])-(rpp[10][2]*
          Wpk[4][8][0])));
        Vpk[4][10][2] = (Vpk[4][9][2]+((rpp[10][1]*Wpk[4][8][0])-(rpp[10][0]*
          Wpk[4][8][1])));
        Vpk[4][11][0] = (((Cik[11][2][0]*Vpk[4][10][2])+((Cik[11][0][0]*
          Vpk[4][10][0])+(Cik[11][1][0]*Vpk[4][10][1])))+((rk[2][1]*
          Wpk[4][11][2])-(rk[2][2]*Wpk[4][11][1])));
        Vpk[4][11][1] = (((Cik[11][2][1]*Vpk[4][10][2])+((Cik[11][0][1]*
          Vpk[4][10][0])+(Cik[11][1][1]*Vpk[4][10][1])))+((rk[2][2]*
          Wpk[4][11][0])-(rk[2][0]*Wpk[4][11][2])));
        Vpk[4][11][2] = (((Cik[11][2][2]*Vpk[4][10][2])+((Cik[11][0][2]*
          Vpk[4][10][0])+(Cik[11][1][2]*Vpk[4][10][1])))+((rk[2][0]*
          Wpk[4][11][1])-(rk[2][1]*Wpk[4][11][0])));
        VWri[4][12][0] = (Vpk[4][11][0]+((ri[3][2]*Wpk[4][11][1])-(ri[3][1]*
          Wpk[4][11][2])));
        VWri[4][12][1] = (Vpk[4][11][1]+((ri[3][0]*Wpk[4][11][2])-(ri[3][2]*
          Wpk[4][11][0])));
        VWri[4][12][2] = (Vpk[4][11][2]+((ri[3][1]*Wpk[4][11][0])-(ri[3][0]*
          Wpk[4][11][1])));
        Vpk[4][12][0] = (((Cik[12][2][0]*VWri[4][12][2])+((Cik[12][0][0]*
          VWri[4][12][0])+(Cik[12][1][0]*VWri[4][12][1])))+((rk[3][1]*
          Wpk[4][12][2])-(rk[3][2]*Wpk[4][12][1])));
        Vpk[4][12][1] = (((Cik[12][2][1]*VWri[4][12][2])+((Cik[12][0][1]*
          VWri[4][12][0])+(Cik[12][1][1]*VWri[4][12][1])))+((rk[3][2]*
          Wpk[4][12][0])-(rk[3][0]*Wpk[4][12][2])));
        Vpk[4][12][2] = (((Cik[12][2][2]*VWri[4][12][2])+((Cik[12][0][2]*
          VWri[4][12][0])+(Cik[12][1][2]*VWri[4][12][1])))+((rk[3][0]*
          Wpk[4][12][1])-(rk[3][1]*Wpk[4][12][0])));
        VWri[4][13][0] = (Vpk[4][12][0]+((ri[4][2]*Wpk[4][12][1])-(ri[4][1]*
          Wpk[4][12][2])));
        VWri[4][13][1] = (Vpk[4][12][1]+((ri[4][0]*Wpk[4][12][2])-(ri[4][2]*
          Wpk[4][12][0])));
        VWri[4][13][2] = (Vpk[4][12][2]+((ri[4][1]*Wpk[4][12][0])-(ri[4][0]*
          Wpk[4][12][1])));
        Vpk[4][13][0] = (((Cik[13][2][0]*VWri[4][13][2])+((Cik[13][0][0]*
          VWri[4][13][0])+(Cik[13][1][0]*VWri[4][13][1])))+((rk[4][1]*
          Wpk[4][13][2])-(rk[4][2]*Wpk[4][13][1])));
        Vpk[4][13][1] = (((Cik[13][2][1]*VWri[4][13][2])+((Cik[13][0][1]*
          VWri[4][13][0])+(Cik[13][1][1]*VWri[4][13][1])))+((rk[4][2]*
          Wpk[4][13][0])-(rk[4][0]*Wpk[4][13][2])));
        Vpk[4][13][2] = (((Cik[13][2][2]*VWri[4][13][2])+((Cik[13][0][2]*
          VWri[4][13][0])+(Cik[13][1][2]*VWri[4][13][1])))+((rk[4][0]*
          Wpk[4][13][1])-(rk[4][1]*Wpk[4][13][0])));
        VWri[4][14][0] = (Vpk[4][13][0]+((ri[5][2]*Wpk[4][13][1])-(ri[5][1]*
          Wpk[4][13][2])));
        VWri[4][14][1] = (Vpk[4][13][1]+((ri[5][0]*Wpk[4][13][2])-(ri[5][2]*
          Wpk[4][13][0])));
        VWri[4][14][2] = (Vpk[4][13][2]+((ri[5][1]*Wpk[4][13][0])-(ri[5][0]*
          Wpk[4][13][1])));
        Vpk[4][14][0] = (((Cik[14][2][0]*VWri[4][14][2])+((Cik[14][0][0]*
          VWri[4][14][0])+(Cik[14][1][0]*VWri[4][14][1])))+((rk[5][1]*
          Wpk[4][14][2])-(rk[5][2]*Wpk[4][14][1])));
        Vpk[4][14][1] = (((Cik[14][2][1]*VWri[4][14][2])+((Cik[14][0][1]*
          VWri[4][14][0])+(Cik[14][1][1]*VWri[4][14][1])))+((rk[5][2]*
          Wpk[4][14][0])-(rk[5][0]*Wpk[4][14][2])));
        Vpk[4][14][2] = (((Cik[14][2][2]*VWri[4][14][2])+((Cik[14][0][2]*
          VWri[4][14][0])+(Cik[14][1][2]*VWri[4][14][1])))+((rk[5][0]*
          Wpk[4][14][1])-(rk[5][1]*Wpk[4][14][0])));
        VWri[4][15][0] = (Vpk[4][5][0]+((ri[6][2]*Wpk[4][5][1])-(ri[6][1]*
          Wpk[4][5][2])));
        VWri[4][15][1] = (Vpk[4][5][1]+((ri[6][0]*Wpk[4][5][2])-(ri[6][2]*
          Wpk[4][5][0])));
        VWri[4][15][2] = (Vpk[4][5][2]+((ri[6][1]*Wpk[4][5][0])-(ri[6][0]*
          Wpk[4][5][1])));
        Vpk[4][15][0] = ((Cik[15][2][0]*VWri[4][15][2])+((Cik[15][0][0]*
          VWri[4][15][0])+(Cik[15][1][0]*VWri[4][15][1])));
        Vpk[4][15][1] = ((Cik[15][2][1]*VWri[4][15][2])+((Cik[15][0][1]*
          VWri[4][15][0])+(Cik[15][1][1]*VWri[4][15][1])));
        Vpk[4][15][2] = ((Cik[15][2][2]*VWri[4][15][2])+((Cik[15][0][2]*
          VWri[4][15][0])+(Cik[15][1][2]*VWri[4][15][1])));
        Vpk[4][16][0] = ((Cik[16][2][0]*Vpk[4][15][2])+((Cik[16][0][0]*
          Vpk[4][15][0])+(Cik[16][1][0]*Vpk[4][15][1])));
        Vpk[4][16][1] = ((Cik[16][2][1]*Vpk[4][15][2])+((Cik[16][0][1]*
          Vpk[4][15][0])+(Cik[16][1][1]*Vpk[4][15][1])));
        Vpk[4][16][2] = ((Cik[16][2][2]*Vpk[4][15][2])+((Cik[16][0][2]*
          Vpk[4][15][0])+(Cik[16][1][2]*Vpk[4][15][1])));
        Vpk[4][17][0] = (((Cik[17][2][0]*Vpk[4][16][2])+((Cik[17][0][0]*
          Vpk[4][16][0])+(Cik[17][1][0]*Vpk[4][16][1])))+((rk[6][1]*
          Wpk[4][17][2])-(rk[6][2]*Wpk[4][17][1])));
        Vpk[4][17][1] = (((Cik[17][2][1]*Vpk[4][16][2])+((Cik[17][0][1]*
          Vpk[4][16][0])+(Cik[17][1][1]*Vpk[4][16][1])))+((rk[6][2]*
          Wpk[4][17][0])-(rk[6][0]*Wpk[4][17][2])));
        Vpk[4][17][2] = (((Cik[17][2][2]*Vpk[4][16][2])+((Cik[17][0][2]*
          Vpk[4][16][0])+(Cik[17][1][2]*Vpk[4][16][1])))+((rk[6][0]*
          Wpk[4][17][1])-(rk[6][1]*Wpk[4][17][0])));
        VWri[4][18][0] = (Vpk[4][17][0]+((ri[7][2]*Wpk[4][17][1])-(ri[7][1]*
          Wpk[4][17][2])));
        VWri[4][18][1] = (Vpk[4][17][1]+((ri[7][0]*Wpk[4][17][2])-(ri[7][2]*
          Wpk[4][17][0])));
        VWri[4][18][2] = (Vpk[4][17][2]+((ri[7][1]*Wpk[4][17][0])-(ri[7][0]*
          Wpk[4][17][1])));
        Vpk[4][18][0] = (VWri[4][18][0]+((rpp[18][2]*Wpk[4][17][1])-(rpp[18][1]*
          Wpk[4][17][2])));
        Vpk[4][18][1] = (VWri[4][18][1]+((rpp[18][0]*Wpk[4][17][2])-(rpp[18][2]*
          Wpk[4][17][0])));
        Vpk[4][18][2] = (VWri[4][18][2]+((rpp[18][1]*Wpk[4][17][0])-(rpp[18][0]*
          Wpk[4][17][1])));
        Vpk[4][19][0] = (Vpk[4][18][0]+((rpp[19][2]*Wpk[4][17][1])-(rpp[19][1]*
          Wpk[4][17][2])));
        Vpk[4][19][1] = (Vpk[4][18][1]+((rpp[19][0]*Wpk[4][17][2])-(rpp[19][2]*
          Wpk[4][17][0])));
        Vpk[4][19][2] = (Vpk[4][18][2]+((rpp[19][1]*Wpk[4][17][0])-(rpp[19][0]*
          Wpk[4][17][1])));
        Vpk[4][20][0] = (((Cik[20][2][0]*Vpk[4][19][2])+((Cik[20][0][0]*
          Vpk[4][19][0])+(Cik[20][1][0]*Vpk[4][19][1])))+((rk[7][1]*
          Wpk[4][20][2])-(rk[7][2]*Wpk[4][20][1])));
        Vpk[4][20][1] = (((Cik[20][2][1]*Vpk[4][19][2])+((Cik[20][0][1]*
          Vpk[4][19][0])+(Cik[20][1][1]*Vpk[4][19][1])))+((rk[7][2]*
          Wpk[4][20][0])-(rk[7][0]*Wpk[4][20][2])));
        Vpk[4][20][2] = (((Cik[20][2][2]*Vpk[4][19][2])+((Cik[20][0][2]*
          Vpk[4][19][0])+(Cik[20][1][2]*Vpk[4][19][1])))+((rk[7][0]*
          Wpk[4][20][1])-(rk[7][1]*Wpk[4][20][0])));
        VWri[4][21][0] = (Vpk[4][20][0]+((ri[8][2]*Wpk[4][20][1])-(ri[8][1]*
          Wpk[4][20][2])));
        VWri[4][21][1] = (Vpk[4][20][1]+((ri[8][0]*Wpk[4][20][2])-(ri[8][2]*
          Wpk[4][20][0])));
        VWri[4][21][2] = (Vpk[4][20][2]+((ri[8][1]*Wpk[4][20][0])-(ri[8][0]*
          Wpk[4][20][1])));
        Vpk[4][21][0] = (((Cik[21][2][0]*VWri[4][21][2])+((Cik[21][0][0]*
          VWri[4][21][0])+(Cik[21][1][0]*VWri[4][21][1])))+((rk[8][1]*
          Wpk[4][21][2])-(rk[8][2]*Wpk[4][21][1])));
        Vpk[4][21][1] = (((Cik[21][2][1]*VWri[4][21][2])+((Cik[21][0][1]*
          VWri[4][21][0])+(Cik[21][1][1]*VWri[4][21][1])))+((rk[8][2]*
          Wpk[4][21][0])-(rk[8][0]*Wpk[4][21][2])));
        Vpk[4][21][2] = (((Cik[21][2][2]*VWri[4][21][2])+((Cik[21][0][2]*
          VWri[4][21][0])+(Cik[21][1][2]*VWri[4][21][1])))+((rk[8][0]*
          Wpk[4][21][1])-(rk[8][1]*Wpk[4][21][0])));
        VWri[4][22][0] = (Vpk[4][21][0]+((ri[9][2]*Wpk[4][21][1])-(ri[9][1]*
          Wpk[4][21][2])));
        VWri[4][22][1] = (Vpk[4][21][1]+((ri[9][0]*Wpk[4][21][2])-(ri[9][2]*
          Wpk[4][21][0])));
        VWri[4][22][2] = (Vpk[4][21][2]+((ri[9][1]*Wpk[4][21][0])-(ri[9][0]*
          Wpk[4][21][1])));
        Vpk[4][22][0] = (((Cik[22][2][0]*VWri[4][22][2])+((Cik[22][0][0]*
          VWri[4][22][0])+(Cik[22][1][0]*VWri[4][22][1])))+((rk[9][1]*
          Wpk[4][22][2])-(rk[9][2]*Wpk[4][22][1])));
        Vpk[4][22][1] = (((Cik[22][2][1]*VWri[4][22][2])+((Cik[22][0][1]*
          VWri[4][22][0])+(Cik[22][1][1]*VWri[4][22][1])))+((rk[9][2]*
          Wpk[4][22][0])-(rk[9][0]*Wpk[4][22][2])));
        Vpk[4][22][2] = (((Cik[22][2][2]*VWri[4][22][2])+((Cik[22][0][2]*
          VWri[4][22][0])+(Cik[22][1][2]*VWri[4][22][1])))+((rk[9][0]*
          Wpk[4][22][1])-(rk[9][1]*Wpk[4][22][0])));
        VWri[4][23][0] = (Vpk[4][22][0]+((ri[10][2]*Wpk[4][22][1])-(ri[10][1]*
          Wpk[4][22][2])));
        VWri[4][23][1] = (Vpk[4][22][1]+((ri[10][0]*Wpk[4][22][2])-(ri[10][2]*
          Wpk[4][22][0])));
        VWri[4][23][2] = (Vpk[4][22][2]+((ri[10][1]*Wpk[4][22][0])-(ri[10][0]*
          Wpk[4][22][1])));
        Vpk[4][23][0] = (((Cik[23][2][0]*VWri[4][23][2])+((Cik[23][0][0]*
          VWri[4][23][0])+(Cik[23][1][0]*VWri[4][23][1])))+((rk[10][1]*
          Wpk[4][23][2])-(rk[10][2]*Wpk[4][23][1])));
        Vpk[4][23][1] = (((Cik[23][2][1]*VWri[4][23][2])+((Cik[23][0][1]*
          VWri[4][23][0])+(Cik[23][1][1]*VWri[4][23][1])))+((rk[10][2]*
          Wpk[4][23][0])-(rk[10][0]*Wpk[4][23][2])));
        Vpk[4][23][2] = (((Cik[23][2][2]*VWri[4][23][2])+((Cik[23][0][2]*
          VWri[4][23][0])+(Cik[23][1][2]*VWri[4][23][1])))+((rk[10][0]*
          Wpk[4][23][1])-(rk[10][1]*Wpk[4][23][0])));
        VWri[4][24][0] = (Vpk[4][5][0]+((ri[11][2]*Wpk[4][5][1])-(ri[11][1]*
          Wpk[4][5][2])));
        VWri[4][24][1] = (Vpk[4][5][1]+((ri[11][0]*Wpk[4][5][2])-(ri[11][2]*
          Wpk[4][5][0])));
        VWri[4][24][2] = (Vpk[4][5][2]+((ri[11][1]*Wpk[4][5][0])-(ri[11][0]*
          Wpk[4][5][1])));
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
        Vpk[4][26][0] = (((Cik[26][2][0]*Vpk[4][25][2])+((Cik[26][0][0]*
          Vpk[4][25][0])+(Cik[26][1][0]*Vpk[4][25][1])))+((rk[11][1]*
          Wpk[4][26][2])-(rk[11][2]*Wpk[4][26][1])));
        Vpk[4][26][1] = (((Cik[26][2][1]*Vpk[4][25][2])+((Cik[26][0][1]*
          Vpk[4][25][0])+(Cik[26][1][1]*Vpk[4][25][1])))+((rk[11][2]*
          Wpk[4][26][0])-(rk[11][0]*Wpk[4][26][2])));
        Vpk[4][26][2] = (((Cik[26][2][2]*Vpk[4][25][2])+((Cik[26][0][2]*
          Vpk[4][25][0])+(Cik[26][1][2]*Vpk[4][25][1])))+((rk[11][0]*
          Wpk[4][26][1])-(rk[11][1]*Wpk[4][26][0])));
        Vpk[5][5][0] = ((pin[2][2]*rk[0][1])-(pin[2][1]*rk[0][2]));
        Vpk[5][5][1] = ((pin[2][0]*rk[0][2])-(pin[2][2]*rk[0][0]));
        Vpk[5][5][2] = ((pin[2][1]*rk[0][0])-(pin[2][0]*rk[0][1]));
        VWri[5][6][0] = (Vpk[5][5][0]+((pin[2][1]*ri[1][2])-(pin[2][2]*ri[1][1])
          ));
        VWri[5][6][1] = (Vpk[5][5][1]+((pin[2][2]*ri[1][0])-(pin[2][0]*ri[1][2])
          ));
        VWri[5][6][2] = (Vpk[5][5][2]+((pin[2][0]*ri[1][1])-(pin[2][1]*ri[1][0])
          ));
        Vpk[5][6][0] = ((Cik[6][2][0]*VWri[5][6][2])+((Cik[6][0][0]*
          VWri[5][6][0])+(Cik[6][1][0]*VWri[5][6][1])));
        Vpk[5][6][1] = ((Cik[6][2][1]*VWri[5][6][2])+((Cik[6][0][1]*
          VWri[5][6][0])+(Cik[6][1][1]*VWri[5][6][1])));
        Vpk[5][6][2] = ((Cik[6][2][2]*VWri[5][6][2])+((Cik[6][0][2]*
          VWri[5][6][0])+(Cik[6][1][2]*VWri[5][6][1])));
        Vpk[5][7][0] = ((Cik[7][2][0]*Vpk[5][6][2])+((Cik[7][0][0]*Vpk[5][6][0])
          +(Cik[7][1][0]*Vpk[5][6][1])));
        Vpk[5][7][1] = ((Cik[7][2][1]*Vpk[5][6][2])+((Cik[7][0][1]*Vpk[5][6][0])
          +(Cik[7][1][1]*Vpk[5][6][1])));
        Vpk[5][7][2] = ((Cik[7][2][2]*Vpk[5][6][2])+((Cik[7][0][2]*Vpk[5][6][0])
          +(Cik[7][1][2]*Vpk[5][6][1])));
        Vpk[5][8][0] = (((Cik[8][2][0]*Vpk[5][7][2])+((Cik[8][0][0]*Vpk[5][7][0]
          )+(Cik[8][1][0]*Vpk[5][7][1])))+((rk[1][1]*Wpk[5][8][2])-(rk[1][2]*
          Wpk[5][8][1])));
        Vpk[5][8][1] = (((Cik[8][2][1]*Vpk[5][7][2])+((Cik[8][0][1]*Vpk[5][7][0]
          )+(Cik[8][1][1]*Vpk[5][7][1])))+((rk[1][2]*Wpk[5][8][0])-(rk[1][0]*
          Wpk[5][8][2])));
        Vpk[5][8][2] = (((Cik[8][2][2]*Vpk[5][7][2])+((Cik[8][0][2]*Vpk[5][7][0]
          )+(Cik[8][1][2]*Vpk[5][7][1])))+((rk[1][0]*Wpk[5][8][1])-(rk[1][1]*
          Wpk[5][8][0])));
        VWri[5][9][0] = (Vpk[5][8][0]+((ri[2][2]*Wpk[5][8][1])-(ri[2][1]*
          Wpk[5][8][2])));
        VWri[5][9][1] = (Vpk[5][8][1]+((ri[2][0]*Wpk[5][8][2])-(ri[2][2]*
          Wpk[5][8][0])));
        VWri[5][9][2] = (Vpk[5][8][2]+((ri[2][1]*Wpk[5][8][0])-(ri[2][0]*
          Wpk[5][8][1])));
        Vpk[5][9][0] = (VWri[5][9][0]+((rpp[9][2]*Wpk[5][8][1])-(rpp[9][1]*
          Wpk[5][8][2])));
        Vpk[5][9][1] = (VWri[5][9][1]+((rpp[9][0]*Wpk[5][8][2])-(rpp[9][2]*
          Wpk[5][8][0])));
        Vpk[5][9][2] = (VWri[5][9][2]+((rpp[9][1]*Wpk[5][8][0])-(rpp[9][0]*
          Wpk[5][8][1])));
        Vpk[5][10][0] = (Vpk[5][9][0]+((rpp[10][2]*Wpk[5][8][1])-(rpp[10][1]*
          Wpk[5][8][2])));
        Vpk[5][10][1] = (Vpk[5][9][1]+((rpp[10][0]*Wpk[5][8][2])-(rpp[10][2]*
          Wpk[5][8][0])));
        Vpk[5][10][2] = (Vpk[5][9][2]+((rpp[10][1]*Wpk[5][8][0])-(rpp[10][0]*
          Wpk[5][8][1])));
        Vpk[5][11][0] = (((Cik[11][2][0]*Vpk[5][10][2])+((Cik[11][0][0]*
          Vpk[5][10][0])+(Cik[11][1][0]*Vpk[5][10][1])))+((rk[2][1]*
          Wpk[5][11][2])-(rk[2][2]*Wpk[5][11][1])));
        Vpk[5][11][1] = (((Cik[11][2][1]*Vpk[5][10][2])+((Cik[11][0][1]*
          Vpk[5][10][0])+(Cik[11][1][1]*Vpk[5][10][1])))+((rk[2][2]*
          Wpk[5][11][0])-(rk[2][0]*Wpk[5][11][2])));
        Vpk[5][11][2] = (((Cik[11][2][2]*Vpk[5][10][2])+((Cik[11][0][2]*
          Vpk[5][10][0])+(Cik[11][1][2]*Vpk[5][10][1])))+((rk[2][0]*
          Wpk[5][11][1])-(rk[2][1]*Wpk[5][11][0])));
        VWri[5][12][0] = (Vpk[5][11][0]+((ri[3][2]*Wpk[5][11][1])-(ri[3][1]*
          Wpk[5][11][2])));
        VWri[5][12][1] = (Vpk[5][11][1]+((ri[3][0]*Wpk[5][11][2])-(ri[3][2]*
          Wpk[5][11][0])));
        VWri[5][12][2] = (Vpk[5][11][2]+((ri[3][1]*Wpk[5][11][0])-(ri[3][0]*
          Wpk[5][11][1])));
        Vpk[5][12][0] = (((Cik[12][2][0]*VWri[5][12][2])+((Cik[12][0][0]*
          VWri[5][12][0])+(Cik[12][1][0]*VWri[5][12][1])))+((rk[3][1]*
          Wpk[5][12][2])-(rk[3][2]*Wpk[5][12][1])));
        Vpk[5][12][1] = (((Cik[12][2][1]*VWri[5][12][2])+((Cik[12][0][1]*
          VWri[5][12][0])+(Cik[12][1][1]*VWri[5][12][1])))+((rk[3][2]*
          Wpk[5][12][0])-(rk[3][0]*Wpk[5][12][2])));
        Vpk[5][12][2] = (((Cik[12][2][2]*VWri[5][12][2])+((Cik[12][0][2]*
          VWri[5][12][0])+(Cik[12][1][2]*VWri[5][12][1])))+((rk[3][0]*
          Wpk[5][12][1])-(rk[3][1]*Wpk[5][12][0])));
        VWri[5][13][0] = (Vpk[5][12][0]+((ri[4][2]*Wpk[5][12][1])-(ri[4][1]*
          Wpk[5][12][2])));
        VWri[5][13][1] = (Vpk[5][12][1]+((ri[4][0]*Wpk[5][12][2])-(ri[4][2]*
          Wpk[5][12][0])));
        VWri[5][13][2] = (Vpk[5][12][2]+((ri[4][1]*Wpk[5][12][0])-(ri[4][0]*
          Wpk[5][12][1])));
        Vpk[5][13][0] = (((Cik[13][2][0]*VWri[5][13][2])+((Cik[13][0][0]*
          VWri[5][13][0])+(Cik[13][1][0]*VWri[5][13][1])))+((rk[4][1]*
          Wpk[5][13][2])-(rk[4][2]*Wpk[5][13][1])));
        Vpk[5][13][1] = (((Cik[13][2][1]*VWri[5][13][2])+((Cik[13][0][1]*
          VWri[5][13][0])+(Cik[13][1][1]*VWri[5][13][1])))+((rk[4][2]*
          Wpk[5][13][0])-(rk[4][0]*Wpk[5][13][2])));
        Vpk[5][13][2] = (((Cik[13][2][2]*VWri[5][13][2])+((Cik[13][0][2]*
          VWri[5][13][0])+(Cik[13][1][2]*VWri[5][13][1])))+((rk[4][0]*
          Wpk[5][13][1])-(rk[4][1]*Wpk[5][13][0])));
        VWri[5][14][0] = (Vpk[5][13][0]+((ri[5][2]*Wpk[5][13][1])-(ri[5][1]*
          Wpk[5][13][2])));
        VWri[5][14][1] = (Vpk[5][13][1]+((ri[5][0]*Wpk[5][13][2])-(ri[5][2]*
          Wpk[5][13][0])));
        VWri[5][14][2] = (Vpk[5][13][2]+((ri[5][1]*Wpk[5][13][0])-(ri[5][0]*
          Wpk[5][13][1])));
        Vpk[5][14][0] = (((Cik[14][2][0]*VWri[5][14][2])+((Cik[14][0][0]*
          VWri[5][14][0])+(Cik[14][1][0]*VWri[5][14][1])))+((rk[5][1]*
          Wpk[5][14][2])-(rk[5][2]*Wpk[5][14][1])));
        Vpk[5][14][1] = (((Cik[14][2][1]*VWri[5][14][2])+((Cik[14][0][1]*
          VWri[5][14][0])+(Cik[14][1][1]*VWri[5][14][1])))+((rk[5][2]*
          Wpk[5][14][0])-(rk[5][0]*Wpk[5][14][2])));
        Vpk[5][14][2] = (((Cik[14][2][2]*VWri[5][14][2])+((Cik[14][0][2]*
          VWri[5][14][0])+(Cik[14][1][2]*VWri[5][14][1])))+((rk[5][0]*
          Wpk[5][14][1])-(rk[5][1]*Wpk[5][14][0])));
        VWri[5][15][0] = (Vpk[5][5][0]+((pin[2][1]*ri[6][2])-(pin[2][2]*ri[6][1]
          )));
        VWri[5][15][1] = (Vpk[5][5][1]+((pin[2][2]*ri[6][0])-(pin[2][0]*ri[6][2]
          )));
        VWri[5][15][2] = (Vpk[5][5][2]+((pin[2][0]*ri[6][1])-(pin[2][1]*ri[6][0]
          )));
        Vpk[5][15][0] = ((Cik[15][2][0]*VWri[5][15][2])+((Cik[15][0][0]*
          VWri[5][15][0])+(Cik[15][1][0]*VWri[5][15][1])));
        Vpk[5][15][1] = ((Cik[15][2][1]*VWri[5][15][2])+((Cik[15][0][1]*
          VWri[5][15][0])+(Cik[15][1][1]*VWri[5][15][1])));
        Vpk[5][15][2] = ((Cik[15][2][2]*VWri[5][15][2])+((Cik[15][0][2]*
          VWri[5][15][0])+(Cik[15][1][2]*VWri[5][15][1])));
        Vpk[5][16][0] = ((Cik[16][2][0]*Vpk[5][15][2])+((Cik[16][0][0]*
          Vpk[5][15][0])+(Cik[16][1][0]*Vpk[5][15][1])));
        Vpk[5][16][1] = ((Cik[16][2][1]*Vpk[5][15][2])+((Cik[16][0][1]*
          Vpk[5][15][0])+(Cik[16][1][1]*Vpk[5][15][1])));
        Vpk[5][16][2] = ((Cik[16][2][2]*Vpk[5][15][2])+((Cik[16][0][2]*
          Vpk[5][15][0])+(Cik[16][1][2]*Vpk[5][15][1])));
        Vpk[5][17][0] = (((Cik[17][2][0]*Vpk[5][16][2])+((Cik[17][0][0]*
          Vpk[5][16][0])+(Cik[17][1][0]*Vpk[5][16][1])))+((rk[6][1]*
          Wpk[5][17][2])-(rk[6][2]*Wpk[5][17][1])));
        Vpk[5][17][1] = (((Cik[17][2][1]*Vpk[5][16][2])+((Cik[17][0][1]*
          Vpk[5][16][0])+(Cik[17][1][1]*Vpk[5][16][1])))+((rk[6][2]*
          Wpk[5][17][0])-(rk[6][0]*Wpk[5][17][2])));
        Vpk[5][17][2] = (((Cik[17][2][2]*Vpk[5][16][2])+((Cik[17][0][2]*
          Vpk[5][16][0])+(Cik[17][1][2]*Vpk[5][16][1])))+((rk[6][0]*
          Wpk[5][17][1])-(rk[6][1]*Wpk[5][17][0])));
        VWri[5][18][0] = (Vpk[5][17][0]+((ri[7][2]*Wpk[5][17][1])-(ri[7][1]*
          Wpk[5][17][2])));
        VWri[5][18][1] = (Vpk[5][17][1]+((ri[7][0]*Wpk[5][17][2])-(ri[7][2]*
          Wpk[5][17][0])));
        VWri[5][18][2] = (Vpk[5][17][2]+((ri[7][1]*Wpk[5][17][0])-(ri[7][0]*
          Wpk[5][17][1])));
        Vpk[5][18][0] = (VWri[5][18][0]+((rpp[18][2]*Wpk[5][17][1])-(rpp[18][1]*
          Wpk[5][17][2])));
        Vpk[5][18][1] = (VWri[5][18][1]+((rpp[18][0]*Wpk[5][17][2])-(rpp[18][2]*
          Wpk[5][17][0])));
        Vpk[5][18][2] = (VWri[5][18][2]+((rpp[18][1]*Wpk[5][17][0])-(rpp[18][0]*
          Wpk[5][17][1])));
        Vpk[5][19][0] = (Vpk[5][18][0]+((rpp[19][2]*Wpk[5][17][1])-(rpp[19][1]*
          Wpk[5][17][2])));
        Vpk[5][19][1] = (Vpk[5][18][1]+((rpp[19][0]*Wpk[5][17][2])-(rpp[19][2]*
          Wpk[5][17][0])));
        Vpk[5][19][2] = (Vpk[5][18][2]+((rpp[19][1]*Wpk[5][17][0])-(rpp[19][0]*
          Wpk[5][17][1])));
        Vpk[5][20][0] = (((Cik[20][2][0]*Vpk[5][19][2])+((Cik[20][0][0]*
          Vpk[5][19][0])+(Cik[20][1][0]*Vpk[5][19][1])))+((rk[7][1]*
          Wpk[5][20][2])-(rk[7][2]*Wpk[5][20][1])));
        Vpk[5][20][1] = (((Cik[20][2][1]*Vpk[5][19][2])+((Cik[20][0][1]*
          Vpk[5][19][0])+(Cik[20][1][1]*Vpk[5][19][1])))+((rk[7][2]*
          Wpk[5][20][0])-(rk[7][0]*Wpk[5][20][2])));
        Vpk[5][20][2] = (((Cik[20][2][2]*Vpk[5][19][2])+((Cik[20][0][2]*
          Vpk[5][19][0])+(Cik[20][1][2]*Vpk[5][19][1])))+((rk[7][0]*
          Wpk[5][20][1])-(rk[7][1]*Wpk[5][20][0])));
        VWri[5][21][0] = (Vpk[5][20][0]+((ri[8][2]*Wpk[5][20][1])-(ri[8][1]*
          Wpk[5][20][2])));
        VWri[5][21][1] = (Vpk[5][20][1]+((ri[8][0]*Wpk[5][20][2])-(ri[8][2]*
          Wpk[5][20][0])));
        VWri[5][21][2] = (Vpk[5][20][2]+((ri[8][1]*Wpk[5][20][0])-(ri[8][0]*
          Wpk[5][20][1])));
        Vpk[5][21][0] = (((Cik[21][2][0]*VWri[5][21][2])+((Cik[21][0][0]*
          VWri[5][21][0])+(Cik[21][1][0]*VWri[5][21][1])))+((rk[8][1]*
          Wpk[5][21][2])-(rk[8][2]*Wpk[5][21][1])));
        Vpk[5][21][1] = (((Cik[21][2][1]*VWri[5][21][2])+((Cik[21][0][1]*
          VWri[5][21][0])+(Cik[21][1][1]*VWri[5][21][1])))+((rk[8][2]*
          Wpk[5][21][0])-(rk[8][0]*Wpk[5][21][2])));
        Vpk[5][21][2] = (((Cik[21][2][2]*VWri[5][21][2])+((Cik[21][0][2]*
          VWri[5][21][0])+(Cik[21][1][2]*VWri[5][21][1])))+((rk[8][0]*
          Wpk[5][21][1])-(rk[8][1]*Wpk[5][21][0])));
        VWri[5][22][0] = (Vpk[5][21][0]+((ri[9][2]*Wpk[5][21][1])-(ri[9][1]*
          Wpk[5][21][2])));
        VWri[5][22][1] = (Vpk[5][21][1]+((ri[9][0]*Wpk[5][21][2])-(ri[9][2]*
          Wpk[5][21][0])));
        VWri[5][22][2] = (Vpk[5][21][2]+((ri[9][1]*Wpk[5][21][0])-(ri[9][0]*
          Wpk[5][21][1])));
        Vpk[5][22][0] = (((Cik[22][2][0]*VWri[5][22][2])+((Cik[22][0][0]*
          VWri[5][22][0])+(Cik[22][1][0]*VWri[5][22][1])))+((rk[9][1]*
          Wpk[5][22][2])-(rk[9][2]*Wpk[5][22][1])));
        Vpk[5][22][1] = (((Cik[22][2][1]*VWri[5][22][2])+((Cik[22][0][1]*
          VWri[5][22][0])+(Cik[22][1][1]*VWri[5][22][1])))+((rk[9][2]*
          Wpk[5][22][0])-(rk[9][0]*Wpk[5][22][2])));
        Vpk[5][22][2] = (((Cik[22][2][2]*VWri[5][22][2])+((Cik[22][0][2]*
          VWri[5][22][0])+(Cik[22][1][2]*VWri[5][22][1])))+((rk[9][0]*
          Wpk[5][22][1])-(rk[9][1]*Wpk[5][22][0])));
        VWri[5][23][0] = (Vpk[5][22][0]+((ri[10][2]*Wpk[5][22][1])-(ri[10][1]*
          Wpk[5][22][2])));
        VWri[5][23][1] = (Vpk[5][22][1]+((ri[10][0]*Wpk[5][22][2])-(ri[10][2]*
          Wpk[5][22][0])));
        VWri[5][23][2] = (Vpk[5][22][2]+((ri[10][1]*Wpk[5][22][0])-(ri[10][0]*
          Wpk[5][22][1])));
        Vpk[5][23][0] = (((Cik[23][2][0]*VWri[5][23][2])+((Cik[23][0][0]*
          VWri[5][23][0])+(Cik[23][1][0]*VWri[5][23][1])))+((rk[10][1]*
          Wpk[5][23][2])-(rk[10][2]*Wpk[5][23][1])));
        Vpk[5][23][1] = (((Cik[23][2][1]*VWri[5][23][2])+((Cik[23][0][1]*
          VWri[5][23][0])+(Cik[23][1][1]*VWri[5][23][1])))+((rk[10][2]*
          Wpk[5][23][0])-(rk[10][0]*Wpk[5][23][2])));
        Vpk[5][23][2] = (((Cik[23][2][2]*VWri[5][23][2])+((Cik[23][0][2]*
          VWri[5][23][0])+(Cik[23][1][2]*VWri[5][23][1])))+((rk[10][0]*
          Wpk[5][23][1])-(rk[10][1]*Wpk[5][23][0])));
        VWri[5][24][0] = (Vpk[5][5][0]+((pin[2][1]*ri[11][2])-(pin[2][2]*
          ri[11][1])));
        VWri[5][24][1] = (Vpk[5][5][1]+((pin[2][2]*ri[11][0])-(pin[2][0]*
          ri[11][2])));
        VWri[5][24][2] = (Vpk[5][5][2]+((pin[2][0]*ri[11][1])-(pin[2][1]*
          ri[11][0])));
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
        Vpk[5][26][0] = (((Cik[26][2][0]*Vpk[5][25][2])+((Cik[26][0][0]*
          Vpk[5][25][0])+(Cik[26][1][0]*Vpk[5][25][1])))+((rk[11][1]*
          Wpk[5][26][2])-(rk[11][2]*Wpk[5][26][1])));
        Vpk[5][26][1] = (((Cik[26][2][1]*Vpk[5][25][2])+((Cik[26][0][1]*
          Vpk[5][25][0])+(Cik[26][1][1]*Vpk[5][25][1])))+((rk[11][2]*
          Wpk[5][26][0])-(rk[11][0]*Wpk[5][26][2])));
        Vpk[5][26][2] = (((Cik[26][2][2]*Vpk[5][25][2])+((Cik[26][0][2]*
          Vpk[5][25][0])+(Cik[26][1][2]*Vpk[5][25][1])))+((rk[11][0]*
          Wpk[5][26][1])-(rk[11][1]*Wpk[5][26][0])));
        Vpk[6][8][0] = ((rk[1][1]*Wpk[6][8][2])-(rk[1][2]*Wpk[6][8][1]));
        Vpk[6][8][1] = ((rk[1][2]*Wpk[6][8][0])-(rk[1][0]*Wpk[6][8][2]));
        Vpk[6][8][2] = ((rk[1][0]*Wpk[6][8][1])-(rk[1][1]*Wpk[6][8][0]));
        VWri[6][9][0] = (Vpk[6][8][0]+((ri[2][2]*Wpk[6][8][1])-(ri[2][1]*
          Wpk[6][8][2])));
        VWri[6][9][1] = (Vpk[6][8][1]+((ri[2][0]*Wpk[6][8][2])-(ri[2][2]*
          Wpk[6][8][0])));
        VWri[6][9][2] = (Vpk[6][8][2]+((ri[2][1]*Wpk[6][8][0])-(ri[2][0]*
          Wpk[6][8][1])));
        Vpk[6][9][0] = (VWri[6][9][0]+((rpp[9][2]*Wpk[6][8][1])-(rpp[9][1]*
          Wpk[6][8][2])));
        Vpk[6][9][1] = (VWri[6][9][1]+((rpp[9][0]*Wpk[6][8][2])-(rpp[9][2]*
          Wpk[6][8][0])));
        Vpk[6][9][2] = (VWri[6][9][2]+((rpp[9][1]*Wpk[6][8][0])-(rpp[9][0]*
          Wpk[6][8][1])));
        Vpk[6][10][0] = (Vpk[6][9][0]+((rpp[10][2]*Wpk[6][8][1])-(rpp[10][1]*
          Wpk[6][8][2])));
        Vpk[6][10][1] = (Vpk[6][9][1]+((rpp[10][0]*Wpk[6][8][2])-(rpp[10][2]*
          Wpk[6][8][0])));
        Vpk[6][10][2] = (Vpk[6][9][2]+((rpp[10][1]*Wpk[6][8][0])-(rpp[10][0]*
          Wpk[6][8][1])));
        Vpk[6][11][0] = (((Cik[11][2][0]*Vpk[6][10][2])+((Cik[11][0][0]*
          Vpk[6][10][0])+(Cik[11][1][0]*Vpk[6][10][1])))+((rk[2][1]*
          Wpk[6][11][2])-(rk[2][2]*Wpk[6][11][1])));
        Vpk[6][11][1] = (((Cik[11][2][1]*Vpk[6][10][2])+((Cik[11][0][1]*
          Vpk[6][10][0])+(Cik[11][1][1]*Vpk[6][10][1])))+((rk[2][2]*
          Wpk[6][11][0])-(rk[2][0]*Wpk[6][11][2])));
        Vpk[6][11][2] = (((Cik[11][2][2]*Vpk[6][10][2])+((Cik[11][0][2]*
          Vpk[6][10][0])+(Cik[11][1][2]*Vpk[6][10][1])))+((rk[2][0]*
          Wpk[6][11][1])-(rk[2][1]*Wpk[6][11][0])));
        VWri[6][12][0] = (Vpk[6][11][0]+((ri[3][2]*Wpk[6][11][1])-(ri[3][1]*
          Wpk[6][11][2])));
        VWri[6][12][1] = (Vpk[6][11][1]+((ri[3][0]*Wpk[6][11][2])-(ri[3][2]*
          Wpk[6][11][0])));
        VWri[6][12][2] = (Vpk[6][11][2]+((ri[3][1]*Wpk[6][11][0])-(ri[3][0]*
          Wpk[6][11][1])));
        Vpk[6][12][0] = (((Cik[12][2][0]*VWri[6][12][2])+((Cik[12][0][0]*
          VWri[6][12][0])+(Cik[12][1][0]*VWri[6][12][1])))+((rk[3][1]*
          Wpk[6][12][2])-(rk[3][2]*Wpk[6][12][1])));
        Vpk[6][12][1] = (((Cik[12][2][1]*VWri[6][12][2])+((Cik[12][0][1]*
          VWri[6][12][0])+(Cik[12][1][1]*VWri[6][12][1])))+((rk[3][2]*
          Wpk[6][12][0])-(rk[3][0]*Wpk[6][12][2])));
        Vpk[6][12][2] = (((Cik[12][2][2]*VWri[6][12][2])+((Cik[12][0][2]*
          VWri[6][12][0])+(Cik[12][1][2]*VWri[6][12][1])))+((rk[3][0]*
          Wpk[6][12][1])-(rk[3][1]*Wpk[6][12][0])));
        VWri[6][13][0] = (Vpk[6][12][0]+((ri[4][2]*Wpk[6][12][1])-(ri[4][1]*
          Wpk[6][12][2])));
        VWri[6][13][1] = (Vpk[6][12][1]+((ri[4][0]*Wpk[6][12][2])-(ri[4][2]*
          Wpk[6][12][0])));
        VWri[6][13][2] = (Vpk[6][12][2]+((ri[4][1]*Wpk[6][12][0])-(ri[4][0]*
          Wpk[6][12][1])));
        Vpk[6][13][0] = (((Cik[13][2][0]*VWri[6][13][2])+((Cik[13][0][0]*
          VWri[6][13][0])+(Cik[13][1][0]*VWri[6][13][1])))+((rk[4][1]*
          Wpk[6][13][2])-(rk[4][2]*Wpk[6][13][1])));
        Vpk[6][13][1] = (((Cik[13][2][1]*VWri[6][13][2])+((Cik[13][0][1]*
          VWri[6][13][0])+(Cik[13][1][1]*VWri[6][13][1])))+((rk[4][2]*
          Wpk[6][13][0])-(rk[4][0]*Wpk[6][13][2])));
        Vpk[6][13][2] = (((Cik[13][2][2]*VWri[6][13][2])+((Cik[13][0][2]*
          VWri[6][13][0])+(Cik[13][1][2]*VWri[6][13][1])))+((rk[4][0]*
          Wpk[6][13][1])-(rk[4][1]*Wpk[6][13][0])));
        VWri[6][14][0] = (Vpk[6][13][0]+((ri[5][2]*Wpk[6][13][1])-(ri[5][1]*
          Wpk[6][13][2])));
        VWri[6][14][1] = (Vpk[6][13][1]+((ri[5][0]*Wpk[6][13][2])-(ri[5][2]*
          Wpk[6][13][0])));
        VWri[6][14][2] = (Vpk[6][13][2]+((ri[5][1]*Wpk[6][13][0])-(ri[5][0]*
          Wpk[6][13][1])));
        Vpk[6][14][0] = (((Cik[14][2][0]*VWri[6][14][2])+((Cik[14][0][0]*
          VWri[6][14][0])+(Cik[14][1][0]*VWri[6][14][1])))+((rk[5][1]*
          Wpk[6][14][2])-(rk[5][2]*Wpk[6][14][1])));
        Vpk[6][14][1] = (((Cik[14][2][1]*VWri[6][14][2])+((Cik[14][0][1]*
          VWri[6][14][0])+(Cik[14][1][1]*VWri[6][14][1])))+((rk[5][2]*
          Wpk[6][14][0])-(rk[5][0]*Wpk[6][14][2])));
        Vpk[6][14][2] = (((Cik[14][2][2]*VWri[6][14][2])+((Cik[14][0][2]*
          VWri[6][14][0])+(Cik[14][1][2]*VWri[6][14][1])))+((rk[5][0]*
          Wpk[6][14][1])-(rk[5][1]*Wpk[6][14][0])));
        Vpk[7][8][0] = ((rk[1][1]*Wpk[7][8][2])-(rk[1][2]*Wpk[7][8][1]));
        Vpk[7][8][1] = ((rk[1][2]*Wpk[7][8][0])-(rk[1][0]*Wpk[7][8][2]));
        Vpk[7][8][2] = ((rk[1][0]*Wpk[7][8][1])-(rk[1][1]*Wpk[7][8][0]));
        VWri[7][9][0] = (Vpk[7][8][0]+((ri[2][2]*Wpk[7][8][1])-(ri[2][1]*
          Wpk[7][8][2])));
        VWri[7][9][1] = (Vpk[7][8][1]+((ri[2][0]*Wpk[7][8][2])-(ri[2][2]*
          Wpk[7][8][0])));
        VWri[7][9][2] = (Vpk[7][8][2]+((ri[2][1]*Wpk[7][8][0])-(ri[2][0]*
          Wpk[7][8][1])));
        Vpk[7][9][0] = (VWri[7][9][0]+((rpp[9][2]*Wpk[7][8][1])-(rpp[9][1]*
          Wpk[7][8][2])));
        Vpk[7][9][1] = (VWri[7][9][1]+((rpp[9][0]*Wpk[7][8][2])-(rpp[9][2]*
          Wpk[7][8][0])));
        Vpk[7][9][2] = (VWri[7][9][2]+((rpp[9][1]*Wpk[7][8][0])-(rpp[9][0]*
          Wpk[7][8][1])));
        Vpk[7][10][0] = (Vpk[7][9][0]+((rpp[10][2]*Wpk[7][8][1])-(rpp[10][1]*
          Wpk[7][8][2])));
        Vpk[7][10][1] = (Vpk[7][9][1]+((rpp[10][0]*Wpk[7][8][2])-(rpp[10][2]*
          Wpk[7][8][0])));
        Vpk[7][10][2] = (Vpk[7][9][2]+((rpp[10][1]*Wpk[7][8][0])-(rpp[10][0]*
          Wpk[7][8][1])));
        Vpk[7][11][0] = (((Cik[11][2][0]*Vpk[7][10][2])+((Cik[11][0][0]*
          Vpk[7][10][0])+(Cik[11][1][0]*Vpk[7][10][1])))+((rk[2][1]*
          Wpk[7][11][2])-(rk[2][2]*Wpk[7][11][1])));
        Vpk[7][11][1] = (((Cik[11][2][1]*Vpk[7][10][2])+((Cik[11][0][1]*
          Vpk[7][10][0])+(Cik[11][1][1]*Vpk[7][10][1])))+((rk[2][2]*
          Wpk[7][11][0])-(rk[2][0]*Wpk[7][11][2])));
        Vpk[7][11][2] = (((Cik[11][2][2]*Vpk[7][10][2])+((Cik[11][0][2]*
          Vpk[7][10][0])+(Cik[11][1][2]*Vpk[7][10][1])))+((rk[2][0]*
          Wpk[7][11][1])-(rk[2][1]*Wpk[7][11][0])));
        VWri[7][12][0] = (Vpk[7][11][0]+((ri[3][2]*Wpk[7][11][1])-(ri[3][1]*
          Wpk[7][11][2])));
        VWri[7][12][1] = (Vpk[7][11][1]+((ri[3][0]*Wpk[7][11][2])-(ri[3][2]*
          Wpk[7][11][0])));
        VWri[7][12][2] = (Vpk[7][11][2]+((ri[3][1]*Wpk[7][11][0])-(ri[3][0]*
          Wpk[7][11][1])));
        Vpk[7][12][0] = (((Cik[12][2][0]*VWri[7][12][2])+((Cik[12][0][0]*
          VWri[7][12][0])+(Cik[12][1][0]*VWri[7][12][1])))+((rk[3][1]*
          Wpk[7][12][2])-(rk[3][2]*Wpk[7][12][1])));
        Vpk[7][12][1] = (((Cik[12][2][1]*VWri[7][12][2])+((Cik[12][0][1]*
          VWri[7][12][0])+(Cik[12][1][1]*VWri[7][12][1])))+((rk[3][2]*
          Wpk[7][12][0])-(rk[3][0]*Wpk[7][12][2])));
        Vpk[7][12][2] = (((Cik[12][2][2]*VWri[7][12][2])+((Cik[12][0][2]*
          VWri[7][12][0])+(Cik[12][1][2]*VWri[7][12][1])))+((rk[3][0]*
          Wpk[7][12][1])-(rk[3][1]*Wpk[7][12][0])));
        VWri[7][13][0] = (Vpk[7][12][0]+((ri[4][2]*Wpk[7][12][1])-(ri[4][1]*
          Wpk[7][12][2])));
        VWri[7][13][1] = (Vpk[7][12][1]+((ri[4][0]*Wpk[7][12][2])-(ri[4][2]*
          Wpk[7][12][0])));
        VWri[7][13][2] = (Vpk[7][12][2]+((ri[4][1]*Wpk[7][12][0])-(ri[4][0]*
          Wpk[7][12][1])));
        Vpk[7][13][0] = (((Cik[13][2][0]*VWri[7][13][2])+((Cik[13][0][0]*
          VWri[7][13][0])+(Cik[13][1][0]*VWri[7][13][1])))+((rk[4][1]*
          Wpk[7][13][2])-(rk[4][2]*Wpk[7][13][1])));
        Vpk[7][13][1] = (((Cik[13][2][1]*VWri[7][13][2])+((Cik[13][0][1]*
          VWri[7][13][0])+(Cik[13][1][1]*VWri[7][13][1])))+((rk[4][2]*
          Wpk[7][13][0])-(rk[4][0]*Wpk[7][13][2])));
        Vpk[7][13][2] = (((Cik[13][2][2]*VWri[7][13][2])+((Cik[13][0][2]*
          VWri[7][13][0])+(Cik[13][1][2]*VWri[7][13][1])))+((rk[4][0]*
          Wpk[7][13][1])-(rk[4][1]*Wpk[7][13][0])));
        VWri[7][14][0] = (Vpk[7][13][0]+((ri[5][2]*Wpk[7][13][1])-(ri[5][1]*
          Wpk[7][13][2])));
        VWri[7][14][1] = (Vpk[7][13][1]+((ri[5][0]*Wpk[7][13][2])-(ri[5][2]*
          Wpk[7][13][0])));
        VWri[7][14][2] = (Vpk[7][13][2]+((ri[5][1]*Wpk[7][13][0])-(ri[5][0]*
          Wpk[7][13][1])));
        Vpk[7][14][0] = (((Cik[14][2][0]*VWri[7][14][2])+((Cik[14][0][0]*
          VWri[7][14][0])+(Cik[14][1][0]*VWri[7][14][1])))+((rk[5][1]*
          Wpk[7][14][2])-(rk[5][2]*Wpk[7][14][1])));
        Vpk[7][14][1] = (((Cik[14][2][1]*VWri[7][14][2])+((Cik[14][0][1]*
          VWri[7][14][0])+(Cik[14][1][1]*VWri[7][14][1])))+((rk[5][2]*
          Wpk[7][14][0])-(rk[5][0]*Wpk[7][14][2])));
        Vpk[7][14][2] = (((Cik[14][2][2]*VWri[7][14][2])+((Cik[14][0][2]*
          VWri[7][14][0])+(Cik[14][1][2]*VWri[7][14][1])))+((rk[5][0]*
          Wpk[7][14][1])-(rk[5][1]*Wpk[7][14][0])));
        Vpk[8][8][0] = ((pin[8][2]*rk[1][1])-(pin[8][1]*rk[1][2]));
        Vpk[8][8][1] = ((pin[8][0]*rk[1][2])-(pin[8][2]*rk[1][0]));
        Vpk[8][8][2] = ((pin[8][1]*rk[1][0])-(pin[8][0]*rk[1][1]));
        VWri[8][9][0] = (Vpk[8][8][0]+((pin[8][1]*ri[2][2])-(pin[8][2]*ri[2][1])
          ));
        VWri[8][9][1] = (Vpk[8][8][1]+((pin[8][2]*ri[2][0])-(pin[8][0]*ri[2][2])
          ));
        VWri[8][9][2] = (Vpk[8][8][2]+((pin[8][0]*ri[2][1])-(pin[8][1]*ri[2][0])
          ));
        Vpk[8][9][0] = (VWri[8][9][0]+((pin[8][1]*rpp[9][2])-(pin[8][2]*
          rpp[9][1])));
        Vpk[8][9][1] = (VWri[8][9][1]+((pin[8][2]*rpp[9][0])-(pin[8][0]*
          rpp[9][2])));
        Vpk[8][9][2] = (VWri[8][9][2]+((pin[8][0]*rpp[9][1])-(pin[8][1]*
          rpp[9][0])));
        Vpk[8][10][0] = (Vpk[8][9][0]+((pin[8][1]*rpp[10][2])-(pin[8][2]*
          rpp[10][1])));
        Vpk[8][10][1] = (Vpk[8][9][1]+((pin[8][2]*rpp[10][0])-(pin[8][0]*
          rpp[10][2])));
        Vpk[8][10][2] = (Vpk[8][9][2]+((pin[8][0]*rpp[10][1])-(pin[8][1]*
          rpp[10][0])));
        Vpk[8][11][0] = (((Cik[11][2][0]*Vpk[8][10][2])+((Cik[11][0][0]*
          Vpk[8][10][0])+(Cik[11][1][0]*Vpk[8][10][1])))+((rk[2][1]*
          Wpk[8][11][2])-(rk[2][2]*Wpk[8][11][1])));
        Vpk[8][11][1] = (((Cik[11][2][1]*Vpk[8][10][2])+((Cik[11][0][1]*
          Vpk[8][10][0])+(Cik[11][1][1]*Vpk[8][10][1])))+((rk[2][2]*
          Wpk[8][11][0])-(rk[2][0]*Wpk[8][11][2])));
        Vpk[8][11][2] = (((Cik[11][2][2]*Vpk[8][10][2])+((Cik[11][0][2]*
          Vpk[8][10][0])+(Cik[11][1][2]*Vpk[8][10][1])))+((rk[2][0]*
          Wpk[8][11][1])-(rk[2][1]*Wpk[8][11][0])));
        VWri[8][12][0] = (Vpk[8][11][0]+((ri[3][2]*Wpk[8][11][1])-(ri[3][1]*
          Wpk[8][11][2])));
        VWri[8][12][1] = (Vpk[8][11][1]+((ri[3][0]*Wpk[8][11][2])-(ri[3][2]*
          Wpk[8][11][0])));
        VWri[8][12][2] = (Vpk[8][11][2]+((ri[3][1]*Wpk[8][11][0])-(ri[3][0]*
          Wpk[8][11][1])));
        Vpk[8][12][0] = (((Cik[12][2][0]*VWri[8][12][2])+((Cik[12][0][0]*
          VWri[8][12][0])+(Cik[12][1][0]*VWri[8][12][1])))+((rk[3][1]*
          Wpk[8][12][2])-(rk[3][2]*Wpk[8][12][1])));
        Vpk[8][12][1] = (((Cik[12][2][1]*VWri[8][12][2])+((Cik[12][0][1]*
          VWri[8][12][0])+(Cik[12][1][1]*VWri[8][12][1])))+((rk[3][2]*
          Wpk[8][12][0])-(rk[3][0]*Wpk[8][12][2])));
        Vpk[8][12][2] = (((Cik[12][2][2]*VWri[8][12][2])+((Cik[12][0][2]*
          VWri[8][12][0])+(Cik[12][1][2]*VWri[8][12][1])))+((rk[3][0]*
          Wpk[8][12][1])-(rk[3][1]*Wpk[8][12][0])));
        VWri[8][13][0] = (Vpk[8][12][0]+((ri[4][2]*Wpk[8][12][1])-(ri[4][1]*
          Wpk[8][12][2])));
        VWri[8][13][1] = (Vpk[8][12][1]+((ri[4][0]*Wpk[8][12][2])-(ri[4][2]*
          Wpk[8][12][0])));
        VWri[8][13][2] = (Vpk[8][12][2]+((ri[4][1]*Wpk[8][12][0])-(ri[4][0]*
          Wpk[8][12][1])));
        Vpk[8][13][0] = (((Cik[13][2][0]*VWri[8][13][2])+((Cik[13][0][0]*
          VWri[8][13][0])+(Cik[13][1][0]*VWri[8][13][1])))+((rk[4][1]*
          Wpk[8][13][2])-(rk[4][2]*Wpk[8][13][1])));
        Vpk[8][13][1] = (((Cik[13][2][1]*VWri[8][13][2])+((Cik[13][0][1]*
          VWri[8][13][0])+(Cik[13][1][1]*VWri[8][13][1])))+((rk[4][2]*
          Wpk[8][13][0])-(rk[4][0]*Wpk[8][13][2])));
        Vpk[8][13][2] = (((Cik[13][2][2]*VWri[8][13][2])+((Cik[13][0][2]*
          VWri[8][13][0])+(Cik[13][1][2]*VWri[8][13][1])))+((rk[4][0]*
          Wpk[8][13][1])-(rk[4][1]*Wpk[8][13][0])));
        VWri[8][14][0] = (Vpk[8][13][0]+((ri[5][2]*Wpk[8][13][1])-(ri[5][1]*
          Wpk[8][13][2])));
        VWri[8][14][1] = (Vpk[8][13][1]+((ri[5][0]*Wpk[8][13][2])-(ri[5][2]*
          Wpk[8][13][0])));
        VWri[8][14][2] = (Vpk[8][13][2]+((ri[5][1]*Wpk[8][13][0])-(ri[5][0]*
          Wpk[8][13][1])));
        Vpk[8][14][0] = (((Cik[14][2][0]*VWri[8][14][2])+((Cik[14][0][0]*
          VWri[8][14][0])+(Cik[14][1][0]*VWri[8][14][1])))+((rk[5][1]*
          Wpk[8][14][2])-(rk[5][2]*Wpk[8][14][1])));
        Vpk[8][14][1] = (((Cik[14][2][1]*VWri[8][14][2])+((Cik[14][0][1]*
          VWri[8][14][0])+(Cik[14][1][1]*VWri[8][14][1])))+((rk[5][2]*
          Wpk[8][14][0])-(rk[5][0]*Wpk[8][14][2])));
        Vpk[8][14][2] = (((Cik[14][2][2]*VWri[8][14][2])+((Cik[14][0][2]*
          VWri[8][14][0])+(Cik[14][1][2]*VWri[8][14][1])))+((rk[5][0]*
          Wpk[8][14][1])-(rk[5][1]*Wpk[8][14][0])));
        Vpk[9][9][0] = pin[9][0];
        Vpk[9][9][1] = pin[9][1];
        Vpk[9][9][2] = pin[9][2];
        Vpk[9][10][0] = pin[9][0];
        Vpk[9][10][1] = pin[9][1];
        Vpk[9][10][2] = pin[9][2];
        Vpk[9][11][0] = ((Cik[11][2][0]*pin[9][2])+((Cik[11][0][0]*pin[9][0])+(
          Cik[11][1][0]*pin[9][1])));
        Vpk[9][11][1] = ((Cik[11][2][1]*pin[9][2])+((Cik[11][0][1]*pin[9][0])+(
          Cik[11][1][1]*pin[9][1])));
        Vpk[9][11][2] = ((Cik[11][2][2]*pin[9][2])+((Cik[11][0][2]*pin[9][0])+(
          Cik[11][1][2]*pin[9][1])));
        Vpk[9][12][0] = ((Cik[12][2][0]*Vpk[9][11][2])+((Cik[12][0][0]*
          Vpk[9][11][0])+(Cik[12][1][0]*Vpk[9][11][1])));
        Vpk[9][12][1] = ((Cik[12][2][1]*Vpk[9][11][2])+((Cik[12][0][1]*
          Vpk[9][11][0])+(Cik[12][1][1]*Vpk[9][11][1])));
        Vpk[9][12][2] = ((Cik[12][2][2]*Vpk[9][11][2])+((Cik[12][0][2]*
          Vpk[9][11][0])+(Cik[12][1][2]*Vpk[9][11][1])));
        Vpk[9][13][0] = ((Cik[13][2][0]*Vpk[9][12][2])+((Cik[13][0][0]*
          Vpk[9][12][0])+(Cik[13][1][0]*Vpk[9][12][1])));
        Vpk[9][13][1] = ((Cik[13][2][1]*Vpk[9][12][2])+((Cik[13][0][1]*
          Vpk[9][12][0])+(Cik[13][1][1]*Vpk[9][12][1])));
        Vpk[9][13][2] = ((Cik[13][2][2]*Vpk[9][12][2])+((Cik[13][0][2]*
          Vpk[9][12][0])+(Cik[13][1][2]*Vpk[9][12][1])));
        Vpk[9][14][0] = ((Cik[14][2][0]*Vpk[9][13][2])+((Cik[14][0][0]*
          Vpk[9][13][0])+(Cik[14][1][0]*Vpk[9][13][1])));
        Vpk[9][14][1] = ((Cik[14][2][1]*Vpk[9][13][2])+((Cik[14][0][1]*
          Vpk[9][13][0])+(Cik[14][1][1]*Vpk[9][13][1])));
        Vpk[9][14][2] = ((Cik[14][2][2]*Vpk[9][13][2])+((Cik[14][0][2]*
          Vpk[9][13][0])+(Cik[14][1][2]*Vpk[9][13][1])));
        Vpk[10][10][0] = pin[10][0];
        Vpk[10][10][1] = pin[10][1];
        Vpk[10][10][2] = pin[10][2];
        Vpk[10][11][0] = ((Cik[11][2][0]*pin[10][2])+((Cik[11][0][0]*pin[10][0])
          +(Cik[11][1][0]*pin[10][1])));
        Vpk[10][11][1] = ((Cik[11][2][1]*pin[10][2])+((Cik[11][0][1]*pin[10][0])
          +(Cik[11][1][1]*pin[10][1])));
        Vpk[10][11][2] = ((Cik[11][2][2]*pin[10][2])+((Cik[11][0][2]*pin[10][0])
          +(Cik[11][1][2]*pin[10][1])));
        Vpk[10][12][0] = ((Cik[12][2][0]*Vpk[10][11][2])+((Cik[12][0][0]*
          Vpk[10][11][0])+(Cik[12][1][0]*Vpk[10][11][1])));
        Vpk[10][12][1] = ((Cik[12][2][1]*Vpk[10][11][2])+((Cik[12][0][1]*
          Vpk[10][11][0])+(Cik[12][1][1]*Vpk[10][11][1])));
        Vpk[10][12][2] = ((Cik[12][2][2]*Vpk[10][11][2])+((Cik[12][0][2]*
          Vpk[10][11][0])+(Cik[12][1][2]*Vpk[10][11][1])));
        Vpk[10][13][0] = ((Cik[13][2][0]*Vpk[10][12][2])+((Cik[13][0][0]*
          Vpk[10][12][0])+(Cik[13][1][0]*Vpk[10][12][1])));
        Vpk[10][13][1] = ((Cik[13][2][1]*Vpk[10][12][2])+((Cik[13][0][1]*
          Vpk[10][12][0])+(Cik[13][1][1]*Vpk[10][12][1])));
        Vpk[10][13][2] = ((Cik[13][2][2]*Vpk[10][12][2])+((Cik[13][0][2]*
          Vpk[10][12][0])+(Cik[13][1][2]*Vpk[10][12][1])));
        Vpk[10][14][0] = ((Cik[14][2][0]*Vpk[10][13][2])+((Cik[14][0][0]*
          Vpk[10][13][0])+(Cik[14][1][0]*Vpk[10][13][1])));
        Vpk[10][14][1] = ((Cik[14][2][1]*Vpk[10][13][2])+((Cik[14][0][1]*
          Vpk[10][13][0])+(Cik[14][1][1]*Vpk[10][13][1])));
        Vpk[10][14][2] = ((Cik[14][2][2]*Vpk[10][13][2])+((Cik[14][0][2]*
          Vpk[10][13][0])+(Cik[14][1][2]*Vpk[10][13][1])));
        Vpk[11][11][0] = ((pin[11][2]*rk[2][1])-(pin[11][1]*rk[2][2]));
        Vpk[11][11][1] = ((pin[11][0]*rk[2][2])-(pin[11][2]*rk[2][0]));
        Vpk[11][11][2] = ((pin[11][1]*rk[2][0])-(pin[11][0]*rk[2][1]));
        VWri[11][12][0] = (Vpk[11][11][0]+((pin[11][1]*ri[3][2])-(pin[11][2]*
          ri[3][1])));
        VWri[11][12][1] = (Vpk[11][11][1]+((pin[11][2]*ri[3][0])-(pin[11][0]*
          ri[3][2])));
        VWri[11][12][2] = (Vpk[11][11][2]+((pin[11][0]*ri[3][1])-(pin[11][1]*
          ri[3][0])));
        Vpk[11][12][0] = (((Cik[12][2][0]*VWri[11][12][2])+((Cik[12][0][0]*
          VWri[11][12][0])+(Cik[12][1][0]*VWri[11][12][1])))+((rk[3][1]*
          Wpk[11][12][2])-(rk[3][2]*Wpk[11][12][1])));
        Vpk[11][12][1] = (((Cik[12][2][1]*VWri[11][12][2])+((Cik[12][0][1]*
          VWri[11][12][0])+(Cik[12][1][1]*VWri[11][12][1])))+((rk[3][2]*
          Wpk[11][12][0])-(rk[3][0]*Wpk[11][12][2])));
        Vpk[11][12][2] = (((Cik[12][2][2]*VWri[11][12][2])+((Cik[12][0][2]*
          VWri[11][12][0])+(Cik[12][1][2]*VWri[11][12][1])))+((rk[3][0]*
          Wpk[11][12][1])-(rk[3][1]*Wpk[11][12][0])));
        VWri[11][13][0] = (Vpk[11][12][0]+((ri[4][2]*Wpk[11][12][1])-(ri[4][1]*
          Wpk[11][12][2])));
        VWri[11][13][1] = (Vpk[11][12][1]+((ri[4][0]*Wpk[11][12][2])-(ri[4][2]*
          Wpk[11][12][0])));
        VWri[11][13][2] = (Vpk[11][12][2]+((ri[4][1]*Wpk[11][12][0])-(ri[4][0]*
          Wpk[11][12][1])));
        Vpk[11][13][0] = (((Cik[13][2][0]*VWri[11][13][2])+((Cik[13][0][0]*
          VWri[11][13][0])+(Cik[13][1][0]*VWri[11][13][1])))+((rk[4][1]*
          Wpk[11][13][2])-(rk[4][2]*Wpk[11][13][1])));
        Vpk[11][13][1] = (((Cik[13][2][1]*VWri[11][13][2])+((Cik[13][0][1]*
          VWri[11][13][0])+(Cik[13][1][1]*VWri[11][13][1])))+((rk[4][2]*
          Wpk[11][13][0])-(rk[4][0]*Wpk[11][13][2])));
        Vpk[11][13][2] = (((Cik[13][2][2]*VWri[11][13][2])+((Cik[13][0][2]*
          VWri[11][13][0])+(Cik[13][1][2]*VWri[11][13][1])))+((rk[4][0]*
          Wpk[11][13][1])-(rk[4][1]*Wpk[11][13][0])));
        VWri[11][14][0] = (Vpk[11][13][0]+((ri[5][2]*Wpk[11][13][1])-(ri[5][1]*
          Wpk[11][13][2])));
        VWri[11][14][1] = (Vpk[11][13][1]+((ri[5][0]*Wpk[11][13][2])-(ri[5][2]*
          Wpk[11][13][0])));
        VWri[11][14][2] = (Vpk[11][13][2]+((ri[5][1]*Wpk[11][13][0])-(ri[5][0]*
          Wpk[11][13][1])));
        Vpk[11][14][0] = (((Cik[14][2][0]*VWri[11][14][2])+((Cik[14][0][0]*
          VWri[11][14][0])+(Cik[14][1][0]*VWri[11][14][1])))+((rk[5][1]*
          Wpk[11][14][2])-(rk[5][2]*Wpk[11][14][1])));
        Vpk[11][14][1] = (((Cik[14][2][1]*VWri[11][14][2])+((Cik[14][0][1]*
          VWri[11][14][0])+(Cik[14][1][1]*VWri[11][14][1])))+((rk[5][2]*
          Wpk[11][14][0])-(rk[5][0]*Wpk[11][14][2])));
        Vpk[11][14][2] = (((Cik[14][2][2]*VWri[11][14][2])+((Cik[14][0][2]*
          VWri[11][14][0])+(Cik[14][1][2]*VWri[11][14][1])))+((rk[5][0]*
          Wpk[11][14][1])-(rk[5][1]*Wpk[11][14][0])));
        Vpk[12][12][0] = ((pin[12][2]*rk[3][1])-(pin[12][1]*rk[3][2]));
        Vpk[12][12][1] = ((pin[12][0]*rk[3][2])-(pin[12][2]*rk[3][0]));
        Vpk[12][12][2] = ((pin[12][1]*rk[3][0])-(pin[12][0]*rk[3][1]));
        VWri[12][13][0] = (Vpk[12][12][0]+((pin[12][1]*ri[4][2])-(pin[12][2]*
          ri[4][1])));
        VWri[12][13][1] = (Vpk[12][12][1]+((pin[12][2]*ri[4][0])-(pin[12][0]*
          ri[4][2])));
        VWri[12][13][2] = (Vpk[12][12][2]+((pin[12][0]*ri[4][1])-(pin[12][1]*
          ri[4][0])));
        Vpk[12][13][0] = (((Cik[13][2][0]*VWri[12][13][2])+((Cik[13][0][0]*
          VWri[12][13][0])+(Cik[13][1][0]*VWri[12][13][1])))+((rk[4][1]*
          Wpk[12][13][2])-(rk[4][2]*Wpk[12][13][1])));
        Vpk[12][13][1] = (((Cik[13][2][1]*VWri[12][13][2])+((Cik[13][0][1]*
          VWri[12][13][0])+(Cik[13][1][1]*VWri[12][13][1])))+((rk[4][2]*
          Wpk[12][13][0])-(rk[4][0]*Wpk[12][13][2])));
        Vpk[12][13][2] = (((Cik[13][2][2]*VWri[12][13][2])+((Cik[13][0][2]*
          VWri[12][13][0])+(Cik[13][1][2]*VWri[12][13][1])))+((rk[4][0]*
          Wpk[12][13][1])-(rk[4][1]*Wpk[12][13][0])));
        VWri[12][14][0] = (Vpk[12][13][0]+((ri[5][2]*Wpk[12][13][1])-(ri[5][1]*
          Wpk[12][13][2])));
        VWri[12][14][1] = (Vpk[12][13][1]+((ri[5][0]*Wpk[12][13][2])-(ri[5][2]*
          Wpk[12][13][0])));
        VWri[12][14][2] = (Vpk[12][13][2]+((ri[5][1]*Wpk[12][13][0])-(ri[5][0]*
          Wpk[12][13][1])));
        Vpk[12][14][0] = (((Cik[14][2][0]*VWri[12][14][2])+((Cik[14][0][0]*
          VWri[12][14][0])+(Cik[14][1][0]*VWri[12][14][1])))+((rk[5][1]*
          Wpk[12][14][2])-(rk[5][2]*Wpk[12][14][1])));
        Vpk[12][14][1] = (((Cik[14][2][1]*VWri[12][14][2])+((Cik[14][0][1]*
          VWri[12][14][0])+(Cik[14][1][1]*VWri[12][14][1])))+((rk[5][2]*
          Wpk[12][14][0])-(rk[5][0]*Wpk[12][14][2])));
        Vpk[12][14][2] = (((Cik[14][2][2]*VWri[12][14][2])+((Cik[14][0][2]*
          VWri[12][14][0])+(Cik[14][1][2]*VWri[12][14][1])))+((rk[5][0]*
          Wpk[12][14][1])-(rk[5][1]*Wpk[12][14][0])));
        Vpk[13][13][0] = ((pin[13][2]*rk[4][1])-(pin[13][1]*rk[4][2]));
        Vpk[13][13][1] = ((pin[13][0]*rk[4][2])-(pin[13][2]*rk[4][0]));
        Vpk[13][13][2] = ((pin[13][1]*rk[4][0])-(pin[13][0]*rk[4][1]));
        VWri[13][14][0] = (Vpk[13][13][0]+((pin[13][1]*ri[5][2])-(pin[13][2]*
          ri[5][1])));
        VWri[13][14][1] = (Vpk[13][13][1]+((pin[13][2]*ri[5][0])-(pin[13][0]*
          ri[5][2])));
        VWri[13][14][2] = (Vpk[13][13][2]+((pin[13][0]*ri[5][1])-(pin[13][1]*
          ri[5][0])));
        Vpk[13][14][0] = (((Cik[14][2][0]*VWri[13][14][2])+((Cik[14][0][0]*
          VWri[13][14][0])+(Cik[14][1][0]*VWri[13][14][1])))+((rk[5][1]*
          Wpk[13][14][2])-(rk[5][2]*Wpk[13][14][1])));
        Vpk[13][14][1] = (((Cik[14][2][1]*VWri[13][14][2])+((Cik[14][0][1]*
          VWri[13][14][0])+(Cik[14][1][1]*VWri[13][14][1])))+((rk[5][2]*
          Wpk[13][14][0])-(rk[5][0]*Wpk[13][14][2])));
        Vpk[13][14][2] = (((Cik[14][2][2]*VWri[13][14][2])+((Cik[14][0][2]*
          VWri[13][14][0])+(Cik[14][1][2]*VWri[13][14][1])))+((rk[5][0]*
          Wpk[13][14][1])-(rk[5][1]*Wpk[13][14][0])));
        Vpk[14][14][0] = ((pin[14][2]*rk[5][1])-(pin[14][1]*rk[5][2]));
        Vpk[14][14][1] = ((pin[14][0]*rk[5][2])-(pin[14][2]*rk[5][0]));
        Vpk[14][14][2] = ((pin[14][1]*rk[5][0])-(pin[14][0]*rk[5][1]));
        Vpk[15][17][0] = ((rk[6][1]*Wpk[15][17][2])-(rk[6][2]*Wpk[15][17][1]));
        Vpk[15][17][1] = ((rk[6][2]*Wpk[15][17][0])-(rk[6][0]*Wpk[15][17][2]));
        Vpk[15][17][2] = ((rk[6][0]*Wpk[15][17][1])-(rk[6][1]*Wpk[15][17][0]));
        VWri[15][18][0] = (Vpk[15][17][0]+((ri[7][2]*Wpk[15][17][1])-(ri[7][1]*
          Wpk[15][17][2])));
        VWri[15][18][1] = (Vpk[15][17][1]+((ri[7][0]*Wpk[15][17][2])-(ri[7][2]*
          Wpk[15][17][0])));
        VWri[15][18][2] = (Vpk[15][17][2]+((ri[7][1]*Wpk[15][17][0])-(ri[7][0]*
          Wpk[15][17][1])));
        Vpk[15][18][0] = (VWri[15][18][0]+((rpp[18][2]*Wpk[15][17][1])-(
          rpp[18][1]*Wpk[15][17][2])));
        Vpk[15][18][1] = (VWri[15][18][1]+((rpp[18][0]*Wpk[15][17][2])-(
          rpp[18][2]*Wpk[15][17][0])));
        Vpk[15][18][2] = (VWri[15][18][2]+((rpp[18][1]*Wpk[15][17][0])-(
          rpp[18][0]*Wpk[15][17][1])));
        Vpk[15][19][0] = (Vpk[15][18][0]+((rpp[19][2]*Wpk[15][17][1])-(
          rpp[19][1]*Wpk[15][17][2])));
        Vpk[15][19][1] = (Vpk[15][18][1]+((rpp[19][0]*Wpk[15][17][2])-(
          rpp[19][2]*Wpk[15][17][0])));
        Vpk[15][19][2] = (Vpk[15][18][2]+((rpp[19][1]*Wpk[15][17][0])-(
          rpp[19][0]*Wpk[15][17][1])));
        Vpk[15][20][0] = (((Cik[20][2][0]*Vpk[15][19][2])+((Cik[20][0][0]*
          Vpk[15][19][0])+(Cik[20][1][0]*Vpk[15][19][1])))+((rk[7][1]*
          Wpk[15][20][2])-(rk[7][2]*Wpk[15][20][1])));
        Vpk[15][20][1] = (((Cik[20][2][1]*Vpk[15][19][2])+((Cik[20][0][1]*
          Vpk[15][19][0])+(Cik[20][1][1]*Vpk[15][19][1])))+((rk[7][2]*
          Wpk[15][20][0])-(rk[7][0]*Wpk[15][20][2])));
        Vpk[15][20][2] = (((Cik[20][2][2]*Vpk[15][19][2])+((Cik[20][0][2]*
          Vpk[15][19][0])+(Cik[20][1][2]*Vpk[15][19][1])))+((rk[7][0]*
          Wpk[15][20][1])-(rk[7][1]*Wpk[15][20][0])));
        VWri[15][21][0] = (Vpk[15][20][0]+((ri[8][2]*Wpk[15][20][1])-(ri[8][1]*
          Wpk[15][20][2])));
        VWri[15][21][1] = (Vpk[15][20][1]+((ri[8][0]*Wpk[15][20][2])-(ri[8][2]*
          Wpk[15][20][0])));
        VWri[15][21][2] = (Vpk[15][20][2]+((ri[8][1]*Wpk[15][20][0])-(ri[8][0]*
          Wpk[15][20][1])));
        Vpk[15][21][0] = (((Cik[21][2][0]*VWri[15][21][2])+((Cik[21][0][0]*
          VWri[15][21][0])+(Cik[21][1][0]*VWri[15][21][1])))+((rk[8][1]*
          Wpk[15][21][2])-(rk[8][2]*Wpk[15][21][1])));
        Vpk[15][21][1] = (((Cik[21][2][1]*VWri[15][21][2])+((Cik[21][0][1]*
          VWri[15][21][0])+(Cik[21][1][1]*VWri[15][21][1])))+((rk[8][2]*
          Wpk[15][21][0])-(rk[8][0]*Wpk[15][21][2])));
        Vpk[15][21][2] = (((Cik[21][2][2]*VWri[15][21][2])+((Cik[21][0][2]*
          VWri[15][21][0])+(Cik[21][1][2]*VWri[15][21][1])))+((rk[8][0]*
          Wpk[15][21][1])-(rk[8][1]*Wpk[15][21][0])));
        VWri[15][22][0] = (Vpk[15][21][0]+((ri[9][2]*Wpk[15][21][1])-(ri[9][1]*
          Wpk[15][21][2])));
        VWri[15][22][1] = (Vpk[15][21][1]+((ri[9][0]*Wpk[15][21][2])-(ri[9][2]*
          Wpk[15][21][0])));
        VWri[15][22][2] = (Vpk[15][21][2]+((ri[9][1]*Wpk[15][21][0])-(ri[9][0]*
          Wpk[15][21][1])));
        Vpk[15][22][0] = (((Cik[22][2][0]*VWri[15][22][2])+((Cik[22][0][0]*
          VWri[15][22][0])+(Cik[22][1][0]*VWri[15][22][1])))+((rk[9][1]*
          Wpk[15][22][2])-(rk[9][2]*Wpk[15][22][1])));
        Vpk[15][22][1] = (((Cik[22][2][1]*VWri[15][22][2])+((Cik[22][0][1]*
          VWri[15][22][0])+(Cik[22][1][1]*VWri[15][22][1])))+((rk[9][2]*
          Wpk[15][22][0])-(rk[9][0]*Wpk[15][22][2])));
        Vpk[15][22][2] = (((Cik[22][2][2]*VWri[15][22][2])+((Cik[22][0][2]*
          VWri[15][22][0])+(Cik[22][1][2]*VWri[15][22][1])))+((rk[9][0]*
          Wpk[15][22][1])-(rk[9][1]*Wpk[15][22][0])));
        VWri[15][23][0] = (Vpk[15][22][0]+((ri[10][2]*Wpk[15][22][1])-(ri[10][1]
          *Wpk[15][22][2])));
        VWri[15][23][1] = (Vpk[15][22][1]+((ri[10][0]*Wpk[15][22][2])-(ri[10][2]
          *Wpk[15][22][0])));
        VWri[15][23][2] = (Vpk[15][22][2]+((ri[10][1]*Wpk[15][22][0])-(ri[10][0]
          *Wpk[15][22][1])));
        Vpk[15][23][0] = (((Cik[23][2][0]*VWri[15][23][2])+((Cik[23][0][0]*
          VWri[15][23][0])+(Cik[23][1][0]*VWri[15][23][1])))+((rk[10][1]*
          Wpk[15][23][2])-(rk[10][2]*Wpk[15][23][1])));
        Vpk[15][23][1] = (((Cik[23][2][1]*VWri[15][23][2])+((Cik[23][0][1]*
          VWri[15][23][0])+(Cik[23][1][1]*VWri[15][23][1])))+((rk[10][2]*
          Wpk[15][23][0])-(rk[10][0]*Wpk[15][23][2])));
        Vpk[15][23][2] = (((Cik[23][2][2]*VWri[15][23][2])+((Cik[23][0][2]*
          VWri[15][23][0])+(Cik[23][1][2]*VWri[15][23][1])))+((rk[10][0]*
          Wpk[15][23][1])-(rk[10][1]*Wpk[15][23][0])));
        Vpk[16][17][0] = ((rk[6][1]*Wpk[16][17][2])-(rk[6][2]*Wpk[16][17][1]));
        Vpk[16][17][1] = ((rk[6][2]*Wpk[16][17][0])-(rk[6][0]*Wpk[16][17][2]));
        Vpk[16][17][2] = ((rk[6][0]*Wpk[16][17][1])-(rk[6][1]*Wpk[16][17][0]));
        VWri[16][18][0] = (Vpk[16][17][0]+((ri[7][2]*Wpk[16][17][1])-(ri[7][1]*
          Wpk[16][17][2])));
        VWri[16][18][1] = (Vpk[16][17][1]+((ri[7][0]*Wpk[16][17][2])-(ri[7][2]*
          Wpk[16][17][0])));
        VWri[16][18][2] = (Vpk[16][17][2]+((ri[7][1]*Wpk[16][17][0])-(ri[7][0]*
          Wpk[16][17][1])));
        Vpk[16][18][0] = (VWri[16][18][0]+((rpp[18][2]*Wpk[16][17][1])-(
          rpp[18][1]*Wpk[16][17][2])));
        Vpk[16][18][1] = (VWri[16][18][1]+((rpp[18][0]*Wpk[16][17][2])-(
          rpp[18][2]*Wpk[16][17][0])));
        Vpk[16][18][2] = (VWri[16][18][2]+((rpp[18][1]*Wpk[16][17][0])-(
          rpp[18][0]*Wpk[16][17][1])));
        Vpk[16][19][0] = (Vpk[16][18][0]+((rpp[19][2]*Wpk[16][17][1])-(
          rpp[19][1]*Wpk[16][17][2])));
        Vpk[16][19][1] = (Vpk[16][18][1]+((rpp[19][0]*Wpk[16][17][2])-(
          rpp[19][2]*Wpk[16][17][0])));
        Vpk[16][19][2] = (Vpk[16][18][2]+((rpp[19][1]*Wpk[16][17][0])-(
          rpp[19][0]*Wpk[16][17][1])));
        Vpk[16][20][0] = (((Cik[20][2][0]*Vpk[16][19][2])+((Cik[20][0][0]*
          Vpk[16][19][0])+(Cik[20][1][0]*Vpk[16][19][1])))+((rk[7][1]*
          Wpk[16][20][2])-(rk[7][2]*Wpk[16][20][1])));
        Vpk[16][20][1] = (((Cik[20][2][1]*Vpk[16][19][2])+((Cik[20][0][1]*
          Vpk[16][19][0])+(Cik[20][1][1]*Vpk[16][19][1])))+((rk[7][2]*
          Wpk[16][20][0])-(rk[7][0]*Wpk[16][20][2])));
        Vpk[16][20][2] = (((Cik[20][2][2]*Vpk[16][19][2])+((Cik[20][0][2]*
          Vpk[16][19][0])+(Cik[20][1][2]*Vpk[16][19][1])))+((rk[7][0]*
          Wpk[16][20][1])-(rk[7][1]*Wpk[16][20][0])));
        VWri[16][21][0] = (Vpk[16][20][0]+((ri[8][2]*Wpk[16][20][1])-(ri[8][1]*
          Wpk[16][20][2])));
        VWri[16][21][1] = (Vpk[16][20][1]+((ri[8][0]*Wpk[16][20][2])-(ri[8][2]*
          Wpk[16][20][0])));
        VWri[16][21][2] = (Vpk[16][20][2]+((ri[8][1]*Wpk[16][20][0])-(ri[8][0]*
          Wpk[16][20][1])));
        Vpk[16][21][0] = (((Cik[21][2][0]*VWri[16][21][2])+((Cik[21][0][0]*
          VWri[16][21][0])+(Cik[21][1][0]*VWri[16][21][1])))+((rk[8][1]*
          Wpk[16][21][2])-(rk[8][2]*Wpk[16][21][1])));
        Vpk[16][21][1] = (((Cik[21][2][1]*VWri[16][21][2])+((Cik[21][0][1]*
          VWri[16][21][0])+(Cik[21][1][1]*VWri[16][21][1])))+((rk[8][2]*
          Wpk[16][21][0])-(rk[8][0]*Wpk[16][21][2])));
        Vpk[16][21][2] = (((Cik[21][2][2]*VWri[16][21][2])+((Cik[21][0][2]*
          VWri[16][21][0])+(Cik[21][1][2]*VWri[16][21][1])))+((rk[8][0]*
          Wpk[16][21][1])-(rk[8][1]*Wpk[16][21][0])));
        VWri[16][22][0] = (Vpk[16][21][0]+((ri[9][2]*Wpk[16][21][1])-(ri[9][1]*
          Wpk[16][21][2])));
        VWri[16][22][1] = (Vpk[16][21][1]+((ri[9][0]*Wpk[16][21][2])-(ri[9][2]*
          Wpk[16][21][0])));
        VWri[16][22][2] = (Vpk[16][21][2]+((ri[9][1]*Wpk[16][21][0])-(ri[9][0]*
          Wpk[16][21][1])));
        Vpk[16][22][0] = (((Cik[22][2][0]*VWri[16][22][2])+((Cik[22][0][0]*
          VWri[16][22][0])+(Cik[22][1][0]*VWri[16][22][1])))+((rk[9][1]*
          Wpk[16][22][2])-(rk[9][2]*Wpk[16][22][1])));
        Vpk[16][22][1] = (((Cik[22][2][1]*VWri[16][22][2])+((Cik[22][0][1]*
          VWri[16][22][0])+(Cik[22][1][1]*VWri[16][22][1])))+((rk[9][2]*
          Wpk[16][22][0])-(rk[9][0]*Wpk[16][22][2])));
        Vpk[16][22][2] = (((Cik[22][2][2]*VWri[16][22][2])+((Cik[22][0][2]*
          VWri[16][22][0])+(Cik[22][1][2]*VWri[16][22][1])))+((rk[9][0]*
          Wpk[16][22][1])-(rk[9][1]*Wpk[16][22][0])));
        VWri[16][23][0] = (Vpk[16][22][0]+((ri[10][2]*Wpk[16][22][1])-(ri[10][1]
          *Wpk[16][22][2])));
        VWri[16][23][1] = (Vpk[16][22][1]+((ri[10][0]*Wpk[16][22][2])-(ri[10][2]
          *Wpk[16][22][0])));
        VWri[16][23][2] = (Vpk[16][22][2]+((ri[10][1]*Wpk[16][22][0])-(ri[10][0]
          *Wpk[16][22][1])));
        Vpk[16][23][0] = (((Cik[23][2][0]*VWri[16][23][2])+((Cik[23][0][0]*
          VWri[16][23][0])+(Cik[23][1][0]*VWri[16][23][1])))+((rk[10][1]*
          Wpk[16][23][2])-(rk[10][2]*Wpk[16][23][1])));
        Vpk[16][23][1] = (((Cik[23][2][1]*VWri[16][23][2])+((Cik[23][0][1]*
          VWri[16][23][0])+(Cik[23][1][1]*VWri[16][23][1])))+((rk[10][2]*
          Wpk[16][23][0])-(rk[10][0]*Wpk[16][23][2])));
        Vpk[16][23][2] = (((Cik[23][2][2]*VWri[16][23][2])+((Cik[23][0][2]*
          VWri[16][23][0])+(Cik[23][1][2]*VWri[16][23][1])))+((rk[10][0]*
          Wpk[16][23][1])-(rk[10][1]*Wpk[16][23][0])));
        Vpk[17][17][0] = ((pin[17][2]*rk[6][1])-(pin[17][1]*rk[6][2]));
        Vpk[17][17][1] = ((pin[17][0]*rk[6][2])-(pin[17][2]*rk[6][0]));
        Vpk[17][17][2] = ((pin[17][1]*rk[6][0])-(pin[17][0]*rk[6][1]));
        VWri[17][18][0] = (Vpk[17][17][0]+((pin[17][1]*ri[7][2])-(pin[17][2]*
          ri[7][1])));
        VWri[17][18][1] = (Vpk[17][17][1]+((pin[17][2]*ri[7][0])-(pin[17][0]*
          ri[7][2])));
        VWri[17][18][2] = (Vpk[17][17][2]+((pin[17][0]*ri[7][1])-(pin[17][1]*
          ri[7][0])));
        Vpk[17][18][0] = (VWri[17][18][0]+((pin[17][1]*rpp[18][2])-(pin[17][2]*
          rpp[18][1])));
        Vpk[17][18][1] = (VWri[17][18][1]+((pin[17][2]*rpp[18][0])-(pin[17][0]*
          rpp[18][2])));
        Vpk[17][18][2] = (VWri[17][18][2]+((pin[17][0]*rpp[18][1])-(pin[17][1]*
          rpp[18][0])));
        Vpk[17][19][0] = (Vpk[17][18][0]+((pin[17][1]*rpp[19][2])-(pin[17][2]*
          rpp[19][1])));
        Vpk[17][19][1] = (Vpk[17][18][1]+((pin[17][2]*rpp[19][0])-(pin[17][0]*
          rpp[19][2])));
        Vpk[17][19][2] = (Vpk[17][18][2]+((pin[17][0]*rpp[19][1])-(pin[17][1]*
          rpp[19][0])));
        Vpk[17][20][0] = (((Cik[20][2][0]*Vpk[17][19][2])+((Cik[20][0][0]*
          Vpk[17][19][0])+(Cik[20][1][0]*Vpk[17][19][1])))+((rk[7][1]*
          Wpk[17][20][2])-(rk[7][2]*Wpk[17][20][1])));
        Vpk[17][20][1] = (((Cik[20][2][1]*Vpk[17][19][2])+((Cik[20][0][1]*
          Vpk[17][19][0])+(Cik[20][1][1]*Vpk[17][19][1])))+((rk[7][2]*
          Wpk[17][20][0])-(rk[7][0]*Wpk[17][20][2])));
        Vpk[17][20][2] = (((Cik[20][2][2]*Vpk[17][19][2])+((Cik[20][0][2]*
          Vpk[17][19][0])+(Cik[20][1][2]*Vpk[17][19][1])))+((rk[7][0]*
          Wpk[17][20][1])-(rk[7][1]*Wpk[17][20][0])));
        VWri[17][21][0] = (Vpk[17][20][0]+((ri[8][2]*Wpk[17][20][1])-(ri[8][1]*
          Wpk[17][20][2])));
        VWri[17][21][1] = (Vpk[17][20][1]+((ri[8][0]*Wpk[17][20][2])-(ri[8][2]*
          Wpk[17][20][0])));
        VWri[17][21][2] = (Vpk[17][20][2]+((ri[8][1]*Wpk[17][20][0])-(ri[8][0]*
          Wpk[17][20][1])));
        Vpk[17][21][0] = (((Cik[21][2][0]*VWri[17][21][2])+((Cik[21][0][0]*
          VWri[17][21][0])+(Cik[21][1][0]*VWri[17][21][1])))+((rk[8][1]*
          Wpk[17][21][2])-(rk[8][2]*Wpk[17][21][1])));
        Vpk[17][21][1] = (((Cik[21][2][1]*VWri[17][21][2])+((Cik[21][0][1]*
          VWri[17][21][0])+(Cik[21][1][1]*VWri[17][21][1])))+((rk[8][2]*
          Wpk[17][21][0])-(rk[8][0]*Wpk[17][21][2])));
        Vpk[17][21][2] = (((Cik[21][2][2]*VWri[17][21][2])+((Cik[21][0][2]*
          VWri[17][21][0])+(Cik[21][1][2]*VWri[17][21][1])))+((rk[8][0]*
          Wpk[17][21][1])-(rk[8][1]*Wpk[17][21][0])));
        VWri[17][22][0] = (Vpk[17][21][0]+((ri[9][2]*Wpk[17][21][1])-(ri[9][1]*
          Wpk[17][21][2])));
        VWri[17][22][1] = (Vpk[17][21][1]+((ri[9][0]*Wpk[17][21][2])-(ri[9][2]*
          Wpk[17][21][0])));
        VWri[17][22][2] = (Vpk[17][21][2]+((ri[9][1]*Wpk[17][21][0])-(ri[9][0]*
          Wpk[17][21][1])));
        Vpk[17][22][0] = (((Cik[22][2][0]*VWri[17][22][2])+((Cik[22][0][0]*
          VWri[17][22][0])+(Cik[22][1][0]*VWri[17][22][1])))+((rk[9][1]*
          Wpk[17][22][2])-(rk[9][2]*Wpk[17][22][1])));
        Vpk[17][22][1] = (((Cik[22][2][1]*VWri[17][22][2])+((Cik[22][0][1]*
          VWri[17][22][0])+(Cik[22][1][1]*VWri[17][22][1])))+((rk[9][2]*
          Wpk[17][22][0])-(rk[9][0]*Wpk[17][22][2])));
        Vpk[17][22][2] = (((Cik[22][2][2]*VWri[17][22][2])+((Cik[22][0][2]*
          VWri[17][22][0])+(Cik[22][1][2]*VWri[17][22][1])))+((rk[9][0]*
          Wpk[17][22][1])-(rk[9][1]*Wpk[17][22][0])));
        VWri[17][23][0] = (Vpk[17][22][0]+((ri[10][2]*Wpk[17][22][1])-(ri[10][1]
          *Wpk[17][22][2])));
        VWri[17][23][1] = (Vpk[17][22][1]+((ri[10][0]*Wpk[17][22][2])-(ri[10][2]
          *Wpk[17][22][0])));
        VWri[17][23][2] = (Vpk[17][22][2]+((ri[10][1]*Wpk[17][22][0])-(ri[10][0]
          *Wpk[17][22][1])));
        Vpk[17][23][0] = (((Cik[23][2][0]*VWri[17][23][2])+((Cik[23][0][0]*
          VWri[17][23][0])+(Cik[23][1][0]*VWri[17][23][1])))+((rk[10][1]*
          Wpk[17][23][2])-(rk[10][2]*Wpk[17][23][1])));
        Vpk[17][23][1] = (((Cik[23][2][1]*VWri[17][23][2])+((Cik[23][0][1]*
          VWri[17][23][0])+(Cik[23][1][1]*VWri[17][23][1])))+((rk[10][2]*
          Wpk[17][23][0])-(rk[10][0]*Wpk[17][23][2])));
        Vpk[17][23][2] = (((Cik[23][2][2]*VWri[17][23][2])+((Cik[23][0][2]*
          VWri[17][23][0])+(Cik[23][1][2]*VWri[17][23][1])))+((rk[10][0]*
          Wpk[17][23][1])-(rk[10][1]*Wpk[17][23][0])));
        Vpk[18][18][0] = pin[18][0];
        Vpk[18][18][1] = pin[18][1];
        Vpk[18][18][2] = pin[18][2];
        Vpk[18][19][0] = pin[18][0];
        Vpk[18][19][1] = pin[18][1];
        Vpk[18][19][2] = pin[18][2];
        Vpk[18][20][0] = ((Cik[20][2][0]*pin[18][2])+((Cik[20][0][0]*pin[18][0])
          +(Cik[20][1][0]*pin[18][1])));
        Vpk[18][20][1] = ((Cik[20][2][1]*pin[18][2])+((Cik[20][0][1]*pin[18][0])
          +(Cik[20][1][1]*pin[18][1])));
        Vpk[18][20][2] = ((Cik[20][2][2]*pin[18][2])+((Cik[20][0][2]*pin[18][0])
          +(Cik[20][1][2]*pin[18][1])));
        Vpk[18][21][0] = ((Cik[21][2][0]*Vpk[18][20][2])+((Cik[21][0][0]*
          Vpk[18][20][0])+(Cik[21][1][0]*Vpk[18][20][1])));
        Vpk[18][21][1] = ((Cik[21][2][1]*Vpk[18][20][2])+((Cik[21][0][1]*
          Vpk[18][20][0])+(Cik[21][1][1]*Vpk[18][20][1])));
        Vpk[18][21][2] = ((Cik[21][2][2]*Vpk[18][20][2])+((Cik[21][0][2]*
          Vpk[18][20][0])+(Cik[21][1][2]*Vpk[18][20][1])));
        Vpk[18][22][0] = ((Cik[22][2][0]*Vpk[18][21][2])+((Cik[22][0][0]*
          Vpk[18][21][0])+(Cik[22][1][0]*Vpk[18][21][1])));
        Vpk[18][22][1] = ((Cik[22][2][1]*Vpk[18][21][2])+((Cik[22][0][1]*
          Vpk[18][21][0])+(Cik[22][1][1]*Vpk[18][21][1])));
        Vpk[18][22][2] = ((Cik[22][2][2]*Vpk[18][21][2])+((Cik[22][0][2]*
          Vpk[18][21][0])+(Cik[22][1][2]*Vpk[18][21][1])));
        Vpk[18][23][0] = ((Cik[23][2][0]*Vpk[18][22][2])+((Cik[23][0][0]*
          Vpk[18][22][0])+(Cik[23][1][0]*Vpk[18][22][1])));
        Vpk[18][23][1] = ((Cik[23][2][1]*Vpk[18][22][2])+((Cik[23][0][1]*
          Vpk[18][22][0])+(Cik[23][1][1]*Vpk[18][22][1])));
        Vpk[18][23][2] = ((Cik[23][2][2]*Vpk[18][22][2])+((Cik[23][0][2]*
          Vpk[18][22][0])+(Cik[23][1][2]*Vpk[18][22][1])));
        Vpk[19][19][0] = pin[19][0];
        Vpk[19][19][1] = pin[19][1];
        Vpk[19][19][2] = pin[19][2];
        Vpk[19][20][0] = ((Cik[20][2][0]*pin[19][2])+((Cik[20][0][0]*pin[19][0])
          +(Cik[20][1][0]*pin[19][1])));
        Vpk[19][20][1] = ((Cik[20][2][1]*pin[19][2])+((Cik[20][0][1]*pin[19][0])
          +(Cik[20][1][1]*pin[19][1])));
        Vpk[19][20][2] = ((Cik[20][2][2]*pin[19][2])+((Cik[20][0][2]*pin[19][0])
          +(Cik[20][1][2]*pin[19][1])));
        Vpk[19][21][0] = ((Cik[21][2][0]*Vpk[19][20][2])+((Cik[21][0][0]*
          Vpk[19][20][0])+(Cik[21][1][0]*Vpk[19][20][1])));
        Vpk[19][21][1] = ((Cik[21][2][1]*Vpk[19][20][2])+((Cik[21][0][1]*
          Vpk[19][20][0])+(Cik[21][1][1]*Vpk[19][20][1])));
        Vpk[19][21][2] = ((Cik[21][2][2]*Vpk[19][20][2])+((Cik[21][0][2]*
          Vpk[19][20][0])+(Cik[21][1][2]*Vpk[19][20][1])));
        Vpk[19][22][0] = ((Cik[22][2][0]*Vpk[19][21][2])+((Cik[22][0][0]*
          Vpk[19][21][0])+(Cik[22][1][0]*Vpk[19][21][1])));
        Vpk[19][22][1] = ((Cik[22][2][1]*Vpk[19][21][2])+((Cik[22][0][1]*
          Vpk[19][21][0])+(Cik[22][1][1]*Vpk[19][21][1])));
        Vpk[19][22][2] = ((Cik[22][2][2]*Vpk[19][21][2])+((Cik[22][0][2]*
          Vpk[19][21][0])+(Cik[22][1][2]*Vpk[19][21][1])));
        Vpk[19][23][0] = ((Cik[23][2][0]*Vpk[19][22][2])+((Cik[23][0][0]*
          Vpk[19][22][0])+(Cik[23][1][0]*Vpk[19][22][1])));
        Vpk[19][23][1] = ((Cik[23][2][1]*Vpk[19][22][2])+((Cik[23][0][1]*
          Vpk[19][22][0])+(Cik[23][1][1]*Vpk[19][22][1])));
        Vpk[19][23][2] = ((Cik[23][2][2]*Vpk[19][22][2])+((Cik[23][0][2]*
          Vpk[19][22][0])+(Cik[23][1][2]*Vpk[19][22][1])));
        Vpk[20][20][0] = ((pin[20][2]*rk[7][1])-(pin[20][1]*rk[7][2]));
        Vpk[20][20][1] = ((pin[20][0]*rk[7][2])-(pin[20][2]*rk[7][0]));
        Vpk[20][20][2] = ((pin[20][1]*rk[7][0])-(pin[20][0]*rk[7][1]));
        VWri[20][21][0] = (Vpk[20][20][0]+((pin[20][1]*ri[8][2])-(pin[20][2]*
          ri[8][1])));
        VWri[20][21][1] = (Vpk[20][20][1]+((pin[20][2]*ri[8][0])-(pin[20][0]*
          ri[8][2])));
        VWri[20][21][2] = (Vpk[20][20][2]+((pin[20][0]*ri[8][1])-(pin[20][1]*
          ri[8][0])));
        Vpk[20][21][0] = (((Cik[21][2][0]*VWri[20][21][2])+((Cik[21][0][0]*
          VWri[20][21][0])+(Cik[21][1][0]*VWri[20][21][1])))+((rk[8][1]*
          Wpk[20][21][2])-(rk[8][2]*Wpk[20][21][1])));
        Vpk[20][21][1] = (((Cik[21][2][1]*VWri[20][21][2])+((Cik[21][0][1]*
          VWri[20][21][0])+(Cik[21][1][1]*VWri[20][21][1])))+((rk[8][2]*
          Wpk[20][21][0])-(rk[8][0]*Wpk[20][21][2])));
        Vpk[20][21][2] = (((Cik[21][2][2]*VWri[20][21][2])+((Cik[21][0][2]*
          VWri[20][21][0])+(Cik[21][1][2]*VWri[20][21][1])))+((rk[8][0]*
          Wpk[20][21][1])-(rk[8][1]*Wpk[20][21][0])));
        VWri[20][22][0] = (Vpk[20][21][0]+((ri[9][2]*Wpk[20][21][1])-(ri[9][1]*
          Wpk[20][21][2])));
        VWri[20][22][1] = (Vpk[20][21][1]+((ri[9][0]*Wpk[20][21][2])-(ri[9][2]*
          Wpk[20][21][0])));
        VWri[20][22][2] = (Vpk[20][21][2]+((ri[9][1]*Wpk[20][21][0])-(ri[9][0]*
          Wpk[20][21][1])));
        Vpk[20][22][0] = (((Cik[22][2][0]*VWri[20][22][2])+((Cik[22][0][0]*
          VWri[20][22][0])+(Cik[22][1][0]*VWri[20][22][1])))+((rk[9][1]*
          Wpk[20][22][2])-(rk[9][2]*Wpk[20][22][1])));
        Vpk[20][22][1] = (((Cik[22][2][1]*VWri[20][22][2])+((Cik[22][0][1]*
          VWri[20][22][0])+(Cik[22][1][1]*VWri[20][22][1])))+((rk[9][2]*
          Wpk[20][22][0])-(rk[9][0]*Wpk[20][22][2])));
        Vpk[20][22][2] = (((Cik[22][2][2]*VWri[20][22][2])+((Cik[22][0][2]*
          VWri[20][22][0])+(Cik[22][1][2]*VWri[20][22][1])))+((rk[9][0]*
          Wpk[20][22][1])-(rk[9][1]*Wpk[20][22][0])));
        VWri[20][23][0] = (Vpk[20][22][0]+((ri[10][2]*Wpk[20][22][1])-(ri[10][1]
          *Wpk[20][22][2])));
        VWri[20][23][1] = (Vpk[20][22][1]+((ri[10][0]*Wpk[20][22][2])-(ri[10][2]
          *Wpk[20][22][0])));
        VWri[20][23][2] = (Vpk[20][22][2]+((ri[10][1]*Wpk[20][22][0])-(ri[10][0]
          *Wpk[20][22][1])));
        Vpk[20][23][0] = (((Cik[23][2][0]*VWri[20][23][2])+((Cik[23][0][0]*
          VWri[20][23][0])+(Cik[23][1][0]*VWri[20][23][1])))+((rk[10][1]*
          Wpk[20][23][2])-(rk[10][2]*Wpk[20][23][1])));
        Vpk[20][23][1] = (((Cik[23][2][1]*VWri[20][23][2])+((Cik[23][0][1]*
          VWri[20][23][0])+(Cik[23][1][1]*VWri[20][23][1])))+((rk[10][2]*
          Wpk[20][23][0])-(rk[10][0]*Wpk[20][23][2])));
        Vpk[20][23][2] = (((Cik[23][2][2]*VWri[20][23][2])+((Cik[23][0][2]*
          VWri[20][23][0])+(Cik[23][1][2]*VWri[20][23][1])))+((rk[10][0]*
          Wpk[20][23][1])-(rk[10][1]*Wpk[20][23][0])));
        Vpk[21][21][0] = ((pin[21][2]*rk[8][1])-(pin[21][1]*rk[8][2]));
        Vpk[21][21][1] = ((pin[21][0]*rk[8][2])-(pin[21][2]*rk[8][0]));
        Vpk[21][21][2] = ((pin[21][1]*rk[8][0])-(pin[21][0]*rk[8][1]));
        VWri[21][22][0] = (Vpk[21][21][0]+((pin[21][1]*ri[9][2])-(pin[21][2]*
          ri[9][1])));
        VWri[21][22][1] = (Vpk[21][21][1]+((pin[21][2]*ri[9][0])-(pin[21][0]*
          ri[9][2])));
        VWri[21][22][2] = (Vpk[21][21][2]+((pin[21][0]*ri[9][1])-(pin[21][1]*
          ri[9][0])));
        Vpk[21][22][0] = (((Cik[22][2][0]*VWri[21][22][2])+((Cik[22][0][0]*
          VWri[21][22][0])+(Cik[22][1][0]*VWri[21][22][1])))+((rk[9][1]*
          Wpk[21][22][2])-(rk[9][2]*Wpk[21][22][1])));
        Vpk[21][22][1] = (((Cik[22][2][1]*VWri[21][22][2])+((Cik[22][0][1]*
          VWri[21][22][0])+(Cik[22][1][1]*VWri[21][22][1])))+((rk[9][2]*
          Wpk[21][22][0])-(rk[9][0]*Wpk[21][22][2])));
        Vpk[21][22][2] = (((Cik[22][2][2]*VWri[21][22][2])+((Cik[22][0][2]*
          VWri[21][22][0])+(Cik[22][1][2]*VWri[21][22][1])))+((rk[9][0]*
          Wpk[21][22][1])-(rk[9][1]*Wpk[21][22][0])));
        VWri[21][23][0] = (Vpk[21][22][0]+((ri[10][2]*Wpk[21][22][1])-(ri[10][1]
          *Wpk[21][22][2])));
        VWri[21][23][1] = (Vpk[21][22][1]+((ri[10][0]*Wpk[21][22][2])-(ri[10][2]
          *Wpk[21][22][0])));
        VWri[21][23][2] = (Vpk[21][22][2]+((ri[10][1]*Wpk[21][22][0])-(ri[10][0]
          *Wpk[21][22][1])));
        Vpk[21][23][0] = (((Cik[23][2][0]*VWri[21][23][2])+((Cik[23][0][0]*
          VWri[21][23][0])+(Cik[23][1][0]*VWri[21][23][1])))+((rk[10][1]*
          Wpk[21][23][2])-(rk[10][2]*Wpk[21][23][1])));
        Vpk[21][23][1] = (((Cik[23][2][1]*VWri[21][23][2])+((Cik[23][0][1]*
          VWri[21][23][0])+(Cik[23][1][1]*VWri[21][23][1])))+((rk[10][2]*
          Wpk[21][23][0])-(rk[10][0]*Wpk[21][23][2])));
        Vpk[21][23][2] = (((Cik[23][2][2]*VWri[21][23][2])+((Cik[23][0][2]*
          VWri[21][23][0])+(Cik[23][1][2]*VWri[21][23][1])))+((rk[10][0]*
          Wpk[21][23][1])-(rk[10][1]*Wpk[21][23][0])));
        Vpk[22][22][0] = ((pin[22][2]*rk[9][1])-(pin[22][1]*rk[9][2]));
        Vpk[22][22][1] = ((pin[22][0]*rk[9][2])-(pin[22][2]*rk[9][0]));
        Vpk[22][22][2] = ((pin[22][1]*rk[9][0])-(pin[22][0]*rk[9][1]));
        VWri[22][23][0] = (Vpk[22][22][0]+((pin[22][1]*ri[10][2])-(pin[22][2]*
          ri[10][1])));
        VWri[22][23][1] = (Vpk[22][22][1]+((pin[22][2]*ri[10][0])-(pin[22][0]*
          ri[10][2])));
        VWri[22][23][2] = (Vpk[22][22][2]+((pin[22][0]*ri[10][1])-(pin[22][1]*
          ri[10][0])));
        Vpk[22][23][0] = (((Cik[23][2][0]*VWri[22][23][2])+((Cik[23][0][0]*
          VWri[22][23][0])+(Cik[23][1][0]*VWri[22][23][1])))+((rk[10][1]*
          Wpk[22][23][2])-(rk[10][2]*Wpk[22][23][1])));
        Vpk[22][23][1] = (((Cik[23][2][1]*VWri[22][23][2])+((Cik[23][0][1]*
          VWri[22][23][0])+(Cik[23][1][1]*VWri[22][23][1])))+((rk[10][2]*
          Wpk[22][23][0])-(rk[10][0]*Wpk[22][23][2])));
        Vpk[22][23][2] = (((Cik[23][2][2]*VWri[22][23][2])+((Cik[23][0][2]*
          VWri[22][23][0])+(Cik[23][1][2]*VWri[22][23][1])))+((rk[10][0]*
          Wpk[22][23][1])-(rk[10][1]*Wpk[22][23][0])));
        Vpk[23][23][0] = ((pin[23][2]*rk[10][1])-(pin[23][1]*rk[10][2]));
        Vpk[23][23][1] = ((pin[23][0]*rk[10][2])-(pin[23][2]*rk[10][0]));
        Vpk[23][23][2] = ((pin[23][1]*rk[10][0])-(pin[23][0]*rk[10][1]));
        Vpk[24][26][0] = ((rk[11][1]*Wpk[24][26][2])-(rk[11][2]*Wpk[24][26][1]))
          ;
        Vpk[24][26][1] = ((rk[11][2]*Wpk[24][26][0])-(rk[11][0]*Wpk[24][26][2]))
          ;
        Vpk[24][26][2] = ((rk[11][0]*Wpk[24][26][1])-(rk[11][1]*Wpk[24][26][0]))
          ;
        Vpk[25][26][0] = ((rk[11][1]*Wpk[25][26][2])-(rk[11][2]*Wpk[25][26][1]))
          ;
        Vpk[25][26][1] = ((rk[11][2]*Wpk[25][26][0])-(rk[11][0]*Wpk[25][26][2]))
          ;
        Vpk[25][26][2] = ((rk[11][0]*Wpk[25][26][1])-(rk[11][1]*Wpk[25][26][0]))
          ;
        Vpk[26][26][0] = ((pin[26][2]*rk[11][1])-(pin[26][1]*rk[11][2]));
        Vpk[26][26][1] = ((pin[26][0]*rk[11][2])-(pin[26][2]*rk[11][0]));
        Vpk[26][26][2] = ((pin[26][1]*rk[11][0])-(pin[26][0]*rk[11][1]));
        vpkflg = 1;
    }
/*
 Used 0.92 seconds CPU time,
 139264 additional bytes of memory.
 Equations contain 2604 adds/subtracts/negates
                   3450 multiplies
                      0 divides
                   1329 assignments
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
        Otk[4][0] = ((Wik[4][2]*wk[4][1])-(Wik[4][1]*wk[4][2]));
        Otk[4][1] = ((Wik[4][0]*wk[4][2])-(Wik[4][2]*wk[4][0]));
        Otk[4][2] = ((Wik[4][1]*wk[4][0])-(Wik[4][0]*wk[4][1]));
        Otk[5][0] = (((Cik[5][2][0]*Otk[4][2])+((Cik[5][0][0]*Otk[4][0])+(
          Cik[5][1][0]*Otk[4][1])))+((Wik[5][2]*wk[5][1])-(Wik[5][1]*wk[5][2])))
          ;
        Otk[5][1] = (((Cik[5][2][1]*Otk[4][2])+((Cik[5][0][1]*Otk[4][0])+(
          Cik[5][1][1]*Otk[4][1])))+((Wik[5][0]*wk[5][2])-(Wik[5][2]*wk[5][0])))
          ;
        Otk[5][2] = (((Cik[5][2][2]*Otk[4][2])+((Cik[5][0][2]*Otk[4][0])+(
          Cik[5][1][2]*Otk[4][1])))+((Wik[5][1]*wk[5][0])-(Wik[5][0]*wk[5][1])))
          ;
        Otk[6][0] = (((Cik[6][2][0]*Otk[5][2])+((Cik[6][0][0]*Otk[5][0])+(
          Cik[6][1][0]*Otk[5][1])))+((Wik[6][2]*wk[6][1])-(Wik[6][1]*wk[6][2])))
          ;
        Otk[6][1] = (((Cik[6][2][1]*Otk[5][2])+((Cik[6][0][1]*Otk[5][0])+(
          Cik[6][1][1]*Otk[5][1])))+((Wik[6][0]*wk[6][2])-(Wik[6][2]*wk[6][0])))
          ;
        Otk[6][2] = (((Cik[6][2][2]*Otk[5][2])+((Cik[6][0][2]*Otk[5][0])+(
          Cik[6][1][2]*Otk[5][1])))+((Wik[6][1]*wk[6][0])-(Wik[6][0]*wk[6][1])))
          ;
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
        Otk[11][0] = (((Cik[11][2][0]*Otk[8][2])+((Cik[11][0][0]*Otk[8][0])+(
          Cik[11][1][0]*Otk[8][1])))+((Wik[11][2]*wk[11][1])-(Wik[11][1]*
          wk[11][2])));
        Otk[11][1] = (((Cik[11][2][1]*Otk[8][2])+((Cik[11][0][1]*Otk[8][0])+(
          Cik[11][1][1]*Otk[8][1])))+((Wik[11][0]*wk[11][2])-(Wik[11][2]*
          wk[11][0])));
        Otk[11][2] = (((Cik[11][2][2]*Otk[8][2])+((Cik[11][0][2]*Otk[8][0])+(
          Cik[11][1][2]*Otk[8][1])))+((Wik[11][1]*wk[11][0])-(Wik[11][0]*
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
        Otk[15][0] = (((Cik[15][2][0]*Otk[5][2])+((Cik[15][0][0]*Otk[5][0])+(
          Cik[15][1][0]*Otk[5][1])))+((Wik[15][2]*wk[15][1])-(Wik[15][1]*
          wk[15][2])));
        Otk[15][1] = (((Cik[15][2][1]*Otk[5][2])+((Cik[15][0][1]*Otk[5][0])+(
          Cik[15][1][1]*Otk[5][1])))+((Wik[15][0]*wk[15][2])-(Wik[15][2]*
          wk[15][0])));
        Otk[15][2] = (((Cik[15][2][2]*Otk[5][2])+((Cik[15][0][2]*Otk[5][0])+(
          Cik[15][1][2]*Otk[5][1])))+((Wik[15][1]*wk[15][0])-(Wik[15][0]*
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
        Otk[20][0] = (((Cik[20][2][0]*Otk[17][2])+((Cik[20][0][0]*Otk[17][0])+(
          Cik[20][1][0]*Otk[17][1])))+((Wik[20][2]*wk[20][1])-(Wik[20][1]*
          wk[20][2])));
        Otk[20][1] = (((Cik[20][2][1]*Otk[17][2])+((Cik[20][0][1]*Otk[17][0])+(
          Cik[20][1][1]*Otk[17][1])))+((Wik[20][0]*wk[20][2])-(Wik[20][2]*
          wk[20][0])));
        Otk[20][2] = (((Cik[20][2][2]*Otk[17][2])+((Cik[20][0][2]*Otk[17][0])+(
          Cik[20][1][2]*Otk[17][1])))+((Wik[20][1]*wk[20][0])-(Wik[20][0]*
          wk[20][1])));
        Otk[21][0] = (((Cik[21][2][0]*Otk[20][2])+((Cik[21][0][0]*Otk[20][0])+(
          Cik[21][1][0]*Otk[20][1])))+((Wik[21][2]*wk[21][1])-(Wik[21][1]*
          wk[21][2])));
        Otk[21][1] = (((Cik[21][2][1]*Otk[20][2])+((Cik[21][0][1]*Otk[20][0])+(
          Cik[21][1][1]*Otk[20][1])))+((Wik[21][0]*wk[21][2])-(Wik[21][2]*
          wk[21][0])));
        Otk[21][2] = (((Cik[21][2][2]*Otk[20][2])+((Cik[21][0][2]*Otk[20][0])+(
          Cik[21][1][2]*Otk[20][1])))+((Wik[21][1]*wk[21][0])-(Wik[21][0]*
          wk[21][1])));
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
        Otk[24][0] = (((Cik[24][2][0]*Otk[5][2])+((Cik[24][0][0]*Otk[5][0])+(
          Cik[24][1][0]*Otk[5][1])))+((Wik[24][2]*wk[24][1])-(Wik[24][1]*
          wk[24][2])));
        Otk[24][1] = (((Cik[24][2][1]*Otk[5][2])+((Cik[24][0][1]*Otk[5][0])+(
          Cik[24][1][1]*Otk[5][1])))+((Wik[24][0]*wk[24][2])-(Wik[24][2]*
          wk[24][0])));
        Otk[24][2] = (((Cik[24][2][2]*Otk[5][2])+((Cik[24][0][2]*Otk[5][0])+(
          Cik[24][1][2]*Otk[5][1])))+((Wik[24][1]*wk[24][0])-(Wik[24][0]*
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
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[5][0] = (((Otk[5][2]*rk[0][1])-(Otk[5][1]*rk[0][2]))+((wk[5][1]*
          Wkrpk[5][2])-(wk[5][2]*Wkrpk[5][1])));
        Atk[5][1] = (((Otk[5][0]*rk[0][2])-(Otk[5][2]*rk[0][0]))+((wk[5][2]*
          Wkrpk[5][0])-(wk[5][0]*Wkrpk[5][2])));
        Atk[5][2] = (((Otk[5][1]*rk[0][0])-(Otk[5][0]*rk[0][1]))+((wk[5][0]*
          Wkrpk[5][1])-(wk[5][1]*Wkrpk[5][0])));
        AiOiWi[6][0] = (Atk[5][0]+(((Otk[5][1]*ri[1][2])-(Otk[5][2]*ri[1][1]))+(
          (Wirk[6][2]*wk[5][1])-(Wirk[6][1]*wk[5][2]))));
        AiOiWi[6][1] = (Atk[5][1]+(((Otk[5][2]*ri[1][0])-(Otk[5][0]*ri[1][2]))+(
          (Wirk[6][0]*wk[5][2])-(Wirk[6][2]*wk[5][0]))));
        AiOiWi[6][2] = (Atk[5][2]+(((Otk[5][0]*ri[1][1])-(Otk[5][1]*ri[1][0]))+(
          (Wirk[6][1]*wk[5][0])-(Wirk[6][0]*wk[5][1]))));
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
        Atk[8][0] = (((Atk[7][2]*Cik[8][2][0])+((Atk[7][0]*Cik[8][0][0])+(
          Atk[7][1]*Cik[8][1][0])))+(((Otk[8][2]*rk[1][1])-(Otk[8][1]*rk[1][2]))
          +((wk[8][1]*Wkrpk[8][2])-(wk[8][2]*Wkrpk[8][1]))));
        Atk[8][1] = (((Atk[7][2]*Cik[8][2][1])+((Atk[7][0]*Cik[8][0][1])+(
          Atk[7][1]*Cik[8][1][1])))+(((Otk[8][0]*rk[1][2])-(Otk[8][2]*rk[1][0]))
          +((wk[8][2]*Wkrpk[8][0])-(wk[8][0]*Wkrpk[8][2]))));
        Atk[8][2] = (((Atk[7][2]*Cik[8][2][2])+((Atk[7][0]*Cik[8][0][2])+(
          Atk[7][1]*Cik[8][1][2])))+(((Otk[8][1]*rk[1][0])-(Otk[8][0]*rk[1][1]))
          +((wk[8][0]*Wkrpk[8][1])-(wk[8][1]*Wkrpk[8][0]))));
        AiOiWi[9][0] = (Atk[8][0]+(((Otk[8][1]*ri[2][2])-(Otk[8][2]*ri[2][1]))+(
          (Wirk[9][2]*wk[8][1])-(Wirk[9][1]*wk[8][2]))));
        AiOiWi[9][1] = (Atk[8][1]+(((Otk[8][2]*ri[2][0])-(Otk[8][0]*ri[2][2]))+(
          (Wirk[9][0]*wk[8][2])-(Wirk[9][2]*wk[8][0]))));
        AiOiWi[9][2] = (Atk[8][2]+(((Otk[8][0]*ri[2][1])-(Otk[8][1]*ri[2][0]))+(
          (Wirk[9][1]*wk[8][0])-(Wirk[9][0]*wk[8][1]))));
        Atk[9][0] = (AiOiWi[9][0]+((2.*((Vik[9][2]*wk[8][1])-(Vik[9][1]*wk[8][2]
          )))+(((Otk[8][1]*rpp[9][2])-(Otk[8][2]*rpp[9][1]))+((wk[8][1]*
          Wkrpk[9][2])-(wk[8][2]*Wkrpk[9][1])))));
        Atk[9][1] = (AiOiWi[9][1]+((2.*((Vik[9][0]*wk[8][2])-(Vik[9][2]*wk[8][0]
          )))+(((Otk[8][2]*rpp[9][0])-(Otk[8][0]*rpp[9][2]))+((wk[8][2]*
          Wkrpk[9][0])-(wk[8][0]*Wkrpk[9][2])))));
        Atk[9][2] = (AiOiWi[9][2]+((2.*((Vik[9][1]*wk[8][0])-(Vik[9][0]*wk[8][1]
          )))+(((Otk[8][0]*rpp[9][1])-(Otk[8][1]*rpp[9][0]))+((wk[8][0]*
          Wkrpk[9][1])-(wk[8][1]*Wkrpk[9][0])))));
        Atk[10][0] = (Atk[9][0]+((2.*((Vik[10][2]*wk[8][1])-(Vik[10][1]*wk[8][2]
          )))+(((Otk[8][1]*rpp[10][2])-(Otk[8][2]*rpp[10][1]))+((wk[8][1]*
          Wkrpk[10][2])-(wk[8][2]*Wkrpk[10][1])))));
        Atk[10][1] = (Atk[9][1]+((2.*((Vik[10][0]*wk[8][2])-(Vik[10][2]*wk[8][0]
          )))+(((Otk[8][2]*rpp[10][0])-(Otk[8][0]*rpp[10][2]))+((wk[8][2]*
          Wkrpk[10][0])-(wk[8][0]*Wkrpk[10][2])))));
        Atk[10][2] = (Atk[9][2]+((2.*((Vik[10][1]*wk[8][0])-(Vik[10][0]*wk[8][1]
          )))+(((Otk[8][0]*rpp[10][1])-(Otk[8][1]*rpp[10][0]))+((wk[8][0]*
          Wkrpk[10][1])-(wk[8][1]*Wkrpk[10][0])))));
        Atk[11][0] = (((Atk[10][2]*Cik[11][2][0])+((Atk[10][0]*Cik[11][0][0])+(
          Atk[10][1]*Cik[11][1][0])))+(((Otk[11][2]*rk[2][1])-(Otk[11][1]*
          rk[2][2]))+((wk[11][1]*Wkrpk[11][2])-(wk[11][2]*Wkrpk[11][1]))));
        Atk[11][1] = (((Atk[10][2]*Cik[11][2][1])+((Atk[10][0]*Cik[11][0][1])+(
          Atk[10][1]*Cik[11][1][1])))+(((Otk[11][0]*rk[2][2])-(Otk[11][2]*
          rk[2][0]))+((wk[11][2]*Wkrpk[11][0])-(wk[11][0]*Wkrpk[11][2]))));
        Atk[11][2] = (((Atk[10][2]*Cik[11][2][2])+((Atk[10][0]*Cik[11][0][2])+(
          Atk[10][1]*Cik[11][1][2])))+(((Otk[11][1]*rk[2][0])-(Otk[11][0]*
          rk[2][1]))+((wk[11][0]*Wkrpk[11][1])-(wk[11][1]*Wkrpk[11][0]))));
        AiOiWi[12][0] = (Atk[11][0]+(((Otk[11][1]*ri[3][2])-(Otk[11][2]*ri[3][1]
          ))+((Wirk[12][2]*wk[11][1])-(Wirk[12][1]*wk[11][2]))));
        AiOiWi[12][1] = (Atk[11][1]+(((Otk[11][2]*ri[3][0])-(Otk[11][0]*ri[3][2]
          ))+((Wirk[12][0]*wk[11][2])-(Wirk[12][2]*wk[11][0]))));
        AiOiWi[12][2] = (Atk[11][2]+(((Otk[11][0]*ri[3][1])-(Otk[11][1]*ri[3][0]
          ))+((Wirk[12][1]*wk[11][0])-(Wirk[12][0]*wk[11][1]))));
        Atk[12][0] = (((AiOiWi[12][2]*Cik[12][2][0])+((AiOiWi[12][0]*
          Cik[12][0][0])+(AiOiWi[12][1]*Cik[12][1][0])))+(((Otk[12][2]*rk[3][1])
          -(Otk[12][1]*rk[3][2]))+((wk[12][1]*Wkrpk[12][2])-(wk[12][2]*
          Wkrpk[12][1]))));
        Atk[12][1] = (((AiOiWi[12][2]*Cik[12][2][1])+((AiOiWi[12][0]*
          Cik[12][0][1])+(AiOiWi[12][1]*Cik[12][1][1])))+(((Otk[12][0]*rk[3][2])
          -(Otk[12][2]*rk[3][0]))+((wk[12][2]*Wkrpk[12][0])-(wk[12][0]*
          Wkrpk[12][2]))));
        Atk[12][2] = (((AiOiWi[12][2]*Cik[12][2][2])+((AiOiWi[12][0]*
          Cik[12][0][2])+(AiOiWi[12][1]*Cik[12][1][2])))+(((Otk[12][1]*rk[3][0])
          -(Otk[12][0]*rk[3][1]))+((wk[12][0]*Wkrpk[12][1])-(wk[12][1]*
          Wkrpk[12][0]))));
        AiOiWi[13][0] = (Atk[12][0]+(((Otk[12][1]*ri[4][2])-(Otk[12][2]*ri[4][1]
          ))+((Wirk[13][2]*wk[12][1])-(Wirk[13][1]*wk[12][2]))));
        AiOiWi[13][1] = (Atk[12][1]+(((Otk[12][2]*ri[4][0])-(Otk[12][0]*ri[4][2]
          ))+((Wirk[13][0]*wk[12][2])-(Wirk[13][2]*wk[12][0]))));
        AiOiWi[13][2] = (Atk[12][2]+(((Otk[12][0]*ri[4][1])-(Otk[12][1]*ri[4][0]
          ))+((Wirk[13][1]*wk[12][0])-(Wirk[13][0]*wk[12][1]))));
        Atk[13][0] = (((AiOiWi[13][2]*Cik[13][2][0])+((AiOiWi[13][0]*
          Cik[13][0][0])+(AiOiWi[13][1]*Cik[13][1][0])))+(((Otk[13][2]*rk[4][1])
          -(Otk[13][1]*rk[4][2]))+((wk[13][1]*Wkrpk[13][2])-(wk[13][2]*
          Wkrpk[13][1]))));
        Atk[13][1] = (((AiOiWi[13][2]*Cik[13][2][1])+((AiOiWi[13][0]*
          Cik[13][0][1])+(AiOiWi[13][1]*Cik[13][1][1])))+(((Otk[13][0]*rk[4][2])
          -(Otk[13][2]*rk[4][0]))+((wk[13][2]*Wkrpk[13][0])-(wk[13][0]*
          Wkrpk[13][2]))));
        Atk[13][2] = (((AiOiWi[13][2]*Cik[13][2][2])+((AiOiWi[13][0]*
          Cik[13][0][2])+(AiOiWi[13][1]*Cik[13][1][2])))+(((Otk[13][1]*rk[4][0])
          -(Otk[13][0]*rk[4][1]))+((wk[13][0]*Wkrpk[13][1])-(wk[13][1]*
          Wkrpk[13][0]))));
        AiOiWi[14][0] = (Atk[13][0]+(((Otk[13][1]*ri[5][2])-(Otk[13][2]*ri[5][1]
          ))+((Wirk[14][2]*wk[13][1])-(Wirk[14][1]*wk[13][2]))));
        AiOiWi[14][1] = (Atk[13][1]+(((Otk[13][2]*ri[5][0])-(Otk[13][0]*ri[5][2]
          ))+((Wirk[14][0]*wk[13][2])-(Wirk[14][2]*wk[13][0]))));
        AiOiWi[14][2] = (Atk[13][2]+(((Otk[13][0]*ri[5][1])-(Otk[13][1]*ri[5][0]
          ))+((Wirk[14][1]*wk[13][0])-(Wirk[14][0]*wk[13][1]))));
        Atk[14][0] = (((AiOiWi[14][2]*Cik[14][2][0])+((AiOiWi[14][0]*
          Cik[14][0][0])+(AiOiWi[14][1]*Cik[14][1][0])))+(((Otk[14][2]*rk[5][1])
          -(Otk[14][1]*rk[5][2]))+((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*
          Wkrpk[14][1]))));
        Atk[14][1] = (((AiOiWi[14][2]*Cik[14][2][1])+((AiOiWi[14][0]*
          Cik[14][0][1])+(AiOiWi[14][1]*Cik[14][1][1])))+(((Otk[14][0]*rk[5][2])
          -(Otk[14][2]*rk[5][0]))+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*
          Wkrpk[14][2]))));
        Atk[14][2] = (((AiOiWi[14][2]*Cik[14][2][2])+((AiOiWi[14][0]*
          Cik[14][0][2])+(AiOiWi[14][1]*Cik[14][1][2])))+(((Otk[14][1]*rk[5][0])
          -(Otk[14][0]*rk[5][1]))+((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*
          Wkrpk[14][0]))));
        AiOiWi[15][0] = (Atk[5][0]+(((Otk[5][1]*ri[6][2])-(Otk[5][2]*ri[6][1]))+
          ((Wirk[15][2]*wk[5][1])-(Wirk[15][1]*wk[5][2]))));
        AiOiWi[15][1] = (Atk[5][1]+(((Otk[5][2]*ri[6][0])-(Otk[5][0]*ri[6][2]))+
          ((Wirk[15][0]*wk[5][2])-(Wirk[15][2]*wk[5][0]))));
        AiOiWi[15][2] = (Atk[5][2]+(((Otk[5][0]*ri[6][1])-(Otk[5][1]*ri[6][0]))+
          ((Wirk[15][1]*wk[5][0])-(Wirk[15][0]*wk[5][1]))));
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
          Atk[16][1]*Cik[17][1][0])))+(((Otk[17][2]*rk[6][1])-(Otk[17][1]*
          rk[6][2]))+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*Wkrpk[17][1]))));
        Atk[17][1] = (((Atk[16][2]*Cik[17][2][1])+((Atk[16][0]*Cik[17][0][1])+(
          Atk[16][1]*Cik[17][1][1])))+(((Otk[17][0]*rk[6][2])-(Otk[17][2]*
          rk[6][0]))+((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
        Atk[17][2] = (((Atk[16][2]*Cik[17][2][2])+((Atk[16][0]*Cik[17][0][2])+(
          Atk[16][1]*Cik[17][1][2])))+(((Otk[17][1]*rk[6][0])-(Otk[17][0]*
          rk[6][1]))+((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*Wkrpk[17][0]))));
        AiOiWi[18][0] = (Atk[17][0]+(((Otk[17][1]*ri[7][2])-(Otk[17][2]*ri[7][1]
          ))+((Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
        AiOiWi[18][1] = (Atk[17][1]+(((Otk[17][2]*ri[7][0])-(Otk[17][0]*ri[7][2]
          ))+((Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
        AiOiWi[18][2] = (Atk[17][2]+(((Otk[17][0]*ri[7][1])-(Otk[17][1]*ri[7][0]
          ))+((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*wk[17][1]))));
        Atk[18][0] = (AiOiWi[18][0]+((2.*((Vik[18][2]*wk[17][1])-(Vik[18][1]*
          wk[17][2])))+(((Otk[17][1]*rpp[18][2])-(Otk[17][2]*rpp[18][1]))+((
          wk[17][1]*Wkrpk[18][2])-(wk[17][2]*Wkrpk[18][1])))));
        Atk[18][1] = (AiOiWi[18][1]+((2.*((Vik[18][0]*wk[17][2])-(Vik[18][2]*
          wk[17][0])))+(((Otk[17][2]*rpp[18][0])-(Otk[17][0]*rpp[18][2]))+((
          wk[17][2]*Wkrpk[18][0])-(wk[17][0]*Wkrpk[18][2])))));
        Atk[18][2] = (AiOiWi[18][2]+((2.*((Vik[18][1]*wk[17][0])-(Vik[18][0]*
          wk[17][1])))+(((Otk[17][0]*rpp[18][1])-(Otk[17][1]*rpp[18][0]))+((
          wk[17][0]*Wkrpk[18][1])-(wk[17][1]*Wkrpk[18][0])))));
        Atk[19][0] = (Atk[18][0]+((2.*((Vik[19][2]*wk[17][1])-(Vik[19][1]*
          wk[17][2])))+(((Otk[17][1]*rpp[19][2])-(Otk[17][2]*rpp[19][1]))+((
          wk[17][1]*Wkrpk[19][2])-(wk[17][2]*Wkrpk[19][1])))));
        Atk[19][1] = (Atk[18][1]+((2.*((Vik[19][0]*wk[17][2])-(Vik[19][2]*
          wk[17][0])))+(((Otk[17][2]*rpp[19][0])-(Otk[17][0]*rpp[19][2]))+((
          wk[17][2]*Wkrpk[19][0])-(wk[17][0]*Wkrpk[19][2])))));
        Atk[19][2] = (Atk[18][2]+((2.*((Vik[19][1]*wk[17][0])-(Vik[19][0]*
          wk[17][1])))+(((Otk[17][0]*rpp[19][1])-(Otk[17][1]*rpp[19][0]))+((
          wk[17][0]*Wkrpk[19][1])-(wk[17][1]*Wkrpk[19][0])))));
        Atk[20][0] = (((Atk[19][2]*Cik[20][2][0])+((Atk[19][0]*Cik[20][0][0])+(
          Atk[19][1]*Cik[20][1][0])))+(((Otk[20][2]*rk[7][1])-(Otk[20][1]*
          rk[7][2]))+((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
        Atk[20][1] = (((Atk[19][2]*Cik[20][2][1])+((Atk[19][0]*Cik[20][0][1])+(
          Atk[19][1]*Cik[20][1][1])))+(((Otk[20][0]*rk[7][2])-(Otk[20][2]*
          rk[7][0]))+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*Wkrpk[20][2]))));
        Atk[20][2] = (((Atk[19][2]*Cik[20][2][2])+((Atk[19][0]*Cik[20][0][2])+(
          Atk[19][1]*Cik[20][1][2])))+(((Otk[20][1]*rk[7][0])-(Otk[20][0]*
          rk[7][1]))+((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*Wkrpk[20][0]))));
        AiOiWi[21][0] = (Atk[20][0]+(((Otk[20][1]*ri[8][2])-(Otk[20][2]*ri[8][1]
          ))+((Wirk[21][2]*wk[20][1])-(Wirk[21][1]*wk[20][2]))));
        AiOiWi[21][1] = (Atk[20][1]+(((Otk[20][2]*ri[8][0])-(Otk[20][0]*ri[8][2]
          ))+((Wirk[21][0]*wk[20][2])-(Wirk[21][2]*wk[20][0]))));
        AiOiWi[21][2] = (Atk[20][2]+(((Otk[20][0]*ri[8][1])-(Otk[20][1]*ri[8][0]
          ))+((Wirk[21][1]*wk[20][0])-(Wirk[21][0]*wk[20][1]))));
        Atk[21][0] = (((AiOiWi[21][2]*Cik[21][2][0])+((AiOiWi[21][0]*
          Cik[21][0][0])+(AiOiWi[21][1]*Cik[21][1][0])))+(((Otk[21][2]*rk[8][1])
          -(Otk[21][1]*rk[8][2]))+((wk[21][1]*Wkrpk[21][2])-(wk[21][2]*
          Wkrpk[21][1]))));
        Atk[21][1] = (((AiOiWi[21][2]*Cik[21][2][1])+((AiOiWi[21][0]*
          Cik[21][0][1])+(AiOiWi[21][1]*Cik[21][1][1])))+(((Otk[21][0]*rk[8][2])
          -(Otk[21][2]*rk[8][0]))+((wk[21][2]*Wkrpk[21][0])-(wk[21][0]*
          Wkrpk[21][2]))));
        Atk[21][2] = (((AiOiWi[21][2]*Cik[21][2][2])+((AiOiWi[21][0]*
          Cik[21][0][2])+(AiOiWi[21][1]*Cik[21][1][2])))+(((Otk[21][1]*rk[8][0])
          -(Otk[21][0]*rk[8][1]))+((wk[21][0]*Wkrpk[21][1])-(wk[21][1]*
          Wkrpk[21][0]))));
        AiOiWi[22][0] = (Atk[21][0]+(((Otk[21][1]*ri[9][2])-(Otk[21][2]*ri[9][1]
          ))+((Wirk[22][2]*wk[21][1])-(Wirk[22][1]*wk[21][2]))));
        AiOiWi[22][1] = (Atk[21][1]+(((Otk[21][2]*ri[9][0])-(Otk[21][0]*ri[9][2]
          ))+((Wirk[22][0]*wk[21][2])-(Wirk[22][2]*wk[21][0]))));
        AiOiWi[22][2] = (Atk[21][2]+(((Otk[21][0]*ri[9][1])-(Otk[21][1]*ri[9][0]
          ))+((Wirk[22][1]*wk[21][0])-(Wirk[22][0]*wk[21][1]))));
        Atk[22][0] = (((AiOiWi[22][2]*Cik[22][2][0])+((AiOiWi[22][0]*
          Cik[22][0][0])+(AiOiWi[22][1]*Cik[22][1][0])))+(((Otk[22][2]*rk[9][1])
          -(Otk[22][1]*rk[9][2]))+((wk[22][1]*Wkrpk[22][2])-(wk[22][2]*
          Wkrpk[22][1]))));
        Atk[22][1] = (((AiOiWi[22][2]*Cik[22][2][1])+((AiOiWi[22][0]*
          Cik[22][0][1])+(AiOiWi[22][1]*Cik[22][1][1])))+(((Otk[22][0]*rk[9][2])
          -(Otk[22][2]*rk[9][0]))+((wk[22][2]*Wkrpk[22][0])-(wk[22][0]*
          Wkrpk[22][2]))));
        Atk[22][2] = (((AiOiWi[22][2]*Cik[22][2][2])+((AiOiWi[22][0]*
          Cik[22][0][2])+(AiOiWi[22][1]*Cik[22][1][2])))+(((Otk[22][1]*rk[9][0])
          -(Otk[22][0]*rk[9][1]))+((wk[22][0]*Wkrpk[22][1])-(wk[22][1]*
          Wkrpk[22][0]))));
        AiOiWi[23][0] = (Atk[22][0]+(((Otk[22][1]*ri[10][2])-(Otk[22][2]*
          ri[10][1]))+((Wirk[23][2]*wk[22][1])-(Wirk[23][1]*wk[22][2]))));
        AiOiWi[23][1] = (Atk[22][1]+(((Otk[22][2]*ri[10][0])-(Otk[22][0]*
          ri[10][2]))+((Wirk[23][0]*wk[22][2])-(Wirk[23][2]*wk[22][0]))));
        AiOiWi[23][2] = (Atk[22][2]+(((Otk[22][0]*ri[10][1])-(Otk[22][1]*
          ri[10][0]))+((Wirk[23][1]*wk[22][0])-(Wirk[23][0]*wk[22][1]))));
        Atk[23][0] = (((AiOiWi[23][2]*Cik[23][2][0])+((AiOiWi[23][0]*
          Cik[23][0][0])+(AiOiWi[23][1]*Cik[23][1][0])))+(((Otk[23][2]*rk[10][1]
          )-(Otk[23][1]*rk[10][2]))+((wk[23][1]*Wkrpk[23][2])-(wk[23][2]*
          Wkrpk[23][1]))));
        Atk[23][1] = (((AiOiWi[23][2]*Cik[23][2][1])+((AiOiWi[23][0]*
          Cik[23][0][1])+(AiOiWi[23][1]*Cik[23][1][1])))+(((Otk[23][0]*rk[10][2]
          )-(Otk[23][2]*rk[10][0]))+((wk[23][2]*Wkrpk[23][0])-(wk[23][0]*
          Wkrpk[23][2]))));
        Atk[23][2] = (((AiOiWi[23][2]*Cik[23][2][2])+((AiOiWi[23][0]*
          Cik[23][0][2])+(AiOiWi[23][1]*Cik[23][1][2])))+(((Otk[23][1]*rk[10][0]
          )-(Otk[23][0]*rk[10][1]))+((wk[23][0]*Wkrpk[23][1])-(wk[23][1]*
          Wkrpk[23][0]))));
        AiOiWi[24][0] = (Atk[5][0]+(((Otk[5][1]*ri[11][2])-(Otk[5][2]*ri[11][1])
          )+((Wirk[24][2]*wk[5][1])-(Wirk[24][1]*wk[5][2]))));
        AiOiWi[24][1] = (Atk[5][1]+(((Otk[5][2]*ri[11][0])-(Otk[5][0]*ri[11][2])
          )+((Wirk[24][0]*wk[5][2])-(Wirk[24][2]*wk[5][0]))));
        AiOiWi[24][2] = (Atk[5][2]+(((Otk[5][0]*ri[11][1])-(Otk[5][1]*ri[11][0])
          )+((Wirk[24][1]*wk[5][0])-(Wirk[24][0]*wk[5][1]))));
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
        Atk[26][0] = (((Atk[25][2]*Cik[26][2][0])+((Atk[25][0]*Cik[26][0][0])+(
          Atk[25][1]*Cik[26][1][0])))+(((Otk[26][2]*rk[11][1])-(Otk[26][1]*
          rk[11][2]))+((wk[26][1]*Wkrpk[26][2])-(wk[26][2]*Wkrpk[26][1]))));
        Atk[26][1] = (((Atk[25][2]*Cik[26][2][1])+((Atk[25][0]*Cik[26][0][1])+(
          Atk[25][1]*Cik[26][1][1])))+(((Otk[26][0]*rk[11][2])-(Otk[26][2]*
          rk[11][0]))+((wk[26][2]*Wkrpk[26][0])-(wk[26][0]*Wkrpk[26][2]))));
        Atk[26][2] = (((Atk[25][2]*Cik[26][2][2])+((Atk[25][0]*Cik[26][0][2])+(
          Atk[25][1]*Cik[26][1][2])))+(((Otk[26][1]*rk[11][0])-(Otk[26][0]*
          rk[11][1]))+((wk[26][0]*Wkrpk[26][1])-(wk[26][1]*Wkrpk[26][0]))));
        inerflg = 1;
    }
/*
 Used 0.16 seconds CPU time,
 16384 additional bytes of memory.
 Equations contain  666 adds/subtracts/negates
                    789 multiplies
                      0 divides
                    156 assignments
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
        Fstar[5][0] = ((mk[0]*(Atk[5][0]-gk[5][0]))-ufk[0][0]);
        Fstar[5][1] = ((mk[0]*(Atk[5][1]-gk[5][1]))-ufk[0][1]);
        Fstar[5][2] = ((mk[0]*(Atk[5][2]-gk[5][2]))-ufk[0][2]);
        Fstar[8][0] = ((mk[1]*(Atk[8][0]-gk[8][0]))-ufk[1][0]);
        Fstar[8][1] = ((mk[1]*(Atk[8][1]-gk[8][1]))-ufk[1][1]);
        Fstar[8][2] = ((mk[1]*(Atk[8][2]-gk[8][2]))-ufk[1][2]);
        Fstar[11][0] = ((mk[2]*(Atk[11][0]-gk[11][0]))-ufk[2][0]);
        Fstar[11][1] = ((mk[2]*(Atk[11][1]-gk[11][1]))-ufk[2][1]);
        Fstar[11][2] = ((mk[2]*(Atk[11][2]-gk[11][2]))-ufk[2][2]);
        Fstar[12][0] = ((mk[3]*(Atk[12][0]-gk[12][0]))-ufk[3][0]);
        Fstar[12][1] = ((mk[3]*(Atk[12][1]-gk[12][1]))-ufk[3][1]);
        Fstar[12][2] = ((mk[3]*(Atk[12][2]-gk[12][2]))-ufk[3][2]);
        Fstar[13][0] = ((mk[4]*(Atk[13][0]-gk[13][0]))-ufk[4][0]);
        Fstar[13][1] = ((mk[4]*(Atk[13][1]-gk[13][1]))-ufk[4][1]);
        Fstar[13][2] = ((mk[4]*(Atk[13][2]-gk[13][2]))-ufk[4][2]);
        Fstar[14][0] = ((mk[5]*(Atk[14][0]-gk[14][0]))-ufk[5][0]);
        Fstar[14][1] = ((mk[5]*(Atk[14][1]-gk[14][1]))-ufk[5][1]);
        Fstar[14][2] = ((mk[5]*(Atk[14][2]-gk[14][2]))-ufk[5][2]);
        Fstar[17][0] = ((mk[6]*(Atk[17][0]-gk[17][0]))-ufk[6][0]);
        Fstar[17][1] = ((mk[6]*(Atk[17][1]-gk[17][1]))-ufk[6][1]);
        Fstar[17][2] = ((mk[6]*(Atk[17][2]-gk[17][2]))-ufk[6][2]);
        Fstar[20][0] = ((mk[7]*(Atk[20][0]-gk[20][0]))-ufk[7][0]);
        Fstar[20][1] = ((mk[7]*(Atk[20][1]-gk[20][1]))-ufk[7][1]);
        Fstar[20][2] = ((mk[7]*(Atk[20][2]-gk[20][2]))-ufk[7][2]);
        Fstar[21][0] = ((mk[8]*(Atk[21][0]-gk[21][0]))-ufk[8][0]);
        Fstar[21][1] = ((mk[8]*(Atk[21][1]-gk[21][1]))-ufk[8][1]);
        Fstar[21][2] = ((mk[8]*(Atk[21][2]-gk[21][2]))-ufk[8][2]);
        Fstar[22][0] = ((mk[9]*(Atk[22][0]-gk[22][0]))-ufk[9][0]);
        Fstar[22][1] = ((mk[9]*(Atk[22][1]-gk[22][1]))-ufk[9][1]);
        Fstar[22][2] = ((mk[9]*(Atk[22][2]-gk[22][2]))-ufk[9][2]);
        Fstar[23][0] = ((mk[10]*(Atk[23][0]-gk[23][0]))-ufk[10][0]);
        Fstar[23][1] = ((mk[10]*(Atk[23][1]-gk[23][1]))-ufk[10][1]);
        Fstar[23][2] = ((mk[10]*(Atk[23][2]-gk[23][2]))-ufk[10][2]);
        Fstar[26][0] = ((mk[11]*(Atk[26][0]-gk[26][0]))-ufk[11][0]);
        Fstar[26][1] = ((mk[11]*(Atk[26][1]-gk[26][1]))-ufk[11][1]);
        Fstar[26][2] = ((mk[11]*(Atk[26][2]-gk[26][2]))-ufk[11][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = ((WkIkWk[5][0]+((ik[0][0][2]*Otk[5][2])+((ik[0][0][0]*
          Otk[5][0])+(ik[0][0][1]*Otk[5][1]))))-utk[0][0]);
        Tstar[5][1] = ((WkIkWk[5][1]+((ik[0][1][2]*Otk[5][2])+((ik[0][1][0]*
          Otk[5][0])+(ik[0][1][1]*Otk[5][1]))))-utk[0][1]);
        Tstar[5][2] = ((WkIkWk[5][2]+((ik[0][2][2]*Otk[5][2])+((ik[0][2][0]*
          Otk[5][0])+(ik[0][2][1]*Otk[5][1]))))-utk[0][2]);
        Tstar[8][0] = ((WkIkWk[8][0]+((ik[1][0][2]*Otk[8][2])+((ik[1][0][0]*
          Otk[8][0])+(ik[1][0][1]*Otk[8][1]))))-utk[1][0]);
        Tstar[8][1] = ((WkIkWk[8][1]+((ik[1][1][2]*Otk[8][2])+((ik[1][1][0]*
          Otk[8][0])+(ik[1][1][1]*Otk[8][1]))))-utk[1][1]);
        Tstar[8][2] = ((WkIkWk[8][2]+((ik[1][2][2]*Otk[8][2])+((ik[1][2][0]*
          Otk[8][0])+(ik[1][2][1]*Otk[8][1]))))-utk[1][2]);
        Tstar[11][0] = ((WkIkWk[11][0]+((ik[2][0][2]*Otk[11][2])+((ik[2][0][0]*
          Otk[11][0])+(ik[2][0][1]*Otk[11][1]))))-utk[2][0]);
        Tstar[11][1] = ((WkIkWk[11][1]+((ik[2][1][2]*Otk[11][2])+((ik[2][1][0]*
          Otk[11][0])+(ik[2][1][1]*Otk[11][1]))))-utk[2][1]);
        Tstar[11][2] = ((WkIkWk[11][2]+((ik[2][2][2]*Otk[11][2])+((ik[2][2][0]*
          Otk[11][0])+(ik[2][2][1]*Otk[11][1]))))-utk[2][2]);
        Tstar[12][0] = ((WkIkWk[12][0]+((ik[3][0][2]*Otk[12][2])+((ik[3][0][0]*
          Otk[12][0])+(ik[3][0][1]*Otk[12][1]))))-utk[3][0]);
        Tstar[12][1] = ((WkIkWk[12][1]+((ik[3][1][2]*Otk[12][2])+((ik[3][1][0]*
          Otk[12][0])+(ik[3][1][1]*Otk[12][1]))))-utk[3][1]);
        Tstar[12][2] = ((WkIkWk[12][2]+((ik[3][2][2]*Otk[12][2])+((ik[3][2][0]*
          Otk[12][0])+(ik[3][2][1]*Otk[12][1]))))-utk[3][2]);
        Tstar[13][0] = ((WkIkWk[13][0]+((ik[4][0][2]*Otk[13][2])+((ik[4][0][0]*
          Otk[13][0])+(ik[4][0][1]*Otk[13][1]))))-utk[4][0]);
        Tstar[13][1] = ((WkIkWk[13][1]+((ik[4][1][2]*Otk[13][2])+((ik[4][1][0]*
          Otk[13][0])+(ik[4][1][1]*Otk[13][1]))))-utk[4][1]);
        Tstar[13][2] = ((WkIkWk[13][2]+((ik[4][2][2]*Otk[13][2])+((ik[4][2][0]*
          Otk[13][0])+(ik[4][2][1]*Otk[13][1]))))-utk[4][2]);
        Tstar[14][0] = ((WkIkWk[14][0]+((ik[5][0][2]*Otk[14][2])+((ik[5][0][0]*
          Otk[14][0])+(ik[5][0][1]*Otk[14][1]))))-utk[5][0]);
        Tstar[14][1] = ((WkIkWk[14][1]+((ik[5][1][2]*Otk[14][2])+((ik[5][1][0]*
          Otk[14][0])+(ik[5][1][1]*Otk[14][1]))))-utk[5][1]);
        Tstar[14][2] = ((WkIkWk[14][2]+((ik[5][2][2]*Otk[14][2])+((ik[5][2][0]*
          Otk[14][0])+(ik[5][2][1]*Otk[14][1]))))-utk[5][2]);
        Tstar[17][0] = ((WkIkWk[17][0]+((ik[6][0][2]*Otk[17][2])+((ik[6][0][0]*
          Otk[17][0])+(ik[6][0][1]*Otk[17][1]))))-utk[6][0]);
        Tstar[17][1] = ((WkIkWk[17][1]+((ik[6][1][2]*Otk[17][2])+((ik[6][1][0]*
          Otk[17][0])+(ik[6][1][1]*Otk[17][1]))))-utk[6][1]);
        Tstar[17][2] = ((WkIkWk[17][2]+((ik[6][2][2]*Otk[17][2])+((ik[6][2][0]*
          Otk[17][0])+(ik[6][2][1]*Otk[17][1]))))-utk[6][2]);
        Tstar[20][0] = ((WkIkWk[20][0]+((ik[7][0][2]*Otk[20][2])+((ik[7][0][0]*
          Otk[20][0])+(ik[7][0][1]*Otk[20][1]))))-utk[7][0]);
        Tstar[20][1] = ((WkIkWk[20][1]+((ik[7][1][2]*Otk[20][2])+((ik[7][1][0]*
          Otk[20][0])+(ik[7][1][1]*Otk[20][1]))))-utk[7][1]);
        Tstar[20][2] = ((WkIkWk[20][2]+((ik[7][2][2]*Otk[20][2])+((ik[7][2][0]*
          Otk[20][0])+(ik[7][2][1]*Otk[20][1]))))-utk[7][2]);
        Tstar[21][0] = ((WkIkWk[21][0]+((ik[8][0][2]*Otk[21][2])+((ik[8][0][0]*
          Otk[21][0])+(ik[8][0][1]*Otk[21][1]))))-utk[8][0]);
        Tstar[21][1] = ((WkIkWk[21][1]+((ik[8][1][2]*Otk[21][2])+((ik[8][1][0]*
          Otk[21][0])+(ik[8][1][1]*Otk[21][1]))))-utk[8][1]);
        Tstar[21][2] = ((WkIkWk[21][2]+((ik[8][2][2]*Otk[21][2])+((ik[8][2][0]*
          Otk[21][0])+(ik[8][2][1]*Otk[21][1]))))-utk[8][2]);
        Tstar[22][0] = ((WkIkWk[22][0]+((ik[9][0][2]*Otk[22][2])+((ik[9][0][0]*
          Otk[22][0])+(ik[9][0][1]*Otk[22][1]))))-utk[9][0]);
        Tstar[22][1] = ((WkIkWk[22][1]+((ik[9][1][2]*Otk[22][2])+((ik[9][1][0]*
          Otk[22][0])+(ik[9][1][1]*Otk[22][1]))))-utk[9][1]);
        Tstar[22][2] = ((WkIkWk[22][2]+((ik[9][2][2]*Otk[22][2])+((ik[9][2][0]*
          Otk[22][0])+(ik[9][2][1]*Otk[22][1]))))-utk[9][2]);
        Tstar[23][0] = ((WkIkWk[23][0]+((ik[10][0][2]*Otk[23][2])+((ik[10][0][0]
          *Otk[23][0])+(ik[10][0][1]*Otk[23][1]))))-utk[10][0]);
        Tstar[23][1] = ((WkIkWk[23][1]+((ik[10][1][2]*Otk[23][2])+((ik[10][1][0]
          *Otk[23][0])+(ik[10][1][1]*Otk[23][1]))))-utk[10][1]);
        Tstar[23][2] = ((WkIkWk[23][2]+((ik[10][2][2]*Otk[23][2])+((ik[10][2][0]
          *Otk[23][0])+(ik[10][2][1]*Otk[23][1]))))-utk[10][2]);
        Tstar[26][0] = ((WkIkWk[26][0]+((ik[11][0][2]*Otk[26][2])+((ik[11][0][0]
          *Otk[26][0])+(ik[11][0][1]*Otk[26][1]))))-utk[11][0]);
        Tstar[26][1] = ((WkIkWk[26][1]+((ik[11][1][2]*Otk[26][2])+((ik[11][1][0]
          *Otk[26][0])+(ik[11][1][1]*Otk[26][1]))))-utk[11][1]);
        Tstar[26][2] = ((WkIkWk[26][2]+((ik[11][2][2]*Otk[26][2])+((ik[11][2][0]
          *Otk[26][0])+(ik[11][2][1]*Otk[26][1]))))-utk[11][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        temp[0] = (((Fstar[12][2]*Vpk[0][12][2])+((Fstar[12][0]*Vpk[0][12][0])+(
          Fstar[12][1]*Vpk[0][12][1])))+(((Fstar[11][2]*Vpk[0][11][2])+((
          Fstar[11][0]*Vpk[0][11][0])+(Fstar[11][1]*Vpk[0][11][1])))+(((
          Fstar[5][2]*Vpk[0][5][2])+((Fstar[5][0]*Vpk[0][5][0])+(Fstar[5][1]*
          Vpk[0][5][1])))+((Fstar[8][2]*Vpk[0][8][2])+((Fstar[8][0]*Vpk[0][8][0]
          )+(Fstar[8][1]*Vpk[0][8][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[0][20][2])+((Fstar[20][0]*Vpk[0][20][0])+(
          Fstar[20][1]*Vpk[0][20][1])))+(((Fstar[17][2]*Vpk[0][17][2])+((
          Fstar[17][0]*Vpk[0][17][0])+(Fstar[17][1]*Vpk[0][17][1])))+(((
          Fstar[14][2]*Vpk[0][14][2])+((Fstar[14][0]*Vpk[0][14][0])+(
          Fstar[14][1]*Vpk[0][14][1])))+(((Fstar[13][2]*Vpk[0][13][2])+((
          Fstar[13][0]*Vpk[0][13][0])+(Fstar[13][1]*Vpk[0][13][1])))+temp[0]))))
          ;
        fs0[0] = (utau[0]-(((Fstar[26][2]*Vpk[0][26][2])+((Fstar[26][0]*
          Vpk[0][26][0])+(Fstar[26][1]*Vpk[0][26][1])))+(((Fstar[23][2]*
          Vpk[0][23][2])+((Fstar[23][0]*Vpk[0][23][0])+(Fstar[23][1]*
          Vpk[0][23][1])))+(((Fstar[22][2]*Vpk[0][22][2])+((Fstar[22][0]*
          Vpk[0][22][0])+(Fstar[22][1]*Vpk[0][22][1])))+(((Fstar[21][2]*
          Vpk[0][21][2])+((Fstar[21][0]*Vpk[0][21][0])+(Fstar[21][1]*
          Vpk[0][21][1])))+temp[1])))));
        temp[0] = (((Fstar[12][2]*Vpk[1][12][2])+((Fstar[12][0]*Vpk[1][12][0])+(
          Fstar[12][1]*Vpk[1][12][1])))+(((Fstar[11][2]*Vpk[1][11][2])+((
          Fstar[11][0]*Vpk[1][11][0])+(Fstar[11][1]*Vpk[1][11][1])))+(((
          Fstar[5][2]*Vpk[1][5][2])+((Fstar[5][0]*Vpk[1][5][0])+(Fstar[5][1]*
          Vpk[1][5][1])))+((Fstar[8][2]*Vpk[1][8][2])+((Fstar[8][0]*Vpk[1][8][0]
          )+(Fstar[8][1]*Vpk[1][8][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[1][20][2])+((Fstar[20][0]*Vpk[1][20][0])+(
          Fstar[20][1]*Vpk[1][20][1])))+(((Fstar[17][2]*Vpk[1][17][2])+((
          Fstar[17][0]*Vpk[1][17][0])+(Fstar[17][1]*Vpk[1][17][1])))+(((
          Fstar[14][2]*Vpk[1][14][2])+((Fstar[14][0]*Vpk[1][14][0])+(
          Fstar[14][1]*Vpk[1][14][1])))+(((Fstar[13][2]*Vpk[1][13][2])+((
          Fstar[13][0]*Vpk[1][13][0])+(Fstar[13][1]*Vpk[1][13][1])))+temp[0]))))
          ;
        fs0[1] = (utau[1]-(((Fstar[26][2]*Vpk[1][26][2])+((Fstar[26][0]*
          Vpk[1][26][0])+(Fstar[26][1]*Vpk[1][26][1])))+(((Fstar[23][2]*
          Vpk[1][23][2])+((Fstar[23][0]*Vpk[1][23][0])+(Fstar[23][1]*
          Vpk[1][23][1])))+(((Fstar[22][2]*Vpk[1][22][2])+((Fstar[22][0]*
          Vpk[1][22][0])+(Fstar[22][1]*Vpk[1][22][1])))+(((Fstar[21][2]*
          Vpk[1][21][2])+((Fstar[21][0]*Vpk[1][21][0])+(Fstar[21][1]*
          Vpk[1][21][1])))+temp[1])))));
        temp[0] = (((Fstar[12][2]*Vpk[2][12][2])+((Fstar[12][0]*Vpk[2][12][0])+(
          Fstar[12][1]*Vpk[2][12][1])))+(((Fstar[11][2]*Vpk[2][11][2])+((
          Fstar[11][0]*Vpk[2][11][0])+(Fstar[11][1]*Vpk[2][11][1])))+(((
          Fstar[5][2]*Vpk[2][5][2])+((Fstar[5][0]*Vpk[2][5][0])+(Fstar[5][1]*
          Vpk[2][5][1])))+((Fstar[8][2]*Vpk[2][8][2])+((Fstar[8][0]*Vpk[2][8][0]
          )+(Fstar[8][1]*Vpk[2][8][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[2][20][2])+((Fstar[20][0]*Vpk[2][20][0])+(
          Fstar[20][1]*Vpk[2][20][1])))+(((Fstar[17][2]*Vpk[2][17][2])+((
          Fstar[17][0]*Vpk[2][17][0])+(Fstar[17][1]*Vpk[2][17][1])))+(((
          Fstar[14][2]*Vpk[2][14][2])+((Fstar[14][0]*Vpk[2][14][0])+(
          Fstar[14][1]*Vpk[2][14][1])))+(((Fstar[13][2]*Vpk[2][13][2])+((
          Fstar[13][0]*Vpk[2][13][0])+(Fstar[13][1]*Vpk[2][13][1])))+temp[0]))))
          ;
        fs0[2] = (utau[2]-(((Fstar[26][2]*Vpk[2][26][2])+((Fstar[26][0]*
          Vpk[2][26][0])+(Fstar[26][1]*Vpk[2][26][1])))+(((Fstar[23][2]*
          Vpk[2][23][2])+((Fstar[23][0]*Vpk[2][23][0])+(Fstar[23][1]*
          Vpk[2][23][1])))+(((Fstar[22][2]*Vpk[2][22][2])+((Fstar[22][0]*
          Vpk[2][22][0])+(Fstar[22][1]*Vpk[2][22][1])))+(((Fstar[21][2]*
          Vpk[2][21][2])+((Fstar[21][0]*Vpk[2][21][0])+(Fstar[21][1]*
          Vpk[2][21][1])))+temp[1])))));
        temp[0] = ((((Fstar[5][2]*Vpk[3][5][2])+((Fstar[5][0]*Vpk[3][5][0])+(
          Fstar[5][1]*Vpk[3][5][1])))+((Tstar[5][2]*Wpk[3][5][2])+((Tstar[5][0]*
          Wpk[3][5][0])+(Tstar[5][1]*Wpk[3][5][1]))))+(((Fstar[8][2]*
          Vpk[3][8][2])+((Fstar[8][0]*Vpk[3][8][0])+(Fstar[8][1]*Vpk[3][8][1])))
          +((Tstar[8][2]*Wpk[3][8][2])+((Tstar[8][0]*Wpk[3][8][0])+(Tstar[8][1]*
          Wpk[3][8][1])))));
        temp[1] = ((((Fstar[12][2]*Vpk[3][12][2])+((Fstar[12][0]*Vpk[3][12][0])+
          (Fstar[12][1]*Vpk[3][12][1])))+((Tstar[12][2]*Wpk[3][12][2])+((
          Tstar[12][0]*Wpk[3][12][0])+(Tstar[12][1]*Wpk[3][12][1]))))+((((
          Fstar[11][2]*Vpk[3][11][2])+((Fstar[11][0]*Vpk[3][11][0])+(
          Fstar[11][1]*Vpk[3][11][1])))+((Tstar[11][2]*Wpk[3][11][2])+((
          Tstar[11][0]*Wpk[3][11][0])+(Tstar[11][1]*Wpk[3][11][1]))))+temp[0]));
        temp[2] = ((((Fstar[14][2]*Vpk[3][14][2])+((Fstar[14][0]*Vpk[3][14][0])+
          (Fstar[14][1]*Vpk[3][14][1])))+((Tstar[14][2]*Wpk[3][14][2])+((
          Tstar[14][0]*Wpk[3][14][0])+(Tstar[14][1]*Wpk[3][14][1]))))+((((
          Fstar[13][2]*Vpk[3][13][2])+((Fstar[13][0]*Vpk[3][13][0])+(
          Fstar[13][1]*Vpk[3][13][1])))+((Tstar[13][2]*Wpk[3][13][2])+((
          Tstar[13][0]*Wpk[3][13][0])+(Tstar[13][1]*Wpk[3][13][1]))))+temp[1]));
        temp[3] = ((((Fstar[20][2]*Vpk[3][20][2])+((Fstar[20][0]*Vpk[3][20][0])+
          (Fstar[20][1]*Vpk[3][20][1])))+((Tstar[20][2]*Wpk[3][20][2])+((
          Tstar[20][0]*Wpk[3][20][0])+(Tstar[20][1]*Wpk[3][20][1]))))+((((
          Fstar[17][2]*Vpk[3][17][2])+((Fstar[17][0]*Vpk[3][17][0])+(
          Fstar[17][1]*Vpk[3][17][1])))+((Tstar[17][2]*Wpk[3][17][2])+((
          Tstar[17][0]*Wpk[3][17][0])+(Tstar[17][1]*Wpk[3][17][1]))))+temp[2]));
        temp[4] = ((((Fstar[22][2]*Vpk[3][22][2])+((Fstar[22][0]*Vpk[3][22][0])+
          (Fstar[22][1]*Vpk[3][22][1])))+((Tstar[22][2]*Wpk[3][22][2])+((
          Tstar[22][0]*Wpk[3][22][0])+(Tstar[22][1]*Wpk[3][22][1]))))+((((
          Fstar[21][2]*Vpk[3][21][2])+((Fstar[21][0]*Vpk[3][21][0])+(
          Fstar[21][1]*Vpk[3][21][1])))+((Tstar[21][2]*Wpk[3][21][2])+((
          Tstar[21][0]*Wpk[3][21][0])+(Tstar[21][1]*Wpk[3][21][1]))))+temp[3]));
        fs0[3] = (utau[3]-((((Fstar[26][2]*Vpk[3][26][2])+((Fstar[26][0]*
          Vpk[3][26][0])+(Fstar[26][1]*Vpk[3][26][1])))+((Tstar[26][2]*
          Wpk[3][26][2])+((Tstar[26][0]*Wpk[3][26][0])+(Tstar[26][1]*
          Wpk[3][26][1]))))+((((Fstar[23][2]*Vpk[3][23][2])+((Fstar[23][0]*
          Vpk[3][23][0])+(Fstar[23][1]*Vpk[3][23][1])))+((Tstar[23][2]*
          Wpk[3][23][2])+((Tstar[23][0]*Wpk[3][23][0])+(Tstar[23][1]*
          Wpk[3][23][1]))))+temp[4])));
        temp[0] = ((((Fstar[5][2]*Vpk[4][5][2])+((Fstar[5][0]*Vpk[4][5][0])+(
          Fstar[5][1]*Vpk[4][5][1])))+((Tstar[5][2]*Wpk[4][5][2])+((Tstar[5][0]*
          Wpk[4][5][0])+(Tstar[5][1]*Wpk[4][5][1]))))+(((Fstar[8][2]*
          Vpk[4][8][2])+((Fstar[8][0]*Vpk[4][8][0])+(Fstar[8][1]*Vpk[4][8][1])))
          +((Tstar[8][2]*Wpk[4][8][2])+((Tstar[8][0]*Wpk[4][8][0])+(Tstar[8][1]*
          Wpk[4][8][1])))));
        temp[1] = ((((Fstar[12][2]*Vpk[4][12][2])+((Fstar[12][0]*Vpk[4][12][0])+
          (Fstar[12][1]*Vpk[4][12][1])))+((Tstar[12][2]*Wpk[4][12][2])+((
          Tstar[12][0]*Wpk[4][12][0])+(Tstar[12][1]*Wpk[4][12][1]))))+((((
          Fstar[11][2]*Vpk[4][11][2])+((Fstar[11][0]*Vpk[4][11][0])+(
          Fstar[11][1]*Vpk[4][11][1])))+((Tstar[11][2]*Wpk[4][11][2])+((
          Tstar[11][0]*Wpk[4][11][0])+(Tstar[11][1]*Wpk[4][11][1]))))+temp[0]));
        temp[2] = ((((Fstar[14][2]*Vpk[4][14][2])+((Fstar[14][0]*Vpk[4][14][0])+
          (Fstar[14][1]*Vpk[4][14][1])))+((Tstar[14][2]*Wpk[4][14][2])+((
          Tstar[14][0]*Wpk[4][14][0])+(Tstar[14][1]*Wpk[4][14][1]))))+((((
          Fstar[13][2]*Vpk[4][13][2])+((Fstar[13][0]*Vpk[4][13][0])+(
          Fstar[13][1]*Vpk[4][13][1])))+((Tstar[13][2]*Wpk[4][13][2])+((
          Tstar[13][0]*Wpk[4][13][0])+(Tstar[13][1]*Wpk[4][13][1]))))+temp[1]));
        temp[3] = ((((Fstar[20][2]*Vpk[4][20][2])+((Fstar[20][0]*Vpk[4][20][0])+
          (Fstar[20][1]*Vpk[4][20][1])))+((Tstar[20][2]*Wpk[4][20][2])+((
          Tstar[20][0]*Wpk[4][20][0])+(Tstar[20][1]*Wpk[4][20][1]))))+((((
          Fstar[17][2]*Vpk[4][17][2])+((Fstar[17][0]*Vpk[4][17][0])+(
          Fstar[17][1]*Vpk[4][17][1])))+((Tstar[17][2]*Wpk[4][17][2])+((
          Tstar[17][0]*Wpk[4][17][0])+(Tstar[17][1]*Wpk[4][17][1]))))+temp[2]));
        temp[4] = ((((Fstar[22][2]*Vpk[4][22][2])+((Fstar[22][0]*Vpk[4][22][0])+
          (Fstar[22][1]*Vpk[4][22][1])))+((Tstar[22][2]*Wpk[4][22][2])+((
          Tstar[22][0]*Wpk[4][22][0])+(Tstar[22][1]*Wpk[4][22][1]))))+((((
          Fstar[21][2]*Vpk[4][21][2])+((Fstar[21][0]*Vpk[4][21][0])+(
          Fstar[21][1]*Vpk[4][21][1])))+((Tstar[21][2]*Wpk[4][21][2])+((
          Tstar[21][0]*Wpk[4][21][0])+(Tstar[21][1]*Wpk[4][21][1]))))+temp[3]));
        fs0[4] = (utau[4]-((((Fstar[26][2]*Vpk[4][26][2])+((Fstar[26][0]*
          Vpk[4][26][0])+(Fstar[26][1]*Vpk[4][26][1])))+((Tstar[26][2]*
          Wpk[4][26][2])+((Tstar[26][0]*Wpk[4][26][0])+(Tstar[26][1]*
          Wpk[4][26][1]))))+((((Fstar[23][2]*Vpk[4][23][2])+((Fstar[23][0]*
          Vpk[4][23][0])+(Fstar[23][1]*Vpk[4][23][1])))+((Tstar[23][2]*
          Wpk[4][23][2])+((Tstar[23][0]*Wpk[4][23][0])+(Tstar[23][1]*
          Wpk[4][23][1]))))+temp[4])));
        temp[0] = ((((Fstar[5][2]*Vpk[5][5][2])+((Fstar[5][0]*Vpk[5][5][0])+(
          Fstar[5][1]*Vpk[5][5][1])))+((pin[2][2]*Tstar[5][2])+((pin[2][0]*
          Tstar[5][0])+(pin[2][1]*Tstar[5][1]))))+(((Fstar[8][2]*Vpk[5][8][2])+(
          (Fstar[8][0]*Vpk[5][8][0])+(Fstar[8][1]*Vpk[5][8][1])))+((Tstar[8][2]*
          Wpk[5][8][2])+((Tstar[8][0]*Wpk[5][8][0])+(Tstar[8][1]*Wpk[5][8][1])))
          ));
        temp[1] = ((((Fstar[12][2]*Vpk[5][12][2])+((Fstar[12][0]*Vpk[5][12][0])+
          (Fstar[12][1]*Vpk[5][12][1])))+((Tstar[12][2]*Wpk[5][12][2])+((
          Tstar[12][0]*Wpk[5][12][0])+(Tstar[12][1]*Wpk[5][12][1]))))+((((
          Fstar[11][2]*Vpk[5][11][2])+((Fstar[11][0]*Vpk[5][11][0])+(
          Fstar[11][1]*Vpk[5][11][1])))+((Tstar[11][2]*Wpk[5][11][2])+((
          Tstar[11][0]*Wpk[5][11][0])+(Tstar[11][1]*Wpk[5][11][1]))))+temp[0]));
        temp[2] = ((((Fstar[14][2]*Vpk[5][14][2])+((Fstar[14][0]*Vpk[5][14][0])+
          (Fstar[14][1]*Vpk[5][14][1])))+((Tstar[14][2]*Wpk[5][14][2])+((
          Tstar[14][0]*Wpk[5][14][0])+(Tstar[14][1]*Wpk[5][14][1]))))+((((
          Fstar[13][2]*Vpk[5][13][2])+((Fstar[13][0]*Vpk[5][13][0])+(
          Fstar[13][1]*Vpk[5][13][1])))+((Tstar[13][2]*Wpk[5][13][2])+((
          Tstar[13][0]*Wpk[5][13][0])+(Tstar[13][1]*Wpk[5][13][1]))))+temp[1]));
        temp[3] = ((((Fstar[20][2]*Vpk[5][20][2])+((Fstar[20][0]*Vpk[5][20][0])+
          (Fstar[20][1]*Vpk[5][20][1])))+((Tstar[20][2]*Wpk[5][20][2])+((
          Tstar[20][0]*Wpk[5][20][0])+(Tstar[20][1]*Wpk[5][20][1]))))+((((
          Fstar[17][2]*Vpk[5][17][2])+((Fstar[17][0]*Vpk[5][17][0])+(
          Fstar[17][1]*Vpk[5][17][1])))+((Tstar[17][2]*Wpk[5][17][2])+((
          Tstar[17][0]*Wpk[5][17][0])+(Tstar[17][1]*Wpk[5][17][1]))))+temp[2]));
        temp[4] = ((((Fstar[22][2]*Vpk[5][22][2])+((Fstar[22][0]*Vpk[5][22][0])+
          (Fstar[22][1]*Vpk[5][22][1])))+((Tstar[22][2]*Wpk[5][22][2])+((
          Tstar[22][0]*Wpk[5][22][0])+(Tstar[22][1]*Wpk[5][22][1]))))+((((
          Fstar[21][2]*Vpk[5][21][2])+((Fstar[21][0]*Vpk[5][21][0])+(
          Fstar[21][1]*Vpk[5][21][1])))+((Tstar[21][2]*Wpk[5][21][2])+((
          Tstar[21][0]*Wpk[5][21][0])+(Tstar[21][1]*Wpk[5][21][1]))))+temp[3]));
        fs0[5] = (utau[5]-((((Fstar[26][2]*Vpk[5][26][2])+((Fstar[26][0]*
          Vpk[5][26][0])+(Fstar[26][1]*Vpk[5][26][1])))+((Tstar[26][2]*
          Wpk[5][26][2])+((Tstar[26][0]*Wpk[5][26][0])+(Tstar[26][1]*
          Wpk[5][26][1]))))+((((Fstar[23][2]*Vpk[5][23][2])+((Fstar[23][0]*
          Vpk[5][23][0])+(Fstar[23][1]*Vpk[5][23][1])))+((Tstar[23][2]*
          Wpk[5][23][2])+((Tstar[23][0]*Wpk[5][23][0])+(Tstar[23][1]*
          Wpk[5][23][1]))))+temp[4])));
        temp[0] = ((((Fstar[8][2]*Vpk[6][8][2])+((Fstar[8][0]*Vpk[6][8][0])+(
          Fstar[8][1]*Vpk[6][8][1])))+((Tstar[8][2]*Wpk[6][8][2])+((Tstar[8][0]*
          Wpk[6][8][0])+(Tstar[8][1]*Wpk[6][8][1]))))+(((Fstar[11][2]*
          Vpk[6][11][2])+((Fstar[11][0]*Vpk[6][11][0])+(Fstar[11][1]*
          Vpk[6][11][1])))+((Tstar[11][2]*Wpk[6][11][2])+((Tstar[11][0]*
          Wpk[6][11][0])+(Tstar[11][1]*Wpk[6][11][1])))));
        temp[1] = ((((Fstar[13][2]*Vpk[6][13][2])+((Fstar[13][0]*Vpk[6][13][0])+
          (Fstar[13][1]*Vpk[6][13][1])))+((Tstar[13][2]*Wpk[6][13][2])+((
          Tstar[13][0]*Wpk[6][13][0])+(Tstar[13][1]*Wpk[6][13][1]))))+((((
          Fstar[12][2]*Vpk[6][12][2])+((Fstar[12][0]*Vpk[6][12][0])+(
          Fstar[12][1]*Vpk[6][12][1])))+((Tstar[12][2]*Wpk[6][12][2])+((
          Tstar[12][0]*Wpk[6][12][0])+(Tstar[12][1]*Wpk[6][12][1]))))+temp[0]));
        fs0[6] = (utau[6]-((((Fstar[14][2]*Vpk[6][14][2])+((Fstar[14][0]*
          Vpk[6][14][0])+(Fstar[14][1]*Vpk[6][14][1])))+((Tstar[14][2]*
          Wpk[6][14][2])+((Tstar[14][0]*Wpk[6][14][0])+(Tstar[14][1]*
          Wpk[6][14][1]))))+temp[1]));
        temp[0] = ((((Fstar[8][2]*Vpk[7][8][2])+((Fstar[8][0]*Vpk[7][8][0])+(
          Fstar[8][1]*Vpk[7][8][1])))+((Tstar[8][2]*Wpk[7][8][2])+((Tstar[8][0]*
          Wpk[7][8][0])+(Tstar[8][1]*Wpk[7][8][1]))))+(((Fstar[11][2]*
          Vpk[7][11][2])+((Fstar[11][0]*Vpk[7][11][0])+(Fstar[11][1]*
          Vpk[7][11][1])))+((Tstar[11][2]*Wpk[7][11][2])+((Tstar[11][0]*
          Wpk[7][11][0])+(Tstar[11][1]*Wpk[7][11][1])))));
        temp[1] = ((((Fstar[13][2]*Vpk[7][13][2])+((Fstar[13][0]*Vpk[7][13][0])+
          (Fstar[13][1]*Vpk[7][13][1])))+((Tstar[13][2]*Wpk[7][13][2])+((
          Tstar[13][0]*Wpk[7][13][0])+(Tstar[13][1]*Wpk[7][13][1]))))+((((
          Fstar[12][2]*Vpk[7][12][2])+((Fstar[12][0]*Vpk[7][12][0])+(
          Fstar[12][1]*Vpk[7][12][1])))+((Tstar[12][2]*Wpk[7][12][2])+((
          Tstar[12][0]*Wpk[7][12][0])+(Tstar[12][1]*Wpk[7][12][1]))))+temp[0]));
        fs0[7] = (utau[7]-((((Fstar[14][2]*Vpk[7][14][2])+((Fstar[14][0]*
          Vpk[7][14][0])+(Fstar[14][1]*Vpk[7][14][1])))+((Tstar[14][2]*
          Wpk[7][14][2])+((Tstar[14][0]*Wpk[7][14][0])+(Tstar[14][1]*
          Wpk[7][14][1]))))+temp[1]));
        temp[0] = ((((Fstar[8][2]*Vpk[8][8][2])+((Fstar[8][0]*Vpk[8][8][0])+(
          Fstar[8][1]*Vpk[8][8][1])))+((pin[8][2]*Tstar[8][2])+((pin[8][0]*
          Tstar[8][0])+(pin[8][1]*Tstar[8][1]))))+(((Fstar[11][2]*Vpk[8][11][2])
          +((Fstar[11][0]*Vpk[8][11][0])+(Fstar[11][1]*Vpk[8][11][1])))+((
          Tstar[11][2]*Wpk[8][11][2])+((Tstar[11][0]*Wpk[8][11][0])+(
          Tstar[11][1]*Wpk[8][11][1])))));
        temp[1] = ((((Fstar[13][2]*Vpk[8][13][2])+((Fstar[13][0]*Vpk[8][13][0])+
          (Fstar[13][1]*Vpk[8][13][1])))+((Tstar[13][2]*Wpk[8][13][2])+((
          Tstar[13][0]*Wpk[8][13][0])+(Tstar[13][1]*Wpk[8][13][1]))))+((((
          Fstar[12][2]*Vpk[8][12][2])+((Fstar[12][0]*Vpk[8][12][0])+(
          Fstar[12][1]*Vpk[8][12][1])))+((Tstar[12][2]*Wpk[8][12][2])+((
          Tstar[12][0]*Wpk[8][12][0])+(Tstar[12][1]*Wpk[8][12][1]))))+temp[0]));
        fs0[8] = (utau[8]-((((Fstar[14][2]*Vpk[8][14][2])+((Fstar[14][0]*
          Vpk[8][14][0])+(Fstar[14][1]*Vpk[8][14][1])))+((Tstar[14][2]*
          Wpk[8][14][2])+((Tstar[14][0]*Wpk[8][14][0])+(Tstar[14][1]*
          Wpk[8][14][1]))))+temp[1]));
        fs0[9] = (utau[9]-(((Fstar[14][2]*Vpk[9][14][2])+((Fstar[14][0]*
          Vpk[9][14][0])+(Fstar[14][1]*Vpk[9][14][1])))+(((Fstar[13][2]*
          Vpk[9][13][2])+((Fstar[13][0]*Vpk[9][13][0])+(Fstar[13][1]*
          Vpk[9][13][1])))+(((Fstar[11][2]*Vpk[9][11][2])+((Fstar[11][0]*
          Vpk[9][11][0])+(Fstar[11][1]*Vpk[9][11][1])))+((Fstar[12][2]*
          Vpk[9][12][2])+((Fstar[12][0]*Vpk[9][12][0])+(Fstar[12][1]*
          Vpk[9][12][1])))))));
        fs0[10] = (utau[10]-(((Fstar[14][2]*Vpk[10][14][2])+((Fstar[14][0]*
          Vpk[10][14][0])+(Fstar[14][1]*Vpk[10][14][1])))+(((Fstar[13][2]*
          Vpk[10][13][2])+((Fstar[13][0]*Vpk[10][13][0])+(Fstar[13][1]*
          Vpk[10][13][1])))+(((Fstar[11][2]*Vpk[10][11][2])+((Fstar[11][0]*
          Vpk[10][11][0])+(Fstar[11][1]*Vpk[10][11][1])))+((Fstar[12][2]*
          Vpk[10][12][2])+((Fstar[12][0]*Vpk[10][12][0])+(Fstar[12][1]*
          Vpk[10][12][1])))))));
        temp[0] = ((((Fstar[11][2]*Vpk[11][11][2])+((Fstar[11][0]*Vpk[11][11][0]
          )+(Fstar[11][1]*Vpk[11][11][1])))+((pin[11][2]*Tstar[11][2])+((
          pin[11][0]*Tstar[11][0])+(pin[11][1]*Tstar[11][1]))))+(((Fstar[12][2]*
          Vpk[11][12][2])+((Fstar[12][0]*Vpk[11][12][0])+(Fstar[12][1]*
          Vpk[11][12][1])))+((Tstar[12][2]*Wpk[11][12][2])+((Tstar[12][0]*
          Wpk[11][12][0])+(Tstar[12][1]*Wpk[11][12][1])))));
        fs0[11] = (utau[11]-((((Fstar[14][2]*Vpk[11][14][2])+((Fstar[14][0]*
          Vpk[11][14][0])+(Fstar[14][1]*Vpk[11][14][1])))+((Tstar[14][2]*
          Wpk[11][14][2])+((Tstar[14][0]*Wpk[11][14][0])+(Tstar[14][1]*
          Wpk[11][14][1]))))+((((Fstar[13][2]*Vpk[11][13][2])+((Fstar[13][0]*
          Vpk[11][13][0])+(Fstar[13][1]*Vpk[11][13][1])))+((Tstar[13][2]*
          Wpk[11][13][2])+((Tstar[13][0]*Wpk[11][13][0])+(Tstar[13][1]*
          Wpk[11][13][1]))))+temp[0])));
        temp[0] = ((((Fstar[12][2]*Vpk[12][12][2])+((Fstar[12][0]*Vpk[12][12][0]
          )+(Fstar[12][1]*Vpk[12][12][1])))+((pin[12][2]*Tstar[12][2])+((
          pin[12][0]*Tstar[12][0])+(pin[12][1]*Tstar[12][1]))))+(((Fstar[13][2]*
          Vpk[12][13][2])+((Fstar[13][0]*Vpk[12][13][0])+(Fstar[13][1]*
          Vpk[12][13][1])))+((Tstar[13][2]*Wpk[12][13][2])+((Tstar[13][0]*
          Wpk[12][13][0])+(Tstar[13][1]*Wpk[12][13][1])))));
        fs0[12] = (utau[12]-((((Fstar[14][2]*Vpk[12][14][2])+((Fstar[14][0]*
          Vpk[12][14][0])+(Fstar[14][1]*Vpk[12][14][1])))+((Tstar[14][2]*
          Wpk[12][14][2])+((Tstar[14][0]*Wpk[12][14][0])+(Tstar[14][1]*
          Wpk[12][14][1]))))+temp[0]));
        fs0[13] = (utau[13]-((((Fstar[13][2]*Vpk[13][13][2])+((Fstar[13][0]*
          Vpk[13][13][0])+(Fstar[13][1]*Vpk[13][13][1])))+((pin[13][2]*
          Tstar[13][2])+((pin[13][0]*Tstar[13][0])+(pin[13][1]*Tstar[13][1]))))+
          (((Fstar[14][2]*Vpk[13][14][2])+((Fstar[14][0]*Vpk[13][14][0])+(
          Fstar[14][1]*Vpk[13][14][1])))+((Tstar[14][2]*Wpk[13][14][2])+((
          Tstar[14][0]*Wpk[13][14][0])+(Tstar[14][1]*Wpk[13][14][1]))))));
        fs0[14] = (utau[14]-(((Fstar[14][2]*Vpk[14][14][2])+((Fstar[14][0]*
          Vpk[14][14][0])+(Fstar[14][1]*Vpk[14][14][1])))+((pin[14][2]*
          Tstar[14][2])+((pin[14][0]*Tstar[14][0])+(pin[14][1]*Tstar[14][1])))))
          ;
        temp[0] = ((((Fstar[17][2]*Vpk[15][17][2])+((Fstar[17][0]*Vpk[15][17][0]
          )+(Fstar[17][1]*Vpk[15][17][1])))+((Tstar[17][2]*Wpk[15][17][2])+((
          Tstar[17][0]*Wpk[15][17][0])+(Tstar[17][1]*Wpk[15][17][1]))))+(((
          Fstar[20][2]*Vpk[15][20][2])+((Fstar[20][0]*Vpk[15][20][0])+(
          Fstar[20][1]*Vpk[15][20][1])))+((Tstar[20][2]*Wpk[15][20][2])+((
          Tstar[20][0]*Wpk[15][20][0])+(Tstar[20][1]*Wpk[15][20][1])))));
        temp[1] = ((((Fstar[22][2]*Vpk[15][22][2])+((Fstar[22][0]*Vpk[15][22][0]
          )+(Fstar[22][1]*Vpk[15][22][1])))+((Tstar[22][2]*Wpk[15][22][2])+((
          Tstar[22][0]*Wpk[15][22][0])+(Tstar[22][1]*Wpk[15][22][1]))))+((((
          Fstar[21][2]*Vpk[15][21][2])+((Fstar[21][0]*Vpk[15][21][0])+(
          Fstar[21][1]*Vpk[15][21][1])))+((Tstar[21][2]*Wpk[15][21][2])+((
          Tstar[21][0]*Wpk[15][21][0])+(Tstar[21][1]*Wpk[15][21][1]))))+temp[0])
          );
        fs0[15] = (utau[15]-((((Fstar[23][2]*Vpk[15][23][2])+((Fstar[23][0]*
          Vpk[15][23][0])+(Fstar[23][1]*Vpk[15][23][1])))+((Tstar[23][2]*
          Wpk[15][23][2])+((Tstar[23][0]*Wpk[15][23][0])+(Tstar[23][1]*
          Wpk[15][23][1]))))+temp[1]));
        temp[0] = ((((Fstar[17][2]*Vpk[16][17][2])+((Fstar[17][0]*Vpk[16][17][0]
          )+(Fstar[17][1]*Vpk[16][17][1])))+((Tstar[17][2]*Wpk[16][17][2])+((
          Tstar[17][0]*Wpk[16][17][0])+(Tstar[17][1]*Wpk[16][17][1]))))+(((
          Fstar[20][2]*Vpk[16][20][2])+((Fstar[20][0]*Vpk[16][20][0])+(
          Fstar[20][1]*Vpk[16][20][1])))+((Tstar[20][2]*Wpk[16][20][2])+((
          Tstar[20][0]*Wpk[16][20][0])+(Tstar[20][1]*Wpk[16][20][1])))));
        temp[1] = ((((Fstar[22][2]*Vpk[16][22][2])+((Fstar[22][0]*Vpk[16][22][0]
          )+(Fstar[22][1]*Vpk[16][22][1])))+((Tstar[22][2]*Wpk[16][22][2])+((
          Tstar[22][0]*Wpk[16][22][0])+(Tstar[22][1]*Wpk[16][22][1]))))+((((
          Fstar[21][2]*Vpk[16][21][2])+((Fstar[21][0]*Vpk[16][21][0])+(
          Fstar[21][1]*Vpk[16][21][1])))+((Tstar[21][2]*Wpk[16][21][2])+((
          Tstar[21][0]*Wpk[16][21][0])+(Tstar[21][1]*Wpk[16][21][1]))))+temp[0])
          );
        fs0[16] = (utau[16]-((((Fstar[23][2]*Vpk[16][23][2])+((Fstar[23][0]*
          Vpk[16][23][0])+(Fstar[23][1]*Vpk[16][23][1])))+((Tstar[23][2]*
          Wpk[16][23][2])+((Tstar[23][0]*Wpk[16][23][0])+(Tstar[23][1]*
          Wpk[16][23][1]))))+temp[1]));
        temp[0] = ((((Fstar[17][2]*Vpk[17][17][2])+((Fstar[17][0]*Vpk[17][17][0]
          )+(Fstar[17][1]*Vpk[17][17][1])))+((pin[17][2]*Tstar[17][2])+((
          pin[17][0]*Tstar[17][0])+(pin[17][1]*Tstar[17][1]))))+(((Fstar[20][2]*
          Vpk[17][20][2])+((Fstar[20][0]*Vpk[17][20][0])+(Fstar[20][1]*
          Vpk[17][20][1])))+((Tstar[20][2]*Wpk[17][20][2])+((Tstar[20][0]*
          Wpk[17][20][0])+(Tstar[20][1]*Wpk[17][20][1])))));
        temp[1] = ((((Fstar[22][2]*Vpk[17][22][2])+((Fstar[22][0]*Vpk[17][22][0]
          )+(Fstar[22][1]*Vpk[17][22][1])))+((Tstar[22][2]*Wpk[17][22][2])+((
          Tstar[22][0]*Wpk[17][22][0])+(Tstar[22][1]*Wpk[17][22][1]))))+((((
          Fstar[21][2]*Vpk[17][21][2])+((Fstar[21][0]*Vpk[17][21][0])+(
          Fstar[21][1]*Vpk[17][21][1])))+((Tstar[21][2]*Wpk[17][21][2])+((
          Tstar[21][0]*Wpk[17][21][0])+(Tstar[21][1]*Wpk[17][21][1]))))+temp[0])
          );
        fs0[17] = (utau[17]-((((Fstar[23][2]*Vpk[17][23][2])+((Fstar[23][0]*
          Vpk[17][23][0])+(Fstar[23][1]*Vpk[17][23][1])))+((Tstar[23][2]*
          Wpk[17][23][2])+((Tstar[23][0]*Wpk[17][23][0])+(Tstar[23][1]*
          Wpk[17][23][1]))))+temp[1]));
        fs0[18] = (utau[18]-(((Fstar[23][2]*Vpk[18][23][2])+((Fstar[23][0]*
          Vpk[18][23][0])+(Fstar[23][1]*Vpk[18][23][1])))+(((Fstar[22][2]*
          Vpk[18][22][2])+((Fstar[22][0]*Vpk[18][22][0])+(Fstar[22][1]*
          Vpk[18][22][1])))+(((Fstar[20][2]*Vpk[18][20][2])+((Fstar[20][0]*
          Vpk[18][20][0])+(Fstar[20][1]*Vpk[18][20][1])))+((Fstar[21][2]*
          Vpk[18][21][2])+((Fstar[21][0]*Vpk[18][21][0])+(Fstar[21][1]*
          Vpk[18][21][1])))))));
        fs0[19] = (utau[19]-(((Fstar[23][2]*Vpk[19][23][2])+((Fstar[23][0]*
          Vpk[19][23][0])+(Fstar[23][1]*Vpk[19][23][1])))+(((Fstar[22][2]*
          Vpk[19][22][2])+((Fstar[22][0]*Vpk[19][22][0])+(Fstar[22][1]*
          Vpk[19][22][1])))+(((Fstar[20][2]*Vpk[19][20][2])+((Fstar[20][0]*
          Vpk[19][20][0])+(Fstar[20][1]*Vpk[19][20][1])))+((Fstar[21][2]*
          Vpk[19][21][2])+((Fstar[21][0]*Vpk[19][21][0])+(Fstar[21][1]*
          Vpk[19][21][1])))))));
        temp[0] = ((((Fstar[20][2]*Vpk[20][20][2])+((Fstar[20][0]*Vpk[20][20][0]
          )+(Fstar[20][1]*Vpk[20][20][1])))+((pin[20][2]*Tstar[20][2])+((
          pin[20][0]*Tstar[20][0])+(pin[20][1]*Tstar[20][1]))))+(((Fstar[21][2]*
          Vpk[20][21][2])+((Fstar[21][0]*Vpk[20][21][0])+(Fstar[21][1]*
          Vpk[20][21][1])))+((Tstar[21][2]*Wpk[20][21][2])+((Tstar[21][0]*
          Wpk[20][21][0])+(Tstar[21][1]*Wpk[20][21][1])))));
        fs0[20] = (utau[20]-((((Fstar[23][2]*Vpk[20][23][2])+((Fstar[23][0]*
          Vpk[20][23][0])+(Fstar[23][1]*Vpk[20][23][1])))+((Tstar[23][2]*
          Wpk[20][23][2])+((Tstar[23][0]*Wpk[20][23][0])+(Tstar[23][1]*
          Wpk[20][23][1]))))+((((Fstar[22][2]*Vpk[20][22][2])+((Fstar[22][0]*
          Vpk[20][22][0])+(Fstar[22][1]*Vpk[20][22][1])))+((Tstar[22][2]*
          Wpk[20][22][2])+((Tstar[22][0]*Wpk[20][22][0])+(Tstar[22][1]*
          Wpk[20][22][1]))))+temp[0])));
        temp[0] = ((((Fstar[21][2]*Vpk[21][21][2])+((Fstar[21][0]*Vpk[21][21][0]
          )+(Fstar[21][1]*Vpk[21][21][1])))+((pin[21][2]*Tstar[21][2])+((
          pin[21][0]*Tstar[21][0])+(pin[21][1]*Tstar[21][1]))))+(((Fstar[22][2]*
          Vpk[21][22][2])+((Fstar[22][0]*Vpk[21][22][0])+(Fstar[22][1]*
          Vpk[21][22][1])))+((Tstar[22][2]*Wpk[21][22][2])+((Tstar[22][0]*
          Wpk[21][22][0])+(Tstar[22][1]*Wpk[21][22][1])))));
        fs0[21] = (utau[21]-((((Fstar[23][2]*Vpk[21][23][2])+((Fstar[23][0]*
          Vpk[21][23][0])+(Fstar[23][1]*Vpk[21][23][1])))+((Tstar[23][2]*
          Wpk[21][23][2])+((Tstar[23][0]*Wpk[21][23][0])+(Tstar[23][1]*
          Wpk[21][23][1]))))+temp[0]));
        fs0[22] = (utau[22]-((((Fstar[22][2]*Vpk[22][22][2])+((Fstar[22][0]*
          Vpk[22][22][0])+(Fstar[22][1]*Vpk[22][22][1])))+((pin[22][2]*
          Tstar[22][2])+((pin[22][0]*Tstar[22][0])+(pin[22][1]*Tstar[22][1]))))+
          (((Fstar[23][2]*Vpk[22][23][2])+((Fstar[23][0]*Vpk[22][23][0])+(
          Fstar[23][1]*Vpk[22][23][1])))+((Tstar[23][2]*Wpk[22][23][2])+((
          Tstar[23][0]*Wpk[22][23][0])+(Tstar[23][1]*Wpk[22][23][1]))))));
        fs0[23] = (utau[23]-(((Fstar[23][2]*Vpk[23][23][2])+((Fstar[23][0]*
          Vpk[23][23][0])+(Fstar[23][1]*Vpk[23][23][1])))+((pin[23][2]*
          Tstar[23][2])+((pin[23][0]*Tstar[23][0])+(pin[23][1]*Tstar[23][1])))))
          ;
        fs0[24] = (utau[24]-(((Fstar[26][2]*Vpk[24][26][2])+((Fstar[26][0]*
          Vpk[24][26][0])+(Fstar[26][1]*Vpk[24][26][1])))+((Tstar[26][2]*
          Wpk[24][26][2])+((Tstar[26][0]*Wpk[24][26][0])+(Tstar[26][1]*
          Wpk[24][26][1])))));
        fs0[25] = (utau[25]-(((Fstar[26][2]*Vpk[25][26][2])+((Fstar[26][0]*
          Vpk[25][26][0])+(Fstar[26][1]*Vpk[25][26][1])))+((Tstar[26][2]*
          Wpk[25][26][2])+((Tstar[26][0]*Wpk[25][26][0])+(Tstar[26][1]*
          Wpk[25][26][1])))));
        fs0[26] = (utau[26]-(((Fstar[26][2]*Vpk[26][26][2])+((Fstar[26][0]*
          Vpk[26][26][0])+(Fstar[26][1]*Vpk[26][26][1])))+((pin[26][2]*
          Tstar[26][2])+((pin[26][0]*Tstar[26][0])+(pin[26][1]*Tstar[26][1])))))
          ;
        fs0flg = 1;
    }
/*
 Used 0.24 seconds CPU time,
 24576 additional bytes of memory.
 Equations contain  906 adds/subtracts/negates
                    834 multiplies
                      0 divides
                    136 assignments
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
        IkWpk[3][5][0] = ((ik[0][0][2]*Wpk[3][5][2])+((ik[0][0][0]*Wpk[3][5][0])
          +(ik[0][0][1]*Wpk[3][5][1])));
        IkWpk[3][5][1] = ((ik[0][1][2]*Wpk[3][5][2])+((ik[0][1][0]*Wpk[3][5][0])
          +(ik[0][1][1]*Wpk[3][5][1])));
        IkWpk[3][5][2] = ((ik[0][2][2]*Wpk[3][5][2])+((ik[0][2][0]*Wpk[3][5][0])
          +(ik[0][2][1]*Wpk[3][5][1])));
        IkWpk[3][8][0] = ((ik[1][0][2]*Wpk[3][8][2])+((ik[1][0][0]*Wpk[3][8][0])
          +(ik[1][0][1]*Wpk[3][8][1])));
        IkWpk[3][8][1] = ((ik[1][1][2]*Wpk[3][8][2])+((ik[1][1][0]*Wpk[3][8][0])
          +(ik[1][1][1]*Wpk[3][8][1])));
        IkWpk[3][8][2] = ((ik[1][2][2]*Wpk[3][8][2])+((ik[1][2][0]*Wpk[3][8][0])
          +(ik[1][2][1]*Wpk[3][8][1])));
        IkWpk[3][11][0] = ((ik[2][0][2]*Wpk[3][11][2])+((ik[2][0][0]*
          Wpk[3][11][0])+(ik[2][0][1]*Wpk[3][11][1])));
        IkWpk[3][11][1] = ((ik[2][1][2]*Wpk[3][11][2])+((ik[2][1][0]*
          Wpk[3][11][0])+(ik[2][1][1]*Wpk[3][11][1])));
        IkWpk[3][11][2] = ((ik[2][2][2]*Wpk[3][11][2])+((ik[2][2][0]*
          Wpk[3][11][0])+(ik[2][2][1]*Wpk[3][11][1])));
        IkWpk[3][12][0] = ((ik[3][0][2]*Wpk[3][12][2])+((ik[3][0][0]*
          Wpk[3][12][0])+(ik[3][0][1]*Wpk[3][12][1])));
        IkWpk[3][12][1] = ((ik[3][1][2]*Wpk[3][12][2])+((ik[3][1][0]*
          Wpk[3][12][0])+(ik[3][1][1]*Wpk[3][12][1])));
        IkWpk[3][12][2] = ((ik[3][2][2]*Wpk[3][12][2])+((ik[3][2][0]*
          Wpk[3][12][0])+(ik[3][2][1]*Wpk[3][12][1])));
        IkWpk[3][13][0] = ((ik[4][0][2]*Wpk[3][13][2])+((ik[4][0][0]*
          Wpk[3][13][0])+(ik[4][0][1]*Wpk[3][13][1])));
        IkWpk[3][13][1] = ((ik[4][1][2]*Wpk[3][13][2])+((ik[4][1][0]*
          Wpk[3][13][0])+(ik[4][1][1]*Wpk[3][13][1])));
        IkWpk[3][13][2] = ((ik[4][2][2]*Wpk[3][13][2])+((ik[4][2][0]*
          Wpk[3][13][0])+(ik[4][2][1]*Wpk[3][13][1])));
        IkWpk[3][14][0] = ((ik[5][0][2]*Wpk[3][14][2])+((ik[5][0][0]*
          Wpk[3][14][0])+(ik[5][0][1]*Wpk[3][14][1])));
        IkWpk[3][14][1] = ((ik[5][1][2]*Wpk[3][14][2])+((ik[5][1][0]*
          Wpk[3][14][0])+(ik[5][1][1]*Wpk[3][14][1])));
        IkWpk[3][14][2] = ((ik[5][2][2]*Wpk[3][14][2])+((ik[5][2][0]*
          Wpk[3][14][0])+(ik[5][2][1]*Wpk[3][14][1])));
        IkWpk[3][17][0] = ((ik[6][0][2]*Wpk[3][17][2])+((ik[6][0][0]*
          Wpk[3][17][0])+(ik[6][0][1]*Wpk[3][17][1])));
        IkWpk[3][17][1] = ((ik[6][1][2]*Wpk[3][17][2])+((ik[6][1][0]*
          Wpk[3][17][0])+(ik[6][1][1]*Wpk[3][17][1])));
        IkWpk[3][17][2] = ((ik[6][2][2]*Wpk[3][17][2])+((ik[6][2][0]*
          Wpk[3][17][0])+(ik[6][2][1]*Wpk[3][17][1])));
        IkWpk[3][20][0] = ((ik[7][0][2]*Wpk[3][20][2])+((ik[7][0][0]*
          Wpk[3][20][0])+(ik[7][0][1]*Wpk[3][20][1])));
        IkWpk[3][20][1] = ((ik[7][1][2]*Wpk[3][20][2])+((ik[7][1][0]*
          Wpk[3][20][0])+(ik[7][1][1]*Wpk[3][20][1])));
        IkWpk[3][20][2] = ((ik[7][2][2]*Wpk[3][20][2])+((ik[7][2][0]*
          Wpk[3][20][0])+(ik[7][2][1]*Wpk[3][20][1])));
        IkWpk[3][21][0] = ((ik[8][0][2]*Wpk[3][21][2])+((ik[8][0][0]*
          Wpk[3][21][0])+(ik[8][0][1]*Wpk[3][21][1])));
        IkWpk[3][21][1] = ((ik[8][1][2]*Wpk[3][21][2])+((ik[8][1][0]*
          Wpk[3][21][0])+(ik[8][1][1]*Wpk[3][21][1])));
        IkWpk[3][21][2] = ((ik[8][2][2]*Wpk[3][21][2])+((ik[8][2][0]*
          Wpk[3][21][0])+(ik[8][2][1]*Wpk[3][21][1])));
        IkWpk[3][22][0] = ((ik[9][0][2]*Wpk[3][22][2])+((ik[9][0][0]*
          Wpk[3][22][0])+(ik[9][0][1]*Wpk[3][22][1])));
        IkWpk[3][22][1] = ((ik[9][1][2]*Wpk[3][22][2])+((ik[9][1][0]*
          Wpk[3][22][0])+(ik[9][1][1]*Wpk[3][22][1])));
        IkWpk[3][22][2] = ((ik[9][2][2]*Wpk[3][22][2])+((ik[9][2][0]*
          Wpk[3][22][0])+(ik[9][2][1]*Wpk[3][22][1])));
        IkWpk[3][23][0] = ((ik[10][0][2]*Wpk[3][23][2])+((ik[10][0][0]*
          Wpk[3][23][0])+(ik[10][0][1]*Wpk[3][23][1])));
        IkWpk[3][23][1] = ((ik[10][1][2]*Wpk[3][23][2])+((ik[10][1][0]*
          Wpk[3][23][0])+(ik[10][1][1]*Wpk[3][23][1])));
        IkWpk[3][23][2] = ((ik[10][2][2]*Wpk[3][23][2])+((ik[10][2][0]*
          Wpk[3][23][0])+(ik[10][2][1]*Wpk[3][23][1])));
        IkWpk[3][26][0] = ((ik[11][0][2]*Wpk[3][26][2])+((ik[11][0][0]*
          Wpk[3][26][0])+(ik[11][0][1]*Wpk[3][26][1])));
        IkWpk[3][26][1] = ((ik[11][1][2]*Wpk[3][26][2])+((ik[11][1][0]*
          Wpk[3][26][0])+(ik[11][1][1]*Wpk[3][26][1])));
        IkWpk[3][26][2] = ((ik[11][2][2]*Wpk[3][26][2])+((ik[11][2][0]*
          Wpk[3][26][0])+(ik[11][2][1]*Wpk[3][26][1])));
        IkWpk[4][5][0] = ((ik[0][0][2]*Wpk[4][5][2])+((ik[0][0][0]*Wpk[4][5][0])
          +(ik[0][0][1]*Wpk[4][5][1])));
        IkWpk[4][5][1] = ((ik[0][1][2]*Wpk[4][5][2])+((ik[0][1][0]*Wpk[4][5][0])
          +(ik[0][1][1]*Wpk[4][5][1])));
        IkWpk[4][5][2] = ((ik[0][2][2]*Wpk[4][5][2])+((ik[0][2][0]*Wpk[4][5][0])
          +(ik[0][2][1]*Wpk[4][5][1])));
        IkWpk[4][8][0] = ((ik[1][0][2]*Wpk[4][8][2])+((ik[1][0][0]*Wpk[4][8][0])
          +(ik[1][0][1]*Wpk[4][8][1])));
        IkWpk[4][8][1] = ((ik[1][1][2]*Wpk[4][8][2])+((ik[1][1][0]*Wpk[4][8][0])
          +(ik[1][1][1]*Wpk[4][8][1])));
        IkWpk[4][8][2] = ((ik[1][2][2]*Wpk[4][8][2])+((ik[1][2][0]*Wpk[4][8][0])
          +(ik[1][2][1]*Wpk[4][8][1])));
        IkWpk[4][11][0] = ((ik[2][0][2]*Wpk[4][11][2])+((ik[2][0][0]*
          Wpk[4][11][0])+(ik[2][0][1]*Wpk[4][11][1])));
        IkWpk[4][11][1] = ((ik[2][1][2]*Wpk[4][11][2])+((ik[2][1][0]*
          Wpk[4][11][0])+(ik[2][1][1]*Wpk[4][11][1])));
        IkWpk[4][11][2] = ((ik[2][2][2]*Wpk[4][11][2])+((ik[2][2][0]*
          Wpk[4][11][0])+(ik[2][2][1]*Wpk[4][11][1])));
        IkWpk[4][12][0] = ((ik[3][0][2]*Wpk[4][12][2])+((ik[3][0][0]*
          Wpk[4][12][0])+(ik[3][0][1]*Wpk[4][12][1])));
        IkWpk[4][12][1] = ((ik[3][1][2]*Wpk[4][12][2])+((ik[3][1][0]*
          Wpk[4][12][0])+(ik[3][1][1]*Wpk[4][12][1])));
        IkWpk[4][12][2] = ((ik[3][2][2]*Wpk[4][12][2])+((ik[3][2][0]*
          Wpk[4][12][0])+(ik[3][2][1]*Wpk[4][12][1])));
        IkWpk[4][13][0] = ((ik[4][0][2]*Wpk[4][13][2])+((ik[4][0][0]*
          Wpk[4][13][0])+(ik[4][0][1]*Wpk[4][13][1])));
        IkWpk[4][13][1] = ((ik[4][1][2]*Wpk[4][13][2])+((ik[4][1][0]*
          Wpk[4][13][0])+(ik[4][1][1]*Wpk[4][13][1])));
        IkWpk[4][13][2] = ((ik[4][2][2]*Wpk[4][13][2])+((ik[4][2][0]*
          Wpk[4][13][0])+(ik[4][2][1]*Wpk[4][13][1])));
        IkWpk[4][14][0] = ((ik[5][0][2]*Wpk[4][14][2])+((ik[5][0][0]*
          Wpk[4][14][0])+(ik[5][0][1]*Wpk[4][14][1])));
        IkWpk[4][14][1] = ((ik[5][1][2]*Wpk[4][14][2])+((ik[5][1][0]*
          Wpk[4][14][0])+(ik[5][1][1]*Wpk[4][14][1])));
        IkWpk[4][14][2] = ((ik[5][2][2]*Wpk[4][14][2])+((ik[5][2][0]*
          Wpk[4][14][0])+(ik[5][2][1]*Wpk[4][14][1])));
        IkWpk[4][17][0] = ((ik[6][0][2]*Wpk[4][17][2])+((ik[6][0][0]*
          Wpk[4][17][0])+(ik[6][0][1]*Wpk[4][17][1])));
        IkWpk[4][17][1] = ((ik[6][1][2]*Wpk[4][17][2])+((ik[6][1][0]*
          Wpk[4][17][0])+(ik[6][1][1]*Wpk[4][17][1])));
        IkWpk[4][17][2] = ((ik[6][2][2]*Wpk[4][17][2])+((ik[6][2][0]*
          Wpk[4][17][0])+(ik[6][2][1]*Wpk[4][17][1])));
        IkWpk[4][20][0] = ((ik[7][0][2]*Wpk[4][20][2])+((ik[7][0][0]*
          Wpk[4][20][0])+(ik[7][0][1]*Wpk[4][20][1])));
        IkWpk[4][20][1] = ((ik[7][1][2]*Wpk[4][20][2])+((ik[7][1][0]*
          Wpk[4][20][0])+(ik[7][1][1]*Wpk[4][20][1])));
        IkWpk[4][20][2] = ((ik[7][2][2]*Wpk[4][20][2])+((ik[7][2][0]*
          Wpk[4][20][0])+(ik[7][2][1]*Wpk[4][20][1])));
        IkWpk[4][21][0] = ((ik[8][0][2]*Wpk[4][21][2])+((ik[8][0][0]*
          Wpk[4][21][0])+(ik[8][0][1]*Wpk[4][21][1])));
        IkWpk[4][21][1] = ((ik[8][1][2]*Wpk[4][21][2])+((ik[8][1][0]*
          Wpk[4][21][0])+(ik[8][1][1]*Wpk[4][21][1])));
        IkWpk[4][21][2] = ((ik[8][2][2]*Wpk[4][21][2])+((ik[8][2][0]*
          Wpk[4][21][0])+(ik[8][2][1]*Wpk[4][21][1])));
        IkWpk[4][22][0] = ((ik[9][0][2]*Wpk[4][22][2])+((ik[9][0][0]*
          Wpk[4][22][0])+(ik[9][0][1]*Wpk[4][22][1])));
        IkWpk[4][22][1] = ((ik[9][1][2]*Wpk[4][22][2])+((ik[9][1][0]*
          Wpk[4][22][0])+(ik[9][1][1]*Wpk[4][22][1])));
        IkWpk[4][22][2] = ((ik[9][2][2]*Wpk[4][22][2])+((ik[9][2][0]*
          Wpk[4][22][0])+(ik[9][2][1]*Wpk[4][22][1])));
        IkWpk[4][23][0] = ((ik[10][0][2]*Wpk[4][23][2])+((ik[10][0][0]*
          Wpk[4][23][0])+(ik[10][0][1]*Wpk[4][23][1])));
        IkWpk[4][23][1] = ((ik[10][1][2]*Wpk[4][23][2])+((ik[10][1][0]*
          Wpk[4][23][0])+(ik[10][1][1]*Wpk[4][23][1])));
        IkWpk[4][23][2] = ((ik[10][2][2]*Wpk[4][23][2])+((ik[10][2][0]*
          Wpk[4][23][0])+(ik[10][2][1]*Wpk[4][23][1])));
        IkWpk[4][26][0] = ((ik[11][0][2]*Wpk[4][26][2])+((ik[11][0][0]*
          Wpk[4][26][0])+(ik[11][0][1]*Wpk[4][26][1])));
        IkWpk[4][26][1] = ((ik[11][1][2]*Wpk[4][26][2])+((ik[11][1][0]*
          Wpk[4][26][0])+(ik[11][1][1]*Wpk[4][26][1])));
        IkWpk[4][26][2] = ((ik[11][2][2]*Wpk[4][26][2])+((ik[11][2][0]*
          Wpk[4][26][0])+(ik[11][2][1]*Wpk[4][26][1])));
        IkWpk[5][5][0] = ((ik[0][0][2]*pin[2][2])+((ik[0][0][0]*pin[2][0])+(
          ik[0][0][1]*pin[2][1])));
        IkWpk[5][5][1] = ((ik[0][1][2]*pin[2][2])+((ik[0][1][0]*pin[2][0])+(
          ik[0][1][1]*pin[2][1])));
        IkWpk[5][5][2] = ((ik[0][2][2]*pin[2][2])+((ik[0][2][0]*pin[2][0])+(
          ik[0][2][1]*pin[2][1])));
        IkWpk[5][8][0] = ((ik[1][0][2]*Wpk[5][8][2])+((ik[1][0][0]*Wpk[5][8][0])
          +(ik[1][0][1]*Wpk[5][8][1])));
        IkWpk[5][8][1] = ((ik[1][1][2]*Wpk[5][8][2])+((ik[1][1][0]*Wpk[5][8][0])
          +(ik[1][1][1]*Wpk[5][8][1])));
        IkWpk[5][8][2] = ((ik[1][2][2]*Wpk[5][8][2])+((ik[1][2][0]*Wpk[5][8][0])
          +(ik[1][2][1]*Wpk[5][8][1])));
        IkWpk[5][11][0] = ((ik[2][0][2]*Wpk[5][11][2])+((ik[2][0][0]*
          Wpk[5][11][0])+(ik[2][0][1]*Wpk[5][11][1])));
        IkWpk[5][11][1] = ((ik[2][1][2]*Wpk[5][11][2])+((ik[2][1][0]*
          Wpk[5][11][0])+(ik[2][1][1]*Wpk[5][11][1])));
        IkWpk[5][11][2] = ((ik[2][2][2]*Wpk[5][11][2])+((ik[2][2][0]*
          Wpk[5][11][0])+(ik[2][2][1]*Wpk[5][11][1])));
        IkWpk[5][12][0] = ((ik[3][0][2]*Wpk[5][12][2])+((ik[3][0][0]*
          Wpk[5][12][0])+(ik[3][0][1]*Wpk[5][12][1])));
        IkWpk[5][12][1] = ((ik[3][1][2]*Wpk[5][12][2])+((ik[3][1][0]*
          Wpk[5][12][0])+(ik[3][1][1]*Wpk[5][12][1])));
        IkWpk[5][12][2] = ((ik[3][2][2]*Wpk[5][12][2])+((ik[3][2][0]*
          Wpk[5][12][0])+(ik[3][2][1]*Wpk[5][12][1])));
        IkWpk[5][13][0] = ((ik[4][0][2]*Wpk[5][13][2])+((ik[4][0][0]*
          Wpk[5][13][0])+(ik[4][0][1]*Wpk[5][13][1])));
        IkWpk[5][13][1] = ((ik[4][1][2]*Wpk[5][13][2])+((ik[4][1][0]*
          Wpk[5][13][0])+(ik[4][1][1]*Wpk[5][13][1])));
        IkWpk[5][13][2] = ((ik[4][2][2]*Wpk[5][13][2])+((ik[4][2][0]*
          Wpk[5][13][0])+(ik[4][2][1]*Wpk[5][13][1])));
        IkWpk[5][14][0] = ((ik[5][0][2]*Wpk[5][14][2])+((ik[5][0][0]*
          Wpk[5][14][0])+(ik[5][0][1]*Wpk[5][14][1])));
        IkWpk[5][14][1] = ((ik[5][1][2]*Wpk[5][14][2])+((ik[5][1][0]*
          Wpk[5][14][0])+(ik[5][1][1]*Wpk[5][14][1])));
        IkWpk[5][14][2] = ((ik[5][2][2]*Wpk[5][14][2])+((ik[5][2][0]*
          Wpk[5][14][0])+(ik[5][2][1]*Wpk[5][14][1])));
        IkWpk[5][17][0] = ((ik[6][0][2]*Wpk[5][17][2])+((ik[6][0][0]*
          Wpk[5][17][0])+(ik[6][0][1]*Wpk[5][17][1])));
        IkWpk[5][17][1] = ((ik[6][1][2]*Wpk[5][17][2])+((ik[6][1][0]*
          Wpk[5][17][0])+(ik[6][1][1]*Wpk[5][17][1])));
        IkWpk[5][17][2] = ((ik[6][2][2]*Wpk[5][17][2])+((ik[6][2][0]*
          Wpk[5][17][0])+(ik[6][2][1]*Wpk[5][17][1])));
        IkWpk[5][20][0] = ((ik[7][0][2]*Wpk[5][20][2])+((ik[7][0][0]*
          Wpk[5][20][0])+(ik[7][0][1]*Wpk[5][20][1])));
        IkWpk[5][20][1] = ((ik[7][1][2]*Wpk[5][20][2])+((ik[7][1][0]*
          Wpk[5][20][0])+(ik[7][1][1]*Wpk[5][20][1])));
        IkWpk[5][20][2] = ((ik[7][2][2]*Wpk[5][20][2])+((ik[7][2][0]*
          Wpk[5][20][0])+(ik[7][2][1]*Wpk[5][20][1])));
        IkWpk[5][21][0] = ((ik[8][0][2]*Wpk[5][21][2])+((ik[8][0][0]*
          Wpk[5][21][0])+(ik[8][0][1]*Wpk[5][21][1])));
        IkWpk[5][21][1] = ((ik[8][1][2]*Wpk[5][21][2])+((ik[8][1][0]*
          Wpk[5][21][0])+(ik[8][1][1]*Wpk[5][21][1])));
        IkWpk[5][21][2] = ((ik[8][2][2]*Wpk[5][21][2])+((ik[8][2][0]*
          Wpk[5][21][0])+(ik[8][2][1]*Wpk[5][21][1])));
        IkWpk[5][22][0] = ((ik[9][0][2]*Wpk[5][22][2])+((ik[9][0][0]*
          Wpk[5][22][0])+(ik[9][0][1]*Wpk[5][22][1])));
        IkWpk[5][22][1] = ((ik[9][1][2]*Wpk[5][22][2])+((ik[9][1][0]*
          Wpk[5][22][0])+(ik[9][1][1]*Wpk[5][22][1])));
        IkWpk[5][22][2] = ((ik[9][2][2]*Wpk[5][22][2])+((ik[9][2][0]*
          Wpk[5][22][0])+(ik[9][2][1]*Wpk[5][22][1])));
        IkWpk[5][23][0] = ((ik[10][0][2]*Wpk[5][23][2])+((ik[10][0][0]*
          Wpk[5][23][0])+(ik[10][0][1]*Wpk[5][23][1])));
        IkWpk[5][23][1] = ((ik[10][1][2]*Wpk[5][23][2])+((ik[10][1][0]*
          Wpk[5][23][0])+(ik[10][1][1]*Wpk[5][23][1])));
        IkWpk[5][23][2] = ((ik[10][2][2]*Wpk[5][23][2])+((ik[10][2][0]*
          Wpk[5][23][0])+(ik[10][2][1]*Wpk[5][23][1])));
        IkWpk[5][26][0] = ((ik[11][0][2]*Wpk[5][26][2])+((ik[11][0][0]*
          Wpk[5][26][0])+(ik[11][0][1]*Wpk[5][26][1])));
        IkWpk[5][26][1] = ((ik[11][1][2]*Wpk[5][26][2])+((ik[11][1][0]*
          Wpk[5][26][0])+(ik[11][1][1]*Wpk[5][26][1])));
        IkWpk[5][26][2] = ((ik[11][2][2]*Wpk[5][26][2])+((ik[11][2][0]*
          Wpk[5][26][0])+(ik[11][2][1]*Wpk[5][26][1])));
        IkWpk[6][8][0] = ((ik[1][0][2]*Wpk[6][8][2])+((ik[1][0][0]*Wpk[6][8][0])
          +(ik[1][0][1]*Wpk[6][8][1])));
        IkWpk[6][8][1] = ((ik[1][1][2]*Wpk[6][8][2])+((ik[1][1][0]*Wpk[6][8][0])
          +(ik[1][1][1]*Wpk[6][8][1])));
        IkWpk[6][8][2] = ((ik[1][2][2]*Wpk[6][8][2])+((ik[1][2][0]*Wpk[6][8][0])
          +(ik[1][2][1]*Wpk[6][8][1])));
        IkWpk[6][11][0] = ((ik[2][0][2]*Wpk[6][11][2])+((ik[2][0][0]*
          Wpk[6][11][0])+(ik[2][0][1]*Wpk[6][11][1])));
        IkWpk[6][11][1] = ((ik[2][1][2]*Wpk[6][11][2])+((ik[2][1][0]*
          Wpk[6][11][0])+(ik[2][1][1]*Wpk[6][11][1])));
        IkWpk[6][11][2] = ((ik[2][2][2]*Wpk[6][11][2])+((ik[2][2][0]*
          Wpk[6][11][0])+(ik[2][2][1]*Wpk[6][11][1])));
        IkWpk[6][12][0] = ((ik[3][0][2]*Wpk[6][12][2])+((ik[3][0][0]*
          Wpk[6][12][0])+(ik[3][0][1]*Wpk[6][12][1])));
        IkWpk[6][12][1] = ((ik[3][1][2]*Wpk[6][12][2])+((ik[3][1][0]*
          Wpk[6][12][0])+(ik[3][1][1]*Wpk[6][12][1])));
        IkWpk[6][12][2] = ((ik[3][2][2]*Wpk[6][12][2])+((ik[3][2][0]*
          Wpk[6][12][0])+(ik[3][2][1]*Wpk[6][12][1])));
        IkWpk[6][13][0] = ((ik[4][0][2]*Wpk[6][13][2])+((ik[4][0][0]*
          Wpk[6][13][0])+(ik[4][0][1]*Wpk[6][13][1])));
        IkWpk[6][13][1] = ((ik[4][1][2]*Wpk[6][13][2])+((ik[4][1][0]*
          Wpk[6][13][0])+(ik[4][1][1]*Wpk[6][13][1])));
        IkWpk[6][13][2] = ((ik[4][2][2]*Wpk[6][13][2])+((ik[4][2][0]*
          Wpk[6][13][0])+(ik[4][2][1]*Wpk[6][13][1])));
        IkWpk[6][14][0] = ((ik[5][0][2]*Wpk[6][14][2])+((ik[5][0][0]*
          Wpk[6][14][0])+(ik[5][0][1]*Wpk[6][14][1])));
        IkWpk[6][14][1] = ((ik[5][1][2]*Wpk[6][14][2])+((ik[5][1][0]*
          Wpk[6][14][0])+(ik[5][1][1]*Wpk[6][14][1])));
        IkWpk[6][14][2] = ((ik[5][2][2]*Wpk[6][14][2])+((ik[5][2][0]*
          Wpk[6][14][0])+(ik[5][2][1]*Wpk[6][14][1])));
        IkWpk[7][8][0] = ((ik[1][0][2]*Wpk[7][8][2])+((ik[1][0][0]*Wpk[7][8][0])
          +(ik[1][0][1]*Wpk[7][8][1])));
        IkWpk[7][8][1] = ((ik[1][1][2]*Wpk[7][8][2])+((ik[1][1][0]*Wpk[7][8][0])
          +(ik[1][1][1]*Wpk[7][8][1])));
        IkWpk[7][8][2] = ((ik[1][2][2]*Wpk[7][8][2])+((ik[1][2][0]*Wpk[7][8][0])
          +(ik[1][2][1]*Wpk[7][8][1])));
        IkWpk[7][11][0] = ((ik[2][0][2]*Wpk[7][11][2])+((ik[2][0][0]*
          Wpk[7][11][0])+(ik[2][0][1]*Wpk[7][11][1])));
        IkWpk[7][11][1] = ((ik[2][1][2]*Wpk[7][11][2])+((ik[2][1][0]*
          Wpk[7][11][0])+(ik[2][1][1]*Wpk[7][11][1])));
        IkWpk[7][11][2] = ((ik[2][2][2]*Wpk[7][11][2])+((ik[2][2][0]*
          Wpk[7][11][0])+(ik[2][2][1]*Wpk[7][11][1])));
        IkWpk[7][12][0] = ((ik[3][0][2]*Wpk[7][12][2])+((ik[3][0][0]*
          Wpk[7][12][0])+(ik[3][0][1]*Wpk[7][12][1])));
        IkWpk[7][12][1] = ((ik[3][1][2]*Wpk[7][12][2])+((ik[3][1][0]*
          Wpk[7][12][0])+(ik[3][1][1]*Wpk[7][12][1])));
        IkWpk[7][12][2] = ((ik[3][2][2]*Wpk[7][12][2])+((ik[3][2][0]*
          Wpk[7][12][0])+(ik[3][2][1]*Wpk[7][12][1])));
        IkWpk[7][13][0] = ((ik[4][0][2]*Wpk[7][13][2])+((ik[4][0][0]*
          Wpk[7][13][0])+(ik[4][0][1]*Wpk[7][13][1])));
        IkWpk[7][13][1] = ((ik[4][1][2]*Wpk[7][13][2])+((ik[4][1][0]*
          Wpk[7][13][0])+(ik[4][1][1]*Wpk[7][13][1])));
        IkWpk[7][13][2] = ((ik[4][2][2]*Wpk[7][13][2])+((ik[4][2][0]*
          Wpk[7][13][0])+(ik[4][2][1]*Wpk[7][13][1])));
        IkWpk[7][14][0] = ((ik[5][0][2]*Wpk[7][14][2])+((ik[5][0][0]*
          Wpk[7][14][0])+(ik[5][0][1]*Wpk[7][14][1])));
        IkWpk[7][14][1] = ((ik[5][1][2]*Wpk[7][14][2])+((ik[5][1][0]*
          Wpk[7][14][0])+(ik[5][1][1]*Wpk[7][14][1])));
        IkWpk[7][14][2] = ((ik[5][2][2]*Wpk[7][14][2])+((ik[5][2][0]*
          Wpk[7][14][0])+(ik[5][2][1]*Wpk[7][14][1])));
        IkWpk[8][8][0] = ((ik[1][0][2]*pin[8][2])+((ik[1][0][0]*pin[8][0])+(
          ik[1][0][1]*pin[8][1])));
        IkWpk[8][8][1] = ((ik[1][1][2]*pin[8][2])+((ik[1][1][0]*pin[8][0])+(
          ik[1][1][1]*pin[8][1])));
        IkWpk[8][8][2] = ((ik[1][2][2]*pin[8][2])+((ik[1][2][0]*pin[8][0])+(
          ik[1][2][1]*pin[8][1])));
        IkWpk[8][11][0] = ((ik[2][0][2]*Wpk[8][11][2])+((ik[2][0][0]*
          Wpk[8][11][0])+(ik[2][0][1]*Wpk[8][11][1])));
        IkWpk[8][11][1] = ((ik[2][1][2]*Wpk[8][11][2])+((ik[2][1][0]*
          Wpk[8][11][0])+(ik[2][1][1]*Wpk[8][11][1])));
        IkWpk[8][11][2] = ((ik[2][2][2]*Wpk[8][11][2])+((ik[2][2][0]*
          Wpk[8][11][0])+(ik[2][2][1]*Wpk[8][11][1])));
        IkWpk[8][12][0] = ((ik[3][0][2]*Wpk[8][12][2])+((ik[3][0][0]*
          Wpk[8][12][0])+(ik[3][0][1]*Wpk[8][12][1])));
        IkWpk[8][12][1] = ((ik[3][1][2]*Wpk[8][12][2])+((ik[3][1][0]*
          Wpk[8][12][0])+(ik[3][1][1]*Wpk[8][12][1])));
        IkWpk[8][12][2] = ((ik[3][2][2]*Wpk[8][12][2])+((ik[3][2][0]*
          Wpk[8][12][0])+(ik[3][2][1]*Wpk[8][12][1])));
        IkWpk[8][13][0] = ((ik[4][0][2]*Wpk[8][13][2])+((ik[4][0][0]*
          Wpk[8][13][0])+(ik[4][0][1]*Wpk[8][13][1])));
        IkWpk[8][13][1] = ((ik[4][1][2]*Wpk[8][13][2])+((ik[4][1][0]*
          Wpk[8][13][0])+(ik[4][1][1]*Wpk[8][13][1])));
        IkWpk[8][13][2] = ((ik[4][2][2]*Wpk[8][13][2])+((ik[4][2][0]*
          Wpk[8][13][0])+(ik[4][2][1]*Wpk[8][13][1])));
        IkWpk[8][14][0] = ((ik[5][0][2]*Wpk[8][14][2])+((ik[5][0][0]*
          Wpk[8][14][0])+(ik[5][0][1]*Wpk[8][14][1])));
        IkWpk[8][14][1] = ((ik[5][1][2]*Wpk[8][14][2])+((ik[5][1][0]*
          Wpk[8][14][0])+(ik[5][1][1]*Wpk[8][14][1])));
        IkWpk[8][14][2] = ((ik[5][2][2]*Wpk[8][14][2])+((ik[5][2][0]*
          Wpk[8][14][0])+(ik[5][2][1]*Wpk[8][14][1])));
        IkWpk[11][11][0] = ((ik[2][0][2]*pin[11][2])+((ik[2][0][0]*pin[11][0])+(
          ik[2][0][1]*pin[11][1])));
        IkWpk[11][11][1] = ((ik[2][1][2]*pin[11][2])+((ik[2][1][0]*pin[11][0])+(
          ik[2][1][1]*pin[11][1])));
        IkWpk[11][11][2] = ((ik[2][2][2]*pin[11][2])+((ik[2][2][0]*pin[11][0])+(
          ik[2][2][1]*pin[11][1])));
        IkWpk[11][12][0] = ((ik[3][0][2]*Wpk[11][12][2])+((ik[3][0][0]*
          Wpk[11][12][0])+(ik[3][0][1]*Wpk[11][12][1])));
        IkWpk[11][12][1] = ((ik[3][1][2]*Wpk[11][12][2])+((ik[3][1][0]*
          Wpk[11][12][0])+(ik[3][1][1]*Wpk[11][12][1])));
        IkWpk[11][12][2] = ((ik[3][2][2]*Wpk[11][12][2])+((ik[3][2][0]*
          Wpk[11][12][0])+(ik[3][2][1]*Wpk[11][12][1])));
        IkWpk[11][13][0] = ((ik[4][0][2]*Wpk[11][13][2])+((ik[4][0][0]*
          Wpk[11][13][0])+(ik[4][0][1]*Wpk[11][13][1])));
        IkWpk[11][13][1] = ((ik[4][1][2]*Wpk[11][13][2])+((ik[4][1][0]*
          Wpk[11][13][0])+(ik[4][1][1]*Wpk[11][13][1])));
        IkWpk[11][13][2] = ((ik[4][2][2]*Wpk[11][13][2])+((ik[4][2][0]*
          Wpk[11][13][0])+(ik[4][2][1]*Wpk[11][13][1])));
        IkWpk[11][14][0] = ((ik[5][0][2]*Wpk[11][14][2])+((ik[5][0][0]*
          Wpk[11][14][0])+(ik[5][0][1]*Wpk[11][14][1])));
        IkWpk[11][14][1] = ((ik[5][1][2]*Wpk[11][14][2])+((ik[5][1][0]*
          Wpk[11][14][0])+(ik[5][1][1]*Wpk[11][14][1])));
        IkWpk[11][14][2] = ((ik[5][2][2]*Wpk[11][14][2])+((ik[5][2][0]*
          Wpk[11][14][0])+(ik[5][2][1]*Wpk[11][14][1])));
        IkWpk[12][12][0] = ((ik[3][0][2]*pin[12][2])+((ik[3][0][0]*pin[12][0])+(
          ik[3][0][1]*pin[12][1])));
        IkWpk[12][12][1] = ((ik[3][1][2]*pin[12][2])+((ik[3][1][0]*pin[12][0])+(
          ik[3][1][1]*pin[12][1])));
        IkWpk[12][12][2] = ((ik[3][2][2]*pin[12][2])+((ik[3][2][0]*pin[12][0])+(
          ik[3][2][1]*pin[12][1])));
        IkWpk[12][13][0] = ((ik[4][0][2]*Wpk[12][13][2])+((ik[4][0][0]*
          Wpk[12][13][0])+(ik[4][0][1]*Wpk[12][13][1])));
        IkWpk[12][13][1] = ((ik[4][1][2]*Wpk[12][13][2])+((ik[4][1][0]*
          Wpk[12][13][0])+(ik[4][1][1]*Wpk[12][13][1])));
        IkWpk[12][13][2] = ((ik[4][2][2]*Wpk[12][13][2])+((ik[4][2][0]*
          Wpk[12][13][0])+(ik[4][2][1]*Wpk[12][13][1])));
        IkWpk[12][14][0] = ((ik[5][0][2]*Wpk[12][14][2])+((ik[5][0][0]*
          Wpk[12][14][0])+(ik[5][0][1]*Wpk[12][14][1])));
        IkWpk[12][14][1] = ((ik[5][1][2]*Wpk[12][14][2])+((ik[5][1][0]*
          Wpk[12][14][0])+(ik[5][1][1]*Wpk[12][14][1])));
        IkWpk[12][14][2] = ((ik[5][2][2]*Wpk[12][14][2])+((ik[5][2][0]*
          Wpk[12][14][0])+(ik[5][2][1]*Wpk[12][14][1])));
        IkWpk[13][13][0] = ((ik[4][0][2]*pin[13][2])+((ik[4][0][0]*pin[13][0])+(
          ik[4][0][1]*pin[13][1])));
        IkWpk[13][13][1] = ((ik[4][1][2]*pin[13][2])+((ik[4][1][0]*pin[13][0])+(
          ik[4][1][1]*pin[13][1])));
        IkWpk[13][13][2] = ((ik[4][2][2]*pin[13][2])+((ik[4][2][0]*pin[13][0])+(
          ik[4][2][1]*pin[13][1])));
        IkWpk[13][14][0] = ((ik[5][0][2]*Wpk[13][14][2])+((ik[5][0][0]*
          Wpk[13][14][0])+(ik[5][0][1]*Wpk[13][14][1])));
        IkWpk[13][14][1] = ((ik[5][1][2]*Wpk[13][14][2])+((ik[5][1][0]*
          Wpk[13][14][0])+(ik[5][1][1]*Wpk[13][14][1])));
        IkWpk[13][14][2] = ((ik[5][2][2]*Wpk[13][14][2])+((ik[5][2][0]*
          Wpk[13][14][0])+(ik[5][2][1]*Wpk[13][14][1])));
        IkWpk[14][14][0] = ((ik[5][0][2]*pin[14][2])+((ik[5][0][0]*pin[14][0])+(
          ik[5][0][1]*pin[14][1])));
        IkWpk[14][14][1] = ((ik[5][1][2]*pin[14][2])+((ik[5][1][0]*pin[14][0])+(
          ik[5][1][1]*pin[14][1])));
        IkWpk[14][14][2] = ((ik[5][2][2]*pin[14][2])+((ik[5][2][0]*pin[14][0])+(
          ik[5][2][1]*pin[14][1])));
        IkWpk[15][17][0] = ((ik[6][0][2]*Wpk[15][17][2])+((ik[6][0][0]*
          Wpk[15][17][0])+(ik[6][0][1]*Wpk[15][17][1])));
        IkWpk[15][17][1] = ((ik[6][1][2]*Wpk[15][17][2])+((ik[6][1][0]*
          Wpk[15][17][0])+(ik[6][1][1]*Wpk[15][17][1])));
        IkWpk[15][17][2] = ((ik[6][2][2]*Wpk[15][17][2])+((ik[6][2][0]*
          Wpk[15][17][0])+(ik[6][2][1]*Wpk[15][17][1])));
        IkWpk[15][20][0] = ((ik[7][0][2]*Wpk[15][20][2])+((ik[7][0][0]*
          Wpk[15][20][0])+(ik[7][0][1]*Wpk[15][20][1])));
        IkWpk[15][20][1] = ((ik[7][1][2]*Wpk[15][20][2])+((ik[7][1][0]*
          Wpk[15][20][0])+(ik[7][1][1]*Wpk[15][20][1])));
        IkWpk[15][20][2] = ((ik[7][2][2]*Wpk[15][20][2])+((ik[7][2][0]*
          Wpk[15][20][0])+(ik[7][2][1]*Wpk[15][20][1])));
        IkWpk[15][21][0] = ((ik[8][0][2]*Wpk[15][21][2])+((ik[8][0][0]*
          Wpk[15][21][0])+(ik[8][0][1]*Wpk[15][21][1])));
        IkWpk[15][21][1] = ((ik[8][1][2]*Wpk[15][21][2])+((ik[8][1][0]*
          Wpk[15][21][0])+(ik[8][1][1]*Wpk[15][21][1])));
        IkWpk[15][21][2] = ((ik[8][2][2]*Wpk[15][21][2])+((ik[8][2][0]*
          Wpk[15][21][0])+(ik[8][2][1]*Wpk[15][21][1])));
        IkWpk[15][22][0] = ((ik[9][0][2]*Wpk[15][22][2])+((ik[9][0][0]*
          Wpk[15][22][0])+(ik[9][0][1]*Wpk[15][22][1])));
        IkWpk[15][22][1] = ((ik[9][1][2]*Wpk[15][22][2])+((ik[9][1][0]*
          Wpk[15][22][0])+(ik[9][1][1]*Wpk[15][22][1])));
        IkWpk[15][22][2] = ((ik[9][2][2]*Wpk[15][22][2])+((ik[9][2][0]*
          Wpk[15][22][0])+(ik[9][2][1]*Wpk[15][22][1])));
        IkWpk[15][23][0] = ((ik[10][0][2]*Wpk[15][23][2])+((ik[10][0][0]*
          Wpk[15][23][0])+(ik[10][0][1]*Wpk[15][23][1])));
        IkWpk[15][23][1] = ((ik[10][1][2]*Wpk[15][23][2])+((ik[10][1][0]*
          Wpk[15][23][0])+(ik[10][1][1]*Wpk[15][23][1])));
        IkWpk[15][23][2] = ((ik[10][2][2]*Wpk[15][23][2])+((ik[10][2][0]*
          Wpk[15][23][0])+(ik[10][2][1]*Wpk[15][23][1])));
        IkWpk[16][17][0] = ((ik[6][0][2]*Wpk[16][17][2])+((ik[6][0][0]*
          Wpk[16][17][0])+(ik[6][0][1]*Wpk[16][17][1])));
        IkWpk[16][17][1] = ((ik[6][1][2]*Wpk[16][17][2])+((ik[6][1][0]*
          Wpk[16][17][0])+(ik[6][1][1]*Wpk[16][17][1])));
        IkWpk[16][17][2] = ((ik[6][2][2]*Wpk[16][17][2])+((ik[6][2][0]*
          Wpk[16][17][0])+(ik[6][2][1]*Wpk[16][17][1])));
        IkWpk[16][20][0] = ((ik[7][0][2]*Wpk[16][20][2])+((ik[7][0][0]*
          Wpk[16][20][0])+(ik[7][0][1]*Wpk[16][20][1])));
        IkWpk[16][20][1] = ((ik[7][1][2]*Wpk[16][20][2])+((ik[7][1][0]*
          Wpk[16][20][0])+(ik[7][1][1]*Wpk[16][20][1])));
        IkWpk[16][20][2] = ((ik[7][2][2]*Wpk[16][20][2])+((ik[7][2][0]*
          Wpk[16][20][0])+(ik[7][2][1]*Wpk[16][20][1])));
        IkWpk[16][21][0] = ((ik[8][0][2]*Wpk[16][21][2])+((ik[8][0][0]*
          Wpk[16][21][0])+(ik[8][0][1]*Wpk[16][21][1])));
        IkWpk[16][21][1] = ((ik[8][1][2]*Wpk[16][21][2])+((ik[8][1][0]*
          Wpk[16][21][0])+(ik[8][1][1]*Wpk[16][21][1])));
        IkWpk[16][21][2] = ((ik[8][2][2]*Wpk[16][21][2])+((ik[8][2][0]*
          Wpk[16][21][0])+(ik[8][2][1]*Wpk[16][21][1])));
        IkWpk[16][22][0] = ((ik[9][0][2]*Wpk[16][22][2])+((ik[9][0][0]*
          Wpk[16][22][0])+(ik[9][0][1]*Wpk[16][22][1])));
        IkWpk[16][22][1] = ((ik[9][1][2]*Wpk[16][22][2])+((ik[9][1][0]*
          Wpk[16][22][0])+(ik[9][1][1]*Wpk[16][22][1])));
        IkWpk[16][22][2] = ((ik[9][2][2]*Wpk[16][22][2])+((ik[9][2][0]*
          Wpk[16][22][0])+(ik[9][2][1]*Wpk[16][22][1])));
        IkWpk[16][23][0] = ((ik[10][0][2]*Wpk[16][23][2])+((ik[10][0][0]*
          Wpk[16][23][0])+(ik[10][0][1]*Wpk[16][23][1])));
        IkWpk[16][23][1] = ((ik[10][1][2]*Wpk[16][23][2])+((ik[10][1][0]*
          Wpk[16][23][0])+(ik[10][1][1]*Wpk[16][23][1])));
        IkWpk[16][23][2] = ((ik[10][2][2]*Wpk[16][23][2])+((ik[10][2][0]*
          Wpk[16][23][0])+(ik[10][2][1]*Wpk[16][23][1])));
        IkWpk[17][17][0] = ((ik[6][0][2]*pin[17][2])+((ik[6][0][0]*pin[17][0])+(
          ik[6][0][1]*pin[17][1])));
        IkWpk[17][17][1] = ((ik[6][1][2]*pin[17][2])+((ik[6][1][0]*pin[17][0])+(
          ik[6][1][1]*pin[17][1])));
        IkWpk[17][17][2] = ((ik[6][2][2]*pin[17][2])+((ik[6][2][0]*pin[17][0])+(
          ik[6][2][1]*pin[17][1])));
        IkWpk[17][20][0] = ((ik[7][0][2]*Wpk[17][20][2])+((ik[7][0][0]*
          Wpk[17][20][0])+(ik[7][0][1]*Wpk[17][20][1])));
        IkWpk[17][20][1] = ((ik[7][1][2]*Wpk[17][20][2])+((ik[7][1][0]*
          Wpk[17][20][0])+(ik[7][1][1]*Wpk[17][20][1])));
        IkWpk[17][20][2] = ((ik[7][2][2]*Wpk[17][20][2])+((ik[7][2][0]*
          Wpk[17][20][0])+(ik[7][2][1]*Wpk[17][20][1])));
        IkWpk[17][21][0] = ((ik[8][0][2]*Wpk[17][21][2])+((ik[8][0][0]*
          Wpk[17][21][0])+(ik[8][0][1]*Wpk[17][21][1])));
        IkWpk[17][21][1] = ((ik[8][1][2]*Wpk[17][21][2])+((ik[8][1][0]*
          Wpk[17][21][0])+(ik[8][1][1]*Wpk[17][21][1])));
        IkWpk[17][21][2] = ((ik[8][2][2]*Wpk[17][21][2])+((ik[8][2][0]*
          Wpk[17][21][0])+(ik[8][2][1]*Wpk[17][21][1])));
        IkWpk[17][22][0] = ((ik[9][0][2]*Wpk[17][22][2])+((ik[9][0][0]*
          Wpk[17][22][0])+(ik[9][0][1]*Wpk[17][22][1])));
        IkWpk[17][22][1] = ((ik[9][1][2]*Wpk[17][22][2])+((ik[9][1][0]*
          Wpk[17][22][0])+(ik[9][1][1]*Wpk[17][22][1])));
        IkWpk[17][22][2] = ((ik[9][2][2]*Wpk[17][22][2])+((ik[9][2][0]*
          Wpk[17][22][0])+(ik[9][2][1]*Wpk[17][22][1])));
        IkWpk[17][23][0] = ((ik[10][0][2]*Wpk[17][23][2])+((ik[10][0][0]*
          Wpk[17][23][0])+(ik[10][0][1]*Wpk[17][23][1])));
        IkWpk[17][23][1] = ((ik[10][1][2]*Wpk[17][23][2])+((ik[10][1][0]*
          Wpk[17][23][0])+(ik[10][1][1]*Wpk[17][23][1])));
        IkWpk[17][23][2] = ((ik[10][2][2]*Wpk[17][23][2])+((ik[10][2][0]*
          Wpk[17][23][0])+(ik[10][2][1]*Wpk[17][23][1])));
        IkWpk[20][20][0] = ((ik[7][0][2]*pin[20][2])+((ik[7][0][0]*pin[20][0])+(
          ik[7][0][1]*pin[20][1])));
        IkWpk[20][20][1] = ((ik[7][1][2]*pin[20][2])+((ik[7][1][0]*pin[20][0])+(
          ik[7][1][1]*pin[20][1])));
        IkWpk[20][20][2] = ((ik[7][2][2]*pin[20][2])+((ik[7][2][0]*pin[20][0])+(
          ik[7][2][1]*pin[20][1])));
        IkWpk[20][21][0] = ((ik[8][0][2]*Wpk[20][21][2])+((ik[8][0][0]*
          Wpk[20][21][0])+(ik[8][0][1]*Wpk[20][21][1])));
        IkWpk[20][21][1] = ((ik[8][1][2]*Wpk[20][21][2])+((ik[8][1][0]*
          Wpk[20][21][0])+(ik[8][1][1]*Wpk[20][21][1])));
        IkWpk[20][21][2] = ((ik[8][2][2]*Wpk[20][21][2])+((ik[8][2][0]*
          Wpk[20][21][0])+(ik[8][2][1]*Wpk[20][21][1])));
        IkWpk[20][22][0] = ((ik[9][0][2]*Wpk[20][22][2])+((ik[9][0][0]*
          Wpk[20][22][0])+(ik[9][0][1]*Wpk[20][22][1])));
        IkWpk[20][22][1] = ((ik[9][1][2]*Wpk[20][22][2])+((ik[9][1][0]*
          Wpk[20][22][0])+(ik[9][1][1]*Wpk[20][22][1])));
        IkWpk[20][22][2] = ((ik[9][2][2]*Wpk[20][22][2])+((ik[9][2][0]*
          Wpk[20][22][0])+(ik[9][2][1]*Wpk[20][22][1])));
        IkWpk[20][23][0] = ((ik[10][0][2]*Wpk[20][23][2])+((ik[10][0][0]*
          Wpk[20][23][0])+(ik[10][0][1]*Wpk[20][23][1])));
        IkWpk[20][23][1] = ((ik[10][1][2]*Wpk[20][23][2])+((ik[10][1][0]*
          Wpk[20][23][0])+(ik[10][1][1]*Wpk[20][23][1])));
        IkWpk[20][23][2] = ((ik[10][2][2]*Wpk[20][23][2])+((ik[10][2][0]*
          Wpk[20][23][0])+(ik[10][2][1]*Wpk[20][23][1])));
        IkWpk[21][21][0] = ((ik[8][0][2]*pin[21][2])+((ik[8][0][0]*pin[21][0])+(
          ik[8][0][1]*pin[21][1])));
        IkWpk[21][21][1] = ((ik[8][1][2]*pin[21][2])+((ik[8][1][0]*pin[21][0])+(
          ik[8][1][1]*pin[21][1])));
        IkWpk[21][21][2] = ((ik[8][2][2]*pin[21][2])+((ik[8][2][0]*pin[21][0])+(
          ik[8][2][1]*pin[21][1])));
        IkWpk[21][22][0] = ((ik[9][0][2]*Wpk[21][22][2])+((ik[9][0][0]*
          Wpk[21][22][0])+(ik[9][0][1]*Wpk[21][22][1])));
        IkWpk[21][22][1] = ((ik[9][1][2]*Wpk[21][22][2])+((ik[9][1][0]*
          Wpk[21][22][0])+(ik[9][1][1]*Wpk[21][22][1])));
        IkWpk[21][22][2] = ((ik[9][2][2]*Wpk[21][22][2])+((ik[9][2][0]*
          Wpk[21][22][0])+(ik[9][2][1]*Wpk[21][22][1])));
        IkWpk[21][23][0] = ((ik[10][0][2]*Wpk[21][23][2])+((ik[10][0][0]*
          Wpk[21][23][0])+(ik[10][0][1]*Wpk[21][23][1])));
        IkWpk[21][23][1] = ((ik[10][1][2]*Wpk[21][23][2])+((ik[10][1][0]*
          Wpk[21][23][0])+(ik[10][1][1]*Wpk[21][23][1])));
        IkWpk[21][23][2] = ((ik[10][2][2]*Wpk[21][23][2])+((ik[10][2][0]*
          Wpk[21][23][0])+(ik[10][2][1]*Wpk[21][23][1])));
        IkWpk[22][22][0] = ((ik[9][0][2]*pin[22][2])+((ik[9][0][0]*pin[22][0])+(
          ik[9][0][1]*pin[22][1])));
        IkWpk[22][22][1] = ((ik[9][1][2]*pin[22][2])+((ik[9][1][0]*pin[22][0])+(
          ik[9][1][1]*pin[22][1])));
        IkWpk[22][22][2] = ((ik[9][2][2]*pin[22][2])+((ik[9][2][0]*pin[22][0])+(
          ik[9][2][1]*pin[22][1])));
        IkWpk[22][23][0] = ((ik[10][0][2]*Wpk[22][23][2])+((ik[10][0][0]*
          Wpk[22][23][0])+(ik[10][0][1]*Wpk[22][23][1])));
        IkWpk[22][23][1] = ((ik[10][1][2]*Wpk[22][23][2])+((ik[10][1][0]*
          Wpk[22][23][0])+(ik[10][1][1]*Wpk[22][23][1])));
        IkWpk[22][23][2] = ((ik[10][2][2]*Wpk[22][23][2])+((ik[10][2][0]*
          Wpk[22][23][0])+(ik[10][2][1]*Wpk[22][23][1])));
        IkWpk[23][23][0] = ((ik[10][0][2]*pin[23][2])+((ik[10][0][0]*pin[23][0])
          +(ik[10][0][1]*pin[23][1])));
        IkWpk[23][23][1] = ((ik[10][1][2]*pin[23][2])+((ik[10][1][0]*pin[23][0])
          +(ik[10][1][1]*pin[23][1])));
        IkWpk[23][23][2] = ((ik[10][2][2]*pin[23][2])+((ik[10][2][0]*pin[23][0])
          +(ik[10][2][1]*pin[23][1])));
        IkWpk[24][26][0] = ((ik[11][0][2]*Wpk[24][26][2])+((ik[11][0][0]*
          Wpk[24][26][0])+(ik[11][0][1]*Wpk[24][26][1])));
        IkWpk[24][26][1] = ((ik[11][1][2]*Wpk[24][26][2])+((ik[11][1][0]*
          Wpk[24][26][0])+(ik[11][1][1]*Wpk[24][26][1])));
        IkWpk[24][26][2] = ((ik[11][2][2]*Wpk[24][26][2])+((ik[11][2][0]*
          Wpk[24][26][0])+(ik[11][2][1]*Wpk[24][26][1])));
        IkWpk[25][26][0] = ((ik[11][0][2]*Wpk[25][26][2])+((ik[11][0][0]*
          Wpk[25][26][0])+(ik[11][0][1]*Wpk[25][26][1])));
        IkWpk[25][26][1] = ((ik[11][1][2]*Wpk[25][26][2])+((ik[11][1][0]*
          Wpk[25][26][0])+(ik[11][1][1]*Wpk[25][26][1])));
        IkWpk[25][26][2] = ((ik[11][2][2]*Wpk[25][26][2])+((ik[11][2][0]*
          Wpk[25][26][0])+(ik[11][2][1]*Wpk[25][26][1])));
        IkWpk[26][26][0] = ((ik[11][0][2]*pin[26][2])+((ik[11][0][0]*pin[26][0])
          +(ik[11][0][1]*pin[26][1])));
        IkWpk[26][26][1] = ((ik[11][1][2]*pin[26][2])+((ik[11][1][0]*pin[26][0])
          +(ik[11][1][1]*pin[26][1])));
        IkWpk[26][26][2] = ((ik[11][2][2]*pin[26][2])+((ik[11][2][0]*pin[26][0])
          +(ik[11][2][1]*pin[26][1])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[0][11][2])+((Vpk[0][11][0]*
          Vpk[0][11][0])+(Vpk[0][11][1]*Vpk[0][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[0][5][2])+((Vpk[0][5][0]*Vpk[0][5][0])+(Vpk[0][5][1]*Vpk[0][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[0][8][2])+((Vpk[0][8][0]*Vpk[0][8][0])+
          (Vpk[0][8][1]*Vpk[0][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[0][14][2])+((Vpk[0][14][0]*
          Vpk[0][14][0])+(Vpk[0][14][1]*Vpk[0][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[0][13][2])+((Vpk[0][13][0]*Vpk[0][13][0])+(
          Vpk[0][13][1]*Vpk[0][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[0][12][2])
          +((Vpk[0][12][0]*Vpk[0][12][0])+(Vpk[0][12][1]*Vpk[0][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[0][21][2])+((Vpk[0][21][0]*
          Vpk[0][21][0])+(Vpk[0][21][1]*Vpk[0][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[0][20][2])+((Vpk[0][20][0]*Vpk[0][20][0])+(
          Vpk[0][20][1]*Vpk[0][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[0][17][2])
          +((Vpk[0][17][0]*Vpk[0][17][0])+(Vpk[0][17][1]*Vpk[0][17][1]))))+
          temp[1])));
        mm[0][0] = ((mk[11]*((Vpk[0][26][2]*Vpk[0][26][2])+((Vpk[0][26][0]*
          Vpk[0][26][0])+(Vpk[0][26][1]*Vpk[0][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[0][23][2])+((Vpk[0][23][0]*Vpk[0][23][0])+(
          Vpk[0][23][1]*Vpk[0][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[0][22][2])
          +((Vpk[0][22][0]*Vpk[0][22][0])+(Vpk[0][22][1]*Vpk[0][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[1][11][2])+((Vpk[0][11][0]*
          Vpk[1][11][0])+(Vpk[0][11][1]*Vpk[1][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[1][5][2])+((Vpk[0][5][0]*Vpk[1][5][0])+(Vpk[0][5][1]*Vpk[1][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[1][8][2])+((Vpk[0][8][0]*Vpk[1][8][0])+
          (Vpk[0][8][1]*Vpk[1][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[1][14][2])+((Vpk[0][14][0]*
          Vpk[1][14][0])+(Vpk[0][14][1]*Vpk[1][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[1][13][2])+((Vpk[0][13][0]*Vpk[1][13][0])+(
          Vpk[0][13][1]*Vpk[1][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[1][12][2])
          +((Vpk[0][12][0]*Vpk[1][12][0])+(Vpk[0][12][1]*Vpk[1][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[1][21][2])+((Vpk[0][21][0]*
          Vpk[1][21][0])+(Vpk[0][21][1]*Vpk[1][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[1][20][2])+((Vpk[0][20][0]*Vpk[1][20][0])+(
          Vpk[0][20][1]*Vpk[1][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[1][17][2])
          +((Vpk[0][17][0]*Vpk[1][17][0])+(Vpk[0][17][1]*Vpk[1][17][1]))))+
          temp[1])));
        mm[0][1] = ((mk[11]*((Vpk[0][26][2]*Vpk[1][26][2])+((Vpk[0][26][0]*
          Vpk[1][26][0])+(Vpk[0][26][1]*Vpk[1][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[1][23][2])+((Vpk[0][23][0]*Vpk[1][23][0])+(
          Vpk[0][23][1]*Vpk[1][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[1][22][2])
          +((Vpk[0][22][0]*Vpk[1][22][0])+(Vpk[0][22][1]*Vpk[1][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[2][11][2])+((Vpk[0][11][0]*
          Vpk[2][11][0])+(Vpk[0][11][1]*Vpk[2][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[2][5][2])+((Vpk[0][5][0]*Vpk[2][5][0])+(Vpk[0][5][1]*Vpk[2][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[2][8][2])+((Vpk[0][8][0]*Vpk[2][8][0])+
          (Vpk[0][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[2][14][2])+((Vpk[0][14][0]*
          Vpk[2][14][0])+(Vpk[0][14][1]*Vpk[2][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[2][13][2])+((Vpk[0][13][0]*Vpk[2][13][0])+(
          Vpk[0][13][1]*Vpk[2][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[2][12][2])
          +((Vpk[0][12][0]*Vpk[2][12][0])+(Vpk[0][12][1]*Vpk[2][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[2][21][2])+((Vpk[0][21][0]*
          Vpk[2][21][0])+(Vpk[0][21][1]*Vpk[2][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[2][20][2])+((Vpk[0][20][0]*Vpk[2][20][0])+(
          Vpk[0][20][1]*Vpk[2][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[2][17][2])
          +((Vpk[0][17][0]*Vpk[2][17][0])+(Vpk[0][17][1]*Vpk[2][17][1]))))+
          temp[1])));
        mm[0][2] = ((mk[11]*((Vpk[0][26][2]*Vpk[2][26][2])+((Vpk[0][26][0]*
          Vpk[2][26][0])+(Vpk[0][26][1]*Vpk[2][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[2][23][2])+((Vpk[0][23][0]*Vpk[2][23][0])+(
          Vpk[0][23][1]*Vpk[2][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[2][22][2])
          +((Vpk[0][22][0]*Vpk[2][22][0])+(Vpk[0][22][1]*Vpk[2][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[3][11][2])+((Vpk[0][11][0]*
          Vpk[3][11][0])+(Vpk[0][11][1]*Vpk[3][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[3][5][2])+((Vpk[0][5][0]*Vpk[3][5][0])+(Vpk[0][5][1]*Vpk[3][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[3][8][2])+((Vpk[0][8][0]*Vpk[3][8][0])+
          (Vpk[0][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[3][14][2])+((Vpk[0][14][0]*
          Vpk[3][14][0])+(Vpk[0][14][1]*Vpk[3][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[3][13][2])+((Vpk[0][13][0]*Vpk[3][13][0])+(
          Vpk[0][13][1]*Vpk[3][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[3][12][2])
          +((Vpk[0][12][0]*Vpk[3][12][0])+(Vpk[0][12][1]*Vpk[3][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[3][21][2])+((Vpk[0][21][0]*
          Vpk[3][21][0])+(Vpk[0][21][1]*Vpk[3][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[3][20][2])+((Vpk[0][20][0]*Vpk[3][20][0])+(
          Vpk[0][20][1]*Vpk[3][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[3][17][2])
          +((Vpk[0][17][0]*Vpk[3][17][0])+(Vpk[0][17][1]*Vpk[3][17][1]))))+
          temp[1])));
        mm[0][3] = ((mk[11]*((Vpk[0][26][2]*Vpk[3][26][2])+((Vpk[0][26][0]*
          Vpk[3][26][0])+(Vpk[0][26][1]*Vpk[3][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[3][23][2])+((Vpk[0][23][0]*Vpk[3][23][0])+(
          Vpk[0][23][1]*Vpk[3][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[3][22][2])
          +((Vpk[0][22][0]*Vpk[3][22][0])+(Vpk[0][22][1]*Vpk[3][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[4][11][2])+((Vpk[0][11][0]*
          Vpk[4][11][0])+(Vpk[0][11][1]*Vpk[4][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[4][5][2])+((Vpk[0][5][0]*Vpk[4][5][0])+(Vpk[0][5][1]*Vpk[4][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[4][8][2])+((Vpk[0][8][0]*Vpk[4][8][0])+
          (Vpk[0][8][1]*Vpk[4][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[4][14][2])+((Vpk[0][14][0]*
          Vpk[4][14][0])+(Vpk[0][14][1]*Vpk[4][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[4][13][2])+((Vpk[0][13][0]*Vpk[4][13][0])+(
          Vpk[0][13][1]*Vpk[4][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[4][12][2])
          +((Vpk[0][12][0]*Vpk[4][12][0])+(Vpk[0][12][1]*Vpk[4][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[4][21][2])+((Vpk[0][21][0]*
          Vpk[4][21][0])+(Vpk[0][21][1]*Vpk[4][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[4][20][2])+((Vpk[0][20][0]*Vpk[4][20][0])+(
          Vpk[0][20][1]*Vpk[4][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[4][17][2])
          +((Vpk[0][17][0]*Vpk[4][17][0])+(Vpk[0][17][1]*Vpk[4][17][1]))))+
          temp[1])));
        mm[0][4] = ((mk[11]*((Vpk[0][26][2]*Vpk[4][26][2])+((Vpk[0][26][0]*
          Vpk[4][26][0])+(Vpk[0][26][1]*Vpk[4][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[4][23][2])+((Vpk[0][23][0]*Vpk[4][23][0])+(
          Vpk[0][23][1]*Vpk[4][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[4][22][2])
          +((Vpk[0][22][0]*Vpk[4][22][0])+(Vpk[0][22][1]*Vpk[4][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[0][11][2]*Vpk[5][11][2])+((Vpk[0][11][0]*
          Vpk[5][11][0])+(Vpk[0][11][1]*Vpk[5][11][1]))))+((mk[0]*((Vpk[0][5][2]
          *Vpk[5][5][2])+((Vpk[0][5][0]*Vpk[5][5][0])+(Vpk[0][5][1]*Vpk[5][5][1]
          ))))+(mk[1]*((Vpk[0][8][2]*Vpk[5][8][2])+((Vpk[0][8][0]*Vpk[5][8][0])+
          (Vpk[0][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][14][2]*Vpk[5][14][2])+((Vpk[0][14][0]*
          Vpk[5][14][0])+(Vpk[0][14][1]*Vpk[5][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[5][13][2])+((Vpk[0][13][0]*Vpk[5][13][0])+(
          Vpk[0][13][1]*Vpk[5][13][1]))))+((mk[3]*((Vpk[0][12][2]*Vpk[5][12][2])
          +((Vpk[0][12][0]*Vpk[5][12][0])+(Vpk[0][12][1]*Vpk[5][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][21][2]*Vpk[5][21][2])+((Vpk[0][21][0]*
          Vpk[5][21][0])+(Vpk[0][21][1]*Vpk[5][21][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[5][20][2])+((Vpk[0][20][0]*Vpk[5][20][0])+(
          Vpk[0][20][1]*Vpk[5][20][1]))))+((mk[6]*((Vpk[0][17][2]*Vpk[5][17][2])
          +((Vpk[0][17][0]*Vpk[5][17][0])+(Vpk[0][17][1]*Vpk[5][17][1]))))+
          temp[1])));
        mm[0][5] = ((mk[11]*((Vpk[0][26][2]*Vpk[5][26][2])+((Vpk[0][26][0]*
          Vpk[5][26][0])+(Vpk[0][26][1]*Vpk[5][26][1]))))+((mk[10]*((
          Vpk[0][23][2]*Vpk[5][23][2])+((Vpk[0][23][0]*Vpk[5][23][0])+(
          Vpk[0][23][1]*Vpk[5][23][1]))))+((mk[9]*((Vpk[0][22][2]*Vpk[5][22][2])
          +((Vpk[0][22][0]*Vpk[5][22][0])+(Vpk[0][22][1]*Vpk[5][22][1]))))+
          temp[2])));
        temp[0] = ((mk[3]*((Vpk[0][12][2]*Vpk[6][12][2])+((Vpk[0][12][0]*
          Vpk[6][12][0])+(Vpk[0][12][1]*Vpk[6][12][1]))))+((mk[1]*((Vpk[0][8][2]
          *Vpk[6][8][2])+((Vpk[0][8][0]*Vpk[6][8][0])+(Vpk[0][8][1]*Vpk[6][8][1]
          ))))+(mk[2]*((Vpk[0][11][2]*Vpk[6][11][2])+((Vpk[0][11][0]*
          Vpk[6][11][0])+(Vpk[0][11][1]*Vpk[6][11][1]))))));
        mm[0][6] = ((mk[5]*((Vpk[0][14][2]*Vpk[6][14][2])+((Vpk[0][14][0]*
          Vpk[6][14][0])+(Vpk[0][14][1]*Vpk[6][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[6][13][2])+((Vpk[0][13][0]*Vpk[6][13][0])+(
          Vpk[0][13][1]*Vpk[6][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[0][12][2]*Vpk[7][12][2])+((Vpk[0][12][0]*
          Vpk[7][12][0])+(Vpk[0][12][1]*Vpk[7][12][1]))))+((mk[1]*((Vpk[0][8][2]
          *Vpk[7][8][2])+((Vpk[0][8][0]*Vpk[7][8][0])+(Vpk[0][8][1]*Vpk[7][8][1]
          ))))+(mk[2]*((Vpk[0][11][2]*Vpk[7][11][2])+((Vpk[0][11][0]*
          Vpk[7][11][0])+(Vpk[0][11][1]*Vpk[7][11][1]))))));
        mm[0][7] = ((mk[5]*((Vpk[0][14][2]*Vpk[7][14][2])+((Vpk[0][14][0]*
          Vpk[7][14][0])+(Vpk[0][14][1]*Vpk[7][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[7][13][2])+((Vpk[0][13][0]*Vpk[7][13][0])+(
          Vpk[0][13][1]*Vpk[7][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[0][12][2]*Vpk[8][12][2])+((Vpk[0][12][0]*
          Vpk[8][12][0])+(Vpk[0][12][1]*Vpk[8][12][1]))))+((mk[1]*((Vpk[0][8][2]
          *Vpk[8][8][2])+((Vpk[0][8][0]*Vpk[8][8][0])+(Vpk[0][8][1]*Vpk[8][8][1]
          ))))+(mk[2]*((Vpk[0][11][2]*Vpk[8][11][2])+((Vpk[0][11][0]*
          Vpk[8][11][0])+(Vpk[0][11][1]*Vpk[8][11][1]))))));
        mm[0][8] = ((mk[5]*((Vpk[0][14][2]*Vpk[8][14][2])+((Vpk[0][14][0]*
          Vpk[8][14][0])+(Vpk[0][14][1]*Vpk[8][14][1]))))+((mk[4]*((
          Vpk[0][13][2]*Vpk[8][13][2])+((Vpk[0][13][0]*Vpk[8][13][0])+(
          Vpk[0][13][1]*Vpk[8][13][1]))))+temp[0]));
        temp[0] = ((mk[4]*((Vpk[0][13][2]*Vpk[9][13][2])+((Vpk[0][13][0]*
          Vpk[9][13][0])+(Vpk[0][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[0][11][2]*Vpk[9][11][2])+((Vpk[0][11][0]*Vpk[9][11][0])+(
          Vpk[0][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[0][12][2]*Vpk[9][12][2])+
          ((Vpk[0][12][0]*Vpk[9][12][0])+(Vpk[0][12][1]*Vpk[9][12][1]))))));
        mm[0][9] = ((mk[5]*((Vpk[0][14][2]*Vpk[9][14][2])+((Vpk[0][14][0]*
          Vpk[9][14][0])+(Vpk[0][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[0][13][2]*Vpk[10][13][2])+((Vpk[0][13][0]*
          Vpk[10][13][0])+(Vpk[0][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[0][11][2]*Vpk[10][11][2])+((Vpk[0][11][0]*Vpk[10][11][0])+(
          Vpk[0][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[0][12][2]*Vpk[10][12][2]
          )+((Vpk[0][12][0]*Vpk[10][12][0])+(Vpk[0][12][1]*Vpk[10][12][1]))))));
        mm[0][10] = ((mk[5]*((Vpk[0][14][2]*Vpk[10][14][2])+((Vpk[0][14][0]*
          Vpk[10][14][0])+(Vpk[0][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[0][13][2]*Vpk[11][13][2])+((Vpk[0][13][0]*
          Vpk[11][13][0])+(Vpk[0][13][1]*Vpk[11][13][1]))))+((mk[2]*((
          Vpk[0][11][2]*Vpk[11][11][2])+((Vpk[0][11][0]*Vpk[11][11][0])+(
          Vpk[0][11][1]*Vpk[11][11][1]))))+(mk[3]*((Vpk[0][12][2]*Vpk[11][12][2]
          )+((Vpk[0][12][0]*Vpk[11][12][0])+(Vpk[0][12][1]*Vpk[11][12][1]))))));
        mm[0][11] = ((mk[5]*((Vpk[0][14][2]*Vpk[11][14][2])+((Vpk[0][14][0]*
          Vpk[11][14][0])+(Vpk[0][14][1]*Vpk[11][14][1]))))+temp[0]);
        mm[0][12] = ((mk[5]*((Vpk[0][14][2]*Vpk[12][14][2])+((Vpk[0][14][0]*
          Vpk[12][14][0])+(Vpk[0][14][1]*Vpk[12][14][1]))))+((mk[3]*((
          Vpk[0][12][2]*Vpk[12][12][2])+((Vpk[0][12][0]*Vpk[12][12][0])+(
          Vpk[0][12][1]*Vpk[12][12][1]))))+(mk[4]*((Vpk[0][13][2]*Vpk[12][13][2]
          )+((Vpk[0][13][0]*Vpk[12][13][0])+(Vpk[0][13][1]*Vpk[12][13][1]))))));
        mm[0][13] = ((mk[4]*((Vpk[0][13][2]*Vpk[13][13][2])+((Vpk[0][13][0]*
          Vpk[13][13][0])+(Vpk[0][13][1]*Vpk[13][13][1]))))+(mk[5]*((
          Vpk[0][14][2]*Vpk[13][14][2])+((Vpk[0][14][0]*Vpk[13][14][0])+(
          Vpk[0][14][1]*Vpk[13][14][1])))));
        mm[0][14] = (mk[5]*((Vpk[0][14][2]*Vpk[14][14][2])+((Vpk[0][14][0]*
          Vpk[14][14][0])+(Vpk[0][14][1]*Vpk[14][14][1]))));
        temp[0] = ((mk[8]*((Vpk[0][21][2]*Vpk[15][21][2])+((Vpk[0][21][0]*
          Vpk[15][21][0])+(Vpk[0][21][1]*Vpk[15][21][1]))))+((mk[6]*((
          Vpk[0][17][2]*Vpk[15][17][2])+((Vpk[0][17][0]*Vpk[15][17][0])+(
          Vpk[0][17][1]*Vpk[15][17][1]))))+(mk[7]*((Vpk[0][20][2]*Vpk[15][20][2]
          )+((Vpk[0][20][0]*Vpk[15][20][0])+(Vpk[0][20][1]*Vpk[15][20][1]))))));
        mm[0][15] = ((mk[10]*((Vpk[0][23][2]*Vpk[15][23][2])+((Vpk[0][23][0]*
          Vpk[15][23][0])+(Vpk[0][23][1]*Vpk[15][23][1]))))+((mk[9]*((
          Vpk[0][22][2]*Vpk[15][22][2])+((Vpk[0][22][0]*Vpk[15][22][0])+(
          Vpk[0][22][1]*Vpk[15][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[0][21][2]*Vpk[16][21][2])+((Vpk[0][21][0]*
          Vpk[16][21][0])+(Vpk[0][21][1]*Vpk[16][21][1]))))+((mk[6]*((
          Vpk[0][17][2]*Vpk[16][17][2])+((Vpk[0][17][0]*Vpk[16][17][0])+(
          Vpk[0][17][1]*Vpk[16][17][1]))))+(mk[7]*((Vpk[0][20][2]*Vpk[16][20][2]
          )+((Vpk[0][20][0]*Vpk[16][20][0])+(Vpk[0][20][1]*Vpk[16][20][1]))))));
        mm[0][16] = ((mk[10]*((Vpk[0][23][2]*Vpk[16][23][2])+((Vpk[0][23][0]*
          Vpk[16][23][0])+(Vpk[0][23][1]*Vpk[16][23][1]))))+((mk[9]*((
          Vpk[0][22][2]*Vpk[16][22][2])+((Vpk[0][22][0]*Vpk[16][22][0])+(
          Vpk[0][22][1]*Vpk[16][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[0][21][2]*Vpk[17][21][2])+((Vpk[0][21][0]*
          Vpk[17][21][0])+(Vpk[0][21][1]*Vpk[17][21][1]))))+((mk[6]*((
          Vpk[0][17][2]*Vpk[17][17][2])+((Vpk[0][17][0]*Vpk[17][17][0])+(
          Vpk[0][17][1]*Vpk[17][17][1]))))+(mk[7]*((Vpk[0][20][2]*Vpk[17][20][2]
          )+((Vpk[0][20][0]*Vpk[17][20][0])+(Vpk[0][20][1]*Vpk[17][20][1]))))));
        mm[0][17] = ((mk[10]*((Vpk[0][23][2]*Vpk[17][23][2])+((Vpk[0][23][0]*
          Vpk[17][23][0])+(Vpk[0][23][1]*Vpk[17][23][1]))))+((mk[9]*((
          Vpk[0][22][2]*Vpk[17][22][2])+((Vpk[0][22][0]*Vpk[17][22][0])+(
          Vpk[0][22][1]*Vpk[17][22][1]))))+temp[0]));
        temp[0] = ((mk[9]*((Vpk[0][22][2]*Vpk[18][22][2])+((Vpk[0][22][0]*
          Vpk[18][22][0])+(Vpk[0][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[18][20][2])+((Vpk[0][20][0]*Vpk[18][20][0])+(
          Vpk[0][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[0][21][2]*Vpk[18][21][2]
          )+((Vpk[0][21][0]*Vpk[18][21][0])+(Vpk[0][21][1]*Vpk[18][21][1]))))));
        mm[0][18] = ((mk[10]*((Vpk[0][23][2]*Vpk[18][23][2])+((Vpk[0][23][0]*
          Vpk[18][23][0])+(Vpk[0][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[0][22][2]*Vpk[19][22][2])+((Vpk[0][22][0]*
          Vpk[19][22][0])+(Vpk[0][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[19][20][2])+((Vpk[0][20][0]*Vpk[19][20][0])+(
          Vpk[0][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[0][21][2]*Vpk[19][21][2]
          )+((Vpk[0][21][0]*Vpk[19][21][0])+(Vpk[0][21][1]*Vpk[19][21][1]))))));
        mm[0][19] = ((mk[10]*((Vpk[0][23][2]*Vpk[19][23][2])+((Vpk[0][23][0]*
          Vpk[19][23][0])+(Vpk[0][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[0][22][2]*Vpk[20][22][2])+((Vpk[0][22][0]*
          Vpk[20][22][0])+(Vpk[0][22][1]*Vpk[20][22][1]))))+((mk[7]*((
          Vpk[0][20][2]*Vpk[20][20][2])+((Vpk[0][20][0]*Vpk[20][20][0])+(
          Vpk[0][20][1]*Vpk[20][20][1]))))+(mk[8]*((Vpk[0][21][2]*Vpk[20][21][2]
          )+((Vpk[0][21][0]*Vpk[20][21][0])+(Vpk[0][21][1]*Vpk[20][21][1]))))));
        mm[0][20] = ((mk[10]*((Vpk[0][23][2]*Vpk[20][23][2])+((Vpk[0][23][0]*
          Vpk[20][23][0])+(Vpk[0][23][1]*Vpk[20][23][1]))))+temp[0]);
        mm[0][21] = ((mk[10]*((Vpk[0][23][2]*Vpk[21][23][2])+((Vpk[0][23][0]*
          Vpk[21][23][0])+(Vpk[0][23][1]*Vpk[21][23][1]))))+((mk[8]*((
          Vpk[0][21][2]*Vpk[21][21][2])+((Vpk[0][21][0]*Vpk[21][21][0])+(
          Vpk[0][21][1]*Vpk[21][21][1]))))+(mk[9]*((Vpk[0][22][2]*Vpk[21][22][2]
          )+((Vpk[0][22][0]*Vpk[21][22][0])+(Vpk[0][22][1]*Vpk[21][22][1]))))));
        mm[0][22] = ((mk[9]*((Vpk[0][22][2]*Vpk[22][22][2])+((Vpk[0][22][0]*
          Vpk[22][22][0])+(Vpk[0][22][1]*Vpk[22][22][1]))))+(mk[10]*((
          Vpk[0][23][2]*Vpk[22][23][2])+((Vpk[0][23][0]*Vpk[22][23][0])+(
          Vpk[0][23][1]*Vpk[22][23][1])))));
        mm[0][23] = (mk[10]*((Vpk[0][23][2]*Vpk[23][23][2])+((Vpk[0][23][0]*
          Vpk[23][23][0])+(Vpk[0][23][1]*Vpk[23][23][1]))));
        mm[0][24] = (mk[11]*((Vpk[0][26][2]*Vpk[24][26][2])+((Vpk[0][26][0]*
          Vpk[24][26][0])+(Vpk[0][26][1]*Vpk[24][26][1]))));
        mm[0][25] = (mk[11]*((Vpk[0][26][2]*Vpk[25][26][2])+((Vpk[0][26][0]*
          Vpk[25][26][0])+(Vpk[0][26][1]*Vpk[25][26][1]))));
        mm[0][26] = (mk[11]*((Vpk[0][26][2]*Vpk[26][26][2])+((Vpk[0][26][0]*
          Vpk[26][26][0])+(Vpk[0][26][1]*Vpk[26][26][1]))));
        temp[0] = ((mk[2]*((Vpk[1][11][2]*Vpk[1][11][2])+((Vpk[1][11][0]*
          Vpk[1][11][0])+(Vpk[1][11][1]*Vpk[1][11][1]))))+((mk[0]*((Vpk[1][5][2]
          *Vpk[1][5][2])+((Vpk[1][5][0]*Vpk[1][5][0])+(Vpk[1][5][1]*Vpk[1][5][1]
          ))))+(mk[1]*((Vpk[1][8][2]*Vpk[1][8][2])+((Vpk[1][8][0]*Vpk[1][8][0])+
          (Vpk[1][8][1]*Vpk[1][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][14][2]*Vpk[1][14][2])+((Vpk[1][14][0]*
          Vpk[1][14][0])+(Vpk[1][14][1]*Vpk[1][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[1][13][2])+((Vpk[1][13][0]*Vpk[1][13][0])+(
          Vpk[1][13][1]*Vpk[1][13][1]))))+((mk[3]*((Vpk[1][12][2]*Vpk[1][12][2])
          +((Vpk[1][12][0]*Vpk[1][12][0])+(Vpk[1][12][1]*Vpk[1][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][21][2]*Vpk[1][21][2])+((Vpk[1][21][0]*
          Vpk[1][21][0])+(Vpk[1][21][1]*Vpk[1][21][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[1][20][2])+((Vpk[1][20][0]*Vpk[1][20][0])+(
          Vpk[1][20][1]*Vpk[1][20][1]))))+((mk[6]*((Vpk[1][17][2]*Vpk[1][17][2])
          +((Vpk[1][17][0]*Vpk[1][17][0])+(Vpk[1][17][1]*Vpk[1][17][1]))))+
          temp[1])));
        mm[1][1] = ((mk[11]*((Vpk[1][26][2]*Vpk[1][26][2])+((Vpk[1][26][0]*
          Vpk[1][26][0])+(Vpk[1][26][1]*Vpk[1][26][1]))))+((mk[10]*((
          Vpk[1][23][2]*Vpk[1][23][2])+((Vpk[1][23][0]*Vpk[1][23][0])+(
          Vpk[1][23][1]*Vpk[1][23][1]))))+((mk[9]*((Vpk[1][22][2]*Vpk[1][22][2])
          +((Vpk[1][22][0]*Vpk[1][22][0])+(Vpk[1][22][1]*Vpk[1][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[1][11][2]*Vpk[2][11][2])+((Vpk[1][11][0]*
          Vpk[2][11][0])+(Vpk[1][11][1]*Vpk[2][11][1]))))+((mk[0]*((Vpk[1][5][2]
          *Vpk[2][5][2])+((Vpk[1][5][0]*Vpk[2][5][0])+(Vpk[1][5][1]*Vpk[2][5][1]
          ))))+(mk[1]*((Vpk[1][8][2]*Vpk[2][8][2])+((Vpk[1][8][0]*Vpk[2][8][0])+
          (Vpk[1][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][14][2]*Vpk[2][14][2])+((Vpk[1][14][0]*
          Vpk[2][14][0])+(Vpk[1][14][1]*Vpk[2][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[2][13][2])+((Vpk[1][13][0]*Vpk[2][13][0])+(
          Vpk[1][13][1]*Vpk[2][13][1]))))+((mk[3]*((Vpk[1][12][2]*Vpk[2][12][2])
          +((Vpk[1][12][0]*Vpk[2][12][0])+(Vpk[1][12][1]*Vpk[2][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][21][2]*Vpk[2][21][2])+((Vpk[1][21][0]*
          Vpk[2][21][0])+(Vpk[1][21][1]*Vpk[2][21][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[2][20][2])+((Vpk[1][20][0]*Vpk[2][20][0])+(
          Vpk[1][20][1]*Vpk[2][20][1]))))+((mk[6]*((Vpk[1][17][2]*Vpk[2][17][2])
          +((Vpk[1][17][0]*Vpk[2][17][0])+(Vpk[1][17][1]*Vpk[2][17][1]))))+
          temp[1])));
        mm[1][2] = ((mk[11]*((Vpk[1][26][2]*Vpk[2][26][2])+((Vpk[1][26][0]*
          Vpk[2][26][0])+(Vpk[1][26][1]*Vpk[2][26][1]))))+((mk[10]*((
          Vpk[1][23][2]*Vpk[2][23][2])+((Vpk[1][23][0]*Vpk[2][23][0])+(
          Vpk[1][23][1]*Vpk[2][23][1]))))+((mk[9]*((Vpk[1][22][2]*Vpk[2][22][2])
          +((Vpk[1][22][0]*Vpk[2][22][0])+(Vpk[1][22][1]*Vpk[2][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[1][11][2]*Vpk[3][11][2])+((Vpk[1][11][0]*
          Vpk[3][11][0])+(Vpk[1][11][1]*Vpk[3][11][1]))))+((mk[0]*((Vpk[1][5][2]
          *Vpk[3][5][2])+((Vpk[1][5][0]*Vpk[3][5][0])+(Vpk[1][5][1]*Vpk[3][5][1]
          ))))+(mk[1]*((Vpk[1][8][2]*Vpk[3][8][2])+((Vpk[1][8][0]*Vpk[3][8][0])+
          (Vpk[1][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][14][2]*Vpk[3][14][2])+((Vpk[1][14][0]*
          Vpk[3][14][0])+(Vpk[1][14][1]*Vpk[3][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[3][13][2])+((Vpk[1][13][0]*Vpk[3][13][0])+(
          Vpk[1][13][1]*Vpk[3][13][1]))))+((mk[3]*((Vpk[1][12][2]*Vpk[3][12][2])
          +((Vpk[1][12][0]*Vpk[3][12][0])+(Vpk[1][12][1]*Vpk[3][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][21][2]*Vpk[3][21][2])+((Vpk[1][21][0]*
          Vpk[3][21][0])+(Vpk[1][21][1]*Vpk[3][21][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[3][20][2])+((Vpk[1][20][0]*Vpk[3][20][0])+(
          Vpk[1][20][1]*Vpk[3][20][1]))))+((mk[6]*((Vpk[1][17][2]*Vpk[3][17][2])
          +((Vpk[1][17][0]*Vpk[3][17][0])+(Vpk[1][17][1]*Vpk[3][17][1]))))+
          temp[1])));
        mm[1][3] = ((mk[11]*((Vpk[1][26][2]*Vpk[3][26][2])+((Vpk[1][26][0]*
          Vpk[3][26][0])+(Vpk[1][26][1]*Vpk[3][26][1]))))+((mk[10]*((
          Vpk[1][23][2]*Vpk[3][23][2])+((Vpk[1][23][0]*Vpk[3][23][0])+(
          Vpk[1][23][1]*Vpk[3][23][1]))))+((mk[9]*((Vpk[1][22][2]*Vpk[3][22][2])
          +((Vpk[1][22][0]*Vpk[3][22][0])+(Vpk[1][22][1]*Vpk[3][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[1][11][2]*Vpk[4][11][2])+((Vpk[1][11][0]*
          Vpk[4][11][0])+(Vpk[1][11][1]*Vpk[4][11][1]))))+((mk[0]*((Vpk[1][5][2]
          *Vpk[4][5][2])+((Vpk[1][5][0]*Vpk[4][5][0])+(Vpk[1][5][1]*Vpk[4][5][1]
          ))))+(mk[1]*((Vpk[1][8][2]*Vpk[4][8][2])+((Vpk[1][8][0]*Vpk[4][8][0])+
          (Vpk[1][8][1]*Vpk[4][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][14][2]*Vpk[4][14][2])+((Vpk[1][14][0]*
          Vpk[4][14][0])+(Vpk[1][14][1]*Vpk[4][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[4][13][2])+((Vpk[1][13][0]*Vpk[4][13][0])+(
          Vpk[1][13][1]*Vpk[4][13][1]))))+((mk[3]*((Vpk[1][12][2]*Vpk[4][12][2])
          +((Vpk[1][12][0]*Vpk[4][12][0])+(Vpk[1][12][1]*Vpk[4][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][21][2]*Vpk[4][21][2])+((Vpk[1][21][0]*
          Vpk[4][21][0])+(Vpk[1][21][1]*Vpk[4][21][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[4][20][2])+((Vpk[1][20][0]*Vpk[4][20][0])+(
          Vpk[1][20][1]*Vpk[4][20][1]))))+((mk[6]*((Vpk[1][17][2]*Vpk[4][17][2])
          +((Vpk[1][17][0]*Vpk[4][17][0])+(Vpk[1][17][1]*Vpk[4][17][1]))))+
          temp[1])));
        mm[1][4] = ((mk[11]*((Vpk[1][26][2]*Vpk[4][26][2])+((Vpk[1][26][0]*
          Vpk[4][26][0])+(Vpk[1][26][1]*Vpk[4][26][1]))))+((mk[10]*((
          Vpk[1][23][2]*Vpk[4][23][2])+((Vpk[1][23][0]*Vpk[4][23][0])+(
          Vpk[1][23][1]*Vpk[4][23][1]))))+((mk[9]*((Vpk[1][22][2]*Vpk[4][22][2])
          +((Vpk[1][22][0]*Vpk[4][22][0])+(Vpk[1][22][1]*Vpk[4][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[1][11][2]*Vpk[5][11][2])+((Vpk[1][11][0]*
          Vpk[5][11][0])+(Vpk[1][11][1]*Vpk[5][11][1]))))+((mk[0]*((Vpk[1][5][2]
          *Vpk[5][5][2])+((Vpk[1][5][0]*Vpk[5][5][0])+(Vpk[1][5][1]*Vpk[5][5][1]
          ))))+(mk[1]*((Vpk[1][8][2]*Vpk[5][8][2])+((Vpk[1][8][0]*Vpk[5][8][0])+
          (Vpk[1][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][14][2]*Vpk[5][14][2])+((Vpk[1][14][0]*
          Vpk[5][14][0])+(Vpk[1][14][1]*Vpk[5][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[5][13][2])+((Vpk[1][13][0]*Vpk[5][13][0])+(
          Vpk[1][13][1]*Vpk[5][13][1]))))+((mk[3]*((Vpk[1][12][2]*Vpk[5][12][2])
          +((Vpk[1][12][0]*Vpk[5][12][0])+(Vpk[1][12][1]*Vpk[5][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][21][2]*Vpk[5][21][2])+((Vpk[1][21][0]*
          Vpk[5][21][0])+(Vpk[1][21][1]*Vpk[5][21][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[5][20][2])+((Vpk[1][20][0]*Vpk[5][20][0])+(
          Vpk[1][20][1]*Vpk[5][20][1]))))+((mk[6]*((Vpk[1][17][2]*Vpk[5][17][2])
          +((Vpk[1][17][0]*Vpk[5][17][0])+(Vpk[1][17][1]*Vpk[5][17][1]))))+
          temp[1])));
        mm[1][5] = ((mk[11]*((Vpk[1][26][2]*Vpk[5][26][2])+((Vpk[1][26][0]*
          Vpk[5][26][0])+(Vpk[1][26][1]*Vpk[5][26][1]))))+((mk[10]*((
          Vpk[1][23][2]*Vpk[5][23][2])+((Vpk[1][23][0]*Vpk[5][23][0])+(
          Vpk[1][23][1]*Vpk[5][23][1]))))+((mk[9]*((Vpk[1][22][2]*Vpk[5][22][2])
          +((Vpk[1][22][0]*Vpk[5][22][0])+(Vpk[1][22][1]*Vpk[5][22][1]))))+
          temp[2])));
        temp[0] = ((mk[3]*((Vpk[1][12][2]*Vpk[6][12][2])+((Vpk[1][12][0]*
          Vpk[6][12][0])+(Vpk[1][12][1]*Vpk[6][12][1]))))+((mk[1]*((Vpk[1][8][2]
          *Vpk[6][8][2])+((Vpk[1][8][0]*Vpk[6][8][0])+(Vpk[1][8][1]*Vpk[6][8][1]
          ))))+(mk[2]*((Vpk[1][11][2]*Vpk[6][11][2])+((Vpk[1][11][0]*
          Vpk[6][11][0])+(Vpk[1][11][1]*Vpk[6][11][1]))))));
        mm[1][6] = ((mk[5]*((Vpk[1][14][2]*Vpk[6][14][2])+((Vpk[1][14][0]*
          Vpk[6][14][0])+(Vpk[1][14][1]*Vpk[6][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[6][13][2])+((Vpk[1][13][0]*Vpk[6][13][0])+(
          Vpk[1][13][1]*Vpk[6][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[1][12][2]*Vpk[7][12][2])+((Vpk[1][12][0]*
          Vpk[7][12][0])+(Vpk[1][12][1]*Vpk[7][12][1]))))+((mk[1]*((Vpk[1][8][2]
          *Vpk[7][8][2])+((Vpk[1][8][0]*Vpk[7][8][0])+(Vpk[1][8][1]*Vpk[7][8][1]
          ))))+(mk[2]*((Vpk[1][11][2]*Vpk[7][11][2])+((Vpk[1][11][0]*
          Vpk[7][11][0])+(Vpk[1][11][1]*Vpk[7][11][1]))))));
        mm[1][7] = ((mk[5]*((Vpk[1][14][2]*Vpk[7][14][2])+((Vpk[1][14][0]*
          Vpk[7][14][0])+(Vpk[1][14][1]*Vpk[7][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[7][13][2])+((Vpk[1][13][0]*Vpk[7][13][0])+(
          Vpk[1][13][1]*Vpk[7][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[1][12][2]*Vpk[8][12][2])+((Vpk[1][12][0]*
          Vpk[8][12][0])+(Vpk[1][12][1]*Vpk[8][12][1]))))+((mk[1]*((Vpk[1][8][2]
          *Vpk[8][8][2])+((Vpk[1][8][0]*Vpk[8][8][0])+(Vpk[1][8][1]*Vpk[8][8][1]
          ))))+(mk[2]*((Vpk[1][11][2]*Vpk[8][11][2])+((Vpk[1][11][0]*
          Vpk[8][11][0])+(Vpk[1][11][1]*Vpk[8][11][1]))))));
        mm[1][8] = ((mk[5]*((Vpk[1][14][2]*Vpk[8][14][2])+((Vpk[1][14][0]*
          Vpk[8][14][0])+(Vpk[1][14][1]*Vpk[8][14][1]))))+((mk[4]*((
          Vpk[1][13][2]*Vpk[8][13][2])+((Vpk[1][13][0]*Vpk[8][13][0])+(
          Vpk[1][13][1]*Vpk[8][13][1]))))+temp[0]));
        temp[0] = ((mk[4]*((Vpk[1][13][2]*Vpk[9][13][2])+((Vpk[1][13][0]*
          Vpk[9][13][0])+(Vpk[1][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[1][11][2]*Vpk[9][11][2])+((Vpk[1][11][0]*Vpk[9][11][0])+(
          Vpk[1][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[1][12][2]*Vpk[9][12][2])+
          ((Vpk[1][12][0]*Vpk[9][12][0])+(Vpk[1][12][1]*Vpk[9][12][1]))))));
        mm[1][9] = ((mk[5]*((Vpk[1][14][2]*Vpk[9][14][2])+((Vpk[1][14][0]*
          Vpk[9][14][0])+(Vpk[1][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[1][13][2]*Vpk[10][13][2])+((Vpk[1][13][0]*
          Vpk[10][13][0])+(Vpk[1][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[1][11][2]*Vpk[10][11][2])+((Vpk[1][11][0]*Vpk[10][11][0])+(
          Vpk[1][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[1][12][2]*Vpk[10][12][2]
          )+((Vpk[1][12][0]*Vpk[10][12][0])+(Vpk[1][12][1]*Vpk[10][12][1]))))));
        mm[1][10] = ((mk[5]*((Vpk[1][14][2]*Vpk[10][14][2])+((Vpk[1][14][0]*
          Vpk[10][14][0])+(Vpk[1][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[1][13][2]*Vpk[11][13][2])+((Vpk[1][13][0]*
          Vpk[11][13][0])+(Vpk[1][13][1]*Vpk[11][13][1]))))+((mk[2]*((
          Vpk[1][11][2]*Vpk[11][11][2])+((Vpk[1][11][0]*Vpk[11][11][0])+(
          Vpk[1][11][1]*Vpk[11][11][1]))))+(mk[3]*((Vpk[1][12][2]*Vpk[11][12][2]
          )+((Vpk[1][12][0]*Vpk[11][12][0])+(Vpk[1][12][1]*Vpk[11][12][1]))))));
        mm[1][11] = ((mk[5]*((Vpk[1][14][2]*Vpk[11][14][2])+((Vpk[1][14][0]*
          Vpk[11][14][0])+(Vpk[1][14][1]*Vpk[11][14][1]))))+temp[0]);
        mm[1][12] = ((mk[5]*((Vpk[1][14][2]*Vpk[12][14][2])+((Vpk[1][14][0]*
          Vpk[12][14][0])+(Vpk[1][14][1]*Vpk[12][14][1]))))+((mk[3]*((
          Vpk[1][12][2]*Vpk[12][12][2])+((Vpk[1][12][0]*Vpk[12][12][0])+(
          Vpk[1][12][1]*Vpk[12][12][1]))))+(mk[4]*((Vpk[1][13][2]*Vpk[12][13][2]
          )+((Vpk[1][13][0]*Vpk[12][13][0])+(Vpk[1][13][1]*Vpk[12][13][1]))))));
        mm[1][13] = ((mk[4]*((Vpk[1][13][2]*Vpk[13][13][2])+((Vpk[1][13][0]*
          Vpk[13][13][0])+(Vpk[1][13][1]*Vpk[13][13][1]))))+(mk[5]*((
          Vpk[1][14][2]*Vpk[13][14][2])+((Vpk[1][14][0]*Vpk[13][14][0])+(
          Vpk[1][14][1]*Vpk[13][14][1])))));
        mm[1][14] = (mk[5]*((Vpk[1][14][2]*Vpk[14][14][2])+((Vpk[1][14][0]*
          Vpk[14][14][0])+(Vpk[1][14][1]*Vpk[14][14][1]))));
        temp[0] = ((mk[8]*((Vpk[1][21][2]*Vpk[15][21][2])+((Vpk[1][21][0]*
          Vpk[15][21][0])+(Vpk[1][21][1]*Vpk[15][21][1]))))+((mk[6]*((
          Vpk[1][17][2]*Vpk[15][17][2])+((Vpk[1][17][0]*Vpk[15][17][0])+(
          Vpk[1][17][1]*Vpk[15][17][1]))))+(mk[7]*((Vpk[1][20][2]*Vpk[15][20][2]
          )+((Vpk[1][20][0]*Vpk[15][20][0])+(Vpk[1][20][1]*Vpk[15][20][1]))))));
        mm[1][15] = ((mk[10]*((Vpk[1][23][2]*Vpk[15][23][2])+((Vpk[1][23][0]*
          Vpk[15][23][0])+(Vpk[1][23][1]*Vpk[15][23][1]))))+((mk[9]*((
          Vpk[1][22][2]*Vpk[15][22][2])+((Vpk[1][22][0]*Vpk[15][22][0])+(
          Vpk[1][22][1]*Vpk[15][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[1][21][2]*Vpk[16][21][2])+((Vpk[1][21][0]*
          Vpk[16][21][0])+(Vpk[1][21][1]*Vpk[16][21][1]))))+((mk[6]*((
          Vpk[1][17][2]*Vpk[16][17][2])+((Vpk[1][17][0]*Vpk[16][17][0])+(
          Vpk[1][17][1]*Vpk[16][17][1]))))+(mk[7]*((Vpk[1][20][2]*Vpk[16][20][2]
          )+((Vpk[1][20][0]*Vpk[16][20][0])+(Vpk[1][20][1]*Vpk[16][20][1]))))));
        mm[1][16] = ((mk[10]*((Vpk[1][23][2]*Vpk[16][23][2])+((Vpk[1][23][0]*
          Vpk[16][23][0])+(Vpk[1][23][1]*Vpk[16][23][1]))))+((mk[9]*((
          Vpk[1][22][2]*Vpk[16][22][2])+((Vpk[1][22][0]*Vpk[16][22][0])+(
          Vpk[1][22][1]*Vpk[16][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[1][21][2]*Vpk[17][21][2])+((Vpk[1][21][0]*
          Vpk[17][21][0])+(Vpk[1][21][1]*Vpk[17][21][1]))))+((mk[6]*((
          Vpk[1][17][2]*Vpk[17][17][2])+((Vpk[1][17][0]*Vpk[17][17][0])+(
          Vpk[1][17][1]*Vpk[17][17][1]))))+(mk[7]*((Vpk[1][20][2]*Vpk[17][20][2]
          )+((Vpk[1][20][0]*Vpk[17][20][0])+(Vpk[1][20][1]*Vpk[17][20][1]))))));
        mm[1][17] = ((mk[10]*((Vpk[1][23][2]*Vpk[17][23][2])+((Vpk[1][23][0]*
          Vpk[17][23][0])+(Vpk[1][23][1]*Vpk[17][23][1]))))+((mk[9]*((
          Vpk[1][22][2]*Vpk[17][22][2])+((Vpk[1][22][0]*Vpk[17][22][0])+(
          Vpk[1][22][1]*Vpk[17][22][1]))))+temp[0]));
        temp[0] = ((mk[9]*((Vpk[1][22][2]*Vpk[18][22][2])+((Vpk[1][22][0]*
          Vpk[18][22][0])+(Vpk[1][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[18][20][2])+((Vpk[1][20][0]*Vpk[18][20][0])+(
          Vpk[1][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[1][21][2]*Vpk[18][21][2]
          )+((Vpk[1][21][0]*Vpk[18][21][0])+(Vpk[1][21][1]*Vpk[18][21][1]))))));
        mm[1][18] = ((mk[10]*((Vpk[1][23][2]*Vpk[18][23][2])+((Vpk[1][23][0]*
          Vpk[18][23][0])+(Vpk[1][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[1][22][2]*Vpk[19][22][2])+((Vpk[1][22][0]*
          Vpk[19][22][0])+(Vpk[1][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[19][20][2])+((Vpk[1][20][0]*Vpk[19][20][0])+(
          Vpk[1][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[1][21][2]*Vpk[19][21][2]
          )+((Vpk[1][21][0]*Vpk[19][21][0])+(Vpk[1][21][1]*Vpk[19][21][1]))))));
        mm[1][19] = ((mk[10]*((Vpk[1][23][2]*Vpk[19][23][2])+((Vpk[1][23][0]*
          Vpk[19][23][0])+(Vpk[1][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[1][22][2]*Vpk[20][22][2])+((Vpk[1][22][0]*
          Vpk[20][22][0])+(Vpk[1][22][1]*Vpk[20][22][1]))))+((mk[7]*((
          Vpk[1][20][2]*Vpk[20][20][2])+((Vpk[1][20][0]*Vpk[20][20][0])+(
          Vpk[1][20][1]*Vpk[20][20][1]))))+(mk[8]*((Vpk[1][21][2]*Vpk[20][21][2]
          )+((Vpk[1][21][0]*Vpk[20][21][0])+(Vpk[1][21][1]*Vpk[20][21][1]))))));
        mm[1][20] = ((mk[10]*((Vpk[1][23][2]*Vpk[20][23][2])+((Vpk[1][23][0]*
          Vpk[20][23][0])+(Vpk[1][23][1]*Vpk[20][23][1]))))+temp[0]);
        mm[1][21] = ((mk[10]*((Vpk[1][23][2]*Vpk[21][23][2])+((Vpk[1][23][0]*
          Vpk[21][23][0])+(Vpk[1][23][1]*Vpk[21][23][1]))))+((mk[8]*((
          Vpk[1][21][2]*Vpk[21][21][2])+((Vpk[1][21][0]*Vpk[21][21][0])+(
          Vpk[1][21][1]*Vpk[21][21][1]))))+(mk[9]*((Vpk[1][22][2]*Vpk[21][22][2]
          )+((Vpk[1][22][0]*Vpk[21][22][0])+(Vpk[1][22][1]*Vpk[21][22][1]))))));
        mm[1][22] = ((mk[9]*((Vpk[1][22][2]*Vpk[22][22][2])+((Vpk[1][22][0]*
          Vpk[22][22][0])+(Vpk[1][22][1]*Vpk[22][22][1]))))+(mk[10]*((
          Vpk[1][23][2]*Vpk[22][23][2])+((Vpk[1][23][0]*Vpk[22][23][0])+(
          Vpk[1][23][1]*Vpk[22][23][1])))));
        mm[1][23] = (mk[10]*((Vpk[1][23][2]*Vpk[23][23][2])+((Vpk[1][23][0]*
          Vpk[23][23][0])+(Vpk[1][23][1]*Vpk[23][23][1]))));
        mm[1][24] = (mk[11]*((Vpk[1][26][2]*Vpk[24][26][2])+((Vpk[1][26][0]*
          Vpk[24][26][0])+(Vpk[1][26][1]*Vpk[24][26][1]))));
        mm[1][25] = (mk[11]*((Vpk[1][26][2]*Vpk[25][26][2])+((Vpk[1][26][0]*
          Vpk[25][26][0])+(Vpk[1][26][1]*Vpk[25][26][1]))));
        mm[1][26] = (mk[11]*((Vpk[1][26][2]*Vpk[26][26][2])+((Vpk[1][26][0]*
          Vpk[26][26][0])+(Vpk[1][26][1]*Vpk[26][26][1]))));
        temp[0] = ((mk[2]*((Vpk[2][11][2]*Vpk[2][11][2])+((Vpk[2][11][0]*
          Vpk[2][11][0])+(Vpk[2][11][1]*Vpk[2][11][1]))))+((mk[0]*((Vpk[2][5][2]
          *Vpk[2][5][2])+((Vpk[2][5][0]*Vpk[2][5][0])+(Vpk[2][5][1]*Vpk[2][5][1]
          ))))+(mk[1]*((Vpk[2][8][2]*Vpk[2][8][2])+((Vpk[2][8][0]*Vpk[2][8][0])+
          (Vpk[2][8][1]*Vpk[2][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][14][2]*Vpk[2][14][2])+((Vpk[2][14][0]*
          Vpk[2][14][0])+(Vpk[2][14][1]*Vpk[2][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[2][13][2])+((Vpk[2][13][0]*Vpk[2][13][0])+(
          Vpk[2][13][1]*Vpk[2][13][1]))))+((mk[3]*((Vpk[2][12][2]*Vpk[2][12][2])
          +((Vpk[2][12][0]*Vpk[2][12][0])+(Vpk[2][12][1]*Vpk[2][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][21][2]*Vpk[2][21][2])+((Vpk[2][21][0]*
          Vpk[2][21][0])+(Vpk[2][21][1]*Vpk[2][21][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[2][20][2])+((Vpk[2][20][0]*Vpk[2][20][0])+(
          Vpk[2][20][1]*Vpk[2][20][1]))))+((mk[6]*((Vpk[2][17][2]*Vpk[2][17][2])
          +((Vpk[2][17][0]*Vpk[2][17][0])+(Vpk[2][17][1]*Vpk[2][17][1]))))+
          temp[1])));
        mm[2][2] = ((mk[11]*((Vpk[2][26][2]*Vpk[2][26][2])+((Vpk[2][26][0]*
          Vpk[2][26][0])+(Vpk[2][26][1]*Vpk[2][26][1]))))+((mk[10]*((
          Vpk[2][23][2]*Vpk[2][23][2])+((Vpk[2][23][0]*Vpk[2][23][0])+(
          Vpk[2][23][1]*Vpk[2][23][1]))))+((mk[9]*((Vpk[2][22][2]*Vpk[2][22][2])
          +((Vpk[2][22][0]*Vpk[2][22][0])+(Vpk[2][22][1]*Vpk[2][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[2][11][2]*Vpk[3][11][2])+((Vpk[2][11][0]*
          Vpk[3][11][0])+(Vpk[2][11][1]*Vpk[3][11][1]))))+((mk[0]*((Vpk[2][5][2]
          *Vpk[3][5][2])+((Vpk[2][5][0]*Vpk[3][5][0])+(Vpk[2][5][1]*Vpk[3][5][1]
          ))))+(mk[1]*((Vpk[2][8][2]*Vpk[3][8][2])+((Vpk[2][8][0]*Vpk[3][8][0])+
          (Vpk[2][8][1]*Vpk[3][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][14][2]*Vpk[3][14][2])+((Vpk[2][14][0]*
          Vpk[3][14][0])+(Vpk[2][14][1]*Vpk[3][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[3][13][2])+((Vpk[2][13][0]*Vpk[3][13][0])+(
          Vpk[2][13][1]*Vpk[3][13][1]))))+((mk[3]*((Vpk[2][12][2]*Vpk[3][12][2])
          +((Vpk[2][12][0]*Vpk[3][12][0])+(Vpk[2][12][1]*Vpk[3][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][21][2]*Vpk[3][21][2])+((Vpk[2][21][0]*
          Vpk[3][21][0])+(Vpk[2][21][1]*Vpk[3][21][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[3][20][2])+((Vpk[2][20][0]*Vpk[3][20][0])+(
          Vpk[2][20][1]*Vpk[3][20][1]))))+((mk[6]*((Vpk[2][17][2]*Vpk[3][17][2])
          +((Vpk[2][17][0]*Vpk[3][17][0])+(Vpk[2][17][1]*Vpk[3][17][1]))))+
          temp[1])));
        mm[2][3] = ((mk[11]*((Vpk[2][26][2]*Vpk[3][26][2])+((Vpk[2][26][0]*
          Vpk[3][26][0])+(Vpk[2][26][1]*Vpk[3][26][1]))))+((mk[10]*((
          Vpk[2][23][2]*Vpk[3][23][2])+((Vpk[2][23][0]*Vpk[3][23][0])+(
          Vpk[2][23][1]*Vpk[3][23][1]))))+((mk[9]*((Vpk[2][22][2]*Vpk[3][22][2])
          +((Vpk[2][22][0]*Vpk[3][22][0])+(Vpk[2][22][1]*Vpk[3][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[2][11][2]*Vpk[4][11][2])+((Vpk[2][11][0]*
          Vpk[4][11][0])+(Vpk[2][11][1]*Vpk[4][11][1]))))+((mk[0]*((Vpk[2][5][2]
          *Vpk[4][5][2])+((Vpk[2][5][0]*Vpk[4][5][0])+(Vpk[2][5][1]*Vpk[4][5][1]
          ))))+(mk[1]*((Vpk[2][8][2]*Vpk[4][8][2])+((Vpk[2][8][0]*Vpk[4][8][0])+
          (Vpk[2][8][1]*Vpk[4][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][14][2]*Vpk[4][14][2])+((Vpk[2][14][0]*
          Vpk[4][14][0])+(Vpk[2][14][1]*Vpk[4][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[4][13][2])+((Vpk[2][13][0]*Vpk[4][13][0])+(
          Vpk[2][13][1]*Vpk[4][13][1]))))+((mk[3]*((Vpk[2][12][2]*Vpk[4][12][2])
          +((Vpk[2][12][0]*Vpk[4][12][0])+(Vpk[2][12][1]*Vpk[4][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][21][2]*Vpk[4][21][2])+((Vpk[2][21][0]*
          Vpk[4][21][0])+(Vpk[2][21][1]*Vpk[4][21][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[4][20][2])+((Vpk[2][20][0]*Vpk[4][20][0])+(
          Vpk[2][20][1]*Vpk[4][20][1]))))+((mk[6]*((Vpk[2][17][2]*Vpk[4][17][2])
          +((Vpk[2][17][0]*Vpk[4][17][0])+(Vpk[2][17][1]*Vpk[4][17][1]))))+
          temp[1])));
        mm[2][4] = ((mk[11]*((Vpk[2][26][2]*Vpk[4][26][2])+((Vpk[2][26][0]*
          Vpk[4][26][0])+(Vpk[2][26][1]*Vpk[4][26][1]))))+((mk[10]*((
          Vpk[2][23][2]*Vpk[4][23][2])+((Vpk[2][23][0]*Vpk[4][23][0])+(
          Vpk[2][23][1]*Vpk[4][23][1]))))+((mk[9]*((Vpk[2][22][2]*Vpk[4][22][2])
          +((Vpk[2][22][0]*Vpk[4][22][0])+(Vpk[2][22][1]*Vpk[4][22][1]))))+
          temp[2])));
        temp[0] = ((mk[2]*((Vpk[2][11][2]*Vpk[5][11][2])+((Vpk[2][11][0]*
          Vpk[5][11][0])+(Vpk[2][11][1]*Vpk[5][11][1]))))+((mk[0]*((Vpk[2][5][2]
          *Vpk[5][5][2])+((Vpk[2][5][0]*Vpk[5][5][0])+(Vpk[2][5][1]*Vpk[5][5][1]
          ))))+(mk[1]*((Vpk[2][8][2]*Vpk[5][8][2])+((Vpk[2][8][0]*Vpk[5][8][0])+
          (Vpk[2][8][1]*Vpk[5][8][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][14][2]*Vpk[5][14][2])+((Vpk[2][14][0]*
          Vpk[5][14][0])+(Vpk[2][14][1]*Vpk[5][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[5][13][2])+((Vpk[2][13][0]*Vpk[5][13][0])+(
          Vpk[2][13][1]*Vpk[5][13][1]))))+((mk[3]*((Vpk[2][12][2]*Vpk[5][12][2])
          +((Vpk[2][12][0]*Vpk[5][12][0])+(Vpk[2][12][1]*Vpk[5][12][1]))))+
          temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][21][2]*Vpk[5][21][2])+((Vpk[2][21][0]*
          Vpk[5][21][0])+(Vpk[2][21][1]*Vpk[5][21][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[5][20][2])+((Vpk[2][20][0]*Vpk[5][20][0])+(
          Vpk[2][20][1]*Vpk[5][20][1]))))+((mk[6]*((Vpk[2][17][2]*Vpk[5][17][2])
          +((Vpk[2][17][0]*Vpk[5][17][0])+(Vpk[2][17][1]*Vpk[5][17][1]))))+
          temp[1])));
        mm[2][5] = ((mk[11]*((Vpk[2][26][2]*Vpk[5][26][2])+((Vpk[2][26][0]*
          Vpk[5][26][0])+(Vpk[2][26][1]*Vpk[5][26][1]))))+((mk[10]*((
          Vpk[2][23][2]*Vpk[5][23][2])+((Vpk[2][23][0]*Vpk[5][23][0])+(
          Vpk[2][23][1]*Vpk[5][23][1]))))+((mk[9]*((Vpk[2][22][2]*Vpk[5][22][2])
          +((Vpk[2][22][0]*Vpk[5][22][0])+(Vpk[2][22][1]*Vpk[5][22][1]))))+
          temp[2])));
        temp[0] = ((mk[3]*((Vpk[2][12][2]*Vpk[6][12][2])+((Vpk[2][12][0]*
          Vpk[6][12][0])+(Vpk[2][12][1]*Vpk[6][12][1]))))+((mk[1]*((Vpk[2][8][2]
          *Vpk[6][8][2])+((Vpk[2][8][0]*Vpk[6][8][0])+(Vpk[2][8][1]*Vpk[6][8][1]
          ))))+(mk[2]*((Vpk[2][11][2]*Vpk[6][11][2])+((Vpk[2][11][0]*
          Vpk[6][11][0])+(Vpk[2][11][1]*Vpk[6][11][1]))))));
        mm[2][6] = ((mk[5]*((Vpk[2][14][2]*Vpk[6][14][2])+((Vpk[2][14][0]*
          Vpk[6][14][0])+(Vpk[2][14][1]*Vpk[6][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[6][13][2])+((Vpk[2][13][0]*Vpk[6][13][0])+(
          Vpk[2][13][1]*Vpk[6][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[2][12][2]*Vpk[7][12][2])+((Vpk[2][12][0]*
          Vpk[7][12][0])+(Vpk[2][12][1]*Vpk[7][12][1]))))+((mk[1]*((Vpk[2][8][2]
          *Vpk[7][8][2])+((Vpk[2][8][0]*Vpk[7][8][0])+(Vpk[2][8][1]*Vpk[7][8][1]
          ))))+(mk[2]*((Vpk[2][11][2]*Vpk[7][11][2])+((Vpk[2][11][0]*
          Vpk[7][11][0])+(Vpk[2][11][1]*Vpk[7][11][1]))))));
        mm[2][7] = ((mk[5]*((Vpk[2][14][2]*Vpk[7][14][2])+((Vpk[2][14][0]*
          Vpk[7][14][0])+(Vpk[2][14][1]*Vpk[7][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[7][13][2])+((Vpk[2][13][0]*Vpk[7][13][0])+(
          Vpk[2][13][1]*Vpk[7][13][1]))))+temp[0]));
        temp[0] = ((mk[3]*((Vpk[2][12][2]*Vpk[8][12][2])+((Vpk[2][12][0]*
          Vpk[8][12][0])+(Vpk[2][12][1]*Vpk[8][12][1]))))+((mk[1]*((Vpk[2][8][2]
          *Vpk[8][8][2])+((Vpk[2][8][0]*Vpk[8][8][0])+(Vpk[2][8][1]*Vpk[8][8][1]
          ))))+(mk[2]*((Vpk[2][11][2]*Vpk[8][11][2])+((Vpk[2][11][0]*
          Vpk[8][11][0])+(Vpk[2][11][1]*Vpk[8][11][1]))))));
        mm[2][8] = ((mk[5]*((Vpk[2][14][2]*Vpk[8][14][2])+((Vpk[2][14][0]*
          Vpk[8][14][0])+(Vpk[2][14][1]*Vpk[8][14][1]))))+((mk[4]*((
          Vpk[2][13][2]*Vpk[8][13][2])+((Vpk[2][13][0]*Vpk[8][13][0])+(
          Vpk[2][13][1]*Vpk[8][13][1]))))+temp[0]));
        temp[0] = ((mk[4]*((Vpk[2][13][2]*Vpk[9][13][2])+((Vpk[2][13][0]*
          Vpk[9][13][0])+(Vpk[2][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[2][11][2]*Vpk[9][11][2])+((Vpk[2][11][0]*Vpk[9][11][0])+(
          Vpk[2][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[2][12][2]*Vpk[9][12][2])+
          ((Vpk[2][12][0]*Vpk[9][12][0])+(Vpk[2][12][1]*Vpk[9][12][1]))))));
        mm[2][9] = ((mk[5]*((Vpk[2][14][2]*Vpk[9][14][2])+((Vpk[2][14][0]*
          Vpk[9][14][0])+(Vpk[2][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[2][13][2]*Vpk[10][13][2])+((Vpk[2][13][0]*
          Vpk[10][13][0])+(Vpk[2][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[2][11][2]*Vpk[10][11][2])+((Vpk[2][11][0]*Vpk[10][11][0])+(
          Vpk[2][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[2][12][2]*Vpk[10][12][2]
          )+((Vpk[2][12][0]*Vpk[10][12][0])+(Vpk[2][12][1]*Vpk[10][12][1]))))));
        mm[2][10] = ((mk[5]*((Vpk[2][14][2]*Vpk[10][14][2])+((Vpk[2][14][0]*
          Vpk[10][14][0])+(Vpk[2][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[2][13][2]*Vpk[11][13][2])+((Vpk[2][13][0]*
          Vpk[11][13][0])+(Vpk[2][13][1]*Vpk[11][13][1]))))+((mk[2]*((
          Vpk[2][11][2]*Vpk[11][11][2])+((Vpk[2][11][0]*Vpk[11][11][0])+(
          Vpk[2][11][1]*Vpk[11][11][1]))))+(mk[3]*((Vpk[2][12][2]*Vpk[11][12][2]
          )+((Vpk[2][12][0]*Vpk[11][12][0])+(Vpk[2][12][1]*Vpk[11][12][1]))))));
        mm[2][11] = ((mk[5]*((Vpk[2][14][2]*Vpk[11][14][2])+((Vpk[2][14][0]*
          Vpk[11][14][0])+(Vpk[2][14][1]*Vpk[11][14][1]))))+temp[0]);
        mm[2][12] = ((mk[5]*((Vpk[2][14][2]*Vpk[12][14][2])+((Vpk[2][14][0]*
          Vpk[12][14][0])+(Vpk[2][14][1]*Vpk[12][14][1]))))+((mk[3]*((
          Vpk[2][12][2]*Vpk[12][12][2])+((Vpk[2][12][0]*Vpk[12][12][0])+(
          Vpk[2][12][1]*Vpk[12][12][1]))))+(mk[4]*((Vpk[2][13][2]*Vpk[12][13][2]
          )+((Vpk[2][13][0]*Vpk[12][13][0])+(Vpk[2][13][1]*Vpk[12][13][1]))))));
        mm[2][13] = ((mk[4]*((Vpk[2][13][2]*Vpk[13][13][2])+((Vpk[2][13][0]*
          Vpk[13][13][0])+(Vpk[2][13][1]*Vpk[13][13][1]))))+(mk[5]*((
          Vpk[2][14][2]*Vpk[13][14][2])+((Vpk[2][14][0]*Vpk[13][14][0])+(
          Vpk[2][14][1]*Vpk[13][14][1])))));
        mm[2][14] = (mk[5]*((Vpk[2][14][2]*Vpk[14][14][2])+((Vpk[2][14][0]*
          Vpk[14][14][0])+(Vpk[2][14][1]*Vpk[14][14][1]))));
        temp[0] = ((mk[8]*((Vpk[2][21][2]*Vpk[15][21][2])+((Vpk[2][21][0]*
          Vpk[15][21][0])+(Vpk[2][21][1]*Vpk[15][21][1]))))+((mk[6]*((
          Vpk[2][17][2]*Vpk[15][17][2])+((Vpk[2][17][0]*Vpk[15][17][0])+(
          Vpk[2][17][1]*Vpk[15][17][1]))))+(mk[7]*((Vpk[2][20][2]*Vpk[15][20][2]
          )+((Vpk[2][20][0]*Vpk[15][20][0])+(Vpk[2][20][1]*Vpk[15][20][1]))))));
        mm[2][15] = ((mk[10]*((Vpk[2][23][2]*Vpk[15][23][2])+((Vpk[2][23][0]*
          Vpk[15][23][0])+(Vpk[2][23][1]*Vpk[15][23][1]))))+((mk[9]*((
          Vpk[2][22][2]*Vpk[15][22][2])+((Vpk[2][22][0]*Vpk[15][22][0])+(
          Vpk[2][22][1]*Vpk[15][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[2][21][2]*Vpk[16][21][2])+((Vpk[2][21][0]*
          Vpk[16][21][0])+(Vpk[2][21][1]*Vpk[16][21][1]))))+((mk[6]*((
          Vpk[2][17][2]*Vpk[16][17][2])+((Vpk[2][17][0]*Vpk[16][17][0])+(
          Vpk[2][17][1]*Vpk[16][17][1]))))+(mk[7]*((Vpk[2][20][2]*Vpk[16][20][2]
          )+((Vpk[2][20][0]*Vpk[16][20][0])+(Vpk[2][20][1]*Vpk[16][20][1]))))));
        mm[2][16] = ((mk[10]*((Vpk[2][23][2]*Vpk[16][23][2])+((Vpk[2][23][0]*
          Vpk[16][23][0])+(Vpk[2][23][1]*Vpk[16][23][1]))))+((mk[9]*((
          Vpk[2][22][2]*Vpk[16][22][2])+((Vpk[2][22][0]*Vpk[16][22][0])+(
          Vpk[2][22][1]*Vpk[16][22][1]))))+temp[0]));
        temp[0] = ((mk[8]*((Vpk[2][21][2]*Vpk[17][21][2])+((Vpk[2][21][0]*
          Vpk[17][21][0])+(Vpk[2][21][1]*Vpk[17][21][1]))))+((mk[6]*((
          Vpk[2][17][2]*Vpk[17][17][2])+((Vpk[2][17][0]*Vpk[17][17][0])+(
          Vpk[2][17][1]*Vpk[17][17][1]))))+(mk[7]*((Vpk[2][20][2]*Vpk[17][20][2]
          )+((Vpk[2][20][0]*Vpk[17][20][0])+(Vpk[2][20][1]*Vpk[17][20][1]))))));
        mm[2][17] = ((mk[10]*((Vpk[2][23][2]*Vpk[17][23][2])+((Vpk[2][23][0]*
          Vpk[17][23][0])+(Vpk[2][23][1]*Vpk[17][23][1]))))+((mk[9]*((
          Vpk[2][22][2]*Vpk[17][22][2])+((Vpk[2][22][0]*Vpk[17][22][0])+(
          Vpk[2][22][1]*Vpk[17][22][1]))))+temp[0]));
        temp[0] = ((mk[9]*((Vpk[2][22][2]*Vpk[18][22][2])+((Vpk[2][22][0]*
          Vpk[18][22][0])+(Vpk[2][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[18][20][2])+((Vpk[2][20][0]*Vpk[18][20][0])+(
          Vpk[2][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[2][21][2]*Vpk[18][21][2]
          )+((Vpk[2][21][0]*Vpk[18][21][0])+(Vpk[2][21][1]*Vpk[18][21][1]))))));
        mm[2][18] = ((mk[10]*((Vpk[2][23][2]*Vpk[18][23][2])+((Vpk[2][23][0]*
          Vpk[18][23][0])+(Vpk[2][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[2][22][2]*Vpk[19][22][2])+((Vpk[2][22][0]*
          Vpk[19][22][0])+(Vpk[2][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[19][20][2])+((Vpk[2][20][0]*Vpk[19][20][0])+(
          Vpk[2][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[2][21][2]*Vpk[19][21][2]
          )+((Vpk[2][21][0]*Vpk[19][21][0])+(Vpk[2][21][1]*Vpk[19][21][1]))))));
        mm[2][19] = ((mk[10]*((Vpk[2][23][2]*Vpk[19][23][2])+((Vpk[2][23][0]*
          Vpk[19][23][0])+(Vpk[2][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[2][22][2]*Vpk[20][22][2])+((Vpk[2][22][0]*
          Vpk[20][22][0])+(Vpk[2][22][1]*Vpk[20][22][1]))))+((mk[7]*((
          Vpk[2][20][2]*Vpk[20][20][2])+((Vpk[2][20][0]*Vpk[20][20][0])+(
          Vpk[2][20][1]*Vpk[20][20][1]))))+(mk[8]*((Vpk[2][21][2]*Vpk[20][21][2]
          )+((Vpk[2][21][0]*Vpk[20][21][0])+(Vpk[2][21][1]*Vpk[20][21][1]))))));
        mm[2][20] = ((mk[10]*((Vpk[2][23][2]*Vpk[20][23][2])+((Vpk[2][23][0]*
          Vpk[20][23][0])+(Vpk[2][23][1]*Vpk[20][23][1]))))+temp[0]);
        mm[2][21] = ((mk[10]*((Vpk[2][23][2]*Vpk[21][23][2])+((Vpk[2][23][0]*
          Vpk[21][23][0])+(Vpk[2][23][1]*Vpk[21][23][1]))))+((mk[8]*((
          Vpk[2][21][2]*Vpk[21][21][2])+((Vpk[2][21][0]*Vpk[21][21][0])+(
          Vpk[2][21][1]*Vpk[21][21][1]))))+(mk[9]*((Vpk[2][22][2]*Vpk[21][22][2]
          )+((Vpk[2][22][0]*Vpk[21][22][0])+(Vpk[2][22][1]*Vpk[21][22][1]))))));
        mm[2][22] = ((mk[9]*((Vpk[2][22][2]*Vpk[22][22][2])+((Vpk[2][22][0]*
          Vpk[22][22][0])+(Vpk[2][22][1]*Vpk[22][22][1]))))+(mk[10]*((
          Vpk[2][23][2]*Vpk[22][23][2])+((Vpk[2][23][0]*Vpk[22][23][0])+(
          Vpk[2][23][1]*Vpk[22][23][1])))));
        mm[2][23] = (mk[10]*((Vpk[2][23][2]*Vpk[23][23][2])+((Vpk[2][23][0]*
          Vpk[23][23][0])+(Vpk[2][23][1]*Vpk[23][23][1]))));
        mm[2][24] = (mk[11]*((Vpk[2][26][2]*Vpk[24][26][2])+((Vpk[2][26][0]*
          Vpk[24][26][0])+(Vpk[2][26][1]*Vpk[24][26][1]))));
        mm[2][25] = (mk[11]*((Vpk[2][26][2]*Vpk[25][26][2])+((Vpk[2][26][0]*
          Vpk[25][26][0])+(Vpk[2][26][1]*Vpk[25][26][1]))));
        mm[2][26] = (mk[11]*((Vpk[2][26][2]*Vpk[26][26][2])+((Vpk[2][26][0]*
          Vpk[26][26][0])+(Vpk[2][26][1]*Vpk[26][26][1]))));
        temp[0] = (((mk[0]*((Vpk[3][5][2]*Vpk[3][5][2])+((Vpk[3][5][0]*
          Vpk[3][5][0])+(Vpk[3][5][1]*Vpk[3][5][1]))))+((IkWpk[3][5][2]*
          Wpk[3][5][2])+((IkWpk[3][5][0]*Wpk[3][5][0])+(IkWpk[3][5][1]*
          Wpk[3][5][1]))))+((mk[1]*((Vpk[3][8][2]*Vpk[3][8][2])+((Vpk[3][8][0]*
          Vpk[3][8][0])+(Vpk[3][8][1]*Vpk[3][8][1]))))+((IkWpk[3][8][2]*
          Wpk[3][8][2])+((IkWpk[3][8][0]*Wpk[3][8][0])+(IkWpk[3][8][1]*
          Wpk[3][8][1])))));
        temp[1] = (((mk[2]*((Vpk[3][11][2]*Vpk[3][11][2])+((Vpk[3][11][0]*
          Vpk[3][11][0])+(Vpk[3][11][1]*Vpk[3][11][1]))))+((IkWpk[3][11][2]*
          Wpk[3][11][2])+((IkWpk[3][11][0]*Wpk[3][11][0])+(IkWpk[3][11][1]*
          Wpk[3][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][12][2]*Vpk[3][12][2])+((Vpk[3][12][0]*
          Vpk[3][12][0])+(Vpk[3][12][1]*Vpk[3][12][1]))))+((IkWpk[3][12][2]*
          Wpk[3][12][2])+((IkWpk[3][12][0]*Wpk[3][12][0])+(IkWpk[3][12][1]*
          Wpk[3][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][13][2]*Vpk[3][13][2])+((Vpk[3][13][0]*
          Vpk[3][13][0])+(Vpk[3][13][1]*Vpk[3][13][1]))))+((IkWpk[3][13][2]*
          Wpk[3][13][2])+((IkWpk[3][13][0]*Wpk[3][13][0])+(IkWpk[3][13][1]*
          Wpk[3][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][14][2]*Vpk[3][14][2])+((Vpk[3][14][0]*
          Vpk[3][14][0])+(Vpk[3][14][1]*Vpk[3][14][1]))))+((IkWpk[3][14][2]*
          Wpk[3][14][2])+((IkWpk[3][14][0]*Wpk[3][14][0])+(IkWpk[3][14][1]*
          Wpk[3][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][17][2]*Vpk[3][17][2])+((Vpk[3][17][0]*
          Vpk[3][17][0])+(Vpk[3][17][1]*Vpk[3][17][1]))))+((IkWpk[3][17][2]*
          Wpk[3][17][2])+((IkWpk[3][17][0]*Wpk[3][17][0])+(IkWpk[3][17][1]*
          Wpk[3][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][20][2]*Vpk[3][20][2])+((Vpk[3][20][0]*
          Vpk[3][20][0])+(Vpk[3][20][1]*Vpk[3][20][1]))))+((IkWpk[3][20][2]*
          Wpk[3][20][2])+((IkWpk[3][20][0]*Wpk[3][20][0])+(IkWpk[3][20][1]*
          Wpk[3][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][21][2]*Vpk[3][21][2])+((Vpk[3][21][0]*
          Vpk[3][21][0])+(Vpk[3][21][1]*Vpk[3][21][1]))))+((IkWpk[3][21][2]*
          Wpk[3][21][2])+((IkWpk[3][21][0]*Wpk[3][21][0])+(IkWpk[3][21][1]*
          Wpk[3][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[3][22][2]*Vpk[3][22][2])+((Vpk[3][22][0]*
          Vpk[3][22][0])+(Vpk[3][22][1]*Vpk[3][22][1]))))+((IkWpk[3][22][2]*
          Wpk[3][22][2])+((IkWpk[3][22][0]*Wpk[3][22][0])+(IkWpk[3][22][1]*
          Wpk[3][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[3][23][2]*Vpk[3][23][2])+((Vpk[3][23][0]*
          Vpk[3][23][0])+(Vpk[3][23][1]*Vpk[3][23][1]))))+((IkWpk[3][23][2]*
          Wpk[3][23][2])+((IkWpk[3][23][0]*Wpk[3][23][0])+(IkWpk[3][23][1]*
          Wpk[3][23][1]))))+temp[8]);
        mm[3][3] = (((mk[11]*((Vpk[3][26][2]*Vpk[3][26][2])+((Vpk[3][26][0]*
          Vpk[3][26][0])+(Vpk[3][26][1]*Vpk[3][26][1]))))+((IkWpk[3][26][2]*
          Wpk[3][26][2])+((IkWpk[3][26][0]*Wpk[3][26][0])+(IkWpk[3][26][1]*
          Wpk[3][26][1]))))+temp[9]);
        temp[0] = (((mk[0]*((Vpk[3][5][2]*Vpk[4][5][2])+((Vpk[3][5][0]*
          Vpk[4][5][0])+(Vpk[3][5][1]*Vpk[4][5][1]))))+((IkWpk[4][5][2]*
          Wpk[3][5][2])+((IkWpk[4][5][0]*Wpk[3][5][0])+(IkWpk[4][5][1]*
          Wpk[3][5][1]))))+((mk[1]*((Vpk[3][8][2]*Vpk[4][8][2])+((Vpk[3][8][0]*
          Vpk[4][8][0])+(Vpk[3][8][1]*Vpk[4][8][1]))))+((IkWpk[4][8][2]*
          Wpk[3][8][2])+((IkWpk[4][8][0]*Wpk[3][8][0])+(IkWpk[4][8][1]*
          Wpk[3][8][1])))));
        temp[1] = (((mk[2]*((Vpk[3][11][2]*Vpk[4][11][2])+((Vpk[3][11][0]*
          Vpk[4][11][0])+(Vpk[3][11][1]*Vpk[4][11][1]))))+((IkWpk[4][11][2]*
          Wpk[3][11][2])+((IkWpk[4][11][0]*Wpk[3][11][0])+(IkWpk[4][11][1]*
          Wpk[3][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][12][2]*Vpk[4][12][2])+((Vpk[3][12][0]*
          Vpk[4][12][0])+(Vpk[3][12][1]*Vpk[4][12][1]))))+((IkWpk[4][12][2]*
          Wpk[3][12][2])+((IkWpk[4][12][0]*Wpk[3][12][0])+(IkWpk[4][12][1]*
          Wpk[3][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][13][2]*Vpk[4][13][2])+((Vpk[3][13][0]*
          Vpk[4][13][0])+(Vpk[3][13][1]*Vpk[4][13][1]))))+((IkWpk[4][13][2]*
          Wpk[3][13][2])+((IkWpk[4][13][0]*Wpk[3][13][0])+(IkWpk[4][13][1]*
          Wpk[3][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][14][2]*Vpk[4][14][2])+((Vpk[3][14][0]*
          Vpk[4][14][0])+(Vpk[3][14][1]*Vpk[4][14][1]))))+((IkWpk[4][14][2]*
          Wpk[3][14][2])+((IkWpk[4][14][0]*Wpk[3][14][0])+(IkWpk[4][14][1]*
          Wpk[3][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][17][2]*Vpk[4][17][2])+((Vpk[3][17][0]*
          Vpk[4][17][0])+(Vpk[3][17][1]*Vpk[4][17][1]))))+((IkWpk[4][17][2]*
          Wpk[3][17][2])+((IkWpk[4][17][0]*Wpk[3][17][0])+(IkWpk[4][17][1]*
          Wpk[3][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][20][2]*Vpk[4][20][2])+((Vpk[3][20][0]*
          Vpk[4][20][0])+(Vpk[3][20][1]*Vpk[4][20][1]))))+((IkWpk[4][20][2]*
          Wpk[3][20][2])+((IkWpk[4][20][0]*Wpk[3][20][0])+(IkWpk[4][20][1]*
          Wpk[3][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][21][2]*Vpk[4][21][2])+((Vpk[3][21][0]*
          Vpk[4][21][0])+(Vpk[3][21][1]*Vpk[4][21][1]))))+((IkWpk[4][21][2]*
          Wpk[3][21][2])+((IkWpk[4][21][0]*Wpk[3][21][0])+(IkWpk[4][21][1]*
          Wpk[3][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[3][22][2]*Vpk[4][22][2])+((Vpk[3][22][0]*
          Vpk[4][22][0])+(Vpk[3][22][1]*Vpk[4][22][1]))))+((IkWpk[4][22][2]*
          Wpk[3][22][2])+((IkWpk[4][22][0]*Wpk[3][22][0])+(IkWpk[4][22][1]*
          Wpk[3][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[3][23][2]*Vpk[4][23][2])+((Vpk[3][23][0]*
          Vpk[4][23][0])+(Vpk[3][23][1]*Vpk[4][23][1]))))+((IkWpk[4][23][2]*
          Wpk[3][23][2])+((IkWpk[4][23][0]*Wpk[3][23][0])+(IkWpk[4][23][1]*
          Wpk[3][23][1]))))+temp[8]);
        mm[3][4] = (((mk[11]*((Vpk[3][26][2]*Vpk[4][26][2])+((Vpk[3][26][0]*
          Vpk[4][26][0])+(Vpk[3][26][1]*Vpk[4][26][1]))))+((IkWpk[4][26][2]*
          Wpk[3][26][2])+((IkWpk[4][26][0]*Wpk[3][26][0])+(IkWpk[4][26][1]*
          Wpk[3][26][1]))))+temp[9]);
        temp[0] = (((mk[0]*((Vpk[3][5][2]*Vpk[5][5][2])+((Vpk[3][5][0]*
          Vpk[5][5][0])+(Vpk[3][5][1]*Vpk[5][5][1]))))+((IkWpk[5][5][2]*
          Wpk[3][5][2])+((IkWpk[5][5][0]*Wpk[3][5][0])+(IkWpk[5][5][1]*
          Wpk[3][5][1]))))+((mk[1]*((Vpk[3][8][2]*Vpk[5][8][2])+((Vpk[3][8][0]*
          Vpk[5][8][0])+(Vpk[3][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*
          Wpk[3][8][2])+((IkWpk[5][8][0]*Wpk[3][8][0])+(IkWpk[5][8][1]*
          Wpk[3][8][1])))));
        temp[1] = (((mk[2]*((Vpk[3][11][2]*Vpk[5][11][2])+((Vpk[3][11][0]*
          Vpk[5][11][0])+(Vpk[3][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[3][11][2])+((IkWpk[5][11][0]*Wpk[3][11][0])+(IkWpk[5][11][1]*
          Wpk[3][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][12][2]*Vpk[5][12][2])+((Vpk[3][12][0]*
          Vpk[5][12][0])+(Vpk[3][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[3][12][2])+((IkWpk[5][12][0]*Wpk[3][12][0])+(IkWpk[5][12][1]*
          Wpk[3][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][13][2]*Vpk[5][13][2])+((Vpk[3][13][0]*
          Vpk[5][13][0])+(Vpk[3][13][1]*Vpk[5][13][1]))))+((IkWpk[5][13][2]*
          Wpk[3][13][2])+((IkWpk[5][13][0]*Wpk[3][13][0])+(IkWpk[5][13][1]*
          Wpk[3][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][14][2]*Vpk[5][14][2])+((Vpk[3][14][0]*
          Vpk[5][14][0])+(Vpk[3][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[3][14][2])+((IkWpk[5][14][0]*Wpk[3][14][0])+(IkWpk[5][14][1]*
          Wpk[3][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][17][2]*Vpk[5][17][2])+((Vpk[3][17][0]*
          Vpk[5][17][0])+(Vpk[3][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[3][17][2])+((IkWpk[5][17][0]*Wpk[3][17][0])+(IkWpk[5][17][1]*
          Wpk[3][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][20][2]*Vpk[5][20][2])+((Vpk[3][20][0]*
          Vpk[5][20][0])+(Vpk[3][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[3][20][2])+((IkWpk[5][20][0]*Wpk[3][20][0])+(IkWpk[5][20][1]*
          Wpk[3][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][21][2]*Vpk[5][21][2])+((Vpk[3][21][0]*
          Vpk[5][21][0])+(Vpk[3][21][1]*Vpk[5][21][1]))))+((IkWpk[5][21][2]*
          Wpk[3][21][2])+((IkWpk[5][21][0]*Wpk[3][21][0])+(IkWpk[5][21][1]*
          Wpk[3][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[3][22][2]*Vpk[5][22][2])+((Vpk[3][22][0]*
          Vpk[5][22][0])+(Vpk[3][22][1]*Vpk[5][22][1]))))+((IkWpk[5][22][2]*
          Wpk[3][22][2])+((IkWpk[5][22][0]*Wpk[3][22][0])+(IkWpk[5][22][1]*
          Wpk[3][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[3][23][2]*Vpk[5][23][2])+((Vpk[3][23][0]*
          Vpk[5][23][0])+(Vpk[3][23][1]*Vpk[5][23][1]))))+((IkWpk[5][23][2]*
          Wpk[3][23][2])+((IkWpk[5][23][0]*Wpk[3][23][0])+(IkWpk[5][23][1]*
          Wpk[3][23][1]))))+temp[8]);
        mm[3][5] = (((mk[11]*((Vpk[3][26][2]*Vpk[5][26][2])+((Vpk[3][26][0]*
          Vpk[5][26][0])+(Vpk[3][26][1]*Vpk[5][26][1]))))+((IkWpk[5][26][2]*
          Wpk[3][26][2])+((IkWpk[5][26][0]*Wpk[3][26][0])+(IkWpk[5][26][1]*
          Wpk[3][26][1]))))+temp[9]);
        temp[0] = (((mk[1]*((Vpk[3][8][2]*Vpk[6][8][2])+((Vpk[3][8][0]*
          Vpk[6][8][0])+(Vpk[3][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][2]*
          Wpk[3][8][2])+((IkWpk[6][8][0]*Wpk[3][8][0])+(IkWpk[6][8][1]*
          Wpk[3][8][1]))))+((mk[2]*((Vpk[3][11][2]*Vpk[6][11][2])+((
          Vpk[3][11][0]*Vpk[6][11][0])+(Vpk[3][11][1]*Vpk[6][11][1]))))+((
          IkWpk[6][11][2]*Wpk[3][11][2])+((IkWpk[6][11][0]*Wpk[3][11][0])+(
          IkWpk[6][11][1]*Wpk[3][11][1])))));
        temp[1] = (((mk[3]*((Vpk[3][12][2]*Vpk[6][12][2])+((Vpk[3][12][0]*
          Vpk[6][12][0])+(Vpk[3][12][1]*Vpk[6][12][1]))))+((IkWpk[6][12][2]*
          Wpk[3][12][2])+((IkWpk[6][12][0]*Wpk[3][12][0])+(IkWpk[6][12][1]*
          Wpk[3][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[3][13][2]*Vpk[6][13][2])+((Vpk[3][13][0]*
          Vpk[6][13][0])+(Vpk[3][13][1]*Vpk[6][13][1]))))+((IkWpk[6][13][2]*
          Wpk[3][13][2])+((IkWpk[6][13][0]*Wpk[3][13][0])+(IkWpk[6][13][1]*
          Wpk[3][13][1]))))+temp[1]);
        mm[3][6] = (((mk[5]*((Vpk[3][14][2]*Vpk[6][14][2])+((Vpk[3][14][0]*
          Vpk[6][14][0])+(Vpk[3][14][1]*Vpk[6][14][1]))))+((IkWpk[6][14][2]*
          Wpk[3][14][2])+((IkWpk[6][14][0]*Wpk[3][14][0])+(IkWpk[6][14][1]*
          Wpk[3][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[3][8][2]*Vpk[7][8][2])+((Vpk[3][8][0]*
          Vpk[7][8][0])+(Vpk[3][8][1]*Vpk[7][8][1]))))+((IkWpk[7][8][2]*
          Wpk[3][8][2])+((IkWpk[7][8][0]*Wpk[3][8][0])+(IkWpk[7][8][1]*
          Wpk[3][8][1]))))+((mk[2]*((Vpk[3][11][2]*Vpk[7][11][2])+((
          Vpk[3][11][0]*Vpk[7][11][0])+(Vpk[3][11][1]*Vpk[7][11][1]))))+((
          IkWpk[7][11][2]*Wpk[3][11][2])+((IkWpk[7][11][0]*Wpk[3][11][0])+(
          IkWpk[7][11][1]*Wpk[3][11][1])))));
        temp[1] = (((mk[3]*((Vpk[3][12][2]*Vpk[7][12][2])+((Vpk[3][12][0]*
          Vpk[7][12][0])+(Vpk[3][12][1]*Vpk[7][12][1]))))+((IkWpk[7][12][2]*
          Wpk[3][12][2])+((IkWpk[7][12][0]*Wpk[3][12][0])+(IkWpk[7][12][1]*
          Wpk[3][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[3][13][2]*Vpk[7][13][2])+((Vpk[3][13][0]*
          Vpk[7][13][0])+(Vpk[3][13][1]*Vpk[7][13][1]))))+((IkWpk[7][13][2]*
          Wpk[3][13][2])+((IkWpk[7][13][0]*Wpk[3][13][0])+(IkWpk[7][13][1]*
          Wpk[3][13][1]))))+temp[1]);
        mm[3][7] = (((mk[5]*((Vpk[3][14][2]*Vpk[7][14][2])+((Vpk[3][14][0]*
          Vpk[7][14][0])+(Vpk[3][14][1]*Vpk[7][14][1]))))+((IkWpk[7][14][2]*
          Wpk[3][14][2])+((IkWpk[7][14][0]*Wpk[3][14][0])+(IkWpk[7][14][1]*
          Wpk[3][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[3][8][2]*Vpk[8][8][2])+((Vpk[3][8][0]*
          Vpk[8][8][0])+(Vpk[3][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          Wpk[3][8][2])+((IkWpk[8][8][0]*Wpk[3][8][0])+(IkWpk[8][8][1]*
          Wpk[3][8][1]))))+((mk[2]*((Vpk[3][11][2]*Vpk[8][11][2])+((
          Vpk[3][11][0]*Vpk[8][11][0])+(Vpk[3][11][1]*Vpk[8][11][1]))))+((
          IkWpk[8][11][2]*Wpk[3][11][2])+((IkWpk[8][11][0]*Wpk[3][11][0])+(
          IkWpk[8][11][1]*Wpk[3][11][1])))));
        temp[1] = (((mk[3]*((Vpk[3][12][2]*Vpk[8][12][2])+((Vpk[3][12][0]*
          Vpk[8][12][0])+(Vpk[3][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[3][12][2])+((IkWpk[8][12][0]*Wpk[3][12][0])+(IkWpk[8][12][1]*
          Wpk[3][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[3][13][2]*Vpk[8][13][2])+((Vpk[3][13][0]*
          Vpk[8][13][0])+(Vpk[3][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[3][13][2])+((IkWpk[8][13][0]*Wpk[3][13][0])+(IkWpk[8][13][1]*
          Wpk[3][13][1]))))+temp[1]);
        mm[3][8] = (((mk[5]*((Vpk[3][14][2]*Vpk[8][14][2])+((Vpk[3][14][0]*
          Vpk[8][14][0])+(Vpk[3][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[3][14][2])+((IkWpk[8][14][0]*Wpk[3][14][0])+(IkWpk[8][14][1]*
          Wpk[3][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[3][13][2]*Vpk[9][13][2])+((Vpk[3][13][0]*
          Vpk[9][13][0])+(Vpk[3][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[3][11][2]*Vpk[9][11][2])+((Vpk[3][11][0]*Vpk[9][11][0])+(
          Vpk[3][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[3][12][2]*Vpk[9][12][2])+
          ((Vpk[3][12][0]*Vpk[9][12][0])+(Vpk[3][12][1]*Vpk[9][12][1]))))));
        mm[3][9] = ((mk[5]*((Vpk[3][14][2]*Vpk[9][14][2])+((Vpk[3][14][0]*
          Vpk[9][14][0])+(Vpk[3][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[3][13][2]*Vpk[10][13][2])+((Vpk[3][13][0]*
          Vpk[10][13][0])+(Vpk[3][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[3][11][2]*Vpk[10][11][2])+((Vpk[3][11][0]*Vpk[10][11][0])+(
          Vpk[3][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[3][12][2]*Vpk[10][12][2]
          )+((Vpk[3][12][0]*Vpk[10][12][0])+(Vpk[3][12][1]*Vpk[10][12][1]))))));
        mm[3][10] = ((mk[5]*((Vpk[3][14][2]*Vpk[10][14][2])+((Vpk[3][14][0]*
          Vpk[10][14][0])+(Vpk[3][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[3][11][2]*Vpk[11][11][2])+((Vpk[3][11][0]*
          Vpk[11][11][0])+(Vpk[3][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[3][11][2])+((IkWpk[11][11][0]*Wpk[3][11][0])+(IkWpk[11][11][1]*
          Wpk[3][11][1]))))+((mk[3]*((Vpk[3][12][2]*Vpk[11][12][2])+((
          Vpk[3][12][0]*Vpk[11][12][0])+(Vpk[3][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[3][12][2])+((IkWpk[11][12][0]*Wpk[3][12][0])+(
          IkWpk[11][12][1]*Wpk[3][12][1])))));
        temp[1] = (((mk[4]*((Vpk[3][13][2]*Vpk[11][13][2])+((Vpk[3][13][0]*
          Vpk[11][13][0])+(Vpk[3][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[3][13][2])+((IkWpk[11][13][0]*Wpk[3][13][0])+(IkWpk[11][13][1]*
          Wpk[3][13][1]))))+temp[0]);
        mm[3][11] = (((mk[5]*((Vpk[3][14][2]*Vpk[11][14][2])+((Vpk[3][14][0]*
          Vpk[11][14][0])+(Vpk[3][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[3][14][2])+((IkWpk[11][14][0]*Wpk[3][14][0])+(IkWpk[11][14][1]*
          Wpk[3][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[3][12][2]*Vpk[12][12][2])+((Vpk[3][12][0]*
          Vpk[12][12][0])+(Vpk[3][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[3][12][2])+((IkWpk[12][12][0]*Wpk[3][12][0])+(IkWpk[12][12][1]*
          Wpk[3][12][1]))))+((mk[4]*((Vpk[3][13][2]*Vpk[12][13][2])+((
          Vpk[3][13][0]*Vpk[12][13][0])+(Vpk[3][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[3][13][2])+((IkWpk[12][13][0]*Wpk[3][13][0])+(
          IkWpk[12][13][1]*Wpk[3][13][1])))));
        mm[3][12] = (((mk[5]*((Vpk[3][14][2]*Vpk[12][14][2])+((Vpk[3][14][0]*
          Vpk[12][14][0])+(Vpk[3][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[3][14][2])+((IkWpk[12][14][0]*Wpk[3][14][0])+(IkWpk[12][14][1]*
          Wpk[3][14][1]))))+temp[0]);
        mm[3][13] = (((mk[4]*((Vpk[3][13][2]*Vpk[13][13][2])+((Vpk[3][13][0]*
          Vpk[13][13][0])+(Vpk[3][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[3][13][2])+((IkWpk[13][13][0]*Wpk[3][13][0])+(IkWpk[13][13][1]*
          Wpk[3][13][1]))))+((mk[5]*((Vpk[3][14][2]*Vpk[13][14][2])+((
          Vpk[3][14][0]*Vpk[13][14][0])+(Vpk[3][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[3][14][2])+((IkWpk[13][14][0]*Wpk[3][14][0])+(
          IkWpk[13][14][1]*Wpk[3][14][1])))));
        mm[3][14] = ((mk[5]*((Vpk[3][14][2]*Vpk[14][14][2])+((Vpk[3][14][0]*
          Vpk[14][14][0])+(Vpk[3][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[3][14][2])+((IkWpk[14][14][0]*Wpk[3][14][0])+(IkWpk[14][14][1]*
          Wpk[3][14][1]))));
        temp[0] = (((mk[6]*((Vpk[3][17][2]*Vpk[15][17][2])+((Vpk[3][17][0]*
          Vpk[15][17][0])+(Vpk[3][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[3][17][2])+((IkWpk[15][17][0]*Wpk[3][17][0])+(IkWpk[15][17][1]*
          Wpk[3][17][1]))))+((mk[7]*((Vpk[3][20][2]*Vpk[15][20][2])+((
          Vpk[3][20][0]*Vpk[15][20][0])+(Vpk[3][20][1]*Vpk[15][20][1]))))+((
          IkWpk[15][20][2]*Wpk[3][20][2])+((IkWpk[15][20][0]*Wpk[3][20][0])+(
          IkWpk[15][20][1]*Wpk[3][20][1])))));
        temp[1] = (((mk[8]*((Vpk[3][21][2]*Vpk[15][21][2])+((Vpk[3][21][0]*
          Vpk[15][21][0])+(Vpk[3][21][1]*Vpk[15][21][1]))))+((IkWpk[15][21][2]*
          Wpk[3][21][2])+((IkWpk[15][21][0]*Wpk[3][21][0])+(IkWpk[15][21][1]*
          Wpk[3][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[3][22][2]*Vpk[15][22][2])+((Vpk[3][22][0]*
          Vpk[15][22][0])+(Vpk[3][22][1]*Vpk[15][22][1]))))+((IkWpk[15][22][2]*
          Wpk[3][22][2])+((IkWpk[15][22][0]*Wpk[3][22][0])+(IkWpk[15][22][1]*
          Wpk[3][22][1]))))+temp[1]);
        mm[3][15] = (((mk[10]*((Vpk[3][23][2]*Vpk[15][23][2])+((Vpk[3][23][0]*
          Vpk[15][23][0])+(Vpk[3][23][1]*Vpk[15][23][1]))))+((IkWpk[15][23][2]*
          Wpk[3][23][2])+((IkWpk[15][23][0]*Wpk[3][23][0])+(IkWpk[15][23][1]*
          Wpk[3][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[3][17][2]*Vpk[16][17][2])+((Vpk[3][17][0]*
          Vpk[16][17][0])+(Vpk[3][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][2]*
          Wpk[3][17][2])+((IkWpk[16][17][0]*Wpk[3][17][0])+(IkWpk[16][17][1]*
          Wpk[3][17][1]))))+((mk[7]*((Vpk[3][20][2]*Vpk[16][20][2])+((
          Vpk[3][20][0]*Vpk[16][20][0])+(Vpk[3][20][1]*Vpk[16][20][1]))))+((
          IkWpk[16][20][2]*Wpk[3][20][2])+((IkWpk[16][20][0]*Wpk[3][20][0])+(
          IkWpk[16][20][1]*Wpk[3][20][1])))));
        temp[1] = (((mk[8]*((Vpk[3][21][2]*Vpk[16][21][2])+((Vpk[3][21][0]*
          Vpk[16][21][0])+(Vpk[3][21][1]*Vpk[16][21][1]))))+((IkWpk[16][21][2]*
          Wpk[3][21][2])+((IkWpk[16][21][0]*Wpk[3][21][0])+(IkWpk[16][21][1]*
          Wpk[3][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[3][22][2]*Vpk[16][22][2])+((Vpk[3][22][0]*
          Vpk[16][22][0])+(Vpk[3][22][1]*Vpk[16][22][1]))))+((IkWpk[16][22][2]*
          Wpk[3][22][2])+((IkWpk[16][22][0]*Wpk[3][22][0])+(IkWpk[16][22][1]*
          Wpk[3][22][1]))))+temp[1]);
        mm[3][16] = (((mk[10]*((Vpk[3][23][2]*Vpk[16][23][2])+((Vpk[3][23][0]*
          Vpk[16][23][0])+(Vpk[3][23][1]*Vpk[16][23][1]))))+((IkWpk[16][23][2]*
          Wpk[3][23][2])+((IkWpk[16][23][0]*Wpk[3][23][0])+(IkWpk[16][23][1]*
          Wpk[3][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[3][17][2]*Vpk[17][17][2])+((Vpk[3][17][0]*
          Vpk[17][17][0])+(Vpk[3][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          Wpk[3][17][2])+((IkWpk[17][17][0]*Wpk[3][17][0])+(IkWpk[17][17][1]*
          Wpk[3][17][1]))))+((mk[7]*((Vpk[3][20][2]*Vpk[17][20][2])+((
          Vpk[3][20][0]*Vpk[17][20][0])+(Vpk[3][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[3][20][2])+((IkWpk[17][20][0]*Wpk[3][20][0])+(
          IkWpk[17][20][1]*Wpk[3][20][1])))));
        temp[1] = (((mk[8]*((Vpk[3][21][2]*Vpk[17][21][2])+((Vpk[3][21][0]*
          Vpk[17][21][0])+(Vpk[3][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[3][21][2])+((IkWpk[17][21][0]*Wpk[3][21][0])+(IkWpk[17][21][1]*
          Wpk[3][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[3][22][2]*Vpk[17][22][2])+((Vpk[3][22][0]*
          Vpk[17][22][0])+(Vpk[3][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[3][22][2])+((IkWpk[17][22][0]*Wpk[3][22][0])+(IkWpk[17][22][1]*
          Wpk[3][22][1]))))+temp[1]);
        mm[3][17] = (((mk[10]*((Vpk[3][23][2]*Vpk[17][23][2])+((Vpk[3][23][0]*
          Vpk[17][23][0])+(Vpk[3][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]*
          Wpk[3][23][2])+((IkWpk[17][23][0]*Wpk[3][23][0])+(IkWpk[17][23][1]*
          Wpk[3][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[3][22][2]*Vpk[18][22][2])+((Vpk[3][22][0]*
          Vpk[18][22][0])+(Vpk[3][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[3][20][2]*Vpk[18][20][2])+((Vpk[3][20][0]*Vpk[18][20][0])+(
          Vpk[3][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[3][21][2]*Vpk[18][21][2]
          )+((Vpk[3][21][0]*Vpk[18][21][0])+(Vpk[3][21][1]*Vpk[18][21][1]))))));
        mm[3][18] = ((mk[10]*((Vpk[3][23][2]*Vpk[18][23][2])+((Vpk[3][23][0]*
          Vpk[18][23][0])+(Vpk[3][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[3][22][2]*Vpk[19][22][2])+((Vpk[3][22][0]*
          Vpk[19][22][0])+(Vpk[3][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[3][20][2]*Vpk[19][20][2])+((Vpk[3][20][0]*Vpk[19][20][0])+(
          Vpk[3][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[3][21][2]*Vpk[19][21][2]
          )+((Vpk[3][21][0]*Vpk[19][21][0])+(Vpk[3][21][1]*Vpk[19][21][1]))))));
        mm[3][19] = ((mk[10]*((Vpk[3][23][2]*Vpk[19][23][2])+((Vpk[3][23][0]*
          Vpk[19][23][0])+(Vpk[3][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[3][20][2]*Vpk[20][20][2])+((Vpk[3][20][0]*
          Vpk[20][20][0])+(Vpk[3][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[3][20][2])+((IkWpk[20][20][0]*Wpk[3][20][0])+(IkWpk[20][20][1]*
          Wpk[3][20][1]))))+((mk[8]*((Vpk[3][21][2]*Vpk[20][21][2])+((
          Vpk[3][21][0]*Vpk[20][21][0])+(Vpk[3][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[3][21][2])+((IkWpk[20][21][0]*Wpk[3][21][0])+(
          IkWpk[20][21][1]*Wpk[3][21][1])))));
        temp[1] = (((mk[9]*((Vpk[3][22][2]*Vpk[20][22][2])+((Vpk[3][22][0]*
          Vpk[20][22][0])+(Vpk[3][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[3][22][2])+((IkWpk[20][22][0]*Wpk[3][22][0])+(IkWpk[20][22][1]*
          Wpk[3][22][1]))))+temp[0]);
        mm[3][20] = (((mk[10]*((Vpk[3][23][2]*Vpk[20][23][2])+((Vpk[3][23][0]*
          Vpk[20][23][0])+(Vpk[3][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]*
          Wpk[3][23][2])+((IkWpk[20][23][0]*Wpk[3][23][0])+(IkWpk[20][23][1]*
          Wpk[3][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[3][21][2]*Vpk[21][21][2])+((Vpk[3][21][0]*
          Vpk[21][21][0])+(Vpk[3][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[3][21][2])+((IkWpk[21][21][0]*Wpk[3][21][0])+(IkWpk[21][21][1]*
          Wpk[3][21][1]))))+((mk[9]*((Vpk[3][22][2]*Vpk[21][22][2])+((
          Vpk[3][22][0]*Vpk[21][22][0])+(Vpk[3][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[3][22][2])+((IkWpk[21][22][0]*Wpk[3][22][0])+(
          IkWpk[21][22][1]*Wpk[3][22][1])))));
        mm[3][21] = (((mk[10]*((Vpk[3][23][2]*Vpk[21][23][2])+((Vpk[3][23][0]*
          Vpk[21][23][0])+(Vpk[3][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]*
          Wpk[3][23][2])+((IkWpk[21][23][0]*Wpk[3][23][0])+(IkWpk[21][23][1]*
          Wpk[3][23][1]))))+temp[0]);
        mm[3][22] = (((mk[9]*((Vpk[3][22][2]*Vpk[22][22][2])+((Vpk[3][22][0]*
          Vpk[22][22][0])+(Vpk[3][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[3][22][2])+((IkWpk[22][22][0]*Wpk[3][22][0])+(IkWpk[22][22][1]*
          Wpk[3][22][1]))))+((mk[10]*((Vpk[3][23][2]*Vpk[22][23][2])+((
          Vpk[3][23][0]*Vpk[22][23][0])+(Vpk[3][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[3][23][2])+((IkWpk[22][23][0]*Wpk[3][23][0])+(
          IkWpk[22][23][1]*Wpk[3][23][1])))));
        mm[3][23] = ((mk[10]*((Vpk[3][23][2]*Vpk[23][23][2])+((Vpk[3][23][0]*
          Vpk[23][23][0])+(Vpk[3][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[3][23][2])+((IkWpk[23][23][0]*Wpk[3][23][0])+(IkWpk[23][23][1]*
          Wpk[3][23][1]))));
        mm[3][24] = ((mk[11]*((Vpk[3][26][2]*Vpk[24][26][2])+((Vpk[3][26][0]*
          Vpk[24][26][0])+(Vpk[3][26][1]*Vpk[24][26][1]))))+((IkWpk[24][26][2]*
          Wpk[3][26][2])+((IkWpk[24][26][0]*Wpk[3][26][0])+(IkWpk[24][26][1]*
          Wpk[3][26][1]))));
        mm[3][25] = ((mk[11]*((Vpk[3][26][2]*Vpk[25][26][2])+((Vpk[3][26][0]*
          Vpk[25][26][0])+(Vpk[3][26][1]*Vpk[25][26][1]))))+((IkWpk[25][26][2]*
          Wpk[3][26][2])+((IkWpk[25][26][0]*Wpk[3][26][0])+(IkWpk[25][26][1]*
          Wpk[3][26][1]))));
        mm[3][26] = ((mk[11]*((Vpk[3][26][2]*Vpk[26][26][2])+((Vpk[3][26][0]*
          Vpk[26][26][0])+(Vpk[3][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          Wpk[3][26][2])+((IkWpk[26][26][0]*Wpk[3][26][0])+(IkWpk[26][26][1]*
          Wpk[3][26][1]))));
        temp[0] = (((mk[0]*((Vpk[4][5][2]*Vpk[4][5][2])+((Vpk[4][5][0]*
          Vpk[4][5][0])+(Vpk[4][5][1]*Vpk[4][5][1]))))+((IkWpk[4][5][2]*
          Wpk[4][5][2])+((IkWpk[4][5][0]*Wpk[4][5][0])+(IkWpk[4][5][1]*
          Wpk[4][5][1]))))+((mk[1]*((Vpk[4][8][2]*Vpk[4][8][2])+((Vpk[4][8][0]*
          Vpk[4][8][0])+(Vpk[4][8][1]*Vpk[4][8][1]))))+((IkWpk[4][8][2]*
          Wpk[4][8][2])+((IkWpk[4][8][0]*Wpk[4][8][0])+(IkWpk[4][8][1]*
          Wpk[4][8][1])))));
        temp[1] = (((mk[2]*((Vpk[4][11][2]*Vpk[4][11][2])+((Vpk[4][11][0]*
          Vpk[4][11][0])+(Vpk[4][11][1]*Vpk[4][11][1]))))+((IkWpk[4][11][2]*
          Wpk[4][11][2])+((IkWpk[4][11][0]*Wpk[4][11][0])+(IkWpk[4][11][1]*
          Wpk[4][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[4][12][2]*Vpk[4][12][2])+((Vpk[4][12][0]*
          Vpk[4][12][0])+(Vpk[4][12][1]*Vpk[4][12][1]))))+((IkWpk[4][12][2]*
          Wpk[4][12][2])+((IkWpk[4][12][0]*Wpk[4][12][0])+(IkWpk[4][12][1]*
          Wpk[4][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[4][13][2]*Vpk[4][13][2])+((Vpk[4][13][0]*
          Vpk[4][13][0])+(Vpk[4][13][1]*Vpk[4][13][1]))))+((IkWpk[4][13][2]*
          Wpk[4][13][2])+((IkWpk[4][13][0]*Wpk[4][13][0])+(IkWpk[4][13][1]*
          Wpk[4][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[4][14][2]*Vpk[4][14][2])+((Vpk[4][14][0]*
          Vpk[4][14][0])+(Vpk[4][14][1]*Vpk[4][14][1]))))+((IkWpk[4][14][2]*
          Wpk[4][14][2])+((IkWpk[4][14][0]*Wpk[4][14][0])+(IkWpk[4][14][1]*
          Wpk[4][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[4][17][2]*Vpk[4][17][2])+((Vpk[4][17][0]*
          Vpk[4][17][0])+(Vpk[4][17][1]*Vpk[4][17][1]))))+((IkWpk[4][17][2]*
          Wpk[4][17][2])+((IkWpk[4][17][0]*Wpk[4][17][0])+(IkWpk[4][17][1]*
          Wpk[4][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[4][20][2]*Vpk[4][20][2])+((Vpk[4][20][0]*
          Vpk[4][20][0])+(Vpk[4][20][1]*Vpk[4][20][1]))))+((IkWpk[4][20][2]*
          Wpk[4][20][2])+((IkWpk[4][20][0]*Wpk[4][20][0])+(IkWpk[4][20][1]*
          Wpk[4][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[4][21][2]*Vpk[4][21][2])+((Vpk[4][21][0]*
          Vpk[4][21][0])+(Vpk[4][21][1]*Vpk[4][21][1]))))+((IkWpk[4][21][2]*
          Wpk[4][21][2])+((IkWpk[4][21][0]*Wpk[4][21][0])+(IkWpk[4][21][1]*
          Wpk[4][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[4][22][2]*Vpk[4][22][2])+((Vpk[4][22][0]*
          Vpk[4][22][0])+(Vpk[4][22][1]*Vpk[4][22][1]))))+((IkWpk[4][22][2]*
          Wpk[4][22][2])+((IkWpk[4][22][0]*Wpk[4][22][0])+(IkWpk[4][22][1]*
          Wpk[4][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[4][23][2]*Vpk[4][23][2])+((Vpk[4][23][0]*
          Vpk[4][23][0])+(Vpk[4][23][1]*Vpk[4][23][1]))))+((IkWpk[4][23][2]*
          Wpk[4][23][2])+((IkWpk[4][23][0]*Wpk[4][23][0])+(IkWpk[4][23][1]*
          Wpk[4][23][1]))))+temp[8]);
        mm[4][4] = (((mk[11]*((Vpk[4][26][2]*Vpk[4][26][2])+((Vpk[4][26][0]*
          Vpk[4][26][0])+(Vpk[4][26][1]*Vpk[4][26][1]))))+((IkWpk[4][26][2]*
          Wpk[4][26][2])+((IkWpk[4][26][0]*Wpk[4][26][0])+(IkWpk[4][26][1]*
          Wpk[4][26][1]))))+temp[9]);
        temp[0] = (((mk[0]*((Vpk[4][5][2]*Vpk[5][5][2])+((Vpk[4][5][0]*
          Vpk[5][5][0])+(Vpk[4][5][1]*Vpk[5][5][1]))))+((IkWpk[5][5][2]*
          Wpk[4][5][2])+((IkWpk[5][5][0]*Wpk[4][5][0])+(IkWpk[5][5][1]*
          Wpk[4][5][1]))))+((mk[1]*((Vpk[4][8][2]*Vpk[5][8][2])+((Vpk[4][8][0]*
          Vpk[5][8][0])+(Vpk[4][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*
          Wpk[4][8][2])+((IkWpk[5][8][0]*Wpk[4][8][0])+(IkWpk[5][8][1]*
          Wpk[4][8][1])))));
        temp[1] = (((mk[2]*((Vpk[4][11][2]*Vpk[5][11][2])+((Vpk[4][11][0]*
          Vpk[5][11][0])+(Vpk[4][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[4][11][2])+((IkWpk[5][11][0]*Wpk[4][11][0])+(IkWpk[5][11][1]*
          Wpk[4][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[4][12][2]*Vpk[5][12][2])+((Vpk[4][12][0]*
          Vpk[5][12][0])+(Vpk[4][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[4][12][2])+((IkWpk[5][12][0]*Wpk[4][12][0])+(IkWpk[5][12][1]*
          Wpk[4][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[4][13][2]*Vpk[5][13][2])+((Vpk[4][13][0]*
          Vpk[5][13][0])+(Vpk[4][13][1]*Vpk[5][13][1]))))+((IkWpk[5][13][2]*
          Wpk[4][13][2])+((IkWpk[5][13][0]*Wpk[4][13][0])+(IkWpk[5][13][1]*
          Wpk[4][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[4][14][2]*Vpk[5][14][2])+((Vpk[4][14][0]*
          Vpk[5][14][0])+(Vpk[4][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[4][14][2])+((IkWpk[5][14][0]*Wpk[4][14][0])+(IkWpk[5][14][1]*
          Wpk[4][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[4][17][2]*Vpk[5][17][2])+((Vpk[4][17][0]*
          Vpk[5][17][0])+(Vpk[4][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[4][17][2])+((IkWpk[5][17][0]*Wpk[4][17][0])+(IkWpk[5][17][1]*
          Wpk[4][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[4][20][2]*Vpk[5][20][2])+((Vpk[4][20][0]*
          Vpk[5][20][0])+(Vpk[4][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[4][20][2])+((IkWpk[5][20][0]*Wpk[4][20][0])+(IkWpk[5][20][1]*
          Wpk[4][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[4][21][2]*Vpk[5][21][2])+((Vpk[4][21][0]*
          Vpk[5][21][0])+(Vpk[4][21][1]*Vpk[5][21][1]))))+((IkWpk[5][21][2]*
          Wpk[4][21][2])+((IkWpk[5][21][0]*Wpk[4][21][0])+(IkWpk[5][21][1]*
          Wpk[4][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[4][22][2]*Vpk[5][22][2])+((Vpk[4][22][0]*
          Vpk[5][22][0])+(Vpk[4][22][1]*Vpk[5][22][1]))))+((IkWpk[5][22][2]*
          Wpk[4][22][2])+((IkWpk[5][22][0]*Wpk[4][22][0])+(IkWpk[5][22][1]*
          Wpk[4][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[4][23][2]*Vpk[5][23][2])+((Vpk[4][23][0]*
          Vpk[5][23][0])+(Vpk[4][23][1]*Vpk[5][23][1]))))+((IkWpk[5][23][2]*
          Wpk[4][23][2])+((IkWpk[5][23][0]*Wpk[4][23][0])+(IkWpk[5][23][1]*
          Wpk[4][23][1]))))+temp[8]);
        mm[4][5] = (((mk[11]*((Vpk[4][26][2]*Vpk[5][26][2])+((Vpk[4][26][0]*
          Vpk[5][26][0])+(Vpk[4][26][1]*Vpk[5][26][1]))))+((IkWpk[5][26][2]*
          Wpk[4][26][2])+((IkWpk[5][26][0]*Wpk[4][26][0])+(IkWpk[5][26][1]*
          Wpk[4][26][1]))))+temp[9]);
        temp[0] = (((mk[1]*((Vpk[4][8][2]*Vpk[6][8][2])+((Vpk[4][8][0]*
          Vpk[6][8][0])+(Vpk[4][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][2]*
          Wpk[4][8][2])+((IkWpk[6][8][0]*Wpk[4][8][0])+(IkWpk[6][8][1]*
          Wpk[4][8][1]))))+((mk[2]*((Vpk[4][11][2]*Vpk[6][11][2])+((
          Vpk[4][11][0]*Vpk[6][11][0])+(Vpk[4][11][1]*Vpk[6][11][1]))))+((
          IkWpk[6][11][2]*Wpk[4][11][2])+((IkWpk[6][11][0]*Wpk[4][11][0])+(
          IkWpk[6][11][1]*Wpk[4][11][1])))));
        temp[1] = (((mk[3]*((Vpk[4][12][2]*Vpk[6][12][2])+((Vpk[4][12][0]*
          Vpk[6][12][0])+(Vpk[4][12][1]*Vpk[6][12][1]))))+((IkWpk[6][12][2]*
          Wpk[4][12][2])+((IkWpk[6][12][0]*Wpk[4][12][0])+(IkWpk[6][12][1]*
          Wpk[4][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[4][13][2]*Vpk[6][13][2])+((Vpk[4][13][0]*
          Vpk[6][13][0])+(Vpk[4][13][1]*Vpk[6][13][1]))))+((IkWpk[6][13][2]*
          Wpk[4][13][2])+((IkWpk[6][13][0]*Wpk[4][13][0])+(IkWpk[6][13][1]*
          Wpk[4][13][1]))))+temp[1]);
        mm[4][6] = (((mk[5]*((Vpk[4][14][2]*Vpk[6][14][2])+((Vpk[4][14][0]*
          Vpk[6][14][0])+(Vpk[4][14][1]*Vpk[6][14][1]))))+((IkWpk[6][14][2]*
          Wpk[4][14][2])+((IkWpk[6][14][0]*Wpk[4][14][0])+(IkWpk[6][14][1]*
          Wpk[4][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[4][8][2]*Vpk[7][8][2])+((Vpk[4][8][0]*
          Vpk[7][8][0])+(Vpk[4][8][1]*Vpk[7][8][1]))))+((IkWpk[7][8][2]*
          Wpk[4][8][2])+((IkWpk[7][8][0]*Wpk[4][8][0])+(IkWpk[7][8][1]*
          Wpk[4][8][1]))))+((mk[2]*((Vpk[4][11][2]*Vpk[7][11][2])+((
          Vpk[4][11][0]*Vpk[7][11][0])+(Vpk[4][11][1]*Vpk[7][11][1]))))+((
          IkWpk[7][11][2]*Wpk[4][11][2])+((IkWpk[7][11][0]*Wpk[4][11][0])+(
          IkWpk[7][11][1]*Wpk[4][11][1])))));
        temp[1] = (((mk[3]*((Vpk[4][12][2]*Vpk[7][12][2])+((Vpk[4][12][0]*
          Vpk[7][12][0])+(Vpk[4][12][1]*Vpk[7][12][1]))))+((IkWpk[7][12][2]*
          Wpk[4][12][2])+((IkWpk[7][12][0]*Wpk[4][12][0])+(IkWpk[7][12][1]*
          Wpk[4][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[4][13][2]*Vpk[7][13][2])+((Vpk[4][13][0]*
          Vpk[7][13][0])+(Vpk[4][13][1]*Vpk[7][13][1]))))+((IkWpk[7][13][2]*
          Wpk[4][13][2])+((IkWpk[7][13][0]*Wpk[4][13][0])+(IkWpk[7][13][1]*
          Wpk[4][13][1]))))+temp[1]);
        mm[4][7] = (((mk[5]*((Vpk[4][14][2]*Vpk[7][14][2])+((Vpk[4][14][0]*
          Vpk[7][14][0])+(Vpk[4][14][1]*Vpk[7][14][1]))))+((IkWpk[7][14][2]*
          Wpk[4][14][2])+((IkWpk[7][14][0]*Wpk[4][14][0])+(IkWpk[7][14][1]*
          Wpk[4][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[4][8][2]*Vpk[8][8][2])+((Vpk[4][8][0]*
          Vpk[8][8][0])+(Vpk[4][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          Wpk[4][8][2])+((IkWpk[8][8][0]*Wpk[4][8][0])+(IkWpk[8][8][1]*
          Wpk[4][8][1]))))+((mk[2]*((Vpk[4][11][2]*Vpk[8][11][2])+((
          Vpk[4][11][0]*Vpk[8][11][0])+(Vpk[4][11][1]*Vpk[8][11][1]))))+((
          IkWpk[8][11][2]*Wpk[4][11][2])+((IkWpk[8][11][0]*Wpk[4][11][0])+(
          IkWpk[8][11][1]*Wpk[4][11][1])))));
        temp[1] = (((mk[3]*((Vpk[4][12][2]*Vpk[8][12][2])+((Vpk[4][12][0]*
          Vpk[8][12][0])+(Vpk[4][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[4][12][2])+((IkWpk[8][12][0]*Wpk[4][12][0])+(IkWpk[8][12][1]*
          Wpk[4][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[4][13][2]*Vpk[8][13][2])+((Vpk[4][13][0]*
          Vpk[8][13][0])+(Vpk[4][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[4][13][2])+((IkWpk[8][13][0]*Wpk[4][13][0])+(IkWpk[8][13][1]*
          Wpk[4][13][1]))))+temp[1]);
        mm[4][8] = (((mk[5]*((Vpk[4][14][2]*Vpk[8][14][2])+((Vpk[4][14][0]*
          Vpk[8][14][0])+(Vpk[4][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[4][14][2])+((IkWpk[8][14][0]*Wpk[4][14][0])+(IkWpk[8][14][1]*
          Wpk[4][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[4][13][2]*Vpk[9][13][2])+((Vpk[4][13][0]*
          Vpk[9][13][0])+(Vpk[4][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[4][11][2]*Vpk[9][11][2])+((Vpk[4][11][0]*Vpk[9][11][0])+(
          Vpk[4][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[4][12][2]*Vpk[9][12][2])+
          ((Vpk[4][12][0]*Vpk[9][12][0])+(Vpk[4][12][1]*Vpk[9][12][1]))))));
        mm[4][9] = ((mk[5]*((Vpk[4][14][2]*Vpk[9][14][2])+((Vpk[4][14][0]*
          Vpk[9][14][0])+(Vpk[4][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[4][13][2]*Vpk[10][13][2])+((Vpk[4][13][0]*
          Vpk[10][13][0])+(Vpk[4][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[4][11][2]*Vpk[10][11][2])+((Vpk[4][11][0]*Vpk[10][11][0])+(
          Vpk[4][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[4][12][2]*Vpk[10][12][2]
          )+((Vpk[4][12][0]*Vpk[10][12][0])+(Vpk[4][12][1]*Vpk[10][12][1]))))));
        mm[4][10] = ((mk[5]*((Vpk[4][14][2]*Vpk[10][14][2])+((Vpk[4][14][0]*
          Vpk[10][14][0])+(Vpk[4][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[4][11][2]*Vpk[11][11][2])+((Vpk[4][11][0]*
          Vpk[11][11][0])+(Vpk[4][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[4][11][2])+((IkWpk[11][11][0]*Wpk[4][11][0])+(IkWpk[11][11][1]*
          Wpk[4][11][1]))))+((mk[3]*((Vpk[4][12][2]*Vpk[11][12][2])+((
          Vpk[4][12][0]*Vpk[11][12][0])+(Vpk[4][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[4][12][2])+((IkWpk[11][12][0]*Wpk[4][12][0])+(
          IkWpk[11][12][1]*Wpk[4][12][1])))));
        temp[1] = (((mk[4]*((Vpk[4][13][2]*Vpk[11][13][2])+((Vpk[4][13][0]*
          Vpk[11][13][0])+(Vpk[4][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[4][13][2])+((IkWpk[11][13][0]*Wpk[4][13][0])+(IkWpk[11][13][1]*
          Wpk[4][13][1]))))+temp[0]);
        mm[4][11] = (((mk[5]*((Vpk[4][14][2]*Vpk[11][14][2])+((Vpk[4][14][0]*
          Vpk[11][14][0])+(Vpk[4][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[4][14][2])+((IkWpk[11][14][0]*Wpk[4][14][0])+(IkWpk[11][14][1]*
          Wpk[4][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[4][12][2]*Vpk[12][12][2])+((Vpk[4][12][0]*
          Vpk[12][12][0])+(Vpk[4][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[4][12][2])+((IkWpk[12][12][0]*Wpk[4][12][0])+(IkWpk[12][12][1]*
          Wpk[4][12][1]))))+((mk[4]*((Vpk[4][13][2]*Vpk[12][13][2])+((
          Vpk[4][13][0]*Vpk[12][13][0])+(Vpk[4][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[4][13][2])+((IkWpk[12][13][0]*Wpk[4][13][0])+(
          IkWpk[12][13][1]*Wpk[4][13][1])))));
        mm[4][12] = (((mk[5]*((Vpk[4][14][2]*Vpk[12][14][2])+((Vpk[4][14][0]*
          Vpk[12][14][0])+(Vpk[4][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[4][14][2])+((IkWpk[12][14][0]*Wpk[4][14][0])+(IkWpk[12][14][1]*
          Wpk[4][14][1]))))+temp[0]);
        mm[4][13] = (((mk[4]*((Vpk[4][13][2]*Vpk[13][13][2])+((Vpk[4][13][0]*
          Vpk[13][13][0])+(Vpk[4][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[4][13][2])+((IkWpk[13][13][0]*Wpk[4][13][0])+(IkWpk[13][13][1]*
          Wpk[4][13][1]))))+((mk[5]*((Vpk[4][14][2]*Vpk[13][14][2])+((
          Vpk[4][14][0]*Vpk[13][14][0])+(Vpk[4][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[4][14][2])+((IkWpk[13][14][0]*Wpk[4][14][0])+(
          IkWpk[13][14][1]*Wpk[4][14][1])))));
        mm[4][14] = ((mk[5]*((Vpk[4][14][2]*Vpk[14][14][2])+((Vpk[4][14][0]*
          Vpk[14][14][0])+(Vpk[4][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[4][14][2])+((IkWpk[14][14][0]*Wpk[4][14][0])+(IkWpk[14][14][1]*
          Wpk[4][14][1]))));
        temp[0] = (((mk[6]*((Vpk[4][17][2]*Vpk[15][17][2])+((Vpk[4][17][0]*
          Vpk[15][17][0])+(Vpk[4][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[4][17][2])+((IkWpk[15][17][0]*Wpk[4][17][0])+(IkWpk[15][17][1]*
          Wpk[4][17][1]))))+((mk[7]*((Vpk[4][20][2]*Vpk[15][20][2])+((
          Vpk[4][20][0]*Vpk[15][20][0])+(Vpk[4][20][1]*Vpk[15][20][1]))))+((
          IkWpk[15][20][2]*Wpk[4][20][2])+((IkWpk[15][20][0]*Wpk[4][20][0])+(
          IkWpk[15][20][1]*Wpk[4][20][1])))));
        temp[1] = (((mk[8]*((Vpk[4][21][2]*Vpk[15][21][2])+((Vpk[4][21][0]*
          Vpk[15][21][0])+(Vpk[4][21][1]*Vpk[15][21][1]))))+((IkWpk[15][21][2]*
          Wpk[4][21][2])+((IkWpk[15][21][0]*Wpk[4][21][0])+(IkWpk[15][21][1]*
          Wpk[4][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[4][22][2]*Vpk[15][22][2])+((Vpk[4][22][0]*
          Vpk[15][22][0])+(Vpk[4][22][1]*Vpk[15][22][1]))))+((IkWpk[15][22][2]*
          Wpk[4][22][2])+((IkWpk[15][22][0]*Wpk[4][22][0])+(IkWpk[15][22][1]*
          Wpk[4][22][1]))))+temp[1]);
        mm[4][15] = (((mk[10]*((Vpk[4][23][2]*Vpk[15][23][2])+((Vpk[4][23][0]*
          Vpk[15][23][0])+(Vpk[4][23][1]*Vpk[15][23][1]))))+((IkWpk[15][23][2]*
          Wpk[4][23][2])+((IkWpk[15][23][0]*Wpk[4][23][0])+(IkWpk[15][23][1]*
          Wpk[4][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[4][17][2]*Vpk[16][17][2])+((Vpk[4][17][0]*
          Vpk[16][17][0])+(Vpk[4][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][2]*
          Wpk[4][17][2])+((IkWpk[16][17][0]*Wpk[4][17][0])+(IkWpk[16][17][1]*
          Wpk[4][17][1]))))+((mk[7]*((Vpk[4][20][2]*Vpk[16][20][2])+((
          Vpk[4][20][0]*Vpk[16][20][0])+(Vpk[4][20][1]*Vpk[16][20][1]))))+((
          IkWpk[16][20][2]*Wpk[4][20][2])+((IkWpk[16][20][0]*Wpk[4][20][0])+(
          IkWpk[16][20][1]*Wpk[4][20][1])))));
        temp[1] = (((mk[8]*((Vpk[4][21][2]*Vpk[16][21][2])+((Vpk[4][21][0]*
          Vpk[16][21][0])+(Vpk[4][21][1]*Vpk[16][21][1]))))+((IkWpk[16][21][2]*
          Wpk[4][21][2])+((IkWpk[16][21][0]*Wpk[4][21][0])+(IkWpk[16][21][1]*
          Wpk[4][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[4][22][2]*Vpk[16][22][2])+((Vpk[4][22][0]*
          Vpk[16][22][0])+(Vpk[4][22][1]*Vpk[16][22][1]))))+((IkWpk[16][22][2]*
          Wpk[4][22][2])+((IkWpk[16][22][0]*Wpk[4][22][0])+(IkWpk[16][22][1]*
          Wpk[4][22][1]))))+temp[1]);
        mm[4][16] = (((mk[10]*((Vpk[4][23][2]*Vpk[16][23][2])+((Vpk[4][23][0]*
          Vpk[16][23][0])+(Vpk[4][23][1]*Vpk[16][23][1]))))+((IkWpk[16][23][2]*
          Wpk[4][23][2])+((IkWpk[16][23][0]*Wpk[4][23][0])+(IkWpk[16][23][1]*
          Wpk[4][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[4][17][2]*Vpk[17][17][2])+((Vpk[4][17][0]*
          Vpk[17][17][0])+(Vpk[4][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          Wpk[4][17][2])+((IkWpk[17][17][0]*Wpk[4][17][0])+(IkWpk[17][17][1]*
          Wpk[4][17][1]))))+((mk[7]*((Vpk[4][20][2]*Vpk[17][20][2])+((
          Vpk[4][20][0]*Vpk[17][20][0])+(Vpk[4][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[4][20][2])+((IkWpk[17][20][0]*Wpk[4][20][0])+(
          IkWpk[17][20][1]*Wpk[4][20][1])))));
        temp[1] = (((mk[8]*((Vpk[4][21][2]*Vpk[17][21][2])+((Vpk[4][21][0]*
          Vpk[17][21][0])+(Vpk[4][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[4][21][2])+((IkWpk[17][21][0]*Wpk[4][21][0])+(IkWpk[17][21][1]*
          Wpk[4][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[4][22][2]*Vpk[17][22][2])+((Vpk[4][22][0]*
          Vpk[17][22][0])+(Vpk[4][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[4][22][2])+((IkWpk[17][22][0]*Wpk[4][22][0])+(IkWpk[17][22][1]*
          Wpk[4][22][1]))))+temp[1]);
        mm[4][17] = (((mk[10]*((Vpk[4][23][2]*Vpk[17][23][2])+((Vpk[4][23][0]*
          Vpk[17][23][0])+(Vpk[4][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]*
          Wpk[4][23][2])+((IkWpk[17][23][0]*Wpk[4][23][0])+(IkWpk[17][23][1]*
          Wpk[4][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[4][22][2]*Vpk[18][22][2])+((Vpk[4][22][0]*
          Vpk[18][22][0])+(Vpk[4][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[4][20][2]*Vpk[18][20][2])+((Vpk[4][20][0]*Vpk[18][20][0])+(
          Vpk[4][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[4][21][2]*Vpk[18][21][2]
          )+((Vpk[4][21][0]*Vpk[18][21][0])+(Vpk[4][21][1]*Vpk[18][21][1]))))));
        mm[4][18] = ((mk[10]*((Vpk[4][23][2]*Vpk[18][23][2])+((Vpk[4][23][0]*
          Vpk[18][23][0])+(Vpk[4][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[4][22][2]*Vpk[19][22][2])+((Vpk[4][22][0]*
          Vpk[19][22][0])+(Vpk[4][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[4][20][2]*Vpk[19][20][2])+((Vpk[4][20][0]*Vpk[19][20][0])+(
          Vpk[4][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[4][21][2]*Vpk[19][21][2]
          )+((Vpk[4][21][0]*Vpk[19][21][0])+(Vpk[4][21][1]*Vpk[19][21][1]))))));
        mm[4][19] = ((mk[10]*((Vpk[4][23][2]*Vpk[19][23][2])+((Vpk[4][23][0]*
          Vpk[19][23][0])+(Vpk[4][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[4][20][2]*Vpk[20][20][2])+((Vpk[4][20][0]*
          Vpk[20][20][0])+(Vpk[4][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[4][20][2])+((IkWpk[20][20][0]*Wpk[4][20][0])+(IkWpk[20][20][1]*
          Wpk[4][20][1]))))+((mk[8]*((Vpk[4][21][2]*Vpk[20][21][2])+((
          Vpk[4][21][0]*Vpk[20][21][0])+(Vpk[4][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[4][21][2])+((IkWpk[20][21][0]*Wpk[4][21][0])+(
          IkWpk[20][21][1]*Wpk[4][21][1])))));
        temp[1] = (((mk[9]*((Vpk[4][22][2]*Vpk[20][22][2])+((Vpk[4][22][0]*
          Vpk[20][22][0])+(Vpk[4][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[4][22][2])+((IkWpk[20][22][0]*Wpk[4][22][0])+(IkWpk[20][22][1]*
          Wpk[4][22][1]))))+temp[0]);
        mm[4][20] = (((mk[10]*((Vpk[4][23][2]*Vpk[20][23][2])+((Vpk[4][23][0]*
          Vpk[20][23][0])+(Vpk[4][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]*
          Wpk[4][23][2])+((IkWpk[20][23][0]*Wpk[4][23][0])+(IkWpk[20][23][1]*
          Wpk[4][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[4][21][2]*Vpk[21][21][2])+((Vpk[4][21][0]*
          Vpk[21][21][0])+(Vpk[4][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[4][21][2])+((IkWpk[21][21][0]*Wpk[4][21][0])+(IkWpk[21][21][1]*
          Wpk[4][21][1]))))+((mk[9]*((Vpk[4][22][2]*Vpk[21][22][2])+((
          Vpk[4][22][0]*Vpk[21][22][0])+(Vpk[4][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[4][22][2])+((IkWpk[21][22][0]*Wpk[4][22][0])+(
          IkWpk[21][22][1]*Wpk[4][22][1])))));
        mm[4][21] = (((mk[10]*((Vpk[4][23][2]*Vpk[21][23][2])+((Vpk[4][23][0]*
          Vpk[21][23][0])+(Vpk[4][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]*
          Wpk[4][23][2])+((IkWpk[21][23][0]*Wpk[4][23][0])+(IkWpk[21][23][1]*
          Wpk[4][23][1]))))+temp[0]);
        mm[4][22] = (((mk[9]*((Vpk[4][22][2]*Vpk[22][22][2])+((Vpk[4][22][0]*
          Vpk[22][22][0])+(Vpk[4][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[4][22][2])+((IkWpk[22][22][0]*Wpk[4][22][0])+(IkWpk[22][22][1]*
          Wpk[4][22][1]))))+((mk[10]*((Vpk[4][23][2]*Vpk[22][23][2])+((
          Vpk[4][23][0]*Vpk[22][23][0])+(Vpk[4][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[4][23][2])+((IkWpk[22][23][0]*Wpk[4][23][0])+(
          IkWpk[22][23][1]*Wpk[4][23][1])))));
        mm[4][23] = ((mk[10]*((Vpk[4][23][2]*Vpk[23][23][2])+((Vpk[4][23][0]*
          Vpk[23][23][0])+(Vpk[4][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[4][23][2])+((IkWpk[23][23][0]*Wpk[4][23][0])+(IkWpk[23][23][1]*
          Wpk[4][23][1]))));
        mm[4][24] = ((mk[11]*((Vpk[4][26][2]*Vpk[24][26][2])+((Vpk[4][26][0]*
          Vpk[24][26][0])+(Vpk[4][26][1]*Vpk[24][26][1]))))+((IkWpk[24][26][2]*
          Wpk[4][26][2])+((IkWpk[24][26][0]*Wpk[4][26][0])+(IkWpk[24][26][1]*
          Wpk[4][26][1]))));
        mm[4][25] = ((mk[11]*((Vpk[4][26][2]*Vpk[25][26][2])+((Vpk[4][26][0]*
          Vpk[25][26][0])+(Vpk[4][26][1]*Vpk[25][26][1]))))+((IkWpk[25][26][2]*
          Wpk[4][26][2])+((IkWpk[25][26][0]*Wpk[4][26][0])+(IkWpk[25][26][1]*
          Wpk[4][26][1]))));
        mm[4][26] = ((mk[11]*((Vpk[4][26][2]*Vpk[26][26][2])+((Vpk[4][26][0]*
          Vpk[26][26][0])+(Vpk[4][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          Wpk[4][26][2])+((IkWpk[26][26][0]*Wpk[4][26][0])+(IkWpk[26][26][1]*
          Wpk[4][26][1]))));
        temp[0] = (((mk[0]*((Vpk[5][5][2]*Vpk[5][5][2])+((Vpk[5][5][0]*
          Vpk[5][5][0])+(Vpk[5][5][1]*Vpk[5][5][1]))))+((IkWpk[5][5][2]*
          pin[2][2])+((IkWpk[5][5][0]*pin[2][0])+(IkWpk[5][5][1]*pin[2][1]))))+(
          (mk[1]*((Vpk[5][8][2]*Vpk[5][8][2])+((Vpk[5][8][0]*Vpk[5][8][0])+(
          Vpk[5][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*Wpk[5][8][2])+((
          IkWpk[5][8][0]*Wpk[5][8][0])+(IkWpk[5][8][1]*Wpk[5][8][1])))));
        temp[1] = (((mk[2]*((Vpk[5][11][2]*Vpk[5][11][2])+((Vpk[5][11][0]*
          Vpk[5][11][0])+(Vpk[5][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[5][11][2])+((IkWpk[5][11][0]*Wpk[5][11][0])+(IkWpk[5][11][1]*
          Wpk[5][11][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[5][12][2]*Vpk[5][12][2])+((Vpk[5][12][0]*
          Vpk[5][12][0])+(Vpk[5][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[5][12][2])+((IkWpk[5][12][0]*Wpk[5][12][0])+(IkWpk[5][12][1]*
          Wpk[5][12][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[5][13][2]*Vpk[5][13][2])+((Vpk[5][13][0]*
          Vpk[5][13][0])+(Vpk[5][13][1]*Vpk[5][13][1]))))+((IkWpk[5][13][2]*
          Wpk[5][13][2])+((IkWpk[5][13][0]*Wpk[5][13][0])+(IkWpk[5][13][1]*
          Wpk[5][13][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[5][14][2]*Vpk[5][14][2])+((Vpk[5][14][0]*
          Vpk[5][14][0])+(Vpk[5][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[5][14][2])+((IkWpk[5][14][0]*Wpk[5][14][0])+(IkWpk[5][14][1]*
          Wpk[5][14][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[5][17][2]*Vpk[5][17][2])+((Vpk[5][17][0]*
          Vpk[5][17][0])+(Vpk[5][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[5][17][2])+((IkWpk[5][17][0]*Wpk[5][17][0])+(IkWpk[5][17][1]*
          Wpk[5][17][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[5][20][2]*Vpk[5][20][2])+((Vpk[5][20][0]*
          Vpk[5][20][0])+(Vpk[5][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[5][20][2])+((IkWpk[5][20][0]*Wpk[5][20][0])+(IkWpk[5][20][1]*
          Wpk[5][20][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[5][21][2]*Vpk[5][21][2])+((Vpk[5][21][0]*
          Vpk[5][21][0])+(Vpk[5][21][1]*Vpk[5][21][1]))))+((IkWpk[5][21][2]*
          Wpk[5][21][2])+((IkWpk[5][21][0]*Wpk[5][21][0])+(IkWpk[5][21][1]*
          Wpk[5][21][1]))))+temp[6]);
        temp[8] = (((mk[9]*((Vpk[5][22][2]*Vpk[5][22][2])+((Vpk[5][22][0]*
          Vpk[5][22][0])+(Vpk[5][22][1]*Vpk[5][22][1]))))+((IkWpk[5][22][2]*
          Wpk[5][22][2])+((IkWpk[5][22][0]*Wpk[5][22][0])+(IkWpk[5][22][1]*
          Wpk[5][22][1]))))+temp[7]);
        temp[9] = (((mk[10]*((Vpk[5][23][2]*Vpk[5][23][2])+((Vpk[5][23][0]*
          Vpk[5][23][0])+(Vpk[5][23][1]*Vpk[5][23][1]))))+((IkWpk[5][23][2]*
          Wpk[5][23][2])+((IkWpk[5][23][0]*Wpk[5][23][0])+(IkWpk[5][23][1]*
          Wpk[5][23][1]))))+temp[8]);
        mm[5][5] = (((mk[11]*((Vpk[5][26][2]*Vpk[5][26][2])+((Vpk[5][26][0]*
          Vpk[5][26][0])+(Vpk[5][26][1]*Vpk[5][26][1]))))+((IkWpk[5][26][2]*
          Wpk[5][26][2])+((IkWpk[5][26][0]*Wpk[5][26][0])+(IkWpk[5][26][1]*
          Wpk[5][26][1]))))+temp[9]);
        temp[0] = (((mk[1]*((Vpk[5][8][2]*Vpk[6][8][2])+((Vpk[5][8][0]*
          Vpk[6][8][0])+(Vpk[5][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][2]*
          Wpk[5][8][2])+((IkWpk[6][8][0]*Wpk[5][8][0])+(IkWpk[6][8][1]*
          Wpk[5][8][1]))))+((mk[2]*((Vpk[5][11][2]*Vpk[6][11][2])+((
          Vpk[5][11][0]*Vpk[6][11][0])+(Vpk[5][11][1]*Vpk[6][11][1]))))+((
          IkWpk[6][11][2]*Wpk[5][11][2])+((IkWpk[6][11][0]*Wpk[5][11][0])+(
          IkWpk[6][11][1]*Wpk[5][11][1])))));
        temp[1] = (((mk[3]*((Vpk[5][12][2]*Vpk[6][12][2])+((Vpk[5][12][0]*
          Vpk[6][12][0])+(Vpk[5][12][1]*Vpk[6][12][1]))))+((IkWpk[6][12][2]*
          Wpk[5][12][2])+((IkWpk[6][12][0]*Wpk[5][12][0])+(IkWpk[6][12][1]*
          Wpk[5][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[5][13][2]*Vpk[6][13][2])+((Vpk[5][13][0]*
          Vpk[6][13][0])+(Vpk[5][13][1]*Vpk[6][13][1]))))+((IkWpk[6][13][2]*
          Wpk[5][13][2])+((IkWpk[6][13][0]*Wpk[5][13][0])+(IkWpk[6][13][1]*
          Wpk[5][13][1]))))+temp[1]);
        mm[5][6] = (((mk[5]*((Vpk[5][14][2]*Vpk[6][14][2])+((Vpk[5][14][0]*
          Vpk[6][14][0])+(Vpk[5][14][1]*Vpk[6][14][1]))))+((IkWpk[6][14][2]*
          Wpk[5][14][2])+((IkWpk[6][14][0]*Wpk[5][14][0])+(IkWpk[6][14][1]*
          Wpk[5][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[5][8][2]*Vpk[7][8][2])+((Vpk[5][8][0]*
          Vpk[7][8][0])+(Vpk[5][8][1]*Vpk[7][8][1]))))+((IkWpk[7][8][2]*
          Wpk[5][8][2])+((IkWpk[7][8][0]*Wpk[5][8][0])+(IkWpk[7][8][1]*
          Wpk[5][8][1]))))+((mk[2]*((Vpk[5][11][2]*Vpk[7][11][2])+((
          Vpk[5][11][0]*Vpk[7][11][0])+(Vpk[5][11][1]*Vpk[7][11][1]))))+((
          IkWpk[7][11][2]*Wpk[5][11][2])+((IkWpk[7][11][0]*Wpk[5][11][0])+(
          IkWpk[7][11][1]*Wpk[5][11][1])))));
        temp[1] = (((mk[3]*((Vpk[5][12][2]*Vpk[7][12][2])+((Vpk[5][12][0]*
          Vpk[7][12][0])+(Vpk[5][12][1]*Vpk[7][12][1]))))+((IkWpk[7][12][2]*
          Wpk[5][12][2])+((IkWpk[7][12][0]*Wpk[5][12][0])+(IkWpk[7][12][1]*
          Wpk[5][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[5][13][2]*Vpk[7][13][2])+((Vpk[5][13][0]*
          Vpk[7][13][0])+(Vpk[5][13][1]*Vpk[7][13][1]))))+((IkWpk[7][13][2]*
          Wpk[5][13][2])+((IkWpk[7][13][0]*Wpk[5][13][0])+(IkWpk[7][13][1]*
          Wpk[5][13][1]))))+temp[1]);
        mm[5][7] = (((mk[5]*((Vpk[5][14][2]*Vpk[7][14][2])+((Vpk[5][14][0]*
          Vpk[7][14][0])+(Vpk[5][14][1]*Vpk[7][14][1]))))+((IkWpk[7][14][2]*
          Wpk[5][14][2])+((IkWpk[7][14][0]*Wpk[5][14][0])+(IkWpk[7][14][1]*
          Wpk[5][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[5][8][2]*Vpk[8][8][2])+((Vpk[5][8][0]*
          Vpk[8][8][0])+(Vpk[5][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          Wpk[5][8][2])+((IkWpk[8][8][0]*Wpk[5][8][0])+(IkWpk[8][8][1]*
          Wpk[5][8][1]))))+((mk[2]*((Vpk[5][11][2]*Vpk[8][11][2])+((
          Vpk[5][11][0]*Vpk[8][11][0])+(Vpk[5][11][1]*Vpk[8][11][1]))))+((
          IkWpk[8][11][2]*Wpk[5][11][2])+((IkWpk[8][11][0]*Wpk[5][11][0])+(
          IkWpk[8][11][1]*Wpk[5][11][1])))));
        temp[1] = (((mk[3]*((Vpk[5][12][2]*Vpk[8][12][2])+((Vpk[5][12][0]*
          Vpk[8][12][0])+(Vpk[5][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[5][12][2])+((IkWpk[8][12][0]*Wpk[5][12][0])+(IkWpk[8][12][1]*
          Wpk[5][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[5][13][2]*Vpk[8][13][2])+((Vpk[5][13][0]*
          Vpk[8][13][0])+(Vpk[5][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[5][13][2])+((IkWpk[8][13][0]*Wpk[5][13][0])+(IkWpk[8][13][1]*
          Wpk[5][13][1]))))+temp[1]);
        mm[5][8] = (((mk[5]*((Vpk[5][14][2]*Vpk[8][14][2])+((Vpk[5][14][0]*
          Vpk[8][14][0])+(Vpk[5][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[5][14][2])+((IkWpk[8][14][0]*Wpk[5][14][0])+(IkWpk[8][14][1]*
          Wpk[5][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[5][13][2]*Vpk[9][13][2])+((Vpk[5][13][0]*
          Vpk[9][13][0])+(Vpk[5][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[5][11][2]*Vpk[9][11][2])+((Vpk[5][11][0]*Vpk[9][11][0])+(
          Vpk[5][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[5][12][2]*Vpk[9][12][2])+
          ((Vpk[5][12][0]*Vpk[9][12][0])+(Vpk[5][12][1]*Vpk[9][12][1]))))));
        mm[5][9] = ((mk[5]*((Vpk[5][14][2]*Vpk[9][14][2])+((Vpk[5][14][0]*
          Vpk[9][14][0])+(Vpk[5][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[5][13][2]*Vpk[10][13][2])+((Vpk[5][13][0]*
          Vpk[10][13][0])+(Vpk[5][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[5][11][2]*Vpk[10][11][2])+((Vpk[5][11][0]*Vpk[10][11][0])+(
          Vpk[5][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[5][12][2]*Vpk[10][12][2]
          )+((Vpk[5][12][0]*Vpk[10][12][0])+(Vpk[5][12][1]*Vpk[10][12][1]))))));
        mm[5][10] = ((mk[5]*((Vpk[5][14][2]*Vpk[10][14][2])+((Vpk[5][14][0]*
          Vpk[10][14][0])+(Vpk[5][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[5][11][2]*Vpk[11][11][2])+((Vpk[5][11][0]*
          Vpk[11][11][0])+(Vpk[5][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[5][11][2])+((IkWpk[11][11][0]*Wpk[5][11][0])+(IkWpk[11][11][1]*
          Wpk[5][11][1]))))+((mk[3]*((Vpk[5][12][2]*Vpk[11][12][2])+((
          Vpk[5][12][0]*Vpk[11][12][0])+(Vpk[5][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[5][12][2])+((IkWpk[11][12][0]*Wpk[5][12][0])+(
          IkWpk[11][12][1]*Wpk[5][12][1])))));
        temp[1] = (((mk[4]*((Vpk[5][13][2]*Vpk[11][13][2])+((Vpk[5][13][0]*
          Vpk[11][13][0])+(Vpk[5][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[5][13][2])+((IkWpk[11][13][0]*Wpk[5][13][0])+(IkWpk[11][13][1]*
          Wpk[5][13][1]))))+temp[0]);
        mm[5][11] = (((mk[5]*((Vpk[5][14][2]*Vpk[11][14][2])+((Vpk[5][14][0]*
          Vpk[11][14][0])+(Vpk[5][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[5][14][2])+((IkWpk[11][14][0]*Wpk[5][14][0])+(IkWpk[11][14][1]*
          Wpk[5][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[5][12][2]*Vpk[12][12][2])+((Vpk[5][12][0]*
          Vpk[12][12][0])+(Vpk[5][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[5][12][2])+((IkWpk[12][12][0]*Wpk[5][12][0])+(IkWpk[12][12][1]*
          Wpk[5][12][1]))))+((mk[4]*((Vpk[5][13][2]*Vpk[12][13][2])+((
          Vpk[5][13][0]*Vpk[12][13][0])+(Vpk[5][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[5][13][2])+((IkWpk[12][13][0]*Wpk[5][13][0])+(
          IkWpk[12][13][1]*Wpk[5][13][1])))));
        mm[5][12] = (((mk[5]*((Vpk[5][14][2]*Vpk[12][14][2])+((Vpk[5][14][0]*
          Vpk[12][14][0])+(Vpk[5][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[5][14][2])+((IkWpk[12][14][0]*Wpk[5][14][0])+(IkWpk[12][14][1]*
          Wpk[5][14][1]))))+temp[0]);
        mm[5][13] = (((mk[4]*((Vpk[5][13][2]*Vpk[13][13][2])+((Vpk[5][13][0]*
          Vpk[13][13][0])+(Vpk[5][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[5][13][2])+((IkWpk[13][13][0]*Wpk[5][13][0])+(IkWpk[13][13][1]*
          Wpk[5][13][1]))))+((mk[5]*((Vpk[5][14][2]*Vpk[13][14][2])+((
          Vpk[5][14][0]*Vpk[13][14][0])+(Vpk[5][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[5][14][2])+((IkWpk[13][14][0]*Wpk[5][14][0])+(
          IkWpk[13][14][1]*Wpk[5][14][1])))));
        mm[5][14] = ((mk[5]*((Vpk[5][14][2]*Vpk[14][14][2])+((Vpk[5][14][0]*
          Vpk[14][14][0])+(Vpk[5][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[5][14][2])+((IkWpk[14][14][0]*Wpk[5][14][0])+(IkWpk[14][14][1]*
          Wpk[5][14][1]))));
        temp[0] = (((mk[6]*((Vpk[5][17][2]*Vpk[15][17][2])+((Vpk[5][17][0]*
          Vpk[15][17][0])+(Vpk[5][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[5][17][2])+((IkWpk[15][17][0]*Wpk[5][17][0])+(IkWpk[15][17][1]*
          Wpk[5][17][1]))))+((mk[7]*((Vpk[5][20][2]*Vpk[15][20][2])+((
          Vpk[5][20][0]*Vpk[15][20][0])+(Vpk[5][20][1]*Vpk[15][20][1]))))+((
          IkWpk[15][20][2]*Wpk[5][20][2])+((IkWpk[15][20][0]*Wpk[5][20][0])+(
          IkWpk[15][20][1]*Wpk[5][20][1])))));
        temp[1] = (((mk[8]*((Vpk[5][21][2]*Vpk[15][21][2])+((Vpk[5][21][0]*
          Vpk[15][21][0])+(Vpk[5][21][1]*Vpk[15][21][1]))))+((IkWpk[15][21][2]*
          Wpk[5][21][2])+((IkWpk[15][21][0]*Wpk[5][21][0])+(IkWpk[15][21][1]*
          Wpk[5][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[5][22][2]*Vpk[15][22][2])+((Vpk[5][22][0]*
          Vpk[15][22][0])+(Vpk[5][22][1]*Vpk[15][22][1]))))+((IkWpk[15][22][2]*
          Wpk[5][22][2])+((IkWpk[15][22][0]*Wpk[5][22][0])+(IkWpk[15][22][1]*
          Wpk[5][22][1]))))+temp[1]);
        mm[5][15] = (((mk[10]*((Vpk[5][23][2]*Vpk[15][23][2])+((Vpk[5][23][0]*
          Vpk[15][23][0])+(Vpk[5][23][1]*Vpk[15][23][1]))))+((IkWpk[15][23][2]*
          Wpk[5][23][2])+((IkWpk[15][23][0]*Wpk[5][23][0])+(IkWpk[15][23][1]*
          Wpk[5][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[5][17][2]*Vpk[16][17][2])+((Vpk[5][17][0]*
          Vpk[16][17][0])+(Vpk[5][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][2]*
          Wpk[5][17][2])+((IkWpk[16][17][0]*Wpk[5][17][0])+(IkWpk[16][17][1]*
          Wpk[5][17][1]))))+((mk[7]*((Vpk[5][20][2]*Vpk[16][20][2])+((
          Vpk[5][20][0]*Vpk[16][20][0])+(Vpk[5][20][1]*Vpk[16][20][1]))))+((
          IkWpk[16][20][2]*Wpk[5][20][2])+((IkWpk[16][20][0]*Wpk[5][20][0])+(
          IkWpk[16][20][1]*Wpk[5][20][1])))));
        temp[1] = (((mk[8]*((Vpk[5][21][2]*Vpk[16][21][2])+((Vpk[5][21][0]*
          Vpk[16][21][0])+(Vpk[5][21][1]*Vpk[16][21][1]))))+((IkWpk[16][21][2]*
          Wpk[5][21][2])+((IkWpk[16][21][0]*Wpk[5][21][0])+(IkWpk[16][21][1]*
          Wpk[5][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[5][22][2]*Vpk[16][22][2])+((Vpk[5][22][0]*
          Vpk[16][22][0])+(Vpk[5][22][1]*Vpk[16][22][1]))))+((IkWpk[16][22][2]*
          Wpk[5][22][2])+((IkWpk[16][22][0]*Wpk[5][22][0])+(IkWpk[16][22][1]*
          Wpk[5][22][1]))))+temp[1]);
        mm[5][16] = (((mk[10]*((Vpk[5][23][2]*Vpk[16][23][2])+((Vpk[5][23][0]*
          Vpk[16][23][0])+(Vpk[5][23][1]*Vpk[16][23][1]))))+((IkWpk[16][23][2]*
          Wpk[5][23][2])+((IkWpk[16][23][0]*Wpk[5][23][0])+(IkWpk[16][23][1]*
          Wpk[5][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[5][17][2]*Vpk[17][17][2])+((Vpk[5][17][0]*
          Vpk[17][17][0])+(Vpk[5][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          Wpk[5][17][2])+((IkWpk[17][17][0]*Wpk[5][17][0])+(IkWpk[17][17][1]*
          Wpk[5][17][1]))))+((mk[7]*((Vpk[5][20][2]*Vpk[17][20][2])+((
          Vpk[5][20][0]*Vpk[17][20][0])+(Vpk[5][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[5][20][2])+((IkWpk[17][20][0]*Wpk[5][20][0])+(
          IkWpk[17][20][1]*Wpk[5][20][1])))));
        temp[1] = (((mk[8]*((Vpk[5][21][2]*Vpk[17][21][2])+((Vpk[5][21][0]*
          Vpk[17][21][0])+(Vpk[5][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[5][21][2])+((IkWpk[17][21][0]*Wpk[5][21][0])+(IkWpk[17][21][1]*
          Wpk[5][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[5][22][2]*Vpk[17][22][2])+((Vpk[5][22][0]*
          Vpk[17][22][0])+(Vpk[5][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[5][22][2])+((IkWpk[17][22][0]*Wpk[5][22][0])+(IkWpk[17][22][1]*
          Wpk[5][22][1]))))+temp[1]);
        mm[5][17] = (((mk[10]*((Vpk[5][23][2]*Vpk[17][23][2])+((Vpk[5][23][0]*
          Vpk[17][23][0])+(Vpk[5][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]*
          Wpk[5][23][2])+((IkWpk[17][23][0]*Wpk[5][23][0])+(IkWpk[17][23][1]*
          Wpk[5][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[5][22][2]*Vpk[18][22][2])+((Vpk[5][22][0]*
          Vpk[18][22][0])+(Vpk[5][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[5][20][2]*Vpk[18][20][2])+((Vpk[5][20][0]*Vpk[18][20][0])+(
          Vpk[5][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[5][21][2]*Vpk[18][21][2]
          )+((Vpk[5][21][0]*Vpk[18][21][0])+(Vpk[5][21][1]*Vpk[18][21][1]))))));
        mm[5][18] = ((mk[10]*((Vpk[5][23][2]*Vpk[18][23][2])+((Vpk[5][23][0]*
          Vpk[18][23][0])+(Vpk[5][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[5][22][2]*Vpk[19][22][2])+((Vpk[5][22][0]*
          Vpk[19][22][0])+(Vpk[5][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[5][20][2]*Vpk[19][20][2])+((Vpk[5][20][0]*Vpk[19][20][0])+(
          Vpk[5][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[5][21][2]*Vpk[19][21][2]
          )+((Vpk[5][21][0]*Vpk[19][21][0])+(Vpk[5][21][1]*Vpk[19][21][1]))))));
        mm[5][19] = ((mk[10]*((Vpk[5][23][2]*Vpk[19][23][2])+((Vpk[5][23][0]*
          Vpk[19][23][0])+(Vpk[5][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[5][20][2]*Vpk[20][20][2])+((Vpk[5][20][0]*
          Vpk[20][20][0])+(Vpk[5][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[5][20][2])+((IkWpk[20][20][0]*Wpk[5][20][0])+(IkWpk[20][20][1]*
          Wpk[5][20][1]))))+((mk[8]*((Vpk[5][21][2]*Vpk[20][21][2])+((
          Vpk[5][21][0]*Vpk[20][21][0])+(Vpk[5][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[5][21][2])+((IkWpk[20][21][0]*Wpk[5][21][0])+(
          IkWpk[20][21][1]*Wpk[5][21][1])))));
        temp[1] = (((mk[9]*((Vpk[5][22][2]*Vpk[20][22][2])+((Vpk[5][22][0]*
          Vpk[20][22][0])+(Vpk[5][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[5][22][2])+((IkWpk[20][22][0]*Wpk[5][22][0])+(IkWpk[20][22][1]*
          Wpk[5][22][1]))))+temp[0]);
        mm[5][20] = (((mk[10]*((Vpk[5][23][2]*Vpk[20][23][2])+((Vpk[5][23][0]*
          Vpk[20][23][0])+(Vpk[5][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]*
          Wpk[5][23][2])+((IkWpk[20][23][0]*Wpk[5][23][0])+(IkWpk[20][23][1]*
          Wpk[5][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[5][21][2]*Vpk[21][21][2])+((Vpk[5][21][0]*
          Vpk[21][21][0])+(Vpk[5][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[5][21][2])+((IkWpk[21][21][0]*Wpk[5][21][0])+(IkWpk[21][21][1]*
          Wpk[5][21][1]))))+((mk[9]*((Vpk[5][22][2]*Vpk[21][22][2])+((
          Vpk[5][22][0]*Vpk[21][22][0])+(Vpk[5][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[5][22][2])+((IkWpk[21][22][0]*Wpk[5][22][0])+(
          IkWpk[21][22][1]*Wpk[5][22][1])))));
        mm[5][21] = (((mk[10]*((Vpk[5][23][2]*Vpk[21][23][2])+((Vpk[5][23][0]*
          Vpk[21][23][0])+(Vpk[5][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]*
          Wpk[5][23][2])+((IkWpk[21][23][0]*Wpk[5][23][0])+(IkWpk[21][23][1]*
          Wpk[5][23][1]))))+temp[0]);
        mm[5][22] = (((mk[9]*((Vpk[5][22][2]*Vpk[22][22][2])+((Vpk[5][22][0]*
          Vpk[22][22][0])+(Vpk[5][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[5][22][2])+((IkWpk[22][22][0]*Wpk[5][22][0])+(IkWpk[22][22][1]*
          Wpk[5][22][1]))))+((mk[10]*((Vpk[5][23][2]*Vpk[22][23][2])+((
          Vpk[5][23][0]*Vpk[22][23][0])+(Vpk[5][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[5][23][2])+((IkWpk[22][23][0]*Wpk[5][23][0])+(
          IkWpk[22][23][1]*Wpk[5][23][1])))));
        mm[5][23] = ((mk[10]*((Vpk[5][23][2]*Vpk[23][23][2])+((Vpk[5][23][0]*
          Vpk[23][23][0])+(Vpk[5][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[5][23][2])+((IkWpk[23][23][0]*Wpk[5][23][0])+(IkWpk[23][23][1]*
          Wpk[5][23][1]))));
        mm[5][24] = ((mk[11]*((Vpk[5][26][2]*Vpk[24][26][2])+((Vpk[5][26][0]*
          Vpk[24][26][0])+(Vpk[5][26][1]*Vpk[24][26][1]))))+((IkWpk[24][26][2]*
          Wpk[5][26][2])+((IkWpk[24][26][0]*Wpk[5][26][0])+(IkWpk[24][26][1]*
          Wpk[5][26][1]))));
        mm[5][25] = ((mk[11]*((Vpk[5][26][2]*Vpk[25][26][2])+((Vpk[5][26][0]*
          Vpk[25][26][0])+(Vpk[5][26][1]*Vpk[25][26][1]))))+((IkWpk[25][26][2]*
          Wpk[5][26][2])+((IkWpk[25][26][0]*Wpk[5][26][0])+(IkWpk[25][26][1]*
          Wpk[5][26][1]))));
        mm[5][26] = ((mk[11]*((Vpk[5][26][2]*Vpk[26][26][2])+((Vpk[5][26][0]*
          Vpk[26][26][0])+(Vpk[5][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          Wpk[5][26][2])+((IkWpk[26][26][0]*Wpk[5][26][0])+(IkWpk[26][26][1]*
          Wpk[5][26][1]))));
        temp[0] = (((mk[1]*((Vpk[6][8][2]*Vpk[6][8][2])+((Vpk[6][8][0]*
          Vpk[6][8][0])+(Vpk[6][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][2]*
          Wpk[6][8][2])+((IkWpk[6][8][0]*Wpk[6][8][0])+(IkWpk[6][8][1]*
          Wpk[6][8][1]))))+((mk[2]*((Vpk[6][11][2]*Vpk[6][11][2])+((
          Vpk[6][11][0]*Vpk[6][11][0])+(Vpk[6][11][1]*Vpk[6][11][1]))))+((
          IkWpk[6][11][2]*Wpk[6][11][2])+((IkWpk[6][11][0]*Wpk[6][11][0])+(
          IkWpk[6][11][1]*Wpk[6][11][1])))));
        temp[1] = (((mk[3]*((Vpk[6][12][2]*Vpk[6][12][2])+((Vpk[6][12][0]*
          Vpk[6][12][0])+(Vpk[6][12][1]*Vpk[6][12][1]))))+((IkWpk[6][12][2]*
          Wpk[6][12][2])+((IkWpk[6][12][0]*Wpk[6][12][0])+(IkWpk[6][12][1]*
          Wpk[6][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[6][13][2]*Vpk[6][13][2])+((Vpk[6][13][0]*
          Vpk[6][13][0])+(Vpk[6][13][1]*Vpk[6][13][1]))))+((IkWpk[6][13][2]*
          Wpk[6][13][2])+((IkWpk[6][13][0]*Wpk[6][13][0])+(IkWpk[6][13][1]*
          Wpk[6][13][1]))))+temp[1]);
        mm[6][6] = (((mk[5]*((Vpk[6][14][2]*Vpk[6][14][2])+((Vpk[6][14][0]*
          Vpk[6][14][0])+(Vpk[6][14][1]*Vpk[6][14][1]))))+((IkWpk[6][14][2]*
          Wpk[6][14][2])+((IkWpk[6][14][0]*Wpk[6][14][0])+(IkWpk[6][14][1]*
          Wpk[6][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[6][8][2]*Vpk[7][8][2])+((Vpk[6][8][0]*
          Vpk[7][8][0])+(Vpk[6][8][1]*Vpk[7][8][1]))))+((IkWpk[7][8][2]*
          Wpk[6][8][2])+((IkWpk[7][8][0]*Wpk[6][8][0])+(IkWpk[7][8][1]*
          Wpk[6][8][1]))))+((mk[2]*((Vpk[6][11][2]*Vpk[7][11][2])+((
          Vpk[6][11][0]*Vpk[7][11][0])+(Vpk[6][11][1]*Vpk[7][11][1]))))+((
          IkWpk[7][11][2]*Wpk[6][11][2])+((IkWpk[7][11][0]*Wpk[6][11][0])+(
          IkWpk[7][11][1]*Wpk[6][11][1])))));
        temp[1] = (((mk[3]*((Vpk[6][12][2]*Vpk[7][12][2])+((Vpk[6][12][0]*
          Vpk[7][12][0])+(Vpk[6][12][1]*Vpk[7][12][1]))))+((IkWpk[7][12][2]*
          Wpk[6][12][2])+((IkWpk[7][12][0]*Wpk[6][12][0])+(IkWpk[7][12][1]*
          Wpk[6][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[6][13][2]*Vpk[7][13][2])+((Vpk[6][13][0]*
          Vpk[7][13][0])+(Vpk[6][13][1]*Vpk[7][13][1]))))+((IkWpk[7][13][2]*
          Wpk[6][13][2])+((IkWpk[7][13][0]*Wpk[6][13][0])+(IkWpk[7][13][1]*
          Wpk[6][13][1]))))+temp[1]);
        mm[6][7] = (((mk[5]*((Vpk[6][14][2]*Vpk[7][14][2])+((Vpk[6][14][0]*
          Vpk[7][14][0])+(Vpk[6][14][1]*Vpk[7][14][1]))))+((IkWpk[7][14][2]*
          Wpk[6][14][2])+((IkWpk[7][14][0]*Wpk[6][14][0])+(IkWpk[7][14][1]*
          Wpk[6][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[6][8][2]*Vpk[8][8][2])+((Vpk[6][8][0]*
          Vpk[8][8][0])+(Vpk[6][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          Wpk[6][8][2])+((IkWpk[8][8][0]*Wpk[6][8][0])+(IkWpk[8][8][1]*
          Wpk[6][8][1]))))+((mk[2]*((Vpk[6][11][2]*Vpk[8][11][2])+((
          Vpk[6][11][0]*Vpk[8][11][0])+(Vpk[6][11][1]*Vpk[8][11][1]))))+((
          IkWpk[8][11][2]*Wpk[6][11][2])+((IkWpk[8][11][0]*Wpk[6][11][0])+(
          IkWpk[8][11][1]*Wpk[6][11][1])))));
        temp[1] = (((mk[3]*((Vpk[6][12][2]*Vpk[8][12][2])+((Vpk[6][12][0]*
          Vpk[8][12][0])+(Vpk[6][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[6][12][2])+((IkWpk[8][12][0]*Wpk[6][12][0])+(IkWpk[8][12][1]*
          Wpk[6][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[6][13][2]*Vpk[8][13][2])+((Vpk[6][13][0]*
          Vpk[8][13][0])+(Vpk[6][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[6][13][2])+((IkWpk[8][13][0]*Wpk[6][13][0])+(IkWpk[8][13][1]*
          Wpk[6][13][1]))))+temp[1]);
        mm[6][8] = (((mk[5]*((Vpk[6][14][2]*Vpk[8][14][2])+((Vpk[6][14][0]*
          Vpk[8][14][0])+(Vpk[6][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[6][14][2])+((IkWpk[8][14][0]*Wpk[6][14][0])+(IkWpk[8][14][1]*
          Wpk[6][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[6][13][2]*Vpk[9][13][2])+((Vpk[6][13][0]*
          Vpk[9][13][0])+(Vpk[6][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[6][11][2]*Vpk[9][11][2])+((Vpk[6][11][0]*Vpk[9][11][0])+(
          Vpk[6][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[6][12][2]*Vpk[9][12][2])+
          ((Vpk[6][12][0]*Vpk[9][12][0])+(Vpk[6][12][1]*Vpk[9][12][1]))))));
        mm[6][9] = ((mk[5]*((Vpk[6][14][2]*Vpk[9][14][2])+((Vpk[6][14][0]*
          Vpk[9][14][0])+(Vpk[6][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[6][13][2]*Vpk[10][13][2])+((Vpk[6][13][0]*
          Vpk[10][13][0])+(Vpk[6][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[6][11][2]*Vpk[10][11][2])+((Vpk[6][11][0]*Vpk[10][11][0])+(
          Vpk[6][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[6][12][2]*Vpk[10][12][2]
          )+((Vpk[6][12][0]*Vpk[10][12][0])+(Vpk[6][12][1]*Vpk[10][12][1]))))));
        mm[6][10] = ((mk[5]*((Vpk[6][14][2]*Vpk[10][14][2])+((Vpk[6][14][0]*
          Vpk[10][14][0])+(Vpk[6][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[6][11][2]*Vpk[11][11][2])+((Vpk[6][11][0]*
          Vpk[11][11][0])+(Vpk[6][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[6][11][2])+((IkWpk[11][11][0]*Wpk[6][11][0])+(IkWpk[11][11][1]*
          Wpk[6][11][1]))))+((mk[3]*((Vpk[6][12][2]*Vpk[11][12][2])+((
          Vpk[6][12][0]*Vpk[11][12][0])+(Vpk[6][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[6][12][2])+((IkWpk[11][12][0]*Wpk[6][12][0])+(
          IkWpk[11][12][1]*Wpk[6][12][1])))));
        temp[1] = (((mk[4]*((Vpk[6][13][2]*Vpk[11][13][2])+((Vpk[6][13][0]*
          Vpk[11][13][0])+(Vpk[6][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[6][13][2])+((IkWpk[11][13][0]*Wpk[6][13][0])+(IkWpk[11][13][1]*
          Wpk[6][13][1]))))+temp[0]);
        mm[6][11] = (((mk[5]*((Vpk[6][14][2]*Vpk[11][14][2])+((Vpk[6][14][0]*
          Vpk[11][14][0])+(Vpk[6][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[6][14][2])+((IkWpk[11][14][0]*Wpk[6][14][0])+(IkWpk[11][14][1]*
          Wpk[6][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[6][12][2]*Vpk[12][12][2])+((Vpk[6][12][0]*
          Vpk[12][12][0])+(Vpk[6][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[6][12][2])+((IkWpk[12][12][0]*Wpk[6][12][0])+(IkWpk[12][12][1]*
          Wpk[6][12][1]))))+((mk[4]*((Vpk[6][13][2]*Vpk[12][13][2])+((
          Vpk[6][13][0]*Vpk[12][13][0])+(Vpk[6][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[6][13][2])+((IkWpk[12][13][0]*Wpk[6][13][0])+(
          IkWpk[12][13][1]*Wpk[6][13][1])))));
        mm[6][12] = (((mk[5]*((Vpk[6][14][2]*Vpk[12][14][2])+((Vpk[6][14][0]*
          Vpk[12][14][0])+(Vpk[6][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[6][14][2])+((IkWpk[12][14][0]*Wpk[6][14][0])+(IkWpk[12][14][1]*
          Wpk[6][14][1]))))+temp[0]);
        mm[6][13] = (((mk[4]*((Vpk[6][13][2]*Vpk[13][13][2])+((Vpk[6][13][0]*
          Vpk[13][13][0])+(Vpk[6][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[6][13][2])+((IkWpk[13][13][0]*Wpk[6][13][0])+(IkWpk[13][13][1]*
          Wpk[6][13][1]))))+((mk[5]*((Vpk[6][14][2]*Vpk[13][14][2])+((
          Vpk[6][14][0]*Vpk[13][14][0])+(Vpk[6][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[6][14][2])+((IkWpk[13][14][0]*Wpk[6][14][0])+(
          IkWpk[13][14][1]*Wpk[6][14][1])))));
        mm[6][14] = ((mk[5]*((Vpk[6][14][2]*Vpk[14][14][2])+((Vpk[6][14][0]*
          Vpk[14][14][0])+(Vpk[6][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[6][14][2])+((IkWpk[14][14][0]*Wpk[6][14][0])+(IkWpk[14][14][1]*
          Wpk[6][14][1]))));
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
        temp[0] = (((mk[1]*((Vpk[7][8][2]*Vpk[7][8][2])+((Vpk[7][8][0]*
          Vpk[7][8][0])+(Vpk[7][8][1]*Vpk[7][8][1]))))+((IkWpk[7][8][2]*
          Wpk[7][8][2])+((IkWpk[7][8][0]*Wpk[7][8][0])+(IkWpk[7][8][1]*
          Wpk[7][8][1]))))+((mk[2]*((Vpk[7][11][2]*Vpk[7][11][2])+((
          Vpk[7][11][0]*Vpk[7][11][0])+(Vpk[7][11][1]*Vpk[7][11][1]))))+((
          IkWpk[7][11][2]*Wpk[7][11][2])+((IkWpk[7][11][0]*Wpk[7][11][0])+(
          IkWpk[7][11][1]*Wpk[7][11][1])))));
        temp[1] = (((mk[3]*((Vpk[7][12][2]*Vpk[7][12][2])+((Vpk[7][12][0]*
          Vpk[7][12][0])+(Vpk[7][12][1]*Vpk[7][12][1]))))+((IkWpk[7][12][2]*
          Wpk[7][12][2])+((IkWpk[7][12][0]*Wpk[7][12][0])+(IkWpk[7][12][1]*
          Wpk[7][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[7][13][2]*Vpk[7][13][2])+((Vpk[7][13][0]*
          Vpk[7][13][0])+(Vpk[7][13][1]*Vpk[7][13][1]))))+((IkWpk[7][13][2]*
          Wpk[7][13][2])+((IkWpk[7][13][0]*Wpk[7][13][0])+(IkWpk[7][13][1]*
          Wpk[7][13][1]))))+temp[1]);
        mm[7][7] = (((mk[5]*((Vpk[7][14][2]*Vpk[7][14][2])+((Vpk[7][14][0]*
          Vpk[7][14][0])+(Vpk[7][14][1]*Vpk[7][14][1]))))+((IkWpk[7][14][2]*
          Wpk[7][14][2])+((IkWpk[7][14][0]*Wpk[7][14][0])+(IkWpk[7][14][1]*
          Wpk[7][14][1]))))+temp[2]);
        temp[0] = (((mk[1]*((Vpk[7][8][2]*Vpk[8][8][2])+((Vpk[7][8][0]*
          Vpk[8][8][0])+(Vpk[7][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          Wpk[7][8][2])+((IkWpk[8][8][0]*Wpk[7][8][0])+(IkWpk[8][8][1]*
          Wpk[7][8][1]))))+((mk[2]*((Vpk[7][11][2]*Vpk[8][11][2])+((
          Vpk[7][11][0]*Vpk[8][11][0])+(Vpk[7][11][1]*Vpk[8][11][1]))))+((
          IkWpk[8][11][2]*Wpk[7][11][2])+((IkWpk[8][11][0]*Wpk[7][11][0])+(
          IkWpk[8][11][1]*Wpk[7][11][1])))));
        temp[1] = (((mk[3]*((Vpk[7][12][2]*Vpk[8][12][2])+((Vpk[7][12][0]*
          Vpk[8][12][0])+(Vpk[7][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[7][12][2])+((IkWpk[8][12][0]*Wpk[7][12][0])+(IkWpk[8][12][1]*
          Wpk[7][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[7][13][2]*Vpk[8][13][2])+((Vpk[7][13][0]*
          Vpk[8][13][0])+(Vpk[7][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[7][13][2])+((IkWpk[8][13][0]*Wpk[7][13][0])+(IkWpk[8][13][1]*
          Wpk[7][13][1]))))+temp[1]);
        mm[7][8] = (((mk[5]*((Vpk[7][14][2]*Vpk[8][14][2])+((Vpk[7][14][0]*
          Vpk[8][14][0])+(Vpk[7][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[7][14][2])+((IkWpk[8][14][0]*Wpk[7][14][0])+(IkWpk[8][14][1]*
          Wpk[7][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[7][13][2]*Vpk[9][13][2])+((Vpk[7][13][0]*
          Vpk[9][13][0])+(Vpk[7][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[7][11][2]*Vpk[9][11][2])+((Vpk[7][11][0]*Vpk[9][11][0])+(
          Vpk[7][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[7][12][2]*Vpk[9][12][2])+
          ((Vpk[7][12][0]*Vpk[9][12][0])+(Vpk[7][12][1]*Vpk[9][12][1]))))));
        mm[7][9] = ((mk[5]*((Vpk[7][14][2]*Vpk[9][14][2])+((Vpk[7][14][0]*
          Vpk[9][14][0])+(Vpk[7][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[7][13][2]*Vpk[10][13][2])+((Vpk[7][13][0]*
          Vpk[10][13][0])+(Vpk[7][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[7][11][2]*Vpk[10][11][2])+((Vpk[7][11][0]*Vpk[10][11][0])+(
          Vpk[7][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[7][12][2]*Vpk[10][12][2]
          )+((Vpk[7][12][0]*Vpk[10][12][0])+(Vpk[7][12][1]*Vpk[10][12][1]))))));
        mm[7][10] = ((mk[5]*((Vpk[7][14][2]*Vpk[10][14][2])+((Vpk[7][14][0]*
          Vpk[10][14][0])+(Vpk[7][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[7][11][2]*Vpk[11][11][2])+((Vpk[7][11][0]*
          Vpk[11][11][0])+(Vpk[7][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[7][11][2])+((IkWpk[11][11][0]*Wpk[7][11][0])+(IkWpk[11][11][1]*
          Wpk[7][11][1]))))+((mk[3]*((Vpk[7][12][2]*Vpk[11][12][2])+((
          Vpk[7][12][0]*Vpk[11][12][0])+(Vpk[7][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[7][12][2])+((IkWpk[11][12][0]*Wpk[7][12][0])+(
          IkWpk[11][12][1]*Wpk[7][12][1])))));
        temp[1] = (((mk[4]*((Vpk[7][13][2]*Vpk[11][13][2])+((Vpk[7][13][0]*
          Vpk[11][13][0])+(Vpk[7][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[7][13][2])+((IkWpk[11][13][0]*Wpk[7][13][0])+(IkWpk[11][13][1]*
          Wpk[7][13][1]))))+temp[0]);
        mm[7][11] = (((mk[5]*((Vpk[7][14][2]*Vpk[11][14][2])+((Vpk[7][14][0]*
          Vpk[11][14][0])+(Vpk[7][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[7][14][2])+((IkWpk[11][14][0]*Wpk[7][14][0])+(IkWpk[11][14][1]*
          Wpk[7][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[7][12][2]*Vpk[12][12][2])+((Vpk[7][12][0]*
          Vpk[12][12][0])+(Vpk[7][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[7][12][2])+((IkWpk[12][12][0]*Wpk[7][12][0])+(IkWpk[12][12][1]*
          Wpk[7][12][1]))))+((mk[4]*((Vpk[7][13][2]*Vpk[12][13][2])+((
          Vpk[7][13][0]*Vpk[12][13][0])+(Vpk[7][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[7][13][2])+((IkWpk[12][13][0]*Wpk[7][13][0])+(
          IkWpk[12][13][1]*Wpk[7][13][1])))));
        mm[7][12] = (((mk[5]*((Vpk[7][14][2]*Vpk[12][14][2])+((Vpk[7][14][0]*
          Vpk[12][14][0])+(Vpk[7][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[7][14][2])+((IkWpk[12][14][0]*Wpk[7][14][0])+(IkWpk[12][14][1]*
          Wpk[7][14][1]))))+temp[0]);
        mm[7][13] = (((mk[4]*((Vpk[7][13][2]*Vpk[13][13][2])+((Vpk[7][13][0]*
          Vpk[13][13][0])+(Vpk[7][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[7][13][2])+((IkWpk[13][13][0]*Wpk[7][13][0])+(IkWpk[13][13][1]*
          Wpk[7][13][1]))))+((mk[5]*((Vpk[7][14][2]*Vpk[13][14][2])+((
          Vpk[7][14][0]*Vpk[13][14][0])+(Vpk[7][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[7][14][2])+((IkWpk[13][14][0]*Wpk[7][14][0])+(
          IkWpk[13][14][1]*Wpk[7][14][1])))));
        mm[7][14] = ((mk[5]*((Vpk[7][14][2]*Vpk[14][14][2])+((Vpk[7][14][0]*
          Vpk[14][14][0])+(Vpk[7][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[7][14][2])+((IkWpk[14][14][0]*Wpk[7][14][0])+(IkWpk[14][14][1]*
          Wpk[7][14][1]))));
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
        temp[0] = (((mk[1]*((Vpk[8][8][2]*Vpk[8][8][2])+((Vpk[8][8][0]*
          Vpk[8][8][0])+(Vpk[8][8][1]*Vpk[8][8][1]))))+((IkWpk[8][8][2]*
          pin[8][2])+((IkWpk[8][8][0]*pin[8][0])+(IkWpk[8][8][1]*pin[8][1]))))+(
          (mk[2]*((Vpk[8][11][2]*Vpk[8][11][2])+((Vpk[8][11][0]*Vpk[8][11][0])+(
          Vpk[8][11][1]*Vpk[8][11][1]))))+((IkWpk[8][11][2]*Wpk[8][11][2])+((
          IkWpk[8][11][0]*Wpk[8][11][0])+(IkWpk[8][11][1]*Wpk[8][11][1])))));
        temp[1] = (((mk[3]*((Vpk[8][12][2]*Vpk[8][12][2])+((Vpk[8][12][0]*
          Vpk[8][12][0])+(Vpk[8][12][1]*Vpk[8][12][1]))))+((IkWpk[8][12][2]*
          Wpk[8][12][2])+((IkWpk[8][12][0]*Wpk[8][12][0])+(IkWpk[8][12][1]*
          Wpk[8][12][1]))))+temp[0]);
        temp[2] = (((mk[4]*((Vpk[8][13][2]*Vpk[8][13][2])+((Vpk[8][13][0]*
          Vpk[8][13][0])+(Vpk[8][13][1]*Vpk[8][13][1]))))+((IkWpk[8][13][2]*
          Wpk[8][13][2])+((IkWpk[8][13][0]*Wpk[8][13][0])+(IkWpk[8][13][1]*
          Wpk[8][13][1]))))+temp[1]);
        mm[8][8] = (((mk[5]*((Vpk[8][14][2]*Vpk[8][14][2])+((Vpk[8][14][0]*
          Vpk[8][14][0])+(Vpk[8][14][1]*Vpk[8][14][1]))))+((IkWpk[8][14][2]*
          Wpk[8][14][2])+((IkWpk[8][14][0]*Wpk[8][14][0])+(IkWpk[8][14][1]*
          Wpk[8][14][1]))))+temp[2]);
        temp[0] = ((mk[4]*((Vpk[8][13][2]*Vpk[9][13][2])+((Vpk[8][13][0]*
          Vpk[9][13][0])+(Vpk[8][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[8][11][2]*Vpk[9][11][2])+((Vpk[8][11][0]*Vpk[9][11][0])+(
          Vpk[8][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[8][12][2]*Vpk[9][12][2])+
          ((Vpk[8][12][0]*Vpk[9][12][0])+(Vpk[8][12][1]*Vpk[9][12][1]))))));
        mm[8][9] = ((mk[5]*((Vpk[8][14][2]*Vpk[9][14][2])+((Vpk[8][14][0]*
          Vpk[9][14][0])+(Vpk[8][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[8][13][2]*Vpk[10][13][2])+((Vpk[8][13][0]*
          Vpk[10][13][0])+(Vpk[8][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[8][11][2]*Vpk[10][11][2])+((Vpk[8][11][0]*Vpk[10][11][0])+(
          Vpk[8][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[8][12][2]*Vpk[10][12][2]
          )+((Vpk[8][12][0]*Vpk[10][12][0])+(Vpk[8][12][1]*Vpk[10][12][1]))))));
        mm[8][10] = ((mk[5]*((Vpk[8][14][2]*Vpk[10][14][2])+((Vpk[8][14][0]*
          Vpk[10][14][0])+(Vpk[8][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = (((mk[2]*((Vpk[8][11][2]*Vpk[11][11][2])+((Vpk[8][11][0]*
          Vpk[11][11][0])+(Vpk[8][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          Wpk[8][11][2])+((IkWpk[11][11][0]*Wpk[8][11][0])+(IkWpk[11][11][1]*
          Wpk[8][11][1]))))+((mk[3]*((Vpk[8][12][2]*Vpk[11][12][2])+((
          Vpk[8][12][0]*Vpk[11][12][0])+(Vpk[8][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[8][12][2])+((IkWpk[11][12][0]*Wpk[8][12][0])+(
          IkWpk[11][12][1]*Wpk[8][12][1])))));
        temp[1] = (((mk[4]*((Vpk[8][13][2]*Vpk[11][13][2])+((Vpk[8][13][0]*
          Vpk[11][13][0])+(Vpk[8][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[8][13][2])+((IkWpk[11][13][0]*Wpk[8][13][0])+(IkWpk[11][13][1]*
          Wpk[8][13][1]))))+temp[0]);
        mm[8][11] = (((mk[5]*((Vpk[8][14][2]*Vpk[11][14][2])+((Vpk[8][14][0]*
          Vpk[11][14][0])+(Vpk[8][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[8][14][2])+((IkWpk[11][14][0]*Wpk[8][14][0])+(IkWpk[11][14][1]*
          Wpk[8][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[8][12][2]*Vpk[12][12][2])+((Vpk[8][12][0]*
          Vpk[12][12][0])+(Vpk[8][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[8][12][2])+((IkWpk[12][12][0]*Wpk[8][12][0])+(IkWpk[12][12][1]*
          Wpk[8][12][1]))))+((mk[4]*((Vpk[8][13][2]*Vpk[12][13][2])+((
          Vpk[8][13][0]*Vpk[12][13][0])+(Vpk[8][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[8][13][2])+((IkWpk[12][13][0]*Wpk[8][13][0])+(
          IkWpk[12][13][1]*Wpk[8][13][1])))));
        mm[8][12] = (((mk[5]*((Vpk[8][14][2]*Vpk[12][14][2])+((Vpk[8][14][0]*
          Vpk[12][14][0])+(Vpk[8][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[8][14][2])+((IkWpk[12][14][0]*Wpk[8][14][0])+(IkWpk[12][14][1]*
          Wpk[8][14][1]))))+temp[0]);
        mm[8][13] = (((mk[4]*((Vpk[8][13][2]*Vpk[13][13][2])+((Vpk[8][13][0]*
          Vpk[13][13][0])+(Vpk[8][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[8][13][2])+((IkWpk[13][13][0]*Wpk[8][13][0])+(IkWpk[13][13][1]*
          Wpk[8][13][1]))))+((mk[5]*((Vpk[8][14][2]*Vpk[13][14][2])+((
          Vpk[8][14][0]*Vpk[13][14][0])+(Vpk[8][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[8][14][2])+((IkWpk[13][14][0]*Wpk[8][14][0])+(
          IkWpk[13][14][1]*Wpk[8][14][1])))));
        mm[8][14] = ((mk[5]*((Vpk[8][14][2]*Vpk[14][14][2])+((Vpk[8][14][0]*
          Vpk[14][14][0])+(Vpk[8][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[8][14][2])+((IkWpk[14][14][0]*Wpk[8][14][0])+(IkWpk[14][14][1]*
          Wpk[8][14][1]))));
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
        temp[0] = ((mk[4]*((Vpk[9][13][2]*Vpk[9][13][2])+((Vpk[9][13][0]*
          Vpk[9][13][0])+(Vpk[9][13][1]*Vpk[9][13][1]))))+((mk[2]*((
          Vpk[9][11][2]*Vpk[9][11][2])+((Vpk[9][11][0]*Vpk[9][11][0])+(
          Vpk[9][11][1]*Vpk[9][11][1]))))+(mk[3]*((Vpk[9][12][2]*Vpk[9][12][2])+
          ((Vpk[9][12][0]*Vpk[9][12][0])+(Vpk[9][12][1]*Vpk[9][12][1]))))));
        mm[9][9] = ((mk[5]*((Vpk[9][14][2]*Vpk[9][14][2])+((Vpk[9][14][0]*
          Vpk[9][14][0])+(Vpk[9][14][1]*Vpk[9][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[9][13][2]*Vpk[10][13][2])+((Vpk[9][13][0]*
          Vpk[10][13][0])+(Vpk[9][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[9][11][2]*Vpk[10][11][2])+((Vpk[9][11][0]*Vpk[10][11][0])+(
          Vpk[9][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[9][12][2]*Vpk[10][12][2]
          )+((Vpk[9][12][0]*Vpk[10][12][0])+(Vpk[9][12][1]*Vpk[10][12][1]))))));
        mm[9][10] = ((mk[5]*((Vpk[9][14][2]*Vpk[10][14][2])+((Vpk[9][14][0]*
          Vpk[10][14][0])+(Vpk[9][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[9][13][2]*Vpk[11][13][2])+((Vpk[9][13][0]*
          Vpk[11][13][0])+(Vpk[9][13][1]*Vpk[11][13][1]))))+((mk[2]*((
          Vpk[9][11][2]*Vpk[11][11][2])+((Vpk[9][11][0]*Vpk[11][11][0])+(
          Vpk[9][11][1]*Vpk[11][11][1]))))+(mk[3]*((Vpk[9][12][2]*Vpk[11][12][2]
          )+((Vpk[9][12][0]*Vpk[11][12][0])+(Vpk[9][12][1]*Vpk[11][12][1]))))));
        mm[9][11] = ((mk[5]*((Vpk[9][14][2]*Vpk[11][14][2])+((Vpk[9][14][0]*
          Vpk[11][14][0])+(Vpk[9][14][1]*Vpk[11][14][1]))))+temp[0]);
        mm[9][12] = ((mk[5]*((Vpk[9][14][2]*Vpk[12][14][2])+((Vpk[9][14][0]*
          Vpk[12][14][0])+(Vpk[9][14][1]*Vpk[12][14][1]))))+((mk[3]*((
          Vpk[9][12][2]*Vpk[12][12][2])+((Vpk[9][12][0]*Vpk[12][12][0])+(
          Vpk[9][12][1]*Vpk[12][12][1]))))+(mk[4]*((Vpk[9][13][2]*Vpk[12][13][2]
          )+((Vpk[9][13][0]*Vpk[12][13][0])+(Vpk[9][13][1]*Vpk[12][13][1]))))));
        mm[9][13] = ((mk[4]*((Vpk[9][13][2]*Vpk[13][13][2])+((Vpk[9][13][0]*
          Vpk[13][13][0])+(Vpk[9][13][1]*Vpk[13][13][1]))))+(mk[5]*((
          Vpk[9][14][2]*Vpk[13][14][2])+((Vpk[9][14][0]*Vpk[13][14][0])+(
          Vpk[9][14][1]*Vpk[13][14][1])))));
        mm[9][14] = (mk[5]*((Vpk[9][14][2]*Vpk[14][14][2])+((Vpk[9][14][0]*
          Vpk[14][14][0])+(Vpk[9][14][1]*Vpk[14][14][1]))));
        mm[9][15] = 0.;
        mm[9][16] = 0.;
        mm[9][17] = 0.;
        mm[9][18] = 0.;
        mm[9][19] = 0.;
        mm[9][20] = 0.;
        mm[9][21] = 0.;
        mm[9][22] = 0.;
        mm[9][23] = 0.;
        mm[9][24] = 0.;
        mm[9][25] = 0.;
        mm[9][26] = 0.;
        temp[0] = ((mk[4]*((Vpk[10][13][2]*Vpk[10][13][2])+((Vpk[10][13][0]*
          Vpk[10][13][0])+(Vpk[10][13][1]*Vpk[10][13][1]))))+((mk[2]*((
          Vpk[10][11][2]*Vpk[10][11][2])+((Vpk[10][11][0]*Vpk[10][11][0])+(
          Vpk[10][11][1]*Vpk[10][11][1]))))+(mk[3]*((Vpk[10][12][2]*
          Vpk[10][12][2])+((Vpk[10][12][0]*Vpk[10][12][0])+(Vpk[10][12][1]*
          Vpk[10][12][1]))))));
        mm[10][10] = ((mk[5]*((Vpk[10][14][2]*Vpk[10][14][2])+((Vpk[10][14][0]*
          Vpk[10][14][0])+(Vpk[10][14][1]*Vpk[10][14][1]))))+temp[0]);
        temp[0] = ((mk[4]*((Vpk[10][13][2]*Vpk[11][13][2])+((Vpk[10][13][0]*
          Vpk[11][13][0])+(Vpk[10][13][1]*Vpk[11][13][1]))))+((mk[2]*((
          Vpk[10][11][2]*Vpk[11][11][2])+((Vpk[10][11][0]*Vpk[11][11][0])+(
          Vpk[10][11][1]*Vpk[11][11][1]))))+(mk[3]*((Vpk[10][12][2]*
          Vpk[11][12][2])+((Vpk[10][12][0]*Vpk[11][12][0])+(Vpk[10][12][1]*
          Vpk[11][12][1]))))));
        mm[10][11] = ((mk[5]*((Vpk[10][14][2]*Vpk[11][14][2])+((Vpk[10][14][0]*
          Vpk[11][14][0])+(Vpk[10][14][1]*Vpk[11][14][1]))))+temp[0]);
        mm[10][12] = ((mk[5]*((Vpk[10][14][2]*Vpk[12][14][2])+((Vpk[10][14][0]*
          Vpk[12][14][0])+(Vpk[10][14][1]*Vpk[12][14][1]))))+((mk[3]*((
          Vpk[10][12][2]*Vpk[12][12][2])+((Vpk[10][12][0]*Vpk[12][12][0])+(
          Vpk[10][12][1]*Vpk[12][12][1]))))+(mk[4]*((Vpk[10][13][2]*
          Vpk[12][13][2])+((Vpk[10][13][0]*Vpk[12][13][0])+(Vpk[10][13][1]*
          Vpk[12][13][1]))))));
        mm[10][13] = ((mk[4]*((Vpk[10][13][2]*Vpk[13][13][2])+((Vpk[10][13][0]*
          Vpk[13][13][0])+(Vpk[10][13][1]*Vpk[13][13][1]))))+(mk[5]*((
          Vpk[10][14][2]*Vpk[13][14][2])+((Vpk[10][14][0]*Vpk[13][14][0])+(
          Vpk[10][14][1]*Vpk[13][14][1])))));
        mm[10][14] = (mk[5]*((Vpk[10][14][2]*Vpk[14][14][2])+((Vpk[10][14][0]*
          Vpk[14][14][0])+(Vpk[10][14][1]*Vpk[14][14][1]))));
        mm[10][15] = 0.;
        mm[10][16] = 0.;
        mm[10][17] = 0.;
        mm[10][18] = 0.;
        mm[10][19] = 0.;
        mm[10][20] = 0.;
        mm[10][21] = 0.;
        mm[10][22] = 0.;
        mm[10][23] = 0.;
        mm[10][24] = 0.;
        mm[10][25] = 0.;
        mm[10][26] = 0.;
        temp[0] = (((mk[2]*((Vpk[11][11][2]*Vpk[11][11][2])+((Vpk[11][11][0]*
          Vpk[11][11][0])+(Vpk[11][11][1]*Vpk[11][11][1]))))+((IkWpk[11][11][2]*
          pin[11][2])+((IkWpk[11][11][0]*pin[11][0])+(IkWpk[11][11][1]*
          pin[11][1]))))+((mk[3]*((Vpk[11][12][2]*Vpk[11][12][2])+((
          Vpk[11][12][0]*Vpk[11][12][0])+(Vpk[11][12][1]*Vpk[11][12][1]))))+((
          IkWpk[11][12][2]*Wpk[11][12][2])+((IkWpk[11][12][0]*Wpk[11][12][0])+(
          IkWpk[11][12][1]*Wpk[11][12][1])))));
        temp[1] = (((mk[4]*((Vpk[11][13][2]*Vpk[11][13][2])+((Vpk[11][13][0]*
          Vpk[11][13][0])+(Vpk[11][13][1]*Vpk[11][13][1]))))+((IkWpk[11][13][2]*
          Wpk[11][13][2])+((IkWpk[11][13][0]*Wpk[11][13][0])+(IkWpk[11][13][1]*
          Wpk[11][13][1]))))+temp[0]);
        mm[11][11] = (((mk[5]*((Vpk[11][14][2]*Vpk[11][14][2])+((Vpk[11][14][0]*
          Vpk[11][14][0])+(Vpk[11][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][2]*
          Wpk[11][14][2])+((IkWpk[11][14][0]*Wpk[11][14][0])+(IkWpk[11][14][1]*
          Wpk[11][14][1]))))+temp[1]);
        temp[0] = (((mk[3]*((Vpk[11][12][2]*Vpk[12][12][2])+((Vpk[11][12][0]*
          Vpk[12][12][0])+(Vpk[11][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          Wpk[11][12][2])+((IkWpk[12][12][0]*Wpk[11][12][0])+(IkWpk[12][12][1]*
          Wpk[11][12][1]))))+((mk[4]*((Vpk[11][13][2]*Vpk[12][13][2])+((
          Vpk[11][13][0]*Vpk[12][13][0])+(Vpk[11][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[11][13][2])+((IkWpk[12][13][0]*Wpk[11][13][0])+(
          IkWpk[12][13][1]*Wpk[11][13][1])))));
        mm[11][12] = (((mk[5]*((Vpk[11][14][2]*Vpk[12][14][2])+((Vpk[11][14][0]*
          Vpk[12][14][0])+(Vpk[11][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[11][14][2])+((IkWpk[12][14][0]*Wpk[11][14][0])+(IkWpk[12][14][1]*
          Wpk[11][14][1]))))+temp[0]);
        mm[11][13] = (((mk[4]*((Vpk[11][13][2]*Vpk[13][13][2])+((Vpk[11][13][0]*
          Vpk[13][13][0])+(Vpk[11][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[11][13][2])+((IkWpk[13][13][0]*Wpk[11][13][0])+(IkWpk[13][13][1]*
          Wpk[11][13][1]))))+((mk[5]*((Vpk[11][14][2]*Vpk[13][14][2])+((
          Vpk[11][14][0]*Vpk[13][14][0])+(Vpk[11][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[11][14][2])+((IkWpk[13][14][0]*Wpk[11][14][0])+(
          IkWpk[13][14][1]*Wpk[11][14][1])))));
        mm[11][14] = ((mk[5]*((Vpk[11][14][2]*Vpk[14][14][2])+((Vpk[11][14][0]*
          Vpk[14][14][0])+(Vpk[11][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[11][14][2])+((IkWpk[14][14][0]*Wpk[11][14][0])+(IkWpk[14][14][1]*
          Wpk[11][14][1]))));
        mm[11][15] = 0.;
        mm[11][16] = 0.;
        mm[11][17] = 0.;
        mm[11][18] = 0.;
        mm[11][19] = 0.;
        mm[11][20] = 0.;
        mm[11][21] = 0.;
        mm[11][22] = 0.;
        mm[11][23] = 0.;
        mm[11][24] = 0.;
        mm[11][25] = 0.;
        mm[11][26] = 0.;
        temp[0] = (((mk[3]*((Vpk[12][12][2]*Vpk[12][12][2])+((Vpk[12][12][0]*
          Vpk[12][12][0])+(Vpk[12][12][1]*Vpk[12][12][1]))))+((IkWpk[12][12][2]*
          pin[12][2])+((IkWpk[12][12][0]*pin[12][0])+(IkWpk[12][12][1]*
          pin[12][1]))))+((mk[4]*((Vpk[12][13][2]*Vpk[12][13][2])+((
          Vpk[12][13][0]*Vpk[12][13][0])+(Vpk[12][13][1]*Vpk[12][13][1]))))+((
          IkWpk[12][13][2]*Wpk[12][13][2])+((IkWpk[12][13][0]*Wpk[12][13][0])+(
          IkWpk[12][13][1]*Wpk[12][13][1])))));
        mm[12][12] = (((mk[5]*((Vpk[12][14][2]*Vpk[12][14][2])+((Vpk[12][14][0]*
          Vpk[12][14][0])+(Vpk[12][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][2]*
          Wpk[12][14][2])+((IkWpk[12][14][0]*Wpk[12][14][0])+(IkWpk[12][14][1]*
          Wpk[12][14][1]))))+temp[0]);
        mm[12][13] = (((mk[4]*((Vpk[12][13][2]*Vpk[13][13][2])+((Vpk[12][13][0]*
          Vpk[13][13][0])+(Vpk[12][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          Wpk[12][13][2])+((IkWpk[13][13][0]*Wpk[12][13][0])+(IkWpk[13][13][1]*
          Wpk[12][13][1]))))+((mk[5]*((Vpk[12][14][2]*Vpk[13][14][2])+((
          Vpk[12][14][0]*Vpk[13][14][0])+(Vpk[12][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[12][14][2])+((IkWpk[13][14][0]*Wpk[12][14][0])+(
          IkWpk[13][14][1]*Wpk[12][14][1])))));
        mm[12][14] = ((mk[5]*((Vpk[12][14][2]*Vpk[14][14][2])+((Vpk[12][14][0]*
          Vpk[14][14][0])+(Vpk[12][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[12][14][2])+((IkWpk[14][14][0]*Wpk[12][14][0])+(IkWpk[14][14][1]*
          Wpk[12][14][1]))));
        mm[12][15] = 0.;
        mm[12][16] = 0.;
        mm[12][17] = 0.;
        mm[12][18] = 0.;
        mm[12][19] = 0.;
        mm[12][20] = 0.;
        mm[12][21] = 0.;
        mm[12][22] = 0.;
        mm[12][23] = 0.;
        mm[12][24] = 0.;
        mm[12][25] = 0.;
        mm[12][26] = 0.;
        mm[13][13] = (((mk[4]*((Vpk[13][13][2]*Vpk[13][13][2])+((Vpk[13][13][0]*
          Vpk[13][13][0])+(Vpk[13][13][1]*Vpk[13][13][1]))))+((IkWpk[13][13][2]*
          pin[13][2])+((IkWpk[13][13][0]*pin[13][0])+(IkWpk[13][13][1]*
          pin[13][1]))))+((mk[5]*((Vpk[13][14][2]*Vpk[13][14][2])+((
          Vpk[13][14][0]*Vpk[13][14][0])+(Vpk[13][14][1]*Vpk[13][14][1]))))+((
          IkWpk[13][14][2]*Wpk[13][14][2])+((IkWpk[13][14][0]*Wpk[13][14][0])+(
          IkWpk[13][14][1]*Wpk[13][14][1])))));
        mm[13][14] = ((mk[5]*((Vpk[13][14][2]*Vpk[14][14][2])+((Vpk[13][14][0]*
          Vpk[14][14][0])+(Vpk[13][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          Wpk[13][14][2])+((IkWpk[14][14][0]*Wpk[13][14][0])+(IkWpk[14][14][1]*
          Wpk[13][14][1]))));
        mm[13][15] = 0.;
        mm[13][16] = 0.;
        mm[13][17] = 0.;
        mm[13][18] = 0.;
        mm[13][19] = 0.;
        mm[13][20] = 0.;
        mm[13][21] = 0.;
        mm[13][22] = 0.;
        mm[13][23] = 0.;
        mm[13][24] = 0.;
        mm[13][25] = 0.;
        mm[13][26] = 0.;
        mm[14][14] = ((mk[5]*((Vpk[14][14][2]*Vpk[14][14][2])+((Vpk[14][14][0]*
          Vpk[14][14][0])+(Vpk[14][14][1]*Vpk[14][14][1]))))+((IkWpk[14][14][2]*
          pin[14][2])+((IkWpk[14][14][0]*pin[14][0])+(IkWpk[14][14][1]*
          pin[14][1]))));
        mm[14][15] = 0.;
        mm[14][16] = 0.;
        mm[14][17] = 0.;
        mm[14][18] = 0.;
        mm[14][19] = 0.;
        mm[14][20] = 0.;
        mm[14][21] = 0.;
        mm[14][22] = 0.;
        mm[14][23] = 0.;
        mm[14][24] = 0.;
        mm[14][25] = 0.;
        mm[14][26] = 0.;
        temp[0] = (((mk[6]*((Vpk[15][17][2]*Vpk[15][17][2])+((Vpk[15][17][0]*
          Vpk[15][17][0])+(Vpk[15][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[15][17][2])+((IkWpk[15][17][0]*Wpk[15][17][0])+(IkWpk[15][17][1]*
          Wpk[15][17][1]))))+((mk[7]*((Vpk[15][20][2]*Vpk[15][20][2])+((
          Vpk[15][20][0]*Vpk[15][20][0])+(Vpk[15][20][1]*Vpk[15][20][1]))))+((
          IkWpk[15][20][2]*Wpk[15][20][2])+((IkWpk[15][20][0]*Wpk[15][20][0])+(
          IkWpk[15][20][1]*Wpk[15][20][1])))));
        temp[1] = (((mk[8]*((Vpk[15][21][2]*Vpk[15][21][2])+((Vpk[15][21][0]*
          Vpk[15][21][0])+(Vpk[15][21][1]*Vpk[15][21][1]))))+((IkWpk[15][21][2]*
          Wpk[15][21][2])+((IkWpk[15][21][0]*Wpk[15][21][0])+(IkWpk[15][21][1]*
          Wpk[15][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[15][22][2]*Vpk[15][22][2])+((Vpk[15][22][0]*
          Vpk[15][22][0])+(Vpk[15][22][1]*Vpk[15][22][1]))))+((IkWpk[15][22][2]*
          Wpk[15][22][2])+((IkWpk[15][22][0]*Wpk[15][22][0])+(IkWpk[15][22][1]*
          Wpk[15][22][1]))))+temp[1]);
        mm[15][15] = (((mk[10]*((Vpk[15][23][2]*Vpk[15][23][2])+((Vpk[15][23][0]
          *Vpk[15][23][0])+(Vpk[15][23][1]*Vpk[15][23][1]))))+((IkWpk[15][23][2]
          *Wpk[15][23][2])+((IkWpk[15][23][0]*Wpk[15][23][0])+(IkWpk[15][23][1]*
          Wpk[15][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[15][17][2]*Vpk[16][17][2])+((Vpk[15][17][0]*
          Vpk[16][17][0])+(Vpk[15][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][2]*
          Wpk[15][17][2])+((IkWpk[16][17][0]*Wpk[15][17][0])+(IkWpk[16][17][1]*
          Wpk[15][17][1]))))+((mk[7]*((Vpk[15][20][2]*Vpk[16][20][2])+((
          Vpk[15][20][0]*Vpk[16][20][0])+(Vpk[15][20][1]*Vpk[16][20][1]))))+((
          IkWpk[16][20][2]*Wpk[15][20][2])+((IkWpk[16][20][0]*Wpk[15][20][0])+(
          IkWpk[16][20][1]*Wpk[15][20][1])))));
        temp[1] = (((mk[8]*((Vpk[15][21][2]*Vpk[16][21][2])+((Vpk[15][21][0]*
          Vpk[16][21][0])+(Vpk[15][21][1]*Vpk[16][21][1]))))+((IkWpk[16][21][2]*
          Wpk[15][21][2])+((IkWpk[16][21][0]*Wpk[15][21][0])+(IkWpk[16][21][1]*
          Wpk[15][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[15][22][2]*Vpk[16][22][2])+((Vpk[15][22][0]*
          Vpk[16][22][0])+(Vpk[15][22][1]*Vpk[16][22][1]))))+((IkWpk[16][22][2]*
          Wpk[15][22][2])+((IkWpk[16][22][0]*Wpk[15][22][0])+(IkWpk[16][22][1]*
          Wpk[15][22][1]))))+temp[1]);
        mm[15][16] = (((mk[10]*((Vpk[15][23][2]*Vpk[16][23][2])+((Vpk[15][23][0]
          *Vpk[16][23][0])+(Vpk[15][23][1]*Vpk[16][23][1]))))+((IkWpk[16][23][2]
          *Wpk[15][23][2])+((IkWpk[16][23][0]*Wpk[15][23][0])+(IkWpk[16][23][1]*
          Wpk[15][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[15][17][2]*Vpk[17][17][2])+((Vpk[15][17][0]*
          Vpk[17][17][0])+(Vpk[15][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          Wpk[15][17][2])+((IkWpk[17][17][0]*Wpk[15][17][0])+(IkWpk[17][17][1]*
          Wpk[15][17][1]))))+((mk[7]*((Vpk[15][20][2]*Vpk[17][20][2])+((
          Vpk[15][20][0]*Vpk[17][20][0])+(Vpk[15][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[15][20][2])+((IkWpk[17][20][0]*Wpk[15][20][0])+(
          IkWpk[17][20][1]*Wpk[15][20][1])))));
        temp[1] = (((mk[8]*((Vpk[15][21][2]*Vpk[17][21][2])+((Vpk[15][21][0]*
          Vpk[17][21][0])+(Vpk[15][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[15][21][2])+((IkWpk[17][21][0]*Wpk[15][21][0])+(IkWpk[17][21][1]*
          Wpk[15][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[15][22][2]*Vpk[17][22][2])+((Vpk[15][22][0]*
          Vpk[17][22][0])+(Vpk[15][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[15][22][2])+((IkWpk[17][22][0]*Wpk[15][22][0])+(IkWpk[17][22][1]*
          Wpk[15][22][1]))))+temp[1]);
        mm[15][17] = (((mk[10]*((Vpk[15][23][2]*Vpk[17][23][2])+((Vpk[15][23][0]
          *Vpk[17][23][0])+(Vpk[15][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]
          *Wpk[15][23][2])+((IkWpk[17][23][0]*Wpk[15][23][0])+(IkWpk[17][23][1]*
          Wpk[15][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[15][22][2]*Vpk[18][22][2])+((Vpk[15][22][0]*
          Vpk[18][22][0])+(Vpk[15][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[15][20][2]*Vpk[18][20][2])+((Vpk[15][20][0]*Vpk[18][20][0])+(
          Vpk[15][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[15][21][2]*
          Vpk[18][21][2])+((Vpk[15][21][0]*Vpk[18][21][0])+(Vpk[15][21][1]*
          Vpk[18][21][1]))))));
        mm[15][18] = ((mk[10]*((Vpk[15][23][2]*Vpk[18][23][2])+((Vpk[15][23][0]*
          Vpk[18][23][0])+(Vpk[15][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[15][22][2]*Vpk[19][22][2])+((Vpk[15][22][0]*
          Vpk[19][22][0])+(Vpk[15][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[15][20][2]*Vpk[19][20][2])+((Vpk[15][20][0]*Vpk[19][20][0])+(
          Vpk[15][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[15][21][2]*
          Vpk[19][21][2])+((Vpk[15][21][0]*Vpk[19][21][0])+(Vpk[15][21][1]*
          Vpk[19][21][1]))))));
        mm[15][19] = ((mk[10]*((Vpk[15][23][2]*Vpk[19][23][2])+((Vpk[15][23][0]*
          Vpk[19][23][0])+(Vpk[15][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[15][20][2]*Vpk[20][20][2])+((Vpk[15][20][0]*
          Vpk[20][20][0])+(Vpk[15][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[15][20][2])+((IkWpk[20][20][0]*Wpk[15][20][0])+(IkWpk[20][20][1]*
          Wpk[15][20][1]))))+((mk[8]*((Vpk[15][21][2]*Vpk[20][21][2])+((
          Vpk[15][21][0]*Vpk[20][21][0])+(Vpk[15][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[15][21][2])+((IkWpk[20][21][0]*Wpk[15][21][0])+(
          IkWpk[20][21][1]*Wpk[15][21][1])))));
        temp[1] = (((mk[9]*((Vpk[15][22][2]*Vpk[20][22][2])+((Vpk[15][22][0]*
          Vpk[20][22][0])+(Vpk[15][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[15][22][2])+((IkWpk[20][22][0]*Wpk[15][22][0])+(IkWpk[20][22][1]*
          Wpk[15][22][1]))))+temp[0]);
        mm[15][20] = (((mk[10]*((Vpk[15][23][2]*Vpk[20][23][2])+((Vpk[15][23][0]
          *Vpk[20][23][0])+(Vpk[15][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]
          *Wpk[15][23][2])+((IkWpk[20][23][0]*Wpk[15][23][0])+(IkWpk[20][23][1]*
          Wpk[15][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[15][21][2]*Vpk[21][21][2])+((Vpk[15][21][0]*
          Vpk[21][21][0])+(Vpk[15][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[15][21][2])+((IkWpk[21][21][0]*Wpk[15][21][0])+(IkWpk[21][21][1]*
          Wpk[15][21][1]))))+((mk[9]*((Vpk[15][22][2]*Vpk[21][22][2])+((
          Vpk[15][22][0]*Vpk[21][22][0])+(Vpk[15][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[15][22][2])+((IkWpk[21][22][0]*Wpk[15][22][0])+(
          IkWpk[21][22][1]*Wpk[15][22][1])))));
        mm[15][21] = (((mk[10]*((Vpk[15][23][2]*Vpk[21][23][2])+((Vpk[15][23][0]
          *Vpk[21][23][0])+(Vpk[15][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]
          *Wpk[15][23][2])+((IkWpk[21][23][0]*Wpk[15][23][0])+(IkWpk[21][23][1]*
          Wpk[15][23][1]))))+temp[0]);
        mm[15][22] = (((mk[9]*((Vpk[15][22][2]*Vpk[22][22][2])+((Vpk[15][22][0]*
          Vpk[22][22][0])+(Vpk[15][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[15][22][2])+((IkWpk[22][22][0]*Wpk[15][22][0])+(IkWpk[22][22][1]*
          Wpk[15][22][1]))))+((mk[10]*((Vpk[15][23][2]*Vpk[22][23][2])+((
          Vpk[15][23][0]*Vpk[22][23][0])+(Vpk[15][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[15][23][2])+((IkWpk[22][23][0]*Wpk[15][23][0])+(
          IkWpk[22][23][1]*Wpk[15][23][1])))));
        mm[15][23] = ((mk[10]*((Vpk[15][23][2]*Vpk[23][23][2])+((Vpk[15][23][0]*
          Vpk[23][23][0])+(Vpk[15][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[15][23][2])+((IkWpk[23][23][0]*Wpk[15][23][0])+(IkWpk[23][23][1]*
          Wpk[15][23][1]))));
        mm[15][24] = 0.;
        mm[15][25] = 0.;
        mm[15][26] = 0.;
        temp[0] = (((mk[6]*((Vpk[16][17][2]*Vpk[16][17][2])+((Vpk[16][17][0]*
          Vpk[16][17][0])+(Vpk[16][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][2]*
          Wpk[16][17][2])+((IkWpk[16][17][0]*Wpk[16][17][0])+(IkWpk[16][17][1]*
          Wpk[16][17][1]))))+((mk[7]*((Vpk[16][20][2]*Vpk[16][20][2])+((
          Vpk[16][20][0]*Vpk[16][20][0])+(Vpk[16][20][1]*Vpk[16][20][1]))))+((
          IkWpk[16][20][2]*Wpk[16][20][2])+((IkWpk[16][20][0]*Wpk[16][20][0])+(
          IkWpk[16][20][1]*Wpk[16][20][1])))));
        temp[1] = (((mk[8]*((Vpk[16][21][2]*Vpk[16][21][2])+((Vpk[16][21][0]*
          Vpk[16][21][0])+(Vpk[16][21][1]*Vpk[16][21][1]))))+((IkWpk[16][21][2]*
          Wpk[16][21][2])+((IkWpk[16][21][0]*Wpk[16][21][0])+(IkWpk[16][21][1]*
          Wpk[16][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[16][22][2]*Vpk[16][22][2])+((Vpk[16][22][0]*
          Vpk[16][22][0])+(Vpk[16][22][1]*Vpk[16][22][1]))))+((IkWpk[16][22][2]*
          Wpk[16][22][2])+((IkWpk[16][22][0]*Wpk[16][22][0])+(IkWpk[16][22][1]*
          Wpk[16][22][1]))))+temp[1]);
        mm[16][16] = (((mk[10]*((Vpk[16][23][2]*Vpk[16][23][2])+((Vpk[16][23][0]
          *Vpk[16][23][0])+(Vpk[16][23][1]*Vpk[16][23][1]))))+((IkWpk[16][23][2]
          *Wpk[16][23][2])+((IkWpk[16][23][0]*Wpk[16][23][0])+(IkWpk[16][23][1]*
          Wpk[16][23][1]))))+temp[2]);
        temp[0] = (((mk[6]*((Vpk[16][17][2]*Vpk[17][17][2])+((Vpk[16][17][0]*
          Vpk[17][17][0])+(Vpk[16][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          Wpk[16][17][2])+((IkWpk[17][17][0]*Wpk[16][17][0])+(IkWpk[17][17][1]*
          Wpk[16][17][1]))))+((mk[7]*((Vpk[16][20][2]*Vpk[17][20][2])+((
          Vpk[16][20][0]*Vpk[17][20][0])+(Vpk[16][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[16][20][2])+((IkWpk[17][20][0]*Wpk[16][20][0])+(
          IkWpk[17][20][1]*Wpk[16][20][1])))));
        temp[1] = (((mk[8]*((Vpk[16][21][2]*Vpk[17][21][2])+((Vpk[16][21][0]*
          Vpk[17][21][0])+(Vpk[16][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[16][21][2])+((IkWpk[17][21][0]*Wpk[16][21][0])+(IkWpk[17][21][1]*
          Wpk[16][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[16][22][2]*Vpk[17][22][2])+((Vpk[16][22][0]*
          Vpk[17][22][0])+(Vpk[16][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[16][22][2])+((IkWpk[17][22][0]*Wpk[16][22][0])+(IkWpk[17][22][1]*
          Wpk[16][22][1]))))+temp[1]);
        mm[16][17] = (((mk[10]*((Vpk[16][23][2]*Vpk[17][23][2])+((Vpk[16][23][0]
          *Vpk[17][23][0])+(Vpk[16][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]
          *Wpk[16][23][2])+((IkWpk[17][23][0]*Wpk[16][23][0])+(IkWpk[17][23][1]*
          Wpk[16][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[16][22][2]*Vpk[18][22][2])+((Vpk[16][22][0]*
          Vpk[18][22][0])+(Vpk[16][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[16][20][2]*Vpk[18][20][2])+((Vpk[16][20][0]*Vpk[18][20][0])+(
          Vpk[16][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[16][21][2]*
          Vpk[18][21][2])+((Vpk[16][21][0]*Vpk[18][21][0])+(Vpk[16][21][1]*
          Vpk[18][21][1]))))));
        mm[16][18] = ((mk[10]*((Vpk[16][23][2]*Vpk[18][23][2])+((Vpk[16][23][0]*
          Vpk[18][23][0])+(Vpk[16][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[16][22][2]*Vpk[19][22][2])+((Vpk[16][22][0]*
          Vpk[19][22][0])+(Vpk[16][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[16][20][2]*Vpk[19][20][2])+((Vpk[16][20][0]*Vpk[19][20][0])+(
          Vpk[16][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[16][21][2]*
          Vpk[19][21][2])+((Vpk[16][21][0]*Vpk[19][21][0])+(Vpk[16][21][1]*
          Vpk[19][21][1]))))));
        mm[16][19] = ((mk[10]*((Vpk[16][23][2]*Vpk[19][23][2])+((Vpk[16][23][0]*
          Vpk[19][23][0])+(Vpk[16][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[16][20][2]*Vpk[20][20][2])+((Vpk[16][20][0]*
          Vpk[20][20][0])+(Vpk[16][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[16][20][2])+((IkWpk[20][20][0]*Wpk[16][20][0])+(IkWpk[20][20][1]*
          Wpk[16][20][1]))))+((mk[8]*((Vpk[16][21][2]*Vpk[20][21][2])+((
          Vpk[16][21][0]*Vpk[20][21][0])+(Vpk[16][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[16][21][2])+((IkWpk[20][21][0]*Wpk[16][21][0])+(
          IkWpk[20][21][1]*Wpk[16][21][1])))));
        temp[1] = (((mk[9]*((Vpk[16][22][2]*Vpk[20][22][2])+((Vpk[16][22][0]*
          Vpk[20][22][0])+(Vpk[16][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[16][22][2])+((IkWpk[20][22][0]*Wpk[16][22][0])+(IkWpk[20][22][1]*
          Wpk[16][22][1]))))+temp[0]);
        mm[16][20] = (((mk[10]*((Vpk[16][23][2]*Vpk[20][23][2])+((Vpk[16][23][0]
          *Vpk[20][23][0])+(Vpk[16][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]
          *Wpk[16][23][2])+((IkWpk[20][23][0]*Wpk[16][23][0])+(IkWpk[20][23][1]*
          Wpk[16][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[16][21][2]*Vpk[21][21][2])+((Vpk[16][21][0]*
          Vpk[21][21][0])+(Vpk[16][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[16][21][2])+((IkWpk[21][21][0]*Wpk[16][21][0])+(IkWpk[21][21][1]*
          Wpk[16][21][1]))))+((mk[9]*((Vpk[16][22][2]*Vpk[21][22][2])+((
          Vpk[16][22][0]*Vpk[21][22][0])+(Vpk[16][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[16][22][2])+((IkWpk[21][22][0]*Wpk[16][22][0])+(
          IkWpk[21][22][1]*Wpk[16][22][1])))));
        mm[16][21] = (((mk[10]*((Vpk[16][23][2]*Vpk[21][23][2])+((Vpk[16][23][0]
          *Vpk[21][23][0])+(Vpk[16][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]
          *Wpk[16][23][2])+((IkWpk[21][23][0]*Wpk[16][23][0])+(IkWpk[21][23][1]*
          Wpk[16][23][1]))))+temp[0]);
        mm[16][22] = (((mk[9]*((Vpk[16][22][2]*Vpk[22][22][2])+((Vpk[16][22][0]*
          Vpk[22][22][0])+(Vpk[16][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[16][22][2])+((IkWpk[22][22][0]*Wpk[16][22][0])+(IkWpk[22][22][1]*
          Wpk[16][22][1]))))+((mk[10]*((Vpk[16][23][2]*Vpk[22][23][2])+((
          Vpk[16][23][0]*Vpk[22][23][0])+(Vpk[16][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[16][23][2])+((IkWpk[22][23][0]*Wpk[16][23][0])+(
          IkWpk[22][23][1]*Wpk[16][23][1])))));
        mm[16][23] = ((mk[10]*((Vpk[16][23][2]*Vpk[23][23][2])+((Vpk[16][23][0]*
          Vpk[23][23][0])+(Vpk[16][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[16][23][2])+((IkWpk[23][23][0]*Wpk[16][23][0])+(IkWpk[23][23][1]*
          Wpk[16][23][1]))));
        mm[16][24] = 0.;
        mm[16][25] = 0.;
        mm[16][26] = 0.;
        temp[0] = (((mk[6]*((Vpk[17][17][2]*Vpk[17][17][2])+((Vpk[17][17][0]*
          Vpk[17][17][0])+(Vpk[17][17][1]*Vpk[17][17][1]))))+((IkWpk[17][17][2]*
          pin[17][2])+((IkWpk[17][17][0]*pin[17][0])+(IkWpk[17][17][1]*
          pin[17][1]))))+((mk[7]*((Vpk[17][20][2]*Vpk[17][20][2])+((
          Vpk[17][20][0]*Vpk[17][20][0])+(Vpk[17][20][1]*Vpk[17][20][1]))))+((
          IkWpk[17][20][2]*Wpk[17][20][2])+((IkWpk[17][20][0]*Wpk[17][20][0])+(
          IkWpk[17][20][1]*Wpk[17][20][1])))));
        temp[1] = (((mk[8]*((Vpk[17][21][2]*Vpk[17][21][2])+((Vpk[17][21][0]*
          Vpk[17][21][0])+(Vpk[17][21][1]*Vpk[17][21][1]))))+((IkWpk[17][21][2]*
          Wpk[17][21][2])+((IkWpk[17][21][0]*Wpk[17][21][0])+(IkWpk[17][21][1]*
          Wpk[17][21][1]))))+temp[0]);
        temp[2] = (((mk[9]*((Vpk[17][22][2]*Vpk[17][22][2])+((Vpk[17][22][0]*
          Vpk[17][22][0])+(Vpk[17][22][1]*Vpk[17][22][1]))))+((IkWpk[17][22][2]*
          Wpk[17][22][2])+((IkWpk[17][22][0]*Wpk[17][22][0])+(IkWpk[17][22][1]*
          Wpk[17][22][1]))))+temp[1]);
        mm[17][17] = (((mk[10]*((Vpk[17][23][2]*Vpk[17][23][2])+((Vpk[17][23][0]
          *Vpk[17][23][0])+(Vpk[17][23][1]*Vpk[17][23][1]))))+((IkWpk[17][23][2]
          *Wpk[17][23][2])+((IkWpk[17][23][0]*Wpk[17][23][0])+(IkWpk[17][23][1]*
          Wpk[17][23][1]))))+temp[2]);
        temp[0] = ((mk[9]*((Vpk[17][22][2]*Vpk[18][22][2])+((Vpk[17][22][0]*
          Vpk[18][22][0])+(Vpk[17][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[17][20][2]*Vpk[18][20][2])+((Vpk[17][20][0]*Vpk[18][20][0])+(
          Vpk[17][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[17][21][2]*
          Vpk[18][21][2])+((Vpk[17][21][0]*Vpk[18][21][0])+(Vpk[17][21][1]*
          Vpk[18][21][1]))))));
        mm[17][18] = ((mk[10]*((Vpk[17][23][2]*Vpk[18][23][2])+((Vpk[17][23][0]*
          Vpk[18][23][0])+(Vpk[17][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[17][22][2]*Vpk[19][22][2])+((Vpk[17][22][0]*
          Vpk[19][22][0])+(Vpk[17][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[17][20][2]*Vpk[19][20][2])+((Vpk[17][20][0]*Vpk[19][20][0])+(
          Vpk[17][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[17][21][2]*
          Vpk[19][21][2])+((Vpk[17][21][0]*Vpk[19][21][0])+(Vpk[17][21][1]*
          Vpk[19][21][1]))))));
        mm[17][19] = ((mk[10]*((Vpk[17][23][2]*Vpk[19][23][2])+((Vpk[17][23][0]*
          Vpk[19][23][0])+(Vpk[17][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[17][20][2]*Vpk[20][20][2])+((Vpk[17][20][0]*
          Vpk[20][20][0])+(Vpk[17][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          Wpk[17][20][2])+((IkWpk[20][20][0]*Wpk[17][20][0])+(IkWpk[20][20][1]*
          Wpk[17][20][1]))))+((mk[8]*((Vpk[17][21][2]*Vpk[20][21][2])+((
          Vpk[17][21][0]*Vpk[20][21][0])+(Vpk[17][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[17][21][2])+((IkWpk[20][21][0]*Wpk[17][21][0])+(
          IkWpk[20][21][1]*Wpk[17][21][1])))));
        temp[1] = (((mk[9]*((Vpk[17][22][2]*Vpk[20][22][2])+((Vpk[17][22][0]*
          Vpk[20][22][0])+(Vpk[17][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[17][22][2])+((IkWpk[20][22][0]*Wpk[17][22][0])+(IkWpk[20][22][1]*
          Wpk[17][22][1]))))+temp[0]);
        mm[17][20] = (((mk[10]*((Vpk[17][23][2]*Vpk[20][23][2])+((Vpk[17][23][0]
          *Vpk[20][23][0])+(Vpk[17][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]
          *Wpk[17][23][2])+((IkWpk[20][23][0]*Wpk[17][23][0])+(IkWpk[20][23][1]*
          Wpk[17][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[17][21][2]*Vpk[21][21][2])+((Vpk[17][21][0]*
          Vpk[21][21][0])+(Vpk[17][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[17][21][2])+((IkWpk[21][21][0]*Wpk[17][21][0])+(IkWpk[21][21][1]*
          Wpk[17][21][1]))))+((mk[9]*((Vpk[17][22][2]*Vpk[21][22][2])+((
          Vpk[17][22][0]*Vpk[21][22][0])+(Vpk[17][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[17][22][2])+((IkWpk[21][22][0]*Wpk[17][22][0])+(
          IkWpk[21][22][1]*Wpk[17][22][1])))));
        mm[17][21] = (((mk[10]*((Vpk[17][23][2]*Vpk[21][23][2])+((Vpk[17][23][0]
          *Vpk[21][23][0])+(Vpk[17][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]
          *Wpk[17][23][2])+((IkWpk[21][23][0]*Wpk[17][23][0])+(IkWpk[21][23][1]*
          Wpk[17][23][1]))))+temp[0]);
        mm[17][22] = (((mk[9]*((Vpk[17][22][2]*Vpk[22][22][2])+((Vpk[17][22][0]*
          Vpk[22][22][0])+(Vpk[17][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[17][22][2])+((IkWpk[22][22][0]*Wpk[17][22][0])+(IkWpk[22][22][1]*
          Wpk[17][22][1]))))+((mk[10]*((Vpk[17][23][2]*Vpk[22][23][2])+((
          Vpk[17][23][0]*Vpk[22][23][0])+(Vpk[17][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[17][23][2])+((IkWpk[22][23][0]*Wpk[17][23][0])+(
          IkWpk[22][23][1]*Wpk[17][23][1])))));
        mm[17][23] = ((mk[10]*((Vpk[17][23][2]*Vpk[23][23][2])+((Vpk[17][23][0]*
          Vpk[23][23][0])+(Vpk[17][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[17][23][2])+((IkWpk[23][23][0]*Wpk[17][23][0])+(IkWpk[23][23][1]*
          Wpk[17][23][1]))));
        mm[17][24] = 0.;
        mm[17][25] = 0.;
        mm[17][26] = 0.;
        temp[0] = ((mk[9]*((Vpk[18][22][2]*Vpk[18][22][2])+((Vpk[18][22][0]*
          Vpk[18][22][0])+(Vpk[18][22][1]*Vpk[18][22][1]))))+((mk[7]*((
          Vpk[18][20][2]*Vpk[18][20][2])+((Vpk[18][20][0]*Vpk[18][20][0])+(
          Vpk[18][20][1]*Vpk[18][20][1]))))+(mk[8]*((Vpk[18][21][2]*
          Vpk[18][21][2])+((Vpk[18][21][0]*Vpk[18][21][0])+(Vpk[18][21][1]*
          Vpk[18][21][1]))))));
        mm[18][18] = ((mk[10]*((Vpk[18][23][2]*Vpk[18][23][2])+((Vpk[18][23][0]*
          Vpk[18][23][0])+(Vpk[18][23][1]*Vpk[18][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[18][22][2]*Vpk[19][22][2])+((Vpk[18][22][0]*
          Vpk[19][22][0])+(Vpk[18][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[18][20][2]*Vpk[19][20][2])+((Vpk[18][20][0]*Vpk[19][20][0])+(
          Vpk[18][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[18][21][2]*
          Vpk[19][21][2])+((Vpk[18][21][0]*Vpk[19][21][0])+(Vpk[18][21][1]*
          Vpk[19][21][1]))))));
        mm[18][19] = ((mk[10]*((Vpk[18][23][2]*Vpk[19][23][2])+((Vpk[18][23][0]*
          Vpk[19][23][0])+(Vpk[18][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[18][22][2]*Vpk[20][22][2])+((Vpk[18][22][0]*
          Vpk[20][22][0])+(Vpk[18][22][1]*Vpk[20][22][1]))))+((mk[7]*((
          Vpk[18][20][2]*Vpk[20][20][2])+((Vpk[18][20][0]*Vpk[20][20][0])+(
          Vpk[18][20][1]*Vpk[20][20][1]))))+(mk[8]*((Vpk[18][21][2]*
          Vpk[20][21][2])+((Vpk[18][21][0]*Vpk[20][21][0])+(Vpk[18][21][1]*
          Vpk[20][21][1]))))));
        mm[18][20] = ((mk[10]*((Vpk[18][23][2]*Vpk[20][23][2])+((Vpk[18][23][0]*
          Vpk[20][23][0])+(Vpk[18][23][1]*Vpk[20][23][1]))))+temp[0]);
        mm[18][21] = ((mk[10]*((Vpk[18][23][2]*Vpk[21][23][2])+((Vpk[18][23][0]*
          Vpk[21][23][0])+(Vpk[18][23][1]*Vpk[21][23][1]))))+((mk[8]*((
          Vpk[18][21][2]*Vpk[21][21][2])+((Vpk[18][21][0]*Vpk[21][21][0])+(
          Vpk[18][21][1]*Vpk[21][21][1]))))+(mk[9]*((Vpk[18][22][2]*
          Vpk[21][22][2])+((Vpk[18][22][0]*Vpk[21][22][0])+(Vpk[18][22][1]*
          Vpk[21][22][1]))))));
        mm[18][22] = ((mk[9]*((Vpk[18][22][2]*Vpk[22][22][2])+((Vpk[18][22][0]*
          Vpk[22][22][0])+(Vpk[18][22][1]*Vpk[22][22][1]))))+(mk[10]*((
          Vpk[18][23][2]*Vpk[22][23][2])+((Vpk[18][23][0]*Vpk[22][23][0])+(
          Vpk[18][23][1]*Vpk[22][23][1])))));
        mm[18][23] = (mk[10]*((Vpk[18][23][2]*Vpk[23][23][2])+((Vpk[18][23][0]*
          Vpk[23][23][0])+(Vpk[18][23][1]*Vpk[23][23][1]))));
        mm[18][24] = 0.;
        mm[18][25] = 0.;
        mm[18][26] = 0.;
        temp[0] = ((mk[9]*((Vpk[19][22][2]*Vpk[19][22][2])+((Vpk[19][22][0]*
          Vpk[19][22][0])+(Vpk[19][22][1]*Vpk[19][22][1]))))+((mk[7]*((
          Vpk[19][20][2]*Vpk[19][20][2])+((Vpk[19][20][0]*Vpk[19][20][0])+(
          Vpk[19][20][1]*Vpk[19][20][1]))))+(mk[8]*((Vpk[19][21][2]*
          Vpk[19][21][2])+((Vpk[19][21][0]*Vpk[19][21][0])+(Vpk[19][21][1]*
          Vpk[19][21][1]))))));
        mm[19][19] = ((mk[10]*((Vpk[19][23][2]*Vpk[19][23][2])+((Vpk[19][23][0]*
          Vpk[19][23][0])+(Vpk[19][23][1]*Vpk[19][23][1]))))+temp[0]);
        temp[0] = ((mk[9]*((Vpk[19][22][2]*Vpk[20][22][2])+((Vpk[19][22][0]*
          Vpk[20][22][0])+(Vpk[19][22][1]*Vpk[20][22][1]))))+((mk[7]*((
          Vpk[19][20][2]*Vpk[20][20][2])+((Vpk[19][20][0]*Vpk[20][20][0])+(
          Vpk[19][20][1]*Vpk[20][20][1]))))+(mk[8]*((Vpk[19][21][2]*
          Vpk[20][21][2])+((Vpk[19][21][0]*Vpk[20][21][0])+(Vpk[19][21][1]*
          Vpk[20][21][1]))))));
        mm[19][20] = ((mk[10]*((Vpk[19][23][2]*Vpk[20][23][2])+((Vpk[19][23][0]*
          Vpk[20][23][0])+(Vpk[19][23][1]*Vpk[20][23][1]))))+temp[0]);
        mm[19][21] = ((mk[10]*((Vpk[19][23][2]*Vpk[21][23][2])+((Vpk[19][23][0]*
          Vpk[21][23][0])+(Vpk[19][23][1]*Vpk[21][23][1]))))+((mk[8]*((
          Vpk[19][21][2]*Vpk[21][21][2])+((Vpk[19][21][0]*Vpk[21][21][0])+(
          Vpk[19][21][1]*Vpk[21][21][1]))))+(mk[9]*((Vpk[19][22][2]*
          Vpk[21][22][2])+((Vpk[19][22][0]*Vpk[21][22][0])+(Vpk[19][22][1]*
          Vpk[21][22][1]))))));
        mm[19][22] = ((mk[9]*((Vpk[19][22][2]*Vpk[22][22][2])+((Vpk[19][22][0]*
          Vpk[22][22][0])+(Vpk[19][22][1]*Vpk[22][22][1]))))+(mk[10]*((
          Vpk[19][23][2]*Vpk[22][23][2])+((Vpk[19][23][0]*Vpk[22][23][0])+(
          Vpk[19][23][1]*Vpk[22][23][1])))));
        mm[19][23] = (mk[10]*((Vpk[19][23][2]*Vpk[23][23][2])+((Vpk[19][23][0]*
          Vpk[23][23][0])+(Vpk[19][23][1]*Vpk[23][23][1]))));
        mm[19][24] = 0.;
        mm[19][25] = 0.;
        mm[19][26] = 0.;
        temp[0] = (((mk[7]*((Vpk[20][20][2]*Vpk[20][20][2])+((Vpk[20][20][0]*
          Vpk[20][20][0])+(Vpk[20][20][1]*Vpk[20][20][1]))))+((IkWpk[20][20][2]*
          pin[20][2])+((IkWpk[20][20][0]*pin[20][0])+(IkWpk[20][20][1]*
          pin[20][1]))))+((mk[8]*((Vpk[20][21][2]*Vpk[20][21][2])+((
          Vpk[20][21][0]*Vpk[20][21][0])+(Vpk[20][21][1]*Vpk[20][21][1]))))+((
          IkWpk[20][21][2]*Wpk[20][21][2])+((IkWpk[20][21][0]*Wpk[20][21][0])+(
          IkWpk[20][21][1]*Wpk[20][21][1])))));
        temp[1] = (((mk[9]*((Vpk[20][22][2]*Vpk[20][22][2])+((Vpk[20][22][0]*
          Vpk[20][22][0])+(Vpk[20][22][1]*Vpk[20][22][1]))))+((IkWpk[20][22][2]*
          Wpk[20][22][2])+((IkWpk[20][22][0]*Wpk[20][22][0])+(IkWpk[20][22][1]*
          Wpk[20][22][1]))))+temp[0]);
        mm[20][20] = (((mk[10]*((Vpk[20][23][2]*Vpk[20][23][2])+((Vpk[20][23][0]
          *Vpk[20][23][0])+(Vpk[20][23][1]*Vpk[20][23][1]))))+((IkWpk[20][23][2]
          *Wpk[20][23][2])+((IkWpk[20][23][0]*Wpk[20][23][0])+(IkWpk[20][23][1]*
          Wpk[20][23][1]))))+temp[1]);
        temp[0] = (((mk[8]*((Vpk[20][21][2]*Vpk[21][21][2])+((Vpk[20][21][0]*
          Vpk[21][21][0])+(Vpk[20][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          Wpk[20][21][2])+((IkWpk[21][21][0]*Wpk[20][21][0])+(IkWpk[21][21][1]*
          Wpk[20][21][1]))))+((mk[9]*((Vpk[20][22][2]*Vpk[21][22][2])+((
          Vpk[20][22][0]*Vpk[21][22][0])+(Vpk[20][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[20][22][2])+((IkWpk[21][22][0]*Wpk[20][22][0])+(
          IkWpk[21][22][1]*Wpk[20][22][1])))));
        mm[20][21] = (((mk[10]*((Vpk[20][23][2]*Vpk[21][23][2])+((Vpk[20][23][0]
          *Vpk[21][23][0])+(Vpk[20][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]
          *Wpk[20][23][2])+((IkWpk[21][23][0]*Wpk[20][23][0])+(IkWpk[21][23][1]*
          Wpk[20][23][1]))))+temp[0]);
        mm[20][22] = (((mk[9]*((Vpk[20][22][2]*Vpk[22][22][2])+((Vpk[20][22][0]*
          Vpk[22][22][0])+(Vpk[20][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[20][22][2])+((IkWpk[22][22][0]*Wpk[20][22][0])+(IkWpk[22][22][1]*
          Wpk[20][22][1]))))+((mk[10]*((Vpk[20][23][2]*Vpk[22][23][2])+((
          Vpk[20][23][0]*Vpk[22][23][0])+(Vpk[20][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[20][23][2])+((IkWpk[22][23][0]*Wpk[20][23][0])+(
          IkWpk[22][23][1]*Wpk[20][23][1])))));
        mm[20][23] = ((mk[10]*((Vpk[20][23][2]*Vpk[23][23][2])+((Vpk[20][23][0]*
          Vpk[23][23][0])+(Vpk[20][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[20][23][2])+((IkWpk[23][23][0]*Wpk[20][23][0])+(IkWpk[23][23][1]*
          Wpk[20][23][1]))));
        mm[20][24] = 0.;
        mm[20][25] = 0.;
        mm[20][26] = 0.;
        temp[0] = (((mk[8]*((Vpk[21][21][2]*Vpk[21][21][2])+((Vpk[21][21][0]*
          Vpk[21][21][0])+(Vpk[21][21][1]*Vpk[21][21][1]))))+((IkWpk[21][21][2]*
          pin[21][2])+((IkWpk[21][21][0]*pin[21][0])+(IkWpk[21][21][1]*
          pin[21][1]))))+((mk[9]*((Vpk[21][22][2]*Vpk[21][22][2])+((
          Vpk[21][22][0]*Vpk[21][22][0])+(Vpk[21][22][1]*Vpk[21][22][1]))))+((
          IkWpk[21][22][2]*Wpk[21][22][2])+((IkWpk[21][22][0]*Wpk[21][22][0])+(
          IkWpk[21][22][1]*Wpk[21][22][1])))));
        mm[21][21] = (((mk[10]*((Vpk[21][23][2]*Vpk[21][23][2])+((Vpk[21][23][0]
          *Vpk[21][23][0])+(Vpk[21][23][1]*Vpk[21][23][1]))))+((IkWpk[21][23][2]
          *Wpk[21][23][2])+((IkWpk[21][23][0]*Wpk[21][23][0])+(IkWpk[21][23][1]*
          Wpk[21][23][1]))))+temp[0]);
        mm[21][22] = (((mk[9]*((Vpk[21][22][2]*Vpk[22][22][2])+((Vpk[21][22][0]*
          Vpk[22][22][0])+(Vpk[21][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          Wpk[21][22][2])+((IkWpk[22][22][0]*Wpk[21][22][0])+(IkWpk[22][22][1]*
          Wpk[21][22][1]))))+((mk[10]*((Vpk[21][23][2]*Vpk[22][23][2])+((
          Vpk[21][23][0]*Vpk[22][23][0])+(Vpk[21][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[21][23][2])+((IkWpk[22][23][0]*Wpk[21][23][0])+(
          IkWpk[22][23][1]*Wpk[21][23][1])))));
        mm[21][23] = ((mk[10]*((Vpk[21][23][2]*Vpk[23][23][2])+((Vpk[21][23][0]*
          Vpk[23][23][0])+(Vpk[21][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[21][23][2])+((IkWpk[23][23][0]*Wpk[21][23][0])+(IkWpk[23][23][1]*
          Wpk[21][23][1]))));
        mm[21][24] = 0.;
        mm[21][25] = 0.;
        mm[21][26] = 0.;
        mm[22][22] = (((mk[9]*((Vpk[22][22][2]*Vpk[22][22][2])+((Vpk[22][22][0]*
          Vpk[22][22][0])+(Vpk[22][22][1]*Vpk[22][22][1]))))+((IkWpk[22][22][2]*
          pin[22][2])+((IkWpk[22][22][0]*pin[22][0])+(IkWpk[22][22][1]*
          pin[22][1]))))+((mk[10]*((Vpk[22][23][2]*Vpk[22][23][2])+((
          Vpk[22][23][0]*Vpk[22][23][0])+(Vpk[22][23][1]*Vpk[22][23][1]))))+((
          IkWpk[22][23][2]*Wpk[22][23][2])+((IkWpk[22][23][0]*Wpk[22][23][0])+(
          IkWpk[22][23][1]*Wpk[22][23][1])))));
        mm[22][23] = ((mk[10]*((Vpk[22][23][2]*Vpk[23][23][2])+((Vpk[22][23][0]*
          Vpk[23][23][0])+(Vpk[22][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          Wpk[22][23][2])+((IkWpk[23][23][0]*Wpk[22][23][0])+(IkWpk[23][23][1]*
          Wpk[22][23][1]))));
        mm[22][24] = 0.;
        mm[22][25] = 0.;
        mm[22][26] = 0.;
        mm[23][23] = ((mk[10]*((Vpk[23][23][2]*Vpk[23][23][2])+((Vpk[23][23][0]*
          Vpk[23][23][0])+(Vpk[23][23][1]*Vpk[23][23][1]))))+((IkWpk[23][23][2]*
          pin[23][2])+((IkWpk[23][23][0]*pin[23][0])+(IkWpk[23][23][1]*
          pin[23][1]))));
        mm[23][24] = 0.;
        mm[23][25] = 0.;
        mm[23][26] = 0.;
        mm[24][24] = ((mk[11]*((Vpk[24][26][2]*Vpk[24][26][2])+((Vpk[24][26][0]*
          Vpk[24][26][0])+(Vpk[24][26][1]*Vpk[24][26][1]))))+((IkWpk[24][26][2]*
          Wpk[24][26][2])+((IkWpk[24][26][0]*Wpk[24][26][0])+(IkWpk[24][26][1]*
          Wpk[24][26][1]))));
        mm[24][25] = ((mk[11]*((Vpk[24][26][2]*Vpk[25][26][2])+((Vpk[24][26][0]*
          Vpk[25][26][0])+(Vpk[24][26][1]*Vpk[25][26][1]))))+((IkWpk[25][26][2]*
          Wpk[24][26][2])+((IkWpk[25][26][0]*Wpk[24][26][0])+(IkWpk[25][26][1]*
          Wpk[24][26][1]))));
        mm[24][26] = ((mk[11]*((Vpk[24][26][2]*Vpk[26][26][2])+((Vpk[24][26][0]*
          Vpk[26][26][0])+(Vpk[24][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          Wpk[24][26][2])+((IkWpk[26][26][0]*Wpk[24][26][0])+(IkWpk[26][26][1]*
          Wpk[24][26][1]))));
        mm[25][25] = ((mk[11]*((Vpk[25][26][2]*Vpk[25][26][2])+((Vpk[25][26][0]*
          Vpk[25][26][0])+(Vpk[25][26][1]*Vpk[25][26][1]))))+((IkWpk[25][26][2]*
          Wpk[25][26][2])+((IkWpk[25][26][0]*Wpk[25][26][0])+(IkWpk[25][26][1]*
          Wpk[25][26][1]))));
        mm[25][26] = ((mk[11]*((Vpk[25][26][2]*Vpk[26][26][2])+((Vpk[25][26][0]*
          Vpk[26][26][0])+(Vpk[25][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          Wpk[25][26][2])+((IkWpk[26][26][0]*Wpk[25][26][0])+(IkWpk[26][26][1]*
          Wpk[25][26][1]))));
        mm[26][26] = ((mk[11]*((Vpk[26][26][2]*Vpk[26][26][2])+((Vpk[26][26][0]*
          Vpk[26][26][0])+(Vpk[26][26][1]*Vpk[26][26][1]))))+((IkWpk[26][26][2]*
          pin[26][2])+((IkWpk[26][26][0]*pin[26][0])+(IkWpk[26][26][1]*
          pin[26][1]))));
/*
Check for singular mass matrix
*/
        for (i = 0; i < 27; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        mmflg = 1;
    }
/*
 Used 1.26 seconds CPU time,
 131072 additional bytes of memory.
 Equations contain 4314 adds/subtracts/negates
                   5768 multiplies
                      0 divides
                    954 assignments
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
        sdldudcomp(27,27,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 27; i++) {
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
    double mmat[27][27];
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 27; i++) {
        for (j = i; j <= 26; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

sdfrcmat(fmat)
    double fmat[27];
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 27; i++) {
        fmat[i] = fs0[i];
    }
}

sdmfrc(imult)
    double imult[27];
{
/*
Calculate forces due to constraint multipliers.

*/
    int i,j;
    double umult[4];

/*
Initialize all multiplier forces to zero.
*/
    for (i = 0; i <= 11; i++) {
        for (j = 0; j <= 2; j++) {
            mfk[i][j] = 0.;
            mtk[i][j] = 0.;
        }
    }
    for (i = 0; i <= 26; i++) {
        mtau[i] = 0.;
    }
/*
Compute user-generated multiplier forces
*/
    umult[0] = imult[23];
    umult[1] = imult[24];
    umult[2] = imult[25];
    umult[3] = imult[26];
    mfrcflg = 1;
    sduconsfrc(curtim,q,u,umult);
    mfrcflg = 0;
    if (pres[0]  !=  0.) {
        mtau[0] = (imult[0]+mtau[0]);
    }
    if (pres[1]  !=  0.) {
        mtau[1] = (imult[1]+mtau[1]);
    }
    if (pres[2]  !=  0.) {
        mtau[2] = (imult[2]+mtau[2]);
    }
    if (pres[3]  !=  0.) {
        mtau[3] = (imult[3]+mtau[3]);
    }
    if (pres[4]  !=  0.) {
        mtau[4] = (imult[4]+mtau[4]);
    }
    if (pres[5]  !=  0.) {
        mtau[5] = (imult[5]+mtau[5]);
    }
    if (pres[6]  !=  0.) {
        mtau[6] = (imult[6]+mtau[6]);
    }
    if (pres[7]  !=  0.) {
        mtau[7] = (imult[7]+mtau[7]);
    }
    if (pres[8]  !=  0.) {
        mtau[8] = (imult[8]+mtau[8]);
    }
    if (pres[11]  !=  0.) {
        mtau[11] = (imult[9]+mtau[11]);
    }
    if (pres[12]  !=  0.) {
        mtau[12] = (imult[10]+mtau[12]);
    }
    if (pres[13]  !=  0.) {
        mtau[13] = (imult[11]+mtau[13]);
    }
    if (pres[14]  !=  0.) {
        mtau[14] = (imult[12]+mtau[14]);
    }
    if (pres[15]  !=  0.) {
        mtau[15] = (imult[13]+mtau[15]);
    }
    if (pres[16]  !=  0.) {
        mtau[16] = (imult[14]+mtau[16]);
    }
    if (pres[17]  !=  0.) {
        mtau[17] = (imult[15]+mtau[17]);
    }
    if (pres[20]  !=  0.) {
        mtau[20] = (imult[16]+mtau[20]);
    }
    if (pres[21]  !=  0.) {
        mtau[21] = (imult[17]+mtau[21]);
    }
    if (pres[22]  !=  0.) {
        mtau[22] = (imult[18]+mtau[22]);
    }
    if (pres[23]  !=  0.) {
        mtau[23] = (imult[19]+mtau[23]);
    }
    if (pres[24]  !=  0.) {
        mtau[24] = (imult[20]+mtau[24]);
    }
    if (pres[25]  !=  0.) {
        mtau[25] = (imult[21]+mtau[25]);
    }
    if (pres[26]  !=  0.) {
        mtau[26] = (imult[22]+mtau[26]);
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   23 adds/subtracts/negates
                      0 multiplies
                      0 divides
                    126 assignments
*/
}

sdequivht(tau)
    double tau[27];
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[27][3],tstareq[27][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[5][0] = -(ufk[0][0]+(gk[5][0]*mk[0]));
    fstareq[5][1] = -(ufk[0][1]+(gk[5][1]*mk[0]));
    fstareq[5][2] = -(ufk[0][2]+(gk[5][2]*mk[0]));
    fstareq[8][0] = -(ufk[1][0]+(gk[8][0]*mk[1]));
    fstareq[8][1] = -(ufk[1][1]+(gk[8][1]*mk[1]));
    fstareq[8][2] = -(ufk[1][2]+(gk[8][2]*mk[1]));
    fstareq[11][0] = -(ufk[2][0]+(gk[11][0]*mk[2]));
    fstareq[11][1] = -(ufk[2][1]+(gk[11][1]*mk[2]));
    fstareq[11][2] = -(ufk[2][2]+(gk[11][2]*mk[2]));
    fstareq[12][0] = -(ufk[3][0]+(gk[12][0]*mk[3]));
    fstareq[12][1] = -(ufk[3][1]+(gk[12][1]*mk[3]));
    fstareq[12][2] = -(ufk[3][2]+(gk[12][2]*mk[3]));
    fstareq[13][0] = -(ufk[4][0]+(gk[13][0]*mk[4]));
    fstareq[13][1] = -(ufk[4][1]+(gk[13][1]*mk[4]));
    fstareq[13][2] = -(ufk[4][2]+(gk[13][2]*mk[4]));
    fstareq[14][0] = -(ufk[5][0]+(gk[14][0]*mk[5]));
    fstareq[14][1] = -(ufk[5][1]+(gk[14][1]*mk[5]));
    fstareq[14][2] = -(ufk[5][2]+(gk[14][2]*mk[5]));
    fstareq[17][0] = -(ufk[6][0]+(gk[17][0]*mk[6]));
    fstareq[17][1] = -(ufk[6][1]+(gk[17][1]*mk[6]));
    fstareq[17][2] = -(ufk[6][2]+(gk[17][2]*mk[6]));
    fstareq[20][0] = -(ufk[7][0]+(gk[20][0]*mk[7]));
    fstareq[20][1] = -(ufk[7][1]+(gk[20][1]*mk[7]));
    fstareq[20][2] = -(ufk[7][2]+(gk[20][2]*mk[7]));
    fstareq[21][0] = -(ufk[8][0]+(gk[21][0]*mk[8]));
    fstareq[21][1] = -(ufk[8][1]+(gk[21][1]*mk[8]));
    fstareq[21][2] = -(ufk[8][2]+(gk[21][2]*mk[8]));
    fstareq[22][0] = -(ufk[9][0]+(gk[22][0]*mk[9]));
    fstareq[22][1] = -(ufk[9][1]+(gk[22][1]*mk[9]));
    fstareq[22][2] = -(ufk[9][2]+(gk[22][2]*mk[9]));
    fstareq[23][0] = -(ufk[10][0]+(gk[23][0]*mk[10]));
    fstareq[23][1] = -(ufk[10][1]+(gk[23][1]*mk[10]));
    fstareq[23][2] = -(ufk[10][2]+(gk[23][2]*mk[10]));
    fstareq[26][0] = -(ufk[11][0]+(gk[26][0]*mk[11]));
    fstareq[26][1] = -(ufk[11][1]+(gk[26][1]*mk[11]));
    fstareq[26][2] = -(ufk[11][2]+(gk[26][2]*mk[11]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    temp[0] = (((fstareq[12][2]*Vpk[0][12][2])+((fstareq[12][0]*Vpk[0][12][0])+(
      fstareq[12][1]*Vpk[0][12][1])))+(((fstareq[11][2]*Vpk[0][11][2])+((
      fstareq[11][0]*Vpk[0][11][0])+(fstareq[11][1]*Vpk[0][11][1])))+(((
      fstareq[5][2]*Vpk[0][5][2])+((fstareq[5][0]*Vpk[0][5][0])+(fstareq[5][1]*
      Vpk[0][5][1])))+((fstareq[8][2]*Vpk[0][8][2])+((fstareq[8][0]*Vpk[0][8][0]
      )+(fstareq[8][1]*Vpk[0][8][1]))))));
    temp[1] = (((fstareq[20][2]*Vpk[0][20][2])+((fstareq[20][0]*Vpk[0][20][0])+(
      fstareq[20][1]*Vpk[0][20][1])))+(((fstareq[17][2]*Vpk[0][17][2])+((
      fstareq[17][0]*Vpk[0][17][0])+(fstareq[17][1]*Vpk[0][17][1])))+(((
      fstareq[14][2]*Vpk[0][14][2])+((fstareq[14][0]*Vpk[0][14][0])+(
      fstareq[14][1]*Vpk[0][14][1])))+(((fstareq[13][2]*Vpk[0][13][2])+((
      fstareq[13][0]*Vpk[0][13][0])+(fstareq[13][1]*Vpk[0][13][1])))+temp[0]))))
      ;
    tau[0] = (utau[0]-(((fstareq[26][2]*Vpk[0][26][2])+((fstareq[26][0]*
      Vpk[0][26][0])+(fstareq[26][1]*Vpk[0][26][1])))+(((fstareq[23][2]*
      Vpk[0][23][2])+((fstareq[23][0]*Vpk[0][23][0])+(fstareq[23][1]*
      Vpk[0][23][1])))+(((fstareq[22][2]*Vpk[0][22][2])+((fstareq[22][0]*
      Vpk[0][22][0])+(fstareq[22][1]*Vpk[0][22][1])))+(((fstareq[21][2]*
      Vpk[0][21][2])+((fstareq[21][0]*Vpk[0][21][0])+(fstareq[21][1]*
      Vpk[0][21][1])))+temp[1])))));
    temp[0] = (((fstareq[12][2]*Vpk[1][12][2])+((fstareq[12][0]*Vpk[1][12][0])+(
      fstareq[12][1]*Vpk[1][12][1])))+(((fstareq[11][2]*Vpk[1][11][2])+((
      fstareq[11][0]*Vpk[1][11][0])+(fstareq[11][1]*Vpk[1][11][1])))+(((
      fstareq[5][2]*Vpk[1][5][2])+((fstareq[5][0]*Vpk[1][5][0])+(fstareq[5][1]*
      Vpk[1][5][1])))+((fstareq[8][2]*Vpk[1][8][2])+((fstareq[8][0]*Vpk[1][8][0]
      )+(fstareq[8][1]*Vpk[1][8][1]))))));
    temp[1] = (((fstareq[20][2]*Vpk[1][20][2])+((fstareq[20][0]*Vpk[1][20][0])+(
      fstareq[20][1]*Vpk[1][20][1])))+(((fstareq[17][2]*Vpk[1][17][2])+((
      fstareq[17][0]*Vpk[1][17][0])+(fstareq[17][1]*Vpk[1][17][1])))+(((
      fstareq[14][2]*Vpk[1][14][2])+((fstareq[14][0]*Vpk[1][14][0])+(
      fstareq[14][1]*Vpk[1][14][1])))+(((fstareq[13][2]*Vpk[1][13][2])+((
      fstareq[13][0]*Vpk[1][13][0])+(fstareq[13][1]*Vpk[1][13][1])))+temp[0]))))
      ;
    tau[1] = (utau[1]-(((fstareq[26][2]*Vpk[1][26][2])+((fstareq[26][0]*
      Vpk[1][26][0])+(fstareq[26][1]*Vpk[1][26][1])))+(((fstareq[23][2]*
      Vpk[1][23][2])+((fstareq[23][0]*Vpk[1][23][0])+(fstareq[23][1]*
      Vpk[1][23][1])))+(((fstareq[22][2]*Vpk[1][22][2])+((fstareq[22][0]*
      Vpk[1][22][0])+(fstareq[22][1]*Vpk[1][22][1])))+(((fstareq[21][2]*
      Vpk[1][21][2])+((fstareq[21][0]*Vpk[1][21][0])+(fstareq[21][1]*
      Vpk[1][21][1])))+temp[1])))));
    temp[0] = (((fstareq[12][2]*Vpk[2][12][2])+((fstareq[12][0]*Vpk[2][12][0])+(
      fstareq[12][1]*Vpk[2][12][1])))+(((fstareq[11][2]*Vpk[2][11][2])+((
      fstareq[11][0]*Vpk[2][11][0])+(fstareq[11][1]*Vpk[2][11][1])))+(((
      fstareq[5][2]*Vpk[2][5][2])+((fstareq[5][0]*Vpk[2][5][0])+(fstareq[5][1]*
      Vpk[2][5][1])))+((fstareq[8][2]*Vpk[2][8][2])+((fstareq[8][0]*Vpk[2][8][0]
      )+(fstareq[8][1]*Vpk[2][8][1]))))));
    temp[1] = (((fstareq[20][2]*Vpk[2][20][2])+((fstareq[20][0]*Vpk[2][20][0])+(
      fstareq[20][1]*Vpk[2][20][1])))+(((fstareq[17][2]*Vpk[2][17][2])+((
      fstareq[17][0]*Vpk[2][17][0])+(fstareq[17][1]*Vpk[2][17][1])))+(((
      fstareq[14][2]*Vpk[2][14][2])+((fstareq[14][0]*Vpk[2][14][0])+(
      fstareq[14][1]*Vpk[2][14][1])))+(((fstareq[13][2]*Vpk[2][13][2])+((
      fstareq[13][0]*Vpk[2][13][0])+(fstareq[13][1]*Vpk[2][13][1])))+temp[0]))))
      ;
    tau[2] = (utau[2]-(((fstareq[26][2]*Vpk[2][26][2])+((fstareq[26][0]*
      Vpk[2][26][0])+(fstareq[26][1]*Vpk[2][26][1])))+(((fstareq[23][2]*
      Vpk[2][23][2])+((fstareq[23][0]*Vpk[2][23][0])+(fstareq[23][1]*
      Vpk[2][23][1])))+(((fstareq[22][2]*Vpk[2][22][2])+((fstareq[22][0]*
      Vpk[2][22][0])+(fstareq[22][1]*Vpk[2][22][1])))+(((fstareq[21][2]*
      Vpk[2][21][2])+((fstareq[21][0]*Vpk[2][21][0])+(fstareq[21][1]*
      Vpk[2][21][1])))+temp[1])))));
    temp[0] = ((((fstareq[5][2]*Vpk[3][5][2])+((fstareq[5][0]*Vpk[3][5][0])+(
      fstareq[5][1]*Vpk[3][5][1])))-((utk[0][2]*Wpk[3][5][2])+((utk[0][0]*
      Wpk[3][5][0])+(utk[0][1]*Wpk[3][5][1]))))+(((fstareq[8][2]*Vpk[3][8][2])+(
      (fstareq[8][0]*Vpk[3][8][0])+(fstareq[8][1]*Vpk[3][8][1])))-((utk[1][2]*
      Wpk[3][8][2])+((utk[1][0]*Wpk[3][8][0])+(utk[1][1]*Wpk[3][8][1])))));
    temp[1] = ((((fstareq[12][2]*Vpk[3][12][2])+((fstareq[12][0]*Vpk[3][12][0])+
      (fstareq[12][1]*Vpk[3][12][1])))-((utk[3][2]*Wpk[3][12][2])+((utk[3][0]*
      Wpk[3][12][0])+(utk[3][1]*Wpk[3][12][1]))))+((((fstareq[11][2]*
      Vpk[3][11][2])+((fstareq[11][0]*Vpk[3][11][0])+(fstareq[11][1]*
      Vpk[3][11][1])))-((utk[2][2]*Wpk[3][11][2])+((utk[2][0]*Wpk[3][11][0])+(
      utk[2][1]*Wpk[3][11][1]))))+temp[0]));
    temp[2] = ((((fstareq[14][2]*Vpk[3][14][2])+((fstareq[14][0]*Vpk[3][14][0])+
      (fstareq[14][1]*Vpk[3][14][1])))-((utk[5][2]*Wpk[3][14][2])+((utk[5][0]*
      Wpk[3][14][0])+(utk[5][1]*Wpk[3][14][1]))))+((((fstareq[13][2]*
      Vpk[3][13][2])+((fstareq[13][0]*Vpk[3][13][0])+(fstareq[13][1]*
      Vpk[3][13][1])))-((utk[4][2]*Wpk[3][13][2])+((utk[4][0]*Wpk[3][13][0])+(
      utk[4][1]*Wpk[3][13][1]))))+temp[1]));
    temp[3] = ((((fstareq[20][2]*Vpk[3][20][2])+((fstareq[20][0]*Vpk[3][20][0])+
      (fstareq[20][1]*Vpk[3][20][1])))-((utk[7][2]*Wpk[3][20][2])+((utk[7][0]*
      Wpk[3][20][0])+(utk[7][1]*Wpk[3][20][1]))))+((((fstareq[17][2]*
      Vpk[3][17][2])+((fstareq[17][0]*Vpk[3][17][0])+(fstareq[17][1]*
      Vpk[3][17][1])))-((utk[6][2]*Wpk[3][17][2])+((utk[6][0]*Wpk[3][17][0])+(
      utk[6][1]*Wpk[3][17][1]))))+temp[2]));
    temp[4] = ((((fstareq[22][2]*Vpk[3][22][2])+((fstareq[22][0]*Vpk[3][22][0])+
      (fstareq[22][1]*Vpk[3][22][1])))-((utk[9][2]*Wpk[3][22][2])+((utk[9][0]*
      Wpk[3][22][0])+(utk[9][1]*Wpk[3][22][1]))))+((((fstareq[21][2]*
      Vpk[3][21][2])+((fstareq[21][0]*Vpk[3][21][0])+(fstareq[21][1]*
      Vpk[3][21][1])))-((utk[8][2]*Wpk[3][21][2])+((utk[8][0]*Wpk[3][21][0])+(
      utk[8][1]*Wpk[3][21][1]))))+temp[3]));
    tau[3] = (utau[3]-((((fstareq[26][2]*Vpk[3][26][2])+((fstareq[26][0]*
      Vpk[3][26][0])+(fstareq[26][1]*Vpk[3][26][1])))-((utk[11][2]*Wpk[3][26][2]
      )+((utk[11][0]*Wpk[3][26][0])+(utk[11][1]*Wpk[3][26][1]))))+((((
      fstareq[23][2]*Vpk[3][23][2])+((fstareq[23][0]*Vpk[3][23][0])+(
      fstareq[23][1]*Vpk[3][23][1])))-((utk[10][2]*Wpk[3][23][2])+((utk[10][0]*
      Wpk[3][23][0])+(utk[10][1]*Wpk[3][23][1]))))+temp[4])));
    temp[0] = ((((fstareq[5][2]*Vpk[4][5][2])+((fstareq[5][0]*Vpk[4][5][0])+(
      fstareq[5][1]*Vpk[4][5][1])))-((utk[0][2]*Wpk[4][5][2])+((utk[0][0]*
      Wpk[4][5][0])+(utk[0][1]*Wpk[4][5][1]))))+(((fstareq[8][2]*Vpk[4][8][2])+(
      (fstareq[8][0]*Vpk[4][8][0])+(fstareq[8][1]*Vpk[4][8][1])))-((utk[1][2]*
      Wpk[4][8][2])+((utk[1][0]*Wpk[4][8][0])+(utk[1][1]*Wpk[4][8][1])))));
    temp[1] = ((((fstareq[12][2]*Vpk[4][12][2])+((fstareq[12][0]*Vpk[4][12][0])+
      (fstareq[12][1]*Vpk[4][12][1])))-((utk[3][2]*Wpk[4][12][2])+((utk[3][0]*
      Wpk[4][12][0])+(utk[3][1]*Wpk[4][12][1]))))+((((fstareq[11][2]*
      Vpk[4][11][2])+((fstareq[11][0]*Vpk[4][11][0])+(fstareq[11][1]*
      Vpk[4][11][1])))-((utk[2][2]*Wpk[4][11][2])+((utk[2][0]*Wpk[4][11][0])+(
      utk[2][1]*Wpk[4][11][1]))))+temp[0]));
    temp[2] = ((((fstareq[14][2]*Vpk[4][14][2])+((fstareq[14][0]*Vpk[4][14][0])+
      (fstareq[14][1]*Vpk[4][14][1])))-((utk[5][2]*Wpk[4][14][2])+((utk[5][0]*
      Wpk[4][14][0])+(utk[5][1]*Wpk[4][14][1]))))+((((fstareq[13][2]*
      Vpk[4][13][2])+((fstareq[13][0]*Vpk[4][13][0])+(fstareq[13][1]*
      Vpk[4][13][1])))-((utk[4][2]*Wpk[4][13][2])+((utk[4][0]*Wpk[4][13][0])+(
      utk[4][1]*Wpk[4][13][1]))))+temp[1]));
    temp[3] = ((((fstareq[20][2]*Vpk[4][20][2])+((fstareq[20][0]*Vpk[4][20][0])+
      (fstareq[20][1]*Vpk[4][20][1])))-((utk[7][2]*Wpk[4][20][2])+((utk[7][0]*
      Wpk[4][20][0])+(utk[7][1]*Wpk[4][20][1]))))+((((fstareq[17][2]*
      Vpk[4][17][2])+((fstareq[17][0]*Vpk[4][17][0])+(fstareq[17][1]*
      Vpk[4][17][1])))-((utk[6][2]*Wpk[4][17][2])+((utk[6][0]*Wpk[4][17][0])+(
      utk[6][1]*Wpk[4][17][1]))))+temp[2]));
    temp[4] = ((((fstareq[22][2]*Vpk[4][22][2])+((fstareq[22][0]*Vpk[4][22][0])+
      (fstareq[22][1]*Vpk[4][22][1])))-((utk[9][2]*Wpk[4][22][2])+((utk[9][0]*
      Wpk[4][22][0])+(utk[9][1]*Wpk[4][22][1]))))+((((fstareq[21][2]*
      Vpk[4][21][2])+((fstareq[21][0]*Vpk[4][21][0])+(fstareq[21][1]*
      Vpk[4][21][1])))-((utk[8][2]*Wpk[4][21][2])+((utk[8][0]*Wpk[4][21][0])+(
      utk[8][1]*Wpk[4][21][1]))))+temp[3]));
    tau[4] = (utau[4]-((((fstareq[26][2]*Vpk[4][26][2])+((fstareq[26][0]*
      Vpk[4][26][0])+(fstareq[26][1]*Vpk[4][26][1])))-((utk[11][2]*Wpk[4][26][2]
      )+((utk[11][0]*Wpk[4][26][0])+(utk[11][1]*Wpk[4][26][1]))))+((((
      fstareq[23][2]*Vpk[4][23][2])+((fstareq[23][0]*Vpk[4][23][0])+(
      fstareq[23][1]*Vpk[4][23][1])))-((utk[10][2]*Wpk[4][23][2])+((utk[10][0]*
      Wpk[4][23][0])+(utk[10][1]*Wpk[4][23][1]))))+temp[4])));
    temp[0] = ((((fstareq[5][2]*Vpk[5][5][2])+((fstareq[5][0]*Vpk[5][5][0])+(
      fstareq[5][1]*Vpk[5][5][1])))-((pin[2][2]*utk[0][2])+((pin[2][0]*utk[0][0]
      )+(pin[2][1]*utk[0][1]))))+(((fstareq[8][2]*Vpk[5][8][2])+((fstareq[8][0]*
      Vpk[5][8][0])+(fstareq[8][1]*Vpk[5][8][1])))-((utk[1][2]*Wpk[5][8][2])+((
      utk[1][0]*Wpk[5][8][0])+(utk[1][1]*Wpk[5][8][1])))));
    temp[1] = ((((fstareq[12][2]*Vpk[5][12][2])+((fstareq[12][0]*Vpk[5][12][0])+
      (fstareq[12][1]*Vpk[5][12][1])))-((utk[3][2]*Wpk[5][12][2])+((utk[3][0]*
      Wpk[5][12][0])+(utk[3][1]*Wpk[5][12][1]))))+((((fstareq[11][2]*
      Vpk[5][11][2])+((fstareq[11][0]*Vpk[5][11][0])+(fstareq[11][1]*
      Vpk[5][11][1])))-((utk[2][2]*Wpk[5][11][2])+((utk[2][0]*Wpk[5][11][0])+(
      utk[2][1]*Wpk[5][11][1]))))+temp[0]));
    temp[2] = ((((fstareq[14][2]*Vpk[5][14][2])+((fstareq[14][0]*Vpk[5][14][0])+
      (fstareq[14][1]*Vpk[5][14][1])))-((utk[5][2]*Wpk[5][14][2])+((utk[5][0]*
      Wpk[5][14][0])+(utk[5][1]*Wpk[5][14][1]))))+((((fstareq[13][2]*
      Vpk[5][13][2])+((fstareq[13][0]*Vpk[5][13][0])+(fstareq[13][1]*
      Vpk[5][13][1])))-((utk[4][2]*Wpk[5][13][2])+((utk[4][0]*Wpk[5][13][0])+(
      utk[4][1]*Wpk[5][13][1]))))+temp[1]));
    temp[3] = ((((fstareq[20][2]*Vpk[5][20][2])+((fstareq[20][0]*Vpk[5][20][0])+
      (fstareq[20][1]*Vpk[5][20][1])))-((utk[7][2]*Wpk[5][20][2])+((utk[7][0]*
      Wpk[5][20][0])+(utk[7][1]*Wpk[5][20][1]))))+((((fstareq[17][2]*
      Vpk[5][17][2])+((fstareq[17][0]*Vpk[5][17][0])+(fstareq[17][1]*
      Vpk[5][17][1])))-((utk[6][2]*Wpk[5][17][2])+((utk[6][0]*Wpk[5][17][0])+(
      utk[6][1]*Wpk[5][17][1]))))+temp[2]));
    temp[4] = ((((fstareq[22][2]*Vpk[5][22][2])+((fstareq[22][0]*Vpk[5][22][0])+
      (fstareq[22][1]*Vpk[5][22][1])))-((utk[9][2]*Wpk[5][22][2])+((utk[9][0]*
      Wpk[5][22][0])+(utk[9][1]*Wpk[5][22][1]))))+((((fstareq[21][2]*
      Vpk[5][21][2])+((fstareq[21][0]*Vpk[5][21][0])+(fstareq[21][1]*
      Vpk[5][21][1])))-((utk[8][2]*Wpk[5][21][2])+((utk[8][0]*Wpk[5][21][0])+(
      utk[8][1]*Wpk[5][21][1]))))+temp[3]));
    tau[5] = (utau[5]-((((fstareq[26][2]*Vpk[5][26][2])+((fstareq[26][0]*
      Vpk[5][26][0])+(fstareq[26][1]*Vpk[5][26][1])))-((utk[11][2]*Wpk[5][26][2]
      )+((utk[11][0]*Wpk[5][26][0])+(utk[11][1]*Wpk[5][26][1]))))+((((
      fstareq[23][2]*Vpk[5][23][2])+((fstareq[23][0]*Vpk[5][23][0])+(
      fstareq[23][1]*Vpk[5][23][1])))-((utk[10][2]*Wpk[5][23][2])+((utk[10][0]*
      Wpk[5][23][0])+(utk[10][1]*Wpk[5][23][1]))))+temp[4])));
    temp[0] = ((((fstareq[8][2]*Vpk[6][8][2])+((fstareq[8][0]*Vpk[6][8][0])+(
      fstareq[8][1]*Vpk[6][8][1])))-((utk[1][2]*Wpk[6][8][2])+((utk[1][0]*
      Wpk[6][8][0])+(utk[1][1]*Wpk[6][8][1]))))+(((fstareq[11][2]*Vpk[6][11][2])
      +((fstareq[11][0]*Vpk[6][11][0])+(fstareq[11][1]*Vpk[6][11][1])))-((
      utk[2][2]*Wpk[6][11][2])+((utk[2][0]*Wpk[6][11][0])+(utk[2][1]*
      Wpk[6][11][1])))));
    temp[1] = ((((fstareq[13][2]*Vpk[6][13][2])+((fstareq[13][0]*Vpk[6][13][0])+
      (fstareq[13][1]*Vpk[6][13][1])))-((utk[4][2]*Wpk[6][13][2])+((utk[4][0]*
      Wpk[6][13][0])+(utk[4][1]*Wpk[6][13][1]))))+((((fstareq[12][2]*
      Vpk[6][12][2])+((fstareq[12][0]*Vpk[6][12][0])+(fstareq[12][1]*
      Vpk[6][12][1])))-((utk[3][2]*Wpk[6][12][2])+((utk[3][0]*Wpk[6][12][0])+(
      utk[3][1]*Wpk[6][12][1]))))+temp[0]));
    tau[6] = (utau[6]-((((fstareq[14][2]*Vpk[6][14][2])+((fstareq[14][0]*
      Vpk[6][14][0])+(fstareq[14][1]*Vpk[6][14][1])))-((utk[5][2]*Wpk[6][14][2])
      +((utk[5][0]*Wpk[6][14][0])+(utk[5][1]*Wpk[6][14][1]))))+temp[1]));
    temp[0] = ((((fstareq[8][2]*Vpk[7][8][2])+((fstareq[8][0]*Vpk[7][8][0])+(
      fstareq[8][1]*Vpk[7][8][1])))-((utk[1][2]*Wpk[7][8][2])+((utk[1][0]*
      Wpk[7][8][0])+(utk[1][1]*Wpk[7][8][1]))))+(((fstareq[11][2]*Vpk[7][11][2])
      +((fstareq[11][0]*Vpk[7][11][0])+(fstareq[11][1]*Vpk[7][11][1])))-((
      utk[2][2]*Wpk[7][11][2])+((utk[2][0]*Wpk[7][11][0])+(utk[2][1]*
      Wpk[7][11][1])))));
    temp[1] = ((((fstareq[13][2]*Vpk[7][13][2])+((fstareq[13][0]*Vpk[7][13][0])+
      (fstareq[13][1]*Vpk[7][13][1])))-((utk[4][2]*Wpk[7][13][2])+((utk[4][0]*
      Wpk[7][13][0])+(utk[4][1]*Wpk[7][13][1]))))+((((fstareq[12][2]*
      Vpk[7][12][2])+((fstareq[12][0]*Vpk[7][12][0])+(fstareq[12][1]*
      Vpk[7][12][1])))-((utk[3][2]*Wpk[7][12][2])+((utk[3][0]*Wpk[7][12][0])+(
      utk[3][1]*Wpk[7][12][1]))))+temp[0]));
    tau[7] = (utau[7]-((((fstareq[14][2]*Vpk[7][14][2])+((fstareq[14][0]*
      Vpk[7][14][0])+(fstareq[14][1]*Vpk[7][14][1])))-((utk[5][2]*Wpk[7][14][2])
      +((utk[5][0]*Wpk[7][14][0])+(utk[5][1]*Wpk[7][14][1]))))+temp[1]));
    temp[0] = ((((fstareq[8][2]*Vpk[8][8][2])+((fstareq[8][0]*Vpk[8][8][0])+(
      fstareq[8][1]*Vpk[8][8][1])))-((pin[8][2]*utk[1][2])+((pin[8][0]*utk[1][0]
      )+(pin[8][1]*utk[1][1]))))+(((fstareq[11][2]*Vpk[8][11][2])+((
      fstareq[11][0]*Vpk[8][11][0])+(fstareq[11][1]*Vpk[8][11][1])))-((utk[2][2]
      *Wpk[8][11][2])+((utk[2][0]*Wpk[8][11][0])+(utk[2][1]*Wpk[8][11][1])))));
    temp[1] = ((((fstareq[13][2]*Vpk[8][13][2])+((fstareq[13][0]*Vpk[8][13][0])+
      (fstareq[13][1]*Vpk[8][13][1])))-((utk[4][2]*Wpk[8][13][2])+((utk[4][0]*
      Wpk[8][13][0])+(utk[4][1]*Wpk[8][13][1]))))+((((fstareq[12][2]*
      Vpk[8][12][2])+((fstareq[12][0]*Vpk[8][12][0])+(fstareq[12][1]*
      Vpk[8][12][1])))-((utk[3][2]*Wpk[8][12][2])+((utk[3][0]*Wpk[8][12][0])+(
      utk[3][1]*Wpk[8][12][1]))))+temp[0]));
    tau[8] = (utau[8]-((((fstareq[14][2]*Vpk[8][14][2])+((fstareq[14][0]*
      Vpk[8][14][0])+(fstareq[14][1]*Vpk[8][14][1])))-((utk[5][2]*Wpk[8][14][2])
      +((utk[5][0]*Wpk[8][14][0])+(utk[5][1]*Wpk[8][14][1]))))+temp[1]));
    tau[9] = (utau[9]-(((fstareq[14][2]*Vpk[9][14][2])+((fstareq[14][0]*
      Vpk[9][14][0])+(fstareq[14][1]*Vpk[9][14][1])))+(((fstareq[13][2]*
      Vpk[9][13][2])+((fstareq[13][0]*Vpk[9][13][0])+(fstareq[13][1]*
      Vpk[9][13][1])))+(((fstareq[11][2]*Vpk[9][11][2])+((fstareq[11][0]*
      Vpk[9][11][0])+(fstareq[11][1]*Vpk[9][11][1])))+((fstareq[12][2]*
      Vpk[9][12][2])+((fstareq[12][0]*Vpk[9][12][0])+(fstareq[12][1]*
      Vpk[9][12][1])))))));
    tau[10] = (utau[10]-(((fstareq[14][2]*Vpk[10][14][2])+((fstareq[14][0]*
      Vpk[10][14][0])+(fstareq[14][1]*Vpk[10][14][1])))+(((fstareq[13][2]*
      Vpk[10][13][2])+((fstareq[13][0]*Vpk[10][13][0])+(fstareq[13][1]*
      Vpk[10][13][1])))+(((fstareq[11][2]*Vpk[10][11][2])+((fstareq[11][0]*
      Vpk[10][11][0])+(fstareq[11][1]*Vpk[10][11][1])))+((fstareq[12][2]*
      Vpk[10][12][2])+((fstareq[12][0]*Vpk[10][12][0])+(fstareq[12][1]*
      Vpk[10][12][1])))))));
    temp[0] = ((((fstareq[11][2]*Vpk[11][11][2])+((fstareq[11][0]*Vpk[11][11][0]
      )+(fstareq[11][1]*Vpk[11][11][1])))-((pin[11][2]*utk[2][2])+((pin[11][0]*
      utk[2][0])+(pin[11][1]*utk[2][1]))))+(((fstareq[12][2]*Vpk[11][12][2])+((
      fstareq[12][0]*Vpk[11][12][0])+(fstareq[12][1]*Vpk[11][12][1])))-((
      utk[3][2]*Wpk[11][12][2])+((utk[3][0]*Wpk[11][12][0])+(utk[3][1]*
      Wpk[11][12][1])))));
    tau[11] = (utau[11]-((((fstareq[14][2]*Vpk[11][14][2])+((fstareq[14][0]*
      Vpk[11][14][0])+(fstareq[14][1]*Vpk[11][14][1])))-((utk[5][2]*
      Wpk[11][14][2])+((utk[5][0]*Wpk[11][14][0])+(utk[5][1]*Wpk[11][14][1]))))+
      ((((fstareq[13][2]*Vpk[11][13][2])+((fstareq[13][0]*Vpk[11][13][0])+(
      fstareq[13][1]*Vpk[11][13][1])))-((utk[4][2]*Wpk[11][13][2])+((utk[4][0]*
      Wpk[11][13][0])+(utk[4][1]*Wpk[11][13][1]))))+temp[0])));
    temp[0] = ((((fstareq[12][2]*Vpk[12][12][2])+((fstareq[12][0]*Vpk[12][12][0]
      )+(fstareq[12][1]*Vpk[12][12][1])))-((pin[12][2]*utk[3][2])+((pin[12][0]*
      utk[3][0])+(pin[12][1]*utk[3][1]))))+(((fstareq[13][2]*Vpk[12][13][2])+((
      fstareq[13][0]*Vpk[12][13][0])+(fstareq[13][1]*Vpk[12][13][1])))-((
      utk[4][2]*Wpk[12][13][2])+((utk[4][0]*Wpk[12][13][0])+(utk[4][1]*
      Wpk[12][13][1])))));
    tau[12] = (utau[12]-((((fstareq[14][2]*Vpk[12][14][2])+((fstareq[14][0]*
      Vpk[12][14][0])+(fstareq[14][1]*Vpk[12][14][1])))-((utk[5][2]*
      Wpk[12][14][2])+((utk[5][0]*Wpk[12][14][0])+(utk[5][1]*Wpk[12][14][1]))))+
      temp[0]));
    tau[13] = (utau[13]-((((fstareq[13][2]*Vpk[13][13][2])+((fstareq[13][0]*
      Vpk[13][13][0])+(fstareq[13][1]*Vpk[13][13][1])))-((pin[13][2]*utk[4][2])+
      ((pin[13][0]*utk[4][0])+(pin[13][1]*utk[4][1]))))+(((fstareq[14][2]*
      Vpk[13][14][2])+((fstareq[14][0]*Vpk[13][14][0])+(fstareq[14][1]*
      Vpk[13][14][1])))-((utk[5][2]*Wpk[13][14][2])+((utk[5][0]*Wpk[13][14][0])+
      (utk[5][1]*Wpk[13][14][1]))))));
    tau[14] = (utau[14]-(((fstareq[14][2]*Vpk[14][14][2])+((fstareq[14][0]*
      Vpk[14][14][0])+(fstareq[14][1]*Vpk[14][14][1])))-((pin[14][2]*utk[5][2])+
      ((pin[14][0]*utk[5][0])+(pin[14][1]*utk[5][1])))));
    temp[0] = ((((fstareq[17][2]*Vpk[15][17][2])+((fstareq[17][0]*Vpk[15][17][0]
      )+(fstareq[17][1]*Vpk[15][17][1])))-((utk[6][2]*Wpk[15][17][2])+((
      utk[6][0]*Wpk[15][17][0])+(utk[6][1]*Wpk[15][17][1]))))+(((fstareq[20][2]*
      Vpk[15][20][2])+((fstareq[20][0]*Vpk[15][20][0])+(fstareq[20][1]*
      Vpk[15][20][1])))-((utk[7][2]*Wpk[15][20][2])+((utk[7][0]*Wpk[15][20][0])+
      (utk[7][1]*Wpk[15][20][1])))));
    temp[1] = ((((fstareq[22][2]*Vpk[15][22][2])+((fstareq[22][0]*Vpk[15][22][0]
      )+(fstareq[22][1]*Vpk[15][22][1])))-((utk[9][2]*Wpk[15][22][2])+((
      utk[9][0]*Wpk[15][22][0])+(utk[9][1]*Wpk[15][22][1]))))+((((fstareq[21][2]
      *Vpk[15][21][2])+((fstareq[21][0]*Vpk[15][21][0])+(fstareq[21][1]*
      Vpk[15][21][1])))-((utk[8][2]*Wpk[15][21][2])+((utk[8][0]*Wpk[15][21][0])+
      (utk[8][1]*Wpk[15][21][1]))))+temp[0]));
    tau[15] = (utau[15]-((((fstareq[23][2]*Vpk[15][23][2])+((fstareq[23][0]*
      Vpk[15][23][0])+(fstareq[23][1]*Vpk[15][23][1])))-((utk[10][2]*
      Wpk[15][23][2])+((utk[10][0]*Wpk[15][23][0])+(utk[10][1]*Wpk[15][23][1])))
      )+temp[1]));
    temp[0] = ((((fstareq[17][2]*Vpk[16][17][2])+((fstareq[17][0]*Vpk[16][17][0]
      )+(fstareq[17][1]*Vpk[16][17][1])))-((utk[6][2]*Wpk[16][17][2])+((
      utk[6][0]*Wpk[16][17][0])+(utk[6][1]*Wpk[16][17][1]))))+(((fstareq[20][2]*
      Vpk[16][20][2])+((fstareq[20][0]*Vpk[16][20][0])+(fstareq[20][1]*
      Vpk[16][20][1])))-((utk[7][2]*Wpk[16][20][2])+((utk[7][0]*Wpk[16][20][0])+
      (utk[7][1]*Wpk[16][20][1])))));
    temp[1] = ((((fstareq[22][2]*Vpk[16][22][2])+((fstareq[22][0]*Vpk[16][22][0]
      )+(fstareq[22][1]*Vpk[16][22][1])))-((utk[9][2]*Wpk[16][22][2])+((
      utk[9][0]*Wpk[16][22][0])+(utk[9][1]*Wpk[16][22][1]))))+((((fstareq[21][2]
      *Vpk[16][21][2])+((fstareq[21][0]*Vpk[16][21][0])+(fstareq[21][1]*
      Vpk[16][21][1])))-((utk[8][2]*Wpk[16][21][2])+((utk[8][0]*Wpk[16][21][0])+
      (utk[8][1]*Wpk[16][21][1]))))+temp[0]));
    tau[16] = (utau[16]-((((fstareq[23][2]*Vpk[16][23][2])+((fstareq[23][0]*
      Vpk[16][23][0])+(fstareq[23][1]*Vpk[16][23][1])))-((utk[10][2]*
      Wpk[16][23][2])+((utk[10][0]*Wpk[16][23][0])+(utk[10][1]*Wpk[16][23][1])))
      )+temp[1]));
    temp[0] = ((((fstareq[17][2]*Vpk[17][17][2])+((fstareq[17][0]*Vpk[17][17][0]
      )+(fstareq[17][1]*Vpk[17][17][1])))-((pin[17][2]*utk[6][2])+((pin[17][0]*
      utk[6][0])+(pin[17][1]*utk[6][1]))))+(((fstareq[20][2]*Vpk[17][20][2])+((
      fstareq[20][0]*Vpk[17][20][0])+(fstareq[20][1]*Vpk[17][20][1])))-((
      utk[7][2]*Wpk[17][20][2])+((utk[7][0]*Wpk[17][20][0])+(utk[7][1]*
      Wpk[17][20][1])))));
    temp[1] = ((((fstareq[22][2]*Vpk[17][22][2])+((fstareq[22][0]*Vpk[17][22][0]
      )+(fstareq[22][1]*Vpk[17][22][1])))-((utk[9][2]*Wpk[17][22][2])+((
      utk[9][0]*Wpk[17][22][0])+(utk[9][1]*Wpk[17][22][1]))))+((((fstareq[21][2]
      *Vpk[17][21][2])+((fstareq[21][0]*Vpk[17][21][0])+(fstareq[21][1]*
      Vpk[17][21][1])))-((utk[8][2]*Wpk[17][21][2])+((utk[8][0]*Wpk[17][21][0])+
      (utk[8][1]*Wpk[17][21][1]))))+temp[0]));
    tau[17] = (utau[17]-((((fstareq[23][2]*Vpk[17][23][2])+((fstareq[23][0]*
      Vpk[17][23][0])+(fstareq[23][1]*Vpk[17][23][1])))-((utk[10][2]*
      Wpk[17][23][2])+((utk[10][0]*Wpk[17][23][0])+(utk[10][1]*Wpk[17][23][1])))
      )+temp[1]));
    tau[18] = (utau[18]-(((fstareq[23][2]*Vpk[18][23][2])+((fstareq[23][0]*
      Vpk[18][23][0])+(fstareq[23][1]*Vpk[18][23][1])))+(((fstareq[22][2]*
      Vpk[18][22][2])+((fstareq[22][0]*Vpk[18][22][0])+(fstareq[22][1]*
      Vpk[18][22][1])))+(((fstareq[20][2]*Vpk[18][20][2])+((fstareq[20][0]*
      Vpk[18][20][0])+(fstareq[20][1]*Vpk[18][20][1])))+((fstareq[21][2]*
      Vpk[18][21][2])+((fstareq[21][0]*Vpk[18][21][0])+(fstareq[21][1]*
      Vpk[18][21][1])))))));
    tau[19] = (utau[19]-(((fstareq[23][2]*Vpk[19][23][2])+((fstareq[23][0]*
      Vpk[19][23][0])+(fstareq[23][1]*Vpk[19][23][1])))+(((fstareq[22][2]*
      Vpk[19][22][2])+((fstareq[22][0]*Vpk[19][22][0])+(fstareq[22][1]*
      Vpk[19][22][1])))+(((fstareq[20][2]*Vpk[19][20][2])+((fstareq[20][0]*
      Vpk[19][20][0])+(fstareq[20][1]*Vpk[19][20][1])))+((fstareq[21][2]*
      Vpk[19][21][2])+((fstareq[21][0]*Vpk[19][21][0])+(fstareq[21][1]*
      Vpk[19][21][1])))))));
    temp[0] = ((((fstareq[20][2]*Vpk[20][20][2])+((fstareq[20][0]*Vpk[20][20][0]
      )+(fstareq[20][1]*Vpk[20][20][1])))-((pin[20][2]*utk[7][2])+((pin[20][0]*
      utk[7][0])+(pin[20][1]*utk[7][1]))))+(((fstareq[21][2]*Vpk[20][21][2])+((
      fstareq[21][0]*Vpk[20][21][0])+(fstareq[21][1]*Vpk[20][21][1])))-((
      utk[8][2]*Wpk[20][21][2])+((utk[8][0]*Wpk[20][21][0])+(utk[8][1]*
      Wpk[20][21][1])))));
    tau[20] = (utau[20]-((((fstareq[23][2]*Vpk[20][23][2])+((fstareq[23][0]*
      Vpk[20][23][0])+(fstareq[23][1]*Vpk[20][23][1])))-((utk[10][2]*
      Wpk[20][23][2])+((utk[10][0]*Wpk[20][23][0])+(utk[10][1]*Wpk[20][23][1])))
      )+((((fstareq[22][2]*Vpk[20][22][2])+((fstareq[22][0]*Vpk[20][22][0])+(
      fstareq[22][1]*Vpk[20][22][1])))-((utk[9][2]*Wpk[20][22][2])+((utk[9][0]*
      Wpk[20][22][0])+(utk[9][1]*Wpk[20][22][1]))))+temp[0])));
    temp[0] = ((((fstareq[21][2]*Vpk[21][21][2])+((fstareq[21][0]*Vpk[21][21][0]
      )+(fstareq[21][1]*Vpk[21][21][1])))-((pin[21][2]*utk[8][2])+((pin[21][0]*
      utk[8][0])+(pin[21][1]*utk[8][1]))))+(((fstareq[22][2]*Vpk[21][22][2])+((
      fstareq[22][0]*Vpk[21][22][0])+(fstareq[22][1]*Vpk[21][22][1])))-((
      utk[9][2]*Wpk[21][22][2])+((utk[9][0]*Wpk[21][22][0])+(utk[9][1]*
      Wpk[21][22][1])))));
    tau[21] = (utau[21]-((((fstareq[23][2]*Vpk[21][23][2])+((fstareq[23][0]*
      Vpk[21][23][0])+(fstareq[23][1]*Vpk[21][23][1])))-((utk[10][2]*
      Wpk[21][23][2])+((utk[10][0]*Wpk[21][23][0])+(utk[10][1]*Wpk[21][23][1])))
      )+temp[0]));
    tau[22] = (utau[22]-((((fstareq[22][2]*Vpk[22][22][2])+((fstareq[22][0]*
      Vpk[22][22][0])+(fstareq[22][1]*Vpk[22][22][1])))-((pin[22][2]*utk[9][2])+
      ((pin[22][0]*utk[9][0])+(pin[22][1]*utk[9][1]))))+(((fstareq[23][2]*
      Vpk[22][23][2])+((fstareq[23][0]*Vpk[22][23][0])+(fstareq[23][1]*
      Vpk[22][23][1])))-((utk[10][2]*Wpk[22][23][2])+((utk[10][0]*Wpk[22][23][0]
      )+(utk[10][1]*Wpk[22][23][1]))))));
    tau[23] = (utau[23]-(((fstareq[23][2]*Vpk[23][23][2])+((fstareq[23][0]*
      Vpk[23][23][0])+(fstareq[23][1]*Vpk[23][23][1])))-((pin[23][2]*utk[10][2])
      +((pin[23][0]*utk[10][0])+(pin[23][1]*utk[10][1])))));
    tau[24] = (utau[24]-(((fstareq[26][2]*Vpk[24][26][2])+((fstareq[26][0]*
      Vpk[24][26][0])+(fstareq[26][1]*Vpk[24][26][1])))-((utk[11][2]*
      Wpk[24][26][2])+((utk[11][0]*Wpk[24][26][0])+(utk[11][1]*Wpk[24][26][1])))
      ));
    tau[25] = (utau[25]-(((fstareq[26][2]*Vpk[25][26][2])+((fstareq[26][0]*
      Vpk[25][26][0])+(fstareq[26][1]*Vpk[25][26][1])))-((utk[11][2]*
      Wpk[25][26][2])+((utk[11][0]*Wpk[25][26][0])+(utk[11][1]*Wpk[25][26][1])))
      ));
    tau[26] = (utau[26]-(((fstareq[26][2]*Vpk[26][26][2])+((fstareq[26][0]*
      Vpk[26][26][0])+(fstareq[26][1]*Vpk[26][26][1])))-((pin[26][2]*utk[11][2])
      +((pin[26][0]*utk[11][0])+(pin[26][1]*utk[11][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.23 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  762 adds/subtracts/negates
                    726 multiplies
                      0 divides
                    100 assignments
*/
}

sdfulltrq(udotin,multin,trqout)
    double udotin[27],multin[27],trqout[27];
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[27][3],tstarr[27][3],Otkr[27][3],Atir[27][3],Atkr[27][3];

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
    Otkr[3][0] = (pin[0][0]*udotin[3]);
    Otkr[3][1] = (pin[0][1]*udotin[3]);
    Otkr[3][2] = (pin[0][2]*udotin[3]);
    Otkr[4][0] = (((Cik[4][2][0]*Otkr[3][2])+((Cik[4][0][0]*Otkr[3][0])+(
      Cik[4][1][0]*Otkr[3][1])))+((pin[1][0]*udotin[4])+((Wik[4][2]*wk[4][1])-(
      Wik[4][1]*wk[4][2]))));
    Otkr[4][1] = (((Cik[4][2][1]*Otkr[3][2])+((Cik[4][0][1]*Otkr[3][0])+(
      Cik[4][1][1]*Otkr[3][1])))+((pin[1][1]*udotin[4])+((Wik[4][0]*wk[4][2])-(
      Wik[4][2]*wk[4][0]))));
    Otkr[4][2] = (((Cik[4][2][2]*Otkr[3][2])+((Cik[4][0][2]*Otkr[3][0])+(
      Cik[4][1][2]*Otkr[3][1])))+((pin[1][2]*udotin[4])+((Wik[4][1]*wk[4][0])-(
      Wik[4][0]*wk[4][1]))));
    Otkr[5][0] = (((Cik[5][2][0]*Otkr[4][2])+((Cik[5][0][0]*Otkr[4][0])+(
      Cik[5][1][0]*Otkr[4][1])))+((pin[2][0]*udotin[5])+((Wik[5][2]*wk[5][1])-(
      Wik[5][1]*wk[5][2]))));
    Otkr[5][1] = (((Cik[5][2][1]*Otkr[4][2])+((Cik[5][0][1]*Otkr[4][0])+(
      Cik[5][1][1]*Otkr[4][1])))+((pin[2][1]*udotin[5])+((Wik[5][0]*wk[5][2])-(
      Wik[5][2]*wk[5][0]))));
    Otkr[5][2] = (((Cik[5][2][2]*Otkr[4][2])+((Cik[5][0][2]*Otkr[4][0])+(
      Cik[5][1][2]*Otkr[4][1])))+((pin[2][2]*udotin[5])+((Wik[5][1]*wk[5][0])-(
      Wik[5][0]*wk[5][1]))));
    Otkr[6][0] = (((Cik[6][2][0]*Otkr[5][2])+((Cik[6][0][0]*Otkr[5][0])+(
      Cik[6][1][0]*Otkr[5][1])))+((pin[6][0]*udotin[6])+((Wik[6][2]*wk[6][1])-(
      Wik[6][1]*wk[6][2]))));
    Otkr[6][1] = (((Cik[6][2][1]*Otkr[5][2])+((Cik[6][0][1]*Otkr[5][0])+(
      Cik[6][1][1]*Otkr[5][1])))+((pin[6][1]*udotin[6])+((Wik[6][0]*wk[6][2])-(
      Wik[6][2]*wk[6][0]))));
    Otkr[6][2] = (((Cik[6][2][2]*Otkr[5][2])+((Cik[6][0][2]*Otkr[5][0])+(
      Cik[6][1][2]*Otkr[5][1])))+((pin[6][2]*udotin[6])+((Wik[6][1]*wk[6][0])-(
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
    Otkr[11][0] = (((Cik[11][2][0]*Otkr[8][2])+((Cik[11][0][0]*Otkr[8][0])+(
      Cik[11][1][0]*Otkr[8][1])))+((pin[11][0]*udotin[11])+((Wik[11][2]*
      wk[11][1])-(Wik[11][1]*wk[11][2]))));
    Otkr[11][1] = (((Cik[11][2][1]*Otkr[8][2])+((Cik[11][0][1]*Otkr[8][0])+(
      Cik[11][1][1]*Otkr[8][1])))+((pin[11][1]*udotin[11])+((Wik[11][0]*
      wk[11][2])-(Wik[11][2]*wk[11][0]))));
    Otkr[11][2] = (((Cik[11][2][2]*Otkr[8][2])+((Cik[11][0][2]*Otkr[8][0])+(
      Cik[11][1][2]*Otkr[8][1])))+((pin[11][2]*udotin[11])+((Wik[11][1]*
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
    Otkr[15][0] = (((Cik[15][2][0]*Otkr[5][2])+((Cik[15][0][0]*Otkr[5][0])+(
      Cik[15][1][0]*Otkr[5][1])))+((pin[15][0]*udotin[15])+((Wik[15][2]*
      wk[15][1])-(Wik[15][1]*wk[15][2]))));
    Otkr[15][1] = (((Cik[15][2][1]*Otkr[5][2])+((Cik[15][0][1]*Otkr[5][0])+(
      Cik[15][1][1]*Otkr[5][1])))+((pin[15][1]*udotin[15])+((Wik[15][0]*
      wk[15][2])-(Wik[15][2]*wk[15][0]))));
    Otkr[15][2] = (((Cik[15][2][2]*Otkr[5][2])+((Cik[15][0][2]*Otkr[5][0])+(
      Cik[15][1][2]*Otkr[5][1])))+((pin[15][2]*udotin[15])+((Wik[15][1]*
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
    Otkr[20][0] = (((Cik[20][2][0]*Otkr[17][2])+((Cik[20][0][0]*Otkr[17][0])+(
      Cik[20][1][0]*Otkr[17][1])))+((pin[20][0]*udotin[20])+((Wik[20][2]*
      wk[20][1])-(Wik[20][1]*wk[20][2]))));
    Otkr[20][1] = (((Cik[20][2][1]*Otkr[17][2])+((Cik[20][0][1]*Otkr[17][0])+(
      Cik[20][1][1]*Otkr[17][1])))+((pin[20][1]*udotin[20])+((Wik[20][0]*
      wk[20][2])-(Wik[20][2]*wk[20][0]))));
    Otkr[20][2] = (((Cik[20][2][2]*Otkr[17][2])+((Cik[20][0][2]*Otkr[17][0])+(
      Cik[20][1][2]*Otkr[17][1])))+((pin[20][2]*udotin[20])+((Wik[20][1]*
      wk[20][0])-(Wik[20][0]*wk[20][1]))));
    Otkr[21][0] = (((Cik[21][2][0]*Otkr[20][2])+((Cik[21][0][0]*Otkr[20][0])+(
      Cik[21][1][0]*Otkr[20][1])))+((pin[21][0]*udotin[21])+((Wik[21][2]*
      wk[21][1])-(Wik[21][1]*wk[21][2]))));
    Otkr[21][1] = (((Cik[21][2][1]*Otkr[20][2])+((Cik[21][0][1]*Otkr[20][0])+(
      Cik[21][1][1]*Otkr[20][1])))+((pin[21][1]*udotin[21])+((Wik[21][0]*
      wk[21][2])-(Wik[21][2]*wk[21][0]))));
    Otkr[21][2] = (((Cik[21][2][2]*Otkr[20][2])+((Cik[21][0][2]*Otkr[20][0])+(
      Cik[21][1][2]*Otkr[20][1])))+((pin[21][2]*udotin[21])+((Wik[21][1]*
      wk[21][0])-(Wik[21][0]*wk[21][1]))));
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
    Otkr[24][0] = (((Cik[24][2][0]*Otkr[5][2])+((Cik[24][0][0]*Otkr[5][0])+(
      Cik[24][1][0]*Otkr[5][1])))+((pin[24][0]*udotin[24])+((Wik[24][2]*
      wk[24][1])-(Wik[24][1]*wk[24][2]))));
    Otkr[24][1] = (((Cik[24][2][1]*Otkr[5][2])+((Cik[24][0][1]*Otkr[5][0])+(
      Cik[24][1][1]*Otkr[5][1])))+((pin[24][1]*udotin[24])+((Wik[24][0]*
      wk[24][2])-(Wik[24][2]*wk[24][0]))));
    Otkr[24][2] = (((Cik[24][2][2]*Otkr[5][2])+((Cik[24][0][2]*Otkr[5][0])+(
      Cik[24][1][2]*Otkr[5][1])))+((pin[24][2]*udotin[24])+((Wik[24][1]*
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
    Atkr[4][0] = ((Atkr[3][2]*Cik[4][2][0])+((Atkr[3][0]*Cik[4][0][0])+(
      Atkr[3][1]*Cik[4][1][0])));
    Atkr[4][1] = ((Atkr[3][2]*Cik[4][2][1])+((Atkr[3][0]*Cik[4][0][1])+(
      Atkr[3][1]*Cik[4][1][1])));
    Atkr[4][2] = ((Atkr[3][2]*Cik[4][2][2])+((Atkr[3][0]*Cik[4][0][2])+(
      Atkr[3][1]*Cik[4][1][2])));
    Atkr[5][0] = (((Atkr[4][2]*Cik[5][2][0])+((Atkr[4][0]*Cik[5][0][0])+(
      Atkr[4][1]*Cik[5][1][0])))+(((Otkr[5][2]*rk[0][1])-(Otkr[5][1]*rk[0][2]))+
      ((wk[5][1]*Wkrpk[5][2])-(wk[5][2]*Wkrpk[5][1]))));
    Atkr[5][1] = (((Atkr[4][2]*Cik[5][2][1])+((Atkr[4][0]*Cik[5][0][1])+(
      Atkr[4][1]*Cik[5][1][1])))+(((Otkr[5][0]*rk[0][2])-(Otkr[5][2]*rk[0][0]))+
      ((wk[5][2]*Wkrpk[5][0])-(wk[5][0]*Wkrpk[5][2]))));
    Atkr[5][2] = (((Atkr[4][2]*Cik[5][2][2])+((Atkr[4][0]*Cik[5][0][2])+(
      Atkr[4][1]*Cik[5][1][2])))+(((Otkr[5][1]*rk[0][0])-(Otkr[5][0]*rk[0][1]))+
      ((wk[5][0]*Wkrpk[5][1])-(wk[5][1]*Wkrpk[5][0]))));
    Atir[6][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[1][2])-(Otkr[5][2]*ri[1][1]))+((
      Wirk[6][2]*wk[5][1])-(Wirk[6][1]*wk[5][2]))));
    Atir[6][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[1][0])-(Otkr[5][0]*ri[1][2]))+((
      Wirk[6][0]*wk[5][2])-(Wirk[6][2]*wk[5][0]))));
    Atir[6][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[1][1])-(Otkr[5][1]*ri[1][0]))+((
      Wirk[6][1]*wk[5][0])-(Wirk[6][0]*wk[5][1]))));
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
    Atkr[8][0] = (((Atkr[7][2]*Cik[8][2][0])+((Atkr[7][0]*Cik[8][0][0])+(
      Atkr[7][1]*Cik[8][1][0])))+(((Otkr[8][2]*rk[1][1])-(Otkr[8][1]*rk[1][2]))+
      ((wk[8][1]*Wkrpk[8][2])-(wk[8][2]*Wkrpk[8][1]))));
    Atkr[8][1] = (((Atkr[7][2]*Cik[8][2][1])+((Atkr[7][0]*Cik[8][0][1])+(
      Atkr[7][1]*Cik[8][1][1])))+(((Otkr[8][0]*rk[1][2])-(Otkr[8][2]*rk[1][0]))+
      ((wk[8][2]*Wkrpk[8][0])-(wk[8][0]*Wkrpk[8][2]))));
    Atkr[8][2] = (((Atkr[7][2]*Cik[8][2][2])+((Atkr[7][0]*Cik[8][0][2])+(
      Atkr[7][1]*Cik[8][1][2])))+(((Otkr[8][1]*rk[1][0])-(Otkr[8][0]*rk[1][1]))+
      ((wk[8][0]*Wkrpk[8][1])-(wk[8][1]*Wkrpk[8][0]))));
    Atir[9][0] = (Atkr[8][0]+(((Otkr[8][1]*ri[2][2])-(Otkr[8][2]*ri[2][1]))+((
      Wirk[9][2]*wk[8][1])-(Wirk[9][1]*wk[8][2]))));
    Atir[9][1] = (Atkr[8][1]+(((Otkr[8][2]*ri[2][0])-(Otkr[8][0]*ri[2][2]))+((
      Wirk[9][0]*wk[8][2])-(Wirk[9][2]*wk[8][0]))));
    Atir[9][2] = (Atkr[8][2]+(((Otkr[8][0]*ri[2][1])-(Otkr[8][1]*ri[2][0]))+((
      Wirk[9][1]*wk[8][0])-(Wirk[9][0]*wk[8][1]))));
    Atkr[9][0] = ((Atir[9][0]+((2.*((Vik[9][2]*wk[8][1])-(Vik[9][1]*wk[8][2])))+
      (((Otkr[8][1]*rpp[9][2])-(Otkr[8][2]*rpp[9][1]))+((wk[8][1]*Wkrpk[9][2])-(
      wk[8][2]*Wkrpk[9][1])))))+(pin[9][0]*udotin[9]));
    Atkr[9][1] = ((Atir[9][1]+((2.*((Vik[9][0]*wk[8][2])-(Vik[9][2]*wk[8][0])))+
      (((Otkr[8][2]*rpp[9][0])-(Otkr[8][0]*rpp[9][2]))+((wk[8][2]*Wkrpk[9][0])-(
      wk[8][0]*Wkrpk[9][2])))))+(pin[9][1]*udotin[9]));
    Atkr[9][2] = ((Atir[9][2]+((2.*((Vik[9][1]*wk[8][0])-(Vik[9][0]*wk[8][1])))+
      (((Otkr[8][0]*rpp[9][1])-(Otkr[8][1]*rpp[9][0]))+((wk[8][0]*Wkrpk[9][1])-(
      wk[8][1]*Wkrpk[9][0])))))+(pin[9][2]*udotin[9]));
    Atkr[10][0] = ((Atkr[9][0]+((2.*((Vik[10][2]*wk[8][1])-(Vik[10][1]*wk[8][2])
      ))+(((Otkr[8][1]*rpp[10][2])-(Otkr[8][2]*rpp[10][1]))+((wk[8][1]*
      Wkrpk[10][2])-(wk[8][2]*Wkrpk[10][1])))))+(pin[10][0]*udotin[10]));
    Atkr[10][1] = ((Atkr[9][1]+((2.*((Vik[10][0]*wk[8][2])-(Vik[10][2]*wk[8][0])
      ))+(((Otkr[8][2]*rpp[10][0])-(Otkr[8][0]*rpp[10][2]))+((wk[8][2]*
      Wkrpk[10][0])-(wk[8][0]*Wkrpk[10][2])))))+(pin[10][1]*udotin[10]));
    Atkr[10][2] = ((Atkr[9][2]+((2.*((Vik[10][1]*wk[8][0])-(Vik[10][0]*wk[8][1])
      ))+(((Otkr[8][0]*rpp[10][1])-(Otkr[8][1]*rpp[10][0]))+((wk[8][0]*
      Wkrpk[10][1])-(wk[8][1]*Wkrpk[10][0])))))+(pin[10][2]*udotin[10]));
    Atkr[11][0] = (((Atkr[10][2]*Cik[11][2][0])+((Atkr[10][0]*Cik[11][0][0])+(
      Atkr[10][1]*Cik[11][1][0])))+(((Otkr[11][2]*rk[2][1])-(Otkr[11][1]*
      rk[2][2]))+((wk[11][1]*Wkrpk[11][2])-(wk[11][2]*Wkrpk[11][1]))));
    Atkr[11][1] = (((Atkr[10][2]*Cik[11][2][1])+((Atkr[10][0]*Cik[11][0][1])+(
      Atkr[10][1]*Cik[11][1][1])))+(((Otkr[11][0]*rk[2][2])-(Otkr[11][2]*
      rk[2][0]))+((wk[11][2]*Wkrpk[11][0])-(wk[11][0]*Wkrpk[11][2]))));
    Atkr[11][2] = (((Atkr[10][2]*Cik[11][2][2])+((Atkr[10][0]*Cik[11][0][2])+(
      Atkr[10][1]*Cik[11][1][2])))+(((Otkr[11][1]*rk[2][0])-(Otkr[11][0]*
      rk[2][1]))+((wk[11][0]*Wkrpk[11][1])-(wk[11][1]*Wkrpk[11][0]))));
    Atir[12][0] = (Atkr[11][0]+(((Otkr[11][1]*ri[3][2])-(Otkr[11][2]*ri[3][1]))+
      ((Wirk[12][2]*wk[11][1])-(Wirk[12][1]*wk[11][2]))));
    Atir[12][1] = (Atkr[11][1]+(((Otkr[11][2]*ri[3][0])-(Otkr[11][0]*ri[3][2]))+
      ((Wirk[12][0]*wk[11][2])-(Wirk[12][2]*wk[11][0]))));
    Atir[12][2] = (Atkr[11][2]+(((Otkr[11][0]*ri[3][1])-(Otkr[11][1]*ri[3][0]))+
      ((Wirk[12][1]*wk[11][0])-(Wirk[12][0]*wk[11][1]))));
    Atkr[12][0] = (((Atir[12][2]*Cik[12][2][0])+((Atir[12][0]*Cik[12][0][0])+(
      Atir[12][1]*Cik[12][1][0])))+(((Otkr[12][2]*rk[3][1])-(Otkr[12][1]*
      rk[3][2]))+((wk[12][1]*Wkrpk[12][2])-(wk[12][2]*Wkrpk[12][1]))));
    Atkr[12][1] = (((Atir[12][2]*Cik[12][2][1])+((Atir[12][0]*Cik[12][0][1])+(
      Atir[12][1]*Cik[12][1][1])))+(((Otkr[12][0]*rk[3][2])-(Otkr[12][2]*
      rk[3][0]))+((wk[12][2]*Wkrpk[12][0])-(wk[12][0]*Wkrpk[12][2]))));
    Atkr[12][2] = (((Atir[12][2]*Cik[12][2][2])+((Atir[12][0]*Cik[12][0][2])+(
      Atir[12][1]*Cik[12][1][2])))+(((Otkr[12][1]*rk[3][0])-(Otkr[12][0]*
      rk[3][1]))+((wk[12][0]*Wkrpk[12][1])-(wk[12][1]*Wkrpk[12][0]))));
    Atir[13][0] = (Atkr[12][0]+(((Otkr[12][1]*ri[4][2])-(Otkr[12][2]*ri[4][1]))+
      ((Wirk[13][2]*wk[12][1])-(Wirk[13][1]*wk[12][2]))));
    Atir[13][1] = (Atkr[12][1]+(((Otkr[12][2]*ri[4][0])-(Otkr[12][0]*ri[4][2]))+
      ((Wirk[13][0]*wk[12][2])-(Wirk[13][2]*wk[12][0]))));
    Atir[13][2] = (Atkr[12][2]+(((Otkr[12][0]*ri[4][1])-(Otkr[12][1]*ri[4][0]))+
      ((Wirk[13][1]*wk[12][0])-(Wirk[13][0]*wk[12][1]))));
    Atkr[13][0] = (((Atir[13][2]*Cik[13][2][0])+((Atir[13][0]*Cik[13][0][0])+(
      Atir[13][1]*Cik[13][1][0])))+(((Otkr[13][2]*rk[4][1])-(Otkr[13][1]*
      rk[4][2]))+((wk[13][1]*Wkrpk[13][2])-(wk[13][2]*Wkrpk[13][1]))));
    Atkr[13][1] = (((Atir[13][2]*Cik[13][2][1])+((Atir[13][0]*Cik[13][0][1])+(
      Atir[13][1]*Cik[13][1][1])))+(((Otkr[13][0]*rk[4][2])-(Otkr[13][2]*
      rk[4][0]))+((wk[13][2]*Wkrpk[13][0])-(wk[13][0]*Wkrpk[13][2]))));
    Atkr[13][2] = (((Atir[13][2]*Cik[13][2][2])+((Atir[13][0]*Cik[13][0][2])+(
      Atir[13][1]*Cik[13][1][2])))+(((Otkr[13][1]*rk[4][0])-(Otkr[13][0]*
      rk[4][1]))+((wk[13][0]*Wkrpk[13][1])-(wk[13][1]*Wkrpk[13][0]))));
    Atir[14][0] = (Atkr[13][0]+(((Otkr[13][1]*ri[5][2])-(Otkr[13][2]*ri[5][1]))+
      ((Wirk[14][2]*wk[13][1])-(Wirk[14][1]*wk[13][2]))));
    Atir[14][1] = (Atkr[13][1]+(((Otkr[13][2]*ri[5][0])-(Otkr[13][0]*ri[5][2]))+
      ((Wirk[14][0]*wk[13][2])-(Wirk[14][2]*wk[13][0]))));
    Atir[14][2] = (Atkr[13][2]+(((Otkr[13][0]*ri[5][1])-(Otkr[13][1]*ri[5][0]))+
      ((Wirk[14][1]*wk[13][0])-(Wirk[14][0]*wk[13][1]))));
    Atkr[14][0] = (((Atir[14][2]*Cik[14][2][0])+((Atir[14][0]*Cik[14][0][0])+(
      Atir[14][1]*Cik[14][1][0])))+(((Otkr[14][2]*rk[5][1])-(Otkr[14][1]*
      rk[5][2]))+((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*Wkrpk[14][1]))));
    Atkr[14][1] = (((Atir[14][2]*Cik[14][2][1])+((Atir[14][0]*Cik[14][0][1])+(
      Atir[14][1]*Cik[14][1][1])))+(((Otkr[14][0]*rk[5][2])-(Otkr[14][2]*
      rk[5][0]))+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*Wkrpk[14][2]))));
    Atkr[14][2] = (((Atir[14][2]*Cik[14][2][2])+((Atir[14][0]*Cik[14][0][2])+(
      Atir[14][1]*Cik[14][1][2])))+(((Otkr[14][1]*rk[5][0])-(Otkr[14][0]*
      rk[5][1]))+((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*Wkrpk[14][0]))));
    Atir[15][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[6][2])-(Otkr[5][2]*ri[6][1]))+((
      Wirk[15][2]*wk[5][1])-(Wirk[15][1]*wk[5][2]))));
    Atir[15][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[6][0])-(Otkr[5][0]*ri[6][2]))+((
      Wirk[15][0]*wk[5][2])-(Wirk[15][2]*wk[5][0]))));
    Atir[15][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[6][1])-(Otkr[5][1]*ri[6][0]))+((
      Wirk[15][1]*wk[5][0])-(Wirk[15][0]*wk[5][1]))));
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
      Atkr[16][1]*Cik[17][1][0])))+(((Otkr[17][2]*rk[6][1])-(Otkr[17][1]*
      rk[6][2]))+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*Wkrpk[17][1]))));
    Atkr[17][1] = (((Atkr[16][2]*Cik[17][2][1])+((Atkr[16][0]*Cik[17][0][1])+(
      Atkr[16][1]*Cik[17][1][1])))+(((Otkr[17][0]*rk[6][2])-(Otkr[17][2]*
      rk[6][0]))+((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
    Atkr[17][2] = (((Atkr[16][2]*Cik[17][2][2])+((Atkr[16][0]*Cik[17][0][2])+(
      Atkr[16][1]*Cik[17][1][2])))+(((Otkr[17][1]*rk[6][0])-(Otkr[17][0]*
      rk[6][1]))+((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*Wkrpk[17][0]))));
    Atir[18][0] = (Atkr[17][0]+(((Otkr[17][1]*ri[7][2])-(Otkr[17][2]*ri[7][1]))+
      ((Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
    Atir[18][1] = (Atkr[17][1]+(((Otkr[17][2]*ri[7][0])-(Otkr[17][0]*ri[7][2]))+
      ((Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
    Atir[18][2] = (Atkr[17][2]+(((Otkr[17][0]*ri[7][1])-(Otkr[17][1]*ri[7][0]))+
      ((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*wk[17][1]))));
    Atkr[18][0] = ((Atir[18][0]+((2.*((Vik[18][2]*wk[17][1])-(Vik[18][1]*
      wk[17][2])))+(((Otkr[17][1]*rpp[18][2])-(Otkr[17][2]*rpp[18][1]))+((
      wk[17][1]*Wkrpk[18][2])-(wk[17][2]*Wkrpk[18][1])))))+(pin[18][0]*
      udotin[18]));
    Atkr[18][1] = ((Atir[18][1]+((2.*((Vik[18][0]*wk[17][2])-(Vik[18][2]*
      wk[17][0])))+(((Otkr[17][2]*rpp[18][0])-(Otkr[17][0]*rpp[18][2]))+((
      wk[17][2]*Wkrpk[18][0])-(wk[17][0]*Wkrpk[18][2])))))+(pin[18][1]*
      udotin[18]));
    Atkr[18][2] = ((Atir[18][2]+((2.*((Vik[18][1]*wk[17][0])-(Vik[18][0]*
      wk[17][1])))+(((Otkr[17][0]*rpp[18][1])-(Otkr[17][1]*rpp[18][0]))+((
      wk[17][0]*Wkrpk[18][1])-(wk[17][1]*Wkrpk[18][0])))))+(pin[18][2]*
      udotin[18]));
    Atkr[19][0] = ((Atkr[18][0]+((2.*((Vik[19][2]*wk[17][1])-(Vik[19][1]*
      wk[17][2])))+(((Otkr[17][1]*rpp[19][2])-(Otkr[17][2]*rpp[19][1]))+((
      wk[17][1]*Wkrpk[19][2])-(wk[17][2]*Wkrpk[19][1])))))+(pin[19][0]*
      udotin[19]));
    Atkr[19][1] = ((Atkr[18][1]+((2.*((Vik[19][0]*wk[17][2])-(Vik[19][2]*
      wk[17][0])))+(((Otkr[17][2]*rpp[19][0])-(Otkr[17][0]*rpp[19][2]))+((
      wk[17][2]*Wkrpk[19][0])-(wk[17][0]*Wkrpk[19][2])))))+(pin[19][1]*
      udotin[19]));
    Atkr[19][2] = ((Atkr[18][2]+((2.*((Vik[19][1]*wk[17][0])-(Vik[19][0]*
      wk[17][1])))+(((Otkr[17][0]*rpp[19][1])-(Otkr[17][1]*rpp[19][0]))+((
      wk[17][0]*Wkrpk[19][1])-(wk[17][1]*Wkrpk[19][0])))))+(pin[19][2]*
      udotin[19]));
    Atkr[20][0] = (((Atkr[19][2]*Cik[20][2][0])+((Atkr[19][0]*Cik[20][0][0])+(
      Atkr[19][1]*Cik[20][1][0])))+(((Otkr[20][2]*rk[7][1])-(Otkr[20][1]*
      rk[7][2]))+((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
    Atkr[20][1] = (((Atkr[19][2]*Cik[20][2][1])+((Atkr[19][0]*Cik[20][0][1])+(
      Atkr[19][1]*Cik[20][1][1])))+(((Otkr[20][0]*rk[7][2])-(Otkr[20][2]*
      rk[7][0]))+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*Wkrpk[20][2]))));
    Atkr[20][2] = (((Atkr[19][2]*Cik[20][2][2])+((Atkr[19][0]*Cik[20][0][2])+(
      Atkr[19][1]*Cik[20][1][2])))+(((Otkr[20][1]*rk[7][0])-(Otkr[20][0]*
      rk[7][1]))+((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*Wkrpk[20][0]))));
    Atir[21][0] = (Atkr[20][0]+(((Otkr[20][1]*ri[8][2])-(Otkr[20][2]*ri[8][1]))+
      ((Wirk[21][2]*wk[20][1])-(Wirk[21][1]*wk[20][2]))));
    Atir[21][1] = (Atkr[20][1]+(((Otkr[20][2]*ri[8][0])-(Otkr[20][0]*ri[8][2]))+
      ((Wirk[21][0]*wk[20][2])-(Wirk[21][2]*wk[20][0]))));
    Atir[21][2] = (Atkr[20][2]+(((Otkr[20][0]*ri[8][1])-(Otkr[20][1]*ri[8][0]))+
      ((Wirk[21][1]*wk[20][0])-(Wirk[21][0]*wk[20][1]))));
    Atkr[21][0] = (((Atir[21][2]*Cik[21][2][0])+((Atir[21][0]*Cik[21][0][0])+(
      Atir[21][1]*Cik[21][1][0])))+(((Otkr[21][2]*rk[8][1])-(Otkr[21][1]*
      rk[8][2]))+((wk[21][1]*Wkrpk[21][2])-(wk[21][2]*Wkrpk[21][1]))));
    Atkr[21][1] = (((Atir[21][2]*Cik[21][2][1])+((Atir[21][0]*Cik[21][0][1])+(
      Atir[21][1]*Cik[21][1][1])))+(((Otkr[21][0]*rk[8][2])-(Otkr[21][2]*
      rk[8][0]))+((wk[21][2]*Wkrpk[21][0])-(wk[21][0]*Wkrpk[21][2]))));
    Atkr[21][2] = (((Atir[21][2]*Cik[21][2][2])+((Atir[21][0]*Cik[21][0][2])+(
      Atir[21][1]*Cik[21][1][2])))+(((Otkr[21][1]*rk[8][0])-(Otkr[21][0]*
      rk[8][1]))+((wk[21][0]*Wkrpk[21][1])-(wk[21][1]*Wkrpk[21][0]))));
    Atir[22][0] = (Atkr[21][0]+(((Otkr[21][1]*ri[9][2])-(Otkr[21][2]*ri[9][1]))+
      ((Wirk[22][2]*wk[21][1])-(Wirk[22][1]*wk[21][2]))));
    Atir[22][1] = (Atkr[21][1]+(((Otkr[21][2]*ri[9][0])-(Otkr[21][0]*ri[9][2]))+
      ((Wirk[22][0]*wk[21][2])-(Wirk[22][2]*wk[21][0]))));
    Atir[22][2] = (Atkr[21][2]+(((Otkr[21][0]*ri[9][1])-(Otkr[21][1]*ri[9][0]))+
      ((Wirk[22][1]*wk[21][0])-(Wirk[22][0]*wk[21][1]))));
    Atkr[22][0] = (((Atir[22][2]*Cik[22][2][0])+((Atir[22][0]*Cik[22][0][0])+(
      Atir[22][1]*Cik[22][1][0])))+(((Otkr[22][2]*rk[9][1])-(Otkr[22][1]*
      rk[9][2]))+((wk[22][1]*Wkrpk[22][2])-(wk[22][2]*Wkrpk[22][1]))));
    Atkr[22][1] = (((Atir[22][2]*Cik[22][2][1])+((Atir[22][0]*Cik[22][0][1])+(
      Atir[22][1]*Cik[22][1][1])))+(((Otkr[22][0]*rk[9][2])-(Otkr[22][2]*
      rk[9][0]))+((wk[22][2]*Wkrpk[22][0])-(wk[22][0]*Wkrpk[22][2]))));
    Atkr[22][2] = (((Atir[22][2]*Cik[22][2][2])+((Atir[22][0]*Cik[22][0][2])+(
      Atir[22][1]*Cik[22][1][2])))+(((Otkr[22][1]*rk[9][0])-(Otkr[22][0]*
      rk[9][1]))+((wk[22][0]*Wkrpk[22][1])-(wk[22][1]*Wkrpk[22][0]))));
    Atir[23][0] = (Atkr[22][0]+(((Otkr[22][1]*ri[10][2])-(Otkr[22][2]*ri[10][1])
      )+((Wirk[23][2]*wk[22][1])-(Wirk[23][1]*wk[22][2]))));
    Atir[23][1] = (Atkr[22][1]+(((Otkr[22][2]*ri[10][0])-(Otkr[22][0]*ri[10][2])
      )+((Wirk[23][0]*wk[22][2])-(Wirk[23][2]*wk[22][0]))));
    Atir[23][2] = (Atkr[22][2]+(((Otkr[22][0]*ri[10][1])-(Otkr[22][1]*ri[10][0])
      )+((Wirk[23][1]*wk[22][0])-(Wirk[23][0]*wk[22][1]))));
    Atkr[23][0] = (((Atir[23][2]*Cik[23][2][0])+((Atir[23][0]*Cik[23][0][0])+(
      Atir[23][1]*Cik[23][1][0])))+(((Otkr[23][2]*rk[10][1])-(Otkr[23][1]*
      rk[10][2]))+((wk[23][1]*Wkrpk[23][2])-(wk[23][2]*Wkrpk[23][1]))));
    Atkr[23][1] = (((Atir[23][2]*Cik[23][2][1])+((Atir[23][0]*Cik[23][0][1])+(
      Atir[23][1]*Cik[23][1][1])))+(((Otkr[23][0]*rk[10][2])-(Otkr[23][2]*
      rk[10][0]))+((wk[23][2]*Wkrpk[23][0])-(wk[23][0]*Wkrpk[23][2]))));
    Atkr[23][2] = (((Atir[23][2]*Cik[23][2][2])+((Atir[23][0]*Cik[23][0][2])+(
      Atir[23][1]*Cik[23][1][2])))+(((Otkr[23][1]*rk[10][0])-(Otkr[23][0]*
      rk[10][1]))+((wk[23][0]*Wkrpk[23][1])-(wk[23][1]*Wkrpk[23][0]))));
    Atir[24][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[11][2])-(Otkr[5][2]*ri[11][1]))+(
      (Wirk[24][2]*wk[5][1])-(Wirk[24][1]*wk[5][2]))));
    Atir[24][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[11][0])-(Otkr[5][0]*ri[11][2]))+(
      (Wirk[24][0]*wk[5][2])-(Wirk[24][2]*wk[5][0]))));
    Atir[24][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[11][1])-(Otkr[5][1]*ri[11][0]))+(
      (Wirk[24][1]*wk[5][0])-(Wirk[24][0]*wk[5][1]))));
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
    Atkr[26][0] = (((Atkr[25][2]*Cik[26][2][0])+((Atkr[25][0]*Cik[26][0][0])+(
      Atkr[25][1]*Cik[26][1][0])))+(((Otkr[26][2]*rk[11][1])-(Otkr[26][1]*
      rk[11][2]))+((wk[26][1]*Wkrpk[26][2])-(wk[26][2]*Wkrpk[26][1]))));
    Atkr[26][1] = (((Atkr[25][2]*Cik[26][2][1])+((Atkr[25][0]*Cik[26][0][1])+(
      Atkr[25][1]*Cik[26][1][1])))+(((Otkr[26][0]*rk[11][2])-(Otkr[26][2]*
      rk[11][0]))+((wk[26][2]*Wkrpk[26][0])-(wk[26][0]*Wkrpk[26][2]))));
    Atkr[26][2] = (((Atkr[25][2]*Cik[26][2][2])+((Atkr[25][0]*Cik[26][0][2])+(
      Atkr[25][1]*Cik[26][1][2])))+(((Otkr[26][1]*rk[11][0])-(Otkr[26][0]*
      rk[11][1]))+((wk[26][0]*Wkrpk[26][1])-(wk[26][1]*Wkrpk[26][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = ((mfk[0][0]+ufk[0][0])+(mk[0]*(gk[5][0]-Atkr[5][0])));
    fstarr[5][1] = ((mfk[0][1]+ufk[0][1])+(mk[0]*(gk[5][1]-Atkr[5][1])));
    fstarr[5][2] = ((mfk[0][2]+ufk[0][2])+(mk[0]*(gk[5][2]-Atkr[5][2])));
    fstarr[8][0] = ((mfk[1][0]+ufk[1][0])+(mk[1]*(gk[8][0]-Atkr[8][0])));
    fstarr[8][1] = ((mfk[1][1]+ufk[1][1])+(mk[1]*(gk[8][1]-Atkr[8][1])));
    fstarr[8][2] = ((mfk[1][2]+ufk[1][2])+(mk[1]*(gk[8][2]-Atkr[8][2])));
    fstarr[11][0] = ((mfk[2][0]+ufk[2][0])+(mk[2]*(gk[11][0]-Atkr[11][0])));
    fstarr[11][1] = ((mfk[2][1]+ufk[2][1])+(mk[2]*(gk[11][1]-Atkr[11][1])));
    fstarr[11][2] = ((mfk[2][2]+ufk[2][2])+(mk[2]*(gk[11][2]-Atkr[11][2])));
    fstarr[12][0] = ((mfk[3][0]+ufk[3][0])+(mk[3]*(gk[12][0]-Atkr[12][0])));
    fstarr[12][1] = ((mfk[3][1]+ufk[3][1])+(mk[3]*(gk[12][1]-Atkr[12][1])));
    fstarr[12][2] = ((mfk[3][2]+ufk[3][2])+(mk[3]*(gk[12][2]-Atkr[12][2])));
    fstarr[13][0] = ((mfk[4][0]+ufk[4][0])+(mk[4]*(gk[13][0]-Atkr[13][0])));
    fstarr[13][1] = ((mfk[4][1]+ufk[4][1])+(mk[4]*(gk[13][1]-Atkr[13][1])));
    fstarr[13][2] = ((mfk[4][2]+ufk[4][2])+(mk[4]*(gk[13][2]-Atkr[13][2])));
    fstarr[14][0] = ((mfk[5][0]+ufk[5][0])+(mk[5]*(gk[14][0]-Atkr[14][0])));
    fstarr[14][1] = ((mfk[5][1]+ufk[5][1])+(mk[5]*(gk[14][1]-Atkr[14][1])));
    fstarr[14][2] = ((mfk[5][2]+ufk[5][2])+(mk[5]*(gk[14][2]-Atkr[14][2])));
    fstarr[17][0] = ((mfk[6][0]+ufk[6][0])+(mk[6]*(gk[17][0]-Atkr[17][0])));
    fstarr[17][1] = ((mfk[6][1]+ufk[6][1])+(mk[6]*(gk[17][1]-Atkr[17][1])));
    fstarr[17][2] = ((mfk[6][2]+ufk[6][2])+(mk[6]*(gk[17][2]-Atkr[17][2])));
    fstarr[20][0] = ((mfk[7][0]+ufk[7][0])+(mk[7]*(gk[20][0]-Atkr[20][0])));
    fstarr[20][1] = ((mfk[7][1]+ufk[7][1])+(mk[7]*(gk[20][1]-Atkr[20][1])));
    fstarr[20][2] = ((mfk[7][2]+ufk[7][2])+(mk[7]*(gk[20][2]-Atkr[20][2])));
    fstarr[21][0] = ((mfk[8][0]+ufk[8][0])+(mk[8]*(gk[21][0]-Atkr[21][0])));
    fstarr[21][1] = ((mfk[8][1]+ufk[8][1])+(mk[8]*(gk[21][1]-Atkr[21][1])));
    fstarr[21][2] = ((mfk[8][2]+ufk[8][2])+(mk[8]*(gk[21][2]-Atkr[21][2])));
    fstarr[22][0] = ((mfk[9][0]+ufk[9][0])+(mk[9]*(gk[22][0]-Atkr[22][0])));
    fstarr[22][1] = ((mfk[9][1]+ufk[9][1])+(mk[9]*(gk[22][1]-Atkr[22][1])));
    fstarr[22][2] = ((mfk[9][2]+ufk[9][2])+(mk[9]*(gk[22][2]-Atkr[22][2])));
    fstarr[23][0] = ((mfk[10][0]+ufk[10][0])+(mk[10]*(gk[23][0]-Atkr[23][0])));
    fstarr[23][1] = ((mfk[10][1]+ufk[10][1])+(mk[10]*(gk[23][1]-Atkr[23][1])));
    fstarr[23][2] = ((mfk[10][2]+ufk[10][2])+(mk[10]*(gk[23][2]-Atkr[23][2])));
    fstarr[26][0] = ((mfk[11][0]+ufk[11][0])+(mk[11]*(gk[26][0]-Atkr[26][0])));
    fstarr[26][1] = ((mfk[11][1]+ufk[11][1])+(mk[11]*(gk[26][1]-Atkr[26][1])));
    fstarr[26][2] = ((mfk[11][2]+ufk[11][2])+(mk[11]*(gk[26][2]-Atkr[26][2])));
    tstarr[5][0] = ((mtk[0][0]+utk[0][0])-(WkIkWk[5][0]+((ik[0][0][2]*Otkr[5][2]
      )+((ik[0][0][0]*Otkr[5][0])+(ik[0][0][1]*Otkr[5][1])))));
    tstarr[5][1] = ((mtk[0][1]+utk[0][1])-(WkIkWk[5][1]+((ik[0][1][2]*Otkr[5][2]
      )+((ik[0][1][0]*Otkr[5][0])+(ik[0][1][1]*Otkr[5][1])))));
    tstarr[5][2] = ((mtk[0][2]+utk[0][2])-(WkIkWk[5][2]+((ik[0][2][2]*Otkr[5][2]
      )+((ik[0][2][0]*Otkr[5][0])+(ik[0][2][1]*Otkr[5][1])))));
    tstarr[8][0] = ((mtk[1][0]+utk[1][0])-(WkIkWk[8][0]+((ik[1][0][2]*Otkr[8][2]
      )+((ik[1][0][0]*Otkr[8][0])+(ik[1][0][1]*Otkr[8][1])))));
    tstarr[8][1] = ((mtk[1][1]+utk[1][1])-(WkIkWk[8][1]+((ik[1][1][2]*Otkr[8][2]
      )+((ik[1][1][0]*Otkr[8][0])+(ik[1][1][1]*Otkr[8][1])))));
    tstarr[8][2] = ((mtk[1][2]+utk[1][2])-(WkIkWk[8][2]+((ik[1][2][2]*Otkr[8][2]
      )+((ik[1][2][0]*Otkr[8][0])+(ik[1][2][1]*Otkr[8][1])))));
    tstarr[11][0] = ((mtk[2][0]+utk[2][0])-(WkIkWk[11][0]+((ik[2][0][2]*
      Otkr[11][2])+((ik[2][0][0]*Otkr[11][0])+(ik[2][0][1]*Otkr[11][1])))));
    tstarr[11][1] = ((mtk[2][1]+utk[2][1])-(WkIkWk[11][1]+((ik[2][1][2]*
      Otkr[11][2])+((ik[2][1][0]*Otkr[11][0])+(ik[2][1][1]*Otkr[11][1])))));
    tstarr[11][2] = ((mtk[2][2]+utk[2][2])-(WkIkWk[11][2]+((ik[2][2][2]*
      Otkr[11][2])+((ik[2][2][0]*Otkr[11][0])+(ik[2][2][1]*Otkr[11][1])))));
    tstarr[12][0] = ((mtk[3][0]+utk[3][0])-(WkIkWk[12][0]+((ik[3][0][2]*
      Otkr[12][2])+((ik[3][0][0]*Otkr[12][0])+(ik[3][0][1]*Otkr[12][1])))));
    tstarr[12][1] = ((mtk[3][1]+utk[3][1])-(WkIkWk[12][1]+((ik[3][1][2]*
      Otkr[12][2])+((ik[3][1][0]*Otkr[12][0])+(ik[3][1][1]*Otkr[12][1])))));
    tstarr[12][2] = ((mtk[3][2]+utk[3][2])-(WkIkWk[12][2]+((ik[3][2][2]*
      Otkr[12][2])+((ik[3][2][0]*Otkr[12][0])+(ik[3][2][1]*Otkr[12][1])))));
    tstarr[13][0] = ((mtk[4][0]+utk[4][0])-(WkIkWk[13][0]+((ik[4][0][2]*
      Otkr[13][2])+((ik[4][0][0]*Otkr[13][0])+(ik[4][0][1]*Otkr[13][1])))));
    tstarr[13][1] = ((mtk[4][1]+utk[4][1])-(WkIkWk[13][1]+((ik[4][1][2]*
      Otkr[13][2])+((ik[4][1][0]*Otkr[13][0])+(ik[4][1][1]*Otkr[13][1])))));
    tstarr[13][2] = ((mtk[4][2]+utk[4][2])-(WkIkWk[13][2]+((ik[4][2][2]*
      Otkr[13][2])+((ik[4][2][0]*Otkr[13][0])+(ik[4][2][1]*Otkr[13][1])))));
    tstarr[14][0] = ((mtk[5][0]+utk[5][0])-(WkIkWk[14][0]+((ik[5][0][2]*
      Otkr[14][2])+((ik[5][0][0]*Otkr[14][0])+(ik[5][0][1]*Otkr[14][1])))));
    tstarr[14][1] = ((mtk[5][1]+utk[5][1])-(WkIkWk[14][1]+((ik[5][1][2]*
      Otkr[14][2])+((ik[5][1][0]*Otkr[14][0])+(ik[5][1][1]*Otkr[14][1])))));
    tstarr[14][2] = ((mtk[5][2]+utk[5][2])-(WkIkWk[14][2]+((ik[5][2][2]*
      Otkr[14][2])+((ik[5][2][0]*Otkr[14][0])+(ik[5][2][1]*Otkr[14][1])))));
    tstarr[17][0] = ((mtk[6][0]+utk[6][0])-(WkIkWk[17][0]+((ik[6][0][2]*
      Otkr[17][2])+((ik[6][0][0]*Otkr[17][0])+(ik[6][0][1]*Otkr[17][1])))));
    tstarr[17][1] = ((mtk[6][1]+utk[6][1])-(WkIkWk[17][1]+((ik[6][1][2]*
      Otkr[17][2])+((ik[6][1][0]*Otkr[17][0])+(ik[6][1][1]*Otkr[17][1])))));
    tstarr[17][2] = ((mtk[6][2]+utk[6][2])-(WkIkWk[17][2]+((ik[6][2][2]*
      Otkr[17][2])+((ik[6][2][0]*Otkr[17][0])+(ik[6][2][1]*Otkr[17][1])))));
    tstarr[20][0] = ((mtk[7][0]+utk[7][0])-(WkIkWk[20][0]+((ik[7][0][2]*
      Otkr[20][2])+((ik[7][0][0]*Otkr[20][0])+(ik[7][0][1]*Otkr[20][1])))));
    tstarr[20][1] = ((mtk[7][1]+utk[7][1])-(WkIkWk[20][1]+((ik[7][1][2]*
      Otkr[20][2])+((ik[7][1][0]*Otkr[20][0])+(ik[7][1][1]*Otkr[20][1])))));
    tstarr[20][2] = ((mtk[7][2]+utk[7][2])-(WkIkWk[20][2]+((ik[7][2][2]*
      Otkr[20][2])+((ik[7][2][0]*Otkr[20][0])+(ik[7][2][1]*Otkr[20][1])))));
    tstarr[21][0] = ((mtk[8][0]+utk[8][0])-(WkIkWk[21][0]+((ik[8][0][2]*
      Otkr[21][2])+((ik[8][0][0]*Otkr[21][0])+(ik[8][0][1]*Otkr[21][1])))));
    tstarr[21][1] = ((mtk[8][1]+utk[8][1])-(WkIkWk[21][1]+((ik[8][1][2]*
      Otkr[21][2])+((ik[8][1][0]*Otkr[21][0])+(ik[8][1][1]*Otkr[21][1])))));
    tstarr[21][2] = ((mtk[8][2]+utk[8][2])-(WkIkWk[21][2]+((ik[8][2][2]*
      Otkr[21][2])+((ik[8][2][0]*Otkr[21][0])+(ik[8][2][1]*Otkr[21][1])))));
    tstarr[22][0] = ((mtk[9][0]+utk[9][0])-(WkIkWk[22][0]+((ik[9][0][2]*
      Otkr[22][2])+((ik[9][0][0]*Otkr[22][0])+(ik[9][0][1]*Otkr[22][1])))));
    tstarr[22][1] = ((mtk[9][1]+utk[9][1])-(WkIkWk[22][1]+((ik[9][1][2]*
      Otkr[22][2])+((ik[9][1][0]*Otkr[22][0])+(ik[9][1][1]*Otkr[22][1])))));
    tstarr[22][2] = ((mtk[9][2]+utk[9][2])-(WkIkWk[22][2]+((ik[9][2][2]*
      Otkr[22][2])+((ik[9][2][0]*Otkr[22][0])+(ik[9][2][1]*Otkr[22][1])))));
    tstarr[23][0] = ((mtk[10][0]+utk[10][0])-(WkIkWk[23][0]+((ik[10][0][2]*
      Otkr[23][2])+((ik[10][0][0]*Otkr[23][0])+(ik[10][0][1]*Otkr[23][1])))));
    tstarr[23][1] = ((mtk[10][1]+utk[10][1])-(WkIkWk[23][1]+((ik[10][1][2]*
      Otkr[23][2])+((ik[10][1][0]*Otkr[23][0])+(ik[10][1][1]*Otkr[23][1])))));
    tstarr[23][2] = ((mtk[10][2]+utk[10][2])-(WkIkWk[23][2]+((ik[10][2][2]*
      Otkr[23][2])+((ik[10][2][0]*Otkr[23][0])+(ik[10][2][1]*Otkr[23][1])))));
    tstarr[26][0] = ((mtk[11][0]+utk[11][0])-(WkIkWk[26][0]+((ik[11][0][2]*
      Otkr[26][2])+((ik[11][0][0]*Otkr[26][0])+(ik[11][0][1]*Otkr[26][1])))));
    tstarr[26][1] = ((mtk[11][1]+utk[11][1])-(WkIkWk[26][1]+((ik[11][1][2]*
      Otkr[26][2])+((ik[11][1][0]*Otkr[26][0])+(ik[11][1][1]*Otkr[26][1])))));
    tstarr[26][2] = ((mtk[11][2]+utk[11][2])-(WkIkWk[26][2]+((ik[11][2][2]*
      Otkr[26][2])+((ik[11][2][0]*Otkr[26][0])+(ik[11][2][1]*Otkr[26][1])))));
/*
Now calculate the torques
*/
    sddovpk();
    temp[0] = (((fstarr[12][2]*Vpk[0][12][2])+((fstarr[12][0]*Vpk[0][12][0])+(
      fstarr[12][1]*Vpk[0][12][1])))+(((fstarr[11][2]*Vpk[0][11][2])+((
      fstarr[11][0]*Vpk[0][11][0])+(fstarr[11][1]*Vpk[0][11][1])))+(((
      fstarr[5][2]*Vpk[0][5][2])+((fstarr[5][0]*Vpk[0][5][0])+(fstarr[5][1]*
      Vpk[0][5][1])))+((fstarr[8][2]*Vpk[0][8][2])+((fstarr[8][0]*Vpk[0][8][0])+
      (fstarr[8][1]*Vpk[0][8][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[0][20][2])+((fstarr[20][0]*Vpk[0][20][0])+(
      fstarr[20][1]*Vpk[0][20][1])))+(((fstarr[17][2]*Vpk[0][17][2])+((
      fstarr[17][0]*Vpk[0][17][0])+(fstarr[17][1]*Vpk[0][17][1])))+(((
      fstarr[14][2]*Vpk[0][14][2])+((fstarr[14][0]*Vpk[0][14][0])+(fstarr[14][1]
      *Vpk[0][14][1])))+(((fstarr[13][2]*Vpk[0][13][2])+((fstarr[13][0]*
      Vpk[0][13][0])+(fstarr[13][1]*Vpk[0][13][1])))+temp[0]))));
    trqout[0] = -((mtau[0]+utau[0])+(((fstarr[26][2]*Vpk[0][26][2])+((
      fstarr[26][0]*Vpk[0][26][0])+(fstarr[26][1]*Vpk[0][26][1])))+(((
      fstarr[23][2]*Vpk[0][23][2])+((fstarr[23][0]*Vpk[0][23][0])+(fstarr[23][1]
      *Vpk[0][23][1])))+(((fstarr[22][2]*Vpk[0][22][2])+((fstarr[22][0]*
      Vpk[0][22][0])+(fstarr[22][1]*Vpk[0][22][1])))+(((fstarr[21][2]*
      Vpk[0][21][2])+((fstarr[21][0]*Vpk[0][21][0])+(fstarr[21][1]*Vpk[0][21][1]
      )))+temp[1])))));
    temp[0] = (((fstarr[12][2]*Vpk[1][12][2])+((fstarr[12][0]*Vpk[1][12][0])+(
      fstarr[12][1]*Vpk[1][12][1])))+(((fstarr[11][2]*Vpk[1][11][2])+((
      fstarr[11][0]*Vpk[1][11][0])+(fstarr[11][1]*Vpk[1][11][1])))+(((
      fstarr[5][2]*Vpk[1][5][2])+((fstarr[5][0]*Vpk[1][5][0])+(fstarr[5][1]*
      Vpk[1][5][1])))+((fstarr[8][2]*Vpk[1][8][2])+((fstarr[8][0]*Vpk[1][8][0])+
      (fstarr[8][1]*Vpk[1][8][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[1][20][2])+((fstarr[20][0]*Vpk[1][20][0])+(
      fstarr[20][1]*Vpk[1][20][1])))+(((fstarr[17][2]*Vpk[1][17][2])+((
      fstarr[17][0]*Vpk[1][17][0])+(fstarr[17][1]*Vpk[1][17][1])))+(((
      fstarr[14][2]*Vpk[1][14][2])+((fstarr[14][0]*Vpk[1][14][0])+(fstarr[14][1]
      *Vpk[1][14][1])))+(((fstarr[13][2]*Vpk[1][13][2])+((fstarr[13][0]*
      Vpk[1][13][0])+(fstarr[13][1]*Vpk[1][13][1])))+temp[0]))));
    trqout[1] = -((mtau[1]+utau[1])+(((fstarr[26][2]*Vpk[1][26][2])+((
      fstarr[26][0]*Vpk[1][26][0])+(fstarr[26][1]*Vpk[1][26][1])))+(((
      fstarr[23][2]*Vpk[1][23][2])+((fstarr[23][0]*Vpk[1][23][0])+(fstarr[23][1]
      *Vpk[1][23][1])))+(((fstarr[22][2]*Vpk[1][22][2])+((fstarr[22][0]*
      Vpk[1][22][0])+(fstarr[22][1]*Vpk[1][22][1])))+(((fstarr[21][2]*
      Vpk[1][21][2])+((fstarr[21][0]*Vpk[1][21][0])+(fstarr[21][1]*Vpk[1][21][1]
      )))+temp[1])))));
    temp[0] = (((fstarr[12][2]*Vpk[2][12][2])+((fstarr[12][0]*Vpk[2][12][0])+(
      fstarr[12][1]*Vpk[2][12][1])))+(((fstarr[11][2]*Vpk[2][11][2])+((
      fstarr[11][0]*Vpk[2][11][0])+(fstarr[11][1]*Vpk[2][11][1])))+(((
      fstarr[5][2]*Vpk[2][5][2])+((fstarr[5][0]*Vpk[2][5][0])+(fstarr[5][1]*
      Vpk[2][5][1])))+((fstarr[8][2]*Vpk[2][8][2])+((fstarr[8][0]*Vpk[2][8][0])+
      (fstarr[8][1]*Vpk[2][8][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[2][20][2])+((fstarr[20][0]*Vpk[2][20][0])+(
      fstarr[20][1]*Vpk[2][20][1])))+(((fstarr[17][2]*Vpk[2][17][2])+((
      fstarr[17][0]*Vpk[2][17][0])+(fstarr[17][1]*Vpk[2][17][1])))+(((
      fstarr[14][2]*Vpk[2][14][2])+((fstarr[14][0]*Vpk[2][14][0])+(fstarr[14][1]
      *Vpk[2][14][1])))+(((fstarr[13][2]*Vpk[2][13][2])+((fstarr[13][0]*
      Vpk[2][13][0])+(fstarr[13][1]*Vpk[2][13][1])))+temp[0]))));
    trqout[2] = -((mtau[2]+utau[2])+(((fstarr[26][2]*Vpk[2][26][2])+((
      fstarr[26][0]*Vpk[2][26][0])+(fstarr[26][1]*Vpk[2][26][1])))+(((
      fstarr[23][2]*Vpk[2][23][2])+((fstarr[23][0]*Vpk[2][23][0])+(fstarr[23][1]
      *Vpk[2][23][1])))+(((fstarr[22][2]*Vpk[2][22][2])+((fstarr[22][0]*
      Vpk[2][22][0])+(fstarr[22][1]*Vpk[2][22][1])))+(((fstarr[21][2]*
      Vpk[2][21][2])+((fstarr[21][0]*Vpk[2][21][0])+(fstarr[21][1]*Vpk[2][21][1]
      )))+temp[1])))));
    temp[0] = ((((fstarr[5][2]*Vpk[3][5][2])+((fstarr[5][0]*Vpk[3][5][0])+(
      fstarr[5][1]*Vpk[3][5][1])))+((tstarr[5][2]*Wpk[3][5][2])+((tstarr[5][0]*
      Wpk[3][5][0])+(tstarr[5][1]*Wpk[3][5][1]))))+(((fstarr[8][2]*Vpk[3][8][2])
      +((fstarr[8][0]*Vpk[3][8][0])+(fstarr[8][1]*Vpk[3][8][1])))+((tstarr[8][2]
      *Wpk[3][8][2])+((tstarr[8][0]*Wpk[3][8][0])+(tstarr[8][1]*Wpk[3][8][1]))))
      );
    temp[1] = ((((fstarr[12][2]*Vpk[3][12][2])+((fstarr[12][0]*Vpk[3][12][0])+(
      fstarr[12][1]*Vpk[3][12][1])))+((tstarr[12][2]*Wpk[3][12][2])+((
      tstarr[12][0]*Wpk[3][12][0])+(tstarr[12][1]*Wpk[3][12][1]))))+((((
      fstarr[11][2]*Vpk[3][11][2])+((fstarr[11][0]*Vpk[3][11][0])+(fstarr[11][1]
      *Vpk[3][11][1])))+((tstarr[11][2]*Wpk[3][11][2])+((tstarr[11][0]*
      Wpk[3][11][0])+(tstarr[11][1]*Wpk[3][11][1]))))+temp[0]));
    temp[2] = ((((fstarr[14][2]*Vpk[3][14][2])+((fstarr[14][0]*Vpk[3][14][0])+(
      fstarr[14][1]*Vpk[3][14][1])))+((tstarr[14][2]*Wpk[3][14][2])+((
      tstarr[14][0]*Wpk[3][14][0])+(tstarr[14][1]*Wpk[3][14][1]))))+((((
      fstarr[13][2]*Vpk[3][13][2])+((fstarr[13][0]*Vpk[3][13][0])+(fstarr[13][1]
      *Vpk[3][13][1])))+((tstarr[13][2]*Wpk[3][13][2])+((tstarr[13][0]*
      Wpk[3][13][0])+(tstarr[13][1]*Wpk[3][13][1]))))+temp[1]));
    temp[3] = ((((fstarr[20][2]*Vpk[3][20][2])+((fstarr[20][0]*Vpk[3][20][0])+(
      fstarr[20][1]*Vpk[3][20][1])))+((tstarr[20][2]*Wpk[3][20][2])+((
      tstarr[20][0]*Wpk[3][20][0])+(tstarr[20][1]*Wpk[3][20][1]))))+((((
      fstarr[17][2]*Vpk[3][17][2])+((fstarr[17][0]*Vpk[3][17][0])+(fstarr[17][1]
      *Vpk[3][17][1])))+((tstarr[17][2]*Wpk[3][17][2])+((tstarr[17][0]*
      Wpk[3][17][0])+(tstarr[17][1]*Wpk[3][17][1]))))+temp[2]));
    temp[4] = ((((fstarr[22][2]*Vpk[3][22][2])+((fstarr[22][0]*Vpk[3][22][0])+(
      fstarr[22][1]*Vpk[3][22][1])))+((tstarr[22][2]*Wpk[3][22][2])+((
      tstarr[22][0]*Wpk[3][22][0])+(tstarr[22][1]*Wpk[3][22][1]))))+((((
      fstarr[21][2]*Vpk[3][21][2])+((fstarr[21][0]*Vpk[3][21][0])+(fstarr[21][1]
      *Vpk[3][21][1])))+((tstarr[21][2]*Wpk[3][21][2])+((tstarr[21][0]*
      Wpk[3][21][0])+(tstarr[21][1]*Wpk[3][21][1]))))+temp[3]));
    trqout[3] = -((mtau[3]+utau[3])+((((fstarr[26][2]*Vpk[3][26][2])+((
      fstarr[26][0]*Vpk[3][26][0])+(fstarr[26][1]*Vpk[3][26][1])))+((
      tstarr[26][2]*Wpk[3][26][2])+((tstarr[26][0]*Wpk[3][26][0])+(tstarr[26][1]
      *Wpk[3][26][1]))))+((((fstarr[23][2]*Vpk[3][23][2])+((fstarr[23][0]*
      Vpk[3][23][0])+(fstarr[23][1]*Vpk[3][23][1])))+((tstarr[23][2]*
      Wpk[3][23][2])+((tstarr[23][0]*Wpk[3][23][0])+(tstarr[23][1]*Wpk[3][23][1]
      ))))+temp[4])));
    temp[0] = ((((fstarr[5][2]*Vpk[4][5][2])+((fstarr[5][0]*Vpk[4][5][0])+(
      fstarr[5][1]*Vpk[4][5][1])))+((tstarr[5][2]*Wpk[4][5][2])+((tstarr[5][0]*
      Wpk[4][5][0])+(tstarr[5][1]*Wpk[4][5][1]))))+(((fstarr[8][2]*Vpk[4][8][2])
      +((fstarr[8][0]*Vpk[4][8][0])+(fstarr[8][1]*Vpk[4][8][1])))+((tstarr[8][2]
      *Wpk[4][8][2])+((tstarr[8][0]*Wpk[4][8][0])+(tstarr[8][1]*Wpk[4][8][1]))))
      );
    temp[1] = ((((fstarr[12][2]*Vpk[4][12][2])+((fstarr[12][0]*Vpk[4][12][0])+(
      fstarr[12][1]*Vpk[4][12][1])))+((tstarr[12][2]*Wpk[4][12][2])+((
      tstarr[12][0]*Wpk[4][12][0])+(tstarr[12][1]*Wpk[4][12][1]))))+((((
      fstarr[11][2]*Vpk[4][11][2])+((fstarr[11][0]*Vpk[4][11][0])+(fstarr[11][1]
      *Vpk[4][11][1])))+((tstarr[11][2]*Wpk[4][11][2])+((tstarr[11][0]*
      Wpk[4][11][0])+(tstarr[11][1]*Wpk[4][11][1]))))+temp[0]));
    temp[2] = ((((fstarr[14][2]*Vpk[4][14][2])+((fstarr[14][0]*Vpk[4][14][0])+(
      fstarr[14][1]*Vpk[4][14][1])))+((tstarr[14][2]*Wpk[4][14][2])+((
      tstarr[14][0]*Wpk[4][14][0])+(tstarr[14][1]*Wpk[4][14][1]))))+((((
      fstarr[13][2]*Vpk[4][13][2])+((fstarr[13][0]*Vpk[4][13][0])+(fstarr[13][1]
      *Vpk[4][13][1])))+((tstarr[13][2]*Wpk[4][13][2])+((tstarr[13][0]*
      Wpk[4][13][0])+(tstarr[13][1]*Wpk[4][13][1]))))+temp[1]));
    temp[3] = ((((fstarr[20][2]*Vpk[4][20][2])+((fstarr[20][0]*Vpk[4][20][0])+(
      fstarr[20][1]*Vpk[4][20][1])))+((tstarr[20][2]*Wpk[4][20][2])+((
      tstarr[20][0]*Wpk[4][20][0])+(tstarr[20][1]*Wpk[4][20][1]))))+((((
      fstarr[17][2]*Vpk[4][17][2])+((fstarr[17][0]*Vpk[4][17][0])+(fstarr[17][1]
      *Vpk[4][17][1])))+((tstarr[17][2]*Wpk[4][17][2])+((tstarr[17][0]*
      Wpk[4][17][0])+(tstarr[17][1]*Wpk[4][17][1]))))+temp[2]));
    temp[4] = ((((fstarr[22][2]*Vpk[4][22][2])+((fstarr[22][0]*Vpk[4][22][0])+(
      fstarr[22][1]*Vpk[4][22][1])))+((tstarr[22][2]*Wpk[4][22][2])+((
      tstarr[22][0]*Wpk[4][22][0])+(tstarr[22][1]*Wpk[4][22][1]))))+((((
      fstarr[21][2]*Vpk[4][21][2])+((fstarr[21][0]*Vpk[4][21][0])+(fstarr[21][1]
      *Vpk[4][21][1])))+((tstarr[21][2]*Wpk[4][21][2])+((tstarr[21][0]*
      Wpk[4][21][0])+(tstarr[21][1]*Wpk[4][21][1]))))+temp[3]));
    trqout[4] = -((mtau[4]+utau[4])+((((fstarr[26][2]*Vpk[4][26][2])+((
      fstarr[26][0]*Vpk[4][26][0])+(fstarr[26][1]*Vpk[4][26][1])))+((
      tstarr[26][2]*Wpk[4][26][2])+((tstarr[26][0]*Wpk[4][26][0])+(tstarr[26][1]
      *Wpk[4][26][1]))))+((((fstarr[23][2]*Vpk[4][23][2])+((fstarr[23][0]*
      Vpk[4][23][0])+(fstarr[23][1]*Vpk[4][23][1])))+((tstarr[23][2]*
      Wpk[4][23][2])+((tstarr[23][0]*Wpk[4][23][0])+(tstarr[23][1]*Wpk[4][23][1]
      ))))+temp[4])));
    temp[0] = ((((fstarr[5][2]*Vpk[5][5][2])+((fstarr[5][0]*Vpk[5][5][0])+(
      fstarr[5][1]*Vpk[5][5][1])))+((pin[2][2]*tstarr[5][2])+((pin[2][0]*
      tstarr[5][0])+(pin[2][1]*tstarr[5][1]))))+(((fstarr[8][2]*Vpk[5][8][2])+((
      fstarr[8][0]*Vpk[5][8][0])+(fstarr[8][1]*Vpk[5][8][1])))+((tstarr[8][2]*
      Wpk[5][8][2])+((tstarr[8][0]*Wpk[5][8][0])+(tstarr[8][1]*Wpk[5][8][1])))))
      ;
    temp[1] = ((((fstarr[12][2]*Vpk[5][12][2])+((fstarr[12][0]*Vpk[5][12][0])+(
      fstarr[12][1]*Vpk[5][12][1])))+((tstarr[12][2]*Wpk[5][12][2])+((
      tstarr[12][0]*Wpk[5][12][0])+(tstarr[12][1]*Wpk[5][12][1]))))+((((
      fstarr[11][2]*Vpk[5][11][2])+((fstarr[11][0]*Vpk[5][11][0])+(fstarr[11][1]
      *Vpk[5][11][1])))+((tstarr[11][2]*Wpk[5][11][2])+((tstarr[11][0]*
      Wpk[5][11][0])+(tstarr[11][1]*Wpk[5][11][1]))))+temp[0]));
    temp[2] = ((((fstarr[14][2]*Vpk[5][14][2])+((fstarr[14][0]*Vpk[5][14][0])+(
      fstarr[14][1]*Vpk[5][14][1])))+((tstarr[14][2]*Wpk[5][14][2])+((
      tstarr[14][0]*Wpk[5][14][0])+(tstarr[14][1]*Wpk[5][14][1]))))+((((
      fstarr[13][2]*Vpk[5][13][2])+((fstarr[13][0]*Vpk[5][13][0])+(fstarr[13][1]
      *Vpk[5][13][1])))+((tstarr[13][2]*Wpk[5][13][2])+((tstarr[13][0]*
      Wpk[5][13][0])+(tstarr[13][1]*Wpk[5][13][1]))))+temp[1]));
    temp[3] = ((((fstarr[20][2]*Vpk[5][20][2])+((fstarr[20][0]*Vpk[5][20][0])+(
      fstarr[20][1]*Vpk[5][20][1])))+((tstarr[20][2]*Wpk[5][20][2])+((
      tstarr[20][0]*Wpk[5][20][0])+(tstarr[20][1]*Wpk[5][20][1]))))+((((
      fstarr[17][2]*Vpk[5][17][2])+((fstarr[17][0]*Vpk[5][17][0])+(fstarr[17][1]
      *Vpk[5][17][1])))+((tstarr[17][2]*Wpk[5][17][2])+((tstarr[17][0]*
      Wpk[5][17][0])+(tstarr[17][1]*Wpk[5][17][1]))))+temp[2]));
    temp[4] = ((((fstarr[22][2]*Vpk[5][22][2])+((fstarr[22][0]*Vpk[5][22][0])+(
      fstarr[22][1]*Vpk[5][22][1])))+((tstarr[22][2]*Wpk[5][22][2])+((
      tstarr[22][0]*Wpk[5][22][0])+(tstarr[22][1]*Wpk[5][22][1]))))+((((
      fstarr[21][2]*Vpk[5][21][2])+((fstarr[21][0]*Vpk[5][21][0])+(fstarr[21][1]
      *Vpk[5][21][1])))+((tstarr[21][2]*Wpk[5][21][2])+((tstarr[21][0]*
      Wpk[5][21][0])+(tstarr[21][1]*Wpk[5][21][1]))))+temp[3]));
    trqout[5] = -((mtau[5]+utau[5])+((((fstarr[26][2]*Vpk[5][26][2])+((
      fstarr[26][0]*Vpk[5][26][0])+(fstarr[26][1]*Vpk[5][26][1])))+((
      tstarr[26][2]*Wpk[5][26][2])+((tstarr[26][0]*Wpk[5][26][0])+(tstarr[26][1]
      *Wpk[5][26][1]))))+((((fstarr[23][2]*Vpk[5][23][2])+((fstarr[23][0]*
      Vpk[5][23][0])+(fstarr[23][1]*Vpk[5][23][1])))+((tstarr[23][2]*
      Wpk[5][23][2])+((tstarr[23][0]*Wpk[5][23][0])+(tstarr[23][1]*Wpk[5][23][1]
      ))))+temp[4])));
    temp[0] = ((((fstarr[8][2]*Vpk[6][8][2])+((fstarr[8][0]*Vpk[6][8][0])+(
      fstarr[8][1]*Vpk[6][8][1])))+((tstarr[8][2]*Wpk[6][8][2])+((tstarr[8][0]*
      Wpk[6][8][0])+(tstarr[8][1]*Wpk[6][8][1]))))+(((fstarr[11][2]*
      Vpk[6][11][2])+((fstarr[11][0]*Vpk[6][11][0])+(fstarr[11][1]*Vpk[6][11][1]
      )))+((tstarr[11][2]*Wpk[6][11][2])+((tstarr[11][0]*Wpk[6][11][0])+(
      tstarr[11][1]*Wpk[6][11][1])))));
    temp[1] = ((((fstarr[13][2]*Vpk[6][13][2])+((fstarr[13][0]*Vpk[6][13][0])+(
      fstarr[13][1]*Vpk[6][13][1])))+((tstarr[13][2]*Wpk[6][13][2])+((
      tstarr[13][0]*Wpk[6][13][0])+(tstarr[13][1]*Wpk[6][13][1]))))+((((
      fstarr[12][2]*Vpk[6][12][2])+((fstarr[12][0]*Vpk[6][12][0])+(fstarr[12][1]
      *Vpk[6][12][1])))+((tstarr[12][2]*Wpk[6][12][2])+((tstarr[12][0]*
      Wpk[6][12][0])+(tstarr[12][1]*Wpk[6][12][1]))))+temp[0]));
    trqout[6] = -((mtau[6]+utau[6])+((((fstarr[14][2]*Vpk[6][14][2])+((
      fstarr[14][0]*Vpk[6][14][0])+(fstarr[14][1]*Vpk[6][14][1])))+((
      tstarr[14][2]*Wpk[6][14][2])+((tstarr[14][0]*Wpk[6][14][0])+(tstarr[14][1]
      *Wpk[6][14][1]))))+temp[1]));
    temp[0] = ((((fstarr[8][2]*Vpk[7][8][2])+((fstarr[8][0]*Vpk[7][8][0])+(
      fstarr[8][1]*Vpk[7][8][1])))+((tstarr[8][2]*Wpk[7][8][2])+((tstarr[8][0]*
      Wpk[7][8][0])+(tstarr[8][1]*Wpk[7][8][1]))))+(((fstarr[11][2]*
      Vpk[7][11][2])+((fstarr[11][0]*Vpk[7][11][0])+(fstarr[11][1]*Vpk[7][11][1]
      )))+((tstarr[11][2]*Wpk[7][11][2])+((tstarr[11][0]*Wpk[7][11][0])+(
      tstarr[11][1]*Wpk[7][11][1])))));
    temp[1] = ((((fstarr[13][2]*Vpk[7][13][2])+((fstarr[13][0]*Vpk[7][13][0])+(
      fstarr[13][1]*Vpk[7][13][1])))+((tstarr[13][2]*Wpk[7][13][2])+((
      tstarr[13][0]*Wpk[7][13][0])+(tstarr[13][1]*Wpk[7][13][1]))))+((((
      fstarr[12][2]*Vpk[7][12][2])+((fstarr[12][0]*Vpk[7][12][0])+(fstarr[12][1]
      *Vpk[7][12][1])))+((tstarr[12][2]*Wpk[7][12][2])+((tstarr[12][0]*
      Wpk[7][12][0])+(tstarr[12][1]*Wpk[7][12][1]))))+temp[0]));
    trqout[7] = -((mtau[7]+utau[7])+((((fstarr[14][2]*Vpk[7][14][2])+((
      fstarr[14][0]*Vpk[7][14][0])+(fstarr[14][1]*Vpk[7][14][1])))+((
      tstarr[14][2]*Wpk[7][14][2])+((tstarr[14][0]*Wpk[7][14][0])+(tstarr[14][1]
      *Wpk[7][14][1]))))+temp[1]));
    temp[0] = ((((fstarr[8][2]*Vpk[8][8][2])+((fstarr[8][0]*Vpk[8][8][0])+(
      fstarr[8][1]*Vpk[8][8][1])))+((pin[8][2]*tstarr[8][2])+((pin[8][0]*
      tstarr[8][0])+(pin[8][1]*tstarr[8][1]))))+(((fstarr[11][2]*Vpk[8][11][2])+
      ((fstarr[11][0]*Vpk[8][11][0])+(fstarr[11][1]*Vpk[8][11][1])))+((
      tstarr[11][2]*Wpk[8][11][2])+((tstarr[11][0]*Wpk[8][11][0])+(tstarr[11][1]
      *Wpk[8][11][1])))));
    temp[1] = ((((fstarr[13][2]*Vpk[8][13][2])+((fstarr[13][0]*Vpk[8][13][0])+(
      fstarr[13][1]*Vpk[8][13][1])))+((tstarr[13][2]*Wpk[8][13][2])+((
      tstarr[13][0]*Wpk[8][13][0])+(tstarr[13][1]*Wpk[8][13][1]))))+((((
      fstarr[12][2]*Vpk[8][12][2])+((fstarr[12][0]*Vpk[8][12][0])+(fstarr[12][1]
      *Vpk[8][12][1])))+((tstarr[12][2]*Wpk[8][12][2])+((tstarr[12][0]*
      Wpk[8][12][0])+(tstarr[12][1]*Wpk[8][12][1]))))+temp[0]));
    trqout[8] = -((mtau[8]+utau[8])+((((fstarr[14][2]*Vpk[8][14][2])+((
      fstarr[14][0]*Vpk[8][14][0])+(fstarr[14][1]*Vpk[8][14][1])))+((
      tstarr[14][2]*Wpk[8][14][2])+((tstarr[14][0]*Wpk[8][14][0])+(tstarr[14][1]
      *Wpk[8][14][1]))))+temp[1]));
    trqout[9] = -((mtau[9]+utau[9])+(((fstarr[14][2]*Vpk[9][14][2])+((
      fstarr[14][0]*Vpk[9][14][0])+(fstarr[14][1]*Vpk[9][14][1])))+(((
      fstarr[13][2]*Vpk[9][13][2])+((fstarr[13][0]*Vpk[9][13][0])+(fstarr[13][1]
      *Vpk[9][13][1])))+(((fstarr[11][2]*Vpk[9][11][2])+((fstarr[11][0]*
      Vpk[9][11][0])+(fstarr[11][1]*Vpk[9][11][1])))+((fstarr[12][2]*
      Vpk[9][12][2])+((fstarr[12][0]*Vpk[9][12][0])+(fstarr[12][1]*Vpk[9][12][1]
      )))))));
    trqout[10] = -((mtau[10]+utau[10])+(((fstarr[14][2]*Vpk[10][14][2])+((
      fstarr[14][0]*Vpk[10][14][0])+(fstarr[14][1]*Vpk[10][14][1])))+(((
      fstarr[13][2]*Vpk[10][13][2])+((fstarr[13][0]*Vpk[10][13][0])+(
      fstarr[13][1]*Vpk[10][13][1])))+(((fstarr[11][2]*Vpk[10][11][2])+((
      fstarr[11][0]*Vpk[10][11][0])+(fstarr[11][1]*Vpk[10][11][1])))+((
      fstarr[12][2]*Vpk[10][12][2])+((fstarr[12][0]*Vpk[10][12][0])+(
      fstarr[12][1]*Vpk[10][12][1])))))));
    temp[0] = ((((fstarr[11][2]*Vpk[11][11][2])+((fstarr[11][0]*Vpk[11][11][0])+
      (fstarr[11][1]*Vpk[11][11][1])))+((pin[11][2]*tstarr[11][2])+((pin[11][0]*
      tstarr[11][0])+(pin[11][1]*tstarr[11][1]))))+(((fstarr[12][2]*
      Vpk[11][12][2])+((fstarr[12][0]*Vpk[11][12][0])+(fstarr[12][1]*
      Vpk[11][12][1])))+((tstarr[12][2]*Wpk[11][12][2])+((tstarr[12][0]*
      Wpk[11][12][0])+(tstarr[12][1]*Wpk[11][12][1])))));
    trqout[11] = -((mtau[11]+utau[11])+((((fstarr[14][2]*Vpk[11][14][2])+((
      fstarr[14][0]*Vpk[11][14][0])+(fstarr[14][1]*Vpk[11][14][1])))+((
      tstarr[14][2]*Wpk[11][14][2])+((tstarr[14][0]*Wpk[11][14][0])+(
      tstarr[14][1]*Wpk[11][14][1]))))+((((fstarr[13][2]*Vpk[11][13][2])+((
      fstarr[13][0]*Vpk[11][13][0])+(fstarr[13][1]*Vpk[11][13][1])))+((
      tstarr[13][2]*Wpk[11][13][2])+((tstarr[13][0]*Wpk[11][13][0])+(
      tstarr[13][1]*Wpk[11][13][1]))))+temp[0])));
    temp[0] = ((((fstarr[12][2]*Vpk[12][12][2])+((fstarr[12][0]*Vpk[12][12][0])+
      (fstarr[12][1]*Vpk[12][12][1])))+((pin[12][2]*tstarr[12][2])+((pin[12][0]*
      tstarr[12][0])+(pin[12][1]*tstarr[12][1]))))+(((fstarr[13][2]*
      Vpk[12][13][2])+((fstarr[13][0]*Vpk[12][13][0])+(fstarr[13][1]*
      Vpk[12][13][1])))+((tstarr[13][2]*Wpk[12][13][2])+((tstarr[13][0]*
      Wpk[12][13][0])+(tstarr[13][1]*Wpk[12][13][1])))));
    trqout[12] = -((mtau[12]+utau[12])+((((fstarr[14][2]*Vpk[12][14][2])+((
      fstarr[14][0]*Vpk[12][14][0])+(fstarr[14][1]*Vpk[12][14][1])))+((
      tstarr[14][2]*Wpk[12][14][2])+((tstarr[14][0]*Wpk[12][14][0])+(
      tstarr[14][1]*Wpk[12][14][1]))))+temp[0]));
    trqout[13] = -((mtau[13]+utau[13])+((((fstarr[13][2]*Vpk[13][13][2])+((
      fstarr[13][0]*Vpk[13][13][0])+(fstarr[13][1]*Vpk[13][13][1])))+((
      pin[13][2]*tstarr[13][2])+((pin[13][0]*tstarr[13][0])+(pin[13][1]*
      tstarr[13][1]))))+(((fstarr[14][2]*Vpk[13][14][2])+((fstarr[14][0]*
      Vpk[13][14][0])+(fstarr[14][1]*Vpk[13][14][1])))+((tstarr[14][2]*
      Wpk[13][14][2])+((tstarr[14][0]*Wpk[13][14][0])+(tstarr[14][1]*
      Wpk[13][14][1]))))));
    trqout[14] = -((mtau[14]+utau[14])+(((fstarr[14][2]*Vpk[14][14][2])+((
      fstarr[14][0]*Vpk[14][14][0])+(fstarr[14][1]*Vpk[14][14][1])))+((
      pin[14][2]*tstarr[14][2])+((pin[14][0]*tstarr[14][0])+(pin[14][1]*
      tstarr[14][1])))));
    temp[0] = ((((fstarr[17][2]*Vpk[15][17][2])+((fstarr[17][0]*Vpk[15][17][0])+
      (fstarr[17][1]*Vpk[15][17][1])))+((tstarr[17][2]*Wpk[15][17][2])+((
      tstarr[17][0]*Wpk[15][17][0])+(tstarr[17][1]*Wpk[15][17][1]))))+(((
      fstarr[20][2]*Vpk[15][20][2])+((fstarr[20][0]*Vpk[15][20][0])+(
      fstarr[20][1]*Vpk[15][20][1])))+((tstarr[20][2]*Wpk[15][20][2])+((
      tstarr[20][0]*Wpk[15][20][0])+(tstarr[20][1]*Wpk[15][20][1])))));
    temp[1] = ((((fstarr[22][2]*Vpk[15][22][2])+((fstarr[22][0]*Vpk[15][22][0])+
      (fstarr[22][1]*Vpk[15][22][1])))+((tstarr[22][2]*Wpk[15][22][2])+((
      tstarr[22][0]*Wpk[15][22][0])+(tstarr[22][1]*Wpk[15][22][1]))))+((((
      fstarr[21][2]*Vpk[15][21][2])+((fstarr[21][0]*Vpk[15][21][0])+(
      fstarr[21][1]*Vpk[15][21][1])))+((tstarr[21][2]*Wpk[15][21][2])+((
      tstarr[21][0]*Wpk[15][21][0])+(tstarr[21][1]*Wpk[15][21][1]))))+temp[0]));
    trqout[15] = -((mtau[15]+utau[15])+((((fstarr[23][2]*Vpk[15][23][2])+((
      fstarr[23][0]*Vpk[15][23][0])+(fstarr[23][1]*Vpk[15][23][1])))+((
      tstarr[23][2]*Wpk[15][23][2])+((tstarr[23][0]*Wpk[15][23][0])+(
      tstarr[23][1]*Wpk[15][23][1]))))+temp[1]));
    temp[0] = ((((fstarr[17][2]*Vpk[16][17][2])+((fstarr[17][0]*Vpk[16][17][0])+
      (fstarr[17][1]*Vpk[16][17][1])))+((tstarr[17][2]*Wpk[16][17][2])+((
      tstarr[17][0]*Wpk[16][17][0])+(tstarr[17][1]*Wpk[16][17][1]))))+(((
      fstarr[20][2]*Vpk[16][20][2])+((fstarr[20][0]*Vpk[16][20][0])+(
      fstarr[20][1]*Vpk[16][20][1])))+((tstarr[20][2]*Wpk[16][20][2])+((
      tstarr[20][0]*Wpk[16][20][0])+(tstarr[20][1]*Wpk[16][20][1])))));
    temp[1] = ((((fstarr[22][2]*Vpk[16][22][2])+((fstarr[22][0]*Vpk[16][22][0])+
      (fstarr[22][1]*Vpk[16][22][1])))+((tstarr[22][2]*Wpk[16][22][2])+((
      tstarr[22][0]*Wpk[16][22][0])+(tstarr[22][1]*Wpk[16][22][1]))))+((((
      fstarr[21][2]*Vpk[16][21][2])+((fstarr[21][0]*Vpk[16][21][0])+(
      fstarr[21][1]*Vpk[16][21][1])))+((tstarr[21][2]*Wpk[16][21][2])+((
      tstarr[21][0]*Wpk[16][21][0])+(tstarr[21][1]*Wpk[16][21][1]))))+temp[0]));
    trqout[16] = -((mtau[16]+utau[16])+((((fstarr[23][2]*Vpk[16][23][2])+((
      fstarr[23][0]*Vpk[16][23][0])+(fstarr[23][1]*Vpk[16][23][1])))+((
      tstarr[23][2]*Wpk[16][23][2])+((tstarr[23][0]*Wpk[16][23][0])+(
      tstarr[23][1]*Wpk[16][23][1]))))+temp[1]));
    temp[0] = ((((fstarr[17][2]*Vpk[17][17][2])+((fstarr[17][0]*Vpk[17][17][0])+
      (fstarr[17][1]*Vpk[17][17][1])))+((pin[17][2]*tstarr[17][2])+((pin[17][0]*
      tstarr[17][0])+(pin[17][1]*tstarr[17][1]))))+(((fstarr[20][2]*
      Vpk[17][20][2])+((fstarr[20][0]*Vpk[17][20][0])+(fstarr[20][1]*
      Vpk[17][20][1])))+((tstarr[20][2]*Wpk[17][20][2])+((tstarr[20][0]*
      Wpk[17][20][0])+(tstarr[20][1]*Wpk[17][20][1])))));
    temp[1] = ((((fstarr[22][2]*Vpk[17][22][2])+((fstarr[22][0]*Vpk[17][22][0])+
      (fstarr[22][1]*Vpk[17][22][1])))+((tstarr[22][2]*Wpk[17][22][2])+((
      tstarr[22][0]*Wpk[17][22][0])+(tstarr[22][1]*Wpk[17][22][1]))))+((((
      fstarr[21][2]*Vpk[17][21][2])+((fstarr[21][0]*Vpk[17][21][0])+(
      fstarr[21][1]*Vpk[17][21][1])))+((tstarr[21][2]*Wpk[17][21][2])+((
      tstarr[21][0]*Wpk[17][21][0])+(tstarr[21][1]*Wpk[17][21][1]))))+temp[0]));
    trqout[17] = -((mtau[17]+utau[17])+((((fstarr[23][2]*Vpk[17][23][2])+((
      fstarr[23][0]*Vpk[17][23][0])+(fstarr[23][1]*Vpk[17][23][1])))+((
      tstarr[23][2]*Wpk[17][23][2])+((tstarr[23][0]*Wpk[17][23][0])+(
      tstarr[23][1]*Wpk[17][23][1]))))+temp[1]));
    trqout[18] = -((mtau[18]+utau[18])+(((fstarr[23][2]*Vpk[18][23][2])+((
      fstarr[23][0]*Vpk[18][23][0])+(fstarr[23][1]*Vpk[18][23][1])))+(((
      fstarr[22][2]*Vpk[18][22][2])+((fstarr[22][0]*Vpk[18][22][0])+(
      fstarr[22][1]*Vpk[18][22][1])))+(((fstarr[20][2]*Vpk[18][20][2])+((
      fstarr[20][0]*Vpk[18][20][0])+(fstarr[20][1]*Vpk[18][20][1])))+((
      fstarr[21][2]*Vpk[18][21][2])+((fstarr[21][0]*Vpk[18][21][0])+(
      fstarr[21][1]*Vpk[18][21][1])))))));
    trqout[19] = -((mtau[19]+utau[19])+(((fstarr[23][2]*Vpk[19][23][2])+((
      fstarr[23][0]*Vpk[19][23][0])+(fstarr[23][1]*Vpk[19][23][1])))+(((
      fstarr[22][2]*Vpk[19][22][2])+((fstarr[22][0]*Vpk[19][22][0])+(
      fstarr[22][1]*Vpk[19][22][1])))+(((fstarr[20][2]*Vpk[19][20][2])+((
      fstarr[20][0]*Vpk[19][20][0])+(fstarr[20][1]*Vpk[19][20][1])))+((
      fstarr[21][2]*Vpk[19][21][2])+((fstarr[21][0]*Vpk[19][21][0])+(
      fstarr[21][1]*Vpk[19][21][1])))))));
    temp[0] = ((((fstarr[20][2]*Vpk[20][20][2])+((fstarr[20][0]*Vpk[20][20][0])+
      (fstarr[20][1]*Vpk[20][20][1])))+((pin[20][2]*tstarr[20][2])+((pin[20][0]*
      tstarr[20][0])+(pin[20][1]*tstarr[20][1]))))+(((fstarr[21][2]*
      Vpk[20][21][2])+((fstarr[21][0]*Vpk[20][21][0])+(fstarr[21][1]*
      Vpk[20][21][1])))+((tstarr[21][2]*Wpk[20][21][2])+((tstarr[21][0]*
      Wpk[20][21][0])+(tstarr[21][1]*Wpk[20][21][1])))));
    trqout[20] = -((mtau[20]+utau[20])+((((fstarr[23][2]*Vpk[20][23][2])+((
      fstarr[23][0]*Vpk[20][23][0])+(fstarr[23][1]*Vpk[20][23][1])))+((
      tstarr[23][2]*Wpk[20][23][2])+((tstarr[23][0]*Wpk[20][23][0])+(
      tstarr[23][1]*Wpk[20][23][1]))))+((((fstarr[22][2]*Vpk[20][22][2])+((
      fstarr[22][0]*Vpk[20][22][0])+(fstarr[22][1]*Vpk[20][22][1])))+((
      tstarr[22][2]*Wpk[20][22][2])+((tstarr[22][0]*Wpk[20][22][0])+(
      tstarr[22][1]*Wpk[20][22][1]))))+temp[0])));
    temp[0] = ((((fstarr[21][2]*Vpk[21][21][2])+((fstarr[21][0]*Vpk[21][21][0])+
      (fstarr[21][1]*Vpk[21][21][1])))+((pin[21][2]*tstarr[21][2])+((pin[21][0]*
      tstarr[21][0])+(pin[21][1]*tstarr[21][1]))))+(((fstarr[22][2]*
      Vpk[21][22][2])+((fstarr[22][0]*Vpk[21][22][0])+(fstarr[22][1]*
      Vpk[21][22][1])))+((tstarr[22][2]*Wpk[21][22][2])+((tstarr[22][0]*
      Wpk[21][22][0])+(tstarr[22][1]*Wpk[21][22][1])))));
    trqout[21] = -((mtau[21]+utau[21])+((((fstarr[23][2]*Vpk[21][23][2])+((
      fstarr[23][0]*Vpk[21][23][0])+(fstarr[23][1]*Vpk[21][23][1])))+((
      tstarr[23][2]*Wpk[21][23][2])+((tstarr[23][0]*Wpk[21][23][0])+(
      tstarr[23][1]*Wpk[21][23][1]))))+temp[0]));
    trqout[22] = -((mtau[22]+utau[22])+((((fstarr[22][2]*Vpk[22][22][2])+((
      fstarr[22][0]*Vpk[22][22][0])+(fstarr[22][1]*Vpk[22][22][1])))+((
      pin[22][2]*tstarr[22][2])+((pin[22][0]*tstarr[22][0])+(pin[22][1]*
      tstarr[22][1]))))+(((fstarr[23][2]*Vpk[22][23][2])+((fstarr[23][0]*
      Vpk[22][23][0])+(fstarr[23][1]*Vpk[22][23][1])))+((tstarr[23][2]*
      Wpk[22][23][2])+((tstarr[23][0]*Wpk[22][23][0])+(tstarr[23][1]*
      Wpk[22][23][1]))))));
    trqout[23] = -((mtau[23]+utau[23])+(((fstarr[23][2]*Vpk[23][23][2])+((
      fstarr[23][0]*Vpk[23][23][0])+(fstarr[23][1]*Vpk[23][23][1])))+((
      pin[23][2]*tstarr[23][2])+((pin[23][0]*tstarr[23][0])+(pin[23][1]*
      tstarr[23][1])))));
    trqout[24] = -((mtau[24]+utau[24])+(((fstarr[26][2]*Vpk[24][26][2])+((
      fstarr[26][0]*Vpk[24][26][0])+(fstarr[26][1]*Vpk[24][26][1])))+((
      tstarr[26][2]*Wpk[24][26][2])+((tstarr[26][0]*Wpk[24][26][0])+(
      tstarr[26][1]*Wpk[24][26][1])))));
    trqout[25] = -((mtau[25]+utau[25])+(((fstarr[26][2]*Vpk[25][26][2])+((
      fstarr[26][0]*Vpk[25][26][0])+(fstarr[26][1]*Vpk[25][26][1])))+((
      tstarr[26][2]*Wpk[25][26][2])+((tstarr[26][0]*Wpk[25][26][0])+(
      tstarr[26][1]*Wpk[25][26][1])))));
    trqout[26] = -((mtau[26]+utau[26])+(((fstarr[26][2]*Vpk[26][26][2])+((
      fstarr[26][0]*Vpk[26][26][0])+(fstarr[26][1]*Vpk[26][26][1])))+((
      pin[26][2]*tstarr[26][2])+((pin[26][0]*tstarr[26][0])+(pin[26][1]*
      tstarr[26][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.44 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 1803 adds/subtracts/negates
                   1740 multiplies
                      0 divides
                    310 assignments
*/
}

sdcomptrq(udotin,trqout)
    double udotin[27],trqout[27];
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    int i;
    double multin[27];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    for (i = 0; i < 27; i++) {
        multin[i] = 0.;
    }
    sdfulltrq(udotin,multin,trqout);
}

sdmulttrq(multin,trqout)
    double multin[27],trqout[27];
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
    for (i = 0; i < 27; i++) {
        trqout[i] = fs[i];
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdfsmult()
{

/*
Compute Fs (multiplier-generated forces only)
*/
    sddovpk();
    temp[0] = (((mfk[3][2]*Vpk[0][12][2])+((mfk[3][0]*Vpk[0][12][0])+(mfk[3][1]*
      Vpk[0][12][1])))+(((mfk[2][2]*Vpk[0][11][2])+((mfk[2][0]*Vpk[0][11][0])+(
      mfk[2][1]*Vpk[0][11][1])))+(((mfk[0][2]*Vpk[0][5][2])+((mfk[0][0]*
      Vpk[0][5][0])+(mfk[0][1]*Vpk[0][5][1])))+((mfk[1][2]*Vpk[0][8][2])+((
      mfk[1][0]*Vpk[0][8][0])+(mfk[1][1]*Vpk[0][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[0][20][2])+((mfk[7][0]*Vpk[0][20][0])+(mfk[7][1]*
      Vpk[0][20][1])))+(((mfk[6][2]*Vpk[0][17][2])+((mfk[6][0]*Vpk[0][17][0])+(
      mfk[6][1]*Vpk[0][17][1])))+(((mfk[5][2]*Vpk[0][14][2])+((mfk[5][0]*
      Vpk[0][14][0])+(mfk[5][1]*Vpk[0][14][1])))+(((mfk[4][2]*Vpk[0][13][2])+((
      mfk[4][0]*Vpk[0][13][0])+(mfk[4][1]*Vpk[0][13][1])))+temp[0]))));
    fs[0] = (mtau[0]+(((mfk[11][2]*Vpk[0][26][2])+((mfk[11][0]*Vpk[0][26][0])+(
      mfk[11][1]*Vpk[0][26][1])))+(((mfk[10][2]*Vpk[0][23][2])+((mfk[10][0]*
      Vpk[0][23][0])+(mfk[10][1]*Vpk[0][23][1])))+(((mfk[9][2]*Vpk[0][22][2])+((
      mfk[9][0]*Vpk[0][22][0])+(mfk[9][1]*Vpk[0][22][1])))+(((mfk[8][2]*
      Vpk[0][21][2])+((mfk[8][0]*Vpk[0][21][0])+(mfk[8][1]*Vpk[0][21][1])))+
      temp[1])))));
    temp[0] = (((mfk[3][2]*Vpk[1][12][2])+((mfk[3][0]*Vpk[1][12][0])+(mfk[3][1]*
      Vpk[1][12][1])))+(((mfk[2][2]*Vpk[1][11][2])+((mfk[2][0]*Vpk[1][11][0])+(
      mfk[2][1]*Vpk[1][11][1])))+(((mfk[0][2]*Vpk[1][5][2])+((mfk[0][0]*
      Vpk[1][5][0])+(mfk[0][1]*Vpk[1][5][1])))+((mfk[1][2]*Vpk[1][8][2])+((
      mfk[1][0]*Vpk[1][8][0])+(mfk[1][1]*Vpk[1][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[1][20][2])+((mfk[7][0]*Vpk[1][20][0])+(mfk[7][1]*
      Vpk[1][20][1])))+(((mfk[6][2]*Vpk[1][17][2])+((mfk[6][0]*Vpk[1][17][0])+(
      mfk[6][1]*Vpk[1][17][1])))+(((mfk[5][2]*Vpk[1][14][2])+((mfk[5][0]*
      Vpk[1][14][0])+(mfk[5][1]*Vpk[1][14][1])))+(((mfk[4][2]*Vpk[1][13][2])+((
      mfk[4][0]*Vpk[1][13][0])+(mfk[4][1]*Vpk[1][13][1])))+temp[0]))));
    fs[1] = (mtau[1]+(((mfk[11][2]*Vpk[1][26][2])+((mfk[11][0]*Vpk[1][26][0])+(
      mfk[11][1]*Vpk[1][26][1])))+(((mfk[10][2]*Vpk[1][23][2])+((mfk[10][0]*
      Vpk[1][23][0])+(mfk[10][1]*Vpk[1][23][1])))+(((mfk[9][2]*Vpk[1][22][2])+((
      mfk[9][0]*Vpk[1][22][0])+(mfk[9][1]*Vpk[1][22][1])))+(((mfk[8][2]*
      Vpk[1][21][2])+((mfk[8][0]*Vpk[1][21][0])+(mfk[8][1]*Vpk[1][21][1])))+
      temp[1])))));
    temp[0] = (((mfk[3][2]*Vpk[2][12][2])+((mfk[3][0]*Vpk[2][12][0])+(mfk[3][1]*
      Vpk[2][12][1])))+(((mfk[2][2]*Vpk[2][11][2])+((mfk[2][0]*Vpk[2][11][0])+(
      mfk[2][1]*Vpk[2][11][1])))+(((mfk[0][2]*Vpk[2][5][2])+((mfk[0][0]*
      Vpk[2][5][0])+(mfk[0][1]*Vpk[2][5][1])))+((mfk[1][2]*Vpk[2][8][2])+((
      mfk[1][0]*Vpk[2][8][0])+(mfk[1][1]*Vpk[2][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[2][20][2])+((mfk[7][0]*Vpk[2][20][0])+(mfk[7][1]*
      Vpk[2][20][1])))+(((mfk[6][2]*Vpk[2][17][2])+((mfk[6][0]*Vpk[2][17][0])+(
      mfk[6][1]*Vpk[2][17][1])))+(((mfk[5][2]*Vpk[2][14][2])+((mfk[5][0]*
      Vpk[2][14][0])+(mfk[5][1]*Vpk[2][14][1])))+(((mfk[4][2]*Vpk[2][13][2])+((
      mfk[4][0]*Vpk[2][13][0])+(mfk[4][1]*Vpk[2][13][1])))+temp[0]))));
    fs[2] = (mtau[2]+(((mfk[11][2]*Vpk[2][26][2])+((mfk[11][0]*Vpk[2][26][0])+(
      mfk[11][1]*Vpk[2][26][1])))+(((mfk[10][2]*Vpk[2][23][2])+((mfk[10][0]*
      Vpk[2][23][0])+(mfk[10][1]*Vpk[2][23][1])))+(((mfk[9][2]*Vpk[2][22][2])+((
      mfk[9][0]*Vpk[2][22][0])+(mfk[9][1]*Vpk[2][22][1])))+(((mfk[8][2]*
      Vpk[2][21][2])+((mfk[8][0]*Vpk[2][21][0])+(mfk[8][1]*Vpk[2][21][1])))+
      temp[1])))));
    temp[0] = ((((mfk[0][2]*Vpk[3][5][2])+((mfk[0][0]*Vpk[3][5][0])+(mfk[0][1]*
      Vpk[3][5][1])))+((mtk[0][2]*Wpk[3][5][2])+((mtk[0][0]*Wpk[3][5][0])+(
      mtk[0][1]*Wpk[3][5][1]))))+(((mfk[1][2]*Vpk[3][8][2])+((mfk[1][0]*
      Vpk[3][8][0])+(mfk[1][1]*Vpk[3][8][1])))+((mtk[1][2]*Wpk[3][8][2])+((
      mtk[1][0]*Wpk[3][8][0])+(mtk[1][1]*Wpk[3][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[3][12][2])+((mfk[3][0]*Vpk[3][12][0])+(mfk[3][1]
      *Vpk[3][12][1])))+((mtk[3][2]*Wpk[3][12][2])+((mtk[3][0]*Wpk[3][12][0])+(
      mtk[3][1]*Wpk[3][12][1]))))+((((mfk[2][2]*Vpk[3][11][2])+((mfk[2][0]*
      Vpk[3][11][0])+(mfk[2][1]*Vpk[3][11][1])))+((mtk[2][2]*Wpk[3][11][2])+((
      mtk[2][0]*Wpk[3][11][0])+(mtk[2][1]*Wpk[3][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[3][14][2])+((mfk[5][0]*Vpk[3][14][0])+(mfk[5][1]
      *Vpk[3][14][1])))+((mtk[5][2]*Wpk[3][14][2])+((mtk[5][0]*Wpk[3][14][0])+(
      mtk[5][1]*Wpk[3][14][1]))))+((((mfk[4][2]*Vpk[3][13][2])+((mfk[4][0]*
      Vpk[3][13][0])+(mfk[4][1]*Vpk[3][13][1])))+((mtk[4][2]*Wpk[3][13][2])+((
      mtk[4][0]*Wpk[3][13][0])+(mtk[4][1]*Wpk[3][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[3][20][2])+((mfk[7][0]*Vpk[3][20][0])+(mfk[7][1]
      *Vpk[3][20][1])))+((mtk[7][2]*Wpk[3][20][2])+((mtk[7][0]*Wpk[3][20][0])+(
      mtk[7][1]*Wpk[3][20][1]))))+((((mfk[6][2]*Vpk[3][17][2])+((mfk[6][0]*
      Vpk[3][17][0])+(mfk[6][1]*Vpk[3][17][1])))+((mtk[6][2]*Wpk[3][17][2])+((
      mtk[6][0]*Wpk[3][17][0])+(mtk[6][1]*Wpk[3][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[3][22][2])+((mfk[9][0]*Vpk[3][22][0])+(mfk[9][1]
      *Vpk[3][22][1])))+((mtk[9][2]*Wpk[3][22][2])+((mtk[9][0]*Wpk[3][22][0])+(
      mtk[9][1]*Wpk[3][22][1]))))+((((mfk[8][2]*Vpk[3][21][2])+((mfk[8][0]*
      Vpk[3][21][0])+(mfk[8][1]*Vpk[3][21][1])))+((mtk[8][2]*Wpk[3][21][2])+((
      mtk[8][0]*Wpk[3][21][0])+(mtk[8][1]*Wpk[3][21][1]))))+temp[3]));
    fs[3] = (mtau[3]+((((mfk[11][2]*Vpk[3][26][2])+((mfk[11][0]*Vpk[3][26][0])+(
      mfk[11][1]*Vpk[3][26][1])))+((mtk[11][2]*Wpk[3][26][2])+((mtk[11][0]*
      Wpk[3][26][0])+(mtk[11][1]*Wpk[3][26][1]))))+((((mfk[10][2]*Vpk[3][23][2])
      +((mfk[10][0]*Vpk[3][23][0])+(mfk[10][1]*Vpk[3][23][1])))+((mtk[10][2]*
      Wpk[3][23][2])+((mtk[10][0]*Wpk[3][23][0])+(mtk[10][1]*Wpk[3][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[0][2]*Vpk[4][5][2])+((mfk[0][0]*Vpk[4][5][0])+(mfk[0][1]*
      Vpk[4][5][1])))+((mtk[0][2]*Wpk[4][5][2])+((mtk[0][0]*Wpk[4][5][0])+(
      mtk[0][1]*Wpk[4][5][1]))))+(((mfk[1][2]*Vpk[4][8][2])+((mfk[1][0]*
      Vpk[4][8][0])+(mfk[1][1]*Vpk[4][8][1])))+((mtk[1][2]*Wpk[4][8][2])+((
      mtk[1][0]*Wpk[4][8][0])+(mtk[1][1]*Wpk[4][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[4][12][2])+((mfk[3][0]*Vpk[4][12][0])+(mfk[3][1]
      *Vpk[4][12][1])))+((mtk[3][2]*Wpk[4][12][2])+((mtk[3][0]*Wpk[4][12][0])+(
      mtk[3][1]*Wpk[4][12][1]))))+((((mfk[2][2]*Vpk[4][11][2])+((mfk[2][0]*
      Vpk[4][11][0])+(mfk[2][1]*Vpk[4][11][1])))+((mtk[2][2]*Wpk[4][11][2])+((
      mtk[2][0]*Wpk[4][11][0])+(mtk[2][1]*Wpk[4][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[4][14][2])+((mfk[5][0]*Vpk[4][14][0])+(mfk[5][1]
      *Vpk[4][14][1])))+((mtk[5][2]*Wpk[4][14][2])+((mtk[5][0]*Wpk[4][14][0])+(
      mtk[5][1]*Wpk[4][14][1]))))+((((mfk[4][2]*Vpk[4][13][2])+((mfk[4][0]*
      Vpk[4][13][0])+(mfk[4][1]*Vpk[4][13][1])))+((mtk[4][2]*Wpk[4][13][2])+((
      mtk[4][0]*Wpk[4][13][0])+(mtk[4][1]*Wpk[4][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[4][20][2])+((mfk[7][0]*Vpk[4][20][0])+(mfk[7][1]
      *Vpk[4][20][1])))+((mtk[7][2]*Wpk[4][20][2])+((mtk[7][0]*Wpk[4][20][0])+(
      mtk[7][1]*Wpk[4][20][1]))))+((((mfk[6][2]*Vpk[4][17][2])+((mfk[6][0]*
      Vpk[4][17][0])+(mfk[6][1]*Vpk[4][17][1])))+((mtk[6][2]*Wpk[4][17][2])+((
      mtk[6][0]*Wpk[4][17][0])+(mtk[6][1]*Wpk[4][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[4][22][2])+((mfk[9][0]*Vpk[4][22][0])+(mfk[9][1]
      *Vpk[4][22][1])))+((mtk[9][2]*Wpk[4][22][2])+((mtk[9][0]*Wpk[4][22][0])+(
      mtk[9][1]*Wpk[4][22][1]))))+((((mfk[8][2]*Vpk[4][21][2])+((mfk[8][0]*
      Vpk[4][21][0])+(mfk[8][1]*Vpk[4][21][1])))+((mtk[8][2]*Wpk[4][21][2])+((
      mtk[8][0]*Wpk[4][21][0])+(mtk[8][1]*Wpk[4][21][1]))))+temp[3]));
    fs[4] = (mtau[4]+((((mfk[11][2]*Vpk[4][26][2])+((mfk[11][0]*Vpk[4][26][0])+(
      mfk[11][1]*Vpk[4][26][1])))+((mtk[11][2]*Wpk[4][26][2])+((mtk[11][0]*
      Wpk[4][26][0])+(mtk[11][1]*Wpk[4][26][1]))))+((((mfk[10][2]*Vpk[4][23][2])
      +((mfk[10][0]*Vpk[4][23][0])+(mfk[10][1]*Vpk[4][23][1])))+((mtk[10][2]*
      Wpk[4][23][2])+((mtk[10][0]*Wpk[4][23][0])+(mtk[10][1]*Wpk[4][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[0][2]*Vpk[5][5][2])+((mfk[0][0]*Vpk[5][5][0])+(mfk[0][1]*
      Vpk[5][5][1])))+((mtk[0][2]*pin[2][2])+((mtk[0][0]*pin[2][0])+(mtk[0][1]*
      pin[2][1]))))+(((mfk[1][2]*Vpk[5][8][2])+((mfk[1][0]*Vpk[5][8][0])+(
      mfk[1][1]*Vpk[5][8][1])))+((mtk[1][2]*Wpk[5][8][2])+((mtk[1][0]*
      Wpk[5][8][0])+(mtk[1][1]*Wpk[5][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[5][12][2])+((mfk[3][0]*Vpk[5][12][0])+(mfk[3][1]
      *Vpk[5][12][1])))+((mtk[3][2]*Wpk[5][12][2])+((mtk[3][0]*Wpk[5][12][0])+(
      mtk[3][1]*Wpk[5][12][1]))))+((((mfk[2][2]*Vpk[5][11][2])+((mfk[2][0]*
      Vpk[5][11][0])+(mfk[2][1]*Vpk[5][11][1])))+((mtk[2][2]*Wpk[5][11][2])+((
      mtk[2][0]*Wpk[5][11][0])+(mtk[2][1]*Wpk[5][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[5][14][2])+((mfk[5][0]*Vpk[5][14][0])+(mfk[5][1]
      *Vpk[5][14][1])))+((mtk[5][2]*Wpk[5][14][2])+((mtk[5][0]*Wpk[5][14][0])+(
      mtk[5][1]*Wpk[5][14][1]))))+((((mfk[4][2]*Vpk[5][13][2])+((mfk[4][0]*
      Vpk[5][13][0])+(mfk[4][1]*Vpk[5][13][1])))+((mtk[4][2]*Wpk[5][13][2])+((
      mtk[4][0]*Wpk[5][13][0])+(mtk[4][1]*Wpk[5][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[5][20][2])+((mfk[7][0]*Vpk[5][20][0])+(mfk[7][1]
      *Vpk[5][20][1])))+((mtk[7][2]*Wpk[5][20][2])+((mtk[7][0]*Wpk[5][20][0])+(
      mtk[7][1]*Wpk[5][20][1]))))+((((mfk[6][2]*Vpk[5][17][2])+((mfk[6][0]*
      Vpk[5][17][0])+(mfk[6][1]*Vpk[5][17][1])))+((mtk[6][2]*Wpk[5][17][2])+((
      mtk[6][0]*Wpk[5][17][0])+(mtk[6][1]*Wpk[5][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[5][22][2])+((mfk[9][0]*Vpk[5][22][0])+(mfk[9][1]
      *Vpk[5][22][1])))+((mtk[9][2]*Wpk[5][22][2])+((mtk[9][0]*Wpk[5][22][0])+(
      mtk[9][1]*Wpk[5][22][1]))))+((((mfk[8][2]*Vpk[5][21][2])+((mfk[8][0]*
      Vpk[5][21][0])+(mfk[8][1]*Vpk[5][21][1])))+((mtk[8][2]*Wpk[5][21][2])+((
      mtk[8][0]*Wpk[5][21][0])+(mtk[8][1]*Wpk[5][21][1]))))+temp[3]));
    fs[5] = (mtau[5]+((((mfk[11][2]*Vpk[5][26][2])+((mfk[11][0]*Vpk[5][26][0])+(
      mfk[11][1]*Vpk[5][26][1])))+((mtk[11][2]*Wpk[5][26][2])+((mtk[11][0]*
      Wpk[5][26][0])+(mtk[11][1]*Wpk[5][26][1]))))+((((mfk[10][2]*Vpk[5][23][2])
      +((mfk[10][0]*Vpk[5][23][0])+(mfk[10][1]*Vpk[5][23][1])))+((mtk[10][2]*
      Wpk[5][23][2])+((mtk[10][0]*Wpk[5][23][0])+(mtk[10][1]*Wpk[5][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[1][2]*Vpk[6][8][2])+((mfk[1][0]*Vpk[6][8][0])+(mfk[1][1]*
      Vpk[6][8][1])))+((mtk[1][2]*Wpk[6][8][2])+((mtk[1][0]*Wpk[6][8][0])+(
      mtk[1][1]*Wpk[6][8][1]))))+(((mfk[2][2]*Vpk[6][11][2])+((mfk[2][0]*
      Vpk[6][11][0])+(mfk[2][1]*Vpk[6][11][1])))+((mtk[2][2]*Wpk[6][11][2])+((
      mtk[2][0]*Wpk[6][11][0])+(mtk[2][1]*Wpk[6][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[6][13][2])+((mfk[4][0]*Vpk[6][13][0])+(mfk[4][1]
      *Vpk[6][13][1])))+((mtk[4][2]*Wpk[6][13][2])+((mtk[4][0]*Wpk[6][13][0])+(
      mtk[4][1]*Wpk[6][13][1]))))+((((mfk[3][2]*Vpk[6][12][2])+((mfk[3][0]*
      Vpk[6][12][0])+(mfk[3][1]*Vpk[6][12][1])))+((mtk[3][2]*Wpk[6][12][2])+((
      mtk[3][0]*Wpk[6][12][0])+(mtk[3][1]*Wpk[6][12][1]))))+temp[0]));
    fs[6] = (mtau[6]+((((mfk[5][2]*Vpk[6][14][2])+((mfk[5][0]*Vpk[6][14][0])+(
      mfk[5][1]*Vpk[6][14][1])))+((mtk[5][2]*Wpk[6][14][2])+((mtk[5][0]*
      Wpk[6][14][0])+(mtk[5][1]*Wpk[6][14][1]))))+temp[1]));
    temp[0] = ((((mfk[1][2]*Vpk[7][8][2])+((mfk[1][0]*Vpk[7][8][0])+(mfk[1][1]*
      Vpk[7][8][1])))+((mtk[1][2]*Wpk[7][8][2])+((mtk[1][0]*Wpk[7][8][0])+(
      mtk[1][1]*Wpk[7][8][1]))))+(((mfk[2][2]*Vpk[7][11][2])+((mfk[2][0]*
      Vpk[7][11][0])+(mfk[2][1]*Vpk[7][11][1])))+((mtk[2][2]*Wpk[7][11][2])+((
      mtk[2][0]*Wpk[7][11][0])+(mtk[2][1]*Wpk[7][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[7][13][2])+((mfk[4][0]*Vpk[7][13][0])+(mfk[4][1]
      *Vpk[7][13][1])))+((mtk[4][2]*Wpk[7][13][2])+((mtk[4][0]*Wpk[7][13][0])+(
      mtk[4][1]*Wpk[7][13][1]))))+((((mfk[3][2]*Vpk[7][12][2])+((mfk[3][0]*
      Vpk[7][12][0])+(mfk[3][1]*Vpk[7][12][1])))+((mtk[3][2]*Wpk[7][12][2])+((
      mtk[3][0]*Wpk[7][12][0])+(mtk[3][1]*Wpk[7][12][1]))))+temp[0]));
    fs[7] = (mtau[7]+((((mfk[5][2]*Vpk[7][14][2])+((mfk[5][0]*Vpk[7][14][0])+(
      mfk[5][1]*Vpk[7][14][1])))+((mtk[5][2]*Wpk[7][14][2])+((mtk[5][0]*
      Wpk[7][14][0])+(mtk[5][1]*Wpk[7][14][1]))))+temp[1]));
    temp[0] = ((((mfk[1][2]*Vpk[8][8][2])+((mfk[1][0]*Vpk[8][8][0])+(mfk[1][1]*
      Vpk[8][8][1])))+((mtk[1][2]*pin[8][2])+((mtk[1][0]*pin[8][0])+(mtk[1][1]*
      pin[8][1]))))+(((mfk[2][2]*Vpk[8][11][2])+((mfk[2][0]*Vpk[8][11][0])+(
      mfk[2][1]*Vpk[8][11][1])))+((mtk[2][2]*Wpk[8][11][2])+((mtk[2][0]*
      Wpk[8][11][0])+(mtk[2][1]*Wpk[8][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[8][13][2])+((mfk[4][0]*Vpk[8][13][0])+(mfk[4][1]
      *Vpk[8][13][1])))+((mtk[4][2]*Wpk[8][13][2])+((mtk[4][0]*Wpk[8][13][0])+(
      mtk[4][1]*Wpk[8][13][1]))))+((((mfk[3][2]*Vpk[8][12][2])+((mfk[3][0]*
      Vpk[8][12][0])+(mfk[3][1]*Vpk[8][12][1])))+((mtk[3][2]*Wpk[8][12][2])+((
      mtk[3][0]*Wpk[8][12][0])+(mtk[3][1]*Wpk[8][12][1]))))+temp[0]));
    fs[8] = (mtau[8]+((((mfk[5][2]*Vpk[8][14][2])+((mfk[5][0]*Vpk[8][14][0])+(
      mfk[5][1]*Vpk[8][14][1])))+((mtk[5][2]*Wpk[8][14][2])+((mtk[5][0]*
      Wpk[8][14][0])+(mtk[5][1]*Wpk[8][14][1]))))+temp[1]));
    fs[9] = (mtau[9]+(((mfk[5][2]*Vpk[9][14][2])+((mfk[5][0]*Vpk[9][14][0])+(
      mfk[5][1]*Vpk[9][14][1])))+(((mfk[4][2]*Vpk[9][13][2])+((mfk[4][0]*
      Vpk[9][13][0])+(mfk[4][1]*Vpk[9][13][1])))+(((mfk[2][2]*Vpk[9][11][2])+((
      mfk[2][0]*Vpk[9][11][0])+(mfk[2][1]*Vpk[9][11][1])))+((mfk[3][2]*
      Vpk[9][12][2])+((mfk[3][0]*Vpk[9][12][0])+(mfk[3][1]*Vpk[9][12][1])))))));
    fs[10] = (mtau[10]+(((mfk[5][2]*Vpk[10][14][2])+((mfk[5][0]*Vpk[10][14][0])+
      (mfk[5][1]*Vpk[10][14][1])))+(((mfk[4][2]*Vpk[10][13][2])+((mfk[4][0]*
      Vpk[10][13][0])+(mfk[4][1]*Vpk[10][13][1])))+(((mfk[2][2]*Vpk[10][11][2])+
      ((mfk[2][0]*Vpk[10][11][0])+(mfk[2][1]*Vpk[10][11][1])))+((mfk[3][2]*
      Vpk[10][12][2])+((mfk[3][0]*Vpk[10][12][0])+(mfk[3][1]*Vpk[10][12][1])))))
      ));
    temp[0] = ((((mfk[2][2]*Vpk[11][11][2])+((mfk[2][0]*Vpk[11][11][0])+(
      mfk[2][1]*Vpk[11][11][1])))+((mtk[2][2]*pin[11][2])+((mtk[2][0]*pin[11][0]
      )+(mtk[2][1]*pin[11][1]))))+(((mfk[3][2]*Vpk[11][12][2])+((mfk[3][0]*
      Vpk[11][12][0])+(mfk[3][1]*Vpk[11][12][1])))+((mtk[3][2]*Wpk[11][12][2])+(
      (mtk[3][0]*Wpk[11][12][0])+(mtk[3][1]*Wpk[11][12][1])))));
    fs[11] = (mtau[11]+((((mfk[5][2]*Vpk[11][14][2])+((mfk[5][0]*Vpk[11][14][0])
      +(mfk[5][1]*Vpk[11][14][1])))+((mtk[5][2]*Wpk[11][14][2])+((mtk[5][0]*
      Wpk[11][14][0])+(mtk[5][1]*Wpk[11][14][1]))))+((((mfk[4][2]*Vpk[11][13][2]
      )+((mfk[4][0]*Vpk[11][13][0])+(mfk[4][1]*Vpk[11][13][1])))+((mtk[4][2]*
      Wpk[11][13][2])+((mtk[4][0]*Wpk[11][13][0])+(mtk[4][1]*Wpk[11][13][1]))))+
      temp[0])));
    temp[0] = ((((mfk[3][2]*Vpk[12][12][2])+((mfk[3][0]*Vpk[12][12][0])+(
      mfk[3][1]*Vpk[12][12][1])))+((mtk[3][2]*pin[12][2])+((mtk[3][0]*pin[12][0]
      )+(mtk[3][1]*pin[12][1]))))+(((mfk[4][2]*Vpk[12][13][2])+((mfk[4][0]*
      Vpk[12][13][0])+(mfk[4][1]*Vpk[12][13][1])))+((mtk[4][2]*Wpk[12][13][2])+(
      (mtk[4][0]*Wpk[12][13][0])+(mtk[4][1]*Wpk[12][13][1])))));
    fs[12] = (mtau[12]+((((mfk[5][2]*Vpk[12][14][2])+((mfk[5][0]*Vpk[12][14][0])
      +(mfk[5][1]*Vpk[12][14][1])))+((mtk[5][2]*Wpk[12][14][2])+((mtk[5][0]*
      Wpk[12][14][0])+(mtk[5][1]*Wpk[12][14][1]))))+temp[0]));
    fs[13] = (mtau[13]+((((mfk[4][2]*Vpk[13][13][2])+((mfk[4][0]*Vpk[13][13][0])
      +(mfk[4][1]*Vpk[13][13][1])))+((mtk[4][2]*pin[13][2])+((mtk[4][0]*
      pin[13][0])+(mtk[4][1]*pin[13][1]))))+(((mfk[5][2]*Vpk[13][14][2])+((
      mfk[5][0]*Vpk[13][14][0])+(mfk[5][1]*Vpk[13][14][1])))+((mtk[5][2]*
      Wpk[13][14][2])+((mtk[5][0]*Wpk[13][14][0])+(mtk[5][1]*Wpk[13][14][1])))))
      );
    fs[14] = (mtau[14]+(((mfk[5][2]*Vpk[14][14][2])+((mfk[5][0]*Vpk[14][14][0])+
      (mfk[5][1]*Vpk[14][14][1])))+((mtk[5][2]*pin[14][2])+((mtk[5][0]*
      pin[14][0])+(mtk[5][1]*pin[14][1])))));
    temp[0] = ((((mfk[6][2]*Vpk[15][17][2])+((mfk[6][0]*Vpk[15][17][0])+(
      mfk[6][1]*Vpk[15][17][1])))+((mtk[6][2]*Wpk[15][17][2])+((mtk[6][0]*
      Wpk[15][17][0])+(mtk[6][1]*Wpk[15][17][1]))))+(((mfk[7][2]*Vpk[15][20][2])
      +((mfk[7][0]*Vpk[15][20][0])+(mfk[7][1]*Vpk[15][20][1])))+((mtk[7][2]*
      Wpk[15][20][2])+((mtk[7][0]*Wpk[15][20][0])+(mtk[7][1]*Wpk[15][20][1])))))
      ;
    temp[1] = ((((mfk[9][2]*Vpk[15][22][2])+((mfk[9][0]*Vpk[15][22][0])+(
      mfk[9][1]*Vpk[15][22][1])))+((mtk[9][2]*Wpk[15][22][2])+((mtk[9][0]*
      Wpk[15][22][0])+(mtk[9][1]*Wpk[15][22][1]))))+((((mfk[8][2]*Vpk[15][21][2]
      )+((mfk[8][0]*Vpk[15][21][0])+(mfk[8][1]*Vpk[15][21][1])))+((mtk[8][2]*
      Wpk[15][21][2])+((mtk[8][0]*Wpk[15][21][0])+(mtk[8][1]*Wpk[15][21][1]))))+
      temp[0]));
    fs[15] = (mtau[15]+((((mfk[10][2]*Vpk[15][23][2])+((mfk[10][0]*
      Vpk[15][23][0])+(mfk[10][1]*Vpk[15][23][1])))+((mtk[10][2]*Wpk[15][23][2])
      +((mtk[10][0]*Wpk[15][23][0])+(mtk[10][1]*Wpk[15][23][1]))))+temp[1]));
    temp[0] = ((((mfk[6][2]*Vpk[16][17][2])+((mfk[6][0]*Vpk[16][17][0])+(
      mfk[6][1]*Vpk[16][17][1])))+((mtk[6][2]*Wpk[16][17][2])+((mtk[6][0]*
      Wpk[16][17][0])+(mtk[6][1]*Wpk[16][17][1]))))+(((mfk[7][2]*Vpk[16][20][2])
      +((mfk[7][0]*Vpk[16][20][0])+(mfk[7][1]*Vpk[16][20][1])))+((mtk[7][2]*
      Wpk[16][20][2])+((mtk[7][0]*Wpk[16][20][0])+(mtk[7][1]*Wpk[16][20][1])))))
      ;
    temp[1] = ((((mfk[9][2]*Vpk[16][22][2])+((mfk[9][0]*Vpk[16][22][0])+(
      mfk[9][1]*Vpk[16][22][1])))+((mtk[9][2]*Wpk[16][22][2])+((mtk[9][0]*
      Wpk[16][22][0])+(mtk[9][1]*Wpk[16][22][1]))))+((((mfk[8][2]*Vpk[16][21][2]
      )+((mfk[8][0]*Vpk[16][21][0])+(mfk[8][1]*Vpk[16][21][1])))+((mtk[8][2]*
      Wpk[16][21][2])+((mtk[8][0]*Wpk[16][21][0])+(mtk[8][1]*Wpk[16][21][1]))))+
      temp[0]));
    fs[16] = (mtau[16]+((((mfk[10][2]*Vpk[16][23][2])+((mfk[10][0]*
      Vpk[16][23][0])+(mfk[10][1]*Vpk[16][23][1])))+((mtk[10][2]*Wpk[16][23][2])
      +((mtk[10][0]*Wpk[16][23][0])+(mtk[10][1]*Wpk[16][23][1]))))+temp[1]));
    temp[0] = ((((mfk[6][2]*Vpk[17][17][2])+((mfk[6][0]*Vpk[17][17][0])+(
      mfk[6][1]*Vpk[17][17][1])))+((mtk[6][2]*pin[17][2])+((mtk[6][0]*pin[17][0]
      )+(mtk[6][1]*pin[17][1]))))+(((mfk[7][2]*Vpk[17][20][2])+((mfk[7][0]*
      Vpk[17][20][0])+(mfk[7][1]*Vpk[17][20][1])))+((mtk[7][2]*Wpk[17][20][2])+(
      (mtk[7][0]*Wpk[17][20][0])+(mtk[7][1]*Wpk[17][20][1])))));
    temp[1] = ((((mfk[9][2]*Vpk[17][22][2])+((mfk[9][0]*Vpk[17][22][0])+(
      mfk[9][1]*Vpk[17][22][1])))+((mtk[9][2]*Wpk[17][22][2])+((mtk[9][0]*
      Wpk[17][22][0])+(mtk[9][1]*Wpk[17][22][1]))))+((((mfk[8][2]*Vpk[17][21][2]
      )+((mfk[8][0]*Vpk[17][21][0])+(mfk[8][1]*Vpk[17][21][1])))+((mtk[8][2]*
      Wpk[17][21][2])+((mtk[8][0]*Wpk[17][21][0])+(mtk[8][1]*Wpk[17][21][1]))))+
      temp[0]));
    fs[17] = (mtau[17]+((((mfk[10][2]*Vpk[17][23][2])+((mfk[10][0]*
      Vpk[17][23][0])+(mfk[10][1]*Vpk[17][23][1])))+((mtk[10][2]*Wpk[17][23][2])
      +((mtk[10][0]*Wpk[17][23][0])+(mtk[10][1]*Wpk[17][23][1]))))+temp[1]));
    fs[18] = (mtau[18]+(((mfk[10][2]*Vpk[18][23][2])+((mfk[10][0]*Vpk[18][23][0]
      )+(mfk[10][1]*Vpk[18][23][1])))+(((mfk[9][2]*Vpk[18][22][2])+((mfk[9][0]*
      Vpk[18][22][0])+(mfk[9][1]*Vpk[18][22][1])))+(((mfk[7][2]*Vpk[18][20][2])+
      ((mfk[7][0]*Vpk[18][20][0])+(mfk[7][1]*Vpk[18][20][1])))+((mfk[8][2]*
      Vpk[18][21][2])+((mfk[8][0]*Vpk[18][21][0])+(mfk[8][1]*Vpk[18][21][1])))))
      ));
    fs[19] = (mtau[19]+(((mfk[10][2]*Vpk[19][23][2])+((mfk[10][0]*Vpk[19][23][0]
      )+(mfk[10][1]*Vpk[19][23][1])))+(((mfk[9][2]*Vpk[19][22][2])+((mfk[9][0]*
      Vpk[19][22][0])+(mfk[9][1]*Vpk[19][22][1])))+(((mfk[7][2]*Vpk[19][20][2])+
      ((mfk[7][0]*Vpk[19][20][0])+(mfk[7][1]*Vpk[19][20][1])))+((mfk[8][2]*
      Vpk[19][21][2])+((mfk[8][0]*Vpk[19][21][0])+(mfk[8][1]*Vpk[19][21][1])))))
      ));
    temp[0] = ((((mfk[7][2]*Vpk[20][20][2])+((mfk[7][0]*Vpk[20][20][0])+(
      mfk[7][1]*Vpk[20][20][1])))+((mtk[7][2]*pin[20][2])+((mtk[7][0]*pin[20][0]
      )+(mtk[7][1]*pin[20][1]))))+(((mfk[8][2]*Vpk[20][21][2])+((mfk[8][0]*
      Vpk[20][21][0])+(mfk[8][1]*Vpk[20][21][1])))+((mtk[8][2]*Wpk[20][21][2])+(
      (mtk[8][0]*Wpk[20][21][0])+(mtk[8][1]*Wpk[20][21][1])))));
    fs[20] = (mtau[20]+((((mfk[10][2]*Vpk[20][23][2])+((mfk[10][0]*
      Vpk[20][23][0])+(mfk[10][1]*Vpk[20][23][1])))+((mtk[10][2]*Wpk[20][23][2])
      +((mtk[10][0]*Wpk[20][23][0])+(mtk[10][1]*Wpk[20][23][1]))))+((((mfk[9][2]
      *Vpk[20][22][2])+((mfk[9][0]*Vpk[20][22][0])+(mfk[9][1]*Vpk[20][22][1])))+
      ((mtk[9][2]*Wpk[20][22][2])+((mtk[9][0]*Wpk[20][22][0])+(mtk[9][1]*
      Wpk[20][22][1]))))+temp[0])));
    temp[0] = ((((mfk[8][2]*Vpk[21][21][2])+((mfk[8][0]*Vpk[21][21][0])+(
      mfk[8][1]*Vpk[21][21][1])))+((mtk[8][2]*pin[21][2])+((mtk[8][0]*pin[21][0]
      )+(mtk[8][1]*pin[21][1]))))+(((mfk[9][2]*Vpk[21][22][2])+((mfk[9][0]*
      Vpk[21][22][0])+(mfk[9][1]*Vpk[21][22][1])))+((mtk[9][2]*Wpk[21][22][2])+(
      (mtk[9][0]*Wpk[21][22][0])+(mtk[9][1]*Wpk[21][22][1])))));
    fs[21] = (mtau[21]+((((mfk[10][2]*Vpk[21][23][2])+((mfk[10][0]*
      Vpk[21][23][0])+(mfk[10][1]*Vpk[21][23][1])))+((mtk[10][2]*Wpk[21][23][2])
      +((mtk[10][0]*Wpk[21][23][0])+(mtk[10][1]*Wpk[21][23][1]))))+temp[0]));
    fs[22] = (mtau[22]+((((mfk[9][2]*Vpk[22][22][2])+((mfk[9][0]*Vpk[22][22][0])
      +(mfk[9][1]*Vpk[22][22][1])))+((mtk[9][2]*pin[22][2])+((mtk[9][0]*
      pin[22][0])+(mtk[9][1]*pin[22][1]))))+(((mfk[10][2]*Vpk[22][23][2])+((
      mfk[10][0]*Vpk[22][23][0])+(mfk[10][1]*Vpk[22][23][1])))+((mtk[10][2]*
      Wpk[22][23][2])+((mtk[10][0]*Wpk[22][23][0])+(mtk[10][1]*Wpk[22][23][1])))
      )));
    fs[23] = (mtau[23]+(((mfk[10][2]*Vpk[23][23][2])+((mfk[10][0]*Vpk[23][23][0]
      )+(mfk[10][1]*Vpk[23][23][1])))+((mtk[10][2]*pin[23][2])+((mtk[10][0]*
      pin[23][0])+(mtk[10][1]*pin[23][1])))));
    fs[24] = (mtau[24]+(((mfk[11][2]*Vpk[24][26][2])+((mfk[11][0]*Vpk[24][26][0]
      )+(mfk[11][1]*Vpk[24][26][1])))+((mtk[11][2]*Wpk[24][26][2])+((mtk[11][0]*
      Wpk[24][26][0])+(mtk[11][1]*Wpk[24][26][1])))));
    fs[25] = (mtau[25]+(((mfk[11][2]*Vpk[25][26][2])+((mfk[11][0]*Vpk[25][26][0]
      )+(mfk[11][1]*Vpk[25][26][1])))+((mtk[11][2]*Wpk[25][26][2])+((mtk[11][0]*
      Wpk[25][26][0])+(mtk[11][1]*Wpk[25][26][1])))));
    fs[26] = (mtau[26]+(((mfk[11][2]*Vpk[26][26][2])+((mfk[11][0]*Vpk[26][26][0]
      )+(mfk[11][1]*Vpk[26][26][1])))+((mtk[11][2]*pin[26][2])+((mtk[11][0]*
      pin[26][0])+(mtk[11][1]*pin[26][1])))));
/*
 Used 0.26 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  690 adds/subtracts/negates
                    690 multiplies
                      0 divides
                     64 assignments
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   27 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdfsgenmult()
{

/*
Compute Fs (generic multiplier-generated forces)
*/
    sddovpk();
    temp[0] = (((mfk[3][2]*Vpk[0][12][2])+((mfk[3][0]*Vpk[0][12][0])+(mfk[3][1]*
      Vpk[0][12][1])))+(((mfk[2][2]*Vpk[0][11][2])+((mfk[2][0]*Vpk[0][11][0])+(
      mfk[2][1]*Vpk[0][11][1])))+(((mfk[0][2]*Vpk[0][5][2])+((mfk[0][0]*
      Vpk[0][5][0])+(mfk[0][1]*Vpk[0][5][1])))+((mfk[1][2]*Vpk[0][8][2])+((
      mfk[1][0]*Vpk[0][8][0])+(mfk[1][1]*Vpk[0][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[0][20][2])+((mfk[7][0]*Vpk[0][20][0])+(mfk[7][1]*
      Vpk[0][20][1])))+(((mfk[6][2]*Vpk[0][17][2])+((mfk[6][0]*Vpk[0][17][0])+(
      mfk[6][1]*Vpk[0][17][1])))+(((mfk[5][2]*Vpk[0][14][2])+((mfk[5][0]*
      Vpk[0][14][0])+(mfk[5][1]*Vpk[0][14][1])))+(((mfk[4][2]*Vpk[0][13][2])+((
      mfk[4][0]*Vpk[0][13][0])+(mfk[4][1]*Vpk[0][13][1])))+temp[0]))));
    fs[0] = (mtau[0]+(((mfk[11][2]*Vpk[0][26][2])+((mfk[11][0]*Vpk[0][26][0])+(
      mfk[11][1]*Vpk[0][26][1])))+(((mfk[10][2]*Vpk[0][23][2])+((mfk[10][0]*
      Vpk[0][23][0])+(mfk[10][1]*Vpk[0][23][1])))+(((mfk[9][2]*Vpk[0][22][2])+((
      mfk[9][0]*Vpk[0][22][0])+(mfk[9][1]*Vpk[0][22][1])))+(((mfk[8][2]*
      Vpk[0][21][2])+((mfk[8][0]*Vpk[0][21][0])+(mfk[8][1]*Vpk[0][21][1])))+
      temp[1])))));
    temp[0] = (((mfk[3][2]*Vpk[1][12][2])+((mfk[3][0]*Vpk[1][12][0])+(mfk[3][1]*
      Vpk[1][12][1])))+(((mfk[2][2]*Vpk[1][11][2])+((mfk[2][0]*Vpk[1][11][0])+(
      mfk[2][1]*Vpk[1][11][1])))+(((mfk[0][2]*Vpk[1][5][2])+((mfk[0][0]*
      Vpk[1][5][0])+(mfk[0][1]*Vpk[1][5][1])))+((mfk[1][2]*Vpk[1][8][2])+((
      mfk[1][0]*Vpk[1][8][0])+(mfk[1][1]*Vpk[1][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[1][20][2])+((mfk[7][0]*Vpk[1][20][0])+(mfk[7][1]*
      Vpk[1][20][1])))+(((mfk[6][2]*Vpk[1][17][2])+((mfk[6][0]*Vpk[1][17][0])+(
      mfk[6][1]*Vpk[1][17][1])))+(((mfk[5][2]*Vpk[1][14][2])+((mfk[5][0]*
      Vpk[1][14][0])+(mfk[5][1]*Vpk[1][14][1])))+(((mfk[4][2]*Vpk[1][13][2])+((
      mfk[4][0]*Vpk[1][13][0])+(mfk[4][1]*Vpk[1][13][1])))+temp[0]))));
    fs[1] = (mtau[1]+(((mfk[11][2]*Vpk[1][26][2])+((mfk[11][0]*Vpk[1][26][0])+(
      mfk[11][1]*Vpk[1][26][1])))+(((mfk[10][2]*Vpk[1][23][2])+((mfk[10][0]*
      Vpk[1][23][0])+(mfk[10][1]*Vpk[1][23][1])))+(((mfk[9][2]*Vpk[1][22][2])+((
      mfk[9][0]*Vpk[1][22][0])+(mfk[9][1]*Vpk[1][22][1])))+(((mfk[8][2]*
      Vpk[1][21][2])+((mfk[8][0]*Vpk[1][21][0])+(mfk[8][1]*Vpk[1][21][1])))+
      temp[1])))));
    temp[0] = (((mfk[3][2]*Vpk[2][12][2])+((mfk[3][0]*Vpk[2][12][0])+(mfk[3][1]*
      Vpk[2][12][1])))+(((mfk[2][2]*Vpk[2][11][2])+((mfk[2][0]*Vpk[2][11][0])+(
      mfk[2][1]*Vpk[2][11][1])))+(((mfk[0][2]*Vpk[2][5][2])+((mfk[0][0]*
      Vpk[2][5][0])+(mfk[0][1]*Vpk[2][5][1])))+((mfk[1][2]*Vpk[2][8][2])+((
      mfk[1][0]*Vpk[2][8][0])+(mfk[1][1]*Vpk[2][8][1]))))));
    temp[1] = (((mfk[7][2]*Vpk[2][20][2])+((mfk[7][0]*Vpk[2][20][0])+(mfk[7][1]*
      Vpk[2][20][1])))+(((mfk[6][2]*Vpk[2][17][2])+((mfk[6][0]*Vpk[2][17][0])+(
      mfk[6][1]*Vpk[2][17][1])))+(((mfk[5][2]*Vpk[2][14][2])+((mfk[5][0]*
      Vpk[2][14][0])+(mfk[5][1]*Vpk[2][14][1])))+(((mfk[4][2]*Vpk[2][13][2])+((
      mfk[4][0]*Vpk[2][13][0])+(mfk[4][1]*Vpk[2][13][1])))+temp[0]))));
    fs[2] = (mtau[2]+(((mfk[11][2]*Vpk[2][26][2])+((mfk[11][0]*Vpk[2][26][0])+(
      mfk[11][1]*Vpk[2][26][1])))+(((mfk[10][2]*Vpk[2][23][2])+((mfk[10][0]*
      Vpk[2][23][0])+(mfk[10][1]*Vpk[2][23][1])))+(((mfk[9][2]*Vpk[2][22][2])+((
      mfk[9][0]*Vpk[2][22][0])+(mfk[9][1]*Vpk[2][22][1])))+(((mfk[8][2]*
      Vpk[2][21][2])+((mfk[8][0]*Vpk[2][21][0])+(mfk[8][1]*Vpk[2][21][1])))+
      temp[1])))));
    temp[0] = ((((mfk[0][2]*Vpk[3][5][2])+((mfk[0][0]*Vpk[3][5][0])+(mfk[0][1]*
      Vpk[3][5][1])))+((mtk[0][2]*Wpk[3][5][2])+((mtk[0][0]*Wpk[3][5][0])+(
      mtk[0][1]*Wpk[3][5][1]))))+(((mfk[1][2]*Vpk[3][8][2])+((mfk[1][0]*
      Vpk[3][8][0])+(mfk[1][1]*Vpk[3][8][1])))+((mtk[1][2]*Wpk[3][8][2])+((
      mtk[1][0]*Wpk[3][8][0])+(mtk[1][1]*Wpk[3][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[3][12][2])+((mfk[3][0]*Vpk[3][12][0])+(mfk[3][1]
      *Vpk[3][12][1])))+((mtk[3][2]*Wpk[3][12][2])+((mtk[3][0]*Wpk[3][12][0])+(
      mtk[3][1]*Wpk[3][12][1]))))+((((mfk[2][2]*Vpk[3][11][2])+((mfk[2][0]*
      Vpk[3][11][0])+(mfk[2][1]*Vpk[3][11][1])))+((mtk[2][2]*Wpk[3][11][2])+((
      mtk[2][0]*Wpk[3][11][0])+(mtk[2][1]*Wpk[3][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[3][14][2])+((mfk[5][0]*Vpk[3][14][0])+(mfk[5][1]
      *Vpk[3][14][1])))+((mtk[5][2]*Wpk[3][14][2])+((mtk[5][0]*Wpk[3][14][0])+(
      mtk[5][1]*Wpk[3][14][1]))))+((((mfk[4][2]*Vpk[3][13][2])+((mfk[4][0]*
      Vpk[3][13][0])+(mfk[4][1]*Vpk[3][13][1])))+((mtk[4][2]*Wpk[3][13][2])+((
      mtk[4][0]*Wpk[3][13][0])+(mtk[4][1]*Wpk[3][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[3][20][2])+((mfk[7][0]*Vpk[3][20][0])+(mfk[7][1]
      *Vpk[3][20][1])))+((mtk[7][2]*Wpk[3][20][2])+((mtk[7][0]*Wpk[3][20][0])+(
      mtk[7][1]*Wpk[3][20][1]))))+((((mfk[6][2]*Vpk[3][17][2])+((mfk[6][0]*
      Vpk[3][17][0])+(mfk[6][1]*Vpk[3][17][1])))+((mtk[6][2]*Wpk[3][17][2])+((
      mtk[6][0]*Wpk[3][17][0])+(mtk[6][1]*Wpk[3][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[3][22][2])+((mfk[9][0]*Vpk[3][22][0])+(mfk[9][1]
      *Vpk[3][22][1])))+((mtk[9][2]*Wpk[3][22][2])+((mtk[9][0]*Wpk[3][22][0])+(
      mtk[9][1]*Wpk[3][22][1]))))+((((mfk[8][2]*Vpk[3][21][2])+((mfk[8][0]*
      Vpk[3][21][0])+(mfk[8][1]*Vpk[3][21][1])))+((mtk[8][2]*Wpk[3][21][2])+((
      mtk[8][0]*Wpk[3][21][0])+(mtk[8][1]*Wpk[3][21][1]))))+temp[3]));
    fs[3] = (mtau[3]+((((mfk[11][2]*Vpk[3][26][2])+((mfk[11][0]*Vpk[3][26][0])+(
      mfk[11][1]*Vpk[3][26][1])))+((mtk[11][2]*Wpk[3][26][2])+((mtk[11][0]*
      Wpk[3][26][0])+(mtk[11][1]*Wpk[3][26][1]))))+((((mfk[10][2]*Vpk[3][23][2])
      +((mfk[10][0]*Vpk[3][23][0])+(mfk[10][1]*Vpk[3][23][1])))+((mtk[10][2]*
      Wpk[3][23][2])+((mtk[10][0]*Wpk[3][23][0])+(mtk[10][1]*Wpk[3][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[0][2]*Vpk[4][5][2])+((mfk[0][0]*Vpk[4][5][0])+(mfk[0][1]*
      Vpk[4][5][1])))+((mtk[0][2]*Wpk[4][5][2])+((mtk[0][0]*Wpk[4][5][0])+(
      mtk[0][1]*Wpk[4][5][1]))))+(((mfk[1][2]*Vpk[4][8][2])+((mfk[1][0]*
      Vpk[4][8][0])+(mfk[1][1]*Vpk[4][8][1])))+((mtk[1][2]*Wpk[4][8][2])+((
      mtk[1][0]*Wpk[4][8][0])+(mtk[1][1]*Wpk[4][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[4][12][2])+((mfk[3][0]*Vpk[4][12][0])+(mfk[3][1]
      *Vpk[4][12][1])))+((mtk[3][2]*Wpk[4][12][2])+((mtk[3][0]*Wpk[4][12][0])+(
      mtk[3][1]*Wpk[4][12][1]))))+((((mfk[2][2]*Vpk[4][11][2])+((mfk[2][0]*
      Vpk[4][11][0])+(mfk[2][1]*Vpk[4][11][1])))+((mtk[2][2]*Wpk[4][11][2])+((
      mtk[2][0]*Wpk[4][11][0])+(mtk[2][1]*Wpk[4][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[4][14][2])+((mfk[5][0]*Vpk[4][14][0])+(mfk[5][1]
      *Vpk[4][14][1])))+((mtk[5][2]*Wpk[4][14][2])+((mtk[5][0]*Wpk[4][14][0])+(
      mtk[5][1]*Wpk[4][14][1]))))+((((mfk[4][2]*Vpk[4][13][2])+((mfk[4][0]*
      Vpk[4][13][0])+(mfk[4][1]*Vpk[4][13][1])))+((mtk[4][2]*Wpk[4][13][2])+((
      mtk[4][0]*Wpk[4][13][0])+(mtk[4][1]*Wpk[4][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[4][20][2])+((mfk[7][0]*Vpk[4][20][0])+(mfk[7][1]
      *Vpk[4][20][1])))+((mtk[7][2]*Wpk[4][20][2])+((mtk[7][0]*Wpk[4][20][0])+(
      mtk[7][1]*Wpk[4][20][1]))))+((((mfk[6][2]*Vpk[4][17][2])+((mfk[6][0]*
      Vpk[4][17][0])+(mfk[6][1]*Vpk[4][17][1])))+((mtk[6][2]*Wpk[4][17][2])+((
      mtk[6][0]*Wpk[4][17][0])+(mtk[6][1]*Wpk[4][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[4][22][2])+((mfk[9][0]*Vpk[4][22][0])+(mfk[9][1]
      *Vpk[4][22][1])))+((mtk[9][2]*Wpk[4][22][2])+((mtk[9][0]*Wpk[4][22][0])+(
      mtk[9][1]*Wpk[4][22][1]))))+((((mfk[8][2]*Vpk[4][21][2])+((mfk[8][0]*
      Vpk[4][21][0])+(mfk[8][1]*Vpk[4][21][1])))+((mtk[8][2]*Wpk[4][21][2])+((
      mtk[8][0]*Wpk[4][21][0])+(mtk[8][1]*Wpk[4][21][1]))))+temp[3]));
    fs[4] = (mtau[4]+((((mfk[11][2]*Vpk[4][26][2])+((mfk[11][0]*Vpk[4][26][0])+(
      mfk[11][1]*Vpk[4][26][1])))+((mtk[11][2]*Wpk[4][26][2])+((mtk[11][0]*
      Wpk[4][26][0])+(mtk[11][1]*Wpk[4][26][1]))))+((((mfk[10][2]*Vpk[4][23][2])
      +((mfk[10][0]*Vpk[4][23][0])+(mfk[10][1]*Vpk[4][23][1])))+((mtk[10][2]*
      Wpk[4][23][2])+((mtk[10][0]*Wpk[4][23][0])+(mtk[10][1]*Wpk[4][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[0][2]*Vpk[5][5][2])+((mfk[0][0]*Vpk[5][5][0])+(mfk[0][1]*
      Vpk[5][5][1])))+((mtk[0][2]*pin[2][2])+((mtk[0][0]*pin[2][0])+(mtk[0][1]*
      pin[2][1]))))+(((mfk[1][2]*Vpk[5][8][2])+((mfk[1][0]*Vpk[5][8][0])+(
      mfk[1][1]*Vpk[5][8][1])))+((mtk[1][2]*Wpk[5][8][2])+((mtk[1][0]*
      Wpk[5][8][0])+(mtk[1][1]*Wpk[5][8][1])))));
    temp[1] = ((((mfk[3][2]*Vpk[5][12][2])+((mfk[3][0]*Vpk[5][12][0])+(mfk[3][1]
      *Vpk[5][12][1])))+((mtk[3][2]*Wpk[5][12][2])+((mtk[3][0]*Wpk[5][12][0])+(
      mtk[3][1]*Wpk[5][12][1]))))+((((mfk[2][2]*Vpk[5][11][2])+((mfk[2][0]*
      Vpk[5][11][0])+(mfk[2][1]*Vpk[5][11][1])))+((mtk[2][2]*Wpk[5][11][2])+((
      mtk[2][0]*Wpk[5][11][0])+(mtk[2][1]*Wpk[5][11][1]))))+temp[0]));
    temp[2] = ((((mfk[5][2]*Vpk[5][14][2])+((mfk[5][0]*Vpk[5][14][0])+(mfk[5][1]
      *Vpk[5][14][1])))+((mtk[5][2]*Wpk[5][14][2])+((mtk[5][0]*Wpk[5][14][0])+(
      mtk[5][1]*Wpk[5][14][1]))))+((((mfk[4][2]*Vpk[5][13][2])+((mfk[4][0]*
      Vpk[5][13][0])+(mfk[4][1]*Vpk[5][13][1])))+((mtk[4][2]*Wpk[5][13][2])+((
      mtk[4][0]*Wpk[5][13][0])+(mtk[4][1]*Wpk[5][13][1]))))+temp[1]));
    temp[3] = ((((mfk[7][2]*Vpk[5][20][2])+((mfk[7][0]*Vpk[5][20][0])+(mfk[7][1]
      *Vpk[5][20][1])))+((mtk[7][2]*Wpk[5][20][2])+((mtk[7][0]*Wpk[5][20][0])+(
      mtk[7][1]*Wpk[5][20][1]))))+((((mfk[6][2]*Vpk[5][17][2])+((mfk[6][0]*
      Vpk[5][17][0])+(mfk[6][1]*Vpk[5][17][1])))+((mtk[6][2]*Wpk[5][17][2])+((
      mtk[6][0]*Wpk[5][17][0])+(mtk[6][1]*Wpk[5][17][1]))))+temp[2]));
    temp[4] = ((((mfk[9][2]*Vpk[5][22][2])+((mfk[9][0]*Vpk[5][22][0])+(mfk[9][1]
      *Vpk[5][22][1])))+((mtk[9][2]*Wpk[5][22][2])+((mtk[9][0]*Wpk[5][22][0])+(
      mtk[9][1]*Wpk[5][22][1]))))+((((mfk[8][2]*Vpk[5][21][2])+((mfk[8][0]*
      Vpk[5][21][0])+(mfk[8][1]*Vpk[5][21][1])))+((mtk[8][2]*Wpk[5][21][2])+((
      mtk[8][0]*Wpk[5][21][0])+(mtk[8][1]*Wpk[5][21][1]))))+temp[3]));
    fs[5] = (mtau[5]+((((mfk[11][2]*Vpk[5][26][2])+((mfk[11][0]*Vpk[5][26][0])+(
      mfk[11][1]*Vpk[5][26][1])))+((mtk[11][2]*Wpk[5][26][2])+((mtk[11][0]*
      Wpk[5][26][0])+(mtk[11][1]*Wpk[5][26][1]))))+((((mfk[10][2]*Vpk[5][23][2])
      +((mfk[10][0]*Vpk[5][23][0])+(mfk[10][1]*Vpk[5][23][1])))+((mtk[10][2]*
      Wpk[5][23][2])+((mtk[10][0]*Wpk[5][23][0])+(mtk[10][1]*Wpk[5][23][1]))))+
      temp[4])));
    temp[0] = ((((mfk[1][2]*Vpk[6][8][2])+((mfk[1][0]*Vpk[6][8][0])+(mfk[1][1]*
      Vpk[6][8][1])))+((mtk[1][2]*Wpk[6][8][2])+((mtk[1][0]*Wpk[6][8][0])+(
      mtk[1][1]*Wpk[6][8][1]))))+(((mfk[2][2]*Vpk[6][11][2])+((mfk[2][0]*
      Vpk[6][11][0])+(mfk[2][1]*Vpk[6][11][1])))+((mtk[2][2]*Wpk[6][11][2])+((
      mtk[2][0]*Wpk[6][11][0])+(mtk[2][1]*Wpk[6][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[6][13][2])+((mfk[4][0]*Vpk[6][13][0])+(mfk[4][1]
      *Vpk[6][13][1])))+((mtk[4][2]*Wpk[6][13][2])+((mtk[4][0]*Wpk[6][13][0])+(
      mtk[4][1]*Wpk[6][13][1]))))+((((mfk[3][2]*Vpk[6][12][2])+((mfk[3][0]*
      Vpk[6][12][0])+(mfk[3][1]*Vpk[6][12][1])))+((mtk[3][2]*Wpk[6][12][2])+((
      mtk[3][0]*Wpk[6][12][0])+(mtk[3][1]*Wpk[6][12][1]))))+temp[0]));
    fs[6] = (mtau[6]+((((mfk[5][2]*Vpk[6][14][2])+((mfk[5][0]*Vpk[6][14][0])+(
      mfk[5][1]*Vpk[6][14][1])))+((mtk[5][2]*Wpk[6][14][2])+((mtk[5][0]*
      Wpk[6][14][0])+(mtk[5][1]*Wpk[6][14][1]))))+temp[1]));
    temp[0] = ((((mfk[1][2]*Vpk[7][8][2])+((mfk[1][0]*Vpk[7][8][0])+(mfk[1][1]*
      Vpk[7][8][1])))+((mtk[1][2]*Wpk[7][8][2])+((mtk[1][0]*Wpk[7][8][0])+(
      mtk[1][1]*Wpk[7][8][1]))))+(((mfk[2][2]*Vpk[7][11][2])+((mfk[2][0]*
      Vpk[7][11][0])+(mfk[2][1]*Vpk[7][11][1])))+((mtk[2][2]*Wpk[7][11][2])+((
      mtk[2][0]*Wpk[7][11][0])+(mtk[2][1]*Wpk[7][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[7][13][2])+((mfk[4][0]*Vpk[7][13][0])+(mfk[4][1]
      *Vpk[7][13][1])))+((mtk[4][2]*Wpk[7][13][2])+((mtk[4][0]*Wpk[7][13][0])+(
      mtk[4][1]*Wpk[7][13][1]))))+((((mfk[3][2]*Vpk[7][12][2])+((mfk[3][0]*
      Vpk[7][12][0])+(mfk[3][1]*Vpk[7][12][1])))+((mtk[3][2]*Wpk[7][12][2])+((
      mtk[3][0]*Wpk[7][12][0])+(mtk[3][1]*Wpk[7][12][1]))))+temp[0]));
    fs[7] = (mtau[7]+((((mfk[5][2]*Vpk[7][14][2])+((mfk[5][0]*Vpk[7][14][0])+(
      mfk[5][1]*Vpk[7][14][1])))+((mtk[5][2]*Wpk[7][14][2])+((mtk[5][0]*
      Wpk[7][14][0])+(mtk[5][1]*Wpk[7][14][1]))))+temp[1]));
    temp[0] = ((((mfk[1][2]*Vpk[8][8][2])+((mfk[1][0]*Vpk[8][8][0])+(mfk[1][1]*
      Vpk[8][8][1])))+((mtk[1][2]*pin[8][2])+((mtk[1][0]*pin[8][0])+(mtk[1][1]*
      pin[8][1]))))+(((mfk[2][2]*Vpk[8][11][2])+((mfk[2][0]*Vpk[8][11][0])+(
      mfk[2][1]*Vpk[8][11][1])))+((mtk[2][2]*Wpk[8][11][2])+((mtk[2][0]*
      Wpk[8][11][0])+(mtk[2][1]*Wpk[8][11][1])))));
    temp[1] = ((((mfk[4][2]*Vpk[8][13][2])+((mfk[4][0]*Vpk[8][13][0])+(mfk[4][1]
      *Vpk[8][13][1])))+((mtk[4][2]*Wpk[8][13][2])+((mtk[4][0]*Wpk[8][13][0])+(
      mtk[4][1]*Wpk[8][13][1]))))+((((mfk[3][2]*Vpk[8][12][2])+((mfk[3][0]*
      Vpk[8][12][0])+(mfk[3][1]*Vpk[8][12][1])))+((mtk[3][2]*Wpk[8][12][2])+((
      mtk[3][0]*Wpk[8][12][0])+(mtk[3][1]*Wpk[8][12][1]))))+temp[0]));
    fs[8] = (mtau[8]+((((mfk[5][2]*Vpk[8][14][2])+((mfk[5][0]*Vpk[8][14][0])+(
      mfk[5][1]*Vpk[8][14][1])))+((mtk[5][2]*Wpk[8][14][2])+((mtk[5][0]*
      Wpk[8][14][0])+(mtk[5][1]*Wpk[8][14][1]))))+temp[1]));
    fs[9] = (mtau[9]+(((mfk[5][2]*Vpk[9][14][2])+((mfk[5][0]*Vpk[9][14][0])+(
      mfk[5][1]*Vpk[9][14][1])))+(((mfk[4][2]*Vpk[9][13][2])+((mfk[4][0]*
      Vpk[9][13][0])+(mfk[4][1]*Vpk[9][13][1])))+(((mfk[2][2]*Vpk[9][11][2])+((
      mfk[2][0]*Vpk[9][11][0])+(mfk[2][1]*Vpk[9][11][1])))+((mfk[3][2]*
      Vpk[9][12][2])+((mfk[3][0]*Vpk[9][12][0])+(mfk[3][1]*Vpk[9][12][1])))))));
    fs[10] = (mtau[10]+(((mfk[5][2]*Vpk[10][14][2])+((mfk[5][0]*Vpk[10][14][0])+
      (mfk[5][1]*Vpk[10][14][1])))+(((mfk[4][2]*Vpk[10][13][2])+((mfk[4][0]*
      Vpk[10][13][0])+(mfk[4][1]*Vpk[10][13][1])))+(((mfk[2][2]*Vpk[10][11][2])+
      ((mfk[2][0]*Vpk[10][11][0])+(mfk[2][1]*Vpk[10][11][1])))+((mfk[3][2]*
      Vpk[10][12][2])+((mfk[3][0]*Vpk[10][12][0])+(mfk[3][1]*Vpk[10][12][1])))))
      ));
    temp[0] = ((((mfk[2][2]*Vpk[11][11][2])+((mfk[2][0]*Vpk[11][11][0])+(
      mfk[2][1]*Vpk[11][11][1])))+((mtk[2][2]*pin[11][2])+((mtk[2][0]*pin[11][0]
      )+(mtk[2][1]*pin[11][1]))))+(((mfk[3][2]*Vpk[11][12][2])+((mfk[3][0]*
      Vpk[11][12][0])+(mfk[3][1]*Vpk[11][12][1])))+((mtk[3][2]*Wpk[11][12][2])+(
      (mtk[3][0]*Wpk[11][12][0])+(mtk[3][1]*Wpk[11][12][1])))));
    fs[11] = (mtau[11]+((((mfk[5][2]*Vpk[11][14][2])+((mfk[5][0]*Vpk[11][14][0])
      +(mfk[5][1]*Vpk[11][14][1])))+((mtk[5][2]*Wpk[11][14][2])+((mtk[5][0]*
      Wpk[11][14][0])+(mtk[5][1]*Wpk[11][14][1]))))+((((mfk[4][2]*Vpk[11][13][2]
      )+((mfk[4][0]*Vpk[11][13][0])+(mfk[4][1]*Vpk[11][13][1])))+((mtk[4][2]*
      Wpk[11][13][2])+((mtk[4][0]*Wpk[11][13][0])+(mtk[4][1]*Wpk[11][13][1]))))+
      temp[0])));
    temp[0] = ((((mfk[3][2]*Vpk[12][12][2])+((mfk[3][0]*Vpk[12][12][0])+(
      mfk[3][1]*Vpk[12][12][1])))+((mtk[3][2]*pin[12][2])+((mtk[3][0]*pin[12][0]
      )+(mtk[3][1]*pin[12][1]))))+(((mfk[4][2]*Vpk[12][13][2])+((mfk[4][0]*
      Vpk[12][13][0])+(mfk[4][1]*Vpk[12][13][1])))+((mtk[4][2]*Wpk[12][13][2])+(
      (mtk[4][0]*Wpk[12][13][0])+(mtk[4][1]*Wpk[12][13][1])))));
    fs[12] = (mtau[12]+((((mfk[5][2]*Vpk[12][14][2])+((mfk[5][0]*Vpk[12][14][0])
      +(mfk[5][1]*Vpk[12][14][1])))+((mtk[5][2]*Wpk[12][14][2])+((mtk[5][0]*
      Wpk[12][14][0])+(mtk[5][1]*Wpk[12][14][1]))))+temp[0]));
    fs[13] = (mtau[13]+((((mfk[4][2]*Vpk[13][13][2])+((mfk[4][0]*Vpk[13][13][0])
      +(mfk[4][1]*Vpk[13][13][1])))+((mtk[4][2]*pin[13][2])+((mtk[4][0]*
      pin[13][0])+(mtk[4][1]*pin[13][1]))))+(((mfk[5][2]*Vpk[13][14][2])+((
      mfk[5][0]*Vpk[13][14][0])+(mfk[5][1]*Vpk[13][14][1])))+((mtk[5][2]*
      Wpk[13][14][2])+((mtk[5][0]*Wpk[13][14][0])+(mtk[5][1]*Wpk[13][14][1])))))
      );
    fs[14] = (mtau[14]+(((mfk[5][2]*Vpk[14][14][2])+((mfk[5][0]*Vpk[14][14][0])+
      (mfk[5][1]*Vpk[14][14][1])))+((mtk[5][2]*pin[14][2])+((mtk[5][0]*
      pin[14][0])+(mtk[5][1]*pin[14][1])))));
    temp[0] = ((((mfk[6][2]*Vpk[15][17][2])+((mfk[6][0]*Vpk[15][17][0])+(
      mfk[6][1]*Vpk[15][17][1])))+((mtk[6][2]*Wpk[15][17][2])+((mtk[6][0]*
      Wpk[15][17][0])+(mtk[6][1]*Wpk[15][17][1]))))+(((mfk[7][2]*Vpk[15][20][2])
      +((mfk[7][0]*Vpk[15][20][0])+(mfk[7][1]*Vpk[15][20][1])))+((mtk[7][2]*
      Wpk[15][20][2])+((mtk[7][0]*Wpk[15][20][0])+(mtk[7][1]*Wpk[15][20][1])))))
      ;
    temp[1] = ((((mfk[9][2]*Vpk[15][22][2])+((mfk[9][0]*Vpk[15][22][0])+(
      mfk[9][1]*Vpk[15][22][1])))+((mtk[9][2]*Wpk[15][22][2])+((mtk[9][0]*
      Wpk[15][22][0])+(mtk[9][1]*Wpk[15][22][1]))))+((((mfk[8][2]*Vpk[15][21][2]
      )+((mfk[8][0]*Vpk[15][21][0])+(mfk[8][1]*Vpk[15][21][1])))+((mtk[8][2]*
      Wpk[15][21][2])+((mtk[8][0]*Wpk[15][21][0])+(mtk[8][1]*Wpk[15][21][1]))))+
      temp[0]));
    fs[15] = (mtau[15]+((((mfk[10][2]*Vpk[15][23][2])+((mfk[10][0]*
      Vpk[15][23][0])+(mfk[10][1]*Vpk[15][23][1])))+((mtk[10][2]*Wpk[15][23][2])
      +((mtk[10][0]*Wpk[15][23][0])+(mtk[10][1]*Wpk[15][23][1]))))+temp[1]));
    temp[0] = ((((mfk[6][2]*Vpk[16][17][2])+((mfk[6][0]*Vpk[16][17][0])+(
      mfk[6][1]*Vpk[16][17][1])))+((mtk[6][2]*Wpk[16][17][2])+((mtk[6][0]*
      Wpk[16][17][0])+(mtk[6][1]*Wpk[16][17][1]))))+(((mfk[7][2]*Vpk[16][20][2])
      +((mfk[7][0]*Vpk[16][20][0])+(mfk[7][1]*Vpk[16][20][1])))+((mtk[7][2]*
      Wpk[16][20][2])+((mtk[7][0]*Wpk[16][20][0])+(mtk[7][1]*Wpk[16][20][1])))))
      ;
    temp[1] = ((((mfk[9][2]*Vpk[16][22][2])+((mfk[9][0]*Vpk[16][22][0])+(
      mfk[9][1]*Vpk[16][22][1])))+((mtk[9][2]*Wpk[16][22][2])+((mtk[9][0]*
      Wpk[16][22][0])+(mtk[9][1]*Wpk[16][22][1]))))+((((mfk[8][2]*Vpk[16][21][2]
      )+((mfk[8][0]*Vpk[16][21][0])+(mfk[8][1]*Vpk[16][21][1])))+((mtk[8][2]*
      Wpk[16][21][2])+((mtk[8][0]*Wpk[16][21][0])+(mtk[8][1]*Wpk[16][21][1]))))+
      temp[0]));
    fs[16] = (mtau[16]+((((mfk[10][2]*Vpk[16][23][2])+((mfk[10][0]*
      Vpk[16][23][0])+(mfk[10][1]*Vpk[16][23][1])))+((mtk[10][2]*Wpk[16][23][2])
      +((mtk[10][0]*Wpk[16][23][0])+(mtk[10][1]*Wpk[16][23][1]))))+temp[1]));
    temp[0] = ((((mfk[6][2]*Vpk[17][17][2])+((mfk[6][0]*Vpk[17][17][0])+(
      mfk[6][1]*Vpk[17][17][1])))+((mtk[6][2]*pin[17][2])+((mtk[6][0]*pin[17][0]
      )+(mtk[6][1]*pin[17][1]))))+(((mfk[7][2]*Vpk[17][20][2])+((mfk[7][0]*
      Vpk[17][20][0])+(mfk[7][1]*Vpk[17][20][1])))+((mtk[7][2]*Wpk[17][20][2])+(
      (mtk[7][0]*Wpk[17][20][0])+(mtk[7][1]*Wpk[17][20][1])))));
    temp[1] = ((((mfk[9][2]*Vpk[17][22][2])+((mfk[9][0]*Vpk[17][22][0])+(
      mfk[9][1]*Vpk[17][22][1])))+((mtk[9][2]*Wpk[17][22][2])+((mtk[9][0]*
      Wpk[17][22][0])+(mtk[9][1]*Wpk[17][22][1]))))+((((mfk[8][2]*Vpk[17][21][2]
      )+((mfk[8][0]*Vpk[17][21][0])+(mfk[8][1]*Vpk[17][21][1])))+((mtk[8][2]*
      Wpk[17][21][2])+((mtk[8][0]*Wpk[17][21][0])+(mtk[8][1]*Wpk[17][21][1]))))+
      temp[0]));
    fs[17] = (mtau[17]+((((mfk[10][2]*Vpk[17][23][2])+((mfk[10][0]*
      Vpk[17][23][0])+(mfk[10][1]*Vpk[17][23][1])))+((mtk[10][2]*Wpk[17][23][2])
      +((mtk[10][0]*Wpk[17][23][0])+(mtk[10][1]*Wpk[17][23][1]))))+temp[1]));
    fs[18] = (mtau[18]+(((mfk[10][2]*Vpk[18][23][2])+((mfk[10][0]*Vpk[18][23][0]
      )+(mfk[10][1]*Vpk[18][23][1])))+(((mfk[9][2]*Vpk[18][22][2])+((mfk[9][0]*
      Vpk[18][22][0])+(mfk[9][1]*Vpk[18][22][1])))+(((mfk[7][2]*Vpk[18][20][2])+
      ((mfk[7][0]*Vpk[18][20][0])+(mfk[7][1]*Vpk[18][20][1])))+((mfk[8][2]*
      Vpk[18][21][2])+((mfk[8][0]*Vpk[18][21][0])+(mfk[8][1]*Vpk[18][21][1])))))
      ));
    fs[19] = (mtau[19]+(((mfk[10][2]*Vpk[19][23][2])+((mfk[10][0]*Vpk[19][23][0]
      )+(mfk[10][1]*Vpk[19][23][1])))+(((mfk[9][2]*Vpk[19][22][2])+((mfk[9][0]*
      Vpk[19][22][0])+(mfk[9][1]*Vpk[19][22][1])))+(((mfk[7][2]*Vpk[19][20][2])+
      ((mfk[7][0]*Vpk[19][20][0])+(mfk[7][1]*Vpk[19][20][1])))+((mfk[8][2]*
      Vpk[19][21][2])+((mfk[8][0]*Vpk[19][21][0])+(mfk[8][1]*Vpk[19][21][1])))))
      ));
    temp[0] = ((((mfk[7][2]*Vpk[20][20][2])+((mfk[7][0]*Vpk[20][20][0])+(
      mfk[7][1]*Vpk[20][20][1])))+((mtk[7][2]*pin[20][2])+((mtk[7][0]*pin[20][0]
      )+(mtk[7][1]*pin[20][1]))))+(((mfk[8][2]*Vpk[20][21][2])+((mfk[8][0]*
      Vpk[20][21][0])+(mfk[8][1]*Vpk[20][21][1])))+((mtk[8][2]*Wpk[20][21][2])+(
      (mtk[8][0]*Wpk[20][21][0])+(mtk[8][1]*Wpk[20][21][1])))));
    fs[20] = (mtau[20]+((((mfk[10][2]*Vpk[20][23][2])+((mfk[10][0]*
      Vpk[20][23][0])+(mfk[10][1]*Vpk[20][23][1])))+((mtk[10][2]*Wpk[20][23][2])
      +((mtk[10][0]*Wpk[20][23][0])+(mtk[10][1]*Wpk[20][23][1]))))+((((mfk[9][2]
      *Vpk[20][22][2])+((mfk[9][0]*Vpk[20][22][0])+(mfk[9][1]*Vpk[20][22][1])))+
      ((mtk[9][2]*Wpk[20][22][2])+((mtk[9][0]*Wpk[20][22][0])+(mtk[9][1]*
      Wpk[20][22][1]))))+temp[0])));
    temp[0] = ((((mfk[8][2]*Vpk[21][21][2])+((mfk[8][0]*Vpk[21][21][0])+(
      mfk[8][1]*Vpk[21][21][1])))+((mtk[8][2]*pin[21][2])+((mtk[8][0]*pin[21][0]
      )+(mtk[8][1]*pin[21][1]))))+(((mfk[9][2]*Vpk[21][22][2])+((mfk[9][0]*
      Vpk[21][22][0])+(mfk[9][1]*Vpk[21][22][1])))+((mtk[9][2]*Wpk[21][22][2])+(
      (mtk[9][0]*Wpk[21][22][0])+(mtk[9][1]*Wpk[21][22][1])))));
    fs[21] = (mtau[21]+((((mfk[10][2]*Vpk[21][23][2])+((mfk[10][0]*
      Vpk[21][23][0])+(mfk[10][1]*Vpk[21][23][1])))+((mtk[10][2]*Wpk[21][23][2])
      +((mtk[10][0]*Wpk[21][23][0])+(mtk[10][1]*Wpk[21][23][1]))))+temp[0]));
    fs[22] = (mtau[22]+((((mfk[9][2]*Vpk[22][22][2])+((mfk[9][0]*Vpk[22][22][0])
      +(mfk[9][1]*Vpk[22][22][1])))+((mtk[9][2]*pin[22][2])+((mtk[9][0]*
      pin[22][0])+(mtk[9][1]*pin[22][1]))))+(((mfk[10][2]*Vpk[22][23][2])+((
      mfk[10][0]*Vpk[22][23][0])+(mfk[10][1]*Vpk[22][23][1])))+((mtk[10][2]*
      Wpk[22][23][2])+((mtk[10][0]*Wpk[22][23][0])+(mtk[10][1]*Wpk[22][23][1])))
      )));
    fs[23] = (mtau[23]+(((mfk[10][2]*Vpk[23][23][2])+((mfk[10][0]*Vpk[23][23][0]
      )+(mfk[10][1]*Vpk[23][23][1])))+((mtk[10][2]*pin[23][2])+((mtk[10][0]*
      pin[23][0])+(mtk[10][1]*pin[23][1])))));
    fs[24] = (mtau[24]+(((mfk[11][2]*Vpk[24][26][2])+((mfk[11][0]*Vpk[24][26][0]
      )+(mfk[11][1]*Vpk[24][26][1])))+((mtk[11][2]*Wpk[24][26][2])+((mtk[11][0]*
      Wpk[24][26][0])+(mtk[11][1]*Wpk[24][26][1])))));
    fs[25] = (mtau[25]+(((mfk[11][2]*Vpk[25][26][2])+((mfk[11][0]*Vpk[25][26][0]
      )+(mfk[11][1]*Vpk[25][26][1])))+((mtk[11][2]*Wpk[25][26][2])+((mtk[11][0]*
      Wpk[25][26][0])+(mtk[11][1]*Wpk[25][26][1])))));
    fs[26] = (mtau[26]+(((mfk[11][2]*Vpk[26][26][2])+((mfk[11][0]*Vpk[26][26][0]
      )+(mfk[11][1]*Vpk[26][26][1])))+((mtk[11][2]*pin[26][2])+((mtk[11][0]*
      pin[26][0])+(mtk[11][1]*pin[26][1])))));
/*
 Used 0.24 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  690 adds/subtracts/negates
                    690 multiplies
                      0 divides
                     64 assignments
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   27 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdrhs()
{
/*
Generated 31-Jul-2007 11:59:41 by SD/FAST, Kane's formulation
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
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[3][0] = (pin[0][0]*udot[3]);
    Onkb[3][1] = (pin[0][1]*udot[3]);
    Onkb[3][2] = (pin[0][2]*udot[3]);
    Onkb[4][0] = ((pin[1][0]*udot[4])+((Cik[4][2][0]*Onkb[3][2])+((Cik[4][0][0]*
      Onkb[3][0])+(Cik[4][1][0]*Onkb[3][1]))));
    Onkb[4][1] = ((pin[1][1]*udot[4])+((Cik[4][2][1]*Onkb[3][2])+((Cik[4][0][1]*
      Onkb[3][0])+(Cik[4][1][1]*Onkb[3][1]))));
    Onkb[4][2] = ((pin[1][2]*udot[4])+((Cik[4][2][2]*Onkb[3][2])+((Cik[4][0][2]*
      Onkb[3][0])+(Cik[4][1][2]*Onkb[3][1]))));
    Onkb[5][0] = ((pin[2][0]*udot[5])+((Cik[5][2][0]*Onkb[4][2])+((Cik[5][0][0]*
      Onkb[4][0])+(Cik[5][1][0]*Onkb[4][1]))));
    Onkb[5][1] = ((pin[2][1]*udot[5])+((Cik[5][2][1]*Onkb[4][2])+((Cik[5][0][1]*
      Onkb[4][0])+(Cik[5][1][1]*Onkb[4][1]))));
    Onkb[5][2] = ((pin[2][2]*udot[5])+((Cik[5][2][2]*Onkb[4][2])+((Cik[5][0][2]*
      Onkb[4][0])+(Cik[5][1][2]*Onkb[4][1]))));
    Onkb[6][0] = ((pin[6][0]*udot[6])+((Cik[6][2][0]*Onkb[5][2])+((Cik[6][0][0]*
      Onkb[5][0])+(Cik[6][1][0]*Onkb[5][1]))));
    Onkb[6][1] = ((pin[6][1]*udot[6])+((Cik[6][2][1]*Onkb[5][2])+((Cik[6][0][1]*
      Onkb[5][0])+(Cik[6][1][1]*Onkb[5][1]))));
    Onkb[6][2] = ((pin[6][2]*udot[6])+((Cik[6][2][2]*Onkb[5][2])+((Cik[6][0][2]*
      Onkb[5][0])+(Cik[6][1][2]*Onkb[5][1]))));
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
    Onkb[11][0] = ((pin[11][0]*udot[11])+((Cik[11][2][0]*Onkb[8][2])+((
      Cik[11][0][0]*Onkb[8][0])+(Cik[11][1][0]*Onkb[8][1]))));
    Onkb[11][1] = ((pin[11][1]*udot[11])+((Cik[11][2][1]*Onkb[8][2])+((
      Cik[11][0][1]*Onkb[8][0])+(Cik[11][1][1]*Onkb[8][1]))));
    Onkb[11][2] = ((pin[11][2]*udot[11])+((Cik[11][2][2]*Onkb[8][2])+((
      Cik[11][0][2]*Onkb[8][0])+(Cik[11][1][2]*Onkb[8][1]))));
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
    Onkb[15][0] = ((pin[15][0]*udot[15])+((Cik[15][2][0]*Onkb[5][2])+((
      Cik[15][0][0]*Onkb[5][0])+(Cik[15][1][0]*Onkb[5][1]))));
    Onkb[15][1] = ((pin[15][1]*udot[15])+((Cik[15][2][1]*Onkb[5][2])+((
      Cik[15][0][1]*Onkb[5][0])+(Cik[15][1][1]*Onkb[5][1]))));
    Onkb[15][2] = ((pin[15][2]*udot[15])+((Cik[15][2][2]*Onkb[5][2])+((
      Cik[15][0][2]*Onkb[5][0])+(Cik[15][1][2]*Onkb[5][1]))));
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
    Onkb[20][0] = ((pin[20][0]*udot[20])+((Cik[20][2][0]*Onkb[17][2])+((
      Cik[20][0][0]*Onkb[17][0])+(Cik[20][1][0]*Onkb[17][1]))));
    Onkb[20][1] = ((pin[20][1]*udot[20])+((Cik[20][2][1]*Onkb[17][2])+((
      Cik[20][0][1]*Onkb[17][0])+(Cik[20][1][1]*Onkb[17][1]))));
    Onkb[20][2] = ((pin[20][2]*udot[20])+((Cik[20][2][2]*Onkb[17][2])+((
      Cik[20][0][2]*Onkb[17][0])+(Cik[20][1][2]*Onkb[17][1]))));
    Onkb[21][0] = ((pin[21][0]*udot[21])+((Cik[21][2][0]*Onkb[20][2])+((
      Cik[21][0][0]*Onkb[20][0])+(Cik[21][1][0]*Onkb[20][1]))));
    Onkb[21][1] = ((pin[21][1]*udot[21])+((Cik[21][2][1]*Onkb[20][2])+((
      Cik[21][0][1]*Onkb[20][0])+(Cik[21][1][1]*Onkb[20][1]))));
    Onkb[21][2] = ((pin[21][2]*udot[21])+((Cik[21][2][2]*Onkb[20][2])+((
      Cik[21][0][2]*Onkb[20][0])+(Cik[21][1][2]*Onkb[20][1]))));
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
    Onkb[24][0] = ((pin[24][0]*udot[24])+((Cik[24][2][0]*Onkb[5][2])+((
      Cik[24][0][0]*Onkb[5][0])+(Cik[24][1][0]*Onkb[5][1]))));
    Onkb[24][1] = ((pin[24][1]*udot[24])+((Cik[24][2][1]*Onkb[5][2])+((
      Cik[24][0][1]*Onkb[5][0])+(Cik[24][1][1]*Onkb[5][1]))));
    Onkb[24][2] = ((pin[24][2]*udot[24])+((Cik[24][2][2]*Onkb[5][2])+((
      Cik[24][0][2]*Onkb[5][0])+(Cik[24][1][2]*Onkb[5][1]))));
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
    onk[5][0] = (Onkb[5][0]+Otk[5][0]);
    onk[5][1] = (Onkb[5][1]+Otk[5][1]);
    onk[5][2] = (Onkb[5][2]+Otk[5][2]);
    onk[8][0] = (Onkb[8][0]+Otk[8][0]);
    onk[8][1] = (Onkb[8][1]+Otk[8][1]);
    onk[8][2] = (Onkb[8][2]+Otk[8][2]);
    onk[11][0] = (Onkb[11][0]+Otk[11][0]);
    onk[11][1] = (Onkb[11][1]+Otk[11][1]);
    onk[11][2] = (Onkb[11][2]+Otk[11][2]);
    onk[12][0] = (Onkb[12][0]+Otk[12][0]);
    onk[12][1] = (Onkb[12][1]+Otk[12][1]);
    onk[12][2] = (Onkb[12][2]+Otk[12][2]);
    onk[13][0] = (Onkb[13][0]+Otk[13][0]);
    onk[13][1] = (Onkb[13][1]+Otk[13][1]);
    onk[13][2] = (Onkb[13][2]+Otk[13][2]);
    onk[14][0] = (Onkb[14][0]+Otk[14][0]);
    onk[14][1] = (Onkb[14][1]+Otk[14][1]);
    onk[14][2] = (Onkb[14][2]+Otk[14][2]);
    onk[17][0] = (Onkb[17][0]+Otk[17][0]);
    onk[17][1] = (Onkb[17][1]+Otk[17][1]);
    onk[17][2] = (Onkb[17][2]+Otk[17][2]);
    onk[20][0] = (Onkb[20][0]+Otk[20][0]);
    onk[20][1] = (Onkb[20][1]+Otk[20][1]);
    onk[20][2] = (Onkb[20][2]+Otk[20][2]);
    onk[21][0] = (Onkb[21][0]+Otk[21][0]);
    onk[21][1] = (Onkb[21][1]+Otk[21][1]);
    onk[21][2] = (Onkb[21][2]+Otk[21][2]);
    onk[22][0] = (Onkb[22][0]+Otk[22][0]);
    onk[22][1] = (Onkb[22][1]+Otk[22][1]);
    onk[22][2] = (Onkb[22][2]+Otk[22][2]);
    onk[23][0] = (Onkb[23][0]+Otk[23][0]);
    onk[23][1] = (Onkb[23][1]+Otk[23][1]);
    onk[23][2] = (Onkb[23][2]+Otk[23][2]);
    onk[26][0] = (Onkb[26][0]+Otk[26][0]);
    onk[26][1] = (Onkb[26][1]+Otk[26][1]);
    onk[26][2] = (Onkb[26][2]+Otk[26][2]);
    onb[0][0] = onk[5][0];
    onb[0][1] = onk[5][1];
    onb[0][2] = onk[5][2];
    onb[1][0] = onk[8][0];
    onb[1][1] = onk[8][1];
    onb[1][2] = onk[8][2];
    onb[2][0] = onk[11][0];
    onb[2][1] = onk[11][1];
    onb[2][2] = onk[11][2];
    onb[3][0] = onk[12][0];
    onb[3][1] = onk[12][1];
    onb[3][2] = onk[12][2];
    onb[4][0] = onk[13][0];
    onb[4][1] = onk[13][1];
    onb[4][2] = onk[13][2];
    onb[5][0] = onk[14][0];
    onb[5][1] = onk[14][1];
    onb[5][2] = onk[14][2];
    onb[6][0] = onk[17][0];
    onb[6][1] = onk[17][1];
    onb[6][2] = onk[17][2];
    onb[7][0] = onk[20][0];
    onb[7][1] = onk[20][1];
    onb[7][2] = onk[20][2];
    onb[8][0] = onk[21][0];
    onb[8][1] = onk[21][1];
    onb[8][2] = onk[21][2];
    onb[9][0] = onk[22][0];
    onb[9][1] = onk[22][1];
    onb[9][2] = onk[22][2];
    onb[10][0] = onk[23][0];
    onb[10][1] = onk[23][1];
    onb[10][2] = onk[23][2];
    onb[11][0] = onk[26][0];
    onb[11][1] = onk[26][1];
    onb[11][2] = onk[26][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-onk[5][2]);
    dyad[0][0][2] = (onk[5][1]+w0w2[0]);
    dyad[0][1][0] = (onk[5][2]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-onk[5][0]);
    dyad[0][2][0] = (w0w2[0]-onk[5][1]);
    dyad[0][2][1] = (onk[5][0]+w1w2[0]);
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
    dyad[3][0][1] = (w0w1[3]-onk[12][2]);
    dyad[3][0][2] = (onk[12][1]+w0w2[3]);
    dyad[3][1][0] = (onk[12][2]+w0w1[3]);
    dyad[3][1][1] = w00w22[3];
    dyad[3][1][2] = (w1w2[3]-onk[12][0]);
    dyad[3][2][0] = (w0w2[3]-onk[12][1]);
    dyad[3][2][1] = (onk[12][0]+w1w2[3]);
    dyad[3][2][2] = w00w11[3];
    dyad[4][0][0] = w11w22[4];
    dyad[4][0][1] = (w0w1[4]-onk[13][2]);
    dyad[4][0][2] = (onk[13][1]+w0w2[4]);
    dyad[4][1][0] = (onk[13][2]+w0w1[4]);
    dyad[4][1][1] = w00w22[4];
    dyad[4][1][2] = (w1w2[4]-onk[13][0]);
    dyad[4][2][0] = (w0w2[4]-onk[13][1]);
    dyad[4][2][1] = (onk[13][0]+w1w2[4]);
    dyad[4][2][2] = w00w11[4];
    dyad[5][0][0] = w11w22[5];
    dyad[5][0][1] = (w0w1[5]-onk[14][2]);
    dyad[5][0][2] = (onk[14][1]+w0w2[5]);
    dyad[5][1][0] = (onk[14][2]+w0w1[5]);
    dyad[5][1][1] = w00w22[5];
    dyad[5][1][2] = (w1w2[5]-onk[14][0]);
    dyad[5][2][0] = (w0w2[5]-onk[14][1]);
    dyad[5][2][1] = (onk[14][0]+w1w2[5]);
    dyad[5][2][2] = w00w11[5];
    dyad[6][0][0] = w11w22[6];
    dyad[6][0][1] = (w0w1[6]-onk[17][2]);
    dyad[6][0][2] = (onk[17][1]+w0w2[6]);
    dyad[6][1][0] = (onk[17][2]+w0w1[6]);
    dyad[6][1][1] = w00w22[6];
    dyad[6][1][2] = (w1w2[6]-onk[17][0]);
    dyad[6][2][0] = (w0w2[6]-onk[17][1]);
    dyad[6][2][1] = (onk[17][0]+w1w2[6]);
    dyad[6][2][2] = w00w11[6];
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-onk[20][2]);
    dyad[7][0][2] = (onk[20][1]+w0w2[7]);
    dyad[7][1][0] = (onk[20][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-onk[20][0]);
    dyad[7][2][0] = (w0w2[7]-onk[20][1]);
    dyad[7][2][1] = (onk[20][0]+w1w2[7]);
    dyad[7][2][2] = w00w11[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-onk[21][2]);
    dyad[8][0][2] = (onk[21][1]+w0w2[8]);
    dyad[8][1][0] = (onk[21][2]+w0w1[8]);
    dyad[8][1][1] = w00w22[8];
    dyad[8][1][2] = (w1w2[8]-onk[21][0]);
    dyad[8][2][0] = (w0w2[8]-onk[21][1]);
    dyad[8][2][1] = (onk[21][0]+w1w2[8]);
    dyad[8][2][2] = w00w11[8];
    dyad[9][0][0] = w11w22[9];
    dyad[9][0][1] = (w0w1[9]-onk[22][2]);
    dyad[9][0][2] = (onk[22][1]+w0w2[9]);
    dyad[9][1][0] = (onk[22][2]+w0w1[9]);
    dyad[9][1][1] = w00w22[9];
    dyad[9][1][2] = (w1w2[9]-onk[22][0]);
    dyad[9][2][0] = (w0w2[9]-onk[22][1]);
    dyad[9][2][1] = (onk[22][0]+w1w2[9]);
    dyad[9][2][2] = w00w11[9];
    dyad[10][0][0] = w11w22[10];
    dyad[10][0][1] = (w0w1[10]-onk[23][2]);
    dyad[10][0][2] = (onk[23][1]+w0w2[10]);
    dyad[10][1][0] = (onk[23][2]+w0w1[10]);
    dyad[10][1][1] = w00w22[10];
    dyad[10][1][2] = (w1w2[10]-onk[23][0]);
    dyad[10][2][0] = (w0w2[10]-onk[23][1]);
    dyad[10][2][1] = (onk[23][0]+w1w2[10]);
    dyad[10][2][2] = w00w11[10];
    dyad[11][0][0] = w11w22[11];
    dyad[11][0][1] = (w0w1[11]-onk[26][2]);
    dyad[11][0][2] = (onk[26][1]+w0w2[11]);
    dyad[11][1][0] = (onk[26][2]+w0w1[11]);
    dyad[11][1][1] = w00w22[11];
    dyad[11][1][2] = (w1w2[11]-onk[26][0]);
    dyad[11][2][0] = (w0w2[11]-onk[26][1]);
    dyad[11][2][1] = (onk[26][0]+w1w2[11]);
    dyad[11][2][2] = w00w11[11];
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
    Ankb[4][0] = ((Ankb[3][2]*Cik[4][2][0])+((Ankb[3][0]*Cik[4][0][0])+(
      Ankb[3][1]*Cik[4][1][0])));
    Ankb[4][1] = ((Ankb[3][2]*Cik[4][2][1])+((Ankb[3][0]*Cik[4][0][1])+(
      Ankb[3][1]*Cik[4][1][1])));
    Ankb[4][2] = ((Ankb[3][2]*Cik[4][2][2])+((Ankb[3][0]*Cik[4][0][2])+(
      Ankb[3][1]*Cik[4][1][2])));
    Ankb[5][0] = (((Ankb[4][2]*Cik[5][2][0])+((Ankb[4][0]*Cik[5][0][0])+(
      Ankb[4][1]*Cik[5][1][0])))+((Onkb[5][2]*rk[0][1])-(Onkb[5][1]*rk[0][2])));
    Ankb[5][1] = (((Ankb[4][2]*Cik[5][2][1])+((Ankb[4][0]*Cik[5][0][1])+(
      Ankb[4][1]*Cik[5][1][1])))+((Onkb[5][0]*rk[0][2])-(Onkb[5][2]*rk[0][0])));
    Ankb[5][2] = (((Ankb[4][2]*Cik[5][2][2])+((Ankb[4][0]*Cik[5][0][2])+(
      Ankb[4][1]*Cik[5][1][2])))+((Onkb[5][1]*rk[0][0])-(Onkb[5][0]*rk[0][1])));
    AOnkri[6][0] = (Ankb[5][0]+((Onkb[5][1]*ri[1][2])-(Onkb[5][2]*ri[1][1])));
    AOnkri[6][1] = (Ankb[5][1]+((Onkb[5][2]*ri[1][0])-(Onkb[5][0]*ri[1][2])));
    AOnkri[6][2] = (Ankb[5][2]+((Onkb[5][0]*ri[1][1])-(Onkb[5][1]*ri[1][0])));
    Ankb[6][0] = ((AOnkri[6][2]*Cik[6][2][0])+((AOnkri[6][0]*Cik[6][0][0])+(
      AOnkri[6][1]*Cik[6][1][0])));
    Ankb[6][1] = ((AOnkri[6][2]*Cik[6][2][1])+((AOnkri[6][0]*Cik[6][0][1])+(
      AOnkri[6][1]*Cik[6][1][1])));
    Ankb[6][2] = ((AOnkri[6][2]*Cik[6][2][2])+((AOnkri[6][0]*Cik[6][0][2])+(
      AOnkri[6][1]*Cik[6][1][2])));
    Ankb[7][0] = ((Ankb[6][2]*Cik[7][2][0])+((Ankb[6][0]*Cik[7][0][0])+(
      Ankb[6][1]*Cik[7][1][0])));
    Ankb[7][1] = ((Ankb[6][2]*Cik[7][2][1])+((Ankb[6][0]*Cik[7][0][1])+(
      Ankb[6][1]*Cik[7][1][1])));
    Ankb[7][2] = ((Ankb[6][2]*Cik[7][2][2])+((Ankb[6][0]*Cik[7][0][2])+(
      Ankb[6][1]*Cik[7][1][2])));
    Ankb[8][0] = (((Ankb[7][2]*Cik[8][2][0])+((Ankb[7][0]*Cik[8][0][0])+(
      Ankb[7][1]*Cik[8][1][0])))+((Onkb[8][2]*rk[1][1])-(Onkb[8][1]*rk[1][2])));
    Ankb[8][1] = (((Ankb[7][2]*Cik[8][2][1])+((Ankb[7][0]*Cik[8][0][1])+(
      Ankb[7][1]*Cik[8][1][1])))+((Onkb[8][0]*rk[1][2])-(Onkb[8][2]*rk[1][0])));
    Ankb[8][2] = (((Ankb[7][2]*Cik[8][2][2])+((Ankb[7][0]*Cik[8][0][2])+(
      Ankb[7][1]*Cik[8][1][2])))+((Onkb[8][1]*rk[1][0])-(Onkb[8][0]*rk[1][1])));
    AOnkri[9][0] = (Ankb[8][0]+((Onkb[8][1]*ri[2][2])-(Onkb[8][2]*ri[2][1])));
    AOnkri[9][1] = (Ankb[8][1]+((Onkb[8][2]*ri[2][0])-(Onkb[8][0]*ri[2][2])));
    AOnkri[9][2] = (Ankb[8][2]+((Onkb[8][0]*ri[2][1])-(Onkb[8][1]*ri[2][0])));
    Ankb[9][0] = (AOnkri[9][0]+((pin[9][0]*udot[9])+((Onkb[8][1]*rpp[9][2])-(
      Onkb[8][2]*rpp[9][1]))));
    Ankb[9][1] = (AOnkri[9][1]+((pin[9][1]*udot[9])+((Onkb[8][2]*rpp[9][0])-(
      Onkb[8][0]*rpp[9][2]))));
    Ankb[9][2] = (AOnkri[9][2]+((pin[9][2]*udot[9])+((Onkb[8][0]*rpp[9][1])-(
      Onkb[8][1]*rpp[9][0]))));
    Ankb[10][0] = (Ankb[9][0]+((pin[10][0]*udot[10])+((Onkb[8][1]*rpp[10][2])-(
      Onkb[8][2]*rpp[10][1]))));
    Ankb[10][1] = (Ankb[9][1]+((pin[10][1]*udot[10])+((Onkb[8][2]*rpp[10][0])-(
      Onkb[8][0]*rpp[10][2]))));
    Ankb[10][2] = (Ankb[9][2]+((pin[10][2]*udot[10])+((Onkb[8][0]*rpp[10][1])-(
      Onkb[8][1]*rpp[10][0]))));
    Ankb[11][0] = (((Ankb[10][2]*Cik[11][2][0])+((Ankb[10][0]*Cik[11][0][0])+(
      Ankb[10][1]*Cik[11][1][0])))+((Onkb[11][2]*rk[2][1])-(Onkb[11][1]*rk[2][2]
      )));
    Ankb[11][1] = (((Ankb[10][2]*Cik[11][2][1])+((Ankb[10][0]*Cik[11][0][1])+(
      Ankb[10][1]*Cik[11][1][1])))+((Onkb[11][0]*rk[2][2])-(Onkb[11][2]*rk[2][0]
      )));
    Ankb[11][2] = (((Ankb[10][2]*Cik[11][2][2])+((Ankb[10][0]*Cik[11][0][2])+(
      Ankb[10][1]*Cik[11][1][2])))+((Onkb[11][1]*rk[2][0])-(Onkb[11][0]*rk[2][1]
      )));
    AOnkri[12][0] = (Ankb[11][0]+((Onkb[11][1]*ri[3][2])-(Onkb[11][2]*ri[3][1]))
      );
    AOnkri[12][1] = (Ankb[11][1]+((Onkb[11][2]*ri[3][0])-(Onkb[11][0]*ri[3][2]))
      );
    AOnkri[12][2] = (Ankb[11][2]+((Onkb[11][0]*ri[3][1])-(Onkb[11][1]*ri[3][0]))
      );
    Ankb[12][0] = (((AOnkri[12][2]*Cik[12][2][0])+((AOnkri[12][0]*Cik[12][0][0])
      +(AOnkri[12][1]*Cik[12][1][0])))+((Onkb[12][2]*rk[3][1])-(Onkb[12][1]*
      rk[3][2])));
    Ankb[12][1] = (((AOnkri[12][2]*Cik[12][2][1])+((AOnkri[12][0]*Cik[12][0][1])
      +(AOnkri[12][1]*Cik[12][1][1])))+((Onkb[12][0]*rk[3][2])-(Onkb[12][2]*
      rk[3][0])));
    Ankb[12][2] = (((AOnkri[12][2]*Cik[12][2][2])+((AOnkri[12][0]*Cik[12][0][2])
      +(AOnkri[12][1]*Cik[12][1][2])))+((Onkb[12][1]*rk[3][0])-(Onkb[12][0]*
      rk[3][1])));
    AOnkri[13][0] = (Ankb[12][0]+((Onkb[12][1]*ri[4][2])-(Onkb[12][2]*ri[4][1]))
      );
    AOnkri[13][1] = (Ankb[12][1]+((Onkb[12][2]*ri[4][0])-(Onkb[12][0]*ri[4][2]))
      );
    AOnkri[13][2] = (Ankb[12][2]+((Onkb[12][0]*ri[4][1])-(Onkb[12][1]*ri[4][0]))
      );
    Ankb[13][0] = (((AOnkri[13][2]*Cik[13][2][0])+((AOnkri[13][0]*Cik[13][0][0])
      +(AOnkri[13][1]*Cik[13][1][0])))+((Onkb[13][2]*rk[4][1])-(Onkb[13][1]*
      rk[4][2])));
    Ankb[13][1] = (((AOnkri[13][2]*Cik[13][2][1])+((AOnkri[13][0]*Cik[13][0][1])
      +(AOnkri[13][1]*Cik[13][1][1])))+((Onkb[13][0]*rk[4][2])-(Onkb[13][2]*
      rk[4][0])));
    Ankb[13][2] = (((AOnkri[13][2]*Cik[13][2][2])+((AOnkri[13][0]*Cik[13][0][2])
      +(AOnkri[13][1]*Cik[13][1][2])))+((Onkb[13][1]*rk[4][0])-(Onkb[13][0]*
      rk[4][1])));
    AOnkri[14][0] = (Ankb[13][0]+((Onkb[13][1]*ri[5][2])-(Onkb[13][2]*ri[5][1]))
      );
    AOnkri[14][1] = (Ankb[13][1]+((Onkb[13][2]*ri[5][0])-(Onkb[13][0]*ri[5][2]))
      );
    AOnkri[14][2] = (Ankb[13][2]+((Onkb[13][0]*ri[5][1])-(Onkb[13][1]*ri[5][0]))
      );
    Ankb[14][0] = (((AOnkri[14][2]*Cik[14][2][0])+((AOnkri[14][0]*Cik[14][0][0])
      +(AOnkri[14][1]*Cik[14][1][0])))+((Onkb[14][2]*rk[5][1])-(Onkb[14][1]*
      rk[5][2])));
    Ankb[14][1] = (((AOnkri[14][2]*Cik[14][2][1])+((AOnkri[14][0]*Cik[14][0][1])
      +(AOnkri[14][1]*Cik[14][1][1])))+((Onkb[14][0]*rk[5][2])-(Onkb[14][2]*
      rk[5][0])));
    Ankb[14][2] = (((AOnkri[14][2]*Cik[14][2][2])+((AOnkri[14][0]*Cik[14][0][2])
      +(AOnkri[14][1]*Cik[14][1][2])))+((Onkb[14][1]*rk[5][0])-(Onkb[14][0]*
      rk[5][1])));
    AOnkri[15][0] = (Ankb[5][0]+((Onkb[5][1]*ri[6][2])-(Onkb[5][2]*ri[6][1])));
    AOnkri[15][1] = (Ankb[5][1]+((Onkb[5][2]*ri[6][0])-(Onkb[5][0]*ri[6][2])));
    AOnkri[15][2] = (Ankb[5][2]+((Onkb[5][0]*ri[6][1])-(Onkb[5][1]*ri[6][0])));
    Ankb[15][0] = ((AOnkri[15][2]*Cik[15][2][0])+((AOnkri[15][0]*Cik[15][0][0])+
      (AOnkri[15][1]*Cik[15][1][0])));
    Ankb[15][1] = ((AOnkri[15][2]*Cik[15][2][1])+((AOnkri[15][0]*Cik[15][0][1])+
      (AOnkri[15][1]*Cik[15][1][1])));
    Ankb[15][2] = ((AOnkri[15][2]*Cik[15][2][2])+((AOnkri[15][0]*Cik[15][0][2])+
      (AOnkri[15][1]*Cik[15][1][2])));
    Ankb[16][0] = ((Ankb[15][2]*Cik[16][2][0])+((Ankb[15][0]*Cik[16][0][0])+(
      Ankb[15][1]*Cik[16][1][0])));
    Ankb[16][1] = ((Ankb[15][2]*Cik[16][2][1])+((Ankb[15][0]*Cik[16][0][1])+(
      Ankb[15][1]*Cik[16][1][1])));
    Ankb[16][2] = ((Ankb[15][2]*Cik[16][2][2])+((Ankb[15][0]*Cik[16][0][2])+(
      Ankb[15][1]*Cik[16][1][2])));
    Ankb[17][0] = (((Ankb[16][2]*Cik[17][2][0])+((Ankb[16][0]*Cik[17][0][0])+(
      Ankb[16][1]*Cik[17][1][0])))+((Onkb[17][2]*rk[6][1])-(Onkb[17][1]*rk[6][2]
      )));
    Ankb[17][1] = (((Ankb[16][2]*Cik[17][2][1])+((Ankb[16][0]*Cik[17][0][1])+(
      Ankb[16][1]*Cik[17][1][1])))+((Onkb[17][0]*rk[6][2])-(Onkb[17][2]*rk[6][0]
      )));
    Ankb[17][2] = (((Ankb[16][2]*Cik[17][2][2])+((Ankb[16][0]*Cik[17][0][2])+(
      Ankb[16][1]*Cik[17][1][2])))+((Onkb[17][1]*rk[6][0])-(Onkb[17][0]*rk[6][1]
      )));
    AOnkri[18][0] = (Ankb[17][0]+((Onkb[17][1]*ri[7][2])-(Onkb[17][2]*ri[7][1]))
      );
    AOnkri[18][1] = (Ankb[17][1]+((Onkb[17][2]*ri[7][0])-(Onkb[17][0]*ri[7][2]))
      );
    AOnkri[18][2] = (Ankb[17][2]+((Onkb[17][0]*ri[7][1])-(Onkb[17][1]*ri[7][0]))
      );
    Ankb[18][0] = (AOnkri[18][0]+((pin[18][0]*udot[18])+((Onkb[17][1]*rpp[18][2]
      )-(Onkb[17][2]*rpp[18][1]))));
    Ankb[18][1] = (AOnkri[18][1]+((pin[18][1]*udot[18])+((Onkb[17][2]*rpp[18][0]
      )-(Onkb[17][0]*rpp[18][2]))));
    Ankb[18][2] = (AOnkri[18][2]+((pin[18][2]*udot[18])+((Onkb[17][0]*rpp[18][1]
      )-(Onkb[17][1]*rpp[18][0]))));
    Ankb[19][0] = (Ankb[18][0]+((pin[19][0]*udot[19])+((Onkb[17][1]*rpp[19][2])-
      (Onkb[17][2]*rpp[19][1]))));
    Ankb[19][1] = (Ankb[18][1]+((pin[19][1]*udot[19])+((Onkb[17][2]*rpp[19][0])-
      (Onkb[17][0]*rpp[19][2]))));
    Ankb[19][2] = (Ankb[18][2]+((pin[19][2]*udot[19])+((Onkb[17][0]*rpp[19][1])-
      (Onkb[17][1]*rpp[19][0]))));
    Ankb[20][0] = (((Ankb[19][2]*Cik[20][2][0])+((Ankb[19][0]*Cik[20][0][0])+(
      Ankb[19][1]*Cik[20][1][0])))+((Onkb[20][2]*rk[7][1])-(Onkb[20][1]*rk[7][2]
      )));
    Ankb[20][1] = (((Ankb[19][2]*Cik[20][2][1])+((Ankb[19][0]*Cik[20][0][1])+(
      Ankb[19][1]*Cik[20][1][1])))+((Onkb[20][0]*rk[7][2])-(Onkb[20][2]*rk[7][0]
      )));
    Ankb[20][2] = (((Ankb[19][2]*Cik[20][2][2])+((Ankb[19][0]*Cik[20][0][2])+(
      Ankb[19][1]*Cik[20][1][2])))+((Onkb[20][1]*rk[7][0])-(Onkb[20][0]*rk[7][1]
      )));
    AOnkri[21][0] = (Ankb[20][0]+((Onkb[20][1]*ri[8][2])-(Onkb[20][2]*ri[8][1]))
      );
    AOnkri[21][1] = (Ankb[20][1]+((Onkb[20][2]*ri[8][0])-(Onkb[20][0]*ri[8][2]))
      );
    AOnkri[21][2] = (Ankb[20][2]+((Onkb[20][0]*ri[8][1])-(Onkb[20][1]*ri[8][0]))
      );
    Ankb[21][0] = (((AOnkri[21][2]*Cik[21][2][0])+((AOnkri[21][0]*Cik[21][0][0])
      +(AOnkri[21][1]*Cik[21][1][0])))+((Onkb[21][2]*rk[8][1])-(Onkb[21][1]*
      rk[8][2])));
    Ankb[21][1] = (((AOnkri[21][2]*Cik[21][2][1])+((AOnkri[21][0]*Cik[21][0][1])
      +(AOnkri[21][1]*Cik[21][1][1])))+((Onkb[21][0]*rk[8][2])-(Onkb[21][2]*
      rk[8][0])));
    Ankb[21][2] = (((AOnkri[21][2]*Cik[21][2][2])+((AOnkri[21][0]*Cik[21][0][2])
      +(AOnkri[21][1]*Cik[21][1][2])))+((Onkb[21][1]*rk[8][0])-(Onkb[21][0]*
      rk[8][1])));
    AOnkri[22][0] = (Ankb[21][0]+((Onkb[21][1]*ri[9][2])-(Onkb[21][2]*ri[9][1]))
      );
    AOnkri[22][1] = (Ankb[21][1]+((Onkb[21][2]*ri[9][0])-(Onkb[21][0]*ri[9][2]))
      );
    AOnkri[22][2] = (Ankb[21][2]+((Onkb[21][0]*ri[9][1])-(Onkb[21][1]*ri[9][0]))
      );
    Ankb[22][0] = (((AOnkri[22][2]*Cik[22][2][0])+((AOnkri[22][0]*Cik[22][0][0])
      +(AOnkri[22][1]*Cik[22][1][0])))+((Onkb[22][2]*rk[9][1])-(Onkb[22][1]*
      rk[9][2])));
    Ankb[22][1] = (((AOnkri[22][2]*Cik[22][2][1])+((AOnkri[22][0]*Cik[22][0][1])
      +(AOnkri[22][1]*Cik[22][1][1])))+((Onkb[22][0]*rk[9][2])-(Onkb[22][2]*
      rk[9][0])));
    Ankb[22][2] = (((AOnkri[22][2]*Cik[22][2][2])+((AOnkri[22][0]*Cik[22][0][2])
      +(AOnkri[22][1]*Cik[22][1][2])))+((Onkb[22][1]*rk[9][0])-(Onkb[22][0]*
      rk[9][1])));
    AOnkri[23][0] = (Ankb[22][0]+((Onkb[22][1]*ri[10][2])-(Onkb[22][2]*ri[10][1]
      )));
    AOnkri[23][1] = (Ankb[22][1]+((Onkb[22][2]*ri[10][0])-(Onkb[22][0]*ri[10][2]
      )));
    AOnkri[23][2] = (Ankb[22][2]+((Onkb[22][0]*ri[10][1])-(Onkb[22][1]*ri[10][0]
      )));
    Ankb[23][0] = (((AOnkri[23][2]*Cik[23][2][0])+((AOnkri[23][0]*Cik[23][0][0])
      +(AOnkri[23][1]*Cik[23][1][0])))+((Onkb[23][2]*rk[10][1])-(Onkb[23][1]*
      rk[10][2])));
    Ankb[23][1] = (((AOnkri[23][2]*Cik[23][2][1])+((AOnkri[23][0]*Cik[23][0][1])
      +(AOnkri[23][1]*Cik[23][1][1])))+((Onkb[23][0]*rk[10][2])-(Onkb[23][2]*
      rk[10][0])));
    Ankb[23][2] = (((AOnkri[23][2]*Cik[23][2][2])+((AOnkri[23][0]*Cik[23][0][2])
      +(AOnkri[23][1]*Cik[23][1][2])))+((Onkb[23][1]*rk[10][0])-(Onkb[23][0]*
      rk[10][1])));
    AOnkri[24][0] = (Ankb[5][0]+((Onkb[5][1]*ri[11][2])-(Onkb[5][2]*ri[11][1])))
      ;
    AOnkri[24][1] = (Ankb[5][1]+((Onkb[5][2]*ri[11][0])-(Onkb[5][0]*ri[11][2])))
      ;
    AOnkri[24][2] = (Ankb[5][2]+((Onkb[5][0]*ri[11][1])-(Onkb[5][1]*ri[11][0])))
      ;
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
    Ankb[26][0] = (((Ankb[25][2]*Cik[26][2][0])+((Ankb[25][0]*Cik[26][0][0])+(
      Ankb[25][1]*Cik[26][1][0])))+((Onkb[26][2]*rk[11][1])-(Onkb[26][1]*
      rk[11][2])));
    Ankb[26][1] = (((Ankb[25][2]*Cik[26][2][1])+((Ankb[25][0]*Cik[26][0][1])+(
      Ankb[25][1]*Cik[26][1][1])))+((Onkb[26][0]*rk[11][2])-(Onkb[26][2]*
      rk[11][0])));
    Ankb[26][2] = (((Ankb[25][2]*Cik[26][2][2])+((Ankb[25][0]*Cik[26][0][2])+(
      Ankb[25][1]*Cik[26][1][2])))+((Onkb[26][1]*rk[11][0])-(Onkb[26][0]*
      rk[11][1])));
    AnkAtk[5][0] = (Ankb[5][0]+Atk[5][0]);
    AnkAtk[5][1] = (Ankb[5][1]+Atk[5][1]);
    AnkAtk[5][2] = (Ankb[5][2]+Atk[5][2]);
    ank[5][0] = ((AnkAtk[5][2]*cnk[5][0][2])+((AnkAtk[5][0]*cnk[5][0][0])+(
      AnkAtk[5][1]*cnk[5][0][1])));
    ank[5][1] = ((AnkAtk[5][2]*cnk[5][1][2])+((AnkAtk[5][0]*cnk[5][1][0])+(
      AnkAtk[5][1]*cnk[5][1][1])));
    ank[5][2] = ((AnkAtk[5][2]*cnk[5][2][2])+((AnkAtk[5][0]*cnk[5][2][0])+(
      AnkAtk[5][1]*cnk[5][2][1])));
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
    AnkAtk[12][0] = (Ankb[12][0]+Atk[12][0]);
    AnkAtk[12][1] = (Ankb[12][1]+Atk[12][1]);
    AnkAtk[12][2] = (Ankb[12][2]+Atk[12][2]);
    ank[12][0] = ((AnkAtk[12][2]*cnk[12][0][2])+((AnkAtk[12][0]*cnk[12][0][0])+(
      AnkAtk[12][1]*cnk[12][0][1])));
    ank[12][1] = ((AnkAtk[12][2]*cnk[12][1][2])+((AnkAtk[12][0]*cnk[12][1][0])+(
      AnkAtk[12][1]*cnk[12][1][1])));
    ank[12][2] = ((AnkAtk[12][2]*cnk[12][2][2])+((AnkAtk[12][0]*cnk[12][2][0])+(
      AnkAtk[12][1]*cnk[12][2][1])));
    AnkAtk[13][0] = (Ankb[13][0]+Atk[13][0]);
    AnkAtk[13][1] = (Ankb[13][1]+Atk[13][1]);
    AnkAtk[13][2] = (Ankb[13][2]+Atk[13][2]);
    ank[13][0] = ((AnkAtk[13][2]*cnk[13][0][2])+((AnkAtk[13][0]*cnk[13][0][0])+(
      AnkAtk[13][1]*cnk[13][0][1])));
    ank[13][1] = ((AnkAtk[13][2]*cnk[13][1][2])+((AnkAtk[13][0]*cnk[13][1][0])+(
      AnkAtk[13][1]*cnk[13][1][1])));
    ank[13][2] = ((AnkAtk[13][2]*cnk[13][2][2])+((AnkAtk[13][0]*cnk[13][2][0])+(
      AnkAtk[13][1]*cnk[13][2][1])));
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
    AnkAtk[21][0] = (Ankb[21][0]+Atk[21][0]);
    AnkAtk[21][1] = (Ankb[21][1]+Atk[21][1]);
    AnkAtk[21][2] = (Ankb[21][2]+Atk[21][2]);
    ank[21][0] = ((AnkAtk[21][2]*cnk[21][0][2])+((AnkAtk[21][0]*cnk[21][0][0])+(
      AnkAtk[21][1]*cnk[21][0][1])));
    ank[21][1] = ((AnkAtk[21][2]*cnk[21][1][2])+((AnkAtk[21][0]*cnk[21][1][0])+(
      AnkAtk[21][1]*cnk[21][1][1])));
    ank[21][2] = ((AnkAtk[21][2]*cnk[21][2][2])+((AnkAtk[21][0]*cnk[21][2][0])+(
      AnkAtk[21][1]*cnk[21][2][1])));
    AnkAtk[22][0] = (Ankb[22][0]+Atk[22][0]);
    AnkAtk[22][1] = (Ankb[22][1]+Atk[22][1]);
    AnkAtk[22][2] = (Ankb[22][2]+Atk[22][2]);
    ank[22][0] = ((AnkAtk[22][2]*cnk[22][0][2])+((AnkAtk[22][0]*cnk[22][0][0])+(
      AnkAtk[22][1]*cnk[22][0][1])));
    ank[22][1] = ((AnkAtk[22][2]*cnk[22][1][2])+((AnkAtk[22][0]*cnk[22][1][0])+(
      AnkAtk[22][1]*cnk[22][1][1])));
    ank[22][2] = ((AnkAtk[22][2]*cnk[22][2][2])+((AnkAtk[22][0]*cnk[22][2][0])+(
      AnkAtk[22][1]*cnk[22][2][1])));
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
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    anb[1][0] = ank[8][0];
    anb[1][1] = ank[8][1];
    anb[1][2] = ank[8][2];
    anb[2][0] = ank[11][0];
    anb[2][1] = ank[11][1];
    anb[2][2] = ank[11][2];
    anb[3][0] = ank[12][0];
    anb[3][1] = ank[12][1];
    anb[3][2] = ank[12][2];
    anb[4][0] = ank[13][0];
    anb[4][1] = ank[13][1];
    anb[4][2] = ank[13][2];
    anb[5][0] = ank[14][0];
    anb[5][1] = ank[14][1];
    anb[5][2] = ank[14][2];
    anb[6][0] = ank[17][0];
    anb[6][1] = ank[17][1];
    anb[6][2] = ank[17][2];
    anb[7][0] = ank[20][0];
    anb[7][1] = ank[20][1];
    anb[7][2] = ank[20][2];
    anb[8][0] = ank[21][0];
    anb[8][1] = ank[21][1];
    anb[8][2] = ank[21][2];
    anb[9][0] = ank[22][0];
    anb[9][1] = ank[22][1];
    anb[9][2] = ank[22][2];
    anb[10][0] = ank[23][0];
    anb[10][1] = ank[23][1];
    anb[10][2] = ank[23][2];
    anb[11][0] = ank[26][0];
    anb[11][1] = ank[26][1];
    anb[11][2] = ank[26][2];
/*
Compute constraint acceleration errors
*/
    roustate = 3;
    sduaerr(curtim,q,u,udot,&aerr[23]);
/*
 Used 0.17 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  714 adds/subtracts/negates
                    702 multiplies
                      0 divides
                    489 assignments
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
    double errs[27];
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
    if (pres[11]  !=  0.) {
        perr[9] = (q[11]-upos[11]);
    } else {
        perr[9] = 0.;
    }
    if (pres[12]  !=  0.) {
        perr[10] = (q[12]-upos[12]);
    } else {
        perr[10] = 0.;
    }
    if (pres[13]  !=  0.) {
        perr[11] = (q[13]-upos[13]);
    } else {
        perr[11] = 0.;
    }
    if (pres[14]  !=  0.) {
        perr[12] = (q[14]-upos[14]);
    } else {
        perr[12] = 0.;
    }
    if (pres[15]  !=  0.) {
        perr[13] = (q[15]-upos[15]);
    } else {
        perr[13] = 0.;
    }
    if (pres[16]  !=  0.) {
        perr[14] = (q[16]-upos[16]);
    } else {
        perr[14] = 0.;
    }
    if (pres[17]  !=  0.) {
        perr[15] = (q[17]-upos[17]);
    } else {
        perr[15] = 0.;
    }
    if (pres[20]  !=  0.) {
        perr[16] = (q[20]-upos[20]);
    } else {
        perr[16] = 0.;
    }
    if (pres[21]  !=  0.) {
        perr[17] = (q[21]-upos[21]);
    } else {
        perr[17] = 0.;
    }
    if (pres[22]  !=  0.) {
        perr[18] = (q[22]-upos[22]);
    } else {
        perr[18] = 0.;
    }
    if (pres[23]  !=  0.) {
        perr[19] = (q[23]-upos[23]);
    } else {
        perr[19] = 0.;
    }
    if (pres[24]  !=  0.) {
        perr[20] = (q[24]-upos[24]);
    } else {
        perr[20] = 0.;
    }
    if (pres[25]  !=  0.) {
        perr[21] = (q[25]-upos[25]);
    } else {
        perr[21] = 0.;
    }
    if (pres[26]  !=  0.) {
        perr[22] = (q[26]-upos[26]);
    } else {
        perr[22] = 0.;
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
}

sdverr(errs)
    double errs[27];
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
    if (pres[11]  !=  0.) {
        verr[9] = (u[11]-uvel[11]);
    } else {
        verr[9] = 0.;
    }
    if (pres[12]  !=  0.) {
        verr[10] = (u[12]-uvel[12]);
    } else {
        verr[10] = 0.;
    }
    if (pres[13]  !=  0.) {
        verr[11] = (u[13]-uvel[13]);
    } else {
        verr[11] = 0.;
    }
    if (pres[14]  !=  0.) {
        verr[12] = (u[14]-uvel[14]);
    } else {
        verr[12] = 0.;
    }
    if (pres[15]  !=  0.) {
        verr[13] = (u[15]-uvel[15]);
    } else {
        verr[13] = 0.;
    }
    if (pres[16]  !=  0.) {
        verr[14] = (u[16]-uvel[16]);
    } else {
        verr[14] = 0.;
    }
    if (pres[17]  !=  0.) {
        verr[15] = (u[17]-uvel[17]);
    } else {
        verr[15] = 0.;
    }
    if (pres[20]  !=  0.) {
        verr[16] = (u[20]-uvel[20]);
    } else {
        verr[16] = 0.;
    }
    if (pres[21]  !=  0.) {
        verr[17] = (u[21]-uvel[21]);
    } else {
        verr[17] = 0.;
    }
    if (pres[22]  !=  0.) {
        verr[18] = (u[22]-uvel[22]);
    } else {
        verr[18] = 0.;
    }
    if (pres[23]  !=  0.) {
        verr[19] = (u[23]-uvel[23]);
    } else {
        verr[19] = 0.;
    }
    if (pres[24]  !=  0.) {
        verr[20] = (u[24]-uvel[24]);
    } else {
        verr[20] = 0.;
    }
    if (pres[25]  !=  0.) {
        verr[21] = (u[25]-uvel[25]);
    } else {
        verr[21] = 0.;
    }
    if (pres[26]  !=  0.) {
        verr[22] = (u[26]-uvel[26]);
    } else {
        verr[22] = 0.;
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
}

sdaerr(errs)
    double errs[27];
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
    if (pres[11]  !=  0.) {
        aerr[9] = (udot[11]-uacc[11]);
    } else {
        aerr[9] = 0.;
    }
    if (pres[12]  !=  0.) {
        aerr[10] = (udot[12]-uacc[12]);
    } else {
        aerr[10] = 0.;
    }
    if (pres[13]  !=  0.) {
        aerr[11] = (udot[13]-uacc[13]);
    } else {
        aerr[11] = 0.;
    }
    if (pres[14]  !=  0.) {
        aerr[12] = (udot[14]-uacc[14]);
    } else {
        aerr[12] = 0.;
    }
    if (pres[15]  !=  0.) {
        aerr[13] = (udot[15]-uacc[15]);
    } else {
        aerr[13] = 0.;
    }
    if (pres[16]  !=  0.) {
        aerr[14] = (udot[16]-uacc[16]);
    } else {
        aerr[14] = 0.;
    }
    if (pres[17]  !=  0.) {
        aerr[15] = (udot[17]-uacc[17]);
    } else {
        aerr[15] = 0.;
    }
    if (pres[20]  !=  0.) {
        aerr[16] = (udot[20]-uacc[20]);
    } else {
        aerr[16] = 0.;
    }
    if (pres[21]  !=  0.) {
        aerr[17] = (udot[21]-uacc[21]);
    } else {
        aerr[17] = 0.;
    }
    if (pres[22]  !=  0.) {
        aerr[18] = (udot[22]-uacc[22]);
    } else {
        aerr[18] = 0.;
    }
    if (pres[23]  !=  0.) {
        aerr[19] = (udot[23]-uacc[23]);
    } else {
        aerr[19] = 0.;
    }
    if (pres[24]  !=  0.) {
        aerr[20] = (udot[24]-uacc[24]);
    } else {
        aerr[20] = 0.;
    }
    if (pres[25]  !=  0.) {
        aerr[21] = (udot[25]-uacc[25]);
    } else {
        aerr[21] = 0.;
    }
    if (pres[26]  !=  0.) {
        aerr[22] = (udot[26]-uacc[26]);
    } else {
        aerr[22] = 0.;
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

sdpresvel(joint,axis,prval)
    int joint,axis;
    double prval;
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

sdprespos(joint,axis,prval)
    int joint,axis;
    double prval;
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
    double pp[27][27],dpp[27][27];
    int i,j,c;
    double sum;
    double dfk[12][3],dtk[12][3],dtau[27],dltci[1][3],dltc[1][3],dlfci[1][3],
      dlfc[1][3];
    double dTinb[1][3],dToutb[1][3],dltaufi[1][3],dltaufo[1][3],dltauti[1][3],
      dltauto[1][3];
    double umult[4];
    double dfs[27],row[27],dinvrow[27];

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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[8][i] = row[i];
            dpp[i][8] = dinvrow[i];
        }
        wmap[8] = 8;
/*
Constraint 9 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[9][i] = row[i];
            dpp[i][9] = dinvrow[i];
        }
        wmap[9] = 9;
/*
Constraint 10 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[10][i] = row[i];
            dpp[i][10] = dinvrow[i];
        }
        wmap[10] = 10;
/*
Constraint 11 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[11][i] = row[i];
            dpp[i][11] = dinvrow[i];
        }
        wmap[11] = 11;
/*
Constraint 12 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[12][i] = row[i];
            dpp[i][12] = dinvrow[i];
        }
        wmap[12] = 12;
/*
Constraint 13 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[13][i] = row[i];
            dpp[i][13] = dinvrow[i];
        }
        wmap[13] = 13;
/*
Constraint 14 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[14][i] = row[i];
            dpp[i][14] = dinvrow[i];
        }
        wmap[14] = 14;
/*
Constraint 15 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[15][i] = row[i];
            dpp[i][15] = dinvrow[i];
        }
        wmap[15] = 15;
/*
Constraint 16 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[16][i] = row[i];
            dpp[i][16] = dinvrow[i];
        }
        wmap[16] = 16;
/*
Constraint 17 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[17][i] = row[i];
            dpp[i][17] = dinvrow[i];
        }
        wmap[17] = 17;
/*
Constraint 18 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[18][i] = row[i];
            dpp[i][18] = dinvrow[i];
        }
        wmap[18] = 18;
/*
Constraint 19 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[19][i] = row[i];
            dpp[i][19] = dinvrow[i];
        }
        wmap[19] = 19;
/*
Constraint 20 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[20][i] = row[i];
            dpp[i][20] = dinvrow[i];
        }
        wmap[20] = 20;
/*
Constraint 21 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[21][i] = row[i];
            dpp[i][21] = dinvrow[i];
        }
        wmap[21] = 21;
/*
Constraint 22 (prescribed motion)
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
        sdldubsl(27,27,mmap,mlo,dfs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[22][i] = row[i];
            dpp[i][22] = dinvrow[i];
        }
        wmap[22] = 22;
/*
Constraint 23 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 11; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 26; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 1.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(27,27,mmap,mlo,fs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[23][i] = row[i];
            dpp[i][23] = dinvrow[i];
        }
        wmap[23] = 23;
/*
Constraint 24 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 11; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 26; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 1.;
        umult[2] = 0.;
        umult[3] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(27,27,mmap,mlo,fs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[24][i] = row[i];
            dpp[i][24] = dinvrow[i];
        }
        wmap[24] = 24;
/*
Constraint 25 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 11; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 26; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 1.;
        umult[3] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(27,27,mmap,mlo,fs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[25][i] = row[i];
            dpp[i][25] = dinvrow[i];
        }
        wmap[25] = 25;
/*
Constraint 26 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 11; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 26; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 1.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(27,27,mmap,mlo,fs,row);
        sdldubsd(27,27,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 26; i++) {
            pp[26][i] = row[i];
            dpp[i][26] = dinvrow[i];
        }
        wmap[26] = 26;
/*
Produce constraint coefficient matrix WW
*/
        for (c = 0; c <= 26; c++) {
            for (i = c; i <= 26; i++) {
                sum = 0.;
                for (j = 0; j <= 26; j++) {
                    sum = sum+pp[wmap[c]][j]*dpp[j][wmap[i]];
                }
                ww[wmap[c]][wmap[i]] = sum;
                ww[wmap[i]][wmap[c]] = sum;
            }
        }
/*
Form QR decomposition of WW
*/
        sdqrdcomp(27,27,27,27,wmap,wmap,ww,qraux,jpvt);
        wwflg = 1;
    }
/*
 Used 1.38 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 10206 adds/subtracts/negates
                   10206 multiplies
                      0 divides
                   13877 assignments
*/
}

sdxudot0(routine,oudot0)
    int routine;
    double oudot0[27];
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
    sdldubslv(27,27,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 26; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdudot0(oudot0)
    double oudot0[27];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

sdsetudot(iudot)
    double iudot[27];
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 26; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

sdxudotm(routine,imult,oudotm)
    int routine;
    double imult[27],oudotm[27];
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    sdmfrc(imult);
    sdfsmult();
    sdldubslv(27,27,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 26; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     27 assignments
*/
}

sdudotm(imult,oudotm)
    double imult[27],oudotm[27];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

sdderiv(oqdot,oudot)
    double oqdot[27],oudot[27];
{
/*
This is the derivative section for a 12-body ground-based
system with 27 hinge degree(s) of freedom.
23 of the degrees of freedom may follow prescribed motion.
There are 27 constraints.
*/
    double workr[27],bb[27],b0[27],v0[27],p0[27];
    int iwork[27];
    int i,j;
    double udot0[27],udot1[27];

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
    wsiz = 27;
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
    for (i = 0; i <= 26; i++) {
        bb[i] = -b0[i];
    }
    if (stabvel  !=  0.) {
        for (i = 0; i <= 26; i++) {
            bb[i] = bb[i]-stabvel*v0[i];
        }
    }
    if (stabpos  !=  0.) {
        for (i = 0; i <= 26; i++) {
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
    sdqrbslv(27,27,27,27,wmap,wmap,1e-13,workr,iwork,ww,qraux,jpvt,bb,mult,&
      wrank);
    for (i = 0; i <= 26; i++) {
        multmap[i] = 0;
    }
    for (i = 0; i < wrank; i++) {
        multmap[jpvt[i]] = 1;
    }
    j = 0;
    for (i = 0; i <= 26; i++) {
        if (multmap[i] != 0) {
            multmap[j] = wmap[i];
            j = j+1;
        }
    }
/*
Compute final udots
*/
    sdxudotm(17,mult,udot1);
    for (i = 0; i <= 26; i++) {
        udot[i] = udot0[i]+udot1[i];
    }
    sdrhs();
    for (i = 0; i <= 26; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 26; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  108 adds/subtracts/negates
                     54 multiplies
                      0 divides
                    162 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

sdresid(eqdot,eudot,emults,resid)
    double eqdot[27],eudot[27],emults[27],resid[81];
{
    int i;
    double uderrs[27],p0[27];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 27; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 27; i++) {
        resid[27+i] = uderrs[i];
    }
    sdverr(&resid[54]);
    if (stabpos  !=  0.) {
        sdperr(p0);
        for (i = 0; i < 27; i++) {
            resid[54+i] = resid[54+i]+stabpos*p0[i];
        }
    }
    for (i = 0; i < 27; i++) {
        udot[i] = eudot[i];
    }
    for (i = 0; i < 27; i++) {
        mult[i] = emults[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   54 adds/subtracts/negates
                     27 multiplies
                      0 divides
                    135 assignments
*/
}

sdmult(omults,owrank,omultmap)
    double omults[27];
    int *owrank,omultmap[27];
{
    int i;

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    for (i = 0; i < 27; i++) {
        omults[i] = mult[i];
        if (i <= wrank-1) {
            omultmap[i] = multmap[i];
        } else {
            omultmap[i] = -1;
        }
    }
    *owrank = wrank;
}

sdreac(force,torque)
    double force[12][3],torque[12][3];
{
/*
Generated 31-Jul-2007 11:59:43 by SD/FAST, Kane's formulation
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
    ffkb[0][0] = (mfk[0][0]+ufk[0][0]);
    ffkb[0][1] = (mfk[0][1]+ufk[0][1]);
    ffkb[0][2] = (mfk[0][2]+ufk[0][2]);
    ffkb[1][0] = (mfk[1][0]+ufk[1][0]);
    ffkb[1][1] = (mfk[1][1]+ufk[1][1]);
    ffkb[1][2] = (mfk[1][2]+ufk[1][2]);
    ffkb[2][0] = (mfk[2][0]+ufk[2][0]);
    ffkb[2][1] = (mfk[2][1]+ufk[2][1]);
    ffkb[2][2] = (mfk[2][2]+ufk[2][2]);
    ffkb[3][0] = (mfk[3][0]+ufk[3][0]);
    ffkb[3][1] = (mfk[3][1]+ufk[3][1]);
    ffkb[3][2] = (mfk[3][2]+ufk[3][2]);
    ffkb[4][0] = (mfk[4][0]+ufk[4][0]);
    ffkb[4][1] = (mfk[4][1]+ufk[4][1]);
    ffkb[4][2] = (mfk[4][2]+ufk[4][2]);
    ffkb[5][0] = (mfk[5][0]+ufk[5][0]);
    ffkb[5][1] = (mfk[5][1]+ufk[5][1]);
    ffkb[5][2] = (mfk[5][2]+ufk[5][2]);
    ffkb[6][0] = (mfk[6][0]+ufk[6][0]);
    ffkb[6][1] = (mfk[6][1]+ufk[6][1]);
    ffkb[6][2] = (mfk[6][2]+ufk[6][2]);
    ffkb[7][0] = (mfk[7][0]+ufk[7][0]);
    ffkb[7][1] = (mfk[7][1]+ufk[7][1]);
    ffkb[7][2] = (mfk[7][2]+ufk[7][2]);
    ffkb[8][0] = (mfk[8][0]+ufk[8][0]);
    ffkb[8][1] = (mfk[8][1]+ufk[8][1]);
    ffkb[8][2] = (mfk[8][2]+ufk[8][2]);
    ffkb[9][0] = (mfk[9][0]+ufk[9][0]);
    ffkb[9][1] = (mfk[9][1]+ufk[9][1]);
    ffkb[9][2] = (mfk[9][2]+ufk[9][2]);
    ffkb[10][0] = (mfk[10][0]+ufk[10][0]);
    ffkb[10][1] = (mfk[10][1]+ufk[10][1]);
    ffkb[10][2] = (mfk[10][2]+ufk[10][2]);
    ffkb[11][0] = (mfk[11][0]+ufk[11][0]);
    ffkb[11][1] = (mfk[11][1]+ufk[11][1]);
    ffkb[11][2] = (mfk[11][2]+ufk[11][2]);
    ttkb[0][0] = (mtk[0][0]+utk[0][0]);
    ttkb[0][1] = (mtk[0][1]+utk[0][1]);
    ttkb[0][2] = (mtk[0][2]+utk[0][2]);
    ttkb[1][0] = (mtk[1][0]+utk[1][0]);
    ttkb[1][1] = (mtk[1][1]+utk[1][1]);
    ttkb[1][2] = (mtk[1][2]+utk[1][2]);
    ttkb[2][0] = (mtk[2][0]+utk[2][0]);
    ttkb[2][1] = (mtk[2][1]+utk[2][1]);
    ttkb[2][2] = (mtk[2][2]+utk[2][2]);
    ttkb[3][0] = (mtk[3][0]+utk[3][0]);
    ttkb[3][1] = (mtk[3][1]+utk[3][1]);
    ttkb[3][2] = (mtk[3][2]+utk[3][2]);
    ttkb[4][0] = (mtk[4][0]+utk[4][0]);
    ttkb[4][1] = (mtk[4][1]+utk[4][1]);
    ttkb[4][2] = (mtk[4][2]+utk[4][2]);
    ttkb[5][0] = (mtk[5][0]+utk[5][0]);
    ttkb[5][1] = (mtk[5][1]+utk[5][1]);
    ttkb[5][2] = (mtk[5][2]+utk[5][2]);
    ttkb[6][0] = (mtk[6][0]+utk[6][0]);
    ttkb[6][1] = (mtk[6][1]+utk[6][1]);
    ttkb[6][2] = (mtk[6][2]+utk[6][2]);
    ttkb[7][0] = (mtk[7][0]+utk[7][0]);
    ttkb[7][1] = (mtk[7][1]+utk[7][1]);
    ttkb[7][2] = (mtk[7][2]+utk[7][2]);
    ttkb[8][0] = (mtk[8][0]+utk[8][0]);
    ttkb[8][1] = (mtk[8][1]+utk[8][1]);
    ttkb[8][2] = (mtk[8][2]+utk[8][2]);
    ttkb[9][0] = (mtk[9][0]+utk[9][0]);
    ttkb[9][1] = (mtk[9][1]+utk[9][1]);
    ttkb[9][2] = (mtk[9][2]+utk[9][2]);
    ttkb[10][0] = (mtk[10][0]+utk[10][0]);
    ttkb[10][1] = (mtk[10][1]+utk[10][1]);
    ttkb[10][2] = (mtk[10][2]+utk[10][2]);
    ttkb[11][0] = (mtk[11][0]+utk[11][0]);
    ttkb[11][1] = (mtk[11][1]+utk[11][1]);
    ttkb[11][2] = (mtk[11][2]+utk[11][2]);
    fc[26][0] = ((mk[11]*(AnkAtk[26][0]-gk[26][0]))-ffkb[11][0]);
    fc[26][1] = ((mk[11]*(AnkAtk[26][1]-gk[26][1]))-ffkb[11][1]);
    fc[26][2] = ((mk[11]*(AnkAtk[26][2]-gk[26][2]))-ffkb[11][2]);
    tc[26][0] = ((WkIkWk[26][0]+((ik[11][0][2]*onk[26][2])+((ik[11][0][0]*
      onk[26][0])+(ik[11][0][1]*onk[26][1]))))-(ttkb[11][0]+((fc[26][2]*
      rk[11][1])-(fc[26][1]*rk[11][2]))));
    tc[26][1] = ((WkIkWk[26][1]+((ik[11][1][2]*onk[26][2])+((ik[11][1][0]*
      onk[26][0])+(ik[11][1][1]*onk[26][1]))))-(ttkb[11][1]+((fc[26][0]*
      rk[11][2])-(fc[26][2]*rk[11][0]))));
    tc[26][2] = ((WkIkWk[26][2]+((ik[11][2][2]*onk[26][2])+((ik[11][2][0]*
      onk[26][0])+(ik[11][2][1]*onk[26][1]))))-(ttkb[11][2]+((fc[26][1]*
      rk[11][0])-(fc[26][0]*rk[11][1]))));
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
    ffk[5][0] = (ffkb[0][0]-fccikt[24][0]);
    ffk[5][1] = (ffkb[0][1]-fccikt[24][1]);
    ffk[5][2] = (ffkb[0][2]-fccikt[24][2]);
    ttk[5][0] = (ttkb[0][0]-(((Cik[24][0][2]*tc[24][2])+((Cik[24][0][0]*
      tc[24][0])+(Cik[24][0][1]*tc[24][1])))+((fccikt[24][2]*ri[11][1])-(
      fccikt[24][1]*ri[11][2]))));
    ttk[5][1] = (ttkb[0][1]-(((Cik[24][1][2]*tc[24][2])+((Cik[24][1][0]*
      tc[24][0])+(Cik[24][1][1]*tc[24][1])))+((fccikt[24][0]*ri[11][2])-(
      fccikt[24][2]*ri[11][0]))));
    ttk[5][2] = (ttkb[0][2]-(((Cik[24][2][2]*tc[24][2])+((Cik[24][2][0]*
      tc[24][0])+(Cik[24][2][1]*tc[24][1])))+((fccikt[24][1]*ri[11][0])-(
      fccikt[24][0]*ri[11][1]))));
    fc[23][0] = ((mk[10]*(AnkAtk[23][0]-gk[23][0]))-ffkb[10][0]);
    fc[23][1] = ((mk[10]*(AnkAtk[23][1]-gk[23][1]))-ffkb[10][1]);
    fc[23][2] = ((mk[10]*(AnkAtk[23][2]-gk[23][2]))-ffkb[10][2]);
    tc[23][0] = ((WkIkWk[23][0]+((ik[10][0][2]*onk[23][2])+((ik[10][0][0]*
      onk[23][0])+(ik[10][0][1]*onk[23][1]))))-(ttkb[10][0]+((fc[23][2]*
      rk[10][1])-(fc[23][1]*rk[10][2]))));
    tc[23][1] = ((WkIkWk[23][1]+((ik[10][1][2]*onk[23][2])+((ik[10][1][0]*
      onk[23][0])+(ik[10][1][1]*onk[23][1]))))-(ttkb[10][1]+((fc[23][0]*
      rk[10][2])-(fc[23][2]*rk[10][0]))));
    tc[23][2] = ((WkIkWk[23][2]+((ik[10][2][2]*onk[23][2])+((ik[10][2][0]*
      onk[23][0])+(ik[10][2][1]*onk[23][1]))))-(ttkb[10][2]+((fc[23][1]*
      rk[10][0])-(fc[23][0]*rk[10][1]))));
    fccikt[23][0] = ((Cik[23][0][2]*fc[23][2])+((Cik[23][0][0]*fc[23][0])+(
      Cik[23][0][1]*fc[23][1])));
    fccikt[23][1] = ((Cik[23][1][2]*fc[23][2])+((Cik[23][1][0]*fc[23][0])+(
      Cik[23][1][1]*fc[23][1])));
    fccikt[23][2] = ((Cik[23][2][2]*fc[23][2])+((Cik[23][2][0]*fc[23][0])+(
      Cik[23][2][1]*fc[23][1])));
    ffk[22][0] = (ffkb[9][0]-fccikt[23][0]);
    ffk[22][1] = (ffkb[9][1]-fccikt[23][1]);
    ffk[22][2] = (ffkb[9][2]-fccikt[23][2]);
    ttk[22][0] = (ttkb[9][0]-(((Cik[23][0][2]*tc[23][2])+((Cik[23][0][0]*
      tc[23][0])+(Cik[23][0][1]*tc[23][1])))+((fccikt[23][2]*ri[10][1])-(
      fccikt[23][1]*ri[10][2]))));
    ttk[22][1] = (ttkb[9][1]-(((Cik[23][1][2]*tc[23][2])+((Cik[23][1][0]*
      tc[23][0])+(Cik[23][1][1]*tc[23][1])))+((fccikt[23][0]*ri[10][2])-(
      fccikt[23][2]*ri[10][0]))));
    ttk[22][2] = (ttkb[9][2]-(((Cik[23][2][2]*tc[23][2])+((Cik[23][2][0]*
      tc[23][0])+(Cik[23][2][1]*tc[23][1])))+((fccikt[23][1]*ri[10][0])-(
      fccikt[23][0]*ri[10][1]))));
    fc[22][0] = ((mk[9]*(AnkAtk[22][0]-gk[22][0]))-ffk[22][0]);
    fc[22][1] = ((mk[9]*(AnkAtk[22][1]-gk[22][1]))-ffk[22][1]);
    fc[22][2] = ((mk[9]*(AnkAtk[22][2]-gk[22][2]))-ffk[22][2]);
    tc[22][0] = ((WkIkWk[22][0]+((ik[9][0][2]*onk[22][2])+((ik[9][0][0]*
      onk[22][0])+(ik[9][0][1]*onk[22][1]))))-(ttk[22][0]+((fc[22][2]*rk[9][1])-
      (fc[22][1]*rk[9][2]))));
    tc[22][1] = ((WkIkWk[22][1]+((ik[9][1][2]*onk[22][2])+((ik[9][1][0]*
      onk[22][0])+(ik[9][1][1]*onk[22][1]))))-(ttk[22][1]+((fc[22][0]*rk[9][2])-
      (fc[22][2]*rk[9][0]))));
    tc[22][2] = ((WkIkWk[22][2]+((ik[9][2][2]*onk[22][2])+((ik[9][2][0]*
      onk[22][0])+(ik[9][2][1]*onk[22][1]))))-(ttk[22][2]+((fc[22][1]*rk[9][0])-
      (fc[22][0]*rk[9][1]))));
    fccikt[22][0] = ((Cik[22][0][2]*fc[22][2])+((Cik[22][0][0]*fc[22][0])+(
      Cik[22][0][1]*fc[22][1])));
    fccikt[22][1] = ((Cik[22][1][2]*fc[22][2])+((Cik[22][1][0]*fc[22][0])+(
      Cik[22][1][1]*fc[22][1])));
    fccikt[22][2] = ((Cik[22][2][2]*fc[22][2])+((Cik[22][2][0]*fc[22][0])+(
      Cik[22][2][1]*fc[22][1])));
    ffk[21][0] = (ffkb[8][0]-fccikt[22][0]);
    ffk[21][1] = (ffkb[8][1]-fccikt[22][1]);
    ffk[21][2] = (ffkb[8][2]-fccikt[22][2]);
    ttk[21][0] = (ttkb[8][0]-(((Cik[22][0][2]*tc[22][2])+((Cik[22][0][0]*
      tc[22][0])+(Cik[22][0][1]*tc[22][1])))+((fccikt[22][2]*ri[9][1])-(
      fccikt[22][1]*ri[9][2]))));
    ttk[21][1] = (ttkb[8][1]-(((Cik[22][1][2]*tc[22][2])+((Cik[22][1][0]*
      tc[22][0])+(Cik[22][1][1]*tc[22][1])))+((fccikt[22][0]*ri[9][2])-(
      fccikt[22][2]*ri[9][0]))));
    ttk[21][2] = (ttkb[8][2]-(((Cik[22][2][2]*tc[22][2])+((Cik[22][2][0]*
      tc[22][0])+(Cik[22][2][1]*tc[22][1])))+((fccikt[22][1]*ri[9][0])-(
      fccikt[22][0]*ri[9][1]))));
    fc[21][0] = ((mk[8]*(AnkAtk[21][0]-gk[21][0]))-ffk[21][0]);
    fc[21][1] = ((mk[8]*(AnkAtk[21][1]-gk[21][1]))-ffk[21][1]);
    fc[21][2] = ((mk[8]*(AnkAtk[21][2]-gk[21][2]))-ffk[21][2]);
    tc[21][0] = ((WkIkWk[21][0]+((ik[8][0][2]*onk[21][2])+((ik[8][0][0]*
      onk[21][0])+(ik[8][0][1]*onk[21][1]))))-(ttk[21][0]+((fc[21][2]*rk[8][1])-
      (fc[21][1]*rk[8][2]))));
    tc[21][1] = ((WkIkWk[21][1]+((ik[8][1][2]*onk[21][2])+((ik[8][1][0]*
      onk[21][0])+(ik[8][1][1]*onk[21][1]))))-(ttk[21][1]+((fc[21][0]*rk[8][2])-
      (fc[21][2]*rk[8][0]))));
    tc[21][2] = ((WkIkWk[21][2]+((ik[8][2][2]*onk[21][2])+((ik[8][2][0]*
      onk[21][0])+(ik[8][2][1]*onk[21][1]))))-(ttk[21][2]+((fc[21][1]*rk[8][0])-
      (fc[21][0]*rk[8][1]))));
    fccikt[21][0] = ((Cik[21][0][2]*fc[21][2])+((Cik[21][0][0]*fc[21][0])+(
      Cik[21][0][1]*fc[21][1])));
    fccikt[21][1] = ((Cik[21][1][2]*fc[21][2])+((Cik[21][1][0]*fc[21][0])+(
      Cik[21][1][1]*fc[21][1])));
    fccikt[21][2] = ((Cik[21][2][2]*fc[21][2])+((Cik[21][2][0]*fc[21][0])+(
      Cik[21][2][1]*fc[21][1])));
    ffk[20][0] = (ffkb[7][0]-fccikt[21][0]);
    ffk[20][1] = (ffkb[7][1]-fccikt[21][1]);
    ffk[20][2] = (ffkb[7][2]-fccikt[21][2]);
    ttk[20][0] = (ttkb[7][0]-(((Cik[21][0][2]*tc[21][2])+((Cik[21][0][0]*
      tc[21][0])+(Cik[21][0][1]*tc[21][1])))+((fccikt[21][2]*ri[8][1])-(
      fccikt[21][1]*ri[8][2]))));
    ttk[20][1] = (ttkb[7][1]-(((Cik[21][1][2]*tc[21][2])+((Cik[21][1][0]*
      tc[21][0])+(Cik[21][1][1]*tc[21][1])))+((fccikt[21][0]*ri[8][2])-(
      fccikt[21][2]*ri[8][0]))));
    ttk[20][2] = (ttkb[7][2]-(((Cik[21][2][2]*tc[21][2])+((Cik[21][2][0]*
      tc[21][0])+(Cik[21][2][1]*tc[21][1])))+((fccikt[21][1]*ri[8][0])-(
      fccikt[21][0]*ri[8][1]))));
    fc[20][0] = ((mk[7]*(AnkAtk[20][0]-gk[20][0]))-ffk[20][0]);
    fc[20][1] = ((mk[7]*(AnkAtk[20][1]-gk[20][1]))-ffk[20][1]);
    fc[20][2] = ((mk[7]*(AnkAtk[20][2]-gk[20][2]))-ffk[20][2]);
    tc[20][0] = ((WkIkWk[20][0]+((ik[7][0][2]*onk[20][2])+((ik[7][0][0]*
      onk[20][0])+(ik[7][0][1]*onk[20][1]))))-(ttk[20][0]+((fc[20][2]*rk[7][1])-
      (fc[20][1]*rk[7][2]))));
    tc[20][1] = ((WkIkWk[20][1]+((ik[7][1][2]*onk[20][2])+((ik[7][1][0]*
      onk[20][0])+(ik[7][1][1]*onk[20][1]))))-(ttk[20][1]+((fc[20][0]*rk[7][2])-
      (fc[20][2]*rk[7][0]))));
    tc[20][2] = ((WkIkWk[20][2]+((ik[7][2][2]*onk[20][2])+((ik[7][2][0]*
      onk[20][0])+(ik[7][2][1]*onk[20][1]))))-(ttk[20][2]+((fc[20][1]*rk[7][0])-
      (fc[20][0]*rk[7][1]))));
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
    fccikt[19][0] = fc[19][0];
    fccikt[19][1] = fc[19][1];
    fccikt[19][2] = fc[19][2];
    ffk[18][0] = -fccikt[19][0];
    ffk[18][1] = -fccikt[19][1];
    ffk[18][2] = -fccikt[19][2];
    ttk[18][0] = -(tc[19][0]+((fccikt[19][2]*rpp[19][1])-(fccikt[19][1]*
      rpp[19][2])));
    ttk[18][1] = -(tc[19][1]+((fccikt[19][0]*rpp[19][2])-(fccikt[19][2]*
      rpp[19][0])));
    ttk[18][2] = -(tc[19][2]+((fccikt[19][1]*rpp[19][0])-(fccikt[19][0]*
      rpp[19][1])));
    fc[18][0] = -ffk[18][0];
    fc[18][1] = -ffk[18][1];
    fc[18][2] = -ffk[18][2];
    tc[18][0] = -ttk[18][0];
    tc[18][1] = -ttk[18][1];
    tc[18][2] = -ttk[18][2];
    fccikt[18][0] = fc[18][0];
    fccikt[18][1] = fc[18][1];
    fccikt[18][2] = fc[18][2];
    ffk[17][0] = (ffkb[6][0]-fccikt[18][0]);
    ffk[17][1] = (ffkb[6][1]-fccikt[18][1]);
    ffk[17][2] = (ffkb[6][2]-fccikt[18][2]);
    ttk[17][0] = (ttkb[6][0]-(tc[18][0]+((fccikt[18][2]*rpri[18][1])-(
      fccikt[18][1]*rpri[18][2]))));
    ttk[17][1] = (ttkb[6][1]-(tc[18][1]+((fccikt[18][0]*rpri[18][2])-(
      fccikt[18][2]*rpri[18][0]))));
    ttk[17][2] = (ttkb[6][2]-(tc[18][2]+((fccikt[18][1]*rpri[18][0])-(
      fccikt[18][0]*rpri[18][1]))));
    fc[17][0] = ((mk[6]*(AnkAtk[17][0]-gk[17][0]))-ffk[17][0]);
    fc[17][1] = ((mk[6]*(AnkAtk[17][1]-gk[17][1]))-ffk[17][1]);
    fc[17][2] = ((mk[6]*(AnkAtk[17][2]-gk[17][2]))-ffk[17][2]);
    tc[17][0] = ((WkIkWk[17][0]+((ik[6][0][2]*onk[17][2])+((ik[6][0][0]*
      onk[17][0])+(ik[6][0][1]*onk[17][1]))))-(ttk[17][0]+((fc[17][2]*rk[6][1])-
      (fc[17][1]*rk[6][2]))));
    tc[17][1] = ((WkIkWk[17][1]+((ik[6][1][2]*onk[17][2])+((ik[6][1][0]*
      onk[17][0])+(ik[6][1][1]*onk[17][1]))))-(ttk[17][1]+((fc[17][0]*rk[6][2])-
      (fc[17][2]*rk[6][0]))));
    tc[17][2] = ((WkIkWk[17][2]+((ik[6][2][2]*onk[17][2])+((ik[6][2][0]*
      onk[17][0])+(ik[6][2][1]*onk[17][1]))))-(ttk[17][2]+((fc[17][1]*rk[6][0])-
      (fc[17][0]*rk[6][1]))));
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
    ffk[5][0] = (ffk[5][0]-fccikt[15][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[15][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[15][2]);
    ttk[5][0] = (ttk[5][0]-(((Cik[15][0][2]*tc[15][2])+((Cik[15][0][0]*tc[15][0]
      )+(Cik[15][0][1]*tc[15][1])))+((fccikt[15][2]*ri[6][1])-(fccikt[15][1]*
      ri[6][2]))));
    ttk[5][1] = (ttk[5][1]-(((Cik[15][1][2]*tc[15][2])+((Cik[15][1][0]*tc[15][0]
      )+(Cik[15][1][1]*tc[15][1])))+((fccikt[15][0]*ri[6][2])-(fccikt[15][2]*
      ri[6][0]))));
    ttk[5][2] = (ttk[5][2]-(((Cik[15][2][2]*tc[15][2])+((Cik[15][2][0]*tc[15][0]
      )+(Cik[15][2][1]*tc[15][1])))+((fccikt[15][1]*ri[6][0])-(fccikt[15][0]*
      ri[6][1]))));
    fc[14][0] = ((mk[5]*(AnkAtk[14][0]-gk[14][0]))-ffkb[5][0]);
    fc[14][1] = ((mk[5]*(AnkAtk[14][1]-gk[14][1]))-ffkb[5][1]);
    fc[14][2] = ((mk[5]*(AnkAtk[14][2]-gk[14][2]))-ffkb[5][2]);
    tc[14][0] = ((WkIkWk[14][0]+((ik[5][0][2]*onk[14][2])+((ik[5][0][0]*
      onk[14][0])+(ik[5][0][1]*onk[14][1]))))-(ttkb[5][0]+((fc[14][2]*rk[5][1])-
      (fc[14][1]*rk[5][2]))));
    tc[14][1] = ((WkIkWk[14][1]+((ik[5][1][2]*onk[14][2])+((ik[5][1][0]*
      onk[14][0])+(ik[5][1][1]*onk[14][1]))))-(ttkb[5][1]+((fc[14][0]*rk[5][2])-
      (fc[14][2]*rk[5][0]))));
    tc[14][2] = ((WkIkWk[14][2]+((ik[5][2][2]*onk[14][2])+((ik[5][2][0]*
      onk[14][0])+(ik[5][2][1]*onk[14][1]))))-(ttkb[5][2]+((fc[14][1]*rk[5][0])-
      (fc[14][0]*rk[5][1]))));
    fccikt[14][0] = ((Cik[14][0][2]*fc[14][2])+((Cik[14][0][0]*fc[14][0])+(
      Cik[14][0][1]*fc[14][1])));
    fccikt[14][1] = ((Cik[14][1][2]*fc[14][2])+((Cik[14][1][0]*fc[14][0])+(
      Cik[14][1][1]*fc[14][1])));
    fccikt[14][2] = ((Cik[14][2][2]*fc[14][2])+((Cik[14][2][0]*fc[14][0])+(
      Cik[14][2][1]*fc[14][1])));
    ffk[13][0] = (ffkb[4][0]-fccikt[14][0]);
    ffk[13][1] = (ffkb[4][1]-fccikt[14][1]);
    ffk[13][2] = (ffkb[4][2]-fccikt[14][2]);
    ttk[13][0] = (ttkb[4][0]-(((Cik[14][0][2]*tc[14][2])+((Cik[14][0][0]*
      tc[14][0])+(Cik[14][0][1]*tc[14][1])))+((fccikt[14][2]*ri[5][1])-(
      fccikt[14][1]*ri[5][2]))));
    ttk[13][1] = (ttkb[4][1]-(((Cik[14][1][2]*tc[14][2])+((Cik[14][1][0]*
      tc[14][0])+(Cik[14][1][1]*tc[14][1])))+((fccikt[14][0]*ri[5][2])-(
      fccikt[14][2]*ri[5][0]))));
    ttk[13][2] = (ttkb[4][2]-(((Cik[14][2][2]*tc[14][2])+((Cik[14][2][0]*
      tc[14][0])+(Cik[14][2][1]*tc[14][1])))+((fccikt[14][1]*ri[5][0])-(
      fccikt[14][0]*ri[5][1]))));
    fc[13][0] = ((mk[4]*(AnkAtk[13][0]-gk[13][0]))-ffk[13][0]);
    fc[13][1] = ((mk[4]*(AnkAtk[13][1]-gk[13][1]))-ffk[13][1]);
    fc[13][2] = ((mk[4]*(AnkAtk[13][2]-gk[13][2]))-ffk[13][2]);
    tc[13][0] = ((WkIkWk[13][0]+((ik[4][0][2]*onk[13][2])+((ik[4][0][0]*
      onk[13][0])+(ik[4][0][1]*onk[13][1]))))-(ttk[13][0]+((fc[13][2]*rk[4][1])-
      (fc[13][1]*rk[4][2]))));
    tc[13][1] = ((WkIkWk[13][1]+((ik[4][1][2]*onk[13][2])+((ik[4][1][0]*
      onk[13][0])+(ik[4][1][1]*onk[13][1]))))-(ttk[13][1]+((fc[13][0]*rk[4][2])-
      (fc[13][2]*rk[4][0]))));
    tc[13][2] = ((WkIkWk[13][2]+((ik[4][2][2]*onk[13][2])+((ik[4][2][0]*
      onk[13][0])+(ik[4][2][1]*onk[13][1]))))-(ttk[13][2]+((fc[13][1]*rk[4][0])-
      (fc[13][0]*rk[4][1]))));
    fccikt[13][0] = ((Cik[13][0][2]*fc[13][2])+((Cik[13][0][0]*fc[13][0])+(
      Cik[13][0][1]*fc[13][1])));
    fccikt[13][1] = ((Cik[13][1][2]*fc[13][2])+((Cik[13][1][0]*fc[13][0])+(
      Cik[13][1][1]*fc[13][1])));
    fccikt[13][2] = ((Cik[13][2][2]*fc[13][2])+((Cik[13][2][0]*fc[13][0])+(
      Cik[13][2][1]*fc[13][1])));
    ffk[12][0] = (ffkb[3][0]-fccikt[13][0]);
    ffk[12][1] = (ffkb[3][1]-fccikt[13][1]);
    ffk[12][2] = (ffkb[3][2]-fccikt[13][2]);
    ttk[12][0] = (ttkb[3][0]-(((Cik[13][0][2]*tc[13][2])+((Cik[13][0][0]*
      tc[13][0])+(Cik[13][0][1]*tc[13][1])))+((fccikt[13][2]*ri[4][1])-(
      fccikt[13][1]*ri[4][2]))));
    ttk[12][1] = (ttkb[3][1]-(((Cik[13][1][2]*tc[13][2])+((Cik[13][1][0]*
      tc[13][0])+(Cik[13][1][1]*tc[13][1])))+((fccikt[13][0]*ri[4][2])-(
      fccikt[13][2]*ri[4][0]))));
    ttk[12][2] = (ttkb[3][2]-(((Cik[13][2][2]*tc[13][2])+((Cik[13][2][0]*
      tc[13][0])+(Cik[13][2][1]*tc[13][1])))+((fccikt[13][1]*ri[4][0])-(
      fccikt[13][0]*ri[4][1]))));
    fc[12][0] = ((mk[3]*(AnkAtk[12][0]-gk[12][0]))-ffk[12][0]);
    fc[12][1] = ((mk[3]*(AnkAtk[12][1]-gk[12][1]))-ffk[12][1]);
    fc[12][2] = ((mk[3]*(AnkAtk[12][2]-gk[12][2]))-ffk[12][2]);
    tc[12][0] = ((WkIkWk[12][0]+((ik[3][0][2]*onk[12][2])+((ik[3][0][0]*
      onk[12][0])+(ik[3][0][1]*onk[12][1]))))-(ttk[12][0]+((fc[12][2]*rk[3][1])-
      (fc[12][1]*rk[3][2]))));
    tc[12][1] = ((WkIkWk[12][1]+((ik[3][1][2]*onk[12][2])+((ik[3][1][0]*
      onk[12][0])+(ik[3][1][1]*onk[12][1]))))-(ttk[12][1]+((fc[12][0]*rk[3][2])-
      (fc[12][2]*rk[3][0]))));
    tc[12][2] = ((WkIkWk[12][2]+((ik[3][2][2]*onk[12][2])+((ik[3][2][0]*
      onk[12][0])+(ik[3][2][1]*onk[12][1]))))-(ttk[12][2]+((fc[12][1]*rk[3][0])-
      (fc[12][0]*rk[3][1]))));
    fccikt[12][0] = ((Cik[12][0][2]*fc[12][2])+((Cik[12][0][0]*fc[12][0])+(
      Cik[12][0][1]*fc[12][1])));
    fccikt[12][1] = ((Cik[12][1][2]*fc[12][2])+((Cik[12][1][0]*fc[12][0])+(
      Cik[12][1][1]*fc[12][1])));
    fccikt[12][2] = ((Cik[12][2][2]*fc[12][2])+((Cik[12][2][0]*fc[12][0])+(
      Cik[12][2][1]*fc[12][1])));
    ffk[11][0] = (ffkb[2][0]-fccikt[12][0]);
    ffk[11][1] = (ffkb[2][1]-fccikt[12][1]);
    ffk[11][2] = (ffkb[2][2]-fccikt[12][2]);
    ttk[11][0] = (ttkb[2][0]-(((Cik[12][0][2]*tc[12][2])+((Cik[12][0][0]*
      tc[12][0])+(Cik[12][0][1]*tc[12][1])))+((fccikt[12][2]*ri[3][1])-(
      fccikt[12][1]*ri[3][2]))));
    ttk[11][1] = (ttkb[2][1]-(((Cik[12][1][2]*tc[12][2])+((Cik[12][1][0]*
      tc[12][0])+(Cik[12][1][1]*tc[12][1])))+((fccikt[12][0]*ri[3][2])-(
      fccikt[12][2]*ri[3][0]))));
    ttk[11][2] = (ttkb[2][2]-(((Cik[12][2][2]*tc[12][2])+((Cik[12][2][0]*
      tc[12][0])+(Cik[12][2][1]*tc[12][1])))+((fccikt[12][1]*ri[3][0])-(
      fccikt[12][0]*ri[3][1]))));
    fc[11][0] = ((mk[2]*(AnkAtk[11][0]-gk[11][0]))-ffk[11][0]);
    fc[11][1] = ((mk[2]*(AnkAtk[11][1]-gk[11][1]))-ffk[11][1]);
    fc[11][2] = ((mk[2]*(AnkAtk[11][2]-gk[11][2]))-ffk[11][2]);
    tc[11][0] = ((WkIkWk[11][0]+((ik[2][0][2]*onk[11][2])+((ik[2][0][0]*
      onk[11][0])+(ik[2][0][1]*onk[11][1]))))-(ttk[11][0]+((fc[11][2]*rk[2][1])-
      (fc[11][1]*rk[2][2]))));
    tc[11][1] = ((WkIkWk[11][1]+((ik[2][1][2]*onk[11][2])+((ik[2][1][0]*
      onk[11][0])+(ik[2][1][1]*onk[11][1]))))-(ttk[11][1]+((fc[11][0]*rk[2][2])-
      (fc[11][2]*rk[2][0]))));
    tc[11][2] = ((WkIkWk[11][2]+((ik[2][2][2]*onk[11][2])+((ik[2][2][0]*
      onk[11][0])+(ik[2][2][1]*onk[11][1]))))-(ttk[11][2]+((fc[11][1]*rk[2][0])-
      (fc[11][0]*rk[2][1]))));
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
    fccikt[10][0] = fc[10][0];
    fccikt[10][1] = fc[10][1];
    fccikt[10][2] = fc[10][2];
    ffk[9][0] = -fccikt[10][0];
    ffk[9][1] = -fccikt[10][1];
    ffk[9][2] = -fccikt[10][2];
    ttk[9][0] = -(tc[10][0]+((fccikt[10][2]*rpp[10][1])-(fccikt[10][1]*
      rpp[10][2])));
    ttk[9][1] = -(tc[10][1]+((fccikt[10][0]*rpp[10][2])-(fccikt[10][2]*
      rpp[10][0])));
    ttk[9][2] = -(tc[10][2]+((fccikt[10][1]*rpp[10][0])-(fccikt[10][0]*
      rpp[10][1])));
    fc[9][0] = -ffk[9][0];
    fc[9][1] = -ffk[9][1];
    fc[9][2] = -ffk[9][2];
    tc[9][0] = -ttk[9][0];
    tc[9][1] = -ttk[9][1];
    tc[9][2] = -ttk[9][2];
    fccikt[9][0] = fc[9][0];
    fccikt[9][1] = fc[9][1];
    fccikt[9][2] = fc[9][2];
    ffk[8][0] = (ffkb[1][0]-fccikt[9][0]);
    ffk[8][1] = (ffkb[1][1]-fccikt[9][1]);
    ffk[8][2] = (ffkb[1][2]-fccikt[9][2]);
    ttk[8][0] = (ttkb[1][0]-(tc[9][0]+((fccikt[9][2]*rpri[9][1])-(fccikt[9][1]*
      rpri[9][2]))));
    ttk[8][1] = (ttkb[1][1]-(tc[9][1]+((fccikt[9][0]*rpri[9][2])-(fccikt[9][2]*
      rpri[9][0]))));
    ttk[8][2] = (ttkb[1][2]-(tc[9][2]+((fccikt[9][1]*rpri[9][0])-(fccikt[9][0]*
      rpri[9][1]))));
    fc[8][0] = ((mk[1]*(AnkAtk[8][0]-gk[8][0]))-ffk[8][0]);
    fc[8][1] = ((mk[1]*(AnkAtk[8][1]-gk[8][1]))-ffk[8][1]);
    fc[8][2] = ((mk[1]*(AnkAtk[8][2]-gk[8][2]))-ffk[8][2]);
    tc[8][0] = ((WkIkWk[8][0]+((ik[1][0][2]*onk[8][2])+((ik[1][0][0]*onk[8][0])+
      (ik[1][0][1]*onk[8][1]))))-(ttk[8][0]+((fc[8][2]*rk[1][1])-(fc[8][1]*
      rk[1][2]))));
    tc[8][1] = ((WkIkWk[8][1]+((ik[1][1][2]*onk[8][2])+((ik[1][1][0]*onk[8][0])+
      (ik[1][1][1]*onk[8][1]))))-(ttk[8][1]+((fc[8][0]*rk[1][2])-(fc[8][2]*
      rk[1][0]))));
    tc[8][2] = ((WkIkWk[8][2]+((ik[1][2][2]*onk[8][2])+((ik[1][2][0]*onk[8][0])+
      (ik[1][2][1]*onk[8][1]))))-(ttk[8][2]+((fc[8][1]*rk[1][0])-(fc[8][0]*
      rk[1][1]))));
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
    ttk[5][0] = (ttk[5][0]-(((Cik[6][0][2]*tc[6][2])+((Cik[6][0][0]*tc[6][0])+(
      Cik[6][0][1]*tc[6][1])))+((fccikt[6][2]*ri[1][1])-(fccikt[6][1]*ri[1][2]))
      ));
    ttk[5][1] = (ttk[5][1]-(((Cik[6][1][2]*tc[6][2])+((Cik[6][1][0]*tc[6][0])+(
      Cik[6][1][1]*tc[6][1])))+((fccikt[6][0]*ri[1][2])-(fccikt[6][2]*ri[1][0]))
      ));
    ttk[5][2] = (ttk[5][2]-(((Cik[6][2][2]*tc[6][2])+((Cik[6][2][0]*tc[6][0])+(
      Cik[6][2][1]*tc[6][1])))+((fccikt[6][1]*ri[1][0])-(fccikt[6][0]*ri[1][1]))
      ));
    fc[5][0] = ((mk[0]*(AnkAtk[5][0]-gk[5][0]))-ffk[5][0]);
    fc[5][1] = ((mk[0]*(AnkAtk[5][1]-gk[5][1]))-ffk[5][1]);
    fc[5][2] = ((mk[0]*(AnkAtk[5][2]-gk[5][2]))-ffk[5][2]);
    tc[5][0] = ((WkIkWk[5][0]+((ik[0][0][2]*onk[5][2])+((ik[0][0][0]*onk[5][0])+
      (ik[0][0][1]*onk[5][1]))))-(ttk[5][0]+((fc[5][2]*rk[0][1])-(fc[5][1]*
      rk[0][2]))));
    tc[5][1] = ((WkIkWk[5][1]+((ik[0][1][2]*onk[5][2])+((ik[0][1][0]*onk[5][0])+
      (ik[0][1][1]*onk[5][1]))))-(ttk[5][1]+((fc[5][0]*rk[0][2])-(fc[5][2]*
      rk[0][0]))));
    tc[5][2] = ((WkIkWk[5][2]+((ik[0][2][2]*onk[5][2])+((ik[0][2][0]*onk[5][0])+
      (ik[0][2][1]*onk[5][1]))))-(ttk[5][2]+((fc[5][1]*rk[0][0])-(fc[5][0]*
      rk[0][1]))));
    fccikt[5][0] = ((Cik[5][0][2]*fc[5][2])+((Cik[5][0][0]*fc[5][0])+(
      Cik[5][0][1]*fc[5][1])));
    fccikt[5][1] = ((Cik[5][1][2]*fc[5][2])+((Cik[5][1][0]*fc[5][0])+(
      Cik[5][1][1]*fc[5][1])));
    fccikt[5][2] = ((Cik[5][2][2]*fc[5][2])+((Cik[5][2][0]*fc[5][0])+(
      Cik[5][2][1]*fc[5][1])));
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -((Cik[5][0][2]*tc[5][2])+((Cik[5][0][0]*tc[5][0])+(Cik[5][0][1]
      *tc[5][1])));
    ttk[4][1] = -((Cik[5][1][2]*tc[5][2])+((Cik[5][1][0]*tc[5][0])+(Cik[5][1][1]
      *tc[5][1])));
    ttk[4][2] = -((Cik[5][2][2]*tc[5][2])+((Cik[5][2][0]*tc[5][0])+(Cik[5][2][1]
      *tc[5][1])));
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = ((Cik[4][0][2]*fc[4][2])+((Cik[4][0][0]*fc[4][0])+(
      Cik[4][0][1]*fc[4][1])));
    fccikt[4][1] = ((Cik[4][1][2]*fc[4][2])+((Cik[4][1][0]*fc[4][0])+(
      Cik[4][1][1]*fc[4][1])));
    fccikt[4][2] = ((Cik[4][2][2]*fc[4][2])+((Cik[4][2][0]*fc[4][0])+(
      Cik[4][2][1]*fc[4][1])));
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -((Cik[4][0][2]*tc[4][2])+((Cik[4][0][0]*tc[4][0])+(Cik[4][0][1]
      *tc[4][1])));
    ttk[3][1] = -((Cik[4][1][2]*tc[4][2])+((Cik[4][1][0]*tc[4][0])+(Cik[4][1][1]
      *tc[4][1])));
    ttk[3][2] = -((Cik[4][2][2]*tc[4][2])+((Cik[4][2][0]*tc[4][0])+(Cik[4][2][1]
      *tc[4][1])));
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
    force[3][0] = fc[12][0];
    torque[3][0] = tc[12][0];
    force[3][1] = fc[12][1];
    torque[3][1] = tc[12][1];
    force[3][2] = fc[12][2];
    torque[3][2] = tc[12][2];
    force[4][0] = fc[13][0];
    torque[4][0] = tc[13][0];
    force[4][1] = fc[13][1];
    torque[4][1] = tc[13][1];
    force[4][2] = fc[13][2];
    torque[4][2] = tc[13][2];
    force[5][0] = fc[14][0];
    torque[5][0] = tc[14][0];
    force[5][1] = fc[14][1];
    torque[5][1] = tc[14][1];
    force[5][2] = fc[14][2];
    torque[5][2] = tc[14][2];
    force[6][0] = fc[17][0];
    torque[6][0] = tc[17][0];
    force[6][1] = fc[17][1];
    torque[6][1] = tc[17][1];
    force[6][2] = fc[17][2];
    torque[6][2] = tc[17][2];
    force[7][0] = fc[20][0];
    torque[7][0] = tc[20][0];
    force[7][1] = fc[20][1];
    torque[7][1] = tc[20][1];
    force[7][2] = fc[20][2];
    torque[7][2] = tc[20][2];
    force[8][0] = fc[21][0];
    torque[8][0] = tc[21][0];
    force[8][1] = fc[21][1];
    torque[8][1] = tc[21][1];
    force[8][2] = fc[21][2];
    torque[8][2] = tc[21][2];
    force[9][0] = fc[22][0];
    torque[9][0] = tc[22][0];
    force[9][1] = fc[22][1];
    torque[9][1] = tc[22][1];
    force[9][2] = fc[22][2];
    torque[9][2] = tc[22][2];
    force[10][0] = fc[23][0];
    torque[10][0] = tc[23][0];
    force[10][1] = fc[23][1];
    torque[10][1] = tc[23][1];
    force[10][2] = fc[23][2];
    torque[10][2] = tc[23][2];
    force[11][0] = fc[26][0];
    torque[11][0] = tc[26][0];
    force[11][1] = fc[26][1];
    torque[11][1] = tc[26][1];
    force[11][2] = fc[26][2];
    torque[11][2] = tc[26][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.19 seconds CPU time,
 24576 additional bytes of memory.
 Equations contain  936 adds/subtracts/negates
                    666 multiplies
                      0 divides
                    540 assignments
*/
}

sdmom(lm,am,ke)
    double lm[3],am[3],*ke;
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 31-Jul-2007 11:59:43 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[12][3],hnk[12][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lk[0][0] = (mk[0]*vnk[5][0]);
    lk[0][1] = (mk[0]*vnk[5][1]);
    lk[0][2] = (mk[0]*vnk[5][2]);
    lk[1][0] = (mk[1]*vnk[8][0]);
    lk[1][1] = (mk[1]*vnk[8][1]);
    lk[1][2] = (mk[1]*vnk[8][2]);
    lk[2][0] = (mk[2]*vnk[11][0]);
    lk[2][1] = (mk[2]*vnk[11][1]);
    lk[2][2] = (mk[2]*vnk[11][2]);
    lk[3][0] = (mk[3]*vnk[12][0]);
    lk[3][1] = (mk[3]*vnk[12][1]);
    lk[3][2] = (mk[3]*vnk[12][2]);
    lk[4][0] = (mk[4]*vnk[13][0]);
    lk[4][1] = (mk[4]*vnk[13][1]);
    lk[4][2] = (mk[4]*vnk[13][2]);
    lk[5][0] = (mk[5]*vnk[14][0]);
    lk[5][1] = (mk[5]*vnk[14][1]);
    lk[5][2] = (mk[5]*vnk[14][2]);
    lk[6][0] = (mk[6]*vnk[17][0]);
    lk[6][1] = (mk[6]*vnk[17][1]);
    lk[6][2] = (mk[6]*vnk[17][2]);
    lk[7][0] = (mk[7]*vnk[20][0]);
    lk[7][1] = (mk[7]*vnk[20][1]);
    lk[7][2] = (mk[7]*vnk[20][2]);
    lk[8][0] = (mk[8]*vnk[21][0]);
    lk[8][1] = (mk[8]*vnk[21][1]);
    lk[8][2] = (mk[8]*vnk[21][2]);
    lk[9][0] = (mk[9]*vnk[22][0]);
    lk[9][1] = (mk[9]*vnk[22][1]);
    lk[9][2] = (mk[9]*vnk[22][2]);
    lk[10][0] = (mk[10]*vnk[23][0]);
    lk[10][1] = (mk[10]*vnk[23][1]);
    lk[10][2] = (mk[10]*vnk[23][2]);
    lk[11][0] = (mk[11]*vnk[26][0]);
    lk[11][1] = (mk[11]*vnk[26][1]);
    lk[11][2] = (mk[11]*vnk[26][2]);
    hnk[0][0] = ((ik[0][0][2]*wk[5][2])+((ik[0][0][0]*wk[5][0])+(ik[0][0][1]*
      wk[5][1])));
    hnk[0][1] = ((ik[0][1][2]*wk[5][2])+((ik[0][1][0]*wk[5][0])+(ik[0][1][1]*
      wk[5][1])));
    hnk[0][2] = ((ik[0][2][2]*wk[5][2])+((ik[0][2][0]*wk[5][0])+(ik[0][2][1]*
      wk[5][1])));
    hnk[1][0] = ((ik[1][0][2]*wk[8][2])+((ik[1][0][0]*wk[8][0])+(ik[1][0][1]*
      wk[8][1])));
    hnk[1][1] = ((ik[1][1][2]*wk[8][2])+((ik[1][1][0]*wk[8][0])+(ik[1][1][1]*
      wk[8][1])));
    hnk[1][2] = ((ik[1][2][2]*wk[8][2])+((ik[1][2][0]*wk[8][0])+(ik[1][2][1]*
      wk[8][1])));
    hnk[2][0] = ((ik[2][0][2]*wk[11][2])+((ik[2][0][0]*wk[11][0])+(ik[2][0][1]*
      wk[11][1])));
    hnk[2][1] = ((ik[2][1][2]*wk[11][2])+((ik[2][1][0]*wk[11][0])+(ik[2][1][1]*
      wk[11][1])));
    hnk[2][2] = ((ik[2][2][2]*wk[11][2])+((ik[2][2][0]*wk[11][0])+(ik[2][2][1]*
      wk[11][1])));
    hnk[3][0] = ((ik[3][0][2]*wk[12][2])+((ik[3][0][0]*wk[12][0])+(ik[3][0][1]*
      wk[12][1])));
    hnk[3][1] = ((ik[3][1][2]*wk[12][2])+((ik[3][1][0]*wk[12][0])+(ik[3][1][1]*
      wk[12][1])));
    hnk[3][2] = ((ik[3][2][2]*wk[12][2])+((ik[3][2][0]*wk[12][0])+(ik[3][2][1]*
      wk[12][1])));
    hnk[4][0] = ((ik[4][0][2]*wk[13][2])+((ik[4][0][0]*wk[13][0])+(ik[4][0][1]*
      wk[13][1])));
    hnk[4][1] = ((ik[4][1][2]*wk[13][2])+((ik[4][1][0]*wk[13][0])+(ik[4][1][1]*
      wk[13][1])));
    hnk[4][2] = ((ik[4][2][2]*wk[13][2])+((ik[4][2][0]*wk[13][0])+(ik[4][2][1]*
      wk[13][1])));
    hnk[5][0] = ((ik[5][0][2]*wk[14][2])+((ik[5][0][0]*wk[14][0])+(ik[5][0][1]*
      wk[14][1])));
    hnk[5][1] = ((ik[5][1][2]*wk[14][2])+((ik[5][1][0]*wk[14][0])+(ik[5][1][1]*
      wk[14][1])));
    hnk[5][2] = ((ik[5][2][2]*wk[14][2])+((ik[5][2][0]*wk[14][0])+(ik[5][2][1]*
      wk[14][1])));
    hnk[6][0] = ((ik[6][0][2]*wk[17][2])+((ik[6][0][0]*wk[17][0])+(ik[6][0][1]*
      wk[17][1])));
    hnk[6][1] = ((ik[6][1][2]*wk[17][2])+((ik[6][1][0]*wk[17][0])+(ik[6][1][1]*
      wk[17][1])));
    hnk[6][2] = ((ik[6][2][2]*wk[17][2])+((ik[6][2][0]*wk[17][0])+(ik[6][2][1]*
      wk[17][1])));
    hnk[7][0] = ((ik[7][0][2]*wk[20][2])+((ik[7][0][0]*wk[20][0])+(ik[7][0][1]*
      wk[20][1])));
    hnk[7][1] = ((ik[7][1][2]*wk[20][2])+((ik[7][1][0]*wk[20][0])+(ik[7][1][1]*
      wk[20][1])));
    hnk[7][2] = ((ik[7][2][2]*wk[20][2])+((ik[7][2][0]*wk[20][0])+(ik[7][2][1]*
      wk[20][1])));
    hnk[8][0] = ((ik[8][0][2]*wk[21][2])+((ik[8][0][0]*wk[21][0])+(ik[8][0][1]*
      wk[21][1])));
    hnk[8][1] = ((ik[8][1][2]*wk[21][2])+((ik[8][1][0]*wk[21][0])+(ik[8][1][1]*
      wk[21][1])));
    hnk[8][2] = ((ik[8][2][2]*wk[21][2])+((ik[8][2][0]*wk[21][0])+(ik[8][2][1]*
      wk[21][1])));
    hnk[9][0] = ((ik[9][0][2]*wk[22][2])+((ik[9][0][0]*wk[22][0])+(ik[9][0][1]*
      wk[22][1])));
    hnk[9][1] = ((ik[9][1][2]*wk[22][2])+((ik[9][1][0]*wk[22][0])+(ik[9][1][1]*
      wk[22][1])));
    hnk[9][2] = ((ik[9][2][2]*wk[22][2])+((ik[9][2][0]*wk[22][0])+(ik[9][2][1]*
      wk[22][1])));
    hnk[10][0] = ((ik[10][0][2]*wk[23][2])+((ik[10][0][0]*wk[23][0])+(
      ik[10][0][1]*wk[23][1])));
    hnk[10][1] = ((ik[10][1][2]*wk[23][2])+((ik[10][1][0]*wk[23][0])+(
      ik[10][1][1]*wk[23][1])));
    hnk[10][2] = ((ik[10][2][2]*wk[23][2])+((ik[10][2][0]*wk[23][0])+(
      ik[10][2][1]*wk[23][1])));
    hnk[11][0] = ((ik[11][0][2]*wk[26][2])+((ik[11][0][0]*wk[26][0])+(
      ik[11][0][1]*wk[26][1])));
    hnk[11][1] = ((ik[11][1][2]*wk[26][2])+((ik[11][1][0]*wk[26][0])+(
      ik[11][1][1]*wk[26][1])));
    hnk[11][2] = ((ik[11][2][2]*wk[26][2])+((ik[11][2][0]*wk[26][0])+(
      ik[11][2][1]*wk[26][1])));
    lm[0] = (lk[11][0]+(lk[10][0]+(lk[9][0]+(lk[8][0]+(lk[7][0]+(lk[6][0]+(
      lk[5][0]+(lk[4][0]+(lk[3][0]+(lk[2][0]+(lk[0][0]+lk[1][0])))))))))));
    lm[1] = (lk[11][1]+(lk[10][1]+(lk[9][1]+(lk[8][1]+(lk[7][1]+(lk[6][1]+(
      lk[5][1]+(lk[4][1]+(lk[3][1]+(lk[2][1]+(lk[0][1]+lk[1][1])))))))))));
    lm[2] = (lk[11][2]+(lk[10][2]+(lk[9][2]+(lk[8][2]+(lk[7][2]+(lk[6][2]+(
      lk[5][2]+(lk[4][2]+(lk[3][2]+(lk[2][2]+(lk[0][2]+lk[1][2])))))))))));
    temp[0] = ((((cnk[11][0][2]*hnk[2][2])+((cnk[11][0][0]*hnk[2][0])+(
      cnk[11][0][1]*hnk[2][1])))+((lk[2][2]*rnk[11][1])-(lk[2][1]*rnk[11][2])))+
      ((((cnk[5][0][2]*hnk[0][2])+((cnk[5][0][0]*hnk[0][0])+(cnk[5][0][1]*
      hnk[0][1])))+((lk[0][2]*rnk[5][1])-(lk[0][1]*rnk[5][2])))+(((cnk[8][0][2]*
      hnk[1][2])+((cnk[8][0][0]*hnk[1][0])+(cnk[8][0][1]*hnk[1][1])))+((lk[1][2]
      *rnk[8][1])-(lk[1][1]*rnk[8][2])))));
    temp[1] = ((((cnk[13][0][2]*hnk[4][2])+((cnk[13][0][0]*hnk[4][0])+(
      cnk[13][0][1]*hnk[4][1])))+((lk[4][2]*rnk[13][1])-(lk[4][1]*rnk[13][2])))+
      ((((cnk[12][0][2]*hnk[3][2])+((cnk[12][0][0]*hnk[3][0])+(cnk[12][0][1]*
      hnk[3][1])))+((lk[3][2]*rnk[12][1])-(lk[3][1]*rnk[12][2])))+temp[0]));
    temp[2] = ((((cnk[17][0][2]*hnk[6][2])+((cnk[17][0][0]*hnk[6][0])+(
      cnk[17][0][1]*hnk[6][1])))+((lk[6][2]*rnk[17][1])-(lk[6][1]*rnk[17][2])))+
      ((((cnk[14][0][2]*hnk[5][2])+((cnk[14][0][0]*hnk[5][0])+(cnk[14][0][1]*
      hnk[5][1])))+((lk[5][2]*rnk[14][1])-(lk[5][1]*rnk[14][2])))+temp[1]));
    temp[3] = ((((cnk[21][0][2]*hnk[8][2])+((cnk[21][0][0]*hnk[8][0])+(
      cnk[21][0][1]*hnk[8][1])))+((lk[8][2]*rnk[21][1])-(lk[8][1]*rnk[21][2])))+
      ((((cnk[20][0][2]*hnk[7][2])+((cnk[20][0][0]*hnk[7][0])+(cnk[20][0][1]*
      hnk[7][1])))+((lk[7][2]*rnk[20][1])-(lk[7][1]*rnk[20][2])))+temp[2]));
    temp[4] = ((((cnk[23][0][2]*hnk[10][2])+((cnk[23][0][0]*hnk[10][0])+(
      cnk[23][0][1]*hnk[10][1])))+((lk[10][2]*rnk[23][1])-(lk[10][1]*rnk[23][2])
      ))+((((cnk[22][0][2]*hnk[9][2])+((cnk[22][0][0]*hnk[9][0])+(cnk[22][0][1]*
      hnk[9][1])))+((lk[9][2]*rnk[22][1])-(lk[9][1]*rnk[22][2])))+temp[3]));
    am[0] = (((((cnk[26][0][2]*hnk[11][2])+((cnk[26][0][0]*hnk[11][0])+(
      cnk[26][0][1]*hnk[11][1])))+((lk[11][2]*rnk[26][1])-(lk[11][1]*rnk[26][2])
      ))+temp[4])-((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = ((((cnk[11][1][2]*hnk[2][2])+((cnk[11][1][0]*hnk[2][0])+(
      cnk[11][1][1]*hnk[2][1])))+((lk[2][0]*rnk[11][2])-(lk[2][2]*rnk[11][0])))+
      ((((cnk[5][1][2]*hnk[0][2])+((cnk[5][1][0]*hnk[0][0])+(cnk[5][1][1]*
      hnk[0][1])))+((lk[0][0]*rnk[5][2])-(lk[0][2]*rnk[5][0])))+(((cnk[8][1][2]*
      hnk[1][2])+((cnk[8][1][0]*hnk[1][0])+(cnk[8][1][1]*hnk[1][1])))+((lk[1][0]
      *rnk[8][2])-(lk[1][2]*rnk[8][0])))));
    temp[1] = ((((cnk[13][1][2]*hnk[4][2])+((cnk[13][1][0]*hnk[4][0])+(
      cnk[13][1][1]*hnk[4][1])))+((lk[4][0]*rnk[13][2])-(lk[4][2]*rnk[13][0])))+
      ((((cnk[12][1][2]*hnk[3][2])+((cnk[12][1][0]*hnk[3][0])+(cnk[12][1][1]*
      hnk[3][1])))+((lk[3][0]*rnk[12][2])-(lk[3][2]*rnk[12][0])))+temp[0]));
    temp[2] = ((((cnk[17][1][2]*hnk[6][2])+((cnk[17][1][0]*hnk[6][0])+(
      cnk[17][1][1]*hnk[6][1])))+((lk[6][0]*rnk[17][2])-(lk[6][2]*rnk[17][0])))+
      ((((cnk[14][1][2]*hnk[5][2])+((cnk[14][1][0]*hnk[5][0])+(cnk[14][1][1]*
      hnk[5][1])))+((lk[5][0]*rnk[14][2])-(lk[5][2]*rnk[14][0])))+temp[1]));
    temp[3] = ((((cnk[21][1][2]*hnk[8][2])+((cnk[21][1][0]*hnk[8][0])+(
      cnk[21][1][1]*hnk[8][1])))+((lk[8][0]*rnk[21][2])-(lk[8][2]*rnk[21][0])))+
      ((((cnk[20][1][2]*hnk[7][2])+((cnk[20][1][0]*hnk[7][0])+(cnk[20][1][1]*
      hnk[7][1])))+((lk[7][0]*rnk[20][2])-(lk[7][2]*rnk[20][0])))+temp[2]));
    temp[4] = ((((cnk[23][1][2]*hnk[10][2])+((cnk[23][1][0]*hnk[10][0])+(
      cnk[23][1][1]*hnk[10][1])))+((lk[10][0]*rnk[23][2])-(lk[10][2]*rnk[23][0])
      ))+((((cnk[22][1][2]*hnk[9][2])+((cnk[22][1][0]*hnk[9][0])+(cnk[22][1][1]*
      hnk[9][1])))+((lk[9][0]*rnk[22][2])-(lk[9][2]*rnk[22][0])))+temp[3]));
    am[1] = (((((cnk[26][1][2]*hnk[11][2])+((cnk[26][1][0]*hnk[11][0])+(
      cnk[26][1][1]*hnk[11][1])))+((lk[11][0]*rnk[26][2])-(lk[11][2]*rnk[26][0])
      ))+temp[4])-((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = ((((cnk[11][2][2]*hnk[2][2])+((cnk[11][2][0]*hnk[2][0])+(
      cnk[11][2][1]*hnk[2][1])))+((lk[2][1]*rnk[11][0])-(lk[2][0]*rnk[11][1])))+
      ((((cnk[5][2][2]*hnk[0][2])+((cnk[5][2][0]*hnk[0][0])+(cnk[5][2][1]*
      hnk[0][1])))+((lk[0][1]*rnk[5][0])-(lk[0][0]*rnk[5][1])))+(((cnk[8][2][2]*
      hnk[1][2])+((cnk[8][2][0]*hnk[1][0])+(cnk[8][2][1]*hnk[1][1])))+((lk[1][1]
      *rnk[8][0])-(lk[1][0]*rnk[8][1])))));
    temp[1] = ((((cnk[13][2][2]*hnk[4][2])+((cnk[13][2][0]*hnk[4][0])+(
      cnk[13][2][1]*hnk[4][1])))+((lk[4][1]*rnk[13][0])-(lk[4][0]*rnk[13][1])))+
      ((((cnk[12][2][2]*hnk[3][2])+((cnk[12][2][0]*hnk[3][0])+(cnk[12][2][1]*
      hnk[3][1])))+((lk[3][1]*rnk[12][0])-(lk[3][0]*rnk[12][1])))+temp[0]));
    temp[2] = ((((cnk[17][2][2]*hnk[6][2])+((cnk[17][2][0]*hnk[6][0])+(
      cnk[17][2][1]*hnk[6][1])))+((lk[6][1]*rnk[17][0])-(lk[6][0]*rnk[17][1])))+
      ((((cnk[14][2][2]*hnk[5][2])+((cnk[14][2][0]*hnk[5][0])+(cnk[14][2][1]*
      hnk[5][1])))+((lk[5][1]*rnk[14][0])-(lk[5][0]*rnk[14][1])))+temp[1]));
    temp[3] = ((((cnk[21][2][2]*hnk[8][2])+((cnk[21][2][0]*hnk[8][0])+(
      cnk[21][2][1]*hnk[8][1])))+((lk[8][1]*rnk[21][0])-(lk[8][0]*rnk[21][1])))+
      ((((cnk[20][2][2]*hnk[7][2])+((cnk[20][2][0]*hnk[7][0])+(cnk[20][2][1]*
      hnk[7][1])))+((lk[7][1]*rnk[20][0])-(lk[7][0]*rnk[20][1])))+temp[2]));
    temp[4] = ((((cnk[23][2][2]*hnk[10][2])+((cnk[23][2][0]*hnk[10][0])+(
      cnk[23][2][1]*hnk[10][1])))+((lk[10][1]*rnk[23][0])-(lk[10][0]*rnk[23][1])
      ))+((((cnk[22][2][2]*hnk[9][2])+((cnk[22][2][0]*hnk[9][0])+(cnk[22][2][1]*
      hnk[9][1])))+((lk[9][1]*rnk[22][0])-(lk[9][0]*rnk[22][1])))+temp[3]));
    am[2] = (((((cnk[26][2][2]*hnk[11][2])+((cnk[26][2][0]*hnk[11][0])+(
      cnk[26][2][1]*hnk[11][1])))+((lk[11][1]*rnk[26][0])-(lk[11][0]*rnk[26][1])
      ))+temp[4])-((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = ((((hnk[0][2]*wk[5][2])+((hnk[0][0]*wk[5][0])+(hnk[0][1]*wk[5][1])
      ))+((lk[0][2]*vnk[5][2])+((lk[0][0]*vnk[5][0])+(lk[0][1]*vnk[5][1]))))+(((
      hnk[1][2]*wk[8][2])+((hnk[1][0]*wk[8][0])+(hnk[1][1]*wk[8][1])))+((
      lk[1][2]*vnk[8][2])+((lk[1][0]*vnk[8][0])+(lk[1][1]*vnk[8][1])))));
    temp[1] = ((((hnk[3][2]*wk[12][2])+((hnk[3][0]*wk[12][0])+(hnk[3][1]*
      wk[12][1])))+((lk[3][2]*vnk[12][2])+((lk[3][0]*vnk[12][0])+(lk[3][1]*
      vnk[12][1]))))+((((hnk[2][2]*wk[11][2])+((hnk[2][0]*wk[11][0])+(hnk[2][1]*
      wk[11][1])))+((lk[2][2]*vnk[11][2])+((lk[2][0]*vnk[11][0])+(lk[2][1]*
      vnk[11][1]))))+temp[0]));
    temp[2] = ((((hnk[5][2]*wk[14][2])+((hnk[5][0]*wk[14][0])+(hnk[5][1]*
      wk[14][1])))+((lk[5][2]*vnk[14][2])+((lk[5][0]*vnk[14][0])+(lk[5][1]*
      vnk[14][1]))))+((((hnk[4][2]*wk[13][2])+((hnk[4][0]*wk[13][0])+(hnk[4][1]*
      wk[13][1])))+((lk[4][2]*vnk[13][2])+((lk[4][0]*vnk[13][0])+(lk[4][1]*
      vnk[13][1]))))+temp[1]));
    temp[3] = ((((hnk[7][2]*wk[20][2])+((hnk[7][0]*wk[20][0])+(hnk[7][1]*
      wk[20][1])))+((lk[7][2]*vnk[20][2])+((lk[7][0]*vnk[20][0])+(lk[7][1]*
      vnk[20][1]))))+((((hnk[6][2]*wk[17][2])+((hnk[6][0]*wk[17][0])+(hnk[6][1]*
      wk[17][1])))+((lk[6][2]*vnk[17][2])+((lk[6][0]*vnk[17][0])+(lk[6][1]*
      vnk[17][1]))))+temp[2]));
    temp[4] = ((((hnk[9][2]*wk[22][2])+((hnk[9][0]*wk[22][0])+(hnk[9][1]*
      wk[22][1])))+((lk[9][2]*vnk[22][2])+((lk[9][0]*vnk[22][0])+(lk[9][1]*
      vnk[22][1]))))+((((hnk[8][2]*wk[21][2])+((hnk[8][0]*wk[21][0])+(hnk[8][1]*
      wk[21][1])))+((lk[8][2]*vnk[21][2])+((lk[8][0]*vnk[21][0])+(lk[8][1]*
      vnk[21][1]))))+temp[3]));
    *ke = (.5*((((hnk[11][2]*wk[26][2])+((hnk[11][0]*wk[26][0])+(hnk[11][1]*
      wk[26][1])))+((lk[11][2]*vnk[26][2])+((lk[11][0]*vnk[26][0])+(lk[11][1]*
      vnk[26][1]))))+((((hnk[10][2]*wk[23][2])+((hnk[10][0]*wk[23][0])+(
      hnk[10][1]*wk[23][1])))+((lk[10][2]*vnk[23][2])+((lk[10][0]*vnk[23][0])+(
      lk[10][1]*vnk[23][1]))))+temp[4])));
/*
 Used 0.09 seconds CPU time,
 49152 additional bytes of memory.
 Equations contain  359 adds/subtracts/negates
                    403 multiplies
                      0 divides
                     99 assignments
*/
}

sdsys(mtoto,cm,icm)
    double *mtoto,cm[3],icm[3][3];
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 31-Jul-2007 11:59:43 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[27][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = mtot;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    ikcnkt[5][0][0] = ((cnk[5][0][2]*ik[0][0][2])+((cnk[5][0][0]*ik[0][0][0])+(
      cnk[5][0][1]*ik[0][0][1])));
    ikcnkt[5][0][1] = ((cnk[5][1][2]*ik[0][0][2])+((cnk[5][1][0]*ik[0][0][0])+(
      cnk[5][1][1]*ik[0][0][1])));
    ikcnkt[5][0][2] = ((cnk[5][2][2]*ik[0][0][2])+((cnk[5][2][0]*ik[0][0][0])+(
      cnk[5][2][1]*ik[0][0][1])));
    ikcnkt[5][1][0] = ((cnk[5][0][2]*ik[0][1][2])+((cnk[5][0][0]*ik[0][1][0])+(
      cnk[5][0][1]*ik[0][1][1])));
    ikcnkt[5][1][1] = ((cnk[5][1][2]*ik[0][1][2])+((cnk[5][1][0]*ik[0][1][0])+(
      cnk[5][1][1]*ik[0][1][1])));
    ikcnkt[5][1][2] = ((cnk[5][2][2]*ik[0][1][2])+((cnk[5][2][0]*ik[0][1][0])+(
      cnk[5][2][1]*ik[0][1][1])));
    ikcnkt[5][2][0] = ((cnk[5][0][2]*ik[0][2][2])+((cnk[5][0][0]*ik[0][2][0])+(
      cnk[5][0][1]*ik[0][2][1])));
    ikcnkt[5][2][1] = ((cnk[5][1][2]*ik[0][2][2])+((cnk[5][1][0]*ik[0][2][0])+(
      cnk[5][1][1]*ik[0][2][1])));
    ikcnkt[5][2][2] = ((cnk[5][2][2]*ik[0][2][2])+((cnk[5][2][0]*ik[0][2][0])+(
      cnk[5][2][1]*ik[0][2][1])));
    ikcnkt[8][0][0] = ((cnk[8][0][2]*ik[1][0][2])+((cnk[8][0][0]*ik[1][0][0])+(
      cnk[8][0][1]*ik[1][0][1])));
    ikcnkt[8][0][1] = ((cnk[8][1][2]*ik[1][0][2])+((cnk[8][1][0]*ik[1][0][0])+(
      cnk[8][1][1]*ik[1][0][1])));
    ikcnkt[8][0][2] = ((cnk[8][2][2]*ik[1][0][2])+((cnk[8][2][0]*ik[1][0][0])+(
      cnk[8][2][1]*ik[1][0][1])));
    ikcnkt[8][1][0] = ((cnk[8][0][2]*ik[1][1][2])+((cnk[8][0][0]*ik[1][1][0])+(
      cnk[8][0][1]*ik[1][1][1])));
    ikcnkt[8][1][1] = ((cnk[8][1][2]*ik[1][1][2])+((cnk[8][1][0]*ik[1][1][0])+(
      cnk[8][1][1]*ik[1][1][1])));
    ikcnkt[8][1][2] = ((cnk[8][2][2]*ik[1][1][2])+((cnk[8][2][0]*ik[1][1][0])+(
      cnk[8][2][1]*ik[1][1][1])));
    ikcnkt[8][2][0] = ((cnk[8][0][2]*ik[1][2][2])+((cnk[8][0][0]*ik[1][2][0])+(
      cnk[8][0][1]*ik[1][2][1])));
    ikcnkt[8][2][1] = ((cnk[8][1][2]*ik[1][2][2])+((cnk[8][1][0]*ik[1][2][0])+(
      cnk[8][1][1]*ik[1][2][1])));
    ikcnkt[8][2][2] = ((cnk[8][2][2]*ik[1][2][2])+((cnk[8][2][0]*ik[1][2][0])+(
      cnk[8][2][1]*ik[1][2][1])));
    ikcnkt[11][0][0] = ((cnk[11][0][2]*ik[2][0][2])+((cnk[11][0][0]*ik[2][0][0])
      +(cnk[11][0][1]*ik[2][0][1])));
    ikcnkt[11][0][1] = ((cnk[11][1][2]*ik[2][0][2])+((cnk[11][1][0]*ik[2][0][0])
      +(cnk[11][1][1]*ik[2][0][1])));
    ikcnkt[11][0][2] = ((cnk[11][2][2]*ik[2][0][2])+((cnk[11][2][0]*ik[2][0][0])
      +(cnk[11][2][1]*ik[2][0][1])));
    ikcnkt[11][1][0] = ((cnk[11][0][2]*ik[2][1][2])+((cnk[11][0][0]*ik[2][1][0])
      +(cnk[11][0][1]*ik[2][1][1])));
    ikcnkt[11][1][1] = ((cnk[11][1][2]*ik[2][1][2])+((cnk[11][1][0]*ik[2][1][0])
      +(cnk[11][1][1]*ik[2][1][1])));
    ikcnkt[11][1][2] = ((cnk[11][2][2]*ik[2][1][2])+((cnk[11][2][0]*ik[2][1][0])
      +(cnk[11][2][1]*ik[2][1][1])));
    ikcnkt[11][2][0] = ((cnk[11][0][2]*ik[2][2][2])+((cnk[11][0][0]*ik[2][2][0])
      +(cnk[11][0][1]*ik[2][2][1])));
    ikcnkt[11][2][1] = ((cnk[11][1][2]*ik[2][2][2])+((cnk[11][1][0]*ik[2][2][0])
      +(cnk[11][1][1]*ik[2][2][1])));
    ikcnkt[11][2][2] = ((cnk[11][2][2]*ik[2][2][2])+((cnk[11][2][0]*ik[2][2][0])
      +(cnk[11][2][1]*ik[2][2][1])));
    ikcnkt[12][0][0] = ((cnk[12][0][2]*ik[3][0][2])+((cnk[12][0][0]*ik[3][0][0])
      +(cnk[12][0][1]*ik[3][0][1])));
    ikcnkt[12][0][1] = ((cnk[12][1][2]*ik[3][0][2])+((cnk[12][1][0]*ik[3][0][0])
      +(cnk[12][1][1]*ik[3][0][1])));
    ikcnkt[12][0][2] = ((cnk[12][2][2]*ik[3][0][2])+((cnk[12][2][0]*ik[3][0][0])
      +(cnk[12][2][1]*ik[3][0][1])));
    ikcnkt[12][1][0] = ((cnk[12][0][2]*ik[3][1][2])+((cnk[12][0][0]*ik[3][1][0])
      +(cnk[12][0][1]*ik[3][1][1])));
    ikcnkt[12][1][1] = ((cnk[12][1][2]*ik[3][1][2])+((cnk[12][1][0]*ik[3][1][0])
      +(cnk[12][1][1]*ik[3][1][1])));
    ikcnkt[12][1][2] = ((cnk[12][2][2]*ik[3][1][2])+((cnk[12][2][0]*ik[3][1][0])
      +(cnk[12][2][1]*ik[3][1][1])));
    ikcnkt[12][2][0] = ((cnk[12][0][2]*ik[3][2][2])+((cnk[12][0][0]*ik[3][2][0])
      +(cnk[12][0][1]*ik[3][2][1])));
    ikcnkt[12][2][1] = ((cnk[12][1][2]*ik[3][2][2])+((cnk[12][1][0]*ik[3][2][0])
      +(cnk[12][1][1]*ik[3][2][1])));
    ikcnkt[12][2][2] = ((cnk[12][2][2]*ik[3][2][2])+((cnk[12][2][0]*ik[3][2][0])
      +(cnk[12][2][1]*ik[3][2][1])));
    ikcnkt[13][0][0] = ((cnk[13][0][2]*ik[4][0][2])+((cnk[13][0][0]*ik[4][0][0])
      +(cnk[13][0][1]*ik[4][0][1])));
    ikcnkt[13][0][1] = ((cnk[13][1][2]*ik[4][0][2])+((cnk[13][1][0]*ik[4][0][0])
      +(cnk[13][1][1]*ik[4][0][1])));
    ikcnkt[13][0][2] = ((cnk[13][2][2]*ik[4][0][2])+((cnk[13][2][0]*ik[4][0][0])
      +(cnk[13][2][1]*ik[4][0][1])));
    ikcnkt[13][1][0] = ((cnk[13][0][2]*ik[4][1][2])+((cnk[13][0][0]*ik[4][1][0])
      +(cnk[13][0][1]*ik[4][1][1])));
    ikcnkt[13][1][1] = ((cnk[13][1][2]*ik[4][1][2])+((cnk[13][1][0]*ik[4][1][0])
      +(cnk[13][1][1]*ik[4][1][1])));
    ikcnkt[13][1][2] = ((cnk[13][2][2]*ik[4][1][2])+((cnk[13][2][0]*ik[4][1][0])
      +(cnk[13][2][1]*ik[4][1][1])));
    ikcnkt[13][2][0] = ((cnk[13][0][2]*ik[4][2][2])+((cnk[13][0][0]*ik[4][2][0])
      +(cnk[13][0][1]*ik[4][2][1])));
    ikcnkt[13][2][1] = ((cnk[13][1][2]*ik[4][2][2])+((cnk[13][1][0]*ik[4][2][0])
      +(cnk[13][1][1]*ik[4][2][1])));
    ikcnkt[13][2][2] = ((cnk[13][2][2]*ik[4][2][2])+((cnk[13][2][0]*ik[4][2][0])
      +(cnk[13][2][1]*ik[4][2][1])));
    ikcnkt[14][0][0] = ((cnk[14][0][2]*ik[5][0][2])+((cnk[14][0][0]*ik[5][0][0])
      +(cnk[14][0][1]*ik[5][0][1])));
    ikcnkt[14][0][1] = ((cnk[14][1][2]*ik[5][0][2])+((cnk[14][1][0]*ik[5][0][0])
      +(cnk[14][1][1]*ik[5][0][1])));
    ikcnkt[14][0][2] = ((cnk[14][2][2]*ik[5][0][2])+((cnk[14][2][0]*ik[5][0][0])
      +(cnk[14][2][1]*ik[5][0][1])));
    ikcnkt[14][1][0] = ((cnk[14][0][2]*ik[5][1][2])+((cnk[14][0][0]*ik[5][1][0])
      +(cnk[14][0][1]*ik[5][1][1])));
    ikcnkt[14][1][1] = ((cnk[14][1][2]*ik[5][1][2])+((cnk[14][1][0]*ik[5][1][0])
      +(cnk[14][1][1]*ik[5][1][1])));
    ikcnkt[14][1][2] = ((cnk[14][2][2]*ik[5][1][2])+((cnk[14][2][0]*ik[5][1][0])
      +(cnk[14][2][1]*ik[5][1][1])));
    ikcnkt[14][2][0] = ((cnk[14][0][2]*ik[5][2][2])+((cnk[14][0][0]*ik[5][2][0])
      +(cnk[14][0][1]*ik[5][2][1])));
    ikcnkt[14][2][1] = ((cnk[14][1][2]*ik[5][2][2])+((cnk[14][1][0]*ik[5][2][0])
      +(cnk[14][1][1]*ik[5][2][1])));
    ikcnkt[14][2][2] = ((cnk[14][2][2]*ik[5][2][2])+((cnk[14][2][0]*ik[5][2][0])
      +(cnk[14][2][1]*ik[5][2][1])));
    ikcnkt[17][0][0] = ((cnk[17][0][2]*ik[6][0][2])+((cnk[17][0][0]*ik[6][0][0])
      +(cnk[17][0][1]*ik[6][0][1])));
    ikcnkt[17][0][1] = ((cnk[17][1][2]*ik[6][0][2])+((cnk[17][1][0]*ik[6][0][0])
      +(cnk[17][1][1]*ik[6][0][1])));
    ikcnkt[17][0][2] = ((cnk[17][2][2]*ik[6][0][2])+((cnk[17][2][0]*ik[6][0][0])
      +(cnk[17][2][1]*ik[6][0][1])));
    ikcnkt[17][1][0] = ((cnk[17][0][2]*ik[6][1][2])+((cnk[17][0][0]*ik[6][1][0])
      +(cnk[17][0][1]*ik[6][1][1])));
    ikcnkt[17][1][1] = ((cnk[17][1][2]*ik[6][1][2])+((cnk[17][1][0]*ik[6][1][0])
      +(cnk[17][1][1]*ik[6][1][1])));
    ikcnkt[17][1][2] = ((cnk[17][2][2]*ik[6][1][2])+((cnk[17][2][0]*ik[6][1][0])
      +(cnk[17][2][1]*ik[6][1][1])));
    ikcnkt[17][2][0] = ((cnk[17][0][2]*ik[6][2][2])+((cnk[17][0][0]*ik[6][2][0])
      +(cnk[17][0][1]*ik[6][2][1])));
    ikcnkt[17][2][1] = ((cnk[17][1][2]*ik[6][2][2])+((cnk[17][1][0]*ik[6][2][0])
      +(cnk[17][1][1]*ik[6][2][1])));
    ikcnkt[17][2][2] = ((cnk[17][2][2]*ik[6][2][2])+((cnk[17][2][0]*ik[6][2][0])
      +(cnk[17][2][1]*ik[6][2][1])));
    ikcnkt[20][0][0] = ((cnk[20][0][2]*ik[7][0][2])+((cnk[20][0][0]*ik[7][0][0])
      +(cnk[20][0][1]*ik[7][0][1])));
    ikcnkt[20][0][1] = ((cnk[20][1][2]*ik[7][0][2])+((cnk[20][1][0]*ik[7][0][0])
      +(cnk[20][1][1]*ik[7][0][1])));
    ikcnkt[20][0][2] = ((cnk[20][2][2]*ik[7][0][2])+((cnk[20][2][0]*ik[7][0][0])
      +(cnk[20][2][1]*ik[7][0][1])));
    ikcnkt[20][1][0] = ((cnk[20][0][2]*ik[7][1][2])+((cnk[20][0][0]*ik[7][1][0])
      +(cnk[20][0][1]*ik[7][1][1])));
    ikcnkt[20][1][1] = ((cnk[20][1][2]*ik[7][1][2])+((cnk[20][1][0]*ik[7][1][0])
      +(cnk[20][1][1]*ik[7][1][1])));
    ikcnkt[20][1][2] = ((cnk[20][2][2]*ik[7][1][2])+((cnk[20][2][0]*ik[7][1][0])
      +(cnk[20][2][1]*ik[7][1][1])));
    ikcnkt[20][2][0] = ((cnk[20][0][2]*ik[7][2][2])+((cnk[20][0][0]*ik[7][2][0])
      +(cnk[20][0][1]*ik[7][2][1])));
    ikcnkt[20][2][1] = ((cnk[20][1][2]*ik[7][2][2])+((cnk[20][1][0]*ik[7][2][0])
      +(cnk[20][1][1]*ik[7][2][1])));
    ikcnkt[20][2][2] = ((cnk[20][2][2]*ik[7][2][2])+((cnk[20][2][0]*ik[7][2][0])
      +(cnk[20][2][1]*ik[7][2][1])));
    ikcnkt[21][0][0] = ((cnk[21][0][2]*ik[8][0][2])+((cnk[21][0][0]*ik[8][0][0])
      +(cnk[21][0][1]*ik[8][0][1])));
    ikcnkt[21][0][1] = ((cnk[21][1][2]*ik[8][0][2])+((cnk[21][1][0]*ik[8][0][0])
      +(cnk[21][1][1]*ik[8][0][1])));
    ikcnkt[21][0][2] = ((cnk[21][2][2]*ik[8][0][2])+((cnk[21][2][0]*ik[8][0][0])
      +(cnk[21][2][1]*ik[8][0][1])));
    ikcnkt[21][1][0] = ((cnk[21][0][2]*ik[8][1][2])+((cnk[21][0][0]*ik[8][1][0])
      +(cnk[21][0][1]*ik[8][1][1])));
    ikcnkt[21][1][1] = ((cnk[21][1][2]*ik[8][1][2])+((cnk[21][1][0]*ik[8][1][0])
      +(cnk[21][1][1]*ik[8][1][1])));
    ikcnkt[21][1][2] = ((cnk[21][2][2]*ik[8][1][2])+((cnk[21][2][0]*ik[8][1][0])
      +(cnk[21][2][1]*ik[8][1][1])));
    ikcnkt[21][2][0] = ((cnk[21][0][2]*ik[8][2][2])+((cnk[21][0][0]*ik[8][2][0])
      +(cnk[21][0][1]*ik[8][2][1])));
    ikcnkt[21][2][1] = ((cnk[21][1][2]*ik[8][2][2])+((cnk[21][1][0]*ik[8][2][0])
      +(cnk[21][1][1]*ik[8][2][1])));
    ikcnkt[21][2][2] = ((cnk[21][2][2]*ik[8][2][2])+((cnk[21][2][0]*ik[8][2][0])
      +(cnk[21][2][1]*ik[8][2][1])));
    ikcnkt[22][0][0] = ((cnk[22][0][2]*ik[9][0][2])+((cnk[22][0][0]*ik[9][0][0])
      +(cnk[22][0][1]*ik[9][0][1])));
    ikcnkt[22][0][1] = ((cnk[22][1][2]*ik[9][0][2])+((cnk[22][1][0]*ik[9][0][0])
      +(cnk[22][1][1]*ik[9][0][1])));
    ikcnkt[22][0][2] = ((cnk[22][2][2]*ik[9][0][2])+((cnk[22][2][0]*ik[9][0][0])
      +(cnk[22][2][1]*ik[9][0][1])));
    ikcnkt[22][1][0] = ((cnk[22][0][2]*ik[9][1][2])+((cnk[22][0][0]*ik[9][1][0])
      +(cnk[22][0][1]*ik[9][1][1])));
    ikcnkt[22][1][1] = ((cnk[22][1][2]*ik[9][1][2])+((cnk[22][1][0]*ik[9][1][0])
      +(cnk[22][1][1]*ik[9][1][1])));
    ikcnkt[22][1][2] = ((cnk[22][2][2]*ik[9][1][2])+((cnk[22][2][0]*ik[9][1][0])
      +(cnk[22][2][1]*ik[9][1][1])));
    ikcnkt[22][2][0] = ((cnk[22][0][2]*ik[9][2][2])+((cnk[22][0][0]*ik[9][2][0])
      +(cnk[22][0][1]*ik[9][2][1])));
    ikcnkt[22][2][1] = ((cnk[22][1][2]*ik[9][2][2])+((cnk[22][1][0]*ik[9][2][0])
      +(cnk[22][1][1]*ik[9][2][1])));
    ikcnkt[22][2][2] = ((cnk[22][2][2]*ik[9][2][2])+((cnk[22][2][0]*ik[9][2][0])
      +(cnk[22][2][1]*ik[9][2][1])));
    ikcnkt[23][0][0] = ((cnk[23][0][2]*ik[10][0][2])+((cnk[23][0][0]*
      ik[10][0][0])+(cnk[23][0][1]*ik[10][0][1])));
    ikcnkt[23][0][1] = ((cnk[23][1][2]*ik[10][0][2])+((cnk[23][1][0]*
      ik[10][0][0])+(cnk[23][1][1]*ik[10][0][1])));
    ikcnkt[23][0][2] = ((cnk[23][2][2]*ik[10][0][2])+((cnk[23][2][0]*
      ik[10][0][0])+(cnk[23][2][1]*ik[10][0][1])));
    ikcnkt[23][1][0] = ((cnk[23][0][2]*ik[10][1][2])+((cnk[23][0][0]*
      ik[10][1][0])+(cnk[23][0][1]*ik[10][1][1])));
    ikcnkt[23][1][1] = ((cnk[23][1][2]*ik[10][1][2])+((cnk[23][1][0]*
      ik[10][1][0])+(cnk[23][1][1]*ik[10][1][1])));
    ikcnkt[23][1][2] = ((cnk[23][2][2]*ik[10][1][2])+((cnk[23][2][0]*
      ik[10][1][0])+(cnk[23][2][1]*ik[10][1][1])));
    ikcnkt[23][2][0] = ((cnk[23][0][2]*ik[10][2][2])+((cnk[23][0][0]*
      ik[10][2][0])+(cnk[23][0][1]*ik[10][2][1])));
    ikcnkt[23][2][1] = ((cnk[23][1][2]*ik[10][2][2])+((cnk[23][1][0]*
      ik[10][2][0])+(cnk[23][1][1]*ik[10][2][1])));
    ikcnkt[23][2][2] = ((cnk[23][2][2]*ik[10][2][2])+((cnk[23][2][0]*
      ik[10][2][0])+(cnk[23][2][1]*ik[10][2][1])));
    ikcnkt[26][0][0] = ((cnk[26][0][2]*ik[11][0][2])+((cnk[26][0][0]*
      ik[11][0][0])+(cnk[26][0][1]*ik[11][0][1])));
    ikcnkt[26][0][1] = ((cnk[26][1][2]*ik[11][0][2])+((cnk[26][1][0]*
      ik[11][0][0])+(cnk[26][1][1]*ik[11][0][1])));
    ikcnkt[26][0][2] = ((cnk[26][2][2]*ik[11][0][2])+((cnk[26][2][0]*
      ik[11][0][0])+(cnk[26][2][1]*ik[11][0][1])));
    ikcnkt[26][1][0] = ((cnk[26][0][2]*ik[11][1][2])+((cnk[26][0][0]*
      ik[11][1][0])+(cnk[26][0][1]*ik[11][1][1])));
    ikcnkt[26][1][1] = ((cnk[26][1][2]*ik[11][1][2])+((cnk[26][1][0]*
      ik[11][1][0])+(cnk[26][1][1]*ik[11][1][1])));
    ikcnkt[26][1][2] = ((cnk[26][2][2]*ik[11][1][2])+((cnk[26][2][0]*
      ik[11][1][0])+(cnk[26][2][1]*ik[11][1][1])));
    ikcnkt[26][2][0] = ((cnk[26][0][2]*ik[11][2][2])+((cnk[26][0][0]*
      ik[11][2][0])+(cnk[26][0][1]*ik[11][2][1])));
    ikcnkt[26][2][1] = ((cnk[26][1][2]*ik[11][2][2])+((cnk[26][1][0]*
      ik[11][2][0])+(cnk[26][1][1]*ik[11][2][1])));
    ikcnkt[26][2][2] = ((cnk[26][2][2]*ik[11][2][2])+((cnk[26][2][0]*
      ik[11][2][0])+(cnk[26][2][1]*ik[11][2][1])));
    temp[0] = (((mk[0]*((rnk[5][1]*rnk[5][1])+(rnk[5][2]*rnk[5][2])))+((
      cnk[5][0][2]*ikcnkt[5][2][0])+((cnk[5][0][0]*ikcnkt[5][0][0])+(
      cnk[5][0][1]*ikcnkt[5][1][0]))))+((mk[1]*((rnk[8][1]*rnk[8][1])+(rnk[8][2]
      *rnk[8][2])))+((cnk[8][0][2]*ikcnkt[8][2][0])+((cnk[8][0][0]*
      ikcnkt[8][0][0])+(cnk[8][0][1]*ikcnkt[8][1][0])))));
    temp[1] = (((mk[3]*((rnk[12][1]*rnk[12][1])+(rnk[12][2]*rnk[12][2])))+((
      cnk[12][0][2]*ikcnkt[12][2][0])+((cnk[12][0][0]*ikcnkt[12][0][0])+(
      cnk[12][0][1]*ikcnkt[12][1][0]))))+(((mk[2]*((rnk[11][1]*rnk[11][1])+(
      rnk[11][2]*rnk[11][2])))+((cnk[11][0][2]*ikcnkt[11][2][0])+((cnk[11][0][0]
      *ikcnkt[11][0][0])+(cnk[11][0][1]*ikcnkt[11][1][0]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[14][1]*rnk[14][1])+(rnk[14][2]*rnk[14][2])))+((
      cnk[14][0][2]*ikcnkt[14][2][0])+((cnk[14][0][0]*ikcnkt[14][0][0])+(
      cnk[14][0][1]*ikcnkt[14][1][0]))))+(((mk[4]*((rnk[13][1]*rnk[13][1])+(
      rnk[13][2]*rnk[13][2])))+((cnk[13][0][2]*ikcnkt[13][2][0])+((cnk[13][0][0]
      *ikcnkt[13][0][0])+(cnk[13][0][1]*ikcnkt[13][1][0]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[20][1]*rnk[20][1])+(rnk[20][2]*rnk[20][2])))+((
      cnk[20][0][2]*ikcnkt[20][2][0])+((cnk[20][0][0]*ikcnkt[20][0][0])+(
      cnk[20][0][1]*ikcnkt[20][1][0]))))+(((mk[6]*((rnk[17][1]*rnk[17][1])+(
      rnk[17][2]*rnk[17][2])))+((cnk[17][0][2]*ikcnkt[17][2][0])+((cnk[17][0][0]
      *ikcnkt[17][0][0])+(cnk[17][0][1]*ikcnkt[17][1][0]))))+temp[2]));
    temp[4] = (((mk[9]*((rnk[22][1]*rnk[22][1])+(rnk[22][2]*rnk[22][2])))+((
      cnk[22][0][2]*ikcnkt[22][2][0])+((cnk[22][0][0]*ikcnkt[22][0][0])+(
      cnk[22][0][1]*ikcnkt[22][1][0]))))+(((mk[8]*((rnk[21][1]*rnk[21][1])+(
      rnk[21][2]*rnk[21][2])))+((cnk[21][0][2]*ikcnkt[21][2][0])+((cnk[21][0][0]
      *ikcnkt[21][0][0])+(cnk[21][0][1]*ikcnkt[21][1][0]))))+temp[3]));
    icm[0][0] = ((((mk[11]*((rnk[26][1]*rnk[26][1])+(rnk[26][2]*rnk[26][2])))+((
      cnk[26][0][2]*ikcnkt[26][2][0])+((cnk[26][0][0]*ikcnkt[26][0][0])+(
      cnk[26][0][1]*ikcnkt[26][1][0]))))+(((mk[10]*((rnk[23][1]*rnk[23][1])+(
      rnk[23][2]*rnk[23][2])))+((cnk[23][0][2]*ikcnkt[23][2][0])+((cnk[23][0][0]
      *ikcnkt[23][0][0])+(cnk[23][0][1]*ikcnkt[23][1][0]))))+temp[4]))-(mtot*((
      com[1]*com[1])+(com[2]*com[2]))));
    temp[0] = ((((cnk[11][0][2]*ikcnkt[11][2][1])+((cnk[11][0][0]*
      ikcnkt[11][0][1])+(cnk[11][0][1]*ikcnkt[11][1][1])))-(mk[2]*(rnk[11][0]*
      rnk[11][1])))+((((cnk[5][0][2]*ikcnkt[5][2][1])+((cnk[5][0][0]*
      ikcnkt[5][0][1])+(cnk[5][0][1]*ikcnkt[5][1][1])))-(mk[0]*(rnk[5][0]*
      rnk[5][1])))+(((cnk[8][0][2]*ikcnkt[8][2][1])+((cnk[8][0][0]*
      ikcnkt[8][0][1])+(cnk[8][0][1]*ikcnkt[8][1][1])))-(mk[1]*(rnk[8][0]*
      rnk[8][1])))));
    temp[1] = ((((cnk[14][0][2]*ikcnkt[14][2][1])+((cnk[14][0][0]*
      ikcnkt[14][0][1])+(cnk[14][0][1]*ikcnkt[14][1][1])))-(mk[5]*(rnk[14][0]*
      rnk[14][1])))+((((cnk[13][0][2]*ikcnkt[13][2][1])+((cnk[13][0][0]*
      ikcnkt[13][0][1])+(cnk[13][0][1]*ikcnkt[13][1][1])))-(mk[4]*(rnk[13][0]*
      rnk[13][1])))+((((cnk[12][0][2]*ikcnkt[12][2][1])+((cnk[12][0][0]*
      ikcnkt[12][0][1])+(cnk[12][0][1]*ikcnkt[12][1][1])))-(mk[3]*(rnk[12][0]*
      rnk[12][1])))+temp[0])));
    temp[2] = ((((cnk[21][0][2]*ikcnkt[21][2][1])+((cnk[21][0][0]*
      ikcnkt[21][0][1])+(cnk[21][0][1]*ikcnkt[21][1][1])))-(mk[8]*(rnk[21][0]*
      rnk[21][1])))+((((cnk[20][0][2]*ikcnkt[20][2][1])+((cnk[20][0][0]*
      ikcnkt[20][0][1])+(cnk[20][0][1]*ikcnkt[20][1][1])))-(mk[7]*(rnk[20][0]*
      rnk[20][1])))+((((cnk[17][0][2]*ikcnkt[17][2][1])+((cnk[17][0][0]*
      ikcnkt[17][0][1])+(cnk[17][0][1]*ikcnkt[17][1][1])))-(mk[6]*(rnk[17][0]*
      rnk[17][1])))+temp[1])));
    temp[3] = ((((cnk[26][0][2]*ikcnkt[26][2][1])+((cnk[26][0][0]*
      ikcnkt[26][0][1])+(cnk[26][0][1]*ikcnkt[26][1][1])))-(mk[11]*(rnk[26][0]*
      rnk[26][1])))+((((cnk[23][0][2]*ikcnkt[23][2][1])+((cnk[23][0][0]*
      ikcnkt[23][0][1])+(cnk[23][0][1]*ikcnkt[23][1][1])))-(mk[10]*(rnk[23][0]*
      rnk[23][1])))+((((cnk[22][0][2]*ikcnkt[22][2][1])+((cnk[22][0][0]*
      ikcnkt[22][0][1])+(cnk[22][0][1]*ikcnkt[22][1][1])))-(mk[9]*(rnk[22][0]*
      rnk[22][1])))+temp[2])));
    icm[0][1] = ((mtot*(com[0]*com[1]))+temp[3]);
    temp[0] = ((((cnk[11][0][2]*ikcnkt[11][2][2])+((cnk[11][0][0]*
      ikcnkt[11][0][2])+(cnk[11][0][1]*ikcnkt[11][1][2])))-(mk[2]*(rnk[11][0]*
      rnk[11][2])))+((((cnk[5][0][2]*ikcnkt[5][2][2])+((cnk[5][0][0]*
      ikcnkt[5][0][2])+(cnk[5][0][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][0]*
      rnk[5][2])))+(((cnk[8][0][2]*ikcnkt[8][2][2])+((cnk[8][0][0]*
      ikcnkt[8][0][2])+(cnk[8][0][1]*ikcnkt[8][1][2])))-(mk[1]*(rnk[8][0]*
      rnk[8][2])))));
    temp[1] = ((((cnk[14][0][2]*ikcnkt[14][2][2])+((cnk[14][0][0]*
      ikcnkt[14][0][2])+(cnk[14][0][1]*ikcnkt[14][1][2])))-(mk[5]*(rnk[14][0]*
      rnk[14][2])))+((((cnk[13][0][2]*ikcnkt[13][2][2])+((cnk[13][0][0]*
      ikcnkt[13][0][2])+(cnk[13][0][1]*ikcnkt[13][1][2])))-(mk[4]*(rnk[13][0]*
      rnk[13][2])))+((((cnk[12][0][2]*ikcnkt[12][2][2])+((cnk[12][0][0]*
      ikcnkt[12][0][2])+(cnk[12][0][1]*ikcnkt[12][1][2])))-(mk[3]*(rnk[12][0]*
      rnk[12][2])))+temp[0])));
    temp[2] = ((((cnk[21][0][2]*ikcnkt[21][2][2])+((cnk[21][0][0]*
      ikcnkt[21][0][2])+(cnk[21][0][1]*ikcnkt[21][1][2])))-(mk[8]*(rnk[21][0]*
      rnk[21][2])))+((((cnk[20][0][2]*ikcnkt[20][2][2])+((cnk[20][0][0]*
      ikcnkt[20][0][2])+(cnk[20][0][1]*ikcnkt[20][1][2])))-(mk[7]*(rnk[20][0]*
      rnk[20][2])))+((((cnk[17][0][2]*ikcnkt[17][2][2])+((cnk[17][0][0]*
      ikcnkt[17][0][2])+(cnk[17][0][1]*ikcnkt[17][1][2])))-(mk[6]*(rnk[17][0]*
      rnk[17][2])))+temp[1])));
    temp[3] = ((((cnk[26][0][2]*ikcnkt[26][2][2])+((cnk[26][0][0]*
      ikcnkt[26][0][2])+(cnk[26][0][1]*ikcnkt[26][1][2])))-(mk[11]*(rnk[26][0]*
      rnk[26][2])))+((((cnk[23][0][2]*ikcnkt[23][2][2])+((cnk[23][0][0]*
      ikcnkt[23][0][2])+(cnk[23][0][1]*ikcnkt[23][1][2])))-(mk[10]*(rnk[23][0]*
      rnk[23][2])))+((((cnk[22][0][2]*ikcnkt[22][2][2])+((cnk[22][0][0]*
      ikcnkt[22][0][2])+(cnk[22][0][1]*ikcnkt[22][1][2])))-(mk[9]*(rnk[22][0]*
      rnk[22][2])))+temp[2])));
    icm[0][2] = ((mtot*(com[0]*com[2]))+temp[3]);
    icm[1][0] = icm[0][1];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][2]*rnk[5][2])))+((
      cnk[5][1][2]*ikcnkt[5][2][1])+((cnk[5][1][0]*ikcnkt[5][0][1])+(
      cnk[5][1][1]*ikcnkt[5][1][1]))))+((mk[1]*((rnk[8][0]*rnk[8][0])+(rnk[8][2]
      *rnk[8][2])))+((cnk[8][1][2]*ikcnkt[8][2][1])+((cnk[8][1][0]*
      ikcnkt[8][0][1])+(cnk[8][1][1]*ikcnkt[8][1][1])))));
    temp[1] = (((mk[3]*((rnk[12][0]*rnk[12][0])+(rnk[12][2]*rnk[12][2])))+((
      cnk[12][1][2]*ikcnkt[12][2][1])+((cnk[12][1][0]*ikcnkt[12][0][1])+(
      cnk[12][1][1]*ikcnkt[12][1][1]))))+(((mk[2]*((rnk[11][0]*rnk[11][0])+(
      rnk[11][2]*rnk[11][2])))+((cnk[11][1][2]*ikcnkt[11][2][1])+((cnk[11][1][0]
      *ikcnkt[11][0][1])+(cnk[11][1][1]*ikcnkt[11][1][1]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[14][0]*rnk[14][0])+(rnk[14][2]*rnk[14][2])))+((
      cnk[14][1][2]*ikcnkt[14][2][1])+((cnk[14][1][0]*ikcnkt[14][0][1])+(
      cnk[14][1][1]*ikcnkt[14][1][1]))))+(((mk[4]*((rnk[13][0]*rnk[13][0])+(
      rnk[13][2]*rnk[13][2])))+((cnk[13][1][2]*ikcnkt[13][2][1])+((cnk[13][1][0]
      *ikcnkt[13][0][1])+(cnk[13][1][1]*ikcnkt[13][1][1]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[20][0]*rnk[20][0])+(rnk[20][2]*rnk[20][2])))+((
      cnk[20][1][2]*ikcnkt[20][2][1])+((cnk[20][1][0]*ikcnkt[20][0][1])+(
      cnk[20][1][1]*ikcnkt[20][1][1]))))+(((mk[6]*((rnk[17][0]*rnk[17][0])+(
      rnk[17][2]*rnk[17][2])))+((cnk[17][1][2]*ikcnkt[17][2][1])+((cnk[17][1][0]
      *ikcnkt[17][0][1])+(cnk[17][1][1]*ikcnkt[17][1][1]))))+temp[2]));
    temp[4] = (((mk[9]*((rnk[22][0]*rnk[22][0])+(rnk[22][2]*rnk[22][2])))+((
      cnk[22][1][2]*ikcnkt[22][2][1])+((cnk[22][1][0]*ikcnkt[22][0][1])+(
      cnk[22][1][1]*ikcnkt[22][1][1]))))+(((mk[8]*((rnk[21][0]*rnk[21][0])+(
      rnk[21][2]*rnk[21][2])))+((cnk[21][1][2]*ikcnkt[21][2][1])+((cnk[21][1][0]
      *ikcnkt[21][0][1])+(cnk[21][1][1]*ikcnkt[21][1][1]))))+temp[3]));
    icm[1][1] = ((((mk[11]*((rnk[26][0]*rnk[26][0])+(rnk[26][2]*rnk[26][2])))+((
      cnk[26][1][2]*ikcnkt[26][2][1])+((cnk[26][1][0]*ikcnkt[26][0][1])+(
      cnk[26][1][1]*ikcnkt[26][1][1]))))+(((mk[10]*((rnk[23][0]*rnk[23][0])+(
      rnk[23][2]*rnk[23][2])))+((cnk[23][1][2]*ikcnkt[23][2][1])+((cnk[23][1][0]
      *ikcnkt[23][0][1])+(cnk[23][1][1]*ikcnkt[23][1][1]))))+temp[4]))-(mtot*((
      com[0]*com[0])+(com[2]*com[2]))));
    temp[0] = ((((cnk[11][1][2]*ikcnkt[11][2][2])+((cnk[11][1][0]*
      ikcnkt[11][0][2])+(cnk[11][1][1]*ikcnkt[11][1][2])))-(mk[2]*(rnk[11][1]*
      rnk[11][2])))+((((cnk[5][1][2]*ikcnkt[5][2][2])+((cnk[5][1][0]*
      ikcnkt[5][0][2])+(cnk[5][1][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][1]*
      rnk[5][2])))+(((cnk[8][1][2]*ikcnkt[8][2][2])+((cnk[8][1][0]*
      ikcnkt[8][0][2])+(cnk[8][1][1]*ikcnkt[8][1][2])))-(mk[1]*(rnk[8][1]*
      rnk[8][2])))));
    temp[1] = ((((cnk[14][1][2]*ikcnkt[14][2][2])+((cnk[14][1][0]*
      ikcnkt[14][0][2])+(cnk[14][1][1]*ikcnkt[14][1][2])))-(mk[5]*(rnk[14][1]*
      rnk[14][2])))+((((cnk[13][1][2]*ikcnkt[13][2][2])+((cnk[13][1][0]*
      ikcnkt[13][0][2])+(cnk[13][1][1]*ikcnkt[13][1][2])))-(mk[4]*(rnk[13][1]*
      rnk[13][2])))+((((cnk[12][1][2]*ikcnkt[12][2][2])+((cnk[12][1][0]*
      ikcnkt[12][0][2])+(cnk[12][1][1]*ikcnkt[12][1][2])))-(mk[3]*(rnk[12][1]*
      rnk[12][2])))+temp[0])));
    temp[2] = ((((cnk[21][1][2]*ikcnkt[21][2][2])+((cnk[21][1][0]*
      ikcnkt[21][0][2])+(cnk[21][1][1]*ikcnkt[21][1][2])))-(mk[8]*(rnk[21][1]*
      rnk[21][2])))+((((cnk[20][1][2]*ikcnkt[20][2][2])+((cnk[20][1][0]*
      ikcnkt[20][0][2])+(cnk[20][1][1]*ikcnkt[20][1][2])))-(mk[7]*(rnk[20][1]*
      rnk[20][2])))+((((cnk[17][1][2]*ikcnkt[17][2][2])+((cnk[17][1][0]*
      ikcnkt[17][0][2])+(cnk[17][1][1]*ikcnkt[17][1][2])))-(mk[6]*(rnk[17][1]*
      rnk[17][2])))+temp[1])));
    temp[3] = ((((cnk[26][1][2]*ikcnkt[26][2][2])+((cnk[26][1][0]*
      ikcnkt[26][0][2])+(cnk[26][1][1]*ikcnkt[26][1][2])))-(mk[11]*(rnk[26][1]*
      rnk[26][2])))+((((cnk[23][1][2]*ikcnkt[23][2][2])+((cnk[23][1][0]*
      ikcnkt[23][0][2])+(cnk[23][1][1]*ikcnkt[23][1][2])))-(mk[10]*(rnk[23][1]*
      rnk[23][2])))+((((cnk[22][1][2]*ikcnkt[22][2][2])+((cnk[22][1][0]*
      ikcnkt[22][0][2])+(cnk[22][1][1]*ikcnkt[22][1][2])))-(mk[9]*(rnk[22][1]*
      rnk[22][2])))+temp[2])));
    icm[1][2] = ((mtot*(com[1]*com[2]))+temp[3]);
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][1]*rnk[5][1])))+((
      cnk[5][2][2]*ikcnkt[5][2][2])+((cnk[5][2][0]*ikcnkt[5][0][2])+(
      cnk[5][2][1]*ikcnkt[5][1][2]))))+((mk[1]*((rnk[8][0]*rnk[8][0])+(rnk[8][1]
      *rnk[8][1])))+((cnk[8][2][2]*ikcnkt[8][2][2])+((cnk[8][2][0]*
      ikcnkt[8][0][2])+(cnk[8][2][1]*ikcnkt[8][1][2])))));
    temp[1] = (((mk[3]*((rnk[12][0]*rnk[12][0])+(rnk[12][1]*rnk[12][1])))+((
      cnk[12][2][2]*ikcnkt[12][2][2])+((cnk[12][2][0]*ikcnkt[12][0][2])+(
      cnk[12][2][1]*ikcnkt[12][1][2]))))+(((mk[2]*((rnk[11][0]*rnk[11][0])+(
      rnk[11][1]*rnk[11][1])))+((cnk[11][2][2]*ikcnkt[11][2][2])+((cnk[11][2][0]
      *ikcnkt[11][0][2])+(cnk[11][2][1]*ikcnkt[11][1][2]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[14][0]*rnk[14][0])+(rnk[14][1]*rnk[14][1])))+((
      cnk[14][2][2]*ikcnkt[14][2][2])+((cnk[14][2][0]*ikcnkt[14][0][2])+(
      cnk[14][2][1]*ikcnkt[14][1][2]))))+(((mk[4]*((rnk[13][0]*rnk[13][0])+(
      rnk[13][1]*rnk[13][1])))+((cnk[13][2][2]*ikcnkt[13][2][2])+((cnk[13][2][0]
      *ikcnkt[13][0][2])+(cnk[13][2][1]*ikcnkt[13][1][2]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[20][0]*rnk[20][0])+(rnk[20][1]*rnk[20][1])))+((
      cnk[20][2][2]*ikcnkt[20][2][2])+((cnk[20][2][0]*ikcnkt[20][0][2])+(
      cnk[20][2][1]*ikcnkt[20][1][2]))))+(((mk[6]*((rnk[17][0]*rnk[17][0])+(
      rnk[17][1]*rnk[17][1])))+((cnk[17][2][2]*ikcnkt[17][2][2])+((cnk[17][2][0]
      *ikcnkt[17][0][2])+(cnk[17][2][1]*ikcnkt[17][1][2]))))+temp[2]));
    temp[4] = (((mk[9]*((rnk[22][0]*rnk[22][0])+(rnk[22][1]*rnk[22][1])))+((
      cnk[22][2][2]*ikcnkt[22][2][2])+((cnk[22][2][0]*ikcnkt[22][0][2])+(
      cnk[22][2][1]*ikcnkt[22][1][2]))))+(((mk[8]*((rnk[21][0]*rnk[21][0])+(
      rnk[21][1]*rnk[21][1])))+((cnk[21][2][2]*ikcnkt[21][2][2])+((cnk[21][2][0]
      *ikcnkt[21][0][2])+(cnk[21][2][1]*ikcnkt[21][1][2]))))+temp[3]));
    icm[2][2] = ((((mk[11]*((rnk[26][0]*rnk[26][0])+(rnk[26][1]*rnk[26][1])))+((
      cnk[26][2][2]*ikcnkt[26][2][2])+((cnk[26][2][0]*ikcnkt[26][0][2])+(
      cnk[26][2][1]*ikcnkt[26][1][2]))))+(((mk[10]*((rnk[23][0]*rnk[23][0])+(
      rnk[23][1]*rnk[23][1])))+((cnk[23][2][2]*ikcnkt[23][2][2])+((cnk[23][2][0]
      *ikcnkt[23][0][2])+(cnk[23][2][1]*ikcnkt[23][1][2]))))+temp[4]))-(mtot*((
      com[0]*com[0])+(com[1]*com[1]))));
/*
 Used 0.28 seconds CPU time,
 40960 additional bytes of memory.
 Equations contain  543 adds/subtracts/negates
                    735 multiplies
                      0 divides
                    148 assignments
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

    if ((coord < 0) || (coord > 26)) {
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
    info[11] = 27;
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
    info[0] = 1;
    info[1] = firstu[consno];
/* info entries from 2-49 are reserved */
}
int 
sdchkbnum(routine,bnum)
    int routine,bnum;
{

    if ((bnum < -1) || (bnum > 11)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(routine,jnum)
    int routine,jnum;
{

    if ((jnum < 0) || (jnum > 11)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(routine,ucnum)
    int routine,ucnum;
{

    if ((ucnum < 0) || (ucnum > 3)) {
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
    double st[27],stang[27];
{
    int i;

    for (i = 0; i < 27; i++) {
        stang[i] = st[i];
    }
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

sdang2st(stang,st)
    double stang[27],st[27];
{
    int i;

    for (i = 0; i < 27; i++) {
        st[i] = stang[i];
    }
}

/* Normalize Euler parameters in state. */

sdnrmsterr(st,normst,routine)
    double st[27],normst[27];
    int routine;
{
    int i;

    for (i = 0; i < 27; i++) {
        normst[i] = st[i];
    }
}

sdnormst(st,normst)
    double st[27],normst[27];
{

    sdnrmsterr(st,normst,0);
}

sdgentime(gentm)
    int *gentm;
{

    *gentm = 115928;
}
/*
Done. CPU seconds used: 6.69  Memory used: 1490944 bytes.
Equation complexity:
  sdstate:  2238 adds  3162 multiplies     3 divides  1521 assignments
  sdderiv: 60290 adds 63921 multiplies   861 divides 63168 assignments
  sdresid:  5198 adds  5919 multiplies     0 divides  2389 assignments
  sdreac:    936 adds   666 multiplies     0 divides   540 assignments
  sdmom:     359 adds   403 multiplies     0 divides    99 assignments
  sdsys:     543 adds   735 multiplies     0 divides   148 assignments
*/
