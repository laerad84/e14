/**
 *  @file
 *  @brief  GsimUserGeom.h
 *  $Id: GsimE14UserGeom.h,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14UserGeom.h,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */

#ifndef GsimE14UserGeom_h
#define GsimE14UserGeom_h

namespace E14 {
  // Constants
  static double  Cbar_Len     = 550; // Length of MainBarrel (bottom)
  static double  Fiber_Len    = 640; // Length of fibers for barrel counters
  
  static double  Fbar_Len     = 275;
  static double  Fbar_Rmin    = 30.83;
  static double  Csir_Len     = 180; // CsI region
  static double  Csir_Zmin    = 609.8; // CsI region (updated : Mon Jun 21 22:45:34 JST 2004)
  static double  Csic_Zmin    = 614.8; // CsI face   (updated : Mon Jun 21 22:45:34 JST 2004)
  static double  Csic_XY      = 7.0;
  static double  Csic_Len     = 30.0;
  static double  Csic_Gap     = 0.03;
  static double  KtevCsic_XY  = 5.0;
  static double  KtevCsic_Len = 50.0;
  static double  KtevCsic_Gap = 0.01; //corrected by Matsumura
  
  static double  KtevCsicFine_XY  = 2.5;
  static double  KtevCsicFine_Len = 50.0;
  static double  KtevCsicFine_Gap = KtevCsic_Gap*2.5/5.;

  static double  CC03_X  = 4.54;
  static double  CC03_Y  = 1.79;
  static double  CC03_Len = 50.0;
  static double  CC03_YGap=0.01;

  //////unused
  static double  CC03_XY  = 2.5;
  static double  CC03_Gap = KtevCsic_Gap*2.5/5.;
  static double  CC03_XY_NEW  = 2.2;
  static double  CC03_Len_NEW = 50.0;
  static double  CC03_Gap_NEW = 0.02;
  //////unused
  

  static double  CV_Len   =  50.0;

  static double  BeamLine_R = 10.6/2.;
  static double  MBN_Thick = 0.02;
  
  static double  Detpos_fbar_z  = 0;
  static double  Detpos_cbar_z  = 134.8;
  // Measured by Misha (27/Mar/2004)
  static double  Detpos_csi_z   = Csic_Zmin;
  
  static double  Detpos_cc00_z = -59.0;
  static double  Detpos_cc01_z =  0;
  static double  Detpos_cc02_z_shift = 30;
  static double  Detpos_cc03_z  = Detpos_csi_z;
  static double  Detpos_cc04_z  = Detpos_csi_z + 95.5;
  static double  Detpos_cc05_z  = Detpos_csi_z + 250;
  static double  Detpos_cc06_z  = Detpos_csi_z + 350;
  
  static double  Detpos_bhcv_z  = Detpos_csi_z + 400;
  static double  Detpos_bhpv_z  = Detpos_csi_z + 430 + 200;

  
}

#endif // GsimE14UserGeom_h

