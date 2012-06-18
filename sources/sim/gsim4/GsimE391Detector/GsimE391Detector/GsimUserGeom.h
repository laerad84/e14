// -*- C++ -*-
//
// GsimUserGeom.h
// Geometry parameter definition
//
// Author:  Mitsuhiro YAMAGA (yamaga@post.kek.jp)
// Created: Thu Jul 12 15:12:46 JST 2001
//
// $Id: GsimUserGeom.h,v 1.4 2007/02/04 12:56:46 nanjo Exp $
//
// Revision History
//
// $Log: GsimUserGeom.h,v $
// Revision 1.4  2007/02/04 12:56:46  nanjo
// GsimBoxWithAHole is used.
//
// Revision 1.3  2006/11/16 23:06:54  nanjo
// Remove extra ;
//
// Revision 1.2  2006/10/26 15:20:25  nanjo
// E391 name space is added.
//
// Revision 1.1  2006/02/03 11:04:50  nanjo
// BHCV and CC06 are added.
//
// Revision 1.11  2005/05/11 16:46:21  toshi
// add GsimUserGeom_CC00, GsimUserGeom_BHCV2.
//
// Revision 1.10  2005/01/27 17:42:53  yamaga
// Updated for neutronMC.
//
// Revision 1.9  2004/07/23 06:43:49  toshi
// Fiber length added
//
// Revision 1.8  2004/06/21 14:09:20  kensh
// Update geometry.
// Z position of CsI and MB was corrected to the drawing values.
//
// Revision 1.7  2004/03/31 10:34:59  kensh
// Describe detector z  position.
//
// Revision 1.6  2004/03/31 01:37:46  kensh
// Update for CC02 by H.Watanabe.
// Add constant of detector position.
//
// Revision 1.5  2004/03/27 17:12:19  kensh
// Update.
//
// Revision 1.4  2004/03/27 03:00:52  kensh
// Update detector for BA,BHCV,CC06,CC07 by H.Watanabe.
//
// Revision 1.3  2003/06/17 19:43:59  kensh
// Separate the geometory description for BarrelChargedVeto.
//
// Revision 1.2  2003/01/31 14:59:34  yamaga
// New gsim code for MIDAS output with e391bank system.
//
// Revision 1.1.1.1  2002/08/13 12:48:08  kensh
//
//
// Start version.
//
//

#ifndef GSIMGEOM_E391A_H_INCLUDED
#define GSIMGEOM_E391A_H_INCLUDED

namespace E391 {

  static const int  grot_z_32      = 101; // 101-132; 32 devision
  static const int  grot_x90_z_32  = 201; // 201-232; 32 devision
  static const int  grot_y90_z_32  = 301; // 301-332; 32 devision
  static const int  grot_x180_z_32 = 401; // 401-432; 32 devision
  static const int  grot_cc02      = 701 ; // 701-712 ; cc02
  static const int  grot_cvs       = 801 ; // CV support
  
  // Constants
  static double  Cbar_Len     = 550; // Length of MainBarrel (bottom)
  static double  Fiber_Len    = 640; // Length of fibers for barrel counters
  
  static double  Fbar_Len     = 275;
  static double  Fbar_Rmin    = 30.83;
  static double  Csir_Len     = 180; // CsI region
  //static double  Csir_Zmin    = 605; // CsI region
  //static double  Csic_Zmin    = 610; // CsI face
  static double  Csir_Zmin    = 609.8; // CsI region (updated : Mon Jun 21 22:45:34 JST 2004)
  static double  Csic_Zmin    = 614.8; // CsI face   (updated : Mon Jun 21 22:45:34 JST 2004)
  static double  Csic_XY      = 7.0;
  static double  Csic_Len     = 30.0;
  static double  Csic_Gap     = 0.03;
  static double  KtevCsic_XY  = 5.0;
  static double  KtevCsic_Len = 50.0;
  static double  KtevCsic_Gap = (Csic_Gap*5/7);

  // Measured by Misha (27/Mar/2004)
  static double  Detpos_csi_z   = Csic_Zmin;             // 610.0 cm
  static double  Detpos_cc03_z  = Detpos_csi_z - 5.;     // 605.0 cm
  static double  Detpos_cc04_z  = Detpos_csi_z + 95.5;   // 705.5 cm
  static double  Detpos_cc05_z  = Detpos_csi_z + 259.3;  // 869.3 cm
  static double  Detpos_cc06_z  = Detpos_csi_z + 310.8;  // 920.8 cm
  static double  Detpos_cc07_z  = Detpos_csi_z + 385.8;  // 995.8 cm
  static double  Detpos_bhcv_z  = Detpos_csi_z + 414.5;  // 1024.5 cm
  static double  Detpos_ba_z    = Detpos_csi_z + 444.5;  // 1054.5 cm
  
  //
  //static double  Detpos_cbar_z  = 135.;  // z = 135 cm
  static double  Detpos_cbar_z  = 134.8;  // z = 134.8 cm (updated : Mon Jun 21 22:45:34 JST 2004)
  
  // by Toshi
  static double  Detpos_cc00_z = -59.0;
  // the end point of CC00
  // : the edge of the blue structure
  
}

#endif // GSIMGEOM_E391A_H_INCLUDED

