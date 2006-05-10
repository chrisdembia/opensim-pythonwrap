/*
Generated 20-Feb-2002 17:54:54 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (utModel.sd)

Bodies        Inb
No  Name      body Joint type  Coords q
--- --------- ---- ----------- ----------------
 -1 $ground                                    
  0 pelvis     -1  Sixdof        0   1   2 
                   ...           3   4   5  23 
  1 hat         0  Gimbal        6   7   8     
  2 rfemur      0  Gimbal        9  10  11     
  3 rtibia      2  Pin          12             
  4 rhindfoot   3  U-joint      13  14         
  5 rtoes       4  Pin          15             
  6 lfemur      0  Gimbal       16  17  18     
  7 ltibia      6  Pin          19             
  8 lhindfoot   7  U-joint      20  21         
  9 ltoes       8  Pin          22             

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[10],inb_[10],outb_[10],njntdof_[10],njntc_[10],njntp_[10],firstq_
      [10],ballq_[10],firstm_[10],firstp_[10];
    int trans_[23];
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
    double grav_[3],mk_[10],ik_[10][3][3],pin_[23][3];
    double rk_[10][3],ri_[10][3],pres_[23],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[23];
    int gravq_[3],mkq_[10],ikq_[10][3][3],pinq_[23][3],rkq_[10][3],riq_[10][3],
      presq_[23],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[10][3],rcom_[10][3],mkrcomt_[10][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[23],psik_[23][3][3],psrcom_[23][3
      ],psrk_[23][3],psri_[23][3];
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
    double curtim_,q_[24],qn_[24],u_[23],cnk_[23][3][3],cnb_[10][3][3];
    double rnk_[23][3],vnk_[23][3],wk_[23][3],rnb_[10][3],vnb_[10][3],wb_[10][3]
      ,wbrcom_[10][3],com_[3],rnkg_[3];
    double Cik_[23][3][3],rikt_[23][3][3],Iko_[23][3][3],mkrk_[23][3][3],Cib_[10
      ][3][3];
    double Wkk_[23][3],Vkk_[23][3],dik_[23][3],rpp_[23][3],rpk_[23][3],rik_[23][
      3],rik2_[23][3];
    double rpri_[23][3],Wik_[23][3],Vik_[23][3],Wirk_[23][3],rkWkk_[23][3],
      Wkrpk_[23][3],VikWkr_[23][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[10][3],utk_[10][3],mfk_[10][
      3],mtk_[10][3];
    double utau_[23],mtau_[23],uacc_[23],uvel_[23],upos_[24];
    double s6_,c6_,s7_,c7_,s8_,c8_,s9_,c9_,s10_,c10_,s11_,c11_,s12_,c12_,s13_,
      c13_,s14_,c14_,s15_,c15_,s16_,c16_,s17_,c17_,s18_,c18_,s19_,c19_,s20_,c20_
      ,s21_,c21_,s22_,c22_;
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

typedef struct {
    double fs0_[23],qdot_[24],Otk_[23][3],Atk_[23][3],AiOiWi_[23][3],Fstar_[23][
      3];
    double Tstar_[23][3],Fstark_[23][3],Tstark_[23][3],IkWk_[23][3],WkIkWk_[23][
      3],gk_[23][3],IkbWk_[10][3],WkIkbWk_[10][3];
    double w0w0_[10],w1w1_[10],w2w2_[10],w0w1_[10],w0w2_[10],w1w2_[10];
    double w00w11_[10],w00w22_[10],w11w22_[10],ww_[1][1],qraux_[1];
    double mm_[23][23],mlo_[23][23],mdi_[23],IkWpk_[23][23][3],works_[23],
      workss_[23][23];
    double Wpk_[23][23][3],Vpk_[23][23][3],VWri_[23][23][3];
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
    double fs_[23],udot_[23],tauc_[23],dyad_[10][3][3],fc_[23][3],tc_[23][3];
    double ank_[23][3],onk_[23][3],Onkb_[23][3],AOnkri_[23][3],Ankb_[23][3],
      AnkAtk_[23][3],anb_[10][3],onb_[10][3],dyrcom_[10][3];
    double ffk_[23][3],ttk_[23][3],fccikt_[23][3],ffkb_[10][3],ttkb_[10][3];
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
    /* ground */ 0,
    /* nbod */ 10,
    /* ndof */ 23,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 1,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 6,
    /* jtype[1] */ 3,
    /* jtype[2] */ 3,
    /* jtype[3] */ 1,
    /* jtype[4] */ 2,
    /* jtype[5] */ 1,
    /* jtype[6] */ 3,
    /* jtype[7] */ 1,
    /* jtype[8] */ 2,
    /* jtype[9] */ 1,
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
    /* njntdof[3] */ 1,
    /* njntdof[4] */ 2,
    /* njntdof[5] */ 1,
    /* njntdof[6] */ 3,
    /* njntdof[7] */ 1,
    /* njntdof[8] */ 2,
    /* njntdof[9] */ 1,
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
    /* njntp[0] */ 0,
    /* njntp[1] */ 0,
    /* njntp[2] */ 0,
    /* njntp[3] */ 0,
    /* njntp[4] */ 0,
    /* njntp[5] */ 0,
    /* njntp[6] */ 0,
    /* njntp[7] */ 0,
    /* njntp[8] */ 0,
    /* njntp[9] */ 0,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 9,
    /* firstq[3] */ 12,
    /* firstq[4] */ 13,
    /* firstq[5] */ 15,
    /* firstq[6] */ 16,
    /* firstq[7] */ 19,
    /* firstq[8] */ 20,
    /* firstq[9] */ 22,
    /* ballq[0] */ 23,
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
    /* firstp[0] */ -1,
    /* firstp[1] */ -1,
    /* firstp[2] */ -1,
    /* firstp[3] */ -1,
    /* firstp[4] */ -1,
    /* firstp[5] */ -1,
    /* firstp[6] */ -1,
    /* firstp[7] */ -1,
    /* firstp[8] */ -1,
    /* firstp[9] */ -1,
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
    /* pin[12][0] */ -.080909,
    /* pin[12][1] */ .040455,
    /* pin[12][2] */ .9959,
    /* pin[13][0] */ -.082186,
    /* pin[13][1] */ -.037209,
    /* pin[13][2] */ .995922,
    /* pin[14][0] */ .814756,
    /* pin[14][1] */ .57726,
    /* pin[14][2] */ -.054258,
    /* pin[15][0] */ -.469472,
    /* pin[15][1] */ 0.,
    /* pin[15][2] */ .882948,
    /* pin[16][0] */ 0.,
    /* pin[16][1] */ 0.,
    /* pin[16][2] */ 1.,
    /* pin[17][0] */ -1.,
    /* pin[17][1] */ 0.,
    /* pin[17][2] */ 0.,
    /* pin[18][0] */ 0.,
    /* pin[18][1] */ -1.,
    /* pin[18][2] */ 0.,
    /* pin[19][0] */ .080909,
    /* pin[19][1] */ -.040455,
    /* pin[19][2] */ .9959,
    /* pin[20][0] */ .082186,
    /* pin[20][1] */ .037209,
    /* pin[20][2] */ .995922,
    /* pin[21][0] */ -.814756,
    /* pin[21][1] */ -.57726,
    /* pin[21][2] */ -.054258,
    /* pin[22][0] */ .469472,
    /* pin[22][1] */ 0.,
    /* pin[22][2] */ .882948,

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
    /* pinq[9][0] */ 0,
    /* pinq[9][1] */ 0,
    /* pinq[9][2] */ 0,
    /* pinq[10][0] */ 0,
    /* pinq[10][1] */ 0,
    /* pinq[10][2] */ 0,
    /* pinq[11][0] */ 0,
    /* pinq[11][1] */ 0,
    /* pinq[11][2] */ 0,
    /* pinq[12][0] */ 0,
    /* pinq[12][1] */ 0,
    /* pinq[12][2] */ 0,
    /* pinq[13][0] */ 0,
    /* pinq[13][1] */ 0,
    /* pinq[13][2] */ 0,
    /* pinq[14][0] */ 0,
    /* pinq[14][1] */ 0,
    /* pinq[14][2] */ 0,
    /* pinq[15][0] */ 0,
    /* pinq[15][1] */ 0,
    /* pinq[15][2] */ 0,
    /* pinq[16][0] */ 0,
    /* pinq[16][1] */ 0,
    /* pinq[16][2] */ 0,
    /* pinq[17][0] */ 0,
    /* pinq[17][1] */ 0,
    /* pinq[17][2] */ 0,
    /* pinq[18][0] */ 0,
    /* pinq[18][1] */ 0,
    /* pinq[18][2] */ 0,
    /* pinq[19][0] */ 0,
    /* pinq[19][1] */ 0,
    /* pinq[19][2] */ 0,
    /* pinq[20][0] */ 0,
    /* pinq[20][1] */ 0,
    /* pinq[20][2] */ 0,
    /* pinq[21][0] */ 0,
    /* pinq[21][1] */ 0,
    /* pinq[21][2] */ 0,
    /* pinq[22][0] */ 0,
    /* pinq[22][1] */ 0,
    /* pinq[22][2] */ 0,
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
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* presq[6] */ 0,
    /* presq[7] */ 0,
    /* presq[8] */ 0,
    /* presq[9] */ 0,
    /* presq[10] */ 0,
    /* presq[11] */ 0,
    /* presq[12] */ 0,
    /* presq[13] */ 0,
    /* presq[14] */ 0,
    /* presq[15] */ 0,
    /* presq[16] */ 0,
    /* presq[17] */ 0,
    /* presq[18] */ 0,
    /* presq[19] */ 0,
    /* presq[20] */ 0,
    /* presq[21] */ 0,
    /* presq[22] */ 0,
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
    for (k = 0; k < 23; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 23; i++) {
        for (j = i; j <= 22; j++) {
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

/* Compute mass properties-related constants */

    mtot = 71.005252;
    sdserialno(&i);
    if (i != 70405) {
        sdseterr(7,41);
    }
    roustate = 1;
}

sdstate(timein,qin,uin)
    double timein,qin[24],uin[23];
{
/*
Compute kinematic information and store it in sdgstate.

Generated 20-Feb-2002 17:54:54 by SD/FAST, Kane's formulation
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
    double ee,stab;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 23; i++) {
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
        for (i = 0; i < 24; i++) {
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
        for (i = 0; i < 23; i++) {
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
    for (i = 0; i < 24; i++) {
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
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (1.-(2.*((qn[4]*qn[4])+(qn[5]*qn[5]))));
    Cik[3][0][1] = (2.*((qn[3]*qn[4])-(qn[5]*qn[23])));
    Cik[3][0][2] = (2.*((qn[3]*qn[5])+(qn[4]*qn[23])));
    Cik[3][1][0] = (2.*((qn[3]*qn[4])+(qn[5]*qn[23])));
    Cik[3][1][1] = (1.-(2.*((qn[3]*qn[3])+(qn[5]*qn[5]))));
    Cik[3][1][2] = (2.*((qn[4]*qn[5])-(qn[3]*qn[23])));
    Cik[3][2][0] = (2.*((qn[3]*qn[5])-(qn[4]*qn[23])));
    Cik[3][2][1] = (2.*((qn[3]*qn[23])+(qn[4]*qn[5])));
    Cik[3][2][2] = (1.-(2.*((qn[3]*qn[3])+(qn[4]*qn[4]))));
    Cik[12][0][0] = (.00654626835416391+(.993453731645836*c12));
    Cik[12][0][1] = ((.00327317463159476*c12)-(.00327317463159476+(
      .995900157697815*s12)));
    Cik[12][0][2] = ((.080577298618347*c12)+((.0404550064059294*s12)-
      .080577298618347));
    Cik[12][1][0] = ((.00327317463159476*c12)+((.995900157697815*s12)-
      .00327317463159476));
    Cik[12][1][1] = (.00163660754330379+(.998363392456696*c12));
    Cik[12][1][2] = (.0402891472593312+((.0809090128117004*s12)-(
      .0402891472593312*c12)));
    Cik[12][2][0] = ((.080577298618347*c12)-(.080577298618347+(.0404550064059294
      *s12)));
    Cik[12][2][1] = (.0402891472593312-((.0402891472593312*c12)+(
      .0809090128117004*s12)));
    Cik[12][2][2] = (.991817124102532+(.00818287589746802*c12));
    Cik[13][0][0] = (.00675454076852374+(.993245459231476*c13));
    Cik[13][0][1] = (.00305805985759131-((.00305805985759131*c13)+(
      .995922160163717*s13)));
    Cik[13][0][2] = ((.0818508718184325*c13)-(.0818508718184325+(
      .0372090059839342*s13)));
    Cik[13][1][0] = (.00305805985759131+((.995922160163717*s13)-(
      .00305805985759131*c13)));
    Cik[13][1][1] = (.00138451012631245+(.998615489873688*c13));
    Cik[13][1][2] = ((.0370572736170644*c13)+((.0821860132171146*s13)-
      .0370572736170644));
    Cik[13][2][0] = ((.0818508718184325*c13)+((.0372090059839342*s13)-
      .0818508718184325));
    Cik[13][2][1] = ((.0370572736170644*c13)-(.0370572736170644+(
      .0821860132171146*s13)));
    Cik[13][2][2] = (.991860949105164+(.00813905089483624*c13));
    Cik[14][0][0] = (.663827088808508+(.336172911191492*c14));
    Cik[14][0][1] = (.470325870917918+((.0542579897533796*s14)-(.470325870917918
      *c14)));
    Cik[14][0][2] = ((.0442070143510107*c14)+((.57725989098448*s14)-
      .0442070143510107));
    Cik[14][1][0] = (.470325870917918-((.0542579897533796*s14)+(.470325870917918
      *c14)));
    Cik[14][1][1] = (.333228981739414+(.666771018260586*c14));
    Cik[14][1][2] = ((.0313209612500729*c14)-(.0313209612500729+(
      .814755846133373*s14)));
    Cik[14][2][0] = ((.0442070143510107*c14)-(.0442070143510107+(.57725989098448
      *s14)));
    Cik[14][2][1] = ((.0313209612500729*c14)+((.814755846133373*s14)-
      .0313209612500729));
    Cik[14][2][2] = (.00294392945207784+(.997056070547922*c14));
    Cik[15][0][0] = (.220403709840655+(.779596290159345*c15));
    Cik[15][0][2] = ((.414518895261882*c15)-.414518895261882);
    Cik[15][2][0] = ((.414518895261882*c15)-.414518895261882);
    Cik[15][2][2] = (.779596290159345+(.220403709840655*c15));
    Cik[19][0][0] = (.00654626835416391+(.993453731645836*c19));
    Cik[19][0][1] = ((.00327317463159476*c19)-(.00327317463159476+(
      .995900157697815*s19)));
    Cik[19][0][2] = (.080577298618347-((.0404550064059294*s19)+(.080577298618347
      *c19)));
    Cik[19][1][0] = ((.00327317463159476*c19)+((.995900157697815*s19)-
      .00327317463159476));
    Cik[19][1][1] = (.00163660754330379+(.998363392456696*c19));
    Cik[19][1][2] = ((.0402891472593312*c19)-(.0402891472593312+(
      .0809090128117004*s19)));
    Cik[19][2][0] = (.080577298618347+((.0404550064059294*s19)-(.080577298618347
      *c19)));
    Cik[19][2][1] = ((.0402891472593312*c19)+((.0809090128117004*s19)-
      .0402891472593312));
    Cik[19][2][2] = (.991817124102532+(.00818287589746802*c19));
    Cik[20][0][0] = (.00675454076852374+(.993245459231476*c20));
    Cik[20][0][1] = (.00305805985759131-((.00305805985759131*c20)+(
      .995922160163717*s20)));
    Cik[20][0][2] = (.0818508718184325+((.0372090059839342*s20)-(
      .0818508718184325*c20)));
    Cik[20][1][0] = (.00305805985759131+((.995922160163717*s20)-(
      .00305805985759131*c20)));
    Cik[20][1][1] = (.00138451012631245+(.998615489873688*c20));
    Cik[20][1][2] = (.0370572736170644-((.0370572736170644*c20)+(
      .0821860132171146*s20)));
    Cik[20][2][0] = (.0818508718184325-((.0372090059839342*s20)+(
      .0818508718184325*c20)));
    Cik[20][2][1] = (.0370572736170644+((.0821860132171146*s20)-(
      .0370572736170644*c20)));
    Cik[20][2][2] = (.991860949105164+(.00813905089483624*c20));
    Cik[21][0][0] = (.663827088808508+(.336172911191492*c21));
    Cik[21][0][1] = (.470325870917918+((.0542579897533796*s21)-(.470325870917918
      *c21)));
    Cik[21][0][2] = (.0442070143510107-((.0442070143510107*c21)+(.57725989098448
      *s21)));
    Cik[21][1][0] = (.470325870917918-((.0542579897533796*s21)+(.470325870917918
      *c21)));
    Cik[21][1][1] = (.333228981739414+(.666771018260586*c21));
    Cik[21][1][2] = (.0313209612500729+((.814755846133373*s21)-(
      .0313209612500729*c21)));
    Cik[21][2][0] = (.0442070143510107+((.57725989098448*s21)-(.0442070143510107
      *c21)));
    Cik[21][2][1] = (.0313209612500729-((.0313209612500729*c21)+(
      .814755846133373*s21)));
    Cik[21][2][2] = (.00294392945207784+(.997056070547922*c21));
    Cik[22][0][0] = (.220403709840655+(.779596290159345*c22));
    Cik[22][0][2] = (.414518895261882-(.414518895261882*c22));
    Cik[22][2][0] = (.414518895261882-(.414518895261882*c22));
    Cik[22][2][2] = (.779596290159345+(.220403709840655*c22));
/*
Compute across-joint direction cosines Cib
*/
    Cib[1][0][0] = ((c6*c8)-(s8*(s6*s7)));
    Cib[1][0][1] = -(s6*c7);
    Cib[1][0][2] = ((s8*c6)+(c8*(s6*s7)));
    Cib[1][1][0] = ((s6*c8)+(s8*(s7*c6)));
    Cib[1][1][1] = (c6*c7);
    Cib[1][1][2] = ((s6*s8)-(c8*(s7*c6)));
    Cib[1][2][0] = -(s8*c7);
    Cib[1][2][2] = (c7*c8);
    Cib[2][0][0] = ((c9*c11)-(s11*(s9*s10)));
    Cib[2][0][1] = -(s9*c10);
    Cib[2][0][2] = ((s11*c9)+(c11*(s9*s10)));
    Cib[2][1][0] = ((s9*c11)+(s11*(s10*c9)));
    Cib[2][1][1] = (c9*c10);
    Cib[2][1][2] = ((s9*s11)-(c11*(s10*c9)));
    Cib[2][2][0] = -(s11*c10);
    Cib[2][2][2] = (c10*c11);
    Cib[4][0][0] = ((Cik[13][0][2]*Cik[14][2][0])+((Cik[13][0][0]*Cik[14][0][0])
      +(Cik[13][0][1]*Cik[14][1][0])));
    Cib[4][0][1] = ((Cik[13][0][2]*Cik[14][2][1])+((Cik[13][0][0]*Cik[14][0][1])
      +(Cik[13][0][1]*Cik[14][1][1])));
    Cib[4][0][2] = ((Cik[13][0][2]*Cik[14][2][2])+((Cik[13][0][0]*Cik[14][0][2])
      +(Cik[13][0][1]*Cik[14][1][2])));
    Cib[4][1][0] = ((Cik[13][1][2]*Cik[14][2][0])+((Cik[13][1][0]*Cik[14][0][0])
      +(Cik[13][1][1]*Cik[14][1][0])));
    Cib[4][1][1] = ((Cik[13][1][2]*Cik[14][2][1])+((Cik[13][1][0]*Cik[14][0][1])
      +(Cik[13][1][1]*Cik[14][1][1])));
    Cib[4][1][2] = ((Cik[13][1][2]*Cik[14][2][2])+((Cik[13][1][0]*Cik[14][0][2])
      +(Cik[13][1][1]*Cik[14][1][2])));
    Cib[4][2][0] = ((Cik[13][2][2]*Cik[14][2][0])+((Cik[13][2][0]*Cik[14][0][0])
      +(Cik[13][2][1]*Cik[14][1][0])));
    Cib[4][2][1] = ((Cik[13][2][2]*Cik[14][2][1])+((Cik[13][2][0]*Cik[14][0][1])
      +(Cik[13][2][1]*Cik[14][1][1])));
    Cib[4][2][2] = ((Cik[13][2][2]*Cik[14][2][2])+((Cik[13][2][0]*Cik[14][0][2])
      +(Cik[13][2][1]*Cik[14][1][2])));
    Cib[6][0][0] = ((c16*c18)-(s18*(s16*s17)));
    Cib[6][0][1] = -(s16*c17);
    Cib[6][0][2] = -((s18*c16)+(c18*(s16*s17)));
    Cib[6][1][0] = ((s16*c18)+(s18*(s17*c16)));
    Cib[6][1][1] = (c16*c17);
    Cib[6][1][2] = ((c18*(s17*c16))-(s16*s18));
    Cib[6][2][0] = (s18*c17);
    Cib[6][2][2] = (c17*c18);
    Cib[8][0][0] = ((Cik[20][0][2]*Cik[21][2][0])+((Cik[20][0][0]*Cik[21][0][0])
      +(Cik[20][0][1]*Cik[21][1][0])));
    Cib[8][0][1] = ((Cik[20][0][2]*Cik[21][2][1])+((Cik[20][0][0]*Cik[21][0][1])
      +(Cik[20][0][1]*Cik[21][1][1])));
    Cib[8][0][2] = ((Cik[20][0][2]*Cik[21][2][2])+((Cik[20][0][0]*Cik[21][0][2])
      +(Cik[20][0][1]*Cik[21][1][2])));
    Cib[8][1][0] = ((Cik[20][1][2]*Cik[21][2][0])+((Cik[20][1][0]*Cik[21][0][0])
      +(Cik[20][1][1]*Cik[21][1][0])));
    Cib[8][1][1] = ((Cik[20][1][2]*Cik[21][2][1])+((Cik[20][1][0]*Cik[21][0][1])
      +(Cik[20][1][1]*Cik[21][1][1])));
    Cib[8][1][2] = ((Cik[20][1][2]*Cik[21][2][2])+((Cik[20][1][0]*Cik[21][0][2])
      +(Cik[20][1][1]*Cik[21][1][2])));
    Cib[8][2][0] = ((Cik[20][2][2]*Cik[21][2][0])+((Cik[20][2][0]*Cik[21][0][0])
      +(Cik[20][2][1]*Cik[21][1][0])));
    Cib[8][2][1] = ((Cik[20][2][2]*Cik[21][2][1])+((Cik[20][2][0]*Cik[21][0][1])
      +(Cik[20][2][1]*Cik[21][1][1])));
    Cib[8][2][2] = ((Cik[20][2][2]*Cik[21][2][2])+((Cik[20][2][0]*Cik[21][0][2])
      +(Cik[20][2][1]*Cik[21][1][2])));
/*
Compute gravity
*/
    gk[3][0] = ((Cik[3][2][0]*grav[2])+((Cik[3][0][0]*grav[0])+(Cik[3][1][0]*
      grav[1])));
    gk[3][1] = ((Cik[3][2][1]*grav[2])+((Cik[3][0][1]*grav[0])+(Cik[3][1][1]*
      grav[1])));
    gk[3][2] = ((Cik[3][2][2]*grav[2])+((Cik[3][0][2]*grav[0])+(Cik[3][1][2]*
      grav[1])));
    gk[6][0] = ((gk[3][0]*c6)+(gk[3][1]*s6));
    gk[6][1] = ((gk[3][1]*c6)-(gk[3][0]*s6));
    gk[7][1] = ((gk[3][2]*s7)+(gk[6][1]*c7));
    gk[7][2] = ((gk[3][2]*c7)-(gk[6][1]*s7));
    gk[8][0] = ((gk[6][0]*c8)-(gk[7][2]*s8));
    gk[8][2] = ((gk[6][0]*s8)+(gk[7][2]*c8));
    gk[9][0] = ((gk[3][0]*c9)+(gk[3][1]*s9));
    gk[9][1] = ((gk[3][1]*c9)-(gk[3][0]*s9));
    gk[10][1] = ((gk[3][2]*s10)+(gk[9][1]*c10));
    gk[10][2] = ((gk[3][2]*c10)-(gk[9][1]*s10));
    gk[11][0] = ((gk[9][0]*c11)-(gk[10][2]*s11));
    gk[11][2] = ((gk[9][0]*s11)+(gk[10][2]*c11));
    gk[12][0] = ((Cik[12][2][0]*gk[11][2])+((Cik[12][0][0]*gk[11][0])+(
      Cik[12][1][0]*gk[10][1])));
    gk[12][1] = ((Cik[12][2][1]*gk[11][2])+((Cik[12][0][1]*gk[11][0])+(
      Cik[12][1][1]*gk[10][1])));
    gk[12][2] = ((Cik[12][2][2]*gk[11][2])+((Cik[12][0][2]*gk[11][0])+(
      Cik[12][1][2]*gk[10][1])));
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
    gk[15][0] = ((Cik[15][2][0]*gk[14][2])+((.882947501360837*(gk[14][1]*s15))+(
      Cik[15][0][0]*gk[14][0])));
    gk[15][1] = (((gk[14][1]*c15)-(.882947501360837*(gk[14][0]*s15)))-(
      .469471734868729*(gk[14][2]*s15)));
    gk[15][2] = ((Cik[15][2][2]*gk[14][2])+((.469471734868729*(gk[14][1]*s15))+(
      Cik[15][0][2]*gk[14][0])));
    gk[16][0] = ((gk[3][0]*c16)+(gk[3][1]*s16));
    gk[16][1] = ((gk[3][1]*c16)-(gk[3][0]*s16));
    gk[17][1] = ((gk[16][1]*c17)-(gk[3][2]*s17));
    gk[17][2] = ((gk[3][2]*c17)+(gk[16][1]*s17));
    gk[18][0] = ((gk[16][0]*c18)+(gk[17][2]*s18));
    gk[18][2] = ((gk[17][2]*c18)-(gk[16][0]*s18));
    gk[19][0] = ((Cik[19][2][0]*gk[18][2])+((Cik[19][0][0]*gk[18][0])+(
      Cik[19][1][0]*gk[17][1])));
    gk[19][1] = ((Cik[19][2][1]*gk[18][2])+((Cik[19][0][1]*gk[18][0])+(
      Cik[19][1][1]*gk[17][1])));
    gk[19][2] = ((Cik[19][2][2]*gk[18][2])+((Cik[19][0][2]*gk[18][0])+(
      Cik[19][1][2]*gk[17][1])));
    gk[20][0] = ((Cik[20][2][0]*gk[19][2])+((Cik[20][0][0]*gk[19][0])+(
      Cik[20][1][0]*gk[19][1])));
    gk[20][1] = ((Cik[20][2][1]*gk[19][2])+((Cik[20][0][1]*gk[19][0])+(
      Cik[20][1][1]*gk[19][1])));
    gk[20][2] = ((Cik[20][2][2]*gk[19][2])+((Cik[20][0][2]*gk[19][0])+(
      Cik[20][1][2]*gk[19][1])));
    gk[21][0] = ((Cik[21][2][0]*gk[20][2])+((Cik[21][0][0]*gk[20][0])+(
      Cik[21][1][0]*gk[20][1])));
    gk[21][1] = ((Cik[21][2][1]*gk[20][2])+((Cik[21][0][1]*gk[20][0])+(
      Cik[21][1][1]*gk[20][1])));
    gk[21][2] = ((Cik[21][2][2]*gk[20][2])+((Cik[21][0][2]*gk[20][0])+(
      Cik[21][1][2]*gk[20][1])));
    gk[22][0] = ((Cik[22][2][0]*gk[21][2])+((.882947501360837*(gk[21][1]*s22))+(
      Cik[22][0][0]*gk[21][0])));
    gk[22][1] = ((.469471734868729*(gk[21][2]*s22))+((gk[21][1]*c22)-(
      .882947501360837*(gk[21][0]*s22))));
    gk[22][2] = ((Cik[22][2][2]*gk[21][2])+((Cik[22][0][2]*gk[21][0])-(
      .469471734868729*(gk[21][1]*s22))));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[6][0][0] = ((Cik[3][0][0]*c6)+(Cik[3][0][1]*s6));
    cnk[6][0][1] = ((Cik[3][0][1]*c6)-(Cik[3][0][0]*s6));
    cnk[6][1][0] = ((Cik[3][1][0]*c6)+(Cik[3][1][1]*s6));
    cnk[6][1][1] = ((Cik[3][1][1]*c6)-(Cik[3][1][0]*s6));
    cnk[6][2][0] = ((Cik[3][2][0]*c6)+(Cik[3][2][1]*s6));
    cnk[6][2][1] = ((Cik[3][2][1]*c6)-(Cik[3][2][0]*s6));
    cnk[7][0][1] = ((Cik[3][0][2]*s7)+(cnk[6][0][1]*c7));
    cnk[7][0][2] = ((Cik[3][0][2]*c7)-(cnk[6][0][1]*s7));
    cnk[7][1][1] = ((Cik[3][1][2]*s7)+(cnk[6][1][1]*c7));
    cnk[7][1][2] = ((Cik[3][1][2]*c7)-(cnk[6][1][1]*s7));
    cnk[7][2][1] = ((Cik[3][2][2]*s7)+(cnk[6][2][1]*c7));
    cnk[7][2][2] = ((Cik[3][2][2]*c7)-(cnk[6][2][1]*s7));
    cnk[8][0][0] = ((cnk[6][0][0]*c8)-(cnk[7][0][2]*s8));
    cnk[8][0][2] = ((cnk[6][0][0]*s8)+(cnk[7][0][2]*c8));
    cnk[8][1][0] = ((cnk[6][1][0]*c8)-(cnk[7][1][2]*s8));
    cnk[8][1][2] = ((cnk[6][1][0]*s8)+(cnk[7][1][2]*c8));
    cnk[8][2][0] = ((cnk[6][2][0]*c8)-(cnk[7][2][2]*s8));
    cnk[8][2][2] = ((cnk[6][2][0]*s8)+(cnk[7][2][2]*c8));
    cnk[9][0][0] = ((Cik[3][0][0]*c9)+(Cik[3][0][1]*s9));
    cnk[9][0][1] = ((Cik[3][0][1]*c9)-(Cik[3][0][0]*s9));
    cnk[9][1][0] = ((Cik[3][1][0]*c9)+(Cik[3][1][1]*s9));
    cnk[9][1][1] = ((Cik[3][1][1]*c9)-(Cik[3][1][0]*s9));
    cnk[9][2][0] = ((Cik[3][2][0]*c9)+(Cik[3][2][1]*s9));
    cnk[9][2][1] = ((Cik[3][2][1]*c9)-(Cik[3][2][0]*s9));
    cnk[10][0][1] = ((Cik[3][0][2]*s10)+(cnk[9][0][1]*c10));
    cnk[10][0][2] = ((Cik[3][0][2]*c10)-(cnk[9][0][1]*s10));
    cnk[10][1][1] = ((Cik[3][1][2]*s10)+(cnk[9][1][1]*c10));
    cnk[10][1][2] = ((Cik[3][1][2]*c10)-(cnk[9][1][1]*s10));
    cnk[10][2][1] = ((Cik[3][2][2]*s10)+(cnk[9][2][1]*c10));
    cnk[10][2][2] = ((Cik[3][2][2]*c10)-(cnk[9][2][1]*s10));
    cnk[11][0][0] = ((cnk[9][0][0]*c11)-(cnk[10][0][2]*s11));
    cnk[11][0][2] = ((cnk[9][0][0]*s11)+(cnk[10][0][2]*c11));
    cnk[11][1][0] = ((cnk[9][1][0]*c11)-(cnk[10][1][2]*s11));
    cnk[11][1][2] = ((cnk[9][1][0]*s11)+(cnk[10][1][2]*c11));
    cnk[11][2][0] = ((cnk[9][2][0]*c11)-(cnk[10][2][2]*s11));
    cnk[11][2][2] = ((cnk[9][2][0]*s11)+(cnk[10][2][2]*c11));
    cnk[12][0][0] = ((Cik[12][2][0]*cnk[11][0][2])+((Cik[12][0][0]*cnk[11][0][0]
      )+(Cik[12][1][0]*cnk[10][0][1])));
    cnk[12][0][1] = ((Cik[12][2][1]*cnk[11][0][2])+((Cik[12][0][1]*cnk[11][0][0]
      )+(Cik[12][1][1]*cnk[10][0][1])));
    cnk[12][0][2] = ((Cik[12][2][2]*cnk[11][0][2])+((Cik[12][0][2]*cnk[11][0][0]
      )+(Cik[12][1][2]*cnk[10][0][1])));
    cnk[12][1][0] = ((Cik[12][2][0]*cnk[11][1][2])+((Cik[12][0][0]*cnk[11][1][0]
      )+(Cik[12][1][0]*cnk[10][1][1])));
    cnk[12][1][1] = ((Cik[12][2][1]*cnk[11][1][2])+((Cik[12][0][1]*cnk[11][1][0]
      )+(Cik[12][1][1]*cnk[10][1][1])));
    cnk[12][1][2] = ((Cik[12][2][2]*cnk[11][1][2])+((Cik[12][0][2]*cnk[11][1][0]
      )+(Cik[12][1][2]*cnk[10][1][1])));
    cnk[12][2][0] = ((Cik[12][2][0]*cnk[11][2][2])+((Cik[12][0][0]*cnk[11][2][0]
      )+(Cik[12][1][0]*cnk[10][2][1])));
    cnk[12][2][1] = ((Cik[12][2][1]*cnk[11][2][2])+((Cik[12][0][1]*cnk[11][2][0]
      )+(Cik[12][1][1]*cnk[10][2][1])));
    cnk[12][2][2] = ((Cik[12][2][2]*cnk[11][2][2])+((Cik[12][0][2]*cnk[11][2][0]
      )+(Cik[12][1][2]*cnk[10][2][1])));
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
    cnk[15][0][0] = ((Cik[15][2][0]*cnk[14][0][2])+((.882947501360837*(
      cnk[14][0][1]*s15))+(Cik[15][0][0]*cnk[14][0][0])));
    cnk[15][0][1] = (((cnk[14][0][1]*c15)-(.882947501360837*(cnk[14][0][0]*s15))
      )-(.469471734868729*(cnk[14][0][2]*s15)));
    cnk[15][0][2] = ((Cik[15][2][2]*cnk[14][0][2])+((.469471734868729*(
      cnk[14][0][1]*s15))+(Cik[15][0][2]*cnk[14][0][0])));
    cnk[15][1][0] = ((Cik[15][2][0]*cnk[14][1][2])+((.882947501360837*(
      cnk[14][1][1]*s15))+(Cik[15][0][0]*cnk[14][1][0])));
    cnk[15][1][1] = (((cnk[14][1][1]*c15)-(.882947501360837*(cnk[14][1][0]*s15))
      )-(.469471734868729*(cnk[14][1][2]*s15)));
    cnk[15][1][2] = ((Cik[15][2][2]*cnk[14][1][2])+((.469471734868729*(
      cnk[14][1][1]*s15))+(Cik[15][0][2]*cnk[14][1][0])));
    cnk[15][2][0] = ((Cik[15][2][0]*cnk[14][2][2])+((.882947501360837*(
      cnk[14][2][1]*s15))+(Cik[15][0][0]*cnk[14][2][0])));
    cnk[15][2][1] = (((cnk[14][2][1]*c15)-(.882947501360837*(cnk[14][2][0]*s15))
      )-(.469471734868729*(cnk[14][2][2]*s15)));
    cnk[15][2][2] = ((Cik[15][2][2]*cnk[14][2][2])+((.469471734868729*(
      cnk[14][2][1]*s15))+(Cik[15][0][2]*cnk[14][2][0])));
    cnk[16][0][0] = ((Cik[3][0][0]*c16)+(Cik[3][0][1]*s16));
    cnk[16][0][1] = ((Cik[3][0][1]*c16)-(Cik[3][0][0]*s16));
    cnk[16][1][0] = ((Cik[3][1][0]*c16)+(Cik[3][1][1]*s16));
    cnk[16][1][1] = ((Cik[3][1][1]*c16)-(Cik[3][1][0]*s16));
    cnk[16][2][0] = ((Cik[3][2][0]*c16)+(Cik[3][2][1]*s16));
    cnk[16][2][1] = ((Cik[3][2][1]*c16)-(Cik[3][2][0]*s16));
    cnk[17][0][1] = ((cnk[16][0][1]*c17)-(Cik[3][0][2]*s17));
    cnk[17][0][2] = ((Cik[3][0][2]*c17)+(cnk[16][0][1]*s17));
    cnk[17][1][1] = ((cnk[16][1][1]*c17)-(Cik[3][1][2]*s17));
    cnk[17][1][2] = ((Cik[3][1][2]*c17)+(cnk[16][1][1]*s17));
    cnk[17][2][1] = ((cnk[16][2][1]*c17)-(Cik[3][2][2]*s17));
    cnk[17][2][2] = ((Cik[3][2][2]*c17)+(cnk[16][2][1]*s17));
    cnk[18][0][0] = ((cnk[16][0][0]*c18)+(cnk[17][0][2]*s18));
    cnk[18][0][2] = ((cnk[17][0][2]*c18)-(cnk[16][0][0]*s18));
    cnk[18][1][0] = ((cnk[16][1][0]*c18)+(cnk[17][1][2]*s18));
    cnk[18][1][2] = ((cnk[17][1][2]*c18)-(cnk[16][1][0]*s18));
    cnk[18][2][0] = ((cnk[16][2][0]*c18)+(cnk[17][2][2]*s18));
    cnk[18][2][2] = ((cnk[17][2][2]*c18)-(cnk[16][2][0]*s18));
    cnk[19][0][0] = ((Cik[19][2][0]*cnk[18][0][2])+((Cik[19][0][0]*cnk[18][0][0]
      )+(Cik[19][1][0]*cnk[17][0][1])));
    cnk[19][0][1] = ((Cik[19][2][1]*cnk[18][0][2])+((Cik[19][0][1]*cnk[18][0][0]
      )+(Cik[19][1][1]*cnk[17][0][1])));
    cnk[19][0][2] = ((Cik[19][2][2]*cnk[18][0][2])+((Cik[19][0][2]*cnk[18][0][0]
      )+(Cik[19][1][2]*cnk[17][0][1])));
    cnk[19][1][0] = ((Cik[19][2][0]*cnk[18][1][2])+((Cik[19][0][0]*cnk[18][1][0]
      )+(Cik[19][1][0]*cnk[17][1][1])));
    cnk[19][1][1] = ((Cik[19][2][1]*cnk[18][1][2])+((Cik[19][0][1]*cnk[18][1][0]
      )+(Cik[19][1][1]*cnk[17][1][1])));
    cnk[19][1][2] = ((Cik[19][2][2]*cnk[18][1][2])+((Cik[19][0][2]*cnk[18][1][0]
      )+(Cik[19][1][2]*cnk[17][1][1])));
    cnk[19][2][0] = ((Cik[19][2][0]*cnk[18][2][2])+((Cik[19][0][0]*cnk[18][2][0]
      )+(Cik[19][1][0]*cnk[17][2][1])));
    cnk[19][2][1] = ((Cik[19][2][1]*cnk[18][2][2])+((Cik[19][0][1]*cnk[18][2][0]
      )+(Cik[19][1][1]*cnk[17][2][1])));
    cnk[19][2][2] = ((Cik[19][2][2]*cnk[18][2][2])+((Cik[19][0][2]*cnk[18][2][0]
      )+(Cik[19][1][2]*cnk[17][2][1])));
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
    cnk[22][0][0] = ((Cik[22][2][0]*cnk[21][0][2])+((.882947501360837*(
      cnk[21][0][1]*s22))+(Cik[22][0][0]*cnk[21][0][0])));
    cnk[22][0][1] = ((.469471734868729*(cnk[21][0][2]*s22))+((cnk[21][0][1]*c22)
      -(.882947501360837*(cnk[21][0][0]*s22))));
    cnk[22][0][2] = ((Cik[22][2][2]*cnk[21][0][2])+((Cik[22][0][2]*cnk[21][0][0]
      )-(.469471734868729*(cnk[21][0][1]*s22))));
    cnk[22][1][0] = ((Cik[22][2][0]*cnk[21][1][2])+((.882947501360837*(
      cnk[21][1][1]*s22))+(Cik[22][0][0]*cnk[21][1][0])));
    cnk[22][1][1] = ((.469471734868729*(cnk[21][1][2]*s22))+((cnk[21][1][1]*c22)
      -(.882947501360837*(cnk[21][1][0]*s22))));
    cnk[22][1][2] = ((Cik[22][2][2]*cnk[21][1][2])+((Cik[22][0][2]*cnk[21][1][0]
      )-(.469471734868729*(cnk[21][1][1]*s22))));
    cnk[22][2][0] = ((Cik[22][2][0]*cnk[21][2][2])+((.882947501360837*(
      cnk[21][2][1]*s22))+(Cik[22][0][0]*cnk[21][2][0])));
    cnk[22][2][1] = ((.469471734868729*(cnk[21][2][2]*s22))+((cnk[21][2][1]*c22)
      -(.882947501360837*(cnk[21][2][0]*s22))));
    cnk[22][2][2] = ((Cik[22][2][2]*cnk[21][2][2])+((Cik[22][0][2]*cnk[21][2][0]
      )-(.469471734868729*(cnk[21][2][1]*s22))));
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
    cnb[1][0][1] = cnk[7][0][1];
    cnb[1][0][2] = cnk[8][0][2];
    cnb[1][1][0] = cnk[8][1][0];
    cnb[1][1][1] = cnk[7][1][1];
    cnb[1][1][2] = cnk[8][1][2];
    cnb[1][2][0] = cnk[8][2][0];
    cnb[1][2][1] = cnk[7][2][1];
    cnb[1][2][2] = cnk[8][2][2];
    cnb[2][0][0] = cnk[11][0][0];
    cnb[2][0][1] = cnk[10][0][1];
    cnb[2][0][2] = cnk[11][0][2];
    cnb[2][1][0] = cnk[11][1][0];
    cnb[2][1][1] = cnk[10][1][1];
    cnb[2][1][2] = cnk[11][1][2];
    cnb[2][2][0] = cnk[11][2][0];
    cnb[2][2][1] = cnk[10][2][1];
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
    cnb[4][0][0] = cnk[14][0][0];
    cnb[4][0][1] = cnk[14][0][1];
    cnb[4][0][2] = cnk[14][0][2];
    cnb[4][1][0] = cnk[14][1][0];
    cnb[4][1][1] = cnk[14][1][1];
    cnb[4][1][2] = cnk[14][1][2];
    cnb[4][2][0] = cnk[14][2][0];
    cnb[4][2][1] = cnk[14][2][1];
    cnb[4][2][2] = cnk[14][2][2];
    cnb[5][0][0] = cnk[15][0][0];
    cnb[5][0][1] = cnk[15][0][1];
    cnb[5][0][2] = cnk[15][0][2];
    cnb[5][1][0] = cnk[15][1][0];
    cnb[5][1][1] = cnk[15][1][1];
    cnb[5][1][2] = cnk[15][1][2];
    cnb[5][2][0] = cnk[15][2][0];
    cnb[5][2][1] = cnk[15][2][1];
    cnb[5][2][2] = cnk[15][2][2];
    cnb[6][0][0] = cnk[18][0][0];
    cnb[6][0][1] = cnk[17][0][1];
    cnb[6][0][2] = cnk[18][0][2];
    cnb[6][1][0] = cnk[18][1][0];
    cnb[6][1][1] = cnk[17][1][1];
    cnb[6][1][2] = cnk[18][1][2];
    cnb[6][2][0] = cnk[18][2][0];
    cnb[6][2][1] = cnk[17][2][1];
    cnb[6][2][2] = cnk[18][2][2];
    cnb[7][0][0] = cnk[19][0][0];
    cnb[7][0][1] = cnk[19][0][1];
    cnb[7][0][2] = cnk[19][0][2];
    cnb[7][1][0] = cnk[19][1][0];
    cnb[7][1][1] = cnk[19][1][1];
    cnb[7][1][2] = cnk[19][1][2];
    cnb[7][2][0] = cnk[19][2][0];
    cnb[7][2][1] = cnk[19][2][1];
    cnb[7][2][2] = cnk[19][2][2];
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
/*
Compute q-related auxiliary variables
*/
    rik[12][0] = ((.0033*Cik[12][0][0])-(.2294*Cik[12][1][0]));
    rik[12][1] = (((.0033*Cik[12][0][1])-(.2294*Cik[12][1][1]))-.1862);
    rik[12][2] = ((.0033*Cik[12][0][2])-(.2294*Cik[12][1][2]));
    rik[15][0] = (.026917+((.018078*Cik[15][2][0])+((.098032*Cik[15][0][0])-(
      .0335520050517118*s15))));
    rik[15][1] = (.0185-((.00848711002295689*s15)+((.038*c15)+(.0865571094534056
      *s15))));
    rik[15][2] = (.005139+((.018078*Cik[15][2][2])+((.098032*Cik[15][0][2])-(
      .0178399259250117*s15))));
    rik[19][0] = ((.0033*Cik[19][0][0])-(.2294*Cik[19][1][0]));
    rik[19][1] = (((.0033*Cik[19][0][1])-(.2294*Cik[19][1][1]))-.1862);
    rik[19][2] = ((.0033*Cik[19][0][2])-(.2294*Cik[19][1][2]));
    rik[22][0] = (.026917+(((.098032*Cik[22][0][0])-(.0335520050517118*s22))-(
      .018078*Cik[22][2][0])));
    rik[22][1] = (.0185-((.00848711002295689*s22)+((.038*c22)+(.0865571094534056
      *s22))));
    rik[22][2] = ((((.0178399259250117*s22)+(.098032*Cik[22][0][2]))-(.018078*
      Cik[22][2][2]))-.005139);
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[6][0] = (q[0]+(.127*Cik[3][0][1]));
    rnk[6][1] = (q[1]+(.127*Cik[3][1][1]));
    rnk[6][2] = (q[2]+(.127*Cik[3][2][1]));
    rnk[8][0] = (rnk[6][0]+(.3202*cnk[7][0][1]));
    rnk[8][1] = (rnk[6][1]+(.3202*cnk[7][1][1]));
    rnk[8][2] = (rnk[6][2]+(.3202*cnk[7][2][1]));
    rnk[9][0] = (q[0]+((.0935*Cik[3][0][2])-(.07*Cik[3][0][1])));
    rnk[9][1] = (q[1]+((.0935*Cik[3][1][2])-(.07*Cik[3][1][1])));
    rnk[9][2] = (q[2]+((.0935*Cik[3][2][2])-(.07*Cik[3][2][1])));
    rnk[11][0] = (rnk[9][0]-((.002*cnk[11][0][0])+(.1715*cnk[10][0][1])));
    rnk[11][1] = (rnk[9][1]-((.002*cnk[11][1][0])+(.1715*cnk[10][1][1])));
    rnk[11][2] = (rnk[9][2]-((.002*cnk[11][2][0])+(.1715*cnk[10][2][1])));
    rnk[12][0] = ((rnk[11][0]+((.0033*cnk[11][0][0])-(.2294*cnk[10][0][1])))-(
      .1862*cnk[12][0][1]));
    rnk[12][1] = ((rnk[11][1]+((.0033*cnk[11][1][0])-(.2294*cnk[10][1][1])))-(
      .1862*cnk[12][1][1]));
    rnk[12][2] = ((rnk[11][2]+((.0033*cnk[11][2][0])-(.2294*cnk[10][2][1])))-(
      .1862*cnk[12][2][1]));
    rnk[13][0] = (rnk[12][0]-(.2438*cnk[12][0][1]));
    rnk[13][1] = (rnk[12][1]-(.2438*cnk[12][1][1]));
    rnk[13][2] = (rnk[12][2]-(.2438*cnk[12][2][1]));
    rnk[14][0] = (rnk[13][0]+((.005539*cnk[14][0][2])+((.035902*cnk[14][0][0])-(
      .051347*cnk[14][0][1]))));
    rnk[14][1] = (rnk[13][1]+((.005539*cnk[14][1][2])+((.035902*cnk[14][1][0])-(
      .051347*cnk[14][1][1]))));
    rnk[14][2] = (rnk[13][2]+((.005539*cnk[14][2][2])+((.035902*cnk[14][2][0])-(
      .051347*cnk[14][2][1]))));
    rnk[15][0] = ((rnk[14][0]+((.018078*cnk[14][0][2])+((.098032*cnk[14][0][0])-
      (.038*cnk[14][0][1]))))+((.005139*cnk[15][0][2])+((.0185*cnk[15][0][1])+(
      .026917*cnk[15][0][0]))));
    rnk[15][1] = ((rnk[14][1]+((.018078*cnk[14][1][2])+((.098032*cnk[14][1][0])-
      (.038*cnk[14][1][1]))))+((.005139*cnk[15][1][2])+((.0185*cnk[15][1][1])+(
      .026917*cnk[15][1][0]))));
    rnk[15][2] = ((rnk[14][2]+((.018078*cnk[14][2][2])+((.098032*cnk[14][2][0])-
      (.038*cnk[14][2][1]))))+((.005139*cnk[15][2][2])+((.0185*cnk[15][2][1])+(
      .026917*cnk[15][2][0]))));
    rnk[16][0] = (q[0]-((.07*Cik[3][0][1])+(.0935*Cik[3][0][2])));
    rnk[16][1] = (q[1]-((.07*Cik[3][1][1])+(.0935*Cik[3][1][2])));
    rnk[16][2] = (q[2]-((.07*Cik[3][2][1])+(.0935*Cik[3][2][2])));
    rnk[18][0] = (rnk[16][0]-((.002*cnk[18][0][0])+(.1715*cnk[17][0][1])));
    rnk[18][1] = (rnk[16][1]-((.002*cnk[18][1][0])+(.1715*cnk[17][1][1])));
    rnk[18][2] = (rnk[16][2]-((.002*cnk[18][2][0])+(.1715*cnk[17][2][1])));
    rnk[19][0] = ((rnk[18][0]+((.0033*cnk[18][0][0])-(.2294*cnk[17][0][1])))-(
      .1862*cnk[19][0][1]));
    rnk[19][1] = ((rnk[18][1]+((.0033*cnk[18][1][0])-(.2294*cnk[17][1][1])))-(
      .1862*cnk[19][1][1]));
    rnk[19][2] = ((rnk[18][2]+((.0033*cnk[18][2][0])-(.2294*cnk[17][2][1])))-(
      .1862*cnk[19][2][1]));
    rnk[20][0] = (rnk[19][0]-(.2438*cnk[19][0][1]));
    rnk[20][1] = (rnk[19][1]-(.2438*cnk[19][1][1]));
    rnk[20][2] = (rnk[19][2]-(.2438*cnk[19][2][1]));
    rnk[21][0] = (rnk[20][0]+(((.035902*cnk[21][0][0])-(.051347*cnk[21][0][1]))-
      (.005539*cnk[21][0][2])));
    rnk[21][1] = (rnk[20][1]+(((.035902*cnk[21][1][0])-(.051347*cnk[21][1][1]))-
      (.005539*cnk[21][1][2])));
    rnk[21][2] = (rnk[20][2]+(((.035902*cnk[21][2][0])-(.051347*cnk[21][2][1]))-
      (.005539*cnk[21][2][2])));
    rnk[22][0] = ((rnk[21][0]+(((.098032*cnk[21][0][0])-(.038*cnk[21][0][1]))-(
      .018078*cnk[21][0][2])))+(((.0185*cnk[22][0][1])+(.026917*cnk[22][0][0]))-
      (.005139*cnk[22][0][2])));
    rnk[22][1] = ((rnk[21][1]+(((.098032*cnk[21][1][0])-(.038*cnk[21][1][1]))-(
      .018078*cnk[21][1][2])))+(((.0185*cnk[22][1][1])+(.026917*cnk[22][1][0]))-
      (.005139*cnk[22][1][2])));
    rnk[22][2] = ((rnk[21][2]+(((.098032*cnk[21][2][0])-(.038*cnk[21][2][1]))-(
      .018078*cnk[21][2][2])))+(((.0185*cnk[22][2][1])+(.026917*cnk[22][2][0]))-
      (.005139*cnk[22][2][2])));
    rnb[0][0] = q[0];
    rnb[0][1] = q[1];
    rnb[0][2] = q[2];
    rnb[1][0] = rnk[8][0];
    rnb[1][1] = rnk[8][1];
    rnb[1][2] = rnk[8][2];
    rnb[2][0] = rnk[11][0];
    rnb[2][1] = rnk[11][1];
    rnb[2][2] = rnk[11][2];
    rnb[3][0] = rnk[12][0];
    rnb[3][1] = rnk[12][1];
    rnb[3][2] = rnk[12][2];
    rnb[4][0] = rnk[14][0];
    rnb[4][1] = rnk[14][1];
    rnb[4][2] = rnk[14][2];
    rnb[5][0] = rnk[15][0];
    rnb[5][1] = rnk[15][1];
    rnb[5][2] = rnk[15][2];
    rnb[6][0] = rnk[18][0];
    rnb[6][1] = rnk[18][1];
    rnb[6][2] = rnk[18][2];
    rnb[7][0] = rnk[19][0];
    rnb[7][1] = rnk[19][1];
    rnb[7][2] = rnk[19][2];
    rnb[8][0] = rnk[21][0];
    rnb[8][1] = rnk[21][1];
    rnb[8][2] = rnk[21][2];
    rnb[9][0] = rnk[22][0];
    rnb[9][1] = rnk[22][1];
    rnb[9][2] = rnk[22][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = (.0140834652625414*((.205126*rnk[22][0])+((1.2*rnk[21][0])+((3.51*
      rnk[19][0])+((8.806*rnk[18][0])+((.205126*rnk[15][0])+((1.2*rnk[14][0])+((
      3.51*rnk[12][0])+((8.806*rnk[11][0])+((11.15*q[0])+(32.413*rnk[8][0]))))))
      )))));
    com[1] = (.0140834652625414*((.205126*rnk[22][1])+((1.2*rnk[21][1])+((3.51*
      rnk[19][1])+((8.806*rnk[18][1])+((.205126*rnk[15][1])+((1.2*rnk[14][1])+((
      3.51*rnk[12][1])+((8.806*rnk[11][1])+((11.15*q[1])+(32.413*rnk[8][1]))))))
      )))));
    com[2] = (.0140834652625414*((.205126*rnk[22][2])+((1.2*rnk[21][2])+((3.51*
      rnk[19][2])+((8.806*rnk[18][2])+((.205126*rnk[15][2])+((1.2*rnk[14][2])+((
      3.51*rnk[12][2])+((8.806*rnk[11][2])+((11.15*q[2])+(32.413*rnk[8][2]))))))
      )))));
    skipqs: ;
/*
Check for locked gimbal tree joint
*/
    if ((fabs((fabs(((Cik[3][2][2]*cnk[7][2][1])+((Cik[3][0][2]*cnk[7][0][1])+(
      Cik[3][1][2]*cnk[7][1][1]))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((Cik[3][2][2]*cnk[10][2][1])+((Cik[3][0][2]*cnk[10][0][1])+
      (Cik[3][1][2]*cnk[10][1][1]))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(-((Cik[3][2][2]*cnk[17][2][1])+((Cik[3][0][2]*cnk[17][0][1])
      +(Cik[3][1][2]*cnk[17][1][1]))))-1.)) <= .00380530190825445)  ) {
        sdseterr(8,43);
    }
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 23; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[6][0] = ((u[3]*c6)+(u[4]*s6));
    wk[6][1] = ((u[4]*c6)-(u[3]*s6));
    wk[6][2] = (u[5]+u[6]);
    wk[7][0] = (u[7]+wk[6][0]);
    wk[7][1] = ((wk[6][1]*c7)+(wk[6][2]*s7));
    wk[7][2] = ((wk[6][2]*c7)-(wk[6][1]*s7));
    wk[8][0] = ((wk[7][0]*c8)-(wk[7][2]*s8));
    wk[8][1] = (u[8]+wk[7][1]);
    wk[8][2] = ((wk[7][0]*s8)+(wk[7][2]*c8));
    wk[9][0] = ((u[3]*c9)+(u[4]*s9));
    wk[9][1] = ((u[4]*c9)-(u[3]*s9));
    wk[9][2] = (u[5]+u[9]);
    wk[10][0] = (u[10]+wk[9][0]);
    wk[10][1] = ((wk[9][1]*c10)+(wk[9][2]*s10));
    wk[10][2] = ((wk[9][2]*c10)-(wk[9][1]*s10));
    wk[11][0] = ((wk[10][0]*c11)-(wk[10][2]*s11));
    wk[11][1] = (u[11]+wk[10][1]);
    wk[11][2] = ((wk[10][0]*s11)+(wk[10][2]*c11));
    wk[12][0] = (((Cik[12][2][0]*wk[11][2])+((Cik[12][0][0]*wk[11][0])+(
      Cik[12][1][0]*wk[11][1])))-(.0809090128117004*u[12]));
    wk[12][1] = ((.0404550064059294*u[12])+((Cik[12][2][1]*wk[11][2])+((
      Cik[12][0][1]*wk[11][0])+(Cik[12][1][1]*wk[11][1]))));
    wk[12][2] = ((.995900157697815*u[12])+((Cik[12][2][2]*wk[11][2])+((
      Cik[12][0][2]*wk[11][0])+(Cik[12][1][2]*wk[11][1]))));
    wk[13][0] = (((Cik[13][2][0]*wk[12][2])+((Cik[13][0][0]*wk[12][0])+(
      Cik[13][1][0]*wk[12][1])))-(.0821860132171146*u[13]));
    wk[13][1] = (((Cik[13][2][1]*wk[12][2])+((Cik[13][0][1]*wk[12][0])+(
      Cik[13][1][1]*wk[12][1])))-(.0372090059839342*u[13]));
    wk[13][2] = ((.995922160163717*u[13])+((Cik[13][2][2]*wk[12][2])+((
      Cik[13][0][2]*wk[12][0])+(Cik[13][1][2]*wk[12][1]))));
    wk[14][0] = ((.814755846133373*u[14])+((Cik[14][2][0]*wk[13][2])+((
      Cik[14][0][0]*wk[13][0])+(Cik[14][1][0]*wk[13][1]))));
    wk[14][1] = ((.57725989098448*u[14])+((Cik[14][2][1]*wk[13][2])+((
      Cik[14][0][1]*wk[13][0])+(Cik[14][1][1]*wk[13][1]))));
    wk[14][2] = (((Cik[14][2][2]*wk[13][2])+((Cik[14][0][2]*wk[13][0])+(
      Cik[14][1][2]*wk[13][1])))-(.0542579897533796*u[14]));
    wk[15][0] = (((Cik[15][2][0]*wk[14][2])+((.882947501360837*(wk[14][1]*s15))+
      (Cik[15][0][0]*wk[14][0])))-(.469471734868729*u[15]));
    wk[15][1] = (((wk[14][1]*c15)-(.882947501360837*(wk[14][0]*s15)))-(
      .469471734868729*(wk[14][2]*s15)));
    wk[15][2] = ((.882947501360837*u[15])+((Cik[15][2][2]*wk[14][2])+((
      .469471734868729*(wk[14][1]*s15))+(Cik[15][0][2]*wk[14][0]))));
    wk[16][0] = ((u[3]*c16)+(u[4]*s16));
    wk[16][1] = ((u[4]*c16)-(u[3]*s16));
    wk[16][2] = (u[5]+u[16]);
    wk[17][0] = (wk[16][0]-u[17]);
    wk[17][1] = ((wk[16][1]*c17)-(wk[16][2]*s17));
    wk[17][2] = ((wk[16][1]*s17)+(wk[16][2]*c17));
    wk[18][0] = ((wk[17][0]*c18)+(wk[17][2]*s18));
    wk[18][1] = (wk[17][1]-u[18]);
    wk[18][2] = ((wk[17][2]*c18)-(wk[17][0]*s18));
    wk[19][0] = ((.0809090128117004*u[19])+((Cik[19][2][0]*wk[18][2])+((
      Cik[19][0][0]*wk[18][0])+(Cik[19][1][0]*wk[18][1]))));
    wk[19][1] = (((Cik[19][2][1]*wk[18][2])+((Cik[19][0][1]*wk[18][0])+(
      Cik[19][1][1]*wk[18][1])))-(.0404550064059294*u[19]));
    wk[19][2] = ((.995900157697815*u[19])+((Cik[19][2][2]*wk[18][2])+((
      Cik[19][0][2]*wk[18][0])+(Cik[19][1][2]*wk[18][1]))));
    wk[20][0] = ((.0821860132171146*u[20])+((Cik[20][2][0]*wk[19][2])+((
      Cik[20][0][0]*wk[19][0])+(Cik[20][1][0]*wk[19][1]))));
    wk[20][1] = ((.0372090059839342*u[20])+((Cik[20][2][1]*wk[19][2])+((
      Cik[20][0][1]*wk[19][0])+(Cik[20][1][1]*wk[19][1]))));
    wk[20][2] = ((.995922160163717*u[20])+((Cik[20][2][2]*wk[19][2])+((
      Cik[20][0][2]*wk[19][0])+(Cik[20][1][2]*wk[19][1]))));
    wk[21][0] = (((Cik[21][2][0]*wk[20][2])+((Cik[21][0][0]*wk[20][0])+(
      Cik[21][1][0]*wk[20][1])))-(.814755846133373*u[21]));
    wk[21][1] = (((Cik[21][2][1]*wk[20][2])+((Cik[21][0][1]*wk[20][0])+(
      Cik[21][1][1]*wk[20][1])))-(.57725989098448*u[21]));
    wk[21][2] = (((Cik[21][2][2]*wk[20][2])+((Cik[21][0][2]*wk[20][0])+(
      Cik[21][1][2]*wk[20][1])))-(.0542579897533796*u[21]));
    wk[22][0] = ((.469471734868729*u[22])+((Cik[22][2][0]*wk[21][2])+((
      .882947501360837*(wk[21][1]*s22))+(Cik[22][0][0]*wk[21][0]))));
    wk[22][1] = ((.469471734868729*(wk[21][2]*s22))+((wk[21][1]*c22)-(
      .882947501360837*(wk[21][0]*s22))));
    wk[22][2] = ((.882947501360837*u[22])+((Cik[22][2][2]*wk[21][2])+((
      Cik[22][0][2]*wk[21][0])-(.469471734868729*(wk[21][1]*s22)))));
    wb[0][0] = u[3];
    wb[0][1] = u[4];
    wb[0][2] = u[5];
    wb[1][0] = wk[8][0];
    wb[1][1] = wk[8][1];
    wb[1][2] = wk[8][2];
    wb[2][0] = wk[11][0];
    wb[2][1] = wk[11][1];
    wb[2][2] = wk[11][2];
    wb[3][0] = wk[12][0];
    wb[3][1] = wk[12][1];
    wb[3][2] = wk[12][2];
    wb[4][0] = wk[14][0];
    wb[4][1] = wk[14][1];
    wb[4][2] = wk[14][2];
    wb[5][0] = wk[15][0];
    wb[5][1] = wk[15][1];
    wb[5][2] = wk[15][2];
    wb[6][0] = wk[18][0];
    wb[6][1] = wk[18][1];
    wb[6][2] = wk[18][2];
    wb[7][0] = wk[19][0];
    wb[7][1] = wk[19][1];
    wb[7][2] = wk[19][2];
    wb[8][0] = wk[21][0];
    wb[8][1] = wk[21][1];
    wb[8][2] = wk[21][2];
    wb[9][0] = wk[22][0];
    wb[9][1] = wk[22][1];
    wb[9][2] = wk[22][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[9][0] = ((.07*u[5])+(.0935*u[4]));
    Wirk[12][2] = -((.0033*wk[11][1])+(.2294*wk[11][0]));
    Wirk[15][0] = ((.018078*wk[14][1])+(.038*wk[14][2]));
    Wirk[15][1] = ((.098032*wk[14][2])-(.018078*wk[14][0]));
    Wirk[15][2] = -((.038*wk[14][0])+(.098032*wk[14][1]));
    Wirk[16][0] = ((.07*u[5])-(.0935*u[4]));
    Wirk[19][2] = -((.0033*wk[18][1])+(.2294*wk[18][0]));
    Wirk[22][0] = ((.038*wk[21][2])-(.018078*wk[21][1]));
    Wirk[22][1] = ((.018078*wk[21][0])+(.098032*wk[21][2]));
    Wirk[22][2] = -((.038*wk[21][0])+(.098032*wk[21][1]));
    Wkrpk[11][2] = ((.002*wk[11][1])-(.1715*wk[11][0]));
    Wkrpk[14][0] = ((.005539*wk[14][1])+(.051347*wk[14][2]));
    Wkrpk[14][1] = ((.035902*wk[14][2])-(.005539*wk[14][0]));
    Wkrpk[14][2] = -((.035902*wk[14][1])+(.051347*wk[14][0]));
    Wkrpk[15][0] = ((.005139*wk[15][1])-(.0185*wk[15][2]));
    Wkrpk[15][1] = ((.026917*wk[15][2])-(.005139*wk[15][0]));
    Wkrpk[15][2] = ((.0185*wk[15][0])-(.026917*wk[15][1]));
    Wkrpk[18][2] = ((.002*wk[18][1])-(.1715*wk[18][0]));
    Wkrpk[21][0] = ((.051347*wk[21][2])-(.005539*wk[21][1]));
    Wkrpk[21][1] = ((.005539*wk[21][0])+(.035902*wk[21][2]));
    Wkrpk[21][2] = -((.035902*wk[21][1])+(.051347*wk[21][0]));
    Wkrpk[22][0] = -((.005139*wk[22][1])+(.0185*wk[22][2]));
    Wkrpk[22][1] = ((.005139*wk[22][0])+(.026917*wk[22][2]));
    Wkrpk[22][2] = ((.0185*wk[22][0])-(.026917*wk[22][1]));
    WkIkWk[5][0] = -(.0277*(u[4]*u[5]));
    WkIkWk[5][1] = (.0425*(u[3]*u[5]));
    WkIkWk[5][2] = -(.0148*(u[3]*u[4]));
    WkIkWk[8][0] = (.6399*(wk[8][1]*wk[8][2]));
    WkIkWk[8][1] = (.0407999999999999*(wk[8][0]*wk[8][2]));
    WkIkWk[8][2] = -(.6807*(wk[8][0]*wk[8][1]));
    WkIkWk[11][0] = (.1005*(wk[11][1]*wk[11][2]));
    WkIkWk[11][1] = -(.00690000000000002*(wk[11][0]*wk[11][2]));
    WkIkWk[11][2] = -(.0936*(wk[11][0]*wk[11][1]));
    WkIkWk[12][0] = (.0436*(wk[12][1]*wk[12][2]));
    WkIkWk[12][1] = -(.000699999999999999*(wk[12][0]*wk[12][2]));
    WkIkWk[12][2] = -(.0429*(wk[12][0]*wk[12][1]));
    WkIkWk[14][0] = (.000207*(wk[14][1]*wk[14][2]));
    WkIkWk[14][1] = -(.002555*(wk[14][0]*wk[14][2]));
    WkIkWk[14][2] = (.002348*(wk[14][0]*wk[14][1]));
    WkIkWk[15][0] = -(6e-5*(wk[15][1]*wk[15][2]));
    WkIkWk[15][1] = -(2.00000000000001e-6*(wk[15][0]*wk[15][2]));
    WkIkWk[15][2] = (6.2e-5*(wk[15][0]*wk[15][1]));
    WkIkWk[18][0] = (.1005*(wk[18][1]*wk[18][2]));
    WkIkWk[18][1] = -(.00690000000000002*(wk[18][0]*wk[18][2]));
    WkIkWk[18][2] = -(.0936*(wk[18][0]*wk[18][1]));
    WkIkWk[19][0] = (.0436*(wk[19][1]*wk[19][2]));
    WkIkWk[19][1] = -(.000699999999999999*(wk[19][0]*wk[19][2]));
    WkIkWk[19][2] = -(.0429*(wk[19][0]*wk[19][1]));
    WkIkWk[21][0] = (.000207*(wk[21][1]*wk[21][2]));
    WkIkWk[21][1] = -(.002555*(wk[21][0]*wk[21][2]));
    WkIkWk[21][2] = (.002348*(wk[21][0]*wk[21][1]));
    WkIkWk[22][0] = -(6e-5*(wk[22][1]*wk[22][2]));
    WkIkWk[22][1] = -(2.00000000000001e-6*(wk[22][0]*wk[22][2]));
    WkIkWk[22][2] = (6.2e-5*(wk[22][0]*wk[22][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (u[3]*u[3]);
    w0w0[1] = (wk[8][0]*wk[8][0]);
    w0w0[2] = (wk[11][0]*wk[11][0]);
    w0w0[3] = (wk[12][0]*wk[12][0]);
    w0w0[4] = (wk[14][0]*wk[14][0]);
    w0w0[5] = (wk[15][0]*wk[15][0]);
    w0w0[6] = (wk[18][0]*wk[18][0]);
    w0w0[7] = (wk[19][0]*wk[19][0]);
    w0w0[8] = (wk[21][0]*wk[21][0]);
    w0w0[9] = (wk[22][0]*wk[22][0]);
    w1w1[0] = (u[4]*u[4]);
    w1w1[1] = (wk[8][1]*wk[8][1]);
    w1w1[2] = (wk[11][1]*wk[11][1]);
    w1w1[3] = (wk[12][1]*wk[12][1]);
    w1w1[4] = (wk[14][1]*wk[14][1]);
    w1w1[5] = (wk[15][1]*wk[15][1]);
    w1w1[6] = (wk[18][1]*wk[18][1]);
    w1w1[7] = (wk[19][1]*wk[19][1]);
    w1w1[8] = (wk[21][1]*wk[21][1]);
    w1w1[9] = (wk[22][1]*wk[22][1]);
    w2w2[0] = (u[5]*u[5]);
    w2w2[1] = (wk[8][2]*wk[8][2]);
    w2w2[2] = (wk[11][2]*wk[11][2]);
    w2w2[3] = (wk[12][2]*wk[12][2]);
    w2w2[4] = (wk[14][2]*wk[14][2]);
    w2w2[5] = (wk[15][2]*wk[15][2]);
    w2w2[6] = (wk[18][2]*wk[18][2]);
    w2w2[7] = (wk[19][2]*wk[19][2]);
    w2w2[8] = (wk[21][2]*wk[21][2]);
    w2w2[9] = (wk[22][2]*wk[22][2]);
    w0w1[0] = (u[3]*u[4]);
    w0w1[1] = (wk[8][0]*wk[8][1]);
    w0w1[2] = (wk[11][0]*wk[11][1]);
    w0w1[3] = (wk[12][0]*wk[12][1]);
    w0w1[4] = (wk[14][0]*wk[14][1]);
    w0w1[5] = (wk[15][0]*wk[15][1]);
    w0w1[6] = (wk[18][0]*wk[18][1]);
    w0w1[7] = (wk[19][0]*wk[19][1]);
    w0w1[8] = (wk[21][0]*wk[21][1]);
    w0w1[9] = (wk[22][0]*wk[22][1]);
    w0w2[0] = (u[3]*u[5]);
    w0w2[1] = (wk[8][0]*wk[8][2]);
    w0w2[2] = (wk[11][0]*wk[11][2]);
    w0w2[3] = (wk[12][0]*wk[12][2]);
    w0w2[4] = (wk[14][0]*wk[14][2]);
    w0w2[5] = (wk[15][0]*wk[15][2]);
    w0w2[6] = (wk[18][0]*wk[18][2]);
    w0w2[7] = (wk[19][0]*wk[19][2]);
    w0w2[8] = (wk[21][0]*wk[21][2]);
    w0w2[9] = (wk[22][0]*wk[22][2]);
    w1w2[0] = (u[4]*u[5]);
    w1w2[1] = (wk[8][1]*wk[8][2]);
    w1w2[2] = (wk[11][1]*wk[11][2]);
    w1w2[3] = (wk[12][1]*wk[12][2]);
    w1w2[4] = (wk[14][1]*wk[14][2]);
    w1w2[5] = (wk[15][1]*wk[15][2]);
    w1w2[6] = (wk[18][1]*wk[18][2]);
    w1w2[7] = (wk[19][1]*wk[19][2]);
    w1w2[8] = (wk[21][1]*wk[21][2]);
    w1w2[9] = (wk[22][1]*wk[22][2]);
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
    vnk[6][0] = (u[0]+(.127*((Cik[3][0][2]*u[3])-(Cik[3][0][0]*u[5]))));
    vnk[6][1] = (u[1]+(.127*((Cik[3][1][2]*u[3])-(Cik[3][1][0]*u[5]))));
    vnk[6][2] = (u[2]+(.127*((Cik[3][2][2]*u[3])-(Cik[3][2][0]*u[5]))));
    vnk[8][0] = (vnk[6][0]+(.3202*((cnk[8][0][2]*wk[8][0])-(cnk[8][0][0]*
      wk[8][2]))));
    vnk[8][1] = (vnk[6][1]+(.3202*((cnk[8][1][2]*wk[8][0])-(cnk[8][1][0]*
      wk[8][2]))));
    vnk[8][2] = (vnk[6][2]+(.3202*((cnk[8][2][2]*wk[8][0])-(cnk[8][2][0]*
      wk[8][2]))));
    vnk[9][0] = (u[0]+(((Cik[3][0][0]*Wirk[9][0])-(.0935*(Cik[3][0][1]*u[3])))-(
      .07*(Cik[3][0][2]*u[3]))));
    vnk[9][1] = (u[1]+(((Cik[3][1][0]*Wirk[9][0])-(.0935*(Cik[3][1][1]*u[3])))-(
      .07*(Cik[3][1][2]*u[3]))));
    vnk[9][2] = (u[2]+(((Cik[3][2][0]*Wirk[9][0])-(.0935*(Cik[3][2][1]*u[3])))-(
      .07*(Cik[3][2][2]*u[3]))));
    vnk[11][0] = (vnk[9][0]+((cnk[11][0][2]*Wkrpk[11][2])+((.1715*(cnk[11][0][0]
      *wk[11][2]))-(.002*(cnk[10][0][1]*wk[11][2])))));
    vnk[11][1] = (vnk[9][1]+((cnk[11][1][2]*Wkrpk[11][2])+((.1715*(cnk[11][1][0]
      *wk[11][2]))-(.002*(cnk[10][1][1]*wk[11][2])))));
    vnk[11][2] = (vnk[9][2]+((cnk[11][2][2]*Wkrpk[11][2])+((.1715*(cnk[11][2][0]
      *wk[11][2]))-(.002*(cnk[10][2][1]*wk[11][2])))));
    vnk[12][0] = ((.1862*((cnk[12][0][0]*wk[12][2])-(cnk[12][0][2]*wk[12][0])))+
      (vnk[11][0]+((cnk[11][0][2]*Wirk[12][2])+((.0033*(cnk[10][0][1]*wk[11][2])
      )+(.2294*(cnk[11][0][0]*wk[11][2]))))));
    vnk[12][1] = ((.1862*((cnk[12][1][0]*wk[12][2])-(cnk[12][1][2]*wk[12][0])))+
      (vnk[11][1]+((cnk[11][1][2]*Wirk[12][2])+((.0033*(cnk[10][1][1]*wk[11][2])
      )+(.2294*(cnk[11][1][0]*wk[11][2]))))));
    vnk[12][2] = ((.1862*((cnk[12][2][0]*wk[12][2])-(cnk[12][2][2]*wk[12][0])))+
      (vnk[11][2]+((cnk[11][2][2]*Wirk[12][2])+((.0033*(cnk[10][2][1]*wk[11][2])
      )+(.2294*(cnk[11][2][0]*wk[11][2]))))));
    vnk[13][0] = (vnk[12][0]+(.2438*((cnk[12][0][0]*wk[12][2])-(cnk[12][0][2]*
      wk[12][0]))));
    vnk[13][1] = (vnk[12][1]+(.2438*((cnk[12][1][0]*wk[12][2])-(cnk[12][1][2]*
      wk[12][0]))));
    vnk[13][2] = (vnk[12][2]+(.2438*((cnk[12][2][0]*wk[12][2])-(cnk[12][2][2]*
      wk[12][0]))));
    vnk[14][0] = (vnk[13][0]+((cnk[14][0][2]*Wkrpk[14][2])+((cnk[14][0][0]*
      Wkrpk[14][0])+(cnk[14][0][1]*Wkrpk[14][1]))));
    vnk[14][1] = (vnk[13][1]+((cnk[14][1][2]*Wkrpk[14][2])+((cnk[14][1][0]*
      Wkrpk[14][0])+(cnk[14][1][1]*Wkrpk[14][1]))));
    vnk[14][2] = (vnk[13][2]+((cnk[14][2][2]*Wkrpk[14][2])+((cnk[14][2][0]*
      Wkrpk[14][0])+(cnk[14][2][1]*Wkrpk[14][1]))));
    vnk[15][0] = ((vnk[14][0]+((cnk[14][0][2]*Wirk[15][2])+((cnk[14][0][0]*
      Wirk[15][0])+(cnk[14][0][1]*Wirk[15][1]))))+((cnk[15][0][2]*Wkrpk[15][2])+
      ((cnk[15][0][0]*Wkrpk[15][0])+(cnk[15][0][1]*Wkrpk[15][1]))));
    vnk[15][1] = ((vnk[14][1]+((cnk[14][1][2]*Wirk[15][2])+((cnk[14][1][0]*
      Wirk[15][0])+(cnk[14][1][1]*Wirk[15][1]))))+((cnk[15][1][2]*Wkrpk[15][2])+
      ((cnk[15][1][0]*Wkrpk[15][0])+(cnk[15][1][1]*Wkrpk[15][1]))));
    vnk[15][2] = ((vnk[14][2]+((cnk[14][2][2]*Wirk[15][2])+((cnk[14][2][0]*
      Wirk[15][0])+(cnk[14][2][1]*Wirk[15][1]))))+((cnk[15][2][2]*Wkrpk[15][2])+
      ((cnk[15][2][0]*Wkrpk[15][0])+(cnk[15][2][1]*Wkrpk[15][1]))));
    vnk[16][0] = (u[0]+(((.0935*(Cik[3][0][1]*u[3]))+(Cik[3][0][0]*Wirk[16][0]))
      -(.07*(Cik[3][0][2]*u[3]))));
    vnk[16][1] = (u[1]+(((.0935*(Cik[3][1][1]*u[3]))+(Cik[3][1][0]*Wirk[16][0]))
      -(.07*(Cik[3][1][2]*u[3]))));
    vnk[16][2] = (u[2]+(((.0935*(Cik[3][2][1]*u[3]))+(Cik[3][2][0]*Wirk[16][0]))
      -(.07*(Cik[3][2][2]*u[3]))));
    vnk[18][0] = (vnk[16][0]+((cnk[18][0][2]*Wkrpk[18][2])+((.1715*(
      cnk[18][0][0]*wk[18][2]))-(.002*(cnk[17][0][1]*wk[18][2])))));
    vnk[18][1] = (vnk[16][1]+((cnk[18][1][2]*Wkrpk[18][2])+((.1715*(
      cnk[18][1][0]*wk[18][2]))-(.002*(cnk[17][1][1]*wk[18][2])))));
    vnk[18][2] = (vnk[16][2]+((cnk[18][2][2]*Wkrpk[18][2])+((.1715*(
      cnk[18][2][0]*wk[18][2]))-(.002*(cnk[17][2][1]*wk[18][2])))));
    vnk[19][0] = ((.1862*((cnk[19][0][0]*wk[19][2])-(cnk[19][0][2]*wk[19][0])))+
      (vnk[18][0]+((cnk[18][0][2]*Wirk[19][2])+((.0033*(cnk[17][0][1]*wk[18][2])
      )+(.2294*(cnk[18][0][0]*wk[18][2]))))));
    vnk[19][1] = ((.1862*((cnk[19][1][0]*wk[19][2])-(cnk[19][1][2]*wk[19][0])))+
      (vnk[18][1]+((cnk[18][1][2]*Wirk[19][2])+((.0033*(cnk[17][1][1]*wk[18][2])
      )+(.2294*(cnk[18][1][0]*wk[18][2]))))));
    vnk[19][2] = ((.1862*((cnk[19][2][0]*wk[19][2])-(cnk[19][2][2]*wk[19][0])))+
      (vnk[18][2]+((cnk[18][2][2]*Wirk[19][2])+((.0033*(cnk[17][2][1]*wk[18][2])
      )+(.2294*(cnk[18][2][0]*wk[18][2]))))));
    vnk[20][0] = (vnk[19][0]+(.2438*((cnk[19][0][0]*wk[19][2])-(cnk[19][0][2]*
      wk[19][0]))));
    vnk[20][1] = (vnk[19][1]+(.2438*((cnk[19][1][0]*wk[19][2])-(cnk[19][1][2]*
      wk[19][0]))));
    vnk[20][2] = (vnk[19][2]+(.2438*((cnk[19][2][0]*wk[19][2])-(cnk[19][2][2]*
      wk[19][0]))));
    vnk[21][0] = (vnk[20][0]+((cnk[21][0][2]*Wkrpk[21][2])+((cnk[21][0][0]*
      Wkrpk[21][0])+(cnk[21][0][1]*Wkrpk[21][1]))));
    vnk[21][1] = (vnk[20][1]+((cnk[21][1][2]*Wkrpk[21][2])+((cnk[21][1][0]*
      Wkrpk[21][0])+(cnk[21][1][1]*Wkrpk[21][1]))));
    vnk[21][2] = (vnk[20][2]+((cnk[21][2][2]*Wkrpk[21][2])+((cnk[21][2][0]*
      Wkrpk[21][0])+(cnk[21][2][1]*Wkrpk[21][1]))));
    vnk[22][0] = ((vnk[21][0]+((cnk[21][0][2]*Wirk[22][2])+((cnk[21][0][0]*
      Wirk[22][0])+(cnk[21][0][1]*Wirk[22][1]))))+((cnk[22][0][2]*Wkrpk[22][2])+
      ((cnk[22][0][0]*Wkrpk[22][0])+(cnk[22][0][1]*Wkrpk[22][1]))));
    vnk[22][1] = ((vnk[21][1]+((cnk[21][1][2]*Wirk[22][2])+((cnk[21][1][0]*
      Wirk[22][0])+(cnk[21][1][1]*Wirk[22][1]))))+((cnk[22][1][2]*Wkrpk[22][2])+
      ((cnk[22][1][0]*Wkrpk[22][0])+(cnk[22][1][1]*Wkrpk[22][1]))));
    vnk[22][2] = ((vnk[21][2]+((cnk[21][2][2]*Wirk[22][2])+((cnk[21][2][0]*
      Wirk[22][0])+(cnk[21][2][1]*Wirk[22][1]))))+((cnk[22][2][2]*Wkrpk[22][2])+
      ((cnk[22][2][0]*Wkrpk[22][0])+(cnk[22][2][1]*Wkrpk[22][1]))));
    vnb[0][0] = u[0];
    vnb[0][1] = u[1];
    vnb[0][2] = u[2];
    vnb[1][0] = vnk[8][0];
    vnb[1][1] = vnk[8][1];
    vnb[1][2] = vnk[8][2];
    vnb[2][0] = vnk[11][0];
    vnb[2][1] = vnk[11][1];
    vnb[2][2] = vnk[11][2];
    vnb[3][0] = vnk[12][0];
    vnb[3][1] = vnk[12][1];
    vnb[3][2] = vnk[12][2];
    vnb[4][0] = vnk[14][0];
    vnb[4][1] = vnk[14][1];
    vnb[4][2] = vnk[14][2];
    vnb[5][0] = vnk[15][0];
    vnb[5][1] = vnk[15][1];
    vnb[5][2] = vnk[15][2];
    vnb[6][0] = vnk[18][0];
    vnb[6][1] = vnk[18][1];
    vnb[6][2] = vnk[18][2];
    vnb[7][0] = vnk[19][0];
    vnb[7][1] = vnk[19][1];
    vnb[7][2] = vnk[19][2];
    vnb[8][0] = vnk[21][0];
    vnb[8][1] = vnk[21][1];
    vnb[8][2] = vnk[21][2];
    vnb[9][0] = vnk[22][0];
    vnb[9][1] = vnk[22][1];
    vnb[9][2] = vnk[22][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = (.5*((q[23]*u[3])+((q[4]*u[5])-(q[5]*u[4]))));
    qdot[4] = (.5*((q[5]*u[3])+((q[23]*u[4])-(q[3]*u[5]))));
    qdot[5] = (.5*(((q[3]*u[4])+(q[23]*u[5]))-(q[4]*u[3])));
    qdot[23] = -(.5*((q[3]*u[3])+((q[4]*u[4])+(q[5]*u[5]))));
    if (stabvel  !=  0.) {
        ee = ((q[23]*q[23])+((q[5]*q[5])+((q[3]*q[3])+(q[4]*q[4]))));
        stab = ((stabvel*(1.-ee))/ee);
        qdot[3] = (qdot[3]+(q[3]*stab));
        qdot[4] = (qdot[4]+(q[4]*stab));
        qdot[5] = (qdot[5]+(q[5]*stab));
        qdot[23] = (qdot[23]+(q[23]*stab));
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
    for (i = 0; i < 23; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 0.36 seconds CPU time,
 81920 additional bytes of memory.
 Equations contain  971 adds/subtracts/negates
                   1409 multiplies
                      1 divides
                    918 assignments
*/
}

sdqdot(oqdot)
    double oqdot[24];
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 23; i++) {
        oqdot[i] = qdot[i];
    }
}

sdu2qdot(uin,oqdot)
    double uin[23],oqdot[24];
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 22; i++) {
        oqdot[i] = uin[i];
    }
    oqdot[3] = (.5*((q[23]*uin[3])+((q[4]*uin[5])-(q[5]*uin[4]))));
    oqdot[4] = (.5*((q[5]*uin[3])+((q[23]*uin[4])-(q[3]*uin[5]))));
    oqdot[5] = (.5*(((q[3]*uin[4])+(q[23]*uin[5]))-(q[4]*uin[3])));
    oqdot[23] = -(.5*((q[3]*uin[3])+((q[4]*uin[4])+(q[5]*uin[5]))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                     16 multiplies
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
        Wpk[3][3][0] = 1.;
        Wpk[3][4][0] = 1.;
        Wpk[3][5][0] = 1.;
        Wpk[3][6][0] = c6;
        Wpk[3][6][1] = -s6;
        Wpk[3][7][0] = c6;
        Wpk[3][7][1] = -(s6*c7);
        Wpk[3][7][2] = (s6*s7);
        Wpk[3][8][0] = ((c6*c8)-(Wpk[3][7][2]*s8));
        Wpk[3][8][1] = Wpk[3][7][1];
        Wpk[3][8][2] = ((Wpk[3][7][2]*c8)+(s8*c6));
        Wpk[3][9][0] = c9;
        Wpk[3][9][1] = -s9;
        Wpk[3][10][0] = c9;
        Wpk[3][10][1] = -(s9*c10);
        Wpk[3][10][2] = (s9*s10);
        Wpk[3][11][0] = ((c9*c11)-(Wpk[3][10][2]*s11));
        Wpk[3][11][1] = Wpk[3][10][1];
        Wpk[3][11][2] = ((Wpk[3][10][2]*c11)+(s11*c9));
        Wpk[3][12][0] = ((Cik[12][2][0]*Wpk[3][11][2])+((Cik[12][0][0]*
          Wpk[3][11][0])+(Cik[12][1][0]*Wpk[3][10][1])));
        Wpk[3][12][1] = ((Cik[12][2][1]*Wpk[3][11][2])+((Cik[12][0][1]*
          Wpk[3][11][0])+(Cik[12][1][1]*Wpk[3][10][1])));
        Wpk[3][12][2] = ((Cik[12][2][2]*Wpk[3][11][2])+((Cik[12][0][2]*
          Wpk[3][11][0])+(Cik[12][1][2]*Wpk[3][10][1])));
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
        Wpk[3][15][0] = ((Cik[15][2][0]*Wpk[3][14][2])+((.882947501360837*(
          Wpk[3][14][1]*s15))+(Cik[15][0][0]*Wpk[3][14][0])));
        Wpk[3][15][1] = (((Wpk[3][14][1]*c15)-(.882947501360837*(Wpk[3][14][0]*
          s15)))-(.469471734868729*(Wpk[3][14][2]*s15)));
        Wpk[3][15][2] = ((Cik[15][2][2]*Wpk[3][14][2])+((.469471734868729*(
          Wpk[3][14][1]*s15))+(Cik[15][0][2]*Wpk[3][14][0])));
        Wpk[3][16][0] = c16;
        Wpk[3][16][1] = -s16;
        Wpk[3][17][0] = c16;
        Wpk[3][17][1] = -(s16*c17);
        Wpk[3][17][2] = -(s16*s17);
        Wpk[3][18][0] = ((Wpk[3][17][2]*s18)+(c16*c18));
        Wpk[3][18][1] = Wpk[3][17][1];
        Wpk[3][18][2] = ((Wpk[3][17][2]*c18)-(s18*c16));
        Wpk[3][19][0] = ((Cik[19][2][0]*Wpk[3][18][2])+((Cik[19][0][0]*
          Wpk[3][18][0])+(Cik[19][1][0]*Wpk[3][17][1])));
        Wpk[3][19][1] = ((Cik[19][2][1]*Wpk[3][18][2])+((Cik[19][0][1]*
          Wpk[3][18][0])+(Cik[19][1][1]*Wpk[3][17][1])));
        Wpk[3][19][2] = ((Cik[19][2][2]*Wpk[3][18][2])+((Cik[19][0][2]*
          Wpk[3][18][0])+(Cik[19][1][2]*Wpk[3][17][1])));
        Wpk[3][20][0] = ((Cik[20][2][0]*Wpk[3][19][2])+((Cik[20][0][0]*
          Wpk[3][19][0])+(Cik[20][1][0]*Wpk[3][19][1])));
        Wpk[3][20][1] = ((Cik[20][2][1]*Wpk[3][19][2])+((Cik[20][0][1]*
          Wpk[3][19][0])+(Cik[20][1][1]*Wpk[3][19][1])));
        Wpk[3][20][2] = ((Cik[20][2][2]*Wpk[3][19][2])+((Cik[20][0][2]*
          Wpk[3][19][0])+(Cik[20][1][2]*Wpk[3][19][1])));
        Wpk[3][21][0] = ((Cik[21][2][0]*Wpk[3][20][2])+((Cik[21][0][0]*
          Wpk[3][20][0])+(Cik[21][1][0]*Wpk[3][20][1])));
        Wpk[3][21][1] = ((Cik[21][2][1]*Wpk[3][20][2])+((Cik[21][0][1]*
          Wpk[3][20][0])+(Cik[21][1][1]*Wpk[3][20][1])));
        Wpk[3][21][2] = ((Cik[21][2][2]*Wpk[3][20][2])+((Cik[21][0][2]*
          Wpk[3][20][0])+(Cik[21][1][2]*Wpk[3][20][1])));
        Wpk[3][22][0] = ((Cik[22][2][0]*Wpk[3][21][2])+((.882947501360837*(
          Wpk[3][21][1]*s22))+(Cik[22][0][0]*Wpk[3][21][0])));
        Wpk[3][22][1] = ((.469471734868729*(Wpk[3][21][2]*s22))+((Wpk[3][21][1]*
          c22)-(.882947501360837*(Wpk[3][21][0]*s22))));
        Wpk[3][22][2] = ((Cik[22][2][2]*Wpk[3][21][2])+((Cik[22][0][2]*
          Wpk[3][21][0])-(.469471734868729*(Wpk[3][21][1]*s22))));
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = 1.;
        Wpk[4][6][0] = s6;
        Wpk[4][6][1] = c6;
        Wpk[4][7][0] = s6;
        Wpk[4][7][1] = (c6*c7);
        Wpk[4][7][2] = -(s7*c6);
        Wpk[4][8][0] = ((s6*c8)-(Wpk[4][7][2]*s8));
        Wpk[4][8][1] = Wpk[4][7][1];
        Wpk[4][8][2] = ((Wpk[4][7][2]*c8)+(s6*s8));
        Wpk[4][9][0] = s9;
        Wpk[4][9][1] = c9;
        Wpk[4][10][0] = s9;
        Wpk[4][10][1] = (c9*c10);
        Wpk[4][10][2] = -(s10*c9);
        Wpk[4][11][0] = ((s9*c11)-(Wpk[4][10][2]*s11));
        Wpk[4][11][1] = Wpk[4][10][1];
        Wpk[4][11][2] = ((Wpk[4][10][2]*c11)+(s9*s11));
        Wpk[4][12][0] = ((Cik[12][2][0]*Wpk[4][11][2])+((Cik[12][0][0]*
          Wpk[4][11][0])+(Cik[12][1][0]*Wpk[4][10][1])));
        Wpk[4][12][1] = ((Cik[12][2][1]*Wpk[4][11][2])+((Cik[12][0][1]*
          Wpk[4][11][0])+(Cik[12][1][1]*Wpk[4][10][1])));
        Wpk[4][12][2] = ((Cik[12][2][2]*Wpk[4][11][2])+((Cik[12][0][2]*
          Wpk[4][11][0])+(Cik[12][1][2]*Wpk[4][10][1])));
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
        Wpk[4][15][0] = ((Cik[15][2][0]*Wpk[4][14][2])+((.882947501360837*(
          Wpk[4][14][1]*s15))+(Cik[15][0][0]*Wpk[4][14][0])));
        Wpk[4][15][1] = (((Wpk[4][14][1]*c15)-(.882947501360837*(Wpk[4][14][0]*
          s15)))-(.469471734868729*(Wpk[4][14][2]*s15)));
        Wpk[4][15][2] = ((Cik[15][2][2]*Wpk[4][14][2])+((.469471734868729*(
          Wpk[4][14][1]*s15))+(Cik[15][0][2]*Wpk[4][14][0])));
        Wpk[4][16][0] = s16;
        Wpk[4][16][1] = c16;
        Wpk[4][17][0] = s16;
        Wpk[4][17][1] = (c16*c17);
        Wpk[4][17][2] = (s17*c16);
        Wpk[4][18][0] = ((Wpk[4][17][2]*s18)+(s16*c18));
        Wpk[4][18][1] = Wpk[4][17][1];
        Wpk[4][18][2] = ((Wpk[4][17][2]*c18)-(s16*s18));
        Wpk[4][19][0] = ((Cik[19][2][0]*Wpk[4][18][2])+((Cik[19][0][0]*
          Wpk[4][18][0])+(Cik[19][1][0]*Wpk[4][17][1])));
        Wpk[4][19][1] = ((Cik[19][2][1]*Wpk[4][18][2])+((Cik[19][0][1]*
          Wpk[4][18][0])+(Cik[19][1][1]*Wpk[4][17][1])));
        Wpk[4][19][2] = ((Cik[19][2][2]*Wpk[4][18][2])+((Cik[19][0][2]*
          Wpk[4][18][0])+(Cik[19][1][2]*Wpk[4][17][1])));
        Wpk[4][20][0] = ((Cik[20][2][0]*Wpk[4][19][2])+((Cik[20][0][0]*
          Wpk[4][19][0])+(Cik[20][1][0]*Wpk[4][19][1])));
        Wpk[4][20][1] = ((Cik[20][2][1]*Wpk[4][19][2])+((Cik[20][0][1]*
          Wpk[4][19][0])+(Cik[20][1][1]*Wpk[4][19][1])));
        Wpk[4][20][2] = ((Cik[20][2][2]*Wpk[4][19][2])+((Cik[20][0][2]*
          Wpk[4][19][0])+(Cik[20][1][2]*Wpk[4][19][1])));
        Wpk[4][21][0] = ((Cik[21][2][0]*Wpk[4][20][2])+((Cik[21][0][0]*
          Wpk[4][20][0])+(Cik[21][1][0]*Wpk[4][20][1])));
        Wpk[4][21][1] = ((Cik[21][2][1]*Wpk[4][20][2])+((Cik[21][0][1]*
          Wpk[4][20][0])+(Cik[21][1][1]*Wpk[4][20][1])));
        Wpk[4][21][2] = ((Cik[21][2][2]*Wpk[4][20][2])+((Cik[21][0][2]*
          Wpk[4][20][0])+(Cik[21][1][2]*Wpk[4][20][1])));
        Wpk[4][22][0] = ((Cik[22][2][0]*Wpk[4][21][2])+((.882947501360837*(
          Wpk[4][21][1]*s22))+(Cik[22][0][0]*Wpk[4][21][0])));
        Wpk[4][22][1] = ((.469471734868729*(Wpk[4][21][2]*s22))+((Wpk[4][21][1]*
          c22)-(.882947501360837*(Wpk[4][21][0]*s22))));
        Wpk[4][22][2] = ((Cik[22][2][2]*Wpk[4][21][2])+((Cik[22][0][2]*
          Wpk[4][21][0])-(.469471734868729*(Wpk[4][21][1]*s22))));
        Wpk[5][5][2] = 1.;
        Wpk[5][6][2] = 1.;
        Wpk[5][7][1] = s7;
        Wpk[5][7][2] = c7;
        Wpk[5][8][0] = -(s8*c7);
        Wpk[5][8][1] = s7;
        Wpk[5][8][2] = (c7*c8);
        Wpk[5][9][2] = 1.;
        Wpk[5][10][1] = s10;
        Wpk[5][10][2] = c10;
        Wpk[5][11][0] = -(s11*c10);
        Wpk[5][11][1] = s10;
        Wpk[5][11][2] = (c10*c11);
        Wpk[5][12][0] = ((Cik[12][2][0]*Wpk[5][11][2])+((Cik[12][0][0]*
          Wpk[5][11][0])+(Cik[12][1][0]*s10)));
        Wpk[5][12][1] = ((Cik[12][2][1]*Wpk[5][11][2])+((Cik[12][0][1]*
          Wpk[5][11][0])+(Cik[12][1][1]*s10)));
        Wpk[5][12][2] = ((Cik[12][2][2]*Wpk[5][11][2])+((Cik[12][0][2]*
          Wpk[5][11][0])+(Cik[12][1][2]*s10)));
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
        Wpk[5][15][0] = ((Cik[15][2][0]*Wpk[5][14][2])+((.882947501360837*(
          Wpk[5][14][1]*s15))+(Cik[15][0][0]*Wpk[5][14][0])));
        Wpk[5][15][1] = (((Wpk[5][14][1]*c15)-(.882947501360837*(Wpk[5][14][0]*
          s15)))-(.469471734868729*(Wpk[5][14][2]*s15)));
        Wpk[5][15][2] = ((Cik[15][2][2]*Wpk[5][14][2])+((.469471734868729*(
          Wpk[5][14][1]*s15))+(Cik[15][0][2]*Wpk[5][14][0])));
        Wpk[5][16][2] = 1.;
        Wpk[5][17][1] = -s17;
        Wpk[5][17][2] = c17;
        Wpk[5][18][0] = (s18*c17);
        Wpk[5][18][1] = -s17;
        Wpk[5][18][2] = (c17*c18);
        Wpk[5][19][0] = ((Cik[19][2][0]*Wpk[5][18][2])+((Cik[19][0][0]*
          Wpk[5][18][0])-(Cik[19][1][0]*s17)));
        Wpk[5][19][1] = ((Cik[19][2][1]*Wpk[5][18][2])+((Cik[19][0][1]*
          Wpk[5][18][0])-(Cik[19][1][1]*s17)));
        Wpk[5][19][2] = ((Cik[19][2][2]*Wpk[5][18][2])+((Cik[19][0][2]*
          Wpk[5][18][0])-(Cik[19][1][2]*s17)));
        Wpk[5][20][0] = ((Cik[20][2][0]*Wpk[5][19][2])+((Cik[20][0][0]*
          Wpk[5][19][0])+(Cik[20][1][0]*Wpk[5][19][1])));
        Wpk[5][20][1] = ((Cik[20][2][1]*Wpk[5][19][2])+((Cik[20][0][1]*
          Wpk[5][19][0])+(Cik[20][1][1]*Wpk[5][19][1])));
        Wpk[5][20][2] = ((Cik[20][2][2]*Wpk[5][19][2])+((Cik[20][0][2]*
          Wpk[5][19][0])+(Cik[20][1][2]*Wpk[5][19][1])));
        Wpk[5][21][0] = ((Cik[21][2][0]*Wpk[5][20][2])+((Cik[21][0][0]*
          Wpk[5][20][0])+(Cik[21][1][0]*Wpk[5][20][1])));
        Wpk[5][21][1] = ((Cik[21][2][1]*Wpk[5][20][2])+((Cik[21][0][1]*
          Wpk[5][20][0])+(Cik[21][1][1]*Wpk[5][20][1])));
        Wpk[5][21][2] = ((Cik[21][2][2]*Wpk[5][20][2])+((Cik[21][0][2]*
          Wpk[5][20][0])+(Cik[21][1][2]*Wpk[5][20][1])));
        Wpk[5][22][0] = ((Cik[22][2][0]*Wpk[5][21][2])+((.882947501360837*(
          Wpk[5][21][1]*s22))+(Cik[22][0][0]*Wpk[5][21][0])));
        Wpk[5][22][1] = ((.469471734868729*(Wpk[5][21][2]*s22))+((Wpk[5][21][1]*
          c22)-(.882947501360837*(Wpk[5][21][0]*s22))));
        Wpk[5][22][2] = ((Cik[22][2][2]*Wpk[5][21][2])+((Cik[22][0][2]*
          Wpk[5][21][0])-(.469471734868729*(Wpk[5][21][1]*s22))));
        Wpk[6][6][2] = 1.;
        Wpk[6][7][1] = s7;
        Wpk[6][7][2] = c7;
        Wpk[6][8][0] = -(s8*c7);
        Wpk[6][8][1] = s7;
        Wpk[6][8][2] = (c7*c8);
        Wpk[7][7][0] = 1.;
        Wpk[7][8][0] = c8;
        Wpk[7][8][2] = s8;
        Wpk[8][8][1] = 1.;
        Wpk[9][9][2] = 1.;
        Wpk[9][10][1] = s10;
        Wpk[9][10][2] = c10;
        Wpk[9][11][0] = -(s11*c10);
        Wpk[9][11][1] = s10;
        Wpk[9][11][2] = (c10*c11);
        Wpk[9][12][0] = ((Cik[12][2][0]*Wpk[9][11][2])+((Cik[12][0][0]*
          Wpk[9][11][0])+(Cik[12][1][0]*s10)));
        Wpk[9][12][1] = ((Cik[12][2][1]*Wpk[9][11][2])+((Cik[12][0][1]*
          Wpk[9][11][0])+(Cik[12][1][1]*s10)));
        Wpk[9][12][2] = ((Cik[12][2][2]*Wpk[9][11][2])+((Cik[12][0][2]*
          Wpk[9][11][0])+(Cik[12][1][2]*s10)));
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
        Wpk[9][15][0] = ((Cik[15][2][0]*Wpk[9][14][2])+((.882947501360837*(
          Wpk[9][14][1]*s15))+(Cik[15][0][0]*Wpk[9][14][0])));
        Wpk[9][15][1] = (((Wpk[9][14][1]*c15)-(.882947501360837*(Wpk[9][14][0]*
          s15)))-(.469471734868729*(Wpk[9][14][2]*s15)));
        Wpk[9][15][2] = ((Cik[15][2][2]*Wpk[9][14][2])+((.469471734868729*(
          Wpk[9][14][1]*s15))+(Cik[15][0][2]*Wpk[9][14][0])));
        Wpk[10][10][0] = 1.;
        Wpk[10][11][0] = c11;
        Wpk[10][11][2] = s11;
        Wpk[10][12][0] = ((Cik[12][0][0]*c11)+(Cik[12][2][0]*s11));
        Wpk[10][12][1] = ((Cik[12][0][1]*c11)+(Cik[12][2][1]*s11));
        Wpk[10][12][2] = ((Cik[12][0][2]*c11)+(Cik[12][2][2]*s11));
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
        Wpk[10][15][0] = ((Cik[15][2][0]*Wpk[10][14][2])+((.882947501360837*(
          Wpk[10][14][1]*s15))+(Cik[15][0][0]*Wpk[10][14][0])));
        Wpk[10][15][1] = (((Wpk[10][14][1]*c15)-(.882947501360837*(
          Wpk[10][14][0]*s15)))-(.469471734868729*(Wpk[10][14][2]*s15)));
        Wpk[10][15][2] = ((Cik[15][2][2]*Wpk[10][14][2])+((.469471734868729*(
          Wpk[10][14][1]*s15))+(Cik[15][0][2]*Wpk[10][14][0])));
        Wpk[11][11][1] = 1.;
        Wpk[11][12][0] = Cik[12][1][0];
        Wpk[11][12][1] = Cik[12][1][1];
        Wpk[11][12][2] = Cik[12][1][2];
        Wpk[11][13][0] = ((Cik[12][1][2]*Cik[13][2][0])+((Cik[12][1][0]*
          Cik[13][0][0])+(Cik[12][1][1]*Cik[13][1][0])));
        Wpk[11][13][1] = ((Cik[12][1][2]*Cik[13][2][1])+((Cik[12][1][0]*
          Cik[13][0][1])+(Cik[12][1][1]*Cik[13][1][1])));
        Wpk[11][13][2] = ((Cik[12][1][2]*Cik[13][2][2])+((Cik[12][1][0]*
          Cik[13][0][2])+(Cik[12][1][1]*Cik[13][1][2])));
        Wpk[11][14][0] = ((Cik[14][2][0]*Wpk[11][13][2])+((Cik[14][0][0]*
          Wpk[11][13][0])+(Cik[14][1][0]*Wpk[11][13][1])));
        Wpk[11][14][1] = ((Cik[14][2][1]*Wpk[11][13][2])+((Cik[14][0][1]*
          Wpk[11][13][0])+(Cik[14][1][1]*Wpk[11][13][1])));
        Wpk[11][14][2] = ((Cik[14][2][2]*Wpk[11][13][2])+((Cik[14][0][2]*
          Wpk[11][13][0])+(Cik[14][1][2]*Wpk[11][13][1])));
        Wpk[11][15][0] = ((Cik[15][2][0]*Wpk[11][14][2])+((.882947501360837*(
          Wpk[11][14][1]*s15))+(Cik[15][0][0]*Wpk[11][14][0])));
        Wpk[11][15][1] = (((Wpk[11][14][1]*c15)-(.882947501360837*(
          Wpk[11][14][0]*s15)))-(.469471734868729*(Wpk[11][14][2]*s15)));
        Wpk[11][15][2] = ((Cik[15][2][2]*Wpk[11][14][2])+((.469471734868729*(
          Wpk[11][14][1]*s15))+(Cik[15][0][2]*Wpk[11][14][0])));
        Wpk[12][12][0] = -.0809090128117004;
        Wpk[12][12][1] = .0404550064059294;
        Wpk[12][12][2] = .995900157697815;
        Wpk[12][13][0] = ((.995900157697815*Cik[13][2][0])+((.0404550064059294*
          Cik[13][1][0])-(.0809090128117004*Cik[13][0][0])));
        Wpk[12][13][1] = ((.995900157697815*Cik[13][2][1])+((.0404550064059294*
          Cik[13][1][1])-(.0809090128117004*Cik[13][0][1])));
        Wpk[12][13][2] = ((.995900157697815*Cik[13][2][2])+((.0404550064059294*
          Cik[13][1][2])-(.0809090128117004*Cik[13][0][2])));
        Wpk[12][14][0] = ((Cik[14][2][0]*Wpk[12][13][2])+((Cik[14][0][0]*
          Wpk[12][13][0])+(Cik[14][1][0]*Wpk[12][13][1])));
        Wpk[12][14][1] = ((Cik[14][2][1]*Wpk[12][13][2])+((Cik[14][0][1]*
          Wpk[12][13][0])+(Cik[14][1][1]*Wpk[12][13][1])));
        Wpk[12][14][2] = ((Cik[14][2][2]*Wpk[12][13][2])+((Cik[14][0][2]*
          Wpk[12][13][0])+(Cik[14][1][2]*Wpk[12][13][1])));
        Wpk[12][15][0] = ((Cik[15][2][0]*Wpk[12][14][2])+((.882947501360837*(
          Wpk[12][14][1]*s15))+(Cik[15][0][0]*Wpk[12][14][0])));
        Wpk[12][15][1] = (((Wpk[12][14][1]*c15)-(.882947501360837*(
          Wpk[12][14][0]*s15)))-(.469471734868729*(Wpk[12][14][2]*s15)));
        Wpk[12][15][2] = ((Cik[15][2][2]*Wpk[12][14][2])+((.469471734868729*(
          Wpk[12][14][1]*s15))+(Cik[15][0][2]*Wpk[12][14][0])));
        Wpk[13][13][0] = -.0821860132171146;
        Wpk[13][13][1] = -.0372090059839342;
        Wpk[13][13][2] = .995922160163717;
        Wpk[13][14][0] = ((.995922160163717*Cik[14][2][0])-((.0372090059839342*
          Cik[14][1][0])+(.0821860132171146*Cik[14][0][0])));
        Wpk[13][14][1] = ((.995922160163717*Cik[14][2][1])-((.0372090059839342*
          Cik[14][1][1])+(.0821860132171146*Cik[14][0][1])));
        Wpk[13][14][2] = ((.995922160163717*Cik[14][2][2])-((.0372090059839342*
          Cik[14][1][2])+(.0821860132171146*Cik[14][0][2])));
        Wpk[13][15][0] = ((Cik[15][2][0]*Wpk[13][14][2])+((.882947501360837*(
          Wpk[13][14][1]*s15))+(Cik[15][0][0]*Wpk[13][14][0])));
        Wpk[13][15][1] = (((Wpk[13][14][1]*c15)-(.882947501360837*(
          Wpk[13][14][0]*s15)))-(.469471734868729*(Wpk[13][14][2]*s15)));
        Wpk[13][15][2] = ((Cik[15][2][2]*Wpk[13][14][2])+((.469471734868729*(
          Wpk[13][14][1]*s15))+(Cik[15][0][2]*Wpk[13][14][0])));
        Wpk[14][14][0] = .814755846133373;
        Wpk[14][14][1] = .57725989098448;
        Wpk[14][14][2] = -.0542579897533796;
        Wpk[14][15][0] = (((.509690178380576*s15)+(.814755846133373*
          Cik[15][0][0]))-(.0542579897533796*Cik[15][2][0]));
        Wpk[14][15][1] = ((.0254725925800089*s15)+((.57725989098448*c15)-(
          .719386638562596*s15)));
        Wpk[14][15][2] = (((.271007202490617*s15)+(.814755846133373*
          Cik[15][0][2]))-(.0542579897533796*Cik[15][2][2]));
        Wpk[15][15][0] = -.469471734868729;
        Wpk[15][15][2] = .882947501360837;
        Wpk[16][16][2] = 1.;
        Wpk[16][17][1] = -s17;
        Wpk[16][17][2] = c17;
        Wpk[16][18][0] = (s18*c17);
        Wpk[16][18][1] = -s17;
        Wpk[16][18][2] = (c17*c18);
        Wpk[16][19][0] = ((Cik[19][2][0]*Wpk[16][18][2])+((Cik[19][0][0]*
          Wpk[16][18][0])-(Cik[19][1][0]*s17)));
        Wpk[16][19][1] = ((Cik[19][2][1]*Wpk[16][18][2])+((Cik[19][0][1]*
          Wpk[16][18][0])-(Cik[19][1][1]*s17)));
        Wpk[16][19][2] = ((Cik[19][2][2]*Wpk[16][18][2])+((Cik[19][0][2]*
          Wpk[16][18][0])-(Cik[19][1][2]*s17)));
        Wpk[16][20][0] = ((Cik[20][2][0]*Wpk[16][19][2])+((Cik[20][0][0]*
          Wpk[16][19][0])+(Cik[20][1][0]*Wpk[16][19][1])));
        Wpk[16][20][1] = ((Cik[20][2][1]*Wpk[16][19][2])+((Cik[20][0][1]*
          Wpk[16][19][0])+(Cik[20][1][1]*Wpk[16][19][1])));
        Wpk[16][20][2] = ((Cik[20][2][2]*Wpk[16][19][2])+((Cik[20][0][2]*
          Wpk[16][19][0])+(Cik[20][1][2]*Wpk[16][19][1])));
        Wpk[16][21][0] = ((Cik[21][2][0]*Wpk[16][20][2])+((Cik[21][0][0]*
          Wpk[16][20][0])+(Cik[21][1][0]*Wpk[16][20][1])));
        Wpk[16][21][1] = ((Cik[21][2][1]*Wpk[16][20][2])+((Cik[21][0][1]*
          Wpk[16][20][0])+(Cik[21][1][1]*Wpk[16][20][1])));
        Wpk[16][21][2] = ((Cik[21][2][2]*Wpk[16][20][2])+((Cik[21][0][2]*
          Wpk[16][20][0])+(Cik[21][1][2]*Wpk[16][20][1])));
        Wpk[16][22][0] = ((Cik[22][2][0]*Wpk[16][21][2])+((.882947501360837*(
          Wpk[16][21][1]*s22))+(Cik[22][0][0]*Wpk[16][21][0])));
        Wpk[16][22][1] = ((.469471734868729*(Wpk[16][21][2]*s22))+((
          Wpk[16][21][1]*c22)-(.882947501360837*(Wpk[16][21][0]*s22))));
        Wpk[16][22][2] = ((Cik[22][2][2]*Wpk[16][21][2])+((Cik[22][0][2]*
          Wpk[16][21][0])-(.469471734868729*(Wpk[16][21][1]*s22))));
        Wpk[17][17][0] = -1.;
        Wpk[17][18][0] = -c18;
        Wpk[17][18][2] = s18;
        Wpk[17][19][0] = ((Cik[19][2][0]*s18)-(Cik[19][0][0]*c18));
        Wpk[17][19][1] = ((Cik[19][2][1]*s18)-(Cik[19][0][1]*c18));
        Wpk[17][19][2] = ((Cik[19][2][2]*s18)-(Cik[19][0][2]*c18));
        Wpk[17][20][0] = ((Cik[20][2][0]*Wpk[17][19][2])+((Cik[20][0][0]*
          Wpk[17][19][0])+(Cik[20][1][0]*Wpk[17][19][1])));
        Wpk[17][20][1] = ((Cik[20][2][1]*Wpk[17][19][2])+((Cik[20][0][1]*
          Wpk[17][19][0])+(Cik[20][1][1]*Wpk[17][19][1])));
        Wpk[17][20][2] = ((Cik[20][2][2]*Wpk[17][19][2])+((Cik[20][0][2]*
          Wpk[17][19][0])+(Cik[20][1][2]*Wpk[17][19][1])));
        Wpk[17][21][0] = ((Cik[21][2][0]*Wpk[17][20][2])+((Cik[21][0][0]*
          Wpk[17][20][0])+(Cik[21][1][0]*Wpk[17][20][1])));
        Wpk[17][21][1] = ((Cik[21][2][1]*Wpk[17][20][2])+((Cik[21][0][1]*
          Wpk[17][20][0])+(Cik[21][1][1]*Wpk[17][20][1])));
        Wpk[17][21][2] = ((Cik[21][2][2]*Wpk[17][20][2])+((Cik[21][0][2]*
          Wpk[17][20][0])+(Cik[21][1][2]*Wpk[17][20][1])));
        Wpk[17][22][0] = ((Cik[22][2][0]*Wpk[17][21][2])+((.882947501360837*(
          Wpk[17][21][1]*s22))+(Cik[22][0][0]*Wpk[17][21][0])));
        Wpk[17][22][1] = ((.469471734868729*(Wpk[17][21][2]*s22))+((
          Wpk[17][21][1]*c22)-(.882947501360837*(Wpk[17][21][0]*s22))));
        Wpk[17][22][2] = ((Cik[22][2][2]*Wpk[17][21][2])+((Cik[22][0][2]*
          Wpk[17][21][0])-(.469471734868729*(Wpk[17][21][1]*s22))));
        Wpk[18][18][1] = -1.;
        Wpk[18][19][0] = -Cik[19][1][0];
        Wpk[18][19][1] = -Cik[19][1][1];
        Wpk[18][19][2] = -Cik[19][1][2];
        Wpk[18][20][0] = -((Cik[19][1][2]*Cik[20][2][0])+((Cik[19][1][0]*
          Cik[20][0][0])+(Cik[19][1][1]*Cik[20][1][0])));
        Wpk[18][20][1] = -((Cik[19][1][2]*Cik[20][2][1])+((Cik[19][1][0]*
          Cik[20][0][1])+(Cik[19][1][1]*Cik[20][1][1])));
        Wpk[18][20][2] = -((Cik[19][1][2]*Cik[20][2][2])+((Cik[19][1][0]*
          Cik[20][0][2])+(Cik[19][1][1]*Cik[20][1][2])));
        Wpk[18][21][0] = ((Cik[21][2][0]*Wpk[18][20][2])+((Cik[21][0][0]*
          Wpk[18][20][0])+(Cik[21][1][0]*Wpk[18][20][1])));
        Wpk[18][21][1] = ((Cik[21][2][1]*Wpk[18][20][2])+((Cik[21][0][1]*
          Wpk[18][20][0])+(Cik[21][1][1]*Wpk[18][20][1])));
        Wpk[18][21][2] = ((Cik[21][2][2]*Wpk[18][20][2])+((Cik[21][0][2]*
          Wpk[18][20][0])+(Cik[21][1][2]*Wpk[18][20][1])));
        Wpk[18][22][0] = ((Cik[22][2][0]*Wpk[18][21][2])+((.882947501360837*(
          Wpk[18][21][1]*s22))+(Cik[22][0][0]*Wpk[18][21][0])));
        Wpk[18][22][1] = ((.469471734868729*(Wpk[18][21][2]*s22))+((
          Wpk[18][21][1]*c22)-(.882947501360837*(Wpk[18][21][0]*s22))));
        Wpk[18][22][2] = ((Cik[22][2][2]*Wpk[18][21][2])+((Cik[22][0][2]*
          Wpk[18][21][0])-(.469471734868729*(Wpk[18][21][1]*s22))));
        Wpk[19][19][0] = .0809090128117004;
        Wpk[19][19][1] = -.0404550064059294;
        Wpk[19][19][2] = .995900157697815;
        Wpk[19][20][0] = ((.995900157697815*Cik[20][2][0])+((.0809090128117004*
          Cik[20][0][0])-(.0404550064059294*Cik[20][1][0])));
        Wpk[19][20][1] = ((.995900157697815*Cik[20][2][1])+((.0809090128117004*
          Cik[20][0][1])-(.0404550064059294*Cik[20][1][1])));
        Wpk[19][20][2] = ((.995900157697815*Cik[20][2][2])+((.0809090128117004*
          Cik[20][0][2])-(.0404550064059294*Cik[20][1][2])));
        Wpk[19][21][0] = ((Cik[21][2][0]*Wpk[19][20][2])+((Cik[21][0][0]*
          Wpk[19][20][0])+(Cik[21][1][0]*Wpk[19][20][1])));
        Wpk[19][21][1] = ((Cik[21][2][1]*Wpk[19][20][2])+((Cik[21][0][1]*
          Wpk[19][20][0])+(Cik[21][1][1]*Wpk[19][20][1])));
        Wpk[19][21][2] = ((Cik[21][2][2]*Wpk[19][20][2])+((Cik[21][0][2]*
          Wpk[19][20][0])+(Cik[21][1][2]*Wpk[19][20][1])));
        Wpk[19][22][0] = ((Cik[22][2][0]*Wpk[19][21][2])+((.882947501360837*(
          Wpk[19][21][1]*s22))+(Cik[22][0][0]*Wpk[19][21][0])));
        Wpk[19][22][1] = ((.469471734868729*(Wpk[19][21][2]*s22))+((
          Wpk[19][21][1]*c22)-(.882947501360837*(Wpk[19][21][0]*s22))));
        Wpk[19][22][2] = ((Cik[22][2][2]*Wpk[19][21][2])+((Cik[22][0][2]*
          Wpk[19][21][0])-(.469471734868729*(Wpk[19][21][1]*s22))));
        Wpk[20][20][0] = .0821860132171146;
        Wpk[20][20][1] = .0372090059839342;
        Wpk[20][20][2] = .995922160163717;
        Wpk[20][21][0] = ((.995922160163717*Cik[21][2][0])+((.0372090059839342*
          Cik[21][1][0])+(.0821860132171146*Cik[21][0][0])));
        Wpk[20][21][1] = ((.995922160163717*Cik[21][2][1])+((.0372090059839342*
          Cik[21][1][1])+(.0821860132171146*Cik[21][0][1])));
        Wpk[20][21][2] = ((.995922160163717*Cik[21][2][2])+((.0372090059839342*
          Cik[21][1][2])+(.0821860132171146*Cik[21][0][2])));
        Wpk[20][22][0] = ((Cik[22][2][0]*Wpk[20][21][2])+((.882947501360837*(
          Wpk[20][21][1]*s22))+(Cik[22][0][0]*Wpk[20][21][0])));
        Wpk[20][22][1] = ((.469471734868729*(Wpk[20][21][2]*s22))+((
          Wpk[20][21][1]*c22)-(.882947501360837*(Wpk[20][21][0]*s22))));
        Wpk[20][22][2] = ((Cik[22][2][2]*Wpk[20][21][2])+((Cik[22][0][2]*
          Wpk[20][21][0])-(.469471734868729*(Wpk[20][21][1]*s22))));
        Wpk[21][21][0] = -.814755846133373;
        Wpk[21][21][1] = -.57725989098448;
        Wpk[21][21][2] = -.0542579897533796;
        Wpk[21][22][0] = -((.0542579897533796*Cik[22][2][0])+((.509690178380576*
          s22)+(.814755846133373*Cik[22][0][0])));
        Wpk[21][22][1] = (((.719386638562596*s22)-(.57725989098448*c22))-(
          .0254725925800089*s22));
        Wpk[21][22][2] = (((.271007202490617*s22)-(.814755846133373*
          Cik[22][0][2]))-(.0542579897533796*Cik[22][2][2]));
        Wpk[22][22][0] = .469471734868729;
        Wpk[22][22][2] = .882947501360837;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = 1.;
        Vpk[0][1][0] = 1.;
        Vpk[0][2][0] = 1.;
        Vpk[0][3][0] = Cik[3][0][0];
        Vpk[0][3][1] = Cik[3][0][1];
        Vpk[0][3][2] = Cik[3][0][2];
        Vpk[0][4][0] = Cik[3][0][0];
        Vpk[0][4][1] = Cik[3][0][1];
        Vpk[0][4][2] = Cik[3][0][2];
        Vpk[0][5][0] = Cik[3][0][0];
        Vpk[0][5][1] = Cik[3][0][1];
        Vpk[0][5][2] = Cik[3][0][2];
        Vpk[0][6][0] = ((Cik[3][0][0]*c6)+(Cik[3][0][1]*s6));
        Vpk[0][6][1] = ((Cik[3][0][1]*c6)-(Cik[3][0][0]*s6));
        Vpk[0][6][2] = Cik[3][0][2];
        Vpk[0][7][0] = Vpk[0][6][0];
        Vpk[0][7][1] = ((Cik[3][0][2]*s7)+(Vpk[0][6][1]*c7));
        Vpk[0][7][2] = ((Cik[3][0][2]*c7)-(Vpk[0][6][1]*s7));
        Vpk[0][8][0] = ((Vpk[0][6][0]*c8)-(Vpk[0][7][2]*s8));
        Vpk[0][8][1] = Vpk[0][7][1];
        Vpk[0][8][2] = ((Vpk[0][6][0]*s8)+(Vpk[0][7][2]*c8));
        Vpk[0][9][0] = ((Cik[3][0][0]*c9)+(Cik[3][0][1]*s9));
        Vpk[0][9][1] = ((Cik[3][0][1]*c9)-(Cik[3][0][0]*s9));
        Vpk[0][9][2] = Cik[3][0][2];
        Vpk[0][10][0] = Vpk[0][9][0];
        Vpk[0][10][1] = ((Cik[3][0][2]*s10)+(Vpk[0][9][1]*c10));
        Vpk[0][10][2] = ((Cik[3][0][2]*c10)-(Vpk[0][9][1]*s10));
        Vpk[0][11][0] = ((Vpk[0][9][0]*c11)-(Vpk[0][10][2]*s11));
        Vpk[0][11][1] = Vpk[0][10][1];
        Vpk[0][11][2] = ((Vpk[0][9][0]*s11)+(Vpk[0][10][2]*c11));
        Vpk[0][12][0] = ((Cik[12][2][0]*Vpk[0][11][2])+((Cik[12][0][0]*
          Vpk[0][11][0])+(Cik[12][1][0]*Vpk[0][10][1])));
        Vpk[0][12][1] = ((Cik[12][2][1]*Vpk[0][11][2])+((Cik[12][0][1]*
          Vpk[0][11][0])+(Cik[12][1][1]*Vpk[0][10][1])));
        Vpk[0][12][2] = ((Cik[12][2][2]*Vpk[0][11][2])+((Cik[12][0][2]*
          Vpk[0][11][0])+(Cik[12][1][2]*Vpk[0][10][1])));
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
        Vpk[0][15][0] = ((Cik[15][2][0]*Vpk[0][14][2])+((.882947501360837*(
          Vpk[0][14][1]*s15))+(Cik[15][0][0]*Vpk[0][14][0])));
        Vpk[0][15][1] = (((Vpk[0][14][1]*c15)-(.882947501360837*(Vpk[0][14][0]*
          s15)))-(.469471734868729*(Vpk[0][14][2]*s15)));
        Vpk[0][15][2] = ((Cik[15][2][2]*Vpk[0][14][2])+((.469471734868729*(
          Vpk[0][14][1]*s15))+(Cik[15][0][2]*Vpk[0][14][0])));
        Vpk[0][16][0] = ((Cik[3][0][0]*c16)+(Cik[3][0][1]*s16));
        Vpk[0][16][1] = ((Cik[3][0][1]*c16)-(Cik[3][0][0]*s16));
        Vpk[0][16][2] = Cik[3][0][2];
        Vpk[0][17][0] = Vpk[0][16][0];
        Vpk[0][17][1] = ((Vpk[0][16][1]*c17)-(Cik[3][0][2]*s17));
        Vpk[0][17][2] = ((Cik[3][0][2]*c17)+(Vpk[0][16][1]*s17));
        Vpk[0][18][0] = ((Vpk[0][16][0]*c18)+(Vpk[0][17][2]*s18));
        Vpk[0][18][1] = Vpk[0][17][1];
        Vpk[0][18][2] = ((Vpk[0][17][2]*c18)-(Vpk[0][16][0]*s18));
        Vpk[0][19][0] = ((Cik[19][2][0]*Vpk[0][18][2])+((Cik[19][0][0]*
          Vpk[0][18][0])+(Cik[19][1][0]*Vpk[0][17][1])));
        Vpk[0][19][1] = ((Cik[19][2][1]*Vpk[0][18][2])+((Cik[19][0][1]*
          Vpk[0][18][0])+(Cik[19][1][1]*Vpk[0][17][1])));
        Vpk[0][19][2] = ((Cik[19][2][2]*Vpk[0][18][2])+((Cik[19][0][2]*
          Vpk[0][18][0])+(Cik[19][1][2]*Vpk[0][17][1])));
        Vpk[0][20][0] = ((Cik[20][2][0]*Vpk[0][19][2])+((Cik[20][0][0]*
          Vpk[0][19][0])+(Cik[20][1][0]*Vpk[0][19][1])));
        Vpk[0][20][1] = ((Cik[20][2][1]*Vpk[0][19][2])+((Cik[20][0][1]*
          Vpk[0][19][0])+(Cik[20][1][1]*Vpk[0][19][1])));
        Vpk[0][20][2] = ((Cik[20][2][2]*Vpk[0][19][2])+((Cik[20][0][2]*
          Vpk[0][19][0])+(Cik[20][1][2]*Vpk[0][19][1])));
        Vpk[0][21][0] = ((Cik[21][2][0]*Vpk[0][20][2])+((Cik[21][0][0]*
          Vpk[0][20][0])+(Cik[21][1][0]*Vpk[0][20][1])));
        Vpk[0][21][1] = ((Cik[21][2][1]*Vpk[0][20][2])+((Cik[21][0][1]*
          Vpk[0][20][0])+(Cik[21][1][1]*Vpk[0][20][1])));
        Vpk[0][21][2] = ((Cik[21][2][2]*Vpk[0][20][2])+((Cik[21][0][2]*
          Vpk[0][20][0])+(Cik[21][1][2]*Vpk[0][20][1])));
        Vpk[0][22][0] = ((Cik[22][2][0]*Vpk[0][21][2])+((.882947501360837*(
          Vpk[0][21][1]*s22))+(Cik[22][0][0]*Vpk[0][21][0])));
        Vpk[0][22][1] = ((.469471734868729*(Vpk[0][21][2]*s22))+((Vpk[0][21][1]*
          c22)-(.882947501360837*(Vpk[0][21][0]*s22))));
        Vpk[0][22][2] = ((Cik[22][2][2]*Vpk[0][21][2])+((Cik[22][0][2]*
          Vpk[0][21][0])-(.469471734868729*(Vpk[0][21][1]*s22))));
        Vpk[1][1][1] = 1.;
        Vpk[1][2][1] = 1.;
        Vpk[1][3][0] = Cik[3][1][0];
        Vpk[1][3][1] = Cik[3][1][1];
        Vpk[1][3][2] = Cik[3][1][2];
        Vpk[1][4][0] = Cik[3][1][0];
        Vpk[1][4][1] = Cik[3][1][1];
        Vpk[1][4][2] = Cik[3][1][2];
        Vpk[1][5][0] = Cik[3][1][0];
        Vpk[1][5][1] = Cik[3][1][1];
        Vpk[1][5][2] = Cik[3][1][2];
        Vpk[1][6][0] = ((Cik[3][1][0]*c6)+(Cik[3][1][1]*s6));
        Vpk[1][6][1] = ((Cik[3][1][1]*c6)-(Cik[3][1][0]*s6));
        Vpk[1][6][2] = Cik[3][1][2];
        Vpk[1][7][0] = Vpk[1][6][0];
        Vpk[1][7][1] = ((Cik[3][1][2]*s7)+(Vpk[1][6][1]*c7));
        Vpk[1][7][2] = ((Cik[3][1][2]*c7)-(Vpk[1][6][1]*s7));
        Vpk[1][8][0] = ((Vpk[1][6][0]*c8)-(Vpk[1][7][2]*s8));
        Vpk[1][8][1] = Vpk[1][7][1];
        Vpk[1][8][2] = ((Vpk[1][6][0]*s8)+(Vpk[1][7][2]*c8));
        Vpk[1][9][0] = ((Cik[3][1][0]*c9)+(Cik[3][1][1]*s9));
        Vpk[1][9][1] = ((Cik[3][1][1]*c9)-(Cik[3][1][0]*s9));
        Vpk[1][9][2] = Cik[3][1][2];
        Vpk[1][10][0] = Vpk[1][9][0];
        Vpk[1][10][1] = ((Cik[3][1][2]*s10)+(Vpk[1][9][1]*c10));
        Vpk[1][10][2] = ((Cik[3][1][2]*c10)-(Vpk[1][9][1]*s10));
        Vpk[1][11][0] = ((Vpk[1][9][0]*c11)-(Vpk[1][10][2]*s11));
        Vpk[1][11][1] = Vpk[1][10][1];
        Vpk[1][11][2] = ((Vpk[1][9][0]*s11)+(Vpk[1][10][2]*c11));
        Vpk[1][12][0] = ((Cik[12][2][0]*Vpk[1][11][2])+((Cik[12][0][0]*
          Vpk[1][11][0])+(Cik[12][1][0]*Vpk[1][10][1])));
        Vpk[1][12][1] = ((Cik[12][2][1]*Vpk[1][11][2])+((Cik[12][0][1]*
          Vpk[1][11][0])+(Cik[12][1][1]*Vpk[1][10][1])));
        Vpk[1][12][2] = ((Cik[12][2][2]*Vpk[1][11][2])+((Cik[12][0][2]*
          Vpk[1][11][0])+(Cik[12][1][2]*Vpk[1][10][1])));
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
        Vpk[1][15][0] = ((Cik[15][2][0]*Vpk[1][14][2])+((.882947501360837*(
          Vpk[1][14][1]*s15))+(Cik[15][0][0]*Vpk[1][14][0])));
        Vpk[1][15][1] = (((Vpk[1][14][1]*c15)-(.882947501360837*(Vpk[1][14][0]*
          s15)))-(.469471734868729*(Vpk[1][14][2]*s15)));
        Vpk[1][15][2] = ((Cik[15][2][2]*Vpk[1][14][2])+((.469471734868729*(
          Vpk[1][14][1]*s15))+(Cik[15][0][2]*Vpk[1][14][0])));
        Vpk[1][16][0] = ((Cik[3][1][0]*c16)+(Cik[3][1][1]*s16));
        Vpk[1][16][1] = ((Cik[3][1][1]*c16)-(Cik[3][1][0]*s16));
        Vpk[1][16][2] = Cik[3][1][2];
        Vpk[1][17][0] = Vpk[1][16][0];
        Vpk[1][17][1] = ((Vpk[1][16][1]*c17)-(Cik[3][1][2]*s17));
        Vpk[1][17][2] = ((Cik[3][1][2]*c17)+(Vpk[1][16][1]*s17));
        Vpk[1][18][0] = ((Vpk[1][16][0]*c18)+(Vpk[1][17][2]*s18));
        Vpk[1][18][1] = Vpk[1][17][1];
        Vpk[1][18][2] = ((Vpk[1][17][2]*c18)-(Vpk[1][16][0]*s18));
        Vpk[1][19][0] = ((Cik[19][2][0]*Vpk[1][18][2])+((Cik[19][0][0]*
          Vpk[1][18][0])+(Cik[19][1][0]*Vpk[1][17][1])));
        Vpk[1][19][1] = ((Cik[19][2][1]*Vpk[1][18][2])+((Cik[19][0][1]*
          Vpk[1][18][0])+(Cik[19][1][1]*Vpk[1][17][1])));
        Vpk[1][19][2] = ((Cik[19][2][2]*Vpk[1][18][2])+((Cik[19][0][2]*
          Vpk[1][18][0])+(Cik[19][1][2]*Vpk[1][17][1])));
        Vpk[1][20][0] = ((Cik[20][2][0]*Vpk[1][19][2])+((Cik[20][0][0]*
          Vpk[1][19][0])+(Cik[20][1][0]*Vpk[1][19][1])));
        Vpk[1][20][1] = ((Cik[20][2][1]*Vpk[1][19][2])+((Cik[20][0][1]*
          Vpk[1][19][0])+(Cik[20][1][1]*Vpk[1][19][1])));
        Vpk[1][20][2] = ((Cik[20][2][2]*Vpk[1][19][2])+((Cik[20][0][2]*
          Vpk[1][19][0])+(Cik[20][1][2]*Vpk[1][19][1])));
        Vpk[1][21][0] = ((Cik[21][2][0]*Vpk[1][20][2])+((Cik[21][0][0]*
          Vpk[1][20][0])+(Cik[21][1][0]*Vpk[1][20][1])));
        Vpk[1][21][1] = ((Cik[21][2][1]*Vpk[1][20][2])+((Cik[21][0][1]*
          Vpk[1][20][0])+(Cik[21][1][1]*Vpk[1][20][1])));
        Vpk[1][21][2] = ((Cik[21][2][2]*Vpk[1][20][2])+((Cik[21][0][2]*
          Vpk[1][20][0])+(Cik[21][1][2]*Vpk[1][20][1])));
        Vpk[1][22][0] = ((Cik[22][2][0]*Vpk[1][21][2])+((.882947501360837*(
          Vpk[1][21][1]*s22))+(Cik[22][0][0]*Vpk[1][21][0])));
        Vpk[1][22][1] = ((.469471734868729*(Vpk[1][21][2]*s22))+((Vpk[1][21][1]*
          c22)-(.882947501360837*(Vpk[1][21][0]*s22))));
        Vpk[1][22][2] = ((Cik[22][2][2]*Vpk[1][21][2])+((Cik[22][0][2]*
          Vpk[1][21][0])-(.469471734868729*(Vpk[1][21][1]*s22))));
        Vpk[2][2][2] = 1.;
        Vpk[2][3][0] = Cik[3][2][0];
        Vpk[2][3][1] = Cik[3][2][1];
        Vpk[2][3][2] = Cik[3][2][2];
        Vpk[2][4][0] = Cik[3][2][0];
        Vpk[2][4][1] = Cik[3][2][1];
        Vpk[2][4][2] = Cik[3][2][2];
        Vpk[2][5][0] = Cik[3][2][0];
        Vpk[2][5][1] = Cik[3][2][1];
        Vpk[2][5][2] = Cik[3][2][2];
        Vpk[2][6][0] = ((Cik[3][2][0]*c6)+(Cik[3][2][1]*s6));
        Vpk[2][6][1] = ((Cik[3][2][1]*c6)-(Cik[3][2][0]*s6));
        Vpk[2][6][2] = Cik[3][2][2];
        Vpk[2][7][0] = Vpk[2][6][0];
        Vpk[2][7][1] = ((Cik[3][2][2]*s7)+(Vpk[2][6][1]*c7));
        Vpk[2][7][2] = ((Cik[3][2][2]*c7)-(Vpk[2][6][1]*s7));
        Vpk[2][8][0] = ((Vpk[2][6][0]*c8)-(Vpk[2][7][2]*s8));
        Vpk[2][8][1] = Vpk[2][7][1];
        Vpk[2][8][2] = ((Vpk[2][6][0]*s8)+(Vpk[2][7][2]*c8));
        Vpk[2][9][0] = ((Cik[3][2][0]*c9)+(Cik[3][2][1]*s9));
        Vpk[2][9][1] = ((Cik[3][2][1]*c9)-(Cik[3][2][0]*s9));
        Vpk[2][9][2] = Cik[3][2][2];
        Vpk[2][10][0] = Vpk[2][9][0];
        Vpk[2][10][1] = ((Cik[3][2][2]*s10)+(Vpk[2][9][1]*c10));
        Vpk[2][10][2] = ((Cik[3][2][2]*c10)-(Vpk[2][9][1]*s10));
        Vpk[2][11][0] = ((Vpk[2][9][0]*c11)-(Vpk[2][10][2]*s11));
        Vpk[2][11][1] = Vpk[2][10][1];
        Vpk[2][11][2] = ((Vpk[2][9][0]*s11)+(Vpk[2][10][2]*c11));
        Vpk[2][12][0] = ((Cik[12][2][0]*Vpk[2][11][2])+((Cik[12][0][0]*
          Vpk[2][11][0])+(Cik[12][1][0]*Vpk[2][10][1])));
        Vpk[2][12][1] = ((Cik[12][2][1]*Vpk[2][11][2])+((Cik[12][0][1]*
          Vpk[2][11][0])+(Cik[12][1][1]*Vpk[2][10][1])));
        Vpk[2][12][2] = ((Cik[12][2][2]*Vpk[2][11][2])+((Cik[12][0][2]*
          Vpk[2][11][0])+(Cik[12][1][2]*Vpk[2][10][1])));
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
        Vpk[2][15][0] = ((Cik[15][2][0]*Vpk[2][14][2])+((.882947501360837*(
          Vpk[2][14][1]*s15))+(Cik[15][0][0]*Vpk[2][14][0])));
        Vpk[2][15][1] = (((Vpk[2][14][1]*c15)-(.882947501360837*(Vpk[2][14][0]*
          s15)))-(.469471734868729*(Vpk[2][14][2]*s15)));
        Vpk[2][15][2] = ((Cik[15][2][2]*Vpk[2][14][2])+((.469471734868729*(
          Vpk[2][14][1]*s15))+(Cik[15][0][2]*Vpk[2][14][0])));
        Vpk[2][16][0] = ((Cik[3][2][0]*c16)+(Cik[3][2][1]*s16));
        Vpk[2][16][1] = ((Cik[3][2][1]*c16)-(Cik[3][2][0]*s16));
        Vpk[2][16][2] = Cik[3][2][2];
        Vpk[2][17][0] = Vpk[2][16][0];
        Vpk[2][17][1] = ((Vpk[2][16][1]*c17)-(Cik[3][2][2]*s17));
        Vpk[2][17][2] = ((Cik[3][2][2]*c17)+(Vpk[2][16][1]*s17));
        Vpk[2][18][0] = ((Vpk[2][16][0]*c18)+(Vpk[2][17][2]*s18));
        Vpk[2][18][1] = Vpk[2][17][1];
        Vpk[2][18][2] = ((Vpk[2][17][2]*c18)-(Vpk[2][16][0]*s18));
        Vpk[2][19][0] = ((Cik[19][2][0]*Vpk[2][18][2])+((Cik[19][0][0]*
          Vpk[2][18][0])+(Cik[19][1][0]*Vpk[2][17][1])));
        Vpk[2][19][1] = ((Cik[19][2][1]*Vpk[2][18][2])+((Cik[19][0][1]*
          Vpk[2][18][0])+(Cik[19][1][1]*Vpk[2][17][1])));
        Vpk[2][19][2] = ((Cik[19][2][2]*Vpk[2][18][2])+((Cik[19][0][2]*
          Vpk[2][18][0])+(Cik[19][1][2]*Vpk[2][17][1])));
        Vpk[2][20][0] = ((Cik[20][2][0]*Vpk[2][19][2])+((Cik[20][0][0]*
          Vpk[2][19][0])+(Cik[20][1][0]*Vpk[2][19][1])));
        Vpk[2][20][1] = ((Cik[20][2][1]*Vpk[2][19][2])+((Cik[20][0][1]*
          Vpk[2][19][0])+(Cik[20][1][1]*Vpk[2][19][1])));
        Vpk[2][20][2] = ((Cik[20][2][2]*Vpk[2][19][2])+((Cik[20][0][2]*
          Vpk[2][19][0])+(Cik[20][1][2]*Vpk[2][19][1])));
        Vpk[2][21][0] = ((Cik[21][2][0]*Vpk[2][20][2])+((Cik[21][0][0]*
          Vpk[2][20][0])+(Cik[21][1][0]*Vpk[2][20][1])));
        Vpk[2][21][1] = ((Cik[21][2][1]*Vpk[2][20][2])+((Cik[21][0][1]*
          Vpk[2][20][0])+(Cik[21][1][1]*Vpk[2][20][1])));
        Vpk[2][21][2] = ((Cik[21][2][2]*Vpk[2][20][2])+((Cik[21][0][2]*
          Vpk[2][20][0])+(Cik[21][1][2]*Vpk[2][20][1])));
        Vpk[2][22][0] = ((Cik[22][2][0]*Vpk[2][21][2])+((.882947501360837*(
          Vpk[2][21][1]*s22))+(Cik[22][0][0]*Vpk[2][21][0])));
        Vpk[2][22][1] = ((.469471734868729*(Vpk[2][21][2]*s22))+((Vpk[2][21][1]*
          c22)-(.882947501360837*(Vpk[2][21][0]*s22))));
        Vpk[2][22][2] = ((Cik[22][2][2]*Vpk[2][21][2])+((Cik[22][0][2]*
          Vpk[2][21][0])-(.469471734868729*(Vpk[2][21][1]*s22))));
        Vpk[3][6][2] = .127;
        Vpk[3][7][1] = (.127*s7);
        Vpk[3][7][2] = (.127*c7);
        Vpk[3][8][0] = -((.127*(s8*c7))+(.3202*Wpk[3][8][2]));
        Vpk[3][8][1] = (.127*s7);
        Vpk[3][8][2] = ((.127*(c7*c8))+(.3202*Wpk[3][8][0]));
        Vpk[3][9][0] = -(.0935*s9);
        Vpk[3][9][1] = -(.0935*c9);
        Vpk[3][9][2] = -.07;
        Vpk[3][10][0] = -(.0935*s9);
        Vpk[3][10][1] = -((.07*s10)+(.0935*(c9*c10)));
        Vpk[3][10][2] = ((.0935*(s10*c9))-(.07*c10));
        Vpk[3][11][0] = ((.1715*Wpk[3][11][2])-((.0935*(s9*c11))+(Vpk[3][10][2]*
          s11)));
        Vpk[3][11][1] = (Vpk[3][10][1]-(.002*Wpk[3][11][2]));
        Vpk[3][11][2] = (((.002*Wpk[3][10][1])-(.1715*Wpk[3][11][0]))+((
          Vpk[3][10][2]*c11)-(.0935*(s9*s11))));
        VWri[3][12][0] = (Vpk[3][11][0]+(.2294*Wpk[3][11][2]));
        VWri[3][12][1] = (Vpk[3][11][1]+(.0033*Wpk[3][11][2]));
        VWri[3][12][2] = (Vpk[3][11][2]-((.0033*Wpk[3][10][1])+(.2294*
          Wpk[3][11][0])));
        Vpk[3][12][0] = ((.1862*Wpk[3][12][2])+((Cik[12][2][0]*VWri[3][12][2])+(
          (Cik[12][0][0]*VWri[3][12][0])+(Cik[12][1][0]*VWri[3][12][1]))));
        Vpk[3][12][1] = ((Cik[12][2][1]*VWri[3][12][2])+((Cik[12][0][1]*
          VWri[3][12][0])+(Cik[12][1][1]*VWri[3][12][1])));
        Vpk[3][12][2] = (((Cik[12][2][2]*VWri[3][12][2])+((Cik[12][0][2]*
          VWri[3][12][0])+(Cik[12][1][2]*VWri[3][12][1])))-(.1862*Wpk[3][12][0])
          );
        VWri[3][13][0] = (Vpk[3][12][0]+(.2438*Wpk[3][12][2]));
        VWri[3][13][2] = (Vpk[3][12][2]-(.2438*Wpk[3][12][0]));
        Vpk[3][13][0] = ((Cik[13][2][0]*VWri[3][13][2])+((Cik[13][0][0]*
          VWri[3][13][0])+(Cik[13][1][0]*Vpk[3][12][1])));
        Vpk[3][13][1] = ((Cik[13][2][1]*VWri[3][13][2])+((Cik[13][0][1]*
          VWri[3][13][0])+(Cik[13][1][1]*Vpk[3][12][1])));
        Vpk[3][13][2] = ((Cik[13][2][2]*VWri[3][13][2])+((Cik[13][0][2]*
          VWri[3][13][0])+(Cik[13][1][2]*Vpk[3][12][1])));
        Vpk[3][14][0] = (((.005539*Wpk[3][14][1])+(.051347*Wpk[3][14][2]))+((
          Cik[14][2][0]*Vpk[3][13][2])+((Cik[14][0][0]*Vpk[3][13][0])+(
          Cik[14][1][0]*Vpk[3][13][1]))));
        Vpk[3][14][1] = (((.035902*Wpk[3][14][2])-(.005539*Wpk[3][14][0]))+((
          Cik[14][2][1]*Vpk[3][13][2])+((Cik[14][0][1]*Vpk[3][13][0])+(
          Cik[14][1][1]*Vpk[3][13][1]))));
        Vpk[3][14][2] = (((Cik[14][2][2]*Vpk[3][13][2])+((Cik[14][0][2]*
          Vpk[3][13][0])+(Cik[14][1][2]*Vpk[3][13][1])))-((.035902*Wpk[3][14][1]
          )+(.051347*Wpk[3][14][0])));
        VWri[3][15][0] = (Vpk[3][14][0]+((.018078*Wpk[3][14][1])+(.038*
          Wpk[3][14][2])));
        VWri[3][15][1] = (Vpk[3][14][1]+((.098032*Wpk[3][14][2])-(.018078*
          Wpk[3][14][0])));
        VWri[3][15][2] = (Vpk[3][14][2]-((.038*Wpk[3][14][0])+(.098032*
          Wpk[3][14][1])));
        Vpk[3][15][0] = (((.005139*Wpk[3][15][1])-(.0185*Wpk[3][15][2]))+((
          Cik[15][2][0]*VWri[3][15][2])+((.882947501360837*(VWri[3][15][1]*s15))
          +(Cik[15][0][0]*VWri[3][15][0]))));
        Vpk[3][15][1] = (((.026917*Wpk[3][15][2])-(.005139*Wpk[3][15][0]))+(((
          VWri[3][15][1]*c15)-(.882947501360837*(VWri[3][15][0]*s15)))-(
          .469471734868729*(VWri[3][15][2]*s15))));
        Vpk[3][15][2] = (((.0185*Wpk[3][15][0])-(.026917*Wpk[3][15][1]))+((
          Cik[15][2][2]*VWri[3][15][2])+((.469471734868729*(VWri[3][15][1]*s15))
          +(Cik[15][0][2]*VWri[3][15][0]))));
        Vpk[3][16][0] = (.0935*s16);
        Vpk[3][16][1] = (.0935*c16);
        Vpk[3][16][2] = -.07;
        Vpk[3][17][0] = (.0935*s16);
        Vpk[3][17][1] = ((.07*s17)+(.0935*(c16*c17)));
        Vpk[3][17][2] = ((.0935*(s17*c16))-(.07*c17));
        Vpk[3][18][0] = ((.1715*Wpk[3][18][2])+((.0935*(s16*c18))+(Vpk[3][17][2]
          *s18)));
        Vpk[3][18][1] = (Vpk[3][17][1]-(.002*Wpk[3][18][2]));
        Vpk[3][18][2] = (((.002*Wpk[3][17][1])-(.1715*Wpk[3][18][0]))+((
          Vpk[3][17][2]*c18)-(.0935*(s16*s18))));
        VWri[3][19][0] = (Vpk[3][18][0]+(.2294*Wpk[3][18][2]));
        VWri[3][19][1] = (Vpk[3][18][1]+(.0033*Wpk[3][18][2]));
        VWri[3][19][2] = (Vpk[3][18][2]-((.0033*Wpk[3][17][1])+(.2294*
          Wpk[3][18][0])));
        Vpk[3][19][0] = ((.1862*Wpk[3][19][2])+((Cik[19][2][0]*VWri[3][19][2])+(
          (Cik[19][0][0]*VWri[3][19][0])+(Cik[19][1][0]*VWri[3][19][1]))));
        Vpk[3][19][1] = ((Cik[19][2][1]*VWri[3][19][2])+((Cik[19][0][1]*
          VWri[3][19][0])+(Cik[19][1][1]*VWri[3][19][1])));
        Vpk[3][19][2] = (((Cik[19][2][2]*VWri[3][19][2])+((Cik[19][0][2]*
          VWri[3][19][0])+(Cik[19][1][2]*VWri[3][19][1])))-(.1862*Wpk[3][19][0])
          );
        VWri[3][20][0] = (Vpk[3][19][0]+(.2438*Wpk[3][19][2]));
        VWri[3][20][2] = (Vpk[3][19][2]-(.2438*Wpk[3][19][0]));
        Vpk[3][20][0] = ((Cik[20][2][0]*VWri[3][20][2])+((Cik[20][0][0]*
          VWri[3][20][0])+(Cik[20][1][0]*Vpk[3][19][1])));
        Vpk[3][20][1] = ((Cik[20][2][1]*VWri[3][20][2])+((Cik[20][0][1]*
          VWri[3][20][0])+(Cik[20][1][1]*Vpk[3][19][1])));
        Vpk[3][20][2] = ((Cik[20][2][2]*VWri[3][20][2])+((Cik[20][0][2]*
          VWri[3][20][0])+(Cik[20][1][2]*Vpk[3][19][1])));
        Vpk[3][21][0] = (((.051347*Wpk[3][21][2])-(.005539*Wpk[3][21][1]))+((
          Cik[21][2][0]*Vpk[3][20][2])+((Cik[21][0][0]*Vpk[3][20][0])+(
          Cik[21][1][0]*Vpk[3][20][1]))));
        Vpk[3][21][1] = (((.005539*Wpk[3][21][0])+(.035902*Wpk[3][21][2]))+((
          Cik[21][2][1]*Vpk[3][20][2])+((Cik[21][0][1]*Vpk[3][20][0])+(
          Cik[21][1][1]*Vpk[3][20][1]))));
        Vpk[3][21][2] = (((Cik[21][2][2]*Vpk[3][20][2])+((Cik[21][0][2]*
          Vpk[3][20][0])+(Cik[21][1][2]*Vpk[3][20][1])))-((.035902*Wpk[3][21][1]
          )+(.051347*Wpk[3][21][0])));
        VWri[3][22][0] = (Vpk[3][21][0]+((.038*Wpk[3][21][2])-(.018078*
          Wpk[3][21][1])));
        VWri[3][22][1] = (Vpk[3][21][1]+((.018078*Wpk[3][21][0])+(.098032*
          Wpk[3][21][2])));
        VWri[3][22][2] = (Vpk[3][21][2]-((.038*Wpk[3][21][0])+(.098032*
          Wpk[3][21][1])));
        Vpk[3][22][0] = (((Cik[22][2][0]*VWri[3][22][2])+((.882947501360837*(
          VWri[3][22][1]*s22))+(Cik[22][0][0]*VWri[3][22][0])))-((.005139*
          Wpk[3][22][1])+(.0185*Wpk[3][22][2])));
        Vpk[3][22][1] = (((.005139*Wpk[3][22][0])+(.026917*Wpk[3][22][2]))+((
          .469471734868729*(VWri[3][22][2]*s22))+((VWri[3][22][1]*c22)-(
          .882947501360837*(VWri[3][22][0]*s22)))));
        Vpk[3][22][2] = (((.0185*Wpk[3][22][0])-(.026917*Wpk[3][22][1]))+((
          Cik[22][2][2]*VWri[3][22][2])+((Cik[22][0][2]*VWri[3][22][0])-(
          .469471734868729*(VWri[3][22][1]*s22)))));
        Vpk[4][8][0] = -(.3202*Wpk[4][8][2]);
        Vpk[4][8][2] = (.3202*Wpk[4][8][0]);
        Vpk[4][9][0] = (.0935*c9);
        Vpk[4][9][1] = -(.0935*s9);
        Vpk[4][10][0] = (.0935*c9);
        Vpk[4][10][1] = -(.0935*(s9*c10));
        Vpk[4][10][2] = (.0935*(s9*s10));
        Vpk[4][11][0] = ((.1715*Wpk[4][11][2])+((.0935*(c9*c11))-(Vpk[4][10][2]*
          s11)));
        Vpk[4][11][1] = (Vpk[4][10][1]-(.002*Wpk[4][11][2]));
        Vpk[4][11][2] = (((.002*Wpk[4][10][1])-(.1715*Wpk[4][11][0]))+((.0935*(
          s11*c9))+(Vpk[4][10][2]*c11)));
        VWri[4][12][0] = (Vpk[4][11][0]+(.2294*Wpk[4][11][2]));
        VWri[4][12][1] = (Vpk[4][11][1]+(.0033*Wpk[4][11][2]));
        VWri[4][12][2] = (Vpk[4][11][2]-((.0033*Wpk[4][10][1])+(.2294*
          Wpk[4][11][0])));
        Vpk[4][12][0] = ((.1862*Wpk[4][12][2])+((Cik[12][2][0]*VWri[4][12][2])+(
          (Cik[12][0][0]*VWri[4][12][0])+(Cik[12][1][0]*VWri[4][12][1]))));
        Vpk[4][12][1] = ((Cik[12][2][1]*VWri[4][12][2])+((Cik[12][0][1]*
          VWri[4][12][0])+(Cik[12][1][1]*VWri[4][12][1])));
        Vpk[4][12][2] = (((Cik[12][2][2]*VWri[4][12][2])+((Cik[12][0][2]*
          VWri[4][12][0])+(Cik[12][1][2]*VWri[4][12][1])))-(.1862*Wpk[4][12][0])
          );
        VWri[4][13][0] = (Vpk[4][12][0]+(.2438*Wpk[4][12][2]));
        VWri[4][13][2] = (Vpk[4][12][2]-(.2438*Wpk[4][12][0]));
        Vpk[4][13][0] = ((Cik[13][2][0]*VWri[4][13][2])+((Cik[13][0][0]*
          VWri[4][13][0])+(Cik[13][1][0]*Vpk[4][12][1])));
        Vpk[4][13][1] = ((Cik[13][2][1]*VWri[4][13][2])+((Cik[13][0][1]*
          VWri[4][13][0])+(Cik[13][1][1]*Vpk[4][12][1])));
        Vpk[4][13][2] = ((Cik[13][2][2]*VWri[4][13][2])+((Cik[13][0][2]*
          VWri[4][13][0])+(Cik[13][1][2]*Vpk[4][12][1])));
        Vpk[4][14][0] = (((.005539*Wpk[4][14][1])+(.051347*Wpk[4][14][2]))+((
          Cik[14][2][0]*Vpk[4][13][2])+((Cik[14][0][0]*Vpk[4][13][0])+(
          Cik[14][1][0]*Vpk[4][13][1]))));
        Vpk[4][14][1] = (((.035902*Wpk[4][14][2])-(.005539*Wpk[4][14][0]))+((
          Cik[14][2][1]*Vpk[4][13][2])+((Cik[14][0][1]*Vpk[4][13][0])+(
          Cik[14][1][1]*Vpk[4][13][1]))));
        Vpk[4][14][2] = (((Cik[14][2][2]*Vpk[4][13][2])+((Cik[14][0][2]*
          Vpk[4][13][0])+(Cik[14][1][2]*Vpk[4][13][1])))-((.035902*Wpk[4][14][1]
          )+(.051347*Wpk[4][14][0])));
        VWri[4][15][0] = (Vpk[4][14][0]+((.018078*Wpk[4][14][1])+(.038*
          Wpk[4][14][2])));
        VWri[4][15][1] = (Vpk[4][14][1]+((.098032*Wpk[4][14][2])-(.018078*
          Wpk[4][14][0])));
        VWri[4][15][2] = (Vpk[4][14][2]-((.038*Wpk[4][14][0])+(.098032*
          Wpk[4][14][1])));
        Vpk[4][15][0] = (((.005139*Wpk[4][15][1])-(.0185*Wpk[4][15][2]))+((
          Cik[15][2][0]*VWri[4][15][2])+((.882947501360837*(VWri[4][15][1]*s15))
          +(Cik[15][0][0]*VWri[4][15][0]))));
        Vpk[4][15][1] = (((.026917*Wpk[4][15][2])-(.005139*Wpk[4][15][0]))+(((
          VWri[4][15][1]*c15)-(.882947501360837*(VWri[4][15][0]*s15)))-(
          .469471734868729*(VWri[4][15][2]*s15))));
        Vpk[4][15][2] = (((.0185*Wpk[4][15][0])-(.026917*Wpk[4][15][1]))+((
          Cik[15][2][2]*VWri[4][15][2])+((.469471734868729*(VWri[4][15][1]*s15))
          +(Cik[15][0][2]*VWri[4][15][0]))));
        Vpk[4][16][0] = -(.0935*c16);
        Vpk[4][16][1] = (.0935*s16);
        Vpk[4][17][0] = -(.0935*c16);
        Vpk[4][17][1] = (.0935*(s16*c17));
        Vpk[4][17][2] = (.0935*(s16*s17));
        Vpk[4][18][0] = ((.1715*Wpk[4][18][2])+((Vpk[4][17][2]*s18)-(.0935*(c16*
          c18))));
        Vpk[4][18][1] = (Vpk[4][17][1]-(.002*Wpk[4][18][2]));
        Vpk[4][18][2] = (((.002*Wpk[4][17][1])-(.1715*Wpk[4][18][0]))+((.0935*(
          s18*c16))+(Vpk[4][17][2]*c18)));
        VWri[4][19][0] = (Vpk[4][18][0]+(.2294*Wpk[4][18][2]));
        VWri[4][19][1] = (Vpk[4][18][1]+(.0033*Wpk[4][18][2]));
        VWri[4][19][2] = (Vpk[4][18][2]-((.0033*Wpk[4][17][1])+(.2294*
          Wpk[4][18][0])));
        Vpk[4][19][0] = ((.1862*Wpk[4][19][2])+((Cik[19][2][0]*VWri[4][19][2])+(
          (Cik[19][0][0]*VWri[4][19][0])+(Cik[19][1][0]*VWri[4][19][1]))));
        Vpk[4][19][1] = ((Cik[19][2][1]*VWri[4][19][2])+((Cik[19][0][1]*
          VWri[4][19][0])+(Cik[19][1][1]*VWri[4][19][1])));
        Vpk[4][19][2] = (((Cik[19][2][2]*VWri[4][19][2])+((Cik[19][0][2]*
          VWri[4][19][0])+(Cik[19][1][2]*VWri[4][19][1])))-(.1862*Wpk[4][19][0])
          );
        VWri[4][20][0] = (Vpk[4][19][0]+(.2438*Wpk[4][19][2]));
        VWri[4][20][2] = (Vpk[4][19][2]-(.2438*Wpk[4][19][0]));
        Vpk[4][20][0] = ((Cik[20][2][0]*VWri[4][20][2])+((Cik[20][0][0]*
          VWri[4][20][0])+(Cik[20][1][0]*Vpk[4][19][1])));
        Vpk[4][20][1] = ((Cik[20][2][1]*VWri[4][20][2])+((Cik[20][0][1]*
          VWri[4][20][0])+(Cik[20][1][1]*Vpk[4][19][1])));
        Vpk[4][20][2] = ((Cik[20][2][2]*VWri[4][20][2])+((Cik[20][0][2]*
          VWri[4][20][0])+(Cik[20][1][2]*Vpk[4][19][1])));
        Vpk[4][21][0] = (((.051347*Wpk[4][21][2])-(.005539*Wpk[4][21][1]))+((
          Cik[21][2][0]*Vpk[4][20][2])+((Cik[21][0][0]*Vpk[4][20][0])+(
          Cik[21][1][0]*Vpk[4][20][1]))));
        Vpk[4][21][1] = (((.005539*Wpk[4][21][0])+(.035902*Wpk[4][21][2]))+((
          Cik[21][2][1]*Vpk[4][20][2])+((Cik[21][0][1]*Vpk[4][20][0])+(
          Cik[21][1][1]*Vpk[4][20][1]))));
        Vpk[4][21][2] = (((Cik[21][2][2]*Vpk[4][20][2])+((Cik[21][0][2]*
          Vpk[4][20][0])+(Cik[21][1][2]*Vpk[4][20][1])))-((.035902*Wpk[4][21][1]
          )+(.051347*Wpk[4][21][0])));
        VWri[4][22][0] = (Vpk[4][21][0]+((.038*Wpk[4][21][2])-(.018078*
          Wpk[4][21][1])));
        VWri[4][22][1] = (Vpk[4][21][1]+((.018078*Wpk[4][21][0])+(.098032*
          Wpk[4][21][2])));
        VWri[4][22][2] = (Vpk[4][21][2]-((.038*Wpk[4][21][0])+(.098032*
          Wpk[4][21][1])));
        Vpk[4][22][0] = (((Cik[22][2][0]*VWri[4][22][2])+((.882947501360837*(
          VWri[4][22][1]*s22))+(Cik[22][0][0]*VWri[4][22][0])))-((.005139*
          Wpk[4][22][1])+(.0185*Wpk[4][22][2])));
        Vpk[4][22][1] = (((.005139*Wpk[4][22][0])+(.026917*Wpk[4][22][2]))+((
          .469471734868729*(VWri[4][22][2]*s22))+((VWri[4][22][1]*c22)-(
          .882947501360837*(VWri[4][22][0]*s22)))));
        Vpk[4][22][2] = (((.0185*Wpk[4][22][0])-(.026917*Wpk[4][22][1]))+((
          Cik[22][2][2]*VWri[4][22][2])+((Cik[22][0][2]*VWri[4][22][0])-(
          .469471734868729*(VWri[4][22][1]*s22)))));
        Vpk[5][6][0] = -(.127*c6);
        Vpk[5][6][1] = (.127*s6);
        Vpk[5][7][0] = -(.127*c6);
        Vpk[5][7][1] = (.127*(s6*c7));
        Vpk[5][7][2] = -(.127*(s6*s7));
        Vpk[5][8][0] = -((.3202*Wpk[5][8][2])+((.127*(c6*c8))+(Vpk[5][7][2]*s8))
          );
        Vpk[5][8][1] = Vpk[5][7][1];
        Vpk[5][8][2] = ((.3202*Wpk[5][8][0])+((Vpk[5][7][2]*c8)-(.127*(s8*c6))))
          ;
        Vpk[5][9][0] = (.07*c9);
        Vpk[5][9][1] = -(.07*s9);
        Vpk[5][10][0] = (.07*c9);
        Vpk[5][10][1] = -(.07*(s9*c10));
        Vpk[5][10][2] = (.07*(s9*s10));
        Vpk[5][11][0] = ((.1715*Wpk[5][11][2])+((.07*(c9*c11))-(Vpk[5][10][2]*
          s11)));
        Vpk[5][11][1] = (Vpk[5][10][1]-(.002*Wpk[5][11][2]));
        Vpk[5][11][2] = (((.002*s10)-(.1715*Wpk[5][11][0]))+((.07*(s11*c9))+(
          Vpk[5][10][2]*c11)));
        VWri[5][12][0] = (Vpk[5][11][0]+(.2294*Wpk[5][11][2]));
        VWri[5][12][1] = (Vpk[5][11][1]+(.0033*Wpk[5][11][2]));
        VWri[5][12][2] = (Vpk[5][11][2]-((.0033*s10)+(.2294*Wpk[5][11][0])));
        Vpk[5][12][0] = ((.1862*Wpk[5][12][2])+((Cik[12][2][0]*VWri[5][12][2])+(
          (Cik[12][0][0]*VWri[5][12][0])+(Cik[12][1][0]*VWri[5][12][1]))));
        Vpk[5][12][1] = ((Cik[12][2][1]*VWri[5][12][2])+((Cik[12][0][1]*
          VWri[5][12][0])+(Cik[12][1][1]*VWri[5][12][1])));
        Vpk[5][12][2] = (((Cik[12][2][2]*VWri[5][12][2])+((Cik[12][0][2]*
          VWri[5][12][0])+(Cik[12][1][2]*VWri[5][12][1])))-(.1862*Wpk[5][12][0])
          );
        VWri[5][13][0] = (Vpk[5][12][0]+(.2438*Wpk[5][12][2]));
        VWri[5][13][2] = (Vpk[5][12][2]-(.2438*Wpk[5][12][0]));
        Vpk[5][13][0] = ((Cik[13][2][0]*VWri[5][13][2])+((Cik[13][0][0]*
          VWri[5][13][0])+(Cik[13][1][0]*Vpk[5][12][1])));
        Vpk[5][13][1] = ((Cik[13][2][1]*VWri[5][13][2])+((Cik[13][0][1]*
          VWri[5][13][0])+(Cik[13][1][1]*Vpk[5][12][1])));
        Vpk[5][13][2] = ((Cik[13][2][2]*VWri[5][13][2])+((Cik[13][0][2]*
          VWri[5][13][0])+(Cik[13][1][2]*Vpk[5][12][1])));
        Vpk[5][14][0] = (((.005539*Wpk[5][14][1])+(.051347*Wpk[5][14][2]))+((
          Cik[14][2][0]*Vpk[5][13][2])+((Cik[14][0][0]*Vpk[5][13][0])+(
          Cik[14][1][0]*Vpk[5][13][1]))));
        Vpk[5][14][1] = (((.035902*Wpk[5][14][2])-(.005539*Wpk[5][14][0]))+((
          Cik[14][2][1]*Vpk[5][13][2])+((Cik[14][0][1]*Vpk[5][13][0])+(
          Cik[14][1][1]*Vpk[5][13][1]))));
        Vpk[5][14][2] = (((Cik[14][2][2]*Vpk[5][13][2])+((Cik[14][0][2]*
          Vpk[5][13][0])+(Cik[14][1][2]*Vpk[5][13][1])))-((.035902*Wpk[5][14][1]
          )+(.051347*Wpk[5][14][0])));
        VWri[5][15][0] = (Vpk[5][14][0]+((.018078*Wpk[5][14][1])+(.038*
          Wpk[5][14][2])));
        VWri[5][15][1] = (Vpk[5][14][1]+((.098032*Wpk[5][14][2])-(.018078*
          Wpk[5][14][0])));
        VWri[5][15][2] = (Vpk[5][14][2]-((.038*Wpk[5][14][0])+(.098032*
          Wpk[5][14][1])));
        Vpk[5][15][0] = (((.005139*Wpk[5][15][1])-(.0185*Wpk[5][15][2]))+((
          Cik[15][2][0]*VWri[5][15][2])+((.882947501360837*(VWri[5][15][1]*s15))
          +(Cik[15][0][0]*VWri[5][15][0]))));
        Vpk[5][15][1] = (((.026917*Wpk[5][15][2])-(.005139*Wpk[5][15][0]))+(((
          VWri[5][15][1]*c15)-(.882947501360837*(VWri[5][15][0]*s15)))-(
          .469471734868729*(VWri[5][15][2]*s15))));
        Vpk[5][15][2] = (((.0185*Wpk[5][15][0])-(.026917*Wpk[5][15][1]))+((
          Cik[15][2][2]*VWri[5][15][2])+((.469471734868729*(VWri[5][15][1]*s15))
          +(Cik[15][0][2]*VWri[5][15][0]))));
        Vpk[5][16][0] = (.07*c16);
        Vpk[5][16][1] = -(.07*s16);
        Vpk[5][17][0] = (.07*c16);
        Vpk[5][17][1] = -(.07*(s16*c17));
        Vpk[5][17][2] = -(.07*(s16*s17));
        Vpk[5][18][0] = ((.1715*Wpk[5][18][2])+((.07*(c16*c18))+(Vpk[5][17][2]*
          s18)));
        Vpk[5][18][1] = (Vpk[5][17][1]-(.002*Wpk[5][18][2]));
        Vpk[5][18][2] = (((Vpk[5][17][2]*c18)-(.07*(s18*c16)))-((.002*s17)+(
          .1715*Wpk[5][18][0])));
        VWri[5][19][0] = (Vpk[5][18][0]+(.2294*Wpk[5][18][2]));
        VWri[5][19][1] = (Vpk[5][18][1]+(.0033*Wpk[5][18][2]));
        VWri[5][19][2] = (Vpk[5][18][2]+((.0033*s17)-(.2294*Wpk[5][18][0])));
        Vpk[5][19][0] = ((.1862*Wpk[5][19][2])+((Cik[19][2][0]*VWri[5][19][2])+(
          (Cik[19][0][0]*VWri[5][19][0])+(Cik[19][1][0]*VWri[5][19][1]))));
        Vpk[5][19][1] = ((Cik[19][2][1]*VWri[5][19][2])+((Cik[19][0][1]*
          VWri[5][19][0])+(Cik[19][1][1]*VWri[5][19][1])));
        Vpk[5][19][2] = (((Cik[19][2][2]*VWri[5][19][2])+((Cik[19][0][2]*
          VWri[5][19][0])+(Cik[19][1][2]*VWri[5][19][1])))-(.1862*Wpk[5][19][0])
          );
        VWri[5][20][0] = (Vpk[5][19][0]+(.2438*Wpk[5][19][2]));
        VWri[5][20][2] = (Vpk[5][19][2]-(.2438*Wpk[5][19][0]));
        Vpk[5][20][0] = ((Cik[20][2][0]*VWri[5][20][2])+((Cik[20][0][0]*
          VWri[5][20][0])+(Cik[20][1][0]*Vpk[5][19][1])));
        Vpk[5][20][1] = ((Cik[20][2][1]*VWri[5][20][2])+((Cik[20][0][1]*
          VWri[5][20][0])+(Cik[20][1][1]*Vpk[5][19][1])));
        Vpk[5][20][2] = ((Cik[20][2][2]*VWri[5][20][2])+((Cik[20][0][2]*
          VWri[5][20][0])+(Cik[20][1][2]*Vpk[5][19][1])));
        Vpk[5][21][0] = (((.051347*Wpk[5][21][2])-(.005539*Wpk[5][21][1]))+((
          Cik[21][2][0]*Vpk[5][20][2])+((Cik[21][0][0]*Vpk[5][20][0])+(
          Cik[21][1][0]*Vpk[5][20][1]))));
        Vpk[5][21][1] = (((.005539*Wpk[5][21][0])+(.035902*Wpk[5][21][2]))+((
          Cik[21][2][1]*Vpk[5][20][2])+((Cik[21][0][1]*Vpk[5][20][0])+(
          Cik[21][1][1]*Vpk[5][20][1]))));
        Vpk[5][21][2] = (((Cik[21][2][2]*Vpk[5][20][2])+((Cik[21][0][2]*
          Vpk[5][20][0])+(Cik[21][1][2]*Vpk[5][20][1])))-((.035902*Wpk[5][21][1]
          )+(.051347*Wpk[5][21][0])));
        VWri[5][22][0] = (Vpk[5][21][0]+((.038*Wpk[5][21][2])-(.018078*
          Wpk[5][21][1])));
        VWri[5][22][1] = (Vpk[5][21][1]+((.018078*Wpk[5][21][0])+(.098032*
          Wpk[5][21][2])));
        VWri[5][22][2] = (Vpk[5][21][2]-((.038*Wpk[5][21][0])+(.098032*
          Wpk[5][21][1])));
        Vpk[5][22][0] = (((Cik[22][2][0]*VWri[5][22][2])+((.882947501360837*(
          VWri[5][22][1]*s22))+(Cik[22][0][0]*VWri[5][22][0])))-((.005139*
          Wpk[5][22][1])+(.0185*Wpk[5][22][2])));
        Vpk[5][22][1] = (((.005139*Wpk[5][22][0])+(.026917*Wpk[5][22][2]))+((
          .469471734868729*(VWri[5][22][2]*s22))+((VWri[5][22][1]*c22)-(
          .882947501360837*(VWri[5][22][0]*s22)))));
        Vpk[5][22][2] = (((.0185*Wpk[5][22][0])-(.026917*Wpk[5][22][1]))+((
          Cik[22][2][2]*VWri[5][22][2])+((Cik[22][0][2]*VWri[5][22][0])-(
          .469471734868729*(VWri[5][22][1]*s22)))));
        Vpk[6][8][0] = -(.3202*Wpk[6][8][2]);
        Vpk[6][8][2] = (.3202*Wpk[6][8][0]);
        Vpk[7][8][0] = -(.3202*s8);
        Vpk[7][8][2] = (.3202*c8);
        Vpk[9][11][0] = (.1715*Wpk[9][11][2]);
        Vpk[9][11][1] = -(.002*Wpk[9][11][2]);
        Vpk[9][11][2] = ((.002*s10)-(.1715*Wpk[9][11][0]));
        VWri[9][12][2] = (Vpk[9][11][2]-((.0033*s10)+(.2294*Wpk[9][11][0])));
        Vpk[9][12][0] = ((.1862*Wpk[9][12][2])+((Cik[12][2][0]*VWri[9][12][2])+(
          (.0013*(Cik[12][1][0]*Wpk[9][11][2]))+(.4009*(Cik[12][0][0]*
          Wpk[9][11][2])))));
        Vpk[9][12][1] = ((Cik[12][2][1]*VWri[9][12][2])+((.0013*(Cik[12][1][1]*
          Wpk[9][11][2]))+(.4009*(Cik[12][0][1]*Wpk[9][11][2]))));
        Vpk[9][12][2] = (((Cik[12][2][2]*VWri[9][12][2])+((.0013*(Cik[12][1][2]*
          Wpk[9][11][2]))+(.4009*(Cik[12][0][2]*Wpk[9][11][2]))))-(.1862*
          Wpk[9][12][0]));
        VWri[9][13][0] = (Vpk[9][12][0]+(.2438*Wpk[9][12][2]));
        VWri[9][13][2] = (Vpk[9][12][2]-(.2438*Wpk[9][12][0]));
        Vpk[9][13][0] = ((Cik[13][2][0]*VWri[9][13][2])+((Cik[13][0][0]*
          VWri[9][13][0])+(Cik[13][1][0]*Vpk[9][12][1])));
        Vpk[9][13][1] = ((Cik[13][2][1]*VWri[9][13][2])+((Cik[13][0][1]*
          VWri[9][13][0])+(Cik[13][1][1]*Vpk[9][12][1])));
        Vpk[9][13][2] = ((Cik[13][2][2]*VWri[9][13][2])+((Cik[13][0][2]*
          VWri[9][13][0])+(Cik[13][1][2]*Vpk[9][12][1])));
        Vpk[9][14][0] = (((.005539*Wpk[9][14][1])+(.051347*Wpk[9][14][2]))+((
          Cik[14][2][0]*Vpk[9][13][2])+((Cik[14][0][0]*Vpk[9][13][0])+(
          Cik[14][1][0]*Vpk[9][13][1]))));
        Vpk[9][14][1] = (((.035902*Wpk[9][14][2])-(.005539*Wpk[9][14][0]))+((
          Cik[14][2][1]*Vpk[9][13][2])+((Cik[14][0][1]*Vpk[9][13][0])+(
          Cik[14][1][1]*Vpk[9][13][1]))));
        Vpk[9][14][2] = (((Cik[14][2][2]*Vpk[9][13][2])+((Cik[14][0][2]*
          Vpk[9][13][0])+(Cik[14][1][2]*Vpk[9][13][1])))-((.035902*Wpk[9][14][1]
          )+(.051347*Wpk[9][14][0])));
        VWri[9][15][0] = (Vpk[9][14][0]+((.018078*Wpk[9][14][1])+(.038*
          Wpk[9][14][2])));
        VWri[9][15][1] = (Vpk[9][14][1]+((.098032*Wpk[9][14][2])-(.018078*
          Wpk[9][14][0])));
        VWri[9][15][2] = (Vpk[9][14][2]-((.038*Wpk[9][14][0])+(.098032*
          Wpk[9][14][1])));
        Vpk[9][15][0] = (((.005139*Wpk[9][15][1])-(.0185*Wpk[9][15][2]))+((
          Cik[15][2][0]*VWri[9][15][2])+((.882947501360837*(VWri[9][15][1]*s15))
          +(Cik[15][0][0]*VWri[9][15][0]))));
        Vpk[9][15][1] = (((.026917*Wpk[9][15][2])-(.005139*Wpk[9][15][0]))+(((
          VWri[9][15][1]*c15)-(.882947501360837*(VWri[9][15][0]*s15)))-(
          .469471734868729*(VWri[9][15][2]*s15))));
        Vpk[9][15][2] = (((.0185*Wpk[9][15][0])-(.026917*Wpk[9][15][1]))+((
          Cik[15][2][2]*VWri[9][15][2])+((.469471734868729*(VWri[9][15][1]*s15))
          +(Cik[15][0][2]*VWri[9][15][0]))));
        Vpk[10][11][0] = (.1715*s11);
        Vpk[10][11][1] = -(.002*s11);
        Vpk[10][11][2] = -(.1715*c11);
        Vpk[10][12][0] = ((.1862*Wpk[10][12][2])+(((.0013*(Cik[12][1][0]*s11))+(
          .4009*(Cik[12][0][0]*s11)))-(.4009*(Cik[12][2][0]*c11))));
        Vpk[10][12][1] = (((.0013*(Cik[12][1][1]*s11))+(.4009*(Cik[12][0][1]*s11
          )))-(.4009*(Cik[12][2][1]*c11)));
        Vpk[10][12][2] = ((((.0013*(Cik[12][1][2]*s11))+(.4009*(Cik[12][0][2]*
          s11)))-(.4009*(Cik[12][2][2]*c11)))-(.1862*Wpk[10][12][0]));
        VWri[10][13][0] = (Vpk[10][12][0]+(.2438*Wpk[10][12][2]));
        VWri[10][13][2] = (Vpk[10][12][2]-(.2438*Wpk[10][12][0]));
        Vpk[10][13][0] = ((Cik[13][2][0]*VWri[10][13][2])+((Cik[13][0][0]*
          VWri[10][13][0])+(Cik[13][1][0]*Vpk[10][12][1])));
        Vpk[10][13][1] = ((Cik[13][2][1]*VWri[10][13][2])+((Cik[13][0][1]*
          VWri[10][13][0])+(Cik[13][1][1]*Vpk[10][12][1])));
        Vpk[10][13][2] = ((Cik[13][2][2]*VWri[10][13][2])+((Cik[13][0][2]*
          VWri[10][13][0])+(Cik[13][1][2]*Vpk[10][12][1])));
        Vpk[10][14][0] = (((.005539*Wpk[10][14][1])+(.051347*Wpk[10][14][2]))+((
          Cik[14][2][0]*Vpk[10][13][2])+((Cik[14][0][0]*Vpk[10][13][0])+(
          Cik[14][1][0]*Vpk[10][13][1]))));
        Vpk[10][14][1] = (((.035902*Wpk[10][14][2])-(.005539*Wpk[10][14][0]))+((
          Cik[14][2][1]*Vpk[10][13][2])+((Cik[14][0][1]*Vpk[10][13][0])+(
          Cik[14][1][1]*Vpk[10][13][1]))));
        Vpk[10][14][2] = (((Cik[14][2][2]*Vpk[10][13][2])+((Cik[14][0][2]*
          Vpk[10][13][0])+(Cik[14][1][2]*Vpk[10][13][1])))-((.035902*
          Wpk[10][14][1])+(.051347*Wpk[10][14][0])));
        VWri[10][15][0] = (Vpk[10][14][0]+((.018078*Wpk[10][14][1])+(.038*
          Wpk[10][14][2])));
        VWri[10][15][1] = (Vpk[10][14][1]+((.098032*Wpk[10][14][2])-(.018078*
          Wpk[10][14][0])));
        VWri[10][15][2] = (Vpk[10][14][2]-((.038*Wpk[10][14][0])+(.098032*
          Wpk[10][14][1])));
        Vpk[10][15][0] = (((.005139*Wpk[10][15][1])-(.0185*Wpk[10][15][2]))+((
          Cik[15][2][0]*VWri[10][15][2])+((.882947501360837*(VWri[10][15][1]*s15
          ))+(Cik[15][0][0]*VWri[10][15][0]))));
        Vpk[10][15][1] = (((.026917*Wpk[10][15][2])-(.005139*Wpk[10][15][0]))+((
          (VWri[10][15][1]*c15)-(.882947501360837*(VWri[10][15][0]*s15)))-(
          .469471734868729*(VWri[10][15][2]*s15))));
        Vpk[10][15][2] = (((.0185*Wpk[10][15][0])-(.026917*Wpk[10][15][1]))+((
          Cik[15][2][2]*VWri[10][15][2])+((.469471734868729*(VWri[10][15][1]*s15
          ))+(Cik[15][0][2]*VWri[10][15][0]))));
        Vpk[11][11][2] = .002;
        Vpk[11][12][0] = ((.1862*Cik[12][1][2])-(.0013*Cik[12][2][0]));
        Vpk[11][12][1] = -(.0013*Cik[12][2][1]);
        Vpk[11][12][2] = -((.0013*Cik[12][2][2])+(.1862*Cik[12][1][0]));
        VWri[11][13][0] = (Vpk[11][12][0]+(.2438*Cik[12][1][2]));
        VWri[11][13][2] = (Vpk[11][12][2]-(.2438*Cik[12][1][0]));
        Vpk[11][13][0] = ((Cik[13][2][0]*VWri[11][13][2])+((Cik[13][0][0]*
          VWri[11][13][0])-(.0013*(Cik[12][2][1]*Cik[13][1][0]))));
        Vpk[11][13][1] = ((Cik[13][2][1]*VWri[11][13][2])+((Cik[13][0][1]*
          VWri[11][13][0])-(.0013*(Cik[12][2][1]*Cik[13][1][1]))));
        Vpk[11][13][2] = ((Cik[13][2][2]*VWri[11][13][2])+((Cik[13][0][2]*
          VWri[11][13][0])-(.0013*(Cik[12][2][1]*Cik[13][1][2]))));
        Vpk[11][14][0] = (((.005539*Wpk[11][14][1])+(.051347*Wpk[11][14][2]))+((
          Cik[14][2][0]*Vpk[11][13][2])+((Cik[14][0][0]*Vpk[11][13][0])+(
          Cik[14][1][0]*Vpk[11][13][1]))));
        Vpk[11][14][1] = (((.035902*Wpk[11][14][2])-(.005539*Wpk[11][14][0]))+((
          Cik[14][2][1]*Vpk[11][13][2])+((Cik[14][0][1]*Vpk[11][13][0])+(
          Cik[14][1][1]*Vpk[11][13][1]))));
        Vpk[11][14][2] = (((Cik[14][2][2]*Vpk[11][13][2])+((Cik[14][0][2]*
          Vpk[11][13][0])+(Cik[14][1][2]*Vpk[11][13][1])))-((.035902*
          Wpk[11][14][1])+(.051347*Wpk[11][14][0])));
        VWri[11][15][0] = (Vpk[11][14][0]+((.018078*Wpk[11][14][1])+(.038*
          Wpk[11][14][2])));
        VWri[11][15][1] = (Vpk[11][14][1]+((.098032*Wpk[11][14][2])-(.018078*
          Wpk[11][14][0])));
        VWri[11][15][2] = (Vpk[11][14][2]-((.038*Wpk[11][14][0])+(.098032*
          Wpk[11][14][1])));
        Vpk[11][15][0] = (((.005139*Wpk[11][15][1])-(.0185*Wpk[11][15][2]))+((
          Cik[15][2][0]*VWri[11][15][2])+((.882947501360837*(VWri[11][15][1]*s15
          ))+(Cik[15][0][0]*VWri[11][15][0]))));
        Vpk[11][15][1] = (((.026917*Wpk[11][15][2])-(.005139*Wpk[11][15][0]))+((
          (VWri[11][15][1]*c15)-(.882947501360837*(VWri[11][15][0]*s15)))-(
          .469471734868729*(VWri[11][15][2]*s15))));
        Vpk[11][15][2] = (((.0185*Wpk[11][15][0])-(.026917*Wpk[11][15][1]))+((
          Cik[15][2][2]*VWri[11][15][2])+((.469471734868729*(VWri[11][15][1]*s15
          ))+(Cik[15][0][2]*VWri[11][15][0]))));
        Vpk[12][12][0] = .185436609363333;
        Vpk[12][12][2] = .0150652581855386;
        Vpk[12][13][0] = ((.0347908755090312*Cik[13][2][0])+(.42823706781006*
          Cik[13][0][0]));
        Vpk[12][13][1] = ((.0347908755090312*Cik[13][2][1])+(.42823706781006*
          Cik[13][0][1]));
        Vpk[12][13][2] = ((.0347908755090312*Cik[13][2][2])+(.42823706781006*
          Cik[13][0][2]));
        Vpk[12][14][0] = (((.005539*Wpk[12][14][1])+(.051347*Wpk[12][14][2]))+((
          Cik[14][2][0]*Vpk[12][13][2])+((Cik[14][0][0]*Vpk[12][13][0])+(
          Cik[14][1][0]*Vpk[12][13][1]))));
        Vpk[12][14][1] = (((.035902*Wpk[12][14][2])-(.005539*Wpk[12][14][0]))+((
          Cik[14][2][1]*Vpk[12][13][2])+((Cik[14][0][1]*Vpk[12][13][0])+(
          Cik[14][1][1]*Vpk[12][13][1]))));
        Vpk[12][14][2] = (((Cik[14][2][2]*Vpk[12][13][2])+((Cik[14][0][2]*
          Vpk[12][13][0])+(Cik[14][1][2]*Vpk[12][13][1])))-((.035902*
          Wpk[12][14][1])+(.051347*Wpk[12][14][0])));
        VWri[12][15][0] = (Vpk[12][14][0]+((.018078*Wpk[12][14][1])+(.038*
          Wpk[12][14][2])));
        VWri[12][15][1] = (Vpk[12][14][1]+((.098032*Wpk[12][14][2])-(.018078*
          Wpk[12][14][0])));
        VWri[12][15][2] = (Vpk[12][14][2]-((.038*Wpk[12][14][0])+(.098032*
          Wpk[12][14][1])));
        Vpk[12][15][0] = (((.005139*Wpk[12][15][1])-(.0185*Wpk[12][15][2]))+((
          Cik[15][2][0]*VWri[12][15][2])+((.882947501360837*(VWri[12][15][1]*s15
          ))+(Cik[15][0][0]*VWri[12][15][0]))));
        Vpk[12][15][1] = (((.026917*Wpk[12][15][2])-(.005139*Wpk[12][15][0]))+((
          (VWri[12][15][1]*c15)-(.882947501360837*(VWri[12][15][0]*s15)))-(
          .469471734868729*(VWri[12][15][2]*s15))));
        Vpk[12][15][2] = (((.0185*Wpk[12][15][0])-(.026917*Wpk[12][15][1]))+((
          Cik[15][2][2]*VWri[12][15][2])+((.469471734868729*(VWri[12][15][1]*s15
          ))+(Cik[15][0][2]*VWri[12][15][0]))));
        Vpk[13][14][0] = ((.005539*Wpk[13][14][1])+(.051347*Wpk[13][14][2]));
        Vpk[13][14][1] = ((.035902*Wpk[13][14][2])-(.005539*Wpk[13][14][0]));
        Vpk[13][14][2] = -((.035902*Wpk[13][14][1])+(.051347*Wpk[13][14][0]));
        VWri[13][15][0] = (Vpk[13][14][0]+((.018078*Wpk[13][14][1])+(.038*
          Wpk[13][14][2])));
        VWri[13][15][1] = (Vpk[13][14][1]+((.098032*Wpk[13][14][2])-(.018078*
          Wpk[13][14][0])));
        VWri[13][15][2] = (Vpk[13][14][2]-((.038*Wpk[13][14][0])+(.098032*
          Wpk[13][14][1])));
        Vpk[13][15][0] = (((.005139*Wpk[13][15][1])-(.0185*Wpk[13][15][2]))+((
          Cik[15][2][0]*VWri[13][15][2])+((.882947501360837*(VWri[13][15][1]*s15
          ))+(Cik[15][0][0]*VWri[13][15][0]))));
        Vpk[13][15][1] = (((.026917*Wpk[13][15][2])-(.005139*Wpk[13][15][0]))+((
          (VWri[13][15][1]*c15)-(.882947501360837*(VWri[13][15][0]*s15)))-(
          .469471734868729*(VWri[13][15][2]*s15))));
        Vpk[13][15][2] = (((.0185*Wpk[13][15][0])-(.026917*Wpk[13][15][1]))+((
          Cik[15][2][2]*VWri[13][15][2])+((.469471734868729*(VWri[13][15][1]*s15
          ))+(Cik[15][0][2]*VWri[13][15][0]))));
        Vpk[14][14][0] = .000411457536296252;
        Vpk[14][14][1] = -.00646090297985859;
        Vpk[14][14][2] = -.0625600530375351;
        Vpk[14][15][0] = (((.005139*Wpk[14][15][1])-(.0185*Wpk[14][15][2]))+(((
          .00878535823488525*Cik[15][0][0])-(.0234061245523406*s15))-(
          .150110716823594*Cik[15][2][0])));
        Vpk[14][15][1] = (((.026917*Wpk[14][15][2])-(.005139*Wpk[14][15][0]))+((
          .0704727386495611*s15)-((.00775701010205179*s15)+(.026509078417761*c15
          ))));
        Vpk[14][15][2] = (((.0185*Wpk[14][15][0])-(.026917*Wpk[14][15][1]))+(((
          .00878535823488525*Cik[15][0][2])-(.0124452630345575*s15))-(
          .150110716823594*Cik[15][2][2])));
        Vpk[15][15][0] = -.0163345287751755;
        Vpk[15][15][1] = .02617891313962;
        Vpk[15][15][2] = -.00868522709507149;
        Vpk[16][18][0] = (.1715*Wpk[16][18][2]);
        Vpk[16][18][1] = -(.002*Wpk[16][18][2]);
        Vpk[16][18][2] = -((.002*s17)+(.1715*Wpk[16][18][0]));
        VWri[16][19][2] = (Vpk[16][18][2]+((.0033*s17)-(.2294*Wpk[16][18][0])));
        Vpk[16][19][0] = ((.1862*Wpk[16][19][2])+((Cik[19][2][0]*VWri[16][19][2]
          )+((.0013*(Cik[19][1][0]*Wpk[16][18][2]))+(.4009*(Cik[19][0][0]*
          Wpk[16][18][2])))));
        Vpk[16][19][1] = ((Cik[19][2][1]*VWri[16][19][2])+((.0013*(Cik[19][1][1]
          *Wpk[16][18][2]))+(.4009*(Cik[19][0][1]*Wpk[16][18][2]))));
        Vpk[16][19][2] = (((Cik[19][2][2]*VWri[16][19][2])+((.0013*(
          Cik[19][1][2]*Wpk[16][18][2]))+(.4009*(Cik[19][0][2]*Wpk[16][18][2])))
          )-(.1862*Wpk[16][19][0]));
        VWri[16][20][0] = (Vpk[16][19][0]+(.2438*Wpk[16][19][2]));
        VWri[16][20][2] = (Vpk[16][19][2]-(.2438*Wpk[16][19][0]));
        Vpk[16][20][0] = ((Cik[20][2][0]*VWri[16][20][2])+((Cik[20][0][0]*
          VWri[16][20][0])+(Cik[20][1][0]*Vpk[16][19][1])));
        Vpk[16][20][1] = ((Cik[20][2][1]*VWri[16][20][2])+((Cik[20][0][1]*
          VWri[16][20][0])+(Cik[20][1][1]*Vpk[16][19][1])));
        Vpk[16][20][2] = ((Cik[20][2][2]*VWri[16][20][2])+((Cik[20][0][2]*
          VWri[16][20][0])+(Cik[20][1][2]*Vpk[16][19][1])));
        Vpk[16][21][0] = (((.051347*Wpk[16][21][2])-(.005539*Wpk[16][21][1]))+((
          Cik[21][2][0]*Vpk[16][20][2])+((Cik[21][0][0]*Vpk[16][20][0])+(
          Cik[21][1][0]*Vpk[16][20][1]))));
        Vpk[16][21][1] = (((.005539*Wpk[16][21][0])+(.035902*Wpk[16][21][2]))+((
          Cik[21][2][1]*Vpk[16][20][2])+((Cik[21][0][1]*Vpk[16][20][0])+(
          Cik[21][1][1]*Vpk[16][20][1]))));
        Vpk[16][21][2] = (((Cik[21][2][2]*Vpk[16][20][2])+((Cik[21][0][2]*
          Vpk[16][20][0])+(Cik[21][1][2]*Vpk[16][20][1])))-((.035902*
          Wpk[16][21][1])+(.051347*Wpk[16][21][0])));
        VWri[16][22][0] = (Vpk[16][21][0]+((.038*Wpk[16][21][2])-(.018078*
          Wpk[16][21][1])));
        VWri[16][22][1] = (Vpk[16][21][1]+((.018078*Wpk[16][21][0])+(.098032*
          Wpk[16][21][2])));
        VWri[16][22][2] = (Vpk[16][21][2]-((.038*Wpk[16][21][0])+(.098032*
          Wpk[16][21][1])));
        Vpk[16][22][0] = (((Cik[22][2][0]*VWri[16][22][2])+((.882947501360837*(
          VWri[16][22][1]*s22))+(Cik[22][0][0]*VWri[16][22][0])))-((.005139*
          Wpk[16][22][1])+(.0185*Wpk[16][22][2])));
        Vpk[16][22][1] = (((.005139*Wpk[16][22][0])+(.026917*Wpk[16][22][2]))+((
          .469471734868729*(VWri[16][22][2]*s22))+((VWri[16][22][1]*c22)-(
          .882947501360837*(VWri[16][22][0]*s22)))));
        Vpk[16][22][2] = (((.0185*Wpk[16][22][0])-(.026917*Wpk[16][22][1]))+((
          Cik[22][2][2]*VWri[16][22][2])+((Cik[22][0][2]*VWri[16][22][0])-(
          .469471734868729*(VWri[16][22][1]*s22)))));
        Vpk[17][18][0] = (.1715*s18);
        Vpk[17][18][1] = -(.002*s18);
        Vpk[17][18][2] = (.1715*c18);
        Vpk[17][19][0] = ((.1862*Wpk[17][19][2])+((.4009*(Cik[19][2][0]*c18))+((
          .0013*(Cik[19][1][0]*s18))+(.4009*(Cik[19][0][0]*s18)))));
        Vpk[17][19][1] = ((.4009*(Cik[19][2][1]*c18))+((.0013*(Cik[19][1][1]*s18
          ))+(.4009*(Cik[19][0][1]*s18))));
        Vpk[17][19][2] = (((.4009*(Cik[19][2][2]*c18))+((.0013*(Cik[19][1][2]*
          s18))+(.4009*(Cik[19][0][2]*s18))))-(.1862*Wpk[17][19][0]));
        VWri[17][20][0] = (Vpk[17][19][0]+(.2438*Wpk[17][19][2]));
        VWri[17][20][2] = (Vpk[17][19][2]-(.2438*Wpk[17][19][0]));
        Vpk[17][20][0] = ((Cik[20][2][0]*VWri[17][20][2])+((Cik[20][0][0]*
          VWri[17][20][0])+(Cik[20][1][0]*Vpk[17][19][1])));
        Vpk[17][20][1] = ((Cik[20][2][1]*VWri[17][20][2])+((Cik[20][0][1]*
          VWri[17][20][0])+(Cik[20][1][1]*Vpk[17][19][1])));
        Vpk[17][20][2] = ((Cik[20][2][2]*VWri[17][20][2])+((Cik[20][0][2]*
          VWri[17][20][0])+(Cik[20][1][2]*Vpk[17][19][1])));
        Vpk[17][21][0] = (((.051347*Wpk[17][21][2])-(.005539*Wpk[17][21][1]))+((
          Cik[21][2][0]*Vpk[17][20][2])+((Cik[21][0][0]*Vpk[17][20][0])+(
          Cik[21][1][0]*Vpk[17][20][1]))));
        Vpk[17][21][1] = (((.005539*Wpk[17][21][0])+(.035902*Wpk[17][21][2]))+((
          Cik[21][2][1]*Vpk[17][20][2])+((Cik[21][0][1]*Vpk[17][20][0])+(
          Cik[21][1][1]*Vpk[17][20][1]))));
        Vpk[17][21][2] = (((Cik[21][2][2]*Vpk[17][20][2])+((Cik[21][0][2]*
          Vpk[17][20][0])+(Cik[21][1][2]*Vpk[17][20][1])))-((.035902*
          Wpk[17][21][1])+(.051347*Wpk[17][21][0])));
        VWri[17][22][0] = (Vpk[17][21][0]+((.038*Wpk[17][21][2])-(.018078*
          Wpk[17][21][1])));
        VWri[17][22][1] = (Vpk[17][21][1]+((.018078*Wpk[17][21][0])+(.098032*
          Wpk[17][21][2])));
        VWri[17][22][2] = (Vpk[17][21][2]-((.038*Wpk[17][21][0])+(.098032*
          Wpk[17][21][1])));
        Vpk[17][22][0] = (((Cik[22][2][0]*VWri[17][22][2])+((.882947501360837*(
          VWri[17][22][1]*s22))+(Cik[22][0][0]*VWri[17][22][0])))-((.005139*
          Wpk[17][22][1])+(.0185*Wpk[17][22][2])));
        Vpk[17][22][1] = (((.005139*Wpk[17][22][0])+(.026917*Wpk[17][22][2]))+((
          .469471734868729*(VWri[17][22][2]*s22))+((VWri[17][22][1]*c22)-(
          .882947501360837*(VWri[17][22][0]*s22)))));
        Vpk[17][22][2] = (((.0185*Wpk[17][22][0])-(.026917*Wpk[17][22][1]))+((
          Cik[22][2][2]*VWri[17][22][2])+((Cik[22][0][2]*VWri[17][22][0])-(
          .469471734868729*(VWri[17][22][1]*s22)))));
        Vpk[18][18][2] = -.002;
        Vpk[18][19][0] = ((.0013*Cik[19][2][0])-(.1862*Cik[19][1][2]));
        Vpk[18][19][1] = (.0013*Cik[19][2][1]);
        Vpk[18][19][2] = ((.0013*Cik[19][2][2])+(.1862*Cik[19][1][0]));
        VWri[18][20][0] = (Vpk[18][19][0]-(.2438*Cik[19][1][2]));
        VWri[18][20][2] = (Vpk[18][19][2]+(.2438*Cik[19][1][0]));
        Vpk[18][20][0] = ((Cik[20][2][0]*VWri[18][20][2])+((.0013*(Cik[19][2][1]
          *Cik[20][1][0]))+(Cik[20][0][0]*VWri[18][20][0])));
        Vpk[18][20][1] = ((Cik[20][2][1]*VWri[18][20][2])+((.0013*(Cik[19][2][1]
          *Cik[20][1][1]))+(Cik[20][0][1]*VWri[18][20][0])));
        Vpk[18][20][2] = ((Cik[20][2][2]*VWri[18][20][2])+((.0013*(Cik[19][2][1]
          *Cik[20][1][2]))+(Cik[20][0][2]*VWri[18][20][0])));
        Vpk[18][21][0] = (((.051347*Wpk[18][21][2])-(.005539*Wpk[18][21][1]))+((
          Cik[21][2][0]*Vpk[18][20][2])+((Cik[21][0][0]*Vpk[18][20][0])+(
          Cik[21][1][0]*Vpk[18][20][1]))));
        Vpk[18][21][1] = (((.005539*Wpk[18][21][0])+(.035902*Wpk[18][21][2]))+((
          Cik[21][2][1]*Vpk[18][20][2])+((Cik[21][0][1]*Vpk[18][20][0])+(
          Cik[21][1][1]*Vpk[18][20][1]))));
        Vpk[18][21][2] = (((Cik[21][2][2]*Vpk[18][20][2])+((Cik[21][0][2]*
          Vpk[18][20][0])+(Cik[21][1][2]*Vpk[18][20][1])))-((.035902*
          Wpk[18][21][1])+(.051347*Wpk[18][21][0])));
        VWri[18][22][0] = (Vpk[18][21][0]+((.038*Wpk[18][21][2])-(.018078*
          Wpk[18][21][1])));
        VWri[18][22][1] = (Vpk[18][21][1]+((.018078*Wpk[18][21][0])+(.098032*
          Wpk[18][21][2])));
        VWri[18][22][2] = (Vpk[18][21][2]-((.038*Wpk[18][21][0])+(.098032*
          Wpk[18][21][1])));
        Vpk[18][22][0] = (((Cik[22][2][0]*VWri[18][22][2])+((.882947501360837*(
          VWri[18][22][1]*s22))+(Cik[22][0][0]*VWri[18][22][0])))-((.005139*
          Wpk[18][22][1])+(.0185*Wpk[18][22][2])));
        Vpk[18][22][1] = (((.005139*Wpk[18][22][0])+(.026917*Wpk[18][22][2]))+((
          .469471734868729*(VWri[18][22][2]*s22))+((VWri[18][22][1]*c22)-(
          .882947501360837*(VWri[18][22][0]*s22)))));
        Vpk[18][22][2] = (((.0185*Wpk[18][22][0])-(.026917*Wpk[18][22][1]))+((
          Cik[22][2][2]*VWri[18][22][2])+((Cik[22][0][2]*VWri[18][22][0])-(
          .469471734868729*(VWri[18][22][1]*s22)))));
        Vpk[19][19][0] = .185436609363333;
        Vpk[19][19][2] = -.0150652581855386;
        Vpk[19][20][0] = ((.42823706781006*Cik[20][0][0])-(.0347908755090312*
          Cik[20][2][0]));
        Vpk[19][20][1] = ((.42823706781006*Cik[20][0][1])-(.0347908755090312*
          Cik[20][2][1]));
        Vpk[19][20][2] = ((.42823706781006*Cik[20][0][2])-(.0347908755090312*
          Cik[20][2][2]));
        Vpk[19][21][0] = (((.051347*Wpk[19][21][2])-(.005539*Wpk[19][21][1]))+((
          Cik[21][2][0]*Vpk[19][20][2])+((Cik[21][0][0]*Vpk[19][20][0])+(
          Cik[21][1][0]*Vpk[19][20][1]))));
        Vpk[19][21][1] = (((.005539*Wpk[19][21][0])+(.035902*Wpk[19][21][2]))+((
          Cik[21][2][1]*Vpk[19][20][2])+((Cik[21][0][1]*Vpk[19][20][0])+(
          Cik[21][1][1]*Vpk[19][20][1]))));
        Vpk[19][21][2] = (((Cik[21][2][2]*Vpk[19][20][2])+((Cik[21][0][2]*
          Vpk[19][20][0])+(Cik[21][1][2]*Vpk[19][20][1])))-((.035902*
          Wpk[19][21][1])+(.051347*Wpk[19][21][0])));
        VWri[19][22][0] = (Vpk[19][21][0]+((.038*Wpk[19][21][2])-(.018078*
          Wpk[19][21][1])));
        VWri[19][22][1] = (Vpk[19][21][1]+((.018078*Wpk[19][21][0])+(.098032*
          Wpk[19][21][2])));
        VWri[19][22][2] = (Vpk[19][21][2]-((.038*Wpk[19][21][0])+(.098032*
          Wpk[19][21][1])));
        Vpk[19][22][0] = (((Cik[22][2][0]*VWri[19][22][2])+((.882947501360837*(
          VWri[19][22][1]*s22))+(Cik[22][0][0]*VWri[19][22][0])))-((.005139*
          Wpk[19][22][1])+(.0185*Wpk[19][22][2])));
        Vpk[19][22][1] = (((.005139*Wpk[19][22][0])+(.026917*Wpk[19][22][2]))+((
          .469471734868729*(VWri[19][22][2]*s22))+((VWri[19][22][1]*c22)-(
          .882947501360837*(VWri[19][22][0]*s22)))));
        Vpk[19][22][2] = (((.0185*Wpk[19][22][0])-(.026917*Wpk[19][22][1]))+((
          Cik[22][2][2]*VWri[19][22][2])+((Cik[22][0][2]*VWri[19][22][0])-(
          .469471734868729*(VWri[19][22][1]*s22)))));
        Vpk[20][21][0] = ((.051347*Wpk[20][21][2])-(.005539*Wpk[20][21][1]));
        Vpk[20][21][1] = ((.005539*Wpk[20][21][0])+(.035902*Wpk[20][21][2]));
        Vpk[20][21][2] = -((.035902*Wpk[20][21][1])+(.051347*Wpk[20][21][0]));
        VWri[20][22][0] = (Vpk[20][21][0]+((.038*Wpk[20][21][2])-(.018078*
          Wpk[20][21][1])));
        VWri[20][22][1] = (Vpk[20][21][1]+((.018078*Wpk[20][21][0])+(.098032*
          Wpk[20][21][2])));
        VWri[20][22][2] = (Vpk[20][21][2]-((.038*Wpk[20][21][0])+(.098032*
          Wpk[20][21][1])));
        Vpk[20][22][0] = (((Cik[22][2][0]*VWri[20][22][2])+((.882947501360837*(
          VWri[20][22][1]*s22))+(Cik[22][0][0]*VWri[20][22][0])))-((.005139*
          Wpk[20][22][1])+(.0185*Wpk[20][22][2])));
        Vpk[20][22][1] = (((.005139*Wpk[20][22][0])+(.026917*Wpk[20][22][2]))+((
          .469471734868729*(VWri[20][22][2]*s22))+((VWri[20][22][1]*c22)-(
          .882947501360837*(VWri[20][22][0]*s22)))));
        Vpk[20][22][2] = (((.0185*Wpk[20][22][0])-(.026917*Wpk[20][22][1]))+((
          Cik[22][2][2]*VWri[20][22][2])+((Cik[22][0][2]*VWri[20][22][0])-(
          .469471734868729*(VWri[20][22][1]*s22)))));
        Vpk[21][21][0] = .000411457536296252;
        Vpk[21][21][1] = -.00646090297985859;
        Vpk[21][21][2] = .0625600530375351;
        Vpk[21][22][0] = (((.150110716823594*Cik[22][2][0])+((.00878535823488525
          *Cik[22][0][0])-(.0234061245523406*s22)))-((.005139*Wpk[21][22][1])+(
          .0185*Wpk[21][22][2])));
        Vpk[21][22][1] = (((.005139*Wpk[21][22][0])+(.026917*Wpk[21][22][2]))+((
          .0704727386495611*s22)-((.00775701010205179*s22)+(.026509078417761*c22
          ))));
        Vpk[21][22][2] = (((.0185*Wpk[21][22][0])-(.026917*Wpk[21][22][1]))+((
          .150110716823594*Cik[22][2][2])+((.00878535823488525*Cik[22][0][2])+(
          .0124452630345575*s22))));
        Vpk[22][22][0] = -.0163345287751755;
        Vpk[22][22][1] = .02617891313962;
        Vpk[22][22][2] = .00868522709507149;
        vpkflg = 1;
    }
/*
 Used 0.62 seconds CPU time,
 98304 additional bytes of memory.
 Equations contain 1356 adds/subtracts/negates
                   2106 multiplies
                      0 divides
                    862 assignments
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
        Otk[6][0] = (u[6]*wk[6][1]);
        Otk[6][1] = -(u[6]*wk[6][0]);
        Otk[7][1] = ((Otk[6][1]*c7)+(u[7]*wk[7][2]));
        Otk[7][2] = -((Otk[6][1]*s7)+(u[7]*wk[7][1]));
        Otk[8][0] = (((Otk[6][0]*c8)-(Otk[7][2]*s8))-(u[8]*wk[8][2]));
        Otk[8][2] = ((u[8]*wk[8][0])+((Otk[6][0]*s8)+(Otk[7][2]*c8)));
        Otk[9][0] = (u[9]*wk[9][1]);
        Otk[9][1] = -(u[9]*wk[9][0]);
        Otk[10][1] = ((Otk[9][1]*c10)+(u[10]*wk[10][2]));
        Otk[10][2] = -((Otk[9][1]*s10)+(u[10]*wk[10][1]));
        Otk[11][0] = (((Otk[9][0]*c11)-(Otk[10][2]*s11))-(u[11]*wk[11][2]));
        Otk[11][2] = ((u[11]*wk[11][0])+((Otk[9][0]*s11)+(Otk[10][2]*c11)));
        Otk[12][0] = (((.995900157697815*(u[12]*wk[12][1]))-(.0404550064059294*(
          u[12]*wk[12][2])))+((Cik[12][2][0]*Otk[11][2])+((Cik[12][0][0]*
          Otk[11][0])+(Cik[12][1][0]*Otk[10][1]))));
        Otk[12][1] = (((Cik[12][2][1]*Otk[11][2])+((Cik[12][0][1]*Otk[11][0])+(
          Cik[12][1][1]*Otk[10][1])))-((.0809090128117004*(u[12]*wk[12][2]))+(
          .995900157697815*(u[12]*wk[12][0]))));
        Otk[12][2] = (((.0404550064059294*(u[12]*wk[12][0]))+(.0809090128117004*
          (u[12]*wk[12][1])))+((Cik[12][2][2]*Otk[11][2])+((Cik[12][0][2]*
          Otk[11][0])+(Cik[12][1][2]*Otk[10][1]))));
        Otk[13][0] = (((.0372090059839342*(u[13]*wk[13][2]))+(.995922160163717*(
          u[13]*wk[13][1])))+((Cik[13][2][0]*Otk[12][2])+((Cik[13][0][0]*
          Otk[12][0])+(Cik[13][1][0]*Otk[12][1]))));
        Otk[13][1] = (((Cik[13][2][1]*Otk[12][2])+((Cik[13][0][1]*Otk[12][0])+(
          Cik[13][1][1]*Otk[12][1])))-((.0821860132171146*(u[13]*wk[13][2]))+(
          .995922160163717*(u[13]*wk[13][0]))));
        Otk[13][2] = (((.0821860132171146*(u[13]*wk[13][1]))-(.0372090059839342*
          (u[13]*wk[13][0])))+((Cik[13][2][2]*Otk[12][2])+((Cik[13][0][2]*
          Otk[12][0])+(Cik[13][1][2]*Otk[12][1]))));
        Otk[14][0] = (((Cik[14][2][0]*Otk[13][2])+((Cik[14][0][0]*Otk[13][0])+(
          Cik[14][1][0]*Otk[13][1])))-((.0542579897533796*(u[14]*wk[14][1]))+(
          .57725989098448*(u[14]*wk[14][2]))));
        Otk[14][1] = (((.0542579897533796*(u[14]*wk[14][0]))+(.814755846133373*(
          u[14]*wk[14][2])))+((Cik[14][2][1]*Otk[13][2])+((Cik[14][0][1]*
          Otk[13][0])+(Cik[14][1][1]*Otk[13][1]))));
        Otk[14][2] = (((.57725989098448*(u[14]*wk[14][0]))-(.814755846133373*(
          u[14]*wk[14][1])))+((Cik[14][2][2]*Otk[13][2])+((Cik[14][0][2]*
          Otk[13][0])+(Cik[14][1][2]*Otk[13][1]))));
        Otk[15][0] = ((.882947501360837*(u[15]*wk[15][1]))+((Cik[15][2][0]*
          Otk[14][2])+((.882947501360837*(Otk[14][1]*s15))+(Cik[15][0][0]*
          Otk[14][0]))));
        Otk[15][1] = ((((Otk[14][1]*c15)-(.882947501360837*(Otk[14][0]*s15)))-(
          .469471734868729*(Otk[14][2]*s15)))-((.469471734868729*(u[15]*
          wk[15][2]))+(.882947501360837*(u[15]*wk[15][0]))));
        Otk[15][2] = ((.469471734868729*(u[15]*wk[15][1]))+((Cik[15][2][2]*
          Otk[14][2])+((.469471734868729*(Otk[14][1]*s15))+(Cik[15][0][2]*
          Otk[14][0]))));
        Otk[16][0] = (u[16]*wk[16][1]);
        Otk[16][1] = -(u[16]*wk[16][0]);
        Otk[17][1] = ((Otk[16][1]*c17)-(u[17]*wk[17][2]));
        Otk[17][2] = ((Otk[16][1]*s17)+(u[17]*wk[17][1]));
        Otk[18][0] = ((u[18]*wk[18][2])+((Otk[16][0]*c18)+(Otk[17][2]*s18)));
        Otk[18][2] = (((Otk[17][2]*c18)-(Otk[16][0]*s18))-(u[18]*wk[18][0]));
        Otk[19][0] = (((.0404550064059294*(u[19]*wk[19][2]))+(.995900157697815*(
          u[19]*wk[19][1])))+((Cik[19][2][0]*Otk[18][2])+((Cik[19][0][0]*
          Otk[18][0])+(Cik[19][1][0]*Otk[17][1]))));
        Otk[19][1] = (((.0809090128117004*(u[19]*wk[19][2]))-(.995900157697815*(
          u[19]*wk[19][0])))+((Cik[19][2][1]*Otk[18][2])+((Cik[19][0][1]*
          Otk[18][0])+(Cik[19][1][1]*Otk[17][1]))));
        Otk[19][2] = (((Cik[19][2][2]*Otk[18][2])+((Cik[19][0][2]*Otk[18][0])+(
          Cik[19][1][2]*Otk[17][1])))-((.0404550064059294*(u[19]*wk[19][0]))+(
          .0809090128117004*(u[19]*wk[19][1]))));
        Otk[20][0] = (((.995922160163717*(u[20]*wk[20][1]))-(.0372090059839342*(
          u[20]*wk[20][2])))+((Cik[20][2][0]*Otk[19][2])+((Cik[20][0][0]*
          Otk[19][0])+(Cik[20][1][0]*Otk[19][1]))));
        Otk[20][1] = (((.0821860132171146*(u[20]*wk[20][2]))-(.995922160163717*(
          u[20]*wk[20][0])))+((Cik[20][2][1]*Otk[19][2])+((Cik[20][0][1]*
          Otk[19][0])+(Cik[20][1][1]*Otk[19][1]))));
        Otk[20][2] = (((.0372090059839342*(u[20]*wk[20][0]))-(.0821860132171146*
          (u[20]*wk[20][1])))+((Cik[20][2][2]*Otk[19][2])+((Cik[20][0][2]*
          Otk[19][0])+(Cik[20][1][2]*Otk[19][1]))));
        Otk[21][0] = (((.57725989098448*(u[21]*wk[21][2]))-(.0542579897533796*(
          u[21]*wk[21][1])))+((Cik[21][2][0]*Otk[20][2])+((Cik[21][0][0]*
          Otk[20][0])+(Cik[21][1][0]*Otk[20][1]))));
        Otk[21][1] = (((.0542579897533796*(u[21]*wk[21][0]))-(.814755846133373*(
          u[21]*wk[21][2])))+((Cik[21][2][1]*Otk[20][2])+((Cik[21][0][1]*
          Otk[20][0])+(Cik[21][1][1]*Otk[20][1]))));
        Otk[21][2] = (((.814755846133373*(u[21]*wk[21][1]))-(.57725989098448*(
          u[21]*wk[21][0])))+((Cik[21][2][2]*Otk[20][2])+((Cik[21][0][2]*
          Otk[20][0])+(Cik[21][1][2]*Otk[20][1]))));
        Otk[22][0] = ((.882947501360837*(u[22]*wk[22][1]))+((Cik[22][2][0]*
          Otk[21][2])+((.882947501360837*(Otk[21][1]*s22))+(Cik[22][0][0]*
          Otk[21][0]))));
        Otk[22][1] = (((.469471734868729*(Otk[21][2]*s22))+((Otk[21][1]*c22)-(
          .882947501360837*(Otk[21][0]*s22))))+((.469471734868729*(u[22]*
          wk[22][2]))-(.882947501360837*(u[22]*wk[22][0]))));
        Otk[22][2] = (((Cik[22][2][2]*Otk[21][2])+((Cik[22][0][2]*Otk[21][0])-(
          .469471734868729*(Otk[21][1]*s22))))-(.469471734868729*(u[22]*
          wk[22][1])));
/*
Compute Atk (inertial linear acceleration)
*/
        AiOiWi[6][0] = (.127*(u[3]*u[4]));
        AiOiWi[6][1] = -(.127*((u[3]*u[3])+(u[5]*u[5])));
        AiOiWi[6][2] = (.127*(u[4]*u[5]));
        Atk[6][0] = ((AiOiWi[6][0]*c6)+(AiOiWi[6][1]*s6));
        Atk[6][1] = ((AiOiWi[6][1]*c6)-(AiOiWi[6][0]*s6));
        Atk[7][1] = ((AiOiWi[6][2]*s7)+(Atk[6][1]*c7));
        Atk[7][2] = ((AiOiWi[6][2]*c7)-(Atk[6][1]*s7));
        Atk[8][0] = ((.3202*((wk[8][0]*wk[8][1])-Otk[8][2]))+((Atk[6][0]*c8)-(
          Atk[7][2]*s8)));
        Atk[8][1] = (Atk[7][1]-(.3202*((wk[8][0]*wk[8][0])+(wk[8][2]*wk[8][2])))
          );
        Atk[8][2] = ((.3202*(Otk[8][0]+(wk[8][1]*wk[8][2])))+((Atk[6][0]*s8)+(
          Atk[7][2]*c8)));
        AiOiWi[9][0] = ((.0935*(u[3]*u[5]))-(.07*(u[3]*u[4])));
        AiOiWi[9][1] = ((.07*(u[3]*u[3]))+(u[5]*Wirk[9][0]));
        AiOiWi[9][2] = -((.0935*(u[3]*u[3]))+(u[4]*Wirk[9][0]));
        Atk[9][0] = ((AiOiWi[9][0]*c9)+(AiOiWi[9][1]*s9));
        Atk[9][1] = ((AiOiWi[9][1]*c9)-(AiOiWi[9][0]*s9));
        Atk[10][1] = ((AiOiWi[9][2]*s10)+(Atk[9][1]*c10));
        Atk[10][2] = ((AiOiWi[9][2]*c10)-(Atk[9][1]*s10));
        Atk[11][0] = (((.1715*Otk[11][2])+((.002*(wk[11][2]*wk[11][2]))+(
          wk[11][1]*Wkrpk[11][2])))+((Atk[9][0]*c11)-(Atk[10][2]*s11)));
        Atk[11][1] = (Atk[10][1]+(((.1715*(wk[11][2]*wk[11][2]))-(wk[11][0]*
          Wkrpk[11][2]))-(.002*Otk[11][2])));
        Atk[11][2] = (((Atk[9][0]*s11)+(Atk[10][2]*c11))+(((.002*Otk[10][1])-(
          .1715*Otk[11][0]))-((.002*(wk[11][0]*wk[11][2]))+(.1715*(wk[11][1]*
          wk[11][2])))));
        AiOiWi[12][0] = (Atk[11][0]+((.2294*Otk[11][2])+((Wirk[12][2]*wk[11][1])
          -(.0033*(wk[11][2]*wk[11][2])))));
        AiOiWi[12][1] = (Atk[11][1]+((.0033*Otk[11][2])+((.2294*(wk[11][2]*
          wk[11][2]))-(Wirk[12][2]*wk[11][0]))));
        AiOiWi[12][2] = (Atk[11][2]+(((.0033*(wk[11][0]*wk[11][2]))-(.2294*(
          wk[11][1]*wk[11][2])))-((.0033*Otk[10][1])+(.2294*Otk[11][0]))));
        Atk[12][0] = ((.1862*(Otk[12][2]-(wk[12][0]*wk[12][1])))+((AiOiWi[12][2]
          *Cik[12][2][0])+((AiOiWi[12][0]*Cik[12][0][0])+(AiOiWi[12][1]*
          Cik[12][1][0]))));
        Atk[12][1] = ((.1862*((wk[12][0]*wk[12][0])+(wk[12][2]*wk[12][2])))+((
          AiOiWi[12][2]*Cik[12][2][1])+((AiOiWi[12][0]*Cik[12][0][1])+(
          AiOiWi[12][1]*Cik[12][1][1]))));
        Atk[12][2] = (((AiOiWi[12][2]*Cik[12][2][2])+((AiOiWi[12][0]*
          Cik[12][0][2])+(AiOiWi[12][1]*Cik[12][1][2])))-(.1862*(Otk[12][0]+(
          wk[12][1]*wk[12][2]))));
        AiOiWi[13][0] = (Atk[12][0]+(.2438*(Otk[12][2]-(wk[12][0]*wk[12][1]))));
        AiOiWi[13][1] = (Atk[12][1]+(.2438*((wk[12][0]*wk[12][0])+(wk[12][2]*
          wk[12][2]))));
        AiOiWi[13][2] = (Atk[12][2]-(.2438*(Otk[12][0]+(wk[12][1]*wk[12][2]))));
        Atk[13][0] = ((AiOiWi[13][2]*Cik[13][2][0])+((AiOiWi[13][0]*
          Cik[13][0][0])+(AiOiWi[13][1]*Cik[13][1][0])));
        Atk[13][1] = ((AiOiWi[13][2]*Cik[13][2][1])+((AiOiWi[13][0]*
          Cik[13][0][1])+(AiOiWi[13][1]*Cik[13][1][1])));
        Atk[13][2] = ((AiOiWi[13][2]*Cik[13][2][2])+((AiOiWi[13][0]*
          Cik[13][0][2])+(AiOiWi[13][1]*Cik[13][1][2])));
        Atk[14][0] = (((Atk[13][2]*Cik[14][2][0])+((Atk[13][0]*Cik[14][0][0])+(
          Atk[13][1]*Cik[14][1][0])))+(((.005539*Otk[14][1])+(.051347*Otk[14][2]
          ))+((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*Wkrpk[14][1]))));
        Atk[14][1] = (((Atk[13][2]*Cik[14][2][1])+((Atk[13][0]*Cik[14][0][1])+(
          Atk[13][1]*Cik[14][1][1])))+(((.035902*Otk[14][2])-(.005539*Otk[14][0]
          ))+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*Wkrpk[14][2]))));
        Atk[14][2] = (((Atk[13][2]*Cik[14][2][2])+((Atk[13][0]*Cik[14][0][2])+(
          Atk[13][1]*Cik[14][1][2])))+(((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*
          Wkrpk[14][0]))-((.035902*Otk[14][1])+(.051347*Otk[14][0]))));
        AiOiWi[15][0] = (Atk[14][0]+(((.018078*Otk[14][1])+(.038*Otk[14][2]))+((
          Wirk[15][2]*wk[14][1])-(Wirk[15][1]*wk[14][2]))));
        AiOiWi[15][1] = (Atk[14][1]+(((.098032*Otk[14][2])-(.018078*Otk[14][0]))
          +((Wirk[15][0]*wk[14][2])-(Wirk[15][2]*wk[14][0]))));
        AiOiWi[15][2] = (Atk[14][2]+(((Wirk[15][1]*wk[14][0])-(Wirk[15][0]*
          wk[14][1]))-((.038*Otk[14][0])+(.098032*Otk[14][1]))));
        Atk[15][0] = (((AiOiWi[15][2]*Cik[15][2][0])+((.882947501360837*(
          AiOiWi[15][1]*s15))+(AiOiWi[15][0]*Cik[15][0][0])))+(((.005139*
          Otk[15][1])-(.0185*Otk[15][2]))+((wk[15][1]*Wkrpk[15][2])-(wk[15][2]*
          Wkrpk[15][1]))));
        Atk[15][1] = ((((.026917*Otk[15][2])-(.005139*Otk[15][0]))+((wk[15][2]*
          Wkrpk[15][0])-(wk[15][0]*Wkrpk[15][2])))+(((AiOiWi[15][1]*c15)-(
          .882947501360837*(AiOiWi[15][0]*s15)))-(.469471734868729*(
          AiOiWi[15][2]*s15))));
        Atk[15][2] = (((AiOiWi[15][2]*Cik[15][2][2])+((.469471734868729*(
          AiOiWi[15][1]*s15))+(AiOiWi[15][0]*Cik[15][0][2])))+(((.0185*
          Otk[15][0])-(.026917*Otk[15][1]))+((wk[15][0]*Wkrpk[15][1])-(wk[15][1]
          *Wkrpk[15][0]))));
        AiOiWi[16][0] = -((.07*(u[3]*u[4]))+(.0935*(u[3]*u[5])));
        AiOiWi[16][1] = ((.07*(u[3]*u[3]))+(u[5]*Wirk[16][0]));
        AiOiWi[16][2] = ((.0935*(u[3]*u[3]))-(u[4]*Wirk[16][0]));
        Atk[16][0] = ((AiOiWi[16][0]*c16)+(AiOiWi[16][1]*s16));
        Atk[16][1] = ((AiOiWi[16][1]*c16)-(AiOiWi[16][0]*s16));
        Atk[17][1] = ((Atk[16][1]*c17)-(AiOiWi[16][2]*s17));
        Atk[17][2] = ((AiOiWi[16][2]*c17)+(Atk[16][1]*s17));
        Atk[18][0] = (((.1715*Otk[18][2])+((.002*(wk[18][2]*wk[18][2]))+(
          wk[18][1]*Wkrpk[18][2])))+((Atk[16][0]*c18)+(Atk[17][2]*s18)));
        Atk[18][1] = (Atk[17][1]+(((.1715*(wk[18][2]*wk[18][2]))-(wk[18][0]*
          Wkrpk[18][2]))-(.002*Otk[18][2])));
        Atk[18][2] = (((Atk[17][2]*c18)-(Atk[16][0]*s18))+(((.002*Otk[17][1])-(
          .1715*Otk[18][0]))-((.002*(wk[18][0]*wk[18][2]))+(.1715*(wk[18][1]*
          wk[18][2])))));
        AiOiWi[19][0] = (Atk[18][0]+((.2294*Otk[18][2])+((Wirk[19][2]*wk[18][1])
          -(.0033*(wk[18][2]*wk[18][2])))));
        AiOiWi[19][1] = (Atk[18][1]+((.0033*Otk[18][2])+((.2294*(wk[18][2]*
          wk[18][2]))-(Wirk[19][2]*wk[18][0]))));
        AiOiWi[19][2] = (Atk[18][2]+(((.0033*(wk[18][0]*wk[18][2]))-(.2294*(
          wk[18][1]*wk[18][2])))-((.0033*Otk[17][1])+(.2294*Otk[18][0]))));
        Atk[19][0] = ((.1862*(Otk[19][2]-(wk[19][0]*wk[19][1])))+((AiOiWi[19][2]
          *Cik[19][2][0])+((AiOiWi[19][0]*Cik[19][0][0])+(AiOiWi[19][1]*
          Cik[19][1][0]))));
        Atk[19][1] = ((.1862*((wk[19][0]*wk[19][0])+(wk[19][2]*wk[19][2])))+((
          AiOiWi[19][2]*Cik[19][2][1])+((AiOiWi[19][0]*Cik[19][0][1])+(
          AiOiWi[19][1]*Cik[19][1][1]))));
        Atk[19][2] = (((AiOiWi[19][2]*Cik[19][2][2])+((AiOiWi[19][0]*
          Cik[19][0][2])+(AiOiWi[19][1]*Cik[19][1][2])))-(.1862*(Otk[19][0]+(
          wk[19][1]*wk[19][2]))));
        AiOiWi[20][0] = (Atk[19][0]+(.2438*(Otk[19][2]-(wk[19][0]*wk[19][1]))));
        AiOiWi[20][1] = (Atk[19][1]+(.2438*((wk[19][0]*wk[19][0])+(wk[19][2]*
          wk[19][2]))));
        AiOiWi[20][2] = (Atk[19][2]-(.2438*(Otk[19][0]+(wk[19][1]*wk[19][2]))));
        Atk[20][0] = ((AiOiWi[20][2]*Cik[20][2][0])+((AiOiWi[20][0]*
          Cik[20][0][0])+(AiOiWi[20][1]*Cik[20][1][0])));
        Atk[20][1] = ((AiOiWi[20][2]*Cik[20][2][1])+((AiOiWi[20][0]*
          Cik[20][0][1])+(AiOiWi[20][1]*Cik[20][1][1])));
        Atk[20][2] = ((AiOiWi[20][2]*Cik[20][2][2])+((AiOiWi[20][0]*
          Cik[20][0][2])+(AiOiWi[20][1]*Cik[20][1][2])));
        Atk[21][0] = (((Atk[20][2]*Cik[21][2][0])+((Atk[20][0]*Cik[21][0][0])+(
          Atk[20][1]*Cik[21][1][0])))+(((.051347*Otk[21][2])-(.005539*Otk[21][1]
          ))+((wk[21][1]*Wkrpk[21][2])-(wk[21][2]*Wkrpk[21][1]))));
        Atk[21][1] = (((Atk[20][2]*Cik[21][2][1])+((Atk[20][0]*Cik[21][0][1])+(
          Atk[20][1]*Cik[21][1][1])))+(((.005539*Otk[21][0])+(.035902*Otk[21][2]
          ))+((wk[21][2]*Wkrpk[21][0])-(wk[21][0]*Wkrpk[21][2]))));
        Atk[21][2] = (((Atk[20][2]*Cik[21][2][2])+((Atk[20][0]*Cik[21][0][2])+(
          Atk[20][1]*Cik[21][1][2])))+(((wk[21][0]*Wkrpk[21][1])-(wk[21][1]*
          Wkrpk[21][0]))-((.035902*Otk[21][1])+(.051347*Otk[21][0]))));
        AiOiWi[22][0] = (Atk[21][0]+(((.038*Otk[21][2])-(.018078*Otk[21][1]))+((
          Wirk[22][2]*wk[21][1])-(Wirk[22][1]*wk[21][2]))));
        AiOiWi[22][1] = (Atk[21][1]+(((.018078*Otk[21][0])+(.098032*Otk[21][2]))
          +((Wirk[22][0]*wk[21][2])-(Wirk[22][2]*wk[21][0]))));
        AiOiWi[22][2] = (Atk[21][2]+(((Wirk[22][1]*wk[21][0])-(Wirk[22][0]*
          wk[21][1]))-((.038*Otk[21][0])+(.098032*Otk[21][1]))));
        Atk[22][0] = (((AiOiWi[22][2]*Cik[22][2][0])+((.882947501360837*(
          AiOiWi[22][1]*s22))+(AiOiWi[22][0]*Cik[22][0][0])))+(((wk[22][1]*
          Wkrpk[22][2])-(wk[22][2]*Wkrpk[22][1]))-((.005139*Otk[22][1])+(.0185*
          Otk[22][2]))));
        Atk[22][1] = (((.469471734868729*(AiOiWi[22][2]*s22))+((AiOiWi[22][1]*
          c22)-(.882947501360837*(AiOiWi[22][0]*s22))))+(((.005139*Otk[22][0])+(
          .026917*Otk[22][2]))+((wk[22][2]*Wkrpk[22][0])-(wk[22][0]*Wkrpk[22][2]
          ))));
        Atk[22][2] = (((AiOiWi[22][2]*Cik[22][2][2])+((AiOiWi[22][0]*
          Cik[22][0][2])-(.469471734868729*(AiOiWi[22][1]*s22))))+(((.0185*
          Otk[22][0])-(.026917*Otk[22][1]))+((wk[22][0]*Wkrpk[22][1])-(wk[22][1]
          *Wkrpk[22][0]))));
        inerflg = 1;
    }
/*
 Used 0.11 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain  333 adds/subtracts/negates
                    510 multiplies
                      0 divides
                    114 assignments
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
        Fstar[5][0] = -(ufk[0][0]+(11.15*gk[3][0]));
        Fstar[5][1] = -(ufk[0][1]+(11.15*gk[3][1]));
        Fstar[5][2] = -(ufk[0][2]+(11.15*gk[3][2]));
        Fstar[8][0] = ((32.413*(Atk[8][0]-gk[8][0]))-ufk[1][0]);
        Fstar[8][1] = ((32.413*(Atk[8][1]-gk[7][1]))-ufk[1][1]);
        Fstar[8][2] = ((32.413*(Atk[8][2]-gk[8][2]))-ufk[1][2]);
        Fstar[11][0] = ((8.806*(Atk[11][0]-gk[11][0]))-ufk[2][0]);
        Fstar[11][1] = ((8.806*(Atk[11][1]-gk[10][1]))-ufk[2][1]);
        Fstar[11][2] = ((8.806*(Atk[11][2]-gk[11][2]))-ufk[2][2]);
        Fstar[12][0] = ((3.51*(Atk[12][0]-gk[12][0]))-ufk[3][0]);
        Fstar[12][1] = ((3.51*(Atk[12][1]-gk[12][1]))-ufk[3][1]);
        Fstar[12][2] = ((3.51*(Atk[12][2]-gk[12][2]))-ufk[3][2]);
        Fstar[14][0] = ((1.2*(Atk[14][0]-gk[14][0]))-ufk[4][0]);
        Fstar[14][1] = ((1.2*(Atk[14][1]-gk[14][1]))-ufk[4][1]);
        Fstar[14][2] = ((1.2*(Atk[14][2]-gk[14][2]))-ufk[4][2]);
        Fstar[15][0] = ((.205126*(Atk[15][0]-gk[15][0]))-ufk[5][0]);
        Fstar[15][1] = ((.205126*(Atk[15][1]-gk[15][1]))-ufk[5][1]);
        Fstar[15][2] = ((.205126*(Atk[15][2]-gk[15][2]))-ufk[5][2]);
        Fstar[18][0] = ((8.806*(Atk[18][0]-gk[18][0]))-ufk[6][0]);
        Fstar[18][1] = ((8.806*(Atk[18][1]-gk[17][1]))-ufk[6][1]);
        Fstar[18][2] = ((8.806*(Atk[18][2]-gk[18][2]))-ufk[6][2]);
        Fstar[19][0] = ((3.51*(Atk[19][0]-gk[19][0]))-ufk[7][0]);
        Fstar[19][1] = ((3.51*(Atk[19][1]-gk[19][1]))-ufk[7][1]);
        Fstar[19][2] = ((3.51*(Atk[19][2]-gk[19][2]))-ufk[7][2]);
        Fstar[21][0] = ((1.2*(Atk[21][0]-gk[21][0]))-ufk[8][0]);
        Fstar[21][1] = ((1.2*(Atk[21][1]-gk[21][1]))-ufk[8][1]);
        Fstar[21][2] = ((1.2*(Atk[21][2]-gk[21][2]))-ufk[8][2]);
        Fstar[22][0] = ((.205126*(Atk[22][0]-gk[22][0]))-ufk[9][0]);
        Fstar[22][1] = ((.205126*(Atk[22][1]-gk[22][1]))-ufk[9][1]);
        Fstar[22][2] = ((.205126*(Atk[22][2]-gk[22][2]))-ufk[9][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = (WkIkWk[5][0]-utk[0][0]);
        Tstar[5][1] = (WkIkWk[5][1]-utk[0][1]);
        Tstar[5][2] = (WkIkWk[5][2]-utk[0][2]);
        Tstar[8][0] = ((WkIkWk[8][0]+(1.396*Otk[8][0]))-utk[1][0]);
        Tstar[8][1] = ((WkIkWk[8][1]+(.7153*Otk[7][1]))-utk[1][1]);
        Tstar[8][2] = ((WkIkWk[8][2]+(1.3552*Otk[8][2]))-utk[1][2]);
        Tstar[11][0] = ((WkIkWk[11][0]+(.1268*Otk[11][0]))-utk[2][0]);
        Tstar[11][1] = ((WkIkWk[11][1]+(.0332*Otk[10][1]))-utk[2][1]);
        Tstar[11][2] = ((WkIkWk[11][2]+(.1337*Otk[11][2]))-utk[2][2]);
        Tstar[12][0] = ((WkIkWk[12][0]+(.0477*Otk[12][0]))-utk[3][0]);
        Tstar[12][1] = ((WkIkWk[12][1]+(.0048*Otk[12][1]))-utk[3][1]);
        Tstar[12][2] = ((WkIkWk[12][2]+(.0484*Otk[12][2]))-utk[3][2]);
        Tstar[14][0] = ((WkIkWk[14][0]+(.001361*Otk[14][0]))-utk[4][0]);
        Tstar[14][1] = ((WkIkWk[14][1]+(.003709*Otk[14][1]))-utk[4][1]);
        Tstar[14][2] = ((WkIkWk[14][2]+(.003916*Otk[14][2]))-utk[4][2]);
        Tstar[15][0] = ((WkIkWk[15][0]+(.000117*Otk[15][0]))-utk[5][0]);
        Tstar[15][1] = ((WkIkWk[15][1]+(.000179*Otk[15][1]))-utk[5][1]);
        Tstar[15][2] = ((WkIkWk[15][2]+(.000119*Otk[15][2]))-utk[5][2]);
        Tstar[18][0] = ((WkIkWk[18][0]+(.1268*Otk[18][0]))-utk[6][0]);
        Tstar[18][1] = ((WkIkWk[18][1]+(.0332*Otk[17][1]))-utk[6][1]);
        Tstar[18][2] = ((WkIkWk[18][2]+(.1337*Otk[18][2]))-utk[6][2]);
        Tstar[19][0] = ((WkIkWk[19][0]+(.0477*Otk[19][0]))-utk[7][0]);
        Tstar[19][1] = ((WkIkWk[19][1]+(.0048*Otk[19][1]))-utk[7][1]);
        Tstar[19][2] = ((WkIkWk[19][2]+(.0484*Otk[19][2]))-utk[7][2]);
        Tstar[21][0] = ((WkIkWk[21][0]+(.001361*Otk[21][0]))-utk[8][0]);
        Tstar[21][1] = ((WkIkWk[21][1]+(.003709*Otk[21][1]))-utk[8][1]);
        Tstar[21][2] = ((WkIkWk[21][2]+(.003916*Otk[21][2]))-utk[8][2]);
        Tstar[22][0] = ((WkIkWk[22][0]+(.000117*Otk[22][0]))-utk[9][0]);
        Tstar[22][1] = ((WkIkWk[22][1]+(.000179*Otk[22][1]))-utk[9][1]);
        Tstar[22][2] = ((WkIkWk[22][2]+(.000119*Otk[22][2]))-utk[9][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        temp[0] = (((Fstar[12][2]*Vpk[0][12][2])+((Fstar[12][0]*Vpk[0][12][0])+(
          Fstar[12][1]*Vpk[0][12][1])))+(((Fstar[11][2]*Vpk[0][11][2])+((
          Fstar[11][0]*Vpk[0][11][0])+(Fstar[11][1]*Vpk[0][10][1])))+(((
          Cik[3][0][2]*Fstar[5][2])+((Cik[3][0][0]*Fstar[5][0])+(Cik[3][0][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[0][8][2])+((Fstar[8][0]*Vpk[0][8][0])
          +(Fstar[8][1]*Vpk[0][7][1]))))));
        temp[1] = (((Fstar[19][2]*Vpk[0][19][2])+((Fstar[19][0]*Vpk[0][19][0])+(
          Fstar[19][1]*Vpk[0][19][1])))+(((Fstar[18][2]*Vpk[0][18][2])+((
          Fstar[18][0]*Vpk[0][18][0])+(Fstar[18][1]*Vpk[0][17][1])))+(((
          Fstar[15][2]*Vpk[0][15][2])+((Fstar[15][0]*Vpk[0][15][0])+(
          Fstar[15][1]*Vpk[0][15][1])))+(((Fstar[14][2]*Vpk[0][14][2])+((
          Fstar[14][0]*Vpk[0][14][0])+(Fstar[14][1]*Vpk[0][14][1])))+temp[0]))))
          ;
        fs0[0] = (utau[0]-(((Fstar[22][2]*Vpk[0][22][2])+((Fstar[22][0]*
          Vpk[0][22][0])+(Fstar[22][1]*Vpk[0][22][1])))+(((Fstar[21][2]*
          Vpk[0][21][2])+((Fstar[21][0]*Vpk[0][21][0])+(Fstar[21][1]*
          Vpk[0][21][1])))+temp[1])));
        temp[0] = (((Fstar[12][2]*Vpk[1][12][2])+((Fstar[12][0]*Vpk[1][12][0])+(
          Fstar[12][1]*Vpk[1][12][1])))+(((Fstar[11][2]*Vpk[1][11][2])+((
          Fstar[11][0]*Vpk[1][11][0])+(Fstar[11][1]*Vpk[1][10][1])))+(((
          Cik[3][1][2]*Fstar[5][2])+((Cik[3][1][0]*Fstar[5][0])+(Cik[3][1][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[1][8][2])+((Fstar[8][0]*Vpk[1][8][0])
          +(Fstar[8][1]*Vpk[1][7][1]))))));
        temp[1] = (((Fstar[19][2]*Vpk[1][19][2])+((Fstar[19][0]*Vpk[1][19][0])+(
          Fstar[19][1]*Vpk[1][19][1])))+(((Fstar[18][2]*Vpk[1][18][2])+((
          Fstar[18][0]*Vpk[1][18][0])+(Fstar[18][1]*Vpk[1][17][1])))+(((
          Fstar[15][2]*Vpk[1][15][2])+((Fstar[15][0]*Vpk[1][15][0])+(
          Fstar[15][1]*Vpk[1][15][1])))+(((Fstar[14][2]*Vpk[1][14][2])+((
          Fstar[14][0]*Vpk[1][14][0])+(Fstar[14][1]*Vpk[1][14][1])))+temp[0]))))
          ;
        fs0[1] = (utau[1]-(((Fstar[22][2]*Vpk[1][22][2])+((Fstar[22][0]*
          Vpk[1][22][0])+(Fstar[22][1]*Vpk[1][22][1])))+(((Fstar[21][2]*
          Vpk[1][21][2])+((Fstar[21][0]*Vpk[1][21][0])+(Fstar[21][1]*
          Vpk[1][21][1])))+temp[1])));
        temp[0] = (((Fstar[12][2]*Vpk[2][12][2])+((Fstar[12][0]*Vpk[2][12][0])+(
          Fstar[12][1]*Vpk[2][12][1])))+(((Fstar[11][2]*Vpk[2][11][2])+((
          Fstar[11][0]*Vpk[2][11][0])+(Fstar[11][1]*Vpk[2][10][1])))+(((
          Cik[3][2][2]*Fstar[5][2])+((Cik[3][2][0]*Fstar[5][0])+(Cik[3][2][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[2][8][2])+((Fstar[8][0]*Vpk[2][8][0])
          +(Fstar[8][1]*Vpk[2][7][1]))))));
        temp[1] = (((Fstar[19][2]*Vpk[2][19][2])+((Fstar[19][0]*Vpk[2][19][0])+(
          Fstar[19][1]*Vpk[2][19][1])))+(((Fstar[18][2]*Vpk[2][18][2])+((
          Fstar[18][0]*Vpk[2][18][0])+(Fstar[18][1]*Vpk[2][17][1])))+(((
          Fstar[15][2]*Vpk[2][15][2])+((Fstar[15][0]*Vpk[2][15][0])+(
          Fstar[15][1]*Vpk[2][15][1])))+(((Fstar[14][2]*Vpk[2][14][2])+((
          Fstar[14][0]*Vpk[2][14][0])+(Fstar[14][1]*Vpk[2][14][1])))+temp[0]))))
          ;
        fs0[2] = (utau[2]-(((Fstar[22][2]*Vpk[2][22][2])+((Fstar[22][0]*
          Vpk[2][22][0])+(Fstar[22][1]*Vpk[2][22][1])))+(((Fstar[21][2]*
          Vpk[2][21][2])+((Fstar[21][0]*Vpk[2][21][0])+(Fstar[21][1]*
          Vpk[2][21][1])))+temp[1])));
        temp[0] = ((Tstar[5][0]+(((Fstar[8][2]*Vpk[3][8][2])+((.127*(Fstar[8][1]
          *s7))+(Fstar[8][0]*Vpk[3][8][0])))+((Tstar[8][2]*Wpk[3][8][2])+((
          Tstar[8][0]*Wpk[3][8][0])+(Tstar[8][1]*Wpk[3][7][1])))))+(((
          Fstar[11][2]*Vpk[3][11][2])+((Fstar[11][0]*Vpk[3][11][0])+(
          Fstar[11][1]*Vpk[3][11][1])))+((Tstar[11][2]*Wpk[3][11][2])+((
          Tstar[11][0]*Wpk[3][11][0])+(Tstar[11][1]*Wpk[3][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[3][14][2])+((Fstar[14][0]*Vpk[3][14][0])+
          (Fstar[14][1]*Vpk[3][14][1])))+((Tstar[14][2]*Wpk[3][14][2])+((
          Tstar[14][0]*Wpk[3][14][0])+(Tstar[14][1]*Wpk[3][14][1]))))+(temp[0]+(
          ((Fstar[12][2]*Vpk[3][12][2])+((Fstar[12][0]*Vpk[3][12][0])+(
          Fstar[12][1]*Vpk[3][12][1])))+((Tstar[12][2]*Wpk[3][12][2])+((
          Tstar[12][0]*Wpk[3][12][0])+(Tstar[12][1]*Wpk[3][12][1]))))));
        temp[2] = ((((Fstar[18][2]*Vpk[3][18][2])+((Fstar[18][0]*Vpk[3][18][0])+
          (Fstar[18][1]*Vpk[3][18][1])))+((Tstar[18][2]*Wpk[3][18][2])+((
          Tstar[18][0]*Wpk[3][18][0])+(Tstar[18][1]*Wpk[3][17][1]))))+((((
          Fstar[15][2]*Vpk[3][15][2])+((Fstar[15][0]*Vpk[3][15][0])+(
          Fstar[15][1]*Vpk[3][15][1])))+((Tstar[15][2]*Wpk[3][15][2])+((
          Tstar[15][0]*Wpk[3][15][0])+(Tstar[15][1]*Wpk[3][15][1]))))+temp[1]));
        temp[3] = ((((Fstar[21][2]*Vpk[3][21][2])+((Fstar[21][0]*Vpk[3][21][0])+
          (Fstar[21][1]*Vpk[3][21][1])))+((Tstar[21][2]*Wpk[3][21][2])+((
          Tstar[21][0]*Wpk[3][21][0])+(Tstar[21][1]*Wpk[3][21][1]))))+((((
          Fstar[19][2]*Vpk[3][19][2])+((Fstar[19][0]*Vpk[3][19][0])+(
          Fstar[19][1]*Vpk[3][19][1])))+((Tstar[19][2]*Wpk[3][19][2])+((
          Tstar[19][0]*Wpk[3][19][0])+(Tstar[19][1]*Wpk[3][19][1]))))+temp[2]));
        fs0[3] = (utau[3]-((((Fstar[22][2]*Vpk[3][22][2])+((Fstar[22][0]*
          Vpk[3][22][0])+(Fstar[22][1]*Vpk[3][22][1])))+((Tstar[22][2]*
          Wpk[3][22][2])+((Tstar[22][0]*Wpk[3][22][0])+(Tstar[22][1]*
          Wpk[3][22][1]))))+temp[3]));
        temp[0] = ((Tstar[5][1]+((.3202*((Fstar[8][2]*Wpk[4][8][0])-(Fstar[8][0]
          *Wpk[4][8][2])))+((Tstar[8][2]*Wpk[4][8][2])+((Tstar[8][0]*
          Wpk[4][8][0])+(Tstar[8][1]*Wpk[4][7][1])))))+(((Fstar[11][2]*
          Vpk[4][11][2])+((Fstar[11][0]*Vpk[4][11][0])+(Fstar[11][1]*
          Vpk[4][11][1])))+((Tstar[11][2]*Wpk[4][11][2])+((Tstar[11][0]*
          Wpk[4][11][0])+(Tstar[11][1]*Wpk[4][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[4][14][2])+((Fstar[14][0]*Vpk[4][14][0])+
          (Fstar[14][1]*Vpk[4][14][1])))+((Tstar[14][2]*Wpk[4][14][2])+((
          Tstar[14][0]*Wpk[4][14][0])+(Tstar[14][1]*Wpk[4][14][1]))))+(temp[0]+(
          ((Fstar[12][2]*Vpk[4][12][2])+((Fstar[12][0]*Vpk[4][12][0])+(
          Fstar[12][1]*Vpk[4][12][1])))+((Tstar[12][2]*Wpk[4][12][2])+((
          Tstar[12][0]*Wpk[4][12][0])+(Tstar[12][1]*Wpk[4][12][1]))))));
        temp[2] = ((((Fstar[18][2]*Vpk[4][18][2])+((Fstar[18][0]*Vpk[4][18][0])+
          (Fstar[18][1]*Vpk[4][18][1])))+((Tstar[18][2]*Wpk[4][18][2])+((
          Tstar[18][0]*Wpk[4][18][0])+(Tstar[18][1]*Wpk[4][17][1]))))+((((
          Fstar[15][2]*Vpk[4][15][2])+((Fstar[15][0]*Vpk[4][15][0])+(
          Fstar[15][1]*Vpk[4][15][1])))+((Tstar[15][2]*Wpk[4][15][2])+((
          Tstar[15][0]*Wpk[4][15][0])+(Tstar[15][1]*Wpk[4][15][1]))))+temp[1]));
        temp[3] = ((((Fstar[21][2]*Vpk[4][21][2])+((Fstar[21][0]*Vpk[4][21][0])+
          (Fstar[21][1]*Vpk[4][21][1])))+((Tstar[21][2]*Wpk[4][21][2])+((
          Tstar[21][0]*Wpk[4][21][0])+(Tstar[21][1]*Wpk[4][21][1]))))+((((
          Fstar[19][2]*Vpk[4][19][2])+((Fstar[19][0]*Vpk[4][19][0])+(
          Fstar[19][1]*Vpk[4][19][1])))+((Tstar[19][2]*Wpk[4][19][2])+((
          Tstar[19][0]*Wpk[4][19][0])+(Tstar[19][1]*Wpk[4][19][1]))))+temp[2]));
        fs0[4] = (utau[4]-((((Fstar[22][2]*Vpk[4][22][2])+((Fstar[22][0]*
          Vpk[4][22][0])+(Fstar[22][1]*Vpk[4][22][1])))+((Tstar[22][2]*
          Wpk[4][22][2])+((Tstar[22][0]*Wpk[4][22][0])+(Tstar[22][1]*
          Wpk[4][22][1]))))+temp[3]));
        temp[0] = ((Tstar[5][2]+(((Fstar[8][2]*Vpk[5][8][2])+((Fstar[8][0]*
          Vpk[5][8][0])+(Fstar[8][1]*Vpk[5][7][1])))+((Tstar[8][2]*Wpk[5][8][2])
          +((Tstar[8][0]*Wpk[5][8][0])+(Tstar[8][1]*s7)))))+(((Fstar[11][2]*
          Vpk[5][11][2])+((Fstar[11][0]*Vpk[5][11][0])+(Fstar[11][1]*
          Vpk[5][11][1])))+((Tstar[11][2]*Wpk[5][11][2])+((Tstar[11][0]*
          Wpk[5][11][0])+(Tstar[11][1]*s10)))));
        temp[1] = ((((Fstar[14][2]*Vpk[5][14][2])+((Fstar[14][0]*Vpk[5][14][0])+
          (Fstar[14][1]*Vpk[5][14][1])))+((Tstar[14][2]*Wpk[5][14][2])+((
          Tstar[14][0]*Wpk[5][14][0])+(Tstar[14][1]*Wpk[5][14][1]))))+(temp[0]+(
          ((Fstar[12][2]*Vpk[5][12][2])+((Fstar[12][0]*Vpk[5][12][0])+(
          Fstar[12][1]*Vpk[5][12][1])))+((Tstar[12][2]*Wpk[5][12][2])+((
          Tstar[12][0]*Wpk[5][12][0])+(Tstar[12][1]*Wpk[5][12][1]))))));
        temp[2] = ((((Fstar[18][2]*Vpk[5][18][2])+((Fstar[18][0]*Vpk[5][18][0])+
          (Fstar[18][1]*Vpk[5][18][1])))+((Tstar[18][2]*Wpk[5][18][2])+((
          Tstar[18][0]*Wpk[5][18][0])-(Tstar[18][1]*s17))))+((((Fstar[15][2]*
          Vpk[5][15][2])+((Fstar[15][0]*Vpk[5][15][0])+(Fstar[15][1]*
          Vpk[5][15][1])))+((Tstar[15][2]*Wpk[5][15][2])+((Tstar[15][0]*
          Wpk[5][15][0])+(Tstar[15][1]*Wpk[5][15][1]))))+temp[1]));
        temp[3] = ((((Fstar[21][2]*Vpk[5][21][2])+((Fstar[21][0]*Vpk[5][21][0])+
          (Fstar[21][1]*Vpk[5][21][1])))+((Tstar[21][2]*Wpk[5][21][2])+((
          Tstar[21][0]*Wpk[5][21][0])+(Tstar[21][1]*Wpk[5][21][1]))))+((((
          Fstar[19][2]*Vpk[5][19][2])+((Fstar[19][0]*Vpk[5][19][0])+(
          Fstar[19][1]*Vpk[5][19][1])))+((Tstar[19][2]*Wpk[5][19][2])+((
          Tstar[19][0]*Wpk[5][19][0])+(Tstar[19][1]*Wpk[5][19][1]))))+temp[2]));
        fs0[5] = (utau[5]-((((Fstar[22][2]*Vpk[5][22][2])+((Fstar[22][0]*
          Vpk[5][22][0])+(Fstar[22][1]*Vpk[5][22][1])))+((Tstar[22][2]*
          Wpk[5][22][2])+((Tstar[22][0]*Wpk[5][22][0])+(Tstar[22][1]*
          Wpk[5][22][1]))))+temp[3]));
        fs0[6] = (utau[6]-((.3202*((Fstar[8][2]*Wpk[6][8][0])-(Fstar[8][0]*
          Wpk[6][8][2])))+((Tstar[8][2]*Wpk[6][8][2])+((Tstar[8][0]*Wpk[6][8][0]
          )+(Tstar[8][1]*s7)))));
        fs0[7] = (utau[7]-((.3202*((Fstar[8][2]*c8)-(Fstar[8][0]*s8)))+((
          Tstar[8][0]*c8)+(Tstar[8][2]*s8))));
        fs0[8] = (utau[8]-Tstar[8][1]);
        temp[0] = ((((Fstar[11][2]*Vpk[9][11][2])+((.1715*(Fstar[11][0]*
          Wpk[9][11][2]))-(.002*(Fstar[11][1]*Wpk[9][11][2]))))+((Tstar[11][2]*
          Wpk[9][11][2])+((Tstar[11][0]*Wpk[9][11][0])+(Tstar[11][1]*s10))))+(((
          Fstar[12][2]*Vpk[9][12][2])+((Fstar[12][0]*Vpk[9][12][0])+(
          Fstar[12][1]*Vpk[9][12][1])))+((Tstar[12][2]*Wpk[9][12][2])+((
          Tstar[12][0]*Wpk[9][12][0])+(Tstar[12][1]*Wpk[9][12][1])))));
        fs0[9] = (utau[9]-((((Fstar[15][2]*Vpk[9][15][2])+((Fstar[15][0]*
          Vpk[9][15][0])+(Fstar[15][1]*Vpk[9][15][1])))+((Tstar[15][2]*
          Wpk[9][15][2])+((Tstar[15][0]*Wpk[9][15][0])+(Tstar[15][1]*
          Wpk[9][15][1]))))+((((Fstar[14][2]*Vpk[9][14][2])+((Fstar[14][0]*
          Vpk[9][14][0])+(Fstar[14][1]*Vpk[9][14][1])))+((Tstar[14][2]*
          Wpk[9][14][2])+((Tstar[14][0]*Wpk[9][14][0])+(Tstar[14][1]*
          Wpk[9][14][1]))))+temp[0])));
        temp[0] = ((((Fstar[12][2]*Vpk[10][12][2])+((Fstar[12][0]*Vpk[10][12][0]
          )+(Fstar[12][1]*Vpk[10][12][1])))+((Tstar[12][2]*Wpk[10][12][2])+((
          Tstar[12][0]*Wpk[10][12][0])+(Tstar[12][1]*Wpk[10][12][1]))))+(((
          Tstar[11][0]*c11)+(Tstar[11][2]*s11))+(((.1715*(Fstar[11][0]*s11))-(
          .002*(Fstar[11][1]*s11)))-(.1715*(Fstar[11][2]*c11)))));
        fs0[10] = (utau[10]-((((Fstar[15][2]*Vpk[10][15][2])+((Fstar[15][0]*
          Vpk[10][15][0])+(Fstar[15][1]*Vpk[10][15][1])))+((Tstar[15][2]*
          Wpk[10][15][2])+((Tstar[15][0]*Wpk[10][15][0])+(Tstar[15][1]*
          Wpk[10][15][1]))))+((((Fstar[14][2]*Vpk[10][14][2])+((Fstar[14][0]*
          Vpk[10][14][0])+(Fstar[14][1]*Vpk[10][14][1])))+((Tstar[14][2]*
          Wpk[10][14][2])+((Tstar[14][0]*Wpk[10][14][0])+(Tstar[14][1]*
          Wpk[10][14][1]))))+temp[0])));
        temp[0] = (((Tstar[11][1]+(.002*Fstar[11][2]))+(((Cik[12][1][2]*
          Tstar[12][2])+((Cik[12][1][0]*Tstar[12][0])+(Cik[12][1][1]*
          Tstar[12][1])))+((Fstar[12][2]*Vpk[11][12][2])+((Fstar[12][0]*
          Vpk[11][12][0])-(.0013*(Cik[12][2][1]*Fstar[12][1]))))))+(((
          Fstar[14][2]*Vpk[11][14][2])+((Fstar[14][0]*Vpk[11][14][0])+(
          Fstar[14][1]*Vpk[11][14][1])))+((Tstar[14][2]*Wpk[11][14][2])+((
          Tstar[14][0]*Wpk[11][14][0])+(Tstar[14][1]*Wpk[11][14][1])))));
        fs0[11] = (utau[11]-((((Fstar[15][2]*Vpk[11][15][2])+((Fstar[15][0]*
          Vpk[11][15][0])+(Fstar[15][1]*Vpk[11][15][1])))+((Tstar[15][2]*
          Wpk[11][15][2])+((Tstar[15][0]*Wpk[11][15][0])+(Tstar[15][1]*
          Wpk[11][15][1]))))+temp[0]));
        temp[0] = ((((.0150652581855386*Fstar[12][2])+(.185436609363333*
          Fstar[12][0]))+((.995900157697815*Tstar[12][2])+((.0404550064059294*
          Tstar[12][1])-(.0809090128117004*Tstar[12][0]))))+(((Fstar[14][2]*
          Vpk[12][14][2])+((Fstar[14][0]*Vpk[12][14][0])+(Fstar[14][1]*
          Vpk[12][14][1])))+((Tstar[14][2]*Wpk[12][14][2])+((Tstar[14][0]*
          Wpk[12][14][0])+(Tstar[14][1]*Wpk[12][14][1])))));
        fs0[12] = (utau[12]-((((Fstar[15][2]*Vpk[12][15][2])+((Fstar[15][0]*
          Vpk[12][15][0])+(Fstar[15][1]*Vpk[12][15][1])))+((Tstar[15][2]*
          Wpk[12][15][2])+((Tstar[15][0]*Wpk[12][15][0])+(Tstar[15][1]*
          Wpk[12][15][1]))))+temp[0]));
        fs0[13] = (utau[13]-((((Fstar[14][2]*Vpk[13][14][2])+((Fstar[14][0]*
          Vpk[13][14][0])+(Fstar[14][1]*Vpk[13][14][1])))+((Tstar[14][2]*
          Wpk[13][14][2])+((Tstar[14][0]*Wpk[13][14][0])+(Tstar[14][1]*
          Wpk[13][14][1]))))+(((Fstar[15][2]*Vpk[13][15][2])+((Fstar[15][0]*
          Vpk[13][15][0])+(Fstar[15][1]*Vpk[13][15][1])))+((Tstar[15][2]*
          Wpk[13][15][2])+((Tstar[15][0]*Wpk[13][15][0])+(Tstar[15][1]*
          Wpk[13][15][1]))))));
        fs0[14] = (utau[14]-((((Fstar[15][2]*Vpk[14][15][2])+((Fstar[15][0]*
          Vpk[14][15][0])+(Fstar[15][1]*Vpk[14][15][1])))+((Tstar[15][2]*
          Wpk[14][15][2])+((Tstar[15][0]*Wpk[14][15][0])+(Tstar[15][1]*
          Wpk[14][15][1]))))+((((.000411457536296252*Fstar[14][0])-(
          .00646090297985859*Fstar[14][1]))-(.0625600530375351*Fstar[14][2]))+((
          (.57725989098448*Tstar[14][1])+(.814755846133373*Tstar[14][0]))-(
          .0542579897533796*Tstar[14][2])))));
        fs0[15] = (utau[15]-(((.882947501360837*Tstar[15][2])-(.469471734868729*
          Tstar[15][0]))+(((.02617891313962*Fstar[15][1])-(.0163345287751755*
          Fstar[15][0]))-(.00868522709507149*Fstar[15][2]))));
        temp[0] = ((((Fstar[18][2]*Vpk[16][18][2])+((.1715*(Fstar[18][0]*
          Wpk[16][18][2]))-(.002*(Fstar[18][1]*Wpk[16][18][2]))))+((Tstar[18][2]
          *Wpk[16][18][2])+((Tstar[18][0]*Wpk[16][18][0])-(Tstar[18][1]*s17))))+
          (((Fstar[19][2]*Vpk[16][19][2])+((Fstar[19][0]*Vpk[16][19][0])+(
          Fstar[19][1]*Vpk[16][19][1])))+((Tstar[19][2]*Wpk[16][19][2])+((
          Tstar[19][0]*Wpk[16][19][0])+(Tstar[19][1]*Wpk[16][19][1])))));
        fs0[16] = (utau[16]-((((Fstar[22][2]*Vpk[16][22][2])+((Fstar[22][0]*
          Vpk[16][22][0])+(Fstar[22][1]*Vpk[16][22][1])))+((Tstar[22][2]*
          Wpk[16][22][2])+((Tstar[22][0]*Wpk[16][22][0])+(Tstar[22][1]*
          Wpk[16][22][1]))))+((((Fstar[21][2]*Vpk[16][21][2])+((Fstar[21][0]*
          Vpk[16][21][0])+(Fstar[21][1]*Vpk[16][21][1])))+((Tstar[21][2]*
          Wpk[16][21][2])+((Tstar[21][0]*Wpk[16][21][0])+(Tstar[21][1]*
          Wpk[16][21][1]))))+temp[0])));
        temp[0] = ((((.1715*(Fstar[18][2]*c18))+((.1715*(Fstar[18][0]*s18))-(
          .002*(Fstar[18][1]*s18))))+((Tstar[18][2]*s18)-(Tstar[18][0]*c18)))+((
          (Fstar[19][2]*Vpk[17][19][2])+((Fstar[19][0]*Vpk[17][19][0])+(
          Fstar[19][1]*Vpk[17][19][1])))+((Tstar[19][2]*Wpk[17][19][2])+((
          Tstar[19][0]*Wpk[17][19][0])+(Tstar[19][1]*Wpk[17][19][1])))));
        fs0[17] = (utau[17]-((((Fstar[22][2]*Vpk[17][22][2])+((Fstar[22][0]*
          Vpk[17][22][0])+(Fstar[22][1]*Vpk[17][22][1])))+((Tstar[22][2]*
          Wpk[17][22][2])+((Tstar[22][0]*Wpk[17][22][0])+(Tstar[22][1]*
          Wpk[17][22][1]))))+((((Fstar[21][2]*Vpk[17][21][2])+((Fstar[21][0]*
          Vpk[17][21][0])+(Fstar[21][1]*Vpk[17][21][1])))+((Tstar[21][2]*
          Wpk[17][21][2])+((Tstar[21][0]*Wpk[17][21][0])+(Tstar[21][1]*
          Wpk[17][21][1]))))+temp[0])));
        temp[0] = ((((Fstar[21][2]*Vpk[18][21][2])+((Fstar[21][0]*Vpk[18][21][0]
          )+(Fstar[21][1]*Vpk[18][21][1])))+((Tstar[21][2]*Wpk[18][21][2])+((
          Tstar[21][0]*Wpk[18][21][0])+(Tstar[21][1]*Wpk[18][21][1]))))+((((
          Fstar[19][2]*Vpk[18][19][2])+((.0013*(Cik[19][2][1]*Fstar[19][1]))+(
          Fstar[19][0]*Vpk[18][19][0])))-((Cik[19][1][2]*Tstar[19][2])+((
          Cik[19][1][0]*Tstar[19][0])+(Cik[19][1][1]*Tstar[19][1]))))-(
          Tstar[18][1]+(.002*Fstar[18][2]))));
        fs0[18] = (utau[18]-((((Fstar[22][2]*Vpk[18][22][2])+((Fstar[22][0]*
          Vpk[18][22][0])+(Fstar[22][1]*Vpk[18][22][1])))+((Tstar[22][2]*
          Wpk[18][22][2])+((Tstar[22][0]*Wpk[18][22][0])+(Tstar[22][1]*
          Wpk[18][22][1]))))+temp[0]));
        temp[0] = ((((.185436609363333*Fstar[19][0])-(.0150652581855386*
          Fstar[19][2]))+((.995900157697815*Tstar[19][2])+((.0809090128117004*
          Tstar[19][0])-(.0404550064059294*Tstar[19][1]))))+(((Fstar[21][2]*
          Vpk[19][21][2])+((Fstar[21][0]*Vpk[19][21][0])+(Fstar[21][1]*
          Vpk[19][21][1])))+((Tstar[21][2]*Wpk[19][21][2])+((Tstar[21][0]*
          Wpk[19][21][0])+(Tstar[21][1]*Wpk[19][21][1])))));
        fs0[19] = (utau[19]-((((Fstar[22][2]*Vpk[19][22][2])+((Fstar[22][0]*
          Vpk[19][22][0])+(Fstar[22][1]*Vpk[19][22][1])))+((Tstar[22][2]*
          Wpk[19][22][2])+((Tstar[22][0]*Wpk[19][22][0])+(Tstar[22][1]*
          Wpk[19][22][1]))))+temp[0]));
        fs0[20] = (utau[20]-((((Fstar[21][2]*Vpk[20][21][2])+((Fstar[21][0]*
          Vpk[20][21][0])+(Fstar[21][1]*Vpk[20][21][1])))+((Tstar[21][2]*
          Wpk[20][21][2])+((Tstar[21][0]*Wpk[20][21][0])+(Tstar[21][1]*
          Wpk[20][21][1]))))+(((Fstar[22][2]*Vpk[20][22][2])+((Fstar[22][0]*
          Vpk[20][22][0])+(Fstar[22][1]*Vpk[20][22][1])))+((Tstar[22][2]*
          Wpk[20][22][2])+((Tstar[22][0]*Wpk[20][22][0])+(Tstar[22][1]*
          Wpk[20][22][1]))))));
        fs0[21] = (utau[21]-((((.0625600530375351*Fstar[21][2])+((
          .000411457536296252*Fstar[21][0])-(.00646090297985859*Fstar[21][1])))-
          ((.0542579897533796*Tstar[21][2])+((.57725989098448*Tstar[21][1])+(
          .814755846133373*Tstar[21][0]))))+(((Fstar[22][2]*Vpk[21][22][2])+((
          Fstar[22][0]*Vpk[21][22][0])+(Fstar[22][1]*Vpk[21][22][1])))+((
          Tstar[22][2]*Wpk[21][22][2])+((Tstar[22][0]*Wpk[21][22][0])+(
          Tstar[22][1]*Wpk[21][22][1]))))));
        fs0[22] = (utau[22]-(((.00868522709507149*Fstar[22][2])+((
          .02617891313962*Fstar[22][1])-(.0163345287751755*Fstar[22][0])))+((
          .469471734868729*Tstar[22][0])+(.882947501360837*Tstar[22][2]))));
        fs0flg = 1;
    }
/*
 Used 0.16 seconds CPU time,
 24576 additional bytes of memory.
 Equations contain  607 adds/subtracts/negates
                    557 multiplies
                      0 divides
                    109 assignments
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
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[0][11][2])+((Vpk[0][10][1]*
          Vpk[0][10][1])+(Vpk[0][11][0]*Vpk[0][11][0]))))+((11.15*((Cik[3][0][2]
          *Cik[3][0][2])+((Cik[3][0][0]*Cik[3][0][0])+(Cik[3][0][1]*Cik[3][0][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[0][8][2])+((Vpk[0][7][1]*Vpk[0][7][1])
          +(Vpk[0][8][0]*Vpk[0][8][0]))))));
        temp[1] = ((.205126*((Vpk[0][15][2]*Vpk[0][15][2])+((Vpk[0][15][0]*
          Vpk[0][15][0])+(Vpk[0][15][1]*Vpk[0][15][1]))))+((1.2*((Vpk[0][14][2]*
          Vpk[0][14][2])+((Vpk[0][14][0]*Vpk[0][14][0])+(Vpk[0][14][1]*
          Vpk[0][14][1]))))+((3.51*((Vpk[0][12][2]*Vpk[0][12][2])+((
          Vpk[0][12][0]*Vpk[0][12][0])+(Vpk[0][12][1]*Vpk[0][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][21][2]*Vpk[0][21][2])+((Vpk[0][21][0]*
          Vpk[0][21][0])+(Vpk[0][21][1]*Vpk[0][21][1]))))+((3.51*((Vpk[0][19][2]
          *Vpk[0][19][2])+((Vpk[0][19][0]*Vpk[0][19][0])+(Vpk[0][19][1]*
          Vpk[0][19][1]))))+((8.806*((Vpk[0][18][2]*Vpk[0][18][2])+((
          Vpk[0][17][1]*Vpk[0][17][1])+(Vpk[0][18][0]*Vpk[0][18][0]))))+temp[1])
          ));
        mm[0][0] = ((.205126*((Vpk[0][22][2]*Vpk[0][22][2])+((Vpk[0][22][0]*
          Vpk[0][22][0])+(Vpk[0][22][1]*Vpk[0][22][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[1][11][2])+((Vpk[0][10][1]*
          Vpk[1][10][1])+(Vpk[0][11][0]*Vpk[1][11][0]))))+((11.15*((Cik[3][0][2]
          *Cik[3][1][2])+((Cik[3][0][0]*Cik[3][1][0])+(Cik[3][0][1]*Cik[3][1][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[1][8][2])+((Vpk[0][7][1]*Vpk[1][7][1])
          +(Vpk[0][8][0]*Vpk[1][8][0]))))));
        temp[1] = ((.205126*((Vpk[0][15][2]*Vpk[1][15][2])+((Vpk[0][15][0]*
          Vpk[1][15][0])+(Vpk[0][15][1]*Vpk[1][15][1]))))+((1.2*((Vpk[0][14][2]*
          Vpk[1][14][2])+((Vpk[0][14][0]*Vpk[1][14][0])+(Vpk[0][14][1]*
          Vpk[1][14][1]))))+((3.51*((Vpk[0][12][2]*Vpk[1][12][2])+((
          Vpk[0][12][0]*Vpk[1][12][0])+(Vpk[0][12][1]*Vpk[1][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][21][2]*Vpk[1][21][2])+((Vpk[0][21][0]*
          Vpk[1][21][0])+(Vpk[0][21][1]*Vpk[1][21][1]))))+((3.51*((Vpk[0][19][2]
          *Vpk[1][19][2])+((Vpk[0][19][0]*Vpk[1][19][0])+(Vpk[0][19][1]*
          Vpk[1][19][1]))))+((8.806*((Vpk[0][18][2]*Vpk[1][18][2])+((
          Vpk[0][17][1]*Vpk[1][17][1])+(Vpk[0][18][0]*Vpk[1][18][0]))))+temp[1])
          ));
        mm[0][1] = ((.205126*((Vpk[0][22][2]*Vpk[1][22][2])+((Vpk[0][22][0]*
          Vpk[1][22][0])+(Vpk[0][22][1]*Vpk[1][22][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[0][11][2]*Vpk[2][11][2])+((Vpk[0][10][1]*
          Vpk[2][10][1])+(Vpk[0][11][0]*Vpk[2][11][0]))))+((11.15*((Cik[3][0][2]
          *Cik[3][2][2])+((Cik[3][0][0]*Cik[3][2][0])+(Cik[3][0][1]*Cik[3][2][1]
          ))))+(32.413*((Vpk[0][8][2]*Vpk[2][8][2])+((Vpk[0][7][1]*Vpk[2][7][1])
          +(Vpk[0][8][0]*Vpk[2][8][0]))))));
        temp[1] = ((.205126*((Vpk[0][15][2]*Vpk[2][15][2])+((Vpk[0][15][0]*
          Vpk[2][15][0])+(Vpk[0][15][1]*Vpk[2][15][1]))))+((1.2*((Vpk[0][14][2]*
          Vpk[2][14][2])+((Vpk[0][14][0]*Vpk[2][14][0])+(Vpk[0][14][1]*
          Vpk[2][14][1]))))+((3.51*((Vpk[0][12][2]*Vpk[2][12][2])+((
          Vpk[0][12][0]*Vpk[2][12][0])+(Vpk[0][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[0][21][2]*Vpk[2][21][2])+((Vpk[0][21][0]*
          Vpk[2][21][0])+(Vpk[0][21][1]*Vpk[2][21][1]))))+((3.51*((Vpk[0][19][2]
          *Vpk[2][19][2])+((Vpk[0][19][0]*Vpk[2][19][0])+(Vpk[0][19][1]*
          Vpk[2][19][1]))))+((8.806*((Vpk[0][18][2]*Vpk[2][18][2])+((
          Vpk[0][17][1]*Vpk[2][17][1])+(Vpk[0][18][0]*Vpk[2][18][0]))))+temp[1])
          ));
        mm[0][2] = ((.205126*((Vpk[0][22][2]*Vpk[2][22][2])+((Vpk[0][22][0]*
          Vpk[2][22][0])+(Vpk[0][22][1]*Vpk[2][22][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[0][12][2]*Vpk[3][12][2])+((Vpk[0][12][0]*
          Vpk[3][12][0])+(Vpk[0][12][1]*Vpk[3][12][1]))))+((8.806*((
          Vpk[0][11][2]*Vpk[3][11][2])+((Vpk[0][10][1]*Vpk[3][11][1])+(
          Vpk[0][11][0]*Vpk[3][11][0]))))+(32.413*((Vpk[0][8][2]*Vpk[3][8][2])+(
          (.127*(Vpk[0][7][1]*s7))+(Vpk[0][8][0]*Vpk[3][8][0]))))));
        temp[1] = ((8.806*((Vpk[0][18][2]*Vpk[3][18][2])+((Vpk[0][17][1]*
          Vpk[3][18][1])+(Vpk[0][18][0]*Vpk[3][18][0]))))+((.205126*((
          Vpk[0][15][2]*Vpk[3][15][2])+((Vpk[0][15][0]*Vpk[3][15][0])+(
          Vpk[0][15][1]*Vpk[3][15][1]))))+((1.2*((Vpk[0][14][2]*Vpk[3][14][2])+(
          (Vpk[0][14][0]*Vpk[3][14][0])+(Vpk[0][14][1]*Vpk[3][14][1]))))+temp[0]
          )));
        mm[0][3] = ((.205126*((Vpk[0][22][2]*Vpk[3][22][2])+((Vpk[0][22][0]*
          Vpk[3][22][0])+(Vpk[0][22][1]*Vpk[3][22][1]))))+((1.2*((Vpk[0][21][2]*
          Vpk[3][21][2])+((Vpk[0][21][0]*Vpk[3][21][0])+(Vpk[0][21][1]*
          Vpk[3][21][1]))))+((3.51*((Vpk[0][19][2]*Vpk[3][19][2])+((
          Vpk[0][19][0]*Vpk[3][19][0])+(Vpk[0][19][1]*Vpk[3][19][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[0][14][2]*Vpk[4][14][2])+((Vpk[0][14][0]*
          Vpk[4][14][0])+(Vpk[0][14][1]*Vpk[4][14][1]))))+((3.51*((Vpk[0][12][2]
          *Vpk[4][12][2])+((Vpk[0][12][0]*Vpk[4][12][0])+(Vpk[0][12][1]*
          Vpk[4][12][1]))))+((8.806*((Vpk[0][11][2]*Vpk[4][11][2])+((
          Vpk[0][10][1]*Vpk[4][11][1])+(Vpk[0][11][0]*Vpk[4][11][0]))))+(
          10.3786426*((Vpk[0][8][2]*Wpk[4][8][0])-(Vpk[0][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[0][19][2]*Vpk[4][19][2])+((Vpk[0][19][0]*
          Vpk[4][19][0])+(Vpk[0][19][1]*Vpk[4][19][1]))))+((8.806*((
          Vpk[0][18][2]*Vpk[4][18][2])+((Vpk[0][17][1]*Vpk[4][18][1])+(
          Vpk[0][18][0]*Vpk[4][18][0]))))+((.205126*((Vpk[0][15][2]*
          Vpk[4][15][2])+((Vpk[0][15][0]*Vpk[4][15][0])+(Vpk[0][15][1]*
          Vpk[4][15][1]))))+temp[0])));
        mm[0][4] = ((.205126*((Vpk[0][22][2]*Vpk[4][22][2])+((Vpk[0][22][0]*
          Vpk[4][22][0])+(Vpk[0][22][1]*Vpk[4][22][1]))))+((1.2*((Vpk[0][21][2]*
          Vpk[4][21][2])+((Vpk[0][21][0]*Vpk[4][21][0])+(Vpk[0][21][1]*
          Vpk[4][21][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[0][12][2]*Vpk[5][12][2])+((Vpk[0][12][0]*
          Vpk[5][12][0])+(Vpk[0][12][1]*Vpk[5][12][1]))))+((8.806*((
          Vpk[0][11][2]*Vpk[5][11][2])+((Vpk[0][10][1]*Vpk[5][11][1])+(
          Vpk[0][11][0]*Vpk[5][11][0]))))+(32.413*((Vpk[0][8][2]*Vpk[5][8][2])+(
          (Vpk[0][7][1]*Vpk[5][7][1])+(Vpk[0][8][0]*Vpk[5][8][0]))))));
        temp[1] = ((8.806*((Vpk[0][18][2]*Vpk[5][18][2])+((Vpk[0][17][1]*
          Vpk[5][18][1])+(Vpk[0][18][0]*Vpk[5][18][0]))))+((.205126*((
          Vpk[0][15][2]*Vpk[5][15][2])+((Vpk[0][15][0]*Vpk[5][15][0])+(
          Vpk[0][15][1]*Vpk[5][15][1]))))+((1.2*((Vpk[0][14][2]*Vpk[5][14][2])+(
          (Vpk[0][14][0]*Vpk[5][14][0])+(Vpk[0][14][1]*Vpk[5][14][1]))))+temp[0]
          )));
        mm[0][5] = ((.205126*((Vpk[0][22][2]*Vpk[5][22][2])+((Vpk[0][22][0]*
          Vpk[5][22][0])+(Vpk[0][22][1]*Vpk[5][22][1]))))+((1.2*((Vpk[0][21][2]*
          Vpk[5][21][2])+((Vpk[0][21][0]*Vpk[5][21][0])+(Vpk[0][21][1]*
          Vpk[5][21][1]))))+((3.51*((Vpk[0][19][2]*Vpk[5][19][2])+((
          Vpk[0][19][0]*Vpk[5][19][0])+(Vpk[0][19][1]*Vpk[5][19][1]))))+temp[1])
          ));
        mm[0][6] = (10.3786426*((Vpk[0][8][2]*Wpk[6][8][0])-(Vpk[0][8][0]*
          Wpk[6][8][2])));
        mm[0][7] = (10.3786426*((Vpk[0][8][2]*c8)-(Vpk[0][8][0]*s8)));
        mm[0][8] = 0.;
        temp[0] = ((1.2*((Vpk[0][14][2]*Vpk[9][14][2])+((Vpk[0][14][0]*
          Vpk[9][14][0])+(Vpk[0][14][1]*Vpk[9][14][1]))))+((3.51*((Vpk[0][12][2]
          *Vpk[9][12][2])+((Vpk[0][12][0]*Vpk[9][12][0])+(Vpk[0][12][1]*
          Vpk[9][12][1]))))+(8.806*((Vpk[0][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[0][11][0]*Wpk[9][11][2]))-(.002*(Vpk[0][10][1]*Wpk[9][11][2]))))))
          );
        mm[0][9] = ((.205126*((Vpk[0][15][2]*Vpk[9][15][2])+((Vpk[0][15][0]*
          Vpk[9][15][0])+(Vpk[0][15][1]*Vpk[9][15][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][14][2]*Vpk[10][14][2])+((Vpk[0][14][0]*
          Vpk[10][14][0])+(Vpk[0][14][1]*Vpk[10][14][1]))))+((3.51*((
          Vpk[0][12][2]*Vpk[10][12][2])+((Vpk[0][12][0]*Vpk[10][12][0])+(
          Vpk[0][12][1]*Vpk[10][12][1]))))+(8.806*(((.1715*(Vpk[0][11][0]*s11))-
          (.002*(Vpk[0][10][1]*s11)))-(.1715*(Vpk[0][11][2]*c11))))));
        mm[0][10] = ((.205126*((Vpk[0][15][2]*Vpk[10][15][2])+((Vpk[0][15][0]*
          Vpk[10][15][0])+(Vpk[0][15][1]*Vpk[10][15][1]))))+temp[0]);
        mm[0][11] = ((.205126*((Vpk[0][15][2]*Vpk[11][15][2])+((Vpk[0][15][0]*
          Vpk[11][15][0])+(Vpk[0][15][1]*Vpk[11][15][1]))))+((1.2*((
          Vpk[0][14][2]*Vpk[11][14][2])+((Vpk[0][14][0]*Vpk[11][14][0])+(
          Vpk[0][14][1]*Vpk[11][14][1]))))+((.017612*Vpk[0][11][2])+(3.51*((
          Vpk[0][12][2]*Vpk[11][12][2])+((Vpk[0][12][0]*Vpk[11][12][0])-(.0013*(
          Cik[12][2][1]*Vpk[0][12][1]))))))));
        mm[0][12] = ((.205126*((Vpk[0][15][2]*Vpk[12][15][2])+((Vpk[0][15][0]*
          Vpk[12][15][0])+(Vpk[0][15][1]*Vpk[12][15][1]))))+((1.2*((
          Vpk[0][14][2]*Vpk[12][14][2])+((Vpk[0][14][0]*Vpk[12][14][0])+(
          Vpk[0][14][1]*Vpk[12][14][1]))))+(3.51*((.0150652581855386*
          Vpk[0][12][2])+(.185436609363333*Vpk[0][12][0])))));
        mm[0][13] = ((.205126*((Vpk[0][15][2]*Vpk[13][15][2])+((Vpk[0][15][0]*
          Vpk[13][15][0])+(Vpk[0][15][1]*Vpk[13][15][1]))))+(1.2*((Vpk[0][14][2]
          *Vpk[13][14][2])+((Vpk[0][14][0]*Vpk[13][14][0])+(Vpk[0][14][1]*
          Vpk[13][14][1])))));
        mm[0][14] = ((.205126*((Vpk[0][15][2]*Vpk[14][15][2])+((Vpk[0][15][0]*
          Vpk[14][15][0])+(Vpk[0][15][1]*Vpk[14][15][1]))))+(1.2*(((
          .000411457536296252*Vpk[0][14][0])-(.00646090297985859*Vpk[0][14][1]))
          -(.0625600530375351*Vpk[0][14][2]))));
        mm[0][15] = (.205126*(((.02617891313962*Vpk[0][15][1])-(
          .0163345287751755*Vpk[0][15][0]))-(.00868522709507149*Vpk[0][15][2])))
          ;
        temp[0] = ((1.2*((Vpk[0][21][2]*Vpk[16][21][2])+((Vpk[0][21][0]*
          Vpk[16][21][0])+(Vpk[0][21][1]*Vpk[16][21][1]))))+((3.51*((
          Vpk[0][19][2]*Vpk[16][19][2])+((Vpk[0][19][0]*Vpk[16][19][0])+(
          Vpk[0][19][1]*Vpk[16][19][1]))))+(8.806*((Vpk[0][18][2]*Vpk[16][18][2]
          )+((.1715*(Vpk[0][18][0]*Wpk[16][18][2]))-(.002*(Vpk[0][17][1]*
          Wpk[16][18][2])))))));
        mm[0][16] = ((.205126*((Vpk[0][22][2]*Vpk[16][22][2])+((Vpk[0][22][0]*
          Vpk[16][22][0])+(Vpk[0][22][1]*Vpk[16][22][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[0][21][2]*Vpk[17][21][2])+((Vpk[0][21][0]*
          Vpk[17][21][0])+(Vpk[0][21][1]*Vpk[17][21][1]))))+((3.51*((
          Vpk[0][19][2]*Vpk[17][19][2])+((Vpk[0][19][0]*Vpk[17][19][0])+(
          Vpk[0][19][1]*Vpk[17][19][1]))))+(8.806*((.1715*(Vpk[0][18][2]*c18))+(
          (.1715*(Vpk[0][18][0]*s18))-(.002*(Vpk[0][17][1]*s18)))))));
        mm[0][17] = ((.205126*((Vpk[0][22][2]*Vpk[17][22][2])+((Vpk[0][22][0]*
          Vpk[17][22][0])+(Vpk[0][22][1]*Vpk[17][22][1]))))+temp[0]);
        mm[0][18] = ((.205126*((Vpk[0][22][2]*Vpk[18][22][2])+((Vpk[0][22][0]*
          Vpk[18][22][0])+(Vpk[0][22][1]*Vpk[18][22][1]))))+((1.2*((
          Vpk[0][21][2]*Vpk[18][21][2])+((Vpk[0][21][0]*Vpk[18][21][0])+(
          Vpk[0][21][1]*Vpk[18][21][1]))))+((3.51*((Vpk[0][19][2]*Vpk[18][19][2]
          )+((.0013*(Cik[19][2][1]*Vpk[0][19][1]))+(Vpk[0][19][0]*Vpk[18][19][0]
          ))))-(.017612*Vpk[0][18][2]))));
        mm[0][19] = ((.205126*((Vpk[0][22][2]*Vpk[19][22][2])+((Vpk[0][22][0]*
          Vpk[19][22][0])+(Vpk[0][22][1]*Vpk[19][22][1]))))+((1.2*((
          Vpk[0][21][2]*Vpk[19][21][2])+((Vpk[0][21][0]*Vpk[19][21][0])+(
          Vpk[0][21][1]*Vpk[19][21][1]))))+(3.51*((.185436609363333*
          Vpk[0][19][0])-(.0150652581855386*Vpk[0][19][2])))));
        mm[0][20] = ((.205126*((Vpk[0][22][2]*Vpk[20][22][2])+((Vpk[0][22][0]*
          Vpk[20][22][0])+(Vpk[0][22][1]*Vpk[20][22][1]))))+(1.2*((Vpk[0][21][2]
          *Vpk[20][21][2])+((Vpk[0][21][0]*Vpk[20][21][0])+(Vpk[0][21][1]*
          Vpk[20][21][1])))));
        mm[0][21] = ((.205126*((Vpk[0][22][2]*Vpk[21][22][2])+((Vpk[0][22][0]*
          Vpk[21][22][0])+(Vpk[0][22][1]*Vpk[21][22][1]))))+(1.2*((
          .0625600530375351*Vpk[0][21][2])+((.000411457536296252*Vpk[0][21][0])-
          (.00646090297985859*Vpk[0][21][1])))));
        mm[0][22] = (.205126*((.00868522709507149*Vpk[0][22][2])+((
          .02617891313962*Vpk[0][22][1])-(.0163345287751755*Vpk[0][22][0]))));
        temp[0] = ((8.806*((Vpk[1][11][2]*Vpk[1][11][2])+((Vpk[1][10][1]*
          Vpk[1][10][1])+(Vpk[1][11][0]*Vpk[1][11][0]))))+((11.15*((Cik[3][1][2]
          *Cik[3][1][2])+((Cik[3][1][0]*Cik[3][1][0])+(Cik[3][1][1]*Cik[3][1][1]
          ))))+(32.413*((Vpk[1][8][2]*Vpk[1][8][2])+((Vpk[1][7][1]*Vpk[1][7][1])
          +(Vpk[1][8][0]*Vpk[1][8][0]))))));
        temp[1] = ((.205126*((Vpk[1][15][2]*Vpk[1][15][2])+((Vpk[1][15][0]*
          Vpk[1][15][0])+(Vpk[1][15][1]*Vpk[1][15][1]))))+((1.2*((Vpk[1][14][2]*
          Vpk[1][14][2])+((Vpk[1][14][0]*Vpk[1][14][0])+(Vpk[1][14][1]*
          Vpk[1][14][1]))))+((3.51*((Vpk[1][12][2]*Vpk[1][12][2])+((
          Vpk[1][12][0]*Vpk[1][12][0])+(Vpk[1][12][1]*Vpk[1][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[1][21][2]*Vpk[1][21][2])+((Vpk[1][21][0]*
          Vpk[1][21][0])+(Vpk[1][21][1]*Vpk[1][21][1]))))+((3.51*((Vpk[1][19][2]
          *Vpk[1][19][2])+((Vpk[1][19][0]*Vpk[1][19][0])+(Vpk[1][19][1]*
          Vpk[1][19][1]))))+((8.806*((Vpk[1][18][2]*Vpk[1][18][2])+((
          Vpk[1][17][1]*Vpk[1][17][1])+(Vpk[1][18][0]*Vpk[1][18][0]))))+temp[1])
          ));
        mm[1][1] = ((.205126*((Vpk[1][22][2]*Vpk[1][22][2])+((Vpk[1][22][0]*
          Vpk[1][22][0])+(Vpk[1][22][1]*Vpk[1][22][1]))))+temp[2]);
        temp[0] = ((8.806*((Vpk[1][11][2]*Vpk[2][11][2])+((Vpk[1][10][1]*
          Vpk[2][10][1])+(Vpk[1][11][0]*Vpk[2][11][0]))))+((11.15*((Cik[3][1][2]
          *Cik[3][2][2])+((Cik[3][1][0]*Cik[3][2][0])+(Cik[3][1][1]*Cik[3][2][1]
          ))))+(32.413*((Vpk[1][8][2]*Vpk[2][8][2])+((Vpk[1][7][1]*Vpk[2][7][1])
          +(Vpk[1][8][0]*Vpk[2][8][0]))))));
        temp[1] = ((.205126*((Vpk[1][15][2]*Vpk[2][15][2])+((Vpk[1][15][0]*
          Vpk[2][15][0])+(Vpk[1][15][1]*Vpk[2][15][1]))))+((1.2*((Vpk[1][14][2]*
          Vpk[2][14][2])+((Vpk[1][14][0]*Vpk[2][14][0])+(Vpk[1][14][1]*
          Vpk[2][14][1]))))+((3.51*((Vpk[1][12][2]*Vpk[2][12][2])+((
          Vpk[1][12][0]*Vpk[2][12][0])+(Vpk[1][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[1][21][2]*Vpk[2][21][2])+((Vpk[1][21][0]*
          Vpk[2][21][0])+(Vpk[1][21][1]*Vpk[2][21][1]))))+((3.51*((Vpk[1][19][2]
          *Vpk[2][19][2])+((Vpk[1][19][0]*Vpk[2][19][0])+(Vpk[1][19][1]*
          Vpk[2][19][1]))))+((8.806*((Vpk[1][18][2]*Vpk[2][18][2])+((
          Vpk[1][17][1]*Vpk[2][17][1])+(Vpk[1][18][0]*Vpk[2][18][0]))))+temp[1])
          ));
        mm[1][2] = ((.205126*((Vpk[1][22][2]*Vpk[2][22][2])+((Vpk[1][22][0]*
          Vpk[2][22][0])+(Vpk[1][22][1]*Vpk[2][22][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[1][12][2]*Vpk[3][12][2])+((Vpk[1][12][0]*
          Vpk[3][12][0])+(Vpk[1][12][1]*Vpk[3][12][1]))))+((8.806*((
          Vpk[1][11][2]*Vpk[3][11][2])+((Vpk[1][10][1]*Vpk[3][11][1])+(
          Vpk[1][11][0]*Vpk[3][11][0]))))+(32.413*((Vpk[1][8][2]*Vpk[3][8][2])+(
          (.127*(Vpk[1][7][1]*s7))+(Vpk[1][8][0]*Vpk[3][8][0]))))));
        temp[1] = ((8.806*((Vpk[1][18][2]*Vpk[3][18][2])+((Vpk[1][17][1]*
          Vpk[3][18][1])+(Vpk[1][18][0]*Vpk[3][18][0]))))+((.205126*((
          Vpk[1][15][2]*Vpk[3][15][2])+((Vpk[1][15][0]*Vpk[3][15][0])+(
          Vpk[1][15][1]*Vpk[3][15][1]))))+((1.2*((Vpk[1][14][2]*Vpk[3][14][2])+(
          (Vpk[1][14][0]*Vpk[3][14][0])+(Vpk[1][14][1]*Vpk[3][14][1]))))+temp[0]
          )));
        mm[1][3] = ((.205126*((Vpk[1][22][2]*Vpk[3][22][2])+((Vpk[1][22][0]*
          Vpk[3][22][0])+(Vpk[1][22][1]*Vpk[3][22][1]))))+((1.2*((Vpk[1][21][2]*
          Vpk[3][21][2])+((Vpk[1][21][0]*Vpk[3][21][0])+(Vpk[1][21][1]*
          Vpk[3][21][1]))))+((3.51*((Vpk[1][19][2]*Vpk[3][19][2])+((
          Vpk[1][19][0]*Vpk[3][19][0])+(Vpk[1][19][1]*Vpk[3][19][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[1][14][2]*Vpk[4][14][2])+((Vpk[1][14][0]*
          Vpk[4][14][0])+(Vpk[1][14][1]*Vpk[4][14][1]))))+((3.51*((Vpk[1][12][2]
          *Vpk[4][12][2])+((Vpk[1][12][0]*Vpk[4][12][0])+(Vpk[1][12][1]*
          Vpk[4][12][1]))))+((8.806*((Vpk[1][11][2]*Vpk[4][11][2])+((
          Vpk[1][10][1]*Vpk[4][11][1])+(Vpk[1][11][0]*Vpk[4][11][0]))))+(
          10.3786426*((Vpk[1][8][2]*Wpk[4][8][0])-(Vpk[1][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[1][19][2]*Vpk[4][19][2])+((Vpk[1][19][0]*
          Vpk[4][19][0])+(Vpk[1][19][1]*Vpk[4][19][1]))))+((8.806*((
          Vpk[1][18][2]*Vpk[4][18][2])+((Vpk[1][17][1]*Vpk[4][18][1])+(
          Vpk[1][18][0]*Vpk[4][18][0]))))+((.205126*((Vpk[1][15][2]*
          Vpk[4][15][2])+((Vpk[1][15][0]*Vpk[4][15][0])+(Vpk[1][15][1]*
          Vpk[4][15][1]))))+temp[0])));
        mm[1][4] = ((.205126*((Vpk[1][22][2]*Vpk[4][22][2])+((Vpk[1][22][0]*
          Vpk[4][22][0])+(Vpk[1][22][1]*Vpk[4][22][1]))))+((1.2*((Vpk[1][21][2]*
          Vpk[4][21][2])+((Vpk[1][21][0]*Vpk[4][21][0])+(Vpk[1][21][1]*
          Vpk[4][21][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[1][12][2]*Vpk[5][12][2])+((Vpk[1][12][0]*
          Vpk[5][12][0])+(Vpk[1][12][1]*Vpk[5][12][1]))))+((8.806*((
          Vpk[1][11][2]*Vpk[5][11][2])+((Vpk[1][10][1]*Vpk[5][11][1])+(
          Vpk[1][11][0]*Vpk[5][11][0]))))+(32.413*((Vpk[1][8][2]*Vpk[5][8][2])+(
          (Vpk[1][7][1]*Vpk[5][7][1])+(Vpk[1][8][0]*Vpk[5][8][0]))))));
        temp[1] = ((8.806*((Vpk[1][18][2]*Vpk[5][18][2])+((Vpk[1][17][1]*
          Vpk[5][18][1])+(Vpk[1][18][0]*Vpk[5][18][0]))))+((.205126*((
          Vpk[1][15][2]*Vpk[5][15][2])+((Vpk[1][15][0]*Vpk[5][15][0])+(
          Vpk[1][15][1]*Vpk[5][15][1]))))+((1.2*((Vpk[1][14][2]*Vpk[5][14][2])+(
          (Vpk[1][14][0]*Vpk[5][14][0])+(Vpk[1][14][1]*Vpk[5][14][1]))))+temp[0]
          )));
        mm[1][5] = ((.205126*((Vpk[1][22][2]*Vpk[5][22][2])+((Vpk[1][22][0]*
          Vpk[5][22][0])+(Vpk[1][22][1]*Vpk[5][22][1]))))+((1.2*((Vpk[1][21][2]*
          Vpk[5][21][2])+((Vpk[1][21][0]*Vpk[5][21][0])+(Vpk[1][21][1]*
          Vpk[5][21][1]))))+((3.51*((Vpk[1][19][2]*Vpk[5][19][2])+((
          Vpk[1][19][0]*Vpk[5][19][0])+(Vpk[1][19][1]*Vpk[5][19][1]))))+temp[1])
          ));
        mm[1][6] = (10.3786426*((Vpk[1][8][2]*Wpk[6][8][0])-(Vpk[1][8][0]*
          Wpk[6][8][2])));
        mm[1][7] = (10.3786426*((Vpk[1][8][2]*c8)-(Vpk[1][8][0]*s8)));
        mm[1][8] = 0.;
        temp[0] = ((1.2*((Vpk[1][14][2]*Vpk[9][14][2])+((Vpk[1][14][0]*
          Vpk[9][14][0])+(Vpk[1][14][1]*Vpk[9][14][1]))))+((3.51*((Vpk[1][12][2]
          *Vpk[9][12][2])+((Vpk[1][12][0]*Vpk[9][12][0])+(Vpk[1][12][1]*
          Vpk[9][12][1]))))+(8.806*((Vpk[1][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[1][11][0]*Wpk[9][11][2]))-(.002*(Vpk[1][10][1]*Wpk[9][11][2]))))))
          );
        mm[1][9] = ((.205126*((Vpk[1][15][2]*Vpk[9][15][2])+((Vpk[1][15][0]*
          Vpk[9][15][0])+(Vpk[1][15][1]*Vpk[9][15][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][14][2]*Vpk[10][14][2])+((Vpk[1][14][0]*
          Vpk[10][14][0])+(Vpk[1][14][1]*Vpk[10][14][1]))))+((3.51*((
          Vpk[1][12][2]*Vpk[10][12][2])+((Vpk[1][12][0]*Vpk[10][12][0])+(
          Vpk[1][12][1]*Vpk[10][12][1]))))+(8.806*(((.1715*(Vpk[1][11][0]*s11))-
          (.002*(Vpk[1][10][1]*s11)))-(.1715*(Vpk[1][11][2]*c11))))));
        mm[1][10] = ((.205126*((Vpk[1][15][2]*Vpk[10][15][2])+((Vpk[1][15][0]*
          Vpk[10][15][0])+(Vpk[1][15][1]*Vpk[10][15][1]))))+temp[0]);
        mm[1][11] = ((.205126*((Vpk[1][15][2]*Vpk[11][15][2])+((Vpk[1][15][0]*
          Vpk[11][15][0])+(Vpk[1][15][1]*Vpk[11][15][1]))))+((1.2*((
          Vpk[1][14][2]*Vpk[11][14][2])+((Vpk[1][14][0]*Vpk[11][14][0])+(
          Vpk[1][14][1]*Vpk[11][14][1]))))+((.017612*Vpk[1][11][2])+(3.51*((
          Vpk[1][12][2]*Vpk[11][12][2])+((Vpk[1][12][0]*Vpk[11][12][0])-(.0013*(
          Cik[12][2][1]*Vpk[1][12][1]))))))));
        mm[1][12] = ((.205126*((Vpk[1][15][2]*Vpk[12][15][2])+((Vpk[1][15][0]*
          Vpk[12][15][0])+(Vpk[1][15][1]*Vpk[12][15][1]))))+((1.2*((
          Vpk[1][14][2]*Vpk[12][14][2])+((Vpk[1][14][0]*Vpk[12][14][0])+(
          Vpk[1][14][1]*Vpk[12][14][1]))))+(3.51*((.0150652581855386*
          Vpk[1][12][2])+(.185436609363333*Vpk[1][12][0])))));
        mm[1][13] = ((.205126*((Vpk[1][15][2]*Vpk[13][15][2])+((Vpk[1][15][0]*
          Vpk[13][15][0])+(Vpk[1][15][1]*Vpk[13][15][1]))))+(1.2*((Vpk[1][14][2]
          *Vpk[13][14][2])+((Vpk[1][14][0]*Vpk[13][14][0])+(Vpk[1][14][1]*
          Vpk[13][14][1])))));
        mm[1][14] = ((.205126*((Vpk[1][15][2]*Vpk[14][15][2])+((Vpk[1][15][0]*
          Vpk[14][15][0])+(Vpk[1][15][1]*Vpk[14][15][1]))))+(1.2*(((
          .000411457536296252*Vpk[1][14][0])-(.00646090297985859*Vpk[1][14][1]))
          -(.0625600530375351*Vpk[1][14][2]))));
        mm[1][15] = (.205126*(((.02617891313962*Vpk[1][15][1])-(
          .0163345287751755*Vpk[1][15][0]))-(.00868522709507149*Vpk[1][15][2])))
          ;
        temp[0] = ((1.2*((Vpk[1][21][2]*Vpk[16][21][2])+((Vpk[1][21][0]*
          Vpk[16][21][0])+(Vpk[1][21][1]*Vpk[16][21][1]))))+((3.51*((
          Vpk[1][19][2]*Vpk[16][19][2])+((Vpk[1][19][0]*Vpk[16][19][0])+(
          Vpk[1][19][1]*Vpk[16][19][1]))))+(8.806*((Vpk[1][18][2]*Vpk[16][18][2]
          )+((.1715*(Vpk[1][18][0]*Wpk[16][18][2]))-(.002*(Vpk[1][17][1]*
          Wpk[16][18][2])))))));
        mm[1][16] = ((.205126*((Vpk[1][22][2]*Vpk[16][22][2])+((Vpk[1][22][0]*
          Vpk[16][22][0])+(Vpk[1][22][1]*Vpk[16][22][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[1][21][2]*Vpk[17][21][2])+((Vpk[1][21][0]*
          Vpk[17][21][0])+(Vpk[1][21][1]*Vpk[17][21][1]))))+((3.51*((
          Vpk[1][19][2]*Vpk[17][19][2])+((Vpk[1][19][0]*Vpk[17][19][0])+(
          Vpk[1][19][1]*Vpk[17][19][1]))))+(8.806*((.1715*(Vpk[1][18][2]*c18))+(
          (.1715*(Vpk[1][18][0]*s18))-(.002*(Vpk[1][17][1]*s18)))))));
        mm[1][17] = ((.205126*((Vpk[1][22][2]*Vpk[17][22][2])+((Vpk[1][22][0]*
          Vpk[17][22][0])+(Vpk[1][22][1]*Vpk[17][22][1]))))+temp[0]);
        mm[1][18] = ((.205126*((Vpk[1][22][2]*Vpk[18][22][2])+((Vpk[1][22][0]*
          Vpk[18][22][0])+(Vpk[1][22][1]*Vpk[18][22][1]))))+((1.2*((
          Vpk[1][21][2]*Vpk[18][21][2])+((Vpk[1][21][0]*Vpk[18][21][0])+(
          Vpk[1][21][1]*Vpk[18][21][1]))))+((3.51*((Vpk[1][19][2]*Vpk[18][19][2]
          )+((.0013*(Cik[19][2][1]*Vpk[1][19][1]))+(Vpk[1][19][0]*Vpk[18][19][0]
          ))))-(.017612*Vpk[1][18][2]))));
        mm[1][19] = ((.205126*((Vpk[1][22][2]*Vpk[19][22][2])+((Vpk[1][22][0]*
          Vpk[19][22][0])+(Vpk[1][22][1]*Vpk[19][22][1]))))+((1.2*((
          Vpk[1][21][2]*Vpk[19][21][2])+((Vpk[1][21][0]*Vpk[19][21][0])+(
          Vpk[1][21][1]*Vpk[19][21][1]))))+(3.51*((.185436609363333*
          Vpk[1][19][0])-(.0150652581855386*Vpk[1][19][2])))));
        mm[1][20] = ((.205126*((Vpk[1][22][2]*Vpk[20][22][2])+((Vpk[1][22][0]*
          Vpk[20][22][0])+(Vpk[1][22][1]*Vpk[20][22][1]))))+(1.2*((Vpk[1][21][2]
          *Vpk[20][21][2])+((Vpk[1][21][0]*Vpk[20][21][0])+(Vpk[1][21][1]*
          Vpk[20][21][1])))));
        mm[1][21] = ((.205126*((Vpk[1][22][2]*Vpk[21][22][2])+((Vpk[1][22][0]*
          Vpk[21][22][0])+(Vpk[1][22][1]*Vpk[21][22][1]))))+(1.2*((
          .0625600530375351*Vpk[1][21][2])+((.000411457536296252*Vpk[1][21][0])-
          (.00646090297985859*Vpk[1][21][1])))));
        mm[1][22] = (.205126*((.00868522709507149*Vpk[1][22][2])+((
          .02617891313962*Vpk[1][22][1])-(.0163345287751755*Vpk[1][22][0]))));
        temp[0] = ((8.806*((Vpk[2][11][2]*Vpk[2][11][2])+((Vpk[2][10][1]*
          Vpk[2][10][1])+(Vpk[2][11][0]*Vpk[2][11][0]))))+((11.15*((Cik[3][2][2]
          *Cik[3][2][2])+((Cik[3][2][0]*Cik[3][2][0])+(Cik[3][2][1]*Cik[3][2][1]
          ))))+(32.413*((Vpk[2][8][2]*Vpk[2][8][2])+((Vpk[2][7][1]*Vpk[2][7][1])
          +(Vpk[2][8][0]*Vpk[2][8][0]))))));
        temp[1] = ((.205126*((Vpk[2][15][2]*Vpk[2][15][2])+((Vpk[2][15][0]*
          Vpk[2][15][0])+(Vpk[2][15][1]*Vpk[2][15][1]))))+((1.2*((Vpk[2][14][2]*
          Vpk[2][14][2])+((Vpk[2][14][0]*Vpk[2][14][0])+(Vpk[2][14][1]*
          Vpk[2][14][1]))))+((3.51*((Vpk[2][12][2]*Vpk[2][12][2])+((
          Vpk[2][12][0]*Vpk[2][12][0])+(Vpk[2][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.2*((Vpk[2][21][2]*Vpk[2][21][2])+((Vpk[2][21][0]*
          Vpk[2][21][0])+(Vpk[2][21][1]*Vpk[2][21][1]))))+((3.51*((Vpk[2][19][2]
          *Vpk[2][19][2])+((Vpk[2][19][0]*Vpk[2][19][0])+(Vpk[2][19][1]*
          Vpk[2][19][1]))))+((8.806*((Vpk[2][18][2]*Vpk[2][18][2])+((
          Vpk[2][17][1]*Vpk[2][17][1])+(Vpk[2][18][0]*Vpk[2][18][0]))))+temp[1])
          ));
        mm[2][2] = ((.205126*((Vpk[2][22][2]*Vpk[2][22][2])+((Vpk[2][22][0]*
          Vpk[2][22][0])+(Vpk[2][22][1]*Vpk[2][22][1]))))+temp[2]);
        temp[0] = ((3.51*((Vpk[2][12][2]*Vpk[3][12][2])+((Vpk[2][12][0]*
          Vpk[3][12][0])+(Vpk[2][12][1]*Vpk[3][12][1]))))+((8.806*((
          Vpk[2][11][2]*Vpk[3][11][2])+((Vpk[2][10][1]*Vpk[3][11][1])+(
          Vpk[2][11][0]*Vpk[3][11][0]))))+(32.413*((Vpk[2][8][2]*Vpk[3][8][2])+(
          (.127*(Vpk[2][7][1]*s7))+(Vpk[2][8][0]*Vpk[3][8][0]))))));
        temp[1] = ((8.806*((Vpk[2][18][2]*Vpk[3][18][2])+((Vpk[2][17][1]*
          Vpk[3][18][1])+(Vpk[2][18][0]*Vpk[3][18][0]))))+((.205126*((
          Vpk[2][15][2]*Vpk[3][15][2])+((Vpk[2][15][0]*Vpk[3][15][0])+(
          Vpk[2][15][1]*Vpk[3][15][1]))))+((1.2*((Vpk[2][14][2]*Vpk[3][14][2])+(
          (Vpk[2][14][0]*Vpk[3][14][0])+(Vpk[2][14][1]*Vpk[3][14][1]))))+temp[0]
          )));
        mm[2][3] = ((.205126*((Vpk[2][22][2]*Vpk[3][22][2])+((Vpk[2][22][0]*
          Vpk[3][22][0])+(Vpk[2][22][1]*Vpk[3][22][1]))))+((1.2*((Vpk[2][21][2]*
          Vpk[3][21][2])+((Vpk[2][21][0]*Vpk[3][21][0])+(Vpk[2][21][1]*
          Vpk[3][21][1]))))+((3.51*((Vpk[2][19][2]*Vpk[3][19][2])+((
          Vpk[2][19][0]*Vpk[3][19][0])+(Vpk[2][19][1]*Vpk[3][19][1]))))+temp[1])
          ));
        temp[0] = ((1.2*((Vpk[2][14][2]*Vpk[4][14][2])+((Vpk[2][14][0]*
          Vpk[4][14][0])+(Vpk[2][14][1]*Vpk[4][14][1]))))+((3.51*((Vpk[2][12][2]
          *Vpk[4][12][2])+((Vpk[2][12][0]*Vpk[4][12][0])+(Vpk[2][12][1]*
          Vpk[4][12][1]))))+((8.806*((Vpk[2][11][2]*Vpk[4][11][2])+((
          Vpk[2][10][1]*Vpk[4][11][1])+(Vpk[2][11][0]*Vpk[4][11][0]))))+(
          10.3786426*((Vpk[2][8][2]*Wpk[4][8][0])-(Vpk[2][8][0]*Wpk[4][8][2]))))
          ));
        temp[1] = ((3.51*((Vpk[2][19][2]*Vpk[4][19][2])+((Vpk[2][19][0]*
          Vpk[4][19][0])+(Vpk[2][19][1]*Vpk[4][19][1]))))+((8.806*((
          Vpk[2][18][2]*Vpk[4][18][2])+((Vpk[2][17][1]*Vpk[4][18][1])+(
          Vpk[2][18][0]*Vpk[4][18][0]))))+((.205126*((Vpk[2][15][2]*
          Vpk[4][15][2])+((Vpk[2][15][0]*Vpk[4][15][0])+(Vpk[2][15][1]*
          Vpk[4][15][1]))))+temp[0])));
        mm[2][4] = ((.205126*((Vpk[2][22][2]*Vpk[4][22][2])+((Vpk[2][22][0]*
          Vpk[4][22][0])+(Vpk[2][22][1]*Vpk[4][22][1]))))+((1.2*((Vpk[2][21][2]*
          Vpk[4][21][2])+((Vpk[2][21][0]*Vpk[4][21][0])+(Vpk[2][21][1]*
          Vpk[4][21][1]))))+temp[1]));
        temp[0] = ((3.51*((Vpk[2][12][2]*Vpk[5][12][2])+((Vpk[2][12][0]*
          Vpk[5][12][0])+(Vpk[2][12][1]*Vpk[5][12][1]))))+((8.806*((
          Vpk[2][11][2]*Vpk[5][11][2])+((Vpk[2][10][1]*Vpk[5][11][1])+(
          Vpk[2][11][0]*Vpk[5][11][0]))))+(32.413*((Vpk[2][8][2]*Vpk[5][8][2])+(
          (Vpk[2][7][1]*Vpk[5][7][1])+(Vpk[2][8][0]*Vpk[5][8][0]))))));
        temp[1] = ((8.806*((Vpk[2][18][2]*Vpk[5][18][2])+((Vpk[2][17][1]*
          Vpk[5][18][1])+(Vpk[2][18][0]*Vpk[5][18][0]))))+((.205126*((
          Vpk[2][15][2]*Vpk[5][15][2])+((Vpk[2][15][0]*Vpk[5][15][0])+(
          Vpk[2][15][1]*Vpk[5][15][1]))))+((1.2*((Vpk[2][14][2]*Vpk[5][14][2])+(
          (Vpk[2][14][0]*Vpk[5][14][0])+(Vpk[2][14][1]*Vpk[5][14][1]))))+temp[0]
          )));
        mm[2][5] = ((.205126*((Vpk[2][22][2]*Vpk[5][22][2])+((Vpk[2][22][0]*
          Vpk[5][22][0])+(Vpk[2][22][1]*Vpk[5][22][1]))))+((1.2*((Vpk[2][21][2]*
          Vpk[5][21][2])+((Vpk[2][21][0]*Vpk[5][21][0])+(Vpk[2][21][1]*
          Vpk[5][21][1]))))+((3.51*((Vpk[2][19][2]*Vpk[5][19][2])+((
          Vpk[2][19][0]*Vpk[5][19][0])+(Vpk[2][19][1]*Vpk[5][19][1]))))+temp[1])
          ));
        mm[2][6] = (10.3786426*((Vpk[2][8][2]*Wpk[6][8][0])-(Vpk[2][8][0]*
          Wpk[6][8][2])));
        mm[2][7] = (10.3786426*((Vpk[2][8][2]*c8)-(Vpk[2][8][0]*s8)));
        mm[2][8] = 0.;
        temp[0] = ((1.2*((Vpk[2][14][2]*Vpk[9][14][2])+((Vpk[2][14][0]*
          Vpk[9][14][0])+(Vpk[2][14][1]*Vpk[9][14][1]))))+((3.51*((Vpk[2][12][2]
          *Vpk[9][12][2])+((Vpk[2][12][0]*Vpk[9][12][0])+(Vpk[2][12][1]*
          Vpk[9][12][1]))))+(8.806*((Vpk[2][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[2][11][0]*Wpk[9][11][2]))-(.002*(Vpk[2][10][1]*Wpk[9][11][2]))))))
          );
        mm[2][9] = ((.205126*((Vpk[2][15][2]*Vpk[9][15][2])+((Vpk[2][15][0]*
          Vpk[9][15][0])+(Vpk[2][15][1]*Vpk[9][15][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][14][2]*Vpk[10][14][2])+((Vpk[2][14][0]*
          Vpk[10][14][0])+(Vpk[2][14][1]*Vpk[10][14][1]))))+((3.51*((
          Vpk[2][12][2]*Vpk[10][12][2])+((Vpk[2][12][0]*Vpk[10][12][0])+(
          Vpk[2][12][1]*Vpk[10][12][1]))))+(8.806*(((.1715*(Vpk[2][11][0]*s11))-
          (.002*(Vpk[2][10][1]*s11)))-(.1715*(Vpk[2][11][2]*c11))))));
        mm[2][10] = ((.205126*((Vpk[2][15][2]*Vpk[10][15][2])+((Vpk[2][15][0]*
          Vpk[10][15][0])+(Vpk[2][15][1]*Vpk[10][15][1]))))+temp[0]);
        mm[2][11] = ((.205126*((Vpk[2][15][2]*Vpk[11][15][2])+((Vpk[2][15][0]*
          Vpk[11][15][0])+(Vpk[2][15][1]*Vpk[11][15][1]))))+((1.2*((
          Vpk[2][14][2]*Vpk[11][14][2])+((Vpk[2][14][0]*Vpk[11][14][0])+(
          Vpk[2][14][1]*Vpk[11][14][1]))))+((.017612*Vpk[2][11][2])+(3.51*((
          Vpk[2][12][2]*Vpk[11][12][2])+((Vpk[2][12][0]*Vpk[11][12][0])-(.0013*(
          Cik[12][2][1]*Vpk[2][12][1]))))))));
        mm[2][12] = ((.205126*((Vpk[2][15][2]*Vpk[12][15][2])+((Vpk[2][15][0]*
          Vpk[12][15][0])+(Vpk[2][15][1]*Vpk[12][15][1]))))+((1.2*((
          Vpk[2][14][2]*Vpk[12][14][2])+((Vpk[2][14][0]*Vpk[12][14][0])+(
          Vpk[2][14][1]*Vpk[12][14][1]))))+(3.51*((.0150652581855386*
          Vpk[2][12][2])+(.185436609363333*Vpk[2][12][0])))));
        mm[2][13] = ((.205126*((Vpk[2][15][2]*Vpk[13][15][2])+((Vpk[2][15][0]*
          Vpk[13][15][0])+(Vpk[2][15][1]*Vpk[13][15][1]))))+(1.2*((Vpk[2][14][2]
          *Vpk[13][14][2])+((Vpk[2][14][0]*Vpk[13][14][0])+(Vpk[2][14][1]*
          Vpk[13][14][1])))));
        mm[2][14] = ((.205126*((Vpk[2][15][2]*Vpk[14][15][2])+((Vpk[2][15][0]*
          Vpk[14][15][0])+(Vpk[2][15][1]*Vpk[14][15][1]))))+(1.2*(((
          .000411457536296252*Vpk[2][14][0])-(.00646090297985859*Vpk[2][14][1]))
          -(.0625600530375351*Vpk[2][14][2]))));
        mm[2][15] = (.205126*(((.02617891313962*Vpk[2][15][1])-(
          .0163345287751755*Vpk[2][15][0]))-(.00868522709507149*Vpk[2][15][2])))
          ;
        temp[0] = ((1.2*((Vpk[2][21][2]*Vpk[16][21][2])+((Vpk[2][21][0]*
          Vpk[16][21][0])+(Vpk[2][21][1]*Vpk[16][21][1]))))+((3.51*((
          Vpk[2][19][2]*Vpk[16][19][2])+((Vpk[2][19][0]*Vpk[16][19][0])+(
          Vpk[2][19][1]*Vpk[16][19][1]))))+(8.806*((Vpk[2][18][2]*Vpk[16][18][2]
          )+((.1715*(Vpk[2][18][0]*Wpk[16][18][2]))-(.002*(Vpk[2][17][1]*
          Wpk[16][18][2])))))));
        mm[2][16] = ((.205126*((Vpk[2][22][2]*Vpk[16][22][2])+((Vpk[2][22][0]*
          Vpk[16][22][0])+(Vpk[2][22][1]*Vpk[16][22][1]))))+temp[0]);
        temp[0] = ((1.2*((Vpk[2][21][2]*Vpk[17][21][2])+((Vpk[2][21][0]*
          Vpk[17][21][0])+(Vpk[2][21][1]*Vpk[17][21][1]))))+((3.51*((
          Vpk[2][19][2]*Vpk[17][19][2])+((Vpk[2][19][0]*Vpk[17][19][0])+(
          Vpk[2][19][1]*Vpk[17][19][1]))))+(8.806*((.1715*(Vpk[2][18][2]*c18))+(
          (.1715*(Vpk[2][18][0]*s18))-(.002*(Vpk[2][17][1]*s18)))))));
        mm[2][17] = ((.205126*((Vpk[2][22][2]*Vpk[17][22][2])+((Vpk[2][22][0]*
          Vpk[17][22][0])+(Vpk[2][22][1]*Vpk[17][22][1]))))+temp[0]);
        mm[2][18] = ((.205126*((Vpk[2][22][2]*Vpk[18][22][2])+((Vpk[2][22][0]*
          Vpk[18][22][0])+(Vpk[2][22][1]*Vpk[18][22][1]))))+((1.2*((
          Vpk[2][21][2]*Vpk[18][21][2])+((Vpk[2][21][0]*Vpk[18][21][0])+(
          Vpk[2][21][1]*Vpk[18][21][1]))))+((3.51*((Vpk[2][19][2]*Vpk[18][19][2]
          )+((.0013*(Cik[19][2][1]*Vpk[2][19][1]))+(Vpk[2][19][0]*Vpk[18][19][0]
          ))))-(.017612*Vpk[2][18][2]))));
        mm[2][19] = ((.205126*((Vpk[2][22][2]*Vpk[19][22][2])+((Vpk[2][22][0]*
          Vpk[19][22][0])+(Vpk[2][22][1]*Vpk[19][22][1]))))+((1.2*((
          Vpk[2][21][2]*Vpk[19][21][2])+((Vpk[2][21][0]*Vpk[19][21][0])+(
          Vpk[2][21][1]*Vpk[19][21][1]))))+(3.51*((.185436609363333*
          Vpk[2][19][0])-(.0150652581855386*Vpk[2][19][2])))));
        mm[2][20] = ((.205126*((Vpk[2][22][2]*Vpk[20][22][2])+((Vpk[2][22][0]*
          Vpk[20][22][0])+(Vpk[2][22][1]*Vpk[20][22][1]))))+(1.2*((Vpk[2][21][2]
          *Vpk[20][21][2])+((Vpk[2][21][0]*Vpk[20][21][0])+(Vpk[2][21][1]*
          Vpk[20][21][1])))));
        mm[2][21] = ((.205126*((Vpk[2][22][2]*Vpk[21][22][2])+((Vpk[2][22][0]*
          Vpk[21][22][0])+(Vpk[2][22][1]*Vpk[21][22][1]))))+(1.2*((
          .0625600530375351*Vpk[2][21][2])+((.000411457536296252*Vpk[2][21][0])-
          (.00646090297985859*Vpk[2][21][1])))));
        mm[2][22] = (.205126*((.00868522709507149*Vpk[2][22][2])+((
          .02617891313962*Vpk[2][22][1])-(.0163345287751755*Vpk[2][22][0]))));
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[3][11][2])+((Vpk[3][11][0]*
          Vpk[3][11][0])+(Vpk[3][11][1]*Vpk[3][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[3][11][2]))+((.0332*(Wpk[3][10][1]*Wpk[3][10][1]))+(.1268*(
          Wpk[3][11][0]*Wpk[3][11][0])))));
        temp[1] = ((3.51*((Vpk[3][12][2]*Vpk[3][12][2])+((Vpk[3][12][0]*
          Vpk[3][12][0])+(Vpk[3][12][1]*Vpk[3][12][1]))))+((.0484*(Wpk[3][12][2]
          *Wpk[3][12][2]))+((.0048*(Wpk[3][12][1]*Wpk[3][12][1]))+(.0477*(
          Wpk[3][12][0]*Wpk[3][12][0])))));
        temp[2] = (temp[1]+(temp[0]+((32.413*((Vpk[3][8][2]*Vpk[3][8][2])+((
          .016129*(s7*s7))+(Vpk[3][8][0]*Vpk[3][8][0]))))+((1.3552*(Wpk[3][8][2]
          *Wpk[3][8][2]))+((.7153*(Wpk[3][7][1]*Wpk[3][7][1]))+(1.396*(
          Wpk[3][8][0]*Wpk[3][8][0])))))));
        temp[3] = (((1.2*((Vpk[3][14][2]*Vpk[3][14][2])+((Vpk[3][14][0]*
          Vpk[3][14][0])+(Vpk[3][14][1]*Vpk[3][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[3][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[3][14][0]))
          +(.003709*(Wpk[3][14][1]*Wpk[3][14][1])))))+temp[2]);
        temp[4] = (((.205126*((Vpk[3][15][2]*Vpk[3][15][2])+((Vpk[3][15][0]*
          Vpk[3][15][0])+(Vpk[3][15][1]*Vpk[3][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[3][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[3][15][0]))
          +(.000179*(Wpk[3][15][1]*Wpk[3][15][1])))))+temp[3]);
        temp[5] = (((8.806*((Vpk[3][18][2]*Vpk[3][18][2])+((Vpk[3][18][0]*
          Vpk[3][18][0])+(Vpk[3][18][1]*Vpk[3][18][1]))))+((.1337*(Wpk[3][18][2]
          *Wpk[3][18][2]))+((.0332*(Wpk[3][17][1]*Wpk[3][17][1]))+(.1268*(
          Wpk[3][18][0]*Wpk[3][18][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[3][19][2]*Vpk[3][19][2])+((Vpk[3][19][0]*
          Vpk[3][19][0])+(Vpk[3][19][1]*Vpk[3][19][1]))))+((.0484*(Wpk[3][19][2]
          *Wpk[3][19][2]))+((.0048*(Wpk[3][19][1]*Wpk[3][19][1]))+(.0477*(
          Wpk[3][19][0]*Wpk[3][19][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[3][21][2]*Vpk[3][21][2])+((Vpk[3][21][0]*
          Vpk[3][21][0])+(Vpk[3][21][1]*Vpk[3][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[3][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[3][21][0]))
          +(.003709*(Wpk[3][21][1]*Wpk[3][21][1])))))+temp[6]);
        mm[3][3] = (.0973+(((.205126*((Vpk[3][22][2]*Vpk[3][22][2])+((
          Vpk[3][22][0]*Vpk[3][22][0])+(Vpk[3][22][1]*Vpk[3][22][1]))))+((
          .000119*(Wpk[3][22][2]*Wpk[3][22][2]))+((.000117*(Wpk[3][22][0]*
          Wpk[3][22][0]))+(.000179*(Wpk[3][22][1]*Wpk[3][22][1])))))+temp[7]));
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[4][11][2])+((Vpk[3][11][0]*
          Vpk[4][11][0])+(Vpk[3][11][1]*Vpk[4][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[4][11][2]))+((.0332*(Wpk[3][10][1]*Wpk[4][10][1]))+(.1268*(
          Wpk[3][11][0]*Wpk[4][11][0])))));
        temp[1] = ((3.51*((Vpk[3][12][2]*Vpk[4][12][2])+((Vpk[3][12][0]*
          Vpk[4][12][0])+(Vpk[3][12][1]*Vpk[4][12][1]))))+((.0484*(Wpk[3][12][2]
          *Wpk[4][12][2]))+((.0048*(Wpk[3][12][1]*Wpk[4][12][1]))+(.0477*(
          Wpk[3][12][0]*Wpk[4][12][0])))));
        temp[2] = ((1.2*((Vpk[3][14][2]*Vpk[4][14][2])+((Vpk[3][14][0]*
          Vpk[4][14][0])+(Vpk[3][14][1]*Vpk[4][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[4][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[4][14][0]))
          +(.003709*(Wpk[3][14][1]*Wpk[4][14][1])))));
        temp[3] = ((.205126*((Vpk[3][15][2]*Vpk[4][15][2])+((Vpk[3][15][0]*
          Vpk[4][15][0])+(Vpk[3][15][1]*Vpk[4][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[4][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[4][15][0]))
          +(.000179*(Wpk[3][15][1]*Wpk[4][15][1])))));
        temp[4] = (temp[3]+(temp[2]+(temp[1]+(temp[0]+((10.3786426*((
          Vpk[3][8][2]*Wpk[4][8][0])-(Vpk[3][8][0]*Wpk[4][8][2])))+((1.3552*(
          Wpk[3][8][2]*Wpk[4][8][2]))+((.7153*(Wpk[3][7][1]*Wpk[4][7][1]))+(
          1.396*(Wpk[3][8][0]*Wpk[4][8][0])))))))));
        temp[5] = (((8.806*((Vpk[3][18][2]*Vpk[4][18][2])+((Vpk[3][18][0]*
          Vpk[4][18][0])+(Vpk[3][18][1]*Vpk[4][18][1]))))+((.1337*(Wpk[3][18][2]
          *Wpk[4][18][2]))+((.0332*(Wpk[3][17][1]*Wpk[4][17][1]))+(.1268*(
          Wpk[3][18][0]*Wpk[4][18][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[3][19][2]*Vpk[4][19][2])+((Vpk[3][19][0]*
          Vpk[4][19][0])+(Vpk[3][19][1]*Vpk[4][19][1]))))+((.0484*(Wpk[3][19][2]
          *Wpk[4][19][2]))+((.0048*(Wpk[3][19][1]*Wpk[4][19][1]))+(.0477*(
          Wpk[3][19][0]*Wpk[4][19][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[3][21][2]*Vpk[4][21][2])+((Vpk[3][21][0]*
          Vpk[4][21][0])+(Vpk[3][21][1]*Vpk[4][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[4][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[4][21][0]))
          +(.003709*(Wpk[3][21][1]*Wpk[4][21][1])))))+temp[6]);
        mm[3][4] = (((.205126*((Vpk[3][22][2]*Vpk[4][22][2])+((Vpk[3][22][0]*
          Vpk[4][22][0])+(Vpk[3][22][1]*Vpk[4][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[4][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[4][22][0]))
          +(.000179*(Wpk[3][22][1]*Wpk[4][22][1])))))+temp[7]);
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[5][11][2])+((Vpk[3][11][0]*
          Vpk[5][11][0])+(Vpk[3][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[3][11][2]
          *Wpk[5][11][2]))+((.0332*(Wpk[3][10][1]*s10))+(.1268*(Wpk[3][11][0]*
          Wpk[5][11][0])))));
        temp[1] = ((3.51*((Vpk[3][12][2]*Vpk[5][12][2])+((Vpk[3][12][0]*
          Vpk[5][12][0])+(Vpk[3][12][1]*Vpk[5][12][1]))))+((.0484*(Wpk[3][12][2]
          *Wpk[5][12][2]))+((.0048*(Wpk[3][12][1]*Wpk[5][12][1]))+(.0477*(
          Wpk[3][12][0]*Wpk[5][12][0])))));
        temp[2] = (temp[1]+(temp[0]+((32.413*((Vpk[3][8][2]*Vpk[5][8][2])+((.127
          *(Vpk[5][7][1]*s7))+(Vpk[3][8][0]*Vpk[5][8][0]))))+((1.3552*(
          Wpk[3][8][2]*Wpk[5][8][2]))+((.7153*(Wpk[3][7][1]*s7))+(1.396*(
          Wpk[3][8][0]*Wpk[5][8][0])))))));
        temp[3] = (((1.2*((Vpk[3][14][2]*Vpk[5][14][2])+((Vpk[3][14][0]*
          Vpk[5][14][0])+(Vpk[3][14][1]*Vpk[5][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[5][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[5][14][0]))
          +(.003709*(Wpk[3][14][1]*Wpk[5][14][1])))))+temp[2]);
        temp[4] = (((.205126*((Vpk[3][15][2]*Vpk[5][15][2])+((Vpk[3][15][0]*
          Vpk[5][15][0])+(Vpk[3][15][1]*Vpk[5][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[5][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[5][15][0]))
          +(.000179*(Wpk[3][15][1]*Wpk[5][15][1])))))+temp[3]);
        temp[5] = ((3.51*((Vpk[3][19][2]*Vpk[5][19][2])+((Vpk[3][19][0]*
          Vpk[5][19][0])+(Vpk[3][19][1]*Vpk[5][19][1]))))+((.0484*(Wpk[3][19][2]
          *Wpk[5][19][2]))+((.0048*(Wpk[3][19][1]*Wpk[5][19][1]))+(.0477*(
          Wpk[3][19][0]*Wpk[5][19][0])))));
        temp[6] = (temp[5]+(((8.806*((Vpk[3][18][2]*Vpk[5][18][2])+((
          Vpk[3][18][0]*Vpk[5][18][0])+(Vpk[3][18][1]*Vpk[5][18][1]))))+((.1337*
          (Wpk[3][18][2]*Wpk[5][18][2]))+((.1268*(Wpk[3][18][0]*Wpk[5][18][0]))-
          (.0332*(Wpk[3][17][1]*s17)))))+temp[4]));
        temp[7] = (((1.2*((Vpk[3][21][2]*Vpk[5][21][2])+((Vpk[3][21][0]*
          Vpk[5][21][0])+(Vpk[3][21][1]*Vpk[5][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[5][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[5][21][0]))
          +(.003709*(Wpk[3][21][1]*Wpk[5][21][1])))))+temp[6]);
        mm[3][5] = (((.205126*((Vpk[3][22][2]*Vpk[5][22][2])+((Vpk[3][22][0]*
          Vpk[5][22][0])+(Vpk[3][22][1]*Vpk[5][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[5][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[5][22][0]))
          +(.000179*(Wpk[3][22][1]*Wpk[5][22][1])))))+temp[7]);
        mm[3][6] = ((10.3786426*((Vpk[3][8][2]*Wpk[6][8][0])-(Vpk[3][8][0]*
          Wpk[6][8][2])))+((1.3552*(Wpk[3][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[3][7][1]*s7))+(1.396*(Wpk[3][8][0]*Wpk[6][8][0])))));
        mm[3][7] = ((10.3786426*((Vpk[3][8][2]*c8)-(Vpk[3][8][0]*s8)))+((1.3552*
          (Wpk[3][8][2]*s8))+(1.396*(Wpk[3][8][0]*c8))));
        mm[3][8] = (.7153*Wpk[3][7][1]);
        temp[0] = ((8.806*((Vpk[3][11][2]*Vpk[9][11][2])+((.1715*(Vpk[3][11][0]*
          Wpk[9][11][2]))-(.002*(Vpk[3][11][1]*Wpk[9][11][2])))))+((.1337*(
          Wpk[3][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[3][10][1]*s10))+(.1268*(
          Wpk[3][11][0]*Wpk[9][11][0])))));
        temp[1] = (((3.51*((Vpk[3][12][2]*Vpk[9][12][2])+((Vpk[3][12][0]*
          Vpk[9][12][0])+(Vpk[3][12][1]*Vpk[9][12][1]))))+((.0484*(Wpk[3][12][2]
          *Wpk[9][12][2]))+((.0048*(Wpk[3][12][1]*Wpk[9][12][1]))+(.0477*(
          Wpk[3][12][0]*Wpk[9][12][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][14][2]*Vpk[9][14][2])+((Vpk[3][14][0]*
          Vpk[9][14][0])+(Vpk[3][14][1]*Vpk[9][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[9][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[9][14][0]))
          +(.003709*(Wpk[3][14][1]*Wpk[9][14][1])))))+temp[1]);
        mm[3][9] = (((.205126*((Vpk[3][15][2]*Vpk[9][15][2])+((Vpk[3][15][0]*
          Vpk[9][15][0])+(Vpk[3][15][1]*Vpk[9][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[9][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[9][15][0]))
          +(.000179*(Wpk[3][15][1]*Wpk[9][15][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[3][12][2]*Vpk[10][12][2])+((Vpk[3][12][0]*
          Vpk[10][12][0])+(Vpk[3][12][1]*Vpk[10][12][1]))))+((.0484*(
          Wpk[3][12][2]*Wpk[10][12][2]))+((.0048*(Wpk[3][12][1]*Wpk[10][12][1]))
          +(.0477*(Wpk[3][12][0]*Wpk[10][12][0])))))+((8.806*(((.1715*(
          Vpk[3][11][0]*s11))-(.002*(Vpk[3][11][1]*s11)))-(.1715*(Vpk[3][11][2]*
          c11))))+((.1268*(Wpk[3][11][0]*c11))+(.1337*(Wpk[3][11][2]*s11)))));
        temp[1] = (((1.2*((Vpk[3][14][2]*Vpk[10][14][2])+((Vpk[3][14][0]*
          Vpk[10][14][0])+(Vpk[3][14][1]*Vpk[10][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[10][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[10][14][0]
          ))+(.003709*(Wpk[3][14][1]*Wpk[10][14][1])))))+temp[0]);
        mm[3][10] = (((.205126*((Vpk[3][15][2]*Vpk[10][15][2])+((Vpk[3][15][0]*
          Vpk[10][15][0])+(Vpk[3][15][1]*Vpk[10][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[10][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[10][15][0]
          ))+(.000179*(Wpk[3][15][1]*Wpk[10][15][1])))))+temp[1]);
        temp[0] = (((.017612*Vpk[3][11][2])+(.0332*Wpk[3][10][1]))+((3.51*((
          Vpk[3][12][2]*Vpk[11][12][2])+((Vpk[3][12][0]*Vpk[11][12][0])-(.0013*(
          Cik[12][2][1]*Vpk[3][12][1])))))+((.0484*(Cik[12][1][2]*Wpk[3][12][2])
          )+((.0048*(Cik[12][1][1]*Wpk[3][12][1]))+(.0477*(Cik[12][1][0]*
          Wpk[3][12][0]))))));
        temp[1] = (((1.2*((Vpk[3][14][2]*Vpk[11][14][2])+((Vpk[3][14][0]*
          Vpk[11][14][0])+(Vpk[3][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[11][14][0]
          ))+(.003709*(Wpk[3][14][1]*Wpk[11][14][1])))))+temp[0]);
        mm[3][11] = (((.205126*((Vpk[3][15][2]*Vpk[11][15][2])+((Vpk[3][15][0]*
          Vpk[11][15][0])+(Vpk[3][15][1]*Vpk[11][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[11][15][0]
          ))+(.000179*(Wpk[3][15][1]*Wpk[11][15][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[3][14][2]*Vpk[12][14][2])+((Vpk[3][14][0]*
          Vpk[12][14][0])+(Vpk[3][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[12][14][0]
          ))+(.003709*(Wpk[3][14][1]*Wpk[12][14][1])))))+((3.51*((
          .0150652581855386*Vpk[3][12][2])+(.185436609363333*Vpk[3][12][0])))+((
          .0482015676325742*Wpk[3][12][2])+((.000194184030748461*Wpk[3][12][1])-
          (.00385935991111811*Wpk[3][12][0])))));
        mm[3][12] = (((.205126*((Vpk[3][15][2]*Vpk[12][15][2])+((Vpk[3][15][0]*
          Vpk[12][15][0])+(Vpk[3][15][1]*Vpk[12][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[12][15][0]
          ))+(.000179*(Wpk[3][15][1]*Wpk[12][15][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][14][2]*Vpk[13][14][2])+((Vpk[3][14][0]*
          Vpk[13][14][0])+(Vpk[3][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[3][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[3][14][0]*Wpk[13][14][0]
          ))+(.003709*(Wpk[3][14][1]*Wpk[13][14][1])))));
        mm[3][13] = (((.205126*((Vpk[3][15][2]*Vpk[13][15][2])+((Vpk[3][15][0]*
          Vpk[13][15][0])+(Vpk[3][15][1]*Vpk[13][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[13][15][0]
          ))+(.000179*(Wpk[3][15][1]*Wpk[13][15][1])))))+temp[0]);
        mm[3][14] = (((.205126*((Vpk[3][15][2]*Vpk[14][15][2])+((Vpk[3][15][0]*
          Vpk[14][15][0])+(Vpk[3][15][1]*Vpk[14][15][1]))))+((.000119*(
          Wpk[3][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[3][15][0]*Wpk[14][15][0]
          ))+(.000179*(Wpk[3][15][1]*Wpk[14][15][1])))))+((1.2*(((
          .000411457536296252*Vpk[3][14][0])-(.00646090297985859*Vpk[3][14][1]))
          -(.0625600530375351*Vpk[3][14][2])))+(((.00110888270658752*
          Wpk[3][14][0])+(.00214105693566144*Wpk[3][14][1]))-(
          .000212474287874234*Wpk[3][14][2]))));
        mm[3][15] = ((.205126*(((.02617891313962*Vpk[3][15][1])-(
          .0163345287751755*Vpk[3][15][0]))-(.00868522709507149*Vpk[3][15][2])))
          +((.00010507075266194*Wpk[3][15][2])-(5.49281929796413e-5*
          Wpk[3][15][0])));
        temp[0] = ((8.806*((Vpk[3][18][2]*Vpk[16][18][2])+((.1715*(Vpk[3][18][0]
          *Wpk[16][18][2]))-(.002*(Vpk[3][18][1]*Wpk[16][18][2])))))+((.1337*(
          Wpk[3][18][2]*Wpk[16][18][2]))+((.1268*(Wpk[3][18][0]*Wpk[16][18][0]))
          -(.0332*(Wpk[3][17][1]*s17)))));
        temp[1] = (((3.51*((Vpk[3][19][2]*Vpk[16][19][2])+((Vpk[3][19][0]*
          Vpk[16][19][0])+(Vpk[3][19][1]*Vpk[16][19][1]))))+((.0484*(
          Wpk[3][19][2]*Wpk[16][19][2]))+((.0048*(Wpk[3][19][1]*Wpk[16][19][1]))
          +(.0477*(Wpk[3][19][0]*Wpk[16][19][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[3][21][2]*Vpk[16][21][2])+((Vpk[3][21][0]*
          Vpk[16][21][0])+(Vpk[3][21][1]*Vpk[16][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[16][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[16][21][0]
          ))+(.003709*(Wpk[3][21][1]*Wpk[16][21][1])))))+temp[1]);
        mm[3][16] = (((.205126*((Vpk[3][22][2]*Vpk[16][22][2])+((Vpk[3][22][0]*
          Vpk[16][22][0])+(Vpk[3][22][1]*Vpk[16][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[16][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[16][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[16][22][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[3][19][2]*Vpk[17][19][2])+((Vpk[3][19][0]*
          Vpk[17][19][0])+(Vpk[3][19][1]*Vpk[17][19][1]))))+((.0484*(
          Wpk[3][19][2]*Wpk[17][19][2]))+((.0048*(Wpk[3][19][1]*Wpk[17][19][1]))
          +(.0477*(Wpk[3][19][0]*Wpk[17][19][0])))))+((8.806*((.1715*(
          Vpk[3][18][2]*c18))+((.1715*(Vpk[3][18][0]*s18))-(.002*(Vpk[3][18][1]*
          s18)))))+((.1337*(Wpk[3][18][2]*s18))-(.1268*(Wpk[3][18][0]*c18)))));
        temp[1] = (((1.2*((Vpk[3][21][2]*Vpk[17][21][2])+((Vpk[3][21][0]*
          Vpk[17][21][0])+(Vpk[3][21][1]*Vpk[17][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[17][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[17][21][0]
          ))+(.003709*(Wpk[3][21][1]*Wpk[17][21][1])))))+temp[0]);
        mm[3][17] = (((.205126*((Vpk[3][22][2]*Vpk[17][22][2])+((Vpk[3][22][0]*
          Vpk[17][22][0])+(Vpk[3][22][1]*Vpk[17][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[17][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[17][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[17][22][1])))))+temp[1]);
        temp[0] = (((3.51*((Vpk[3][19][2]*Vpk[18][19][2])+((.0013*(Cik[19][2][1]
          *Vpk[3][19][1]))+(Vpk[3][19][0]*Vpk[18][19][0]))))-((.0484*(
          Cik[19][1][2]*Wpk[3][19][2]))+((.0048*(Cik[19][1][1]*Wpk[3][19][1]))+(
          .0477*(Cik[19][1][0]*Wpk[3][19][0])))))-((.017612*Vpk[3][18][2])+(
          .0332*Wpk[3][17][1])));
        temp[1] = (((1.2*((Vpk[3][21][2]*Vpk[18][21][2])+((Vpk[3][21][0]*
          Vpk[18][21][0])+(Vpk[3][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[18][21][0]
          ))+(.003709*(Wpk[3][21][1]*Wpk[18][21][1])))))+temp[0]);
        mm[3][18] = (((.205126*((Vpk[3][22][2]*Vpk[18][22][2])+((Vpk[3][22][0]*
          Vpk[18][22][0])+(Vpk[3][22][1]*Vpk[18][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[18][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[18][22][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[3][21][2]*Vpk[19][21][2])+((Vpk[3][21][0]*
          Vpk[19][21][0])+(Vpk[3][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[19][21][0]
          ))+(.003709*(Wpk[3][21][1]*Wpk[19][21][1])))))+((3.51*((
          .185436609363333*Vpk[3][19][0])-(.0150652581855386*Vpk[3][19][2])))+((
          .0482015676325742*Wpk[3][19][2])+((.00385935991111811*Wpk[3][19][0])-(
          .000194184030748461*Wpk[3][19][1])))));
        mm[3][19] = (((.205126*((Vpk[3][22][2]*Vpk[19][22][2])+((Vpk[3][22][0]*
          Vpk[19][22][0])+(Vpk[3][22][1]*Vpk[19][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[19][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[19][22][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[3][21][2]*Vpk[20][21][2])+((Vpk[3][21][0]*
          Vpk[20][21][0])+(Vpk[3][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[3][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[3][21][0]*Wpk[20][21][0]
          ))+(.003709*(Wpk[3][21][1]*Wpk[20][21][1])))));
        mm[3][20] = (((.205126*((Vpk[3][22][2]*Vpk[20][22][2])+((Vpk[3][22][0]*
          Vpk[20][22][0])+(Vpk[3][22][1]*Vpk[20][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[20][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[20][22][1])))))+temp[0]);
        mm[3][21] = (((.205126*((Vpk[3][22][2]*Vpk[21][22][2])+((Vpk[3][22][0]*
          Vpk[21][22][0])+(Vpk[3][22][1]*Vpk[21][22][1]))))+((.000119*(
          Wpk[3][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[3][22][0]*Wpk[21][22][0]
          ))+(.000179*(Wpk[3][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[3][21][2])+((.000411457536296252*Vpk[3][21][0])-
          (.00646090297985859*Vpk[3][21][1]))))-((.000212474287874234*
          Wpk[3][21][2])+((.00110888270658752*Wpk[3][21][0])+(.00214105693566144
          *Wpk[3][21][1])))));
        mm[3][22] = ((.205126*((.00868522709507149*Vpk[3][22][2])+((
          .02617891313962*Vpk[3][22][1])-(.0163345287751755*Vpk[3][22][0]))))+((
          5.49281929796413e-5*Wpk[3][22][0])+(.00010507075266194*Wpk[3][22][2]))
          );
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[4][11][2])+((Vpk[4][11][0]*
          Vpk[4][11][0])+(Vpk[4][11][1]*Vpk[4][11][1]))))+((.1337*(Wpk[4][11][2]
          *Wpk[4][11][2]))+((.0332*(Wpk[4][10][1]*Wpk[4][10][1]))+(.1268*(
          Wpk[4][11][0]*Wpk[4][11][0])))));
        temp[1] = ((3.51*((Vpk[4][12][2]*Vpk[4][12][2])+((Vpk[4][12][0]*
          Vpk[4][12][0])+(Vpk[4][12][1]*Vpk[4][12][1]))))+((.0484*(Wpk[4][12][2]
          *Wpk[4][12][2]))+((.0048*(Wpk[4][12][1]*Wpk[4][12][1]))+(.0477*(
          Wpk[4][12][0]*Wpk[4][12][0])))));
        temp[2] = ((1.2*((Vpk[4][14][2]*Vpk[4][14][2])+((Vpk[4][14][0]*
          Vpk[4][14][0])+(Vpk[4][14][1]*Vpk[4][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[4][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[4][14][0]))
          +(.003709*(Wpk[4][14][1]*Wpk[4][14][1])))));
        temp[3] = ((.205126*((Vpk[4][15][2]*Vpk[4][15][2])+((Vpk[4][15][0]*
          Vpk[4][15][0])+(Vpk[4][15][1]*Vpk[4][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[4][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[4][15][0]))
          +(.000179*(Wpk[4][15][1]*Wpk[4][15][1])))));
        temp[4] = (temp[3]+(temp[2]+(temp[1]+(((3.32324136052*((Wpk[4][8][0]*
          Wpk[4][8][0])+(Wpk[4][8][2]*Wpk[4][8][2])))+((1.3552*(Wpk[4][8][2]*
          Wpk[4][8][2]))+((.7153*(Wpk[4][7][1]*Wpk[4][7][1]))+(1.396*(
          Wpk[4][8][0]*Wpk[4][8][0])))))+temp[0]))));
        temp[5] = (((8.806*((Vpk[4][18][2]*Vpk[4][18][2])+((Vpk[4][18][0]*
          Vpk[4][18][0])+(Vpk[4][18][1]*Vpk[4][18][1]))))+((.1337*(Wpk[4][18][2]
          *Wpk[4][18][2]))+((.0332*(Wpk[4][17][1]*Wpk[4][17][1]))+(.1268*(
          Wpk[4][18][0]*Wpk[4][18][0])))))+temp[4]);
        temp[6] = (((3.51*((Vpk[4][19][2]*Vpk[4][19][2])+((Vpk[4][19][0]*
          Vpk[4][19][0])+(Vpk[4][19][1]*Vpk[4][19][1]))))+((.0484*(Wpk[4][19][2]
          *Wpk[4][19][2]))+((.0048*(Wpk[4][19][1]*Wpk[4][19][1]))+(.0477*(
          Wpk[4][19][0]*Wpk[4][19][0])))))+temp[5]);
        temp[7] = (((1.2*((Vpk[4][21][2]*Vpk[4][21][2])+((Vpk[4][21][0]*
          Vpk[4][21][0])+(Vpk[4][21][1]*Vpk[4][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[4][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[4][21][0]))
          +(.003709*(Wpk[4][21][1]*Wpk[4][21][1])))))+temp[6]);
        mm[4][4] = (.0825+(((.205126*((Vpk[4][22][2]*Vpk[4][22][2])+((
          Vpk[4][22][0]*Vpk[4][22][0])+(Vpk[4][22][1]*Vpk[4][22][1]))))+((
          .000119*(Wpk[4][22][2]*Wpk[4][22][2]))+((.000117*(Wpk[4][22][0]*
          Wpk[4][22][0]))+(.000179*(Wpk[4][22][1]*Wpk[4][22][1])))))+temp[7]));
        temp[0] = (((8.806*((Vpk[4][11][2]*Vpk[5][11][2])+((Vpk[4][11][0]*
          Vpk[5][11][0])+(Vpk[4][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[4][11][2]
          *Wpk[5][11][2]))+((.0332*(Wpk[4][10][1]*s10))+(.1268*(Wpk[4][11][0]*
          Wpk[5][11][0])))))+((10.3786426*((Vpk[5][8][2]*Wpk[4][8][0])-(
          Vpk[5][8][0]*Wpk[4][8][2])))+((1.3552*(Wpk[4][8][2]*Wpk[5][8][2]))+((
          .7153*(Wpk[4][7][1]*s7))+(1.396*(Wpk[4][8][0]*Wpk[5][8][0]))))));
        temp[1] = (((3.51*((Vpk[4][12][2]*Vpk[5][12][2])+((Vpk[4][12][0]*
          Vpk[5][12][0])+(Vpk[4][12][1]*Vpk[5][12][1]))))+((.0484*(Wpk[4][12][2]
          *Wpk[5][12][2]))+((.0048*(Wpk[4][12][1]*Wpk[5][12][1]))+(.0477*(
          Wpk[4][12][0]*Wpk[5][12][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][14][2]*Vpk[5][14][2])+((Vpk[4][14][0]*
          Vpk[5][14][0])+(Vpk[4][14][1]*Vpk[5][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[5][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[5][14][0]))
          +(.003709*(Wpk[4][14][1]*Wpk[5][14][1])))))+temp[1]);
        temp[3] = (((.205126*((Vpk[4][15][2]*Vpk[5][15][2])+((Vpk[4][15][0]*
          Vpk[5][15][0])+(Vpk[4][15][1]*Vpk[5][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[5][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[5][15][0]))
          +(.000179*(Wpk[4][15][1]*Wpk[5][15][1])))))+temp[2]);
        temp[4] = ((3.51*((Vpk[4][19][2]*Vpk[5][19][2])+((Vpk[4][19][0]*
          Vpk[5][19][0])+(Vpk[4][19][1]*Vpk[5][19][1]))))+((.0484*(Wpk[4][19][2]
          *Wpk[5][19][2]))+((.0048*(Wpk[4][19][1]*Wpk[5][19][1]))+(.0477*(
          Wpk[4][19][0]*Wpk[5][19][0])))));
        temp[5] = (temp[4]+(((8.806*((Vpk[4][18][2]*Vpk[5][18][2])+((
          Vpk[4][18][0]*Vpk[5][18][0])+(Vpk[4][18][1]*Vpk[5][18][1]))))+((.1337*
          (Wpk[4][18][2]*Wpk[5][18][2]))+((.1268*(Wpk[4][18][0]*Wpk[5][18][0]))-
          (.0332*(Wpk[4][17][1]*s17)))))+temp[3]));
        temp[6] = (((1.2*((Vpk[4][21][2]*Vpk[5][21][2])+((Vpk[4][21][0]*
          Vpk[5][21][0])+(Vpk[4][21][1]*Vpk[5][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[5][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[5][21][0]))
          +(.003709*(Wpk[4][21][1]*Wpk[5][21][1])))))+temp[5]);
        mm[4][5] = (((.205126*((Vpk[4][22][2]*Vpk[5][22][2])+((Vpk[4][22][0]*
          Vpk[5][22][0])+(Vpk[4][22][1]*Vpk[5][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[5][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[5][22][0]))
          +(.000179*(Wpk[4][22][1]*Wpk[5][22][1])))))+temp[6]);
        mm[4][6] = ((3.32324136052*((Wpk[4][8][0]*Wpk[6][8][0])+(Wpk[4][8][2]*
          Wpk[6][8][2])))+((1.3552*(Wpk[4][8][2]*Wpk[6][8][2]))+((.7153*(
          Wpk[4][7][1]*s7))+(1.396*(Wpk[4][8][0]*Wpk[6][8][0])))));
        mm[4][7] = ((3.32324136052*((Wpk[4][8][0]*c8)+(Wpk[4][8][2]*s8)))+((
          1.3552*(Wpk[4][8][2]*s8))+(1.396*(Wpk[4][8][0]*c8))));
        mm[4][8] = (.7153*Wpk[4][7][1]);
        temp[0] = ((8.806*((Vpk[4][11][2]*Vpk[9][11][2])+((.1715*(Vpk[4][11][0]*
          Wpk[9][11][2]))-(.002*(Vpk[4][11][1]*Wpk[9][11][2])))))+((.1337*(
          Wpk[4][11][2]*Wpk[9][11][2]))+((.0332*(Wpk[4][10][1]*s10))+(.1268*(
          Wpk[4][11][0]*Wpk[9][11][0])))));
        temp[1] = (((3.51*((Vpk[4][12][2]*Vpk[9][12][2])+((Vpk[4][12][0]*
          Vpk[9][12][0])+(Vpk[4][12][1]*Vpk[9][12][1]))))+((.0484*(Wpk[4][12][2]
          *Wpk[9][12][2]))+((.0048*(Wpk[4][12][1]*Wpk[9][12][1]))+(.0477*(
          Wpk[4][12][0]*Wpk[9][12][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][14][2]*Vpk[9][14][2])+((Vpk[4][14][0]*
          Vpk[9][14][0])+(Vpk[4][14][1]*Vpk[9][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[9][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[9][14][0]))
          +(.003709*(Wpk[4][14][1]*Wpk[9][14][1])))))+temp[1]);
        mm[4][9] = (((.205126*((Vpk[4][15][2]*Vpk[9][15][2])+((Vpk[4][15][0]*
          Vpk[9][15][0])+(Vpk[4][15][1]*Vpk[9][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[9][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[9][15][0]))
          +(.000179*(Wpk[4][15][1]*Wpk[9][15][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[4][12][2]*Vpk[10][12][2])+((Vpk[4][12][0]*
          Vpk[10][12][0])+(Vpk[4][12][1]*Vpk[10][12][1]))))+((.0484*(
          Wpk[4][12][2]*Wpk[10][12][2]))+((.0048*(Wpk[4][12][1]*Wpk[10][12][1]))
          +(.0477*(Wpk[4][12][0]*Wpk[10][12][0])))))+((8.806*(((.1715*(
          Vpk[4][11][0]*s11))-(.002*(Vpk[4][11][1]*s11)))-(.1715*(Vpk[4][11][2]*
          c11))))+((.1268*(Wpk[4][11][0]*c11))+(.1337*(Wpk[4][11][2]*s11)))));
        temp[1] = (((1.2*((Vpk[4][14][2]*Vpk[10][14][2])+((Vpk[4][14][0]*
          Vpk[10][14][0])+(Vpk[4][14][1]*Vpk[10][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[10][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[10][14][0]
          ))+(.003709*(Wpk[4][14][1]*Wpk[10][14][1])))))+temp[0]);
        mm[4][10] = (((.205126*((Vpk[4][15][2]*Vpk[10][15][2])+((Vpk[4][15][0]*
          Vpk[10][15][0])+(Vpk[4][15][1]*Vpk[10][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[10][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[10][15][0]
          ))+(.000179*(Wpk[4][15][1]*Wpk[10][15][1])))))+temp[1]);
        temp[0] = (((.017612*Vpk[4][11][2])+(.0332*Wpk[4][10][1]))+((3.51*((
          Vpk[4][12][2]*Vpk[11][12][2])+((Vpk[4][12][0]*Vpk[11][12][0])-(.0013*(
          Cik[12][2][1]*Vpk[4][12][1])))))+((.0484*(Cik[12][1][2]*Wpk[4][12][2])
          )+((.0048*(Cik[12][1][1]*Wpk[4][12][1]))+(.0477*(Cik[12][1][0]*
          Wpk[4][12][0]))))));
        temp[1] = (((1.2*((Vpk[4][14][2]*Vpk[11][14][2])+((Vpk[4][14][0]*
          Vpk[11][14][0])+(Vpk[4][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[11][14][0]
          ))+(.003709*(Wpk[4][14][1]*Wpk[11][14][1])))))+temp[0]);
        mm[4][11] = (((.205126*((Vpk[4][15][2]*Vpk[11][15][2])+((Vpk[4][15][0]*
          Vpk[11][15][0])+(Vpk[4][15][1]*Vpk[11][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[11][15][0]
          ))+(.000179*(Wpk[4][15][1]*Wpk[11][15][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[4][14][2]*Vpk[12][14][2])+((Vpk[4][14][0]*
          Vpk[12][14][0])+(Vpk[4][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[12][14][0]
          ))+(.003709*(Wpk[4][14][1]*Wpk[12][14][1])))))+((3.51*((
          .0150652581855386*Vpk[4][12][2])+(.185436609363333*Vpk[4][12][0])))+((
          .0482015676325742*Wpk[4][12][2])+((.000194184030748461*Wpk[4][12][1])-
          (.00385935991111811*Wpk[4][12][0])))));
        mm[4][12] = (((.205126*((Vpk[4][15][2]*Vpk[12][15][2])+((Vpk[4][15][0]*
          Vpk[12][15][0])+(Vpk[4][15][1]*Vpk[12][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[12][15][0]
          ))+(.000179*(Wpk[4][15][1]*Wpk[12][15][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][14][2]*Vpk[13][14][2])+((Vpk[4][14][0]*
          Vpk[13][14][0])+(Vpk[4][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[4][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[4][14][0]*Wpk[13][14][0]
          ))+(.003709*(Wpk[4][14][1]*Wpk[13][14][1])))));
        mm[4][13] = (((.205126*((Vpk[4][15][2]*Vpk[13][15][2])+((Vpk[4][15][0]*
          Vpk[13][15][0])+(Vpk[4][15][1]*Vpk[13][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[13][15][0]
          ))+(.000179*(Wpk[4][15][1]*Wpk[13][15][1])))))+temp[0]);
        mm[4][14] = (((.205126*((Vpk[4][15][2]*Vpk[14][15][2])+((Vpk[4][15][0]*
          Vpk[14][15][0])+(Vpk[4][15][1]*Vpk[14][15][1]))))+((.000119*(
          Wpk[4][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[4][15][0]*Wpk[14][15][0]
          ))+(.000179*(Wpk[4][15][1]*Wpk[14][15][1])))))+((1.2*(((
          .000411457536296252*Vpk[4][14][0])-(.00646090297985859*Vpk[4][14][1]))
          -(.0625600530375351*Vpk[4][14][2])))+(((.00110888270658752*
          Wpk[4][14][0])+(.00214105693566144*Wpk[4][14][1]))-(
          .000212474287874234*Wpk[4][14][2]))));
        mm[4][15] = ((.205126*(((.02617891313962*Vpk[4][15][1])-(
          .0163345287751755*Vpk[4][15][0]))-(.00868522709507149*Vpk[4][15][2])))
          +((.00010507075266194*Wpk[4][15][2])-(5.49281929796413e-5*
          Wpk[4][15][0])));
        temp[0] = ((8.806*((Vpk[4][18][2]*Vpk[16][18][2])+((.1715*(Vpk[4][18][0]
          *Wpk[16][18][2]))-(.002*(Vpk[4][18][1]*Wpk[16][18][2])))))+((.1337*(
          Wpk[4][18][2]*Wpk[16][18][2]))+((.1268*(Wpk[4][18][0]*Wpk[16][18][0]))
          -(.0332*(Wpk[4][17][1]*s17)))));
        temp[1] = (((3.51*((Vpk[4][19][2]*Vpk[16][19][2])+((Vpk[4][19][0]*
          Vpk[16][19][0])+(Vpk[4][19][1]*Vpk[16][19][1]))))+((.0484*(
          Wpk[4][19][2]*Wpk[16][19][2]))+((.0048*(Wpk[4][19][1]*Wpk[16][19][1]))
          +(.0477*(Wpk[4][19][0]*Wpk[16][19][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[4][21][2]*Vpk[16][21][2])+((Vpk[4][21][0]*
          Vpk[16][21][0])+(Vpk[4][21][1]*Vpk[16][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[16][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[16][21][0]
          ))+(.003709*(Wpk[4][21][1]*Wpk[16][21][1])))))+temp[1]);
        mm[4][16] = (((.205126*((Vpk[4][22][2]*Vpk[16][22][2])+((Vpk[4][22][0]*
          Vpk[16][22][0])+(Vpk[4][22][1]*Vpk[16][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[16][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[16][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[16][22][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[4][19][2]*Vpk[17][19][2])+((Vpk[4][19][0]*
          Vpk[17][19][0])+(Vpk[4][19][1]*Vpk[17][19][1]))))+((.0484*(
          Wpk[4][19][2]*Wpk[17][19][2]))+((.0048*(Wpk[4][19][1]*Wpk[17][19][1]))
          +(.0477*(Wpk[4][19][0]*Wpk[17][19][0])))))+((8.806*((.1715*(
          Vpk[4][18][2]*c18))+((.1715*(Vpk[4][18][0]*s18))-(.002*(Vpk[4][18][1]*
          s18)))))+((.1337*(Wpk[4][18][2]*s18))-(.1268*(Wpk[4][18][0]*c18)))));
        temp[1] = (((1.2*((Vpk[4][21][2]*Vpk[17][21][2])+((Vpk[4][21][0]*
          Vpk[17][21][0])+(Vpk[4][21][1]*Vpk[17][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[17][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[17][21][0]
          ))+(.003709*(Wpk[4][21][1]*Wpk[17][21][1])))))+temp[0]);
        mm[4][17] = (((.205126*((Vpk[4][22][2]*Vpk[17][22][2])+((Vpk[4][22][0]*
          Vpk[17][22][0])+(Vpk[4][22][1]*Vpk[17][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[17][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[17][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[17][22][1])))))+temp[1]);
        temp[0] = (((3.51*((Vpk[4][19][2]*Vpk[18][19][2])+((.0013*(Cik[19][2][1]
          *Vpk[4][19][1]))+(Vpk[4][19][0]*Vpk[18][19][0]))))-((.0484*(
          Cik[19][1][2]*Wpk[4][19][2]))+((.0048*(Cik[19][1][1]*Wpk[4][19][1]))+(
          .0477*(Cik[19][1][0]*Wpk[4][19][0])))))-((.017612*Vpk[4][18][2])+(
          .0332*Wpk[4][17][1])));
        temp[1] = (((1.2*((Vpk[4][21][2]*Vpk[18][21][2])+((Vpk[4][21][0]*
          Vpk[18][21][0])+(Vpk[4][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[18][21][0]
          ))+(.003709*(Wpk[4][21][1]*Wpk[18][21][1])))))+temp[0]);
        mm[4][18] = (((.205126*((Vpk[4][22][2]*Vpk[18][22][2])+((Vpk[4][22][0]*
          Vpk[18][22][0])+(Vpk[4][22][1]*Vpk[18][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[18][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[18][22][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[4][21][2]*Vpk[19][21][2])+((Vpk[4][21][0]*
          Vpk[19][21][0])+(Vpk[4][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[19][21][0]
          ))+(.003709*(Wpk[4][21][1]*Wpk[19][21][1])))))+((3.51*((
          .185436609363333*Vpk[4][19][0])-(.0150652581855386*Vpk[4][19][2])))+((
          .0482015676325742*Wpk[4][19][2])+((.00385935991111811*Wpk[4][19][0])-(
          .000194184030748461*Wpk[4][19][1])))));
        mm[4][19] = (((.205126*((Vpk[4][22][2]*Vpk[19][22][2])+((Vpk[4][22][0]*
          Vpk[19][22][0])+(Vpk[4][22][1]*Vpk[19][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[19][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[19][22][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[4][21][2]*Vpk[20][21][2])+((Vpk[4][21][0]*
          Vpk[20][21][0])+(Vpk[4][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[4][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[4][21][0]*Wpk[20][21][0]
          ))+(.003709*(Wpk[4][21][1]*Wpk[20][21][1])))));
        mm[4][20] = (((.205126*((Vpk[4][22][2]*Vpk[20][22][2])+((Vpk[4][22][0]*
          Vpk[20][22][0])+(Vpk[4][22][1]*Vpk[20][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[20][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[20][22][1])))))+temp[0]);
        mm[4][21] = (((.205126*((Vpk[4][22][2]*Vpk[21][22][2])+((Vpk[4][22][0]*
          Vpk[21][22][0])+(Vpk[4][22][1]*Vpk[21][22][1]))))+((.000119*(
          Wpk[4][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[4][22][0]*Wpk[21][22][0]
          ))+(.000179*(Wpk[4][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[4][21][2])+((.000411457536296252*Vpk[4][21][0])-
          (.00646090297985859*Vpk[4][21][1]))))-((.000212474287874234*
          Wpk[4][21][2])+((.00110888270658752*Wpk[4][21][0])+(.00214105693566144
          *Wpk[4][21][1])))));
        mm[4][22] = ((.205126*((.00868522709507149*Vpk[4][22][2])+((
          .02617891313962*Vpk[4][22][1])-(.0163345287751755*Vpk[4][22][0]))))+((
          5.49281929796413e-5*Wpk[4][22][0])+(.00010507075266194*Wpk[4][22][2]))
          );
        temp[0] = (((8.806*((Vpk[5][11][2]*Vpk[5][11][2])+((Vpk[5][11][0]*
          Vpk[5][11][0])+(Vpk[5][11][1]*Vpk[5][11][1]))))+((.1337*(Wpk[5][11][2]
          *Wpk[5][11][2]))+((.0332*(s10*s10))+(.1268*(Wpk[5][11][0]*
          Wpk[5][11][0])))))+((32.413*((Vpk[5][8][2]*Vpk[5][8][2])+((
          Vpk[5][7][1]*Vpk[5][7][1])+(Vpk[5][8][0]*Vpk[5][8][0]))))+((1.3552*(
          Wpk[5][8][2]*Wpk[5][8][2]))+((.7153*(s7*s7))+(1.396*(Wpk[5][8][0]*
          Wpk[5][8][0]))))));
        temp[1] = (((3.51*((Vpk[5][12][2]*Vpk[5][12][2])+((Vpk[5][12][0]*
          Vpk[5][12][0])+(Vpk[5][12][1]*Vpk[5][12][1]))))+((.0484*(Wpk[5][12][2]
          *Wpk[5][12][2]))+((.0048*(Wpk[5][12][1]*Wpk[5][12][1]))+(.0477*(
          Wpk[5][12][0]*Wpk[5][12][0])))))+temp[0]);
        temp[2] = (((1.2*((Vpk[5][14][2]*Vpk[5][14][2])+((Vpk[5][14][0]*
          Vpk[5][14][0])+(Vpk[5][14][1]*Vpk[5][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[5][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[5][14][0]))
          +(.003709*(Wpk[5][14][1]*Wpk[5][14][1])))))+temp[1]);
        temp[3] = (((.205126*((Vpk[5][15][2]*Vpk[5][15][2])+((Vpk[5][15][0]*
          Vpk[5][15][0])+(Vpk[5][15][1]*Vpk[5][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[5][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[5][15][0]))
          +(.000179*(Wpk[5][15][1]*Wpk[5][15][1])))))+temp[2]);
        temp[4] = ((3.51*((Vpk[5][19][2]*Vpk[5][19][2])+((Vpk[5][19][0]*
          Vpk[5][19][0])+(Vpk[5][19][1]*Vpk[5][19][1]))))+((.0484*(Wpk[5][19][2]
          *Wpk[5][19][2]))+((.0048*(Wpk[5][19][1]*Wpk[5][19][1]))+(.0477*(
          Wpk[5][19][0]*Wpk[5][19][0])))));
        temp[5] = ((1.2*((Vpk[5][21][2]*Vpk[5][21][2])+((Vpk[5][21][0]*
          Vpk[5][21][0])+(Vpk[5][21][1]*Vpk[5][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[5][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[5][21][0]))
          +(.003709*(Wpk[5][21][1]*Wpk[5][21][1])))));
        temp[6] = (temp[5]+(temp[4]+(((8.806*((Vpk[5][18][2]*Vpk[5][18][2])+((
          Vpk[5][18][0]*Vpk[5][18][0])+(Vpk[5][18][1]*Vpk[5][18][1]))))+((.1337*
          (Wpk[5][18][2]*Wpk[5][18][2]))+((.0332*(s17*s17))+(.1268*(
          Wpk[5][18][0]*Wpk[5][18][0])))))+temp[3])));
        mm[5][5] = (.0548+(((.205126*((Vpk[5][22][2]*Vpk[5][22][2])+((
          Vpk[5][22][0]*Vpk[5][22][0])+(Vpk[5][22][1]*Vpk[5][22][1]))))+((
          .000119*(Wpk[5][22][2]*Wpk[5][22][2]))+((.000117*(Wpk[5][22][0]*
          Wpk[5][22][0]))+(.000179*(Wpk[5][22][1]*Wpk[5][22][1])))))+temp[6]));
        mm[5][6] = ((10.3786426*((Vpk[5][8][2]*Wpk[6][8][0])-(Vpk[5][8][0]*
          Wpk[6][8][2])))+((1.3552*(Wpk[5][8][2]*Wpk[6][8][2]))+((.7153*(s7*s7))
          +(1.396*(Wpk[5][8][0]*Wpk[6][8][0])))));
        mm[5][7] = ((10.3786426*((Vpk[5][8][2]*c8)-(Vpk[5][8][0]*s8)))+((1.3552*
          (Wpk[5][8][2]*s8))+(1.396*(Wpk[5][8][0]*c8))));
        mm[5][8] = (.7153*s7);
        temp[0] = ((3.51*((Vpk[5][12][2]*Vpk[9][12][2])+((Vpk[5][12][0]*
          Vpk[9][12][0])+(Vpk[5][12][1]*Vpk[9][12][1]))))+((.0484*(Wpk[5][12][2]
          *Wpk[9][12][2]))+((.0048*(Wpk[5][12][1]*Wpk[9][12][1]))+(.0477*(
          Wpk[5][12][0]*Wpk[9][12][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[5][11][2]*Vpk[9][11][2])+((.1715*(
          Vpk[5][11][0]*Wpk[9][11][2]))-(.002*(Vpk[5][11][1]*Wpk[9][11][2])))))+
          ((.1337*(Wpk[5][11][2]*Wpk[9][11][2]))+((.0332*(s10*s10))+(.1268*(
          Wpk[5][11][0]*Wpk[9][11][0]))))));
        temp[2] = (((1.2*((Vpk[5][14][2]*Vpk[9][14][2])+((Vpk[5][14][0]*
          Vpk[9][14][0])+(Vpk[5][14][1]*Vpk[9][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[9][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[9][14][0]))
          +(.003709*(Wpk[5][14][1]*Wpk[9][14][1])))))+temp[1]);
        mm[5][9] = (((.205126*((Vpk[5][15][2]*Vpk[9][15][2])+((Vpk[5][15][0]*
          Vpk[9][15][0])+(Vpk[5][15][1]*Vpk[9][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[9][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[9][15][0]))
          +(.000179*(Wpk[5][15][1]*Wpk[9][15][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[5][12][2]*Vpk[10][12][2])+((Vpk[5][12][0]*
          Vpk[10][12][0])+(Vpk[5][12][1]*Vpk[10][12][1]))))+((.0484*(
          Wpk[5][12][2]*Wpk[10][12][2]))+((.0048*(Wpk[5][12][1]*Wpk[10][12][1]))
          +(.0477*(Wpk[5][12][0]*Wpk[10][12][0])))))+((8.806*(((.1715*(
          Vpk[5][11][0]*s11))-(.002*(Vpk[5][11][1]*s11)))-(.1715*(Vpk[5][11][2]*
          c11))))+((.1268*(Wpk[5][11][0]*c11))+(.1337*(Wpk[5][11][2]*s11)))));
        temp[1] = (((1.2*((Vpk[5][14][2]*Vpk[10][14][2])+((Vpk[5][14][0]*
          Vpk[10][14][0])+(Vpk[5][14][1]*Vpk[10][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[10][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[10][14][0]
          ))+(.003709*(Wpk[5][14][1]*Wpk[10][14][1])))))+temp[0]);
        mm[5][10] = (((.205126*((Vpk[5][15][2]*Vpk[10][15][2])+((Vpk[5][15][0]*
          Vpk[10][15][0])+(Vpk[5][15][1]*Vpk[10][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[10][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[10][15][0]
          ))+(.000179*(Wpk[5][15][1]*Wpk[10][15][1])))))+temp[1]);
        temp[0] = (((.017612*Vpk[5][11][2])+(.0332*s10))+((3.51*((Vpk[5][12][2]*
          Vpk[11][12][2])+((Vpk[5][12][0]*Vpk[11][12][0])-(.0013*(Cik[12][2][1]*
          Vpk[5][12][1])))))+((.0484*(Cik[12][1][2]*Wpk[5][12][2]))+((.0048*(
          Cik[12][1][1]*Wpk[5][12][1]))+(.0477*(Cik[12][1][0]*Wpk[5][12][0])))))
          );
        temp[1] = (((1.2*((Vpk[5][14][2]*Vpk[11][14][2])+((Vpk[5][14][0]*
          Vpk[11][14][0])+(Vpk[5][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[11][14][0]
          ))+(.003709*(Wpk[5][14][1]*Wpk[11][14][1])))))+temp[0]);
        mm[5][11] = (((.205126*((Vpk[5][15][2]*Vpk[11][15][2])+((Vpk[5][15][0]*
          Vpk[11][15][0])+(Vpk[5][15][1]*Vpk[11][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[11][15][0]
          ))+(.000179*(Wpk[5][15][1]*Wpk[11][15][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[5][14][2]*Vpk[12][14][2])+((Vpk[5][14][0]*
          Vpk[12][14][0])+(Vpk[5][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[12][14][0]
          ))+(.003709*(Wpk[5][14][1]*Wpk[12][14][1])))))+((3.51*((
          .0150652581855386*Vpk[5][12][2])+(.185436609363333*Vpk[5][12][0])))+((
          .0482015676325742*Wpk[5][12][2])+((.000194184030748461*Wpk[5][12][1])-
          (.00385935991111811*Wpk[5][12][0])))));
        mm[5][12] = (((.205126*((Vpk[5][15][2]*Vpk[12][15][2])+((Vpk[5][15][0]*
          Vpk[12][15][0])+(Vpk[5][15][1]*Vpk[12][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[12][15][0]
          ))+(.000179*(Wpk[5][15][1]*Wpk[12][15][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][14][2]*Vpk[13][14][2])+((Vpk[5][14][0]*
          Vpk[13][14][0])+(Vpk[5][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[5][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[5][14][0]*Wpk[13][14][0]
          ))+(.003709*(Wpk[5][14][1]*Wpk[13][14][1])))));
        mm[5][13] = (((.205126*((Vpk[5][15][2]*Vpk[13][15][2])+((Vpk[5][15][0]*
          Vpk[13][15][0])+(Vpk[5][15][1]*Vpk[13][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[13][15][0]
          ))+(.000179*(Wpk[5][15][1]*Wpk[13][15][1])))))+temp[0]);
        mm[5][14] = (((.205126*((Vpk[5][15][2]*Vpk[14][15][2])+((Vpk[5][15][0]*
          Vpk[14][15][0])+(Vpk[5][15][1]*Vpk[14][15][1]))))+((.000119*(
          Wpk[5][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[5][15][0]*Wpk[14][15][0]
          ))+(.000179*(Wpk[5][15][1]*Wpk[14][15][1])))))+((1.2*(((
          .000411457536296252*Vpk[5][14][0])-(.00646090297985859*Vpk[5][14][1]))
          -(.0625600530375351*Vpk[5][14][2])))+(((.00110888270658752*
          Wpk[5][14][0])+(.00214105693566144*Wpk[5][14][1]))-(
          .000212474287874234*Wpk[5][14][2]))));
        mm[5][15] = ((.205126*(((.02617891313962*Vpk[5][15][1])-(
          .0163345287751755*Vpk[5][15][0]))-(.00868522709507149*Vpk[5][15][2])))
          +((.00010507075266194*Wpk[5][15][2])-(5.49281929796413e-5*
          Wpk[5][15][0])));
        temp[0] = ((3.51*((Vpk[5][19][2]*Vpk[16][19][2])+((Vpk[5][19][0]*
          Vpk[16][19][0])+(Vpk[5][19][1]*Vpk[16][19][1]))))+((.0484*(
          Wpk[5][19][2]*Wpk[16][19][2]))+((.0048*(Wpk[5][19][1]*Wpk[16][19][1]))
          +(.0477*(Wpk[5][19][0]*Wpk[16][19][0])))));
        temp[1] = (temp[0]+((8.806*((Vpk[5][18][2]*Vpk[16][18][2])+((.1715*(
          Vpk[5][18][0]*Wpk[16][18][2]))-(.002*(Vpk[5][18][1]*Wpk[16][18][2]))))
          )+((.1337*(Wpk[5][18][2]*Wpk[16][18][2]))+((.0332*(s17*s17))+(.1268*(
          Wpk[5][18][0]*Wpk[16][18][0]))))));
        temp[2] = (((1.2*((Vpk[5][21][2]*Vpk[16][21][2])+((Vpk[5][21][0]*
          Vpk[16][21][0])+(Vpk[5][21][1]*Vpk[16][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[16][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[16][21][0]
          ))+(.003709*(Wpk[5][21][1]*Wpk[16][21][1])))))+temp[1]);
        mm[5][16] = (((.205126*((Vpk[5][22][2]*Vpk[16][22][2])+((Vpk[5][22][0]*
          Vpk[16][22][0])+(Vpk[5][22][1]*Vpk[16][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[16][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[16][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[16][22][1])))))+temp[2]);
        temp[0] = (((3.51*((Vpk[5][19][2]*Vpk[17][19][2])+((Vpk[5][19][0]*
          Vpk[17][19][0])+(Vpk[5][19][1]*Vpk[17][19][1]))))+((.0484*(
          Wpk[5][19][2]*Wpk[17][19][2]))+((.0048*(Wpk[5][19][1]*Wpk[17][19][1]))
          +(.0477*(Wpk[5][19][0]*Wpk[17][19][0])))))+((8.806*((.1715*(
          Vpk[5][18][2]*c18))+((.1715*(Vpk[5][18][0]*s18))-(.002*(Vpk[5][18][1]*
          s18)))))+((.1337*(Wpk[5][18][2]*s18))-(.1268*(Wpk[5][18][0]*c18)))));
        temp[1] = (((1.2*((Vpk[5][21][2]*Vpk[17][21][2])+((Vpk[5][21][0]*
          Vpk[17][21][0])+(Vpk[5][21][1]*Vpk[17][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[17][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[17][21][0]
          ))+(.003709*(Wpk[5][21][1]*Wpk[17][21][1])))))+temp[0]);
        mm[5][17] = (((.205126*((Vpk[5][22][2]*Vpk[17][22][2])+((Vpk[5][22][0]*
          Vpk[17][22][0])+(Vpk[5][22][1]*Vpk[17][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[17][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[17][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[17][22][1])))))+temp[1]);
        temp[0] = (((.0332*s17)-(.017612*Vpk[5][18][2]))+((3.51*((Vpk[5][19][2]*
          Vpk[18][19][2])+((.0013*(Cik[19][2][1]*Vpk[5][19][1]))+(Vpk[5][19][0]*
          Vpk[18][19][0]))))-((.0484*(Cik[19][1][2]*Wpk[5][19][2]))+((.0048*(
          Cik[19][1][1]*Wpk[5][19][1]))+(.0477*(Cik[19][1][0]*Wpk[5][19][0])))))
          );
        temp[1] = (((1.2*((Vpk[5][21][2]*Vpk[18][21][2])+((Vpk[5][21][0]*
          Vpk[18][21][0])+(Vpk[5][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[18][21][0]
          ))+(.003709*(Wpk[5][21][1]*Wpk[18][21][1])))))+temp[0]);
        mm[5][18] = (((.205126*((Vpk[5][22][2]*Vpk[18][22][2])+((Vpk[5][22][0]*
          Vpk[18][22][0])+(Vpk[5][22][1]*Vpk[18][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[18][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[18][22][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[5][21][2]*Vpk[19][21][2])+((Vpk[5][21][0]*
          Vpk[19][21][0])+(Vpk[5][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[19][21][0]
          ))+(.003709*(Wpk[5][21][1]*Wpk[19][21][1])))))+((3.51*((
          .185436609363333*Vpk[5][19][0])-(.0150652581855386*Vpk[5][19][2])))+((
          .0482015676325742*Wpk[5][19][2])+((.00385935991111811*Wpk[5][19][0])-(
          .000194184030748461*Wpk[5][19][1])))));
        mm[5][19] = (((.205126*((Vpk[5][22][2]*Vpk[19][22][2])+((Vpk[5][22][0]*
          Vpk[19][22][0])+(Vpk[5][22][1]*Vpk[19][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[19][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[19][22][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[5][21][2]*Vpk[20][21][2])+((Vpk[5][21][0]*
          Vpk[20][21][0])+(Vpk[5][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[5][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[5][21][0]*Wpk[20][21][0]
          ))+(.003709*(Wpk[5][21][1]*Wpk[20][21][1])))));
        mm[5][20] = (((.205126*((Vpk[5][22][2]*Vpk[20][22][2])+((Vpk[5][22][0]*
          Vpk[20][22][0])+(Vpk[5][22][1]*Vpk[20][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[20][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[20][22][1])))))+temp[0]);
        mm[5][21] = (((.205126*((Vpk[5][22][2]*Vpk[21][22][2])+((Vpk[5][22][0]*
          Vpk[21][22][0])+(Vpk[5][22][1]*Vpk[21][22][1]))))+((.000119*(
          Wpk[5][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[5][22][0]*Wpk[21][22][0]
          ))+(.000179*(Wpk[5][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[5][21][2])+((.000411457536296252*Vpk[5][21][0])-
          (.00646090297985859*Vpk[5][21][1]))))-((.000212474287874234*
          Wpk[5][21][2])+((.00110888270658752*Wpk[5][21][0])+(.00214105693566144
          *Wpk[5][21][1])))));
        mm[5][22] = ((.205126*((.00868522709507149*Vpk[5][22][2])+((
          .02617891313962*Vpk[5][22][1])-(.0163345287751755*Vpk[5][22][0]))))+((
          5.49281929796413e-5*Wpk[5][22][0])+(.00010507075266194*Wpk[5][22][2]))
          );
        mm[6][6] = ((3.32324136052*((Wpk[6][8][0]*Wpk[6][8][0])+(Wpk[6][8][2]*
          Wpk[6][8][2])))+((1.3552*(Wpk[6][8][2]*Wpk[6][8][2]))+((.7153*(s7*s7))
          +(1.396*(Wpk[6][8][0]*Wpk[6][8][0])))));
        mm[6][7] = ((3.32324136052*((Wpk[6][8][0]*c8)+(Wpk[6][8][2]*s8)))+((
          1.3552*(Wpk[6][8][2]*s8))+(1.396*(Wpk[6][8][0]*c8))));
        mm[6][8] = (.7153*s7);
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
        mm[7][7] = (4.67844136052+(.0407999999999999*(c8*c8)));
        mm[7][8] = 0.;
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
        mm[8][8] = .7153;
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
        temp[0] = (((3.51*((Vpk[9][12][2]*Vpk[9][12][2])+((Vpk[9][12][0]*
          Vpk[9][12][0])+(Vpk[9][12][1]*Vpk[9][12][1]))))+((.0484*(Wpk[9][12][2]
          *Wpk[9][12][2]))+((.0048*(Wpk[9][12][1]*Wpk[9][12][1]))+(.0477*(
          Wpk[9][12][0]*Wpk[9][12][0])))))+((8.806*((.02941625*(Wpk[9][11][2]*
          Wpk[9][11][2]))+(Vpk[9][11][2]*Vpk[9][11][2])))+((.1337*(Wpk[9][11][2]
          *Wpk[9][11][2]))+((.0332*(s10*s10))+(.1268*(Wpk[9][11][0]*
          Wpk[9][11][0]))))));
        temp[1] = (((1.2*((Vpk[9][14][2]*Vpk[9][14][2])+((Vpk[9][14][0]*
          Vpk[9][14][0])+(Vpk[9][14][1]*Vpk[9][14][1]))))+((.003916*(
          Wpk[9][14][2]*Wpk[9][14][2]))+((.001361*(Wpk[9][14][0]*Wpk[9][14][0]))
          +(.003709*(Wpk[9][14][1]*Wpk[9][14][1])))))+temp[0]);
        mm[9][9] = (((.205126*((Vpk[9][15][2]*Vpk[9][15][2])+((Vpk[9][15][0]*
          Vpk[9][15][0])+(Vpk[9][15][1]*Vpk[9][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[9][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[9][15][0]))
          +(.000179*(Wpk[9][15][1]*Wpk[9][15][1])))))+temp[1]);
        temp[0] = (((3.51*((Vpk[9][12][2]*Vpk[10][12][2])+((Vpk[9][12][0]*
          Vpk[10][12][0])+(Vpk[9][12][1]*Vpk[10][12][1]))))+((.0484*(
          Wpk[9][12][2]*Wpk[10][12][2]))+((.0048*(Wpk[9][12][1]*Wpk[10][12][1]))
          +(.0477*(Wpk[9][12][0]*Wpk[10][12][0])))))+((8.806*((.02941625*(
          Wpk[9][11][2]*s11))-(.1715*(Vpk[9][11][2]*c11))))+((.1268*(
          Wpk[9][11][0]*c11))+(.1337*(Wpk[9][11][2]*s11)))));
        temp[1] = (((1.2*((Vpk[9][14][2]*Vpk[10][14][2])+((Vpk[9][14][0]*
          Vpk[10][14][0])+(Vpk[9][14][1]*Vpk[10][14][1]))))+((.003916*(
          Wpk[9][14][2]*Wpk[10][14][2]))+((.001361*(Wpk[9][14][0]*Wpk[10][14][0]
          ))+(.003709*(Wpk[9][14][1]*Wpk[10][14][1])))))+temp[0]);
        mm[9][10] = (((.205126*((Vpk[9][15][2]*Vpk[10][15][2])+((Vpk[9][15][0]*
          Vpk[10][15][0])+(Vpk[9][15][1]*Vpk[10][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[10][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[10][15][0]
          ))+(.000179*(Wpk[9][15][1]*Wpk[10][15][1])))))+temp[1]);
        temp[0] = (((.017612*Vpk[9][11][2])+(.0332*s10))+((3.51*((Vpk[9][12][2]*
          Vpk[11][12][2])+((Vpk[9][12][0]*Vpk[11][12][0])-(.0013*(Cik[12][2][1]*
          Vpk[9][12][1])))))+((.0484*(Cik[12][1][2]*Wpk[9][12][2]))+((.0048*(
          Cik[12][1][1]*Wpk[9][12][1]))+(.0477*(Cik[12][1][0]*Wpk[9][12][0])))))
          );
        temp[1] = (((1.2*((Vpk[9][14][2]*Vpk[11][14][2])+((Vpk[9][14][0]*
          Vpk[11][14][0])+(Vpk[9][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[9][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[9][14][0]*Wpk[11][14][0]
          ))+(.003709*(Wpk[9][14][1]*Wpk[11][14][1])))))+temp[0]);
        mm[9][11] = (((.205126*((Vpk[9][15][2]*Vpk[11][15][2])+((Vpk[9][15][0]*
          Vpk[11][15][0])+(Vpk[9][15][1]*Vpk[11][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[11][15][0]
          ))+(.000179*(Wpk[9][15][1]*Wpk[11][15][1])))))+temp[1]);
        temp[0] = (((1.2*((Vpk[9][14][2]*Vpk[12][14][2])+((Vpk[9][14][0]*
          Vpk[12][14][0])+(Vpk[9][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[9][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[9][14][0]*Wpk[12][14][0]
          ))+(.003709*(Wpk[9][14][1]*Wpk[12][14][1])))))+((3.51*((
          .0150652581855386*Vpk[9][12][2])+(.185436609363333*Vpk[9][12][0])))+((
          .0482015676325742*Wpk[9][12][2])+((.000194184030748461*Wpk[9][12][1])-
          (.00385935991111811*Wpk[9][12][0])))));
        mm[9][12] = (((.205126*((Vpk[9][15][2]*Vpk[12][15][2])+((Vpk[9][15][0]*
          Vpk[12][15][0])+(Vpk[9][15][1]*Vpk[12][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[12][15][0]
          ))+(.000179*(Wpk[9][15][1]*Wpk[12][15][1])))))+temp[0]);
        temp[0] = ((1.2*((Vpk[9][14][2]*Vpk[13][14][2])+((Vpk[9][14][0]*
          Vpk[13][14][0])+(Vpk[9][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[9][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[9][14][0]*Wpk[13][14][0]
          ))+(.003709*(Wpk[9][14][1]*Wpk[13][14][1])))));
        mm[9][13] = (((.205126*((Vpk[9][15][2]*Vpk[13][15][2])+((Vpk[9][15][0]*
          Vpk[13][15][0])+(Vpk[9][15][1]*Vpk[13][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[13][15][0]
          ))+(.000179*(Wpk[9][15][1]*Wpk[13][15][1])))))+temp[0]);
        mm[9][14] = (((.205126*((Vpk[9][15][2]*Vpk[14][15][2])+((Vpk[9][15][0]*
          Vpk[14][15][0])+(Vpk[9][15][1]*Vpk[14][15][1]))))+((.000119*(
          Wpk[9][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[9][15][0]*Wpk[14][15][0]
          ))+(.000179*(Wpk[9][15][1]*Wpk[14][15][1])))))+((1.2*(((
          .000411457536296252*Vpk[9][14][0])-(.00646090297985859*Vpk[9][14][1]))
          -(.0625600530375351*Vpk[9][14][2])))+(((.00110888270658752*
          Wpk[9][14][0])+(.00214105693566144*Wpk[9][14][1]))-(
          .000212474287874234*Wpk[9][14][2]))));
        mm[9][15] = ((.205126*(((.02617891313962*Vpk[9][15][1])-(
          .0163345287751755*Vpk[9][15][0]))-(.00868522709507149*Vpk[9][15][2])))
          +((.00010507075266194*Wpk[9][15][2])-(5.49281929796413e-5*
          Wpk[9][15][0])));
        mm[9][16] = 0.;
        mm[9][17] = 0.;
        mm[9][18] = 0.;
        mm[9][19] = 0.;
        mm[9][20] = 0.;
        mm[9][21] = 0.;
        mm[9][22] = 0.;
        temp[0] = (((.00690000000000002*(s11*s11))+(8.806*(.02941225+(
          4.00000000000053e-6*(s11*s11)))))+((3.51*((Vpk[10][12][2]*
          Vpk[10][12][2])+((Vpk[10][12][0]*Vpk[10][12][0])+(Vpk[10][12][1]*
          Vpk[10][12][1]))))+((.0484*(Wpk[10][12][2]*Wpk[10][12][2]))+((.0048*(
          Wpk[10][12][1]*Wpk[10][12][1]))+(.0477*(Wpk[10][12][0]*Wpk[10][12][0])
          )))));
        temp[1] = (((1.2*((Vpk[10][14][2]*Vpk[10][14][2])+((Vpk[10][14][0]*
          Vpk[10][14][0])+(Vpk[10][14][1]*Vpk[10][14][1]))))+((.003916*(
          Wpk[10][14][2]*Wpk[10][14][2]))+((.001361*(Wpk[10][14][0]*
          Wpk[10][14][0]))+(.003709*(Wpk[10][14][1]*Wpk[10][14][1])))))+temp[0])
          ;
        mm[10][10] = (.1268+(((.205126*((Vpk[10][15][2]*Vpk[10][15][2])+((
          Vpk[10][15][0]*Vpk[10][15][0])+(Vpk[10][15][1]*Vpk[10][15][1]))))+((
          .000119*(Wpk[10][15][2]*Wpk[10][15][2]))+((.000117*(Wpk[10][15][0]*
          Wpk[10][15][0]))+(.000179*(Wpk[10][15][1]*Wpk[10][15][1])))))+temp[1])
          );
        temp[0] = (((3.51*((Vpk[10][12][2]*Vpk[11][12][2])+((Vpk[10][12][0]*
          Vpk[11][12][0])-(.0013*(Cik[12][2][1]*Vpk[10][12][1])))))+((.0484*(
          Cik[12][1][2]*Wpk[10][12][2]))+((.0048*(Cik[12][1][1]*Wpk[10][12][1]))
          +(.0477*(Cik[12][1][0]*Wpk[10][12][0])))))-(.003020458*c11));
        temp[1] = (((1.2*((Vpk[10][14][2]*Vpk[11][14][2])+((Vpk[10][14][0]*
          Vpk[11][14][0])+(Vpk[10][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[10][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[10][14][0]*
          Wpk[11][14][0]))+(.003709*(Wpk[10][14][1]*Wpk[11][14][1])))))+temp[0])
          ;
        mm[10][11] = (((.205126*((Vpk[10][15][2]*Vpk[11][15][2])+((
          Vpk[10][15][0]*Vpk[11][15][0])+(Vpk[10][15][1]*Vpk[11][15][1]))))+((
          .000119*(Wpk[10][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[10][15][0]*
          Wpk[11][15][0]))+(.000179*(Wpk[10][15][1]*Wpk[11][15][1])))))+temp[1])
          ;
        temp[0] = (((1.2*((Vpk[10][14][2]*Vpk[12][14][2])+((Vpk[10][14][0]*
          Vpk[12][14][0])+(Vpk[10][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[10][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[10][14][0]*
          Wpk[12][14][0]))+(.003709*(Wpk[10][14][1]*Wpk[12][14][1])))))+((3.51*(
          (.0150652581855386*Vpk[10][12][2])+(.185436609363333*Vpk[10][12][0])))
          +((.0482015676325742*Wpk[10][12][2])+((.000194184030748461*
          Wpk[10][12][1])-(.00385935991111811*Wpk[10][12][0])))));
        mm[10][12] = (((.205126*((Vpk[10][15][2]*Vpk[12][15][2])+((
          Vpk[10][15][0]*Vpk[12][15][0])+(Vpk[10][15][1]*Vpk[12][15][1]))))+((
          .000119*(Wpk[10][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[10][15][0]*
          Wpk[12][15][0]))+(.000179*(Wpk[10][15][1]*Wpk[12][15][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[10][14][2]*Vpk[13][14][2])+((Vpk[10][14][0]*
          Vpk[13][14][0])+(Vpk[10][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[10][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[10][14][0]*
          Wpk[13][14][0]))+(.003709*(Wpk[10][14][1]*Wpk[13][14][1])))));
        mm[10][13] = (((.205126*((Vpk[10][15][2]*Vpk[13][15][2])+((
          Vpk[10][15][0]*Vpk[13][15][0])+(Vpk[10][15][1]*Vpk[13][15][1]))))+((
          .000119*(Wpk[10][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[10][15][0]*
          Wpk[13][15][0]))+(.000179*(Wpk[10][15][1]*Wpk[13][15][1])))))+temp[0])
          ;
        mm[10][14] = (((.205126*((Vpk[10][15][2]*Vpk[14][15][2])+((
          Vpk[10][15][0]*Vpk[14][15][0])+(Vpk[10][15][1]*Vpk[14][15][1]))))+((
          .000119*(Wpk[10][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[10][15][0]*
          Wpk[14][15][0]))+(.000179*(Wpk[10][15][1]*Wpk[14][15][1])))))+((1.2*((
          (.000411457536296252*Vpk[10][14][0])-(.00646090297985859*
          Vpk[10][14][1]))-(.0625600530375351*Vpk[10][14][2])))+(((
          .00110888270658752*Wpk[10][14][0])+(.00214105693566144*Wpk[10][14][1])
          )-(.000212474287874234*Wpk[10][14][2]))));
        mm[10][15] = ((.205126*(((.02617891313962*Vpk[10][15][1])-(
          .0163345287751755*Vpk[10][15][0]))-(.00868522709507149*Vpk[10][15][2])
          ))+((.00010507075266194*Wpk[10][15][2])-(5.49281929796413e-5*
          Wpk[10][15][0])));
        mm[10][16] = 0.;
        mm[10][17] = 0.;
        mm[10][18] = 0.;
        mm[10][19] = 0.;
        mm[10][20] = 0.;
        mm[10][21] = 0.;
        mm[10][22] = 0.;
        temp[0] = ((3.51*((Vpk[11][12][2]*Vpk[11][12][2])+((1.69e-6*(
          Cik[12][2][1]*Cik[12][2][1]))+(Vpk[11][12][0]*Vpk[11][12][0]))))+((
          .0484*(Cik[12][1][2]*Cik[12][1][2]))+((.0048*(Cik[12][1][1]*
          Cik[12][1][1]))+(.0477*(Cik[12][1][0]*Cik[12][1][0])))));
        temp[1] = (((1.2*((Vpk[11][14][2]*Vpk[11][14][2])+((Vpk[11][14][0]*
          Vpk[11][14][0])+(Vpk[11][14][1]*Vpk[11][14][1]))))+((.003916*(
          Wpk[11][14][2]*Wpk[11][14][2]))+((.001361*(Wpk[11][14][0]*
          Wpk[11][14][0]))+(.003709*(Wpk[11][14][1]*Wpk[11][14][1])))))+temp[0])
          ;
        mm[11][11] = (.033235224+(((.205126*((Vpk[11][15][2]*Vpk[11][15][2])+((
          Vpk[11][15][0]*Vpk[11][15][0])+(Vpk[11][15][1]*Vpk[11][15][1]))))+((
          .000119*(Wpk[11][15][2]*Wpk[11][15][2]))+((.000117*(Wpk[11][15][0]*
          Wpk[11][15][0]))+(.000179*(Wpk[11][15][1]*Wpk[11][15][1])))))+temp[1])
          );
        temp[0] = (((1.2*((Vpk[11][14][2]*Vpk[12][14][2])+((Vpk[11][14][0]*
          Vpk[12][14][0])+(Vpk[11][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[11][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[11][14][0]*
          Wpk[12][14][0]))+(.003709*(Wpk[11][14][1]*Wpk[12][14][1])))))+((3.51*(
          (.0150652581855386*Vpk[11][12][2])+(.185436609363333*Vpk[11][12][0])))
          +((.0482015676325742*Cik[12][1][2])+((.000194184030748461*
          Cik[12][1][1])-(.00385935991111811*Cik[12][1][0])))));
        mm[11][12] = (((.205126*((Vpk[11][15][2]*Vpk[12][15][2])+((
          Vpk[11][15][0]*Vpk[12][15][0])+(Vpk[11][15][1]*Vpk[12][15][1]))))+((
          .000119*(Wpk[11][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[11][15][0]*
          Wpk[12][15][0]))+(.000179*(Wpk[11][15][1]*Wpk[12][15][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[11][14][2]*Vpk[13][14][2])+((Vpk[11][14][0]*
          Vpk[13][14][0])+(Vpk[11][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[11][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[11][14][0]*
          Wpk[13][14][0]))+(.003709*(Wpk[11][14][1]*Wpk[13][14][1])))));
        mm[11][13] = (((.205126*((Vpk[11][15][2]*Vpk[13][15][2])+((
          Vpk[11][15][0]*Vpk[13][15][0])+(Vpk[11][15][1]*Vpk[13][15][1]))))+((
          .000119*(Wpk[11][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[11][15][0]*
          Wpk[13][15][0]))+(.000179*(Wpk[11][15][1]*Wpk[13][15][1])))))+temp[0])
          ;
        mm[11][14] = (((.205126*((Vpk[11][15][2]*Vpk[14][15][2])+((
          Vpk[11][15][0]*Vpk[14][15][0])+(Vpk[11][15][1]*Vpk[14][15][1]))))+((
          .000119*(Wpk[11][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[11][15][0]*
          Wpk[14][15][0]))+(.000179*(Wpk[11][15][1]*Wpk[14][15][1])))))+((1.2*((
          (.000411457536296252*Vpk[11][14][0])-(.00646090297985859*
          Vpk[11][14][1]))-(.0625600530375351*Vpk[11][14][2])))+(((
          .00110888270658752*Wpk[11][14][0])+(.00214105693566144*Wpk[11][14][1])
          )-(.000212474287874234*Wpk[11][14][2]))));
        mm[11][15] = ((.205126*(((.02617891313962*Vpk[11][15][1])-(
          .0163345287751755*Vpk[11][15][0]))-(.00868522709507149*Vpk[11][15][2])
          ))+((.00010507075266194*Wpk[11][15][2])-(5.49281929796413e-5*
          Wpk[11][15][0])));
        mm[11][16] = 0.;
        mm[11][17] = 0.;
        mm[11][18] = 0.;
        mm[11][19] = 0.;
        mm[11][20] = 0.;
        mm[11][21] = 0.;
        mm[11][22] = 0.;
        temp[0] = ((1.2*((Vpk[12][14][2]*Vpk[12][14][2])+((Vpk[12][14][0]*
          Vpk[12][14][0])+(Vpk[12][14][1]*Vpk[12][14][1]))))+((.003916*(
          Wpk[12][14][2]*Wpk[12][14][2]))+((.001361*(Wpk[12][14][0]*
          Wpk[12][14][0]))+(.003709*(Wpk[12][14][1]*Wpk[12][14][1])))));
        mm[12][12] = (.16981814184151+(((.205126*((Vpk[12][15][2]*Vpk[12][15][2]
          )+((Vpk[12][15][0]*Vpk[12][15][0])+(Vpk[12][15][1]*Vpk[12][15][1]))))+
          ((.000119*(Wpk[12][15][2]*Wpk[12][15][2]))+((.000117*(Wpk[12][15][0]*
          Wpk[12][15][0]))+(.000179*(Wpk[12][15][1]*Wpk[12][15][1])))))+temp[0])
          );
        temp[0] = ((1.2*((Vpk[12][14][2]*Vpk[13][14][2])+((Vpk[12][14][0]*
          Vpk[13][14][0])+(Vpk[12][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[12][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[12][14][0]*
          Wpk[13][14][0]))+(.003709*(Wpk[12][14][1]*Wpk[13][14][1])))));
        mm[12][13] = (((.205126*((Vpk[12][15][2]*Vpk[13][15][2])+((
          Vpk[12][15][0]*Vpk[13][15][0])+(Vpk[12][15][1]*Vpk[13][15][1]))))+((
          .000119*(Wpk[12][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[12][15][0]*
          Wpk[13][15][0]))+(.000179*(Wpk[12][15][1]*Wpk[13][15][1])))))+temp[0])
          ;
        mm[12][14] = (((.205126*((Vpk[12][15][2]*Vpk[14][15][2])+((
          Vpk[12][15][0]*Vpk[14][15][0])+(Vpk[12][15][1]*Vpk[14][15][1]))))+((
          .000119*(Wpk[12][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[12][15][0]*
          Wpk[14][15][0]))+(.000179*(Wpk[12][15][1]*Wpk[14][15][1])))))+((1.2*((
          (.000411457536296252*Vpk[12][14][0])-(.00646090297985859*
          Vpk[12][14][1]))-(.0625600530375351*Vpk[12][14][2])))+(((
          .00110888270658752*Wpk[12][14][0])+(.00214105693566144*Wpk[12][14][1])
          )-(.000212474287874234*Wpk[12][14][2]))));
        mm[12][15] = ((.205126*(((.02617891313962*Vpk[12][15][1])-(
          .0163345287751755*Vpk[12][15][0]))-(.00868522709507149*Vpk[12][15][2])
          ))+((.00010507075266194*Wpk[12][15][2])-(5.49281929796413e-5*
          Wpk[12][15][0])));
        mm[12][16] = 0.;
        mm[12][17] = 0.;
        mm[12][18] = 0.;
        mm[12][19] = 0.;
        mm[12][20] = 0.;
        mm[12][21] = 0.;
        mm[12][22] = 0.;
        temp[0] = ((1.2*((Vpk[13][14][2]*Vpk[13][14][2])+((Vpk[13][14][0]*
          Vpk[13][14][0])+(Vpk[13][14][1]*Vpk[13][14][1]))))+((.003916*(
          Wpk[13][14][2]*Wpk[13][14][2]))+((.001361*(Wpk[13][14][0]*
          Wpk[13][14][0]))+(.003709*(Wpk[13][14][1]*Wpk[13][14][1])))));
        mm[13][13] = (((.205126*((Vpk[13][15][2]*Vpk[13][15][2])+((
          Vpk[13][15][0]*Vpk[13][15][0])+(Vpk[13][15][1]*Vpk[13][15][1]))))+((
          .000119*(Wpk[13][15][2]*Wpk[13][15][2]))+((.000117*(Wpk[13][15][0]*
          Wpk[13][15][0]))+(.000179*(Wpk[13][15][1]*Wpk[13][15][1])))))+temp[0])
          ;
        mm[13][14] = (((.205126*((Vpk[13][15][2]*Vpk[14][15][2])+((
          Vpk[13][15][0]*Vpk[14][15][0])+(Vpk[13][15][1]*Vpk[14][15][1]))))+((
          .000119*(Wpk[13][15][2]*Wpk[14][15][2]))+((.000117*(Wpk[13][15][0]*
          Wpk[14][15][0]))+(.000179*(Wpk[13][15][1]*Wpk[14][15][1])))))+((1.2*((
          (.000411457536296252*Vpk[13][14][0])-(.00646090297985859*
          Vpk[13][14][1]))-(.0625600530375351*Vpk[13][14][2])))+(((
          .00110888270658752*Wpk[13][14][0])+(.00214105693566144*Wpk[13][14][1])
          )-(.000212474287874234*Wpk[13][14][2]))));
        mm[13][15] = ((.205126*(((.02617891313962*Vpk[13][15][1])-(
          .0163345287751755*Vpk[13][15][0]))-(.00868522709507149*Vpk[13][15][2])
          ))+((.00010507075266194*Wpk[13][15][2])-(5.49281929796413e-5*
          Wpk[13][15][0])));
        mm[13][16] = 0.;
        mm[13][17] = 0.;
        mm[13][18] = 0.;
        mm[13][19] = 0.;
        mm[13][20] = 0.;
        mm[13][21] = 0.;
        mm[13][22] = 0.;
        mm[14][14] = (.00689775074968843+((.205126*((Vpk[14][15][2]*
          Vpk[14][15][2])+((Vpk[14][15][0]*Vpk[14][15][0])+(Vpk[14][15][1]*
          Vpk[14][15][1]))))+((.000119*(Wpk[14][15][2]*Wpk[14][15][2]))+((
          .000117*(Wpk[14][15][0]*Wpk[14][15][0]))+(.000179*(Wpk[14][15][1]*
          Wpk[14][15][1]))))));
        mm[14][15] = ((.205126*(((.02617891313962*Vpk[14][15][1])-(
          .0163345287751755*Vpk[14][15][0]))-(.00868522709507149*Vpk[14][15][2])
          ))+((.00010507075266194*Wpk[14][15][2])-(5.49281929796413e-5*
          Wpk[14][15][0])));
        mm[14][16] = 0.;
        mm[14][17] = 0.;
        mm[14][18] = 0.;
        mm[14][19] = 0.;
        mm[14][20] = 0.;
        mm[14][21] = 0.;
        mm[14][22] = 0.;
        mm[15][15] = .000329343694452671;
        mm[15][16] = 0.;
        mm[15][17] = 0.;
        mm[15][18] = 0.;
        mm[15][19] = 0.;
        mm[15][20] = 0.;
        mm[15][21] = 0.;
        mm[15][22] = 0.;
        temp[0] = (((3.51*((Vpk[16][19][2]*Vpk[16][19][2])+((Vpk[16][19][0]*
          Vpk[16][19][0])+(Vpk[16][19][1]*Vpk[16][19][1]))))+((.0484*(
          Wpk[16][19][2]*Wpk[16][19][2]))+((.0048*(Wpk[16][19][1]*Wpk[16][19][1]
          ))+(.0477*(Wpk[16][19][0]*Wpk[16][19][0])))))+((8.806*((.02941625*(
          Wpk[16][18][2]*Wpk[16][18][2]))+(Vpk[16][18][2]*Vpk[16][18][2])))+((
          .1337*(Wpk[16][18][2]*Wpk[16][18][2]))+((.0332*(s17*s17))+(.1268*(
          Wpk[16][18][0]*Wpk[16][18][0]))))));
        temp[1] = (((1.2*((Vpk[16][21][2]*Vpk[16][21][2])+((Vpk[16][21][0]*
          Vpk[16][21][0])+(Vpk[16][21][1]*Vpk[16][21][1]))))+((.003916*(
          Wpk[16][21][2]*Wpk[16][21][2]))+((.001361*(Wpk[16][21][0]*
          Wpk[16][21][0]))+(.003709*(Wpk[16][21][1]*Wpk[16][21][1])))))+temp[0])
          ;
        mm[16][16] = (((.205126*((Vpk[16][22][2]*Vpk[16][22][2])+((
          Vpk[16][22][0]*Vpk[16][22][0])+(Vpk[16][22][1]*Vpk[16][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[16][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[16][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[16][22][1])))))+temp[1])
          ;
        temp[0] = (((3.51*((Vpk[16][19][2]*Vpk[17][19][2])+((Vpk[16][19][0]*
          Vpk[17][19][0])+(Vpk[16][19][1]*Vpk[17][19][1]))))+((.0484*(
          Wpk[16][19][2]*Wpk[17][19][2]))+((.0048*(Wpk[16][19][1]*Wpk[17][19][1]
          ))+(.0477*(Wpk[16][19][0]*Wpk[17][19][0])))))+((8.806*((.02941625*(
          Wpk[16][18][2]*s18))+(.1715*(Vpk[16][18][2]*c18))))+((.1337*(
          Wpk[16][18][2]*s18))-(.1268*(Wpk[16][18][0]*c18)))));
        temp[1] = (((1.2*((Vpk[16][21][2]*Vpk[17][21][2])+((Vpk[16][21][0]*
          Vpk[17][21][0])+(Vpk[16][21][1]*Vpk[17][21][1]))))+((.003916*(
          Wpk[16][21][2]*Wpk[17][21][2]))+((.001361*(Wpk[16][21][0]*
          Wpk[17][21][0]))+(.003709*(Wpk[16][21][1]*Wpk[17][21][1])))))+temp[0])
          ;
        mm[16][17] = (((.205126*((Vpk[16][22][2]*Vpk[17][22][2])+((
          Vpk[16][22][0]*Vpk[17][22][0])+(Vpk[16][22][1]*Vpk[17][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[17][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[17][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[17][22][1])))))+temp[1])
          ;
        temp[0] = (((.0332*s17)-(.017612*Vpk[16][18][2]))+((3.51*((
          Vpk[16][19][2]*Vpk[18][19][2])+((.0013*(Cik[19][2][1]*Vpk[16][19][1]))
          +(Vpk[16][19][0]*Vpk[18][19][0]))))-((.0484*(Cik[19][1][2]*
          Wpk[16][19][2]))+((.0048*(Cik[19][1][1]*Wpk[16][19][1]))+(.0477*(
          Cik[19][1][0]*Wpk[16][19][0]))))));
        temp[1] = (((1.2*((Vpk[16][21][2]*Vpk[18][21][2])+((Vpk[16][21][0]*
          Vpk[18][21][0])+(Vpk[16][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[16][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[16][21][0]*
          Wpk[18][21][0]))+(.003709*(Wpk[16][21][1]*Wpk[18][21][1])))))+temp[0])
          ;
        mm[16][18] = (((.205126*((Vpk[16][22][2]*Vpk[18][22][2])+((
          Vpk[16][22][0]*Vpk[18][22][0])+(Vpk[16][22][1]*Vpk[18][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[18][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[18][22][1])))))+temp[1])
          ;
        temp[0] = (((1.2*((Vpk[16][21][2]*Vpk[19][21][2])+((Vpk[16][21][0]*
          Vpk[19][21][0])+(Vpk[16][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[16][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[16][21][0]*
          Wpk[19][21][0]))+(.003709*(Wpk[16][21][1]*Wpk[19][21][1])))))+((3.51*(
          (.185436609363333*Vpk[16][19][0])-(.0150652581855386*Vpk[16][19][2])))
          +((.0482015676325742*Wpk[16][19][2])+((.00385935991111811*
          Wpk[16][19][0])-(.000194184030748461*Wpk[16][19][1])))));
        mm[16][19] = (((.205126*((Vpk[16][22][2]*Vpk[19][22][2])+((
          Vpk[16][22][0]*Vpk[19][22][0])+(Vpk[16][22][1]*Vpk[19][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[19][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[19][22][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[16][21][2]*Vpk[20][21][2])+((Vpk[16][21][0]*
          Vpk[20][21][0])+(Vpk[16][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[16][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[16][21][0]*
          Wpk[20][21][0]))+(.003709*(Wpk[16][21][1]*Wpk[20][21][1])))));
        mm[16][20] = (((.205126*((Vpk[16][22][2]*Vpk[20][22][2])+((
          Vpk[16][22][0]*Vpk[20][22][0])+(Vpk[16][22][1]*Vpk[20][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[20][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[20][22][1])))))+temp[0])
          ;
        mm[16][21] = (((.205126*((Vpk[16][22][2]*Vpk[21][22][2])+((
          Vpk[16][22][0]*Vpk[21][22][0])+(Vpk[16][22][1]*Vpk[21][22][1]))))+((
          .000119*(Wpk[16][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[16][22][0]*
          Wpk[21][22][0]))+(.000179*(Wpk[16][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[16][21][2])+((.000411457536296252*Vpk[16][21][0]
          )-(.00646090297985859*Vpk[16][21][1]))))-((.000212474287874234*
          Wpk[16][21][2])+((.00110888270658752*Wpk[16][21][0])+(
          .00214105693566144*Wpk[16][21][1])))));
        mm[16][22] = ((.205126*((.00868522709507149*Vpk[16][22][2])+((
          .02617891313962*Vpk[16][22][1])-(.0163345287751755*Vpk[16][22][0]))))+
          ((5.49281929796413e-5*Wpk[16][22][0])+(.00010507075266194*
          Wpk[16][22][2])));
        temp[0] = (((.00690000000000002*(s18*s18))+(8.806*(.02941225+(
          4.00000000000053e-6*(s18*s18)))))+((3.51*((Vpk[17][19][2]*
          Vpk[17][19][2])+((Vpk[17][19][0]*Vpk[17][19][0])+(Vpk[17][19][1]*
          Vpk[17][19][1]))))+((.0484*(Wpk[17][19][2]*Wpk[17][19][2]))+((.0048*(
          Wpk[17][19][1]*Wpk[17][19][1]))+(.0477*(Wpk[17][19][0]*Wpk[17][19][0])
          )))));
        temp[1] = (((1.2*((Vpk[17][21][2]*Vpk[17][21][2])+((Vpk[17][21][0]*
          Vpk[17][21][0])+(Vpk[17][21][1]*Vpk[17][21][1]))))+((.003916*(
          Wpk[17][21][2]*Wpk[17][21][2]))+((.001361*(Wpk[17][21][0]*
          Wpk[17][21][0]))+(.003709*(Wpk[17][21][1]*Wpk[17][21][1])))))+temp[0])
          ;
        mm[17][17] = (.1268+(((.205126*((Vpk[17][22][2]*Vpk[17][22][2])+((
          Vpk[17][22][0]*Vpk[17][22][0])+(Vpk[17][22][1]*Vpk[17][22][1]))))+((
          .000119*(Wpk[17][22][2]*Wpk[17][22][2]))+((.000117*(Wpk[17][22][0]*
          Wpk[17][22][0]))+(.000179*(Wpk[17][22][1]*Wpk[17][22][1])))))+temp[1])
          );
        temp[0] = (((3.51*((Vpk[17][19][2]*Vpk[18][19][2])+((.0013*(
          Cik[19][2][1]*Vpk[17][19][1]))+(Vpk[17][19][0]*Vpk[18][19][0]))))-((
          .0484*(Cik[19][1][2]*Wpk[17][19][2]))+((.0048*(Cik[19][1][1]*
          Wpk[17][19][1]))+(.0477*(Cik[19][1][0]*Wpk[17][19][0])))))-(.003020458
          *c18));
        temp[1] = (((1.2*((Vpk[17][21][2]*Vpk[18][21][2])+((Vpk[17][21][0]*
          Vpk[18][21][0])+(Vpk[17][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[17][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[17][21][0]*
          Wpk[18][21][0]))+(.003709*(Wpk[17][21][1]*Wpk[18][21][1])))))+temp[0])
          ;
        mm[17][18] = (((.205126*((Vpk[17][22][2]*Vpk[18][22][2])+((
          Vpk[17][22][0]*Vpk[18][22][0])+(Vpk[17][22][1]*Vpk[18][22][1]))))+((
          .000119*(Wpk[17][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[17][22][0]*
          Wpk[18][22][0]))+(.000179*(Wpk[17][22][1]*Wpk[18][22][1])))))+temp[1])
          ;
        temp[0] = (((1.2*((Vpk[17][21][2]*Vpk[19][21][2])+((Vpk[17][21][0]*
          Vpk[19][21][0])+(Vpk[17][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[17][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[17][21][0]*
          Wpk[19][21][0]))+(.003709*(Wpk[17][21][1]*Wpk[19][21][1])))))+((3.51*(
          (.185436609363333*Vpk[17][19][0])-(.0150652581855386*Vpk[17][19][2])))
          +((.0482015676325742*Wpk[17][19][2])+((.00385935991111811*
          Wpk[17][19][0])-(.000194184030748461*Wpk[17][19][1])))));
        mm[17][19] = (((.205126*((Vpk[17][22][2]*Vpk[19][22][2])+((
          Vpk[17][22][0]*Vpk[19][22][0])+(Vpk[17][22][1]*Vpk[19][22][1]))))+((
          .000119*(Wpk[17][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[17][22][0]*
          Wpk[19][22][0]))+(.000179*(Wpk[17][22][1]*Wpk[19][22][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[17][21][2]*Vpk[20][21][2])+((Vpk[17][21][0]*
          Vpk[20][21][0])+(Vpk[17][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[17][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[17][21][0]*
          Wpk[20][21][0]))+(.003709*(Wpk[17][21][1]*Wpk[20][21][1])))));
        mm[17][20] = (((.205126*((Vpk[17][22][2]*Vpk[20][22][2])+((
          Vpk[17][22][0]*Vpk[20][22][0])+(Vpk[17][22][1]*Vpk[20][22][1]))))+((
          .000119*(Wpk[17][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[17][22][0]*
          Wpk[20][22][0]))+(.000179*(Wpk[17][22][1]*Wpk[20][22][1])))))+temp[0])
          ;
        mm[17][21] = (((.205126*((Vpk[17][22][2]*Vpk[21][22][2])+((
          Vpk[17][22][0]*Vpk[21][22][0])+(Vpk[17][22][1]*Vpk[21][22][1]))))+((
          .000119*(Wpk[17][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[17][22][0]*
          Wpk[21][22][0]))+(.000179*(Wpk[17][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[17][21][2])+((.000411457536296252*Vpk[17][21][0]
          )-(.00646090297985859*Vpk[17][21][1]))))-((.000212474287874234*
          Wpk[17][21][2])+((.00110888270658752*Wpk[17][21][0])+(
          .00214105693566144*Wpk[17][21][1])))));
        mm[17][22] = ((.205126*((.00868522709507149*Vpk[17][22][2])+((
          .02617891313962*Vpk[17][22][1])-(.0163345287751755*Vpk[17][22][0]))))+
          ((5.49281929796413e-5*Wpk[17][22][0])+(.00010507075266194*
          Wpk[17][22][2])));
        temp[0] = ((3.51*((Vpk[18][19][2]*Vpk[18][19][2])+((1.69e-6*(
          Cik[19][2][1]*Cik[19][2][1]))+(Vpk[18][19][0]*Vpk[18][19][0]))))+((
          .0484*(Cik[19][1][2]*Cik[19][1][2]))+((.0048*(Cik[19][1][1]*
          Cik[19][1][1]))+(.0477*(Cik[19][1][0]*Cik[19][1][0])))));
        temp[1] = (((1.2*((Vpk[18][21][2]*Vpk[18][21][2])+((Vpk[18][21][0]*
          Vpk[18][21][0])+(Vpk[18][21][1]*Vpk[18][21][1]))))+((.003916*(
          Wpk[18][21][2]*Wpk[18][21][2]))+((.001361*(Wpk[18][21][0]*
          Wpk[18][21][0]))+(.003709*(Wpk[18][21][1]*Wpk[18][21][1])))))+temp[0])
          ;
        mm[18][18] = (.033235224+(((.205126*((Vpk[18][22][2]*Vpk[18][22][2])+((
          Vpk[18][22][0]*Vpk[18][22][0])+(Vpk[18][22][1]*Vpk[18][22][1]))))+((
          .000119*(Wpk[18][22][2]*Wpk[18][22][2]))+((.000117*(Wpk[18][22][0]*
          Wpk[18][22][0]))+(.000179*(Wpk[18][22][1]*Wpk[18][22][1])))))+temp[1])
          );
        temp[0] = (((1.2*((Vpk[18][21][2]*Vpk[19][21][2])+((Vpk[18][21][0]*
          Vpk[19][21][0])+(Vpk[18][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[18][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[18][21][0]*
          Wpk[19][21][0]))+(.003709*(Wpk[18][21][1]*Wpk[19][21][1])))))+((3.51*(
          (.185436609363333*Vpk[18][19][0])-(.0150652581855386*Vpk[18][19][2])))
          +(((.000194184030748461*Cik[19][1][1])-(.00385935991111811*
          Cik[19][1][0]))-(.0482015676325742*Cik[19][1][2]))));
        mm[18][19] = (((.205126*((Vpk[18][22][2]*Vpk[19][22][2])+((
          Vpk[18][22][0]*Vpk[19][22][0])+(Vpk[18][22][1]*Vpk[19][22][1]))))+((
          .000119*(Wpk[18][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[18][22][0]*
          Wpk[19][22][0]))+(.000179*(Wpk[18][22][1]*Wpk[19][22][1])))))+temp[0])
          ;
        temp[0] = ((1.2*((Vpk[18][21][2]*Vpk[20][21][2])+((Vpk[18][21][0]*
          Vpk[20][21][0])+(Vpk[18][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[18][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[18][21][0]*
          Wpk[20][21][0]))+(.003709*(Wpk[18][21][1]*Wpk[20][21][1])))));
        mm[18][20] = (((.205126*((Vpk[18][22][2]*Vpk[20][22][2])+((
          Vpk[18][22][0]*Vpk[20][22][0])+(Vpk[18][22][1]*Vpk[20][22][1]))))+((
          .000119*(Wpk[18][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[18][22][0]*
          Wpk[20][22][0]))+(.000179*(Wpk[18][22][1]*Wpk[20][22][1])))))+temp[0])
          ;
        mm[18][21] = (((.205126*((Vpk[18][22][2]*Vpk[21][22][2])+((
          Vpk[18][22][0]*Vpk[21][22][0])+(Vpk[18][22][1]*Vpk[21][22][1]))))+((
          .000119*(Wpk[18][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[18][22][0]*
          Wpk[21][22][0]))+(.000179*(Wpk[18][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[18][21][2])+((.000411457536296252*Vpk[18][21][0]
          )-(.00646090297985859*Vpk[18][21][1]))))-((.000212474287874234*
          Wpk[18][21][2])+((.00110888270658752*Wpk[18][21][0])+(
          .00214105693566144*Wpk[18][21][1])))));
        mm[18][22] = ((.205126*((.00868522709507149*Vpk[18][22][2])+((
          .02617891313962*Vpk[18][22][1])-(.0163345287751755*Vpk[18][22][0]))))+
          ((5.49281929796413e-5*Wpk[18][22][0])+(.00010507075266194*
          Wpk[18][22][2])));
        temp[0] = ((1.2*((Vpk[19][21][2]*Vpk[19][21][2])+((Vpk[19][21][0]*
          Vpk[19][21][0])+(Vpk[19][21][1]*Vpk[19][21][1]))))+((.003916*(
          Wpk[19][21][2]*Wpk[19][21][2]))+((.001361*(Wpk[19][21][0]*
          Wpk[19][21][0]))+(.003709*(Wpk[19][21][1]*Wpk[19][21][1])))));
        mm[19][19] = (.16981814184151+(((.205126*((Vpk[19][22][2]*Vpk[19][22][2]
          )+((Vpk[19][22][0]*Vpk[19][22][0])+(Vpk[19][22][1]*Vpk[19][22][1]))))+
          ((.000119*(Wpk[19][22][2]*Wpk[19][22][2]))+((.000117*(Wpk[19][22][0]*
          Wpk[19][22][0]))+(.000179*(Wpk[19][22][1]*Wpk[19][22][1])))))+temp[0])
          );
        temp[0] = ((1.2*((Vpk[19][21][2]*Vpk[20][21][2])+((Vpk[19][21][0]*
          Vpk[20][21][0])+(Vpk[19][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[19][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[19][21][0]*
          Wpk[20][21][0]))+(.003709*(Wpk[19][21][1]*Wpk[20][21][1])))));
        mm[19][20] = (((.205126*((Vpk[19][22][2]*Vpk[20][22][2])+((
          Vpk[19][22][0]*Vpk[20][22][0])+(Vpk[19][22][1]*Vpk[20][22][1]))))+((
          .000119*(Wpk[19][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[19][22][0]*
          Wpk[20][22][0]))+(.000179*(Wpk[19][22][1]*Wpk[20][22][1])))))+temp[0])
          ;
        mm[19][21] = (((.205126*((Vpk[19][22][2]*Vpk[21][22][2])+((
          Vpk[19][22][0]*Vpk[21][22][0])+(Vpk[19][22][1]*Vpk[21][22][1]))))+((
          .000119*(Wpk[19][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[19][22][0]*
          Wpk[21][22][0]))+(.000179*(Wpk[19][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[19][21][2])+((.000411457536296252*Vpk[19][21][0]
          )-(.00646090297985859*Vpk[19][21][1]))))-((.000212474287874234*
          Wpk[19][21][2])+((.00110888270658752*Wpk[19][21][0])+(
          .00214105693566144*Wpk[19][21][1])))));
        mm[19][22] = ((.205126*((.00868522709507149*Vpk[19][22][2])+((
          .02617891313962*Vpk[19][22][1])-(.0163345287751755*Vpk[19][22][0]))))+
          ((5.49281929796413e-5*Wpk[19][22][0])+(.00010507075266194*
          Wpk[19][22][2])));
        temp[0] = ((1.2*((Vpk[20][21][2]*Vpk[20][21][2])+((Vpk[20][21][0]*
          Vpk[20][21][0])+(Vpk[20][21][1]*Vpk[20][21][1]))))+((.003916*(
          Wpk[20][21][2]*Wpk[20][21][2]))+((.001361*(Wpk[20][21][0]*
          Wpk[20][21][0]))+(.003709*(Wpk[20][21][1]*Wpk[20][21][1])))));
        mm[20][20] = (((.205126*((Vpk[20][22][2]*Vpk[20][22][2])+((
          Vpk[20][22][0]*Vpk[20][22][0])+(Vpk[20][22][1]*Vpk[20][22][1]))))+((
          .000119*(Wpk[20][22][2]*Wpk[20][22][2]))+((.000117*(Wpk[20][22][0]*
          Wpk[20][22][0]))+(.000179*(Wpk[20][22][1]*Wpk[20][22][1])))))+temp[0])
          ;
        mm[20][21] = (((.205126*((Vpk[20][22][2]*Vpk[21][22][2])+((
          Vpk[20][22][0]*Vpk[21][22][0])+(Vpk[20][22][1]*Vpk[21][22][1]))))+((
          .000119*(Wpk[20][22][2]*Wpk[21][22][2]))+((.000117*(Wpk[20][22][0]*
          Wpk[21][22][0]))+(.000179*(Wpk[20][22][1]*Wpk[21][22][1])))))+((1.2*((
          .0625600530375351*Vpk[20][21][2])+((.000411457536296252*Vpk[20][21][0]
          )-(.00646090297985859*Vpk[20][21][1]))))-((.000212474287874234*
          Wpk[20][21][2])+((.00110888270658752*Wpk[20][21][0])+(
          .00214105693566144*Wpk[20][21][1])))));
        mm[20][22] = ((.205126*((.00868522709507149*Vpk[20][22][2])+((
          .02617891313962*Vpk[20][22][1])-(.0163345287751755*Vpk[20][22][0]))))+
          ((5.49281929796413e-5*Wpk[20][22][0])+(.00010507075266194*
          Wpk[20][22][2])));
        mm[21][21] = (.00689775074968843+((.205126*((Vpk[21][22][2]*
          Vpk[21][22][2])+((Vpk[21][22][0]*Vpk[21][22][0])+(Vpk[21][22][1]*
          Vpk[21][22][1]))))+((.000119*(Wpk[21][22][2]*Wpk[21][22][2]))+((
          .000117*(Wpk[21][22][0]*Wpk[21][22][0]))+(.000179*(Wpk[21][22][1]*
          Wpk[21][22][1]))))));
        mm[21][22] = ((.205126*((.00868522709507149*Vpk[21][22][2])+((
          .02617891313962*Vpk[21][22][1])-(.0163345287751755*Vpk[21][22][0]))))+
          ((5.49281929796413e-5*Wpk[21][22][0])+(.00010507075266194*
          Wpk[21][22][2])));
        mm[22][22] = .000329343694452671;
/*
Check for singular mass matrix
*/
        for (i = 0; i < 23; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        mmflg = 1;
    }
/*
 Used 0.82 seconds CPU time,
 49152 additional bytes of memory.
 Equations contain 2332 adds/subtracts/negates
                   3871 multiplies
                      0 divides
                    466 assignments
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
        sdldudcomp(23,23,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 23; i++) {
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
    double mmat[23][23];
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 23; i++) {
        for (j = i; j <= 22; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}


#define rdNU 23
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


sdfrcmat(fmat)
    double fmat[23];
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 23; i++) {
        fmat[i] = fs0[i];
    }
}

sdmfrc(imult)
    double imult[1];
{

}

sdequivht(tau)
    double tau[23];
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[23][3],tstareq[23][3];

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
    fstareq[8][1] = -(ufk[1][1]+(32.413*gk[7][1]));
    fstareq[8][2] = -(ufk[1][2]+(32.413*gk[8][2]));
    fstareq[11][0] = -(ufk[2][0]+(8.806*gk[11][0]));
    fstareq[11][1] = -(ufk[2][1]+(8.806*gk[10][1]));
    fstareq[11][2] = -(ufk[2][2]+(8.806*gk[11][2]));
    fstareq[12][0] = -(ufk[3][0]+(3.51*gk[12][0]));
    fstareq[12][1] = -(ufk[3][1]+(3.51*gk[12][1]));
    fstareq[12][2] = -(ufk[3][2]+(3.51*gk[12][2]));
    fstareq[14][0] = -(ufk[4][0]+(1.2*gk[14][0]));
    fstareq[14][1] = -(ufk[4][1]+(1.2*gk[14][1]));
    fstareq[14][2] = -(ufk[4][2]+(1.2*gk[14][2]));
    fstareq[15][0] = -(ufk[5][0]+(.205126*gk[15][0]));
    fstareq[15][1] = -(ufk[5][1]+(.205126*gk[15][1]));
    fstareq[15][2] = -(ufk[5][2]+(.205126*gk[15][2]));
    fstareq[18][0] = -(ufk[6][0]+(8.806*gk[18][0]));
    fstareq[18][1] = -(ufk[6][1]+(8.806*gk[17][1]));
    fstareq[18][2] = -(ufk[6][2]+(8.806*gk[18][2]));
    fstareq[19][0] = -(ufk[7][0]+(3.51*gk[19][0]));
    fstareq[19][1] = -(ufk[7][1]+(3.51*gk[19][1]));
    fstareq[19][2] = -(ufk[7][2]+(3.51*gk[19][2]));
    fstareq[21][0] = -(ufk[8][0]+(1.2*gk[21][0]));
    fstareq[21][1] = -(ufk[8][1]+(1.2*gk[21][1]));
    fstareq[21][2] = -(ufk[8][2]+(1.2*gk[21][2]));
    fstareq[22][0] = -(ufk[9][0]+(.205126*gk[22][0]));
    fstareq[22][1] = -(ufk[9][1]+(.205126*gk[22][1]));
    fstareq[22][2] = -(ufk[9][2]+(.205126*gk[22][2]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    temp[0] = (((fstareq[12][2]*Vpk[0][12][2])+((fstareq[12][0]*Vpk[0][12][0])+(
      fstareq[12][1]*Vpk[0][12][1])))+(((fstareq[11][2]*Vpk[0][11][2])+((
      fstareq[11][0]*Vpk[0][11][0])+(fstareq[11][1]*Vpk[0][10][1])))+(((
      Cik[3][0][2]*fstareq[5][2])+((Cik[3][0][0]*fstareq[5][0])+(Cik[3][0][1]*
      fstareq[5][1])))+((fstareq[8][2]*Vpk[0][8][2])+((fstareq[8][0]*
      Vpk[0][8][0])+(fstareq[8][1]*Vpk[0][7][1]))))));
    temp[1] = (((fstareq[19][2]*Vpk[0][19][2])+((fstareq[19][0]*Vpk[0][19][0])+(
      fstareq[19][1]*Vpk[0][19][1])))+(((fstareq[18][2]*Vpk[0][18][2])+((
      fstareq[18][0]*Vpk[0][18][0])+(fstareq[18][1]*Vpk[0][17][1])))+(((
      fstareq[15][2]*Vpk[0][15][2])+((fstareq[15][0]*Vpk[0][15][0])+(
      fstareq[15][1]*Vpk[0][15][1])))+(((fstareq[14][2]*Vpk[0][14][2])+((
      fstareq[14][0]*Vpk[0][14][0])+(fstareq[14][1]*Vpk[0][14][1])))+temp[0]))))
      ;
    tau[0] = (utau[0]-(((fstareq[22][2]*Vpk[0][22][2])+((fstareq[22][0]*
      Vpk[0][22][0])+(fstareq[22][1]*Vpk[0][22][1])))+(((fstareq[21][2]*
      Vpk[0][21][2])+((fstareq[21][0]*Vpk[0][21][0])+(fstareq[21][1]*
      Vpk[0][21][1])))+temp[1])));
    temp[0] = (((fstareq[12][2]*Vpk[1][12][2])+((fstareq[12][0]*Vpk[1][12][0])+(
      fstareq[12][1]*Vpk[1][12][1])))+(((fstareq[11][2]*Vpk[1][11][2])+((
      fstareq[11][0]*Vpk[1][11][0])+(fstareq[11][1]*Vpk[1][10][1])))+(((
      Cik[3][1][2]*fstareq[5][2])+((Cik[3][1][0]*fstareq[5][0])+(Cik[3][1][1]*
      fstareq[5][1])))+((fstareq[8][2]*Vpk[1][8][2])+((fstareq[8][0]*
      Vpk[1][8][0])+(fstareq[8][1]*Vpk[1][7][1]))))));
    temp[1] = (((fstareq[19][2]*Vpk[1][19][2])+((fstareq[19][0]*Vpk[1][19][0])+(
      fstareq[19][1]*Vpk[1][19][1])))+(((fstareq[18][2]*Vpk[1][18][2])+((
      fstareq[18][0]*Vpk[1][18][0])+(fstareq[18][1]*Vpk[1][17][1])))+(((
      fstareq[15][2]*Vpk[1][15][2])+((fstareq[15][0]*Vpk[1][15][0])+(
      fstareq[15][1]*Vpk[1][15][1])))+(((fstareq[14][2]*Vpk[1][14][2])+((
      fstareq[14][0]*Vpk[1][14][0])+(fstareq[14][1]*Vpk[1][14][1])))+temp[0]))))
      ;
    tau[1] = (utau[1]-(((fstareq[22][2]*Vpk[1][22][2])+((fstareq[22][0]*
      Vpk[1][22][0])+(fstareq[22][1]*Vpk[1][22][1])))+(((fstareq[21][2]*
      Vpk[1][21][2])+((fstareq[21][0]*Vpk[1][21][0])+(fstareq[21][1]*
      Vpk[1][21][1])))+temp[1])));
    temp[0] = (((fstareq[12][2]*Vpk[2][12][2])+((fstareq[12][0]*Vpk[2][12][0])+(
      fstareq[12][1]*Vpk[2][12][1])))+(((fstareq[11][2]*Vpk[2][11][2])+((
      fstareq[11][0]*Vpk[2][11][0])+(fstareq[11][1]*Vpk[2][10][1])))+(((
      Cik[3][2][2]*fstareq[5][2])+((Cik[3][2][0]*fstareq[5][0])+(Cik[3][2][1]*
      fstareq[5][1])))+((fstareq[8][2]*Vpk[2][8][2])+((fstareq[8][0]*
      Vpk[2][8][0])+(fstareq[8][1]*Vpk[2][7][1]))))));
    temp[1] = (((fstareq[19][2]*Vpk[2][19][2])+((fstareq[19][0]*Vpk[2][19][0])+(
      fstareq[19][1]*Vpk[2][19][1])))+(((fstareq[18][2]*Vpk[2][18][2])+((
      fstareq[18][0]*Vpk[2][18][0])+(fstareq[18][1]*Vpk[2][17][1])))+(((
      fstareq[15][2]*Vpk[2][15][2])+((fstareq[15][0]*Vpk[2][15][0])+(
      fstareq[15][1]*Vpk[2][15][1])))+(((fstareq[14][2]*Vpk[2][14][2])+((
      fstareq[14][0]*Vpk[2][14][0])+(fstareq[14][1]*Vpk[2][14][1])))+temp[0]))))
      ;
    tau[2] = (utau[2]-(((fstareq[22][2]*Vpk[2][22][2])+((fstareq[22][0]*
      Vpk[2][22][0])+(fstareq[22][1]*Vpk[2][22][1])))+(((fstareq[21][2]*
      Vpk[2][21][2])+((fstareq[21][0]*Vpk[2][21][0])+(fstareq[21][1]*
      Vpk[2][21][1])))+temp[1])));
    temp[0] = ((((fstareq[11][2]*Vpk[3][11][2])+((fstareq[11][0]*Vpk[3][11][0])+
      (fstareq[11][1]*Vpk[3][11][1])))-((utk[2][2]*Wpk[3][11][2])+((utk[2][0]*
      Wpk[3][11][0])+(utk[2][1]*Wpk[3][10][1]))))+((((fstareq[8][2]*Vpk[3][8][2]
      )+((.127*(fstareq[8][1]*s7))+(fstareq[8][0]*Vpk[3][8][0])))-((utk[1][2]*
      Wpk[3][8][2])+((utk[1][0]*Wpk[3][8][0])+(utk[1][1]*Wpk[3][7][1]))))-
      utk[0][0]));
    temp[1] = ((((fstareq[14][2]*Vpk[3][14][2])+((fstareq[14][0]*Vpk[3][14][0])+
      (fstareq[14][1]*Vpk[3][14][1])))-((utk[4][2]*Wpk[3][14][2])+((utk[4][0]*
      Wpk[3][14][0])+(utk[4][1]*Wpk[3][14][1]))))+((((fstareq[12][2]*
      Vpk[3][12][2])+((fstareq[12][0]*Vpk[3][12][0])+(fstareq[12][1]*
      Vpk[3][12][1])))-((utk[3][2]*Wpk[3][12][2])+((utk[3][0]*Wpk[3][12][0])+(
      utk[3][1]*Wpk[3][12][1]))))+temp[0]));
    temp[2] = ((((fstareq[18][2]*Vpk[3][18][2])+((fstareq[18][0]*Vpk[3][18][0])+
      (fstareq[18][1]*Vpk[3][18][1])))-((utk[6][2]*Wpk[3][18][2])+((utk[6][0]*
      Wpk[3][18][0])+(utk[6][1]*Wpk[3][17][1]))))+((((fstareq[15][2]*
      Vpk[3][15][2])+((fstareq[15][0]*Vpk[3][15][0])+(fstareq[15][1]*
      Vpk[3][15][1])))-((utk[5][2]*Wpk[3][15][2])+((utk[5][0]*Wpk[3][15][0])+(
      utk[5][1]*Wpk[3][15][1]))))+temp[1]));
    temp[3] = ((((fstareq[21][2]*Vpk[3][21][2])+((fstareq[21][0]*Vpk[3][21][0])+
      (fstareq[21][1]*Vpk[3][21][1])))-((utk[8][2]*Wpk[3][21][2])+((utk[8][0]*
      Wpk[3][21][0])+(utk[8][1]*Wpk[3][21][1]))))+((((fstareq[19][2]*
      Vpk[3][19][2])+((fstareq[19][0]*Vpk[3][19][0])+(fstareq[19][1]*
      Vpk[3][19][1])))-((utk[7][2]*Wpk[3][19][2])+((utk[7][0]*Wpk[3][19][0])+(
      utk[7][1]*Wpk[3][19][1]))))+temp[2]));
    tau[3] = (utau[3]-((((fstareq[22][2]*Vpk[3][22][2])+((fstareq[22][0]*
      Vpk[3][22][0])+(fstareq[22][1]*Vpk[3][22][1])))-((utk[9][2]*Wpk[3][22][2])
      +((utk[9][0]*Wpk[3][22][0])+(utk[9][1]*Wpk[3][22][1]))))+temp[3]));
    temp[0] = ((((.3202*((fstareq[8][2]*Wpk[4][8][0])-(fstareq[8][0]*
      Wpk[4][8][2])))-((utk[1][2]*Wpk[4][8][2])+((utk[1][0]*Wpk[4][8][0])+(
      utk[1][1]*Wpk[4][7][1]))))-utk[0][1])+(((fstareq[11][2]*Vpk[4][11][2])+((
      fstareq[11][0]*Vpk[4][11][0])+(fstareq[11][1]*Vpk[4][11][1])))-((utk[2][2]
      *Wpk[4][11][2])+((utk[2][0]*Wpk[4][11][0])+(utk[2][1]*Wpk[4][10][1])))));
    temp[1] = ((((fstareq[14][2]*Vpk[4][14][2])+((fstareq[14][0]*Vpk[4][14][0])+
      (fstareq[14][1]*Vpk[4][14][1])))-((utk[4][2]*Wpk[4][14][2])+((utk[4][0]*
      Wpk[4][14][0])+(utk[4][1]*Wpk[4][14][1]))))+((((fstareq[12][2]*
      Vpk[4][12][2])+((fstareq[12][0]*Vpk[4][12][0])+(fstareq[12][1]*
      Vpk[4][12][1])))-((utk[3][2]*Wpk[4][12][2])+((utk[3][0]*Wpk[4][12][0])+(
      utk[3][1]*Wpk[4][12][1]))))+temp[0]));
    temp[2] = ((((fstareq[18][2]*Vpk[4][18][2])+((fstareq[18][0]*Vpk[4][18][0])+
      (fstareq[18][1]*Vpk[4][18][1])))-((utk[6][2]*Wpk[4][18][2])+((utk[6][0]*
      Wpk[4][18][0])+(utk[6][1]*Wpk[4][17][1]))))+((((fstareq[15][2]*
      Vpk[4][15][2])+((fstareq[15][0]*Vpk[4][15][0])+(fstareq[15][1]*
      Vpk[4][15][1])))-((utk[5][2]*Wpk[4][15][2])+((utk[5][0]*Wpk[4][15][0])+(
      utk[5][1]*Wpk[4][15][1]))))+temp[1]));
    temp[3] = ((((fstareq[21][2]*Vpk[4][21][2])+((fstareq[21][0]*Vpk[4][21][0])+
      (fstareq[21][1]*Vpk[4][21][1])))-((utk[8][2]*Wpk[4][21][2])+((utk[8][0]*
      Wpk[4][21][0])+(utk[8][1]*Wpk[4][21][1]))))+((((fstareq[19][2]*
      Vpk[4][19][2])+((fstareq[19][0]*Vpk[4][19][0])+(fstareq[19][1]*
      Vpk[4][19][1])))-((utk[7][2]*Wpk[4][19][2])+((utk[7][0]*Wpk[4][19][0])+(
      utk[7][1]*Wpk[4][19][1]))))+temp[2]));
    tau[4] = (utau[4]-((((fstareq[22][2]*Vpk[4][22][2])+((fstareq[22][0]*
      Vpk[4][22][0])+(fstareq[22][1]*Vpk[4][22][1])))-((utk[9][2]*Wpk[4][22][2])
      +((utk[9][0]*Wpk[4][22][0])+(utk[9][1]*Wpk[4][22][1]))))+temp[3]));
    temp[0] = ((((fstareq[11][2]*Vpk[5][11][2])+((fstareq[11][0]*Vpk[5][11][0])+
      (fstareq[11][1]*Vpk[5][11][1])))-((utk[2][2]*Wpk[5][11][2])+((utk[2][0]*
      Wpk[5][11][0])+(utk[2][1]*s10))))+((((fstareq[8][2]*Vpk[5][8][2])+((
      fstareq[8][0]*Vpk[5][8][0])+(fstareq[8][1]*Vpk[5][7][1])))-((utk[1][2]*
      Wpk[5][8][2])+((utk[1][0]*Wpk[5][8][0])+(utk[1][1]*s7))))-utk[0][2]));
    temp[1] = ((((fstareq[14][2]*Vpk[5][14][2])+((fstareq[14][0]*Vpk[5][14][0])+
      (fstareq[14][1]*Vpk[5][14][1])))-((utk[4][2]*Wpk[5][14][2])+((utk[4][0]*
      Wpk[5][14][0])+(utk[4][1]*Wpk[5][14][1]))))+((((fstareq[12][2]*
      Vpk[5][12][2])+((fstareq[12][0]*Vpk[5][12][0])+(fstareq[12][1]*
      Vpk[5][12][1])))-((utk[3][2]*Wpk[5][12][2])+((utk[3][0]*Wpk[5][12][0])+(
      utk[3][1]*Wpk[5][12][1]))))+temp[0]));
    temp[2] = ((((fstareq[18][2]*Vpk[5][18][2])+((fstareq[18][0]*Vpk[5][18][0])+
      (fstareq[18][1]*Vpk[5][18][1])))+(((utk[6][1]*s17)-(utk[6][0]*
      Wpk[5][18][0]))-(utk[6][2]*Wpk[5][18][2])))+((((fstareq[15][2]*
      Vpk[5][15][2])+((fstareq[15][0]*Vpk[5][15][0])+(fstareq[15][1]*
      Vpk[5][15][1])))-((utk[5][2]*Wpk[5][15][2])+((utk[5][0]*Wpk[5][15][0])+(
      utk[5][1]*Wpk[5][15][1]))))+temp[1]));
    temp[3] = ((((fstareq[21][2]*Vpk[5][21][2])+((fstareq[21][0]*Vpk[5][21][0])+
      (fstareq[21][1]*Vpk[5][21][1])))-((utk[8][2]*Wpk[5][21][2])+((utk[8][0]*
      Wpk[5][21][0])+(utk[8][1]*Wpk[5][21][1]))))+((((fstareq[19][2]*
      Vpk[5][19][2])+((fstareq[19][0]*Vpk[5][19][0])+(fstareq[19][1]*
      Vpk[5][19][1])))-((utk[7][2]*Wpk[5][19][2])+((utk[7][0]*Wpk[5][19][0])+(
      utk[7][1]*Wpk[5][19][1]))))+temp[2]));
    tau[5] = (utau[5]-((((fstareq[22][2]*Vpk[5][22][2])+((fstareq[22][0]*
      Vpk[5][22][0])+(fstareq[22][1]*Vpk[5][22][1])))-((utk[9][2]*Wpk[5][22][2])
      +((utk[9][0]*Wpk[5][22][0])+(utk[9][1]*Wpk[5][22][1]))))+temp[3]));
    tau[6] = (utau[6]-((.3202*((fstareq[8][2]*Wpk[6][8][0])-(fstareq[8][0]*
      Wpk[6][8][2])))-((utk[1][2]*Wpk[6][8][2])+((utk[1][0]*Wpk[6][8][0])+(
      utk[1][1]*s7)))));
    tau[7] = (utau[7]-((.3202*((fstareq[8][2]*c8)-(fstareq[8][0]*s8)))-((
      utk[1][0]*c8)+(utk[1][2]*s8))));
    tau[8] = (utau[8]+utk[1][1]);
    temp[0] = ((((fstareq[11][2]*Vpk[9][11][2])+((.1715*(fstareq[11][0]*
      Wpk[9][11][2]))-(.002*(fstareq[11][1]*Wpk[9][11][2]))))-((utk[2][2]*
      Wpk[9][11][2])+((utk[2][0]*Wpk[9][11][0])+(utk[2][1]*s10))))+(((
      fstareq[12][2]*Vpk[9][12][2])+((fstareq[12][0]*Vpk[9][12][0])+(
      fstareq[12][1]*Vpk[9][12][1])))-((utk[3][2]*Wpk[9][12][2])+((utk[3][0]*
      Wpk[9][12][0])+(utk[3][1]*Wpk[9][12][1])))));
    tau[9] = (utau[9]-((((fstareq[15][2]*Vpk[9][15][2])+((fstareq[15][0]*
      Vpk[9][15][0])+(fstareq[15][1]*Vpk[9][15][1])))-((utk[5][2]*Wpk[9][15][2])
      +((utk[5][0]*Wpk[9][15][0])+(utk[5][1]*Wpk[9][15][1]))))+((((
      fstareq[14][2]*Vpk[9][14][2])+((fstareq[14][0]*Vpk[9][14][0])+(
      fstareq[14][1]*Vpk[9][14][1])))-((utk[4][2]*Wpk[9][14][2])+((utk[4][0]*
      Wpk[9][14][0])+(utk[4][1]*Wpk[9][14][1]))))+temp[0])));
    temp[0] = ((((fstareq[12][2]*Vpk[10][12][2])+((fstareq[12][0]*Vpk[10][12][0]
      )+(fstareq[12][1]*Vpk[10][12][1])))-((utk[3][2]*Wpk[10][12][2])+((
      utk[3][0]*Wpk[10][12][0])+(utk[3][1]*Wpk[10][12][1]))))+((((.1715*(
      fstareq[11][0]*s11))-(.002*(fstareq[11][1]*s11)))-(.1715*(fstareq[11][2]*
      c11)))-((utk[2][0]*c11)+(utk[2][2]*s11))));
    tau[10] = (utau[10]-((((fstareq[15][2]*Vpk[10][15][2])+((fstareq[15][0]*
      Vpk[10][15][0])+(fstareq[15][1]*Vpk[10][15][1])))-((utk[5][2]*
      Wpk[10][15][2])+((utk[5][0]*Wpk[10][15][0])+(utk[5][1]*Wpk[10][15][1]))))+
      ((((fstareq[14][2]*Vpk[10][14][2])+((fstareq[14][0]*Vpk[10][14][0])+(
      fstareq[14][1]*Vpk[10][14][1])))-((utk[4][2]*Wpk[10][14][2])+((utk[4][0]*
      Wpk[10][14][0])+(utk[4][1]*Wpk[10][14][1]))))+temp[0])));
    temp[0] = ((((.002*fstareq[11][2])-utk[2][1])+(((fstareq[12][2]*
      Vpk[11][12][2])+((fstareq[12][0]*Vpk[11][12][0])-(.0013*(Cik[12][2][1]*
      fstareq[12][1]))))-((Cik[12][1][2]*utk[3][2])+((Cik[12][1][0]*utk[3][0])+(
      Cik[12][1][1]*utk[3][1])))))+(((fstareq[14][2]*Vpk[11][14][2])+((
      fstareq[14][0]*Vpk[11][14][0])+(fstareq[14][1]*Vpk[11][14][1])))-((
      utk[4][2]*Wpk[11][14][2])+((utk[4][0]*Wpk[11][14][0])+(utk[4][1]*
      Wpk[11][14][1])))));
    tau[11] = (utau[11]-((((fstareq[15][2]*Vpk[11][15][2])+((fstareq[15][0]*
      Vpk[11][15][0])+(fstareq[15][1]*Vpk[11][15][1])))-((utk[5][2]*
      Wpk[11][15][2])+((utk[5][0]*Wpk[11][15][0])+(utk[5][1]*Wpk[11][15][1]))))+
      temp[0]));
    temp[0] = ((((.0150652581855386*fstareq[12][2])+(.185436609363333*
      fstareq[12][0]))+(((.0809090128117004*utk[3][0])-(.0404550064059294*
      utk[3][1]))-(.995900157697815*utk[3][2])))+(((fstareq[14][2]*
      Vpk[12][14][2])+((fstareq[14][0]*Vpk[12][14][0])+(fstareq[14][1]*
      Vpk[12][14][1])))-((utk[4][2]*Wpk[12][14][2])+((utk[4][0]*Wpk[12][14][0])+
      (utk[4][1]*Wpk[12][14][1])))));
    tau[12] = (utau[12]-((((fstareq[15][2]*Vpk[12][15][2])+((fstareq[15][0]*
      Vpk[12][15][0])+(fstareq[15][1]*Vpk[12][15][1])))-((utk[5][2]*
      Wpk[12][15][2])+((utk[5][0]*Wpk[12][15][0])+(utk[5][1]*Wpk[12][15][1]))))+
      temp[0]));
    tau[13] = (utau[13]-((((fstareq[14][2]*Vpk[13][14][2])+((fstareq[14][0]*
      Vpk[13][14][0])+(fstareq[14][1]*Vpk[13][14][1])))-((utk[4][2]*
      Wpk[13][14][2])+((utk[4][0]*Wpk[13][14][0])+(utk[4][1]*Wpk[13][14][1]))))+
      (((fstareq[15][2]*Vpk[13][15][2])+((fstareq[15][0]*Vpk[13][15][0])+(
      fstareq[15][1]*Vpk[13][15][1])))-((utk[5][2]*Wpk[13][15][2])+((utk[5][0]*
      Wpk[13][15][0])+(utk[5][1]*Wpk[13][15][1]))))));
    tau[14] = (utau[14]-((((.0542579897533796*utk[4][2])-((.57725989098448*
      utk[4][1])+(.814755846133373*utk[4][0])))+(((.000411457536296252*
      fstareq[14][0])-(.00646090297985859*fstareq[14][1]))-(.0625600530375351*
      fstareq[14][2])))+(((fstareq[15][2]*Vpk[14][15][2])+((fstareq[15][0]*
      Vpk[14][15][0])+(fstareq[15][1]*Vpk[14][15][1])))-((utk[5][2]*
      Wpk[14][15][2])+((utk[5][0]*Wpk[14][15][0])+(utk[5][1]*Wpk[14][15][1])))))
      );
    tau[15] = (utau[15]-(((.469471734868729*utk[5][0])-(.882947501360837*
      utk[5][2]))+(((.02617891313962*fstareq[15][1])-(.0163345287751755*
      fstareq[15][0]))-(.00868522709507149*fstareq[15][2]))));
    temp[0] = ((((fstareq[18][2]*Vpk[16][18][2])+((.1715*(fstareq[18][0]*
      Wpk[16][18][2]))-(.002*(fstareq[18][1]*Wpk[16][18][2]))))+(((utk[6][1]*s17
      )-(utk[6][0]*Wpk[16][18][0]))-(utk[6][2]*Wpk[16][18][2])))+(((
      fstareq[19][2]*Vpk[16][19][2])+((fstareq[19][0]*Vpk[16][19][0])+(
      fstareq[19][1]*Vpk[16][19][1])))-((utk[7][2]*Wpk[16][19][2])+((utk[7][0]*
      Wpk[16][19][0])+(utk[7][1]*Wpk[16][19][1])))));
    tau[16] = (utau[16]-((((fstareq[22][2]*Vpk[16][22][2])+((fstareq[22][0]*
      Vpk[16][22][0])+(fstareq[22][1]*Vpk[16][22][1])))-((utk[9][2]*
      Wpk[16][22][2])+((utk[9][0]*Wpk[16][22][0])+(utk[9][1]*Wpk[16][22][1]))))+
      ((((fstareq[21][2]*Vpk[16][21][2])+((fstareq[21][0]*Vpk[16][21][0])+(
      fstareq[21][1]*Vpk[16][21][1])))-((utk[8][2]*Wpk[16][21][2])+((utk[8][0]*
      Wpk[16][21][0])+(utk[8][1]*Wpk[16][21][1]))))+temp[0])));
    temp[0] = ((((.1715*(fstareq[18][2]*c18))+((.1715*(fstareq[18][0]*s18))-(
      .002*(fstareq[18][1]*s18))))+((utk[6][0]*c18)-(utk[6][2]*s18)))+(((
      fstareq[19][2]*Vpk[17][19][2])+((fstareq[19][0]*Vpk[17][19][0])+(
      fstareq[19][1]*Vpk[17][19][1])))-((utk[7][2]*Wpk[17][19][2])+((utk[7][0]*
      Wpk[17][19][0])+(utk[7][1]*Wpk[17][19][1])))));
    tau[17] = (utau[17]-((((fstareq[22][2]*Vpk[17][22][2])+((fstareq[22][0]*
      Vpk[17][22][0])+(fstareq[22][1]*Vpk[17][22][1])))-((utk[9][2]*
      Wpk[17][22][2])+((utk[9][0]*Wpk[17][22][0])+(utk[9][1]*Wpk[17][22][1]))))+
      ((((fstareq[21][2]*Vpk[17][21][2])+((fstareq[21][0]*Vpk[17][21][0])+(
      fstareq[21][1]*Vpk[17][21][1])))-((utk[8][2]*Wpk[17][21][2])+((utk[8][0]*
      Wpk[17][21][0])+(utk[8][1]*Wpk[17][21][1]))))+temp[0])));
    temp[0] = (((utk[6][1]-(.002*fstareq[18][2]))+(((Cik[19][1][2]*utk[7][2])+((
      Cik[19][1][0]*utk[7][0])+(Cik[19][1][1]*utk[7][1])))+((fstareq[19][2]*
      Vpk[18][19][2])+((.0013*(Cik[19][2][1]*fstareq[19][1]))+(fstareq[19][0]*
      Vpk[18][19][0])))))+(((fstareq[21][2]*Vpk[18][21][2])+((fstareq[21][0]*
      Vpk[18][21][0])+(fstareq[21][1]*Vpk[18][21][1])))-((utk[8][2]*
      Wpk[18][21][2])+((utk[8][0]*Wpk[18][21][0])+(utk[8][1]*Wpk[18][21][1])))))
      ;
    tau[18] = (utau[18]-((((fstareq[22][2]*Vpk[18][22][2])+((fstareq[22][0]*
      Vpk[18][22][0])+(fstareq[22][1]*Vpk[18][22][1])))-((utk[9][2]*
      Wpk[18][22][2])+((utk[9][0]*Wpk[18][22][0])+(utk[9][1]*Wpk[18][22][1]))))+
      temp[0]));
    temp[0] = ((((.185436609363333*fstareq[19][0])-(.0150652581855386*
      fstareq[19][2]))+(((.0404550064059294*utk[7][1])-(.0809090128117004*
      utk[7][0]))-(.995900157697815*utk[7][2])))+(((fstareq[21][2]*
      Vpk[19][21][2])+((fstareq[21][0]*Vpk[19][21][0])+(fstareq[21][1]*
      Vpk[19][21][1])))-((utk[8][2]*Wpk[19][21][2])+((utk[8][0]*Wpk[19][21][0])+
      (utk[8][1]*Wpk[19][21][1])))));
    tau[19] = (utau[19]-((((fstareq[22][2]*Vpk[19][22][2])+((fstareq[22][0]*
      Vpk[19][22][0])+(fstareq[22][1]*Vpk[19][22][1])))-((utk[9][2]*
      Wpk[19][22][2])+((utk[9][0]*Wpk[19][22][0])+(utk[9][1]*Wpk[19][22][1]))))+
      temp[0]));
    tau[20] = (utau[20]-((((fstareq[21][2]*Vpk[20][21][2])+((fstareq[21][0]*
      Vpk[20][21][0])+(fstareq[21][1]*Vpk[20][21][1])))-((utk[8][2]*
      Wpk[20][21][2])+((utk[8][0]*Wpk[20][21][0])+(utk[8][1]*Wpk[20][21][1]))))+
      (((fstareq[22][2]*Vpk[20][22][2])+((fstareq[22][0]*Vpk[20][22][0])+(
      fstareq[22][1]*Vpk[20][22][1])))-((utk[9][2]*Wpk[20][22][2])+((utk[9][0]*
      Wpk[20][22][0])+(utk[9][1]*Wpk[20][22][1]))))));
    tau[21] = (utau[21]-((((.0542579897533796*utk[8][2])+((.57725989098448*
      utk[8][1])+(.814755846133373*utk[8][0])))+((.0625600530375351*
      fstareq[21][2])+((.000411457536296252*fstareq[21][0])-(.00646090297985859*
      fstareq[21][1]))))+(((fstareq[22][2]*Vpk[21][22][2])+((fstareq[22][0]*
      Vpk[21][22][0])+(fstareq[22][1]*Vpk[21][22][1])))-((utk[9][2]*
      Wpk[21][22][2])+((utk[9][0]*Wpk[21][22][0])+(utk[9][1]*Wpk[21][22][1])))))
      );
    tau[22] = (utau[22]-(((.00868522709507149*fstareq[22][2])+((.02617891313962*
      fstareq[22][1])-(.0163345287751755*fstareq[22][0])))-((.469471734868729*
      utk[9][0])+(.882947501360837*utk[9][2]))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.16 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  550 adds/subtracts/negates
                    530 multiplies
                      0 divides
                     79 assignments
*/
}

sdfulltrq(udotin,multin,trqout)
    double udotin[23],multin[1],trqout[23];
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[23][3],tstarr[23][3],Otkr[23][3],Atir[23][3],Atkr[23][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[6][0] = ((u[6]*wk[6][1])+((udotin[3]*c6)+(udotin[4]*s6)));
    Otkr[6][1] = (((udotin[4]*c6)-(udotin[3]*s6))-(u[6]*wk[6][0]));
    Otkr[6][2] = (udotin[5]+udotin[6]);
    Otkr[7][0] = (Otkr[6][0]+udotin[7]);
    Otkr[7][1] = ((u[7]*wk[7][2])+((Otkr[6][1]*c7)+(Otkr[6][2]*s7)));
    Otkr[7][2] = (((Otkr[6][2]*c7)-(Otkr[6][1]*s7))-(u[7]*wk[7][1]));
    Otkr[8][0] = (((Otkr[7][0]*c8)-(Otkr[7][2]*s8))-(u[8]*wk[8][2]));
    Otkr[8][1] = (Otkr[7][1]+udotin[8]);
    Otkr[8][2] = ((u[8]*wk[8][0])+((Otkr[7][0]*s8)+(Otkr[7][2]*c8)));
    Otkr[9][0] = ((u[9]*wk[9][1])+((udotin[3]*c9)+(udotin[4]*s9)));
    Otkr[9][1] = (((udotin[4]*c9)-(udotin[3]*s9))-(u[9]*wk[9][0]));
    Otkr[9][2] = (udotin[5]+udotin[9]);
    Otkr[10][0] = (Otkr[9][0]+udotin[10]);
    Otkr[10][1] = ((u[10]*wk[10][2])+((Otkr[9][1]*c10)+(Otkr[9][2]*s10)));
    Otkr[10][2] = (((Otkr[9][2]*c10)-(Otkr[9][1]*s10))-(u[10]*wk[10][1]));
    Otkr[11][0] = (((Otkr[10][0]*c11)-(Otkr[10][2]*s11))-(u[11]*wk[11][2]));
    Otkr[11][1] = (Otkr[10][1]+udotin[11]);
    Otkr[11][2] = ((u[11]*wk[11][0])+((Otkr[10][0]*s11)+(Otkr[10][2]*c11)));
    Otkr[12][0] = (((Cik[12][2][0]*Otkr[11][2])+((Cik[12][0][0]*Otkr[11][0])+(
      Cik[12][1][0]*Otkr[11][1])))+(((.995900157697815*(u[12]*wk[12][1]))-(
      .0404550064059294*(u[12]*wk[12][2])))-(.0809090128117004*udotin[12])));
    Otkr[12][1] = (((.0404550064059294*udotin[12])-((.0809090128117004*(u[12]*
      wk[12][2]))+(.995900157697815*(u[12]*wk[12][0]))))+((Cik[12][2][1]*
      Otkr[11][2])+((Cik[12][0][1]*Otkr[11][0])+(Cik[12][1][1]*Otkr[11][1]))));
    Otkr[12][2] = (((.995900157697815*udotin[12])+((.0404550064059294*(u[12]*
      wk[12][0]))+(.0809090128117004*(u[12]*wk[12][1]))))+((Cik[12][2][2]*
      Otkr[11][2])+((Cik[12][0][2]*Otkr[11][0])+(Cik[12][1][2]*Otkr[11][1]))));
    Otkr[13][0] = (((Cik[13][2][0]*Otkr[12][2])+((Cik[13][0][0]*Otkr[12][0])+(
      Cik[13][1][0]*Otkr[12][1])))+(((.0372090059839342*(u[13]*wk[13][2]))+(
      .995922160163717*(u[13]*wk[13][1])))-(.0821860132171146*udotin[13])));
    Otkr[13][1] = (((Cik[13][2][1]*Otkr[12][2])+((Cik[13][0][1]*Otkr[12][0])+(
      Cik[13][1][1]*Otkr[12][1])))-((.0372090059839342*udotin[13])+((
      .0821860132171146*(u[13]*wk[13][2]))+(.995922160163717*(u[13]*wk[13][0])))
      ));
    Otkr[13][2] = (((.995922160163717*udotin[13])+((.0821860132171146*(u[13]*
      wk[13][1]))-(.0372090059839342*(u[13]*wk[13][0]))))+((Cik[13][2][2]*
      Otkr[12][2])+((Cik[13][0][2]*Otkr[12][0])+(Cik[13][1][2]*Otkr[12][1]))));
    Otkr[14][0] = (((.814755846133373*udotin[14])-((.0542579897533796*(u[14]*
      wk[14][1]))+(.57725989098448*(u[14]*wk[14][2]))))+((Cik[14][2][0]*
      Otkr[13][2])+((Cik[14][0][0]*Otkr[13][0])+(Cik[14][1][0]*Otkr[13][1]))));
    Otkr[14][1] = (((.57725989098448*udotin[14])+((.0542579897533796*(u[14]*
      wk[14][0]))+(.814755846133373*(u[14]*wk[14][2]))))+((Cik[14][2][1]*
      Otkr[13][2])+((Cik[14][0][1]*Otkr[13][0])+(Cik[14][1][1]*Otkr[13][1]))));
    Otkr[14][2] = (((Cik[14][2][2]*Otkr[13][2])+((Cik[14][0][2]*Otkr[13][0])+(
      Cik[14][1][2]*Otkr[13][1])))+(((.57725989098448*(u[14]*wk[14][0]))-(
      .814755846133373*(u[14]*wk[14][1])))-(.0542579897533796*udotin[14])));
    Otkr[15][0] = (((.882947501360837*(u[15]*wk[15][1]))-(.469471734868729*
      udotin[15]))+((Cik[15][2][0]*Otkr[14][2])+((.882947501360837*(Otkr[14][1]*
      s15))+(Cik[15][0][0]*Otkr[14][0]))));
    Otkr[15][1] = ((((Otkr[14][1]*c15)-(.882947501360837*(Otkr[14][0]*s15)))-(
      .469471734868729*(Otkr[14][2]*s15)))-((.469471734868729*(u[15]*wk[15][2]))
      +(.882947501360837*(u[15]*wk[15][0]))));
    Otkr[15][2] = (((.469471734868729*(u[15]*wk[15][1]))+(.882947501360837*
      udotin[15]))+((Cik[15][2][2]*Otkr[14][2])+((.469471734868729*(Otkr[14][1]*
      s15))+(Cik[15][0][2]*Otkr[14][0]))));
    Otkr[16][0] = ((u[16]*wk[16][1])+((udotin[3]*c16)+(udotin[4]*s16)));
    Otkr[16][1] = (((udotin[4]*c16)-(udotin[3]*s16))-(u[16]*wk[16][0]));
    Otkr[16][2] = (udotin[5]+udotin[16]);
    Otkr[17][0] = (Otkr[16][0]-udotin[17]);
    Otkr[17][1] = (((Otkr[16][1]*c17)-(Otkr[16][2]*s17))-(u[17]*wk[17][2]));
    Otkr[17][2] = ((u[17]*wk[17][1])+((Otkr[16][1]*s17)+(Otkr[16][2]*c17)));
    Otkr[18][0] = ((u[18]*wk[18][2])+((Otkr[17][0]*c18)+(Otkr[17][2]*s18)));
    Otkr[18][1] = (Otkr[17][1]-udotin[18]);
    Otkr[18][2] = (((Otkr[17][2]*c18)-(Otkr[17][0]*s18))-(u[18]*wk[18][0]));
    Otkr[19][0] = (((.0809090128117004*udotin[19])+((.0404550064059294*(u[19]*
      wk[19][2]))+(.995900157697815*(u[19]*wk[19][1]))))+((Cik[19][2][0]*
      Otkr[18][2])+((Cik[19][0][0]*Otkr[18][0])+(Cik[19][1][0]*Otkr[18][1]))));
    Otkr[19][1] = (((Cik[19][2][1]*Otkr[18][2])+((Cik[19][0][1]*Otkr[18][0])+(
      Cik[19][1][1]*Otkr[18][1])))+(((.0809090128117004*(u[19]*wk[19][2]))-(
      .995900157697815*(u[19]*wk[19][0])))-(.0404550064059294*udotin[19])));
    Otkr[19][2] = (((.995900157697815*udotin[19])-((.0404550064059294*(u[19]*
      wk[19][0]))+(.0809090128117004*(u[19]*wk[19][1]))))+((Cik[19][2][2]*
      Otkr[18][2])+((Cik[19][0][2]*Otkr[18][0])+(Cik[19][1][2]*Otkr[18][1]))));
    Otkr[20][0] = (((.0821860132171146*udotin[20])+((.995922160163717*(u[20]*
      wk[20][1]))-(.0372090059839342*(u[20]*wk[20][2]))))+((Cik[20][2][0]*
      Otkr[19][2])+((Cik[20][0][0]*Otkr[19][0])+(Cik[20][1][0]*Otkr[19][1]))));
    Otkr[20][1] = (((.0372090059839342*udotin[20])+((.0821860132171146*(u[20]*
      wk[20][2]))-(.995922160163717*(u[20]*wk[20][0]))))+((Cik[20][2][1]*
      Otkr[19][2])+((Cik[20][0][1]*Otkr[19][0])+(Cik[20][1][1]*Otkr[19][1]))));
    Otkr[20][2] = (((.995922160163717*udotin[20])+((.0372090059839342*(u[20]*
      wk[20][0]))-(.0821860132171146*(u[20]*wk[20][1]))))+((Cik[20][2][2]*
      Otkr[19][2])+((Cik[20][0][2]*Otkr[19][0])+(Cik[20][1][2]*Otkr[19][1]))));
    Otkr[21][0] = (((Cik[21][2][0]*Otkr[20][2])+((Cik[21][0][0]*Otkr[20][0])+(
      Cik[21][1][0]*Otkr[20][1])))+(((.57725989098448*(u[21]*wk[21][2]))-(
      .0542579897533796*(u[21]*wk[21][1])))-(.814755846133373*udotin[21])));
    Otkr[21][1] = (((Cik[21][2][1]*Otkr[20][2])+((Cik[21][0][1]*Otkr[20][0])+(
      Cik[21][1][1]*Otkr[20][1])))+(((.0542579897533796*(u[21]*wk[21][0]))-(
      .814755846133373*(u[21]*wk[21][2])))-(.57725989098448*udotin[21])));
    Otkr[21][2] = (((Cik[21][2][2]*Otkr[20][2])+((Cik[21][0][2]*Otkr[20][0])+(
      Cik[21][1][2]*Otkr[20][1])))+(((.814755846133373*(u[21]*wk[21][1]))-(
      .57725989098448*(u[21]*wk[21][0])))-(.0542579897533796*udotin[21])));
    Otkr[22][0] = (((.469471734868729*udotin[22])+(.882947501360837*(u[22]*
      wk[22][1])))+((Cik[22][2][0]*Otkr[21][2])+((.882947501360837*(Otkr[21][1]*
      s22))+(Cik[22][0][0]*Otkr[21][0]))));
    Otkr[22][1] = (((.469471734868729*(Otkr[21][2]*s22))+((Otkr[21][1]*c22)-(
      .882947501360837*(Otkr[21][0]*s22))))+((.469471734868729*(u[22]*wk[22][2])
      )-(.882947501360837*(u[22]*wk[22][0]))));
    Otkr[22][2] = (((.882947501360837*udotin[22])-(.469471734868729*(u[22]*
      wk[22][1])))+((Cik[22][2][2]*Otkr[21][2])+((Cik[22][0][2]*Otkr[21][0])-(
      .469471734868729*(Otkr[21][1]*s22)))));
    Atkr[3][0] = ((Cik[3][2][0]*udotin[2])+((Cik[3][0][0]*udotin[0])+(
      Cik[3][1][0]*udotin[1])));
    Atkr[3][1] = ((Cik[3][2][1]*udotin[2])+((Cik[3][0][1]*udotin[0])+(
      Cik[3][1][1]*udotin[1])));
    Atkr[3][2] = ((Cik[3][2][2]*udotin[2])+((Cik[3][0][2]*udotin[0])+(
      Cik[3][1][2]*udotin[1])));
    Atir[6][0] = (Atkr[3][0]+(.127*((u[3]*u[4])-udotin[5])));
    Atir[6][1] = (Atkr[3][1]-(.127*((u[3]*u[3])+(u[5]*u[5]))));
    Atir[6][2] = (Atkr[3][2]+(.127*(udotin[3]+(u[4]*u[5]))));
    Atkr[6][0] = ((Atir[6][0]*c6)+(Atir[6][1]*s6));
    Atkr[6][1] = ((Atir[6][1]*c6)-(Atir[6][0]*s6));
    Atkr[7][1] = ((Atir[6][2]*s7)+(Atkr[6][1]*c7));
    Atkr[7][2] = ((Atir[6][2]*c7)-(Atkr[6][1]*s7));
    Atkr[8][0] = ((.3202*((wk[8][0]*wk[8][1])-Otkr[8][2]))+((Atkr[6][0]*c8)-(
      Atkr[7][2]*s8)));
    Atkr[8][1] = (Atkr[7][1]-(.3202*((wk[8][0]*wk[8][0])+(wk[8][2]*wk[8][2]))));
    Atkr[8][2] = ((.3202*(Otkr[8][0]+(wk[8][1]*wk[8][2])))+((Atkr[6][0]*s8)+(
      Atkr[7][2]*c8)));
    Atir[9][0] = (Atkr[3][0]+(((.07*udotin[5])+(.0935*udotin[4]))+((.0935*(u[3]*
      u[5]))-(.07*(u[3]*u[4])))));
    Atir[9][1] = (Atkr[3][1]+(((.07*(u[3]*u[3]))+(u[5]*Wirk[9][0]))-(.0935*
      udotin[3])));
    Atir[9][2] = (Atkr[3][2]-((.07*udotin[3])+((.0935*(u[3]*u[3]))+(u[4]*
      Wirk[9][0]))));
    Atkr[9][0] = ((Atir[9][0]*c9)+(Atir[9][1]*s9));
    Atkr[9][1] = ((Atir[9][1]*c9)-(Atir[9][0]*s9));
    Atkr[10][1] = ((Atir[9][2]*s10)+(Atkr[9][1]*c10));
    Atkr[10][2] = ((Atir[9][2]*c10)-(Atkr[9][1]*s10));
    Atkr[11][0] = (((.1715*Otkr[11][2])+((.002*(wk[11][2]*wk[11][2]))+(wk[11][1]
      *Wkrpk[11][2])))+((Atkr[9][0]*c11)-(Atkr[10][2]*s11)));
    Atkr[11][1] = (Atkr[10][1]+(((.1715*(wk[11][2]*wk[11][2]))-(wk[11][0]*
      Wkrpk[11][2]))-(.002*Otkr[11][2])));
    Atkr[11][2] = (((Atkr[9][0]*s11)+(Atkr[10][2]*c11))+(((.002*Otkr[11][1])-(
      .1715*Otkr[11][0]))-((.002*(wk[11][0]*wk[11][2]))+(.1715*(wk[11][1]*
      wk[11][2])))));
    Atir[12][0] = (Atkr[11][0]+((.2294*Otkr[11][2])+((Wirk[12][2]*wk[11][1])-(
      .0033*(wk[11][2]*wk[11][2])))));
    Atir[12][1] = (Atkr[11][1]+((.0033*Otkr[11][2])+((.2294*(wk[11][2]*wk[11][2]
      ))-(Wirk[12][2]*wk[11][0]))));
    Atir[12][2] = (Atkr[11][2]+(((.0033*(wk[11][0]*wk[11][2]))-(.2294*(wk[11][1]
      *wk[11][2])))-((.0033*Otkr[11][1])+(.2294*Otkr[11][0]))));
    Atkr[12][0] = ((.1862*(Otkr[12][2]-(wk[12][0]*wk[12][1])))+((Atir[12][2]*
      Cik[12][2][0])+((Atir[12][0]*Cik[12][0][0])+(Atir[12][1]*Cik[12][1][0]))))
      ;
    Atkr[12][1] = ((.1862*((wk[12][0]*wk[12][0])+(wk[12][2]*wk[12][2])))+((
      Atir[12][2]*Cik[12][2][1])+((Atir[12][0]*Cik[12][0][1])+(Atir[12][1]*
      Cik[12][1][1]))));
    Atkr[12][2] = (((Atir[12][2]*Cik[12][2][2])+((Atir[12][0]*Cik[12][0][2])+(
      Atir[12][1]*Cik[12][1][2])))-(.1862*(Otkr[12][0]+(wk[12][1]*wk[12][2]))));
    Atir[13][0] = (Atkr[12][0]+(.2438*(Otkr[12][2]-(wk[12][0]*wk[12][1]))));
    Atir[13][1] = (Atkr[12][1]+(.2438*((wk[12][0]*wk[12][0])+(wk[12][2]*
      wk[12][2]))));
    Atir[13][2] = (Atkr[12][2]-(.2438*(Otkr[12][0]+(wk[12][1]*wk[12][2]))));
    Atkr[13][0] = ((Atir[13][2]*Cik[13][2][0])+((Atir[13][0]*Cik[13][0][0])+(
      Atir[13][1]*Cik[13][1][0])));
    Atkr[13][1] = ((Atir[13][2]*Cik[13][2][1])+((Atir[13][0]*Cik[13][0][1])+(
      Atir[13][1]*Cik[13][1][1])));
    Atkr[13][2] = ((Atir[13][2]*Cik[13][2][2])+((Atir[13][0]*Cik[13][0][2])+(
      Atir[13][1]*Cik[13][1][2])));
    Atkr[14][0] = (((Atkr[13][2]*Cik[14][2][0])+((Atkr[13][0]*Cik[14][0][0])+(
      Atkr[13][1]*Cik[14][1][0])))+(((.005539*Otkr[14][1])+(.051347*Otkr[14][2])
      )+((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*Wkrpk[14][1]))));
    Atkr[14][1] = (((Atkr[13][2]*Cik[14][2][1])+((Atkr[13][0]*Cik[14][0][1])+(
      Atkr[13][1]*Cik[14][1][1])))+(((.035902*Otkr[14][2])-(.005539*Otkr[14][0])
      )+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*Wkrpk[14][2]))));
    Atkr[14][2] = (((Atkr[13][2]*Cik[14][2][2])+((Atkr[13][0]*Cik[14][0][2])+(
      Atkr[13][1]*Cik[14][1][2])))+(((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*
      Wkrpk[14][0]))-((.035902*Otkr[14][1])+(.051347*Otkr[14][0]))));
    Atir[15][0] = (Atkr[14][0]+(((.018078*Otkr[14][1])+(.038*Otkr[14][2]))+((
      Wirk[15][2]*wk[14][1])-(Wirk[15][1]*wk[14][2]))));
    Atir[15][1] = (Atkr[14][1]+(((.098032*Otkr[14][2])-(.018078*Otkr[14][0]))+((
      Wirk[15][0]*wk[14][2])-(Wirk[15][2]*wk[14][0]))));
    Atir[15][2] = (Atkr[14][2]+(((Wirk[15][1]*wk[14][0])-(Wirk[15][0]*wk[14][1])
      )-((.038*Otkr[14][0])+(.098032*Otkr[14][1]))));
    Atkr[15][0] = (((Atir[15][2]*Cik[15][2][0])+((.882947501360837*(Atir[15][1]*
      s15))+(Atir[15][0]*Cik[15][0][0])))+(((.005139*Otkr[15][1])-(.0185*
      Otkr[15][2]))+((wk[15][1]*Wkrpk[15][2])-(wk[15][2]*Wkrpk[15][1]))));
    Atkr[15][1] = ((((.026917*Otkr[15][2])-(.005139*Otkr[15][0]))+((wk[15][2]*
      Wkrpk[15][0])-(wk[15][0]*Wkrpk[15][2])))+(((Atir[15][1]*c15)-(
      .882947501360837*(Atir[15][0]*s15)))-(.469471734868729*(Atir[15][2]*s15)))
      );
    Atkr[15][2] = (((Atir[15][2]*Cik[15][2][2])+((.469471734868729*(Atir[15][1]*
      s15))+(Atir[15][0]*Cik[15][0][2])))+(((.0185*Otkr[15][0])-(.026917*
      Otkr[15][1]))+((wk[15][0]*Wkrpk[15][1])-(wk[15][1]*Wkrpk[15][0]))));
    Atir[16][0] = (Atkr[3][0]+(((.07*udotin[5])-(.0935*udotin[4]))-((.07*(u[3]*
      u[4]))+(.0935*(u[3]*u[5])))));
    Atir[16][1] = (Atkr[3][1]+((.0935*udotin[3])+((.07*(u[3]*u[3]))+(u[5]*
      Wirk[16][0]))));
    Atir[16][2] = (Atkr[3][2]+(((.0935*(u[3]*u[3]))-(u[4]*Wirk[16][0]))-(.07*
      udotin[3])));
    Atkr[16][0] = ((Atir[16][0]*c16)+(Atir[16][1]*s16));
    Atkr[16][1] = ((Atir[16][1]*c16)-(Atir[16][0]*s16));
    Atkr[17][1] = ((Atkr[16][1]*c17)-(Atir[16][2]*s17));
    Atkr[17][2] = ((Atir[16][2]*c17)+(Atkr[16][1]*s17));
    Atkr[18][0] = (((.1715*Otkr[18][2])+((.002*(wk[18][2]*wk[18][2]))+(wk[18][1]
      *Wkrpk[18][2])))+((Atkr[16][0]*c18)+(Atkr[17][2]*s18)));
    Atkr[18][1] = (Atkr[17][1]+(((.1715*(wk[18][2]*wk[18][2]))-(wk[18][0]*
      Wkrpk[18][2]))-(.002*Otkr[18][2])));
    Atkr[18][2] = (((Atkr[17][2]*c18)-(Atkr[16][0]*s18))+(((.002*Otkr[18][1])-(
      .1715*Otkr[18][0]))-((.002*(wk[18][0]*wk[18][2]))+(.1715*(wk[18][1]*
      wk[18][2])))));
    Atir[19][0] = (Atkr[18][0]+((.2294*Otkr[18][2])+((Wirk[19][2]*wk[18][1])-(
      .0033*(wk[18][2]*wk[18][2])))));
    Atir[19][1] = (Atkr[18][1]+((.0033*Otkr[18][2])+((.2294*(wk[18][2]*wk[18][2]
      ))-(Wirk[19][2]*wk[18][0]))));
    Atir[19][2] = (Atkr[18][2]+(((.0033*(wk[18][0]*wk[18][2]))-(.2294*(wk[18][1]
      *wk[18][2])))-((.0033*Otkr[18][1])+(.2294*Otkr[18][0]))));
    Atkr[19][0] = ((.1862*(Otkr[19][2]-(wk[19][0]*wk[19][1])))+((Atir[19][2]*
      Cik[19][2][0])+((Atir[19][0]*Cik[19][0][0])+(Atir[19][1]*Cik[19][1][0]))))
      ;
    Atkr[19][1] = ((.1862*((wk[19][0]*wk[19][0])+(wk[19][2]*wk[19][2])))+((
      Atir[19][2]*Cik[19][2][1])+((Atir[19][0]*Cik[19][0][1])+(Atir[19][1]*
      Cik[19][1][1]))));
    Atkr[19][2] = (((Atir[19][2]*Cik[19][2][2])+((Atir[19][0]*Cik[19][0][2])+(
      Atir[19][1]*Cik[19][1][2])))-(.1862*(Otkr[19][0]+(wk[19][1]*wk[19][2]))));
    Atir[20][0] = (Atkr[19][0]+(.2438*(Otkr[19][2]-(wk[19][0]*wk[19][1]))));
    Atir[20][1] = (Atkr[19][1]+(.2438*((wk[19][0]*wk[19][0])+(wk[19][2]*
      wk[19][2]))));
    Atir[20][2] = (Atkr[19][2]-(.2438*(Otkr[19][0]+(wk[19][1]*wk[19][2]))));
    Atkr[20][0] = ((Atir[20][2]*Cik[20][2][0])+((Atir[20][0]*Cik[20][0][0])+(
      Atir[20][1]*Cik[20][1][0])));
    Atkr[20][1] = ((Atir[20][2]*Cik[20][2][1])+((Atir[20][0]*Cik[20][0][1])+(
      Atir[20][1]*Cik[20][1][1])));
    Atkr[20][2] = ((Atir[20][2]*Cik[20][2][2])+((Atir[20][0]*Cik[20][0][2])+(
      Atir[20][1]*Cik[20][1][2])));
    Atkr[21][0] = (((Atkr[20][2]*Cik[21][2][0])+((Atkr[20][0]*Cik[21][0][0])+(
      Atkr[20][1]*Cik[21][1][0])))+(((.051347*Otkr[21][2])-(.005539*Otkr[21][1])
      )+((wk[21][1]*Wkrpk[21][2])-(wk[21][2]*Wkrpk[21][1]))));
    Atkr[21][1] = (((Atkr[20][2]*Cik[21][2][1])+((Atkr[20][0]*Cik[21][0][1])+(
      Atkr[20][1]*Cik[21][1][1])))+(((.005539*Otkr[21][0])+(.035902*Otkr[21][2])
      )+((wk[21][2]*Wkrpk[21][0])-(wk[21][0]*Wkrpk[21][2]))));
    Atkr[21][2] = (((Atkr[20][2]*Cik[21][2][2])+((Atkr[20][0]*Cik[21][0][2])+(
      Atkr[20][1]*Cik[21][1][2])))+(((wk[21][0]*Wkrpk[21][1])-(wk[21][1]*
      Wkrpk[21][0]))-((.035902*Otkr[21][1])+(.051347*Otkr[21][0]))));
    Atir[22][0] = (Atkr[21][0]+(((.038*Otkr[21][2])-(.018078*Otkr[21][1]))+((
      Wirk[22][2]*wk[21][1])-(Wirk[22][1]*wk[21][2]))));
    Atir[22][1] = (Atkr[21][1]+(((.018078*Otkr[21][0])+(.098032*Otkr[21][2]))+((
      Wirk[22][0]*wk[21][2])-(Wirk[22][2]*wk[21][0]))));
    Atir[22][2] = (Atkr[21][2]+(((Wirk[22][1]*wk[21][0])-(Wirk[22][0]*wk[21][1])
      )-((.038*Otkr[21][0])+(.098032*Otkr[21][1]))));
    Atkr[22][0] = (((Atir[22][2]*Cik[22][2][0])+((.882947501360837*(Atir[22][1]*
      s22))+(Atir[22][0]*Cik[22][0][0])))+(((wk[22][1]*Wkrpk[22][2])-(wk[22][2]*
      Wkrpk[22][1]))-((.005139*Otkr[22][1])+(.0185*Otkr[22][2]))));
    Atkr[22][1] = (((.469471734868729*(Atir[22][2]*s22))+((Atir[22][1]*c22)-(
      .882947501360837*(Atir[22][0]*s22))))+(((.005139*Otkr[22][0])+(.026917*
      Otkr[22][2]))+((wk[22][2]*Wkrpk[22][0])-(wk[22][0]*Wkrpk[22][2]))));
    Atkr[22][2] = (((Atir[22][2]*Cik[22][2][2])+((Atir[22][0]*Cik[22][0][2])-(
      .469471734868729*(Atir[22][1]*s22))))+(((.0185*Otkr[22][0])-(.026917*
      Otkr[22][1]))+((wk[22][0]*Wkrpk[22][1])-(wk[22][1]*Wkrpk[22][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = (ufk[0][0]+(11.15*(gk[3][0]-Atkr[3][0])));
    fstarr[5][1] = (ufk[0][1]+(11.15*(gk[3][1]-Atkr[3][1])));
    fstarr[5][2] = (ufk[0][2]+(11.15*(gk[3][2]-Atkr[3][2])));
    fstarr[8][0] = (ufk[1][0]+(32.413*(gk[8][0]-Atkr[8][0])));
    fstarr[8][1] = (ufk[1][1]+(32.413*(gk[7][1]-Atkr[8][1])));
    fstarr[8][2] = (ufk[1][2]+(32.413*(gk[8][2]-Atkr[8][2])));
    fstarr[11][0] = (ufk[2][0]+(8.806*(gk[11][0]-Atkr[11][0])));
    fstarr[11][1] = (ufk[2][1]+(8.806*(gk[10][1]-Atkr[11][1])));
    fstarr[11][2] = (ufk[2][2]+(8.806*(gk[11][2]-Atkr[11][2])));
    fstarr[12][0] = (ufk[3][0]+(3.51*(gk[12][0]-Atkr[12][0])));
    fstarr[12][1] = (ufk[3][1]+(3.51*(gk[12][1]-Atkr[12][1])));
    fstarr[12][2] = (ufk[3][2]+(3.51*(gk[12][2]-Atkr[12][2])));
    fstarr[14][0] = (ufk[4][0]+(1.2*(gk[14][0]-Atkr[14][0])));
    fstarr[14][1] = (ufk[4][1]+(1.2*(gk[14][1]-Atkr[14][1])));
    fstarr[14][2] = (ufk[4][2]+(1.2*(gk[14][2]-Atkr[14][2])));
    fstarr[15][0] = (ufk[5][0]+(.205126*(gk[15][0]-Atkr[15][0])));
    fstarr[15][1] = (ufk[5][1]+(.205126*(gk[15][1]-Atkr[15][1])));
    fstarr[15][2] = (ufk[5][2]+(.205126*(gk[15][2]-Atkr[15][2])));
    fstarr[18][0] = (ufk[6][0]+(8.806*(gk[18][0]-Atkr[18][0])));
    fstarr[18][1] = (ufk[6][1]+(8.806*(gk[17][1]-Atkr[18][1])));
    fstarr[18][2] = (ufk[6][2]+(8.806*(gk[18][2]-Atkr[18][2])));
    fstarr[19][0] = (ufk[7][0]+(3.51*(gk[19][0]-Atkr[19][0])));
    fstarr[19][1] = (ufk[7][1]+(3.51*(gk[19][1]-Atkr[19][1])));
    fstarr[19][2] = (ufk[7][2]+(3.51*(gk[19][2]-Atkr[19][2])));
    fstarr[21][0] = (ufk[8][0]+(1.2*(gk[21][0]-Atkr[21][0])));
    fstarr[21][1] = (ufk[8][1]+(1.2*(gk[21][1]-Atkr[21][1])));
    fstarr[21][2] = (ufk[8][2]+(1.2*(gk[21][2]-Atkr[21][2])));
    fstarr[22][0] = (ufk[9][0]+(.205126*(gk[22][0]-Atkr[22][0])));
    fstarr[22][1] = (ufk[9][1]+(.205126*(gk[22][1]-Atkr[22][1])));
    fstarr[22][2] = (ufk[9][2]+(.205126*(gk[22][2]-Atkr[22][2])));
    tstarr[5][0] = (utk[0][0]-(WkIkWk[5][0]+(.0973*udotin[3])));
    tstarr[5][1] = (utk[0][1]-(WkIkWk[5][1]+(.0825*udotin[4])));
    tstarr[5][2] = (utk[0][2]-(WkIkWk[5][2]+(.0548*udotin[5])));
    tstarr[8][0] = (utk[1][0]-(WkIkWk[8][0]+(1.396*Otkr[8][0])));
    tstarr[8][1] = (utk[1][1]-(WkIkWk[8][1]+(.7153*Otkr[8][1])));
    tstarr[8][2] = (utk[1][2]-(WkIkWk[8][2]+(1.3552*Otkr[8][2])));
    tstarr[11][0] = (utk[2][0]-(WkIkWk[11][0]+(.1268*Otkr[11][0])));
    tstarr[11][1] = (utk[2][1]-(WkIkWk[11][1]+(.0332*Otkr[11][1])));
    tstarr[11][2] = (utk[2][2]-(WkIkWk[11][2]+(.1337*Otkr[11][2])));
    tstarr[12][0] = (utk[3][0]-(WkIkWk[12][0]+(.0477*Otkr[12][0])));
    tstarr[12][1] = (utk[3][1]-(WkIkWk[12][1]+(.0048*Otkr[12][1])));
    tstarr[12][2] = (utk[3][2]-(WkIkWk[12][2]+(.0484*Otkr[12][2])));
    tstarr[14][0] = (utk[4][0]-(WkIkWk[14][0]+(.001361*Otkr[14][0])));
    tstarr[14][1] = (utk[4][1]-(WkIkWk[14][1]+(.003709*Otkr[14][1])));
    tstarr[14][2] = (utk[4][2]-(WkIkWk[14][2]+(.003916*Otkr[14][2])));
    tstarr[15][0] = (utk[5][0]-(WkIkWk[15][0]+(.000117*Otkr[15][0])));
    tstarr[15][1] = (utk[5][1]-(WkIkWk[15][1]+(.000179*Otkr[15][1])));
    tstarr[15][2] = (utk[5][2]-(WkIkWk[15][2]+(.000119*Otkr[15][2])));
    tstarr[18][0] = (utk[6][0]-(WkIkWk[18][0]+(.1268*Otkr[18][0])));
    tstarr[18][1] = (utk[6][1]-(WkIkWk[18][1]+(.0332*Otkr[18][1])));
    tstarr[18][2] = (utk[6][2]-(WkIkWk[18][2]+(.1337*Otkr[18][2])));
    tstarr[19][0] = (utk[7][0]-(WkIkWk[19][0]+(.0477*Otkr[19][0])));
    tstarr[19][1] = (utk[7][1]-(WkIkWk[19][1]+(.0048*Otkr[19][1])));
    tstarr[19][2] = (utk[7][2]-(WkIkWk[19][2]+(.0484*Otkr[19][2])));
    tstarr[21][0] = (utk[8][0]-(WkIkWk[21][0]+(.001361*Otkr[21][0])));
    tstarr[21][1] = (utk[8][1]-(WkIkWk[21][1]+(.003709*Otkr[21][1])));
    tstarr[21][2] = (utk[8][2]-(WkIkWk[21][2]+(.003916*Otkr[21][2])));
    tstarr[22][0] = (utk[9][0]-(WkIkWk[22][0]+(.000117*Otkr[22][0])));
    tstarr[22][1] = (utk[9][1]-(WkIkWk[22][1]+(.000179*Otkr[22][1])));
    tstarr[22][2] = (utk[9][2]-(WkIkWk[22][2]+(.000119*Otkr[22][2])));
/*
Now calculate the torques
*/
    sddovpk();
    temp[0] = (((fstarr[12][2]*Vpk[0][12][2])+((fstarr[12][0]*Vpk[0][12][0])+(
      fstarr[12][1]*Vpk[0][12][1])))+(((fstarr[11][2]*Vpk[0][11][2])+((
      fstarr[11][0]*Vpk[0][11][0])+(fstarr[11][1]*Vpk[0][10][1])))+(((
      Cik[3][0][2]*fstarr[5][2])+((Cik[3][0][0]*fstarr[5][0])+(Cik[3][0][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[0][8][2])+((fstarr[8][0]*Vpk[0][8][0])+
      (fstarr[8][1]*Vpk[0][7][1]))))));
    temp[1] = (((fstarr[19][2]*Vpk[0][19][2])+((fstarr[19][0]*Vpk[0][19][0])+(
      fstarr[19][1]*Vpk[0][19][1])))+(((fstarr[18][2]*Vpk[0][18][2])+((
      fstarr[18][0]*Vpk[0][18][0])+(fstarr[18][1]*Vpk[0][17][1])))+(((
      fstarr[15][2]*Vpk[0][15][2])+((fstarr[15][0]*Vpk[0][15][0])+(fstarr[15][1]
      *Vpk[0][15][1])))+(((fstarr[14][2]*Vpk[0][14][2])+((fstarr[14][0]*
      Vpk[0][14][0])+(fstarr[14][1]*Vpk[0][14][1])))+temp[0]))));
    trqout[0] = -(utau[0]+(((fstarr[22][2]*Vpk[0][22][2])+((fstarr[22][0]*
      Vpk[0][22][0])+(fstarr[22][1]*Vpk[0][22][1])))+(((fstarr[21][2]*
      Vpk[0][21][2])+((fstarr[21][0]*Vpk[0][21][0])+(fstarr[21][1]*Vpk[0][21][1]
      )))+temp[1])));
    temp[0] = (((fstarr[12][2]*Vpk[1][12][2])+((fstarr[12][0]*Vpk[1][12][0])+(
      fstarr[12][1]*Vpk[1][12][1])))+(((fstarr[11][2]*Vpk[1][11][2])+((
      fstarr[11][0]*Vpk[1][11][0])+(fstarr[11][1]*Vpk[1][10][1])))+(((
      Cik[3][1][2]*fstarr[5][2])+((Cik[3][1][0]*fstarr[5][0])+(Cik[3][1][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[1][8][2])+((fstarr[8][0]*Vpk[1][8][0])+
      (fstarr[8][1]*Vpk[1][7][1]))))));
    temp[1] = (((fstarr[19][2]*Vpk[1][19][2])+((fstarr[19][0]*Vpk[1][19][0])+(
      fstarr[19][1]*Vpk[1][19][1])))+(((fstarr[18][2]*Vpk[1][18][2])+((
      fstarr[18][0]*Vpk[1][18][0])+(fstarr[18][1]*Vpk[1][17][1])))+(((
      fstarr[15][2]*Vpk[1][15][2])+((fstarr[15][0]*Vpk[1][15][0])+(fstarr[15][1]
      *Vpk[1][15][1])))+(((fstarr[14][2]*Vpk[1][14][2])+((fstarr[14][0]*
      Vpk[1][14][0])+(fstarr[14][1]*Vpk[1][14][1])))+temp[0]))));
    trqout[1] = -(utau[1]+(((fstarr[22][2]*Vpk[1][22][2])+((fstarr[22][0]*
      Vpk[1][22][0])+(fstarr[22][1]*Vpk[1][22][1])))+(((fstarr[21][2]*
      Vpk[1][21][2])+((fstarr[21][0]*Vpk[1][21][0])+(fstarr[21][1]*Vpk[1][21][1]
      )))+temp[1])));
    temp[0] = (((fstarr[12][2]*Vpk[2][12][2])+((fstarr[12][0]*Vpk[2][12][0])+(
      fstarr[12][1]*Vpk[2][12][1])))+(((fstarr[11][2]*Vpk[2][11][2])+((
      fstarr[11][0]*Vpk[2][11][0])+(fstarr[11][1]*Vpk[2][10][1])))+(((
      Cik[3][2][2]*fstarr[5][2])+((Cik[3][2][0]*fstarr[5][0])+(Cik[3][2][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[2][8][2])+((fstarr[8][0]*Vpk[2][8][0])+
      (fstarr[8][1]*Vpk[2][7][1]))))));
    temp[1] = (((fstarr[19][2]*Vpk[2][19][2])+((fstarr[19][0]*Vpk[2][19][0])+(
      fstarr[19][1]*Vpk[2][19][1])))+(((fstarr[18][2]*Vpk[2][18][2])+((
      fstarr[18][0]*Vpk[2][18][0])+(fstarr[18][1]*Vpk[2][17][1])))+(((
      fstarr[15][2]*Vpk[2][15][2])+((fstarr[15][0]*Vpk[2][15][0])+(fstarr[15][1]
      *Vpk[2][15][1])))+(((fstarr[14][2]*Vpk[2][14][2])+((fstarr[14][0]*
      Vpk[2][14][0])+(fstarr[14][1]*Vpk[2][14][1])))+temp[0]))));
    trqout[2] = -(utau[2]+(((fstarr[22][2]*Vpk[2][22][2])+((fstarr[22][0]*
      Vpk[2][22][0])+(fstarr[22][1]*Vpk[2][22][1])))+(((fstarr[21][2]*
      Vpk[2][21][2])+((fstarr[21][0]*Vpk[2][21][0])+(fstarr[21][1]*Vpk[2][21][1]
      )))+temp[1])));
    temp[0] = ((tstarr[5][0]+(((fstarr[8][2]*Vpk[3][8][2])+((.127*(fstarr[8][1]*
      s7))+(fstarr[8][0]*Vpk[3][8][0])))+((tstarr[8][2]*Wpk[3][8][2])+((
      tstarr[8][0]*Wpk[3][8][0])+(tstarr[8][1]*Wpk[3][7][1])))))+(((
      fstarr[11][2]*Vpk[3][11][2])+((fstarr[11][0]*Vpk[3][11][0])+(fstarr[11][1]
      *Vpk[3][11][1])))+((tstarr[11][2]*Wpk[3][11][2])+((tstarr[11][0]*
      Wpk[3][11][0])+(tstarr[11][1]*Wpk[3][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[3][14][2])+((fstarr[14][0]*Vpk[3][14][0])+(
      fstarr[14][1]*Vpk[3][14][1])))+((tstarr[14][2]*Wpk[3][14][2])+((
      tstarr[14][0]*Wpk[3][14][0])+(tstarr[14][1]*Wpk[3][14][1]))))+(temp[0]+(((
      fstarr[12][2]*Vpk[3][12][2])+((fstarr[12][0]*Vpk[3][12][0])+(fstarr[12][1]
      *Vpk[3][12][1])))+((tstarr[12][2]*Wpk[3][12][2])+((tstarr[12][0]*
      Wpk[3][12][0])+(tstarr[12][1]*Wpk[3][12][1]))))));
    temp[2] = ((((fstarr[18][2]*Vpk[3][18][2])+((fstarr[18][0]*Vpk[3][18][0])+(
      fstarr[18][1]*Vpk[3][18][1])))+((tstarr[18][2]*Wpk[3][18][2])+((
      tstarr[18][0]*Wpk[3][18][0])+(tstarr[18][1]*Wpk[3][17][1]))))+((((
      fstarr[15][2]*Vpk[3][15][2])+((fstarr[15][0]*Vpk[3][15][0])+(fstarr[15][1]
      *Vpk[3][15][1])))+((tstarr[15][2]*Wpk[3][15][2])+((tstarr[15][0]*
      Wpk[3][15][0])+(tstarr[15][1]*Wpk[3][15][1]))))+temp[1]));
    temp[3] = ((((fstarr[21][2]*Vpk[3][21][2])+((fstarr[21][0]*Vpk[3][21][0])+(
      fstarr[21][1]*Vpk[3][21][1])))+((tstarr[21][2]*Wpk[3][21][2])+((
      tstarr[21][0]*Wpk[3][21][0])+(tstarr[21][1]*Wpk[3][21][1]))))+((((
      fstarr[19][2]*Vpk[3][19][2])+((fstarr[19][0]*Vpk[3][19][0])+(fstarr[19][1]
      *Vpk[3][19][1])))+((tstarr[19][2]*Wpk[3][19][2])+((tstarr[19][0]*
      Wpk[3][19][0])+(tstarr[19][1]*Wpk[3][19][1]))))+temp[2]));
    trqout[3] = -(utau[3]+((((fstarr[22][2]*Vpk[3][22][2])+((fstarr[22][0]*
      Vpk[3][22][0])+(fstarr[22][1]*Vpk[3][22][1])))+((tstarr[22][2]*
      Wpk[3][22][2])+((tstarr[22][0]*Wpk[3][22][0])+(tstarr[22][1]*Wpk[3][22][1]
      ))))+temp[3]));
    temp[0] = ((tstarr[5][1]+((.3202*((fstarr[8][2]*Wpk[4][8][0])-(fstarr[8][0]*
      Wpk[4][8][2])))+((tstarr[8][2]*Wpk[4][8][2])+((tstarr[8][0]*Wpk[4][8][0])+
      (tstarr[8][1]*Wpk[4][7][1])))))+(((fstarr[11][2]*Vpk[4][11][2])+((
      fstarr[11][0]*Vpk[4][11][0])+(fstarr[11][1]*Vpk[4][11][1])))+((
      tstarr[11][2]*Wpk[4][11][2])+((tstarr[11][0]*Wpk[4][11][0])+(tstarr[11][1]
      *Wpk[4][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[4][14][2])+((fstarr[14][0]*Vpk[4][14][0])+(
      fstarr[14][1]*Vpk[4][14][1])))+((tstarr[14][2]*Wpk[4][14][2])+((
      tstarr[14][0]*Wpk[4][14][0])+(tstarr[14][1]*Wpk[4][14][1]))))+(temp[0]+(((
      fstarr[12][2]*Vpk[4][12][2])+((fstarr[12][0]*Vpk[4][12][0])+(fstarr[12][1]
      *Vpk[4][12][1])))+((tstarr[12][2]*Wpk[4][12][2])+((tstarr[12][0]*
      Wpk[4][12][0])+(tstarr[12][1]*Wpk[4][12][1]))))));
    temp[2] = ((((fstarr[18][2]*Vpk[4][18][2])+((fstarr[18][0]*Vpk[4][18][0])+(
      fstarr[18][1]*Vpk[4][18][1])))+((tstarr[18][2]*Wpk[4][18][2])+((
      tstarr[18][0]*Wpk[4][18][0])+(tstarr[18][1]*Wpk[4][17][1]))))+((((
      fstarr[15][2]*Vpk[4][15][2])+((fstarr[15][0]*Vpk[4][15][0])+(fstarr[15][1]
      *Vpk[4][15][1])))+((tstarr[15][2]*Wpk[4][15][2])+((tstarr[15][0]*
      Wpk[4][15][0])+(tstarr[15][1]*Wpk[4][15][1]))))+temp[1]));
    temp[3] = ((((fstarr[21][2]*Vpk[4][21][2])+((fstarr[21][0]*Vpk[4][21][0])+(
      fstarr[21][1]*Vpk[4][21][1])))+((tstarr[21][2]*Wpk[4][21][2])+((
      tstarr[21][0]*Wpk[4][21][0])+(tstarr[21][1]*Wpk[4][21][1]))))+((((
      fstarr[19][2]*Vpk[4][19][2])+((fstarr[19][0]*Vpk[4][19][0])+(fstarr[19][1]
      *Vpk[4][19][1])))+((tstarr[19][2]*Wpk[4][19][2])+((tstarr[19][0]*
      Wpk[4][19][0])+(tstarr[19][1]*Wpk[4][19][1]))))+temp[2]));
    trqout[4] = -(utau[4]+((((fstarr[22][2]*Vpk[4][22][2])+((fstarr[22][0]*
      Vpk[4][22][0])+(fstarr[22][1]*Vpk[4][22][1])))+((tstarr[22][2]*
      Wpk[4][22][2])+((tstarr[22][0]*Wpk[4][22][0])+(tstarr[22][1]*Wpk[4][22][1]
      ))))+temp[3]));
    temp[0] = ((tstarr[5][2]+(((fstarr[8][2]*Vpk[5][8][2])+((fstarr[8][0]*
      Vpk[5][8][0])+(fstarr[8][1]*Vpk[5][7][1])))+((tstarr[8][2]*Wpk[5][8][2])+(
      (tstarr[8][0]*Wpk[5][8][0])+(tstarr[8][1]*s7)))))+(((fstarr[11][2]*
      Vpk[5][11][2])+((fstarr[11][0]*Vpk[5][11][0])+(fstarr[11][1]*Vpk[5][11][1]
      )))+((tstarr[11][2]*Wpk[5][11][2])+((tstarr[11][0]*Wpk[5][11][0])+(
      tstarr[11][1]*s10)))));
    temp[1] = ((((fstarr[14][2]*Vpk[5][14][2])+((fstarr[14][0]*Vpk[5][14][0])+(
      fstarr[14][1]*Vpk[5][14][1])))+((tstarr[14][2]*Wpk[5][14][2])+((
      tstarr[14][0]*Wpk[5][14][0])+(tstarr[14][1]*Wpk[5][14][1]))))+(temp[0]+(((
      fstarr[12][2]*Vpk[5][12][2])+((fstarr[12][0]*Vpk[5][12][0])+(fstarr[12][1]
      *Vpk[5][12][1])))+((tstarr[12][2]*Wpk[5][12][2])+((tstarr[12][0]*
      Wpk[5][12][0])+(tstarr[12][1]*Wpk[5][12][1]))))));
    temp[2] = ((((fstarr[18][2]*Vpk[5][18][2])+((fstarr[18][0]*Vpk[5][18][0])+(
      fstarr[18][1]*Vpk[5][18][1])))+((tstarr[18][2]*Wpk[5][18][2])+((
      tstarr[18][0]*Wpk[5][18][0])-(tstarr[18][1]*s17))))+((((fstarr[15][2]*
      Vpk[5][15][2])+((fstarr[15][0]*Vpk[5][15][0])+(fstarr[15][1]*Vpk[5][15][1]
      )))+((tstarr[15][2]*Wpk[5][15][2])+((tstarr[15][0]*Wpk[5][15][0])+(
      tstarr[15][1]*Wpk[5][15][1]))))+temp[1]));
    temp[3] = ((((fstarr[21][2]*Vpk[5][21][2])+((fstarr[21][0]*Vpk[5][21][0])+(
      fstarr[21][1]*Vpk[5][21][1])))+((tstarr[21][2]*Wpk[5][21][2])+((
      tstarr[21][0]*Wpk[5][21][0])+(tstarr[21][1]*Wpk[5][21][1]))))+((((
      fstarr[19][2]*Vpk[5][19][2])+((fstarr[19][0]*Vpk[5][19][0])+(fstarr[19][1]
      *Vpk[5][19][1])))+((tstarr[19][2]*Wpk[5][19][2])+((tstarr[19][0]*
      Wpk[5][19][0])+(tstarr[19][1]*Wpk[5][19][1]))))+temp[2]));
    trqout[5] = -(utau[5]+((((fstarr[22][2]*Vpk[5][22][2])+((fstarr[22][0]*
      Vpk[5][22][0])+(fstarr[22][1]*Vpk[5][22][1])))+((tstarr[22][2]*
      Wpk[5][22][2])+((tstarr[22][0]*Wpk[5][22][0])+(tstarr[22][1]*Wpk[5][22][1]
      ))))+temp[3]));
    trqout[6] = -(utau[6]+((.3202*((fstarr[8][2]*Wpk[6][8][0])-(fstarr[8][0]*
      Wpk[6][8][2])))+((tstarr[8][2]*Wpk[6][8][2])+((tstarr[8][0]*Wpk[6][8][0])+
      (tstarr[8][1]*s7)))));
    trqout[7] = -(utau[7]+((.3202*((fstarr[8][2]*c8)-(fstarr[8][0]*s8)))+((
      tstarr[8][0]*c8)+(tstarr[8][2]*s8))));
    trqout[8] = -(tstarr[8][1]+utau[8]);
    temp[0] = ((((fstarr[11][2]*Vpk[9][11][2])+((.1715*(fstarr[11][0]*
      Wpk[9][11][2]))-(.002*(fstarr[11][1]*Wpk[9][11][2]))))+((tstarr[11][2]*
      Wpk[9][11][2])+((tstarr[11][0]*Wpk[9][11][0])+(tstarr[11][1]*s10))))+(((
      fstarr[12][2]*Vpk[9][12][2])+((fstarr[12][0]*Vpk[9][12][0])+(fstarr[12][1]
      *Vpk[9][12][1])))+((tstarr[12][2]*Wpk[9][12][2])+((tstarr[12][0]*
      Wpk[9][12][0])+(tstarr[12][1]*Wpk[9][12][1])))));
    trqout[9] = -(utau[9]+((((fstarr[15][2]*Vpk[9][15][2])+((fstarr[15][0]*
      Vpk[9][15][0])+(fstarr[15][1]*Vpk[9][15][1])))+((tstarr[15][2]*
      Wpk[9][15][2])+((tstarr[15][0]*Wpk[9][15][0])+(tstarr[15][1]*Wpk[9][15][1]
      ))))+((((fstarr[14][2]*Vpk[9][14][2])+((fstarr[14][0]*Vpk[9][14][0])+(
      fstarr[14][1]*Vpk[9][14][1])))+((tstarr[14][2]*Wpk[9][14][2])+((
      tstarr[14][0]*Wpk[9][14][0])+(tstarr[14][1]*Wpk[9][14][1]))))+temp[0])));
    temp[0] = ((((fstarr[12][2]*Vpk[10][12][2])+((fstarr[12][0]*Vpk[10][12][0])+
      (fstarr[12][1]*Vpk[10][12][1])))+((tstarr[12][2]*Wpk[10][12][2])+((
      tstarr[12][0]*Wpk[10][12][0])+(tstarr[12][1]*Wpk[10][12][1]))))+(((
      tstarr[11][0]*c11)+(tstarr[11][2]*s11))+(((.1715*(fstarr[11][0]*s11))-(
      .002*(fstarr[11][1]*s11)))-(.1715*(fstarr[11][2]*c11)))));
    trqout[10] = -(utau[10]+((((fstarr[15][2]*Vpk[10][15][2])+((fstarr[15][0]*
      Vpk[10][15][0])+(fstarr[15][1]*Vpk[10][15][1])))+((tstarr[15][2]*
      Wpk[10][15][2])+((tstarr[15][0]*Wpk[10][15][0])+(tstarr[15][1]*
      Wpk[10][15][1]))))+((((fstarr[14][2]*Vpk[10][14][2])+((fstarr[14][0]*
      Vpk[10][14][0])+(fstarr[14][1]*Vpk[10][14][1])))+((tstarr[14][2]*
      Wpk[10][14][2])+((tstarr[14][0]*Wpk[10][14][0])+(tstarr[14][1]*
      Wpk[10][14][1]))))+temp[0])));
    temp[0] = (((tstarr[11][1]+(.002*fstarr[11][2]))+(((Cik[12][1][2]*
      tstarr[12][2])+((Cik[12][1][0]*tstarr[12][0])+(Cik[12][1][1]*tstarr[12][1]
      )))+((fstarr[12][2]*Vpk[11][12][2])+((fstarr[12][0]*Vpk[11][12][0])-(.0013
      *(Cik[12][2][1]*fstarr[12][1]))))))+(((fstarr[14][2]*Vpk[11][14][2])+((
      fstarr[14][0]*Vpk[11][14][0])+(fstarr[14][1]*Vpk[11][14][1])))+((
      tstarr[14][2]*Wpk[11][14][2])+((tstarr[14][0]*Wpk[11][14][0])+(
      tstarr[14][1]*Wpk[11][14][1])))));
    trqout[11] = -(utau[11]+((((fstarr[15][2]*Vpk[11][15][2])+((fstarr[15][0]*
      Vpk[11][15][0])+(fstarr[15][1]*Vpk[11][15][1])))+((tstarr[15][2]*
      Wpk[11][15][2])+((tstarr[15][0]*Wpk[11][15][0])+(tstarr[15][1]*
      Wpk[11][15][1]))))+temp[0]));
    temp[0] = ((((.0150652581855386*fstarr[12][2])+(.185436609363333*
      fstarr[12][0]))+((.995900157697815*tstarr[12][2])+((.0404550064059294*
      tstarr[12][1])-(.0809090128117004*tstarr[12][0]))))+(((fstarr[14][2]*
      Vpk[12][14][2])+((fstarr[14][0]*Vpk[12][14][0])+(fstarr[14][1]*
      Vpk[12][14][1])))+((tstarr[14][2]*Wpk[12][14][2])+((tstarr[14][0]*
      Wpk[12][14][0])+(tstarr[14][1]*Wpk[12][14][1])))));
    trqout[12] = -(utau[12]+((((fstarr[15][2]*Vpk[12][15][2])+((fstarr[15][0]*
      Vpk[12][15][0])+(fstarr[15][1]*Vpk[12][15][1])))+((tstarr[15][2]*
      Wpk[12][15][2])+((tstarr[15][0]*Wpk[12][15][0])+(tstarr[15][1]*
      Wpk[12][15][1]))))+temp[0]));
    trqout[13] = -(utau[13]+((((fstarr[14][2]*Vpk[13][14][2])+((fstarr[14][0]*
      Vpk[13][14][0])+(fstarr[14][1]*Vpk[13][14][1])))+((tstarr[14][2]*
      Wpk[13][14][2])+((tstarr[14][0]*Wpk[13][14][0])+(tstarr[14][1]*
      Wpk[13][14][1]))))+(((fstarr[15][2]*Vpk[13][15][2])+((fstarr[15][0]*
      Vpk[13][15][0])+(fstarr[15][1]*Vpk[13][15][1])))+((tstarr[15][2]*
      Wpk[13][15][2])+((tstarr[15][0]*Wpk[13][15][0])+(tstarr[15][1]*
      Wpk[13][15][1]))))));
    trqout[14] = -(utau[14]+((((fstarr[15][2]*Vpk[14][15][2])+((fstarr[15][0]*
      Vpk[14][15][0])+(fstarr[15][1]*Vpk[14][15][1])))+((tstarr[15][2]*
      Wpk[14][15][2])+((tstarr[15][0]*Wpk[14][15][0])+(tstarr[15][1]*
      Wpk[14][15][1]))))+((((.000411457536296252*fstarr[14][0])-(
      .00646090297985859*fstarr[14][1]))-(.0625600530375351*fstarr[14][2]))+(((
      .57725989098448*tstarr[14][1])+(.814755846133373*tstarr[14][0]))-(
      .0542579897533796*tstarr[14][2])))));
    trqout[15] = -(utau[15]+(((.882947501360837*tstarr[15][2])-(.469471734868729
      *tstarr[15][0]))+(((.02617891313962*fstarr[15][1])-(.0163345287751755*
      fstarr[15][0]))-(.00868522709507149*fstarr[15][2]))));
    temp[0] = ((((fstarr[18][2]*Vpk[16][18][2])+((.1715*(fstarr[18][0]*
      Wpk[16][18][2]))-(.002*(fstarr[18][1]*Wpk[16][18][2]))))+((tstarr[18][2]*
      Wpk[16][18][2])+((tstarr[18][0]*Wpk[16][18][0])-(tstarr[18][1]*s17))))+(((
      fstarr[19][2]*Vpk[16][19][2])+((fstarr[19][0]*Vpk[16][19][0])+(
      fstarr[19][1]*Vpk[16][19][1])))+((tstarr[19][2]*Wpk[16][19][2])+((
      tstarr[19][0]*Wpk[16][19][0])+(tstarr[19][1]*Wpk[16][19][1])))));
    trqout[16] = -(utau[16]+((((fstarr[22][2]*Vpk[16][22][2])+((fstarr[22][0]*
      Vpk[16][22][0])+(fstarr[22][1]*Vpk[16][22][1])))+((tstarr[22][2]*
      Wpk[16][22][2])+((tstarr[22][0]*Wpk[16][22][0])+(tstarr[22][1]*
      Wpk[16][22][1]))))+((((fstarr[21][2]*Vpk[16][21][2])+((fstarr[21][0]*
      Vpk[16][21][0])+(fstarr[21][1]*Vpk[16][21][1])))+((tstarr[21][2]*
      Wpk[16][21][2])+((tstarr[21][0]*Wpk[16][21][0])+(tstarr[21][1]*
      Wpk[16][21][1]))))+temp[0])));
    temp[0] = ((((.1715*(fstarr[18][2]*c18))+((.1715*(fstarr[18][0]*s18))-(.002*
      (fstarr[18][1]*s18))))+((tstarr[18][2]*s18)-(tstarr[18][0]*c18)))+(((
      fstarr[19][2]*Vpk[17][19][2])+((fstarr[19][0]*Vpk[17][19][0])+(
      fstarr[19][1]*Vpk[17][19][1])))+((tstarr[19][2]*Wpk[17][19][2])+((
      tstarr[19][0]*Wpk[17][19][0])+(tstarr[19][1]*Wpk[17][19][1])))));
    trqout[17] = -(utau[17]+((((fstarr[22][2]*Vpk[17][22][2])+((fstarr[22][0]*
      Vpk[17][22][0])+(fstarr[22][1]*Vpk[17][22][1])))+((tstarr[22][2]*
      Wpk[17][22][2])+((tstarr[22][0]*Wpk[17][22][0])+(tstarr[22][1]*
      Wpk[17][22][1]))))+((((fstarr[21][2]*Vpk[17][21][2])+((fstarr[21][0]*
      Vpk[17][21][0])+(fstarr[21][1]*Vpk[17][21][1])))+((tstarr[21][2]*
      Wpk[17][21][2])+((tstarr[21][0]*Wpk[17][21][0])+(tstarr[21][1]*
      Wpk[17][21][1]))))+temp[0])));
    temp[0] = ((((fstarr[21][2]*Vpk[18][21][2])+((fstarr[21][0]*Vpk[18][21][0])+
      (fstarr[21][1]*Vpk[18][21][1])))+((tstarr[21][2]*Wpk[18][21][2])+((
      tstarr[21][0]*Wpk[18][21][0])+(tstarr[21][1]*Wpk[18][21][1]))))+((((
      fstarr[19][2]*Vpk[18][19][2])+((.0013*(Cik[19][2][1]*fstarr[19][1]))+(
      fstarr[19][0]*Vpk[18][19][0])))-((Cik[19][1][2]*tstarr[19][2])+((
      Cik[19][1][0]*tstarr[19][0])+(Cik[19][1][1]*tstarr[19][1]))))-(
      tstarr[18][1]+(.002*fstarr[18][2]))));
    trqout[18] = -(utau[18]+((((fstarr[22][2]*Vpk[18][22][2])+((fstarr[22][0]*
      Vpk[18][22][0])+(fstarr[22][1]*Vpk[18][22][1])))+((tstarr[22][2]*
      Wpk[18][22][2])+((tstarr[22][0]*Wpk[18][22][0])+(tstarr[22][1]*
      Wpk[18][22][1]))))+temp[0]));
    temp[0] = ((((.185436609363333*fstarr[19][0])-(.0150652581855386*
      fstarr[19][2]))+((.995900157697815*tstarr[19][2])+((.0809090128117004*
      tstarr[19][0])-(.0404550064059294*tstarr[19][1]))))+(((fstarr[21][2]*
      Vpk[19][21][2])+((fstarr[21][0]*Vpk[19][21][0])+(fstarr[21][1]*
      Vpk[19][21][1])))+((tstarr[21][2]*Wpk[19][21][2])+((tstarr[21][0]*
      Wpk[19][21][0])+(tstarr[21][1]*Wpk[19][21][1])))));
    trqout[19] = -(utau[19]+((((fstarr[22][2]*Vpk[19][22][2])+((fstarr[22][0]*
      Vpk[19][22][0])+(fstarr[22][1]*Vpk[19][22][1])))+((tstarr[22][2]*
      Wpk[19][22][2])+((tstarr[22][0]*Wpk[19][22][0])+(tstarr[22][1]*
      Wpk[19][22][1]))))+temp[0]));
    trqout[20] = -(utau[20]+((((fstarr[21][2]*Vpk[20][21][2])+((fstarr[21][0]*
      Vpk[20][21][0])+(fstarr[21][1]*Vpk[20][21][1])))+((tstarr[21][2]*
      Wpk[20][21][2])+((tstarr[21][0]*Wpk[20][21][0])+(tstarr[21][1]*
      Wpk[20][21][1]))))+(((fstarr[22][2]*Vpk[20][22][2])+((fstarr[22][0]*
      Vpk[20][22][0])+(fstarr[22][1]*Vpk[20][22][1])))+((tstarr[22][2]*
      Wpk[20][22][2])+((tstarr[22][0]*Wpk[20][22][0])+(tstarr[22][1]*
      Wpk[20][22][1]))))));
    trqout[21] = -(utau[21]+((((.0625600530375351*fstarr[21][2])+((
      .000411457536296252*fstarr[21][0])-(.00646090297985859*fstarr[21][1])))-((
      .0542579897533796*tstarr[21][2])+((.57725989098448*tstarr[21][1])+(
      .814755846133373*tstarr[21][0]))))+(((fstarr[22][2]*Vpk[21][22][2])+((
      fstarr[22][0]*Vpk[21][22][0])+(fstarr[22][1]*Vpk[21][22][1])))+((
      tstarr[22][2]*Wpk[21][22][2])+((tstarr[22][0]*Wpk[21][22][0])+(
      tstarr[22][1]*Wpk[21][22][1]))))));
    trqout[22] = -(utau[22]+(((.00868522709507149*fstarr[22][2])+((
      .02617891313962*fstarr[22][1])-(.0163345287751755*fstarr[22][0])))+((
      .469471734868729*tstarr[22][0])+(.882947501360837*tstarr[22][2]))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.29 seconds CPU time,
 24576 additional bytes of memory.
 Equations contain 1032 adds/subtracts/negates
                   1127 multiplies
                      0 divides
                    235 assignments
*/
}

sdcomptrq(udotin,trqout)
    double udotin[23],trqout[23];
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
    double multin[1],trqout[23];
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    for (i = 0; i < 23; i++) {
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
*/
}

sdfsmult()
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 23; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   23 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
*/
}

sdfsgenmult()
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 23; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
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
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   23 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
*/
}

sdrhs()
{
/*
Generated 20-Feb-2002 17:54:57 by SD/FAST, Kane's formulation
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
    tauc[9] = utau[9];
    tauc[10] = utau[10];
    tauc[11] = utau[11];
    tauc[12] = utau[12];
    tauc[13] = utau[13];
    tauc[14] = utau[14];
    tauc[15] = utau[15];
    tauc[16] = utau[16];
    tauc[17] = utau[17];
    tauc[18] = utau[18];
    tauc[19] = utau[19];
    tauc[20] = utau[20];
    tauc[21] = utau[21];
    tauc[22] = utau[22];
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[6][0] = ((udot[3]*c6)+(udot[4]*s6));
    Onkb[6][1] = ((udot[4]*c6)-(udot[3]*s6));
    Onkb[6][2] = (udot[5]+udot[6]);
    Onkb[7][0] = (Onkb[6][0]+udot[7]);
    Onkb[7][1] = ((Onkb[6][1]*c7)+(Onkb[6][2]*s7));
    Onkb[7][2] = ((Onkb[6][2]*c7)-(Onkb[6][1]*s7));
    Onkb[8][0] = ((Onkb[7][0]*c8)-(Onkb[7][2]*s8));
    Onkb[8][1] = (Onkb[7][1]+udot[8]);
    Onkb[8][2] = ((Onkb[7][0]*s8)+(Onkb[7][2]*c8));
    Onkb[9][0] = ((udot[3]*c9)+(udot[4]*s9));
    Onkb[9][1] = ((udot[4]*c9)-(udot[3]*s9));
    Onkb[9][2] = (udot[5]+udot[9]);
    Onkb[10][0] = (Onkb[9][0]+udot[10]);
    Onkb[10][1] = ((Onkb[9][1]*c10)+(Onkb[9][2]*s10));
    Onkb[10][2] = ((Onkb[9][2]*c10)-(Onkb[9][1]*s10));
    Onkb[11][0] = ((Onkb[10][0]*c11)-(Onkb[10][2]*s11));
    Onkb[11][1] = (Onkb[10][1]+udot[11]);
    Onkb[11][2] = ((Onkb[10][0]*s11)+(Onkb[10][2]*c11));
    Onkb[12][0] = (((Cik[12][2][0]*Onkb[11][2])+((Cik[12][0][0]*Onkb[11][0])+(
      Cik[12][1][0]*Onkb[11][1])))-(.0809090128117004*udot[12]));
    Onkb[12][1] = ((.0404550064059294*udot[12])+((Cik[12][2][1]*Onkb[11][2])+((
      Cik[12][0][1]*Onkb[11][0])+(Cik[12][1][1]*Onkb[11][1]))));
    Onkb[12][2] = ((.995900157697815*udot[12])+((Cik[12][2][2]*Onkb[11][2])+((
      Cik[12][0][2]*Onkb[11][0])+(Cik[12][1][2]*Onkb[11][1]))));
    Onkb[13][0] = (((Cik[13][2][0]*Onkb[12][2])+((Cik[13][0][0]*Onkb[12][0])+(
      Cik[13][1][0]*Onkb[12][1])))-(.0821860132171146*udot[13]));
    Onkb[13][1] = (((Cik[13][2][1]*Onkb[12][2])+((Cik[13][0][1]*Onkb[12][0])+(
      Cik[13][1][1]*Onkb[12][1])))-(.0372090059839342*udot[13]));
    Onkb[13][2] = ((.995922160163717*udot[13])+((Cik[13][2][2]*Onkb[12][2])+((
      Cik[13][0][2]*Onkb[12][0])+(Cik[13][1][2]*Onkb[12][1]))));
    Onkb[14][0] = ((.814755846133373*udot[14])+((Cik[14][2][0]*Onkb[13][2])+((
      Cik[14][0][0]*Onkb[13][0])+(Cik[14][1][0]*Onkb[13][1]))));
    Onkb[14][1] = ((.57725989098448*udot[14])+((Cik[14][2][1]*Onkb[13][2])+((
      Cik[14][0][1]*Onkb[13][0])+(Cik[14][1][1]*Onkb[13][1]))));
    Onkb[14][2] = (((Cik[14][2][2]*Onkb[13][2])+((Cik[14][0][2]*Onkb[13][0])+(
      Cik[14][1][2]*Onkb[13][1])))-(.0542579897533796*udot[14]));
    Onkb[15][0] = (((Cik[15][2][0]*Onkb[14][2])+((.882947501360837*(Onkb[14][1]*
      s15))+(Cik[15][0][0]*Onkb[14][0])))-(.469471734868729*udot[15]));
    Onkb[15][1] = (((Onkb[14][1]*c15)-(.882947501360837*(Onkb[14][0]*s15)))-(
      .469471734868729*(Onkb[14][2]*s15)));
    Onkb[15][2] = ((.882947501360837*udot[15])+((Cik[15][2][2]*Onkb[14][2])+((
      .469471734868729*(Onkb[14][1]*s15))+(Cik[15][0][2]*Onkb[14][0]))));
    Onkb[16][0] = ((udot[3]*c16)+(udot[4]*s16));
    Onkb[16][1] = ((udot[4]*c16)-(udot[3]*s16));
    Onkb[16][2] = (udot[5]+udot[16]);
    Onkb[17][0] = (Onkb[16][0]-udot[17]);
    Onkb[17][1] = ((Onkb[16][1]*c17)-(Onkb[16][2]*s17));
    Onkb[17][2] = ((Onkb[16][1]*s17)+(Onkb[16][2]*c17));
    Onkb[18][0] = ((Onkb[17][0]*c18)+(Onkb[17][2]*s18));
    Onkb[18][1] = (Onkb[17][1]-udot[18]);
    Onkb[18][2] = ((Onkb[17][2]*c18)-(Onkb[17][0]*s18));
    Onkb[19][0] = ((.0809090128117004*udot[19])+((Cik[19][2][0]*Onkb[18][2])+((
      Cik[19][0][0]*Onkb[18][0])+(Cik[19][1][0]*Onkb[18][1]))));
    Onkb[19][1] = (((Cik[19][2][1]*Onkb[18][2])+((Cik[19][0][1]*Onkb[18][0])+(
      Cik[19][1][1]*Onkb[18][1])))-(.0404550064059294*udot[19]));
    Onkb[19][2] = ((.995900157697815*udot[19])+((Cik[19][2][2]*Onkb[18][2])+((
      Cik[19][0][2]*Onkb[18][0])+(Cik[19][1][2]*Onkb[18][1]))));
    Onkb[20][0] = ((.0821860132171146*udot[20])+((Cik[20][2][0]*Onkb[19][2])+((
      Cik[20][0][0]*Onkb[19][0])+(Cik[20][1][0]*Onkb[19][1]))));
    Onkb[20][1] = ((.0372090059839342*udot[20])+((Cik[20][2][1]*Onkb[19][2])+((
      Cik[20][0][1]*Onkb[19][0])+(Cik[20][1][1]*Onkb[19][1]))));
    Onkb[20][2] = ((.995922160163717*udot[20])+((Cik[20][2][2]*Onkb[19][2])+((
      Cik[20][0][2]*Onkb[19][0])+(Cik[20][1][2]*Onkb[19][1]))));
    Onkb[21][0] = (((Cik[21][2][0]*Onkb[20][2])+((Cik[21][0][0]*Onkb[20][0])+(
      Cik[21][1][0]*Onkb[20][1])))-(.814755846133373*udot[21]));
    Onkb[21][1] = (((Cik[21][2][1]*Onkb[20][2])+((Cik[21][0][1]*Onkb[20][0])+(
      Cik[21][1][1]*Onkb[20][1])))-(.57725989098448*udot[21]));
    Onkb[21][2] = (((Cik[21][2][2]*Onkb[20][2])+((Cik[21][0][2]*Onkb[20][0])+(
      Cik[21][1][2]*Onkb[20][1])))-(.0542579897533796*udot[21]));
    Onkb[22][0] = ((.469471734868729*udot[22])+((Cik[22][2][0]*Onkb[21][2])+((
      .882947501360837*(Onkb[21][1]*s22))+(Cik[22][0][0]*Onkb[21][0]))));
    Onkb[22][1] = ((.469471734868729*(Onkb[21][2]*s22))+((Onkb[21][1]*c22)-(
      .882947501360837*(Onkb[21][0]*s22))));
    Onkb[22][2] = ((.882947501360837*udot[22])+((Cik[22][2][2]*Onkb[21][2])+((
      Cik[22][0][2]*Onkb[21][0])-(.469471734868729*(Onkb[21][1]*s22)))));
    onk[8][0] = (Onkb[8][0]+Otk[8][0]);
    onk[8][1] = (Onkb[8][1]+Otk[7][1]);
    onk[8][2] = (Onkb[8][2]+Otk[8][2]);
    onk[11][0] = (Onkb[11][0]+Otk[11][0]);
    onk[11][1] = (Onkb[11][1]+Otk[10][1]);
    onk[11][2] = (Onkb[11][2]+Otk[11][2]);
    onk[12][0] = (Onkb[12][0]+Otk[12][0]);
    onk[12][1] = (Onkb[12][1]+Otk[12][1]);
    onk[12][2] = (Onkb[12][2]+Otk[12][2]);
    onk[14][0] = (Onkb[14][0]+Otk[14][0]);
    onk[14][1] = (Onkb[14][1]+Otk[14][1]);
    onk[14][2] = (Onkb[14][2]+Otk[14][2]);
    onk[15][0] = (Onkb[15][0]+Otk[15][0]);
    onk[15][1] = (Onkb[15][1]+Otk[15][1]);
    onk[15][2] = (Onkb[15][2]+Otk[15][2]);
    onk[18][0] = (Onkb[18][0]+Otk[18][0]);
    onk[18][1] = (Onkb[18][1]+Otk[17][1]);
    onk[18][2] = (Onkb[18][2]+Otk[18][2]);
    onk[19][0] = (Onkb[19][0]+Otk[19][0]);
    onk[19][1] = (Onkb[19][1]+Otk[19][1]);
    onk[19][2] = (Onkb[19][2]+Otk[19][2]);
    onk[21][0] = (Onkb[21][0]+Otk[21][0]);
    onk[21][1] = (Onkb[21][1]+Otk[21][1]);
    onk[21][2] = (Onkb[21][2]+Otk[21][2]);
    onk[22][0] = (Onkb[22][0]+Otk[22][0]);
    onk[22][1] = (Onkb[22][1]+Otk[22][1]);
    onk[22][2] = (Onkb[22][2]+Otk[22][2]);
    onb[0][0] = udot[3];
    onb[0][1] = udot[4];
    onb[0][2] = udot[5];
    onb[1][0] = onk[8][0];
    onb[1][1] = onk[8][1];
    onb[1][2] = onk[8][2];
    onb[2][0] = onk[11][0];
    onb[2][1] = onk[11][1];
    onb[2][2] = onk[11][2];
    onb[3][0] = onk[12][0];
    onb[3][1] = onk[12][1];
    onb[3][2] = onk[12][2];
    onb[4][0] = onk[14][0];
    onb[4][1] = onk[14][1];
    onb[4][2] = onk[14][2];
    onb[5][0] = onk[15][0];
    onb[5][1] = onk[15][1];
    onb[5][2] = onk[15][2];
    onb[6][0] = onk[18][0];
    onb[6][1] = onk[18][1];
    onb[6][2] = onk[18][2];
    onb[7][0] = onk[19][0];
    onb[7][1] = onk[19][1];
    onb[7][2] = onk[19][2];
    onb[8][0] = onk[21][0];
    onb[8][1] = onk[21][1];
    onb[8][2] = onk[21][2];
    onb[9][0] = onk[22][0];
    onb[9][1] = onk[22][1];
    onb[9][2] = onk[22][2];
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
    dyad[3][0][1] = (w0w1[3]-onk[12][2]);
    dyad[3][0][2] = (onk[12][1]+w0w2[3]);
    dyad[3][1][0] = (onk[12][2]+w0w1[3]);
    dyad[3][1][1] = w00w22[3];
    dyad[3][1][2] = (w1w2[3]-onk[12][0]);
    dyad[3][2][0] = (w0w2[3]-onk[12][1]);
    dyad[3][2][1] = (onk[12][0]+w1w2[3]);
    dyad[3][2][2] = w00w11[3];
    dyad[4][0][0] = w11w22[4];
    dyad[4][0][1] = (w0w1[4]-onk[14][2]);
    dyad[4][0][2] = (onk[14][1]+w0w2[4]);
    dyad[4][1][0] = (onk[14][2]+w0w1[4]);
    dyad[4][1][1] = w00w22[4];
    dyad[4][1][2] = (w1w2[4]-onk[14][0]);
    dyad[4][2][0] = (w0w2[4]-onk[14][1]);
    dyad[4][2][1] = (onk[14][0]+w1w2[4]);
    dyad[4][2][2] = w00w11[4];
    dyad[5][0][0] = w11w22[5];
    dyad[5][0][1] = (w0w1[5]-onk[15][2]);
    dyad[5][0][2] = (onk[15][1]+w0w2[5]);
    dyad[5][1][0] = (onk[15][2]+w0w1[5]);
    dyad[5][1][1] = w00w22[5];
    dyad[5][1][2] = (w1w2[5]-onk[15][0]);
    dyad[5][2][0] = (w0w2[5]-onk[15][1]);
    dyad[5][2][1] = (onk[15][0]+w1w2[5]);
    dyad[5][2][2] = w00w11[5];
    dyad[6][0][0] = w11w22[6];
    dyad[6][0][1] = (w0w1[6]-onk[18][2]);
    dyad[6][0][2] = (onk[18][1]+w0w2[6]);
    dyad[6][1][0] = (onk[18][2]+w0w1[6]);
    dyad[6][1][1] = w00w22[6];
    dyad[6][1][2] = (w1w2[6]-onk[18][0]);
    dyad[6][2][0] = (w0w2[6]-onk[18][1]);
    dyad[6][2][1] = (onk[18][0]+w1w2[6]);
    dyad[6][2][2] = w00w11[6];
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-onk[19][2]);
    dyad[7][0][2] = (onk[19][1]+w0w2[7]);
    dyad[7][1][0] = (onk[19][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-onk[19][0]);
    dyad[7][2][0] = (w0w2[7]-onk[19][1]);
    dyad[7][2][1] = (onk[19][0]+w1w2[7]);
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
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[3][0] = ((Cik[3][2][0]*udot[2])+((Cik[3][0][0]*udot[0])+(Cik[3][1][0]*
      udot[1])));
    Ankb[3][1] = ((Cik[3][2][1]*udot[2])+((Cik[3][0][1]*udot[0])+(Cik[3][1][1]*
      udot[1])));
    Ankb[3][2] = ((Cik[3][2][2]*udot[2])+((Cik[3][0][2]*udot[0])+(Cik[3][1][2]*
      udot[1])));
    AOnkri[6][0] = (Ankb[3][0]-(.127*udot[5]));
    AOnkri[6][2] = (Ankb[3][2]+(.127*udot[3]));
    Ankb[6][0] = ((Ankb[3][1]*s6)+(AOnkri[6][0]*c6));
    Ankb[6][1] = ((Ankb[3][1]*c6)-(AOnkri[6][0]*s6));
    Ankb[7][1] = ((Ankb[6][1]*c7)+(AOnkri[6][2]*s7));
    Ankb[7][2] = ((AOnkri[6][2]*c7)-(Ankb[6][1]*s7));
    Ankb[8][0] = (((Ankb[6][0]*c8)-(Ankb[7][2]*s8))-(.3202*Onkb[8][2]));
    Ankb[8][2] = ((.3202*Onkb[8][0])+((Ankb[6][0]*s8)+(Ankb[7][2]*c8)));
    AOnkri[9][0] = (Ankb[3][0]+((.07*udot[5])+(.0935*udot[4])));
    AOnkri[9][1] = (Ankb[3][1]-(.0935*udot[3]));
    AOnkri[9][2] = (Ankb[3][2]-(.07*udot[3]));
    Ankb[9][0] = ((AOnkri[9][0]*c9)+(AOnkri[9][1]*s9));
    Ankb[9][1] = ((AOnkri[9][1]*c9)-(AOnkri[9][0]*s9));
    Ankb[10][1] = ((Ankb[9][1]*c10)+(AOnkri[9][2]*s10));
    Ankb[10][2] = ((AOnkri[9][2]*c10)-(Ankb[9][1]*s10));
    Ankb[11][0] = ((.1715*Onkb[11][2])+((Ankb[9][0]*c11)-(Ankb[10][2]*s11)));
    Ankb[11][1] = (Ankb[10][1]-(.002*Onkb[11][2]));
    Ankb[11][2] = (((.002*Onkb[11][1])-(.1715*Onkb[11][0]))+((Ankb[9][0]*s11)+(
      Ankb[10][2]*c11)));
    AOnkri[12][0] = (Ankb[11][0]+(.2294*Onkb[11][2]));
    AOnkri[12][1] = (Ankb[11][1]+(.0033*Onkb[11][2]));
    AOnkri[12][2] = (Ankb[11][2]-((.0033*Onkb[11][1])+(.2294*Onkb[11][0])));
    Ankb[12][0] = ((.1862*Onkb[12][2])+((AOnkri[12][2]*Cik[12][2][0])+((
      AOnkri[12][0]*Cik[12][0][0])+(AOnkri[12][1]*Cik[12][1][0]))));
    Ankb[12][1] = ((AOnkri[12][2]*Cik[12][2][1])+((AOnkri[12][0]*Cik[12][0][1])+
      (AOnkri[12][1]*Cik[12][1][1])));
    Ankb[12][2] = (((AOnkri[12][2]*Cik[12][2][2])+((AOnkri[12][0]*Cik[12][0][2])
      +(AOnkri[12][1]*Cik[12][1][2])))-(.1862*Onkb[12][0]));
    AOnkri[13][0] = (Ankb[12][0]+(.2438*Onkb[12][2]));
    AOnkri[13][2] = (Ankb[12][2]-(.2438*Onkb[12][0]));
    Ankb[13][0] = ((AOnkri[13][2]*Cik[13][2][0])+((Ankb[12][1]*Cik[13][1][0])+(
      AOnkri[13][0]*Cik[13][0][0])));
    Ankb[13][1] = ((AOnkri[13][2]*Cik[13][2][1])+((Ankb[12][1]*Cik[13][1][1])+(
      AOnkri[13][0]*Cik[13][0][1])));
    Ankb[13][2] = ((AOnkri[13][2]*Cik[13][2][2])+((Ankb[12][1]*Cik[13][1][2])+(
      AOnkri[13][0]*Cik[13][0][2])));
    Ankb[14][0] = (((.005539*Onkb[14][1])+(.051347*Onkb[14][2]))+((Ankb[13][2]*
      Cik[14][2][0])+((Ankb[13][0]*Cik[14][0][0])+(Ankb[13][1]*Cik[14][1][0]))))
      ;
    Ankb[14][1] = (((.035902*Onkb[14][2])-(.005539*Onkb[14][0]))+((Ankb[13][2]*
      Cik[14][2][1])+((Ankb[13][0]*Cik[14][0][1])+(Ankb[13][1]*Cik[14][1][1]))))
      ;
    Ankb[14][2] = (((Ankb[13][2]*Cik[14][2][2])+((Ankb[13][0]*Cik[14][0][2])+(
      Ankb[13][1]*Cik[14][1][2])))-((.035902*Onkb[14][1])+(.051347*Onkb[14][0]))
      );
    AOnkri[15][0] = (Ankb[14][0]+((.018078*Onkb[14][1])+(.038*Onkb[14][2])));
    AOnkri[15][1] = (Ankb[14][1]+((.098032*Onkb[14][2])-(.018078*Onkb[14][0])));
    AOnkri[15][2] = (Ankb[14][2]-((.038*Onkb[14][0])+(.098032*Onkb[14][1])));
    Ankb[15][0] = (((.005139*Onkb[15][1])-(.0185*Onkb[15][2]))+((AOnkri[15][2]*
      Cik[15][2][0])+((.882947501360837*(AOnkri[15][1]*s15))+(AOnkri[15][0]*
      Cik[15][0][0]))));
    Ankb[15][1] = (((.026917*Onkb[15][2])-(.005139*Onkb[15][0]))+(((
      AOnkri[15][1]*c15)-(.882947501360837*(AOnkri[15][0]*s15)))-(
      .469471734868729*(AOnkri[15][2]*s15))));
    Ankb[15][2] = (((.0185*Onkb[15][0])-(.026917*Onkb[15][1]))+((AOnkri[15][2]*
      Cik[15][2][2])+((.469471734868729*(AOnkri[15][1]*s15))+(AOnkri[15][0]*
      Cik[15][0][2]))));
    AOnkri[16][0] = (Ankb[3][0]+((.07*udot[5])-(.0935*udot[4])));
    AOnkri[16][1] = (Ankb[3][1]+(.0935*udot[3]));
    AOnkri[16][2] = (Ankb[3][2]-(.07*udot[3]));
    Ankb[16][0] = ((AOnkri[16][0]*c16)+(AOnkri[16][1]*s16));
    Ankb[16][1] = ((AOnkri[16][1]*c16)-(AOnkri[16][0]*s16));
    Ankb[17][1] = ((Ankb[16][1]*c17)-(AOnkri[16][2]*s17));
    Ankb[17][2] = ((Ankb[16][1]*s17)+(AOnkri[16][2]*c17));
    Ankb[18][0] = ((.1715*Onkb[18][2])+((Ankb[16][0]*c18)+(Ankb[17][2]*s18)));
    Ankb[18][1] = (Ankb[17][1]-(.002*Onkb[18][2]));
    Ankb[18][2] = (((.002*Onkb[18][1])-(.1715*Onkb[18][0]))+((Ankb[17][2]*c18)-(
      Ankb[16][0]*s18)));
    AOnkri[19][0] = (Ankb[18][0]+(.2294*Onkb[18][2]));
    AOnkri[19][1] = (Ankb[18][1]+(.0033*Onkb[18][2]));
    AOnkri[19][2] = (Ankb[18][2]-((.0033*Onkb[18][1])+(.2294*Onkb[18][0])));
    Ankb[19][0] = ((.1862*Onkb[19][2])+((AOnkri[19][2]*Cik[19][2][0])+((
      AOnkri[19][0]*Cik[19][0][0])+(AOnkri[19][1]*Cik[19][1][0]))));
    Ankb[19][1] = ((AOnkri[19][2]*Cik[19][2][1])+((AOnkri[19][0]*Cik[19][0][1])+
      (AOnkri[19][1]*Cik[19][1][1])));
    Ankb[19][2] = (((AOnkri[19][2]*Cik[19][2][2])+((AOnkri[19][0]*Cik[19][0][2])
      +(AOnkri[19][1]*Cik[19][1][2])))-(.1862*Onkb[19][0]));
    AOnkri[20][0] = (Ankb[19][0]+(.2438*Onkb[19][2]));
    AOnkri[20][2] = (Ankb[19][2]-(.2438*Onkb[19][0]));
    Ankb[20][0] = ((AOnkri[20][2]*Cik[20][2][0])+((Ankb[19][1]*Cik[20][1][0])+(
      AOnkri[20][0]*Cik[20][0][0])));
    Ankb[20][1] = ((AOnkri[20][2]*Cik[20][2][1])+((Ankb[19][1]*Cik[20][1][1])+(
      AOnkri[20][0]*Cik[20][0][1])));
    Ankb[20][2] = ((AOnkri[20][2]*Cik[20][2][2])+((Ankb[19][1]*Cik[20][1][2])+(
      AOnkri[20][0]*Cik[20][0][2])));
    Ankb[21][0] = (((.051347*Onkb[21][2])-(.005539*Onkb[21][1]))+((Ankb[20][2]*
      Cik[21][2][0])+((Ankb[20][0]*Cik[21][0][0])+(Ankb[20][1]*Cik[21][1][0]))))
      ;
    Ankb[21][1] = (((.005539*Onkb[21][0])+(.035902*Onkb[21][2]))+((Ankb[20][2]*
      Cik[21][2][1])+((Ankb[20][0]*Cik[21][0][1])+(Ankb[20][1]*Cik[21][1][1]))))
      ;
    Ankb[21][2] = (((Ankb[20][2]*Cik[21][2][2])+((Ankb[20][0]*Cik[21][0][2])+(
      Ankb[20][1]*Cik[21][1][2])))-((.035902*Onkb[21][1])+(.051347*Onkb[21][0]))
      );
    AOnkri[22][0] = (Ankb[21][0]+((.038*Onkb[21][2])-(.018078*Onkb[21][1])));
    AOnkri[22][1] = (Ankb[21][1]+((.018078*Onkb[21][0])+(.098032*Onkb[21][2])));
    AOnkri[22][2] = (Ankb[21][2]-((.038*Onkb[21][0])+(.098032*Onkb[21][1])));
    Ankb[22][0] = (((AOnkri[22][2]*Cik[22][2][0])+((.882947501360837*(
      AOnkri[22][1]*s22))+(AOnkri[22][0]*Cik[22][0][0])))-((.005139*Onkb[22][1])
      +(.0185*Onkb[22][2])));
    Ankb[22][1] = (((.005139*Onkb[22][0])+(.026917*Onkb[22][2]))+((
      .469471734868729*(AOnkri[22][2]*s22))+((AOnkri[22][1]*c22)-(
      .882947501360837*(AOnkri[22][0]*s22)))));
    Ankb[22][2] = (((.0185*Onkb[22][0])-(.026917*Onkb[22][1]))+((AOnkri[22][2]*
      Cik[22][2][2])+((AOnkri[22][0]*Cik[22][0][2])-(.469471734868729*(
      AOnkri[22][1]*s22)))));
    ank[5][0] = ((Ankb[3][2]*Cik[3][0][2])+((Ankb[3][0]*Cik[3][0][0])+(
      Ankb[3][1]*Cik[3][0][1])));
    ank[5][1] = ((Ankb[3][2]*Cik[3][1][2])+((Ankb[3][0]*Cik[3][1][0])+(
      Ankb[3][1]*Cik[3][1][1])));
    ank[5][2] = ((Ankb[3][2]*Cik[3][2][2])+((Ankb[3][0]*Cik[3][2][0])+(
      Ankb[3][1]*Cik[3][2][1])));
    AnkAtk[8][0] = (Ankb[8][0]+Atk[8][0]);
    AnkAtk[8][1] = (Ankb[7][1]+Atk[8][1]);
    AnkAtk[8][2] = (Ankb[8][2]+Atk[8][2]);
    ank[8][0] = ((AnkAtk[8][2]*cnk[8][0][2])+((AnkAtk[8][0]*cnk[8][0][0])+(
      AnkAtk[8][1]*cnk[7][0][1])));
    ank[8][1] = ((AnkAtk[8][2]*cnk[8][1][2])+((AnkAtk[8][0]*cnk[8][1][0])+(
      AnkAtk[8][1]*cnk[7][1][1])));
    ank[8][2] = ((AnkAtk[8][2]*cnk[8][2][2])+((AnkAtk[8][0]*cnk[8][2][0])+(
      AnkAtk[8][1]*cnk[7][2][1])));
    AnkAtk[11][0] = (Ankb[11][0]+Atk[11][0]);
    AnkAtk[11][1] = (Ankb[11][1]+Atk[11][1]);
    AnkAtk[11][2] = (Ankb[11][2]+Atk[11][2]);
    ank[11][0] = ((AnkAtk[11][2]*cnk[11][0][2])+((AnkAtk[11][0]*cnk[11][0][0])+(
      AnkAtk[11][1]*cnk[10][0][1])));
    ank[11][1] = ((AnkAtk[11][2]*cnk[11][1][2])+((AnkAtk[11][0]*cnk[11][1][0])+(
      AnkAtk[11][1]*cnk[10][1][1])));
    ank[11][2] = ((AnkAtk[11][2]*cnk[11][2][2])+((AnkAtk[11][0]*cnk[11][2][0])+(
      AnkAtk[11][1]*cnk[10][2][1])));
    AnkAtk[12][0] = (Ankb[12][0]+Atk[12][0]);
    AnkAtk[12][1] = (Ankb[12][1]+Atk[12][1]);
    AnkAtk[12][2] = (Ankb[12][2]+Atk[12][2]);
    ank[12][0] = ((AnkAtk[12][2]*cnk[12][0][2])+((AnkAtk[12][0]*cnk[12][0][0])+(
      AnkAtk[12][1]*cnk[12][0][1])));
    ank[12][1] = ((AnkAtk[12][2]*cnk[12][1][2])+((AnkAtk[12][0]*cnk[12][1][0])+(
      AnkAtk[12][1]*cnk[12][1][1])));
    ank[12][2] = ((AnkAtk[12][2]*cnk[12][2][2])+((AnkAtk[12][0]*cnk[12][2][0])+(
      AnkAtk[12][1]*cnk[12][2][1])));
    AnkAtk[14][0] = (Ankb[14][0]+Atk[14][0]);
    AnkAtk[14][1] = (Ankb[14][1]+Atk[14][1]);
    AnkAtk[14][2] = (Ankb[14][2]+Atk[14][2]);
    ank[14][0] = ((AnkAtk[14][2]*cnk[14][0][2])+((AnkAtk[14][0]*cnk[14][0][0])+(
      AnkAtk[14][1]*cnk[14][0][1])));
    ank[14][1] = ((AnkAtk[14][2]*cnk[14][1][2])+((AnkAtk[14][0]*cnk[14][1][0])+(
      AnkAtk[14][1]*cnk[14][1][1])));
    ank[14][2] = ((AnkAtk[14][2]*cnk[14][2][2])+((AnkAtk[14][0]*cnk[14][2][0])+(
      AnkAtk[14][1]*cnk[14][2][1])));
    AnkAtk[15][0] = (Ankb[15][0]+Atk[15][0]);
    AnkAtk[15][1] = (Ankb[15][1]+Atk[15][1]);
    AnkAtk[15][2] = (Ankb[15][2]+Atk[15][2]);
    ank[15][0] = ((AnkAtk[15][2]*cnk[15][0][2])+((AnkAtk[15][0]*cnk[15][0][0])+(
      AnkAtk[15][1]*cnk[15][0][1])));
    ank[15][1] = ((AnkAtk[15][2]*cnk[15][1][2])+((AnkAtk[15][0]*cnk[15][1][0])+(
      AnkAtk[15][1]*cnk[15][1][1])));
    ank[15][2] = ((AnkAtk[15][2]*cnk[15][2][2])+((AnkAtk[15][0]*cnk[15][2][0])+(
      AnkAtk[15][1]*cnk[15][2][1])));
    AnkAtk[18][0] = (Ankb[18][0]+Atk[18][0]);
    AnkAtk[18][1] = (Ankb[18][1]+Atk[18][1]);
    AnkAtk[18][2] = (Ankb[18][2]+Atk[18][2]);
    ank[18][0] = ((AnkAtk[18][2]*cnk[18][0][2])+((AnkAtk[18][0]*cnk[18][0][0])+(
      AnkAtk[18][1]*cnk[17][0][1])));
    ank[18][1] = ((AnkAtk[18][2]*cnk[18][1][2])+((AnkAtk[18][0]*cnk[18][1][0])+(
      AnkAtk[18][1]*cnk[17][1][1])));
    ank[18][2] = ((AnkAtk[18][2]*cnk[18][2][2])+((AnkAtk[18][0]*cnk[18][2][0])+(
      AnkAtk[18][1]*cnk[17][2][1])));
    AnkAtk[19][0] = (Ankb[19][0]+Atk[19][0]);
    AnkAtk[19][1] = (Ankb[19][1]+Atk[19][1]);
    AnkAtk[19][2] = (Ankb[19][2]+Atk[19][2]);
    ank[19][0] = ((AnkAtk[19][2]*cnk[19][0][2])+((AnkAtk[19][0]*cnk[19][0][0])+(
      AnkAtk[19][1]*cnk[19][0][1])));
    ank[19][1] = ((AnkAtk[19][2]*cnk[19][1][2])+((AnkAtk[19][0]*cnk[19][1][0])+(
      AnkAtk[19][1]*cnk[19][1][1])));
    ank[19][2] = ((AnkAtk[19][2]*cnk[19][2][2])+((AnkAtk[19][0]*cnk[19][2][0])+(
      AnkAtk[19][1]*cnk[19][2][1])));
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
    anb[4][0] = ank[14][0];
    anb[4][1] = ank[14][1];
    anb[4][2] = ank[14][2];
    anb[5][0] = ank[15][0];
    anb[5][1] = ank[15][1];
    anb[5][2] = ank[15][2];
    anb[6][0] = ank[18][0];
    anb[6][1] = ank[18][1];
    anb[6][2] = ank[18][2];
    anb[7][0] = ank[19][0];
    anb[7][1] = ank[19][1];
    anb[7][2] = ank[19][2];
    anb[8][0] = ank[21][0];
    anb[8][1] = ank[21][1];
    anb[8][2] = ank[21][2];
    anb[9][0] = ank[22][0];
    anb[9][1] = ank[22][1];
    anb[9][2] = ank[22][2];
    roustate = 3;
/*
 Used 0.12 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  415 adds/subtracts/negates
                    425 multiplies
                      0 divides
                    379 assignments
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
    double oudot0[23];
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
    sdldubslv(23,23,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 22; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     23 assignments
*/
}

sdudot0(oudot0)
    double oudot0[23];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

sdsetudot(iudot)
    double iudot[23];
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 22; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

sdxudotm(routine,imult,oudotm)
    int routine;
    double imult[1],oudotm[23];
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    for (i = 0; i <= 22; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 22; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     46 assignments
*/
}

sdudotm(imult,oudotm)
    double imult[1],oudotm[23];
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

sdderiv(oqdot,oudot)
    double oqdot[24],oudot[23];
{
/*
This is the derivative section for a 10-body free-flying
system with 23 degree(s) of freedom, including 6 degrees
of freedom for attitude and translation of the base body.
*/
    int i;
    double udot0[23],udot1[23];

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
    for (i = 0; i <= 23; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 22; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     47 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

sdresid(eqdot,eudot,emults,resid)
    double eqdot[24],eudot[23],emults[1],resid[47];
{
    int i;
    double uderrs[23];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 24; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 23; i++) {
        resid[24+i] = uderrs[i];
    }
    for (i = 0; i < 23; i++) {
        udot[i] = eudot[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   24 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     70 assignments
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
    double force[10][3],torque[10][3];
{
/*
Generated 20-Feb-2002 17:54:57 by SD/FAST, Kane's formulation
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
    fc[22][0] = ((.205126*(AnkAtk[22][0]-gk[22][0]))-ufk[9][0]);
    fc[22][1] = ((.205126*(AnkAtk[22][1]-gk[22][1]))-ufk[9][1]);
    fc[22][2] = ((.205126*(AnkAtk[22][2]-gk[22][2]))-ufk[9][2]);
    tc[22][0] = ((WkIkWk[22][0]+(.000117*onk[22][0]))-(utk[9][0]-((.005139*
      fc[22][1])+(.0185*fc[22][2]))));
    tc[22][1] = ((WkIkWk[22][1]+(.000179*onk[22][1]))-(utk[9][1]+((.005139*
      fc[22][0])+(.026917*fc[22][2]))));
    tc[22][2] = ((WkIkWk[22][2]+(.000119*onk[22][2]))-(utk[9][2]+((.0185*
      fc[22][0])-(.026917*fc[22][1]))));
    fccikt[22][0] = ((Cik[22][0][2]*fc[22][2])+((Cik[22][0][0]*fc[22][0])-(
      .882947501360837*(fc[22][1]*s22))));
    fccikt[22][1] = (((.882947501360837*(fc[22][0]*s22))+(fc[22][1]*c22))-(
      .469471734868729*(fc[22][2]*s22)));
    fccikt[22][2] = ((Cik[22][2][2]*fc[22][2])+((.469471734868729*(fc[22][1]*s22
      ))+(Cik[22][2][0]*fc[22][0])));
    ffk[21][0] = (ufk[8][0]-fccikt[22][0]);
    ffk[21][1] = (ufk[8][1]-fccikt[22][1]);
    ffk[21][2] = (ufk[8][2]-fccikt[22][2]);
    ttk[21][0] = (utk[8][0]-(((.018078*fccikt[22][1])-(.038*fccikt[22][2]))+((
      Cik[22][0][2]*tc[22][2])+((Cik[22][0][0]*tc[22][0])-(.882947501360837*(
      tc[22][1]*s22))))));
    ttk[21][1] = (utk[8][1]-((((.882947501360837*(tc[22][0]*s22))+(tc[22][1]*c22
      ))-(.469471734868729*(tc[22][2]*s22)))-((.018078*fccikt[22][0])+(.098032*
      fccikt[22][2]))));
    ttk[21][2] = (utk[8][2]-(((.038*fccikt[22][0])+(.098032*fccikt[22][1]))+((
      Cik[22][2][2]*tc[22][2])+((.469471734868729*(tc[22][1]*s22))+(
      Cik[22][2][0]*tc[22][0])))));
    fc[21][0] = ((1.2*(AnkAtk[21][0]-gk[21][0]))-ffk[21][0]);
    fc[21][1] = ((1.2*(AnkAtk[21][1]-gk[21][1]))-ffk[21][1]);
    fc[21][2] = ((1.2*(AnkAtk[21][2]-gk[21][2]))-ffk[21][2]);
    tc[21][0] = ((WkIkWk[21][0]+(.001361*onk[21][0]))-(ttk[21][0]+((.051347*
      fc[21][2])-(.005539*fc[21][1]))));
    tc[21][1] = ((WkIkWk[21][1]+(.003709*onk[21][1]))-(ttk[21][1]+((.005539*
      fc[21][0])+(.035902*fc[21][2]))));
    tc[21][2] = ((WkIkWk[21][2]+(.003916*onk[21][2]))-(ttk[21][2]-((.035902*
      fc[21][1])+(.051347*fc[21][0]))));
    fccikt[21][0] = ((Cik[21][0][2]*fc[21][2])+((Cik[21][0][0]*fc[21][0])+(
      Cik[21][0][1]*fc[21][1])));
    fccikt[21][1] = ((Cik[21][1][2]*fc[21][2])+((Cik[21][1][0]*fc[21][0])+(
      Cik[21][1][1]*fc[21][1])));
    fccikt[21][2] = ((Cik[21][2][2]*fc[21][2])+((Cik[21][2][0]*fc[21][0])+(
      Cik[21][2][1]*fc[21][1])));
    ffk[20][0] = -fccikt[21][0];
    ffk[20][1] = -fccikt[21][1];
    ffk[20][2] = -fccikt[21][2];
    ttk[20][0] = -((Cik[21][0][2]*tc[21][2])+((Cik[21][0][0]*tc[21][0])+(
      Cik[21][0][1]*tc[21][1])));
    ttk[20][1] = -((Cik[21][1][2]*tc[21][2])+((Cik[21][1][0]*tc[21][0])+(
      Cik[21][1][1]*tc[21][1])));
    ttk[20][2] = -((Cik[21][2][2]*tc[21][2])+((Cik[21][2][0]*tc[21][0])+(
      Cik[21][2][1]*tc[21][1])));
    fc[20][0] = -ffk[20][0];
    fc[20][1] = -ffk[20][1];
    fc[20][2] = -ffk[20][2];
    tc[20][0] = -ttk[20][0];
    tc[20][1] = -ttk[20][1];
    tc[20][2] = -ttk[20][2];
    fccikt[20][0] = ((Cik[20][0][2]*fc[20][2])+((Cik[20][0][0]*fc[20][0])+(
      Cik[20][0][1]*fc[20][1])));
    fccikt[20][1] = ((Cik[20][1][2]*fc[20][2])+((Cik[20][1][0]*fc[20][0])+(
      Cik[20][1][1]*fc[20][1])));
    fccikt[20][2] = ((Cik[20][2][2]*fc[20][2])+((Cik[20][2][0]*fc[20][0])+(
      Cik[20][2][1]*fc[20][1])));
    ffk[19][0] = (ufk[7][0]-fccikt[20][0]);
    ffk[19][1] = (ufk[7][1]-fccikt[20][1]);
    ffk[19][2] = (ufk[7][2]-fccikt[20][2]);
    ttk[19][0] = (utk[7][0]-(((Cik[20][0][2]*tc[20][2])+((Cik[20][0][0]*
      tc[20][0])+(Cik[20][0][1]*tc[20][1])))-(.2438*fccikt[20][2])));
    ttk[19][1] = (utk[7][1]-((Cik[20][1][2]*tc[20][2])+((Cik[20][1][0]*tc[20][0]
      )+(Cik[20][1][1]*tc[20][1]))));
    ttk[19][2] = (utk[7][2]-((.2438*fccikt[20][0])+((Cik[20][2][2]*tc[20][2])+((
      Cik[20][2][0]*tc[20][0])+(Cik[20][2][1]*tc[20][1])))));
    fc[19][0] = ((3.51*(AnkAtk[19][0]-gk[19][0]))-ffk[19][0]);
    fc[19][1] = ((3.51*(AnkAtk[19][1]-gk[19][1]))-ffk[19][1]);
    fc[19][2] = ((3.51*(AnkAtk[19][2]-gk[19][2]))-ffk[19][2]);
    tc[19][0] = ((WkIkWk[19][0]+(.0477*onk[19][0]))-(ttk[19][0]+(.1862*fc[19][2]
      )));
    tc[19][1] = ((WkIkWk[19][1]+(.0048*onk[19][1]))-ttk[19][1]);
    tc[19][2] = ((WkIkWk[19][2]+(.0484*onk[19][2]))-(ttk[19][2]-(.1862*fc[19][0]
      )));
    fccikt[19][0] = ((Cik[19][0][2]*fc[19][2])+((Cik[19][0][0]*fc[19][0])+(
      Cik[19][0][1]*fc[19][1])));
    fccikt[19][1] = ((Cik[19][1][2]*fc[19][2])+((Cik[19][1][0]*fc[19][0])+(
      Cik[19][1][1]*fc[19][1])));
    fccikt[19][2] = ((Cik[19][2][2]*fc[19][2])+((Cik[19][2][0]*fc[19][0])+(
      Cik[19][2][1]*fc[19][1])));
    ffk[18][0] = (ufk[6][0]-fccikt[19][0]);
    ffk[18][1] = (ufk[6][1]-fccikt[19][1]);
    ffk[18][2] = (ufk[6][2]-fccikt[19][2]);
    ttk[18][0] = (utk[6][0]-(((Cik[19][0][2]*tc[19][2])+((Cik[19][0][0]*
      tc[19][0])+(Cik[19][0][1]*tc[19][1])))-(.2294*fccikt[19][2])));
    ttk[18][1] = (utk[6][1]-(((Cik[19][1][2]*tc[19][2])+((Cik[19][1][0]*
      tc[19][0])+(Cik[19][1][1]*tc[19][1])))-(.0033*fccikt[19][2])));
    ttk[18][2] = (utk[6][2]-(((.0033*fccikt[19][1])+(.2294*fccikt[19][0]))+((
      Cik[19][2][2]*tc[19][2])+((Cik[19][2][0]*tc[19][0])+(Cik[19][2][1]*
      tc[19][1])))));
    fc[18][0] = ((8.806*(AnkAtk[18][0]-gk[18][0]))-ffk[18][0]);
    fc[18][1] = ((8.806*(AnkAtk[18][1]-gk[17][1]))-ffk[18][1]);
    fc[18][2] = ((8.806*(AnkAtk[18][2]-gk[18][2]))-ffk[18][2]);
    tc[18][0] = ((WkIkWk[18][0]+(.1268*onk[18][0]))-(ttk[18][0]+(.1715*fc[18][2]
      )));
    tc[18][1] = ((WkIkWk[18][1]+(.0332*onk[18][1]))-(ttk[18][1]-(.002*fc[18][2])
      ));
    tc[18][2] = ((WkIkWk[18][2]+(.1337*onk[18][2]))-(ttk[18][2]+((.002*fc[18][1]
      )-(.1715*fc[18][0]))));
    fccikt[18][0] = ((fc[18][0]*c18)-(fc[18][2]*s18));
    fccikt[18][1] = fc[18][1];
    fccikt[18][2] = ((fc[18][0]*s18)+(fc[18][2]*c18));
    ffk[17][0] = -fccikt[18][0];
    ffk[17][1] = -fccikt[18][1];
    ffk[17][2] = -fccikt[18][2];
    ttk[17][0] = -((tc[18][0]*c18)-(tc[18][2]*s18));
    ttk[17][1] = -tc[18][1];
    ttk[17][2] = -((tc[18][0]*s18)+(tc[18][2]*c18));
    fc[17][0] = -ffk[17][0];
    fc[17][1] = -ffk[17][1];
    fc[17][2] = -ffk[17][2];
    tc[17][0] = -ttk[17][0];
    tc[17][1] = -ttk[17][1];
    tc[17][2] = -ttk[17][2];
    fccikt[17][0] = fc[17][0];
    fccikt[17][1] = ((fc[17][1]*c17)+(fc[17][2]*s17));
    fccikt[17][2] = ((fc[17][2]*c17)-(fc[17][1]*s17));
    ffk[16][0] = -fccikt[17][0];
    ffk[16][1] = -fccikt[17][1];
    ffk[16][2] = -fccikt[17][2];
    ttk[16][0] = -tc[17][0];
    ttk[16][1] = -((tc[17][1]*c17)+(tc[17][2]*s17));
    ttk[16][2] = -((tc[17][2]*c17)-(tc[17][1]*s17));
    fc[16][0] = -ffk[16][0];
    fc[16][1] = -ffk[16][1];
    fc[16][2] = -ffk[16][2];
    tc[16][0] = -ttk[16][0];
    tc[16][1] = -ttk[16][1];
    tc[16][2] = -ttk[16][2];
    fccikt[16][0] = ((fc[16][0]*c16)-(fc[16][1]*s16));
    fccikt[16][1] = ((fc[16][0]*s16)+(fc[16][1]*c16));
    fccikt[16][2] = fc[16][2];
    ffk[5][0] = (ufk[0][0]-fccikt[16][0]);
    ffk[5][1] = (ufk[0][1]-fccikt[16][1]);
    ffk[5][2] = (ufk[0][2]-fccikt[16][2]);
    ttk[5][0] = (utk[0][0]-(((.0935*fccikt[16][1])-(.07*fccikt[16][2]))+((
      tc[16][0]*c16)-(tc[16][1]*s16))));
    ttk[5][1] = (utk[0][1]-(((tc[16][0]*s16)+(tc[16][1]*c16))-(.0935*
      fccikt[16][0])));
    ttk[5][2] = (utk[0][2]-(tc[16][2]+(.07*fccikt[16][0])));
    fc[15][0] = ((.205126*(AnkAtk[15][0]-gk[15][0]))-ufk[5][0]);
    fc[15][1] = ((.205126*(AnkAtk[15][1]-gk[15][1]))-ufk[5][1]);
    fc[15][2] = ((.205126*(AnkAtk[15][2]-gk[15][2]))-ufk[5][2]);
    tc[15][0] = ((WkIkWk[15][0]+(.000117*onk[15][0]))-(utk[5][0]+((.005139*
      fc[15][1])-(.0185*fc[15][2]))));
    tc[15][1] = ((WkIkWk[15][1]+(.000179*onk[15][1]))-(utk[5][1]+((.026917*
      fc[15][2])-(.005139*fc[15][0]))));
    tc[15][2] = ((WkIkWk[15][2]+(.000119*onk[15][2]))-(utk[5][2]+((.0185*
      fc[15][0])-(.026917*fc[15][1]))));
    fccikt[15][0] = ((Cik[15][0][2]*fc[15][2])+((Cik[15][0][0]*fc[15][0])-(
      .882947501360837*(fc[15][1]*s15))));
    fccikt[15][1] = ((.469471734868729*(fc[15][2]*s15))+((.882947501360837*(
      fc[15][0]*s15))+(fc[15][1]*c15)));
    fccikt[15][2] = ((Cik[15][2][2]*fc[15][2])+((Cik[15][2][0]*fc[15][0])-(
      .469471734868729*(fc[15][1]*s15))));
    ffk[14][0] = (ufk[4][0]-fccikt[15][0]);
    ffk[14][1] = (ufk[4][1]-fccikt[15][1]);
    ffk[14][2] = (ufk[4][2]-fccikt[15][2]);
    ttk[14][0] = (utk[4][0]-(((Cik[15][0][2]*tc[15][2])+((Cik[15][0][0]*
      tc[15][0])-(.882947501360837*(tc[15][1]*s15))))-((.018078*fccikt[15][1])+(
      .038*fccikt[15][2]))));
    ttk[14][1] = (utk[4][1]-(((.018078*fccikt[15][0])-(.098032*fccikt[15][2]))+(
      (.469471734868729*(tc[15][2]*s15))+((.882947501360837*(tc[15][0]*s15))+(
      tc[15][1]*c15)))));
    ttk[14][2] = (utk[4][2]-(((.038*fccikt[15][0])+(.098032*fccikt[15][1]))+((
      Cik[15][2][2]*tc[15][2])+((Cik[15][2][0]*tc[15][0])-(.469471734868729*(
      tc[15][1]*s15))))));
    fc[14][0] = ((1.2*(AnkAtk[14][0]-gk[14][0]))-ffk[14][0]);
    fc[14][1] = ((1.2*(AnkAtk[14][1]-gk[14][1]))-ffk[14][1]);
    fc[14][2] = ((1.2*(AnkAtk[14][2]-gk[14][2]))-ffk[14][2]);
    tc[14][0] = ((WkIkWk[14][0]+(.001361*onk[14][0]))-(ttk[14][0]+((.005539*
      fc[14][1])+(.051347*fc[14][2]))));
    tc[14][1] = ((WkIkWk[14][1]+(.003709*onk[14][1]))-(ttk[14][1]+((.035902*
      fc[14][2])-(.005539*fc[14][0]))));
    tc[14][2] = ((WkIkWk[14][2]+(.003916*onk[14][2]))-(ttk[14][2]-((.035902*
      fc[14][1])+(.051347*fc[14][0]))));
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
    ffk[12][0] = (ufk[3][0]-fccikt[13][0]);
    ffk[12][1] = (ufk[3][1]-fccikt[13][1]);
    ffk[12][2] = (ufk[3][2]-fccikt[13][2]);
    ttk[12][0] = (utk[3][0]-(((Cik[13][0][2]*tc[13][2])+((Cik[13][0][0]*
      tc[13][0])+(Cik[13][0][1]*tc[13][1])))-(.2438*fccikt[13][2])));
    ttk[12][1] = (utk[3][1]-((Cik[13][1][2]*tc[13][2])+((Cik[13][1][0]*tc[13][0]
      )+(Cik[13][1][1]*tc[13][1]))));
    ttk[12][2] = (utk[3][2]-((.2438*fccikt[13][0])+((Cik[13][2][2]*tc[13][2])+((
      Cik[13][2][0]*tc[13][0])+(Cik[13][2][1]*tc[13][1])))));
    fc[12][0] = ((3.51*(AnkAtk[12][0]-gk[12][0]))-ffk[12][0]);
    fc[12][1] = ((3.51*(AnkAtk[12][1]-gk[12][1]))-ffk[12][1]);
    fc[12][2] = ((3.51*(AnkAtk[12][2]-gk[12][2]))-ffk[12][2]);
    tc[12][0] = ((WkIkWk[12][0]+(.0477*onk[12][0]))-(ttk[12][0]+(.1862*fc[12][2]
      )));
    tc[12][1] = ((WkIkWk[12][1]+(.0048*onk[12][1]))-ttk[12][1]);
    tc[12][2] = ((WkIkWk[12][2]+(.0484*onk[12][2]))-(ttk[12][2]-(.1862*fc[12][0]
      )));
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
    fc[11][1] = ((8.806*(AnkAtk[11][1]-gk[10][1]))-ffk[11][1]);
    fc[11][2] = ((8.806*(AnkAtk[11][2]-gk[11][2]))-ffk[11][2]);
    tc[11][0] = ((WkIkWk[11][0]+(.1268*onk[11][0]))-(ttk[11][0]+(.1715*fc[11][2]
      )));
    tc[11][1] = ((WkIkWk[11][1]+(.0332*onk[11][1]))-(ttk[11][1]-(.002*fc[11][2])
      ));
    tc[11][2] = ((WkIkWk[11][2]+(.1337*onk[11][2]))-(ttk[11][2]+((.002*fc[11][1]
      )-(.1715*fc[11][0]))));
    fccikt[11][0] = ((fc[11][0]*c11)+(fc[11][2]*s11));
    fccikt[11][1] = fc[11][1];
    fccikt[11][2] = ((fc[11][2]*c11)-(fc[11][0]*s11));
    ffk[10][0] = -fccikt[11][0];
    ffk[10][1] = -fccikt[11][1];
    ffk[10][2] = -fccikt[11][2];
    ttk[10][0] = -((tc[11][0]*c11)+(tc[11][2]*s11));
    ttk[10][1] = -tc[11][1];
    ttk[10][2] = -((tc[11][2]*c11)-(tc[11][0]*s11));
    fc[10][0] = -ffk[10][0];
    fc[10][1] = -ffk[10][1];
    fc[10][2] = -ffk[10][2];
    tc[10][0] = -ttk[10][0];
    tc[10][1] = -ttk[10][1];
    tc[10][2] = -ttk[10][2];
    fccikt[10][0] = fc[10][0];
    fccikt[10][1] = ((fc[10][1]*c10)-(fc[10][2]*s10));
    fccikt[10][2] = ((fc[10][1]*s10)+(fc[10][2]*c10));
    ffk[9][0] = -fccikt[10][0];
    ffk[9][1] = -fccikt[10][1];
    ffk[9][2] = -fccikt[10][2];
    ttk[9][0] = -tc[10][0];
    ttk[9][1] = -((tc[10][1]*c10)-(tc[10][2]*s10));
    ttk[9][2] = -((tc[10][1]*s10)+(tc[10][2]*c10));
    fc[9][0] = -ffk[9][0];
    fc[9][1] = -ffk[9][1];
    fc[9][2] = -ffk[9][2];
    tc[9][0] = -ttk[9][0];
    tc[9][1] = -ttk[9][1];
    tc[9][2] = -ttk[9][2];
    fccikt[9][0] = ((fc[9][0]*c9)-(fc[9][1]*s9));
    fccikt[9][1] = ((fc[9][0]*s9)+(fc[9][1]*c9));
    fccikt[9][2] = fc[9][2];
    ffk[5][0] = (ffk[5][0]-fccikt[9][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[9][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[9][2]);
    ttk[5][0] = (ttk[5][0]-(((tc[9][0]*c9)-(tc[9][1]*s9))-((.07*fccikt[9][2])+(
      .0935*fccikt[9][1]))));
    ttk[5][1] = (ttk[5][1]-((.0935*fccikt[9][0])+((tc[9][0]*s9)+(tc[9][1]*c9))))
      ;
    ttk[5][2] = (ttk[5][2]-(tc[9][2]+(.07*fccikt[9][0])));
    fc[8][0] = ((32.413*(AnkAtk[8][0]-gk[8][0]))-ufk[1][0]);
    fc[8][1] = ((32.413*(AnkAtk[8][1]-gk[7][1]))-ufk[1][1]);
    fc[8][2] = ((32.413*(AnkAtk[8][2]-gk[8][2]))-ufk[1][2]);
    tc[8][0] = ((WkIkWk[8][0]+(1.396*onk[8][0]))-(utk[1][0]-(.3202*fc[8][2])));
    tc[8][1] = ((WkIkWk[8][1]+(.7153*onk[8][1]))-utk[1][1]);
    tc[8][2] = ((WkIkWk[8][2]+(1.3552*onk[8][2]))-(utk[1][2]+(.3202*fc[8][0])));
    fccikt[8][0] = ((fc[8][0]*c8)+(fc[8][2]*s8));
    fccikt[8][1] = fc[8][1];
    fccikt[8][2] = ((fc[8][2]*c8)-(fc[8][0]*s8));
    ffk[7][0] = -fccikt[8][0];
    ffk[7][1] = -fccikt[8][1];
    ffk[7][2] = -fccikt[8][2];
    ttk[7][0] = -((tc[8][0]*c8)+(tc[8][2]*s8));
    ttk[7][1] = -tc[8][1];
    ttk[7][2] = -((tc[8][2]*c8)-(tc[8][0]*s8));
    fc[7][0] = -ffk[7][0];
    fc[7][1] = -ffk[7][1];
    fc[7][2] = -ffk[7][2];
    tc[7][0] = -ttk[7][0];
    tc[7][1] = -ttk[7][1];
    tc[7][2] = -ttk[7][2];
    fccikt[7][0] = fc[7][0];
    fccikt[7][1] = ((fc[7][1]*c7)-(fc[7][2]*s7));
    fccikt[7][2] = ((fc[7][1]*s7)+(fc[7][2]*c7));
    ffk[6][0] = -fccikt[7][0];
    ffk[6][1] = -fccikt[7][1];
    ffk[6][2] = -fccikt[7][2];
    ttk[6][0] = -tc[7][0];
    ttk[6][1] = -((tc[7][1]*c7)-(tc[7][2]*s7));
    ttk[6][2] = -((tc[7][1]*s7)+(tc[7][2]*c7));
    fc[6][0] = -ffk[6][0];
    fc[6][1] = -ffk[6][1];
    fc[6][2] = -ffk[6][2];
    tc[6][0] = -ttk[6][0];
    tc[6][1] = -ttk[6][1];
    tc[6][2] = -ttk[6][2];
    fccikt[6][0] = ((fc[6][0]*c6)-(fc[6][1]*s6));
    fccikt[6][1] = ((fc[6][0]*s6)+(fc[6][1]*c6));
    fccikt[6][2] = fc[6][2];
    ffk[5][0] = (ffk[5][0]-fccikt[6][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[6][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[6][2]);
    ttk[5][0] = (ttk[5][0]-((.127*fccikt[6][2])+((tc[6][0]*c6)-(tc[6][1]*s6))));
    ttk[5][1] = (ttk[5][1]-((tc[6][0]*s6)+(tc[6][1]*c6)));
    ttk[5][2] = (ttk[5][2]-(tc[6][2]-(.127*fccikt[6][0])));
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
    ttk[1][0] = -(tc[2][0]-(fccikt[2][1]*q[2]));
    ttk[1][1] = -(tc[2][1]+(fccikt[2][0]*q[2]));
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
    force[4][0] = fc[14][0];
    torque[4][0] = tc[14][0];
    force[4][1] = fc[14][1];
    torque[4][1] = tc[14][1];
    force[4][2] = fc[14][2];
    torque[4][2] = tc[14][2];
    force[5][0] = fc[15][0];
    torque[5][0] = tc[15][0];
    force[5][1] = fc[15][1];
    torque[5][1] = tc[15][1];
    force[5][2] = fc[15][2];
    torque[5][2] = tc[15][2];
    force[6][0] = fc[18][0];
    torque[6][0] = tc[18][0];
    force[6][1] = fc[18][1];
    torque[6][1] = tc[18][1];
    force[6][2] = fc[18][2];
    torque[6][2] = tc[18][2];
    force[7][0] = fc[19][0];
    torque[7][0] = tc[19][0];
    force[7][1] = fc[19][1];
    torque[7][1] = tc[19][1];
    force[7][2] = fc[19][2];
    torque[7][2] = tc[19][2];
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
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.13 seconds CPU time,
 32768 additional bytes of memory.
 Equations contain  550 adds/subtracts/negates
                    386 multiplies
                      0 divides
                    396 assignments
*/
}

sdmom(lm,am,ke)
    double lm[3],am[3],*ke;
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 20-Feb-2002 17:54:57 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
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
    lm[0] = ((.205126*vnk[22][0])+((1.2*vnk[21][0])+((3.51*vnk[19][0])+((8.806*
      vnk[18][0])+((.205126*vnk[15][0])+((1.2*vnk[14][0])+((3.51*vnk[12][0])+((
      8.806*vnk[11][0])+((11.15*u[0])+(32.413*vnk[8][0]))))))))));
    lm[1] = ((.205126*vnk[22][1])+((1.2*vnk[21][1])+((3.51*vnk[19][1])+((8.806*
      vnk[18][1])+((.205126*vnk[15][1])+((1.2*vnk[14][1])+((3.51*vnk[12][1])+((
      8.806*vnk[11][1])+((11.15*u[1])+(32.413*vnk[8][1]))))))))));
    lm[2] = ((.205126*vnk[22][2])+((1.2*vnk[21][2])+((3.51*vnk[19][2])+((8.806*
      vnk[18][2])+((.205126*vnk[15][2])+((1.2*vnk[14][2])+((3.51*vnk[12][2])+((
      8.806*vnk[11][2])+((11.15*u[2])+(32.413*vnk[8][2]))))))))));
    temp[0] = (((11.15*((q[1]*u[2])-(q[2]*u[1])))+((.0548*(Cik[3][0][2]*u[5]))+(
      (.0825*(Cik[3][0][1]*u[4]))+(.0973*(Cik[3][0][0]*u[3])))))+((32.413*((
      rnk[8][1]*vnk[8][2])-(rnk[8][2]*vnk[8][1])))+((1.3552*(cnk[8][0][2]*
      wk[8][2]))+((.7153*(cnk[7][0][1]*wk[8][1]))+(1.396*(cnk[8][0][0]*wk[8][0])
      )))));
    temp[1] = (((3.51*((rnk[12][1]*vnk[12][2])-(rnk[12][2]*vnk[12][1])))+((.0484
      *(cnk[12][0][2]*wk[12][2]))+((.0048*(cnk[12][0][1]*wk[12][1]))+(.0477*(
      cnk[12][0][0]*wk[12][0])))))+(((8.806*((rnk[11][1]*vnk[11][2])-(rnk[11][2]
      *vnk[11][1])))+((.1337*(cnk[11][0][2]*wk[11][2]))+((.0332*(cnk[10][0][1]*
      wk[11][1]))+(.1268*(cnk[11][0][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[15][1]*vnk[15][2])-(rnk[15][2]*vnk[15][1])))+((
      .000119*(cnk[15][0][2]*wk[15][2]))+((.000117*(cnk[15][0][0]*wk[15][0]))+(
      .000179*(cnk[15][0][1]*wk[15][1])))))+(((1.2*((rnk[14][1]*vnk[14][2])-(
      rnk[14][2]*vnk[14][1])))+((.003916*(cnk[14][0][2]*wk[14][2]))+((.001361*(
      cnk[14][0][0]*wk[14][0]))+(.003709*(cnk[14][0][1]*wk[14][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[19][1]*vnk[19][2])-(rnk[19][2]*vnk[19][1])))+((.0484
      *(cnk[19][0][2]*wk[19][2]))+((.0048*(cnk[19][0][1]*wk[19][1]))+(.0477*(
      cnk[19][0][0]*wk[19][0])))))+(((8.806*((rnk[18][1]*vnk[18][2])-(rnk[18][2]
      *vnk[18][1])))+((.1337*(cnk[18][0][2]*wk[18][2]))+((.0332*(cnk[17][0][1]*
      wk[18][1]))+(.1268*(cnk[18][0][0]*wk[18][0])))))+temp[2]));
    am[0] = ((((.205126*((rnk[22][1]*vnk[22][2])-(rnk[22][2]*vnk[22][1])))+((
      .000119*(cnk[22][0][2]*wk[22][2]))+((.000117*(cnk[22][0][0]*wk[22][0]))+(
      .000179*(cnk[22][0][1]*wk[22][1])))))+(((1.2*((rnk[21][1]*vnk[21][2])-(
      rnk[21][2]*vnk[21][1])))+((.003916*(cnk[21][0][2]*wk[21][2]))+((.001361*(
      cnk[21][0][0]*wk[21][0]))+(.003709*(cnk[21][0][1]*wk[21][1])))))+temp[3]))
      -((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = (((11.15*((q[2]*u[0])-(q[0]*u[2])))+((.0548*(Cik[3][1][2]*u[5]))+(
      (.0825*(Cik[3][1][1]*u[4]))+(.0973*(Cik[3][1][0]*u[3])))))+((32.413*((
      rnk[8][2]*vnk[8][0])-(rnk[8][0]*vnk[8][2])))+((1.3552*(cnk[8][1][2]*
      wk[8][2]))+((.7153*(cnk[7][1][1]*wk[8][1]))+(1.396*(cnk[8][1][0]*wk[8][0])
      )))));
    temp[1] = (((3.51*((rnk[12][2]*vnk[12][0])-(rnk[12][0]*vnk[12][2])))+((.0484
      *(cnk[12][1][2]*wk[12][2]))+((.0048*(cnk[12][1][1]*wk[12][1]))+(.0477*(
      cnk[12][1][0]*wk[12][0])))))+(((8.806*((rnk[11][2]*vnk[11][0])-(rnk[11][0]
      *vnk[11][2])))+((.1337*(cnk[11][1][2]*wk[11][2]))+((.0332*(cnk[10][1][1]*
      wk[11][1]))+(.1268*(cnk[11][1][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[15][2]*vnk[15][0])-(rnk[15][0]*vnk[15][2])))+((
      .000119*(cnk[15][1][2]*wk[15][2]))+((.000117*(cnk[15][1][0]*wk[15][0]))+(
      .000179*(cnk[15][1][1]*wk[15][1])))))+(((1.2*((rnk[14][2]*vnk[14][0])-(
      rnk[14][0]*vnk[14][2])))+((.003916*(cnk[14][1][2]*wk[14][2]))+((.001361*(
      cnk[14][1][0]*wk[14][0]))+(.003709*(cnk[14][1][1]*wk[14][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[19][2]*vnk[19][0])-(rnk[19][0]*vnk[19][2])))+((.0484
      *(cnk[19][1][2]*wk[19][2]))+((.0048*(cnk[19][1][1]*wk[19][1]))+(.0477*(
      cnk[19][1][0]*wk[19][0])))))+(((8.806*((rnk[18][2]*vnk[18][0])-(rnk[18][0]
      *vnk[18][2])))+((.1337*(cnk[18][1][2]*wk[18][2]))+((.0332*(cnk[17][1][1]*
      wk[18][1]))+(.1268*(cnk[18][1][0]*wk[18][0])))))+temp[2]));
    am[1] = ((((.205126*((rnk[22][2]*vnk[22][0])-(rnk[22][0]*vnk[22][2])))+((
      .000119*(cnk[22][1][2]*wk[22][2]))+((.000117*(cnk[22][1][0]*wk[22][0]))+(
      .000179*(cnk[22][1][1]*wk[22][1])))))+(((1.2*((rnk[21][2]*vnk[21][0])-(
      rnk[21][0]*vnk[21][2])))+((.003916*(cnk[21][1][2]*wk[21][2]))+((.001361*(
      cnk[21][1][0]*wk[21][0]))+(.003709*(cnk[21][1][1]*wk[21][1])))))+temp[3]))
      -((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = (((11.15*((q[0]*u[1])-(q[1]*u[0])))+((.0548*(Cik[3][2][2]*u[5]))+(
      (.0825*(Cik[3][2][1]*u[4]))+(.0973*(Cik[3][2][0]*u[3])))))+((32.413*((
      rnk[8][0]*vnk[8][1])-(rnk[8][1]*vnk[8][0])))+((1.3552*(cnk[8][2][2]*
      wk[8][2]))+((.7153*(cnk[7][2][1]*wk[8][1]))+(1.396*(cnk[8][2][0]*wk[8][0])
      )))));
    temp[1] = (((3.51*((rnk[12][0]*vnk[12][1])-(rnk[12][1]*vnk[12][0])))+((.0484
      *(cnk[12][2][2]*wk[12][2]))+((.0048*(cnk[12][2][1]*wk[12][1]))+(.0477*(
      cnk[12][2][0]*wk[12][0])))))+(((8.806*((rnk[11][0]*vnk[11][1])-(rnk[11][1]
      *vnk[11][0])))+((.1337*(cnk[11][2][2]*wk[11][2]))+((.0332*(cnk[10][2][1]*
      wk[11][1]))+(.1268*(cnk[11][2][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((rnk[15][0]*vnk[15][1])-(rnk[15][1]*vnk[15][0])))+((
      .000119*(cnk[15][2][2]*wk[15][2]))+((.000117*(cnk[15][2][0]*wk[15][0]))+(
      .000179*(cnk[15][2][1]*wk[15][1])))))+(((1.2*((rnk[14][0]*vnk[14][1])-(
      rnk[14][1]*vnk[14][0])))+((.003916*(cnk[14][2][2]*wk[14][2]))+((.001361*(
      cnk[14][2][0]*wk[14][0]))+(.003709*(cnk[14][2][1]*wk[14][1])))))+temp[1]))
      ;
    temp[3] = (((3.51*((rnk[19][0]*vnk[19][1])-(rnk[19][1]*vnk[19][0])))+((.0484
      *(cnk[19][2][2]*wk[19][2]))+((.0048*(cnk[19][2][1]*wk[19][1]))+(.0477*(
      cnk[19][2][0]*wk[19][0])))))+(((8.806*((rnk[18][0]*vnk[18][1])-(rnk[18][1]
      *vnk[18][0])))+((.1337*(cnk[18][2][2]*wk[18][2]))+((.0332*(cnk[17][2][1]*
      wk[18][1]))+(.1268*(cnk[18][2][0]*wk[18][0])))))+temp[2]));
    am[2] = ((((.205126*((rnk[22][0]*vnk[22][1])-(rnk[22][1]*vnk[22][0])))+((
      .000119*(cnk[22][2][2]*wk[22][2]))+((.000117*(cnk[22][2][0]*wk[22][0]))+(
      .000179*(cnk[22][2][1]*wk[22][1])))))+(((1.2*((rnk[21][0]*vnk[21][1])-(
      rnk[21][1]*vnk[21][0])))+((.003916*(cnk[21][2][2]*wk[21][2]))+((.001361*(
      cnk[21][2][0]*wk[21][0]))+(.003709*(cnk[21][2][1]*wk[21][1])))))+temp[3]))
      -((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = (((11.15*((u[2]*u[2])+((u[0]*u[0])+(u[1]*u[1]))))+((.0548*(u[5]*
      u[5]))+((.0825*(u[4]*u[4]))+(.0973*(u[3]*u[3])))))+((32.413*((vnk[8][2]*
      vnk[8][2])+((vnk[8][0]*vnk[8][0])+(vnk[8][1]*vnk[8][1]))))+((1.3552*(
      wk[8][2]*wk[8][2]))+((.7153*(wk[8][1]*wk[8][1]))+(1.396*(wk[8][0]*wk[8][0]
      ))))));
    temp[1] = (((3.51*((vnk[12][2]*vnk[12][2])+((vnk[12][0]*vnk[12][0])+(
      vnk[12][1]*vnk[12][1]))))+((.0484*(wk[12][2]*wk[12][2]))+((.0048*(
      wk[12][1]*wk[12][1]))+(.0477*(wk[12][0]*wk[12][0])))))+(((8.806*((
      vnk[11][2]*vnk[11][2])+((vnk[11][0]*vnk[11][0])+(vnk[11][1]*vnk[11][1]))))
      +((.1337*(wk[11][2]*wk[11][2]))+((.0332*(wk[11][1]*wk[11][1]))+(.1268*(
      wk[11][0]*wk[11][0])))))+temp[0]));
    temp[2] = (((.205126*((vnk[15][2]*vnk[15][2])+((vnk[15][0]*vnk[15][0])+(
      vnk[15][1]*vnk[15][1]))))+((.000119*(wk[15][2]*wk[15][2]))+((.000117*(
      wk[15][0]*wk[15][0]))+(.000179*(wk[15][1]*wk[15][1])))))+(((1.2*((
      vnk[14][2]*vnk[14][2])+((vnk[14][0]*vnk[14][0])+(vnk[14][1]*vnk[14][1]))))
      +((.003916*(wk[14][2]*wk[14][2]))+((.001361*(wk[14][0]*wk[14][0]))+(
      .003709*(wk[14][1]*wk[14][1])))))+temp[1]));
    temp[3] = (((3.51*((vnk[19][2]*vnk[19][2])+((vnk[19][0]*vnk[19][0])+(
      vnk[19][1]*vnk[19][1]))))+((.0484*(wk[19][2]*wk[19][2]))+((.0048*(
      wk[19][1]*wk[19][1]))+(.0477*(wk[19][0]*wk[19][0])))))+(((8.806*((
      vnk[18][2]*vnk[18][2])+((vnk[18][0]*vnk[18][0])+(vnk[18][1]*vnk[18][1]))))
      +((.1337*(wk[18][2]*wk[18][2]))+((.0332*(wk[18][1]*wk[18][1]))+(.1268*(
      wk[18][0]*wk[18][0])))))+temp[2]));
    *ke = (.5*(((.205126*((vnk[22][2]*vnk[22][2])+((vnk[22][0]*vnk[22][0])+(
      vnk[22][1]*vnk[22][1]))))+((.000119*(wk[22][2]*wk[22][2]))+((.000117*(
      wk[22][0]*wk[22][0]))+(.000179*(wk[22][1]*wk[22][1])))))+(((1.2*((
      vnk[21][2]*vnk[21][2])+((vnk[21][0]*vnk[21][0])+(vnk[21][1]*vnk[21][1]))))
      +((.003916*(wk[21][2]*wk[21][2]))+((.001361*(wk[21][0]*wk[21][0]))+(
      .003709*(wk[21][1]*wk[21][1])))))+temp[3])));
/*
 Used 0.08 seconds CPU time,
 32768 additional bytes of memory.
 Equations contain  239 adds/subtracts/negates
                    407 multiplies
                      0 divides
                     23 assignments
*/
}

sdsys(mtoto,cm,icm)
    double *mtoto,cm[3],icm[3][3];
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 20-Feb-2002 17:54:57 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[23][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = 71.005252;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    temp[0] = (((11.15*((q[1]*q[1])+(q[2]*q[2])))+((.0548*(Cik[3][0][2]*
      Cik[3][0][2]))+((.0825*(Cik[3][0][1]*Cik[3][0][1]))+(.0973*(Cik[3][0][0]*
      Cik[3][0][0])))))+((32.413*((rnk[8][1]*rnk[8][1])+(rnk[8][2]*rnk[8][2])))+
      ((1.3552*(cnk[8][0][2]*cnk[8][0][2]))+((.7153*(cnk[7][0][1]*cnk[7][0][1]))
      +(1.396*(cnk[8][0][0]*cnk[8][0][0]))))));
    temp[1] = (((3.51*((rnk[12][1]*rnk[12][1])+(rnk[12][2]*rnk[12][2])))+((.0484
      *(cnk[12][0][2]*cnk[12][0][2]))+((.0048*(cnk[12][0][1]*cnk[12][0][1]))+(
      .0477*(cnk[12][0][0]*cnk[12][0][0])))))+(((8.806*((rnk[11][1]*rnk[11][1])+
      (rnk[11][2]*rnk[11][2])))+((.1337*(cnk[11][0][2]*cnk[11][0][2]))+((.0332*(
      cnk[10][0][1]*cnk[10][0][1]))+(.1268*(cnk[11][0][0]*cnk[11][0][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[15][1]*rnk[15][1])+(rnk[15][2]*rnk[15][2])))+((
      .000119*(cnk[15][0][2]*cnk[15][0][2]))+((.000117*(cnk[15][0][0]*
      cnk[15][0][0]))+(.000179*(cnk[15][0][1]*cnk[15][0][1])))))+(((1.2*((
      rnk[14][1]*rnk[14][1])+(rnk[14][2]*rnk[14][2])))+((.003916*(cnk[14][0][2]*
      cnk[14][0][2]))+((.001361*(cnk[14][0][0]*cnk[14][0][0]))+(.003709*(
      cnk[14][0][1]*cnk[14][0][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[19][1]*rnk[19][1])+(rnk[19][2]*rnk[19][2])))+((.0484
      *(cnk[19][0][2]*cnk[19][0][2]))+((.0048*(cnk[19][0][1]*cnk[19][0][1]))+(
      .0477*(cnk[19][0][0]*cnk[19][0][0])))))+(((8.806*((rnk[18][1]*rnk[18][1])+
      (rnk[18][2]*rnk[18][2])))+((.1337*(cnk[18][0][2]*cnk[18][0][2]))+((.0332*(
      cnk[17][0][1]*cnk[17][0][1]))+(.1268*(cnk[18][0][0]*cnk[18][0][0])))))+
      temp[2]));
    icm[0][0] = ((((.205126*((rnk[22][1]*rnk[22][1])+(rnk[22][2]*rnk[22][2])))+(
      (.000119*(cnk[22][0][2]*cnk[22][0][2]))+((.000117*(cnk[22][0][0]*
      cnk[22][0][0]))+(.000179*(cnk[22][0][1]*cnk[22][0][1])))))+(((1.2*((
      rnk[21][1]*rnk[21][1])+(rnk[21][2]*rnk[21][2])))+((.003916*(cnk[21][0][2]*
      cnk[21][0][2]))+((.001361*(cnk[21][0][0]*cnk[21][0][0]))+(.003709*(
      cnk[21][0][1]*cnk[21][0][1])))))+temp[3]))-(71.005252*((com[1]*com[1])+(
      com[2]*com[2]))));
    temp[0] = ((((.0548*(Cik[3][0][2]*Cik[3][1][2]))+((.0825*(Cik[3][0][1]*
      Cik[3][1][1]))+(.0973*(Cik[3][0][0]*Cik[3][1][0]))))-(11.15*(q[0]*q[1])))+
      (((1.3552*(cnk[8][0][2]*cnk[8][1][2]))+((.7153*(cnk[7][0][1]*cnk[7][1][1])
      )+(1.396*(cnk[8][0][0]*cnk[8][1][0]))))-(32.413*(rnk[8][0]*rnk[8][1]))));
    temp[1] = ((((.0484*(cnk[12][0][2]*cnk[12][1][2]))+((.0048*(cnk[12][0][1]*
      cnk[12][1][1]))+(.0477*(cnk[12][0][0]*cnk[12][1][0]))))-(3.51*(rnk[12][0]*
      rnk[12][1])))+((((.1337*(cnk[11][0][2]*cnk[11][1][2]))+((.0332*(
      cnk[10][0][1]*cnk[10][1][1]))+(.1268*(cnk[11][0][0]*cnk[11][1][0]))))-(
      8.806*(rnk[11][0]*rnk[11][1])))+temp[0]));
    temp[2] = ((((.000119*(cnk[15][0][2]*cnk[15][1][2]))+((.000117*(
      cnk[15][0][0]*cnk[15][1][0]))+(.000179*(cnk[15][0][1]*cnk[15][1][1]))))-(
      .205126*(rnk[15][0]*rnk[15][1])))+((((.003916*(cnk[14][0][2]*cnk[14][1][2]
      ))+((.001361*(cnk[14][0][0]*cnk[14][1][0]))+(.003709*(cnk[14][0][1]*
      cnk[14][1][1]))))-(1.2*(rnk[14][0]*rnk[14][1])))+temp[1]));
    temp[3] = ((((.0484*(cnk[19][0][2]*cnk[19][1][2]))+((.0048*(cnk[19][0][1]*
      cnk[19][1][1]))+(.0477*(cnk[19][0][0]*cnk[19][1][0]))))-(3.51*(rnk[19][0]*
      rnk[19][1])))+((((.1337*(cnk[18][0][2]*cnk[18][1][2]))+((.0332*(
      cnk[17][0][1]*cnk[17][1][1]))+(.1268*(cnk[18][0][0]*cnk[18][1][0]))))-(
      8.806*(rnk[18][0]*rnk[18][1])))+temp[2]));
    icm[0][1] = ((71.005252*(com[0]*com[1]))+((((.000119*(cnk[22][0][2]*
      cnk[22][1][2]))+((.000117*(cnk[22][0][0]*cnk[22][1][0]))+(.000179*(
      cnk[22][0][1]*cnk[22][1][1]))))-(.205126*(rnk[22][0]*rnk[22][1])))+((((
      .003916*(cnk[21][0][2]*cnk[21][1][2]))+((.001361*(cnk[21][0][0]*
      cnk[21][1][0]))+(.003709*(cnk[21][0][1]*cnk[21][1][1]))))-(1.2*(rnk[21][0]
      *rnk[21][1])))+temp[3])));
    temp[0] = ((((.0548*(Cik[3][0][2]*Cik[3][2][2]))+((.0825*(Cik[3][0][1]*
      Cik[3][2][1]))+(.0973*(Cik[3][0][0]*Cik[3][2][0]))))-(11.15*(q[0]*q[2])))+
      (((1.3552*(cnk[8][0][2]*cnk[8][2][2]))+((.7153*(cnk[7][0][1]*cnk[7][2][1])
      )+(1.396*(cnk[8][0][0]*cnk[8][2][0]))))-(32.413*(rnk[8][0]*rnk[8][2]))));
    temp[1] = ((((.0484*(cnk[12][0][2]*cnk[12][2][2]))+((.0048*(cnk[12][0][1]*
      cnk[12][2][1]))+(.0477*(cnk[12][0][0]*cnk[12][2][0]))))-(3.51*(rnk[12][0]*
      rnk[12][2])))+((((.1337*(cnk[11][0][2]*cnk[11][2][2]))+((.0332*(
      cnk[10][0][1]*cnk[10][2][1]))+(.1268*(cnk[11][0][0]*cnk[11][2][0]))))-(
      8.806*(rnk[11][0]*rnk[11][2])))+temp[0]));
    temp[2] = ((((.000119*(cnk[15][0][2]*cnk[15][2][2]))+((.000117*(
      cnk[15][0][0]*cnk[15][2][0]))+(.000179*(cnk[15][0][1]*cnk[15][2][1]))))-(
      .205126*(rnk[15][0]*rnk[15][2])))+((((.003916*(cnk[14][0][2]*cnk[14][2][2]
      ))+((.001361*(cnk[14][0][0]*cnk[14][2][0]))+(.003709*(cnk[14][0][1]*
      cnk[14][2][1]))))-(1.2*(rnk[14][0]*rnk[14][2])))+temp[1]));
    temp[3] = ((((.0484*(cnk[19][0][2]*cnk[19][2][2]))+((.0048*(cnk[19][0][1]*
      cnk[19][2][1]))+(.0477*(cnk[19][0][0]*cnk[19][2][0]))))-(3.51*(rnk[19][0]*
      rnk[19][2])))+((((.1337*(cnk[18][0][2]*cnk[18][2][2]))+((.0332*(
      cnk[17][0][1]*cnk[17][2][1]))+(.1268*(cnk[18][0][0]*cnk[18][2][0]))))-(
      8.806*(rnk[18][0]*rnk[18][2])))+temp[2]));
    icm[0][2] = ((71.005252*(com[0]*com[2]))+((((.000119*(cnk[22][0][2]*
      cnk[22][2][2]))+((.000117*(cnk[22][0][0]*cnk[22][2][0]))+(.000179*(
      cnk[22][0][1]*cnk[22][2][1]))))-(.205126*(rnk[22][0]*rnk[22][2])))+((((
      .003916*(cnk[21][0][2]*cnk[21][2][2]))+((.001361*(cnk[21][0][0]*
      cnk[21][2][0]))+(.003709*(cnk[21][0][1]*cnk[21][2][1]))))-(1.2*(rnk[21][0]
      *rnk[21][2])))+temp[3])));
    icm[1][0] = icm[0][1];
    temp[0] = (((11.15*((q[0]*q[0])+(q[2]*q[2])))+((.0548*(Cik[3][1][2]*
      Cik[3][1][2]))+((.0825*(Cik[3][1][1]*Cik[3][1][1]))+(.0973*(Cik[3][1][0]*
      Cik[3][1][0])))))+((32.413*((rnk[8][0]*rnk[8][0])+(rnk[8][2]*rnk[8][2])))+
      ((1.3552*(cnk[8][1][2]*cnk[8][1][2]))+((.7153*(cnk[7][1][1]*cnk[7][1][1]))
      +(1.396*(cnk[8][1][0]*cnk[8][1][0]))))));
    temp[1] = (((3.51*((rnk[12][0]*rnk[12][0])+(rnk[12][2]*rnk[12][2])))+((.0484
      *(cnk[12][1][2]*cnk[12][1][2]))+((.0048*(cnk[12][1][1]*cnk[12][1][1]))+(
      .0477*(cnk[12][1][0]*cnk[12][1][0])))))+(((8.806*((rnk[11][0]*rnk[11][0])+
      (rnk[11][2]*rnk[11][2])))+((.1337*(cnk[11][1][2]*cnk[11][1][2]))+((.0332*(
      cnk[10][1][1]*cnk[10][1][1]))+(.1268*(cnk[11][1][0]*cnk[11][1][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[15][0]*rnk[15][0])+(rnk[15][2]*rnk[15][2])))+((
      .000119*(cnk[15][1][2]*cnk[15][1][2]))+((.000117*(cnk[15][1][0]*
      cnk[15][1][0]))+(.000179*(cnk[15][1][1]*cnk[15][1][1])))))+(((1.2*((
      rnk[14][0]*rnk[14][0])+(rnk[14][2]*rnk[14][2])))+((.003916*(cnk[14][1][2]*
      cnk[14][1][2]))+((.001361*(cnk[14][1][0]*cnk[14][1][0]))+(.003709*(
      cnk[14][1][1]*cnk[14][1][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[19][0]*rnk[19][0])+(rnk[19][2]*rnk[19][2])))+((.0484
      *(cnk[19][1][2]*cnk[19][1][2]))+((.0048*(cnk[19][1][1]*cnk[19][1][1]))+(
      .0477*(cnk[19][1][0]*cnk[19][1][0])))))+(((8.806*((rnk[18][0]*rnk[18][0])+
      (rnk[18][2]*rnk[18][2])))+((.1337*(cnk[18][1][2]*cnk[18][1][2]))+((.0332*(
      cnk[17][1][1]*cnk[17][1][1]))+(.1268*(cnk[18][1][0]*cnk[18][1][0])))))+
      temp[2]));
    icm[1][1] = ((((.205126*((rnk[22][0]*rnk[22][0])+(rnk[22][2]*rnk[22][2])))+(
      (.000119*(cnk[22][1][2]*cnk[22][1][2]))+((.000117*(cnk[22][1][0]*
      cnk[22][1][0]))+(.000179*(cnk[22][1][1]*cnk[22][1][1])))))+(((1.2*((
      rnk[21][0]*rnk[21][0])+(rnk[21][2]*rnk[21][2])))+((.003916*(cnk[21][1][2]*
      cnk[21][1][2]))+((.001361*(cnk[21][1][0]*cnk[21][1][0]))+(.003709*(
      cnk[21][1][1]*cnk[21][1][1])))))+temp[3]))-(71.005252*((com[0]*com[0])+(
      com[2]*com[2]))));
    temp[0] = ((((.0548*(Cik[3][1][2]*Cik[3][2][2]))+((.0825*(Cik[3][1][1]*
      Cik[3][2][1]))+(.0973*(Cik[3][1][0]*Cik[3][2][0]))))-(11.15*(q[1]*q[2])))+
      (((1.3552*(cnk[8][1][2]*cnk[8][2][2]))+((.7153*(cnk[7][1][1]*cnk[7][2][1])
      )+(1.396*(cnk[8][1][0]*cnk[8][2][0]))))-(32.413*(rnk[8][1]*rnk[8][2]))));
    temp[1] = ((((.0484*(cnk[12][1][2]*cnk[12][2][2]))+((.0048*(cnk[12][1][1]*
      cnk[12][2][1]))+(.0477*(cnk[12][1][0]*cnk[12][2][0]))))-(3.51*(rnk[12][1]*
      rnk[12][2])))+((((.1337*(cnk[11][1][2]*cnk[11][2][2]))+((.0332*(
      cnk[10][1][1]*cnk[10][2][1]))+(.1268*(cnk[11][1][0]*cnk[11][2][0]))))-(
      8.806*(rnk[11][1]*rnk[11][2])))+temp[0]));
    temp[2] = ((((.000119*(cnk[15][1][2]*cnk[15][2][2]))+((.000117*(
      cnk[15][1][0]*cnk[15][2][0]))+(.000179*(cnk[15][1][1]*cnk[15][2][1]))))-(
      .205126*(rnk[15][1]*rnk[15][2])))+((((.003916*(cnk[14][1][2]*cnk[14][2][2]
      ))+((.001361*(cnk[14][1][0]*cnk[14][2][0]))+(.003709*(cnk[14][1][1]*
      cnk[14][2][1]))))-(1.2*(rnk[14][1]*rnk[14][2])))+temp[1]));
    temp[3] = ((((.0484*(cnk[19][1][2]*cnk[19][2][2]))+((.0048*(cnk[19][1][1]*
      cnk[19][2][1]))+(.0477*(cnk[19][1][0]*cnk[19][2][0]))))-(3.51*(rnk[19][1]*
      rnk[19][2])))+((((.1337*(cnk[18][1][2]*cnk[18][2][2]))+((.0332*(
      cnk[17][1][1]*cnk[17][2][1]))+(.1268*(cnk[18][1][0]*cnk[18][2][0]))))-(
      8.806*(rnk[18][1]*rnk[18][2])))+temp[2]));
    icm[1][2] = ((71.005252*(com[1]*com[2]))+((((.000119*(cnk[22][1][2]*
      cnk[22][2][2]))+((.000117*(cnk[22][1][0]*cnk[22][2][0]))+(.000179*(
      cnk[22][1][1]*cnk[22][2][1]))))-(.205126*(rnk[22][1]*rnk[22][2])))+((((
      .003916*(cnk[21][1][2]*cnk[21][2][2]))+((.001361*(cnk[21][1][0]*
      cnk[21][2][0]))+(.003709*(cnk[21][1][1]*cnk[21][2][1]))))-(1.2*(rnk[21][1]
      *rnk[21][2])))+temp[3])));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((11.15*((q[0]*q[0])+(q[1]*q[1])))+((.0548*(Cik[3][2][2]*
      Cik[3][2][2]))+((.0825*(Cik[3][2][1]*Cik[3][2][1]))+(.0973*(Cik[3][2][0]*
      Cik[3][2][0])))))+((32.413*((rnk[8][0]*rnk[8][0])+(rnk[8][1]*rnk[8][1])))+
      ((1.3552*(cnk[8][2][2]*cnk[8][2][2]))+((.7153*(cnk[7][2][1]*cnk[7][2][1]))
      +(1.396*(cnk[8][2][0]*cnk[8][2][0]))))));
    temp[1] = (((3.51*((rnk[12][0]*rnk[12][0])+(rnk[12][1]*rnk[12][1])))+((.0484
      *(cnk[12][2][2]*cnk[12][2][2]))+((.0048*(cnk[12][2][1]*cnk[12][2][1]))+(
      .0477*(cnk[12][2][0]*cnk[12][2][0])))))+(((8.806*((rnk[11][0]*rnk[11][0])+
      (rnk[11][1]*rnk[11][1])))+((.1337*(cnk[11][2][2]*cnk[11][2][2]))+((.0332*(
      cnk[10][2][1]*cnk[10][2][1]))+(.1268*(cnk[11][2][0]*cnk[11][2][0])))))+
      temp[0]));
    temp[2] = (((.205126*((rnk[15][0]*rnk[15][0])+(rnk[15][1]*rnk[15][1])))+((
      .000119*(cnk[15][2][2]*cnk[15][2][2]))+((.000117*(cnk[15][2][0]*
      cnk[15][2][0]))+(.000179*(cnk[15][2][1]*cnk[15][2][1])))))+(((1.2*((
      rnk[14][0]*rnk[14][0])+(rnk[14][1]*rnk[14][1])))+((.003916*(cnk[14][2][2]*
      cnk[14][2][2]))+((.001361*(cnk[14][2][0]*cnk[14][2][0]))+(.003709*(
      cnk[14][2][1]*cnk[14][2][1])))))+temp[1]));
    temp[3] = (((3.51*((rnk[19][0]*rnk[19][0])+(rnk[19][1]*rnk[19][1])))+((.0484
      *(cnk[19][2][2]*cnk[19][2][2]))+((.0048*(cnk[19][2][1]*cnk[19][2][1]))+(
      .0477*(cnk[19][2][0]*cnk[19][2][0])))))+(((8.806*((rnk[18][0]*rnk[18][0])+
      (rnk[18][1]*rnk[18][1])))+((.1337*(cnk[18][2][2]*cnk[18][2][2]))+((.0332*(
      cnk[17][2][1]*cnk[17][2][1]))+(.1268*(cnk[18][2][0]*cnk[18][2][0])))))+
      temp[2]));
    icm[2][2] = ((((.205126*((rnk[22][0]*rnk[22][0])+(rnk[22][1]*rnk[22][1])))+(
      (.000119*(cnk[22][2][2]*cnk[22][2][2]))+((.000117*(cnk[22][2][0]*
      cnk[22][2][0]))+(.000179*(cnk[22][2][1]*cnk[22][2][1])))))+(((1.2*((
      rnk[21][0]*rnk[21][0])+(rnk[21][1]*rnk[21][1])))+((.003916*(cnk[21][2][2]*
      cnk[21][2][2]))+((.001361*(cnk[21][2][0]*cnk[21][2][0]))+(.003709*(
      cnk[21][2][1]*cnk[21][2][1])))))+temp[3]))-(71.005252*((com[0]*com[0])+(
      com[1]*com[1]))));
/*
 Used 0.23 seconds CPU time,
 49152 additional bytes of memory.
 Equations contain  273 adds/subtracts/negates
                    525 multiplies
                      0 divides
                     37 assignments
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

    if ((coord < 0) || (coord > 22)) {
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

    if ((bnum < -1) || (bnum > 9)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(routine,jnum)
    int routine,jnum;
{

    if ((jnum < 0) || (jnum > 9)) {
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
    double st[24],stang[23];
{
    int i;
    double dc[3][3];

    for (i = 0; i < 23; i++) {
        stang[i] = st[i];
    }
    sdquat2dc(st[3],st[4],st[5],st[23],dc);
    sddc2ang(dc,&stang[3],&stang[4],&stang[5]);
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

sdang2st(stang,st)
    double stang[23],st[24];
{
    int i;
    double dc[3][3];

    for (i = 0; i < 23; i++) {
        st[i] = stang[i];
    }
    sdang2dc(stang[3],stang[4],stang[5],dc);
    sddc2quat(dc,&st[3],&st[4],&st[5],&st[23]);
}

/* Normalize Euler parameters in state. */

sdnrmsterr(st,normst,routine)
    double st[24],normst[24];
    int routine;
{
    int i;
    double norm;

    for (i = 0; i < 24; i++) {
        normst[i] = st[i];
    }
    norm = sqrt(st[3]*st[3]+st[4]*st[4]+st[5]*st[5]+st[23]*st[23]);
    if (routine != 0) {
        if ((norm < .9) || (norm > 1.1)) {
            sdseterr(routine,14);
        }
    }
    if (norm == 0.) {
        normst[23] = 1.;
        norm = 1.;
    }
    norm = 1./norm;
    normst[3] = normst[3]*norm;
    normst[4] = normst[4]*norm;
    normst[5] = normst[5]*norm;
    normst[23] = normst[23]*norm;
}

sdnormst(st,normst)
    double st[24],normst[24];
{

    sdnrmsterr(st,normst,0);
}

sdgentime(gentm)
    int *gentm;
{

    *gentm = 175441;
}
/*
Done. CPU seconds used: 3.20  Memory used: 1318912 bytes.
Equation complexity:
  sdstate:   971 adds  1409 multiplies     1 divides   918 assignments
  sdderiv:  7596 adds 10298 multiplies    23 divides  6138 assignments
  sdresid:  2827 adds  3658 multiplies     0 divides  1546 assignments
  sdreac:    550 adds   386 multiplies     0 divides   396 assignments
  sdmom:     239 adds   407 multiplies     0 divides    23 assignments
  sdsys:     273 adds   525 multiplies     0 divides    37 assignments
*/
