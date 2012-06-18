/**
 *  @file
 *  @brief  GsimE14Membrane
 *  $Id: GsimE14Membrane.cc,v 1.4 2007/02/04 12:56:55 nanjo Exp $ 
 *  $Log: GsimE14Membrane.cc,v $
 *  Revision 1.4  2007/02/04 12:56:55  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14Membrane.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimE14Detector/GsimE14BHCV.h"
#include "GsimDetector/GsimTube.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14Membrane::GsimE14Membrane(std::string name,
				 GsimDetector* motherDetector,
				 G4ThreeVector transV,G4ThreeVector rotV,
				 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14Membrane";
  // Membrane

  std::vector<double> paramVec;
  paramVec.push_back(0.);
  paramVec.push_back(BeamLine_R*cm);
  paramVec.push_back(MBN_Thick*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  GsimTube* usmbn = new GsimTube("usmbn",this,
				 G4ThreeVector(0,0,MBN_Thick/2.*cm),
				 G4ThreeVector(0,0,0));
  usmbn->setParameters(paramVec);
  usmbn->setOuterMaterial("GsimMembrane");
  usmbn->setOuterVisibility(false);
  addDaughter(usmbn);

  // paramVec.clear();
//   paramVec.push_back(BeamLine_R*cm);
//   paramVec.push_back(99*cm);
//   paramVec.push_back(MBN_Thick*cm);
//   paramVec.push_back(0.);
//   paramVec.push_back(360.*deg);
//   GsimTube* cvmbn = new GsimTube("cvmbn",this,
// 				 G4ThreeVector(0,0,(Csic_Zmin-CV_Len-MBN_Thick/2.)*cm),
// 				 G4ThreeVector(0,0,0));
//   cvmbn->setParameters(paramVec);
//   cvmbn->setOuterMaterial("GsimMembrane");
//   cvmbn->setOuterVisibility(false);
//   addDaughter(cvmbn);


  double c_mbn1_z = //front face of CC04 
    Detpos_cc04_z-MBN_Thick/2.;

  paramVec.clear();
  paramVec.push_back(0.);
  paramVec.push_back(BeamLine_R*cm);
  paramVec.push_back(MBN_Thick*cm);
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

GsimE14Membrane::~GsimE14Membrane()
{
  ;
}

