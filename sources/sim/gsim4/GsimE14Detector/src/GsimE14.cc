/**
 *  @file
 *  @brief  GsimE14
 *  $Id: GsimE14.cc,v 1.4 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14.cc,v $
 *  Revision 1.4  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14.h"
#include "GsimE14Detector/GsimE14UserGeom.h"

#include "GsimE14Detector/GsimE14Membrane.h"

#include "GsimE14Detector/GsimE14FBAR.h"
#include "GsimE14Detector/GsimE14CBAR.h"
#include "GsimE14Detector/GsimE14BCV.h"
#include "GsimE14Detector/GsimE14CV.h"
#include "GsimE14Detector/GsimE14LCV.h"
#include "GsimE14Detector/GsimE14CSI.h"
#include "GsimE14Detector/GsimE14OEV.h"
//#include "GsimE14Detector/GsimE14CC00.h"
//#include "GsimE14Detector/GsimE14CC01.h"
#include "GsimE14Detector/GsimE14CC02.h"
#include "GsimE14Detector/GsimE14CC03.h"
#include "GsimE14Detector/GsimE14CC04.h"
#include "GsimE14Detector/GsimE14CC05.h"
#include "GsimE14Detector/GsimE14CC06.h"
#include "GsimE14Detector/GsimE14BHCV.h"
#include "GsimE14Detector/GsimE14BHPV.h"

#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimTube.h"

#include "G4Track.hh"
#include "G4VProcess.hh"

#include <sstream>

using namespace E14;


GsimE14::GsimE14(std::string name,
		 GsimDetector* motherDetector,
		 G4ThreeVector transV,G4ThreeVector rotV,
		 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14";

  m_photoNuclearDetID = new int[1000];

  GsimE14Membrane* mbn = new GsimE14Membrane("mbn",this,
						 G4ThreeVector(0,0,0),
						 G4ThreeVector(0,0,0));
  addDaughter(mbn);
  m_detMoveList.push_back(mbn);
  

  GsimE14FBAR* fbar = new GsimE14FBAR("fbar",this,
					  G4ThreeVector(0,0,(Fbar_Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(fbar);
  
  
  GsimE14CBAR* cbar = new GsimE14CBAR("cbar",this,
					  G4ThreeVector(0,0,(Detpos_cbar_z+Cbar_Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cbar);
  
  GsimE14BCV* bcv = new GsimE14BCV("bcv",this,
					     G4ThreeVector(0,0,(Detpos_cbar_z+Cbar_Len/2.)*cm),
					     G4ThreeVector(0,0,0));
  addDaughter(bcv);
  m_detMoveList.push_back(bcv);
  
  
  GsimE14CV* cv = new GsimE14CV("cv",this,
				    G4ThreeVector(0,0,(Csic_Zmin)*cm),
				    G4ThreeVector(0,0,0));
  addDaughter(cv);
  m_detMoveList.push_back(cv);

  GsimE14CSI* csi = new GsimE14CSI("csi",this,
				   G4ThreeVector(0,0,(Csir_Zmin+Csir_Len/2.)*cm),
				   G4ThreeVector(0,0,0));
  addDaughter(csi);
  
  GsimE14OEV* oev = new GsimE14OEV("oev",this,
				   G4ThreeVector(0,0,(Csic_Zmin+KtevCsic_Len/2.)*cm),
				   G4ThreeVector(0,0,0));
  addDaughter(oev);
  

//   double cc00Len= GsimE14CC00::getCC00Length();
//   GsimE14CC00* cc00 = new GsimE14CC00("cc00",this,
// 					  G4ThreeVector(0,0,(Detpos_cc00_z+cc00Len/2.)*cm),
// 					  G4ThreeVector(0,0,0));
//   addDaughter(cc00);

//   double cc01Len= GsimE14CC01::getCC01Length();
//   GsimE14CC01* cc01 = new GsimE14CC01("cc01",this,
// 					  G4ThreeVector(0,0,(Detpos_cc01_z+cc01Len/2.)*cm),
// 					  G4ThreeVector(0,0,0));
//   addDaughter(cc01);

  double cc02Len= GsimE14CC02::getCC02Length();
  GsimE14CC02* cc02 = new GsimE14CC02("cc02",this,
					  G4ThreeVector(0,0,(Fbar_Len-Detpos_cc02_z_shift-cc02Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cc02);
  

  GsimE14CC03* cc03 = new GsimE14CC03("cc03",this,
					  G4ThreeVector(0,0,(Detpos_cc03_z+CC03_Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cc03);

  GsimE14LCV* lcv = new GsimE14LCV("lcv",this,
				   G4ThreeVector(0,0,(Detpos_cc03_z+CC03_Len/2.)*cm),
				   G4ThreeVector(0,0,0));
  addDaughter(lcv);
  m_detMoveList.push_back(lcv);
  
  double cc04Len= GsimE14CC04::getCC04Length();
  GsimE14CC04* cc04 = new GsimE14CC04("cc04",this,
					  G4ThreeVector(0,0,(Detpos_cc04_z+cc04Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cc04);

  double cc05Len= GsimE14CC05::getCC05Length();
  GsimE14CC05* cc05 = new GsimE14CC05("cc05",this,
					  G4ThreeVector(0,0,(Detpos_cc05_z+cc05Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cc05);

  
  double cc06Len= GsimE14CC06::getCC06Length();
  GsimE14CC06* cc06 = new GsimE14CC06("cc06",this,
					  G4ThreeVector(0,0,(Detpos_cc06_z+cc06Len/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(cc06);
  
  double BHCVLen=GsimE14BHCV::getBHCVLength();
  GsimE14BHCV* bhcv = new GsimE14BHCV("bhcv",this,
					  G4ThreeVector(0,0,(Detpos_bhcv_z+BHCVLen/2.)*cm),
					  G4ThreeVector(0,0,0));
  addDaughter(bhcv);
  m_detMoveList.push_back(bhcv);

  double BHPVLen=GsimE14BHPV::getBHPVLength();
  GsimE14BHPV* bhpv = new GsimE14BHPV("bhpv",this,
				      G4ThreeVector(0,0,(Detpos_bhpv_z+BHPVLen/2)*cm),
				      G4ThreeVector(0,0,0),
				      userFlag);
  addDaughter(bhpv);
}


GsimE14::~GsimE14()
{
  delete [] m_photoNuclearDetID;
}



void GsimE14::beginOfRunAction()
{
  GsimPersistencyManager* pm= GsimPersistencyManager::getPersistencyManager();
  pm->setBranchOf("eventTree",
		  "photoNuclearN",&m_photoNuclearN,"photoNuclearN/I");
  pm->setBranchOf("eventTree",
		  "photoNuclearDetID",m_photoNuclearDetID,"photoNuclearDetID[photoNuclearN]/I");
}

void GsimE14::endOfRunAction()
{
  ;
}

bool GsimE14::beginOfEventAction(const G4Event*)
{
  m_photoNuclearN=0;
  return true;
}

bool GsimE14::endOfEventAction(const G4Event*)
{
  return false;
}

bool GsimE14::steppingAction(const G4Step* theStep)
{
  G4Track* track = theStep->GetTrack();
  G4String theProName =""; 
  if(theStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
    theProName = 
      theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  }
  if(theProName == "PhotonInelastic") {
    GsimPersistencyManager* persistencyManager
      = GsimPersistencyManager::getPersistencyManager();
    std::string volumeName = std::string( (track->GetVolume()->GetName()).data() );
    int detID=persistencyManager->getDetectorIDByPhysicalVolumeName(volumeName);
    int briefID = persistencyManager->getDetectorBriefIDByID(detID);
    if(briefID!=-1) {
      if(m_photoNuclearN<1000) {
	m_photoNuclearDetID[m_photoNuclearN]=briefID;
	m_photoNuclearN++;
      }
    }
  }
  return true;
}



void GsimE14::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //reset
  if(m_fastSimulationLevel==6) {
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z+29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setThisAndDaughterOuterVisibility(true);
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z-29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setThisAndDaughterOuterVisibility(false);
    }
  }

  
  {
    m_fastSimulationLevel=level;
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->setFastSimulationLevel(level);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}
