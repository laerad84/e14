/**
 *  @file
 *  @brief  GsimE391Membrane
 *  $Id: GsimE391Membrane.cc,v 1.1 2007/02/04 12:57:39 nanjo Exp $ 
 *  $Log: GsimE391Membrane.cc,v $
 *  Revision 1.1  2007/02/04 12:57:39  nanjo
 *  GsimE391Membrane is added.
 *
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391Membrane.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimTube.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E391;

GsimE391Membrane::GsimE391Membrane(std::string name,
				   GsimDetector* motherDetector,
				   G4ThreeVector transV,G4ThreeVector rotV,
				   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391Membrane";
  // Membrane


  double mbn_thick  = 0.02; // 0.2 mm 
  double mbn_diameter = 10.6; // 10.6 cm in diameter
  double thickness_CV = 0.6;
  double CV_inner_length = 50.0;
  //double c_mbn1_z2 = Csic_Zmin -  CV_inner_length - thickness_CV - 0.5; // 0.5 is margine
  double c_mbn1_z2 = Csic_Zmin -  CV_inner_length - thickness_CV - 0.8; // 0.8 is margine

  std::vector<double> paramVec;
  paramVec.push_back(0.);
  paramVec.push_back(mbn_diameter/2.*cm);
  paramVec.push_back(mbn_thick*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  GsimTube* usmbn = new GsimTube("usmbn",this,
				 G4ThreeVector(0,0,mbn_thick/2.*cm),
				 G4ThreeVector(0,0,0));
  usmbn->setParameters(paramVec);
  usmbn->setOuterMaterial("GsimMembrane");
  usmbn->setOuterVisibility(false);
  addDaughter(usmbn);

  

//   paramVec.clear();
//   paramVec.push_back(mbn_diameter/2.*cm);
//   paramVec.push_back(99*cm);
//   paramVec.push_back(mbn_thick*cm);
//   paramVec.push_back(0.);
//   paramVec.push_back(360.*deg);
  
//   GsimTube* cvmbn = new GsimTube("cvmbn",this,
// 				 G4ThreeVector(0,0,c_mbn1_z2*cm),
// 				 G4ThreeVector(0,0,0));
//   cvmbn->setParameters(paramVec);
//   cvmbn->setOuterMaterial("GsimMembrane");
//   cvmbn->setOuterVisibility(false);
//   addDaughter(cvmbn);


  double c_mbn1_z = //front face of CC04 
    Detpos_cc04_z-mbn_thick/2.;

  paramVec.clear();
  paramVec.push_back(0.);
  paramVec.push_back(mbn_diameter/2.*cm);
  paramVec.push_back(mbn_thick*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  GsimTube* dsmbn = new GsimTube("dsmbn",this,
				 G4ThreeVector(0,0,c_mbn1_z*cm),
				 G4ThreeVector(0,0,0));
  dsmbn->setParameters(paramVec);
  dsmbn->setOuterMaterial("GsimMembrane");
  dsmbn->setOuterVisibility(false);
  addDaughter(dsmbn);

  setThisAndDaughterBriefName("MBN");
}

GsimE391Membrane::~GsimE391Membrane()
{
  ;
}

